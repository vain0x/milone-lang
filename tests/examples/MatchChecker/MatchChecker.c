#include "milone.h"

struct Space_List;

struct StringList;

struct StringSpaceListTuple2_;

struct Space_;

struct StringList;

struct Space_List;

struct BoolList;

struct BoolList;

struct SpaceSpaceTuple2_List;

struct SpaceSpaceTuple2_;

struct SpaceSpaceTuple2_List;

struct Space_Space_Fun1;

struct Ty_List;

struct Ty_;

struct Ty_Space_Fun1;

struct Ty_List;

struct Pat_List;

struct Pat_;

struct Pat_Space_Fun1;

struct Pat_List;

struct StringSpaceTuple2_;

struct StringSpaceTuple2_BoolFun1;

struct StringSpaceTuple2_List;

struct StringSpaceTuple2_List;

struct Covering_;

struct StringTyPatListCoveringTuple4_;

struct StringTyPatListCoveringTuple4_BoolFun1;

struct StringTyPatListCoveringTuple4_List;

struct StringTyPatListCoveringTuple4_List;

struct IntSpaceSpaceTuple2_Space_Fun2;

struct IntSpace_Space_Fun2;

struct Space_BoolFun1;

struct SpaceSpaceTuple2_BoolFun1;

struct BoolBoolFun1;

struct Space_Space_Space_Fun2;

struct StringListSpace_StringListFun2;

struct SpaceListSpaceListTuple2_;

struct UnitSpace_Fun1;

struct StringUnitSpaceFun1Tuple2_;

struct StringSpaceListSpaceListTuple3_;

struct PatPatTuple2_;

struct BoolStringTuple2_;

struct CoveringCoveringTuple2_;

struct Space_List const* failwith_2(struct String msg_);

struct StringList const* failwith_1(struct String msg_);

struct Space_ failwith_(struct String msg_);

struct StringList const* cons_(struct String head_, struct StringList const* tail_);

struct Space_List const* go_6(struct Space_List const* acc_, struct Space_List const* xs_2);

struct StringList const* go_5(struct StringList const* acc_, struct StringList const* xs_2);

struct BoolList const* go_22(struct BoolList const* acc_, struct BoolList const* xs_2);

struct SpaceSpaceTuple2_List const* go_21(struct SpaceSpaceTuple2_List const* acc_, struct SpaceSpaceTuple2_List const* xs_2);

struct Space_List const* listRev_1(struct Space_List const* xs_1);

struct StringList const* listRev_(struct StringList const* xs_1);

struct BoolList const* listRev_3(struct BoolList const* xs_1);

struct SpaceSpaceTuple2_List const* listRev_2(struct SpaceSpaceTuple2_List const* xs_1);

struct Space_List const* go_11(struct Space_Space_Fun1 f_, struct Space_List const* acc_1, struct Space_List const* xs_5);

struct Space_List const* go_10(struct Ty_Space_Fun1 f_, struct Space_List const* acc_1, struct Ty_List const* xs_5);

struct Space_List const* go_9(struct Pat_Space_Fun1 f_, struct Space_List const* acc_1, struct Pat_List const* xs_5);

struct BoolList const* go_8(struct StringSpaceTuple2_BoolFun1 f_, struct BoolList const* acc_1, struct StringSpaceTuple2_List const* xs_5);

struct BoolList const* go_7(struct StringTyPatListCoveringTuple4_BoolFun1 f_, struct BoolList const* acc_1, struct StringTyPatListCoveringTuple4_List const* xs_5);

struct Space_List const* listMap_4(struct Space_Space_Fun1 f_, struct Space_List const* xs_4);

struct Space_List const* listMap_3(struct Ty_Space_Fun1 f_, struct Ty_List const* xs_4);

struct Space_List const* listMap_2(struct Pat_Space_Fun1 f_, struct Pat_List const* xs_4);

struct BoolList const* listMap_1(struct StringSpaceTuple2_BoolFun1 f_, struct StringSpaceTuple2_List const* xs_4);

struct BoolList const* listMap_(struct StringTyPatListCoveringTuple4_BoolFun1 f_, struct StringTyPatListCoveringTuple4_List const* xs_4);

struct Space_List const* go_13(struct IntSpaceSpaceTuple2_Space_Fun2 f_1, struct Space_List const* acc_2, int i_, struct SpaceSpaceTuple2_List const* xs_8);

struct Space_List const* go_12(struct IntSpace_Space_Fun2 f_1, struct Space_List const* acc_2, int i_, struct Space_List const* xs_8);

struct Space_List const* listMapWithIndex_1(struct IntSpaceSpaceTuple2_Space_Fun2 f_1, struct SpaceSpaceTuple2_List const* xs_7);

struct Space_List const* listMapWithIndex_(struct IntSpace_Space_Fun2 f_1, struct Space_List const* xs_7);

bool go_16(struct Space_BoolFun1 p_, struct Space_List const* xs_11);

bool go_15(struct SpaceSpaceTuple2_BoolFun1 p_, struct SpaceSpaceTuple2_List const* xs_11);

bool go_14(struct BoolBoolFun1 p_, struct BoolList const* xs_11);

bool listForAll_2(struct Space_BoolFun1 p_, struct Space_List const* xs_10);

bool listForAll_1(struct SpaceSpaceTuple2_BoolFun1 p_, struct SpaceSpaceTuple2_List const* xs_10);

bool listForAll_(struct BoolBoolFun1 p_, struct BoolList const* xs_10);

bool go_17(struct Space_BoolFun1 p_1, struct Space_List const* xs_14);

bool listExists_(struct Space_BoolFun1 p_1, struct Space_List const* xs_13);

struct Space_ go_19(struct Space_Space_Space_Fun2 folder_, struct Space_ state_1, struct Space_List const* xs_17);

struct StringList const* go_18(struct StringListSpace_StringListFun2 folder_, struct StringList const* state_1, struct Space_List const* xs_17);

struct Space_ listFold_1(struct Space_Space_Space_Fun2 folder_, struct Space_ state_, struct Space_List const* xs_16);

struct StringList const* listFold_(struct StringListSpace_StringListFun2 folder_, struct StringList const* state_, struct Space_List const* xs_16);

struct SpaceSpaceTuple2_List const* go_20(struct SpaceSpaceTuple2_List const* acc_3, struct Space_List const* xs_20, struct Space_List const* ys_1);

struct SpaceSpaceTuple2_List const* listZip_(struct Space_List const* xs_19, struct Space_List const* ys_);

struct String go_(struct StringList const* xs_23);

struct String MatchChecker_Program_strConcat(struct StringList const* xs_22);

struct Space_ MatchChecker_Program_spaceCtor(struct String tag_, struct Space_List const* items_);

struct Space_ MatchChecker_Program_spaceRef(struct String tag_1, struct UnitSpace_Fun1 thunk_);

struct Space_List const* go_1(struct Space_List const* spaces_1, struct Space_List const* acc_4);

struct Space_ MatchChecker_Program_spaceUnion(struct Space_List const* spaces_);

bool fun_8(void const* env_, struct Space_ arg_);

bool fun_9(void const* env_1, struct Space_ arg_1);

bool MatchChecker_Program_spaceIsEmpty(struct Space_ space_3);

struct Space_ MatchChecker_Program_spaceDecompose(struct Space_ space_4);

bool fun_(struct SpaceSpaceTuple2_ arg_85);

bool fun_10(void const* env_2, struct SpaceSpaceTuple2_ arg_2);

struct Space_ fun_1(int i_1, int j_, struct SpaceSpaceTuple2_ arg_86);

struct Space_ fun_11(void const* env_3, int arg_3, struct SpaceSpaceTuple2_ arg_4);

struct Space_ fun_27(struct String tag_2, struct Space_List const* firsts_, struct Space_List const* seconds_, int i_1, struct Space_ arg_87);

struct Space_ fun_12(void const* env_4, int arg_6, struct Space_ arg_7);

struct Space_ fun_13(void const* env_5, struct Space_ arg_11, struct Space_ arg_12);

struct Space_ fun_2(struct Space_ second_, struct Space_ first_3);

struct Space_ fun_14(void const* env_6, struct Space_ arg_13);

struct Space_ MatchChecker_Program_spaceExclude(struct Space_ first_, struct Space_ second_);

bool MatchChecker_Program_spaceCovers(struct Space_ other_, struct Space_ cover_);

struct StringList const* fun_3(struct StringList const* acc_7, struct Space_ space_8);

struct StringList const* fun_15(void const* env_7, struct StringList const* arg_15, struct Space_ arg_16);

struct StringList const* fun_4(struct StringList const* acc_9, struct Space_ space_9);

struct StringList const* fun_16(void const* env_8, struct StringList const* arg_17, struct Space_ arg_18);

struct StringList const* go_2(struct Space_ space_7, struct StringList const* acc_5);

struct String MatchChecker_Program_spaceToString(struct Space_ space_6);

struct Space_ fun_17(void const* env_9, struct Ty_ arg_19);

struct Space_ fun_18(void const* env_10, char arg_20);

struct Space_ thunk_2(struct Space_ itemSpace_, char arg_92);

struct Space_ fun_19(void const* env_11, char arg_22);

struct Space_ go_3(struct Ty_ ty_1);

struct Space_ MatchChecker_Program_tyToSpace(struct Ty_ ty_);

struct Space_ fun_20(void const* env_12, struct Pat_ arg_24);

struct Space_ go_4(struct Pat_ pat_1);

struct Space_ MatchChecker_Program_patToSpace(struct Pat_ pat_);

struct Space_ fun_21(void const* env_13, struct Pat_ arg_25);

struct Space_ MatchChecker_Program_patsToSpace(struct Pat_List const* pats_);

struct Space_ fun_5(char arg_93);

struct Space_ fun_22(void const* env_14, char arg_26);

char MatchChecker_Program_testSpaceIsEmpty(char arg_94);

bool id_(bool);

bool fun_23(void const* env_15, bool arg_27);

bool fun_6(struct StringSpaceTuple2_ arg_95);

bool fun_24(void const* env_16, struct StringSpaceTuple2_ arg_28);

char MatchChecker_Program_testSpaceToString(char arg_96);

bool fun_25(void const* env_17, bool arg_29);

bool fun_7(struct StringTyPatListCoveringTuple4_ arg_97);

bool fun_26(void const* env_18, struct StringTyPatListCoveringTuple4_ arg_30);

int milone_main();

