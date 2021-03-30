#include "milone.h"

int module_dependencies_root_root(char);

int module_dependencies_third_third(char arg_1);

int module_dependencies_third_third(char arg_1) {
    int call_ = module_dependencies_root_root(0);
    return call_;
}
