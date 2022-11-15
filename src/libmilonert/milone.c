// Runtime code for C programs generated by the milone-lang compiler.

// Some of functions are not declared in milone.h
// but usable with __nativeFun.

// Use C standard functions only.
// Other functions that require platform-specific functions are defined in
// `milone_platform.c`.

// Customization:
//      Define MILONE_NO_DEFAULT_ALLOCATOR to disable memory allocator API.

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <milone.h>

#if defined(_MSC_VER) // On Windows MSVC
#define THREAD_LOCAL __declspec(thread)
#else
#define THREAD_LOCAL _Thread_local
#endif

// Max size of allocation.
static uint32_t const LIMIT = 1U << 31;

// -----------------------------------------------
// runtime error
// -----------------------------------------------

_Noreturn void milone_abort(char const *name, char const *filename, int32_t row,
                            int32_t column) {
    fflush(stdout);
    fprintf(stderr, "milone: %s: %s:%d:%d\n", name, filename, row + 1,
            column + 1);
    abort();
}

_Noreturn void milone_failwith(char const *msg) {
    fprintf(stderr, "milone: Runtime Error: %s\n", msg);
    abort();
}

_Noreturn void milone_failwithf(char const *fmt, ...) {
    va_list va;
    va_start(va, fmt);
    fprintf(stderr, "milone: Runtime Error: ");
    vfprintf(stderr, fmt, va);
    fprintf(stderr, "\n");
    va_end(va);
    abort();
}

// -----------------------------------------------
// memory management (memory pool)
// -----------------------------------------------

size_t milone_heap_size(void);
size_t milone_alloc_cost(void);

typedef void (*DeferFunPtr)(void const *env);

struct DeferChain {
  DeferFunPtr fun;
  void const *env;
  struct DeferChain *parent;
};

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
    struct MemoryChunk *used;

    // parent region or null
    // each region is allocated by calloc and should be freed after leaving
    // region
    struct MemoryChunk *parent;

    struct DeferChain *defer_chain;
};

THREAD_LOCAL struct MemoryChunk s_heap;
THREAD_LOCAL size_t s_heap_level; // depth of current region
THREAD_LOCAL size_t s_heap_size;  // consumed size in all regions
THREAD_LOCAL size_t s_heap_alloc; // allocated size in all regions
THREAD_LOCAL size_t s_alloc_cost; // allocation count

_Noreturn static void oom(void) { milone_failwith("Out of memory"); }

// free chunk itself, not used list
static void free_chunk(struct MemoryChunk *chunk) {
    assert(chunk != NULL);
    assert(chunk->ptr != NULL);

    free(chunk->ptr);
    s_heap_size -= chunk->len;
    s_heap_alloc -= chunk->cap;
}

static void do_region_enter(void) {
    // fprintf(stderr, "debug: enter_region level=%d size=%d\n", s_heap_level +
    // 1, s_heap_size);

    struct MemoryChunk *parent = calloc(1, sizeof(struct MemoryChunk));
    if (parent == NULL) {
        oom();
    }
    s_alloc_cost++;

    *parent = s_heap;
    s_heap = (struct MemoryChunk){.parent = parent};

    s_heap_level++;
}

static void do_region_leave(void) {
    // fprintf(stderr, "debug: leave_region level=%d size=%d\n", s_heap_level,
    // s_heap_size);

    assert(s_heap.parent != NULL);
    struct MemoryChunk *parent = s_heap.parent;

    // free resources
    {
        struct DeferChain *chain = s_heap.defer_chain;
        s_heap.defer_chain = NULL;

        while (chain != NULL) {
            struct DeferChain *parent = chain->parent;
            chain->fun(chain->env);
            free(chain);
            s_heap_size -= sizeof(struct DeferChain);
            chain = parent;
        }
    }

    // free current region
    {
        if (s_heap.ptr != NULL) {
            free_chunk(&s_heap);
        }

        // other than s_heap, chunk itself needs to be freed
        struct MemoryChunk *chunk = s_heap.used;
        while (chunk) {
            struct MemoryChunk *current = chunk;
            chunk = current->used;

            free_chunk(current);
            free(current);
        }

        s_heap = *parent;
        free(parent);
    }

    assert(s_heap_level > 0);
    s_heap_level--;

    // fprintf(stderr, "debug: free level=%d size=%d\n", s_heap_level,
    // s_heap_size);
}

