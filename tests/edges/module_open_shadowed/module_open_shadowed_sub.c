#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

int32_t module_open_shadowed_sub_f(int32_t x_);

int32_t module_open_shadowed_sub_g(int32_t x_1);

int32_t module_open_shadowed_sub_f(int32_t x_) {
    return (x_ + 2);
}

int32_t module_open_shadowed_sub_g(int32_t x_1) {
    return (x_1 + 3);
}
