#include "milone.h"

int module_dependencies_second_second(void);

int module_dependencies_third_third(void);

int milone_main(void);

int milone_main(void) {
    int call_ = module_dependencies_second_second();
    int call_1 = module_dependencies_third_third();
    return (call_ + call_1);
}
