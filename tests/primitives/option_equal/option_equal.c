#include "milone.h"

struct IntOption_;

struct IntStringTuple2_;

struct IntStringTuple2Option_;

bool optionEqual_(struct IntOption_ , struct IntOption_ );

void testIntOption_(void);

bool optionEqual_1(struct IntStringTuple2Option_ , struct IntStringTuple2Option_ );

void testPair_(void);

int milone_main(void);

enum IntOption_Discriminant {
    None_,
    Some_,
};

struct IntOption_ {
    enum IntOption_Discriminant discriminant;
    union {
        int Some_;
    };
};

struct IntStringTuple2_ {
    int t0;
    struct String t1;
};

enum IntStringTuple2Option_Discriminant {
    None_1,
    Some_1,
};

struct IntStringTuple2Option_ {
    enum IntStringTuple2Option_Discriminant discriminant;
    union {
        struct IntStringTuple2_ Some_1;
    };
};

void testIntOption_(void) {
    struct IntOption_ variant_ = (struct IntOption_){.discriminant = Some_, .Some_ = 2};
    struct IntOption_ some_ = variant_;
    struct IntOption_ variant_1 = (struct IntOption_){.discriminant = Some_, .Some_ = 2};
    bool call_1 = optionEqual_(some_, variant_1);
    milone_assert(call_1, 6, 2);
    struct IntOption_ variant_2 = (struct IntOption_){.discriminant = Some_, .Some_ = 3};
    bool call_2 = optionEqual_(some_, variant_2);
    milone_assert((!(call_2)), 7, 2);
    bool call_3 = optionEqual_(some_, (struct IntOption_){.discriminant = None_});
    milone_assert((!(call_3)), 8, 2);
    struct IntOption_ none_ = (struct IntOption_){.discriminant = None_};
    bool call_4 = optionEqual_(none_, (struct IntOption_){.discriminant = None_});
    milone_assert(call_4, 11, 2);
    bool call_5 = optionEqual_(none_, some_);
    milone_assert((!(call_5)), 12, 2);
    return;
}

void testPair_(void) {
    struct IntStringTuple2_ IntStringTuple2_ = (struct IntStringTuple2_){.t0 = 2, .t1 = (struct String){.str = "a", .len = 1}};
    struct IntStringTuple2Option_ variant_3 = (struct IntStringTuple2Option_){.discriminant = Some_1, .Some_1 = IntStringTuple2_};
    struct IntStringTuple2_ IntStringTuple2_1 = (struct IntStringTuple2_){.t0 = 2, .t1 = (struct String){.str = "a", .len = 1}};
    struct IntStringTuple2Option_ variant_4 = (struct IntStringTuple2Option_){.discriminant = Some_1, .Some_1 = IntStringTuple2_1};
    bool call_6 = optionEqual_1(variant_3, variant_4);
    milone_assert(call_6, 15, 2);
    struct IntStringTuple2_ IntStringTuple2_2 = (struct IntStringTuple2_){.t0 = 2, .t1 = (struct String){.str = "a", .len = 1}};
    struct IntStringTuple2Option_ variant_5 = (struct IntStringTuple2Option_){.discriminant = Some_1, .Some_1 = IntStringTuple2_2};
    struct IntStringTuple2_ IntStringTuple2_3 = (struct IntStringTuple2_){.t0 = 2, .t1 = (struct String){.str = "A", .len = 1}};
    struct IntStringTuple2Option_ variant_6 = (struct IntStringTuple2Option_){.discriminant = Some_1, .Some_1 = IntStringTuple2_3};
    bool call_7 = optionEqual_1(variant_5, variant_6);
    milone_assert((!(call_7)), 16, 2);
    return;
}

int milone_main(void) {
    testIntOption_();
    testPair_();
    return 0;
}
