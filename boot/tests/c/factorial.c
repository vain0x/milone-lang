int factorial_2(int x_3) {
    int if_5;
    if ((x_3 == 0)) {
        if_5 = 1;
    } else {
        int call_6 = factorial_2((x_3 - 1));
        if_5 = (x_3 * call_6);
    }
    return if_5;
}

int main() {
    int call_7 = factorial_2(5);
    return (call_7 - 120);
}
