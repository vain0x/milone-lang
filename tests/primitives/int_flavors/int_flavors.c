#include "milone.h"

void int_flavors_Program_signedCases(void);

void int_flavors_Program_unsignedCases(void);

void int_flavors_int_flavors_suffix(void);

int milone_main(void);

void int_flavors_Program_signedCases(void) {
    milone_assert((1 == 1), 9, 2);
    milone_assert((((int8_t)1) == ((int8_t)1)), 12, 2);
    milone_assert((((int8_t)2 + (int8_t)3) == (int8_t)5), 18, 2);
    milone_assert((((int16_t)7 - (int16_t)11) == (int16_t)-4), 19, 2);
    milone_assert((((int)(int16_t)-4) == -4), 20, 2);
    milone_assert((((((int8_t)1 + (int8_t)2) + (int8_t)4) & (((int8_t)2 + (int8_t)4) + (int8_t)8)) == ((int8_t)2 + (int8_t)4)), 23, 2);
    milone_assert((((((int16_t)1 + (int16_t)2) + (int16_t)4) | (((int16_t)2 + (int16_t)4) + (int16_t)8)) == ((((int16_t)1 + (int16_t)2) + (int16_t)4) + (int16_t)8)), 25, 2);
    milone_assert(((((1LL + 2LL) + 4LL) ^ ((2LL + 4LL) + 8LL)) == (1LL + 8LL)), 27, 2);
    milone_assert((((((int8_t)1 + (int8_t)4) + (int8_t)16) << 1) == (((int8_t)2 + (int8_t)8) + (int8_t)32)), 29, 2);
    milone_assert((((((int16_t)1 + (int16_t)4) + (int16_t)16) >> 1) == (((int16_t)0 + (int16_t)2) + (int16_t)8)), 30, 2);
    milone_assert((((int8_t)-1 >> 1) == (int8_t)-1), 32, 2);
    milone_assert((13 == 13), 35, 2);
    milone_assert((17LL == 17LL), 36, 2);
    milone_assert((-23LL < 19LL), 37, 2);
    milone_assert((((int8_t)2 - (int8_t)2) == 0), 39, 2);
    milone_assert((((int8_t)2 - (int8_t)3) < 0), 40, 2);
    milone_assert((0 < ((int8_t)2 - (int8_t)-1)), 41, 2);
    milone_assert((int64_compare((1231231231LL * 2LL), (1231231231LL * 3LL)) < 0), 43, 2);
    milone_assert((0 < int64_compare((1231231231LL * 3LL), (1231231231LL * 2LL))), 44, 2);
    struct String call_ = str_of_int64((int8_t)-1);
    milone_assert((str_compare(call_, (struct String){.str = "-1", .len = 2}) == 0), 47, 2);
    struct String call_1 = str_of_int64((1231231231LL * 3LL));
    milone_assert((str_compare(call_1, (struct String){.str = "3693693693", .len = 10}) == 0), 48, 2);
    int64_t call_2 = str_to_int64((struct String){.str = "-3693693693", .len = 11});
    milone_assert((((int)(call_2 / 3LL)) == -1231231231), 51, 2);
    return;
}

void int_flavors_Program_unsignedCases(void) {
    milone_assert((((uint8_t)1) == ((uint8_t)1)), 55, 2);
    milone_assert((((uint32_t)1) == ((uint32_t)1)), 58, 2);
    milone_assert((((uint8_t)2U + (uint8_t)3U) == (uint8_t)5U), 61, 2);
    milone_assert((((uint16_t)11U - (uint16_t)7U) == (uint16_t)4U), 62, 2);
    milone_assert((((((uint8_t)1U + (uint8_t)2U) + (uint8_t)4U) & (((uint8_t)2U + (uint8_t)4U) + (uint8_t)8U)) == ((uint8_t)2U + (uint8_t)4U)), 65, 2);
    milone_assert((((((uint16_t)1U + (uint16_t)2U) + (uint16_t)4U) | (((uint16_t)2U + (uint16_t)4U) + (uint16_t)8U)) == ((((uint16_t)1U + (uint16_t)2U) + (uint16_t)4U) + (uint16_t)8U)), 67, 2);
    milone_assert(((((1ULL + 2ULL) + 4ULL) ^ ((2ULL + 4ULL) + 8ULL)) == (1ULL + 8ULL)), 69, 2);
    milone_assert((((((uint8_t)1U + (uint8_t)4U) + (uint8_t)16U) << 1) == (((uint8_t)2U + (uint8_t)8U) + (uint8_t)32U)), 71, 2);
    milone_assert((((((uint16_t)1U + (uint16_t)4U) + (uint16_t)16U) >> 1) == (((uint16_t)0U + (uint16_t)2U) + (uint16_t)8U)), 72, 2);
    milone_assert((((uint32_t)13) == (uint32_t)13U), 75, 2);
    milone_assert((17ULL == 17ULL), 76, 2);
    milone_assert(((size_t)19ULL < (size_t)23ULL), 77, 2);
    milone_assert((uint64_compare(2ULL, 2ULL) == 0), 79, 2);
    milone_assert((uint64_compare((1231231231ULL * 2ULL), (1231231231ULL * 3ULL)) < 0), 80, 2);
    milone_assert((0 < uint64_compare((1231231231ULL * 3ULL), (1231231231ULL * 2ULL))), 81, 2);
    struct String call_3 = str_of_uint64((uint8_t)0U);
    milone_assert((str_compare(call_3, (struct String){.str = "0", .len = 1}) == 0), 84, 2);
    struct String call_4 = str_of_uint64((1231231231ULL * 3ULL));
    milone_assert((str_compare(call_4, (struct String){.str = "3693693693", .len = 10}) == 0), 85, 2);
    uint8_t call_5 = str_to_uint8((struct String){.str = "255", .len = 3});
    milone_assert((call_5 == (uint8_t)255U), 88, 2);
    uint64_t call_6 = str_to_uint64((struct String){.str = "3693693693", .len = 10});
    milone_assert((((int)(call_6 / 3ULL)) == 1231231231), 89, 2);
    return;
}

void int_flavors_int_flavors_suffix(void) {
    milone_assert((64LL == ((int64_t)64)), 92, 2);
    milone_assert((0x7fLL == ((int64_t)127)), 93, 2);
    milone_assert(((uint8_t)8U == ((uint8_t)8)), 95, 2);
    milone_assert(((uint16_t)16U == ((uint16_t)16)), 96, 2);
    milone_assert(((uint32_t)32U == ((uint32_t)32)), 97, 2);
    milone_assert(((uint32_t)32U == ((uint32_t)32)), 98, 2);
    milone_assert((64ULL == ((uint64_t)64)), 99, 2);
    milone_assert(((size_t)99ULL == ((uintptr_t)99)), 100, 2);
    struct String call_7 = str_of_int64(180150120900600300LL);
    milone_assert((str_compare(call_7, (struct String){.str = "180150120900600300", .len = 18}) == 0), 102, 2);
    return;
}

int milone_main(void) {
    int_flavors_Program_signedCases();
    int_flavors_Program_unsignedCases();
    int_flavors_int_flavors_suffix();
    return 0;
}
