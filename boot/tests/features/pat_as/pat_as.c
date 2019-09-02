int simpleCase_(int arg_);

struct IntIntTuple2;

int shadowingCase_(int arg_1);

int main();

int simpleCase_(int arg_) {
    int match_;
    int x_ = 1;
    if (!((x_ == 1))) goto next_2;
    int match_1;
    if (!(((x_ != 1) == 1))) goto next_5;
    exit(1);
    match_1 = 0;
    goto end_match_4;
next_5:;
    if (!(((x_ != 1) == 0))) goto next_6;
    match_1 = 0;
    goto end_match_4;
next_6:;
end_match_4:;
    match_ = 0;
    goto end_match_1;
next_2:;
    exit(1);
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    return 0;
}

struct IntIntTuple2 {
    int t0;
    int t1;
};

int shadowingCase_(int arg_1) {
    int x_1 = 1;
    int match_2;
    struct IntIntTuple2 tuple_;
    tuple_.t0 = x_1;
    tuple_.t1 = 2;
    struct IntIntTuple2 y_ = tuple_;
    int x_2 = y_.t1;
    int y1_ = y_.t0;
    int y2_ = y_.t1;
    int match_3;
    int match_4;
    int match_5;
    if (!(((x_2 == 2) == 1))) goto next_13;
    match_5 = (y1_ == 1);
    goto end_match_12;
next_13:;
    if (!(((x_2 == 2) == 0))) goto next_14;
    match_5 = 0;
    goto end_match_12;
next_14:;
end_match_12:;
    if (!((match_5 == 1))) goto next_15;
    match_4 = (y2_ == 2);
    goto end_match_11;
next_15:;
    if (!((match_5 == 0))) goto next_16;
    match_4 = 0;
    goto end_match_11;
next_16:;
end_match_11:;
    if (!(((!(match_4)) == 1))) goto next_17;
    exit(1);
    match_3 = 0;
    goto end_match_10;
next_17:;
    if (!(((!(match_4)) == 0))) goto next_18;
    match_3 = 0;
    goto end_match_10;
next_18:;
end_match_10:;
    match_2 = 0;
    goto end_match_7;
next_8:;
    exit(1);
    match_2 = 0;
    goto end_match_7;
next_9:;
end_match_7:;
    return 0;
}

int main() {
    int call_ = simpleCase_(0);
    int call_1 = shadowingCase_(0);
    return 0;
}