// allocate new chunk
static void *do_region_alloc_slow(size_t total) {
    size_t cap = s_heap.cap;

    // move current chunk to used list
    if (s_heap.ptr != NULL) {
        struct MemoryChunk *used = calloc(1, sizeof(struct MemoryChunk));
        if (used == NULL) {
            oom();
        }
        s_alloc_cost++;

        *used = s_heap;
        s_heap.used = used;
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
    s_alloc_cost++;
    s_heap.ptr = ptr;
    s_heap.len = total;
    s_heap.cap = cap;

    s_heap_size += total;
    s_heap_alloc += cap;

    // fprintf(stderr, "debug: alloc level=%d size=%d  new chunk(h=%d
    // cap=%d)\n", s_heap_level, (int)size, h, (int)cap);
    return ptr;
}

static void *do_region_alloc(uint32_t count, uint32_t size) {
    assert(count != 0 && size != 0);

    // Allocation size limit: count * size < LIMIT
    if (count >= LIMIT / size) {
        oom();
    }

    size_t total = (size_t)count * size;

    // align to 16x
    total = (total + 0xf) & ~0xf;
    assert(total % 16 == 0 && total >= (size_t)count * size);

    if (total > s_heap.cap - s_heap.len) {
        return do_region_alloc_slow(total);
    }

    // use current chunk
    void *ptr = (char *)s_heap.ptr + s_heap.len;
    s_heap.len += total;
    s_heap_size += total;
    s_alloc_cost++;

    // fprintf(stderr, "debug: alloc level=%d size=%d (%dx%d)\n", s_heap_level,
    // (int)((size_t)count * size), (int)count, (int)size);
    return ptr;
}

static void do_region_defer(DeferFunPtr fun, void const *env) {
    s_heap_alloc++;
    s_heap_size += sizeof(struct DeferChain);
    struct DeferChain *chain = calloc(1, sizeof(struct DeferChain));
    if (chain == NULL) {
        oom();
    }
    chain->fun = fun;
    chain->env = env;
    chain->parent = s_heap.defer_chain;
    s_heap.defer_chain = chain;
}

#ifndef MILONE_NO_DEFAULT_ALLOCATOR

size_t milone_heap_size(void) { return s_heap_size; }
size_t milone_alloc_cost(void) { return s_alloc_cost; }

void milone_region_enter(void) { do_region_enter(); }
void milone_region_leave(void) { do_region_leave(); }

void *milone_region_alloc(uint32_t count, uint32_t size) {
    return do_region_alloc(count, size);
}

void milone_region_defer(DeferFunPtr fun, void const *env) { do_region_defer(fun, env); }

#endif // MILONE_NO_DEFAULT_ALLOCATOR

// -----------------------------------------------
// int
// -----------------------------------------------

int milone_int32_compare(int32_t l, int32_t r) {
    // if l < r: 0 - 1
    // if l == r: 0 - 0
    // if l > r: 1 - 0
    return (r < l) - (l < r);
}

int milone_int64_compare(int64_t l, int64_t r) {
    return (r < l) - (l < r);
}

int milone_uint64_compare(uint64_t l, uint64_t r) {
    return (r < l) - (l < r);
}

static uint32_t uint32_min(uint32_t l, uint32_t r) {
    return r < l ? r : l;
}

static int uint32_compare(uint32_t l, uint32_t r) {
    return (r < l) - (l < r);
}

// -----------------------------------------------
// string
// -----------------------------------------------

struct StringBuilder {
    char *buf;
    uint32_t len;
    uint32_t cap;
};

static struct StringBuilder *string_builder_new_with_capacity(uint32_t cap) {
    struct StringBuilder *sb =
        milone_region_alloc(1, sizeof(struct StringBuilder));
    *sb = (struct StringBuilder){
        .buf = cap > 0 ? milone_region_alloc(cap, sizeof(char)) : "",
        .len = 0,
        .cap = cap,
    };
    return sb;
}

static void string_builder_grow(struct StringBuilder *sb, uint32_t addition) {
    // Addition must be larger than unused space.
    assert(addition >= sb->cap - sb->len);
    if (addition >= LIMIT - sb->cap) oom();

    // grow exponentially
    sb->cap *= 2;

    // +1 for final null byte.
    uint32_t min_len = sb->len + addition + 1;
    if (sb->cap < min_len) {
        sb->cap = min_len;
    }

    char *buf = milone_region_alloc(sb->cap, sizeof(char));
    memcpy(buf, sb->buf, sb->len);
    sb->buf = buf;

    assert(sb->len < sb->cap);
    assert(sb->buf[sb->cap - 1] == '\0');
}

static void string_builder_append_string(struct StringBuilder *sb,
                                         struct String value) {
    if (value.len >= sb->cap - sb->len) {
        string_builder_grow(sb, value.len);
    }

    memcpy(&sb->buf[sb->len], value.ptr, value.len);
    sb->len += value.len;

    assert(sb->len < sb->cap);
    assert(sb->buf[sb->cap - 1] == '\0');
}

struct String string_borrow(char const *c_str) {
    assert(c_str != NULL);
    return (struct String){.ptr = c_str, .len = (uint32_t)strlen(c_str)};
}

int string_compare(struct String left, struct String right) {
    // Compare prefix part of two strings.
    uint32_t min_len = uint32_min(left.len, right.len);
    int c = memcmp(left.ptr, right.ptr, min_len);
    if (c != 0) {
        return c;
    }

    // One is prefix of the other here, and therefore, longer is greater.
    return uint32_compare(left.len, right.len);
}

struct String string_of_raw_parts(char const *p, uint32_t len) {
    assert(p != NULL);

    if (len == 0) return string_borrow("");
    if (len >= LIMIT - 1) oom();

    // +1 for the invariant of existence of null byte.
    char *buf = milone_region_alloc(len + 1, sizeof(char));
    memcpy(buf, p, len * sizeof(char));
    assert(buf[len] == '\0');
    return (struct String){.ptr = buf, .len = len};
}

struct String string_of_c_str(char const *s) {
    assert(s != NULL);
    return string_of_raw_parts(s, (uint32_t)strlen(s));
}

struct String string_add(struct String left, struct String right) {
    if (left.len == 0 || right.len == 0) {
        return right.len == 0 ? left : right;
    }

    // Length limit: |l| + |r| < LIMIT
    if (right.len >= LIMIT - left.len) {
        milone_failwith("str_add: Length overflow");
    }

    uint32_t len = left.len + right.len;
    char *buf = milone_region_alloc(len + 1, sizeof(char));
    memcpy(buf, left.ptr, left.len);
    memcpy(buf + left.len, right.ptr, right.len);
    assert(buf[len] == '\0');
    return (struct String){.ptr = buf, .len = len};
}

struct String string_slice(struct String s, int32_t l, int32_t r) {
    if (l < 0) l = 0;
    if (r < 0) r = 0;
    uint32_t ur = uint32_min((uint32_t)r, s.len);
    uint32_t ul = uint32_min((uint32_t)l, (uint32_t)r);
    assert(ul <= ur && ur <= s.len);
    return (struct String){.ptr = s.ptr + ul, .len = ur - ul};
}

struct String string_ensure_null_terminated(struct String s) {
    // The dereference is safe due to the invariant of existence of null byte.
    if (s.ptr[s.len] != '\0') {
        s = string_of_raw_parts(s.ptr, s.len);
    }

    assert(s.ptr[s.len] == '\0');
    return s;
}

char const *string_to_c_str(struct String s) {
    return string_ensure_null_terminated(s).ptr;
}

static bool string_is_all_spaces(char const *begin, char const *end) {
    char const *p = begin;
    while (p != end && *p != 0 && isspace(*p)) {
        p++;
    }
    return p == end;
}

// type_name: name of a number type in milone-lang
static void verify_str_to_number(const char *type_name, bool ok) {
    if (!ok) {
        milone_failwithf("%s: Failed to convert from a string", type_name);
    }
}

bool string_to_int64_checked(struct String s, int64_t *value_ptr) {
    s = string_ensure_null_terminated(s);
    char *endptr = (char *)(s.ptr + s.len);
    long long value = strtoll(s.ptr, &endptr, 10);
    *value_ptr = (int64_t)value;
    return endptr != s.ptr && string_is_all_spaces(endptr, s.ptr + s.len) &&
           errno != ERANGE;
}

bool string_to_uint64_checked(struct String s, uint64_t *value_ptr) {
    s = string_ensure_null_terminated(s);
    char *endptr = (char *)(s.ptr + s.len);
    unsigned long long value = strtoull(s.ptr, &endptr, 10);
    *value_ptr = (uint64_t)value;
    return endptr != s.ptr && string_is_all_spaces(endptr, s.ptr + s.len) &&
           errno != ERANGE;
}

double string_to_float64(struct String s) {
    s = string_ensure_null_terminated(s);
    char *endptr = (char *)(s.ptr + s.len);
    double value = strtod(s.ptr, &endptr);
    bool ok = endptr != s.ptr && string_is_all_spaces(endptr, s.ptr + s.len) &&
              errno != ERANGE;
    verify_str_to_number("float", ok);
    return value;
}

bool string_to_int32_checked(struct String s, int32_t *value_ptr) {
    int64_t value;
    bool ok = string_to_int64_checked(s, &value);
    if (!(ok && INT32_MIN <= value && value <= INT32_MAX)) {
        *value_ptr = 0;
        return false;
    }

    *value_ptr = (int32_t)value;
    return true;
}

int8_t string_to_int8(struct String s) {
    int64_t value;
    bool ok = string_to_int64_checked(s, &value);
    verify_str_to_number("int8", ok && INT8_MIN <= value && value <= INT8_MAX);
    return (int8_t)value;
}

int16_t string_to_int16(struct String s) {
    int64_t value;
    bool ok = string_to_int64_checked(s, &value);
    verify_str_to_number("int16",
                         ok && INT16_MIN <= value && value <= INT16_MAX);
    return (int16_t)value;
}

int32_t string_to_int32(struct String s) {
    int32_t value;
    bool ok = string_to_int32_checked(s, &value);
    verify_str_to_number("int", ok);
    return value;
}

int64_t string_to_int64(struct String s) {
    int64_t value;
    bool ok = string_to_int64_checked(s, &value);
    verify_str_to_number("int64", ok);
    return value;
}

intptr_t string_to_nativeint(struct String s) { return (intptr_t)string_to_int64(s); }

uint8_t string_to_uint8(struct String s) {
    uint64_t value;
    bool ok = string_to_uint64_checked(s, &value);
    verify_str_to_number("uint8", ok && value <= UINT8_MAX);
    return (uint8_t)value;
}

uint16_t string_to_uint16(struct String s) {
    uint64_t value;
    bool ok = string_to_uint64_checked(s, &value);
    verify_str_to_number("uint16", ok && value <= UINT16_MAX);
    return (uint16_t)value;
}

uint32_t string_to_uint32(struct String s) {
    uint64_t value;
    bool ok = string_to_uint64_checked(s, &value);
    verify_str_to_number("uint", ok && value <= UINT32_MAX);
    return (uint32_t)value;
}

uint64_t string_to_uint64(struct String s) {
    uint64_t value;
    bool ok = string_to_uint64_checked(s, &value);
    verify_str_to_number("uint64", ok);
    return value;
}

uintptr_t string_to_unativeint(struct String s) {
    return (uintptr_t)string_to_uint64(s);
}

struct String string_of_int64(int64_t value) {
    char buf[21] = {0};
    int n = sprintf(buf, "%lld", (long long)value);
    return string_of_raw_parts(buf, n);
}

struct String string_of_uint64(uint64_t value) {
    char buf[21] = {0};
    int n = sprintf(buf, "%llu", (unsigned long long)value);
    return string_of_raw_parts(buf, n);
}

struct String string_of_float64(double value) {
    char buf[64] = {0};
    int n = sprintf(buf, "%f", value);
    return string_of_raw_parts(buf, n);
}

struct String string_of_bool(bool value) {
    return value ? string_borrow("True") : string_borrow("False");
}

char string_to_char(struct String s) { return s.len >= 1 ? *s.ptr : '\0'; }

struct String string_of_char(char value) {
    if (value == '\0') {
        return string_borrow("");
    }

    char *buf = milone_region_alloc(2, sizeof(char));
    buf[0] = value;
    return (struct String){.ptr = buf, .len = 1};
}

struct MyStringCons {
    struct String head;
    struct MyStringCons const *tail;
};

struct String string_concat(struct String sep, struct StringCons const *strings) {
    struct MyStringCons const *ss = (struct MyStringCons const *)strings;

    struct StringBuilder *sb = string_builder_new_with_capacity(0x1000);
    bool first = true;

    while (ss) {
        struct String head = ss->head;
        ss = ss->tail;

        if (!first && sep.len >= 1) {
            string_builder_append_string(sb, sep);
        }
        first = false;

        string_builder_append_string(sb, head);
    }

    // #sb_finish
    // Null termination. Technically unnecessary but can skip some cloning.
    assert(sb->len < sb->cap);
    sb->buf[sb->len] = '\0';

    return (struct String){.ptr = sb->buf, .len = sb->len};
}

// -----------------------------------------------
// file IO
// -----------------------------------------------

int file_exists(struct String file_name) {
    file_name = string_ensure_null_terminated(file_name);

    bool ok = false;

    FILE *fp = fopen(file_name.ptr, "r");
    if (fp) {
        ok = true;
        fclose(fp);
    }

    return ok;
}

struct String file_read_all_text(struct String file_name) {
    file_name = string_ensure_null_terminated(file_name);

    FILE *fp = fopen(file_name.ptr, "rb");
    if (!fp) {
        perror("fopen");
        fprintf(stderr, "File '%s' not found.", file_name.ptr);
        goto FAIL;
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    if (size < 0) {
        perror("ftell");
        goto FAIL;
    }
    if ((size_t)size >= LIMIT) {
        fprintf(stderr, "%s", "File size is too large.\n");
        goto FAIL;
    }
    fseek(fp, 0, SEEK_SET);

    char *content = milone_region_alloc((uint32_t)size + 1, sizeof(char));
    size_t read_size = fread(content, 1, (size_t)size, fp);
    if (read_size != (size_t)size) {
        perror("fread");
        goto FAIL;
    }

    fclose(fp);
    return (struct String){.ptr = content, .len = (uint32_t)size};

FAIL:
    if (fp)
        fclose(fp);

    milone_failwith("file_read_all_text");
}

void file_write_all_text(struct String file_name, struct String content) {
    file_name = string_ensure_null_terminated(file_name);

    FILE *fp = NULL;

    // Skip writing if unchanged.
    {
        fp = fopen(file_name.ptr, "rb");
        if (fp) {
            fseek(fp, 0, SEEK_END);
            long size = ftell(fp);
            fseek(fp, 0, SEEK_SET);

            if (size >= 0 && (size_t)size == (size_t)content.len) {
                char *old_content = calloc((uint32_t)size + 1, sizeof(char));
                if (old_content == NULL) {
                    oom();
                }
                size_t read_len =
                    fread(old_content, sizeof(char), (size_t)size, fp);
                bool same = read_len == (size_t)size &&
                            memcmp(old_content, content.ptr, read_len) == 0;
                free(old_content);

                if (same) {
                    goto END;
                }
            }
            fclose(fp);
            fp = NULL;
        }
    }

    fp = fopen(file_name.ptr, "wb+");
    if (!fp) {
        perror("fopen(wb+)");
        milone_failwith("file_write_all_text");
    }

    bool ok = fwrite(content.ptr, sizeof(char), (size_t)content.len, fp) ==
              (size_t)content.len;
    if (!ok) {
        perror("fwrite");
        fclose(fp);
        milone_failwith("file_write_all_text");
    }

END:
    fclose(fp);
}

struct String milone_read_stdin_all(void) {
    char buf[0x1000] = "";
    struct StringBuilder *sb = string_builder_new_with_capacity(sizeof buf);

    while (true) {
        if (sb->cap > 10100100) {
            milone_failwith("milone_read_stdin_all: stdin too long");
        }

        size_t read_len = fread(buf, 1, sizeof buf, stdin);
        if (read_len == 0)
            break;

        string_builder_append_string(
            sb, (struct String){.ptr = buf, .len = (uint32_t)read_len});
    }

    // #sb_finish
    // Null termination. Technically unnecessary but can skip some cloning.
    assert(sb->len < sb->cap);
    sb->buf[sb->len] = '\0';

    return (struct String){.ptr = sb->buf, .len = sb->len};
}

// -----------------------------------------------
// environment
// -----------------------------------------------

struct String milone_get_env(struct String name) {
    name = string_ensure_null_terminated(name);

    char const *value = getenv(name.ptr);
    if (value == NULL) {
        return string_borrow("");
    }

    return string_of_c_str(value);
}

// -----------------------------------------------
// profiling
// -----------------------------------------------

static long milone_get_time_millis(void) {
    struct timespec t;
    (void)timespec_get(&t, TIME_UTC);
    return (long)(t.tv_sec * 1000L + t.tv_nsec / (1000L * 1000L));
}

static void thousand_sep(long value, char *buf, size_t buf_size) {
    assert(buf_size >= 14);

    bool neg = value < 0;
    if (neg)
        value = -value;

    long kilo = value / 1000;
    value %= 1000;

    long mega = kilo / 1000;
    kilo %= 1000;

    size_t written = snprintf(buf, buf_size, "%3u,%03u,%03u", (uint32_t)mega,
                              (uint32_t)kilo, (uint32_t)value);
    assert(written < buf_size);
}

struct Profiler {
    struct String msg;
    long start_epoch;
    long epoch;
    size_t heap_size;
    size_t alloc_cost;
};

void *milone_profile_init(void) {
    struct Profiler *p = milone_region_alloc(1, sizeof(struct Profiler));
    p->msg = string_borrow("start");
    p->epoch = milone_get_time_millis();
    p->start_epoch = p->epoch;
    p->heap_size = milone_heap_size();
    p->alloc_cost = milone_alloc_cost();
    return p;
}

static void milone_profile_print_log(struct String msg, long millis,
                                     long mem_bytes, long alloc_cost) {
    msg = string_ensure_null_terminated(msg);

    if (millis < 0) {
        millis = 0;
    }
    long sec = millis / 1000;
    millis %= 1000;
    millis /= 10; // 10 ms

    char mem[16];
    thousand_sep(mem_bytes, mem, sizeof(mem));

    char cost[16];
    thousand_sep(alloc_cost, cost, sizeof(cost));

    fprintf(stderr, "profile: %-17s time=%4d.%02d mem=%s cost=%s\n", msg.ptr,
            (int)sec, (int)millis, mem, cost);
}

void milone_profile_log(struct String msg, void *profiler) {
    struct Profiler *p = (struct Profiler *)profiler;

    long t = milone_get_time_millis();
    long heap_size = (long)milone_heap_size();
    long alloc_cost = (long)milone_alloc_cost();

    long time_delta = t - p->epoch;
    long mem_delta = heap_size - (long)p->heap_size;
    long alloc_delta = alloc_cost - (long)p->alloc_cost;

    milone_profile_print_log(p->msg, time_delta, mem_delta, alloc_delta);

    p->msg = msg;
    p->epoch = t;
    p->heap_size = heap_size;
    p->alloc_cost = alloc_cost;

    if (string_compare(msg, string_borrow("Finish")) == 0) {
        fprintf(stderr, "profile: Finish\n");
        long millis = t - p->start_epoch;
        milone_profile_print_log(string_borrow("total"), millis, heap_size,
                                 alloc_cost);
    }
}

// -----------------------------------------------
// Runtime Entrypoint
// -----------------------------------------------

static int32_t s_argc;
static char **s_argv;

int32_t milone_get_arg_count(void) { return s_argc; }

struct String milone_get_arg(int32_t index) {
    if ((uint32_t)index >= (uint32_t)s_argc) {
        return string_borrow("");
    }

    return string_borrow(s_argv[index]);
}

void milone_start(int argc, char **argv) {
    s_argc = argc;
    s_argv = argv;
}
