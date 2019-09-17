#include "milone.h"

int even_(int n_);

int odd_(int n_1);

int main();

int even_(int n_) {
    int match_;
    if (!(((n_ == 0) == 1))) goto next_2;
    match_ = 1;
    goto end_match_1;
next_2:;
    if (!(((n_ == 0) == 0))) goto next_3;
    int call_ = odd_((n_ - 1));
    match_ = call_;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return match_;
}

int odd_(int n_1) {
    int match_1;
    if (!(((n_1 != 0) == 1))) goto next_5;
    int call_1 = even_((n_1 - 1));
    match_1 = call_1;
    goto end_match_4;
next_5:;
    if (!(((n_1 != 0) == 0))) goto next_6;
    match_1 = 0;
    goto end_match_4;
next_6:;
    exit(1);
end_match_4:;
    return match_1;
}

int main() {
    int call_2 = odd_(1);
    milone_assert(call_2, 9, 2);
    int call_3 = 0;
    int call_4 = even_(2);
    milone_assert(call_4, 10, 2);
    int call_5 = 0;
    int call_6 = even_(3);
    milone_assert((!(call_6)), 11, 2);
    int call_7 = 0;
    return 0;
}
