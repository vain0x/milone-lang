#include "milone.h"

int f_(int arg_);

int g_(int arg_1);

int main();

int f_(int arg_) {
    int call_ = g_(0);
    return call_;
}

int g_(int arg_1) {
    return 0;
}

int main() {
    int call_1 = f_(0);
    milone_assert((call_1 == 0), 17, 2);
    return 0;
}
