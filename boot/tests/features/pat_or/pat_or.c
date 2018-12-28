int isZeroOrOne_(int x_);

int main();

int isZeroOrOne_(int x_) {
    int match_;
    if (!((x_ == 0))) goto next_2;
    match_ = 1;
    goto end_match_1;
next_2:;
    if (!((x_ == 1))) goto next_3;
    match_ = 1;
    goto end_match_1;
next_3:;
    match_ = 0;
    goto end_match_1;
next_4:;
end_match_1:;
    return match_;
}

int main() {
    int match_1;
    int match_2;
    int call_ = isZeroOrOne_(0);
    if (!((call_ == 1))) goto next_7;
    int call_1 = isZeroOrOne_(1);
    match_2 = call_1;
    goto end_match_6;
next_7:;
    if (!((call_ == 0))) goto next_8;
    match_2 = 0;
    goto end_match_6;
next_8:;
    exit(1);
end_match_6:;
    if (!(((!(match_2)) == 1))) goto next_9;
    exit(1);
    match_1 = 0;
    goto end_match_5;
next_9:;
    if (!(((!(match_2)) == 0))) goto next_10;
    match_1 = 0;
    goto end_match_5;
next_10:;
    exit(1);
end_match_5:;
    int match_3;
    int call_2 = isZeroOrOne_(2);
    if (!((call_2 == 1))) goto next_12;
    exit(1);
    match_3 = 0;
    goto end_match_11;
next_12:;
    if (!((call_2 == 0))) goto next_13;
    match_3 = 0;
    goto end_match_11;
next_13:;
    exit(1);
end_match_11:;
    return 0;
}
