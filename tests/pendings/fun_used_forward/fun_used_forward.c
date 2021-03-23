#include "milone.h"

int fun_used_forward_Program_f(char arg_);

int fun_used_forward_Program_g(char arg_1);

int milone_main();

int fun_used_forward_Program_f(char arg_) {
    int call_ = fun_used_forward_Program_g(0);
    return call_;
}

int fun_used_forward_Program_g(char arg_1) {
    return 0;
}

int milone_main() {
    int call_1 = fun_used_forward_Program_f(0);
    milone_assert((call_1 == 0), 17, 2);
    return 0;
}
