#include "milone.h"

char literalTest_(char arg_);

char arithmeticOperatorsTest_(int two_, int three_, int thirtyNine_);

char bitOperatorsTest_(int n1_);

char compareTest_(int n2_1, int n3_);

char toIntTest_(char arg_1);

int milone_main();

char literalTest_(char arg_) {
    milone_assert(((-((-2147483648 + 1))) == 2147483647), 4, 2);
    return 0;
}

char arithmeticOperatorsTest_(int two_, int three_, int thirtyNine_) {
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

char bitOperatorsTest_(int n1_) {
    int n2_ = (n1_ * 2);
    int n4_ = (n2_ * 2);
    int n8_ = (n4_ * 2);
    int n16_ = (n8_ * 2);
    milone_assert(((((n1_ + n2_) + n4_) & ((n2_ + n4_) + n8_)) == (n2_ + n4_)), 23, 2);
    milone_assert(((((n1_ + n2_) + n4_) | ((n2_ + n4_) + n8_)) == (((n1_ + n2_) + n4_) + n8_)), 24, 2);
    milone_assert(((((n1_ + n2_) + n4_) ^ ((n2_ + n4_) + n8_)) == (n1_ + n8_)), 25, 2);
    milone_assert(((n1_ << 0) == n1_), 27, 2);
    milone_assert(((n1_ << 1) == n2_), 28, 2);
    milone_assert(((((n1_ + n2_) + n8_) << 1) == ((n2_ + n4_) + n16_)), 29, 2);
    milone_assert(((n4_ >> 0) == n4_), 31, 2);
    milone_assert(((n4_ >> 1) == n2_), 32, 2);
    milone_assert(((n4_ >> 2) == n1_), 33, 2);
    milone_assert(((n4_ >> 3) == 0), 34, 2);
    milone_assert(((((n1_ + n2_) + n8_) >> 1) == ((0 + n1_) + n4_)), 35, 2);
    return 0;
}

char compareTest_(int n2_1, int n3_) {
    milone_assert((n2_1 == 2), 38, 2);
    milone_assert((n3_ != 2), 39, 2);
    milone_assert((2 >= n2_1), 41, 2);
    milone_assert((n3_ >= n2_1), 42, 2);
    milone_assert((n2_1 < n3_), 43, 2);
    milone_assert((n2_1 < n3_), 45, 2);
    milone_assert((int_compare(n2_1, 3) < 0), 47, 2);
    milone_assert((int_compare(n2_1, 2) == 0), 48, 2);
    milone_assert((0 < int_compare(n3_, 2)), 49, 2);
    return 0;
}

char toIntTest_(char arg_1) {
    milone_assert((0 == 0), 52, 2);
    milone_assert((((int)'a') == 97), 53, 2);
    int call_ = str_to_int((struct String){.str = "42", .len = 2});
    milone_assert((call_ == 42), 54, 2);
    int call_1 = str_to_int((struct String){.str = "-1", .len = 2});
    milone_assert(((call_1 + 1) == 0), 55, 2);
    return 0;
}

int milone_main() {
    char call_2 = literalTest_(0);
    char call_3 = arithmeticOperatorsTest_(2, 3, 39);
    char call_4 = bitOperatorsTest_(1);
    char call_5 = compareTest_(2, 3);
    char call_6 = toIntTest_(0);
    return 0;
}
