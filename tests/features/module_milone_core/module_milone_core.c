#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32Cons;

struct Int32Cons;

bool MiloneCore_List_Int32ListBoolFun1_isEmpty(struct Int32Cons const *);

void module_milone_core_module_milone_core_Int32ListUnitFun1_assertNotEmpty(struct Int32Cons const *xs_);

int main(int argc, char **argv);

struct Int32Cons {
    int32_t head;
    struct Int32Cons const *tail;
};

void module_milone_core_module_milone_core_Int32ListUnitFun1_assertNotEmpty(struct Int32Cons const *xs_) {
    bool call_;
    call_ = MiloneCore_List_Int32ListBoolFun1_isEmpty(xs_);
    if (call_) milone_assert_error("module_milone_core/module_milone_core.milone", 5, 34);
    return;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    struct Int32Cons const *list_;
    list_ = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_))) = (struct Int32Cons){.head = 1, .tail = NULL};
    module_milone_core_module_milone_core_Int32ListUnitFun1_assertNotEmpty(list_);
    return 0;
}
