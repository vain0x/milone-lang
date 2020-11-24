#include "milone.h"

struct IntWrapper_;

int letWithTypeAnnotationCase_(int n_);

int typeAnnotationExprCase_(int n_1);

int matchExprCase_(int n_2);

int main();

struct IntWrapper_ {
    int Value;
};

int letWithTypeAnnotationCase_(int n_) {
    struct IntWrapper_ IntWrapper_;
    IntWrapper_.Value = n_;
    void* box_ = (void*)milone_mem_alloc(1, sizeof(struct IntWrapper_));
    (*(((struct IntWrapper_*)box_))) = IntWrapper_;
    void* w_ = box_;
    milone_assert(((*(((struct IntWrapper_*)w_))).Value == n_), 10, 2);
    int call_ = 0;
    return 0;
}

int typeAnnotationExprCase_(int n_1) {
    struct IntWrapper_ IntWrapper_1;
    IntWrapper_1.Value = n_1;
    void* box_1 = (void*)milone_mem_alloc(1, sizeof(struct IntWrapper_));
    (*(((struct IntWrapper_*)box_1))) = IntWrapper_1;
    milone_assert(((*(((struct IntWrapper_*)box_1))).Value == n_1), 13, 2);
    int call_1 = 0;
    return 0;
}

int matchExprCase_(int n_2) {
    void* switch_;
    switch (n_2) {
        case 5:
            goto clause_2;

        default:
            goto clause_3;
    }
clause_2:;
    struct IntWrapper_ IntWrapper_2;
    IntWrapper_2.Value = 0;
    void* box_2 = (void*)milone_mem_alloc(1, sizeof(struct IntWrapper_));
    (*(((struct IntWrapper_*)box_2))) = IntWrapper_2;
    switch_ = box_2;
    goto switch_next_1;
clause_3:;
    exit(1);
    switch_ = NULL;
    goto switch_next_1;
switch_next_1:;
    void* t_ = switch_;
    milone_assert(((*(((struct IntWrapper_*)t_))).Value == 0), 21, 2);
    int call_2 = 0;
    return 0;
}

int main() {
    int call_3 = letWithTypeAnnotationCase_(2);
    int call_4 = typeAnnotationExprCase_(3);
    int call_5 = matchExprCase_(5);
    return 0;
}
