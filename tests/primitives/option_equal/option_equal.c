#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32StringTuple2_;

struct Int32option1_;

struct Int32option1Int32option1Tuple2_;

struct Int32StringTuple2option1_;

struct Int32StringTuple2option1Int32StringTuple2option1Tuple2_;

bool MiloneDerive_TupleEqual_tuple2Equal(struct Int32StringTuple2_ l_4, struct Int32StringTuple2_ r_4);

bool MiloneCore_Option_optionEqual(struct Int32option1_ l_, struct Int32option1_ r_);

bool MiloneDerive_TupleEqual_tuple2Equal(struct Int32StringTuple2_, struct Int32StringTuple2_);

bool MiloneCore_Option_optionEqual_1(struct Int32StringTuple2option1_ l_2, struct Int32StringTuple2option1_ r_2);

bool MiloneCore_Option_optionEqual(struct Int32option1_, struct Int32option1_);

void option_equal_option_equal_testIntOption(void);

bool MiloneCore_Option_optionEqual_1(struct Int32StringTuple2option1_, struct Int32StringTuple2option1_);

void option_equal_option_equal_testPair(void);

int main(int argc, char **argv);

struct Int32StringTuple2_ {
    int32_t t0;
    struct String t1;
};

enum Int32option1_Discriminant {
    None_,
    Some_,
};

struct Int32option1_ {
    enum Int32option1_Discriminant discriminant;
    union {
        int32_t Some_;
    };
};

struct Int32option1Int32option1Tuple2_ {
    struct Int32option1_ t0;
    struct Int32option1_ t1;
};

enum Int32StringTuple2option1_Discriminant {
    None_1,
    Some_1,
};

struct Int32StringTuple2option1_ {
    enum Int32StringTuple2option1_Discriminant discriminant;
    union {
        struct Int32StringTuple2_ Some_1;
    };
};

struct Int32StringTuple2option1Int32StringTuple2option1Tuple2_ {
    struct Int32StringTuple2option1_ t0;
    struct Int32StringTuple2option1_ t1;
};

bool MiloneDerive_TupleEqual_tuple2Equal(struct Int32StringTuple2_ l_4, struct Int32StringTuple2_ r_4) {
    int32_t l_5;
    int32_t r_5;
    struct String l_6;
    struct String r_6;
    l_5 = l_4.t0;
    l_6 = l_4.t1;
    r_5 = r_4.t0;
    r_6 = r_4.t1;
    return ((l_5 == r_5) & (string_compare(l_6, r_6) == 0));
}

bool MiloneCore_Option_optionEqual(struct Int32option1_ l_, struct Int32option1_ r_) {
    int32_t l_1;
    int32_t r_1;
    bool match_;
    struct Int32option1Int32option1Tuple2_ Int32option1Int32option1Tuple2_;
    Int32option1Int32option1Tuple2_ = (struct Int32option1Int32option1Tuple2_){.t0 = l_, .t1 = r_};
    if ((Int32option1Int32option1Tuple2_.t0.discriminant != None_)) goto next_2;
    if ((Int32option1Int32option1Tuple2_.t1.discriminant != None_)) goto next_2;
    match_ = true;
    goto end_match_1;
next_2:;
    if ((Int32option1Int32option1Tuple2_.t0.discriminant != Some_)) goto next_3;
    l_1 = Int32option1Int32option1Tuple2_.t0.Some_;
    if ((Int32option1Int32option1Tuple2_.t1.discriminant != Some_)) goto next_3;
    r_1 = Int32option1Int32option1Tuple2_.t1.Some_;
    match_ = (l_1 == r_1);
    goto end_match_1;
next_3:;
    match_ = false;
    goto end_match_1;
next_4:;
end_match_1:;
    return match_;
}

