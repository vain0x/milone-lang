char at_(int i_, struct String s_);

int main();

char at_(int i_, struct String s_) {
    return s_.str[i_];
}

int main() {
    struct String hello_ = (struct String){.str = "hello", .len = 5};
    int match_;
    int match_1;
    if (!(((hello_.str[0] == 'h') == 1))) goto next_3;
    match_1 = (hello_.str[4] == 'o');
    goto end_match_2;
next_3:;
    if (!(((hello_.str[0] == 'h') == 0))) goto next_4;
    match_1 = 0;
    goto end_match_2;
next_4:;
end_match_2:;
    if (!(((!(match_1)) == 1))) goto next_5;
    exit(1);
    match_ = 0;
    goto end_match_1;
next_5:;
    if (!(((!(match_1)) == 0))) goto next_6;
    match_ = 0;
    goto end_match_1;
next_6:;
end_match_1:;
    int match_2;
    char call_ = at_(0, hello_);
    if (!(((call_ != 'h') == 1))) goto next_8;
    exit(1);
    match_2 = 0;
    goto end_match_7;
next_8:;
    if (!(((call_ != 'h') == 0))) goto next_9;
    match_2 = 0;
    goto end_match_7;
next_9:;
end_match_7:;
    return 0;
}
