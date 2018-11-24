char at_(int i_, struct String s_) {
    return s_.str[i_];
}

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
    if (!((!(if_1)))) goto else_1;
    exit(1);
    if_ = 0;
    goto end_if_2;
else_1:;
    if_ = 0;
end_if_2:;
    int if_2;
    char call_ = at_(0, hello_);
    if (!((call_ != 'h'))) goto else_5;
    exit(1);
    if_2 = 0;
    goto end_if_6;
else_5:;
    if_2 = 0;
end_if_6:;
    return 0;
}
