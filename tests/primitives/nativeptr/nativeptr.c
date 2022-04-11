#include <milone.h>

void* milone_mem_alloc(int , uintptr_t );

void* nativeptr_nativeptr_memAlloc(int count_, int size_);

void* memset(void* , int , uintptr_t );

void nativeptr_nativeptr_memSet(void* dest_, uint8_t value_, int count_1);

char* strcpy(char* , char const* );

char* nativeptr_nativeptr_strcpy(char* dest_1, char const* src_);

void nativeptr_nativeptr_testVoidPtrAvailable(void);

void nativeptr_nativeptr_testNullPtr(void);

void nativeptr_nativeptr_testEquality(void);

int main(int argc, char** argv);

void* nativeptr_nativeptr_memAlloc(int count_, int size_) {
    void* milone_mem_alloc_result;
    milone_mem_alloc_result = milone_mem_alloc(count_, ((uintptr_t)size_));
    return milone_mem_alloc_result;
}

void nativeptr_nativeptr_memSet(void* dest_, uint8_t value_, int count_1) {
    void* memset_result;
    memset_result = memset(dest_, ((int)value_), ((uintptr_t)count_1));
    return;
}

char* nativeptr_nativeptr_strcpy(char* dest_1, char const* src_) {
    char* strcpy_result;
    strcpy_result = strcpy(dest_1, src_);
    return strcpy_result;
}

void nativeptr_nativeptr_testVoidPtrAvailable(void) {
    void* mutEnv_;
    void const* constEnv_;
    mutEnv_ = ((void*)(size_t)42ULL);
    constEnv_ = ((void const*)mutEnv_);
    milone_assert((((uintptr_t)constEnv_) == (size_t)42ULL), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 18, 2);
    return;
}

void nativeptr_nativeptr_testNullPtr(void) {
    void* nullVoidPtr_;
    void const* nullVoidConstPtr_;
    double* nullNativePtr_;
    double const* nullConstPtr_;
    nullVoidPtr_ = NULL;
    milone_assert((((uintptr_t)nullVoidPtr_) == (size_t)0ULL), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 22, 2);
    nullVoidConstPtr_ = NULL;
    milone_assert((((uintptr_t)nullVoidConstPtr_) == (size_t)0ULL), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 25, 2);
    nullNativePtr_ = ((double*)NULL);
    milone_assert((((uintptr_t)nullNativePtr_) == (size_t)0ULL), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 28, 2);
    nullConstPtr_ = ((double const*)NULL);
    milone_assert((((uintptr_t)nullConstPtr_) == (size_t)0ULL), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 31, 2);
    return;
}

void nativeptr_nativeptr_testEquality(void) {
    int* np_;
    int* p_;
    int const* nq_;
    int const* q_;
    np_ = ((int*)NULL);
    p_ = ((int*)(size_t)42ULL);
    milone_assert((p_ != np_), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 36, 2);
    nq_ = ((int const*)NULL);
    q_ = ((int const*)(size_t)42ULL);
    milone_assert((q_ != nq_), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 40, 2);
    return;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    void* buf_;
    void* call_;
    int read_;
    nativeptr_nativeptr_testVoidPtrAvailable();
    nativeptr_nativeptr_testNullPtr();
    nativeptr_nativeptr_testEquality();
    call_ = nativeptr_nativeptr_memAlloc(1, 8);
    buf_ = call_;
    nativeptr_nativeptr_memSet(buf_, (uint8_t)255U, 8);
    read_ = (*(((int const*)buf_)));
    milone_assert((read_ == -1), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 49, 2);
    milone_assert((((uintptr_t)buf_) != (size_t)0ULL), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 52, 2);
    return 0;
}
