int factorial_(int x_) {
    int if_;
    if (!((x_ == 0))) goto else_1;
    if_ = 1;
    goto end_if_2;
else_1:;
    int call_ = factorial_((x_ - 1));
    if_ = (x_ * call_);
end_if_2:;
    return if_;
}

int main() {
    int call_1 = factorial_(5);
    return (call_1 - 120);
}
