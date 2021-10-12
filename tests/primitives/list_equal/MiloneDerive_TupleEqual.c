#include "milone.h"

struct IntStringTuple2_;

bool tuple2Equal_(struct IntStringTuple2_ l_2, struct IntStringTuple2_ r_2);

struct IntStringTuple2_ {
    int t0;
    struct String t1;
};

bool tuple2Equal_(struct IntStringTuple2_ l_2, struct IntStringTuple2_ r_2) {
    int l_3 = l_2.t0;
    struct String l_4 = l_2.t1;
    int r_3 = r_2.t0;
    struct String r_4 = r_2.t1;
    return ((l_3 == r_3) & (str_compare(l_4, r_4) == 0));
}
