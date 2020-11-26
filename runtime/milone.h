// Runtime code for C programs generated by the milone-lang compiler.

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// null-terminated string
struct String {
    char *str;
    int len;
};

// -----------------------------------------------
// memory management (memory pool)
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
    struct MemoryChunk *used;

    // parent region or null
    // each region is allocated by calloc and should be freed after leaving
    // region
    struct MemoryChunk *parent;
};

static struct MemoryChunk s_heap;
static int s_heap_level; // depth of current region
static int s_heap_size;  // consumed size in all regions
static int s_heap_alloc; // allocated size in all regions

static void oom(void) {
    fprintf(stderr, "Out of memory.\n");
    exit(1);
}

// free chunk itself, not used list
static void free_chunk(struct MemoryChunk *chunk) {
    assert(chunk != NULL);
    assert(chunk->ptr != NULL);

    free(chunk->ptr);
    s_heap_size -= chunk->len;
    s_heap_alloc -= chunk->cap;
}

void milone_enter_region(void) {
    // fprintf(stderr, "debug: enter_region level=%d size=%d\n", s_heap_level +
    // 1, s_heap_size);

    struct MemoryChunk *parent = calloc(1, sizeof(struct MemoryChunk));
    if (parent == NULL) {
        oom();
    }

    *parent = s_heap;
    s_heap = (struct MemoryChunk){.parent = parent};

    s_heap_level++;
}

