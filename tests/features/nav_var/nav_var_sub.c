#include <milone.h>

int nav_var_sub_getAnswer(void);

void nav_var_sub_start(void);

int nav_var_sub_answer;

int nav_var_sub_getAnswer(void) {
    return 42;
}

void nav_var_sub_start(void) {
    nav_var_sub_answer = 42;
    return;
}
