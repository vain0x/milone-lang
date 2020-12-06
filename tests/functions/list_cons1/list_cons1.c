#include "milone.h"

struct IntList;

int main();

struct IntList {
    int head;
    struct IntList const* tail;
};

int main() {
    int match_;
    struct IntList const* list_ = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_))) = (struct IntList){.head = 1, .tail = NULL};
    if ((!(list_))) goto next_2;
    int x1_ = list_->head;
    if ((!((!(list_->tail))))) goto next_2;
    milone_assert((x1_ == 1), 3, 4);
    match_ = 0;
    goto end_match_1;
next_2:;
    milone_assert(false, 5, 4);
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    return 0;
}
