#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

int main(int argc, char** argv);

int main(int argc, char** argv) {
    milone_start(argc, argv);
    uint32_t call_;
    struct String call_1;
    milone_assert((((int32_t)(uint32_t)42U) == 42), (struct String){.ptr = "int_flavor_unsigned/int_flavor_unsigned.milone", .len = 46}, 6, 2);
    milone_assert((((uint32_t)42) == (uint32_t)42U), (struct String){.ptr = "int_flavor_unsigned/int_flavor_unsigned.milone", .len = 46}, 7, 2);
    milone_assert((((uint32_t)'A') == (uint32_t)65U), (struct String){.ptr = "int_flavor_unsigned/int_flavor_unsigned.milone", .len = 46}, 10, 2);
    milone_assert((((char)(uint32_t)65U) == 'A'), (struct String){.ptr = "int_flavor_unsigned/int_flavor_unsigned.milone", .len = 46}, 11, 2);
    call_ = string_to_uint32((struct String){.ptr = "42", .len = 2});
    milone_assert((((int32_t)call_) == 42), (struct String){.ptr = "int_flavor_unsigned/int_flavor_unsigned.milone", .len = 46}, 14, 2);
    call_1 = string_of_uint64((uint32_t)42U);
    milone_assert((string_compare(call_1, (struct String){.ptr = "42", .len = 2}) == 0), (struct String){.ptr = "int_flavor_unsigned/int_flavor_unsigned.milone", .len = 46}, 15, 2);
    milone_assert((((int32_t)((uint32_t)40U + (uint32_t)2U)) == 42), (struct String){.ptr = "int_flavor_unsigned/int_flavor_unsigned.milone", .len = 46}, 18, 2);
    milone_assert((((int32_t)((uint32_t)49U - (uint32_t)7U)) == 42), (struct String){.ptr = "int_flavor_unsigned/int_flavor_unsigned.milone", .len = 46}, 19, 2);
    milone_assert((((int32_t)((uint32_t)6U * (uint32_t)7U)) == 42), (struct String){.ptr = "int_flavor_unsigned/int_flavor_unsigned.milone", .len = 46}, 20, 2);
    milone_assert((((int32_t)((uint32_t)294U / (uint32_t)7U)) == 42), (struct String){.ptr = "int_flavor_unsigned/int_flavor_unsigned.milone", .len = 46}, 21, 2);
    milone_assert((((int32_t)((uint32_t)2063U % (uint32_t)43U)) == 42), (struct String){.ptr = "int_flavor_unsigned/int_flavor_unsigned.milone", .len = 46}, 22, 2);
    milone_assert((((int32_t)((((uint32_t)-1) - (uint32_t)1U) / (uint32_t)2U)) == 2147483647), (struct String){.ptr = "int_flavor_unsigned/int_flavor_unsigned.milone", .len = 46}, 25, 2);
    milone_assert(((uint32_t)2U < (uint32_t)3U), (struct String){.ptr = "int_flavor_unsigned/int_flavor_unsigned.milone", .len = 46}, 28, 2);
    milone_assert(((uint32_t)3U >= (uint32_t)2U), (struct String){.ptr = "int_flavor_unsigned/int_flavor_unsigned.milone", .len = 46}, 29, 2);
    milone_assert(((uint32_t)3U >= (uint32_t)2U), (struct String){.ptr = "int_flavor_unsigned/int_flavor_unsigned.milone", .len = 46}, 30, 2);
    milone_assert(((uint32_t)2U == (uint32_t)2U), (struct String){.ptr = "int_flavor_unsigned/int_flavor_unsigned.milone", .len = 46}, 31, 2);
    milone_assert(((uint32_t)2U != (uint32_t)3U), (struct String){.ptr = "int_flavor_unsigned/int_flavor_unsigned.milone", .len = 46}, 32, 2);
    return 0;
}
