#include "milone.h"

struct IntIntTuple2;

bool eq_(struct IntIntTuple2 t_);

int main();

struct IntIntTuple2 {
    int t0;
    int t1;
};

bool eq_(struct IntIntTuple2 t_) {
    bool match_;
    int x_ = t_.t0;
    int y_ = t_.t1;
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

int main() {
    struct IntIntTuple2 tuple_ = (struct IntIntTuple2){.t0 = 1, .t1 = 1};
    bool call_ = eq_(tuple_);
    milone_assert(call_, 10, 2);
    struct IntIntTuple2 tuple_1 = (struct IntIntTuple2){.t0 = 1, .t1 = 2};
    bool call_1 = eq_(tuple_1);
    milone_assert((!(call_1)), 11, 2);
    return 0;
}
