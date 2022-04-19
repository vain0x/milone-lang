// Expose platform-specific functions for milone-lang compiler.

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <milone.h>

#if defined(_MSC_VER)

#define MILONE_PLATFORM_WINDOWS 1
#define WIN32_LEAN_AND_MEAN 1
#include <Windows.h>
#include <tchar.h>

#include <bcrypt.h> // for uuid
#pragma comment(lib, "bcrypt.lib")

#else

#define MILONE_PLATFORM_UNIX 1
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#endif              // defined(_MSC_VER)

// -----------------------------------------------
// utils
// -----------------------------------------------

_Noreturn static void failwith(char const *msg) {
    fprintf(stderr, "ERROR: %s\n", msg);
    exit(1);
}

static bool path_is_absolute(struct String path) {
#if defined(MILONE_PLATFORM_UNIX)
    return path.len >= 1 && *path.ptr == '/';
#elif defined(MILONE_PLATFORM_WINDOWS)
    // UNC style path isn't supported
    return (path.len >= 1 && *path.ptr == '/') ||
           (path.len >= 2 && path.ptr[1] == ':');
#else
#error no platform
#endif
}

// #pathJoin
// Prepend `base_path` as prefix to the path if it's relative.
// For absolute path, just return `path`.
static struct String path_join(struct String base_path, struct String path) {
    assert(path_is_absolute(base_path));

    if (path_is_absolute(path)) {
        return path;
    }

    if (base_path.len >= 1 && base_path.ptr[base_path.len - 1] != '/') {
        base_path = string_add(base_path, string_borrow("/"));
    }
    return string_add(base_path, path);
}

// -----------------------------------------------
// OSString
// -----------------------------------------------

#ifdef MILONE_PLATFORM_WINDOWS

// String of OS-native encoding.
//
// This holds the same invariant as `String`.
struct OsString {
    // Pointer to string.
    //
    // Allocation block that is pointed to must include at least one "\x00\x00"
    // sequence in distance of 2N bytes from the end of the span.
    LPCTSTR ptr;

    // Length. Count of UTF-16 code units. Half of bytes.
    size_t len;
};

// Convert an null-terminated OS-native string to OsString.
//
// The result is NOT allocated and is valid only when the parmeter is valid.
static struct OsString os_string_borrow(LPCTSTR s) {
    assert(s != NULL);
    return (struct OsString){.ptr = s, .len = _tcslen(s)};
}

// Convert a UTF-8 string to OS-native encoding. (UTF-16 on Windows)
//
// The result is null-terminated.
static struct OsString os_string_of(struct String s) {
    if (s.len == 0) {
        return os_string_borrow(L"");
    }

    int len = MultiByteToWideChar(CP_UTF8, 0, s.ptr, s.len, NULL, 0);
    if (len == 0) {
        failwith("MultiByteToWideChar");
    }
    assert(len >= 0);

    LPTSTR buf = milone_region_alloc(len + 1, sizeof(TCHAR));

    int n = MultiByteToWideChar(CP_UTF8, 0, s.ptr, s.len, buf, len);
    if (n == 0) {
        failwith("MultiByteToWideChar");
    }
    assert(n >= 0);
    assert(n <= len);
    assert(buf[(size_t)n] == L'\0');
    return (struct OsString){.ptr = buf, .len = (size_t)n};
}

// Convert an OS-string to a UTF-8. Allocate to copy.
//
// The result is null-terminated.
static struct String os_string_to(struct OsString s) {
    if (s.len == 0) {
        return string_borrow("");
    }

    static_assert(sizeof(wchar_t) == 2, "this function is windows only");
    int len =
        WideCharToMultiByte(CP_UTF8, 0, s.ptr, (int)s.len, NULL, 0, NULL, NULL);
    if (len == 0) {
        failwith("WideCharToMultiByte");
    }
    assert(len >= 0);

    char *buf = milone_region_alloc(len + 1, sizeof(char));

    int n = WideCharToMultiByte(CP_UTF8, 0, s.ptr, (int)s.len, buf, len, NULL,
                                NULL);
    if (n == 0) {
        failwith("WideCharToMultiByte");
    }
    assert(n >= 0);
    assert(n <= len);
    assert(buf[(size_t)n] == '\0');
    return (struct String){.ptr = buf, .len = (size_t)n};
}

#endif // windows

// -----------------------------------------------
// misc
// -----------------------------------------------

struct String milone_get_platform(void) {
#if defined(MILONE_PLATFORM_UNIX)
    return string_borrow("unix");
#elif defined(MILONE_PLATFORM_WINDOWS)
    return string_borrow("windows");
#else
#error no platform
#endif
}

