#include "milone.h"

struct IntIntIntFun2;

struct IntIntIntObjectUnitTuple5_;

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4_;

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_;

struct IntList;

struct IntList;

int fun_20(int arg_135, int arg_136);

int fun_17(void const* env_17, int arg_33, int arg_34);

int segTreeGet_(int, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_);

int go_3(int n_5, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ a_1, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ b_1, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ c_1, int sum_3, int i_8);

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4_ segItemTypeNew_(int, struct IntIntIntFun2);

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ segTreeOfList_(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4_, struct IntList const*);

int Competitive_ABC140B_abc140bSolve(int n_5, struct IntList const* a_, struct IntList const* b_, struct IntList const* c_);

int listLength_(struct IntList const*);

int f_(struct IntList const* a_2, struct IntList const* b_2, struct IntList const* c_2);

bool case1_(char arg_143);

bool case2_(char arg_144);

bool case3_(char arg_145);

char Competitive_ABC140B_abc140bTest(char arg_146);

int Competitive_Helpers_scanInt(char);

struct IntList const* Competitive_Helpers_scanIntList(int);

char Competitive_ABC140B_abc140bMain(char arg_147);

struct IntIntIntFun2 {
    int(*fun)(void const*, int, int);
    void const* env;
};

struct IntIntIntObjectUnitTuple5_ {
    int t0;
    int t1;
    int t2;
    void const* t3;
    char t4;
};

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4_ {
    struct IntIntIntFun2 t0;
    struct IntIntIntObjectUnitTuple5_ t1;
    void const* t2;
    char t3;
};

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ {
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4_ t0;
    struct IntIntIntObjectUnitTuple5_ t1;
    char t2;
};

struct IntList {
    int head;
    struct IntList const* tail;
};

int fun_20(int arg_135, int arg_136) {
    return 0;
}

int fun_17(void const* env_17, int arg_33, int arg_34) {
    int call_344 = fun_20(arg_33, arg_34);
    return call_344;
}

int go_3(int n_5, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ a_1, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ b_1, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ c_1, int sum_3, int i_8) {
tailrec_313:;
    int if_83;
    if ((i_8 == n_5)) {
        goto then_315;
    } else {
        goto else_316;
    }
then_315:;
    if_83 = sum_3;
    goto if_next_314;
else_316:;
    int call_345 = segTreeGet_(i_8, a_1);
    int ai_ = call_345;
    int call_346 = segTreeGet_((ai_ - 1), b_1);
    int eat_ = call_346;
    bool if_84;
    if (((i_8 + 1) < n_5)) {
        goto then_318;
    } else {
        goto else_319;
    }
then_318:;
    int call_347 = segTreeGet_((i_8 + 1), a_1);
    if_84 = (call_347 == (ai_ + 1));
    goto if_next_317;
else_319:;
    if_84 = false;
    goto if_next_317;
if_next_317:;
    int if_85;
    if (if_84) {
        goto then_321;
    } else {
        goto else_322;
    }
then_321:;
    int call_348 = segTreeGet_((ai_ - 1), c_1);
    if_85 = call_348;
    goto if_next_320;
else_322:;
    if_85 = 0;
    goto if_next_320;
if_next_320:;
    int bonus_ = if_85;
    int arg_137 = n_5;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ arg_138 = a_1;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ arg_139 = b_1;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ arg_140 = c_1;
    int arg_141 = ((sum_3 + eat_) + bonus_);
    int arg_142 = (i_8 + 1);
    n_5 = arg_137;
    a_1 = arg_138;
    b_1 = arg_139;
    c_1 = arg_140;
    sum_3 = arg_141;
    i_8 = arg_142;
    goto tailrec_313;
if_next_314:;
    return if_83;
}

int Competitive_ABC140B_abc140bSolve(int n_5, struct IntList const* a_, struct IntList const* b_, struct IntList const* c_) {
    struct IntIntIntFun2 fun_35 = (struct IntIntIntFun2){.fun = fun_17, .env = NULL};
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4_ call_349 = segItemTypeNew_(0, fun_35);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4_ segItemTypeInt_2 = call_349;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ call_350 = segTreeOfList_(segItemTypeInt_2, a_);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ a_1 = call_350;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ call_351 = segTreeOfList_(segItemTypeInt_2, b_);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ b_1 = call_351;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ call_352 = segTreeOfList_(segItemTypeInt_2, c_);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ c_1 = call_352;
    int call_353 = go_3(n_5, a_1, b_1, c_1, 0, 0);
    return call_353;
}

