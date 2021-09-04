#include "milone.h"

struct IntIntIntFun2;

struct IntIntIntObjectUnitTuple5_;

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4_;

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_;

struct IntList;

struct IntList;

int fun_19(int arg_108, int arg_109);

int fun_14(void const* env_14, int arg_27, int arg_28);

int Competitive_Helpers_intMax(int , int );

int fun_15(void const* env_15, int arg_29, int arg_30);

int Competitive_Helpers_intMin(int , int );

int fun_16(void const* env_16, int arg_31, int arg_32);

int segTreeGet_(int , struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ );

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ segTreeSet_(int , int , struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ );

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ go_5(int n_2, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ perm_2, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ pos_1, int i_6);

int segTreeSum_(int , int , struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ );

int go_3(int n_2, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ pos_, int sum_1, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ prev_1, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ next_1, int p_);

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4_ segItemTypeNew_(int , struct IntIntIntFun2 );

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ segTreeOfList_(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4_ , struct IntList const* );

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ segTreeInsert_(int , int , struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ );

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ segTreePush_(int , struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ );

int segTreeToLength_(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ );

struct IntList const* listReplicate_(int , int );

int Competitive_ABC140E_abc140eSolve(int n_2, struct IntList const* perm_);

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

int fun_19(int arg_108, int arg_109) {
    return 0;
}

int fun_14(void const* env_14, int arg_27, int arg_28) {
    int call_292 = fun_19(arg_27, arg_28);
    return call_292;
}

int fun_15(void const* env_15, int arg_29, int arg_30) {
    int call_293 = Competitive_Helpers_intMax(arg_29, arg_30);
    return call_293;
}

int fun_16(void const* env_16, int arg_31, int arg_32) {
    int call_294 = Competitive_Helpers_intMin(arg_31, arg_32);
    return call_294;
}

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ go_5(int n_2, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ perm_2, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ pos_1, int i_6) {
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
    int call_295 = segTreeGet_(i_6, perm_2);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ call_296 = segTreeSet_(call_295, i_6, pos_1);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ pos_2 = call_296;
    int arg_110 = n_2;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ arg_111 = perm_2;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ arg_112 = pos_2;
    int arg_113 = (i_6 + 1);
    n_2 = arg_110;
    perm_2 = arg_111;
    pos_1 = arg_112;
    i_6 = arg_113;
    goto tailrec_296;
if_next_297:;
    return if_78;
}

int go_3(int n_2, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ pos_, int sum_1, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ prev_1, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ next_1, int p_) {
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
    int call_297 = segTreeGet_(p_, pos_);
    int i_7 = call_297;
    int call_298 = segTreeSum_(0, i_7, prev_1);
    int x_11 = call_298;
    int call_299 = segTreeSum_(0, x_11, prev_1);
    int w_ = call_299;
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
    int call_300 = segTreeSum_((i_7 + 1), (n_2 + 2), next_1);
    int y_5 = call_300;
    int call_301 = segTreeSum_((y_5 + 1), (n_2 + 2), next_1);
    int z_ = call_301;
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
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ call_302 = segTreeSet_(i_7, i_7, prev_1);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ prev_2 = call_302;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ call_303 = segTreeSet_(i_7, i_7, next_1);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ next_2 = call_303;
    int arg_114 = n_2;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ arg_115 = pos_;
    int arg_116 = sum_2;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ arg_117 = prev_2;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ arg_118 = next_2;
    int arg_119 = (p_ - 1);
    n_2 = arg_114;
    pos_ = arg_115;
    sum_1 = arg_116;
    prev_1 = arg_117;
    next_1 = arg_118;
    p_ = arg_119;
    goto tailrec_300;
if_next_301:;
    return if_79;
}

int Competitive_ABC140E_abc140eSolve(int n_2, struct IntList const* perm_) {
    struct IntIntIntFun2 fun_32 = (struct IntIntIntFun2){.fun = fun_14, .env = NULL};
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4_ call_304 = segItemTypeNew_(0, fun_32);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4_ segItemTypeInt_1 = call_304;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ call_305 = segTreeOfList_(segItemTypeInt_1, perm_);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ perm_1 = call_305;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ call_306 = segTreeInsert_(0, (n_2 + 1), perm_1);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ call_307 = segTreePush_((n_2 + 2), call_306);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ perm_2 = call_307;
    int call_308 = segTreeToLength_(perm_2);
    milone_assert((call_308 == (n_2 + 2)), 22, 2);
    struct IntIntIntFun2 fun_33 = (struct IntIntIntFun2){.fun = fun_15, .env = NULL};
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4_ call_309 = segItemTypeNew_(0, fun_33);
    struct IntList const* call_310 = listReplicate_(0, (n_2 + 2));
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ call_311 = segTreeOfList_(call_309, call_310);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ prev_ = call_311;
    struct IntIntIntFun2 fun_34 = (struct IntIntIntFun2){.fun = fun_16, .env = NULL};
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4_ call_312 = segItemTypeNew_((n_2 + 1), fun_34);
    struct IntList const* call_313 = listReplicate_((n_2 + 1), (n_2 + 2));
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ call_314 = segTreeOfList_(call_312, call_313);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ next_ = call_314;
    struct IntList const* call_315 = listReplicate_(0, (n_2 + 3));
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ call_316 = segTreeOfList_(segItemTypeInt_1, call_315);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ pos_3 = call_316;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ call_317 = go_5(n_2, perm_2, pos_3, 0);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ pos_ = call_317;
    int call_318 = go_3(n_2, pos_, 0, prev_, next_, n_2);
    return call_318;
}

bool solve_(struct IntList const* p_1, int expected_1) {
    int call_319 = listLength_(p_1);
    int n_3 = call_319;
    int call_320 = Competitive_ABC140E_abc140eSolve(n_3, p_1);
    int actual_1 = call_320;
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

void Competitive_ABC140E_abc140eTest(void) {
    struct IntList const* list_56 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_56))) = (struct IntList){.head = 1, .tail = NULL};
    struct IntList const* list_55 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_55))) = (struct IntList){.head = 3, .tail = list_56};
    struct IntList const* list_54 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_54))) = (struct IntList){.head = 2, .tail = list_55};
    bool call_321 = solve_(list_54, 5);
    milone_assert(call_321, 88, 2);
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
    bool call_322 = solve_(list_57, 30);
    milone_assert(call_322, 89, 2);
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
    bool call_323 = solve_(list_62, 136);
    milone_assert(call_323, 90, 2);
    return;
}

void Competitive_ABC140E_abc140eMain(void) {
    int call_324 = Competitive_Helpers_scanInt();
    int n_4 = call_324;
    struct IntList const* call_325 = Competitive_Helpers_scanIntList(n_4);
    struct IntList const* p_2 = call_325;
    int call_326 = Competitive_ABC140E_abc140eSolve(n_4, p_2);
    int m_2 = call_326;
    printf("%d\n", m_2);
    return;
}
