// Runtime library for parallel primitives.

#include <cassert>

#include <tbb/parallel_for.h>

extern "C" void *milone_region_alloc(int, size_t);

struct IntIntFun1 {
    int (*fun)(void const *env, int arg);
    void const *env;
};

extern "C" int *milone_parallel_for_int(int start, int endIndex,
                                        struct IntIntFun1 f) {
    int len = endIndex - start;
    assert(len >= 0);

    auto output = (int *)milone_region_alloc(len, sizeof(int));
    tbb::parallel_for(0, len, [start, &f, &output](int i) {
        int n = start + i;
        output[i] = f.fun(f.env, n);
    });
    return output;
}
