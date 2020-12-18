#include "milone.h"

struct StringList;

struct String str_concat(struct String, struct StringList const*);

struct String __stringJoin_(struct String sep_, struct StringList const* xs_);

intptr_t __pointeeSize_2(int const* constPtr_);

intptr_t __pointeeSize_1(int const* constPtr_);

int const* __ptrAsConst_2(int* mutPtr_1);

int const* __ptrAsConst_1(int* mutPtr_1);

int const* __ptrAdd_1(int index_, int const* ptr_);

int* __mutPtrAdd_1(int index_1, int* mutPtr_2);

void* milone_mem_alloc(int, uintptr_t);

void* memAlloc_(int len_, uintptr_t size_);

void* memcpy(void*, void const*, uintptr_t);

void* memcpy_(void* dest_, void const* src_, uintptr_t size_1);

struct UnitMutPtrIntTuple2;

struct UnitMutPtrIntTuple2 __mutArrayCreate_2(int len_1);

struct IntMutPtrIntTuple2;

struct IntMutPtrIntTuple2 __mutArrayCreate_1(int len_1);

int __mutArraySet_2(int index_2, int value_, struct UnitMutPtrIntTuple2 array_);

int __mutArraySet_1(int index_2, int value_, struct IntMutPtrIntTuple2 array_);

struct IntMutPtrIntTuple2 __mutArraySlice_1(int start_, int endIndex_, struct IntMutPtrIntTuple2 array_1);

struct UnitConstPtrIntTuple2;

struct UnitConstPtrIntTuple2 __constArrayOfMut_2(struct UnitMutPtrIntTuple2 mutArray_);

struct IntConstPtrIntTuple2;

struct IntConstPtrIntTuple2 __constArrayOfMut_1(struct IntMutPtrIntTuple2 mutArray_);

int __constArrayLength_2(struct UnitConstPtrIntTuple2 array_2);

int __constArrayLength_1(struct IntConstPtrIntTuple2 array_2);

int __constArrayGet_1(int index_3, struct IntConstPtrIntTuple2 array_3);

struct IntConstPtrIntTuple2 __constArraySlice_1(int start_1, int endIndex_1, struct IntConstPtrIntTuple2 array_4);

struct IntConstPtrIntTuple2 empty_3(int arg_20);

struct UnitConstPtrIntTuple2 empty_4(int arg_21);

struct IntUnitFun1;

int arrayInitLoop_2(int len_8, struct IntUnitFun1 f_, struct UnitMutPtrIntTuple2 array_7, int i_4);

struct IntIntFun1;

int arrayInitLoop_1(int len_8, struct IntIntFun1 f_, struct IntMutPtrIntTuple2 array_7, int i_4);

struct UnitConstPtrIntTuple2 init_2(int len_8, struct IntUnitFun1 f_);

struct IntConstPtrIntTuple2 init_1(int len_8, struct IntIntFun1 f_);

int fun_8(int i_5);

int fun_13(void const* env_1, int arg_2);

struct IntConstPtrIntTuple2 range_(int len_10);

int length_2(struct UnitConstPtrIntTuple2 array_8);

int length_1(struct IntConstPtrIntTuple2 array_8);

struct IntList;

struct IntList const* tryItem_1(int i_6, struct IntConstPtrIntTuple2 array_10);

struct IntConstPtrIntTuple2 slice_1(int start_2, int endIndex_2, struct IntConstPtrIntTuple2 array_11);

struct IntConstPtrIntTuple2 skip_1(int skipLen_, struct IntConstPtrIntTuple2 array_12);

struct IntIntConstPtrIntTuple2Tuple2;

struct IntIntConstPtrIntTuple2Tuple2List;

struct IntIntConstPtrIntTuple2Tuple2List const* uncons_1(struct IntConstPtrIntTuple2 array_15);

struct IntIntIntFun2;

int fun_25(struct IntIntIntFun2 f_1, struct IntConstPtrIntTuple2 array_16, int i_7);

struct IntIntIntFun2IntConstPtrIntTuple2Tuple2;

int fun_24(void const* env_2, int arg_3);

struct IntConstPtrIntTuple2 mapi_1(struct IntIntIntFun2 f_1, struct IntConstPtrIntTuple2 array_16);

struct IntIntListFun1;

int chooseLoop_1(struct IntIntListFun1 f_3, struct IntConstPtrIntTuple2 src_1, int len_13, struct IntMutPtrIntTuple2 dest_1, int di_, int si_);

struct IntConstPtrIntTuple2 choose_1(struct IntIntListFun1 f_3, struct IntConstPtrIntTuple2 src_1);

int arrayFoldLoop_1(struct IntIntIntFun2 folder_, struct IntConstPtrIntTuple2 array_18, int len_14, int state_2, int i_9);

int fold_1(struct IntIntIntFun2 folder_, int state_1, struct IntConstPtrIntTuple2 array_18);

int listLengthLoop_1(int acc_, struct IntList const* xs_2);

int ofListLoop_1(int len_15, struct IntMutPtrIntTuple2 dest_2, int i_10, struct IntList const* xs_4);

struct IntConstPtrIntTuple2 ofList_1(struct IntList const* xs_1);

struct IntList const* toListLoop_1(struct IntConstPtrIntTuple2 array_19, struct IntList const* acc_1, int i_11);

struct IntList const* toList_1(struct IntConstPtrIntTuple2 array_19);

int get_1(int i_, struct IntConstPtrIntTuple2 array_5);

int fun_(int arg_56);

int fun_17(void const* env_5, int arg_11);

int fun_1(int n_);

int fun_18(void const* env_6, int arg_12);

int initTest_(int arg_57);

int rangeTest_(int arg_58);

int at_(int bad_, int i_1, struct IntConstPtrIntTuple2 array_6);

int tryItemTest_(int arg_59);

int sliceTest_(int arg_60);

int fun_2(int n_1);

int fun_19(void const* env_7, int arg_13);

int unconsTest_(int arg_61);

int fun_3(int i_2, int n_2);

int fun_20(void const* env_8, int arg_14, int arg_15);

int mapTest_(int arg_62);

struct IntList const* fun_4(int n_3);

