#include "milone.h"

int main();

int main() {
    int le_ = (str_cmp((struct String){.str = "a", .len = 1}, (struct String){.str = "b", .len = 1}) < 0);
    int eq_ = (str_cmp((struct String){.str = "o", .len = 1}, (struct String){.str = "o", .len = 1}) == 0);
    int match_;
    int match_1;
    if ((!(le_))) goto next_3;
    match_1 = eq_;
    goto end_match_2;
next_3:;
    if (le_) goto next_4;
    match_1 = 0;
    goto end_match_2;
next_4:;
    exit(1);
end_match_2:;
    if ((!(match_1))) goto next_5;
    match_ = 0;
    goto end_match_1;
next_5:;
    if (match_1) goto next_6;
    match_ = 1;
    goto end_match_1;
next_6:;
    exit(1);
end_match_1:;
    return match_;
}
