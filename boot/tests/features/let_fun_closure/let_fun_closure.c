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

int mutuallyRecursiveCase_(int arg_9);

int f1_(int arg_10);

int f2_(int arg_11);

int f3_(int arg_12);

int f4_(int arg_13);

int f5_(int arg_14);

int f6_(int arg_15);

int f7_(int arg_16);

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

int mutuallyRecursiveCase_(int arg_9) {
    int call_14 = f1_(0);
    milone_assert((call_14 == 1), 31, 2);
    int call_15 = 0;
    return 0;
}

int f1_(int arg_10) {
    int call_16 = f2_(0);
    return call_16;
}

int f2_(int arg_11) {
    int call_17 = f3_(0);
    return call_17;
}

int f3_(int arg_12) {
    int call_18 = f4_(0);
    return call_18;
}

int f4_(int arg_13) {
    int call_19 = f5_(0);
    return call_19;
}

int f5_(int arg_14) {
    int call_20 = f6_(0);
    return call_20;
}

int f6_(int arg_15) {
    int call_21 = f7_(0);
    return call_21;
}

int f7_(int arg_16) {
    return a_;
}

// static a_;

int main() {
    a_ = 1;
    int call_22 = basicCase_(0);
    int call_23 = transitiveCase_(0);
    int call_24 = recursiveCase_(0);
    int call_25 = lambdaCase_(0);
    int call_26 = mutuallyRecursiveCase_(0);
    return 0;
}
