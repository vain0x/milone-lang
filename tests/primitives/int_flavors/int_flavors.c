#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

void int_flavors_int_flavors_signedCases(void);

void int_flavors_int_flavors_unsignedCases(void);

void int_flavors_int_flavors_suffix(void);

void int_flavors_int_flavors_charConversion(void);

int main(int argc, char **argv);

void int_flavors_int_flavors_signedCases(void) {
    struct String call_;
    struct String call_1;
    int64_t call_2;
    if ((1 != 1)) milone_assert_error("int_flavors/int_flavors.milone", 9, 2);
    if ((((int8_t)1) != ((int8_t)1))) milone_assert_error("int_flavors/int_flavors.milone", 12, 2);
    if ((((int8_t)2 + (int8_t)3) != (int8_t)5)) milone_assert_error("int_flavors/int_flavors.milone", 18, 2);
    if ((((int16_t)7 - (int16_t)11) != (int16_t)-4)) milone_assert_error("int_flavors/int_flavors.milone", 19, 2);
    if ((((int32_t)(int16_t)-4) != -4)) milone_assert_error("int_flavors/int_flavors.milone", 20, 2);
    if ((((((int8_t)1 + (int8_t)2) + (int8_t)4) & (((int8_t)2 + (int8_t)4) + (int8_t)8)) != ((int8_t)2 + (int8_t)4))) milone_assert_error("int_flavors/int_flavors.milone", 23, 2);
    if ((((((int16_t)1 + (int16_t)2) + (int16_t)4) | (((int16_t)2 + (int16_t)4) + (int16_t)8)) != ((((int16_t)1 + (int16_t)2) + (int16_t)4) + (int16_t)8))) milone_assert_error("int_flavors/int_flavors.milone", 25, 2);
    if (((((1LL + 2LL) + 4LL) ^ ((2LL + 4LL) + 8LL)) != (1LL + 8LL))) milone_assert_error("int_flavors/int_flavors.milone", 27, 2);
    if ((((((int8_t)1 + (int8_t)4) + (int8_t)16) << 1) != (((int8_t)2 + (int8_t)8) + (int8_t)32))) milone_assert_error("int_flavors/int_flavors.milone", 29, 2);
    if ((((((int16_t)1 + (int16_t)4) + (int16_t)16) >> 1) != (((int16_t)0 + (int16_t)2) + (int16_t)8))) milone_assert_error("int_flavors/int_flavors.milone", 30, 2);
    if ((((int8_t)-1 >> 1) != (int8_t)-1)) milone_assert_error("int_flavors/int_flavors.milone", 32, 2);
    if ((((int8_t)(~((int8_t)60))) != (int8_t)-61)) milone_assert_error("int_flavors/int_flavors.milone", 34, 2);
    if ((13 != 13)) milone_assert_error("int_flavors/int_flavors.milone", 37, 2);
    if ((17LL != 17LL)) milone_assert_error("int_flavors/int_flavors.milone", 38, 2);
    if ((-23LL >= 19LL)) milone_assert_error("int_flavors/int_flavors.milone", 39, 2);
    if ((((int8_t)2 - (int8_t)2) != 0)) milone_assert_error("int_flavors/int_flavors.milone", 41, 2);
    if ((((int8_t)2 - (int8_t)3) >= 0)) milone_assert_error("int_flavors/int_flavors.milone", 42, 2);
    if ((0 >= ((int8_t)2 - (int8_t)-1))) milone_assert_error("int_flavors/int_flavors.milone", 43, 2);
    if ((milone_int64_compare((1231231231LL * 2LL), (1231231231LL * 3LL)) >= 0)) milone_assert_error("int_flavors/int_flavors.milone", 45, 2);
    if ((0 >= milone_int64_compare((1231231231LL * 3LL), (1231231231LL * 2LL)))) milone_assert_error("int_flavors/int_flavors.milone", 46, 2);
    call_ = string_of_int64((int8_t)-1);
    if ((string_compare(call_, (struct String){.ptr = "-1", .len = 2}) != 0)) milone_assert_error("int_flavors/int_flavors.milone", 49, 2);
    call_1 = string_of_int64((1231231231LL * 3LL));
    if ((string_compare(call_1, (struct String){.ptr = "3693693693", .len = 10}) != 0)) milone_assert_error("int_flavors/int_flavors.milone", 50, 2);
    call_2 = string_to_int64((struct String){.ptr = "-3693693693", .len = 11});
    if ((((int32_t)(call_2 / 3LL)) != -1231231231)) milone_assert_error("int_flavors/int_flavors.milone", 53, 2);
    return;
}

