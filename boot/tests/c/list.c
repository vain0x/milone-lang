struct List_1 {
    int head;
    struct List_1* tail;
};

int main() {
    struct List_1* list_7 = (struct List_1*)malloc(sizeof(struct List_1));
    list_7->head = 3;
    list_7->tail = NULL;
    struct List_1* list_6 = (struct List_1*)malloc(sizeof(struct List_1));
    list_6->head = 2;
    list_6->tail = list_7;
    struct List_1* list_5 = (struct List_1*)malloc(sizeof(struct List_1));
    list_5->head = 1;
    list_5->tail = list_6;
    struct List_1* xs_2 = list_5;
    struct List_1* list_10 = (struct List_1*)malloc(sizeof(struct List_1));
    list_10->head = 3;
    list_10->tail = NULL;
    struct List_1* list_9 = (struct List_1*)malloc(sizeof(struct List_1));
    list_9->head = 2;
    list_9->tail = list_10;
    struct List_1* list_8 = (struct List_1*)malloc(sizeof(struct List_1));
    list_8->head = 1;
    list_8->tail = list_9;
    struct List_1* ys_3 = list_8;
    return 0;
}
