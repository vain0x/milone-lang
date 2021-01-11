// Works on Linux only.
// Current code is not http server yet.

#include <errno.h>
#include <netdb.h>
#include <signal.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include <milone.h>

#define SERVER_NAME "httpd"
#define SERVER_VERSION "0.1.0"

typedef struct String (*request_handler_t)(struct String method,
                                           struct String pathname);

struct MiloneProfiler;
struct MiloneProfiler *milone_profile_init(void);
void milone_profile_log(struct String msg, struct MiloneProfiler *profiler);

// -----------------------------------------------
// Error
// -----------------------------------------------

_Noreturn static void log_exit(char const *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    fputc('\n', stderr);
    va_end(ap);
    exit(1);
}

// -----------------------------------------------
// Memory
// -----------------------------------------------

static void *xcalloc(size_t count, size_t size) {
    void *p = calloc(count, size);
    if (p == NULL) {
        log_exit("out of memory");
    }
    return p;
}

// -----------------------------------------------
// Signals
// -----------------------------------------------

_Noreturn static void signal_exit(int sig) {
    log_exit("exit by signal %d", sig);
}

static void trap_signal(int sig, __sighandler_t handler) {
    __sigset_t mask;
    sigemptyset(&mask);

    struct sigaction act = (struct sigaction){
        .sa_handler = handler,
        .sa_mask = mask,
        .sa_flags = SA_RESTART,
    };
    int stat = sigaction(sig, &act, NULL);
    if (stat < 0) {
        log_exit("sigaction() failed: %s", strerror(errno));
    }
}

static void install_signal_handlers() { trap_signal(SIGPIPE, signal_exit); }

// -----------------------------------------------
// HTTP
// -----------------------------------------------

struct Entry {
    char *name;
    char *value;
    struct Entry *next;
};

struct Req {
    int protocol_minor_version;
    char *method;
    char *path;
    struct Entry *headers;
};

static void free_entry_recursive(struct Entry *entry) {
    while (entry != NULL) {
        struct Entry *e = entry;
        entry = entry->next;

        free(e->name);
        free(e->value);
        free(e);
    }
}

static void free_req(struct Req *req) {
    free(req->method);
    free(req->path);
    free_entry_recursive(req->headers);
    free(req);
}

// Reads `GET ...` line.
static void read_request_line(struct Req *req, FILE *in) {
    char buf[0x8000];
    bool ok = fgets(buf, sizeof(buf), in) != NULL;
    if (!ok) {
        log_exit("read_request_line: expected a line");
    }

    char const *method = buf;
    char *p = strchr(buf, ' ');
    if (!p) {
        log_exit("read_request_line: expected method");
    }
    *p = '\0';
    p++;
    req->method = strdup(buf);

    char const *path = p;
    p = strchr(path, ' ');
    *p = '\0';
    p++;
    req->path = strdup(path);

    if (strncasecmp(p, "HTTP/1.", strlen("HTTP/1.")) != 0) {
        log_exit("read_request_line: expected protocol version");
    }
    p += strlen("HTTP/1.");
    req->protocol_minor_version = atoi(p);
}

// Returns true if success, and then entry{.name, .value} is filled.
// Returns false if empty (entry is unused).
// No return if error.
static bool read_header_field(FILE *in, struct Entry *entry) {
    char buf[0x8000];
    bool ok = fgets(buf, sizeof(buf), in) != NULL;
    if (!ok) {
        log_exit("read_header_field: expected a line");
    }

    if (buf[0] == '\n' || strcmp(buf, "\r\n") == 0) {
        return false;
    }

    char *p = strchr(buf, ':');
    if (p == NULL) {
        log_exit("read_header_field: expected ':' in header line. %s", buf);
    }
    *p = '\0';
    p += strspn(p, " \t");

    entry->name = strdup(buf);
    entry->value = strdup(p);
    return true;
}

static bool find_header(struct Req *req, char const *header,
                        char const **value_ptr) {
    for (struct Entry *entry = req->headers; entry != NULL;
         entry = entry->next) {
        if (strcasecmp(entry->name, header) == 0) {
            *value_ptr = entry->value;
            return true;
        }
    }
    return false;
}

static size_t content_length(struct Req *req) {
    char const *value;
    bool ok = find_header(req, "Content-Length", &value);
    if (!ok) {
        return 0;
    }

    long len = atol(value);
    if (len < 0) {
        log_exit("negative content-length. %ld", len);
    }

    return (size_t)len;
}

// data is discarded
static void read_req_body(FILE *in, size_t len) {
    if (len > 0x100000) {
        // FIXME: this should not be a fatal error.
        log_exit("request body too long");
    }

    char buf[0x1000];
    size_t rest = len;
    while (rest != 0) {
        size_t read_size = sizeof buf;
        if (read_size > len) {
            read_size = len;
        }
        size_t n = fread(buf, read_size, 1, in);
        if (n != 1) {
            log_exit("failed to read request body: %s", strerror(errno));
        }
        rest -= read_size;
    }
}

static struct Req *read_req(FILE *in) {
    struct Req *req = xcalloc(1, sizeof(struct Req));

    read_request_line(req, in);

    while (true) {
        struct Entry entry = {};
        bool found = read_header_field(in, &entry);
        if (!found) {
            break;
        }

        struct Entry *headers = xcalloc(1, sizeof(struct Entry));
        *headers = (struct Entry){
            .name = entry.name,
            .value = entry.value,
            .next = req->headers,
        };
        req->headers = headers;

        size_t len = content_length(req);
        read_req_body(in, len);
    }

    return req;
}

static void write_common_res_headers(struct Req *req, FILE *out,
                                     char const *status_text) {
    time_t t;
    time(&t);
    struct tm *tm = gmtime(&t);
    if (tm == NULL) {
        log_exit("gmtime() failed: %s", strerror(errno));
    }

    char date_value[64];
    strftime(date_value, sizeof(date_value), "%a, %d %b %Y %H:%M:%S GMT", tm);

    fprintf(out, "HTTP/1.%d %s\r\n", req->protocol_minor_version, status_text);
    fprintf(out, "Date: %s\r\n", date_value);
    fprintf(out, "Server: %s/%s\r\n", SERVER_NAME, SERVER_VERSION);
    fprintf(out, "Connection: close\r\n");
}

static void write_res_with_body(struct Req *req, FILE *out, uint8_t const *body,
                                size_t len, bool write_body) {
    write_common_res_headers(req, out, "200 OK");
    fprintf(out, "Content-Length: %ld\r\n", len);
    fprintf(out, "Content-Type: text/plain\r\n");
    fprintf(out, "\r\n");

    if (write_body) {
        size_t n = fwrite(body, len, 1, out);
        if (n != 1) {
            log_exit("failed to write to socket: %s", strerror(errno));
        }
    }
    fflush(out);
}

static void http_service(FILE *in, FILE *out, request_handler_t handler) {
    struct Req *req = read_req(in);

    struct MiloneProfiler *p = milone_profile_init();
    milone_profile_log(str_borrow("handle begin"), p);
    milone_enter_region();
    bool write_body = strcmp(req->method, "HEAD") != 0;
    struct String result =
        handler(str_borrow(req->method), str_borrow(req->path));
    write_res_with_body(req, out, (uint8_t const *)result.str, result.len,
                        write_body);
    milone_leave_region();
    milone_profile_log(str_borrow("handle end"), p);

    free_req(req);
}

// -----------------------------------------------
// Entrypoint
// -----------------------------------------------

int do_serve(request_handler_t handler) {
    install_signal_handlers();
    http_service(stdin, stdout, handler);
    return 0;
}
