#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

typedef int32_t(*VoidConstPtrInt32Int32FunPtr2)(void const *, int32_t);

struct Int32Int32Fun1;

typedef void(*VoidConstPtrVoidFunPtr1)(void const *);

struct UnitNeverFun1;

int32_t MiloneCore_Prelude_Int32Int32Fun1_id(int32_t);

int32_t never_ty_never_ty_eta2__id(void const *env_, int32_t arg_);

void never_ty_never_ty_opaqueStmt(void);

void never_ty_never_ty_graceful(void);

void never_ty_never_ty_crash(void);

void never_ty_never_ty_testLetInit(void);

void MiloneCore_Prelude_Int32UnitFun1_ignore(int32_t);

void never_ty_never_ty_testMatchArm(void);

void never_ty_never_ty_eta2_testFunObj_crash(void const *env_1);

void MiloneCore_Prelude_NeverUnitFun1_ignore(char);

void never_ty_never_ty_testFunObj(void);

void never_ty_never_ty_testOwn(void);

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
    exit(0);
clause_3:;
    switch_ = 0;
    goto switch_next_1;
switch_next_1:;
    return;
}

void never_ty_never_ty_crash(void) {
    never_ty_never_ty_opaqueStmt();
    exit(1);
}

void never_ty_never_ty_testLetInit(void) {
    never_ty_never_ty_crash();
    exit(1);
}

void never_ty_never_ty_testMatchArm(void) {
    int32_t switch_1;
    int32_t app_1;
    app_1 = blackBox_.fun(blackBox_.env, 0);
    switch (app_1) {
        case 0:
            goto clause_5;

        default:
            goto clause_6;
    }
clause_5:;
    never_ty_never_ty_crash();
    exit(1);
clause_6:;
    switch_1 = 1;
    goto switch_next_4;
switch_next_4:;
    MiloneCore_Prelude_Int32UnitFun1_ignore((switch_1 + 1));
    return;
}

void never_ty_never_ty_eta2_testFunObj_crash(void const *env_1) {
    never_ty_never_ty_crash();
    return;
}

void never_ty_never_ty_testFunObj(void) {
    struct UnitNeverFun1 crashFn_;
    struct UnitNeverFun1 fun_;
    fun_ = (struct UnitNeverFun1){.fun = never_ty_never_ty_eta2_testFunObj_crash, .env = NULL};
    crashFn_ = fun_;
    crashFn_.fun(crashFn_.env);
    MiloneCore_Prelude_NeverUnitFun1_ignore(0);
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
            goto clause_8;

        default:
            goto clause_9;
    }
clause_8:;
    never_ty_never_ty_crash();
    exit(1);
clause_9:;
    switch_2 = 0;
    goto switch_next_7;
switch_next_7:;
    resource_1 = 0;
    return;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    never_ty_never_ty_start();
    never_ty_never_ty_graceful();
    never_ty_never_ty_testLetInit();
    never_ty_never_ty_testMatchArm();
    never_ty_never_ty_testFunObj();
    never_ty_never_ty_testOwn();
    never_ty_never_ty_crash();
    exit(1);
}

void never_ty_never_ty_start(void) {
    struct Int32Int32Fun1 fun_1;
    fun_1 = (struct Int32Int32Fun1){.fun = never_ty_never_ty_eta2__id, .env = NULL};
    blackBox_ = fun_1;
    return;
}
