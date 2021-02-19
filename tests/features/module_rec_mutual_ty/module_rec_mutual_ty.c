#include "milone.h"

struct UnionA_List;

enum UnionA_Discriminant;

struct UnionA_;

struct UnionA_List;

enum UnionB_Discriminant;

struct UnionB_;

enum UnionX_Discriminant;

struct UnionX_;

struct RecB_List;

enum RecA_Discriminant;

struct RecA_;

int milone_main();


enum UnionA_Discriminant {
    T_3,
};

struct UnionA_ {
    enum UnionA_Discriminant discriminant;
};

struct UnionA_List {
    struct UnionA_ head;
    struct UnionA_List const* tail;
};

enum UnionB_Discriminant {
    T_,
};

struct UnionB_ {
    enum UnionB_Discriminant discriminant;
    union {
        struct UnionA_List const* T_;
    };
};

enum UnionX_Discriminant {
    VariantX_,
    VariantY_,
};

struct UnionX_ {
    enum UnionX_Discriminant discriminant;
};


enum RecA_Discriminant {
    T_2,
};

struct RecA_ {
    enum RecA_Discriminant discriminant;
    union {
        struct RecB_List const* T_2;
    };
};

int milone_main() {
    struct UnionA_List const* list_ = milone_mem_alloc(1, sizeof(struct UnionA_List));
    (*(((struct UnionA_List*)list_))) = (struct UnionA_List){.head = (struct UnionA_){.discriminant = T_3}, .tail = NULL};
    struct UnionB_ variant_ = (struct UnionB_){.discriminant = T_, .T_ = list_};
    int switch_;
    switch ((struct UnionX_){.discriminant = VariantY_}.discriminant) {
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
    struct RecA_ variant_1 = (struct RecA_){.discriminant = T_2, .T_2 = NULL};
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
