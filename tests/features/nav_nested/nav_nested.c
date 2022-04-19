#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct SubRecord_;

int main(int argc, char** argv);

struct SubRecord_ {
    struct String t0;
};

int main(int argc, char** argv) {
    milone_start(argc, argv);
    struct SubRecord_ text_;
    int32_t value_;
    struct SubRecord_ SubRecord_;
    char match_;
    SubRecord_ = (struct SubRecord_){.t0 = (struct String){.ptr = "Hello", .len = 5}};
    text_ = SubRecord_;
    milone_assert((text_.t0.len == 5), (struct String){.ptr = "nav_nested/nav_nested.milone", .len = 28}, 8, 2);
    value_ = 42;
    milone_assert((value_ == 42), (struct String){.ptr = "nav_nested/nav_nested.milone", .len = 28}, 11, 35);
    match_ = 0;
    goto end_match_1;
next_2:;
end_match_1:;
    return 0;
}
