struct IntList {
    int head;
    struct IntList* tail;
};

struct IntIntTuple2 {
    int t0;
    int t1;
};

int main() {
    int match_;
    match_ = 0;
    goto end_match_1;
next_2:;
end_match_1:;
    int match_1;
    struct IntList* list_ = (struct IntList*)malloc(sizeof(struct IntList));
    list_->head = 0;
    list_->tail = NULL;
    if (!((!((!(list_)))))) goto next_4;
    if (!((!((!(list_->tail)))))) goto next_4;
    if (!((!(list_->tail->tail)))) goto next_4;
    exit(1);
    match_1 = 0;
    goto end_match_3;
next_4:;
    if (!((!((!(list_)))))) goto next_5;
    if (!((!(list_->tail)))) goto next_5;
    match_1 = 0;
    goto end_match_3;
next_5:;
    if (!((!(list_)))) goto next_6;
    exit(1);
    match_1 = 0;
    goto end_match_3;
next_6:;
    exit(1);
end_match_3:;
    int x_ = 2;
    int match_2;
    struct IntIntTuple2 tuple_;
    tuple_.t0 = x_;
    tuple_.t1 = 1;
    if (!((tuple_.t0 == 1))) goto next_8;
    int x_1 = tuple_.t1;
    exit(1);
    match_2 = 0;
    goto end_match_7;
next_8:;
    if (!((tuple_.t0 == 2))) goto next_9;
    int if_;
    if (!((x_ != 2))) goto else_10;
    exit(1);
    if_ = 0;
    goto end_if_11;
else_10:;
    if_ = 0;
end_if_11:;
    match_2 = 0;
    goto end_match_7;
next_9:;
    exit(1);
    match_2 = 0;
    goto end_match_7;
next_12:;
end_match_7:;
    return 0;
}
