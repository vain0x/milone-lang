#include "milone.h"

struct Space_List;

struct StringList;

struct StringSpace_ListTuple2;

struct Space_;

struct StringList;

struct Space_List;

struct BoolList;

struct BoolList;

struct Space_Space_Tuple2List;

struct Space_Space_Tuple2;

struct Space_Space_Tuple2List;

struct Space_Space_Fun1;

struct Ty_Space_Fun1;

struct Ty_List;

struct Ty_;

struct Ty_List;

struct Pat_Space_Fun1;

struct Pat_List;

struct Pat_;

struct Pat_List;

struct StringSpace_Tuple2BoolFun1;

struct StringSpace_Tuple2List;

struct StringSpace_Tuple2;

struct StringSpace_Tuple2List;

struct StringTy_Pat_ListCovering_Tuple4BoolFun1;

struct StringTy_Pat_ListCovering_Tuple4List;

struct Covering_;

struct StringTy_Pat_ListCovering_Tuple4;

struct StringTy_Pat_ListCovering_Tuple4List;

struct IntSpace_Space_Tuple2Space_Fun2;

struct IntSpace_Space_Fun2;

struct Space_BoolFun1;

struct Space_Space_Tuple2BoolFun1;

struct BoolBoolFun1;

struct Space_Space_Space_Fun2;

struct StringListSpace_StringListFun2;

struct Space_ListSpace_ListTuple2;

struct UnitSpace_Fun1;

struct StringUnitSpace_Fun1Tuple2;

struct IntTuple1;

struct StringSpace_ListSpace_ListTuple3;

struct Space_Tuple1;

struct Pat_Pat_Tuple2;

struct BoolStringTuple2;

struct Covering_Covering_Tuple2;

bool id_1(bool x_);

struct Space_List const* failwith_3(struct String msg_);

struct StringList const* failwith_2(struct String msg_);

struct Space_ failwith_1(struct String msg_);

struct StringList const* cons_1(struct String head_, struct StringList const* tail_);

struct Space_List const* go_13(struct Space_List const* acc_, struct Space_List const* xs_2);

struct StringList const* go_12(struct StringList const* acc_, struct StringList const* xs_2);

struct BoolList const* go_29(struct BoolList const* acc_, struct BoolList const* xs_2);

struct Space_Space_Tuple2List const* go_28(struct Space_Space_Tuple2List const* acc_, struct Space_Space_Tuple2List const* xs_2);

struct Space_List const* listRev_2(struct Space_List const* xs_1);

struct StringList const* listRev_1(struct StringList const* xs_1);

struct BoolList const* listRev_4(struct BoolList const* xs_1);

struct Space_Space_Tuple2List const* listRev_3(struct Space_Space_Tuple2List const* xs_1);

struct Space_List const* go_18(struct Space_Space_Fun1 f_, struct Space_List const* acc_1, struct Space_List const* xs_5);

struct Space_List const* go_17(struct Ty_Space_Fun1 f_, struct Space_List const* acc_1, struct Ty_List const* xs_5);

struct Space_List const* go_16(struct Pat_Space_Fun1 f_, struct Space_List const* acc_1, struct Pat_List const* xs_5);

struct BoolList const* go_15(struct StringSpace_Tuple2BoolFun1 f_, struct BoolList const* acc_1, struct StringSpace_Tuple2List const* xs_5);

struct BoolList const* go_14(struct StringTy_Pat_ListCovering_Tuple4BoolFun1 f_, struct BoolList const* acc_1, struct StringTy_Pat_ListCovering_Tuple4List const* xs_5);

struct Space_List const* listMap_5(struct Space_Space_Fun1 f_, struct Space_List const* xs_4);

struct Space_List const* listMap_4(struct Ty_Space_Fun1 f_, struct Ty_List const* xs_4);

struct Space_List const* listMap_3(struct Pat_Space_Fun1 f_, struct Pat_List const* xs_4);

struct BoolList const* listMap_2(struct StringSpace_Tuple2BoolFun1 f_, struct StringSpace_Tuple2List const* xs_4);

struct BoolList const* listMap_1(struct StringTy_Pat_ListCovering_Tuple4BoolFun1 f_, struct StringTy_Pat_ListCovering_Tuple4List const* xs_4);

struct Space_List const* go_20(struct IntSpace_Space_Tuple2Space_Fun2 f_1, struct Space_List const* acc_2, int i_, struct Space_Space_Tuple2List const* xs_8);

struct Space_List const* go_19(struct IntSpace_Space_Fun2 f_1, struct Space_List const* acc_2, int i_, struct Space_List const* xs_8);

struct Space_List const* listMapWithIndex_2(struct IntSpace_Space_Tuple2Space_Fun2 f_1, struct Space_Space_Tuple2List const* xs_7);

struct Space_List const* listMapWithIndex_1(struct IntSpace_Space_Fun2 f_1, struct Space_List const* xs_7);

bool go_23(struct Space_BoolFun1 p_, struct Space_List const* xs_11);

bool go_22(struct Space_Space_Tuple2BoolFun1 p_, struct Space_Space_Tuple2List const* xs_11);

bool go_21(struct BoolBoolFun1 p_, struct BoolList const* xs_11);

bool listForAll_3(struct Space_BoolFun1 p_, struct Space_List const* xs_10);

bool listForAll_2(struct Space_Space_Tuple2BoolFun1 p_, struct Space_Space_Tuple2List const* xs_10);

bool listForAll_1(struct BoolBoolFun1 p_, struct BoolList const* xs_10);

bool go_24(struct Space_BoolFun1 p_1, struct Space_List const* xs_14);

bool listExists_1(struct Space_BoolFun1 p_1, struct Space_List const* xs_13);

struct Space_ go_26(struct Space_Space_Space_Fun2 folder_, struct Space_ state_1, struct Space_List const* xs_17);

struct StringList const* go_25(struct StringListSpace_StringListFun2 folder_, struct StringList const* state_1, struct Space_List const* xs_17);

struct Space_ listFold_2(struct Space_Space_Space_Fun2 folder_, struct Space_ state_, struct Space_List const* xs_16);

struct StringList const* listFold_1(struct StringListSpace_StringListFun2 folder_, struct StringList const* state_, struct Space_List const* xs_16);

struct Space_Space_Tuple2List const* go_27(struct Space_Space_Tuple2List const* acc_3, struct Space_List const* xs_20, struct Space_List const* ys_1);

struct Space_Space_Tuple2List const* listZip_1(struct Space_List const* xs_19, struct Space_List const* ys_);

struct String go_7(struct StringList const* xs_23);

struct String strConcat_(struct StringList const* xs_22);

struct Space_ spaceCtor_(struct String tag_, struct Space_List const* items_);

struct Space_ spaceRef_(struct String tag_1, struct UnitSpace_Fun1 thunk_);

struct Space_List const* go_8(struct Space_List const* spaces_1, struct Space_List const* acc_4);

struct Space_ spaceUnion_(struct Space_List const* spaces_);

bool fun_9(void const* env_, struct Space_ arg_);

bool fun_10(void const* env_1, struct Space_ arg_1);

bool spaceIsEmpty_(struct Space_ space_3);

struct Space_ spaceDecompose_(struct Space_ space_4);

bool fun_(struct Space_Space_Tuple2 arg_85);

bool fun_11(void const* env_2, struct Space_Space_Tuple2 arg_2);

struct Space_ fun_2(int i_1, int j_, struct Space_Space_Tuple2 arg_86);

struct Space_ fun_12(void const* env_3, int arg_3, struct Space_Space_Tuple2 arg_4);

struct Space_ fun_28(struct String tag_2, struct Space_List const* firsts_, struct Space_List const* seconds_, int i_1, struct Space_ arg_87);

struct Space_ fun_13(void const* env_4, int arg_6, struct Space_ arg_7);

struct Space_ fun_14(void const* env_5, struct Space_ arg_11, struct Space_ arg_12);

struct Space_ fun_3(struct Space_ second_, struct Space_ first_3);

struct Space_ fun_15(void const* env_6, struct Space_ arg_13);

struct Space_ spaceExclude_(struct Space_ first_, struct Space_ second_);

bool spaceCovers_(struct Space_ other_, struct Space_ cover_);

struct StringList const* fun_4(struct StringList const* acc_7, struct Space_ space_8);

struct StringList const* fun_16(void const* env_7, struct StringList const* arg_15, struct Space_ arg_16);

struct StringList const* fun_5(struct StringList const* acc_9, struct Space_ space_9);

struct StringList const* fun_17(void const* env_8, struct StringList const* arg_17, struct Space_ arg_18);

struct StringList const* go_9(struct Space_ space_7, struct StringList const* acc_5);

struct String spaceToString_(struct Space_ space_6);

struct Space_ fun_18(void const* env_9, struct Ty_ arg_19);

struct Space_ fun_19(void const* env_10, char arg_20);

struct Space_ thunk_2(struct Space_ itemSpace_, char arg_92);

struct Space_ fun_20(void const* env_11, char arg_22);

struct Space_ go_10(struct Ty_ ty_1);

struct Space_ tyToSpace_(struct Ty_ ty_);

struct Space_ fun_21(void const* env_12, struct Pat_ arg_24);

struct Space_ go_11(struct Pat_ pat_1);

struct Space_ patToSpace_(struct Pat_ pat_);

struct Space_ fun_22(void const* env_13, struct Pat_ arg_25);

struct Space_ patsToSpace_(struct Pat_List const* pats_);

struct Space_ fun_6(char arg_93);

struct Space_ fun_23(void const* env_14, char arg_26);

char testSpaceIsEmpty_(char arg_94);

bool fun_24(void const* env_15, bool arg_27);

bool fun_7(struct StringSpace_Tuple2 arg_95);

bool fun_25(void const* env_16, struct StringSpace_Tuple2 arg_28);

char testSpaceToString_(char arg_96);

bool fun_26(void const* env_17, bool arg_29);

bool fun_8(struct StringTy_Pat_ListCovering_Tuple4 arg_97);

bool fun_27(void const* env_18, struct StringTy_Pat_ListCovering_Tuple4 arg_30);

int milone_main();

struct StringSpace_ListTuple2 {
    struct String t0;
    struct Space_List const* t1;
};

enum Space_Discriminant {
    Full_,
    Ctor_,
    Ref_,
    Union_,
};

struct Space_ {
    enum Space_Discriminant discriminant;
    union {
        struct StringSpace_ListTuple2 Ctor_;
        void const* Ref_;
        struct Space_List const* Union_;
    };
};

struct StringList {
    struct String head;
    struct StringList const* tail;
};

struct Space_List {
    struct Space_ head;
    struct Space_List const* tail;
};

struct BoolList {
    bool head;
    struct BoolList const* tail;
};

struct Space_Space_Tuple2 {
    struct Space_ t0;
    struct Space_ t1;
};

struct Space_Space_Tuple2List {
    struct Space_Space_Tuple2 head;
    struct Space_Space_Tuple2List const* tail;
};

struct Space_Space_Fun1 {
    struct Space_(*fun)(void const*, struct Space_);
    void const* env;
};

struct Ty_Space_Fun1 {
    struct Space_(*fun)(void const*, struct Ty_);
    void const* env;
};

enum Ty_Discriminant {
    Int_,
    Tuple_,
    List_,
};

struct Ty_ {
    enum Ty_Discriminant discriminant;
    union {
        struct Ty_List const* Tuple_;
        void const* List_;
    };
};

struct Ty_List {
    struct Ty_ head;
    struct Ty_List const* tail;
};

struct Pat_Space_Fun1 {
    struct Space_(*fun)(void const*, struct Pat_);
    void const* env;
};

enum Pat_Discriminant {
    Discard_,
    IntLit_,
    TupleLit_,
    Nil_,
    Cons_,
};

struct Pat_ {
    enum Pat_Discriminant discriminant;
    union {
        int IntLit_;
        struct Pat_List const* TupleLit_;
        void const* Cons_;
    };
};

struct Pat_List {
    struct Pat_ head;
    struct Pat_List const* tail;
};

struct StringSpace_Tuple2BoolFun1 {
    bool(*fun)(void const*, struct StringSpace_Tuple2);
    void const* env;
};

