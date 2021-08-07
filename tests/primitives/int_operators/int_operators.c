#include "milone.h"

char int_operators_Program_literalTest(char arg_);

char int_operators_Program_hexLiteralTest(char arg_1);

char int_operators_Program_arithmeticOperatorsTest(int two_, int three_, int thirtyNine_);

char int_operators_Program_bitOperatorsTest(int n1_);

char int_operators_Program_compareTest(int n2_1, int n3_);

char int_operators_Program_toIntTest(char arg_2);

int milone_main();

char int_operators_Program_literalTest(char arg_) {
    milone_assert(((-((-2147483648 + 1))) == 2147483647), 4, 2);
    return 0;
}

char int_operators_Program_hexLiteralTest(char arg_1) {
    milone_assert((0x00000000 == 0), 7, 2);
    milone_assert((0x10 == 16), 8, 2);
    milone_assert((0x7fffffff == 2147483647), 9, 2);
    return 0;
}

char int_operators_Program_arithmeticOperatorsTest(int two_, int three_, int thirtyNine_) {
    milone_assert(((two_ + three_) == 5), 12, 2);
    milone_assert(((three_ - two_) == 1), 13, 2);
    milone_assert(((two_ * three_) == 6), 14, 2);
    milone_assert(((thirtyNine_ / two_) == 19), 15, 2);
    milone_assert(((thirtyNine_ / three_) == 13), 16, 2);
    milone_assert(((thirtyNine_ % two_) == 1), 17, 2);
    milone_assert(((thirtyNine_ % three_) == 0), 18, 2);
    milone_assert(((-(two_)) == -2), 20, 2);
    return 0;
}

char int_operators_Program_bitOperatorsTest(int n1_) {
    int n2_ = (n1_ * 2);
    int n4_ = (n2_ * 2);
    int n8_ = (n4_ * 2);
    int n16_ = (n8_ * 2);
    milone_assert(((((n1_ + n2_) + n4_) & ((n2_ + n4_) + n8_)) == (n2_ + n4_)), 28, 2);
    milone_assert(((((n1_ + n2_) + n4_) | ((n2_ + n4_) + n8_)) == (((n1_ + n2_) + n4_) + n8_)), 29, 2);
    milone_assert(((((n1_ + n2_) + n4_) ^ ((n2_ + n4_) + n8_)) == (n1_ + n8_)), 30, 2);
    milone_assert(((n1_ << 0) == n1_), 32, 2);
    milone_assert(((n1_ << 1) == n2_), 33, 2);
    milone_assert(((((n1_ + n2_) + n8_) << 1) == ((n2_ + n4_) + n16_)), 34, 2);
    milone_assert(((n4_ >> 0) == n4_), 36, 2);
    milone_assert(((n4_ >> 1) == n2_), 37, 2);
    milone_assert(((n4_ >> 2) == n1_), 38, 2);
    milone_assert(((n4_ >> 3) == 0), 39, 2);
    milone_assert(((((n1_ + n2_) + n8_) >> 1) == ((0 + n1_) + n4_)), 40, 2);
    return 0;
}

char int_operators_Program_compareTest(int n2_1, int n3_) {
    milone_assert((n2_1 == 2), 43, 2);
    milone_assert((n3_ != 2), 44, 2);
    milone_assert((2 >= n2_1), 46, 2);
    milone_assert((n3_ >= n2_1), 47, 2);
    milone_assert((n2_1 < n3_), 48, 2);
    milone_assert((n2_1 < n3_), 50, 2);
    milone_assert((int_compare(n2_1, 3) < 0), 52, 2);
    milone_assert((int_compare(n2_1, 2) == 0), 53, 2);
    milone_assert((0 < int_compare(n3_, 2)), 54, 2);
    return 0;
}

char int_operators_Program_toIntTest(char arg_2) {
    milone_assert((0 == 0), 57, 2);
    milone_assert((((int)'a') == 97), 58, 2);
    int call_ = str_to_int((struct String){.str = "42", .len = 2});
    milone_assert((call_ == 42), 59, 2);
    int call_1 = str_to_int((struct String){.str = "-1", .len = 2});
    milone_assert(((call_1 + 1) == 0), 60, 2);
    return 0;
}

int milone_main() {
    char call_2 = int_operators_Program_literalTest(0);
    char call_3 = int_operators_Program_hexLiteralTest(0);
    char call_4 = int_operators_Program_arithmeticOperatorsTest(2, 3, 39);
    char call_5 = int_operators_Program_bitOperatorsTest(1);
    char call_6 = int_operators_Program_compareTest(2, 3);
    char call_7 = int_operators_Program_toIntTest(0);
    return 0;
}
