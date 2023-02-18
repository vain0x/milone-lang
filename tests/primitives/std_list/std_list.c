#include "milone.h"

struct IntList;

struct IntStringFun1;

struct StringList;

struct IntIntListFun1;

struct IntList;

struct IntBoolFun1;

struct IntIntIntFun2;

struct String fun_8(void const* env_3, int arg_3);

struct StringList const* map_(struct IntStringFun1, struct IntList const*);

struct String MiloneStd_StdString_concat(struct String, struct StringList const*);

struct String debug_(struct IntList const* xs_66);

bool eq_(struct IntList const* expected_, struct IntList const* actual_);

bool fun_15(int arg_63);

bool fun_9(void const* env_4, int arg_4);

bool fun_1(int n_3);

bool fun_10(void const* env_5, int arg_5);

struct IntList const* takeWhile_(struct IntBoolFun1, struct IntList const*);

char std_list_Program_testTakeWhile(struct IntIntListFun1 gen_);

bool fun_16(int arg_64);

bool fun_11(void const* env_6, int arg_6);

bool fun_3(int n_4);

bool fun_12(void const* env_7, int arg_7);

struct IntList const* skipWhile_(struct IntBoolFun1, struct IntList const*);

char std_list_Program_testSkipWhile(struct IntIntListFun1 gen_1);

struct IntList const* go_(struct IntList const* acc_18, int i_8);

struct IntList const* gen_2(int n_5);

int fun_4(int x_22, int y_3);

int fun_13(void const* env_8, int arg_8, int arg_9);

struct IntList const* fun_14(void const* env_9, int arg_10);

bool isEmpty_(struct IntList const*);

int fold_(struct IntIntIntFun2, int, struct IntList const*);

int milone_main();

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

struct IntIntIntFun2 {
    int(*fun)(void const*, int, int);
    void const* env;
};

struct String fun_8(void const* env_3, int arg_3) {
    struct String call_52 = str_of_int64(arg_3);
    return call_52;
}

struct String debug_(struct IntList const* xs_66) {
    struct IntStringFun1 fun_20 = (struct IntStringFun1){.fun = fun_8, .env = NULL};
    struct StringList const* call_53 = map_(fun_20, xs_66);
    struct String call_54 = MiloneStd_StdString_concat((struct String){.str = ", ", .len = 2}, call_53);
    return call_54;
}

bool eq_(struct IntList const* expected_, struct IntList const* actual_) {
    struct String call_55 = debug_(expected_);
    struct String expected_1 = call_55;
    struct String call_56 = debug_(actual_);
    struct String actual_1 = call_56;
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

bool fun_15(int arg_63) {
    return true;
}

bool fun_9(void const* env_4, int arg_4) {
    bool call_57 = fun_15(arg_4);
    return call_57;
}

bool fun_1(int n_3) {
    return ((n_3 % 3) != 2);
}

bool fun_10(void const* env_5, int arg_5) {
    bool call_58 = fun_1(arg_5);
    return call_58;
}

char std_list_Program_testTakeWhile(struct IntIntListFun1 gen_) {
    struct IntList const* list_9 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_9))) = (struct IntList){.head = 2, .tail = NULL};
    struct IntList const* list_8 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_8))) = (struct IntList){.head = 1, .tail = list_9};
    struct IntList const* list_7 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_7))) = (struct IntList){.head = 0, .tail = list_8};
    struct IntBoolFun1 fun_21 = (struct IntBoolFun1){.fun = fun_9, .env = NULL};
    struct IntList const* app_8 = gen_.fun(gen_.env, 3);
    struct IntList const* call_59 = takeWhile_(fun_21, app_8);
    bool call_60 = eq_(list_7, call_59);
    milone_assert(call_60, 22, 2);
    struct IntList const* list_11 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_11))) = (struct IntList){.head = 1, .tail = NULL};
    struct IntList const* list_10 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_10))) = (struct IntList){.head = 0, .tail = list_11};
    struct IntBoolFun1 fun_22 = (struct IntBoolFun1){.fun = fun_10, .env = NULL};
    struct IntList const* app_9 = gen_.fun(gen_.env, 6);
    struct IntList const* call_61 = takeWhile_(fun_22, app_9);
    bool call_62 = eq_(list_10, call_61);
    milone_assert(call_62, 26, 2);
    return 0;
}

