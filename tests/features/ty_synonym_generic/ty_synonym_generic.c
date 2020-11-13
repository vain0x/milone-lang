#include "milone.h"

struct IntList;

struct IntList* newStack_(int arg_);

int main();

struct IntList {
    int head;
    struct IntList* tail;
};

struct IntList* newStack_(int arg_) {
    return NULL;
}

int main() {
    struct IntList* call_ = newStack_(0);
    struct IntList* list_ = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_->head = 1;
    list_->tail = call_;
    struct IntList* _stack_ = list_;
    return 0;
}