struct IntList const* fun_21(void const* env_9, int arg_16);

struct IntList const* fun_5(int arg_63);

struct IntList const* fun_22(void const* env_10, int arg_17);

int chooseTest_(int arg_64);

int fun_6(int state_, int i_3);

int fun_23(void const* env_11, int arg_18, int arg_19);

int foldTest_(int arg_65);

int ofListTest_(int arg_66);

int toListTest_(int arg_67);

int main();

struct StringList {
    struct String head;
    struct StringList const* tail;
};

struct String __stringJoin_(struct String sep_, struct StringList const* xs_) {
    struct String str_concat_result_ = str_concat(sep_, xs_);
    return str_concat_result_;
}

intptr_t __pointeeSize_2(int const* constPtr_) {
    return ((intptr_t)sizeof(int));
}

intptr_t __pointeeSize_1(int const* constPtr_) {
    return ((intptr_t)sizeof(int));
}

int const* __ptrAsConst_2(int* mutPtr_1) {
    int const* constPtr_2 = ((int const*)mutPtr_1);
    return constPtr_2;
}

int const* __ptrAsConst_1(int* mutPtr_1) {
    int const* constPtr_2 = ((int const*)mutPtr_1);
    return constPtr_2;
}

int const* __ptrAdd_1(int index_, int const* ptr_) {
    intptr_t call_ = __pointeeSize_1(ptr_);
    int const* addedPtr_ = ((int const*)(((intptr_t)ptr_) + (((intptr_t)index_) * call_)));
    return addedPtr_;
}

int* __mutPtrAdd_1(int index_1, int* mutPtr_2) {
    int const* call_1 = __ptrAsConst_1(mutPtr_2);
    intptr_t call_2 = __pointeeSize_1(call_1);
    int* addedPtr_1 = ((int*)(((intptr_t)mutPtr_2) + (((intptr_t)index_1) * call_2)));
    return addedPtr_1;
}

void* memAlloc_(int len_, uintptr_t size_) {
    void* milone_mem_alloc_result_ = milone_mem_alloc(len_, size_);
    return milone_mem_alloc_result_;
}

void* memcpy_(void* dest_, void const* src_, uintptr_t size_1) {
    void* memcpy_result_ = memcpy(dest_, src_, size_1);
    return memcpy_result_;
}

struct UnitMutPtrIntTuple2 {
    int* t0;
    int t1;
};

struct UnitMutPtrIntTuple2 __mutArrayCreate_2(int len_1) {
    struct UnitMutPtrIntTuple2 if_;
    if ((len_1 == 0)) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    struct UnitMutPtrIntTuple2 tuple_;
    tuple_.t0 = ((int*)((uintptr_t)0));
    tuple_.t1 = 0;
    if_ = tuple_;
    goto if_next_1;
else_3:;
    int const* nullPtr_ = ((int const*)((uintptr_t)0));
    intptr_t call_3 = __pointeeSize_2(nullPtr_);
    void* call_4 = memAlloc_(len_1, ((uintptr_t)call_3));
    int* ptr_1 = ((int*)call_4);
    struct UnitMutPtrIntTuple2 tuple_1;
    tuple_1.t0 = ptr_1;
    tuple_1.t1 = len_1;
    if_ = tuple_1;
    goto if_next_1;
if_next_1:;
    return if_;
}

struct IntMutPtrIntTuple2 {
    int* t0;
    int t1;
};

struct IntMutPtrIntTuple2 __mutArrayCreate_1(int len_1) {
    struct IntMutPtrIntTuple2 if_1;
    if ((len_1 == 0)) {
        goto then_5;
    } else {
        goto else_6;
    }
then_5:;
    struct IntMutPtrIntTuple2 tuple_2;
    tuple_2.t0 = ((int*)((uintptr_t)0));
    tuple_2.t1 = 0;
    if_1 = tuple_2;
    goto if_next_4;
else_6:;
    int const* nullPtr_ = ((int const*)((uintptr_t)0));
    intptr_t call_5 = __pointeeSize_1(nullPtr_);
    void* call_6 = memAlloc_(len_1, ((uintptr_t)call_5));
    int* ptr_1 = ((int*)call_6);
    struct IntMutPtrIntTuple2 tuple_3;
    tuple_3.t0 = ptr_1;
    tuple_3.t1 = len_1;
    if_1 = tuple_3;
    goto if_next_4;
if_next_4:;
    return if_1;
}

int __mutArraySet_2(int index_2, int value_, struct UnitMutPtrIntTuple2 array_) {
    int* mutPtr_3 = array_.t0;
    int len_2 = array_.t1;
    milone_assert((((uint32_t)index_2) < ((uint32_t)len_2)), 59, 2);
    mutPtr_3[index_2] = 0;
    return 0;
}

int __mutArraySet_1(int index_2, int value_, struct IntMutPtrIntTuple2 array_) {
    int* mutPtr_3 = array_.t0;
    int len_2 = array_.t1;
    milone_assert((((uint32_t)index_2) < ((uint32_t)len_2)), 59, 2);
    mutPtr_3[index_2] = value_;
    return 0;
}

struct IntMutPtrIntTuple2 __mutArraySlice_1(int start_, int endIndex_, struct IntMutPtrIntTuple2 array_1) {
    int* mutPtr_4 = array_1.t0;
    int len_3 = array_1.t1;
    bool if_2;
    if ((start_ >= 0)) {
        goto then_8;
    } else {
        goto else_9;
    }
then_8:;
    if_2 = (endIndex_ >= start_);
    goto if_next_7;
else_9:;
    if_2 = false;
    goto if_next_7;
if_next_7:;
    bool if_3;
    if (if_2) {
        goto then_11;
    } else {
        goto else_12;
    }
then_11:;
    if_3 = (len_3 >= endIndex_);
    goto if_next_10;
else_12:;
    if_3 = false;
    goto if_next_10;
if_next_10:;
    milone_assert(if_3, 66, 2);
    int* call_7 = __mutPtrAdd_1(start_, mutPtr_4);
    struct IntMutPtrIntTuple2 tuple_4;
    tuple_4.t0 = call_7;
    tuple_4.t1 = (endIndex_ - start_);
    return tuple_4;
}

