#include "milone.h"

int main();

int main() {
    struct String str_ = (struct String){.str = "Hello, John!", .len = 12};
    int match_;
    struct String slice_ = str_slice(str_, 0, 4);
    if (!(((str_cmp(slice_, (struct String){.str = "Hello", .len = 5}) != 0) == 1))) goto next_2;
    exit(1);
    match_ = 0;
    goto end_match_1;
next_2:;
    if (!(((str_cmp(slice_, (struct String){.str = "Hello", .len = 5}) != 0) == 0))) goto next_3;
    match_ = 0;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    int match_1;
    struct String slice_1 = str_slice(str_, 7, 10);
    if (!(((str_cmp(slice_1, (struct String){.str = "John", .len = 4}) != 0) == 1))) goto next_5;
    exit(2);
    match_1 = 0;
    goto end_match_4;
next_5:;
    if (!(((str_cmp(slice_1, (struct String){.str = "John", .len = 4}) != 0) == 0))) goto next_6;
    match_1 = 0;
    goto end_match_4;
next_6:;
    exit(1);
end_match_4:;
    int match_2;
    struct String slice_2 = str_slice(str_, 11, 11);
    if (!(((str_cmp(slice_2, (struct String){.str = "!", .len = 1}) != 0) == 1))) goto next_8;
    exit(3);
    match_2 = 0;
    goto end_match_7;
next_8:;
    if (!(((str_cmp(slice_2, (struct String){.str = "!", .len = 1}) != 0) == 0))) goto next_9;
    match_2 = 0;
    goto end_match_7;
next_9:;
    exit(1);
end_match_7:;
    return 0;
}
