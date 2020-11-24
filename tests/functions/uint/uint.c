#include "milone.h"

int main();

int main() {
    milone_assert((((int)((uint32_t)42)) == 42), 6, 2);
    milone_assert((((int)((uint32_t)'A')) == ((int)'A')), 7, 2);
    uint32_t call_ = str_to_uint((struct String){.str = "42", .len = 2});
    milone_assert((((int)call_) == 42), 10, 2);
    struct String call_1 = str_of_uint(((uint32_t)42));
    milone_assert((str_cmp(call_1, (struct String){.str = "42", .len = 2}) == 0), 11, 2);
    milone_assert((((int)(((uint32_t)40) + ((uint32_t)2))) == 42), 14, 2);
    milone_assert((((int)(((uint32_t)49) - ((uint32_t)7))) == 42), 15, 2);
    milone_assert((((int)(((uint32_t)6) * ((uint32_t)7))) == 42), 16, 2);
    milone_assert((((int)(((uint32_t)294) / ((uint32_t)7))) == 42), 17, 2);
    milone_assert((((int)(((uint32_t)2063) % ((uint32_t)43))) == 42), 18, 2);
    milone_assert((((int)((((uint32_t)(0 - 1)) - ((uint32_t)1)) / ((uint32_t)2))) == 2147483647), 21, 2);
    milone_assert((((uint32_t)2) < ((uint32_t)3)), 24, 2);
    milone_assert((((uint32_t)3) >= ((uint32_t)2)), 25, 2);
    milone_assert((((uint32_t)3) >= ((uint32_t)2)), 26, 2);
    milone_assert((((uint32_t)2) == ((uint32_t)2)), 27, 2);
    milone_assert((((uint32_t)2) != ((uint32_t)3)), 28, 2);
    return 0;
}
