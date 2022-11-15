#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32StringResult2_;

typedef struct Int32StringResult2_(*VoidConstPtrInt32Int32StringResult2_FunPtr2)(void const *, int32_t);

struct Int32Int32StringResult2_Fun1;

typedef int32_t(*VoidConstPtrInt32Int32FunPtr2)(void const *, int32_t);

struct Int32Int32Fun1;

typedef struct String(*VoidConstPtrStringStringFunPtr2)(void const *, struct String);

struct StringStringFun1;

struct String result_result_Int32StringResult2StringFun1_unexpected(struct Int32StringResult2_ result_);

int32_t result_result_Int32StringResult2Int32Fun1_unexpected(struct Int32StringResult2_ result_);

int32_t result_result_unwrapOk(struct Int32StringResult2_ result_1);

struct String result_result_unwrapError(struct Int32StringResult2_ result_2);

struct Int32StringResult2_ result_result_testBind_divBy2(int32_t n_);

struct Int32StringResult2_ result_result_eta2_testBind_divBy2(void const *env_, int32_t arg_);

struct Int32StringResult2_ result_result_eta2_testBind_divBy2_1(void const *env_1, int32_t arg_1);

struct Int32StringResult2_ result_result_eta2_testBind_divBy2_2(void const *env_2, int32_t arg_2);

struct Int32StringResult2_ MiloneCore_Result_Int32Int32StringResult2Fun1Int32StringResult2Int32StringResult2Fun2_bind(struct Int32Int32StringResult2_Fun1, struct Int32StringResult2_);

void result_result_testBind(void);

int32_t result_result_testMap_inc(int32_t n_1);

int32_t result_result_eta2_testMap_inc(void const *env_3, int32_t arg_3);

int32_t result_result_eta2_testMap_inc_1(void const *env_4, int32_t arg_4);

struct Int32StringResult2_ MiloneCore_Result_Int32Int32Fun1Int32StringResult2Int32StringResult2Fun2_map(struct Int32Int32Fun1, struct Int32StringResult2_);

void result_result_testMap(void);

struct String result_result_testMapError_bang(struct String s_);

struct String result_result_eta2_testMapError_bang(void const *env_5, struct String arg_5);

struct String result_result_eta2_testMapError_bang_1(void const *env_6, struct String arg_6);

struct Int32StringResult2_ MiloneCore_Result_StringStringFun1Int32StringResult2Int32StringResult2Fun2_mapError(struct StringStringFun1, struct Int32StringResult2_);

void result_result_testMapError(void);

int main(int argc, char **argv);

enum Int32StringResult2_Discriminant {
    Int32StringResult2_Error,
    Int32StringResult2_Ok,
};

struct Int32StringResult2_ {
    enum Int32StringResult2_Discriminant discriminant;
    union {
        struct String Int32StringResult2_Error;
        int32_t Int32StringResult2_Ok;
    };
};

struct Int32Int32StringResult2_Fun1 {
    VoidConstPtrInt32Int32StringResult2_FunPtr2 fun;
    void const *env;
};

struct Int32Int32Fun1 {
    VoidConstPtrInt32Int32FunPtr2 fun;
    void const *env;
};

struct StringStringFun1 {
    VoidConstPtrStringStringFunPtr2 fun;
    void const *env;
};

struct String result_result_Int32StringResult2StringFun1_unexpected(struct Int32StringResult2_ result_) {
    int32_t value_;
    struct String e_;
    char match_;
    if ((result_.discriminant != Int32StringResult2_Ok)) goto next_11;
    value_ = result_.Int32StringResult2_Ok;
    printf("Ok(%d)\n", value_);
    match_ = 0;
    goto end_match_10;
next_11:;
    if ((result_.discriminant != Int32StringResult2_Error)) goto next_12;
    e_ = result_.Int32StringResult2_Error;
    printf("Error(%s)\n", string_to_c_str(e_));
    match_ = 0;
    goto end_match_10;
next_12:;
    milone_exhaust_error("result/result.milone", 5, 2);
end_match_10:;
    if (true) milone_assert_error("result/result.milone", 9, 2);
    exit(1);
}

int32_t result_result_Int32StringResult2Int32Fun1_unexpected(struct Int32StringResult2_ result_) {
    int32_t value_;
    struct String e_;
    char match_1;
    if ((result_.discriminant != Int32StringResult2_Ok)) goto next_14;
    value_ = result_.Int32StringResult2_Ok;
    printf("Ok(%d)\n", value_);
    match_1 = 0;
    goto end_match_13;
next_14:;
    if ((result_.discriminant != Int32StringResult2_Error)) goto next_15;
    e_ = result_.Int32StringResult2_Error;
    printf("Error(%s)\n", string_to_c_str(e_));
    match_1 = 0;
    goto end_match_13;
next_15:;
    milone_exhaust_error("result/result.milone", 5, 2);
end_match_13:;
    if (true) milone_assert_error("result/result.milone", 9, 2);
    exit(1);
}

