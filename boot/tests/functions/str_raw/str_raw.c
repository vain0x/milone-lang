#include "milone.h"

int testEol_(int arg_);

int testNoEscape_(int arg_1);

int main();

int testEol_(int arg_) {
    struct String eol_ = (struct String){.str = "\n", .len = 1};
    int match_;
    if (!(((str_cmp(eol_, (struct String){.str = "\n", .len = 1}) == 0) == 1))) goto next_2;
    match_ = 1;
    goto end_match_1;
next_2:;
    if (!(((str_cmp(eol_, (struct String){.str = "\n", .len = 1}) == 0) == 0))) goto next_3;
    match_ = (str_cmp(eol_, (struct String){.str = "\r\n", .len = 2}) == 0);
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    milone_assert(match_);
    int call_ = 0;
    return 0;
}

int testNoEscape_(int arg_1) {
    milone_assert((str_cmp((struct String){.str = " \\\"\" ", .len = 5}, (struct String){.str = " \\\"\" ", .len = 5}) == 0));
    int call_1 = 0;
    return 0;
}

int main() {
    int call_2 = testEol_(0);
    int call_3 = testNoEscape_(0);
    return 0;
}