struct StringSpaceListTuple2_ {
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
        struct StringSpaceListTuple2_ Ctor_;
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

struct SpaceSpaceTuple2_ {
    struct Space_ t0;
    struct Space_ t1;
};

struct SpaceSpaceTuple2_List {
    struct SpaceSpaceTuple2_ head;
    struct SpaceSpaceTuple2_List const* tail;
};

struct Space_Space_Fun1 {
    struct Space_(*fun)(void const*, struct Space_);
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

struct Ty_Space_Fun1 {
    struct Space_(*fun)(void const*, struct Ty_);
    void const* env;
};

struct Ty_List {
    struct Ty_ head;
    struct Ty_List const* tail;
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

struct Pat_Space_Fun1 {
    struct Space_(*fun)(void const*, struct Pat_);
    void const* env;
};

struct Pat_List {
    struct Pat_ head;
    struct Pat_List const* tail;
};

struct StringSpaceTuple2_ {
    struct String t0;
    struct Space_ t1;
};

struct StringSpaceTuple2_BoolFun1 {
    bool(*fun)(void const*, struct StringSpaceTuple2_);
    void const* env;
};

struct StringSpaceTuple2_List {
    struct StringSpaceTuple2_ head;
    struct StringSpaceTuple2_List const* tail;
};

enum Covering_Discriminant {
    Covering_,
    Open_,
};

struct Covering_ {
    enum Covering_Discriminant discriminant;
};

struct StringTyPatListCoveringTuple4_ {
    struct String t0;
    struct Ty_ t1;
    struct Pat_List const* t2;
    struct Covering_ t3;
};

struct StringTyPatListCoveringTuple4_BoolFun1 {
    bool(*fun)(void const*, struct StringTyPatListCoveringTuple4_);
    void const* env;
};

struct StringTyPatListCoveringTuple4_List {
    struct StringTyPatListCoveringTuple4_ head;
    struct StringTyPatListCoveringTuple4_List const* tail;
};

struct IntSpaceSpaceTuple2_Space_Fun2 {
    struct Space_(*fun)(void const*, int, struct SpaceSpaceTuple2_);
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

struct SpaceSpaceTuple2_BoolFun1 {
    bool(*fun)(void const*, struct SpaceSpaceTuple2_);
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

struct SpaceListSpaceListTuple2_ {
    struct Space_List const* t0;
    struct Space_List const* t1;
};

struct UnitSpace_Fun1 {
    struct Space_(*fun)(void const*, char);
    void const* env;
};

struct StringUnitSpaceFun1Tuple2_ {
    struct String t0;
    struct UnitSpace_Fun1 t1;
};

struct StringSpaceListSpaceListTuple3_ {
    struct String t0;
    struct Space_List const* t1;
    struct Space_List const* t2;
};

struct PatPatTuple2_ {
    struct Pat_ t0;
    struct Pat_ t1;
};

struct BoolStringTuple2_ {
    bool t0;
    struct String t1;
};

struct CoveringCoveringTuple2_ {
    struct Covering_ t0;
    struct Covering_ t1;
};

extern struct Space_ MatchChecker_Program_spaceEmpty;

extern struct Space_ MatchChecker_Program_spaceFull;

struct Space_ MatchChecker_Program_spaceFull;

struct Space_ MatchChecker_Program_spaceEmpty;

struct Space_List const* failwith_2(struct String msg_) {
    printf("ERROR %s\n", str_to_c_str(msg_));
    exit(1);
}

struct StringList const* failwith_1(struct String msg_) {
    printf("ERROR %s\n", str_to_c_str(msg_));
    exit(1);
}

struct Space_ failwith_(struct String msg_) {
    printf("ERROR %s\n", str_to_c_str(msg_));
    exit(1);
}

struct StringList const* cons_(struct String head_, struct StringList const* tail_) {
    struct StringList const* list_ = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_))) = (struct StringList){.head = head_, .tail = tail_};
    return list_;
}

struct Space_List const* go_6(struct Space_List const* acc_, struct Space_List const* xs_2) {
    struct Space_List const* xs_3;
    struct Space_ x_;
tailrec_1:;
    struct Space_List const* match_;
    if ((!((!(xs_2))))) goto next_3;
    match_ = acc_;
    goto end_match_2;
next_3:;
    if ((!(xs_2))) goto next_4;
    x_ = xs_2->head;
    xs_3 = xs_2->tail;
    struct Space_List const* list_1 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_1))) = (struct Space_List){.head = x_, .tail = acc_};
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

struct StringList const* go_5(struct StringList const* acc_, struct StringList const* xs_2) {
    struct StringList const* xs_3;
    struct String x_;
tailrec_5:;
    struct StringList const* match_1;
    if ((!((!(xs_2))))) goto next_7;
    match_1 = acc_;
    goto end_match_6;
next_7:;
    if ((!(xs_2))) goto next_8;
    x_ = xs_2->head;
    xs_3 = xs_2->tail;
    struct StringList const* list_2 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_2))) = (struct StringList){.head = x_, .tail = acc_};
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

