#include "milone.h"

char at_(int i_, struct String s_);

int main();

char at_(int i_, struct String s_) {
    return s_.str[i_];
}

int main() {
    struct String hello_ = (struct String){.str = "hello", .len = 5};
    int match_;
    if (!(((hello_.str[0] == 'h') == 1))) goto next_2;
    match_ = (hello_.str[4] == 'o');
    goto end_match_1;
next_2:;
    if (!(((hello_.str[0] == 'h') == 0))) goto next_3;
    match_ = 0;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    milone_assert(match_, 2, 2);
    int call_ = 0;
    char call_1 = at_(0, hello_);
    milone_assert((call_1 == 'h'), 7, 2);
    int call_2 = 0;
    return 0;
}
