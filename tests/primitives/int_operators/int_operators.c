#include "milone.h"

int arithmeticOperatorsTest_(int two_, int three_, int thirtyNine_);

int bitOperatorsTest_(int n1_);

int compareTest_(int n2_1, int n3_);

int toIntTest_(int arg_);

int main();

int arithmeticOperatorsTest_(int two_, int three_, int thirtyNine_) {
    milone_assert(((two_ + three_) == 5), 3, 2);
    milone_assert(((three_ - two_) == 1), 4, 2);
    milone_assert(((two_ * three_) == 6), 5, 2);
    milone_assert(((thirtyNine_ / two_) == 19), 6, 2);
    milone_assert(((thirtyNine_ / three_) == 13), 7, 2);
    milone_assert(((thirtyNine_ % two_) == 1), 8, 2);
    milone_assert(((thirtyNine_ % three_) == 0), 9, 2);
    milone_assert(((-(two_)) == -2), 11, 2);
    return 0;
}

int bitOperatorsTest_(int n1_) {
    int n2_ = (n1_ * 2);
    int n4_ = (n2_ * 2);
    int n8_ = (n4_ * 2);
    int n16_ = (n8_ * 2);
    milone_assert(((((n1_ + n2_) + n4_) & ((n2_ + n4_) + n8_)) == (n2_ + n4_)), 19, 2);
    milone_assert(((((n1_ + n2_) + n4_) | ((n2_ + n4_) + n8_)) == (((n1_ + n2_) + n4_) + n8_)), 20, 2);
    milone_assert(((((n1_ + n2_) + n4_) ^ ((n2_ + n4_) + n8_)) == (n1_ + n8_)), 22, 2);
    milone_assert(((n1_ << 0) == n1_), 24, 2);
    milone_assert(((n1_ << 1) == n2_), 25, 2);
    milone_assert(((((n1_ + n2_) + n8_) << 1) == ((n2_ + n4_) + n16_)), 26, 2);
    milone_assert(((n4_ >> 0) == n4_), 28, 2);
    milone_assert(((n4_ >> 1) == n2_), 29, 2);
    milone_assert(((n4_ >> 2) == n1_), 30, 2);
    milone_assert(((n4_ >> 3) == 0), 31, 2);
    milone_assert(((((n1_ + n2_) + n8_) >> 1) == ((0 + n1_) + n4_)), 32, 2);
    return 0;
}

int compareTest_(int n2_1, int n3_) {
    milone_assert((n2_1 == 2), 35, 2);
    milone_assert((n3_ != 2), 36, 2);
    milone_assert((2 >= n2_1), 38, 2);
    milone_assert((n3_ >= n2_1), 39, 2);
    milone_assert((n2_1 < n3_), 40, 2);
    milone_assert((n2_1 < n3_), 42, 2);
    milone_assert((int_compare(n2_1, 3) < 0), 44, 2);
    milone_assert((int_compare(n2_1, 2) == 0), 45, 2);
    milone_assert((0 < int_compare(n3_, 2)), 46, 2);
    return 0;
}

int toIntTest_(int arg_) {
    milone_assert((0 == 0), 49, 2);
    milone_assert((((int)'a') == 97), 50, 2);
    int call_ = str_to_int((struct String){.str = "42", .len = 2});
    milone_assert((call_ == 42), 51, 2);
    int call_1 = str_to_int((struct String){.str = "-1", .len = 2});
    milone_assert(((call_1 + 1) == 0), 52, 2);
    return 0;
}

int main() {
    int call_2 = arithmeticOperatorsTest_(2, 3, 39);
    int call_3 = bitOperatorsTest_(1);
    int call_4 = compareTest_(2, 3);
    int call_5 = toIntTest_(0);
    return 0;
}
