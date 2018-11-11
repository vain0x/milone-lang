struct Tuple_1 {
    int t0;
    int t1;
};

int sub_(struct Tuple_1 arg_) {
    int x_ = arg_.t0;
    int y_ = arg_.t1;
    return (x_ - y_);
}

int main() {
    struct Tuple_1 tuple_;
    tuple_.t0 = 8;
    tuple_.t1 = 3;
    int call_ = sub_(tuple_);
    return (call_ - 5);
}
