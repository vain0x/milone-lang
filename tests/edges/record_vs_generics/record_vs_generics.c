#include "milone.h"

struct IntWrapper_;

struct UnitIntWrapper_Fun1;

struct IntWrapper_ constant_(struct IntWrapper_ value_, char arg_2);

struct IntWrapper_ fun_(void const* env_, char arg_);

int milone_main();

struct IntWrapper_ {
    int t0;
};

struct UnitIntWrapper_Fun1 {
    struct IntWrapper_(*fun)(void const*, char);
    void const* env;
};

struct IntWrapper_ constant_(struct IntWrapper_ value_, char arg_2) {
    return value_;
}

struct IntWrapper_ fun_(void const* env_, char arg_) {
    struct IntWrapper_ arg_1 = (*(((struct IntWrapper_ const*)env_)));
    struct IntWrapper_ call_ = constant_(arg_1, 0);
    return call_;
}

int milone_main() {
    struct IntWrapper_ IntWrapper_ = (struct IntWrapper_){.t0 = 42};
    void const* box_ = milone_mem_alloc(1, sizeof(struct IntWrapper_));
    (*(((struct IntWrapper_*)box_))) = IntWrapper_;
    struct UnitIntWrapper_Fun1 fun_1 = (struct UnitIntWrapper_Fun1){.fun = fun_, .env = box_};
    struct UnitIntWrapper_Fun1 f_ = fun_1;
    struct IntWrapper_ app_ = f_.fun(f_.env, 0);
    struct IntWrapper_ wrapper_ = app_;
    milone_assert((wrapper_.t0 == 42), 12, 2);
    return 0;
}
