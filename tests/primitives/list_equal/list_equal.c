#include "milone.h"

struct IntList;

struct IntList;

struct IntStringTuple2_;

struct IntStringTuple2_List;

struct IntStringTuple2_List;

bool listEqual_(struct IntList const* , struct IntList const* );

void testIntList_(void);

bool listEqual_1(struct IntStringTuple2_List const* , struct IntStringTuple2_List const* );

void testPairList_(void);

int milone_main(void);

struct IntList {
    int head;
    struct IntList const* tail;
};

struct IntStringTuple2_ {
    int t0;
    struct String t1;
};

struct IntStringTuple2_List {
    struct IntStringTuple2_ head;
    struct IntStringTuple2_List const* tail;
};

void testIntList_(void) {
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
    bool call_5 = listEqual_(list_, list_4);
    milone_assert(call_5, 8, 2);
    struct IntList const* nil_ = NULL;
    bool call_6 = listEqual_(nil_, NULL);
    milone_assert(call_6, 11, 2);
    struct IntList const* list_8 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_8))) = (struct IntList){.head = 0, .tail = NULL};
    bool call_7 = listEqual_(nil_, list_8);
    milone_assert((!(call_7)), 12, 2);
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
    bool call_8 = listEqual_(list_9, list_13);
    milone_assert((!(call_8)), 15, 2);
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
    bool call_9 = listEqual_(list_17, list_20);
    milone_assert((!(call_9)), 17, 2);
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
    bool call_10 = listEqual_(list_24, list_27);
    milone_assert((!(call_10)), 19, 2);
    return;
}

void testPairList_(void) {
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
    bool call_11 = listEqual_1(list_31, list_33);
    milone_assert(call_11, 22, 2);
    return;
}

int milone_main(void) {
    testIntList_();
    testPairList_();
    return 0;
}
