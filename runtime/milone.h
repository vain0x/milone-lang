// Runtime code for C programs generated by the milone-lang compiler.
// Interface is still unstable.

#ifndef MILONE_H_INCLUDED
#define MILONE_H_INCLUDED

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

// -----------------------------------------------
// assertion
// -----------------------------------------------

void milone_assert(bool cond, int row, int column);

// -----------------------------------------------
// memory management
// -----------------------------------------------

void milone_enter_region(void);
void milone_leave_region(void);
void *milone_mem_alloc(int count, size_t size);

// -----------------------------------------------
// int
// -----------------------------------------------

int int_compare(int l, int r);
int int64_compare(int64_t l, int64_t r);
int uint64_compare(uint64_t l, uint64_t r);

// -----------------------------------------------
// str
// -----------------------------------------------

// This assumes some invariants, see documentation about string type.
struct String {
    char const *str;
    int len;
};

// Convert a null-terminated string to a string object by computing its length.
//
// SAFETY: The resulting string is valid until the pointer is valid.
struct String str_borrow(char const *c_str);

// Compare two strings in lexicographical order.
int str_compare(struct String l, struct String r);

// Create a copy of native C string.
struct String str_of_raw_parts(char const *ptr, int len);

// Create a copy of native null-terminated C string.
struct String str_of_c_str(char const *s);

// Create a concatenation of two string.
struct String str_add(struct String l, struct String r);

// Create a slice of string.
struct String str_slice(struct String s, int l, int r);

/// Implementation of `s.[l..r]`; `r` is inclusive.
static struct String str_get_slice(int l, int r, struct String s) {
    return str_slice(s, l, r + 1);
}

struct String str_ensure_null_terminated(struct String s);

// Ensure null-terminated.
char const *str_to_c_str(struct String s);

// Conversion:

int8_t str_to_int8(struct String s);
int16_t str_to_int16(struct String s);
int str_to_int(struct String s);
int64_t str_to_int64(struct String s);
intptr_t str_to_intptr(struct String s);

uint8_t str_to_uint8(struct String s);
uint16_t str_to_uint16(struct String s);
uint32_t str_to_uint32(struct String s);
uint64_t str_to_uint64(struct String s);
uintptr_t str_to_uintptr(struct String s);

struct String str_of_int64(int64_t value);
struct String str_of_uint64(uint64_t value);

double str_to_double(struct String s);
struct String str_of_double(double value);

struct String str_of_bool(bool value);

char str_to_char(struct String s);
struct String str_of_char(char value);

// Actual name of string list.
struct StringList;

struct String str_concat(struct String sep, struct StringList const *strings);

// Low level operations.

inline char const *str_as_ptr(struct String s) { return s.str; }

#endif
