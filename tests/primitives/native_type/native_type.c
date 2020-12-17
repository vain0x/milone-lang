#include "milone.h"

char const* str_as_ptr(struct String);

char const* strAsPtr_(struct String s_);

FILE* fopen(char const*, char const*);

FILE* fopen_(struct String filename_, struct String mode_);

int fclose(FILE*);

int fclose_(FILE* fp_);

int main();

char const* strAsPtr_(struct String s_) {
    char const* str_as_ptr_result_ = str_as_ptr(s_);
    return str_as_ptr_result_;
}

FILE* fopen_(struct String filename_, struct String mode_) {
    char const* call_ = strAsPtr_(filename_);
    char const* call_1 = strAsPtr_(mode_);
    FILE* fopen_result_ = fopen(call_, call_1);
    return fopen_result_;
}

int fclose_(FILE* fp_) {
    int fclose_result_ = fclose(fp_);
    return fclose_result_;
}

int main() {
    FILE* call_2 = fopen_((struct String){.str = "LICENSE", .len = 7}, (struct String){.str = "r", .len = 1});
    FILE* fp_1 = call_2;
    milone_assert((((uintptr_t)fp_1) != ((uintptr_t)0)), 15, 2);
    int call_3 = fclose_(fp_1);
    int stat_ = call_3;
    milone_assert((stat_ == 0), 18, 2);
    return 0;
}
