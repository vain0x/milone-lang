#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <milone.h>

struct String stdin_read_all(void) {
    size_t len = 0;
    size_t cap = 0x1000;
    char *s = malloc(cap * sizeof(char));

    while (true) {
        if (len >= 0x1000000) {
            fprintf(stderr, "stdin too long\n");
            exit(1);
        }

        if (len + 1 == cap) {
            cap *= 2;
            s = realloc(s, cap);
        }

        size_t n = fread(&s[len], 1, cap - len - 1, stdin);
        if (n == 0) {
            break;
        }
        len += n;
    }

    struct String result = str_of_raw_parts(s, len);
    free(s);
    return result;
}
