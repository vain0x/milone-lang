struct List_1 {
    int head;
    struct List_1* tail;
};

struct List_1* go_(struct List_1* acc_, struct List_1* xs_1) {
    struct List_1* match_;
    if (!(!(xs_1))) goto next_2;
    match_ = acc_;
    goto end_match_1;
next_2:;
    if (!(!(!(xs_1)))) goto next_3;
    int x_ = xs_1->head;
    struct List_1* xs_2 = xs_1->tail;
    struct List_1* list_ = (struct List_1*)malloc(sizeof(struct List_1));
    list_->head = x_;
    list_->tail = acc_;
    struct List_1* call_ = go_(list_, xs_2);
    match_ = call_;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return match_;
}

struct List_1* rev_(struct List_1* xs_) {
    struct List_1* call_1 = go_(NULL, xs_);
    return call_1;
}

int printList_(struct List_1* xs_3) {
    int match_1;
    if (!(!(xs_3))) goto next_5;
    match_1 = 0;
    goto end_match_4;
next_5:;
    if (!(!(!(xs_3)))) goto next_6;
    int x_1 = xs_3->head;
    struct List_1* xs_4 = xs_3->tail;
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
    struct List_1* list_3 = (struct List_1*)malloc(sizeof(struct List_1));
    list_3->head = 2;
    list_3->tail = NULL;
    struct List_1* list_2 = (struct List_1*)malloc(sizeof(struct List_1));
    list_2->head = 1;
    list_2->tail = list_3;
    struct List_1* list_1 = (struct List_1*)malloc(sizeof(struct List_1));
    list_1->head = 0;
    list_1->tail = list_2;
    struct List_1* xs_5 = list_1;
    printf("xs:\n");
    int call_4 = 0;
    int call_5 = printList_(xs_5);
    printf("rev xs:\n");
    int call_6 = 0;
    struct List_1* call_7 = rev_(xs_5);
    int call_8 = printList_(call_7);
    return 0;
}
