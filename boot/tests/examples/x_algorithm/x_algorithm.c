int test_(int pred_) {
    int if_;
    if (!((!(pred_)))) goto else_1;
    exit(1);
    if_ = 0;
    goto end_if_2;
else_1:;
    if_ = 0;
end_if_2:;
    return 0;
}

int neg_(int x_) {
    return (0 - x_);
}

int abs_(int x_1) {
    int if_1;
    if (!((0 <= x_1))) goto else_3;
    if_1 = x_1;
    goto end_if_4;
else_3:;
    int call_ = neg_(x_1);
    if_1 = call_;
end_if_4:;
    return if_1;
}

int gcd_(int x_2, int y_) {
    int if_2;
    if (!((y_ == 0))) goto else_5;
    int call_1 = abs_(x_2);
    if_2 = call_1;
    goto end_if_6;
else_5:;
    int call_2 = gcd_(y_, (x_2 % y_));
    if_2 = call_2;
end_if_6:;
    return if_2;
}

struct IntTuple1 {
    int t0;
};

int go_(struct IntTuple1 caps_1, int k_) {
    int x_3 = caps_1.t0;
    int if_3;
    if (!((x_3 < (k_ * k_)))) goto else_7;
    if_3 = 1;
    goto end_if_8;
else_7:;
    int if_4;
    if (!(((x_3 % k_) != 0))) goto else_9;
    struct IntTuple1 caps_;
    caps_.t0 = x_3;
    int call_3 = go_(caps_, (k_ + 1));
    if_4 = call_3;
    goto end_if_10;
else_9:;
    if_4 = 0;
end_if_10:;
    if_3 = if_4;
end_if_8:;
    return if_3;
}

int isPrime_(int x_3) {
    int if_5;
    if (!((2 <= x_3))) goto else_11;
    struct IntTuple1 caps_3;
    caps_3.t0 = x_3;
    int call_4 = go_(caps_3, 2);
    if_5 = call_4;
    goto end_if_12;
else_11:;
    if_5 = 0;
end_if_12:;
    return if_5;
}

int main() {
    int call_5 = abs_(0);
    int call_6 = test_((call_5 == 0));
    int call_7 = abs_(1);
    int call_8 = test_((call_7 == 1));
    int call_9 = neg_(1);
    int call_10 = abs_(call_9);
    int call_11 = test_((call_10 == 1));
    int call_12 = gcd_(1, 1);
    int call_13 = test_((call_12 == 1));
    int call_14 = gcd_(12, 18);
    int call_15 = test_((call_14 == 6));
    int call_16 = neg_(6);
    int call_17 = gcd_(4, call_16);
    int call_18 = test_((call_17 == 2));
    int call_19 = isPrime_(2);
    int call_20 = test_(call_19);
    int call_21 = isPrime_(3);
    int call_22 = test_(call_21);
    int call_23 = isPrime_(4);
    int call_24 = test_((!(call_23)));
    int call_25 = isPrime_(1000000007);
    int call_26 = test_(call_25);
    return 0;
}
