#include "milone.h"

struct IntIntTuple2_;

bool pat_when_Program_equal(struct IntIntTuple2_ t_);

int milone_main(void);

struct IntIntTuple2_ {
    int t0;
    int t1;
};

bool pat_when_Program_equal(struct IntIntTuple2_ t_) {
    int y_;
    int x_;
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

int milone_main(void) {
    struct IntIntTuple2_ IntIntTuple2_ = (struct IntIntTuple2_){.t0 = 1, .t1 = 1};
    bool call_ = pat_when_Program_equal(IntIntTuple2_);
    milone_assert(call_, 10, 2);
    struct IntIntTuple2_ IntIntTuple2_1 = (struct IntIntTuple2_){.t0 = 1, .t1 = 2};
    bool call_1 = pat_when_Program_equal(IntIntTuple2_1);
    milone_assert((!(call_1)), 11, 2);
    return 0;
}
