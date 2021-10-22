#include "milone.h"

struct MyOption_;

struct String union_generic_union_generic_StringMyOption1StringFun1_unwrap(struct MyOption_ opt_1);

bool union_generic_union_generic_StringMyOption1BoolFun1_isNone(struct MyOption_ opt_);

int union_generic_union_generic_IntMyOption1IntFun1_unwrap(struct MyOption_ opt_1);

bool union_generic_union_generic_IntMyOption1BoolFun1_isNone(struct MyOption_ opt_);

bool union_generic_union_generic_UnitMyOption1BoolFun1_isNone(struct MyOption_ opt_);

void union_generic_union_generic_testBasicUsage(void);

void union_generic_union_generic_testAnotherInstance(void);

int milone_main(void);

enum MyOption_Discriminant {
    MyNone_,
    MySome_,
};

struct MyOption_ {
    enum MyOption_Discriminant discriminant;
    union {
        void const* MySome_;
    };
};

struct String union_generic_union_generic_StringMyOption1StringFun1_unwrap(struct MyOption_ opt_1) {
    struct String it_;
    struct String match_;
    if ((opt_1.discriminant != MySome_)) goto next_2;
    it_ = (*(((struct String const*)opt_1.MySome_)));
    match_ = it_;
    goto end_match_1;
next_2:;
    if ((opt_1.discriminant != MyNone_)) goto next_3;
    milone_assert(false, 16, 4);
    exit(1);
next_3:;
    exit(1);
end_match_1:;
    return match_;
}

bool union_generic_union_generic_StringMyOption1BoolFun1_isNone(struct MyOption_ opt_) {
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

int union_generic_union_generic_IntMyOption1IntFun1_unwrap(struct MyOption_ opt_1) {
    int it_;
    int match_1;
    if ((opt_1.discriminant != MySome_)) goto next_8;
    it_ = ((int)((intptr_t)opt_1.MySome_));
    match_1 = it_;
    goto end_match_7;
next_8:;
    if ((opt_1.discriminant != MyNone_)) goto next_9;
    milone_assert(false, 16, 4);
    exit(1);
next_9:;
    exit(1);
end_match_7:;
    return match_1;
}

bool union_generic_union_generic_IntMyOption1BoolFun1_isNone(struct MyOption_ opt_) {
    bool switch_1;
    switch (opt_.discriminant) {
        case MyNone_:
            goto clause_11;

        case MySome_:
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

bool union_generic_union_generic_UnitMyOption1BoolFun1_isNone(struct MyOption_ opt_) {
    bool switch_2;
    switch (opt_.discriminant) {
        case MyNone_:
            goto clause_14;

        case MySome_:
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
    struct MyOption_ none_ = (struct MyOption_){.discriminant = MyNone_};
    bool call_ = union_generic_union_generic_UnitMyOption1BoolFun1_isNone(none_);
    milone_assert(call_, 23, 2);
    struct MyOption_ variant_ = (struct MyOption_){.discriminant = MySome_, .MySome_ = ((void const*)((intptr_t)42))};
    struct MyOption_ some_ = variant_;
    bool call_1 = union_generic_union_generic_IntMyOption1BoolFun1_isNone(some_);
    milone_assert((!(call_1)), 28, 2);
    int call_2 = union_generic_union_generic_IntMyOption1IntFun1_unwrap(some_);
    milone_assert((call_2 == 42), 29, 2);
    return;
}

void union_generic_union_generic_testAnotherInstance(void) {
    struct MyOption_ stringNone_ = (struct MyOption_){.discriminant = MyNone_};
    bool call_3 = union_generic_union_generic_StringMyOption1BoolFun1_isNone(stringNone_);
    milone_assert(call_3, 34, 2);
    void const* box_ = milone_mem_alloc(1, sizeof(struct String));
    (*(((struct String*)box_))) = (struct String){.str = "hey", .len = 3};
    struct MyOption_ variant_1 = (struct MyOption_){.discriminant = MySome_, .MySome_ = box_};
    struct MyOption_ stringSome_ = variant_1;
    bool call_4 = union_generic_union_generic_StringMyOption1BoolFun1_isNone(stringSome_);
    milone_assert((!(call_4)), 38, 2);
    struct String call_5 = union_generic_union_generic_StringMyOption1StringFun1_unwrap(stringSome_);
    milone_assert((str_compare(call_5, (struct String){.str = "hey", .len = 3}) == 0), 39, 2);
    return;
}

int milone_main(void) {
    union_generic_union_generic_testBasicUsage();
    union_generic_union_generic_testAnotherInstance();
    return 0;
}
