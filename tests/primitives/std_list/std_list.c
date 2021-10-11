#include "milone.h"

struct IntList;

struct IntStringFun1;

struct StringList;

struct IntIntListFun1;

struct IntBoolFun1;

struct IntList;

struct IntIntTuple2_;

struct IntIntTuple2_List;

struct IntIntTuple2_List;

struct IntListIntListTuple2_;

struct IntIntIntFun2;

struct String fun_5(void const* env_3, int arg_3);

struct StringList const* map_(struct IntStringFun1 , struct IntList const* );

struct String MiloneStd_StdString_concat(struct String , struct StringList const* );

struct String debug_(struct IntList const* xs_66);

bool eq_(struct IntList const* expected_, struct IntList const* actual_);

bool fun_10(int arg_60);

bool fun_6(void const* env_4, int arg_4);

bool fun_(int n_3);

bool fun_7(void const* env_5, int arg_5);

struct IntList const* skipWhile_(struct IntBoolFun1 , struct IntList const* );

void std_list_Program_testSkipWhile(struct IntIntListFun1 gen_);

struct IntListIntListTuple2_ unzip_(struct IntIntTuple2_List const* );

void std_list_Program_testUnzip(void);

struct IntList const* go_(struct IntList const* acc_17, int i_9);

struct IntList const* gen_1(int n_4);

int fun_1(int x_22, int y_3);

int fun_8(void const* env_6, int arg_6, int arg_7);

struct IntList const* fun_9(void const* env_7, int arg_8);

bool isEmpty_(struct IntList const* );

int fold_(struct IntIntIntFun2 , int , struct IntList const* );

int milone_main(void);

struct IntStringFun1 {
    struct String(*fun)(void const*, int);
    void const* env;
};

struct IntIntListFun1 {
    struct IntList const*(*fun)(void const*, int);
    void const* env;
};

struct IntBoolFun1 {
    bool(*fun)(void const*, int);
    void const* env;
};

struct IntList {
    int head;
    struct IntList const* tail;
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

struct String fun_5(void const* env_3, int arg_3) {
    struct String call_53 = str_of_int64(arg_3);
    return call_53;
}

struct String debug_(struct IntList const* xs_66) {
    struct IntStringFun1 fun_14 = (struct IntStringFun1){.fun = fun_5, .env = NULL};
    struct StringList const* call_54 = map_(fun_14, xs_66);
    struct String call_55 = MiloneStd_StdString_concat((struct String){.str = ", ", .len = 2}, call_54);
    return call_55;
}

bool eq_(struct IntList const* expected_, struct IntList const* actual_) {
    struct String call_56 = debug_(expected_);
    struct String expected_1 = call_56;
    struct String call_57 = debug_(actual_);
    struct String actual_1 = call_57;
    bool if_73;
    if ((str_compare(expected_1, actual_1) == 0)) {
        goto then_261;
    } else {
        goto else_262;
    }
then_261:;
    if_73 = true;
    goto if_next_260;
else_262:;
    printf("expected: %s\nactual: %s\n\n", str_to_c_str(expected_1), str_to_c_str(actual_1));
    if_73 = false;
    goto if_next_260;
if_next_260:;
    return if_73;
}

bool fun_10(int arg_60) {
    return true;
}

bool fun_6(void const* env_4, int arg_4) {
    bool call_58 = fun_10(arg_4);
    return call_58;
}

bool fun_(int n_3) {
    return ((n_3 % 2) == 0);
}

bool fun_7(void const* env_5, int arg_5) {
    bool call_59 = fun_(arg_5);
    return call_59;
}

void std_list_Program_testSkipWhile(struct IntIntListFun1 gen_) {
    struct IntBoolFun1 fun_15 = (struct IntBoolFun1){.fun = fun_6, .env = NULL};
    struct IntList const* app_7 = gen_.fun(gen_.env, 5);
    struct IntList const* call_60 = skipWhile_(fun_15, app_7);
    bool call_61 = eq_(NULL, call_60);
    milone_assert(call_61, 22, 2);
    struct IntList const* list_11 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_11))) = (struct IntList){.head = 4, .tail = NULL};
    struct IntList const* list_10 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_10))) = (struct IntList){.head = 3, .tail = list_11};
    struct IntList const* list_9 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_9))) = (struct IntList){.head = 2, .tail = list_10};
    struct IntList const* list_8 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_8))) = (struct IntList){.head = 1, .tail = list_9};
    struct IntBoolFun1 fun_16 = (struct IntBoolFun1){.fun = fun_7, .env = NULL};
    struct IntList const* app_8 = gen_.fun(gen_.env, 5);
    struct IntList const* call_62 = skipWhile_(fun_16, app_8);
    bool call_63 = eq_(list_8, call_62);
    milone_assert(call_63, 24, 2);
    return;
}

