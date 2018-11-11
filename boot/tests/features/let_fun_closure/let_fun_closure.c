struct Tuple_1 {
    int t0;
};

int sub_(struct Tuple_1 caps_, int x_) {
    int y_ = caps_.t0;
    return (x_ - y_);
}

int main() {
    int y_ = 3;
    struct Tuple_1 caps_2;
    caps_2.t0 = y_;
    int call_ = sub_(caps_2, 8);
    return (call_ - 5);
}
