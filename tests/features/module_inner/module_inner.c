#include <milone.h>

int module_inner_module_inner_Inner_f(int x_);

int module_inner_sub_Inner_decrement(int );

int main(int argc, char** argv);

int module_inner_module_inner_Inner_f(int x_) {
    return (x_ + 1);
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    int call_ = module_inner_module_inner_Inner_f(2);
    milone_assert((call_ == 3), (struct String){.str = "module_inner/module_inner.milone", .len = 32}, 11, 2);
    int call_1 = module_inner_sub_Inner_decrement(3);
    milone_assert((call_1 == 2), (struct String){.str = "module_inner/module_inner.milone", .len = 32}, 14, 2);
    return 0;
}
