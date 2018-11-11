int go_(struct String s_, int i_, int d_) {
    int if_;
    if (!((s_.len <= i_))) goto else_1;
    if_ = (d_ == 0);
    goto end_if_2;
else_1:;
    int if_1;
    if (!((s_.str[i_] == '('))) goto else_3;
    int call_ = go_(s_, (i_ + 1), (d_ + 1));
    if_1 = call_;
    goto end_if_4;
else_3:;
    int if_2;
    if (!((d_ <= 0))) goto else_5;
    if_2 = 0;
    goto end_if_6;
else_5:;
    int call_1 = go_(s_, (i_ + 1), (d_ - 1));
    if_2 = call_1;
end_if_6:;
    if_1 = if_2;
end_if_4:;
    if_ = if_1;
end_if_2:;
    return if_;
}

struct String parse_(struct String s_1) {
    struct String if_3;
    int call_2 = go_(s_1, 0, 0);
    if (!(call_2)) goto else_7;
    if_3 = (struct String){.str = "Accept", .len = 6};
    goto end_if_8;
else_7:;
    if_3 = (struct String){.str = "Reject", .len = 6};
end_if_8:;
    return if_3;
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
