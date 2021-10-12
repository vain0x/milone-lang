#include "milone.h"

struct IntOption_;

struct IntOptionIntOptionTuple2_;

struct IntStringTuple2_;

struct IntStringTuple2Option_;

struct IntStringTuple2OptionIntStringTuple2OptionTuple2_;

bool optionEqual_(struct IntOption_ l_, struct IntOption_ r_);

bool tuple2Equal_(struct IntStringTuple2_ , struct IntStringTuple2_ );

bool optionEqual_1(struct IntStringTuple2Option_ l_2, struct IntStringTuple2Option_ r_2);

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

struct IntStringTuple2OptionIntStringTuple2OptionTuple2_ {
    struct IntStringTuple2Option_ t0;
    struct IntStringTuple2Option_ t1;
};

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
