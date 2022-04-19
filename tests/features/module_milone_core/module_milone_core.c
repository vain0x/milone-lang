#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32List;

struct Int32List;

bool MiloneCore_List_Int32ListBoolFun1_isEmpty(struct Int32List const* );

void module_milone_core_module_milone_core_Int32ListUnitFun1_assertNotEmpty(struct Int32List const* xs_);

int main(int argc, char** argv);

struct Int32List {
    int32_t head;
    struct Int32List const* tail;
};

void module_milone_core_module_milone_core_Int32ListUnitFun1_assertNotEmpty(struct Int32List const* xs_) {
    bool call_;
    call_ = MiloneCore_List_Int32ListBoolFun1_isEmpty(xs_);
    milone_assert((!(call_)), (struct String){.ptr = "module_milone_core/module_milone_core.milone", .len = 44}, 5, 34);
    return;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    struct Int32List const* list_;
    list_ = ((struct Int32List const*)milone_region_alloc(1, sizeof(struct Int32List)));
    (*(((struct Int32List*)list_))) = (struct Int32List){.head = 1, .tail = NULL};
    module_milone_core_module_milone_core_Int32ListUnitFun1_assertNotEmpty(list_);
    return 0;
}
