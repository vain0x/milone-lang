#include "milone.h"

int module_dependencies_second_second(char);

int module_dependencies_third_third(char);

int milone_main();

int milone_main() {
    int call_2 = module_dependencies_second_second(0);
    int call_3 = module_dependencies_third_third(0);
    return (call_2 + call_3);
}
