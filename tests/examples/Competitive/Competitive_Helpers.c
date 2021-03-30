#include "milone.h"

struct StringList;

struct StringStringStringFun2List;

struct IntList;

struct IntIntIntFun2List;

struct IntIntIntObjectUnitTuple5List;

struct StringIntIntObjectUnitTuple5List;

struct StringList;

struct IntList;

struct IntIntBoolFun2;

struct IntListIntListTuple2;

struct StringStringBoolFun2;

struct StringListStringListTuple2;

struct IntIntFun1;

struct StringStringListTuple2;

struct IntVoidMutPtrFun1;

struct VoidMutPtrIntIntFun2;

struct VoidMutPtrIntIntUnitFun3;

struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6;

struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5;

void* milone_mem_alloc(int, uintptr_t);

void* Competitive_Helpers_memAlloc(int len_, int size_);

void* memcpy(void*, void const*, uintptr_t);

void* Competitive_Helpers_memCopy(void* dest_, void const* src_, int size_1);

int scan_int();

int Competitive_Helpers_scanInt(char arg_35);

void* Competitive_Helpers_rawIntArrayNew(int len_1);

int Competitive_Helpers_rawIntArrayGet(void* array_, int index_);

char Competitive_Helpers_rawIntArraySet(void* array_1, int index_1, int value_);

char Competitive_Helpers_rawMemoryCopy(void* dest_1, void* src_1, int size_2);

bool listIsEmpty_(struct StringList const* xs_);

bool listIsEmpty_3(struct StringStringStringFun2List const* xs_);

bool listIsEmpty_2(struct IntList const* xs_);

bool listIsEmpty_1(struct IntIntIntFun2List const* xs_);

bool listIsEmpty_4(struct IntIntIntObjectUnitTuple5List const* xs_);

bool listIsEmpty_5(struct StringIntIntObjectUnitTuple5List const* xs_);

int go_22(int len_2, struct StringList const* xs_2);

int go_21(int len_2, struct IntList const* xs_2);

int listLength_1(struct StringList const* xs_1);

int listLength_(struct IntList const* xs_1);

struct IntList const* go_38(struct IntList const* acc_, struct IntList const* xs_5);

struct StringList const* go_37(struct StringList const* acc_, struct StringList const* xs_5);

struct IntList const* listRev_1(struct IntList const* xs_4);

struct StringList const* listRev_(struct StringList const* xs_4);

bool go_24(struct IntIntBoolFun2 itemEqual_, struct IntList const* xs_8, struct IntList const* ys_1);

bool go_23(struct StringStringBoolFun2 itemEqual_, struct StringList const* xs_8, struct StringList const* ys_1);

bool listEqual_1(struct IntIntBoolFun2 itemEqual_, struct IntList const* xs_7, struct IntList const* ys_);

bool listEqual_(struct StringStringBoolFun2 itemEqual_, struct StringList const* xs_7, struct StringList const* ys_);

struct IntList const* go_25(int item_, int len_3, struct IntList const* acc_1, int i_);

struct IntList const* listReplicate_(int item_, int len_3);

struct IntList const* go_26(int len_4, struct IntIntFun1 gen_, struct IntList const* acc_2, int i_1);

struct IntList const* listInit_(int len_4, struct IntIntFun1 gen_);

struct StringStringListTuple2 go_5(struct StringList const* xs_11, int xn_);

struct String Competitive_Helpers_strConcat(struct StringList const* xs_10);

bool Competitive_Helpers_intEqual(int first_, int second_);

int Competitive_Helpers_intMin(int first_1, int second_1);

int Competitive_Helpers_intMax(int first_2, int second_2);

bool Competitive_Helpers_strEqual(struct String first_3, struct String second_3);

int failwith_(struct String msg_);

int fun_21(int arg_58);

int fun_3(void const* env_, int arg_);

struct IntList const* Competitive_Helpers_scanIntList(int len_5);

struct IntVoidMutPtrFun1 typeToArrayNew_(struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6 arg_59);

struct VoidMutPtrIntIntFun2 typeToArrayGet_(struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6 arg_60);

struct VoidMutPtrIntIntUnitFun3 typeToArraySet_(struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6 arg_61);

void* fun_4(void const* env_1, int arg_1);

int fun_5(void const* env_2, void* arg_2, int arg_3);

char fun_6(void const* env_3, void* arg_4, int arg_5, int arg_6);

