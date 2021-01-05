#include "milone.h"

struct SubRecord_;

enum SubUnion_Discriminant;

struct SubUnion_;

int main();

struct SubRecord_ {
    struct String t0;
};

enum SubUnion_Discriminant {
    SubUnion_,
};

struct SubUnion_ {
    enum SubUnion_Discriminant discriminant;
    union {
        int SubUnion_;
    };
};

int main() {
    struct SubRecord_ SubRecord_ = (struct SubRecord_){.t0 = (struct String){.str = "Hello", .len = 5}};
    struct SubRecord_ text_ = SubRecord_;
    milone_assert((text_.t0.len == 5), 8, 2);
    int match_;
    struct SubUnion_ variant_ = (struct SubUnion_){.discriminant = SubUnion_, .SubUnion_ = 42};
    int value_ = variant_.SubUnion_;
    milone_assert((value_ == 42), 11, 35);
    match_ = 0;
    goto end_match_1;
next_2:;
end_match_1:;
    return 0;
}
