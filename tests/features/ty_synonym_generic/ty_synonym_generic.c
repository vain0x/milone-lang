#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32List;

struct Int32List;

struct Int32List const* ty_synonym_generic_ty_synonym_generic_UnitInt32ListFun1_newStack(void);

int main(int argc, char** argv);

struct Int32List {
    int32_t head;
    struct Int32List const* tail;
};

struct Int32List const* ty_synonym_generic_ty_synonym_generic_UnitInt32ListFun1_newStack(void) {
    return NULL;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    struct Int32List const* _stack;
    struct Int32List const* list_;
    struct Int32List const* call_;
    call_ = ty_synonym_generic_ty_synonym_generic_UnitInt32ListFun1_newStack();
    list_ = ((struct Int32List const*)milone_region_alloc(1, sizeof(struct Int32List)));
    (*(((struct Int32List*)list_))) = (struct Int32List){.head = 1, .tail = call_};
    _stack = list_;
    return 0;
}