struct StringSpace_Tuple2 {
    struct String t0;
    struct Space_ t1;
};

struct StringSpace_Tuple2List {
    struct StringSpace_Tuple2 head;
    struct StringSpace_Tuple2List const* tail;
};

struct StringTy_Pat_ListCovering_Tuple4BoolFun1 {
    bool(*fun)(void const*, struct StringTy_Pat_ListCovering_Tuple4);
    void const* env;
};

enum Covering_Discriminant {
    Covering_,
    Open_,
};

struct Covering_ {
    enum Covering_Discriminant discriminant;
};

struct StringTy_Pat_ListCovering_Tuple4 {
    struct String t0;
    struct Ty_ t1;
    struct Pat_List const* t2;
    struct Covering_ t3;
};

struct StringTy_Pat_ListCovering_Tuple4List {
    struct StringTy_Pat_ListCovering_Tuple4 head;
    struct StringTy_Pat_ListCovering_Tuple4List const* tail;
};

struct IntSpace_Space_Tuple2Space_Fun2 {
    struct Space_(*fun)(void const*, int, struct Space_Space_Tuple2);
    void const* env;
};

struct IntSpace_Space_Fun2 {
    struct Space_(*fun)(void const*, int, struct Space_);
    void const* env;
};

struct Space_BoolFun1 {
    bool(*fun)(void const*, struct Space_);
    void const* env;
};

struct Space_Space_Tuple2BoolFun1 {
    bool(*fun)(void const*, struct Space_Space_Tuple2);
    void const* env;
};

struct BoolBoolFun1 {
    bool(*fun)(void const*, bool);
    void const* env;
};

struct Space_Space_Space_Fun2 {
    struct Space_(*fun)(void const*, struct Space_, struct Space_);
    void const* env;
};

struct StringListSpace_StringListFun2 {
    struct StringList const*(*fun)(void const*, struct StringList const*, struct Space_);
    void const* env;
};

struct Space_ListSpace_ListTuple2 {
    struct Space_List const* t0;
    struct Space_List const* t1;
};

struct UnitSpace_Fun1 {
    struct Space_(*fun)(void const*, char);
    void const* env;
};

struct StringUnitSpace_Fun1Tuple2 {
    struct String t0;
    struct UnitSpace_Fun1 t1;
};

struct IntTuple1 {
    int t0;
};

struct StringSpace_ListSpace_ListTuple3 {
    struct String t0;
    struct Space_List const* t1;
    struct Space_List const* t2;
};

struct Space_Tuple1 {
    struct Space_ t0;
};

struct Pat_Pat_Tuple2 {
    struct Pat_ t0;
    struct Pat_ t1;
};

struct BoolStringTuple2 {
    bool t0;
    struct String t1;
};

struct Covering_Covering_Tuple2 {
    struct Covering_ t0;
    struct Covering_ t1;
};

static struct Space_ spaceFull_;

static struct Space_ spaceEmpty_;

bool id_1(bool x_) {
    return x_;
}

struct Space_List const* failwith_3(struct String msg_) {
    printf("ERROR %s\n", str_to_c_str(msg_));
    exit(1);
}

struct StringList const* failwith_2(struct String msg_) {
    printf("ERROR %s\n", str_to_c_str(msg_));
    exit(1);
}

struct Space_ failwith_1(struct String msg_) {
    printf("ERROR %s\n", str_to_c_str(msg_));
    exit(1);
}

struct StringList const* cons_1(struct String head_, struct StringList const* tail_) {
    struct StringList const* list_ = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_))) = (struct StringList){.head = head_, .tail = tail_};
    return list_;
}

struct Space_List const* go_13(struct Space_List const* acc_, struct Space_List const* xs_2) {
tailrec_1:;
    struct Space_List const* match_;
    if ((!((!(xs_2))))) goto next_3;
    match_ = acc_;
    goto end_match_2;
next_3:;
    if ((!(xs_2))) goto next_4;
    struct Space_ x_2 = xs_2->head;
    struct Space_List const* xs_3 = xs_2->tail;
    struct Space_List const* list_1 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_1))) = (struct Space_List){.head = x_2, .tail = acc_};
    struct Space_List const* arg_31 = list_1;
    struct Space_List const* arg_32 = xs_3;
    acc_ = arg_31;
    xs_2 = arg_32;
    goto tailrec_1;
next_4:;
    exit(1);
end_match_2:;
    return match_;
}

struct StringList const* go_12(struct StringList const* acc_, struct StringList const* xs_2) {
tailrec_5:;
    struct StringList const* match_1;
    if ((!((!(xs_2))))) goto next_7;
    match_1 = acc_;
    goto end_match_6;
next_7:;
    if ((!(xs_2))) goto next_8;
    struct String x_2 = xs_2->head;
    struct StringList const* xs_3 = xs_2->tail;
    struct StringList const* list_2 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_2))) = (struct StringList){.head = x_2, .tail = acc_};
    struct StringList const* arg_33 = list_2;
    struct StringList const* arg_34 = xs_3;
    acc_ = arg_33;
    xs_2 = arg_34;
    goto tailrec_5;
next_8:;
    exit(1);
end_match_6:;
    return match_1;
}

struct BoolList const* go_29(struct BoolList const* acc_, struct BoolList const* xs_2) {
tailrec_9:;
    struct BoolList const* match_2;
    if ((!((!(xs_2))))) goto next_11;
    match_2 = acc_;
    goto end_match_10;
next_11:;
    if ((!(xs_2))) goto next_12;
    bool x_2 = xs_2->head;
    struct BoolList const* xs_3 = xs_2->tail;
    struct BoolList const* list_3 = milone_mem_alloc(1, sizeof(struct BoolList));
    (*(((struct BoolList*)list_3))) = (struct BoolList){.head = x_2, .tail = acc_};
    struct BoolList const* arg_35 = list_3;
    struct BoolList const* arg_36 = xs_3;
    acc_ = arg_35;
    xs_2 = arg_36;
    goto tailrec_9;
next_12:;
    exit(1);
end_match_10:;
    return match_2;
}

struct Space_Space_Tuple2List const* go_28(struct Space_Space_Tuple2List const* acc_, struct Space_Space_Tuple2List const* xs_2) {
tailrec_13:;
    struct Space_Space_Tuple2List const* match_3;
    if ((!((!(xs_2))))) goto next_15;
    match_3 = acc_;
    goto end_match_14;
next_15:;
    if ((!(xs_2))) goto next_16;
    struct Space_Space_Tuple2 x_2 = xs_2->head;
    struct Space_Space_Tuple2List const* xs_3 = xs_2->tail;
    struct Space_Space_Tuple2List const* list_4 = milone_mem_alloc(1, sizeof(struct Space_Space_Tuple2List));
    (*(((struct Space_Space_Tuple2List*)list_4))) = (struct Space_Space_Tuple2List){.head = x_2, .tail = acc_};
    struct Space_Space_Tuple2List const* arg_37 = list_4;
    struct Space_Space_Tuple2List const* arg_38 = xs_3;
    acc_ = arg_37;
    xs_2 = arg_38;
    goto tailrec_13;
next_16:;
    exit(1);
end_match_14:;
    return match_3;
}

struct Space_List const* listRev_2(struct Space_List const* xs_1) {
    struct Space_List const* call_ = go_13(NULL, xs_1);
    return call_;
}

struct StringList const* listRev_1(struct StringList const* xs_1) {
    struct StringList const* call_1 = go_12(NULL, xs_1);
    return call_1;
}

struct BoolList const* listRev_4(struct BoolList const* xs_1) {
    struct BoolList const* call_2 = go_29(NULL, xs_1);
    return call_2;
}

struct Space_Space_Tuple2List const* listRev_3(struct Space_Space_Tuple2List const* xs_1) {
    struct Space_Space_Tuple2List const* call_3 = go_28(NULL, xs_1);
    return call_3;
}

struct Space_List const* go_18(struct Space_Space_Fun1 f_, struct Space_List const* acc_1, struct Space_List const* xs_5) {
tailrec_17:;
    struct Space_List const* match_4;
    if ((!((!(xs_5))))) goto next_19;
    struct Space_List const* call_4 = listRev_2(acc_1);
    match_4 = call_4;
    goto end_match_18;
next_19:;
    if ((!(xs_5))) goto next_20;
    struct Space_ x_3 = xs_5->head;
    struct Space_List const* xs_6 = xs_5->tail;
    struct Space_Space_Fun1 arg_39 = f_;
    struct Space_ app_ = f_.fun(f_.env, x_3);
    struct Space_List const* list_5 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_5))) = (struct Space_List){.head = app_, .tail = acc_1};
    struct Space_List const* arg_40 = list_5;
    struct Space_List const* arg_41 = xs_6;
    f_ = arg_39;
    acc_1 = arg_40;
    xs_5 = arg_41;
    goto tailrec_17;
next_20:;
    exit(1);
end_match_18:;
    return match_4;
}

struct Space_List const* go_17(struct Ty_Space_Fun1 f_, struct Space_List const* acc_1, struct Ty_List const* xs_5) {
tailrec_21:;
    struct Space_List const* match_5;
    if ((!((!(xs_5))))) goto next_23;
    struct Space_List const* call_5 = listRev_2(acc_1);
    match_5 = call_5;
    goto end_match_22;
next_23:;
    if ((!(xs_5))) goto next_24;
    struct Ty_ x_3 = xs_5->head;
    struct Ty_List const* xs_6 = xs_5->tail;
    struct Ty_Space_Fun1 arg_42 = f_;
    struct Space_ app_1 = f_.fun(f_.env, x_3);
    struct Space_List const* list_6 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_6))) = (struct Space_List){.head = app_1, .tail = acc_1};
    struct Space_List const* arg_43 = list_6;
    struct Ty_List const* arg_44 = xs_6;
    f_ = arg_42;
    acc_1 = arg_43;
    xs_5 = arg_44;
    goto tailrec_21;
next_24:;
    exit(1);
end_match_22:;
    return match_5;
}

struct Space_List const* go_16(struct Pat_Space_Fun1 f_, struct Space_List const* acc_1, struct Pat_List const* xs_5) {
tailrec_25:;
    struct Space_List const* match_6;
    if ((!((!(xs_5))))) goto next_27;
    struct Space_List const* call_6 = listRev_2(acc_1);
    match_6 = call_6;
    goto end_match_26;
next_27:;
    if ((!(xs_5))) goto next_28;
    struct Pat_ x_3 = xs_5->head;
    struct Pat_List const* xs_6 = xs_5->tail;
    struct Pat_Space_Fun1 arg_45 = f_;
    struct Space_ app_2 = f_.fun(f_.env, x_3);
    struct Space_List const* list_7 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_7))) = (struct Space_List){.head = app_2, .tail = acc_1};
    struct Space_List const* arg_46 = list_7;
    struct Pat_List const* arg_47 = xs_6;
    f_ = arg_45;
    acc_1 = arg_46;
    xs_5 = arg_47;
    goto tailrec_25;
next_28:;
    exit(1);
end_match_26:;
    return match_6;
}

struct BoolList const* go_15(struct StringSpace_Tuple2BoolFun1 f_, struct BoolList const* acc_1, struct StringSpace_Tuple2List const* xs_5) {
tailrec_29:;
    struct BoolList const* match_7;
    if ((!((!(xs_5))))) goto next_31;
    struct BoolList const* call_7 = listRev_4(acc_1);
    match_7 = call_7;
    goto end_match_30;
next_31:;
    if ((!(xs_5))) goto next_32;
    struct StringSpace_Tuple2 x_3 = xs_5->head;
    struct StringSpace_Tuple2List const* xs_6 = xs_5->tail;
    struct StringSpace_Tuple2BoolFun1 arg_48 = f_;
    bool app_3 = f_.fun(f_.env, x_3);
    struct BoolList const* list_8 = milone_mem_alloc(1, sizeof(struct BoolList));
    (*(((struct BoolList*)list_8))) = (struct BoolList){.head = app_3, .tail = acc_1};
    struct BoolList const* arg_49 = list_8;
    struct StringSpace_Tuple2List const* arg_50 = xs_6;
    f_ = arg_48;
    acc_1 = arg_49;
    xs_5 = arg_50;
    goto tailrec_29;
next_32:;
    exit(1);
end_match_30:;
    return match_7;
}

