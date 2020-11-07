#include "milone.h"

struct IntIntIntTuple3;

struct StringIntIntIntIntTuple3Tuple3;

struct StringIntIntIntIntTuple3Tuple3 newPerson_(int arg_);

struct StringIntObjectTuple3;

int main();

struct IntIntIntTuple3 {
    int t0;
    int t1;
    int t2;
};

struct StringIntIntIntIntTuple3Tuple3 {
    struct String t0;
    int t1;
    struct IntIntIntTuple3 t2;
};

struct StringIntIntIntIntTuple3Tuple3 newPerson_(int arg_) {
    struct IntIntIntTuple3 tuple_1;
    tuple_1.t0 = 2007;
    tuple_1.t1 = 8;
    tuple_1.t2 = 31;
    struct StringIntIntIntIntTuple3Tuple3 tuple_;
    tuple_.t0 = (struct String){.str = "Jane Doe", .len = 8};
    tuple_.t1 = 16;
    tuple_.t2 = tuple_1;
    return tuple_;
}

struct StringIntObjectTuple3 {
    struct String t0;
    int t1;
    void* t2;
};

int main() {
    struct StringIntObjectTuple3 call_ = newPerson_(0);
    struct StringIntObjectTuple3 base_ = call_;
    struct StringIntObjectTuple3 tuple_2;
    tuple_2.t0 = (struct String){.str = "John Doe", .len = 8};
    tuple_2.t1 = base_.t1;
    tuple_2.t2 = base_.t2;
    struct StringIntObjectTuple3 john_ = tuple_2;
    struct String name_ = john_.t0;
    milone_assert((name_.len == 8), 21, 2);
    int call_1 = 0;
    return 0;
}
