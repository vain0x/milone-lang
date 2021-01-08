#include "milone.h"

struct IntList;

struct IntList const* newStack_1(int arg_);

int milone_main();

struct IntList {
    int head;
    struct IntList const* tail;
};

struct IntList const* newStack_1(int arg_) {
    return NULL;
}

int milone_main() {
    struct IntList const* call_ = newStack_1(0);
    struct IntList const* list_ = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_))) = (struct IntList){.head = 1, .tail = call_};
    struct IntList const* _stack_ = list_;
    return 0;
}
