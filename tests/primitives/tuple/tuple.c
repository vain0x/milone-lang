#include "milone.h"

struct IntStringTuple2;

struct StringIntTuple2;

struct StringStringTuple2;

struct StringStringTuple2StringTuple2;

int main();

struct IntStringTuple2 {
    int t0;
    struct String t1;
};

struct StringIntTuple2 {
    struct String t0;
    int t1;
};

struct StringStringTuple2 {
    struct String t0;
    struct String t1;
};

struct StringStringTuple2StringTuple2 {
    struct StringStringTuple2 t0;
    struct String t1;
};

int main() {
    struct IntStringTuple2 tuple_ = (struct IntStringTuple2){.t0 = 1, .t1 = (struct String){.str = "snd", .len = 3}};
    struct IntStringTuple2 a_ = tuple_;
    int x_ = a_.t0;
    struct String _x_ = a_.t1;
    printf("%d\n", x_);
    struct StringIntTuple2 tuple_1 = (struct StringIntTuple2){.t0 = (struct String){.str = "fst", .len = 3}, .t1 = 2};
    struct StringIntTuple2 b_ = tuple_1;
    struct String y_ = b_.t0;
    int _y_ = b_.t1;
    printf("%s\n", y_.str);
    struct StringStringTuple2 tuple_2 = (struct StringStringTuple2){.t0 = (struct String){.str = "z", .len = 1}, .t1 = (struct String){.str = "w", .len = 1}};
    struct String z_ = tuple_2.t0;
    struct String w_ = tuple_2.t1;
    printf("z=%s\n", z_.str);
    printf("w=%s\n", w_.str);
    struct StringStringTuple2 tuple_4 = (struct StringStringTuple2){.t0 = (struct String){.str = "p", .len = 1}, .t1 = (struct String){.str = "q", .len = 1}};
    struct StringStringTuple2StringTuple2 tuple_3 = (struct StringStringTuple2StringTuple2){.t0 = tuple_4, .t1 = (struct String){.str = "r", .len = 1}};
    struct String p_ = tuple_3.t0.t0;
    struct String q_ = tuple_3.t0.t1;
    struct String r_ = tuple_3.t1;
    printf("p=%s\n", p_.str);
    return 0;
}
