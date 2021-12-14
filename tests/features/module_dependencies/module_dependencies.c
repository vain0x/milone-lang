#include <milone.h>

int module_dependencies_second_second(void);

int module_dependencies_third_third(void);

int main(int argc, char** argv);

int main(int argc, char** argv) {
    milone_start(argc, argv);
    int call_ = module_dependencies_second_second();
    int call_1 = module_dependencies_third_third();
    return (call_ + call_1);
}
