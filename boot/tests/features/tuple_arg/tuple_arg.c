struct IntIntTuple2;

int sub_(struct IntIntTuple2 arg_);

int main();

struct IntIntTuple2 {
    int t0;
    int t1;
};

int sub_(struct IntIntTuple2 arg_) {
    int x_ = arg_.t0;
    int y_ = arg_.t1;
    return (x_ - y_);
}

int main() {
    struct IntIntTuple2 tuple_;
    tuple_.t0 = 8;
    tuple_.t1 = 3;
    int call_ = sub_(tuple_);
    return (call_ - 5);
}
