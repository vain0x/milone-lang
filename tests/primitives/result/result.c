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

_Noreturn void MiloneCore_Prelude_exit(int32_t);

_Noreturn void result_result_unexpected(struct Int32StringResult2_ result_);

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

_Noreturn void result_result_unexpected(struct Int32StringResult2_ result_) {
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
    MiloneCore_Prelude_exit(1);
    milone_never_error("result/result.milone", 4, 0);
}

int32_t result_result_unwrapOk(struct Int32StringResult2_ result_1) {
    int32_t value_1;
    int32_t match_1;
    if ((result_1.discriminant != Int32StringResult2_Ok)) goto next_14;
    value_1 = result_1.Int32StringResult2_Ok;
    match_1 = value_1;
    goto end_match_13;
next_14:;
    result_result_unexpected(result_1);
    milone_never_error("result/result.milone", 15, 19);
next_15:;
end_match_13:;
    return match_1;
}

struct String result_result_unwrapError(struct Int32StringResult2_ result_2) {
    struct String e_1;
    struct String match_2;
    if ((result_2.discriminant != Int32StringResult2_Error)) goto next_17;
    e_1 = result_2.Int32StringResult2_Error;
    match_2 = e_1;
    goto end_match_16;
next_17:;
    result_result_unexpected(result_2);
    milone_never_error("result/result.milone", 20, 19);
next_18:;
end_match_16:;
    return match_2;
}

struct Int32StringResult2_ result_result_testBind_divBy2(int32_t n_) {
    struct Int32StringResult2_ if_;
    struct Int32StringResult2_ variant_;
    struct Int32StringResult2_ variant_1;
    if (((n_ % 2) == 0)) {
        goto then_20;
    } else {
        goto else_21;
    }
then_20:;
    variant_ = (struct Int32StringResult2_){.discriminant = Int32StringResult2_Ok, .Int32StringResult2_Ok = (n_ / 2)};
    if_ = variant_;
    goto if_next_19;
else_21:;
    variant_1 = (struct Int32StringResult2_){.discriminant = Int32StringResult2_Error, .Int32StringResult2_Error = (struct String){.ptr = "Odd", .len = 3}};
    if_ = variant_1;
    goto if_next_19;
if_next_19:;
    return if_;
}

struct Int32StringResult2_ result_result_eta2_testBind_divBy2(void const *env_, int32_t arg_) {
    struct Int32StringResult2_ call_;
    call_ = result_result_testBind_divBy2(arg_);
    return call_;
}

struct Int32StringResult2_ result_result_eta2_testBind_divBy2_1(void const *env_1, int32_t arg_1) {
    struct Int32StringResult2_ call_1;
    call_1 = result_result_testBind_divBy2(arg_1);
    return call_1;
}

struct Int32StringResult2_ result_result_eta2_testBind_divBy2_2(void const *env_2, int32_t arg_2) {
    struct Int32StringResult2_ call_2;
    call_2 = result_result_testBind_divBy2(arg_2);
    return call_2;
}

void result_result_testBind(void) {
    struct Int32Int32StringResult2_Fun1 fun_;
    struct Int32StringResult2_ variant_2;
    struct Int32StringResult2_ call_3;
    int32_t call_4;
    struct Int32Int32StringResult2_Fun1 fun_1;
    struct Int32StringResult2_ variant_3;
    struct Int32StringResult2_ call_5;
    struct String call_6;
    struct Int32Int32StringResult2_Fun1 fun_2;
    struct Int32StringResult2_ variant_4;
    struct Int32StringResult2_ call_7;
    struct String call_8;
    fun_ = (struct Int32Int32StringResult2_Fun1){.fun = result_result_eta2_testBind_divBy2, .env = NULL};
    variant_2 = (struct Int32StringResult2_){.discriminant = Int32StringResult2_Ok, .Int32StringResult2_Ok = 2};
    call_3 = MiloneCore_Result_Int32Int32StringResult2Fun1Int32StringResult2Int32StringResult2Fun2_bind(fun_, variant_2);
    call_4 = result_result_unwrapOk(call_3);
    if ((call_4 != 1)) milone_assert_error("result/result.milone", 29, 2);
    fun_1 = (struct Int32Int32StringResult2_Fun1){.fun = result_result_eta2_testBind_divBy2_1, .env = NULL};
    variant_3 = (struct Int32StringResult2_){.discriminant = Int32StringResult2_Ok, .Int32StringResult2_Ok = 3};
    call_5 = MiloneCore_Result_Int32Int32StringResult2Fun1Int32StringResult2Int32StringResult2Fun2_bind(fun_1, variant_3);
    call_6 = result_result_unwrapError(call_5);
    if ((string_compare(call_6, (struct String){.ptr = "Odd", .len = 3}) != 0)) milone_assert_error("result/result.milone", 30, 2);
    fun_2 = (struct Int32Int32StringResult2_Fun1){.fun = result_result_eta2_testBind_divBy2_2, .env = NULL};
    variant_4 = (struct Int32StringResult2_){.discriminant = Int32StringResult2_Error, .Int32StringResult2_Error = (struct String){.ptr = "Bad", .len = 3}};
    call_7 = MiloneCore_Result_Int32Int32StringResult2Fun1Int32StringResult2Int32StringResult2Fun2_bind(fun_2, variant_4);
    call_8 = result_result_unwrapError(call_7);
    if ((string_compare(call_8, (struct String){.ptr = "Bad", .len = 3}) != 0)) milone_assert_error("result/result.milone", 31, 2);
    return;
}

