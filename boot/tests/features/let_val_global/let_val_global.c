#include "milone.h"

int f_(int success_, int arg_);

int g_(int success_, int arg_1);

int main();

int f_(int success_, int arg_) {
    return success_;
}

int g_(int success_, int arg_1) {
    int call_ = f_(success_, 0);
    return call_;
}

int main() {
    int success_ = 0;
    int call_1 = g_(success_, 0);
    return call_1;
}
