#include "milone.h"

struct IntList;

struct IntList;

char nilTest_(char arg_);

char cons1Test_(char arg_1);

char cons2Test_(char arg_2);

char literalTest_(char arg_3);

int milone_main();

struct IntList {
    int head;
    struct IntList const* tail;
};

char nilTest_(char arg_) {
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
    return 0;
}

char cons1Test_(char arg_1) {
    struct IntList const* list_ = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_))) = ((struct IntList){.head = 1, .tail = NULL});
    struct IntList const* xs_ = list_;
    char match_;
    if ((!(xs_))) goto next_5;
    int x_ = xs_->head;
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
    return 0;
}

char cons2Test_(char arg_2) {
    struct IntList const* list_2 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_2))) = ((struct IntList){.head = 3, .tail = NULL});
    struct IntList const* list_1 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_1))) = ((struct IntList){.head = 2, .tail = list_2});
    struct IntList const* ys_ = list_1;
    char match_1;
    if ((!(ys_))) goto next_8;
    int y2_ = ys_->head;
    if ((!(ys_->tail))) goto next_8;
    int y3_ = ys_->tail->head;
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
    return 0;
}

char literalTest_(char arg_3) {
    struct IntList const* list_6 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_6))) = ((struct IntList){.head = 7, .tail = NULL});
    struct IntList const* list_5 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_5))) = ((struct IntList){.head = 5, .tail = list_6});
    struct IntList const* list_4 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_4))) = ((struct IntList){.head = 3, .tail = list_5});
    struct IntList const* list_3 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_3))) = ((struct IntList){.head = 2, .tail = list_4});
    struct IntList const* zs_ = list_3;
    char match_2;
    if ((!(zs_))) goto next_14;
    int z2_ = zs_->head;
    if ((!(zs_->tail))) goto next_14;
    int z3_ = zs_->tail->head;
    if ((!(zs_->tail->tail))) goto next_14;
    int z5_ = zs_->tail->tail->head;
    if ((!(zs_->tail->tail->tail))) goto next_14;
    int z7_ = zs_->tail->tail->tail->head;
    if ((!((!(zs_->tail->tail->tail->tail))))) goto next_14;
    milone_assert((z2_ == 2), 30, 6);
    milone_assert((z3_ == 3), 31, 6);
    milone_assert((z5_ == 5), 32, 6);
    milone_assert((z7_ == 7), 33, 6);
    match_2 = 0;
    goto end_match_13;
next_14:;
    milone_assert(false, 35, 9);
    match_2 = 0;
    goto end_match_13;
next_15:;
end_match_13:;
    return 0;
}

int milone_main() {
    char call_ = nilTest_(0);
    char call_1 = cons1Test_(0);
    char call_2 = cons2Test_(0);
    char call_3 = literalTest_(0);
    return 0;
}
