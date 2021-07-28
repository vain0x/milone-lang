#include "milone.h"

struct String module_open_shadowed_Program_g(char arg_);

struct String f_(char arg_1);

int module_open_shadowed_sub_f(int);

int module_open_shadowed_sub_g(int);

int milone_main();

struct String module_open_shadowed_Program_g(char arg_) {
    return (struct String){.str = "g is shadowed", .len = 13};
}

struct String f_(char arg_1) {
    return (struct String){.str = "f is locally shadowed", .len = 21};
}

int milone_main() {
    int call_ = module_open_shadowed_sub_f(40);
    milone_assert((call_ == 42), 7, 2);
    int call_1 = module_open_shadowed_sub_g(0);
    milone_assert((call_1 == 3), 9, 2);
    struct String call_2 = f_(0);
    milone_assert((str_compare(call_2, (struct String){.str = "f is locally shadowed", .len = 21}) == 0), 14, 4);
    return 0;
}
