#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

int32_t module_dependencies_second_second(void);

int32_t module_dependencies_third_third(void);

int main(int argc, char** argv);

int main(int argc, char** argv) {
    milone_start(argc, argv);
    int32_t call_;
    int32_t call_1;
    call_ = module_dependencies_second_second();
    call_1 = module_dependencies_third_third();
    return (call_ + call_1);
}
