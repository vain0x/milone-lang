#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

int module_dependencies_root_root(void);

int module_dependencies_second_second(void);

int module_dependencies_second_second(void) {
    int call_;
    call_ = module_dependencies_root_root();
    return call_;
}