struct BoolList const* go_14(struct StringTy_Pat_ListCovering_Tuple4BoolFun1 f_, struct BoolList const* acc_1, struct StringTy_Pat_ListCovering_Tuple4List const* xs_5) {
tailrec_33:;
    struct BoolList const* match_8;
    if ((!((!(xs_5))))) goto next_35;
    struct BoolList const* call_8 = listRev_4(acc_1);
    match_8 = call_8;
    goto end_match_34;
next_35:;
    if ((!(xs_5))) goto next_36;
    struct StringTy_Pat_ListCovering_Tuple4 x_3 = xs_5->head;
    struct StringTy_Pat_ListCovering_Tuple4List const* xs_6 = xs_5->tail;
    struct StringTy_Pat_ListCovering_Tuple4BoolFun1 arg_51 = f_;
    bool app_4 = f_.fun(f_.env, x_3);
    struct BoolList const* list_9 = milone_mem_alloc(1, sizeof(struct BoolList));
    (*(((struct BoolList*)list_9))) = (struct BoolList){.head = app_4, .tail = acc_1};
    struct BoolList const* arg_52 = list_9;
    struct StringTy_Pat_ListCovering_Tuple4List const* arg_53 = xs_6;
    f_ = arg_51;
    acc_1 = arg_52;
    xs_5 = arg_53;
    goto tailrec_33;
next_36:;
    exit(1);
end_match_34:;
    return match_8;
}

struct Space_List const* listMap_5(struct Space_Space_Fun1 f_, struct Space_List const* xs_4) {
    struct Space_List const* call_9 = go_18(f_, NULL, xs_4);
    return call_9;
}

struct Space_List const* listMap_4(struct Ty_Space_Fun1 f_, struct Ty_List const* xs_4) {
    struct Space_List const* call_10 = go_17(f_, NULL, xs_4);
    return call_10;
}

struct Space_List const* listMap_3(struct Pat_Space_Fun1 f_, struct Pat_List const* xs_4) {
    struct Space_List const* call_11 = go_16(f_, NULL, xs_4);
    return call_11;
}

struct BoolList const* listMap_2(struct StringSpace_Tuple2BoolFun1 f_, struct StringSpace_Tuple2List const* xs_4) {
    struct BoolList const* call_12 = go_15(f_, NULL, xs_4);
    return call_12;
}

struct BoolList const* listMap_1(struct StringTy_Pat_ListCovering_Tuple4BoolFun1 f_, struct StringTy_Pat_ListCovering_Tuple4List const* xs_4) {
    struct BoolList const* call_13 = go_14(f_, NULL, xs_4);
    return call_13;
}

struct Space_List const* go_20(struct IntSpace_Space_Tuple2Space_Fun2 f_1, struct Space_List const* acc_2, int i_, struct Space_Space_Tuple2List const* xs_8) {
tailrec_37:;
    struct Space_List const* match_9;
    if ((!((!(xs_8))))) goto next_39;
    struct Space_List const* call_14 = listRev_2(acc_2);
    match_9 = call_14;
    goto end_match_38;
next_39:;
    if ((!(xs_8))) goto next_40;
    struct Space_Space_Tuple2 x_4 = xs_8->head;
    struct Space_Space_Tuple2List const* xs_9 = xs_8->tail;
    struct IntSpace_Space_Tuple2Space_Fun2 arg_54 = f_1;
    struct Space_ app_5 = f_1.fun(f_1.env, i_, x_4);
    struct Space_List const* list_10 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_10))) = (struct Space_List){.head = app_5, .tail = acc_2};
    struct Space_List const* arg_55 = list_10;
    int arg_56 = (i_ + 1);
    struct Space_Space_Tuple2List const* arg_57 = xs_9;
    f_1 = arg_54;
    acc_2 = arg_55;
    i_ = arg_56;
    xs_8 = arg_57;
    goto tailrec_37;
next_40:;
    exit(1);
end_match_38:;
    return match_9;
}

struct Space_List const* go_19(struct IntSpace_Space_Fun2 f_1, struct Space_List const* acc_2, int i_, struct Space_List const* xs_8) {
tailrec_41:;
    struct Space_List const* match_10;
    if ((!((!(xs_8))))) goto next_43;
    struct Space_List const* call_15 = listRev_2(acc_2);
    match_10 = call_15;
    goto end_match_42;
next_43:;
    if ((!(xs_8))) goto next_44;
    struct Space_ x_4 = xs_8->head;
    struct Space_List const* xs_9 = xs_8->tail;
    struct IntSpace_Space_Fun2 arg_58 = f_1;
    struct Space_ app_6 = f_1.fun(f_1.env, i_, x_4);
    struct Space_List const* list_11 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_11))) = (struct Space_List){.head = app_6, .tail = acc_2};
    struct Space_List const* arg_59 = list_11;
    int arg_60 = (i_ + 1);
    struct Space_List const* arg_61 = xs_9;
    f_1 = arg_58;
    acc_2 = arg_59;
    i_ = arg_60;
    xs_8 = arg_61;
    goto tailrec_41;
next_44:;
    exit(1);
end_match_42:;
    return match_10;
}

struct Space_List const* listMapWithIndex_2(struct IntSpace_Space_Tuple2Space_Fun2 f_1, struct Space_Space_Tuple2List const* xs_7) {
    struct Space_List const* call_16 = go_20(f_1, NULL, 0, xs_7);
    return call_16;
}

struct Space_List const* listMapWithIndex_1(struct IntSpace_Space_Fun2 f_1, struct Space_List const* xs_7) {
    struct Space_List const* call_17 = go_19(f_1, NULL, 0, xs_7);
    return call_17;
}

bool go_23(struct Space_BoolFun1 p_, struct Space_List const* xs_11) {
tailrec_45:;
    bool match_11;
    if ((!((!(xs_11))))) goto next_47;
    match_11 = true;
    goto end_match_46;
next_47:;
    if ((!(xs_11))) goto next_48;
    struct Space_ x_5 = xs_11->head;
    struct Space_List const* xs_12 = xs_11->tail;
    bool app_7 = p_.fun(p_.env, x_5);
    bool if_;
    if (app_7) {
        goto then_50;
    } else {
        goto else_51;
    }
then_50:;
    struct Space_BoolFun1 arg_62 = p_;
    struct Space_List const* arg_63 = xs_12;
    p_ = arg_62;
    xs_11 = arg_63;
    goto tailrec_45;
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

bool go_22(struct Space_Space_Tuple2BoolFun1 p_, struct Space_Space_Tuple2List const* xs_11) {
tailrec_52:;
    bool match_12;
    if ((!((!(xs_11))))) goto next_54;
    match_12 = true;
    goto end_match_53;
next_54:;
    if ((!(xs_11))) goto next_55;
    struct Space_Space_Tuple2 x_5 = xs_11->head;
    struct Space_Space_Tuple2List const* xs_12 = xs_11->tail;
    bool app_8 = p_.fun(p_.env, x_5);
    bool if_1;
    if (app_8) {
        goto then_57;
    } else {
        goto else_58;
    }
then_57:;
    struct Space_Space_Tuple2BoolFun1 arg_64 = p_;
    struct Space_Space_Tuple2List const* arg_65 = xs_12;
    p_ = arg_64;
    xs_11 = arg_65;
    goto tailrec_52;
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

bool go_21(struct BoolBoolFun1 p_, struct BoolList const* xs_11) {
tailrec_59:;
    bool match_13;
    if ((!((!(xs_11))))) goto next_61;
    match_13 = true;
    goto end_match_60;
next_61:;
    if ((!(xs_11))) goto next_62;
    bool x_5 = xs_11->head;
    struct BoolList const* xs_12 = xs_11->tail;
    bool app_9 = p_.fun(p_.env, x_5);
    bool if_2;
    if (app_9) {
        goto then_64;
    } else {
        goto else_65;
    }
then_64:;
    struct BoolBoolFun1 arg_66 = p_;
    struct BoolList const* arg_67 = xs_12;
    p_ = arg_66;
    xs_11 = arg_67;
    goto tailrec_59;
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

bool listForAll_3(struct Space_BoolFun1 p_, struct Space_List const* xs_10) {
    bool call_18 = go_23(p_, xs_10);
    return call_18;
}

bool listForAll_2(struct Space_Space_Tuple2BoolFun1 p_, struct Space_Space_Tuple2List const* xs_10) {
    bool call_19 = go_22(p_, xs_10);
    return call_19;
}

bool listForAll_1(struct BoolBoolFun1 p_, struct BoolList const* xs_10) {
    bool call_20 = go_21(p_, xs_10);
    return call_20;
}

bool go_24(struct Space_BoolFun1 p_1, struct Space_List const* xs_14) {
tailrec_66:;
    bool match_14;
    if ((!((!(xs_14))))) goto next_68;
    match_14 = false;
    goto end_match_67;
next_68:;
    if ((!(xs_14))) goto next_69;
    struct Space_ x_6 = xs_14->head;
    struct Space_List const* xs_15 = xs_14->tail;
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
    struct Space_List const* arg_69 = xs_15;
    p_1 = arg_68;
    xs_14 = arg_69;
    goto tailrec_66;
if_next_70:;
    match_14 = if_3;
    goto end_match_67;
next_69:;
    exit(1);
end_match_67:;
    return match_14;
}

bool listExists_1(struct Space_BoolFun1 p_1, struct Space_List const* xs_13) {
    bool call_21 = go_24(p_1, xs_13);
    return call_21;
}

struct Space_ go_26(struct Space_Space_Space_Fun2 folder_, struct Space_ state_1, struct Space_List const* xs_17) {
tailrec_73:;
    struct Space_ match_15;
    if ((!((!(xs_17))))) goto next_75;
    match_15 = state_1;
    goto end_match_74;
next_75:;
    if ((!(xs_17))) goto next_76;
    struct Space_ x_7 = xs_17->head;
    struct Space_List const* xs_18 = xs_17->tail;
    struct Space_Space_Space_Fun2 arg_70 = folder_;
    struct Space_ app_11 = folder_.fun(folder_.env, state_1, x_7);
    struct Space_ arg_71 = app_11;
    struct Space_List const* arg_72 = xs_18;
    folder_ = arg_70;
    state_1 = arg_71;
    xs_17 = arg_72;
    goto tailrec_73;
next_76:;
    exit(1);
end_match_74:;
    return match_15;
}

struct StringList const* go_25(struct StringListSpace_StringListFun2 folder_, struct StringList const* state_1, struct Space_List const* xs_17) {
tailrec_77:;
    struct StringList const* match_16;
    if ((!((!(xs_17))))) goto next_79;
    match_16 = state_1;
    goto end_match_78;
next_79:;
    if ((!(xs_17))) goto next_80;
    struct Space_ x_7 = xs_17->head;
    struct Space_List const* xs_18 = xs_17->tail;
    struct StringListSpace_StringListFun2 arg_73 = folder_;
    struct StringList const* app_12 = folder_.fun(folder_.env, state_1, x_7);
    struct StringList const* arg_74 = app_12;
    struct Space_List const* arg_75 = xs_18;
    folder_ = arg_73;
    state_1 = arg_74;
    xs_17 = arg_75;
    goto tailrec_77;
next_80:;
    exit(1);
end_match_78:;
    return match_16;
}

struct Space_ listFold_2(struct Space_Space_Space_Fun2 folder_, struct Space_ state_, struct Space_List const* xs_16) {
    struct Space_ call_22 = go_26(folder_, state_, xs_16);
    return call_22;
}

struct StringList const* listFold_1(struct StringListSpace_StringListFun2 folder_, struct StringList const* state_, struct Space_List const* xs_16) {
    struct StringList const* call_23 = go_25(folder_, state_, xs_16);
    return call_23;
}

struct Space_Space_Tuple2List const* go_27(struct Space_Space_Tuple2List const* acc_3, struct Space_List const* xs_20, struct Space_List const* ys_1) {
tailrec_81:;
    struct Space_Space_Tuple2List const* match_17;
    struct Space_ListSpace_ListTuple2 tuple_ = (struct Space_ListSpace_ListTuple2){.t0 = xs_20, .t1 = ys_1};
    if ((!((!(tuple_.t0))))) goto next_84;
    goto match_body_83;
next_84:;
    if ((!((!(tuple_.t1))))) goto next_85;
    goto match_body_83;
match_body_83:;
    struct Space_Space_Tuple2List const* call_24 = listRev_3(acc_3);
    match_17 = call_24;
    goto end_match_82;
next_85:;
    if ((!(tuple_.t0))) goto next_86;
    struct Space_ x_8 = tuple_.t0->head;
    struct Space_List const* xs_21 = tuple_.t0->tail;
    if ((!(tuple_.t1))) goto next_86;
    struct Space_ y_ = tuple_.t1->head;
    struct Space_List const* ys_2 = tuple_.t1->tail;
    struct Space_Space_Tuple2 tuple_1 = (struct Space_Space_Tuple2){.t0 = x_8, .t1 = y_};
    struct Space_Space_Tuple2List const* list_12 = milone_mem_alloc(1, sizeof(struct Space_Space_Tuple2List));
    (*(((struct Space_Space_Tuple2List*)list_12))) = (struct Space_Space_Tuple2List){.head = tuple_1, .tail = acc_3};
    struct Space_Space_Tuple2List const* arg_76 = list_12;
    struct Space_List const* arg_77 = xs_21;
    struct Space_List const* arg_78 = ys_2;
    acc_3 = arg_76;
    xs_20 = arg_77;
    ys_1 = arg_78;
    goto tailrec_81;
next_86:;
    exit(1);
end_match_82:;
    return match_17;
}

struct Space_Space_Tuple2List const* listZip_1(struct Space_List const* xs_19, struct Space_List const* ys_) {
    struct Space_Space_Tuple2List const* call_25 = go_27(NULL, xs_19, ys_);
    return call_25;
}

struct String go_7(struct StringList const* xs_23) {
    struct String match_18;
    if ((!((!(xs_23))))) goto next_88;
    match_18 = (struct String){.str = "", .len = 0};
    goto end_match_87;
next_88:;
    if ((!(xs_23))) goto next_89;
    struct String x_9 = xs_23->head;
    struct StringList const* xs_24 = xs_23->tail;
    struct String call_26 = go_7(xs_24);
    match_18 = str_add(x_9, call_26);
    goto end_match_87;
next_89:;
    exit(1);
end_match_87:;
    return match_18;
}

struct String strConcat_(struct StringList const* xs_22) {
    struct String call_27 = go_7(xs_22);
    return call_27;
}

struct Space_ spaceCtor_(struct String tag_, struct Space_List const* items_) {
    struct StringSpace_ListTuple2 tuple_2 = (struct StringSpace_ListTuple2){.t0 = tag_, .t1 = items_};
    struct Space_ variant_ = (struct Space_){.discriminant = Ctor_, .Ctor_ = tuple_2};
    return variant_;
}

struct Space_ spaceRef_(struct String tag_1, struct UnitSpace_Fun1 thunk_) {
    struct StringUnitSpace_Fun1Tuple2 tuple_3 = (struct StringUnitSpace_Fun1Tuple2){.t0 = tag_1, .t1 = thunk_};
    void const* box_ = milone_mem_alloc(1, sizeof(struct StringUnitSpace_Fun1Tuple2));
    (*(((struct StringUnitSpace_Fun1Tuple2*)box_))) = tuple_3;
    struct Space_ variant_1 = (struct Space_){.discriminant = Ref_, .Ref_ = box_};
    return variant_1;
}

struct Space_List const* go_8(struct Space_List const* spaces_1, struct Space_List const* acc_4) {
tailrec_90:;
    struct Space_List const* match_19;
    if ((!((!(spaces_1))))) goto next_92;
    struct Space_List const* call_28 = listRev_2(acc_4);
    match_19 = call_28;
    goto end_match_91;
next_92:;
    if ((!(spaces_1))) goto next_93;
    if ((spaces_1->head.discriminant != Union_)) goto next_93;
    struct Space_List const* subspaces_ = spaces_1->head.Union_;
    struct Space_List const* spaces_2 = spaces_1->tail;
    struct Space_List const* arg_79 = spaces_2;
    struct Space_List const* call_29 = go_8(subspaces_, acc_4);
    struct Space_List const* arg_80 = call_29;
    spaces_1 = arg_79;
    acc_4 = arg_80;
    goto tailrec_90;
next_93:;
    if ((!(spaces_1))) goto next_94;
    struct Space_ space_ = spaces_1->head;
    struct Space_List const* spaces_3 = spaces_1->tail;
    bool call_30 = spaceIsEmpty_(space_);
    if ((!(call_30))) goto next_94;
    struct Space_List const* arg_81 = spaces_3;
    struct Space_List const* arg_82 = acc_4;
    spaces_1 = arg_81;
    acc_4 = arg_82;
    goto tailrec_90;
next_94:;
    if ((!(spaces_1))) goto next_95;
    struct Space_ space_1 = spaces_1->head;
    struct Space_List const* spaces_4 = spaces_1->tail;
    struct Space_List const* arg_83 = spaces_4;
    struct Space_List const* list_13 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_13))) = (struct Space_List){.head = space_1, .tail = acc_4};
    struct Space_List const* arg_84 = list_13;
    spaces_1 = arg_83;
    acc_4 = arg_84;
    goto tailrec_90;
next_95:;
    struct Space_List const* call_31 = failwith_3((struct String){.str = "NEVER: suppress warning", .len = 23});
    match_19 = call_31;
    goto end_match_91;
next_96:;
end_match_91:;
    return match_19;
}

