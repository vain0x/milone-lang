#include "milone.h"

int ty_var_unified_unexpectedly_Program_f(char arg_);

int milone_main();

int ty_var_unified_unexpectedly_Program_f(char arg_) {
    return 1;
}

int milone_main() {
    int call_ = ty_var_unified_unexpectedly_Program_f(0);
    milone_assert((call_ == 1), 9, 2);
    return 0;
}
