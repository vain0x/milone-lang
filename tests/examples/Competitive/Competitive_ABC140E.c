#include "milone.h"

struct IntIntIntFun2;

struct IntIntIntObjectUnitTuple5_;

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4_;

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_;

struct IntList;

struct IntList;

int fun_20(int arg_116, int arg_117);

int fun_15(void const* env_15, int arg_29, int arg_30);

int Competitive_Helpers_intMax(int , int );

int fun_16(void const* env_16, int arg_31, int arg_32);

int Competitive_Helpers_intMin(int , int );

int fun_17(void const* env_17, int arg_33, int arg_34);

int segTreeGet_(int , struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ );

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ segTreeSet_(int , int , struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ );

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ go_5(int n_7, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ perm_2, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ pos_1, int i_7);

int segTreeSum_(int , int , struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ );

int go_4(int n_7, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ pos_, int sum_2, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ prev_1, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ next_1, int p_);

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4_ segItemTypeNew_(int , struct IntIntIntFun2 );

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ segTreeOfList_(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4_ , struct IntList const* );

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ segTreeInsert_(int , int , struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ );

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ segTreePush_(int , struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ );

int segTreeToLength_(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ );

struct IntList const* listReplicate_(int , int );

int Competitive_ABC140E_abc140eSolve(int n_7, struct IntList const* perm_);

int listLength_(struct IntList const* );

bool solve_(struct IntList const* p_1, int expected_1);

void Competitive_ABC140E_abc140eTest(void);

int Competitive_Helpers_scanInt(void);

struct IntList const* Competitive_Helpers_scanIntList(int );

void Competitive_ABC140E_abc140eMain(void);

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

int fun_20(int arg_116, int arg_117) {
    return 0;
}

int fun_15(void const* env_15, int arg_29, int arg_30) {
    int call_321 = fun_20(arg_29, arg_30);
    return call_321;
}

int fun_16(void const* env_16, int arg_31, int arg_32) {
    int call_322 = Competitive_Helpers_intMax(arg_31, arg_32);
    return call_322;
}

int fun_17(void const* env_17, int arg_33, int arg_34) {
    int call_323 = Competitive_Helpers_intMin(arg_33, arg_34);
    return call_323;
}

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ go_5(int n_7, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ perm_2, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ pos_1, int i_7) {
tailrec_306:;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ if_81;
    if ((i_7 == (n_7 + 2))) {
        goto then_308;
    } else {
        goto else_309;
    }
then_308:;
    if_81 = pos_1;
    goto if_next_307;
else_309:;
    int call_324 = segTreeGet_(i_7, perm_2);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ call_325 = segTreeSet_(call_324, i_7, pos_1);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ pos_2 = call_325;
    int arg_118 = n_7;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ arg_119 = perm_2;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ arg_120 = pos_2;
    int arg_121 = (i_7 + 1);
    n_7 = arg_118;
    perm_2 = arg_119;
    pos_1 = arg_120;
    i_7 = arg_121;
    goto tailrec_306;
if_next_307:;
    return if_81;
}

int go_4(int n_7, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ pos_, int sum_2, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ prev_1, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ next_1, int p_) {
tailrec_310:;
    int if_82;
    if ((p_ < 1)) {
        goto then_312;
    } else {
        goto else_313;
    }
then_312:;
    if_82 = sum_2;
    goto if_next_311;
else_313:;
    int call_326 = segTreeGet_(p_, pos_);
    int i_8 = call_326;
    int call_327 = segTreeSum_(0, i_8, prev_1);
    int x_11 = call_327;
    int call_328 = segTreeSum_(0, x_11, prev_1);
    int w_ = call_328;
    bool if_83;
    if ((x_11 >= w_)) {
        goto then_315;
    } else {
        goto else_316;
    }
then_315:;
    if_83 = (x_11 < i_8);
    goto if_next_314;
else_316:;
    if_83 = false;
    goto if_next_314;
if_next_314:;
    milone_assert(if_83, 58, 6);
    int call_329 = segTreeSum_((i_8 + 1), (n_7 + 2), next_1);
    int y_5 = call_329;
    int call_330 = segTreeSum_((y_5 + 1), (n_7 + 2), next_1);
    int z_ = call_330;
    bool if_84;
    if ((i_8 < y_5)) {
        goto then_318;
    } else {
        goto else_319;
    }
then_318:;
    if_84 = (z_ >= y_5);
    goto if_next_317;
else_319:;
    if_84 = false;
    goto if_next_317;
if_next_317:;
    milone_assert(if_84, 62, 6);
    int count_ = (((x_11 - w_) * (y_5 - i_8)) + ((i_8 - x_11) * (z_ - y_5)));
    int sum_3 = (sum_2 + (count_ * p_));
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ call_331 = segTreeSet_(i_8, i_8, prev_1);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ prev_2 = call_331;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ call_332 = segTreeSet_(i_8, i_8, next_1);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ next_2 = call_332;
    int arg_122 = n_7;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ arg_123 = pos_;
    int arg_124 = sum_3;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ arg_125 = prev_2;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ arg_126 = next_2;
    int arg_127 = (p_ - 1);
    n_7 = arg_122;
    pos_ = arg_123;
    sum_2 = arg_124;
    prev_1 = arg_125;
    next_1 = arg_126;
    p_ = arg_127;
    goto tailrec_310;
if_next_311:;
    return if_82;
}

