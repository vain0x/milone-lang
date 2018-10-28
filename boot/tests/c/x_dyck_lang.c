struct Tuple_1 {
    char* t0;
    int t1;
};

struct Tuple_2 {
    struct Tuple_1 t0;
    int t1;
};

struct Tuple_3 {
    struct Tuple_2 t0;
    int t1;
};

int go_2(struct Tuple_3 arg_15) {
    char* s_3 = arg_15.t0.t0.t0;
    int n_4 = arg_15.t0.t0.t1;
    int i_5 = arg_15.t0.t1;
    int d_6 = arg_15.t1;
    int if_16;
    if (!((n_4 <= i_5))) goto else_1;
    if_16 = (d_6 == 0);
    goto end_if_2;
else_1:;
    int if_17;
    if (!((s_3[i_5] == 40))) goto else_3;
    struct Tuple_1 tuple_20;
    tuple_20.t0 = s_3;
    tuple_20.t1 = n_4;
    struct Tuple_2 tuple_19;
    tuple_19.t0 = tuple_20;
    tuple_19.t1 = (i_5 + 1);
    struct Tuple_3 tuple_18;
    tuple_18.t0 = tuple_19;
    tuple_18.t1 = (d_6 + 1);
    int call_21 = go_2(tuple_18);
    if_17 = call_21;
    goto end_if_4;
else_3:;
    int if_22;
    if (!((d_6 <= 0))) goto else_5;
    if_22 = 0;
    goto end_if_6;
else_5:;
    struct Tuple_1 tuple_25;
    tuple_25.t0 = s_3;
    tuple_25.t1 = n_4;
    struct Tuple_2 tuple_24;
    tuple_24.t0 = tuple_25;
    tuple_24.t1 = (i_5 + 1);
    struct Tuple_3 tuple_23;
    tuple_23.t0 = tuple_24;
    tuple_23.t1 = (d_6 - 1);
    int call_26 = go_2(tuple_23);
    if_22 = call_26;
end_if_6:;
    if_17 = if_22;
end_if_4:;
    if_16 = if_17;
end_if_2:;
    return if_16;
}

char* parse_7(struct Tuple_1 arg_27) {
    char* s_8 = arg_27.t0;
    int n_9 = arg_27.t1;
    char* if_28;
    struct Tuple_1 tuple_31;
    tuple_31.t0 = s_8;
    tuple_31.t1 = n_9;
    struct Tuple_2 tuple_30;
    tuple_30.t0 = tuple_31;
    tuple_30.t1 = 0;
    struct Tuple_3 tuple_29;
    tuple_29.t0 = tuple_30;
    tuple_29.t1 = 0;
    int call_32 = go_2(tuple_29);
    if (!(call_32)) goto else_7;
    if_28 = "Accept";
    goto end_if_8;
else_7:;
    if_28 = "Reject";
end_if_8:;
    return if_28;
}

int main() {
    struct Tuple_1 tuple_33;
    tuple_33.t0 = "()";
    tuple_33.t1 = 2;
    struct Tuple_1 case1_10 = tuple_33;
    struct Tuple_1 tuple_34;
    tuple_34.t0 = "()((())(()))()";
    tuple_34.t1 = 14;
    struct Tuple_1 case2_11 = tuple_34;
    struct Tuple_1 tuple_35;
    tuple_35.t0 = "(()";
    tuple_35.t1 = 3;
    struct Tuple_1 case3_12 = tuple_35;
    struct Tuple_1 tuple_36;
    tuple_36.t0 = ")(";
    tuple_36.t1 = 2;
    struct Tuple_1 case4_13 = tuple_36;
    char* call_37 = parse_7(case1_10);
    printf("case1 (A): %s\n", call_37);
    int call_38 = 0;
    char* call_39 = parse_7(case2_11);
    printf("case2 (A): %s\n", call_39);
    int call_40 = 0;
    char* call_41 = parse_7(case3_12);
    printf("case3 (R): %s\n", call_41);
    int call_42 = 0;
    char* call_43 = parse_7(case4_13);
    printf("case4 (R): %s\n", call_43);
    int call_44 = 0;
    return 0;
}
