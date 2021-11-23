#include <milone.h>

int fun_used_forward_Program_f(void);

int fun_used_forward_Program_g(void);

int main(int argc, char** argv);

int fun_used_forward_Program_f(void) {
    int call_ = fun_used_forward_Program_g();
    return call_;
}

int fun_used_forward_Program_g(void) {
    return 0;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    int call_1 = fun_used_forward_Program_f();
    milone_assert((call_1 == 0), (struct String){.str = "fun_used_forward/fun_used_forward.milone", .len = 40}, 17, 2);
    return 0;
}
