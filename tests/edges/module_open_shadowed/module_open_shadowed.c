#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct String module_open_shadowed_module_open_shadowed_g(void);

struct String module_open_shadowed_module_open_shadowed_main_f(void);

int32_t module_open_shadowed_sub_f(int32_t);

int main(int argc, char **argv);

struct String module_open_shadowed_module_open_shadowed_g(void) {
    return (struct String){.ptr = "g is shadowed", .len = 13};
}

struct String module_open_shadowed_module_open_shadowed_main_f(void) {
    return (struct String){.ptr = "f is locally shadowed", .len = 21};
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    int32_t call_;
    struct String call_1;
    struct String call_2;
    call_ = module_open_shadowed_sub_f(40);
    if ((call_ != 42)) milone_assert_error("module_open_shadowed/module_open_shadowed.milone", 7, 2);
    call_1 = module_open_shadowed_module_open_shadowed_g();
    if ((string_compare(call_1, (struct String){.ptr = "g is shadowed", .len = 13}) != 0)) milone_assert_error("module_open_shadowed/module_open_shadowed.milone", 9, 2);
    call_2 = module_open_shadowed_module_open_shadowed_main_f();
    if ((string_compare(call_2, (struct String){.ptr = "f is locally shadowed", .len = 21}) != 0)) milone_assert_error("module_open_shadowed/module_open_shadowed.milone", 13, 4);
    return 0;
}
