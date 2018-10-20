int fizzBuzz_2(int i_3) {
    int if_5;
    int op_6 = (i_3 <= 15);
    if (op_6) {
        int if_7;
        int op_8 = (i_3 % 15);
        int op_9 = (op_8 == 0);
        if (op_9) {
            printf("FizzBuzz\n");
            int call_10 = 0;
            if_7 = 0;
        } else {
            int if_11;
            int op_12 = (i_3 % 3);
            int op_13 = (op_12 == 0);
            if (op_13) {
                printf("Fizz\n");
                int call_14 = 0;
                if_11 = 0;
            } else {
                int if_15;
                int op_16 = (i_3 % 5);
                int op_17 = (op_16 == 0);
                if (op_17) {
                    printf("Buzz\n");
                    int call_18 = 0;
                    if_15 = 0;
                } else {
                    printf("%d\n", i_3);
                    int call_19 = 0;
                    if_15 = 0;
                }
                if_11 = 0;
            }
            if_7 = 0;
        }
        int op_20 = (i_3 + 1);
        int call_21 = fizzBuzz_2(op_20);
        if_5 = 0;
    } else {
        if_5 = 0;
    }
    return 0;
}

int main() {
    int call_22 = fizzBuzz_2(1);
    return 0;
}
