#include "milone.h"

struct SubRecord_;

enum SubUnion_Tag;

struct SubUnion_;

int main();

struct SubRecord_ {
    struct String Text;
};

enum SubUnion_Tag {
    SubUnion_,
};

struct SubUnion_ {
    enum SubUnion_Tag tag;
    union {
        int SubUnion_;
    };
};

int main() {
    struct SubRecord_ SubRecord_;
    SubRecord_.Text = (struct String){.str = "Hello", .len = 5};
    struct SubRecord_ text_ = SubRecord_;
    milone_assert((text_.Text.len == 5), 6, 2);
    int match_;
    struct SubUnion_ variant_ = (struct SubUnion_){.tag = SubUnion_, .SubUnion_ = 42};
    int value_ = variant_.SubUnion_;
    milone_assert((value_ == 42), 9, 35);
    match_ = 0;
    goto end_match_1;
next_2:;
    exit(1);
end_match_1:;
    return 0;
}
