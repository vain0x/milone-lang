// Works on Linux only.

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

struct StringUnitFun1 {
    void (*fun)(void const *, struct String);
    void const *env;
};

typedef void (*request_handler_t)(struct String method, struct String pathname,
                                  struct String date, struct String dist_dir,
                                  int protocol_minor_version,
                                  struct StringUnitFun1 write_string);

struct MiloneProfiler;
struct MiloneProfiler *milone_profile_init(void);
void milone_profile_log(struct String msg, struct MiloneProfiler *profiler);

struct String milone_get_env(struct String name);

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

static void noop_handler(int sig) { (void)sig; }

static void detach_children(void) {
    sigset_t mask;
    sigemptyset(&mask);
    struct sigaction act = {
        .sa_handler = noop_handler,
        .sa_mask = mask,
        .sa_flags = SA_RESTART | SA_NOCLDWAIT,
    };

    int stat = sigaction(SIGCHLD, &act, NULL);
    if (stat < 0) {
        log_exit("sigaction() failed: %s", strerror(errno));
    }
}

static void install_signal_handlers() {
    trap_signal(SIGINT, signal_exit);
    trap_signal(SIGTERM, signal_exit);
    trap_signal(SIGPIPE, signal_exit);
    detach_children();
}

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

static struct String get_date() {
    time_t t;
    time(&t);
    struct tm *tm = gmtime(&t);
    if (tm == NULL) {
        log_exit("gmtime() failed: %s", strerror(errno));
    }

    char date_value[64];
    size_t len = strftime(date_value, sizeof(date_value),
                          "%a, %d %b %Y %H:%M:%S GMT", tm);
    return str_of_raw_parts(date_value, (int)len);
}

static void do_write_string(void const *env, struct String value) {
    fprintf((FILE *)env, "%s", str_to_c_str(value));
}

static struct String get_dist_dir(void) {
    struct String dist_dir = milone_get_env(str_borrow("DIST_DIR"));
    if (str_compare(dist_dir, str_borrow("")) != 0) {
        return dist_dir;
    }

    // Default to $PWD/dist.
    {
        char buf[FILENAME_MAX];
        bool ok = getcwd(buf, sizeof buf) != NULL;
        if (!ok) {
            fprintf(stderr, "error: getcwd failed\n");
            exit(1);
        }

        return str_add(str_borrow(buf), str_borrow("/dist"));
    }
}

static void http_service(FILE *in, FILE *out, request_handler_t handler) {
    struct Req *req = read_req(in);

    // struct MiloneProfiler *p = milone_profile_init();
    // milone_profile_log(str_borrow("handle begin"), p);
    milone_enter_region();

    {
        struct StringUnitFun1 write_string = (struct StringUnitFun1){
            .env = out,
            .fun = do_write_string,
        };
        handler(str_borrow(req->method), str_borrow(req->path), get_date(),
                get_dist_dir(), req->protocol_minor_version, write_string);
        fflush(out);
    }

    milone_leave_region();
    // milone_profile_log(str_borrow("handle end"), p);

    free_req(req);
}

// -----------------------------------------------
// Entrypoint
// -----------------------------------------------

static int const MAX_BACKLOG = 5;
static char const *const port = "8080";

static int listen_socket() {
    struct addrinfo hints = {
        .ai_family = AF_INET,
        .ai_socktype = SOCK_STREAM,
        .ai_flags = AI_PASSIVE,
    };
    struct addrinfo *res;
    int err = getaddrinfo(NULL, port, &hints, &res);
    if (err != 0) {
        log_exit(gai_strerror(err));
    }

    for (struct addrinfo *ai = res; ai != NULL; ai = ai->ai_next) {
        int sock = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
        if (sock < 0) {
            continue;
        }

        int stat = bind(sock, ai->ai_addr, ai->ai_addrlen);
        if (stat < 0) {
            close(sock);
            continue;
        }

        stat = listen(sock, MAX_BACKLOG);
        if (stat < 0) {
            close(sock);
            continue;
        }

        // Success.
        freeaddrinfo(res);
        return sock;
    }

    log_exit("failed to listen socket");
}

_Noreturn void do_serve(request_handler_t handler) {
    install_signal_handlers();

    int server_fd = listen_socket();
    fprintf(stderr, "INFO: Listening to http://localhost:8080\n");

    while (true) {
        struct sockaddr_storage addr;
        socklen_t addr_len = sizeof addr;
        int sock = accept(server_fd, (struct sockaddr *)&addr, &addr_len);
        if (sock < 0) {
            log_exit("accept(2) failed: %s", strerror(errno));
        }

        int pid = fork();
        if (pid < 0) {
            exit(3);
        }
        if (pid == 0) {
            // Child process.

            FILE *input = fdopen(sock, "r");
            FILE *output = fdopen(sock, "w");

            http_service(input, output, handler);
            exit(0);
        }

        close(sock);
    }
}
