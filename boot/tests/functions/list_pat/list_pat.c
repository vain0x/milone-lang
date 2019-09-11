#include "milone.h"

struct IntList;

int main();

struct IntList {
    int head;
    struct IntList* tail;
};

int main() {
    int match_;
    struct IntList* list_1 = (struct IntList*)malloc(sizeof(struct IntList));
    list_1->head = 2;
    list_1->tail = NULL;
    struct IntList* list_ = (struct IntList*)malloc(sizeof(struct IntList));
    list_->head = 1;
    list_->tail = list_1;
    if (!((!(list_)))) goto next_2;
    exit(1);
    match_ = 0;
    goto end_match_1;
next_2:;
    if (!((!((!(list_)))))) goto next_3;
    int x_ = list_->head;
    if (!((!((!(list_->tail)))))) goto next_3;
    int y_ = list_->tail->head;
    if (!((!(list_->tail->tail)))) goto next_3;
    int match_1;
    if (!(((x_ == 1) == 1))) goto next_6;
    match_1 = (y_ == 2);
    goto end_match_5;
next_6:;
    if (!(((x_ == 1) == 0))) goto next_7;
    match_1 = 0;
    goto end_match_5;
next_7:;
    exit(1);
end_match_5:;
    milone_assert(match_1);
    int call_ = 0;
    match_ = 0;
    goto end_match_1;
next_3:;
    exit(1);
    match_ = 0;
    goto end_match_1;
next_4:;
end_match_1:;
    return 0;
}
