#include "milone.h"

struct IntIntFun1;

int twice_(struct IntIntFun1 f_, int x_);

int dec_(int y_, int x_1);

int add4_(int x1_, int x2_, int x3_, int x4_);

struct IntTuple1;

int fun_(void const* env_, int arg_);

struct IntIntTuple2;

int fun_1(void const* env_1, int arg_2, int arg_3);

int fun_2(void const* env_2, int arg_6, int arg_7, int arg_8, int arg_9);

struct IntIntIntFun2;

struct IntIntIntIntIntFun4;

int main();

struct IntIntFun1 {
    int(*fun)(void const*, int);
    void const* env;
};

int twice_(struct IntIntFun1 f_, int x_) {
    int app_ = f_.fun(f_.env, x_);
    int app_1 = f_.fun(f_.env, app_);
    return app_1;
}

int dec_(int y_, int x_1) {
    return (x_1 - y_);
}

int add4_(int x1_, int x2_, int x3_, int x4_) {
    return (((x1_ + x2_) + x3_) + x4_);
}

struct IntTuple1 {
    int t0;
};

int fun_(void const* env_, int arg_) {
    int arg_1 = (*(((struct IntTuple1 const*)env_))).t0;
    int call_ = dec_(arg_1, arg_);
    return call_;
}

struct IntIntTuple2 {
    int t0;
    int t1;
};

int fun_1(void const* env_1, int arg_2, int arg_3) {
    int arg_4 = (*(((struct IntIntTuple2 const*)env_1))).t0;
    int arg_5 = (*(((struct IntIntTuple2 const*)env_1))).t1;
    int call_1 = add4_(arg_4, arg_5, arg_2, arg_3);
    return call_1;
}

int fun_2(void const* env_2, int arg_6, int arg_7, int arg_8, int arg_9) {
    int call_2 = add4_(arg_6, arg_7, arg_8, arg_9);
    return call_2;
}

struct IntIntIntFun2 {
    int(*fun)(void const*, int, int);
    void const* env;
};

struct IntIntIntIntIntFun4 {
    int(*fun)(void const*, int, int, int, int);
    void const* env;
};

int main() {
    struct IntTuple1 tuple_;
    tuple_.t0 = 3;
    void const* box_ = milone_mem_alloc(1, sizeof(struct IntTuple1));
    (*(((struct IntTuple1*)box_))) = tuple_;
    void const* env_3 = box_;
    struct IntIntFun1 fun_3 = (struct IntIntFun1){.fun = fun_, .env = env_3};
    struct IntIntFun1 dec3_ = fun_3;
    int call_3 = twice_(dec3_, 8);
    milone_assert((call_3 == 2), 12, 2);
    struct IntIntTuple2 tuple_1;
    tuple_1.t0 = 2;
    tuple_1.t1 = 3;
    void const* box_1 = milone_mem_alloc(1, sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)box_1))) = tuple_1;
    void const* env_4 = box_1;
    struct IntIntIntFun2 fun_4 = (struct IntIntIntFun2){.fun = fun_1, .env = env_4};
    struct IntIntIntFun2 add2_ = fun_4;
    int app_2 = add2_.fun(add2_.env, 5, 7);
    milone_assert((app_2 == (((2 + 3) + 5) + 7)), 15, 2);
    void const* box_2 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_2))) = 0;
    void const* env_5 = box_2;
    struct IntIntIntIntIntFun4 fun_5 = (struct IntIntIntIntIntFun4){.fun = fun_2, .env = env_5};
    struct IntIntIntIntIntFun4 f_1 = fun_5;
    int app_3 = f_1.fun(f_1.env, 1, 2, 3, 4);
    milone_assert((app_3 == (((1 + 2) + 3) + 4)), 18, 2);
    return 0;
}