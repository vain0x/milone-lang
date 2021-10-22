#include "milone.h"

struct IntIntFun1;

struct IntIntIntFun2;

int fun_lambda_fun_lambda_main_IntIntFun1IntIntFun2_twice(struct IntIntFun1 f_1, int x_2);

int fun_lambda_fun_lambda_layoutTest_IntIntFun1IntIntFun2_apply(struct IntIntFun1 f_, int x_);

int fun_lambda_fun_lambda_layoutTest_fun(int x_1);

int fun_lambda_fun_lambda_eta2_layoutTest_fun(void const* env_, int arg_);

void fun_lambda_Program_layoutTest(void);

int fun_lambda_fun_lambda_main_fun(int x_4);

int fun_lambda_fun_lambda_eta2_main_fun(void const* env_1, int arg_1);

int fun_lambda_fun_lambda_main_fun_1(int x_5, int y_1);

int fun_lambda_fun_lambda_eta3_main_fun(void const* env_2, int arg_2, int arg_3);

int milone_main(void);

struct IntIntFun1 {
    int(*fun)(void const*, int);
    void const* env;
};

struct IntIntIntFun2 {
    int(*fun)(void const*, int, int);
    void const* env;
};

int fun_lambda_fun_lambda_main_IntIntFun1IntIntFun2_twice(struct IntIntFun1 f_1, int x_2) {
    int app_ = f_1.fun(f_1.env, x_2);
    int app_1 = f_1.fun(f_1.env, app_);
    return app_1;
}

int fun_lambda_fun_lambda_layoutTest_IntIntFun1IntIntFun2_apply(struct IntIntFun1 f_, int x_) {
    int app_2 = f_.fun(f_.env, x_);
    return app_2;
}

int fun_lambda_fun_lambda_layoutTest_fun(int x_1) {
    return (x_1 + 3);
}

int fun_lambda_fun_lambda_eta2_layoutTest_fun(void const* env_, int arg_) {
    int call_ = fun_lambda_fun_lambda_layoutTest_fun(arg_);
    return call_;
}

void fun_lambda_Program_layoutTest(void) {
    struct IntIntFun1 fun_ = (struct IntIntFun1){.fun = fun_lambda_fun_lambda_eta2_layoutTest_fun, .env = NULL};
    int call_1 = fun_lambda_fun_lambda_layoutTest_IntIntFun1IntIntFun2_apply(fun_, 2);
    int a_ = call_1;
    milone_assert((a_ == 5), 14, 2);
    return;
}

int fun_lambda_fun_lambda_main_fun(int x_4) {
    int y_ = (x_4 + 1);
    return y_;
}

int fun_lambda_fun_lambda_eta2_main_fun(void const* env_1, int arg_1) {
    int call_2 = fun_lambda_fun_lambda_main_fun(arg_1);
    return call_2;
}

int fun_lambda_fun_lambda_main_fun_1(int x_5, int y_1) {
    return ((x_5 / y_1) + 0);
}

int fun_lambda_fun_lambda_eta3_main_fun(void const* env_2, int arg_2, int arg_3) {
    int call_3 = fun_lambda_fun_lambda_main_fun_1(arg_2, arg_3);
    return call_3;
}

int milone_main(void) {
    struct IntIntFun1 fun_1 = (struct IntIntFun1){.fun = fun_lambda_fun_lambda_eta2_main_fun, .env = NULL};
    int call_4 = fun_lambda_fun_lambda_main_IntIntFun1IntIntFun2_twice(fun_1, 40);
    int x_3 = call_4;
    milone_assert((x_3 == 42), 26, 2);
    struct IntIntIntFun2 fun_2 = (struct IntIntIntFun2){.fun = fun_lambda_fun_lambda_eta3_main_fun, .env = NULL};
    int app_3 = fun_2.fun(fun_2.env, 84, 2);
    milone_assert((app_3 == 42), 28, 2);
    fun_lambda_Program_layoutTest();
    return 0;
}
