#include "milone.h"

int module_synonym_sub_inc(int x_);

int milone_main();

int module_synonym_sub_inc(int x_) {
    return (x_ + 1);
}

int milone_main() {
    int call_ = module_synonym_sub_inc(2);
    milone_assert((call_ == 3), 7, 2);
    return 0;
}
