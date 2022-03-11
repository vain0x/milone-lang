#include <milone.h>

struct IntStringTuple2_;

struct IntList;

typedef bool(*VoidConstPtrIntIntBoolFunPtr3)(void const*, int, int);

struct IntIntBoolFun2;

struct IntStringTuple2_List;

typedef bool(*VoidConstPtrIntStringTuple2_IntStringTuple2_BoolFunPtr3)(void const*, struct IntStringTuple2_, struct IntStringTuple2_);

struct IntStringTuple2_IntStringTuple2_BoolFun2;

struct IntList;

struct IntStringTuple2_List;

bool MiloneDerive_TupleEqual_tuple2Equal(struct IntStringTuple2_ l_2, struct IntStringTuple2_ r_2);

bool MiloneDerive_ListEqual_eta3_prim(void const* env_, int arg_, int arg_1);

bool MiloneDerive_ListEqual_eta3_prim(void const* , int , int );

bool Std_Equal_IntIntBoolFun2IntListIntListBoolFun3_genericListEqual(struct IntIntBoolFun2 , struct IntList const* , struct IntList const* );

bool MiloneDerive_ListEqual_listEqual(struct IntList const* l_, struct IntList const* r_);

bool MiloneDerive_TupleEqual_tuple2Equal(struct IntStringTuple2_ , struct IntStringTuple2_ );

bool MiloneDerive_ListEqual_eta3_listEqual_tuple2Equal(void const* env_1, struct IntStringTuple2_ arg_2, struct IntStringTuple2_ arg_3);

bool MiloneDerive_ListEqual_eta3_listEqual_tuple2Equal(void const* , struct IntStringTuple2_ , struct IntStringTuple2_ );

bool Std_Equal_IntStringTuple2IntStringTuple2BoolFun2IntStringTuple2ListIntStringTuple2ListBoolFun3_genericListEqual(struct IntStringTuple2_IntStringTuple2_BoolFun2 , struct IntStringTuple2_List const* , struct IntStringTuple2_List const* );

bool MiloneDerive_ListEqual_listEqual_1(struct IntStringTuple2_List const* l_1, struct IntStringTuple2_List const* r_1);

bool MiloneDerive_ListEqual_listEqual(struct IntList const* , struct IntList const* );

void list_equal_list_equal_testIntList(void);

bool MiloneDerive_ListEqual_listEqual_1(struct IntStringTuple2_List const* , struct IntStringTuple2_List const* );

void list_equal_list_equal_testPairList(void);

int main(int argc, char** argv);

struct IntStringTuple2_ {
    int t0;
    struct String t1;
};

struct IntIntBoolFun2 {
    VoidConstPtrIntIntBoolFunPtr3 fun;
    void const* env;
};

struct IntStringTuple2_IntStringTuple2_BoolFun2 {
    VoidConstPtrIntStringTuple2_IntStringTuple2_BoolFunPtr3 fun;
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
    int l_3;
    int r_3;
    struct String l_4;
    struct String r_4;
    l_3 = l_2.t0;
    l_4 = l_2.t1;
    r_3 = r_2.t0;
    r_4 = r_2.t1;
    return ((l_3 == r_3) & (str_compare(l_4, r_4) == 0));
}

bool MiloneDerive_ListEqual_eta3_prim(void const* env_, int arg_, int arg_1) {
    return (arg_ == arg_1);
}

bool MiloneDerive_ListEqual_listEqual(struct IntList const* l_, struct IntList const* r_) {
    struct IntIntBoolFun2 fun_;
    bool call_;
    fun_ = (struct IntIntBoolFun2){.fun = MiloneDerive_ListEqual_eta3_prim, .env = NULL};
    call_ = Std_Equal_IntIntBoolFun2IntListIntListBoolFun3_genericListEqual(fun_, l_, r_);
    return call_;
}

bool MiloneDerive_ListEqual_eta3_listEqual_tuple2Equal(void const* env_1, struct IntStringTuple2_ arg_2, struct IntStringTuple2_ arg_3) {
    bool call_1;
    call_1 = MiloneDerive_TupleEqual_tuple2Equal(arg_2, arg_3);
    return call_1;
}

bool MiloneDerive_ListEqual_listEqual_1(struct IntStringTuple2_List const* l_1, struct IntStringTuple2_List const* r_1) {
    struct IntStringTuple2_IntStringTuple2_BoolFun2 fun_1;
    bool call_2;
    fun_1 = (struct IntStringTuple2_IntStringTuple2_BoolFun2){.fun = MiloneDerive_ListEqual_eta3_listEqual_tuple2Equal, .env = NULL};
    call_2 = Std_Equal_IntStringTuple2IntStringTuple2BoolFun2IntStringTuple2ListIntStringTuple2ListBoolFun3_genericListEqual(fun_1, l_1, r_1);
    return call_2;
}

