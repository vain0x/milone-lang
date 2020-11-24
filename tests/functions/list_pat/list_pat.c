#include "milone.h"

struct IntList;

int basicCase_1(struct IntList* xs_);

int complicatedCase_(struct IntList* xs_1);

int main();

struct IntList {
    int head;
    struct IntList* tail;
};

int basicCase_1(struct IntList* xs_) {
    int if_;
    if ((!(xs_))) {
        goto nil_cl_2;
    } else {
        goto cons_cl_3;
    }
nil_cl_2:;
    milone_assert(0, 2, 10);
    if_ = 0;
    goto if_next_1;
cons_cl_3:;
    if_ = 0;
    goto if_next_1;
if_next_1:;
    return 0;
}

int complicatedCase_(struct IntList* xs_1) {
    int match_;
    if ((!((!(xs_1))))) goto next_5;
    milone_assert(0, 7, 10);
    match_ = 0;
    goto end_match_4;
next_5:;
    if ((!(xs_1))) goto next_6;
    int x_ = xs_1->head;
    if ((!(xs_1->tail))) goto next_6;
    int y_ = xs_1->tail->head;
    if ((!((!(xs_1->tail->tail))))) goto next_6;
    int if_1;
    if ((x_ == 1)) {
        goto then_9;
    } else {
        goto else_10;
    }
then_9:;
    if_1 = (y_ == 2);
    goto if_next_8;
else_10:;
    if_1 = 0;
    goto if_next_8;
if_next_8:;
    milone_assert(if_1, 8, 14);
    match_ = 0;
    goto end_match_4;
next_6:;
    milone_assert(0, 9, 9);
    match_ = 0;
    goto end_match_4;
next_7:;
end_match_4:;
    return 0;
}

int main() {
    struct IntList* list_ = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_->head = 1;
    list_->tail = NULL;
    int call_ = basicCase_1(list_);
    struct IntList* list_2 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_2->head = 2;
    list_2->tail = NULL;
    struct IntList* list_1 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_1->head = 1;
    list_1->tail = list_2;
    int call_1 = complicatedCase_(list_1);
    return 0;
}
