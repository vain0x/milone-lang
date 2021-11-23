#include <milone.h>

int ty_var_unified_unexpectedly_Program_f(void);

int main(int argc, char** argv);

int ty_var_unified_unexpectedly_Program_f(void) {
    return 1;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    int call_ = ty_var_unified_unexpectedly_Program_f();
    milone_assert((call_ == 1), (struct String){.str = "ty_var_unified_unexpectedly/ty_var_unified_unexpectedly.milone", .len = 62}, 10, 2);
    return 0;
}
