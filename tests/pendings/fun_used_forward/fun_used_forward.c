#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

int32_t fun_used_forward_fun_used_forward_f(void);

int32_t fun_used_forward_fun_used_forward_g(void);

int main(int argc, char** argv);

int32_t fun_used_forward_fun_used_forward_f(void) {
    int32_t call_;
    call_ = fun_used_forward_fun_used_forward_g();
    return call_;
}

int32_t fun_used_forward_fun_used_forward_g(void) {
    return 0;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    int32_t call_1;
    call_1 = fun_used_forward_fun_used_forward_f();
    milone_assert((call_1 == 0), (struct String){.ptr = "fun_used_forward/fun_used_forward.milone", .len = 40}, 17, 2);
    return 0;
}
