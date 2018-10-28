struct List_1 {
    int head;
    struct List_1* tail;
};

int main() {
    int match_5;
    struct List_1* list_6 = (struct List_1*)malloc(sizeof(struct List_1));
    list_6->head = 1;
    list_6->tail = NULL;
    if (!(!(!(list_6)))) goto next_2;
    int x1_2 = list_6->head;
    if (!(!(list_6->tail))) goto next_2;
    match_5 = (x1_2 - 1);
    goto end_match_1;
next_2:;
    exit(1);
    match_5 = 0;
    goto end_match_1;
end_match_1:;
    return match_5;
}
