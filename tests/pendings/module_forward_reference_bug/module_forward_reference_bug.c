#include "milone.h"

int module_forward_reference_bug_Program_Early_f(void);

int module_forward_reference_bug_Program_Late_g(void);

int milone_main(void);

int module_forward_reference_bug_Program_Early_f(void) {
    return 2;
}

int module_forward_reference_bug_Program_Late_g(void) {
    return 2;
}

int milone_main(void) {
    int call_ = module_forward_reference_bug_Program_Early_f();
    milone_assert((call_ == 2), 14, 2);
    return 0;
}
