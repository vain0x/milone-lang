#include "milone.h"

struct IntList;

struct IntStringFun1;

struct StringList;

struct IntIntListFun1;

struct IntList;

struct IntBoolFun1;

struct IntIntTuple2_;

struct IntIntTuple2_List;

struct IntIntTuple2_List;

struct IntListIntListTuple2_;

struct IntIntIntFun2;

bool std_list_std_list_testSkipWhile_IntBoolFun1_fun(int arg_8);

bool std_list_std_list_testTakeWhile_IntBoolFun1_fun(int arg_9);

struct String std_list_std_list_eta2_prim(void const* env_, int arg_);

struct StringList const* MiloneCore_List_IntStringFun1IntListStringListFun2_map(struct IntStringFun1 , struct IntList const* );

struct String MiloneStd_StdString_concat(struct String , struct StringList const* );

struct String std_list_std_list_eq_debug(struct IntList const* xs_);

bool std_list_std_list_eq(struct IntList const* expected_, struct IntList const* actual_);

bool std_list_std_list_eta2_testTakeWhile_fun(void const* env_1, int arg_1);

bool std_list_std_list_testTakeWhile_fun(int n_);

bool std_list_std_list_eta2_testTakeWhile_fun_1(void const* env_2, int arg_2);

struct IntList const* MiloneCore_List_IntBoolFun1IntListIntListFun2_takeWhile(struct IntBoolFun1 , struct IntList const* );

void std_list_Program_testTakeWhile(struct IntIntListFun1 gen_);

bool std_list_std_list_eta2_testSkipWhile_fun(void const* env_3, int arg_3);

bool std_list_std_list_testSkipWhile_fun(int n_1);

bool std_list_std_list_eta2_testSkipWhile_fun_1(void const* env_4, int arg_4);

struct IntList const* MiloneCore_List_IntBoolFun1IntListIntListFun2_skipWhile(struct IntBoolFun1 , struct IntList const* );

void std_list_Program_testSkipWhile(struct IntIntListFun1 gen_1);

struct IntListIntListTuple2_ MiloneCore_List_IntIntTuple2ListIntListIntListTuple2Fun1_unzip(struct IntIntTuple2_List const* );

void std_list_Program_testUnzip(void);

struct IntList const* std_list_std_list_main_gen_go(struct IntList const* acc_, int i_);

struct IntList const* std_list_std_list_main_gen(int n_2);

int std_list_std_list_main_fun(int x_, int y_);

int std_list_std_list_eta3_main_fun(void const* env_5, int arg_5, int arg_6);

struct IntList const* std_list_std_list_eta2_main_gen(void const* env_6, int arg_7);

bool MiloneCore_List_IntListBoolFun1_isEmpty(struct IntList const* );

int MiloneCore_List_IntIntIntFun2IntIntListIntFun3_fold(struct IntIntIntFun2 , int , struct IntList const* );

int milone_main(void);

struct IntStringFun1 {
    struct String(*fun)(void const*, int);
    void const* env;
};

struct IntIntListFun1 {
    struct IntList const*(*fun)(void const*, int);
    void const* env;
};

struct IntList {
    int head;
    struct IntList const* tail;
};

struct IntBoolFun1 {
    bool(*fun)(void const*, int);
    void const* env;
};

struct IntIntTuple2_ {
    int t0;
    int t1;
};

struct IntIntTuple2_List {
    struct IntIntTuple2_ head;
    struct IntIntTuple2_List const* tail;
};

struct IntListIntListTuple2_ {
    struct IntList const* t0;
    struct IntList const* t1;
};

struct IntIntIntFun2 {
    int(*fun)(void const*, int, int);
    void const* env;
};

bool std_list_std_list_testSkipWhile_IntBoolFun1_fun(int arg_8) {
    return true;
}

bool std_list_std_list_testTakeWhile_IntBoolFun1_fun(int arg_9) {
    return true;
}

