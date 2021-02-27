#include "milone.h"

int f_(char arg_);

int g_(char arg_1);

static int success_;

int milone_main();

int f_(char arg_) {
    return success_;
}

int g_(char arg_1) {
    int call_ = f_(0);
    return call_;
}

int milone_main() {
    success_ = 0;
    int call_1 = g_(0);
    return call_1;
}
