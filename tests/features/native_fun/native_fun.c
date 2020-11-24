#include "milone.h"

int intCmp_(int l_, int r_);

int main();

int intCmp_(int l_, int r_) {
    int int_cmp_result_ = int_cmp(l_, r_);
    return int_cmp_result_;
}

int main() {
    int call_ = intCmp_(5, 3);
    milone_assert((call_ == 1), 4, 2);
    return 0;
}
