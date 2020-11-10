#include "milone.h"

int f_(int x_);

int g_(int x_1);

struct IntList;

struct StringList;

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

struct StringList {
    struct String head;
    struct StringList* tail;
};

int main() {
    int call_ = f_(1);
    int call_1 = g_(1);
    int zero_ = (call_ - call_1);
    struct IntList* list_ = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_->head = 1;
    list_->tail = NULL;
    struct IntList* xs_ = list_;
    struct StringList* list_1 = (struct StringList*)milone_mem_alloc(1, sizeof(struct StringList));
    list_1->head = (struct String){.str = "a", .len = 1};
    list_1->tail = NULL;
    struct StringList* ys_ = list_1;
    return zero_;
}