int32_t result_result_unwrapOk(struct Int32StringResult2_ result_1) {
    int32_t value_1;
    int32_t match_2;
    int32_t call_;
    if ((result_1.discriminant != Int32StringResult2_Ok)) goto next_17;
    value_1 = result_1.Int32StringResult2_Ok;
    match_2 = value_1;
    goto end_match_16;
next_17:;
    call_ = result_result_Int32StringResult2Int32Fun1_unexpected(result_1);
    match_2 = call_;
    goto end_match_16;
next_18:;
end_match_16:;
    return match_2;
}

struct String result_result_unwrapError(struct Int32StringResult2_ result_2) {
    struct String e_1;
    struct String match_3;
    struct String call_1;
    if ((result_2.discriminant != Int32StringResult2_Error)) goto next_20;
    e_1 = result_2.Int32StringResult2_Error;
    match_3 = e_1;
    goto end_match_19;
next_20:;
    call_1 = result_result_Int32StringResult2StringFun1_unexpected(result_2);
    match_3 = call_1;
    goto end_match_19;
next_21:;
end_match_19:;
    return match_3;
}

struct Int32StringResult2_ result_result_testBind_divBy2(int32_t n_) {
    struct Int32StringResult2_ if_;
    struct Int32StringResult2_ variant_;
    struct Int32StringResult2_ variant_1;
    if (((n_ % 2) == 0)) {
        goto then_23;
    } else {
        goto else_24;
    }
then_23:;
    variant_ = (struct Int32StringResult2_){.discriminant = Int32StringResult2_Ok, .Int32StringResult2_Ok = (n_ / 2)};
    if_ = variant_;
    goto if_next_22;
else_24:;
    variant_1 = (struct Int32StringResult2_){.discriminant = Int32StringResult2_Error, .Int32StringResult2_Error = (struct String){.ptr = "Odd", .len = 3}};
    if_ = variant_1;
    goto if_next_22;
if_next_22:;
    return if_;
}

struct Int32StringResult2_ result_result_eta2_testBind_divBy2(void const *env_, int32_t arg_) {
    struct Int32StringResult2_ call_2;
    call_2 = result_result_testBind_divBy2(arg_);
    return call_2;
}

struct Int32StringResult2_ result_result_eta2_testBind_divBy2_1(void const *env_1, int32_t arg_1) {
    struct Int32StringResult2_ call_3;
    call_3 = result_result_testBind_divBy2(arg_1);
    return call_3;
}

struct Int32StringResult2_ result_result_eta2_testBind_divBy2_2(void const *env_2, int32_t arg_2) {
    struct Int32StringResult2_ call_4;
    call_4 = result_result_testBind_divBy2(arg_2);
    return call_4;
}

void result_result_testBind(void) {
    struct Int32Int32StringResult2_Fun1 fun_;
    struct Int32StringResult2_ variant_2;
    struct Int32StringResult2_ call_5;
    int32_t call_6;
    struct Int32Int32StringResult2_Fun1 fun_1;
    struct Int32StringResult2_ variant_3;
    struct Int32StringResult2_ call_7;
    struct String call_8;
    struct Int32Int32StringResult2_Fun1 fun_2;
    struct Int32StringResult2_ variant_4;
    struct Int32StringResult2_ call_9;
    struct String call_10;
    fun_ = (struct Int32Int32StringResult2_Fun1){.fun = result_result_eta2_testBind_divBy2, .env = NULL};
    variant_2 = (struct Int32StringResult2_){.discriminant = Int32StringResult2_Ok, .Int32StringResult2_Ok = 2};
    call_5 = MiloneCore_Result_Int32Int32StringResult2Fun1Int32StringResult2Int32StringResult2Fun2_bind(fun_, variant_2);
    call_6 = result_result_unwrapOk(call_5);
    if ((call_6 != 1)) milone_assert_error("result/result.milone", 29, 2);
    fun_1 = (struct Int32Int32StringResult2_Fun1){.fun = result_result_eta2_testBind_divBy2_1, .env = NULL};
    variant_3 = (struct Int32StringResult2_){.discriminant = Int32StringResult2_Ok, .Int32StringResult2_Ok = 3};
    call_7 = MiloneCore_Result_Int32Int32StringResult2Fun1Int32StringResult2Int32StringResult2Fun2_bind(fun_1, variant_3);
    call_8 = result_result_unwrapError(call_7);
    if ((string_compare(call_8, (struct String){.ptr = "Odd", .len = 3}) != 0)) milone_assert_error("result/result.milone", 30, 2);
    fun_2 = (struct Int32Int32StringResult2_Fun1){.fun = result_result_eta2_testBind_divBy2_2, .env = NULL};
    variant_4 = (struct Int32StringResult2_){.discriminant = Int32StringResult2_Error, .Int32StringResult2_Error = (struct String){.ptr = "Bad", .len = 3}};
    call_9 = MiloneCore_Result_Int32Int32StringResult2Fun1Int32StringResult2Int32StringResult2Fun2_bind(fun_2, variant_4);
    call_10 = result_result_unwrapError(call_9);
    if ((string_compare(call_10, (struct String){.ptr = "Bad", .len = 3}) != 0)) milone_assert_error("result/result.milone", 31, 2);
    return;
}

