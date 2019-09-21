#include "milone.h"

int id_1(int x_);

enum Space_Tag;

struct Space_;

struct StringSpace_ListTuple2;

struct UnitSpace_Fun1;

struct StringUnitSpace_Fun1Tuple2;

struct Space_List;

struct Space_List* failwith_3(struct String msg_);

struct StringList;

struct StringList* failwith_2(struct String msg_);

struct Space_ failwith_1(struct String msg_);

struct StringList* cons_1(struct String head_, struct StringList* tail_);

struct Space_List* go_27(struct Space_List* acc_, struct Space_List* xs_2);

struct StringList* go_26(struct StringList* acc_, struct StringList* xs_2);

struct BoolList;

struct BoolList* go_29(struct BoolList* acc_, struct BoolList* xs_2);

struct Space_Space_Tuple2;

struct Space_Space_Tuple2List;

struct Space_Space_Tuple2List* go_28(struct Space_Space_Tuple2List* acc_, struct Space_Space_Tuple2List* xs_2);

struct Space_List* listRev_2(struct Space_List* xs_1);

struct StringList* listRev_1(struct StringList* xs_1);

struct BoolList* listRev_4(struct BoolList* xs_1);

struct Space_Space_Tuple2List* listRev_3(struct Space_Space_Tuple2List* xs_1);

struct Space_Space_Fun1;

struct Space_Space_Fun1Tuple1;

struct Space_List* go_25(struct Space_Space_Fun1Tuple1 arg_36, struct Space_List* acc_1, struct Space_List* xs_5);

struct Ty_Space_Fun1;

enum Ty_Tag;

struct Ty_;

struct Ty_List;

struct Ty_Space_Fun1Tuple1;

struct Space_List* go_24(struct Ty_Space_Fun1Tuple1 arg_37, struct Space_List* acc_1, struct Ty_List* xs_5);

struct Pat_Space_Fun1;

enum Pat_Tag;

struct Pat_;

struct Pat_List;

struct Pat_Pat_Tuple2;

struct Pat_Space_Fun1Tuple1;

struct Space_List* go_23(struct Pat_Space_Fun1Tuple1 arg_38, struct Space_List* acc_1, struct Pat_List* xs_5);

struct StringSpace_Tuple2BoolFun1;

struct StringSpace_Tuple2;

struct StringSpace_Tuple2BoolFun1Tuple1;

struct StringSpace_Tuple2List;

struct BoolList* go_22(struct StringSpace_Tuple2BoolFun1Tuple1 arg_39, struct BoolList* acc_1, struct StringSpace_Tuple2List* xs_5);

struct StringTy_Pat_ListCovering_Tuple4BoolFun1;

enum Covering_Tag;

struct Covering_;

struct StringTy_Pat_ListCovering_Tuple4;

struct StringTy_Pat_ListCovering_Tuple4BoolFun1Tuple1;

struct StringTy_Pat_ListCovering_Tuple4List;

struct BoolList* go_21(struct StringTy_Pat_ListCovering_Tuple4BoolFun1Tuple1 arg_40, struct BoolList* acc_1, struct StringTy_Pat_ListCovering_Tuple4List* xs_5);

struct Space_List* listMap_5(struct Space_Space_Fun1 f_, struct Space_List* xs_4);

struct Space_List* listMap_4(struct Ty_Space_Fun1 f_, struct Ty_List* xs_4);

struct Space_List* listMap_3(struct Pat_Space_Fun1 f_, struct Pat_List* xs_4);

struct BoolList* listMap_2(struct StringSpace_Tuple2BoolFun1 f_, struct StringSpace_Tuple2List* xs_4);

struct BoolList* listMap_1(struct StringTy_Pat_ListCovering_Tuple4BoolFun1 f_, struct StringTy_Pat_ListCovering_Tuple4List* xs_4);

struct IntSpace_Space_Tuple2Space_Fun2;

struct IntSpace_Space_Tuple2Space_Fun2Tuple1;

struct Space_List* go_20(struct IntSpace_Space_Tuple2Space_Fun2Tuple1 arg_41, struct Space_List* acc_2, int i_, struct Space_Space_Tuple2List* xs_8);

struct IntSpace_Space_Fun2;

struct IntSpace_Space_Fun2Tuple1;

struct Space_List* go_19(struct IntSpace_Space_Fun2Tuple1 arg_42, struct Space_List* acc_2, int i_, struct Space_List* xs_8);

struct Space_List* listMapWithIndex_2(struct IntSpace_Space_Tuple2Space_Fun2 f_1, struct Space_Space_Tuple2List* xs_7);

struct Space_List* listMapWithIndex_1(struct IntSpace_Space_Fun2 f_1, struct Space_List* xs_7);

struct Space_BoolFun1;

struct Space_BoolFun1Tuple1;

int go_18(struct Space_BoolFun1Tuple1 arg_43, struct Space_List* xs_11);

struct Space_Space_Tuple2BoolFun1;

struct Space_Space_Tuple2BoolFun1Tuple1;

int go_17(struct Space_Space_Tuple2BoolFun1Tuple1 arg_44, struct Space_Space_Tuple2List* xs_11);

struct BoolBoolFun1;

struct BoolBoolFun1Tuple1;

int go_16(struct BoolBoolFun1Tuple1 arg_45, struct BoolList* xs_11);

int listForAll_3(struct Space_BoolFun1 p_, struct Space_List* xs_10);

int listForAll_2(struct Space_Space_Tuple2BoolFun1 p_, struct Space_Space_Tuple2List* xs_10);

int listForAll_1(struct BoolBoolFun1 p_, struct BoolList* xs_10);

int go_15(struct Space_BoolFun1Tuple1 arg_46, struct Space_List* xs_14);

int listExists_1(struct Space_BoolFun1 p_1, struct Space_List* xs_13);

struct Space_Space_Space_Fun2;

struct Space_Space_Space_Fun2Tuple1;

struct Space_ go_14(struct Space_Space_Space_Fun2Tuple1 arg_47, struct Space_ state_1, struct Space_List* xs_17);

struct StringListSpace_StringListFun2;

struct StringListSpace_StringListFun2Tuple1;

struct StringList* go_13(struct StringListSpace_StringListFun2Tuple1 arg_48, struct StringList* state_1, struct Space_List* xs_17);

struct Space_ listFold_2(struct Space_Space_Space_Fun2 folder_, struct Space_ state_, struct Space_List* xs_16);

struct StringList* listFold_1(struct StringListSpace_StringListFun2 folder_, struct StringList* state_, struct Space_List* xs_16);

struct Space_ListSpace_ListTuple2;

struct Space_Space_Tuple2List* go_12(struct Space_Space_Tuple2List* acc_3, struct Space_List* xs_20, struct Space_List* ys_1);

struct Space_Space_Tuple2List* listZip_1(struct Space_List* xs_19, struct Space_List* ys_);

struct String go_7(struct StringList* xs_23);

struct String strConcat_(struct StringList* xs_22);

struct Space_ spaceCtor_(struct String tag_, struct Space_List* items_);

struct Space_ spaceRef_(struct String tag_1, struct UnitSpace_Fun1 thunk_);

struct Space_List* go_8(struct Space_List* spaces_1, struct Space_List* acc_4);

struct Space_ spaceUnion_(struct Space_List* spaces_);

int fun_9(void* env_, struct Space_ arg_);

int fun_10(void* env_1, struct Space_ arg_1);

int spaceIsEmpty_(struct Space_ space_3);

struct Space_ spaceDecompose_(struct Space_ space_4);

int fun_(struct Space_Space_Tuple2 arg_49, struct Space_Space_Tuple2 arg_50);

struct Space_Space_Tuple2Tuple1;

int fun_11(void* env_2, struct Space_Space_Tuple2 arg_2);

struct Space_Space_IntTuple3;

struct Space_ fun_2(struct Space_Space_IntTuple3 arg_51, int j_, struct Space_Space_Tuple2 arg_52);

struct Space_Space_IntTuple3Tuple1;

struct Space_ fun_12(void* env_3, int arg_4, struct Space_Space_Tuple2 arg_5);

struct Space_Space_StringSpace_ListSpace_ListTuple5;

struct Space_ fun_28(struct Space_Space_StringSpace_ListSpace_ListTuple5 arg_53, int i_1, struct Space_ __14);

struct Space_Space_StringSpace_ListSpace_ListTuple5Tuple1;

struct Space_ fun_13(void* env_4, int arg_7, struct Space_ arg_8);

struct Space_ fun_14(void* env_5, struct Space_ arg_10, struct Space_ arg_11);

struct Space_Space_Space_Tuple3;

struct Space_ fun_3(struct Space_Space_Space_Tuple3 arg_54, struct Space_ first_3);

struct Space_Space_Space_Tuple3Tuple1;

struct Space_ fun_15(void* env_6, struct Space_ arg_13);

struct Space_ spaceExclude_(struct Space_Space_Tuple2 arg_55, struct Space_ first_, struct Space_ second_);

int spaceCovers_(struct Space_Space_Tuple2 arg_56, struct Space_ other_, struct Space_ cover_);

struct StringList* fun_4(struct StringList* acc_7, struct Space_ space_8);

struct StringList* fun_16(void* env_7, struct StringList* arg_15, struct Space_ arg_16);

struct StringList* fun_5(struct StringList* acc_9, struct Space_ space_9);

struct StringList* fun_17(void* env_8, struct StringList* arg_17, struct Space_ arg_18);

struct StringList* go_9(struct Space_ space_7, struct StringList* acc_5);

struct String spaceToString_(struct Space_ space_6);

struct Space_Tuple1;

struct Space_Tuple1Tuple1;

struct Space_ fun_18(void* env_9, struct Ty_ arg_19);

struct Space_ fun_19(void* env_10, int arg_21);

struct Space_ thunk_2(struct Space_Tuple1 arg_57, int arg_58);

struct Space_ fun_20(void* env_11, int arg_23);

struct Space_ go_10(struct Space_Tuple1 arg_59, struct Ty_ ty_1);

struct Space_ tyToSpace_(struct Space_Tuple1 arg_60, struct Ty_ ty_);

struct Space_ fun_21(void* env_12, struct Pat_ arg_25);

struct Space_ go_11(struct Space_Space_Tuple2 arg_61, struct Pat_ pat_1);

struct Space_ patToSpace_(struct Space_Space_Tuple2 arg_62, struct Pat_ pat_);

struct Space_ fun_22(void* env_13, struct Pat_ arg_27);

struct Space_ patsToSpace_(struct Space_Space_Tuple2 arg_63, struct Pat_List* pats_);

struct Space_ fun_6(struct Space_Tuple1 arg_64, int arg_65);

struct Space_ fun_23(void* env_14, int arg_29);

int testSpaceIsEmpty_(struct Space_Space_Tuple2 arg_66, int arg_67);

int fun_24(void* env_15, int arg_31);

int fun_7(struct StringSpace_Tuple2 arg_68);

int fun_25(void* env_16, struct StringSpace_Tuple2 arg_32);

int testSpaceToString_(struct Space_Space_Tuple2 arg_69, int arg_70);

int fun_26(void* env_17, int arg_33);

struct BoolStringTuple2;

struct Covering_Covering_Tuple2;

int fun_8(struct Space_Space_Tuple2 arg_71, struct StringTy_Pat_ListCovering_Tuple4 arg_72);

int fun_27(void* env_18, struct StringTy_Pat_ListCovering_Tuple4 arg_34);

int main();

int id_1(int x_) {
    return x_;
}

enum Space_Tag {
    Full_,
    Ctor_,
    Ref_,
    Union_,
};

struct Space_ {
    enum Space_Tag tag;
    union {
        struct StringSpace_ListTuple2* Ctor_;
        struct StringUnitSpace_Fun1Tuple2* Ref_;
        struct Space_List** Union_;
    };
};

struct StringSpace_ListTuple2 {
    struct String t0;
    struct Space_List* t1;
};

struct UnitSpace_Fun1 {
    struct Space_(*fun)(void*, int);
    void* env;
};

struct StringUnitSpace_Fun1Tuple2 {
    struct String t0;
    struct UnitSpace_Fun1 t1;
};

struct Space_List {
    struct Space_ head;
    struct Space_List* tail;
};

struct Space_List* failwith_3(struct String msg_) {
    printf("ERROR %s\n", msg_.str);
    int call_ = 0;
    exit(1);
    return NULL;
}

struct StringList {
    struct String head;
    struct StringList* tail;
};

struct StringList* failwith_2(struct String msg_) {
    printf("ERROR %s\n", msg_.str);
    int call_1 = 0;
    exit(1);
    return NULL;
}

struct Space_ failwith_1(struct String msg_) {
    printf("ERROR %s\n", msg_.str);
    int call_2 = 0;
    exit(1);
    return ((struct Space_){});
}

struct StringList* cons_1(struct String head_, struct StringList* tail_) {
    struct StringList* list_ = (struct StringList*)malloc(sizeof(struct StringList));
    list_->head = head_;
    list_->tail = tail_;
    return list_;
}

struct Space_List* go_27(struct Space_List* acc_, struct Space_List* xs_2) {
    struct Space_List* match_;
    if ((!((!(xs_2))))) goto next_2;
    match_ = acc_;
    goto end_match_1;
next_2:;
    if ((!(xs_2))) goto next_3;
    struct Space_ x_2 = xs_2->head;
    struct Space_List* xs_3 = xs_2->tail;
    struct Space_List* list_1 = (struct Space_List*)malloc(sizeof(struct Space_List));
    list_1->head = x_2;
    list_1->tail = acc_;
    struct Space_List* call_3 = go_27(list_1, xs_3);
    match_ = call_3;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return match_;
}

struct StringList* go_26(struct StringList* acc_, struct StringList* xs_2) {
    struct StringList* match_1;
    if ((!((!(xs_2))))) goto next_5;
    match_1 = acc_;
    goto end_match_4;
next_5:;
    if ((!(xs_2))) goto next_6;
    struct String x_2 = xs_2->head;
    struct StringList* xs_3 = xs_2->tail;
    struct StringList* list_2 = (struct StringList*)malloc(sizeof(struct StringList));
    list_2->head = x_2;
    list_2->tail = acc_;
    struct StringList* call_4 = go_26(list_2, xs_3);
    match_1 = call_4;
    goto end_match_4;
next_6:;
    exit(1);
end_match_4:;
    return match_1;
}

struct BoolList {
    int head;
    struct BoolList* tail;
};

struct BoolList* go_29(struct BoolList* acc_, struct BoolList* xs_2) {
    struct BoolList* match_2;
    if ((!((!(xs_2))))) goto next_8;
    match_2 = acc_;
    goto end_match_7;
next_8:;
    if ((!(xs_2))) goto next_9;
    int x_2 = xs_2->head;
    struct BoolList* xs_3 = xs_2->tail;
    struct BoolList* list_3 = (struct BoolList*)malloc(sizeof(struct BoolList));
    list_3->head = x_2;
    list_3->tail = acc_;
    struct BoolList* call_5 = go_29(list_3, xs_3);
    match_2 = call_5;
    goto end_match_7;
next_9:;
    exit(1);
end_match_7:;
    return match_2;
}

