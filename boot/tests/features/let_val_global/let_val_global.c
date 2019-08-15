struct IntTuple1;

int f_(struct IntTuple1 arg_, int arg_1);

int g_(struct IntTuple1 arg_2, int arg_3);

int main();

struct IntTuple1 {
    int t0;
};

int f_(struct IntTuple1 arg_, int arg_1) {
    int success_ = arg_.t0;
    return success_;
}

int g_(struct IntTuple1 arg_2, int arg_3) {
    int success_ = arg_2.t0;
    struct IntTuple1 tuple_;
    tuple_.t0 = success_;
    int call_ = f_(tuple_, 0);
    return call_;
}

int main() {
    int success_ = 0;
    struct IntTuple1 tuple_1;
    tuple_1.t0 = success_;
    int call_1 = g_(tuple_1, 0);
    return call_1;
}
