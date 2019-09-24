#include "milone.h"

int main();

int main() {
    char call_ = ((char)97);
    milone_assert((call_ == 'a'), 1, 2);
    int call_1 = 0;
    char call_2 = ((char)0);
    milone_assert((call_2 == '\0'), 2, 2);
    int call_3 = 0;
    int call_4 = 0;
    milone_assert((call_4 == 0), 4, 2);
    int call_5 = 0;
    int call_6 = ((int)'a');
    milone_assert(((call_6 - 97) == 0), 5, 2);
    int call_7 = 0;
    int call_8 = str_to_int((struct String){.str = "42", .len = 2});
    milone_assert(((call_8 - 42) == 0), 6, 2);
    int call_9 = 0;
    int call_10 = str_to_int((struct String){.str = "-1", .len = 2});
    milone_assert(((call_10 + 1) == 0), 7, 2);
    int call_11 = 0;
    struct String call_12 = str_of_int(0);
    milone_assert((str_cmp(call_12, (struct String){.str = "0", .len = 1}) == 0), 9, 2);
    int call_13 = 0;
    struct String call_14 = str_of_int((0 - 97));
    milone_assert((str_cmp(call_14, (struct String){.str = "-97", .len = 3}) == 0), 10, 2);
    int call_15 = 0;
    struct String call_16 = str_of_char('a');
    milone_assert((str_cmp(call_16, (struct String){.str = "a", .len = 1}) == 0), 11, 2);
    int call_17 = 0;
    struct String call_18 = str_of_char('\0');
    milone_assert((str_cmp(call_18, (struct String){.str = "", .len = 0}) == 0), 12, 2);
    int call_19 = 0;
    struct String call_20 = (struct String){.str = "fix", .len = 3};
    milone_assert((str_cmp(call_20, (struct String){.str = "fix", .len = 3}) == 0), 13, 2);
    int call_21 = 0;
    return 0;
}
