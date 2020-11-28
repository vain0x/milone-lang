#include "milone.h"

int main();

int main() {
    bool if_;
    if ((2 >= 1)) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    if_ = (2 < 3);
    goto if_next_1;
else_3:;
    if_ = false;
    goto if_next_1;
if_next_1:;
    bool if_1;
    if (if_) {
        goto then_5;
    } else {
        goto else_6;
    }
then_5:;
    if_1 = true;
    goto if_next_4;
else_6:;
    bool if_2;
    if ((2 < 3)) {
        goto then_8;
    } else {
        goto else_9;
    }
then_8:;
    if_2 = (2 >= 1);
    goto if_next_7;
else_9:;
    if_2 = false;
    goto if_next_7;
if_next_7:;
    if_1 = if_2;
    goto if_next_4;
if_next_4:;
    int if_3;
    if (if_1) {
        goto then_11;
    } else {
        goto else_12;
    }
then_11:;
    if_3 = 0;
    goto if_next_10;
else_12:;
    if_3 = 1;
    goto if_next_10;
if_next_10:;
    return if_3;
}
