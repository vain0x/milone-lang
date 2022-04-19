#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

int main(int argc, char** argv);

int main(int argc, char** argv) {
    milone_start(argc, argv);
    int x_;
    int x_1;
    char case1_;
    int x_2;
    int x_3;
    char case2_;
    x_ = 1;
    x_1 = 0;
    milone_assert((x_1 == 0), (struct String){.ptr = "pat_shadowing/pat_shadowing.milone", .len = 34}, 8, 4);
    case1_ = 0;
    x_2 = 0;
    x_3 = 1;
    milone_assert((x_3 == 1), (struct String){.ptr = "pat_shadowing/pat_shadowing.milone", .len = 34}, 14, 5);
    milone_assert((x_2 == 0), (struct String){.ptr = "pat_shadowing/pat_shadowing.milone", .len = 34}, 16, 4);
    case2_ = 0;
    return 0;
}
