#include "milone.h"

struct IntIntTuple2_;

int sub_(struct IntIntTuple2_ arg_);

int milone_main();

struct IntIntTuple2_ {
    int t0;
    int t1;
};

int sub_(struct IntIntTuple2_ arg_) {
    int x_ = arg_.t0;
    int y_ = arg_.t1;
    return (x_ - y_);
}

int milone_main() {
    struct IntIntTuple2_ IntIntTuple2_ = (struct IntIntTuple2_){.t0 = 8, .t1 = 3};
    int call_ = sub_(IntIntTuple2_);
    return (call_ - 5);
}
