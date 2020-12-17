#include "milone.h"

struct IntList;

struct IntList const* go_2(struct IntList const* acc_, struct IntList const* xs_1);

struct StringList;

struct StringList const* go_1(struct StringList const* acc_, struct StringList const* xs_1);

struct IntList const* listRev_2(struct IntList const* xs_);

struct StringList const* listRev_1(struct StringList const* xs_);

int id_2(int x_1);

struct StringList const* id_1(struct StringList const* x_1);

struct IntIntFun1;

struct IntList const* listMap_2(struct IntIntFun1 f_, struct IntList const* xs_3);

struct StringIntTuple2;

struct IntStringTuple2StringIntTuple2Fun1;

struct IntStringTuple2;

struct IntStringTuple2List;

struct StringIntTuple2List;

struct StringIntTuple2List const* listMap_1(struct IntStringTuple2StringIntTuple2Fun1 f_, struct IntStringTuple2List const* xs_3);

int f_1(int x_3);

int fun_(void const* env_, int arg_);

int fun_1(void const* env_1, int arg_1);

struct IntStringTuple2 flip_2(struct StringIntTuple2 arg_7);

struct StringIntTuple2 flip_1(struct IntStringTuple2 arg_8);

struct StringIntTuple2 fun_2(void const* env_2, struct IntStringTuple2 arg_2);

struct IntListStringListTuple2;

int main();

struct IntList {
    int head;
    struct IntList const* tail;
};

struct IntList const* go_2(struct IntList const* acc_, struct IntList const* xs_1) {
tailrec_1:;
    struct IntList const* match_;
    if ((!((!(xs_1))))) goto next_3;
    match_ = acc_;
    goto end_match_2;
next_3:;
    if ((!(xs_1))) goto next_4;
    int x_ = xs_1->head;
    struct IntList const* xs_2 = xs_1->tail;
    struct IntList const* list_ = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_))) = (struct IntList){.head = x_, .tail = acc_};
    struct IntList const* arg_3 = list_;
    struct IntList const* arg_4 = xs_2;
    acc_ = arg_3;
    xs_1 = arg_4;
    goto tailrec_1;
    match_ = NULL;
    goto end_match_2;
next_4:;
    exit(1);
end_match_2:;
    return match_;
}

struct StringList {
    struct String head;
    struct StringList const* tail;
};

struct StringList const* go_1(struct StringList const* acc_, struct StringList const* xs_1) {
tailrec_5:;
    struct StringList const* match_1;
    if ((!((!(xs_1))))) goto next_7;
    match_1 = acc_;
    goto end_match_6;
next_7:;
    if ((!(xs_1))) goto next_8;
    struct String x_ = xs_1->head;
    struct StringList const* xs_2 = xs_1->tail;
    struct StringList const* list_1 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_1))) = (struct StringList){.head = x_, .tail = acc_};
    struct StringList const* arg_5 = list_1;
    struct StringList const* arg_6 = xs_2;
    acc_ = arg_5;
    xs_1 = arg_6;
    goto tailrec_5;
    match_1 = NULL;
    goto end_match_6;
next_8:;
    exit(1);
end_match_6:;
    return match_1;
}

struct IntList const* listRev_2(struct IntList const* xs_) {
    struct IntList const* call_ = go_2(NULL, xs_);
    return call_;
}

struct StringList const* listRev_1(struct StringList const* xs_) {
    struct StringList const* call_1 = go_1(NULL, xs_);
    return call_1;
}

int id_2(int x_1) {
    return x_1;
}

struct StringList const* id_1(struct StringList const* x_1) {
    return x_1;
}

struct IntIntFun1 {
    int(*fun)(void const*, int);
    void const* env;
};

struct IntList const* listMap_2(struct IntIntFun1 f_, struct IntList const* xs_3) {
    struct IntList const* match_2;
    if ((!((!(xs_3))))) goto next_10;
    match_2 = NULL;
    goto end_match_9;
next_10:;
    if ((!(xs_3))) goto next_11;
    int x_2 = xs_3->head;
    struct IntList const* xs_4 = xs_3->tail;
    int app_ = f_.fun(f_.env, x_2);
    struct IntList const* call_2 = listMap_2(f_, xs_4);
    struct IntList const* list_2 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_2))) = (struct IntList){.head = app_, .tail = call_2};
    match_2 = list_2;
    goto end_match_9;
