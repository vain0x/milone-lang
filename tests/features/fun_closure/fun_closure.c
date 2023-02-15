#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

typedef int32_t(*VoidConstPtrInt32FunPtr1)(void const *);

struct UnitInt32Fun1;

int32_t fun_closure_fun_closure_basicCase_sub(int32_t step_, int32_t x_);

void fun_closure_fun_closure_basicCase(void);

int32_t fun_closure_fun_closure_transitiveCase_inc(int32_t step_1, int32_t x_1);

int32_t fun_closure_fun_closure_transitiveCase_incTwice(int32_t step_1, int32_t x_2);

void fun_closure_fun_closure_transitiveCase(void);

int32_t fun_closure_fun_closure_recursiveCase_inc(int32_t step_2, int32_t x_3);

bool fun_closure_fun_closure_recursiveCase_go(int32_t step_2, int32_t n_);

void fun_closure_fun_closure_recursiveCase(void);

int32_t fun_closure_fun_closure_lambdaCase_lf_lg(int32_t lx_);

int32_t fun_closure_fun_closure_lambdaCase_lf_fun(int32_t lx_);

int32_t fun_closure_fun_closure_eta2_lambdaCase_lf_fun(void const *env_);

int32_t fun_closure_fun_closure_lambdaCase_lf(int32_t lx_);

void fun_closure_fun_closure_lambdaCase(void);

int32_t fun_closure_fun_closure_escapeCase_xf1_xf2_xf3_xf4(int32_t x3_, int32_t x2_, int32_t x1_);

int32_t fun_closure_fun_closure_escapeCase_xf1_xf2_xf3(int32_t x2_, int32_t x1_, int32_t x3_);

int32_t fun_closure_fun_closure_escapeCase_xf1_xf2(int32_t x1_, int32_t x2_);

int32_t fun_closure_fun_closure_escapeCase_xf1(int32_t x1_);

void fun_closure_fun_closure_escapeCase(void);

int32_t fun_closure_fun_closure_innerFunCase_zf1_zf11(int32_t x_4);

int32_t fun_closure_fun_closure_innerFunCase_zf1(int32_t x_4);

int32_t fun_closure_fun_closure_innerFunCase_zf2_zf22(int32_t x_5);

int32_t fun_closure_fun_closure_innerFunCase_zf2(int32_t x_5);

void fun_closure_fun_closure_innerFunCase(void);

void fun_closure_fun_closure_mutuallyRecursiveCase(void);

int32_t fun_closure_fun_closure_f1(void);

int32_t fun_closure_fun_closure_f2(void);

int32_t fun_closure_fun_closure_f3(void);

int32_t fun_closure_fun_closure_f4(void);

int32_t fun_closure_fun_closure_f5(void);

int32_t fun_closure_fun_closure_f6(void);

int32_t fun_closure_fun_closure_f7(void);

int main(int argc, char **argv);

void fun_closure_fun_closure_start(void);

struct UnitInt32Fun1 {
    VoidConstPtrInt32FunPtr1 fun;
    void const *env;
};

int32_t fun_closure_fun_closure_a;

int32_t fun_closure_fun_closure_basicCase_sub(int32_t step_, int32_t x_) {
    return (x_ - step_);
}

void fun_closure_fun_closure_basicCase(void) {
    int32_t step_;
    int32_t call_;
    step_ = 3;
    call_ = fun_closure_fun_closure_basicCase_sub(step_, 8);
    if ((call_ != 5)) milone_assert_error("fun_closure/fun_closure.milone", 7, 2);
    return;
}

int32_t fun_closure_fun_closure_transitiveCase_inc(int32_t step_1, int32_t x_1) {
    return (x_1 + step_1);
}

int32_t fun_closure_fun_closure_transitiveCase_incTwice(int32_t step_1, int32_t x_2) {
    int32_t call_1;
    int32_t call_2;
    call_1 = fun_closure_fun_closure_transitiveCase_inc(step_1, x_2);
    call_2 = fun_closure_fun_closure_transitiveCase_inc(step_1, call_1);
    return call_2;
}

