#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32option1_;

struct Int32option1option1_;

struct Int32option1option1option1_;

typedef struct Int32option1option1option1_(*VoidConstPtrInt32Int32option1option1option1_FunPtr2)(void const *, int32_t);

struct Int32Int32option1option1option1_Fun1;

struct Int32Cons;

struct Int32option1option1option1_Cons;

struct Int32Cons;

struct Int32option1option1option1_Cons;

struct Int32option1option1option1_ list_pat_list_pat_main_fun(int32_t x_);

struct Int32option1option1option1_ list_pat_list_pat_eta2_main_fun(void const *env_, int32_t arg_);

struct Int32option1option1option1_Cons const *MiloneCore_List_Int32Int32option1option1option1Fun1Int32ListInt32option1option1option1ListFun2_map(struct Int32Int32option1option1option1_Fun1, struct Int32Cons const *);

int main(int argc, char **argv);

enum Int32option1_Discriminant {
    Int32option1_None,
    Int32option1_Some,
};

struct Int32option1_ {
    enum Int32option1_Discriminant discriminant;
    union {
        int32_t Int32option1_Some;
    };
};

enum Int32option1option1_Discriminant {
    Int32option1option1_None,
    Int32option1option1_Some,
};

struct Int32option1option1_ {
    enum Int32option1option1_Discriminant discriminant;
    union {
        struct Int32option1_ Int32option1option1_Some;
    };
};

enum Int32option1option1option1_Discriminant {
    Int32option1option1option1_None,
    Int32option1option1option1_Some,
};

struct Int32option1option1option1_ {
    enum Int32option1option1option1_Discriminant discriminant;
    union {
        struct Int32option1option1_ Int32option1option1option1_Some;
    };
};

struct Int32Int32option1option1option1_Fun1 {
    VoidConstPtrInt32Int32option1option1option1_FunPtr2 fun;
    void const *env;
};

struct Int32Cons {
    int32_t head;
    struct Int32Cons const *tail;
};

struct Int32option1option1option1_Cons {
    struct Int32option1option1option1_ head;
    struct Int32option1option1option1_Cons const *tail;
};

struct Int32option1option1option1_ list_pat_list_pat_main_fun(int32_t x_) {
    struct Int32option1_ variant_;
    struct Int32option1option1_ variant_1;
    struct Int32option1option1option1_ variant_2;
    variant_ = (struct Int32option1_){.discriminant = Int32option1_Some, .Int32option1_Some = x_};
    variant_1 = (struct Int32option1option1_){.discriminant = Int32option1option1_Some, .Int32option1option1_Some = variant_};
    variant_2 = (struct Int32option1option1option1_){.discriminant = Int32option1option1option1_Some, .Int32option1option1option1_Some = variant_1};
    return variant_2;
}

