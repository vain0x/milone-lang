#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct IntIntTuple2_;

struct IntStringTuple2_;

struct IntIntIntTuple2Tuple2_;

bool MiloneDerive_TupleEqual_tuple2Equal_2(struct IntIntTuple2_ l_6, struct IntIntTuple2_ r_6);

bool MiloneDerive_TupleEqual_tuple2Equal(struct IntStringTuple2_ l_, struct IntStringTuple2_ r_);

bool MiloneDerive_TupleEqual_tuple2Equal_2(struct IntIntTuple2_ , struct IntIntTuple2_ );

bool MiloneDerive_TupleEqual_tuple2Equal_1(struct IntIntIntTuple2Tuple2_ l_3, struct IntIntIntTuple2Tuple2_ r_3);

bool MiloneDerive_TupleEqual_tuple2Equal(struct IntStringTuple2_ , struct IntStringTuple2_ );

void tuple_equal_tuple_equal_testPair(void);

void tuple_equal_tuple_equal_testUnit(void);

bool MiloneDerive_TupleEqual_tuple2Equal_1(struct IntIntIntTuple2Tuple2_ , struct IntIntIntTuple2Tuple2_ );

void tuple_equal_tuple_equal_testNested(void);

void tuple_equal_tuple_equal_testUnitCompare(void);

int main(int argc, char** argv);

struct IntIntTuple2_ {
    int t0;
    int t1;
};

struct IntStringTuple2_ {
    int t0;
    struct String t1;
};

struct IntIntIntTuple2Tuple2_ {
    int t0;
    struct IntIntTuple2_ t1;
};

bool MiloneDerive_TupleEqual_tuple2Equal_2(struct IntIntTuple2_ l_6, struct IntIntTuple2_ r_6) {
    int l_7;
    int r_7;
    int l_8;
    int r_8;
    l_7 = l_6.t0;
    l_8 = l_6.t1;
    r_7 = r_6.t0;
    r_8 = r_6.t1;
    return ((l_7 == r_7) & (l_8 == r_8));
}

bool MiloneDerive_TupleEqual_tuple2Equal(struct IntStringTuple2_ l_, struct IntStringTuple2_ r_) {
    int l_1;
    int r_1;
    struct String l_2;
    struct String r_2;
    l_1 = l_.t0;
    l_2 = l_.t1;
    r_1 = r_.t0;
    r_2 = r_.t1;
    return ((l_1 == r_1) & (string_compare(l_2, r_2) == 0));
}

bool MiloneDerive_TupleEqual_tuple2Equal_1(struct IntIntIntTuple2Tuple2_ l_3, struct IntIntIntTuple2Tuple2_ r_3) {
    int l_4;
    int r_4;
    struct IntIntTuple2_ l_5;
    struct IntIntTuple2_ r_5;
    bool call_;
    l_4 = l_3.t0;
    l_5 = l_3.t1;
    r_4 = r_3.t0;
    r_5 = r_3.t1;
    call_ = MiloneDerive_TupleEqual_tuple2Equal_2(l_5, r_5);
    return ((l_4 == r_4) & call_);
}

void tuple_equal_tuple_equal_testPair(void) {
    struct IntStringTuple2_ IntStringTuple2_;
    struct IntStringTuple2_ IntStringTuple2_1;
    bool call_1;
    struct IntStringTuple2_ IntStringTuple2_2;
    struct IntStringTuple2_ IntStringTuple2_3;
    bool call_2;
    struct IntStringTuple2_ IntStringTuple2_4;
    struct IntStringTuple2_ IntStringTuple2_5;
    bool call_3;
    IntStringTuple2_ = (struct IntStringTuple2_){.t0 = 0, .t1 = (struct String){.ptr = "zero", .len = 4}};
    IntStringTuple2_1 = (struct IntStringTuple2_){.t0 = 0, .t1 = (struct String){.ptr = "zero", .len = 4}};
    call_1 = MiloneDerive_TupleEqual_tuple2Equal(IntStringTuple2_, IntStringTuple2_1);
    milone_assert(call_1, (struct String){.ptr = "tuple_equal/tuple_equal.milone", .len = 30}, 5, 2);
    IntStringTuple2_2 = (struct IntStringTuple2_){.t0 = 0, .t1 = (struct String){.ptr = "zero", .len = 4}};
    IntStringTuple2_3 = (struct IntStringTuple2_){.t0 = 1, .t1 = (struct String){.ptr = "zero", .len = 4}};
    call_2 = MiloneDerive_TupleEqual_tuple2Equal(IntStringTuple2_2, IntStringTuple2_3);
    milone_assert((!(call_2)), (struct String){.ptr = "tuple_equal/tuple_equal.milone", .len = 30}, 7, 2);
    IntStringTuple2_4 = (struct IntStringTuple2_){.t0 = 0, .t1 = (struct String){.ptr = "zero", .len = 4}};
    IntStringTuple2_5 = (struct IntStringTuple2_){.t0 = 0, .t1 = (struct String){.ptr = "one", .len = 3}};
    call_3 = MiloneDerive_TupleEqual_tuple2Equal(IntStringTuple2_4, IntStringTuple2_5);
    milone_assert((!(call_3)), (struct String){.ptr = "tuple_equal/tuple_equal.milone", .len = 30}, 8, 2);
    return;
}

