#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32Cons;

struct StringCons;

struct Int32Cons;

struct StringCons;

int32_t ty_ascribe_ty_ascribe_main_f(int32_t x_);

int32_t ty_ascribe_ty_ascribe_main_g(int32_t x_1);

int main(int argc, char **argv);

struct Int32Cons {
    int32_t head;
    struct Int32Cons const *tail;
};

struct StringCons {
    struct String head;
    struct StringCons const *tail;
};

int32_t ty_ascribe_ty_ascribe_main_f(int32_t x_) {
    return x_;
}

int32_t ty_ascribe_ty_ascribe_main_g(int32_t x_1) {
    return x_1;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    int32_t zero_;
    struct Int32Cons const *xs_;
    struct StringCons const *ys_;
    int32_t call_;
    int32_t call_1;
    struct Int32Cons const *list_;
    struct StringCons const *list_1;
    call_ = ty_ascribe_ty_ascribe_main_f(1);
    call_1 = ty_ascribe_ty_ascribe_main_g(1);
    zero_ = (call_ - call_1);
    list_ = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_))) = (struct Int32Cons){.head = 1, .tail = NULL};
    xs_ = list_;
    list_1 = ((struct StringCons const *)milone_region_alloc(1, sizeof(struct StringCons)));
    (*(((struct StringCons *)list_1))) = (struct StringCons){.head = (struct String){.ptr = "a", .len = 1}, .tail = NULL};
    ys_ = list_1;
    return zero_;
}
