#include "milone.h"

int main();

int main() {
    struct String str_ = (struct String){.str = "Hello, John!", .len = 12};
    int match_;
    struct String call_ = str_substring(0, 5, str_);
    if (!(((str_cmp(call_, (struct String){.str = "Hello", .len = 5}) != 0) == 1))) goto next_2;
    exit(1);
    match_ = 0;
    goto end_match_1;
next_2:;
    if (!(((str_cmp(call_, (struct String){.str = "Hello", .len = 5}) != 0) == 0))) goto next_3;
    match_ = 0;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    int match_1;
    struct String call_1 = str_substring(7, 4, str_);
    if (!(((str_cmp(call_1, (struct String){.str = "John", .len = 4}) != 0) == 1))) goto next_5;
    exit(2);
    match_1 = 0;
    goto end_match_4;
next_5:;
    if (!(((str_cmp(call_1, (struct String){.str = "John", .len = 4}) != 0) == 0))) goto next_6;
    match_1 = 0;
    goto end_match_4;
next_6:;
    exit(1);
end_match_4:;
    int match_2;
    struct String call_2 = str_substring(11, 1, str_);
    if (!(((str_cmp(call_2, (struct String){.str = "!", .len = 1}) != 0) == 1))) goto next_8;
    exit(3);
    match_2 = 0;
    goto end_match_7;
next_8:;
    if (!(((str_cmp(call_2, (struct String){.str = "!", .len = 1}) != 0) == 0))) goto next_9;
    match_2 = 0;
    goto end_match_7;
next_9:;
    exit(1);
end_match_7:;
    return 0;
}