next_11:;
    exit(1);
end_match_9:;
    return match_2;
}

struct StringIntTuple2 {
    struct String t0;
    int t1;
};

struct IntStringTuple2StringIntTuple2Fun1 {
    struct StringIntTuple2(*fun)(void const*, struct IntStringTuple2);
    void const* env;
};

struct IntStringTuple2 {
    int t0;
    struct String t1;
};

struct IntStringTuple2List {
    struct IntStringTuple2 head;
    struct IntStringTuple2List const* tail;
};

struct StringIntTuple2List {
    struct StringIntTuple2 head;
    struct StringIntTuple2List const* tail;
};

struct StringIntTuple2List const* listMap_1(struct IntStringTuple2StringIntTuple2Fun1 f_, struct IntStringTuple2List const* xs_3) {
    struct StringIntTuple2List const* match_3;
    if ((!((!(xs_3))))) goto next_13;
    match_3 = NULL;
    goto end_match_12;
next_13:;
    if ((!(xs_3))) goto next_14;
    struct IntStringTuple2 x_2 = xs_3->head;
    struct IntStringTuple2List const* xs_4 = xs_3->tail;
    struct StringIntTuple2 app_1 = f_.fun(f_.env, x_2);
    struct StringIntTuple2List const* call_3 = listMap_1(f_, xs_4);
    struct StringIntTuple2List const* list_3 = milone_mem_alloc(1, sizeof(struct StringIntTuple2List));
    (*(((struct StringIntTuple2List*)list_3))) = (struct StringIntTuple2List){.head = app_1, .tail = call_3};
    match_3 = list_3;
    goto end_match_12;
next_14:;
    exit(1);
end_match_12:;
    return match_3;
}

int f_1(int x_3) {
    printf("%d\n", x_3);
    return (x_3 * x_3);
}

int fun_(void const* env_, int arg_) {
    int call_4 = f_1(arg_);
    return call_4;
}

int fun_1(void const* env_1, int arg_1) {
    int call_5 = f_1(arg_1);
    return call_5;
}

struct IntStringTuple2 flip_2(struct StringIntTuple2 arg_7) {
    struct String x_4 = arg_7.t0;
    int y_ = arg_7.t1;
    struct IntStringTuple2 tuple_;
    tuple_.t0 = y_;
    tuple_.t1 = x_4;
    return tuple_;
}

struct StringIntTuple2 flip_1(struct IntStringTuple2 arg_8) {
    int x_4 = arg_8.t0;
    struct String y_ = arg_8.t1;
    struct StringIntTuple2 tuple_1;
    tuple_1.t0 = y_;
    tuple_1.t1 = x_4;
    return tuple_1;
}

struct StringIntTuple2 fun_2(void const* env_2, struct IntStringTuple2 arg_2) {
    struct StringIntTuple2 call_6 = flip_1(arg_2);
    return call_6;
}

struct IntListStringListTuple2 {
    struct IntList const* t0;
    struct StringList const* t1;
};

int main() {
    int call_7 = id_2(42);
    int call_8 = id_2(1);
    struct StringList const* list_4 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_4))) = (struct StringList){.head = (struct String){.str = "A", .len = 1}, .tail = NULL};
    struct StringList const* call_9 = id_1(list_4);
    void const* box_ = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_))) = 0;
    void const* env_3 = box_;
    struct IntIntFun1 fun_3 = (struct IntIntFun1){.fun = fun_, .env = env_3};
    void const* box_1 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_1))) = 0;
    void const* env_4 = box_1;
    struct IntIntFun1 fun_4 = (struct IntIntFun1){.fun = fun_1, .env = env_4};
    struct IntList const* list_7 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_7))) = (struct IntList){.head = 3, .tail = NULL};
    struct IntList const* list_6 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_6))) = (struct IntList){.head = 2, .tail = list_7};
    struct IntList const* list_5 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_5))) = (struct IntList){.head = 1, .tail = list_6};
    struct IntList const* call_10 = listMap_2(fun_4, list_5);
    struct IntList const* call_11 = listMap_2(fun_3, call_10);
    int match_4;
    struct IntStringTuple2 tuple_2;
    tuple_2.t0 = 1;
    tuple_2.t1 = (struct String){.str = "a", .len = 1};
    struct StringIntTuple2 call_12 = flip_1(tuple_2);
    struct IntStringTuple2 call_13 = flip_2(call_12);
    if ((call_13.t0 != 1)) goto next_16;
    if ((str_cmp(call_13.t1, (struct String){.str = "a", .len = 1}) != 0)) goto next_16;
    match_4 = 0;
    goto end_match_15;
