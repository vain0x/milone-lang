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
    void* _john_ = box_;
    struct StringIntTuple2 tuple_1;
    tuple_1.t0 = (struct String){.str = "Jane Doe", .len = 8};
    tuple_1.t1 = 18;
    void* box_1 = (void*)milone_mem_alloc(1, sizeof(struct StringIntTuple2));
    (*(((struct StringIntTuple2*)box_1))) = tuple_1;
    void* _jane_ = box_1;
    return 0;
}
