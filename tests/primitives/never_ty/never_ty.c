#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

typedef int32_t(*VoidConstPtrInt32Int32FunPtr2)(void const *, int32_t);

struct Int32Int32Fun1;

typedef void(*VoidConstPtrVoidFunPtr1)(void const *);

struct UnitNeverFun1;

struct Neveroption1_;

struct Int32NeverResult2_;

int32_t MiloneCore_Prelude_Int32Int32Fun1_id(int32_t);

int32_t never_ty_never_ty_eta2__id(void const *env_, int32_t arg_);

void never_ty_never_ty_opaqueStmt(void);

_Noreturn void MiloneCore_Prelude_exit(int32_t);

void never_ty_never_ty_graceful(void);

_Noreturn void never_ty_never_ty_crash(void);

void never_ty_never_ty_testStmt(void);

void never_ty_never_ty_testLetInit(void);

void MiloneCore_Prelude_Int32UnitFun1_ignore(int32_t);

void never_ty_never_ty_testMatchArm(void);

_Noreturn void never_ty_never_ty_eta2_testFunObj_crash(void const *env_1);

void never_ty_never_ty_testFunObj_callFnObj(struct UnitNeverFun1 crashFn_);

void MiloneCore_Prelude_UnitUnitFun1_ignore(void);

void never_ty_never_ty_testFunObj(void);

void never_ty_never_ty_testOwn(void);

_Noreturn void never_ty_never_ty_testInfiniteLoop_diverge(void);

void never_ty_never_ty_testInfiniteLoop(void);

void never_ty_never_ty_testNeverAsValue(void);

int main(int argc, char **argv);

void never_ty_never_ty_start(void);

struct Int32Int32Fun1 {
    VoidConstPtrInt32Int32FunPtr2 fun;
    void const *env;
};

struct UnitNeverFun1 {
    VoidConstPtrVoidFunPtr1 fun;
    void const *env;
};

enum Neveroption1_Discriminant {
    Neveroption1_None,
    Neveroption1_Some,
};

struct Neveroption1_ {
    enum Neveroption1_Discriminant discriminant;
    union {
        char Neveroption1_Some;
    };
};

enum Int32NeverResult2_Discriminant {
    Int32NeverResult2_Error,
    Int32NeverResult2_Ok,
};

struct Int32NeverResult2_ {
    enum Int32NeverResult2_Discriminant discriminant;
    union {
        char Int32NeverResult2_Error;
        int32_t Int32NeverResult2_Ok;
    };
};

struct Int32Int32Fun1 blackBox_;

int32_t never_ty_never_ty_eta2__id(void const *env_, int32_t arg_) {
    int32_t call_;
    call_ = MiloneCore_Prelude_Int32Int32Fun1_id(arg_);
    return call_;
}

void never_ty_never_ty_opaqueStmt(void) {
    return;
}

void never_ty_never_ty_graceful(void) {
    char switch_;
    int32_t app_;
    app_ = blackBox_.fun(blackBox_.env, 0);
    switch (app_) {
        case 0:
            goto clause_2;

        default:
            goto clause_3;
    }
clause_2:;
    MiloneCore_Prelude_exit(0);
    milone_never_error("never_ty/never_ty.milone", 9, 13);
clause_3:;
    switch_ = 0;
    goto switch_next_1;
switch_next_1:;
    return;
}

_Noreturn void never_ty_never_ty_crash(void) {
    never_ty_never_ty_opaqueStmt();
    MiloneCore_Prelude_exit(1);
    milone_never_error("never_ty/never_ty.milone", 15, 6);
}

void never_ty_never_ty_testStmt(void) {
    never_ty_never_ty_crash();
    milone_never_error("never_ty/never_ty.milone", 19, 7);
}

void never_ty_never_ty_testLetInit(void) {
    never_ty_never_ty_crash();
    milone_never_error("never_ty/never_ty.milone", 24, 26);
}

void never_ty_never_ty_testMatchArm(void) {
    int32_t switch_1;
    int32_t app_1;
    app_1 = blackBox_.fun(blackBox_.env, 0);
    switch (app_1) {
        case 0:
            goto clause_2;

        default:
            goto clause_3;
    }
clause_2:;
    never_ty_never_ty_crash();
    milone_never_error("never_ty/never_ty.milone", 30, 16);
clause_3:;
    switch_1 = 1;
    goto switch_next_1;
switch_next_1:;
    MiloneCore_Prelude_Int32UnitFun1_ignore((switch_1 + 1));
    return;
}

