struct IntTuple1;

int aux_1(struct IntTuple1 arg_, int arg_1);

int id_1(int x_);

int main();

struct IntTuple1 {
    int t0;
};

int aux_1(struct IntTuple1 arg_, int arg_1) {
    int x_ = arg_.t0;
    return x_;
}

int id_1(int x_) {
    struct IntTuple1 tuple_;
    tuple_.t0 = x_;
    int call_ = aux_1(tuple_, 0);
    return call_;
}

int main() {
    int call_1 = id_1(1);
    milone_assert((call_1 == 1));
    int call_2 = 0;
    return 0;
}
