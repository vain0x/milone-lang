#include "milone.h"

struct IntList;

bool isEmpty_1(struct IntList const* xs_1);

int assertNotEmpty_1(struct IntList const* xs_);

int main();

struct IntList {
    int head;
    struct IntList const* tail;
};

bool isEmpty_1(struct IntList const* xs_1) {
    bool if_;
    if ((!(xs_1))) {
        goto nil_cl_2;
    } else {
        goto cons_cl_3;
    }
nil_cl_2:;
    if_ = true;
    goto if_next_1;
cons_cl_3:;
    if_ = false;
    goto if_next_1;
if_next_1:;
    return if_;
}

int assertNotEmpty_1(struct IntList const* xs_) {
    bool call_ = isEmpty_1(xs_);
    milone_assert((!(call_)), 4, 34);
    return 0;
}

int main() {
    struct IntList const* list_ = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_))) = (struct IntList){.head = 1, .tail = NULL};
    int call_1 = assertNotEmpty_1(list_);
    return 0;
}
