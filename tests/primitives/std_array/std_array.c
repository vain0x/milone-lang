#include "milone.h"

struct StringList;

struct String str_concat(struct String, struct StringList const*);

struct String __stringJoin_(struct String sep_, struct StringList const* xs_5);

intptr_t __pointeeSize_2(int const* constPtr_);

intptr_t __pointeeSize_1(int const* constPtr_);

int const* __ptrAsConst_1(int* mutPtr_);

int const* __ptrAsConst_2(int* mutPtr_);

int const* __ptrAdd_1(int index_1, int const* ptr_);

int* __mutPtrAdd_1(int index_2, int* mutPtr_1);

void* milone_mem_alloc(int, uintptr_t);

void* memAlloc_(int len_8, uintptr_t size_);

void* memcpy(void*, void const*, uintptr_t);

void* memcpy_(void* dest_2, void const* src_2, uintptr_t size_1);

struct UnitMutPtrIntTuple2;

struct UnitMutPtrIntTuple2 __mutArrayCreate_2(int len_9);

struct IntMutPtrIntTuple2;

struct IntMutPtrIntTuple2 __mutArrayCreate_1(int len_9);

int __mutArraySet_2(int index_3, int value_1, struct UnitMutPtrIntTuple2 array_15);

int __mutArraySet_1(int index_3, int value_1, struct IntMutPtrIntTuple2 array_15);

struct IntMutPtrIntTuple2 __mutArraySlice_1(int start_2, int endIndex_2, struct IntMutPtrIntTuple2 array_16);

struct UnitConstPtrIntTuple2;

struct UnitConstPtrIntTuple2 __constArrayOfMut_2(struct UnitMutPtrIntTuple2 mutArray_);

struct IntConstPtrIntTuple2;

struct IntConstPtrIntTuple2 __constArrayOfMut_1(struct IntMutPtrIntTuple2 mutArray_);

int __constArrayLength_2(struct UnitConstPtrIntTuple2 array_17);

int __constArrayLength_1(struct IntConstPtrIntTuple2 array_17);

int __constArrayGet_1(int index_4, struct IntConstPtrIntTuple2 array_18);

struct IntConstPtrIntTuple2 __constArraySlice_1(int start_3, int endIndex_3, struct IntConstPtrIntTuple2 array_19);

bool str_to_int_checked(struct String, int*);

struct IntList;

struct IntList const* __intOfStr_(struct String s_);

int milone_get_arg_count();

int __argCount_(int arg_20);

struct String milone_get_arg(int);

struct String __argGet_(int index_5);

struct IntConstPtrIntTuple2 empty_3(int arg_21);

struct UnitConstPtrIntTuple2 empty_4(int arg_22);

struct IntUnitFun1;

int arrayInitLoop_2(int len_, struct IntUnitFun1 f_, struct UnitMutPtrIntTuple2 array_2, int i_4);

struct IntIntFun1;

int arrayInitLoop_1(int len_, struct IntIntFun1 f_, struct IntMutPtrIntTuple2 array_2, int i_4);

struct UnitConstPtrIntTuple2 init_2(int len_, struct IntUnitFun1 f_);

struct IntConstPtrIntTuple2 init_1(int len_, struct IntIntFun1 f_);

int fun_8(int i_5);

int fun_13(void const* env_1, int arg_2);

struct IntConstPtrIntTuple2 range_(int len_2);

int length_2(struct UnitConstPtrIntTuple2 array_3);

int length_1(struct IntConstPtrIntTuple2 array_3);

struct IntList const* tryItem_1(int i_6, struct IntConstPtrIntTuple2 array_5);

struct IntConstPtrIntTuple2 slice_1(int start_, int endIndex_, struct IntConstPtrIntTuple2 array_6);

struct IntConstPtrIntTuple2 skip_1(int skipLen_, struct IntConstPtrIntTuple2 array_7);

struct IntIntConstPtrIntTuple2Tuple2;

struct IntIntConstPtrIntTuple2Tuple2List;

struct IntIntConstPtrIntTuple2Tuple2List const* uncons_1(struct IntConstPtrIntTuple2 array_10);

struct IntIntIntFun2;

int fun_25(struct IntIntIntFun2 f_1, struct IntConstPtrIntTuple2 array_11, int i_7);

struct IntIntIntFun2IntConstPtrIntTuple2Tuple2;

int fun_24(void const* env_2, int arg_3);

struct IntConstPtrIntTuple2 mapi_1(struct IntIntIntFun2 f_1, struct IntConstPtrIntTuple2 array_11);

struct IntIntListFun1;

int chooseLoop_1(struct IntIntListFun1 f_3, struct IntConstPtrIntTuple2 src_, int len_5, struct IntMutPtrIntTuple2 dest_, int di_, int si_);

struct IntConstPtrIntTuple2 choose_1(struct IntIntListFun1 f_3, struct IntConstPtrIntTuple2 src_);

int arrayFoldLoop_1(struct IntIntIntFun2 folder_, struct IntConstPtrIntTuple2 array_13, int len_6, int state_2, int i_9);

int fold_1(struct IntIntIntFun2 folder_, int state_1, struct IntConstPtrIntTuple2 array_13);

int listLengthLoop_1(int acc_, struct IntList const* xs_1);

int ofListLoop_1(int len_7, struct IntMutPtrIntTuple2 dest_1, int i_10, struct IntList const* xs_3);

struct IntConstPtrIntTuple2 ofList_1(struct IntList const* xs_);

struct IntList const* toListLoop_1(struct IntConstPtrIntTuple2 array_14, struct IntList const* acc_1, int i_11);

struct IntList const* toList_1(struct IntConstPtrIntTuple2 array_14);

int get_1(int i_, struct IntConstPtrIntTuple2 array_);

int fun_(int arg_57);

int fun_17(void const* env_5, int arg_11);

int fun_1(int n_);

int fun_18(void const* env_6, int arg_12);

int initTest_(int arg_58);

int rangeTest_(int arg_59);

int at_(int bad_, int i_1, struct IntConstPtrIntTuple2 array_1);

int tryItemTest_(int arg_60);

int sliceTest_(int arg_61);

int fun_2(int n_1);

int fun_19(void const* env_7, int arg_13);

int unconsTest_(int arg_62);

