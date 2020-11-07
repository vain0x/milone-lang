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
    struct StringIntTuple2 _john_ = tuple_;
    struct StringIntTuple2 tuple_1;
    tuple_1.t0 = (struct String){.str = "Jane Doe", .len = 8};
    tuple_1.t1 = 18;
    struct StringIntTuple2 _jane_ = tuple_1;
    return 0;
}
