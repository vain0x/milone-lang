#include "milone.h"

int module_inner_Program_Inner_f(int x_1);

int module_inner_sub_Inner_decrement(int );

int milone_main(void);

int module_inner_Program_Inner_f(int x_1) {
    return (x_1 + 1);
}

int milone_main(void) {
    int call_ = module_inner_Program_Inner_f(2);
    milone_assert((call_ == 3), 11, 2);
    int call_1 = module_inner_sub_Inner_decrement(3);
    milone_assert((call_1 == 2), 14, 2);
    return 0;
}
