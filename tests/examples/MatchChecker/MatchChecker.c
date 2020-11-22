#include "milone.h"

int id_1(int x_);

enum Space_Tag;

struct Space_;

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

struct Space_List* go_25(struct Space_Space_Fun1 f_, struct Space_List* acc_1, struct Space_List* xs_5);

struct Ty_Space_Fun1;

enum Ty_Tag;

struct Ty_;

struct Ty_List;

struct Space_List* go_24(struct Ty_Space_Fun1 f_, struct Space_List* acc_1, struct Ty_List* xs_5);

struct Pat_Space_Fun1;

enum Pat_Tag;

struct Pat_;

struct Pat_List;

struct Space_List* go_23(struct Pat_Space_Fun1 f_, struct Space_List* acc_1, struct Pat_List* xs_5);

struct StringSpace_Tuple2BoolFun1;

struct StringSpace_Tuple2;

struct StringSpace_Tuple2List;

struct BoolList* go_22(struct StringSpace_Tuple2BoolFun1 f_, struct BoolList* acc_1, struct StringSpace_Tuple2List* xs_5);

struct StringTy_Pat_ListCovering_Tuple4BoolFun1;

enum Covering_Tag;

struct Covering_;

struct StringTy_Pat_ListCovering_Tuple4;

struct StringTy_Pat_ListCovering_Tuple4List;

struct BoolList* go_21(struct StringTy_Pat_ListCovering_Tuple4BoolFun1 f_, struct BoolList* acc_1, struct StringTy_Pat_ListCovering_Tuple4List* xs_5);

struct Space_List* listMap_5(struct Space_Space_Fun1 f_, struct Space_List* xs_4);

struct Space_List* listMap_4(struct Ty_Space_Fun1 f_, struct Ty_List* xs_4);

struct Space_List* listMap_3(struct Pat_Space_Fun1 f_, struct Pat_List* xs_4);

struct BoolList* listMap_2(struct StringSpace_Tuple2BoolFun1 f_, struct StringSpace_Tuple2List* xs_4);

struct BoolList* listMap_1(struct StringTy_Pat_ListCovering_Tuple4BoolFun1 f_, struct StringTy_Pat_ListCovering_Tuple4List* xs_4);

struct IntSpace_Space_Tuple2Space_Fun2;

struct Space_List* go_20(struct IntSpace_Space_Tuple2Space_Fun2 f_1, struct Space_List* acc_2, int i_, struct Space_Space_Tuple2List* xs_8);

struct IntSpace_Space_Fun2;

struct Space_List* go_19(struct IntSpace_Space_Fun2 f_1, struct Space_List* acc_2, int i_, struct Space_List* xs_8);

struct Space_List* listMapWithIndex_2(struct IntSpace_Space_Tuple2Space_Fun2 f_1, struct Space_Space_Tuple2List* xs_7);

struct Space_List* listMapWithIndex_1(struct IntSpace_Space_Fun2 f_1, struct Space_List* xs_7);

struct Space_BoolFun1;

int go_18(struct Space_BoolFun1 p_, struct Space_List* xs_11);

struct Space_Space_Tuple2BoolFun1;

int go_17(struct Space_Space_Tuple2BoolFun1 p_, struct Space_Space_Tuple2List* xs_11);

struct BoolBoolFun1;

int go_16(struct BoolBoolFun1 p_, struct BoolList* xs_11);

int listForAll_3(struct Space_BoolFun1 p_, struct Space_List* xs_10);

int listForAll_2(struct Space_Space_Tuple2BoolFun1 p_, struct Space_Space_Tuple2List* xs_10);

int listForAll_1(struct BoolBoolFun1 p_, struct BoolList* xs_10);

int go_15(struct Space_BoolFun1 p_1, struct Space_List* xs_14);

int listExists_1(struct Space_BoolFun1 p_1, struct Space_List* xs_13);

struct Space_Space_Space_Fun2;

struct Space_ go_14(struct Space_Space_Space_Fun2 folder_, struct Space_ state_1, struct Space_List* xs_17);

struct StringListSpace_StringListFun2;

struct StringList* go_13(struct StringListSpace_StringListFun2 folder_, struct StringList* state_1, struct Space_List* xs_17);

struct Space_ listFold_2(struct Space_Space_Space_Fun2 folder_, struct Space_ state_, struct Space_List* xs_16);

struct StringList* listFold_1(struct StringListSpace_StringListFun2 folder_, struct StringList* state_, struct Space_List* xs_16);

struct Space_ListSpace_ListTuple2;

struct Space_Space_Tuple2List* go_12(struct Space_Space_Tuple2List* acc_3, struct Space_List* xs_20, struct Space_List* ys_1);

struct Space_Space_Tuple2List* listZip_1(struct Space_List* xs_19, struct Space_List* ys_);

struct String go_7(struct StringList* xs_23);

struct String strConcat_(struct StringList* xs_22);

struct StringSpace_ListTuple2;

struct Space_ spaceCtor_(struct String tag_, struct Space_List* items_);

struct UnitSpace_Fun1;

struct StringUnitSpace_Fun1Tuple2;

struct Space_ spaceRef_(struct String tag_1, struct UnitSpace_Fun1 thunk_);

struct Space_List* go_8(struct Space_List* spaces_1, struct Space_List* acc_4);

struct Space_ spaceUnion_(struct Space_List* spaces_);

int fun_9(void* env_, struct Space_ arg_);

int fun_10(void* env_1, struct Space_ arg_1);

int spaceIsEmpty_(struct Space_ space_3);

struct Space_ spaceDecompose_(struct Space_ space_4);

int fun_(struct Space_Space_Tuple2 arg_85);

int fun_11(void* env_2, struct Space_Space_Tuple2 arg_2);

struct Space_ fun_2(int i_1, int j_, struct Space_Space_Tuple2 arg_86);

struct IntTuple1;

struct Space_ fun_12(void* env_3, int arg_3, struct Space_Space_Tuple2 arg_4);

struct Space_ fun_1(struct String tag_2, struct Space_List* firsts_, struct Space_List* seconds_, int i_1, struct Space_ arg_87);

struct StringSpace_ListSpace_ListTuple3;

struct Space_ fun_13(void* env_4, int arg_6, struct Space_ arg_7);

struct Space_ fun_14(void* env_5, struct Space_ arg_11, struct Space_ arg_12);

struct Space_ fun_3(struct Space_ second_, struct Space_ first_3);

struct Space_Tuple1;

struct Space_ fun_15(void* env_6, struct Space_ arg_13);

struct Space_ spaceExclude_(struct Space_ first_, struct Space_ second_);

int spaceCovers_(struct Space_ other_, struct Space_ cover_);

struct StringList* fun_4(struct StringList* acc_7, struct Space_ space_8);

struct StringList* fun_16(void* env_7, struct StringList* arg_15, struct Space_ arg_16);

struct StringList* fun_5(struct StringList* acc_9, struct Space_ space_9);

struct StringList* fun_17(void* env_8, struct StringList* arg_17, struct Space_ arg_18);

struct StringList* go_9(struct Space_ space_7, struct StringList* acc_5);

struct String spaceToString_(struct Space_ space_6);

struct Space_ fun_18(void* env_9, struct Ty_ arg_19);

struct Space_ fun_19(void* env_10, int arg_20);

struct Space_ thunk_2(struct Space_ itemSpace_, int arg_92);

struct Space_ fun_20(void* env_11, int arg_22);

struct Space_ go_10(struct Ty_ ty_1);

struct Space_ tyToSpace_(struct Ty_ ty_);

struct Space_ fun_21(void* env_12, struct Pat_ arg_24);

struct Pat_Pat_Tuple2;

struct Space_ go_11(struct Pat_ pat_1);

struct Space_ patToSpace_(struct Pat_ pat_);

struct Space_ fun_22(void* env_13, struct Pat_ arg_25);

struct Space_ patsToSpace_(struct Pat_List* pats_);

struct Space_ fun_6(int arg_93);

struct Space_ fun_23(void* env_14, int arg_26);

int testSpaceIsEmpty_(int arg_94);

int fun_24(void* env_15, int arg_27);

int fun_7(struct StringSpace_Tuple2 arg_95);

int fun_25(void* env_16, struct StringSpace_Tuple2 arg_28);

int testSpaceToString_(int arg_96);

int fun_26(void* env_17, int arg_29);

struct BoolStringTuple2;

struct Covering_Covering_Tuple2;

int fun_8(struct StringTy_Pat_ListCovering_Tuple4 arg_97);

int fun_27(void* env_18, struct StringTy_Pat_ListCovering_Tuple4 arg_30);

static struct Space_ spaceFull_;

static struct Space_ spaceEmpty_;

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
        void* Ctor_;
        void* Ref_;
        void* Union_;
    };
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
    struct StringList* list_ = (struct StringList*)milone_mem_alloc(1, sizeof(struct StringList));
    list_->head = head_;
    list_->tail = tail_;
    return list_;
}

struct Space_List* go_27(struct Space_List* acc_, struct Space_List* xs_2) {
tailrec_1:;
    struct Space_List* match_;
    if ((!((!(xs_2))))) goto next_3;
    match_ = acc_;
    goto end_match_2;
next_3:;
    if ((!(xs_2))) goto next_4;
    struct Space_ x_2 = xs_2->head;
    struct Space_List* xs_3 = xs_2->tail;
    struct Space_List* list_1 = (struct Space_List*)milone_mem_alloc(1, sizeof(struct Space_List));
    list_1->head = x_2;
    list_1->tail = acc_;
    struct Space_List* arg_31 = list_1;
    struct Space_List* arg_32 = xs_3;
    acc_ = arg_31;
    xs_2 = arg_32;
    goto tailrec_1;
    match_ = NULL;
    goto end_match_2;
next_4:;
    exit(1);
end_match_2:;
    return match_;
}

struct StringList* go_26(struct StringList* acc_, struct StringList* xs_2) {
tailrec_5:;
    struct StringList* match_1;
    if ((!((!(xs_2))))) goto next_7;
    match_1 = acc_;
    goto end_match_6;
next_7:;
    if ((!(xs_2))) goto next_8;
    struct String x_2 = xs_2->head;
    struct StringList* xs_3 = xs_2->tail;
    struct StringList* list_2 = (struct StringList*)milone_mem_alloc(1, sizeof(struct StringList));
    list_2->head = x_2;
    list_2->tail = acc_;
    struct StringList* arg_33 = list_2;
    struct StringList* arg_34 = xs_3;
    acc_ = arg_33;
    xs_2 = arg_34;
    goto tailrec_5;
    match_1 = NULL;
    goto end_match_6;
next_8:;
    exit(1);
end_match_6:;
    return match_1;
}

struct BoolList {
    int head;
    struct BoolList* tail;
};

struct BoolList* go_29(struct BoolList* acc_, struct BoolList* xs_2) {
tailrec_9:;
    struct BoolList* match_2;
    if ((!((!(xs_2))))) goto next_11;
    match_2 = acc_;
    goto end_match_10;
next_11:;
    if ((!(xs_2))) goto next_12;
    int x_2 = xs_2->head;
    struct BoolList* xs_3 = xs_2->tail;
    struct BoolList* list_3 = (struct BoolList*)milone_mem_alloc(1, sizeof(struct BoolList));
    list_3->head = x_2;
    list_3->tail = acc_;
    struct BoolList* arg_35 = list_3;
    struct BoolList* arg_36 = xs_3;
    acc_ = arg_35;
    xs_2 = arg_36;
    goto tailrec_9;
    match_2 = NULL;
    goto end_match_10;
next_12:;
    exit(1);
end_match_10:;
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
tailrec_13:;
    struct Space_Space_Tuple2List* match_3;
    if ((!((!(xs_2))))) goto next_15;
    match_3 = acc_;
    goto end_match_14;
next_15:;
    if ((!(xs_2))) goto next_16;
    struct Space_Space_Tuple2 x_2 = xs_2->head;
    struct Space_Space_Tuple2List* xs_3 = xs_2->tail;
    struct Space_Space_Tuple2List* list_4 = (struct Space_Space_Tuple2List*)milone_mem_alloc(1, sizeof(struct Space_Space_Tuple2List));
    list_4->head = x_2;
    list_4->tail = acc_;
    struct Space_Space_Tuple2List* arg_37 = list_4;
    struct Space_Space_Tuple2List* arg_38 = xs_3;
    acc_ = arg_37;
    xs_2 = arg_38;
    goto tailrec_13;
    match_3 = NULL;
    goto end_match_14;
next_16:;
    exit(1);
end_match_14:;
    return match_3;
}

struct Space_List* listRev_2(struct Space_List* xs_1) {
    struct Space_List* call_3 = go_27(NULL, xs_1);
    return call_3;
}

struct StringList* listRev_1(struct StringList* xs_1) {
    struct StringList* call_4 = go_26(NULL, xs_1);
    return call_4;
}

struct BoolList* listRev_4(struct BoolList* xs_1) {
    struct BoolList* call_5 = go_29(NULL, xs_1);
    return call_5;
}

struct Space_Space_Tuple2List* listRev_3(struct Space_Space_Tuple2List* xs_1) {
    struct Space_Space_Tuple2List* call_6 = go_28(NULL, xs_1);
    return call_6;
}

