#include "milone.h"

struct IntIntIntFun2;

struct IntIntIntObjectUnitTuple5_;

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4_;

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_;

struct IntList;

struct IntList;

int fun_19(int arg_108, int arg_109);

int fun_14(void const* env_14, int arg_27, int arg_28);

int segTreeGet_(int , struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ );

int go_3(int n_4, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ a_1, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ b_1, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ c_1, int sum_1, int i_6);

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4_ segItemTypeNew_(int , struct IntIntIntFun2 );

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ segTreeOfList_(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4_ , struct IntList const* );

int Competitive_ABC140B_abc140bSolve(int n_4, struct IntList const* a_, struct IntList const* b_, struct IntList const* c_);

int listLength_(struct IntList const* );

int f_(struct IntList const* a_2, struct IntList const* b_2, struct IntList const* c_2);

bool case1_(void);

bool case2_(void);

bool case3_(void);

void Competitive_ABC140B_abc140bTest(void);

int Competitive_Helpers_scanInt(void);

struct IntList const* Competitive_Helpers_scanIntList(int );

void Competitive_ABC140B_abc140bMain(void);

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
    int call_296 = fun_19(arg_27, arg_28);
    return call_296;
}

int go_3(int n_4, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ a_1, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ b_1, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ c_1, int sum_1, int i_6) {
tailrec_296:;
    int if_78;
    if ((i_6 == n_4)) {
        goto then_298;
    } else {
        goto else_299;
    }
then_298:;
    if_78 = sum_1;
    goto if_next_297;
else_299:;
    int call_297 = segTreeGet_(i_6, a_1);
    int ai_ = call_297;
    int call_298 = segTreeGet_((ai_ - 1), b_1);
    int eat_ = call_298;
    bool if_79;
    if (((i_6 + 1) < n_4)) {
        goto then_301;
    } else {
        goto else_302;
    }
then_301:;
    int call_299 = segTreeGet_((i_6 + 1), a_1);
    if_79 = (call_299 == (ai_ + 1));
    goto if_next_300;
else_302:;
    if_79 = false;
    goto if_next_300;
if_next_300:;
    int if_80;
    if (if_79) {
        goto then_304;
    } else {
        goto else_305;
    }
then_304:;
    int call_300 = segTreeGet_((ai_ - 1), c_1);
    if_80 = call_300;
    goto if_next_303;
else_305:;
    if_80 = 0;
    goto if_next_303;
if_next_303:;
    int bonus_ = if_80;
    int arg_110 = n_4;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ arg_111 = a_1;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ arg_112 = b_1;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ arg_113 = c_1;
    int arg_114 = ((sum_1 + eat_) + bonus_);
    int arg_115 = (i_6 + 1);
    n_4 = arg_110;
    a_1 = arg_111;
    b_1 = arg_112;
    c_1 = arg_113;
    sum_1 = arg_114;
    i_6 = arg_115;
    goto tailrec_296;
if_next_297:;
    return if_78;
}

int Competitive_ABC140B_abc140bSolve(int n_4, struct IntList const* a_, struct IntList const* b_, struct IntList const* c_) {
    struct IntIntIntFun2 fun_32 = (struct IntIntIntFun2){.fun = fun_14, .env = NULL};
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4_ call_301 = segItemTypeNew_(0, fun_32);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4_ segItemTypeInt_1 = call_301;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ call_302 = segTreeOfList_(segItemTypeInt_1, a_);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ a_1 = call_302;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ call_303 = segTreeOfList_(segItemTypeInt_1, b_);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ b_1 = call_303;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ call_304 = segTreeOfList_(segItemTypeInt_1, c_);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3_ c_1 = call_304;
    int call_305 = go_3(n_4, a_1, b_1, c_1, 0, 0);
    return call_305;
}

int f_(struct IntList const* a_2, struct IntList const* b_2, struct IntList const* c_2) {
    int call_306 = listLength_(a_2);
    int n_5 = call_306;
    int call_307 = listLength_(b_2);
    milone_assert((call_307 == n_5), 32, 4);
    int call_308 = listLength_(c_2);
    milone_assert((call_308 == (n_5 - 1)), 33, 4);
    int call_309 = Competitive_ABC140B_abc140bSolve(n_5, a_2, b_2, c_2);
    return call_309;
}

