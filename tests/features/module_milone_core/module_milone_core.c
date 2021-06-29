#include "milone.h"

struct IntList;

struct IntList;

bool isEmpty_(struct IntList const*);

char assertNotEmpty_(struct IntList const* xs_62);

int milone_main();

struct IntList {
    int head;
    struct IntList const* tail;
};

char assertNotEmpty_(struct IntList const* xs_62) {
    bool call_ = isEmpty_(xs_62);
    milone_assert((!(call_)), 5, 34);
    return 0;
}

int milone_main() {
    struct IntList const* list_ = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_))) = (struct IntList){.head = 1, .tail = NULL};
    char call_1 = assertNotEmpty_(list_);
    return 0;
}
