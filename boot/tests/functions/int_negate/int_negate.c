int f_(int x_);

int main();

int f_(int x_) {
    return (x_ - 2);
}

int main() {
    int m_ = (0 - 2);
    milone_assert(((m_ + 2) == 0));
    int call_ = 0;
    int u_ = 2;
    int v_ = (0 - u_);
    milone_assert(((v_ + 2) == 0));
    int call_1 = 0;
    int call_2 = f_(4);
    int y_ = (0 - call_2);
    milone_assert(((y_ + 2) == 0));
    int call_3 = 0;
    return 0;
}
