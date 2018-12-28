struct IntIntTuple2;

int eq_(struct IntIntTuple2 t_);

int main();

struct IntIntTuple2 {
    int t0;
    int t1;
};

int eq_(struct IntIntTuple2 t_) {
    int match_;
    int x_ = t_.t0;
    int y_ = t_.t1;
    if (!((x_ == y_))) goto next_2;
    match_ = 1;
    goto end_match_1;
next_2:;
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    return match_;
}

int main() {
    int match_1;
    struct IntIntTuple2 tuple_;
    tuple_.t0 = 1;
    tuple_.t1 = 1;
    int call_ = eq_(tuple_);
    if (!(((!(call_)) == 1))) goto next_5;
    exit(1);
    match_1 = 0;
    goto end_match_4;
next_5:;
    if (!(((!(call_)) == 0))) goto next_6;
    match_1 = 0;
    goto end_match_4;
next_6:;
    exit(1);
end_match_4:;
    int match_2;
    struct IntIntTuple2 tuple_1;
    tuple_1.t0 = 1;
    tuple_1.t1 = 2;
    int call_1 = eq_(tuple_1);
    if (!((call_1 == 1))) goto next_8;
    exit(1);
    match_2 = 0;
    goto end_match_7;
next_8:;
    if (!((call_1 == 0))) goto next_9;
    match_2 = 0;
    goto end_match_7;
next_9:;
    exit(1);
end_match_7:;
    return 0;
}
