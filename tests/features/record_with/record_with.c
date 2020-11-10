#include "milone.h"

struct StringIntTuple2;

int main();

struct StringIntTuple2 {
    struct String t0;
    int t1;
};

int main() {
    struct StringIntTuple2 tuple_;
    tuple_.t0 = (struct String){.str = "John Doe", .len = 8};
    tuple_.t1 = 16;
    void* box_ = (void*)milone_mem_alloc(1, sizeof(struct StringIntTuple2));
    (*(((struct StringIntTuple2*)box_))) = tuple_;
    void* john_ = box_;
    void* base_ = john_;
    struct StringIntTuple2 tuple_1;
    tuple_1.t0 = (struct String){.str = "Jane Doe", .len = 8};
    tuple_1.t1 = (*(((struct StringIntTuple2*)base_))).t1;
    void* box_1 = (void*)milone_mem_alloc(1, sizeof(struct StringIntTuple2));
    (*(((struct StringIntTuple2*)box_1))) = tuple_1;
    void* jane_ = box_1;
    milone_assert((str_cmp((*(((struct StringIntTuple2*)john_))).t0, (struct String){.str = "John Doe", .len = 8}) == 0), 8, 2);
    int call_ = 0;
    milone_assert((str_cmp((*(((struct StringIntTuple2*)jane_))).t0, (struct String){.str = "Jane Doe", .len = 8}) == 0), 9, 2);
    int call_1 = 0;
    milone_assert(((*(((struct StringIntTuple2*)jane_))).t1 == 16), 10, 2);
    int call_2 = 0;
    void* base_1 = john_;
    struct StringIntTuple2 tuple_2;
    tuple_2.t0 = (*(((struct StringIntTuple2*)base_1))).t0;
    tuple_2.t1 = ((*(((struct StringIntTuple2*)john_))).t1 + 1);
    void* box_2 = (void*)milone_mem_alloc(1, sizeof(struct StringIntTuple2));
    (*(((struct StringIntTuple2*)box_2))) = tuple_2;
    void* john_1 = box_2;
    milone_assert(((*(((struct StringIntTuple2*)john_1))).t1 == 17), 13, 2);
    int call_3 = 0;
    return 0;
}
