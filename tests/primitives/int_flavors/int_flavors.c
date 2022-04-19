#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

void int_flavors_int_flavors_signedCases(void);

void int_flavors_int_flavors_unsignedCases(void);

void int_flavors_int_flavors_suffix(void);

int main(int argc, char** argv);

void int_flavors_int_flavors_signedCases(void) {
    struct String call_;
    struct String call_1;
    int64_t call_2;
    milone_assert((1 == 1), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 9, 2);
    milone_assert((((int8_t)1) == ((int8_t)1)), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 12, 2);
    milone_assert((((int8_t)2 + (int8_t)3) == (int8_t)5), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 18, 2);
    milone_assert((((int16_t)7 - (int16_t)11) == (int16_t)-4), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 19, 2);
    milone_assert((((int32_t)(int16_t)-4) == -4), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 20, 2);
    milone_assert((((((int8_t)1 + (int8_t)2) + (int8_t)4) & (((int8_t)2 + (int8_t)4) + (int8_t)8)) == ((int8_t)2 + (int8_t)4)), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 23, 2);
    milone_assert((((((int16_t)1 + (int16_t)2) + (int16_t)4) | (((int16_t)2 + (int16_t)4) + (int16_t)8)) == ((((int16_t)1 + (int16_t)2) + (int16_t)4) + (int16_t)8)), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 25, 2);
    milone_assert(((((1LL + 2LL) + 4LL) ^ ((2LL + 4LL) + 8LL)) == (1LL + 8LL)), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 27, 2);
    milone_assert((((((int8_t)1 + (int8_t)4) + (int8_t)16) << 1) == (((int8_t)2 + (int8_t)8) + (int8_t)32)), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 29, 2);
    milone_assert((((((int16_t)1 + (int16_t)4) + (int16_t)16) >> 1) == (((int16_t)0 + (int16_t)2) + (int16_t)8)), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 30, 2);
    milone_assert((((int8_t)-1 >> 1) == (int8_t)-1), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 32, 2);
    milone_assert((13 == 13), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 35, 2);
    milone_assert((17LL == 17LL), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 36, 2);
    milone_assert((-23LL < 19LL), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 37, 2);
    milone_assert((((int8_t)2 - (int8_t)2) == 0), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 39, 2);
    milone_assert((((int8_t)2 - (int8_t)3) < 0), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 40, 2);
    milone_assert((0 < ((int8_t)2 - (int8_t)-1)), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 41, 2);
    milone_assert((milone_int64_compare((1231231231LL * 2LL), (1231231231LL * 3LL)) < 0), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 43, 2);
    milone_assert((0 < milone_int64_compare((1231231231LL * 3LL), (1231231231LL * 2LL))), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 44, 2);
    call_ = string_of_int64((int8_t)-1);
    milone_assert((string_compare(call_, (struct String){.ptr = "-1", .len = 2}) == 0), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 47, 2);
    call_1 = string_of_int64((1231231231LL * 3LL));
    milone_assert((string_compare(call_1, (struct String){.ptr = "3693693693", .len = 10}) == 0), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 48, 2);
    call_2 = string_to_int64((struct String){.ptr = "-3693693693", .len = 11});
    milone_assert((((int32_t)(call_2 / 3LL)) == -1231231231), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 51, 2);
    return;
}

void int_flavors_int_flavors_unsignedCases(void) {
    struct String call_3;
    struct String call_4;
    uint8_t call_5;
    uint64_t call_6;
    milone_assert((((uint8_t)1) == ((uint8_t)1)), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 55, 2);
    milone_assert((((uint32_t)1) == ((uint32_t)1)), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 58, 2);
    milone_assert((((uint8_t)2U + (uint8_t)3U) == (uint8_t)5U), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 61, 2);
    milone_assert((((uint16_t)11U - (uint16_t)7U) == (uint16_t)4U), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 62, 2);
    milone_assert((((((uint8_t)1U + (uint8_t)2U) + (uint8_t)4U) & (((uint8_t)2U + (uint8_t)4U) + (uint8_t)8U)) == ((uint8_t)2U + (uint8_t)4U)), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 65, 2);
    milone_assert((((((uint16_t)1U + (uint16_t)2U) + (uint16_t)4U) | (((uint16_t)2U + (uint16_t)4U) + (uint16_t)8U)) == ((((uint16_t)1U + (uint16_t)2U) + (uint16_t)4U) + (uint16_t)8U)), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 67, 2);
    milone_assert(((((1ULL + 2ULL) + 4ULL) ^ ((2ULL + 4ULL) + 8ULL)) == (1ULL + 8ULL)), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 69, 2);
    milone_assert((((((uint8_t)1U + (uint8_t)4U) + (uint8_t)16U) << 1) == (((uint8_t)2U + (uint8_t)8U) + (uint8_t)32U)), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 71, 2);
    milone_assert((((((uint16_t)1U + (uint16_t)4U) + (uint16_t)16U) >> 1) == (((uint16_t)0U + (uint16_t)2U) + (uint16_t)8U)), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 72, 2);
    milone_assert((((uint32_t)13) == (uint32_t)13U), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 75, 2);
    milone_assert((17ULL == 17ULL), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 76, 2);
    milone_assert(((size_t)19ULL < (size_t)23ULL), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 77, 2);
    milone_assert((milone_uint64_compare(2ULL, 2ULL) == 0), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 79, 2);
    milone_assert((milone_uint64_compare((1231231231ULL * 2ULL), (1231231231ULL * 3ULL)) < 0), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 80, 2);
    milone_assert((0 < milone_uint64_compare((1231231231ULL * 3ULL), (1231231231ULL * 2ULL))), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 81, 2);
    call_3 = string_of_uint64((uint8_t)0U);
    milone_assert((string_compare(call_3, (struct String){.ptr = "0", .len = 1}) == 0), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 84, 2);
    call_4 = string_of_uint64((1231231231ULL * 3ULL));
    milone_assert((string_compare(call_4, (struct String){.ptr = "3693693693", .len = 10}) == 0), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 85, 2);
    call_5 = string_to_uint8((struct String){.ptr = "255", .len = 3});
    milone_assert((call_5 == (uint8_t)255U), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 88, 2);
    call_6 = string_to_uint64((struct String){.ptr = "3693693693", .len = 10});
    milone_assert((((int32_t)(call_6 / 3ULL)) == 1231231231), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 89, 2);
    return;
}

void int_flavors_int_flavors_suffix(void) {
    struct String call_7;
    milone_assert((64LL == ((int64_t)64)), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 92, 2);
    milone_assert((0x7fLL == ((int64_t)127)), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 93, 2);
    milone_assert(((uint8_t)8U == ((uint8_t)8)), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 95, 2);
    milone_assert(((uint16_t)16U == ((uint16_t)16)), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 96, 2);
    milone_assert(((uint32_t)32U == ((uint32_t)32)), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 97, 2);
    milone_assert(((uint32_t)32U == ((uint32_t)32)), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 98, 2);
    milone_assert((64ULL == ((uint64_t)64)), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 99, 2);
    milone_assert(((size_t)99ULL == ((uintptr_t)99)), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 100, 2);
    call_7 = string_of_int64(180150120900600300LL);
    milone_assert((string_compare(call_7, (struct String){.ptr = "180150120900600300", .len = 18}) == 0), (struct String){.ptr = "int_flavors/int_flavors.milone", .len = 30}, 102, 2);
    return;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    int_flavors_int_flavors_signedCases();
    int_flavors_int_flavors_unsignedCases();
    int_flavors_int_flavors_suffix();
    return 0;
}
