#include "milone.h"

struct IntIntTuple2_;

struct IntStringTuple2_;

struct IntIntIntTuple2Tuple2_;

bool tuple2Equal_2(struct IntIntTuple2_ l_6, struct IntIntTuple2_ r_6);

bool tuple2Equal_(struct IntStringTuple2_ l_, struct IntStringTuple2_ r_);

bool tuple2Equal_1(struct IntIntIntTuple2Tuple2_ l_3, struct IntIntIntTuple2Tuple2_ r_3);

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
