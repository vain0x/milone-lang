int go_3(struct String s_4, int i_5, int d_6) {
    int if_13;
    if (!((s_4.len <= i_5))) goto else_1;
    if_13 = (d_6 == 0);
    goto end_if_2;
else_1:;
    int if_14;
    if (!((s_4.str[i_5] == '('))) goto else_3;
    int call_15 = go_3(s_4, (i_5 + 1), (d_6 + 1));
    if_14 = call_15;
    goto end_if_4;
else_3:;
    int if_16;
    if (!((d_6 <= 0))) goto else_5;
    if_16 = 0;
    goto end_if_6;
else_5:;
    int call_17 = go_3(s_4, (i_5 + 1), (d_6 - 1));
    if_16 = call_17;
end_if_6:;
    if_14 = if_16;
end_if_4:;
    if_13 = if_14;
end_if_2:;
    return if_13;
}

struct String parse_7(struct String s_8) {
    struct String if_18;
    int call_19 = go_3(s_8, 0, 0);
    if (!(call_19)) goto else_7;
    if_18 = (struct String){.str = "Accept", .len = 6};
    goto end_if_8;
else_7:;
    if_18 = (struct String){.str = "Reject", .len = 6};
end_if_8:;
    return if_18;
}

int main() {
    struct String case1_9 = (struct String){.str = "()", .len = 2};
    struct String case2_10 = (struct String){.str = "()((())(()))()", .len = 14};
    struct String case3_11 = (struct String){.str = "(()", .len = 3};
    struct String case4_12 = (struct String){.str = ")(", .len = 2};
    struct String call_20 = parse_7(case1_9);
    printf("case1 (A): %s\n", call_20.str);
    int call_21 = 0;
    struct String call_22 = parse_7(case2_10);
    printf("case2 (A): %s\n", call_22.str);
    int call_23 = 0;
    struct String call_24 = parse_7(case3_11);
    printf("case3 (R): %s\n", call_24.str);
    int call_25 = 0;
    struct String call_26 = parse_7(case4_12);
    printf("case4 (R): %s\n", call_26.str);
    int call_27 = 0;
    return 0;
}
