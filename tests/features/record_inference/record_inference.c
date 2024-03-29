#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct IntWrapper_;

void record_inference_record_inference_letWithTypeAscriptionCase(int32_t n_);

void record_inference_record_inference_typeAscriptionExprCase(int32_t n_1);

_Noreturn void MiloneCore_Prelude_exit(int32_t);

void record_inference_record_inference_matchExprCase(int32_t n_2);

int32_t record_inference_record_inference_funAppCase_unwrap(struct IntWrapper_ w_1);

void record_inference_record_inference_funAppCase(int32_t n_3);

int main(int argc, char **argv);

struct IntWrapper_ {
    int32_t t0;
};

void record_inference_record_inference_letWithTypeAscriptionCase(int32_t n_) {
    struct IntWrapper_ w_;
    struct IntWrapper_ IntWrapper_;
    IntWrapper_ = (struct IntWrapper_){.t0 = n_};
    w_ = IntWrapper_;
    if ((w_.t0 != n_)) milone_assert_error("record_inference/record_inference.milone", 10, 2);
    return;
}

void record_inference_record_inference_typeAscriptionExprCase(int32_t n_1) {
    struct IntWrapper_ IntWrapper_1;
    IntWrapper_1 = (struct IntWrapper_){.t0 = n_1};
    if ((IntWrapper_1.t0 != n_1)) milone_assert_error("record_inference/record_inference.milone", 13, 2);
    return;
}

void record_inference_record_inference_matchExprCase(int32_t n_2) {
    struct IntWrapper_ t_;
    struct IntWrapper_ switch_;
    struct IntWrapper_ IntWrapper_2;
    switch (n_2) {
        case 5:
            goto clause_2;

        default:
            goto clause_3;
    }
clause_2:;
    IntWrapper_2 = (struct IntWrapper_){.t0 = 0};
    switch_ = IntWrapper_2;
    goto switch_next_1;
clause_3:;
    MiloneCore_Prelude_exit(1);
    milone_never_error("record_inference/record_inference.milone", 19, 15);
switch_next_1:;
    t_ = switch_;
    if ((t_.t0 != 0)) milone_assert_error("record_inference/record_inference.milone", 21, 2);
    return;
}

int32_t record_inference_record_inference_funAppCase_unwrap(struct IntWrapper_ w_1) {
    return w_1.t0;
}

void record_inference_record_inference_funAppCase(int32_t n_3) {
    struct IntWrapper_ IntWrapper_3;
    int32_t call_;
    IntWrapper_3 = (struct IntWrapper_){.t0 = n_3};
    call_ = record_inference_record_inference_funAppCase_unwrap(IntWrapper_3);
    if ((call_ != 7)) milone_assert_error("record_inference/record_inference.milone", 26, 2);
    return;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    record_inference_record_inference_letWithTypeAscriptionCase(2);
    record_inference_record_inference_typeAscriptionExprCase(3);
    record_inference_record_inference_matchExprCase(5);
    record_inference_record_inference_funAppCase(7);
    return 0;
}
