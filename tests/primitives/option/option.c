#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32option1_;

struct Stringoption1_;

struct Unitoption1_;

void option_option_basicSomeCase(void);

void option_option_basicNoneCase(void);

void option_option_basicMatchCase(void);

int main(int argc, char **argv);

enum Int32option1_Discriminant {
    Int32option1_None,
    Int32option1_Some,
};

struct Int32option1_ {
    enum Int32option1_Discriminant discriminant;
    union {
        int32_t Int32option1_Some;
    };
};

enum Stringoption1_Discriminant {
    Stringoption1_None,
    Stringoption1_Some,
};

struct Stringoption1_ {
    enum Stringoption1_Discriminant discriminant;
    union {
        struct String Stringoption1_Some;
    };
};

enum Unitoption1_Discriminant {
    Unitoption1_None,
    Unitoption1_Some,
};

struct Unitoption1_ {
    enum Unitoption1_Discriminant discriminant;
    union {
        char Unitoption1_Some;
    };
};

void option_option_basicSomeCase(void) {
    char match_;
    struct Int32option1_ variant_;
    variant_ = (struct Int32option1_){.discriminant = Int32option1_Some, .Int32option1_Some = 1};
    if ((variant_.discriminant != Int32option1_None)) goto next_2;
    if (true) milone_assert_error("option/option.milone", 6, 12);
    match_ = 0;
    goto end_match_1;
next_2:;
    if ((variant_.discriminant != Int32option1_Some)) goto next_3;
    if ((variant_.Int32option1_Some != 1)) goto next_3;
    match_ = 0;
    goto end_match_1;
next_3:;
    if (true) milone_assert_error("option/option.milone", 10, 9);
    match_ = 0;
    goto end_match_1;
next_4:;
end_match_1:;
    return;
}

void option_option_basicNoneCase(void) {
    char match_1;
    if (((struct Stringoption1_){.discriminant = Stringoption1_None}.discriminant != Stringoption1_Some)) goto next_2;
    if ((string_compare((struct Stringoption1_){.discriminant = Stringoption1_None}.Stringoption1_Some, (struct String){.ptr = "a", .len = 1}) != 0)) goto next_2;
    if (true) milone_assert_error("option/option.milone", 14, 16);
    match_1 = 0;
    goto end_match_1;
next_2:;
    if (((struct Stringoption1_){.discriminant = Stringoption1_None}.discriminant != Stringoption1_None)) goto next_3;
    match_1 = 0;
    goto end_match_1;
next_3:;
    if (true) milone_assert_error("option/option.milone", 18, 9);
    match_1 = 0;
    goto end_match_1;
next_4:;
end_match_1:;
    return;
}

void option_option_basicMatchCase(void) {
    char switch_;
    struct Unitoption1_ variant_1;
    variant_1 = (struct Unitoption1_){.discriminant = Unitoption1_Some, .Unitoption1_Some = 0};
    switch (variant_1.discriminant) {
        case Unitoption1_None:
            goto clause_2;

        default:
            goto clause_3;
    }
clause_2:;
    if (true) milone_assert_error("option/option.milone", 24, 12);
    switch_ = 0;
    goto switch_next_1;
clause_3:;
    switch_ = 0;
    goto switch_next_1;
switch_next_1:;
    return;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    option_option_basicSomeCase();
    option_option_basicNoneCase();
    option_option_basicMatchCase();
    return 0;
}
