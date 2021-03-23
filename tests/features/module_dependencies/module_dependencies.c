#include "milone.h"

int module_dependencies_root_root(char arg_);

int module_dependencies_third_third(char arg_1);

int module_dependencies_second_second(char arg_2);

int milone_main();

int module_dependencies_root_root(char arg_) {
    return 0;
}

int module_dependencies_third_third(char arg_1) {
    int call_ = module_dependencies_root_root(0);
    return call_;
}

int module_dependencies_second_second(char arg_2) {
    int call_1 = module_dependencies_root_root(0);
    return call_1;
}

int milone_main() {
    int call_2 = module_dependencies_second_second(0);
    int call_3 = module_dependencies_third_third(0);
    return (call_2 + call_3);
}
