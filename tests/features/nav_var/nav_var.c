#include <milone.h>

void nav_var_sub_start(void);

int nav_var_sub_getAnswer(void);

int main(int argc, char** argv);

extern int nav_var_sub_answer;

int main(int argc, char** argv) {
    milone_start(argc, argv);
    int myAnswer_;
    int call_;
    nav_var_sub_start();
    milone_assert((nav_var_sub_answer == 42), (struct String){.str = "nav_var/nav_var.milone", .len = 22}, 8, 2);
    call_ = nav_var_sub_getAnswer();
    milone_assert((call_ == 42), (struct String){.str = "nav_var/nav_var.milone", .len = 22}, 11, 2);
    myAnswer_ = 42;
    return 0;
}
