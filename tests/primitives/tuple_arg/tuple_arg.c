#include "milone.h"

struct IntIntTuple2_;

int tuple_arg_tuple_arg_main_IntIntTuple2IntFun1_sub(struct IntIntTuple2_ arg_);

int milone_main(void);

struct IntIntTuple2_ {
    int t0;
    int t1;
};

int tuple_arg_tuple_arg_main_IntIntTuple2IntFun1_sub(struct IntIntTuple2_ arg_) {
    int x_ = arg_.t0;
    int y_ = arg_.t1;
    return (x_ - y_);
}

int milone_main(void) {
    struct IntIntTuple2_ IntIntTuple2_ = (struct IntIntTuple2_){.t0 = 8, .t1 = 3};
    int call_ = tuple_arg_tuple_arg_main_IntIntTuple2IntFun1_sub(IntIntTuple2_);
    return (call_ - 5);
}
