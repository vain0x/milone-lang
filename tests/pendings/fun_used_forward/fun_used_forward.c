#include "milone.h"

int fun_used_forward_Program_f(void);

int fun_used_forward_Program_g(void);

int milone_main(void);

int fun_used_forward_Program_f(void) {
    int call_ = fun_used_forward_Program_g();
    return call_;
}

int fun_used_forward_Program_g(void) {
    return 0;
}

int milone_main(void) {
    int call_1 = fun_used_forward_Program_f();
    milone_assert((call_1 == 0), 17, 2);
    return 0;
}
