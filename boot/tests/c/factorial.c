int factorial_2(int x_3) {
    int op_5 = (x_3 == 0);
    int if_4;
    if (op_5) {
        if_4 = 1;
    } else {
        int op_6 = (x_3 - 1);
        int op_7 = (x_3 * factorial_2(op_6));
        if_4 = op_7;
    }
    return if_4;
}

int main() {
    int op_8 = (factorial_2(5) - 120);
    return op_8;
}
