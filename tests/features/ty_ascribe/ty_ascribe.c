#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32List;

struct StringList;

struct Int32List;

struct StringList;

int32_t ty_ascribe_ty_ascribe_main_f(int32_t x_);

int32_t ty_ascribe_ty_ascribe_main_g(int32_t x_1);

int main(int argc, char** argv);

struct Int32List {
    int32_t head;
    struct Int32List const* tail;
};

struct StringList {
    struct String head;
    struct StringList const* tail;
};

int32_t ty_ascribe_ty_ascribe_main_f(int32_t x_) {
    return x_;
}

int32_t ty_ascribe_ty_ascribe_main_g(int32_t x_1) {
    return x_1;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    int32_t zero_;
    struct Int32List const* xs_;
    struct StringList const* ys_;
    int32_t call_;
    int32_t call_1;
    struct Int32List const* list_;
    struct StringList const* list_1;
    call_ = ty_ascribe_ty_ascribe_main_f(1);
    call_1 = ty_ascribe_ty_ascribe_main_g(1);
    zero_ = (call_ - call_1);
    list_ = ((struct Int32List const*)milone_region_alloc(1, sizeof(struct Int32List)));
    (*(((struct Int32List*)list_))) = (struct Int32List){.head = 1, .tail = NULL};
    xs_ = list_;
    list_1 = ((struct StringList const*)milone_region_alloc(1, sizeof(struct StringList)));
    (*(((struct StringList*)list_1))) = (struct StringList){.head = (struct String){.ptr = "a", .len = 1}, .tail = NULL};
    ys_ = list_1;
    return zero_;
}
