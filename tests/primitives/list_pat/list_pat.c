#include "milone.h"

struct IntOption_;

struct IntOptionOption_;

struct IntOptionOptionOption_;

struct IntIntOptionOptionOption_Fun1;

struct IntList;

struct IntList;

struct IntOptionOptionOption_List;

struct IntOptionOptionOption_List;

struct IntOptionOptionOption_ list_pat_list_pat_main_IntIntOptionOptionOptionFun1_fun(int x_);

struct IntOptionOptionOption_ list_pat_list_pat_eta2_main_fun(void const* env_, int arg_);

struct IntOptionOptionOption_List const* MiloneCore_List_IntIntOptionOptionOptionFun1IntListIntOptionOptionOptionListFun2_map(struct IntIntOptionOptionOption_Fun1 , struct IntList const* );

int milone_main(void);

enum IntOption_Discriminant {
    None_,
    Some_,
};

struct IntOption_ {
    enum IntOption_Discriminant discriminant;
    union {
        int Some_;
    };
};

enum IntOptionOption_Discriminant {
    None_1,
    Some_1,
};

struct IntOptionOption_ {
    enum IntOptionOption_Discriminant discriminant;
    union {
        struct IntOption_ Some_1;
    };
};

enum IntOptionOptionOption_Discriminant {
    None_2,
    Some_2,
};

struct IntOptionOptionOption_ {
    enum IntOptionOptionOption_Discriminant discriminant;
    union {
        struct IntOptionOption_ Some_2;
    };
};

struct IntIntOptionOptionOption_Fun1 {
    struct IntOptionOptionOption_(*fun)(void const*, int);
    void const* env;
};

struct IntList {
    int head;
    struct IntList const* tail;
};

struct IntOptionOptionOption_List {
    struct IntOptionOptionOption_ head;
    struct IntOptionOptionOption_List const* tail;
};

struct IntOptionOptionOption_ list_pat_list_pat_main_IntIntOptionOptionOptionFun1_fun(int x_) {
    struct IntOption_ variant_ = (struct IntOption_){.discriminant = Some_, .Some_ = x_};
    struct IntOptionOption_ variant_1 = (struct IntOptionOption_){.discriminant = Some_1, .Some_1 = variant_};
    struct IntOptionOptionOption_ variant_2 = (struct IntOptionOptionOption_){.discriminant = Some_2, .Some_2 = variant_1};
    return variant_2;
}

struct IntOptionOptionOption_ list_pat_list_pat_eta2_main_fun(void const* env_, int arg_) {
    struct IntOptionOptionOption_ call_ = list_pat_list_pat_main_IntIntOptionOptionOptionFun1_fun(arg_);
    return call_;
}

