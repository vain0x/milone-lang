#include "milone.h"

int minus_(int x_);

int abs_(int x_1);

int gcd_(int x_2, int y_);

bool go_(int x_3, int k_);

bool isPrime_(int x_3);

int main();

int minus_(int x_) {
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
    int call_ = minus_(x_1);
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

bool go_(int x_3, int k_) {
tailrec_8:;
    bool if_2;
    if ((x_3 < (k_ * k_))) {
        goto then_10;
    } else {
        goto else_11;
    }
then_10:;
    if_2 = true;
    goto if_next_9;
else_11:;
    bool if_3;
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
    if_3 = false;
    goto if_next_12;
else_14:;
    if_3 = false;
    goto if_next_12;
if_next_12:;
    if_2 = if_3;
    goto if_next_9;
if_next_9:;
    return if_2;
}

bool isPrime_(int x_3) {
    bool if_4;
    if ((x_3 >= 2)) {
        goto then_16;
    } else {
        goto else_17;
    }
then_16:;
    bool call_2 = go_(x_3, 2);
    if_4 = call_2;
    goto if_next_15;
else_17:;
    if_4 = false;
    goto if_next_15;
if_next_15:;
    return if_4;
}

int main() {
    int call_3 = abs_(0);
    milone_assert((call_3 == 0), 13, 2);
    int call_4 = abs_(1);
    milone_assert((call_4 == 1), 14, 2);
    int call_5 = minus_(1);
    int call_6 = abs_(call_5);
    milone_assert((call_6 == 1), 15, 2);
    int call_7 = gcd_(1, 1);
    milone_assert((call_7 == 1), 17, 2);
    int call_8 = gcd_(12, 18);
    milone_assert((call_8 == 6), 18, 2);
    int call_9 = minus_(6);
    int call_10 = gcd_(4, call_9);
    milone_assert((call_10 == 2), 19, 2);
    bool call_11 = isPrime_(2);
    milone_assert(call_11, 21, 2);
    bool call_12 = isPrime_(3);
    milone_assert(call_12, 22, 2);
    bool call_13 = isPrime_(4);
    milone_assert((!(call_13)), 23, 2);
    bool call_14 = isPrime_(1000000007);
    milone_assert(call_14, 24, 2);
    return 0;
}
