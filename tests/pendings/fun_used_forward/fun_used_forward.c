#include "milone.h"

int f_(void);

int fun_used_forward_Program_g(void);

int milone_main(void);

int f_(void) {
    int call_ = fun_used_forward_Program_g();
    return call_;
}

int fun_used_forward_Program_g(void) {
    return 0;
}

int milone_main(void) {
    int call_1 = f_();
    milone_assert((call_1 == 0), 17, 2);
    return 0;
}
