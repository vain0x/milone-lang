#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

typedef struct String(*VoidConstPtrStringStringFunPtr2)(void const *, struct String);

struct StringStringFun1;

void fun_underlying_fun_forward_decl_issue_sub_start(void);

int main(int argc, char **argv);

struct StringStringFun1 {
    VoidConstPtrStringStringFunPtr2 fun;
    void const *env;
};

extern struct StringStringFun1 fun_underlying_fun_forward_decl_issue_sub_f2;

int main(int argc, char **argv) {
    milone_start(argc, argv);
    struct String app_;
    fun_underlying_fun_forward_decl_issue_sub_start();
    app_ = fun_underlying_fun_forward_decl_issue_sub_f2.fun(fun_underlying_fun_forward_decl_issue_sub_f2.env, (struct String){.ptr = "hi", .len = 2});
    if ((string_compare(app_, (struct String){.ptr = "x = 2, y = hi", .len = 13}) != 0)) milone_assert_error("fun_underlying_fun_forward_decl_issue/fun_underlying_fun_forward_decl_issue.milone", 22, 2);
    return 0;
}
