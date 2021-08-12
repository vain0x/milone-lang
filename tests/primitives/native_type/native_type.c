#include "milone.h"

char const* str_as_ptr(struct String );

char const* native_type_Program_strAsPtr(struct String s_);

FILE* fopen(char const* , char const* );

FILE* native_type_Program_fopen(struct String filename_, struct String mode_);

int fclose(FILE* );

int native_type_Program_fclose(FILE* fp_);

int milone_main(void);

char const* native_type_Program_strAsPtr(struct String s_) {
    char const* str_as_ptr_result = str_as_ptr(s_);
    return str_as_ptr_result;
}

FILE* native_type_Program_fopen(struct String filename_, struct String mode_) {
    char const* call_ = native_type_Program_strAsPtr(filename_);
    char const* call_1 = native_type_Program_strAsPtr(mode_);
    FILE* fopen_result = fopen(call_, call_1);
    return fopen_result;
}

int native_type_Program_fclose(FILE* fp_) {
    int fclose_result = fclose(fp_);
    return fclose_result;
}

int milone_main(void) {
    FILE* call_2 = native_type_Program_fopen((struct String){.str = "LICENSE", .len = 7}, (struct String){.str = "r", .len = 1});
    FILE* fp_1 = call_2;
    milone_assert((((uintptr_t)fp_1) != ((uintptr_t)0)), 15, 2);
    int call_3 = native_type_Program_fclose(fp_1);
    int stat_ = call_3;
    milone_assert((stat_ == 0), 18, 2);
    return 0;
}