struct Space_Space_Tuple2 {
    struct Space_ t0;
    struct Space_ t1;
};

struct Space_Space_Tuple2List {
    struct Space_Space_Tuple2 head;
    struct Space_Space_Tuple2List* tail;
};

struct Space_Space_Tuple2List* go_28(struct Space_Space_Tuple2List* acc_, struct Space_Space_Tuple2List* xs_2) {
    struct Space_Space_Tuple2List* match_3;
    if ((!((!(xs_2))))) goto next_11;
    match_3 = acc_;
    goto end_match_10;
next_11:;
    if ((!(xs_2))) goto next_12;
    struct Space_Space_Tuple2 x_2 = xs_2->head;
    struct Space_Space_Tuple2List* xs_3 = xs_2->tail;
    struct Space_Space_Tuple2List* list_4 = (struct Space_Space_Tuple2List*)malloc(sizeof(struct Space_Space_Tuple2List));
    list_4->head = x_2;
    list_4->tail = acc_;
    struct Space_Space_Tuple2List* call_6 = go_28(list_4, xs_3);
    match_3 = call_6;
    goto end_match_10;
next_12:;
    exit(1);
end_match_10:;
    return match_3;
}

struct Space_List* listRev_2(struct Space_List* xs_1) {
    struct Space_List* call_7 = go_27(NULL, xs_1);
    return call_7;
}

struct StringList* listRev_1(struct StringList* xs_1) {
    struct StringList* call_8 = go_26(NULL, xs_1);
    return call_8;
}

struct BoolList* listRev_4(struct BoolList* xs_1) {
    struct BoolList* call_9 = go_29(NULL, xs_1);
    return call_9;
}

struct Space_Space_Tuple2List* listRev_3(struct Space_Space_Tuple2List* xs_1) {
    struct Space_Space_Tuple2List* call_10 = go_28(NULL, xs_1);
    return call_10;
}

struct Space_Space_Fun1 {
    struct Space_(*fun)(void*, struct Space_);
    void* env;
};

struct Space_Space_Fun1Tuple1 {
    struct Space_Space_Fun1 t0;
};

struct Space_List* go_25(struct Space_Space_Fun1Tuple1 arg_36, struct Space_List* acc_1, struct Space_List* xs_5) {
    struct Space_Space_Fun1 f_ = arg_36.t0;
    struct Space_List* match_4;
    if ((!((!(xs_5))))) goto next_14;
    struct Space_List* call_11 = listRev_2(acc_1);
    match_4 = call_11;
    goto end_match_13;
next_14:;
    if ((!(xs_5))) goto next_15;
    struct Space_ x_3 = xs_5->head;
    struct Space_List* xs_6 = xs_5->tail;
    struct Space_Space_Fun1Tuple1 tuple_;
    tuple_.t0 = f_;
    struct Space_ app_ = f_.fun(f_.env, x_3);
    struct Space_List* list_5 = (struct Space_List*)malloc(sizeof(struct Space_List));
    list_5->head = app_;
    list_5->tail = acc_1;
    struct Space_List* call_12 = go_25(tuple_, list_5, xs_6);
    match_4 = call_12;
    goto end_match_13;
next_15:;
    exit(1);
end_match_13:;
    return match_4;
}

struct Ty_Space_Fun1 {
    struct Space_(*fun)(void*, struct Ty_);
    void* env;
};

enum Ty_Tag {
    Int_,
    Tuple_,
    List_,
};

struct Ty_ {
    enum Ty_Tag tag;
    union {
        struct Ty_List** Tuple_;
        struct Ty_* List_;
    };
};

struct Ty_List {
    struct Ty_ head;
    struct Ty_List* tail;
};

struct Ty_Space_Fun1Tuple1 {
    struct Ty_Space_Fun1 t0;
};

struct Space_List* go_24(struct Ty_Space_Fun1Tuple1 arg_37, struct Space_List* acc_1, struct Ty_List* xs_5) {
    struct Ty_Space_Fun1 f_ = arg_37.t0;
    struct Space_List* match_5;
    if ((!((!(xs_5))))) goto next_17;
    struct Space_List* call_13 = listRev_2(acc_1);
    match_5 = call_13;
    goto end_match_16;
next_17:;
    if ((!(xs_5))) goto next_18;
    struct Ty_ x_3 = xs_5->head;
    struct Ty_List* xs_6 = xs_5->tail;
    struct Ty_Space_Fun1Tuple1 tuple_1;
    tuple_1.t0 = f_;
    struct Space_ app_1 = f_.fun(f_.env, x_3);
    struct Space_List* list_6 = (struct Space_List*)malloc(sizeof(struct Space_List));
    list_6->head = app_1;
    list_6->tail = acc_1;
    struct Space_List* call_14 = go_24(tuple_1, list_6, xs_6);
    match_5 = call_14;
    goto end_match_16;
next_18:;
    exit(1);
end_match_16:;
    return match_5;
}

struct Pat_Space_Fun1 {
    struct Space_(*fun)(void*, struct Pat_);
    void* env;
};

enum Pat_Tag {
    Discard_,
    IntLit_,
    TupleLit_,
    Nil_,
    Cons_,
};

struct Pat_ {
    enum Pat_Tag tag;
    union {
        int* IntLit_;
        struct Pat_List** TupleLit_;
        struct Pat_Pat_Tuple2* Cons_;
    };
};

struct Pat_List {
    struct Pat_ head;
    struct Pat_List* tail;
};

struct Pat_Pat_Tuple2 {
    struct Pat_ t0;
    struct Pat_ t1;
};

struct Pat_Space_Fun1Tuple1 {
    struct Pat_Space_Fun1 t0;
};

struct Space_List* go_23(struct Pat_Space_Fun1Tuple1 arg_38, struct Space_List* acc_1, struct Pat_List* xs_5) {
    struct Pat_Space_Fun1 f_ = arg_38.t0;
    struct Space_List* match_6;
    if ((!((!(xs_5))))) goto next_20;
    struct Space_List* call_15 = listRev_2(acc_1);
    match_6 = call_15;
    goto end_match_19;
next_20:;
    if ((!(xs_5))) goto next_21;
    struct Pat_ x_3 = xs_5->head;
    struct Pat_List* xs_6 = xs_5->tail;
    struct Pat_Space_Fun1Tuple1 tuple_2;
    tuple_2.t0 = f_;
    struct Space_ app_2 = f_.fun(f_.env, x_3);
    struct Space_List* list_7 = (struct Space_List*)malloc(sizeof(struct Space_List));
    list_7->head = app_2;
    list_7->tail = acc_1;
    struct Space_List* call_16 = go_23(tuple_2, list_7, xs_6);
    match_6 = call_16;
    goto end_match_19;
next_21:;
    exit(1);
end_match_19:;
    return match_6;
}

struct StringSpace_Tuple2BoolFun1 {
    int(*fun)(void*, struct StringSpace_Tuple2);
    void* env;
};

struct StringSpace_Tuple2 {
    struct String t0;
    struct Space_ t1;
};

struct StringSpace_Tuple2BoolFun1Tuple1 {
    struct StringSpace_Tuple2BoolFun1 t0;
};

struct StringSpace_Tuple2List {
    struct StringSpace_Tuple2 head;
    struct StringSpace_Tuple2List* tail;
};

struct BoolList* go_22(struct StringSpace_Tuple2BoolFun1Tuple1 arg_39, struct BoolList* acc_1, struct StringSpace_Tuple2List* xs_5) {
    struct StringSpace_Tuple2BoolFun1 f_ = arg_39.t0;
    struct BoolList* match_7;
    if ((!((!(xs_5))))) goto next_23;
    struct BoolList* call_17 = listRev_4(acc_1);
    match_7 = call_17;
    goto end_match_22;
next_23:;
    if ((!(xs_5))) goto next_24;
    struct StringSpace_Tuple2 x_3 = xs_5->head;
    struct StringSpace_Tuple2List* xs_6 = xs_5->tail;
    struct StringSpace_Tuple2BoolFun1Tuple1 tuple_3;
    tuple_3.t0 = f_;
    int app_3 = f_.fun(f_.env, x_3);
    struct BoolList* list_8 = (struct BoolList*)malloc(sizeof(struct BoolList));
    list_8->head = app_3;
    list_8->tail = acc_1;
    struct BoolList* call_18 = go_22(tuple_3, list_8, xs_6);
    match_7 = call_18;
    goto end_match_22;
next_24:;
    exit(1);
end_match_22:;
    return match_7;
}

struct StringTy_Pat_ListCovering_Tuple4BoolFun1 {
    int(*fun)(void*, struct StringTy_Pat_ListCovering_Tuple4);
    void* env;
};

enum Covering_Tag {
    Covering_,
    Open_,
};

struct Covering_ {
    enum Covering_Tag tag;
};

struct StringTy_Pat_ListCovering_Tuple4 {
    struct String t0;
    struct Ty_ t1;
    struct Pat_List* t2;
    struct Covering_ t3;
};

struct StringTy_Pat_ListCovering_Tuple4BoolFun1Tuple1 {
    struct StringTy_Pat_ListCovering_Tuple4BoolFun1 t0;
};

struct StringTy_Pat_ListCovering_Tuple4List {
    struct StringTy_Pat_ListCovering_Tuple4 head;
    struct StringTy_Pat_ListCovering_Tuple4List* tail;
};

struct BoolList* go_21(struct StringTy_Pat_ListCovering_Tuple4BoolFun1Tuple1 arg_40, struct BoolList* acc_1, struct StringTy_Pat_ListCovering_Tuple4List* xs_5) {
    struct StringTy_Pat_ListCovering_Tuple4BoolFun1 f_ = arg_40.t0;
    struct BoolList* match_8;
    if ((!((!(xs_5))))) goto next_26;
    struct BoolList* call_19 = listRev_4(acc_1);
    match_8 = call_19;
    goto end_match_25;
next_26:;
    if ((!(xs_5))) goto next_27;
    struct StringTy_Pat_ListCovering_Tuple4 x_3 = xs_5->head;
    struct StringTy_Pat_ListCovering_Tuple4List* xs_6 = xs_5->tail;
    struct StringTy_Pat_ListCovering_Tuple4BoolFun1Tuple1 tuple_4;
    tuple_4.t0 = f_;
    int app_4 = f_.fun(f_.env, x_3);
    struct BoolList* list_9 = (struct BoolList*)malloc(sizeof(struct BoolList));
    list_9->head = app_4;
    list_9->tail = acc_1;
    struct BoolList* call_20 = go_21(tuple_4, list_9, xs_6);
    match_8 = call_20;
    goto end_match_25;
next_27:;
    exit(1);
end_match_25:;
    return match_8;
}

struct Space_List* listMap_5(struct Space_Space_Fun1 f_, struct Space_List* xs_4) {
    struct Space_Space_Fun1Tuple1 tuple_5;
    tuple_5.t0 = f_;
    struct Space_List* call_21 = go_25(tuple_5, NULL, xs_4);
    return call_21;
}

struct Space_List* listMap_4(struct Ty_Space_Fun1 f_, struct Ty_List* xs_4) {
    struct Ty_Space_Fun1Tuple1 tuple_6;
    tuple_6.t0 = f_;
    struct Space_List* call_22 = go_24(tuple_6, NULL, xs_4);
    return call_22;
}

struct Space_List* listMap_3(struct Pat_Space_Fun1 f_, struct Pat_List* xs_4) {
    struct Pat_Space_Fun1Tuple1 tuple_7;
    tuple_7.t0 = f_;
    struct Space_List* call_23 = go_23(tuple_7, NULL, xs_4);
    return call_23;
}

struct BoolList* listMap_2(struct StringSpace_Tuple2BoolFun1 f_, struct StringSpace_Tuple2List* xs_4) {
    struct StringSpace_Tuple2BoolFun1Tuple1 tuple_8;
    tuple_8.t0 = f_;
    struct BoolList* call_24 = go_22(tuple_8, NULL, xs_4);
    return call_24;
}

struct BoolList* listMap_1(struct StringTy_Pat_ListCovering_Tuple4BoolFun1 f_, struct StringTy_Pat_ListCovering_Tuple4List* xs_4) {
    struct StringTy_Pat_ListCovering_Tuple4BoolFun1Tuple1 tuple_9;
    tuple_9.t0 = f_;
    struct BoolList* call_25 = go_21(tuple_9, NULL, xs_4);
    return call_25;
}

struct IntSpace_Space_Tuple2Space_Fun2 {
    struct Space_(*fun)(void*, int, struct Space_Space_Tuple2);
    void* env;
};

struct IntSpace_Space_Tuple2Space_Fun2Tuple1 {
    struct IntSpace_Space_Tuple2Space_Fun2 t0;
};

struct Space_List* go_20(struct IntSpace_Space_Tuple2Space_Fun2Tuple1 arg_41, struct Space_List* acc_2, int i_, struct Space_Space_Tuple2List* xs_8) {
    struct IntSpace_Space_Tuple2Space_Fun2 f_1 = arg_41.t0;
    struct Space_List* match_9;
    if ((!((!(xs_8))))) goto next_29;
    struct Space_List* call_26 = listRev_2(acc_2);
    match_9 = call_26;
    goto end_match_28;
next_29:;
    if ((!(xs_8))) goto next_30;
    struct Space_Space_Tuple2 x_4 = xs_8->head;
    struct Space_Space_Tuple2List* xs_9 = xs_8->tail;
    struct IntSpace_Space_Tuple2Space_Fun2Tuple1 tuple_10;
    tuple_10.t0 = f_1;
    struct Space_ app_5 = f_1.fun(f_1.env, i_, x_4);
    struct Space_List* list_10 = (struct Space_List*)malloc(sizeof(struct Space_List));
    list_10->head = app_5;
    list_10->tail = acc_2;
    struct Space_List* call_27 = go_20(tuple_10, list_10, (i_ + 1), xs_9);
    match_9 = call_27;
    goto end_match_28;
next_30:;
    exit(1);
end_match_28:;
    return match_9;
}

struct IntSpace_Space_Fun2 {
    struct Space_(*fun)(void*, int, struct Space_);
    void* env;
};

struct IntSpace_Space_Fun2Tuple1 {
    struct IntSpace_Space_Fun2 t0;
};

