struct IntList;

int main();

struct IntList {
    int head;
    struct IntList* tail;
};

int main() {
    int success_ = 0;
    int failure_ = 1;
    struct IntList* list_1 = (struct IntList*)malloc(sizeof(struct IntList));
    list_1->head = failure_;
    list_1->tail = NULL;
    struct IntList* list_ = (struct IntList*)malloc(sizeof(struct IntList));
    list_->head = success_;
    list_->tail = list_1;
    struct IntList* codes_ = list_;
    return success_;
}
