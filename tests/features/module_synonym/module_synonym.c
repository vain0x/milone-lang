#include "milone.h"

int inc_(int x_);

int milone_main();

int inc_(int x_) {
    return (x_ + 1);
}

int milone_main() {
    int call_ = inc_(2);
    milone_assert((call_ == 3), 7, 2);
    return 0;
}
