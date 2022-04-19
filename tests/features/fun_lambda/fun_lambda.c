#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

typedef int(*VoidConstPtrIntIntFunPtr2)(void const*, int);

struct IntIntFun1;

typedef int(*VoidConstPtrIntIntIntFunPtr3)(void const*, int, int);

struct IntIntIntFun2;

int fun_lambda_fun_lambda_layoutTest_apply(struct IntIntFun1 f_, int x_);

int fun_lambda_fun_lambda_layoutTest_fun(int x_1);

int fun_lambda_fun_lambda_eta2_layoutTest_fun(void const* env_, int arg_);

void fun_lambda_fun_lambda_layoutTest(void);

int fun_lambda_fun_lambda_main_twice(struct IntIntFun1 f_1, int x_2);

int fun_lambda_fun_lambda_main_fun(int x_3);

int fun_lambda_fun_lambda_eta2_main_fun(void const* env_1, int arg_1);

int fun_lambda_fun_lambda_main_fun_1(int x_5, int y_1);

int fun_lambda_fun_lambda_eta3_main_fun(void const* env_2, int arg_2, int arg_3);

int main(int argc, char** argv);

struct IntIntFun1 {
    VoidConstPtrIntIntFunPtr2 fun;
    void const* env;
};

struct IntIntIntFun2 {
    VoidConstPtrIntIntIntFunPtr3 fun;
    void const* env;
};

int fun_lambda_fun_lambda_layoutTest_apply(struct IntIntFun1 f_, int x_) {
    int app_;
    app_ = f_.fun(f_.env, x_);
    return app_;
}

int fun_lambda_fun_lambda_layoutTest_fun(int x_1) {
    return (x_1 + 3);
}

int fun_lambda_fun_lambda_eta2_layoutTest_fun(void const* env_, int arg_) {
    int call_;
    call_ = fun_lambda_fun_lambda_layoutTest_fun(arg_);
    return call_;
}

void fun_lambda_fun_lambda_layoutTest(void) {
    int a_;
    struct IntIntFun1 fun_;
    int call_1;
    fun_ = (struct IntIntFun1){.fun = fun_lambda_fun_lambda_eta2_layoutTest_fun, .env = NULL};
    call_1 = fun_lambda_fun_lambda_layoutTest_apply(fun_, 2);
    a_ = call_1;
    milone_assert((a_ == 5), (struct String){.ptr = "fun_lambda/fun_lambda.milone", .len = 28}, 13, 2);
    return;
}

int fun_lambda_fun_lambda_main_twice(struct IntIntFun1 f_1, int x_2) {
    int app_1;
    int app_2;
    app_1 = f_1.fun(f_1.env, x_2);
    app_2 = f_1.fun(f_1.env, app_1);
    return app_2;
}

int fun_lambda_fun_lambda_main_fun(int x_3) {
    int y_;
    y_ = (x_3 + 1);
    return y_;
}

int fun_lambda_fun_lambda_eta2_main_fun(void const* env_1, int arg_1) {
    int call_2;
    call_2 = fun_lambda_fun_lambda_main_fun(arg_1);
    return call_2;
}

int fun_lambda_fun_lambda_main_fun_1(int x_5, int y_1) {
    return ((x_5 / y_1) + 0);
}

int fun_lambda_fun_lambda_eta3_main_fun(void const* env_2, int arg_2, int arg_3) {
    int call_3;
    call_3 = fun_lambda_fun_lambda_main_fun_1(arg_2, arg_3);
    return call_3;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    int x_4;
    struct IntIntFun1 fun_1;
    int call_4;
    struct IntIntIntFun2 fun_2;
    int app_3;
    fun_1 = (struct IntIntFun1){.fun = fun_lambda_fun_lambda_eta2_main_fun, .env = NULL};
    call_4 = fun_lambda_fun_lambda_main_twice(fun_1, 40);
    x_4 = call_4;
    milone_assert((x_4 == 42), (struct String){.ptr = "fun_lambda/fun_lambda.milone", .len = 28}, 24, 2);
    fun_2 = (struct IntIntIntFun2){.fun = fun_lambda_fun_lambda_eta3_main_fun, .env = NULL};
    app_3 = fun_2.fun(fun_2.env, 84, 2);
    milone_assert((app_3 == 42), (struct String){.ptr = "fun_lambda/fun_lambda.milone", .len = 28}, 26, 2);
    fun_lambda_fun_lambda_layoutTest();
    return 0;
}
