struct StringIntTuple2;

int go_(struct StringIntTuple2 arg_, int i_);

int main();

struct StringIntTuple2 {
    struct String t0;
    int t1;
};

int go_(struct StringIntTuple2 arg_, int i_) {
    struct String source_ = arg_.t0;
    int len_ = arg_.t1;
    int match_;
    if (!(((i_ < len_) == 1))) goto next_2;
    int match_1;
    if (!(((source_.str[i_] == 'o') == 1))) goto next_5;
    printf("%d\n", i_);
    int call_ = 0;
    match_1 = 0;
    goto end_match_4;
next_5:;
    if (!(((source_.str[i_] == 'o') == 0))) goto next_6;
    match_1 = 0;
    goto end_match_4;
next_6:;
end_match_4:;
    struct StringIntTuple2 tuple_;
    tuple_.t0 = source_;
    tuple_.t1 = len_;
    int call_1 = go_(tuple_, (i_ + 1));
    match_ = 0;
    goto end_match_1;
next_2:;
    if (!(((i_ < len_) == 0))) goto next_3;
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    return 0;
}

int main() {
    struct String source_ = (struct String){.str = "hello world", .len = 11};
    int len_ = source_.len;
    struct StringIntTuple2 tuple_1;
    tuple_1.t0 = source_;
    tuple_1.t1 = len_;
    int call_2 = go_(tuple_1, 0);
    return 0;
}
