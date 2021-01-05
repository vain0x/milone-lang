#include "milone.h"

int inc_(int x_);

int main();

int inc_(int x_) {
    return (x_ + 1);
}

int main() {
    int call_ = inc_(2);
    milone_assert((call_ == 3), 7, 2);
    return 0;
}
