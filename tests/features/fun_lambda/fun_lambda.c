#include "milone.h"

struct IntIntFun1;

int apply_1(struct IntIntFun1 f_, int x_);

int fun_(int x_1);

int fun_3(void const* env_, int arg_);

int layoutTest_(int arg_4);

int twice_1(struct IntIntFun1 f_1, int x_2);

int fun_1(int x_4);

int fun_4(void const* env_1, int arg_1);

int fun_2(int x_5, int y_1);

int fun_5(void const* env_2, int arg_2, int arg_3);

struct IntIntIntFun2;

int main();

struct IntIntFun1 {
    int(*fun)(void const*, int);
    void const* env;
};

int apply_1(struct IntIntFun1 f_, int x_) {
    int app_ = f_.fun(f_.env, x_);
    return app_;
}

int fun_(int x_1) {
    return (x_1 + 3);
}

int fun_3(void const* env_, int arg_) {
    int call_ = fun_(arg_);
    return call_;
}

int layoutTest_(int arg_4) {
    void const* box_ = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_))) = 0;
    struct IntIntFun1 fun_6 = (struct IntIntFun1){.fun = fun_3, .env = box_};
    int call_1 = apply_1(fun_6, 2);
    int a_ = call_1;
    milone_assert((a_ == 5), 13, 2);
    return 0;
}

int twice_1(struct IntIntFun1 f_1, int x_2) {
    int app_1 = f_1.fun(f_1.env, x_2);
    int app_2 = f_1.fun(f_1.env, app_1);
    return app_2;
}

int fun_1(int x_4) {
    int y_ = (x_4 + 1);
    return y_;
}

int fun_4(void const* env_1, int arg_1) {
    int call_2 = fun_1(arg_1);
    return call_2;
}

int fun_2(int x_5, int y_1) {
    return ((x_5 / y_1) + 0);
}

int fun_5(void const* env_2, int arg_2, int arg_3) {
    int call_3 = fun_2(arg_2, arg_3);
    return call_3;
}

struct IntIntIntFun2 {
    int(*fun)(void const*, int, int);
    void const* env;
};

int main() {
    void const* box_1 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_1))) = 0;
    struct IntIntFun1 fun_7 = (struct IntIntFun1){.fun = fun_4, .env = box_1};
    int call_4 = twice_1(fun_7, 40);
    int x_3 = call_4;
    milone_assert((x_3 == 42), 24, 2);
    void const* box_2 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_2))) = 0;
    struct IntIntIntFun2 fun_8 = (struct IntIntIntFun2){.fun = fun_5, .env = box_2};
    int app_3 = fun_8.fun(fun_8.env, 84, 2);
    milone_assert((app_3 == 42), 26, 2);
    int call_5 = layoutTest_(0);
    return 0;
}
