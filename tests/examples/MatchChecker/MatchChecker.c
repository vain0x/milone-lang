#include "milone.h"

bool id_1(bool x_);

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

bool go_18(struct Space_BoolFun1 p_, struct Space_List* xs_11);

struct Space_Space_Tuple2BoolFun1;

bool go_17(struct Space_Space_Tuple2BoolFun1 p_, struct Space_Space_Tuple2List* xs_11);

struct BoolBoolFun1;

bool go_16(struct BoolBoolFun1 p_, struct BoolList* xs_11);

bool listForAll_3(struct Space_BoolFun1 p_, struct Space_List* xs_10);

bool listForAll_2(struct Space_Space_Tuple2BoolFun1 p_, struct Space_Space_Tuple2List* xs_10);

bool listForAll_1(struct BoolBoolFun1 p_, struct BoolList* xs_10);

bool go_15(struct Space_BoolFun1 p_1, struct Space_List* xs_14);

bool listExists_1(struct Space_BoolFun1 p_1, struct Space_List* xs_13);

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

bool fun_9(void* env_, struct Space_ arg_);

bool fun_10(void* env_1, struct Space_ arg_1);

bool spaceIsEmpty_(struct Space_ space_3);

struct Space_ spaceDecompose_(struct Space_ space_4);

bool fun_(struct Space_Space_Tuple2 arg_85);

bool fun_11(void* env_2, struct Space_Space_Tuple2 arg_2);

struct Space_ fun_2(int i_1, int j_, struct Space_Space_Tuple2 arg_86);

struct IntTuple1;

struct Space_ fun_12(void* env_3, int arg_3, struct Space_Space_Tuple2 arg_4);

struct Space_ fun_28(struct String tag_2, struct Space_List* firsts_, struct Space_List* seconds_, int i_1, struct Space_ arg_87);

struct StringSpace_ListSpace_ListTuple3;

struct Space_ fun_13(void* env_4, int arg_6, struct Space_ arg_7);

struct Space_ fun_14(void* env_5, struct Space_ arg_11, struct Space_ arg_12);

struct Space_ fun_3(struct Space_ second_, struct Space_ first_3);

struct Space_Tuple1;

struct Space_ fun_15(void* env_6, struct Space_ arg_13);

struct Space_ spaceExclude_(struct Space_ first_, struct Space_ second_);

bool spaceCovers_(struct Space_ other_, struct Space_ cover_);

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

bool fun_24(void* env_15, bool arg_27);

bool fun_7(struct StringSpace_Tuple2 arg_95);

bool fun_25(void* env_16, struct StringSpace_Tuple2 arg_28);

int testSpaceToString_(int arg_96);

bool fun_26(void* env_17, bool arg_29);

struct BoolStringTuple2;

struct Covering_Covering_Tuple2;

bool fun_8(struct StringTy_Pat_ListCovering_Tuple4 arg_97);

bool fun_27(void* env_18, struct StringTy_Pat_ListCovering_Tuple4 arg_30);

static struct Space_ spaceFull_;

static struct Space_ spaceEmpty_;

int main();

bool id_1(bool x_) {
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
    exit(1);
    return NULL;
}

struct StringList {
    struct String head;
    struct StringList* tail;
};

struct StringList* failwith_2(struct String msg_) {
    printf("ERROR %s\n", msg_.str);
    exit(1);
    return NULL;
}

struct Space_ failwith_1(struct String msg_) {
    printf("ERROR %s\n", msg_.str);
    exit(1);
    return ((struct Space_){});
}

struct StringList* cons_1(struct String head_, struct StringList* tail_) {
    struct StringList* list_ = milone_mem_alloc(1, sizeof(struct StringList));
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
    struct Space_List* list_1 = milone_mem_alloc(1, sizeof(struct Space_List));
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
    struct StringList* list_2 = milone_mem_alloc(1, sizeof(struct StringList));
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
    bool head;
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
    bool x_2 = xs_2->head;
    struct BoolList* xs_3 = xs_2->tail;
    struct BoolList* list_3 = milone_mem_alloc(1, sizeof(struct BoolList));
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
    struct Space_Space_Tuple2List* list_4 = milone_mem_alloc(1, sizeof(struct Space_Space_Tuple2List));
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
    struct Space_List* call_ = go_27(NULL, xs_1);
    return call_;
}

struct StringList* listRev_1(struct StringList* xs_1) {
    struct StringList* call_1 = go_26(NULL, xs_1);
    return call_1;
}

struct BoolList* listRev_4(struct BoolList* xs_1) {
    struct BoolList* call_2 = go_29(NULL, xs_1);
    return call_2;
}

struct Space_Space_Tuple2List* listRev_3(struct Space_Space_Tuple2List* xs_1) {
    struct Space_Space_Tuple2List* call_3 = go_28(NULL, xs_1);
    return call_3;
}

struct Space_Space_Fun1 {
    struct Space_(*fun)(void*, struct Space_);
    void* env;
};

struct Space_List* go_25(struct Space_Space_Fun1 f_, struct Space_List* acc_1, struct Space_List* xs_5) {
tailrec_17:;
    struct Space_List* match_4;
    if ((!((!(xs_5))))) goto next_19;
    struct Space_List* call_4 = listRev_2(acc_1);
    match_4 = call_4;
    goto end_match_18;
next_19:;
    if ((!(xs_5))) goto next_20;
    struct Space_ x_3 = xs_5->head;
    struct Space_List* xs_6 = xs_5->tail;
    struct Space_Space_Fun1 arg_39 = f_;
    struct Space_ app_ = f_.fun(f_.env, x_3);
    struct Space_List* list_5 = milone_mem_alloc(1, sizeof(struct Space_List));
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
    struct Space_List* call_5 = listRev_2(acc_1);
    match_5 = call_5;
    goto end_match_22;
next_23:;
    if ((!(xs_5))) goto next_24;
    struct Ty_ x_3 = xs_5->head;
    struct Ty_List* xs_6 = xs_5->tail;
    struct Ty_Space_Fun1 arg_42 = f_;
    struct Space_ app_1 = f_.fun(f_.env, x_3);
    struct Space_List* list_6 = milone_mem_alloc(1, sizeof(struct Space_List));
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
        int IntLit_;
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
    struct Space_List* call_6 = listRev_2(acc_1);
    match_6 = call_6;
    goto end_match_26;
next_27:;
    if ((!(xs_5))) goto next_28;
    struct Pat_ x_3 = xs_5->head;
    struct Pat_List* xs_6 = xs_5->tail;
    struct Pat_Space_Fun1 arg_45 = f_;
    struct Space_ app_2 = f_.fun(f_.env, x_3);
    struct Space_List* list_7 = milone_mem_alloc(1, sizeof(struct Space_List));
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
    bool(*fun)(void*, struct StringSpace_Tuple2);
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
    struct BoolList* call_7 = listRev_4(acc_1);
    match_7 = call_7;
    goto end_match_30;
next_31:;
    if ((!(xs_5))) goto next_32;
    struct StringSpace_Tuple2 x_3 = xs_5->head;
    struct StringSpace_Tuple2List* xs_6 = xs_5->tail;
    struct StringSpace_Tuple2BoolFun1 arg_48 = f_;
    bool app_3 = f_.fun(f_.env, x_3);
    struct BoolList* list_8 = milone_mem_alloc(1, sizeof(struct BoolList));
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
    bool(*fun)(void*, struct StringTy_Pat_ListCovering_Tuple4);
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
    struct BoolList* call_8 = listRev_4(acc_1);
    match_8 = call_8;
    goto end_match_34;
next_35:;
    if ((!(xs_5))) goto next_36;
    struct StringTy_Pat_ListCovering_Tuple4 x_3 = xs_5->head;
    struct StringTy_Pat_ListCovering_Tuple4List* xs_6 = xs_5->tail;
    struct StringTy_Pat_ListCovering_Tuple4BoolFun1 arg_51 = f_;
    bool app_4 = f_.fun(f_.env, x_3);
    struct BoolList* list_9 = milone_mem_alloc(1, sizeof(struct BoolList));
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
    struct Space_List* call_9 = go_25(f_, NULL, xs_4);
    return call_9;
}

struct Space_List* listMap_4(struct Ty_Space_Fun1 f_, struct Ty_List* xs_4) {
    struct Space_List* call_10 = go_24(f_, NULL, xs_4);
    return call_10;
}

struct Space_List* listMap_3(struct Pat_Space_Fun1 f_, struct Pat_List* xs_4) {
    struct Space_List* call_11 = go_23(f_, NULL, xs_4);
    return call_11;
}

struct BoolList* listMap_2(struct StringSpace_Tuple2BoolFun1 f_, struct StringSpace_Tuple2List* xs_4) {
    struct BoolList* call_12 = go_22(f_, NULL, xs_4);
    return call_12;
}

struct BoolList* listMap_1(struct StringTy_Pat_ListCovering_Tuple4BoolFun1 f_, struct StringTy_Pat_ListCovering_Tuple4List* xs_4) {
    struct BoolList* call_13 = go_21(f_, NULL, xs_4);
    return call_13;
}

struct IntSpace_Space_Tuple2Space_Fun2 {
    struct Space_(*fun)(void*, int, struct Space_Space_Tuple2);
    void* env;
};

