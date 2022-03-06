#include <milone.h>

struct IntWrapper_;

void record_inference_record_inference_letWithTypeAscriptionCase(int n_);

void record_inference_record_inference_typeAscriptionExprCase(int n_1);

void record_inference_record_inference_matchExprCase(int n_2);

int record_inference_record_inference_funAppCase_unwrap(struct IntWrapper_ w_1);

void record_inference_record_inference_funAppCase(int n_3);

int main(int argc, char** argv);

struct IntWrapper_ {
    int t0;
};

void record_inference_record_inference_letWithTypeAscriptionCase(int n_) {
    struct IntWrapper_ IntWrapper_ = (struct IntWrapper_){.t0 = n_};
    struct IntWrapper_ w_ = IntWrapper_;
    milone_assert((w_.t0 == n_), (struct String){.str = "record_inference/record_inference.milone", .len = 40}, 10, 2);
    return;
}

void record_inference_record_inference_typeAscriptionExprCase(int n_1) {
    struct IntWrapper_ IntWrapper_1 = (struct IntWrapper_){.t0 = n_1};
    milone_assert((IntWrapper_1.t0 == n_1), (struct String){.str = "record_inference/record_inference.milone", .len = 40}, 13, 2);
    return;
}

void record_inference_record_inference_matchExprCase(int n_2) {
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
    milone_assert((t_.t0 == 0), (struct String){.str = "record_inference/record_inference.milone", .len = 40}, 21, 2);
    return;
}

int record_inference_record_inference_funAppCase_unwrap(struct IntWrapper_ w_1) {
    return w_1.t0;
}

void record_inference_record_inference_funAppCase(int n_3) {
    struct IntWrapper_ IntWrapper_3 = (struct IntWrapper_){.t0 = n_3};
    int call_ = record_inference_record_inference_funAppCase_unwrap(IntWrapper_3);
    milone_assert((call_ == 7), (struct String){.str = "record_inference/record_inference.milone", .len = 40}, 26, 2);
    return;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    record_inference_record_inference_letWithTypeAscriptionCase(2);
    record_inference_record_inference_typeAscriptionExprCase(3);
    record_inference_record_inference_matchExprCase(5);
    record_inference_record_inference_funAppCase(7);
    return 0;
}
