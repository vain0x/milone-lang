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
    struct IntIntTuple2 _pt_ = tuple_;
    return 0;
}
