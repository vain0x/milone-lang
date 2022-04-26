#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct ObjectObjectTuple2_;

typedef void(*VoidFunPtr0)(void);

typedef void const *(*VoidConstPtrVoidConstPtrVoidConstPtrFunPtr2)(void const *, void const *);

typedef void(*VoidConstPtrVoidFunPtr1)(void const *);

struct UnitUnitFun1;

struct Int64UInt8UInt8Tuple3_;

int32_t nativeptr_nativeptr_ObjectObjectTuple2MutPtrInt32Fun1_sizeOfPointee(struct ObjectObjectTuple2_ *ptr_);

void *milone_region_alloc(uint32_t, uint32_t);

void *nativeptr_nativeptr_memAlloc(uint32_t count_, uint32_t size_);

void *memset(void *, int32_t, uintptr_t);

void nativeptr_nativeptr_memSet(void *dest_, uint8_t value_, uint32_t count_1);

char *strcpy(char *, char const *);

char *nativeptr_nativeptr_strcpy(char *dest_1, char const *src_);

void nativeptr_nativeptr_testBasic(void);

void nativeptr_nativeptr_testVoidPtrAvailable(void);

void nativeptr_nativeptr_testNullPtr(void);

void nativeptr_nativeptr_testPtrInvalid(void);

void nativeptr_nativeptr_testPtrCast(void);

void nativeptr_nativeptr_testAsIn(void);

void nativeptr_nativeptr_testAsNative(void);

void nativeptr_nativeptr_testPtrDistance(void);

void nativeptr_nativeptr_testEquality(void);

void nativeptr_nativeptr_testSizeOf(void);

void nativeptr_nativeptr_testPtrOf(void);

void nativeptr_nativeptr_testPtrSelect(void);

void nativeptr_nativeptr_testPtrRead(void);

void nativeptr_nativeptr_testPtrWrite(void);

int32_t *Std_Ptr_UInt32Int32OutPtrFun1_regionAlloc(uint32_t);

void nativeptr_nativeptr_testPtrRegionAlloc(void);

void nativeptr_nativeptr_testPtrAddress(void);

int main(int argc, char **argv);

struct ObjectObjectTuple2_ {
    void const *t0;
    void const *t1;
};

struct UnitUnitFun1 {
    VoidConstPtrVoidFunPtr1 fun;
    void const *env;
};

struct Int64UInt8UInt8Tuple3_ {
    int64_t t0;
    uint8_t t1;
    uint8_t t2;
};

int32_t nativeptr_nativeptr_ObjectObjectTuple2MutPtrInt32Fun1_sizeOfPointee(struct ObjectObjectTuple2_ *ptr_) {
    return sizeof(struct ObjectObjectTuple2_);
}

void *nativeptr_nativeptr_memAlloc(uint32_t count_, uint32_t size_) {
    void *milone_region_alloc_result;
    milone_region_alloc_result = milone_region_alloc(count_, size_);
    return milone_region_alloc_result;
}

void nativeptr_nativeptr_memSet(void *dest_, uint8_t value_, uint32_t count_1) {
    void *memset_result;
    memset_result = memset(dest_, ((int32_t)value_), ((uintptr_t)count_1));
    return;
}

char *nativeptr_nativeptr_strcpy(char *dest_1, char const *src_) {
    char *strcpy_result;
    strcpy_result = strcpy(dest_1, src_);
    return strcpy_result;
}

void nativeptr_nativeptr_testBasic(void) {
    void *buf_;
    void *call_;
    uintptr_t address_1;
    call_ = nativeptr_nativeptr_memAlloc((uint32_t)1U, (uint32_t)8U);
    buf_ = call_;
    nativeptr_nativeptr_memSet(buf_, (uint8_t)255U, (uint32_t)8U);
    if (((*(((int32_t const *)buf_))) != -1)) milone_assert_error("nativeptr/nativeptr.milone", 21, 2);
    address_1 = ((uintptr_t)buf_);
    if ((address_1 == (size_t)0ULL)) milone_assert_error("nativeptr/nativeptr.milone", 24, 2);
    return;
}

