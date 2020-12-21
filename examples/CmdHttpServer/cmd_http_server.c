// Works on Linux only.
// Current code is not http server yet.

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

static int open_connection(char const *hostname, char const *service);

int do_serve() {
    char const *hostname = "localhost";

    int sock = open_connection(hostname, "daytime");
    FILE *f = fdopen(sock, "r");
    if (f == NULL) {
        perror("fdopen");
        exit(1);
    }

    char buf[1024] = {};
    fgets(buf, sizeof(buf), f);
    fclose(f);
    fputs(buf, stdout);
    return 0;
}

int open_connection(char const *hostname, char const *service) {
    struct addrinfo hints = {
        .ai_family = AF_UNSPEC,
        .ai_socktype = SOCK_STREAM,
    };
    struct addrinfo *res;
    int err = getaddrinfo(hostname, service, &hints, &res);
    if (err != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(err));
        exit(1);
    }

    for (struct addrinfo *ai = res; ai != NULL; ai = ai->ai_next) {
        int sock = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
        if (sock < 0) {
            continue;
        }

        int stat = connect(sock, ai->ai_addr, ai->ai_addrlen);
        if (stat != 0) {
            close(sock);
            continue;
        }

        // Success. res is alloacted and needs to be freed by caller.
        freeaddrinfo(res);
        return sock;
    }

    fprintf(stderr, "socket/connect failed\n");
    freeaddrinfo(res);
    exit(1);
}

// try: sudo apt install xinetd
//      sudo nano /etc/xinetd.d/daytime # edit disable = no
//      sudo systemctl reload xinetd
//      netstat -l | grep daytime # check
//      make && target/serve
