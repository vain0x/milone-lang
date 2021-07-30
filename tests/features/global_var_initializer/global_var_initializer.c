#include "milone.h"

void const* global_var_initializer_Program_f(char arg_);

int milone_main();

void const* global_var_initializer_Program_boxedValue;

void const* global_var_initializer_Program_f(char arg_) {
    return ((void const*)((intptr_t)1));
}

int milone_main() {
    global_var_initializer_Program_boxedValue = ((void const*)((intptr_t)1));
    void const* call_ = global_var_initializer_Program_f(0);
    milone_assert((((int)((intptr_t)call_)) == 1), 10, 2);
    return 0;
}