int fun_3(int i_2, int n_2);

int fun_20(void const* env_8, int arg_14, int arg_15);

int mapTest_(int arg_63);

struct IntList const* fun_4(int n_3);

struct IntList const* fun_21(void const* env_9, int arg_16);

struct IntList const* fun_5(int arg_64);

struct IntList const* fun_22(void const* env_10, int arg_17);

int chooseTest_(int arg_65);

int fun_6(int state_, int i_3);

int fun_23(void const* env_11, int arg_18, int arg_19);

int foldTest_(int arg_66);

int ofListTest_(int arg_67);

int toListTest_(int arg_68);

int milone_main();

struct StringList {
    struct String head;
    struct StringList const* tail;
};

struct String __stringJoin_(struct String sep_, struct StringList const* xs_5) {
    struct String str_concat_result_ = str_concat(sep_, xs_5);
    return str_concat_result_;
}

intptr_t __pointeeSize_2(int const* constPtr_) {
    return ((intptr_t)sizeof(int));
}

intptr_t __pointeeSize_1(int const* constPtr_) {
    return ((intptr_t)sizeof(int));
}

int const* __ptrAsConst_1(int* mutPtr_) {
    return ((int const*)mutPtr_);
}

int const* __ptrAsConst_2(int* mutPtr_) {
    return ((int const*)mutPtr_);
}

int const* __ptrAdd_1(int index_1, int const* ptr_) {
    intptr_t call_ = __pointeeSize_1(ptr_);
    return ((int const*)(((intptr_t)ptr_) + (((intptr_t)index_1) * call_)));
}

int* __mutPtrAdd_1(int index_2, int* mutPtr_1) {
    int const* call_1 = __ptrAsConst_1(mutPtr_1);
    intptr_t call_2 = __pointeeSize_1(call_1);
    return ((int*)(((intptr_t)mutPtr_1) + (((intptr_t)index_2) * call_2)));
}

void* memAlloc_(int len_8, uintptr_t size_) {
    void* milone_mem_alloc_result_ = milone_mem_alloc(len_8, size_);
    return milone_mem_alloc_result_;
}

void* memcpy_(void* dest_2, void const* src_2, uintptr_t size_1) {
    void* memcpy_result_ = memcpy(dest_2, src_2, size_1);
    return memcpy_result_;
}

struct UnitMutPtrIntTuple2 {
    int* t0;
    int t1;
};

struct UnitMutPtrIntTuple2 __mutArrayCreate_2(int len_9) {
    struct UnitMutPtrIntTuple2 if_;
    if ((len_9 == 0)) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    struct UnitMutPtrIntTuple2 tuple_ = (struct UnitMutPtrIntTuple2){.t0 = ((int*)((uintptr_t)0)), .t1 = 0};
    if_ = tuple_;
    goto if_next_1;
else_3:;
    int const* nullPtr_ = ((int const*)((uintptr_t)0));
    intptr_t call_3 = __pointeeSize_2(nullPtr_);
    void* call_4 = memAlloc_(len_9, ((uintptr_t)call_3));
    int* ptr_1 = ((int*)call_4);
    struct UnitMutPtrIntTuple2 tuple_1 = (struct UnitMutPtrIntTuple2){.t0 = ptr_1, .t1 = len_9};
    if_ = tuple_1;
    goto if_next_1;
if_next_1:;
    return if_;
}

struct IntMutPtrIntTuple2 {
    int* t0;
    int t1;
};

struct IntMutPtrIntTuple2 __mutArrayCreate_1(int len_9) {
    struct IntMutPtrIntTuple2 if_1;
    if ((len_9 == 0)) {
        goto then_5;
    } else {
        goto else_6;
    }
then_5:;
    struct IntMutPtrIntTuple2 tuple_2 = (struct IntMutPtrIntTuple2){.t0 = ((int*)((uintptr_t)0)), .t1 = 0};
    if_1 = tuple_2;
    goto if_next_4;
else_6:;
    int const* nullPtr_ = ((int const*)((uintptr_t)0));
    intptr_t call_5 = __pointeeSize_1(nullPtr_);
    void* call_6 = memAlloc_(len_9, ((uintptr_t)call_5));
    int* ptr_1 = ((int*)call_6);
    struct IntMutPtrIntTuple2 tuple_3 = (struct IntMutPtrIntTuple2){.t0 = ptr_1, .t1 = len_9};
    if_1 = tuple_3;
    goto if_next_4;
if_next_4:;
    return if_1;
}

int __mutArraySet_2(int index_3, int value_1, struct UnitMutPtrIntTuple2 array_15) {
    int* mutPtr_2 = array_15.t0;
    int len_10 = array_15.t1;
    milone_assert((((uint32_t)index_3) < ((uint32_t)len_10)), 54, 2);
    mutPtr_2[index_3] = 0;
    return 0;
}

int __mutArraySet_1(int index_3, int value_1, struct IntMutPtrIntTuple2 array_15) {
    int* mutPtr_2 = array_15.t0;
    int len_10 = array_15.t1;
    milone_assert((((uint32_t)index_3) < ((uint32_t)len_10)), 54, 2);
    mutPtr_2[index_3] = value_1;
    return 0;
}

struct IntMutPtrIntTuple2 __mutArraySlice_1(int start_2, int endIndex_2, struct IntMutPtrIntTuple2 array_16) {
    int* mutPtr_3 = array_16.t0;
    int len_11 = array_16.t1;
    bool if_2;
    if ((start_2 >= 0)) {
        goto then_8;
    } else {
        goto else_9;
    }
then_8:;
    if_2 = (endIndex_2 >= start_2);
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
    if_3 = (len_11 >= endIndex_2);
    goto if_next_10;
else_12:;
    if_3 = false;
    goto if_next_10;
if_next_10:;
    milone_assert(if_3, 61, 2);
    int* call_7 = __mutPtrAdd_1(start_2, mutPtr_3);
    struct IntMutPtrIntTuple2 tuple_4 = (struct IntMutPtrIntTuple2){.t0 = call_7, .t1 = (endIndex_2 - start_2)};
    return tuple_4;
}

struct UnitConstPtrIntTuple2 {
    int const* t0;
    int t1;
};

