#include "milone.h"

struct IntUnitTuple2;

int fst_1(struct IntUnitTuple2 arg_);

int f_1(void const* boxedPair_, char arg_1);

struct IntStringTuple2;

struct IntStringTuple2Option;

int fstUnbox_1(void const* boxedPair_, struct IntStringTuple2Option phantom_);

char testCase_(struct IntStringTuple2 kv_);

int milone_main();

struct IntUnitTuple2 {
    int t0;
    char t1;
};

int fst_1(struct IntUnitTuple2 arg_) {
    int x_ = arg_.t0;
    return x_;
}

int f_1(void const* boxedPair_, char arg_1) {
    int call_ = fst_1((*(((struct IntUnitTuple2 const*)boxedPair_))));
    return call_;
}

struct IntStringTuple2 {
    int t0;
    struct String t1;
};

struct IntStringTuple2Option {
    bool some;
    struct IntStringTuple2 value;
};

int fstUnbox_1(void const* boxedPair_, struct IntStringTuple2Option phantom_) {
    int call_1 = f_1(boxedPair_, 0);
    return call_1;
}

char testCase_(struct IntStringTuple2 kv_) {
    void const* box_ = milone_mem_alloc(1, sizeof(struct IntStringTuple2));
    (*(((struct IntStringTuple2*)box_))) = kv_;
    int call_2 = fstUnbox_1(box_, ((struct IntStringTuple2Option){}));
    milone_assert((call_2 == 0), 18, 2);
    return 0;
}

int milone_main() {
    struct IntStringTuple2 tuple_ = (struct IntStringTuple2){.t0 = 0, .t1 = (struct String){.str = "right", .len = 5}};
    char call_3 = testCase_(tuple_);
    return 0;
}
