#include "milone.h"

struct StringStringFun1;

void fun_underlying_fun_forward_decl_issue_sub__start(void);

int milone_main(void);

struct StringStringFun1 {
    struct String(*fun)(void const*, struct String);
    void const* env;
};

extern struct StringStringFun1 fun_underlying_fun_forward_decl_issue_sub_f2;

int milone_main(void) {
    fun_underlying_fun_forward_decl_issue_sub__start();
    struct String app_ = fun_underlying_fun_forward_decl_issue_sub_f2.fun(fun_underlying_fun_forward_decl_issue_sub_f2.env, (struct String){.str = "hi", .len = 2});
    milone_assert((str_compare(app_, (struct String){.str = "x = 2, y = hi", .len = 13}) == 0), 22, 2);
    return 0;
}