int vectorToLength_(struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 arg_62);

struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 vectorNew_(struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6 itemTy_, int len_7);

char vectorCheckIndex_(int index_2, struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 self_);

int vectorGet_(int index_3, struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 self_1);

char vectorSet_(int index_4, int value_1, struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 self_2);

char go_27(int len_10, struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 v_, int i_2, struct IntList const* xs_19);

struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 vectorOfList_(struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6 ty_, struct IntList const* xs_18);

char go_7(int len_11, struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 v_1, int i_3);

struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 Competitive_Helpers_scanIntVector(int len_11);

char refCase_(char arg_70);

char vectorOfListTest_(char arg_71);

char Competitive_Helpers_vectorTest(char arg_72);

struct StringList {
    struct String head;
    struct StringList const* tail;
};

struct IntList {
    int head;
    struct IntList const* tail;
};

struct IntIntBoolFun2 {
    bool(*fun)(void const*, int, int);
    void const* env;
};

struct IntListIntListTuple2 {
    struct IntList const* t0;
    struct IntList const* t1;
};

struct StringStringBoolFun2 {
    bool(*fun)(void const*, struct String, struct String);
    void const* env;
};

struct StringListStringListTuple2 {
    struct StringList const* t0;
    struct StringList const* t1;
};

struct IntIntFun1 {
    int(*fun)(void const*, int);
    void const* env;
};

struct StringStringListTuple2 {
    struct String t0;
    struct StringList const* t1;
};

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

struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 {
    struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6 t0;
    void* t1;
    int t2;
    int t3;
    char t4;
};

extern struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6 Competitive_Helpers_typeInt;

void* Competitive_Helpers_memAlloc(int len_, int size_) {
    void* milone_mem_alloc_result = milone_mem_alloc(len_, ((uintptr_t)size_));
    return milone_mem_alloc_result;
}

void* Competitive_Helpers_memCopy(void* dest_, void const* src_, int size_1) {
    void* memcpy_result = memcpy(dest_, src_, ((uintptr_t)size_1));
    return memcpy_result;
}

int Competitive_Helpers_scanInt(char arg_35) {
    int scan_int_result = scan_int();
    return scan_int_result;
}

void* Competitive_Helpers_rawIntArrayNew(int len_1) {
    void* call_ = Competitive_Helpers_memAlloc(len_1, sizeof(int));
    return ((void*)call_);
}

int Competitive_Helpers_rawIntArrayGet(void* array_, int index_) {
    int read_ = ((int const*)array_)[index_];
    return read_;
}

char Competitive_Helpers_rawIntArraySet(void* array_1, int index_1, int value_) {
    ((int*)array_1)[index_1] = value_;
    return 0;
}

char Competitive_Helpers_rawMemoryCopy(void* dest_1, void* src_1, int size_2) {
    void* call_1 = Competitive_Helpers_memCopy(dest_1, ((void const*)src_1), (size_2 * sizeof(int)));
    return 0;
}

bool listIsEmpty_(struct StringList const* xs_) {
    bool if_;
    if ((!(xs_))) {
        goto nil_cl_2;
    } else {
        goto cons_cl_3;
    }
nil_cl_2:;
    if_ = true;
    goto if_next_1;
cons_cl_3:;
    if_ = false;
    goto if_next_1;
if_next_1:;
    return if_;
}

bool listIsEmpty_3(struct StringStringStringFun2List const* xs_) {
    bool if_1;
    if ((!(xs_))) {
        goto nil_cl_5;
    } else {
        goto cons_cl_6;
    }
nil_cl_5:;
    if_1 = true;
    goto if_next_4;
cons_cl_6:;
    if_1 = false;
    goto if_next_4;
if_next_4:;
    return if_1;
}

bool listIsEmpty_2(struct IntList const* xs_) {
    bool if_2;
    if ((!(xs_))) {
        goto nil_cl_8;
    } else {
        goto cons_cl_9;
    }
nil_cl_8:;
    if_2 = true;
    goto if_next_7;
cons_cl_9:;
    if_2 = false;
    goto if_next_7;
if_next_7:;
    return if_2;
}

bool listIsEmpty_1(struct IntIntIntFun2List const* xs_) {
    bool if_3;
    if ((!(xs_))) {
        goto nil_cl_11;
    } else {
        goto cons_cl_12;
    }
nil_cl_11:;
    if_3 = true;
    goto if_next_10;
cons_cl_12:;
    if_3 = false;
    goto if_next_10;
if_next_10:;
    return if_3;
}

