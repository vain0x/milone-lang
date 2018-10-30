int go_3(char* s_4, int n_5, int i_6, int d_7) {
    int if_15;
    if (!((n_5 <= i_6))) goto else_1;
    if_15 = (d_7 == 0);
    goto end_if_2;
else_1:;
    int if_16;
    if (!((s_4[i_6] == '('))) goto else_3;
    int call_17 = go_3(s_4, n_5, (i_6 + 1), (d_7 + 1));
    if_16 = call_17;
    goto end_if_4;
else_3:;
    int if_18;
    if (!((d_7 <= 0))) goto else_5;
    if_18 = 0;
    goto end_if_6;
else_5:;
    int call_19 = go_3(s_4, n_5, (i_6 + 1), (d_7 - 1));
    if_18 = call_19;
end_if_6:;
    if_16 = if_18;
end_if_4:;
    if_15 = if_16;
end_if_2:;
    return if_15;
}

char* parse_8(char* s_9) {
    int n_10 = strlen(s_9);
    char* if_20;
    int call_21 = go_3(s_9, n_10, 0, 0);
    if (!(call_21)) goto else_7;
    if_20 = "Accept";
    goto end_if_8;
else_7:;
    if_20 = "Reject";
end_if_8:;
    return if_20;
}

int main() {
    char* case1_11 = "()";
    char* case2_12 = "()((())(()))()";
    char* case3_13 = "(()";
    char* case4_14 = ")(";
    char* call_22 = parse_8(case1_11);
    printf("case1 (A): %s\n", call_22);
    int call_23 = 0;
    char* call_24 = parse_8(case2_12);
    printf("case2 (A): %s\n", call_24);
    int call_25 = 0;
    char* call_26 = parse_8(case3_13);
    printf("case3 (R): %s\n", call_26);
    int call_27 = 0;
    char* call_28 = parse_8(case4_14);
    printf("case4 (R): %s\n", call_28);
    int call_29 = 0;
    return 0;
}