void milone_leave_region(void) {
    // fprintf(stderr, "debug: leave_region level=%d size=%d\n", s_heap_level,
    // s_heap_size);

    assert(s_heap.parent != NULL);
    struct MemoryChunk *parent = s_heap.parent;

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
static void *milone_mem_alloc_slow(size_t total) {
    size_t cap = s_heap.cap;

    // move current chunk to used list
    if (s_heap.ptr != NULL) {
        struct MemoryChunk *used = calloc(1, sizeof(struct MemoryChunk));
        if (used == NULL) {
            oom();
        }

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
    s_heap.ptr = ptr;
    s_heap.len = total;
    s_heap.cap = cap;

    s_heap_size += total;
    s_heap_alloc += cap;

    // fprintf(stderr, "debug: alloc level=%d size=%d  new chunk(h=%d
    // cap=%d)\n", s_heap_level, (int)size, h, (int)cap);
    return ptr;
}

void *milone_mem_alloc(int count, size_t size) {
    assert(count > 0 && size > 0);

    size_t total = (size_t)count * size;
    if (s_heap.len + total > s_heap.cap) {
        return milone_mem_alloc_slow(total);
    }

    // use current chunk
    void *ptr = (char *)s_heap.ptr + s_heap.len;
    s_heap.len += total;
    s_heap_size += total;

    // fprintf(stderr, "debug: alloc level=%d size=%d (%dx%d)\n", s_heap_level,
    // (int)((size_t)count * size), (int)count, (int)size);
    return ptr;
}

// -----------------------------------------------
// int
// -----------------------------------------------

int int_cmp(int l, int r) {
    if (l == r)
        return 0;
    if (l < r)
        return -1;
    return 1;
}

int int_clamp(int x, int l, int r) {
    if (x < l)
        return l;
    if (x > r)
        return r;
    return x;
}

// -----------------------------------------------
// str
// -----------------------------------------------

struct StringBuilder {
    char *buf;
    int len;
    int cap;
};

static struct StringBuilder *string_builder_new_with_capacity(int cap) {
    assert(cap >= 0);

    struct StringBuilder *sb =
        milone_mem_alloc(1, sizeof(struct StringBuilder));
    *sb = (struct StringBuilder){
        .buf = cap > 0 ? milone_mem_alloc(cap, sizeof(char)) : "",
        .len = 0,
        .cap = cap,
    };
    return sb;
}

static void string_builder_grow(struct StringBuilder *sb, int addition) {
    assert(addition >= 0);
    assert(sb->len + addition >= sb->cap);

    // grow exponentially
    sb->cap *= 2;

    int min_len = sb->len + addition + 1;
    if (sb->cap < min_len) {
        sb->cap = min_len;
    }

    char *buf = milone_mem_alloc(sb->cap, sizeof(char));
    memcpy(buf, sb->buf, sb->len);
    sb->buf = buf;

    assert(sb->len < sb->cap);
    sb->buf[sb->len] = '\0';
}

static void string_builder_append_string(struct StringBuilder *sb,
                                         struct String value) {
    if (sb->len + value.len >= sb->cap) {
        string_builder_grow(sb, value.len);
    }

    memcpy(&sb->buf[sb->len], value.str, value.len + 1);
    sb->len += value.len;
    assert(sb->buf[sb->len] == '\0');
}

int str_cmp(struct String left, struct String right) {
    int min_len = int_clamp(left.len, 0, right.len);
    return memcmp(left.str, right.str, min_len + 1);
}

/// Create a string from a slice of native C string.
struct String str_of_raw_parts(char const *p, int len) {
    if (len <= 0) {
        if (len < 0) {
            fprintf(stderr, "FATAL: Negative string length (%d).\n", len);
            abort();
        }

        return (struct String){.str = "", .len = 0};
    }

    char *str = (char *)milone_mem_alloc(len + 1, sizeof(char));
    memcpy(str, p, len * sizeof(char));
    str[len] = '\0';
    return (struct String){.str = str, .len = len};
}

struct String str_add(struct String left, struct String right) {
    if (left.len == 0 || right.len == 0) {
        return right.len == 0 ? left : right;
    }
    int len = left.len + right.len;
    char *str = (char *)milone_mem_alloc(len + 1, sizeof(char));
    memcpy(str, left.str, left.len);
    memcpy(str + left.len, right.str, right.len);
    assert(str[len] == '\0');
    return (struct String){.str = str, .len = len};
}

struct String str_get_slice(int l, int r, struct String s) {
    l = int_clamp(l, 0, s.len);
    r = int_clamp(r + 1, l, s.len);
    int len = r - l;
    char *str;
    if (r == s.len) {
        str = s.str + l;
    } else {
        str = (char *)milone_mem_alloc(len + 1, sizeof(char));
        memcpy(str, s.str + l, len);
    }
    assert(str[len] == '\0');
    return (struct String){.str = str, .len = len};
}

static void verify_str_to_int(const char *int_type_name, const char *endptr, int range_check) {
    if (!range_check || (*endptr != '\0' && !isspace(*endptr)) || errno == ERANGE) {
        fprintf(stderr, "FATAL: Failed to convert a string to %s.\n", int_type_name);
        exit(1);
    }
}

int8_t str_to_int8(struct String s) {
    char *endptr = s.str + s.len;
    int n = strtol(s.str, &endptr, 10);
    verify_str_to_int("int8_t", endptr,INT8_MIN <= n && n <= INT8_MAX);
    return (int8_t)n;
}

int16_t str_to_int16(struct String s) {
    char *endptr = s.str + s.len;
    int n = strtol(s.str, &endptr, 10);
    verify_str_to_int("int16_t", endptr, INT16_MIN <= n && n <= INT16_MAX);
    return (int16_t)n;
}

int str_to_int(struct String s) {
    char *endptr = s.str + s.len;
    int n = strtol(s.str, &endptr, 10);
    verify_str_to_int("int", endptr, 1);
    return n;
}

int64_t str_to_int64(struct String s) {
    char *endptr = s.str + s.len;
    int64_t n = strtoll(s.str, &endptr, 10);
    verify_str_to_int("int64_t", endptr, 1);
    return n;
}

intptr_t str_to_intptr(struct String s) {
    char *endptr = s.str + s.len;
    int64_t n = strtoll(s.str, &endptr, 10);
    verify_str_to_int("intptr_t", endptr, 1);
    return (intptr_t)n;
}

uint8_t str_to_uint8(struct String s) {
    char *endptr = s.str + s.len;
    uint32_t n = strtoul(s.str, &endptr, 10);
    verify_str_to_int("uint8_t", endptr, n <= UINT8_MAX);
    return (uint8_t)n;
}

uint16_t str_to_uint16(struct String s) {
    char *endptr = s.str + s.len;
    uint32_t n = strtoul(s.str, &endptr, 10);
    verify_str_to_int("uint16_t", endptr, n <= UINT16_MAX);
    return (uint16_t)n;
}

uint32_t str_to_uint32(struct String s) {
    char *endptr = s.str + s.len;
    uint32_t n = strtoul(s.str, &endptr, 10);
    verify_str_to_int("uint32_t", endptr, 1);
    return n;
}

uint64_t str_to_uint64(struct String s) {
    char *endptr = s.str + s.len;
    uint64_t n = strtoull(s.str, &endptr, 10);
    verify_str_to_int("uint64_t", endptr, 1);
    return n;
}

uintptr_t str_to_uintptr(struct String s) {
    char *endptr = s.str + s.len;
    uint64_t n = strtoull(s.str, &endptr, 10);
    verify_str_to_int("uintptr_t", endptr, 1);
    return n;
}

struct String str_of_int64(int64_t value) {
    char buf[21] = {};
    int n = sprintf(buf, "%ld", value);
    return str_of_raw_parts(buf, n);
}

struct String str_of_uint64(uint64_t value) {
    char buf[21] = {};
    int n = sprintf(buf, "%lu", value);
    return str_of_raw_parts(buf, n);
}

struct String str_of_char(char value) {
    char *str = (char *)milone_mem_alloc(2, sizeof(char));
    str[0] = value;
    return (struct String){.str = str, .len = strlen(str)};
}

// Actual name of string list.
struct StringList;

struct MyStringList {
    struct String head;
    struct MyStringList *tail;
};

struct String str_concat(struct String sep, struct StringList *strings) {
    struct MyStringList *ss = (struct MyStringList *)strings;

    struct StringBuilder *sb = string_builder_new_with_capacity(0x1000);
    int first = 1;

    while (ss) {
        struct String head = ss->head;
        ss = ss->tail;

        if (!first && sep.len > 0) {
            string_builder_append_string(sb, sep);
        }
        first = 0;

        string_builder_append_string(sb, head);
    }

    return str_of_raw_parts(sb->buf, sb->len);
}

// -----------------------------------------------
// assertion
// -----------------------------------------------

void milone_assert(int cond, int y, int x) {
    if (!cond) {
        fprintf(stderr, "Assertion failed at (%d, %d)\n", y + 1, x + 1);
        exit(1);
    }
}

// -----------------------------------------------
// file IO
// -----------------------------------------------

int file_exists(struct String file_name) {
    int ok = 0;

    FILE *fp = fopen(file_name.str, "r");
    if (fp) {
        ok = 1;
        fclose(fp);
    }

    return ok;
}

struct String file_read_all_text(struct String file_name) {
    FILE *fp = fopen(file_name.str, "r");
    if (!fp) {
        fprintf(stderr, "File '%s' not found.", file_name.str);
        abort();
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    if (size < 0) {
        fclose(fp);
        fprintf(stderr, "%s", "Couldn't retrieve the file size.");
        abort();
    }
    fseek(fp, 0, SEEK_SET);

    char *content = (char *)milone_mem_alloc((size_t)size + 1, sizeof(char));
    size_t read_size = fread(content, 1, (size_t)size, fp);
    if (read_size != (size_t)size) {
        fclose(fp);
        fprintf(stderr, "%s", "Couldn't retrieve the file contents");
        abort();
    }

    fclose(fp);
    return (struct String){.str = content, .len = size};
}

void file_write_all_text(struct String file_name, struct String content) {
    FILE *fp = fopen(file_name.str, "w");
    if (!fp) {
        fprintf(stderr, "File '%s' not found.", file_name.str);
        abort();
    }

    fprintf(fp, "%s", content.str);

    fclose(fp);
}

struct String milone_get_env(struct String name) {
    char const *value = getenv(name.str);
    if (value == NULL) {
        return (struct String){.str = "", .len = 0};
    }

    return str_of_raw_parts(value, strlen(value));
}

// -----------------------------------------------
// profiling
// -----------------------------------------------

long milone_get_time_millis(void) {
    struct timespec t;
    timespec_get(&t, TIME_UTC);
    return t.tv_sec * 1000L + t.tv_nsec / (1000L * 1000L);
}

struct Profiler {
    long epoch;
    long heap_size;
};

void *milone_profile_init(void) {
    struct Profiler *p =
        (struct Profiler *)milone_mem_alloc(1, sizeof(struct Profiler));
    p->epoch = milone_get_time_millis();
    p->heap_size = s_heap_size;
    return p;
}

void milone_profile_log(struct String msg, void *profiler) {
    struct Profiler *p = (struct Profiler *)profiler;

    long t = milone_get_time_millis();
    long s = p->epoch;

    long millis = t - s;
    if (millis < 0) {
        millis = 0;
    }

    long sec = millis / 1000;
    millis %= 1000;

    long bytes = s_heap_size - p->heap_size;
    if (bytes < 0) {
        bytes = 0;
    }

    long kilo = bytes / 1000;
    bytes %= 1000;

    long mega = kilo / 1000;
    kilo %= 1000;

    double usage = s_heap_alloc == 0 ? 0.0 : (double)s_heap_size / s_heap_alloc;
    fprintf(stderr, "profile: time=%4d.%03d mem=%5d,%03d,%03d use=%.03f\n%s\n",
            (int)sec, (int)millis, (int)mega, (int)kilo, (int)bytes, usage,
            msg.str);

    p->epoch = t;
    p->heap_size = s_heap_size;
}

// -----------------------------------------------
// For competitive programming
// -----------------------------------------------

int scan_int(void) {
    int value;
    int _n = scanf("%d", &value);
    return value;
}

char scan_char(void) {
    char value;
    int _n = scanf("%c", &value);
    return value;
}

struct String scan_str(int capacity) {
    if (capacity <= 0) {
        fprintf(stderr, "scan_str(%d)", capacity);
        exit(1);
    }

    char *str = calloc(capacity, sizeof(char));
    if (str == NULL) {
        fprintf(stderr, "scan_str(%d) out of memory", capacity);
        exit(1);
    }

    char fmt[16] = {};
    sprintf(fmt, "%%%ds", capacity);
    assert(fmt[15] == 0);

    int _n = scanf(fmt, str);

    int len = strlen(str);
    assert(len < capacity);
    return (struct String){.str = str, .len = len};
}

void *int_array_new(int len) {
    void *p = calloc(len, sizeof(int));
    // fprintf(stderr, "int_array_new(len=%d) = %p\n", len, p);
    return p;
}

int int_array_get(void *array, int index) {
    int value = ((int *)array)[index];
    // fprintf(stderr, "int_array_get(%p, index=%d) = %d\n", array, index,
    // value);
    return value;
}

void int_array_set(void *array, int index, int value) {
    // fprintf(stderr, "int_array_set(%p, index=%d, value=%d)\n", array, index,
    // value);
    ((int *)array)[index] = value;
}

// -----------------------------------------------
// Command-line Arguments
// -----------------------------------------------

static int s_argc;
static char **s_argv;

int arg_count(void) { return s_argc; }

struct String arg_get(int index) {
    if (!(0 <= index && index < s_argc)) {
        abort();
    }

    char *str = s_argv[index];
    int len = strlen(str);
    return (struct String){.str = str, .len = len};
}

// -----------------------------------------------
// Runtime Entrypoint
// -----------------------------------------------

int main(int argc, char **argv) {
    s_argc = argc - 1;
    s_argv = argv + 1;

    int milone_main();
    return milone_main();
}

#define main milone_main