struct Space_List* go_19(struct IntSpace_Space_Fun2Tuple1 arg_42, struct Space_List* acc_2, int i_, struct Space_List* xs_8) {
    struct IntSpace_Space_Fun2 f_1 = arg_42.t0;
    struct Space_List* match_10;
    if ((!((!(xs_8))))) goto next_32;
    struct Space_List* call_28 = listRev_2(acc_2);
    match_10 = call_28;
    goto end_match_31;
next_32:;
    if ((!(xs_8))) goto next_33;
    struct Space_ x_4 = xs_8->head;
    struct Space_List* xs_9 = xs_8->tail;
    struct IntSpace_Space_Fun2Tuple1 tuple_11;
    tuple_11.t0 = f_1;
    struct Space_ app_6 = f_1.fun(f_1.env, i_, x_4);
    struct Space_List* list_11 = (struct Space_List*)malloc(sizeof(struct Space_List));
    list_11->head = app_6;
    list_11->tail = acc_2;
    struct Space_List* call_29 = go_19(tuple_11, list_11, (i_ + 1), xs_9);
    match_10 = call_29;
    goto end_match_31;
next_33:;
    exit(1);
end_match_31:;
    return match_10;
}

struct Space_List* listMapWithIndex_2(struct IntSpace_Space_Tuple2Space_Fun2 f_1, struct Space_Space_Tuple2List* xs_7) {
    struct IntSpace_Space_Tuple2Space_Fun2Tuple1 tuple_12;
    tuple_12.t0 = f_1;
    struct Space_List* call_30 = go_20(tuple_12, NULL, 0, xs_7);
    return call_30;
}

struct Space_List* listMapWithIndex_1(struct IntSpace_Space_Fun2 f_1, struct Space_List* xs_7) {
    struct IntSpace_Space_Fun2Tuple1 tuple_13;
    tuple_13.t0 = f_1;
    struct Space_List* call_31 = go_19(tuple_13, NULL, 0, xs_7);
    return call_31;
}

struct Space_BoolFun1 {
    int(*fun)(void*, struct Space_);
    void* env;
};

struct Space_BoolFun1Tuple1 {
    struct Space_BoolFun1 t0;
};

int go_18(struct Space_BoolFun1Tuple1 arg_43, struct Space_List* xs_11) {
    struct Space_BoolFun1 p_ = arg_43.t0;
    int match_11;
    if ((!((!(xs_11))))) goto next_35;
    match_11 = 1;
    goto end_match_34;
next_35:;
    if ((!(xs_11))) goto next_36;
    struct Space_ x_5 = xs_11->head;
    struct Space_List* xs_12 = xs_11->tail;
    int match_12;
    int app_7 = p_.fun(p_.env, x_5);
    if ((!(app_7))) goto next_38;
    struct Space_BoolFun1Tuple1 tuple_14;
    tuple_14.t0 = p_;
    int call_32 = go_18(tuple_14, xs_12);
    match_12 = call_32;
    goto end_match_37;
next_38:;
    if (app_7) goto next_39;
    match_12 = 0;
    goto end_match_37;
next_39:;
    exit(1);
end_match_37:;
    match_11 = match_12;
    goto end_match_34;
next_36:;
    exit(1);
end_match_34:;
    return match_11;
}

struct Space_Space_Tuple2BoolFun1 {
    int(*fun)(void*, struct Space_Space_Tuple2);
    void* env;
};

struct Space_Space_Tuple2BoolFun1Tuple1 {
    struct Space_Space_Tuple2BoolFun1 t0;
};

int go_17(struct Space_Space_Tuple2BoolFun1Tuple1 arg_44, struct Space_Space_Tuple2List* xs_11) {
    struct Space_Space_Tuple2BoolFun1 p_ = arg_44.t0;
    int match_13;
    if ((!((!(xs_11))))) goto next_41;
    match_13 = 1;
    goto end_match_40;
next_41:;
    if ((!(xs_11))) goto next_42;
    struct Space_Space_Tuple2 x_5 = xs_11->head;
    struct Space_Space_Tuple2List* xs_12 = xs_11->tail;
    int match_14;
    int app_8 = p_.fun(p_.env, x_5);
    if ((!(app_8))) goto next_44;
    struct Space_Space_Tuple2BoolFun1Tuple1 tuple_15;
    tuple_15.t0 = p_;
    int call_33 = go_17(tuple_15, xs_12);
    match_14 = call_33;
    goto end_match_43;
next_44:;
    if (app_8) goto next_45;
    match_14 = 0;
    goto end_match_43;
next_45:;
    exit(1);
end_match_43:;
    match_13 = match_14;
    goto end_match_40;
next_42:;
    exit(1);
end_match_40:;
    return match_13;
}

struct BoolBoolFun1 {
    int(*fun)(void*, int);
    void* env;
};

struct BoolBoolFun1Tuple1 {
    struct BoolBoolFun1 t0;
};

int go_16(struct BoolBoolFun1Tuple1 arg_45, struct BoolList* xs_11) {
    struct BoolBoolFun1 p_ = arg_45.t0;
    int match_15;
    if ((!((!(xs_11))))) goto next_47;
    match_15 = 1;
    goto end_match_46;
next_47:;
    if ((!(xs_11))) goto next_48;
    int x_5 = xs_11->head;
    struct BoolList* xs_12 = xs_11->tail;
    int match_16;
    int app_9 = p_.fun(p_.env, x_5);
    if ((!(app_9))) goto next_50;
    struct BoolBoolFun1Tuple1 tuple_16;
    tuple_16.t0 = p_;
    int call_34 = go_16(tuple_16, xs_12);
    match_16 = call_34;
    goto end_match_49;
next_50:;
    if (app_9) goto next_51;
    match_16 = 0;
    goto end_match_49;
next_51:;
    exit(1);
end_match_49:;
    match_15 = match_16;
    goto end_match_46;
next_48:;
    exit(1);
end_match_46:;
    return match_15;
}

int listForAll_3(struct Space_BoolFun1 p_, struct Space_List* xs_10) {
    struct Space_BoolFun1Tuple1 tuple_17;
    tuple_17.t0 = p_;
    int call_35 = go_18(tuple_17, xs_10);
    return call_35;
}

int listForAll_2(struct Space_Space_Tuple2BoolFun1 p_, struct Space_Space_Tuple2List* xs_10) {
    struct Space_Space_Tuple2BoolFun1Tuple1 tuple_18;
    tuple_18.t0 = p_;
    int call_36 = go_17(tuple_18, xs_10);
    return call_36;
}

int listForAll_1(struct BoolBoolFun1 p_, struct BoolList* xs_10) {
    struct BoolBoolFun1Tuple1 tuple_19;
    tuple_19.t0 = p_;
    int call_37 = go_16(tuple_19, xs_10);
    return call_37;
}

int go_15(struct Space_BoolFun1Tuple1 arg_46, struct Space_List* xs_14) {
    struct Space_BoolFun1 p_1 = arg_46.t0;
    int match_17;
    if ((!((!(xs_14))))) goto next_53;
    match_17 = 0;
    goto end_match_52;
next_53:;
    if ((!(xs_14))) goto next_54;
    struct Space_ x_6 = xs_14->head;
    struct Space_List* xs_15 = xs_14->tail;
    int match_18;
    int app_10 = p_1.fun(p_1.env, x_6);
    if ((!(app_10))) goto next_56;
    match_18 = 1;
    goto end_match_55;
next_56:;
    if (app_10) goto next_57;
    struct Space_BoolFun1Tuple1 tuple_20;
    tuple_20.t0 = p_1;
    int call_38 = go_15(tuple_20, xs_15);
    match_18 = call_38;
    goto end_match_55;
next_57:;
    exit(1);
end_match_55:;
    match_17 = match_18;
    goto end_match_52;
next_54:;
    exit(1);
end_match_52:;
    return match_17;
}

int listExists_1(struct Space_BoolFun1 p_1, struct Space_List* xs_13) {
    struct Space_BoolFun1Tuple1 tuple_21;
    tuple_21.t0 = p_1;
    int call_39 = go_15(tuple_21, xs_13);
    return call_39;
}

struct Space_Space_Space_Fun2 {
    struct Space_(*fun)(void*, struct Space_, struct Space_);
    void* env;
};

struct Space_Space_Space_Fun2Tuple1 {
    struct Space_Space_Space_Fun2 t0;
};

struct Space_ go_14(struct Space_Space_Space_Fun2Tuple1 arg_47, struct Space_ state_1, struct Space_List* xs_17) {
    struct Space_Space_Space_Fun2 folder_ = arg_47.t0;
    struct Space_ match_19;
    if ((!((!(xs_17))))) goto next_59;
    match_19 = state_1;
    goto end_match_58;
next_59:;
    if ((!(xs_17))) goto next_60;
    struct Space_ x_7 = xs_17->head;
    struct Space_List* xs_18 = xs_17->tail;
    struct Space_Space_Space_Fun2Tuple1 tuple_22;
    tuple_22.t0 = folder_;
    struct Space_ app_11 = folder_.fun(folder_.env, state_1, x_7);
    struct Space_ call_40 = go_14(tuple_22, app_11, xs_18);
    match_19 = call_40;
    goto end_match_58;
next_60:;
    exit(1);
end_match_58:;
    return match_19;
}

struct StringListSpace_StringListFun2 {
    struct StringList*(*fun)(void*, struct StringList*, struct Space_);
    void* env;
};

struct StringListSpace_StringListFun2Tuple1 {
    struct StringListSpace_StringListFun2 t0;
};

struct StringList* go_13(struct StringListSpace_StringListFun2Tuple1 arg_48, struct StringList* state_1, struct Space_List* xs_17) {
    struct StringListSpace_StringListFun2 folder_ = arg_48.t0;
    struct StringList* match_20;
    if ((!((!(xs_17))))) goto next_62;
    match_20 = state_1;
    goto end_match_61;
next_62:;
    if ((!(xs_17))) goto next_63;
    struct Space_ x_7 = xs_17->head;
    struct Space_List* xs_18 = xs_17->tail;
    struct StringListSpace_StringListFun2Tuple1 tuple_23;
    tuple_23.t0 = folder_;
    struct StringList* app_12 = folder_.fun(folder_.env, state_1, x_7);
    struct StringList* call_41 = go_13(tuple_23, app_12, xs_18);
    match_20 = call_41;
    goto end_match_61;
next_63:;
    exit(1);
end_match_61:;
    return match_20;
}

struct Space_ listFold_2(struct Space_Space_Space_Fun2 folder_, struct Space_ state_, struct Space_List* xs_16) {
    struct Space_Space_Space_Fun2Tuple1 tuple_24;
    tuple_24.t0 = folder_;
    struct Space_ call_42 = go_14(tuple_24, state_, xs_16);
    return call_42;
}

struct StringList* listFold_1(struct StringListSpace_StringListFun2 folder_, struct StringList* state_, struct Space_List* xs_16) {
    struct StringListSpace_StringListFun2Tuple1 tuple_25;
    tuple_25.t0 = folder_;
    struct StringList* call_43 = go_13(tuple_25, state_, xs_16);
    return call_43;
}

struct Space_ListSpace_ListTuple2 {
    struct Space_List* t0;
    struct Space_List* t1;
};

struct Space_Space_Tuple2List* go_12(struct Space_Space_Tuple2List* acc_3, struct Space_List* xs_20, struct Space_List* ys_1) {
    struct Space_Space_Tuple2List* match_21;
    struct Space_ListSpace_ListTuple2 tuple_26;
    tuple_26.t0 = xs_20;
    tuple_26.t1 = ys_1;
    if ((!((!(tuple_26.t0))))) goto next_66;
    goto match_body_65;
next_66:;
    if ((!((!(tuple_26.t1))))) goto next_67;
    goto match_body_65;
match_body_65:;
    struct Space_Space_Tuple2List* call_44 = listRev_3(acc_3);
    match_21 = call_44;
    goto end_match_64;
next_67:;
    if ((!(tuple_26.t0))) goto next_68;
    struct Space_ x_8 = tuple_26.t0->head;
    struct Space_List* xs_21 = tuple_26.t0->tail;
    if ((!(tuple_26.t1))) goto next_68;
    struct Space_ y_ = tuple_26.t1->head;
    struct Space_List* ys_2 = tuple_26.t1->tail;
    struct Space_Space_Tuple2 tuple_27;
    tuple_27.t0 = x_8;
    tuple_27.t1 = y_;
    struct Space_Space_Tuple2List* list_12 = (struct Space_Space_Tuple2List*)malloc(sizeof(struct Space_Space_Tuple2List));
    list_12->head = tuple_27;
    list_12->tail = acc_3;
    struct Space_Space_Tuple2List* call_45 = go_12(list_12, xs_21, ys_2);
    match_21 = call_45;
    goto end_match_64;
next_68:;
    exit(1);
end_match_64:;
    return match_21;
}

struct Space_Space_Tuple2List* listZip_1(struct Space_List* xs_19, struct Space_List* ys_) {
    struct Space_Space_Tuple2List* call_46 = go_12(NULL, xs_19, ys_);
    return call_46;
}

struct String go_7(struct StringList* xs_23) {
    struct String match_22;
    if ((!((!(xs_23))))) goto next_70;
    match_22 = (struct String){.str = "", .len = 0};
    goto end_match_69;
next_70:;
    if ((!(xs_23))) goto next_71;
    struct String x_9 = xs_23->head;
    struct StringList* xs_24 = xs_23->tail;
    struct String call_47 = go_7(xs_24);
    match_22 = str_add(x_9, call_47);
    goto end_match_69;
next_71:;
    exit(1);
end_match_69:;
    return match_22;
}

struct String strConcat_(struct StringList* xs_22) {
    struct String call_48 = go_7(xs_22);
    return call_48;
}

struct Space_ spaceCtor_(struct String tag_, struct Space_List* items_) {
    struct StringSpace_ListTuple2 tuple_28;
    tuple_28.t0 = tag_;
    tuple_28.t1 = items_;
    struct StringSpace_ListTuple2* payload_ = (struct StringSpace_ListTuple2*)malloc(sizeof(struct StringSpace_ListTuple2));
    (*(((struct StringSpace_ListTuple2*)payload_))) = tuple_28;
    struct Space_ variant_ = (struct Space_){.tag = Ctor_, .Ctor_ = payload_};
    return variant_;
}

struct Space_ spaceRef_(struct String tag_1, struct UnitSpace_Fun1 thunk_) {
    struct StringUnitSpace_Fun1Tuple2 tuple_29;
    tuple_29.t0 = tag_1;
    tuple_29.t1 = thunk_;
    struct StringUnitSpace_Fun1Tuple2* payload_1 = (struct StringUnitSpace_Fun1Tuple2*)malloc(sizeof(struct StringUnitSpace_Fun1Tuple2));
    (*(((struct StringUnitSpace_Fun1Tuple2*)payload_1))) = tuple_29;
    struct Space_ variant_1 = (struct Space_){.tag = Ref_, .Ref_ = payload_1};
    return variant_1;
}