struct UnitConstPtrIntTuple2 __constArrayOfMut_2(struct UnitMutPtrIntTuple2 mutArray_) {
    int* mutPtr_4 = mutArray_.t0;
    int len_12 = mutArray_.t1;
    int const* call_8 = __ptrAsConst_2(mutPtr_4);
    struct UnitConstPtrIntTuple2 tuple_5 = (struct UnitConstPtrIntTuple2){.t0 = call_8, .t1 = len_12};
    return tuple_5;
}

struct IntConstPtrIntTuple2 {
    int const* t0;
    int t1;
};

struct IntConstPtrIntTuple2 __constArrayOfMut_1(struct IntMutPtrIntTuple2 mutArray_) {
    int* mutPtr_4 = mutArray_.t0;
    int len_12 = mutArray_.t1;
    int const* call_9 = __ptrAsConst_1(mutPtr_4);
    struct IntConstPtrIntTuple2 tuple_6 = (struct IntConstPtrIntTuple2){.t0 = call_9, .t1 = len_12};
    return tuple_6;
}

int __constArrayLength_2(struct UnitConstPtrIntTuple2 array_17) {
    int len_13 = array_17.t1;
    return len_13;
}

int __constArrayLength_1(struct IntConstPtrIntTuple2 array_17) {
    int len_13 = array_17.t1;
    return len_13;
}

int __constArrayGet_1(int index_4, struct IntConstPtrIntTuple2 array_18) {
    int const* ptr_2 = array_18.t0;
    int len_14 = array_18.t1;
    milone_assert((((uint32_t)index_4) < ((uint32_t)len_14)), 81, 2);
    int read_ = ptr_2[index_4];
    return read_;
}

struct IntConstPtrIntTuple2 __constArraySlice_1(int start_3, int endIndex_3, struct IntConstPtrIntTuple2 array_19) {
    int const* ptr_3 = array_19.t0;
    int len_15 = array_19.t1;
    bool if_4;
    if ((start_3 >= 0)) {
        goto then_14;
    } else {
        goto else_15;
    }
then_14:;
    if_4 = (endIndex_3 >= start_3);
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
    if_5 = (len_15 >= endIndex_3);
    goto if_next_16;
else_18:;
    if_5 = false;
    goto if_next_16;
if_next_16:;
    milone_assert(if_5, 87, 2);
    int const* call_10 = __ptrAdd_1(start_3, ptr_3);
    struct IntConstPtrIntTuple2 tuple_7 = (struct IntConstPtrIntTuple2){.t0 = call_10, .t1 = (endIndex_3 - start_3)};
    return tuple_7;
}

struct IntList {
    int head;
    struct IntList const* tail;
};

struct IntList const* __intOfStr_(struct String s_) {
    void* call_11 = memAlloc_(1, ((uintptr_t)sizeof(int)));
    int* valueRef_ = ((int*)call_11);
    bool str_to_int_checked_result_ = str_to_int_checked(s_, valueRef_);
    bool ok_ = str_to_int_checked_result_;
    struct IntList const* if_6;
    if (ok_) {
        goto then_20;
    } else {
        goto else_21;
    }
then_20:;
    int const* call_12 = __ptrAsConst_1(valueRef_);
    int read_1 = (*(call_12));
    struct IntList const* some_ = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)some_))) = (struct IntList){.head = read_1, .tail = NULL};
    if_6 = some_;
    goto if_next_19;
else_21:;
    if_6 = NULL;
    goto if_next_19;
if_next_19:;
    return if_6;
}

int __argCount_(int arg_20) {
    int milone_get_arg_count_result_ = milone_get_arg_count();
    return milone_get_arg_count_result_;
}

struct String __argGet_(int index_5) {
    struct String milone_get_arg_result_ = milone_get_arg(index_5);
    return milone_get_arg_result_;
}

struct IntConstPtrIntTuple2 empty_3(int arg_21) {
    struct IntMutPtrIntTuple2 call_13 = __mutArrayCreate_1(0);
    struct IntConstPtrIntTuple2 call_14 = __constArrayOfMut_1(call_13);
    return call_14;
}

struct UnitConstPtrIntTuple2 empty_4(int arg_22) {
    struct UnitMutPtrIntTuple2 call_15 = __mutArrayCreate_2(0);
    struct UnitConstPtrIntTuple2 call_16 = __constArrayOfMut_2(call_15);
    return call_16;
}

struct IntUnitFun1 {
    int(*fun)(void const*, int);
    void const* env;
};

int arrayInitLoop_2(int len_, struct IntUnitFun1 f_, struct UnitMutPtrIntTuple2 array_2, int i_4) {
tailrec_22:;
    int if_7;
    if ((i_4 < len_)) {
        goto then_24;
    } else {
        goto else_25;
    }
then_24:;
    int app_ = f_.fun(f_.env, i_4);
    int item_ = 0;
    int call_17 = __mutArraySet_2(i_4, 0, array_2);
    int arg_23 = len_;
    struct IntUnitFun1 arg_24 = f_;
    struct UnitMutPtrIntTuple2 arg_25 = array_2;
    int arg_26 = (i_4 + 1);
    len_ = arg_23;
    f_ = arg_24;
    array_2 = arg_25;
    i_4 = arg_26;
    goto tailrec_22;
    if_7 = 0;
    goto if_next_23;
else_25:;
    if_7 = 0;
    goto if_next_23;
if_next_23:;
    return 0;
}

struct IntIntFun1 {
    int(*fun)(void const*, int);
    void const* env;
};

int arrayInitLoop_1(int len_, struct IntIntFun1 f_, struct IntMutPtrIntTuple2 array_2, int i_4) {
tailrec_26:;
    int if_8;
    if ((i_4 < len_)) {
        goto then_28;
    } else {
        goto else_29;
    }
then_28:;
    int app_1 = f_.fun(f_.env, i_4);
    int item_ = app_1;
    int call_18 = __mutArraySet_1(i_4, item_, array_2);
    int arg_27 = len_;
    struct IntIntFun1 arg_28 = f_;
    struct IntMutPtrIntTuple2 arg_29 = array_2;
    int arg_30 = (i_4 + 1);
    len_ = arg_27;
    f_ = arg_28;
    array_2 = arg_29;
    i_4 = arg_30;
    goto tailrec_26;
    if_8 = 0;
    goto if_next_27;
else_29:;
    if_8 = 0;
    goto if_next_27;
if_next_27:;
    return 0;
}