struct BoolList const* go_22(struct BoolList const* acc_, struct BoolList const* xs_2) {
    struct BoolList const* xs_3;
    bool x_;
tailrec_9:;
    struct BoolList const* match_2;
    if ((!((!(xs_2))))) goto next_11;
    match_2 = acc_;
    goto end_match_10;
next_11:;
    if ((!(xs_2))) goto next_12;
    x_ = xs_2->head;
    xs_3 = xs_2->tail;
    struct BoolList const* list_3 = milone_mem_alloc(1, sizeof(struct BoolList));
    (*(((struct BoolList*)list_3))) = (struct BoolList){.head = x_, .tail = acc_};
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

struct SpaceSpaceTuple2_List const* go_21(struct SpaceSpaceTuple2_List const* acc_, struct SpaceSpaceTuple2_List const* xs_2) {
    struct SpaceSpaceTuple2_List const* xs_3;
    struct SpaceSpaceTuple2_ x_;
tailrec_13:;
    struct SpaceSpaceTuple2_List const* match_3;
    if ((!((!(xs_2))))) goto next_15;
    match_3 = acc_;
    goto end_match_14;
next_15:;
    if ((!(xs_2))) goto next_16;
    x_ = xs_2->head;
    xs_3 = xs_2->tail;
    struct SpaceSpaceTuple2_List const* list_4 = milone_mem_alloc(1, sizeof(struct SpaceSpaceTuple2_List));
    (*(((struct SpaceSpaceTuple2_List*)list_4))) = (struct SpaceSpaceTuple2_List){.head = x_, .tail = acc_};
    struct SpaceSpaceTuple2_List const* arg_37 = list_4;
    struct SpaceSpaceTuple2_List const* arg_38 = xs_3;
    acc_ = arg_37;
    xs_2 = arg_38;
    goto tailrec_13;
next_16:;
    exit(1);
end_match_14:;
    return match_3;
}

struct Space_List const* listRev_1(struct Space_List const* xs_1) {
    struct Space_List const* call_ = go_6(NULL, xs_1);
    return call_;
}

struct StringList const* listRev_(struct StringList const* xs_1) {
    struct StringList const* call_1 = go_5(NULL, xs_1);
    return call_1;
}

struct BoolList const* listRev_3(struct BoolList const* xs_1) {
    struct BoolList const* call_2 = go_22(NULL, xs_1);
    return call_2;
}

struct SpaceSpaceTuple2_List const* listRev_2(struct SpaceSpaceTuple2_List const* xs_1) {
    struct SpaceSpaceTuple2_List const* call_3 = go_21(NULL, xs_1);
    return call_3;
}

struct Space_List const* go_11(struct Space_Space_Fun1 f_, struct Space_List const* acc_1, struct Space_List const* xs_5) {
    struct Space_List const* xs_6;
    struct Space_ x_1;
tailrec_17:;
    struct Space_List const* match_4;
    if ((!((!(xs_5))))) goto next_19;
    struct Space_List const* call_4 = listRev_1(acc_1);
    match_4 = call_4;
    goto end_match_18;
next_19:;
    if ((!(xs_5))) goto next_20;
    x_1 = xs_5->head;
    xs_6 = xs_5->tail;
    struct Space_Space_Fun1 arg_39 = f_;
    struct Space_ app_ = f_.fun(f_.env, x_1);
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

struct Space_List const* go_10(struct Ty_Space_Fun1 f_, struct Space_List const* acc_1, struct Ty_List const* xs_5) {
    struct Ty_List const* xs_6;
    struct Ty_ x_1;
tailrec_21:;
    struct Space_List const* match_5;
    if ((!((!(xs_5))))) goto next_23;
    struct Space_List const* call_5 = listRev_1(acc_1);
    match_5 = call_5;
    goto end_match_22;
next_23:;
    if ((!(xs_5))) goto next_24;
    x_1 = xs_5->head;
    xs_6 = xs_5->tail;
    struct Ty_Space_Fun1 arg_42 = f_;
    struct Space_ app_1 = f_.fun(f_.env, x_1);
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

struct Space_List const* go_9(struct Pat_Space_Fun1 f_, struct Space_List const* acc_1, struct Pat_List const* xs_5) {
    struct Pat_List const* xs_6;
    struct Pat_ x_1;
tailrec_25:;
    struct Space_List const* match_6;
    if ((!((!(xs_5))))) goto next_27;
    struct Space_List const* call_6 = listRev_1(acc_1);
    match_6 = call_6;
    goto end_match_26;
next_27:;
    if ((!(xs_5))) goto next_28;
    x_1 = xs_5->head;
    xs_6 = xs_5->tail;
    struct Pat_Space_Fun1 arg_45 = f_;
    struct Space_ app_2 = f_.fun(f_.env, x_1);
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

struct BoolList const* go_8(struct StringSpaceTuple2_BoolFun1 f_, struct BoolList const* acc_1, struct StringSpaceTuple2_List const* xs_5) {
    struct StringSpaceTuple2_List const* xs_6;
    struct StringSpaceTuple2_ x_1;
tailrec_29:;
    struct BoolList const* match_7;
    if ((!((!(xs_5))))) goto next_31;
    struct BoolList const* call_7 = listRev_3(acc_1);
    match_7 = call_7;
    goto end_match_30;
next_31:;
    if ((!(xs_5))) goto next_32;
    x_1 = xs_5->head;
    xs_6 = xs_5->tail;
    struct StringSpaceTuple2_BoolFun1 arg_48 = f_;
    bool app_3 = f_.fun(f_.env, x_1);
    struct BoolList const* list_8 = milone_mem_alloc(1, sizeof(struct BoolList));
    (*(((struct BoolList*)list_8))) = (struct BoolList){.head = app_3, .tail = acc_1};
    struct BoolList const* arg_49 = list_8;
    struct StringSpaceTuple2_List const* arg_50 = xs_6;
    f_ = arg_48;
    acc_1 = arg_49;
    xs_5 = arg_50;
    goto tailrec_29;
next_32:;
    exit(1);
end_match_30:;
    return match_7;
}

struct BoolList const* go_7(struct StringTyPatListCoveringTuple4_BoolFun1 f_, struct BoolList const* acc_1, struct StringTyPatListCoveringTuple4_List const* xs_5) {
    struct StringTyPatListCoveringTuple4_List const* xs_6;
    struct StringTyPatListCoveringTuple4_ x_1;
tailrec_33:;
    struct BoolList const* match_8;
    if ((!((!(xs_5))))) goto next_35;
    struct BoolList const* call_8 = listRev_3(acc_1);
    match_8 = call_8;
    goto end_match_34;
next_35:;
    if ((!(xs_5))) goto next_36;
    x_1 = xs_5->head;
    xs_6 = xs_5->tail;
    struct StringTyPatListCoveringTuple4_BoolFun1 arg_51 = f_;
    bool app_4 = f_.fun(f_.env, x_1);
    struct BoolList const* list_9 = milone_mem_alloc(1, sizeof(struct BoolList));
    (*(((struct BoolList*)list_9))) = (struct BoolList){.head = app_4, .tail = acc_1};
    struct BoolList const* arg_52 = list_9;
    struct StringTyPatListCoveringTuple4_List const* arg_53 = xs_6;
    f_ = arg_51;
    acc_1 = arg_52;
    xs_5 = arg_53;
    goto tailrec_33;
next_36:;
    exit(1);
end_match_34:;
    return match_8;
}

struct Space_List const* listMap_4(struct Space_Space_Fun1 f_, struct Space_List const* xs_4) {
    struct Space_List const* call_9 = go_11(f_, NULL, xs_4);
    return call_9;
}

struct Space_List const* listMap_3(struct Ty_Space_Fun1 f_, struct Ty_List const* xs_4) {
    struct Space_List const* call_10 = go_10(f_, NULL, xs_4);
    return call_10;
}

struct Space_List const* listMap_2(struct Pat_Space_Fun1 f_, struct Pat_List const* xs_4) {
    struct Space_List const* call_11 = go_9(f_, NULL, xs_4);
    return call_11;
}

struct BoolList const* listMap_1(struct StringSpaceTuple2_BoolFun1 f_, struct StringSpaceTuple2_List const* xs_4) {
    struct BoolList const* call_12 = go_8(f_, NULL, xs_4);
    return call_12;
}

struct BoolList const* listMap_(struct StringTyPatListCoveringTuple4_BoolFun1 f_, struct StringTyPatListCoveringTuple4_List const* xs_4) {
    struct BoolList const* call_13 = go_7(f_, NULL, xs_4);
    return call_13;
}

struct Space_List const* go_13(struct IntSpaceSpaceTuple2_Space_Fun2 f_1, struct Space_List const* acc_2, int i_, struct SpaceSpaceTuple2_List const* xs_8) {
    struct SpaceSpaceTuple2_List const* xs_9;
    struct SpaceSpaceTuple2_ x_2;
tailrec_37:;
    struct Space_List const* match_9;
    if ((!((!(xs_8))))) goto next_39;
    struct Space_List const* call_14 = listRev_1(acc_2);
    match_9 = call_14;
    goto end_match_38;
next_39:;
    if ((!(xs_8))) goto next_40;
    x_2 = xs_8->head;
    xs_9 = xs_8->tail;
    struct IntSpaceSpaceTuple2_Space_Fun2 arg_54 = f_1;
    struct Space_ app_5 = f_1.fun(f_1.env, i_, x_2);
    struct Space_List const* list_10 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_10))) = (struct Space_List){.head = app_5, .tail = acc_2};
    struct Space_List const* arg_55 = list_10;
    int arg_56 = (i_ + 1);
    struct SpaceSpaceTuple2_List const* arg_57 = xs_9;
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

struct Space_List const* go_12(struct IntSpace_Space_Fun2 f_1, struct Space_List const* acc_2, int i_, struct Space_List const* xs_8) {
    struct Space_List const* xs_9;
    struct Space_ x_2;
tailrec_41:;
    struct Space_List const* match_10;
    if ((!((!(xs_8))))) goto next_43;
    struct Space_List const* call_15 = listRev_1(acc_2);
    match_10 = call_15;
    goto end_match_42;
next_43:;
    if ((!(xs_8))) goto next_44;
    x_2 = xs_8->head;
    xs_9 = xs_8->tail;
    struct IntSpace_Space_Fun2 arg_58 = f_1;
    struct Space_ app_6 = f_1.fun(f_1.env, i_, x_2);
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

struct Space_List const* listMapWithIndex_1(struct IntSpaceSpaceTuple2_Space_Fun2 f_1, struct SpaceSpaceTuple2_List const* xs_7) {
    struct Space_List const* call_16 = go_13(f_1, NULL, 0, xs_7);
    return call_16;
}

struct Space_List const* listMapWithIndex_(struct IntSpace_Space_Fun2 f_1, struct Space_List const* xs_7) {
    struct Space_List const* call_17 = go_12(f_1, NULL, 0, xs_7);
    return call_17;
}

bool go_16(struct Space_BoolFun1 p_, struct Space_List const* xs_11) {
    struct Space_List const* xs_12;
    struct Space_ x_3;
tailrec_45:;
    bool match_11;
    if ((!((!(xs_11))))) goto next_47;
    match_11 = true;
    goto end_match_46;
next_47:;
    if ((!(xs_11))) goto next_48;
    x_3 = xs_11->head;
    xs_12 = xs_11->tail;
    bool app_7 = p_.fun(p_.env, x_3);
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

bool go_15(struct SpaceSpaceTuple2_BoolFun1 p_, struct SpaceSpaceTuple2_List const* xs_11) {
    struct SpaceSpaceTuple2_List const* xs_12;
    struct SpaceSpaceTuple2_ x_3;
tailrec_52:;
    bool match_12;
    if ((!((!(xs_11))))) goto next_54;
    match_12 = true;
    goto end_match_53;
next_54:;
    if ((!(xs_11))) goto next_55;
    x_3 = xs_11->head;
    xs_12 = xs_11->tail;
    bool app_8 = p_.fun(p_.env, x_3);
    bool if_1;
    if (app_8) {
        goto then_57;
    } else {
        goto else_58;
    }
then_57:;
    struct SpaceSpaceTuple2_BoolFun1 arg_64 = p_;
    struct SpaceSpaceTuple2_List const* arg_65 = xs_12;
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

bool go_14(struct BoolBoolFun1 p_, struct BoolList const* xs_11) {
    struct BoolList const* xs_12;
    bool x_3;
tailrec_59:;
    bool match_13;
    if ((!((!(xs_11))))) goto next_61;
    match_13 = true;
    goto end_match_60;
next_61:;
    if ((!(xs_11))) goto next_62;
    x_3 = xs_11->head;
    xs_12 = xs_11->tail;
    bool app_9 = p_.fun(p_.env, x_3);
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

bool listForAll_2(struct Space_BoolFun1 p_, struct Space_List const* xs_10) {
    bool call_18 = go_16(p_, xs_10);
    return call_18;
}

bool listForAll_1(struct SpaceSpaceTuple2_BoolFun1 p_, struct SpaceSpaceTuple2_List const* xs_10) {
    bool call_19 = go_15(p_, xs_10);
    return call_19;
}

bool listForAll_(struct BoolBoolFun1 p_, struct BoolList const* xs_10) {
    bool call_20 = go_14(p_, xs_10);
    return call_20;
}

bool go_17(struct Space_BoolFun1 p_1, struct Space_List const* xs_14) {
    struct Space_List const* xs_15;
    struct Space_ x_4;
tailrec_66:;
    bool match_14;
    if ((!((!(xs_14))))) goto next_68;
    match_14 = false;
    goto end_match_67;
next_68:;
    if ((!(xs_14))) goto next_69;
    x_4 = xs_14->head;
    xs_15 = xs_14->tail;
    bool app_10 = p_1.fun(p_1.env, x_4);
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

bool listExists_(struct Space_BoolFun1 p_1, struct Space_List const* xs_13) {
    bool call_21 = go_17(p_1, xs_13);
    return call_21;
}

struct Space_ go_19(struct Space_Space_Space_Fun2 folder_, struct Space_ state_1, struct Space_List const* xs_17) {
    struct Space_List const* xs_18;
    struct Space_ x_5;
tailrec_73:;
    struct Space_ match_15;
    if ((!((!(xs_17))))) goto next_75;
    match_15 = state_1;
    goto end_match_74;
next_75:;
    if ((!(xs_17))) goto next_76;
    x_5 = xs_17->head;
    xs_18 = xs_17->tail;
    struct Space_Space_Space_Fun2 arg_70 = folder_;
    struct Space_ app_11 = folder_.fun(folder_.env, state_1, x_5);
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

struct StringList const* go_18(struct StringListSpace_StringListFun2 folder_, struct StringList const* state_1, struct Space_List const* xs_17) {
    struct Space_List const* xs_18;
    struct Space_ x_5;
tailrec_77:;
    struct StringList const* match_16;
    if ((!((!(xs_17))))) goto next_79;
    match_16 = state_1;
    goto end_match_78;
next_79:;
    if ((!(xs_17))) goto next_80;
    x_5 = xs_17->head;
    xs_18 = xs_17->tail;
    struct StringListSpace_StringListFun2 arg_73 = folder_;
    struct StringList const* app_12 = folder_.fun(folder_.env, state_1, x_5);
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

struct Space_ listFold_1(struct Space_Space_Space_Fun2 folder_, struct Space_ state_, struct Space_List const* xs_16) {
    struct Space_ call_22 = go_19(folder_, state_, xs_16);
    return call_22;
}

struct StringList const* listFold_(struct StringListSpace_StringListFun2 folder_, struct StringList const* state_, struct Space_List const* xs_16) {
    struct StringList const* call_23 = go_18(folder_, state_, xs_16);
    return call_23;
}

struct SpaceSpaceTuple2_List const* go_20(struct SpaceSpaceTuple2_List const* acc_3, struct Space_List const* xs_20, struct Space_List const* ys_1) {
    struct Space_List const* ys_2;
    struct Space_ y_;
    struct Space_List const* xs_21;
    struct Space_ x_6;
tailrec_81:;
    struct SpaceSpaceTuple2_List const* match_17;
    struct SpaceListSpaceListTuple2_ SpaceListSpaceListTuple2_ = (struct SpaceListSpaceListTuple2_){.t0 = xs_20, .t1 = ys_1};
    if ((!((!(SpaceListSpaceListTuple2_.t0))))) goto next_84;
    goto match_body_83;
next_84:;
    if ((!((!(SpaceListSpaceListTuple2_.t1))))) goto next_85;
    goto match_body_83;
match_body_83:;
    struct SpaceSpaceTuple2_List const* call_24 = listRev_2(acc_3);
    match_17 = call_24;
    goto end_match_82;
next_85:;
    if ((!(SpaceListSpaceListTuple2_.t0))) goto next_86;
    x_6 = SpaceListSpaceListTuple2_.t0->head;
    xs_21 = SpaceListSpaceListTuple2_.t0->tail;
    if ((!(SpaceListSpaceListTuple2_.t1))) goto next_86;
    y_ = SpaceListSpaceListTuple2_.t1->head;
    ys_2 = SpaceListSpaceListTuple2_.t1->tail;
    struct SpaceSpaceTuple2_ SpaceSpaceTuple2_ = (struct SpaceSpaceTuple2_){.t0 = x_6, .t1 = y_};
    struct SpaceSpaceTuple2_List const* list_12 = milone_mem_alloc(1, sizeof(struct SpaceSpaceTuple2_List));
    (*(((struct SpaceSpaceTuple2_List*)list_12))) = (struct SpaceSpaceTuple2_List){.head = SpaceSpaceTuple2_, .tail = acc_3};
    struct SpaceSpaceTuple2_List const* arg_76 = list_12;
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

struct SpaceSpaceTuple2_List const* listZip_(struct Space_List const* xs_19, struct Space_List const* ys_) {
    struct SpaceSpaceTuple2_List const* call_25 = go_20(NULL, xs_19, ys_);
    return call_25;
}

struct String go_(struct StringList const* xs_23) {
    struct StringList const* xs_24;
    struct String x_7;
    struct String match_18;
    if ((!((!(xs_23))))) goto next_88;
    match_18 = (struct String){.str = "", .len = 0};
    goto end_match_87;
next_88:;
    if ((!(xs_23))) goto next_89;
    x_7 = xs_23->head;
    xs_24 = xs_23->tail;
    struct String call_26 = go_(xs_24);
    match_18 = str_add(x_7, call_26);
    goto end_match_87;
next_89:;
    exit(1);
end_match_87:;
    return match_18;
}

struct String MatchChecker_Program_strConcat(struct StringList const* xs_22) {
    struct String call_27 = go_(xs_22);
    return call_27;
}

struct Space_ MatchChecker_Program_spaceCtor(struct String tag_, struct Space_List const* items_) {
    struct StringSpaceListTuple2_ StringSpaceListTuple2_ = (struct StringSpaceListTuple2_){.t0 = tag_, .t1 = items_};
    struct Space_ variant_ = (struct Space_){.discriminant = Ctor_, .Ctor_ = StringSpaceListTuple2_};
    return variant_;
}

struct Space_ MatchChecker_Program_spaceRef(struct String tag_1, struct UnitSpace_Fun1 thunk_) {
    struct StringUnitSpaceFun1Tuple2_ StringUnitSpaceFun1Tuple2_ = (struct StringUnitSpaceFun1Tuple2_){.t0 = tag_1, .t1 = thunk_};
    void const* box_ = milone_mem_alloc(1, sizeof(struct StringUnitSpaceFun1Tuple2_));
    (*(((struct StringUnitSpaceFun1Tuple2_*)box_))) = StringUnitSpaceFun1Tuple2_;
    struct Space_ variant_1 = (struct Space_){.discriminant = Ref_, .Ref_ = box_};
    return variant_1;
}

struct Space_List const* go_1(struct Space_List const* spaces_1, struct Space_List const* acc_4) {
    struct Space_List const* spaces_4;
    struct Space_ space_1;
    struct Space_List const* spaces_3;
    struct Space_ space_;
    struct Space_List const* spaces_2;
    struct Space_List const* subspaces_;
tailrec_90:;
    struct Space_List const* match_19;
    if ((!((!(spaces_1))))) goto next_92;
    struct Space_List const* call_28 = listRev_1(acc_4);
    match_19 = call_28;
    goto end_match_91;
next_92:;
    if ((!(spaces_1))) goto next_93;
    if ((spaces_1->head.discriminant != Union_)) goto next_93;
    subspaces_ = spaces_1->head.Union_;
    spaces_2 = spaces_1->tail;
    struct Space_List const* arg_79 = spaces_2;
    struct Space_List const* call_29 = go_1(subspaces_, acc_4);
    struct Space_List const* arg_80 = call_29;
    spaces_1 = arg_79;
    acc_4 = arg_80;
    goto tailrec_90;
next_93:;
    if ((!(spaces_1))) goto next_94;
    space_ = spaces_1->head;
    subspaces_ = spaces_1->tail;
    bool call_30 = MatchChecker_Program_spaceIsEmpty(space_);
    if ((!(call_30))) goto next_94;
    struct Space_List const* arg_81 = subspaces_;
    struct Space_List const* arg_82 = acc_4;
    spaces_1 = arg_81;
    acc_4 = arg_82;
    goto tailrec_90;
next_94:;
    if ((!(spaces_1))) goto next_95;
    space_ = spaces_1->head;
    subspaces_ = spaces_1->tail;
    struct Space_List const* arg_83 = subspaces_;
    struct Space_List const* list_13 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_13))) = (struct Space_List){.head = space_, .tail = acc_4};
    struct Space_List const* arg_84 = list_13;
    spaces_1 = arg_83;
    acc_4 = arg_84;
    goto tailrec_90;
next_95:;
    struct Space_List const* call_31 = failwith_2((struct String){.str = "NEVER: suppress warning", .len = 23});
    match_19 = call_31;
    goto end_match_91;
next_96:;
end_match_91:;
    return match_19;
}

struct Space_ MatchChecker_Program_spaceUnion(struct Space_List const* spaces_) {
    struct Space_List const* spaces_5;
    struct Space_ space_2;
    struct Space_ match_20;
    struct Space_List const* call_32 = go_1(spaces_, NULL);
    if ((!(call_32))) goto next_98;
    space_2 = call_32->head;
    if ((!((!(call_32->tail))))) goto next_98;
    match_20 = space_2;
    goto end_match_97;
next_98:;
    spaces_5 = call_32;
    struct Space_ variant_2 = (struct Space_){.discriminant = Union_, .Union_ = spaces_5};
    match_20 = variant_2;
    goto end_match_97;
next_99:;
end_match_97:;
    return match_20;
}

bool fun_8(void const* env_, struct Space_ arg_) {
    bool call_33 = MatchChecker_Program_spaceIsEmpty(arg_);
    return call_33;
}

bool fun_9(void const* env_1, struct Space_ arg_1) {
    bool call_34 = MatchChecker_Program_spaceIsEmpty(arg_1);
    return call_34;
}

bool MatchChecker_Program_spaceIsEmpty(struct Space_ space_3) {
    struct Space_List const* spaces_7;
    struct Space_List const* spaces_6;
    bool match_21;
    if ((space_3.discriminant != Ctor_)) goto next_101;
    spaces_6 = space_3.Ctor_.t1;
    struct Space_BoolFun1 fun_28 = (struct Space_BoolFun1){.fun = fun_8, .env = NULL};
    bool call_35 = listExists_(fun_28, spaces_6);
    match_21 = call_35;
    goto end_match_100;
next_101:;
    if ((space_3.discriminant != Union_)) goto next_102;
    spaces_6 = space_3.Union_;
    struct Space_BoolFun1 fun_29 = (struct Space_BoolFun1){.fun = fun_9, .env = NULL};
    bool call_36 = listForAll_2(fun_29, spaces_6);
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

struct Space_ MatchChecker_Program_spaceDecompose(struct Space_ space_4) {
    struct UnitSpace_Fun1 thunk_1;
    struct Space_ match_22;
    if ((space_4.discriminant != Ref_)) goto next_105;
    thunk_1 = (*(((struct StringUnitSpaceFun1Tuple2_ const*)space_4.Ref_))).t1;
    struct Space_ app_13 = thunk_1.fun(thunk_1.env, 0);
    struct Space_ space_5 = app_13;
    bool call_37 = MatchChecker_Program_spaceIsEmpty(space_5);
    milone_assert((!(call_37)), 195, 4);
    match_22 = space_5;
    goto end_match_104;
next_105:;
    milone_assert(false, 199, 4);
    match_22 = space_4;
    goto end_match_104;
next_106:;
end_match_104:;
    return match_22;
}

bool fun_(struct SpaceSpaceTuple2_ arg_85) {
    struct Space_ first_1 = arg_85.t0;
    struct Space_ second_1 = arg_85.t1;
    bool call_38 = MatchChecker_Program_spaceCovers(first_1, second_1);
    return call_38;
}

bool fun_10(void const* env_2, struct SpaceSpaceTuple2_ arg_2) {
    bool call_39 = fun_(arg_2);
    return call_39;
}

struct Space_ fun_1(int i_1, int j_, struct SpaceSpaceTuple2_ arg_86) {
    struct Space_ first_2 = arg_86.t0;
    struct Space_ second_2 = arg_86.t1;
    struct Space_ if_4;
    if ((i_1 == j_)) {
        goto then_108;
    } else {
        goto else_109;
    }
then_108:;
    struct Space_ call_40 = MatchChecker_Program_spaceExclude(first_2, second_2);
    if_4 = call_40;
    goto if_next_107;
else_109:;
    if_4 = first_2;
    goto if_next_107;
if_next_107:;
    return if_4;
}

struct Space_ fun_11(void const* env_3, int arg_3, struct SpaceSpaceTuple2_ arg_4) {
    int arg_5 = ((int)((intptr_t)env_3));
    struct Space_ call_41 = fun_1(arg_5, arg_3, arg_4);
    return call_41;
}

struct Space_ fun_27(struct String tag_2, struct Space_List const* firsts_, struct Space_List const* seconds_, int i_1, struct Space_ arg_87) {
    struct IntSpaceSpaceTuple2_Space_Fun2 fun_30 = (struct IntSpaceSpaceTuple2_Space_Fun2){.fun = fun_11, .env = ((void const*)((intptr_t)i_1))};
    struct SpaceSpaceTuple2_List const* call_42 = listZip_(firsts_, seconds_);
    struct Space_List const* call_43 = listMapWithIndex_1(fun_30, call_42);
    struct Space_ call_44 = MatchChecker_Program_spaceCtor(tag_2, call_43);
    return call_44;
}

struct Space_ fun_12(void const* env_4, int arg_6, struct Space_ arg_7) {
    struct String arg_8 = (*(((struct StringSpaceListSpaceListTuple3_ const*)env_4))).t0;
    struct Space_List const* arg_9 = (*(((struct StringSpaceListSpaceListTuple3_ const*)env_4))).t1;
    struct Space_List const* arg_10 = (*(((struct StringSpaceListSpaceListTuple3_ const*)env_4))).t2;
    struct Space_ call_45 = fun_27(arg_8, arg_9, arg_10, arg_6, arg_7);
    return call_45;
}

struct Space_ fun_13(void const* env_5, struct Space_ arg_11, struct Space_ arg_12) {
    struct Space_ call_46 = MatchChecker_Program_spaceExclude(arg_11, arg_12);
    return call_46;
}

struct Space_ fun_2(struct Space_ second_, struct Space_ first_3) {
    struct Space_ call_47 = MatchChecker_Program_spaceExclude(first_3, second_);
    return call_47;
}

struct Space_ fun_14(void const* env_6, struct Space_ arg_13) {
    struct Space_ arg_14 = (*(((struct Space_ const*)env_6)));
    struct Space_ call_48 = fun_2(arg_14, arg_13);
    return call_48;
}

struct Space_ MatchChecker_Program_spaceExclude(struct Space_ first_, struct Space_ second_) {
    struct String secondTag_1;
    struct String tag_3;
    struct Space_List const* firsts_1;
    struct Space_List const* seconds_1;
    struct Space_List const* seconds_;
    struct String secondTag_;
    struct Space_List const* firsts_;
    struct String tag_2;
tailrec_110:;
    struct Space_ match_23;
    struct SpaceSpaceTuple2_ SpaceSpaceTuple2_1 = (struct SpaceSpaceTuple2_){.t0 = first_, .t1 = second_};
    if ((SpaceSpaceTuple2_1.t0.discriminant != Union_)) goto next_112;
    if ((!((!(SpaceSpaceTuple2_1.t0.Union_))))) goto next_112;
    match_23 = MatchChecker_Program_spaceEmpty;
    goto end_match_111;
next_112:;
    if ((SpaceSpaceTuple2_1.t1.discriminant != Union_)) goto next_113;
    if ((!((!(SpaceSpaceTuple2_1.t1.Union_))))) goto next_113;
    match_23 = first_;
    goto end_match_111;
next_113:;
    if ((SpaceSpaceTuple2_1.t1.discriminant != Full_)) goto next_114;
    match_23 = MatchChecker_Program_spaceEmpty;
    goto end_match_111;
next_114:;
    if ((SpaceSpaceTuple2_1.t0.discriminant != Full_)) goto next_115;
    if ((SpaceSpaceTuple2_1.t1.discriminant != Ctor_)) goto next_115;
    match_23 = MatchChecker_Program_spaceFull;
    goto end_match_111;
next_115:;
    if ((SpaceSpaceTuple2_1.t0.discriminant != Ctor_)) goto next_116;
    tag_2 = SpaceSpaceTuple2_1.t0.Ctor_.t0;
    firsts_ = SpaceSpaceTuple2_1.t0.Ctor_.t1;
    if ((SpaceSpaceTuple2_1.t1.discriminant != Ctor_)) goto next_116;
    secondTag_ = SpaceSpaceTuple2_1.t1.Ctor_.t0;
    seconds_ = SpaceSpaceTuple2_1.t1.Ctor_.t1;
    if ((str_compare(tag_2, secondTag_) != 0)) goto next_116;
    struct SpaceSpaceTuple2_BoolFun1 fun_31 = (struct SpaceSpaceTuple2_BoolFun1){.fun = fun_10, .env = NULL};
    struct SpaceSpaceTuple2_List const* call_49 = listZip_(firsts_, seconds_);
    bool call_50 = listForAll_1(fun_31, call_49);
    bool dominant_ = call_50;
    struct Space_ if_5;
    if (dominant_) {
        goto then_124;
    } else {
        goto else_125;
    }
then_124:;
    if_5 = MatchChecker_Program_spaceEmpty;
    goto if_next_123;
else_125:;
    struct StringSpaceListSpaceListTuple3_ StringSpaceListSpaceListTuple3_ = (struct StringSpaceListSpaceListTuple3_){.t0 = tag_2, .t1 = firsts_, .t2 = seconds_};
    void const* box_1 = milone_mem_alloc(1, sizeof(struct StringSpaceListSpaceListTuple3_));
    (*(((struct StringSpaceListSpaceListTuple3_*)box_1))) = StringSpaceListSpaceListTuple3_;
    struct IntSpace_Space_Fun2 fun_32 = (struct IntSpace_Space_Fun2){.fun = fun_12, .env = box_1};
    struct Space_List const* call_51 = listMapWithIndex_(fun_32, firsts_);
    struct Space_ call_52 = MatchChecker_Program_spaceUnion(call_51);
    if_5 = call_52;
    goto if_next_123;
if_next_123:;
    match_23 = if_5;
    goto end_match_111;
next_116:;
    if ((SpaceSpaceTuple2_1.t0.discriminant != Ctor_)) goto next_117;
    if ((SpaceSpaceTuple2_1.t1.discriminant != Ctor_)) goto next_117;
    match_23 = first_;
    goto end_match_111;
next_117:;
    if ((SpaceSpaceTuple2_1.t1.discriminant != Union_)) goto next_118;
    firsts_ = SpaceSpaceTuple2_1.t1.Union_;
    struct Space_Space_Space_Fun2 fun_33 = (struct Space_Space_Space_Fun2){.fun = fun_13, .env = NULL};
    struct Space_ call_53 = listFold_1(fun_33, first_, firsts_);
    match_23 = call_53;
    goto end_match_111;
next_118:;
    if ((SpaceSpaceTuple2_1.t0.discriminant != Union_)) goto next_119;
    firsts_ = SpaceSpaceTuple2_1.t0.Union_;
    void const* box_2 = milone_mem_alloc(1, sizeof(struct Space_));
    (*(((struct Space_*)box_2))) = second_;
    struct Space_Space_Fun1 fun_34 = (struct Space_Space_Fun1){.fun = fun_14, .env = box_2};
    struct Space_List const* call_54 = listMap_4(fun_34, firsts_);
    struct Space_ call_55 = MatchChecker_Program_spaceUnion(call_54);
    match_23 = call_55;
    goto end_match_111;
next_119:;
    if ((SpaceSpaceTuple2_1.t0.discriminant != Ref_)) goto next_120;
    tag_2 = (*(((struct StringUnitSpaceFun1Tuple2_ const*)SpaceSpaceTuple2_1.t0.Ref_))).t0;
    if ((SpaceSpaceTuple2_1.t1.discriminant != Ref_)) goto next_120;
    secondTag_ = (*(((struct StringUnitSpaceFun1Tuple2_ const*)SpaceSpaceTuple2_1.t1.Ref_))).t0;
    if ((str_compare(tag_2, secondTag_) != 0)) goto next_120;
    match_23 = MatchChecker_Program_spaceEmpty;
    goto end_match_111;
next_120:;
    if ((SpaceSpaceTuple2_1.t0.discriminant != Ref_)) goto next_121;
    struct Space_ call_56 = MatchChecker_Program_spaceDecompose(first_);
    struct Space_ arg_88 = call_56;
    struct Space_ arg_89 = second_;
    first_ = arg_88;
    second_ = arg_89;
    goto tailrec_110;
next_121:;
    if ((SpaceSpaceTuple2_1.t1.discriminant != Ref_)) goto next_122;
    milone_assert(false, 301, 4);
    struct Space_ arg_90 = first_;
    struct Space_ call_57 = MatchChecker_Program_spaceDecompose(second_);
    struct Space_ arg_91 = call_57;
    first_ = arg_90;
    second_ = arg_91;
    goto tailrec_110;
next_122:;
    exit(1);
end_match_111:;
    return match_23;
}

bool MatchChecker_Program_spaceCovers(struct Space_ other_, struct Space_ cover_) {
    struct Space_ call_58 = MatchChecker_Program_spaceExclude(other_, cover_);
    bool call_59 = MatchChecker_Program_spaceIsEmpty(call_58);
    return call_59;
}

struct StringList const* fun_3(struct StringList const* acc_7, struct Space_ space_8) {
    struct StringList const* call_60 = cons_((struct String){.str = ", ", .len = 2}, acc_7);
    struct StringList const* call_61 = go_2(space_8, call_60);
    return call_61;
}

struct StringList const* fun_15(void const* env_7, struct StringList const* arg_15, struct Space_ arg_16) {
    struct StringList const* call_62 = fun_3(arg_15, arg_16);
    return call_62;
}

struct StringList const* fun_4(struct StringList const* acc_9, struct Space_ space_9) {
    struct StringList const* call_63 = cons_((struct String){.str = ", ", .len = 2}, acc_9);
    struct StringList const* call_64 = go_2(space_9, call_63);
    return call_64;
}

struct StringList const* fun_16(void const* env_8, struct StringList const* arg_17, struct Space_ arg_18) {
    struct StringList const* call_65 = fun_4(arg_17, arg_18);
    return call_65;
}

struct StringList const* go_2(struct Space_ space_7, struct StringList const* acc_5) {
    struct Space_List const* subspaces_1;
    struct Space_ subspace_;
    struct String tag_6;
    struct Space_List const* items_1;
    struct Space_ item_;
    struct String tag_5;
    struct String tag_4;
    struct StringList const* match_24;
    if ((space_7.discriminant != Full_)) goto next_127;
    struct StringList const* call_66 = cons_((struct String){.str = "full", .len = 4}, acc_5);
    match_24 = call_66;
    goto end_match_126;
next_127:;
    if ((space_7.discriminant != Ctor_)) goto next_128;
    tag_4 = space_7.Ctor_.t0;
    if ((!((!(space_7.Ctor_.t1))))) goto next_128;
    struct StringList const* call_67 = cons_(tag_4, acc_5);
    match_24 = call_67;
    goto end_match_126;
next_128:;
    if ((space_7.discriminant != Ctor_)) goto next_129;
    tag_4 = space_7.Ctor_.t0;
    if ((!(space_7.Ctor_.t1))) goto next_129;
    item_ = space_7.Ctor_.t1->head;
    items_1 = space_7.Ctor_.t1->tail;
    struct StringList const* call_68 = cons_(tag_4, acc_5);
    struct StringList const* call_69 = cons_((struct String){.str = "(", .len = 1}, call_68);
    struct StringList const* call_70 = go_2(item_, call_69);
    struct StringList const* acc_6 = call_70;
    struct StringListSpace_StringListFun2 fun_35 = (struct StringListSpace_StringListFun2){.fun = fun_15, .env = NULL};
    struct StringList const* call_71 = listFold_(fun_35, acc_6, items_1);
    struct StringList const* call_72 = cons_((struct String){.str = ")", .len = 1}, call_71);
    match_24 = call_72;
    goto end_match_126;
next_129:;
    if ((space_7.discriminant != Ref_)) goto next_130;
    tag_4 = (*(((struct StringUnitSpaceFun1Tuple2_ const*)space_7.Ref_))).t0;
    struct StringList const* call_73 = cons_(tag_4, acc_5);
    match_24 = call_73;
    goto end_match_126;
next_130:;
    if ((space_7.discriminant != Union_)) goto next_131;
    if ((!((!(space_7.Union_))))) goto next_131;
    struct StringList const* call_74 = cons_((struct String){.str = "empty", .len = 5}, acc_5);
    match_24 = call_74;
    goto end_match_126;
next_131:;
    if ((space_7.discriminant != Union_)) goto next_132;
    if ((!(space_7.Union_))) goto next_132;
    item_ = space_7.Union_->head;
    items_1 = space_7.Union_->tail;
    struct StringList const* call_75 = cons_((struct String){.str = "+(", .len = 2}, acc_5);
    struct StringList const* call_76 = go_2(item_, call_75);
    struct StringList const* acc_8 = call_76;
    struct StringListSpace_StringListFun2 fun_36 = (struct StringListSpace_StringListFun2){.fun = fun_16, .env = NULL};
    struct StringList const* call_77 = listFold_(fun_36, acc_8, items_1);
    struct StringList const* call_78 = cons_((struct String){.str = ")", .len = 1}, call_77);
    match_24 = call_78;
    goto end_match_126;
next_132:;
    struct StringList const* call_79 = failwith_1((struct String){.str = "NEVER: suppress warning", .len = 23});
    match_24 = call_79;
    goto end_match_126;
next_133:;
end_match_126:;
    return match_24;
}

struct String MatchChecker_Program_spaceToString(struct Space_ space_6) {
    struct StringList const* call_80 = go_2(space_6, NULL);
    struct StringList const* call_81 = listRev_(call_80);
    struct String call_82 = MatchChecker_Program_strConcat(call_81);
    return call_82;
}

struct Space_ fun_17(void const* env_9, struct Ty_ arg_19) {
    struct Space_ call_83 = go_3(arg_19);
    return call_83;
}

struct Space_ fun_18(void const* env_10, char arg_20) {
    struct Space_ arg_21 = (*(((struct Space_ const*)env_10)));
    struct Space_ call_84 = thunk_2(arg_21, 0);
    return call_84;
}

struct Space_ thunk_2(struct Space_ itemSpace_, char arg_92) {
    struct Space_ call_85 = MatchChecker_Program_spaceCtor((struct String){.str = "nil", .len = 3}, NULL);
    void const* box_3 = milone_mem_alloc(1, sizeof(struct Space_));
    (*(((struct Space_*)box_3))) = itemSpace_;
    struct UnitSpace_Fun1 fun_37 = (struct UnitSpace_Fun1){.fun = fun_18, .env = box_3};
    struct Space_ call_86 = MatchChecker_Program_spaceRef((struct String){.str = "list", .len = 4}, fun_37);
    struct Space_List const* list_17 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_17))) = (struct Space_List){.head = call_86, .tail = NULL};
    struct Space_List const* list_16 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_16))) = (struct Space_List){.head = itemSpace_, .tail = list_17};
    struct Space_ call_87 = MatchChecker_Program_spaceCtor((struct String){.str = "cons", .len = 4}, list_16);
    struct Space_List const* list_15 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_15))) = (struct Space_List){.head = call_87, .tail = NULL};
    struct Space_List const* list_14 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_14))) = (struct Space_List){.head = call_85, .tail = list_15};
    struct Space_ call_88 = MatchChecker_Program_spaceUnion(list_14);
    return call_88;
}