void nativeptr_nativeptr_testVoidPtrAvailable(void) {
    void *mutEnv_;
    void const *constEnv_;
    mutEnv_ = ((void *)(size_t)42ULL);
    constEnv_ = ((void const *)mutEnv_);
    if ((((uintptr_t)constEnv_) != (size_t)42ULL)) milone_assert_error("nativeptr/nativeptr.milone", 29, 2);
    return;
}

void nativeptr_nativeptr_testNullPtr(void) {
    void *nullVoidPtr_;
    void const *nullVoidInPtr_;
    double *nullNativePtr_;
    double const *nullInPtr_;
    double *nullOutPtr_;
    VoidFunPtr0 nullFunPtr_;
    nullVoidPtr_ = NULL;
    if ((((uintptr_t)nullVoidPtr_) != (size_t)0ULL)) milone_assert_error("nativeptr/nativeptr.milone", 33, 2);
    nullVoidInPtr_ = NULL;
    if ((((uintptr_t)nullVoidInPtr_) != (size_t)0ULL)) milone_assert_error("nativeptr/nativeptr.milone", 36, 2);
    nullNativePtr_ = ((double *)NULL);
    if ((((uintptr_t)nullNativePtr_) != (size_t)0ULL)) milone_assert_error("nativeptr/nativeptr.milone", 39, 2);
    nullInPtr_ = ((double const *)NULL);
    if ((((uintptr_t)nullInPtr_) != (size_t)0ULL)) milone_assert_error("nativeptr/nativeptr.milone", 42, 2);
    nullOutPtr_ = ((double *)NULL);
    if ((((uintptr_t)nullOutPtr_) != (size_t)0ULL)) milone_assert_error("nativeptr/nativeptr.milone", 45, 2);
    nullFunPtr_ = ((VoidFunPtr0)NULL);
    if ((((uintptr_t)nullFunPtr_) != (size_t)0ULL)) milone_assert_error("nativeptr/nativeptr.milone", 48, 2);
    return;
}

void nativeptr_nativeptr_testPtrInvalid(void) {
    int64_t *danglingPtr_;
    int32_t n_;
    uintptr_t address_;
    int32_t *exposedPtr_;
    uintptr_t address_2;
    uintptr_t address_3;
    danglingPtr_ = ((int64_t *)(size_t)8ULL);
    address_2 = ((uintptr_t)danglingPtr_);
    if ((address_2 != (size_t)8ULL)) milone_assert_error("nativeptr/nativeptr.milone", 52, 2);
    n_ = 42;
    address_3 = ((uintptr_t)(&(n_)));
    address_ = address_3;
    exposedPtr_ = ((int32_t *)address_);
    if (((*(exposedPtr_)) != 42)) milone_assert_error("nativeptr/nativeptr.milone", 57, 2);
    return;
}

void nativeptr_nativeptr_testPtrCast(void) {
    void *voidPtr_;
    void const *voidInPtr_;
    int32_t *intOutPtr_;
    int32_t *intPtr_;
    void const **objOutPtr_;
    VoidConstPtrVoidConstPtrVoidConstPtrFunPtr2 funPtr_;
    uint32_t *uintPtrLinear_;
    voidPtr_ = ((void *)((uint8_t *)NULL));
    voidInPtr_ = ((void const *)((int32_t const *)NULL));
    intOutPtr_ = ((int32_t *)((int32_t *)NULL));
    intPtr_ = ((int32_t *)NULL);
    objOutPtr_ = ((void const **)((struct String const *)NULL));
    funPtr_ = ((VoidConstPtrVoidConstPtrVoidConstPtrFunPtr2)NULL);
    uintPtrLinear_ = ((uint32_t *)NULL);
    return;
}

void nativeptr_nativeptr_testAsIn(void) {
    int32_t *mp_;
    int32_t const *kp_;
    void *mq_;
    void const *kq_;
    mp_ = ((int32_t *)NULL);
    kp_ = ((int32_t const *)mp_);
    if ((kp_ != ((int32_t const *)NULL))) milone_assert_error("nativeptr/nativeptr.milone", 81, 2);
    mq_ = NULL;
    kq_ = ((void const *)mq_);
    if ((kq_ != NULL)) milone_assert_error("nativeptr/nativeptr.milone", 86, 2);
    return;
}

