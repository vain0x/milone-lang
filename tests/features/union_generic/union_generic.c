#include "milone.h"

struct MyOption_;

bool isNone_2(struct MyOption_ opt_);

bool isNone_1(struct MyOption_ opt_);

bool isNone_(struct MyOption_ opt_);

int unwrap_1(struct MyOption_ opt_1);

struct String unwrap_(struct MyOption_ opt_1);

void testBasicUsage_(void);

void testAnotherInstance_(void);

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

bool isNone_2(struct MyOption_ opt_) {
    bool switch_;
    switch (opt_.discriminant) {
        case MyNone_:
            goto clause_2;

        case MySome_:
            goto clause_3;

        default:
            exit(1);
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

bool isNone_1(struct MyOption_ opt_) {
    bool switch_1;
    switch (opt_.discriminant) {
        case MyNone_:
            goto clause_5;

        case MySome_:
            goto clause_6;

        default:
            exit(1);
    }
clause_5:;
    switch_1 = true;
    goto switch_next_4;
clause_6:;
    switch_1 = false;
    goto switch_next_4;
switch_next_4:;
    return switch_1;
}

bool isNone_(struct MyOption_ opt_) {
    bool switch_2;
    switch (opt_.discriminant) {
        case MyNone_:
            goto clause_8;

        case MySome_:
            goto clause_9;

        default:
            exit(1);
    }
clause_8:;
    switch_2 = true;
    goto switch_next_7;
clause_9:;
    switch_2 = false;
    goto switch_next_7;
switch_next_7:;
    return switch_2;
}

int unwrap_1(struct MyOption_ opt_1) {
    int it_;
    int match_;
    if ((opt_1.discriminant != MySome_)) goto next_11;
    it_ = ((int)((intptr_t)opt_1.MySome_));
    match_ = it_;
    goto end_match_10;
next_11:;
    if ((opt_1.discriminant != MyNone_)) goto next_12;
    milone_assert(false, 16, 4);
    exit(1);
next_12:;
    exit(1);
end_match_10:;
    return match_;
}

struct String unwrap_(struct MyOption_ opt_1) {
    struct String it_;
    struct String match_1;
    if ((opt_1.discriminant != MySome_)) goto next_14;
    it_ = (*(((struct String const*)opt_1.MySome_)));
    match_1 = it_;
    goto end_match_13;
next_14:;
    if ((opt_1.discriminant != MyNone_)) goto next_15;
    milone_assert(false, 16, 4);
    exit(1);
next_15:;
    exit(1);
end_match_13:;
    return match_1;
}

void testBasicUsage_(void) {
    struct MyOption_ none_ = (struct MyOption_){.discriminant = MyNone_};
    bool call_ = isNone_2(none_);
    milone_assert(call_, 23, 2);
    struct MyOption_ variant_ = (struct MyOption_){.discriminant = MySome_, .MySome_ = ((void const*)((intptr_t)42))};
    struct MyOption_ some_ = variant_;
    bool call_1 = isNone_1(some_);
    milone_assert((!(call_1)), 28, 2);
    int call_2 = unwrap_1(some_);
    milone_assert((call_2 == 42), 29, 2);
    return;
}

void testAnotherInstance_(void) {
    struct MyOption_ stringNone_ = (struct MyOption_){.discriminant = MyNone_};
    bool call_3 = isNone_(stringNone_);
    milone_assert(call_3, 34, 2);
    void const* box_ = milone_mem_alloc(1, sizeof(struct String));
    (*(((struct String*)box_))) = (struct String){.str = "hey", .len = 3};
    struct MyOption_ variant_1 = (struct MyOption_){.discriminant = MySome_, .MySome_ = box_};
    struct MyOption_ stringSome_ = variant_1;
    bool call_4 = isNone_(stringSome_);
    milone_assert((!(call_4)), 38, 2);
    struct String call_5 = unwrap_(stringSome_);
    milone_assert((str_compare(call_5, (struct String){.str = "hey", .len = 3}) == 0), 39, 2);
    return;
}

int milone_main(void) {
    testBasicUsage_();
    testAnotherInstance_();
    return 0;
}
