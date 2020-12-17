#include "milone.h"

int f_(int arg_);

int g_(int arg_1);

static int success_;

int main();

int f_(int arg_) {
    return success_;
}

int g_(int arg_1) {
    int call_ = f_(0);
    return call_;
}

int main() {
    success_ = 0;
    int call_1 = g_(0);
    return call_1;
}