struct Space_Space_Fun1 {
    struct Space_(*fun)(void*, struct Space_);
    void* env;
};

struct Space_List* go_25(struct Space_Space_Fun1 f_, struct Space_List* acc_1, struct Space_List* xs_5) {
tailrec_17:;
    struct Space_List* match_4;
    if ((!((!(xs_5))))) goto next_19;
    struct Space_List* call_7 = listRev_2(acc_1);
    match_4 = call_7;
    goto end_match_18;
next_19:;
    if ((!(xs_5))) goto next_20;
    struct Space_ x_3 = xs_5->head;
    struct Space_List* xs_6 = xs_5->tail;
    struct Space_Space_Fun1 arg_39 = f_;
    struct Space_ app_ = f_.fun(f_.env, x_3);
    struct Space_List* list_5 = (struct Space_List*)milone_mem_alloc(1, sizeof(struct Space_List));
    list_5->head = app_;
    list_5->tail = acc_1;
    struct Space_List* arg_40 = list_5;
    struct Space_List* arg_41 = xs_6;
    f_ = arg_39;
    acc_1 = arg_40;
    xs_5 = arg_41;
    goto tailrec_17;
    match_4 = NULL;
    goto end_match_18;
next_20:;
    exit(1);
end_match_18:;
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
        void* Tuple_;
        void* List_;
    };
};

struct Ty_List {
    struct Ty_ head;
    struct Ty_List* tail;
};

struct Space_List* go_24(struct Ty_Space_Fun1 f_, struct Space_List* acc_1, struct Ty_List* xs_5) {
tailrec_21:;
    struct Space_List* match_5;
    if ((!((!(xs_5))))) goto next_23;
    struct Space_List* call_8 = listRev_2(acc_1);
    match_5 = call_8;
    goto end_match_22;
next_23:;
    if ((!(xs_5))) goto next_24;
    struct Ty_ x_3 = xs_5->head;
    struct Ty_List* xs_6 = xs_5->tail;
    struct Ty_Space_Fun1 arg_42 = f_;
    struct Space_ app_1 = f_.fun(f_.env, x_3);
    struct Space_List* list_6 = (struct Space_List*)milone_mem_alloc(1, sizeof(struct Space_List));
    list_6->head = app_1;
    list_6->tail = acc_1;
    struct Space_List* arg_43 = list_6;
    struct Ty_List* arg_44 = xs_6;
    f_ = arg_42;
    acc_1 = arg_43;
    xs_5 = arg_44;
    goto tailrec_21;
    match_5 = NULL;
    goto end_match_22;
next_24:;
    exit(1);
end_match_22:;
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
        void* IntLit_;
        void* TupleLit_;
        void* Cons_;
    };
};

struct Pat_List {
    struct Pat_ head;
    struct Pat_List* tail;
};