struct UnitConstPtrIntTuple2 {
    int const* t0;
    int t1;
};

struct UnitConstPtrIntTuple2 __constArrayOfMut_2(struct UnitMutPtrIntTuple2 mutArray_) {
    int* mutPtr_5 = mutArray_.t0;
    int len_4 = mutArray_.t1;
    int const* call_8 = __ptrAsConst_2(mutPtr_5);
    struct UnitConstPtrIntTuple2 tuple_5;
    tuple_5.t0 = call_8;
    tuple_5.t1 = len_4;
    return tuple_5;
}

struct IntConstPtrIntTuple2 {
    int const* t0;
    int t1;
};

struct IntConstPtrIntTuple2 __constArrayOfMut_1(struct IntMutPtrIntTuple2 mutArray_) {
    int* mutPtr_5 = mutArray_.t0;
    int len_4 = mutArray_.t1;
    int const* call_9 = __ptrAsConst_1(mutPtr_5);
    struct IntConstPtrIntTuple2 tuple_6;
    tuple_6.t0 = call_9;
    tuple_6.t1 = len_4;
    return tuple_6;
}

int __constArrayLength_2(struct UnitConstPtrIntTuple2 array_2) {
    int len_5 = array_2.t1;
    return len_5;
}

int __constArrayLength_1(struct IntConstPtrIntTuple2 array_2) {
    int len_5 = array_2.t1;
    return len_5;
}

int __constArrayGet_1(int index_3, struct IntConstPtrIntTuple2 array_3) {
    int const* ptr_2 = array_3.t0;
    int len_6 = array_3.t1;
    milone_assert((((uint32_t)index_3) < ((uint32_t)len_6)), 86, 2);
    int read_ = ptr_2[index_3];
    return read_;
}

struct IntConstPtrIntTuple2 __constArraySlice_1(int start_1, int endIndex_1, struct IntConstPtrIntTuple2 array_4) {
    int const* ptr_3 = array_4.t0;
    int len_7 = array_4.t1;
    bool if_4;
    if ((start_1 >= 0)) {
        goto then_14;
    } else {
        goto else_15;
    }
then_14:;
    if_4 = (endIndex_1 >= start_1);
    goto if_next_13;
else_15:;
    if_4 = false;
    goto if_next_13;
if_next_13:;
    bool if_5;
    if (if_4) {
        goto then_17;
    } else {
        goto else_18;
    }
then_17:;
    if_5 = (len_7 >= endIndex_1);
    goto if_next_16;
else_18:;
    if_5 = false;
    goto if_next_16;
if_next_16:;
    milone_assert(if_5, 92, 2);
    int const* call_10 = __ptrAdd_1(start_1, ptr_3);
    struct IntConstPtrIntTuple2 tuple_7;
    tuple_7.t0 = call_10;
    tuple_7.t1 = (endIndex_1 - start_1);
    return tuple_7;
}

struct IntConstPtrIntTuple2 empty_3(int arg_20) {
    struct IntMutPtrIntTuple2 call_11 = __mutArrayCreate_1(0);
    struct IntConstPtrIntTuple2 call_12 = __constArrayOfMut_1(call_11);
    return call_12;
}

struct UnitConstPtrIntTuple2 empty_4(int arg_21) {
    struct UnitMutPtrIntTuple2 call_13 = __mutArrayCreate_2(0);
    struct UnitConstPtrIntTuple2 call_14 = __constArrayOfMut_2(call_13);
    return call_14;
}

struct IntUnitFun1 {
    int(*fun)(void const*, int);
    void const* env;
};

int arrayInitLoop_2(int len_8, struct IntUnitFun1 f_, struct UnitMutPtrIntTuple2 array_7, int i_4) {
tailrec_19:;
    int if_6;
    if ((i_4 < len_8)) {
        goto then_21;
    } else {
        goto else_22;
    }
then_21:;
    int app_ = f_.fun(f_.env, i_4);
    int item_ = 0;
    int call_15 = __mutArraySet_2(i_4, 0, array_7);
    int arg_22 = len_8;
    struct IntUnitFun1 arg_23 = f_;
    struct UnitMutPtrIntTuple2 arg_24 = array_7;
    int arg_25 = (i_4 + 1);
    len_8 = arg_22;
    f_ = arg_23;
    array_7 = arg_24;
    i_4 = arg_25;
    goto tailrec_19;
    if_6 = 0;
    goto if_next_20;
else_22:;
    if_6 = 0;
    goto if_next_20;
if_next_20:;
    return 0;
}

struct IntIntFun1 {
    int(*fun)(void const*, int);
    void const* env;
};

int arrayInitLoop_1(int len_8, struct IntIntFun1 f_, struct IntMutPtrIntTuple2 array_7, int i_4) {
tailrec_23:;
    int if_7;
    if ((i_4 < len_8)) {
        goto then_25;
    } else {
        goto else_26;
    }
then_25:;
    int app_1 = f_.fun(f_.env, i_4);
    int item_ = app_1;
    int call_16 = __mutArraySet_1(i_4, item_, array_7);
    int arg_26 = len_8;
    struct IntIntFun1 arg_27 = f_;
    struct IntMutPtrIntTuple2 arg_28 = array_7;
    int arg_29 = (i_4 + 1);
    len_8 = arg_26;
    f_ = arg_27;
    array_7 = arg_28;
    i_4 = arg_29;
    goto tailrec_23;
    if_7 = 0;
    goto if_next_24;
else_26:;
    if_7 = 0;
    goto if_next_24;
if_next_24:;
    return 0;
}

struct UnitConstPtrIntTuple2 init_2(int len_8, struct IntUnitFun1 f_) {
    struct UnitConstPtrIntTuple2 if_8;
    if ((0 >= len_8)) {
        goto then_28;
    } else {
        goto else_29;
    }
then_28:;
    milone_assert((len_8 == 0), 21, 4);
    struct UnitConstPtrIntTuple2 call_17 = empty_4(0);
    if_8 = call_17;
    goto if_next_27;
else_29:;
    struct UnitMutPtrIntTuple2 call_18 = __mutArrayCreate_2(len_8);
    struct UnitMutPtrIntTuple2 array_7 = call_18;
    int call_19 = arrayInitLoop_2(len_8, f_, array_7, 0);
    struct UnitConstPtrIntTuple2 call_20 = __constArrayOfMut_2(array_7);
    if_8 = call_20;
    goto if_next_27;
if_next_27:;
    return if_8;
}

