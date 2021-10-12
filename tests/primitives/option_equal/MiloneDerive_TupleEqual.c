#include "milone.h"

struct IntStringTuple2_;

bool tuple2Equal_(struct IntStringTuple2_ l_4, struct IntStringTuple2_ r_4);

struct IntStringTuple2_ {
    int t0;
    struct String t1;
};

bool tuple2Equal_(struct IntStringTuple2_ l_4, struct IntStringTuple2_ r_4) {
    int l_5 = l_4.t0;
    struct String l_6 = l_4.t1;
    int r_5 = r_4.t0;
    struct String r_6 = r_4.t1;
    return ((l_5 == r_5) & (str_compare(l_6, r_6) == 0));
}
