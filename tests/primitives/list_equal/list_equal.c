#include "milone.h"

struct IntStringTuple2_;

struct IntList;

struct IntIntBoolFun2;

struct IntStringTuple2_List;

struct IntStringTuple2_IntStringTuple2_BoolFun2;

struct IntList;

struct IntStringTuple2_List;

bool MiloneDerive_TupleEqual_tuple2Equal(struct IntStringTuple2_ l_2, struct IntStringTuple2_ r_2);

bool MiloneDerive_ListEqual_eta3_prim(void const* env_, int arg_, int arg_1);

bool MiloneDerive_ListEqual_eta3_prim(void const* , int , int );

bool MiloneStd_Equal_IntIntBoolFun2IntListIntListBoolFun3_genericListEqual(struct IntIntBoolFun2 , struct IntList const* , struct IntList const* );

bool MiloneDerive_ListEqual_listEqual(struct IntList const* l_, struct IntList const* r_);

bool MiloneDerive_TupleEqual_tuple2Equal(struct IntStringTuple2_ , struct IntStringTuple2_ );

bool MiloneDerive_ListEqual_eta3_listEqual_tuple2Equal(void const* env_1, struct IntStringTuple2_ arg_2, struct IntStringTuple2_ arg_3);

bool MiloneDerive_ListEqual_eta3_listEqual_tuple2Equal(void const* , struct IntStringTuple2_ , struct IntStringTuple2_ );

bool MiloneStd_Equal_IntStringTuple2IntStringTuple2BoolFun2IntStringTuple2ListIntStringTuple2ListBoolFun3_genericListEqual(struct IntStringTuple2_IntStringTuple2_BoolFun2 , struct IntStringTuple2_List const* , struct IntStringTuple2_List const* );

bool MiloneDerive_ListEqual_listEqual_1(struct IntStringTuple2_List const* l_1, struct IntStringTuple2_List const* r_1);

bool MiloneDerive_ListEqual_listEqual(struct IntList const* , struct IntList const* );

void list_equal_list_equal_testIntList(void);

bool MiloneDerive_ListEqual_listEqual_1(struct IntStringTuple2_List const* , struct IntStringTuple2_List const* );

void list_equal_list_equal_testPairList(void);

int milone_main(void);

struct IntStringTuple2_ {
    int t0;
    struct String t1;
};

struct IntIntBoolFun2 {
    bool(*fun)(void const*, int, int);
    void const* env;
};

struct IntStringTuple2_IntStringTuple2_BoolFun2 {
    bool(*fun)(void const*, struct IntStringTuple2_, struct IntStringTuple2_);
    void const* env;
};

struct IntList {
    int head;
    struct IntList const* tail;
};

struct IntStringTuple2_List {
    struct IntStringTuple2_ head;
    struct IntStringTuple2_List const* tail;
};

bool MiloneDerive_TupleEqual_tuple2Equal(struct IntStringTuple2_ l_2, struct IntStringTuple2_ r_2) {
    int l_3 = l_2.t0;
    struct String l_4 = l_2.t1;
    int r_3 = r_2.t0;
    struct String r_4 = r_2.t1;
    return ((l_3 == r_3) & (str_compare(l_4, r_4) == 0));
}

bool MiloneDerive_ListEqual_eta3_prim(void const* env_, int arg_, int arg_1) {
    return (arg_ == arg_1);
}

bool MiloneDerive_ListEqual_listEqual(struct IntList const* l_, struct IntList const* r_) {
    struct IntIntBoolFun2 fun_ = (struct IntIntBoolFun2){.fun = MiloneDerive_ListEqual_eta3_prim, .env = NULL};
    bool call_ = MiloneStd_Equal_IntIntBoolFun2IntListIntListBoolFun3_genericListEqual(fun_, l_, r_);
    return call_;
}

bool MiloneDerive_ListEqual_eta3_listEqual_tuple2Equal(void const* env_1, struct IntStringTuple2_ arg_2, struct IntStringTuple2_ arg_3) {
    bool call_1 = MiloneDerive_TupleEqual_tuple2Equal(arg_2, arg_3);
    return call_1;
}

bool MiloneDerive_ListEqual_listEqual_1(struct IntStringTuple2_List const* l_1, struct IntStringTuple2_List const* r_1) {
    struct IntStringTuple2_IntStringTuple2_BoolFun2 fun_1 = (struct IntStringTuple2_IntStringTuple2_BoolFun2){.fun = MiloneDerive_ListEqual_eta3_listEqual_tuple2Equal, .env = NULL};
    bool call_2 = MiloneStd_Equal_IntStringTuple2IntStringTuple2BoolFun2IntStringTuple2ListIntStringTuple2ListBoolFun3_genericListEqual(fun_1, l_1, r_1);
    return call_2;
}

