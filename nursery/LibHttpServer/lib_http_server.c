#include <assert.h>
#include <errno.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// linux
#include <netdb.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

// milone
#include <milone.h>

// -----------------------------------------------
// signal
// -----------------------------------------------

static void noop_handler(int sig) { (void)sig; }

static void signal_exit(int sig) {
    fprintf(stderr, "error: exit by signal %d\n", sig);
    exit(128 + sig);
}

static void trap_signal(int sig, __sighandler_t handler) {
    __sigset_t mask;
    sigemptyset(&mask);

    struct sigaction act = {
        .sa_handler = handler,
        .sa_mask = mask,
        .sa_flags = SA_RESTART,
    };
    if (sigaction(sig, &act, NULL) < 0) {
        fprintf(stderr, "error: sigaction: %s\n", strerror(errno));
        exit(1);
    }
}

static void detach_children(void) {
    sigset_t mask;
    sigemptyset(&mask);
    struct sigaction act = {
        .sa_handler = noop_handler,
        .sa_mask = mask,
        .sa_flags = SA_RESTART | SA_NOCLDWAIT,
    };

    if (sigaction(SIGCHLD, &act, NULL) < 0) {
        fprintf(stderr, "error: sigaction: %s\n", strerror(errno));
        exit(1);
    }
}

void install_signal_handlers(void) {
    trap_signal(SIGINT, signal_exit);
    trap_signal(SIGTERM, signal_exit);
    trap_signal(SIGPIPE, signal_exit);
    detach_children();
}

// -----------------------------------------------
// socket
// -----------------------------------------------

static int const MAX_BACKLOG = 5;

static int s_current_fd = -1;

void set_current_fd(int current_fd) {
    // fprintf(stderr, "set server %d\n", current_fd);
    s_current_fd = current_fd;
}

void close_current_fd(void) {
    int current_fd = s_current_fd;
    s_current_fd = -1;

    // fprintf(stderr, "close fd=%d (if >= 0)\n", current_fd);
    if (current_fd >= 0) {
        close(current_fd);
    }
}

// Listen to a port. Return socket file descriptor.
int listen_socket(struct String port) {
    struct addrinfo hints = {
        .ai_flags = AI_PASSIVE,
        .ai_family = AF_INET,
        .ai_socktype = SOCK_STREAM,
    };
    struct addrinfo *res;
    int err = getaddrinfo(NULL, string_to_c_str(port), &hints, &res);
    if (err != 0) {
        fprintf(stderr, "error: %s\n", gai_strerror(err));
        exit(1);
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

    fprintf(stderr, "error: failed to listen. (%s)\n", strerror(errno));
    exit(1);
}

// Wait for client. Return socket file descriptor for client.
int accept_client(int server_fd) {
    struct sockaddr_storage addr;
    socklen_t addr_len = sizeof addr;
    int sock = accept(server_fd, (struct sockaddr *)&addr, &addr_len);
    if (sock < 0) {
        fprintf(stderr, "error: accept(2) failed: %s\n", strerror(errno));
        exit(1);
    }
    return sock;
}

// -----------------------------------------------
// platform
// -----------------------------------------------

bool get_date(char *buf, int buf_size, int *len) {
    assert(buf != NULL);
    assert(buf_size >= 1);
    assert(len != NULL);

    time_t t;
    time(&t);
    struct tm *tm = gmtime(&t);
    if (tm == NULL) {
        return false;
    }

    size_t result = strftime(buf, buf_size, "%a, %d %b %Y %H:%M:%S GMT", tm);
    if (result == 0) {
        return false;
    }

    *len = (int)result;
    return true;
}

struct String get_env(struct String name) {
    char const *value = getenv(string_to_c_str(name));
    if (value == NULL) {
        return string_borrow("");
    }

    return string_of_c_str(value);
}

struct String get_cwd(void) {
    char buf[FILENAME_MAX + 1];
    bool ok = getcwd(buf, sizeof buf) != NULL;
    if (!ok) {
        fprintf(stderr, "error: getcwd failed\n");
        exit(1);
    }

    return string_of_c_str(buf);
}
