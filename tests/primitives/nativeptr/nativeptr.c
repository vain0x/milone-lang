#include "milone.h"

void* milone_mem_alloc(int, uintptr_t);

void* memAlloc_(int count_, int size_);

void* memset(void*, int, uintptr_t);

char memSet_(void* dest_, uint8_t value_, int count_1);

char* strcpy(char*, char const*);

char* strcpy_(char* dest_1, char const* src_);

int milone_main();

void* memAlloc_(int count_, int size_) {
    void* milone_mem_alloc_result_ = milone_mem_alloc(count_, ((uintptr_t)size_));
    return milone_mem_alloc_result_;
}

char memSet_(void* dest_, uint8_t value_, int count_1) {
    void* memset_result_ = memset(dest_, ((int)value_), ((uintptr_t)count_1));
    return 0;
}

char* strcpy_(char* dest_1, char const* src_) {
    char* strcpy_result_ = strcpy(dest_1, src_);
    return strcpy_result_;
}

int milone_main() {
    void* call_ = memAlloc_(1, 8);
    void* buf_ = call_;
    char call_1 = memSet_(buf_, ((uint8_t)255), 8);
    milone_assert(((*(((int const*)((void const*)buf_)))) == -1), 22, 2);
    milone_assert((((uintptr_t)buf_) != ((uintptr_t)0)), 25, 2);
    return 0;
}
