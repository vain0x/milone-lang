#include "milone.h"

struct StringList;

struct UnitMutPtrIntTuple2;

struct IntMutPtrIntTuple2;

struct UnitConstPtrIntTuple2;

struct IntConstPtrIntTuple2;

struct IntOption;

struct IntUnitFun1;

struct IntIntFun1;

struct IntIntConstPtrIntTuple2Tuple2;

struct IntIntConstPtrIntTuple2Tuple2Option;

struct IntIntIntFun2;

struct IntIntIntFun2IntConstPtrIntTuple2Tuple2;

struct IntIntOptionFun1;

struct IntList;

struct IntList;

struct String str_concat(struct String, struct StringList const*);

struct String __stringJoin_(struct String sep_, struct StringList const* xs_);

intptr_t __pointeeSize_2(char const* constPtr_);

intptr_t __pointeeSize_1(int const* constPtr_);

int const* __ptrAsConst_1(int* mutPtr_);

char const* __ptrAsConst_2(char* mutPtr_);

int const* __ptrAdd_1(int index_, int const* ptr_);

int* __mutPtrAdd_1(int index_1, int* mutPtr_1);

void* milone_mem_alloc(int, uintptr_t);

void* memAlloc_(int len_, uintptr_t size_);

void* memcpy(void*, void const*, uintptr_t);

void* memcpy_(void* dest_, void const* src_, uintptr_t size_1);

struct UnitMutPtrIntTuple2 __mutArrayCreate_2(int len_1);

struct IntMutPtrIntTuple2 __mutArrayCreate_1(int len_1);

char __mutArraySet_2(int index_2, char value_, struct UnitMutPtrIntTuple2 array_);

char __mutArraySet_1(int index_2, int value_, struct IntMutPtrIntTuple2 array_);

struct IntMutPtrIntTuple2 __mutArraySlice_1(int start_, int endIndex_, struct IntMutPtrIntTuple2 array_1);

struct UnitConstPtrIntTuple2 __constArrayOfMut_2(struct UnitMutPtrIntTuple2 mutArray_);

struct IntConstPtrIntTuple2 __constArrayOfMut_1(struct IntMutPtrIntTuple2 mutArray_);

int __constArrayLength_2(struct UnitConstPtrIntTuple2 array_2);

int __constArrayLength_1(struct IntConstPtrIntTuple2 array_2);

int __constArrayGet_1(int index_3, struct IntConstPtrIntTuple2 array_3);

struct IntConstPtrIntTuple2 __constArraySlice_1(int start_1, int endIndex_1, struct IntConstPtrIntTuple2 array_4);

bool str_to_int_checked(struct String, int*);

struct IntOption __intOfStr_(struct String s_);

int milone_get_arg_count();

int __argCount_(char arg_20);

struct String milone_get_arg(int);

struct String __argGet_(int index_4);

struct IntConstPtrIntTuple2 empty_3(char arg_21);

struct UnitConstPtrIntTuple2 empty_4(char arg_22);

char arrayInitLoop_2(int len_8, struct IntUnitFun1 f_, struct UnitMutPtrIntTuple2 array_5, int i_);

char arrayInitLoop_1(int len_8, struct IntIntFun1 f_, struct IntMutPtrIntTuple2 array_5, int i_);

struct UnitConstPtrIntTuple2 init_2(int len_8, struct IntUnitFun1 f_);

struct IntConstPtrIntTuple2 init_1(int len_8, struct IntIntFun1 f_);

int fun_1(int i_1);

int fun_13(void const* env_1, int arg_2);

struct IntConstPtrIntTuple2 range_(int len_10);

int length_2(struct UnitConstPtrIntTuple2 array_6);

int length_1(struct IntConstPtrIntTuple2 array_6);

struct IntOption tryItem_1(int i_2, struct IntConstPtrIntTuple2 array_8);

struct IntConstPtrIntTuple2 slice_1(int start_2, int endIndex_2, struct IntConstPtrIntTuple2 array_9);

struct IntConstPtrIntTuple2 skip_1(int skipLen_, struct IntConstPtrIntTuple2 array_10);

struct IntIntConstPtrIntTuple2Tuple2Option uncons_1(struct IntConstPtrIntTuple2 array_13);

int fun_25(struct IntIntIntFun2 f_1, struct IntConstPtrIntTuple2 array_14, int i_3);

int fun_24(void const* env_2, int arg_3);

struct IntConstPtrIntTuple2 mapi_1(struct IntIntIntFun2 f_1, struct IntConstPtrIntTuple2 array_14);

int chooseLoop_1(struct IntIntOptionFun1 f_3, struct IntConstPtrIntTuple2 src_1, int len_13, struct IntMutPtrIntTuple2 dest_1, int di_, int si_);

struct IntConstPtrIntTuple2 choose_1(struct IntIntOptionFun1 f_3, struct IntConstPtrIntTuple2 src_1);

int arrayFoldLoop_1(struct IntIntIntFun2 folder_, struct IntConstPtrIntTuple2 array_16, int len_14, int state_1, int i_5);

int fold_1(struct IntIntIntFun2 folder_, int state_, struct IntConstPtrIntTuple2 array_16);

int listLengthLoop_1(int acc_, struct IntList const* xs_2);

char ofListLoop_1(int len_15, struct IntMutPtrIntTuple2 dest_2, int i_6, struct IntList const* xs_4);

struct IntConstPtrIntTuple2 ofList_1(struct IntList const* xs_1);

