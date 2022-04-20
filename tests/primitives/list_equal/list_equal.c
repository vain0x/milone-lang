#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32StringTuple2_;

struct Int32Cons;

typedef bool(*VoidConstPtrInt32Int32BoolFunPtr3)(void const *, int32_t, int32_t);

struct Int32Int32BoolFun2;

struct Int32StringTuple2_Cons;

typedef bool(*VoidConstPtrInt32StringTuple2_Int32StringTuple2_BoolFunPtr3)(void const *, struct Int32StringTuple2_, struct Int32StringTuple2_);

struct Int32StringTuple2_Int32StringTuple2_BoolFun2;

struct Int32Cons;

struct Int32StringTuple2_Cons;

bool MiloneDerive_TupleEqual_tuple2Equal(struct Int32StringTuple2_ l_2, struct Int32StringTuple2_ r_2);

bool MiloneDerive_ListEqual_eta3_prim(void const *env_, int32_t arg_, int32_t arg_1);

bool Std_Equal_Int32Int32BoolFun2Int32ListInt32ListBoolFun3_genericListEqual(struct Int32Int32BoolFun2, struct Int32Cons const *, struct Int32Cons const *);

bool MiloneDerive_ListEqual_listEqual(struct Int32Cons const *l_, struct Int32Cons const *r_);

bool MiloneDerive_TupleEqual_tuple2Equal(struct Int32StringTuple2_, struct Int32StringTuple2_);

bool MiloneDerive_ListEqual_eta3_listEqual_tuple2Equal(void const *env_1, struct Int32StringTuple2_ arg_2, struct Int32StringTuple2_ arg_3);

bool Std_Equal_Int32StringTuple2Int32StringTuple2BoolFun2Int32StringTuple2ListInt32StringTuple2ListBoolFun3_genericListEqual(struct Int32StringTuple2_Int32StringTuple2_BoolFun2, struct Int32StringTuple2_Cons const *, struct Int32StringTuple2_Cons const *);

bool MiloneDerive_ListEqual_listEqual_1(struct Int32StringTuple2_Cons const *l_1, struct Int32StringTuple2_Cons const *r_1);

bool MiloneDerive_ListEqual_listEqual(struct Int32Cons const *, struct Int32Cons const *);

void list_equal_list_equal_testIntList(void);

bool MiloneDerive_ListEqual_listEqual_1(struct Int32StringTuple2_Cons const *, struct Int32StringTuple2_Cons const *);

void list_equal_list_equal_testPairList(void);

int main(int argc, char **argv);

struct Int32StringTuple2_ {
    int32_t t0;
    struct String t1;
};

struct Int32Int32BoolFun2 {
    VoidConstPtrInt32Int32BoolFunPtr3 fun;
    void const *env;
};

struct Int32StringTuple2_Int32StringTuple2_BoolFun2 {
    VoidConstPtrInt32StringTuple2_Int32StringTuple2_BoolFunPtr3 fun;
    void const *env;
};

struct Int32Cons {
    int32_t head;
    struct Int32Cons const *tail;
};

struct Int32StringTuple2_Cons {
    struct Int32StringTuple2_ head;
    struct Int32StringTuple2_Cons const *tail;
};

bool MiloneDerive_TupleEqual_tuple2Equal(struct Int32StringTuple2_ l_2, struct Int32StringTuple2_ r_2) {
    int32_t l_3;
    int32_t r_3;
    struct String l_4;
    struct String r_4;
    l_3 = l_2.t0;
    l_4 = l_2.t1;
    r_3 = r_2.t0;
    r_4 = r_2.t1;
    return ((l_3 == r_3) & (string_compare(l_4, r_4) == 0));
}

bool MiloneDerive_ListEqual_eta3_prim(void const *env_, int32_t arg_, int32_t arg_1) {
    return (arg_ == arg_1);
}

bool MiloneDerive_ListEqual_listEqual(struct Int32Cons const *l_, struct Int32Cons const *r_) {
    struct Int32Int32BoolFun2 fun_;
    bool call_;
    fun_ = (struct Int32Int32BoolFun2){.fun = MiloneDerive_ListEqual_eta3_prim, .env = NULL};
    call_ = Std_Equal_Int32Int32BoolFun2Int32ListInt32ListBoolFun3_genericListEqual(fun_, l_, r_);
    return call_;
}

bool MiloneDerive_ListEqual_eta3_listEqual_tuple2Equal(void const *env_1, struct Int32StringTuple2_ arg_2, struct Int32StringTuple2_ arg_3) {
    bool call_1;
    call_1 = MiloneDerive_TupleEqual_tuple2Equal(arg_2, arg_3);
    return call_1;
}

