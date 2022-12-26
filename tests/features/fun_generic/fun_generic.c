#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32StringTuple2_;

struct StringInt32Tuple2_;

typedef struct StringInt32Tuple2_(*VoidConstPtrInt32StringTuple2_StringInt32Tuple2_FunPtr2)(void const *, struct Int32StringTuple2_);

struct Int32StringTuple2_StringInt32Tuple2_Fun1;

struct Int32StringTuple2_Cons;

struct StringInt32Tuple2_Cons;

struct Int32StringTuple2_Cons;

struct StringInt32Tuple2_Cons;

struct StringCons;

struct Int32Cons;

typedef int32_t(*VoidConstPtrInt32Int32FunPtr2)(void const *, int32_t);

struct Int32Int32Fun1;

struct Int32Cons;

struct StringCons;

struct Int32ListStringListTuple2_;

struct StringInt32Tuple2_Cons const *fun_generic_fun_generic_Int32StringTuple2StringInt32Tuple2Fun1Int32StringTuple2ListStringInt32Tuple2ListFun2_listMap(struct Int32StringTuple2_StringInt32Tuple2_Fun1 f_, struct Int32StringTuple2_Cons const *xs_3);

struct StringCons const *fun_generic_fun_generic_StringListStringListFun1_listRev(struct StringCons const *xs_);

struct Int32Cons const *fun_generic_fun_generic_Int32ListInt32ListFun1_listRev(struct Int32Cons const *xs_);

int32_t fun_generic_fun_generic_f(int32_t x_3);

struct StringInt32Tuple2_ fun_generic_fun_generic_Int32StringTuple2StringInt32Tuple2Fun1_flip(struct Int32StringTuple2_ arg_3);

struct Int32StringTuple2_ fun_generic_fun_generic_StringInt32Tuple2Int32StringTuple2Fun1_flip(struct StringInt32Tuple2_ arg_4);

struct Int32Cons const *fun_generic_fun_generic_Int32Int32Fun1Int32ListInt32ListFun2_listMap(struct Int32Int32Fun1 f_, struct Int32Cons const *xs_3);

struct StringCons const *fun_generic_fun_generic_StringListStringListFun1_id(struct StringCons const *x_2);

int32_t fun_generic_fun_generic_Int32Int32Fun1_id(int32_t x_2);

struct Int32Cons const *fun_generic_fun_generic_listRev_Int32ListInt32ListInt32ListFun2_go(struct Int32Cons const *acc_, struct Int32Cons const *xs_1);

struct StringCons const *fun_generic_fun_generic_listRev_StringListStringListStringListFun2_go(struct StringCons const *acc_, struct StringCons const *xs_1);

int32_t fun_generic_fun_generic_eta2_main_f(void const *env_, int32_t arg_);

int32_t fun_generic_fun_generic_eta2_main_f_1(void const *env_1, int32_t arg_1);

struct StringInt32Tuple2_ fun_generic_fun_generic_eta2_main_flip(void const *env_2, struct Int32StringTuple2_ arg_2);

int main(int argc, char **argv);

struct Int32StringTuple2_ {
    int32_t t0;
    struct String t1;
};

struct StringInt32Tuple2_ {
    struct String t0;
    int32_t t1;
};

struct Int32StringTuple2_StringInt32Tuple2_Fun1 {
    VoidConstPtrInt32StringTuple2_StringInt32Tuple2_FunPtr2 fun;
    void const *env;
};

struct Int32StringTuple2_Cons {
    struct Int32StringTuple2_ head;
    struct Int32StringTuple2_Cons const *tail;
};

struct StringInt32Tuple2_Cons {
    struct StringInt32Tuple2_ head;
    struct StringInt32Tuple2_Cons const *tail;
};

struct Int32Int32Fun1 {
    VoidConstPtrInt32Int32FunPtr2 fun;
    void const *env;
};

struct Int32Cons {
    int32_t head;
    struct Int32Cons const *tail;
};

struct StringCons {
    struct String head;
    struct StringCons const *tail;
};

