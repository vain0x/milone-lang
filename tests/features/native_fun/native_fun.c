#include "milone.h"

int int_compare(int, int);

int intCompare_(int l_, int r_);

int main();

int intCompare_(int l_, int r_) {
    int int_compare_result_ = int_compare(l_, r_);
    return int_compare_result_;
}

int main() {
    int call_ = intCompare_(5, 3);
    milone_assert((call_ == 1), 4, 2);
    return 0;
}
