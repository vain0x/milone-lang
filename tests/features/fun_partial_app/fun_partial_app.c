#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

typedef int(*VoidConstPtrIntIntFunPtr2)(void const*, int);

struct IntIntFun1;

struct IntIntTuple2_;

typedef int(*VoidConstPtrIntIntIntFunPtr3)(void const*, int, int);

struct IntIntIntFun2;

typedef int(*VoidConstPtrIntIntIntIntIntFunPtr5)(void const*, int, int, int, int);

struct IntIntIntIntIntFun4;

int fun_partial_app_fun_partial_app_twice(struct IntIntFun1 f_, int x_);

int fun_partial_app_fun_partial_app_dec(int y_, int x_1);

int fun_partial_app_fun_partial_app_add4(int x1_, int x2_, int x3_, int x4_);

int fun_partial_app_fun_partial_app_eta2_main_dec(void const* env_, int arg_);

int fun_partial_app_fun_partial_app_eta3_main_add4(void const* env_1, int arg_2, int arg_3);

int fun_partial_app_fun_partial_app_eta5_main_add4(void const* env_2, int arg_6, int arg_7, int arg_8, int arg_9);

int main(int argc, char** argv);

struct IntIntFun1 {
    VoidConstPtrIntIntFunPtr2 fun;
    void const* env;
};

struct IntIntTuple2_ {
    int t0;
    int t1;
};

struct IntIntIntFun2 {
    VoidConstPtrIntIntIntFunPtr3 fun;
    void const* env;
};

struct IntIntIntIntIntFun4 {
    VoidConstPtrIntIntIntIntIntFunPtr5 fun;
    void const* env;
};

int fun_partial_app_fun_partial_app_twice(struct IntIntFun1 f_, int x_) {
    int app_;
    int app_1;
    app_ = f_.fun(f_.env, x_);
    app_1 = f_.fun(f_.env, app_);
    return app_1;
}

int fun_partial_app_fun_partial_app_dec(int y_, int x_1) {
    return (x_1 - y_);
}

int fun_partial_app_fun_partial_app_add4(int x1_, int x2_, int x3_, int x4_) {
    return (((x1_ + x2_) + x3_) + x4_);
}

int fun_partial_app_fun_partial_app_eta2_main_dec(void const* env_, int arg_) {
    int arg_1;
    int call_;
    arg_1 = ((int)((intptr_t)env_));
    call_ = fun_partial_app_fun_partial_app_dec(arg_1, arg_);
    return call_;
}

int fun_partial_app_fun_partial_app_eta3_main_add4(void const* env_1, int arg_2, int arg_3) {
    int arg_4;
    int arg_5;
    int call_1;
    arg_4 = (*(((struct IntIntTuple2_ const*)env_1))).t0;
    arg_5 = (*(((struct IntIntTuple2_ const*)env_1))).t1;
    call_1 = fun_partial_app_fun_partial_app_add4(arg_4, arg_5, arg_2, arg_3);
    return call_1;
}

int fun_partial_app_fun_partial_app_eta5_main_add4(void const* env_2, int arg_6, int arg_7, int arg_8, int arg_9) {
    int call_2;
    call_2 = fun_partial_app_fun_partial_app_add4(arg_6, arg_7, arg_8, arg_9);
    return call_2;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    struct IntIntFun1 dec3_;
    struct IntIntIntFun2 add2_;
    struct IntIntIntIntIntFun4 f_1;
    struct IntIntFun1 fun_;
    int call_3;
    struct IntIntTuple2_ IntIntTuple2_;
    void const* box_;
    struct IntIntIntFun2 fun_1;
    int app_2;
    struct IntIntIntIntIntFun4 fun_2;
    int app_3;
    fun_ = (struct IntIntFun1){.fun = fun_partial_app_fun_partial_app_eta2_main_dec, .env = ((void const*)((intptr_t)3))};
    dec3_ = fun_;
    call_3 = fun_partial_app_fun_partial_app_twice(dec3_, 8);
    milone_assert((call_3 == 2), (struct String){.ptr = "fun_partial_app/fun_partial_app.milone", .len = 38}, 12, 2);
    IntIntTuple2_ = (struct IntIntTuple2_){.t0 = 2, .t1 = 3};
    box_ = ((void const*)milone_region_alloc(1, sizeof(struct IntIntTuple2_)));
    (*(((struct IntIntTuple2_*)box_))) = IntIntTuple2_;
    fun_1 = (struct IntIntIntFun2){.fun = fun_partial_app_fun_partial_app_eta3_main_add4, .env = box_};
    add2_ = fun_1;
    app_2 = add2_.fun(add2_.env, 5, 7);
    milone_assert((app_2 == (((2 + 3) + 5) + 7)), (struct String){.ptr = "fun_partial_app/fun_partial_app.milone", .len = 38}, 15, 2);
    fun_2 = (struct IntIntIntIntIntFun4){.fun = fun_partial_app_fun_partial_app_eta5_main_add4, .env = NULL};
    f_1 = fun_2;
    app_3 = f_1.fun(f_1.env, 1, 2, 3, 4);
    milone_assert((app_3 == (((1 + 2) + 3) + 4)), (struct String){.ptr = "fun_partial_app/fun_partial_app.milone", .len = 38}, 18, 2);
    return 0;
}