struct IntList const* toListLoop_1(struct IntConstPtrIntTuple2 array_17, struct IntList const* acc_1, int i_7);

struct IntList const* toList_1(struct IntConstPtrIntTuple2 array_17);

int get_1(int i_8, struct IntConstPtrIntTuple2 array_18);

char fun_5(int arg_57);

char fun_17(void const* env_5, int arg_11);

int fun_6(int n_);

int fun_18(void const* env_6, int arg_12);

char initTest_(char arg_58);

char rangeTest_(char arg_59);

int at_(int bad_, int i_9, struct IntConstPtrIntTuple2 array_19);

char tryItemTest_(char arg_60);

char sliceTest_(char arg_61);

int fun_7(int n_1);

int fun_19(void const* env_7, int arg_13);

char unconsTest_(char arg_62);

int fun_8(int i_10, int n_2);

int fun_20(void const* env_8, int arg_14, int arg_15);

char mapTest_(char arg_63);

struct IntOption fun_9(int n_3);

struct IntOption fun_21(void const* env_9, int arg_16);

struct IntOption fun_10(int arg_64);

struct IntOption fun_22(void const* env_10, int arg_17);

char chooseTest_(char arg_65);

int fun_11(int state_2, int i_11);

int fun_23(void const* env_11, int arg_18, int arg_19);

char foldTest_(char arg_66);

char ofListTest_(char arg_67);

char toListTest_(char arg_68);

int milone_main();

struct UnitMutPtrIntTuple2 {
    char* t0;
    int t1;
};

struct IntMutPtrIntTuple2 {
    int* t0;
    int t1;
};

struct UnitConstPtrIntTuple2 {
    char const* t0;
    int t1;
};

struct IntConstPtrIntTuple2 {
    int const* t0;
    int t1;
};

struct IntOption {
    bool some;
    int value;
};

struct IntUnitFun1 {
    char(*fun)(void const*, int);
    void const* env;
};

struct IntIntFun1 {
    int(*fun)(void const*, int);
    void const* env;
};

struct IntIntConstPtrIntTuple2Tuple2 {
    int t0;
    struct IntConstPtrIntTuple2 t1;
};

struct IntIntConstPtrIntTuple2Tuple2Option {
    bool some;
    struct IntIntConstPtrIntTuple2Tuple2 value;
};

struct IntIntIntFun2 {
    int(*fun)(void const*, int, int);
    void const* env;
};

struct IntIntIntFun2IntConstPtrIntTuple2Tuple2 {
    struct IntIntIntFun2 t0;
    struct IntConstPtrIntTuple2 t1;
};

struct IntIntOptionFun1 {
    struct IntOption(*fun)(void const*, int);
    void const* env;
};

struct IntList {
    int head;
    struct IntList const* tail;
};

struct String __stringJoin_(struct String sep_, struct StringList const* xs_) {
    struct String str_concat_result_ = str_concat(sep_, xs_);
    return str_concat_result_;
}

intptr_t __pointeeSize_2(char const* constPtr_) {
    return ((intptr_t)sizeof(char));
}

intptr_t __pointeeSize_1(int const* constPtr_) {
    return ((intptr_t)sizeof(int));
}

int const* __ptrAsConst_1(int* mutPtr_) {
    return ((int const*)mutPtr_);
}

char const* __ptrAsConst_2(char* mutPtr_) {
    return ((char const*)mutPtr_);
}

int const* __ptrAdd_1(int index_, int const* ptr_) {
    intptr_t call_ = __pointeeSize_1(ptr_);
    return ((int const*)(((intptr_t)ptr_) + (((intptr_t)index_) * call_)));
}

int* __mutPtrAdd_1(int index_1, int* mutPtr_1) {
    int const* call_1 = __ptrAsConst_1(mutPtr_1);
    intptr_t call_2 = __pointeeSize_1(call_1);
    return ((int*)(((intptr_t)mutPtr_1) + (((intptr_t)index_1) * call_2)));
}

void* memAlloc_(int len_, uintptr_t size_) {
    void* milone_mem_alloc_result_ = milone_mem_alloc(len_, size_);
    return milone_mem_alloc_result_;
}

void* memcpy_(void* dest_, void const* src_, uintptr_t size_1) {
    void* memcpy_result_ = memcpy(dest_, src_, size_1);
    return memcpy_result_;
}

struct UnitMutPtrIntTuple2 __mutArrayCreate_2(int len_1) {
    struct UnitMutPtrIntTuple2 if_;
    if ((len_1 == 0)) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    struct UnitMutPtrIntTuple2 tuple_ = ((struct UnitMutPtrIntTuple2){.t0 = ((char*)((uintptr_t)0)), .t1 = 0});
    if_ = tuple_;
    goto if_next_1;
else_3:;
    char const* nullPtr_ = ((char const*)((uintptr_t)0));
    intptr_t call_3 = __pointeeSize_2(nullPtr_);
    void* call_4 = memAlloc_(len_1, ((uintptr_t)call_3));
    char* ptr_1 = ((char*)call_4);
    struct UnitMutPtrIntTuple2 tuple_1 = ((struct UnitMutPtrIntTuple2){.t0 = ptr_1, .t1 = len_1});
    if_ = tuple_1;
    goto if_next_1;
if_next_1:;
    return if_;
}

