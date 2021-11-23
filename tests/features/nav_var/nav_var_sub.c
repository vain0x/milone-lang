#include "milone.h"

int nav_var_sub_getAnswer(void);

void nav_var_sub__start(void);

int nav_var_sub_answer;

int nav_var_sub_getAnswer(void) {
    return 42;
}

void nav_var_sub__start(void) {
    nav_var_sub_answer = 42;
    return;
}
