#include "milone.h"

int scanInt_(int arg_6);

void* rawIntArrayNew_(int len_);

int rawIntArrayGet_(void* array_, int index_);

void* rawIntArraySet_(void* array_1, int index_1, int value_);

void* rawMemoryCopy_(void* dest_, void* src_, int size_);

int ignore_1(void* __1);

struct IntList;

int go_6(int len_1, struct IntList* xs_1);

int listLength_1(struct IntList* xs_);

struct IntObjectFun1;

struct ObjectIntIntFun2;

struct ObjectIntIntObjectFun3;

enum TypeTag_Tag;

struct TypeTag_;

struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6;

struct IntObjectFun1 typeToArrayNew_1(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 arg_7);

struct ObjectIntIntFun2 typeToArrayGet_1(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 arg_8);

struct ObjectIntIntObjectFun3 typeToArraySet_1(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 arg_9);

void* fun_(void* env_, int arg_);

int fun_1(void* env_1, void* arg_1, int arg_2);

void* fun_2(void* env_2, void* arg_3, int arg_4, int arg_5);

enum VectorTag_Tag;

struct VectorTag_;

struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5;

int vectorToLength_1(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 arg_10);

struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 vectorNew_1(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 itemTy_, int len_3);

int vectorCheckIndex_1(int index_2, struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 self_);

int vectorGet_1(int index_3, struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 self_1);

int vectorSet_1(int index_4, int value_1, struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 self_2);

struct IntIntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5Tuple2;

int go_5(struct IntIntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5Tuple2 arg_11, int i_, struct IntList* xs_4);

struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 vectorOfList_1(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 ty_, struct IntList* xs_3);

int go_2(struct IntIntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5Tuple2 arg_12, int i_1);

struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1;

struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 scanIntVector_(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 arg_13, int len_7);

int refCase_(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 arg_14, int arg_15);

int vectorOfListTest_(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 arg_16, int arg_17);

int vectorTest_(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 arg_18, int arg_19);

int abc140aSolve_(int n_);

int abc140aTest_(int arg_20);

int abc140aMain_(int arg_21);

struct IntIntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5Tuple4;

int go_4(struct IntIntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5Tuple4 arg_22, int sum_, int i_2);

int abc140bSolve_1(int n_2, struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 a_, struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 b_, struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 c_);

int f_(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 arg_23, struct IntList* a_1, struct IntList* b_1, struct IntList* c_1);

int case1_(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 arg_24, int arg_25);

int case2_(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 arg_26, int arg_27);

int case3_(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 arg_28, int arg_29);

int abc140bTest_(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 arg_30, int arg_31);

int abc140bMain_(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 arg_32, int arg_33);

int main();

int scanInt_(int arg_6) {
    int call_ = scan_int(0);
    return call_;
}

void* rawIntArrayNew_(int len_) {
    void* call_1 = int_array_new(len_);
    return call_1;
}

int rawIntArrayGet_(void* array_, int index_) {
    int call_2 = int_array_get(array_, index_);
    return call_2;
}

void* rawIntArraySet_(void* array_1, int index_1, int value_) {
    void* call_3 = int_array_set(array_1, index_1, value_);
    return call_3;
}

void* rawMemoryCopy_(void* dest_, void* src_, int size_) {
    void* call_4 = memcpy(dest_, src_, size_);
    return call_4;
}

int ignore_1(void* __1) {
    return 0;
}

struct IntList {
    int head;
    struct IntList* tail;
};

int go_6(int len_1, struct IntList* xs_1) {
    int match_;
    if (!((!(xs_1)))) goto next_2;
    match_ = len_1;
    goto end_match_1;
next_2:;
    if (!((!((!(xs_1)))))) goto next_3;
    struct IntList* xs_2 = xs_1->tail;
    int call_5 = go_6((len_1 + 1), xs_2);
    match_ = call_5;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return match_;
}

int listLength_1(struct IntList* xs_) {
    int call_6 = go_6(0, xs_);
    return call_6;
}

struct IntObjectFun1 {
    void*(*fun)(void*, int);
    void* env;
};

struct ObjectIntIntFun2 {
    int(*fun)(void*, void*, int);
    void* env;
};

