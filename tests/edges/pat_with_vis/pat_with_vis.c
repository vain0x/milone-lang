#include "milone.h"

struct IntIntTuple2_;

int milone_main(void);

void pat_with_vis_pat_with_vis__start(void);

struct IntIntTuple2_ {
    int t0;
    int t1;
};

extern int pat_with_vis_Program_x;

extern int y_;

int pat_with_vis_Program_x;

int y_;

int milone_main(void) {
    pat_with_vis_pat_with_vis__start();
    milone_assert((pat_with_vis_Program_x == 2), 7, 2);
    milone_assert((y_ == 3), 8, 2);
    return 0;
}

void pat_with_vis_pat_with_vis__start(void) {
    struct IntIntTuple2_ IntIntTuple2_ = (struct IntIntTuple2_){.t0 = 2, .t1 = 3};
    pat_with_vis_Program_x = IntIntTuple2_.t0;
    y_ = IntIntTuple2_.t1;
    return;
}
