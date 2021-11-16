#include "milone.h"

void char_operators_Program_arithmeticOperatorsTest(void);

void char_operators_Program_comparisonOperatorsTest(void);

void char_operators_Program_conversionTest(void);

int milone_main(void);

void char_operators_Program_arithmeticOperatorsTest(void) {
    milone_assert((('\r' + '\n') == ((char)(13 + 10))), 6, 2);
    return;
}

void char_operators_Program_comparisonOperatorsTest(void) {
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
    return;
}

void char_operators_Program_conversionTest(void) {
    milone_assert(('A' == 'A'), 29, 2);
    milone_assert((((char)65) == 'A'), 30, 2);
    milone_assert((((char)(uint32_t)65U) == 'A'), 31, 2);
    milone_assert((((char)65.5) == 'A'), 32, 2);
    char char_of_string = str_to_char((struct String){.str = "A", .len = 1});
    milone_assert((char_of_string == 'A'), 33, 2);
    return;
}

int milone_main(void) {
    char_operators_Program_arithmeticOperatorsTest();
    char_operators_Program_comparisonOperatorsTest();
    char_operators_Program_conversionTest();
    return 0;
}