bool MiloneDerive_ListEqual_listEqual_1(struct Int32StringTuple2_Cons const *l_1, struct Int32StringTuple2_Cons const *r_1) {
    struct Int32StringTuple2_Int32StringTuple2_BoolFun2 fun_1;
    bool call_2;
    fun_1 = (struct Int32StringTuple2_Int32StringTuple2_BoolFun2){.fun = MiloneDerive_ListEqual_eta3_listEqual_tuple2Equal, .env = NULL};
    call_2 = Std_Equal_Int32StringTuple2Int32StringTuple2BoolFun2Int32StringTuple2ListInt32StringTuple2ListBoolFun3_genericListEqual(fun_1, l_1, r_1);
    return call_2;
}

void list_equal_list_equal_testIntList(void) {
    struct Int32Cons const *nil_;
    struct Int32Cons const *list_;
    struct Int32Cons const *list_1;
    struct Int32Cons const *list_2;
    struct Int32Cons const *list_3;
    struct Int32Cons const *list_4;
    struct Int32Cons const *list_5;
    struct Int32Cons const *list_6;
    struct Int32Cons const *list_7;
    bool call_3;
    bool call_4;
    struct Int32Cons const *list_8;
    bool call_5;
    struct Int32Cons const *list_9;
    struct Int32Cons const *list_10;
    struct Int32Cons const *list_11;
    struct Int32Cons const *list_12;
    struct Int32Cons const *list_13;
    struct Int32Cons const *list_14;
    struct Int32Cons const *list_15;
    struct Int32Cons const *list_16;
    bool call_6;
    struct Int32Cons const *list_17;
    struct Int32Cons const *list_18;
    struct Int32Cons const *list_19;
    struct Int32Cons const *list_20;
    struct Int32Cons const *list_21;
    struct Int32Cons const *list_22;
    struct Int32Cons const *list_23;
    bool call_7;
    struct Int32Cons const *list_24;
    struct Int32Cons const *list_25;
    struct Int32Cons const *list_26;
    struct Int32Cons const *list_27;
    struct Int32Cons const *list_28;
    struct Int32Cons const *list_29;
    struct Int32Cons const *list_30;
    bool call_8;
    list_3 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_3))) = (struct Int32Cons){.head = 5, .tail = NULL};
    list_2 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_2))) = (struct Int32Cons){.head = 3, .tail = list_3};
    list_1 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_1))) = (struct Int32Cons){.head = 2, .tail = list_2};
    list_ = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_))) = (struct Int32Cons){.head = 2, .tail = list_1};
    list_7 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_7))) = (struct Int32Cons){.head = 5, .tail = NULL};
    list_6 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_6))) = (struct Int32Cons){.head = 3, .tail = list_7};
    list_5 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_5))) = (struct Int32Cons){.head = 2, .tail = list_6};
    list_4 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_4))) = (struct Int32Cons){.head = 2, .tail = list_5};
    call_3 = MiloneDerive_ListEqual_listEqual(list_, list_4);
    if ((!(call_3))) milone_assert_error("list_equal/list_equal.milone", 8, 2);
    nil_ = NULL;
    call_4 = MiloneDerive_ListEqual_listEqual(nil_, NULL);
    if ((!(call_4))) milone_assert_error("list_equal/list_equal.milone", 11, 2);
    list_8 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_8))) = (struct Int32Cons){.head = 0, .tail = NULL};
    call_5 = MiloneDerive_ListEqual_listEqual(nil_, list_8);
    if (call_5) milone_assert_error("list_equal/list_equal.milone", 12, 2);
    list_12 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_12))) = (struct Int32Cons){.head = 5, .tail = NULL};
    list_11 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_11))) = (struct Int32Cons){.head = 3, .tail = list_12};
    list_10 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_10))) = (struct Int32Cons){.head = 2, .tail = list_11};
    list_9 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_9))) = (struct Int32Cons){.head = 2, .tail = list_10};
    list_16 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_16))) = (struct Int32Cons){.head = 5, .tail = NULL};
    list_15 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_15))) = (struct Int32Cons){.head = 2, .tail = list_16};
    list_14 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_14))) = (struct Int32Cons){.head = 3, .tail = list_15};
    list_13 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_13))) = (struct Int32Cons){.head = 2, .tail = list_14};
    call_6 = MiloneDerive_ListEqual_listEqual(list_9, list_13);
    if (call_6) milone_assert_error("list_equal/list_equal.milone", 15, 2);
    list_19 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_19))) = (struct Int32Cons){.head = 3, .tail = NULL};
    list_18 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_18))) = (struct Int32Cons){.head = 2, .tail = list_19};
    list_17 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_17))) = (struct Int32Cons){.head = 2, .tail = list_18};
    list_23 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_23))) = (struct Int32Cons){.head = 5, .tail = NULL};
    list_22 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_22))) = (struct Int32Cons){.head = 3, .tail = list_23};
    list_21 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_21))) = (struct Int32Cons){.head = 2, .tail = list_22};
    list_20 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_20))) = (struct Int32Cons){.head = 2, .tail = list_21};
    call_7 = MiloneDerive_ListEqual_listEqual(list_17, list_20);
    if (call_7) milone_assert_error("list_equal/list_equal.milone", 17, 2);
    list_26 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_26))) = (struct Int32Cons){.head = 5, .tail = NULL};
    list_25 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_25))) = (struct Int32Cons){.head = 3, .tail = list_26};
    list_24 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_24))) = (struct Int32Cons){.head = 2, .tail = list_25};
    list_30 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_30))) = (struct Int32Cons){.head = 5, .tail = NULL};
    list_29 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_29))) = (struct Int32Cons){.head = 3, .tail = list_30};
    list_28 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_28))) = (struct Int32Cons){.head = 2, .tail = list_29};
    list_27 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_27))) = (struct Int32Cons){.head = 2, .tail = list_28};
    call_8 = MiloneDerive_ListEqual_listEqual(list_24, list_27);
    if (call_8) milone_assert_error("list_equal/list_equal.milone", 19, 2);
    return;
}

