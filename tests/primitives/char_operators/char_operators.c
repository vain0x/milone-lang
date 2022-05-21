#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

void char_operators_char_operators_testAddition(void);

void char_operators_char_operators_testEquality(void);

void char_operators_char_operators_testConversion(void);

int main(int argc, char **argv);

void char_operators_char_operators_testAddition(void) {
    if ((('\r' + '\n') != ((char)((uint8_t)13U + (uint8_t)10U)))) milone_assert_error("char_operators/char_operators.milone", 3, 2);
    return;
}

void char_operators_char_operators_testEquality(void) {
    if (('A' != 'A')) milone_assert_error("char_operators/char_operators.milone", 6, 2);
    if (('A' == 'a')) milone_assert_error("char_operators/char_operators.milone", 7, 2);
    return;
}

void char_operators_char_operators_testConversion(void) {
    char char_of_string;
    if (('A' != 'A')) milone_assert_error("char_operators/char_operators.milone", 10, 2);
    char_of_string = string_to_char((struct String){.ptr = "A", .len = 1});
    if ((char_of_string != 'A')) milone_assert_error("char_operators/char_operators.milone", 11, 2);
    if ((((char)(uint8_t)65U) != 'A')) milone_assert_error("char_operators/char_operators.milone", 14, 2);
    if ((((char)(int8_t)65) != 'A')) milone_assert_error("char_operators/char_operators.milone", 15, 2);
    if ((((char)(uint8_t)0U) != '\0')) milone_assert_error("char_operators/char_operators.milone", 17, 2);
    if ((((char)(uint8_t)127U) != '\x7f')) milone_assert_error("char_operators/char_operators.milone", 18, 2);
    if ((((char)(uint8_t)255U) != (char)'\xff')) milone_assert_error("char_operators/char_operators.milone", 19, 2);
    return;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    char_operators_char_operators_testAddition();
    char_operators_char_operators_testEquality();
    char_operators_char_operators_testConversion();
    return 0;
}