bool listIsEmpty_4(struct IntIntIntObjectUnitTuple5List const* xs_) {
    bool if_4;
    if ((!(xs_))) {
        goto nil_cl_14;
    } else {
        goto cons_cl_15;
    }
nil_cl_14:;
    if_4 = true;
    goto if_next_13;
cons_cl_15:;
    if_4 = false;
    goto if_next_13;
if_next_13:;
    return if_4;
}

bool listIsEmpty_5(struct StringIntIntObjectUnitTuple5List const* xs_) {
    bool if_5;
    if ((!(xs_))) {
        goto nil_cl_17;
    } else {
        goto cons_cl_18;
    }
nil_cl_17:;
    if_5 = true;
    goto if_next_16;
cons_cl_18:;
    if_5 = false;
    goto if_next_16;
if_next_16:;
    return if_5;
}

int go_22(int len_2, struct StringList const* xs_2) {
tailrec_19:;
    int match_;
    if ((!((!(xs_2))))) goto next_21;
    match_ = len_2;
    goto end_match_20;
next_21:;
    if ((!(xs_2))) goto next_22;
    struct StringList const* xs_3 = xs_2->tail;
    int arg_36 = (len_2 + 1);
    struct StringList const* arg_37 = xs_3;
    len_2 = arg_36;
    xs_2 = arg_37;
    goto tailrec_19;
next_22:;
    exit(1);
end_match_20:;
    return match_;
}

int go_21(int len_2, struct IntList const* xs_2) {
tailrec_23:;
    int match_1;
    if ((!((!(xs_2))))) goto next_25;
    match_1 = len_2;
    goto end_match_24;
next_25:;
    if ((!(xs_2))) goto next_26;
    struct IntList const* xs_3 = xs_2->tail;
    int arg_38 = (len_2 + 1);
    struct IntList const* arg_39 = xs_3;
    len_2 = arg_38;
    xs_2 = arg_39;
    goto tailrec_23;
next_26:;
    exit(1);
end_match_24:;
    return match_1;
}

int listLength_1(struct StringList const* xs_1) {
    int call_2 = go_22(0, xs_1);
    return call_2;
}

int listLength_(struct IntList const* xs_1) {
    int call_3 = go_21(0, xs_1);
    return call_3;
}

struct IntList const* go_38(struct IntList const* acc_, struct IntList const* xs_5) {
tailrec_27:;
    struct IntList const* match_2;
    if ((!((!(xs_5))))) goto next_29;
    match_2 = acc_;
    goto end_match_28;
next_29:;
    if ((!(xs_5))) goto next_30;
    int x_ = xs_5->head;
    struct IntList const* xs_6 = xs_5->tail;
    struct IntList const* list_ = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_))) = (struct IntList){.head = x_, .tail = acc_};
    struct IntList const* arg_40 = list_;
    struct IntList const* arg_41 = xs_6;
    acc_ = arg_40;
    xs_5 = arg_41;
    goto tailrec_27;
next_30:;
    exit(1);
end_match_28:;
    return match_2;
}

struct StringList const* go_37(struct StringList const* acc_, struct StringList const* xs_5) {
tailrec_31:;
    struct StringList const* match_3;
    if ((!((!(xs_5))))) goto next_33;
    match_3 = acc_;
    goto end_match_32;
next_33:;
    if ((!(xs_5))) goto next_34;
    struct String x_ = xs_5->head;
    struct StringList const* xs_6 = xs_5->tail;
    struct StringList const* list_1 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_1))) = (struct StringList){.head = x_, .tail = acc_};
    struct StringList const* arg_42 = list_1;
    struct StringList const* arg_43 = xs_6;
    acc_ = arg_42;
    xs_5 = arg_43;
    goto tailrec_31;
next_34:;
    exit(1);
end_match_32:;
    return match_3;
}

struct IntList const* listRev_1(struct IntList const* xs_4) {
    struct IntList const* call_4 = go_38(NULL, xs_4);
    return call_4;
}

struct StringList const* listRev_(struct StringList const* xs_4) {
    struct StringList const* call_5 = go_37(NULL, xs_4);
    return call_5;
}

