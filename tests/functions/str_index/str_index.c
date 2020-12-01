#include "milone.h"

char at_(int i_, struct String s_);

int main();

char at_(int i_, struct String s_) {
    return s_.str[i_];
}

int main() {
    struct String hello_ = (struct String){.str = "hello", .len = 5};
    bool if_;
    if ((hello_.str[0] == 'h')) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    if_ = (hello_.str[4] == 'o');
    goto if_next_1;
else_3:;
    if_ = false;
    goto if_next_1;
if_next_1:;
    milone_assert(if_, 2, 2);
    char call_ = at_(0, hello_);
    milone_assert((call_ == 'h'), 7, 2);
    return 0;
}
