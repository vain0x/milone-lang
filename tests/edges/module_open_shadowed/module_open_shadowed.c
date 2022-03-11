#include <milone.h>

struct String module_open_shadowed_module_open_shadowed_g(void);

struct String module_open_shadowed_module_open_shadowed_main_f(void);

int module_open_shadowed_sub_f(int );

int main(int argc, char** argv);

struct String module_open_shadowed_module_open_shadowed_g(void) {
    return (struct String){.str = "g is shadowed", .len = 13};
}

struct String module_open_shadowed_module_open_shadowed_main_f(void) {
    return (struct String){.str = "f is locally shadowed", .len = 21};
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    int call_;
    struct String call_1;
    struct String call_2;
    call_ = module_open_shadowed_sub_f(40);
    milone_assert((call_ == 42), (struct String){.str = "module_open_shadowed/module_open_shadowed.milone", .len = 48}, 7, 2);
    call_1 = module_open_shadowed_module_open_shadowed_g();
    milone_assert((str_compare(call_1, (struct String){.str = "g is shadowed", .len = 13}) == 0), (struct String){.str = "module_open_shadowed/module_open_shadowed.milone", .len = 48}, 9, 2);
    call_2 = module_open_shadowed_module_open_shadowed_main_f();
    milone_assert((str_compare(call_2, (struct String){.str = "f is locally shadowed", .len = 21}) == 0), (struct String){.str = "module_open_shadowed/module_open_shadowed.milone", .len = 48}, 13, 4);
    return 0;
}
