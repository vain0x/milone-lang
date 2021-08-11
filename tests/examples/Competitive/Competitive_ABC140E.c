#include "milone.h"

struct IntIntIntFun2;

struct IntIntIntObjectUnitTuple5_;

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4_;

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_;

struct IntList;

struct IntList;

int fun_19(int arg_121, int arg_122);

int fun_14(void const* env_14, int arg_27, int arg_28);

int Competitive_Helpers_intMax(int, int);

int fun_15(void const* env_15, int arg_29, int arg_30);

int Competitive_Helpers_intMin(int, int);

int fun_16(void const* env_16, int arg_31, int arg_32);

int segTreeGet_(int, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_);

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ segTreeSet_(int, int, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_);

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ go_4(int n_2, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ perm_2, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ pos_1, int i_6);

int segTreeSum_(int, int, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_);

int go_5(int n_2, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ pos_, int sum_1, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ prev_1, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ next_1, int p_);

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4_ segItemTypeNew_(int, struct IntIntIntFun2);

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ segTreeOfList_(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4_, struct IntList const*);

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ segTreeInsert_(int, int, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_);

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ segTreePush_(int, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_);

int segTreeToLength_(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_);

struct IntList const* listReplicate_(int, int);

int Competitive_ABC140E_abc140eSolve(int n_2, struct IntList const* perm_);

int listLength_(struct IntList const*);

bool solve_(struct IntList const* p_1, int expected_1);

char Competitive_ABC140E_abc140eTest(char arg_133);

int Competitive_Helpers_scanInt(char);

struct IntList const* Competitive_Helpers_scanIntList(int);

char Competitive_ABC140E_abc140eMain(char arg_134);

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

int fun_19(int arg_121, int arg_122) {
    return 0;
}

int fun_14(void const* env_14, int arg_27, int arg_28) {
    int call_309 = fun_19(arg_27, arg_28);
    return call_309;
}

int fun_15(void const* env_15, int arg_29, int arg_30) {
    int call_310 = Competitive_Helpers_intMax(arg_29, arg_30);
    return call_310;
}

int fun_16(void const* env_16, int arg_31, int arg_32) {
    int call_311 = Competitive_Helpers_intMin(arg_31, arg_32);
    return call_311;
}

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ go_4(int n_2, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ perm_2, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ pos_1, int i_6) {
tailrec_296:;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ if_78;
    if ((i_6 == (n_2 + 2))) {
        goto then_298;
    } else {
        goto else_299;
    }
then_298:;
    if_78 = pos_1;
    goto if_next_297;
else_299:;
    int call_312 = segTreeGet_(i_6, perm_2);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ call_313 = segTreeSet_(call_312, i_6, pos_1);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ pos_2 = call_313;
    int arg_123 = n_2;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ arg_124 = perm_2;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ arg_125 = pos_2;
    int arg_126 = (i_6 + 1);
    n_2 = arg_123;
    perm_2 = arg_124;
    pos_1 = arg_125;
    i_6 = arg_126;
    goto tailrec_296;
if_next_297:;
    return if_78;
}

int go_5(int n_2, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ pos_, int sum_1, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ prev_1, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ next_1, int p_) {
tailrec_300:;
    int if_79;
    if ((p_ < 1)) {
        goto then_302;
    } else {
        goto else_303;
    }
then_302:;
    if_79 = sum_1;
    goto if_next_301;
else_303:;
    int call_314 = segTreeGet_(p_, pos_);
    int i_7 = call_314;
    int call_315 = segTreeSum_(0, i_7, prev_1);
    int x_11 = call_315;
    int call_316 = segTreeSum_(0, x_11, prev_1);
    int w_ = call_316;
    bool if_80;
    if ((x_11 >= w_)) {
        goto then_305;
    } else {
        goto else_306;
    }
then_305:;
    if_80 = (x_11 < i_7);
    goto if_next_304;
else_306:;
    if_80 = false;
    goto if_next_304;
if_next_304:;
    milone_assert(if_80, 58, 6);
    int call_317 = segTreeSum_((i_7 + 1), (n_2 + 2), next_1);
    int y_5 = call_317;
    int call_318 = segTreeSum_((y_5 + 1), (n_2 + 2), next_1);
    int z_ = call_318;
    bool if_81;
    if ((i_7 < y_5)) {
        goto then_308;
    } else {
        goto else_309;
    }
then_308:;
    if_81 = (z_ >= y_5);
    goto if_next_307;
else_309:;
    if_81 = false;
    goto if_next_307;
if_next_307:;
    milone_assert(if_81, 62, 6);
    int count_ = (((x_11 - w_) * (y_5 - i_7)) + ((i_7 - x_11) * (z_ - y_5)));
    int sum_2 = (sum_1 + (count_ * p_));
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ call_319 = segTreeSet_(i_7, i_7, prev_1);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ prev_2 = call_319;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ call_320 = segTreeSet_(i_7, i_7, next_1);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ next_2 = call_320;
    int arg_127 = n_2;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ arg_128 = pos_;
    int arg_129 = sum_2;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ arg_130 = prev_2;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ arg_131 = next_2;
    int arg_132 = (p_ - 1);
    n_2 = arg_127;
    pos_ = arg_128;
    sum_1 = arg_129;
    prev_1 = arg_130;
    next_1 = arg_131;
    p_ = arg_132;
    goto tailrec_300;
if_next_301:;
    return if_79;
}

