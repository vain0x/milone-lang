#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

typedef int32_t(*VoidConstPtrInt32Int32FunPtr2)(void const *, int32_t);

struct Int32Int32Fun1;

_Noreturn void MiloneCore_Prelude_exit(int32_t);

_Noreturn void resolved_issues_resolved_issues_testFunArityNeverResultBug_unreachable(void);

int32_t MiloneCore_Prelude_Int32Int32Fun1_id(int32_t);

int32_t resolved_issues_resolved_issues_eta2_testFunArityNeverResultBug_id(void const *env_, int32_t arg_);

void resolved_issues_resolved_issues_testFunArityNeverResultBug(void);

int main(int argc, char **argv);

struct Int32Int32Fun1 {
    VoidConstPtrInt32Int32FunPtr2 fun;
    void const *env;
};

_Noreturn void resolved_issues_resolved_issues_testFunArityNeverResultBug_unreachable(void) {
    MiloneCore_Prelude_exit(1);
    milone_never_error("resolved_issues/resolved_issues.milone", 15, 2);
}

int32_t resolved_issues_resolved_issues_eta2_testFunArityNeverResultBug_id(void const *env_, int32_t arg_) {
    int32_t call_;
    call_ = MiloneCore_Prelude_Int32Int32Fun1_id(arg_);
    return call_;
}

void resolved_issues_resolved_issues_testFunArityNeverResultBug(void) {
    struct Int32Int32Fun1 f_;
    struct Int32Int32Fun1 switch_;
    struct Int32Int32Fun1 fun_;
    int32_t app_;
    switch (1) {
        case 1:
            goto clause_2;

        default:
            goto clause_3;
    }
clause_2:;
    fun_ = (struct Int32Int32Fun1){.fun = resolved_issues_resolved_issues_eta2_testFunArityNeverResultBug_id, .env = NULL};
    switch_ = fun_;
    goto switch_next_1;
clause_3:;
    resolved_issues_resolved_issues_testFunArityNeverResultBug_unreachable();
    milone_never_error("resolved_issues/resolved_issues.milone", 19, 22);
switch_next_1:;
    f_ = switch_;
    app_ = f_.fun(f_.env, 1);
    if ((app_ != 1)) milone_assert_error("resolved_issues/resolved_issues.milone", 22, 2);
    return;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    resolved_issues_resolved_issues_testFunArityNeverResultBug();
    return 0;
}
