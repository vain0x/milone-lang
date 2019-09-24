#include "milone.h"

int sub_(int step_, int x_);

int basicCase_(int arg_);

int inc_(int step_1, int x_1);

int incTwice_(int step_1, int x_2);

int transitiveCase_(int arg_1);

int inc_1(int step_2, int x_3);

int go_(int step_2, int n_);

int recursiveCase_(int arg_2);

int main();

int sub_(int step_, int x_) {
    return (x_ - step_);
}

int basicCase_(int arg_) {
    int step_ = 3;
    int call_ = sub_(step_, 8);
    milone_assert((call_ == 5), 3, 2);
    int call_1 = 0;
    return 0;
}

int inc_(int step_1, int x_1) {
    return (x_1 + step_1);
}

int incTwice_(int step_1, int x_2) {
    int call_2 = inc_(step_1, x_2);
    int call_3 = inc_(step_1, call_2);
    return call_3;
}

int transitiveCase_(int arg_1) {
    int step_1 = 1;
    int call_4 = incTwice_(step_1, 0);
    milone_assert((call_4 == 2), 9, 2);
    int call_5 = 0;
    return 0;
}

int inc_1(int step_2, int x_3) {
    return (x_3 + step_2);
}

int go_(int step_2, int n_) {
    int match_;
    if ((n_ < 10)) goto next_2;
    match_ = 1;
    goto end_match_1;
next_2:;
    if ((n_ >= 10)) goto next_3;
    int call_6 = inc_1(step_2, n_);
    int call_7 = go_(step_2, call_6);
    match_ = call_7;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return match_;
}

int recursiveCase_(int arg_2) {
    int step_2 = 1;
    int call_8 = go_(step_2, 0);
    milone_assert(call_8, 18, 2);
    int call_9 = 0;
    return 0;
}

int main() {
    int call_10 = basicCase_(0);
    int call_11 = transitiveCase_(0);
    int call_12 = recursiveCase_(0);
    return 0;
}
