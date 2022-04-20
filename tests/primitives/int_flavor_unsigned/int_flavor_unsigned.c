#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

int main(int argc, char **argv);

int main(int argc, char **argv) {
    milone_start(argc, argv);
    uint32_t call_;
    struct String call_1;
    if ((((int32_t)(uint32_t)42U) != 42)) milone_assert_error("int_flavor_unsigned/int_flavor_unsigned.milone", 6, 2);
    if ((((uint32_t)42) != (uint32_t)42U)) milone_assert_error("int_flavor_unsigned/int_flavor_unsigned.milone", 7, 2);
    if ((((uint32_t)'A') != (uint32_t)65U)) milone_assert_error("int_flavor_unsigned/int_flavor_unsigned.milone", 10, 2);
    if ((((char)(uint32_t)65U) != 'A')) milone_assert_error("int_flavor_unsigned/int_flavor_unsigned.milone", 11, 2);
    call_ = string_to_uint32((struct String){.ptr = "42", .len = 2});
    if ((((int32_t)call_) != 42)) milone_assert_error("int_flavor_unsigned/int_flavor_unsigned.milone", 14, 2);
    call_1 = string_of_uint64((uint32_t)42U);
    if ((string_compare(call_1, (struct String){.ptr = "42", .len = 2}) != 0)) milone_assert_error("int_flavor_unsigned/int_flavor_unsigned.milone", 15, 2);
    if ((((int32_t)((uint32_t)40U + (uint32_t)2U)) != 42)) milone_assert_error("int_flavor_unsigned/int_flavor_unsigned.milone", 18, 2);
    if ((((int32_t)((uint32_t)49U - (uint32_t)7U)) != 42)) milone_assert_error("int_flavor_unsigned/int_flavor_unsigned.milone", 19, 2);
    if ((((int32_t)((uint32_t)6U * (uint32_t)7U)) != 42)) milone_assert_error("int_flavor_unsigned/int_flavor_unsigned.milone", 20, 2);
    if ((((int32_t)((uint32_t)294U / (uint32_t)7U)) != 42)) milone_assert_error("int_flavor_unsigned/int_flavor_unsigned.milone", 21, 2);
    if ((((int32_t)((uint32_t)2063U % (uint32_t)43U)) != 42)) milone_assert_error("int_flavor_unsigned/int_flavor_unsigned.milone", 22, 2);
    if ((((int32_t)((((uint32_t)-1) - (uint32_t)1U) / (uint32_t)2U)) != 2147483647)) milone_assert_error("int_flavor_unsigned/int_flavor_unsigned.milone", 25, 2);
    if (((uint32_t)2U >= (uint32_t)3U)) milone_assert_error("int_flavor_unsigned/int_flavor_unsigned.milone", 28, 2);
    if (((uint32_t)3U < (uint32_t)2U)) milone_assert_error("int_flavor_unsigned/int_flavor_unsigned.milone", 29, 2);
    if (((uint32_t)3U < (uint32_t)2U)) milone_assert_error("int_flavor_unsigned/int_flavor_unsigned.milone", 30, 2);
    if (((uint32_t)2U != (uint32_t)2U)) milone_assert_error("int_flavor_unsigned/int_flavor_unsigned.milone", 31, 2);
    if (((uint32_t)2U == (uint32_t)3U)) milone_assert_error("int_flavor_unsigned/int_flavor_unsigned.milone", 32, 2);
    return 0;
}
