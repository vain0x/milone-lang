#include "milone.h"

int main();

int main() {
    milone_assert(((((1 + 2) + 4) & ((2 + 4) + 8)) == (2 + 4)), 5, 2);
    milone_assert(((((1 + 2) + 4) | ((2 + 4) + 8)) == (((1 + 2) + 4) + 8)), 6, 2);
    milone_assert(((((1 + 2) + 4) ^ ((2 + 4) + 8)) == (1 + 8)), 7, 2);
    milone_assert(((1 << 0) == 1), 9, 2);
    milone_assert(((1 << 1) == 2), 10, 2);
    milone_assert(((((1 + 2) + 8) << 1) == ((2 + 4) + 16)), 11, 2);
    milone_assert(((4 >> 0) == 4), 13, 2);
    milone_assert(((4 >> 1) == 2), 14, 2);
    milone_assert(((4 >> 2) == 1), 15, 2);
    milone_assert(((4 >> 3) == 0), 16, 2);
    milone_assert(((((1 + 2) + 8) >> 1) == ((0 + 1) + 4)), 17, 2);
    return 0;
}
