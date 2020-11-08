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
    int match_;
    if ((x_1 < 0)) goto next_2;
    match_ = x_1;
    goto end_match_1;
next_2:;
    if ((x_1 >= 0)) goto next_3;
    int call_ = neg_(x_1);
    match_ = call_;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return match_;
}

int gcd_(int x_2, int y_) {
tailrec_4:;
    int match_1;
    if ((y_ != 0)) goto next_6;
    int call_1 = abs_(x_2);
    match_1 = call_1;
    goto end_match_5;
next_6:;
    if ((y_ == 0)) goto next_7;
    int arg_ = y_;
    int arg_1 = (x_2 % y_);
    x_2 = arg_;
    y_ = arg_1;
    goto tailrec_4;
    match_1 = 0;
    goto end_match_5;
next_7:;
    exit(1);
end_match_5:;
    return match_1;
}

int go_(int x_3, int k_) {
tailrec_8:;
    int match_2;
    if ((x_3 >= (k_ * k_))) goto next_10;
    match_2 = 1;
    goto end_match_9;
next_10:;
    if ((x_3 < (k_ * k_))) goto next_11;
    int match_3;
    if (((x_3 % k_) == 0)) goto next_13;
    int arg_2 = x_3;
    int arg_3 = (k_ + 1);
    x_3 = arg_2;
    k_ = arg_3;
    goto tailrec_8;
    match_3 = 0;
    goto end_match_12;
next_13:;
    if (((x_3 % k_) != 0)) goto next_14;
    match_3 = 0;
    goto end_match_12;
next_14:;
    exit(1);
end_match_12:;
    match_2 = match_3;
    goto end_match_9;
next_11:;
    exit(1);
end_match_9:;
    return match_2;
}

int isPrime_(int x_3) {
    int match_4;
    if ((x_3 < 2)) goto next_16;
    int call_2 = go_(x_3, 2);
    match_4 = call_2;
    goto end_match_15;
next_16:;
    if ((x_3 >= 2)) goto next_17;
    match_4 = 0;
    goto end_match_15;
next_17:;
    exit(1);
end_match_15:;
    return match_4;
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
