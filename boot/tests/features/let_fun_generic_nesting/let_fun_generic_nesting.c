#include "milone.h"

int aux_2(int x_, int arg_);

struct String aux_1(struct String x_, int arg_1);

int id_2(int x_);

struct String id_1(struct String x_);

int gooAux_2(int x_1, int arg_2);

struct String gooAux_1(struct String x_1, int arg_3);

int goo_2(int x_1);

struct String goo_1(struct String x_1);

int main();

int aux_2(int x_, int arg_) {
    return x_;
}

struct String aux_1(struct String x_, int arg_1) {
    return x_;
}

int id_2(int x_) {
    int call_ = aux_2(x_, 0);
    return call_;
}

struct String id_1(struct String x_) {
    struct String call_1 = aux_1(x_, 0);
    return call_1;
}

int gooAux_2(int x_1, int arg_2) {
    int call_2 = id_2(x_1);
    return call_2;
}

struct String gooAux_1(struct String x_1, int arg_3) {
    struct String call_3 = id_1(x_1);
    return call_3;
}

int goo_2(int x_1) {
    int call_4 = gooAux_2(x_1, 0);
    return call_4;
}

struct String goo_1(struct String x_1) {
    struct String call_5 = gooAux_1(x_1, 0);
    return call_5;
}

int main() {
    int call_6 = id_2(1);
    milone_assert((call_6 == 1), 6, 2);
    int call_7 = 0;
    struct String call_8 = id_1((struct String){.str = "a", .len = 1});
    milone_assert((str_cmp(call_8, (struct String){.str = "a", .len = 1}) == 0), 7, 2);
    int call_9 = 0;
    int call_10 = goo_2(1);
    milone_assert((call_10 == 1), 14, 2);
    int call_11 = 0;
    struct String call_12 = goo_1((struct String){.str = "a", .len = 1});
    milone_assert((str_cmp(call_12, (struct String){.str = "a", .len = 1}) == 0), 15, 2);
    int call_13 = 0;
    return 0;
}