struct Space_ spaceUnion_(struct Space_List const* spaces_) {
    struct Space_ match_20;
    struct Space_List const* call_32 = go_8(spaces_, NULL);
    if ((!(call_32))) goto next_98;
    struct Space_ space_2 = call_32->head;
    if ((!((!(call_32->tail))))) goto next_98;
    match_20 = space_2;
    goto end_match_97;
next_98:;
    struct Space_List const* spaces_5 = call_32;
    struct Space_ variant_2 = (struct Space_){.discriminant = Union_, .Union_ = spaces_5};
    match_20 = variant_2;
    goto end_match_97;
next_99:;
end_match_97:;
    return match_20;
}

bool fun_9(void const* env_, struct Space_ arg_) {
    bool call_33 = spaceIsEmpty_(arg_);
    return call_33;
}

bool fun_10(void const* env_1, struct Space_ arg_1) {
    bool call_34 = spaceIsEmpty_(arg_1);
    return call_34;
}

bool spaceIsEmpty_(struct Space_ space_3) {
    bool match_21;
    if ((space_3.discriminant != Ctor_)) goto next_101;
    struct Space_List const* spaces_6 = space_3.Ctor_.t1;
    struct Space_BoolFun1 fun_29 = (struct Space_BoolFun1){.fun = fun_9, .env = NULL};
    bool call_35 = listExists_1(fun_29, spaces_6);
    match_21 = call_35;
    goto end_match_100;
next_101:;
    if ((space_3.discriminant != Union_)) goto next_102;
    struct Space_List const* spaces_7 = space_3.Union_;
    struct Space_BoolFun1 fun_30 = (struct Space_BoolFun1){.fun = fun_10, .env = NULL};
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
    if ((space_4.discriminant != Ref_)) goto next_105;
    struct UnitSpace_Fun1 thunk_1 = (*(((struct StringUnitSpace_Fun1Tuple2 const*)space_4.Ref_))).t1;
    struct Space_ app_13 = thunk_1.fun(thunk_1.env, 0);
    struct Space_ space_5 = app_13;
    bool call_37 = spaceIsEmpty_(space_5);
    milone_assert((!(call_37)), 201, 6);
    match_22 = space_5;
    goto end_match_104;
next_105:;
    milone_assert(false, 205, 6);
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

bool fun_11(void const* env_2, struct Space_Space_Tuple2 arg_2) {
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

struct Space_ fun_12(void const* env_3, int arg_3, struct Space_Space_Tuple2 arg_4) {
    int arg_5 = (*(((struct IntTuple1 const*)env_3))).t0;
    struct Space_ call_41 = fun_2(arg_5, arg_3, arg_4);
    return call_41;
}

struct Space_ fun_28(struct String tag_2, struct Space_List const* firsts_, struct Space_List const* seconds_, int i_1, struct Space_ arg_87) {
    struct IntTuple1 tuple_4 = (struct IntTuple1){.t0 = i_1};
    void const* box_1 = milone_mem_alloc(1, sizeof(struct IntTuple1));
    (*(((struct IntTuple1*)box_1))) = tuple_4;
    struct IntSpace_Space_Tuple2Space_Fun2 fun_31 = (struct IntSpace_Space_Tuple2Space_Fun2){.fun = fun_12, .env = box_1};
    struct Space_Space_Tuple2List const* call_42 = listZip_1(firsts_, seconds_);
    struct Space_List const* call_43 = listMapWithIndex_2(fun_31, call_42);
    struct Space_ call_44 = spaceCtor_(tag_2, call_43);
    return call_44;
}

struct Space_ fun_13(void const* env_4, int arg_6, struct Space_ arg_7) {
    struct String arg_8 = (*(((struct StringSpace_ListSpace_ListTuple3 const*)env_4))).t0;
    struct Space_List const* arg_9 = (*(((struct StringSpace_ListSpace_ListTuple3 const*)env_4))).t1;
    struct Space_List const* arg_10 = (*(((struct StringSpace_ListSpace_ListTuple3 const*)env_4))).t2;
    struct Space_ call_45 = fun_28(arg_8, arg_9, arg_10, arg_6, arg_7);
    return call_45;
}

struct Space_ fun_14(void const* env_5, struct Space_ arg_11, struct Space_ arg_12) {
    struct Space_ call_46 = spaceExclude_(arg_11, arg_12);
    return call_46;
}

struct Space_ fun_3(struct Space_ second_, struct Space_ first_3) {
    struct Space_ call_47 = spaceExclude_(first_3, second_);
    return call_47;
}

struct Space_ fun_15(void const* env_6, struct Space_ arg_13) {
    struct Space_ arg_14 = (*(((struct Space_Tuple1 const*)env_6))).t0;
    struct Space_ call_48 = fun_3(arg_14, arg_13);
    return call_48;
}

struct Space_ spaceExclude_(struct Space_ first_, struct Space_ second_) {
tailrec_110:;
    struct Space_ match_23;
    struct Space_Space_Tuple2 tuple_5 = (struct Space_Space_Tuple2){.t0 = first_, .t1 = second_};
    if ((tuple_5.t0.discriminant != Union_)) goto next_112;
    if ((!((!(tuple_5.t0.Union_))))) goto next_112;
    match_23 = spaceEmpty_;
    goto end_match_111;
next_112:;
    if ((tuple_5.t1.discriminant != Union_)) goto next_113;
    if ((!((!(tuple_5.t1.Union_))))) goto next_113;
    match_23 = first_;
    goto end_match_111;
next_113:;
    if ((tuple_5.t1.discriminant != Full_)) goto next_114;
    match_23 = spaceEmpty_;
    goto end_match_111;
next_114:;
    if ((tuple_5.t0.discriminant != Full_)) goto next_115;
    if ((tuple_5.t1.discriminant != Ctor_)) goto next_115;
    match_23 = spaceFull_;
    goto end_match_111;
next_115:;
    if ((tuple_5.t0.discriminant != Ctor_)) goto next_116;
    struct String tag_2 = tuple_5.t0.Ctor_.t0;
    struct Space_List const* firsts_ = tuple_5.t0.Ctor_.t1;
    if ((tuple_5.t1.discriminant != Ctor_)) goto next_116;
    struct String secondTag_ = tuple_5.t1.Ctor_.t0;
    struct Space_List const* seconds_ = tuple_5.t1.Ctor_.t1;
    if ((str_compare(tag_2, secondTag_) != 0)) goto next_116;
    struct Space_Space_Tuple2BoolFun1 fun_32 = (struct Space_Space_Tuple2BoolFun1){.fun = fun_11, .env = NULL};
    struct Space_Space_Tuple2List const* call_49 = listZip_1(firsts_, seconds_);
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
    struct StringSpace_ListSpace_ListTuple3 tuple_6 = (struct StringSpace_ListSpace_ListTuple3){.t0 = tag_2, .t1 = firsts_, .t2 = seconds_};
    void const* box_2 = milone_mem_alloc(1, sizeof(struct StringSpace_ListSpace_ListTuple3));
    (*(((struct StringSpace_ListSpace_ListTuple3*)box_2))) = tuple_6;
    struct IntSpace_Space_Fun2 fun_33 = (struct IntSpace_Space_Fun2){.fun = fun_13, .env = box_2};
    struct Space_List const* call_51 = listMapWithIndex_1(fun_33, firsts_);
    struct Space_ call_52 = spaceUnion_(call_51);
    if_5 = call_52;
    goto if_next_123;
if_next_123:;
    match_23 = if_5;
    goto end_match_111;
next_116:;
    if ((tuple_5.t0.discriminant != Ctor_)) goto next_117;
    if ((tuple_5.t1.discriminant != Ctor_)) goto next_117;
    match_23 = first_;
    goto end_match_111;
next_117:;
    if ((tuple_5.t1.discriminant != Union_)) goto next_118;
    struct Space_List const* seconds_1 = tuple_5.t1.Union_;
    struct Space_Space_Space_Fun2 fun_34 = (struct Space_Space_Space_Fun2){.fun = fun_14, .env = NULL};
    struct Space_ call_53 = listFold_2(fun_34, first_, seconds_1);
    match_23 = call_53;
    goto end_match_111;
next_118:;
    if ((tuple_5.t0.discriminant != Union_)) goto next_119;
    struct Space_List const* firsts_1 = tuple_5.t0.Union_;
    struct Space_Tuple1 tuple_7 = (struct Space_Tuple1){.t0 = second_};
    void const* box_3 = milone_mem_alloc(1, sizeof(struct Space_Tuple1));
    (*(((struct Space_Tuple1*)box_3))) = tuple_7;
    struct Space_Space_Fun1 fun_35 = (struct Space_Space_Fun1){.fun = fun_15, .env = box_3};
    struct Space_List const* call_54 = listMap_5(fun_35, firsts_1);
    struct Space_ call_55 = spaceUnion_(call_54);
    match_23 = call_55;
    goto end_match_111;
next_119:;
    if ((tuple_5.t0.discriminant != Ref_)) goto next_120;
    struct String tag_3 = (*(((struct StringUnitSpace_Fun1Tuple2 const*)tuple_5.t0.Ref_))).t0;
    if ((tuple_5.t1.discriminant != Ref_)) goto next_120;
    struct String secondTag_1 = (*(((struct StringUnitSpace_Fun1Tuple2 const*)tuple_5.t1.Ref_))).t0;
    if ((str_compare(tag_3, secondTag_1) != 0)) goto next_120;
    match_23 = spaceEmpty_;
    goto end_match_111;
next_120:;
    if ((tuple_5.t0.discriminant != Ref_)) goto next_121;
    struct Space_ call_56 = spaceDecompose_(first_);
    struct Space_ arg_88 = call_56;
    struct Space_ arg_89 = second_;
    first_ = arg_88;
    second_ = arg_89;
    goto tailrec_110;
next_121:;
    if ((tuple_5.t1.discriminant != Ref_)) goto next_122;
    milone_assert(false, 307, 6);
    struct Space_ arg_90 = first_;
    struct Space_ call_57 = spaceDecompose_(second_);
    struct Space_ arg_91 = call_57;
    first_ = arg_90;
    second_ = arg_91;
    goto tailrec_110;
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

struct StringList const* fun_4(struct StringList const* acc_7, struct Space_ space_8) {
    struct StringList const* call_60 = cons_1((struct String){.str = ", ", .len = 2}, acc_7);
    struct StringList const* call_61 = go_9(space_8, call_60);
    return call_61;
}

struct StringList const* fun_16(void const* env_7, struct StringList const* arg_15, struct Space_ arg_16) {
    struct StringList const* call_62 = fun_4(arg_15, arg_16);
    return call_62;
}

struct StringList const* fun_5(struct StringList const* acc_9, struct Space_ space_9) {
    struct StringList const* call_63 = cons_1((struct String){.str = ", ", .len = 2}, acc_9);
    struct StringList const* call_64 = go_9(space_9, call_63);
    return call_64;
}

struct StringList const* fun_17(void const* env_8, struct StringList const* arg_17, struct Space_ arg_18) {
    struct StringList const* call_65 = fun_5(arg_17, arg_18);
    return call_65;
}

struct StringList const* go_9(struct Space_ space_7, struct StringList const* acc_5) {
    struct StringList const* match_24;
    if ((space_7.discriminant != Full_)) goto next_127;
    struct StringList const* call_66 = cons_1((struct String){.str = "full", .len = 4}, acc_5);
    match_24 = call_66;
    goto end_match_126;
next_127:;
    if ((space_7.discriminant != Ctor_)) goto next_128;
    struct String tag_4 = space_7.Ctor_.t0;
    if ((!((!(space_7.Ctor_.t1))))) goto next_128;
    struct StringList const* call_67 = cons_1(tag_4, acc_5);
    match_24 = call_67;
    goto end_match_126;
next_128:;
    if ((space_7.discriminant != Ctor_)) goto next_129;
    struct String tag_5 = space_7.Ctor_.t0;
    if ((!(space_7.Ctor_.t1))) goto next_129;
    struct Space_ item_ = space_7.Ctor_.t1->head;
    struct Space_List const* items_1 = space_7.Ctor_.t1->tail;
    struct StringList const* call_68 = cons_1(tag_5, acc_5);
    struct StringList const* call_69 = cons_1((struct String){.str = "(", .len = 1}, call_68);
    struct StringList const* call_70 = go_9(item_, call_69);
    struct StringList const* acc_6 = call_70;
    struct StringListSpace_StringListFun2 fun_36 = (struct StringListSpace_StringListFun2){.fun = fun_16, .env = NULL};
    struct StringList const* call_71 = listFold_1(fun_36, acc_6, items_1);
    struct StringList const* call_72 = cons_1((struct String){.str = ")", .len = 1}, call_71);
    match_24 = call_72;
    goto end_match_126;
next_129:;
    if ((space_7.discriminant != Ref_)) goto next_130;
    struct String tag_6 = (*(((struct StringUnitSpace_Fun1Tuple2 const*)space_7.Ref_))).t0;
    struct StringList const* call_73 = cons_1(tag_6, acc_5);
    match_24 = call_73;
    goto end_match_126;
next_130:;
    if ((space_7.discriminant != Union_)) goto next_131;
    if ((!((!(space_7.Union_))))) goto next_131;
    struct StringList const* call_74 = cons_1((struct String){.str = "empty", .len = 5}, acc_5);
    match_24 = call_74;
    goto end_match_126;
next_131:;
    if ((space_7.discriminant != Union_)) goto next_132;
    if ((!(space_7.Union_))) goto next_132;
    struct Space_ subspace_ = space_7.Union_->head;
    struct Space_List const* subspaces_1 = space_7.Union_->tail;
    struct StringList const* call_75 = cons_1((struct String){.str = "+(", .len = 2}, acc_5);
    struct StringList const* call_76 = go_9(subspace_, call_75);
    struct StringList const* acc_8 = call_76;
    struct StringListSpace_StringListFun2 fun_37 = (struct StringListSpace_StringListFun2){.fun = fun_17, .env = NULL};
    struct StringList const* call_77 = listFold_1(fun_37, acc_8, subspaces_1);
    struct StringList const* call_78 = cons_1((struct String){.str = ")", .len = 1}, call_77);
    match_24 = call_78;
    goto end_match_126;
next_132:;
    struct StringList const* call_79 = failwith_2((struct String){.str = "NEVER: suppress warning", .len = 23});
    match_24 = call_79;
    goto end_match_126;
next_133:;
end_match_126:;
    return match_24;
}

struct String spaceToString_(struct Space_ space_6) {
    struct StringList const* call_80 = go_9(space_6, NULL);
    struct StringList const* call_81 = listRev_1(call_80);
    struct String call_82 = strConcat_(call_81);
    return call_82;
}

struct Space_ fun_18(void const* env_9, struct Ty_ arg_19) {
    struct Space_ call_83 = go_10(arg_19);
    return call_83;
}

struct Space_ fun_19(void const* env_10, char arg_20) {
    struct Space_ arg_21 = (*(((struct Space_Tuple1 const*)env_10))).t0;
    struct Space_ call_84 = thunk_2(arg_21, 0);
    return call_84;
}

struct Space_ thunk_2(struct Space_ itemSpace_, char arg_92) {
    struct Space_ call_85 = spaceCtor_((struct String){.str = "nil", .len = 3}, NULL);
    struct Space_Tuple1 tuple_8 = (struct Space_Tuple1){.t0 = itemSpace_};
    void const* box_4 = milone_mem_alloc(1, sizeof(struct Space_Tuple1));
    (*(((struct Space_Tuple1*)box_4))) = tuple_8;
    struct UnitSpace_Fun1 fun_38 = (struct UnitSpace_Fun1){.fun = fun_19, .env = box_4};
    struct Space_ call_86 = spaceRef_((struct String){.str = "list", .len = 4}, fun_38);
    struct Space_List const* list_17 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_17))) = (struct Space_List){.head = call_86, .tail = NULL};
    struct Space_List const* list_16 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_16))) = (struct Space_List){.head = itemSpace_, .tail = list_17};
    struct Space_ call_87 = spaceCtor_((struct String){.str = "cons", .len = 4}, list_16);
    struct Space_List const* list_15 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_15))) = (struct Space_List){.head = call_87, .tail = NULL};
    struct Space_List const* list_14 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_14))) = (struct Space_List){.head = call_85, .tail = list_15};
    struct Space_ call_88 = spaceUnion_(list_14);
    return call_88;
}

