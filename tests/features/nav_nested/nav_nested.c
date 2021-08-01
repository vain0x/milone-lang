#include "milone.h"

struct SubRecord_;

int milone_main();

struct SubRecord_ {
    struct String t0;
};

int milone_main() {
    int value_;
    struct SubRecord_ SubRecord_ = (struct SubRecord_){.t0 = (struct String){.str = "Hello", .len = 5}};
    struct SubRecord_ text_ = SubRecord_;
    milone_assert((text_.t0.len == 5), 8, 2);
    char match_;
    value_ = 42;
    milone_assert((value_ == 42), 11, 35);
    match_ = 0;
    goto end_match_1;
next_2:;
end_match_1:;
    return 0;
}
