int main() {
    int if_5;
    if (!(1)) goto else_1;
    printf("then\n");
    int call_6 = 0;
    struct String hello_3 = (struct String){.str = "hello", .len = 5};
    int if_7;
    if (!(1)) goto else_3;
    if_7 = 0;
    goto end_if_4;
else_3:;
    struct String message_4 = hello_3;
    if_7 = 1;
end_if_4:;
    if_5 = if_7;
    goto end_if_2;
else_1:;
    printf("else\n");
    int call_8 = 0;
    if_5 = 1;
end_if_2:;
    return if_5;
}
