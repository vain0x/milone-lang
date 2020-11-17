#include "milone.h"

int main();

int main() {
    int if_;
    int if_1;
    int if_2;
    if ((2 >= 1)) {
        goto then_4;
    } else {
        goto else_5;
    }
then_4:;
    if_2 = (2 < 3);
    goto if_next_3;
else_5:;
    if_2 = 0;
    goto if_next_3;
if_next_3:;
    if (if_2) {
        goto then_6;
    } else {
        goto else_7;
    }
then_6:;
    if_1 = 1;
    goto if_next_2;
else_7:;
    int if_3;
    if ((2 < 3)) {
        goto then_9;
    } else {
        goto else_10;
    }
then_9:;
    if_3 = (2 >= 1);
    goto if_next_8;
else_10:;
    if_3 = 0;
    goto if_next_8;
if_next_8:;
    if_1 = if_3;
    goto if_next_2;
if_next_2:;
    if (if_1) {
        goto then_11;
    } else {
        goto else_12;
    }
then_11:;
    if_ = 0;
    goto if_next_1;
else_12:;
    if_ = 1;
    goto if_next_1;
if_next_1:;
    return if_;
}
