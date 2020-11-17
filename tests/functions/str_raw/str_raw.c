#include "milone.h"

int testEol_(int arg_);

int testNoEscape_(int arg_1);

int main();

int testEol_(int arg_) {
    struct String eol_ = (struct String){.str = "\n", .len = 1};
    int if_;
    if ((str_cmp(eol_, (struct String){.str = "\n", .len = 1}) != 0)) goto else_1;
    if_ = 1;
    goto end_if_2;
else_1:;
    if_ = (str_cmp(eol_, (struct String){.str = "\r\n", .len = 2}) == 0);
end_if_2:;
    milone_assert(if_, 3, 2);
    int call_ = 0;
    return 0;
}

int testNoEscape_(int arg_1) {
    milone_assert((str_cmp((struct String){.str = " \\\"\" ", .len = 5}, (struct String){.str = " \\\"\" ", .len = 5}) == 0), 6, 2);
    int call_1 = 0;
    return 0;
}

int main() {
    int call_2 = testEol_(0);
    int call_3 = testNoEscape_(0);
    return 0;
}
