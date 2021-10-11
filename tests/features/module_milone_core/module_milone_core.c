#include "milone.h"

struct IntList;

struct IntList;

bool isEmpty_(struct IntList const* );

void assertNotEmpty_(struct IntList const* xs_64);

int milone_main(void);

struct IntList {
    int head;
    struct IntList const* tail;
};

void assertNotEmpty_(struct IntList const* xs_64) {
    bool call_ = isEmpty_(xs_64);
    milone_assert((!(call_)), 5, 34);
    return;
}

int milone_main(void) {
    struct IntList const* list_ = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_))) = (struct IntList){.head = 1, .tail = NULL};
    assertNotEmpty_(list_);
    return 0;
}