struct UnitConstPtrIntTuple2 init_2(int len_, struct IntUnitFun1 f_) {
    struct UnitConstPtrIntTuple2 if_9;
    if ((0 >= len_)) {
        goto then_31;
    } else {
        goto else_32;
    }
then_31:;
    milone_assert((len_ == 0), 24, 4);
    struct UnitConstPtrIntTuple2 call_19 = empty_4(0);
    if_9 = call_19;
    goto if_next_30;
else_32:;
    struct UnitMutPtrIntTuple2 call_20 = __mutArrayCreate_2(len_);
    struct UnitMutPtrIntTuple2 array_2 = call_20;
    int call_21 = arrayInitLoop_2(len_, f_, array_2, 0);
    struct UnitConstPtrIntTuple2 call_22 = __constArrayOfMut_2(array_2);
    if_9 = call_22;
    goto if_next_30;
if_next_30:;
    return if_9;
}

struct IntConstPtrIntTuple2 init_1(int len_, struct IntIntFun1 f_) {
    struct IntConstPtrIntTuple2 if_10;
    if ((0 >= len_)) {
        goto then_34;
    } else {
        goto else_35;
    }
then_34:;
    milone_assert((len_ == 0), 24, 4);
    struct IntConstPtrIntTuple2 call_23 = empty_3(0);
    if_10 = call_23;
    goto if_next_33;
else_35:;
    struct IntMutPtrIntTuple2 call_24 = __mutArrayCreate_1(len_);
    struct IntMutPtrIntTuple2 array_2 = call_24;
    int call_25 = arrayInitLoop_1(len_, f_, array_2, 0);
    struct IntConstPtrIntTuple2 call_26 = __constArrayOfMut_1(array_2);
    if_10 = call_26;
    goto if_next_33;
if_next_33:;
    return if_10;
}

int fun_8(int i_5) {
    return i_5;
}

int fun_13(void const* env_1, int arg_2) {
    int call_27 = fun_8(arg_2);
    return call_27;
}

struct IntConstPtrIntTuple2 range_(int len_2) {
    void const* box_ = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_))) = 0;
    struct IntIntFun1 fun_26 = (struct IntIntFun1){.fun = fun_13, .env = box_};
    struct IntConstPtrIntTuple2 call_28 = init_1(len_2, fun_26);
    return call_28;
}

int length_2(struct UnitConstPtrIntTuple2 array_3) {
    int call_29 = __constArrayLength_2(array_3);
    return call_29;
}

int length_1(struct IntConstPtrIntTuple2 array_3) {
    int call_30 = __constArrayLength_1(array_3);
    return call_30;
}

struct IntList const* tryItem_1(int i_6, struct IntConstPtrIntTuple2 array_5) {
    int call_31 = length_1(array_5);
    struct IntList const* if_11;
    if ((((uint32_t)i_6) < ((uint32_t)call_31))) {
        goto then_37;
    } else {
        goto else_38;
    }
then_37:;
    int call_32 = __constArrayGet_1(i_6, array_5);
    struct IntList const* some_1 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)some_1))) = (struct IntList){.head = call_32, .tail = NULL};
    if_11 = some_1;
    goto if_next_36;
else_38:;
    if_11 = NULL;
    goto if_next_36;
if_next_36:;
    return if_11;
}

struct IntConstPtrIntTuple2 slice_1(int start_, int endIndex_, struct IntConstPtrIntTuple2 array_6) {
    int call_33 = length_1(array_6);
    int len_3 = call_33;
    int if_12;
    if ((start_ >= 0)) {
        goto then_40;
    } else {
        goto else_41;
    }
then_40:;
    if_12 = start_;
    goto if_next_39;
else_41:;
    if_12 = 0;
    goto if_next_39;
if_next_39:;
    int start_1 = if_12;
    int if_13;
    if ((endIndex_ < len_3)) {
        goto then_43;
    } else {
        goto else_44;
    }
then_43:;
    if_13 = endIndex_;
    goto if_next_42;
else_44:;
    if_13 = len_3;
    goto if_next_42;
if_next_42:;
    int endIndex_1 = if_13;
    struct IntConstPtrIntTuple2 if_14;
    if ((start_1 < endIndex_1)) {
        goto then_46;
    } else {
        goto else_47;
    }
then_46:;
    struct IntConstPtrIntTuple2 call_34 = __constArraySlice_1(start_1, endIndex_1, array_6);
    if_14 = call_34;
    goto if_next_45;
else_47:;
    struct IntConstPtrIntTuple2 call_35 = empty_3(0);
    if_14 = call_35;
    goto if_next_45;
if_next_45:;
    return if_14;
}

struct IntConstPtrIntTuple2 skip_1(int skipLen_, struct IntConstPtrIntTuple2 array_7) {
    int call_36 = length_1(array_7);
    struct IntConstPtrIntTuple2 call_37 = slice_1(skipLen_, call_36, array_7);
    return call_37;
}

struct IntIntConstPtrIntTuple2Tuple2 {
    int t0;
    struct IntConstPtrIntTuple2 t1;
};

struct IntIntConstPtrIntTuple2Tuple2List {
    struct IntIntConstPtrIntTuple2Tuple2 head;
    struct IntIntConstPtrIntTuple2Tuple2List const* tail;
};

struct IntIntConstPtrIntTuple2Tuple2List const* uncons_1(struct IntConstPtrIntTuple2 array_10) {
    int call_38 = length_1(array_10);
    int len_4 = call_38;
    struct IntIntConstPtrIntTuple2Tuple2List const* if_15;
    if ((len_4 == 0)) {
        goto then_49;
    } else {
        goto else_50;
    }
then_49:;
    if_15 = NULL;
    goto if_next_48;
else_50:;
    int call_39 = __constArrayGet_1(0, array_10);
    int head_ = call_39;
    struct IntConstPtrIntTuple2 call_40 = __constArraySlice_1(1, len_4, array_10);
    struct IntConstPtrIntTuple2 tail_ = call_40;
    struct IntIntConstPtrIntTuple2Tuple2 tuple_8 = (struct IntIntConstPtrIntTuple2Tuple2){.t0 = head_, .t1 = tail_};
    struct IntIntConstPtrIntTuple2Tuple2List const* some_2 = milone_mem_alloc(1, sizeof(struct IntIntConstPtrIntTuple2Tuple2List));
    (*(((struct IntIntConstPtrIntTuple2Tuple2List*)some_2))) = (struct IntIntConstPtrIntTuple2Tuple2List){.head = tuple_8, .tail = NULL};
    if_15 = some_2;
    goto if_next_48;
if_next_48:;
    return if_15;
}

