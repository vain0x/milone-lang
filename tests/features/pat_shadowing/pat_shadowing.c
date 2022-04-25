#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

int main(int argc, char **argv);

int main(int argc, char **argv) {
    milone_start(argc, argv);
    int32_t x_;
    int32_t x_1;
    char case1_;
    int32_t x_2;
    int32_t x_3;
    char case2_;
    x_ = 1;
    x_1 = 0;
    if ((x_1 != 0)) milone_assert_error("pat_shadowing/pat_shadowing.milone", 8, 4);
    case1_ = 0;
    x_2 = 0;
    x_3 = 1;
    if ((x_3 != 1)) milone_assert_error("pat_shadowing/pat_shadowing.milone", 14, 5);
    if ((x_2 != 0)) milone_assert_error("pat_shadowing/pat_shadowing.milone", 16, 4);
    case2_ = 0;
    return 0;
}
