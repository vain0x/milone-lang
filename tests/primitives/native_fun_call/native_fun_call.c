#include "milone.h"

int int_compare(int , int );

int native_fun_call_Program_intCompare(int l_, int r_);

int milone_main(void);

int native_fun_call_Program_intCompare(int l_, int r_) {
    int int_compare_result = int_compare(l_, r_);
    return int_compare_result;
}

int milone_main(void) {
    int call_ = native_fun_call_Program_intCompare(5, 3);
    milone_assert((call_ == 1), 7, 2);
    return 0;
}
