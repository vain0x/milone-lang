#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

typedef struct String(*VoidConstPtrStringStringFunPtr2)(void const *, struct String);

struct StringStringFun1;

struct String fun_underlying_fun_forward_decl_issue_sub_f(int32_t x_, struct String y_);

struct String fun_underlying_fun_forward_decl_issue_sub_eta2__f(void const *env_, struct String arg_);

void fun_underlying_fun_forward_decl_issue_sub_start(void);

struct StringStringFun1 {
    VoidConstPtrStringStringFunPtr2 fun;
    void const *env;
};

struct StringStringFun1 fun_underlying_fun_forward_decl_issue_sub_f2;

struct String fun_underlying_fun_forward_decl_issue_sub_f(int32_t x_, struct String y_) {
    struct String call_;
    call_ = string_of_int64(x_);
    return string_add(string_add(string_add((struct String){.ptr = "x = ", .len = 4}, call_), (struct String){.ptr = ", y = ", .len = 6}), y_);
}

struct String fun_underlying_fun_forward_decl_issue_sub_eta2__f(void const *env_, struct String arg_) {
    int32_t arg_1;
    struct String call_1;
    arg_1 = ((int32_t)((intptr_t)env_));
    call_1 = fun_underlying_fun_forward_decl_issue_sub_f(arg_1, arg_);
    return call_1;
}

void fun_underlying_fun_forward_decl_issue_sub_start(void) {
    struct StringStringFun1 fun_;
    fun_ = (struct StringStringFun1){.fun = fun_underlying_fun_forward_decl_issue_sub_eta2__f, .env = ((void const *)((intptr_t)2))};
    fun_underlying_fun_forward_decl_issue_sub_f2 = fun_;
    return;
}
