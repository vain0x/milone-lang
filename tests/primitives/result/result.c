#include <milone.h>

struct IntStringResult2_;

struct IntIntStringResult2_Fun1;

struct IntIntFun1;

struct StringStringFun1;

struct String result_result_IntStringResult2StringFun1_unexpected(struct IntStringResult2_ result_);

int result_result_IntStringResult2IntFun1_unexpected(struct IntStringResult2_ result_);

int result_result_unwrapOk(struct IntStringResult2_ result_1);

struct String result_result_unwrapError(struct IntStringResult2_ result_2);

struct IntStringResult2_ result_result_testBind_divBy2(int n_);

struct IntStringResult2_ result_result_eta2_testBind_divBy2(void const* env_, int arg_);

struct IntStringResult2_ result_result_eta2_testBind_divBy2_1(void const* env_1, int arg_1);

struct IntStringResult2_ result_result_eta2_testBind_divBy2_2(void const* env_2, int arg_2);

struct IntStringResult2_ MiloneCore_Result_IntIntStringResult2Fun1IntStringResult2IntStringResult2Fun2_bind(struct IntIntStringResult2_Fun1 , struct IntStringResult2_ );

void result_result_testBind(void);

int result_result_testMap_inc(int n_1);

int result_result_eta2_testMap_inc(void const* env_3, int arg_3);

int result_result_eta2_testMap_inc_1(void const* env_4, int arg_4);

struct IntStringResult2_ MiloneCore_Result_IntIntFun1IntStringResult2IntStringResult2Fun2_map(struct IntIntFun1 , struct IntStringResult2_ );

void result_result_testMap(void);

struct String result_result_testMapError_bang(struct String s_);

struct String result_result_eta2_testMapError_bang(void const* env_5, struct String arg_5);

struct String result_result_eta2_testMapError_bang_1(void const* env_6, struct String arg_6);

struct IntStringResult2_ MiloneCore_Result_StringStringFun1IntStringResult2IntStringResult2Fun2_mapError(struct StringStringFun1 , struct IntStringResult2_ );

void result_result_testMapError(void);

int main(int argc, char** argv);

enum IntStringResult2_Discriminant {
    Error_,
    Ok_,
};

struct IntStringResult2_ {
    enum IntStringResult2_Discriminant discriminant;
    union {
        struct String Error_;
        int Ok_;
    };
};

struct IntIntStringResult2_Fun1 {
    struct IntStringResult2_(*fun)(void const*, int);
    void const* env;
};

struct IntIntFun1 {
    int(*fun)(void const*, int);
    void const* env;
};

struct StringStringFun1 {
    struct String(*fun)(void const*, struct String);
    void const* env;
};

struct String result_result_IntStringResult2StringFun1_unexpected(struct IntStringResult2_ result_) {
    struct String e_;
    int value_;
    char match_;
    if ((result_.discriminant != Ok_)) goto next_11;
    value_ = result_.Ok_;
    printf("Ok(%d)\n", value_);
    match_ = 0;
    goto end_match_10;
next_11:;
    if ((result_.discriminant != Error_)) goto next_12;
    e_ = result_.Error_;
    printf("Error(%s)\n", str_to_c_str(e_));
    match_ = 0;
    goto end_match_10;
next_12:;
    exit(1);
end_match_10:;
    milone_assert(false, (struct String){.str = "result/result.milone", .len = 20}, 9, 2);
    exit(1);
}

int result_result_IntStringResult2IntFun1_unexpected(struct IntStringResult2_ result_) {
    struct String e_;
    int value_;
    char match_1;
    if ((result_.discriminant != Ok_)) goto next_14;
    value_ = result_.Ok_;
    printf("Ok(%d)\n", value_);
    match_1 = 0;
    goto end_match_13;
next_14:;
    if ((result_.discriminant != Error_)) goto next_15;
    e_ = result_.Error_;
    printf("Error(%s)\n", str_to_c_str(e_));
    match_1 = 0;
    goto end_match_13;
next_15:;
    exit(1);
end_match_13:;
    milone_assert(false, (struct String){.str = "result/result.milone", .len = 20}, 9, 2);
    exit(1);
}