struct IntConstPtrIntTuple2 init_1(int len_8, struct IntIntFun1 f_) {
    struct IntConstPtrIntTuple2 if_9;
    if ((0 >= len_8)) {
        goto then_31;
    } else {
        goto else_32;
    }
then_31:;
    milone_assert((len_8 == 0), 21, 4);
    struct IntConstPtrIntTuple2 call_21 = empty_3(0);
    if_9 = call_21;
    goto if_next_30;
else_32:;
    struct IntMutPtrIntTuple2 call_22 = __mutArrayCreate_1(len_8);
    struct IntMutPtrIntTuple2 array_7 = call_22;
    int call_23 = arrayInitLoop_1(len_8, f_, array_7, 0);
    struct IntConstPtrIntTuple2 call_24 = __constArrayOfMut_1(array_7);
    if_9 = call_24;
    goto if_next_30;
if_next_30:;
    return if_9;
}

int fun_8(int i_5) {
    return i_5;
}

int fun_13(void const* env_1, int arg_2) {
    int call_25 = fun_8(arg_2);
    return call_25;
}

struct IntConstPtrIntTuple2 range_(int len_10) {
    void const* box_ = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_))) = 0;
    void const* env_12 = box_;
    struct IntIntFun1 fun_26 = (struct IntIntFun1){.fun = fun_13, .env = env_12};
    struct IntConstPtrIntTuple2 call_26 = init_1(len_10, fun_26);
    return call_26;
}

int length_2(struct UnitConstPtrIntTuple2 array_8) {
    int call_27 = __constArrayLength_2(array_8);
    return call_27;
}

int length_1(struct IntConstPtrIntTuple2 array_8) {
    int call_28 = __constArrayLength_1(array_8);
    return call_28;
}

struct IntList {
    int head;
    struct IntList const* tail;
};

struct IntList const* tryItem_1(int i_6, struct IntConstPtrIntTuple2 array_10) {
    int call_29 = length_1(array_10);
    struct IntList const* if_10;
    if ((((uint32_t)i_6) < ((uint32_t)call_29))) {
        goto then_34;
    } else {
        goto else_35;
    }
then_34:;
    int call_30 = __constArrayGet_1(i_6, array_10);
    struct IntList const* some_ = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)some_))) = (struct IntList){.head = call_30, .tail = NULL};
    if_10 = some_;
    goto if_next_33;
else_35:;
    if_10 = NULL;
    goto if_next_33;
if_next_33:;
    return if_10;
}

struct IntConstPtrIntTuple2 slice_1(int start_2, int endIndex_2, struct IntConstPtrIntTuple2 array_11) {
    int call_31 = length_1(array_11);
    int len_11 = call_31;
    int if_11;
    if ((start_2 >= 0)) {
        goto then_37;
    } else {
        goto else_38;
    }
then_37:;
    if_11 = start_2;
    goto if_next_36;
else_38:;
    if_11 = 0;
    goto if_next_36;
if_next_36:;
    int start_3 = if_11;
    int if_12;
    if ((endIndex_2 < len_11)) {
        goto then_40;
    } else {
        goto else_41;
    }
then_40:;
    if_12 = endIndex_2;
    goto if_next_39;
else_41:;
    if_12 = len_11;
    goto if_next_39;
if_next_39:;
    int endIndex_3 = if_12;
    struct IntConstPtrIntTuple2 if_13;
    if ((start_3 < endIndex_3)) {
        goto then_43;
    } else {
        goto else_44;
    }
then_43:;
    struct IntConstPtrIntTuple2 call_32 = __constArraySlice_1(start_3, endIndex_3, array_11);
    if_13 = call_32;
    goto if_next_42;
else_44:;
    struct IntConstPtrIntTuple2 call_33 = empty_3(0);
    if_13 = call_33;
    goto if_next_42;
if_next_42:;
    return if_13;
}

struct IntConstPtrIntTuple2 skip_1(int skipLen_, struct IntConstPtrIntTuple2 array_12) {
    int call_34 = length_1(array_12);
    struct IntConstPtrIntTuple2 call_35 = slice_1(skipLen_, call_34, array_12);
    return call_35;
}

struct IntIntConstPtrIntTuple2Tuple2 {
    int t0;
    struct IntConstPtrIntTuple2 t1;
};

struct IntIntConstPtrIntTuple2Tuple2List {
    struct IntIntConstPtrIntTuple2Tuple2 head;
    struct IntIntConstPtrIntTuple2Tuple2List const* tail;
};

struct IntIntConstPtrIntTuple2Tuple2List const* uncons_1(struct IntConstPtrIntTuple2 array_15) {
    int call_36 = length_1(array_15);
    int len_12 = call_36;
    struct IntIntConstPtrIntTuple2Tuple2List const* if_14;
    if ((len_12 == 0)) {
        goto then_46;
    } else {
        goto else_47;
    }
then_46:;
    if_14 = NULL;
    goto if_next_45;
else_47:;
    int call_37 = __constArrayGet_1(0, array_15);
    int head_ = call_37;
    struct IntConstPtrIntTuple2 call_38 = __constArraySlice_1(1, len_12, array_15);
    struct IntConstPtrIntTuple2 tail_ = call_38;
    struct IntIntConstPtrIntTuple2Tuple2 tuple_8;
    tuple_8.t0 = head_;
    tuple_8.t1 = tail_;
    struct IntIntConstPtrIntTuple2Tuple2List const* some_1 = milone_mem_alloc(1, sizeof(struct IntIntConstPtrIntTuple2Tuple2List));
    (*(((struct IntIntConstPtrIntTuple2Tuple2List*)some_1))) = (struct IntIntConstPtrIntTuple2Tuple2List){.head = tuple_8, .tail = NULL};
    if_14 = some_1;
    goto if_next_45;
if_next_45:;
    return if_14;
}

struct IntIntIntFun2 {
    int(*fun)(void const*, int, int);
    void const* env;
};

