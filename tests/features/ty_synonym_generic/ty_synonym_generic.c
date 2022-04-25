#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32Cons;

struct Int32Cons;

struct Int32Cons const *ty_synonym_generic_ty_synonym_generic_UnitInt32ListFun1_newStack(void);

int main(int argc, char **argv);

struct Int32Cons {
    int32_t head;
    struct Int32Cons const *tail;
};

struct Int32Cons const *ty_synonym_generic_ty_synonym_generic_UnitInt32ListFun1_newStack(void) {
    return NULL;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    struct Int32Cons const *_stack;
    struct Int32Cons const *list_;
    struct Int32Cons const *call_;
    call_ = ty_synonym_generic_ty_synonym_generic_UnitInt32ListFun1_newStack();
    list_ = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_))) = (struct Int32Cons){.head = 1, .tail = call_};
    _stack = list_;
    return 0;
}
