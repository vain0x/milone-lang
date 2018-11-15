struct IntList {
    int head;
    struct IntList* tail;
};

struct IntList* go_(struct IntList* acc_, struct IntList* xs_1) {
    struct IntList* match_;
    if (!((!(xs_1)))) goto next_2;
    match_ = acc_;
    goto end_match_1;
next_2:;
    if (!((!((!(xs_1)))))) goto next_3;
    int x_ = xs_1->head;
    struct IntList* xs_2 = xs_1->tail;
    struct IntList* list_ = (struct IntList*)malloc(sizeof(struct IntList));
    list_->head = x_;
    list_->tail = acc_;
    struct IntList* call_ = go_(list_, xs_2);
    match_ = call_;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return match_;
}

struct IntList* rev_(struct IntList* xs_) {
    struct IntList* call_1 = go_(NULL, xs_);
    return call_1;
}

int printList_(struct IntList* xs_3) {
    int match_1;
    if (!((!(xs_3)))) goto next_5;
    match_1 = 0;
    goto end_match_4;
next_5:;
    if (!((!((!(xs_3)))))) goto next_6;
    int x_1 = xs_3->head;
    struct IntList* xs_4 = xs_3->tail;
    printf("%d\n", x_1);
    int call_2 = 0;
    int call_3 = printList_(xs_4);
    match_1 = 0;
    goto end_match_4;
next_6:;
    exit(1);
end_match_4:;
    return 0;
}

int main() {
    struct IntList* list_3 = (struct IntList*)malloc(sizeof(struct IntList));
    list_3->head = 2;
    list_3->tail = NULL;
    struct IntList* list_2 = (struct IntList*)malloc(sizeof(struct IntList));
    list_2->head = 1;
    list_2->tail = list_3;
    struct IntList* list_1 = (struct IntList*)malloc(sizeof(struct IntList));
    list_1->head = 0;
    list_1->tail = list_2;
    struct IntList* xs_5 = list_1;
    printf("xs:\n");
    int call_4 = 0;
    int call_5 = printList_(xs_5);
    printf("rev xs:\n");
    int call_6 = 0;
    struct IntList* call_7 = rev_(xs_5);
    int call_8 = printList_(call_7);
    return 0;
}
