#include "milone.h"

char at_(int i_, struct String s_);

int main();

char at_(int i_, struct String s_) {
    return s_.str[i_];
}

int main() {
    struct String hello_ = (struct String){.str = "hello", .len = 5};
    int if_;
    if ((hello_.str[0] != 'h')) goto else_1;
    if_ = (hello_.str[4] == 'o');
    goto end_if_2;
else_1:;
    if_ = 0;
end_if_2:;
    milone_assert(if_, 2, 2);
    int call_ = 0;
    char call_1 = at_(0, hello_);
    milone_assert((call_1 == 'h'), 7, 2);
    int call_2 = 0;
    return 0;
}
