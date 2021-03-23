#include "milone.h"

int global_var_Program_f(char arg_);

int global_var_Program_g(char arg_1);

int milone_main();

int global_var_Program_success;

static int failure_;

int global_var_Program_f(char arg_) {
    return global_var_Program_success;
}

int global_var_Program_g(char arg_1) {
    int call_ = global_var_Program_f(0);
    return call_;
}

int milone_main() {
    global_var_Program_success = 0;
    failure_ = 1;
    int call_1 = global_var_Program_g(0);
    milone_assert((call_1 == 0), 13, 2);
    milone_assert((failure_ == 1), 14, 2);
    return 0;
}
