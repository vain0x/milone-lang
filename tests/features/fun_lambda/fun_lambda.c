#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

typedef int32_t(*VoidConstPtrInt32Int32FunPtr2)(void const *, int32_t);

struct Int32Int32Fun1;

typedef int32_t(*VoidConstPtrInt32Int32Int32FunPtr3)(void const *, int32_t, int32_t);

struct Int32Int32Int32Fun2;

int32_t fun_lambda_fun_lambda_layoutTest_apply(struct Int32Int32Fun1 f_, int32_t x_);

int32_t fun_lambda_fun_lambda_layoutTest_fun(int32_t x_1);

int32_t fun_lambda_fun_lambda_eta2_layoutTest_fun(void const *env_, int32_t arg_);

void fun_lambda_fun_lambda_layoutTest(void);

int32_t fun_lambda_fun_lambda_main_twice(struct Int32Int32Fun1 f_1, int32_t x_2);

int32_t fun_lambda_fun_lambda_main_fun(int32_t x_3);

int32_t fun_lambda_fun_lambda_eta2_main_fun(void const *env_1, int32_t arg_1);

int32_t fun_lambda_fun_lambda_main_fun_1(int32_t x_5, int32_t y_1);

int32_t fun_lambda_fun_lambda_eta3_main_fun(void const *env_2, int32_t arg_2, int32_t arg_3);

int main(int argc, char **argv);

struct Int32Int32Fun1 {
    VoidConstPtrInt32Int32FunPtr2 fun;
    void const *env;
};

struct Int32Int32Int32Fun2 {
    VoidConstPtrInt32Int32Int32FunPtr3 fun;
    void const *env;
};

int32_t fun_lambda_fun_lambda_layoutTest_apply(struct Int32Int32Fun1 f_, int32_t x_) {
    int32_t app_;
    app_ = f_.fun(f_.env, x_);
    return app_;
}

int32_t fun_lambda_fun_lambda_layoutTest_fun(int32_t x_1) {
    return (x_1 + 3);
}

int32_t fun_lambda_fun_lambda_eta2_layoutTest_fun(void const *env_, int32_t arg_) {
    int32_t call_;
    call_ = fun_lambda_fun_lambda_layoutTest_fun(arg_);
    return call_;
}

void fun_lambda_fun_lambda_layoutTest(void) {
    int32_t a_;
    struct Int32Int32Fun1 fun_;
    int32_t call_1;
    fun_ = (struct Int32Int32Fun1){.fun = fun_lambda_fun_lambda_eta2_layoutTest_fun, .env = NULL};
    call_1 = fun_lambda_fun_lambda_layoutTest_apply(fun_, 2);
    a_ = call_1;
    if ((a_ != 5)) milone_assert_error("fun_lambda/fun_lambda.milone", 13, 2);
    return;
}

int32_t fun_lambda_fun_lambda_main_twice(struct Int32Int32Fun1 f_1, int32_t x_2) {
    int32_t app_1;
    int32_t app_2;
    app_1 = f_1.fun(f_1.env, x_2);
    app_2 = f_1.fun(f_1.env, app_1);
    return app_2;
}

int32_t fun_lambda_fun_lambda_main_fun(int32_t x_3) {
    int32_t y_;
    y_ = (x_3 + 1);
    return y_;
}

int32_t fun_lambda_fun_lambda_eta2_main_fun(void const *env_1, int32_t arg_1) {
    int32_t call_2;
    call_2 = fun_lambda_fun_lambda_main_fun(arg_1);
    return call_2;
}

int32_t fun_lambda_fun_lambda_main_fun_1(int32_t x_5, int32_t y_1) {
    return ((x_5 / y_1) + 0);
}

int32_t fun_lambda_fun_lambda_eta3_main_fun(void const *env_2, int32_t arg_2, int32_t arg_3) {
    int32_t call_3;
    call_3 = fun_lambda_fun_lambda_main_fun_1(arg_2, arg_3);
    return call_3;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    int32_t x_4;
    struct Int32Int32Fun1 fun_1;
    int32_t call_4;
    struct Int32Int32Int32Fun2 fun_2;
    int32_t app_3;
    fun_1 = (struct Int32Int32Fun1){.fun = fun_lambda_fun_lambda_eta2_main_fun, .env = NULL};
    call_4 = fun_lambda_fun_lambda_main_twice(fun_1, 40);
    x_4 = call_4;
    if ((x_4 != 42)) milone_assert_error("fun_lambda/fun_lambda.milone", 24, 2);
    fun_2 = (struct Int32Int32Int32Fun2){.fun = fun_lambda_fun_lambda_eta3_main_fun, .env = NULL};
    app_3 = fun_2.fun(fun_2.env, 84, 2);
    if ((app_3 != 42)) milone_assert_error("fun_lambda/fun_lambda.milone", 26, 2);
    fun_lambda_fun_lambda_layoutTest();
    return 0;
}