struct Space_List* go_20(struct IntSpace_Space_Tuple2Space_Fun2 f_1, struct Space_List* acc_2, int i_, struct Space_Space_Tuple2List* xs_8) {
tailrec_37:;
    struct Space_List* match_9;
    if ((!((!(xs_8))))) goto next_39;
    struct Space_List* call_14 = listRev_2(acc_2);
    match_9 = call_14;
    goto end_match_38;
next_39:;
    if ((!(xs_8))) goto next_40;
    struct Space_Space_Tuple2 x_4 = xs_8->head;
    struct Space_Space_Tuple2List* xs_9 = xs_8->tail;
    struct IntSpace_Space_Tuple2Space_Fun2 arg_54 = f_1;
    struct Space_ app_5 = f_1.fun(f_1.env, i_, x_4);
    struct Space_List* list_10 = milone_mem_alloc(1, sizeof(struct Space_List));
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
    struct Space_List* call_15 = listRev_2(acc_2);
    match_10 = call_15;
    goto end_match_42;
next_43:;
    if ((!(xs_8))) goto next_44;
    struct Space_ x_4 = xs_8->head;
    struct Space_List* xs_9 = xs_8->tail;
    struct IntSpace_Space_Fun2 arg_58 = f_1;
    struct Space_ app_6 = f_1.fun(f_1.env, i_, x_4);
    struct Space_List* list_11 = milone_mem_alloc(1, sizeof(struct Space_List));
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
    struct Space_List* call_16 = go_20(f_1, NULL, 0, xs_7);
    return call_16;
}

struct Space_List* listMapWithIndex_1(struct IntSpace_Space_Fun2 f_1, struct Space_List* xs_7) {
    struct Space_List* call_17 = go_19(f_1, NULL, 0, xs_7);
    return call_17;
}

struct Space_BoolFun1 {
    bool(*fun)(void*, struct Space_);
    void* env;
};

bool go_18(struct Space_BoolFun1 p_, struct Space_List* xs_11) {
tailrec_45:;
    bool match_11;
    if ((!((!(xs_11))))) goto next_47;
    match_11 = true;
    goto end_match_46;
next_47:;
    if ((!(xs_11))) goto next_48;
    struct Space_ x_5 = xs_11->head;
    struct Space_List* xs_12 = xs_11->tail;
    bool app_7 = p_.fun(p_.env, x_5);
    bool if_;
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
    if_ = false;
    goto if_next_49;
else_51:;
    if_ = false;
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
    bool(*fun)(void*, struct Space_Space_Tuple2);
    void* env;
};

bool go_17(struct Space_Space_Tuple2BoolFun1 p_, struct Space_Space_Tuple2List* xs_11) {
tailrec_52:;
    bool match_12;
    if ((!((!(xs_11))))) goto next_54;
    match_12 = true;
    goto end_match_53;
next_54:;
    if ((!(xs_11))) goto next_55;
    struct Space_Space_Tuple2 x_5 = xs_11->head;
    struct Space_Space_Tuple2List* xs_12 = xs_11->tail;
    bool app_8 = p_.fun(p_.env, x_5);
    bool if_1;
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
    if_1 = false;
    goto if_next_56;
else_58:;
    if_1 = false;
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
    bool(*fun)(void*, bool);
    void* env;
};

bool go_16(struct BoolBoolFun1 p_, struct BoolList* xs_11) {
tailrec_59:;
    bool match_13;
    if ((!((!(xs_11))))) goto next_61;
    match_13 = true;
    goto end_match_60;
next_61:;
    if ((!(xs_11))) goto next_62;
    bool x_5 = xs_11->head;
    struct BoolList* xs_12 = xs_11->tail;
    bool app_9 = p_.fun(p_.env, x_5);
    bool if_2;
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
    if_2 = false;
    goto if_next_63;
else_65:;
    if_2 = false;
    goto if_next_63;
if_next_63:;
    match_13 = if_2;
    goto end_match_60;
next_62:;
    exit(1);
end_match_60:;
    return match_13;
}

bool listForAll_3(struct Space_BoolFun1 p_, struct Space_List* xs_10) {
    bool call_18 = go_18(p_, xs_10);
    return call_18;
}

bool listForAll_2(struct Space_Space_Tuple2BoolFun1 p_, struct Space_Space_Tuple2List* xs_10) {
    bool call_19 = go_17(p_, xs_10);
    return call_19;
}

bool listForAll_1(struct BoolBoolFun1 p_, struct BoolList* xs_10) {
    bool call_20 = go_16(p_, xs_10);
    return call_20;
}

bool go_15(struct Space_BoolFun1 p_1, struct Space_List* xs_14) {
tailrec_66:;
    bool match_14;
    if ((!((!(xs_14))))) goto next_68;
    match_14 = false;
    goto end_match_67;
next_68:;
    if ((!(xs_14))) goto next_69;
    struct Space_ x_6 = xs_14->head;
    struct Space_List* xs_15 = xs_14->tail;
    bool app_10 = p_1.fun(p_1.env, x_6);
    bool if_3;
    if (app_10) {
        goto then_71;
    } else {
        goto else_72;
    }
then_71:;
    if_3 = true;
    goto if_next_70;
else_72:;
    struct Space_BoolFun1 arg_68 = p_1;
    struct Space_List* arg_69 = xs_15;
    p_1 = arg_68;
    xs_14 = arg_69;
    goto tailrec_66;
    if_3 = false;
    goto if_next_70;
if_next_70:;
    match_14 = if_3;
    goto end_match_67;
next_69:;
    exit(1);
end_match_67:;
    return match_14;
}

bool listExists_1(struct Space_BoolFun1 p_1, struct Space_List* xs_13) {
    bool call_21 = go_15(p_1, xs_13);
    return call_21;
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
    struct Space_ call_22 = go_14(folder_, state_, xs_16);
    return call_22;
}

struct StringList* listFold_1(struct StringListSpace_StringListFun2 folder_, struct StringList* state_, struct Space_List* xs_16) {
    struct StringList* call_23 = go_13(folder_, state_, xs_16);
    return call_23;
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
    struct Space_Space_Tuple2List* call_24 = listRev_3(acc_3);
    match_17 = call_24;
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
    struct Space_Space_Tuple2List* list_12 = milone_mem_alloc(1, sizeof(struct Space_Space_Tuple2List));
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
    struct Space_Space_Tuple2List* call_25 = go_12(NULL, xs_19, ys_);
    return call_25;
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
    struct String call_26 = go_7(xs_24);
    match_18 = str_add(x_9, call_26);
    goto end_match_87;
next_89:;
    exit(1);
end_match_87:;
    return match_18;
}

struct String strConcat_(struct StringList* xs_22) {
    struct String call_27 = go_7(xs_22);
    return call_27;
}

struct StringSpace_ListTuple2 {
    struct String t0;
    struct Space_List* t1;
};

struct Space_ spaceCtor_(struct String tag_, struct Space_List* items_) {
    struct StringSpace_ListTuple2 tuple_2;
    tuple_2.t0 = tag_;
    tuple_2.t1 = items_;
    void* box_ = milone_mem_alloc(1, sizeof(struct StringSpace_ListTuple2));
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
    void* box_1 = milone_mem_alloc(1, sizeof(struct StringUnitSpace_Fun1Tuple2));
    (*(((struct StringUnitSpace_Fun1Tuple2*)box_1))) = tuple_3;
    struct Space_ variant_1 = (struct Space_){.tag = Ref_, .Ref_ = box_1};
    return variant_1;
}

struct Space_List* go_8(struct Space_List* spaces_1, struct Space_List* acc_4) {
tailrec_90:;
    struct Space_List* match_19;
    if ((!((!(spaces_1))))) goto next_92;
    struct Space_List* call_28 = listRev_2(acc_4);
    match_19 = call_28;
    goto end_match_91;
next_92:;
    if ((!(spaces_1))) goto next_93;
    if ((spaces_1->head.tag != Union_)) goto next_93;
    struct Space_List* subspaces_ = (*(((struct Space_List**)spaces_1->head.Union_)));
    struct Space_List* spaces_2 = spaces_1->tail;
    struct Space_List* arg_79 = spaces_2;
    struct Space_List* call_29 = go_8(subspaces_, acc_4);
    struct Space_List* arg_80 = call_29;
    spaces_1 = arg_79;
    acc_4 = arg_80;
    goto tailrec_90;
    match_19 = NULL;
    goto end_match_91;
next_93:;
    if ((!(spaces_1))) goto next_94;
    struct Space_ space_ = spaces_1->head;
    struct Space_List* spaces_3 = spaces_1->tail;
    bool call_30 = spaceIsEmpty_(space_);
    if ((!(call_30))) goto next_94;
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
    struct Space_List* list_13 = milone_mem_alloc(1, sizeof(struct Space_List));
    list_13->head = space_1;
    list_13->tail = acc_4;
    struct Space_List* arg_84 = list_13;
    spaces_1 = arg_83;
    acc_4 = arg_84;
    goto tailrec_90;
    match_19 = NULL;
    goto end_match_91;
next_95:;
    struct Space_List* call_31 = failwith_3((struct String){.str = "NEVER: suppress warning", .len = 23});
    match_19 = call_31;
    goto end_match_91;
next_96:;
end_match_91:;
    return match_19;
}

