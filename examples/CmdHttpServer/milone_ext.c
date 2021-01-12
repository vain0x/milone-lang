#include <assert.h>
#include <errno.h>
#include <milone.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "./milone_ext.h"

struct Span span_slice(struct Span span, size_t start, size_t end,
                       size_t item_size) {
    if (end > span.len) {
        end = span.len;
    }
    if (start > end) {
        start = end;
    }
    assert(start <= end && end <= span.len);
    return (struct Span){
        .ptr = (void const *)((uintptr_t)span.ptr + start * item_size),
        .len = end - start};
}

struct Buffer buffer_new(size_t cap, size_t item_size) {
    uint8_t *ptr =
        cap == 0 || item_size == 0 ? NULL : milone_mem_alloc(cap, item_size);
    return (struct Buffer){.ptr = ptr, .len = 0, .cap = cap};
}

struct Buffer buffer_new_uninit(size_t len, size_t cap, size_t item_size) {
    if (cap < len) {
        cap = len;
    }

    struct Buffer buffer = buffer_new(cap, item_size);
    buffer.len = len;
    return buffer;
}

void buffer_grow(struct Buffer *buffer, size_t required_len, size_t item_size) {
    assert(required_len > buffer->len);

    size_t new_cap = buffer->cap * 2;
    if (new_cap < required_len) {
        new_cap = required_len;
    }

    void *new_ptr = milone_mem_alloc((int)new_cap, item_size);
    memcpy(new_ptr, buffer->ptr, item_size * buffer->len);

    buffer->ptr = new_ptr;
    buffer->cap = new_cap;
}

void buffer_append(struct Buffer *buffer, struct Span src, size_t item_size) {
    size_t new_len = buffer->len + src.len;
    if (new_len > buffer->cap) {
        buffer_grow(buffer, new_len, item_size);
    }

    void *dest = (void *)((uintptr_t)buffer->ptr + buffer->len * item_size);
    memcpy(dest, src.ptr, src.len * item_size);

    buffer->len += src.len;
    assert(buffer->len <= buffer->cap);
}

struct SpanMut buffer_slice_mut(struct Buffer buffer, size_t start, size_t end,
                                size_t item_size) {

    if (end > buffer.len) {
        end = buffer.len;
    }
    if (start > end) {
        start = end;
    }
    return (struct SpanMut){
        .ptr = (void *)((uintptr_t)buffer.ptr + start * item_size),
        .len = end - start};
}

bool milone_file_exists(struct String file_path, bool follow_link) {
    struct stat st = {};
    bool ok = follow_link ? stat(str_to_c_str(file_path), &st) == 0
                          : lstat(str_to_c_str(file_path), &st) == 0;
    if (!ok) {
        return false;
    }

    return S_ISREG(st.st_mode);
}

size_t milone_file_read(FILE *fp, struct SpanMut dest) {
    assert(fp != NULL);
    return fread(dest.ptr, 1, dest.len, fp);
}

size_t milone_file_write(FILE *fp, struct SpanMut src) {
    assert(fp != NULL);
    return fwrite(src.ptr, 1, src.len, fp);
}
