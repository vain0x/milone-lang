#include "milone.h"

struct IntWrapper_;

struct IntWrapper_ constant_1(struct IntWrapper_ value_, int arg_2);

struct IntWrapper_Tuple1;

struct IntWrapper_ fun_(void* env_, int arg_);

struct UnitIntWrapper_Fun1;

int main();

struct IntWrapper_ {
    int Value;
};

struct IntWrapper_ constant_1(struct IntWrapper_ value_, int arg_2) {
    return value_;
}

struct IntWrapper_Tuple1 {
    struct IntWrapper_ t0;
};

struct IntWrapper_ fun_(void* env_, int arg_) {
    struct IntWrapper_ arg_1 = (*(((struct IntWrapper_Tuple1*)env_))).t0;
    struct IntWrapper_ call_ = constant_1(arg_1, 0);
    return call_;
}

struct UnitIntWrapper_Fun1 {
    struct IntWrapper_(*fun)(void*, int);
    void* env;
};

int main() {
    struct IntWrapper_ IntWrapper_;
    IntWrapper_.Value = 42;
    struct IntWrapper_Tuple1 tuple_;
    tuple_.t0 = IntWrapper_;
    void* box_ = milone_mem_alloc(1, sizeof(struct IntWrapper_Tuple1));
    (*(((struct IntWrapper_Tuple1*)box_))) = tuple_;
    void* env_1 = box_;
    struct UnitIntWrapper_Fun1 fun_1 = (struct UnitIntWrapper_Fun1){.fun = fun_, .env = env_1};
    struct UnitIntWrapper_Fun1 f_ = fun_1;
    struct IntWrapper_ app_ = f_.fun(f_.env, 0);
    struct IntWrapper_ wrapper_ = app_;
    milone_assert((wrapper_.Value == 42), 12, 2);
    return 0;
}
