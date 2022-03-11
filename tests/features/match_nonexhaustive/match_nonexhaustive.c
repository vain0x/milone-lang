#include <milone.h>

struct IntIntTuple2_;

int main(int argc, char** argv);

struct IntIntTuple2_ {
    int t0;
    int t1;
};

int main(int argc, char** argv) {
    milone_start(argc, argv);
    int y_;
    int match_;
    struct IntIntTuple2_ IntIntTuple2_;
    IntIntTuple2_ = (struct IntIntTuple2_){.t0 = (2 * 2), .t1 = (3 * 3)};
    if ((IntIntTuple2_.t0 != 4)) goto next_2;
    if ((IntIntTuple2_.t1 != 9)) goto next_2;
    match_ = 0;
    goto end_match_1;
next_2:;
    if ((IntIntTuple2_.t0 != 999)) goto next_3;
    y_ = IntIntTuple2_.t1;
    milone_assert((y_ != 9), (struct String){.str = "match_nonexhaustive/match_nonexhaustive.milone", .len = 46}, 9, 4);
    match_ = 1;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return match_;
}
