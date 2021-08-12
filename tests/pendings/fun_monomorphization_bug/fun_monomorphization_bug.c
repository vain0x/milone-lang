#include "milone.h"

struct IntIntTuple2_;

void const* myFst_(struct IntIntTuple2_ pair_);

int milone_main(void);

struct IntIntTuple2_ {
    int t0;
    int t1;
};

void const* myFst_(struct IntIntTuple2_ pair_) {
    int x_ = pair_.t0;
    return ((void const*)((intptr_t)x_));
}

int milone_main(void) {
    struct IntIntTuple2_ IntIntTuple2_ = (struct IntIntTuple2_){.t0 = 2, .t1 = 3};
    void const* call_ = myFst_(IntIntTuple2_);
    milone_assert((((int)((intptr_t)call_)) == 2), 17, 2);
    return 0;
}
