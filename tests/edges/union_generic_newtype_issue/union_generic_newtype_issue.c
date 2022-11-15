#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32Int32Tuple2_;

struct Int32Int32Tuple2MyOption1_;

struct Int32Int32Tuple2MyOption1_ union_generic_newtype_issue_union_generic_newtype_issue_f(void);

int main(int argc, char **argv);

struct Int32Int32Tuple2_ {
    int32_t t0;
    int32_t t1;
};

enum Int32Int32Tuple2MyOption1_Discriminant {
    Int32Int32Tuple2MyOption1_MyNone,
    Int32Int32Tuple2MyOption1_MySome,
};

struct Int32Int32Tuple2MyOption1_ {
    enum Int32Int32Tuple2MyOption1_Discriminant discriminant;
    union {
        struct Int32Int32Tuple2_ Int32Int32Tuple2MyOption1_MySome;
    };
};

struct Int32Int32Tuple2MyOption1_ union_generic_newtype_issue_union_generic_newtype_issue_f(void) {
    struct Int32Int32Tuple2_ Int32Int32Tuple2_;
    struct Int32Int32Tuple2MyOption1_ variant_;
    Int32Int32Tuple2_ = (struct Int32Int32Tuple2_){.t0 = 1, .t1 = 0};
    variant_ = (struct Int32Int32Tuple2MyOption1_){.discriminant = Int32Int32Tuple2MyOption1_MySome, .Int32Int32Tuple2MyOption1_MySome = Int32Int32Tuple2_};
    return variant_;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    char switch_;
    struct Int32Int32Tuple2MyOption1_ call_;
    call_ = union_generic_newtype_issue_union_generic_newtype_issue_f();
    switch (call_.discriminant) {
        case Int32Int32Tuple2MyOption1_MySome:
            goto clause_2;

        case Int32Int32Tuple2MyOption1_MyNone:
            goto clause_3;

        default:
            milone_exhaust_error("union_generic_newtype_issue/union_generic_newtype_issue.milone", 14, 2);
    }
clause_2:;
    switch_ = 0;
    goto switch_next_1;
clause_3:;
    if (true) milone_assert_error("union_generic_newtype_issue/union_generic_newtype_issue.milone", 16, 16);
    switch_ = 0;
    goto switch_next_1;
switch_next_1:;
    return 0;
}
