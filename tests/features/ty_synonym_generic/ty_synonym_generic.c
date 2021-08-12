#include "milone.h"

struct IntList;

struct IntList;

struct IntList const* newStack_(void);

int milone_main(void);

struct IntList {
    int head;
    struct IntList const* tail;
};

struct IntList const* newStack_(void) {
    return NULL;
}

int milone_main(void) {
    struct IntList const* call_ = newStack_();
    struct IntList const* list_ = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_))) = (struct IntList){.head = 1, .tail = call_};
    struct IntList const* _stack = list_;
    return 0;
}
