#include "milone.h"

int f_(int x_);

int milone_main(void);

int f_(int x_) {
    return (x_ * x_);
}

int milone_main(void) {
    int y_;
    int match_;
    int call_ = f_(3);
    if ((call_ != 1)) goto next_2;
    milone_assert(false, 9, 4);
    match_ = 1;
    goto end_match_1;
next_2:;
    y_ = call_;
    milone_assert((y_ == 9), 13, 4);
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    return match_;
}
