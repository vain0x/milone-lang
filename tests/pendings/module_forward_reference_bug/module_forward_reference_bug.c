#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

int32_t module_forward_reference_bug_module_forward_reference_bug_Early_f(void);

int32_t module_forward_reference_bug_module_forward_reference_bug_Late_g(void);

int main(int argc, char **argv);

int32_t module_forward_reference_bug_module_forward_reference_bug_Early_f(void) {
    return 2;
}

int32_t module_forward_reference_bug_module_forward_reference_bug_Late_g(void) {
    return 2;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    int32_t call_;
    call_ = module_forward_reference_bug_module_forward_reference_bug_Early_f();
    if ((call_ != 2)) milone_assert_error("module_forward_reference_bug/module_forward_reference_bug.milone", 14, 2);
    return 0;
}
