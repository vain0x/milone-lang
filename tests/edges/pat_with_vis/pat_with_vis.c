#include "milone.h"

struct IntIntTuple2;

int milone_main();

struct IntIntTuple2 {
    int t0;
    int t1;
};

int pat_with_vis_Program_x;

static int y_;

int milone_main() {
    struct IntIntTuple2 tuple_ = (struct IntIntTuple2){.t0 = 2, .t1 = 3};
    pat_with_vis_Program_x = tuple_.t0;
    y_ = tuple_.t1;
    milone_assert((pat_with_vis_Program_x == 2), 7, 2);
    milone_assert((y_ == 3), 8, 2);
    return 0;
}
