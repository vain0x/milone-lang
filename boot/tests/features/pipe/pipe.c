int inc_(int x_) {
    return (x_ + 1);
}

int twice_(int x_1) {
    return (x_1 * x_1);
}

int sub_(int x_2, int y_) {
    return (x_2 - y_);
}

int between_(int l_, int r_, int x_3) {
    int if_;
    if (!((l_ <= x_3))) goto else_1;
    if_ = (x_3 < r_);
    goto end_if_2;
else_1:;
    if_ = 0;
end_if_2:;
    return if_;
}

int main() {
    int call_ = inc_(1);
    int call_1 = twice_(call_);
    int call_2 = twice_(call_1);
    int n_ = call_2;
    int if_1;
    if (!((n_ != 16))) goto else_3;
    exit(1);
    if_1 = 0;
    goto end_if_4;
else_3:;
    if_1 = 0;
end_if_4:;
    int if_2;
    void* call_3 = sub_(100, 98);
    void* call_4 = between_(2, 3, call_3);
    if (!(!(call_4))) goto else_5;
    exit(2);
    if_2 = 0;
    goto end_if_6;
else_5:;
    if_2 = 0;
end_if_6:;
    return 0;
}
