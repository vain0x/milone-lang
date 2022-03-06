#include <milone.h>

typedef int(*VoidConstPtrIntFunPtr1)(void const*);

struct UnitIntFun1;

int fun_closure_fun_closure_basicCase_sub(int step_, int x_);

void fun_closure_fun_closure_basicCase(void);

int fun_closure_fun_closure_transitiveCase_inc(int step_1, int x_1);

int fun_closure_fun_closure_transitiveCase_incTwice(int step_1, int x_2);

void fun_closure_fun_closure_transitiveCase(void);

int fun_closure_fun_closure_recursiveCase_inc(int step_2, int x_3);

bool fun_closure_fun_closure_recursiveCase_go(int step_2, int n_);

void fun_closure_fun_closure_recursiveCase(void);

int fun_closure_fun_closure_lambdaCase_lf_lg(int lx_);

int fun_closure_fun_closure_lambdaCase_lf_fun(int lx_);

int fun_closure_fun_closure_eta2_lambdaCase_lf_fun(void const* env_);

int fun_closure_fun_closure_lambdaCase_lf(int lx_);

void fun_closure_fun_closure_lambdaCase(void);

int fun_closure_fun_closure_escapeCase_xf1_xf2_xf3_xf4(int x3_, int x2_, int x1_);

int fun_closure_fun_closure_escapeCase_xf1_xf2_xf3(int x2_, int x1_, int x3_);

int fun_closure_fun_closure_escapeCase_xf1_xf2(int x1_, int x2_);

int fun_closure_fun_closure_escapeCase_xf1(int x1_);

void fun_closure_fun_closure_escapeCase(void);

int fun_closure_fun_closure_innerFunCase_zf1_zf11(int x_4);

int fun_closure_fun_closure_innerFunCase_zf1(int x_4);

int fun_closure_fun_closure_innerFunCase_zf2_zf22(int x_5);

int fun_closure_fun_closure_innerFunCase_zf2(int x_5);

void fun_closure_fun_closure_innerFunCase(void);

void fun_closure_fun_closure_mutuallyRecursiveCase(void);

int fun_closure_fun_closure_f1(void);

int fun_closure_fun_closure_f2(void);

int fun_closure_fun_closure_f3(void);

int fun_closure_fun_closure_f4(void);

int fun_closure_fun_closure_f5(void);

int fun_closure_fun_closure_f6(void);

int fun_closure_fun_closure_f7(void);

int main(int argc, char** argv);

void fun_closure_fun_closure_start(void);

struct UnitIntFun1 {
    VoidConstPtrIntFunPtr1 fun;
    void const* env;
};

extern int fun_closure_fun_closure_a;

int fun_closure_fun_closure_a;

int fun_closure_fun_closure_basicCase_sub(int step_, int x_) {
    return (x_ - step_);
}

void fun_closure_fun_closure_basicCase(void) {
    int step_ = 3;
    int call_ = fun_closure_fun_closure_basicCase_sub(step_, 8);
    milone_assert((call_ == 5), (struct String){.str = "fun_closure/fun_closure.milone", .len = 30}, 7, 2);
    return;
}

int fun_closure_fun_closure_transitiveCase_inc(int step_1, int x_1) {
    return (x_1 + step_1);
}

int fun_closure_fun_closure_transitiveCase_incTwice(int step_1, int x_2) {
    int call_1 = fun_closure_fun_closure_transitiveCase_inc(step_1, x_2);
    int call_2 = fun_closure_fun_closure_transitiveCase_inc(step_1, call_1);
    return call_2;
}

void fun_closure_fun_closure_transitiveCase(void) {
    int step_1 = 1;
    int call_3 = fun_closure_fun_closure_transitiveCase_incTwice(step_1, 0);
    milone_assert((call_3 == 2), (struct String){.str = "fun_closure/fun_closure.milone", .len = 30}, 13, 2);
    return;
}

int fun_closure_fun_closure_recursiveCase_inc(int step_2, int x_3) {
    return (x_3 + step_2);
}

bool fun_closure_fun_closure_recursiveCase_go(int step_2, int n_) {
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
    int call_4 = fun_closure_fun_closure_recursiveCase_inc(step_2, n_);
    int arg_2 = step_2;
    int arg_3 = call_4;
    step_2 = arg_2;
    n_ = arg_3;
    goto tailrec_1;
if_next_2:;
    return if_;
}

void fun_closure_fun_closure_recursiveCase(void) {
    int step_2 = 1;
    bool call_5 = fun_closure_fun_closure_recursiveCase_go(step_2, 0);
    milone_assert(call_5, (struct String){.str = "fun_closure/fun_closure.milone", .len = 30}, 21, 2);
    return;
}

int fun_closure_fun_closure_lambdaCase_lf_lg(int lx_) {
    return lx_;
}

int fun_closure_fun_closure_lambdaCase_lf_fun(int lx_) {
    int call_6 = fun_closure_fun_closure_lambdaCase_lf_lg(lx_);
    return call_6;
}

int fun_closure_fun_closure_eta2_lambdaCase_lf_fun(void const* env_) {
    int arg_1 = ((int)((intptr_t)env_));
    int call_7 = fun_closure_fun_closure_lambdaCase_lf_fun(arg_1);
    return call_7;
}