bool go_24(struct IntIntBoolFun2 itemEqual_, struct IntList const* xs_8, struct IntList const* ys_1) {
tailrec_35:;
    bool match_4;
    struct IntListIntListTuple2 tuple_ = (struct IntListIntListTuple2){.t0 = xs_8, .t1 = ys_1};
    if ((!((!(tuple_.t0))))) goto next_37;
    if ((!((!(tuple_.t1))))) goto next_37;
    match_4 = true;
    goto end_match_36;
next_37:;
    if ((!(tuple_.t0))) goto next_38;
    int x_1 = tuple_.t0->head;
    struct IntList const* xs_9 = tuple_.t0->tail;
    if ((!(tuple_.t1))) goto next_38;
    int y_ = tuple_.t1->head;
    struct IntList const* ys_2 = tuple_.t1->tail;
    bool app_ = itemEqual_.fun(itemEqual_.env, x_1, y_);
    bool if_6;
    if (app_) {
        goto then_41;
    } else {
        goto else_42;
    }
then_41:;
    struct IntIntBoolFun2 arg_44 = itemEqual_;
    struct IntList const* arg_45 = xs_9;
    struct IntList const* arg_46 = ys_2;
    itemEqual_ = arg_44;
    xs_8 = arg_45;
    ys_1 = arg_46;
    goto tailrec_35;
else_42:;
    if_6 = false;
    goto if_next_40;
if_next_40:;
    match_4 = if_6;
    goto end_match_36;
next_38:;
    match_4 = false;
    goto end_match_36;
next_39:;
end_match_36:;
    return match_4;
}

bool go_23(struct StringStringBoolFun2 itemEqual_, struct StringList const* xs_8, struct StringList const* ys_1) {
tailrec_43:;
    bool match_5;
    struct StringListStringListTuple2 tuple_1 = (struct StringListStringListTuple2){.t0 = xs_8, .t1 = ys_1};
    if ((!((!(tuple_1.t0))))) goto next_45;
    if ((!((!(tuple_1.t1))))) goto next_45;
    match_5 = true;
    goto end_match_44;
next_45:;
    if ((!(tuple_1.t0))) goto next_46;
    struct String x_1 = tuple_1.t0->head;
    struct StringList const* xs_9 = tuple_1.t0->tail;
    if ((!(tuple_1.t1))) goto next_46;
    struct String y_ = tuple_1.t1->head;
    struct StringList const* ys_2 = tuple_1.t1->tail;
    bool app_1 = itemEqual_.fun(itemEqual_.env, x_1, y_);
    bool if_7;
    if (app_1) {
        goto then_49;
    } else {
        goto else_50;
    }
then_49:;
    struct StringStringBoolFun2 arg_47 = itemEqual_;
    struct StringList const* arg_48 = xs_9;
    struct StringList const* arg_49 = ys_2;
    itemEqual_ = arg_47;
    xs_8 = arg_48;
    ys_1 = arg_49;
    goto tailrec_43;
else_50:;
    if_7 = false;
    goto if_next_48;
if_next_48:;
    match_5 = if_7;
    goto end_match_44;
next_46:;
    match_5 = false;
    goto end_match_44;
next_47:;
end_match_44:;
    return match_5;
}

bool listEqual_1(struct IntIntBoolFun2 itemEqual_, struct IntList const* xs_7, struct IntList const* ys_) {
    bool call_6 = go_24(itemEqual_, xs_7, ys_);
    return call_6;
}

bool listEqual_(struct StringStringBoolFun2 itemEqual_, struct StringList const* xs_7, struct StringList const* ys_) {
    bool call_7 = go_23(itemEqual_, xs_7, ys_);
    return call_7;
}

struct IntList const* go_25(int item_, int len_3, struct IntList const* acc_1, int i_) {
tailrec_51:;
    struct IntList const* if_8;
    if ((i_ == len_3)) {
        goto then_53;
    } else {
        goto else_54;
    }
then_53:;
    if_8 = acc_1;
    goto if_next_52;
else_54:;
    int arg_50 = item_;
    int arg_51 = len_3;
    struct IntList const* list_2 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_2))) = (struct IntList){.head = item_, .tail = acc_1};
    struct IntList const* arg_52 = list_2;
    int arg_53 = (i_ + 1);
    item_ = arg_50;
    len_3 = arg_51;
    acc_1 = arg_52;
    i_ = arg_53;
    goto tailrec_51;
if_next_52:;
    return if_8;
}

