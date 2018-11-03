int test_1(int pred_2) {
    int if_16;
    if (!(!(pred_2))) goto else_1;
    exit(1);
    if_16 = 0;
    goto end_if_2;
else_1:;
    if_16 = 0;
end_if_2:;
    return 0;
}

int neg_3(int x_4) {
    return (0 - x_4);
}

int abs_5(int x_6) {
    int if_17;
    if (!((0 <= x_6))) goto else_3;
    if_17 = x_6;
    goto end_if_4;
else_3:;
    int call_18 = neg_3(x_6);
    if_17 = call_18;
end_if_4:;
    return if_17;
}

int gcd_7(int x_8, int y_9) {
    int if_19;
    if (!((y_9 == 0))) goto else_5;
    int call_20 = abs_5(x_8);
    if_19 = call_20;
    goto end_if_6;
else_5:;
    int call_21 = gcd_7(y_9, (x_8 % y_9));
    if_19 = call_21;
end_if_6:;
    return if_19;
}

struct Tuple_1 {
    int t0;
};

int go_12(struct Tuple_1 caps_50, int k_13) {
    int x_11 = caps_50.t0;
    int if_22;
    if (!((x_11 < (k_13 * k_13)))) goto else_7;
    if_22 = 1;
    goto end_if_8;
else_7:;
    int if_23;
    if (!(((x_11 % k_13) != 0))) goto else_9;
    struct Tuple_1 caps_49;
    caps_49.t0 = x_11;
    int call_24 = go_12(caps_49, (k_13 + 1));
    if_23 = call_24;
    goto end_if_10;
else_9:;
    if_23 = 0;
end_if_10:;
    if_22 = if_23;
end_if_8:;
    return if_22;
}

int isPrime_10(int x_11) {
    int if_25;
    if (!((2 <= x_11))) goto else_11;
    struct Tuple_1 caps_52;
    caps_52.t0 = x_11;
    int call_26 = go_12(caps_52, 2);
    if_25 = call_26;
    goto end_if_12;
else_11:;
    if_25 = 0;
end_if_12:;
    return if_25;
}

int main() {
    int call_27 = abs_5(0);
    int call_28 = test_1((call_27 == 0));
    int call_29 = abs_5(1);
    int call_30 = test_1((call_29 == 1));
    int call_31 = neg_3(1);
    int call_32 = abs_5(call_31);
    int call_33 = test_1((call_32 == 1));
    int call_34 = gcd_7(1, 1);
    int call_35 = test_1((call_34 == 1));
    int call_36 = gcd_7(12, 18);
    int call_37 = test_1((call_36 == 6));
    int call_38 = neg_3(6);
    int call_39 = gcd_7(4, call_38);
    int call_40 = test_1((call_39 == 2));
    int call_41 = isPrime_10(2);
    int call_42 = test_1(call_41);
    int call_43 = isPrime_10(3);
    int call_44 = test_1(call_43);
    int call_45 = isPrime_10(4);
    int call_46 = test_1(!(call_45));
    int call_47 = isPrime_10(1000000007);
    int call_48 = test_1(call_47);
    return 0;
}
