#include "milone.h"

int intCmp_(int l_, int r_);

int main();

int intCmp_(int l_, int r_) {
    int int_compare_result_ = int_compare(l_, r_);
    return int_compare_result_;
}

int main() {
    int call_ = intCmp_(5, 3);
    milone_assert((call_ == 1), 4, 2);
    return 0;
}