int32_t result_result_testMap_inc(int32_t n_1) {
    return (n_1 + 1);
}

int32_t result_result_eta2_testMap_inc(void const *env_3, int32_t arg_3) {
    int32_t call_11;
    call_11 = result_result_testMap_inc(arg_3);
    return call_11;
}

int32_t result_result_eta2_testMap_inc_1(void const *env_4, int32_t arg_4) {
    int32_t call_12;
    call_12 = result_result_testMap_inc(arg_4);
    return call_12;
}

void result_result_testMap(void) {
    struct Int32Int32Fun1 fun_3;
    struct Int32StringResult2_ variant_5;
    struct Int32StringResult2_ call_13;
    int32_t call_14;
    struct Int32Int32Fun1 fun_4;
    struct Int32StringResult2_ variant_6;
    struct Int32StringResult2_ call_15;
    struct String call_16;
    fun_3 = (struct Int32Int32Fun1){.fun = result_result_eta2_testMap_inc, .env = NULL};
    variant_5 = (struct Int32StringResult2_){.discriminant = Int32StringResult2_Ok, .Int32StringResult2_Ok = 2};
    call_13 = MiloneCore_Result_Int32Int32Fun1Int32StringResult2Int32StringResult2Fun2_map(fun_3, variant_5);
    call_14 = result_result_unwrapOk(call_13);
    if ((call_14 != 3)) milone_assert_error("result/result.milone", 36, 2);
    fun_4 = (struct Int32Int32Fun1){.fun = result_result_eta2_testMap_inc_1, .env = NULL};
    variant_6 = (struct Int32StringResult2_){.discriminant = Int32StringResult2_Error, .Int32StringResult2_Error = (struct String){.ptr = "Bad", .len = 3}};
    call_15 = MiloneCore_Result_Int32Int32Fun1Int32StringResult2Int32StringResult2Fun2_map(fun_4, variant_6);
    call_16 = result_result_unwrapError(call_15);
    if ((string_compare(call_16, (struct String){.ptr = "Bad", .len = 3}) != 0)) milone_assert_error("result/result.milone", 37, 2);
    return;
}

struct String result_result_testMapError_bang(struct String s_) {
    return string_add(s_, (struct String){.ptr = "!", .len = 1});
}

struct String result_result_eta2_testMapError_bang(void const *env_5, struct String arg_5) {
    struct String call_17;
    call_17 = result_result_testMapError_bang(arg_5);
    return call_17;
}

struct String result_result_eta2_testMapError_bang_1(void const *env_6, struct String arg_6) {
    struct String call_18;
    call_18 = result_result_testMapError_bang(arg_6);
    return call_18;
}

void result_result_testMapError(void) {
    struct StringStringFun1 fun_5;
    struct Int32StringResult2_ variant_7;
    struct Int32StringResult2_ call_19;
    int32_t call_20;
    struct StringStringFun1 fun_6;
    struct Int32StringResult2_ variant_8;
    struct Int32StringResult2_ call_21;
    struct String call_22;
    fun_5 = (struct StringStringFun1){.fun = result_result_eta2_testMapError_bang, .env = NULL};
    variant_7 = (struct Int32StringResult2_){.discriminant = Int32StringResult2_Ok, .Int32StringResult2_Ok = 2};
    call_19 = MiloneCore_Result_StringStringFun1Int32StringResult2Int32StringResult2Fun2_mapError(fun_5, variant_7);
    call_20 = result_result_unwrapOk(call_19);
    if ((call_20 != 2)) milone_assert_error("result/result.milone", 42, 2);
    fun_6 = (struct StringStringFun1){.fun = result_result_eta2_testMapError_bang_1, .env = NULL};
    variant_8 = (struct Int32StringResult2_){.discriminant = Int32StringResult2_Error, .Int32StringResult2_Error = (struct String){.ptr = "Bad", .len = 3}};
    call_21 = MiloneCore_Result_StringStringFun1Int32StringResult2Int32StringResult2Fun2_mapError(fun_6, variant_8);
    call_22 = result_result_unwrapError(call_21);
    if ((string_compare(call_22, (struct String){.ptr = "Bad!", .len = 4}) != 0)) milone_assert_error("result/result.milone", 43, 2);
    return;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    result_result_testBind();
    result_result_testMap();
    result_result_testMapError();
    return 0;
}