struct Int32ListStringListTuple2_ {
    struct Int32Cons const *t0;
    struct StringCons const *t1;
};

struct StringInt32Tuple2_Cons const *fun_generic_fun_generic_Int32StringTuple2StringInt32Tuple2Fun1Int32StringTuple2ListStringInt32Tuple2ListFun2_listMap(struct Int32StringTuple2_StringInt32Tuple2_Fun1 f_, struct Int32StringTuple2_Cons const *xs_3) {
    struct Int32StringTuple2_ x_1;
    struct Int32StringTuple2_Cons const *xs_4;
    struct StringInt32Tuple2_Cons const *match_;
    struct StringInt32Tuple2_Cons const *list_;
    struct StringInt32Tuple2_ app_;
    struct StringInt32Tuple2_Cons const *call_;
    if ((!((!(xs_3))))) goto next_2;
    match_ = NULL;
    goto end_match_1;
next_2:;
    if ((!(xs_3))) goto next_3;
    x_1 = xs_3->head;
    xs_4 = xs_3->tail;
    app_ = f_.fun(f_.env, x_1);
    call_ = fun_generic_fun_generic_Int32StringTuple2StringInt32Tuple2Fun1Int32StringTuple2ListStringInt32Tuple2ListFun2_listMap(f_, xs_4);
    list_ = ((struct StringInt32Tuple2_Cons const *)milone_region_alloc(1, sizeof(struct StringInt32Tuple2_Cons)));
    (*(((struct StringInt32Tuple2_Cons *)list_))) = (struct StringInt32Tuple2_Cons){.head = app_, .tail = call_};
    match_ = list_;
    goto end_match_1;
next_3:;
    milone_exhaust_error("fun_generic/fun_generic.milone", 14, 2);
end_match_1:;
    return match_;
}

struct StringCons const *fun_generic_fun_generic_StringListStringListFun1_listRev(struct StringCons const *xs_) {
    struct StringCons const *call_1;
    call_1 = fun_generic_fun_generic_listRev_StringListStringListStringListFun2_go(NULL, xs_);
    return call_1;
}

struct Int32Cons const *fun_generic_fun_generic_Int32ListInt32ListFun1_listRev(struct Int32Cons const *xs_) {
    struct Int32Cons const *call_2;
    call_2 = fun_generic_fun_generic_listRev_Int32ListInt32ListInt32ListFun2_go(NULL, xs_);
    return call_2;
}

int32_t fun_generic_fun_generic_f(int32_t x_3) {
    printf("%d\n", x_3);
    return (x_3 * x_3);
}

struct StringInt32Tuple2_ fun_generic_fun_generic_Int32StringTuple2StringInt32Tuple2Fun1_flip(struct Int32StringTuple2_ arg_3) {
    int32_t x_4;
    struct String y_;
    struct StringInt32Tuple2_ StringInt32Tuple2_;
    x_4 = arg_3.t0;
    y_ = arg_3.t1;
    StringInt32Tuple2_ = (struct StringInt32Tuple2_){.t0 = y_, .t1 = x_4};
    return StringInt32Tuple2_;
}

struct Int32StringTuple2_ fun_generic_fun_generic_StringInt32Tuple2Int32StringTuple2Fun1_flip(struct StringInt32Tuple2_ arg_4) {
    struct String x_4;
    int32_t y_;
    struct Int32StringTuple2_ Int32StringTuple2_;
    x_4 = arg_4.t0;
    y_ = arg_4.t1;
    Int32StringTuple2_ = (struct Int32StringTuple2_){.t0 = y_, .t1 = x_4};
    return Int32StringTuple2_;
}

