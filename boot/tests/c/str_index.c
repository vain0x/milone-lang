int main() {
    struct String hello_3 = (struct String){.str = "hello", .len = 5};
    int if_4;
    int if_5;
    if (!((hello_3.str[0] == 'h'))) goto else_3;
    if_5 = (hello_3.str[4] == 'o');
    goto end_if_4;
else_3:;
    if_5 = 0;
end_if_4:;
    if (!(if_5)) goto else_1;
    if_4 = 0;
    goto end_if_2;
else_1:;
    if_4 = 1;
end_if_2:;
    return if_4;
}
