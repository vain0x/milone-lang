#include "milone.h"

struct IntTuple1;

int letWithTypeAnnotationCase_(int n_);

int typeAnnotationExprCase_(int n_1);

int matchExprCase_(int n_2);

int main();

struct IntTuple1 {
    int t0;
};

int letWithTypeAnnotationCase_(int n_) {
    struct IntTuple1 tuple_;
    tuple_.t0 = n_;
    void* box_ = (void*)milone_mem_alloc(1, sizeof(struct IntTuple1));
    (*(((struct IntTuple1*)box_))) = tuple_;
    void* w_ = box_;
    milone_assert(((*(((struct IntTuple1*)w_))).t0 == n_), 10, 2);
    int call_ = 0;
    return 0;
}

int typeAnnotationExprCase_(int n_1) {
    struct IntTuple1 tuple_1;
    tuple_1.t0 = n_1;
    void* box_1 = (void*)milone_mem_alloc(1, sizeof(struct IntTuple1));
    (*(((struct IntTuple1*)box_1))) = tuple_1;
    milone_assert(((*(((struct IntTuple1*)box_1))).t0 == n_1), 13, 2);
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
    struct IntTuple1 tuple_2;
    tuple_2.t0 = 0;
    void* box_2 = (void*)milone_mem_alloc(1, sizeof(struct IntTuple1));
    (*(((struct IntTuple1*)box_2))) = tuple_2;
    switch_ = box_2;
    goto switch_next_1;
clause_3:;
    exit(1);
    switch_ = NULL;
    goto switch_next_1;
switch_next_1:;
    void* t_ = switch_;
    milone_assert(((*(((struct IntTuple1*)t_))).t0 == 0), 21, 2);
    int call_2 = 0;
    return 0;
}

int main() {
    int call_3 = letWithTypeAnnotationCase_(2);
    int call_4 = typeAnnotationExprCase_(3);
    int call_5 = matchExprCase_(5);
    return 0;
}
