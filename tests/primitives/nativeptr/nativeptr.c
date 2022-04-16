#include <milone.h>

struct ObjectObjectTuple2_;

typedef void(*VoidConstPtrVoidFunPtr1)(void const*);

struct UnitUnitFun1;

struct Int64UInt8UInt8Tuple3_;

int nativeptr_nativeptr_ObjectObjectTuple2MutPtrIntFun1_sizeOfPointee(struct ObjectObjectTuple2_* ptr_);

void* milone_mem_alloc(int , uintptr_t );

void* nativeptr_nativeptr_memAlloc(int count_, int size_);

void* memset(void* , int , uintptr_t );

void nativeptr_nativeptr_memSet(void* dest_, uint8_t value_, int count_1);

char* strcpy(char* , char const* );

char* nativeptr_nativeptr_strcpy(char* dest_1, char const* src_);

void nativeptr_nativeptr_testBasic(void);

void nativeptr_nativeptr_testVoidPtrAvailable(void);

void nativeptr_nativeptr_testNullPtr(void);

void nativeptr_nativeptr_testAsConst(void);

void nativeptr_nativeptr_testAsMutable(void);

void nativeptr_nativeptr_testEquality(void);

void nativeptr_nativeptr_testSizeOf(void);

void nativeptr_nativeptr_testPtrOf(void);

void nativeptr_nativeptr_testPtrSelect(void);

void nativeptr_nativeptr_testPtrRead(void);

void nativeptr_nativeptr_testPtrWrite(void);

int main(int argc, char** argv);

struct ObjectObjectTuple2_ {
    void const* t0;
    void const* t1;
};

struct UnitUnitFun1 {
    VoidConstPtrVoidFunPtr1 fun;
    void const* env;
};

struct Int64UInt8UInt8Tuple3_ {
    int64_t t0;
    uint8_t t1;
    uint8_t t2;
};

int nativeptr_nativeptr_ObjectObjectTuple2MutPtrIntFun1_sizeOfPointee(struct ObjectObjectTuple2_* ptr_) {
    return sizeof(struct ObjectObjectTuple2_);
}

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

void nativeptr_nativeptr_testBasic(void) {
    void* buf_;
    void* call_;
    call_ = nativeptr_nativeptr_memAlloc(1, 8);
    buf_ = call_;
    nativeptr_nativeptr_memSet(buf_, (uint8_t)255U, 8);
    milone_assert(((*(((int const*)buf_))) == -1), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 20, 2);
    milone_assert((((uintptr_t)buf_) != (size_t)0ULL), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 23, 2);
    return;
}

void nativeptr_nativeptr_testVoidPtrAvailable(void) {
    void* mutEnv_;
    void const* constEnv_;
    mutEnv_ = ((void*)(size_t)42ULL);
    constEnv_ = ((void const*)mutEnv_);
    milone_assert((((uintptr_t)constEnv_) == (size_t)42ULL), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 28, 2);
    return;
}

void nativeptr_nativeptr_testNullPtr(void) {
    void* nullVoidPtr_;
    void const* nullVoidInPtr_;
    double* nullNativePtr_;
    double const* nullInPtr_;
    double* nullOutPtr_;
    nullVoidPtr_ = NULL;
    milone_assert((((uintptr_t)nullVoidPtr_) == (size_t)0ULL), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 32, 2);
    nullVoidInPtr_ = NULL;
    milone_assert((((uintptr_t)nullVoidInPtr_) == (size_t)0ULL), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 35, 2);
    nullNativePtr_ = ((double*)NULL);
    milone_assert((((uintptr_t)nullNativePtr_) == (size_t)0ULL), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 38, 2);
    nullInPtr_ = ((double const*)NULL);
    milone_assert((((uintptr_t)nullInPtr_) == (size_t)0ULL), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 41, 2);
    nullOutPtr_ = ((double*)NULL);
    milone_assert((((uintptr_t)nullOutPtr_) == (size_t)0ULL), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 44, 2);
    return;
}

void nativeptr_nativeptr_testAsConst(void) {
    int* mp_;
    int const* kp_;
    void* mq_;
    void const* kq_;
    mp_ = ((int*)NULL);
    kp_ = ((int const*)mp_);
    milone_assert((kp_ == ((int const*)NULL)), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 50, 2);
    mq_ = NULL;
    kq_ = ((void const*)mq_);
    milone_assert((kq_ == NULL), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 55, 2);
    return;
}