struct String std_list_std_list_eta2_prim(void const* env_, int arg_) {
    struct String call_ = str_of_int64(arg_);
    return call_;
}

struct String std_list_std_list_eq_debug(struct IntList const* xs_) {
    struct IntStringFun1 fun_ = (struct IntStringFun1){.fun = std_list_std_list_eta2_prim, .env = NULL};
    struct StringList const* call_1 = MiloneCore_List_IntStringFun1IntListStringListFun2_map(fun_, xs_);
    struct String call_2 = MiloneStd_StdString_concat((struct String){.str = ", ", .len = 2}, call_1);
    return call_2;
}

bool std_list_std_list_eq(struct IntList const* expected_, struct IntList const* actual_) {
    struct String call_3 = std_list_std_list_eq_debug(expected_);
    struct String expected_1 = call_3;
    struct String call_4 = std_list_std_list_eq_debug(actual_);
    struct String actual_1 = call_4;
    bool if_;
    if ((str_compare(expected_1, actual_1) == 0)) {
        goto then_284;
    } else {
        goto else_285;
    }
then_284:;
    if_ = true;
    goto if_next_283;
else_285:;
    printf("expected: %s\nactual: %s\n\n", str_to_c_str(expected_1), str_to_c_str(actual_1));
    if_ = false;
    goto if_next_283;
if_next_283:;
    return if_;
}

bool std_list_std_list_eta2_testTakeWhile_fun(void const* env_1, int arg_1) {
    bool call_5 = std_list_std_list_testTakeWhile_IntBoolFun1_fun(arg_1);
    return call_5;
}

bool std_list_std_list_testTakeWhile_fun(int n_) {
    return ((n_ % 3) != 2);
}

bool std_list_std_list_eta2_testTakeWhile_fun_1(void const* env_2, int arg_2) {
    bool call_6 = std_list_std_list_testTakeWhile_fun(arg_2);
    return call_6;
}

void std_list_Program_testTakeWhile(struct IntIntListFun1 gen_) {
    struct IntList const* list_2 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_2))) = (struct IntList){.head = 2, .tail = NULL};
    struct IntList const* list_1 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_1))) = (struct IntList){.head = 1, .tail = list_2};
    struct IntList const* list_ = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_))) = (struct IntList){.head = 0, .tail = list_1};
    struct IntBoolFun1 fun_1 = (struct IntBoolFun1){.fun = std_list_std_list_eta2_testTakeWhile_fun, .env = NULL};
    struct IntList const* app_ = gen_.fun(gen_.env, 3);
    struct IntList const* call_7 = MiloneCore_List_IntBoolFun1IntListIntListFun2_takeWhile(fun_1, app_);
    bool call_8 = std_list_std_list_eq(list_, call_7);
    milone_assert(call_8, 22, 2);
    struct IntList const* list_4 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_4))) = (struct IntList){.head = 1, .tail = NULL};
    struct IntList const* list_3 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_3))) = (struct IntList){.head = 0, .tail = list_4};
    struct IntBoolFun1 fun_2 = (struct IntBoolFun1){.fun = std_list_std_list_eta2_testTakeWhile_fun_1, .env = NULL};
    struct IntList const* app_1 = gen_.fun(gen_.env, 6);
    struct IntList const* call_9 = MiloneCore_List_IntBoolFun1IntListIntListFun2_takeWhile(fun_2, app_1);
    bool call_10 = std_list_std_list_eq(list_3, call_9);
    milone_assert(call_10, 26, 2);
    return;
}

bool std_list_std_list_eta2_testSkipWhile_fun(void const* env_3, int arg_3) {
    bool call_11 = std_list_std_list_testSkipWhile_IntBoolFun1_fun(arg_3);
    return call_11;
}

bool std_list_std_list_testSkipWhile_fun(int n_1) {
    return ((n_1 % 2) == 0);
}

