#include <milone.h>

struct IntList;

struct IntList;

struct IntList const* ty_synonym_generic_ty_synonym_generic_UnitIntListFun1_newStack(void);

int main(int argc, char** argv);

struct IntList {
    int head;
    struct IntList const* tail;
};

struct IntList const* ty_synonym_generic_ty_synonym_generic_UnitIntListFun1_newStack(void) {
    return NULL;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    struct IntList const* _stack;
    struct IntList const* list_;
    struct IntList const* call_;
    call_ = ty_synonym_generic_ty_synonym_generic_UnitIntListFun1_newStack();
    list_ = ((struct IntList const*)milone_mem_alloc(1, sizeof(struct IntList)));
    (*(((struct IntList*)list_))) = (struct IntList){.head = 1, .tail = call_};
    _stack = list_;
    return 0;
}
