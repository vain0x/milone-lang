#include "milone.h"

int ty_var_unified_unexpectedly_Program_f(void);

int milone_main(void);

int ty_var_unified_unexpectedly_Program_f(void) {
    return 1;
}

int milone_main(void) {
    int call_ = ty_var_unified_unexpectedly_Program_f();
    milone_assert((call_ == 1), 10, 2);
    return 0;
}
