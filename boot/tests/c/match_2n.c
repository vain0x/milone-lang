struct Tuple_1 {
    int t0;
    int t1;
};

int main() {
    int match_4;
    struct Tuple_1 tuple_5;
    tuple_5.t0 = (2 * 2);
    tuple_5.t1 = (3 * 3);
    if (!((tuple_5.t0 == 4))) goto next_2;
    if (!((tuple_5.t1 == 9))) goto next_2;
    match_4 = 0;
    goto end_match_1;
next_2:;
    if (!((tuple_5.t0 == 999))) goto next_3;
    int y_2 = tuple_5.t1;
    match_4 = 1;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return match_4;
}
