#include <milone.h>

void const* global_var_initializer_Program_f(void);

int main(int argc, char** argv);

void global_var_initializer_global_var_initializer_start(void);

void const* global_var_initializer_Program_boxedValue;

void const* global_var_initializer_Program_f(void) {
    return ((void const*)((intptr_t)1));
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    global_var_initializer_global_var_initializer_start();
    void const* call_ = global_var_initializer_Program_f();
    milone_assert((((int)((intptr_t)call_)) == 1), (struct String){.str = "global_var_initializer/global_var_initializer.milone", .len = 52}, 10, 2);
    return 0;
}

void global_var_initializer_global_var_initializer_start(void) {
    global_var_initializer_Program_boxedValue = ((void const*)((intptr_t)1));
    return;
}