struct Space_ fun_20(void const* env_11, char arg_22) {
    struct Space_ arg_23 = (*(((struct Space_Tuple1 const*)env_11))).t0;
    struct Space_ call_89 = thunk_2(arg_23, 0);
    return call_89;
}

struct Space_ go_10(struct Ty_ ty_1) {
    struct Space_ match_25;
    if ((ty_1.discriminant != Int_)) goto next_135;
    match_25 = spaceFull_;
    goto end_match_134;
next_135:;
    if ((ty_1.discriminant != Tuple_)) goto next_136;
    struct Ty_List const* itemTys_ = ty_1.Tuple_;
    struct Ty_Space_Fun1 fun_39 = (struct Ty_Space_Fun1){.fun = fun_18, .env = NULL};
    struct Space_List const* call_90 = listMap_4(fun_39, itemTys_);
    struct Space_ call_91 = spaceCtor_((struct String){.str = "tuple", .len = 5}, call_90);
    match_25 = call_91;
    goto end_match_134;
next_136:;
    if ((ty_1.discriminant != List_)) goto next_137;
    struct Ty_ itemTy_ = (*(((struct Ty_ const*)ty_1.List_)));
    struct Space_ call_92 = go_10(itemTy_);
    struct Space_ itemSpace_ = call_92;
    struct Space_Tuple1 tuple_9 = (struct Space_Tuple1){.t0 = itemSpace_};
    void const* box_5 = milone_mem_alloc(1, sizeof(struct Space_Tuple1));
    (*(((struct Space_Tuple1*)box_5))) = tuple_9;
    struct UnitSpace_Fun1 fun_40 = (struct UnitSpace_Fun1){.fun = fun_20, .env = box_5};
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

struct Space_ fun_21(void const* env_12, struct Pat_ arg_24) {
    struct Space_ call_95 = go_11(arg_24);
    return call_95;
}

struct Space_ go_11(struct Pat_ pat_1) {
    struct Space_ match_26;
    if ((pat_1.discriminant != Discard_)) goto next_139;
    match_26 = spaceFull_;
    goto end_match_138;
next_139:;
    if ((pat_1.discriminant != IntLit_)) goto next_140;
    match_26 = spaceEmpty_;
    goto end_match_138;
next_140:;
    if ((pat_1.discriminant != TupleLit_)) goto next_141;
    struct Pat_List const* itemPats_ = pat_1.TupleLit_;
    struct Pat_Space_Fun1 fun_41 = (struct Pat_Space_Fun1){.fun = fun_21, .env = NULL};
    struct Space_List const* call_96 = listMap_3(fun_41, itemPats_);
    struct Space_ call_97 = spaceCtor_((struct String){.str = "tuple", .len = 5}, call_96);
    match_26 = call_97;
    goto end_match_138;
next_141:;
    if ((pat_1.discriminant != Nil_)) goto next_142;
    struct Space_ call_98 = spaceCtor_((struct String){.str = "nil", .len = 3}, NULL);
    match_26 = call_98;
    goto end_match_138;
next_142:;
    if ((pat_1.discriminant != Cons_)) goto next_143;
    struct Pat_ headPat_ = (*(((struct Pat_Pat_Tuple2 const*)pat_1.Cons_))).t0;
    struct Pat_ tailPat_ = (*(((struct Pat_Pat_Tuple2 const*)pat_1.Cons_))).t1;
    struct Space_ call_99 = go_11(headPat_);
    struct Space_ call_100 = go_11(tailPat_);
    struct Space_List const* list_19 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_19))) = (struct Space_List){.head = call_100, .tail = NULL};
    struct Space_List const* list_18 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_18))) = (struct Space_List){.head = call_99, .tail = list_19};
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

