#include "milone.h"

int testBinarySafe_(int arg_);

int main();

int testBinarySafe_(int arg_) {
    milone_assert((str_cmp((struct String){.str = "\0x", .len = 2}, (struct String){.str = "\0y", .len = 2}) < 0), 1, 2);
    int call_ = 0;
    return 0;
}

int main() {
    int le_ = (str_cmp((struct String){.str = "a", .len = 1}, (struct String){.str = "b", .len = 1}) < 0);
    int eq_ = (str_cmp((struct String){.str = "o", .len = 1}, (struct String){.str = "o", .len = 1}) == 0);
    int match_;
    if ((!(le_))) goto next_2;
    match_ = eq_;
    goto end_match_1;
next_2:;
    if (le_) goto next_3;
    match_ = 0;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    milone_assert(match_, 6, 2);
    int call_1 = 0;
    int call_2 = testBinarySafe_(0);
    return 0;
}