struct ObjectIntIntObjectFun3 {
    void*(*fun)(void*, void*, int, int);
    void* env;
};

enum TypeTag_Tag {
    TypeTag_,
};

struct TypeTag_ {
    enum TypeTag_Tag tag;
};

struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 {
    int t0;
    int t1;
    struct IntObjectFun1 t2;
    struct ObjectIntIntFun2 t3;
    struct ObjectIntIntObjectFun3 t4;
    struct TypeTag_ t5;
};

struct IntObjectFun1 typeToArrayNew_1(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 arg_7) {
    struct IntObjectFun1 arrayNew_ = arg_7.t2;
    struct TypeTag_ _typeTag_2 = arg_7.t5;
    return arrayNew_;
}

struct ObjectIntIntFun2 typeToArrayGet_1(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 arg_8) {
    struct ObjectIntIntFun2 arrayGet_ = arg_8.t3;
    struct TypeTag_ _typeTag_3 = arg_8.t5;
    return arrayGet_;
}

struct ObjectIntIntObjectFun3 typeToArraySet_1(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 arg_9) {
    struct ObjectIntIntObjectFun3 arraySet_ = arg_9.t4;
    struct TypeTag_ _typeTag_4 = arg_9.t5;
    return arraySet_;
}

void* fun_(void* env_, int arg_) {
    void* call_7 = rawIntArrayNew_(arg_);
    return call_7;
}

int fun_1(void* env_1, void* arg_1, int arg_2) {
    int call_8 = rawIntArrayGet_(arg_1, arg_2);
    return call_8;
}

void* fun_2(void* env_2, void* arg_3, int arg_4, int arg_5) {
    void* call_9 = rawIntArraySet_(arg_3, arg_4, arg_5);
    return call_9;
}

enum VectorTag_Tag {
    VectorTag_,
};

struct VectorTag_ {
    enum VectorTag_Tag tag;
};

struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 {
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 t0;
    void* t1;
    int t2;
    int t3;
    struct VectorTag_ t4;
};

int vectorToLength_1(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 arg_10) {
    int len_2 = arg_10.t2;
    struct VectorTag_ _vectorTag_ = arg_10.t4;
    return len_2;
}

struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 vectorNew_1(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 itemTy_, int len_3) {
    struct IntObjectFun1 call_10 = typeToArrayNew_1(itemTy_);
    void* app_ = call_10.fun(call_10.env, len_3);
    void* array_2 = app_;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 tuple_;
    tuple_.t0 = itemTy_;
    tuple_.t1 = array_2;
    tuple_.t2 = len_3;
    tuple_.t3 = len_3;
    tuple_.t4 = (struct VectorTag_){.tag = VectorTag_};
    return tuple_;
}

int vectorCheckIndex_1(int index_2, struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 self_) {
    int call_11 = vectorToLength_1(self_);
    int len_4 = call_11;
    int match_1;
    int match_2;
    if (!(((index_2 < 0) == 1))) goto next_6;
    match_2 = 1;
    goto end_match_5;
next_6:;
    if (!(((index_2 < 0) == 0))) goto next_7;
    match_2 = (len_4 <= index_2);
    goto end_match_5;
next_7:;
    exit(1);
end_match_5:;
    if (!((match_2 == 1))) goto next_8;
    printf("ERROR: Out of range (len = %d, index = %d)\n", len_4, index_2);
    int call_12 = 0;
    exit(1);
    match_1 = 0;
    goto end_match_4;
next_8:;
    if (!((match_2 == 0))) goto next_9;
    match_1 = 0;
    goto end_match_4;
next_9:;
    exit(1);
end_match_4:;
    return 0;
}

int vectorGet_1(int index_3, struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 self_1) {
    int call_13 = vectorCheckIndex_1(index_3, self_1);
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 itemTy_1 = self_1.t0;
    void* array_3 = self_1.t1;
    struct VectorTag_ _vectorTag_1 = self_1.t4;
    struct ObjectIntIntFun2 call_14 = typeToArrayGet_1(itemTy_1);
    int app_1 = call_14.fun(call_14.env, array_3, index_3);
    return app_1;
}

