#include "milone.h"

struct IntVoidMutPtrFun1;

struct VoidMutPtrIntIntFun2;

struct VoidMutPtrIntIntUnitFun3;

struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6;

void* fun_4(void const*, int);

int fun_5(void const*, void*, int);

char fun_6(void const*, void*, int, int);

char Competitive_Helpers_vectorTest(char);

char Competitive_SegTree_segTreeTest(char);

char Competitive_ABC140A_abc140aTest(char);

char Competitive_ABC140B_abc140bTest(char);

char Competitive_ABC140E_abc140eTest(char);

int milone_main();

struct IntVoidMutPtrFun1 {
    void*(*fun)(void const*, int);
    void const* env;
};

struct VoidMutPtrIntIntFun2 {
    int(*fun)(void const*, void*, int);
    void const* env;
};

struct VoidMutPtrIntIntUnitFun3 {
    char(*fun)(void const*, void*, int, int);
    void const* env;
};

struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6 {
    int t0;
    int t1;
    struct IntVoidMutPtrFun1 t2;
    struct VoidMutPtrIntIntFun2 t3;
    struct VoidMutPtrIntIntUnitFun3 t4;
    char t5;
};

void const* Competitive_Helpers_unitObj;

struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6 Competitive_Helpers_typeInt;

int milone_main() {
    Competitive_Helpers_unitObj = NULL;
    struct IntVoidMutPtrFun1 fun_39 = (struct IntVoidMutPtrFun1){.fun = fun_4, .env = NULL};
    struct VoidMutPtrIntIntFun2 fun_40 = (struct VoidMutPtrIntIntFun2){.fun = fun_5, .env = NULL};
    struct VoidMutPtrIntIntUnitFun3 fun_41 = (struct VoidMutPtrIntIntUnitFun3){.fun = fun_6, .env = NULL};
    struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6 tuple_43 = (struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6){.t0 = 0, .t1 = 4, .t2 = fun_39, .t3 = fun_40, .t4 = fun_41, .t5 = 0};
    Competitive_Helpers_typeInt = tuple_43;
    char call_373 = Competitive_Helpers_vectorTest(0);
    char call_374 = Competitive_SegTree_segTreeTest(0);
    char call_375 = Competitive_ABC140A_abc140aTest(0);
    char call_376 = Competitive_ABC140B_abc140bTest(0);
    char call_377 = Competitive_ABC140E_abc140eTest(0);
    return 0;
}
