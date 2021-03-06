#include "milone.h"

struct StringList;

struct IntOption;

struct String str_concat(struct String, struct StringList const*);

struct String __stringJoin_(struct String sep_, struct StringList const* xs_);

int const* __ptrAsConst_1(int* mutPtr_);

void* milone_mem_alloc(int, uintptr_t);

void* memAlloc_(int len_, uintptr_t size_);

void* memcpy(void*, void const*, uintptr_t);

void* memcpy_(void* dest_, void const* src_, uintptr_t size_1);

bool str_to_int_checked(struct String, int*);

struct IntOption __intOfStr_(struct String s_);

int milone_get_arg_count();

int __argCount_(char arg_);

struct String milone_get_arg(int);

struct String __argGet_(int index_4);

int min_(int l_, int r_);

int max_(int l_1, int r_1);

struct IntOption tryParse_(struct String s_1);

int parseOk_(struct String s_2);

bool parseError_(struct String s_3);

char tryParseTest_(char arg_1);

int milone_main();

struct IntOption {
    bool some;
    int value;
};

static int MinValue_;

static int MaxValue_;

struct String __stringJoin_(struct String sep_, struct StringList const* xs_) {
    struct String str_concat_result_ = str_concat(sep_, xs_);
    return str_concat_result_;
}

int const* __ptrAsConst_1(int* mutPtr_) {
    return ((int const*)mutPtr_);
}

void* memAlloc_(int len_, uintptr_t size_) {
    void* milone_mem_alloc_result_ = milone_mem_alloc(len_, size_);
    return milone_mem_alloc_result_;
}

void* memcpy_(void* dest_, void const* src_, uintptr_t size_1) {
    void* memcpy_result_ = memcpy(dest_, src_, size_1);
    return memcpy_result_;
}

struct IntOption __intOfStr_(struct String s_) {
    void* call_ = memAlloc_(1, ((uintptr_t)sizeof(int)));
    int* valueRef_ = ((int*)call_);
    bool str_to_int_checked_result_ = str_to_int_checked(s_, valueRef_);
    bool ok_ = str_to_int_checked_result_;
    struct IntOption if_;
    if (ok_) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    int const* call_1 = __ptrAsConst_1(valueRef_);
    int read_ = (*(call_1));
    struct IntOption some_ = (struct IntOption){.some = true, .value = read_};
    if_ = some_;
    goto if_next_1;
else_3:;
    if_ = (struct IntOption){.some = false};
    goto if_next_1;
if_next_1:;
    return if_;
}

int __argCount_(char arg_) {
    int milone_get_arg_count_result_ = milone_get_arg_count();
    return milone_get_arg_count_result_;
}

struct String __argGet_(int index_4) {
    struct String milone_get_arg_result_ = milone_get_arg(index_4);
    return milone_get_arg_result_;
}

int min_(int l_, int r_) {
    int if_1;
    if ((l_ < r_)) {
        goto then_5;
    } else {
        goto else_6;
    }
then_5:;
    if_1 = l_;
    goto if_next_4;
else_6:;
    if_1 = r_;
    goto if_next_4;
if_next_4:;
    return if_1;
}

int max_(int l_1, int r_1) {
    int if_2;
    if ((l_1 < r_1)) {
        goto then_8;
    } else {
        goto else_9;
    }
then_8:;
    if_2 = r_1;
    goto if_next_7;
else_9:;
    if_2 = l_1;
    goto if_next_7;
if_next_7:;
    return if_2;
}

struct IntOption tryParse_(struct String s_1) {
    struct IntOption call_2 = __intOfStr_(s_1);
    return call_2;
}

int parseOk_(struct String s_2) {
    int match_;
    struct IntOption call_3 = tryParse_(s_2);
    if ((!(call_3.some))) goto next_11;
    int value_1 = call_3.value;
    match_ = value_1;
    goto end_match_10;
next_11:;
    if (call_3.some) goto next_12;
    printf("should parse: %s\n", str_to_c_str(s_2));
    milone_assert(false, 11, 8);
    match_ = 0;
    goto end_match_10;
next_12:;
    exit(1);
end_match_10:;
    return match_;
}

bool parseError_(struct String s_3) {
    bool match_1;
    struct IntOption call_4 = tryParse_(s_3);
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

char tryParseTest_(char arg_1) {
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
    MinValue_ = -2147483648;
    MaxValue_ = 2147483647;
    char call_25 = tryParseTest_(0);
    return 0;
}