struct Space_ spaceUnion_(struct Space_List* spaces_) {
    struct Space_ match_20;
    struct Space_List* call_32 = go_8(spaces_, NULL);
    if ((!(call_32))) goto next_98;
    struct Space_ space_2 = call_32->head;
    if ((!((!(call_32->tail))))) goto next_98;
    match_20 = space_2;
    goto end_match_97;
next_98:;
    struct Space_List* spaces_5 = call_32;
    void* box_2 = milone_mem_alloc(1, sizeof(struct Space_List*));
    (*(((struct Space_List**)box_2))) = spaces_5;
    struct Space_ variant_2 = (struct Space_){.tag = Union_, .Union_ = box_2};
    match_20 = variant_2;
    goto end_match_97;
next_99:;
end_match_97:;
    return match_20;
}

bool fun_9(void* env_, struct Space_ arg_) {
    bool call_33 = spaceIsEmpty_(arg_);
    return call_33;
}

bool fun_10(void* env_1, struct Space_ arg_1) {
    bool call_34 = spaceIsEmpty_(arg_1);
    return call_34;
}

bool spaceIsEmpty_(struct Space_ space_3) {
    bool match_21;
    if ((space_3.tag != Ctor_)) goto next_101;
    struct Space_List* spaces_6 = (*(((struct StringSpace_ListTuple2*)space_3.Ctor_))).t1;
    void* box_3 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_3))) = 0;
    void* env_19 = box_3;
    struct Space_BoolFun1 fun_29 = (struct Space_BoolFun1){.fun = fun_9, .env = env_19};
    bool call_35 = listExists_1(fun_29, spaces_6);
    match_21 = call_35;
    goto end_match_100;
next_101:;
    if ((space_3.tag != Union_)) goto next_102;
    struct Space_List* spaces_7 = (*(((struct Space_List**)space_3.Union_)));
    void* box_4 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_4))) = 0;
    void* env_20 = box_4;
    struct Space_BoolFun1 fun_30 = (struct Space_BoolFun1){.fun = fun_10, .env = env_20};
    bool call_36 = listForAll_3(fun_30, spaces_7);
    match_21 = call_36;
    goto end_match_100;
next_102:;
    match_21 = false;
    goto end_match_100;
next_103:;
end_match_100:;
    bool result_ = match_21;
    return result_;
}

struct Space_ spaceDecompose_(struct Space_ space_4) {
    struct Space_ match_22;
    if ((space_4.tag != Ref_)) goto next_105;
    struct UnitSpace_Fun1 thunk_1 = (*(((struct StringUnitSpace_Fun1Tuple2*)space_4.Ref_))).t1;
    struct Space_ app_13 = thunk_1.fun(thunk_1.env, 0);
    struct Space_ space_5 = app_13;
    bool call_37 = spaceIsEmpty_(space_5);
    milone_assert((!(call_37)), 234, 4);
    match_22 = space_5;
    goto end_match_104;
next_105:;
    milone_assert(false, 238, 4);
    match_22 = space_4;
    goto end_match_104;
next_106:;
end_match_104:;
    return match_22;
}

bool fun_(struct Space_Space_Tuple2 arg_85) {
    struct Space_ first_1 = arg_85.t0;
    struct Space_ second_1 = arg_85.t1;
    bool call_38 = spaceCovers_(first_1, second_1);
    return call_38;
}

bool fun_11(void* env_2, struct Space_Space_Tuple2 arg_2) {
    bool call_39 = fun_(arg_2);
    return call_39;
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
    struct Space_ call_40 = spaceExclude_(first_2, second_2);
    if_4 = call_40;
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
    struct Space_ call_41 = fun_2(arg_5, arg_3, arg_4);
    return call_41;
}

struct Space_ fun_28(struct String tag_2, struct Space_List* firsts_, struct Space_List* seconds_, int i_1, struct Space_ arg_87) {
    struct IntTuple1 tuple_4;
    tuple_4.t0 = i_1;
    void* box_5 = milone_mem_alloc(1, sizeof(struct IntTuple1));
    (*(((struct IntTuple1*)box_5))) = tuple_4;
    void* env_21 = box_5;
    struct IntSpace_Space_Tuple2Space_Fun2 fun_31 = (struct IntSpace_Space_Tuple2Space_Fun2){.fun = fun_12, .env = env_21};
    struct Space_Space_Tuple2List* call_42 = listZip_1(firsts_, seconds_);
    struct Space_List* call_43 = listMapWithIndex_2(fun_31, call_42);
    struct Space_ call_44 = spaceCtor_(tag_2, call_43);
    return call_44;
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
    struct Space_ call_45 = fun_28(arg_8, arg_9, arg_10, arg_6, arg_7);
    return call_45;
}

struct Space_ fun_14(void* env_5, struct Space_ arg_11, struct Space_ arg_12) {
    struct Space_ call_46 = spaceExclude_(arg_11, arg_12);
    return call_46;
}

struct Space_ fun_3(struct Space_ second_, struct Space_ first_3) {
    struct Space_ call_47 = spaceExclude_(first_3, second_);
    return call_47;
}

struct Space_Tuple1 {
    struct Space_ t0;
};

struct Space_ fun_15(void* env_6, struct Space_ arg_13) {
    struct Space_ arg_14 = (*(((struct Space_Tuple1*)env_6))).t0;
    struct Space_ call_48 = fun_3(arg_14, arg_13);
    return call_48;
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
    void* box_6 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_6))) = 0;
    void* env_22 = box_6;
    struct Space_Space_Tuple2BoolFun1 fun_32 = (struct Space_Space_Tuple2BoolFun1){.fun = fun_11, .env = env_22};
    struct Space_Space_Tuple2List* call_49 = listZip_1(firsts_, seconds_);
    bool call_50 = listForAll_2(fun_32, call_49);
    bool dominant_ = call_50;
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
    void* box_7 = milone_mem_alloc(1, sizeof(struct StringSpace_ListSpace_ListTuple3));
    (*(((struct StringSpace_ListSpace_ListTuple3*)box_7))) = tuple_6;
    void* env_23 = box_7;
    struct IntSpace_Space_Fun2 fun_33 = (struct IntSpace_Space_Fun2){.fun = fun_13, .env = env_23};
    struct Space_List* call_51 = listMapWithIndex_1(fun_33, firsts_);
    struct Space_ call_52 = spaceUnion_(call_51);
    if_5 = call_52;
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
    void* box_8 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_8))) = 0;
    void* env_24 = box_8;
    struct Space_Space_Space_Fun2 fun_34 = (struct Space_Space_Space_Fun2){.fun = fun_14, .env = env_24};
    struct Space_ call_53 = listFold_2(fun_34, first_, seconds_1);
    match_23 = call_53;
    goto end_match_111;
next_118:;
    if ((tuple_5.t0.tag != Union_)) goto next_119;
    struct Space_List* firsts_1 = (*(((struct Space_List**)tuple_5.t0.Union_)));
    struct Space_Tuple1 tuple_7;
    tuple_7.t0 = second_;
    void* box_9 = milone_mem_alloc(1, sizeof(struct Space_Tuple1));
    (*(((struct Space_Tuple1*)box_9))) = tuple_7;
    void* env_25 = box_9;
    struct Space_Space_Fun1 fun_35 = (struct Space_Space_Fun1){.fun = fun_15, .env = env_25};
    struct Space_List* call_54 = listMap_5(fun_35, firsts_1);
    struct Space_ call_55 = spaceUnion_(call_54);
    match_23 = call_55;
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
    struct Space_ call_56 = spaceDecompose_(first_);
    struct Space_ arg_88 = call_56;
    struct Space_ arg_89 = second_;
    first_ = arg_88;
    second_ = arg_89;
    goto tailrec_110;
    match_23 = ((struct Space_){});
    goto end_match_111;
next_121:;
    if ((tuple_5.t1.tag != Ref_)) goto next_122;
    milone_assert(false, 345, 4);
    struct Space_ arg_90 = first_;
    struct Space_ call_57 = spaceDecompose_(second_);
    struct Space_ arg_91 = call_57;
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

bool spaceCovers_(struct Space_ other_, struct Space_ cover_) {
    struct Space_ call_58 = spaceExclude_(other_, cover_);
    bool call_59 = spaceIsEmpty_(call_58);
    return call_59;
}

struct StringList* fun_4(struct StringList* acc_7, struct Space_ space_8) {
    struct StringList* call_60 = cons_1((struct String){.str = ", ", .len = 2}, acc_7);
    struct StringList* call_61 = go_9(space_8, call_60);
    return call_61;
}

struct StringList* fun_16(void* env_7, struct StringList* arg_15, struct Space_ arg_16) {
    struct StringList* call_62 = fun_4(arg_15, arg_16);
    return call_62;
}

struct StringList* fun_5(struct StringList* acc_9, struct Space_ space_9) {
    struct StringList* call_63 = cons_1((struct String){.str = ", ", .len = 2}, acc_9);
    struct StringList* call_64 = go_9(space_9, call_63);
    return call_64;
}

struct StringList* fun_17(void* env_8, struct StringList* arg_17, struct Space_ arg_18) {
    struct StringList* call_65 = fun_5(arg_17, arg_18);
    return call_65;
}

