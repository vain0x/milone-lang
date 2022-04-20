#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

int32_t milone_int32_compare(int32_t, int32_t);

int32_t native_fun_call_native_fun_call_intCompare(int32_t l_, int32_t r_);

int main(int argc, char **argv);

int32_t native_fun_call_native_fun_call_intCompare(int32_t l_, int32_t r_) {
    int32_t milone_int32_compare_result;
    milone_int32_compare_result = milone_int32_compare(l_, r_);
    return milone_int32_compare_result;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    int32_t call_;
    call_ = native_fun_call_native_fun_call_intCompare(5, 3);
    if ((call_ != 1)) milone_assert_error("native_fun_call/native_fun_call.milone", 9, 2);
    return 0;
}