struct IntMutPtrIntTuple2 __mutArrayCreate_1(int len_1) {
    struct IntMutPtrIntTuple2 if_1;
    if ((len_1 == 0)) {
        goto then_5;
    } else {
        goto else_6;
    }
then_5:;
    struct IntMutPtrIntTuple2 tuple_2 = ((struct IntMutPtrIntTuple2){.t0 = ((int*)((uintptr_t)0)), .t1 = 0});
    if_1 = tuple_2;
    goto if_next_4;
else_6:;
    int const* nullPtr_ = ((int const*)((uintptr_t)0));
    intptr_t call_5 = __pointeeSize_1(nullPtr_);
    void* call_6 = memAlloc_(len_1, ((uintptr_t)call_5));
    int* ptr_1 = ((int*)call_6);
    struct IntMutPtrIntTuple2 tuple_3 = ((struct IntMutPtrIntTuple2){.t0 = ptr_1, .t1 = len_1});
    if_1 = tuple_3;
    goto if_next_4;
if_next_4:;
    return if_1;
}

char __mutArraySet_2(int index_2, char value_, struct UnitMutPtrIntTuple2 array_) {
    char* mutPtr_2 = array_.t0;
    int len_2 = array_.t1;
    milone_assert((((uint32_t)index_2) < ((uint32_t)len_2)), 54, 2);
    mutPtr_2[index_2] = 0;
    return 0;
}

char __mutArraySet_1(int index_2, int value_, struct IntMutPtrIntTuple2 array_) {
    int* mutPtr_2 = array_.t0;
    int len_2 = array_.t1;
    milone_assert((((uint32_t)index_2) < ((uint32_t)len_2)), 54, 2);
    mutPtr_2[index_2] = value_;
    return 0;
}

struct IntMutPtrIntTuple2 __mutArraySlice_1(int start_, int endIndex_, struct IntMutPtrIntTuple2 array_1) {
    int* mutPtr_3 = array_1.t0;
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
    milone_assert(if_3, 61, 2);
    int* call_7 = __mutPtrAdd_1(start_, mutPtr_3);
    struct IntMutPtrIntTuple2 tuple_4 = ((struct IntMutPtrIntTuple2){.t0 = call_7, .t1 = (endIndex_ - start_)});
    return tuple_4;
}

struct UnitConstPtrIntTuple2 __constArrayOfMut_2(struct UnitMutPtrIntTuple2 mutArray_) {
    char* mutPtr_4 = mutArray_.t0;
    int len_4 = mutArray_.t1;
    char const* call_8 = __ptrAsConst_2(mutPtr_4);
    struct UnitConstPtrIntTuple2 tuple_5 = ((struct UnitConstPtrIntTuple2){.t0 = call_8, .t1 = len_4});
    return tuple_5;
}

struct IntConstPtrIntTuple2 __constArrayOfMut_1(struct IntMutPtrIntTuple2 mutArray_) {
    int* mutPtr_4 = mutArray_.t0;
    int len_4 = mutArray_.t1;
    int const* call_9 = __ptrAsConst_1(mutPtr_4);
    struct IntConstPtrIntTuple2 tuple_6 = ((struct IntConstPtrIntTuple2){.t0 = call_9, .t1 = len_4});
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
    milone_assert((((uint32_t)index_3) < ((uint32_t)len_6)), 81, 2);
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
    milone_assert(if_5, 87, 2);
    int const* call_10 = __ptrAdd_1(start_1, ptr_3);
    struct IntConstPtrIntTuple2 tuple_7 = ((struct IntConstPtrIntTuple2){.t0 = call_10, .t1 = (endIndex_1 - start_1)});
    return tuple_7;
}

struct IntOption __intOfStr_(struct String s_) {
    void* call_11 = memAlloc_(1, ((uintptr_t)sizeof(int)));
    int* valueRef_ = ((int*)call_11);
    bool str_to_int_checked_result_ = str_to_int_checked(s_, valueRef_);
    bool ok_ = str_to_int_checked_result_;
    struct IntOption if_6;
    if (ok_) {
        goto then_20;
    } else {
        goto else_21;
    }
then_20:;
    int const* call_12 = __ptrAsConst_1(valueRef_);
    int read_1 = (*(call_12));
    struct IntOption some_ = ((struct IntOption){.some = true, .value = read_1});
    if_6 = some_;
    goto if_next_19;
else_21:;
    if_6 = ((struct IntOption){.some = false});
    goto if_next_19;
if_next_19:;
    return if_6;
}

int __argCount_(char arg_20) {
    int milone_get_arg_count_result_ = milone_get_arg_count();
    return milone_get_arg_count_result_;
}

struct String __argGet_(int index_4) {
    struct String milone_get_arg_result_ = milone_get_arg(index_4);
    return milone_get_arg_result_;
}

struct IntConstPtrIntTuple2 empty_3(char arg_21) {
    struct IntMutPtrIntTuple2 call_13 = __mutArrayCreate_1(0);
    struct IntConstPtrIntTuple2 call_14 = __constArrayOfMut_1(call_13);
    return call_14;
}

struct UnitConstPtrIntTuple2 empty_4(char arg_22) {
    struct UnitMutPtrIntTuple2 call_15 = __mutArrayCreate_2(0);
    struct UnitConstPtrIntTuple2 call_16 = __constArrayOfMut_2(call_15);
    return call_16;
}