void list_equal_list_equal_testIntList(void) {
    struct IntList const* nil_;
    struct IntList const* list_;
    struct IntList const* list_1;
    struct IntList const* list_2;
    struct IntList const* list_3;
    struct IntList const* list_4;
    struct IntList const* list_5;
    struct IntList const* list_6;
    struct IntList const* list_7;
    bool call_3;
    bool call_4;
    struct IntList const* list_8;
    bool call_5;
    struct IntList const* list_9;
    struct IntList const* list_10;
    struct IntList const* list_11;
    struct IntList const* list_12;
    struct IntList const* list_13;
    struct IntList const* list_14;
    struct IntList const* list_15;
    struct IntList const* list_16;
    bool call_6;
    struct IntList const* list_17;
    struct IntList const* list_18;
    struct IntList const* list_19;
    struct IntList const* list_20;
    struct IntList const* list_21;
    struct IntList const* list_22;
    struct IntList const* list_23;
    bool call_7;
    struct IntList const* list_24;
    struct IntList const* list_25;
    struct IntList const* list_26;
    struct IntList const* list_27;
    struct IntList const* list_28;
    struct IntList const* list_29;
    struct IntList const* list_30;
    bool call_8;
    list_3 = ((struct IntList const*)milone_mem_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_3))) = (struct IntList){.head = 5, .tail = NULL};
    list_2 = ((struct IntList const*)milone_mem_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_2))) = (struct IntList){.head = 3, .tail = list_3};
    list_1 = ((struct IntList const*)milone_mem_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_1))) = (struct IntList){.head = 2, .tail = list_2};
    list_ = ((struct IntList const*)milone_mem_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_))) = (struct IntList){.head = 2, .tail = list_1};
    list_7 = ((struct IntList const*)milone_mem_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_7))) = (struct IntList){.head = 5, .tail = NULL};
    list_6 = ((struct IntList const*)milone_mem_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_6))) = (struct IntList){.head = 3, .tail = list_7};
    list_5 = ((struct IntList const*)milone_mem_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_5))) = (struct IntList){.head = 2, .tail = list_6};
    list_4 = ((struct IntList const*)milone_mem_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_4))) = (struct IntList){.head = 2, .tail = list_5};
    call_3 = MiloneDerive_ListEqual_listEqual(list_, list_4);
    milone_assert(call_3, (struct String){.str = "list_equal/list_equal.milone", .len = 28}, 8, 2);
    nil_ = NULL;
    call_4 = MiloneDerive_ListEqual_listEqual(nil_, NULL);
    milone_assert(call_4, (struct String){.str = "list_equal/list_equal.milone", .len = 28}, 11, 2);
    list_8 = ((struct IntList const*)milone_mem_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_8))) = (struct IntList){.head = 0, .tail = NULL};
    call_5 = MiloneDerive_ListEqual_listEqual(nil_, list_8);
    milone_assert((!(call_5)), (struct String){.str = "list_equal/list_equal.milone", .len = 28}, 12, 2);
    list_12 = ((struct IntList const*)milone_mem_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_12))) = (struct IntList){.head = 5, .tail = NULL};
    list_11 = ((struct IntList const*)milone_mem_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_11))) = (struct IntList){.head = 3, .tail = list_12};
    list_10 = ((struct IntList const*)milone_mem_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_10))) = (struct IntList){.head = 2, .tail = list_11};
    list_9 = ((struct IntList const*)milone_mem_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_9))) = (struct IntList){.head = 2, .tail = list_10};
    list_16 = ((struct IntList const*)milone_mem_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_16))) = (struct IntList){.head = 5, .tail = NULL};
    list_15 = ((struct IntList const*)milone_mem_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_15))) = (struct IntList){.head = 2, .tail = list_16};
    list_14 = ((struct IntList const*)milone_mem_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_14))) = (struct IntList){.head = 3, .tail = list_15};
    list_13 = ((struct IntList const*)milone_mem_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_13))) = (struct IntList){.head = 2, .tail = list_14};
    call_6 = MiloneDerive_ListEqual_listEqual(list_9, list_13);
    milone_assert((!(call_6)), (struct String){.str = "list_equal/list_equal.milone", .len = 28}, 15, 2);
    list_19 = ((struct IntList const*)milone_mem_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_19))) = (struct IntList){.head = 3, .tail = NULL};
    list_18 = ((struct IntList const*)milone_mem_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_18))) = (struct IntList){.head = 2, .tail = list_19};
    list_17 = ((struct IntList const*)milone_mem_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_17))) = (struct IntList){.head = 2, .tail = list_18};
    list_23 = ((struct IntList const*)milone_mem_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_23))) = (struct IntList){.head = 5, .tail = NULL};
    list_22 = ((struct IntList const*)milone_mem_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_22))) = (struct IntList){.head = 3, .tail = list_23};
    list_21 = ((struct IntList const*)milone_mem_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_21))) = (struct IntList){.head = 2, .tail = list_22};
    list_20 = ((struct IntList const*)milone_mem_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_20))) = (struct IntList){.head = 2, .tail = list_21};
    call_7 = MiloneDerive_ListEqual_listEqual(list_17, list_20);
    milone_assert((!(call_7)), (struct String){.str = "list_equal/list_equal.milone", .len = 28}, 17, 2);
    list_26 = ((struct IntList const*)milone_mem_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_26))) = (struct IntList){.head = 5, .tail = NULL};
    list_25 = ((struct IntList const*)milone_mem_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_25))) = (struct IntList){.head = 3, .tail = list_26};
    list_24 = ((struct IntList const*)milone_mem_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_24))) = (struct IntList){.head = 2, .tail = list_25};
    list_30 = ((struct IntList const*)milone_mem_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_30))) = (struct IntList){.head = 5, .tail = NULL};
    list_29 = ((struct IntList const*)milone_mem_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_29))) = (struct IntList){.head = 3, .tail = list_30};
    list_28 = ((struct IntList const*)milone_mem_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_28))) = (struct IntList){.head = 2, .tail = list_29};
    list_27 = ((struct IntList const*)milone_mem_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_27))) = (struct IntList){.head = 2, .tail = list_28};
    call_8 = MiloneDerive_ListEqual_listEqual(list_24, list_27);
    milone_assert((!(call_8)), (struct String){.str = "list_equal/list_equal.milone", .len = 28}, 19, 2);
    return;
}

