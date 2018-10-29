int abs_3(int x_4) {
    int if_8;
    if (!((0 <= x_4))) goto else_1;
    if_8 = x_4;
    goto end_if_2;
else_1:;
    if_8 = (0 - x_4);
end_if_2:;
    return if_8;
}

struct List_1 {
    int head;
    struct List_1* tail;
};

int main() {
    int match_9;
    struct List_1* list_11 = (struct List_1*)malloc(sizeof(struct List_1));
    list_11->head = 2;
    list_11->tail = NULL;
    struct List_1* list_10 = (struct List_1*)malloc(sizeof(struct List_1));
    list_10->head = 1;
    list_10->tail = list_11;
    if (!(!(!(list_10)))) goto next_4;
    int x1_5 = list_10->head;
    if (!(!(!(list_10->tail)))) goto next_4;
    int x2_6 = list_10->tail->head;
    if (!(!(list_10->tail->tail))) goto next_4;
    int call_12 = abs_3((x1_5 - 1));
    int call_13 = abs_3((x2_6 - 2));
    match_9 = (call_12 + call_13);
    goto end_match_3;
next_4:;
    exit(1);
    match_9 = 0;
    goto end_match_3;
end_match_3:;
    return match_9;
}
