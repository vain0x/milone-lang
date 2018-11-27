struct StringIntTuple2;

int go_(struct StringIntTuple2 caps_1, int i_);

int main();

struct StringIntTuple2 {
    struct String t0;
    int t1;
};

int go_(struct StringIntTuple2 caps_1, int i_) {
    int len_ = caps_1.t1;
    struct String source_ = caps_1.t0;
    int match_;
    if (!(((i_ < len_) == 1))) goto next_2;
    int match_1;
    if (!(((source_.str[i_] == 'o') == 1))) goto next_4;
    printf("%d\n", i_);
    int call_ = 0;
    match_1 = 0;
    goto end_match_3;
next_4:;
    if (!(((source_.str[i_] == 'o') == 0))) goto next_5;
    match_1 = 0;
    goto end_match_3;
next_5:;
    exit(1);
end_match_3:;
    struct StringIntTuple2 caps_;
    caps_.t0 = source_;
    caps_.t1 = len_;
    int call_1 = go_(caps_, (i_ + 1));
    match_ = 0;
    goto end_match_1;
next_2:;
    if (!(((i_ < len_) == 0))) goto next_6;
    match_ = 0;
    goto end_match_1;
next_6:;
    exit(1);
end_match_1:;
    return 0;
}

int main() {
    struct String source_ = (struct String){.str = "hello world", .len = 11};
    int len_ = source_.len;
    struct StringIntTuple2 caps_3;
    caps_3.t0 = source_;
    caps_3.t1 = len_;
    int call_2 = go_(caps_3, 0);
    return 0;
}
