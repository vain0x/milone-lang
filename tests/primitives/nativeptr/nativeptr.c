#include "milone.h"

void* milone_mem_alloc(int , uintptr_t );

void* nativeptr_Program_memAlloc(int count_, int size_);

void* memset(void* , int , uintptr_t );

void nativeptr_Program_memSet(void* dest_, uint8_t value_, int count_1);

char* strcpy(char* , char const* );

char* nativeptr_Program_strcpy(char* dest_1, char const* src_);

int milone_main(void);

void* nativeptr_Program_memAlloc(int count_, int size_) {
    void* milone_mem_alloc_result = milone_mem_alloc(count_, ((uintptr_t)size_));
    return milone_mem_alloc_result;
}

void nativeptr_Program_memSet(void* dest_, uint8_t value_, int count_1) {
    void* memset_result = memset(dest_, ((int)value_), ((uintptr_t)count_1));
    return;
}

char* nativeptr_Program_strcpy(char* dest_1, char const* src_) {
    char* strcpy_result = strcpy(dest_1, src_);
    return strcpy_result;
}

int milone_main(void) {
    void* call_ = nativeptr_Program_memAlloc(1, 8);
    void* buf_ = call_;
    nativeptr_Program_memSet(buf_, ((uint8_t)255), 8);
    int read_ = (*(((int const*)buf_)));
    milone_assert((read_ == -1), 22, 2);
    milone_assert((((uintptr_t)buf_) != ((uintptr_t)0)), 25, 2);
    return 0;
}