int fun_closure_fun_closure_lambdaCase_lf(int lx_) {
    struct UnitIntFun1 fun_ = (struct UnitIntFun1){.fun = fun_closure_fun_closure_eta2_lambdaCase_lf_fun, .env = ((void const*)((intptr_t)lx_))};
    int app_ = fun_.fun(fun_.env);
    return app_;
}

void fun_closure_fun_closure_lambdaCase(void) {
    int lx_ = 7;
    int call_8 = fun_closure_fun_closure_lambdaCase_lf(lx_);
    milone_assert((call_8 == lx_), (struct String){.str = "fun_closure/fun_closure.milone", .len = 30}, 30, 2);
    return;
}

int fun_closure_fun_closure_escapeCase_xf1_xf2_xf3_xf4(int x3_, int x2_, int x1_) {
    int call_9 = fun_closure_fun_closure_escapeCase_xf1(((x1_ + x2_) + x3_));
    return call_9;
}

int fun_closure_fun_closure_escapeCase_xf1_xf2_xf3(int x2_, int x1_, int x3_) {
    int if_1;
    if ((x3_ == 3)) {
        goto then_6;
    } else {
        goto else_7;
    }
then_6:;
    int call_10 = fun_closure_fun_closure_escapeCase_xf1_xf2_xf3_xf4(x3_, x2_, x1_);
    if_1 = call_10;
    goto if_next_5;
else_7:;
    if_1 = x3_;
    goto if_next_5;
if_next_5:;
    return if_1;
}

int fun_closure_fun_closure_escapeCase_xf1_xf2(int x1_, int x2_) {
    int if_2;
    if ((x2_ == 2)) {
        goto then_9;
    } else {
        goto else_10;
    }
then_9:;
    int call_11 = fun_closure_fun_closure_escapeCase_xf1_xf2_xf3(x2_, x1_, 3);
    if_2 = call_11;
    goto if_next_8;
else_10:;
    if_2 = x2_;
    goto if_next_8;
if_next_8:;
    return if_2;
}

int fun_closure_fun_closure_escapeCase_xf1(int x1_) {
    int if_3;
    if ((x1_ == 1)) {
        goto then_12;
    } else {
        goto else_13;
    }
then_12:;
    int call_12 = fun_closure_fun_closure_escapeCase_xf1_xf2(x1_, 2);
    if_3 = call_12;
    goto if_next_11;
else_13:;
    if_3 = x1_;
    goto if_next_11;
if_next_11:;
    return if_3;
}

void fun_closure_fun_closure_escapeCase(void) {
    int call_13 = fun_closure_fun_closure_escapeCase_xf1(1);
    milone_assert((call_13 == ((1 + 2) + 3)), (struct String){.str = "fun_closure/fun_closure.milone", .len = 30}, 50, 2);
    return;
}

int fun_closure_fun_closure_innerFunCase_zf1_zf11(int x_4) {
    return x_4;
}

int fun_closure_fun_closure_innerFunCase_zf1(int x_4) {
    int call_14 = fun_closure_fun_closure_innerFunCase_zf1_zf11(x_4);
    return call_14;
}

int fun_closure_fun_closure_innerFunCase_zf2_zf22(int x_5) {
    int call_15 = fun_closure_fun_closure_innerFunCase_zf1(x_5);
    return call_15;
}

int fun_closure_fun_closure_innerFunCase_zf2(int x_5) {
    int call_16 = fun_closure_fun_closure_innerFunCase_zf2_zf22(x_5);
    return call_16;
}

void fun_closure_fun_closure_innerFunCase(void) {
    int call_17 = fun_closure_fun_closure_innerFunCase_zf2(1);
    milone_assert((call_17 == 1), (struct String){.str = "fun_closure/fun_closure.milone", .len = 30}, 61, 2);
    return;
}

void fun_closure_fun_closure_mutuallyRecursiveCase(void) {
    int call_18 = fun_closure_fun_closure_f1();
    milone_assert((call_18 == 1), (struct String){.str = "fun_closure/fun_closure.milone", .len = 30}, 64, 31);
    return;
}

int fun_closure_fun_closure_f1(void) {
    int call_19 = fun_closure_fun_closure_f2();
    return call_19;
}

int fun_closure_fun_closure_f2(void) {
    int call_20 = fun_closure_fun_closure_f3();
    return call_20;
}

int fun_closure_fun_closure_f3(void) {
    int call_21 = fun_closure_fun_closure_f4();
    return call_21;
}

int fun_closure_fun_closure_f4(void) {
    int call_22 = fun_closure_fun_closure_f5();
    return call_22;
}

int fun_closure_fun_closure_f5(void) {
    int call_23 = fun_closure_fun_closure_f6();
    return call_23;
}

int fun_closure_fun_closure_f6(void) {
    int call_24 = fun_closure_fun_closure_f7();
    return call_24;
}

int fun_closure_fun_closure_f7(void) {
    return fun_closure_fun_closure_a;
}

int main(int argc, char** argv) {
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
