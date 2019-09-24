#include "milone.h"

int go_(struct String s_, int i_, int d_);

struct String parse_(struct String s_1);

int main();

int go_(struct String s_, int i_, int d_) {
    int match_;
    if ((i_ < s_.len)) goto next_2;
    match_ = (d_ == 0);
    goto end_match_1;
next_2:;
    if ((i_ >= s_.len)) goto next_3;
    int match_1;
    if ((s_.str[i_] != '(')) goto next_5;
    int call_ = go_(s_, (i_ + 1), (d_ + 1));
    match_1 = call_;
    goto end_match_4;
next_5:;
    if ((s_.str[i_] == '(')) goto next_6;
    int match_2;
    if ((0 < d_)) goto next_8;
    match_2 = 0;
    goto end_match_7;
next_8:;
    if ((0 >= d_)) goto next_9;
    int call_1 = go_(s_, (i_ + 1), (d_ - 1));
    match_2 = call_1;
    goto end_match_7;
next_9:;
    exit(1);
end_match_7:;
    match_1 = match_2;
    goto end_match_4;
next_6:;
    exit(1);
end_match_4:;
    match_ = match_1;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return match_;
}

struct String parse_(struct String s_1) {
    struct String match_3;
    int call_2 = go_(s_1, 0, 0);
    if ((!(call_2))) goto next_11;
    match_3 = (struct String){.str = "Accept", .len = 6};
    goto end_match_10;
next_11:;
    if (call_2) goto next_12;
    match_3 = (struct String){.str = "Reject", .len = 6};
    goto end_match_10;
next_12:;
    exit(1);
end_match_10:;
    return match_3;
}

int main() {
    struct String case1_ = (struct String){.str = "()", .len = 2};
    struct String case2_ = (struct String){.str = "()((())(()))()", .len = 14};
    struct String case3_ = (struct String){.str = "(()", .len = 3};
    struct String case4_ = (struct String){.str = ")(", .len = 2};
    struct String call_3 = parse_(case1_);
    printf("case1 (A): %s\n", call_3.str);
    int call_4 = 0;
    struct String call_5 = parse_(case2_);
    printf("case2 (A): %s\n", call_5.str);
    int call_6 = 0;
    struct String call_7 = parse_(case3_);
    printf("case3 (R): %s\n", call_7.str);
    int call_8 = 0;
    struct String call_9 = parse_(case4_);
    printf("case4 (R): %s\n", call_9.str);
    int call_10 = 0;
    return 0;
}
