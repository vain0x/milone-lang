#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct StringMyOption1_;

struct Int32MyOption1_;

struct UnitMyOption1_;

_Noreturn void MiloneCore_Prelude_exit(int32_t);

struct String union_generic_union_generic_StringMyOption1StringFun1_unwrap(struct StringMyOption1_ opt_1);

bool union_generic_union_generic_StringMyOption1BoolFun1_isNone(struct StringMyOption1_ opt_);

int32_t union_generic_union_generic_Int32MyOption1Int32Fun1_unwrap(struct Int32MyOption1_ opt_1);

bool union_generic_union_generic_Int32MyOption1BoolFun1_isNone(struct Int32MyOption1_ opt_);

bool union_generic_union_generic_UnitMyOption1BoolFun1_isNone(struct UnitMyOption1_ opt_);

void union_generic_union_generic_testBasicUsage(void);

void union_generic_union_generic_testAnotherInstance(void);

int main(int argc, char **argv);

enum StringMyOption1_Discriminant {
    StringMyOption1_MyNone,
    StringMyOption1_MySome,
};

struct StringMyOption1_ {
    enum StringMyOption1_Discriminant discriminant;
    union {
        struct String StringMyOption1_MySome;
    };
};

enum Int32MyOption1_Discriminant {
    Int32MyOption1_MyNone,
    Int32MyOption1_MySome,
};

struct Int32MyOption1_ {
    enum Int32MyOption1_Discriminant discriminant;
    union {
        int32_t Int32MyOption1_MySome;
    };
};

enum UnitMyOption1_Discriminant {
    UnitMyOption1_MyNone,
    UnitMyOption1_MySome,
};

struct UnitMyOption1_ {
    enum UnitMyOption1_Discriminant discriminant;
    union {
        char UnitMyOption1_MySome;
    };
};

struct String union_generic_union_generic_StringMyOption1StringFun1_unwrap(struct StringMyOption1_ opt_1) {
    struct String it_;
    struct String match_;
    if ((opt_1.discriminant != StringMyOption1_MySome)) goto next_2;
    it_ = opt_1.StringMyOption1_MySome;
    match_ = it_;
    goto end_match_1;
next_2:;
    if ((opt_1.discriminant != StringMyOption1_MyNone)) goto next_3;
    if (true) milone_assert_error("union_generic/union_generic.milone", 16, 4);
    MiloneCore_Prelude_exit(1);
    milone_never_error("union_generic/union_generic.milone", 17, 8);
next_3:;
    milone_exhaust_error("union_generic/union_generic.milone", 12, 2);
end_match_1:;
    return match_;
}

bool union_generic_union_generic_StringMyOption1BoolFun1_isNone(struct StringMyOption1_ opt_) {
    bool switch_;
    switch (opt_.discriminant) {
        case StringMyOption1_MyNone:
            goto clause_2;

        case StringMyOption1_MySome:
            goto clause_3;

        default:
            milone_exhaust_error("union_generic/union_generic.milone", 7, 2);
    }
clause_2:;
    switch_ = true;
    goto switch_next_1;
clause_3:;
    switch_ = false;
    goto switch_next_1;
switch_next_1:;
    return switch_;
}

int32_t union_generic_union_generic_Int32MyOption1Int32Fun1_unwrap(struct Int32MyOption1_ opt_1) {
    int32_t it_;
    int32_t match_1;
    if ((opt_1.discriminant != Int32MyOption1_MySome)) goto next_2;
    it_ = opt_1.Int32MyOption1_MySome;
    match_1 = it_;
    goto end_match_1;
next_2:;
    if ((opt_1.discriminant != Int32MyOption1_MyNone)) goto next_3;
    if (true) milone_assert_error("union_generic/union_generic.milone", 16, 4);
    MiloneCore_Prelude_exit(1);
    milone_never_error("union_generic/union_generic.milone", 17, 8);
next_3:;
    milone_exhaust_error("union_generic/union_generic.milone", 12, 2);
end_match_1:;
    return match_1;
}

bool union_generic_union_generic_Int32MyOption1BoolFun1_isNone(struct Int32MyOption1_ opt_) {
    bool switch_1;
    switch (opt_.discriminant) {
        case Int32MyOption1_MyNone:
            goto clause_2;

        case Int32MyOption1_MySome:
            goto clause_3;

        default:
            milone_exhaust_error("union_generic/union_generic.milone", 7, 2);
    }
clause_2:;
    switch_1 = true;
    goto switch_next_1;
clause_3:;
    switch_1 = false;
    goto switch_next_1;
switch_next_1:;
    return switch_1;
}

bool union_generic_union_generic_UnitMyOption1BoolFun1_isNone(struct UnitMyOption1_ opt_) {
    bool switch_2;
    switch (opt_.discriminant) {
        case UnitMyOption1_MyNone:
            goto clause_2;

        case UnitMyOption1_MySome:
            goto clause_3;

        default:
            milone_exhaust_error("union_generic/union_generic.milone", 7, 2);
    }
clause_2:;
    switch_2 = true;
    goto switch_next_1;
clause_3:;
    switch_2 = false;
    goto switch_next_1;
switch_next_1:;
    return switch_2;
}

void union_generic_union_generic_testBasicUsage(void) {
    struct UnitMyOption1_ none_;
    struct Int32MyOption1_ some_;
    bool call_;
    struct Int32MyOption1_ variant_;
    bool call_1;
    int32_t call_2;
    none_ = (struct UnitMyOption1_){.discriminant = UnitMyOption1_MyNone};
    call_ = union_generic_union_generic_UnitMyOption1BoolFun1_isNone(none_);
    if ((!(call_))) milone_assert_error("union_generic/union_generic.milone", 23, 2);
    variant_ = (struct Int32MyOption1_){.discriminant = Int32MyOption1_MySome, .Int32MyOption1_MySome = 42};
    some_ = variant_;
    call_1 = union_generic_union_generic_Int32MyOption1BoolFun1_isNone(some_);
    if (call_1) milone_assert_error("union_generic/union_generic.milone", 28, 2);
    call_2 = union_generic_union_generic_Int32MyOption1Int32Fun1_unwrap(some_);
    if ((call_2 != 42)) milone_assert_error("union_generic/union_generic.milone", 29, 2);
    return;
}

void union_generic_union_generic_testAnotherInstance(void) {
    struct StringMyOption1_ stringNone_;
    struct StringMyOption1_ stringSome_;
    bool call_3;
    struct StringMyOption1_ variant_1;
    bool call_4;
    struct String call_5;
    stringNone_ = (struct StringMyOption1_){.discriminant = StringMyOption1_MyNone};
    call_3 = union_generic_union_generic_StringMyOption1BoolFun1_isNone(stringNone_);
    if ((!(call_3))) milone_assert_error("union_generic/union_generic.milone", 34, 2);
    variant_1 = (struct StringMyOption1_){.discriminant = StringMyOption1_MySome, .StringMyOption1_MySome = (struct String){.ptr = "hey", .len = 3}};
    stringSome_ = variant_1;
    call_4 = union_generic_union_generic_StringMyOption1BoolFun1_isNone(stringSome_);
    if (call_4) milone_assert_error("union_generic/union_generic.milone", 38, 2);
    call_5 = union_generic_union_generic_StringMyOption1StringFun1_unwrap(stringSome_);
    if ((string_compare(call_5, (struct String){.ptr = "hey", .len = 3}) != 0)) milone_assert_error("union_generic/union_generic.milone", 39, 2);
    return;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    union_generic_union_generic_testBasicUsage();
    union_generic_union_generic_testAnotherInstance();
    return 0;
}
