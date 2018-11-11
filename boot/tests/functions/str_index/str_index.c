int main() {
    struct String hello_ = (struct String){.str = "hello", .len = 5};
    int if_;
    int if_1;
    if (!((hello_.str[0] == 'h'))) goto else_3;
    if_1 = (hello_.str[4] == 'o');
    goto end_if_4;
else_3:;
    if_1 = 0;
end_if_4:;
    if (!(if_1)) goto else_1;
    if_ = 0;
    goto end_if_2;
else_1:;
    if_ = 1;
end_if_2:;
    return if_;
}
