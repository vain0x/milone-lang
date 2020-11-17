#include "milone.h"

int go_(struct String s_, int i_, int d_);

struct String parse_(struct String s_1);

int main();

int go_(struct String s_, int i_, int d_) {
tailrec_1:;
    int if_;
    if ((i_ < s_.len)) goto else_2;
    if_ = (d_ == 0);
    goto end_if_3;
else_2:;
    int if_1;
    if ((s_.str[i_] != '(')) goto else_4;
    struct String arg_ = s_;
    int arg_1 = (i_ + 1);
    int arg_2 = (d_ + 1);
    s_ = arg_;
    i_ = arg_1;
    d_ = arg_2;
    goto tailrec_1;
    if_1 = 0;
    goto end_if_5;
else_4:;
    int if_2;
    if ((0 < d_)) goto else_6;
    if_2 = 0;
    goto end_if_7;
else_6:;
    struct String arg_3 = s_;
    int arg_4 = (i_ + 1);
    int arg_5 = (d_ - 1);
    s_ = arg_3;
    i_ = arg_4;
    d_ = arg_5;
    goto tailrec_1;
    if_2 = 0;
end_if_7:;
    if_1 = if_2;
end_if_5:;
    if_ = if_1;
end_if_3:;
    return if_;
}

struct String parse_(struct String s_1) {
    struct String if_3;
    int call_ = go_(s_1, 0, 0);
    if ((!(call_))) goto else_8;
    if_3 = (struct String){.str = "Accept", .len = 6};
    goto end_if_9;
else_8:;
    if_3 = (struct String){.str = "Reject", .len = 6};
end_if_9:;
    return if_3;
}

int main() {
    struct String case1_ = (struct String){.str = "()", .len = 2};
    struct String case2_ = (struct String){.str = "()((())(()))()", .len = 14};
    struct String case3_ = (struct String){.str = "(()", .len = 3};
    struct String case4_ = (struct String){.str = ")(", .len = 2};
    struct String call_1 = parse_(case1_);
    printf("case1 (A): %s\n", call_1.str);
    int call_2 = 0;
    struct String call_3 = parse_(case2_);
    printf("case2 (A): %s\n", call_3.str);
    int call_4 = 0;
    struct String call_5 = parse_(case3_);
    printf("case3 (R): %s\n", call_5.str);
    int call_6 = 0;
    struct String call_7 = parse_(case4_);
    printf("case4 (R): %s\n", call_7.str);
    int call_8 = 0;
    return 0;
}
