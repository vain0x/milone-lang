#include "milone.h"

enum UnionA_Tag;

struct UnionA_;

struct UnionA_List;

enum UnionB_Tag;

struct UnionB_;

enum UnionX_Tag;

struct UnionX_;

int main();

enum UnionA_Tag {
    T_1,
};

struct UnionA_ {
    enum UnionA_Tag tag;
};

struct UnionA_List {
    struct UnionA_ head;
    struct UnionA_List* tail;
};

enum UnionB_Tag {
    T_,
};

struct UnionB_ {
    enum UnionB_Tag tag;
    union {
        struct UnionA_List* T_;
    };
};

enum UnionX_Tag {
    VariantX_,
    VariantY_,
};

struct UnionX_ {
    enum UnionX_Tag tag;
};

int main() {
    struct UnionA_List* list_ = milone_mem_alloc(1, sizeof(struct UnionA_List));
    list_->head = (struct UnionA_){.tag = T_1};
    list_->tail = NULL;
    struct UnionB_ variant_ = (struct UnionB_){.tag = T_, .T_ = list_};
    int switch_;
    switch ((struct UnionX_){.tag = VariantY_}.tag) {
        case VariantX_:
            goto clause_2;

        default:
            goto clause_3;
    }
clause_2:;
    milone_assert(false, 18, 4);
    switch_ = 0;
    goto switch_next_1;
clause_3:;
    switch_ = 0;
    goto switch_next_1;
switch_next_1:;
    return 0;
}