char arrayInitLoop_2(int len_8, struct IntUnitFun1 f_, struct UnitMutPtrIntTuple2 array_5, int i_) {
tailrec_22:;
    char if_7;
    if ((i_ < len_8)) {
        goto then_24;
    } else {
        goto else_25;
    }
then_24:;
    char app_ = f_.fun(f_.env, i_);
    char item_ = 0;
    char call_17 = __mutArraySet_2(i_, 0, array_5);
    int arg_23 = len_8;
    struct IntUnitFun1 arg_24 = f_;
    struct UnitMutPtrIntTuple2 arg_25 = array_5;
    int arg_26 = (i_ + 1);
    len_8 = arg_23;
    f_ = arg_24;
    array_5 = arg_25;
    i_ = arg_26;
    goto tailrec_22;
else_25:;
    if_7 = 0;
    goto if_next_23;
if_next_23:;
    return 0;
}

char arrayInitLoop_1(int len_8, struct IntIntFun1 f_, struct IntMutPtrIntTuple2 array_5, int i_) {
tailrec_26:;
    char if_8;
    if ((i_ < len_8)) {
        goto then_28;
    } else {
        goto else_29;
    }
then_28:;
    int app_1 = f_.fun(f_.env, i_);
    int item_ = app_1;
    char call_18 = __mutArraySet_1(i_, item_, array_5);
    int arg_27 = len_8;
    struct IntIntFun1 arg_28 = f_;
    struct IntMutPtrIntTuple2 arg_29 = array_5;
    int arg_30 = (i_ + 1);
    len_8 = arg_27;
    f_ = arg_28;
    array_5 = arg_29;
    i_ = arg_30;
    goto tailrec_26;
else_29:;
    if_8 = 0;
    goto if_next_27;
if_next_27:;
    return 0;
}

struct UnitConstPtrIntTuple2 init_2(int len_8, struct IntUnitFun1 f_) {
    struct UnitConstPtrIntTuple2 if_9;
    if ((0 >= len_8)) {
        goto then_31;
    } else {
        goto else_32;
    }
then_31:;
    milone_assert((len_8 == 0), 24, 4);
    struct UnitConstPtrIntTuple2 call_19 = empty_4(0);
    if_9 = call_19;
    goto if_next_30;
else_32:;
    struct UnitMutPtrIntTuple2 call_20 = __mutArrayCreate_2(len_8);
    struct UnitMutPtrIntTuple2 array_5 = call_20;
    char call_21 = arrayInitLoop_2(len_8, f_, array_5, 0);
    struct UnitConstPtrIntTuple2 call_22 = __constArrayOfMut_2(array_5);
    if_9 = call_22;
    goto if_next_30;
if_next_30:;
    return if_9;
}

struct IntConstPtrIntTuple2 init_1(int len_8, struct IntIntFun1 f_) {
    struct IntConstPtrIntTuple2 if_10;
    if ((0 >= len_8)) {
        goto then_34;
    } else {
        goto else_35;
    }
then_34:;
    milone_assert((len_8 == 0), 24, 4);
    struct IntConstPtrIntTuple2 call_23 = empty_3(0);
    if_10 = call_23;
    goto if_next_33;
else_35:;
    struct IntMutPtrIntTuple2 call_24 = __mutArrayCreate_1(len_8);
    struct IntMutPtrIntTuple2 array_5 = call_24;
    char call_25 = arrayInitLoop_1(len_8, f_, array_5, 0);
    struct IntConstPtrIntTuple2 call_26 = __constArrayOfMut_1(array_5);
    if_10 = call_26;
    goto if_next_33;
if_next_33:;
    return if_10;
}

int fun_1(int i_1) {
    return i_1;
}

int fun_13(void const* env_1, int arg_2) {
    int call_27 = fun_1(arg_2);
    return call_27;
}

struct IntConstPtrIntTuple2 range_(int len_10) {
    struct IntIntFun1 fun_26 = ((struct IntIntFun1){.fun = fun_13, .env = NULL});
    struct IntConstPtrIntTuple2 call_28 = init_1(len_10, fun_26);
    return call_28;
}

int length_2(struct UnitConstPtrIntTuple2 array_6) {
    int call_29 = __constArrayLength_2(array_6);
    return call_29;
}

int length_1(struct IntConstPtrIntTuple2 array_6) {
    int call_30 = __constArrayLength_1(array_6);
    return call_30;
}

struct IntOption tryItem_1(int i_2, struct IntConstPtrIntTuple2 array_8) {
    int call_31 = length_1(array_8);
    struct IntOption if_11;
    if ((((uint32_t)i_2) < ((uint32_t)call_31))) {
        goto then_37;
    } else {
        goto else_38;
    }
then_37:;
    int call_32 = __constArrayGet_1(i_2, array_8);
    struct IntOption some_1 = ((struct IntOption){.some = true, .value = call_32});
    if_11 = some_1;
    goto if_next_36;
else_38:;
    if_11 = ((struct IntOption){.some = false});
    goto if_next_36;
if_next_36:;
    return if_11;
}

