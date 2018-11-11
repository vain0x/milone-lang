struct Tuple_1 {
    int t0;
};

int sub_4(struct Tuple_1 caps_7, int x_5) {
    int y_3 = caps_7.t0;
    return (x_5 - y_3);
}

int main() {
    int y_3 = 3;
    struct Tuple_1 caps_9;
    caps_9.t0 = y_3;
    int call_6 = sub_4(caps_9, 8);
    return (call_6 - 5);
}