void fun_closure_fun_closure_transitiveCase(void) {
    int32_t step_1;
    int32_t call_3;
    step_1 = 1;
    call_3 = fun_closure_fun_closure_transitiveCase_incTwice(step_1, 0);
    if ((call_3 != 2)) milone_assert_error("fun_closure/fun_closure.milone", 13, 2);
    return;
}

int32_t fun_closure_fun_closure_recursiveCase_inc(int32_t step_2, int32_t x_3) {
    return (x_3 + step_2);
}

bool fun_closure_fun_closure_recursiveCase_go(int32_t step_2, int32_t n_) {
    bool if_;
    int32_t call_4;
    int32_t arg_2;
    int32_t arg_3;
tailrec_1:;
    if ((n_ >= 10)) {
        goto then_3;
    } else {
        goto else_4;
    }
then_3:;
    if_ = true;
    goto if_next_2;
else_4:;
    call_4 = fun_closure_fun_closure_recursiveCase_inc(step_2, n_);
    arg_2 = step_2;
    arg_3 = call_4;
    step_2 = arg_2;
    n_ = arg_3;
    goto tailrec_1;
if_next_2:;
    return if_;
}

void fun_closure_fun_closure_recursiveCase(void) {
    int32_t step_2;
    bool call_5;
    step_2 = 1;
    call_5 = fun_closure_fun_closure_recursiveCase_go(step_2, 0);
    if ((!(call_5))) milone_assert_error("fun_closure/fun_closure.milone", 21, 2);
    return;
}

int32_t fun_closure_fun_closure_lambdaCase_lf_lg(int32_t lx_) {
    return lx_;
}

int32_t fun_closure_fun_closure_lambdaCase_lf_fun(int32_t lx_) {
    int32_t call_6;
    call_6 = fun_closure_fun_closure_lambdaCase_lf_lg(lx_);
    return call_6;
}

int32_t fun_closure_fun_closure_eta2_lambdaCase_lf_fun(void const *env_) {
    int32_t arg_1;
    int32_t call_7;
    arg_1 = ((int32_t)((intptr_t)env_));
    call_7 = fun_closure_fun_closure_lambdaCase_lf_fun(arg_1);
    return call_7;
}

int32_t fun_closure_fun_closure_lambdaCase_lf(int32_t lx_) {
    struct UnitInt32Fun1 fun_;
    int32_t app_;
    fun_ = (struct UnitInt32Fun1){.fun = fun_closure_fun_closure_eta2_lambdaCase_lf_fun, .env = ((void const *)((intptr_t)lx_))};
    app_ = fun_.fun(fun_.env);
    return app_;
}

void fun_closure_fun_closure_lambdaCase(void) {
    int32_t lx_;
    int32_t call_8;
    lx_ = 7;
    call_8 = fun_closure_fun_closure_lambdaCase_lf(lx_);
    if ((call_8 != lx_)) milone_assert_error("fun_closure/fun_closure.milone", 30, 2);
    return;
}

int32_t fun_closure_fun_closure_escapeCase_xf1_xf2_xf3_xf4(int32_t x3_, int32_t x2_, int32_t x1_) {
    int32_t call_9;
    call_9 = fun_closure_fun_closure_escapeCase_xf1(((x1_ + x2_) + x3_));
    return call_9;
}

int32_t fun_closure_fun_closure_escapeCase_xf1_xf2_xf3(int32_t x2_, int32_t x1_, int32_t x3_) {
    int32_t if_1;
    int32_t call_10;
    if ((x3_ == 3)) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    call_10 = fun_closure_fun_closure_escapeCase_xf1_xf2_xf3_xf4(x3_, x2_, x1_);
    if_1 = call_10;
    goto if_next_1;
else_3:;
    if_1 = x3_;
    goto if_next_1;
if_next_1:;
    return if_1;
}

