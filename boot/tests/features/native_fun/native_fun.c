int intCmp_(int l_, int r_);

int main();

int intCmp_(int l_, int r_) {
    int call_ = int_cmp(l_, r_);
    return call_;
}

int main() {
    int call_1 = intCmp_(5, 3);
    milone_assert((call_1 == 1));
    int call_2 = 0;
    return 0;
}
