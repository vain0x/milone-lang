#include <milone.h>

struct IntIntFun1;

struct IntIntTuple2_;

struct IntIntIntFun2;

struct IntIntIntIntIntFun4;

int fun_partial_app_Program_twice(struct IntIntFun1 f_, int x_);

int fun_partial_app_Program_dec(int y_, int x_1);

int fun_partial_app_Program_add4(int x1_, int x2_, int x3_, int x4_);

int fun_partial_app_fun_partial_app_eta2_main_dec(void const* env_, int arg_);

int fun_partial_app_fun_partial_app_eta3_main_add4(void const* env_1, int arg_2, int arg_3);

int fun_partial_app_fun_partial_app_eta5_main_add4(void const* env_2, int arg_6, int arg_7, int arg_8, int arg_9);

int main(int argc, char** argv);

struct IntIntFun1 {
    int(*fun)(void const*, int);
    void const* env;
};

struct IntIntTuple2_ {
    int t0;
    int t1;
};

struct IntIntIntFun2 {
    int(*fun)(void const*, int, int);
    void const* env;
};

struct IntIntIntIntIntFun4 {
    int(*fun)(void const*, int, int, int, int);
    void const* env;
};

int fun_partial_app_Program_twice(struct IntIntFun1 f_, int x_) {
    int app_ = f_.fun(f_.env, x_);
    int app_1 = f_.fun(f_.env, app_);
    return app_1;
}

int fun_partial_app_Program_dec(int y_, int x_1) {
    return (x_1 - y_);
}

int fun_partial_app_Program_add4(int x1_, int x2_, int x3_, int x4_) {
    return (((x1_ + x2_) + x3_) + x4_);
}

int fun_partial_app_fun_partial_app_eta2_main_dec(void const* env_, int arg_) {
    int arg_1 = ((int)((intptr_t)env_));
    int call_ = fun_partial_app_Program_dec(arg_1, arg_);
    return call_;
}

int fun_partial_app_fun_partial_app_eta3_main_add4(void const* env_1, int arg_2, int arg_3) {
    int arg_4 = (*(((struct IntIntTuple2_ const*)env_1))).t0;
    int arg_5 = (*(((struct IntIntTuple2_ const*)env_1))).t1;
    int call_1 = fun_partial_app_Program_add4(arg_4, arg_5, arg_2, arg_3);
    return call_1;
}

int fun_partial_app_fun_partial_app_eta5_main_add4(void const* env_2, int arg_6, int arg_7, int arg_8, int arg_9) {
    int call_2 = fun_partial_app_Program_add4(arg_6, arg_7, arg_8, arg_9);
    return call_2;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    struct IntIntFun1 fun_ = (struct IntIntFun1){.fun = fun_partial_app_fun_partial_app_eta2_main_dec, .env = ((void const*)((intptr_t)3))};
    struct IntIntFun1 dec3_ = fun_;
    int call_3 = fun_partial_app_Program_twice(dec3_, 8);
    milone_assert((call_3 == 2), (struct String){.str = "fun_partial_app/fun_partial_app.milone", .len = 38}, 12, 2);
    struct IntIntTuple2_ IntIntTuple2_ = (struct IntIntTuple2_){.t0 = 2, .t1 = 3};
    void const* box_ = milone_mem_alloc(1, sizeof(struct IntIntTuple2_));
    (*(((struct IntIntTuple2_*)box_))) = IntIntTuple2_;
    struct IntIntIntFun2 fun_1 = (struct IntIntIntFun2){.fun = fun_partial_app_fun_partial_app_eta3_main_add4, .env = box_};
    struct IntIntIntFun2 add2_ = fun_1;
    int app_2 = add2_.fun(add2_.env, 5, 7);
    milone_assert((app_2 == (((2 + 3) + 5) + 7)), (struct String){.str = "fun_partial_app/fun_partial_app.milone", .len = 38}, 15, 2);
    struct IntIntIntIntIntFun4 fun_2 = (struct IntIntIntIntIntFun4){.fun = fun_partial_app_fun_partial_app_eta5_main_add4, .env = NULL};
    struct IntIntIntIntIntFun4 f_1 = fun_2;
    int app_3 = f_1.fun(f_1.env, 1, 2, 3, 4);
    milone_assert((app_3 == (((1 + 2) + 3) + 4)), (struct String){.str = "fun_partial_app/fun_partial_app.milone", .len = 38}, 18, 2);
    return 0;
}
