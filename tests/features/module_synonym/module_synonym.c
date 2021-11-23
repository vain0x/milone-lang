#include <milone.h>

int module_synonym_sub_inc(int );

int main(int argc, char** argv);

int main(int argc, char** argv) {
    milone_start(argc, argv);
    int call_ = module_synonym_sub_inc(2);
    milone_assert((call_ == 3), (struct String){.str = "module_synonym/module_synonym.milone", .len = 36}, 7, 2);
    return 0;
}
