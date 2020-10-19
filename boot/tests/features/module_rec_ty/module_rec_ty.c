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
        struct UnionA_List** T_;
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
    struct UnionA_List* list_ = (struct UnionA_List*)milone_mem_alloc(1, sizeof(struct UnionA_List));
    list_->head = (struct UnionA_){.tag = T_1};
    list_->tail = NULL;
    struct UnionA_List** payload_ = (struct UnionA_List**)milone_mem_alloc(1, sizeof(struct UnionA_List*));
    (*(((struct UnionA_List**)payload_))) = list_;
    struct UnionB_ variant_ = (struct UnionB_){.tag = T_, .T_ = payload_};
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