struct Space_ fun_19(void const* env_11, char arg_22) {
    struct Space_ arg_23 = (*(((struct Space_ const*)env_11)));
    struct Space_ call_89 = thunk_2(arg_23, 0);
    return call_89;
}

struct Space_ go_3(struct Ty_ ty_1) {
    struct Ty_ itemTy_;
    struct Ty_List const* itemTys_;
    struct Space_ match_25;
    if ((ty_1.discriminant != Int_)) goto next_135;
    match_25 = MatchChecker_Program_spaceFull;
    goto end_match_134;
next_135:;
    if ((ty_1.discriminant != Tuple_)) goto next_136;
    itemTys_ = ty_1.Tuple_;
    struct Ty_Space_Fun1 fun_38 = (struct Ty_Space_Fun1){.fun = fun_17, .env = NULL};
    struct Space_List const* call_90 = listMap_3(fun_38, itemTys_);
    struct Space_ call_91 = MatchChecker_Program_spaceCtor((struct String){.str = "tuple", .len = 5}, call_90);
    match_25 = call_91;
    goto end_match_134;
next_136:;
    if ((ty_1.discriminant != List_)) goto next_137;
    itemTy_ = (*(((struct Ty_ const*)ty_1.List_)));
    struct Space_ call_92 = go_3(itemTy_);
    struct Space_ itemSpace_ = call_92;
    void const* box_4 = milone_mem_alloc(1, sizeof(struct Space_));
    (*(((struct Space_*)box_4))) = itemSpace_;
    struct UnitSpace_Fun1 fun_39 = (struct UnitSpace_Fun1){.fun = fun_19, .env = box_4};
    struct Space_ call_93 = MatchChecker_Program_spaceRef((struct String){.str = "list", .len = 4}, fun_39);
    match_25 = call_93;
    goto end_match_134;
next_137:;
    exit(1);
end_match_134:;
    return match_25;
}