int vectorSet_1(int index_4, int value_1, struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 self_2) {
    int call_15 = vectorCheckIndex_1(index_4, self_2);
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 itemTy_2 = self_2.t0;
    void* array_4 = self_2.t1;
    struct VectorTag_ _vectorTag_2 = self_2.t4;
    struct ObjectIntIntObjectFun3 call_16 = typeToArraySet_1(itemTy_2);
    void* app_2 = call_16.fun(call_16.env, array_4, index_4, value_1);
    int call_17 = ignore_1(app_2);
    return 0;
}

struct IntIntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5Tuple2 {
    int t0;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 t1;
};

int go_5(struct IntIntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5Tuple2 arg_11, int i_, struct IntList* xs_4) {
    int len_6 = arg_11.t0;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 v_ = arg_11.t1;
    int match_3;
    if (!((!(xs_4)))) goto next_11;
    milone_assert((i_ == len_6));
    int call_18 = 0;
    match_3 = 0;
    goto end_match_10;
next_11:;
    if (!((!((!(xs_4)))))) goto next_12;
    int x_ = xs_4->head;
    struct IntList* xs_5 = xs_4->tail;
    int call_19 = vectorSet_1(i_, x_, v_);
    struct IntIntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5Tuple2 tuple_1;
    tuple_1.t0 = len_6;
    tuple_1.t1 = v_;
    int call_20 = go_5(tuple_1, (i_ + 1), xs_5);
    match_3 = 0;
    goto end_match_10;
next_12:;
    exit(1);
end_match_10:;
    return 0;
}

struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 vectorOfList_1(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 ty_, struct IntList* xs_3) {
    int call_21 = listLength_1(xs_3);
    int len_6 = call_21;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 call_22 = vectorNew_1(ty_, len_6);
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 v_ = call_22;
    struct IntIntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5Tuple2 tuple_2;
    tuple_2.t0 = len_6;
    tuple_2.t1 = v_;
    int call_23 = go_5(tuple_2, 0, xs_3);
    return v_;
}

int go_2(struct IntIntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5Tuple2 arg_12, int i_1) {
    int len_7 = arg_12.t0;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 v_1 = arg_12.t1;
    int match_4;
    if (!(((i_1 < len_7) == 1))) goto next_14;
    int call_24 = scanInt_(0);
    int value_3 = call_24;
    int call_25 = vectorSet_1(i_1, value_3, v_1);
    struct IntIntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5Tuple2 tuple_3;
    tuple_3.t0 = len_7;
    tuple_3.t1 = v_1;
    int call_26 = go_2(tuple_3, (i_1 + 1));
    match_4 = 0;
    goto end_match_13;
next_14:;
    if (!(((i_1 < len_7) == 0))) goto next_15;
    match_4 = 0;
    goto end_match_13;
next_15:;
    exit(1);
end_match_13:;
    return 0;
}

struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 {
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 t0;
};

struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 scanIntVector_(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 arg_13, int len_7) {
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 typeInt_ = arg_13.t0;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 call_27 = vectorNew_1(typeInt_, len_7);
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 v_1 = call_27;
    struct IntIntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5Tuple2 tuple_4;
    tuple_4.t0 = len_7;
    tuple_4.t1 = v_1;
    int call_28 = go_2(tuple_4, 0);
    return v_1;
}

int refCase_(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 arg_14, int arg_15) {
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 typeInt_ = arg_14.t0;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 call_29 = vectorNew_1(typeInt_, 1);
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 v_2 = call_29;
    int call_30 = vectorToLength_1(v_2);
    milone_assert((call_30 == 1));
    int call_31 = 0;
    int call_32 = vectorGet_1(0, v_2);
    milone_assert((call_32 == 0));
    int call_33 = 0;
    int call_34 = vectorSet_1(0, 42, v_2);
    int call_35 = vectorGet_1(0, v_2);
    milone_assert((call_35 == 42));
    int call_36 = 0;
    return 0;
}

