int id_1(int x_);

struct StringList;

struct StringList* go_20(struct StringList* acc_, struct StringList* xs_2);

enum Space_Tag;

struct Space_;

struct IntSpace_Tuple2;

struct Space_List;

struct Space_List* go_23(struct Space_List* acc_, struct Space_List* xs_2);

struct BoolList;

struct BoolList* go_22(struct BoolList* acc_, struct BoolList* xs_2);

struct IntSpace_Tuple2List;

struct IntSpace_Tuple2List* go_21(struct IntSpace_Tuple2List* acc_, struct IntSpace_Tuple2List* xs_2);

struct StringList* listRev_1(struct StringList* xs_1);

struct Space_List* listRev_4(struct Space_List* xs_1);

struct BoolList* listRev_3(struct BoolList* xs_1);

struct IntSpace_Tuple2List* listRev_2(struct IntSpace_Tuple2List* xs_1);

struct IntSpace_Tuple2Space_Fun1;

struct IntSpace_Tuple2Space_Fun1Tuple1;

struct Space_List* go_19(struct IntSpace_Tuple2Space_Fun1Tuple1 arg_21, struct Space_List* acc_1, struct IntSpace_Tuple2List* xs_5);

struct Space_Space_Fun1;

struct Space_Space_Fun1Tuple1;

struct Space_List* go_18(struct Space_Space_Fun1Tuple1 arg_22, struct Space_List* acc_1, struct Space_List* xs_5);

struct Pat_Space_Fun1;

enum Pat_Tag;

struct Pat_;

struct Pat_List;

struct Pat_Pat_Tuple2;

struct Pat_Space_Fun1Tuple1;

struct Space_List* go_17(struct Pat_Space_Fun1Tuple1 arg_23, struct Space_List* acc_1, struct Pat_List* xs_5);

struct StringTy_Pat_ListCovering_Tuple4BoolFun1;

enum Ty_Tag;

struct Ty_;

struct Ty_List;

enum Covering_Tag;

struct Covering_;

struct StringTy_Pat_ListCovering_Tuple4;

struct StringTy_Pat_ListCovering_Tuple4BoolFun1Tuple1;

struct StringTy_Pat_ListCovering_Tuple4List;

struct BoolList* go_16(struct StringTy_Pat_ListCovering_Tuple4BoolFun1Tuple1 arg_24, struct BoolList* acc_1, struct StringTy_Pat_ListCovering_Tuple4List* xs_5);

struct Space_List* listMap_4(struct IntSpace_Tuple2Space_Fun1 f_, struct IntSpace_Tuple2List* xs_4);

struct Space_List* listMap_3(struct Space_Space_Fun1 f_, struct Space_List* xs_4);

struct Space_List* listMap_2(struct Pat_Space_Fun1 f_, struct Pat_List* xs_4);

struct BoolList* listMap_1(struct StringTy_Pat_ListCovering_Tuple4BoolFun1 f_, struct StringTy_Pat_ListCovering_Tuple4List* xs_4);

struct IntTy_IntSpace_Tuple2Fun2;

struct IntTy_IntSpace_Tuple2Fun2Tuple1;

struct IntSpace_Tuple2List* go_15(struct IntTy_IntSpace_Tuple2Fun2Tuple1 arg_25, struct IntSpace_Tuple2List* acc_2, int i_, struct Ty_List* xs_8);

struct IntPat_IntSpace_Tuple2Fun2;

struct IntPat_IntSpace_Tuple2Fun2Tuple1;

struct IntSpace_Tuple2List* go_14(struct IntPat_IntSpace_Tuple2Fun2Tuple1 arg_26, struct IntSpace_Tuple2List* acc_2, int i_, struct Pat_List* xs_8);

struct IntSpace_Tuple2List* listMapWithIndex_2(struct IntTy_IntSpace_Tuple2Fun2 f_1, struct Ty_List* xs_7);

struct IntSpace_Tuple2List* listMapWithIndex_1(struct IntPat_IntSpace_Tuple2Fun2 f_1, struct Pat_List* xs_7);

struct Space_BoolFun1;

struct Space_BoolFun1Tuple1;

int go_13(struct Space_BoolFun1Tuple1 arg_27, struct Space_List* xs_11);

struct BoolBoolFun1;

struct BoolBoolFun1Tuple1;

int go_12(struct BoolBoolFun1Tuple1 arg_28, struct BoolList* xs_11);

int listForAll_2(struct Space_BoolFun1 p_, struct Space_List* xs_10);

int listForAll_1(struct BoolBoolFun1 p_, struct BoolList* xs_10);

struct Space_Space_Space_Fun2;

struct Space_Space_Space_Fun2Tuple1;

struct Space_ go_11(struct Space_Space_Space_Fun2Tuple1 arg_29, struct Space_ state_1, struct Space_List* xs_14);

struct StringListSpace_StringListFun2;

struct StringListSpace_StringListFun2Tuple1;

struct StringList* go_10(struct StringListSpace_StringListFun2Tuple1 arg_30, struct StringList* state_1, struct Space_List* xs_14);

struct Space_ listFold_2(struct Space_Space_Space_Fun2 folder_, struct Space_ state_, struct Space_List* xs_13);

struct StringList* listFold_1(struct StringListSpace_StringListFun2 folder_, struct StringList* state_, struct Space_List* xs_13);

struct String go_5(struct StringList* xs_17);

struct String strConcat_(struct StringList* xs_16);

struct Space_List* failwith_4(struct String msg_);

int failwith_3(struct String msg_);

struct StringList* failwith_2(struct String msg_);

struct Space_ failwith_1(struct String msg_);

struct Space_ spaceVariant_(struct IntSpace_Tuple2 variant_);

struct Space_ fun_5(void* env_, struct IntSpace_Tuple2 arg_);

struct Space_ spaceSum_(struct IntSpace_Tuple2List* variants_);

struct Space_List* go_6(struct Space_List* spaces_1, struct Space_List* acc_3);

struct Space_ spaceUnion_(struct Space_List* spaces_);

int fun_6(void* env_1, struct Space_ arg_1);

int spaceIsEmpty_(struct Space_ space_3);

struct Space_Tuple1;

struct Space_Tuple1Tuple1;

struct Space_ fun_7(void* env_2, struct Space_ arg_2, struct Space_ arg_3);

struct Space_Space_Tuple2;

struct Space_ fun_(struct Space_Space_Tuple2 arg_31, struct Space_ first_1);

struct Space_Space_Tuple2Tuple1;

struct Space_ fun_8(void* env_3, struct Space_ arg_5);

struct Space_ spaceExclude_(struct Space_Tuple1 arg_32, struct Space_ first_, struct Space_ second_);

int spaceCovers_(struct Space_Tuple1 arg_33, struct Space_ other_, struct Space_ cover_);

struct StringList* cons_1(struct String head_, struct StringList* tail_);

struct StringList* fun_1(struct StringList* acc_6, struct Space_ space_6);

struct StringList* fun_9(void* env_4, struct StringList* arg_7, struct Space_ arg_8);

struct StringList* go_7(struct Space_ space_5, struct StringList* acc_4);

struct String spaceToString_(struct Space_ space_4);

struct IntSpace_Tuple2 fun_16(struct Space_Space_Tuple2 arg_34, int i_1, struct Ty_ itemTy_);

struct IntSpace_Tuple2 fun_10(void* env_5, int arg_9, struct Ty_ arg_10);

struct Space_ go_8(struct Space_Space_Tuple2 arg_35, struct Ty_ ty_1);

struct Space_ tyToSpace_1(struct Space_Space_Tuple2 arg_36, int _ctx_, struct Ty_ ty_);

struct Space_Space_Space_Tuple3;

struct IntSpace_Tuple2 fun_15(struct Space_Space_Space_Tuple3 arg_37, int i_2, struct Pat_ itemPat_);

struct Space_Space_Space_Tuple3Tuple1;

struct IntSpace_Tuple2 fun_11(void* env_6, int arg_12, struct Pat_ arg_13);

struct Space_ go_9(struct Space_Space_Space_Tuple3 arg_38, struct Pat_ pat_1);

struct Space_ patToSpace_(struct Space_Space_Space_Tuple3 arg_39, int _ctx_1, struct Pat_ pat_);

struct Space_Space_Space_Tuple3UnitTuple2;

struct Space_ fun_12(void* env_7, struct Pat_ arg_15);

struct Space_ patsToSpace_(struct Space_Space_Space_Tuple3 arg_40, int ctx_, struct Pat_List* pats_);

struct String coveringToString_(struct Covering_ covering_);

int fun_13(void* env_8, int arg_18);

struct BoolStringTuple2;

