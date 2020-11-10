#include "milone.h"

struct IntList;

int isEmpty_1(struct IntList* xs_1);

int assertNotEmpty_1(struct IntList* xs_);

int main();

struct IntList {
    int head;
    struct IntList* tail;
};

int isEmpty_1(struct IntList* xs_1) {
    int match_;
    if ((!((!(xs_1))))) goto next_2;
    match_ = 1;
    goto end_match_1;
next_2:;
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    return match_;
}

int assertNotEmpty_1(struct IntList* xs_) {
    int call_ = isEmpty_1(xs_);
    milone_assert((!(call_)), 4, 34);
    int call_1 = 0;
    return 0;
}

int main() {
    struct IntList* list_ = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_->head = 1;
    list_->tail = NULL;
    int call_2 = assertNotEmpty_1(list_);
    return 0;
}
