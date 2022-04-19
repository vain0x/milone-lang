#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

int module_dependencies_root_root(void);

int module_dependencies_third_third(void);

int module_dependencies_third_third(void) {
    int call_;
    call_ = module_dependencies_root_root();
    return call_;
}