struct IntIntIntFun2 {
    int(*fun)(void const*, int, int);
    void const* env;
};

int fun_25(struct IntIntIntFun2 f_1, struct IntConstPtrIntTuple2 array_11, int i_7) {
    int call_41 = __constArrayGet_1(i_7, array_11);
    int app_2 = f_1.fun(f_1.env, i_7, call_41);
    return app_2;
}

struct IntIntIntFun2IntConstPtrIntTuple2Tuple2 {
    struct IntIntIntFun2 t0;
    struct IntConstPtrIntTuple2 t1;
};

int fun_24(void const* env_2, int arg_3) {
    struct IntIntIntFun2 arg_4 = (*(((struct IntIntIntFun2IntConstPtrIntTuple2Tuple2 const*)env_2))).t0;
    struct IntConstPtrIntTuple2 arg_5 = (*(((struct IntIntIntFun2IntConstPtrIntTuple2Tuple2 const*)env_2))).t1;
    int call_42 = fun_25(arg_4, arg_5, arg_3);
    return call_42;
}

struct IntConstPtrIntTuple2 mapi_1(struct IntIntIntFun2 f_1, struct IntConstPtrIntTuple2 array_11) {
    int call_43 = length_1(array_11);
    struct IntIntIntFun2IntConstPtrIntTuple2Tuple2 tuple_9 = (struct IntIntIntFun2IntConstPtrIntTuple2Tuple2){.t0 = f_1, .t1 = array_11};
    void const* box_1 = milone_mem_alloc(1, sizeof(struct IntIntIntFun2IntConstPtrIntTuple2Tuple2));
    (*(((struct IntIntIntFun2IntConstPtrIntTuple2Tuple2*)box_1))) = tuple_9;
    struct IntIntFun1 fun_27 = (struct IntIntFun1){.fun = fun_24, .env = box_1};
    struct IntConstPtrIntTuple2 call_44 = init_1(call_43, fun_27);
    return call_44;
}

struct IntIntListFun1 {
    struct IntList const*(*fun)(void const*, int);
    void const* env;
};

int chooseLoop_1(struct IntIntListFun1 f_3, struct IntConstPtrIntTuple2 src_, int len_5, struct IntMutPtrIntTuple2 dest_, int di_, int si_) {
tailrec_51:;
    int if_16;
    if ((si_ == len_5)) {
        goto then_53;
    } else {
        goto else_54;
    }
then_53:;
    if_16 = di_;
    goto if_next_52;
else_54:;
    int match_;
    int call_45 = __constArrayGet_1(si_, src_);
    struct IntList const* app_3 = f_3.fun(f_3.env, call_45);
    if ((!(app_3))) goto next_56;
    int value_ = app_3->head;
    int call_46 = __mutArraySet_1(di_, value_, dest_);
    struct IntIntListFun1 arg_31 = f_3;
    struct IntConstPtrIntTuple2 arg_32 = src_;
    int arg_33 = len_5;
    struct IntMutPtrIntTuple2 arg_34 = dest_;
    int arg_35 = (di_ + 1);
    int arg_36 = (si_ + 1);
    f_3 = arg_31;
    src_ = arg_32;
    len_5 = arg_33;
    dest_ = arg_34;
    di_ = arg_35;
    si_ = arg_36;
    goto tailrec_51;
    match_ = 0;
    goto end_match_55;
next_56:;
    if ((!((!(app_3))))) goto next_57;
    struct IntIntListFun1 arg_37 = f_3;
    struct IntConstPtrIntTuple2 arg_38 = src_;
    int arg_39 = len_5;
    struct IntMutPtrIntTuple2 arg_40 = dest_;
    int arg_41 = di_;
    int arg_42 = (si_ + 1);
    f_3 = arg_37;
    src_ = arg_38;
    len_5 = arg_39;
    dest_ = arg_40;
    di_ = arg_41;
    si_ = arg_42;
    goto tailrec_51;
    match_ = 0;
    goto end_match_55;
next_57:;
    exit(1);
end_match_55:;
    if_16 = match_;
    goto if_next_52;
if_next_52:;
    return if_16;
}

struct IntConstPtrIntTuple2 choose_1(struct IntIntListFun1 f_3, struct IntConstPtrIntTuple2 src_) {
    int call_47 = length_1(src_);
    int len_5 = call_47;
    struct IntMutPtrIntTuple2 call_48 = __mutArrayCreate_1(len_5);
    struct IntMutPtrIntTuple2 dest_ = call_48;
    int call_49 = chooseLoop_1(f_3, src_, len_5, dest_, 0, 0);
    int di_1 = call_49;
    struct IntConstPtrIntTuple2 if_17;
    if ((di_1 == 0)) {
        goto then_59;
    } else {
        goto else_60;
    }
then_59:;
    struct IntConstPtrIntTuple2 call_50 = empty_3(0);
    if_17 = call_50;
    goto if_next_58;
else_60:;
    struct IntMutPtrIntTuple2 call_51 = __mutArraySlice_1(0, di_1, dest_);
    struct IntConstPtrIntTuple2 call_52 = __constArrayOfMut_1(call_51);
    if_17 = call_52;
    goto if_next_58;
if_next_58:;
    return if_17;
}

int arrayFoldLoop_1(struct IntIntIntFun2 folder_, struct IntConstPtrIntTuple2 array_13, int len_6, int state_2, int i_9) {
tailrec_61:;
    int if_18;
    if ((i_9 == len_6)) {
        goto then_63;
    } else {
        goto else_64;
    }
then_63:;
    if_18 = state_2;
    goto if_next_62;
else_64:;
    struct IntIntIntFun2 arg_43 = folder_;
    struct IntConstPtrIntTuple2 arg_44 = array_13;
    int arg_45 = len_6;
    int call_53 = __constArrayGet_1(i_9, array_13);
    int app_4 = folder_.fun(folder_.env, state_2, call_53);
    int arg_46 = app_4;
    int arg_47 = (i_9 + 1);
    folder_ = arg_43;
    array_13 = arg_44;
    len_6 = arg_45;
    state_2 = arg_46;
    i_9 = arg_47;
    goto tailrec_61;
    if_18 = 0;
    goto if_next_62;
if_next_62:;
    return if_18;
}