struct Int32Cons const *fun_generic_fun_generic_Int32Int32Fun1Int32ListInt32ListFun2_listMap(struct Int32Int32Fun1 f_, struct Int32Cons const *xs_3) {
    int32_t x_1;
    struct Int32Cons const *xs_4;
    struct Int32Cons const *match_1;
    struct Int32Cons const *list_1;
    int32_t app_1;
    struct Int32Cons const *call_3;
    if ((!((!(xs_3))))) goto next_2;
    match_1 = NULL;
    goto end_match_1;
next_2:;
    if ((!(xs_3))) goto next_3;
    x_1 = xs_3->head;
    xs_4 = xs_3->tail;
    app_1 = f_.fun(f_.env, x_1);
    call_3 = fun_generic_fun_generic_Int32Int32Fun1Int32ListInt32ListFun2_listMap(f_, xs_4);
    list_1 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_1))) = (struct Int32Cons){.head = app_1, .tail = call_3};
    match_1 = list_1;
    goto end_match_1;
next_3:;
    milone_exhaust_error("fun_generic/fun_generic.milone", 14, 2);
end_match_1:;
    return match_1;
}

struct StringCons const *fun_generic_fun_generic_StringListStringListFun1_id(struct StringCons const *x_2) {
    return x_2;
}

int32_t fun_generic_fun_generic_Int32Int32Fun1_id(int32_t x_2) {
    return x_2;
}

struct Int32Cons const *fun_generic_fun_generic_listRev_Int32ListInt32ListInt32ListFun2_go(struct Int32Cons const *acc_, struct Int32Cons const *xs_1) {
    int32_t x_;
    struct Int32Cons const *xs_2;
    struct Int32Cons const *match_2;
    struct Int32Cons const *list_2;
    struct Int32Cons const *arg_5;
    struct Int32Cons const *arg_6;
tailrec_1:;
    if ((!((!(xs_1))))) goto next_3;
    match_2 = acc_;
    goto end_match_2;
next_3:;
    if ((!(xs_1))) goto next_4;
    x_ = xs_1->head;
    xs_2 = xs_1->tail;
    list_2 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_2))) = (struct Int32Cons){.head = x_, .tail = acc_};
    arg_5 = list_2;
    arg_6 = xs_2;
    acc_ = arg_5;
    xs_1 = arg_6;
    goto tailrec_1;
next_4:;
    milone_exhaust_error("fun_generic/fun_generic.milone", 6, 4);
end_match_2:;
    return match_2;
}

struct StringCons const *fun_generic_fun_generic_listRev_StringListStringListStringListFun2_go(struct StringCons const *acc_, struct StringCons const *xs_1) {
    struct String x_;
    struct StringCons const *xs_2;
    struct StringCons const *match_3;
    struct StringCons const *list_3;
    struct StringCons const *arg_7;
    struct StringCons const *arg_8;
tailrec_1:;
    if ((!((!(xs_1))))) goto next_3;
    match_3 = acc_;
    goto end_match_2;
next_3:;
    if ((!(xs_1))) goto next_4;
    x_ = xs_1->head;
    xs_2 = xs_1->tail;
    list_3 = ((struct StringCons const *)milone_region_alloc(1, sizeof(struct StringCons)));
    (*(((struct StringCons *)list_3))) = (struct StringCons){.head = x_, .tail = acc_};
    arg_7 = list_3;
    arg_8 = xs_2;
    acc_ = arg_7;
    xs_1 = arg_8;
    goto tailrec_1;
next_4:;
    milone_exhaust_error("fun_generic/fun_generic.milone", 6, 4);
end_match_2:;
    return match_3;
}

int32_t fun_generic_fun_generic_eta2_main_f(void const *env_, int32_t arg_) {
    int32_t call_4;
    call_4 = fun_generic_fun_generic_f(arg_);
    return call_4;
}

int32_t fun_generic_fun_generic_eta2_main_f_1(void const *env_1, int32_t arg_1) {
    int32_t call_5;
    call_5 = fun_generic_fun_generic_f(arg_1);
    return call_5;
}