struct Space_List* go_23(struct Pat_Space_Fun1 f_, struct Space_List* acc_1, struct Pat_List* xs_5) {
tailrec_25:;
    struct Space_List* match_6;
    if ((!((!(xs_5))))) goto next_27;
    struct Space_List* call_9 = listRev_2(acc_1);
    match_6 = call_9;
    goto end_match_26;
next_27:;
    if ((!(xs_5))) goto next_28;
    struct Pat_ x_3 = xs_5->head;
    struct Pat_List* xs_6 = xs_5->tail;
    struct Pat_Space_Fun1 arg_45 = f_;
    struct Space_ app_2 = f_.fun(f_.env, x_3);
    struct Space_List* list_7 = (struct Space_List*)milone_mem_alloc(1, sizeof(struct Space_List));
    list_7->head = app_2;
    list_7->tail = acc_1;
    struct Space_List* arg_46 = list_7;
    struct Pat_List* arg_47 = xs_6;
    f_ = arg_45;
    acc_1 = arg_46;
    xs_5 = arg_47;
    goto tailrec_25;
    match_6 = NULL;
    goto end_match_26;
next_28:;
    exit(1);
end_match_26:;
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

struct StringSpace_Tuple2List {
    struct StringSpace_Tuple2 head;
    struct StringSpace_Tuple2List* tail;
};

struct BoolList* go_22(struct StringSpace_Tuple2BoolFun1 f_, struct BoolList* acc_1, struct StringSpace_Tuple2List* xs_5) {
tailrec_29:;
    struct BoolList* match_7;
    if ((!((!(xs_5))))) goto next_31;
    struct BoolList* call_10 = listRev_4(acc_1);
    match_7 = call_10;
    goto end_match_30;
next_31:;
    if ((!(xs_5))) goto next_32;
    struct StringSpace_Tuple2 x_3 = xs_5->head;
    struct StringSpace_Tuple2List* xs_6 = xs_5->tail;
    struct StringSpace_Tuple2BoolFun1 arg_48 = f_;
    int app_3 = f_.fun(f_.env, x_3);
    struct BoolList* list_8 = (struct BoolList*)milone_mem_alloc(1, sizeof(struct BoolList));
    list_8->head = app_3;
    list_8->tail = acc_1;
    struct BoolList* arg_49 = list_8;
    struct StringSpace_Tuple2List* arg_50 = xs_6;
    f_ = arg_48;
    acc_1 = arg_49;
    xs_5 = arg_50;
    goto tailrec_29;
    match_7 = NULL;
    goto end_match_30;
next_32:;
    exit(1);
end_match_30:;
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

struct StringTy_Pat_ListCovering_Tuple4List {
    struct StringTy_Pat_ListCovering_Tuple4 head;
    struct StringTy_Pat_ListCovering_Tuple4List* tail;
};

struct BoolList* go_21(struct StringTy_Pat_ListCovering_Tuple4BoolFun1 f_, struct BoolList* acc_1, struct StringTy_Pat_ListCovering_Tuple4List* xs_5) {
tailrec_33:;
    struct BoolList* match_8;
    if ((!((!(xs_5))))) goto next_35;
    struct BoolList* call_11 = listRev_4(acc_1);
    match_8 = call_11;
    goto end_match_34;
next_35:;
    if ((!(xs_5))) goto next_36;
    struct StringTy_Pat_ListCovering_Tuple4 x_3 = xs_5->head;
    struct StringTy_Pat_ListCovering_Tuple4List* xs_6 = xs_5->tail;
    struct StringTy_Pat_ListCovering_Tuple4BoolFun1 arg_51 = f_;
    int app_4 = f_.fun(f_.env, x_3);
    struct BoolList* list_9 = (struct BoolList*)milone_mem_alloc(1, sizeof(struct BoolList));
    list_9->head = app_4;
    list_9->tail = acc_1;
    struct BoolList* arg_52 = list_9;
    struct StringTy_Pat_ListCovering_Tuple4List* arg_53 = xs_6;
    f_ = arg_51;
    acc_1 = arg_52;
    xs_5 = arg_53;
    goto tailrec_33;
    match_8 = NULL;
    goto end_match_34;
next_36:;
    exit(1);
end_match_34:;
    return match_8;
}

struct Space_List* listMap_5(struct Space_Space_Fun1 f_, struct Space_List* xs_4) {
    struct Space_List* call_12 = go_25(f_, NULL, xs_4);
    return call_12;
}

struct Space_List* listMap_4(struct Ty_Space_Fun1 f_, struct Ty_List* xs_4) {
    struct Space_List* call_13 = go_24(f_, NULL, xs_4);
    return call_13;
}

struct Space_List* listMap_3(struct Pat_Space_Fun1 f_, struct Pat_List* xs_4) {
    struct Space_List* call_14 = go_23(f_, NULL, xs_4);
    return call_14;
}

struct BoolList* listMap_2(struct StringSpace_Tuple2BoolFun1 f_, struct StringSpace_Tuple2List* xs_4) {
    struct BoolList* call_15 = go_22(f_, NULL, xs_4);
    return call_15;
}

struct BoolList* listMap_1(struct StringTy_Pat_ListCovering_Tuple4BoolFun1 f_, struct StringTy_Pat_ListCovering_Tuple4List* xs_4) {
    struct BoolList* call_16 = go_21(f_, NULL, xs_4);
    return call_16;
}

struct IntSpace_Space_Tuple2Space_Fun2 {
    struct Space_(*fun)(void*, int, struct Space_Space_Tuple2);
    void* env;
};

struct Space_List* go_20(struct IntSpace_Space_Tuple2Space_Fun2 f_1, struct Space_List* acc_2, int i_, struct Space_Space_Tuple2List* xs_8) {
tailrec_37:;
    struct Space_List* match_9;
    if ((!((!(xs_8))))) goto next_39;
    struct Space_List* call_17 = listRev_2(acc_2);
    match_9 = call_17;
    goto end_match_38;
next_39:;
    if ((!(xs_8))) goto next_40;
    struct Space_Space_Tuple2 x_4 = xs_8->head;
    struct Space_Space_Tuple2List* xs_9 = xs_8->tail;
    struct IntSpace_Space_Tuple2Space_Fun2 arg_54 = f_1;
    struct Space_ app_5 = f_1.fun(f_1.env, i_, x_4);
    struct Space_List* list_10 = (struct Space_List*)milone_mem_alloc(1, sizeof(struct Space_List));
    list_10->head = app_5;
    list_10->tail = acc_2;
    struct Space_List* arg_55 = list_10;
    int arg_56 = (i_ + 1);
    struct Space_Space_Tuple2List* arg_57 = xs_9;
    f_1 = arg_54;
    acc_2 = arg_55;
    i_ = arg_56;
    xs_8 = arg_57;
    goto tailrec_37;
    match_9 = NULL;
    goto end_match_38;
next_40:;
    exit(1);
end_match_38:;
    return match_9;
}

struct IntSpace_Space_Fun2 {
    struct Space_(*fun)(void*, int, struct Space_);
    void* env;
};

struct Space_List* go_19(struct IntSpace_Space_Fun2 f_1, struct Space_List* acc_2, int i_, struct Space_List* xs_8) {
tailrec_41:;
    struct Space_List* match_10;
    if ((!((!(xs_8))))) goto next_43;
    struct Space_List* call_18 = listRev_2(acc_2);
    match_10 = call_18;
    goto end_match_42;
next_43:;
    if ((!(xs_8))) goto next_44;
    struct Space_ x_4 = xs_8->head;
    struct Space_List* xs_9 = xs_8->tail;
    struct IntSpace_Space_Fun2 arg_58 = f_1;
    struct Space_ app_6 = f_1.fun(f_1.env, i_, x_4);
    struct Space_List* list_11 = (struct Space_List*)milone_mem_alloc(1, sizeof(struct Space_List));
    list_11->head = app_6;
    list_11->tail = acc_2;
    struct Space_List* arg_59 = list_11;
    int arg_60 = (i_ + 1);
    struct Space_List* arg_61 = xs_9;
    f_1 = arg_58;
    acc_2 = arg_59;
    i_ = arg_60;
    xs_8 = arg_61;
    goto tailrec_41;
    match_10 = NULL;
    goto end_match_42;
next_44:;
    exit(1);
end_match_42:;
    return match_10;
}

struct Space_List* listMapWithIndex_2(struct IntSpace_Space_Tuple2Space_Fun2 f_1, struct Space_Space_Tuple2List* xs_7) {
    struct Space_List* call_19 = go_20(f_1, NULL, 0, xs_7);
    return call_19;
}

struct Space_List* listMapWithIndex_1(struct IntSpace_Space_Fun2 f_1, struct Space_List* xs_7) {
    struct Space_List* call_20 = go_19(f_1, NULL, 0, xs_7);
    return call_20;
}

struct Space_BoolFun1 {
    int(*fun)(void*, struct Space_);
    void* env;
};

int go_18(struct Space_BoolFun1 p_, struct Space_List* xs_11) {
tailrec_45:;
    int match_11;
    if ((!((!(xs_11))))) goto next_47;
    match_11 = 1;
    goto end_match_46;
next_47:;
    if ((!(xs_11))) goto next_48;
    struct Space_ x_5 = xs_11->head;
    struct Space_List* xs_12 = xs_11->tail;
    int app_7 = p_.fun(p_.env, x_5);
    int if_;
    if (app_7) {
        goto then_50;
    } else {
        goto else_51;
    }
then_50:;
    struct Space_BoolFun1 arg_62 = p_;
    struct Space_List* arg_63 = xs_12;
    p_ = arg_62;
    xs_11 = arg_63;
    goto tailrec_45;
    if_ = 0;
    goto if_next_49;
else_51:;
    if_ = 0;
    goto if_next_49;
if_next_49:;
    match_11 = if_;
    goto end_match_46;
next_48:;
    exit(1);
end_match_46:;
    return match_11;
}

struct Space_Space_Tuple2BoolFun1 {
    int(*fun)(void*, struct Space_Space_Tuple2);
    void* env;
};

int go_17(struct Space_Space_Tuple2BoolFun1 p_, struct Space_Space_Tuple2List* xs_11) {
tailrec_52:;
    int match_12;
    if ((!((!(xs_11))))) goto next_54;
    match_12 = 1;
    goto end_match_53;
next_54:;
    if ((!(xs_11))) goto next_55;
    struct Space_Space_Tuple2 x_5 = xs_11->head;
    struct Space_Space_Tuple2List* xs_12 = xs_11->tail;
    int app_8 = p_.fun(p_.env, x_5);
    int if_1;
    if (app_8) {
        goto then_57;
    } else {
        goto else_58;
    }
then_57:;
    struct Space_Space_Tuple2BoolFun1 arg_64 = p_;
    struct Space_Space_Tuple2List* arg_65 = xs_12;
    p_ = arg_64;
    xs_11 = arg_65;
    goto tailrec_52;
    if_1 = 0;
    goto if_next_56;
else_58:;
    if_1 = 0;
    goto if_next_56;
if_next_56:;
    match_12 = if_1;
    goto end_match_53;
next_55:;
    exit(1);
end_match_53:;
    return match_12;
}

struct BoolBoolFun1 {
    int(*fun)(void*, int);
    void* env;
};

int go_16(struct BoolBoolFun1 p_, struct BoolList* xs_11) {
tailrec_59:;
    int match_13;
    if ((!((!(xs_11))))) goto next_61;
    match_13 = 1;
    goto end_match_60;
next_61:;
    if ((!(xs_11))) goto next_62;
    int x_5 = xs_11->head;
    struct BoolList* xs_12 = xs_11->tail;
    int app_9 = p_.fun(p_.env, x_5);
    int if_2;
    if (app_9) {
        goto then_64;
    } else {
        goto else_65;
    }
then_64:;
    struct BoolBoolFun1 arg_66 = p_;
    struct BoolList* arg_67 = xs_12;
    p_ = arg_66;
    xs_11 = arg_67;
    goto tailrec_59;
    if_2 = 0;
    goto if_next_63;
else_65:;
    if_2 = 0;
    goto if_next_63;
if_next_63:;
    match_13 = if_2;
    goto end_match_60;
next_62:;
    exit(1);
end_match_60:;
    return match_13;
}

int listForAll_3(struct Space_BoolFun1 p_, struct Space_List* xs_10) {
    int call_21 = go_18(p_, xs_10);
    return call_21;
}

int listForAll_2(struct Space_Space_Tuple2BoolFun1 p_, struct Space_Space_Tuple2List* xs_10) {
    int call_22 = go_17(p_, xs_10);
    return call_22;
}

int listForAll_1(struct BoolBoolFun1 p_, struct BoolList* xs_10) {
    int call_23 = go_16(p_, xs_10);
    return call_23;
}

int go_15(struct Space_BoolFun1 p_1, struct Space_List* xs_14) {
tailrec_66:;
    int match_14;
    if ((!((!(xs_14))))) goto next_68;
    match_14 = 0;
    goto end_match_67;
next_68:;
    if ((!(xs_14))) goto next_69;
    struct Space_ x_6 = xs_14->head;
    struct Space_List* xs_15 = xs_14->tail;
    int app_10 = p_1.fun(p_1.env, x_6);
    int if_3;
    if (app_10) {
        goto then_71;
    } else {
        goto else_72;
    }
then_71:;
    if_3 = 1;
    goto if_next_70;
else_72:;
    struct Space_BoolFun1 arg_68 = p_1;
    struct Space_List* arg_69 = xs_15;
    p_1 = arg_68;
    xs_14 = arg_69;
    goto tailrec_66;
    if_3 = 0;
    goto if_next_70;
if_next_70:;
    match_14 = if_3;
    goto end_match_67;
next_69:;
    exit(1);
end_match_67:;
    return match_14;
}

int listExists_1(struct Space_BoolFun1 p_1, struct Space_List* xs_13) {
    int call_24 = go_15(p_1, xs_13);
    return call_24;
}

struct Space_Space_Space_Fun2 {
    struct Space_(*fun)(void*, struct Space_, struct Space_);
    void* env;
};

struct Space_ go_14(struct Space_Space_Space_Fun2 folder_, struct Space_ state_1, struct Space_List* xs_17) {
tailrec_73:;
    struct Space_ match_15;
    if ((!((!(xs_17))))) goto next_75;
    match_15 = state_1;
    goto end_match_74;
next_75:;
    if ((!(xs_17))) goto next_76;
    struct Space_ x_7 = xs_17->head;
    struct Space_List* xs_18 = xs_17->tail;
    struct Space_Space_Space_Fun2 arg_70 = folder_;
    struct Space_ app_11 = folder_.fun(folder_.env, state_1, x_7);
    struct Space_ arg_71 = app_11;
    struct Space_List* arg_72 = xs_18;
    folder_ = arg_70;
    state_1 = arg_71;
    xs_17 = arg_72;
    goto tailrec_73;
    match_15 = ((struct Space_){});
    goto end_match_74;
next_76:;
    exit(1);
end_match_74:;
    return match_15;
}

struct StringListSpace_StringListFun2 {
    struct StringList*(*fun)(void*, struct StringList*, struct Space_);
    void* env;
};

struct StringList* go_13(struct StringListSpace_StringListFun2 folder_, struct StringList* state_1, struct Space_List* xs_17) {
tailrec_77:;
    struct StringList* match_16;
    if ((!((!(xs_17))))) goto next_79;
    match_16 = state_1;
    goto end_match_78;
next_79:;
    if ((!(xs_17))) goto next_80;
    struct Space_ x_7 = xs_17->head;
    struct Space_List* xs_18 = xs_17->tail;
    struct StringListSpace_StringListFun2 arg_73 = folder_;
    struct StringList* app_12 = folder_.fun(folder_.env, state_1, x_7);
    struct StringList* arg_74 = app_12;
    struct Space_List* arg_75 = xs_18;
    folder_ = arg_73;
    state_1 = arg_74;
    xs_17 = arg_75;
    goto tailrec_77;
    match_16 = NULL;
    goto end_match_78;
next_80:;
    exit(1);
end_match_78:;
    return match_16;
}

struct Space_ listFold_2(struct Space_Space_Space_Fun2 folder_, struct Space_ state_, struct Space_List* xs_16) {
    struct Space_ call_25 = go_14(folder_, state_, xs_16);
    return call_25;
}

struct StringList* listFold_1(struct StringListSpace_StringListFun2 folder_, struct StringList* state_, struct Space_List* xs_16) {
    struct StringList* call_26 = go_13(folder_, state_, xs_16);
    return call_26;
}

struct Space_ListSpace_ListTuple2 {
    struct Space_List* t0;
    struct Space_List* t1;
};

struct Space_Space_Tuple2List* go_12(struct Space_Space_Tuple2List* acc_3, struct Space_List* xs_20, struct Space_List* ys_1) {
tailrec_81:;
    struct Space_Space_Tuple2List* match_17;
    struct Space_ListSpace_ListTuple2 tuple_;
    tuple_.t0 = xs_20;
    tuple_.t1 = ys_1;
    if ((!((!(tuple_.t0))))) goto next_84;
    goto match_body_83;
next_84:;
    if ((!((!(tuple_.t1))))) goto next_85;
    goto match_body_83;
match_body_83:;
    struct Space_Space_Tuple2List* call_27 = listRev_3(acc_3);
    match_17 = call_27;
    goto end_match_82;
next_85:;
    if ((!(tuple_.t0))) goto next_86;
    struct Space_ x_8 = tuple_.t0->head;
    struct Space_List* xs_21 = tuple_.t0->tail;
    if ((!(tuple_.t1))) goto next_86;
    struct Space_ y_ = tuple_.t1->head;
    struct Space_List* ys_2 = tuple_.t1->tail;
    struct Space_Space_Tuple2 tuple_1;
    tuple_1.t0 = x_8;
    tuple_1.t1 = y_;
    struct Space_Space_Tuple2List* list_12 = (struct Space_Space_Tuple2List*)milone_mem_alloc(1, sizeof(struct Space_Space_Tuple2List));
    list_12->head = tuple_1;
    list_12->tail = acc_3;
    struct Space_Space_Tuple2List* arg_76 = list_12;
    struct Space_List* arg_77 = xs_21;
    struct Space_List* arg_78 = ys_2;
    acc_3 = arg_76;
    xs_20 = arg_77;
    ys_1 = arg_78;
    goto tailrec_81;
    match_17 = NULL;
    goto end_match_82;
next_86:;
    exit(1);
end_match_82:;
    return match_17;
}

struct Space_Space_Tuple2List* listZip_1(struct Space_List* xs_19, struct Space_List* ys_) {
    struct Space_Space_Tuple2List* call_28 = go_12(NULL, xs_19, ys_);
    return call_28;
}

struct String go_7(struct StringList* xs_23) {
    struct String match_18;
    if ((!((!(xs_23))))) goto next_88;
    match_18 = (struct String){.str = "", .len = 0};
    goto end_match_87;
next_88:;
    if ((!(xs_23))) goto next_89;
    struct String x_9 = xs_23->head;
    struct StringList* xs_24 = xs_23->tail;
    struct String call_29 = go_7(xs_24);
    match_18 = str_add(x_9, call_29);
    goto end_match_87;
next_89:;
    exit(1);
end_match_87:;
    return match_18;
}

struct String strConcat_(struct StringList* xs_22) {
    struct String call_30 = go_7(xs_22);
    return call_30;
}

struct StringSpace_ListTuple2 {
    struct String t0;
    struct Space_List* t1;
};

struct Space_ spaceCtor_(struct String tag_, struct Space_List* items_) {
    struct StringSpace_ListTuple2 tuple_2;
    tuple_2.t0 = tag_;
    tuple_2.t1 = items_;
    void* box_ = (void*)milone_mem_alloc(1, sizeof(struct StringSpace_ListTuple2));
    (*(((struct StringSpace_ListTuple2*)box_))) = tuple_2;
    struct Space_ variant_ = (struct Space_){.tag = Ctor_, .Ctor_ = box_};
    return variant_;
}

struct UnitSpace_Fun1 {
    struct Space_(*fun)(void*, int);
    void* env;
};

struct StringUnitSpace_Fun1Tuple2 {
    struct String t0;
    struct UnitSpace_Fun1 t1;
};

struct Space_ spaceRef_(struct String tag_1, struct UnitSpace_Fun1 thunk_) {
    struct StringUnitSpace_Fun1Tuple2 tuple_3;
    tuple_3.t0 = tag_1;
    tuple_3.t1 = thunk_;
    void* box_1 = (void*)milone_mem_alloc(1, sizeof(struct StringUnitSpace_Fun1Tuple2));
    (*(((struct StringUnitSpace_Fun1Tuple2*)box_1))) = tuple_3;
    struct Space_ variant_1 = (struct Space_){.tag = Ref_, .Ref_ = box_1};
    return variant_1;
}

struct Space_List* go_8(struct Space_List* spaces_1, struct Space_List* acc_4) {
tailrec_90:;
    struct Space_List* match_19;
    if ((!((!(spaces_1))))) goto next_92;
    struct Space_List* call_31 = listRev_2(acc_4);
    match_19 = call_31;
    goto end_match_91;
next_92:;
    if ((!(spaces_1))) goto next_93;
    if ((spaces_1->head.tag != Union_)) goto next_93;
    struct Space_List* subspaces_ = (*(((struct Space_List**)spaces_1->head.Union_)));
    struct Space_List* spaces_2 = spaces_1->tail;
    struct Space_List* arg_79 = spaces_2;
    struct Space_List* call_32 = go_8(subspaces_, acc_4);
    struct Space_List* arg_80 = call_32;
    spaces_1 = arg_79;
    acc_4 = arg_80;
    goto tailrec_90;
    match_19 = NULL;
    goto end_match_91;
next_93:;
    if ((!(spaces_1))) goto next_94;
    struct Space_ space_ = spaces_1->head;
    struct Space_List* spaces_3 = spaces_1->tail;
    int call_33 = spaceIsEmpty_(space_);
    if ((!(call_33))) goto next_94;
    struct Space_List* arg_81 = spaces_3;
    struct Space_List* arg_82 = acc_4;
    spaces_1 = arg_81;
    acc_4 = arg_82;
    goto tailrec_90;
    match_19 = NULL;
    goto end_match_91;
next_94:;
    if ((!(spaces_1))) goto next_95;
    struct Space_ space_1 = spaces_1->head;
    struct Space_List* spaces_4 = spaces_1->tail;
    struct Space_List* arg_83 = spaces_4;
    struct Space_List* list_13 = (struct Space_List*)milone_mem_alloc(1, sizeof(struct Space_List));
    list_13->head = space_1;
    list_13->tail = acc_4;
    struct Space_List* arg_84 = list_13;
    spaces_1 = arg_83;
    acc_4 = arg_84;
    goto tailrec_90;
    match_19 = NULL;
    goto end_match_91;
next_95:;
    struct Space_List* call_34 = failwith_3((struct String){.str = "NEVER: suppress warning", .len = 23});
    match_19 = call_34;
    goto end_match_91;
next_96:;
end_match_91:;
    return match_19;
}

struct Space_ spaceUnion_(struct Space_List* spaces_) {
    struct Space_ match_20;
    struct Space_List* call_35 = go_8(spaces_, NULL);
    if ((!(call_35))) goto next_98;
    struct Space_ space_2 = call_35->head;
    if ((!((!(call_35->tail))))) goto next_98;
    match_20 = space_2;
    goto end_match_97;
next_98:;
    struct Space_List* spaces_5 = call_35;
    void* box_2 = (void*)milone_mem_alloc(1, sizeof(struct Space_List*));
    (*(((struct Space_List**)box_2))) = spaces_5;
    struct Space_ variant_2 = (struct Space_){.tag = Union_, .Union_ = box_2};
    match_20 = variant_2;
    goto end_match_97;
next_99:;
end_match_97:;
    return match_20;
}

int fun_9(void* env_, struct Space_ arg_) {
    int call_36 = spaceIsEmpty_(arg_);
    return call_36;
}

int fun_10(void* env_1, struct Space_ arg_1) {
    int call_37 = spaceIsEmpty_(arg_1);
    return call_37;
}

int spaceIsEmpty_(struct Space_ space_3) {
    int match_21;
    if ((space_3.tag != Ctor_)) goto next_101;
    struct Space_List* spaces_6 = (*(((struct StringSpace_ListTuple2*)space_3.Ctor_))).t1;
    void* box_3 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_3))) = 0;
    void* env_19 = box_3;
    struct Space_BoolFun1 fun_28 = (struct Space_BoolFun1){.fun = fun_9, .env = env_19};
    int call_38 = listExists_1(fun_28, spaces_6);
    match_21 = call_38;
    goto end_match_100;