int fold_1(struct IntIntIntFun2 folder_, int state_1, struct IntConstPtrIntTuple2 array_13) {
    int call_54 = length_1(array_13);
    int len_6 = call_54;
    int call_55 = arrayFoldLoop_1(folder_, array_13, len_6, state_1, 0);
    return call_55;
}

int listLengthLoop_1(int acc_, struct IntList const* xs_1) {
tailrec_65:;
    int match_1;
    if ((!((!(xs_1))))) goto next_67;
    match_1 = acc_;
    goto end_match_66;
next_67:;
    if ((!(xs_1))) goto next_68;
    struct IntList const* xs_2 = xs_1->tail;
    int arg_48 = (acc_ + 1);
    struct IntList const* arg_49 = xs_2;
    acc_ = arg_48;
    xs_1 = arg_49;
    goto tailrec_65;
    match_1 = 0;
    goto end_match_66;
next_68:;
    exit(1);
end_match_66:;
    return match_1;
}

int ofListLoop_1(int len_7, struct IntMutPtrIntTuple2 dest_1, int i_10, struct IntList const* xs_3) {
tailrec_69:;
    int match_2;
    if ((!((!(xs_3))))) goto next_71;
    milone_assert((i_10 == len_7), 186, 12);
    match_2 = 0;
    goto end_match_70;
next_71:;
    if ((!(xs_3))) goto next_72;
    int x_ = xs_3->head;
    struct IntList const* xs_4 = xs_3->tail;
    int call_56 = __mutArraySet_1(i_10, x_, dest_1);
    int arg_50 = len_7;
    struct IntMutPtrIntTuple2 arg_51 = dest_1;
    int arg_52 = (i_10 + 1);
    struct IntList const* arg_53 = xs_4;
    len_7 = arg_50;
    dest_1 = arg_51;
    i_10 = arg_52;
    xs_3 = arg_53;
    goto tailrec_69;
    match_2 = 0;
    goto end_match_70;
next_72:;
    exit(1);
end_match_70:;
    return 0;
}

struct IntConstPtrIntTuple2 ofList_1(struct IntList const* xs_) {
    int call_57 = listLengthLoop_1(0, xs_);
    int len_7 = call_57;
    struct IntMutPtrIntTuple2 call_58 = __mutArrayCreate_1(len_7);
    struct IntMutPtrIntTuple2 dest_1 = call_58;
    int call_59 = ofListLoop_1(len_7, dest_1, 0, xs_);
    struct IntConstPtrIntTuple2 call_60 = __constArrayOfMut_1(dest_1);
    return call_60;
}

struct IntList const* toListLoop_1(struct IntConstPtrIntTuple2 array_14, struct IntList const* acc_1, int i_11) {
tailrec_73:;
    struct IntList const* if_19;
    if ((i_11 == 0)) {
        goto then_75;
    } else {
        goto else_76;
    }
then_75:;
    if_19 = acc_1;
    goto if_next_74;
else_76:;
    struct IntConstPtrIntTuple2 arg_54 = array_14;
    int call_61 = __constArrayGet_1((i_11 - 1), array_14);
    struct IntList const* list_ = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_))) = (struct IntList){.head = call_61, .tail = acc_1};
    struct IntList const* arg_55 = list_;
    int arg_56 = (i_11 - 1);
    array_14 = arg_54;
    acc_1 = arg_55;
    i_11 = arg_56;
    goto tailrec_73;
    if_19 = NULL;
    goto if_next_74;
if_next_74:;
    return if_19;
}

struct IntList const* toList_1(struct IntConstPtrIntTuple2 array_14) {
    int call_62 = length_1(array_14);
    struct IntList const* call_63 = toListLoop_1(array_14, NULL, call_62);
    return call_63;
}

int get_1(int i_, struct IntConstPtrIntTuple2 array_) {
    int match_3;
    struct IntList const* call_64 = tryItem_1(i_, array_);
    if ((!(call_64))) goto next_78;
    int it_ = call_64->head;
    match_3 = it_;
    goto end_match_77;
next_78:;
    if ((!((!(call_64))))) goto next_79;
    int call_65 = length_1(array_);
    printf("out of range: i=%d len=%d\n", i_, call_65);
    milone_assert(false, 9, 6);
    exit(1);
    match_3 = 0;
    goto end_match_77;
next_79:;
    exit(1);
end_match_77:;
    return match_3;
}

int fun_(int arg_57) {
    milone_assert(false, 13, 45);
    return 0;
}

int fun_17(void const* env_5, int arg_11) {
    int call_66 = fun_(arg_11);
    return 0;
}

int fun_1(int n_) {
    return ((n_ + 1) * 3);
}

int fun_18(void const* env_6, int arg_12) {
    int call_67 = fun_1(arg_12);
    return call_67;
}

int initTest_(int arg_58) {
    void const* box_2 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_2))) = 0;
    struct IntUnitFun1 fun_28 = (struct IntUnitFun1){.fun = fun_17, .env = box_2};
    struct UnitConstPtrIntTuple2 call_68 = init_2(0, fun_28);
    struct UnitConstPtrIntTuple2 emptyArray_ = call_68;
    int call_69 = length_2(emptyArray_);
    milone_assert((call_69 == 0), 14, 2);
    void const* box_3 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_3))) = 0;
    struct IntIntFun1 fun_29 = (struct IntIntFun1){.fun = fun_18, .env = box_3};
    struct IntConstPtrIntTuple2 call_70 = init_1(3, fun_29);
    struct IntConstPtrIntTuple2 a369_ = call_70;
    int call_71 = length_1(a369_);
    milone_assert((call_71 == 3), 17, 2);
    int call_72 = get_1(0, a369_);
    milone_assert((call_72 == 3), 18, 2);
    int call_73 = get_1(1, a369_);
    milone_assert((call_73 == 6), 19, 2);
    int call_74 = get_1(2, a369_);
    milone_assert((call_74 == 9), 20, 2);
    return 0;
}

