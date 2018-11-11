struct List_1 {
    int head;
    struct List_1* tail;
};

int main() {
    int match_;
    struct List_1* list_ = (struct List_1*)malloc(sizeof(struct List_1));
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
