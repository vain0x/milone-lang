int abs_(int x_);

struct IntList;

int main();

int abs_(int x_) {
    int if_;
    if (!((0 <= x_))) goto else_1;
    if_ = x_;
    goto end_if_2;
else_1:;
    if_ = (0 - x_);
end_if_2:;
    return if_;
}

struct IntList {
    int head;
    struct IntList* tail;
};

int main() {
    int match_;
    struct IntList* list_1 = (struct IntList*)malloc(sizeof(struct IntList));
    list_1->head = 2;
    list_1->tail = NULL;
    struct IntList* list_ = (struct IntList*)malloc(sizeof(struct IntList));
    list_->head = 1;
    list_->tail = list_1;
    if (!((!((!(list_)))))) goto next_4;
    int x1_ = list_->head;
    if (!((!((!(list_->tail)))))) goto next_4;
    int x2_ = list_->tail->head;
    if (!((!(list_->tail->tail)))) goto next_4;
    int call_ = abs_((x1_ - 1));
    int call_1 = abs_((x2_ - 2));
    match_ = (call_ + call_1);
    goto end_match_3;
next_4:;
    exit(1);
    match_ = 0;
    goto end_match_3;
next_5:;
end_match_3:;
    return match_;
}
