#include <milone.h>

struct StringStringFun1;

void fun_underlying_fun_forward_decl_issue_sub_start(void);

int main(int argc, char** argv);

struct StringStringFun1 {
    struct String(*fun)(void const*, struct String);
    void const* env;
};

extern struct StringStringFun1 fun_underlying_fun_forward_decl_issue_sub_f2;

int main(int argc, char** argv) {
    milone_start(argc, argv);
    fun_underlying_fun_forward_decl_issue_sub_start();
    struct String app_ = fun_underlying_fun_forward_decl_issue_sub_f2.fun(fun_underlying_fun_forward_decl_issue_sub_f2.env, (struct String){.str = "hi", .len = 2});
    milone_assert((str_compare(app_, (struct String){.str = "x = 2, y = hi", .len = 13}) == 0), (struct String){.str = "fun_underlying_fun_forward_decl_issue/fun_underlying_fun_forward_decl_issue.milone", .len = 82}, 22, 2);
    return 0;
}
