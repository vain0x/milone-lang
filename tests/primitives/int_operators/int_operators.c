#include <milone.h>

void int_operators_int_operators_literalTest(void);

void int_operators_int_operators_hexLiteralTest(void);

void int_operators_int_operators_arithmeticOperatorsTest(int two_, int three_, int thirtyNine_);

void int_operators_int_operators_bitOperatorsTest(int n1_);

void int_operators_int_operators_compareTest(int n2_1, int n3_);

void int_operators_int_operators_toIntTest(void);

int main(int argc, char** argv);

void int_operators_int_operators_literalTest(void) {
    milone_assert(((-(((int32_t)0x80000000 + 1))) == 2147483647), (struct String){.str = "int_operators/int_operators.milone", .len = 34}, 4, 2);
    return;
}

void int_operators_int_operators_hexLiteralTest(void) {
    milone_assert(((int32_t)0x00000000 == 0), (struct String){.str = "int_operators/int_operators.milone", .len = 34}, 7, 2);
    milone_assert(((int32_t)0x10 == 16), (struct String){.str = "int_operators/int_operators.milone", .len = 34}, 8, 2);
    milone_assert(((int32_t)0x7fffffff == 2147483647), (struct String){.str = "int_operators/int_operators.milone", .len = 34}, 9, 2);
    milone_assert(((int32_t)0xffffffff == -1), (struct String){.str = "int_operators/int_operators.milone", .len = 34}, 10, 2);
    return;
}

void int_operators_int_operators_arithmeticOperatorsTest(int two_, int three_, int thirtyNine_) {
    milone_assert(((two_ + three_) == 5), (struct String){.str = "int_operators/int_operators.milone", .len = 34}, 13, 2);
    milone_assert(((three_ - two_) == 1), (struct String){.str = "int_operators/int_operators.milone", .len = 34}, 14, 2);
    milone_assert(((two_ * three_) == 6), (struct String){.str = "int_operators/int_operators.milone", .len = 34}, 15, 2);
    milone_assert(((thirtyNine_ / two_) == 19), (struct String){.str = "int_operators/int_operators.milone", .len = 34}, 16, 2);
    milone_assert(((thirtyNine_ / three_) == 13), (struct String){.str = "int_operators/int_operators.milone", .len = 34}, 17, 2);
    milone_assert(((thirtyNine_ % two_) == 1), (struct String){.str = "int_operators/int_operators.milone", .len = 34}, 18, 2);
    milone_assert(((thirtyNine_ % three_) == 0), (struct String){.str = "int_operators/int_operators.milone", .len = 34}, 19, 2);
    milone_assert(((-(two_)) == -2), (struct String){.str = "int_operators/int_operators.milone", .len = 34}, 21, 2);
    return;
}

void int_operators_int_operators_bitOperatorsTest(int n1_) {
    int n2_ = (n1_ * 2);
    int n4_ = (n2_ * 2);
    int n8_ = (n4_ * 2);
    int n16_ = (n8_ * 2);
    milone_assert(((((n1_ + n2_) + n4_) & ((n2_ + n4_) + n8_)) == (n2_ + n4_)), (struct String){.str = "int_operators/int_operators.milone", .len = 34}, 29, 2);
    milone_assert(((((n1_ + n2_) + n4_) | ((n2_ + n4_) + n8_)) == (((n1_ + n2_) + n4_) + n8_)), (struct String){.str = "int_operators/int_operators.milone", .len = 34}, 30, 2);
    milone_assert(((((n1_ + n2_) + n4_) ^ ((n2_ + n4_) + n8_)) == (n1_ + n8_)), (struct String){.str = "int_operators/int_operators.milone", .len = 34}, 31, 2);
    milone_assert(((n1_ << 0) == n1_), (struct String){.str = "int_operators/int_operators.milone", .len = 34}, 33, 2);
    milone_assert(((n1_ << 1) == n2_), (struct String){.str = "int_operators/int_operators.milone", .len = 34}, 34, 2);
    milone_assert(((((n1_ + n2_) + n8_) << 1) == ((n2_ + n4_) + n16_)), (struct String){.str = "int_operators/int_operators.milone", .len = 34}, 35, 2);
    milone_assert(((n4_ >> 0) == n4_), (struct String){.str = "int_operators/int_operators.milone", .len = 34}, 37, 2);
    milone_assert(((n4_ >> 1) == n2_), (struct String){.str = "int_operators/int_operators.milone", .len = 34}, 38, 2);
    milone_assert(((n4_ >> 2) == n1_), (struct String){.str = "int_operators/int_operators.milone", .len = 34}, 39, 2);
    milone_assert(((n4_ >> 3) == 0), (struct String){.str = "int_operators/int_operators.milone", .len = 34}, 40, 2);
    milone_assert(((((n1_ + n2_) + n8_) >> 1) == ((0 + n1_) + n4_)), (struct String){.str = "int_operators/int_operators.milone", .len = 34}, 41, 2);
    return;
}

void int_operators_int_operators_compareTest(int n2_1, int n3_) {
    milone_assert((n2_1 == 2), (struct String){.str = "int_operators/int_operators.milone", .len = 34}, 44, 2);
    milone_assert((n3_ != 2), (struct String){.str = "int_operators/int_operators.milone", .len = 34}, 45, 2);
    milone_assert((2 >= n2_1), (struct String){.str = "int_operators/int_operators.milone", .len = 34}, 47, 2);
    milone_assert((n3_ >= n2_1), (struct String){.str = "int_operators/int_operators.milone", .len = 34}, 48, 2);
    milone_assert((n2_1 < n3_), (struct String){.str = "int_operators/int_operators.milone", .len = 34}, 49, 2);
    milone_assert((n2_1 < n3_), (struct String){.str = "int_operators/int_operators.milone", .len = 34}, 51, 2);
    milone_assert((int_compare(n2_1, 3) < 0), (struct String){.str = "int_operators/int_operators.milone", .len = 34}, 53, 2);
    milone_assert((int_compare(n2_1, 2) == 0), (struct String){.str = "int_operators/int_operators.milone", .len = 34}, 54, 2);
    milone_assert((0 < int_compare(n3_, 2)), (struct String){.str = "int_operators/int_operators.milone", .len = 34}, 55, 2);
    return;
}

void int_operators_int_operators_toIntTest(void) {
    milone_assert((0 == 0), (struct String){.str = "int_operators/int_operators.milone", .len = 34}, 58, 2);
    milone_assert((((int)'a') == 97), (struct String){.str = "int_operators/int_operators.milone", .len = 34}, 59, 2);
    int call_ = str_to_int((struct String){.str = "42", .len = 2});
    milone_assert((call_ == 42), (struct String){.str = "int_operators/int_operators.milone", .len = 34}, 60, 2);
    int call_1 = str_to_int((struct String){.str = "-1", .len = 2});
    milone_assert(((call_1 + 1) == 0), (struct String){.str = "int_operators/int_operators.milone", .len = 34}, 61, 2);
    return;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    int_operators_int_operators_literalTest();
    int_operators_int_operators_hexLiteralTest();
    int_operators_int_operators_arithmeticOperatorsTest(2, 3, 39);
    int_operators_int_operators_bitOperatorsTest(1);
    int_operators_int_operators_compareTest(2, 3);
    int_operators_int_operators_toIntTest();
    return 0;
}
