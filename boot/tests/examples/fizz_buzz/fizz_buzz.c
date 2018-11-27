int fizzBuzz_(int i_);

int main();

int fizzBuzz_(int i_) {
    int match_;
    if (!(((i_ <= 15) == 1))) goto next_2;
    int match_1;
    if (!((((i_ % 15) == 0) == 1))) goto next_4;
    printf("FizzBuzz\n");
    int call_ = 0;
    match_1 = 0;
    goto end_match_3;
next_4:;
    if (!((((i_ % 15) == 0) == 0))) goto next_5;
    int match_2;
    if (!((((i_ % 3) == 0) == 1))) goto next_7;
    printf("Fizz\n");
    int call_1 = 0;
    match_2 = 0;
    goto end_match_6;
next_7:;
    if (!((((i_ % 3) == 0) == 0))) goto next_8;
    int match_3;
    if (!((((i_ % 5) == 0) == 1))) goto next_10;
    printf("Buzz\n");
    int call_2 = 0;
    match_3 = 0;
    goto end_match_9;
next_10:;
    if (!((((i_ % 5) == 0) == 0))) goto next_11;
    printf("%d\n", i_);
    int call_3 = 0;
    match_3 = 0;
    goto end_match_9;
next_11:;
    exit(1);
end_match_9:;
    match_2 = 0;
    goto end_match_6;
next_8:;
    exit(1);
end_match_6:;
    match_1 = 0;
    goto end_match_3;
next_5:;
    exit(1);
end_match_3:;
    int call_4 = fizzBuzz_((i_ + 1));
    match_ = 0;
    goto end_match_1;
next_2:;
    if (!(((i_ <= 15) == 0))) goto next_12;
    match_ = 0;
    goto end_match_1;
next_12:;
    exit(1);
end_match_1:;
    return 0;
}

int main() {
    int call_5 = fizzBuzz_(1);
    return 0;
}
