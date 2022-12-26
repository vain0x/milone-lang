#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

void bool_operators_bool_operators_test(bool t_, bool f_);

_Noreturn void MiloneCore_Prelude_exit(int32_t);

void bool_operators_bool_operators_testShortCircuit(bool t_1, bool f_1);

int main(int argc, char **argv);

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
    if ((!(t_))) milone_assert_error("bool_operators/bool_operators.milone", 6, 2);
    if (f_) milone_assert_error("bool_operators/bool_operators.milone", 9, 2);
    if ((!(t_))) milone_assert_error("bool_operators/bool_operators.milone", 10, 2);
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
    if ((!(if_))) milone_assert_error("bool_operators/bool_operators.milone", 13, 2);
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
    if (if_1) milone_assert_error("bool_operators/bool_operators.milone", 14, 2);
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
    if (if_2) milone_assert_error("bool_operators/bool_operators.milone", 15, 2);
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
    if (if_3) milone_assert_error("bool_operators/bool_operators.milone", 16, 2);
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
    if ((!(if_4))) milone_assert_error("bool_operators/bool_operators.milone", 19, 2);
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
    if ((!(if_5))) milone_assert_error("bool_operators/bool_operators.milone", 20, 2);
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
    if ((!(if_6))) milone_assert_error("bool_operators/bool_operators.milone", 21, 2);
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
    if (if_7) milone_assert_error("bool_operators/bool_operators.milone", 22, 2);
    if (false) milone_assert_error("bool_operators/bool_operators.milone", 25, 2);
    if (false) milone_assert_error("bool_operators/bool_operators.milone", 26, 2);
    if ((false >= true)) milone_assert_error("bool_operators/bool_operators.milone", 28, 2);
    if ((true < false)) milone_assert_error("bool_operators/bool_operators.milone", 29, 2);
    if ((true < true)) milone_assert_error("bool_operators/bool_operators.milone", 30, 2);
    if ((false >= true)) milone_assert_error("bool_operators/bool_operators.milone", 32, 2);
    call_ = string_of_bool(t_);
    if ((string_compare(call_, (struct String){.ptr = "True", .len = 4}) != 0)) milone_assert_error("bool_operators/bool_operators.milone", 38, 2);
    call_1 = string_of_bool(f_);
    if ((string_compare(call_1, (struct String){.ptr = "False", .len = 5}) != 0)) milone_assert_error("bool_operators/bool_operators.milone", 39, 2);
    return;
}

void bool_operators_bool_operators_testShortCircuit(bool t_1, bool f_1) {
    bool if_8;
    bool if_9;
    if (f_1) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    MiloneCore_Prelude_exit(1);
    milone_never_error("bool_operators/bool_operators.milone", 44, 12);
else_3:;
    if_8 = false;
    goto if_next_1;
if_next_1:;
    if (if_8) milone_assert_error("bool_operators/bool_operators.milone", 42, 2);
    if (t_1) {
        goto then_5;
    } else {
        goto else_6;
    }
then_5:;
    if_9 = true;
    goto if_next_4;
else_6:;
    MiloneCore_Prelude_exit(1);
    milone_never_error("bool_operators/bool_operators.milone", 49, 18);
if_next_4:;
    if ((!(if_9))) milone_assert_error("bool_operators/bool_operators.milone", 48, 2);
    return;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    bool_operators_bool_operators_test(true, false);
    bool_operators_bool_operators_testShortCircuit(true, false);
    return 0;
}
