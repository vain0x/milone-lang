int fizzBuzz_2(int i_3) {
    int op_5 = (i_3 <= 15);
    int if_4;
    if (op_5) {
        int op_7 = (i_3 % 15);
        int op_8 = (op_7 == 0);
        int if_6;
        if (op_8) {
            printf("FizzBuzz\n");
            if_6 = 0;
        } else {
            int op_10 = (i_3 % 3);
            int op_11 = (op_10 == 0);
            int if_9;
            if (op_11) {
                printf("Fizz\n");
                if_9 = 0;
            } else {
                int op_13 = (i_3 % 5);
                int op_14 = (op_13 == 0);
                int if_12;
                if (op_14) {
                    printf("Buzz\n");
                    if_12 = 0;
                } else {
                    printf("%d\n", i_3);
                    if_12 = 0;
                }
                if_9 = if_12;
            }
            if_6 = if_9;
        }
        int op_15 = (i_3 + 1);
        if_4 = fizzBuzz_2(op_15);
    } else {
        if_4 = 0;
    }
    return if_4;
}

int main() {
    fizzBuzz_2(1);
    return 0;
}
