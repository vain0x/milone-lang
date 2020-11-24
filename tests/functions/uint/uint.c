#include "milone.h"

int main();

int main() {
    milone_assert((((int)((uint32_t)42)) == 42), 6, 2);
    int call_ = 0;
    milone_assert((((int)((uint32_t)'A')) == ((int)'A')), 7, 2);
    int call_1 = 0;
    uint32_t call_2 = str_to_uint((struct String){.str = "42", .len = 2});
    milone_assert((((int)call_2) == 42), 10, 2);
    int call_3 = 0;
    struct String call_4 = str_of_uint(((uint32_t)42));
    milone_assert((str_cmp(call_4, (struct String){.str = "42", .len = 2}) == 0), 11, 2);
    int call_5 = 0;
    milone_assert((((int)(((uint32_t)40) + ((uint32_t)2))) == 42), 14, 2);
    int call_6 = 0;
    milone_assert((((int)(((uint32_t)49) - ((uint32_t)7))) == 42), 15, 2);
    int call_7 = 0;
    milone_assert((((int)(((uint32_t)6) * ((uint32_t)7))) == 42), 16, 2);
    int call_8 = 0;
    milone_assert((((int)(((uint32_t)294) / ((uint32_t)7))) == 42), 17, 2);
    int call_9 = 0;
    milone_assert((((int)(((uint32_t)2063) % ((uint32_t)43))) == 42), 18, 2);
    int call_10 = 0;
    milone_assert((((int)((((uint32_t)(0 - 1)) - ((uint32_t)1)) / ((uint32_t)2))) == 2147483647), 21, 2);
    int call_11 = 0;
    milone_assert((((uint32_t)2) < ((uint32_t)3)), 24, 2);
    int call_12 = 0;
    milone_assert((((uint32_t)3) >= ((uint32_t)2)), 25, 2);
    int call_13 = 0;
    milone_assert((((uint32_t)3) >= ((uint32_t)2)), 26, 2);
    int call_14 = 0;
    milone_assert((((uint32_t)2) == ((uint32_t)2)), 27, 2);
    int call_15 = 0;
    milone_assert((((uint32_t)2) != ((uint32_t)3)), 28, 2);
    int call_16 = 0;
    return 0;
}
