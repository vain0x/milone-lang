#include "milone.h"

int getAnswer_(int arg_);

static int answer_;

enum Answer_Discriminant;

struct Answer_;

int milone_main();

int getAnswer_(int arg_) {
    return 42;
}

enum Answer_Discriminant {
    Answer_,
};

struct Answer_ {
    enum Answer_Discriminant discriminant;
    union {
        int Answer_;
    };
};

int milone_main() {
    answer_ = 42;
    milone_assert((answer_ == 42), 8, 2);
    int call_ = getAnswer_(0);
    milone_assert((call_ == 42), 11, 2);
    struct Answer_ variant_ = (struct Answer_){.discriminant = Answer_, .Answer_ = 42};
    struct Answer_ myAnswer_ = variant_;
    return 0;
}