struct StringList* go_9(struct Space_ space_7, struct StringList* acc_5) {
    struct StringList* match_24;
    if ((space_7.tag != Full_)) goto next_127;
    struct StringList* call_66 = cons_1((struct String){.str = "full", .len = 4}, acc_5);
    match_24 = call_66;
    goto end_match_126;
next_127:;
    if ((space_7.tag != Ctor_)) goto next_128;
    struct String tag_4 = (*(((struct StringSpace_ListTuple2*)space_7.Ctor_))).t0;
    if ((!((!((*(((struct StringSpace_ListTuple2*)space_7.Ctor_))).t1))))) goto next_128;
    struct StringList* call_67 = cons_1(tag_4, acc_5);
    match_24 = call_67;
    goto end_match_126;
next_128:;
    if ((space_7.tag != Ctor_)) goto next_129;
    struct String tag_5 = (*(((struct StringSpace_ListTuple2*)space_7.Ctor_))).t0;
    if ((!((*(((struct StringSpace_ListTuple2*)space_7.Ctor_))).t1))) goto next_129;
    struct Space_ item_ = (*(((struct StringSpace_ListTuple2*)space_7.Ctor_))).t1->head;
    struct Space_List* items_1 = (*(((struct StringSpace_ListTuple2*)space_7.Ctor_))).t1->tail;
    struct StringList* call_68 = cons_1(tag_5, acc_5);
    struct StringList* call_69 = cons_1((struct String){.str = "(", .len = 1}, call_68);
    struct StringList* call_70 = go_9(item_, call_69);
    struct StringList* acc_6 = call_70;
    void* box_10 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_10))) = 0;
    void* env_26 = box_10;
    struct StringListSpace_StringListFun2 fun_36 = (struct StringListSpace_StringListFun2){.fun = fun_16, .env = env_26};
    struct StringList* call_71 = listFold_1(fun_36, acc_6, items_1);
    struct StringList* call_72 = cons_1((struct String){.str = ")", .len = 1}, call_71);
    match_24 = call_72;
    goto end_match_126;
next_129:;
    if ((space_7.tag != Ref_)) goto next_130;
    struct String tag_6 = (*(((struct StringUnitSpace_Fun1Tuple2*)space_7.Ref_))).t0;
    struct StringList* call_73 = cons_1(tag_6, acc_5);
    match_24 = call_73;
    goto end_match_126;
next_130:;
    if ((space_7.tag != Union_)) goto next_131;
    if ((!((!((*(((struct Space_List**)space_7.Union_)))))))) goto next_131;
    struct StringList* call_74 = cons_1((struct String){.str = "empty", .len = 5}, acc_5);
    match_24 = call_74;
    goto end_match_126;
next_131:;
    if ((space_7.tag != Union_)) goto next_132;
    if ((!((*(((struct Space_List**)space_7.Union_)))))) goto next_132;
    struct Space_ subspace_ = (*(((struct Space_List**)space_7.Union_)))->head;
    struct Space_List* subspaces_1 = (*(((struct Space_List**)space_7.Union_)))->tail;
    struct StringList* call_75 = cons_1((struct String){.str = "+(", .len = 2}, acc_5);
    struct StringList* call_76 = go_9(subspace_, call_75);
    struct StringList* acc_8 = call_76;
    void* box_11 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_11))) = 0;
    void* env_27 = box_11;
    struct StringListSpace_StringListFun2 fun_37 = (struct StringListSpace_StringListFun2){.fun = fun_17, .env = env_27};
    struct StringList* call_77 = listFold_1(fun_37, acc_8, subspaces_1);
    struct StringList* call_78 = cons_1((struct String){.str = ")", .len = 1}, call_77);
    match_24 = call_78;
    goto end_match_126;
next_132:;
    struct StringList* call_79 = failwith_2((struct String){.str = "NEVER: suppress warning", .len = 23});
    match_24 = call_79;
    goto end_match_126;
next_133:;
end_match_126:;
    return match_24;
}

struct String spaceToString_(struct Space_ space_6) {
    struct StringList* call_80 = go_9(space_6, NULL);
    struct StringList* call_81 = listRev_1(call_80);
    struct String call_82 = strConcat_(call_81);
    return call_82;
}

struct Space_ fun_18(void* env_9, struct Ty_ arg_19) {
    struct Space_ call_83 = go_10(arg_19);
    return call_83;
}

struct Space_ fun_19(void* env_10, int arg_20) {
    struct Space_ arg_21 = (*(((struct Space_Tuple1*)env_10))).t0;
    struct Space_ call_84 = thunk_2(arg_21, 0);
    return call_84;
}

struct Space_ thunk_2(struct Space_ itemSpace_, int arg_92) {
    struct Space_ call_85 = spaceCtor_((struct String){.str = "nil", .len = 3}, NULL);
    struct Space_Tuple1 tuple_8;
    tuple_8.t0 = itemSpace_;
    void* box_12 = milone_mem_alloc(1, sizeof(struct Space_Tuple1));
    (*(((struct Space_Tuple1*)box_12))) = tuple_8;
    void* env_28 = box_12;
    struct UnitSpace_Fun1 fun_38 = (struct UnitSpace_Fun1){.fun = fun_19, .env = env_28};
    struct Space_ call_86 = spaceRef_((struct String){.str = "list", .len = 4}, fun_38);
    struct Space_List* list_17 = milone_mem_alloc(1, sizeof(struct Space_List));
    list_17->head = call_86;
    list_17->tail = NULL;
    struct Space_List* list_16 = milone_mem_alloc(1, sizeof(struct Space_List));
    list_16->head = itemSpace_;
    list_16->tail = list_17;
    struct Space_ call_87 = spaceCtor_((struct String){.str = "cons", .len = 4}, list_16);
    struct Space_List* list_15 = milone_mem_alloc(1, sizeof(struct Space_List));
    list_15->head = call_87;
    list_15->tail = NULL;
    struct Space_List* list_14 = milone_mem_alloc(1, sizeof(struct Space_List));
    list_14->head = call_85;
    list_14->tail = list_15;
    struct Space_ call_88 = spaceUnion_(list_14);
    return call_88;
}

struct Space_ fun_20(void* env_11, int arg_22) {
    struct Space_ arg_23 = (*(((struct Space_Tuple1*)env_11))).t0;
    struct Space_ call_89 = thunk_2(arg_23, 0);
    return call_89;
}

struct Space_ go_10(struct Ty_ ty_1) {
    struct Space_ match_25;
    if ((ty_1.tag != Int_)) goto next_135;
    match_25 = spaceFull_;
    goto end_match_134;
next_135:;
    if ((ty_1.tag != Tuple_)) goto next_136;
    struct Ty_List* itemTys_ = (*(((struct Ty_List**)ty_1.Tuple_)));
    void* box_13 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_13))) = 0;
    void* env_29 = box_13;
    struct Ty_Space_Fun1 fun_39 = (struct Ty_Space_Fun1){.fun = fun_18, .env = env_29};
    struct Space_List* call_90 = listMap_4(fun_39, itemTys_);
    struct Space_ call_91 = spaceCtor_((struct String){.str = "tuple", .len = 5}, call_90);
    match_25 = call_91;
    goto end_match_134;
next_136:;
    if ((ty_1.tag != List_)) goto next_137;
    struct Ty_ itemTy_ = (*(((struct Ty_*)ty_1.List_)));
    struct Space_ call_92 = go_10(itemTy_);
    struct Space_ itemSpace_ = call_92;
    struct Space_Tuple1 tuple_9;
    tuple_9.t0 = itemSpace_;
    void* box_14 = milone_mem_alloc(1, sizeof(struct Space_Tuple1));
    (*(((struct Space_Tuple1*)box_14))) = tuple_9;
    void* env_30 = box_14;
    struct UnitSpace_Fun1 fun_40 = (struct UnitSpace_Fun1){.fun = fun_20, .env = env_30};
    struct Space_ call_93 = spaceRef_((struct String){.str = "list", .len = 4}, fun_40);
    match_25 = call_93;
    goto end_match_134;
next_137:;
    exit(1);
end_match_134:;
    return match_25;
}

struct Space_ tyToSpace_(struct Ty_ ty_) {
    struct Space_ call_94 = go_10(ty_);
    return call_94;
}

struct Space_ fun_21(void* env_12, struct Pat_ arg_24) {
    struct Space_ call_95 = go_11(arg_24);
    return call_95;
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
    void* box_15 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_15))) = 0;
    void* env_31 = box_15;
    struct Pat_Space_Fun1 fun_41 = (struct Pat_Space_Fun1){.fun = fun_21, .env = env_31};
    struct Space_List* call_96 = listMap_3(fun_41, itemPats_);
    struct Space_ call_97 = spaceCtor_((struct String){.str = "tuple", .len = 5}, call_96);
    match_26 = call_97;
    goto end_match_138;
next_141:;
    if ((pat_1.tag != Nil_)) goto next_142;
    struct Space_ call_98 = spaceCtor_((struct String){.str = "nil", .len = 3}, NULL);
    match_26 = call_98;
    goto end_match_138;
next_142:;
    if ((pat_1.tag != Cons_)) goto next_143;
    struct Pat_ headPat_ = (*(((struct Pat_Pat_Tuple2*)pat_1.Cons_))).t0;
    struct Pat_ tailPat_ = (*(((struct Pat_Pat_Tuple2*)pat_1.Cons_))).t1;
    struct Space_ call_99 = go_11(headPat_);
    struct Space_ call_100 = go_11(tailPat_);
    struct Space_List* list_19 = milone_mem_alloc(1, sizeof(struct Space_List));
    list_19->head = call_100;
    list_19->tail = NULL;
    struct Space_List* list_18 = milone_mem_alloc(1, sizeof(struct Space_List));
    list_18->head = call_99;
    list_18->tail = list_19;
    struct Space_ call_101 = spaceCtor_((struct String){.str = "cons", .len = 4}, list_18);
    match_26 = call_101;
    goto end_match_138;
