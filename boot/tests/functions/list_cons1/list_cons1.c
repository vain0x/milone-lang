struct IntList {
    int head;
    struct IntList* tail;
};

int main() {
    int match_;
    struct IntList* list_ = (struct IntList*)malloc(sizeof(struct IntList));
    list_->head = 1;
    list_->tail = NULL;
    if (!(!(!(list_)))) goto next_2;
    int x1_ = list_->head;
    if (!(!(list_->tail))) goto next_2;
    match_ = (x1_ - 1);
    goto end_match_1;
next_2:;
    exit(1);
    match_ = 0;
    goto end_match_1;
end_match_1:;
    return match_;
}
