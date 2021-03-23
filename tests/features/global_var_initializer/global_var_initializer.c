#include "milone.h"

void const* global_var_initializer_Program_f(char arg_);

int milone_main();

void const* global_var_initializer_Program_boxedValue;

void const* global_var_initializer_Program_f(char arg_) {
    void const* box_ = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_))) = 1;
    return box_;
}

int milone_main() {
    void const* box_1 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_1))) = 1;
    global_var_initializer_Program_boxedValue = box_1;
    void const* call_ = global_var_initializer_Program_f(0);
    milone_assert(((*(((int const*)call_))) == 1), 10, 2);
    return 0;
}
