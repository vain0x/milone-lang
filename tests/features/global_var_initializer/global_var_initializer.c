#include "milone.h"

void const* global_var_initializer_Program_f(void);

int milone_main(void);

void global_var_initializer_global_var_initializer__start(void);

void const* global_var_initializer_Program_boxedValue;

void const* global_var_initializer_Program_f(void) {
    return ((void const*)((intptr_t)1));
}

int milone_main(void) {
    global_var_initializer_global_var_initializer__start();
    void const* call_ = global_var_initializer_Program_f();
    milone_assert((((int)((intptr_t)call_)) == 1), 10, 2);
    return 0;
}

void global_var_initializer_global_var_initializer__start(void) {
    global_var_initializer_Program_boxedValue = ((void const*)((intptr_t)1));
    return;
}
