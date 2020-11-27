#include "milone.h"

int basicTest_(int arg_);

int compareFunTest_(int arg_1);

int main();

int basicTest_(int arg_) {
    milone_assert((2 < 3), 5, 2);
    milone_assert((2 >= 2), 6, 2);
    milone_assert((2 == 2), 8, 2);
    milone_assert((2 != 3), 9, 2);
    milone_assert((2 < 3), 11, 2);
    milone_assert((3 >= 2), 12, 2);
    return 0;
}

int compareFunTest_(int arg_1) {
    milone_assert((int_compare(2, 2) == 0), 15, 2);
    milone_assert((int_compare(2, 3) < 0), 16, 2);
    milone_assert((0 < int_compare(3, 2)), 17, 2);
    return 0;
}

int main() {
    int call_ = basicTest_(0);
    int call_1 = compareFunTest_(0);
    return 0;
}