int Competitive_ABC140E_abc140eSolve(int n_7, struct IntList const* perm_) {
    struct IntIntIntFun2 fun_33 = (struct IntIntIntFun2){.fun = fun_15, .env = NULL};
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4_ call_333 = segItemTypeNew_(0, fun_33);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4_ segItemTypeInt_2 = call_333;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ call_334 = segTreeOfList_(segItemTypeInt_2, perm_);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ perm_1 = call_334;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ call_335 = segTreeInsert_(0, (n_7 + 1), perm_1);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ call_336 = segTreePush_((n_7 + 2), call_335);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ perm_2 = call_336;
    int call_337 = segTreeToLength_(perm_2);
    milone_assert((call_337 == (n_7 + 2)), 22, 2);
    struct IntIntIntFun2 fun_34 = (struct IntIntIntFun2){.fun = fun_16, .env = NULL};
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4_ call_338 = segItemTypeNew_(0, fun_34);
    struct IntList const* call_339 = listReplicate_(0, (n_7 + 2));
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ call_340 = segTreeOfList_(call_338, call_339);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ prev_ = call_340;
    struct IntIntIntFun2 fun_35 = (struct IntIntIntFun2){.fun = fun_17, .env = NULL};
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4_ call_341 = segItemTypeNew_((n_7 + 1), fun_35);
    struct IntList const* call_342 = listReplicate_((n_7 + 1), (n_7 + 2));
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ call_343 = segTreeOfList_(call_341, call_342);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ next_ = call_343;
    struct IntList const* call_344 = listReplicate_(0, (n_7 + 3));
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ call_345 = segTreeOfList_(segItemTypeInt_2, call_344);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ pos_3 = call_345;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ call_346 = go_5(n_7, perm_2, pos_3, 0);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ pos_ = call_346;
    int call_347 = go_4(n_7, pos_, 0, prev_, next_, n_7);
    return call_347;
}

bool solve_(struct IntList const* p_1, int expected_1) {
    int call_348 = listLength_(p_1);
    int n_8 = call_348;
    int call_349 = Competitive_ABC140E_abc140eSolve(n_8, p_1);
    int actual_1 = call_349;
    bool if_85;
    if ((actual_1 == expected_1)) {
        goto then_321;
    } else {
        goto else_322;
    }
then_321:;
    if_85 = true;
    goto if_next_320;
else_322:;
    printf("actual=%d expected=%d\n", actual_1, expected_1);
    if_85 = false;
    goto if_next_320;
if_next_320:;
    return if_85;
}

void Competitive_ABC140E_abc140eTest(void) {
    struct IntList const* list_80 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_80))) = (struct IntList){.head = 1, .tail = NULL};
    struct IntList const* list_79 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_79))) = (struct IntList){.head = 3, .tail = list_80};
    struct IntList const* list_78 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_78))) = (struct IntList){.head = 2, .tail = list_79};
    bool call_350 = solve_(list_78, 5);
    milone_assert(call_350, 88, 2);
    struct IntList const* list_85 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_85))) = (struct IntList){.head = 5, .tail = NULL};
    struct IntList const* list_84 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_84))) = (struct IntList){.head = 4, .tail = list_85};
    struct IntList const* list_83 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_83))) = (struct IntList){.head = 3, .tail = list_84};
    struct IntList const* list_82 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_82))) = (struct IntList){.head = 2, .tail = list_83};
    struct IntList const* list_81 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_81))) = (struct IntList){.head = 1, .tail = list_82};
    bool call_351 = solve_(list_81, 30);
    milone_assert(call_351, 89, 2);
    struct IntList const* list_93 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_93))) = (struct IntList){.head = 1, .tail = NULL};
    struct IntList const* list_92 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_92))) = (struct IntList){.head = 6, .tail = list_93};
    struct IntList const* list_91 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_91))) = (struct IntList){.head = 5, .tail = list_92};
    struct IntList const* list_90 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_90))) = (struct IntList){.head = 4, .tail = list_91};
    struct IntList const* list_89 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_89))) = (struct IntList){.head = 3, .tail = list_90};
    struct IntList const* list_88 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_88))) = (struct IntList){.head = 7, .tail = list_89};
    struct IntList const* list_87 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_87))) = (struct IntList){.head = 2, .tail = list_88};
    struct IntList const* list_86 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_86))) = (struct IntList){.head = 8, .tail = list_87};
    bool call_352 = solve_(list_86, 136);
    milone_assert(call_352, 90, 2);
    return;
}

void Competitive_ABC140E_abc140eMain(void) {
    int call_353 = Competitive_Helpers_scanInt();
    int n_9 = call_353;
    struct IntList const* call_354 = Competitive_Helpers_scanIntList(n_9);
    struct IntList const* p_2 = call_354;
    int call_355 = Competitive_ABC140E_abc140eSolve(n_9, p_2);
    int m_4 = call_355;
    printf("%d\n", m_4);
    return;
}