bool std_list_std_list_eta2_testSkipWhile_fun_1(void const* env_4, int arg_4) {
    bool call_12 = std_list_std_list_testSkipWhile_fun(arg_4);
    return call_12;
}

void std_list_Program_testSkipWhile(struct IntIntListFun1 gen_1) {
    struct IntBoolFun1 fun_3 = (struct IntBoolFun1){.fun = std_list_std_list_eta2_testSkipWhile_fun, .env = NULL};
    struct IntList const* app_2 = gen_1.fun(gen_1.env, 5);
    struct IntList const* call_13 = MiloneCore_List_IntBoolFun1IntListIntListFun2_skipWhile(fun_3, app_2);
    bool call_14 = std_list_std_list_eq(NULL, call_13);
    milone_assert(call_14, 31, 2);
    struct IntList const* list_8 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_8))) = (struct IntList){.head = 4, .tail = NULL};
    struct IntList const* list_7 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_7))) = (struct IntList){.head = 3, .tail = list_8};
    struct IntList const* list_6 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_6))) = (struct IntList){.head = 2, .tail = list_7};
    struct IntList const* list_5 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_5))) = (struct IntList){.head = 1, .tail = list_6};
    struct IntBoolFun1 fun_4 = (struct IntBoolFun1){.fun = std_list_std_list_eta2_testSkipWhile_fun_1, .env = NULL};
    struct IntList const* app_3 = gen_1.fun(gen_1.env, 5);
    struct IntList const* call_15 = MiloneCore_List_IntBoolFun1IntListIntListFun2_skipWhile(fun_4, app_3);
    bool call_16 = std_list_std_list_eq(list_5, call_15);
    milone_assert(call_16, 33, 2);
    return;
}

void std_list_Program_testUnzip(void) {
    struct IntIntTuple2_ IntIntTuple2_ = (struct IntIntTuple2_){.t0 = 0, .t1 = 1};
    struct IntIntTuple2_ IntIntTuple2_1 = (struct IntIntTuple2_){.t0 = 1, .t1 = 1};
    struct IntIntTuple2_ IntIntTuple2_2 = (struct IntIntTuple2_){.t0 = 2, .t1 = 2};
    struct IntIntTuple2_ IntIntTuple2_3 = (struct IntIntTuple2_){.t0 = 3, .t1 = 3};
    struct IntIntTuple2_ IntIntTuple2_4 = (struct IntIntTuple2_){.t0 = 4, .t1 = 5};
    struct IntIntTuple2_List const* list_13 = milone_mem_alloc(1, sizeof(struct IntIntTuple2_List));
    (*(((struct IntIntTuple2_List*)list_13))) = (struct IntIntTuple2_List){.head = IntIntTuple2_4, .tail = NULL};
    struct IntIntTuple2_List const* list_12 = milone_mem_alloc(1, sizeof(struct IntIntTuple2_List));
    (*(((struct IntIntTuple2_List*)list_12))) = (struct IntIntTuple2_List){.head = IntIntTuple2_3, .tail = list_13};
    struct IntIntTuple2_List const* list_11 = milone_mem_alloc(1, sizeof(struct IntIntTuple2_List));
    (*(((struct IntIntTuple2_List*)list_11))) = (struct IntIntTuple2_List){.head = IntIntTuple2_2, .tail = list_12};
    struct IntIntTuple2_List const* list_10 = milone_mem_alloc(1, sizeof(struct IntIntTuple2_List));
    (*(((struct IntIntTuple2_List*)list_10))) = (struct IntIntTuple2_List){.head = IntIntTuple2_1, .tail = list_11};
    struct IntIntTuple2_List const* list_9 = milone_mem_alloc(1, sizeof(struct IntIntTuple2_List));
    (*(((struct IntIntTuple2_List*)list_9))) = (struct IntIntTuple2_List){.head = IntIntTuple2_, .tail = list_10};
    struct IntListIntListTuple2_ call_17 = MiloneCore_List_IntIntTuple2ListIntListIntListTuple2Fun1_unzip(list_9);
    struct IntList const* xs_1 = call_17.t0;
    struct IntList const* ys_ = call_17.t1;
    struct IntList const* list_18 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_18))) = (struct IntList){.head = 4, .tail = NULL};
    struct IntList const* list_17 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_17))) = (struct IntList){.head = 3, .tail = list_18};
    struct IntList const* list_16 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_16))) = (struct IntList){.head = 2, .tail = list_17};
    struct IntList const* list_15 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_15))) = (struct IntList){.head = 1, .tail = list_16};
    struct IntList const* list_14 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_14))) = (struct IntList){.head = 0, .tail = list_15};
    bool call_18 = std_list_std_list_eq(list_14, xs_1);
    milone_assert(call_18, 47, 2);
    struct IntList const* list_23 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_23))) = (struct IntList){.head = 5, .tail = NULL};
    struct IntList const* list_22 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_22))) = (struct IntList){.head = 3, .tail = list_23};
    struct IntList const* list_21 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_21))) = (struct IntList){.head = 2, .tail = list_22};
    struct IntList const* list_20 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_20))) = (struct IntList){.head = 1, .tail = list_21};
    struct IntList const* list_19 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_19))) = (struct IntList){.head = 1, .tail = list_20};
    bool call_19 = std_list_std_list_eq(list_19, ys_);
    milone_assert(call_19, 48, 2);
    return;
}

