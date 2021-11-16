#include "milone.h"

int milone_main(void);

int milone_main(void) {
    milone_assert((((int)(uint32_t)42U) == 42), 6, 2);
    milone_assert((((uint32_t)42) == (uint32_t)42U), 7, 2);
    milone_assert((((uint32_t)'A') == (uint32_t)65U), 10, 2);
    milone_assert((((char)(uint32_t)65U) == 'A'), 11, 2);
    uint32_t call_ = str_to_uint32((struct String){.str = "42", .len = 2});
    milone_assert((((int)call_) == 42), 14, 2);
    struct String call_1 = str_of_uint64((uint32_t)42U);
    milone_assert((str_compare(call_1, (struct String){.str = "42", .len = 2}) == 0), 15, 2);
    milone_assert((((int)((uint32_t)40U + (uint32_t)2U)) == 42), 18, 2);
    milone_assert((((int)((uint32_t)49U - (uint32_t)7U)) == 42), 19, 2);
    milone_assert((((int)((uint32_t)6U * (uint32_t)7U)) == 42), 20, 2);
    milone_assert((((int)((uint32_t)294U / (uint32_t)7U)) == 42), 21, 2);
    milone_assert((((int)((uint32_t)2063U % (uint32_t)43U)) == 42), 22, 2);
    milone_assert((((int)((((uint32_t)-1) - (uint32_t)1U) / (uint32_t)2U)) == 2147483647), 25, 2);
    milone_assert(((uint32_t)2U < (uint32_t)3U), 28, 2);
    milone_assert(((uint32_t)3U >= (uint32_t)2U), 29, 2);
    milone_assert(((uint32_t)3U >= (uint32_t)2U), 30, 2);
    milone_assert(((uint32_t)2U == (uint32_t)2U), 31, 2);
    milone_assert(((uint32_t)2U != (uint32_t)3U), 32, 2);
    return 0;
}
