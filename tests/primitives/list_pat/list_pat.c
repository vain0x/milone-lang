#include "milone.h"

struct IntOption;

struct IntOptionOption;

struct IntOptionOptionOption;

struct IntIntOptionOptionOptionFun1;

struct IntList;

struct IntList;

struct IntOptionOptionOptionList;

struct IntOptionOptionOptionList;

struct IntOptionOptionOption fun_2(int x_22);

struct IntOptionOptionOption fun_1(void const* env_, int arg_);

struct IntOptionOptionOptionList const* map_(struct IntIntOptionOptionOptionFun1, struct IntList const*);

int milone_main();

struct IntOption {
    bool some;
    int value;
};

struct IntOptionOption {
    bool some;
    struct IntOption value;
};

struct IntOptionOptionOption {
    bool some;
    struct IntOptionOption value;
};

struct IntIntOptionOptionOptionFun1 {
    struct IntOptionOptionOption(*fun)(void const*, int);
    void const* env;
};

struct IntList {
    int head;
    struct IntList const* tail;
};

struct IntOptionOptionOptionList {
    struct IntOptionOptionOption head;
    struct IntOptionOptionOptionList const* tail;
};

struct IntOptionOptionOption fun_2(int x_22) {
    struct IntOption some_2 = (struct IntOption){.some = true, .value = x_22};
    struct IntOptionOption some_1 = (struct IntOptionOption){.some = true, .value = some_2};
    struct IntOptionOptionOption some_ = (struct IntOptionOptionOption){.some = true, .value = some_1};
    return some_;
}

struct IntOptionOptionOption fun_1(void const* env_, int arg_) {
    struct IntOptionOptionOption call_3 = fun_2(arg_);
    return call_3;
}

int milone_main() {
    char match_2;
    struct IntIntOptionOptionOptionFun1 fun_3 = (struct IntIntOptionOptionOptionFun1){.fun = fun_1, .env = NULL};
    struct IntList const* list_8 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_8))) = (struct IntList){.head = 7, .tail = NULL};
    struct IntList const* list_7 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_7))) = (struct IntList){.head = 6, .tail = list_8};
    struct IntList const* list_6 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_6))) = (struct IntList){.head = 5, .tail = list_7};
    struct IntList const* list_5 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_5))) = (struct IntList){.head = 4, .tail = list_6};
    struct IntList const* list_4 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_4))) = (struct IntList){.head = 3, .tail = list_5};
    struct IntList const* list_3 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_3))) = (struct IntList){.head = 2, .tail = list_4};
    struct IntList const* list_2 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_2))) = (struct IntList){.head = 1, .tail = list_3};
    struct IntOptionOptionOptionList const* call_4 = map_(fun_3, list_2);
    if ((!(call_4))) goto next_10;
    if ((!(call_4->head.some))) goto next_10;
    if ((!(call_4->head.value.some))) goto next_10;
    if ((!(call_4->head.value.value.some))) goto next_10;
    int x1_ = call_4->head.value.value.value;
    if ((!(call_4->tail))) goto next_10;
    if ((!(call_4->tail->head.some))) goto next_10;
    if ((!(call_4->tail->head.value.some))) goto next_10;
    if ((!(call_4->tail->head.value.value.some))) goto next_10;
    int x2_ = call_4->tail->head.value.value.value;
    if ((!(call_4->tail->tail))) goto next_10;
    if ((!(call_4->tail->tail->head.some))) goto next_10;
    if ((!(call_4->tail->tail->head.value.some))) goto next_10;
    if ((!(call_4->tail->tail->head.value.value.some))) goto next_10;
    int x3_ = call_4->tail->tail->head.value.value.value;
    if ((!(call_4->tail->tail->tail))) goto next_10;
    if ((!(call_4->tail->tail->tail->head.some))) goto next_10;
    if ((!(call_4->tail->tail->tail->head.value.some))) goto next_10;
    if ((!(call_4->tail->tail->tail->head.value.value.some))) goto next_10;
    int x4_ = call_4->tail->tail->tail->head.value.value.value;
    if ((!(call_4->tail->tail->tail->tail))) goto next_10;
    if ((!(call_4->tail->tail->tail->tail->head.some))) goto next_10;
    if ((!(call_4->tail->tail->tail->tail->head.value.some))) goto next_10;
    if ((!(call_4->tail->tail->tail->tail->head.value.value.some))) goto next_10;
    int x5_ = call_4->tail->tail->tail->tail->head.value.value.value;
    if ((!(call_4->tail->tail->tail->tail->tail))) goto next_10;
    if ((!(call_4->tail->tail->tail->tail->tail->head.some))) goto next_10;
    if ((!(call_4->tail->tail->tail->tail->tail->head.value.some))) goto next_10;
    if ((!(call_4->tail->tail->tail->tail->tail->head.value.value.some))) goto next_10;
    int x6_ = call_4->tail->tail->tail->tail->tail->head.value.value.value;
    if ((!(call_4->tail->tail->tail->tail->tail->tail))) goto next_10;
    if ((!(call_4->tail->tail->tail->tail->tail->tail->head.some))) goto next_10;
    if ((!(call_4->tail->tail->tail->tail->tail->tail->head.value.some))) goto next_10;
    if ((!(call_4->tail->tail->tail->tail->tail->tail->head.value.value.some))) goto next_10;
    int x7_ = call_4->tail->tail->tail->tail->tail->tail->head.value.value.value;
    if ((!((!(call_4->tail->tail->tail->tail->tail->tail->tail))))) goto next_10;
    milone_assert((x1_ == 1), 14, 4);
    milone_assert((x2_ == 2), 15, 4);
    milone_assert((x3_ == 3), 16, 4);
    milone_assert((x4_ == 4), 17, 4);
    milone_assert((x5_ == 5), 18, 4);
    milone_assert((x6_ == 6), 19, 4);
    milone_assert((x7_ == 7), 20, 4);
    match_2 = 0;
    goto end_match_9;
next_10:;
    milone_assert(false, 22, 9);
    match_2 = 0;
    goto end_match_9;
next_11:;
end_match_9:;
    return 0;
}
