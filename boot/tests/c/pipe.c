int inc_1(int x_2) {
    return (x_2 + 1);
}

int twice_3(int x_4) {
    return (x_4 * x_4);
}

int main() {
    int call_8 = inc_1(1);
    int call_9 = twice_3(call_8);
    int call_10 = twice_3(call_9);
    int n_7 = call_10;
    return (n_7 - 16);
}
