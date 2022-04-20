#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

void char_operators_char_operators_arithmeticOperatorsTest(void);

void char_operators_char_operators_comparisonOperatorsTest(void);

void char_operators_char_operators_conversionTest(void);

int main(int argc, char **argv);

void char_operators_char_operators_arithmeticOperatorsTest(void) {
    if ((('\r' + '\n') != ((char)(13 + 10)))) milone_assert_error("char_operators/char_operators.milone", 6, 2);
    return;
}

void char_operators_char_operators_comparisonOperatorsTest(void) {
    if (('A' != 'A')) milone_assert_error("char_operators/char_operators.milone", 13, 2);
    if (('A' == 'B')) milone_assert_error("char_operators/char_operators.milone", 14, 2);
    if (('A' >= 'B')) milone_assert_error("char_operators/char_operators.milone", 16, 2);
    if (('A' < 'A')) milone_assert_error("char_operators/char_operators.milone", 17, 2);
    if (('B' < 'A')) milone_assert_error("char_operators/char_operators.milone", 18, 2);
    if (('A' >= 'B')) milone_assert_error("char_operators/char_operators.milone", 20, 2);
    if (('A' < 'A')) milone_assert_error("char_operators/char_operators.milone", 21, 2);
    if (('B' < 'A')) milone_assert_error("char_operators/char_operators.milone", 22, 2);
    if ((('A' - 'A') != 0)) milone_assert_error("char_operators/char_operators.milone", 24, 2);
    if ((('A' - 'B') >= 0)) milone_assert_error("char_operators/char_operators.milone", 25, 2);
    if ((0 >= ('B' - 'A'))) milone_assert_error("char_operators/char_operators.milone", 26, 2);
    return;
}

void char_operators_char_operators_conversionTest(void) {
    char char_of_string;
    if (('A' != 'A')) milone_assert_error("char_operators/char_operators.milone", 29, 2);
    if ((((char)65) != 'A')) milone_assert_error("char_operators/char_operators.milone", 30, 2);
    if ((((char)(uint32_t)65U) != 'A')) milone_assert_error("char_operators/char_operators.milone", 31, 2);
    if ((((char)65.5) != 'A')) milone_assert_error("char_operators/char_operators.milone", 32, 2);
    char_of_string = string_to_char((struct String){.ptr = "A", .len = 1});
    if ((char_of_string != 'A')) milone_assert_error("char_operators/char_operators.milone", 33, 2);
    return;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    char_operators_char_operators_arithmeticOperatorsTest();
    char_operators_char_operators_comparisonOperatorsTest();
    char_operators_char_operators_conversionTest();
    return 0;
}