void nativeptr_nativeptr_testAsNative(void) {
    int32_t const *kp_1;
    int32_t *mp_1;
    void const *kq_1;
    void *mq_1;
    kp_1 = ((int32_t const *)NULL);
    mp_1 = ((int32_t *)kp_1);
    if ((mp_1 != ((int32_t *)NULL))) milone_assert_error("nativeptr/nativeptr.milone", 92, 2);
    kq_1 = NULL;
    mq_1 = ((void *)kq_1);
    if ((mq_1 != NULL)) milone_assert_error("nativeptr/nativeptr.milone", 97, 2);
    return;
}

void nativeptr_nativeptr_testPtrDistance(void) {
    int32_t *p_;
    int32_t *q_;
    p_ = ((int32_t *)(size_t)0x8000ULL);
    q_ = ((int32_t *)(size_t)0x8020ULL);
    if (((p_ - p_) != 0LL)) milone_assert_error("nativeptr/nativeptr.milone", 102, 2);
    if (((q_ - p_) != 8LL)) milone_assert_error("nativeptr/nativeptr.milone", 103, 2);
    if (((p_ - q_) != -8LL)) milone_assert_error("nativeptr/nativeptr.milone", 104, 2);
    return;
}

void nativeptr_nativeptr_testEquality(void) {
    int32_t *np_;
    int32_t *p_1;
    int32_t const *nq_;
    int32_t const *q_1;
    np_ = ((int32_t *)NULL);
    p_1 = ((int32_t *)(size_t)42ULL);
    if ((p_1 == np_)) milone_assert_error("nativeptr/nativeptr.milone", 109, 2);
    nq_ = ((int32_t const *)NULL);
    q_1 = ((int32_t const *)(size_t)42ULL);
    if ((q_1 == nq_)) milone_assert_error("nativeptr/nativeptr.milone", 113, 2);
    return;
}

void nativeptr_nativeptr_testSizeOf(void) {
    int32_t w_;
    int32_t call_1;
    if ((sizeof(char) != 1)) milone_assert_error("nativeptr/nativeptr.milone", 118, 2);
    if ((sizeof(uint8_t) != 1)) milone_assert_error("nativeptr/nativeptr.milone", 119, 2);
    if ((sizeof(int16_t) != 2)) milone_assert_error("nativeptr/nativeptr.milone", 120, 2);
    if ((sizeof(int32_t) != 4)) milone_assert_error("nativeptr/nativeptr.milone", 121, 2);
    if ((sizeof(int64_t) != 8)) milone_assert_error("nativeptr/nativeptr.milone", 122, 2);
    w_ = sizeof(uintptr_t);
    if ((sizeof(void *) != w_)) milone_assert_error("nativeptr/nativeptr.milone", 125, 2);
    if ((sizeof(struct ObjectObjectTuple2_ *) != w_)) milone_assert_error("nativeptr/nativeptr.milone", 126, 2);
    if ((sizeof(struct String) != (w_ * 2))) milone_assert_error("nativeptr/nativeptr.milone", 127, 2);
    if ((sizeof(struct UnitUnitFun1) != (w_ * 2))) milone_assert_error("nativeptr/nativeptr.milone", 128, 2);
    if ((sizeof(struct Int64UInt8UInt8Tuple3_) != 16)) milone_assert_error("nativeptr/nativeptr.milone", 130, 2);
    call_1 = nativeptr_nativeptr_ObjectObjectTuple2MutPtrInt32Fun1_sizeOfPointee(((struct ObjectObjectTuple2_ *)NULL));
    if ((call_1 != sizeof(struct ObjectObjectTuple2_))) milone_assert_error("nativeptr/nativeptr.milone", 133, 2);
    return;
}

void nativeptr_nativeptr_testPtrOf(void) {
    int32_t x_;
    int32_t const *p_2;
    x_ = 42;
    p_2 = (&(x_));
    if (((*(p_2)) != 42)) milone_assert_error("nativeptr/nativeptr.milone", 138, 2);
    return;
}

