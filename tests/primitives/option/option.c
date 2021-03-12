#include "milone.h"

struct IntOption;

struct StringOption;

struct UnitOption;

char basicSomeCase_(char arg_);

char basicNoneCase_(char arg_1);

char basicMatchCase_(char arg_2);

int milone_main();

struct IntOption {
    bool some;
    int value;
};

struct StringOption {
    bool some;
    struct String value;
};

struct UnitOption {
    bool some;
    char value;
};

char basicSomeCase_(char arg_) {
    char match_;
    struct IntOption some_ = ((struct IntOption){.some = true, .value = 1});
    if (some_.some) goto next_2;
    milone_assert(false, 6, 12);
    match_ = 0;
    goto end_match_1;
next_2:;
    if ((!(some_.some))) goto next_3;
    if ((some_.value != 1)) goto next_3;
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

char basicNoneCase_(char arg_1) {
    struct StringOption none_ = ((struct StringOption){.some = false});
    char match_1;
    if ((!(none_.some))) goto next_6;
    if ((str_compare(none_.value, (struct String){.str = "a", .len = 1}) != 0)) goto next_6;
    milone_assert(false, 17, 16);
    match_1 = 0;
    goto end_match_5;
next_6:;
    if (none_.some) goto next_7;
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

char basicMatchCase_(char arg_2) {
    struct UnitOption some_1 = ((struct UnitOption){.some = true, .value = 0});
    char if_;
    if ((!(some_1.some))) {
        goto none_cl_10;
    } else {
        goto some_cl_11;
    }
none_cl_10:;
    milone_assert(false, 27, 12);
    if_ = 0;
    goto if_next_9;
some_cl_11:;
    if_ = 0;
    goto if_next_9;
if_next_9:;
    return 0;
}

int milone_main() {
    char call_ = basicSomeCase_(0);
    char call_1 = basicNoneCase_(0);
    char call_2 = basicMatchCase_(0);
    return 0;
}
