#include "milone.h"

struct IntIntTuple2;

void const* myFst_(struct IntIntTuple2 pair_);

int milone_main();

struct IntIntTuple2 {
    int t0;
    int t1;
};

void const* myFst_(struct IntIntTuple2 pair_) {
    int x_ = pair_.t0;
    return ((void const*)((intptr_t)x_));
}

int milone_main() {
    struct IntIntTuple2 tuple_ = (struct IntIntTuple2){.t0 = 2, .t1 = 3};
    void const* call_ = myFst_(tuple_);
    milone_assert((((int)((intptr_t)call_)) == 2), 17, 2);
    return 0;
}
