#include "milone.h"

int module_forward_reference_bug_Program_Early_f(char arg_);

int module_forward_reference_bug_Program_Late_g(char arg_1);

int milone_main();

int module_forward_reference_bug_Program_Early_f(char arg_) {
    return 2;
}

int module_forward_reference_bug_Program_Late_g(char arg_1) {
    return 2;
}

int milone_main() {
    int call_ = module_forward_reference_bug_Program_Early_f(0);
    milone_assert((call_ == 2), 14, 2);
    return 0;
}
