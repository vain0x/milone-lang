int fizzBuzz_(int i_) {
    int if_;
    if (!((i_ <= 15))) goto else_1;
    int if_1;
    if (!(((i_ % 15) == 0))) goto else_3;
    printf("FizzBuzz\n");
    int call_ = 0;
    if_1 = 0;
    goto end_if_4;
else_3:;
    int if_2;
    if (!(((i_ % 3) == 0))) goto else_5;
    printf("Fizz\n");
    int call_1 = 0;
    if_2 = 0;
    goto end_if_6;
else_5:;
    int if_3;
    if (!(((i_ % 5) == 0))) goto else_7;
    printf("Buzz\n");
    int call_2 = 0;
    if_3 = 0;
    goto end_if_8;
else_7:;
    printf("%d\n", i_);
    int call_3 = 0;
    if_3 = 0;
end_if_8:;
    if_2 = 0;
end_if_6:;
    if_1 = 0;
end_if_4:;
    int call_4 = fizzBuzz_((i_ + 1));
    if_ = 0;
    goto end_if_2;
else_1:;
    if_ = 0;
end_if_2:;
    return 0;
}

int main() {
    int call_5 = fizzBuzz_(1);
    return 0;
}
