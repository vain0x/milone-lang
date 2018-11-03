struct Tuple_1 {
    char* t0;
    int t1;
};

int go_5(struct Tuple_1 caps_13, int i_6) {
    int len_4 = caps_13.t1;
    char* source_3 = caps_13.t0;
    int if_7;
    if (!((i_6 < len_4))) goto else_1;
    int if_8;
    if (!((source_3[i_6] == 'o'))) goto else_3;
    printf("%d\n", i_6);
    int call_9 = 0;
    if_8 = 0;
    goto end_if_4;
else_3:;
    if_8 = 0;
end_if_4:;
    struct Tuple_1 caps_12;
    caps_12.t0 = source_3;
    caps_12.t1 = len_4;
    int call_10 = go_5(caps_12, (i_6 + 1));
    if_7 = 0;
    goto end_if_2;
else_1:;
    if_7 = 0;
end_if_2:;
    return 0;
}

int main() {
    char* source_3 = "hello world";
    int len_4 = strlen(source_3);
    struct Tuple_1 caps_15;
    caps_15.t0 = source_3;
    caps_15.t1 = len_4;
    int call_11 = go_5(caps_15, 0);
    return 0;
}
