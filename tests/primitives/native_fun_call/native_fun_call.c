#include <milone.h>

int int_compare(int , int );

int native_fun_call_Program_intCompare(int l_, int r_);

int main(int argc, char** argv);

int native_fun_call_Program_intCompare(int l_, int r_) {
    int int_compare_result = int_compare(l_, r_);
    return int_compare_result;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    int call_ = native_fun_call_Program_intCompare(5, 3);
    milone_assert((call_ == 1), (struct String){.str = "native_fun_call/native_fun_call.milone", .len = 38}, 7, 2);
    return 0;
}
