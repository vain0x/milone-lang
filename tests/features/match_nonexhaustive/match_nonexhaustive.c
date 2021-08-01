#include "milone.h"

struct IntIntTuple2;

int milone_main();

struct IntIntTuple2 {
    int t0;
    int t1;
};

int milone_main() {
    int y_;
    int match_;
    struct IntIntTuple2 tuple_ = (struct IntIntTuple2){.t0 = (2 * 2), .t1 = (3 * 3)};
    if ((tuple_.t0 != 4)) goto next_2;
    if ((tuple_.t1 != 9)) goto next_2;
    match_ = 0;
    goto end_match_1;
next_2:;
    if ((tuple_.t0 != 999)) goto next_3;
    y_ = tuple_.t1;
    milone_assert((y_ != 9), 9, 4);
    match_ = 1;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return match_;
}