struct StringInt32Tuple2_ fun_generic_fun_generic_eta2_main_flip(void const *env_2, struct Int32StringTuple2_ arg_2) {
    struct StringInt32Tuple2_ call_6;
    call_6 = fun_generic_fun_generic_Int32StringTuple2StringInt32Tuple2Fun1_flip(arg_2);
    return call_6;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    int32_t call_7;
    int32_t call_8;
    struct StringCons const *list_4;
    struct StringCons const *call_9;
    struct Int32Int32Fun1 fun_;
    struct Int32Int32Fun1 fun_1;
    struct Int32Cons const *list_5;
    struct Int32Cons const *list_6;
    struct Int32Cons const *list_7;
    struct Int32Cons const *call_10;
    struct Int32Cons const *call_11;
    char match_4;
    struct Int32StringTuple2_ Int32StringTuple2_1;
    struct StringInt32Tuple2_ call_12;
    struct Int32StringTuple2_ call_13;
    char match_5;
    struct Int32ListStringListTuple2_ Int32ListStringListTuple2_;
    struct Int32Cons const *list_8;
    struct Int32Cons const *list_9;
    struct Int32Cons const *call_14;
    struct StringCons const *list_10;
    struct StringCons const *list_11;
    struct StringCons const *call_15;
    char match_6;
    struct Int32StringTuple2_StringInt32Tuple2_Fun1 fun_2;
    struct Int32StringTuple2_Cons const *list_12;
    struct Int32StringTuple2_ Int32StringTuple2_2;
    struct Int32StringTuple2_Cons const *list_13;
    struct Int32StringTuple2_ Int32StringTuple2_3;
    struct StringInt32Tuple2_Cons const *call_16;
    call_7 = fun_generic_fun_generic_Int32Int32Fun1_id(42);
    call_8 = fun_generic_fun_generic_Int32Int32Fun1_id(1);
    list_4 = ((struct StringCons const *)milone_region_alloc(1, sizeof(struct StringCons)));
    (*(((struct StringCons *)list_4))) = (struct StringCons){.head = (struct String){.ptr = "A", .len = 1}, .tail = NULL};
    call_9 = fun_generic_fun_generic_StringListStringListFun1_id(list_4);
    fun_ = (struct Int32Int32Fun1){.fun = fun_generic_fun_generic_eta2_main_f, .env = NULL};
    fun_1 = (struct Int32Int32Fun1){.fun = fun_generic_fun_generic_eta2_main_f_1, .env = NULL};
    list_7 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_7))) = (struct Int32Cons){.head = 3, .tail = NULL};
    list_6 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_6))) = (struct Int32Cons){.head = 2, .tail = list_7};
    list_5 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_5))) = (struct Int32Cons){.head = 1, .tail = list_6};
    call_10 = fun_generic_fun_generic_Int32Int32Fun1Int32ListInt32ListFun2_listMap(fun_1, list_5);
    call_11 = fun_generic_fun_generic_Int32Int32Fun1Int32ListInt32ListFun2_listMap(fun_, call_10);
    Int32StringTuple2_1 = (struct Int32StringTuple2_){.t0 = 1, .t1 = (struct String){.ptr = "a", .len = 1}};
    call_12 = fun_generic_fun_generic_Int32StringTuple2StringInt32Tuple2Fun1_flip(Int32StringTuple2_1);
    call_13 = fun_generic_fun_generic_StringInt32Tuple2Int32StringTuple2Fun1_flip(call_12);
    if ((call_13.t0 != 1)) goto next_2;
    if ((string_compare(call_13.t1, (struct String){.ptr = "a", .len = 1}) != 0)) goto next_2;
    match_4 = 0;
    goto end_match_1;
