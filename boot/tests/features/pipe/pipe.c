int inc_(int x_);

int twice_(int x_1);

int sub_(int x_2, int y_);

int between_(int l_, int r_, int x_3);

struct IntList;

int len_(struct IntList* xs_);

int main();

int inc_(int x_) {
    return (x_ + 1);
}

int twice_(int x_1) {
    return (x_1 * x_1);
}

int sub_(int x_2, int y_) {
    return (x_2 - y_);
}

int between_(int l_, int r_, int x_3) {
    int match_;
    if (!(((l_ <= x_3) == 1))) goto next_2;
    match_ = (x_3 < r_);
    goto end_match_1;
next_2:;
    if (!(((l_ <= x_3) == 0))) goto next_3;
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    return match_;
}

struct IntList {
    int head;
    struct IntList* tail;
};

int len_(struct IntList* xs_) {
    int match_1;
    if (!((!(xs_)))) goto next_5;
    match_1 = 0;
    goto end_match_4;
next_5:;
    match_1 = 1;
    goto end_match_4;
next_6:;
end_match_4:;
    return match_1;
}

int main() {
    int call_ = inc_(1);
    int call_1 = twice_(call_);
    int call_2 = twice_(call_1);
    int n_ = call_2;
    int match_2;
    if (!(((n_ != 16) == 1))) goto next_8;
    exit(1);
    match_2 = 0;
    goto end_match_7;
next_8:;
    if (!(((n_ != 16) == 0))) goto next_9;
    match_2 = 0;
    goto end_match_7;
next_9:;
end_match_7:;
    int match_3;
    int call_3 = sub_(100, 98);
    int call_4 = between_(2, 3, call_3);
    if (!(((!(call_4)) == 1))) goto next_11;
    exit(2);
    match_3 = 0;
    goto end_match_10;
next_11:;
    if (!(((!(call_4)) == 0))) goto next_12;
    match_3 = 0;
    goto end_match_10;
next_12:;
end_match_10:;
    int match_4;
    struct IntList* list_ = (struct IntList*)malloc(sizeof(struct IntList));
    list_->head = 1;
    list_->tail = NULL;
    int call_5 = len_(list_);
    if (!(((call_5 == 0) == 1))) goto next_14;
    exit(1);
    match_4 = 0;
    goto end_match_13;
next_14:;
    if (!(((call_5 == 0) == 0))) goto next_15;
    match_4 = 0;
    goto end_match_13;
next_15:;
end_match_13:;
    return 0;
}