int f_(struct IntList const* a_2, struct IntList const* b_2, struct IntList const* c_2) {
    int call_354 = listLength_(a_2);
    int n_6 = call_354;
    int call_355 = listLength_(b_2);
    milone_assert((call_355 == n_6), 32, 4);
    int call_356 = listLength_(c_2);
    milone_assert((call_356 == (n_6 - 1)), 33, 4);
    int call_357 = Competitive_ABC140B_abc140bSolve(n_6, a_2, b_2, c_2);
    return call_357;
}

bool case1_(char arg_143) {
    struct IntList const* list_72 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_72))) = (struct IntList){.head = 2, .tail = NULL};
    struct IntList const* list_71 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_71))) = (struct IntList){.head = 1, .tail = list_72};
    struct IntList const* list_70 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_70))) = (struct IntList){.head = 3, .tail = list_71};
    struct IntList const* a_3 = list_70;
    struct IntList const* list_75 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_75))) = (struct IntList){.head = 4, .tail = NULL};
    struct IntList const* list_74 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_74))) = (struct IntList){.head = 5, .tail = list_75};
    struct IntList const* list_73 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_73))) = (struct IntList){.head = 2, .tail = list_74};
    struct IntList const* b_3 = list_73;
    struct IntList const* list_77 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_77))) = (struct IntList){.head = 6, .tail = NULL};
    struct IntList const* list_76 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_76))) = (struct IntList){.head = 3, .tail = list_77};
    struct IntList const* c_3 = list_76;
    int call_358 = f_(a_3, b_3, c_3);
    return (call_358 == 14);
}

bool case2_(char arg_144) {
    struct IntList const* list_81 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_81))) = (struct IntList){.head = 1, .tail = NULL};
    struct IntList const* list_80 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_80))) = (struct IntList){.head = 4, .tail = list_81};
    struct IntList const* list_79 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_79))) = (struct IntList){.head = 3, .tail = list_80};
    struct IntList const* list_78 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_78))) = (struct IntList){.head = 2, .tail = list_79};
    struct IntList const* a_4 = list_78;
    struct IntList const* list_85 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_85))) = (struct IntList){.head = 24, .tail = NULL};
    struct IntList const* list_84 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_84))) = (struct IntList){.head = 8, .tail = list_85};
    struct IntList const* list_83 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_83))) = (struct IntList){.head = 5, .tail = list_84};
    struct IntList const* list_82 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_82))) = (struct IntList){.head = 13, .tail = list_83};
    struct IntList const* b_4 = list_82;
    struct IntList const* list_88 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_88))) = (struct IntList){.head = 15, .tail = NULL};
    struct IntList const* list_87 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_87))) = (struct IntList){.head = 9, .tail = list_88};
    struct IntList const* list_86 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_86))) = (struct IntList){.head = 45, .tail = list_87};
    struct IntList const* c_4 = list_86;
    int call_359 = f_(a_4, b_4, c_4);
    return (call_359 == 74);
}

bool case3_(char arg_145) {
    struct IntList const* list_90 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_90))) = (struct IntList){.head = 2, .tail = NULL};
    struct IntList const* list_89 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_89))) = (struct IntList){.head = 1, .tail = list_90};
    struct IntList const* a_5 = list_89;
    struct IntList const* list_92 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_92))) = (struct IntList){.head = 50, .tail = NULL};
    struct IntList const* list_91 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_91))) = (struct IntList){.head = 50, .tail = list_92};
    struct IntList const* b_5 = list_91;
    struct IntList const* list_93 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_93))) = (struct IntList){.head = 50, .tail = NULL};
    struct IntList const* c_5 = list_93;
    int call_360 = f_(a_5, b_5, c_5);
    return (call_360 == 150);
}

char Competitive_ABC140B_abc140bTest(char arg_146) {
    bool call_361 = case1_(0);
    milone_assert(call_361, 42, 2);
    bool call_362 = case2_(0);
    milone_assert(call_362, 50, 2);
    bool call_363 = case3_(0);
    milone_assert(call_363, 58, 2);
    return 0;
}

char Competitive_ABC140B_abc140bMain(char arg_147) {
    int call_364 = Competitive_Helpers_scanInt(0);
    int n_7 = call_364;
    struct IntList const* call_365 = Competitive_Helpers_scanIntList(n_7);
    struct IntList const* a_6 = call_365;
    struct IntList const* call_366 = Competitive_Helpers_scanIntList(n_7);
    struct IntList const* b_6 = call_366;
    struct IntList const* call_367 = Competitive_Helpers_scanIntList((n_7 - 1));
    struct IntList const* c_6 = call_367;
    int call_368 = Competitive_ABC140B_abc140bSolve(n_7, a_6, b_6, c_6);
    int m_3 = call_368;
    printf("%d\n", m_3);
    return 0;
}
