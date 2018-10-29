struct List_1 {
    int head;
    struct List_1* tail;
};

struct Tuple_2 {
    struct List_1* t0;
    struct List_1* t1;
};

struct List_1* go_3(struct Tuple_2 arg_15) {
    struct List_1* acc_4 = arg_15.t0;
    struct List_1* xs_5 = arg_15.t1;
    struct List_1* match_16;
    if (!(!(xs_5))) goto next_2;
    match_16 = acc_4;
    goto end_match_1;
next_2:;
    if (!(!(!(xs_5)))) goto next_3;
    int x_6 = xs_5->head;
    struct List_1* xs_7 = xs_5->tail;
    struct List_1* list_18 = (struct List_1*)malloc(sizeof(struct List_1));
    list_18->head = x_6;
    list_18->tail = acc_4;
    struct Tuple_2 tuple_17;
    tuple_17.t0 = list_18;
    tuple_17.t1 = xs_7;
    struct List_1* call_19 = go_3(tuple_17);
    match_16 = call_19;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return match_16;
}

struct List_1* rev_1(struct List_1* xs_2) {
    struct Tuple_2 tuple_20;
    tuple_20.t0 = NULL;
    tuple_20.t1 = xs_2;
    struct List_1* call_21 = go_3(tuple_20);
    return call_21;
}

int printList_8(struct List_1* xs_9) {
    int match_22;
    if (!(!(xs_9))) goto next_5;
    match_22 = 0;
    goto end_match_4;
next_5:;
    if (!(!(!(xs_9)))) goto next_6;
    int x_10 = xs_9->head;
    struct List_1* xs_11 = xs_9->tail;
    printf("%d\n", x_10);
    int call_23 = 0;
    int call_24 = printList_8(xs_11);
    match_22 = 0;
    goto end_match_4;
next_6:;
    exit(1);
end_match_4:;
    return 0;
}

int main() {
    struct List_1* list_27 = (struct List_1*)malloc(sizeof(struct List_1));
    list_27->head = 2;
    list_27->tail = NULL;
    struct List_1* list_26 = (struct List_1*)malloc(sizeof(struct List_1));
    list_26->head = 1;
    list_26->tail = list_27;
    struct List_1* list_25 = (struct List_1*)malloc(sizeof(struct List_1));
    list_25->head = 0;
    list_25->tail = list_26;
    struct List_1* xs_14 = list_25;
    printf("xs:\n");
    int call_28 = 0;
    int call_29 = printList_8(xs_14);
    printf("rev xs:\n");
    int call_30 = 0;
    struct List_1* call_31 = rev_1(xs_14);
    int call_32 = printList_8(call_31);
    return 0;
}
