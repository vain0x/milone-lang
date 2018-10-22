int fizzBuzz_2(int i_3) {
    int if_5;
    if ((i_3 <= 15)) {
        int if_6;
        if (((i_3 % 15) == 0)) {
            printf("FizzBuzz\n");
            int call_7 = 0;
            if_6 = 0;
        } else {
            int if_8;
            if (((i_3 % 3) == 0)) {
                printf("Fizz\n");
                int call_9 = 0;
                if_8 = 0;
            } else {
                int if_10;
                if (((i_3 % 5) == 0)) {
                    printf("Buzz\n");
                    int call_11 = 0;
                    if_10 = 0;
                } else {
                    printf("%d\n", i_3);
                    int call_12 = 0;
                    if_10 = 0;
                }
                if_8 = 0;
            }
            if_6 = 0;
        }
        int call_13 = fizzBuzz_2((i_3 + 1));
        if_5 = 0;
    } else {
        if_5 = 0;
    }
    return 0;
}

int main() {
    int call_14 = fizzBuzz_2(1);
    return 0;
}
