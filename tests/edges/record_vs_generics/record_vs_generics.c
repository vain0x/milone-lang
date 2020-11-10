#include "milone.h"

void* constant_1(void* value_, int arg_2);

struct ObjectTuple1;

void* fun_(void* env_, int arg_);

struct IntTuple1;

struct UnitObjectFun1;

int main();

void* constant_1(void* value_, int arg_2) {
    return value_;
}

struct ObjectTuple1 {
    void* t0;
};

void* fun_(void* env_, int arg_) {
    void* arg_1 = (*(((struct ObjectTuple1*)env_))).t0;
    void* call_ = constant_1(arg_1, 0);
    return call_;
}

struct IntTuple1 {
    int t0;
};

struct UnitObjectFun1 {
    void*(*fun)(void*, int);
    void* env;
};

int main() {
    struct IntTuple1 tuple_1;
    tuple_1.t0 = 42;
    void* box_ = (void*)milone_mem_alloc(1, sizeof(struct IntTuple1));
    (*(((struct IntTuple1*)box_))) = tuple_1;
    struct ObjectTuple1 tuple_;
    tuple_.t0 = box_;
    void* box_1 = (void*)milone_mem_alloc(1, sizeof(struct ObjectTuple1));
    (*(((struct ObjectTuple1*)box_1))) = tuple_;
    void* env_1 = box_1;
    struct UnitObjectFun1 fun_1 = (struct UnitObjectFun1){.fun = fun_, .env = env_1};
    struct UnitObjectFun1 f_ = fun_1;
    void* app_ = f_.fun(f_.env, 0);
    void* wrapper_ = app_;
    milone_assert(((*(((struct IntTuple1*)wrapper_))).t0 == 42), 12, 2);
    int call_1 = 0;
    return 0;
}