int milone_main(void) {
    int x7_;
    int x6_;
    int x5_;
    int x4_;
    int x3_;
    int x2_;
    int x1_;
    char match_;
    struct IntIntOptionOptionOption_Fun1 fun_ = (struct IntIntOptionOptionOption_Fun1){.fun = list_pat_list_pat_eta2_main_fun, .env = NULL};
    struct IntList const* list_6 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_6))) = (struct IntList){.head = 7, .tail = NULL};
    struct IntList const* list_5 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_5))) = (struct IntList){.head = 6, .tail = list_6};
    struct IntList const* list_4 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_4))) = (struct IntList){.head = 5, .tail = list_5};
    struct IntList const* list_3 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_3))) = (struct IntList){.head = 4, .tail = list_4};
    struct IntList const* list_2 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_2))) = (struct IntList){.head = 3, .tail = list_3};
    struct IntList const* list_1 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_1))) = (struct IntList){.head = 2, .tail = list_2};
    struct IntList const* list_ = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_))) = (struct IntList){.head = 1, .tail = list_1};
    struct IntOptionOptionOption_List const* call_1 = MiloneCore_List_IntIntOptionOptionOptionFun1IntListIntOptionOptionOptionListFun2_map(fun_, list_);
    if ((!(call_1))) goto next_10;
    if ((call_1->head.discriminant != Some_2)) goto next_10;
    if ((call_1->head.Some_2.discriminant != Some_1)) goto next_10;
    if ((call_1->head.Some_2.Some_1.discriminant != Some_)) goto next_10;
    x1_ = call_1->head.Some_2.Some_1.Some_;
    if ((!(call_1->tail))) goto next_10;
    if ((call_1->tail->head.discriminant != Some_2)) goto next_10;
    if ((call_1->tail->head.Some_2.discriminant != Some_1)) goto next_10;
    if ((call_1->tail->head.Some_2.Some_1.discriminant != Some_)) goto next_10;
    x2_ = call_1->tail->head.Some_2.Some_1.Some_;
    if ((!(call_1->tail->tail))) goto next_10;
    if ((call_1->tail->tail->head.discriminant != Some_2)) goto next_10;
    if ((call_1->tail->tail->head.Some_2.discriminant != Some_1)) goto next_10;
    if ((call_1->tail->tail->head.Some_2.Some_1.discriminant != Some_)) goto next_10;
    x3_ = call_1->tail->tail->head.Some_2.Some_1.Some_;
    if ((!(call_1->tail->tail->tail))) goto next_10;
    if ((call_1->tail->tail->tail->head.discriminant != Some_2)) goto next_10;
    if ((call_1->tail->tail->tail->head.Some_2.discriminant != Some_1)) goto next_10;
    if ((call_1->tail->tail->tail->head.Some_2.Some_1.discriminant != Some_)) goto next_10;
    x4_ = call_1->tail->tail->tail->head.Some_2.Some_1.Some_;
    if ((!(call_1->tail->tail->tail->tail))) goto next_10;
    if ((call_1->tail->tail->tail->tail->head.discriminant != Some_2)) goto next_10;
    if ((call_1->tail->tail->tail->tail->head.Some_2.discriminant != Some_1)) goto next_10;
    if ((call_1->tail->tail->tail->tail->head.Some_2.Some_1.discriminant != Some_)) goto next_10;
    x5_ = call_1->tail->tail->tail->tail->head.Some_2.Some_1.Some_;
    if ((!(call_1->tail->tail->tail->tail->tail))) goto next_10;
    if ((call_1->tail->tail->tail->tail->tail->head.discriminant != Some_2)) goto next_10;
    if ((call_1->tail->tail->tail->tail->tail->head.Some_2.discriminant != Some_1)) goto next_10;
    if ((call_1->tail->tail->tail->tail->tail->head.Some_2.Some_1.discriminant != Some_)) goto next_10;
    x6_ = call_1->tail->tail->tail->tail->tail->head.Some_2.Some_1.Some_;
    if ((!(call_1->tail->tail->tail->tail->tail->tail))) goto next_10;
    if ((call_1->tail->tail->tail->tail->tail->tail->head.discriminant != Some_2)) goto next_10;
    if ((call_1->tail->tail->tail->tail->tail->tail->head.Some_2.discriminant != Some_1)) goto next_10;
    if ((call_1->tail->tail->tail->tail->tail->tail->head.Some_2.Some_1.discriminant != Some_)) goto next_10;
    x7_ = call_1->tail->tail->tail->tail->tail->tail->head.Some_2.Some_1.Some_;
    if ((!((!(call_1->tail->tail->tail->tail->tail->tail->tail))))) goto next_10;
    milone_assert((x1_ == 1), 15, 4);
    milone_assert((x2_ == 2), 16, 4);
    milone_assert((x3_ == 3), 17, 4);
    milone_assert((x4_ == 4), 18, 4);
    milone_assert((x5_ == 5), 19, 4);
    milone_assert((x6_ == 6), 20, 4);
    milone_assert((x7_ == 7), 21, 4);
    match_ = 0;
    goto end_match_9;
next_10:;
    milone_assert(false, 23, 9);
    match_ = 0;
    goto end_match_9;
next_11:;
end_match_9:;
    return 0;
}
