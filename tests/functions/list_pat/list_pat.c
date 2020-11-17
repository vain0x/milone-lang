#include "milone.h"

struct IntList;

int main();

struct IntList {
    int head;
    struct IntList* tail;
};

int main() {
    int match_;
    struct IntList* list_1 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_1->head = 2;
    list_1->tail = NULL;
    struct IntList* list_ = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_->head = 1;
    list_->tail = list_1;
    if ((!((!(list_))))) goto next_2;
    milone_assert(0, 3, 4);
    int call_ = 0;
    match_ = 0;
    goto end_match_1;
next_2:;
    if ((!(list_))) goto next_3;
    int x_ = list_->head;
    if ((!(list_->tail))) goto next_3;
    int y_ = list_->tail->head;
    if ((!((!(list_->tail->tail))))) goto next_3;
    int if_;
    if ((x_ != 1)) goto else_5;
    if_ = (y_ == 2);
    goto end_if_6;
else_5:;
    if_ = 0;
end_if_6:;
    milone_assert(if_, 5, 4);
    int call_1 = 0;
    match_ = 0;
    goto end_match_1;
next_3:;
    milone_assert(0, 7, 4);
    int call_2 = 0;
    match_ = 0;
    goto end_match_1;
next_4:;
end_match_1:;
    return 0;
}
