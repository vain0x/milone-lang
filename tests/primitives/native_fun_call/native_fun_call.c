#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

int milone_int32_compare(int , int );

int native_fun_call_native_fun_call_intCompare(int l_, int r_);

int main(int argc, char** argv);

int native_fun_call_native_fun_call_intCompare(int l_, int r_) {
    int milone_int32_compare_result;
    milone_int32_compare_result = milone_int32_compare(l_, r_);
    return milone_int32_compare_result;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    int call_;
    call_ = native_fun_call_native_fun_call_intCompare(5, 3);
    milone_assert((call_ == 1), (struct String){.ptr = "native_fun_call/native_fun_call.milone", .len = 38}, 9, 2);
    return 0;
}