int vectorOfListTest_(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 arg_16, int arg_17) {
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 typeInt_ = arg_16.t0;
    struct IntList* list_2 = (struct IntList*)malloc(sizeof(struct IntList));
    list_2->head = 3;
    list_2->tail = NULL;
    struct IntList* list_1 = (struct IntList*)malloc(sizeof(struct IntList));
    list_1->head = 2;
    list_1->tail = list_2;
    struct IntList* list_ = (struct IntList*)malloc(sizeof(struct IntList));
    list_->head = 1;
    list_->tail = list_1;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 call_37 = vectorOfList_1(typeInt_, list_);
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 v_3 = call_37;
    int call_38 = vectorToLength_1(v_3);
    milone_assert((call_38 == 3));
    int call_39 = 0;
    int call_40 = vectorGet_1(0, v_3);
    milone_assert((call_40 == 1));
    int call_41 = 0;
    int call_42 = vectorGet_1(1, v_3);
    milone_assert((call_42 == 2));
    int call_43 = 0;
    int call_44 = vectorGet_1(2, v_3);
    milone_assert((call_44 == 3));
    int call_45 = 0;
    return 0;
}

int vectorTest_(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 arg_18, int arg_19) {
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 typeInt_ = arg_18.t0;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 tuple_5;
    tuple_5.t0 = typeInt_;
    int call_46 = refCase_(tuple_5, 0);
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 tuple_6;
    tuple_6.t0 = typeInt_;
    int call_47 = vectorOfListTest_(tuple_6, 0);
    return 0;
}

int abc140aSolve_(int n_) {
    return ((n_ * n_) * n_);
}

int abc140aTest_(int arg_20) {
    int call_48 = abc140aSolve_(2);
    milone_assert((call_48 == 8));
    int call_49 = 0;
    int call_50 = abc140aSolve_(1);
    milone_assert((call_50 == 1));
    int call_51 = 0;
    return 0;
}

int abc140aMain_(int arg_21) {
    int call_52 = scanInt_(0);
    int n_1 = call_52;
    int call_53 = abc140aSolve_(n_1);
    int m_ = call_53;
    printf("%d\n", m_);
    int call_54 = 0;
    return 0;
}

struct IntIntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5Tuple4 {
    int t0;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 t1;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 t2;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 t3;
};

int go_4(struct IntIntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5Tuple4 arg_22, int sum_, int i_2) {
    int n_2 = arg_22.t0;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 a_ = arg_22.t1;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 b_ = arg_22.t2;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 c_ = arg_22.t3;
    int match_5;
    if (!(((i_2 == n_2) == 1))) goto next_17;
    match_5 = sum_;
    goto end_match_16;
next_17:;
    if (!(((i_2 == n_2) == 0))) goto next_18;
    int call_55 = vectorGet_1(i_2, a_);
    int ai_ = call_55;
    int call_56 = vectorGet_1((ai_ - 1), b_);
    int eat_ = call_56;
    int match_6;
    int match_7;
    if (!((((i_2 + 1) < n_2) == 1))) goto next_21;
    int call_57 = vectorGet_1((i_2 + 1), a_);
    match_7 = (call_57 == (ai_ + 1));
    goto end_match_20;
next_21:;
    if (!((((i_2 + 1) < n_2) == 0))) goto next_22;
    match_7 = 0;
    goto end_match_20;
next_22:;
    exit(1);
end_match_20:;
    if (!((match_7 == 1))) goto next_23;
    int call_58 = vectorGet_1((ai_ - 1), c_);
    match_6 = call_58;
    goto end_match_19;
next_23:;
    if (!((match_7 == 0))) goto next_24;
    match_6 = 0;
    goto end_match_19;
next_24:;
    exit(1);
end_match_19:;
    int bonus_ = match_6;
    struct IntIntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5Tuple4 tuple_7;
    tuple_7.t0 = n_2;
    tuple_7.t1 = a_;
    tuple_7.t2 = b_;
    tuple_7.t3 = c_;
    int call_59 = go_4(tuple_7, ((sum_ + eat_) + bonus_), (i_2 + 1));
    match_5 = call_59;
    goto end_match_16;
next_18:;
    exit(1);
end_match_16:;
    return match_5;
}

int abc140bSolve_1(int n_2, struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 a_, struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 b_, struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 c_) {
    struct IntIntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5Tuple4 tuple_8;
    tuple_8.t0 = n_2;
    tuple_8.t1 = a_;
    tuple_8.t2 = b_;
    tuple_8.t3 = c_;
    int call_60 = go_4(tuple_8, 0, 0);
    return call_60;
}

