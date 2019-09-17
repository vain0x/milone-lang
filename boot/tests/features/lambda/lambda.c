#include "milone.h"

struct IntIntFun1;

int twice_1(struct IntIntFun1 f_, int x_);

int fun_(int x_2);

int fun_2(void* env_, int arg_);

int fun_1(int x_3, int y_1);

int fun_3(void* env_1, int arg_1, int arg_2);

struct IntIntIntFun2;

int main();

struct IntIntFun1 {
    int(*fun)(void*, int);
    void* env;
};

int twice_1(struct IntIntFun1 f_, int x_) {
    int app_ = f_.fun(f_.env, x_);
    int app_1 = f_.fun(f_.env, app_);
    return app_1;
}

int fun_(int x_2) {
    int y_ = (x_2 + 1);
    return y_;
}

int fun_2(void* env_, int arg_) {
    int call_ = fun_(arg_);
    return call_;
}

int fun_1(int x_3, int y_1) {
    return ((x_3 / y_1) + 0);
}

int fun_3(void* env_1, int arg_1, int arg_2) {
    int call_1 = fun_1(arg_1, arg_2);
    return call_1;
}

struct IntIntIntFun2 {
    int(*fun)(void*, int, int);
    void* env;
};

int main() {
    void* box_ = (void*)malloc(sizeof(int));
    (*(((int*)box_))) = 0;
    void* env_2 = box_;
    struct IntIntFun1 fun_4 = (struct IntIntFun1){.fun = fun_2, .env = env_2};
    int call_2 = twice_1(fun_4, 40);
    int x_1 = call_2;
    milone_assert((x_1 == 42), 7, 2);
    int call_3 = 0;
    void* box_1 = (void*)malloc(sizeof(int));
    (*(((int*)box_1))) = 0;
    void* env_3 = box_1;
    struct IntIntIntFun2 fun_5 = (struct IntIntIntFun2){.fun = fun_3, .env = env_3};
    int app_2 = fun_5.fun(fun_5.env, 84, 2);
    milone_assert((app_2 == 42), 9, 2);
    int call_4 = 0;
    return 0;
}
