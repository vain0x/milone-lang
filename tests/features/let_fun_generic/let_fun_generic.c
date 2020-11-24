#include "milone.h"

struct IntList;

struct IntList* go_2(struct IntList* acc_, struct IntList* xs_1);

struct StringList;

struct StringList* go_1(struct StringList* acc_, struct StringList* xs_1);

struct IntList* listRev_2(struct IntList* xs_);

struct StringList* listRev_1(struct StringList* xs_);

int id_2(int x_1);

struct StringList* id_1(struct StringList* x_1);

struct IntIntFun1;

struct IntList* listMap_2(struct IntIntFun1 f_, struct IntList* xs_3);

struct StringIntTuple2;

struct IntStringTuple2StringIntTuple2Fun1;

struct IntStringTuple2;

struct IntStringTuple2List;

struct StringIntTuple2List;

struct StringIntTuple2List* listMap_1(struct IntStringTuple2StringIntTuple2Fun1 f_, struct IntStringTuple2List* xs_3);

int f_1(int x_3);

int fun_(void* env_, int arg_);

int fun_1(void* env_1, int arg_1);

struct IntStringTuple2 flip_2(struct StringIntTuple2 arg_7);

struct StringIntTuple2 flip_1(struct IntStringTuple2 arg_8);

struct StringIntTuple2 fun_2(void* env_2, struct IntStringTuple2 arg_2);

struct IntListStringListTuple2;

int main();

struct IntList {
    int head;
    struct IntList* tail;
};

struct IntList* go_2(struct IntList* acc_, struct IntList* xs_1) {
tailrec_1:;
    struct IntList* match_;
    if ((!((!(xs_1))))) goto next_3;
    match_ = acc_;
    goto end_match_2;
next_3:;
    if ((!(xs_1))) goto next_4;
    int x_ = xs_1->head;
    struct IntList* xs_2 = xs_1->tail;
    struct IntList* list_ = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_->head = x_;
    list_->tail = acc_;
    struct IntList* arg_3 = list_;
    struct IntList* arg_4 = xs_2;
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
    struct StringList* tail;
};

struct StringList* go_1(struct StringList* acc_, struct StringList* xs_1) {
tailrec_5:;
    struct StringList* match_1;
    if ((!((!(xs_1))))) goto next_7;
    match_1 = acc_;
    goto end_match_6;
next_7:;
    if ((!(xs_1))) goto next_8;
    struct String x_ = xs_1->head;
    struct StringList* xs_2 = xs_1->tail;
    struct StringList* list_1 = (struct StringList*)milone_mem_alloc(1, sizeof(struct StringList));
    list_1->head = x_;
    list_1->tail = acc_;
    struct StringList* arg_5 = list_1;
    struct StringList* arg_6 = xs_2;
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

struct IntList* listRev_2(struct IntList* xs_) {
    struct IntList* call_ = go_2(NULL, xs_);
    return call_;
}

struct StringList* listRev_1(struct StringList* xs_) {
    struct StringList* call_1 = go_1(NULL, xs_);
    return call_1;
}

int id_2(int x_1) {
    return x_1;
}

struct StringList* id_1(struct StringList* x_1) {
    return x_1;
}

struct IntIntFun1 {
    int(*fun)(void*, int);
    void* env;
};

struct IntList* listMap_2(struct IntIntFun1 f_, struct IntList* xs_3) {
    struct IntList* match_2;
    if ((!((!(xs_3))))) goto next_10;
    match_2 = NULL;
    goto end_match_9;
next_10:;
    if ((!(xs_3))) goto next_11;
    int x_2 = xs_3->head;
    struct IntList* xs_4 = xs_3->tail;
    int app_ = f_.fun(f_.env, x_2);
    struct IntList* call_2 = listMap_2(f_, xs_4);
    struct IntList* list_2 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_2->head = app_;
    list_2->tail = call_2;
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
    struct StringIntTuple2(*fun)(void*, struct IntStringTuple2);
    void* env;
};

struct IntStringTuple2 {
    int t0;
    struct String t1;
};

struct IntStringTuple2List {
    struct IntStringTuple2 head;
    struct IntStringTuple2List* tail;
};

struct StringIntTuple2List {
    struct StringIntTuple2 head;
    struct StringIntTuple2List* tail;
};

struct StringIntTuple2List* listMap_1(struct IntStringTuple2StringIntTuple2Fun1 f_, struct IntStringTuple2List* xs_3) {
    struct StringIntTuple2List* match_3;
    if ((!((!(xs_3))))) goto next_13;
    match_3 = NULL;
    goto end_match_12;
next_13:;
    if ((!(xs_3))) goto next_14;
    struct IntStringTuple2 x_2 = xs_3->head;
    struct IntStringTuple2List* xs_4 = xs_3->tail;
    struct StringIntTuple2 app_1 = f_.fun(f_.env, x_2);
    struct StringIntTuple2List* call_3 = listMap_1(f_, xs_4);
    struct StringIntTuple2List* list_3 = (struct StringIntTuple2List*)milone_mem_alloc(1, sizeof(struct StringIntTuple2List));
    list_3->head = app_1;
    list_3->tail = call_3;
    match_3 = list_3;
    goto end_match_12;
next_14:;
    exit(1);
end_match_12:;
    return match_3;
}

int f_1(int x_3) {
    printf("%d\n", x_3);
    int call_4 = 0;
    return (x_3 * x_3);
}

int fun_(void* env_, int arg_) {
    int call_5 = f_1(arg_);
    return call_5;
}

int fun_1(void* env_1, int arg_1) {
    int call_6 = f_1(arg_1);
    return call_6;
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

struct StringIntTuple2 fun_2(void* env_2, struct IntStringTuple2 arg_2) {
    struct StringIntTuple2 call_7 = flip_1(arg_2);
    return call_7;
}

struct IntListStringListTuple2 {
    struct IntList* t0;
    struct StringList* t1;
};

int main() {
    int call_8 = id_2(42);
    int call_9 = id_2(1);
    struct StringList* list_4 = (struct StringList*)milone_mem_alloc(1, sizeof(struct StringList));
    list_4->head = (struct String){.str = "A", .len = 1};
    list_4->tail = NULL;
    struct StringList* call_10 = id_1(list_4);
    void* box_ = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_))) = 0;
    void* env_3 = box_;
    struct IntIntFun1 fun_3 = (struct IntIntFun1){.fun = fun_, .env = env_3};
    void* box_1 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_1))) = 0;
    void* env_4 = box_1;
    struct IntIntFun1 fun_4 = (struct IntIntFun1){.fun = fun_1, .env = env_4};
    struct IntList* list_7 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_7->head = 3;
    list_7->tail = NULL;
    struct IntList* list_6 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_6->head = 2;
    list_6->tail = list_7;
    struct IntList* list_5 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_5->head = 1;
    list_5->tail = list_6;
    struct IntList* call_11 = listMap_2(fun_4, list_5);
    struct IntList* call_12 = listMap_2(fun_3, call_11);
    int match_4;
    struct IntStringTuple2 tuple_2;
    tuple_2.t0 = 1;
    tuple_2.t1 = (struct String){.str = "a", .len = 1};
    struct StringIntTuple2 call_13 = flip_1(tuple_2);
    struct IntStringTuple2 call_14 = flip_2(call_13);
    if ((call_14.t0 != 1)) goto next_16;
    if ((str_cmp(call_14.t1, (struct String){.str = "a", .len = 1}) != 0)) goto next_16;
    match_4 = 0;
    goto end_match_15;
