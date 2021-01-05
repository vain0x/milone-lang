#include "milone.h"

int literalTest_(int arg_);

int arithmeticOperatorsTest_(int two_, int three_, int thirtyNine_);

int bitOperatorsTest_(int n1_);

int compareTest_(int n2_1, int n3_);

int toIntTest_(int arg_1);

int main();

int literalTest_(int arg_) {
    milone_assert(((-((-2147483648 + 1))) == 2147483647), 4, 2);
    return 0;
}

int arithmeticOperatorsTest_(int two_, int three_, int thirtyNine_) {
    milone_assert(((two_ + three_) == 5), 7, 2);
    milone_assert(((three_ - two_) == 1), 8, 2);
    milone_assert(((two_ * three_) == 6), 9, 2);
    milone_assert(((thirtyNine_ / two_) == 19), 10, 2);
    milone_assert(((thirtyNine_ / three_) == 13), 11, 2);
    milone_assert(((thirtyNine_ % two_) == 1), 12, 2);
    milone_assert(((thirtyNine_ % three_) == 0), 13, 2);
    milone_assert(((-(two_)) == -2), 15, 2);
    return 0;
}

int bitOperatorsTest_(int n1_) {
    int n2_ = (n1_ * 2);
    int n4_ = (n2_ * 2);
    int n8_ = (n4_ * 2);
    int n16_ = (n8_ * 2);
    milone_assert(((((n1_ + n2_) + n4_) & ((n2_ + n4_) + n8_)) == (n2_ + n4_)), 23, 2);
    milone_assert(((((n1_ + n2_) + n4_) | ((n2_ + n4_) + n8_)) == (((n1_ + n2_) + n4_) + n8_)), 24, 2);
    milone_assert(((((n1_ + n2_) + n4_) ^ ((n2_ + n4_) + n8_)) == (n1_ + n8_)), 26, 2);
    milone_assert(((n1_ << 0) == n1_), 28, 2);
    milone_assert(((n1_ << 1) == n2_), 29, 2);
    milone_assert(((((n1_ + n2_) + n8_) << 1) == ((n2_ + n4_) + n16_)), 30, 2);
    milone_assert(((n4_ >> 0) == n4_), 32, 2);
    milone_assert(((n4_ >> 1) == n2_), 33, 2);
    milone_assert(((n4_ >> 2) == n1_), 34, 2);
    milone_assert(((n4_ >> 3) == 0), 35, 2);
    milone_assert(((((n1_ + n2_) + n8_) >> 1) == ((0 + n1_) + n4_)), 36, 2);
    return 0;
}

int compareTest_(int n2_1, int n3_) {
    milone_assert((n2_1 == 2), 39, 2);
    milone_assert((n3_ != 2), 40, 2);
    milone_assert((2 >= n2_1), 42, 2);
    milone_assert((n3_ >= n2_1), 43, 2);
    milone_assert((n2_1 < n3_), 44, 2);
    milone_assert((n2_1 < n3_), 46, 2);
    milone_assert((int_compare(n2_1, 3) < 0), 48, 2);
    milone_assert((int_compare(n2_1, 2) == 0), 49, 2);
    milone_assert((0 < int_compare(n3_, 2)), 50, 2);
    return 0;
}

int toIntTest_(int arg_1) {
    milone_assert((0 == 0), 53, 2);
    milone_assert((((int)'a') == 97), 54, 2);
    int call_ = str_to_int((struct String){.str = "42", .len = 2});
    milone_assert((call_ == 42), 55, 2);
    int call_1 = str_to_int((struct String){.str = "-1", .len = 2});
    milone_assert(((call_1 + 1) == 0), 56, 2);
    return 0;
}

int main() {
    int call_2 = literalTest_(0);
    int call_3 = arithmeticOperatorsTest_(2, 3, 39);
    int call_4 = bitOperatorsTest_(1);
    int call_5 = compareTest_(2, 3);
    int call_6 = toIntTest_(0);
    return 0;
}
