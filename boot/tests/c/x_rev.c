struct List_1 {
    int head;
    struct List_1* tail;
};

struct Tuple_2 {
    struct List_1* t0;
    struct List_1* t1;
};

struct List_1* go_3(struct Tuple_2 arg_14) {
    struct List_1* acc_4 = arg_14.t0;
    struct List_1* xs_5 = arg_14.t1;
    struct List_1* match_15;
    if (!(!(xs_5))) goto next_2;
    match_15 = acc_4;
    goto end_match_1;
next_2:;
    if (!(!(!(xs_5)))) goto next_3;
    int x_6 = xs_5->head;
    struct List_1* xs_7 = xs_5->tail;
    struct List_1* list_17 = (struct List_1*)malloc(sizeof(struct List_1));
    list_17->head = x_6;
    list_17->tail = acc_4;
    struct Tuple_2 tuple_16;
    tuple_16.t0 = list_17;
    tuple_16.t1 = xs_7;
    struct List_1* call_18 = go_3(tuple_16);
    match_15 = call_18;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return match_15;
}

struct List_1* rev_1(struct List_1* xs_2) {
    struct Tuple_2 tuple_19;
    tuple_19.t0 = NULL;
    tuple_19.t1 = xs_2;
    struct List_1* call_20 = go_3(tuple_19);
    return call_20;
}

int printList_8(struct List_1* xs_9) {
    int match_21;
    if (!(!(xs_9))) goto next_5;
    match_21 = 0;
    goto end_match_4;
next_5:;
    if (!(!(!(xs_9)))) goto next_6;
    int x_10 = xs_9->head;
    struct List_1* xs_11 = xs_9->tail;
    printf("%d\n", x_10);
    int call_22 = 0;
    int call_23 = printList_8(xs_11);
    match_21 = 0;
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
    struct List_1* xs_13 = list_25;
    printf("xs:\n");
    int call_28 = 0;
    int call_29 = printList_8(xs_13);
    printf("rev xs:\n");
    int call_30 = 0;
    struct List_1* call_31 = rev_1(xs_13);
    int call_32 = printList_8(call_31);
    return 0;
}