struct Int32option1option1option1_ list_pat_list_pat_eta2_main_fun(void const *env_, int32_t arg_) {
    struct Int32option1option1option1_ call_;
    call_ = list_pat_list_pat_main_fun(arg_);
    return call_;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    int32_t x1_;
    int32_t x2_;
    int32_t x3_;
    int32_t x4_;
    int32_t x5_;
    int32_t x6_;
    int32_t x7_;
    char match_;
    struct Int32Int32option1option1option1_Fun1 fun_;
    struct Int32Cons const *list_;
    struct Int32Cons const *list_1;
    struct Int32Cons const *list_2;
    struct Int32Cons const *list_3;
    struct Int32Cons const *list_4;
    struct Int32Cons const *list_5;
    struct Int32Cons const *list_6;
    struct Int32option1option1option1_Cons const *call_1;
    fun_ = (struct Int32Int32option1option1option1_Fun1){.fun = list_pat_list_pat_eta2_main_fun, .env = NULL};
    list_6 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_6))) = (struct Int32Cons){.head = 7, .tail = NULL};
    list_5 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_5))) = (struct Int32Cons){.head = 6, .tail = list_6};
    list_4 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_4))) = (struct Int32Cons){.head = 5, .tail = list_5};
    list_3 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_3))) = (struct Int32Cons){.head = 4, .tail = list_4};
    list_2 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_2))) = (struct Int32Cons){.head = 3, .tail = list_3};
    list_1 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_1))) = (struct Int32Cons){.head = 2, .tail = list_2};
    list_ = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_))) = (struct Int32Cons){.head = 1, .tail = list_1};
    call_1 = MiloneCore_List_Int32Int32option1option1option1Fun1Int32ListInt32option1option1option1ListFun2_map(fun_, list_);
    if ((!(call_1))) goto next_10;
    if ((call_1->head.discriminant != Int32option1option1option1_Some)) goto next_10;
    if ((call_1->head.Int32option1option1option1_Some.discriminant != Int32option1option1_Some)) goto next_10;
    if ((call_1->head.Int32option1option1option1_Some.Int32option1option1_Some.discriminant != Int32option1_Some)) goto next_10;
    x1_ = call_1->head.Int32option1option1option1_Some.Int32option1option1_Some.Int32option1_Some;
    if ((!(call_1->tail))) goto next_10;
    if ((call_1->tail->head.discriminant != Int32option1option1option1_Some)) goto next_10;
    if ((call_1->tail->head.Int32option1option1option1_Some.discriminant != Int32option1option1_Some)) goto next_10;
    if ((call_1->tail->head.Int32option1option1option1_Some.Int32option1option1_Some.discriminant != Int32option1_Some)) goto next_10;
    x2_ = call_1->tail->head.Int32option1option1option1_Some.Int32option1option1_Some.Int32option1_Some;
    if ((!(call_1->tail->tail))) goto next_10;
    if ((call_1->tail->tail->head.discriminant != Int32option1option1option1_Some)) goto next_10;
    if ((call_1->tail->tail->head.Int32option1option1option1_Some.discriminant != Int32option1option1_Some)) goto next_10;
    if ((call_1->tail->tail->head.Int32option1option1option1_Some.Int32option1option1_Some.discriminant != Int32option1_Some)) goto next_10;
    x3_ = call_1->tail->tail->head.Int32option1option1option1_Some.Int32option1option1_Some.Int32option1_Some;
    if ((!(call_1->tail->tail->tail))) goto next_10;
    if ((call_1->tail->tail->tail->head.discriminant != Int32option1option1option1_Some)) goto next_10;
    if ((call_1->tail->tail->tail->head.Int32option1option1option1_Some.discriminant != Int32option1option1_Some)) goto next_10;
    if ((call_1->tail->tail->tail->head.Int32option1option1option1_Some.Int32option1option1_Some.discriminant != Int32option1_Some)) goto next_10;
    x4_ = call_1->tail->tail->tail->head.Int32option1option1option1_Some.Int32option1option1_Some.Int32option1_Some;
    if ((!(call_1->tail->tail->tail->tail))) goto next_10;
    if ((call_1->tail->tail->tail->tail->head.discriminant != Int32option1option1option1_Some)) goto next_10;
    if ((call_1->tail->tail->tail->tail->head.Int32option1option1option1_Some.discriminant != Int32option1option1_Some)) goto next_10;
    if ((call_1->tail->tail->tail->tail->head.Int32option1option1option1_Some.Int32option1option1_Some.discriminant != Int32option1_Some)) goto next_10;
    x5_ = call_1->tail->tail->tail->tail->head.Int32option1option1option1_Some.Int32option1option1_Some.Int32option1_Some;
    if ((!(call_1->tail->tail->tail->tail->tail))) goto next_10;
    if ((call_1->tail->tail->tail->tail->tail->head.discriminant != Int32option1option1option1_Some)) goto next_10;
    if ((call_1->tail->tail->tail->tail->tail->head.Int32option1option1option1_Some.discriminant != Int32option1option1_Some)) goto next_10;
    if ((call_1->tail->tail->tail->tail->tail->head.Int32option1option1option1_Some.Int32option1option1_Some.discriminant != Int32option1_Some)) goto next_10;
    x6_ = call_1->tail->tail->tail->tail->tail->head.Int32option1option1option1_Some.Int32option1option1_Some.Int32option1_Some;
    if ((!(call_1->tail->tail->tail->tail->tail->tail))) goto next_10;
    if ((call_1->tail->tail->tail->tail->tail->tail->head.discriminant != Int32option1option1option1_Some)) goto next_10;
    if ((call_1->tail->tail->tail->tail->tail->tail->head.Int32option1option1option1_Some.discriminant != Int32option1option1_Some)) goto next_10;
    if ((call_1->tail->tail->tail->tail->tail->tail->head.Int32option1option1option1_Some.Int32option1option1_Some.discriminant != Int32option1_Some)) goto next_10;
    x7_ = call_1->tail->tail->tail->tail->tail->tail->head.Int32option1option1option1_Some.Int32option1option1_Some.Int32option1_Some;
    if ((!((!(call_1->tail->tail->tail->tail->tail->tail->tail))))) goto next_10;
    if ((x1_ != 1)) milone_assert_error("list_pat/list_pat.milone", 15, 4);
    if ((x2_ != 2)) milone_assert_error("list_pat/list_pat.milone", 16, 4);
    if ((x3_ != 3)) milone_assert_error("list_pat/list_pat.milone", 17, 4);
    if ((x4_ != 4)) milone_assert_error("list_pat/list_pat.milone", 18, 4);
    if ((x5_ != 5)) milone_assert_error("list_pat/list_pat.milone", 19, 4);
    if ((x6_ != 6)) milone_assert_error("list_pat/list_pat.milone", 20, 4);
    if ((x7_ != 7)) milone_assert_error("list_pat/list_pat.milone", 21, 4);
    match_ = 0;
    goto end_match_9;
next_10:;
    if (true) milone_assert_error("list_pat/list_pat.milone", 23, 9);
    match_ = 0;
    goto end_match_9;
next_11:;
end_match_9:;
    return 0;
}
