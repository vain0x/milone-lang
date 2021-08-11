#include "milone.h"

struct IntOption_;

struct StringOption_;

struct UnitOption_;

char option_Program_basicSomeCase(char arg_);

char option_Program_basicNoneCase(char arg_1);

char option_Program_basicMatchCase(char arg_2);

int milone_main();

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

enum StringOption_Discriminant {
    None_1,
    Some_1,
};

struct StringOption_ {
    enum StringOption_Discriminant discriminant;
    union {
        struct String Some_1;
    };
};

enum UnitOption_Discriminant {
    None_2,
    Some_2,
};

struct UnitOption_ {
    enum UnitOption_Discriminant discriminant;
    union {
        char Some_2;
    };
};

char option_Program_basicSomeCase(char arg_) {
    char match_;
    struct IntOption_ variant_ = (struct IntOption_){.discriminant = Some_, .Some_ = 1};
    if ((variant_.discriminant != None_)) goto next_2;
    milone_assert(false, 6, 12);
    match_ = 0;
    goto end_match_1;
next_2:;
    if ((variant_.discriminant != Some_)) goto next_3;
    if ((variant_.Some_ != 1)) goto next_3;
    match_ = 0;
    goto end_match_1;
next_3:;
    milone_assert(false, 10, 9);
    match_ = 0;
    goto end_match_1;
next_4:;
end_match_1:;
    return 0;
}

char option_Program_basicNoneCase(char arg_1) {
    struct StringOption_ none_ = (struct StringOption_){.discriminant = None_1};
    char match_1;
    if ((none_.discriminant != Some_1)) goto next_6;
    if ((str_compare(none_.Some_1, (struct String){.str = "a", .len = 1}) != 0)) goto next_6;
    milone_assert(false, 17, 16);
    match_1 = 0;
    goto end_match_5;
next_6:;
    if ((none_.discriminant != None_1)) goto next_7;
    match_1 = 0;
    goto end_match_5;
next_7:;
    milone_assert(false, 21, 9);
    match_1 = 0;
    goto end_match_5;
next_8:;
end_match_5:;
    return 0;
}

char option_Program_basicMatchCase(char arg_2) {
    char switch_;
    struct UnitOption_ variant_1 = (struct UnitOption_){.discriminant = Some_2, .Some_2 = 0};
    switch (variant_1.discriminant) {
        case None_2:
            goto clause_10;

        default:
            goto clause_11;
    }
clause_10:;
    milone_assert(false, 27, 12);
    switch_ = 0;
    goto switch_next_9;
clause_11:;
    switch_ = 0;
    goto switch_next_9;
switch_next_9:;
    return 0;
}

int milone_main() {
    char call_ = option_Program_basicSomeCase(0);
    char call_1 = option_Program_basicNoneCase(0);
    char call_2 = option_Program_basicMatchCase(0);
    return 0;
}
