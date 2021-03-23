#include "milone.h"

bool module_rec_mutual_fun_Program_even(int n_);

bool module_rec_mutual_fun_Program_odd(int n_1);

int milone_main();

bool module_rec_mutual_fun_Program_even(int n_) {
    bool if_;
    if ((n_ == 0)) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    if_ = true;
    goto if_next_1;
else_3:;
    bool call_ = module_rec_mutual_fun_Program_odd((n_ - 1));
    if_ = call_;
    goto if_next_1;
if_next_1:;
    return if_;
}

bool module_rec_mutual_fun_Program_odd(int n_1) {
    bool if_1;
    if ((n_1 != 0)) {
        goto then_5;
    } else {
        goto else_6;
    }
then_5:;
    bool call_1 = module_rec_mutual_fun_Program_even((n_1 - 1));
    if_1 = call_1;
    goto if_next_4;
else_6:;
    if_1 = false;
    goto if_next_4;
if_next_4:;
    return if_1;
}

int milone_main() {
    bool call_2 = module_rec_mutual_fun_Program_odd(1);
    milone_assert(call_2, 9, 2);
    bool call_3 = module_rec_mutual_fun_Program_even(2);
    milone_assert(call_3, 10, 2);
    bool call_4 = module_rec_mutual_fun_Program_even(3);
    milone_assert((!(call_4)), 11, 2);
    return 0;
}
