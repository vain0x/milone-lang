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

// -----------------------------------------------
// memory management (memory pool)
// -----------------------------------------------

size_t milone_mem_heap_size(void);
size_t milone_mem_alloc_cost(void);

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

THREAD_LOCAL struct MemoryChunk s_heap;
THREAD_LOCAL size_t s_heap_level; // depth of current region
THREAD_LOCAL size_t s_heap_size;  // consumed size in all regions
THREAD_LOCAL size_t s_heap_alloc; // allocated size in all regions
THREAD_LOCAL size_t s_alloc_cost; // allocation count

_Noreturn static void oom(void) {
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

static void do_enter_region(void) {
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

static void do_leave_region(void) {
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

static void *do_mem_alloc(int count, size_t size) {
    assert(count > 0 && size > 0);

    size_t total = (size_t)count * size;

    // align to 16x
    total = (total + 0xf) & ~0xf;
    assert(total % 16 == 0 && total >= (size_t)count * size);

    if (s_heap.len + total > s_heap.cap) {
        return milone_mem_alloc_slow(total);
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

#ifndef MILONE_NO_DEFAULT_ALLOCATOR

size_t milone_mem_heap_size(void) { return s_heap_size; }
size_t milone_mem_alloc_cost(void) { return s_alloc_cost; }

void milone_enter_region(void) { do_enter_region(); }
void milone_leave_region(void) { do_leave_region(); }

void *milone_mem_alloc(int count, size_t size) {
    return do_mem_alloc(count, size);
}

#endif // MILONE_NO_DEFAULT_ALLOCATOR

// -----------------------------------------------
// int
// -----------------------------------------------

int int_compare(int l, int r) {
    if (l == r)
        return 0;
    if (l < r)
        return -1;
    return 1;
}

int int64_compare(int64_t l, int64_t r) {
    if (l == r)
        return 0;
    if (l < r)
        return -1;
    return 1;
}

int uint64_compare(uint64_t l, uint64_t r) {
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

    // +1 for final null byte.
    int min_len = sb->len + addition + 1;
    if (sb->cap < min_len) {
        sb->cap = min_len;
    }

    char *buf = milone_mem_alloc(sb->cap, sizeof(char));
    memcpy(buf, sb->buf, sb->len);
    sb->buf = buf;

    assert(sb->len < sb->cap);
    assert(sb->buf[sb->cap - 1] == '\0');
}

static void string_builder_append_string(struct StringBuilder *sb,
                                         struct String value) {
    if (sb->len + value.len >= sb->cap) {
        string_builder_grow(sb, value.len);
    }

    memcpy(&sb->buf[sb->len], value.str, value.len);
    sb->len += value.len;

    assert(sb->len < sb->cap);
    assert(sb->buf[sb->cap - 1] == '\0');
}

struct String str_borrow(char const *c_str) {
    assert(c_str != NULL);
    return (struct String){.str = c_str, .len = (int)strlen(c_str)};
}

int str_compare(struct String left, struct String right) {
    // Compare prefix part of two strings.
    int min_len = int_clamp(left.len, 0, right.len);
    int c = memcmp(left.str, right.str, min_len);
    if (c != 0) {
        return c;
    }

    // One is prefix of the other here, and therefore, longer is greater.
    return int_compare(left.len, right.len);
}

_Noreturn static void error_str_of_raw_parts(int len) {
    fprintf(stderr, "FATAL: Negative string length (%d).\n", len);
    exit(1);
}

struct String str_of_raw_parts(char const *p, int len) {
    assert(p != NULL);

    if (len <= 0) {
        if (len < 0) {
            error_str_of_raw_parts(len);
        }

        return str_borrow("");
    }

    // +1 for the invariant of existence of null byte.
    char *str = milone_mem_alloc(len + 1, sizeof(char));
    memcpy(str, p, len * sizeof(char));
    assert(str[len] == '\0');
    return (struct String){.str = str, .len = len};
}

struct String str_of_c_str(char const *s) {
    assert(s != NULL);
    return str_of_raw_parts(s, (int)strlen(s));
}

_Noreturn static void error_str_add_overflow() {
    fprintf(stderr, "str_add: length overflow.\n");
    exit(1);
}

struct String str_add(struct String left, struct String right) {
    if (left.len == 0 || right.len == 0) {
        return right.len == 0 ? left : right;
    }

    if ((uint32_t)left.len + (uint32_t)right.len >= (uint32_t)INT32_MAX) {
        error_str_add_overflow();
    }

    int len = left.len + right.len;
    char *str = milone_mem_alloc(len + 1, sizeof(char));
    memcpy(str, left.str, left.len);
    memcpy(str + left.len, right.str, right.len);
    assert(str[len] == '\0');
    return (struct String){.str = str, .len = len};
}

struct String str_slice(struct String s, int l, int r) {
    l = int_clamp(l, 0, s.len);
    r = int_clamp(r, l, s.len);
    assert(0 <= l && l <= r && r <= s.len);
    return (struct String){.str = s.str + l, .len = r - l};
}

struct String str_ensure_null_terminated(struct String s) {
    // The dereference is safe due to the invariant of existence of null byte.
    if (s.str[s.len] != '\0') {
        s = str_of_raw_parts(s.str, s.len);
    }

    assert(s.str[s.len] == '\0');
    return s;
}

char const *str_to_c_str(struct String s) {
    return str_ensure_null_terminated(s).str;
}

static bool str_is_all_spaces(char const *begin, char const *end) {
    char const *p = begin;
    while (p != end && *p != 0 && isspace(*p)) {
        p++;
    }
    return p == end;
}

static void verify_str_to_number(const char *type_name, bool ok) {
    if (!ok) {
        fprintf(stderr, "FATAL: Failed to convert a string to %s.\n",
                type_name);
        exit(1);
    }
}

bool str_to_int64_checked(struct String s, int64_t *value_ptr) {
    s = str_ensure_null_terminated(s);
    char *endptr = (char *)(s.str + s.len);
    long long value = strtoll(s.str, &endptr, 10);
    *value_ptr = (int64_t)value;
    return endptr != s.str && str_is_all_spaces(endptr, s.str + s.len) &&
           errno != ERANGE;
}

bool str_to_uint64_checked(struct String s, uint64_t *value_ptr) {
    s = str_ensure_null_terminated(s);
    char *endptr = (char *)(s.str + s.len);
    unsigned long long value = strtoull(s.str, &endptr, 10);
    *value_ptr = (uint64_t)value;
    return endptr != s.str && str_is_all_spaces(endptr, s.str + s.len) &&
           errno != ERANGE;
}

double str_to_double(struct String s) {
    s = str_ensure_null_terminated(s);
    char *endptr = (char *)(s.str + s.len);
    double value = strtod(s.str, &endptr);
    bool ok = endptr != s.str && str_is_all_spaces(endptr, s.str + s.len) &&
              errno != ERANGE;
    verify_str_to_number("float", ok);
    return value;
}

bool str_to_int_checked(struct String s, int *value_ptr) {
    int64_t value;
    bool ok = str_to_int64_checked(s, &value);
    if (!(ok && INT32_MIN <= value && value <= INT32_MAX)) {
        *value_ptr = 0;
        return false;
    }

    *value_ptr = (int)value;
    return true;
}

int8_t str_to_int8(struct String s) {
    int64_t value;
    bool ok = str_to_int64_checked(s, &value);
    verify_str_to_number("int8", ok && INT8_MIN <= value && value <= INT8_MAX);
    return (int8_t)value;
}

int16_t str_to_int16(struct String s) {
    int64_t value;
    bool ok = str_to_int64_checked(s, &value);
    verify_str_to_number("int16",
                         ok && INT16_MIN <= value && value <= INT16_MAX);
    return (int16_t)value;
}

int str_to_int(struct String s) {
    int value;
    bool ok = str_to_int_checked(s, &value);
    verify_str_to_number("int", ok);
    return value;
}

int64_t str_to_int64(struct String s) {
    int64_t value;
    bool ok = str_to_int64_checked(s, &value);
    verify_str_to_number("int64", ok);
    return value;
}

intptr_t str_to_intptr(struct String s) { return (intptr_t)str_to_int64(s); }

uint8_t str_to_uint8(struct String s) {
    uint64_t value;
    bool ok = str_to_uint64_checked(s, &value);
    verify_str_to_number("uint8", ok && value <= UINT8_MAX);
    return (uint8_t)value;
}

uint16_t str_to_uint16(struct String s) {
    uint64_t value;
    bool ok = str_to_uint64_checked(s, &value);
    verify_str_to_number("uint16", ok && value <= UINT16_MAX);
    return (uint16_t)value;
}

uint32_t str_to_uint32(struct String s) {
    uint64_t value;
    bool ok = str_to_uint64_checked(s, &value);
    verify_str_to_number("uint", ok && value <= UINT32_MAX);
    return (uint32_t)value;
}

uint64_t str_to_uint64(struct String s) {
    uint64_t value;
    bool ok = str_to_uint64_checked(s, &value);
    verify_str_to_number("uint64", ok);
    return value;
}

uintptr_t str_to_uintptr(struct String s) {
    return (uintptr_t)str_to_uint64(s);
}

struct String str_of_int64(int64_t value) {
    char buf[21] = {0};
    int n = sprintf(buf, "%lld", (long long)value);
    return str_of_raw_parts(buf, n);
}

struct String str_of_uint64(uint64_t value) {
    char buf[21] = {0};
    int n = sprintf(buf, "%llu", (unsigned long long)value);
    return str_of_raw_parts(buf, n);
}

struct String str_of_double(double value) {
    char buf[64] = {0};
    int n = sprintf(buf, "%f", value);
    return str_of_raw_parts(buf, n);
}

struct String str_of_bool(bool value) {
    return value ? str_borrow("True") : str_borrow("False");
}

char str_to_char(struct String s) { return s.len >= 1 ? *s.str : '\0'; }

struct String str_of_char(char value) {
    if (value == '\0') {
        return str_borrow("");
    }

    char *str = milone_mem_alloc(2, sizeof(char));
    str[0] = value;
    return (struct String){.str = str, .len = 1};
}

struct MyStringList {
    struct String head;
    struct MyStringList const *tail;
};

struct String str_concat(struct String sep, struct StringList const *strings) {
    struct MyStringList const *ss = (struct MyStringList const *)strings;

    struct StringBuilder *sb = string_builder_new_with_capacity(0x1000);
    bool first = true;

    while (ss) {
        struct String head = ss->head;
        ss = ss->tail;

        if (!first && sep.len > 0) {
            string_builder_append_string(sb, sep);
        }
        first = false;

        string_builder_append_string(sb, head);
    }

    // #sb_finish
    // Null termination. Technically unnecessary but can skip some cloning.
    assert(sb->len < sb->cap);
    sb->buf[sb->len] = '\0';

    return (struct String){.str = sb->buf, .len = sb->len};
}

// -----------------------------------------------
// assertion
// -----------------------------------------------

void milone_assert(bool cond, struct String name, int y, int x) {
    if (!cond) {
        fprintf(stderr, "Assertion failed at %s:%d:%d\n", str_to_c_str(name), y + 1, x + 1);
        exit(1);
    }
}

// -----------------------------------------------
// file IO
// -----------------------------------------------

int file_exists(struct String file_name) {
    file_name = str_ensure_null_terminated(file_name);

    bool ok = false;

    FILE *fp = fopen(file_name.str, "r");
    if (fp) {
        ok = true;
        fclose(fp);
    }

    return ok;
}

struct String file_read_all_text(struct String file_name) {
    file_name = str_ensure_null_terminated(file_name);

    FILE *fp = fopen(file_name.str, "rb");
    if (!fp) {
        fprintf(stderr, "File '%s' not found.", file_name.str);
        exit(1);
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    if (size < 0) {
        fclose(fp);
        fprintf(stderr, "%s", "Couldn't retrieve the file size.");
        exit(1);
    }
    fseek(fp, 0, SEEK_SET);

    char *content = milone_mem_alloc((size_t)size + 1, sizeof(char));
    size_t read_size = fread(content, 1, (size_t)size, fp);
    if (read_size != (size_t)size) {
        fclose(fp);
        fprintf(stderr, "%s", "Couldn't retrieve the file contents");
        exit(1);
    }

    fclose(fp);
    return (struct String){.str = content, .len = size};
}

void file_write_all_text(struct String file_name, struct String content) {
    file_name = str_ensure_null_terminated(file_name);

    FILE *fp = NULL;

    // Skip writing if unchanged.
    {
        fp = fopen(file_name.str, "rb");
        if (fp) {
            fseek(fp, 0, SEEK_END);
            long size = ftell(fp);
            fseek(fp, 0, SEEK_SET);

            if (size >= 0 && (size_t)size == (size_t)content.len) {
                char *old_content = calloc((size_t)size + 1, sizeof(char));
                size_t read_len =
                    fread(old_content, sizeof(char), (size_t)size, fp);
                bool same = read_len == (size_t)size &&
                            memcmp(old_content, content.str, read_len) == 0;
                free(old_content);

                if (same) {
                    goto END;
                }
            }
            fclose(fp);
            fp = NULL;
        }
    }

    fp = fopen(file_name.str, "w+");
    if (!fp) {
        perror("fopen(w+)");
        exit(1);
    }

    bool ok = fwrite(content.str, sizeof(char), (size_t)content.len, fp) ==
              (size_t)content.len;
    if (!ok) {
        perror("fwrite");
        fclose(fp);
        exit(1);
    }

END:
    fclose(fp);
}

struct String milone_read_stdin_all(void) {
    char buf[0x1000] = "";
    struct StringBuilder *sb = string_builder_new_with_capacity(sizeof buf);

    while (true) {
        if (sb->cap > 10100100) {
            fprintf(stderr, "error: stdin too long\n");
            exit(1);
        }

        size_t read_len = fread(buf, 1, sizeof buf, stdin);
        if (read_len == 0)
            break;

        string_builder_append_string(
            sb, (struct String){.str = buf, .len = (int)read_len});
    }

    // #sb_finish
    // Null termination. Technically unnecessary but can skip some cloning.
    assert(sb->len < sb->cap);
    sb->buf[sb->len] = '\0';

    return (struct String){.str = sb->buf, .len = sb->len};
}

// -----------------------------------------------
// environment
// -----------------------------------------------

struct String milone_get_env(struct String name) {
    name = str_ensure_null_terminated(name);

    char const *value = getenv(name.str);
    if (value == NULL) {
        return str_borrow("");
    }

    return str_of_c_str(value);
}

// -----------------------------------------------
// profiling
// -----------------------------------------------

static long milone_get_time_millis(void) {
    struct timespec t;
    timespec_get(&t, TIME_UTC);
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
    struct Profiler *p = milone_mem_alloc(1, sizeof(struct Profiler));
    p->msg = str_borrow("start");
    p->epoch = milone_get_time_millis();
    p->start_epoch = p->epoch;
    p->heap_size = milone_mem_heap_size();
    p->alloc_cost = milone_mem_alloc_cost();
    return p;
}

static void milone_profile_print_log(struct String msg, long millis,
                                     long mem_bytes, long alloc_cost) {
    msg = str_ensure_null_terminated(msg);

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

    fprintf(stderr, "profile: %-17s time=%4d.%02d mem=%s cost=%s\n", msg.str,
            (int)sec, (int)millis, mem, cost);
}

void milone_profile_log(struct String msg, void *profiler) {
    struct Profiler *p = (struct Profiler *)profiler;

    long t = milone_get_time_millis();
    long heap_size = (long)milone_mem_heap_size();
    long alloc_cost = (long)milone_mem_alloc_cost();

    long time_delta = t - p->epoch;
    long mem_delta = heap_size - (long)p->heap_size;
    long alloc_delta = alloc_cost - (long)p->alloc_cost;

    milone_profile_print_log(p->msg, time_delta, mem_delta, alloc_delta);

    p->msg = msg;
    p->epoch = t;
    p->heap_size = heap_size;
    p->alloc_cost = alloc_cost;

    if (str_compare(msg, str_borrow("Finish")) == 0) {
        fprintf(stderr, "profile: Finish\n");
        long millis = t - p->start_epoch;
        milone_profile_print_log(str_borrow("total"), millis, heap_size,
                                 alloc_cost);
    }
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

    char *str = milone_mem_alloc(capacity, sizeof(char));
    if (str == NULL) {
        fprintf(stderr, "scan_str(%d) out of memory", capacity);
        exit(1);
    }

    char fmt[16] = {0};
    sprintf(fmt, "%%%ds", capacity);
    assert(fmt[15] == 0);

    int _n = scanf(fmt, str);

    size_t len = strlen(str);
    assert((long long)len < (long long)capacity);
    return (struct String){.str = str, .len = (int)len};
}

// -----------------------------------------------
// Runtime Entrypoint
// -----------------------------------------------

static int s_argc;
static char **s_argv;

int milone_get_arg_count(void) { return s_argc; }

struct String milone_get_arg(int index) {
    if ((uint32_t)index >= (uint32_t)s_argc) {
        return str_borrow("");
    }

    return str_borrow(s_argv[index]);
}

void milone_start(int argc, char **argv) {
    s_argc = argc;
    s_argv = argv;
}
