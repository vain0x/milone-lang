#include <assert.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <milone.h>

// -----------------------------------------------
// buffer
// -----------------------------------------------

struct Buffer {
    char *ptr;
    int len;
};

int buffer_get_length(void const *buf) {
    return ((struct Buffer const *)buf)->len;
}

// -----------------------------------------------
// file IO
// -----------------------------------------------

int file_open_read(struct String path) { return open(path.ptr, O_RDONLY); }

int file_close(int fd) {
    assert(fd >= 0);
    return close(fd);
}

void const *file_read_bytes(int fd, int len) {
    assert(fd >= 0);

    struct Buffer *buf = milone_region_alloc(1, sizeof(struct Buffer));
    buf->ptr = milone_region_alloc(len + 1, sizeof(char));
    buf->len = len;

    // fprintf(stderr, "reading fd=%d buf ptr=%p len=%d\n", fd, buf->ptr,
    //         buf->len);

    int n = read(fd, buf->ptr, buf->len);
    if (n < 0) {
        return NULL;
    }

    buf->len = n;
    return buf;
}

int file_write_bytes(int fd, void const *src, int src_epoch) {
    assert(fd >= 0);

    struct Buffer *buf = (struct Buffer *)src;
    if (buf->len == 0) {
        return 0;
    }

    return write(fd, buf->ptr, buf->len);
}
