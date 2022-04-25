#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32Int32Tuple2_;

int main(int argc, char **argv);

void pat_with_vis_pat_with_vis_start(void);

struct Int32Int32Tuple2_ {
    int32_t t0;
    int32_t t1;
};

int32_t pat_with_vis_pat_with_vis_x;

int32_t y_;

int main(int argc, char **argv) {
    milone_start(argc, argv);
    pat_with_vis_pat_with_vis_start();
    if ((pat_with_vis_pat_with_vis_x != 2)) milone_assert_error("pat_with_vis/pat_with_vis.milone", 7, 2);
    if ((y_ != 3)) milone_assert_error("pat_with_vis/pat_with_vis.milone", 8, 2);
    return 0;
}

void pat_with_vis_pat_with_vis_start(void) {
    struct Int32Int32Tuple2_ Int32Int32Tuple2_;
    Int32Int32Tuple2_ = (struct Int32Int32Tuple2_){.t0 = 2, .t1 = 3};
    pat_with_vis_pat_with_vis_x = Int32Int32Tuple2_.t0;
    y_ = Int32Int32Tuple2_.t1;
    return;
}
