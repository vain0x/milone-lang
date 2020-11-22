#include "milone.h"

int sub_(int step_, int x_);

int basicCase_(int arg_2);

int inc_(int step_1, int x_1);

int incTwice_(int step_1, int x_2);

int transitiveCase_(int arg_3);

int inc_1(int step_2, int x_3);

int go_(int step_2, int n_);

int recursiveCase_(int arg_6);

int lg_(int lx_, int arg_7);

int fun_(int lx_, int arg_8);

struct IntTuple1;

int fun_1(void* env_, int arg_);

struct UnitIntFun1;

int lf_(int lx_, int arg_9);

int lambdaCase_(int arg_10);

int xf4_(int x1_, int x2_, int x3_, int arg_11);

int xf3_(int x1_, int x2_, int x3_);

int xf2_(int x1_, int x2_);

int xf1_(int x1_);

int escapeCase_(int arg_12);

int zf11_(int x_4, int arg_13);

int zf1_(int x_4);

int zf22_(int x_5, int arg_14);

int zf2_(int x_5);

int innerFunCase_(int arg_15);

int mutuallyRecursiveCase_(int arg_16);

int f1_(int arg_17);

int f2_(int arg_18);

int f3_(int arg_19);

int f4_(int arg_20);

int f5_(int arg_21);

int f6_(int arg_22);

int f7_(int arg_23);

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
tailrec_1:;
    int if_;
    if ((n_ >= 10)) {
        goto then_3;
    } else {
        goto else_4;
    }
then_3:;
    if_ = 1;
    goto if_next_2;
else_4:;
    int arg_4 = step_2;
    int call_6 = inc_1(step_2, n_);
    int arg_5 = call_6;
    step_2 = arg_4;
    n_ = arg_5;
    goto tailrec_1;
    if_ = 0;
    goto if_next_2;
if_next_2:;
    return if_;
}

int recursiveCase_(int arg_6) {
    int step_2 = 1;
    int call_7 = go_(step_2, 0);
    milone_assert(call_7, 18, 2);
    int call_8 = 0;
    return 0;
}

int lg_(int lx_, int arg_7) {
    return lx_;
}

int fun_(int lx_, int arg_8) {
    int call_9 = lg_(lx_, 0);
    return call_9;
}

struct IntTuple1 {
    int t0;
};

int fun_1(void* env_, int arg_) {
    int arg_1 = (*(((struct IntTuple1*)env_))).t0;
    int call_10 = fun_(arg_1, 0);
    return call_10;
}

struct UnitIntFun1 {
    int(*fun)(void*, int);
    void* env;
};

int lf_(int lx_, int arg_9) {
    struct IntTuple1 tuple_;
    tuple_.t0 = lx_;
    void* box_ = (void*)milone_mem_alloc(1, sizeof(struct IntTuple1));
    (*(((struct IntTuple1*)box_))) = tuple_;
    void* env_1 = box_;
    struct UnitIntFun1 fun_2 = (struct UnitIntFun1){.fun = fun_1, .env = env_1};
    int app_ = fun_2.fun(fun_2.env, 0);
    return app_;
}

int lambdaCase_(int arg_10) {
    int lx_ = 7;
    int call_11 = lf_(lx_, 0);
    milone_assert((call_11 == lx_), 27, 2);
    int call_12 = 0;
    return 0;
}

int xf4_(int x1_, int x2_, int x3_, int arg_11) {
    int call_13 = xf1_(((x1_ + x2_) + x3_));
    return call_13;
}

int xf3_(int x1_, int x2_, int x3_) {
    int if_1;
    if ((x3_ == 3)) {
        goto then_6;
    } else {
        goto else_7;
    }
then_6:;
    int call_14 = xf4_(x1_, x2_, x3_, 0);
    if_1 = call_14;
    goto if_next_5;
else_7:;
    if_1 = x3_;
    goto if_next_5;
if_next_5:;
    return if_1;
}

int xf2_(int x1_, int x2_) {
    int if_2;
    if ((x2_ == 2)) {
        goto then_9;
    } else {
        goto else_10;
    }
then_9:;
    int call_15 = xf3_(x1_, x2_, 3);
    if_2 = call_15;
    goto if_next_8;
else_10:;
    if_2 = x2_;
    goto if_next_8;
if_next_8:;
    return if_2;
}

int xf1_(int x1_) {
    int if_3;
    if ((x1_ == 1)) {
        goto then_12;
    } else {
        goto else_13;
    }
then_12:;
    int call_16 = xf2_(x1_, 2);
    if_3 = call_16;
    goto if_next_11;
else_13:;
    if_3 = x1_;
    goto if_next_11;
if_next_11:;
    return if_3;
}

int escapeCase_(int arg_12) {
    int call_17 = xf1_(1);
    milone_assert((call_17 == ((1 + 2) + 3)), 48, 2);
    int call_18 = 0;
    return 0;
}

int zf11_(int x_4, int arg_13) {
    return x_4;
}

int zf1_(int x_4) {
    int call_19 = zf11_(x_4, 0);
    return call_19;
}

int zf22_(int x_5, int arg_14) {
    int call_20 = zf1_(x_5);
    return call_20;
}

int zf2_(int x_5) {
    int call_21 = zf22_(x_5, 0);
    return call_21;
}

int innerFunCase_(int arg_15) {
    int call_22 = zf2_(1);
    milone_assert((call_22 == 1), 59, 2);
    int call_23 = 0;
    return 0;
}

int mutuallyRecursiveCase_(int arg_16) {
    int call_24 = f1_(0);
    milone_assert((call_24 == 1), 63, 2);
    int call_25 = 0;
    return 0;
}

int f1_(int arg_17) {
    int call_26 = f2_(0);
    return call_26;
}

int f2_(int arg_18) {
    int call_27 = f3_(0);
    return call_27;
}

int f3_(int arg_19) {
    int call_28 = f4_(0);
    return call_28;
}

int f4_(int arg_20) {
    int call_29 = f5_(0);
    return call_29;
}

int f5_(int arg_21) {
    int call_30 = f6_(0);
    return call_30;
}

int f6_(int arg_22) {
    int call_31 = f7_(0);
    return call_31;
}

int f7_(int arg_23) {
    return a_;
}

// static a_;

int main() {
    a_ = 1;
    int call_32 = basicCase_(0);
    int call_33 = transitiveCase_(0);
    int call_34 = recursiveCase_(0);
    int call_35 = lambdaCase_(0);
    int call_36 = escapeCase_(0);
    int call_37 = innerFunCase_(0);
    int call_38 = mutuallyRecursiveCase_(0);
    return 0;
}
