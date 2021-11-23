#include <milone.h>

struct String fun_generic_nesting_fun_generic_nesting_main_StringStringFun1_goo(struct String x_1);

int fun_generic_nesting_fun_generic_nesting_main_IntIntFun1_goo(int x_1);

struct String fun_generic_nesting_fun_generic_nesting_main_StringStringFun1_myId(struct String x_);

int fun_generic_nesting_fun_generic_nesting_main_IntIntFun1_myId(int x_);

int fun_generic_nesting_fun_generic_nesting_main_myId_IntUnitIntFun2_aux(int x_);

struct String fun_generic_nesting_fun_generic_nesting_main_myId_StringUnitStringFun2_aux(struct String x_);

int fun_generic_nesting_fun_generic_nesting_main_goo_IntUnitIntFun2_gooAux(int x_1);

struct String fun_generic_nesting_fun_generic_nesting_main_goo_StringUnitStringFun2_gooAux(struct String x_1);

int main(int argc, char** argv);

struct String fun_generic_nesting_fun_generic_nesting_main_StringStringFun1_goo(struct String x_1) {
    struct String call_ = fun_generic_nesting_fun_generic_nesting_main_goo_StringUnitStringFun2_gooAux(x_1);
    return call_;
}

int fun_generic_nesting_fun_generic_nesting_main_IntIntFun1_goo(int x_1) {
    int call_1 = fun_generic_nesting_fun_generic_nesting_main_goo_IntUnitIntFun2_gooAux(x_1);
    return call_1;
}

struct String fun_generic_nesting_fun_generic_nesting_main_StringStringFun1_myId(struct String x_) {
    struct String call_2 = fun_generic_nesting_fun_generic_nesting_main_myId_StringUnitStringFun2_aux(x_);
    return call_2;
}

int fun_generic_nesting_fun_generic_nesting_main_IntIntFun1_myId(int x_) {
    int call_3 = fun_generic_nesting_fun_generic_nesting_main_myId_IntUnitIntFun2_aux(x_);
    return call_3;
}

int fun_generic_nesting_fun_generic_nesting_main_myId_IntUnitIntFun2_aux(int x_) {
    return x_;
}

struct String fun_generic_nesting_fun_generic_nesting_main_myId_StringUnitStringFun2_aux(struct String x_) {
    return x_;
}

int fun_generic_nesting_fun_generic_nesting_main_goo_IntUnitIntFun2_gooAux(int x_1) {
    int call_4 = fun_generic_nesting_fun_generic_nesting_main_IntIntFun1_myId(x_1);
    return call_4;
}

struct String fun_generic_nesting_fun_generic_nesting_main_goo_StringUnitStringFun2_gooAux(struct String x_1) {
    struct String call_5 = fun_generic_nesting_fun_generic_nesting_main_StringStringFun1_myId(x_1);
    return call_5;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    int call_6 = fun_generic_nesting_fun_generic_nesting_main_IntIntFun1_myId(1);
    milone_assert((call_6 == 1), (struct String){.str = "fun_generic_nesting/fun_generic_nesting.milone", .len = 46}, 11, 2);
    struct String call_7 = fun_generic_nesting_fun_generic_nesting_main_StringStringFun1_myId((struct String){.str = "a", .len = 1});
    milone_assert((str_compare(call_7, (struct String){.str = "a", .len = 1}) == 0), (struct String){.str = "fun_generic_nesting/fun_generic_nesting.milone", .len = 46}, 12, 2);
    int call_8 = fun_generic_nesting_fun_generic_nesting_main_IntIntFun1_goo(1);
    milone_assert((call_8 == 1), (struct String){.str = "fun_generic_nesting/fun_generic_nesting.milone", .len = 46}, 20, 2);
    struct String call_9 = fun_generic_nesting_fun_generic_nesting_main_StringStringFun1_goo((struct String){.str = "a", .len = 1});
    milone_assert((str_compare(call_9, (struct String){.str = "a", .len = 1}) == 0), (struct String){.str = "fun_generic_nesting/fun_generic_nesting.milone", .len = 46}, 21, 2);
    return 0;
}
