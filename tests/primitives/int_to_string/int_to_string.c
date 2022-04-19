#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

int main(int argc, char** argv);

int main(int argc, char** argv) {
    milone_start(argc, argv);
    int call_;
    int call_1;
    struct String call_2;
    struct String call_3;
    struct String call_4;
    struct String call_5;
    milone_assert((((char)97) == 'a'), (struct String){.ptr = "int_to_string/int_to_string.milone", .len = 34}, 1, 2);
    milone_assert((((char)0) == '\0'), (struct String){.ptr = "int_to_string/int_to_string.milone", .len = 34}, 2, 2);
    milone_assert((0 == 0), (struct String){.ptr = "int_to_string/int_to_string.milone", .len = 34}, 4, 2);
    milone_assert(((((int)'a') - 97) == 0), (struct String){.ptr = "int_to_string/int_to_string.milone", .len = 34}, 5, 2);
    call_ = string_to_int32((struct String){.ptr = "42", .len = 2});
    milone_assert(((call_ - 42) == 0), (struct String){.ptr = "int_to_string/int_to_string.milone", .len = 34}, 6, 2);
    call_1 = string_to_int32((struct String){.ptr = "-1", .len = 2});
    milone_assert(((call_1 + 1) == 0), (struct String){.ptr = "int_to_string/int_to_string.milone", .len = 34}, 7, 2);
    call_2 = string_of_int64(0);
    milone_assert((string_compare(call_2, (struct String){.ptr = "0", .len = 1}) == 0), (struct String){.ptr = "int_to_string/int_to_string.milone", .len = 34}, 9, 2);
    call_3 = string_of_int64((0 - 97));
    milone_assert((string_compare(call_3, (struct String){.ptr = "-97", .len = 3}) == 0), (struct String){.ptr = "int_to_string/int_to_string.milone", .len = 34}, 10, 2);
    call_4 = string_of_char('a');
    milone_assert((string_compare(call_4, (struct String){.ptr = "a", .len = 1}) == 0), (struct String){.ptr = "int_to_string/int_to_string.milone", .len = 34}, 11, 2);
    call_5 = string_of_char('\0');
    milone_assert((string_compare(call_5, (struct String){.ptr = "", .len = 0}) == 0), (struct String){.ptr = "int_to_string/int_to_string.milone", .len = 34}, 12, 2);
    milone_assert((string_compare((struct String){.ptr = "fix", .len = 3}, (struct String){.ptr = "fix", .len = 3}) == 0), (struct String){.ptr = "int_to_string/int_to_string.milone", .len = 34}, 13, 2);
    return 0;
}
