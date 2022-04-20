#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

void const *global_var_initializer_global_var_initializer_f(void);

int main(int argc, char **argv);

void global_var_initializer_global_var_initializer_start(void);

void const *global_var_initializer_global_var_initializer_boxedValue;

void const *global_var_initializer_global_var_initializer_f(void) {
    return ((void const *)((intptr_t)1));
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    void const *call_;
    global_var_initializer_global_var_initializer_start();
    call_ = global_var_initializer_global_var_initializer_f();
    if ((((int32_t)((intptr_t)call_)) != 1)) milone_assert_error("global_var_initializer/global_var_initializer.milone", 10, 2);
    return 0;
}

void global_var_initializer_global_var_initializer_start(void) {
    global_var_initializer_global_var_initializer_boxedValue = ((void const *)((intptr_t)1));
    return;
}
