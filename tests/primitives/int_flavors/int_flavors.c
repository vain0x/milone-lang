#include "milone.h"

int signedCases_(int arg_);

int unsignedCases_(int arg_1);

int milone_main();

int signedCases_(int arg_) {
    milone_assert((1 == 1), 10, 2);
    milone_assert((((int8_t)1) == ((int8_t)1)), 13, 2);
    milone_assert(((((int8_t)2) + ((int8_t)3)) == ((int8_t)5)), 19, 2);
    milone_assert(((((int16_t)7) - ((int16_t)11)) == ((int16_t)-4)), 20, 2);
    milone_assert((((int)((int16_t)-4)) == -4), 21, 2);
    milone_assert(((((int8_t)((1 + 2) + 4)) & ((int8_t)((2 + 4) + 8))) == ((int8_t)(2 + 4))), 24, 2);
    milone_assert(((((int16_t)((1 + 2) + 4)) | ((int16_t)((2 + 4) + 8))) == ((int16_t)(((1 + 2) + 4) + 8))), 27, 2);
    milone_assert(((((int64_t)((1 + 2) + 4)) ^ ((int64_t)((2 + 4) + 8))) == ((int64_t)(1 + 8))), 30, 2);
    milone_assert(((((int8_t)((1 + 4) + 16)) << 1) == ((int8_t)((2 + 8) + 32))), 33, 2);
    milone_assert(((((int16_t)((1 + 4) + 16)) >> 1) == ((int16_t)((0 + 2) + 8))), 34, 2);
    milone_assert(((((int8_t)-1) >> 1) == ((int8_t)-1)), 36, 2);
    milone_assert((13 == 13), 39, 2);
    milone_assert((((int64_t)17) == ((int64_t)17)), 40, 2);
    milone_assert((((intptr_t)-23) < ((intptr_t)19)), 41, 2);
    milone_assert(((((int8_t)2) - ((int8_t)2)) == 0), 43, 2);
    milone_assert(((((int8_t)2) - ((int8_t)3)) < 0), 44, 2);
    milone_assert((0 < (((int8_t)2) - ((int8_t)-1))), 45, 2);
    milone_assert((int64_compare((((int64_t)1231231231) * ((int64_t)2)), (((int64_t)1231231231) * ((int64_t)3))) < 0), 47, 2);
    milone_assert((0 < int64_compare((((int64_t)1231231231) * ((int64_t)3)), (((int64_t)1231231231) * ((int64_t)2)))), 48, 2);
    struct String call_ = str_of_int64(((int8_t)-1));
    milone_assert((str_compare(call_, (struct String){.str = "-1", .len = 2}) == 0), 51, 2);
    struct String call_1 = str_of_int64((((int64_t)1231231231) * ((int64_t)3)));
    milone_assert((str_compare(call_1, (struct String){.str = "3693693693", .len = 10}) == 0), 52, 2);
    int64_t call_2 = str_to_int64((struct String){.str = "-3693693693", .len = 11});
    milone_assert((((int)(call_2 / ((int64_t)3))) == -1231231231), 55, 2);
    return 0;
}

int unsignedCases_(int arg_1) {
    milone_assert((((uint8_t)1) == ((uint8_t)1)), 59, 2);
    milone_assert((((uint32_t)1) == ((uint32_t)1)), 62, 2);
    milone_assert(((((uint8_t)2) + ((uint8_t)3)) == ((uint8_t)5)), 65, 2);
    milone_assert(((((uint16_t)11) - ((uint16_t)7)) == ((uint16_t)4)), 66, 2);
    milone_assert(((((uint8_t)((1 + 2) + 4)) & ((uint8_t)((2 + 4) + 8))) == ((uint8_t)(2 + 4))), 69, 2);
    milone_assert(((((uint16_t)((1 + 2) + 4)) | ((uint16_t)((2 + 4) + 8))) == ((uint16_t)(((1 + 2) + 4) + 8))), 72, 2);
    milone_assert(((((uint64_t)((1 + 2) + 4)) ^ ((uint64_t)((2 + 4) + 8))) == ((uint64_t)(1 + 8))), 75, 2);
    milone_assert(((((uint8_t)((1 + 4) + 16)) << 1) == ((uint8_t)((2 + 8) + 32))), 78, 2);
    milone_assert(((((uint16_t)((1 + 4) + 16)) >> 1) == ((uint16_t)((0 + 2) + 8))), 79, 2);
    milone_assert((((uint32_t)13) == ((uint32_t)13)), 82, 2);
    milone_assert((((uint64_t)17) == ((uint64_t)17)), 83, 2);
    milone_assert((((uintptr_t)19) < ((uintptr_t)23)), 84, 2);
    milone_assert((uint64_compare(((uint64_t)2), ((uint64_t)2)) == 0), 86, 2);
    milone_assert((uint64_compare((((uint64_t)1231231231) * ((uint64_t)2)), (((uint64_t)1231231231) * ((uint64_t)3))) < 0), 87, 2);
    milone_assert((0 < uint64_compare((((uint64_t)1231231231) * ((uint64_t)3)), (((uint64_t)1231231231) * ((uint64_t)2)))), 88, 2);
    struct String call_3 = str_of_uint64(((uint8_t)0));
    milone_assert((str_compare(call_3, (struct String){.str = "0", .len = 1}) == 0), 91, 2);
    struct String call_4 = str_of_uint64((((uint64_t)1231231231) * ((uint64_t)3)));
    milone_assert((str_compare(call_4, (struct String){.str = "3693693693", .len = 10}) == 0), 92, 2);
    uint8_t call_5 = str_to_uint8((struct String){.str = "255", .len = 3});
    milone_assert((call_5 == ((uint8_t)255)), 95, 2);
    uint64_t call_6 = str_to_uint64((struct String){.str = "3693693693", .len = 10});
    milone_assert((((int)(call_6 / ((uint64_t)3))) == 1231231231), 96, 2);
    return 0;
}

int milone_main() {
    int call_7 = signedCases_(0);
    int call_8 = unsignedCases_(0);
    return 0;
}