struct Space_List* go_8(struct Space_List* spaces_1, struct Space_List* acc_4) {
    struct Space_List* match_23;
    if ((!((!(spaces_1))))) goto next_73;
    struct Space_List* call_49 = listRev_2(acc_4);
    match_23 = call_49;
    goto end_match_72;
next_73:;
    if ((!(spaces_1))) goto next_74;
    if ((spaces_1->head.tag != Union_)) goto next_74;
    struct Space_List* subspaces_ = (*(spaces_1->head.Union_));
    struct Space_List* spaces_2 = spaces_1->tail;
    struct Space_List* call_50 = go_8(subspaces_, acc_4);
    struct Space_List* call_51 = go_8(spaces_2, call_50);
    match_23 = call_51;
    goto end_match_72;
next_74:;
    if ((!(spaces_1))) goto next_75;
    struct Space_ space_ = spaces_1->head;
    struct Space_List* spaces_3 = spaces_1->tail;
    int call_52 = spaceIsEmpty_(space_);
    if ((!(call_52))) goto next_75;
    struct Space_List* call_53 = go_8(spaces_3, acc_4);
    match_23 = call_53;
    goto end_match_72;
next_75:;
    if ((!(spaces_1))) goto next_76;
    struct Space_ space_1 = spaces_1->head;
    struct Space_List* spaces_4 = spaces_1->tail;
    struct Space_List* list_13 = (struct Space_List*)malloc(sizeof(struct Space_List));
    list_13->head = space_1;
    list_13->tail = acc_4;
    struct Space_List* call_54 = go_8(spaces_4, list_13);
    match_23 = call_54;
    goto end_match_72;
next_76:;
    struct Space_List* call_55 = failwith_3((struct String){.str = "NEVER: suppress warning", .len = 23});
    match_23 = call_55;
    goto end_match_72;
next_77:;
end_match_72:;
    return match_23;
}

struct Space_ spaceUnion_(struct Space_List* spaces_) {
    struct Space_ match_24;
    struct Space_List* call_56 = go_8(spaces_, NULL);
    if ((!(call_56))) goto next_79;
    struct Space_ space_2 = call_56->head;
    if ((!((!(call_56->tail))))) goto next_79;
    match_24 = space_2;
    goto end_match_78;
next_79:;
    struct Space_List* spaces_5 = call_56;
    struct Space_List** payload_2 = (struct Space_List**)malloc(sizeof(struct Space_List*));
    (*(((struct Space_List**)payload_2))) = spaces_5;
    struct Space_ variant_2 = (struct Space_){.tag = Union_, .Union_ = payload_2};
    match_24 = variant_2;
    goto end_match_78;
next_80:;
end_match_78:;
    return match_24;
}

int fun_9(void* env_, struct Space_ arg_) {
    int call_57 = spaceIsEmpty_(arg_);
    return call_57;
}

int fun_10(void* env_1, struct Space_ arg_1) {
    int call_58 = spaceIsEmpty_(arg_1);
    return call_58;
}

int spaceIsEmpty_(struct Space_ space_3) {
    int match_25;
    if ((space_3.tag != Ctor_)) goto next_82;
    struct Space_List* spaces_6 = (*(space_3.Ctor_)).t1;
    void* box_ = (void*)malloc(sizeof(int));
    (*(((int*)box_))) = 0;
    void* env_19 = box_;
    struct Space_BoolFun1 fun_29 = (struct Space_BoolFun1){.fun = fun_9, .env = env_19};
    int call_59 = listExists_1(fun_29, spaces_6);
    match_25 = call_59;
    goto end_match_81;
next_82:;
    if ((space_3.tag != Union_)) goto next_83;
    struct Space_List* spaces_7 = (*(space_3.Union_));
    void* box_1 = (void*)malloc(sizeof(int));
    (*(((int*)box_1))) = 0;
    void* env_20 = box_1;
    struct Space_BoolFun1 fun_30 = (struct Space_BoolFun1){.fun = fun_10, .env = env_20};
    int call_60 = listForAll_3(fun_30, spaces_7);
    match_25 = call_60;
    goto end_match_81;
next_83:;
    match_25 = 0;
    goto end_match_81;
next_84:;
end_match_81:;
    int result_ = match_25;
    return result_;
}

struct Space_ spaceDecompose_(struct Space_ space_4) {
    struct Space_ match_26;
    if ((space_4.tag != Ref_)) goto next_86;
    struct UnitSpace_Fun1 thunk_1 = (*(space_4.Ref_)).t1;
    struct Space_ app_13 = thunk_1.fun(thunk_1.env, 0);
    struct Space_ space_5 = app_13;
    int call_61 = spaceIsEmpty_(space_5);
    milone_assert((!(call_61)), 234, 4);
    int call_62 = 0;
    match_26 = space_5;
    goto end_match_85;
next_86:;
    milone_assert(0, 238, 4);
    int call_63 = 0;
    match_26 = space_4;
    goto end_match_85;
next_87:;
end_match_85:;
    return match_26;
}

int fun_(struct Space_Space_Tuple2 arg_49, struct Space_Space_Tuple2 arg_50) {
    struct Space_ spaceFull_ = arg_49.t0;
    struct Space_ spaceEmpty_ = arg_49.t1;
    struct Space_ first_1 = arg_50.t0;
    struct Space_ second_1 = arg_50.t1;
    struct Space_Space_Tuple2 tuple_30;
    tuple_30.t0 = spaceFull_;
    tuple_30.t1 = spaceEmpty_;
    int call_64 = spaceCovers_(tuple_30, first_1, second_1);
    return call_64;
}

struct Space_Space_Tuple2Tuple1 {
    struct Space_Space_Tuple2 t0;
};

int fun_11(void* env_2, struct Space_Space_Tuple2 arg_2) {
    struct Space_Space_Tuple2 arg_3 = (*(((struct Space_Space_Tuple2Tuple1*)env_2))).t0;
    int call_65 = fun_(arg_3, arg_2);
    return call_65;
}

struct Space_Space_IntTuple3 {
    struct Space_ t0;
    struct Space_ t1;
    int t2;
};

struct Space_ fun_2(struct Space_Space_IntTuple3 arg_51, int j_, struct Space_Space_Tuple2 arg_52) {
    struct Space_ spaceFull_ = arg_51.t0;
    struct Space_ spaceEmpty_ = arg_51.t1;
    int i_1 = arg_51.t2;
    struct Space_ first_2 = arg_52.t0;
    struct Space_ second_2 = arg_52.t1;
    struct Space_ match_27;
    if ((i_1 != j_)) goto next_89;
    struct Space_Space_Tuple2 tuple_31;
    tuple_31.t0 = spaceFull_;
    tuple_31.t1 = spaceEmpty_;
    struct Space_ call_66 = spaceExclude_(tuple_31, first_2, second_2);
    match_27 = call_66;
    goto end_match_88;
next_89:;
    if ((i_1 == j_)) goto next_90;
    match_27 = first_2;
    goto end_match_88;
next_90:;
    exit(1);
end_match_88:;
    return match_27;
}

struct Space_Space_IntTuple3Tuple1 {
    struct Space_Space_IntTuple3 t0;
};

struct Space_ fun_12(void* env_3, int arg_4, struct Space_Space_Tuple2 arg_5) {
    struct Space_Space_IntTuple3 arg_6 = (*(((struct Space_Space_IntTuple3Tuple1*)env_3))).t0;
    struct Space_ call_67 = fun_2(arg_6, arg_4, arg_5);
    return call_67;
}

struct Space_Space_StringSpace_ListSpace_ListTuple5 {
    struct Space_ t0;
    struct Space_ t1;
    struct String t2;
    struct Space_List* t3;
    struct Space_List* t4;
};

struct Space_ fun_28(struct Space_Space_StringSpace_ListSpace_ListTuple5 arg_53, int i_1, struct Space_ __14) {
    struct Space_ spaceFull_ = arg_53.t0;
    struct Space_ spaceEmpty_ = arg_53.t1;
    struct String tag_2 = arg_53.t2;
    struct Space_List* firsts_ = arg_53.t3;
    struct Space_List* seconds_ = arg_53.t4;
    struct Space_Space_IntTuple3 tuple_33;
    tuple_33.t0 = spaceFull_;
    tuple_33.t1 = spaceEmpty_;
    tuple_33.t2 = i_1;
    struct Space_Space_IntTuple3Tuple1 tuple_32;
    tuple_32.t0 = tuple_33;
    void* box_2 = (void*)malloc(sizeof(struct Space_Space_IntTuple3Tuple1));
    (*(((struct Space_Space_IntTuple3Tuple1*)box_2))) = tuple_32;
    void* env_21 = box_2;
    struct IntSpace_Space_Tuple2Space_Fun2 fun_31 = (struct IntSpace_Space_Tuple2Space_Fun2){.fun = fun_12, .env = env_21};
    struct Space_Space_Tuple2List* call_68 = listZip_1(firsts_, seconds_);
    struct Space_List* call_69 = listMapWithIndex_2(fun_31, call_68);
    struct Space_ call_70 = spaceCtor_(tag_2, call_69);
    return call_70;
}

struct Space_Space_StringSpace_ListSpace_ListTuple5Tuple1 {
    struct Space_Space_StringSpace_ListSpace_ListTuple5 t0;
};

struct Space_ fun_13(void* env_4, int arg_7, struct Space_ arg_8) {
    struct Space_Space_StringSpace_ListSpace_ListTuple5 arg_9 = (*(((struct Space_Space_StringSpace_ListSpace_ListTuple5Tuple1*)env_4))).t0;
    struct Space_ call_71 = fun_28(arg_9, arg_7, arg_8);
    return call_71;
}

struct Space_ fun_14(void* env_5, struct Space_ arg_10, struct Space_ arg_11) {
    struct Space_Space_Tuple2 arg_12 = (*(((struct Space_Space_Tuple2Tuple1*)env_5))).t0;
    struct Space_ call_72 = spaceExclude_(arg_12, arg_10, arg_11);
    return call_72;
}

struct Space_Space_Space_Tuple3 {
    struct Space_ t0;
    struct Space_ t1;
    struct Space_ t2;
};

struct Space_ fun_3(struct Space_Space_Space_Tuple3 arg_54, struct Space_ first_3) {
    struct Space_ spaceFull_ = arg_54.t0;
    struct Space_ spaceEmpty_ = arg_54.t1;
    struct Space_ second_ = arg_54.t2;
    struct Space_Space_Tuple2 tuple_34;
    tuple_34.t0 = spaceFull_;
    tuple_34.t1 = spaceEmpty_;
    struct Space_ call_73 = spaceExclude_(tuple_34, first_3, second_);
    return call_73;
}

struct Space_Space_Space_Tuple3Tuple1 {
    struct Space_Space_Space_Tuple3 t0;
};

struct Space_ fun_15(void* env_6, struct Space_ arg_13) {
    struct Space_Space_Space_Tuple3 arg_14 = (*(((struct Space_Space_Space_Tuple3Tuple1*)env_6))).t0;
    struct Space_ call_74 = fun_3(arg_14, arg_13);
    return call_74;
}

struct Space_ spaceExclude_(struct Space_Space_Tuple2 arg_55, struct Space_ first_, struct Space_ second_) {
    struct Space_ spaceFull_ = arg_55.t0;
    struct Space_ spaceEmpty_ = arg_55.t1;
    struct Space_ match_28;
    struct Space_Space_Tuple2 tuple_35;
    tuple_35.t0 = first_;
    tuple_35.t1 = second_;
    if ((tuple_35.t0.tag != Union_)) goto next_92;
    if ((!((!((*(tuple_35.t0.Union_))))))) goto next_92;
    match_28 = spaceEmpty_;
    goto end_match_91;
next_92:;
    if ((tuple_35.t1.tag != Union_)) goto next_93;
    if ((!((!((*(tuple_35.t1.Union_))))))) goto next_93;
    match_28 = first_;
    goto end_match_91;
next_93:;
    if ((tuple_35.t1.tag != Full_)) goto next_94;
    match_28 = spaceEmpty_;
    goto end_match_91;
next_94:;
    if ((tuple_35.t0.tag != Full_)) goto next_95;
    if ((tuple_35.t1.tag != Ctor_)) goto next_95;
    match_28 = spaceFull_;
    goto end_match_91;
next_95:;
    if ((tuple_35.t0.tag != Ctor_)) goto next_96;
    struct String tag_2 = (*(tuple_35.t0.Ctor_)).t0;
    struct Space_List* firsts_ = (*(tuple_35.t0.Ctor_)).t1;
    if ((tuple_35.t1.tag != Ctor_)) goto next_96;
    struct String secondTag_ = (*(tuple_35.t1.Ctor_)).t0;
    struct Space_List* seconds_ = (*(tuple_35.t1.Ctor_)).t1;
    if ((str_cmp(tag_2, secondTag_) != 0)) goto next_96;
    struct Space_Space_Tuple2 tuple_37;
    tuple_37.t0 = spaceFull_;
    tuple_37.t1 = spaceEmpty_;
    struct Space_Space_Tuple2Tuple1 tuple_36;
    tuple_36.t0 = tuple_37;
    void* box_3 = (void*)malloc(sizeof(struct Space_Space_Tuple2Tuple1));
    (*(((struct Space_Space_Tuple2Tuple1*)box_3))) = tuple_36;
    void* env_22 = box_3;
    struct Space_Space_Tuple2BoolFun1 fun_32 = (struct Space_Space_Tuple2BoolFun1){.fun = fun_11, .env = env_22};
    struct Space_Space_Tuple2List* call_75 = listZip_1(firsts_, seconds_);
    int call_76 = listForAll_2(fun_32, call_75);
    int dominant_ = call_76;
    struct Space_ match_29;
    if ((!(dominant_))) goto next_104;
    match_29 = spaceEmpty_;
    goto end_match_103;
next_104:;
    if (dominant_) goto next_105;
    struct Space_Space_StringSpace_ListSpace_ListTuple5 tuple_39;
    tuple_39.t0 = spaceFull_;
    tuple_39.t1 = spaceEmpty_;
    tuple_39.t2 = tag_2;
    tuple_39.t3 = firsts_;
    tuple_39.t4 = seconds_;
    struct Space_Space_StringSpace_ListSpace_ListTuple5Tuple1 tuple_38;
    tuple_38.t0 = tuple_39;
    void* box_4 = (void*)malloc(sizeof(struct Space_Space_StringSpace_ListSpace_ListTuple5Tuple1));
    (*(((struct Space_Space_StringSpace_ListSpace_ListTuple5Tuple1*)box_4))) = tuple_38;
    void* env_23 = box_4;
    struct IntSpace_Space_Fun2 fun_33 = (struct IntSpace_Space_Fun2){.fun = fun_13, .env = env_23};
    struct Space_List* call_77 = listMapWithIndex_1(fun_33, firsts_);
    struct Space_ call_78 = spaceUnion_(call_77);
    match_29 = call_78;
    goto end_match_103;
next_105:;
    exit(1);
end_match_103:;
    match_28 = match_29;
    goto end_match_91;
next_96:;
    if ((tuple_35.t0.tag != Ctor_)) goto next_97;
    if ((tuple_35.t1.tag != Ctor_)) goto next_97;
    match_28 = first_;
    goto end_match_91;
next_97:;
    if ((tuple_35.t1.tag != Union_)) goto next_98;
    struct Space_List* seconds_1 = (*(tuple_35.t1.Union_));
    struct Space_Space_Tuple2 tuple_41;
    tuple_41.t0 = spaceFull_;
    tuple_41.t1 = spaceEmpty_;
    struct Space_Space_Tuple2Tuple1 tuple_40;
    tuple_40.t0 = tuple_41;
    void* box_5 = (void*)malloc(sizeof(struct Space_Space_Tuple2Tuple1));
    (*(((struct Space_Space_Tuple2Tuple1*)box_5))) = tuple_40;
    void* env_24 = box_5;
    struct Space_Space_Space_Fun2 fun_34 = (struct Space_Space_Space_Fun2){.fun = fun_14, .env = env_24};
    struct Space_ call_79 = listFold_2(fun_34, first_, seconds_1);
    match_28 = call_79;
    goto end_match_91;
next_98:;
    if ((tuple_35.t0.tag != Union_)) goto next_99;
    struct Space_List* firsts_1 = (*(tuple_35.t0.Union_));
    struct Space_Space_Space_Tuple3 tuple_43;
    tuple_43.t0 = spaceFull_;
    tuple_43.t1 = spaceEmpty_;
    tuple_43.t2 = second_;
    struct Space_Space_Space_Tuple3Tuple1 tuple_42;
    tuple_42.t0 = tuple_43;
    void* box_6 = (void*)malloc(sizeof(struct Space_Space_Space_Tuple3Tuple1));
    (*(((struct Space_Space_Space_Tuple3Tuple1*)box_6))) = tuple_42;
    void* env_25 = box_6;
    struct Space_Space_Fun1 fun_35 = (struct Space_Space_Fun1){.fun = fun_15, .env = env_25};
    struct Space_List* call_80 = listMap_5(fun_35, firsts_1);
    struct Space_ call_81 = spaceUnion_(call_80);
    match_28 = call_81;
    goto end_match_91;
next_99:;
    if ((tuple_35.t0.tag != Ref_)) goto next_100;
    struct String tag_3 = (*(tuple_35.t0.Ref_)).t0;
    if ((tuple_35.t1.tag != Ref_)) goto next_100;
    struct String secondTag_1 = (*(tuple_35.t1.Ref_)).t0;
    if ((str_cmp(tag_3, secondTag_1) != 0)) goto next_100;
    match_28 = spaceEmpty_;
    goto end_match_91;
next_100:;
    if ((tuple_35.t0.tag != Ref_)) goto next_101;
    struct Space_Space_Tuple2 tuple_44;
    tuple_44.t0 = spaceFull_;
    tuple_44.t1 = spaceEmpty_;
    struct Space_ call_82 = spaceDecompose_(first_);
    struct Space_ call_83 = spaceExclude_(tuple_44, call_82, second_);
    match_28 = call_83;
    goto end_match_91;
next_101:;
    if ((tuple_35.t1.tag != Ref_)) goto next_102;
    milone_assert(0, 345, 4);
    int call_84 = 0;
    struct Space_Space_Tuple2 tuple_45;
    tuple_45.t0 = spaceFull_;
    tuple_45.t1 = spaceEmpty_;
    struct Space_ call_85 = spaceDecompose_(second_);
    struct Space_ call_86 = spaceExclude_(tuple_45, first_, call_85);
    match_28 = call_86;
    goto end_match_91;
next_102:;
end_match_91:;
    return match_28;
}

