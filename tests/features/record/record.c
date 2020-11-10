#include "milone.h"

struct IntIntTuple2;

int main();

struct IntIntTuple2 {
    int t0;
    int t1;
};

int main() {
    struct IntIntTuple2 tuple_;
    tuple_.t0 = 40;
    tuple_.t1 = 2;
    void* box_ = (void*)milone_mem_alloc(1, sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)box_))) = tuple_;
    void* point_ = box_;
    milone_assert(((*(((struct IntIntTuple2*)point_))).t0 == 40), 7, 2);
    int call_ = 0;
    milone_assert(((*(((struct IntIntTuple2*)point_))).t1 == 2), 8, 2);
    int call_1 = 0;
    return 0;
}