bool case1_(void) {
    struct IntList const* list_56 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_56))) = (struct IntList){.head = 2, .tail = NULL};
    struct IntList const* list_55 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_55))) = (struct IntList){.head = 1, .tail = list_56};
    struct IntList const* list_54 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_54))) = (struct IntList){.head = 3, .tail = list_55};
    struct IntList const* a_3 = list_54;
    struct IntList const* list_59 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_59))) = (struct IntList){.head = 4, .tail = NULL};
    struct IntList const* list_58 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_58))) = (struct IntList){.head = 5, .tail = list_59};
    struct IntList const* list_57 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_57))) = (struct IntList){.head = 2, .tail = list_58};
    struct IntList const* b_3 = list_57;
    struct IntList const* list_61 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_61))) = (struct IntList){.head = 6, .tail = NULL};
    struct IntList const* list_60 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_60))) = (struct IntList){.head = 3, .tail = list_61};
    struct IntList const* c_3 = list_60;
    int call_310 = f_(a_3, b_3, c_3);
    return (call_310 == 14);
}

bool case2_(void) {
    struct IntList const* list_65 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_65))) = (struct IntList){.head = 1, .tail = NULL};
    struct IntList const* list_64 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_64))) = (struct IntList){.head = 4, .tail = list_65};
    struct IntList const* list_63 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_63))) = (struct IntList){.head = 3, .tail = list_64};
    struct IntList const* list_62 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_62))) = (struct IntList){.head = 2, .tail = list_63};
    struct IntList const* a_4 = list_62;
    struct IntList const* list_69 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_69))) = (struct IntList){.head = 24, .tail = NULL};
    struct IntList const* list_68 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_68))) = (struct IntList){.head = 8, .tail = list_69};
    struct IntList const* list_67 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_67))) = (struct IntList){.head = 5, .tail = list_68};
    struct IntList const* list_66 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_66))) = (struct IntList){.head = 13, .tail = list_67};
    struct IntList const* b_4 = list_66;
    struct IntList const* list_72 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_72))) = (struct IntList){.head = 15, .tail = NULL};
    struct IntList const* list_71 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_71))) = (struct IntList){.head = 9, .tail = list_72};
    struct IntList const* list_70 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_70))) = (struct IntList){.head = 45, .tail = list_71};
    struct IntList const* c_4 = list_70;
    int call_311 = f_(a_4, b_4, c_4);
    return (call_311 == 74);
}

bool case3_(void) {
    struct IntList const* list_74 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_74))) = (struct IntList){.head = 2, .tail = NULL};
    struct IntList const* list_73 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_73))) = (struct IntList){.head = 1, .tail = list_74};
    struct IntList const* a_5 = list_73;
    struct IntList const* list_76 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_76))) = (struct IntList){.head = 50, .tail = NULL};
    struct IntList const* list_75 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_75))) = (struct IntList){.head = 50, .tail = list_76};
    struct IntList const* b_5 = list_75;
    struct IntList const* list_77 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_77))) = (struct IntList){.head = 50, .tail = NULL};
    struct IntList const* c_5 = list_77;
    int call_312 = f_(a_5, b_5, c_5);
    return (call_312 == 150);
}

void Competitive_ABC140B_abc140bTest(void) {
    bool call_313 = case1_();
    milone_assert(call_313, 42, 2);
    bool call_314 = case2_();
    milone_assert(call_314, 50, 2);
    bool call_315 = case3_();
    milone_assert(call_315, 58, 2);
    return;
}

void Competitive_ABC140B_abc140bMain(void) {
    int call_316 = Competitive_Helpers_scanInt();
    int n_6 = call_316;
    struct IntList const* call_317 = Competitive_Helpers_scanIntList(n_6);
    struct IntList const* a_6 = call_317;
    struct IntList const* call_318 = Competitive_Helpers_scanIntList(n_6);
    struct IntList const* b_6 = call_318;
    struct IntList const* call_319 = Competitive_Helpers_scanIntList((n_6 - 1));
    struct IntList const* c_6 = call_319;
    int call_320 = Competitive_ABC140B_abc140bSolve(n_6, a_6, b_6, c_6);
    int m_3 = call_320;
    printf("%d\n", m_3);
    return;
}