int spaceCovers_(struct Space_Space_Tuple2 arg_56, struct Space_ other_, struct Space_ cover_) {
    struct Space_ spaceFull_ = arg_56.t0;
    struct Space_ spaceEmpty_ = arg_56.t1;
    struct Space_Space_Tuple2 tuple_46;
    tuple_46.t0 = spaceFull_;
    tuple_46.t1 = spaceEmpty_;
    struct Space_ call_87 = spaceExclude_(tuple_46, other_, cover_);
    int call_88 = spaceIsEmpty_(call_87);
    return call_88;
}

struct StringList* fun_4(struct StringList* acc_7, struct Space_ space_8) {
    struct StringList* call_89 = cons_1((struct String){.str = ", ", .len = 2}, acc_7);
    struct StringList* call_90 = go_9(space_8, call_89);
    return call_90;
}

struct StringList* fun_16(void* env_7, struct StringList* arg_15, struct Space_ arg_16) {
    struct StringList* call_91 = fun_4(arg_15, arg_16);
    return call_91;
}

struct StringList* fun_5(struct StringList* acc_9, struct Space_ space_9) {
    struct StringList* call_92 = cons_1((struct String){.str = ", ", .len = 2}, acc_9);
    struct StringList* call_93 = go_9(space_9, call_92);
    return call_93;
}

struct StringList* fun_17(void* env_8, struct StringList* arg_17, struct Space_ arg_18) {
    struct StringList* call_94 = fun_5(arg_17, arg_18);
    return call_94;
}

struct StringList* go_9(struct Space_ space_7, struct StringList* acc_5) {
    struct StringList* match_30;
    if ((space_7.tag != Full_)) goto next_107;
    struct StringList* call_95 = cons_1((struct String){.str = "full", .len = 4}, acc_5);
    match_30 = call_95;
    goto end_match_106;
next_107:;
    if ((space_7.tag != Ctor_)) goto next_108;
    struct String tag_4 = (*(space_7.Ctor_)).t0;
    if ((!((!((*(space_7.Ctor_)).t1))))) goto next_108;
    struct StringList* call_96 = cons_1(tag_4, acc_5);
    match_30 = call_96;
    goto end_match_106;
next_108:;
    if ((space_7.tag != Ctor_)) goto next_109;
    struct String tag_5 = (*(space_7.Ctor_)).t0;
    if ((!((*(space_7.Ctor_)).t1))) goto next_109;
    struct Space_ item_ = (*(space_7.Ctor_)).t1->head;
    struct Space_List* items_1 = (*(space_7.Ctor_)).t1->tail;
    struct StringList* call_97 = cons_1(tag_5, acc_5);
    struct StringList* call_98 = cons_1((struct String){.str = "(", .len = 1}, call_97);
    struct StringList* call_99 = go_9(item_, call_98);
    struct StringList* acc_6 = call_99;
    void* box_7 = (void*)malloc(sizeof(int));
    (*(((int*)box_7))) = 0;
    void* env_26 = box_7;
    struct StringListSpace_StringListFun2 fun_36 = (struct StringListSpace_StringListFun2){.fun = fun_16, .env = env_26};
    struct StringList* call_100 = listFold_1(fun_36, acc_6, items_1);
    struct StringList* call_101 = cons_1((struct String){.str = ")", .len = 1}, call_100);
    match_30 = call_101;
    goto end_match_106;
next_109:;
    if ((space_7.tag != Ref_)) goto next_110;
    struct String tag_6 = (*(space_7.Ref_)).t0;
    struct StringList* call_102 = cons_1(tag_6, acc_5);
    match_30 = call_102;
    goto end_match_106;
next_110:;
    if ((space_7.tag != Union_)) goto next_111;
    if ((!((!((*(space_7.Union_))))))) goto next_111;
    struct StringList* call_103 = cons_1((struct String){.str = "empty", .len = 5}, acc_5);
    match_30 = call_103;
    goto end_match_106;
next_111:;
    if ((space_7.tag != Union_)) goto next_112;
    if ((!((*(space_7.Union_))))) goto next_112;
    struct Space_ subspace_ = (*(space_7.Union_))->head;
    struct Space_List* subspaces_1 = (*(space_7.Union_))->tail;
    struct StringList* call_104 = cons_1((struct String){.str = "+(", .len = 2}, acc_5);
    struct StringList* call_105 = go_9(subspace_, call_104);
    struct StringList* acc_8 = call_105;
    void* box_8 = (void*)malloc(sizeof(int));
    (*(((int*)box_8))) = 0;
    void* env_27 = box_8;
    struct StringListSpace_StringListFun2 fun_37 = (struct StringListSpace_StringListFun2){.fun = fun_17, .env = env_27};
    struct StringList* call_106 = listFold_1(fun_37, acc_8, subspaces_1);
    struct StringList* call_107 = cons_1((struct String){.str = ")", .len = 1}, call_106);
    match_30 = call_107;
    goto end_match_106;
next_112:;
    struct StringList* call_108 = failwith_2((struct String){.str = "NEVER: suppress warning", .len = 23});
    match_30 = call_108;
    goto end_match_106;
next_113:;
end_match_106:;
    return match_30;
}

struct String spaceToString_(struct Space_ space_6) {
    struct StringList* call_109 = go_9(space_6, NULL);
    struct StringList* call_110 = listRev_1(call_109);
    struct String call_111 = strConcat_(call_110);
    return call_111;
}

struct Space_Tuple1 {
    struct Space_ t0;
};

struct Space_Tuple1Tuple1 {
    struct Space_Tuple1 t0;
};

struct Space_ fun_18(void* env_9, struct Ty_ arg_19) {
    struct Space_Tuple1 arg_20 = (*(((struct Space_Tuple1Tuple1*)env_9))).t0;
    struct Space_ call_112 = go_10(arg_20, arg_19);
    return call_112;
}

struct Space_ fun_19(void* env_10, int arg_21) {
    struct Space_Tuple1 arg_22 = (*(((struct Space_Tuple1Tuple1*)env_10))).t0;
    struct Space_ call_113 = thunk_2(arg_22, 0);
    return call_113;
}

struct Space_ thunk_2(struct Space_Tuple1 arg_57, int arg_58) {
    struct Space_ itemSpace_ = arg_57.t0;
    struct Space_ call_114 = spaceCtor_((struct String){.str = "nil", .len = 3}, NULL);
    struct Space_Tuple1 tuple_48;
    tuple_48.t0 = itemSpace_;
    struct Space_Tuple1Tuple1 tuple_47;
    tuple_47.t0 = tuple_48;
    void* box_9 = (void*)malloc(sizeof(struct Space_Tuple1Tuple1));
    (*(((struct Space_Tuple1Tuple1*)box_9))) = tuple_47;
    void* env_28 = box_9;
    struct UnitSpace_Fun1 fun_38 = (struct UnitSpace_Fun1){.fun = fun_19, .env = env_28};
    struct Space_ call_115 = spaceRef_((struct String){.str = "list", .len = 4}, fun_38);
    struct Space_List* list_17 = (struct Space_List*)malloc(sizeof(struct Space_List));
    list_17->head = call_115;
    list_17->tail = NULL;
    struct Space_List* list_16 = (struct Space_List*)malloc(sizeof(struct Space_List));
    list_16->head = itemSpace_;
    list_16->tail = list_17;
    struct Space_ call_116 = spaceCtor_((struct String){.str = "cons", .len = 4}, list_16);
    struct Space_List* list_15 = (struct Space_List*)malloc(sizeof(struct Space_List));
    list_15->head = call_116;
    list_15->tail = NULL;
    struct Space_List* list_14 = (struct Space_List*)malloc(sizeof(struct Space_List));
    list_14->head = call_114;
    list_14->tail = list_15;
    struct Space_ call_117 = spaceUnion_(list_14);
    return call_117;
}

struct Space_ fun_20(void* env_11, int arg_23) {
    struct Space_Tuple1 arg_24 = (*(((struct Space_Tuple1Tuple1*)env_11))).t0;
    struct Space_ call_118 = thunk_2(arg_24, 0);
    return call_118;
}

struct Space_ go_10(struct Space_Tuple1 arg_59, struct Ty_ ty_1) {
    struct Space_ spaceFull_ = arg_59.t0;
    struct Space_ match_31;
    if ((ty_1.tag != Int_)) goto next_115;
    match_31 = spaceFull_;
    goto end_match_114;
next_115:;
    if ((ty_1.tag != Tuple_)) goto next_116;
    struct Ty_List* itemTys_ = (*(ty_1.Tuple_));
    struct Space_Tuple1 tuple_50;
    tuple_50.t0 = spaceFull_;
    struct Space_Tuple1Tuple1 tuple_49;
    tuple_49.t0 = tuple_50;
    void* box_10 = (void*)malloc(sizeof(struct Space_Tuple1Tuple1));
    (*(((struct Space_Tuple1Tuple1*)box_10))) = tuple_49;
    void* env_29 = box_10;
    struct Ty_Space_Fun1 fun_39 = (struct Ty_Space_Fun1){.fun = fun_18, .env = env_29};
    struct Space_List* call_119 = listMap_4(fun_39, itemTys_);
    struct Space_ call_120 = spaceCtor_((struct String){.str = "tuple", .len = 5}, call_119);
    match_31 = call_120;
    goto end_match_114;
next_116:;
    if ((ty_1.tag != List_)) goto next_117;
    struct Ty_ itemTy_ = (*(ty_1.List_));
    struct Space_Tuple1 tuple_51;
    tuple_51.t0 = spaceFull_;
    struct Space_ call_121 = go_10(tuple_51, itemTy_);
    struct Space_ itemSpace_ = call_121;
    struct Space_Tuple1 tuple_53;
    tuple_53.t0 = itemSpace_;
    struct Space_Tuple1Tuple1 tuple_52;
    tuple_52.t0 = tuple_53;
    void* box_11 = (void*)malloc(sizeof(struct Space_Tuple1Tuple1));
    (*(((struct Space_Tuple1Tuple1*)box_11))) = tuple_52;
    void* env_30 = box_11;
    struct UnitSpace_Fun1 fun_40 = (struct UnitSpace_Fun1){.fun = fun_20, .env = env_30};
    struct Space_ call_122 = spaceRef_((struct String){.str = "list", .len = 4}, fun_40);
    match_31 = call_122;
    goto end_match_114;
next_117:;
end_match_114:;
    return match_31;
}

struct Space_ tyToSpace_(struct Space_Tuple1 arg_60, struct Ty_ ty_) {
    struct Space_ spaceFull_ = arg_60.t0;
    struct Space_Tuple1 tuple_54;
    tuple_54.t0 = spaceFull_;
    struct Space_ call_123 = go_10(tuple_54, ty_);
    return call_123;
}

struct Space_ fun_21(void* env_12, struct Pat_ arg_25) {
    struct Space_Space_Tuple2 arg_26 = (*(((struct Space_Space_Tuple2Tuple1*)env_12))).t0;
    struct Space_ call_124 = go_11(arg_26, arg_25);
    return call_124;
}