int rangeTest_(int arg_59) {
    struct IntConstPtrIntTuple2 call_75 = range_(3);
    struct IntConstPtrIntTuple2 a012_ = call_75;
    int call_76 = length_1(a012_);
    milone_assert((call_76 == 3), 25, 2);
    int call_77 = get_1(0, a012_);
    milone_assert((call_77 == 0), 26, 2);
    int call_78 = get_1(1, a012_);
    milone_assert((call_78 == 1), 27, 2);
    int call_79 = get_1(2, a012_);
    milone_assert((call_79 == 2), 28, 2);
    return 0;
}

int at_(int bad_, int i_1, struct IntConstPtrIntTuple2 array_1) {
    int match_4;
    struct IntList const* call_80 = tryItem_1(i_1, array_1);
    if ((!(call_80))) goto next_81;
    int it_1 = call_80->head;
    match_4 = it_1;
    goto end_match_80;
next_81:;
    if ((!((!(call_80))))) goto next_82;
    match_4 = bad_;
    goto end_match_80;
next_82:;
    exit(1);
end_match_80:;
    return match_4;
}

int tryItemTest_(int arg_60) {
    struct IntConstPtrIntTuple2 call_81 = range_(3);
    struct IntConstPtrIntTuple2 a012_1 = call_81;
    int bad_ = -127;
    int call_82 = at_(bad_, -1, a012_1);
    milone_assert((call_82 == bad_), 40, 2);
    int call_83 = at_(bad_, 0, a012_1);
    milone_assert((call_83 == 0), 41, 2);
    int call_84 = at_(bad_, 2, a012_1);
    milone_assert((call_84 == 2), 42, 2);
    int call_85 = at_(bad_, 3, a012_1);
    milone_assert((call_85 == bad_), 43, 2);
    struct IntConstPtrIntTuple2 call_86 = empty_3(0);
    struct IntConstPtrIntTuple2 emptyArray_1 = call_86;
    int call_87 = at_(bad_, 0, emptyArray_1);
    milone_assert((call_87 == bad_), 46, 2);
    return 0;
}

int sliceTest_(int arg_61) {
    struct IntConstPtrIntTuple2 call_88 = range_(10);
    struct IntConstPtrIntTuple2 ten_ = call_88;
    struct IntConstPtrIntTuple2 call_89 = slice_1(1, 4, ten_);
    struct IntConstPtrIntTuple2 three_ = call_89;
    int call_90 = length_1(three_);
    milone_assert((call_90 == 3), 52, 2);
    int call_91 = get_1(0, three_);
    milone_assert((call_91 == 1), 53, 2);
    int call_92 = get_1(2, three_);
    milone_assert((call_92 == 3), 54, 2);
    struct IntConstPtrIntTuple2 call_93 = slice_1(-1, 2, ten_);
    struct IntConstPtrIntTuple2 behind_ = call_93;
    int call_94 = length_1(behind_);
    milone_assert((call_94 == 2), 58, 2);
    int call_95 = get_1(1, behind_);
    milone_assert((call_95 == 1), 59, 2);
    struct IntConstPtrIntTuple2 call_96 = slice_1(7, 11, ten_);
    struct IntConstPtrIntTuple2 beyond_ = call_96;
    int call_97 = length_1(beyond_);
    milone_assert((call_97 == 3), 63, 2);
    int call_98 = get_1(0, beyond_);
    milone_assert((call_98 == 7), 64, 2);
    int call_99 = get_1(2, beyond_);
    milone_assert((call_99 == 9), 65, 2);
    return 0;
}

int fun_2(int n_1) {
    return (n_1 + 1);
}

int fun_19(void const* env_7, int arg_13) {
    int call_100 = fun_2(arg_13);
    return call_100;
}

int unconsTest_(int arg_62) {
    void const* box_4 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_4))) = 0;
    struct IntIntFun1 fun_30 = (struct IntIntFun1){.fun = fun_19, .env = box_4};
    struct IntConstPtrIntTuple2 call_101 = init_1(3, fun_30);
    struct IntConstPtrIntTuple2 a123_ = call_101;
    int match_5;
    struct IntIntConstPtrIntTuple2Tuple2List const* call_102 = uncons_1(a123_);
    if ((!((!(call_102))))) goto next_84;
    milone_assert(false, 70, 12);
    match_5 = 0;
    goto end_match_83;
next_84:;
    if ((!(call_102))) goto next_85;
    int n1_ = call_102->head.t0;
    struct IntConstPtrIntTuple2 a23_ = call_102->head.t1;
    milone_assert((n1_ == 1), 72, 6);
    int call_103 = length_1(a23_);
    milone_assert((call_103 == 2), 73, 6);
    int match_6;
    struct IntConstPtrIntTuple2 call_104 = skip_1(1, a23_);
    struct IntIntConstPtrIntTuple2Tuple2List const* call_105 = uncons_1(call_104);
    if ((!((!(call_105))))) goto next_87;
    milone_assert(false, 76, 16);
    match_6 = 0;
    goto end_match_86;
next_87:;
    if ((!(call_105))) goto next_88;
    int n3_ = call_105->head.t0;
    struct IntConstPtrIntTuple2 empty_ = call_105->head.t1;
    milone_assert((n3_ == 3), 78, 10);
    int call_106 = length_1(empty_);
    milone_assert((call_106 == 0), 79, 10);
    int match_7;
    struct IntIntConstPtrIntTuple2Tuple2List const* call_107 = uncons_1(empty_);
    if ((!((!(call_107))))) goto next_90;
    match_7 = 0;
    goto end_match_89;
next_90:;
    if ((!(call_107))) goto next_91;
    milone_assert(false, 83, 22);
    match_7 = 0;
    goto end_match_89;
next_91:;
    exit(1);
end_match_89:;
    match_6 = 0;
    goto end_match_86;
next_88:;
    exit(1);
end_match_86:;
    match_5 = 0;
    goto end_match_83;
next_85:;
    exit(1);
end_match_83:;
    return 0;
}

int fun_3(int i_2, int n_2) {
    return ((i_2 * 10) + n_2);
}