struct Space_ fun_22(void const* env_13, struct Pat_ arg_25) {
    struct Space_ call_104 = patToSpace_(arg_25);
    return call_104;
}

struct Space_ patsToSpace_(struct Pat_List const* pats_) {
    struct Pat_Space_Fun1 fun_42 = (struct Pat_Space_Fun1){.fun = fun_22, .env = NULL};
    struct Space_List const* call_105 = listMap_3(fun_42, pats_);
    struct Space_ call_106 = spaceUnion_(call_105);
    return call_106;
}

struct Space_ fun_6(char arg_93) {
    return spaceFull_;
}

struct Space_ fun_23(void const* env_14, char arg_26) {
    struct Space_ call_107 = fun_6(0);
    return call_107;
}

char testSpaceIsEmpty_(char arg_94) {
    bool call_108 = spaceIsEmpty_(spaceEmpty_);
    milone_assert(call_108, 398, 2);
    struct Space_List const* list_22 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_22))) = (struct Space_List){.head = spaceEmpty_, .tail = NULL};
    struct Space_ call_109 = spaceUnion_(list_22);
    struct Space_List const* list_21 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_21))) = (struct Space_List){.head = call_109, .tail = NULL};
    struct Space_List const* list_20 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_20))) = (struct Space_List){.head = spaceEmpty_, .tail = list_21};
    struct Space_ call_110 = spaceUnion_(list_20);
    bool call_111 = spaceIsEmpty_(call_110);
    milone_assert(call_111, 400, 2);
    bool call_112 = spaceIsEmpty_(spaceFull_);
    milone_assert((!(call_112)), 404, 2);
    struct UnitSpace_Fun1 fun_43 = (struct UnitSpace_Fun1){.fun = fun_23, .env = NULL};
    struct Space_ call_113 = spaceRef_((struct String){.str = "ref", .len = 3}, fun_43);
    bool call_114 = spaceIsEmpty_(call_113);
    milone_assert((!(call_114)), 406, 2);
    struct Space_List const* list_24 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_24))) = (struct Space_List){.head = spaceFull_, .tail = NULL};
    struct Space_List const* list_23 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_23))) = (struct Space_List){.head = spaceEmpty_, .tail = list_24};
    struct Space_ call_115 = spaceUnion_(list_23);
    bool call_116 = spaceIsEmpty_(call_115);
    milone_assert((!(call_116)), 410, 2);
    struct Space_ call_117 = spaceCtor_((struct String){.str = "tuple", .len = 5}, NULL);
    bool call_118 = spaceIsEmpty_(call_117);
    milone_assert((!(call_118)), 414, 2);
    struct Space_List const* list_27 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_27))) = (struct Space_List){.head = spaceFull_, .tail = NULL};
    struct Space_List const* list_26 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_26))) = (struct Space_List){.head = spaceEmpty_, .tail = list_27};
    struct Space_List const* list_25 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_25))) = (struct Space_List){.head = spaceFull_, .tail = list_26};
    struct Space_ call_119 = spaceCtor_((struct String){.str = "tuple", .len = 5}, list_25);
    bool call_120 = spaceIsEmpty_(call_119);
    milone_assert(call_120, 416, 2);
    void const* box_6 = milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_6))) = (struct Ty_){.discriminant = Int_};
    struct Ty_ variant_3 = (struct Ty_){.discriminant = List_, .List_ = box_6};
    struct Space_ call_121 = tyToSpace_(variant_3);
    bool call_122 = spaceIsEmpty_(call_121);
    milone_assert((!(call_122)), 419, 2);
    struct Ty_ variant_4 = (struct Ty_){.discriminant = Tuple_, .Tuple_ = NULL};
    void const* box_7 = milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_7))) = variant_4;
    struct Ty_ variant_5 = (struct Ty_){.discriminant = List_, .List_ = box_7};
    struct Space_ call_123 = tyToSpace_(variant_5);
    bool call_124 = spaceIsEmpty_(call_123);
    milone_assert((!(call_124)), 421, 2);
    return 0;
}

bool fun_24(void const* env_15, bool arg_27) {
    bool call_125 = id_1(arg_27);
    return call_125;
}

bool fun_7(struct StringSpace_Tuple2 arg_95) {
    struct String expected_ = arg_95.t0;
    struct Space_ space_10 = arg_95.t1;
    struct String call_126 = spaceToString_(space_10);
    struct String actual_ = call_126;
    bool if_6;
    if ((str_compare(actual_, expected_) == 0)) {
        goto then_146;
    } else {
        goto else_147;
    }
then_146:;
    if_6 = true;
    goto if_next_145;
else_147:;
    printf("%s: NG (%s)\n", str_to_c_str(expected_), str_to_c_str(actual_));
    if_6 = false;
    goto if_next_145;
if_next_145:;
    return if_6;
}

bool fun_25(void const* env_16, struct StringSpace_Tuple2 arg_28) {
    bool call_127 = fun_7(arg_28);
    return call_127;
}

char testSpaceToString_(char arg_96) {
    struct StringSpace_Tuple2 tuple_10 = (struct StringSpace_Tuple2){.t0 = (struct String){.str = "empty", .len = 5}, .t1 = spaceEmpty_};
    struct StringSpace_Tuple2 tuple_11 = (struct StringSpace_Tuple2){.t0 = (struct String){.str = "full", .len = 4}, .t1 = spaceFull_};
    struct Space_ call_128 = spaceCtor_((struct String){.str = "nil", .len = 3}, NULL);
    struct StringSpace_Tuple2 tuple_12 = (struct StringSpace_Tuple2){.t0 = (struct String){.str = "nil", .len = 3}, .t1 = call_128};
    struct Space_List const* list_33 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_33))) = (struct Space_List){.head = spaceFull_, .tail = NULL};
    struct Space_List const* list_32 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_32))) = (struct Space_List){.head = spaceEmpty_, .tail = list_33};
    struct Space_ call_129 = spaceCtor_((struct String){.str = "tuple", .len = 5}, list_32);
    struct StringSpace_Tuple2 tuple_13 = (struct StringSpace_Tuple2){.t0 = (struct String){.str = "tuple(empty, full)", .len = 18}, .t1 = call_129};
    struct Space_ call_130 = tyToSpace_((struct Ty_){.discriminant = Int_});
    struct StringSpace_Tuple2 tuple_14 = (struct StringSpace_Tuple2){.t0 = (struct String){.str = "full", .len = 4}, .t1 = call_130};
    void const* box_8 = milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_8))) = (struct Ty_){.discriminant = Int_};
    struct Ty_ variant_6 = (struct Ty_){.discriminant = List_, .List_ = box_8};
    struct Space_ call_131 = tyToSpace_(variant_6);
    struct Space_ call_132 = spaceDecompose_(call_131);
    struct StringSpace_Tuple2 tuple_15 = (struct StringSpace_Tuple2){.t0 = (struct String){.str = "+(nil, cons(full, list))", .len = 24}, .t1 = call_132};
    struct Pat_Pat_Tuple2 tuple_17 = (struct Pat_Pat_Tuple2){.t0 = (struct Pat_){.discriminant = Discard_}, .t1 = (struct Pat_){.discriminant = Nil_}};
    void const* box_9 = milone_mem_alloc(1, sizeof(struct Pat_Pat_Tuple2));
    (*(((struct Pat_Pat_Tuple2*)box_9))) = tuple_17;
    struct Pat_ variant_7 = (struct Pat_){.discriminant = Cons_, .Cons_ = box_9};
    struct Space_ call_133 = patToSpace_(variant_7);
    struct StringSpace_Tuple2 tuple_16 = (struct StringSpace_Tuple2){.t0 = (struct String){.str = "cons(full, nil)", .len = 15}, .t1 = call_133};
    struct StringSpace_Tuple2List const* list_36 = milone_mem_alloc(1, sizeof(struct StringSpace_Tuple2List));
    (*(((struct StringSpace_Tuple2List*)list_36))) = (struct StringSpace_Tuple2List){.head = tuple_16, .tail = NULL};
    struct StringSpace_Tuple2List const* list_35 = milone_mem_alloc(1, sizeof(struct StringSpace_Tuple2List));
    (*(((struct StringSpace_Tuple2List*)list_35))) = (struct StringSpace_Tuple2List){.head = tuple_15, .tail = list_36};
    struct StringSpace_Tuple2List const* list_34 = milone_mem_alloc(1, sizeof(struct StringSpace_Tuple2List));
    (*(((struct StringSpace_Tuple2List*)list_34))) = (struct StringSpace_Tuple2List){.head = tuple_14, .tail = list_35};
    struct StringSpace_Tuple2List const* list_31 = milone_mem_alloc(1, sizeof(struct StringSpace_Tuple2List));
    (*(((struct StringSpace_Tuple2List*)list_31))) = (struct StringSpace_Tuple2List){.head = tuple_13, .tail = list_34};
    struct StringSpace_Tuple2List const* list_30 = milone_mem_alloc(1, sizeof(struct StringSpace_Tuple2List));
    (*(((struct StringSpace_Tuple2List*)list_30))) = (struct StringSpace_Tuple2List){.head = tuple_12, .tail = list_31};
    struct StringSpace_Tuple2List const* list_29 = milone_mem_alloc(1, sizeof(struct StringSpace_Tuple2List));
    (*(((struct StringSpace_Tuple2List*)list_29))) = (struct StringSpace_Tuple2List){.head = tuple_11, .tail = list_30};
    struct StringSpace_Tuple2List const* list_28 = milone_mem_alloc(1, sizeof(struct StringSpace_Tuple2List));
    (*(((struct StringSpace_Tuple2List*)list_28))) = (struct StringSpace_Tuple2List){.head = tuple_10, .tail = list_29};
    struct StringSpace_Tuple2List const* cases_ = list_28;
    struct BoolBoolFun1 fun_44 = (struct BoolBoolFun1){.fun = fun_24, .env = NULL};
    struct StringSpace_Tuple2BoolFun1 fun_45 = (struct StringSpace_Tuple2BoolFun1){.fun = fun_25, .env = NULL};
    struct BoolList const* call_134 = listMap_2(fun_45, cases_);
    bool call_135 = listForAll_1(fun_44, call_134);
    bool ok_ = call_135;
    milone_assert(ok_, 448, 2);
    return 0;
}

bool fun_26(void const* env_17, bool arg_29) {
    bool call_136 = id_1(arg_29);
    return call_136;
}