void tuple_equal_tuple_equal_testUnit(void) {
    milone_assert(true, (struct String){.ptr = "tuple_equal/tuple_equal.milone", .len = 30}, 10, 26);
    return;
}

void tuple_equal_tuple_equal_testNested(void) {
    struct IntIntIntTuple2Tuple2_ IntIntIntTuple2Tuple2_;
    struct IntIntTuple2_ IntIntTuple2_;
    struct IntIntIntTuple2Tuple2_ IntIntIntTuple2Tuple2_1;
    struct IntIntTuple2_ IntIntTuple2_1;
    bool call_4;
    struct IntIntIntTuple2Tuple2_ IntIntIntTuple2Tuple2_2;
    struct IntIntTuple2_ IntIntTuple2_2;
    struct IntIntIntTuple2Tuple2_ IntIntIntTuple2Tuple2_3;
    struct IntIntTuple2_ IntIntTuple2_3;
    bool call_5;
    struct IntIntIntTuple2Tuple2_ IntIntIntTuple2Tuple2_4;
    struct IntIntTuple2_ IntIntTuple2_4;
    struct IntIntIntTuple2Tuple2_ IntIntIntTuple2Tuple2_5;
    struct IntIntTuple2_ IntIntTuple2_5;
    bool call_6;
    IntIntTuple2_ = (struct IntIntTuple2_){.t0 = 2, .t1 = 3};
    IntIntIntTuple2Tuple2_ = (struct IntIntIntTuple2Tuple2_){.t0 = 1, .t1 = IntIntTuple2_};
    IntIntTuple2_1 = (struct IntIntTuple2_){.t0 = 2, .t1 = 3};
    IntIntIntTuple2Tuple2_1 = (struct IntIntIntTuple2Tuple2_){.t0 = 1, .t1 = IntIntTuple2_1};
    call_4 = MiloneDerive_TupleEqual_tuple2Equal_1(IntIntIntTuple2Tuple2_, IntIntIntTuple2Tuple2_1);
    milone_assert(call_4, (struct String){.ptr = "tuple_equal/tuple_equal.milone", .len = 30}, 13, 2);
    IntIntTuple2_2 = (struct IntIntTuple2_){.t0 = 2, .t1 = 3};
    IntIntIntTuple2Tuple2_2 = (struct IntIntIntTuple2Tuple2_){.t0 = 1, .t1 = IntIntTuple2_2};
    IntIntTuple2_3 = (struct IntIntTuple2_){.t0 = 2, .t1 = 3};
    IntIntIntTuple2Tuple2_3 = (struct IntIntIntTuple2Tuple2_){.t0 = 0, .t1 = IntIntTuple2_3};
    call_5 = MiloneDerive_TupleEqual_tuple2Equal_1(IntIntIntTuple2Tuple2_2, IntIntIntTuple2Tuple2_3);
    milone_assert((!(call_5)), (struct String){.ptr = "tuple_equal/tuple_equal.milone", .len = 30}, 15, 2);
    IntIntTuple2_4 = (struct IntIntTuple2_){.t0 = 2, .t1 = 3};
    IntIntIntTuple2Tuple2_4 = (struct IntIntIntTuple2Tuple2_){.t0 = 1, .t1 = IntIntTuple2_4};
    IntIntTuple2_5 = (struct IntIntTuple2_){.t0 = 2, .t1 = 0};
    IntIntIntTuple2Tuple2_5 = (struct IntIntIntTuple2Tuple2_){.t0 = 1, .t1 = IntIntTuple2_5};
    call_6 = MiloneDerive_TupleEqual_tuple2Equal_1(IntIntIntTuple2Tuple2_4, IntIntIntTuple2Tuple2_5);
    milone_assert((!(call_6)), (struct String){.ptr = "tuple_equal/tuple_equal.milone", .len = 30}, 16, 2);
    return;
}

void tuple_equal_tuple_equal_testUnitCompare(void) {
    milone_assert(true, (struct String){.ptr = "tuple_equal/tuple_equal.milone", .len = 30}, 20, 2);
    milone_assert(true, (struct String){.ptr = "tuple_equal/tuple_equal.milone", .len = 30}, 21, 2);
    milone_assert(true, (struct String){.ptr = "tuple_equal/tuple_equal.milone", .len = 30}, 22, 2);
    milone_assert(true, (struct String){.ptr = "tuple_equal/tuple_equal.milone", .len = 30}, 23, 2);
    return;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    tuple_equal_tuple_equal_testUnit();
    tuple_equal_tuple_equal_testPair();
    tuple_equal_tuple_equal_testNested();
    tuple_equal_tuple_equal_testUnitCompare();
    return 0;
}
