#include "milone.h"

int main();

int main() {
    struct String hello_ = (struct String){.str = "hello", .len = 5};
    struct String world_ = (struct String){.str = "world", .len = 5};
    milone_assert((hello_.len == 5), 8, 2);
    struct String message_ = str_add(hello_, world_);
    milone_assert((message_.len == 10), 11, 2);
    milone_assert((hello_.len == 5), 13, 2);
    milone_assert((5 == 5), 17, 2);
    milone_assert((3 == 3), 20, 2);
    return 0;
}
