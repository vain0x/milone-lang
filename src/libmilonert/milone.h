// Runtime code for C programs generated by the milone-lang compiler.
// Interface is still unstable.

#ifndef MILONE_H_INCLUDED
#define MILONE_H_INCLUDED

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

void milone_start(int argc, char **argv);

// -----------------------------------------------
// memory management
// -----------------------------------------------

void milone_region_enter(void);
void milone_region_leave(void);
void *milone_region_alloc(uint32_t count, uint32_t size);
void milone_region_defer(void (*fun)(void const *env), void const *env);

// -----------------------------------------------
// integers
// -----------------------------------------------

int milone_int32_compare(int32_t l, int32_t r);
int milone_int64_compare(int64_t l, int64_t r);
int milone_uint64_compare(uint64_t l, uint64_t r);

// -----------------------------------------------
// String
// -----------------------------------------------

// This assumes some invariants, see documentation about string type.
struct String {
    char const *ptr;
    uint32_t len;
};

// Convert a null-terminated string to a string object by computing its length.
//
// SAFETY: The resulting string is valid until the pointer is valid.
struct String string_borrow(char const *c_str);

// Compare two strings in lexicographical order.
int string_compare(struct String l, struct String r);

// Create a copy of native C string.
struct String string_of_raw_parts(char const *ptr, uint32_t len);

// Create a copy of native null-terminated C string.
struct String string_of_c_str(char const *s);

// Create a concatenation of two string.
struct String string_add(struct String l, struct String r);

// Create a slice of string.
struct String string_slice(struct String s, int32_t l, int32_t r);

/// Implementation of `s.[l..r]`; `r` is inclusive.
static struct String string_get_slice(int32_t l, int32_t r, struct String s) {
    return string_slice(s, l, r + 1);
}

struct String string_ensure_null_terminated(struct String s);

// Ensure null-terminated.
char const *string_to_c_str(struct String s);

// Conversion:

int8_t string_to_int8(struct String s);
int16_t string_to_int16(struct String s);
int32_t string_to_int32(struct String s);
int64_t string_to_int64(struct String s);
intptr_t string_to_nativeint(struct String s);

uint8_t string_to_uint8(struct String s);
uint16_t string_to_uint16(struct String s);
uint32_t string_to_uint32(struct String s);
uint64_t string_to_uint64(struct String s);
uintptr_t string_to_unativeint(struct String s);

struct String string_of_int64(int64_t value);
struct String string_of_uint64(uint64_t value);

double string_to_float64(struct String s);
struct String string_of_float64(double value);

struct String string_of_bool(bool value);

char string_to_char(struct String s);
struct String string_of_char(char value);

// Actual name of string cons-cell.
struct StringCons;

struct String string_concat(struct String sep, struct StringCons const *strings);

// Low level operations.

inline char const *string_as_ptr(struct String s) { return s.ptr; }

// -----------------------------------------------
// OsString
// -----------------------------------------------
// #milone_os_string

// HACK: This section should be written in an appropriate module
//       but there's no good way.
//       On Windows, this should include Windows.h and tchar.h if necessary.

#if defined(_MSC_VER) // On Windows MSVC

// UTF-16 code unit
typedef uint16_t OsChar;

#else

// UTF-8 code unit
typedef char OsChar;

#endif

// Pointer to a NUL-terminated string of OS-dependent encoding.
// LPCTSTR on Windows, char const * on Linux.
typedef OsChar const *OsStringPtr;

// String of OS-dependent encoding.
//
// This holds the same invariants as String.
struct MiloneOsString {
    OsStringPtr ptr;
    uint32_t len;
};

// Wraps a pointer with a string object.
//
// SAFETY: Tha result is valid as long as the given pointer is valid.
struct MiloneOsString milone_os_string_borrow(OsStringPtr ptr);

// Creates an OS-encode string by copying from a NUL-terminated string.
// The result is guaranteed to be NUL-terminated.
struct MiloneOsString milone_os_string_of_native(OsStringPtr ptr);

// Creates an OS-encode string by converting from a UTF-8 string.
// The result is guaranteed to be NUL-terminated.
struct MiloneOsString milone_os_string_of(struct String s);

// Creates a UTF-8 string by converting from an OS-encode string.
// The result is guaranteed to be NUL-terminated.
struct String milone_os_string_to(struct MiloneOsString s);

// -----------------------------------------------
// runtime error
// -----------------------------------------------

// Invoke a runtime error with an error message to terminate the process.
_Noreturn void milone_abort(char const *name, char const *filename, int32_t row, int32_t column);

// Invoked when asserted condition was evaluated to false.
_Noreturn static void milone_assert_error(char const *filename, int32_t row, int32_t column) {
    milone_abort("Assertion Error", filename, row, column);
}

// Invoked when match expression didn't have any arm to match.
_Noreturn static void milone_exhaust_error(char const *filename, int32_t row, int32_t column) {
    milone_abort("Exhaustion Error", filename, row, column);
}

// Invoked when never-returning function actually returned to caller.
_Noreturn static void milone_never_error(char const *filename, int32_t row, int32_t column) {
    milone_abort("Never Error", filename, row, column);
}

#endif
