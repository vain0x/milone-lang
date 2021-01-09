#include "milone.h"

bool go_(struct String s_, int i_, int d_);

struct String parse_(struct String s_1);

int milone_main();

bool go_(struct String s_, int i_, int d_) {
tailrec_1:;
    bool if_;
    if ((i_ >= s_.len)) {
        goto then_3;
    } else {
        goto else_4;
    }
then_3:;
    if_ = (d_ == 0);
    goto if_next_2;
else_4:;
    bool if_1;
    if ((s_.str[i_] == '(')) {
        goto then_6;
    } else {
        goto else_7;
    }
then_6:;
    struct String arg_ = s_;
    int arg_1 = (i_ + 1);
    int arg_2 = (d_ + 1);
    s_ = arg_;
    i_ = arg_1;
    d_ = arg_2;
    goto tailrec_1;
    if_1 = false;
    goto if_next_5;
else_7:;
    bool if_2;
    if ((0 >= d_)) {
        goto then_9;
    } else {
        goto else_10;
    }
then_9:;
    if_2 = false;
    goto if_next_8;
else_10:;
    struct String arg_3 = s_;
    int arg_4 = (i_ + 1);
    int arg_5 = (d_ - 1);
    s_ = arg_3;
    i_ = arg_4;
    d_ = arg_5;
    goto tailrec_1;
    if_2 = false;
    goto if_next_8;
if_next_8:;
    if_1 = if_2;
    goto if_next_5;
if_next_5:;
    if_ = if_1;
    goto if_next_2;
if_next_2:;
    return if_;
}

struct String parse_(struct String s_1) {
    bool call_ = go_(s_1, 0, 0);
    struct String if_3;
    if (call_) {
        goto then_12;
    } else {
        goto else_13;
    }
then_12:;
    if_3 = (struct String){.str = "Accept", .len = 6};
    goto if_next_11;
else_13:;
    if_3 = (struct String){.str = "Reject", .len = 6};
    goto if_next_11;
if_next_11:;
    return if_3;
}

int milone_main() {
    struct String case1_ = (struct String){.str = "()", .len = 2};
    struct String case2_ = (struct String){.str = "()((())(()))()", .len = 14};
    struct String case3_ = (struct String){.str = "(()", .len = 3};
    struct String case4_ = (struct String){.str = ")(", .len = 2};
    struct String call_1 = parse_(case1_);
    printf("case1 (A): %s\n", str_to_c_str(call_1));
    struct String call_2 = parse_(case2_);
    printf("case2 (A): %s\n", str_to_c_str(call_2));
    struct String call_3 = parse_(case3_);
    printf("case3 (R): %s\n", str_to_c_str(call_3));
    struct String call_4 = parse_(case4_);
    printf("case4 (R): %s\n", str_to_c_str(call_4));
    return 0;
}
