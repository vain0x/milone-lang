#include "milone.h"

int f_(int x_);

int main();

int f_(int x_) {
    return (x_ * x_);
}

int main() {
    int match_;
    int call_ = f_(3);
    if (!((call_ == 1))) goto next_2;
    match_ = 1;
    goto end_match_1;
next_2:;
    int y_ = call_;
    match_ = (y_ - 9);
    goto end_match_1;
next_3:;
end_match_1:;
    return match_;
}
