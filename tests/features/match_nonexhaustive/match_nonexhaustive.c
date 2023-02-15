#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32Int32Tuple2_;

int main(int argc, char **argv);

struct Int32Int32Tuple2_ {
    int32_t t0;
    int32_t t1;
};

int main(int argc, char **argv) {
    milone_start(argc, argv);
    int32_t y_;
    int32_t match_;
    struct Int32Int32Tuple2_ Int32Int32Tuple2_;
    Int32Int32Tuple2_ = (struct Int32Int32Tuple2_){.t0 = (2 * 2), .t1 = (3 * 3)};
    if ((Int32Int32Tuple2_.t0 != 4)) goto next_2;
    if ((Int32Int32Tuple2_.t1 != 9)) goto next_2;
    match_ = 0;
    goto end_match_1;
next_2:;
    if ((Int32Int32Tuple2_.t0 != 999)) goto next_3;
    y_ = Int32Int32Tuple2_.t1;
    if ((y_ == 9)) milone_assert_error("match_nonexhaustive/match_nonexhaustive.milone", 9, 4);
    match_ = 1;
    goto end_match_1;
next_3:;
    milone_exhaust_error("match_nonexhaustive/match_nonexhaustive.milone", 5, 2);
end_match_1:;
    return match_;
}
