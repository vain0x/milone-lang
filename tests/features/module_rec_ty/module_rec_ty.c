#include "milone.h"

struct ObjectList;

enum UnionX_Tag;

struct UnionX_;

int main();

struct ObjectList {
    void* head;
    struct ObjectList* tail;
};

enum UnionX_Tag {
    VariantX_,
    VariantY_,
};

struct UnionX_ {
    enum UnionX_Tag tag;
};

int main() {
    struct ObjectList* list_ = (struct ObjectList*)milone_mem_alloc(1, sizeof(struct ObjectList));
    list_->head = 0;
    list_->tail = NULL;
    void* box_ = (void*)milone_mem_alloc(1, sizeof(struct ObjectList*));
    (*(((struct ObjectList**)box_))) = list_;
    int switch_;
    switch ((struct UnionX_){.tag = VariantY_}.tag) {
       case VariantX_:
          goto clause_2;

       default:
          goto clause_3;
    }
clause_2:;
    milone_assert(0, 18, 4);
    int call_ = 0;
    switch_ = 0;
    goto switch_next_1;
clause_3:;
    switch_ = 0;
    goto switch_next_1;
switch_next_1:;
    return 0;
}