int Competitive_ABC140E_abc140eSolve(int n_2, struct IntList const* perm_) {
    struct IntIntIntFun2 fun_32 = (struct IntIntIntFun2){.fun = fun_14, .env = NULL};
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4_ call_321 = segItemTypeNew_(0, fun_32);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4_ segItemTypeInt_1 = call_321;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ call_322 = segTreeOfList_(segItemTypeInt_1, perm_);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ perm_1 = call_322;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ call_323 = segTreeInsert_(0, (n_2 + 1), perm_1);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ call_324 = segTreePush_((n_2 + 2), call_323);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ perm_2 = call_324;
    int call_325 = segTreeToLength_(perm_2);
    milone_assert((call_325 == (n_2 + 2)), 22, 2);
    struct IntIntIntFun2 fun_33 = (struct IntIntIntFun2){.fun = fun_15, .env = NULL};
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4_ call_326 = segItemTypeNew_(0, fun_33);
    struct IntList const* call_327 = listReplicate_(0, (n_2 + 2));
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ call_328 = segTreeOfList_(call_326, call_327);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ prev_ = call_328;
    struct IntIntIntFun2 fun_34 = (struct IntIntIntFun2){.fun = fun_16, .env = NULL};
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4_ call_329 = segItemTypeNew_((n_2 + 1), fun_34);
    struct IntList const* call_330 = listReplicate_((n_2 + 1), (n_2 + 2));
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ call_331 = segTreeOfList_(call_329, call_330);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ next_ = call_331;
    struct IntList const* call_332 = listReplicate_(0, (n_2 + 3));
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ call_333 = segTreeOfList_(segItemTypeInt_1, call_332);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ pos_3 = call_333;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ call_334 = go_4(n_2, perm_2, pos_3, 0);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ pos_ = call_334;
    int call_335 = go_5(n_2, pos_, 0, prev_, next_, n_2);
    return call_335;
}

bool solve_(struct IntList const* p_1, int expected_1) {
    int call_336 = listLength_(p_1);
    int n_3 = call_336;
    int call_337 = Competitive_ABC140E_abc140eSolve(n_3, p_1);
    int actual_1 = call_337;
    bool if_82;
    if ((actual_1 == expected_1)) {
        goto then_311;
    } else {
        goto else_312;
    }
then_311:;
    if_82 = true;
    goto if_next_310;
else_312:;
    printf("actual=%d expected=%d\n", actual_1, expected_1);
    if_82 = false;
    goto if_next_310;
if_next_310:;
    return if_82;
}

char Competitive_ABC140E_abc140eTest(char arg_133) {
    struct IntList const* list_56 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_56))) = (struct IntList){.head = 1, .tail = NULL};
    struct IntList const* list_55 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_55))) = (struct IntList){.head = 3, .tail = list_56};
    struct IntList const* list_54 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_54))) = (struct IntList){.head = 2, .tail = list_55};
    bool call_338 = solve_(list_54, 5);
    milone_assert(call_338, 88, 2);
    struct IntList const* list_61 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_61))) = (struct IntList){.head = 5, .tail = NULL};
    struct IntList const* list_60 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_60))) = (struct IntList){.head = 4, .tail = list_61};
    struct IntList const* list_59 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_59))) = (struct IntList){.head = 3, .tail = list_60};
    struct IntList const* list_58 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_58))) = (struct IntList){.head = 2, .tail = list_59};
    struct IntList const* list_57 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_57))) = (struct IntList){.head = 1, .tail = list_58};
    bool call_339 = solve_(list_57, 30);
    milone_assert(call_339, 89, 2);
    struct IntList const* list_69 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_69))) = (struct IntList){.head = 1, .tail = NULL};
    struct IntList const* list_68 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_68))) = (struct IntList){.head = 6, .tail = list_69};
    struct IntList const* list_67 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_67))) = (struct IntList){.head = 5, .tail = list_68};
    struct IntList const* list_66 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_66))) = (struct IntList){.head = 4, .tail = list_67};
    struct IntList const* list_65 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_65))) = (struct IntList){.head = 3, .tail = list_66};
    struct IntList const* list_64 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_64))) = (struct IntList){.head = 7, .tail = list_65};
    struct IntList const* list_63 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_63))) = (struct IntList){.head = 2, .tail = list_64};
    struct IntList const* list_62 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_62))) = (struct IntList){.head = 8, .tail = list_63};
    bool call_340 = solve_(list_62, 136);
    milone_assert(call_340, 90, 2);
    return 0;
}

char Competitive_ABC140E_abc140eMain(char arg_134) {
    int call_341 = Competitive_Helpers_scanInt(0);
    int n_4 = call_341;
    struct IntList const* call_342 = Competitive_Helpers_scanIntList(n_4);
    struct IntList const* p_2 = call_342;
    int call_343 = Competitive_ABC140E_abc140eSolve(n_4, p_2);
    int m_2 = call_343;
    printf("%d\n", m_2);
    return 0;
}