int result_result_unwrapOk(struct IntStringResult2_ result_1) {
    int value_1;
    int match_2;
    if ((result_1.discriminant != Ok_)) goto next_17;
    value_1 = result_1.Ok_;
    match_2 = value_1;
    goto end_match_16;
next_17:;
    int call_ = result_result_IntStringResult2IntFun1_unexpected(result_1);
    match_2 = call_;
    goto end_match_16;
next_18:;
end_match_16:;
    return match_2;
}

struct String result_result_unwrapError(struct IntStringResult2_ result_2) {
    struct String e_1;
    struct String match_3;
    if ((result_2.discriminant != Error_)) goto next_20;
    e_1 = result_2.Error_;
    match_3 = e_1;
    goto end_match_19;
next_20:;
    struct String call_1 = result_result_IntStringResult2StringFun1_unexpected(result_2);
    match_3 = call_1;
    goto end_match_19;
next_21:;
end_match_19:;
    return match_3;
}

struct IntStringResult2_ result_result_testBind_divBy2(int n_) {
    struct IntStringResult2_ if_;
    if (((n_ % 2) == 0)) {
        goto then_23;
    } else {
        goto else_24;
    }
then_23:;
    struct IntStringResult2_ variant_ = (struct IntStringResult2_){.discriminant = Ok_, .Ok_ = (n_ / 2)};
    if_ = variant_;
    goto if_next_22;
else_24:;
    struct IntStringResult2_ variant_1 = (struct IntStringResult2_){.discriminant = Error_, .Error_ = (struct String){.str = "Odd", .len = 3}};
    if_ = variant_1;
    goto if_next_22;
if_next_22:;
    return if_;
}

struct IntStringResult2_ result_result_eta2_testBind_divBy2(void const* env_, int arg_) {
    struct IntStringResult2_ call_2 = result_result_testBind_divBy2(arg_);
    return call_2;
}

struct IntStringResult2_ result_result_eta2_testBind_divBy2_1(void const* env_1, int arg_1) {
    struct IntStringResult2_ call_3 = result_result_testBind_divBy2(arg_1);
    return call_3;
}

struct IntStringResult2_ result_result_eta2_testBind_divBy2_2(void const* env_2, int arg_2) {
    struct IntStringResult2_ call_4 = result_result_testBind_divBy2(arg_2);
    return call_4;
}

void result_result_testBind(void) {
    struct IntIntStringResult2_Fun1 fun_ = (struct IntIntStringResult2_Fun1){.fun = result_result_eta2_testBind_divBy2, .env = NULL};
    struct IntStringResult2_ variant_2 = (struct IntStringResult2_){.discriminant = Ok_, .Ok_ = 2};
    struct IntStringResult2_ call_5 = MiloneCore_Result_IntIntStringResult2Fun1IntStringResult2IntStringResult2Fun2_bind(fun_, variant_2);
    int call_6 = result_result_unwrapOk(call_5);
    milone_assert((call_6 == 1), (struct String){.str = "result/result.milone", .len = 20}, 29, 2);
    struct IntIntStringResult2_Fun1 fun_1 = (struct IntIntStringResult2_Fun1){.fun = result_result_eta2_testBind_divBy2_1, .env = NULL};
    struct IntStringResult2_ variant_3 = (struct IntStringResult2_){.discriminant = Ok_, .Ok_ = 3};
    struct IntStringResult2_ call_7 = MiloneCore_Result_IntIntStringResult2Fun1IntStringResult2IntStringResult2Fun2_bind(fun_1, variant_3);
    struct String call_8 = result_result_unwrapError(call_7);
    milone_assert((str_compare(call_8, (struct String){.str = "Odd", .len = 3}) == 0), (struct String){.str = "result/result.milone", .len = 20}, 30, 2);
    struct IntIntStringResult2_Fun1 fun_2 = (struct IntIntStringResult2_Fun1){.fun = result_result_eta2_testBind_divBy2_2, .env = NULL};
    struct IntStringResult2_ variant_4 = (struct IntStringResult2_){.discriminant = Error_, .Error_ = (struct String){.str = "Bad", .len = 3}};
    struct IntStringResult2_ call_9 = MiloneCore_Result_IntIntStringResult2Fun1IntStringResult2IntStringResult2Fun2_bind(fun_2, variant_4);
    struct String call_10 = result_result_unwrapError(call_9);
    milone_assert((str_compare(call_10, (struct String){.str = "Bad", .len = 3}) == 0), (struct String){.str = "result/result.milone", .len = 20}, 31, 2);
    return;
}

