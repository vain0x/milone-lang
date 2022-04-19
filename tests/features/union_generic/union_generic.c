#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct StringMyOption1_;

struct IntMyOption1_;

struct UnitMyOption1_;

struct String union_generic_union_generic_StringMyOption1StringFun1_unwrap(struct StringMyOption1_ opt_1);

bool union_generic_union_generic_StringMyOption1BoolFun1_isNone(struct StringMyOption1_ opt_);

int union_generic_union_generic_IntMyOption1IntFun1_unwrap(struct IntMyOption1_ opt_1);

bool union_generic_union_generic_IntMyOption1BoolFun1_isNone(struct IntMyOption1_ opt_);

bool union_generic_union_generic_UnitMyOption1BoolFun1_isNone(struct UnitMyOption1_ opt_);

void union_generic_union_generic_testBasicUsage(void);

void union_generic_union_generic_testAnotherInstance(void);

int main(int argc, char** argv);

enum StringMyOption1_Discriminant {
    MyNone_,
    MySome_,
};

struct StringMyOption1_ {
    enum StringMyOption1_Discriminant discriminant;
    union {
        struct String MySome_;
    };
};

enum IntMyOption1_Discriminant {
    MyNone_1,
    MySome_1,
};

struct IntMyOption1_ {
    enum IntMyOption1_Discriminant discriminant;
    union {
        int MySome_1;
    };
};

enum UnitMyOption1_Discriminant {
    MyNone_2,
    MySome_2,
};

struct UnitMyOption1_ {
    enum UnitMyOption1_Discriminant discriminant;
    union {
        char MySome_2;
    };
};

struct String union_generic_union_generic_StringMyOption1StringFun1_unwrap(struct StringMyOption1_ opt_1) {
    struct String it_;
    struct String match_;
    if ((opt_1.discriminant != MySome_)) goto next_2;
    it_ = opt_1.MySome_;
    match_ = it_;
    goto end_match_1;
next_2:;
    if ((opt_1.discriminant != MyNone_)) goto next_3;
    milone_assert(false, (struct String){.ptr = "union_generic/union_generic.milone", .len = 34}, 16, 4);
    exit(1);
next_3:;
    exit(1);
end_match_1:;
    return match_;
}

bool union_generic_union_generic_StringMyOption1BoolFun1_isNone(struct StringMyOption1_ opt_) {
    bool switch_;
    switch (opt_.discriminant) {
        case MyNone_:
            goto clause_5;

        case MySome_:
            goto clause_6;

        default:
            exit(1);
    }
clause_5:;
    switch_ = true;
    goto switch_next_4;
clause_6:;
    switch_ = false;
    goto switch_next_4;
switch_next_4:;
    return switch_;
}

int union_generic_union_generic_IntMyOption1IntFun1_unwrap(struct IntMyOption1_ opt_1) {
    int it_;
    int match_1;
    if ((opt_1.discriminant != MySome_1)) goto next_8;
    it_ = opt_1.MySome_1;
    match_1 = it_;
    goto end_match_7;
next_8:;
    if ((opt_1.discriminant != MyNone_1)) goto next_9;
    milone_assert(false, (struct String){.ptr = "union_generic/union_generic.milone", .len = 34}, 16, 4);
    exit(1);
next_9:;
    exit(1);
end_match_7:;
    return match_1;
}

bool union_generic_union_generic_IntMyOption1BoolFun1_isNone(struct IntMyOption1_ opt_) {
    bool switch_1;
    switch (opt_.discriminant) {
        case MyNone_1:
            goto clause_11;

        case MySome_1:
            goto clause_12;

        default:
            exit(1);
    }
clause_11:;
    switch_1 = true;
    goto switch_next_10;
clause_12:;
    switch_1 = false;
    goto switch_next_10;
switch_next_10:;
    return switch_1;
}

bool union_generic_union_generic_UnitMyOption1BoolFun1_isNone(struct UnitMyOption1_ opt_) {
    bool switch_2;
    switch (opt_.discriminant) {
        case MyNone_2:
            goto clause_14;

        case MySome_2:
            goto clause_15;

        default:
            exit(1);
    }
clause_14:;
    switch_2 = true;
    goto switch_next_13;
clause_15:;
    switch_2 = false;
    goto switch_next_13;
switch_next_13:;
    return switch_2;
}

void union_generic_union_generic_testBasicUsage(void) {
    struct UnitMyOption1_ none_;
    struct IntMyOption1_ some_;
    bool call_;
    struct IntMyOption1_ variant_;
    bool call_1;
    int call_2;
    none_ = (struct UnitMyOption1_){.discriminant = MyNone_2};
    call_ = union_generic_union_generic_UnitMyOption1BoolFun1_isNone(none_);
    milone_assert(call_, (struct String){.ptr = "union_generic/union_generic.milone", .len = 34}, 23, 2);
    variant_ = (struct IntMyOption1_){.discriminant = MySome_1, .MySome_1 = 42};
    some_ = variant_;
    call_1 = union_generic_union_generic_IntMyOption1BoolFun1_isNone(some_);
    milone_assert((!(call_1)), (struct String){.ptr = "union_generic/union_generic.milone", .len = 34}, 28, 2);
    call_2 = union_generic_union_generic_IntMyOption1IntFun1_unwrap(some_);
    milone_assert((call_2 == 42), (struct String){.ptr = "union_generic/union_generic.milone", .len = 34}, 29, 2);
    return;
}

void union_generic_union_generic_testAnotherInstance(void) {
    struct StringMyOption1_ stringNone_;
    struct StringMyOption1_ stringSome_;
    bool call_3;
    struct StringMyOption1_ variant_1;
    bool call_4;
    struct String call_5;
    stringNone_ = (struct StringMyOption1_){.discriminant = MyNone_};
    call_3 = union_generic_union_generic_StringMyOption1BoolFun1_isNone(stringNone_);
    milone_assert(call_3, (struct String){.ptr = "union_generic/union_generic.milone", .len = 34}, 34, 2);
    variant_1 = (struct StringMyOption1_){.discriminant = MySome_, .MySome_ = (struct String){.ptr = "hey", .len = 3}};
    stringSome_ = variant_1;
    call_4 = union_generic_union_generic_StringMyOption1BoolFun1_isNone(stringSome_);
    milone_assert((!(call_4)), (struct String){.ptr = "union_generic/union_generic.milone", .len = 34}, 38, 2);
    call_5 = union_generic_union_generic_StringMyOption1StringFun1_unwrap(stringSome_);
    milone_assert((string_compare(call_5, (struct String){.ptr = "hey", .len = 3}) == 0), (struct String){.ptr = "union_generic/union_generic.milone", .len = 34}, 39, 2);
    return;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    union_generic_union_generic_testBasicUsage();
    union_generic_union_generic_testAnotherInstance();
    return 0;
}