bool fun_8(struct StringTy_Pat_ListCovering_Tuple4 arg_97) {
    struct String name_ = arg_97.t0;
    struct Ty_ ty_2 = arg_97.t1;
    struct Pat_List const* pats_1 = arg_97.t2;
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
    if_7 = (struct Covering_){.discriminant = Covering_};
    goto if_next_148;
else_150:;
    if_7 = (struct Covering_){.discriminant = Open_};
    goto if_next_148;
if_next_148:;
    struct Covering_ actual_1 = if_7;
    struct BoolStringTuple2 match_27;
    struct Covering_Covering_Tuple2 tuple_18 = (struct Covering_Covering_Tuple2){.t0 = covering_, .t1 = actual_1};
    if ((tuple_18.t0.discriminant != Covering_)) goto next_153;
    if ((tuple_18.t1.discriminant != Covering_)) goto next_153;
    goto match_body_152;
next_153:;
    if ((tuple_18.t0.discriminant != Open_)) goto next_154;
    if ((tuple_18.t1.discriminant != Open_)) goto next_154;
    goto match_body_152;
match_body_152:;
    struct BoolStringTuple2 tuple_19 = (struct BoolStringTuple2){.t0 = true, .t1 = (struct String){.str = "OK", .len = 2}};
    match_27 = tuple_19;
    goto end_match_151;
next_154:;
    if ((tuple_18.t0.discriminant != Covering_)) goto next_155;
    if ((tuple_18.t1.discriminant != Open_)) goto next_155;
    struct BoolStringTuple2 tuple_20 = (struct BoolStringTuple2){.t0 = false, .t1 = (struct String){.str = "NG. Expected covering but open", .len = 30}};
    match_27 = tuple_20;
    goto end_match_151;
next_155:;
    struct BoolStringTuple2 tuple_21 = (struct BoolStringTuple2){.t0 = false, .t1 = (struct String){.str = "NG. Expected open but covering", .len = 30}};
    match_27 = tuple_21;
    goto end_match_151;
next_156:;
end_match_151:;
    bool ok_2 = match_27.t0;
    struct String msg_1 = match_27.t1;
    printf("%s: %s\n", str_to_c_str(name_), str_to_c_str(msg_1));
    char if_8;
    if ((!(ok_2))) {
        goto then_158;
    } else {
        goto else_159;
    }
then_158:;
    struct String call_140 = spaceToString_(tySpace_);
    printf("  ty: %s\n", str_to_c_str(call_140));
    struct String call_141 = spaceToString_(patSpace_);
    printf("  pats: %s\n", str_to_c_str(call_141));
    if_8 = 0;
    goto if_next_157;
else_159:;
    if_8 = 0;
    goto if_next_157;
if_next_157:;
    return ok_2;
}

bool fun_27(void const* env_18, struct StringTy_Pat_ListCovering_Tuple4 arg_30) {
    bool call_142 = fun_8(arg_30);
    return call_142;
}