next_143:;
    struct Space_ call_102 = failwith_1((struct String){.str = "NEVER: suppress warning", .len = 23});
    match_26 = call_102;
    goto end_match_138;
next_144:;
end_match_138:;
    return match_26;
}

struct Space_ patToSpace_(struct Pat_ pat_) {
    struct Space_ call_103 = go_11(pat_);
    return call_103;
}

struct Space_ fun_22(void* env_13, struct Pat_ arg_25) {
    struct Space_ call_104 = patToSpace_(arg_25);
    return call_104;
}

struct Space_ patsToSpace_(struct Pat_List* pats_) {
    void* box_16 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_16))) = 0;
    void* env_32 = box_16;
    struct Pat_Space_Fun1 fun_42 = (struct Pat_Space_Fun1){.fun = fun_22, .env = env_32};
    struct Space_List* call_105 = listMap_3(fun_42, pats_);
    struct Space_ call_106 = spaceUnion_(call_105);
    return call_106;
}

struct Space_ fun_6(int arg_93) {
    return spaceFull_;
}

struct Space_ fun_23(void* env_14, int arg_26) {
    struct Space_ call_107 = fun_6(0);
    return call_107;
}

int testSpaceIsEmpty_(int arg_94) {
    bool call_108 = spaceIsEmpty_(spaceEmpty_);
    milone_assert(call_108, 455, 2);
    struct Space_List* list_22 = milone_mem_alloc(1, sizeof(struct Space_List));
    list_22->head = spaceEmpty_;
    list_22->tail = NULL;
    struct Space_ call_109 = spaceUnion_(list_22);
    struct Space_List* list_21 = milone_mem_alloc(1, sizeof(struct Space_List));
    list_21->head = call_109;
    list_21->tail = NULL;
    struct Space_List* list_20 = milone_mem_alloc(1, sizeof(struct Space_List));
    list_20->head = spaceEmpty_;
    list_20->tail = list_21;
    struct Space_ call_110 = spaceUnion_(list_20);
    bool call_111 = spaceIsEmpty_(call_110);
    milone_assert(call_111, 456, 2);
    bool call_112 = spaceIsEmpty_(spaceFull_);
    milone_assert((!(call_112)), 458, 2);
    void* box_17 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_17))) = 0;
    void* env_33 = box_17;
    struct UnitSpace_Fun1 fun_43 = (struct UnitSpace_Fun1){.fun = fun_23, .env = env_33};
    struct Space_ call_113 = spaceRef_((struct String){.str = "ref", .len = 3}, fun_43);
    bool call_114 = spaceIsEmpty_(call_113);
    milone_assert((!(call_114)), 459, 2);
    struct Space_List* list_24 = milone_mem_alloc(1, sizeof(struct Space_List));
    list_24->head = spaceFull_;
    list_24->tail = NULL;
    struct Space_List* list_23 = milone_mem_alloc(1, sizeof(struct Space_List));
    list_23->head = spaceEmpty_;
    list_23->tail = list_24;
    struct Space_ call_115 = spaceUnion_(list_23);
    bool call_116 = spaceIsEmpty_(call_115);
    milone_assert((!(call_116)), 460, 2);
    struct Space_ call_117 = spaceCtor_((struct String){.str = "tuple", .len = 5}, NULL);
    bool call_118 = spaceIsEmpty_(call_117);
    milone_assert((!(call_118)), 462, 2);
    struct Space_List* list_27 = milone_mem_alloc(1, sizeof(struct Space_List));
    list_27->head = spaceFull_;
    list_27->tail = NULL;
    struct Space_List* list_26 = milone_mem_alloc(1, sizeof(struct Space_List));
    list_26->head = spaceEmpty_;
    list_26->tail = list_27;
    struct Space_List* list_25 = milone_mem_alloc(1, sizeof(struct Space_List));
    list_25->head = spaceFull_;
    list_25->tail = list_26;
    struct Space_ call_119 = spaceCtor_((struct String){.str = "tuple", .len = 5}, list_25);
    bool call_120 = spaceIsEmpty_(call_119);
    milone_assert(call_120, 463, 2);
    void* box_18 = milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_18))) = (struct Ty_){.tag = Int_};
    struct Ty_ variant_3 = (struct Ty_){.tag = List_, .List_ = box_18};
    struct Space_ call_121 = tyToSpace_(variant_3);
    bool call_122 = spaceIsEmpty_(call_121);
    milone_assert((!(call_122)), 465, 2);
    void* box_19 = milone_mem_alloc(1, sizeof(struct Ty_List*));
    (*(((struct Ty_List**)box_19))) = NULL;
    struct Ty_ variant_4 = (struct Ty_){.tag = Tuple_, .Tuple_ = box_19};
    void* box_20 = milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_20))) = variant_4;
    struct Ty_ variant_5 = (struct Ty_){.tag = List_, .List_ = box_20};
    struct Space_ call_123 = tyToSpace_(variant_5);
    bool call_124 = spaceIsEmpty_(call_123);
    milone_assert((!(call_124)), 466, 2);
    return 0;
}

bool fun_24(void* env_15, bool arg_27) {
    bool call_125 = id_1(arg_27);
    return call_125;
}

bool fun_7(struct StringSpace_Tuple2 arg_95) {
    struct String expected_ = arg_95.t0;
    struct Space_ space_10 = arg_95.t1;
    struct String call_126 = spaceToString_(space_10);
    struct String actual_ = call_126;
    bool if_6;
    if ((str_cmp(actual_, expected_) == 0)) {
        goto then_146;
    } else {
        goto else_147;
    }
then_146:;
    if_6 = true;
    goto if_next_145;
else_147:;
    printf("%s: NG (%s)\n", expected_.str, actual_.str);
    if_6 = false;
    goto if_next_145;
if_next_145:;
    return if_6;
}

bool fun_25(void* env_16, struct StringSpace_Tuple2 arg_28) {
    bool call_127 = fun_7(arg_28);
    return call_127;
}

int testSpaceToString_(int arg_96) {
    struct StringSpace_Tuple2 tuple_10;
    tuple_10.t0 = (struct String){.str = "empty", .len = 5};
    tuple_10.t1 = spaceEmpty_;
    struct StringSpace_Tuple2 tuple_11;
    tuple_11.t0 = (struct String){.str = "full", .len = 4};
    tuple_11.t1 = spaceFull_;
    struct Space_ call_128 = spaceCtor_((struct String){.str = "nil", .len = 3}, NULL);
    struct StringSpace_Tuple2 tuple_12;
    tuple_12.t0 = (struct String){.str = "nil", .len = 3};
    tuple_12.t1 = call_128;
    struct Space_List* list_33 = milone_mem_alloc(1, sizeof(struct Space_List));
    list_33->head = spaceFull_;
    list_33->tail = NULL;
    struct Space_List* list_32 = milone_mem_alloc(1, sizeof(struct Space_List));
    list_32->head = spaceEmpty_;
    list_32->tail = list_33;
    struct Space_ call_129 = spaceCtor_((struct String){.str = "tuple", .len = 5}, list_32);
    struct StringSpace_Tuple2 tuple_13;
    tuple_13.t0 = (struct String){.str = "tuple(empty, full)", .len = 18};
    tuple_13.t1 = call_129;
    struct Space_ call_130 = tyToSpace_((struct Ty_){.tag = Int_});
    struct StringSpace_Tuple2 tuple_14;
    tuple_14.t0 = (struct String){.str = "full", .len = 4};
    tuple_14.t1 = call_130;
    void* box_21 = milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_21))) = (struct Ty_){.tag = Int_};
    struct Ty_ variant_6 = (struct Ty_){.tag = List_, .List_ = box_21};
    struct Space_ call_131 = tyToSpace_(variant_6);
    struct Space_ call_132 = spaceDecompose_(call_131);
    struct StringSpace_Tuple2 tuple_15;
    tuple_15.t0 = (struct String){.str = "+(nil, cons(full, list))", .len = 24};
    tuple_15.t1 = call_132;
    struct Pat_Pat_Tuple2 tuple_17;
    tuple_17.t0 = (struct Pat_){.tag = Discard_};
    tuple_17.t1 = (struct Pat_){.tag = Nil_};
    void* box_22 = milone_mem_alloc(1, sizeof(struct Pat_Pat_Tuple2));
    (*(((struct Pat_Pat_Tuple2*)box_22))) = tuple_17;
    struct Pat_ variant_7 = (struct Pat_){.tag = Cons_, .Cons_ = box_22};
    struct Space_ call_133 = patToSpace_(variant_7);
    struct StringSpace_Tuple2 tuple_16;
    tuple_16.t0 = (struct String){.str = "cons(full, nil)", .len = 15};
    tuple_16.t1 = call_133;
    struct StringSpace_Tuple2List* list_36 = milone_mem_alloc(1, sizeof(struct StringSpace_Tuple2List));
    list_36->head = tuple_16;
    list_36->tail = NULL;
    struct StringSpace_Tuple2List* list_35 = milone_mem_alloc(1, sizeof(struct StringSpace_Tuple2List));
    list_35->head = tuple_15;
    list_35->tail = list_36;
    struct StringSpace_Tuple2List* list_34 = milone_mem_alloc(1, sizeof(struct StringSpace_Tuple2List));
    list_34->head = tuple_14;
    list_34->tail = list_35;
    struct StringSpace_Tuple2List* list_31 = milone_mem_alloc(1, sizeof(struct StringSpace_Tuple2List));
    list_31->head = tuple_13;
    list_31->tail = list_34;
    struct StringSpace_Tuple2List* list_30 = milone_mem_alloc(1, sizeof(struct StringSpace_Tuple2List));
    list_30->head = tuple_12;
    list_30->tail = list_31;
    struct StringSpace_Tuple2List* list_29 = milone_mem_alloc(1, sizeof(struct StringSpace_Tuple2List));
    list_29->head = tuple_11;
    list_29->tail = list_30;
    struct StringSpace_Tuple2List* list_28 = milone_mem_alloc(1, sizeof(struct StringSpace_Tuple2List));
    list_28->head = tuple_10;
    list_28->tail = list_29;
    struct StringSpace_Tuple2List* cases_ = list_28;
    void* box_23 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_23))) = 0;
    void* env_34 = box_23;
    struct BoolBoolFun1 fun_44 = (struct BoolBoolFun1){.fun = fun_24, .env = env_34};
    void* box_24 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_24))) = 0;
    void* env_35 = box_24;
    struct StringSpace_Tuple2BoolFun1 fun_45 = (struct StringSpace_Tuple2BoolFun1){.fun = fun_25, .env = env_35};
    struct BoolList* call_134 = listMap_2(fun_45, cases_);
    bool call_135 = listForAll_1(fun_44, call_134);
    bool ok_ = call_135;
    milone_assert(ok_, 497, 2);
    return 0;
}

