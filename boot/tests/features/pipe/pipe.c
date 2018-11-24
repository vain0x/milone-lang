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
    int if_;
    if (!((l_ <= x_3))) goto else_1;
    if_ = (x_3 < r_);
    goto end_if_2;
else_1:;
    if_ = 0;
end_if_2:;
    return if_;
}

struct IntList {
    int head;
    struct IntList* tail;
};

int len_(struct IntList* xs_) {
    int match_;
    if (!((!(xs_)))) goto next_8;
    match_ = 0;
    goto end_match_7;
next_8:;
    match_ = 1;
    goto end_match_7;
next_9:;
end_match_7:;
    return match_;
}

int main() {
    int call_ = inc_(1);
    int call_1 = twice_(call_);
    int call_2 = twice_(call_1);
    int n_ = call_2;
    int if_1;
    if (!((n_ != 16))) goto else_3;
    exit(1);
    if_1 = 0;
    goto end_if_4;
else_3:;
    if_1 = 0;
end_if_4:;
    int if_2;
    int call_3 = sub_(100, 98);
    int call_4 = between_(2, 3, call_3);
    if (!((!(call_4)))) goto else_5;
    exit(2);
    if_2 = 0;
    goto end_if_6;
else_5:;
    if_2 = 0;
end_if_6:;
    int if_3;
    struct IntList* list_ = (struct IntList*)malloc(sizeof(struct IntList));
    list_->head = 1;
    list_->tail = NULL;
    int call_5 = len_(list_);
    if (!((call_5 == 0))) goto else_10;
    exit(1);
    if_3 = 0;
    goto end_if_11;
else_10:;
    if_3 = 0;
end_if_11:;
    return 0;
}
