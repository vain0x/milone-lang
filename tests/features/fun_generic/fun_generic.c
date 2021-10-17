#include "milone.h"

struct IntStringTuple2_;

struct StringIntTuple2_;

struct IntStringTuple2_StringIntTuple2_Fun1;

struct IntStringTuple2_List;

struct StringIntTuple2_List;

struct IntStringTuple2_List;

struct StringIntTuple2_List;

struct StringList;

struct IntList;

struct IntIntFun1;

struct IntList;

struct StringList;

struct IntListStringListTuple2_;

struct StringIntTuple2_List const* listMap_(struct IntStringTuple2_StringIntTuple2_Fun1 f_1, struct IntStringTuple2_List const* xs_3);

struct StringList const* listRev_(struct StringList const* xs_);

struct IntList const* listRev_1(struct IntList const* xs_);

struct StringIntTuple2_ flip_(struct IntStringTuple2_ arg_3);

struct IntStringTuple2_ flip_1(struct StringIntTuple2_ arg_4);

struct IntList const* listMap_1(struct IntIntFun1 f_1, struct IntList const* xs_3);

struct StringList const* id_(struct StringList const* x_1);

int id_1(int x_1);

struct IntList const* go_(struct IntList const* acc_, struct IntList const* xs_1);

struct StringList const* go_1(struct StringList const* acc_, struct StringList const* xs_1);

int f_(int x_3);

int fun_(void const* env_, int arg_);

int fun_1(void const* env_1, int arg_1);

struct StringIntTuple2_ fun_2(void const* env_2, struct IntStringTuple2_ arg_2);

int milone_main(void);

struct IntStringTuple2_ {
    int t0;
    struct String t1;
};

struct StringIntTuple2_ {
    struct String t0;
    int t1;
};

struct IntStringTuple2_StringIntTuple2_Fun1 {
    struct StringIntTuple2_(*fun)(void const*, struct IntStringTuple2_);
    void const* env;
};

struct IntStringTuple2_List {
    struct IntStringTuple2_ head;
    struct IntStringTuple2_List const* tail;
};

struct StringIntTuple2_List {
    struct StringIntTuple2_ head;
    struct StringIntTuple2_List const* tail;
};

struct IntIntFun1 {
    int(*fun)(void const*, int);
    void const* env;
};

struct IntList {
    int head;
    struct IntList const* tail;
};

struct StringList {
    struct String head;
    struct StringList const* tail;
};

struct IntListStringListTuple2_ {
    struct IntList const* t0;
    struct StringList const* t1;
};

struct StringIntTuple2_List const* listMap_(struct IntStringTuple2_StringIntTuple2_Fun1 f_1, struct IntStringTuple2_List const* xs_3) {
    struct IntStringTuple2_List const* xs_4;
    struct IntStringTuple2_ x_2;
    struct StringIntTuple2_List const* match_;
    if ((!((!(xs_3))))) goto next_2;
    match_ = NULL;
    goto end_match_1;
next_2:;
    if ((!(xs_3))) goto next_3;
    x_2 = xs_3->head;
    xs_4 = xs_3->tail;
    struct StringIntTuple2_ app_ = f_1.fun(f_1.env, x_2);
    struct StringIntTuple2_List const* call_ = listMap_(f_1, xs_4);
    struct StringIntTuple2_List const* list_ = milone_mem_alloc(1, sizeof(struct StringIntTuple2_List));
    (*(((struct StringIntTuple2_List*)list_))) = (struct StringIntTuple2_List){.head = app_, .tail = call_};
    match_ = list_;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return match_;
}

struct StringList const* listRev_(struct StringList const* xs_) {
    struct StringList const* call_1 = go_1(NULL, xs_);
    return call_1;
}

struct IntList const* listRev_1(struct IntList const* xs_) {
    struct IntList const* call_2 = go_(NULL, xs_);
    return call_2;
}

struct StringIntTuple2_ flip_(struct IntStringTuple2_ arg_3) {
    int x_4 = arg_3.t0;
    struct String y_ = arg_3.t1;
    struct StringIntTuple2_ StringIntTuple2_ = (struct StringIntTuple2_){.t0 = y_, .t1 = x_4};
    return StringIntTuple2_;
}

struct IntStringTuple2_ flip_1(struct StringIntTuple2_ arg_4) {
    struct String x_4 = arg_4.t0;
    int y_ = arg_4.t1;
    struct IntStringTuple2_ IntStringTuple2_ = (struct IntStringTuple2_){.t0 = y_, .t1 = x_4};
    return IntStringTuple2_;
}

