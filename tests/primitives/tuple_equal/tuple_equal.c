#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32Int32Tuple2_;

struct Int32StringTuple2_;

struct Int32Int32Int32Tuple2Tuple2_;

bool MiloneDerive_TupleEqual_tuple2Equal_2(struct Int32Int32Tuple2_ l_6, struct Int32Int32Tuple2_ r_6);

bool MiloneDerive_TupleEqual_tuple2Equal(struct Int32StringTuple2_ l_, struct Int32StringTuple2_ r_);

bool MiloneDerive_TupleEqual_tuple2Equal_2(struct Int32Int32Tuple2_ , struct Int32Int32Tuple2_ );

bool MiloneDerive_TupleEqual_tuple2Equal_1(struct Int32Int32Int32Tuple2Tuple2_ l_3, struct Int32Int32Int32Tuple2Tuple2_ r_3);

bool MiloneDerive_TupleEqual_tuple2Equal(struct Int32StringTuple2_ , struct Int32StringTuple2_ );

void tuple_equal_tuple_equal_testPair(void);

void tuple_equal_tuple_equal_testUnit(void);

bool MiloneDerive_TupleEqual_tuple2Equal_1(struct Int32Int32Int32Tuple2Tuple2_ , struct Int32Int32Int32Tuple2Tuple2_ );

void tuple_equal_tuple_equal_testNested(void);

void tuple_equal_tuple_equal_testUnitCompare(void);

int main(int argc, char** argv);

struct Int32Int32Tuple2_ {
    int32_t t0;
    int32_t t1;
};

struct Int32StringTuple2_ {
    int32_t t0;
    struct String t1;
};

struct Int32Int32Int32Tuple2Tuple2_ {
    int32_t t0;
    struct Int32Int32Tuple2_ t1;
};

bool MiloneDerive_TupleEqual_tuple2Equal_2(struct Int32Int32Tuple2_ l_6, struct Int32Int32Tuple2_ r_6) {
    int32_t l_7;
    int32_t r_7;
    int32_t l_8;
    int32_t r_8;
    l_7 = l_6.t0;
    l_8 = l_6.t1;
    r_7 = r_6.t0;
    r_8 = r_6.t1;
    return ((l_7 == r_7) & (l_8 == r_8));
}

bool MiloneDerive_TupleEqual_tuple2Equal(struct Int32StringTuple2_ l_, struct Int32StringTuple2_ r_) {
    int32_t l_1;
    int32_t r_1;
    struct String l_2;
    struct String r_2;
    l_1 = l_.t0;
    l_2 = l_.t1;
    r_1 = r_.t0;
    r_2 = r_.t1;
    return ((l_1 == r_1) & (string_compare(l_2, r_2) == 0));
}

bool MiloneDerive_TupleEqual_tuple2Equal_1(struct Int32Int32Int32Tuple2Tuple2_ l_3, struct Int32Int32Int32Tuple2Tuple2_ r_3) {
    int32_t l_4;
    int32_t r_4;
    struct Int32Int32Tuple2_ l_5;
    struct Int32Int32Tuple2_ r_5;
    bool call_;
    l_4 = l_3.t0;
    l_5 = l_3.t1;
    r_4 = r_3.t0;
    r_5 = r_3.t1;
    call_ = MiloneDerive_TupleEqual_tuple2Equal_2(l_5, r_5);
    return ((l_4 == r_4) & call_);
}

void tuple_equal_tuple_equal_testPair(void) {
    struct Int32StringTuple2_ Int32StringTuple2_;
    struct Int32StringTuple2_ Int32StringTuple2_1;
    bool call_1;
    struct Int32StringTuple2_ Int32StringTuple2_2;
    struct Int32StringTuple2_ Int32StringTuple2_3;
    bool call_2;
    struct Int32StringTuple2_ Int32StringTuple2_4;
    struct Int32StringTuple2_ Int32StringTuple2_5;
    bool call_3;
    Int32StringTuple2_ = (struct Int32StringTuple2_){.t0 = 0, .t1 = (struct String){.ptr = "zero", .len = 4}};
    Int32StringTuple2_1 = (struct Int32StringTuple2_){.t0 = 0, .t1 = (struct String){.ptr = "zero", .len = 4}};
    call_1 = MiloneDerive_TupleEqual_tuple2Equal(Int32StringTuple2_, Int32StringTuple2_1);
    milone_assert(call_1, (struct String){.ptr = "tuple_equal/tuple_equal.milone", .len = 30}, 5, 2);
    Int32StringTuple2_2 = (struct Int32StringTuple2_){.t0 = 0, .t1 = (struct String){.ptr = "zero", .len = 4}};
    Int32StringTuple2_3 = (struct Int32StringTuple2_){.t0 = 1, .t1 = (struct String){.ptr = "zero", .len = 4}};
    call_2 = MiloneDerive_TupleEqual_tuple2Equal(Int32StringTuple2_2, Int32StringTuple2_3);
    milone_assert((!(call_2)), (struct String){.ptr = "tuple_equal/tuple_equal.milone", .len = 30}, 7, 2);
    Int32StringTuple2_4 = (struct Int32StringTuple2_){.t0 = 0, .t1 = (struct String){.ptr = "zero", .len = 4}};
    Int32StringTuple2_5 = (struct Int32StringTuple2_){.t0 = 0, .t1 = (struct String){.ptr = "one", .len = 3}};
    call_3 = MiloneDerive_TupleEqual_tuple2Equal(Int32StringTuple2_4, Int32StringTuple2_5);
    milone_assert((!(call_3)), (struct String){.ptr = "tuple_equal/tuple_equal.milone", .len = 30}, 8, 2);
    return;
}