next_16:;
    milone_assert(0, 35, 9);
    match_4 = 0;
    goto end_match_15;
next_17:;
end_match_15:;
    int match_5;
    struct IntList* list_9 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_9->head = 2;
    list_9->tail = NULL;
    struct IntList* list_8 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_8->head = 1;
    list_8->tail = list_9;
    struct IntList* call_15 = listRev_2(list_8);
    struct StringList* list_11 = (struct StringList*)milone_mem_alloc(1, sizeof(struct StringList));
    list_11->head = (struct String){.str = "b", .len = 1};
    list_11->tail = NULL;
    struct StringList* list_10 = (struct StringList*)milone_mem_alloc(1, sizeof(struct StringList));
    list_10->head = (struct String){.str = "a", .len = 1};
    list_10->tail = list_11;
    struct StringList* call_16 = listRev_1(list_10);
    struct IntListStringListTuple2 tuple_3;
    tuple_3.t0 = call_15;
    tuple_3.t1 = call_16;
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
    milone_assert(0, 39, 9);
    match_5 = 0;
    goto end_match_18;
next_20:;
end_match_18:;
    int match_6;
    void* box_2 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_2))) = 0;
    void* env_5 = box_2;
    struct IntStringTuple2StringIntTuple2Fun1 fun_5 = (struct IntStringTuple2StringIntTuple2Fun1){.fun = fun_2, .env = env_5};
    struct IntStringTuple2 tuple_4;
    tuple_4.t0 = 1;
    tuple_4.t1 = (struct String){.str = "a", .len = 1};
    struct IntStringTuple2 tuple_5;
    tuple_5.t0 = 2;
    tuple_5.t1 = (struct String){.str = "b", .len = 1};
    struct IntStringTuple2List* list_13 = (struct IntStringTuple2List*)milone_mem_alloc(1, sizeof(struct IntStringTuple2List));
    list_13->head = tuple_5;
    list_13->tail = NULL;
    struct IntStringTuple2List* list_12 = (struct IntStringTuple2List*)milone_mem_alloc(1, sizeof(struct IntStringTuple2List));
    list_12->head = tuple_4;
    list_12->tail = list_13;
    struct StringIntTuple2List* call_17 = listMap_1(fun_5, list_12);
    if ((!(call_17))) goto next_22;
    if ((str_cmp(call_17->head.t0, (struct String){.str = "a", .len = 1}) != 0)) goto next_22;
    if ((call_17->head.t1 != 1)) goto next_22;
    if ((!(call_17->tail))) goto next_22;
    if ((str_cmp(call_17->tail->head.t0, (struct String){.str = "b", .len = 1}) != 0)) goto next_22;
    if ((call_17->tail->head.t1 != 2)) goto next_22;
    if ((!((!(call_17->tail->tail))))) goto next_22;
    match_6 = 0;
    goto end_match_21;
next_22:;
    milone_assert(0, 43, 9);
    match_6 = 0;
    goto end_match_21;
next_23:;
end_match_21:;
    return 0;
}
