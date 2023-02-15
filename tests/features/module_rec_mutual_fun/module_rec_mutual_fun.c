#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

bool module_rec_mutual_fun_module_rec_mutual_fun_even(int32_t n_);

bool module_rec_mutual_fun_module_rec_mutual_fun_odd(int32_t n_1);

int main(int argc, char **argv);

bool module_rec_mutual_fun_module_rec_mutual_fun_even(int32_t n_) {
    bool if_;
    bool call_;
    if ((n_ == 0)) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    if_ = true;
    goto if_next_1;
else_3:;
    call_ = module_rec_mutual_fun_module_rec_mutual_fun_odd((n_ - 1));
    if_ = call_;
    goto if_next_1;
if_next_1:;
    return if_;
}

bool module_rec_mutual_fun_module_rec_mutual_fun_odd(int32_t n_1) {
    bool if_1;
    bool call_1;
    if ((n_1 != 0)) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    call_1 = module_rec_mutual_fun_module_rec_mutual_fun_even((n_1 - 1));
    if_1 = call_1;
    goto if_next_1;
else_3:;
    if_1 = false;
    goto if_next_1;
if_next_1:;
    return if_1;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    bool call_2;
    bool call_3;
    bool call_4;
    call_2 = module_rec_mutual_fun_module_rec_mutual_fun_odd(1);
    if ((!(call_2))) milone_assert_error("module_rec_mutual_fun/module_rec_mutual_fun.milone", 9, 2);
    call_3 = module_rec_mutual_fun_module_rec_mutual_fun_even(2);
    if ((!(call_3))) milone_assert_error("module_rec_mutual_fun/module_rec_mutual_fun.milone", 10, 2);
    call_4 = module_rec_mutual_fun_module_rec_mutual_fun_even(3);
    if (call_4) milone_assert_error("module_rec_mutual_fun/module_rec_mutual_fun.milone", 11, 2);
    return 0;
}
