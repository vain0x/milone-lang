#include "milone.h"

char addTest_(char arg_);

char compareTest_(char arg_1);

char at_(int i_, struct String s_);

char indexOperatorTest_(char arg_2);

char subscriptOperatorTest_(char arg_3);

int milone_main();

char addTest_(char arg_) {
    struct String hello_ = (struct String){.str = "Hello", .len = 5};
    struct String world_ = (struct String){.str = ", world!", .len = 8};
    milone_assert((str_compare(str_add(hello_, world_), (struct String){.str = "Hello, world!", .len = 13}) == 0), 5, 2);
    milone_assert((str_add((struct String){.str = "a", .len = 1}, (struct String){.str = "\0b", .len = 2}).str[2] == 'b'), 8, 2);
    return 0;
}

char compareTest_(char arg_1) {
    milone_assert((str_compare((struct String){.str = "", .len = 0}, (struct String){.str = "", .len = 0}) == 0), 11, 2);
    milone_assert((str_compare((struct String){.str = "o", .len = 1}, (struct String){.str = "o", .len = 1}) == 0), 12, 2);
    milone_assert((str_compare((struct String){.str = "alpha", .len = 5}, (struct String){.str = "alpha", .len = 5}) == 0), 13, 2);
    milone_assert((str_compare((struct String){.str = "a", .len = 1}, (struct String){.str = "b", .len = 1}) < 0), 15, 2);
    milone_assert((str_compare((struct String){.str = "alpha", .len = 5}, (struct String){.str = "beta", .len = 4}) < 0), 16, 2);
    milone_assert((str_compare((struct String){.str = "a", .len = 1}, (struct String){.str = "z", .len = 1}) < 0), 18, 2);
    milone_assert((str_compare((struct String){.str = "alpha", .len = 5}, (struct String){.str = "beta", .len = 4}) < 0), 20, 2);
    milone_assert((str_compare((struct String){.str = "alpha", .len = 5}, (struct String){.str = "alpha", .len = 5}) == 0), 21, 2);
    milone_assert((0 < str_compare((struct String){.str = "beta", .len = 4}, (struct String){.str = "alpha", .len = 5})), 22, 2);
    milone_assert((str_compare((struct String){.str = "\0x", .len = 2}, (struct String){.str = "\0y", .len = 2}) < 0), 25, 2);
    return 0;
}

char at_(int i_, struct String s_) {
    return s_.str[i_];
}

char indexOperatorTest_(char arg_2) {
    struct String hello_1 = (struct String){.str = "hello", .len = 5};
    bool if_;
    if ((hello_1.str[0] == 'h')) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    if_ = (hello_1.str[4] == 'o');
    goto if_next_1;
else_3:;
    if_ = false;
    goto if_next_1;
if_next_1:;
    milone_assert(if_, 33, 2);
    char call_ = at_(0, hello_1);
    milone_assert((call_ == 'h'), 38, 2);
    return 0;
}

char subscriptOperatorTest_(char arg_3) {
    struct String str_ = (struct String){.str = "Hello, John!", .len = 12};
    struct String slice_ = str_get_slice(0, 4, str_);
    milone_assert((str_compare(slice_, (struct String){.str = "Hello", .len = 5}) == 0), 42, 2);
    struct String slice_1 = str_get_slice(7, 10, str_);
    milone_assert((str_compare(slice_1, (struct String){.str = "John", .len = 4}) == 0), 43, 2);
    struct String slice_2 = str_get_slice(11, 11, str_);
    milone_assert((str_compare(slice_2, (struct String){.str = "!", .len = 1}) == 0), 44, 2);
    return 0;
}

int milone_main() {
    char call_1 = addTest_(0);
    char call_2 = compareTest_(0);
    char call_3 = indexOperatorTest_(0);
    char call_4 = subscriptOperatorTest_(0);
    return 0;
}