struct Space_ go_11(struct Space_Space_Tuple2 arg_61, struct Pat_ pat_1) {
    struct Space_ spaceFull_ = arg_61.t0;
    struct Space_ spaceEmpty_ = arg_61.t1;
    struct Space_ match_32;
    if ((pat_1.tag != Discard_)) goto next_119;
    match_32 = spaceFull_;
    goto end_match_118;
next_119:;
    if ((pat_1.tag != IntLit_)) goto next_120;
    match_32 = spaceEmpty_;
    goto end_match_118;
next_120:;
    if ((pat_1.tag != TupleLit_)) goto next_121;
    struct Pat_List* itemPats_ = (*(pat_1.TupleLit_));
    struct Space_Space_Tuple2 tuple_56;
    tuple_56.t0 = spaceFull_;
    tuple_56.t1 = spaceEmpty_;
    struct Space_Space_Tuple2Tuple1 tuple_55;
    tuple_55.t0 = tuple_56;
    void* box_12 = (void*)malloc(sizeof(struct Space_Space_Tuple2Tuple1));
    (*(((struct Space_Space_Tuple2Tuple1*)box_12))) = tuple_55;
    void* env_31 = box_12;
    struct Pat_Space_Fun1 fun_41 = (struct Pat_Space_Fun1){.fun = fun_21, .env = env_31};
    struct Space_List* call_125 = listMap_3(fun_41, itemPats_);
    struct Space_ call_126 = spaceCtor_((struct String){.str = "tuple", .len = 5}, call_125);
    match_32 = call_126;
    goto end_match_118;
next_121:;
    if ((pat_1.tag != Nil_)) goto next_122;
    struct Space_ call_127 = spaceCtor_((struct String){.str = "nil", .len = 3}, NULL);
    match_32 = call_127;
    goto end_match_118;
next_122:;
    if ((pat_1.tag != Cons_)) goto next_123;
    struct Pat_ headPat_ = (*(pat_1.Cons_)).t0;
    struct Pat_ tailPat_ = (*(pat_1.Cons_)).t1;
    struct Space_Space_Tuple2 tuple_57;
    tuple_57.t0 = spaceFull_;
    tuple_57.t1 = spaceEmpty_;
    struct Space_ call_128 = go_11(tuple_57, headPat_);
    struct Space_Space_Tuple2 tuple_58;
    tuple_58.t0 = spaceFull_;
    tuple_58.t1 = spaceEmpty_;
    struct Space_ call_129 = go_11(tuple_58, tailPat_);
    struct Space_List* list_19 = (struct Space_List*)malloc(sizeof(struct Space_List));
    list_19->head = call_129;
    list_19->tail = NULL;
    struct Space_List* list_18 = (struct Space_List*)malloc(sizeof(struct Space_List));
    list_18->head = call_128;
    list_18->tail = list_19;
    struct Space_ call_130 = spaceCtor_((struct String){.str = "cons", .len = 4}, list_18);
    match_32 = call_130;
    goto end_match_118;
next_123:;
    struct Space_ call_131 = failwith_1((struct String){.str = "NEVER: suppress warning", .len = 23});
    match_32 = call_131;
    goto end_match_118;
next_124:;
end_match_118:;
    return match_32;
}

struct Space_ patToSpace_(struct Space_Space_Tuple2 arg_62, struct Pat_ pat_) {
    struct Space_ spaceFull_ = arg_62.t0;
    struct Space_ spaceEmpty_ = arg_62.t1;
    struct Space_Space_Tuple2 tuple_59;
    tuple_59.t0 = spaceFull_;
    tuple_59.t1 = spaceEmpty_;
    struct Space_ call_132 = go_11(tuple_59, pat_);
    return call_132;
}

struct Space_ fun_22(void* env_13, struct Pat_ arg_27) {
    struct Space_Space_Tuple2 arg_28 = (*(((struct Space_Space_Tuple2Tuple1*)env_13))).t0;
    struct Space_ call_133 = patToSpace_(arg_28, arg_27);
    return call_133;
}

struct Space_ patsToSpace_(struct Space_Space_Tuple2 arg_63, struct Pat_List* pats_) {
    struct Space_ spaceFull_ = arg_63.t0;
    struct Space_ spaceEmpty_ = arg_63.t1;
    struct Space_Space_Tuple2 tuple_61;
    tuple_61.t0 = spaceFull_;
    tuple_61.t1 = spaceEmpty_;
    struct Space_Space_Tuple2Tuple1 tuple_60;
    tuple_60.t0 = tuple_61;
    void* box_13 = (void*)malloc(sizeof(struct Space_Space_Tuple2Tuple1));
    (*(((struct Space_Space_Tuple2Tuple1*)box_13))) = tuple_60;
    void* env_32 = box_13;
    struct Pat_Space_Fun1 fun_42 = (struct Pat_Space_Fun1){.fun = fun_22, .env = env_32};
    struct Space_List* call_134 = listMap_3(fun_42, pats_);
    struct Space_ call_135 = spaceUnion_(call_134);
    return call_135;
}

struct Space_ fun_6(struct Space_Tuple1 arg_64, int arg_65) {
    struct Space_ spaceFull_ = arg_64.t0;
    return spaceFull_;
}

struct Space_ fun_23(void* env_14, int arg_29) {
    struct Space_Tuple1 arg_30 = (*(((struct Space_Tuple1Tuple1*)env_14))).t0;
    struct Space_ call_136 = fun_6(arg_30, 0);
    return call_136;
}

int testSpaceIsEmpty_(struct Space_Space_Tuple2 arg_66, int arg_67) {
    struct Space_ spaceFull_ = arg_66.t0;
    struct Space_ spaceEmpty_ = arg_66.t1;
    int call_137 = spaceIsEmpty_(spaceEmpty_);
    milone_assert(call_137, 455, 2);
    int call_138 = 0;
    struct Space_List* list_22 = (struct Space_List*)malloc(sizeof(struct Space_List));
    list_22->head = spaceEmpty_;
    list_22->tail = NULL;
    struct Space_ call_139 = spaceUnion_(list_22);
    struct Space_List* list_21 = (struct Space_List*)malloc(sizeof(struct Space_List));
    list_21->head = call_139;
    list_21->tail = NULL;
    struct Space_List* list_20 = (struct Space_List*)malloc(sizeof(struct Space_List));
    list_20->head = spaceEmpty_;
    list_20->tail = list_21;
    struct Space_ call_140 = spaceUnion_(list_20);
    int call_141 = spaceIsEmpty_(call_140);
    milone_assert(call_141, 456, 2);
    int call_142 = 0;
    int call_143 = spaceIsEmpty_(spaceFull_);
    milone_assert((!(call_143)), 458, 2);
    int call_144 = 0;
    struct Space_Tuple1 tuple_63;
    tuple_63.t0 = spaceFull_;
    struct Space_Tuple1Tuple1 tuple_62;
    tuple_62.t0 = tuple_63;
    void* box_14 = (void*)malloc(sizeof(struct Space_Tuple1Tuple1));
    (*(((struct Space_Tuple1Tuple1*)box_14))) = tuple_62;
    void* env_33 = box_14;
    struct UnitSpace_Fun1 fun_43 = (struct UnitSpace_Fun1){.fun = fun_23, .env = env_33};
    struct Space_ call_145 = spaceRef_((struct String){.str = "ref", .len = 3}, fun_43);
    int call_146 = spaceIsEmpty_(call_145);
    milone_assert((!(call_146)), 459, 2);
    int call_147 = 0;
    struct Space_List* list_24 = (struct Space_List*)malloc(sizeof(struct Space_List));
    list_24->head = spaceFull_;
    list_24->tail = NULL;
    struct Space_List* list_23 = (struct Space_List*)malloc(sizeof(struct Space_List));
    list_23->head = spaceEmpty_;
    list_23->tail = list_24;
    struct Space_ call_148 = spaceUnion_(list_23);
    int call_149 = spaceIsEmpty_(call_148);
    milone_assert((!(call_149)), 460, 2);
    int call_150 = 0;
    struct Space_ call_151 = spaceCtor_((struct String){.str = "tuple", .len = 5}, NULL);
    int call_152 = spaceIsEmpty_(call_151);
    milone_assert((!(call_152)), 462, 2);
    int call_153 = 0;
    struct Space_List* list_27 = (struct Space_List*)malloc(sizeof(struct Space_List));
    list_27->head = spaceFull_;
    list_27->tail = NULL;
    struct Space_List* list_26 = (struct Space_List*)malloc(sizeof(struct Space_List));
    list_26->head = spaceEmpty_;
    list_26->tail = list_27;
    struct Space_List* list_25 = (struct Space_List*)malloc(sizeof(struct Space_List));
    list_25->head = spaceFull_;
    list_25->tail = list_26;
    struct Space_ call_154 = spaceCtor_((struct String){.str = "tuple", .len = 5}, list_25);
    int call_155 = spaceIsEmpty_(call_154);
    milone_assert(call_155, 463, 2);
    int call_156 = 0;
    struct Space_Tuple1 tuple_64;
    tuple_64.t0 = spaceFull_;
    struct Ty_* payload_3 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_3))) = (struct Ty_){.tag = Int_};
    struct Ty_ variant_3 = (struct Ty_){.tag = List_, .List_ = payload_3};
    struct Space_ call_157 = tyToSpace_(tuple_64, variant_3);
    int call_158 = spaceIsEmpty_(call_157);
    milone_assert((!(call_158)), 465, 2);
    int call_159 = 0;
    struct Space_Tuple1 tuple_65;
    tuple_65.t0 = spaceFull_;
    struct Ty_List** payload_4 = (struct Ty_List**)malloc(sizeof(struct Ty_List*));
    (*(((struct Ty_List**)payload_4))) = NULL;
    struct Ty_ variant_4 = (struct Ty_){.tag = Tuple_, .Tuple_ = payload_4};
    struct Ty_* payload_5 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_5))) = variant_4;
    struct Ty_ variant_5 = (struct Ty_){.tag = List_, .List_ = payload_5};
    struct Space_ call_160 = tyToSpace_(tuple_65, variant_5);
    int call_161 = spaceIsEmpty_(call_160);
    milone_assert((!(call_161)), 466, 2);
    int call_162 = 0;
    return 0;
}

int fun_24(void* env_15, int arg_31) {
    int call_163 = id_1(arg_31);
    return call_163;
}

int fun_7(struct StringSpace_Tuple2 arg_68) {
    struct String expected_ = arg_68.t0;
    struct Space_ space_10 = arg_68.t1;
    struct String call_164 = spaceToString_(space_10);
    struct String actual_ = call_164;
    int match_33;
    if ((str_cmp(actual_, expected_) != 0)) goto next_126;
    match_33 = 1;
    goto end_match_125;
next_126:;
    if ((str_cmp(actual_, expected_) == 0)) goto next_127;
    printf("%s: NG (%s)\n", expected_.str, actual_.str);
    int call_165 = 0;
    match_33 = 0;
    goto end_match_125;
next_127:;
    exit(1);
end_match_125:;
    return match_33;
}

int fun_25(void* env_16, struct StringSpace_Tuple2 arg_32) {
    int call_166 = fun_7(arg_32);
    return call_166;
}

int testSpaceToString_(struct Space_Space_Tuple2 arg_69, int arg_70) {
    struct Space_ spaceFull_ = arg_69.t0;
    struct Space_ spaceEmpty_ = arg_69.t1;
    struct StringSpace_Tuple2 tuple_66;
    tuple_66.t0 = (struct String){.str = "empty", .len = 5};
    tuple_66.t1 = spaceEmpty_;
    struct StringSpace_Tuple2 tuple_67;
    tuple_67.t0 = (struct String){.str = "full", .len = 4};
    tuple_67.t1 = spaceFull_;
    struct Space_ call_167 = spaceCtor_((struct String){.str = "nil", .len = 3}, NULL);
    struct StringSpace_Tuple2 tuple_68;
    tuple_68.t0 = (struct String){.str = "nil", .len = 3};
    tuple_68.t1 = call_167;
    struct Space_List* list_33 = (struct Space_List*)malloc(sizeof(struct Space_List));
    list_33->head = spaceFull_;
    list_33->tail = NULL;
    struct Space_List* list_32 = (struct Space_List*)malloc(sizeof(struct Space_List));
    list_32->head = spaceEmpty_;
    list_32->tail = list_33;
    struct Space_ call_168 = spaceCtor_((struct String){.str = "tuple", .len = 5}, list_32);
    struct StringSpace_Tuple2 tuple_69;
    tuple_69.t0 = (struct String){.str = "tuple(empty, full)", .len = 18};
    tuple_69.t1 = call_168;
    struct Space_Tuple1 tuple_71;
    tuple_71.t0 = spaceFull_;
    struct Space_ call_169 = tyToSpace_(tuple_71, (struct Ty_){.tag = Int_});
    struct StringSpace_Tuple2 tuple_70;
    tuple_70.t0 = (struct String){.str = "full", .len = 4};
    tuple_70.t1 = call_169;
    struct Space_Tuple1 tuple_73;
    tuple_73.t0 = spaceFull_;
    struct Ty_* payload_6 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_6))) = (struct Ty_){.tag = Int_};
    struct Ty_ variant_6 = (struct Ty_){.tag = List_, .List_ = payload_6};
    struct Space_ call_170 = tyToSpace_(tuple_73, variant_6);
    struct Space_ call_171 = spaceDecompose_(call_170);
    struct StringSpace_Tuple2 tuple_72;
    tuple_72.t0 = (struct String){.str = "+(nil, cons(full, list))", .len = 24};
    tuple_72.t1 = call_171;
    struct Space_Space_Tuple2 tuple_75;
    tuple_75.t0 = spaceFull_;
    tuple_75.t1 = spaceEmpty_;
    struct Pat_Pat_Tuple2 tuple_76;
    tuple_76.t0 = (struct Pat_){.tag = Discard_};
    tuple_76.t1 = (struct Pat_){.tag = Nil_};
    struct Pat_Pat_Tuple2* payload_7 = (struct Pat_Pat_Tuple2*)malloc(sizeof(struct Pat_Pat_Tuple2));
    (*(((struct Pat_Pat_Tuple2*)payload_7))) = tuple_76;
    struct Pat_ variant_7 = (struct Pat_){.tag = Cons_, .Cons_ = payload_7};
    struct Space_ call_172 = patToSpace_(tuple_75, variant_7);
    struct StringSpace_Tuple2 tuple_74;
    tuple_74.t0 = (struct String){.str = "cons(full, nil)", .len = 15};
    tuple_74.t1 = call_172;
    struct StringSpace_Tuple2List* list_36 = (struct StringSpace_Tuple2List*)malloc(sizeof(struct StringSpace_Tuple2List));
    list_36->head = tuple_74;
    list_36->tail = NULL;
    struct StringSpace_Tuple2List* list_35 = (struct StringSpace_Tuple2List*)malloc(sizeof(struct StringSpace_Tuple2List));
    list_35->head = tuple_72;
    list_35->tail = list_36;
    struct StringSpace_Tuple2List* list_34 = (struct StringSpace_Tuple2List*)malloc(sizeof(struct StringSpace_Tuple2List));
    list_34->head = tuple_70;
    list_34->tail = list_35;
    struct StringSpace_Tuple2List* list_31 = (struct StringSpace_Tuple2List*)malloc(sizeof(struct StringSpace_Tuple2List));
    list_31->head = tuple_69;
    list_31->tail = list_34;
    struct StringSpace_Tuple2List* list_30 = (struct StringSpace_Tuple2List*)malloc(sizeof(struct StringSpace_Tuple2List));
    list_30->head = tuple_68;
    list_30->tail = list_31;
    struct StringSpace_Tuple2List* list_29 = (struct StringSpace_Tuple2List*)malloc(sizeof(struct StringSpace_Tuple2List));
    list_29->head = tuple_67;
    list_29->tail = list_30;
    struct StringSpace_Tuple2List* list_28 = (struct StringSpace_Tuple2List*)malloc(sizeof(struct StringSpace_Tuple2List));
    list_28->head = tuple_66;
    list_28->tail = list_29;
    struct StringSpace_Tuple2List* cases_ = list_28;
    void* box_15 = (void*)malloc(sizeof(int));
    (*(((int*)box_15))) = 0;
    void* env_34 = box_15;
    struct BoolBoolFun1 fun_44 = (struct BoolBoolFun1){.fun = fun_24, .env = env_34};
    void* box_16 = (void*)malloc(sizeof(int));
    (*(((int*)box_16))) = 0;
    void* env_35 = box_16;
    struct StringSpace_Tuple2BoolFun1 fun_45 = (struct StringSpace_Tuple2BoolFun1){.fun = fun_25, .env = env_35};
    struct BoolList* call_173 = listMap_2(fun_45, cases_);
    int call_174 = listForAll_1(fun_44, call_173);
    int ok_ = call_174;
    milone_assert(ok_, 497, 2);
    int call_175 = 0;
    return 0;
}