struct IntConstPtrIntTuple2 slice_1(int start_2, int endIndex_2, struct IntConstPtrIntTuple2 array_9) {
    int call_33 = length_1(array_9);
    int len_11 = call_33;
    int if_12;
    if ((start_2 >= 0)) {
        goto then_40;
    } else {
        goto else_41;
    }
then_40:;
    if_12 = start_2;
    goto if_next_39;
else_41:;
    if_12 = 0;
    goto if_next_39;
if_next_39:;
    int start_3 = if_12;
    int if_13;
    if ((endIndex_2 < len_11)) {
        goto then_43;
    } else {
        goto else_44;
    }
then_43:;
    if_13 = endIndex_2;
    goto if_next_42;
else_44:;
    if_13 = len_11;
    goto if_next_42;
if_next_42:;
    int endIndex_3 = if_13;
    struct IntConstPtrIntTuple2 if_14;
    if ((start_3 < endIndex_3)) {
        goto then_46;
    } else {
        goto else_47;
    }
then_46:;
    struct IntConstPtrIntTuple2 call_34 = __constArraySlice_1(start_3, endIndex_3, array_9);
    if_14 = call_34;
    goto if_next_45;
else_47:;
    struct IntConstPtrIntTuple2 call_35 = empty_3(0);
    if_14 = call_35;
    goto if_next_45;
if_next_45:;
    return if_14;
}

struct IntConstPtrIntTuple2 skip_1(int skipLen_, struct IntConstPtrIntTuple2 array_10) {
    int call_36 = length_1(array_10);
    struct IntConstPtrIntTuple2 call_37 = slice_1(skipLen_, call_36, array_10);
    return call_37;
}

struct IntIntConstPtrIntTuple2Tuple2Option uncons_1(struct IntConstPtrIntTuple2 array_13) {
    int call_38 = length_1(array_13);
    int len_12 = call_38;
    struct IntIntConstPtrIntTuple2Tuple2Option if_15;
    if ((len_12 == 0)) {
        goto then_49;
    } else {
        goto else_50;
    }
then_49:;
    if_15 = ((struct IntIntConstPtrIntTuple2Tuple2Option){.some = false});
    goto if_next_48;
else_50:;
    int call_39 = __constArrayGet_1(0, array_13);
    int head_ = call_39;
    struct IntConstPtrIntTuple2 call_40 = __constArraySlice_1(1, len_12, array_13);
    struct IntConstPtrIntTuple2 tail_ = call_40;
    struct IntIntConstPtrIntTuple2Tuple2 tuple_8 = ((struct IntIntConstPtrIntTuple2Tuple2){.t0 = head_, .t1 = tail_});
    struct IntIntConstPtrIntTuple2Tuple2Option some_2 = ((struct IntIntConstPtrIntTuple2Tuple2Option){.some = true, .value = tuple_8});
    if_15 = some_2;
    goto if_next_48;
if_next_48:;
    return if_15;
}

int fun_25(struct IntIntIntFun2 f_1, struct IntConstPtrIntTuple2 array_14, int i_3) {
    int call_41 = __constArrayGet_1(i_3, array_14);
    int app_2 = f_1.fun(f_1.env, i_3, call_41);
    return app_2;
}

int fun_24(void const* env_2, int arg_3) {
    struct IntIntIntFun2 arg_4 = (*(((struct IntIntIntFun2IntConstPtrIntTuple2Tuple2 const*)env_2))).t0;
    struct IntConstPtrIntTuple2 arg_5 = (*(((struct IntIntIntFun2IntConstPtrIntTuple2Tuple2 const*)env_2))).t1;
    int call_42 = fun_25(arg_4, arg_5, arg_3);
    return call_42;
}

struct IntConstPtrIntTuple2 mapi_1(struct IntIntIntFun2 f_1, struct IntConstPtrIntTuple2 array_14) {
    int call_43 = length_1(array_14);
    struct IntIntIntFun2IntConstPtrIntTuple2Tuple2 tuple_9 = ((struct IntIntIntFun2IntConstPtrIntTuple2Tuple2){.t0 = f_1, .t1 = array_14});
    void const* box_ = milone_mem_alloc(1, sizeof(struct IntIntIntFun2IntConstPtrIntTuple2Tuple2));
    (*(((struct IntIntIntFun2IntConstPtrIntTuple2Tuple2*)box_))) = tuple_9;
    struct IntIntFun1 fun_27 = ((struct IntIntFun1){.fun = fun_24, .env = box_});
    struct IntConstPtrIntTuple2 call_44 = init_1(call_43, fun_27);
    return call_44;
}

int chooseLoop_1(struct IntIntOptionFun1 f_3, struct IntConstPtrIntTuple2 src_1, int len_13, struct IntMutPtrIntTuple2 dest_1, int di_, int si_) {
tailrec_51:;
    int if_16;
    if ((si_ == len_13)) {
        goto then_53;
    } else {
        goto else_54;
    }
then_53:;
    if_16 = di_;
    goto if_next_52;
else_54:;
    int match_;
    int call_45 = __constArrayGet_1(si_, src_1);
    struct IntOption app_3 = f_3.fun(f_3.env, call_45);
    if ((!(app_3.some))) goto next_56;
    int value_1 = app_3.value;
    char call_46 = __mutArraySet_1(di_, value_1, dest_1);
    struct IntIntOptionFun1 arg_31 = f_3;
    struct IntConstPtrIntTuple2 arg_32 = src_1;
    int arg_33 = len_13;
    struct IntMutPtrIntTuple2 arg_34 = dest_1;
    int arg_35 = (di_ + 1);
    int arg_36 = (si_ + 1);
    f_3 = arg_31;
    src_1 = arg_32;
    len_13 = arg_33;
    dest_1 = arg_34;
    di_ = arg_35;
    si_ = arg_36;
    goto tailrec_51;
next_56:;
    if (app_3.some) goto next_57;
    struct IntIntOptionFun1 arg_37 = f_3;
    struct IntConstPtrIntTuple2 arg_38 = src_1;
    int arg_39 = len_13;
    struct IntMutPtrIntTuple2 arg_40 = dest_1;
    int arg_41 = di_;
    int arg_42 = (si_ + 1);
    f_3 = arg_37;
    src_1 = arg_38;
    len_13 = arg_39;
    dest_1 = arg_40;
    di_ = arg_41;
    si_ = arg_42;
    goto tailrec_51;
next_57:;
    exit(1);
end_match_55:;
    if_16 = match_;
    goto if_next_52;
if_next_52:;
    return if_16;
}

