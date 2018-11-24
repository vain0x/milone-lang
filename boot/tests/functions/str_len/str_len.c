int main();

int main() {
    struct String hello_ = (struct String){.str = "hello", .len = 5};
    struct String world_ = (struct String){.str = "world", .len = 5};
    int if_;
    if (!((hello_.len != 5))) goto else_1;
    exit(1);
    if_ = 0;
    goto end_if_2;
else_1:;
    if_ = 0;
end_if_2:;
    struct String message_ = str_add(hello_, world_);
    int if_1;
    if (!((message_.len != 10))) goto else_3;
    exit(1);
    if_1 = 0;
    goto end_if_4;
else_3:;
    if_1 = 0;
end_if_4:;
    return 0;
}
