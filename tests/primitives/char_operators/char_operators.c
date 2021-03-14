#include "milone.h"

char arithmeticOperatorsTest_(char arg_);

char comparisonOperatorsTest_(char arg_1);

char conversionTest_(char arg_2);

int milone_main();

char arithmeticOperatorsTest_(char arg_) {
    milone_assert((('\r' + '\n') == ((char)(13 + 10))), 6, 2);
    return 0;
}

char comparisonOperatorsTest_(char arg_1) {
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

char conversionTest_(char arg_2) {
    milone_assert(('A' == 'A'), 29, 2);
    milone_assert((((char)65) == 'A'), 30, 2);
    milone_assert((((char)((uint32_t)65)) == 'A'), 31, 2);
    milone_assert((((char)65.5) == 'A'), 32, 2);
    char char_of_string_ = str_to_char((struct String){.str = "A", .len = 1});
    milone_assert((char_of_string_ == 'A'), 33, 2);
    return 0;
}

int milone_main() {
    char call_ = arithmeticOperatorsTest_(0);
    char call_1 = comparisonOperatorsTest_(0);
    char call_2 = conversionTest_(0);
    return 0;
}