int fun_20(void const* env_8, int arg_14, int arg_15) {
    int call_108 = fun_3(arg_14, arg_15);
    return call_108;
}

int mapTest_(int arg_63) {
    void const* box_5 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_5))) = 0;
    struct IntIntIntFun2 fun_31 = (struct IntIntIntFun2){.fun = fun_20, .env = box_5};
    struct IntConstPtrIntTuple2 call_109 = range_(3);
    struct IntConstPtrIntTuple2 call_110 = mapi_1(fun_31, call_109);
    struct IntConstPtrIntTuple2 mapped_ = call_110;
    int call_111 = length_1(mapped_);
    milone_assert((call_111 == 3), 89, 2);
    int call_112 = get_1(0, mapped_);
    milone_assert((call_112 == 0), 90, 2);
    int call_113 = get_1(1, mapped_);
    milone_assert((call_113 == 11), 91, 2);
    int call_114 = get_1(2, mapped_);
    milone_assert((call_114 == 22), 92, 2);
    return 0;
}

struct IntList const* fun_4(int n_3) {
    struct IntList const* if_20;
    if (((n_3 % 2) == 0)) {
        goto then_93;
    } else {
        goto else_94;
    }
then_93:;
    struct IntList const* some_3 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)some_3))) = (struct IntList){.head = (n_3 * 2), .tail = NULL};
    if_20 = some_3;
    goto if_next_92;
else_94:;
    if_20 = NULL;
    goto if_next_92;
if_next_92:;
    return if_20;
}

struct IntList const* fun_21(void const* env_9, int arg_16) {
    struct IntList const* call_115 = fun_4(arg_16);
    return call_115;
}

struct IntList const* fun_5(int arg_64) {
    return NULL;
}

struct IntList const* fun_22(void const* env_10, int arg_17) {
    struct IntList const* call_116 = fun_5(arg_17);
    return call_116;
}

int chooseTest_(int arg_65) {
    void const* box_6 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_6))) = 0;
    struct IntIntListFun1 fun_32 = (struct IntIntListFun1){.fun = fun_21, .env = box_6};
    struct IntConstPtrIntTuple2 call_117 = range_(6);
    struct IntConstPtrIntTuple2 call_118 = choose_1(fun_32, call_117);
    struct IntConstPtrIntTuple2 chosen_ = call_118;
    int call_119 = length_1(chosen_);
    milone_assert((call_119 == 3), 98, 2);
    int call_120 = get_1(0, chosen_);
    milone_assert((call_120 == 0), 99, 2);
    int call_121 = get_1(1, chosen_);
    milone_assert((call_121 == 4), 100, 2);
    int call_122 = get_1(2, chosen_);
    milone_assert((call_122 == 8), 101, 2);
    void const* box_7 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_7))) = 0;
    struct IntIntListFun1 fun_33 = (struct IntIntListFun1){.fun = fun_22, .env = box_7};
    struct IntConstPtrIntTuple2 call_123 = range_(3);
    struct IntConstPtrIntTuple2 call_124 = choose_1(fun_33, call_123);
    struct IntConstPtrIntTuple2 empty_1 = call_124;
    int call_125 = length_1(empty_1);
    milone_assert((call_125 == 0), 106, 2);
    return 0;
}

int fun_6(int state_, int i_3) {
    return ((state_ * 10) + (i_3 + 1));
}

int fun_23(void const* env_11, int arg_18, int arg_19) {
    int call_126 = fun_6(arg_18, arg_19);
    return call_126;
}

int foldTest_(int arg_66) {
    void const* box_8 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_8))) = 0;
    struct IntIntIntFun2 fun_34 = (struct IntIntIntFun2){.fun = fun_23, .env = box_8};
    struct IntConstPtrIntTuple2 call_127 = range_(3);
    int call_128 = fold_1(fun_34, 0, call_127);
    int sum_ = call_128;
    milone_assert((sum_ == 123), 112, 2);
    return 0;
}

int ofListTest_(int arg_67) {
    struct IntList const* list_3 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_3))) = (struct IntList){.head = 5, .tail = NULL};
    struct IntList const* list_2 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_2))) = (struct IntList){.head = 3, .tail = list_3};
    struct IntList const* list_1 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_1))) = (struct IntList){.head = 2, .tail = list_2};
    struct IntConstPtrIntTuple2 call_129 = ofList_1(list_1);
    struct IntConstPtrIntTuple2 ol_ = call_129;
    int call_130 = length_1(ol_);
    milone_assert((call_130 == 3), 125, 2);
    int call_131 = get_1(0, ol_);
    milone_assert((call_131 == 2), 126, 2);
    int call_132 = get_1(1, ol_);
    milone_assert((call_132 == 3), 127, 2);
    int call_133 = get_1(2, ol_);
    milone_assert((call_133 == 5), 128, 2);
    return 0;
}

int toListTest_(int arg_68) {
    struct IntConstPtrIntTuple2 call_134 = range_(3);
    struct IntList const* call_135 = toList_1(call_134);
    struct IntList const* tl_ = call_135;
    int match_8;
    if ((!(tl_))) goto next_96;
    int n0_ = tl_->head;
    if ((!(tl_->tail))) goto next_96;
    int n1_1 = tl_->tail->head;
    if ((!(tl_->tail->tail))) goto next_96;
    int n2_ = tl_->tail->tail->head;
    if ((!((!(tl_->tail->tail->tail))))) goto next_96;
    milone_assert((n0_ == 0), 135, 6);
    milone_assert((n1_1 == 1), 136, 6);
    milone_assert((n2_ == 2), 137, 6);
    match_8 = 0;
    goto end_match_95;
next_96:;
    match_8 = 0;
    goto end_match_95;
next_97:;
end_match_95:;
    return 0;
}

int milone_main() {
    int call_136 = initTest_(0);
    int call_137 = rangeTest_(0);
    int call_138 = tryItemTest_(0);
    int call_139 = sliceTest_(0);
    int call_140 = unconsTest_(0);
    int call_141 = mapTest_(0);
    int call_142 = chooseTest_(0);
    int call_143 = foldTest_(0);
    int call_144 = ofListTest_(0);
    int call_145 = toListTest_(0);
    return 0;
}
