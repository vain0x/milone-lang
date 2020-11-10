#include "milone.h"

struct IntIntIntTuple3;

struct StringIntObjectTuple3;

void* newPerson_(int arg_);

int main();

struct IntIntIntTuple3 {
    int t0;
    int t1;
    int t2;
};

struct StringIntObjectTuple3 {
    struct String t0;
    int t1;
    void* t2;
};

void* newPerson_(int arg_) {
    struct IntIntIntTuple3 tuple_1;
    tuple_1.t0 = 2007;
    tuple_1.t1 = 8;
    tuple_1.t2 = 31;
    void* box_ = (void*)milone_mem_alloc(1, sizeof(struct IntIntIntTuple3));
    (*(((struct IntIntIntTuple3*)box_))) = tuple_1;
    struct StringIntObjectTuple3 tuple_;
    tuple_.t0 = (struct String){.str = "Jane Doe", .len = 8};
    tuple_.t1 = 16;
    tuple_.t2 = box_;
    void* box_1 = (void*)milone_mem_alloc(1, sizeof(struct StringIntObjectTuple3));
    (*(((struct StringIntObjectTuple3*)box_1))) = tuple_;
    return box_1;
}

int main() {
    void* call_ = newPerson_(0);
    void* base_ = call_;
    struct StringIntObjectTuple3 tuple_2;
    tuple_2.t0 = (struct String){.str = "John Doe", .len = 8};
    tuple_2.t1 = (*(((struct StringIntObjectTuple3*)base_))).t1;
    tuple_2.t2 = (*(((struct StringIntObjectTuple3*)base_))).t2;
    void* box_2 = (void*)milone_mem_alloc(1, sizeof(struct StringIntObjectTuple3));
    (*(((struct StringIntObjectTuple3*)box_2))) = tuple_2;
    void* john_ = box_2;
    struct String name_ = (*(((struct StringIntObjectTuple3*)john_))).t0;
    milone_assert((name_.len == 8), 19, 2);
    int call_1 = 0;
    return 0;
}
