#include <milone.h>

void bool_operators_bool_operators_test(bool t_, bool f_);

void bool_operators_bool_operators_testShortCircuit(bool t_1, bool f_1);

int main(int argc, char** argv);

void bool_operators_bool_operators_test(bool t_, bool f_) {
    bool if_;
    bool if_1;
    bool if_2;
    bool if_3;
    bool if_4;
    bool if_5;
    bool if_6;
    bool if_7;
    struct String call_;
    struct String call_1;
    milone_assert(t_, (struct String){.str = "bool_operators/bool_operators.milone", .len = 36}, 6, 2);
    milone_assert((!(f_)), (struct String){.str = "bool_operators/bool_operators.milone", .len = 36}, 9, 2);
    milone_assert(t_, (struct String){.str = "bool_operators/bool_operators.milone", .len = 36}, 10, 2);
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
    milone_assert(if_, (struct String){.str = "bool_operators/bool_operators.milone", .len = 36}, 13, 2);
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
    milone_assert((!(if_1)), (struct String){.str = "bool_operators/bool_operators.milone", .len = 36}, 14, 2);
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
    milone_assert((!(if_2)), (struct String){.str = "bool_operators/bool_operators.milone", .len = 36}, 15, 2);
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
    milone_assert((!(if_3)), (struct String){.str = "bool_operators/bool_operators.milone", .len = 36}, 16, 2);
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
    milone_assert(if_4, (struct String){.str = "bool_operators/bool_operators.milone", .len = 36}, 19, 2);
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
    milone_assert(if_5, (struct String){.str = "bool_operators/bool_operators.milone", .len = 36}, 20, 2);
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
    milone_assert(if_6, (struct String){.str = "bool_operators/bool_operators.milone", .len = 36}, 21, 2);
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
    milone_assert((!(if_7)), (struct String){.str = "bool_operators/bool_operators.milone", .len = 36}, 22, 2);
    milone_assert(true, (struct String){.str = "bool_operators/bool_operators.milone", .len = 36}, 25, 2);
    milone_assert(true, (struct String){.str = "bool_operators/bool_operators.milone", .len = 36}, 26, 2);
    milone_assert((false < true), (struct String){.str = "bool_operators/bool_operators.milone", .len = 36}, 28, 2);
    milone_assert((true >= false), (struct String){.str = "bool_operators/bool_operators.milone", .len = 36}, 29, 2);
    milone_assert((true >= true), (struct String){.str = "bool_operators/bool_operators.milone", .len = 36}, 30, 2);
    milone_assert((false < true), (struct String){.str = "bool_operators/bool_operators.milone", .len = 36}, 32, 2);
    call_ = str_of_bool(t_);
    milone_assert((str_compare(call_, (struct String){.str = "True", .len = 4}) == 0), (struct String){.str = "bool_operators/bool_operators.milone", .len = 36}, 38, 2);
    call_1 = str_of_bool(f_);
    milone_assert((str_compare(call_1, (struct String){.str = "False", .len = 5}) == 0), (struct String){.str = "bool_operators/bool_operators.milone", .len = 36}, 39, 2);
    return;
}

void bool_operators_bool_operators_testShortCircuit(bool t_1, bool f_1) {
    bool if_8;
    bool if_9;
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
    milone_assert((!(if_8)), (struct String){.str = "bool_operators/bool_operators.milone", .len = 36}, 42, 2);
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
    milone_assert(if_9, (struct String){.str = "bool_operators/bool_operators.milone", .len = 36}, 48, 2);
    return;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    bool_operators_bool_operators_test(true, false);
    bool_operators_bool_operators_testShortCircuit(true, false);
    return 0;
}
