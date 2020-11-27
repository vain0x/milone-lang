#include "milone.h"

void* memAlloc_(int count_, uintptr_t size_);

int memSet_(void* dest_, uint8_t value_, int count_1);

char* strcpy_(char* dest_1, char const* src_);

int main();

void* memAlloc_(int count_, uintptr_t size_) {
    void* milone_mem_alloc_result_ = milone_mem_alloc(count_, size_);
    return milone_mem_alloc_result_;
}

int memSet_(void* dest_, uint8_t value_, int count_1) {
    void* memset_result_ = memset(dest_, value_, count_1);
    return 0;
}

char* strcpy_(char* dest_1, char const* src_) {
    char* strcpy_result_ = strcpy(dest_1, src_);
    return strcpy_result_;
}

int main() {
    void* call_ = memAlloc_(1, ((uintptr_t)8));
    void* buf_ = call_;
    int call_1 = memSet_(buf_, ((uint8_t)255), 8);
    milone_assert(((*(((int*)buf_))) == (0 - 1)), 16, 2);
    return 0;
}
