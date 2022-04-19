#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

int32_t match_exhaustive_match_exhaustive_main_f(int32_t x_);

int main(int argc, char** argv);

int32_t match_exhaustive_match_exhaustive_main_f(int32_t x_) {
    return (x_ * x_);
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    int32_t y_;
    int32_t match_;
    int32_t call_;
    call_ = match_exhaustive_match_exhaustive_main_f(3);
    if ((call_ != 1)) goto next_2;
    milone_assert(false, (struct String){.ptr = "match_exhaustive/match_exhaustive.milone", .len = 40}, 9, 4);
    match_ = 1;
    goto end_match_1;
next_2:;
    y_ = call_;
    milone_assert((y_ == 9), (struct String){.ptr = "match_exhaustive/match_exhaustive.milone", .len = 40}, 13, 4);
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    return match_;
}
