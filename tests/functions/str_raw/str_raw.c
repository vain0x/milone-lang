#include "milone.h"

int testEol_(int arg_);

int testNoEscape_(int arg_1);

int main();

int testEol_(int arg_) {
    struct String eol_ = (struct String){.str = "\n", .len = 1};
    bool if_;
    if ((str_cmp(eol_, (struct String){.str = "\n", .len = 1}) == 0)) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    if_ = true;
    goto if_next_1;
else_3:;
    if_ = (str_cmp(eol_, (struct String){.str = "\r\n", .len = 2}) == 0);
    goto if_next_1;
if_next_1:;
    milone_assert(if_, 3, 2);
    return 0;
}

int testNoEscape_(int arg_1) {
    milone_assert((str_cmp((struct String){.str = " \\\"\" ", .len = 5}, (struct String){.str = " \\\"\" ", .len = 5}) == 0), 6, 2);
    return 0;
}

int main() {
    int call_ = testEol_(0);
    int call_1 = testNoEscape_(0);
    return 0;
}