int fun_25(struct IntIntIntFun2 f_1, struct IntConstPtrIntTuple2 array_16, int i_7) {
    int call_39 = __constArrayGet_1(i_7, array_16);
    int app_2 = f_1.fun(f_1.env, i_7, call_39);
    return app_2;
}

struct IntIntIntFun2IntConstPtrIntTuple2Tuple2 {
    struct IntIntIntFun2 t0;
    struct IntConstPtrIntTuple2 t1;
};

int fun_24(void const* env_2, int arg_3) {
    struct IntIntIntFun2 arg_4 = (*(((struct IntIntIntFun2IntConstPtrIntTuple2Tuple2 const*)env_2))).t0;
    struct IntConstPtrIntTuple2 arg_5 = (*(((struct IntIntIntFun2IntConstPtrIntTuple2Tuple2 const*)env_2))).t1;
    int call_40 = fun_25(arg_4, arg_5, arg_3);
    return call_40;
}

struct IntConstPtrIntTuple2 mapi_1(struct IntIntIntFun2 f_1, struct IntConstPtrIntTuple2 array_16) {
    int call_41 = length_1(array_16);
    struct IntIntIntFun2IntConstPtrIntTuple2Tuple2 tuple_9;
    tuple_9.t0 = f_1;
    tuple_9.t1 = array_16;
    void const* box_1 = milone_mem_alloc(1, sizeof(struct IntIntIntFun2IntConstPtrIntTuple2Tuple2));
    (*(((struct IntIntIntFun2IntConstPtrIntTuple2Tuple2*)box_1))) = tuple_9;
    void const* env_13 = box_1;
    struct IntIntFun1 fun_27 = (struct IntIntFun1){.fun = fun_24, .env = env_13};
    struct IntConstPtrIntTuple2 call_42 = init_1(call_41, fun_27);
    return call_42;
}

struct IntIntListFun1 {
    struct IntList const*(*fun)(void const*, int);
    void const* env;
};

int chooseLoop_1(struct IntIntListFun1 f_3, struct IntConstPtrIntTuple2 src_1, int len_13, struct IntMutPtrIntTuple2 dest_1, int di_, int si_) {
tailrec_48:;
    int if_15;
    if ((si_ == len_13)) {
        goto then_50;
    } else {
        goto else_51;
    }
then_50:;
    if_15 = di_;
    goto if_next_49;
else_51:;
    int match_;
    int call_43 = __constArrayGet_1(si_, src_1);
    struct IntList const* app_3 = f_3.fun(f_3.env, call_43);
    if ((!(app_3))) goto next_53;
    int value_1 = app_3->head;
    int call_44 = __mutArraySet_1(di_, value_1, dest_1);
    struct IntIntListFun1 arg_30 = f_3;
    struct IntConstPtrIntTuple2 arg_31 = src_1;
    int arg_32 = len_13;
    struct IntMutPtrIntTuple2 arg_33 = dest_1;
    int arg_34 = (di_ + 1);
    int arg_35 = (si_ + 1);
    f_3 = arg_30;
    src_1 = arg_31;
    len_13 = arg_32;
    dest_1 = arg_33;
    di_ = arg_34;
    si_ = arg_35;
    goto tailrec_48;
    match_ = 0;
    goto end_match_52;
next_53:;
    if ((!((!(app_3))))) goto next_54;
    struct IntIntListFun1 arg_36 = f_3;
    struct IntConstPtrIntTuple2 arg_37 = src_1;
    int arg_38 = len_13;
    struct IntMutPtrIntTuple2 arg_39 = dest_1;
    int arg_40 = di_;
    int arg_41 = (si_ + 1);
    f_3 = arg_36;
    src_1 = arg_37;
    len_13 = arg_38;
    dest_1 = arg_39;
    di_ = arg_40;
    si_ = arg_41;
    goto tailrec_48;
    match_ = 0;
    goto end_match_52;
next_54:;
    exit(1);
end_match_52:;
    if_15 = match_;
    goto if_next_49;
if_next_49:;
    return if_15;
}

struct IntConstPtrIntTuple2 choose_1(struct IntIntListFun1 f_3, struct IntConstPtrIntTuple2 src_1) {
    int call_45 = length_1(src_1);
    int len_13 = call_45;
    struct IntMutPtrIntTuple2 call_46 = __mutArrayCreate_1(len_13);
    struct IntMutPtrIntTuple2 dest_1 = call_46;
    int call_47 = chooseLoop_1(f_3, src_1, len_13, dest_1, 0, 0);
    int di_1 = call_47;
    struct IntConstPtrIntTuple2 if_16;
    if ((di_1 == 0)) {
        goto then_56;
    } else {
        goto else_57;
    }
then_56:;
    struct IntConstPtrIntTuple2 call_48 = empty_3(0);
    if_16 = call_48;
    goto if_next_55;
else_57:;
    struct IntMutPtrIntTuple2 call_49 = __mutArraySlice_1(0, di_1, dest_1);
    struct IntConstPtrIntTuple2 call_50 = __constArrayOfMut_1(call_49);
    if_16 = call_50;
    goto if_next_55;
if_next_55:;
    return if_16;
}

int arrayFoldLoop_1(struct IntIntIntFun2 folder_, struct IntConstPtrIntTuple2 array_18, int len_14, int state_2, int i_9) {
tailrec_58:;
    int if_17;
    if ((i_9 == len_14)) {
        goto then_60;
    } else {
        goto else_61;
    }
then_60:;
    if_17 = state_2;
    goto if_next_59;
else_61:;
    struct IntIntIntFun2 arg_42 = folder_;
    struct IntConstPtrIntTuple2 arg_43 = array_18;
    int arg_44 = len_14;
    int call_51 = __constArrayGet_1(i_9, array_18);
    int app_4 = folder_.fun(folder_.env, state_2, call_51);
    int arg_45 = app_4;
    int arg_46 = (i_9 + 1);
    folder_ = arg_42;
    array_18 = arg_43;
    len_14 = arg_44;
    state_2 = arg_45;
    i_9 = arg_46;
    goto tailrec_58;
    if_17 = 0;
    goto if_next_59;
if_next_59:;
    return if_17;
}

