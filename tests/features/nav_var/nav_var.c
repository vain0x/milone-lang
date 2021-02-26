#include "milone.h"

int getAnswer_(int arg_);

static int answer_;

int milone_main();

int getAnswer_(int arg_) {
    return 42;
}

int milone_main() {
    answer_ = 42;
    milone_assert((answer_ == 42), 8, 2);
    int call_ = getAnswer_(0);
    milone_assert((call_ == 42), 11, 2);
    int myAnswer_ = 42;
    return 0;
}