struct IntConstPtrIntTuple2 choose_1(struct IntIntOptionFun1 f_3, struct IntConstPtrIntTuple2 src_1) {
    int call_47 = length_1(src_1);
    int len_13 = call_47;
    struct IntMutPtrIntTuple2 call_48 = __mutArrayCreate_1(len_13);
    struct IntMutPtrIntTuple2 dest_1 = call_48;
    int call_49 = chooseLoop_1(f_3, src_1, len_13, dest_1, 0, 0);
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
    struct IntMutPtrIntTuple2 call_51 = __mutArraySlice_1(0, di_1, dest_1);
    struct IntConstPtrIntTuple2 call_52 = __constArrayOfMut_1(call_51);
    if_17 = call_52;
    goto if_next_58;
if_next_58:;
    return if_17;
}

int arrayFoldLoop_1(struct IntIntIntFun2 folder_, struct IntConstPtrIntTuple2 array_16, int len_14, int state_1, int i_5) {
tailrec_61:;
    int if_18;
    if ((i_5 == len_14)) {
        goto then_63;
    } else {
        goto else_64;
    }
then_63:;
    if_18 = state_1;
    goto if_next_62;
else_64:;
    struct IntIntIntFun2 arg_43 = folder_;
    struct IntConstPtrIntTuple2 arg_44 = array_16;
    int arg_45 = len_14;
    int call_53 = __constArrayGet_1(i_5, array_16);
    int app_4 = folder_.fun(folder_.env, state_1, call_53);
    int arg_46 = app_4;
    int arg_47 = (i_5 + 1);
    folder_ = arg_43;
    array_16 = arg_44;
    len_14 = arg_45;
    state_1 = arg_46;
    i_5 = arg_47;
    goto tailrec_61;
if_next_62:;
    return if_18;
}

int fold_1(struct IntIntIntFun2 folder_, int state_, struct IntConstPtrIntTuple2 array_16) {
    int call_54 = length_1(array_16);
    int len_14 = call_54;
    int call_55 = arrayFoldLoop_1(folder_, array_16, len_14, state_, 0);
    return call_55;
}

int listLengthLoop_1(int acc_, struct IntList const* xs_2) {
tailrec_65:;
    int match_1;
    if ((!((!(xs_2))))) goto next_67;
    match_1 = acc_;
    goto end_match_66;
next_67:;
    if ((!(xs_2))) goto next_68;
    struct IntList const* xs_3 = xs_2->tail;
    int arg_48 = (acc_ + 1);
    struct IntList const* arg_49 = xs_3;
    acc_ = arg_48;
    xs_2 = arg_49;
    goto tailrec_65;
next_68:;
    exit(1);
end_match_66:;
    return match_1;
}

char ofListLoop_1(int len_15, struct IntMutPtrIntTuple2 dest_2, int i_6, struct IntList const* xs_4) {
tailrec_69:;
    char match_2;
    if ((!((!(xs_4))))) goto next_71;
    milone_assert((i_6 == len_15), 186, 12);
    match_2 = 0;
    goto end_match_70;
next_71:;
    if ((!(xs_4))) goto next_72;
    int x_ = xs_4->head;
    struct IntList const* xs_5 = xs_4->tail;
    char call_56 = __mutArraySet_1(i_6, x_, dest_2);
    int arg_50 = len_15;
    struct IntMutPtrIntTuple2 arg_51 = dest_2;
    int arg_52 = (i_6 + 1);
    struct IntList const* arg_53 = xs_5;
    len_15 = arg_50;
    dest_2 = arg_51;
    i_6 = arg_52;
    xs_4 = arg_53;
    goto tailrec_69;
next_72:;
    exit(1);
end_match_70:;
    return 0;
}

struct IntConstPtrIntTuple2 ofList_1(struct IntList const* xs_1) {
    int call_57 = listLengthLoop_1(0, xs_1);
    int len_15 = call_57;
    struct IntMutPtrIntTuple2 call_58 = __mutArrayCreate_1(len_15);
    struct IntMutPtrIntTuple2 dest_2 = call_58;
    char call_59 = ofListLoop_1(len_15, dest_2, 0, xs_1);
    struct IntConstPtrIntTuple2 call_60 = __constArrayOfMut_1(dest_2);
    return call_60;
}

struct IntList const* toListLoop_1(struct IntConstPtrIntTuple2 array_17, struct IntList const* acc_1, int i_7) {
tailrec_73:;
    struct IntList const* if_19;
    if ((i_7 == 0)) {
        goto then_75;
    } else {
        goto else_76;
    }
then_75:;
    if_19 = acc_1;
    goto if_next_74;
else_76:;
    struct IntConstPtrIntTuple2 arg_54 = array_17;
    int call_61 = __constArrayGet_1((i_7 - 1), array_17);
    struct IntList const* list_ = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_))) = ((struct IntList){.head = call_61, .tail = acc_1});
    struct IntList const* arg_55 = list_;
    int arg_56 = (i_7 - 1);
    array_17 = arg_54;
    acc_1 = arg_55;
    i_7 = arg_56;
    goto tailrec_73;
