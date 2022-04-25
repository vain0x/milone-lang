#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

void nav_var_sub_start(void);

int32_t nav_var_sub_getAnswer(void);

int main(int argc, char **argv);

extern int32_t nav_var_sub_answer;

int main(int argc, char **argv) {
    milone_start(argc, argv);
    int32_t myAnswer_;
    int32_t call_;
    nav_var_sub_start();
    if ((nav_var_sub_answer != 42)) milone_assert_error("nav_var/nav_var.milone", 8, 2);
    call_ = nav_var_sub_getAnswer();
    if ((call_ != 42)) milone_assert_error("nav_var/nav_var.milone", 11, 2);
    myAnswer_ = 42;
    return 0;
}
