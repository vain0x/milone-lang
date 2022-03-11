#include <milone.h>

int module_forward_reference_bug_module_forward_reference_bug_Early_f(void);

int module_forward_reference_bug_module_forward_reference_bug_Late_g(void);

int main(int argc, char** argv);

int module_forward_reference_bug_module_forward_reference_bug_Early_f(void) {
    return 2;
}

int module_forward_reference_bug_module_forward_reference_bug_Late_g(void) {
    return 2;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    int call_;
    call_ = module_forward_reference_bug_module_forward_reference_bug_Early_f();
    milone_assert((call_ == 2), (struct String){.str = "module_forward_reference_bug/module_forward_reference_bug.milone", .len = 64}, 14, 2);
    return 0;
}
