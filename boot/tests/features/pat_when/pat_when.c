#include "milone.h"

struct IntIntTuple2;

int eq_(struct IntIntTuple2 t_);

int main();

struct IntIntTuple2 {
    int t0;
    int t1;
};

int eq_(struct IntIntTuple2 t_) {
    int match_;
    int x_ = t_.t0;
    int y_ = t_.t1;
    if ((x_ != y_)) goto next_2;
    match_ = 1;
    goto end_match_1;
next_2:;
    struct IntIntTuple2 __ = t_;
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    return match_;
}

int main() {
    struct IntIntTuple2 tuple_;
    tuple_.t0 = 1;
    tuple_.t1 = 1;
    int call_ = eq_(tuple_);
    milone_assert(call_, 8, 2);
    int call_1 = 0;
    struct IntIntTuple2 tuple_1;
    tuple_1.t0 = 1;
    tuple_1.t1 = 2;
    int call_2 = eq_(tuple_1);
    milone_assert((!(call_2)), 9, 2);
    int call_3 = 0;
    return 0;
}
