#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

int32_t fun_generic_complicated_fun_generic_complicated_Int32Int32Fun1_mutuallyRecursive2(int32_t b_);

int32_t fun_generic_complicated_fun_generic_complicated_Int32Int32Fun1_mutuallyRecursive1(int32_t a_);

void fun_generic_complicated_fun_generic_complicated_UnitUnitFun1_mutuallyRecursive2(void);

void fun_generic_complicated_fun_generic_complicated_UnitUnitFun1_mutuallyRecursive1(void);

void MiloneCore_Prelude_Int32UnitFun1_ignore(int32_t);

void fun_generic_complicated_fun_generic_complicated_testMutualRecursion(void);

int main(int argc, char **argv);

int32_t fun_generic_complicated_fun_generic_complicated_Int32Int32Fun1_mutuallyRecursive2(int32_t b_) {
    int32_t if_;
    int32_t call_;
    if (false) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    call_ = fun_generic_complicated_fun_generic_complicated_Int32Int32Fun1_mutuallyRecursive1(b_);
    if_ = call_;
    goto if_next_1;
else_3:;
    if_ = b_;
    goto if_next_1;
if_next_1:;
    return if_;
}

int32_t fun_generic_complicated_fun_generic_complicated_Int32Int32Fun1_mutuallyRecursive1(int32_t a_) {
    int32_t call_1;
    call_1 = fun_generic_complicated_fun_generic_complicated_Int32Int32Fun1_mutuallyRecursive2(a_);
    return call_1;
}

void fun_generic_complicated_fun_generic_complicated_UnitUnitFun1_mutuallyRecursive2(void) {
    char if_1;
    if (false) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    fun_generic_complicated_fun_generic_complicated_UnitUnitFun1_mutuallyRecursive1();
    if_1 = 0;
    goto if_next_1;
else_3:;
    if_1 = 0;
    goto if_next_1;
if_next_1:;
    return;
}

void fun_generic_complicated_fun_generic_complicated_UnitUnitFun1_mutuallyRecursive1(void) {
    fun_generic_complicated_fun_generic_complicated_UnitUnitFun1_mutuallyRecursive2();
    return;
}

void fun_generic_complicated_fun_generic_complicated_testMutualRecursion(void) {
    int32_t call_2;
    int32_t call_3;
    fun_generic_complicated_fun_generic_complicated_UnitUnitFun1_mutuallyRecursive1();
    fun_generic_complicated_fun_generic_complicated_UnitUnitFun1_mutuallyRecursive2();
    call_2 = fun_generic_complicated_fun_generic_complicated_Int32Int32Fun1_mutuallyRecursive1(0);
    MiloneCore_Prelude_Int32UnitFun1_ignore(call_2);
    call_3 = fun_generic_complicated_fun_generic_complicated_Int32Int32Fun1_mutuallyRecursive2(0);
    MiloneCore_Prelude_Int32UnitFun1_ignore(call_3);
    return;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    fun_generic_complicated_fun_generic_complicated_testMutualRecursion();
    return 0;
}
