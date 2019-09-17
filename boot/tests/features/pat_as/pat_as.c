#include "milone.h"

int simpleCase_(int arg_);

struct IntIntTuple2;

int shadowingCase_(int arg_1);

int main();

int simpleCase_(int arg_) {
    int match_;
    int x_ = 1;
    if (!((x_ == 1))) goto next_2;
    milone_assert((x_ == 1));
    int call_ = 0;
    match_ = 0;
    goto end_match_1;
next_2:;
    milone_assert(0);
    int call_1 = 0;
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

int shadowingCase_(int arg_1) {
    int x_1 = 1;
    int match_1;
    struct IntIntTuple2 tuple_;
    tuple_.t0 = x_1;
    tuple_.t1 = 2;
    struct IntIntTuple2 y_ = tuple_;
    int x_2 = y_.t1;
    int y1_ = y_.t0;
    int y2_ = y_.t1;
    int match_2;
    int match_3;
    if (!(((x_2 == 2) == 1))) goto next_9;
    match_3 = (y1_ == 1);
    goto end_match_8;
next_9:;
    if (!(((x_2 == 2) == 0))) goto next_10;
    match_3 = 0;
    goto end_match_8;
next_10:;
    exit(1);
end_match_8:;
    if (!((match_3 == 1))) goto next_11;
    match_2 = (y2_ == 2);
    goto end_match_7;
next_11:;
    if (!((match_3 == 0))) goto next_12;
    match_2 = 0;
    goto end_match_7;
next_12:;
    exit(1);
end_match_7:;
    milone_assert(match_2);
    int call_2 = 0;
    match_1 = 0;
    goto end_match_4;
next_5:;
    milone_assert(0);
    int call_3 = 0;
    match_1 = 0;
    goto end_match_4;
next_6:;
end_match_4:;
    return 0;
}

int main() {
    int call_4 = simpleCase_(0);
    int call_5 = shadowingCase_(0);
    return 0;
}
