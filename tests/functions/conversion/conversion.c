#include "milone.h"

int main();

int main() {
    milone_assert((((char)97) == 'a'), 1, 2);
    int call_ = 0;
    milone_assert((((char)0) == '\0'), 2, 2);
    int call_1 = 0;
    milone_assert((0 == 0), 4, 2);
    int call_2 = 0;
    milone_assert(((((int)'a') - 97) == 0), 5, 2);
    int call_3 = 0;
    int call_4 = str_to_int((struct String){.str = "42", .len = 2});
    milone_assert(((call_4 - 42) == 0), 6, 2);
    int call_5 = 0;
    int call_6 = str_to_int((struct String){.str = "-1", .len = 2});
    milone_assert(((call_6 + 1) == 0), 7, 2);
    int call_7 = 0;
    struct String call_8 = str_of_int(0);
    milone_assert((str_cmp(call_8, (struct String){.str = "0", .len = 1}) == 0), 9, 2);
    int call_9 = 0;
    struct String call_10 = str_of_int((0 - 97));
    milone_assert((str_cmp(call_10, (struct String){.str = "-97", .len = 3}) == 0), 10, 2);
    int call_11 = 0;
    struct String call_12 = str_of_char('a');
    milone_assert((str_cmp(call_12, (struct String){.str = "a", .len = 1}) == 0), 11, 2);
    int call_13 = 0;
    struct String call_14 = str_of_char('\0');
    milone_assert((str_cmp(call_14, (struct String){.str = "", .len = 0}) == 0), 12, 2);
    int call_15 = 0;
    milone_assert((str_cmp((struct String){.str = "fix", .len = 3}, (struct String){.str = "fix", .len = 3}) == 0), 13, 2);
    int call_16 = 0;
    return 0;
}
