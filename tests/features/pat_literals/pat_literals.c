#include "milone.h"

int main();

int main() {
    int match_;
    match_ = 0;
    goto end_match_1;
next_2:;
end_match_1:;
    int match_1;
    if (true) goto next_4;
    milone_assert(false, 9, 13);
    match_1 = 0;
    goto end_match_3;
next_4:;
    if (false) goto next_5;
    match_1 = 0;
    goto end_match_3;
next_5:;
    exit(1);
end_match_3:;
    int switch_;
    switch (1) {
        case 0:
            goto clause_7;

        case 1:
            goto clause_8;

        default:
            goto clause_9;
    }
clause_7:;
    milone_assert(false, 13, 9);
    switch_ = 0;
    goto switch_next_6;
clause_8:;
    switch_ = 0;
    goto switch_next_6;
clause_9:;
    milone_assert(false, 15, 9);
    switch_ = 0;
    goto switch_next_6;
switch_next_6:;
    int switch_1;
    switch ('a') {
        case 'A':
            goto clause_11;

        case 'a':
            goto clause_12;

        default:
            goto clause_13;
    }
clause_11:;
    milone_assert(false, 18, 11);
    switch_1 = 0;
    goto switch_next_10;
clause_12:;
    switch_1 = 0;
    goto switch_next_10;
clause_13:;
    milone_assert(false, 20, 9);
    switch_1 = 0;
    goto switch_next_10;
switch_next_10:;
    int match_2;
    if ((str_cmp((struct String){.str = "a", .len = 1}, (struct String){.str = "an", .len = 2}) != 0)) goto next_15;
    milone_assert(false, 23, 12);
    match_2 = 0;
    goto end_match_14;
next_15:;
    if ((str_cmp((struct String){.str = "a", .len = 1}, (struct String){.str = "a", .len = 1}) != 0)) goto next_16;
    match_2 = 0;
    goto end_match_14;
next_16:;
    milone_assert(false, 25, 9);
    match_2 = 0;
    goto end_match_14;
next_17:;
end_match_14:;
    return 0;
}