struct IntList const* listMap_1(struct IntIntFun1 f_1, struct IntList const* xs_3) {
    struct IntList const* xs_4;
    int x_2;
    struct IntList const* match_1;
    if ((!((!(xs_3))))) goto next_5;
    match_1 = NULL;
    goto end_match_4;
next_5:;
    if ((!(xs_3))) goto next_6;
    x_2 = xs_3->head;
    xs_4 = xs_3->tail;
    int app_1 = f_1.fun(f_1.env, x_2);
    struct IntList const* call_3 = listMap_1(f_1, xs_4);
    struct IntList const* list_1 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_1))) = (struct IntList){.head = app_1, .tail = call_3};
    match_1 = list_1;
    goto end_match_4;
next_6:;
    exit(1);
end_match_4:;
    return match_1;
}

struct StringList const* id_(struct StringList const* x_1) {
    return x_1;
}

int id_1(int x_1) {
    return x_1;
}

struct IntList const* go_(struct IntList const* acc_, struct IntList const* xs_1) {
    struct IntList const* xs_2;
    int x_;
tailrec_7:;
    struct IntList const* match_2;
    if ((!((!(xs_1))))) goto next_9;
    match_2 = acc_;
    goto end_match_8;
next_9:;
    if ((!(xs_1))) goto next_10;
    x_ = xs_1->head;
    xs_2 = xs_1->tail;
    struct IntList const* list_2 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_2))) = (struct IntList){.head = x_, .tail = acc_};
    struct IntList const* arg_5 = list_2;
    struct IntList const* arg_6 = xs_2;
    acc_ = arg_5;
    xs_1 = arg_6;
    goto tailrec_7;
next_10:;
    exit(1);
end_match_8:;
    return match_2;
}

struct StringList const* go_1(struct StringList const* acc_, struct StringList const* xs_1) {
    struct StringList const* xs_2;
    struct String x_;
tailrec_11:;
    struct StringList const* match_3;
    if ((!((!(xs_1))))) goto next_13;
    match_3 = acc_;
    goto end_match_12;
next_13:;
    if ((!(xs_1))) goto next_14;
    x_ = xs_1->head;
    xs_2 = xs_1->tail;
    struct StringList const* list_3 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_3))) = (struct StringList){.head = x_, .tail = acc_};
    struct StringList const* arg_7 = list_3;
    struct StringList const* arg_8 = xs_2;
    acc_ = arg_7;
    xs_1 = arg_8;
    goto tailrec_11;
next_14:;
    exit(1);
end_match_12:;
    return match_3;
}

int f_(int x_3) {
    printf("%d\n", x_3);
    return (x_3 * x_3);
}

int fun_(void const* env_, int arg_) {
    int call_4 = f_(arg_);
    return call_4;
}

int fun_1(void const* env_1, int arg_1) {
    int call_5 = f_(arg_1);
    return call_5;
}

struct StringIntTuple2_ fun_2(void const* env_2, struct IntStringTuple2_ arg_2) {
    struct StringIntTuple2_ call_6 = flip_(arg_2);
    return call_6;
}

int milone_main(void) {
    int call_7 = id_1(42);
    int call_8 = id_1(1);
    struct StringList const* list_4 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_4))) = (struct StringList){.head = (struct String){.str = "A", .len = 1}, .tail = NULL};
    struct StringList const* call_9 = id_(list_4);
    struct IntIntFun1 fun_3 = (struct IntIntFun1){.fun = fun_, .env = NULL};
    struct IntIntFun1 fun_4 = (struct IntIntFun1){.fun = fun_1, .env = NULL};
    struct IntList const* list_7 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_7))) = (struct IntList){.head = 3, .tail = NULL};
    struct IntList const* list_6 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_6))) = (struct IntList){.head = 2, .tail = list_7};
    struct IntList const* list_5 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_5))) = (struct IntList){.head = 1, .tail = list_6};
    struct IntList const* call_10 = listMap_1(fun_4, list_5);
    struct IntList const* call_11 = listMap_1(fun_3, call_10);
    char match_4;
    struct IntStringTuple2_ IntStringTuple2_1 = (struct IntStringTuple2_){.t0 = 1, .t1 = (struct String){.str = "a", .len = 1}};
    struct StringIntTuple2_ call_12 = flip_(IntStringTuple2_1);
    struct IntStringTuple2_ call_13 = flip_1(call_12);
    if ((call_13.t0 != 1)) goto next_16;
    if ((str_compare(call_13.t1, (struct String){.str = "a", .len = 1}) != 0)) goto next_16;
    match_4 = 0;
    goto end_match_15;