bool MiloneCore_Option_optionEqual_1(struct Int32StringTuple2option1_ l_2, struct Int32StringTuple2option1_ r_2) {
    struct Int32StringTuple2_ l_3;
    struct Int32StringTuple2_ r_3;
    bool match_1;
    struct Int32StringTuple2option1Int32StringTuple2option1Tuple2_ Int32StringTuple2option1Int32StringTuple2option1Tuple2_;
    bool call_;
    Int32StringTuple2option1Int32StringTuple2option1Tuple2_ = (struct Int32StringTuple2option1Int32StringTuple2option1Tuple2_){.t0 = l_2, .t1 = r_2};
    if ((Int32StringTuple2option1Int32StringTuple2option1Tuple2_.t0.discriminant != None_1)) goto next_6;
    if ((Int32StringTuple2option1Int32StringTuple2option1Tuple2_.t1.discriminant != None_1)) goto next_6;
    match_1 = true;
    goto end_match_5;
next_6:;
    if ((Int32StringTuple2option1Int32StringTuple2option1Tuple2_.t0.discriminant != Some_1)) goto next_7;
    l_3 = Int32StringTuple2option1Int32StringTuple2option1Tuple2_.t0.Some_1;
    if ((Int32StringTuple2option1Int32StringTuple2option1Tuple2_.t1.discriminant != Some_1)) goto next_7;
    r_3 = Int32StringTuple2option1Int32StringTuple2option1Tuple2_.t1.Some_1;
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
    struct Int32option1_ some_;
    struct Int32option1_ none_;
    struct Int32option1_ variant_;
    struct Int32option1_ variant_1;
    bool call_1;
    struct Int32option1_ variant_2;
    bool call_2;
    bool call_3;
    bool call_4;
    bool call_5;
    variant_ = (struct Int32option1_){.discriminant = Some_, .Some_ = 2};
    some_ = variant_;
    variant_1 = (struct Int32option1_){.discriminant = Some_, .Some_ = 2};
    call_1 = MiloneCore_Option_optionEqual(some_, variant_1);
    if ((!(call_1))) milone_assert_error("option_equal/option_equal.milone", 6, 2);
    variant_2 = (struct Int32option1_){.discriminant = Some_, .Some_ = 3};
    call_2 = MiloneCore_Option_optionEqual(some_, variant_2);
    if (call_2) milone_assert_error("option_equal/option_equal.milone", 7, 2);
    call_3 = MiloneCore_Option_optionEqual(some_, (struct Int32option1_){.discriminant = None_});
    if (call_3) milone_assert_error("option_equal/option_equal.milone", 8, 2);
    none_ = (struct Int32option1_){.discriminant = None_};
    call_4 = MiloneCore_Option_optionEqual(none_, (struct Int32option1_){.discriminant = None_});
    if ((!(call_4))) milone_assert_error("option_equal/option_equal.milone", 11, 2);
    call_5 = MiloneCore_Option_optionEqual(none_, some_);
    if (call_5) milone_assert_error("option_equal/option_equal.milone", 12, 2);
    return;
}

void option_equal_option_equal_testPair(void) {
    struct Int32StringTuple2_ Int32StringTuple2_;
    struct Int32StringTuple2option1_ variant_3;
    struct Int32StringTuple2_ Int32StringTuple2_1;
    struct Int32StringTuple2option1_ variant_4;
    bool call_6;
    struct Int32StringTuple2_ Int32StringTuple2_2;
    struct Int32StringTuple2option1_ variant_5;
    struct Int32StringTuple2_ Int32StringTuple2_3;
    struct Int32StringTuple2option1_ variant_6;
    bool call_7;
    Int32StringTuple2_ = (struct Int32StringTuple2_){.t0 = 2, .t1 = (struct String){.ptr = "a", .len = 1}};
    variant_3 = (struct Int32StringTuple2option1_){.discriminant = Some_1, .Some_1 = Int32StringTuple2_};
    Int32StringTuple2_1 = (struct Int32StringTuple2_){.t0 = 2, .t1 = (struct String){.ptr = "a", .len = 1}};
    variant_4 = (struct Int32StringTuple2option1_){.discriminant = Some_1, .Some_1 = Int32StringTuple2_1};
    call_6 = MiloneCore_Option_optionEqual_1(variant_3, variant_4);
    if ((!(call_6))) milone_assert_error("option_equal/option_equal.milone", 15, 2);
    Int32StringTuple2_2 = (struct Int32StringTuple2_){.t0 = 2, .t1 = (struct String){.ptr = "a", .len = 1}};
    variant_5 = (struct Int32StringTuple2option1_){.discriminant = Some_1, .Some_1 = Int32StringTuple2_2};
    Int32StringTuple2_3 = (struct Int32StringTuple2_){.t0 = 2, .t1 = (struct String){.ptr = "A", .len = 1}};
    variant_6 = (struct Int32StringTuple2option1_){.discriminant = Some_1, .Some_1 = Int32StringTuple2_3};
    call_7 = MiloneCore_Option_optionEqual_1(variant_5, variant_6);
    if (call_7) milone_assert_error("option_equal/option_equal.milone", 16, 2);
    return;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    option_equal_option_equal_testIntOption();
    option_equal_option_equal_testPair();
    return 0;
}
