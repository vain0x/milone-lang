#include "milone.h"

struct IntList;

int isEmpty_1(struct IntList* xs_1);

int assertNotEmpty_1(struct IntList* xs_);

int main();

struct IntList {
    int head;
    struct IntList* tail;
};

int isEmpty_1(struct IntList* xs_1) {
    int if_;
    if ((!(xs_1))) {
        goto nil_cl_2;
    } else {
        goto cons_cl_3;
    }
nil_cl_2:;
    if_ = 1;
    goto if_next_1;
cons_cl_3:;
    if_ = 0;
    goto if_next_1;
if_next_1:;
    return if_;
}

int assertNotEmpty_1(struct IntList* xs_) {
    int call_ = isEmpty_1(xs_);
    milone_assert((!(call_)), 4, 34);
    return 0;
}

int main() {
    struct IntList* list_ = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_->head = 1;
    list_->tail = NULL;
    int call_1 = assertNotEmpty_1(list_);
    return 0;
}
