#include "milone.h"

struct IntTuple1;

struct UnitIntFun1;

int sub_(int step_, int x_);

char basicCase_(char arg_2);

int inc_(int step_1, int x_1);

int incTwice_(int step_1, int x_2);

char transitiveCase_(char arg_3);

int inc_1(int step_2, int x_3);

bool go_(int step_2, int n_);

char recursiveCase_(char arg_6);

int lg_(int lx_, char arg_7);

int fun_(int lx_, char arg_8);

int fun_1(void const* env_, char arg_);

int lf_(int lx_, char arg_9);

char lambdaCase_(char arg_10);

int xf4_(int x1_, int x2_, int x3_, char arg_11);

int xf3_(int x1_, int x2_, int x3_);

int xf2_(int x1_, int x2_);

int xf1_(int x1_);

char escapeCase_(char arg_12);

int zf11_1(int x_4, char arg_13);

int zf1_1(int x_4);

int zf22_1(int x_5, char arg_14);

int zf2_1(int x_5);

char innerFunCase_(char arg_15);

char mutuallyRecursiveCase_(char arg_16);

int f1_(char arg_17);

int f2_(char arg_18);

int f3_(char arg_19);

int f4_(char arg_20);

int f5_(char arg_21);

int f6_(char arg_22);

int f7_(char arg_23);

int milone_main();

struct IntTuple1 {
    int t0;
};

struct UnitIntFun1 {
    int(*fun)(void const*, char);
    void const* env;
};

static int a_;

int sub_(int step_, int x_) {
    return (x_ - step_);
}

char basicCase_(char arg_2) {
    int step_ = 3;
    int call_ = sub_(step_, 8);
    milone_assert((call_ == 5), 7, 2);
    return 0;
}

int inc_(int step_1, int x_1) {
    return (x_1 + step_1);
}

int incTwice_(int step_1, int x_2) {
    int call_1 = inc_(step_1, x_2);
    int call_2 = inc_(step_1, call_1);
    return call_2;
}

char transitiveCase_(char arg_3) {
    int step_1 = 1;
    int call_3 = incTwice_(step_1, 0);
    milone_assert((call_3 == 2), 13, 2);
    return 0;
}

int inc_1(int step_2, int x_3) {
    return (x_3 + step_2);
}

bool go_(int step_2, int n_) {
tailrec_1:;
    bool if_;
    if ((n_ >= 10)) {
        goto then_3;
    } else {
        goto else_4;
    }
then_3:;
    if_ = true;
    goto if_next_2;
else_4:;
    int arg_4 = step_2;
    int call_4 = inc_1(step_2, n_);
    int arg_5 = call_4;
    step_2 = arg_4;
    n_ = arg_5;
    goto tailrec_1;
if_next_2:;
    return if_;
}

char recursiveCase_(char arg_6) {
    int step_2 = 1;
    bool call_5 = go_(step_2, 0);
    milone_assert(call_5, 21, 2);
    return 0;
}

int lg_(int lx_, char arg_7) {
    return lx_;
}

int fun_(int lx_, char arg_8) {
    int call_6 = lg_(lx_, 0);
    return call_6;
}

int fun_1(void const* env_, char arg_) {
    int arg_1 = (*(((struct IntTuple1 const*)env_))).t0;
    int call_7 = fun_(arg_1, 0);
    return call_7;
}

int lf_(int lx_, char arg_9) {
    struct IntTuple1 tuple_ = (struct IntTuple1){.t0 = lx_};
    void const* box_ = milone_mem_alloc(1, sizeof(struct IntTuple1));
    (*(((struct IntTuple1*)box_))) = tuple_;
    struct UnitIntFun1 fun_2 = (struct UnitIntFun1){.fun = fun_1, .env = box_};
    int app_ = fun_2.fun(fun_2.env, 0);
    return app_;
}

char lambdaCase_(char arg_10) {
    int lx_ = 7;
    int call_8 = lf_(lx_, 0);
    milone_assert((call_8 == lx_), 30, 2);
    return 0;
}

int xf4_(int x1_, int x2_, int x3_, char arg_11) {
    int call_9 = xf1_(((x1_ + x2_) + x3_));
    return call_9;
}

int xf3_(int x1_, int x2_, int x3_) {
    int if_1;
    if ((x3_ == 3)) {
        goto then_6;
    } else {
        goto else_7;
    }
then_6:;
    int call_10 = xf4_(x1_, x2_, x3_, 0);
    if_1 = call_10;
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
    int call_11 = xf3_(x1_, x2_, 3);
    if_2 = call_11;
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
    int call_12 = xf2_(x1_, 2);
    if_3 = call_12;
    goto if_next_11;
else_13:;
    if_3 = x1_;
    goto if_next_11;
if_next_11:;
    return if_3;
}

char escapeCase_(char arg_12) {
    int call_13 = xf1_(1);
    milone_assert((call_13 == ((1 + 2) + 3)), 50, 2);
    return 0;
}

int zf11_1(int x_4, char arg_13) {
    return x_4;
}

int zf1_1(int x_4) {
    int call_14 = zf11_1(x_4, 0);
    return call_14;
}

int zf22_1(int x_5, char arg_14) {
    int call_15 = zf1_1(x_5);
    return call_15;
}

int zf2_1(int x_5) {
    int call_16 = zf22_1(x_5, 0);
    return call_16;
}

char innerFunCase_(char arg_15) {
    int call_17 = zf2_1(1);
    milone_assert((call_17 == 1), 61, 2);
    return 0;
}

char mutuallyRecursiveCase_(char arg_16) {
    int call_18 = f1_(0);
    milone_assert((call_18 == 1), 64, 31);
    return 0;
}

int f1_(char arg_17) {
    int call_19 = f2_(0);
    return call_19;
}

int f2_(char arg_18) {
    int call_20 = f3_(0);
    return call_20;
}

int f3_(char arg_19) {
    int call_21 = f4_(0);
    return call_21;
}

int f4_(char arg_20) {
    int call_22 = f5_(0);
    return call_22;
}

int f5_(char arg_21) {
    int call_23 = f6_(0);
    return call_23;
}

int f6_(char arg_22) {
    int call_24 = f7_(0);
    return call_24;
}

int f7_(char arg_23) {
    return a_;
}

int milone_main() {
    a_ = 1;
    char call_25 = basicCase_(0);
    char call_26 = transitiveCase_(0);
    char call_27 = recursiveCase_(0);
    char call_28 = lambdaCase_(0);
    char call_29 = escapeCase_(0);
    char call_30 = innerFunCase_(0);
    char call_31 = mutuallyRecursiveCase_(0);
    return 0;
}