// -----------------------------------------------
// environment
// -----------------------------------------------

struct String milone_get_cwd(void) {
#if defined(MILONE_PLATFORM_UNIX)
    char buf[FILENAME_MAX + 1];
    bool ok = getcwd(buf, sizeof buf) != NULL;
    if (!ok) {
        perror("getcwd");
        exit(1);
    }

    return string_of_c_str(buf);
#elif defined(MILONE_PLATFORM_WINDOWS)
    TCHAR buf[MAX_PATH + 1] = {0};
    DWORD len = GetCurrentDirectory(sizeof(buf), buf);
    if (len == 0 || len >= sizeof(buf)) {
        failwith("GetCurrentDirectory");
        exit(1);
    }

    return os_string_to((struct OsString){.ptr = buf, .len = len});
#else
#error no platform
#endif
}

// -----------------------------------------------
// file IO
// -----------------------------------------------

// Convert all path separators to `/`. (On windows, `\\` to `/`.)
static struct String milone_platform_normalize_path_sep(struct String path) {
#if defined(MILONE_PLATFORM_UNIX)
    return path;
#elif defined(MILONE_PLATFORM_WINDOWS)
    char *buf = milone_region_alloc(path.len + 1, sizeof(char));
    strncpy(buf, path.ptr, path.len);
    for (size_t i = 0; i < path.len; i++) {
        if (buf[i] == '\\') {
            buf[i] = '/';
        }
    }
    return (struct String){.ptr = buf, .len = path.len};
#else
#error no platform
#endif
}

// Create a single directory (not recursive).
static bool milone_platform_create_single_directory(struct String dir) {
#if defined(MILONE_PLATFORM_UNIX)
    return mkdir(string_to_c_str(dir), 0774) == 0 || errno == EEXIST;
#elif defined(MILONE_PLATFORM_WINDOWS)
    struct OsString d = os_string_of(dir);
    return CreateDirectoryW(d.ptr, NULL) != 0 ||
           GetLastError() == ERROR_ALREADY_EXISTS;
#else
#error no platform
#endif
}

// Create a directory unless it exists.
bool dir_create(struct String dir, struct String base_dir) {
    assert(dir.len != 0);

    dir = milone_platform_normalize_path_sep(dir);
    base_dir = milone_platform_normalize_path_sep(base_dir);

    dir = path_join(base_dir, dir);

    // Span of absolute path.
    char const *const al = dir.ptr;
    char const *const ar = dir.ptr + (size_t)dir.len;

    // Start of basename.
    char const *bl = al;

    while (bl - al < dir.len) {
        if (*bl == '/') {
            bl++;
            continue;
        }

        // Assume a directory at `dir[..bl]` exists.
        // Find the range of basename: `bl..br`.
        char const *br = bl + 1;
        while (br != ar && *br != '/') {
            br++;
        }

        if ((br - bl == 1 && *bl == '.') ||
            (br - bl == 2 && strncmp(bl, "..", 2) == 0)) {
            bl = br;
            continue;
        }

        // Create the directory at `al..br`.
        {
            // FIXME: Unnecessary copying
            struct String d = string_slice(dir, 0, (int)(br - al));

            if (!milone_platform_create_single_directory(d)) {
                return false;
            }
            bl = br;
        }
    }
    return true;
}

// -----------------------------------------------
// processes
// -----------------------------------------------

struct StringCons {
    struct String head;
    struct StringCons const *tail;
};

#if defined(MILONE_PLATFORM_UNIX)

// pass

#elif defined(MILONE_PLATFORM_WINDOWS)

// Combine command and args into single command line string.
// Write to buf.
static void build_cmdline(struct String command, struct StringCons const *args,
                          char *buf, size_t buf_size) {
    size_t total_len = command.len + 2;
    {
        struct StringCons const *a = args;
        while (a != NULL) {
            total_len += a->head.len + 3;
            a = a->tail;
        }
    }
    if (buf_size <= total_len) {
        fprintf(stderr, "error: command line too long\n");
        exit(1);
    }

    size_t i = 0;
    buf[i] = '"';
    i++;

    strncpy(&buf[i], command.ptr, (size_t)command.len);
    i += command.len;

    buf[i] = '"';
    i++;

    {
        struct StringCons const *a = args;
        while (a != NULL) {
            buf[i] = ' ';
            i++;

            buf[i] = '"';
            i++;

            strncpy(&buf[i], a->head.ptr, a->head.len);
            i += a->head.len;

            buf[i] = '"';
            i++;

            a = a->tail;
        }
    }

    assert(i == total_len);
    buf[i] = '\0';
}

