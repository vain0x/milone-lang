#include "milone.h"

struct IntList;

struct IntList;

void list_operators_Program_nilTest(void);

void list_operators_Program_cons1Test(void);

void list_operators_Program_cons2Test(void);

void list_operators_Program_literalTest(void);

int milone_main(void);

struct IntList {
    int head;
    struct IntList const* tail;
};

void list_operators_Program_nilTest(void) {
    struct IntList const* nil_ = NULL;
    char if_;
    if ((!(nil_))) {
        goto nil_cl_2;
    } else {
        goto cons_cl_3;
    }
nil_cl_2:;
    if_ = 0;
    goto if_next_1;
cons_cl_3:;
    milone_assert(false, 9, 9);
    if_ = 0;
    goto if_next_1;
if_next_1:;
    return;
}

void list_operators_Program_cons1Test(void) {
    int x_;
    struct IntList const* list_ = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_))) = (struct IntList){.head = 1, .tail = NULL};
    struct IntList const* xs_ = list_;
    char match_;
    if ((!(xs_))) goto next_5;
    x_ = xs_->head;
    if ((!((!(xs_->tail))))) goto next_5;
    milone_assert((x_ == 1), 15, 15);
    match_ = 0;
    goto end_match_4;
next_5:;
    milone_assert(false, 16, 9);
    match_ = 0;
    goto end_match_4;
next_6:;
end_match_4:;
    return;
}

void list_operators_Program_cons2Test(void) {
    int y3_;
    int y2_;
    struct IntList const* list_2 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_2))) = (struct IntList){.head = 3, .tail = NULL};
    struct IntList const* list_1 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_1))) = (struct IntList){.head = 2, .tail = list_2};
    struct IntList const* ys_ = list_1;
    char match_1;
    if ((!(ys_))) goto next_8;
    y2_ = ys_->head;
    if ((!(ys_->tail))) goto next_8;
    y3_ = ys_->tail->head;
    if ((!((!(ys_->tail->tail))))) goto next_8;
    bool if_1;
    if ((y2_ == 2)) {
        goto then_11;
    } else {
        goto else_12;
    }
then_11:;
    if_1 = (y3_ == 3);
    goto if_next_10;
else_12:;
    if_1 = false;
    goto if_next_10;
if_next_10:;
    milone_assert(if_1, 22, 22);
    match_1 = 0;
    goto end_match_7;
next_8:;
    milone_assert(false, 23, 9);
    match_1 = 0;
    goto end_match_7;
next_9:;
end_match_7:;
    return;
}

void list_operators_Program_literalTest(void) {
    int z7_;
    int z5_;
    int z3_;
    int z2_;
    struct IntList const* list_6 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_6))) = (struct IntList){.head = 7, .tail = NULL};
    struct IntList const* list_5 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_5))) = (struct IntList){.head = 5, .tail = list_6};
    struct IntList const* list_4 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_4))) = (struct IntList){.head = 3, .tail = list_5};
    struct IntList const* list_3 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_3))) = (struct IntList){.head = 2, .tail = list_4};
    struct IntList const* zs_ = list_3;
    char match_2;
    if ((!(zs_))) goto next_14;
    z2_ = zs_->head;
    if ((!(zs_->tail))) goto next_14;
    z3_ = zs_->tail->head;
    if ((!(zs_->tail->tail))) goto next_14;
    z5_ = zs_->tail->tail->head;
    if ((!(zs_->tail->tail->tail))) goto next_14;
    z7_ = zs_->tail->tail->tail->head;
    if ((!((!(zs_->tail->tail->tail->tail))))) goto next_14;
    milone_assert((z2_ == 2), 30, 4);
    milone_assert((z3_ == 3), 31, 4);
    milone_assert((z5_ == 5), 32, 4);
    milone_assert((z7_ == 7), 33, 4);
    match_2 = 0;
    goto end_match_13;
next_14:;
    milone_assert(false, 35, 9);
    match_2 = 0;
    goto end_match_13;
next_15:;
end_match_13:;
    return;
}

int milone_main(void) {
    list_operators_Program_nilTest();
    list_operators_Program_cons1Test();
    list_operators_Program_cons2Test();
    list_operators_Program_literalTest();
    return 0;
}
