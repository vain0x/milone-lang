#include "milone.h"

char bool_operators_Program_test(bool t_, bool f_);

char bool_operators_Program_testShortCircuit(bool t_1, bool f_1);

int milone_main();

char bool_operators_Program_test(bool t_, bool f_) {
    milone_assert(t_, 6, 2);
    milone_assert((!(f_)), 9, 2);
    milone_assert(t_, 10, 2);
    bool if_;
    if (t_) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    if_ = t_;
    goto if_next_1;
else_3:;
    if_ = false;
    goto if_next_1;
if_next_1:;
    milone_assert(if_, 13, 2);
    bool if_1;
    if (t_) {
        goto then_5;
    } else {
        goto else_6;
    }
then_5:;
    if_1 = f_;
    goto if_next_4;
else_6:;
    if_1 = false;
    goto if_next_4;
if_next_4:;
    milone_assert((!(if_1)), 14, 2);
    bool if_2;
    if (f_) {
        goto then_8;
    } else {
        goto else_9;
    }
then_8:;
    if_2 = t_;
    goto if_next_7;
else_9:;
    if_2 = false;
    goto if_next_7;
if_next_7:;
    milone_assert((!(if_2)), 15, 2);
    bool if_3;
    if (f_) {
        goto then_11;
    } else {
        goto else_12;
    }
then_11:;
    if_3 = f_;
    goto if_next_10;
else_12:;
    if_3 = false;
    goto if_next_10;
if_next_10:;
    milone_assert((!(if_3)), 16, 2);
    bool if_4;
    if (t_) {
        goto then_14;
    } else {
        goto else_15;
    }
then_14:;
    if_4 = true;
    goto if_next_13;
else_15:;
    if_4 = t_;
    goto if_next_13;
if_next_13:;
    milone_assert(if_4, 19, 2);
    bool if_5;
    if (t_) {
        goto then_17;
    } else {
        goto else_18;
    }
then_17:;
    if_5 = true;
    goto if_next_16;
else_18:;
    if_5 = f_;
    goto if_next_16;
if_next_16:;
    milone_assert(if_5, 20, 2);
    bool if_6;
    if (f_) {
        goto then_20;
    } else {
        goto else_21;
    }
then_20:;
    if_6 = true;
    goto if_next_19;
else_21:;
    if_6 = t_;
    goto if_next_19;
if_next_19:;
    milone_assert(if_6, 21, 2);
    bool if_7;
    if (f_) {
        goto then_23;
    } else {
        goto else_24;
    }
then_23:;
    if_7 = true;
    goto if_next_22;
else_24:;
    if_7 = f_;
    goto if_next_22;
if_next_22:;
    milone_assert((!(if_7)), 22, 2);
    milone_assert(true, 25, 2);
    milone_assert(true, 26, 2);
    milone_assert((false < true), 28, 2);
    milone_assert((true >= false), 29, 2);
    milone_assert((true >= true), 30, 2);
    milone_assert((false < true), 32, 2);
    return 0;
}

char bool_operators_Program_testShortCircuit(bool t_1, bool f_1) {
    bool if_8;
    if (f_1) {
        goto then_26;
    } else {
        goto else_27;
    }
then_26:;
    exit(1);
else_27:;
    if_8 = false;
    goto if_next_25;
if_next_25:;
    milone_assert((!(if_8)), 44, 2);
    bool if_9;
    if (t_1) {
        goto then_29;
    } else {
        goto else_30;
    }
then_29:;
    if_9 = true;
    goto if_next_28;
else_30:;
    exit(1);
if_next_28:;
    milone_assert(if_9, 50, 2);
    return 0;
}

int milone_main() {
    char call_ = bool_operators_Program_test(true, false);
    char call_1 = bool_operators_Program_testShortCircuit(true, false);
    return 0;
}
