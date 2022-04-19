#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

int32_t module_dependencies_root_root(void);

int32_t module_dependencies_third_third(void);

int32_t module_dependencies_third_third(void) {
    int32_t call_;
    call_ = module_dependencies_root_root();
    return call_;
}
