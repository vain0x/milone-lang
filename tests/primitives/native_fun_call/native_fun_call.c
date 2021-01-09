#include "milone.h"

int int_compare(int, int);

int intCompare_(int l_, int r_);

int milone_main();

int intCompare_(int l_, int r_) {
    int int_compare_result_ = int_compare(l_, r_);
    return int_compare_result_;
}

int milone_main() {
    int call_ = intCompare_(5, 3);
    milone_assert((call_ == 1), 7, 2);
    return 0;
}