static void milone_subprocess_run_windows(struct String cmdline, int *code) {
    PROCESS_INFORMATION process_info = {NULL};
    STARTUPINFO start_info = {sizeof(STARTUPINFO)};

    BOOL ok = CreateProcessW(
        // application name: null to use command line
        NULL,
        // command line
        (LPWSTR)os_string_of(cmdline).ptr,
        // process security attributes
        NULL,
        // primary thread security attributes
        NULL,
        // inherit handles
        TRUE,
        // creation flags
        0,
        // used environment
        NULL,
        // working directory: null to use parent's current directory
        NULL, &start_info, &process_info);
    if (!ok) {
        fprintf(stderr, "error: CreateProcess %d\n", (int)GetLastError());
        exit(1);
    }

    WaitForSingleObject(process_info.hProcess, INFINITE);

    DWORD exit_code = 0;
    ok = GetExitCodeProcess(process_info.hProcess, &exit_code);
    assert(ok && "GetExitCodeProcess");
    *code = (int)exit_code;

    CloseHandle(process_info.hProcess);
    CloseHandle(process_info.hThread);
}

#endif

// Run a subprocess and wait for exit.
// Return exit code.
int milone_subprocess_run(struct String command,
                          struct StringCons const *args) {
#if defined(MILONE_PLATFORM_UNIX)
    // FIXME: see CmdLspServer
    fprintf(stderr, "ERROR: subprocess not implemented on Unix.\n");
    exit(1);
#elif defined(MILONE_PLATFORM_WINDOWS)
    char buf[8000] = "";
    build_cmdline(command, args, buf, sizeof(buf));
    struct String cmdline = string_borrow(buf);

    int code;
    milone_subprocess_run_windows(cmdline, &code);
    return code;
#else
#error no platform
#endif
}

// Turn current process into a shell to execute a command.
void execute_into(struct String cmd) {
#if defined(MILONE_PLATFORM_UNIX)
    char *argv[] = {
        "/bin/sh",
        "-c",
        (char *)string_to_c_str(cmd),
        0,
    };

    int code = execv("/bin/sh", argv);
    assert(code != 0);
    fprintf(stderr, "ERROR: Failed to execute '%s'.\n", string_to_c_str(cmd));
    exit(code);
#elif defined(MILONE_PLATFORM_WINDOWS)
    assert(false && "execute_into isn't supported on Windows\n");
#else
#error no platform
#endif
}

// -----------------------------------------------
// [Windows] UUID generation
// -----------------------------------------------

#if defined(MILONE_PLATFORM_WINDOWS)

// https://docs.microsoft.com/en-us/windows/win32/seccng/cng-portal
// https://docs.microsoft.com/en-us/windows/win32/seccng/cng-algorithm-identifiers

static BCRYPT_ALG_HANDLE rng_create() {
    BCRYPT_ALG_HANDLE h_alg;
    if (BCryptOpenAlgorithmProvider(&h_alg, BCRYPT_RNG_ALGORITHM, NULL, 0) != 0) {
        failwith("BCryptCloseAlgorithmProvider");
    }
    return h_alg;
}

static void rng_destroy(BCRYPT_ALG_HANDLE h_alg) {
    BCryptCloseAlgorithmProvider(h_alg, 0);
}

static void rng_random_bytes(BCRYPT_ALG_HANDLE h_alg, uint8_t *buf, int len) {
    assert(len >= 0);
    if (len == 0) return;

    assert(buf != NULL);

    if (BCryptGenRandom(h_alg, (PUCHAR)buf, (ULONG)len, 0) != 0) {
        failwith("BCryptGenRandom");
    }
}

struct String milone_uuid(void) {
    BCRYPT_ALG_HANDLE rng = rng_create();
    uint8_t buf[16];
    rng_random_bytes(rng, buf, sizeof(buf));
    rng_destroy(rng);

    buf[6] = buf[6] & 0b01001111 | 0b01000000; // version
    buf[8] = buf[8] & 0b10111111 | 0b10000000; // variant

    char s[36 + 1] = "";
    sprintf(
        s,
        "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
        buf[0x0], buf[0x1], buf[0x2], buf[0x3],
        buf[0x4], buf[0x5], buf[0x6], buf[0x7],
        buf[0x8], buf[0x9], buf[0xa], buf[0xb],
        buf[0xc], buf[0xd], buf[0xe], buf[0xf]
    );
    return string_of_c_str(s);
}

#else

_Noreturn struct String milone_uuid(void) {
    failwith("uuid not supported on linux");
}

#endif
