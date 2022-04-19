#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

typedef int32_t(*VoidConstPtrInt32Int32FunPtr2)(void const*, int32_t);

struct Int32Int32Fun1;

struct Int32Int32Tuple2_;

typedef int32_t(*VoidConstPtrInt32Int32Int32FunPtr3)(void const*, int32_t, int32_t);

struct Int32Int32Int32Fun2;

typedef int32_t(*VoidConstPtrInt32Int32Int32Int32Int32FunPtr5)(void const*, int32_t, int32_t, int32_t, int32_t);

struct Int32Int32Int32Int32Int32Fun4;

int32_t fun_partial_app_fun_partial_app_twice(struct Int32Int32Fun1 f_, int32_t x_);

int32_t fun_partial_app_fun_partial_app_dec(int32_t y_, int32_t x_1);

int32_t fun_partial_app_fun_partial_app_add4(int32_t x1_, int32_t x2_, int32_t x3_, int32_t x4_);

int32_t fun_partial_app_fun_partial_app_eta2_main_dec(void const* env_, int32_t arg_);

int32_t fun_partial_app_fun_partial_app_eta3_main_add4(void const* env_1, int32_t arg_2, int32_t arg_3);

int32_t fun_partial_app_fun_partial_app_eta5_main_add4(void const* env_2, int32_t arg_6, int32_t arg_7, int32_t arg_8, int32_t arg_9);

int main(int argc, char** argv);

struct Int32Int32Fun1 {
    VoidConstPtrInt32Int32FunPtr2 fun;
    void const* env;
};

struct Int32Int32Tuple2_ {
    int32_t t0;
    int32_t t1;
};

struct Int32Int32Int32Fun2 {
    VoidConstPtrInt32Int32Int32FunPtr3 fun;
    void const* env;
};

struct Int32Int32Int32Int32Int32Fun4 {
    VoidConstPtrInt32Int32Int32Int32Int32FunPtr5 fun;
    void const* env;
};

int32_t fun_partial_app_fun_partial_app_twice(struct Int32Int32Fun1 f_, int32_t x_) {
    int32_t app_;
    int32_t app_1;
    app_ = f_.fun(f_.env, x_);
    app_1 = f_.fun(f_.env, app_);
    return app_1;
}

int32_t fun_partial_app_fun_partial_app_dec(int32_t y_, int32_t x_1) {
    return (x_1 - y_);
}

int32_t fun_partial_app_fun_partial_app_add4(int32_t x1_, int32_t x2_, int32_t x3_, int32_t x4_) {
    return (((x1_ + x2_) + x3_) + x4_);
}

int32_t fun_partial_app_fun_partial_app_eta2_main_dec(void const* env_, int32_t arg_) {
    int32_t arg_1;
    int32_t call_;
    arg_1 = ((int32_t)((intptr_t)env_));
    call_ = fun_partial_app_fun_partial_app_dec(arg_1, arg_);
    return call_;
}

int32_t fun_partial_app_fun_partial_app_eta3_main_add4(void const* env_1, int32_t arg_2, int32_t arg_3) {
    int32_t arg_4;
    int32_t arg_5;
    int32_t call_1;
    arg_4 = (*(((struct Int32Int32Tuple2_ const*)env_1))).t0;
    arg_5 = (*(((struct Int32Int32Tuple2_ const*)env_1))).t1;
    call_1 = fun_partial_app_fun_partial_app_add4(arg_4, arg_5, arg_2, arg_3);
    return call_1;
}

int32_t fun_partial_app_fun_partial_app_eta5_main_add4(void const* env_2, int32_t arg_6, int32_t arg_7, int32_t arg_8, int32_t arg_9) {
    int32_t call_2;
    call_2 = fun_partial_app_fun_partial_app_add4(arg_6, arg_7, arg_8, arg_9);
    return call_2;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    struct Int32Int32Fun1 dec3_;
    struct Int32Int32Int32Fun2 add2_;
    struct Int32Int32Int32Int32Int32Fun4 f_1;
    struct Int32Int32Fun1 fun_;
    int32_t call_3;
    struct Int32Int32Tuple2_ Int32Int32Tuple2_;
    void const* box_;
    struct Int32Int32Int32Fun2 fun_1;
    int32_t app_2;
    struct Int32Int32Int32Int32Int32Fun4 fun_2;
    int32_t app_3;
    fun_ = (struct Int32Int32Fun1){.fun = fun_partial_app_fun_partial_app_eta2_main_dec, .env = ((void const*)((intptr_t)3))};
    dec3_ = fun_;
    call_3 = fun_partial_app_fun_partial_app_twice(dec3_, 8);
    milone_assert((call_3 == 2), (struct String){.ptr = "fun_partial_app/fun_partial_app.milone", .len = 38}, 12, 2);
    Int32Int32Tuple2_ = (struct Int32Int32Tuple2_){.t0 = 2, .t1 = 3};
    box_ = ((void const*)milone_region_alloc(1, sizeof(struct Int32Int32Tuple2_)));
    (*(((struct Int32Int32Tuple2_*)box_))) = Int32Int32Tuple2_;
    fun_1 = (struct Int32Int32Int32Fun2){.fun = fun_partial_app_fun_partial_app_eta3_main_add4, .env = box_};
    add2_ = fun_1;
    app_2 = add2_.fun(add2_.env, 5, 7);
    milone_assert((app_2 == (((2 + 3) + 5) + 7)), (struct String){.ptr = "fun_partial_app/fun_partial_app.milone", .len = 38}, 15, 2);
    fun_2 = (struct Int32Int32Int32Int32Int32Fun4){.fun = fun_partial_app_fun_partial_app_eta5_main_add4, .env = NULL};
    f_1 = fun_2;
    app_3 = f_1.fun(f_1.env, 1, 2, 3, 4);
    milone_assert((app_3 == (((1 + 2) + 3) + 4)), (struct String){.ptr = "fun_partial_app/fun_partial_app.milone", .len = 38}, 18, 2);
    return 0;
}
