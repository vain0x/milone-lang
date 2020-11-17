#include "milone.h"

int simpleCase_(int arg_);

struct IntIntTuple2;

int shadowingCase_(int arg_1);

int main();

int simpleCase_(int arg_) {
    int switch_;
    switch (1) {
       case 1:
          goto clause_2;

       default:
          goto clause_3;
    }
clause_2:;
    int x_ = 1;
    milone_assert((x_ == 1), 3, 4);
    int call_ = 0;
    switch_ = 0;
    goto switch_next_1;
clause_3:;
    milone_assert(0, 5, 4);
    int call_1 = 0;
    switch_ = 0;
    goto switch_next_1;
switch_next_1:;
    return 0;
}

struct IntIntTuple2 {
    int t0;
    int t1;
};

int shadowingCase_(int arg_1) {
    int x_1 = 1;
    int match_;
    struct IntIntTuple2 tuple_;
    tuple_.t0 = x_1;
    tuple_.t1 = 2;
    struct IntIntTuple2 y_ = tuple_;
    int x_2 = y_.t1;
    int y1_ = y_.t0;
    int y2_ = y_.t1;
    int if_;
    int if_1;
    if ((x_2 != 2)) goto else_8;
    if_1 = (y1_ == 1);
    goto end_if_9;
else_8:;
    if_1 = 0;
end_if_9:;
    if ((!(if_1))) goto else_6;
    if_ = (y2_ == 2);
    goto end_if_7;
else_6:;
    if_ = 0;
end_if_7:;
    milone_assert(if_, 12, 4);
    int call_2 = 0;
    match_ = 0;
    goto end_match_4;
next_5:;
end_match_4:;
    return 0;
}

int main() {
    int call_3 = simpleCase_(0);
    int call_4 = shadowingCase_(0);
    return 0;
}
