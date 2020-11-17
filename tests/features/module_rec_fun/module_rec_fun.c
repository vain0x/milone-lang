#include "milone.h"

int even_(int n_);

int odd_(int n_1);

int main();

int even_(int n_) {
    int if_;
    if ((n_ == 0)) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    if_ = 1;
    goto if_next_1;
else_3:;
    int call_ = odd_((n_ - 1));
    if_ = call_;
    goto if_next_1;
if_next_1:;
    return if_;
}

int odd_(int n_1) {
    int if_1;
    if ((n_1 != 0)) {
        goto then_5;
    } else {
        goto else_6;
    }
then_5:;
    int call_1 = even_((n_1 - 1));
    if_1 = call_1;
    goto if_next_4;
else_6:;
    if_1 = 0;
    goto if_next_4;
if_next_4:;
    return if_1;
}

int main() {
    int call_2 = odd_(1);
    milone_assert(call_2, 9, 2);
    int call_3 = 0;
    int call_4 = even_(2);
    milone_assert(call_4, 10, 2);
    int call_5 = 0;
    int call_6 = even_(3);
    milone_assert((!(call_6)), 11, 2);
    int call_7 = 0;
    return 0;
}