int f_(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 arg_23, struct IntList* a_1, struct IntList* b_1, struct IntList* c_1) {
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 typeInt_ = arg_23.t0;
    int call_61 = listLength_1(a_1);
    int n_3 = call_61;
    int call_62 = listLength_1(b_1);
    milone_assert((call_62 == n_3));
    int call_63 = 0;
    int call_64 = listLength_1(c_1);
    milone_assert((call_64 == (n_3 - 1)));
    int call_65 = 0;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 call_66 = vectorOfList_1(typeInt_, a_1);
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 a_2 = call_66;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 call_67 = vectorOfList_1(typeInt_, b_1);
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 b_2 = call_67;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 call_68 = vectorOfList_1(typeInt_, c_1);
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 c_2 = call_68;
    int call_69 = abc140bSolve_1(n_3, a_2, b_2, c_2);
    return call_69;
}

int case1_(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 arg_24, int arg_25) {
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 typeInt_ = arg_24.t0;
    struct IntList* list_5 = (struct IntList*)malloc(sizeof(struct IntList));
    list_5->head = 2;
    list_5->tail = NULL;
    struct IntList* list_4 = (struct IntList*)malloc(sizeof(struct IntList));
    list_4->head = 1;
    list_4->tail = list_5;
    struct IntList* list_3 = (struct IntList*)malloc(sizeof(struct IntList));
    list_3->head = 3;
    list_3->tail = list_4;
    struct IntList* a_3 = list_3;
    struct IntList* list_8 = (struct IntList*)malloc(sizeof(struct IntList));
    list_8->head = 4;
    list_8->tail = NULL;
    struct IntList* list_7 = (struct IntList*)malloc(sizeof(struct IntList));
    list_7->head = 5;
    list_7->tail = list_8;
    struct IntList* list_6 = (struct IntList*)malloc(sizeof(struct IntList));
    list_6->head = 2;
    list_6->tail = list_7;
    struct IntList* b_3 = list_6;
    struct IntList* list_10 = (struct IntList*)malloc(sizeof(struct IntList));
    list_10->head = 6;
    list_10->tail = NULL;
    struct IntList* list_9 = (struct IntList*)malloc(sizeof(struct IntList));
    list_9->head = 3;
    list_9->tail = list_10;
    struct IntList* c_3 = list_9;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 tuple_9;
    tuple_9.t0 = typeInt_;
    int call_70 = f_(tuple_9, a_3, b_3, c_3);
    return (call_70 == 14);
}

int case2_(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 arg_26, int arg_27) {
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 typeInt_ = arg_26.t0;
    struct IntList* list_14 = (struct IntList*)malloc(sizeof(struct IntList));
    list_14->head = 1;
    list_14->tail = NULL;
    struct IntList* list_13 = (struct IntList*)malloc(sizeof(struct IntList));
    list_13->head = 4;
    list_13->tail = list_14;
    struct IntList* list_12 = (struct IntList*)malloc(sizeof(struct IntList));
    list_12->head = 3;
    list_12->tail = list_13;
    struct IntList* list_11 = (struct IntList*)malloc(sizeof(struct IntList));
    list_11->head = 2;
    list_11->tail = list_12;
    struct IntList* a_4 = list_11;
    struct IntList* list_18 = (struct IntList*)malloc(sizeof(struct IntList));
    list_18->head = 24;
    list_18->tail = NULL;
    struct IntList* list_17 = (struct IntList*)malloc(sizeof(struct IntList));
    list_17->head = 8;
    list_17->tail = list_18;
    struct IntList* list_16 = (struct IntList*)malloc(sizeof(struct IntList));
    list_16->head = 5;
    list_16->tail = list_17;
    struct IntList* list_15 = (struct IntList*)malloc(sizeof(struct IntList));
    list_15->head = 13;
    list_15->tail = list_16;
    struct IntList* b_4 = list_15;
    struct IntList* list_21 = (struct IntList*)malloc(sizeof(struct IntList));
    list_21->head = 15;
    list_21->tail = NULL;
    struct IntList* list_20 = (struct IntList*)malloc(sizeof(struct IntList));
    list_20->head = 9;
    list_20->tail = list_21;
    struct IntList* list_19 = (struct IntList*)malloc(sizeof(struct IntList));
    list_19->head = 45;
    list_19->tail = list_20;
    struct IntList* c_4 = list_19;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 tuple_10;
    tuple_10.t0 = typeInt_;
    int call_71 = f_(tuple_10, a_4, b_4, c_4);
    return (call_71 == 74);
}