struct Covering_Covering_Tuple2;

int fun_4(struct Space_Space_Space_Tuple3 arg_41, struct StringTy_Pat_ListCovering_Tuple4 arg_42);

int fun_14(void* env_9, struct StringTy_Pat_ListCovering_Tuple4 arg_19);

int main();

int id_1(int x_) {
    return x_;
}

struct StringList {
    struct String head;
    struct StringList* tail;
};

struct StringList* go_20(struct StringList* acc_, struct StringList* xs_2) {
    struct StringList* match_;
    if (!((!(xs_2)))) goto next_2;
    match_ = acc_;
    goto end_match_1;
next_2:;
    if (!((!((!(xs_2)))))) goto next_3;
    struct String x_2 = xs_2->head;
    struct StringList* xs_3 = xs_2->tail;
    struct StringList* list_ = (struct StringList*)malloc(sizeof(struct StringList));
    list_->head = x_2;
    list_->tail = acc_;
    struct StringList* call_ = go_20(list_, xs_3);
    match_ = call_;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return match_;
}

enum Space_Tag {
    Full_,
    Variant_,
    Union_,
};

struct Space_ {
    enum Space_Tag tag;
    union {
        struct IntSpace_Tuple2* Variant_;
        struct Space_List** Union_;
    };
};

struct IntSpace_Tuple2 {
    int t0;
    struct Space_ t1;
};

struct Space_List {
    struct Space_ head;
    struct Space_List* tail;
};

