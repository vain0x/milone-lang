#include "milone.h"

char simpleCase_(char arg_);

struct IntIntTuple2;

char shadowingCase_(char arg_1);

int milone_main();

char simpleCase_(char arg_) {
    char match_;
    int x_ = 1;
    if ((x_ != 1)) goto next_2;
    milone_assert((x_ == 1), 6, 14);
    match_ = 0;
    goto end_match_1;
next_2:;
    milone_assert(false, 7, 9);
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    return 0;
}

struct IntIntTuple2 {
    int t0;
    int t1;
};

char shadowingCase_(char arg_1) {
    int x_1 = 1;
    char match_1;
    struct IntIntTuple2 tuple_ = (struct IntIntTuple2){.t0 = x_1, .t1 = 2};
    struct IntIntTuple2 y_ = tuple_;
    int x_2 = y_.t1;
    int y1_ = y_.t0;
    int y2_ = y_.t1;
    bool if_;
    if ((x_2 == 2)) {
        goto then_7;
    } else {
        goto else_8;
    }
then_7:;
    if_ = (y1_ == 1);
    goto if_next_6;
else_8:;
    if_ = false;
    goto if_next_6;
if_next_6:;
    bool if_1;
    if (if_) {
        goto then_10;
    } else {
        goto else_11;
    }
then_10:;
    if_1 = (y2_ == 2);
    goto if_next_9;
else_11:;
    if_1 = false;
    goto if_next_9;
if_next_9:;
    milone_assert(if_1, 15, 6);
    match_1 = 0;
    goto end_match_4;
next_5:;
end_match_4:;
    return 0;
}

int milone_main() {
    char call_ = simpleCase_(0);
    char call_1 = shadowingCase_(0);
    return 0;
}
