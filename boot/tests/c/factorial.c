int factorial_3(int x_4) {
    int if_5;
    if (!((x_4 == 0))) goto else_1;
    if_5 = 1;
    goto end_if_2;
else_1:;
    int call_6 = factorial_3((x_4 - 1));
    if_5 = (x_4 * call_6);
end_if_2:;
    return if_5;
}

int main() {
    int call_7 = factorial_3(5);
    return (call_7 - 120);
}
