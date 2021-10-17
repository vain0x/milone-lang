#include "milone.h"

struct IntIntTuple2_;

struct IntStringTuple2_;

struct IntIntIntTuple2Tuple2_;

bool tuple2Equal_2(struct IntIntTuple2_ l_6, struct IntIntTuple2_ r_6);

bool tuple2Equal_(struct IntStringTuple2_ l_, struct IntStringTuple2_ r_);

bool tuple2Equal_2(struct IntIntTuple2_ , struct IntIntTuple2_ );

bool tuple2Equal_1(struct IntIntIntTuple2Tuple2_ l_3, struct IntIntIntTuple2Tuple2_ r_3);

bool tuple2Equal_(struct IntStringTuple2_ , struct IntStringTuple2_ );

void testPair_(void);

void testUnit_(void);

bool tuple2Equal_1(struct IntIntIntTuple2Tuple2_ , struct IntIntIntTuple2Tuple2_ );

void testNested_(void);

void testUnitCompare_(void);

int milone_main(void);

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

bool tuple2Equal_2(struct IntIntTuple2_ l_6, struct IntIntTuple2_ r_6) {
    int l_7 = l_6.t0;
    int l_8 = l_6.t1;
    int r_7 = r_6.t0;
    int r_8 = r_6.t1;
    return ((l_7 == r_7) & (l_8 == r_8));
}

bool tuple2Equal_(struct IntStringTuple2_ l_, struct IntStringTuple2_ r_) {
    int l_1 = l_.t0;
    struct String l_2 = l_.t1;
    int r_1 = r_.t0;
    struct String r_2 = r_.t1;
    return ((l_1 == r_1) & (str_compare(l_2, r_2) == 0));
}

bool tuple2Equal_1(struct IntIntIntTuple2Tuple2_ l_3, struct IntIntIntTuple2Tuple2_ r_3) {
    int l_4 = l_3.t0;
    struct IntIntTuple2_ l_5 = l_3.t1;
    int r_4 = r_3.t0;
    struct IntIntTuple2_ r_5 = r_3.t1;
    bool call_ = tuple2Equal_2(l_5, r_5);
    return ((l_4 == r_4) & call_);
}

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