struct Space_ MatchChecker_Program_tyToSpace(struct Ty_ ty_) {
    struct Space_ call_94 = go_3(ty_);
    return call_94;
}

struct Space_ fun_20(void const* env_12, struct Pat_ arg_24) {
    struct Space_ call_95 = go_4(arg_24);
    return call_95;
}

struct Space_ go_4(struct Pat_ pat_1) {
    struct Pat_ tailPat_;
    struct Pat_ headPat_;
    struct Pat_List const* itemPats_;
    struct Space_ match_26;
    if ((pat_1.discriminant != Discard_)) goto next_139;
    match_26 = MatchChecker_Program_spaceFull;
    goto end_match_138;
next_139:;
    if ((pat_1.discriminant != IntLit_)) goto next_140;
    match_26 = MatchChecker_Program_spaceEmpty;
    goto end_match_138;
next_140:;
    if ((pat_1.discriminant != TupleLit_)) goto next_141;
    itemPats_ = pat_1.TupleLit_;
    struct Pat_Space_Fun1 fun_40 = (struct Pat_Space_Fun1){.fun = fun_20, .env = NULL};
    struct Space_List const* call_96 = listMap_2(fun_40, itemPats_);
    struct Space_ call_97 = MatchChecker_Program_spaceCtor((struct String){.str = "tuple", .len = 5}, call_96);
    match_26 = call_97;
    goto end_match_138;
next_141:;
    if ((pat_1.discriminant != Nil_)) goto next_142;
    struct Space_ call_98 = MatchChecker_Program_spaceCtor((struct String){.str = "nil", .len = 3}, NULL);
    match_26 = call_98;
    goto end_match_138;
next_142:;
    if ((pat_1.discriminant != Cons_)) goto next_143;
    headPat_ = (*(((struct PatPatTuple2_ const*)pat_1.Cons_))).t0;
    tailPat_ = (*(((struct PatPatTuple2_ const*)pat_1.Cons_))).t1;
    struct Space_ call_99 = go_4(headPat_);
    struct Space_ call_100 = go_4(tailPat_);
    struct Space_List const* list_19 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_19))) = (struct Space_List){.head = call_100, .tail = NULL};
    struct Space_List const* list_18 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_18))) = (struct Space_List){.head = call_99, .tail = list_19};
    struct Space_ call_101 = MatchChecker_Program_spaceCtor((struct String){.str = "cons", .len = 4}, list_18);
    match_26 = call_101;
    goto end_match_138;
