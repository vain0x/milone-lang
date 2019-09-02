int even_(int n_);

int odd_(int n_1);

int main();

int even_(int n_) {
    int match_;
    if (!(((n_ == 0) == 1))) goto next_2;
    match_ = 1;
    goto end_match_1;
next_2:;
    if (!(((n_ == 0) == 0))) goto next_3;
    int call_ = odd_((n_ - 1));
    match_ = call_;
    goto end_match_1;
next_3:;
end_match_1:;
    return match_;
}

int odd_(int n_1) {
    int match_1;
    if (!(((n_1 != 0) == 1))) goto next_5;
    int call_1 = even_((n_1 - 1));
    match_1 = call_1;
    goto end_match_4;
next_5:;
    if (!(((n_1 != 0) == 0))) goto next_6;
    match_1 = 0;
    goto end_match_4;
next_6:;
end_match_4:;
    return match_1;
}

int main() {
    int match_2;
    int call_2 = odd_(1);
    if (!(((!(call_2)) == 1))) goto next_8;
    exit(1);
    match_2 = 0;
    goto end_match_7;
next_8:;
    if (!(((!(call_2)) == 0))) goto next_9;
    match_2 = 0;
    goto end_match_7;
next_9:;
end_match_7:;
    int match_3;
    int call_3 = even_(2);
    if (!(((!(call_3)) == 1))) goto next_11;
    exit(1);
    match_3 = 0;
    goto end_match_10;
next_11:;
    if (!(((!(call_3)) == 0))) goto next_12;
    match_3 = 0;
    goto end_match_10;
next_12:;
end_match_10:;
    int match_4;
    int call_4 = even_(3);
    if (!((call_4 == 1))) goto next_14;
    exit(1);
    match_4 = 0;
    goto end_match_13;
next_14:;
    if (!((call_4 == 0))) goto next_15;
    match_4 = 0;
    goto end_match_13;
next_15:;
end_match_13:;
    return 0;
}
