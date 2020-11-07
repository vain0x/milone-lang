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
    struct IntIntTuple2 point_ = tuple_;
    milone_assert((point_.t0 == 40), 7, 2);
    int call_ = 0;
    milone_assert((point_.t1 == 2), 8, 2);
    int call_1 = 0;
    return 0;
}
