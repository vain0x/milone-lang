#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

char const* string_as_ptr(struct String );

char const* native_type_native_type_strAsPtr(struct String s_);

FILE* fopen(char const* , char const* );

FILE* native_type_native_type_fopen(struct String filename_, struct String mode_);

int32_t fclose(FILE* );

int32_t native_type_native_type_fclose(FILE* fp_);

int main(int argc, char** argv);

char const* native_type_native_type_strAsPtr(struct String s_) {
    char const* string_as_ptr_result;
    string_as_ptr_result = string_as_ptr(s_);
    return string_as_ptr_result;
}

FILE* native_type_native_type_fopen(struct String filename_, struct String mode_) {
    char const* call_;
    char const* call_1;
    FILE* fopen_result;
    call_ = native_type_native_type_strAsPtr(filename_);
    call_1 = native_type_native_type_strAsPtr(mode_);
    fopen_result = fopen(call_, call_1);
    return fopen_result;
}

int32_t native_type_native_type_fclose(FILE* fp_) {
    int32_t fclose_result;
    fclose_result = fclose(fp_);
    return fclose_result;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    FILE* fp_1;
    int32_t stat_;
    FILE* call_2;
    int32_t call_3;
    call_2 = native_type_native_type_fopen((struct String){.ptr = "LICENSE", .len = 7}, (struct String){.ptr = "r", .len = 1});
    fp_1 = call_2;
    milone_assert((fp_1 != ((FILE*)NULL)), (struct String){.ptr = "native_type/native_type.milone", .len = 30}, 18, 2);
    call_3 = native_type_native_type_fclose(fp_1);
    stat_ = call_3;
    milone_assert((stat_ == 0), (struct String){.ptr = "native_type/native_type.milone", .len = 30}, 21, 2);
    return 0;
}
