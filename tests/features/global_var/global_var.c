#include "milone.h"

int global_var_Program_f(void);

int global_var_Program_g(void);

int milone_main(void);

extern int global_var_Program_success;

int global_var_Program_success;

int failure_;

extern int failure_;

int global_var_Program_f(void) {
    return global_var_Program_success;
}

int global_var_Program_g(void) {
    int call_ = global_var_Program_f();
    return call_;
}

int milone_main(void) {
    global_var_Program_success = 0;
    failure_ = 1;
    int call_1 = global_var_Program_g();
    milone_assert((call_1 == 0), 13, 2);
    milone_assert((failure_ == 1), 14, 2);
    return 0;
}
