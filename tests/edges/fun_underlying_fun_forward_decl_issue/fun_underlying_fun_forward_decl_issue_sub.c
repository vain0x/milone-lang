#include "milone.h"

struct String fun_underlying_fun_forward_decl_issue_sub_f(int x_, struct String y_);

struct String fun_underlying_fun_forward_decl_issue_sub_eta2__f(void const* env_, struct String arg_);

struct String fun_underlying_fun_forward_decl_issue_sub_f(int x_, struct String y_) {
    struct String call_ = str_of_int64(x_);
    return str_add(str_add(str_add((struct String){.str = "x = ", .len = 4}, call_), (struct String){.str = ", y = ", .len = 6}), y_);
}

struct String fun_underlying_fun_forward_decl_issue_sub_eta2__f(void const* env_, struct String arg_) {
    int arg_1 = ((int)((intptr_t)env_));
    struct String call_1 = fun_underlying_fun_forward_decl_issue_sub_f(arg_1, arg_);
    return call_1;
}
