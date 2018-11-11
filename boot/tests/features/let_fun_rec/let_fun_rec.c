struct StringIntTuple2 {
    struct String t0;
    int t1;
};

int go_(struct StringIntTuple2 caps_1, int i_) {
    int len_ = caps_1.t1;
    struct String source_ = caps_1.t0;
    int if_;
    if (!((i_ < len_))) goto else_1;
    int if_1;
    if (!((source_.str[i_] == 'o'))) goto else_3;
    printf("%d\n", i_);
    int call_ = 0;
    if_1 = 0;
    goto end_if_4;
else_3:;
    if_1 = 0;
end_if_4:;
    struct StringIntTuple2 caps_;
    caps_.t0 = source_;
    caps_.t1 = len_;
    int call_1 = go_(caps_, (i_ + 1));
    if_ = 0;
    goto end_if_2;
else_1:;
    if_ = 0;
end_if_2:;
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