struct IntList const* std_list_std_list_main_gen_go(struct IntList const* acc_, int i_) {
tailrec_286:;
    struct IntList const* if_1;
    if ((i_ == 0)) {
        goto then_288;
    } else {
        goto else_289;
    }
then_288:;
    if_1 = acc_;
    goto if_next_287;
else_289:;
    int i_1 = (i_ - 1);
    struct IntList const* list_24 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_24))) = (struct IntList){.head = i_1, .tail = acc_};
    struct IntList const* arg_10 = list_24;
    int arg_11 = i_1;
    acc_ = arg_10;
    i_ = arg_11;
    goto tailrec_286;
if_next_287:;
    return if_1;
}

struct IntList const* std_list_std_list_main_gen(int n_2) {
    struct IntList const* call_20 = std_list_std_list_main_gen_go(NULL, n_2);
    return call_20;
}

int std_list_std_list_main_fun(int x_, int y_) {
    return (x_ + y_);
}

int std_list_std_list_eta3_main_fun(void const* env_5, int arg_5, int arg_6) {
    int call_21 = std_list_std_list_main_fun(arg_5, arg_6);
    return call_21;
}

struct IntList const* std_list_std_list_eta2_main_gen(void const* env_6, int arg_7) {
    struct IntList const* call_22 = std_list_std_list_main_gen(arg_7);
    return call_22;
}

int milone_main(void) {
    struct IntList const* call_23 = std_list_std_list_main_gen(0);
    bool call_24 = MiloneCore_List_IntListBoolFun1_isEmpty(call_23);
    milone_assert(call_24, 64, 2);
    struct IntIntIntFun2 fun_5 = (struct IntIntIntFun2){.fun = std_list_std_list_eta3_main_fun, .env = NULL};
    struct IntList const* call_25 = std_list_std_list_main_gen(5);
    int call_26 = MiloneCore_List_IntIntIntFun2IntIntListIntFun3_fold(fun_5, 0, call_25);
    milone_assert((call_26 == ((((0 + 1) + 2) + 3) + 4)), 66, 2);
    struct IntIntListFun1 fun_6 = (struct IntIntListFun1){.fun = std_list_std_list_eta2_main_gen, .env = NULL};
    struct IntIntListFun1 gen_2 = fun_6;
    std_list_Program_testSkipWhile(gen_2);
    std_list_Program_testUnzip();
    return 0;
}
