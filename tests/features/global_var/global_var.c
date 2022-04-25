#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

int32_t global_var_global_var_f(void);

int32_t global_var_global_var_g(void);

int main(int argc, char **argv);

void global_var_global_var_start(void);

int32_t global_var_global_var_success;

int32_t failure_;

int32_t global_var_global_var_f(void) {
    return global_var_global_var_success;
}

int32_t global_var_global_var_g(void) {
    int32_t call_;
    call_ = global_var_global_var_f();
    return call_;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    int32_t call_1;
    global_var_global_var_start();
    call_1 = global_var_global_var_g();
    if ((call_1 != 0)) milone_assert_error("global_var/global_var.milone", 13, 2);
    if ((failure_ != 1)) milone_assert_error("global_var/global_var.milone", 14, 2);
    return 0;
}

void global_var_global_var_start(void) {
    global_var_global_var_success = 0;
    failure_ = 1;
    return;
}
