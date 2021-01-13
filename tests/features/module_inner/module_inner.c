#include "milone.h"

int f_(int x_);

int milone_main();

int f_(int x_) {
    return (x_ + 1);
}

int milone_main() {
    int call_ = f_(2);
    milone_assert((call_ == 3), 8, 2);
    return 0;
}
