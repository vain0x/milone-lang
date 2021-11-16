// Milone allocator for multi-threaded program.
// Requires OneTBB.

#include <cassert>
#include <cstddef>
#include <cstdio>
#include <cstdlib>

#include <tbb/combinable.h>

static void oom(void) {
    fprintf(stderr, "Out of memory.\n");
    exit(1);
}

// -----------------------------------------------
// Memory pool
// -----------------------------------------------

// structure for memory management. poor implementation. thread unsafe.
struct MemoryChunk {
    // start of allocated memory or null
    void *ptr;

    // used size
    size_t len;

    // total capacity
    size_t cap;

    // list of used chunks or null
    // each chunk is allocated by calloc and should be freed after leaving
    // region
    MemoryChunk *used;

    // parent region or null
    // each region is allocated by calloc and should be freed after leaving
    // region
    MemoryChunk *parent;
};

class MemoryPool {
    MemoryChunk heap_;
    size_t heap_level_; // depth of current region
    size_t heap_size_;  // consumed size in all regions
    size_t heap_alloc_; // allocated size in all regions
    size_t alloc_cost_; // allocation count

  private:
    // free chunk itself, not used list
    void free_chunk(MemoryChunk *chunk) {
        assert(chunk != NULL);
        assert(chunk->ptr != NULL);

        free(chunk->ptr);
        heap_size_ -= chunk->len;
        heap_alloc_ -= chunk->cap;
    }

  public:
    auto heap_size() const -> size_t { return heap_size_; }
    auto alloc_cost() const -> size_t { return alloc_cost_; }

    void enter_region() {
        // fprintf(stderr, "debug: enter_region level=%d size=%d\n",
        // s_heap_level + 1, heap_size_);

        MemoryChunk *parent = (MemoryChunk *)calloc(1, sizeof(MemoryChunk));
        if (parent == NULL) {
            oom();
        }
        alloc_cost_++;

        *parent = heap_;
        heap_ = (MemoryChunk){.parent = parent};

        heap_level_++;
    }

    void leave_region() {
        // fprintf(stderr, "debug: leave_region level=%d size=%d\n",
        // s_heap_level, heap_size_);

        assert(heap_.parent != NULL);
        MemoryChunk *parent = heap_.parent;

        // free current region
        {
            if (heap_.ptr != NULL) {
                free_chunk(&heap_);
            }

            // other than heap_, chunk itself needs to be freed
            MemoryChunk *chunk = heap_.used;
            while (chunk) {
                MemoryChunk *current = chunk;
                chunk = current->used;

                free_chunk(current);
                free(current);
            }

            heap_ = *parent;
            free(parent);
        }

        assert(heap_level_ > 0);
        heap_level_--;

        // fprintf(stderr, "debug: free level=%d size=%d\n", s_heap_level,
        // heap_size_);
    }

    // allocate new chunk
    void *alloc_slow(size_t total) {
        size_t cap = heap_.cap;

        // move current chunk to used list
        if (heap_.ptr != NULL) {
            MemoryChunk *used = (MemoryChunk *)calloc(1, sizeof(MemoryChunk));
            if (used == NULL) {
                oom();
            }
            alloc_cost_++;

            *used = heap_;
            heap_.used = used;
        }

        // grow exponentially
        cap *= 2;
        if (cap < total) {
            cap = total;
        }

        // initialize chunk
        void *ptr = calloc(1, cap);
        if (ptr == NULL) {
            oom();
        }
        alloc_cost_++;
        heap_.ptr = ptr;
        heap_.len = total;
        heap_.cap = cap;

        heap_size_ += total;
        heap_alloc_ += cap;

        // fprintf(stderr, "debug: alloc level=%d size=%d  new chunk(h=%d
        // cap=%d)\n", s_heap_level, (int)size, h, (int)cap);
        return ptr;
    }

    void *alloc(int count, size_t size) {
        assert(count > 0 && size > 0);

        size_t total = (size_t)count * size;

        // align to 16x
        total = (total + 0xf) & ~0xf;
        assert(total % 16 == 0 && total >= (size_t)count * size);

        if (heap_.len + total > heap_.cap) {
            return alloc_slow(total);
        }

        // use current chunk
        void *ptr = (char *)heap_.ptr + heap_.len;
        heap_.len += total;
        heap_size_ += total;
        alloc_cost_++;

        // fprintf(stderr, "debug: alloc level=%d size=%d (%dx%d)\n",
        // s_heap_level, (int)((size_t)count * size), (int)count, (int)size);
        return ptr;
    }
};

// -----------------------------------------------
// Runtime API
// -----------------------------------------------

static struct tbb::combinable<MemoryPool> s_heap {};

extern "C" size_t milone_mem_heap_size(void) {
    size_t total = 0;
    s_heap.combine_each(
        [&total](MemoryPool &pool) { total += pool.heap_size(); });
    return total;
}

extern "C" size_t milone_mem_alloc_cost(void) {
    size_t total = 0;
    s_heap.combine_each(
        [&total](MemoryPool &pool) { total += pool.alloc_cost(); });
    return total;
}

extern "C" void milone_enter_region(void) { s_heap.local().enter_region(); }

extern "C" void milone_leave_region(void) { s_heap.local().leave_region(); }

extern "C" void *milone_mem_alloc(int count, size_t size) {
    void *p = s_heap.local().alloc(count, size);
    // fprintf(stderr, "alloc %d x %d -> %p\n", count, (int)size, p);
    return p;
}
