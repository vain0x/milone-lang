struct IntList;

int main();

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
    if (!((!((!(list_)))))) goto next_2;
    int x1_ = list_->head;
    if (!((!((!(list_->tail)))))) goto next_2;
    int x2_ = list_->tail->head;
    if (!((!(list_->tail->tail)))) goto next_2;
    int match_1;
    if (!(((x1_ == 1) == 1))) goto next_5;
    match_1 = (x2_ == 2);
    goto end_match_4;
next_5:;
    if (!(((x1_ == 1) == 0))) goto next_6;
    match_1 = 0;
    goto end_match_4;
next_6:;
    exit(1);
end_match_4:;
    milone_assert(match_1);
    int call_ = 0;
    match_ = 0;
    goto end_match_1;
next_2:;
    exit(1);
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    return 0;
}
