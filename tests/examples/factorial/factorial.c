#include "milone.h"

int factorial_(int x_);

int milone_main(void);

int factorial_(int x_) {
    int if_;
    if ((x_ == 0)) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    if_ = 1;
    goto if_next_1;
else_3:;
    int call_ = factorial_((x_ - 1));
    if_ = (x_ * call_);
    goto if_next_1;
if_next_1:;
    return if_;
}

int milone_main(void) {
    int call_1 = factorial_(5);
    return (call_1 - 120);
}
