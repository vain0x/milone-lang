#include "milone.h"

int inc_(int x_, int arg_3, int y_);

struct IntUnitTuple2;

int fun_(void* env_, int arg_);

struct IntIntFun1;

struct IntIntFun1 add_(int x_);

struct IntIntIntFun2;

int main();

int inc_(int x_, int arg_3, int y_) {
    return (x_ + y_);
}

struct IntUnitTuple2 {
    int t0;
    int t1;
};

int fun_(void* env_, int arg_) {
    int arg_1 = (*(((struct IntUnitTuple2*)env_))).t0;
    int arg_2 = (*(((struct IntUnitTuple2*)env_))).t1;
    int call_ = inc_(arg_1, 0, arg_);
    return call_;
}

struct IntIntFun1 {
    int(*fun)(void*, int);
    void* env;
};

struct IntIntFun1 add_(int x_) {
    struct IntUnitTuple2 tuple_;
    tuple_.t0 = x_;
    tuple_.t1 = 0;
    void* box_ = (void*)milone_mem_alloc(1, sizeof(struct IntUnitTuple2));
    (*(((struct IntUnitTuple2*)box_))) = tuple_;
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
    milone_assert((app_ == 5), 20, 2);
    int call_1 = 0;
    return 0;
}