_Noreturn void never_ty_never_ty_eta2_testFunObj_crash(void const *env_1) {
    never_ty_never_ty_crash();
}

void never_ty_never_ty_testFunObj_callFnObj(struct UnitNeverFun1 crashFn_) {
    crashFn_.fun(crashFn_.env);
    milone_never_error("never_ty/never_ty.milone", 38, 28);
}

void never_ty_never_ty_testFunObj(void) {
    struct UnitNeverFun1 crashFn_;
    struct UnitNeverFun1 fun_;
    fun_ = (struct UnitNeverFun1){.fun = never_ty_never_ty_eta2_testFunObj_crash, .env = NULL};
    crashFn_ = fun_;
    never_ty_never_ty_testFunObj_callFnObj(crashFn_);
    MiloneCore_Prelude_UnitUnitFun1_ignore();
    return;
}

void never_ty_never_ty_testOwn(void) {
    char resource_;
    char resource_1;
    char switch_2;
    int32_t app_2;
    resource_ = 0;
    app_2 = blackBox_.fun(blackBox_.env, 1);
    switch (app_2) {
        case 1:
            goto clause_2;

        default:
            goto clause_3;
    }
clause_2:;
    never_ty_never_ty_crash();
    milone_never_error("never_ty/never_ty.milone", 49, 11);
clause_3:;
    switch_2 = 0;
    goto switch_next_1;
switch_next_1:;
    resource_1 = 0;
    return;
}

_Noreturn void never_ty_never_ty_testInfiniteLoop_diverge(void) {
    never_ty_never_ty_testInfiniteLoop_diverge();
    milone_never_error("never_ty/never_ty.milone", 57, 2);
}

void never_ty_never_ty_testInfiniteLoop(void) {
    return;
}

void never_ty_never_ty_testNeverAsValue(void) {
    struct Neveroption1_ opt_;
    char n_;
    struct Int32NeverResult2_ ok_;
    int32_t it_;
    char n_1;
    int32_t value_;
    char match_;
    struct Int32NeverResult2_ variant_;
    int32_t match_1;
    opt_ = (struct Neveroption1_){.discriminant = Neveroption1_None};
    if ((opt_.discriminant != Neveroption1_Some)) goto next_2;
    n_ = opt_.Neveroption1_Some;
    milone_never_error("never_ty/never_ty.milone", 65, 15);
next_2:;
    if ((opt_.discriminant != Neveroption1_None)) goto next_3;
    never_ty_never_ty_crash();
    milone_never_error("never_ty/never_ty.milone", 66, 18);
next_3:;
    milone_exhaust_error("never_ty/never_ty.milone", 64, 3);
end_match_1:;
    variant_ = (struct Int32NeverResult2_){.discriminant = Int32NeverResult2_Ok, .Int32NeverResult2_Ok = 0};
    ok_ = variant_;
    if ((ok_.discriminant != Int32NeverResult2_Ok)) goto next_5;
    it_ = ok_.Int32NeverResult2_Ok;
    match_1 = it_;
    goto end_match_4;
next_5:;
    if ((ok_.discriminant != Int32NeverResult2_Error)) goto next_6;
    n_1 = ok_.Int32NeverResult2_Error;
    milone_never_error("never_ty/never_ty.milone", 73, 17);
next_6:;
    milone_exhaust_error("never_ty/never_ty.milone", 71, 4);
end_match_4:;
    value_ = match_1;
    if ((value_ != 0)) milone_assert_error("never_ty/never_ty.milone", 75, 2);
    return;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    never_ty_never_ty_start();
    never_ty_never_ty_graceful();
    never_ty_never_ty_testStmt();
    never_ty_never_ty_testLetInit();
    never_ty_never_ty_testMatchArm();
    never_ty_never_ty_testFunObj();
    never_ty_never_ty_testOwn();
    never_ty_never_ty_testInfiniteLoop();
    never_ty_never_ty_testNeverAsValue();
    never_ty_never_ty_crash();
    milone_never_error("never_ty/never_ty.milone", 90, 7);
}

void never_ty_never_ty_start(void) {
    struct Int32Int32Fun1 fun_1;
    fun_1 = (struct Int32Int32Fun1){.fun = never_ty_never_ty_eta2__id, .env = NULL};
    blackBox_ = fun_1;
    return;
}
