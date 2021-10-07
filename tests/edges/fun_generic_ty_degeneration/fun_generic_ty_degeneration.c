#include "milone.h"

struct IntStringTuple2_;

struct IntStringTuple2Option_;

int myFst_(struct IntStringTuple2_ arg_);

int f_(void const* boxedPair_);

int fstUnbox_(void const* boxedPair_, struct IntStringTuple2Option_ phantom_);

void fun_generic_ty_degeneration_Program_testCase(struct IntStringTuple2_ kv_);

int milone_main(void);

struct IntStringTuple2_ {
    int t0;
    struct String t1;
};

enum IntStringTuple2Option_Discriminant {
    None_,
    Some_,
};

struct IntStringTuple2Option_ {
    enum IntStringTuple2Option_Discriminant discriminant;
    union {
        struct IntStringTuple2_ Some_;
    };
};

int myFst_(struct IntStringTuple2_ arg_) {
    int x_ = arg_.t0;
    return x_;
}

int f_(void const* boxedPair_) {
    int call_ = myFst_((*(((struct IntStringTuple2_ const*)boxedPair_))));
    return call_;
}

int fstUnbox_(void const* boxedPair_, struct IntStringTuple2Option_ phantom_) {
    int call_1 = f_(boxedPair_);
    return call_1;
}

void fun_generic_ty_degeneration_Program_testCase(struct IntStringTuple2_ kv_) {
    void const* box_ = milone_mem_alloc(1, sizeof(struct IntStringTuple2_));
    (*(((struct IntStringTuple2_*)box_))) = kv_;
    int call_2 = fstUnbox_(box_, (struct IntStringTuple2Option_){.discriminant = None_});
    milone_assert((call_2 == 0), 20, 2);
    return;
}

int milone_main(void) {
    struct IntStringTuple2_ IntStringTuple2_ = (struct IntStringTuple2_){.t0 = 0, .t1 = (struct String){.str = "right", .len = 5}};
    fun_generic_ty_degeneration_Program_testCase(IntStringTuple2_);
    return 0;
}