void list_equal_list_equal_testPairList(void) {
    struct Int32StringTuple2_Cons const *list_31;
    struct Int32StringTuple2_ Int32StringTuple2_;
    struct Int32StringTuple2_Cons const *list_32;
    struct Int32StringTuple2_ Int32StringTuple2_1;
    struct Int32StringTuple2_Cons const *list_33;
    struct Int32StringTuple2_ Int32StringTuple2_2;
    struct Int32StringTuple2_Cons const *list_34;
    struct Int32StringTuple2_ Int32StringTuple2_3;
    bool call_9;
    Int32StringTuple2_ = (struct Int32StringTuple2_){.t0 = 1, .t1 = (struct String){.ptr = "a", .len = 1}};
    Int32StringTuple2_1 = (struct Int32StringTuple2_){.t0 = 2, .t1 = (struct String){.ptr = "b", .len = 1}};
    list_32 = ((struct Int32StringTuple2_Cons const *)milone_region_alloc(1, sizeof(struct Int32StringTuple2_Cons)));
    (*(((struct Int32StringTuple2_Cons *)list_32))) = (struct Int32StringTuple2_Cons){.head = Int32StringTuple2_1, .tail = NULL};
    list_31 = ((struct Int32StringTuple2_Cons const *)milone_region_alloc(1, sizeof(struct Int32StringTuple2_Cons)));
    (*(((struct Int32StringTuple2_Cons *)list_31))) = (struct Int32StringTuple2_Cons){.head = Int32StringTuple2_, .tail = list_32};
    Int32StringTuple2_2 = (struct Int32StringTuple2_){.t0 = 1, .t1 = (struct String){.ptr = "a", .len = 1}};
    Int32StringTuple2_3 = (struct Int32StringTuple2_){.t0 = 2, .t1 = (struct String){.ptr = "b", .len = 1}};
    list_34 = ((struct Int32StringTuple2_Cons const *)milone_region_alloc(1, sizeof(struct Int32StringTuple2_Cons)));
    (*(((struct Int32StringTuple2_Cons *)list_34))) = (struct Int32StringTuple2_Cons){.head = Int32StringTuple2_3, .tail = NULL};
    list_33 = ((struct Int32StringTuple2_Cons const *)milone_region_alloc(1, sizeof(struct Int32StringTuple2_Cons)));
    (*(((struct Int32StringTuple2_Cons *)list_33))) = (struct Int32StringTuple2_Cons){.head = Int32StringTuple2_2, .tail = list_34};
    call_9 = MiloneDerive_ListEqual_listEqual_1(list_31, list_33);
    if ((!(call_9))) milone_assert_error("list_equal/list_equal.milone", 22, 2);
    return;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    list_equal_list_equal_testIntList();
    list_equal_list_equal_testPairList();
    return 0;
}
