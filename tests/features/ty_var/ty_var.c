#include "milone.h"

struct IntIntTuple2;

int pair_2(struct IntIntTuple2 arg_);

struct StringStringTuple2;

int pair_1(struct StringStringTuple2 arg_1);

char useStringIndexWithoutAnnotation_(struct String x_);

int main();

struct IntIntTuple2 {
    int t0;
    int t1;
};

int pair_2(struct IntIntTuple2 arg_) {
    return 2;
}

struct StringStringTuple2 {
    struct String t0;
    struct String t1;
};

int pair_1(struct StringStringTuple2 arg_1) {
    return 2;
}

char useStringIndexWithoutAnnotation_(struct String x_) {
    struct StringStringTuple2 tuple_;
    tuple_.t0 = x_;
    tuple_.t1 = (struct String){.str = "", .len = 0};
    int call_ = pair_1(tuple_);
    return x_.str[0];
}

int main() {
    struct IntIntTuple2 tuple_1;
    tuple_1.t0 = 0;
    tuple_1.t1 = 0;
    int call_1 = pair_2(tuple_1);
    milone_assert((call_1 == 2), 14, 2);
    struct StringStringTuple2 tuple_2;
    tuple_2.t0 = (struct String){.str = "", .len = 0};
    tuple_2.t1 = (struct String){.str = "", .len = 0};
    int call_2 = pair_1(tuple_2);
    milone_assert((call_2 == 2), 15, 2);
    char call_3 = useStringIndexWithoutAnnotation_((struct String){.str = "a", .len = 1});
    milone_assert((call_3 == 'a'), 17, 2);
    return 0;
}