int32_t result_result_testMap_inc(int32_t n_1) {
    return (n_1 + 1);
}

int32_t result_result_eta2_testMap_inc(void const *env_3, int32_t arg_3) {
    int32_t call_9;
    call_9 = result_result_testMap_inc(arg_3);
    return call_9;
}

int32_t result_result_eta2_testMap_inc_1(void const *env_4, int32_t arg_4) {
    int32_t call_10;
    call_10 = result_result_testMap_inc(arg_4);
    return call_10;
}

void result_result_testMap(void) {
    struct Int32Int32Fun1 fun_3;
    struct Int32StringResult2_ variant_5;
    struct Int32StringResult2_ call_11;
    int32_t call_12;
    struct Int32Int32Fun1 fun_4;
    struct Int32StringResult2_ variant_6;
    struct Int32StringResult2_ call_13;
    struct String call_14;
    fun_3 = (struct Int32Int32Fun1){.fun = result_result_eta2_testMap_inc, .env = NULL};
    variant_5 = (struct Int32StringResult2_){.discriminant = Int32StringResult2_Ok, .Int32StringResult2_Ok = 2};
    call_11 = MiloneCore_Result_Int32Int32Fun1Int32StringResult2Int32StringResult2Fun2_map(fun_3, variant_5);
    call_12 = result_result_unwrapOk(call_11);
    if ((call_12 != 3)) milone_assert_error("result/result.milone", 36, 2);
    fun_4 = (struct Int32Int32Fun1){.fun = result_result_eta2_testMap_inc_1, .env = NULL};
    variant_6 = (struct Int32StringResult2_){.discriminant = Int32StringResult2_Error, .Int32StringResult2_Error = (struct String){.ptr = "Bad", .len = 3}};
    call_13 = MiloneCore_Result_Int32Int32Fun1Int32StringResult2Int32StringResult2Fun2_map(fun_4, variant_6);
    call_14 = result_result_unwrapError(call_13);
    if ((string_compare(call_14, (struct String){.ptr = "Bad", .len = 3}) != 0)) milone_assert_error("result/result.milone", 37, 2);
    return;
}

struct String result_result_testMapError_bang(struct String s_) {
    return string_add(s_, (struct String){.ptr = "!", .len = 1});
}

struct String result_result_eta2_testMapError_bang(void const *env_5, struct String arg_5) {
    struct String call_15;
    call_15 = result_result_testMapError_bang(arg_5);
    return call_15;
}

struct String result_result_eta2_testMapError_bang_1(void const *env_6, struct String arg_6) {
    struct String call_16;
    call_16 = result_result_testMapError_bang(arg_6);
    return call_16;
}

void result_result_testMapError(void) {
    struct StringStringFun1 fun_5;
    struct Int32StringResult2_ variant_7;
    struct Int32StringResult2_ call_17;
    int32_t call_18;
    struct StringStringFun1 fun_6;
    struct Int32StringResult2_ variant_8;
    struct Int32StringResult2_ call_19;
    struct String call_20;
    fun_5 = (struct StringStringFun1){.fun = result_result_eta2_testMapError_bang, .env = NULL};
    variant_7 = (struct Int32StringResult2_){.discriminant = Int32StringResult2_Ok, .Int32StringResult2_Ok = 2};
    call_17 = MiloneCore_Result_StringStringFun1Int32StringResult2Int32StringResult2Fun2_mapError(fun_5, variant_7);
    call_18 = result_result_unwrapOk(call_17);
    if ((call_18 != 2)) milone_assert_error("result/result.milone", 42, 2);
    fun_6 = (struct StringStringFun1){.fun = result_result_eta2_testMapError_bang_1, .env = NULL};
    variant_8 = (struct Int32StringResult2_){.discriminant = Int32StringResult2_Error, .Int32StringResult2_Error = (struct String){.ptr = "Bad", .len = 3}};
    call_19 = MiloneCore_Result_StringStringFun1Int32StringResult2Int32StringResult2Fun2_mapError(fun_6, variant_8);
    call_20 = result_result_unwrapError(call_19);
    if ((string_compare(call_20, (struct String){.ptr = "Bad!", .len = 4}) != 0)) milone_assert_error("result/result.milone", 43, 2);
    return;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    result_result_testBind();
    result_result_testMap();
    result_result_testMapError();
    return 0;
}
