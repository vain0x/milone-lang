int main() {
    int le_3 = (str_cmp("a", "b") < 0);
    int eq_4 = (str_cmp("o", "o") == 0);
    int if_5;
    int if_6;
    if (!(le_3)) goto else_3;
    if_6 = eq_4;
    goto end_if_4;
else_3:;
    if_6 = 0;
end_if_4:;
    if (!(if_6)) goto else_1;
    if_5 = 0;
    goto end_if_2;
else_1:;
    if_5 = 1;
end_if_2:;
    return if_5;
}
