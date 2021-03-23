#include "milone.h"

int f_(char arg_);

int g_(char arg_1);

int milone_main();

int success_;

static int failure_;

int f_(char arg_) {
    return success_;
}

int g_(char arg_1) {
    int call_ = f_(0);
    return call_;
}

int milone_main() {
    success_ = 0;
    failure_ = 1;
    int call_1 = g_(0);
    milone_assert((call_1 == 0), 13, 2);
    milone_assert((failure_ == 1), 14, 2);
    return 0;
}
