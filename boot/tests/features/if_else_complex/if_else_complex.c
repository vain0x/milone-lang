int main();

int main() {
    int match_;
    if (!((1 == 1))) goto next_2;
    printf("then\n");
    int call_ = 0;
    struct String hello_ = (struct String){.str = "hello", .len = 5};
    int match_1;
    if (!((1 == 1))) goto next_4;
    match_1 = 0;
    goto end_match_3;
next_4:;
    if (!((1 == 0))) goto next_5;
    struct String message_ = hello_;
    match_1 = 1;
    goto end_match_3;
next_5:;
    exit(1);
end_match_3:;
    match_ = match_1;
    goto end_match_1;
next_2:;
    if (!((1 == 0))) goto next_6;
    printf("else\n");
    int call_1 = 0;
    match_ = 1;
    goto end_match_1;
next_6:;
    exit(1);
end_match_1:;
    return match_;
}
