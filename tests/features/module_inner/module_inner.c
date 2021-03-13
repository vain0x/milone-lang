#include "milone.h"

int decrement_(int x_);

int f_(int x_1);

int milone_main();

int decrement_(int x_) {
    return (x_ - 1);
}

int f_(int x_1) {
    return (x_1 + 1);
}

int milone_main() {
    int call_ = f_(2);
    milone_assert((call_ == 3), 11, 2);
    int call_1 = decrement_(3);
    milone_assert((call_1 == 2), 14, 2);
    return 0;
}
