#include "milone.h"

int neg_(int x_);

int abs_(int x_1);

int gcd_(int x_2, int y_);

struct IntTuple1;

int go_(struct IntTuple1 arg_, int k_);

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
    int match_1;
    if ((y_ != 0)) goto next_5;
    int call_1 = abs_(x_2);
    match_1 = call_1;
    goto end_match_4;
next_5:;
    if ((y_ == 0)) goto next_6;
    int call_2 = gcd_(y_, (x_2 % y_));
    match_1 = call_2;
    goto end_match_4;
next_6:;
    exit(1);
end_match_4:;
    return match_1;
}

struct IntTuple1 {
    int t0;
};

int go_(struct IntTuple1 arg_, int k_) {
    int x_3 = arg_.t0;
    int match_2;
    if ((x_3 >= (k_ * k_))) goto next_8;
    match_2 = 1;
    goto end_match_7;
next_8:;
    if ((x_3 < (k_ * k_))) goto next_9;
    int match_3;
    if (((x_3 % k_) == 0)) goto next_11;
    struct IntTuple1 tuple_;
    tuple_.t0 = x_3;
    int call_3 = go_(tuple_, (k_ + 1));
    match_3 = call_3;
    goto end_match_10;
next_11:;
    if (((x_3 % k_) != 0)) goto next_12;
    match_3 = 0;
    goto end_match_10;
next_12:;
    exit(1);
end_match_10:;
    match_2 = match_3;
    goto end_match_7;
next_9:;
    exit(1);
end_match_7:;
    return match_2;
}

int isPrime_(int x_3) {
    int match_4;
    if ((x_3 < 2)) goto next_14;
    struct IntTuple1 tuple_1;
    tuple_1.t0 = x_3;
    int call_4 = go_(tuple_1, 2);
    match_4 = call_4;
    goto end_match_13;
next_14:;
    if ((x_3 >= 2)) goto next_15;
    match_4 = 0;
    goto end_match_13;
next_15:;
    exit(1);
end_match_13:;
    return match_4;
}

int main() {
    int call_5 = abs_(0);
    milone_assert((call_5 == 0), 17, 2);
    int call_6 = 0;
    int call_7 = abs_(1);
    milone_assert((call_7 == 1), 18, 2);
    int call_8 = 0;
    int call_9 = neg_(1);
    int call_10 = abs_(call_9);
    milone_assert((call_10 == 1), 19, 2);
    int call_11 = 0;
    int call_12 = gcd_(1, 1);
    milone_assert((call_12 == 1), 21, 2);
    int call_13 = 0;
    int call_14 = gcd_(12, 18);
    milone_assert((call_14 == 6), 22, 2);
    int call_15 = 0;
    int call_16 = neg_(6);
    int call_17 = gcd_(4, call_16);
    milone_assert((call_17 == 2), 23, 2);
    int call_18 = 0;
    int call_19 = isPrime_(2);
    milone_assert(call_19, 25, 2);
    int call_20 = 0;
    int call_21 = isPrime_(3);
    milone_assert(call_21, 26, 2);
    int call_22 = 0;
    int call_23 = isPrime_(4);
    milone_assert((!(call_23)), 27, 2);
    int call_24 = 0;
    int call_25 = isPrime_(1000000007);
    milone_assert(call_25, 28, 2);
    int call_26 = 0;
    return 0;
}
