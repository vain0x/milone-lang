#include <milone.h>

struct IntStringTuple2_;

struct Intoption1_;

struct Intoption1Intoption1Tuple2_;

struct IntStringTuple2option1_;

struct IntStringTuple2option1IntStringTuple2option1Tuple2_;

bool MiloneDerive_TupleEqual_tuple2Equal(struct IntStringTuple2_ l_4, struct IntStringTuple2_ r_4);

bool MiloneCore_Option_optionEqual(struct Intoption1_ l_, struct Intoption1_ r_);

bool MiloneDerive_TupleEqual_tuple2Equal(struct IntStringTuple2_ , struct IntStringTuple2_ );

bool MiloneCore_Option_optionEqual_1(struct IntStringTuple2option1_ l_2, struct IntStringTuple2option1_ r_2);

bool MiloneCore_Option_optionEqual(struct Intoption1_ , struct Intoption1_ );

void option_equal_option_equal_testIntOption(void);

bool MiloneCore_Option_optionEqual_1(struct IntStringTuple2option1_ , struct IntStringTuple2option1_ );

void option_equal_option_equal_testPair(void);

int main(int argc, char** argv);

struct IntStringTuple2_ {
    int t0;
    struct String t1;
};

enum Intoption1_Discriminant {
    None_,
    Some_,
};

struct Intoption1_ {
    enum Intoption1_Discriminant discriminant;
    union {
        int Some_;
    };
};

struct Intoption1Intoption1Tuple2_ {
    struct Intoption1_ t0;
    struct Intoption1_ t1;
};

enum IntStringTuple2option1_Discriminant {
    None_1,
    Some_1,
};

struct IntStringTuple2option1_ {
    enum IntStringTuple2option1_Discriminant discriminant;
    union {
        struct IntStringTuple2_ Some_1;
    };
};

struct IntStringTuple2option1IntStringTuple2option1Tuple2_ {
    struct IntStringTuple2option1_ t0;
    struct IntStringTuple2option1_ t1;
};

bool MiloneDerive_TupleEqual_tuple2Equal(struct IntStringTuple2_ l_4, struct IntStringTuple2_ r_4) {
    int l_5;
    int r_5;
    struct String l_6;
    struct String r_6;
    l_5 = l_4.t0;
    l_6 = l_4.t1;
    r_5 = r_4.t0;
    r_6 = r_4.t1;
    return ((l_5 == r_5) & (str_compare(l_6, r_6) == 0));
}

bool MiloneCore_Option_optionEqual(struct Intoption1_ l_, struct Intoption1_ r_) {
    int l_1;
    int r_1;
    bool match_;
    struct Intoption1Intoption1Tuple2_ Intoption1Intoption1Tuple2_;
    Intoption1Intoption1Tuple2_ = (struct Intoption1Intoption1Tuple2_){.t0 = l_, .t1 = r_};
    if ((Intoption1Intoption1Tuple2_.t0.discriminant != None_)) goto next_2;
    if ((Intoption1Intoption1Tuple2_.t1.discriminant != None_)) goto next_2;
    match_ = true;
    goto end_match_1;
next_2:;
    if ((Intoption1Intoption1Tuple2_.t0.discriminant != Some_)) goto next_3;
    l_1 = Intoption1Intoption1Tuple2_.t0.Some_;
    if ((Intoption1Intoption1Tuple2_.t1.discriminant != Some_)) goto next_3;
    r_1 = Intoption1Intoption1Tuple2_.t1.Some_;
    match_ = (l_1 == r_1);
    goto end_match_1;
next_3:;
    match_ = false;
    goto end_match_1;
next_4:;
end_match_1:;
    return match_;
}

bool MiloneCore_Option_optionEqual_1(struct IntStringTuple2option1_ l_2, struct IntStringTuple2option1_ r_2) {
    struct IntStringTuple2_ l_3;
    struct IntStringTuple2_ r_3;
    bool match_1;
    struct IntStringTuple2option1IntStringTuple2option1Tuple2_ IntStringTuple2option1IntStringTuple2option1Tuple2_;
    bool call_;
    IntStringTuple2option1IntStringTuple2option1Tuple2_ = (struct IntStringTuple2option1IntStringTuple2option1Tuple2_){.t0 = l_2, .t1 = r_2};
    if ((IntStringTuple2option1IntStringTuple2option1Tuple2_.t0.discriminant != None_1)) goto next_6;
    if ((IntStringTuple2option1IntStringTuple2option1Tuple2_.t1.discriminant != None_1)) goto next_6;
    match_1 = true;
    goto end_match_5;
next_6:;
    if ((IntStringTuple2option1IntStringTuple2option1Tuple2_.t0.discriminant != Some_1)) goto next_7;
    l_3 = IntStringTuple2option1IntStringTuple2option1Tuple2_.t0.Some_1;
    if ((IntStringTuple2option1IntStringTuple2option1Tuple2_.t1.discriminant != Some_1)) goto next_7;
    r_3 = IntStringTuple2option1IntStringTuple2option1Tuple2_.t1.Some_1;
    call_ = MiloneDerive_TupleEqual_tuple2Equal(l_3, r_3);
    match_1 = call_;
    goto end_match_5;
next_7:;
    match_1 = false;
    goto end_match_5;
next_8:;
end_match_5:;
    return match_1;
}

