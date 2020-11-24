#include "milone.h"

int getAnswer_(int arg_);

static int answer_;

enum Answer_Tag;

struct Answer_;

int main();

int getAnswer_(int arg_) {
    return 42;
}

// static answer_;

enum Answer_Tag {
    Answer_,
};

struct Answer_ {
    enum Answer_Tag tag;
    union {
        int Answer_;
    };
};

int main() {
    answer_ = 42;
    milone_assert((answer_ == 42), 8, 2);
    int call_ = getAnswer_(0);
    milone_assert((call_ == 42), 11, 2);
    struct Answer_ variant_ = (struct Answer_){.tag = Answer_, .Answer_ = 42};
    struct Answer_ myAnswer_ = variant_;
    return 0;
}
