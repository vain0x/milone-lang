#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

int recursive_ty_error_by_synonym_recursive_ty_error_by_synonym_IntIntFun1_just(int value_);

int main(int argc, char** argv);

int recursive_ty_error_by_synonym_recursive_ty_error_by_synonym_IntIntFun1_just(int value_) {
    return value_;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    int call_;
    call_ = recursive_ty_error_by_synonym_recursive_ty_error_by_synonym_IntIntFun1_just(2);
    milone_assert((call_ == 2), (struct String){.ptr = "recursive_ty_error_by_synonym/recursive_ty_error_by_synonym.milone", .len = 66}, 7, 2);
    return 0;
}
