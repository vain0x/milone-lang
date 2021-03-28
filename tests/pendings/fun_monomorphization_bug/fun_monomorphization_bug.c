#include "milone.h"

struct IntIntTuple2;

void const* fst_(struct IntIntTuple2 pair_);

int milone_main();

struct IntIntTuple2 {
    int t0;
    int t1;
};

void const* fst_(struct IntIntTuple2 pair_) {
    int x_ = pair_.t0;
    void const* box_ = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_))) = x_;
    return box_;
}

int milone_main() {
    struct IntIntTuple2 tuple_ = (struct IntIntTuple2){.t0 = 2, .t1 = 3};
    void const* call_ = fst_(tuple_);
    milone_assert(((*(((int const*)call_))) == 2), 17, 2);
    return 0;
}