int fold_1(struct IntIntIntFun2 folder_, int state_1, struct IntConstPtrIntTuple2 array_18) {
    int call_52 = length_1(array_18);
    int len_14 = call_52;
    int call_53 = arrayFoldLoop_1(folder_, array_18, len_14, state_1, 0);
    return call_53;
}

int listLengthLoop_1(int acc_, struct IntList const* xs_2) {
tailrec_62:;
    int match_1;
    if ((!((!(xs_2))))) goto next_64;
    match_1 = acc_;
    goto end_match_63;
next_64:;
    if ((!(xs_2))) goto next_65;
    struct IntList const* xs_3 = xs_2->tail;
    int arg_47 = (acc_ + 1);
    struct IntList const* arg_48 = xs_3;
    acc_ = arg_47;
    xs_2 = arg_48;
    goto tailrec_62;
    match_1 = 0;
    goto end_match_63;
next_65:;
    exit(1);
end_match_63:;
    return match_1;
}

int ofListLoop_1(int len_15, struct IntMutPtrIntTuple2 dest_2, int i_10, struct IntList const* xs_4) {
tailrec_66:;
    int match_2;
    if ((!((!(xs_4))))) goto next_68;
    milone_assert((i_10 == len_15), 159, 12);
    match_2 = 0;
    goto end_match_67;
next_68:;
    if ((!(xs_4))) goto next_69;
    int x_ = xs_4->head;
    struct IntList const* xs_5 = xs_4->tail;
    int call_54 = __mutArraySet_1(i_10, x_, dest_2);
    int arg_49 = len_15;
    struct IntMutPtrIntTuple2 arg_50 = dest_2;
    int arg_51 = (i_10 + 1);
    struct IntList const* arg_52 = xs_5;
    len_15 = arg_49;
    dest_2 = arg_50;
    i_10 = arg_51;
    xs_4 = arg_52;
    goto tailrec_66;
    match_2 = 0;
    goto end_match_67;
next_69:;
    exit(1);
end_match_67:;
    return 0;
}

struct IntConstPtrIntTuple2 ofList_1(struct IntList const* xs_1) {
    int call_55 = listLengthLoop_1(0, xs_1);
    int len_15 = call_55;
    struct IntMutPtrIntTuple2 call_56 = __mutArrayCreate_1(len_15);
    struct IntMutPtrIntTuple2 dest_2 = call_56;
    int call_57 = ofListLoop_1(len_15, dest_2, 0, xs_1);
    struct IntConstPtrIntTuple2 call_58 = __constArrayOfMut_1(dest_2);
    return call_58;
}

struct IntList const* toListLoop_1(struct IntConstPtrIntTuple2 array_19, struct IntList const* acc_1, int i_11) {
tailrec_70:;
    struct IntList const* if_18;
    if ((i_11 == 0)) {
        goto then_72;
    } else {
        goto else_73;
    }
then_72:;
    if_18 = acc_1;
    goto if_next_71;
else_73:;
    struct IntConstPtrIntTuple2 arg_53 = array_19;
    int call_59 = __constArrayGet_1((i_11 - 1), array_19);
    struct IntList const* list_ = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_))) = (struct IntList){.head = call_59, .tail = acc_1};
    struct IntList const* arg_54 = list_;
    int arg_55 = (i_11 - 1);
    array_19 = arg_53;
    acc_1 = arg_54;
    i_11 = arg_55;
    goto tailrec_70;
    if_18 = NULL;
    goto if_next_71;
if_next_71:;
    return if_18;
}

struct IntList const* toList_1(struct IntConstPtrIntTuple2 array_19) {
    int call_60 = length_1(array_19);
    struct IntList const* call_61 = toListLoop_1(array_19, NULL, call_60);
    return call_61;
}

int get_1(int i_, struct IntConstPtrIntTuple2 array_5) {
    int match_3;
    struct IntList const* call_62 = tryItem_1(i_, array_5);
    if ((!(call_62))) goto next_75;
    int it_ = call_62->head;
    match_3 = it_;
    goto end_match_74;
next_75:;
    if ((!((!(call_62))))) goto next_76;
    int call_63 = length_1(array_5);
    printf("out of range: i=%d len=%d\n", i_, call_63);
    milone_assert(false, 9, 6);
    exit(1);
    match_3 = 0;
    goto end_match_74;
next_76:;
    exit(1);
end_match_74:;
    return match_3;
}

int fun_(int arg_56) {
    milone_assert(false, 13, 45);
    return 0;
}

int fun_17(void const* env_5, int arg_11) {
    int call_64 = fun_(arg_11);
    return 0;
}

int fun_1(int n_) {
    return ((n_ + 1) * 3);
}

int fun_18(void const* env_6, int arg_12) {
    int call_65 = fun_1(arg_12);
    return call_65;
}

int initTest_(int arg_57) {
    void const* box_2 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_2))) = 0;
    void const* env_14 = box_2;
    struct IntUnitFun1 fun_28 = (struct IntUnitFun1){.fun = fun_17, .env = env_14};
    struct UnitConstPtrIntTuple2 call_66 = init_2(0, fun_28);
    struct UnitConstPtrIntTuple2 emptyArray_ = call_66;
    int call_67 = length_2(emptyArray_);
    milone_assert((call_67 == 0), 14, 2);
    void const* box_3 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_3))) = 0;
    void const* env_15 = box_3;
    struct IntIntFun1 fun_29 = (struct IntIntFun1){.fun = fun_18, .env = env_15};
    struct IntConstPtrIntTuple2 call_68 = init_1(3, fun_29);
    struct IntConstPtrIntTuple2 a369_ = call_68;
    int call_69 = length_1(a369_);
    milone_assert((call_69 == 3), 17, 2);
    int call_70 = get_1(0, a369_);
    milone_assert((call_70 == 3), 18, 2);
    int call_71 = get_1(1, a369_);
    milone_assert((call_71 == 6), 19, 2);
    int call_72 = get_1(2, a369_);
    milone_assert((call_72 == 9), 20, 2);
    return 0;
}

