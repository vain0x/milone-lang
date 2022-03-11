#include <milone.h>

struct IntList;

struct IntList;

bool MiloneCore_List_IntListBoolFun1_isEmpty(struct IntList const* );

void module_milone_core_module_milone_core_IntListUnitFun1_assertNotEmpty(struct IntList const* xs_);

int main(int argc, char** argv);

struct IntList {
    int head;
    struct IntList const* tail;
};

void module_milone_core_module_milone_core_IntListUnitFun1_assertNotEmpty(struct IntList const* xs_) {
    bool call_;
    call_ = MiloneCore_List_IntListBoolFun1_isEmpty(xs_);
    milone_assert((!(call_)), (struct String){.str = "module_milone_core/module_milone_core.milone", .len = 44}, 5, 34);
    return;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    struct IntList const* list_;
    list_ = ((struct IntList const*)milone_mem_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_))) = (struct IntList){.head = 1, .tail = NULL};
    module_milone_core_module_milone_core_IntListUnitFun1_assertNotEmpty(list_);
    return 0;
}