int case3_(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 arg_28, int arg_29) {
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 typeInt_ = arg_28.t0;
    struct IntList* list_23 = (struct IntList*)malloc(sizeof(struct IntList));
    list_23->head = 2;
    list_23->tail = NULL;
    struct IntList* list_22 = (struct IntList*)malloc(sizeof(struct IntList));
    list_22->head = 1;
    list_22->tail = list_23;
    struct IntList* a_5 = list_22;
    struct IntList* list_25 = (struct IntList*)malloc(sizeof(struct IntList));
    list_25->head = 50;
    list_25->tail = NULL;
    struct IntList* list_24 = (struct IntList*)malloc(sizeof(struct IntList));
    list_24->head = 50;
    list_24->tail = list_25;
    struct IntList* b_5 = list_24;
    struct IntList* list_26 = (struct IntList*)malloc(sizeof(struct IntList));
    list_26->head = 50;
    list_26->tail = NULL;
    struct IntList* c_5 = list_26;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 tuple_11;
    tuple_11.t0 = typeInt_;
    int call_72 = f_(tuple_11, a_5, b_5, c_5);
    return (call_72 == 150);
}

int abc140bTest_(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 arg_30, int arg_31) {
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 typeInt_ = arg_30.t0;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 tuple_12;
    tuple_12.t0 = typeInt_;
    int call_73 = case1_(tuple_12, 0);
    milone_assert(call_73);
    int call_74 = 0;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 tuple_13;
    tuple_13.t0 = typeInt_;
    int call_75 = case2_(tuple_13, 0);
    milone_assert(call_75);
    int call_76 = 0;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 tuple_14;
    tuple_14.t0 = typeInt_;
    int call_77 = case3_(tuple_14, 0);
    milone_assert(call_77);
    int call_78 = 0;
    return 0;
}

int abc140bMain_(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 arg_32, int arg_33) {
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 typeInt_ = arg_32.t0;
    int call_79 = scanInt_(0);
    int n_4 = call_79;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 tuple_15;
    tuple_15.t0 = typeInt_;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 call_80 = scanIntVector_(tuple_15, n_4);
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 a_6 = call_80;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 tuple_16;
    tuple_16.t0 = typeInt_;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 call_81 = scanIntVector_(tuple_16, n_4);
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 b_6 = call_81;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 tuple_17;
    tuple_17.t0 = typeInt_;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 call_82 = scanIntVector_(tuple_17, (n_4 - 1));
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 c_6 = call_82;
    int call_83 = abc140bSolve_1(n_4, a_6, b_6, c_6);
    int m_1 = call_83;
    printf("%d\n", m_1);
    int call_84 = 0;
    return 0;
}

int main() {
    void* box_ = (void*)malloc(sizeof(int));
    (*(((int*)box_))) = 0;
    void* env_3 = box_;
    struct IntObjectFun1 fun_3 = (struct IntObjectFun1){.fun = fun_, .env = env_3};
    void* box_1 = (void*)malloc(sizeof(int));
    (*(((int*)box_1))) = 0;
    void* env_4 = box_1;
    struct ObjectIntIntFun2 fun_4 = (struct ObjectIntIntFun2){.fun = fun_1, .env = env_4};
    void* box_2 = (void*)malloc(sizeof(int));
    (*(((int*)box_2))) = 0;
    void* env_5 = box_2;
    struct ObjectIntIntObjectFun3 fun_5 = (struct ObjectIntIntObjectFun3){.fun = fun_2, .env = env_5};
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 tuple_18;
    tuple_18.t0 = 0;
    tuple_18.t1 = 4;
    tuple_18.t2 = fun_3;
    tuple_18.t3 = fun_4;
    tuple_18.t4 = fun_5;
    tuple_18.t5 = (struct TypeTag_){.tag = TypeTag_};
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 typeInt_ = tuple_18;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 tuple_19;
    tuple_19.t0 = typeInt_;
    int call_85 = vectorTest_(tuple_19, 0);
    int call_86 = abc140aTest_(0);
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 tuple_20;
    tuple_20.t0 = typeInt_;
    int call_87 = abc140bTest_(tuple_20, 0);
    return 0;
}