next_101:;
    if ((space_3.tag != Union_)) goto next_102;
    struct Space_List* spaces_7 = (*(((struct Space_List**)space_3.Union_)));
    void* box_4 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_4))) = 0;
    void* env_20 = box_4;
    struct Space_BoolFun1 fun_29 = (struct Space_BoolFun1){.fun = fun_10, .env = env_20};
    int call_39 = listForAll_3(fun_29, spaces_7);
    match_21 = call_39;
    goto end_match_100;
next_102:;
    match_21 = 0;
    goto end_match_100;
next_103:;
end_match_100:;
    int result_ = match_21;
    return result_;
}

struct Space_ spaceDecompose_(struct Space_ space_4) {
    struct Space_ match_22;
    if ((space_4.tag != Ref_)) goto next_105;
    struct UnitSpace_Fun1 thunk_1 = (*(((struct StringUnitSpace_Fun1Tuple2*)space_4.Ref_))).t1;
    struct Space_ app_13 = thunk_1.fun(thunk_1.env, 0);
    struct Space_ space_5 = app_13;
    int call_40 = spaceIsEmpty_(space_5);
    milone_assert((!(call_40)), 234, 4);
    int call_41 = 0;
    match_22 = space_5;
    goto end_match_104;
next_105:;
    milone_assert(0, 238, 4);
    int call_42 = 0;
    match_22 = space_4;
    goto end_match_104;
next_106:;
end_match_104:;
    return match_22;
}

int fun_(struct Space_Space_Tuple2 arg_85) {
    struct Space_ first_1 = arg_85.t0;
    struct Space_ second_1 = arg_85.t1;
    int call_43 = spaceCovers_(first_1, second_1);
    return call_43;
}

int fun_11(void* env_2, struct Space_Space_Tuple2 arg_2) {
    int call_44 = fun_(arg_2);
    return call_44;
}

struct Space_ fun_2(int i_1, int j_, struct Space_Space_Tuple2 arg_86) {
    struct Space_ first_2 = arg_86.t0;
    struct Space_ second_2 = arg_86.t1;
    struct Space_ if_4;
    if ((i_1 == j_)) {
        goto then_108;
    } else {
        goto else_109;
    }
then_108:;
    struct Space_ call_45 = spaceExclude_(first_2, second_2);
    if_4 = call_45;
    goto if_next_107;
else_109:;
    if_4 = first_2;
    goto if_next_107;
if_next_107:;
    return if_4;
}

struct IntTuple1 {
    int t0;
};

struct Space_ fun_12(void* env_3, int arg_3, struct Space_Space_Tuple2 arg_4) {
    int arg_5 = (*(((struct IntTuple1*)env_3))).t0;
    struct Space_ call_46 = fun_2(arg_5, arg_3, arg_4);
    return call_46;
}

struct Space_ fun_1(struct String tag_2, struct Space_List* firsts_, struct Space_List* seconds_, int i_1, struct Space_ arg_87) {
    struct IntTuple1 tuple_4;
    tuple_4.t0 = i_1;
    void* box_5 = (void*)milone_mem_alloc(1, sizeof(struct IntTuple1));
    (*(((struct IntTuple1*)box_5))) = tuple_4;
    void* env_21 = box_5;
    struct IntSpace_Space_Tuple2Space_Fun2 fun_30 = (struct IntSpace_Space_Tuple2Space_Fun2){.fun = fun_12, .env = env_21};
    struct Space_Space_Tuple2List* call_47 = listZip_1(firsts_, seconds_);
    struct Space_List* call_48 = listMapWithIndex_2(fun_30, call_47);
    struct Space_ call_49 = spaceCtor_(tag_2, call_48);
    return call_49;
}

struct StringSpace_ListSpace_ListTuple3 {
    struct String t0;
    struct Space_List* t1;
    struct Space_List* t2;
};

struct Space_ fun_13(void* env_4, int arg_6, struct Space_ arg_7) {
    struct String arg_8 = (*(((struct StringSpace_ListSpace_ListTuple3*)env_4))).t0;
    struct Space_List* arg_9 = (*(((struct StringSpace_ListSpace_ListTuple3*)env_4))).t1;
    struct Space_List* arg_10 = (*(((struct StringSpace_ListSpace_ListTuple3*)env_4))).t2;
    struct Space_ call_50 = fun_1(arg_8, arg_9, arg_10, arg_6, arg_7);
    return call_50;
}

struct Space_ fun_14(void* env_5, struct Space_ arg_11, struct Space_ arg_12) {
    struct Space_ call_51 = spaceExclude_(arg_11, arg_12);
    return call_51;
}

struct Space_ fun_3(struct Space_ second_, struct Space_ first_3) {
    struct Space_ call_52 = spaceExclude_(first_3, second_);
    return call_52;
}

struct Space_Tuple1 {
    struct Space_ t0;
};

struct Space_ fun_15(void* env_6, struct Space_ arg_13) {
    struct Space_ arg_14 = (*(((struct Space_Tuple1*)env_6))).t0;
    struct Space_ call_53 = fun_3(arg_14, arg_13);
    return call_53;
}

struct Space_ spaceExclude_(struct Space_ first_, struct Space_ second_) {
tailrec_110:;
    struct Space_ match_23;
    struct Space_Space_Tuple2 tuple_5;
    tuple_5.t0 = first_;
    tuple_5.t1 = second_;
    if ((tuple_5.t0.tag != Union_)) goto next_112;
    if ((!((!((*(((struct Space_List**)tuple_5.t0.Union_)))))))) goto next_112;
    match_23 = spaceEmpty_;
    goto end_match_111;
next_112:;
    if ((tuple_5.t1.tag != Union_)) goto next_113;
    if ((!((!((*(((struct Space_List**)tuple_5.t1.Union_)))))))) goto next_113;
    match_23 = first_;
    goto end_match_111;
next_113:;
    if ((tuple_5.t1.tag != Full_)) goto next_114;
    match_23 = spaceEmpty_;
    goto end_match_111;
next_114:;
    if ((tuple_5.t0.tag != Full_)) goto next_115;
    if ((tuple_5.t1.tag != Ctor_)) goto next_115;
    match_23 = spaceFull_;
    goto end_match_111;
next_115:;
    if ((tuple_5.t0.tag != Ctor_)) goto next_116;
    struct String tag_2 = (*(((struct StringSpace_ListTuple2*)tuple_5.t0.Ctor_))).t0;
    struct Space_List* firsts_ = (*(((struct StringSpace_ListTuple2*)tuple_5.t0.Ctor_))).t1;
    if ((tuple_5.t1.tag != Ctor_)) goto next_116;
    struct String secondTag_ = (*(((struct StringSpace_ListTuple2*)tuple_5.t1.Ctor_))).t0;
    struct Space_List* seconds_ = (*(((struct StringSpace_ListTuple2*)tuple_5.t1.Ctor_))).t1;
    if ((str_cmp(tag_2, secondTag_) != 0)) goto next_116;
    void* box_6 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_6))) = 0;
    void* env_22 = box_6;
    struct Space_Space_Tuple2BoolFun1 fun_31 = (struct Space_Space_Tuple2BoolFun1){.fun = fun_11, .env = env_22};
    struct Space_Space_Tuple2List* call_54 = listZip_1(firsts_, seconds_);
    int call_55 = listForAll_2(fun_31, call_54);
    int dominant_ = call_55;
    struct Space_ if_5;
    if (dominant_) {
        goto then_124;
    } else {
        goto else_125;
    }
then_124:;
    if_5 = spaceEmpty_;
    goto if_next_123;
else_125:;
    struct StringSpace_ListSpace_ListTuple3 tuple_6;
    tuple_6.t0 = tag_2;
    tuple_6.t1 = firsts_;
    tuple_6.t2 = seconds_;
    void* box_7 = (void*)milone_mem_alloc(1, sizeof(struct StringSpace_ListSpace_ListTuple3));
    (*(((struct StringSpace_ListSpace_ListTuple3*)box_7))) = tuple_6;
    void* env_23 = box_7;
    struct IntSpace_Space_Fun2 fun_32 = (struct IntSpace_Space_Fun2){.fun = fun_13, .env = env_23};
    struct Space_List* call_56 = listMapWithIndex_1(fun_32, firsts_);
    struct Space_ call_57 = spaceUnion_(call_56);
    if_5 = call_57;
    goto if_next_123;
if_next_123:;
    match_23 = if_5;
    goto end_match_111;
next_116:;
    if ((tuple_5.t0.tag != Ctor_)) goto next_117;
    if ((tuple_5.t1.tag != Ctor_)) goto next_117;
    match_23 = first_;
    goto end_match_111;
next_117:;
    if ((tuple_5.t1.tag != Union_)) goto next_118;
    struct Space_List* seconds_1 = (*(((struct Space_List**)tuple_5.t1.Union_)));
    void* box_8 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_8))) = 0;
    void* env_24 = box_8;
    struct Space_Space_Space_Fun2 fun_33 = (struct Space_Space_Space_Fun2){.fun = fun_14, .env = env_24};
    struct Space_ call_58 = listFold_2(fun_33, first_, seconds_1);
    match_23 = call_58;
    goto end_match_111;
next_118:;
    if ((tuple_5.t0.tag != Union_)) goto next_119;
    struct Space_List* firsts_1 = (*(((struct Space_List**)tuple_5.t0.Union_)));
    struct Space_Tuple1 tuple_7;
    tuple_7.t0 = second_;
    void* box_9 = (void*)milone_mem_alloc(1, sizeof(struct Space_Tuple1));
    (*(((struct Space_Tuple1*)box_9))) = tuple_7;
    void* env_25 = box_9;
    struct Space_Space_Fun1 fun_34 = (struct Space_Space_Fun1){.fun = fun_15, .env = env_25};
    struct Space_List* call_59 = listMap_5(fun_34, firsts_1);
    struct Space_ call_60 = spaceUnion_(call_59);
    match_23 = call_60;
    goto end_match_111;
next_119:;
    if ((tuple_5.t0.tag != Ref_)) goto next_120;
    struct String tag_3 = (*(((struct StringUnitSpace_Fun1Tuple2*)tuple_5.t0.Ref_))).t0;
    if ((tuple_5.t1.tag != Ref_)) goto next_120;
    struct String secondTag_1 = (*(((struct StringUnitSpace_Fun1Tuple2*)tuple_5.t1.Ref_))).t0;
    if ((str_cmp(tag_3, secondTag_1) != 0)) goto next_120;
    match_23 = spaceEmpty_;
    goto end_match_111;
next_120:;
    if ((tuple_5.t0.tag != Ref_)) goto next_121;
    struct Space_ call_61 = spaceDecompose_(first_);
    struct Space_ arg_88 = call_61;
    struct Space_ arg_89 = second_;
    first_ = arg_88;
    second_ = arg_89;
    goto tailrec_110;
    match_23 = ((struct Space_){});
    goto end_match_111;
next_121:;
    if ((tuple_5.t1.tag != Ref_)) goto next_122;
    milone_assert(0, 345, 4);
    int call_62 = 0;
    struct Space_ arg_90 = first_;
    struct Space_ call_63 = spaceDecompose_(second_);
    struct Space_ arg_91 = call_63;
    first_ = arg_90;
    second_ = arg_91;
    goto tailrec_110;
    match_23 = ((struct Space_){});
    goto end_match_111;
next_122:;
    exit(1);
end_match_111:;
    return match_23;
}

int spaceCovers_(struct Space_ other_, struct Space_ cover_) {
    struct Space_ call_64 = spaceExclude_(other_, cover_);
    int call_65 = spaceIsEmpty_(call_64);
    return call_65;
}

struct StringList* fun_4(struct StringList* acc_7, struct Space_ space_8) {
    struct StringList* call_66 = cons_1((struct String){.str = ", ", .len = 2}, acc_7);
    struct StringList* call_67 = go_9(space_8, call_66);
    return call_67;
}