void list_equal_list_equal_testIntList(void) {
    struct IntList const* list_3 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_3))) = (struct IntList){.head = 5, .tail = NULL};
    struct IntList const* list_2 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_2))) = (struct IntList){.head = 3, .tail = list_3};
    struct IntList const* list_1 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_1))) = (struct IntList){.head = 2, .tail = list_2};
    struct IntList const* list_ = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_))) = (struct IntList){.head = 2, .tail = list_1};
    struct IntList const* list_7 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_7))) = (struct IntList){.head = 5, .tail = NULL};
    struct IntList const* list_6 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_6))) = (struct IntList){.head = 3, .tail = list_7};
    struct IntList const* list_5 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_5))) = (struct IntList){.head = 2, .tail = list_6};
    struct IntList const* list_4 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_4))) = (struct IntList){.head = 2, .tail = list_5};
    bool call_3 = MiloneDerive_ListEqual_listEqual(list_, list_4);
    milone_assert(call_3, 8, 2);
    struct IntList const* nil_ = NULL;
    bool call_4 = MiloneDerive_ListEqual_listEqual(nil_, NULL);
    milone_assert(call_4, 11, 2);
    struct IntList const* list_8 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_8))) = (struct IntList){.head = 0, .tail = NULL};
    bool call_5 = MiloneDerive_ListEqual_listEqual(nil_, list_8);
    milone_assert((!(call_5)), 12, 2);
    struct IntList const* list_12 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_12))) = (struct IntList){.head = 5, .tail = NULL};
    struct IntList const* list_11 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_11))) = (struct IntList){.head = 3, .tail = list_12};
    struct IntList const* list_10 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_10))) = (struct IntList){.head = 2, .tail = list_11};
    struct IntList const* list_9 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_9))) = (struct IntList){.head = 2, .tail = list_10};
    struct IntList const* list_16 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_16))) = (struct IntList){.head = 5, .tail = NULL};
    struct IntList const* list_15 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_15))) = (struct IntList){.head = 2, .tail = list_16};
    struct IntList const* list_14 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_14))) = (struct IntList){.head = 3, .tail = list_15};
    struct IntList const* list_13 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_13))) = (struct IntList){.head = 2, .tail = list_14};
    bool call_6 = MiloneDerive_ListEqual_listEqual(list_9, list_13);
    milone_assert((!(call_6)), 15, 2);
    struct IntList const* list_19 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_19))) = (struct IntList){.head = 3, .tail = NULL};
    struct IntList const* list_18 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_18))) = (struct IntList){.head = 2, .tail = list_19};
    struct IntList const* list_17 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_17))) = (struct IntList){.head = 2, .tail = list_18};
    struct IntList const* list_23 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_23))) = (struct IntList){.head = 5, .tail = NULL};
    struct IntList const* list_22 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_22))) = (struct IntList){.head = 3, .tail = list_23};
    struct IntList const* list_21 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_21))) = (struct IntList){.head = 2, .tail = list_22};
    struct IntList const* list_20 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_20))) = (struct IntList){.head = 2, .tail = list_21};
    bool call_7 = MiloneDerive_ListEqual_listEqual(list_17, list_20);
    milone_assert((!(call_7)), 17, 2);
    struct IntList const* list_26 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_26))) = (struct IntList){.head = 5, .tail = NULL};
    struct IntList const* list_25 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_25))) = (struct IntList){.head = 3, .tail = list_26};
    struct IntList const* list_24 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_24))) = (struct IntList){.head = 2, .tail = list_25};
    struct IntList const* list_30 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_30))) = (struct IntList){.head = 5, .tail = NULL};
    struct IntList const* list_29 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_29))) = (struct IntList){.head = 3, .tail = list_30};
    struct IntList const* list_28 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_28))) = (struct IntList){.head = 2, .tail = list_29};
    struct IntList const* list_27 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_27))) = (struct IntList){.head = 2, .tail = list_28};
    bool call_8 = MiloneDerive_ListEqual_listEqual(list_24, list_27);
    milone_assert((!(call_8)), 19, 2);
    return;
}

void list_equal_list_equal_testPairList(void) {
    struct IntStringTuple2_ IntStringTuple2_ = (struct IntStringTuple2_){.t0 = 1, .t1 = (struct String){.str = "a", .len = 1}};
    struct IntStringTuple2_ IntStringTuple2_1 = (struct IntStringTuple2_){.t0 = 2, .t1 = (struct String){.str = "b", .len = 1}};
    struct IntStringTuple2_List const* list_32 = milone_mem_alloc(1, sizeof(struct IntStringTuple2_List));
    (*(((struct IntStringTuple2_List*)list_32))) = (struct IntStringTuple2_List){.head = IntStringTuple2_1, .tail = NULL};
    struct IntStringTuple2_List const* list_31 = milone_mem_alloc(1, sizeof(struct IntStringTuple2_List));
    (*(((struct IntStringTuple2_List*)list_31))) = (struct IntStringTuple2_List){.head = IntStringTuple2_, .tail = list_32};
    struct IntStringTuple2_ IntStringTuple2_2 = (struct IntStringTuple2_){.t0 = 1, .t1 = (struct String){.str = "a", .len = 1}};
    struct IntStringTuple2_ IntStringTuple2_3 = (struct IntStringTuple2_){.t0 = 2, .t1 = (struct String){.str = "b", .len = 1}};
    struct IntStringTuple2_List const* list_34 = milone_mem_alloc(1, sizeof(struct IntStringTuple2_List));
    (*(((struct IntStringTuple2_List*)list_34))) = (struct IntStringTuple2_List){.head = IntStringTuple2_3, .tail = NULL};
    struct IntStringTuple2_List const* list_33 = milone_mem_alloc(1, sizeof(struct IntStringTuple2_List));
    (*(((struct IntStringTuple2_List*)list_33))) = (struct IntStringTuple2_List){.head = IntStringTuple2_2, .tail = list_34};
    bool call_9 = MiloneDerive_ListEqual_listEqual_1(list_31, list_33);
    milone_assert(call_9, 22, 2);
    return;
}

int milone_main(void) {
    list_equal_list_equal_testIntList();
    list_equal_list_equal_testPairList();
    return 0;
}
