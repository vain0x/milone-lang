#include "milone.h"

struct ObjectList;

struct IntObjectListTuple2;

void* myCons_(int head_, void* tail_);

int main();

struct ObjectList {
    void* head;
    struct ObjectList* tail;
};

struct IntObjectListTuple2 {
    int t0;
    struct ObjectList* t1;
};

void* myCons_(int head_, void* tail_) {
    struct ObjectList* some_ = (struct ObjectList*)milone_mem_alloc(1, sizeof(struct ObjectList));
    some_->head = tail_;
    some_->tail = NULL;
    struct IntObjectListTuple2 tuple_;
    tuple_.t0 = head_;
    tuple_.t1 = some_;
    void* box_ = (void*)milone_mem_alloc(1, sizeof(struct IntObjectListTuple2));
    (*(((struct IntObjectListTuple2*)box_))) = tuple_;
    return box_;
}

int main() {
    struct IntObjectListTuple2 tuple_1;
    tuple_1.t0 = 0;
    tuple_1.t1 = NULL;
    void* box_1 = (void*)milone_mem_alloc(1, sizeof(struct IntObjectListTuple2));
    (*(((struct IntObjectListTuple2*)box_1))) = tuple_1;
    void* first_ = box_1;
    void* call_ = myCons_(1, first_);
    void* second_ = call_;
    int match_;
    if (((*(((struct IntObjectListTuple2*)first_))).t0 != 0)) goto next_2;
    if ((!((!((*(((struct IntObjectListTuple2*)first_))).t1))))) goto next_2;
    match_ = 0;
    goto end_match_1;
next_2:;
    milone_assert(0, 14, 9);
    int call_1 = 0;
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    int match_1;
    if ((!((*(((struct IntObjectListTuple2*)second_))).t1))) goto next_5;
    int value_ = (*(((struct IntObjectListTuple2*)(*(((struct IntObjectListTuple2*)second_))).t1->head))).t0;
    if ((!((!((*(((struct IntObjectListTuple2*)second_))).t1->tail))))) goto next_5;
    milone_assert((value_ == 1), 17, 44);
    int call_2 = 0;
    match_1 = 0;
    goto end_match_4;
next_5:;
    milone_assert(0, 18, 9);
    int call_3 = 0;
    match_1 = 0;
    goto end_match_4;
next_6:;
end_match_4:;
    return 0;
}
