#include "milone.h"

int nav_var_sub_getAnswer(char arg_);

int milone_main();

int nav_var_sub_answer;

int nav_var_sub_getAnswer(char arg_) {
    return 42;
}

int milone_main() {
    nav_var_sub_answer = 42;
    milone_assert((nav_var_sub_answer == 42), 8, 2);
    int call_ = nav_var_sub_getAnswer(0);
    milone_assert((call_ == 42), 11, 2);
    int myAnswer_ = 42;
    return 0;
}
