#include "milone.h"

struct IntIntTuple2;

static int x_;

static int y_;

int milone_main();

struct IntIntTuple2 {
    int t0;
    int t1;
};

int milone_main() {
    struct IntIntTuple2 tuple_ = (struct IntIntTuple2){.t0 = 2, .t1 = 3};
    x_ = tuple_.t0;
    y_ = tuple_.t1;
    milone_assert((x_ == 2), 7, 2);
    milone_assert((y_ == 3), 8, 2);
    return 0;
}
