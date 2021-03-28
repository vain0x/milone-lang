#include "milone.h"

struct IntUnitTuple2;

struct IntStringTuple2;

struct IntStringTuple2Option;

int fst_(struct IntUnitTuple2 arg_);

int f_1(void const* boxedPair_, char arg_1);

int fstUnbox_(void const* boxedPair_, struct IntStringTuple2Option phantom_);

char fun_generic_ty_degeneration_Program_testCase(struct IntStringTuple2 kv_);

int milone_main();

struct IntUnitTuple2 {
    int t0;
    char t1;
};

struct IntStringTuple2 {
    int t0;
    struct String t1;
};

struct IntStringTuple2Option {
    bool some;
    struct IntStringTuple2 value;
};

int fst_(struct IntUnitTuple2 arg_) {
    int x_ = arg_.t0;
    return x_;
}

int f_1(void const* boxedPair_, char arg_1) {
    int call_ = fst_((*(((struct IntUnitTuple2 const*)boxedPair_))));
    return call_;
}

int fstUnbox_(void const* boxedPair_, struct IntStringTuple2Option phantom_) {
    int call_1 = f_1(boxedPair_, 0);
    return call_1;
}

char fun_generic_ty_degeneration_Program_testCase(struct IntStringTuple2 kv_) {
    void const* box_ = milone_mem_alloc(1, sizeof(struct IntStringTuple2));
    (*(((struct IntStringTuple2*)box_))) = kv_;
    int call_2 = fstUnbox_(box_, (struct IntStringTuple2Option){.some = false});
    milone_assert((call_2 == 0), 18, 2);
    return 0;
}

int milone_main() {
    struct IntStringTuple2 tuple_ = (struct IntStringTuple2){.t0 = 0, .t1 = (struct String){.str = "right", .len = 5}};
    char call_3 = fun_generic_ty_degeneration_Program_testCase(tuple_);
    return 0;
}