next_16:;
    milone_assert(false, 37, 9);
    match_4 = 0;
    goto end_match_15;
next_17:;
end_match_15:;
    int match_5;
    struct IntList const* list_9 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_9))) = (struct IntList){.head = 2, .tail = NULL};
    struct IntList const* list_8 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_8))) = (struct IntList){.head = 1, .tail = list_9};
    struct IntList const* call_14 = listRev_2(list_8);
    struct StringList const* list_11 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_11))) = (struct StringList){.head = (struct String){.str = "b", .len = 1}, .tail = NULL};
    struct StringList const* list_10 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_10))) = (struct StringList){.head = (struct String){.str = "a", .len = 1}, .tail = list_11};
    struct StringList const* call_15 = listRev_1(list_10);
    struct IntListStringListTuple2 tuple_3;
    tuple_3.t0 = call_14;
    tuple_3.t1 = call_15;
    if ((!(tuple_3.t0))) goto next_19;
    if ((tuple_3.t0->head != 2)) goto next_19;
    if ((!(tuple_3.t0->tail))) goto next_19;
    if ((tuple_3.t0->tail->head != 1)) goto next_19;
    if ((!((!(tuple_3.t0->tail->tail))))) goto next_19;
    if ((!(tuple_3.t1))) goto next_19;
    if ((str_cmp(tuple_3.t1->head, (struct String){.str = "b", .len = 1}) != 0)) goto next_19;
    if ((!(tuple_3.t1->tail))) goto next_19;
    if ((str_cmp(tuple_3.t1->tail->head, (struct String){.str = "a", .len = 1}) != 0)) goto next_19;
    if ((!((!(tuple_3.t1->tail->tail))))) goto next_19;
    match_5 = 0;
    goto end_match_18;
next_19:;
    milone_assert(false, 41, 9);
    match_5 = 0;
    goto end_match_18;
next_20:;
end_match_18:;
    int match_6;
    void const* box_2 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_2))) = 0;
    void const* env_5 = box_2;
    struct IntStringTuple2StringIntTuple2Fun1 fun_5 = (struct IntStringTuple2StringIntTuple2Fun1){.fun = fun_2, .env = env_5};
    struct IntStringTuple2 tuple_4;
    tuple_4.t0 = 1;
    tuple_4.t1 = (struct String){.str = "a", .len = 1};
    struct IntStringTuple2 tuple_5;
    tuple_5.t0 = 2;
    tuple_5.t1 = (struct String){.str = "b", .len = 1};
    struct IntStringTuple2List const* list_13 = milone_mem_alloc(1, sizeof(struct IntStringTuple2List));
    (*(((struct IntStringTuple2List*)list_13))) = (struct IntStringTuple2List){.head = tuple_5, .tail = NULL};
    struct IntStringTuple2List const* list_12 = milone_mem_alloc(1, sizeof(struct IntStringTuple2List));
    (*(((struct IntStringTuple2List*)list_12))) = (struct IntStringTuple2List){.head = tuple_4, .tail = list_13};
    struct StringIntTuple2List const* call_16 = listMap_1(fun_5, list_12);
    if ((!(call_16))) goto next_22;
    if ((str_cmp(call_16->head.t0, (struct String){.str = "a", .len = 1}) != 0)) goto next_22;
    if ((call_16->head.t1 != 1)) goto next_22;
    if ((!(call_16->tail))) goto next_22;
    if ((str_cmp(call_16->tail->head.t0, (struct String){.str = "b", .len = 1}) != 0)) goto next_22;
    if ((call_16->tail->head.t1 != 2)) goto next_22;
    if ((!((!(call_16->tail->tail))))) goto next_22;
    match_6 = 0;
    goto end_match_21;
next_22:;
    milone_assert(false, 45, 9);
    match_6 = 0;
    goto end_match_21;
next_23:;
end_match_21:;
    return 0;
}
