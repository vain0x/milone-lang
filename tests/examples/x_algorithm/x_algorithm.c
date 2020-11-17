#include "milone.h"

int neg_(int x_);

int abs_(int x_1);

int gcd_(int x_2, int y_);

int go_(int x_3, int k_);

int isPrime_(int x_3);

int main();

int neg_(int x_) {
    return (0 - x_);
}

int abs_(int x_1) {
    int if_;
    if ((x_1 >= 0)) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    if_ = x_1;
    goto if_next_1;
else_3:;
    int call_ = neg_(x_1);
    if_ = call_;
    goto if_next_1;
if_next_1:;
    return if_;
}

int gcd_(int x_2, int y_) {
tailrec_4:;
    int if_1;
    if ((y_ == 0)) {
        goto then_6;
    } else {
        goto else_7;
    }
then_6:;
    int call_1 = abs_(x_2);
    if_1 = call_1;
    goto if_next_5;
else_7:;
    int arg_ = y_;
    int arg_1 = (x_2 % y_);
    x_2 = arg_;
    y_ = arg_1;
    goto tailrec_4;
    if_1 = 0;
    goto if_next_5;
if_next_5:;
    return if_1;
}

int go_(int x_3, int k_) {
tailrec_8:;
    int if_2;
    if ((x_3 < (k_ * k_))) {
        goto then_10;
    } else {
        goto else_11;
    }
then_10:;
    if_2 = 1;
    goto if_next_9;
else_11:;
    int if_3;
    if (((x_3 % k_) != 0)) {
        goto then_13;
    } else {
        goto else_14;
    }
then_13:;
    int arg_2 = x_3;
    int arg_3 = (k_ + 1);
    x_3 = arg_2;
    k_ = arg_3;
    goto tailrec_8;
    if_3 = 0;
    goto if_next_12;
else_14:;
    if_3 = 0;
    goto if_next_12;
if_next_12:;
    if_2 = if_3;
    goto if_next_9;
if_next_9:;
    return if_2;
}

int isPrime_(int x_3) {
    int if_4;
    if ((x_3 >= 2)) {
        goto then_16;
    } else {
        goto else_17;
    }
then_16:;
    int call_2 = go_(x_3, 2);
    if_4 = call_2;
    goto if_next_15;
else_17:;
    if_4 = 0;
    goto if_next_15;
if_next_15:;
    return if_4;
}

int main() {
    int call_3 = abs_(0);
    milone_assert((call_3 == 0), 17, 2);
    int call_4 = 0;
    int call_5 = abs_(1);
    milone_assert((call_5 == 1), 18, 2);
    int call_6 = 0;
    int call_7 = neg_(1);
    int call_8 = abs_(call_7);
    milone_assert((call_8 == 1), 19, 2);
    int call_9 = 0;
    int call_10 = gcd_(1, 1);
    milone_assert((call_10 == 1), 21, 2);
    int call_11 = 0;
    int call_12 = gcd_(12, 18);
    milone_assert((call_12 == 6), 22, 2);
    int call_13 = 0;
    int call_14 = neg_(6);
    int call_15 = gcd_(4, call_14);
    milone_assert((call_15 == 2), 23, 2);
    int call_16 = 0;
    int call_17 = isPrime_(2);
    milone_assert(call_17, 25, 2);
    int call_18 = 0;
    int call_19 = isPrime_(3);
    milone_assert(call_19, 26, 2);
    int call_20 = 0;
    int call_21 = isPrime_(4);
    milone_assert((!(call_21)), 27, 2);
    int call_22 = 0;
    int call_23 = isPrime_(1000000007);
    milone_assert(call_23, 28, 2);
    int call_24 = 0;
    return 0;
}
