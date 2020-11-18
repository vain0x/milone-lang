#include "milone.h"

struct IntIntTuple2;

struct IntIntIntIntTuple2Tuple3;

struct IntIntIntIntIntIntIntIntIntIntIntTuple11;

int main();

struct IntIntTuple2 {
    int t0;
    int t1;
};

struct IntIntIntIntTuple2Tuple3 {
    int t0;
    int t1;
    struct IntIntTuple2 t2;
};

struct IntIntIntIntIntIntIntIntIntIntIntTuple11 {
    int t0;
    int t1;
    int t2;
    int t3;
    int t4;
    int t5;
    int t6;
    int t7;
    int t8;
    int t9;
    int t10;
};

int main() {
    struct IntIntTuple2 tuple_1;
    tuple_1.t0 = 3;
    tuple_1.t1 = 4;
    struct IntIntIntIntTuple2Tuple3 tuple_;
    tuple_.t0 = 1;
    tuple_.t1 = 2;
    tuple_.t2 = tuple_1;
    int x_ = tuple_.t0;
    int y_ = tuple_.t1;
    int z_ = tuple_.t2.t0;
    int w_ = tuple_.t2.t1;
    int if_;
    if ((x_ == 1)) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    if_ = (y_ == 2);
    goto if_next_1;
else_3:;
    if_ = 0;
    goto if_next_1;
if_next_1:;
    int if_1;
    if (if_) {
        goto then_5;
    } else {
        goto else_6;
    }
then_5:;
    if_1 = (z_ == 3);
    goto if_next_4;
else_6:;
    if_1 = 0;
    goto if_next_4;
if_next_4:;
    int if_2;
    if (if_1) {
        goto then_8;
    } else {
        goto else_9;
    }
then_8:;
    if_2 = (w_ == 4);
    goto if_next_7;
else_9:;
    if_2 = 0;
    goto if_next_7;
if_next_7:;
    milone_assert(if_2, 2, 2);
    int call_ = 0;
    struct IntIntIntIntIntIntIntIntIntIntIntTuple11 tuple_2;
    tuple_2.t0 = 1;
    tuple_2.t1 = 2;
    tuple_2.t2 = 3;
    tuple_2.t3 = 4;
    tuple_2.t4 = 5;
    tuple_2.t5 = 6;
    tuple_2.t6 = 7;
    tuple_2.t7 = 8;
    tuple_2.t8 = 9;
    tuple_2.t9 = 10;
    tuple_2.t10 = 11;
    struct IntIntIntIntIntIntIntIntIntIntIntTuple11 t11_ = tuple_2;
    return 0;
}