void nativeptr_nativeptr_testPtrSelect(void) {
    int32_t *p_3;
    void *call_2;
    uintptr_t address_4;
    uintptr_t address_5;
    call_2 = nativeptr_nativeptr_memAlloc((uint32_t)4U, ((uint32_t)sizeof(int32_t)));
    p_3 = ((int32_t *)call_2);
    if (((&(p_3[0])) != p_3)) milone_assert_error("nativeptr/nativeptr.milone", 144, 2);
    address_4 = ((uintptr_t)(&(p_3[1])));
    address_5 = ((uintptr_t)p_3);
    if (((address_4 - address_5) != ((uintptr_t)sizeof(int32_t)))) milone_assert_error("nativeptr/nativeptr.milone", 145, 2);
    return;
}

void nativeptr_nativeptr_testPtrRead(void) {
    int32_t *p_4;
    int32_t const *q_2;
int array[] = {1, 2, 4, 8, 16};    p_4 = array;
    if (((*(p_4)) != 1)) milone_assert_error("nativeptr/nativeptr.milone", 151, 2);
    if ((p_4[0] != 1)) milone_assert_error("nativeptr/nativeptr.milone", 152, 2);
    if ((p_4[4] != 16)) milone_assert_error("nativeptr/nativeptr.milone", 153, 2);
    q_2 = ((int32_t const *)p_4);
    if (((*(q_2)) != 1)) milone_assert_error("nativeptr/nativeptr.milone", 156, 2);
    if ((q_2[2] != 4)) milone_assert_error("nativeptr/nativeptr.milone", 157, 2);
    return;
}

void nativeptr_nativeptr_testPtrWrite(void) {
    int32_t *p_5;
    int32_t *q_3;
    int32_t *q_4;
int data[8] = { 0 };    p_5 = data;
    (*(p_5)) = 42;
    if (((*(p_5)) != 42)) milone_assert_error("nativeptr/nativeptr.milone", 164, 2);
    p_5[0] = 43;
    if (((*(p_5)) != 43)) milone_assert_error("nativeptr/nativeptr.milone", 166, 2);
    p_5[3] = 39;
    if ((p_5[3] != 39)) milone_assert_error("nativeptr/nativeptr.milone", 168, 2);
    q_3 = &data[7];
    (*(q_3)) = 77;
    q_4 = ((int32_t *)q_3);
    if (((*(q_4)) != 77)) milone_assert_error("nativeptr/nativeptr.milone", 173, 2);
    return;
}

void nativeptr_nativeptr_testPtrRegionAlloc(void) {
    int32_t *p_6;
    int32_t *p_7;
    int32_t *call_3;
    call_3 = Std_Ptr_UInt32Int32OutPtrFun1_regionAlloc((uint32_t)2U);
    p_6 = call_3;
    p_6[0] = 42;
    p_6[1] = 43;
    p_7 = ((int32_t *)p_6);
    if (((*(p_7)) != 42)) milone_assert_error("nativeptr/nativeptr.milone", 182, 2);
    if ((p_7[1] != 43)) milone_assert_error("nativeptr/nativeptr.milone", 183, 2);
    return;
}

void nativeptr_nativeptr_testPtrAddress(void) {
    int32_t n_1;
    uintptr_t address_6;
    n_1 = 42;
    address_6 = ((uintptr_t)(&(n_1)));
    return;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    nativeptr_nativeptr_testBasic();
    nativeptr_nativeptr_testVoidPtrAvailable();
    nativeptr_nativeptr_testNullPtr();
    nativeptr_nativeptr_testPtrInvalid();
    nativeptr_nativeptr_testPtrCast();
    nativeptr_nativeptr_testAsIn();
    nativeptr_nativeptr_testAsNative();
    nativeptr_nativeptr_testPtrDistance();
    nativeptr_nativeptr_testEquality();
    nativeptr_nativeptr_testSizeOf();
    nativeptr_nativeptr_testPtrOf();
    nativeptr_nativeptr_testPtrSelect();
    nativeptr_nativeptr_testPtrRead();
    nativeptr_nativeptr_testPtrWrite();
    nativeptr_nativeptr_testPtrRegionAlloc();
    nativeptr_nativeptr_testPtrAddress();
    return 0;
}
