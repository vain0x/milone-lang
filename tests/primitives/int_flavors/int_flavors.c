#include "milone.h"

void int_flavors_Program_signedCases(void);

void int_flavors_Program_unsignedCases(void);

int milone_main(void);

void int_flavors_Program_signedCases(void) {
    milone_assert((1 == 1), 10, 2);
    milone_assert((((int8_t)1) == ((int8_t)1)), 13, 2);
    milone_assert(((((int8_t)2) + ((int8_t)3)) == ((int8_t)5)), 19, 2);
    milone_assert(((((int16_t)7) - ((int16_t)11)) == ((int16_t)-4)), 20, 2);
    milone_assert((((int)((int16_t)-4)) == -4), 21, 2);
    milone_assert(((((int8_t)((1 + 2) + 4)) & ((int8_t)((2 + 4) + 8))) == ((int8_t)(2 + 4))), 24, 2);
    milone_assert(((((int16_t)((1 + 2) + 4)) | ((int16_t)((2 + 4) + 8))) == ((int16_t)(((1 + 2) + 4) + 8))), 26, 2);
    milone_assert(((((int64_t)((1 + 2) + 4)) ^ ((int64_t)((2 + 4) + 8))) == ((int64_t)(1 + 8))), 28, 2);
    milone_assert(((((int8_t)((1 + 4) + 16)) << 1) == ((int8_t)((2 + 8) + 32))), 30, 2);
    milone_assert(((((int16_t)((1 + 4) + 16)) >> 1) == ((int16_t)((0 + 2) + 8))), 31, 2);
    milone_assert(((((int8_t)-1) >> 1) == ((int8_t)-1)), 33, 2);
    milone_assert((13 == 13), 36, 2);
    milone_assert((((int64_t)17) == ((int64_t)17)), 37, 2);
    milone_assert((((intptr_t)-23) < ((intptr_t)19)), 38, 2);
    milone_assert(((((int8_t)2) - ((int8_t)2)) == 0), 40, 2);
    milone_assert(((((int8_t)2) - ((int8_t)3)) < 0), 41, 2);
    milone_assert((0 < (((int8_t)2) - ((int8_t)-1))), 42, 2);
    milone_assert((int64_compare((((int64_t)1231231231) * ((int64_t)2)), (((int64_t)1231231231) * ((int64_t)3))) < 0), 44, 2);
    milone_assert((0 < int64_compare((((int64_t)1231231231) * ((int64_t)3)), (((int64_t)1231231231) * ((int64_t)2)))), 45, 2);
    struct String call_ = str_of_int64(((int8_t)-1));
    milone_assert((str_compare(call_, (struct String){.str = "-1", .len = 2}) == 0), 48, 2);
    struct String call_1 = str_of_int64((((int64_t)1231231231) * ((int64_t)3)));
    milone_assert((str_compare(call_1, (struct String){.str = "3693693693", .len = 10}) == 0), 49, 2);
    int64_t call_2 = str_to_int64((struct String){.str = "-3693693693", .len = 11});
    milone_assert((((int)(call_2 / ((int64_t)3))) == -1231231231), 52, 2);
    return;
}

void int_flavors_Program_unsignedCases(void) {
    milone_assert((((uint8_t)1) == ((uint8_t)1)), 56, 2);
    milone_assert((((uint32_t)1) == ((uint32_t)1)), 59, 2);
    milone_assert(((((uint8_t)2) + ((uint8_t)3)) == ((uint8_t)5)), 62, 2);
    milone_assert(((((uint16_t)11) - ((uint16_t)7)) == ((uint16_t)4)), 63, 2);
    milone_assert(((((uint8_t)((1 + 2) + 4)) & ((uint8_t)((2 + 4) + 8))) == ((uint8_t)(2 + 4))), 66, 2);
    milone_assert(((((uint16_t)((1 + 2) + 4)) | ((uint16_t)((2 + 4) + 8))) == ((uint16_t)(((1 + 2) + 4) + 8))), 68, 2);
    milone_assert(((((uint64_t)((1 + 2) + 4)) ^ ((uint64_t)((2 + 4) + 8))) == ((uint64_t)(1 + 8))), 70, 2);
    milone_assert(((((uint8_t)((1 + 4) + 16)) << 1) == ((uint8_t)((2 + 8) + 32))), 72, 2);
    milone_assert(((((uint16_t)((1 + 4) + 16)) >> 1) == ((uint16_t)((0 + 2) + 8))), 73, 2);
    milone_assert((((uint32_t)13) == ((uint32_t)13)), 76, 2);
    milone_assert((((uint64_t)17) == ((uint64_t)17)), 77, 2);
    milone_assert((((uintptr_t)19) < ((uintptr_t)23)), 78, 2);
    milone_assert((uint64_compare(((uint64_t)2), ((uint64_t)2)) == 0), 80, 2);
    milone_assert((uint64_compare((((uint64_t)1231231231) * ((uint64_t)2)), (((uint64_t)1231231231) * ((uint64_t)3))) < 0), 81, 2);
    milone_assert((0 < uint64_compare((((uint64_t)1231231231) * ((uint64_t)3)), (((uint64_t)1231231231) * ((uint64_t)2)))), 82, 2);
    struct String call_3 = str_of_uint64(((uint8_t)0));
    milone_assert((str_compare(call_3, (struct String){.str = "0", .len = 1}) == 0), 85, 2);
    struct String call_4 = str_of_uint64((((uint64_t)1231231231) * ((uint64_t)3)));
    milone_assert((str_compare(call_4, (struct String){.str = "3693693693", .len = 10}) == 0), 86, 2);
    uint8_t call_5 = str_to_uint8((struct String){.str = "255", .len = 3});
    milone_assert((call_5 == ((uint8_t)255)), 89, 2);
    uint64_t call_6 = str_to_uint64((struct String){.str = "3693693693", .len = 10});
    milone_assert((((int)(call_6 / ((uint64_t)3))) == 1231231231), 90, 2);
    return;
}

int milone_main(void) {
    int_flavors_Program_signedCases();
    int_flavors_Program_unsignedCases();
    return 0;
}
