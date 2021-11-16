#include "milone.h"

int module_open_shadowed_sub_f(int x_);

int module_open_shadowed_sub_g(int x_1);

int module_open_shadowed_sub_f(int x_) {
    return (x_ + 2);
}

int module_open_shadowed_sub_g(int x_1) {
    return (x_1 + 3);
}
