#include "milone.h"

struct IntIntTuple2;

int main();

struct IntIntTuple2 {
    int t0;
    int t1;
};

int main() {
    int match_;
    struct IntIntTuple2 tuple_;
    tuple_.t0 = (2 * 2);
    tuple_.t1 = (3 * 3);
    if ((tuple_.t0 != 4)) goto next_2;
    if ((tuple_.t1 != 9)) goto next_2;
    match_ = 0;
    goto end_match_1;
next_2:;
    if ((tuple_.t0 != 999)) goto next_3;
    int y_ = tuple_.t1;
    match_ = 1;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return match_;
}
