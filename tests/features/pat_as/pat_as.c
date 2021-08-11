#include "milone.h"

struct IntIntTuple2_;

char pat_as_Program_simpleCase(char arg_);

char pat_as_Program_shadowingCase(char arg_1);

int milone_main();

struct IntIntTuple2_ {
    int t0;
    int t1;
};

char pat_as_Program_simpleCase(char arg_) {
    int x_;
    char match_;
    x_ = 1;
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

char pat_as_Program_shadowingCase(char arg_1) {
    int x_2;
    struct IntIntTuple2_ y_;
    int x_1 = 1;
    char match_1;
    struct IntIntTuple2_ IntIntTuple2_ = (struct IntIntTuple2_){.t0 = x_1, .t1 = 2};
    y_ = IntIntTuple2_;
    x_2 = y_.t1;
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
    milone_assert(if_1, 15, 4);
    match_1 = 0;
    goto end_match_4;
next_5:;
end_match_4:;
    return 0;
}

int milone_main() {
    char call_ = pat_as_Program_simpleCase(0);
    char call_1 = pat_as_Program_shadowingCase(0);
    return 0;
}
