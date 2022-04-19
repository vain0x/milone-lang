#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

int global_var_global_var_f(void);

int global_var_global_var_g(void);

int main(int argc, char** argv);

void global_var_global_var_start(void);

int global_var_global_var_success;

int failure_;

int global_var_global_var_f(void) {
    return global_var_global_var_success;
}

int global_var_global_var_g(void) {
    int call_;
    call_ = global_var_global_var_f();
    return call_;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    int call_1;
    global_var_global_var_start();
    call_1 = global_var_global_var_g();
    milone_assert((call_1 == 0), (struct String){.ptr = "global_var/global_var.milone", .len = 28}, 13, 2);
    milone_assert((failure_ == 1), (struct String){.ptr = "global_var/global_var.milone", .len = 28}, 14, 2);
    return 0;
}

void global_var_global_var_start(void) {
    global_var_global_var_success = 0;
    failure_ = 1;
    return;
}