if_next_74:;
    return if_19;
}

struct IntList const* toList_1(struct IntConstPtrIntTuple2 array_17) {
    int call_62 = length_1(array_17);
    struct IntList const* call_63 = toListLoop_1(array_17, NULL, call_62);
    return call_63;
}

int get_1(int i_8, struct IntConstPtrIntTuple2 array_18) {
    int match_3;
    struct IntOption call_64 = tryItem_1(i_8, array_18);
    if ((!(call_64.some))) goto next_78;
    int it_ = call_64.value;
    match_3 = it_;
    goto end_match_77;
next_78:;
    if (call_64.some) goto next_79;
    int call_65 = length_1(array_18);
    printf("out of range: i=%d len=%d\n", i_8, call_65);
    milone_assert(false, 9, 6);
    exit(1);
next_79:;
    exit(1);
end_match_77:;
    return match_3;
}

char fun_5(int arg_57) {
    milone_assert(false, 13, 45);
    return 0;
}

char fun_17(void const* env_5, int arg_11) {
    char call_66 = fun_5(arg_11);
    return 0;
}

int fun_6(int n_) {
    return ((n_ + 1) * 3);
}

int fun_18(void const* env_6, int arg_12) {
    int call_67 = fun_6(arg_12);
    return call_67;
}