void list_equal_list_equal_testPairList(void) {
    struct IntStringTuple2_List const* list_31;
    struct IntStringTuple2_ IntStringTuple2_;
    struct IntStringTuple2_List const* list_32;
    struct IntStringTuple2_ IntStringTuple2_1;
    struct IntStringTuple2_List const* list_33;
    struct IntStringTuple2_ IntStringTuple2_2;
    struct IntStringTuple2_List const* list_34;
    struct IntStringTuple2_ IntStringTuple2_3;
    bool call_9;
    IntStringTuple2_ = (struct IntStringTuple2_){.t0 = 1, .t1 = (struct String){.str = "a", .len = 1}};
    IntStringTuple2_1 = (struct IntStringTuple2_){.t0 = 2, .t1 = (struct String){.str = "b", .len = 1}};
    list_32 = ((struct IntStringTuple2_List const*)milone_mem_alloc(1, sizeof(struct IntStringTuple2_List)));
    (*(((struct IntStringTuple2_List*)list_32))) = (struct IntStringTuple2_List){.head = IntStringTuple2_1, .tail = NULL};
    list_31 = ((struct IntStringTuple2_List const*)milone_mem_alloc(1, sizeof(struct IntStringTuple2_List)));
    (*(((struct IntStringTuple2_List*)list_31))) = (struct IntStringTuple2_List){.head = IntStringTuple2_, .tail = list_32};
    IntStringTuple2_2 = (struct IntStringTuple2_){.t0 = 1, .t1 = (struct String){.str = "a", .len = 1}};
    IntStringTuple2_3 = (struct IntStringTuple2_){.t0 = 2, .t1 = (struct String){.str = "b", .len = 1}};
    list_34 = ((struct IntStringTuple2_List const*)milone_mem_alloc(1, sizeof(struct IntStringTuple2_List)));
    (*(((struct IntStringTuple2_List*)list_34))) = (struct IntStringTuple2_List){.head = IntStringTuple2_3, .tail = NULL};
    list_33 = ((struct IntStringTuple2_List const*)milone_mem_alloc(1, sizeof(struct IntStringTuple2_List)));
    (*(((struct IntStringTuple2_List*)list_33))) = (struct IntStringTuple2_List){.head = IntStringTuple2_2, .tail = list_34};
    call_9 = MiloneDerive_ListEqual_listEqual_1(list_31, list_33);
    milone_assert(call_9, (struct String){.str = "list_equal/list_equal.milone", .len = 28}, 22, 2);
    return;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    list_equal_list_equal_testIntList();
    list_equal_list_equal_testPairList();
    return 0;
}
