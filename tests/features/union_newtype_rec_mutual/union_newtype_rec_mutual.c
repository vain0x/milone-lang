#include "milone.h"

struct ObjectList;

struct IntObjectListTuple2;

struct StringObjectListTuple2;

int main();

struct ObjectList {
    void* head;
    struct ObjectList* tail;
};

struct IntObjectListTuple2 {
    int t0;
    struct ObjectList* t1;
};

struct StringObjectListTuple2 {
    struct String t0;
    struct ObjectList* t1;
};

int main() {
    struct IntObjectListTuple2 tuple_;
    tuple_.t0 = 1;
    tuple_.t1 = NULL;
    void* box_ = (void*)milone_mem_alloc(1, sizeof(struct IntObjectListTuple2));
    (*(((struct IntObjectListTuple2*)box_))) = tuple_;
    void* one_ = box_;
    struct ObjectList* some_ = (struct ObjectList*)milone_mem_alloc(1, sizeof(struct ObjectList));
    some_->head = one_;
    some_->tail = NULL;
    struct StringObjectListTuple2 tuple_1;
    tuple_1.t0 = (struct String){.str = "two", .len = 3};
    tuple_1.t1 = some_;
    void* box_1 = (void*)milone_mem_alloc(1, sizeof(struct StringObjectListTuple2));
    (*(((struct StringObjectListTuple2*)box_1))) = tuple_1;
    void* two_ = box_1;
    struct ObjectList* some_1 = (struct ObjectList*)milone_mem_alloc(1, sizeof(struct ObjectList));
    some_1->head = two_;
    some_1->tail = NULL;
    struct IntObjectListTuple2 tuple_2;
    tuple_2.t0 = 3;
    tuple_2.t1 = some_1;
    void* box_2 = (void*)milone_mem_alloc(1, sizeof(struct IntObjectListTuple2));
    (*(((struct IntObjectListTuple2*)box_2))) = tuple_2;
    void* three_ = box_2;
    struct ObjectList* some_2 = (struct ObjectList*)milone_mem_alloc(1, sizeof(struct ObjectList));
    some_2->head = three_;
    some_2->tail = NULL;
    struct StringObjectListTuple2 tuple_3;
    tuple_3.t0 = (struct String){.str = "four", .len = 4};
    tuple_3.t1 = some_2;
    void* box_3 = (void*)milone_mem_alloc(1, sizeof(struct StringObjectListTuple2));
    (*(((struct StringObjectListTuple2*)box_3))) = tuple_3;
    void* four_ = box_3;
    int match_;
    struct String s4_ = (*(((struct StringObjectListTuple2*)four_))).t0;
    if ((!((*(((struct StringObjectListTuple2*)four_))).t1))) goto next_2;
    int n3_ = (*(((struct IntObjectListTuple2*)(*(((struct StringObjectListTuple2*)four_))).t1->head))).t0;
    if ((!((*(((struct IntObjectListTuple2*)(*(((struct StringObjectListTuple2*)four_))).t1->head))).t1))) goto next_2;
    struct String s2_ = (*(((struct StringObjectListTuple2*)(*(((struct IntObjectListTuple2*)(*(((struct StringObjectListTuple2*)four_))).t1->head))).t1->head))).t0;
    if ((!((*(((struct StringObjectListTuple2*)(*(((struct IntObjectListTuple2*)(*(((struct StringObjectListTuple2*)four_))).t1->head))).t1->head))).t1))) goto next_2;
    int n1_ = (*(((struct IntObjectListTuple2*)(*(((struct StringObjectListTuple2*)(*(((struct IntObjectListTuple2*)(*(((struct StringObjectListTuple2*)four_))).t1->head))).t1->head))).t1->head))).t0;
    if ((!((!((*(((struct IntObjectListTuple2*)(*(((struct StringObjectListTuple2*)(*(((struct IntObjectListTuple2*)(*(((struct StringObjectListTuple2*)four_))).t1->head))).t1->head))).t1->head))).t1))))) goto next_2;
    if ((!((!((*(((struct StringObjectListTuple2*)(*(((struct IntObjectListTuple2*)(*(((struct StringObjectListTuple2*)four_))).t1->head))).t1->head))).t1->tail))))) goto next_2;
    if ((!((!((*(((struct IntObjectListTuple2*)(*(((struct StringObjectListTuple2*)four_))).t1->head))).t1->tail))))) goto next_2;
    if ((!((!((*(((struct StringObjectListTuple2*)four_))).t1->tail))))) goto next_2;
    milone_assert((n1_ == 1), 15, 6);
    int call_ = 0;
    milone_assert((str_cmp(s2_, (struct String){.str = "two", .len = 3}) == 0), 16, 6);
    int call_1 = 0;
    milone_assert((n3_ == 3), 17, 6);
    int call_2 = 0;
    milone_assert((str_cmp(s4_, (struct String){.str = "four", .len = 4}) == 0), 18, 6);
    int call_3 = 0;
    match_ = 0;
    goto end_match_1;
next_2:;
    milone_assert(0, 20, 9);
    int call_4 = 0;
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    return 0;
}
