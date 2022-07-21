#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

int main(int argc, char **argv);

int main(int argc, char **argv) {
    milone_start(argc, argv);
    int32_t call_;
    int32_t call_1;
    struct String call_2;
    struct String call_3;
    struct String call_4;
    struct String call_5;
    if ((0 != 0)) milone_assert_error("int_to_string/int_to_string.milone", 1, 2);
    call_ = string_to_int32((struct String){.ptr = "42", .len = 2});
    if (((call_ - 42) != 0)) milone_assert_error("int_to_string/int_to_string.milone", 2, 2);
    call_1 = string_to_int32((struct String){.ptr = "-1", .len = 2});
    if (((call_1 + 1) != 0)) milone_assert_error("int_to_string/int_to_string.milone", 3, 2);
    call_2 = string_of_int64(0);
    if ((string_compare(call_2, (struct String){.ptr = "0", .len = 1}) != 0)) milone_assert_error("int_to_string/int_to_string.milone", 5, 2);
    call_3 = string_of_int64((0 - 97));
    if ((string_compare(call_3, (struct String){.ptr = "-97", .len = 3}) != 0)) milone_assert_error("int_to_string/int_to_string.milone", 6, 2);
    call_4 = string_of_char('a');
    if ((string_compare(call_4, (struct String){.ptr = "a", .len = 1}) != 0)) milone_assert_error("int_to_string/int_to_string.milone", 7, 2);
    call_5 = string_of_char('\0');
    if ((string_compare(call_5, (struct String){.ptr = "", .len = 0}) != 0)) milone_assert_error("int_to_string/int_to_string.milone", 8, 2);
    if ((string_compare((struct String){.ptr = "fix", .len = 3}, (struct String){.ptr = "fix", .len = 3}) != 0)) milone_assert_error("int_to_string/int_to_string.milone", 9, 2);
    return 0;
}
