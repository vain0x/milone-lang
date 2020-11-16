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
    int match_;
    if (((struct UnionX_){.tag = VariantY_}.tag != VariantX_)) goto next_2;
    milone_assert(0, 18, 4);
    int call_ = 0;
    match_ = 0;
    goto end_match_1;
next_2:;
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    return 0;
}
