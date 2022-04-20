#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

int32_t module_synonym_sub_inc(int32_t);

int main(int argc, char **argv);

int main(int argc, char **argv) {
    milone_start(argc, argv);
    int32_t call_;
    call_ = module_synonym_sub_inc(2);
    if ((call_ != 3)) milone_assert_error("module_synonym/module_synonym.milone", 7, 2);
    return 0;
}
