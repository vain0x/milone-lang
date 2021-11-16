#include "milone.h"

struct IntList;

struct IntList;

struct StringList;

struct StringList;

int ty_ascribe_ty_ascribe_main_f(int x_);

int ty_ascribe_ty_ascribe_main_g(int x_1);

int milone_main(void);

struct IntList {
    int head;
    struct IntList const* tail;
};

struct StringList {
    struct String head;
    struct StringList const* tail;
};

int ty_ascribe_ty_ascribe_main_f(int x_) {
    return x_;
}

int ty_ascribe_ty_ascribe_main_g(int x_1) {
    return x_1;
}

int milone_main(void) {
    int call_ = ty_ascribe_ty_ascribe_main_f(1);
    int call_1 = ty_ascribe_ty_ascribe_main_g(1);
    int zero_ = (call_ - call_1);
    struct IntList const* list_ = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_))) = (struct IntList){.head = 1, .tail = NULL};
    struct IntList const* xs_ = list_;
    struct StringList const* list_1 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_1))) = (struct StringList){.head = (struct String){.str = "a", .len = 1}, .tail = NULL};
    struct StringList const* ys_ = list_1;
    return zero_;
}
