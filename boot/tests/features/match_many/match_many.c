struct IntList {
    int head;
    struct IntList* tail;
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
    if (!(!(!(list_)))) goto next_4;
    if (!(!(!(list_->tail)))) goto next_4;
    if (!(!(list_->tail->tail))) goto next_4;
    exit(1);
    match_1 = 0;
    goto end_match_3;
next_4:;
    if (!(!(!(list_)))) goto next_5;
    if (!(!(list_->tail))) goto next_5;
    match_1 = 0;
    goto end_match_3;
next_5:;
    if (!(!(list_))) goto next_6;
    exit(1);
    match_1 = 0;
    goto end_match_3;
next_6:;
    exit(1);
end_match_3:;
    return 0;
}
