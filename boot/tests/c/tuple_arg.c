struct Tuple_1 {
    int t0;
    int t1;
};

int sub_3(struct Tuple_1 arg_6) {
    int x_4 = arg_6.t0;
    int y_5 = arg_6.t1;
    return (x_4 - y_5);
}

int main() {
    struct Tuple_1 tuple_7;
    tuple_7.t0 = 8;
    tuple_7.t1 = 3;
    int call_8 = sub_3(tuple_7);
    return (call_8 - 5);
}
