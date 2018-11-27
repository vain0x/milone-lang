struct IntIntTuple2;

struct IntIntIntIntTuple2Tuple3;

struct IntIntIntIntIntIntIntIntIntIntIntTuple11;

int main();

struct IntIntTuple2 {
    int t0;
    int t1;
};

struct IntIntIntIntTuple2Tuple3 {
    int t0;
    int t1;
    struct IntIntTuple2 t2;
};

struct IntIntIntIntIntIntIntIntIntIntIntTuple11 {
    int t0;
    int t1;
    int t2;
    int t3;
    int t4;
    int t5;
    int t6;
    int t7;
    int t8;
    int t9;
    int t10;
};

int main() {
    struct IntIntTuple2 tuple_1;
    tuple_1.t0 = 3;
    tuple_1.t1 = 4;
    struct IntIntIntIntTuple2Tuple3 tuple_;
    tuple_.t0 = 1;
    tuple_.t1 = 2;
    tuple_.t2 = tuple_1;
    int x_ = tuple_.t0;
    int y_ = tuple_.t1;
    int z_ = tuple_.t2.t0;
    int w_ = tuple_.t2.t1;
    int match_;
    int match_1;
    int match_2;
    int match_3;
    if (!(((x_ == 1) == 1))) goto next_5;
    match_3 = (y_ == 2);
    goto end_match_4;
next_5:;
    if (!(((x_ == 1) == 0))) goto next_6;
    match_3 = 0;
    goto end_match_4;
next_6:;
    exit(1);
end_match_4:;
    if (!((match_3 == 1))) goto next_7;
    match_2 = (z_ == 3);
    goto end_match_3;
next_7:;
    if (!((match_3 == 0))) goto next_8;
    match_2 = 0;
    goto end_match_3;
next_8:;
    exit(1);
end_match_3:;
    if (!((match_2 == 1))) goto next_9;
    match_1 = (w_ == 4);
    goto end_match_2;
next_9:;
    if (!((match_2 == 0))) goto next_10;
    match_1 = 0;
    goto end_match_2;
next_10:;
    exit(1);
end_match_2:;
    if (!(((!(match_1)) == 1))) goto next_11;
    exit(1);
    match_ = 0;
    goto end_match_1;
next_11:;
    if (!(((!(match_1)) == 0))) goto next_12;
    match_ = 0;
    goto end_match_1;
next_12:;
    exit(1);
end_match_1:;
    struct IntIntIntIntIntIntIntIntIntIntIntTuple11 tuple_2;
    tuple_2.t0 = 1;
    tuple_2.t1 = 2;
    tuple_2.t2 = 3;
    tuple_2.t3 = 4;
    tuple_2.t4 = 5;
    tuple_2.t5 = 6;
    tuple_2.t6 = 7;
    tuple_2.t7 = 8;
    tuple_2.t8 = 9;
    tuple_2.t9 = 10;
    tuple_2.t10 = 11;
    struct IntIntIntIntIntIntIntIntIntIntIntTuple11 t11_ = tuple_2;
    return 0;
}
