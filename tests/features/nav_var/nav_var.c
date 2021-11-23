#include "milone.h"

void nav_var_sub__start(void);

int nav_var_sub_getAnswer(void);

int milone_main(void);

extern int nav_var_sub_answer;

int milone_main(void) {
    nav_var_sub__start();
    milone_assert((nav_var_sub_answer == 42), 8, 2);
    int call_ = nav_var_sub_getAnswer();
    milone_assert((call_ == 42), 11, 2);
    int myAnswer_ = 42;
    return 0;
}
