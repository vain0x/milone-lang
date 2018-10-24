struct Tuple_1 {
    int t0;
    int t1;
};

int sub_2(struct Tuple_1 arg_6) {
    int x_3 = arg_6.t0;
    int y_4 = arg_6.t1;
    return (x_3 - y_4);
}

int main() {
    struct Tuple_1 tuple_7;
    tuple_7.t0 = 8;
    tuple_7.t1 = 3;
    int call_8 = sub_2(tuple_7);
    return (call_8 - 5);
}