struct IntList const* listReplicate_(int item_, int len_3) {
    struct IntList const* call_8 = go_25(item_, len_3, NULL, 0);
    return call_8;
}

struct IntList const* go_26(int len_4, struct IntIntFun1 gen_, struct IntList const* acc_2, int i_1) {
tailrec_55:;
    struct IntList const* if_9;
    if ((i_1 == len_4)) {
        goto then_57;
    } else {
        goto else_58;
    }
then_57:;
    struct IntList const* call_9 = listRev_1(acc_2);
    if_9 = call_9;
    goto if_next_56;
else_58:;
    int arg_54 = len_4;
    struct IntIntFun1 arg_55 = gen_;
    int app_2 = gen_.fun(gen_.env, i_1);
    struct IntList const* list_3 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_3))) = (struct IntList){.head = app_2, .tail = acc_2};
    struct IntList const* arg_56 = list_3;
    int arg_57 = (i_1 + 1);
    len_4 = arg_54;
    gen_ = arg_55;
    acc_2 = arg_56;
    i_1 = arg_57;
    goto tailrec_55;
if_next_56:;
    return if_9;
}

struct IntList const* listInit_(int len_4, struct IntIntFun1 gen_) {
    milone_assert((len_4 >= 0), 79, 2);
    struct IntList const* call_10 = go_26(len_4, gen_, NULL, 0);
    return call_10;
}

struct StringStringListTuple2 go_5(struct StringList const* xs_11, int xn_) {
    struct StringStringListTuple2 match_6;
    if ((!((!(xs_11))))) goto next_60;
    milone_assert((xn_ == 0), 97, 8);
    struct StringStringListTuple2 tuple_2 = (struct StringStringListTuple2){.t0 = (struct String){.str = "", .len = 0}, .t1 = NULL};
    match_6 = tuple_2;
    goto end_match_59;
next_60:;
    if ((!(xs_11))) goto next_61;
    struct String x_2 = xs_11->head;
    struct StringList const* xs_12 = xs_11->tail;
    if ((xn_ != 1)) goto next_61;
    struct StringStringListTuple2 tuple_3 = (struct StringStringListTuple2){.t0 = x_2, .t1 = xs_12};
    match_6 = tuple_3;
    goto end_match_59;
next_61:;
    if ((!(xs_11))) goto next_62;
    struct String x_3 = xs_11->head;
    if ((!(xs_11->tail))) goto next_62;
    struct String y_1 = xs_11->tail->head;
    struct StringList const* xs_13 = xs_11->tail->tail;
    if ((xn_ != 2)) goto next_62;
    struct StringStringListTuple2 tuple_4 = (struct StringStringListTuple2){.t0 = str_add(x_3, y_1), .t1 = xs_13};
    match_6 = tuple_4;
    goto end_match_59;
next_62:;
    struct StringList const* xs_14 = xs_11;
    int m_ = (xn_ / 2);
    struct StringStringListTuple2 call_11 = go_5(xs_14, m_);
    struct String l_ = call_11.t0;
    struct StringList const* xs_15 = call_11.t1;
    struct StringStringListTuple2 call_12 = go_5(xs_15, (xn_ - m_));
    struct String r_ = call_12.t0;
    struct StringList const* xs_16 = call_12.t1;
    struct StringStringListTuple2 tuple_5 = (struct StringStringListTuple2){.t0 = str_add(l_, r_), .t1 = xs_16};
    match_6 = tuple_5;
    goto end_match_59;
next_63:;
end_match_59:;
    return match_6;
}

struct String Competitive_Helpers_strConcat(struct StringList const* xs_10) {
    int call_13 = listLength_1(xs_10);
    int n_ = call_13;
    struct StringStringListTuple2 call_14 = go_5(xs_10, n_);
    struct String s_ = call_14.t0;
    struct StringList const* xs_17 = call_14.t1;
    bool call_15 = listIsEmpty_(xs_17);
    milone_assert(call_15, 109, 2);
    return s_;
}

bool Competitive_Helpers_intEqual(int first_, int second_) {
    return (first_ == second_);
}

int Competitive_Helpers_intMin(int first_1, int second_1) {
    int if_10;
    if ((second_1 < first_1)) {
        goto then_65;
    } else {
        goto else_66;
    }
then_65:;
    if_10 = second_1;
    goto if_next_64;
else_66:;
    if_10 = first_1;
    goto if_next_64;
if_next_64:;
    return if_10;
}

