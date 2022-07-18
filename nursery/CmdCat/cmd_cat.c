// Only for Linux.

#include <errno.h>
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
// file IO
// -----------------------------------------------

int32_t fd_open_read(struct String pathname) { return open(string_to_c_str(pathname), O_RDONLY); }

int32_t fd_close(uint32_t fd) { return close((int)fd); }

bool fd_read_bytes(uint32_t fd, void *buf, uint32_t buf_size, uint32_t *read_size) {
    fprintf(stderr, "trace: read fd:%d size:%d\n", fd, (int)buf_size);

    assert(buf != NULL);
    assert(buf_size < (1UL << 31));
    assert(read_size != NULL);

    long long n = read((int)fd, buf, buf_size);
    if (n < 0 || n >= (1LL << 31)) {
        fprintf(stderr, "trace: read failed\n");
        return false;
    }

    fprintf(stderr, "trace:   -> read:%d\n", (uint32_t)n);
    *read_size = (uint32_t)n;
    return true;
}

void fd_write_bytes(uint32_t fd, void const *src, uint32_t size) {
    assert(src != NULL);

    fprintf(stderr, "trace: write fd:%d size:%d\n", fd, size);

    while (size >= 1) {
        ssize_t n = write((int)fd, src, size);
        if (n == 0 || n == -1) {
            fprintf(stderr, "%s\n", strerror(errno));
            fprintf(stderr, "trace: write failed\n");
            exit(1);
        }

        assert((uint32_t)n <= size);
        if (n >= size) break;

        src = (uint8_t *)src + (uint32_t)n;
        size -= (uint32_t)n;
    }
}
