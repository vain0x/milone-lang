struct Tuple_1 {
    int t0;
    int t1;
};

int main() {
    int match_3;
    struct Tuple_1 tuple_4;
    tuple_4.t0 = (2 * 2);
    tuple_4.t1 = (3 * 3);
    if (((tuple_4.t0 == 4) && (tuple_4.t1 == 9))) {
        match_3 = 0;
    } else {
        exit(1);
    }
    return match_3;
}
