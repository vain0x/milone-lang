int inc_1(int x_2) {
    return (x_2 + 1);
}

int twice_3(int x_4) {
    return (x_4 * x_4);
}

int sub_5(int x_6, int y_7) {
    return (x_6 - y_7);
}

int between_8(int l_9, int r_10, int x_11) {
    int if_15;
    if (!((l_9 <= x_11))) goto else_1;
    if_15 = (x_11 < r_10);
    goto end_if_2;
else_1:;
    if_15 = 0;
end_if_2:;
    return if_15;
}

int main() {
    int call_16 = inc_1(1);
    int call_17 = twice_3(call_16);
    int call_18 = twice_3(call_17);
    int n_14 = call_18;
    int if_19;
    if (!((n_14 != 16))) goto else_3;
    exit(1);
    if_19 = 0;
    goto end_if_4;
else_3:;
    if_19 = 0;
end_if_4:;
    int if_20;
    void* call_21 = sub_5(100, 98);
    void* call_22 = between_8(2, 3, call_21);
    if (!(!(call_22))) goto else_5;
    exit(2);
    if_20 = 0;
    goto end_if_6;
else_5:;
    if_20 = 0;
end_if_6:;
    return 0;
}