bool fun_16(int arg_64) {
    return true;
}

bool fun_11(void const* env_6, int arg_6) {
    bool call_63 = fun_16(arg_6);
    return call_63;
}

bool fun_3(int n_4) {
    return ((n_4 % 2) == 0);
}

bool fun_12(void const* env_7, int arg_7) {
    bool call_64 = fun_3(arg_7);
    return call_64;
}

char std_list_Program_testSkipWhile(struct IntIntListFun1 gen_1) {
    struct IntBoolFun1 fun_23 = (struct IntBoolFun1){.fun = fun_11, .env = NULL};
    struct IntList const* app_10 = gen_1.fun(gen_1.env, 5);
    struct IntList const* call_65 = skipWhile_(fun_23, app_10);
    bool call_66 = eq_(NULL, call_65);
    milone_assert(call_66, 31, 2);
    struct IntList const* list_15 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_15))) = (struct IntList){.head = 4, .tail = NULL};
    struct IntList const* list_14 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_14))) = (struct IntList){.head = 3, .tail = list_15};
    struct IntList const* list_13 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_13))) = (struct IntList){.head = 2, .tail = list_14};
    struct IntList const* list_12 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_12))) = (struct IntList){.head = 1, .tail = list_13};
    struct IntBoolFun1 fun_24 = (struct IntBoolFun1){.fun = fun_12, .env = NULL};
    struct IntList const* app_11 = gen_1.fun(gen_1.env, 5);
    struct IntList const* call_67 = skipWhile_(fun_24, app_11);
    bool call_68 = eq_(list_12, call_67);
    milone_assert(call_68, 33, 2);
    return 0;
}

struct IntList const* go_(struct IntList const* acc_18, int i_8) {
tailrec_263:;
    struct IntList const* if_74;
    if ((i_8 == 0)) {
        goto then_265;
    } else {
        goto else_266;
    }
then_265:;
    if_74 = acc_18;
    goto if_next_264;
else_266:;
    int i_9 = (i_8 - 1);
    struct IntList const* list_16 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_16))) = (struct IntList){.head = i_9, .tail = acc_18};
    struct IntList const* arg_65 = list_16;
    int arg_66 = i_9;
    acc_18 = arg_65;
    i_8 = arg_66;
    goto tailrec_263;
if_next_264:;
    return if_74;
}

struct IntList const* gen_2(int n_5) {
    struct IntList const* call_69 = go_(NULL, n_5);
    return call_69;
}

int fun_4(int x_22, int y_3) {
    return (x_22 + y_3);
}

int fun_13(void const* env_8, int arg_8, int arg_9) {
    int call_70 = fun_4(arg_8, arg_9);
    return call_70;
}

struct IntList const* fun_14(void const* env_9, int arg_10) {
    struct IntList const* call_71 = gen_2(arg_10);
    return call_71;
}

int milone_main() {
    struct IntList const* call_72 = gen_2(0);
    bool call_73 = isEmpty_(call_72);
    milone_assert(call_73, 51, 2);
    struct IntIntIntFun2 fun_25 = (struct IntIntIntFun2){.fun = fun_13, .env = NULL};
    struct IntList const* call_74 = gen_2(5);
    int call_75 = fold_(fun_25, 0, call_74);
    milone_assert((call_75 == ((((0 + 1) + 2) + 3) + 4)), 53, 2);
    struct IntIntListFun1 fun_26 = (struct IntIntListFun1){.fun = fun_14, .env = NULL};
    struct IntIntListFun1 gen_3 = fun_26;
    char call_76 = std_list_Program_testSkipWhile(gen_3);
    return 0;
}
