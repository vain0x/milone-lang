#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct RecA_ListCons;

struct RecA_;

struct UnitCons;

struct UnitCons;

struct UnionX_;

int main(int argc, char **argv);

enum RecA_Discriminant {
    RecA_T,
};

struct RecA_ {
    enum RecA_Discriminant discriminant;
    union {
        struct RecA_ListCons const *RecA_T;
    };
};

struct UnitCons {
    char head;
    struct UnitCons const *tail;
};

enum UnionX_Discriminant {
    UnionX_VariantX,
    UnionX_VariantY,
};

struct UnionX_ {
    enum UnionX_Discriminant discriminant;
};

int main(int argc, char **argv) {
    milone_start(argc, argv);
    struct RecA_ useRecA_;
    struct UnitCons const *list_;
    char switch_;
    struct RecA_ variant_;
    char match_;
    list_ = ((struct UnitCons const *)milone_region_alloc(1, sizeof(struct UnitCons)));
    (*(((struct UnitCons *)list_))) = (struct UnitCons){.head = 0, .tail = NULL};
    switch ((struct UnionX_){.discriminant = UnionX_VariantY}.discriminant) {
        case UnionX_VariantX:
            goto clause_2;

        default:
            goto clause_3;
    }
clause_2:;
    if (true) milone_assert_error("module_rec_mutual_ty/module_rec_mutual_ty.milone", 19, 4);
    switch_ = 0;
    goto switch_next_1;
clause_3:;
    switch_ = 0;
    goto switch_next_1;
switch_next_1:;
    variant_ = (struct RecA_){.discriminant = RecA_T, .RecA_T = NULL};
    useRecA_ = variant_;
    if ((!((!(useRecA_.RecA_T))))) goto next_5;
    match_ = 0;
    goto end_match_4;
next_5:;
    if (true) milone_assert_error("module_rec_mutual_ty/module_rec_mutual_ty.milone", 26, 9);
    match_ = 0;
    goto end_match_4;
next_6:;
end_match_4:;
    return 0;
}
