#include "milone.h"

int arithmeticOperatorsTest_(int arg_);

int comparisonOperatorsTest_(int arg_1);

int main();

int arithmeticOperatorsTest_(int arg_) {
    milone_assert((('\r' + '\n') == ((char)(13 + 10))), 6, 2);
    return 0;
}

int comparisonOperatorsTest_(int arg_1) {
    milone_assert(('A' == 'A'), 13, 2);
    milone_assert(('A' != 'B'), 14, 2);
    milone_assert(('A' < 'B'), 16, 2);
    milone_assert(('A' >= 'A'), 17, 2);
    milone_assert(('B' >= 'A'), 18, 2);
    milone_assert(('A' < 'B'), 20, 2);
    milone_assert(('A' >= 'A'), 21, 2);
    milone_assert(('B' >= 'A'), 22, 2);
    milone_assert((('A' - 'A') == 0), 24, 2);
    milone_assert((('A' - 'B') < 0), 25, 2);
    milone_assert((0 < ('B' - 'A')), 26, 2);
    return 0;
}

int main() {
    int call_ = arithmeticOperatorsTest_(0);
    int call_1 = comparisonOperatorsTest_(0);
    return 0;
}
