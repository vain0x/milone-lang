#include "milone.h"

void* int_array_new(int);

void* rawIntArrayNew_(int len_);

int int_array_get(void*, int);

int rawIntArrayGet_(void* array_, int index_);

void int_array_set(void*, int, int);

int rawIntArraySet_(void* array_1, int index_1, int value_);

int intCompare_(void const* l_, void const* r_);

void qsort(void*, uintptr_t, uintptr_t, int(*)(void const*, void const*));

int rawIntArraySort_(void* array_2, int len_1);

int main();

void* rawIntArrayNew_(int len_) {
    void* int_array_new_result_ = int_array_new(len_);
    return int_array_new_result_;
}

int rawIntArrayGet_(void* array_, int index_) {
    int int_array_get_result_ = int_array_get(array_, index_);
    return int_array_get_result_;
}

int rawIntArraySet_(void* array_1, int index_1, int value_) {
    int_array_set(array_1, index_1, value_);
    return 0;
}

int intCompare_(void const* l_, void const* r_) {
    return int_compare((*(((int*)((void*)l_)))), (*(((int*)((void*)r_)))));
}

int rawIntArraySort_(void* array_2, int len_1) {
    qsort(array_2, ((uintptr_t)len_1), ((uintptr_t)4), intCompare_);
    return 0;
}

int main() {
    int len_2 = 5;
    void* call_ = rawIntArrayNew_(len_2);
    void* array_3 = call_;
    int call_1 = rawIntArraySet_(array_3, 0, 3);
    int call_2 = rawIntArraySet_(array_3, 1, 1);
    int call_3 = rawIntArraySet_(array_3, 2, 4);
    int call_4 = rawIntArraySet_(array_3, 3, 1);
    int call_5 = rawIntArraySet_(array_3, 4, 5);
    int call_6 = rawIntArraySort_(array_3, len_2);
    int call_7 = rawIntArrayGet_(array_3, 0);
    milone_assert((call_7 == 1), 28, 2);
    int call_8 = rawIntArrayGet_(array_3, 1);
    milone_assert((call_8 == 1), 29, 2);
    int call_9 = rawIntArrayGet_(array_3, 2);
    milone_assert((call_9 == 3), 30, 2);
    int call_10 = rawIntArrayGet_(array_3, 3);
    milone_assert((call_10 == 4), 31, 2);
    int call_11 = rawIntArrayGet_(array_3, 4);
    milone_assert((call_11 == 5), 32, 2);
    return 0;
}