struct StringList* fun_16(void* env_7, struct StringList* arg_15, struct Space_ arg_16) {
    struct StringList* call_68 = fun_4(arg_15, arg_16);
    return call_68;
}

struct StringList* fun_5(struct StringList* acc_9, struct Space_ space_9) {
    struct StringList* call_69 = cons_1((struct String){.str = ", ", .len = 2}, acc_9);
    struct StringList* call_70 = go_9(space_9, call_69);
    return call_70;
}

struct StringList* fun_17(void* env_8, struct StringList* arg_17, struct Space_ arg_18) {
    struct StringList* call_71 = fun_5(arg_17, arg_18);
    return call_71;
}

struct StringList* go_9(struct Space_ space_7, struct StringList* acc_5) {
    struct StringList* match_24;
    if ((space_7.tag != Full_)) goto next_127;
    struct StringList* call_72 = cons_1((struct String){.str = "full", .len = 4}, acc_5);
    match_24 = call_72;
    goto end_match_126;
next_127:;
    if ((space_7.tag != Ctor_)) goto next_128;
    struct String tag_4 = (*(((struct StringSpace_ListTuple2*)space_7.Ctor_))).t0;
    if ((!((!((*(((struct StringSpace_ListTuple2*)space_7.Ctor_))).t1))))) goto next_128;
    struct StringList* call_73 = cons_1(tag_4, acc_5);
    match_24 = call_73;
    goto end_match_126;
next_128:;
    if ((space_7.tag != Ctor_)) goto next_129;
    struct String tag_5 = (*(((struct StringSpace_ListTuple2*)space_7.Ctor_))).t0;
    if ((!((*(((struct StringSpace_ListTuple2*)space_7.Ctor_))).t1))) goto next_129;
    struct Space_ item_ = (*(((struct StringSpace_ListTuple2*)space_7.Ctor_))).t1->head;
    struct Space_List* items_1 = (*(((struct StringSpace_ListTuple2*)space_7.Ctor_))).t1->tail;
    struct StringList* call_74 = cons_1(tag_5, acc_5);
    struct StringList* call_75 = cons_1((struct String){.str = "(", .len = 1}, call_74);
    struct StringList* call_76 = go_9(item_, call_75);
    struct StringList* acc_6 = call_76;
    void* box_10 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_10))) = 0;
    void* env_26 = box_10;
    struct StringListSpace_StringListFun2 fun_35 = (struct StringListSpace_StringListFun2){.fun = fun_16, .env = env_26};
    struct StringList* call_77 = listFold_1(fun_35, acc_6, items_1);
    struct StringList* call_78 = cons_1((struct String){.str = ")", .len = 1}, call_77);
    match_24 = call_78;
    goto end_match_126;
next_129:;
    if ((space_7.tag != Ref_)) goto next_130;
    struct String tag_6 = (*(((struct StringUnitSpace_Fun1Tuple2*)space_7.Ref_))).t0;
    struct StringList* call_79 = cons_1(tag_6, acc_5);
    match_24 = call_79;
    goto end_match_126;
next_130:;
    if ((space_7.tag != Union_)) goto next_131;
    if ((!((!((*(((struct Space_List**)space_7.Union_)))))))) goto next_131;
    struct StringList* call_80 = cons_1((struct String){.str = "empty", .len = 5}, acc_5);
    match_24 = call_80;
    goto end_match_126;
next_131:;
    if ((space_7.tag != Union_)) goto next_132;
    if ((!((*(((struct Space_List**)space_7.Union_)))))) goto next_132;
    struct Space_ subspace_ = (*(((struct Space_List**)space_7.Union_)))->head;
    struct Space_List* subspaces_1 = (*(((struct Space_List**)space_7.Union_)))->tail;
    struct StringList* call_81 = cons_1((struct String){.str = "+(", .len = 2}, acc_5);
    struct StringList* call_82 = go_9(subspace_, call_81);
    struct StringList* acc_8 = call_82;
    void* box_11 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_11))) = 0;
    void* env_27 = box_11;
    struct StringListSpace_StringListFun2 fun_36 = (struct StringListSpace_StringListFun2){.fun = fun_17, .env = env_27};
    struct StringList* call_83 = listFold_1(fun_36, acc_8, subspaces_1);
    struct StringList* call_84 = cons_1((struct String){.str = ")", .len = 1}, call_83);
    match_24 = call_84;
    goto end_match_126;
next_132:;
    struct StringList* call_85 = failwith_2((struct String){.str = "NEVER: suppress warning", .len = 23});
    match_24 = call_85;
    goto end_match_126;
next_133:;
end_match_126:;
    return match_24;
}

struct String spaceToString_(struct Space_ space_6) {
    struct StringList* call_86 = go_9(space_6, NULL);
    struct StringList* call_87 = listRev_1(call_86);
    struct String call_88 = strConcat_(call_87);
    return call_88;
}

struct Space_ fun_18(void* env_9, struct Ty_ arg_19) {
    struct Space_ call_89 = go_10(arg_19);
    return call_89;
}

struct Space_ fun_19(void* env_10, int arg_20) {
    struct Space_ arg_21 = (*(((struct Space_Tuple1*)env_10))).t0;
    struct Space_ call_90 = thunk_2(arg_21, 0);
    return call_90;
}

struct Space_ thunk_2(struct Space_ itemSpace_, int arg_92) {
    struct Space_ call_91 = spaceCtor_((struct String){.str = "nil", .len = 3}, NULL);
    struct Space_Tuple1 tuple_8;
    tuple_8.t0 = itemSpace_;
    void* box_12 = (void*)milone_mem_alloc(1, sizeof(struct Space_Tuple1));
    (*(((struct Space_Tuple1*)box_12))) = tuple_8;
    void* env_28 = box_12;
    struct UnitSpace_Fun1 fun_37 = (struct UnitSpace_Fun1){.fun = fun_19, .env = env_28};
    struct Space_ call_92 = spaceRef_((struct String){.str = "list", .len = 4}, fun_37);
    struct Space_List* list_17 = (struct Space_List*)milone_mem_alloc(1, sizeof(struct Space_List));
    list_17->head = call_92;
    list_17->tail = NULL;
    struct Space_List* list_16 = (struct Space_List*)milone_mem_alloc(1, sizeof(struct Space_List));
    list_16->head = itemSpace_;
    list_16->tail = list_17;
    struct Space_ call_93 = spaceCtor_((struct String){.str = "cons", .len = 4}, list_16);
    struct Space_List* list_15 = (struct Space_List*)milone_mem_alloc(1, sizeof(struct Space_List));
    list_15->head = call_93;
    list_15->tail = NULL;
    struct Space_List* list_14 = (struct Space_List*)milone_mem_alloc(1, sizeof(struct Space_List));
    list_14->head = call_91;
    list_14->tail = list_15;
    struct Space_ call_94 = spaceUnion_(list_14);
    return call_94;
}

struct Space_ fun_20(void* env_11, int arg_22) {
    struct Space_ arg_23 = (*(((struct Space_Tuple1*)env_11))).t0;
    struct Space_ call_95 = thunk_2(arg_23, 0);
    return call_95;
}

struct Space_ go_10(struct Ty_ ty_1) {
    struct Space_ match_25;
    if ((ty_1.tag != Int_)) goto next_135;
    match_25 = spaceFull_;
    goto end_match_134;
next_135:;
    if ((ty_1.tag != Tuple_)) goto next_136;
    struct Ty_List* itemTys_ = (*(((struct Ty_List**)ty_1.Tuple_)));
    void* box_13 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_13))) = 0;
    void* env_29 = box_13;
    struct Ty_Space_Fun1 fun_38 = (struct Ty_Space_Fun1){.fun = fun_18, .env = env_29};
    struct Space_List* call_96 = listMap_4(fun_38, itemTys_);
    struct Space_ call_97 = spaceCtor_((struct String){.str = "tuple", .len = 5}, call_96);
    match_25 = call_97;
    goto end_match_134;
next_136:;
    if ((ty_1.tag != List_)) goto next_137;
    struct Ty_ itemTy_ = (*(((struct Ty_*)ty_1.List_)));
    struct Space_ call_98 = go_10(itemTy_);
    struct Space_ itemSpace_ = call_98;
    struct Space_Tuple1 tuple_9;
    tuple_9.t0 = itemSpace_;
    void* box_14 = (void*)milone_mem_alloc(1, sizeof(struct Space_Tuple1));
    (*(((struct Space_Tuple1*)box_14))) = tuple_9;
    void* env_30 = box_14;
    struct UnitSpace_Fun1 fun_39 = (struct UnitSpace_Fun1){.fun = fun_20, .env = env_30};
    struct Space_ call_99 = spaceRef_((struct String){.str = "list", .len = 4}, fun_39);
    match_25 = call_99;
    goto end_match_134;
next_137:;
    exit(1);
end_match_134:;
    return match_25;
}

struct Space_ tyToSpace_(struct Ty_ ty_) {
    struct Space_ call_100 = go_10(ty_);
    return call_100;
}

struct Space_ fun_21(void* env_12, struct Pat_ arg_24) {
    struct Space_ call_101 = go_11(arg_24);
    return call_101;
}

struct Pat_Pat_Tuple2 {
    struct Pat_ t0;
    struct Pat_ t1;
};

struct Space_ go_11(struct Pat_ pat_1) {
    struct Space_ match_26;
    if ((pat_1.tag != Discard_)) goto next_139;
    match_26 = spaceFull_;
    goto end_match_138;
next_139:;
    if ((pat_1.tag != IntLit_)) goto next_140;
    match_26 = spaceEmpty_;
    goto end_match_138;
next_140:;
    if ((pat_1.tag != TupleLit_)) goto next_141;
    struct Pat_List* itemPats_ = (*(((struct Pat_List**)pat_1.TupleLit_)));
    void* box_15 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_15))) = 0;
    void* env_31 = box_15;
    struct Pat_Space_Fun1 fun_40 = (struct Pat_Space_Fun1){.fun = fun_21, .env = env_31};
    struct Space_List* call_102 = listMap_3(fun_40, itemPats_);
    struct Space_ call_103 = spaceCtor_((struct String){.str = "tuple", .len = 5}, call_102);
    match_26 = call_103;
    goto end_match_138;
next_141:;
    if ((pat_1.tag != Nil_)) goto next_142;
    struct Space_ call_104 = spaceCtor_((struct String){.str = "nil", .len = 3}, NULL);
    match_26 = call_104;
    goto end_match_138;
next_142:;
    if ((pat_1.tag != Cons_)) goto next_143;
    struct Pat_ headPat_ = (*(((struct Pat_Pat_Tuple2*)pat_1.Cons_))).t0;
    struct Pat_ tailPat_ = (*(((struct Pat_Pat_Tuple2*)pat_1.Cons_))).t1;
    struct Space_ call_105 = go_11(headPat_);
    struct Space_ call_106 = go_11(tailPat_);
    struct Space_List* list_19 = (struct Space_List*)milone_mem_alloc(1, sizeof(struct Space_List));
    list_19->head = call_106;
    list_19->tail = NULL;
    struct Space_List* list_18 = (struct Space_List*)milone_mem_alloc(1, sizeof(struct Space_List));
    list_18->head = call_105;
    list_18->tail = list_19;
    struct Space_ call_107 = spaceCtor_((struct String){.str = "cons", .len = 4}, list_18);
    match_26 = call_107;
    goto end_match_138;
next_143:;
    struct Space_ call_108 = failwith_1((struct String){.str = "NEVER: suppress warning", .len = 23});
    match_26 = call_108;
    goto end_match_138;
next_144:;
end_match_138:;
    return match_26;
}

struct Space_ patToSpace_(struct Pat_ pat_) {
    struct Space_ call_109 = go_11(pat_);
    return call_109;
}

struct Space_ fun_22(void* env_13, struct Pat_ arg_25) {
    struct Space_ call_110 = patToSpace_(arg_25);
    return call_110;
}

struct Space_ patsToSpace_(struct Pat_List* pats_) {
    void* box_16 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_16))) = 0;
    void* env_32 = box_16;
    struct Pat_Space_Fun1 fun_41 = (struct Pat_Space_Fun1){.fun = fun_22, .env = env_32};
    struct Space_List* call_111 = listMap_3(fun_41, pats_);
    struct Space_ call_112 = spaceUnion_(call_111);
    return call_112;
}

struct Space_ fun_6(int arg_93) {
    return spaceFull_;
}

struct Space_ fun_23(void* env_14, int arg_26) {
    struct Space_ call_113 = fun_6(0);
    return call_113;
}