int32_t fun_closure_fun_closure_escapeCase_xf1_xf2(int32_t x1_, int32_t x2_) {
    int32_t if_2;
    int32_t call_11;
    if ((x2_ == 2)) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    call_11 = fun_closure_fun_closure_escapeCase_xf1_xf2_xf3(x2_, x1_, 3);
    if_2 = call_11;
    goto if_next_1;
else_3:;
    if_2 = x2_;
    goto if_next_1;
if_next_1:;
    return if_2;
}

int32_t fun_closure_fun_closure_escapeCase_xf1(int32_t x1_) {
    int32_t if_3;
    int32_t call_12;
    if ((x1_ == 1)) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    call_12 = fun_closure_fun_closure_escapeCase_xf1_xf2(x1_, 2);
    if_3 = call_12;
    goto if_next_1;
else_3:;
    if_3 = x1_;
    goto if_next_1;
if_next_1:;
    return if_3;
}

void fun_closure_fun_closure_escapeCase(void) {
    int32_t call_13;
    call_13 = fun_closure_fun_closure_escapeCase_xf1(1);
    if ((call_13 != ((1 + 2) + 3))) milone_assert_error("fun_closure/fun_closure.milone", 50, 2);
    return;
}

int32_t fun_closure_fun_closure_innerFunCase_zf1_zf11(int32_t x_4) {
    return x_4;
}

int32_t fun_closure_fun_closure_innerFunCase_zf1(int32_t x_4) {
    int32_t call_14;
    call_14 = fun_closure_fun_closure_innerFunCase_zf1_zf11(x_4);
    return call_14;
}

int32_t fun_closure_fun_closure_innerFunCase_zf2_zf22(int32_t x_5) {
    int32_t call_15;
    call_15 = fun_closure_fun_closure_innerFunCase_zf1(x_5);
    return call_15;
}

int32_t fun_closure_fun_closure_innerFunCase_zf2(int32_t x_5) {
    int32_t call_16;
    call_16 = fun_closure_fun_closure_innerFunCase_zf2_zf22(x_5);
    return call_16;
}

void fun_closure_fun_closure_innerFunCase(void) {
    int32_t call_17;
    call_17 = fun_closure_fun_closure_innerFunCase_zf2(1);
    if ((call_17 != 1)) milone_assert_error("fun_closure/fun_closure.milone", 61, 2);
    return;
}

void fun_closure_fun_closure_mutuallyRecursiveCase(void) {
    int32_t call_18;
    call_18 = fun_closure_fun_closure_f1();
    if ((call_18 != 1)) milone_assert_error("fun_closure/fun_closure.milone", 64, 31);
    return;
}

int32_t fun_closure_fun_closure_f1(void) {
    int32_t call_19;
    call_19 = fun_closure_fun_closure_f2();
    return call_19;
}

int32_t fun_closure_fun_closure_f2(void) {
    int32_t call_20;
    call_20 = fun_closure_fun_closure_f3();
    return call_20;
}

int32_t fun_closure_fun_closure_f3(void) {
    int32_t call_21;
    call_21 = fun_closure_fun_closure_f4();
    return call_21;
}

int32_t fun_closure_fun_closure_f4(void) {
    int32_t call_22;
    call_22 = fun_closure_fun_closure_f5();
    return call_22;
}

int32_t fun_closure_fun_closure_f5(void) {
    int32_t call_23;
    call_23 = fun_closure_fun_closure_f6();
    return call_23;
}

int32_t fun_closure_fun_closure_f6(void) {
    int32_t call_24;
    call_24 = fun_closure_fun_closure_f7();
    return call_24;
}

int32_t fun_closure_fun_closure_f7(void) {
    return fun_closure_fun_closure_a;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    fun_closure_fun_closure_start();
    fun_closure_fun_closure_basicCase();
    fun_closure_fun_closure_transitiveCase();
    fun_closure_fun_closure_recursiveCase();
    fun_closure_fun_closure_lambdaCase();
    fun_closure_fun_closure_escapeCase();
    fun_closure_fun_closure_innerFunCase();
    fun_closure_fun_closure_mutuallyRecursiveCase();
    return 0;
}

void fun_closure_fun_closure_start(void) {
    fun_closure_fun_closure_a = 1;
    return;
}
