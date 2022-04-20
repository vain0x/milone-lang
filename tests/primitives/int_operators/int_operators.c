#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

void int_operators_int_operators_literalTest(void);

void int_operators_int_operators_hexLiteralTest(void);

void int_operators_int_operators_arithmeticOperatorsTest(int32_t two_, int32_t three_, int32_t thirtyNine_);

void int_operators_int_operators_bitOperatorsTest(int32_t n1_);

void int_operators_int_operators_compareTest(int32_t n2_1, int32_t n3_);

void int_operators_int_operators_toIntTest(void);

int main(int argc, char **argv);

void int_operators_int_operators_literalTest(void) {
    if (((-(((int32_t)0x80000000 + 1))) != 2147483647)) milone_assert_error("int_operators/int_operators.milone", 4, 2);
    return;
}

void int_operators_int_operators_hexLiteralTest(void) {
    if (((int32_t)0x00000000 != 0)) milone_assert_error("int_operators/int_operators.milone", 7, 2);
    if (((int32_t)0x10 != 16)) milone_assert_error("int_operators/int_operators.milone", 8, 2);
    if (((int32_t)0x7fffffff != 2147483647)) milone_assert_error("int_operators/int_operators.milone", 9, 2);
    if (((int32_t)0xffffffff != -1)) milone_assert_error("int_operators/int_operators.milone", 10, 2);
    return;
}

void int_operators_int_operators_arithmeticOperatorsTest(int32_t two_, int32_t three_, int32_t thirtyNine_) {
    if (((two_ + three_) != 5)) milone_assert_error("int_operators/int_operators.milone", 13, 2);
    if (((three_ - two_) != 1)) milone_assert_error("int_operators/int_operators.milone", 14, 2);
    if (((two_ * three_) != 6)) milone_assert_error("int_operators/int_operators.milone", 15, 2);
    if (((thirtyNine_ / two_) != 19)) milone_assert_error("int_operators/int_operators.milone", 16, 2);
    if (((thirtyNine_ / three_) != 13)) milone_assert_error("int_operators/int_operators.milone", 17, 2);
    if (((thirtyNine_ % two_) != 1)) milone_assert_error("int_operators/int_operators.milone", 18, 2);
    if (((thirtyNine_ % three_) != 0)) milone_assert_error("int_operators/int_operators.milone", 19, 2);
    if (((-(two_)) != -2)) milone_assert_error("int_operators/int_operators.milone", 21, 2);
    return;
}

void int_operators_int_operators_bitOperatorsTest(int32_t n1_) {
    int32_t n2_;
    int32_t n4_;
    int32_t n8_;
    int32_t n16_;
    n2_ = (n1_ * 2);
    n4_ = (n2_ * 2);
    n8_ = (n4_ * 2);
    n16_ = (n8_ * 2);
    if (((((n1_ + n2_) + n4_) & ((n2_ + n4_) + n8_)) != (n2_ + n4_))) milone_assert_error("int_operators/int_operators.milone", 29, 2);
    if (((((n1_ + n2_) + n4_) | ((n2_ + n4_) + n8_)) != (((n1_ + n2_) + n4_) + n8_))) milone_assert_error("int_operators/int_operators.milone", 30, 2);
    if (((((n1_ + n2_) + n4_) ^ ((n2_ + n4_) + n8_)) != (n1_ + n8_))) milone_assert_error("int_operators/int_operators.milone", 31, 2);
    if (((n1_ << 0) != n1_)) milone_assert_error("int_operators/int_operators.milone", 33, 2);
    if (((n1_ << 1) != n2_)) milone_assert_error("int_operators/int_operators.milone", 34, 2);
    if (((((n1_ + n2_) + n8_) << 1) != ((n2_ + n4_) + n16_))) milone_assert_error("int_operators/int_operators.milone", 35, 2);
    if (((n4_ >> 0) != n4_)) milone_assert_error("int_operators/int_operators.milone", 37, 2);
    if (((n4_ >> 1) != n2_)) milone_assert_error("int_operators/int_operators.milone", 38, 2);
    if (((n4_ >> 2) != n1_)) milone_assert_error("int_operators/int_operators.milone", 39, 2);
    if (((n4_ >> 3) != 0)) milone_assert_error("int_operators/int_operators.milone", 40, 2);
    if (((((n1_ + n2_) + n8_) >> 1) != ((0 + n1_) + n4_))) milone_assert_error("int_operators/int_operators.milone", 41, 2);
    return;
}

void int_operators_int_operators_compareTest(int32_t n2_1, int32_t n3_) {
    if ((n2_1 != 2)) milone_assert_error("int_operators/int_operators.milone", 44, 2);
    if ((n3_ == 2)) milone_assert_error("int_operators/int_operators.milone", 45, 2);
    if ((2 < n2_1)) milone_assert_error("int_operators/int_operators.milone", 47, 2);
    if ((n3_ < n2_1)) milone_assert_error("int_operators/int_operators.milone", 48, 2);
    if ((n2_1 >= n3_)) milone_assert_error("int_operators/int_operators.milone", 49, 2);
    if ((n2_1 >= n3_)) milone_assert_error("int_operators/int_operators.milone", 51, 2);
    if ((milone_int32_compare(n2_1, 3) >= 0)) milone_assert_error("int_operators/int_operators.milone", 53, 2);
    if ((milone_int32_compare(n2_1, 2) != 0)) milone_assert_error("int_operators/int_operators.milone", 54, 2);
    if ((0 >= milone_int32_compare(n3_, 2))) milone_assert_error("int_operators/int_operators.milone", 55, 2);
    return;
}

void int_operators_int_operators_toIntTest(void) {
    int32_t call_;
    int32_t call_1;
    if ((0 != 0)) milone_assert_error("int_operators/int_operators.milone", 58, 2);
    if ((((int32_t)'a') != 97)) milone_assert_error("int_operators/int_operators.milone", 59, 2);
    call_ = string_to_int32((struct String){.ptr = "42", .len = 2});
    if ((call_ != 42)) milone_assert_error("int_operators/int_operators.milone", 60, 2);
    call_1 = string_to_int32((struct String){.ptr = "-1", .len = 2});
    if (((call_1 + 1) != 0)) milone_assert_error("int_operators/int_operators.milone", 61, 2);
    return;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    int_operators_int_operators_literalTest();
    int_operators_int_operators_hexLiteralTest();
    int_operators_int_operators_arithmeticOperatorsTest(2, 3, 39);
    int_operators_int_operators_bitOperatorsTest(1);
    int_operators_int_operators_compareTest(2, 3);
    int_operators_int_operators_toIntTest();
    return 0;
}
