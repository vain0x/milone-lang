#include "milone.h"

int aux_1(int x_, char arg_);

struct String aux_(struct String x_, char arg_1);

int myId_1(int x_);

struct String myId_(struct String x_);

int gooAux_1(int x_1, char arg_2);

struct String gooAux_(struct String x_1, char arg_3);

int goo_1(int x_1);

struct String goo_(struct String x_1);

int milone_main();

int aux_1(int x_, char arg_) {
    return x_;
}

struct String aux_(struct String x_, char arg_1) {
    return x_;
}

int myId_1(int x_) {
    int call_ = aux_1(x_, 0);
    return call_;
}

struct String myId_(struct String x_) {
    struct String call_1 = aux_(x_, 0);
    return call_1;
}

int gooAux_1(int x_1, char arg_2) {
    int call_2 = myId_1(x_1);
    return call_2;
}

struct String gooAux_(struct String x_1, char arg_3) {
    struct String call_3 = myId_(x_1);
    return call_3;
}

int goo_1(int x_1) {
    int call_4 = gooAux_1(x_1, 0);
    return call_4;
}

struct String goo_(struct String x_1) {
    struct String call_5 = gooAux_(x_1, 0);
    return call_5;
}

int milone_main() {
    int call_6 = myId_1(1);
    milone_assert((call_6 == 1), 11, 2);
    struct String call_7 = myId_((struct String){.str = "a", .len = 1});
    milone_assert((str_compare(call_7, (struct String){.str = "a", .len = 1}) == 0), 12, 2);
    int call_8 = goo_1(1);
    milone_assert((call_8 == 1), 20, 2);
    struct String call_9 = goo_((struct String){.str = "a", .len = 1});
    milone_assert((str_compare(call_9, (struct String){.str = "a", .len = 1}) == 0), 21, 2);
    return 0;
}
