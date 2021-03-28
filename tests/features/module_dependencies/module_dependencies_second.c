#include "milone.h"

int module_dependencies_root_root(char);

int module_dependencies_second_second(char arg_2);

int module_dependencies_second_second(char arg_2) {
    int call_1 = module_dependencies_root_root(0);
    return call_1;
}
