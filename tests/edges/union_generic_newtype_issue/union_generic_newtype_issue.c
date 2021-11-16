#include "milone.h"

struct IntIntTuple2_;

struct IntIntTuple2MyOption1_;

struct IntIntTuple2MyOption1_ union_generic_newtype_issue_union_generic_newtype_issue_f(void);

int milone_main(void);

struct IntIntTuple2_ {
    int t0;
    int t1;
};

enum IntIntTuple2MyOption1_Discriminant {
    MyNone_,
    MySome_,
};

struct IntIntTuple2MyOption1_ {
    enum IntIntTuple2MyOption1_Discriminant discriminant;
    union {
        struct IntIntTuple2_ MySome_;
    };
};

struct IntIntTuple2MyOption1_ union_generic_newtype_issue_union_generic_newtype_issue_f(void) {
    struct IntIntTuple2_ IntIntTuple2_ = (struct IntIntTuple2_){.t0 = 1, .t1 = 0};
    struct IntIntTuple2MyOption1_ variant_ = (struct IntIntTuple2MyOption1_){.discriminant = MySome_, .MySome_ = IntIntTuple2_};
    return variant_;
}

int milone_main(void) {
    char switch_;
    struct IntIntTuple2MyOption1_ call_ = union_generic_newtype_issue_union_generic_newtype_issue_f();
    switch (call_.discriminant) {
        case MySome_:
            goto clause_2;

        case MyNone_:
            goto clause_3;

        default:
            exit(1);
    }
clause_2:;
    switch_ = 0;
    goto switch_next_1;
clause_3:;
    milone_assert(false, 16, 16);
    switch_ = 0;
    goto switch_next_1;
switch_next_1:;
    return 0;
}
