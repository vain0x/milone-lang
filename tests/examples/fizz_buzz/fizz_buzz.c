#include "milone.h"

int fizzBuzz_(int i_);

int main();

int fizzBuzz_(int i_) {
tailrec_1:;
    int if_;
    if ((15 >= i_)) {
        goto then_3;
    } else {
        goto else_13;
    }
then_3:;
    int if_1;
    if (((i_ % 15) == 0)) {
        goto then_5;
    } else {
        goto else_6;
    }
then_5:;
    printf("FizzBuzz\n");
    if_1 = 0;
    goto if_next_4;
else_6:;
    int if_2;
    if (((i_ % 3) == 0)) {
        goto then_8;
    } else {
        goto else_9;
    }
then_8:;
    printf("Fizz\n");
    if_2 = 0;
    goto if_next_7;
else_9:;
    int if_3;
    if (((i_ % 5) == 0)) {
        goto then_11;
    } else {
        goto else_12;
    }
then_11:;
    printf("Buzz\n");
    if_3 = 0;
    goto if_next_10;
else_12:;
    printf("%d\n", i_);
    if_3 = 0;
    goto if_next_10;
if_next_10:;
    if_2 = 0;
    goto if_next_7;
if_next_7:;
    if_1 = 0;
    goto if_next_4;
if_next_4:;
    int arg_ = (i_ + 1);
    i_ = arg_;
    goto tailrec_1;
    if_ = 0;
    goto if_next_2;
else_13:;
    if_ = 0;
    goto if_next_2;
if_next_2:;
    return 0;
}

int main() {
    int call_ = fizzBuzz_(1);
    return 0;
}
