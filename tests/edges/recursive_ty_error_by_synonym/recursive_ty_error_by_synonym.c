#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

int32_t recursive_ty_error_by_synonym_recursive_ty_error_by_synonym_Int32Int32Fun1_just(int32_t value_);

int main(int argc, char **argv);

int32_t recursive_ty_error_by_synonym_recursive_ty_error_by_synonym_Int32Int32Fun1_just(int32_t value_) {
    return value_;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    int32_t call_;
    call_ = recursive_ty_error_by_synonym_recursive_ty_error_by_synonym_Int32Int32Fun1_just(2);
    if ((call_ != 2)) milone_assert_error("recursive_ty_error_by_synonym/recursive_ty_error_by_synonym.milone", 7, 2);
    return 0;
}
