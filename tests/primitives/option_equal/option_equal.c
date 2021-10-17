#include "milone.h"

struct IntStringTuple2_;

struct IntOption_;

struct IntOptionIntOptionTuple2_;

struct IntStringTuple2Option_;

struct IntStringTuple2OptionIntStringTuple2OptionTuple2_;

bool tuple2Equal_(struct IntStringTuple2_ l_4, struct IntStringTuple2_ r_4);

bool optionEqual_(struct IntOption_ l_, struct IntOption_ r_);

bool tuple2Equal_(struct IntStringTuple2_ , struct IntStringTuple2_ );

bool optionEqual_1(struct IntStringTuple2Option_ l_2, struct IntStringTuple2Option_ r_2);

bool optionEqual_(struct IntOption_ , struct IntOption_ );

void testIntOption_(void);

bool optionEqual_1(struct IntStringTuple2Option_ , struct IntStringTuple2Option_ );

void testPair_(void);

int milone_main(void);

struct IntStringTuple2_ {
    int t0;
    struct String t1;
};

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

struct IntOptionIntOptionTuple2_ {
    struct IntOption_ t0;
    struct IntOption_ t1;
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

struct IntStringTuple2OptionIntStringTuple2OptionTuple2_ {
    struct IntStringTuple2Option_ t0;
    struct IntStringTuple2Option_ t1;
};

bool tuple2Equal_(struct IntStringTuple2_ l_4, struct IntStringTuple2_ r_4) {
    int l_5 = l_4.t0;
    struct String l_6 = l_4.t1;
    int r_5 = r_4.t0;
    struct String r_6 = r_4.t1;
    return ((l_5 == r_5) & (str_compare(l_6, r_6) == 0));
}

bool optionEqual_(struct IntOption_ l_, struct IntOption_ r_) {
    int r_1;
    int l_1;
    bool match_;
    struct IntOptionIntOptionTuple2_ IntOptionIntOptionTuple2_ = (struct IntOptionIntOptionTuple2_){.t0 = l_, .t1 = r_};
    if ((IntOptionIntOptionTuple2_.t0.discriminant != None_)) goto next_2;
    if ((IntOptionIntOptionTuple2_.t1.discriminant != None_)) goto next_2;
    match_ = true;
    goto end_match_1;
next_2:;
    if ((IntOptionIntOptionTuple2_.t0.discriminant != Some_)) goto next_3;
    l_1 = IntOptionIntOptionTuple2_.t0.Some_;
    if ((IntOptionIntOptionTuple2_.t1.discriminant != Some_)) goto next_3;
    r_1 = IntOptionIntOptionTuple2_.t1.Some_;
    match_ = (l_1 == r_1);
    goto end_match_1;
next_3:;
    match_ = false;
    goto end_match_1;
next_4:;
end_match_1:;
    return match_;
}

bool optionEqual_1(struct IntStringTuple2Option_ l_2, struct IntStringTuple2Option_ r_2) {
    struct IntStringTuple2_ r_3;
    struct IntStringTuple2_ l_3;
    bool match_1;
    struct IntStringTuple2OptionIntStringTuple2OptionTuple2_ IntStringTuple2OptionIntStringTuple2OptionTuple2_ = (struct IntStringTuple2OptionIntStringTuple2OptionTuple2_){.t0 = l_2, .t1 = r_2};
    if ((IntStringTuple2OptionIntStringTuple2OptionTuple2_.t0.discriminant != None_1)) goto next_6;
    if ((IntStringTuple2OptionIntStringTuple2OptionTuple2_.t1.discriminant != None_1)) goto next_6;
    match_1 = true;
    goto end_match_5;
next_6:;
    if ((IntStringTuple2OptionIntStringTuple2OptionTuple2_.t0.discriminant != Some_1)) goto next_7;
    l_3 = IntStringTuple2OptionIntStringTuple2OptionTuple2_.t0.Some_1;
    if ((IntStringTuple2OptionIntStringTuple2OptionTuple2_.t1.discriminant != Some_1)) goto next_7;
    r_3 = IntStringTuple2OptionIntStringTuple2OptionTuple2_.t1.Some_1;
    bool call_ = tuple2Equal_(l_3, r_3);
    match_1 = call_;
    goto end_match_5;
next_7:;
    match_1 = false;
    goto end_match_5;
next_8:;
end_match_5:;
    return match_1;
}

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