int Competitive_Helpers_intMax(int first_2, int second_2) {
    int if_11;
    if ((first_2 < second_2)) {
        goto then_68;
    } else {
        goto else_69;
    }
then_68:;
    if_11 = second_2;
    goto if_next_67;
else_69:;
    if_11 = first_2;
    goto if_next_67;
if_next_67:;
    return if_11;
}

bool Competitive_Helpers_strEqual(struct String first_3, struct String second_3) {
    return (str_compare(first_3, second_3) == 0);
}

int failwith_(struct String msg_) {
    printf("ERROR %s\n", str_to_c_str(msg_));
    exit(1);
}

int fun_21(int arg_58) {
    int call_16 = Competitive_Helpers_scanInt(0);
    return call_16;
}

int fun_3(void const* env_, int arg_) {
    int call_17 = fun_21(arg_);
    return call_17;
}

struct IntList const* Competitive_Helpers_scanIntList(int len_5) {
    struct IntIntFun1 fun_24 = (struct IntIntFun1){.fun = fun_3, .env = NULL};
    struct IntList const* call_18 = listInit_(len_5, fun_24);
    return call_18;
}

struct IntVoidMutPtrFun1 typeToArrayNew_(struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6 arg_59) {
    struct IntVoidMutPtrFun1 arrayNew_ = arg_59.t2;
    char _typeTag_2 = arg_59.t5;
    return arrayNew_;
}

struct VoidMutPtrIntIntFun2 typeToArrayGet_(struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6 arg_60) {
    struct VoidMutPtrIntIntFun2 arrayGet_ = arg_60.t3;
    char _typeTag_3 = arg_60.t5;
    return arrayGet_;
}

struct VoidMutPtrIntIntUnitFun3 typeToArraySet_(struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6 arg_61) {
    struct VoidMutPtrIntIntUnitFun3 arraySet_ = arg_61.t4;
    char _typeTag_4 = arg_61.t5;
    return arraySet_;
}

void* fun_4(void const* env_1, int arg_1) {
    void* call_19 = Competitive_Helpers_rawIntArrayNew(arg_1);
    return call_19;
}

int fun_5(void const* env_2, void* arg_2, int arg_3) {
    int call_20 = Competitive_Helpers_rawIntArrayGet(arg_2, arg_3);
    return call_20;
}

char fun_6(void const* env_3, void* arg_4, int arg_5, int arg_6) {
    char call_21 = Competitive_Helpers_rawIntArraySet(arg_4, arg_5, arg_6);
    return 0;
}

int vectorToLength_(struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 arg_62) {
    int len_6 = arg_62.t2;
    char _vectorTag = arg_62.t4;
    return len_6;
}

struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 vectorNew_(struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6 itemTy_, int len_7) {
    struct IntVoidMutPtrFun1 call_22 = typeToArrayNew_(itemTy_);
    void* app_3 = call_22.fun(call_22.env, len_7);
    void* array_2 = app_3;
    struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 tuple_6 = (struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5){.t0 = itemTy_, .t1 = array_2, .t2 = len_7, .t3 = len_7, .t4 = 0};
    return tuple_6;
}

char vectorCheckIndex_(int index_2, struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 self_) {
    int call_23 = vectorToLength_(self_);
    int len_8 = call_23;
    bool if_12;
    if ((index_2 < 0)) {
        goto then_71;
    } else {
        goto else_72;
    }
then_71:;
    if_12 = true;
    goto if_next_70;
else_72:;
    if_12 = (index_2 >= len_8);
    goto if_next_70;
if_next_70:;
    char if_13;
    if (if_12) {
        goto then_74;
    } else {
        goto else_75;
    }
then_74:;
    printf("ERROR: Out of range (len = %d, index = %d)\n", len_8, index_2);
    exit(1);
else_75:;
    if_13 = 0;
    goto if_next_73;
if_next_73:;
    return 0;
}

int vectorGet_(int index_3, struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 self_1) {
    char call_24 = vectorCheckIndex_(index_3, self_1);
    struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6 itemTy_1 = self_1.t0;
    void* array_3 = self_1.t1;
    char _vectorTag_1 = self_1.t4;
    struct VoidMutPtrIntIntFun2 call_25 = typeToArrayGet_(itemTy_1);
    int app_4 = call_25.fun(call_25.env, array_3, index_3);
    return app_4;
}

