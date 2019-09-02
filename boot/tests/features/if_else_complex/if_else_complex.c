int main();

int main() {
    int match_;
    if (!((1 == 1))) goto next_2;
    printf("then\n");
    int call_ = 0;
    struct String hello_ = (struct String){.str = "hello", .len = 5};
    int match_1;
    if (!((1 == 1))) goto next_5;
    match_1 = 0;
    goto end_match_4;
next_5:;
    if (!((1 == 0))) goto next_6;
    struct String message_ = hello_;
    match_1 = 1;
    goto end_match_4;
next_6:;
end_match_4:;
    match_ = match_1;
    goto end_match_1;
next_2:;
    if (!((1 == 0))) goto next_3;
    printf("else\n");
    int call_1 = 0;
    match_ = 1;
    goto end_match_1;
next_3:;
end_match_1:;
    return match_;
}