struct Space_List* go_23(struct Space_List* acc_, struct Space_List* xs_2) {
    struct Space_List* match_1;
    if (!((!(xs_2)))) goto next_5;
    match_1 = acc_;
    goto end_match_4;
next_5:;
    if (!((!((!(xs_2)))))) goto next_6;
    struct Space_ x_2 = xs_2->head;
    struct Space_List* xs_3 = xs_2->tail;
    struct Space_List* list_1 = (struct Space_List*)malloc(sizeof(struct Space_List));
    list_1->head = x_2;
    list_1->tail = acc_;
    struct Space_List* call_1 = go_23(list_1, xs_3);
    match_1 = call_1;
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

struct BoolList* go_22(struct BoolList* acc_, struct BoolList* xs_2) {
    struct BoolList* match_2;
    if (!((!(xs_2)))) goto next_8;
    match_2 = acc_;
    goto end_match_7;
next_8:;
    if (!((!((!(xs_2)))))) goto next_9;
    int x_2 = xs_2->head;
    struct BoolList* xs_3 = xs_2->tail;
    struct BoolList* list_2 = (struct BoolList*)malloc(sizeof(struct BoolList));
    list_2->head = x_2;
    list_2->tail = acc_;
    struct BoolList* call_2 = go_22(list_2, xs_3);
    match_2 = call_2;
    goto end_match_7;
next_9:;
    exit(1);
end_match_7:;
    return match_2;
}

struct IntSpace_Tuple2List {
    struct IntSpace_Tuple2 head;
    struct IntSpace_Tuple2List* tail;
};

struct IntSpace_Tuple2List* go_21(struct IntSpace_Tuple2List* acc_, struct IntSpace_Tuple2List* xs_2) {
    struct IntSpace_Tuple2List* match_3;
    if (!((!(xs_2)))) goto next_11;
    match_3 = acc_;
    goto end_match_10;
next_11:;
    if (!((!((!(xs_2)))))) goto next_12;
    struct IntSpace_Tuple2 x_2 = xs_2->head;
    struct IntSpace_Tuple2List* xs_3 = xs_2->tail;
    struct IntSpace_Tuple2List* list_3 = (struct IntSpace_Tuple2List*)malloc(sizeof(struct IntSpace_Tuple2List));
    list_3->head = x_2;
    list_3->tail = acc_;
    struct IntSpace_Tuple2List* call_3 = go_21(list_3, xs_3);
    match_3 = call_3;
    goto end_match_10;
next_12:;
    exit(1);
end_match_10:;
    return match_3;
}

struct StringList* listRev_1(struct StringList* xs_1) {
    struct StringList* call_4 = go_20(NULL, xs_1);
    return call_4;
}

struct Space_List* listRev_4(struct Space_List* xs_1) {
    struct Space_List* call_5 = go_23(NULL, xs_1);
    return call_5;
}

struct BoolList* listRev_3(struct BoolList* xs_1) {
    struct BoolList* call_6 = go_22(NULL, xs_1);
    return call_6;
}

struct IntSpace_Tuple2List* listRev_2(struct IntSpace_Tuple2List* xs_1) {
    struct IntSpace_Tuple2List* call_7 = go_21(NULL, xs_1);
    return call_7;
}

struct IntSpace_Tuple2Space_Fun1 {
    struct Space_(*fun)(void*, struct IntSpace_Tuple2);
    void* env;
};

struct IntSpace_Tuple2Space_Fun1Tuple1 {
    struct IntSpace_Tuple2Space_Fun1 t0;
};

struct Space_List* go_19(struct IntSpace_Tuple2Space_Fun1Tuple1 arg_21, struct Space_List* acc_1, struct IntSpace_Tuple2List* xs_5) {
    struct IntSpace_Tuple2Space_Fun1 f_ = arg_21.t0;
    struct Space_List* match_4;
    if (!((!(xs_5)))) goto next_14;
    struct Space_List* call_8 = listRev_4(acc_1);
    match_4 = call_8;
    goto end_match_13;
next_14:;
    if (!((!((!(xs_5)))))) goto next_15;
    struct IntSpace_Tuple2 x_3 = xs_5->head;
    struct IntSpace_Tuple2List* xs_6 = xs_5->tail;
    struct IntSpace_Tuple2Space_Fun1Tuple1 tuple_;
    tuple_.t0 = f_;
    struct Space_ app_ = f_.fun(f_.env, x_3);
    struct Space_List* list_4 = (struct Space_List*)malloc(sizeof(struct Space_List));
    list_4->head = app_;
    list_4->tail = acc_1;
    struct Space_List* call_9 = go_19(tuple_, list_4, xs_6);
    match_4 = call_9;
    goto end_match_13;
next_15:;
    exit(1);
end_match_13:;
    return match_4;
}

struct Space_Space_Fun1 {
    struct Space_(*fun)(void*, struct Space_);
    void* env;
};

struct Space_Space_Fun1Tuple1 {
    struct Space_Space_Fun1 t0;
};

struct Space_List* go_18(struct Space_Space_Fun1Tuple1 arg_22, struct Space_List* acc_1, struct Space_List* xs_5) {
    struct Space_Space_Fun1 f_ = arg_22.t0;
    struct Space_List* match_5;
    if (!((!(xs_5)))) goto next_17;
    struct Space_List* call_10 = listRev_4(acc_1);
    match_5 = call_10;
    goto end_match_16;
next_17:;
    if (!((!((!(xs_5)))))) goto next_18;
    struct Space_ x_3 = xs_5->head;
    struct Space_List* xs_6 = xs_5->tail;
    struct Space_Space_Fun1Tuple1 tuple_1;
    tuple_1.t0 = f_;
    struct Space_ app_1 = f_.fun(f_.env, x_3);
    struct Space_List* list_5 = (struct Space_List*)malloc(sizeof(struct Space_List));
    list_5->head = app_1;
    list_5->tail = acc_1;
    struct Space_List* call_11 = go_18(tuple_1, list_5, xs_6);
    match_5 = call_11;
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

struct Space_List* go_17(struct Pat_Space_Fun1Tuple1 arg_23, struct Space_List* acc_1, struct Pat_List* xs_5) {
    struct Pat_Space_Fun1 f_ = arg_23.t0;
    struct Space_List* match_6;
    if (!((!(xs_5)))) goto next_20;
    struct Space_List* call_12 = listRev_4(acc_1);
    match_6 = call_12;
    goto end_match_19;
next_20:;
    if (!((!((!(xs_5)))))) goto next_21;
    struct Pat_ x_3 = xs_5->head;
    struct Pat_List* xs_6 = xs_5->tail;
    struct Pat_Space_Fun1Tuple1 tuple_2;
    tuple_2.t0 = f_;
    struct Space_ app_2 = f_.fun(f_.env, x_3);
    struct Space_List* list_6 = (struct Space_List*)malloc(sizeof(struct Space_List));
    list_6->head = app_2;
    list_6->tail = acc_1;
    struct Space_List* call_13 = go_17(tuple_2, list_6, xs_6);
    match_6 = call_13;
    goto end_match_19;
next_21:;
    exit(1);
end_match_19:;
    return match_6;
}

struct StringTy_Pat_ListCovering_Tuple4BoolFun1 {
    int(*fun)(void*, struct StringTy_Pat_ListCovering_Tuple4);
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

struct BoolList* go_16(struct StringTy_Pat_ListCovering_Tuple4BoolFun1Tuple1 arg_24, struct BoolList* acc_1, struct StringTy_Pat_ListCovering_Tuple4List* xs_5) {
    struct StringTy_Pat_ListCovering_Tuple4BoolFun1 f_ = arg_24.t0;
    struct BoolList* match_7;
    if (!((!(xs_5)))) goto next_23;
    struct BoolList* call_14 = listRev_3(acc_1);
    match_7 = call_14;
    goto end_match_22;
next_23:;
    if (!((!((!(xs_5)))))) goto next_24;
    struct StringTy_Pat_ListCovering_Tuple4 x_3 = xs_5->head;
    struct StringTy_Pat_ListCovering_Tuple4List* xs_6 = xs_5->tail;
    struct StringTy_Pat_ListCovering_Tuple4BoolFun1Tuple1 tuple_3;
    tuple_3.t0 = f_;
    int app_3 = f_.fun(f_.env, x_3);
    struct BoolList* list_7 = (struct BoolList*)malloc(sizeof(struct BoolList));
    list_7->head = app_3;
    list_7->tail = acc_1;
    struct BoolList* call_15 = go_16(tuple_3, list_7, xs_6);
    match_7 = call_15;
    goto end_match_22;
next_24:;
    exit(1);
end_match_22:;
    return match_7;
}

struct Space_List* listMap_4(struct IntSpace_Tuple2Space_Fun1 f_, struct IntSpace_Tuple2List* xs_4) {
    struct IntSpace_Tuple2Space_Fun1Tuple1 tuple_4;
    tuple_4.t0 = f_;
    struct Space_List* call_16 = go_19(tuple_4, NULL, xs_4);
    return call_16;
}

struct Space_List* listMap_3(struct Space_Space_Fun1 f_, struct Space_List* xs_4) {
    struct Space_Space_Fun1Tuple1 tuple_5;
    tuple_5.t0 = f_;
    struct Space_List* call_17 = go_18(tuple_5, NULL, xs_4);
    return call_17;
}

struct Space_List* listMap_2(struct Pat_Space_Fun1 f_, struct Pat_List* xs_4) {
    struct Pat_Space_Fun1Tuple1 tuple_6;
    tuple_6.t0 = f_;
    struct Space_List* call_18 = go_17(tuple_6, NULL, xs_4);
    return call_18;
}

struct BoolList* listMap_1(struct StringTy_Pat_ListCovering_Tuple4BoolFun1 f_, struct StringTy_Pat_ListCovering_Tuple4List* xs_4) {
    struct StringTy_Pat_ListCovering_Tuple4BoolFun1Tuple1 tuple_7;
    tuple_7.t0 = f_;
    struct BoolList* call_19 = go_16(tuple_7, NULL, xs_4);
    return call_19;
}

struct IntTy_IntSpace_Tuple2Fun2 {
    struct IntSpace_Tuple2(*fun)(void*, int, struct Ty_);
    void* env;
};

struct IntTy_IntSpace_Tuple2Fun2Tuple1 {
    struct IntTy_IntSpace_Tuple2Fun2 t0;
};

struct IntSpace_Tuple2List* go_15(struct IntTy_IntSpace_Tuple2Fun2Tuple1 arg_25, struct IntSpace_Tuple2List* acc_2, int i_, struct Ty_List* xs_8) {
    struct IntTy_IntSpace_Tuple2Fun2 f_1 = arg_25.t0;
    struct IntSpace_Tuple2List* match_8;
    if (!((!(xs_8)))) goto next_26;
    struct IntSpace_Tuple2List* call_20 = listRev_2(acc_2);
    match_8 = call_20;
    goto end_match_25;
next_26:;
    if (!((!((!(xs_8)))))) goto next_27;
    struct Ty_ x_4 = xs_8->head;
    struct Ty_List* xs_9 = xs_8->tail;
    struct IntTy_IntSpace_Tuple2Fun2Tuple1 tuple_8;
    tuple_8.t0 = f_1;
    struct IntSpace_Tuple2 app_4 = f_1.fun(f_1.env, i_, x_4);
    struct IntSpace_Tuple2List* list_8 = (struct IntSpace_Tuple2List*)malloc(sizeof(struct IntSpace_Tuple2List));
    list_8->head = app_4;
    list_8->tail = acc_2;
    struct IntSpace_Tuple2List* call_21 = go_15(tuple_8, list_8, (i_ + 1), xs_9);
    match_8 = call_21;
    goto end_match_25;
next_27:;
    exit(1);
end_match_25:;
    return match_8;
}

struct IntPat_IntSpace_Tuple2Fun2 {
    struct IntSpace_Tuple2(*fun)(void*, int, struct Pat_);
    void* env;
};

struct IntPat_IntSpace_Tuple2Fun2Tuple1 {
    struct IntPat_IntSpace_Tuple2Fun2 t0;
};

struct IntSpace_Tuple2List* go_14(struct IntPat_IntSpace_Tuple2Fun2Tuple1 arg_26, struct IntSpace_Tuple2List* acc_2, int i_, struct Pat_List* xs_8) {
    struct IntPat_IntSpace_Tuple2Fun2 f_1 = arg_26.t0;
    struct IntSpace_Tuple2List* match_9;
    if (!((!(xs_8)))) goto next_29;
    struct IntSpace_Tuple2List* call_22 = listRev_2(acc_2);
    match_9 = call_22;
    goto end_match_28;
next_29:;
    if (!((!((!(xs_8)))))) goto next_30;
    struct Pat_ x_4 = xs_8->head;
    struct Pat_List* xs_9 = xs_8->tail;
    struct IntPat_IntSpace_Tuple2Fun2Tuple1 tuple_9;
    tuple_9.t0 = f_1;
    struct IntSpace_Tuple2 app_5 = f_1.fun(f_1.env, i_, x_4);
    struct IntSpace_Tuple2List* list_9 = (struct IntSpace_Tuple2List*)malloc(sizeof(struct IntSpace_Tuple2List));
    list_9->head = app_5;
    list_9->tail = acc_2;
    struct IntSpace_Tuple2List* call_23 = go_14(tuple_9, list_9, (i_ + 1), xs_9);
    match_9 = call_23;
    goto end_match_28;
next_30:;
    exit(1);
end_match_28:;
    return match_9;
}

struct IntSpace_Tuple2List* listMapWithIndex_2(struct IntTy_IntSpace_Tuple2Fun2 f_1, struct Ty_List* xs_7) {
    struct IntTy_IntSpace_Tuple2Fun2Tuple1 tuple_10;
    tuple_10.t0 = f_1;
    struct IntSpace_Tuple2List* call_24 = go_15(tuple_10, NULL, 0, xs_7);
    return call_24;
}

struct IntSpace_Tuple2List* listMapWithIndex_1(struct IntPat_IntSpace_Tuple2Fun2 f_1, struct Pat_List* xs_7) {
    struct IntPat_IntSpace_Tuple2Fun2Tuple1 tuple_11;
    tuple_11.t0 = f_1;
    struct IntSpace_Tuple2List* call_25 = go_14(tuple_11, NULL, 0, xs_7);
    return call_25;
}

struct Space_BoolFun1 {
    int(*fun)(void*, struct Space_);
    void* env;
};

struct Space_BoolFun1Tuple1 {
    struct Space_BoolFun1 t0;
};

int go_13(struct Space_BoolFun1Tuple1 arg_27, struct Space_List* xs_11) {
    struct Space_BoolFun1 p_ = arg_27.t0;
    int match_10;
    if (!((!(xs_11)))) goto next_32;
    match_10 = 1;
    goto end_match_31;
next_32:;
    if (!((!((!(xs_11)))))) goto next_33;
    struct Space_ x_5 = xs_11->head;
    struct Space_List* xs_12 = xs_11->tail;
    int match_11;
    int app_6 = p_.fun(p_.env, x_5);
    if (!((app_6 == 1))) goto next_35;
    struct Space_BoolFun1Tuple1 tuple_12;
    tuple_12.t0 = p_;
    int call_26 = go_13(tuple_12, xs_12);
    match_11 = call_26;
    goto end_match_34;
next_35:;
    if (!((app_6 == 0))) goto next_36;
    match_11 = 0;
    goto end_match_34;
next_36:;
    exit(1);
end_match_34:;
    match_10 = match_11;
    goto end_match_31;
next_33:;
    exit(1);
end_match_31:;
    return match_10;
}

struct BoolBoolFun1 {
    int(*fun)(void*, int);
    void* env;
};

struct BoolBoolFun1Tuple1 {
    struct BoolBoolFun1 t0;
};

int go_12(struct BoolBoolFun1Tuple1 arg_28, struct BoolList* xs_11) {
    struct BoolBoolFun1 p_ = arg_28.t0;
    int match_12;
    if (!((!(xs_11)))) goto next_38;
    match_12 = 1;
    goto end_match_37;
next_38:;
    if (!((!((!(xs_11)))))) goto next_39;
    int x_5 = xs_11->head;
    struct BoolList* xs_12 = xs_11->tail;
    int match_13;
    int app_7 = p_.fun(p_.env, x_5);
    if (!((app_7 == 1))) goto next_41;
    struct BoolBoolFun1Tuple1 tuple_13;
    tuple_13.t0 = p_;
    int call_27 = go_12(tuple_13, xs_12);
    match_13 = call_27;
    goto end_match_40;
next_41:;
    if (!((app_7 == 0))) goto next_42;
    match_13 = 0;
    goto end_match_40;
next_42:;
    exit(1);
end_match_40:;
    match_12 = match_13;
    goto end_match_37;
next_39:;
    exit(1);
end_match_37:;
    return match_12;
}

int listForAll_2(struct Space_BoolFun1 p_, struct Space_List* xs_10) {
    struct Space_BoolFun1Tuple1 tuple_14;
    tuple_14.t0 = p_;
    int call_28 = go_13(tuple_14, xs_10);
    return call_28;
}

int listForAll_1(struct BoolBoolFun1 p_, struct BoolList* xs_10) {
    struct BoolBoolFun1Tuple1 tuple_15;
    tuple_15.t0 = p_;
    int call_29 = go_12(tuple_15, xs_10);
    return call_29;
}

struct Space_Space_Space_Fun2 {
    struct Space_(*fun)(void*, struct Space_, struct Space_);
    void* env;
};

struct Space_Space_Space_Fun2Tuple1 {
    struct Space_Space_Space_Fun2 t0;
};

struct Space_ go_11(struct Space_Space_Space_Fun2Tuple1 arg_29, struct Space_ state_1, struct Space_List* xs_14) {
    struct Space_Space_Space_Fun2 folder_ = arg_29.t0;
    struct Space_ match_14;
    if (!((!(xs_14)))) goto next_44;
    match_14 = state_1;
    goto end_match_43;
next_44:;
    if (!((!((!(xs_14)))))) goto next_45;
    struct Space_ x_6 = xs_14->head;
    struct Space_List* xs_15 = xs_14->tail;
    struct Space_Space_Space_Fun2Tuple1 tuple_16;
    tuple_16.t0 = folder_;
    struct Space_ app_8 = folder_.fun(folder_.env, state_1, x_6);
    struct Space_ call_30 = go_11(tuple_16, app_8, xs_15);
    match_14 = call_30;
    goto end_match_43;
next_45:;
    exit(1);
end_match_43:;
    return match_14;
}

struct StringListSpace_StringListFun2 {
    struct StringList*(*fun)(void*, struct StringList*, struct Space_);
    void* env;
};

struct StringListSpace_StringListFun2Tuple1 {
    struct StringListSpace_StringListFun2 t0;
};

struct StringList* go_10(struct StringListSpace_StringListFun2Tuple1 arg_30, struct StringList* state_1, struct Space_List* xs_14) {
    struct StringListSpace_StringListFun2 folder_ = arg_30.t0;
    struct StringList* match_15;
    if (!((!(xs_14)))) goto next_47;
    match_15 = state_1;
    goto end_match_46;
next_47:;
    if (!((!((!(xs_14)))))) goto next_48;
    struct Space_ x_6 = xs_14->head;
    struct Space_List* xs_15 = xs_14->tail;
    struct StringListSpace_StringListFun2Tuple1 tuple_17;
    tuple_17.t0 = folder_;
    struct StringList* app_9 = folder_.fun(folder_.env, state_1, x_6);
    struct StringList* call_31 = go_10(tuple_17, app_9, xs_15);
    match_15 = call_31;
    goto end_match_46;
next_48:;
    exit(1);
end_match_46:;
    return match_15;
}

struct Space_ listFold_2(struct Space_Space_Space_Fun2 folder_, struct Space_ state_, struct Space_List* xs_13) {
    struct Space_Space_Space_Fun2Tuple1 tuple_18;
    tuple_18.t0 = folder_;
    struct Space_ call_32 = go_11(tuple_18, state_, xs_13);
    return call_32;
}

struct StringList* listFold_1(struct StringListSpace_StringListFun2 folder_, struct StringList* state_, struct Space_List* xs_13) {
    struct StringListSpace_StringListFun2Tuple1 tuple_19;
    tuple_19.t0 = folder_;
    struct StringList* call_33 = go_10(tuple_19, state_, xs_13);
    return call_33;
}

struct String go_5(struct StringList* xs_17) {
    struct String match_16;
    if (!((!(xs_17)))) goto next_50;
    match_16 = (struct String){.str = "", .len = 0};
    goto end_match_49;
next_50:;
    if (!((!((!(xs_17)))))) goto next_51;
    struct String x_7 = xs_17->head;
    struct StringList* xs_18 = xs_17->tail;
    struct String call_34 = go_5(xs_18);
    match_16 = str_add(x_7, call_34);
    goto end_match_49;
next_51:;
    exit(1);
end_match_49:;
    return match_16;
}

struct String strConcat_(struct StringList* xs_16) {
    struct String call_35 = go_5(xs_16);
    return call_35;
}

struct Space_List* failwith_4(struct String msg_) {
    printf("ERROR %s\n", msg_.str);
    int call_36 = 0;
    exit(1);
    return NULL;
}

int failwith_3(struct String msg_) {
    printf("ERROR %s\n", msg_.str);
    int call_37 = 0;
    exit(1);
    return 0;
}

struct StringList* failwith_2(struct String msg_) {
    printf("ERROR %s\n", msg_.str);
    int call_38 = 0;
    exit(1);
    return NULL;
}

struct Space_ failwith_1(struct String msg_) {
    printf("ERROR %s\n", msg_.str);
    int call_39 = 0;
    exit(1);
    return ((struct Space_){});
}

struct Space_ spaceVariant_(struct IntSpace_Tuple2 variant_) {
    struct IntSpace_Tuple2* payload_ = (struct IntSpace_Tuple2*)malloc(sizeof(struct IntSpace_Tuple2));
    (*(((struct IntSpace_Tuple2*)payload_))) = variant_;
    struct Space_ variant_1 = (struct Space_){.tag = Variant_, .Variant_ = payload_};
    return variant_1;
}

struct Space_ fun_5(void* env_, struct IntSpace_Tuple2 arg_) {
    struct Space_ call_40 = spaceVariant_(arg_);
    return call_40;
}

struct Space_ spaceSum_(struct IntSpace_Tuple2List* variants_) {
    void* box_ = (void*)malloc(sizeof(int));
    (*(((int*)box_))) = 0;
    void* env_10 = box_;
    struct IntSpace_Tuple2Space_Fun1 fun_17 = (struct IntSpace_Tuple2Space_Fun1){.fun = fun_5, .env = env_10};
    struct Space_List* call_41 = listMap_4(fun_17, variants_);
    struct Space_ call_42 = spaceUnion_(call_41);
    return call_42;
}

struct Space_List* go_6(struct Space_List* spaces_1, struct Space_List* acc_3) {
    struct Space_List* match_17;
    if (!(0)) goto next_53;
    struct Space_List* call_43 = failwith_4((struct String){.str = "NEVER: suppress warning", .len = 23});
    match_17 = call_43;
    goto end_match_52;
next_53:;
    if (!((!(spaces_1)))) goto next_54;
    match_17 = acc_3;
    goto end_match_52;
next_54:;
    if (!((!((!(spaces_1)))))) goto next_55;
    if (!((spaces_1->head.tag == Union_))) goto next_55;
    struct Space_List* subspaces_ = (*(spaces_1->head.Union_));
    struct Space_List* spaces_2 = spaces_1->tail;
    struct Space_List* call_44 = go_6(subspaces_, acc_3);
    struct Space_List* call_45 = go_6(spaces_2, call_44);
    match_17 = call_45;
    goto end_match_52;
next_55:;
    if (!((!((!(spaces_1)))))) goto next_56;
    struct Space_ space_ = spaces_1->head;
    struct Space_List* spaces_3 = spaces_1->tail;
    int call_46 = spaceIsEmpty_(space_);
    if (!(call_46)) goto next_56;
    struct Space_List* call_47 = go_6(spaces_3, acc_3);
    match_17 = call_47;
    goto end_match_52;
next_56:;
    if (!((!((!(spaces_1)))))) goto next_57;
    struct Space_ space_1 = spaces_1->head;
    struct Space_List* spaces_4 = spaces_1->tail;
    struct Space_List* list_10 = (struct Space_List*)malloc(sizeof(struct Space_List));
    list_10->head = space_1;
    list_10->tail = acc_3;
    struct Space_List* call_48 = go_6(spaces_4, list_10);
    match_17 = call_48;
    goto end_match_52;
next_57:;
    exit(1);
end_match_52:;
    return match_17;
}

struct Space_ spaceUnion_(struct Space_List* spaces_) {
    struct Space_ match_18;
    struct Space_List* call_49 = go_6(spaces_, NULL);
    if (!((!((!(call_49)))))) goto next_59;
    struct Space_ space_2 = call_49->head;
    if (!((!(call_49->tail)))) goto next_59;
    match_18 = space_2;
    goto end_match_58;
next_59:;
    struct Space_List* spaces_5 = call_49;
    struct Space_List** payload_1 = (struct Space_List**)malloc(sizeof(struct Space_List*));
    (*(((struct Space_List**)payload_1))) = spaces_5;
    struct Space_ variant_2 = (struct Space_){.tag = Union_, .Union_ = payload_1};
    match_18 = variant_2;
    goto end_match_58;
next_60:;
end_match_58:;
    return match_18;
}

int fun_6(void* env_1, struct Space_ arg_1) {
    int call_50 = spaceIsEmpty_(arg_1);
    return call_50;
}

int spaceIsEmpty_(struct Space_ space_3) {
    int match_19;
    if (!((space_3.tag == Full_))) goto next_62;
    match_19 = 0;
    goto end_match_61;
next_62:;
    if (!((space_3.tag == Variant_))) goto next_63;
    struct Space_ subspace_ = (*(space_3.Variant_)).t1;
    int call_51 = spaceIsEmpty_(subspace_);
    match_19 = call_51;
    goto end_match_61;
next_63:;
    if (!((space_3.tag == Union_))) goto next_64;
    struct Space_List* spaces_6 = (*(space_3.Union_));
    void* box_1 = (void*)malloc(sizeof(int));
    (*(((int*)box_1))) = 0;
    void* env_11 = box_1;
    struct Space_BoolFun1 fun_18 = (struct Space_BoolFun1){.fun = fun_6, .env = env_11};
    int call_52 = listForAll_2(fun_18, spaces_6);
    match_19 = call_52;
    goto end_match_61;
next_64:;
    int call_53 = failwith_3((struct String){.str = "NEVER: suppress warning", .len = 23});
    match_19 = call_53;
    goto end_match_61;
next_65:;
end_match_61:;
    int result_ = match_19;
    return result_;
}

struct Space_Tuple1 {
    struct Space_ t0;
};

struct Space_Tuple1Tuple1 {
    struct Space_Tuple1 t0;
};

struct Space_ fun_7(void* env_2, struct Space_ arg_2, struct Space_ arg_3) {
    struct Space_Tuple1 arg_4 = (*(((struct Space_Tuple1Tuple1*)env_2))).t0;
    struct Space_ call_54 = spaceExclude_(arg_4, arg_2, arg_3);
    return call_54;
}

struct Space_Space_Tuple2 {
    struct Space_ t0;
    struct Space_ t1;
};

struct Space_ fun_(struct Space_Space_Tuple2 arg_31, struct Space_ first_1) {
    struct Space_ spaceEmpty_ = arg_31.t0;
    struct Space_ second_ = arg_31.t1;
    struct Space_Tuple1 tuple_20;
    tuple_20.t0 = spaceEmpty_;
    struct Space_ call_55 = spaceExclude_(tuple_20, first_1, second_);
    return call_55;
}

struct Space_Space_Tuple2Tuple1 {
    struct Space_Space_Tuple2 t0;
};

struct Space_ fun_8(void* env_3, struct Space_ arg_5) {
    struct Space_Space_Tuple2 arg_6 = (*(((struct Space_Space_Tuple2Tuple1*)env_3))).t0;
    struct Space_ call_56 = fun_(arg_6, arg_5);
    return call_56;
}

struct Space_ spaceExclude_(struct Space_Tuple1 arg_32, struct Space_ first_, struct Space_ second_) {
    struct Space_ spaceEmpty_ = arg_32.t0;
    struct Space_ match_20;
    struct Space_Space_Tuple2 tuple_21;
    tuple_21.t0 = first_;
    tuple_21.t1 = second_;
    if (!((tuple_21.t1.tag == Full_))) goto next_68;
    goto match_body_67;
next_68:;
    if (!((tuple_21.t0.tag == Union_))) goto next_69;
    if (!((!((*(tuple_21.t0.Union_)))))) goto next_69;
    goto match_body_67;
match_body_67:;
    match_20 = spaceEmpty_;
    goto end_match_66;
next_69:;
    if (!((tuple_21.t1.tag == Union_))) goto next_70;
    if (!((!((*(tuple_21.t1.Union_)))))) goto next_70;
    match_20 = first_;
    goto end_match_66;
next_70:;
    if (!((tuple_21.t0.tag == Variant_))) goto next_71;
    int tag_ = (*(tuple_21.t0.Variant_)).t0;
    struct Space_ firstSpace_ = (*(tuple_21.t0.Variant_)).t1;
    if (!((tuple_21.t1.tag == Variant_))) goto next_71;
    int secondTag_ = (*(tuple_21.t1.Variant_)).t0;
    struct Space_ secondSpace_ = (*(tuple_21.t1.Variant_)).t1;
    if (!((tag_ == secondTag_))) goto next_71;
    struct Space_Tuple1 tuple_22;
    tuple_22.t0 = spaceEmpty_;
    struct Space_ call_57 = spaceExclude_(tuple_22, firstSpace_, secondSpace_);
    struct Space_ subspace_1 = call_57;
    struct IntSpace_Tuple2 tuple_23;
    tuple_23.t0 = tag_;
    tuple_23.t1 = subspace_1;
    struct Space_ call_58 = spaceVariant_(tuple_23);
    match_20 = call_58;
    goto end_match_66;
next_71:;
    if (!((tuple_21.t0.tag == Variant_))) goto next_72;
    if (!((tuple_21.t1.tag == Variant_))) goto next_72;
    match_20 = first_;
    goto end_match_66;
next_72:;
    if (!((tuple_21.t1.tag == Union_))) goto next_73;
    struct Space_List* seconds_ = (*(tuple_21.t1.Union_));
    struct Space_Tuple1 tuple_25;
    tuple_25.t0 = spaceEmpty_;
    struct Space_Tuple1Tuple1 tuple_24;
    tuple_24.t0 = tuple_25;
    void* box_2 = (void*)malloc(sizeof(struct Space_Tuple1Tuple1));
    (*(((struct Space_Tuple1Tuple1*)box_2))) = tuple_24;
    void* env_12 = box_2;
    struct Space_Space_Space_Fun2 fun_19 = (struct Space_Space_Space_Fun2){.fun = fun_7, .env = env_12};
    struct Space_ call_59 = listFold_2(fun_19, first_, seconds_);
    match_20 = call_59;
    goto end_match_66;
next_73:;
    if (!((tuple_21.t0.tag == Union_))) goto next_74;
    struct Space_List* firsts_ = (*(tuple_21.t0.Union_));
    struct Space_Space_Tuple2 tuple_27;
    tuple_27.t0 = spaceEmpty_;
    tuple_27.t1 = second_;
    struct Space_Space_Tuple2Tuple1 tuple_26;
    tuple_26.t0 = tuple_27;
    void* box_3 = (void*)malloc(sizeof(struct Space_Space_Tuple2Tuple1));
    (*(((struct Space_Space_Tuple2Tuple1*)box_3))) = tuple_26;
    void* env_13 = box_3;
    struct Space_Space_Fun1 fun_20 = (struct Space_Space_Fun1){.fun = fun_8, .env = env_13};
    struct Space_List* call_60 = listMap_3(fun_20, firsts_);
    struct Space_ call_61 = spaceUnion_(call_60);
    match_20 = call_61;
    goto end_match_66;
next_74:;
end_match_66:;
    return match_20;
}

int spaceCovers_(struct Space_Tuple1 arg_33, struct Space_ other_, struct Space_ cover_) {
    struct Space_ spaceEmpty_ = arg_33.t0;
    struct Space_Tuple1 tuple_28;
    tuple_28.t0 = spaceEmpty_;
    struct Space_ call_62 = spaceExclude_(tuple_28, other_, cover_);
    struct Space_ excluded_ = call_62;
    int call_63 = spaceIsEmpty_(excluded_);
    return call_63;
}

struct StringList* cons_1(struct String head_, struct StringList* tail_) {
    struct StringList* list_11 = (struct StringList*)malloc(sizeof(struct StringList));
    list_11->head = head_;
    list_11->tail = tail_;
    return list_11;
}

struct StringList* fun_1(struct StringList* acc_6, struct Space_ space_6) {
    struct StringList* call_64 = cons_1((struct String){.str = ", ", .len = 2}, acc_6);
    struct StringList* call_65 = go_7(space_6, call_64);
    return call_65;
}

struct StringList* fun_9(void* env_4, struct StringList* arg_7, struct Space_ arg_8) {
    struct StringList* call_66 = fun_1(arg_7, arg_8);
    return call_66;
}

struct StringList* go_7(struct Space_ space_5, struct StringList* acc_4) {
    struct StringList* match_21;
    if (!((space_5.tag == Full_))) goto next_76;
    struct StringList* call_67 = cons_1((struct String){.str = "full", .len = 4}, acc_4);
    match_21 = call_67;
    goto end_match_75;
next_76:;
    if (!((space_5.tag == Variant_))) goto next_77;
    int variantId_ = (*(space_5.Variant_)).t0;
    struct Space_ subspace_2 = (*(space_5.Variant_)).t1;
    struct String call_68 = str_of_int(variantId_);
    struct StringList* call_69 = cons_1((struct String){.str = "var#", .len = 4}, acc_4);
    struct StringList* call_70 = cons_1(call_68, call_69);
    struct StringList* call_71 = cons_1((struct String){.str = " (", .len = 2}, call_70);
    struct StringList* call_72 = go_7(subspace_2, call_71);
    struct StringList* call_73 = cons_1((struct String){.str = ")", .len = 1}, call_72);
    match_21 = call_73;
    goto end_match_75;
next_77:;
    if (!((space_5.tag == Union_))) goto next_78;
    if (!((!((*(space_5.Union_)))))) goto next_78;
    struct StringList* call_74 = cons_1((struct String){.str = "empty", .len = 5}, acc_4);
    match_21 = call_74;
    goto end_match_75;
next_78:;
    if (!((space_5.tag == Union_))) goto next_79;
    if (!((!((!((*(space_5.Union_)))))))) goto next_79;
    struct Space_ subspace_3 = (*(space_5.Union_))->head;
    struct Space_List* subspaces_1 = (*(space_5.Union_))->tail;
    struct StringList* call_75 = cons_1((struct String){.str = "+(", .len = 2}, acc_4);
    struct StringList* call_76 = go_7(subspace_3, call_75);
    struct StringList* acc_5 = call_76;
    void* box_4 = (void*)malloc(sizeof(int));
    (*(((int*)box_4))) = 0;
    void* env_14 = box_4;
    struct StringListSpace_StringListFun2 fun_21 = (struct StringListSpace_StringListFun2){.fun = fun_9, .env = env_14};
    struct StringList* call_77 = listFold_1(fun_21, acc_5, subspaces_1);
    struct StringList* call_78 = cons_1((struct String){.str = ")", .len = 1}, call_77);
    match_21 = call_78;
    goto end_match_75;
next_79:;
    struct StringList* call_79 = failwith_2((struct String){.str = "NEVER: suppress warning", .len = 23});
    match_21 = call_79;
    goto end_match_75;
next_80:;
end_match_75:;
    return match_21;
}

struct String spaceToString_(struct Space_ space_4) {
    struct StringList* call_80 = go_7(space_4, NULL);
    struct StringList* call_81 = listRev_1(call_80);
    struct String call_82 = strConcat_(call_81);
    return call_82;
}

struct IntSpace_Tuple2 fun_16(struct Space_Space_Tuple2 arg_34, int i_1, struct Ty_ itemTy_) {
    struct Space_ spaceFull_ = arg_34.t0;
    struct Space_ spaceUnit_ = arg_34.t1;
    struct Space_Space_Tuple2 tuple_30;
    tuple_30.t0 = spaceFull_;
    tuple_30.t1 = spaceUnit_;
    struct Space_ call_83 = go_8(tuple_30, itemTy_);
    struct IntSpace_Tuple2 tuple_29;
    tuple_29.t0 = i_1;
    tuple_29.t1 = call_83;
    return tuple_29;
}

struct IntSpace_Tuple2 fun_10(void* env_5, int arg_9, struct Ty_ arg_10) {
    struct Space_Space_Tuple2 arg_11 = (*(((struct Space_Space_Tuple2Tuple1*)env_5))).t0;
    struct IntSpace_Tuple2 call_84 = fun_16(arg_11, arg_9, arg_10);
    return call_84;
}

struct Space_ go_8(struct Space_Space_Tuple2 arg_35, struct Ty_ ty_1) {
    struct Space_ spaceFull_ = arg_35.t0;
    struct Space_ spaceUnit_ = arg_35.t1;
    struct Space_ match_22;
    if (!((ty_1.tag == Int_))) goto next_82;
    match_22 = spaceFull_;
    goto end_match_81;
next_82:;
    if (!((ty_1.tag == Tuple_))) goto next_83;
    if (!((!((*(ty_1.Tuple_)))))) goto next_83;
    match_22 = spaceUnit_;
    goto end_match_81;
next_83:;
    if (!((ty_1.tag == Tuple_))) goto next_84;
    struct Ty_List* itemTys_ = (*(ty_1.Tuple_));
    struct Space_Space_Tuple2 tuple_32;
    tuple_32.t0 = spaceFull_;
    tuple_32.t1 = spaceUnit_;
    struct Space_Space_Tuple2Tuple1 tuple_31;
    tuple_31.t0 = tuple_32;
    void* box_5 = (void*)malloc(sizeof(struct Space_Space_Tuple2Tuple1));
    (*(((struct Space_Space_Tuple2Tuple1*)box_5))) = tuple_31;
    void* env_15 = box_5;
    struct IntTy_IntSpace_Tuple2Fun2 fun_22 = (struct IntTy_IntSpace_Tuple2Fun2){.fun = fun_10, .env = env_15};
    struct IntSpace_Tuple2List* call_85 = listMapWithIndex_2(fun_22, itemTys_);
    struct Space_ call_86 = spaceSum_(call_85);
    match_22 = call_86;
    goto end_match_81;
next_84:;
    struct Space_ call_87 = failwith_1((struct String){.str = "unimpl", .len = 6});
    match_22 = call_87;
    goto end_match_81;
next_85:;
end_match_81:;
    return match_22;
}

struct Space_ tyToSpace_1(struct Space_Space_Tuple2 arg_36, int _ctx_, struct Ty_ ty_) {
    struct Space_ spaceFull_ = arg_36.t0;
    struct Space_ spaceUnit_ = arg_36.t1;
    struct Space_Space_Tuple2 tuple_33;
    tuple_33.t0 = spaceFull_;
    tuple_33.t1 = spaceUnit_;
    struct Space_ call_88 = go_8(tuple_33, ty_);
    return call_88;
}

struct Space_Space_Space_Tuple3 {
    struct Space_ t0;
    struct Space_ t1;
    struct Space_ t2;
};

struct IntSpace_Tuple2 fun_15(struct Space_Space_Space_Tuple3 arg_37, int i_2, struct Pat_ itemPat_) {
    struct Space_ spaceFull_ = arg_37.t0;
    struct Space_ spaceEmpty_ = arg_37.t1;
    struct Space_ spaceUnit_ = arg_37.t2;
    struct Space_Space_Space_Tuple3 tuple_35;
    tuple_35.t0 = spaceFull_;
    tuple_35.t1 = spaceEmpty_;
    tuple_35.t2 = spaceUnit_;
    struct Space_ call_89 = go_9(tuple_35, itemPat_);
    struct IntSpace_Tuple2 tuple_34;
    tuple_34.t0 = i_2;
    tuple_34.t1 = call_89;
    return tuple_34;
}

struct Space_Space_Space_Tuple3Tuple1 {
    struct Space_Space_Space_Tuple3 t0;
};

struct IntSpace_Tuple2 fun_11(void* env_6, int arg_12, struct Pat_ arg_13) {
    struct Space_Space_Space_Tuple3 arg_14 = (*(((struct Space_Space_Space_Tuple3Tuple1*)env_6))).t0;
    struct IntSpace_Tuple2 call_90 = fun_15(arg_14, arg_12, arg_13);
    return call_90;
}

struct Space_ go_9(struct Space_Space_Space_Tuple3 arg_38, struct Pat_ pat_1) {
    struct Space_ spaceFull_ = arg_38.t0;
    struct Space_ spaceEmpty_ = arg_38.t1;
    struct Space_ spaceUnit_ = arg_38.t2;
    struct Space_ match_23;
    if (!((pat_1.tag == Discard_))) goto next_87;
    match_23 = spaceFull_;
    goto end_match_86;
next_87:;
    if (!((pat_1.tag == IntLit_))) goto next_88;
    match_23 = spaceEmpty_;
    goto end_match_86;
next_88:;
    if (!((pat_1.tag == TupleLit_))) goto next_89;
    if (!((!((*(pat_1.TupleLit_)))))) goto next_89;
    match_23 = spaceUnit_;
    goto end_match_86;
next_89:;
    if (!((pat_1.tag == TupleLit_))) goto next_90;
    struct Pat_List* itemPats_ = (*(pat_1.TupleLit_));
    struct Space_Space_Space_Tuple3 tuple_37;
    tuple_37.t0 = spaceFull_;
    tuple_37.t1 = spaceEmpty_;
    tuple_37.t2 = spaceUnit_;
    struct Space_Space_Space_Tuple3Tuple1 tuple_36;
    tuple_36.t0 = tuple_37;
    void* box_6 = (void*)malloc(sizeof(struct Space_Space_Space_Tuple3Tuple1));
    (*(((struct Space_Space_Space_Tuple3Tuple1*)box_6))) = tuple_36;
    void* env_16 = box_6;
    struct IntPat_IntSpace_Tuple2Fun2 fun_23 = (struct IntPat_IntSpace_Tuple2Fun2){.fun = fun_11, .env = env_16};
    struct IntSpace_Tuple2List* call_91 = listMapWithIndex_1(fun_23, itemPats_);
    struct Space_ call_92 = spaceSum_(call_91);
    match_23 = call_92;
    goto end_match_86;
next_90:;
    struct Space_ call_93 = failwith_1((struct String){.str = "unimpl", .len = 6});
    match_23 = call_93;
    goto end_match_86;
next_91:;
end_match_86:;
    return match_23;
}

struct Space_ patToSpace_(struct Space_Space_Space_Tuple3 arg_39, int _ctx_1, struct Pat_ pat_) {
    struct Space_ spaceFull_ = arg_39.t0;
    struct Space_ spaceEmpty_ = arg_39.t1;
    struct Space_ spaceUnit_ = arg_39.t2;
    struct Space_Space_Space_Tuple3 tuple_38;
    tuple_38.t0 = spaceFull_;
    tuple_38.t1 = spaceEmpty_;
    tuple_38.t2 = spaceUnit_;
    struct Space_ call_94 = go_9(tuple_38, pat_);
    return call_94;
}

struct Space_Space_Space_Tuple3UnitTuple2 {
    struct Space_Space_Space_Tuple3 t0;
    int t1;
};

struct Space_ fun_12(void* env_7, struct Pat_ arg_15) {
    struct Space_Space_Space_Tuple3 arg_16 = (*(((struct Space_Space_Space_Tuple3UnitTuple2*)env_7))).t0;
    int arg_17 = (*(((struct Space_Space_Space_Tuple3UnitTuple2*)env_7))).t1;
    struct Space_ call_95 = patToSpace_(arg_16, 0, arg_15);
    return call_95;
}

struct Space_ patsToSpace_(struct Space_Space_Space_Tuple3 arg_40, int ctx_, struct Pat_List* pats_) {
    struct Space_ spaceFull_ = arg_40.t0;
    struct Space_ spaceEmpty_ = arg_40.t1;
    struct Space_ spaceUnit_ = arg_40.t2;
    struct Space_Space_Space_Tuple3 tuple_40;
    tuple_40.t0 = spaceFull_;
    tuple_40.t1 = spaceEmpty_;
    tuple_40.t2 = spaceUnit_;
    struct Space_Space_Space_Tuple3UnitTuple2 tuple_39;
    tuple_39.t0 = tuple_40;
    tuple_39.t1 = 0;
    void* box_7 = (void*)malloc(sizeof(struct Space_Space_Space_Tuple3UnitTuple2));
    (*(((struct Space_Space_Space_Tuple3UnitTuple2*)box_7))) = tuple_39;
    void* env_17 = box_7;
    struct Pat_Space_Fun1 fun_24 = (struct Pat_Space_Fun1){.fun = fun_12, .env = env_17};
    struct Space_List* call_96 = listMap_2(fun_24, pats_);
    struct Space_ call_97 = spaceUnion_(call_96);
    return call_97;
}

struct String coveringToString_(struct Covering_ covering_) {
    struct String match_24;
    if (!((covering_.tag == Covering_))) goto next_93;
    match_24 = (struct String){.str = "Covering", .len = 8};
    goto end_match_92;
next_93:;
    if (!((covering_.tag == Open_))) goto next_94;
    match_24 = (struct String){.str = "open", .len = 4};
    goto end_match_92;
next_94:;
end_match_92:;
    return match_24;
}

int fun_13(void* env_8, int arg_18) {
    int call_98 = id_1(arg_18);
    return call_98;
}

struct BoolStringTuple2 {
    int t0;
    struct String t1;
};

struct Covering_Covering_Tuple2 {
    struct Covering_ t0;
    struct Covering_ t1;
};

int fun_4(struct Space_Space_Space_Tuple3 arg_41, struct StringTy_Pat_ListCovering_Tuple4 arg_42) {
    struct Space_ spaceFull_ = arg_41.t0;
    struct Space_ spaceEmpty_ = arg_41.t1;
    struct Space_ spaceUnit_ = arg_41.t2;
    struct String name_ = arg_42.t0;
    struct Ty_ ty_2 = arg_42.t1;
    struct Pat_List* pats_1 = arg_42.t2;
    struct Covering_ covering_1 = arg_42.t3;
    int ctx_1 = 0;
    struct Space_Space_Tuple2 tuple_41;
    tuple_41.t0 = spaceFull_;
    tuple_41.t1 = spaceUnit_;
    struct Space_ call_99 = tyToSpace_1(tuple_41, 0, ty_2);
    struct Space_ tySpace_ = call_99;
    struct Space_Space_Space_Tuple3 tuple_42;
    tuple_42.t0 = spaceFull_;
    tuple_42.t1 = spaceEmpty_;
    tuple_42.t2 = spaceUnit_;
    struct Space_ call_100 = patsToSpace_(tuple_42, 0, pats_1);
    struct Space_ patSpace_ = call_100;
    struct Covering_ match_25;
    struct Space_Tuple1 tuple_43;
    tuple_43.t0 = spaceEmpty_;
    int call_101 = spaceCovers_(tuple_43, tySpace_, patSpace_);
    if (!((call_101 == 1))) goto next_96;
    match_25 = (struct Covering_){.tag = Covering_};
    goto end_match_95;
next_96:;
    if (!((call_101 == 0))) goto next_97;
    match_25 = (struct Covering_){.tag = Open_};
    goto end_match_95;
next_97:;
    exit(1);
end_match_95:;
    struct Covering_ actual_ = match_25;
    struct BoolStringTuple2 match_26;
    struct Covering_Covering_Tuple2 tuple_44;
    tuple_44.t0 = covering_1;
    tuple_44.t1 = actual_;
    if (!((tuple_44.t0.tag == Covering_))) goto next_100;
    if (!((tuple_44.t1.tag == Covering_))) goto next_100;
    goto match_body_99;
next_100:;
    if (!((tuple_44.t0.tag == Open_))) goto next_101;
    if (!((tuple_44.t1.tag == Open_))) goto next_101;
    goto match_body_99;
match_body_99:;
    struct BoolStringTuple2 tuple_45;
    tuple_45.t0 = 1;
    tuple_45.t1 = (struct String){.str = "OK", .len = 2};
    match_26 = tuple_45;
    goto end_match_98;
next_101:;
    if (!((tuple_44.t0.tag == Covering_))) goto next_102;
    if (!((tuple_44.t1.tag == Open_))) goto next_102;
    struct BoolStringTuple2 tuple_46;
    tuple_46.t0 = 0;
    tuple_46.t1 = (struct String){.str = "NG. Expected covering but open", .len = 30};
    match_26 = tuple_46;
    goto end_match_98;
next_102:;
    struct BoolStringTuple2 tuple_47;
    tuple_47.t0 = 0;
    tuple_47.t1 = (struct String){.str = "NG. Expected open but covering", .len = 30};
    match_26 = tuple_47;
    goto end_match_98;
next_103:;
end_match_98:;
    int ok_1 = match_26.t0;
    struct String msg_1 = match_26.t1;
    printf("%s: %s\n", name_.str, msg_1.str);
    int call_102 = 0;
    struct String call_103 = spaceToString_(tySpace_);
    printf("  ty: %s\n", call_103.str);
    int call_104 = 0;
    struct String call_105 = spaceToString_(patSpace_);
    printf("  pats: %s\n", call_105.str);
    int call_106 = 0;
    return ok_1;
}

int fun_14(void* env_9, struct StringTy_Pat_ListCovering_Tuple4 arg_19) {
    struct Space_Space_Space_Tuple3 arg_20 = (*(((struct Space_Space_Space_Tuple3Tuple1*)env_9))).t0;
    int call_107 = fun_4(arg_20, arg_19);
    return call_107;
}

int main() {
    struct Space_ spaceFull_ = (struct Space_){.tag = Full_};
    struct Space_List** payload_2 = (struct Space_List**)malloc(sizeof(struct Space_List*));
    (*(((struct Space_List**)payload_2))) = NULL;
    struct Space_ variant_3 = (struct Space_){.tag = Union_, .Union_ = payload_2};
    struct Space_ spaceEmpty_ = variant_3;
    struct Space_ spaceUnit_ = spaceFull_;
    int NilId_ = 0;
    int ConsId_ = 1;
    int ConsHeadId_ = 0;
    int ConsTailId_ = 1;
    int ConsRefId_ = (0 - 1);
    int call_108 = spaceIsEmpty_(spaceEmpty_);
    milone_assert(call_108);
    int call_109 = 0;
    struct Ty_List** payload_3 = (struct Ty_List**)malloc(sizeof(struct Ty_List*));
    (*(((struct Ty_List**)payload_3))) = NULL;
    struct Ty_ variant_4 = (struct Ty_){.tag = Tuple_, .Tuple_ = payload_3};
    struct Pat_List** payload_4 = (struct Pat_List**)malloc(sizeof(struct Pat_List*));
    (*(((struct Pat_List**)payload_4))) = NULL;
    struct Pat_ variant_5 = (struct Pat_){.tag = TupleLit_, .TupleLit_ = payload_4};
    struct Pat_List* list_13 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_13->head = variant_5;
    list_13->tail = NULL;
    struct StringTy_Pat_ListCovering_Tuple4 tuple_48;
    tuple_48.t0 = (struct String){.str = "unit with ()", .len = 12};
    tuple_48.t1 = variant_4;
    tuple_48.t2 = list_13;
    tuple_48.t3 = (struct Covering_){.tag = Covering_};
    int* payload_5 = (int*)malloc(sizeof(int));
    (*(((int*)payload_5))) = 1;
    struct Pat_ variant_6 = (struct Pat_){.tag = IntLit_, .IntLit_ = payload_5};
    struct Pat_List* list_15 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_15->head = variant_6;
    list_15->tail = NULL;
    struct StringTy_Pat_ListCovering_Tuple4 tuple_49;
    tuple_49.t0 = (struct String){.str = "int with literal pats", .len = 21};
    tuple_49.t1 = (struct Ty_){.tag = Int_};
    tuple_49.t2 = list_15;
    tuple_49.t3 = (struct Covering_){.tag = Open_};
    struct Ty_List** payload_6 = (struct Ty_List**)malloc(sizeof(struct Ty_List*));
    (*(((struct Ty_List**)payload_6))) = NULL;
    struct Ty_ variant_7 = (struct Ty_){.tag = Tuple_, .Tuple_ = payload_6};
    struct Pat_List* list_17 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_17->head = (struct Pat_){.tag = Discard_};
    list_17->tail = NULL;
    struct StringTy_Pat_ListCovering_Tuple4 tuple_50;
    tuple_50.t0 = (struct String){.str = "int with _", .len = 10};
    tuple_50.t1 = variant_7;
    tuple_50.t2 = list_17;
    tuple_50.t3 = (struct Covering_){.tag = Covering_};
    struct Ty_List** payload_7 = (struct Ty_List**)malloc(sizeof(struct Ty_List*));
    (*(((struct Ty_List**)payload_7))) = NULL;
    struct Ty_ variant_8 = (struct Ty_){.tag = Tuple_, .Tuple_ = payload_7};
    struct Ty_List* list_20 = (struct Ty_List*)malloc(sizeof(struct Ty_List));
    list_20->head = variant_8;
    list_20->tail = NULL;
    struct Ty_List* list_19 = (struct Ty_List*)malloc(sizeof(struct Ty_List));
    list_19->head = (struct Ty_){.tag = Int_};
    list_19->tail = list_20;
    struct Ty_List** payload_8 = (struct Ty_List**)malloc(sizeof(struct Ty_List*));
    (*(((struct Ty_List**)payload_8))) = list_19;
    struct Ty_ variant_9 = (struct Ty_){.tag = Tuple_, .Tuple_ = payload_8};
    struct Pat_List** payload_9 = (struct Pat_List**)malloc(sizeof(struct Pat_List*));
    (*(((struct Pat_List**)payload_9))) = NULL;
    struct Pat_ variant_10 = (struct Pat_){.tag = TupleLit_, .TupleLit_ = payload_9};
    struct Pat_List* list_23 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_23->head = variant_10;
    list_23->tail = NULL;
    struct Pat_List* list_22 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_22->head = (struct Pat_){.tag = Discard_};
    list_22->tail = list_23;
    struct Pat_List** payload_10 = (struct Pat_List**)malloc(sizeof(struct Pat_List*));
    (*(((struct Pat_List**)payload_10))) = list_22;
    struct Pat_ variant_11 = (struct Pat_){.tag = TupleLit_, .TupleLit_ = payload_10};
    struct Pat_List* list_21 = (struct Pat_List*)malloc(sizeof(struct Pat_List));
    list_21->head = variant_11;
    list_21->tail = NULL;
    struct StringTy_Pat_ListCovering_Tuple4 tuple_51;
    tuple_51.t0 = (struct String){.str = "int * unit with _, ()", .len = 21};
    tuple_51.t1 = variant_9;
    tuple_51.t2 = list_21;
    tuple_51.t3 = (struct Covering_){.tag = Covering_};
    struct StringTy_Pat_ListCovering_Tuple4List* list_18 = (struct StringTy_Pat_ListCovering_Tuple4List*)malloc(sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    list_18->head = tuple_51;
    list_18->tail = NULL;
    struct StringTy_Pat_ListCovering_Tuple4List* list_16 = (struct StringTy_Pat_ListCovering_Tuple4List*)malloc(sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    list_16->head = tuple_50;
    list_16->tail = list_18;
    struct StringTy_Pat_ListCovering_Tuple4List* list_14 = (struct StringTy_Pat_ListCovering_Tuple4List*)malloc(sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    list_14->head = tuple_49;
    list_14->tail = list_16;
    struct StringTy_Pat_ListCovering_Tuple4List* list_12 = (struct StringTy_Pat_ListCovering_Tuple4List*)malloc(sizeof(struct StringTy_Pat_ListCovering_Tuple4List));
    list_12->head = tuple_48;
    list_12->tail = list_14;
    struct StringTy_Pat_ListCovering_Tuple4List* testCases_ = list_12;
    void* box_8 = (void*)malloc(sizeof(int));
    (*(((int*)box_8))) = 0;
    void* env_18 = box_8;
    struct BoolBoolFun1 fun_25 = (struct BoolBoolFun1){.fun = fun_13, .env = env_18};
    struct Space_Space_Space_Tuple3 tuple_53;
    tuple_53.t0 = spaceFull_;
    tuple_53.t1 = spaceEmpty_;
    tuple_53.t2 = spaceUnit_;
    struct Space_Space_Space_Tuple3Tuple1 tuple_52;
    tuple_52.t0 = tuple_53;
    void* box_9 = (void*)malloc(sizeof(struct Space_Space_Space_Tuple3Tuple1));
    (*(((struct Space_Space_Space_Tuple3Tuple1*)box_9))) = tuple_52;
    void* env_19 = box_9;
    struct StringTy_Pat_ListCovering_Tuple4BoolFun1 fun_26 = (struct StringTy_Pat_ListCovering_Tuple4BoolFun1){.fun = fun_14, .env = env_19};
    struct BoolList* call_110 = listMap_1(fun_26, testCases_);
    int call_111 = listForAll_1(fun_25, call_110);
    int ok_ = call_111;
    int match_27;
    if (!((ok_ == 1))) goto next_105;
    match_27 = 0;
    goto end_match_104;
next_105:;
    if (!((ok_ == 0))) goto next_106;
    match_27 = 1;
    goto end_match_104;
next_106:;
    exit(1);
end_match_104:;
    int exitCode_ = match_27;
    return exitCode_;
}
