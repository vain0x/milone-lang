#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

int32_t nav_var_sub_getAnswer(void);

void nav_var_sub_start(void);

int32_t nav_var_sub_answer;

int32_t nav_var_sub_getAnswer(void) {
    return 42;
}

void nav_var_sub_start(void) {
    nav_var_sub_answer = 42;
    return;
}
