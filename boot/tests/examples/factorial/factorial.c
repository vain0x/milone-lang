int factorial_(int x_);

int main();

int factorial_(int x_) {
    int match_;
    if (!(((x_ == 0) == 1))) goto next_2;
    match_ = 1;
    goto end_match_1;
next_2:;
    if (!(((x_ == 0) == 0))) goto next_3;
    int call_ = factorial_((x_ - 1));
    match_ = (x_ * call_);
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return match_;
}

int main() {
    int call_1 = factorial_(5);
    return (call_1 - 120);
}
