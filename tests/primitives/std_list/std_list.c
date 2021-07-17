#include "milone.h"

struct IntList;

struct IntStringFun1;

struct StringList;

struct IntIntListFun1;

struct IntBoolFun1;

struct IntList;

struct IntIntIntFun2;

struct String fun_6(void const* env_3, int arg_3);

struct StringList const* map_(struct IntStringFun1, struct IntList const*);

struct String MiloneStd_StdString_concat(struct String, struct StringList const*);

struct String debug_(struct IntList const* xs_63);

bool eq_(struct IntList const* expected_, struct IntList const* actual_);

bool fun_11(int arg_56);

bool fun_7(void const* env_4, int arg_4);

bool fun_1(int n_3);

bool fun_8(void const* env_5, int arg_5);

struct IntList const* skipWhile_(struct IntBoolFun1, struct IntList const*);

char std_list_Program_testSkipWhile(struct IntIntListFun1 gen_);

struct IntList const* go_(struct IntList const* acc_17, int i_9);

struct IntList const* gen_1(int n_4);

int fun_2(int x_22, int y_3);

int fun_9(void const* env_6, int arg_6, int arg_7);

struct IntList const* fun_10(void const* env_7, int arg_8);

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

struct IntBoolFun1 {
    bool(*fun)(void const*, int);
    void const* env;
};

struct IntList {
    int head;
    struct IntList const* tail;
};

struct IntIntIntFun2 {
    int(*fun)(void const*, int, int);
    void const* env;
};

struct String fun_6(void const* env_3, int arg_3) {
    struct String call_49 = str_of_int64(arg_3);
    return call_49;
}

struct String debug_(struct IntList const* xs_63) {
    struct IntStringFun1 fun_15 = (struct IntStringFun1){.fun = fun_6, .env = NULL};
    struct StringList const* call_50 = map_(fun_15, xs_63);
    struct String call_51 = MiloneStd_StdString_concat((struct String){.str = ", ", .len = 2}, call_50);
    return call_51;
}

bool eq_(struct IntList const* expected_, struct IntList const* actual_) {
    struct String call_52 = debug_(expected_);
    struct String expected_1 = call_52;
    struct String call_53 = debug_(actual_);
    struct String actual_1 = call_53;
    bool if_73;
    if ((str_compare(expected_1, actual_1) == 0)) {
        goto then_253;
    } else {
        goto else_254;
    }
then_253:;
    if_73 = true;
    goto if_next_252;
else_254:;
    printf("expected: %s\nactual: %s\n\n", str_to_c_str(expected_1), str_to_c_str(actual_1));
    if_73 = false;
    goto if_next_252;
if_next_252:;
    return if_73;
}

bool fun_11(int arg_56) {
    return true;
}

bool fun_7(void const* env_4, int arg_4) {
    bool call_54 = fun_11(arg_4);
    return call_54;
}

bool fun_1(int n_3) {
    return ((n_3 % 2) == 0);
}

bool fun_8(void const* env_5, int arg_5) {
    bool call_55 = fun_1(arg_5);
    return call_55;
}

char std_list_Program_testSkipWhile(struct IntIntListFun1 gen_) {
    struct IntBoolFun1 fun_16 = (struct IntBoolFun1){.fun = fun_7, .env = NULL};
    struct IntList const* app_7 = gen_.fun(gen_.env, 5);
    struct IntList const* call_56 = skipWhile_(fun_16, app_7);
    bool call_57 = eq_(NULL, call_56);
    milone_assert(call_57, 22, 2);
    struct IntList const* list_8 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_8))) = (struct IntList){.head = 4, .tail = NULL};
    struct IntList const* list_7 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_7))) = (struct IntList){.head = 3, .tail = list_8};
    struct IntList const* list_6 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_6))) = (struct IntList){.head = 2, .tail = list_7};
    struct IntList const* list_5 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_5))) = (struct IntList){.head = 1, .tail = list_6};
    struct IntBoolFun1 fun_17 = (struct IntBoolFun1){.fun = fun_8, .env = NULL};
    struct IntList const* app_8 = gen_.fun(gen_.env, 5);
    struct IntList const* call_58 = skipWhile_(fun_17, app_8);
    bool call_59 = eq_(list_5, call_58);
    milone_assert(call_59, 24, 2);
    return 0;
}

struct IntList const* go_(struct IntList const* acc_17, int i_9) {
tailrec_255:;
    struct IntList const* if_74;
    if ((i_9 == 0)) {
        goto then_257;
    } else {
        goto else_258;
    }
then_257:;
    if_74 = acc_17;
    goto if_next_256;
else_258:;
    int i_10 = (i_9 - 1);
    struct IntList const* list_9 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_9))) = (struct IntList){.head = i_10, .tail = acc_17};
    struct IntList const* arg_57 = list_9;
    int arg_58 = i_10;
    acc_17 = arg_57;
    i_9 = arg_58;
    goto tailrec_255;
if_next_256:;
    return if_74;
}

struct IntList const* gen_1(int n_4) {
    struct IntList const* call_60 = go_(NULL, n_4);
    return call_60;
}

int fun_2(int x_22, int y_3) {
    return (x_22 + y_3);
}

int fun_9(void const* env_6, int arg_6, int arg_7) {
    int call_61 = fun_2(arg_6, arg_7);
    return call_61;
}

struct IntList const* fun_10(void const* env_7, int arg_8) {
    struct IntList const* call_62 = gen_1(arg_8);
    return call_62;
}

int milone_main() {
    struct IntList const* call_63 = gen_1(0);
    bool call_64 = isEmpty_(call_63);
    milone_assert(call_64, 42, 2);
    struct IntIntIntFun2 fun_18 = (struct IntIntIntFun2){.fun = fun_9, .env = NULL};
    struct IntList const* call_65 = gen_1(5);
    int call_66 = fold_(fun_18, 0, call_65);
    milone_assert((call_66 == ((((0 + 1) + 2) + 3) + 4)), 44, 2);
    struct IntIntListFun1 fun_19 = (struct IntIntListFun1){.fun = fun_10, .env = NULL};
    struct IntIntListFun1 gen_2 = fun_19;
    char call_67 = std_list_Program_testSkipWhile(gen_2);
    return 0;
}