void option_equal_option_equal_testIntOption(void) {
    struct Intoption1_ some_;
    struct Intoption1_ none_;
    struct Intoption1_ variant_;
    struct Intoption1_ variant_1;
    bool call_1;
    struct Intoption1_ variant_2;
    bool call_2;
    bool call_3;
    bool call_4;
    bool call_5;
    variant_ = (struct Intoption1_){.discriminant = Some_, .Some_ = 2};
    some_ = variant_;
    variant_1 = (struct Intoption1_){.discriminant = Some_, .Some_ = 2};
    call_1 = MiloneCore_Option_optionEqual(some_, variant_1);
    milone_assert(call_1, (struct String){.str = "option_equal/option_equal.milone", .len = 32}, 6, 2);
    variant_2 = (struct Intoption1_){.discriminant = Some_, .Some_ = 3};
    call_2 = MiloneCore_Option_optionEqual(some_, variant_2);
    milone_assert((!(call_2)), (struct String){.str = "option_equal/option_equal.milone", .len = 32}, 7, 2);
    call_3 = MiloneCore_Option_optionEqual(some_, (struct Intoption1_){.discriminant = None_});
    milone_assert((!(call_3)), (struct String){.str = "option_equal/option_equal.milone", .len = 32}, 8, 2);
    none_ = (struct Intoption1_){.discriminant = None_};
    call_4 = MiloneCore_Option_optionEqual(none_, (struct Intoption1_){.discriminant = None_});
    milone_assert(call_4, (struct String){.str = "option_equal/option_equal.milone", .len = 32}, 11, 2);
    call_5 = MiloneCore_Option_optionEqual(none_, some_);
    milone_assert((!(call_5)), (struct String){.str = "option_equal/option_equal.milone", .len = 32}, 12, 2);
    return;
}

void option_equal_option_equal_testPair(void) {
    struct IntStringTuple2_ IntStringTuple2_;
    struct IntStringTuple2option1_ variant_3;
    struct IntStringTuple2_ IntStringTuple2_1;
    struct IntStringTuple2option1_ variant_4;
    bool call_6;
    struct IntStringTuple2_ IntStringTuple2_2;
    struct IntStringTuple2option1_ variant_5;
    struct IntStringTuple2_ IntStringTuple2_3;
    struct IntStringTuple2option1_ variant_6;
    bool call_7;
    IntStringTuple2_ = (struct IntStringTuple2_){.t0 = 2, .t1 = (struct String){.str = "a", .len = 1}};
    variant_3 = (struct IntStringTuple2option1_){.discriminant = Some_1, .Some_1 = IntStringTuple2_};
    IntStringTuple2_1 = (struct IntStringTuple2_){.t0 = 2, .t1 = (struct String){.str = "a", .len = 1}};
    variant_4 = (struct IntStringTuple2option1_){.discriminant = Some_1, .Some_1 = IntStringTuple2_1};
    call_6 = MiloneCore_Option_optionEqual_1(variant_3, variant_4);
    milone_assert(call_6, (struct String){.str = "option_equal/option_equal.milone", .len = 32}, 15, 2);
    IntStringTuple2_2 = (struct IntStringTuple2_){.t0 = 2, .t1 = (struct String){.str = "a", .len = 1}};
    variant_5 = (struct IntStringTuple2option1_){.discriminant = Some_1, .Some_1 = IntStringTuple2_2};
    IntStringTuple2_3 = (struct IntStringTuple2_){.t0 = 2, .t1 = (struct String){.str = "A", .len = 1}};
    variant_6 = (struct IntStringTuple2option1_){.discriminant = Some_1, .Some_1 = IntStringTuple2_3};
    call_7 = MiloneCore_Option_optionEqual_1(variant_5, variant_6);
    milone_assert((!(call_7)), (struct String){.str = "option_equal/option_equal.milone", .len = 32}, 16, 2);
    return;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    option_equal_option_equal_testIntOption();
    option_equal_option_equal_testPair();
    return 0;
}
