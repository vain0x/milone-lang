#include "milone.h"

int sub_(int step_, int x_);

int basicCase_(int arg_2);

int inc_(int step_1, int x_1);

int incTwice_(int step_1, int x_2);

int transitiveCase_(int arg_3);

int inc_1(int step_2, int x_3);

int go_(int step_2, int n_);

int recursiveCase_(int arg_4);

int lg_(int lx_, int arg_5);

int fun_(int lx_, int arg_6);

struct IntTuple1;

int fun_1(void* env_, int arg_);

struct UnitIntFun1;

int lf_(int lx_, int arg_7);

int lambdaCase_(int arg_8);

int xf3_(int x2_, int x1_, int arg_9);

int xf2_(int x1_, int x2_);

int xf1_(int x2_, int x1_);

int escapeCase_(int x2_, int x1_, int arg_10);

int mutuallyRecursiveCase_(int arg_11);

int f1_(int arg_12);

int f2_(int arg_13);

int f3_(int arg_14);

int f4_(int arg_15);

int f5_(int arg_16);

int f6_(int arg_17);

int f7_(int arg_18);

static int a_;

int main();

int sub_(int step_, int x_) {
    return (x_ - step_);
}

int basicCase_(int arg_2) {
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

int transitiveCase_(int arg_3) {
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

int recursiveCase_(int arg_4) {
    int step_2 = 1;
    int call_8 = go_(step_2, 0);
    milone_assert(call_8, 18, 2);
    int call_9 = 0;
    return 0;
}

int lg_(int lx_, int arg_5) {
    return lx_;
}

int fun_(int lx_, int arg_6) {
    int call_10 = lg_(lx_, 0);
    return call_10;
}

struct IntTuple1 {
    int t0;
};

int fun_1(void* env_, int arg_) {
    int arg_1 = (*(((struct IntTuple1*)env_))).t0;
    int call_11 = fun_(arg_1, 0);
    return call_11;
}

struct UnitIntFun1 {
    int(*fun)(void*, int);
    void* env;
};

int lf_(int lx_, int arg_7) {
    struct IntTuple1 tuple_;
    tuple_.t0 = lx_;
    void* box_ = (void*)milone_mem_alloc(1, sizeof(struct IntTuple1));
    (*(((struct IntTuple1*)box_))) = tuple_;
    void* env_1 = box_;
    struct UnitIntFun1 fun_2 = (struct UnitIntFun1){.fun = fun_1, .env = env_1};
    int app_ = fun_2.fun(fun_2.env, 0);
    return app_;
}

int lambdaCase_(int arg_8) {
    int lx_ = 7;
    int call_12 = lf_(lx_, 0);
    milone_assert((call_12 == lx_), 27, 2);
    int call_13 = 0;
    return 0;
}

int xf3_(int x2_, int x1_, int arg_9) {
    int x3_ = 3;
    int call_14 = xf1_(x2_, ((x1_ + x2_) + x3_));
    return call_14;
}

int xf2_(int x1_, int x2_) {
    int match_1;
    if ((x2_ != 2)) goto next_5;
    int call_15 = xf3_(x2_, x1_, 0);
    match_1 = call_15;
    goto end_match_4;
next_5:;
    if ((x2_ == 2)) goto next_6;
    match_1 = x2_;
    goto end_match_4;
next_6:;
    exit(1);
end_match_4:;
    return match_1;
}

int xf1_(int x2_, int x1_) {
    int match_2;
    if ((x1_ != 1)) goto next_8;
    int call_16 = xf2_(x1_, 2);
    match_2 = call_16;
    goto end_match_7;
next_8:;
    if ((x1_ == 1)) goto next_9;
    match_2 = x1_;
    goto end_match_7;
next_9:;
    exit(1);
end_match_7:;
    return match_2;
}

int escapeCase_(int x2_, int x1_, int arg_10) {
    int call_17 = xf1_(x2_, 1);
    milone_assert((call_17 == ((1 + 2) + 3)), 46, 2);
    int call_18 = 0;
    return 0;
}

int mutuallyRecursiveCase_(int arg_11) {
    int call_19 = f1_(0);
    milone_assert((call_19 == 1), 50, 2);
    int call_20 = 0;
    return 0;
}

int f1_(int arg_12) {
    int call_21 = f2_(0);
    return call_21;
}

int f2_(int arg_13) {
    int call_22 = f3_(0);
    return call_22;
}

int f3_(int arg_14) {
    int call_23 = f4_(0);
    return call_23;
}

int f4_(int arg_15) {
    int call_24 = f5_(0);
    return call_24;
}

int f5_(int arg_16) {
    int call_25 = f6_(0);
    return call_25;
}

int f6_(int arg_17) {
    int call_26 = f7_(0);
    return call_26;
}

int f7_(int arg_18) {
    return a_;
}

// static a_;

int main() {
    a_ = 1;
    int call_27 = basicCase_(0);
    int call_28 = transitiveCase_(0);
    int call_29 = recursiveCase_(0);
    int call_30 = lambdaCase_(0);
    int call_31 = escapeCase_(x2_, x1_, 0);
    int call_32 = mutuallyRecursiveCase_(0);
    return 0;
}