next_143:;
    struct Space_ call_102 = failwith_((struct String){.str = "NEVER: suppress warning", .len = 23});
    match_26 = call_102;
    goto end_match_138;
next_144:;
end_match_138:;
    return match_26;
}

struct Space_ MatchChecker_Program_patToSpace(struct Pat_ pat_) {
    struct Space_ call_103 = go_4(pat_);
    return call_103;
}

struct Space_ fun_21(void const* env_13, struct Pat_ arg_25) {
    struct Space_ call_104 = MatchChecker_Program_patToSpace(arg_25);
    return call_104;
}

struct Space_ MatchChecker_Program_patsToSpace(struct Pat_List const* pats_) {
    struct Pat_Space_Fun1 fun_41 = (struct Pat_Space_Fun1){.fun = fun_21, .env = NULL};
    struct Space_List const* call_105 = listMap_2(fun_41, pats_);
    struct Space_ call_106 = MatchChecker_Program_spaceUnion(call_105);
    return call_106;
}

struct Space_ fun_5(char arg_93) {
    return MatchChecker_Program_spaceFull;
}

struct Space_ fun_22(void const* env_14, char arg_26) {
    struct Space_ call_107 = fun_5(0);
    return call_107;
}

char MatchChecker_Program_testSpaceIsEmpty(char arg_94) {
    bool call_108 = MatchChecker_Program_spaceIsEmpty(MatchChecker_Program_spaceEmpty);
    milone_assert(call_108, 392, 2);
    struct Space_List const* list_22 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_22))) = (struct Space_List){.head = MatchChecker_Program_spaceEmpty, .tail = NULL};
    struct Space_ call_109 = MatchChecker_Program_spaceUnion(list_22);
    struct Space_List const* list_21 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_21))) = (struct Space_List){.head = call_109, .tail = NULL};
    struct Space_List const* list_20 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_20))) = (struct Space_List){.head = MatchChecker_Program_spaceEmpty, .tail = list_21};
    struct Space_ call_110 = MatchChecker_Program_spaceUnion(list_20);
    bool call_111 = MatchChecker_Program_spaceIsEmpty(call_110);
    milone_assert(call_111, 394, 2);
    bool call_112 = MatchChecker_Program_spaceIsEmpty(MatchChecker_Program_spaceFull);
    milone_assert((!(call_112)), 398, 2);
    struct UnitSpace_Fun1 fun_42 = (struct UnitSpace_Fun1){.fun = fun_22, .env = NULL};
    struct Space_ call_113 = MatchChecker_Program_spaceRef((struct String){.str = "ref", .len = 3}, fun_42);
    bool call_114 = MatchChecker_Program_spaceIsEmpty(call_113);
    milone_assert((!(call_114)), 400, 2);
    struct Space_List const* list_24 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_24))) = (struct Space_List){.head = MatchChecker_Program_spaceFull, .tail = NULL};
    struct Space_List const* list_23 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_23))) = (struct Space_List){.head = MatchChecker_Program_spaceEmpty, .tail = list_24};
    struct Space_ call_115 = MatchChecker_Program_spaceUnion(list_23);
    bool call_116 = MatchChecker_Program_spaceIsEmpty(call_115);
    milone_assert((!(call_116)), 404, 2);
    struct Space_ call_117 = MatchChecker_Program_spaceCtor((struct String){.str = "tuple", .len = 5}, NULL);
    bool call_118 = MatchChecker_Program_spaceIsEmpty(call_117);
    milone_assert((!(call_118)), 408, 2);
    struct Space_List const* list_27 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_27))) = (struct Space_List){.head = MatchChecker_Program_spaceFull, .tail = NULL};
    struct Space_List const* list_26 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_26))) = (struct Space_List){.head = MatchChecker_Program_spaceEmpty, .tail = list_27};
    struct Space_List const* list_25 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_25))) = (struct Space_List){.head = MatchChecker_Program_spaceFull, .tail = list_26};
    struct Space_ call_119 = MatchChecker_Program_spaceCtor((struct String){.str = "tuple", .len = 5}, list_25);
    bool call_120 = MatchChecker_Program_spaceIsEmpty(call_119);
    milone_assert(call_120, 410, 2);
    void const* box_5 = milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_5))) = (struct Ty_){.discriminant = Int_};
    struct Ty_ variant_3 = (struct Ty_){.discriminant = List_, .List_ = box_5};
    struct Space_ call_121 = MatchChecker_Program_tyToSpace(variant_3);
    bool call_122 = MatchChecker_Program_spaceIsEmpty(call_121);
    milone_assert((!(call_122)), 413, 2);
    struct Ty_ variant_4 = (struct Ty_){.discriminant = Tuple_, .Tuple_ = NULL};
    void const* box_6 = milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_6))) = variant_4;
    struct Ty_ variant_5 = (struct Ty_){.discriminant = List_, .List_ = box_6};
    struct Space_ call_123 = MatchChecker_Program_tyToSpace(variant_5);
    bool call_124 = MatchChecker_Program_spaceIsEmpty(call_123);
    milone_assert((!(call_124)), 415, 2);
    return 0;
}

bool fun_23(void const* env_15, bool arg_27) {
    bool call_125 = id_(arg_27);
    return call_125;
}