char vectorSet_(int index_4, int value_1, struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 self_2) {
    char call_26 = vectorCheckIndex_(index_4, self_2);
    struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6 itemTy_2 = self_2.t0;
    void* array_4 = self_2.t1;
    char _vectorTag_2 = self_2.t4;
    struct VoidMutPtrIntIntUnitFun3 call_27 = typeToArraySet_(itemTy_2);
    char app_5 = call_27.fun(call_27.env, array_4, index_4, value_1);
    return 0;
}

char go_27(int len_10, struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 v_, int i_2, struct IntList const* xs_19) {
tailrec_76:;
    char match_7;
    if ((!((!(xs_19))))) goto next_78;
    milone_assert((i_2 == len_10), 205, 12);
    match_7 = 0;
    goto end_match_77;
next_78:;
    if ((!(xs_19))) goto next_79;
    int x_4 = xs_19->head;
    struct IntList const* xs_20 = xs_19->tail;
    char call_28 = vectorSet_(i_2, x_4, v_);
    int arg_63 = len_10;
    struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 arg_64 = v_;
    int arg_65 = (i_2 + 1);
    struct IntList const* arg_66 = xs_20;
    len_10 = arg_63;
    v_ = arg_64;
    i_2 = arg_65;
    xs_19 = arg_66;
    goto tailrec_76;
next_79:;
    exit(1);
end_match_77:;
    return 0;
}

struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 vectorOfList_(struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6 ty_, struct IntList const* xs_18) {
    int call_29 = listLength_(xs_18);
    int len_10 = call_29;
    struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 call_30 = vectorNew_(ty_, len_10);
    struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 v_ = call_30;
    char call_31 = go_27(len_10, v_, 0, xs_18);
    return v_;
}

char go_7(int len_11, struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 v_1, int i_3) {
tailrec_80:;
    char if_14;
    if ((i_3 < len_11)) {
        goto then_82;
    } else {
        goto else_83;
    }
then_82:;
    int call_32 = Competitive_Helpers_scanInt(0);
    int value_3 = call_32;
    char call_33 = vectorSet_(i_3, value_3, v_1);
    int arg_67 = len_11;
    struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 arg_68 = v_1;
    int arg_69 = (i_3 + 1);
    len_11 = arg_67;
    v_1 = arg_68;
    i_3 = arg_69;
    goto tailrec_80;
else_83:;
    if_14 = 0;
    goto if_next_81;
if_next_81:;
    return 0;
}

struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 Competitive_Helpers_scanIntVector(int len_11) {
    struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 call_34 = vectorNew_(Competitive_Helpers_typeInt, len_11);
    struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 v_1 = call_34;
    char call_35 = go_7(len_11, v_1, 0);
    return v_1;
}

char refCase_(char arg_70) {
    struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 call_36 = vectorNew_(Competitive_Helpers_typeInt, 1);
    struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 v_2 = call_36;
    int call_37 = vectorToLength_(v_2);
    milone_assert((call_37 == 1), 228, 4);
    int call_38 = vectorGet_(0, v_2);
    milone_assert((call_38 == 0), 229, 4);
    char call_39 = vectorSet_(0, 42, v_2);
    int call_40 = vectorGet_(0, v_2);
    milone_assert((call_40 == 42), 231, 4);
    return 0;
}

char vectorOfListTest_(char arg_71) {
    struct IntList const* list_6 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_6))) = (struct IntList){.head = 3, .tail = NULL};
    struct IntList const* list_5 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_5))) = (struct IntList){.head = 2, .tail = list_6};
    struct IntList const* list_4 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_4))) = (struct IntList){.head = 1, .tail = list_5};
    struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 call_41 = vectorOfList_(Competitive_Helpers_typeInt, list_4);
    struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 v_3 = call_41;
    int call_42 = vectorToLength_(v_3);
    milone_assert((call_42 == 3), 237, 4);
    int call_43 = vectorGet_(0, v_3);
    milone_assert((call_43 == 1), 238, 4);
    int call_44 = vectorGet_(1, v_3);
    milone_assert((call_44 == 2), 239, 4);
    int call_45 = vectorGet_(2, v_3);
    milone_assert((call_45 == 3), 240, 4);
    return 0;
}

char Competitive_Helpers_vectorTest(char arg_72) {
    char call_46 = refCase_(0);
    char call_47 = vectorOfListTest_(0);
    return 0;
}
