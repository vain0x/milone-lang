#include "milone.h"

int testBasicCase_(int arg_);

int testBinarySafe_(int arg_1);

int testCompareFun_(int arg_2);

int main();

int testBasicCase_(int arg_) {
    milone_assert((str_cmp((struct String){.str = "a", .len = 1}, (struct String){.str = "b", .len = 1}) < 0), 1, 2);
    milone_assert((str_cmp((struct String){.str = "alpha", .len = 5}, (struct String){.str = "beta", .len = 4}) < 0), 2, 2);
    milone_assert((str_cmp((struct String){.str = "", .len = 0}, (struct String){.str = "", .len = 0}) == 0), 4, 2);
    milone_assert((str_cmp((struct String){.str = "o", .len = 1}, (struct String){.str = "o", .len = 1}) == 0), 5, 2);
    milone_assert((str_cmp((struct String){.str = "a", .len = 1}, (struct String){.str = "z", .len = 1}) < 0), 7, 2);
    return 0;
}

int testBinarySafe_(int arg_1) {
    milone_assert((str_cmp((struct String){.str = "\0x", .len = 2}, (struct String){.str = "\0y", .len = 2}) < 0), 10, 2);
    return 0;
}

int testCompareFun_(int arg_2) {
    milone_assert((str_cmp((struct String){.str = "a", .len = 1}, (struct String){.str = "b", .len = 1}) < 0), 13, 2);
    milone_assert((str_cmp((struct String){.str = "a", .len = 1}, (struct String){.str = "a", .len = 1}) == 0), 14, 2);
    milone_assert((0 < str_cmp((struct String){.str = "b", .len = 1}, (struct String){.str = "a", .len = 1})), 15, 2);
    return 0;
}

int main() {
    int call_ = testBasicCase_(0);
    int call_1 = testBinarySafe_(0);
    int call_2 = testCompareFun_(0);
    return 0;
}
