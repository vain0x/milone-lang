#include "milone.h"

int main();

int main() {
    struct String hello_ = (struct String){.str = "hello", .len = 5};
    struct String world_ = (struct String){.str = "world", .len = 5};
    milone_assert((hello_.len == 5), 4, 2);
    int call_ = 0;
    struct String message_ = str_add(hello_, world_);
    milone_assert((message_.len == 10), 7, 2);
    int call_1 = 0;
    milone_assert((hello_.len == 5), 9, 2);
    int call_2 = 0;
    milone_assert((5 == 5), 11, 2);
    int call_3 = 0;
    return 0;
}
