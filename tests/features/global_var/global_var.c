#include <milone.h>

int global_var_Program_f(void);

int global_var_Program_g(void);

int main(int argc, char** argv);

void global_var_global_var_start(void);

extern int global_var_Program_success;

extern int failure_;

int global_var_Program_success;

int failure_;

int global_var_Program_f(void) {
    return global_var_Program_success;
}

int global_var_Program_g(void) {
    int call_ = global_var_Program_f();
    return call_;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    global_var_global_var_start();
    int call_1 = global_var_Program_g();
    milone_assert((call_1 == 0), (struct String){.str = "global_var/global_var.milone", .len = 28}, 13, 2);
    milone_assert((failure_ == 1), (struct String){.str = "global_var/global_var.milone", .len = 28}, 14, 2);
    return 0;
}

void global_var_global_var_start(void) {
    global_var_Program_success = 0;
    failure_ = 1;
    return;
}
