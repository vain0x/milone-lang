#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32Int32Int32Int32Int32Int32Int32Int32Int32Int32Int32Tuple11_;

struct Int32Int32Tuple2_;

struct Int32Int32Int32Int32Tuple2Tuple3_;

int main(int argc, char **argv);

struct Int32Int32Int32Int32Int32Int32Int32Int32Int32Int32Int32Tuple11_ {
    int32_t t0;
    int32_t t1;
    int32_t t2;
    int32_t t3;
    int32_t t4;
    int32_t t5;
    int32_t t6;
    int32_t t7;
    int32_t t8;
    int32_t t9;
    int32_t t10;
};

struct Int32Int32Tuple2_ {
    int32_t t0;
    int32_t t1;
};

struct Int32Int32Int32Int32Tuple2Tuple3_ {
    int32_t t0;
    int32_t t1;
    struct Int32Int32Tuple2_ t2;
};

int main(int argc, char **argv) {
    milone_start(argc, argv);
    int32_t x_;
    int32_t y_;
    int32_t z_;
    int32_t w_;
    struct Int32Int32Int32Int32Int32Int32Int32Int32Int32Int32Int32Tuple11_ _t11;
    struct Int32Int32Int32Int32Tuple2Tuple3_ Int32Int32Int32Int32Tuple2Tuple3_;
    struct Int32Int32Tuple2_ Int32Int32Tuple2_;
    bool if_;
    bool if_1;
    bool if_2;
    struct Int32Int32Int32Int32Int32Int32Int32Int32Int32Int32Int32Tuple11_ Int32Int32Int32Int32Int32Int32Int32Int32Int32Int32Int32Tuple11_;
    Int32Int32Tuple2_ = (struct Int32Int32Tuple2_){.t0 = 3, .t1 = 4};
    Int32Int32Int32Int32Tuple2Tuple3_ = (struct Int32Int32Int32Int32Tuple2Tuple3_){.t0 = 1, .t1 = 2, .t2 = Int32Int32Tuple2_};
    x_ = Int32Int32Int32Int32Tuple2Tuple3_.t0;
    y_ = Int32Int32Int32Int32Tuple2Tuple3_.t1;
    z_ = Int32Int32Int32Int32Tuple2Tuple3_.t2.t0;
    w_ = Int32Int32Int32Int32Tuple2Tuple3_.t2.t1;
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
    if ((!(if_2))) milone_assert_error("tuple_large/tuple_large.milone", 6, 2);
    Int32Int32Int32Int32Int32Int32Int32Int32Int32Int32Int32Tuple11_ = (struct Int32Int32Int32Int32Int32Int32Int32Int32Int32Int32Int32Tuple11_){.t0 = 1, .t1 = 2, .t2 = 3, .t3 = 4, .t4 = 5, .t5 = 6, .t6 = 7, .t7 = 8, .t8 = 9, .t9 = 10, .t10 = 11};
    _t11 = Int32Int32Int32Int32Int32Int32Int32Int32Int32Int32Int32Tuple11_;
    return 0;
}
