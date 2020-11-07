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
    struct StringIntTuple2 john_ = tuple_;
    struct StringIntTuple2 base_ = john_;
    struct StringIntTuple2 tuple_1;
    tuple_1.t0 = (struct String){.str = "Jane Doe", .len = 8};
    tuple_1.t1 = base_.t1;
    struct StringIntTuple2 jane_ = tuple_1;
    milone_assert((str_cmp(john_.t0, (struct String){.str = "John Doe", .len = 8}) == 0), 8, 2);
    int call_ = 0;
    milone_assert((str_cmp(jane_.t0, (struct String){.str = "Jane Doe", .len = 8}) == 0), 9, 2);
    int call_1 = 0;
    milone_assert((jane_.t1 == 16), 10, 2);
    int call_2 = 0;
    struct StringIntTuple2 base_1 = john_;
    struct StringIntTuple2 tuple_2;
    tuple_2.t0 = base_1.t0;
    tuple_2.t1 = (john_.t1 + 1);
    struct StringIntTuple2 john_1 = tuple_2;
    milone_assert((john_1.t1 == 17), 13, 2);
    int call_3 = 0;
    return 0;
}
