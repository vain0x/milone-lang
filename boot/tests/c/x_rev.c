struct List_1 {
    int head;
    struct List_1* tail;
};

struct List_1* go_3(struct List_1* acc_5, struct List_1* xs_4) {
    struct List_1* match_15;
    if (!(!(xs_4))) goto next_2;
    match_15 = acc_5;
    goto end_match_1;
next_2:;
    if (!(!(!(xs_4)))) goto next_3;
    int x_6 = xs_4->head;
    struct List_1* xs_7 = xs_4->tail;
    struct List_1* list_16 = (struct List_1*)malloc(sizeof(struct List_1));
    list_16->head = x_6;
    list_16->tail = acc_5;
    struct List_1* call_17 = go_3(list_16, xs_7);
    match_15 = call_17;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return match_15;
}

struct List_1* rev_1(struct List_1* xs_2) {
    struct List_1* call_18 = go_3(NULL, xs_2);
    return call_18;
}

int printList_8(struct List_1* xs_9) {
    int match_19;
    if (!(!(xs_9))) goto next_5;
    match_19 = 0;
    goto end_match_4;
next_5:;
    if (!(!(!(xs_9)))) goto next_6;
    int x_10 = xs_9->head;
    struct List_1* xs_11 = xs_9->tail;
    printf("%d\n", x_10);
    int call_20 = 0;
    int call_21 = printList_8(xs_11);
    match_19 = 0;
    goto end_match_4;
next_6:;
    exit(1);
end_match_4:;
    return 0;
}

int main() {
    struct List_1* list_24 = (struct List_1*)malloc(sizeof(struct List_1));
    list_24->head = 2;
    list_24->tail = NULL;
    struct List_1* list_23 = (struct List_1*)malloc(sizeof(struct List_1));
    list_23->head = 1;
    list_23->tail = list_24;
    struct List_1* list_22 = (struct List_1*)malloc(sizeof(struct List_1));
    list_22->head = 0;
    list_22->tail = list_23;
    struct List_1* xs_14 = list_22;
    printf("xs:\n");
    int call_25 = 0;
    int call_26 = printList_8(xs_14);
    printf("rev xs:\n");
    int call_27 = 0;
    struct List_1* call_28 = rev_1(xs_14);
    int call_29 = printList_8(call_28);
    return 0;
}