int milone_main() {
    spaceFull_ = (struct Space_){.discriminant = Full_};
    struct Space_ variant_8 = (struct Space_){.discriminant = Union_, .Union_ = NULL};
    spaceEmpty_ = variant_8;
    char call_143 = testSpaceIsEmpty_(0);
    char call_144 = testSpaceToString_(0);
    struct Pat_Pat_Tuple2 tuple_22 = (struct Pat_Pat_Tuple2){.t0 = (struct Pat_){.discriminant = Discard_}, .t1 = (struct Pat_){.discriminant = Discard_}};
    void const* box_10 = milone_mem_alloc(1, sizeof(struct Pat_Pat_Tuple2));
    (*(((struct Pat_Pat_Tuple2*)box_10))) = tuple_22;
    struct Pat_ variant_9 = (struct Pat_){.discriminant = Cons_, .Cons_ = box_10};
    struct Pat_ anyConsPat_ = variant_9;
    struct Ty_ variant_10 = (struct Ty_){.discriminant = Tuple_, .Tuple_ = NULL};
    struct Pat_ variant_11 = (struct Pat_){.discriminant = TupleLit_, .TupleLit_ = NULL};
    struct Pat_List const* list_38 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_38))) = (struct Pat_List){.head = variant_11, .tail = NULL};
    struct StringTy_Pat_ListCovering_Tuple4 tuple_23 = (struct StringTy_Pat_ListCovering_Tuple4){.t0 = (struct String){.str = "unit with ()", .len = 12}, .t1 = variant_10, .t2 = list_38, .t3 = (struct Covering_){.discriminant = Covering_}};
    struct Pat_ variant_12 = (struct Pat_){.discriminant = IntLit_, .IntLit_ = 1};
    struct Pat_List const* list_40 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_40))) = (struct Pat_List){.head = variant_12, .tail = NULL};
    struct StringTy_Pat_ListCovering_Tuple4 tuple_24 = (struct StringTy_Pat_ListCovering_Tuple4){.t0 = (struct String){.str = "int with literal pats", .len = 21}, .t1 = (struct Ty_){.discriminant = Int_}, .t2 = list_40, .t3 = (struct Covering_){.discriminant = Open_}};
    struct Pat_List const* list_42 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_42))) = (struct Pat_List){.head = (struct Pat_){.discriminant = Discard_}, .tail = NULL};
    struct StringTy_Pat_ListCovering_Tuple4 tuple_25 = (struct StringTy_Pat_ListCovering_Tuple4){.t0 = (struct String){.str = "int with _", .len = 10}, .t1 = (struct Ty_){.discriminant = Int_}, .t2 = list_42, .t3 = (struct Covering_){.discriminant = Covering_}};
    struct Pat_ variant_13 = (struct Pat_){.discriminant = IntLit_, .IntLit_ = 1};
    struct Pat_List const* list_45 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_45))) = (struct Pat_List){.head = (struct Pat_){.discriminant = Discard_}, .tail = NULL};
    struct Pat_List const* list_44 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_44))) = (struct Pat_List){.head = variant_13, .tail = list_45};
    struct StringTy_Pat_ListCovering_Tuple4 tuple_26 = (struct StringTy_Pat_ListCovering_Tuple4){.t0 = (struct String){.str = "int with 1|_", .len = 12}, .t1 = (struct Ty_){.discriminant = Int_}, .t2 = list_44, .t3 = (struct Covering_){.discriminant = Covering_}};
    struct Ty_ variant_14 = (struct Ty_){.discriminant = Tuple_, .Tuple_ = NULL};
    struct Ty_List const* list_48 = milone_mem_alloc(1, sizeof(struct Ty_List));
    (*(((struct Ty_List*)list_48))) = (struct Ty_List){.head = variant_14, .tail = NULL};
    struct Ty_List const* list_47 = milone_mem_alloc(1, sizeof(struct Ty_List));
    (*(((struct Ty_List*)list_47))) = (struct Ty_List){.head = (struct Ty_){.discriminant = Int_}, .tail = list_48};
    struct Ty_ variant_15 = (struct Ty_){.discriminant = Tuple_, .Tuple_ = list_47};
    struct Pat_ variant_16 = (struct Pat_){.discriminant = TupleLit_, .TupleLit_ = NULL};
    struct Pat_List const* list_51 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_51))) = (struct Pat_List){.head = variant_16, .tail = NULL};
    struct Pat_List const* list_50 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_50))) = (struct Pat_List){.head = (struct Pat_){.discriminant = Discard_}, .tail = list_51};
    struct Pat_ variant_17 = (struct Pat_){.discriminant = TupleLit_, .TupleLit_ = list_50};
    struct Pat_List const* list_49 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_49))) = (struct Pat_List){.head = variant_17, .tail = NULL};
    struct StringTy_Pat_ListCovering_Tuple4 tuple_27 = (struct StringTy_Pat_ListCovering_Tuple4){.t0 = (struct String){.str = "int * unit with _, ()", .len = 21}, .t1 = variant_15, .t2 = list_49, .t3 = (struct Covering_){.discriminant = Covering_}};
    struct Ty_List const* list_54 = milone_mem_alloc(1, sizeof(struct Ty_List));
    (*(((struct Ty_List*)list_54))) = (struct Ty_List){.head = (struct Ty_){.discriminant = Int_}, .tail = NULL};
    struct Ty_List const* list_53 = milone_mem_alloc(1, sizeof(struct Ty_List));
    (*(((struct Ty_List*)list_53))) = (struct Ty_List){.head = (struct Ty_){.discriminant = Int_}, .tail = list_54};
    struct Ty_ variant_18 = (struct Ty_){.discriminant = Tuple_, .Tuple_ = list_53};
    struct Pat_ variant_19 = (struct Pat_){.discriminant = IntLit_, .IntLit_ = 1};
    struct Pat_List const* list_57 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_57))) = (struct Pat_List){.head = (struct Pat_){.discriminant = Discard_}, .tail = NULL};
    struct Pat_List const* list_56 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_56))) = (struct Pat_List){.head = variant_19, .tail = list_57};
    struct Pat_ variant_20 = (struct Pat_){.discriminant = TupleLit_, .TupleLit_ = list_56};
    struct Pat_ variant_21 = (struct Pat_){.discriminant = IntLit_, .IntLit_ = 1};
    struct Pat_List const* list_60 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_60))) = (struct Pat_List){.head = variant_21, .tail = NULL};
    struct Pat_List const* list_59 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_59))) = (struct Pat_List){.head = (struct Pat_){.discriminant = Discard_}, .tail = list_60};
    struct Pat_ variant_22 = (struct Pat_){.discriminant = TupleLit_, .TupleLit_ = list_59};
    struct Pat_List const* list_58 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_58))) = (struct Pat_List){.head = variant_22, .tail = NULL};
    struct Pat_List const* list_55 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_55))) = (struct Pat_List){.head = variant_20, .tail = list_58};
    struct StringTy_Pat_ListCovering_Tuple4 tuple_28 = (struct StringTy_Pat_ListCovering_Tuple4){.t0 = (struct String){.str = "int * int with 1, _ | _, 1", .len = 26}, .t1 = variant_18, .t2 = list_55, .t3 = (struct Covering_){.discriminant = Open_}};
    void const* box_11 = milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_11))) = (struct Ty_){.discriminant = Int_};
    struct Ty_ variant_23 = (struct Ty_){.discriminant = List_, .List_ = box_11};
    struct Pat_List const* list_62 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_62))) = (struct Pat_List){.head = (struct Pat_){.discriminant = Nil_}, .tail = NULL};
    struct StringTy_Pat_ListCovering_Tuple4 tuple_29 = (struct StringTy_Pat_ListCovering_Tuple4){.t0 = (struct String){.str = "int list with []", .len = 16}, .t1 = variant_23, .t2 = list_62, .t3 = (struct Covering_){.discriminant = Open_}};
    void const* box_12 = milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_12))) = (struct Ty_){.discriminant = Int_};
    struct Ty_ variant_24 = (struct Ty_){.discriminant = List_, .List_ = box_12};
    struct Pat_List const* list_64 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_64))) = (struct Pat_List){.head = anyConsPat_, .tail = NULL};
    struct StringTy_Pat_ListCovering_Tuple4 tuple_30 = (struct StringTy_Pat_ListCovering_Tuple4){.t0 = (struct String){.str = "int list with _::_", .len = 18}, .t1 = variant_24, .t2 = list_64, .t3 = (struct Covering_){.discriminant = Open_}};
    void const* box_13 = milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_13))) = (struct Ty_){.discriminant = Int_};
    struct Ty_ variant_25 = (struct Ty_){.discriminant = List_, .List_ = box_13};
    struct Pat_List const* list_67 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_67))) = (struct Pat_List){.head = anyConsPat_, .tail = NULL};
    struct Pat_List const* list_66 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_66))) = (struct Pat_List){.head = (struct Pat_){.discriminant = Nil_}, .tail = list_67};
    struct StringTy_Pat_ListCovering_Tuple4 tuple_31 = (struct StringTy_Pat_ListCovering_Tuple4){.t0 = (struct String){.str = "int list with [] | _::_", .len = 23}, .t1 = variant_25, .t2 = list_66, .t3 = (struct Covering_){.discriminant = Covering_}};
    void const* box_14 = milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_14))) = (struct Ty_){.discriminant = Int_};
    struct Ty_ variant_26 = (struct Ty_){.discriminant = List_, .List_ = box_14};
    struct Pat_Pat_Tuple2 tuple_33 = (struct Pat_Pat_Tuple2){.t0 = (struct Pat_){.discriminant = Discard_}, .t1 = (struct Pat_){.discriminant = Nil_}};
    void const* box_15 = milone_mem_alloc(1, sizeof(struct Pat_Pat_Tuple2));
    (*(((struct Pat_Pat_Tuple2*)box_15))) = tuple_33;
    struct Pat_ variant_27 = (struct Pat_){.discriminant = Cons_, .Cons_ = box_15};
    struct Pat_Pat_Tuple2 tuple_34 = (struct Pat_Pat_Tuple2){.t0 = (struct Pat_){.discriminant = Discard_}, .t1 = anyConsPat_};
    void const* box_16 = milone_mem_alloc(1, sizeof(struct Pat_Pat_Tuple2));
    (*(((struct Pat_Pat_Tuple2*)box_16))) = tuple_34;
    struct Pat_ variant_28 = (struct Pat_){.discriminant = Cons_, .Cons_ = box_16};
    struct Pat_List const* list_71 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_71))) = (struct Pat_List){.head = variant_28, .tail = NULL};
    struct Pat_List const* list_70 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_70))) = (struct Pat_List){.head = variant_27, .tail = list_71};
    struct Pat_List const* list_69 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_69))) = (struct Pat_List){.head = (struct Pat_){.discriminant = Nil_}, .tail = list_70};
    struct StringTy_Pat_ListCovering_Tuple4 tuple_32 = (struct StringTy_Pat_ListCovering_Tuple4){.t0 = (struct String){.str = "int list with [] | [_] | _::_::_", .len = 32}, .t1 = variant_26, .t2 = list_69, .t3 = (struct Covering_){.discriminant = Covering_}};
    void const* box_17 = milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_17))) = (struct Ty_){.discriminant = Int_};
    struct Ty_ variant_29 = (struct Ty_){.discriminant = List_, .List_ = box_17};
    void const* box_18 = milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_18))) = variant_29;
    struct Ty_ variant_30 = (struct Ty_){.discriminant = List_, .List_ = box_18};
    struct Pat_Pat_Tuple2 tuple_36 = (struct Pat_Pat_Tuple2){.t0 = (struct Pat_){.discriminant = Nil_}, .t1 = (struct Pat_){.discriminant = Nil_}};
    void const* box_19 = milone_mem_alloc(1, sizeof(struct Pat_Pat_Tuple2));
    (*(((struct Pat_Pat_Tuple2*)box_19))) = tuple_36;
    struct Pat_ variant_31 = (struct Pat_){.discriminant = Cons_, .Cons_ = box_19};
    struct Pat_Pat_Tuple2 tuple_37 = (struct Pat_Pat_Tuple2){.t0 = anyConsPat_, .t1 = (struct Pat_){.discriminant = Discard_}};
    void const* box_20 = milone_mem_alloc(1, sizeof(struct Pat_Pat_Tuple2));
    (*(((struct Pat_Pat_Tuple2*)box_20))) = tuple_37;
    struct Pat_ variant_32 = (struct Pat_){.discriminant = Cons_, .Cons_ = box_20};
    struct Pat_Pat_Tuple2 tuple_38 = (struct Pat_Pat_Tuple2){.t0 = (struct Pat_){.discriminant = Discard_}, .t1 = anyConsPat_};
    void const* box_21 = milone_mem_alloc(1, sizeof(struct Pat_Pat_Tuple2));
    (*(((struct Pat_Pat_Tuple2*)box_21))) = tuple_38;
    struct Pat_ variant_33 = (struct Pat_){.discriminant = Cons_, .Cons_ = box_21};
    struct Pat_List const* list_76 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_76))) = (struct Pat_List){.head = variant_33, .tail = NULL};
    struct Pat_List const* list_75 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_75))) = (struct Pat_List){.head = variant_32, .tail = list_76};
    struct Pat_List const* list_74 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_74))) = (struct Pat_List){.head = variant_31, .tail = list_75};
    struct Pat_List const* list_73 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_73))) = (struct Pat_List){.head = (struct Pat_){.discriminant = Nil_}, .tail = list_74};
    struct StringTy_Pat_ListCovering_Tuple4 tuple_35 = (struct StringTy_Pat_ListCovering_Tuple4){.t0 = (struct String){.str = "int list list with [] | [[]] | [_::_] | _::_::_", .len = 47}, .t1 = variant_30, .t2 = list_73, .t3 = (struct Covering_){.discriminant = Covering_}};
    void const* box_22 = milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_22))) = (struct Ty_){.discriminant = Int_};
    struct Ty_ variant_34 = (struct Ty_){.discriminant = List_, .List_ = box_22};
    void const* box_23 = milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_23))) = (struct Ty_){.discriminant = Int_};
    struct Ty_ variant_35 = (struct Ty_){.discriminant = List_, .List_ = box_23};
    struct Ty_List const* list_79 = milone_mem_alloc(1, sizeof(struct Ty_List));
    (*(((struct Ty_List*)list_79))) = (struct Ty_List){.head = variant_35, .tail = NULL};
    struct Ty_List const* list_78 = milone_mem_alloc(1, sizeof(struct Ty_List));
    (*(((struct Ty_List*)list_78))) = (struct Ty_List){.head = variant_34, .tail = list_79};
    struct Ty_ variant_36 = (struct Ty_){.discriminant = Tuple_, .Tuple_ = list_78};
    struct Pat_List const* list_82 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_82))) = (struct Pat_List){.head = (struct Pat_){.discriminant = Nil_}, .tail = NULL};
    struct Pat_List const* list_81 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_81))) = (struct Pat_List){.head = (struct Pat_){.discriminant = Nil_}, .tail = list_82};
    struct Pat_ variant_37 = (struct Pat_){.discriminant = TupleLit_, .TupleLit_ = list_81};
    struct Pat_List const* list_85 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_85))) = (struct Pat_List){.head = (struct Pat_){.discriminant = Nil_}, .tail = NULL};
    struct Pat_List const* list_84 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_84))) = (struct Pat_List){.head = anyConsPat_, .tail = list_85};
    struct Pat_ variant_38 = (struct Pat_){.discriminant = TupleLit_, .TupleLit_ = list_84};
    struct Pat_List const* list_88 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_88))) = (struct Pat_List){.head = anyConsPat_, .tail = NULL};
    struct Pat_List const* list_87 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_87))) = (struct Pat_List){.head = (struct Pat_){.discriminant = Nil_}, .tail = list_88};
    struct Pat_ variant_39 = (struct Pat_){.discriminant = TupleLit_, .TupleLit_ = list_87};
    struct Pat_List const* list_91 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_91))) = (struct Pat_List){.head = anyConsPat_, .tail = NULL};
    struct Pat_List const* list_90 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_90))) = (struct Pat_List){.head = anyConsPat_, .tail = list_91};
    struct Pat_ variant_40 = (struct Pat_){.discriminant = TupleLit_, .TupleLit_ = list_90};
    struct Pat_List const* list_89 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_89))) = (struct Pat_List){.head = variant_40, .tail = NULL};
    struct Pat_List const* list_86 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_86))) = (struct Pat_List){.head = variant_39, .tail = list_89};
    struct Pat_List const* list_83 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_83))) = (struct Pat_List){.head = variant_38, .tail = list_86};
    struct Pat_List const* list_80 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_80))) = (struct Pat_List){.head = variant_37, .tail = list_83};
    struct StringTy_Pat_ListCovering_Tuple4 tuple_39 = (struct StringTy_Pat_ListCovering_Tuple4){.t0 = (struct String){.str = "int list * int list with [], [] | [], _::_ | _::_, [] | _::_, _::_", .len = 66}, .t1 = variant_36, .t2 = list_80, .t3 = (struct Covering_){.discriminant = Covering_}};
    struct StringTy_Pat_ListCovering_Tuple4List const* list_77 = milone_mem_alloc(1, sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    (*(((struct StringTy_Pat_ListCovering_Tuple4List*)list_77))) = (struct StringTy_Pat_ListCovering_Tuple4List){.head = tuple_39, .tail = NULL};
    struct StringTy_Pat_ListCovering_Tuple4List const* list_72 = milone_mem_alloc(1, sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    (*(((struct StringTy_Pat_ListCovering_Tuple4List*)list_72))) = (struct StringTy_Pat_ListCovering_Tuple4List){.head = tuple_35, .tail = list_77};
    struct StringTy_Pat_ListCovering_Tuple4List const* list_68 = milone_mem_alloc(1, sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    (*(((struct StringTy_Pat_ListCovering_Tuple4List*)list_68))) = (struct StringTy_Pat_ListCovering_Tuple4List){.head = tuple_32, .tail = list_72};
    struct StringTy_Pat_ListCovering_Tuple4List const* list_65 = milone_mem_alloc(1, sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    (*(((struct StringTy_Pat_ListCovering_Tuple4List*)list_65))) = (struct StringTy_Pat_ListCovering_Tuple4List){.head = tuple_31, .tail = list_68};
    struct StringTy_Pat_ListCovering_Tuple4List const* list_63 = milone_mem_alloc(1, sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    (*(((struct StringTy_Pat_ListCovering_Tuple4List*)list_63))) = (struct StringTy_Pat_ListCovering_Tuple4List){.head = tuple_30, .tail = list_65};
    struct StringTy_Pat_ListCovering_Tuple4List const* list_61 = milone_mem_alloc(1, sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    (*(((struct StringTy_Pat_ListCovering_Tuple4List*)list_61))) = (struct StringTy_Pat_ListCovering_Tuple4List){.head = tuple_29, .tail = list_63};
    struct StringTy_Pat_ListCovering_Tuple4List const* list_52 = milone_mem_alloc(1, sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    (*(((struct StringTy_Pat_ListCovering_Tuple4List*)list_52))) = (struct StringTy_Pat_ListCovering_Tuple4List){.head = tuple_28, .tail = list_61};
    struct StringTy_Pat_ListCovering_Tuple4List const* list_46 = milone_mem_alloc(1, sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    (*(((struct StringTy_Pat_ListCovering_Tuple4List*)list_46))) = (struct StringTy_Pat_ListCovering_Tuple4List){.head = tuple_27, .tail = list_52};
    struct StringTy_Pat_ListCovering_Tuple4List const* list_43 = milone_mem_alloc(1, sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    (*(((struct StringTy_Pat_ListCovering_Tuple4List*)list_43))) = (struct StringTy_Pat_ListCovering_Tuple4List){.head = tuple_26, .tail = list_46};
    struct StringTy_Pat_ListCovering_Tuple4List const* list_41 = milone_mem_alloc(1, sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    (*(((struct StringTy_Pat_ListCovering_Tuple4List*)list_41))) = (struct StringTy_Pat_ListCovering_Tuple4List){.head = tuple_25, .tail = list_43};
    struct StringTy_Pat_ListCovering_Tuple4List const* list_39 = milone_mem_alloc(1, sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    (*(((struct StringTy_Pat_ListCovering_Tuple4List*)list_39))) = (struct StringTy_Pat_ListCovering_Tuple4List){.head = tuple_24, .tail = list_41};
    struct StringTy_Pat_ListCovering_Tuple4List const* list_37 = milone_mem_alloc(1, sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    (*(((struct StringTy_Pat_ListCovering_Tuple4List*)list_37))) = (struct StringTy_Pat_ListCovering_Tuple4List){.head = tuple_23, .tail = list_39};
    struct StringTy_Pat_ListCovering_Tuple4List const* testCases_ = list_37;
    struct BoolBoolFun1 fun_46 = (struct BoolBoolFun1){.fun = fun_26, .env = NULL};
    struct StringTy_Pat_ListCovering_Tuple4BoolFun1 fun_47 = (struct StringTy_Pat_ListCovering_Tuple4BoolFun1){.fun = fun_27, .env = NULL};
    struct BoolList const* call_145 = listMap_1(fun_47, testCases_);
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
