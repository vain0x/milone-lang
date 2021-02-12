#include "milone.h"

int f_(int x_);

int g_(int x_1);

struct IntList;

struct StringList;

int milone_main();

int f_(int x_) {
    return x_;
}

int g_(int x_1) {
    return x_1;
}

struct IntList {
    int head;
    struct IntList const* tail;
};

struct StringList {
    struct String head;
    struct StringList const* tail;
};

int milone_main() {
    int call_ = f_(1);
    int call_1 = g_(1);
    int zero_ = (call_ - call_1);
    struct IntList const* list_ = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_))) = (struct IntList){.head = 1, .tail = NULL};
    struct IntList const* xs_ = list_;
    struct StringList const* list_1 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_1))) = (struct StringList){.head = (struct String){.str = "a", .len = 1}, .tail = NULL};
    struct StringList const* ys_ = list_1;
    return zero_;
}
