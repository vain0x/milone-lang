int main() {
    int if_3;
    int if_4;
    int if_5;
    if (!((1 <= 2))) goto else_5;
    if_5 = (2 < 3);
    goto end_if_6;
else_5:;
    if_5 = 0;
end_if_6:;
    if (!(if_5)) goto else_3;
    if_4 = 1;
    goto end_if_4;
else_3:;
    int if_6;
    if (!((2 < 3))) goto else_7;
    if_6 = (1 <= 2);
    goto end_if_8;
else_7:;
    if_6 = 0;
end_if_8:;
    if_4 = if_6;
end_if_4:;
    if (!(if_4)) goto else_1;
    if_3 = 0;
    goto end_if_2;
else_1:;
    if_3 = 1;
end_if_2:;
    return if_3;
}
