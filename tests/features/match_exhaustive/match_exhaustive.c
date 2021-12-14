#include <milone.h>

int match_exhaustive_match_exhaustive_main_f(int x_);

int main(int argc, char** argv);

int match_exhaustive_match_exhaustive_main_f(int x_) {
    return (x_ * x_);
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    int y_;
    int match_;
    int call_ = match_exhaustive_match_exhaustive_main_f(3);
    if ((call_ != 1)) goto next_2;
    milone_assert(false, (struct String){.str = "match_exhaustive/match_exhaustive.milone", .len = 40}, 9, 4);
    match_ = 1;
    goto end_match_1;
next_2:;
    y_ = call_;
    milone_assert((y_ == 9), (struct String){.str = "match_exhaustive/match_exhaustive.milone", .len = 40}, 13, 4);
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    return match_;
}
