#include <milone.h>

struct UnitIntFun1;

struct IntIntFun1;

int fun_arity_never_result_bug_fun_arity_never_result_bug_main_IntIntFun1_fun(int arg_2);

int fun_arity_never_result_bug_fun_arity_never_result_bug_UnitIntFun1_unreachable(void);

struct UnitIntFun1 fun_arity_never_result_bug_fun_arity_never_result_bug_StringUnitIntFun2_failwithf(struct String msg_);

int MiloneCore_Prelude_IntIntFun1_id(int );

int fun_arity_never_result_bug_fun_arity_never_result_bug_eta2_main_id(void const* env_, int arg_);

int fun_arity_never_result_bug_fun_arity_never_result_bug_eta2_main_fun(void const* env_1, int arg_1);

int main(int argc, char** argv);

struct UnitIntFun1 {
    int(*fun)(void const*);
    void const* env;
};

struct IntIntFun1 {
    int(*fun)(void const*, int);
    void const* env;
};

int fun_arity_never_result_bug_fun_arity_never_result_bug_main_IntIntFun1_fun(int arg_2) {
    int call_ = fun_arity_never_result_bug_fun_arity_never_result_bug_UnitIntFun1_unreachable();
    return call_;
}

int fun_arity_never_result_bug_fun_arity_never_result_bug_UnitIntFun1_unreachable(void) {
    struct UnitIntFun1 call_1 = fun_arity_never_result_bug_fun_arity_never_result_bug_StringUnitIntFun2_failwithf((struct String){.str = "NEVER: %A", .len = 9});
    int app_ = call_1.fun(call_1.env);
    return app_;
}

struct UnitIntFun1 fun_arity_never_result_bug_fun_arity_never_result_bug_StringUnitIntFun2_failwithf(struct String msg_) {
    printf("%s\n", str_to_c_str(msg_));
    exit(1);
}

int fun_arity_never_result_bug_fun_arity_never_result_bug_eta2_main_id(void const* env_, int arg_) {
    int call_2 = MiloneCore_Prelude_IntIntFun1_id(arg_);
    return call_2;
}

int fun_arity_never_result_bug_fun_arity_never_result_bug_eta2_main_fun(void const* env_1, int arg_1) {
    int call_3 = fun_arity_never_result_bug_fun_arity_never_result_bug_main_IntIntFun1_fun(arg_1);
    return call_3;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    struct IntIntFun1 switch_;
    switch (1) {
        case 1:
            goto clause_2;

        default:
            goto clause_3;
    }
clause_2:;
    struct IntIntFun1 fun_ = (struct IntIntFun1){.fun = fun_arity_never_result_bug_fun_arity_never_result_bug_eta2_main_id, .env = NULL};
    switch_ = fun_;
    goto switch_next_1;
clause_3:;
    struct IntIntFun1 fun_1 = (struct IntIntFun1){.fun = fun_arity_never_result_bug_fun_arity_never_result_bug_eta2_main_fun, .env = NULL};
    switch_ = fun_1;
    goto switch_next_1;
switch_next_1:;
    struct IntIntFun1 f_ = switch_;
    int app_1 = f_.fun(f_.env, 2);
    milone_assert((app_1 == 2), (struct String){.str = "fun_arity_never_result_bug/fun_arity_never_result_bug.milone", .len = 60}, 38, 2);
    return 0;
}
