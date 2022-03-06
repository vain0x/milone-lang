#include <milone.h>

char const* str_as_ptr(struct String );

char const* native_type_native_type_strAsPtr(struct String s_);

FILE* fopen(char const* , char const* );

FILE* native_type_native_type_fopen(struct String filename_, struct String mode_);

int fclose(FILE* );

int native_type_native_type_fclose(FILE* fp_);

int main(int argc, char** argv);

char const* native_type_native_type_strAsPtr(struct String s_) {
    char const* str_as_ptr_result = str_as_ptr(s_);
    return str_as_ptr_result;
}

FILE* native_type_native_type_fopen(struct String filename_, struct String mode_) {
    char const* call_ = native_type_native_type_strAsPtr(filename_);
    char const* call_1 = native_type_native_type_strAsPtr(mode_);
    FILE* fopen_result = fopen(call_, call_1);
    return fopen_result;
}

int native_type_native_type_fclose(FILE* fp_) {
    int fclose_result = fclose(fp_);
    return fclose_result;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    FILE* call_2 = native_type_native_type_fopen((struct String){.str = "LICENSE", .len = 7}, (struct String){.str = "r", .len = 1});
    FILE* fp_1 = call_2;
    milone_assert((((uintptr_t)fp_1) != (size_t)0ULL), (struct String){.str = "native_type/native_type.milone", .len = 30}, 15, 2);
    int call_3 = native_type_native_type_fclose(fp_1);
    int stat_ = call_3;
    milone_assert((stat_ == 0), (struct String){.str = "native_type/native_type.milone", .len = 30}, 18, 2);
    return 0;
}
