#include "milone.h"

struct IntWrapper_;

char record_inference_Program_letWithTypeAscriptionCase(int n_);

char record_inference_Program_typeAscriptionExprCase(int n_1);

char record_inference_Program_matchExprCase(int n_2);

int milone_main();

struct IntWrapper_ {
    int t0;
};

char record_inference_Program_letWithTypeAscriptionCase(int n_) {
    struct IntWrapper_ IntWrapper_ = (struct IntWrapper_){.t0 = n_};
    struct IntWrapper_ w_ = IntWrapper_;
    milone_assert((w_.t0 == n_), 10, 2);
    return 0;
}

char record_inference_Program_typeAscriptionExprCase(int n_1) {
    struct IntWrapper_ IntWrapper_1 = (struct IntWrapper_){.t0 = n_1};
    milone_assert((IntWrapper_1.t0 == n_1), 13, 2);
    return 0;
}

char record_inference_Program_matchExprCase(int n_2) {
    struct IntWrapper_ switch_;
    switch (n_2) {
        case 5:
            goto clause_2;

        default:
            goto clause_3;
    }
clause_2:;
    struct IntWrapper_ IntWrapper_2 = (struct IntWrapper_){.t0 = 0};
    switch_ = IntWrapper_2;
    goto switch_next_1;
clause_3:;
    exit(1);
switch_next_1:;
    struct IntWrapper_ t_ = switch_;
    milone_assert((t_.t0 == 0), 21, 2);
    return 0;
}

int milone_main() {
    char call_ = record_inference_Program_letWithTypeAscriptionCase(2);
    char call_1 = record_inference_Program_typeAscriptionExprCase(3);
    char call_2 = record_inference_Program_matchExprCase(5);
    return 0;
}
