int go_3(char* s_7, int n_6, int i_5, int d_4) {
    int if_15;
    if (!((n_6 <= i_5))) goto else_1;
    if_15 = (d_4 == 0);
    goto end_if_2;
else_1:;
    int if_16;
    if (!((s_7[i_5] == 40))) goto else_3;
    int call_17 = go_3(s_7, n_6, (i_5 + 1), (d_4 + 1));
    if_16 = call_17;
    goto end_if_4;
else_3:;
    int if_18;
    if (!((d_4 <= 0))) goto else_5;
    if_18 = 0;
    goto end_if_6;
else_5:;
    int call_19 = go_3(s_7, n_6, (i_5 + 1), (d_4 - 1));
    if_18 = call_19;
end_if_6:;
    if_16 = if_18;
end_if_4:;
    if_15 = if_16;
end_if_2:;
    return if_15;
}

struct Tuple_1 {
    char* t0;
    int t1;
};

char* parse_8(struct Tuple_1 arg_20) {
    char* s_9 = arg_20.t0;
    int n_10 = arg_20.t1;
    char* if_21;
    int call_22 = go_3(s_9, n_10, 0, 0);
    if (!(call_22)) goto else_7;
    if_21 = "Accept";
    goto end_if_8;
else_7:;
    if_21 = "Reject";
end_if_8:;
    return if_21;
}

int main() {
    struct Tuple_1 tuple_23;
    tuple_23.t0 = "()";
    tuple_23.t1 = 2;
    struct Tuple_1 case1_11 = tuple_23;
    struct Tuple_1 tuple_24;
    tuple_24.t0 = "()((())(()))()";
    tuple_24.t1 = 14;
    struct Tuple_1 case2_12 = tuple_24;
    struct Tuple_1 tuple_25;
    tuple_25.t0 = "(()";
    tuple_25.t1 = 3;
    struct Tuple_1 case3_13 = tuple_25;
    struct Tuple_1 tuple_26;
    tuple_26.t0 = ")(";
    tuple_26.t1 = 2;
    struct Tuple_1 case4_14 = tuple_26;
    char* call_27 = parse_8(case1_11);
    printf("case1 (A): %s\n", call_27);
    int call_28 = 0;
    char* call_29 = parse_8(case2_12);
    printf("case2 (A): %s\n", call_29);
    int call_30 = 0;
    char* call_31 = parse_8(case3_13);
    printf("case3 (R): %s\n", call_31);
    int call_32 = 0;
    char* call_33 = parse_8(case4_14);
    printf("case4 (R): %s\n", call_33);
    int call_34 = 0;
    return 0;
}
