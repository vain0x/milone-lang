#include "milone.h"

struct IntStringTuple2_;

struct IntIntTuple2_;

struct IntIntIntTuple2Tuple2_;

bool tuple2Equal_(struct IntStringTuple2_ , struct IntStringTuple2_ );

void testPair_(void);

void testUnit_(void);

bool tuple2Equal_1(struct IntIntIntTuple2Tuple2_ , struct IntIntIntTuple2Tuple2_ );

void testNested_(void);

void testUnitCompare_(void);

int milone_main(void);

struct IntStringTuple2_ {
    int t0;
    struct String t1;
};

struct IntIntTuple2_ {
    int t0;
    int t1;
};

struct IntIntIntTuple2Tuple2_ {
    int t0;
    struct IntIntTuple2_ t1;
};

void testPair_(void) {
    struct IntStringTuple2_ IntStringTuple2_ = (struct IntStringTuple2_){.t0 = 0, .t1 = (struct String){.str = "zero", .len = 4}};
    struct IntStringTuple2_ IntStringTuple2_1 = (struct IntStringTuple2_){.t0 = 0, .t1 = (struct String){.str = "zero", .len = 4}};
    bool call_1 = tuple2Equal_(IntStringTuple2_, IntStringTuple2_1);
    milone_assert(call_1, 5, 2);
    struct IntStringTuple2_ IntStringTuple2_2 = (struct IntStringTuple2_){.t0 = 0, .t1 = (struct String){.str = "zero", .len = 4}};
    struct IntStringTuple2_ IntStringTuple2_3 = (struct IntStringTuple2_){.t0 = 1, .t1 = (struct String){.str = "zero", .len = 4}};
    bool call_2 = tuple2Equal_(IntStringTuple2_2, IntStringTuple2_3);
    milone_assert((!(call_2)), 7, 2);
    struct IntStringTuple2_ IntStringTuple2_4 = (struct IntStringTuple2_){.t0 = 0, .t1 = (struct String){.str = "zero", .len = 4}};
    struct IntStringTuple2_ IntStringTuple2_5 = (struct IntStringTuple2_){.t0 = 0, .t1 = (struct String){.str = "one", .len = 3}};
    bool call_3 = tuple2Equal_(IntStringTuple2_4, IntStringTuple2_5);
    milone_assert((!(call_3)), 8, 2);
    return;
}

void testUnit_(void) {
    milone_assert(true, 10, 26);
    return;
}

void testNested_(void) {
    struct IntIntTuple2_ IntIntTuple2_ = (struct IntIntTuple2_){.t0 = 2, .t1 = 3};
    struct IntIntIntTuple2Tuple2_ IntIntIntTuple2Tuple2_ = (struct IntIntIntTuple2Tuple2_){.t0 = 1, .t1 = IntIntTuple2_};
    struct IntIntTuple2_ IntIntTuple2_1 = (struct IntIntTuple2_){.t0 = 2, .t1 = 3};
    struct IntIntIntTuple2Tuple2_ IntIntIntTuple2Tuple2_1 = (struct IntIntIntTuple2Tuple2_){.t0 = 1, .t1 = IntIntTuple2_1};
    bool call_4 = tuple2Equal_1(IntIntIntTuple2Tuple2_, IntIntIntTuple2Tuple2_1);
    milone_assert(call_4, 13, 2);
    struct IntIntTuple2_ IntIntTuple2_2 = (struct IntIntTuple2_){.t0 = 2, .t1 = 3};
    struct IntIntIntTuple2Tuple2_ IntIntIntTuple2Tuple2_2 = (struct IntIntIntTuple2Tuple2_){.t0 = 1, .t1 = IntIntTuple2_2};
    struct IntIntTuple2_ IntIntTuple2_3 = (struct IntIntTuple2_){.t0 = 2, .t1 = 3};
    struct IntIntIntTuple2Tuple2_ IntIntIntTuple2Tuple2_3 = (struct IntIntIntTuple2Tuple2_){.t0 = 0, .t1 = IntIntTuple2_3};
    bool call_5 = tuple2Equal_1(IntIntIntTuple2Tuple2_2, IntIntIntTuple2Tuple2_3);
    milone_assert((!(call_5)), 15, 2);
    struct IntIntTuple2_ IntIntTuple2_4 = (struct IntIntTuple2_){.t0 = 2, .t1 = 3};
    struct IntIntIntTuple2Tuple2_ IntIntIntTuple2Tuple2_4 = (struct IntIntIntTuple2Tuple2_){.t0 = 1, .t1 = IntIntTuple2_4};
    struct IntIntTuple2_ IntIntTuple2_5 = (struct IntIntTuple2_){.t0 = 2, .t1 = 0};
    struct IntIntIntTuple2Tuple2_ IntIntIntTuple2Tuple2_5 = (struct IntIntIntTuple2Tuple2_){.t0 = 1, .t1 = IntIntTuple2_5};
    bool call_6 = tuple2Equal_1(IntIntIntTuple2Tuple2_4, IntIntIntTuple2Tuple2_5);
    milone_assert((!(call_6)), 16, 2);
    return;
}

void testUnitCompare_(void) {
    milone_assert(true, 20, 2);
    milone_assert(true, 21, 2);
    milone_assert(true, 22, 2);
    milone_assert(true, 23, 2);
    return;
}

int milone_main(void) {
    testUnit_();
    testPair_();
    testNested_();
    testUnitCompare_();
    return 0;
}