void nativeptr_nativeptr_testAsMutable(void) {
    int const* kp_1;
    int* mp_1;
    void const* kq_1;
    void* mq_1;
    kp_1 = ((int const*)NULL);
    mp_1 = ((int*)kp_1);
    milone_assert((mp_1 == ((int*)NULL)), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 61, 2);
    kq_1 = NULL;
    mq_1 = ((void*)kq_1);
    milone_assert((mq_1 == NULL), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 66, 2);
    return;
}

void nativeptr_nativeptr_testEquality(void) {
    int* np_;
    int* p_;
    int const* nq_;
    int const* q_;
    np_ = ((int*)NULL);
    p_ = ((int*)(size_t)42ULL);
    milone_assert((p_ != np_), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 71, 2);
    nq_ = ((int const*)NULL);
    q_ = ((int const*)(size_t)42ULL);
    milone_assert((q_ != nq_), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 75, 2);
    return;
}

void nativeptr_nativeptr_testSizeOf(void) {
    int w_;
    int call_1;
    milone_assert((sizeof(char) == 1), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 80, 2);
    milone_assert((sizeof(uint8_t) == 1), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 81, 2);
    milone_assert((sizeof(int16_t) == 2), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 82, 2);
    milone_assert((sizeof(int) == 4), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 83, 2);
    milone_assert((sizeof(int64_t) == 8), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 84, 2);
    w_ = sizeof(uintptr_t);
    milone_assert((sizeof(void*) == w_), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 87, 2);
    milone_assert((sizeof(struct ObjectObjectTuple2_*) == w_), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 88, 2);
    milone_assert((sizeof(struct String) == (w_ * 2)), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 89, 2);
    milone_assert((sizeof(struct UnitUnitFun1) == (w_ * 2)), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 90, 2);
    milone_assert((sizeof(struct Int64UInt8UInt8Tuple3_) == 16), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 92, 2);
    call_1 = nativeptr_nativeptr_ObjectObjectTuple2MutPtrIntFun1_sizeOfPointee(((struct ObjectObjectTuple2_*)NULL));
    milone_assert((call_1 == sizeof(struct ObjectObjectTuple2_)), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 95, 2);
    return;
}

void nativeptr_nativeptr_testPtrOf(void) {
    int x_;
    int const* p_1;
    x_ = 42;
    p_1 = (&(x_));
    milone_assert(((*(p_1)) == 42), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 100, 2);
    return;
}

void nativeptr_nativeptr_testPtrSelect(void) {
    int* p_2;
    void* call_2;
    call_2 = nativeptr_nativeptr_memAlloc(4, sizeof(int));
    p_2 = ((int*)call_2);
    milone_assert(((&(p_2[0])) == p_2), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 105, 2);
    milone_assert(((((uintptr_t)(&(p_2[1]))) - ((uintptr_t)p_2)) == ((uintptr_t)sizeof(int))), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 106, 2);
    return;
}

void nativeptr_nativeptr_testPtrRead(void) {
    int* p_3;
    int const* q_1;
int array[] = {1, 2, 4, 8, 16};    p_3 = array;
    milone_assert(((*(p_3)) == 1), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 112, 2);
    milone_assert((p_3[0] == 1), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 113, 2);
    milone_assert((p_3[4] == 16), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 114, 2);
    q_1 = ((int const*)p_3);
    milone_assert(((*(q_1)) == 1), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 117, 2);
    milone_assert((q_1[2] == 4), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 118, 2);
    return;
}

void nativeptr_nativeptr_testPtrWrite(void) {
    int* p_4;
    int* q_2;
    int* q_3;
int data[8] = { 0 };    p_4 = data;
    (*(p_4)) = 42;
    milone_assert(((*(p_4)) == 42), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 125, 2);
    p_4[0] = 43;
    milone_assert(((*(p_4)) == 43), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 127, 2);
    p_4[3] = 39;
    milone_assert((p_4[3] == 39), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 129, 2);
    q_2 = &data[7];
    (*(q_2)) = 77;
    q_3 = ((int*)q_2);
    milone_assert(((*(q_3)) == 77), (struct String){.str = "nativeptr/nativeptr.milone", .len = 26}, 134, 2);
    return;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    nativeptr_nativeptr_testBasic();
    nativeptr_nativeptr_testVoidPtrAvailable();
    nativeptr_nativeptr_testNullPtr();
    nativeptr_nativeptr_testAsConst();
    nativeptr_nativeptr_testAsMutable();
    nativeptr_nativeptr_testEquality();
    nativeptr_nativeptr_testSizeOf();
    nativeptr_nativeptr_testPtrOf();
    nativeptr_nativeptr_testPtrSelect();
    nativeptr_nativeptr_testPtrRead();
    nativeptr_nativeptr_testPtrWrite();
    return 0;
}
