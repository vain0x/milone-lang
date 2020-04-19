#include "milone.h"

int sub_(int step_, int x_);

int basicCase_(int arg_);

int inc_(int step_1, int x_1);

int incTwice_(int step_1, int x_2);

int transitiveCase_(int arg_1);

int inc_1(int step_2, int x_3);

int go_(int step_2, int n_);

int recursiveCase_(int arg_2);

int mutuallyRecursiveCase_(int arg_3);

int f1_(int arg_4);

int f2_(int arg_5);

int f3_(int arg_6);

int f4_(int arg_7);

int f5_(int arg_8);

int f6_(int arg_9);

int f7_(int arg_10);

static int a_;

int main();

int sub_(int step_, int x_) {
    return (x_ - step_);
}

int basicCase_(int arg_) {
    int step_ = 3;
    int call_ = sub_(step_, 8);
    milone_assert((call_ == 5), 3, 2);
    int call_1 = 0;
    return 0;
}

int inc_(int step_1, int x_1) {
    return (x_1 + step_1);
}

int incTwice_(int step_1, int x_2) {
    int call_2 = inc_(step_1, x_2);
    int call_3 = inc_(step_1, call_2);
    return call_3;
}

int transitiveCase_(int arg_1) {
    int step_1 = 1;
    int call_4 = incTwice_(step_1, 0);
    milone_assert((call_4 == 2), 9, 2);
    int call_5 = 0;
    return 0;
}

int inc_1(int step_2, int x_3) {
    return (x_3 + step_2);
}

int go_(int step_2, int n_) {
    int match_;
    if ((n_ < 10)) goto next_2;
    match_ = 1;
    goto end_match_1;
next_2:;
    if ((n_ >= 10)) goto next_3;
    int call_6 = inc_1(step_2, n_);
    int call_7 = go_(step_2, call_6);
    match_ = call_7;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return match_;
}

int recursiveCase_(int arg_2) {
    int step_2 = 1;
    int call_8 = go_(step_2, 0);
    milone_assert(call_8, 18, 2);
    int call_9 = 0;
    return 0;
}

int mutuallyRecursiveCase_(int arg_3) {
    int call_10 = f1_(0);
    milone_assert((call_10 == 1), 22, 2);
    int call_11 = 0;
    return 0;
}

int f1_(int arg_4) {
    int call_12 = f2_(0);
    return call_12;
}

int f2_(int arg_5) {
    int call_13 = f3_(0);
    return call_13;
}

int f3_(int arg_6) {
    int call_14 = f4_(0);
    return call_14;
}

int f4_(int arg_7) {
    int call_15 = f5_(0);
    return call_15;
}

int f5_(int arg_8) {
    int call_16 = f6_(0);
    return call_16;
}

int f6_(int arg_9) {
    int call_17 = f7_(0);
    return call_17;
}

int f7_(int arg_10) {
    return a_;
}

// static a_;

int main() {
    a_ = 1;
    int call_18 = basicCase_(0);
    int call_19 = transitiveCase_(0);
    int call_20 = recursiveCase_(0);
    int call_21 = mutuallyRecursiveCase_(0);
    return 0;
}
