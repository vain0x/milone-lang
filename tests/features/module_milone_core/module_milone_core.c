#include "milone.h"

struct IntList;

bool isEmpty_1(struct IntList const* xs_1);

char assertNotEmpty_1(struct IntList const* xs_);

struct IntList;

int milone_main();


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

char assertNotEmpty_1(struct IntList const* xs_) {
    bool call_ = isEmpty_1(xs_);
    milone_assert((!(call_)), 5, 34);
    return 0;
}

struct IntList {
    int head;
    struct IntList const* tail;
};

int milone_main() {
    struct IntList const* list_ = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_))) = (struct IntList){.head = 1, .tail = NULL};
    char call_1 = assertNotEmpty_1(list_);
    return 0;
}
