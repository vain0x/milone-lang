int abs_(int x_);

struct IntList;

int main();

int abs_(int x_) {
    int match_;
    if (!(((0 <= x_) == 1))) goto next_2;
    match_ = x_;
    goto end_match_1;
next_2:;
    if (!(((0 <= x_) == 0))) goto next_3;
    match_ = (0 - x_);
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return match_;
}

struct IntList {
    int head;
    struct IntList* tail;
};

int main() {
    int match_1;
    struct IntList* list_1 = (struct IntList*)malloc(sizeof(struct IntList));
    list_1->head = 2;
    list_1->tail = NULL;
    struct IntList* list_ = (struct IntList*)malloc(sizeof(struct IntList));
    list_->head = 1;
    list_->tail = list_1;
    if (!((!((!(list_)))))) goto next_5;
    int x1_ = list_->head;
    if (!((!((!(list_->tail)))))) goto next_5;
    int x2_ = list_->tail->head;
    if (!((!(list_->tail->tail)))) goto next_5;
    int call_ = abs_((x1_ - 1));
    int call_1 = abs_((x2_ - 2));
    match_1 = (call_ + call_1);
    goto end_match_4;
next_5:;
    exit(1);
    match_1 = 0;
    goto end_match_4;
next_6:;
end_match_4:;
    return match_1;
}