void tuple_equal_tuple_equal_testUnit(void) {
    milone_assert(true, (struct String){.ptr = "tuple_equal/tuple_equal.milone", .len = 30}, 10, 26);
    return;
}

void tuple_equal_tuple_equal_testNested(void) {
    struct Int32Int32Int32Tuple2Tuple2_ Int32Int32Int32Tuple2Tuple2_;
    struct Int32Int32Tuple2_ Int32Int32Tuple2_;
    struct Int32Int32Int32Tuple2Tuple2_ Int32Int32Int32Tuple2Tuple2_1;
    struct Int32Int32Tuple2_ Int32Int32Tuple2_1;
    bool call_4;
    struct Int32Int32Int32Tuple2Tuple2_ Int32Int32Int32Tuple2Tuple2_2;
    struct Int32Int32Tuple2_ Int32Int32Tuple2_2;
    struct Int32Int32Int32Tuple2Tuple2_ Int32Int32Int32Tuple2Tuple2_3;
    struct Int32Int32Tuple2_ Int32Int32Tuple2_3;
    bool call_5;
    struct Int32Int32Int32Tuple2Tuple2_ Int32Int32Int32Tuple2Tuple2_4;
    struct Int32Int32Tuple2_ Int32Int32Tuple2_4;
    struct Int32Int32Int32Tuple2Tuple2_ Int32Int32Int32Tuple2Tuple2_5;
    struct Int32Int32Tuple2_ Int32Int32Tuple2_5;
    bool call_6;
    Int32Int32Tuple2_ = (struct Int32Int32Tuple2_){.t0 = 2, .t1 = 3};
    Int32Int32Int32Tuple2Tuple2_ = (struct Int32Int32Int32Tuple2Tuple2_){.t0 = 1, .t1 = Int32Int32Tuple2_};
    Int32Int32Tuple2_1 = (struct Int32Int32Tuple2_){.t0 = 2, .t1 = 3};
    Int32Int32Int32Tuple2Tuple2_1 = (struct Int32Int32Int32Tuple2Tuple2_){.t0 = 1, .t1 = Int32Int32Tuple2_1};
    call_4 = MiloneDerive_TupleEqual_tuple2Equal_1(Int32Int32Int32Tuple2Tuple2_, Int32Int32Int32Tuple2Tuple2_1);
    milone_assert(call_4, (struct String){.ptr = "tuple_equal/tuple_equal.milone", .len = 30}, 13, 2);
    Int32Int32Tuple2_2 = (struct Int32Int32Tuple2_){.t0 = 2, .t1 = 3};
    Int32Int32Int32Tuple2Tuple2_2 = (struct Int32Int32Int32Tuple2Tuple2_){.t0 = 1, .t1 = Int32Int32Tuple2_2};
    Int32Int32Tuple2_3 = (struct Int32Int32Tuple2_){.t0 = 2, .t1 = 3};
    Int32Int32Int32Tuple2Tuple2_3 = (struct Int32Int32Int32Tuple2Tuple2_){.t0 = 0, .t1 = Int32Int32Tuple2_3};
    call_5 = MiloneDerive_TupleEqual_tuple2Equal_1(Int32Int32Int32Tuple2Tuple2_2, Int32Int32Int32Tuple2Tuple2_3);
    milone_assert((!(call_5)), (struct String){.ptr = "tuple_equal/tuple_equal.milone", .len = 30}, 15, 2);
    Int32Int32Tuple2_4 = (struct Int32Int32Tuple2_){.t0 = 2, .t1 = 3};
    Int32Int32Int32Tuple2Tuple2_4 = (struct Int32Int32Int32Tuple2Tuple2_){.t0 = 1, .t1 = Int32Int32Tuple2_4};
    Int32Int32Tuple2_5 = (struct Int32Int32Tuple2_){.t0 = 2, .t1 = 0};
    Int32Int32Int32Tuple2Tuple2_5 = (struct Int32Int32Int32Tuple2Tuple2_){.t0 = 1, .t1 = Int32Int32Tuple2_5};
    call_6 = MiloneDerive_TupleEqual_tuple2Equal_1(Int32Int32Int32Tuple2Tuple2_4, Int32Int32Int32Tuple2Tuple2_5);
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