int fun_26(void* env_17, int arg_33) {
    int call_176 = id_1(arg_33);
    return call_176;
}

struct BoolStringTuple2 {
    int t0;
    struct String t1;
};

struct Covering_Covering_Tuple2 {
    struct Covering_ t0;
    struct Covering_ t1;
};

int fun_8(struct Space_Space_Tuple2 arg_71, struct StringTy_Pat_ListCovering_Tuple4 arg_72) {
    struct Space_ spaceFull_ = arg_71.t0;
    struct Space_ spaceEmpty_ = arg_71.t1;
    struct String name_ = arg_72.t0;
    struct Ty_ ty_2 = arg_72.t1;
    struct Pat_List* pats_1 = arg_72.t2;
    struct Covering_ covering_ = arg_72.t3;
    struct Space_Tuple1 tuple_77;
    tuple_77.t0 = spaceFull_;
    struct Space_ call_177 = tyToSpace_(tuple_77, ty_2);
    struct Space_ tySpace_ = call_177;
    struct Space_Space_Tuple2 tuple_78;
    tuple_78.t0 = spaceFull_;
    tuple_78.t1 = spaceEmpty_;
    struct Space_ call_178 = patsToSpace_(tuple_78, pats_1);
    struct Space_ patSpace_ = call_178;
    struct Covering_ match_34;
    struct Space_Space_Tuple2 tuple_79;
    tuple_79.t0 = spaceFull_;
    tuple_79.t1 = spaceEmpty_;
    int call_179 = spaceCovers_(tuple_79, tySpace_, patSpace_);
    if ((!(call_179))) goto next_129;
    match_34 = (struct Covering_){.tag = Covering_};
    goto end_match_128;
next_129:;
    if (call_179) goto next_130;
    match_34 = (struct Covering_){.tag = Open_};
    goto end_match_128;
next_130:;
    exit(1);
end_match_128:;
    struct Covering_ actual_1 = match_34;
    struct BoolStringTuple2 match_35;
    struct Covering_Covering_Tuple2 tuple_80;
    tuple_80.t0 = covering_;
    tuple_80.t1 = actual_1;
    if ((tuple_80.t0.tag != Covering_)) goto next_133;
    if ((tuple_80.t1.tag != Covering_)) goto next_133;
    goto match_body_132;
next_133:;
    if ((tuple_80.t0.tag != Open_)) goto next_134;
    if ((tuple_80.t1.tag != Open_)) goto next_134;
    goto match_body_132;
match_body_132:;
    struct BoolStringTuple2 tuple_81;
    tuple_81.t0 = 1;
    tuple_81.t1 = (struct String){.str = "OK", .len = 2};
    match_35 = tuple_81;
    goto end_match_131;
next_134:;
    if ((tuple_80.t0.tag != Covering_)) goto next_135;
    if ((tuple_80.t1.tag != Open_)) goto next_135;
    struct BoolStringTuple2 tuple_82;
    tuple_82.t0 = 0;
    tuple_82.t1 = (struct String){.str = "NG. Expected covering but open", .len = 30};
    match_35 = tuple_82;
    goto end_match_131;
next_135:;
    struct BoolStringTuple2 tuple_83;
    tuple_83.t0 = 0;
    tuple_83.t1 = (struct String){.str = "NG. Expected open but covering", .len = 30};
    match_35 = tuple_83;
    goto end_match_131;
next_136:;
end_match_131:;
    int ok_2 = match_35.t0;
    struct String msg_1 = match_35.t1;
    printf("%s: %s\n", name_.str, msg_1.str);
    int call_180 = 0;
    int match_36;
    if (ok_2) goto next_138;
    struct String call_181 = spaceToString_(tySpace_);
    printf("  ty: %s\n", call_181.str);
    int call_182 = 0;
    struct String call_183 = spaceToString_(patSpace_);
    printf("  pats: %s\n", call_183.str);
    int call_184 = 0;
    match_36 = 0;
    goto end_match_137;
next_138:;
    if ((!(ok_2))) goto next_139;
    match_36 = 0;
    goto end_match_137;
next_139:;
    exit(1);
end_match_137:;
    return ok_2;
}

int fun_27(void* env_18, struct StringTy_Pat_ListCovering_Tuple4 arg_34) {
    struct Space_Space_Tuple2 arg_35 = (*(((struct Space_Space_Tuple2Tuple1*)env_18))).t0;
    int call_185 = fun_8(arg_35, arg_34);
    return call_185;
}

