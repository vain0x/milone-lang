#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

typedef int(*VoidConstPtrIntFunPtr1)(void const*);

struct UnitIntFun1;

typedef int(*VoidConstPtrIntIntFunPtr2)(void const*, int);

struct IntIntFun1;

int fun_arity_never_result_bug_fun_arity_never_result_bug_UnitIntFun1_unreachable(void);

struct UnitIntFun1 fun_arity_never_result_bug_fun_arity_never_result_bug_StringUnitIntFun2_failwithf(struct String msg_);

int MiloneCore_Prelude_IntIntFun1_id(int );

int fun_arity_never_result_bug_fun_arity_never_result_bug_eta2_main_id(void const* env_, int arg_);

int fun_arity_never_result_bug_fun_arity_never_result_bug_main_fun(int arg_2);

int fun_arity_never_result_bug_fun_arity_never_result_bug_eta2_main_fun(void const* env_1, int arg_1);

int main(int argc, char** argv);

struct UnitIntFun1 {
    VoidConstPtrIntFunPtr1 fun;
    void const* env;
};

struct IntIntFun1 {
    VoidConstPtrIntIntFunPtr2 fun;
    void const* env;
};

int fun_arity_never_result_bug_fun_arity_never_result_bug_UnitIntFun1_unreachable(void) {
    struct UnitIntFun1 call_;
    int app_;
    call_ = fun_arity_never_result_bug_fun_arity_never_result_bug_StringUnitIntFun2_failwithf((struct String){.ptr = "NEVER: %A", .len = 9});
    app_ = call_.fun(call_.env);
    return app_;
}

struct UnitIntFun1 fun_arity_never_result_bug_fun_arity_never_result_bug_StringUnitIntFun2_failwithf(struct String msg_) {
    printf("%s\n", string_to_c_str(msg_));
    exit(1);
}

int fun_arity_never_result_bug_fun_arity_never_result_bug_eta2_main_id(void const* env_, int arg_) {
    int call_1;
    call_1 = MiloneCore_Prelude_IntIntFun1_id(arg_);
    return call_1;
}

int fun_arity_never_result_bug_fun_arity_never_result_bug_main_fun(int arg_2) {
    int call_2;
    call_2 = fun_arity_never_result_bug_fun_arity_never_result_bug_UnitIntFun1_unreachable();
    return call_2;
}

int fun_arity_never_result_bug_fun_arity_never_result_bug_eta2_main_fun(void const* env_1, int arg_1) {
    int call_3;
    call_3 = fun_arity_never_result_bug_fun_arity_never_result_bug_main_fun(arg_1);
    return call_3;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    struct IntIntFun1 f_;
    struct IntIntFun1 switch_;
    struct IntIntFun1 fun_;
    struct IntIntFun1 fun_1;
    int app_1;
    switch (1) {
        case 1:
            goto clause_2;

        default:
            goto clause_3;
    }
clause_2:;
    fun_ = (struct IntIntFun1){.fun = fun_arity_never_result_bug_fun_arity_never_result_bug_eta2_main_id, .env = NULL};
    switch_ = fun_;
    goto switch_next_1;
clause_3:;
    fun_1 = (struct IntIntFun1){.fun = fun_arity_never_result_bug_fun_arity_never_result_bug_eta2_main_fun, .env = NULL};
    switch_ = fun_1;
    goto switch_next_1;
switch_next_1:;
    f_ = switch_;
    app_1 = f_.fun(f_.env, 2);
    milone_assert((app_1 == 2), (struct String){.ptr = "fun_arity_never_result_bug/fun_arity_never_result_bug.milone", .len = 60}, 38, 2);
    return 0;
}