void std_list_Program_testUnzip(void) {
    struct IntIntTuple2_ IntIntTuple2_ = (struct IntIntTuple2_){.t0 = 0, .t1 = 1};
    struct IntIntTuple2_ IntIntTuple2_1 = (struct IntIntTuple2_){.t0 = 1, .t1 = 1};
    struct IntIntTuple2_ IntIntTuple2_2 = (struct IntIntTuple2_){.t0 = 2, .t1 = 2};
    struct IntIntTuple2_ IntIntTuple2_3 = (struct IntIntTuple2_){.t0 = 3, .t1 = 3};
    struct IntIntTuple2_ IntIntTuple2_4 = (struct IntIntTuple2_){.t0 = 4, .t1 = 5};
    struct IntIntTuple2_List const* list_16 = milone_mem_alloc(1, sizeof(struct IntIntTuple2_List));
    (*(((struct IntIntTuple2_List*)list_16))) = (struct IntIntTuple2_List){.head = IntIntTuple2_4, .tail = NULL};
    struct IntIntTuple2_List const* list_15 = milone_mem_alloc(1, sizeof(struct IntIntTuple2_List));
    (*(((struct IntIntTuple2_List*)list_15))) = (struct IntIntTuple2_List){.head = IntIntTuple2_3, .tail = list_16};
    struct IntIntTuple2_List const* list_14 = milone_mem_alloc(1, sizeof(struct IntIntTuple2_List));
    (*(((struct IntIntTuple2_List*)list_14))) = (struct IntIntTuple2_List){.head = IntIntTuple2_2, .tail = list_15};
    struct IntIntTuple2_List const* list_13 = milone_mem_alloc(1, sizeof(struct IntIntTuple2_List));
    (*(((struct IntIntTuple2_List*)list_13))) = (struct IntIntTuple2_List){.head = IntIntTuple2_1, .tail = list_14};
    struct IntIntTuple2_List const* list_12 = milone_mem_alloc(1, sizeof(struct IntIntTuple2_List));
    (*(((struct IntIntTuple2_List*)list_12))) = (struct IntIntTuple2_List){.head = IntIntTuple2_, .tail = list_13};
    struct IntListIntListTuple2_ call_64 = unzip_(list_12);
    struct IntList const* xs_67 = call_64.t0;
    struct IntList const* ys_3 = call_64.t1;
    struct IntList const* list_21 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_21))) = (struct IntList){.head = 4, .tail = NULL};
    struct IntList const* list_20 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_20))) = (struct IntList){.head = 3, .tail = list_21};
    struct IntList const* list_19 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_19))) = (struct IntList){.head = 2, .tail = list_20};
    struct IntList const* list_18 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_18))) = (struct IntList){.head = 1, .tail = list_19};
    struct IntList const* list_17 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_17))) = (struct IntList){.head = 0, .tail = list_18};
    bool call_65 = eq_(list_17, xs_67);
    milone_assert(call_65, 38, 2);
    struct IntList const* list_26 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_26))) = (struct IntList){.head = 5, .tail = NULL};
    struct IntList const* list_25 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_25))) = (struct IntList){.head = 3, .tail = list_26};
    struct IntList const* list_24 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_24))) = (struct IntList){.head = 2, .tail = list_25};
    struct IntList const* list_23 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_23))) = (struct IntList){.head = 1, .tail = list_24};
    struct IntList const* list_22 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_22))) = (struct IntList){.head = 1, .tail = list_23};
    bool call_66 = eq_(list_22, ys_3);
    milone_assert(call_66, 39, 2);
    return;
}

struct IntList const* go_(struct IntList const* acc_17, int i_9) {
tailrec_263:;
    struct IntList const* if_74;
    if ((i_9 == 0)) {
        goto then_265;
    } else {
        goto else_266;
    }
then_265:;
    if_74 = acc_17;
    goto if_next_264;
else_266:;
    int i_10 = (i_9 - 1);
    struct IntList const* list_27 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_27))) = (struct IntList){.head = i_10, .tail = acc_17};
    struct IntList const* arg_61 = list_27;
    int arg_62 = i_10;
    acc_17 = arg_61;
    i_9 = arg_62;
    goto tailrec_263;
if_next_264:;
    return if_74;
}

struct IntList const* gen_1(int n_4) {
    struct IntList const* call_67 = go_(NULL, n_4);
    return call_67;
}

int fun_1(int x_22, int y_3) {
    return (x_22 + y_3);
}

int fun_8(void const* env_6, int arg_6, int arg_7) {
    int call_68 = fun_1(arg_6, arg_7);
    return call_68;
}

struct IntList const* fun_9(void const* env_7, int arg_8) {
    struct IntList const* call_69 = gen_1(arg_8);
    return call_69;
}

int milone_main(void) {
    struct IntList const* call_70 = gen_1(0);
    bool call_71 = isEmpty_(call_70);
    milone_assert(call_71, 55, 2);
    struct IntIntIntFun2 fun_17 = (struct IntIntIntFun2){.fun = fun_8, .env = NULL};
    struct IntList const* call_72 = gen_1(5);
    int call_73 = fold_(fun_17, 0, call_72);
    milone_assert((call_73 == ((((0 + 1) + 2) + 3) + 4)), 57, 2);
    struct IntIntListFun1 fun_18 = (struct IntIntListFun1){.fun = fun_9, .env = NULL};
    struct IntIntListFun1 gen_2 = fun_18;
    std_list_Program_testSkipWhile(gen_2);
    std_list_Program_testUnzip();
    return 0;
}