void int_flavors_int_flavors_unsignedCases(void) {
    struct String call_3;
    struct String call_4;
    uint8_t call_5;
    uint64_t call_6;
    if ((((uint8_t)1) != ((uint8_t)1))) milone_assert_error("int_flavors/int_flavors.milone", 57, 2);
    if ((((uint32_t)1) != ((uint32_t)1))) milone_assert_error("int_flavors/int_flavors.milone", 60, 2);
    if ((((uint8_t)2U + (uint8_t)3U) != (uint8_t)5U)) milone_assert_error("int_flavors/int_flavors.milone", 63, 2);
    if ((((uint16_t)11U - (uint16_t)7U) != (uint16_t)4U)) milone_assert_error("int_flavors/int_flavors.milone", 64, 2);
    if ((((((uint8_t)1U + (uint8_t)2U) + (uint8_t)4U) & (((uint8_t)2U + (uint8_t)4U) + (uint8_t)8U)) != ((uint8_t)2U + (uint8_t)4U))) milone_assert_error("int_flavors/int_flavors.milone", 67, 2);
    if ((((((uint16_t)1U + (uint16_t)2U) + (uint16_t)4U) | (((uint16_t)2U + (uint16_t)4U) + (uint16_t)8U)) != ((((uint16_t)1U + (uint16_t)2U) + (uint16_t)4U) + (uint16_t)8U))) milone_assert_error("int_flavors/int_flavors.milone", 69, 2);
    if (((((1ULL + 2ULL) + 4ULL) ^ ((2ULL + 4ULL) + 8ULL)) != (1ULL + 8ULL))) milone_assert_error("int_flavors/int_flavors.milone", 71, 2);
    if ((((((uint8_t)1U + (uint8_t)4U) + (uint8_t)16U) << 1) != (((uint8_t)2U + (uint8_t)8U) + (uint8_t)32U))) milone_assert_error("int_flavors/int_flavors.milone", 73, 2);
    if ((((((uint16_t)1U + (uint16_t)4U) + (uint16_t)16U) >> 1) != (((uint16_t)0U + (uint16_t)2U) + (uint16_t)8U))) milone_assert_error("int_flavors/int_flavors.milone", 74, 2);
    if ((((uint8_t)(~((uint8_t)60U))) != (uint8_t)195U)) milone_assert_error("int_flavors/int_flavors.milone", 76, 2);
    if ((((uint32_t)13) != (uint32_t)13U)) milone_assert_error("int_flavors/int_flavors.milone", 79, 2);
    if ((17ULL != 17ULL)) milone_assert_error("int_flavors/int_flavors.milone", 80, 2);
    if (((size_t)19ULL >= (size_t)23ULL)) milone_assert_error("int_flavors/int_flavors.milone", 81, 2);
    if ((milone_uint64_compare(2ULL, 2ULL) != 0)) milone_assert_error("int_flavors/int_flavors.milone", 83, 2);
    if ((milone_uint64_compare((1231231231ULL * 2ULL), (1231231231ULL * 3ULL)) >= 0)) milone_assert_error("int_flavors/int_flavors.milone", 84, 2);
    if ((0 >= milone_uint64_compare((1231231231ULL * 3ULL), (1231231231ULL * 2ULL)))) milone_assert_error("int_flavors/int_flavors.milone", 85, 2);
    call_3 = string_of_uint64((uint8_t)0U);
    if ((string_compare(call_3, (struct String){.ptr = "0", .len = 1}) != 0)) milone_assert_error("int_flavors/int_flavors.milone", 88, 2);
    call_4 = string_of_uint64((1231231231ULL * 3ULL));
    if ((string_compare(call_4, (struct String){.ptr = "3693693693", .len = 10}) != 0)) milone_assert_error("int_flavors/int_flavors.milone", 89, 2);
    call_5 = string_to_uint8((struct String){.ptr = "255", .len = 3});
    if ((call_5 != (uint8_t)255U)) milone_assert_error("int_flavors/int_flavors.milone", 92, 2);
    call_6 = string_to_uint64((struct String){.ptr = "3693693693", .len = 10});
    if ((((int32_t)(call_6 / 3ULL)) != 1231231231)) milone_assert_error("int_flavors/int_flavors.milone", 93, 2);
    return;
}

void int_flavors_int_flavors_suffix(void) {
    struct String call_7;
    if ((64LL != ((int64_t)64))) milone_assert_error("int_flavors/int_flavors.milone", 96, 2);
    if ((0x7fLL != ((int64_t)127))) milone_assert_error("int_flavors/int_flavors.milone", 97, 2);
    if (((uint8_t)8U != ((uint8_t)8))) milone_assert_error("int_flavors/int_flavors.milone", 99, 2);
    if (((uint16_t)16U != ((uint16_t)16))) milone_assert_error("int_flavors/int_flavors.milone", 100, 2);
    if (((uint32_t)32U != ((uint32_t)32))) milone_assert_error("int_flavors/int_flavors.milone", 101, 2);
    if (((uint32_t)32U != ((uint32_t)32))) milone_assert_error("int_flavors/int_flavors.milone", 102, 2);
    if ((64ULL != ((uint64_t)64))) milone_assert_error("int_flavors/int_flavors.milone", 103, 2);
    if (((size_t)99ULL != ((uintptr_t)99))) milone_assert_error("int_flavors/int_flavors.milone", 104, 2);
    call_7 = string_of_int64(180150120900600300LL);
    if ((string_compare(call_7, (struct String){.ptr = "180150120900600300", .len = 18}) != 0)) milone_assert_error("int_flavors/int_flavors.milone", 106, 2);
    return;
}

void int_flavors_int_flavors_charConversion(void) {
    if ((((char)(int8_t)65) != 'A')) milone_assert_error("int_flavors/int_flavors.milone", 110, 2);
    if ((((int8_t)'A') != (int8_t)65)) milone_assert_error("int_flavors/int_flavors.milone", 111, 2);
    if ((((char)(uint8_t)65U) != 'A')) milone_assert_error("int_flavors/int_flavors.milone", 112, 2);
    if ((((uint8_t)'A') != (uint8_t)65U)) milone_assert_error("int_flavors/int_flavors.milone", 113, 2);
    return;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    int_flavors_int_flavors_signedCases();
    int_flavors_int_flavors_unsignedCases();
    int_flavors_int_flavors_suffix();
    int_flavors_int_flavors_charConversion();
    return 0;
}
