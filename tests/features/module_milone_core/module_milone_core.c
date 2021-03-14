#include "milone.h"

struct IntList;

struct IntList;

bool isEmpty_1(struct IntList const* xs_);

char assertNotEmpty_1(struct IntList const* xs_60);

int milone_main();

struct IntList {
    int head;
    struct IntList const* tail;
};

bool isEmpty_1(struct IntList const* xs_) {
    bool if_;
    if ((!(xs_))) {
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

char assertNotEmpty_1(struct IntList const* xs_60) {
    bool call_ = isEmpty_1(xs_60);
    milone_assert((!(call_)), 5, 34);
    return 0;
}

int milone_main() {
    struct IntList const* list_ = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_))) = (struct IntList){.head = 1, .tail = NULL};
    char call_1 = assertNotEmpty_1(list_);
    return 0;
}
