int fizzBuzz_3(int i_4) {
    int if_5;
    if (!((i_4 <= 15))) goto else_1;
    int if_6;
    if (!(((i_4 % 15) == 0))) goto else_3;
    printf("FizzBuzz\n");
    int call_7 = 0;
    if_6 = 0;
    goto end_if_4;
else_3:;
    int if_8;
    if (!(((i_4 % 3) == 0))) goto else_5;
    printf("Fizz\n");
    int call_9 = 0;
    if_8 = 0;
    goto end_if_6;
else_5:;
    int if_10;
    if (!(((i_4 % 5) == 0))) goto else_7;
    printf("Buzz\n");
    int call_11 = 0;
    if_10 = 0;
    goto end_if_8;
else_7:;
    printf("%d\n", i_4);
    int call_12 = 0;
    if_10 = 0;
end_if_8:;
    if_8 = 0;
end_if_6:;
    if_6 = 0;
end_if_4:;
    int call_13 = fizzBuzz_3((i_4 + 1));
    if_5 = 0;
    goto end_if_2;
else_1:;
    if_5 = 0;
end_if_2:;
    return 0;
}

int main() {
    int call_14 = fizzBuzz_3(1);
    return 0;
}
