#include <milone.h>

struct Intoption1_;

struct Intoption1option1_;

struct Intoption1option1option1_;

typedef struct Intoption1option1option1_(*VoidConstPtrIntIntoption1option1option1_FunPtr2)(void const*, int);

struct IntIntoption1option1option1_Fun1;

struct IntList;

struct IntList;

struct Intoption1option1option1_List;

struct Intoption1option1option1_List;

struct Intoption1option1option1_ list_pat_list_pat_main_IntIntoption1option1option1Fun1_fun(int x_);

struct Intoption1option1option1_ list_pat_list_pat_eta2_main_fun(void const* env_, int arg_);

struct Intoption1option1option1_List const* MiloneCore_List_IntIntoption1option1option1Fun1IntListIntoption1option1option1ListFun2_map(struct IntIntoption1option1option1_Fun1 , struct IntList const* );

int main(int argc, char** argv);

enum Intoption1_Discriminant {
    None_,
    Some_,
};

struct Intoption1_ {
    enum Intoption1_Discriminant discriminant;
    union {
        int Some_;
    };
};

enum Intoption1option1_Discriminant {
    None_1,
    Some_1,
};

struct Intoption1option1_ {
    enum Intoption1option1_Discriminant discriminant;
    union {
        struct Intoption1_ Some_1;
    };
};

enum Intoption1option1option1_Discriminant {
    None_2,
    Some_2,
};

struct Intoption1option1option1_ {
    enum Intoption1option1option1_Discriminant discriminant;
    union {
        struct Intoption1option1_ Some_2;
    };
};

struct IntIntoption1option1option1_Fun1 {
    VoidConstPtrIntIntoption1option1option1_FunPtr2 fun;
    void const* env;
};

struct IntList {
    int head;
    struct IntList const* tail;
};

struct Intoption1option1option1_List {
    struct Intoption1option1option1_ head;
    struct Intoption1option1option1_List const* tail;
};

struct Intoption1option1option1_ list_pat_list_pat_main_IntIntoption1option1option1Fun1_fun(int x_) {
    struct Intoption1_ variant_ = (struct Intoption1_){.discriminant = Some_, .Some_ = x_};
    struct Intoption1option1_ variant_1 = (struct Intoption1option1_){.discriminant = Some_1, .Some_1 = variant_};
    struct Intoption1option1option1_ variant_2 = (struct Intoption1option1option1_){.discriminant = Some_2, .Some_2 = variant_1};
    return variant_2;
}

struct Intoption1option1option1_ list_pat_list_pat_eta2_main_fun(void const* env_, int arg_) {
    struct Intoption1option1option1_ call_ = list_pat_list_pat_main_IntIntoption1option1option1Fun1_fun(arg_);
    return call_;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    int x7_;
    int x6_;
    int x5_;
    int x4_;
    int x3_;
    int x2_;
    int x1_;
    char match_;
    struct IntIntoption1option1option1_Fun1 fun_ = (struct IntIntoption1option1option1_Fun1){.fun = list_pat_list_pat_eta2_main_fun, .env = NULL};
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
    struct Intoption1option1option1_List const* call_1 = MiloneCore_List_IntIntoption1option1option1Fun1IntListIntoption1option1option1ListFun2_map(fun_, list_);
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
    milone_assert((x1_ == 1), (struct String){.str = "list_pat/list_pat.milone", .len = 24}, 15, 4);
    milone_assert((x2_ == 2), (struct String){.str = "list_pat/list_pat.milone", .len = 24}, 16, 4);
    milone_assert((x3_ == 3), (struct String){.str = "list_pat/list_pat.milone", .len = 24}, 17, 4);
    milone_assert((x4_ == 4), (struct String){.str = "list_pat/list_pat.milone", .len = 24}, 18, 4);
    milone_assert((x5_ == 5), (struct String){.str = "list_pat/list_pat.milone", .len = 24}, 19, 4);
    milone_assert((x6_ == 6), (struct String){.str = "list_pat/list_pat.milone", .len = 24}, 20, 4);
    milone_assert((x7_ == 7), (struct String){.str = "list_pat/list_pat.milone", .len = 24}, 21, 4);
    match_ = 0;
    goto end_match_9;
next_10:;
    milone_assert(false, (struct String){.str = "list_pat/list_pat.milone", .len = 24}, 23, 9);
    match_ = 0;
    goto end_match_9;
next_11:;
end_match_9:;
    return 0;
}
