#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

int32_t factorial_factorial_main_factorial(int32_t x_);

int main(int argc, char **argv);

int32_t factorial_factorial_main_factorial(int32_t x_) {
    int32_t if_;
    int32_t call_;
    if ((x_ == 0)) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    if_ = 1;
    goto if_next_1;
else_3:;
    call_ = factorial_factorial_main_factorial((x_ - 1));
    if_ = (x_ * call_);
    goto if_next_1;
if_next_1:;
    return if_;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    int32_t call_1;
    call_1 = factorial_factorial_main_factorial(5);
    return (call_1 - 120);
}
