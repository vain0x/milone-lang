#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

typedef int32_t(*VoidConstPtrInt32FunPtr1)(void const *);

struct UnitInt32Fun1;

typedef int32_t(*VoidConstPtrInt32Int32FunPtr2)(void const *, int32_t);

struct Int32Int32Fun1;

int32_t fun_arity_never_result_bug_fun_arity_never_result_bug_UnitInt32Fun1_unreachable(void);

struct UnitInt32Fun1 fun_arity_never_result_bug_fun_arity_never_result_bug_StringUnitInt32Fun2_failwithf(struct String msg_);

int32_t MiloneCore_Prelude_Int32Int32Fun1_id(int32_t);

int32_t fun_arity_never_result_bug_fun_arity_never_result_bug_eta2_main_id(void const *env_, int32_t arg_);

int32_t fun_arity_never_result_bug_fun_arity_never_result_bug_main_fun(int32_t arg_2);

int32_t fun_arity_never_result_bug_fun_arity_never_result_bug_eta2_main_fun(void const *env_1, int32_t arg_1);

int main(int argc, char **argv);

struct UnitInt32Fun1 {
    VoidConstPtrInt32FunPtr1 fun;
    void const *env;
};

struct Int32Int32Fun1 {
    VoidConstPtrInt32Int32FunPtr2 fun;
    void const *env;
};

int32_t fun_arity_never_result_bug_fun_arity_never_result_bug_UnitInt32Fun1_unreachable(void) {
    struct UnitInt32Fun1 call_;
    int32_t app_;
    call_ = fun_arity_never_result_bug_fun_arity_never_result_bug_StringUnitInt32Fun2_failwithf((struct String){.ptr = "NEVER: %A", .len = 9});
    app_ = call_.fun(call_.env);
    return app_;
}

struct UnitInt32Fun1 fun_arity_never_result_bug_fun_arity_never_result_bug_StringUnitInt32Fun2_failwithf(struct String msg_) {
    printf("%s\n", string_to_c_str(msg_));
    exit(1);
}

int32_t fun_arity_never_result_bug_fun_arity_never_result_bug_eta2_main_id(void const *env_, int32_t arg_) {
    int32_t call_1;
    call_1 = MiloneCore_Prelude_Int32Int32Fun1_id(arg_);
    return call_1;
}

int32_t fun_arity_never_result_bug_fun_arity_never_result_bug_main_fun(int32_t arg_2) {
    int32_t call_2;
    call_2 = fun_arity_never_result_bug_fun_arity_never_result_bug_UnitInt32Fun1_unreachable();
    return call_2;
}

int32_t fun_arity_never_result_bug_fun_arity_never_result_bug_eta2_main_fun(void const *env_1, int32_t arg_1) {
    int32_t call_3;
    call_3 = fun_arity_never_result_bug_fun_arity_never_result_bug_main_fun(arg_1);
    return call_3;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    struct Int32Int32Fun1 f_;
    struct Int32Int32Fun1 switch_;
    struct Int32Int32Fun1 fun_;
    struct Int32Int32Fun1 fun_1;
    int32_t app_1;
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
    fun_1 = (struct Int32Int32Fun1){.fun = fun_arity_never_result_bug_fun_arity_never_result_bug_eta2_main_fun, .env = NULL};
    switch_ = fun_1;
    goto switch_next_1;
switch_next_1:;
    f_ = switch_;
    app_1 = f_.fun(f_.env, 2);
    if ((app_1 != 2)) milone_assert_error("fun_arity_never_result_bug/fun_arity_never_result_bug.milone", 38, 2);
    return 0;
}
