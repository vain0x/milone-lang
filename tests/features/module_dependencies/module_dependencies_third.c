#include "milone.h"

int module_dependencies_root_root(void);

int module_dependencies_third_third(void);

int module_dependencies_third_third(void) {
    int call_1 = module_dependencies_root_root();
    return call_1;
}
