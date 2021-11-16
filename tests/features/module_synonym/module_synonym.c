#include "milone.h"

int module_synonym_sub_inc(int );

int milone_main(void);

int milone_main(void) {
    int call_ = module_synonym_sub_inc(2);
    milone_assert((call_ == 3), 7, 2);
    return 0;
}
