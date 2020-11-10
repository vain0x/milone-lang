#include "milone.h"

int testBinarySafe_(int arg_);

int main();

int testBinarySafe_(int arg_) {
    milone_assert((str_add((struct String){.str = "a", .len = 1}, (struct String){.str = "\0b", .len = 2}).str[2] == 'b'), 1, 2);
    int call_ = 0;
    return 0;
}

int main() {
    struct String hello_ = (struct String){.str = "Hello", .len = 5};
    struct String world_ = (struct String){.str = ", world!", .len = 8};
    printf("%s\n", str_add(hello_, world_).str);
    int call_1 = 0;
    int call_2 = testBinarySafe_(0);
    return 0;
}