int testSpaceIsEmpty_(int arg_94) {
    int call_114 = spaceIsEmpty_(spaceEmpty_);
    milone_assert(call_114, 455, 2);
    int call_115 = 0;
    struct Space_List* list_22 = (struct Space_List*)milone_mem_alloc(1, sizeof(struct Space_List));
    list_22->head = spaceEmpty_;
    list_22->tail = NULL;
    struct Space_ call_116 = spaceUnion_(list_22);
    struct Space_List* list_21 = (struct Space_List*)milone_mem_alloc(1, sizeof(struct Space_List));
    list_21->head = call_116;
    list_21->tail = NULL;
    struct Space_List* list_20 = (struct Space_List*)milone_mem_alloc(1, sizeof(struct Space_List));
    list_20->head = spaceEmpty_;
    list_20->tail = list_21;
    struct Space_ call_117 = spaceUnion_(list_20);
    int call_118 = spaceIsEmpty_(call_117);
    milone_assert(call_118, 456, 2);
    int call_119 = 0;
    int call_120 = spaceIsEmpty_(spaceFull_);
    milone_assert((!(call_120)), 458, 2);
    int call_121 = 0;
    void* box_17 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_17))) = 0;
    void* env_33 = box_17;
    struct UnitSpace_Fun1 fun_42 = (struct UnitSpace_Fun1){.fun = fun_23, .env = env_33};
    struct Space_ call_122 = spaceRef_((struct String){.str = "ref", .len = 3}, fun_42);
    int call_123 = spaceIsEmpty_(call_122);
    milone_assert((!(call_123)), 459, 2);
    int call_124 = 0;
    struct Space_List* list_24 = (struct Space_List*)milone_mem_alloc(1, sizeof(struct Space_List));
    list_24->head = spaceFull_;
    list_24->tail = NULL;
    struct Space_List* list_23 = (struct Space_List*)milone_mem_alloc(1, sizeof(struct Space_List));
    list_23->head = spaceEmpty_;
    list_23->tail = list_24;
    struct Space_ call_125 = spaceUnion_(list_23);
    int call_126 = spaceIsEmpty_(call_125);
    milone_assert((!(call_126)), 460, 2);
    int call_127 = 0;
    struct Space_ call_128 = spaceCtor_((struct String){.str = "tuple", .len = 5}, NULL);
    int call_129 = spaceIsEmpty_(call_128);
    milone_assert((!(call_129)), 462, 2);
    int call_130 = 0;
    struct Space_List* list_27 = (struct Space_List*)milone_mem_alloc(1, sizeof(struct Space_List));
    list_27->head = spaceFull_;
    list_27->tail = NULL;
    struct Space_List* list_26 = (struct Space_List*)milone_mem_alloc(1, sizeof(struct Space_List));
    list_26->head = spaceEmpty_;
    list_26->tail = list_27;
    struct Space_List* list_25 = (struct Space_List*)milone_mem_alloc(1, sizeof(struct Space_List));
    list_25->head = spaceFull_;
    list_25->tail = list_26;
    struct Space_ call_131 = spaceCtor_((struct String){.str = "tuple", .len = 5}, list_25);
    int call_132 = spaceIsEmpty_(call_131);
    milone_assert(call_132, 463, 2);
    int call_133 = 0;
    void* box_18 = (void*)milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_18))) = (struct Ty_){.tag = Int_};
    struct Ty_ variant_3 = (struct Ty_){.tag = List_, .List_ = box_18};
    struct Space_ call_134 = tyToSpace_(variant_3);
    int call_135 = spaceIsEmpty_(call_134);
    milone_assert((!(call_135)), 465, 2);
    int call_136 = 0;
    void* box_19 = (void*)milone_mem_alloc(1, sizeof(struct Ty_List*));
    (*(((struct Ty_List**)box_19))) = NULL;
    struct Ty_ variant_4 = (struct Ty_){.tag = Tuple_, .Tuple_ = box_19};
    void* box_20 = (void*)milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_20))) = variant_4;
    struct Ty_ variant_5 = (struct Ty_){.tag = List_, .List_ = box_20};
    struct Space_ call_137 = tyToSpace_(variant_5);
    int call_138 = spaceIsEmpty_(call_137);
    milone_assert((!(call_138)), 466, 2);
    int call_139 = 0;
    return 0;
}

int fun_24(void* env_15, int arg_27) {
    int call_140 = id_1(arg_27);
    return call_140;
}

int fun_7(struct StringSpace_Tuple2 arg_95) {
    struct String expected_ = arg_95.t0;
    struct Space_ space_10 = arg_95.t1;
    struct String call_141 = spaceToString_(space_10);
    struct String actual_ = call_141;
    int if_6;
    if ((str_cmp(actual_, expected_) == 0)) {
        goto then_146;
    } else {
        goto else_147;
    }
then_146:;
    if_6 = 1;
    goto if_next_145;
else_147:;
    printf("%s: NG (%s)\n", expected_.str, actual_.str);
    int call_142 = 0;
    if_6 = 0;
    goto if_next_145;
if_next_145:;
    return if_6;
}

int fun_25(void* env_16, struct StringSpace_Tuple2 arg_28) {
    int call_143 = fun_7(arg_28);
    return call_143;
}

int testSpaceToString_(int arg_96) {
    struct StringSpace_Tuple2 tuple_10;
    tuple_10.t0 = (struct String){.str = "empty", .len = 5};
    tuple_10.t1 = spaceEmpty_;
    struct StringSpace_Tuple2 tuple_11;
    tuple_11.t0 = (struct String){.str = "full", .len = 4};
    tuple_11.t1 = spaceFull_;
    struct Space_ call_144 = spaceCtor_((struct String){.str = "nil", .len = 3}, NULL);
    struct StringSpace_Tuple2 tuple_12;
    tuple_12.t0 = (struct String){.str = "nil", .len = 3};
    tuple_12.t1 = call_144;
    struct Space_List* list_33 = (struct Space_List*)milone_mem_alloc(1, sizeof(struct Space_List));
    list_33->head = spaceFull_;
    list_33->tail = NULL;
    struct Space_List* list_32 = (struct Space_List*)milone_mem_alloc(1, sizeof(struct Space_List));
    list_32->head = spaceEmpty_;
    list_32->tail = list_33;
    struct Space_ call_145 = spaceCtor_((struct String){.str = "tuple", .len = 5}, list_32);
    struct StringSpace_Tuple2 tuple_13;
    tuple_13.t0 = (struct String){.str = "tuple(empty, full)", .len = 18};
    tuple_13.t1 = call_145;
    struct Space_ call_146 = tyToSpace_((struct Ty_){.tag = Int_});
    struct StringSpace_Tuple2 tuple_14;
    tuple_14.t0 = (struct String){.str = "full", .len = 4};
    tuple_14.t1 = call_146;
    void* box_21 = (void*)milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_21))) = (struct Ty_){.tag = Int_};
    struct Ty_ variant_6 = (struct Ty_){.tag = List_, .List_ = box_21};
    struct Space_ call_147 = tyToSpace_(variant_6);
    struct Space_ call_148 = spaceDecompose_(call_147);
    struct StringSpace_Tuple2 tuple_15;
    tuple_15.t0 = (struct String){.str = "+(nil, cons(full, list))", .len = 24};
    tuple_15.t1 = call_148;
    struct Pat_Pat_Tuple2 tuple_17;
    tuple_17.t0 = (struct Pat_){.tag = Discard_};
    tuple_17.t1 = (struct Pat_){.tag = Nil_};
    void* box_22 = (void*)milone_mem_alloc(1, sizeof(struct Pat_Pat_Tuple2));
    (*(((struct Pat_Pat_Tuple2*)box_22))) = tuple_17;
    struct Pat_ variant_7 = (struct Pat_){.tag = Cons_, .Cons_ = box_22};
    struct Space_ call_149 = patToSpace_(variant_7);
    struct StringSpace_Tuple2 tuple_16;
    tuple_16.t0 = (struct String){.str = "cons(full, nil)", .len = 15};
    tuple_16.t1 = call_149;
    struct StringSpace_Tuple2List* list_36 = (struct StringSpace_Tuple2List*)milone_mem_alloc(1, sizeof(struct StringSpace_Tuple2List));
    list_36->head = tuple_16;
    list_36->tail = NULL;
    struct StringSpace_Tuple2List* list_35 = (struct StringSpace_Tuple2List*)milone_mem_alloc(1, sizeof(struct StringSpace_Tuple2List));
    list_35->head = tuple_15;
    list_35->tail = list_36;
    struct StringSpace_Tuple2List* list_34 = (struct StringSpace_Tuple2List*)milone_mem_alloc(1, sizeof(struct StringSpace_Tuple2List));
    list_34->head = tuple_14;
    list_34->tail = list_35;
    struct StringSpace_Tuple2List* list_31 = (struct StringSpace_Tuple2List*)milone_mem_alloc(1, sizeof(struct StringSpace_Tuple2List));
    list_31->head = tuple_13;
    list_31->tail = list_34;
    struct StringSpace_Tuple2List* list_30 = (struct StringSpace_Tuple2List*)milone_mem_alloc(1, sizeof(struct StringSpace_Tuple2List));
    list_30->head = tuple_12;
    list_30->tail = list_31;
    struct StringSpace_Tuple2List* list_29 = (struct StringSpace_Tuple2List*)milone_mem_alloc(1, sizeof(struct StringSpace_Tuple2List));
    list_29->head = tuple_11;
    list_29->tail = list_30;
    struct StringSpace_Tuple2List* list_28 = (struct StringSpace_Tuple2List*)milone_mem_alloc(1, sizeof(struct StringSpace_Tuple2List));
    list_28->head = tuple_10;
    list_28->tail = list_29;
    struct StringSpace_Tuple2List* cases_ = list_28;
    void* box_23 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_23))) = 0;
    void* env_34 = box_23;
    struct BoolBoolFun1 fun_43 = (struct BoolBoolFun1){.fun = fun_24, .env = env_34};
    void* box_24 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_24))) = 0;
    void* env_35 = box_24;
    struct StringSpace_Tuple2BoolFun1 fun_44 = (struct StringSpace_Tuple2BoolFun1){.fun = fun_25, .env = env_35};
    struct BoolList* call_150 = listMap_2(fun_44, cases_);
    int call_151 = listForAll_1(fun_43, call_150);
    int ok_ = call_151;
    milone_assert(ok_, 497, 2);
    int call_152 = 0;
    return 0;
}

int fun_26(void* env_17, int arg_29) {
    int call_153 = id_1(arg_29);
    return call_153;
}

struct BoolStringTuple2 {
    int t0;
    struct String t1;
};

struct Covering_Covering_Tuple2 {
    struct Covering_ t0;
    struct Covering_ t1;
};

int fun_8(struct StringTy_Pat_ListCovering_Tuple4 arg_97) {
    struct String name_ = arg_97.t0;
    struct Ty_ ty_2 = arg_97.t1;
    struct Pat_List* pats_1 = arg_97.t2;
    struct Covering_ covering_ = arg_97.t3;
    struct Space_ call_154 = tyToSpace_(ty_2);
    struct Space_ tySpace_ = call_154;
    struct Space_ call_155 = patsToSpace_(pats_1);
    struct Space_ patSpace_ = call_155;
    int call_156 = spaceCovers_(tySpace_, patSpace_);
    struct Covering_ if_7;
    if (call_156) {
        goto then_149;
    } else {
        goto else_150;
    }
then_149:;
    if_7 = (struct Covering_){.tag = Covering_};
    goto if_next_148;
else_150:;
    if_7 = (struct Covering_){.tag = Open_};
    goto if_next_148;
if_next_148:;
    struct Covering_ actual_1 = if_7;
    struct BoolStringTuple2 match_27;
    struct Covering_Covering_Tuple2 tuple_18;
    tuple_18.t0 = covering_;
    tuple_18.t1 = actual_1;
    if ((tuple_18.t0.tag != Covering_)) goto next_153;
    if ((tuple_18.t1.tag != Covering_)) goto next_153;
    goto match_body_152;
next_153:;
    if ((tuple_18.t0.tag != Open_)) goto next_154;
    if ((tuple_18.t1.tag != Open_)) goto next_154;
    goto match_body_152;
match_body_152:;
    struct BoolStringTuple2 tuple_19;
    tuple_19.t0 = 1;
    tuple_19.t1 = (struct String){.str = "OK", .len = 2};
    match_27 = tuple_19;
    goto end_match_151;
next_154:;
    if ((tuple_18.t0.tag != Covering_)) goto next_155;
    if ((tuple_18.t1.tag != Open_)) goto next_155;
    struct BoolStringTuple2 tuple_20;
    tuple_20.t0 = 0;
    tuple_20.t1 = (struct String){.str = "NG. Expected covering but open", .len = 30};
    match_27 = tuple_20;
    goto end_match_151;
next_155:;
    struct BoolStringTuple2 tuple_21;
    tuple_21.t0 = 0;
    tuple_21.t1 = (struct String){.str = "NG. Expected open but covering", .len = 30};
    match_27 = tuple_21;
    goto end_match_151;
next_156:;
end_match_151:;
    int ok_2 = match_27.t0;
    struct String msg_1 = match_27.t1;
    printf("%s: %s\n", name_.str, msg_1.str);
    int call_157 = 0;
    int if_8;
    if ((!(ok_2))) {
        goto then_158;
    } else {
        goto else_159;
    }
then_158:;
    struct String call_158 = spaceToString_(tySpace_);
    printf("  ty: %s\n", call_158.str);
    int call_159 = 0;
    struct String call_160 = spaceToString_(patSpace_);
    printf("  pats: %s\n", call_160.str);
    int call_161 = 0;
    if_8 = 0;
    goto if_next_157;
else_159:;
    if_8 = 0;
    goto if_next_157;
if_next_157:;
    return ok_2;
}

