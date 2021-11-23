#include <milone.h>

int main(int argc, char** argv);

int main(int argc, char** argv) {
    milone_start(argc, argv);
    milone_assert((((char)97) == 'a'), (struct String){.str = "int_to_string/int_to_string.milone", .len = 34}, 1, 2);
    milone_assert((((char)0) == '\0'), (struct String){.str = "int_to_string/int_to_string.milone", .len = 34}, 2, 2);
    milone_assert((0 == 0), (struct String){.str = "int_to_string/int_to_string.milone", .len = 34}, 4, 2);
    milone_assert(((((int)'a') - 97) == 0), (struct String){.str = "int_to_string/int_to_string.milone", .len = 34}, 5, 2);
    int call_ = str_to_int((struct String){.str = "42", .len = 2});
    milone_assert(((call_ - 42) == 0), (struct String){.str = "int_to_string/int_to_string.milone", .len = 34}, 6, 2);
    int call_1 = str_to_int((struct String){.str = "-1", .len = 2});
    milone_assert(((call_1 + 1) == 0), (struct String){.str = "int_to_string/int_to_string.milone", .len = 34}, 7, 2);
    struct String call_2 = str_of_int64(0);
    milone_assert((str_compare(call_2, (struct String){.str = "0", .len = 1}) == 0), (struct String){.str = "int_to_string/int_to_string.milone", .len = 34}, 9, 2);
    struct String call_3 = str_of_int64((0 - 97));
    milone_assert((str_compare(call_3, (struct String){.str = "-97", .len = 3}) == 0), (struct String){.str = "int_to_string/int_to_string.milone", .len = 34}, 10, 2);
    struct String call_4 = str_of_char('a');
    milone_assert((str_compare(call_4, (struct String){.str = "a", .len = 1}) == 0), (struct String){.str = "int_to_string/int_to_string.milone", .len = 34}, 11, 2);
    struct String call_5 = str_of_char('\0');
    milone_assert((str_compare(call_5, (struct String){.str = "", .len = 0}) == 0), (struct String){.str = "int_to_string/int_to_string.milone", .len = 34}, 12, 2);
    milone_assert((str_compare((struct String){.str = "fix", .len = 3}, (struct String){.str = "fix", .len = 3}) == 0), (struct String){.str = "int_to_string/int_to_string.milone", .len = 34}, 13, 2);
    return 0;
}
