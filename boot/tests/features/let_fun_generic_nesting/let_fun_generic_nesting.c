#include "milone.h"

struct IntTuple1;

int aux_2(struct IntTuple1 arg_, int arg_1);

struct StringTuple1;

struct String aux_1(struct StringTuple1 arg_2, int arg_3);

int id_2(int x_);

struct String id_1(struct String x_);

int gooAux_2(struct IntTuple1 arg_4, int arg_5);

struct String gooAux_1(struct StringTuple1 arg_6, int arg_7);

int goo_2(int x_1);

struct String goo_1(struct String x_1);

int main();

struct IntTuple1 {
    int t0;
};

int aux_2(struct IntTuple1 arg_, int arg_1) {
    int x_ = arg_.t0;
    return x_;
}

struct StringTuple1 {
    struct String t0;
};

struct String aux_1(struct StringTuple1 arg_2, int arg_3) {
    struct String x_ = arg_2.t0;
    return x_;
}

int id_2(int x_) {
    struct IntTuple1 tuple_;
    tuple_.t0 = x_;
    int call_ = aux_2(tuple_, 0);
    return call_;
}

struct String id_1(struct String x_) {
    struct StringTuple1 tuple_1;
    tuple_1.t0 = x_;
    struct String call_1 = aux_1(tuple_1, 0);
    return call_1;
}

int gooAux_2(struct IntTuple1 arg_4, int arg_5) {
    int x_1 = arg_4.t0;
    int call_2 = id_2(x_1);
    return call_2;
}

struct String gooAux_1(struct StringTuple1 arg_6, int arg_7) {
    struct String x_1 = arg_6.t0;
    struct String call_3 = id_1(x_1);
    return call_3;
}

int goo_2(int x_1) {
    struct IntTuple1 tuple_2;
    tuple_2.t0 = x_1;
    int call_4 = gooAux_2(tuple_2, 0);
    return call_4;
}

struct String goo_1(struct String x_1) {
    struct StringTuple1 tuple_3;
    tuple_3.t0 = x_1;
    struct String call_5 = gooAux_1(tuple_3, 0);
    return call_5;
}

int main() {
    int call_6 = id_2(1);
    milone_assert((call_6 == 1));
    int call_7 = 0;
    struct String call_8 = id_1((struct String){.str = "a", .len = 1});
    milone_assert((str_cmp(call_8, (struct String){.str = "a", .len = 1}) == 0));
    int call_9 = 0;
    int call_10 = goo_2(1);
    milone_assert((call_10 == 1));
    int call_11 = 0;
    struct String call_12 = goo_1((struct String){.str = "a", .len = 1});
    milone_assert((str_cmp(call_12, (struct String){.str = "a", .len = 1}) == 0));
    int call_13 = 0;
    return 0;
}