bool fun_6(struct StringSpaceTuple2_ arg_95) {
    struct String expected_ = arg_95.t0;
    struct Space_ space_10 = arg_95.t1;
    struct String call_126 = MatchChecker_Program_spaceToString(space_10);
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

bool fun_24(void const* env_16, struct StringSpaceTuple2_ arg_28) {
    bool call_127 = fun_6(arg_28);
    return call_127;
}

char MatchChecker_Program_testSpaceToString(char arg_96) {
    struct StringSpaceTuple2_ StringSpaceTuple2_ = (struct StringSpaceTuple2_){.t0 = (struct String){.str = "empty", .len = 5}, .t1 = MatchChecker_Program_spaceEmpty};
    struct StringSpaceTuple2_ StringSpaceTuple2_1 = (struct StringSpaceTuple2_){.t0 = (struct String){.str = "full", .len = 4}, .t1 = MatchChecker_Program_spaceFull};
    struct Space_ call_128 = MatchChecker_Program_spaceCtor((struct String){.str = "nil", .len = 3}, NULL);
    struct StringSpaceTuple2_ StringSpaceTuple2_2 = (struct StringSpaceTuple2_){.t0 = (struct String){.str = "nil", .len = 3}, .t1 = call_128};
    struct Space_List const* list_33 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_33))) = (struct Space_List){.head = MatchChecker_Program_spaceFull, .tail = NULL};
    struct Space_List const* list_32 = milone_mem_alloc(1, sizeof(struct Space_List));
    (*(((struct Space_List*)list_32))) = (struct Space_List){.head = MatchChecker_Program_spaceEmpty, .tail = list_33};
    struct Space_ call_129 = MatchChecker_Program_spaceCtor((struct String){.str = "tuple", .len = 5}, list_32);
    struct StringSpaceTuple2_ StringSpaceTuple2_3 = (struct StringSpaceTuple2_){.t0 = (struct String){.str = "tuple(empty, full)", .len = 18}, .t1 = call_129};
    struct Space_ call_130 = MatchChecker_Program_tyToSpace((struct Ty_){.discriminant = Int_});
    struct StringSpaceTuple2_ StringSpaceTuple2_4 = (struct StringSpaceTuple2_){.t0 = (struct String){.str = "full", .len = 4}, .t1 = call_130};
    void const* box_7 = milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_7))) = (struct Ty_){.discriminant = Int_};
    struct Ty_ variant_6 = (struct Ty_){.discriminant = List_, .List_ = box_7};
    struct Space_ call_131 = MatchChecker_Program_tyToSpace(variant_6);
    struct Space_ call_132 = MatchChecker_Program_spaceDecompose(call_131);
    struct StringSpaceTuple2_ StringSpaceTuple2_5 = (struct StringSpaceTuple2_){.t0 = (struct String){.str = "+(nil, cons(full, list))", .len = 24}, .t1 = call_132};
    struct PatPatTuple2_ PatPatTuple2_ = (struct PatPatTuple2_){.t0 = (struct Pat_){.discriminant = Discard_}, .t1 = (struct Pat_){.discriminant = Nil_}};
    void const* box_8 = milone_mem_alloc(1, sizeof(struct PatPatTuple2_));
    (*(((struct PatPatTuple2_*)box_8))) = PatPatTuple2_;
    struct Pat_ variant_7 = (struct Pat_){.discriminant = Cons_, .Cons_ = box_8};
    struct Space_ call_133 = MatchChecker_Program_patToSpace(variant_7);
    struct StringSpaceTuple2_ StringSpaceTuple2_6 = (struct StringSpaceTuple2_){.t0 = (struct String){.str = "cons(full, nil)", .len = 15}, .t1 = call_133};
    struct StringSpaceTuple2_List const* list_36 = milone_mem_alloc(1, sizeof(struct StringSpaceTuple2_List));
    (*(((struct StringSpaceTuple2_List*)list_36))) = (struct StringSpaceTuple2_List){.head = StringSpaceTuple2_6, .tail = NULL};
    struct StringSpaceTuple2_List const* list_35 = milone_mem_alloc(1, sizeof(struct StringSpaceTuple2_List));
    (*(((struct StringSpaceTuple2_List*)list_35))) = (struct StringSpaceTuple2_List){.head = StringSpaceTuple2_5, .tail = list_36};
    struct StringSpaceTuple2_List const* list_34 = milone_mem_alloc(1, sizeof(struct StringSpaceTuple2_List));
    (*(((struct StringSpaceTuple2_List*)list_34))) = (struct StringSpaceTuple2_List){.head = StringSpaceTuple2_4, .tail = list_35};
    struct StringSpaceTuple2_List const* list_31 = milone_mem_alloc(1, sizeof(struct StringSpaceTuple2_List));
    (*(((struct StringSpaceTuple2_List*)list_31))) = (struct StringSpaceTuple2_List){.head = StringSpaceTuple2_3, .tail = list_34};
    struct StringSpaceTuple2_List const* list_30 = milone_mem_alloc(1, sizeof(struct StringSpaceTuple2_List));
    (*(((struct StringSpaceTuple2_List*)list_30))) = (struct StringSpaceTuple2_List){.head = StringSpaceTuple2_2, .tail = list_31};
    struct StringSpaceTuple2_List const* list_29 = milone_mem_alloc(1, sizeof(struct StringSpaceTuple2_List));
    (*(((struct StringSpaceTuple2_List*)list_29))) = (struct StringSpaceTuple2_List){.head = StringSpaceTuple2_1, .tail = list_30};
    struct StringSpaceTuple2_List const* list_28 = milone_mem_alloc(1, sizeof(struct StringSpaceTuple2_List));
    (*(((struct StringSpaceTuple2_List*)list_28))) = (struct StringSpaceTuple2_List){.head = StringSpaceTuple2_, .tail = list_29};
    struct StringSpaceTuple2_List const* cases_ = list_28;
    struct BoolBoolFun1 fun_43 = (struct BoolBoolFun1){.fun = fun_23, .env = NULL};
    struct StringSpaceTuple2_BoolFun1 fun_44 = (struct StringSpaceTuple2_BoolFun1){.fun = fun_24, .env = NULL};
    struct BoolList const* call_134 = listMap_1(fun_44, cases_);
    bool call_135 = listForAll_(fun_43, call_134);
    bool ok_ = call_135;
    milone_assert(ok_, 442, 2);
    return 0;
}

bool fun_25(void const* env_17, bool arg_29) {
    bool call_136 = id_(arg_29);
    return call_136;
}

bool fun_7(struct StringTyPatListCoveringTuple4_ arg_97) {
    struct String name_ = arg_97.t0;
    struct Ty_ ty_2 = arg_97.t1;
    struct Pat_List const* pats_1 = arg_97.t2;
    struct Covering_ covering_ = arg_97.t3;
    struct Space_ call_137 = MatchChecker_Program_tyToSpace(ty_2);
    struct Space_ tySpace_ = call_137;
    struct Space_ call_138 = MatchChecker_Program_patsToSpace(pats_1);
    struct Space_ patSpace_ = call_138;
    bool call_139 = MatchChecker_Program_spaceCovers(tySpace_, patSpace_);
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
    struct BoolStringTuple2_ match_27;
    struct CoveringCoveringTuple2_ CoveringCoveringTuple2_ = (struct CoveringCoveringTuple2_){.t0 = covering_, .t1 = actual_1};
    if ((CoveringCoveringTuple2_.t0.discriminant != Covering_)) goto next_153;
    if ((CoveringCoveringTuple2_.t1.discriminant != Covering_)) goto next_153;
    goto match_body_152;
next_153:;
    if ((CoveringCoveringTuple2_.t0.discriminant != Open_)) goto next_154;
    if ((CoveringCoveringTuple2_.t1.discriminant != Open_)) goto next_154;
    goto match_body_152;
match_body_152:;
    struct BoolStringTuple2_ BoolStringTuple2_ = (struct BoolStringTuple2_){.t0 = true, .t1 = (struct String){.str = "OK", .len = 2}};
    match_27 = BoolStringTuple2_;
    goto end_match_151;
next_154:;
    if ((CoveringCoveringTuple2_.t0.discriminant != Covering_)) goto next_155;
    if ((CoveringCoveringTuple2_.t1.discriminant != Open_)) goto next_155;
    struct BoolStringTuple2_ BoolStringTuple2_1 = (struct BoolStringTuple2_){.t0 = false, .t1 = (struct String){.str = "NG. Expected covering but open", .len = 30}};
    match_27 = BoolStringTuple2_1;
    goto end_match_151;
next_155:;
    struct BoolStringTuple2_ BoolStringTuple2_2 = (struct BoolStringTuple2_){.t0 = false, .t1 = (struct String){.str = "NG. Expected open but covering", .len = 30}};
    match_27 = BoolStringTuple2_2;
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
    struct String call_140 = MatchChecker_Program_spaceToString(tySpace_);
    printf("  ty: %s\n", str_to_c_str(call_140));
    struct String call_141 = MatchChecker_Program_spaceToString(patSpace_);
    printf("  pats: %s\n", str_to_c_str(call_141));
    if_8 = 0;
    goto if_next_157;
else_159:;
    if_8 = 0;
    goto if_next_157;
if_next_157:;
    return ok_2;
}

bool fun_26(void const* env_18, struct StringTyPatListCoveringTuple4_ arg_30) {
    bool call_142 = fun_7(arg_30);
    return call_142;
}

