#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct IntIntTuple2_;

bool pat_when_pat_when_equal(struct IntIntTuple2_ t_);

int main(int argc, char** argv);

struct IntIntTuple2_ {
    int t0;
    int t1;
};

bool pat_when_pat_when_equal(struct IntIntTuple2_ t_) {
    int x_;
    int y_;
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

int main(int argc, char** argv) {
    milone_start(argc, argv);
    struct IntIntTuple2_ IntIntTuple2_;
    bool call_;
    struct IntIntTuple2_ IntIntTuple2_1;
    bool call_1;
    IntIntTuple2_ = (struct IntIntTuple2_){.t0 = 1, .t1 = 1};
    call_ = pat_when_pat_when_equal(IntIntTuple2_);
    milone_assert(call_, (struct String){.ptr = "pat_when/pat_when.milone", .len = 24}, 10, 2);
    IntIntTuple2_1 = (struct IntIntTuple2_){.t0 = 1, .t1 = 2};
    call_1 = pat_when_pat_when_equal(IntIntTuple2_1);
    milone_assert((!(call_1)), (struct String){.ptr = "pat_when/pat_when.milone", .len = 24}, 11, 2);
    return 0;
}
