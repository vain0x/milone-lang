int isDigit_1(char c_2) {
    int if_13;
    if (!(('0' <= c_2))) goto else_1;
    if_13 = (c_2 <= '9');
    goto end_if_2;
else_1:;
    if_13 = 0;
end_if_2:;
    return if_13;
}

struct Tuple_1 {
    struct String t0;
};

int readInt_5(struct Tuple_1 caps_35, int i_6) {
    struct String s_4 = caps_35.t0;
    int if_14;
    int if_15;
    if (!((s_4.len <= i_6))) goto else_5;
    if_15 = 1;
    goto end_if_6;
else_5:;
    int call_16 = isDigit_1(s_4.str[i_6]);
    if_15 = !(call_16);
end_if_6:;
    if (!(if_15)) goto else_3;
    if_14 = i_6;
    goto end_if_4;
else_3:;
    struct Tuple_1 caps_34;
    caps_34.t0 = s_4;
    int call_17 = readInt_5(caps_34, (i_6 + 1));
    if_14 = call_17;
end_if_4:;
    return if_14;
}

int go_7(struct Tuple_1 caps_41, int i_8) {
    struct String s_4 = caps_41.t0;
    int if_18;
    if (!((i_8 < s_4.len))) goto else_7;
    int if_19;
    if (!((s_4.str[i_8] == ' '))) goto else_9;
    struct Tuple_1 caps_37;
    caps_37.t0 = s_4;
    int call_20 = go_7(caps_37, (i_8 + 1));
    if_19 = 0;
    goto end_if_10;
else_9:;
    int if_21;
    int if_22;
    int if_23;
    if (!((s_4.str[i_8] == '['))) goto else_15;
    if_23 = 1;
    goto end_if_16;
else_15:;
    if_23 = (s_4.str[i_8] == ']');
end_if_16:;
    if (!(if_23)) goto else_13;
    if_22 = 1;
    goto end_if_14;
else_13:;
    if_22 = (s_4.str[i_8] == ',');
end_if_14:;
    if (!(if_22)) goto else_11;
    printf("punct %c\n", s_4.str[i_8]);
    int call_24 = 0;
    struct Tuple_1 caps_38;
    caps_38.t0 = s_4;
    int call_25 = go_7(caps_38, (i_8 + 1));
    if_21 = 0;
    goto end_if_12;
else_11:;
    int if_26;
    int call_27 = isDigit_1(s_4.str[i_8]);
    if (!(call_27)) goto else_17;
    struct Tuple_1 caps_39;
    caps_39.t0 = s_4;
    int call_28 = readInt_5(caps_39, i_8);
    int r_9 = call_28;
    struct String slice_29 = str_slice(s_4, i_8, (r_9 - 1));
    printf("int %s\n", slice_29.str);
    int call_30 = 0;
    struct Tuple_1 caps_40;
    caps_40.t0 = s_4;
    int call_31 = go_7(caps_40, r_9);
    if_26 = 0;
    goto end_if_18;
else_17:;
    if_26 = 0;
end_if_18:;
    if_21 = 0;
end_if_12:;
    if_19 = 0;
end_if_10:;
    if_18 = 0;
    goto end_if_8;
else_7:;
    if_18 = 0;
end_if_8:;
    return 0;
}

int tokenize_3(struct String s_4) {
    struct Tuple_1 caps_43;
    caps_43.t0 = s_4;
    int call_32 = go_7(caps_43, 0);
    return 0;
}

int main() {
    struct String source_12 = (struct String){.str = "[0, 1000000007, 314159]", .len = 23};
    int call_33 = tokenize_3(source_12);
    return 0;
}
