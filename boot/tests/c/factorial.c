int factorial_2(int x_3) {
    int if_5;
    int op_6 = (x_3 == 0);
    if (op_6) {
        if_5 = 1;
    } else {
        int op_7 = (x_3 - 1);
        int call_8 = factorial_2(op_7);
        int op_9 = (x_3 * call_8);
        if_5 = op_9;
    }
    return if_5;
}

int main() {
    int call_10 = factorial_2(5);
    int op_11 = (call_10 - 120);
    return op_11;
}
