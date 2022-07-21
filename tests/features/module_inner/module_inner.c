#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

int32_t module_inner_module_inner_Inner_f(int32_t x_);

int32_t module_inner_sub_Inner_decrement(int32_t);

int main(int argc, char **argv);

int32_t module_inner_module_inner_Inner_f(int32_t x_) {
    return (x_ + 1);
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    int32_t call_;
    int32_t call_1;
    call_ = module_inner_module_inner_Inner_f(2);
    if ((call_ != 3)) milone_assert_error("module_inner/module_inner.milone", 11, 2);
    call_1 = module_inner_sub_Inner_decrement(3);
    if ((call_1 != 2)) milone_assert_error("module_inner/module_inner.milone", 14, 2);
    return 0;
}