int main() {
    struct Space_ spaceFull_ = (struct Space_){.tag = Full_};
    struct Space_List** payload_8 = (struct Space_List**)malloc(sizeof(struct Space_List*));
    (*(((struct Space_List**)payload_8))) = NULL;
    struct Space_ variant_8 = (struct Space_){.tag = Union_, .Union_ = payload_8};
    struct Space_ spaceEmpty_ = variant_8;
    struct Space_Space_Tuple2 tuple_84;
    tuple_84.t0 = spaceFull_;
    tuple_84.t1 = spaceEmpty_;
    int call_186 = testSpaceIsEmpty_(tuple_84, 0);
    struct Space_Space_Tuple2 tuple_85;
    tuple_85.t0 = spaceFull_;
    tuple_85.t1 = spaceEmpty_;
    int call_187 = testSpaceToString_(tuple_85, 0);
    struct Pat_Pat_Tuple2 tuple_86;
    tuple_86.t0 = (struct Pat_){.tag = Discard_};
    tuple_86.t1 = (struct Pat_){.tag = Discard_};
    struct Pat_Pat_Tuple2* payload_9 = (struct Pat_Pat_Tuple2*)malloc(sizeof(struct Pat_Pat_Tuple2));
    (*(((struct Pat_Pat_Tuple2*)payload_9))) = tuple_86;
    struct Pat_ variant_9 = (struct Pat_){.tag = Cons_, .Cons_ = payload_9};
    struct Pat_ anyConsPat_ = variant_9;
    struct Ty_List** payload_10 = (struct Ty_List**)malloc(sizeof(struct Ty_List*));
    (*(((struct Ty_List**)payload_10))) = NULL;
    struct Ty_ variant_10 = (struct Ty_){.tag = Tuple_, .Tuple_ = payload_10};
    struct Pat_List** payload_11 = (struct Pat_List**)malloc(sizeof(struct Pat_List*));
    (*(((struct Pat_List**)payload_11))) = NULL;
    struct Pat_ variant_11 = (struct Pat_){.tag = TupleLit_, .TupleLit_ = payload_11};
    struct Pat_List* list_38 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_38->head = variant_11;
    list_38->tail = NULL;
    struct StringTy_Pat_ListCovering_Tuple4 tuple_87;
    tuple_87.t0 = (struct String){.str = "unit with ()", .len = 12};
    tuple_87.t1 = variant_10;
    tuple_87.t2 = list_38;
    tuple_87.t3 = (struct Covering_){.tag = Covering_};
    int* payload_12 = (int*)malloc(sizeof(int));
    (*(((int*)payload_12))) = 1;
    struct Pat_ variant_12 = (struct Pat_){.tag = IntLit_, .IntLit_ = payload_12};
    struct Pat_List* list_40 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_40->head = variant_12;
    list_40->tail = NULL;
    struct StringTy_Pat_ListCovering_Tuple4 tuple_88;
    tuple_88.t0 = (struct String){.str = "int with literal pats", .len = 21};
    tuple_88.t1 = (struct Ty_){.tag = Int_};
    tuple_88.t2 = list_40;
    tuple_88.t3 = (struct Covering_){.tag = Open_};
    struct Pat_List* list_42 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_42->head = (struct Pat_){.tag = Discard_};
    list_42->tail = NULL;
    struct StringTy_Pat_ListCovering_Tuple4 tuple_89;
    tuple_89.t0 = (struct String){.str = "int with _", .len = 10};
    tuple_89.t1 = (struct Ty_){.tag = Int_};
    tuple_89.t2 = list_42;
    tuple_89.t3 = (struct Covering_){.tag = Covering_};
    int* payload_13 = (int*)malloc(sizeof(int));
    (*(((int*)payload_13))) = 1;
    struct Pat_ variant_13 = (struct Pat_){.tag = IntLit_, .IntLit_ = payload_13};
    struct Pat_List* list_45 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_45->head = (struct Pat_){.tag = Discard_};
    list_45->tail = NULL;
    struct Pat_List* list_44 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_44->head = variant_13;
    list_44->tail = list_45;
    struct StringTy_Pat_ListCovering_Tuple4 tuple_90;
    tuple_90.t0 = (struct String){.str = "int with 1|_", .len = 12};
    tuple_90.t1 = (struct Ty_){.tag = Int_};
    tuple_90.t2 = list_44;
    tuple_90.t3 = (struct Covering_){.tag = Covering_};
    struct Ty_List** payload_14 = (struct Ty_List**)malloc(sizeof(struct Ty_List*));
    (*(((struct Ty_List**)payload_14))) = NULL;
    struct Ty_ variant_14 = (struct Ty_){.tag = Tuple_, .Tuple_ = payload_14};
    struct Ty_List* list_48 = (struct Ty_List*)malloc(sizeof(struct Ty_List));
    list_48->head = variant_14;
    list_48->tail = NULL;
    struct Ty_List* list_47 = (struct Ty_List*)malloc(sizeof(struct Ty_List));
    list_47->head = (struct Ty_){.tag = Int_};
    list_47->tail = list_48;
    struct Ty_List** payload_15 = (struct Ty_List**)malloc(sizeof(struct Ty_List*));
    (*(((struct Ty_List**)payload_15))) = list_47;
    struct Ty_ variant_15 = (struct Ty_){.tag = Tuple_, .Tuple_ = payload_15};
    struct Pat_List** payload_16 = (struct Pat_List**)malloc(sizeof(struct Pat_List*));
    (*(((struct Pat_List**)payload_16))) = NULL;
    struct Pat_ variant_16 = (struct Pat_){.tag = TupleLit_, .TupleLit_ = payload_16};
    struct Pat_List* list_51 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_51->head = variant_16;
    list_51->tail = NULL;
    struct Pat_List* list_50 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_50->head = (struct Pat_){.tag = Discard_};
    list_50->tail = list_51;
    struct Pat_List** payload_17 = (struct Pat_List**)malloc(sizeof(struct Pat_List*));
    (*(((struct Pat_List**)payload_17))) = list_50;
    struct Pat_ variant_17 = (struct Pat_){.tag = TupleLit_, .TupleLit_ = payload_17};
    struct Pat_List* list_49 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_49->head = variant_17;
    list_49->tail = NULL;
    struct StringTy_Pat_ListCovering_Tuple4 tuple_91;
    tuple_91.t0 = (struct String){.str = "int * unit with _, ()", .len = 21};
    tuple_91.t1 = variant_15;
    tuple_91.t2 = list_49;
    tuple_91.t3 = (struct Covering_){.tag = Covering_};
    struct Ty_List* list_54 = (struct Ty_List*)malloc(sizeof(struct Ty_List));
    list_54->head = (struct Ty_){.tag = Int_};
    list_54->tail = NULL;
    struct Ty_List* list_53 = (struct Ty_List*)malloc(sizeof(struct Ty_List));
    list_53->head = (struct Ty_){.tag = Int_};
    list_53->tail = list_54;
    struct Ty_List** payload_18 = (struct Ty_List**)malloc(sizeof(struct Ty_List*));
    (*(((struct Ty_List**)payload_18))) = list_53;
    struct Ty_ variant_18 = (struct Ty_){.tag = Tuple_, .Tuple_ = payload_18};
    int* payload_19 = (int*)malloc(sizeof(int));
    (*(((int*)payload_19))) = 1;
    struct Pat_ variant_19 = (struct Pat_){.tag = IntLit_, .IntLit_ = payload_19};
    struct Pat_List* list_57 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_57->head = (struct Pat_){.tag = Discard_};
    list_57->tail = NULL;
    struct Pat_List* list_56 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_56->head = variant_19;
    list_56->tail = list_57;
    struct Pat_List** payload_20 = (struct Pat_List**)malloc(sizeof(struct Pat_List*));
    (*(((struct Pat_List**)payload_20))) = list_56;
    struct Pat_ variant_20 = (struct Pat_){.tag = TupleLit_, .TupleLit_ = payload_20};
    int* payload_21 = (int*)malloc(sizeof(int));
    (*(((int*)payload_21))) = 1;
    struct Pat_ variant_21 = (struct Pat_){.tag = IntLit_, .IntLit_ = payload_21};
    struct Pat_List* list_60 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_60->head = variant_21;
    list_60->tail = NULL;
    struct Pat_List* list_59 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_59->head = (struct Pat_){.tag = Discard_};
    list_59->tail = list_60;
    struct Pat_List** payload_22 = (struct Pat_List**)malloc(sizeof(struct Pat_List*));
    (*(((struct Pat_List**)payload_22))) = list_59;
    struct Pat_ variant_22 = (struct Pat_){.tag = TupleLit_, .TupleLit_ = payload_22};
    struct Pat_List* list_58 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_58->head = variant_22;
    list_58->tail = NULL;
    struct Pat_List* list_55 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_55->head = variant_20;
    list_55->tail = list_58;
    struct StringTy_Pat_ListCovering_Tuple4 tuple_92;
    tuple_92.t0 = (struct String){.str = "int * int with 1, _ | _, 1", .len = 26};
    tuple_92.t1 = variant_18;
    tuple_92.t2 = list_55;
    tuple_92.t3 = (struct Covering_){.tag = Open_};
    struct Ty_* payload_23 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_23))) = (struct Ty_){.tag = Int_};
    struct Ty_ variant_23 = (struct Ty_){.tag = List_, .List_ = payload_23};
    struct Pat_List* list_62 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_62->head = (struct Pat_){.tag = Nil_};
    list_62->tail = NULL;
    struct StringTy_Pat_ListCovering_Tuple4 tuple_93;
    tuple_93.t0 = (struct String){.str = "int list with []", .len = 16};
    tuple_93.t1 = variant_23;
    tuple_93.t2 = list_62;
    tuple_93.t3 = (struct Covering_){.tag = Open_};
    struct Ty_* payload_24 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_24))) = (struct Ty_){.tag = Int_};
    struct Ty_ variant_24 = (struct Ty_){.tag = List_, .List_ = payload_24};
    struct Pat_List* list_64 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_64->head = anyConsPat_;
    list_64->tail = NULL;
    struct StringTy_Pat_ListCovering_Tuple4 tuple_94;
    tuple_94.t0 = (struct String){.str = "int list with _::_", .len = 18};
    tuple_94.t1 = variant_24;
    tuple_94.t2 = list_64;
    tuple_94.t3 = (struct Covering_){.tag = Open_};
    struct Ty_* payload_25 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_25))) = (struct Ty_){.tag = Int_};
    struct Ty_ variant_25 = (struct Ty_){.tag = List_, .List_ = payload_25};
    struct Pat_List* list_67 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_67->head = anyConsPat_;
    list_67->tail = NULL;
    struct Pat_List* list_66 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_66->head = (struct Pat_){.tag = Nil_};
    list_66->tail = list_67;
    struct StringTy_Pat_ListCovering_Tuple4 tuple_95;
    tuple_95.t0 = (struct String){.str = "int list with [] | _::_", .len = 23};
    tuple_95.t1 = variant_25;
    tuple_95.t2 = list_66;
    tuple_95.t3 = (struct Covering_){.tag = Covering_};
    struct Ty_* payload_26 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_26))) = (struct Ty_){.tag = Int_};
    struct Ty_ variant_26 = (struct Ty_){.tag = List_, .List_ = payload_26};
    struct Pat_Pat_Tuple2 tuple_97;
    tuple_97.t0 = (struct Pat_){.tag = Discard_};
    tuple_97.t1 = (struct Pat_){.tag = Nil_};
    struct Pat_Pat_Tuple2* payload_27 = (struct Pat_Pat_Tuple2*)malloc(sizeof(struct Pat_Pat_Tuple2));
    (*(((struct Pat_Pat_Tuple2*)payload_27))) = tuple_97;
    struct Pat_ variant_27 = (struct Pat_){.tag = Cons_, .Cons_ = payload_27};
    struct Pat_Pat_Tuple2 tuple_98;
    tuple_98.t0 = (struct Pat_){.tag = Discard_};
    tuple_98.t1 = anyConsPat_;
    struct Pat_Pat_Tuple2* payload_28 = (struct Pat_Pat_Tuple2*)malloc(sizeof(struct Pat_Pat_Tuple2));
    (*(((struct Pat_Pat_Tuple2*)payload_28))) = tuple_98;
    struct Pat_ variant_28 = (struct Pat_){.tag = Cons_, .Cons_ = payload_28};
    struct Pat_List* list_71 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_71->head = variant_28;
    list_71->tail = NULL;
    struct Pat_List* list_70 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_70->head = variant_27;
    list_70->tail = list_71;
    struct Pat_List* list_69 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_69->head = (struct Pat_){.tag = Nil_};
    list_69->tail = list_70;
    struct StringTy_Pat_ListCovering_Tuple4 tuple_96;
    tuple_96.t0 = (struct String){.str = "int list with [] | [_] | _::_::_", .len = 32};
    tuple_96.t1 = variant_26;
    tuple_96.t2 = list_69;
    tuple_96.t3 = (struct Covering_){.tag = Covering_};
    struct Ty_* payload_29 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_29))) = (struct Ty_){.tag = Int_};
    struct Ty_ variant_29 = (struct Ty_){.tag = List_, .List_ = payload_29};
    struct Ty_* payload_30 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_30))) = variant_29;
    struct Ty_ variant_30 = (struct Ty_){.tag = List_, .List_ = payload_30};
    struct Pat_Pat_Tuple2 tuple_100;
    tuple_100.t0 = (struct Pat_){.tag = Nil_};
    tuple_100.t1 = (struct Pat_){.tag = Nil_};
    struct Pat_Pat_Tuple2* payload_31 = (struct Pat_Pat_Tuple2*)malloc(sizeof(struct Pat_Pat_Tuple2));
    (*(((struct Pat_Pat_Tuple2*)payload_31))) = tuple_100;
    struct Pat_ variant_31 = (struct Pat_){.tag = Cons_, .Cons_ = payload_31};
    struct Pat_Pat_Tuple2 tuple_101;
    tuple_101.t0 = anyConsPat_;
    tuple_101.t1 = (struct Pat_){.tag = Discard_};
    struct Pat_Pat_Tuple2* payload_32 = (struct Pat_Pat_Tuple2*)malloc(sizeof(struct Pat_Pat_Tuple2));
    (*(((struct Pat_Pat_Tuple2*)payload_32))) = tuple_101;
    struct Pat_ variant_32 = (struct Pat_){.tag = Cons_, .Cons_ = payload_32};
    struct Pat_Pat_Tuple2 tuple_102;
    tuple_102.t0 = (struct Pat_){.tag = Discard_};
    tuple_102.t1 = anyConsPat_;
    struct Pat_Pat_Tuple2* payload_33 = (struct Pat_Pat_Tuple2*)malloc(sizeof(struct Pat_Pat_Tuple2));
    (*(((struct Pat_Pat_Tuple2*)payload_33))) = tuple_102;
    struct Pat_ variant_33 = (struct Pat_){.tag = Cons_, .Cons_ = payload_33};
    struct Pat_List* list_76 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_76->head = variant_33;
    list_76->tail = NULL;
    struct Pat_List* list_75 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_75->head = variant_32;
    list_75->tail = list_76;
    struct Pat_List* list_74 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_74->head = variant_31;
    list_74->tail = list_75;
    struct Pat_List* list_73 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_73->head = (struct Pat_){.tag = Nil_};
    list_73->tail = list_74;
    struct StringTy_Pat_ListCovering_Tuple4 tuple_99;
    tuple_99.t0 = (struct String){.str = "int list list with [] | [[]] | [_::_] | _::_::_", .len = 47};
    tuple_99.t1 = variant_30;
    tuple_99.t2 = list_73;
    tuple_99.t3 = (struct Covering_){.tag = Covering_};
    struct Ty_* payload_34 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_34))) = (struct Ty_){.tag = Int_};
    struct Ty_ variant_34 = (struct Ty_){.tag = List_, .List_ = payload_34};
    struct Ty_* payload_35 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_35))) = (struct Ty_){.tag = Int_};
    struct Ty_ variant_35 = (struct Ty_){.tag = List_, .List_ = payload_35};
    struct Ty_List* list_79 = (struct Ty_List*)malloc(sizeof(struct Ty_List));
    list_79->head = variant_35;
    list_79->tail = NULL;
    struct Ty_List* list_78 = (struct Ty_List*)malloc(sizeof(struct Ty_List));
    list_78->head = variant_34;
    list_78->tail = list_79;
    struct Ty_List** payload_36 = (struct Ty_List**)malloc(sizeof(struct Ty_List*));
    (*(((struct Ty_List**)payload_36))) = list_78;
    struct Ty_ variant_36 = (struct Ty_){.tag = Tuple_, .Tuple_ = payload_36};
    struct Pat_List* list_82 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_82->head = (struct Pat_){.tag = Nil_};
    list_82->tail = NULL;
    struct Pat_List* list_81 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_81->head = (struct Pat_){.tag = Nil_};
    list_81->tail = list_82;
    struct Pat_List** payload_37 = (struct Pat_List**)malloc(sizeof(struct Pat_List*));
    (*(((struct Pat_List**)payload_37))) = list_81;
    struct Pat_ variant_37 = (struct Pat_){.tag = TupleLit_, .TupleLit_ = payload_37};
    struct Pat_List* list_85 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_85->head = (struct Pat_){.tag = Nil_};
    list_85->tail = NULL;
    struct Pat_List* list_84 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_84->head = anyConsPat_;
    list_84->tail = list_85;
    struct Pat_List** payload_38 = (struct Pat_List**)malloc(sizeof(struct Pat_List*));
    (*(((struct Pat_List**)payload_38))) = list_84;
    struct Pat_ variant_38 = (struct Pat_){.tag = TupleLit_, .TupleLit_ = payload_38};
    struct Pat_List* list_88 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_88->head = anyConsPat_;
    list_88->tail = NULL;
    struct Pat_List* list_87 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_87->head = (struct Pat_){.tag = Nil_};
    list_87->tail = list_88;
    struct Pat_List** payload_39 = (struct Pat_List**)malloc(sizeof(struct Pat_List*));
    (*(((struct Pat_List**)payload_39))) = list_87;
    struct Pat_ variant_39 = (struct Pat_){.tag = TupleLit_, .TupleLit_ = payload_39};
    struct Pat_List* list_91 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_91->head = anyConsPat_;
    list_91->tail = NULL;
    struct Pat_List* list_90 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_90->head = anyConsPat_;
    list_90->tail = list_91;
    struct Pat_List** payload_40 = (struct Pat_List**)malloc(sizeof(struct Pat_List*));
    (*(((struct Pat_List**)payload_40))) = list_90;
    struct Pat_ variant_40 = (struct Pat_){.tag = TupleLit_, .TupleLit_ = payload_40};
    struct Pat_List* list_89 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_89->head = variant_40;
    list_89->tail = NULL;
    struct Pat_List* list_86 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_86->head = variant_39;
    list_86->tail = list_89;
    struct Pat_List* list_83 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_83->head = variant_38;
    list_83->tail = list_86;
    struct Pat_List* list_80 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_80->head = variant_37;
    list_80->tail = list_83;
    struct StringTy_Pat_ListCovering_Tuple4 tuple_103;
    tuple_103.t0 = (struct String){.str = "int list * int list with [], [] | [], _::_ | _::_, [] | _::_, _::_", .len = 66};
    tuple_103.t1 = variant_36;
    tuple_103.t2 = list_80;
    tuple_103.t3 = (struct Covering_){.tag = Covering_};
    struct StringTy_Pat_ListCovering_Tuple4List* list_77 = (struct StringTy_Pat_ListCovering_Tuple4List*)malloc(sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    list_77->head = tuple_103;
    list_77->tail = NULL;
    struct StringTy_Pat_ListCovering_Tuple4List* list_72 = (struct StringTy_Pat_ListCovering_Tuple4List*)malloc(sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    list_72->head = tuple_99;
    list_72->tail = list_77;
    struct StringTy_Pat_ListCovering_Tuple4List* list_68 = (struct StringTy_Pat_ListCovering_Tuple4List*)malloc(sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    list_68->head = tuple_96;
    list_68->tail = list_72;
    struct StringTy_Pat_ListCovering_Tuple4List* list_65 = (struct StringTy_Pat_ListCovering_Tuple4List*)malloc(sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    list_65->head = tuple_95;
    list_65->tail = list_68;
    struct StringTy_Pat_ListCovering_Tuple4List* list_63 = (struct StringTy_Pat_ListCovering_Tuple4List*)malloc(sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    list_63->head = tuple_94;
    list_63->tail = list_65;
    struct StringTy_Pat_ListCovering_Tuple4List* list_61 = (struct StringTy_Pat_ListCovering_Tuple4List*)malloc(sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    list_61->head = tuple_93;
    list_61->tail = list_63;
    struct StringTy_Pat_ListCovering_Tuple4List* list_52 = (struct StringTy_Pat_ListCovering_Tuple4List*)malloc(sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    list_52->head = tuple_92;
    list_52->tail = list_61;
    struct StringTy_Pat_ListCovering_Tuple4List* list_46 = (struct StringTy_Pat_ListCovering_Tuple4List*)malloc(sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    list_46->head = tuple_91;
    list_46->tail = list_52;
    struct StringTy_Pat_ListCovering_Tuple4List* list_43 = (struct StringTy_Pat_ListCovering_Tuple4List*)malloc(sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    list_43->head = tuple_90;
    list_43->tail = list_46;
    struct StringTy_Pat_ListCovering_Tuple4List* list_41 = (struct StringTy_Pat_ListCovering_Tuple4List*)malloc(sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    list_41->head = tuple_89;
    list_41->tail = list_43;
    struct StringTy_Pat_ListCovering_Tuple4List* list_39 = (struct StringTy_Pat_ListCovering_Tuple4List*)malloc(sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    list_39->head = tuple_88;
    list_39->tail = list_41;
    struct StringTy_Pat_ListCovering_Tuple4List* list_37 = (struct StringTy_Pat_ListCovering_Tuple4List*)malloc(sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    list_37->head = tuple_87;
    list_37->tail = list_39;
    struct StringTy_Pat_ListCovering_Tuple4List* testCases_ = list_37;
    void* box_17 = (void*)malloc(sizeof(int));
    (*(((int*)box_17))) = 0;
    void* env_36 = box_17;
    struct BoolBoolFun1 fun_46 = (struct BoolBoolFun1){.fun = fun_26, .env = env_36};
    struct Space_Space_Tuple2 tuple_105;
    tuple_105.t0 = spaceFull_;
    tuple_105.t1 = spaceEmpty_;
    struct Space_Space_Tuple2Tuple1 tuple_104;
    tuple_104.t0 = tuple_105;
    void* box_18 = (void*)malloc(sizeof(struct Space_Space_Tuple2Tuple1));
    (*(((struct Space_Space_Tuple2Tuple1*)box_18))) = tuple_104;
    void* env_37 = box_18;
    struct StringTy_Pat_ListCovering_Tuple4BoolFun1 fun_47 = (struct StringTy_Pat_ListCovering_Tuple4BoolFun1){.fun = fun_27, .env = env_37};
    struct BoolList* call_188 = listMap_1(fun_47, testCases_);
    int call_189 = listForAll_1(fun_46, call_188);
    int ok_1 = call_189;
    int match_37;
    if ((!(ok_1))) goto next_141;
    match_37 = 0;
    goto end_match_140;
next_141:;
    if (ok_1) goto next_142;
    match_37 = 1;
    goto end_match_140;
next_142:;
    exit(1);
end_match_140:;
    int exitCode_ = match_37;
    return exitCode_;
}
