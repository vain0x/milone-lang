int test_(int pred_);

int neg_(int x_);

int abs_(int x_1);

int gcd_(int x_2, int y_);

struct IntTuple1;

int go_(struct IntTuple1 arg_, int k_);

int isPrime_(int x_3);

int main();

int test_(int pred_) {
    int match_;
    if (!(((!(pred_)) == 1))) goto next_2;
    exit(1);
    match_ = 0;
    goto end_match_1;
next_2:;
    if (!(((!(pred_)) == 0))) goto next_3;
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    return 0;
}

int neg_(int x_) {
    return (0 - x_);
}

int abs_(int x_1) {
    int match_1;
    if (!(((0 <= x_1) == 1))) goto next_5;
    match_1 = x_1;
    goto end_match_4;
next_5:;
    if (!(((0 <= x_1) == 0))) goto next_6;
    int call_ = neg_(x_1);
    match_1 = call_;
    goto end_match_4;
next_6:;
end_match_4:;
    return match_1;
}

int gcd_(int x_2, int y_) {
    int match_2;
    if (!(((y_ == 0) == 1))) goto next_8;
    int call_1 = abs_(x_2);
    match_2 = call_1;
    goto end_match_7;
next_8:;
    if (!(((y_ == 0) == 0))) goto next_9;
    int call_2 = gcd_(y_, (x_2 % y_));
    match_2 = call_2;
    goto end_match_7;
next_9:;
end_match_7:;
    return match_2;
}

struct IntTuple1 {
    int t0;
};

int go_(struct IntTuple1 arg_, int k_) {
    int x_3 = arg_.t0;
    int match_3;
    if (!(((x_3 < (k_ * k_)) == 1))) goto next_11;
    match_3 = 1;
    goto end_match_10;
next_11:;
    if (!(((x_3 < (k_ * k_)) == 0))) goto next_12;
    int match_4;
    if (!((((x_3 % k_) != 0) == 1))) goto next_14;
    struct IntTuple1 tuple_;
    tuple_.t0 = x_3;
    int call_3 = go_(tuple_, (k_ + 1));
    match_4 = call_3;
    goto end_match_13;
next_14:;
    if (!((((x_3 % k_) != 0) == 0))) goto next_15;
    match_4 = 0;
    goto end_match_13;
next_15:;
end_match_13:;
    match_3 = match_4;
    goto end_match_10;
next_12:;
end_match_10:;
    return match_3;
}

int isPrime_(int x_3) {
    int match_5;
    if (!(((2 <= x_3) == 1))) goto next_17;
    struct IntTuple1 tuple_1;
    tuple_1.t0 = x_3;
    int call_4 = go_(tuple_1, 2);
    match_5 = call_4;
    goto end_match_16;
next_17:;
    if (!(((2 <= x_3) == 0))) goto next_18;
    match_5 = 0;
    goto end_match_16;
next_18:;
end_match_16:;
    return match_5;
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
