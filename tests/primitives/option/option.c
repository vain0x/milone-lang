#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Intoption1_;

struct Stringoption1_;

struct Unitoption1_;

void option_option_basicSomeCase(void);

void option_option_basicNoneCase(void);

void option_option_basicMatchCase(void);

int main(int argc, char** argv);

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

enum Stringoption1_Discriminant {
    None_1,
    Some_1,
};

struct Stringoption1_ {
    enum Stringoption1_Discriminant discriminant;
    union {
        struct String Some_1;
    };
};

enum Unitoption1_Discriminant {
    None_2,
    Some_2,
};

struct Unitoption1_ {
    enum Unitoption1_Discriminant discriminant;
    union {
        char Some_2;
    };
};

void option_option_basicSomeCase(void) {
    char match_;
    struct Intoption1_ variant_;
    variant_ = (struct Intoption1_){.discriminant = Some_, .Some_ = 1};
    if ((variant_.discriminant != None_)) goto next_2;
    milone_assert(false, (struct String){.ptr = "option/option.milone", .len = 20}, 6, 12);
    match_ = 0;
    goto end_match_1;
next_2:;
    if ((variant_.discriminant != Some_)) goto next_3;
    if ((variant_.Some_ != 1)) goto next_3;
    match_ = 0;
    goto end_match_1;
next_3:;
    milone_assert(false, (struct String){.ptr = "option/option.milone", .len = 20}, 10, 9);
    match_ = 0;
    goto end_match_1;
next_4:;
end_match_1:;
    return;
}

void option_option_basicNoneCase(void) {
    char match_1;
    if (((struct Stringoption1_){.discriminant = None_1}.discriminant != Some_1)) goto next_6;
    if ((string_compare((struct Stringoption1_){.discriminant = None_1}.Some_1, (struct String){.ptr = "a", .len = 1}) != 0)) goto next_6;
    milone_assert(false, (struct String){.ptr = "option/option.milone", .len = 20}, 14, 16);
    match_1 = 0;
    goto end_match_5;
next_6:;
    if (((struct Stringoption1_){.discriminant = None_1}.discriminant != None_1)) goto next_7;
    match_1 = 0;
    goto end_match_5;
next_7:;
    milone_assert(false, (struct String){.ptr = "option/option.milone", .len = 20}, 18, 9);
    match_1 = 0;
    goto end_match_5;
next_8:;
end_match_5:;
    return;
}

void option_option_basicMatchCase(void) {
    char switch_;
    struct Unitoption1_ variant_1;
    variant_1 = (struct Unitoption1_){.discriminant = Some_2, .Some_2 = 0};
    switch (variant_1.discriminant) {
        case None_2:
            goto clause_10;

        default:
            goto clause_11;
    }
clause_10:;
    milone_assert(false, (struct String){.ptr = "option/option.milone", .len = 20}, 24, 12);
    switch_ = 0;
    goto switch_next_9;
clause_11:;
    switch_ = 0;
    goto switch_next_9;
switch_next_9:;
    return;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    option_option_basicSomeCase();
    option_option_basicNoneCase();
    option_option_basicMatchCase();
    return 0;
}