int result_result_testMap_inc(int n_1) {
    return (n_1 + 1);
}

int result_result_eta2_testMap_inc(void const* env_3, int arg_3) {
    int call_11 = result_result_testMap_inc(arg_3);
    return call_11;
}

int result_result_eta2_testMap_inc_1(void const* env_4, int arg_4) {
    int call_12 = result_result_testMap_inc(arg_4);
    return call_12;
}

void result_result_testMap(void) {
    struct IntIntFun1 fun_3 = (struct IntIntFun1){.fun = result_result_eta2_testMap_inc, .env = NULL};
    struct IntStringResult2_ variant_5 = (struct IntStringResult2_){.discriminant = Ok_, .Ok_ = 2};
    struct IntStringResult2_ call_13 = MiloneCore_Result_IntIntFun1IntStringResult2IntStringResult2Fun2_map(fun_3, variant_5);
    int call_14 = result_result_unwrapOk(call_13);
    milone_assert((call_14 == 3), (struct String){.str = "result/result.milone", .len = 20}, 36, 2);
    struct IntIntFun1 fun_4 = (struct IntIntFun1){.fun = result_result_eta2_testMap_inc_1, .env = NULL};
    struct IntStringResult2_ variant_6 = (struct IntStringResult2_){.discriminant = Error_, .Error_ = (struct String){.str = "Bad", .len = 3}};
    struct IntStringResult2_ call_15 = MiloneCore_Result_IntIntFun1IntStringResult2IntStringResult2Fun2_map(fun_4, variant_6);
    struct String call_16 = result_result_unwrapError(call_15);
    milone_assert((str_compare(call_16, (struct String){.str = "Bad", .len = 3}) == 0), (struct String){.str = "result/result.milone", .len = 20}, 37, 2);
    return;
}

struct String result_result_testMapError_bang(struct String s_) {
    return str_add(s_, (struct String){.str = "!", .len = 1});
}

struct String result_result_eta2_testMapError_bang(void const* env_5, struct String arg_5) {
    struct String call_17 = result_result_testMapError_bang(arg_5);
    return call_17;
}

struct String result_result_eta2_testMapError_bang_1(void const* env_6, struct String arg_6) {
    struct String call_18 = result_result_testMapError_bang(arg_6);
    return call_18;
}

void result_result_testMapError(void) {
    struct StringStringFun1 fun_5 = (struct StringStringFun1){.fun = result_result_eta2_testMapError_bang, .env = NULL};
    struct IntStringResult2_ variant_7 = (struct IntStringResult2_){.discriminant = Ok_, .Ok_ = 2};
    struct IntStringResult2_ call_19 = MiloneCore_Result_StringStringFun1IntStringResult2IntStringResult2Fun2_mapError(fun_5, variant_7);
    int call_20 = result_result_unwrapOk(call_19);
    milone_assert((call_20 == 2), (struct String){.str = "result/result.milone", .len = 20}, 42, 2);
    struct StringStringFun1 fun_6 = (struct StringStringFun1){.fun = result_result_eta2_testMapError_bang_1, .env = NULL};
    struct IntStringResult2_ variant_8 = (struct IntStringResult2_){.discriminant = Error_, .Error_ = (struct String){.str = "Bad", .len = 3}};
    struct IntStringResult2_ call_21 = MiloneCore_Result_StringStringFun1IntStringResult2IntStringResult2Fun2_mapError(fun_6, variant_8);
    struct String call_22 = result_result_unwrapError(call_21);
    milone_assert((str_compare(call_22, (struct String){.str = "Bad!", .len = 4}) == 0), (struct String){.str = "result/result.milone", .len = 20}, 43, 2);
    return;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    result_result_testBind();
    result_result_testMap();
    result_result_testMapError();
    return 0;
}