next_16:;
    milone_assert(false, 38, 9);
    match_4 = 0;
    goto end_match_15;
next_17:;
end_match_15:;
    char match_5;
    struct IntList const* list_9 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_9))) = (struct IntList){.head = 2, .tail = NULL};
    struct IntList const* list_8 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_8))) = (struct IntList){.head = 1, .tail = list_9};
    struct IntList const* call_14 = listRev_1(list_8);
    struct StringList const* list_11 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_11))) = (struct StringList){.head = (struct String){.str = "b", .len = 1}, .tail = NULL};
    struct StringList const* list_10 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_10))) = (struct StringList){.head = (struct String){.str = "a", .len = 1}, .tail = list_11};
    struct StringList const* call_15 = listRev_(list_10);
    struct IntListStringListTuple2_ IntListStringListTuple2_ = (struct IntListStringListTuple2_){.t0 = call_14, .t1 = call_15};
    if ((!(IntListStringListTuple2_.t0))) goto next_19;
    if ((IntListStringListTuple2_.t0->head != 2)) goto next_19;
    if ((!(IntListStringListTuple2_.t0->tail))) goto next_19;
    if ((IntListStringListTuple2_.t0->tail->head != 1)) goto next_19;
    if ((!((!(IntListStringListTuple2_.t0->tail->tail))))) goto next_19;
    if ((!(IntListStringListTuple2_.t1))) goto next_19;
    if ((str_compare(IntListStringListTuple2_.t1->head, (struct String){.str = "b", .len = 1}) != 0)) goto next_19;
    if ((!(IntListStringListTuple2_.t1->tail))) goto next_19;
    if ((str_compare(IntListStringListTuple2_.t1->tail->head, (struct String){.str = "a", .len = 1}) != 0)) goto next_19;
    if ((!((!(IntListStringListTuple2_.t1->tail->tail))))) goto next_19;
    match_5 = 0;
    goto end_match_18;
next_19:;
    milone_assert(false, 42, 9);
    match_5 = 0;
    goto end_match_18;
next_20:;
end_match_18:;
    char match_6;
    struct IntStringTuple2_StringIntTuple2_Fun1 fun_5 = (struct IntStringTuple2_StringIntTuple2_Fun1){.fun = fun_2, .env = NULL};
    struct IntStringTuple2_ IntStringTuple2_2 = (struct IntStringTuple2_){.t0 = 1, .t1 = (struct String){.str = "a", .len = 1}};
    struct IntStringTuple2_ IntStringTuple2_3 = (struct IntStringTuple2_){.t0 = 2, .t1 = (struct String){.str = "b", .len = 1}};
    struct IntStringTuple2_List const* list_13 = milone_mem_alloc(1, sizeof(struct IntStringTuple2_List));
    (*(((struct IntStringTuple2_List*)list_13))) = (struct IntStringTuple2_List){.head = IntStringTuple2_3, .tail = NULL};
    struct IntStringTuple2_List const* list_12 = milone_mem_alloc(1, sizeof(struct IntStringTuple2_List));
    (*(((struct IntStringTuple2_List*)list_12))) = (struct IntStringTuple2_List){.head = IntStringTuple2_2, .tail = list_13};
    struct StringIntTuple2_List const* call_16 = listMap_(fun_5, list_12);
    if ((!(call_16))) goto next_22;
    if ((str_compare(call_16->head.t0, (struct String){.str = "a", .len = 1}) != 0)) goto next_22;
    if ((call_16->head.t1 != 1)) goto next_22;
    if ((!(call_16->tail))) goto next_22;
    if ((str_compare(call_16->tail->head.t0, (struct String){.str = "b", .len = 1}) != 0)) goto next_22;
    if ((call_16->tail->head.t1 != 2)) goto next_22;
    if ((!((!(call_16->tail->tail))))) goto next_22;
    match_6 = 0;
    goto end_match_21;
next_22:;
    milone_assert(false, 46, 9);
    match_6 = 0;
    goto end_match_21;
next_23:;
end_match_21:;
    return 0;
}
