#include "milone.h"

struct Int32X4_;

struct Int32X32_;

int milone_main(void);

struct Int32X4_ {
    int t0;
    int t1;
    int t2;
    int t3;
};

struct Int32X32_ {
    struct Int32X4_ t0;
    struct Int32X4_ t1;
    struct Int32X4_ t2;
    struct Int32X4_ t3;
};

struct Int32X4_ records_c_repr_Program_int32X4Zero;

extern struct Int32X4_ records_c_repr_Program_int32X4Zero;

struct Int32X32_ records_c_repr_Program_int32X32Zero;

extern struct Int32X32_ records_c_repr_Program_int32X32Zero;

int milone_main(void) {
    struct Int32X4_ Int32X4_ = (struct Int32X4_){.t0 = 0, .t1 = 0, .t2 = 0, .t3 = 0};
    records_c_repr_Program_int32X4Zero = Int32X4_;
    struct Int32X32_ Int32X32_ = (struct Int32X32_){.t0 = records_c_repr_Program_int32X4Zero, .t1 = records_c_repr_Program_int32X4Zero, .t2 = records_c_repr_Program_int32X4Zero, .t3 = records_c_repr_Program_int32X4Zero};
    records_c_repr_Program_int32X32Zero = Int32X32_;
    milone_assert((records_c_repr_Program_int32X32Zero.t0.t0 == 0), 24, 2);
    return 0;
}