bool fun_26(void* env_17, bool arg_29) {
    bool call_136 = id_1(arg_29);
    return call_136;
}

struct BoolStringTuple2 {
    bool t0;
    struct String t1;
};

struct Covering_Covering_Tuple2 {
    struct Covering_ t0;
    struct Covering_ t1;
};

bool fun_8(struct StringTy_Pat_ListCovering_Tuple4 arg_97) {
    struct String name_ = arg_97.t0;
    struct Ty_ ty_2 = arg_97.t1;
    struct Pat_List* pats_1 = arg_97.t2;
    struct Covering_ covering_ = arg_97.t3;
    struct Space_ call_137 = tyToSpace_(ty_2);
    struct Space_ tySpace_ = call_137;
    struct Space_ call_138 = patsToSpace_(pats_1);
    struct Space_ patSpace_ = call_138;
    bool call_139 = spaceCovers_(tySpace_, patSpace_);
    struct Covering_ if_7;
    if (call_139) {
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
    tuple_19.t0 = true;
    tuple_19.t1 = (struct String){.str = "OK", .len = 2};
    match_27 = tuple_19;
    goto end_match_151;
next_154:;
    if ((tuple_18.t0.tag != Covering_)) goto next_155;
    if ((tuple_18.t1.tag != Open_)) goto next_155;
    struct BoolStringTuple2 tuple_20;
    tuple_20.t0 = false;
    tuple_20.t1 = (struct String){.str = "NG. Expected covering but open", .len = 30};
    match_27 = tuple_20;
    goto end_match_151;
next_155:;
    struct BoolStringTuple2 tuple_21;
    tuple_21.t0 = false;
    tuple_21.t1 = (struct String){.str = "NG. Expected open but covering", .len = 30};
    match_27 = tuple_21;
    goto end_match_151;
next_156:;
end_match_151:;
    bool ok_2 = match_27.t0;
    struct String msg_1 = match_27.t1;
    printf("%s: %s\n", name_.str, msg_1.str);
    int if_8;
    if ((!(ok_2))) {
        goto then_158;
    } else {
        goto else_159;
    }
then_158:;
    struct String call_140 = spaceToString_(tySpace_);
    printf("  ty: %s\n", call_140.str);
    struct String call_141 = spaceToString_(patSpace_);
    printf("  pats: %s\n", call_141.str);
    if_8 = 0;
    goto if_next_157;
else_159:;
    if_8 = 0;
    goto if_next_157;
if_next_157:;
    return ok_2;
}

bool fun_27(void* env_18, struct StringTy_Pat_ListCovering_Tuple4 arg_30) {
    bool call_142 = fun_8(arg_30);
    return call_142;
}

int main() {
    spaceFull_ = (struct Space_){.tag = Full_};
    void* box_25 = milone_mem_alloc(1, sizeof(struct Space_List*));
    (*(((struct Space_List**)box_25))) = NULL;
    struct Space_ variant_8 = (struct Space_){.tag = Union_, .Union_ = box_25};
    spaceEmpty_ = variant_8;
    int call_143 = testSpaceIsEmpty_(0);
    int call_144 = testSpaceToString_(0);
    struct Pat_Pat_Tuple2 tuple_22;
    tuple_22.t0 = (struct Pat_){.tag = Discard_};
    tuple_22.t1 = (struct Pat_){.tag = Discard_};
    void* box_26 = milone_mem_alloc(1, sizeof(struct Pat_Pat_Tuple2));
    (*(((struct Pat_Pat_Tuple2*)box_26))) = tuple_22;
    struct Pat_ variant_9 = (struct Pat_){.tag = Cons_, .Cons_ = box_26};
    struct Pat_ anyConsPat_ = variant_9;
    void* box_27 = milone_mem_alloc(1, sizeof(struct Ty_List*));
    (*(((struct Ty_List**)box_27))) = NULL;
    struct Ty_ variant_10 = (struct Ty_){.tag = Tuple_, .Tuple_ = box_27};
    void* box_28 = milone_mem_alloc(1, sizeof(struct Pat_List*));
    (*(((struct Pat_List**)box_28))) = NULL;
    struct Pat_ variant_11 = (struct Pat_){.tag = TupleLit_, .TupleLit_ = box_28};
    struct Pat_List* list_38 = milone_mem_alloc(1, sizeof(struct Pat_List));
    list_38->head = variant_11;
    list_38->tail = NULL;
    struct StringTy_Pat_ListCovering_Tuple4 tuple_23;
    tuple_23.t0 = (struct String){.str = "unit with ()", .len = 12};
    tuple_23.t1 = variant_10;
    tuple_23.t2 = list_38;
    tuple_23.t3 = (struct Covering_){.tag = Covering_};
    struct Pat_ variant_12 = (struct Pat_){.tag = IntLit_, .IntLit_ = 1};
    struct Pat_List* list_40 = milone_mem_alloc(1, sizeof(struct Pat_List));
    list_40->head = variant_12;
    list_40->tail = NULL;
    struct StringTy_Pat_ListCovering_Tuple4 tuple_24;
    tuple_24.t0 = (struct String){.str = "int with literal pats", .len = 21};
    tuple_24.t1 = (struct Ty_){.tag = Int_};
    tuple_24.t2 = list_40;
    tuple_24.t3 = (struct Covering_){.tag = Open_};
    struct Pat_List* list_42 = milone_mem_alloc(1, sizeof(struct Pat_List));
    list_42->head = (struct Pat_){.tag = Discard_};
    list_42->tail = NULL;
    struct StringTy_Pat_ListCovering_Tuple4 tuple_25;
    tuple_25.t0 = (struct String){.str = "int with _", .len = 10};
    tuple_25.t1 = (struct Ty_){.tag = Int_};
    tuple_25.t2 = list_42;
    tuple_25.t3 = (struct Covering_){.tag = Covering_};
    struct Pat_ variant_13 = (struct Pat_){.tag = IntLit_, .IntLit_ = 1};
    struct Pat_List* list_45 = milone_mem_alloc(1, sizeof(struct Pat_List));
    list_45->head = (struct Pat_){.tag = Discard_};
    list_45->tail = NULL;
    struct Pat_List* list_44 = milone_mem_alloc(1, sizeof(struct Pat_List));
    list_44->head = variant_13;
    list_44->tail = list_45;
    struct StringTy_Pat_ListCovering_Tuple4 tuple_26;
    tuple_26.t0 = (struct String){.str = "int with 1|_", .len = 12};
    tuple_26.t1 = (struct Ty_){.tag = Int_};
    tuple_26.t2 = list_44;
    tuple_26.t3 = (struct Covering_){.tag = Covering_};
    void* box_29 = milone_mem_alloc(1, sizeof(struct Ty_List*));
    (*(((struct Ty_List**)box_29))) = NULL;
    struct Ty_ variant_14 = (struct Ty_){.tag = Tuple_, .Tuple_ = box_29};
    struct Ty_List* list_48 = milone_mem_alloc(1, sizeof(struct Ty_List));
    list_48->head = variant_14;
    list_48->tail = NULL;
    struct Ty_List* list_47 = milone_mem_alloc(1, sizeof(struct Ty_List));
    list_47->head = (struct Ty_){.tag = Int_};
    list_47->tail = list_48;
    void* box_30 = milone_mem_alloc(1, sizeof(struct Ty_List*));
    (*(((struct Ty_List**)box_30))) = list_47;
    struct Ty_ variant_15 = (struct Ty_){.tag = Tuple_, .Tuple_ = box_30};
    void* box_31 = milone_mem_alloc(1, sizeof(struct Pat_List*));
    (*(((struct Pat_List**)box_31))) = NULL;
    struct Pat_ variant_16 = (struct Pat_){.tag = TupleLit_, .TupleLit_ = box_31};
    struct Pat_List* list_51 = milone_mem_alloc(1, sizeof(struct Pat_List));
    list_51->head = variant_16;
    list_51->tail = NULL;
    struct Pat_List* list_50 = milone_mem_alloc(1, sizeof(struct Pat_List));
    list_50->head = (struct Pat_){.tag = Discard_};
    list_50->tail = list_51;
    void* box_32 = milone_mem_alloc(1, sizeof(struct Pat_List*));
    (*(((struct Pat_List**)box_32))) = list_50;
    struct Pat_ variant_17 = (struct Pat_){.tag = TupleLit_, .TupleLit_ = box_32};
    struct Pat_List* list_49 = milone_mem_alloc(1, sizeof(struct Pat_List));
    list_49->head = variant_17;
    list_49->tail = NULL;
    struct StringTy_Pat_ListCovering_Tuple4 tuple_27;
    tuple_27.t0 = (struct String){.str = "int * unit with _, ()", .len = 21};
    tuple_27.t1 = variant_15;
    tuple_27.t2 = list_49;
    tuple_27.t3 = (struct Covering_){.tag = Covering_};
    struct Ty_List* list_54 = milone_mem_alloc(1, sizeof(struct Ty_List));
    list_54->head = (struct Ty_){.tag = Int_};
    list_54->tail = NULL;
    struct Ty_List* list_53 = milone_mem_alloc(1, sizeof(struct Ty_List));
    list_53->head = (struct Ty_){.tag = Int_};
    list_53->tail = list_54;
    void* box_33 = milone_mem_alloc(1, sizeof(struct Ty_List*));
    (*(((struct Ty_List**)box_33))) = list_53;
    struct Ty_ variant_18 = (struct Ty_){.tag = Tuple_, .Tuple_ = box_33};
    struct Pat_ variant_19 = (struct Pat_){.tag = IntLit_, .IntLit_ = 1};
    struct Pat_List* list_57 = milone_mem_alloc(1, sizeof(struct Pat_List));
    list_57->head = (struct Pat_){.tag = Discard_};
    list_57->tail = NULL;
    struct Pat_List* list_56 = milone_mem_alloc(1, sizeof(struct Pat_List));
    list_56->head = variant_19;
    list_56->tail = list_57;
    void* box_34 = milone_mem_alloc(1, sizeof(struct Pat_List*));
    (*(((struct Pat_List**)box_34))) = list_56;
    struct Pat_ variant_20 = (struct Pat_){.tag = TupleLit_, .TupleLit_ = box_34};
    struct Pat_ variant_21 = (struct Pat_){.tag = IntLit_, .IntLit_ = 1};
    struct Pat_List* list_60 = milone_mem_alloc(1, sizeof(struct Pat_List));
    list_60->head = variant_21;
    list_60->tail = NULL;
    struct Pat_List* list_59 = milone_mem_alloc(1, sizeof(struct Pat_List));
    list_59->head = (struct Pat_){.tag = Discard_};
    list_59->tail = list_60;
    void* box_35 = milone_mem_alloc(1, sizeof(struct Pat_List*));
    (*(((struct Pat_List**)box_35))) = list_59;
    struct Pat_ variant_22 = (struct Pat_){.tag = TupleLit_, .TupleLit_ = box_35};
    struct Pat_List* list_58 = milone_mem_alloc(1, sizeof(struct Pat_List));
    list_58->head = variant_22;
    list_58->tail = NULL;
    struct Pat_List* list_55 = milone_mem_alloc(1, sizeof(struct Pat_List));
    list_55->head = variant_20;
    list_55->tail = list_58;
    struct StringTy_Pat_ListCovering_Tuple4 tuple_28;
    tuple_28.t0 = (struct String){.str = "int * int with 1, _ | _, 1", .len = 26};
    tuple_28.t1 = variant_18;
    tuple_28.t2 = list_55;
    tuple_28.t3 = (struct Covering_){.tag = Open_};
    void* box_36 = milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_36))) = (struct Ty_){.tag = Int_};
    struct Ty_ variant_23 = (struct Ty_){.tag = List_, .List_ = box_36};
    struct Pat_List* list_62 = milone_mem_alloc(1, sizeof(struct Pat_List));
    list_62->head = (struct Pat_){.tag = Nil_};
    list_62->tail = NULL;
    struct StringTy_Pat_ListCovering_Tuple4 tuple_29;
    tuple_29.t0 = (struct String){.str = "int list with []", .len = 16};
    tuple_29.t1 = variant_23;
    tuple_29.t2 = list_62;
    tuple_29.t3 = (struct Covering_){.tag = Open_};
    void* box_37 = milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_37))) = (struct Ty_){.tag = Int_};
    struct Ty_ variant_24 = (struct Ty_){.tag = List_, .List_ = box_37};
    struct Pat_List* list_64 = milone_mem_alloc(1, sizeof(struct Pat_List));
    list_64->head = anyConsPat_;
    list_64->tail = NULL;
    struct StringTy_Pat_ListCovering_Tuple4 tuple_30;
    tuple_30.t0 = (struct String){.str = "int list with _::_", .len = 18};
    tuple_30.t1 = variant_24;
    tuple_30.t2 = list_64;
    tuple_30.t3 = (struct Covering_){.tag = Open_};
    void* box_38 = milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_38))) = (struct Ty_){.tag = Int_};
    struct Ty_ variant_25 = (struct Ty_){.tag = List_, .List_ = box_38};
    struct Pat_List* list_67 = milone_mem_alloc(1, sizeof(struct Pat_List));
    list_67->head = anyConsPat_;
    list_67->tail = NULL;
    struct Pat_List* list_66 = milone_mem_alloc(1, sizeof(struct Pat_List));
    list_66->head = (struct Pat_){.tag = Nil_};
    list_66->tail = list_67;
    struct StringTy_Pat_ListCovering_Tuple4 tuple_31;
    tuple_31.t0 = (struct String){.str = "int list with [] | _::_", .len = 23};
    tuple_31.t1 = variant_25;
    tuple_31.t2 = list_66;
    tuple_31.t3 = (struct Covering_){.tag = Covering_};
    void* box_39 = milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_39))) = (struct Ty_){.tag = Int_};
    struct Ty_ variant_26 = (struct Ty_){.tag = List_, .List_ = box_39};
    struct Pat_Pat_Tuple2 tuple_33;
    tuple_33.t0 = (struct Pat_){.tag = Discard_};
    tuple_33.t1 = (struct Pat_){.tag = Nil_};
    void* box_40 = milone_mem_alloc(1, sizeof(struct Pat_Pat_Tuple2));
    (*(((struct Pat_Pat_Tuple2*)box_40))) = tuple_33;
    struct Pat_ variant_27 = (struct Pat_){.tag = Cons_, .Cons_ = box_40};
    struct Pat_Pat_Tuple2 tuple_34;
    tuple_34.t0 = (struct Pat_){.tag = Discard_};
    tuple_34.t1 = anyConsPat_;
    void* box_41 = milone_mem_alloc(1, sizeof(struct Pat_Pat_Tuple2));
    (*(((struct Pat_Pat_Tuple2*)box_41))) = tuple_34;
    struct Pat_ variant_28 = (struct Pat_){.tag = Cons_, .Cons_ = box_41};
    struct Pat_List* list_71 = milone_mem_alloc(1, sizeof(struct Pat_List));
    list_71->head = variant_28;
    list_71->tail = NULL;
    struct Pat_List* list_70 = milone_mem_alloc(1, sizeof(struct Pat_List));
    list_70->head = variant_27;
    list_70->tail = list_71;
    struct Pat_List* list_69 = milone_mem_alloc(1, sizeof(struct Pat_List));
    list_69->head = (struct Pat_){.tag = Nil_};
    list_69->tail = list_70;
    struct StringTy_Pat_ListCovering_Tuple4 tuple_32;
    tuple_32.t0 = (struct String){.str = "int list with [] | [_] | _::_::_", .len = 32};
    tuple_32.t1 = variant_26;
    tuple_32.t2 = list_69;
    tuple_32.t3 = (struct Covering_){.tag = Covering_};
    void* box_42 = milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_42))) = (struct Ty_){.tag = Int_};
    struct Ty_ variant_29 = (struct Ty_){.tag = List_, .List_ = box_42};
    void* box_43 = milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_43))) = variant_29;
    struct Ty_ variant_30 = (struct Ty_){.tag = List_, .List_ = box_43};
    struct Pat_Pat_Tuple2 tuple_36;
    tuple_36.t0 = (struct Pat_){.tag = Nil_};
    tuple_36.t1 = (struct Pat_){.tag = Nil_};
    void* box_44 = milone_mem_alloc(1, sizeof(struct Pat_Pat_Tuple2));
    (*(((struct Pat_Pat_Tuple2*)box_44))) = tuple_36;
    struct Pat_ variant_31 = (struct Pat_){.tag = Cons_, .Cons_ = box_44};
    struct Pat_Pat_Tuple2 tuple_37;
    tuple_37.t0 = anyConsPat_;
    tuple_37.t1 = (struct Pat_){.tag = Discard_};
    void* box_45 = milone_mem_alloc(1, sizeof(struct Pat_Pat_Tuple2));
    (*(((struct Pat_Pat_Tuple2*)box_45))) = tuple_37;
    struct Pat_ variant_32 = (struct Pat_){.tag = Cons_, .Cons_ = box_45};
    struct Pat_Pat_Tuple2 tuple_38;
    tuple_38.t0 = (struct Pat_){.tag = Discard_};
    tuple_38.t1 = anyConsPat_;
    void* box_46 = milone_mem_alloc(1, sizeof(struct Pat_Pat_Tuple2));
    (*(((struct Pat_Pat_Tuple2*)box_46))) = tuple_38;
    struct Pat_ variant_33 = (struct Pat_){.tag = Cons_, .Cons_ = box_46};
    struct Pat_List* list_76 = milone_mem_alloc(1, sizeof(struct Pat_List));
    list_76->head = variant_33;
    list_76->tail = NULL;
    struct Pat_List* list_75 = milone_mem_alloc(1, sizeof(struct Pat_List));
    list_75->head = variant_32;
    list_75->tail = list_76;
    struct Pat_List* list_74 = milone_mem_alloc(1, sizeof(struct Pat_List));
    list_74->head = variant_31;
    list_74->tail = list_75;
    struct Pat_List* list_73 = milone_mem_alloc(1, sizeof(struct Pat_List));
    list_73->head = (struct Pat_){.tag = Nil_};
    list_73->tail = list_74;
    struct StringTy_Pat_ListCovering_Tuple4 tuple_35;
    tuple_35.t0 = (struct String){.str = "int list list with [] | [[]] | [_::_] | _::_::_", .len = 47};
    tuple_35.t1 = variant_30;
    tuple_35.t2 = list_73;
    tuple_35.t3 = (struct Covering_){.tag = Covering_};
    void* box_47 = milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_47))) = (struct Ty_){.tag = Int_};
    struct Ty_ variant_34 = (struct Ty_){.tag = List_, .List_ = box_47};
    void* box_48 = milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_48))) = (struct Ty_){.tag = Int_};
    struct Ty_ variant_35 = (struct Ty_){.tag = List_, .List_ = box_48};
    struct Ty_List* list_79 = milone_mem_alloc(1, sizeof(struct Ty_List));
    list_79->head = variant_35;
    list_79->tail = NULL;
    struct Ty_List* list_78 = milone_mem_alloc(1, sizeof(struct Ty_List));
    list_78->head = variant_34;
    list_78->tail = list_79;
    void* box_49 = milone_mem_alloc(1, sizeof(struct Ty_List*));
    (*(((struct Ty_List**)box_49))) = list_78;
    struct Ty_ variant_36 = (struct Ty_){.tag = Tuple_, .Tuple_ = box_49};
    struct Pat_List* list_82 = milone_mem_alloc(1, sizeof(struct Pat_List));
    list_82->head = (struct Pat_){.tag = Nil_};
    list_82->tail = NULL;
    struct Pat_List* list_81 = milone_mem_alloc(1, sizeof(struct Pat_List));
    list_81->head = (struct Pat_){.tag = Nil_};
    list_81->tail = list_82;
    void* box_50 = milone_mem_alloc(1, sizeof(struct Pat_List*));
    (*(((struct Pat_List**)box_50))) = list_81;
    struct Pat_ variant_37 = (struct Pat_){.tag = TupleLit_, .TupleLit_ = box_50};
    struct Pat_List* list_85 = milone_mem_alloc(1, sizeof(struct Pat_List));
    list_85->head = (struct Pat_){.tag = Nil_};
    list_85->tail = NULL;
    struct Pat_List* list_84 = milone_mem_alloc(1, sizeof(struct Pat_List));
    list_84->head = anyConsPat_;
    list_84->tail = list_85;
    void* box_51 = milone_mem_alloc(1, sizeof(struct Pat_List*));
    (*(((struct Pat_List**)box_51))) = list_84;
    struct Pat_ variant_38 = (struct Pat_){.tag = TupleLit_, .TupleLit_ = box_51};
    struct Pat_List* list_88 = milone_mem_alloc(1, sizeof(struct Pat_List));
    list_88->head = anyConsPat_;
    list_88->tail = NULL;
    struct Pat_List* list_87 = milone_mem_alloc(1, sizeof(struct Pat_List));
    list_87->head = (struct Pat_){.tag = Nil_};
    list_87->tail = list_88;
    void* box_52 = milone_mem_alloc(1, sizeof(struct Pat_List*));
    (*(((struct Pat_List**)box_52))) = list_87;
    struct Pat_ variant_39 = (struct Pat_){.tag = TupleLit_, .TupleLit_ = box_52};
    struct Pat_List* list_91 = milone_mem_alloc(1, sizeof(struct Pat_List));
    list_91->head = anyConsPat_;
    list_91->tail = NULL;
    struct Pat_List* list_90 = milone_mem_alloc(1, sizeof(struct Pat_List));
    list_90->head = anyConsPat_;
    list_90->tail = list_91;
    void* box_53 = milone_mem_alloc(1, sizeof(struct Pat_List*));
    (*(((struct Pat_List**)box_53))) = list_90;
    struct Pat_ variant_40 = (struct Pat_){.tag = TupleLit_, .TupleLit_ = box_53};
    struct Pat_List* list_89 = milone_mem_alloc(1, sizeof(struct Pat_List));
    list_89->head = variant_40;
    list_89->tail = NULL;
    struct Pat_List* list_86 = milone_mem_alloc(1, sizeof(struct Pat_List));
    list_86->head = variant_39;
    list_86->tail = list_89;
    struct Pat_List* list_83 = milone_mem_alloc(1, sizeof(struct Pat_List));
    list_83->head = variant_38;
    list_83->tail = list_86;
    struct Pat_List* list_80 = milone_mem_alloc(1, sizeof(struct Pat_List));
    list_80->head = variant_37;
    list_80->tail = list_83;
    struct StringTy_Pat_ListCovering_Tuple4 tuple_39;
    tuple_39.t0 = (struct String){.str = "int list * int list with [], [] | [], _::_ | _::_, [] | _::_, _::_", .len = 66};
    tuple_39.t1 = variant_36;
    tuple_39.t2 = list_80;
    tuple_39.t3 = (struct Covering_){.tag = Covering_};
    struct StringTy_Pat_ListCovering_Tuple4List* list_77 = milone_mem_alloc(1, sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    list_77->head = tuple_39;
    list_77->tail = NULL;
    struct StringTy_Pat_ListCovering_Tuple4List* list_72 = milone_mem_alloc(1, sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    list_72->head = tuple_35;
    list_72->tail = list_77;
    struct StringTy_Pat_ListCovering_Tuple4List* list_68 = milone_mem_alloc(1, sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    list_68->head = tuple_32;
    list_68->tail = list_72;
    struct StringTy_Pat_ListCovering_Tuple4List* list_65 = milone_mem_alloc(1, sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    list_65->head = tuple_31;
    list_65->tail = list_68;
    struct StringTy_Pat_ListCovering_Tuple4List* list_63 = milone_mem_alloc(1, sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    list_63->head = tuple_30;
    list_63->tail = list_65;
    struct StringTy_Pat_ListCovering_Tuple4List* list_61 = milone_mem_alloc(1, sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    list_61->head = tuple_29;
    list_61->tail = list_63;
    struct StringTy_Pat_ListCovering_Tuple4List* list_52 = milone_mem_alloc(1, sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    list_52->head = tuple_28;
    list_52->tail = list_61;
    struct StringTy_Pat_ListCovering_Tuple4List* list_46 = milone_mem_alloc(1, sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    list_46->head = tuple_27;
    list_46->tail = list_52;
    struct StringTy_Pat_ListCovering_Tuple4List* list_43 = milone_mem_alloc(1, sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    list_43->head = tuple_26;
    list_43->tail = list_46;
    struct StringTy_Pat_ListCovering_Tuple4List* list_41 = milone_mem_alloc(1, sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    list_41->head = tuple_25;
    list_41->tail = list_43;
    struct StringTy_Pat_ListCovering_Tuple4List* list_39 = milone_mem_alloc(1, sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    list_39->head = tuple_24;
    list_39->tail = list_41;
    struct StringTy_Pat_ListCovering_Tuple4List* list_37 = milone_mem_alloc(1, sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    list_37->head = tuple_23;
    list_37->tail = list_39;
    struct StringTy_Pat_ListCovering_Tuple4List* testCases_ = list_37;
    void* box_54 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_54))) = 0;
    void* env_36 = box_54;
    struct BoolBoolFun1 fun_46 = (struct BoolBoolFun1){.fun = fun_26, .env = env_36};
    void* box_55 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_55))) = 0;
    void* env_37 = box_55;
    struct StringTy_Pat_ListCovering_Tuple4BoolFun1 fun_47 = (struct StringTy_Pat_ListCovering_Tuple4BoolFun1){.fun = fun_27, .env = env_37};
    struct BoolList* call_145 = listMap_1(fun_47, testCases_);
    bool call_146 = listForAll_1(fun_46, call_145);
    bool ok_1 = call_146;
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