int fun_27(void* env_18, struct StringTy_Pat_ListCovering_Tuple4 arg_30) {
    int call_162 = fun_8(arg_30);
    return call_162;
}

// static spaceFull_;

// static spaceEmpty_;

int main() {
    spaceFull_ = (struct Space_){.tag = Full_};
    void* box_25 = (void*)milone_mem_alloc(1, sizeof(struct Space_List*));
    (*(((struct Space_List**)box_25))) = NULL;
    struct Space_ variant_8 = (struct Space_){.tag = Union_, .Union_ = box_25};
    spaceEmpty_ = variant_8;
    int call_163 = testSpaceIsEmpty_(0);
    int call_164 = testSpaceToString_(0);
    struct Pat_Pat_Tuple2 tuple_22;
    tuple_22.t0 = (struct Pat_){.tag = Discard_};
    tuple_22.t1 = (struct Pat_){.tag = Discard_};
    void* box_26 = (void*)milone_mem_alloc(1, sizeof(struct Pat_Pat_Tuple2));
    (*(((struct Pat_Pat_Tuple2*)box_26))) = tuple_22;
    struct Pat_ variant_9 = (struct Pat_){.tag = Cons_, .Cons_ = box_26};
    struct Pat_ anyConsPat_ = variant_9;
    void* box_27 = (void*)milone_mem_alloc(1, sizeof(struct Ty_List*));
    (*(((struct Ty_List**)box_27))) = NULL;
    struct Ty_ variant_10 = (struct Ty_){.tag = Tuple_, .Tuple_ = box_27};
    void* box_28 = (void*)milone_mem_alloc(1, sizeof(struct Pat_List*));
    (*(((struct Pat_List**)box_28))) = NULL;
    struct Pat_ variant_11 = (struct Pat_){.tag = TupleLit_, .TupleLit_ = box_28};
    struct Pat_List* list_38 = (struct Pat_List*)milone_mem_alloc(1, sizeof(struct Pat_List));
    list_38->head = variant_11;
    list_38->tail = NULL;
    struct StringTy_Pat_ListCovering_Tuple4 tuple_23;
    tuple_23.t0 = (struct String){.str = "unit with ()", .len = 12};
    tuple_23.t1 = variant_10;
    tuple_23.t2 = list_38;
    tuple_23.t3 = (struct Covering_){.tag = Covering_};
    void* box_29 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_29))) = 1;
    struct Pat_ variant_12 = (struct Pat_){.tag = IntLit_, .IntLit_ = box_29};
    struct Pat_List* list_40 = (struct Pat_List*)milone_mem_alloc(1, sizeof(struct Pat_List));
    list_40->head = variant_12;
    list_40->tail = NULL;
    struct StringTy_Pat_ListCovering_Tuple4 tuple_24;
    tuple_24.t0 = (struct String){.str = "int with literal pats", .len = 21};
    tuple_24.t1 = (struct Ty_){.tag = Int_};
    tuple_24.t2 = list_40;
    tuple_24.t3 = (struct Covering_){.tag = Open_};
    struct Pat_List* list_42 = (struct Pat_List*)milone_mem_alloc(1, sizeof(struct Pat_List));
    list_42->head = (struct Pat_){.tag = Discard_};
    list_42->tail = NULL;
    struct StringTy_Pat_ListCovering_Tuple4 tuple_25;
    tuple_25.t0 = (struct String){.str = "int with _", .len = 10};
    tuple_25.t1 = (struct Ty_){.tag = Int_};
    tuple_25.t2 = list_42;
    tuple_25.t3 = (struct Covering_){.tag = Covering_};
    void* box_30 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_30))) = 1;
    struct Pat_ variant_13 = (struct Pat_){.tag = IntLit_, .IntLit_ = box_30};
    struct Pat_List* list_45 = (struct Pat_List*)milone_mem_alloc(1, sizeof(struct Pat_List));
    list_45->head = (struct Pat_){.tag = Discard_};
    list_45->tail = NULL;
    struct Pat_List* list_44 = (struct Pat_List*)milone_mem_alloc(1, sizeof(struct Pat_List));
    list_44->head = variant_13;
    list_44->tail = list_45;
    struct StringTy_Pat_ListCovering_Tuple4 tuple_26;
    tuple_26.t0 = (struct String){.str = "int with 1|_", .len = 12};
    tuple_26.t1 = (struct Ty_){.tag = Int_};
    tuple_26.t2 = list_44;
    tuple_26.t3 = (struct Covering_){.tag = Covering_};
    void* box_31 = (void*)milone_mem_alloc(1, sizeof(struct Ty_List*));
    (*(((struct Ty_List**)box_31))) = NULL;
    struct Ty_ variant_14 = (struct Ty_){.tag = Tuple_, .Tuple_ = box_31};
    struct Ty_List* list_48 = (struct Ty_List*)milone_mem_alloc(1, sizeof(struct Ty_List));
    list_48->head = variant_14;
    list_48->tail = NULL;
    struct Ty_List* list_47 = (struct Ty_List*)milone_mem_alloc(1, sizeof(struct Ty_List));
    list_47->head = (struct Ty_){.tag = Int_};
    list_47->tail = list_48;
    void* box_32 = (void*)milone_mem_alloc(1, sizeof(struct Ty_List*));
    (*(((struct Ty_List**)box_32))) = list_47;
    struct Ty_ variant_15 = (struct Ty_){.tag = Tuple_, .Tuple_ = box_32};
    void* box_33 = (void*)milone_mem_alloc(1, sizeof(struct Pat_List*));
    (*(((struct Pat_List**)box_33))) = NULL;
    struct Pat_ variant_16 = (struct Pat_){.tag = TupleLit_, .TupleLit_ = box_33};
    struct Pat_List* list_51 = (struct Pat_List*)milone_mem_alloc(1, sizeof(struct Pat_List));
    list_51->head = variant_16;
    list_51->tail = NULL;
    struct Pat_List* list_50 = (struct Pat_List*)milone_mem_alloc(1, sizeof(struct Pat_List));
    list_50->head = (struct Pat_){.tag = Discard_};
    list_50->tail = list_51;
    void* box_34 = (void*)milone_mem_alloc(1, sizeof(struct Pat_List*));
    (*(((struct Pat_List**)box_34))) = list_50;
    struct Pat_ variant_17 = (struct Pat_){.tag = TupleLit_, .TupleLit_ = box_34};
    struct Pat_List* list_49 = (struct Pat_List*)milone_mem_alloc(1, sizeof(struct Pat_List));
    list_49->head = variant_17;
    list_49->tail = NULL;
    struct StringTy_Pat_ListCovering_Tuple4 tuple_27;
    tuple_27.t0 = (struct String){.str = "int * unit with _, ()", .len = 21};
    tuple_27.t1 = variant_15;
    tuple_27.t2 = list_49;
    tuple_27.t3 = (struct Covering_){.tag = Covering_};
    struct Ty_List* list_54 = (struct Ty_List*)milone_mem_alloc(1, sizeof(struct Ty_List));
    list_54->head = (struct Ty_){.tag = Int_};
    list_54->tail = NULL;
    struct Ty_List* list_53 = (struct Ty_List*)milone_mem_alloc(1, sizeof(struct Ty_List));
    list_53->head = (struct Ty_){.tag = Int_};
    list_53->tail = list_54;
    void* box_35 = (void*)milone_mem_alloc(1, sizeof(struct Ty_List*));
    (*(((struct Ty_List**)box_35))) = list_53;
    struct Ty_ variant_18 = (struct Ty_){.tag = Tuple_, .Tuple_ = box_35};
    void* box_36 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_36))) = 1;
    struct Pat_ variant_19 = (struct Pat_){.tag = IntLit_, .IntLit_ = box_36};
    struct Pat_List* list_57 = (struct Pat_List*)milone_mem_alloc(1, sizeof(struct Pat_List));
    list_57->head = (struct Pat_){.tag = Discard_};
    list_57->tail = NULL;
    struct Pat_List* list_56 = (struct Pat_List*)milone_mem_alloc(1, sizeof(struct Pat_List));
    list_56->head = variant_19;
    list_56->tail = list_57;
    void* box_37 = (void*)milone_mem_alloc(1, sizeof(struct Pat_List*));
    (*(((struct Pat_List**)box_37))) = list_56;
    struct Pat_ variant_20 = (struct Pat_){.tag = TupleLit_, .TupleLit_ = box_37};
    void* box_38 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_38))) = 1;
    struct Pat_ variant_21 = (struct Pat_){.tag = IntLit_, .IntLit_ = box_38};
    struct Pat_List* list_60 = (struct Pat_List*)milone_mem_alloc(1, sizeof(struct Pat_List));
    list_60->head = variant_21;
    list_60->tail = NULL;
    struct Pat_List* list_59 = (struct Pat_List*)milone_mem_alloc(1, sizeof(struct Pat_List));
    list_59->head = (struct Pat_){.tag = Discard_};
    list_59->tail = list_60;
    void* box_39 = (void*)milone_mem_alloc(1, sizeof(struct Pat_List*));
    (*(((struct Pat_List**)box_39))) = list_59;
    struct Pat_ variant_22 = (struct Pat_){.tag = TupleLit_, .TupleLit_ = box_39};
    struct Pat_List* list_58 = (struct Pat_List*)milone_mem_alloc(1, sizeof(struct Pat_List));
    list_58->head = variant_22;
    list_58->tail = NULL;
    struct Pat_List* list_55 = (struct Pat_List*)milone_mem_alloc(1, sizeof(struct Pat_List));
    list_55->head = variant_20;
    list_55->tail = list_58;
    struct StringTy_Pat_ListCovering_Tuple4 tuple_28;
    tuple_28.t0 = (struct String){.str = "int * int with 1, _ | _, 1", .len = 26};
    tuple_28.t1 = variant_18;
    tuple_28.t2 = list_55;
    tuple_28.t3 = (struct Covering_){.tag = Open_};
    void* box_40 = (void*)milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_40))) = (struct Ty_){.tag = Int_};
    struct Ty_ variant_23 = (struct Ty_){.tag = List_, .List_ = box_40};
    struct Pat_List* list_62 = (struct Pat_List*)milone_mem_alloc(1, sizeof(struct Pat_List));
    list_62->head = (struct Pat_){.tag = Nil_};
    list_62->tail = NULL;
    struct StringTy_Pat_ListCovering_Tuple4 tuple_29;
    tuple_29.t0 = (struct String){.str = "int list with []", .len = 16};
    tuple_29.t1 = variant_23;
    tuple_29.t2 = list_62;
    tuple_29.t3 = (struct Covering_){.tag = Open_};
    void* box_41 = (void*)milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_41))) = (struct Ty_){.tag = Int_};
    struct Ty_ variant_24 = (struct Ty_){.tag = List_, .List_ = box_41};
    struct Pat_List* list_64 = (struct Pat_List*)milone_mem_alloc(1, sizeof(struct Pat_List));
    list_64->head = anyConsPat_;
    list_64->tail = NULL;
    struct StringTy_Pat_ListCovering_Tuple4 tuple_30;
    tuple_30.t0 = (struct String){.str = "int list with _::_", .len = 18};
    tuple_30.t1 = variant_24;
    tuple_30.t2 = list_64;
    tuple_30.t3 = (struct Covering_){.tag = Open_};
    void* box_42 = (void*)milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_42))) = (struct Ty_){.tag = Int_};
    struct Ty_ variant_25 = (struct Ty_){.tag = List_, .List_ = box_42};
    struct Pat_List* list_67 = (struct Pat_List*)milone_mem_alloc(1, sizeof(struct Pat_List));
    list_67->head = anyConsPat_;
    list_67->tail = NULL;
    struct Pat_List* list_66 = (struct Pat_List*)milone_mem_alloc(1, sizeof(struct Pat_List));
    list_66->head = (struct Pat_){.tag = Nil_};
    list_66->tail = list_67;
    struct StringTy_Pat_ListCovering_Tuple4 tuple_31;
    tuple_31.t0 = (struct String){.str = "int list with [] | _::_", .len = 23};
    tuple_31.t1 = variant_25;
    tuple_31.t2 = list_66;
    tuple_31.t3 = (struct Covering_){.tag = Covering_};
    void* box_43 = (void*)milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_43))) = (struct Ty_){.tag = Int_};
    struct Ty_ variant_26 = (struct Ty_){.tag = List_, .List_ = box_43};
    struct Pat_Pat_Tuple2 tuple_33;
    tuple_33.t0 = (struct Pat_){.tag = Discard_};
    tuple_33.t1 = (struct Pat_){.tag = Nil_};
    void* box_44 = (void*)milone_mem_alloc(1, sizeof(struct Pat_Pat_Tuple2));
    (*(((struct Pat_Pat_Tuple2*)box_44))) = tuple_33;
    struct Pat_ variant_27 = (struct Pat_){.tag = Cons_, .Cons_ = box_44};
    struct Pat_Pat_Tuple2 tuple_34;
    tuple_34.t0 = (struct Pat_){.tag = Discard_};
    tuple_34.t1 = anyConsPat_;
    void* box_45 = (void*)milone_mem_alloc(1, sizeof(struct Pat_Pat_Tuple2));
    (*(((struct Pat_Pat_Tuple2*)box_45))) = tuple_34;
    struct Pat_ variant_28 = (struct Pat_){.tag = Cons_, .Cons_ = box_45};
    struct Pat_List* list_71 = (struct Pat_List*)milone_mem_alloc(1, sizeof(struct Pat_List));
    list_71->head = variant_28;
    list_71->tail = NULL;
    struct Pat_List* list_70 = (struct Pat_List*)milone_mem_alloc(1, sizeof(struct Pat_List));
    list_70->head = variant_27;
    list_70->tail = list_71;
    struct Pat_List* list_69 = (struct Pat_List*)milone_mem_alloc(1, sizeof(struct Pat_List));
    list_69->head = (struct Pat_){.tag = Nil_};
    list_69->tail = list_70;
    struct StringTy_Pat_ListCovering_Tuple4 tuple_32;
    tuple_32.t0 = (struct String){.str = "int list with [] | [_] | _::_::_", .len = 32};
    tuple_32.t1 = variant_26;
    tuple_32.t2 = list_69;
    tuple_32.t3 = (struct Covering_){.tag = Covering_};
    void* box_46 = (void*)milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_46))) = (struct Ty_){.tag = Int_};
    struct Ty_ variant_29 = (struct Ty_){.tag = List_, .List_ = box_46};
    void* box_47 = (void*)milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_47))) = variant_29;
    struct Ty_ variant_30 = (struct Ty_){.tag = List_, .List_ = box_47};
    struct Pat_Pat_Tuple2 tuple_36;
    tuple_36.t0 = (struct Pat_){.tag = Nil_};
    tuple_36.t1 = (struct Pat_){.tag = Nil_};
    void* box_48 = (void*)milone_mem_alloc(1, sizeof(struct Pat_Pat_Tuple2));
    (*(((struct Pat_Pat_Tuple2*)box_48))) = tuple_36;
    struct Pat_ variant_31 = (struct Pat_){.tag = Cons_, .Cons_ = box_48};
    struct Pat_Pat_Tuple2 tuple_37;
    tuple_37.t0 = anyConsPat_;
    tuple_37.t1 = (struct Pat_){.tag = Discard_};
    void* box_49 = (void*)milone_mem_alloc(1, sizeof(struct Pat_Pat_Tuple2));
    (*(((struct Pat_Pat_Tuple2*)box_49))) = tuple_37;
    struct Pat_ variant_32 = (struct Pat_){.tag = Cons_, .Cons_ = box_49};
    struct Pat_Pat_Tuple2 tuple_38;
    tuple_38.t0 = (struct Pat_){.tag = Discard_};
    tuple_38.t1 = anyConsPat_;
    void* box_50 = (void*)milone_mem_alloc(1, sizeof(struct Pat_Pat_Tuple2));
    (*(((struct Pat_Pat_Tuple2*)box_50))) = tuple_38;
    struct Pat_ variant_33 = (struct Pat_){.tag = Cons_, .Cons_ = box_50};
    struct Pat_List* list_76 = (struct Pat_List*)milone_mem_alloc(1, sizeof(struct Pat_List));
    list_76->head = variant_33;
    list_76->tail = NULL;
    struct Pat_List* list_75 = (struct Pat_List*)milone_mem_alloc(1, sizeof(struct Pat_List));
    list_75->head = variant_32;
    list_75->tail = list_76;
    struct Pat_List* list_74 = (struct Pat_List*)milone_mem_alloc(1, sizeof(struct Pat_List));
    list_74->head = variant_31;
    list_74->tail = list_75;
    struct Pat_List* list_73 = (struct Pat_List*)milone_mem_alloc(1, sizeof(struct Pat_List));
    list_73->head = (struct Pat_){.tag = Nil_};
    list_73->tail = list_74;
    struct StringTy_Pat_ListCovering_Tuple4 tuple_35;
    tuple_35.t0 = (struct String){.str = "int list list with [] | [[]] | [_::_] | _::_::_", .len = 47};
    tuple_35.t1 = variant_30;
    tuple_35.t2 = list_73;
    tuple_35.t3 = (struct Covering_){.tag = Covering_};
    void* box_51 = (void*)milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_51))) = (struct Ty_){.tag = Int_};
    struct Ty_ variant_34 = (struct Ty_){.tag = List_, .List_ = box_51};
    void* box_52 = (void*)milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_52))) = (struct Ty_){.tag = Int_};
    struct Ty_ variant_35 = (struct Ty_){.tag = List_, .List_ = box_52};
    struct Ty_List* list_79 = (struct Ty_List*)milone_mem_alloc(1, sizeof(struct Ty_List));
    list_79->head = variant_35;
    list_79->tail = NULL;
    struct Ty_List* list_78 = (struct Ty_List*)milone_mem_alloc(1, sizeof(struct Ty_List));
    list_78->head = variant_34;
    list_78->tail = list_79;
    void* box_53 = (void*)milone_mem_alloc(1, sizeof(struct Ty_List*));
    (*(((struct Ty_List**)box_53))) = list_78;
    struct Ty_ variant_36 = (struct Ty_){.tag = Tuple_, .Tuple_ = box_53};
    struct Pat_List* list_82 = (struct Pat_List*)milone_mem_alloc(1, sizeof(struct Pat_List));
    list_82->head = (struct Pat_){.tag = Nil_};
    list_82->tail = NULL;
    struct Pat_List* list_81 = (struct Pat_List*)milone_mem_alloc(1, sizeof(struct Pat_List));
    list_81->head = (struct Pat_){.tag = Nil_};
    list_81->tail = list_82;
    void* box_54 = (void*)milone_mem_alloc(1, sizeof(struct Pat_List*));
    (*(((struct Pat_List**)box_54))) = list_81;
    struct Pat_ variant_37 = (struct Pat_){.tag = TupleLit_, .TupleLit_ = box_54};
    struct Pat_List* list_85 = (struct Pat_List*)milone_mem_alloc(1, sizeof(struct Pat_List));
    list_85->head = (struct Pat_){.tag = Nil_};
    list_85->tail = NULL;
    struct Pat_List* list_84 = (struct Pat_List*)milone_mem_alloc(1, sizeof(struct Pat_List));
    list_84->head = anyConsPat_;
    list_84->tail = list_85;
    void* box_55 = (void*)milone_mem_alloc(1, sizeof(struct Pat_List*));
    (*(((struct Pat_List**)box_55))) = list_84;
    struct Pat_ variant_38 = (struct Pat_){.tag = TupleLit_, .TupleLit_ = box_55};
    struct Pat_List* list_88 = (struct Pat_List*)milone_mem_alloc(1, sizeof(struct Pat_List));
    list_88->head = anyConsPat_;
    list_88->tail = NULL;
    struct Pat_List* list_87 = (struct Pat_List*)milone_mem_alloc(1, sizeof(struct Pat_List));
    list_87->head = (struct Pat_){.tag = Nil_};
    list_87->tail = list_88;
    void* box_56 = (void*)milone_mem_alloc(1, sizeof(struct Pat_List*));
    (*(((struct Pat_List**)box_56))) = list_87;
    struct Pat_ variant_39 = (struct Pat_){.tag = TupleLit_, .TupleLit_ = box_56};
    struct Pat_List* list_91 = (struct Pat_List*)milone_mem_alloc(1, sizeof(struct Pat_List));
    list_91->head = anyConsPat_;
    list_91->tail = NULL;
    struct Pat_List* list_90 = (struct Pat_List*)milone_mem_alloc(1, sizeof(struct Pat_List));
    list_90->head = anyConsPat_;
    list_90->tail = list_91;
    void* box_57 = (void*)milone_mem_alloc(1, sizeof(struct Pat_List*));
    (*(((struct Pat_List**)box_57))) = list_90;
    struct Pat_ variant_40 = (struct Pat_){.tag = TupleLit_, .TupleLit_ = box_57};
    struct Pat_List* list_89 = (struct Pat_List*)milone_mem_alloc(1, sizeof(struct Pat_List));
    list_89->head = variant_40;
    list_89->tail = NULL;
    struct Pat_List* list_86 = (struct Pat_List*)milone_mem_alloc(1, sizeof(struct Pat_List));
    list_86->head = variant_39;
    list_86->tail = list_89;
    struct Pat_List* list_83 = (struct Pat_List*)milone_mem_alloc(1, sizeof(struct Pat_List));
    list_83->head = variant_38;
    list_83->tail = list_86;
    struct Pat_List* list_80 = (struct Pat_List*)milone_mem_alloc(1, sizeof(struct Pat_List));
    list_80->head = variant_37;
    list_80->tail = list_83;
    struct StringTy_Pat_ListCovering_Tuple4 tuple_39;
    tuple_39.t0 = (struct String){.str = "int list * int list with [], [] | [], _::_ | _::_, [] | _::_, _::_", .len = 66};
    tuple_39.t1 = variant_36;
    tuple_39.t2 = list_80;
    tuple_39.t3 = (struct Covering_){.tag = Covering_};
    struct StringTy_Pat_ListCovering_Tuple4List* list_77 = (struct StringTy_Pat_ListCovering_Tuple4List*)milone_mem_alloc(1, sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    list_77->head = tuple_39;
    list_77->tail = NULL;
    struct StringTy_Pat_ListCovering_Tuple4List* list_72 = (struct StringTy_Pat_ListCovering_Tuple4List*)milone_mem_alloc(1, sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    list_72->head = tuple_35;
    list_72->tail = list_77;
    struct StringTy_Pat_ListCovering_Tuple4List* list_68 = (struct StringTy_Pat_ListCovering_Tuple4List*)milone_mem_alloc(1, sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    list_68->head = tuple_32;
    list_68->tail = list_72;
    struct StringTy_Pat_ListCovering_Tuple4List* list_65 = (struct StringTy_Pat_ListCovering_Tuple4List*)milone_mem_alloc(1, sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    list_65->head = tuple_31;
    list_65->tail = list_68;
    struct StringTy_Pat_ListCovering_Tuple4List* list_63 = (struct StringTy_Pat_ListCovering_Tuple4List*)milone_mem_alloc(1, sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    list_63->head = tuple_30;
    list_63->tail = list_65;
    struct StringTy_Pat_ListCovering_Tuple4List* list_61 = (struct StringTy_Pat_ListCovering_Tuple4List*)milone_mem_alloc(1, sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    list_61->head = tuple_29;
    list_61->tail = list_63;
    struct StringTy_Pat_ListCovering_Tuple4List* list_52 = (struct StringTy_Pat_ListCovering_Tuple4List*)milone_mem_alloc(1, sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    list_52->head = tuple_28;
    list_52->tail = list_61;
    struct StringTy_Pat_ListCovering_Tuple4List* list_46 = (struct StringTy_Pat_ListCovering_Tuple4List*)milone_mem_alloc(1, sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    list_46->head = tuple_27;
    list_46->tail = list_52;
    struct StringTy_Pat_ListCovering_Tuple4List* list_43 = (struct StringTy_Pat_ListCovering_Tuple4List*)milone_mem_alloc(1, sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    list_43->head = tuple_26;
    list_43->tail = list_46;
    struct StringTy_Pat_ListCovering_Tuple4List* list_41 = (struct StringTy_Pat_ListCovering_Tuple4List*)milone_mem_alloc(1, sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    list_41->head = tuple_25;
    list_41->tail = list_43;
    struct StringTy_Pat_ListCovering_Tuple4List* list_39 = (struct StringTy_Pat_ListCovering_Tuple4List*)milone_mem_alloc(1, sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    list_39->head = tuple_24;
    list_39->tail = list_41;
    struct StringTy_Pat_ListCovering_Tuple4List* list_37 = (struct StringTy_Pat_ListCovering_Tuple4List*)milone_mem_alloc(1, sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    list_37->head = tuple_23;
    list_37->tail = list_39;
    struct StringTy_Pat_ListCovering_Tuple4List* testCases_ = list_37;
    void* box_58 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_58))) = 0;
    void* env_36 = box_58;
    struct BoolBoolFun1 fun_45 = (struct BoolBoolFun1){.fun = fun_26, .env = env_36};
    void* box_59 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_59))) = 0;
    void* env_37 = box_59;
    struct StringTy_Pat_ListCovering_Tuple4BoolFun1 fun_46 = (struct StringTy_Pat_ListCovering_Tuple4BoolFun1){.fun = fun_27, .env = env_37};
    struct BoolList* call_165 = listMap_1(fun_46, testCases_);
    int call_166 = listForAll_1(fun_45, call_165);
    int ok_1 = call_166;
    int if_9;
    if (ok_1) {
        goto then_161;
    } else {
        goto else_162;
    }
then_161:;
    if_9 = 0;
    goto if_next_160;
else_162:;
    if_9 = 1;
    goto if_next_160;
if_next_160:;
    int exitCode_ = if_9;
    return exitCode_;
}
