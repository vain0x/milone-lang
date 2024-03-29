#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32X4_;

struct Int32X32_;

int main(int argc, char **argv);

void records_c_repr_records_c_repr_start(void);

struct Int32X4_ {
    int32_t t0;
    int32_t t1;
    int32_t t2;
    int32_t t3;
};

struct Int32X32_ {
    struct Int32X4_ t0;
    struct Int32X4_ t1;
    struct Int32X4_ t2;
    struct Int32X4_ t3;
};

struct Int32X4_ records_c_repr_records_c_repr_int32X4Zero;

struct Int32X32_ records_c_repr_records_c_repr_int32X32Zero;

int main(int argc, char **argv) {
    milone_start(argc, argv);
    records_c_repr_records_c_repr_start();
    if ((records_c_repr_records_c_repr_int32X32Zero.t0.t0 != 0)) milone_assert_error("records_c_repr/records_c_repr.milone", 24, 2);
    return 0;
}

void records_c_repr_records_c_repr_start(void) {
    struct Int32X4_ Int32X4_;
    struct Int32X32_ Int32X32_;
    Int32X4_ = (struct Int32X4_){.t0 = 0, .t1 = 0, .t2 = 0, .t3 = 0};
    records_c_repr_records_c_repr_int32X4Zero = Int32X4_;
    Int32X32_ = (struct Int32X32_){.t0 = records_c_repr_records_c_repr_int32X4Zero, .t1 = records_c_repr_records_c_repr_int32X4Zero, .t2 = records_c_repr_records_c_repr_int32X4Zero, .t3 = records_c_repr_records_c_repr_int32X4Zero};
    records_c_repr_records_c_repr_int32X32Zero = Int32X32_;
    return;
}
