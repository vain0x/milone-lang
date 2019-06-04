int f_(int x_);

int g_(int x_1);

struct IntList;

int main();

int f_(int x_) {
    return x_;
}

int g_(int x_1) {
    return x_1;
}

struct IntList {
    int head;
    struct IntList* tail;
};

int main() {
    int call_ = f_(1);
    int call_1 = g_(1);
    int zero_ = (call_ - call_1);
    struct IntList* list_ = (struct IntList*)malloc(sizeof(struct IntList));
    list_->head = 1;
    list_->tail = NULL;
    struct IntList* xs_ = list_;
    return zero_;
}
