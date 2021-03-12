#include "milone.h"

struct UnitList;

struct UnitList;

struct UnionX_;

struct RecA_ListList;

struct RecA_;

int milone_main();

struct UnitList {
    char head;
    struct UnitList const* tail;
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
        struct RecA_ListList const* T_2;
    };
};

int milone_main() {
    struct UnitList const* list_ = milone_mem_alloc(1, sizeof(struct UnitList));
    (*(((struct UnitList*)list_))) = (struct UnitList){.head = 0, .tail = NULL};
    char switch_;
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
    struct RecA_ variant_ = (struct RecA_){.discriminant = T_2, .T_2 = NULL};
    struct RecA_ useRecA_ = variant_;
    char match_;
    if ((!((!(useRecA_.T_2))))) goto next_5;
    match_ = 0;
    goto end_match_4;
next_5:;
    milone_assert(false, 26, 9);
    match_ = 0;
    goto end_match_4;
next_6:;
end_match_4:;
    return 0;
}
