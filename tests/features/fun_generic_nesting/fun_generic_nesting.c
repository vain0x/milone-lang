#include "milone.h"

struct String goo_(struct String x_1);

int goo_1(int x_1);

struct String myId_(struct String x_);

int myId_1(int x_);

int aux_(int x_);

struct String aux_1(struct String x_);

int gooAux_(int x_1);

struct String gooAux_1(struct String x_1);

int milone_main(void);

struct String goo_(struct String x_1) {
    struct String call_ = gooAux_1(x_1);
    return call_;
}

int goo_1(int x_1) {
    int call_1 = gooAux_(x_1);
    return call_1;
}

struct String myId_(struct String x_) {
    struct String call_2 = aux_1(x_);
    return call_2;
}

int myId_1(int x_) {
    int call_3 = aux_(x_);
    return call_3;
}

int aux_(int x_) {
    return x_;
}

struct String aux_1(struct String x_) {
    return x_;
}

int gooAux_(int x_1) {
    int call_4 = myId_1(x_1);
    return call_4;
}

struct String gooAux_1(struct String x_1) {
    struct String call_5 = myId_(x_1);
    return call_5;
}

int milone_main(void) {
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
