#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

int main(int argc, char **argv);

int main(int argc, char **argv) {
    milone_start(argc, argv);
    char match_;
    char match_1;
    char switch_;
    char switch_1;
    char switch_2;
    char match_2;
    match_ = 0;
    goto end_match_1;
next_2:;
end_match_1:;
    if (true) goto next_4;
    if (true) milone_assert_error("pat_literals/pat_literals.milone", 9, 13);
    match_1 = 0;
    goto end_match_3;
next_4:;
    if (false) goto next_5;
    match_1 = 0;
    goto end_match_3;
next_5:;
    milone_exhaust_error("pat_literals/pat_literals.milone", 8, 2);
end_match_3:;
    switch (1) {
        case 0:
            goto clause_7;

        case 1:
            goto clause_8;

        default:
            goto clause_9;
    }
clause_7:;
    if (true) milone_assert_error("pat_literals/pat_literals.milone", 13, 9);
    switch_ = 0;
    goto switch_next_6;
clause_8:;
    switch_ = 0;
    goto switch_next_6;
clause_9:;
    if (true) milone_assert_error("pat_literals/pat_literals.milone", 15, 9);
    switch_ = 0;
    goto switch_next_6;
switch_next_6:;
    switch (-2) {
        case 2:
            goto clause_11;

        case -2:
            goto clause_12;

        default:
            goto clause_13;
    }
clause_11:;
    if (true) milone_assert_error("pat_literals/pat_literals.milone", 18, 9);
    switch_1 = 0;
    goto switch_next_10;
clause_12:;
    switch_1 = 0;
    goto switch_next_10;
clause_13:;
    if (true) milone_assert_error("pat_literals/pat_literals.milone", 20, 9);
    switch_1 = 0;
    goto switch_next_10;
switch_next_10:;
    switch ('a') {
        case 'A':
            goto clause_15;

        case 'a':
            goto clause_16;

        default:
            goto clause_17;
    }
clause_15:;
    if (true) milone_assert_error("pat_literals/pat_literals.milone", 23, 11);
    switch_2 = 0;
    goto switch_next_14;
clause_16:;
    switch_2 = 0;
    goto switch_next_14;
clause_17:;
    if (true) milone_assert_error("pat_literals/pat_literals.milone", 25, 9);
    switch_2 = 0;
    goto switch_next_14;
switch_next_14:;
    if ((string_compare((struct String){.ptr = "a", .len = 1}, (struct String){.ptr = "an", .len = 2}) != 0)) goto next_19;
    if (true) milone_assert_error("pat_literals/pat_literals.milone", 28, 12);
    match_2 = 0;
    goto end_match_18;
next_19:;
    if ((string_compare((struct String){.ptr = "a", .len = 1}, (struct String){.ptr = "a", .len = 1}) != 0)) goto next_20;
    match_2 = 0;
    goto end_match_18;
next_20:;
    if (true) milone_assert_error("pat_literals/pat_literals.milone", 30, 9);
    match_2 = 0;
    goto end_match_18;
next_21:;
end_match_18:;
    return 0;
}
