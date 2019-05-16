int g_(int x_1);

int f_(int x_);

int main();

int g_(int x_1) {
    return x_1;
}

int f_(int x_) {
    return x_;
}

int main() {
    int call_ = f_(1);
    int call_1 = g_(1);
    return (call_ - call_1);
}