int milone_main() {
    MatchChecker_Program_spaceFull = (struct Space_){.discriminant = Full_};
    struct Space_ variant_8 = (struct Space_){.discriminant = Union_, .Union_ = NULL};
    MatchChecker_Program_spaceEmpty = variant_8;
    char call_143 = MatchChecker_Program_testSpaceIsEmpty(0);
    char call_144 = MatchChecker_Program_testSpaceToString(0);
    struct PatPatTuple2_ PatPatTuple2_1 = (struct PatPatTuple2_){.t0 = (struct Pat_){.discriminant = Discard_}, .t1 = (struct Pat_){.discriminant = Discard_}};
    void const* box_9 = milone_mem_alloc(1, sizeof(struct PatPatTuple2_));
    (*(((struct PatPatTuple2_*)box_9))) = PatPatTuple2_1;
    struct Pat_ variant_9 = (struct Pat_){.discriminant = Cons_, .Cons_ = box_9};
    struct Pat_ anyConsPat_ = variant_9;
    struct Ty_ variant_10 = (struct Ty_){.discriminant = Tuple_, .Tuple_ = NULL};
    struct Pat_ variant_11 = (struct Pat_){.discriminant = TupleLit_, .TupleLit_ = NULL};
    struct Pat_List const* list_38 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_38))) = (struct Pat_List){.head = variant_11, .tail = NULL};
    struct StringTyPatListCoveringTuple4_ StringTyPatListCoveringTuple4_ = (struct StringTyPatListCoveringTuple4_){.t0 = (struct String){.str = "unit with ()", .len = 12}, .t1 = variant_10, .t2 = list_38, .t3 = (struct Covering_){.discriminant = Covering_}};
    struct Pat_ variant_12 = (struct Pat_){.discriminant = IntLit_, .IntLit_ = 1};
    struct Pat_List const* list_40 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_40))) = (struct Pat_List){.head = variant_12, .tail = NULL};
    struct StringTyPatListCoveringTuple4_ StringTyPatListCoveringTuple4_1 = (struct StringTyPatListCoveringTuple4_){.t0 = (struct String){.str = "int with literal pats", .len = 21}, .t1 = (struct Ty_){.discriminant = Int_}, .t2 = list_40, .t3 = (struct Covering_){.discriminant = Open_}};
    struct Pat_List const* list_42 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_42))) = (struct Pat_List){.head = (struct Pat_){.discriminant = Discard_}, .tail = NULL};
    struct StringTyPatListCoveringTuple4_ StringTyPatListCoveringTuple4_2 = (struct StringTyPatListCoveringTuple4_){.t0 = (struct String){.str = "int with _", .len = 10}, .t1 = (struct Ty_){.discriminant = Int_}, .t2 = list_42, .t3 = (struct Covering_){.discriminant = Covering_}};
    struct Pat_ variant_13 = (struct Pat_){.discriminant = IntLit_, .IntLit_ = 1};
    struct Pat_List const* list_45 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_45))) = (struct Pat_List){.head = (struct Pat_){.discriminant = Discard_}, .tail = NULL};
    struct Pat_List const* list_44 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_44))) = (struct Pat_List){.head = variant_13, .tail = list_45};
    struct StringTyPatListCoveringTuple4_ StringTyPatListCoveringTuple4_3 = (struct StringTyPatListCoveringTuple4_){.t0 = (struct String){.str = "int with 1|_", .len = 12}, .t1 = (struct Ty_){.discriminant = Int_}, .t2 = list_44, .t3 = (struct Covering_){.discriminant = Covering_}};
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
    struct StringTyPatListCoveringTuple4_ StringTyPatListCoveringTuple4_4 = (struct StringTyPatListCoveringTuple4_){.t0 = (struct String){.str = "int * unit with _, ()", .len = 21}, .t1 = variant_15, .t2 = list_49, .t3 = (struct Covering_){.discriminant = Covering_}};
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
    struct StringTyPatListCoveringTuple4_ StringTyPatListCoveringTuple4_5 = (struct StringTyPatListCoveringTuple4_){.t0 = (struct String){.str = "int * int with 1, _ | _, 1", .len = 26}, .t1 = variant_18, .t2 = list_55, .t3 = (struct Covering_){.discriminant = Open_}};
    void const* box_10 = milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_10))) = (struct Ty_){.discriminant = Int_};
    struct Ty_ variant_23 = (struct Ty_){.discriminant = List_, .List_ = box_10};
    struct Pat_List const* list_62 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_62))) = (struct Pat_List){.head = (struct Pat_){.discriminant = Nil_}, .tail = NULL};
    struct StringTyPatListCoveringTuple4_ StringTyPatListCoveringTuple4_6 = (struct StringTyPatListCoveringTuple4_){.t0 = (struct String){.str = "int list with []", .len = 16}, .t1 = variant_23, .t2 = list_62, .t3 = (struct Covering_){.discriminant = Open_}};
    void const* box_11 = milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_11))) = (struct Ty_){.discriminant = Int_};
    struct Ty_ variant_24 = (struct Ty_){.discriminant = List_, .List_ = box_11};
    struct Pat_List const* list_64 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_64))) = (struct Pat_List){.head = anyConsPat_, .tail = NULL};
    struct StringTyPatListCoveringTuple4_ StringTyPatListCoveringTuple4_7 = (struct StringTyPatListCoveringTuple4_){.t0 = (struct String){.str = "int list with _::_", .len = 18}, .t1 = variant_24, .t2 = list_64, .t3 = (struct Covering_){.discriminant = Open_}};
    void const* box_12 = milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_12))) = (struct Ty_){.discriminant = Int_};
    struct Ty_ variant_25 = (struct Ty_){.discriminant = List_, .List_ = box_12};
    struct Pat_List const* list_67 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_67))) = (struct Pat_List){.head = anyConsPat_, .tail = NULL};
    struct Pat_List const* list_66 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_66))) = (struct Pat_List){.head = (struct Pat_){.discriminant = Nil_}, .tail = list_67};
    struct StringTyPatListCoveringTuple4_ StringTyPatListCoveringTuple4_8 = (struct StringTyPatListCoveringTuple4_){.t0 = (struct String){.str = "int list with [] | _::_", .len = 23}, .t1 = variant_25, .t2 = list_66, .t3 = (struct Covering_){.discriminant = Covering_}};
    void const* box_13 = milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_13))) = (struct Ty_){.discriminant = Int_};
    struct Ty_ variant_26 = (struct Ty_){.discriminant = List_, .List_ = box_13};
    struct PatPatTuple2_ PatPatTuple2_2 = (struct PatPatTuple2_){.t0 = (struct Pat_){.discriminant = Discard_}, .t1 = (struct Pat_){.discriminant = Nil_}};
    void const* box_14 = milone_mem_alloc(1, sizeof(struct PatPatTuple2_));
    (*(((struct PatPatTuple2_*)box_14))) = PatPatTuple2_2;
    struct Pat_ variant_27 = (struct Pat_){.discriminant = Cons_, .Cons_ = box_14};
    struct PatPatTuple2_ PatPatTuple2_3 = (struct PatPatTuple2_){.t0 = (struct Pat_){.discriminant = Discard_}, .t1 = anyConsPat_};
    void const* box_15 = milone_mem_alloc(1, sizeof(struct PatPatTuple2_));
    (*(((struct PatPatTuple2_*)box_15))) = PatPatTuple2_3;
    struct Pat_ variant_28 = (struct Pat_){.discriminant = Cons_, .Cons_ = box_15};
    struct Pat_List const* list_71 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_71))) = (struct Pat_List){.head = variant_28, .tail = NULL};
    struct Pat_List const* list_70 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_70))) = (struct Pat_List){.head = variant_27, .tail = list_71};
    struct Pat_List const* list_69 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_69))) = (struct Pat_List){.head = (struct Pat_){.discriminant = Nil_}, .tail = list_70};
    struct StringTyPatListCoveringTuple4_ StringTyPatListCoveringTuple4_9 = (struct StringTyPatListCoveringTuple4_){.t0 = (struct String){.str = "int list with [] | [_] | _::_::_", .len = 32}, .t1 = variant_26, .t2 = list_69, .t3 = (struct Covering_){.discriminant = Covering_}};
    void const* box_16 = milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_16))) = (struct Ty_){.discriminant = Int_};
    struct Ty_ variant_29 = (struct Ty_){.discriminant = List_, .List_ = box_16};
    void const* box_17 = milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_17))) = variant_29;
    struct Ty_ variant_30 = (struct Ty_){.discriminant = List_, .List_ = box_17};
    struct PatPatTuple2_ PatPatTuple2_4 = (struct PatPatTuple2_){.t0 = (struct Pat_){.discriminant = Nil_}, .t1 = (struct Pat_){.discriminant = Nil_}};
    void const* box_18 = milone_mem_alloc(1, sizeof(struct PatPatTuple2_));
    (*(((struct PatPatTuple2_*)box_18))) = PatPatTuple2_4;
    struct Pat_ variant_31 = (struct Pat_){.discriminant = Cons_, .Cons_ = box_18};
    struct PatPatTuple2_ PatPatTuple2_5 = (struct PatPatTuple2_){.t0 = anyConsPat_, .t1 = (struct Pat_){.discriminant = Discard_}};
    void const* box_19 = milone_mem_alloc(1, sizeof(struct PatPatTuple2_));
    (*(((struct PatPatTuple2_*)box_19))) = PatPatTuple2_5;
    struct Pat_ variant_32 = (struct Pat_){.discriminant = Cons_, .Cons_ = box_19};
    struct PatPatTuple2_ PatPatTuple2_6 = (struct PatPatTuple2_){.t0 = (struct Pat_){.discriminant = Discard_}, .t1 = anyConsPat_};
    void const* box_20 = milone_mem_alloc(1, sizeof(struct PatPatTuple2_));
    (*(((struct PatPatTuple2_*)box_20))) = PatPatTuple2_6;
    struct Pat_ variant_33 = (struct Pat_){.discriminant = Cons_, .Cons_ = box_20};
    struct Pat_List const* list_76 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_76))) = (struct Pat_List){.head = variant_33, .tail = NULL};
    struct Pat_List const* list_75 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_75))) = (struct Pat_List){.head = variant_32, .tail = list_76};
    struct Pat_List const* list_74 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_74))) = (struct Pat_List){.head = variant_31, .tail = list_75};
    struct Pat_List const* list_73 = milone_mem_alloc(1, sizeof(struct Pat_List));
    (*(((struct Pat_List*)list_73))) = (struct Pat_List){.head = (struct Pat_){.discriminant = Nil_}, .tail = list_74};
    struct StringTyPatListCoveringTuple4_ StringTyPatListCoveringTuple4_10 = (struct StringTyPatListCoveringTuple4_){.t0 = (struct String){.str = "int list list with [] | [[]] | [_::_] | _::_::_", .len = 47}, .t1 = variant_30, .t2 = list_73, .t3 = (struct Covering_){.discriminant = Covering_}};
    void const* box_21 = milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_21))) = (struct Ty_){.discriminant = Int_};
    struct Ty_ variant_34 = (struct Ty_){.discriminant = List_, .List_ = box_21};
    void const* box_22 = milone_mem_alloc(1, sizeof(struct Ty_));
    (*(((struct Ty_*)box_22))) = (struct Ty_){.discriminant = Int_};
    struct Ty_ variant_35 = (struct Ty_){.discriminant = List_, .List_ = box_22};
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
    struct StringTyPatListCoveringTuple4_ StringTyPatListCoveringTuple4_11 = (struct StringTyPatListCoveringTuple4_){.t0 = (struct String){.str = "int list * int list with [], [] | [], _::_ | _::_, [] | _::_, _::_", .len = 66}, .t1 = variant_36, .t2 = list_80, .t3 = (struct Covering_){.discriminant = Covering_}};
    struct StringTyPatListCoveringTuple4_List const* list_77 = milone_mem_alloc(1, sizeof(struct StringTyPatListCoveringTuple4_List));
    (*(((struct StringTyPatListCoveringTuple4_List*)list_77))) = (struct StringTyPatListCoveringTuple4_List){.head = StringTyPatListCoveringTuple4_11, .tail = NULL};
    struct StringTyPatListCoveringTuple4_List const* list_72 = milone_mem_alloc(1, sizeof(struct StringTyPatListCoveringTuple4_List));
    (*(((struct StringTyPatListCoveringTuple4_List*)list_72))) = (struct StringTyPatListCoveringTuple4_List){.head = StringTyPatListCoveringTuple4_10, .tail = list_77};
    struct StringTyPatListCoveringTuple4_List const* list_68 = milone_mem_alloc(1, sizeof(struct StringTyPatListCoveringTuple4_List));
    (*(((struct StringTyPatListCoveringTuple4_List*)list_68))) = (struct StringTyPatListCoveringTuple4_List){.head = StringTyPatListCoveringTuple4_9, .tail = list_72};
    struct StringTyPatListCoveringTuple4_List const* list_65 = milone_mem_alloc(1, sizeof(struct StringTyPatListCoveringTuple4_List));
    (*(((struct StringTyPatListCoveringTuple4_List*)list_65))) = (struct StringTyPatListCoveringTuple4_List){.head = StringTyPatListCoveringTuple4_8, .tail = list_68};
    struct StringTyPatListCoveringTuple4_List const* list_63 = milone_mem_alloc(1, sizeof(struct StringTyPatListCoveringTuple4_List));
    (*(((struct StringTyPatListCoveringTuple4_List*)list_63))) = (struct StringTyPatListCoveringTuple4_List){.head = StringTyPatListCoveringTuple4_7, .tail = list_65};
    struct StringTyPatListCoveringTuple4_List const* list_61 = milone_mem_alloc(1, sizeof(struct StringTyPatListCoveringTuple4_List));
    (*(((struct StringTyPatListCoveringTuple4_List*)list_61))) = (struct StringTyPatListCoveringTuple4_List){.head = StringTyPatListCoveringTuple4_6, .tail = list_63};
    struct StringTyPatListCoveringTuple4_List const* list_52 = milone_mem_alloc(1, sizeof(struct StringTyPatListCoveringTuple4_List));
    (*(((struct StringTyPatListCoveringTuple4_List*)list_52))) = (struct StringTyPatListCoveringTuple4_List){.head = StringTyPatListCoveringTuple4_5, .tail = list_61};
    struct StringTyPatListCoveringTuple4_List const* list_46 = milone_mem_alloc(1, sizeof(struct StringTyPatListCoveringTuple4_List));
    (*(((struct StringTyPatListCoveringTuple4_List*)list_46))) = (struct StringTyPatListCoveringTuple4_List){.head = StringTyPatListCoveringTuple4_4, .tail = list_52};
    struct StringTyPatListCoveringTuple4_List const* list_43 = milone_mem_alloc(1, sizeof(struct StringTyPatListCoveringTuple4_List));
    (*(((struct StringTyPatListCoveringTuple4_List*)list_43))) = (struct StringTyPatListCoveringTuple4_List){.head = StringTyPatListCoveringTuple4_3, .tail = list_46};
    struct StringTyPatListCoveringTuple4_List const* list_41 = milone_mem_alloc(1, sizeof(struct StringTyPatListCoveringTuple4_List));
    (*(((struct StringTyPatListCoveringTuple4_List*)list_41))) = (struct StringTyPatListCoveringTuple4_List){.head = StringTyPatListCoveringTuple4_2, .tail = list_43};
    struct StringTyPatListCoveringTuple4_List const* list_39 = milone_mem_alloc(1, sizeof(struct StringTyPatListCoveringTuple4_List));
    (*(((struct StringTyPatListCoveringTuple4_List*)list_39))) = (struct StringTyPatListCoveringTuple4_List){.head = StringTyPatListCoveringTuple4_1, .tail = list_41};
    struct StringTyPatListCoveringTuple4_List const* list_37 = milone_mem_alloc(1, sizeof(struct StringTyPatListCoveringTuple4_List));
    (*(((struct StringTyPatListCoveringTuple4_List*)list_37))) = (struct StringTyPatListCoveringTuple4_List){.head = StringTyPatListCoveringTuple4_, .tail = list_39};
    struct StringTyPatListCoveringTuple4_List const* testCases_ = list_37;
    struct BoolBoolFun1 fun_45 = (struct BoolBoolFun1){.fun = fun_25, .env = NULL};
    struct StringTyPatListCoveringTuple4_BoolFun1 fun_46 = (struct StringTyPatListCoveringTuple4_BoolFun1){.fun = fun_26, .env = NULL};
    struct BoolList const* call_145 = listMap_(fun_46, testCases_);
    bool call_146 = listForAll_(fun_45, call_145);
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