int rangeTest_(int arg_58) {
    struct IntConstPtrIntTuple2 call_73 = range_(3);
    struct IntConstPtrIntTuple2 a012_ = call_73;
    int call_74 = length_1(a012_);
    milone_assert((call_74 == 3), 25, 2);
    int call_75 = get_1(0, a012_);
    milone_assert((call_75 == 0), 26, 2);
    int call_76 = get_1(1, a012_);
    milone_assert((call_76 == 1), 27, 2);
    int call_77 = get_1(2, a012_);
    milone_assert((call_77 == 2), 28, 2);
    return 0;
}

int at_(int bad_, int i_1, struct IntConstPtrIntTuple2 array_6) {
    int match_4;
    struct IntList const* call_78 = tryItem_1(i_1, array_6);
    if ((!(call_78))) goto next_78;
    int it_1 = call_78->head;
    match_4 = it_1;
    goto end_match_77;
next_78:;
    if ((!((!(call_78))))) goto next_79;
    match_4 = bad_;
    goto end_match_77;
next_79:;
    exit(1);
end_match_77:;
    return match_4;
}

int tryItemTest_(int arg_59) {
    struct IntConstPtrIntTuple2 call_79 = range_(3);
    struct IntConstPtrIntTuple2 a012_1 = call_79;
    int bad_ = -127;
    int call_80 = at_(bad_, -1, a012_1);
    milone_assert((call_80 == bad_), 40, 2);
    int call_81 = at_(bad_, 0, a012_1);
    milone_assert((call_81 == 0), 41, 2);
    int call_82 = at_(bad_, 2, a012_1);
    milone_assert((call_82 == 2), 42, 2);
    int call_83 = at_(bad_, 3, a012_1);
    milone_assert((call_83 == bad_), 43, 2);
    struct IntConstPtrIntTuple2 call_84 = empty_3(0);
    struct IntConstPtrIntTuple2 emptyArray_1 = call_84;
    int call_85 = at_(bad_, 0, emptyArray_1);
    milone_assert((call_85 == bad_), 46, 2);
    return 0;
}

int sliceTest_(int arg_60) {
    struct IntConstPtrIntTuple2 call_86 = range_(10);
    struct IntConstPtrIntTuple2 ten_ = call_86;
    struct IntConstPtrIntTuple2 call_87 = slice_1(1, 3, ten_);
    struct IntConstPtrIntTuple2 three_ = call_87;
    int call_88 = length_1(three_);
    milone_assert((call_88 == 3), 52, 2);
    int call_89 = get_1(0, three_);
    milone_assert((call_89 == 1), 53, 2);
    int call_90 = get_1(2, three_);
    milone_assert((call_90 == 3), 54, 2);
    struct IntConstPtrIntTuple2 call_91 = slice_1(-1, 2, ten_);
    struct IntConstPtrIntTuple2 behind_ = call_91;
    int call_92 = length_1(behind_);
    milone_assert((call_92 == 2), 57, 2);
    int call_93 = get_1(1, behind_);
    milone_assert((call_93 == 1), 58, 2);
    struct IntConstPtrIntTuple2 call_94 = slice_1(7, 11, ten_);
    struct IntConstPtrIntTuple2 beyond_ = call_94;
    int call_95 = length_1(beyond_);
    milone_assert((call_95 == 3), 61, 2);
    int call_96 = get_1(0, beyond_);
    milone_assert((call_96 == 7), 62, 2);
    int call_97 = get_1(2, beyond_);
    milone_assert((call_97 == 9), 63, 2);
    return 0;
}

int fun_2(int n_1) {
    return (n_1 + 1);
}

int fun_19(void const* env_7, int arg_13) {
    int call_98 = fun_2(arg_13);
    return call_98;
}

int unconsTest_(int arg_61) {
    void const* box_4 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_4))) = 0;
    void const* env_16 = box_4;
    struct IntIntFun1 fun_30 = (struct IntIntFun1){.fun = fun_19, .env = env_16};
    struct IntConstPtrIntTuple2 call_99 = init_1(3, fun_30);
    struct IntConstPtrIntTuple2 a123_ = call_99;
    int match_5;
    struct IntIntConstPtrIntTuple2Tuple2List const* call_100 = uncons_1(a123_);
    if ((!((!(call_100))))) goto next_81;
    milone_assert(false, 68, 12);
    match_5 = 0;
    goto end_match_80;
next_81:;
    if ((!(call_100))) goto next_82;
    int n1_ = call_100->head.t0;
    struct IntConstPtrIntTuple2 a23_ = call_100->head.t1;
    milone_assert((n1_ == 1), 70, 6);
    int call_101 = length_1(a23_);
    milone_assert((call_101 == 2), 71, 6);
    int match_6;
    struct IntConstPtrIntTuple2 call_102 = skip_1(1, a23_);
    struct IntIntConstPtrIntTuple2Tuple2List const* call_103 = uncons_1(call_102);
    if ((!((!(call_103))))) goto next_84;
    milone_assert(false, 74, 16);
    match_6 = 0;
    goto end_match_83;
next_84:;
    if ((!(call_103))) goto next_85;
    int n3_ = call_103->head.t0;
    struct IntConstPtrIntTuple2 empty_ = call_103->head.t1;
    milone_assert((n3_ == 3), 76, 10);
    int call_104 = length_1(empty_);
    milone_assert((call_104 == 0), 77, 10);
    int match_7;
    struct IntIntConstPtrIntTuple2Tuple2List const* call_105 = uncons_1(empty_);
    if ((!((!(call_105))))) goto next_87;
    match_7 = 0;
    goto end_match_86;
next_87:;
    if ((!(call_105))) goto next_88;
    milone_assert(false, 81, 22);
    match_7 = 0;
    goto end_match_86;
next_88:;
    exit(1);
end_match_86:;
    match_6 = 0;
    goto end_match_83;
next_85:;
    exit(1);
end_match_83:;
    match_5 = 0;
    goto end_match_80;
next_82:;
    exit(1);
end_match_80:;
    return 0;
}

int fun_3(int i_2, int n_2) {
    return ((i_2 * 10) + n_2);
}

int fun_20(void const* env_8, int arg_14, int arg_15) {
    int call_106 = fun_3(arg_14, arg_15);
    return call_106;
}

