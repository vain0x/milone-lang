#include "milone.h"

int main();

int main() {
    int match_;
    int match_1;
    int match_2;
    if ((2 < 1)) goto next_4;
    match_2 = (2 < 3);
    goto end_match_3;
next_4:;
    if ((2 >= 1)) goto next_5;
    match_2 = 0;
    goto end_match_3;
next_5:;
    exit(1);
end_match_3:;
    if ((!(match_2))) goto next_6;
    match_1 = 1;
    goto end_match_2;
next_6:;
    if (match_2) goto next_7;
    int match_3;
    if ((2 >= 3)) goto next_9;
    match_3 = (2 >= 1);
    goto end_match_8;
next_9:;
    if ((2 < 3)) goto next_10;
    match_3 = 0;
    goto end_match_8;
next_10:;
    exit(1);
end_match_8:;
    match_1 = match_3;
    goto end_match_2;
next_7:;
    exit(1);
end_match_2:;
    if ((!(match_1))) goto next_11;
    match_ = 0;
    goto end_match_1;
next_11:;
    if (match_1) goto next_12;
    match_ = 1;
    goto end_match_1;
next_12:;
    exit(1);
end_match_1:;
    return match_;
}