char initTest_(char arg_58) {
    struct IntUnitFun1 fun_28 = ((struct IntUnitFun1){.fun = fun_17, .env = NULL});
    struct UnitConstPtrIntTuple2 call_68 = init_2(0, fun_28);
    struct UnitConstPtrIntTuple2 emptyArray_ = call_68;
    int call_69 = length_2(emptyArray_);
    milone_assert((call_69 == 0), 14, 2);
    struct IntIntFun1 fun_29 = ((struct IntIntFun1){.fun = fun_18, .env = NULL});
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

char rangeTest_(char arg_59) {
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

int at_(int bad_, int i_9, struct IntConstPtrIntTuple2 array_19) {
    int match_4;
    struct IntOption call_80 = tryItem_1(i_9, array_19);
    if ((!(call_80.some))) goto next_81;
    int it_1 = call_80.value;
    match_4 = it_1;
    goto end_match_80;
next_81:;
    if (call_80.some) goto next_82;
    match_4 = bad_;
    goto end_match_80;
next_82:;
    exit(1);
end_match_80:;
    return match_4;
}

char tryItemTest_(char arg_60) {
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

char sliceTest_(char arg_61) {
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

int fun_7(int n_1) {
    return (n_1 + 1);
}

int fun_19(void const* env_7, int arg_13) {
    int call_100 = fun_7(arg_13);
    return call_100;
}

char unconsTest_(char arg_62) {
    struct IntIntFun1 fun_30 = ((struct IntIntFun1){.fun = fun_19, .env = NULL});
    struct IntConstPtrIntTuple2 call_101 = init_1(3, fun_30);
    struct IntConstPtrIntTuple2 a123_ = call_101;
    char match_5;
    struct IntIntConstPtrIntTuple2Tuple2Option call_102 = uncons_1(a123_);
    if (call_102.some) goto next_84;
    milone_assert(false, 71, 12);
    match_5 = 0;
    goto end_match_83;
next_84:;
    if ((!(call_102.some))) goto next_85;
    int n1_ = call_102.value.t0;
    struct IntConstPtrIntTuple2 a23_ = call_102.value.t1;
    milone_assert((n1_ == 1), 73, 6);
    int call_103 = length_1(a23_);
    milone_assert((call_103 == 2), 74, 6);
    char match_6;
    struct IntConstPtrIntTuple2 call_104 = skip_1(1, a23_);
    struct IntIntConstPtrIntTuple2Tuple2Option call_105 = uncons_1(call_104);
    if (call_105.some) goto next_87;
    milone_assert(false, 77, 16);
    match_6 = 0;
    goto end_match_86;
next_87:;
    if ((!(call_105.some))) goto next_88;
    int n3_ = call_105.value.t0;
    struct IntConstPtrIntTuple2 empty_1 = call_105.value.t1;
    milone_assert((n3_ == 3), 79, 10);
    int call_106 = length_1(empty_1);
    milone_assert((call_106 == 0), 80, 10);
    char match_7;
    struct IntIntConstPtrIntTuple2Tuple2Option call_107 = uncons_1(empty_1);
    if (call_107.some) goto next_90;
    match_7 = 0;
    goto end_match_89;
next_90:;
    if ((!(call_107.some))) goto next_91;
    milone_assert(false, 84, 22);
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

int fun_8(int i_10, int n_2) {
    return ((i_10 * 10) + n_2);
}

int fun_20(void const* env_8, int arg_14, int arg_15) {
    int call_108 = fun_8(arg_14, arg_15);
    return call_108;
}

char mapTest_(char arg_63) {
    struct IntIntIntFun2 fun_31 = ((struct IntIntIntFun2){.fun = fun_20, .env = NULL});
    struct IntConstPtrIntTuple2 call_109 = range_(3);
    struct IntConstPtrIntTuple2 call_110 = mapi_1(fun_31, call_109);
    struct IntConstPtrIntTuple2 mapped_ = call_110;
    int call_111 = length_1(mapped_);
    milone_assert((call_111 == 3), 90, 2);
    int call_112 = get_1(0, mapped_);
    milone_assert((call_112 == 0), 91, 2);
    int call_113 = get_1(1, mapped_);
    milone_assert((call_113 == 11), 92, 2);
    int call_114 = get_1(2, mapped_);
    milone_assert((call_114 == 22), 93, 2);
    return 0;
}

struct IntOption fun_9(int n_3) {
    struct IntOption if_20;
    if (((n_3 % 2) == 0)) {
        goto then_93;
    } else {
        goto else_94;
    }
then_93:;
    struct IntOption some_3 = ((struct IntOption){.some = true, .value = (n_3 * 2)});
    if_20 = some_3;
    goto if_next_92;
else_94:;
    if_20 = ((struct IntOption){.some = false});
    goto if_next_92;
if_next_92:;
    return if_20;
}

struct IntOption fun_21(void const* env_9, int arg_16) {
    struct IntOption call_115 = fun_9(arg_16);
    return call_115;
}

struct IntOption fun_10(int arg_64) {
    return ((struct IntOption){.some = false});
}

struct IntOption fun_22(void const* env_10, int arg_17) {
    struct IntOption call_116 = fun_10(arg_17);
    return call_116;
}

char chooseTest_(char arg_65) {
    struct IntIntOptionFun1 fun_32 = ((struct IntIntOptionFun1){.fun = fun_21, .env = NULL});
    struct IntConstPtrIntTuple2 call_117 = range_(6);
    struct IntConstPtrIntTuple2 call_118 = choose_1(fun_32, call_117);
    struct IntConstPtrIntTuple2 chosen_ = call_118;
    int call_119 = length_1(chosen_);
    milone_assert((call_119 == 3), 99, 2);
    int call_120 = get_1(0, chosen_);
    milone_assert((call_120 == 0), 100, 2);
    int call_121 = get_1(1, chosen_);
    milone_assert((call_121 == 4), 101, 2);
    int call_122 = get_1(2, chosen_);
    milone_assert((call_122 == 8), 102, 2);
    struct IntIntOptionFun1 fun_33 = ((struct IntIntOptionFun1){.fun = fun_22, .env = NULL});
    struct IntConstPtrIntTuple2 call_123 = range_(3);
    struct IntConstPtrIntTuple2 call_124 = choose_1(fun_33, call_123);
    struct IntConstPtrIntTuple2 empty_2 = call_124;
    int call_125 = length_1(empty_2);
    milone_assert((call_125 == 0), 107, 2);
    return 0;
}

int fun_11(int state_2, int i_11) {
    return ((state_2 * 10) + (i_11 + 1));
}

int fun_23(void const* env_11, int arg_18, int arg_19) {
    int call_126 = fun_11(arg_18, arg_19);
    return call_126;
}

char foldTest_(char arg_66) {
    struct IntIntIntFun2 fun_34 = ((struct IntIntIntFun2){.fun = fun_23, .env = NULL});
    struct IntConstPtrIntTuple2 call_127 = range_(3);
    int call_128 = fold_1(fun_34, 0, call_127);
    int sum_ = call_128;
    milone_assert((sum_ == 123), 113, 2);
    return 0;
}

char ofListTest_(char arg_67) {
    struct IntList const* list_3 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_3))) = ((struct IntList){.head = 5, .tail = NULL});
    struct IntList const* list_2 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_2))) = ((struct IntList){.head = 3, .tail = list_3});
    struct IntList const* list_1 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_1))) = ((struct IntList){.head = 2, .tail = list_2});
    struct IntConstPtrIntTuple2 call_129 = ofList_1(list_1);
    struct IntConstPtrIntTuple2 ol_ = call_129;
    int call_130 = length_1(ol_);
    milone_assert((call_130 == 3), 126, 2);
    int call_131 = get_1(0, ol_);
    milone_assert((call_131 == 2), 127, 2);
    int call_132 = get_1(1, ol_);
    milone_assert((call_132 == 3), 128, 2);
    int call_133 = get_1(2, ol_);
    milone_assert((call_133 == 5), 129, 2);
    return 0;
}

char toListTest_(char arg_68) {
    struct IntConstPtrIntTuple2 call_134 = range_(3);
    struct IntList const* call_135 = toList_1(call_134);
    struct IntList const* tl_ = call_135;
    char match_8;
    if ((!(tl_))) goto next_96;
    int n0_ = tl_->head;
    if ((!(tl_->tail))) goto next_96;
    int n1_1 = tl_->tail->head;
    if ((!(tl_->tail->tail))) goto next_96;
    int n2_ = tl_->tail->tail->head;
    if ((!((!(tl_->tail->tail->tail))))) goto next_96;
    milone_assert((n0_ == 0), 136, 6);
    milone_assert((n1_1 == 1), 137, 6);
    milone_assert((n2_ == 2), 138, 6);
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
    char call_136 = initTest_(0);
    char call_137 = rangeTest_(0);
    char call_138 = tryItemTest_(0);
    char call_139 = sliceTest_(0);
    char call_140 = unconsTest_(0);
    char call_141 = mapTest_(0);
    char call_142 = chooseTest_(0);
    char call_143 = foldTest_(0);
    char call_144 = ofListTest_(0);
    char call_145 = toListTest_(0);
    return 0;
}