next_2:;
    if (true) milone_assert_error("fun_generic/fun_generic.milone", 38, 9);
    match_4 = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    list_9 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_9))) = (struct Int32Cons){.head = 2, .tail = NULL};
    list_8 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_8))) = (struct Int32Cons){.head = 1, .tail = list_9};
    call_14 = fun_generic_fun_generic_Int32ListInt32ListFun1_listRev(list_8);
    list_11 = ((struct StringCons const *)milone_region_alloc(1, sizeof(struct StringCons)));
    (*(((struct StringCons *)list_11))) = (struct StringCons){.head = (struct String){.ptr = "b", .len = 1}, .tail = NULL};
    list_10 = ((struct StringCons const *)milone_region_alloc(1, sizeof(struct StringCons)));
    (*(((struct StringCons *)list_10))) = (struct StringCons){.head = (struct String){.ptr = "a", .len = 1}, .tail = list_11};
    call_15 = fun_generic_fun_generic_StringListStringListFun1_listRev(list_10);
    Int32ListStringListTuple2_ = (struct Int32ListStringListTuple2_){.t0 = call_14, .t1 = call_15};
    if ((!(Int32ListStringListTuple2_.t0))) goto next_5;
    if ((Int32ListStringListTuple2_.t0->head != 2)) goto next_5;
    if ((!(Int32ListStringListTuple2_.t0->tail))) goto next_5;
    if ((Int32ListStringListTuple2_.t0->tail->head != 1)) goto next_5;
    if ((!((!(Int32ListStringListTuple2_.t0->tail->tail))))) goto next_5;
    if ((!(Int32ListStringListTuple2_.t1))) goto next_5;
    if ((string_compare(Int32ListStringListTuple2_.t1->head, (struct String){.ptr = "b", .len = 1}) != 0)) goto next_5;
    if ((!(Int32ListStringListTuple2_.t1->tail))) goto next_5;
    if ((string_compare(Int32ListStringListTuple2_.t1->tail->head, (struct String){.ptr = "a", .len = 1}) != 0)) goto next_5;
    if ((!((!(Int32ListStringListTuple2_.t1->tail->tail))))) goto next_5;
    match_5 = 0;
    goto end_match_4;
next_5:;
    if (true) milone_assert_error("fun_generic/fun_generic.milone", 42, 9);
    match_5 = 0;
    goto end_match_4;
next_6:;
end_match_4:;
    fun_2 = (struct Int32StringTuple2_StringInt32Tuple2_Fun1){.fun = fun_generic_fun_generic_eta2_main_flip, .env = NULL};
    Int32StringTuple2_2 = (struct Int32StringTuple2_){.t0 = 1, .t1 = (struct String){.ptr = "a", .len = 1}};
    Int32StringTuple2_3 = (struct Int32StringTuple2_){.t0 = 2, .t1 = (struct String){.ptr = "b", .len = 1}};
    list_13 = ((struct Int32StringTuple2_Cons const *)milone_region_alloc(1, sizeof(struct Int32StringTuple2_Cons)));
    (*(((struct Int32StringTuple2_Cons *)list_13))) = (struct Int32StringTuple2_Cons){.head = Int32StringTuple2_3, .tail = NULL};
    list_12 = ((struct Int32StringTuple2_Cons const *)milone_region_alloc(1, sizeof(struct Int32StringTuple2_Cons)));
    (*(((struct Int32StringTuple2_Cons *)list_12))) = (struct Int32StringTuple2_Cons){.head = Int32StringTuple2_2, .tail = list_13};
    call_16 = fun_generic_fun_generic_Int32StringTuple2StringInt32Tuple2Fun1Int32StringTuple2ListStringInt32Tuple2ListFun2_listMap(fun_2, list_12);
    if ((!(call_16))) goto next_8;
    if ((string_compare(call_16->head.t0, (struct String){.ptr = "a", .len = 1}) != 0)) goto next_8;
    if ((call_16->head.t1 != 1)) goto next_8;
    if ((!(call_16->tail))) goto next_8;
    if ((string_compare(call_16->tail->head.t0, (struct String){.ptr = "b", .len = 1}) != 0)) goto next_8;
    if ((call_16->tail->head.t1 != 2)) goto next_8;
    if ((!((!(call_16->tail->tail))))) goto next_8;
    match_6 = 0;
    goto end_match_7;
next_8:;
    if (true) milone_assert_error("fun_generic/fun_generic.milone", 46, 9);
    match_6 = 0;
    goto end_match_7;
next_9:;
end_match_7:;
    return 0;
}
