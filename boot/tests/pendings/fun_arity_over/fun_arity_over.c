#include "milone.h"

struct IntTuple1;

int inc_(struct IntTuple1 arg_3, int arg_4, int y_);

struct IntTuple1UnitTuple2;

int fun_(void* env_, int arg_);

struct IntIntFun1;

struct IntIntFun1 add_(int x_);

struct IntIntIntFun2;

int main();

struct IntTuple1 {
    int t0;
};

int inc_(struct IntTuple1 arg_3, int arg_4, int y_) {
    int x_ = arg_3.t0;
    return (x_ + y_);
}

struct IntTuple1UnitTuple2 {
    struct IntTuple1 t0;
    int t1;
};

int fun_(void* env_, int arg_) {
    struct IntTuple1 arg_1 = (*(((struct IntTuple1UnitTuple2*)env_))).t0;
    int arg_2 = (*(((struct IntTuple1UnitTuple2*)env_))).t1;
    int call_ = inc_(arg_1, 0, arg_);
    return call_;
}

struct IntIntFun1 {
    int(*fun)(void*, int);
    void* env;
};

struct IntIntFun1 add_(int x_) {
    struct IntTuple1 tuple_1;
    tuple_1.t0 = x_;
    struct IntTuple1UnitTuple2 tuple_;
    tuple_.t0 = tuple_1;
    tuple_.t1 = 0;
    void* box_ = (void*)malloc(sizeof(struct IntTuple1UnitTuple2));
    (*(((struct IntTuple1UnitTuple2*)box_))) = tuple_;
    void* env_1 = box_;
    struct IntIntFun1 fun_1 = (struct IntIntFun1){.fun = fun_, .env = env_1};
    return fun_1;
}

struct IntIntIntFun2 {
    int(*fun)(void*, int, int);
    void* env;
};

int main() {
    exit(0);
    struct IntIntIntFun2 f_ = ((struct IntIntIntFun2){});
    int app_ = f_.fun(f_.env, 2, 3);
    milone_assert((app_ == 5));
    int call_1 = 0;
    return 0;
}
