#include "milone.h"

struct IntOption;

struct IntOption MiloneStd_StdInt_tryParse(struct String);

int parseOk_(struct String s_2);

bool parseError_(struct String s_3);

char std_int_Program_tryParseTest(char arg_1);

int milone_main();

struct IntOption {
    bool some;
    int value;
};

int MiloneStd_StdInt_MinValue;

int MiloneStd_StdInt_MaxValue;

int parseOk_(struct String s_2) {
    int match_;
    struct IntOption call_3 = MiloneStd_StdInt_tryParse(s_2);
    if ((!(call_3.some))) goto next_11;
    int value_1 = call_3.value;
    match_ = value_1;
    goto end_match_10;
next_11:;
    if (call_3.some) goto next_12;
    printf("should parse: %s\n", str_to_c_str(s_2));
    milone_assert(false, 11, 6);
    match_ = 0;
    goto end_match_10;
next_12:;
    exit(1);
end_match_10:;
    return match_;
}

bool parseError_(struct String s_3) {
    bool match_1;
    struct IntOption call_4 = MiloneStd_StdInt_tryParse(s_3);
    if (call_4.some) goto next_14;
    match_1 = true;
    goto end_match_13;
next_14:;
    if ((!(call_4.some))) goto next_15;
    int value_2 = call_4.value;
    printf("should not parse: %s -> %d\n", str_to_c_str(s_3), value_2);
    match_1 = false;
    goto end_match_13;
next_15:;
    exit(1);
end_match_13:;
    return match_1;
}

char std_int_Program_tryParseTest(char arg_1) {
    int call_5 = parseOk_((struct String){.str = "0", .len = 1});
    milone_assert((call_5 == 0), 21, 2);
    int call_6 = parseOk_((struct String){.str = "000", .len = 3});
    milone_assert((call_6 == 0), 22, 2);
    int call_7 = parseOk_((struct String){.str = "0010", .len = 4});
    milone_assert((call_7 == 10), 23, 2);
    int call_8 = parseOk_((struct String){.str = "42", .len = 2});
    milone_assert((call_8 == 42), 24, 2);
    int call_9 = parseOk_((struct String){.str = " \t            42             \t ", .len = 31});
    milone_assert((call_9 == 42), 25, 2);
    int call_10 = parseOk_((struct String){.str = "+81", .len = 3});
    milone_assert((call_10 == 81), 26, 2);
    int call_11 = parseOk_((struct String){.str = "-1", .len = 2});
    milone_assert(((call_11 + 1) == 0), 27, 2);
    int call_12 = parseOk_((struct String){.str = "2147483647", .len = 10});
    milone_assert((call_12 == 2147483647), 28, 2);
    int call_13 = parseOk_((struct String){.str = "-2147483648", .len = 11});
    milone_assert(((call_13 + 1) == -2147483647), 29, 2);
    struct String slice_ = str_get_slice(0, 4, (struct String){.str = "123456789123456789", .len = 18});
    int call_14 = parseOk_(slice_);
    milone_assert((call_14 == 12345), 30, 2);
    bool call_15 = parseError_((struct String){.str = "", .len = 0});
    milone_assert(call_15, 32, 2);
    bool call_16 = parseError_((struct String){.str = "   ", .len = 3});
    milone_assert(call_16, 33, 2);
    bool call_17 = parseError_((struct String){.str = "\0 1", .len = 3});
    milone_assert(call_17, 34, 2);
    bool call_18 = parseError_((struct String){.str = "+ 81", .len = 4});
    milone_assert(call_18, 35, 2);
    bool call_19 = parseError_((struct String){.str = "2147483648", .len = 10});
    milone_assert(call_19, 36, 2);
    bool call_20 = parseError_((struct String){.str = "-2147483649", .len = 11});
    milone_assert(call_20, 37, 2);
    bool call_21 = parseError_((struct String){.str = "0x0", .len = 3});
    milone_assert(call_21, 38, 2);
    bool call_22 = parseError_((struct String){.str = "0.0", .len = 3});
    milone_assert(call_22, 39, 2);
    bool call_23 = parseError_((struct String){.str = ".0", .len = 2});
    milone_assert(call_23, 40, 2);
    bool call_24 = parseError_((struct String){.str = "1e9", .len = 3});
    milone_assert(call_24, 41, 2);
    return 0;
}

int milone_main() {
    MiloneStd_StdInt_MinValue = -2147483648;
    MiloneStd_StdInt_MaxValue = 2147483647;
    char call_25 = std_int_Program_tryParseTest(0);
    return 0;
}
