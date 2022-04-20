#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32Int32Tuple2_;

bool pat_when_pat_when_equal(struct Int32Int32Tuple2_ t_);

int main(int argc, char **argv);

struct Int32Int32Tuple2_ {
    int32_t t0;
    int32_t t1;
};

bool pat_when_pat_when_equal(struct Int32Int32Tuple2_ t_) {
    int32_t x_;
    int32_t y_;
    bool match_;
    x_ = t_.t0;
    y_ = t_.t1;
    if ((x_ != y_)) goto next_2;
    match_ = true;
    goto end_match_1;
next_2:;
    match_ = false;
    goto end_match_1;
next_3:;
end_match_1:;
    return match_;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    struct Int32Int32Tuple2_ Int32Int32Tuple2_;
    bool call_;
    struct Int32Int32Tuple2_ Int32Int32Tuple2_1;
    bool call_1;
    Int32Int32Tuple2_ = (struct Int32Int32Tuple2_){.t0 = 1, .t1 = 1};
    call_ = pat_when_pat_when_equal(Int32Int32Tuple2_);
    if ((!(call_))) milone_assert_error("pat_when/pat_when.milone", 10, 2);
    Int32Int32Tuple2_1 = (struct Int32Int32Tuple2_){.t0 = 1, .t1 = 2};
    call_1 = pat_when_pat_when_equal(Int32Int32Tuple2_1);
    if (call_1) milone_assert_error("pat_when/pat_when.milone", 11, 2);
    return 0;
}
