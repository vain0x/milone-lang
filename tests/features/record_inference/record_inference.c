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
    struct IntTuple1 w_ = tuple_;
    milone_assert((w_.t0 == n_), 10, 2);
    int call_ = 0;
    return 0;
}

int typeAnnotationExprCase_(int n_1) {
    struct IntTuple1 tuple_1;
    tuple_1.t0 = n_1;
    milone_assert((tuple_1.t0 == n_1), 13, 2);
    int call_1 = 0;
    return 0;
}

int matchExprCase_(int n_2) {
    struct IntTuple1 match_;
    if ((n_2 != 5)) goto next_2;
    struct IntTuple1 tuple_2;
    tuple_2.t0 = 0;
    match_ = tuple_2;
    goto end_match_1;
next_2:;
    exit(1);
    match_ = ((struct IntTuple1){});
    goto end_match_1;
next_3:;
end_match_1:;
    struct IntTuple1 t_ = match_;
    milone_assert((t_.t0 == 0), 21, 2);
    int call_2 = 0;
    return 0;
}

int main() {
    int call_3 = letWithTypeAnnotationCase_(2);
    int call_4 = typeAnnotationExprCase_(3);
    int call_5 = matchExprCase_(5);
    return 0;
}
