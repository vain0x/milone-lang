#ifndef INCLUDED_LIB_SPAN_H
#define INCLUDED_LIB_SPAN_H

#include <stddef.h>
#include <stdint.h>

#include <milone.h>

// Read-only untyped memory.
struct Span {
    void const *ptr;
    size_t len;
};

struct Span span_slice(struct Span span, size_t start, size_t end,
                       size_t item_size);

static inline struct Span span_take(struct Span span, size_t len,
                                    size_t item_size) {
    return span_slice(span, 0, len, item_size);
}

// Mutable untyped memory.
struct SpanMut {
    void *ptr;
    size_t len;
};

static inline struct Span span_mut_as_const(struct SpanMut span) {
    return (struct Span){.ptr = span.ptr, .len = span.len};
}

// Growable untyped memory.
struct Buffer {
    void *ptr;
    size_t len;
    size_t cap;
};

struct Buffer buffer_new(size_t cap, size_t item_size);

struct Buffer buffer_new_uninit(size_t len, size_t cap, size_t item_size);

void buffer_grow(struct Buffer *buffer, size_t required_len, size_t item_size);

static inline struct Buffer buffer_grow_nonmut(struct Buffer buffer,
                                               size_t required_len,
                                               size_t item_size) {
    buffer_grow(&buffer, required_len, item_size);
    return buffer;
}

void buffer_append(struct Buffer *buffer, struct Span span, size_t item_size);

static inline struct Buffer
buffer_append_nonmut(struct Buffer buffer, struct Span span, size_t item_size) {
    buffer_append(&buffer, span, item_size);
    return buffer;
}

struct SpanMut buffer_slice_mut(struct Buffer buffer, size_t start, size_t end,
                                size_t item_size);

static inline struct String buffer_as_string(struct Buffer buffer) {
    if (buffer.len == buffer.cap) {
        buffer_grow(&buffer, buffer.len + 1, 1);
    }
    return (struct String){.str = (char const *)buffer.ptr, .len = buffer.len};
}

#endif
