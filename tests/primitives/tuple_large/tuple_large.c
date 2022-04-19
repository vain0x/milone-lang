#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct IntIntIntIntIntIntIntIntIntIntIntTuple11_;

struct IntIntTuple2_;

struct IntIntIntIntTuple2Tuple3_;

int main(int argc, char** argv);

struct IntIntIntIntIntIntIntIntIntIntIntTuple11_ {
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

struct IntIntTuple2_ {
    int t0;
    int t1;
};

struct IntIntIntIntTuple2Tuple3_ {
    int t0;
    int t1;
    struct IntIntTuple2_ t2;
};

int main(int argc, char** argv) {
    milone_start(argc, argv);
    int x_;
    int y_;
    int z_;
    int w_;
    struct IntIntIntIntIntIntIntIntIntIntIntTuple11_ _t11;
    struct IntIntIntIntTuple2Tuple3_ IntIntIntIntTuple2Tuple3_;
    struct IntIntTuple2_ IntIntTuple2_;
    bool if_;
    bool if_1;
    bool if_2;
    struct IntIntIntIntIntIntIntIntIntIntIntTuple11_ IntIntIntIntIntIntIntIntIntIntIntTuple11_;
    IntIntTuple2_ = (struct IntIntTuple2_){.t0 = 3, .t1 = 4};
    IntIntIntIntTuple2Tuple3_ = (struct IntIntIntIntTuple2Tuple3_){.t0 = 1, .t1 = 2, .t2 = IntIntTuple2_};
    x_ = IntIntIntIntTuple2Tuple3_.t0;
    y_ = IntIntIntIntTuple2Tuple3_.t1;
    z_ = IntIntIntIntTuple2Tuple3_.t2.t0;
    w_ = IntIntIntIntTuple2Tuple3_.t2.t1;
    if ((x_ == 1)) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    if_ = (y_ == 2);
    goto if_next_1;
else_3:;
    if_ = false;
    goto if_next_1;
if_next_1:;
    if (if_) {
        goto then_5;
    } else {
        goto else_6;
    }
then_5:;
    if_1 = (z_ == 3);
    goto if_next_4;
else_6:;
    if_1 = false;
    goto if_next_4;
if_next_4:;
    if (if_1) {
        goto then_8;
    } else {
        goto else_9;
    }
then_8:;
    if_2 = (w_ == 4);
    goto if_next_7;
else_9:;
    if_2 = false;
    goto if_next_7;
if_next_7:;
    milone_assert(if_2, (struct String){.ptr = "tuple_large/tuple_large.milone", .len = 30}, 6, 2);
    IntIntIntIntIntIntIntIntIntIntIntTuple11_ = (struct IntIntIntIntIntIntIntIntIntIntIntTuple11_){.t0 = 1, .t1 = 2, .t2 = 3, .t3 = 4, .t4 = 5, .t5 = 6, .t6 = 7, .t7 = 8, .t8 = 9, .t9 = 10, .t10 = 11};
    _t11 = IntIntIntIntIntIntIntIntIntIntIntTuple11_;
    return 0;
}
