#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct IntList;

struct StringList;

struct IntList;

struct StringList;

int ty_ascribe_ty_ascribe_main_f(int x_);

int ty_ascribe_ty_ascribe_main_g(int x_1);

int main(int argc, char** argv);

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

int main(int argc, char** argv) {
    milone_start(argc, argv);
    int zero_;
    struct IntList const* xs_;
    struct StringList const* ys_;
    int call_;
    int call_1;
    struct IntList const* list_;
    struct StringList const* list_1;
    call_ = ty_ascribe_ty_ascribe_main_f(1);
    call_1 = ty_ascribe_ty_ascribe_main_g(1);
    zero_ = (call_ - call_1);
    list_ = ((struct IntList const*)milone_region_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_))) = (struct IntList){.head = 1, .tail = NULL};
    xs_ = list_;
    list_1 = ((struct StringList const*)milone_region_alloc(1, sizeof(struct StringList)));
    (*(((struct StringList*)list_1))) = (struct StringList){.head = (struct String){.ptr = "a", .len = 1}, .tail = NULL};
    ys_ = list_1;
    return zero_;
}
