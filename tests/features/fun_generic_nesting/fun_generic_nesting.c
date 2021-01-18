#include "milone.h"

int aux_2(int x_, int arg_);

struct String aux_1(struct String x_, int arg_1);

int id_2(int x_);

struct String id_1(struct String x_);

int gooAux_2(int x_1, int arg_2);

struct String gooAux_1(struct String x_1, int arg_3);

int goo_2(int x_1);

struct String goo_1(struct String x_1);

int milone_main();

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

int milone_main() {
    int call_6 = id_2(1);
    milone_assert((call_6 == 1), 11, 2);
    struct String call_7 = id_1((struct String){.str = "a", .len = 1});
    milone_assert((str_compare(call_7, (struct String){.str = "a", .len = 1}) == 0), 12, 2);
    int call_8 = goo_2(1);
    milone_assert((call_8 == 1), 20, 2);
    struct String call_9 = goo_1((struct String){.str = "a", .len = 1});
    milone_assert((str_compare(call_9, (struct String){.str = "a", .len = 1}) == 0), 21, 2);
    return 0;
}
