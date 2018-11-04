int main() {
    struct String hello_3 = (struct String){.str = "hello", .len = 5};
    struct String world_4 = (struct String){.str = "world", .len = 5};
    int if_6;
    if (!((hello_3.len != 5))) goto else_1;
    exit(1);
    if_6 = 0;
    goto end_if_2;
else_1:;
    if_6 = 0;
end_if_2:;
    struct String message_5 = str_add(hello_3, world_4);
    int if_7;
    if (!((message_5.len != 10))) goto else_3;
    exit(1);
    if_7 = 0;
    goto end_if_4;
else_3:;
    if_7 = 0;
end_if_4:;
    return 0;
}