int mapTest_(int arg_62) {
    void const* box_5 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_5))) = 0;
    void const* env_17 = box_5;
    struct IntIntIntFun2 fun_31 = (struct IntIntIntFun2){.fun = fun_20, .env = env_17};
    struct IntConstPtrIntTuple2 call_107 = range_(3);
    struct IntConstPtrIntTuple2 call_108 = mapi_1(fun_31, call_107);
    struct IntConstPtrIntTuple2 mapped_ = call_108;
    int call_109 = length_1(mapped_);
    milone_assert((call_109 == 3), 87, 2);
    int call_110 = get_1(0, mapped_);
    milone_assert((call_110 == 0), 88, 2);
    int call_111 = get_1(1, mapped_);
    milone_assert((call_111 == 11), 89, 2);
    int call_112 = get_1(2, mapped_);
    milone_assert((call_112 == 22), 90, 2);
    return 0;
}

struct IntList const* fun_4(int n_3) {
    struct IntList const* if_19;
    if (((n_3 % 2) == 0)) {
        goto then_90;
    } else {
        goto else_91;
    }
then_90:;
    struct IntList const* some_2 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)some_2))) = (struct IntList){.head = (n_3 * 2), .tail = NULL};
    if_19 = some_2;
    goto if_next_89;
else_91:;
    if_19 = NULL;
    goto if_next_89;
if_next_89:;
    return if_19;
}

struct IntList const* fun_21(void const* env_9, int arg_16) {
    struct IntList const* call_113 = fun_4(arg_16);
    return call_113;
}

struct IntList const* fun_5(int arg_63) {
    return NULL;
}

struct IntList const* fun_22(void const* env_10, int arg_17) {
    struct IntList const* call_114 = fun_5(arg_17);
    return call_114;
}

int chooseTest_(int arg_64) {
    void const* box_6 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_6))) = 0;
    void const* env_18 = box_6;
    struct IntIntListFun1 fun_32 = (struct IntIntListFun1){.fun = fun_21, .env = env_18};
    struct IntConstPtrIntTuple2 call_115 = range_(6);
    struct IntConstPtrIntTuple2 call_116 = choose_1(fun_32, call_115);
    struct IntConstPtrIntTuple2 chosen_ = call_116;
    int call_117 = length_1(chosen_);
    milone_assert((call_117 == 3), 96, 2);
    int call_118 = get_1(0, chosen_);
    milone_assert((call_118 == 0), 97, 2);
    int call_119 = get_1(1, chosen_);
    milone_assert((call_119 == 4), 98, 2);
    int call_120 = get_1(2, chosen_);
    milone_assert((call_120 == 8), 99, 2);
    void const* box_7 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_7))) = 0;
    void const* env_19 = box_7;
    struct IntIntListFun1 fun_33 = (struct IntIntListFun1){.fun = fun_22, .env = env_19};
    struct IntConstPtrIntTuple2 call_121 = range_(3);
    struct IntConstPtrIntTuple2 call_122 = choose_1(fun_33, call_121);
    struct IntConstPtrIntTuple2 empty_1 = call_122;
    int call_123 = length_1(empty_1);
    milone_assert((call_123 == 0), 104, 2);
    return 0;
}

int fun_6(int state_, int i_3) {
    return ((state_ * 10) + (i_3 + 1));
}

int fun_23(void const* env_11, int arg_18, int arg_19) {
    int call_124 = fun_6(arg_18, arg_19);
    return call_124;
}

int foldTest_(int arg_65) {
    void const* box_8 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_8))) = 0;
    void const* env_20 = box_8;
    struct IntIntIntFun2 fun_34 = (struct IntIntIntFun2){.fun = fun_23, .env = env_20};
    struct IntConstPtrIntTuple2 call_125 = range_(3);
    int call_126 = fold_1(fun_34, 0, call_125);
    int sum_ = call_126;
    milone_assert((sum_ == 123), 110, 2);
    return 0;
}

int ofListTest_(int arg_66) {
    struct IntList const* list_3 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_3))) = (struct IntList){.head = 5, .tail = NULL};
    struct IntList const* list_2 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_2))) = (struct IntList){.head = 3, .tail = list_3};
    struct IntList const* list_1 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_1))) = (struct IntList){.head = 2, .tail = list_2};
    struct IntConstPtrIntTuple2 call_127 = ofList_1(list_1);
    struct IntConstPtrIntTuple2 ol_ = call_127;
    int call_128 = length_1(ol_);
    milone_assert((call_128 == 3), 123, 2);
    int call_129 = get_1(0, ol_);
    milone_assert((call_129 == 2), 124, 2);
    int call_130 = get_1(1, ol_);
    milone_assert((call_130 == 3), 125, 2);
    int call_131 = get_1(2, ol_);
    milone_assert((call_131 == 5), 126, 2);
    return 0;
}

int toListTest_(int arg_67) {
    struct IntConstPtrIntTuple2 call_132 = range_(3);
    struct IntList const* call_133 = toList_1(call_132);
    struct IntList const* tl_ = call_133;
    int match_8;
    if ((!(tl_))) goto next_93;
    int n0_ = tl_->head;
    if ((!(tl_->tail))) goto next_93;
    int n1_1 = tl_->tail->head;
    if ((!(tl_->tail->tail))) goto next_93;
    int n2_ = tl_->tail->tail->head;
    if ((!((!(tl_->tail->tail->tail))))) goto next_93;
    milone_assert((n0_ == 0), 133, 6);
    milone_assert((n1_1 == 1), 134, 6);
    milone_assert((n2_ == 2), 135, 6);
    match_8 = 0;
    goto end_match_92;
next_93:;
    match_8 = 0;
    goto end_match_92;
next_94:;
end_match_92:;
    return 0;
}

int main() {
    int call_134 = initTest_(0);
    int call_135 = rangeTest_(0);
    int call_136 = tryItemTest_(0);
    int call_137 = unconsTest_(0);
    int call_138 = mapTest_(0);
    int call_139 = chooseTest_(0);
    int call_140 = foldTest_(0);
    int call_141 = ofListTest_(0);
    int call_142 = toListTest_(0);
    return 0;
}
