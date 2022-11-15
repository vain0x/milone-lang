#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

typedef int32_t(*VoidConstPtrInt32Int32FunPtr2)(void const *, int32_t);

struct Int32Int32Fun1;

_Noreturn void fun_arity_never_result_bug_fun_arity_never_result_bug_UnitNeverFun1_unreachable(void);

int32_t MiloneCore_Prelude_Int32Int32Fun1_id(int32_t);

int32_t fun_arity_never_result_bug_fun_arity_never_result_bug_eta2_main_id(void const *env_, int32_t arg_);

int main(int argc, char **argv);

struct Int32Int32Fun1 {
    VoidConstPtrInt32Int32FunPtr2 fun;
    void const *env;
};

_Noreturn void fun_arity_never_result_bug_fun_arity_never_result_bug_UnitNeverFun1_unreachable(void) {
    printf("NEVER\n");
    if (true) milone_assert_error("fun_arity_never_result_bug/fun_arity_never_result_bug.milone", 7, 2);
    fun_arity_never_result_bug_fun_arity_never_result_bug_UnitNeverFun1_unreachable();
    milone_never_error("fun_arity_never_result_bug/fun_arity_never_result_bug.milone", 5, 0);
}

int32_t fun_arity_never_result_bug_fun_arity_never_result_bug_eta2_main_id(void const *env_, int32_t arg_) {
    int32_t call_;
    call_ = MiloneCore_Prelude_Int32Int32Fun1_id(arg_);
    return call_;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
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
    fun_ = (struct Int32Int32Fun1){.fun = fun_arity_never_result_bug_fun_arity_never_result_bug_eta2_main_id, .env = NULL};
    switch_ = fun_;
    goto switch_next_1;
clause_3:;
    fun_arity_never_result_bug_fun_arity_never_result_bug_UnitNeverFun1_unreachable();
    milone_never_error("fun_arity_never_result_bug/fun_arity_never_result_bug.milone", 14, 22);
switch_next_1:;
    f_ = switch_;
    app_ = f_.fun(f_.env, 2);
    if ((app_ != 2)) milone_assert_error("fun_arity_never_result_bug/fun_arity_never_result_bug.milone", 16, 2);
    return 0;
}
