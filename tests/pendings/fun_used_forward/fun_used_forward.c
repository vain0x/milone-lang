#include "milone.h"

int f_(char arg_);

int g_(char arg_1);

int milone_main();

int f_(char arg_) {
    int call_ = g_(0);
    return call_;
}

int g_(char arg_1) {
    return 0;
}

int milone_main() {
    int call_1 = f_(0);
    milone_assert((call_1 == 0), 17, 2);
    return 0;
}
