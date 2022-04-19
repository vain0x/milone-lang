#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

void char_operators_char_operators_arithmeticOperatorsTest(void);

void char_operators_char_operators_comparisonOperatorsTest(void);

void char_operators_char_operators_conversionTest(void);

int main(int argc, char** argv);

void char_operators_char_operators_arithmeticOperatorsTest(void) {
    milone_assert((('\r' + '\n') == ((char)(13 + 10))), (struct String){.ptr = "char_operators/char_operators.milone", .len = 36}, 6, 2);
    return;
}

void char_operators_char_operators_comparisonOperatorsTest(void) {
    milone_assert(('A' == 'A'), (struct String){.ptr = "char_operators/char_operators.milone", .len = 36}, 13, 2);
    milone_assert(('A' != 'B'), (struct String){.ptr = "char_operators/char_operators.milone", .len = 36}, 14, 2);
    milone_assert(('A' < 'B'), (struct String){.ptr = "char_operators/char_operators.milone", .len = 36}, 16, 2);
    milone_assert(('A' >= 'A'), (struct String){.ptr = "char_operators/char_operators.milone", .len = 36}, 17, 2);
    milone_assert(('B' >= 'A'), (struct String){.ptr = "char_operators/char_operators.milone", .len = 36}, 18, 2);
    milone_assert(('A' < 'B'), (struct String){.ptr = "char_operators/char_operators.milone", .len = 36}, 20, 2);
    milone_assert(('A' >= 'A'), (struct String){.ptr = "char_operators/char_operators.milone", .len = 36}, 21, 2);
    milone_assert(('B' >= 'A'), (struct String){.ptr = "char_operators/char_operators.milone", .len = 36}, 22, 2);
    milone_assert((('A' - 'A') == 0), (struct String){.ptr = "char_operators/char_operators.milone", .len = 36}, 24, 2);
    milone_assert((('A' - 'B') < 0), (struct String){.ptr = "char_operators/char_operators.milone", .len = 36}, 25, 2);
    milone_assert((0 < ('B' - 'A')), (struct String){.ptr = "char_operators/char_operators.milone", .len = 36}, 26, 2);
    return;
}

void char_operators_char_operators_conversionTest(void) {
    char char_of_string;
    milone_assert(('A' == 'A'), (struct String){.ptr = "char_operators/char_operators.milone", .len = 36}, 29, 2);
    milone_assert((((char)65) == 'A'), (struct String){.ptr = "char_operators/char_operators.milone", .len = 36}, 30, 2);
    milone_assert((((char)(uint32_t)65U) == 'A'), (struct String){.ptr = "char_operators/char_operators.milone", .len = 36}, 31, 2);
    milone_assert((((char)65.5) == 'A'), (struct String){.ptr = "char_operators/char_operators.milone", .len = 36}, 32, 2);
    char_of_string = string_to_char((struct String){.ptr = "A", .len = 1});
    milone_assert((char_of_string == 'A'), (struct String){.ptr = "char_operators/char_operators.milone", .len = 36}, 33, 2);
    return;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    char_operators_char_operators_arithmeticOperatorsTest();
    char_operators_char_operators_comparisonOperatorsTest();
    char_operators_char_operators_conversionTest();
    return 0;
}
