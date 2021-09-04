#include "milone.h"

struct IntUnitTuple2_;

struct IntIntTuple2_;

void const* g_(void const* pair_1);

void const* myFst_(struct IntIntTuple2_ pair_);

int milone_main(void);

struct IntUnitTuple2_ {
    int t0;
    char t1;
};

struct IntIntTuple2_ {
    int t0;
    int t1;
};

void const* g_(void const* pair_1) {
    int x_ = (*(((struct IntUnitTuple2_ const*)pair_1))).t0;
    return ((void const*)((intptr_t)x_));
}

void const* myFst_(struct IntIntTuple2_ pair_) {
    void const* box_ = milone_mem_alloc(1, sizeof(struct IntIntTuple2_));
    (*(((struct IntIntTuple2_*)box_))) = pair_;
    void const* call_ = g_(box_);
    return call_;
}

int milone_main(void) {
    struct IntIntTuple2_ IntIntTuple2_ = (struct IntIntTuple2_){.t0 = 2, .t1 = 3};
    void const* call_1 = myFst_(IntIntTuple2_);
    milone_assert((((int)((intptr_t)call_1)) == 2), 14, 2);
    return 0;
}
