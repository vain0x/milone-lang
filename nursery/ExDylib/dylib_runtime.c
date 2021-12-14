#include <assert.h>
#include <milone.h>

// Opaque
struct Dylib;

#if defined(_MSC_VER)

#define MILONE_PLATFORM_WINDOWS 1
#define WIN32_LEAN_AND_MEAN 1
#include <Windows.h>
#include <tchar.h>

// from milone_platform

_Noreturn static void failwith(char const *msg) {
    fprintf(stderr, "ERROR: %s\n", msg);
    exit(1);
}

// String of OS-native encoding.
//
// This holds the same invariant as `String`.
struct OsString {
    // Pointer to string.
    //
    // Allocation block that is pointed to must include at least one "\x00\x00"
    // sequence in distance of 2N bytes from the end of the span.
    LPCTSTR str;

    // Length. Count of UTF-16 code units. Half of bytes.
    size_t len;
};

// Convert an null-terminated OS-native string to OsString.
//
// The result is NOT allocated and is valid only when the parmeter is valid.
static struct OsString os_string_borrow(LPCTSTR s) {
    assert(s != NULL);
    return (struct OsString){.str = s, .len = _tcslen(s)};
}

// Convert a UTF-8 string to OS-native encoding. (UTF-16 on Windows)
//
// The result is null-terminated.
static struct OsString os_string_of(struct String s) {
    if (s.len == 0) {
        return os_string_borrow(L"");
    }

    int len = MultiByteToWideChar(CP_UTF8, 0, s.str, s.len, NULL, 0);
    if (len == 0) {
        failwith("MultiByteToWideChar");
    }
    assert(len >= 0);

    LPTSTR buf = milone_mem_alloc(len + 1, sizeof(TCHAR));

    int n = MultiByteToWideChar(CP_UTF8, 0, s.str, s.len, buf, len);
    if (n == 0) {
        failwith("MultiByteToWideChar");
    }
    assert(n >= 0);
    assert(n <= len);
    assert(buf[(size_t)n] == L'\0');
    return (struct OsString){.str = buf, .len = (size_t)n};
}

struct Dylib *milone_dylib_open(struct String path) {
    HMODULE h_module = LoadLibrary(os_string_of(path).str);
    if (h_module == NULL) {
        DWORD err = GetLastError();
        fprintf(stderr, "ERROR: LoadLibrary(%s) %d\n", str_to_c_str(path), err);
        abort();
    }
    return (struct Dylib *)h_module;
}

void milone_dylib_close(struct Dylib *lib) {
    bool ok = FreeLibrary(lib) != 0;
    assert(ok);
}

void *milone_dylib_get_symbol(struct Dylib *lib, struct String symbol_name) {
    assert(lib != NULL);

    HMODULE h_module = (HMODULE)lib;
    void *proc = GetProcAddress(h_module, str_to_c_str(symbol_name));
    if (proc == NULL) {
        DWORD err = GetLastError();
        fprintf(stderr, "ERROR: GetProcAddress(%s) %d\n", str_to_c_str(symbol_name), err);
        abort();
    }
    return proc;
}

#endif // windows
