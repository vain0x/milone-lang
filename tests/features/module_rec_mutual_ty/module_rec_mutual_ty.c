#include "milone.h"

enum UnionA_Tag;

struct UnionA_;

struct UnionA_List;

enum UnionB_Tag;

struct UnionB_;

enum UnionX_Tag;

struct UnionX_;

enum RecB_Tag;

struct RecB_;

struct RecB_List;

enum RecA_Tag;

struct RecA_;

int main();

enum UnionA_Tag {
    T_3,
};

struct UnionA_ {
    enum UnionA_Tag tag;
};

struct UnionA_List {
    struct UnionA_ head;
    struct UnionA_List const* tail;
};

enum UnionB_Tag {
    T_,
};

struct UnionB_ {
    enum UnionB_Tag tag;
    union {
        struct UnionA_List const* T_;
    };
};

enum UnionX_Tag {
    VariantX_,
    VariantY_,
};

struct UnionX_ {
    enum UnionX_Tag tag;
};

enum RecB_Tag {
    T_1,
};

struct RecB_ {
    enum RecB_Tag tag;
    union {
        void const* T_1;
    };
};

struct RecB_List {
    struct RecB_ head;
    struct RecB_List const* tail;
};

enum RecA_Tag {
    T_2,
};

struct RecA_ {
    enum RecA_Tag tag;
    union {
        struct RecB_List const* T_2;
    };
};

int main() {
    struct UnionA_List const* list_ = milone_mem_alloc(1, sizeof(struct UnionA_List));
    (*(((struct UnionA_List*)list_))) = (struct UnionA_List){.head = (struct UnionA_){.tag = T_3}, .tail = NULL};
    struct UnionB_ variant_ = (struct UnionB_){.tag = T_, .T_ = list_};
    int switch_;
    switch ((struct UnionX_){.tag = VariantY_}.tag) {
        case VariantX_:
            goto clause_2;

        default:
            goto clause_3;
    }
clause_2:;
    milone_assert(false, 19, 6);
    switch_ = 0;
    goto switch_next_1;
clause_3:;
    switch_ = 0;
    goto switch_next_1;
switch_next_1:;
    struct RecA_ variant_1 = (struct RecA_){.tag = T_2, .T_2 = NULL};
    struct RecA_ useRecA_ = variant_1;
    int match_;
    if ((!((!(useRecA_.T_2))))) goto next_5;
    match_ = 0;
    goto end_match_4;
next_5:;
    milone_assert(false, 25, 9);
    match_ = 0;
    goto end_match_4;
next_6:;
end_match_4:;
    return 0;
}
