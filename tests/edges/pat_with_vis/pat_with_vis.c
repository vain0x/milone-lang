#include <milone.h>

struct IntIntTuple2_;

int main(int argc, char** argv);

void pat_with_vis_pat_with_vis_start(void);

struct IntIntTuple2_ {
    int t0;
    int t1;
};

int pat_with_vis_pat_with_vis_x;

int y_;

int main(int argc, char** argv) {
    milone_start(argc, argv);
    pat_with_vis_pat_with_vis_start();
    milone_assert((pat_with_vis_pat_with_vis_x == 2), (struct String){.str = "pat_with_vis/pat_with_vis.milone", .len = 32}, 7, 2);
    milone_assert((y_ == 3), (struct String){.str = "pat_with_vis/pat_with_vis.milone", .len = 32}, 8, 2);
    return 0;
}

void pat_with_vis_pat_with_vis_start(void) {
    struct IntIntTuple2_ IntIntTuple2_;
    IntIntTuple2_ = (struct IntIntTuple2_){.t0 = 2, .t1 = 3};
    pat_with_vis_pat_with_vis_x = IntIntTuple2_.t0;
    y_ = IntIntTuple2_.t1;
    return;
}
