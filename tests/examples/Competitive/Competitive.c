#include "milone.h"

int scanInt_(int arg_35);

void* rawIntArrayNew_(int len_);

int rawIntArrayGet_(void* array_, int index_);

void* rawIntArraySet_(void* array_1, int index_1, int value_);

void* rawMemoryCopy_(void* dest_, void* src_, int size_);

int ignore_1(void* arg_36);

struct StringList;

int listIsEmpty_1(struct StringList* xs_);

struct StringStringStringFun2;

struct StringStringStringFun2List;

int listIsEmpty_4(struct StringStringStringFun2List* xs_);

struct IntList;

int listIsEmpty_3(struct IntList* xs_);

struct IntIntIntFun2;

struct IntIntIntFun2List;

int listIsEmpty_2(struct IntIntIntFun2List* xs_);

struct IntIntIntObjectObjectTuple5;

struct IntIntIntObjectObjectTuple5List;

int listIsEmpty_5(struct IntIntIntObjectObjectTuple5List* xs_);

struct StringIntIntObjectObjectTuple5;

struct StringIntIntObjectObjectTuple5List;

int listIsEmpty_6(struct StringIntIntObjectObjectTuple5List* xs_);

int go_34(int len_1, struct StringList* xs_2);

int go_33(int len_1, struct IntList* xs_2);

int listLength_2(struct StringList* xs_1);

int listLength_1(struct IntList* xs_1);

struct IntList* go_39(struct IntList* acc_, struct IntList* xs_5);

struct StringList* go_38(struct StringList* acc_, struct StringList* xs_5);

struct IntList* listRev_2(struct IntList* xs_4);

struct StringList* listRev_1(struct StringList* xs_4);

struct IntIntBoolFun2;

struct IntListIntListTuple2;

int go_32(struct IntIntBoolFun2 itemEq_, struct IntList* xs_8, struct IntList* ys_1);

struct StringStringBoolFun2;

struct StringListStringListTuple2;

int go_31(struct StringStringBoolFun2 itemEq_, struct StringList* xs_8, struct StringList* ys_1);

int listEq_2(struct IntIntBoolFun2 itemEq_, struct IntList* xs_7, struct IntList* ys_);

int listEq_1(struct StringStringBoolFun2 itemEq_, struct StringList* xs_7, struct StringList* ys_);

struct IntList* go_30(int len_2, int item_, struct IntList* acc_1, int i_);

struct IntList* listReplicate_1(int item_, int len_2);

struct IntIntFun1;

struct IntList* go_29(struct IntIntFun1 gen_, int len_3, struct IntList* acc_2, int i_1);

struct IntList* listInit_1(int len_3, struct IntIntFun1 gen_);

struct StringStringListTuple2;

struct StringStringListTuple2 go_5(struct StringList* xs_11, int xn_);

struct String strConcat_(struct StringList* xs_10);

int intEq_(int first_, int second_);

int intMin_(int first_1, int second_1);

int intMax_(int first_2, int second_2);

int strEq_(struct String first_3, struct String second_3);

int failwith_1(struct String msg_);

int fun_23(int arg_59);

int fun_3(void* env_, int arg_);

struct IntList* scanIntList_(int len_4);

struct IntObjectFun1;

struct ObjectIntIntFun2;

struct ObjectIntIntObjectFun3;

struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6;

struct IntObjectFun1 typeToArrayNew_1(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6 arg_60);

struct ObjectIntIntFun2 typeToArrayGet_1(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6 arg_61);

struct ObjectIntIntObjectFun3 typeToArraySet_1(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6 arg_62);

void* fun_4(void* env_1, int arg_1);

int fun_5(void* env_2, void* arg_2, int arg_3);

void* fun_6(void* env_3, void* arg_4, int arg_5, int arg_6);

struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6ObjectIntIntObjectTuple5;

int vectorToLength_1(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6ObjectIntIntObjectTuple5 arg_63);

struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6ObjectIntIntObjectTuple5 vectorNew_1(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6 itemTy_, int len_6);

int vectorCheckIndex_1(int index_2, struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6ObjectIntIntObjectTuple5 self_);

int vectorGet_1(int index_3, struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6ObjectIntIntObjectTuple5 self_1);

int vectorSet_1(int index_4, int value_1, struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6ObjectIntIntObjectTuple5 self_2);

int go_28(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6ObjectIntIntObjectTuple5 v_, int len_9, int i_2, struct IntList* xs_19);

struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6ObjectIntIntObjectTuple5 vectorOfList_1(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6 ty_, struct IntList* xs_18);

int go_7(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6ObjectIntIntObjectTuple5 v_1, int len_10, int i_3);

struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6ObjectIntIntObjectTuple5 scanIntVector_(int len_10);

int refCase_(int arg_71);

int vectorOfListTest_(int arg_72);

int vectorTest_(int arg_73);

struct IntIntTuple2;

int intervalIsDisjoint_(struct IntIntTuple2 first_4, struct IntIntTuple2 second_4);

int intervalCovers_(struct IntIntTuple2 first_5, struct IntIntTuple2 second_5);

struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4;

struct StringStringStringFun2 segItemTypeToAppend_2(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 arg_74);

struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4;

struct IntIntIntFun2 segItemTypeToAppend_1(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 arg_75);

struct IntIntIntObjectObjectTuple5 segItemTypeToEmptyNode_2(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 arg_76);

struct StringIntIntObjectObjectTuple5 segItemTypeToEmptyNode_1(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 arg_77);

void* segItemTypeToNoChildren_1(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 arg_78);

void* segItemTypeToNoChildren_2(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 arg_79);

int segItemTypeToEmptyItem_1(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_4);

struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2;

struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 segItemTypeNew_2(struct String emptyItem_, struct StringStringStringFun2 append_1);

struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2;

struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 segItemTypeNew_1(int emptyItem_, struct IntIntIntFun2 append_1);

struct StringIntIntObjectObjectTuple5 segNodeNewEmpty_2(struct String emptyItem_1);

struct IntIntIntObjectObjectTuple5 segNodeNewEmpty_1(int emptyItem_1);

struct IntIntIntObjectObjectTuple5 segNodeNewLeaf_1(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_6, int item_1);

struct StringIntIntObjectObjectTuple5 segNodeNewLeaf_2(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_6, struct String item_1);

struct IntIntIntObjectObjectTuple5 doNew_1(struct IntIntIntObjectObjectTuple5 right_, struct IntIntIntObjectObjectTuple5 left_, struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_7, int arg_80);

struct StringIntIntObjectObjectTuple5 doNew_2(struct StringIntIntObjectObjectTuple5 right_, struct StringIntIntObjectObjectTuple5 left_, struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_7, int arg_81);

struct IntIntIntObjectObjectTuple5 segNodeNew_1(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_7, struct IntIntIntObjectObjectTuple5 left_, struct IntIntIntObjectObjectTuple5 right_);

struct StringIntIntObjectObjectTuple5 segNodeNew_2(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_7, struct StringIntIntObjectObjectTuple5 left_, struct StringIntIntObjectObjectTuple5 right_);

int segNodeToItem_1(struct IntIntIntObjectObjectTuple5 node_);

int segNodeToLength_1(struct IntIntIntObjectObjectTuple5 node_1);

int segNodeToLength_2(struct StringIntIntObjectObjectTuple5 node_1);

int segNodeToHeight_1(struct IntIntIntObjectObjectTuple5 node_2);

int segNodeToHeight_2(struct StringIntIntObjectObjectTuple5 node_2);

struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 segNodeToChildren_1(struct IntIntIntObjectObjectTuple5 node_3);

struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2 segNodeToChildren_2(struct StringIntIntObjectObjectTuple5 node_3);

int segNodeIsEmpty_1(struct IntIntIntObjectObjectTuple5 node_4);

struct IntIntIntObjectObjectTuple5 segNodeWithLeft_1(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_8, struct IntIntIntObjectObjectTuple5 newLeft_, struct IntIntIntObjectObjectTuple5 node_5);

struct StringIntIntObjectObjectTuple5 segNodeWithLeft_2(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_8, struct StringIntIntObjectObjectTuple5 newLeft_, struct StringIntIntObjectObjectTuple5 node_5);

struct IntIntIntObjectObjectTuple5 segNodeWithRight_1(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_9, struct IntIntIntObjectObjectTuple5 newRight_, struct IntIntIntObjectObjectTuple5 node_6);

struct StringIntIntObjectObjectTuple5 segNodeWithRight_2(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_9, struct StringIntIntObjectObjectTuple5 newRight_, struct StringIntIntObjectObjectTuple5 node_6);

struct IntIntIntObjectObjectTuple5 rotateLeft_1(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_10, struct IntIntIntObjectObjectTuple5 node_8);

struct StringIntIntObjectObjectTuple5 rotateLeft_2(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_10, struct StringIntIntObjectObjectTuple5 node_8);

struct IntIntIntObjectObjectTuple5 rotateRight_1(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_10, struct IntIntIntObjectObjectTuple5 node_9);

struct StringIntIntObjectObjectTuple5 rotateRight_2(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_10, struct StringIntIntObjectObjectTuple5 node_9);

struct IntIntIntObjectObjectTuple5 doubleLeft_1(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_10, struct IntIntIntObjectObjectTuple5 node_10);

struct StringIntIntObjectObjectTuple5 doubleLeft_2(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_10, struct StringIntIntObjectObjectTuple5 node_10);

struct IntIntIntObjectObjectTuple5 doubleRight_1(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_10, struct IntIntIntObjectObjectTuple5 node_11);

struct StringIntIntObjectObjectTuple5 doubleRight_2(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_10, struct StringIntIntObjectObjectTuple5 node_11);

int toBalance_1(struct IntIntIntObjectObjectTuple5 node_12);

int toBalance_2(struct StringIntIntObjectObjectTuple5 node_12);

struct IntIntIntObjectObjectTuple5 segNodeMakeBalanced_1(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_10, struct IntIntIntObjectObjectTuple5 node_7);

struct StringIntIntObjectObjectTuple5 segNodeMakeBalanced_2(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_10, struct StringIntIntObjectObjectTuple5 node_7);

struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3;

struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 segTreeNew_2(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_11);

struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4StringIntIntObjectObjectTuple5ObjectTuple3;

struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4StringIntIntObjectObjectTuple5ObjectTuple3 segTreeNew_1(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_11);

struct IntIntIntObjectObjectTuple5 segTreeToRoot_1(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 self_4);

struct StringIntIntObjectObjectTuple5 segTreeToRoot_2(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4StringIntIntObjectObjectTuple5ObjectTuple3 self_4);

int segTreeToLength_1(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 self_5);

int segTreeToLength_2(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4StringIntIntObjectObjectTuple5ObjectTuple3 self_5);

int segTreeToHeight_1(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 self_6);

int go_27(int index_6, struct IntIntIntObjectObjectTuple5 node_14);

struct String go_37(int index_6, struct StringIntIntObjectObjectTuple5 node_14);

int segTreeGet_1(int index_5, struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 self_8);

struct String segTreeGet_2(int index_5, struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4StringIntIntObjectObjectTuple5ObjectTuple3 self_8);

int go_26(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_12, struct IntIntTuple2 e_, struct IntIntTuple2 q_, struct IntIntIntObjectObjectTuple5 node_15);

int segTreeSum_1(int ql_, int qr_, struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 self_9);

struct IntIntIntObjectObjectTuple5 go_25(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_13, int newItem_, int index_8, struct IntIntIntObjectObjectTuple5 node_16);

struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 segTreeSet_1(int index_7, int newItem_, struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 self_10);

struct IntIntIntObjectObjectTuple5 go_24(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_14, int newItem_1, int index_10, struct IntIntIntObjectObjectTuple5 node_17);

struct StringIntIntObjectObjectTuple5 go_36(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_14, struct String newItem_1, int index_10, struct StringIntIntObjectObjectTuple5 node_17);

struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 segTreeInsert_1(int index_9, int newItem_1, struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 self_11);

struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4StringIntIntObjectObjectTuple5ObjectTuple3 segTreeInsert_2(int index_9, struct String newItem_1, struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4StringIntIntObjectObjectTuple5ObjectTuple3 self_11);

struct IntIntIntObjectObjectTuple5 go_35(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_15, int index_12, struct IntIntIntObjectObjectTuple5 node_18);

struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 segTreeRemove_1(int index_11, struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 self_12);

struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4StringIntIntObjectObjectTuple5ObjectTuple3 segTreePush_2(struct String value_4, struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4StringIntIntObjectObjectTuple5ObjectTuple3 self_13);

struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 segTreePush_1(int value_4, struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 self_13);

struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 segTreePop_1(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 self_14);

struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 go_23(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 t_2, struct IntList* xs_22);

struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 segTreeOfList_1(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_16, struct IntList* xs_21);

struct IntList* go_22(int len_19, struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 v_4, struct IntList* acc_3, int i_4);

struct StringList* go_21(int len_19, struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4StringIntIntObjectObjectTuple5ObjectTuple3 v_4, struct StringList* acc_3, int i_4);

struct IntList* segTreeToList_2(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 v_4);

struct StringList* segTreeToList_1(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4StringIntIntObjectObjectTuple5ObjectTuple3 v_4);

int intAdd_(int x_8, int y_3);

int fun_7(void* env_4, int arg_7, int arg_8);

struct String strAdd_(struct String x_9, struct String y_4);

struct String fun_8(void* env_5, struct String arg_9, struct String arg_10);

int fun_9(void* env_6, int arg_11, int arg_12);

int fun_10(void* env_7, int arg_13, int arg_14);

int fun_11(void* env_8, int arg_15, int arg_16);

int fun_12(void* env_9, int arg_17, int arg_18);

int fun_13(void* env_10, int arg_19, int arg_20);

int testPushPop_(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 segItemTypeInt_, int arg_100);

int fun_14(void* env_11, int arg_21, int arg_22);

int fun_15(void* env_12, int arg_23, int arg_24);

int testSet_(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 segItemTypeInt_, int arg_101);

int testSum_(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 segItemTypeInt_, int arg_102);

int sum_(int r_1, int l_1, int acc_4, int i_5, struct IntList* xs_25);

int go_15(int n_1, struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 v_13, struct IntList* xs_24, int l_1, int r_1);

int testSumMore_(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 segItemTypeInt_, int arg_118);

int testBalance_(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 segItemTypeInt_, int arg_119);

int fun_16(void* env_13, struct String arg_25, struct String arg_26);

int testPolymorphic_(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 segItemTypeStr_, int arg_120);

int segTreeTest_(int arg_121);

int abc140aSolve_(int n_2);

int abc140aTest_(int arg_122);

int abc140aMain_(int arg_123);

int fun_22(int arg_124, int arg_125);

int fun_17(void* env_14, int arg_27, int arg_28);

int go_16(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 c_1, struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 b_1, struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 a_1, int n_4, int sum_1, int i_6);

int abc140bSolve_(int n_4, struct IntList* a_, struct IntList* b_, struct IntList* c_);

int f_(struct IntList* a_2, struct IntList* b_2, struct IntList* c_2);

int case1_(int arg_132);

int case2_(int arg_133);

int case3_(int arg_134);

int abc140bTest_(int arg_135);

int abc140bMain_(int arg_136);

int fun_21(int arg_137, int arg_138);

int fun_18(void* env_15, int arg_29, int arg_30);

int fun_19(void* env_16, int arg_31, int arg_32);

int fun_20(void* env_17, int arg_33, int arg_34);

struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 go_20(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 perm_2, int n_7, struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 pos_1, int i_7);

int go_19(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 pos_, int n_7, int sum_2, struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 prev_1, struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 next_1, int p_);

int abc140eSolve_(int n_7, struct IntList* perm_);

int solve_(struct IntList* p_1, int expected_1);

int abc140eTest_(int arg_149);

int abc140eMain_(int arg_150);

static void* unitObj_;

static struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6 typeInt_;

int main();

int scanInt_(int arg_35) {
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

int ignore_1(void* arg_36) {
    return 0;
}

struct StringList {
    struct String head;
    struct StringList* tail;
};

int listIsEmpty_1(struct StringList* xs_) {
    int if_;
    if ((!(xs_))) {
        goto nil_cl_2;
    } else {
        goto cons_cl_3;
    }
nil_cl_2:;
    if_ = 1;
    goto if_next_1;
cons_cl_3:;
    if_ = 0;
    goto if_next_1;
if_next_1:;
    return if_;
}

struct StringStringStringFun2 {
    struct String(*fun)(void*, struct String, struct String);
    void* env;
};

struct StringStringStringFun2List {
    struct StringStringStringFun2 head;
    struct StringStringStringFun2List* tail;
};

int listIsEmpty_4(struct StringStringStringFun2List* xs_) {
    int if_1;
    if ((!(xs_))) {
        goto nil_cl_5;
    } else {
        goto cons_cl_6;
    }
nil_cl_5:;
    if_1 = 1;
    goto if_next_4;
cons_cl_6:;
    if_1 = 0;
    goto if_next_4;
if_next_4:;
    return if_1;
}

struct IntList {
    int head;
    struct IntList* tail;
};

int listIsEmpty_3(struct IntList* xs_) {
    int if_2;
    if ((!(xs_))) {
        goto nil_cl_8;
    } else {
        goto cons_cl_9;
    }
nil_cl_8:;
    if_2 = 1;
    goto if_next_7;
cons_cl_9:;
    if_2 = 0;
    goto if_next_7;
if_next_7:;
    return if_2;
}

struct IntIntIntFun2 {
    int(*fun)(void*, int, int);
    void* env;
};

struct IntIntIntFun2List {
    struct IntIntIntFun2 head;
    struct IntIntIntFun2List* tail;
};

int listIsEmpty_2(struct IntIntIntFun2List* xs_) {
    int if_3;
    if ((!(xs_))) {
        goto nil_cl_11;
    } else {
        goto cons_cl_12;
    }
nil_cl_11:;
    if_3 = 1;
    goto if_next_10;
cons_cl_12:;
    if_3 = 0;
    goto if_next_10;
if_next_10:;
    return if_3;
}

struct IntIntIntObjectObjectTuple5 {
    int t0;
    int t1;
    int t2;
    void* t3;
    void* t4;
};

struct IntIntIntObjectObjectTuple5List {
    struct IntIntIntObjectObjectTuple5 head;
    struct IntIntIntObjectObjectTuple5List* tail;
};

int listIsEmpty_5(struct IntIntIntObjectObjectTuple5List* xs_) {
    int if_4;
    if ((!(xs_))) {
        goto nil_cl_14;
    } else {
        goto cons_cl_15;
    }
nil_cl_14:;
    if_4 = 1;
    goto if_next_13;
cons_cl_15:;
    if_4 = 0;
    goto if_next_13;
if_next_13:;
    return if_4;
}

struct StringIntIntObjectObjectTuple5 {
    struct String t0;
    int t1;
    int t2;
    void* t3;
    void* t4;
};

struct StringIntIntObjectObjectTuple5List {
    struct StringIntIntObjectObjectTuple5 head;
    struct StringIntIntObjectObjectTuple5List* tail;
};

int listIsEmpty_6(struct StringIntIntObjectObjectTuple5List* xs_) {
    int if_5;
    if ((!(xs_))) {
        goto nil_cl_17;
    } else {
        goto cons_cl_18;
    }
nil_cl_17:;
    if_5 = 1;
    goto if_next_16;
cons_cl_18:;
    if_5 = 0;
    goto if_next_16;
if_next_16:;
    return if_5;
}

int go_34(int len_1, struct StringList* xs_2) {
tailrec_19:;
    int match_;
    if ((!((!(xs_2))))) goto next_21;
    match_ = len_1;
    goto end_match_20;
next_21:;
    if ((!(xs_2))) goto next_22;
    struct StringList* xs_3 = xs_2->tail;
    int arg_37 = (len_1 + 1);
    struct StringList* arg_38 = xs_3;
    len_1 = arg_37;
    xs_2 = arg_38;
    goto tailrec_19;
    match_ = 0;
    goto end_match_20;
next_22:;
    exit(1);
end_match_20:;
    return match_;
}

int go_33(int len_1, struct IntList* xs_2) {
tailrec_23:;
    int match_1;
    if ((!((!(xs_2))))) goto next_25;
    match_1 = len_1;
    goto end_match_24;
next_25:;
    if ((!(xs_2))) goto next_26;
    struct IntList* xs_3 = xs_2->tail;
    int arg_39 = (len_1 + 1);
    struct IntList* arg_40 = xs_3;
    len_1 = arg_39;
    xs_2 = arg_40;
    goto tailrec_23;
    match_1 = 0;
    goto end_match_24;
next_26:;
    exit(1);
end_match_24:;
    return match_1;
}

int listLength_2(struct StringList* xs_1) {
    int call_5 = go_34(0, xs_1);
    return call_5;
}

int listLength_1(struct IntList* xs_1) {
    int call_6 = go_33(0, xs_1);
    return call_6;
}

struct IntList* go_39(struct IntList* acc_, struct IntList* xs_5) {
tailrec_27:;
    struct IntList* match_2;
    if ((!((!(xs_5))))) goto next_29;
    match_2 = acc_;
    goto end_match_28;
next_29:;
    if ((!(xs_5))) goto next_30;
    int x_ = xs_5->head;
    struct IntList* xs_6 = xs_5->tail;
    struct IntList* list_ = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_->head = x_;
    list_->tail = acc_;
    struct IntList* arg_41 = list_;
    struct IntList* arg_42 = xs_6;
    acc_ = arg_41;
    xs_5 = arg_42;
    goto tailrec_27;
    match_2 = NULL;
    goto end_match_28;
next_30:;
    exit(1);
end_match_28:;
    return match_2;
}

struct StringList* go_38(struct StringList* acc_, struct StringList* xs_5) {
tailrec_31:;
    struct StringList* match_3;
    if ((!((!(xs_5))))) goto next_33;
    match_3 = acc_;
    goto end_match_32;
next_33:;
    if ((!(xs_5))) goto next_34;
    struct String x_ = xs_5->head;
    struct StringList* xs_6 = xs_5->tail;
    struct StringList* list_1 = (struct StringList*)milone_mem_alloc(1, sizeof(struct StringList));
    list_1->head = x_;
    list_1->tail = acc_;
    struct StringList* arg_43 = list_1;
    struct StringList* arg_44 = xs_6;
    acc_ = arg_43;
    xs_5 = arg_44;
    goto tailrec_31;
    match_3 = NULL;
    goto end_match_32;
next_34:;
    exit(1);
end_match_32:;
    return match_3;
}

struct IntList* listRev_2(struct IntList* xs_4) {
    struct IntList* call_7 = go_39(NULL, xs_4);
    return call_7;
}

struct StringList* listRev_1(struct StringList* xs_4) {
    struct StringList* call_8 = go_38(NULL, xs_4);
    return call_8;
}

struct IntIntBoolFun2 {
    int(*fun)(void*, int, int);
    void* env;
};

struct IntListIntListTuple2 {
    struct IntList* t0;
    struct IntList* t1;
};

int go_32(struct IntIntBoolFun2 itemEq_, struct IntList* xs_8, struct IntList* ys_1) {
tailrec_35:;
    int match_4;
    struct IntListIntListTuple2 tuple_;
    tuple_.t0 = xs_8;
    tuple_.t1 = ys_1;
    if ((!((!(tuple_.t0))))) goto next_37;
    if ((!((!(tuple_.t1))))) goto next_37;
    match_4 = 1;
    goto end_match_36;
next_37:;
    if ((!(tuple_.t0))) goto next_38;
    int x_1 = tuple_.t0->head;
    struct IntList* xs_9 = tuple_.t0->tail;
    if ((!(tuple_.t1))) goto next_38;
    int y_ = tuple_.t1->head;
    struct IntList* ys_2 = tuple_.t1->tail;
    int app_ = itemEq_.fun(itemEq_.env, x_1, y_);
    int if_6;
    if (app_) {
        goto then_41;
    } else {
        goto else_42;
    }
then_41:;
    struct IntIntBoolFun2 arg_45 = itemEq_;
    struct IntList* arg_46 = xs_9;
    struct IntList* arg_47 = ys_2;
    itemEq_ = arg_45;
    xs_8 = arg_46;
    ys_1 = arg_47;
    goto tailrec_35;
    if_6 = 0;
    goto if_next_40;
else_42:;
    if_6 = 0;
    goto if_next_40;
if_next_40:;
    match_4 = if_6;
    goto end_match_36;
next_38:;
    match_4 = 0;
    goto end_match_36;
next_39:;
end_match_36:;
    return match_4;
}

struct StringStringBoolFun2 {
    int(*fun)(void*, struct String, struct String);
    void* env;
};

struct StringListStringListTuple2 {
    struct StringList* t0;
    struct StringList* t1;
};

int go_31(struct StringStringBoolFun2 itemEq_, struct StringList* xs_8, struct StringList* ys_1) {
tailrec_43:;
    int match_5;
    struct StringListStringListTuple2 tuple_1;
    tuple_1.t0 = xs_8;
    tuple_1.t1 = ys_1;
    if ((!((!(tuple_1.t0))))) goto next_45;
    if ((!((!(tuple_1.t1))))) goto next_45;
    match_5 = 1;
    goto end_match_44;
next_45:;
    if ((!(tuple_1.t0))) goto next_46;
    struct String x_1 = tuple_1.t0->head;
    struct StringList* xs_9 = tuple_1.t0->tail;
    if ((!(tuple_1.t1))) goto next_46;
    struct String y_ = tuple_1.t1->head;
    struct StringList* ys_2 = tuple_1.t1->tail;
    int app_1 = itemEq_.fun(itemEq_.env, x_1, y_);
    int if_7;
    if (app_1) {
        goto then_49;
    } else {
        goto else_50;
    }
then_49:;
    struct StringStringBoolFun2 arg_48 = itemEq_;
    struct StringList* arg_49 = xs_9;
    struct StringList* arg_50 = ys_2;
    itemEq_ = arg_48;
    xs_8 = arg_49;
    ys_1 = arg_50;
    goto tailrec_43;
    if_7 = 0;
    goto if_next_48;
else_50:;
    if_7 = 0;
    goto if_next_48;
if_next_48:;
    match_5 = if_7;
    goto end_match_44;
next_46:;
    match_5 = 0;
    goto end_match_44;
next_47:;
end_match_44:;
    return match_5;
}

int listEq_2(struct IntIntBoolFun2 itemEq_, struct IntList* xs_7, struct IntList* ys_) {
    int call_9 = go_32(itemEq_, xs_7, ys_);
    return call_9;
}

int listEq_1(struct StringStringBoolFun2 itemEq_, struct StringList* xs_7, struct StringList* ys_) {
    int call_10 = go_31(itemEq_, xs_7, ys_);
    return call_10;
}

struct IntList* go_30(int len_2, int item_, struct IntList* acc_1, int i_) {
tailrec_51:;
    struct IntList* if_8;
    if ((i_ == len_2)) {
        goto then_53;
    } else {
        goto else_54;
    }
then_53:;
    if_8 = acc_1;
    goto if_next_52;
else_54:;
    int arg_51 = len_2;
    int arg_52 = item_;
    struct IntList* list_2 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_2->head = item_;
    list_2->tail = acc_1;
    struct IntList* arg_53 = list_2;
    int arg_54 = (i_ + 1);
    len_2 = arg_51;
    item_ = arg_52;
    acc_1 = arg_53;
    i_ = arg_54;
    goto tailrec_51;
    if_8 = NULL;
    goto if_next_52;
if_next_52:;
    return if_8;
}

struct IntList* listReplicate_1(int item_, int len_2) {
    struct IntList* call_11 = go_30(len_2, item_, NULL, 0);
    return call_11;
}

struct IntIntFun1 {
    int(*fun)(void*, int);
    void* env;
};

struct IntList* go_29(struct IntIntFun1 gen_, int len_3, struct IntList* acc_2, int i_1) {
tailrec_55:;
    struct IntList* if_9;
    if ((i_1 == len_3)) {
        goto then_57;
    } else {
        goto else_58;
    }
then_57:;
    struct IntList* call_12 = listRev_2(acc_2);
    if_9 = call_12;
    goto if_next_56;
else_58:;
    struct IntIntFun1 arg_55 = gen_;
    int arg_56 = len_3;
    int app_2 = gen_.fun(gen_.env, i_1);
    struct IntList* list_3 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_3->head = app_2;
    list_3->tail = acc_2;
    struct IntList* arg_57 = list_3;
    int arg_58 = (i_1 + 1);
    gen_ = arg_55;
    len_3 = arg_56;
    acc_2 = arg_57;
    i_1 = arg_58;
    goto tailrec_55;
    if_9 = NULL;
    goto if_next_56;
if_next_56:;
    return if_9;
}

struct IntList* listInit_1(int len_3, struct IntIntFun1 gen_) {
    milone_assert((len_3 >= 0), 66, 2);
    int call_13 = 0;
    struct IntList* call_14 = go_29(gen_, len_3, NULL, 0);
    return call_14;
}

struct StringStringListTuple2 {
    struct String t0;
    struct StringList* t1;
};

struct StringStringListTuple2 go_5(struct StringList* xs_11, int xn_) {
    struct StringStringListTuple2 match_6;
    if ((!((!(xs_11))))) goto next_60;
    milone_assert((xn_ == 0), 81, 8);
    int call_15 = 0;
    struct StringStringListTuple2 tuple_2;
    tuple_2.t0 = (struct String){.str = "", .len = 0};
    tuple_2.t1 = NULL;
    match_6 = tuple_2;
    goto end_match_59;
next_60:;
    if ((!(xs_11))) goto next_61;
    struct String x_2 = xs_11->head;
    struct StringList* xs_12 = xs_11->tail;
    if ((xn_ != 1)) goto next_61;
    struct StringStringListTuple2 tuple_3;
    tuple_3.t0 = x_2;
    tuple_3.t1 = xs_12;
    match_6 = tuple_3;
    goto end_match_59;
next_61:;
    if ((!(xs_11))) goto next_62;
    struct String x_3 = xs_11->head;
    if ((!(xs_11->tail))) goto next_62;
    struct String y_1 = xs_11->tail->head;
    struct StringList* xs_13 = xs_11->tail->tail;
    if ((xn_ != 2)) goto next_62;
    struct StringStringListTuple2 tuple_4;
    tuple_4.t0 = str_add(x_3, y_1);
    tuple_4.t1 = xs_13;
    match_6 = tuple_4;
    goto end_match_59;
next_62:;
    struct StringList* xs_14 = xs_11;
    int m_ = (xn_ / 2);
    struct StringStringListTuple2 call_16 = go_5(xs_14, m_);
    struct String l_ = call_16.t0;
    struct StringList* xs_15 = call_16.t1;
    struct StringStringListTuple2 call_17 = go_5(xs_15, (xn_ - m_));
    struct String r_ = call_17.t0;
    struct StringList* xs_16 = call_17.t1;
    struct StringStringListTuple2 tuple_5;
    tuple_5.t0 = str_add(l_, r_);
    tuple_5.t1 = xs_16;
    match_6 = tuple_5;
    goto end_match_59;
next_63:;
end_match_59:;
    return match_6;
}

struct String strConcat_(struct StringList* xs_10) {
    int call_18 = listLength_2(xs_10);
    int n_ = call_18;
    struct StringStringListTuple2 call_19 = go_5(xs_10, n_);
    struct String s_ = call_19.t0;
    struct StringList* xs_17 = call_19.t1;
    int call_20 = listIsEmpty_1(xs_17);
    milone_assert(call_20, 93, 2);
    int call_21 = 0;
    return s_;
}

int intEq_(int first_, int second_) {
    return (first_ == second_);
}

int intMin_(int first_1, int second_1) {
    int if_10;
    if ((second_1 < first_1)) {
        goto then_65;
    } else {
        goto else_66;
    }
then_65:;
    if_10 = second_1;
    goto if_next_64;
else_66:;
    if_10 = first_1;
    goto if_next_64;
if_next_64:;
    return if_10;
}

int intMax_(int first_2, int second_2) {
    int if_11;
    if ((first_2 < second_2)) {
        goto then_68;
    } else {
        goto else_69;
    }
then_68:;
    if_11 = second_2;
    goto if_next_67;
else_69:;
    if_11 = first_2;
    goto if_next_67;
if_next_67:;
    return if_11;
}

int strEq_(struct String first_3, struct String second_3) {
    return (str_cmp(first_3, second_3) == 0);
}

int failwith_1(struct String msg_) {
    printf("ERROR %s\n", msg_.str);
    int call_22 = 0;
    exit(1);
    return 0;
}

int fun_23(int arg_59) {
    int call_23 = scanInt_(0);
    return call_23;
}

int fun_3(void* env_, int arg_) {
    int call_24 = fun_23(arg_);
    return call_24;
}

struct IntList* scanIntList_(int len_4) {
    void* box_ = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_))) = 0;
    void* env_18 = box_;
    struct IntIntFun1 fun_24 = (struct IntIntFun1){.fun = fun_3, .env = env_18};
    struct IntList* call_25 = listInit_1(len_4, fun_24);
    return call_25;
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

struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6 {
    int t0;
    int t1;
    struct IntObjectFun1 t2;
    struct ObjectIntIntFun2 t3;
    struct ObjectIntIntObjectFun3 t4;
    void* t5;
};

struct IntObjectFun1 typeToArrayNew_1(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6 arg_60) {
    struct IntObjectFun1 arrayNew_ = arg_60.t2;
    void* _typeTag_2 = arg_60.t5;
    return arrayNew_;
}

struct ObjectIntIntFun2 typeToArrayGet_1(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6 arg_61) {
    struct ObjectIntIntFun2 arrayGet_ = arg_61.t3;
    void* _typeTag_3 = arg_61.t5;
    return arrayGet_;
}

struct ObjectIntIntObjectFun3 typeToArraySet_1(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6 arg_62) {
    struct ObjectIntIntObjectFun3 arraySet_ = arg_62.t4;
    void* _typeTag_4 = arg_62.t5;
    return arraySet_;
}

void* fun_4(void* env_1, int arg_1) {
    void* call_26 = rawIntArrayNew_(arg_1);
    return call_26;
}

int fun_5(void* env_2, void* arg_2, int arg_3) {
    int call_27 = rawIntArrayGet_(arg_2, arg_3);
    return call_27;
}

void* fun_6(void* env_3, void* arg_4, int arg_5, int arg_6) {
    void* call_28 = rawIntArraySet_(arg_4, arg_5, arg_6);
    return call_28;
}

struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6ObjectIntIntObjectTuple5 {
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6 t0;
    void* t1;
    int t2;
    int t3;
    void* t4;
};

int vectorToLength_1(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6ObjectIntIntObjectTuple5 arg_63) {
    int len_5 = arg_63.t2;
    void* _vectorTag_ = arg_63.t4;
    return len_5;
}

struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6ObjectIntIntObjectTuple5 vectorNew_1(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6 itemTy_, int len_6) {
    struct IntObjectFun1 call_29 = typeToArrayNew_1(itemTy_);
    void* app_3 = call_29.fun(call_29.env, len_6);
    void* array_2 = app_3;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6ObjectIntIntObjectTuple5 tuple_6;
    tuple_6.t0 = itemTy_;
    tuple_6.t1 = array_2;
    tuple_6.t2 = len_6;
    tuple_6.t3 = len_6;
    tuple_6.t4 = 0;
    return tuple_6;
}

int vectorCheckIndex_1(int index_2, struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6ObjectIntIntObjectTuple5 self_) {
    int call_30 = vectorToLength_1(self_);
    int len_7 = call_30;
    int if_12;
    if ((index_2 < 0)) {
        goto then_71;
    } else {
        goto else_72;
    }
then_71:;
    if_12 = 1;
    goto if_next_70;
else_72:;
    if_12 = (index_2 >= len_7);
    goto if_next_70;
if_next_70:;
    int if_13;
    if (if_12) {
        goto then_74;
    } else {
        goto else_75;
    }
then_74:;
    printf("ERROR: Out of range (len = %d, index = %d)\n", len_7, index_2);
    int call_31 = 0;
    exit(1);
    if_13 = 0;
    goto if_next_73;
else_75:;
    if_13 = 0;
    goto if_next_73;
if_next_73:;
    return 0;
}

int vectorGet_1(int index_3, struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6ObjectIntIntObjectTuple5 self_1) {
    int call_32 = vectorCheckIndex_1(index_3, self_1);
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6 itemTy_1 = self_1.t0;
    void* array_3 = self_1.t1;
    void* _vectorTag_1 = self_1.t4;
    struct ObjectIntIntFun2 call_33 = typeToArrayGet_1(itemTy_1);
    int app_4 = call_33.fun(call_33.env, array_3, index_3);
    return app_4;
}

int vectorSet_1(int index_4, int value_1, struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6ObjectIntIntObjectTuple5 self_2) {
    int call_34 = vectorCheckIndex_1(index_4, self_2);
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6 itemTy_2 = self_2.t0;
    void* array_4 = self_2.t1;
    void* _vectorTag_2 = self_2.t4;
    struct ObjectIntIntObjectFun3 call_35 = typeToArraySet_1(itemTy_2);
    void* app_5 = call_35.fun(call_35.env, array_4, index_4, value_1);
    int call_36 = ignore_1(app_5);
    return 0;
}

int go_28(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6ObjectIntIntObjectTuple5 v_, int len_9, int i_2, struct IntList* xs_19) {
tailrec_76:;
    int match_7;
    if ((!((!(xs_19))))) goto next_78;
    milone_assert((i_2 == len_9), 185, 12);
    int call_37 = 0;
    match_7 = 0;
    goto end_match_77;
next_78:;
    if ((!(xs_19))) goto next_79;
    int x_4 = xs_19->head;
    struct IntList* xs_20 = xs_19->tail;
    int call_38 = vectorSet_1(i_2, x_4, v_);
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6ObjectIntIntObjectTuple5 arg_64 = v_;
    int arg_65 = len_9;
    int arg_66 = (i_2 + 1);
    struct IntList* arg_67 = xs_20;
    v_ = arg_64;
    len_9 = arg_65;
    i_2 = arg_66;
    xs_19 = arg_67;
    goto tailrec_76;
    match_7 = 0;
    goto end_match_77;
next_79:;
    exit(1);
end_match_77:;
    return 0;
}

struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6ObjectIntIntObjectTuple5 vectorOfList_1(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6 ty_, struct IntList* xs_18) {
    int call_39 = listLength_1(xs_18);
    int len_9 = call_39;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6ObjectIntIntObjectTuple5 call_40 = vectorNew_1(ty_, len_9);
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6ObjectIntIntObjectTuple5 v_ = call_40;
    int call_41 = go_28(v_, len_9, 0, xs_18);
    return v_;
}

int go_7(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6ObjectIntIntObjectTuple5 v_1, int len_10, int i_3) {
tailrec_80:;
    int if_14;
    if ((i_3 < len_10)) {
        goto then_82;
    } else {
        goto else_83;
    }
then_82:;
    int call_42 = scanInt_(0);
    int value_3 = call_42;
    int call_43 = vectorSet_1(i_3, value_3, v_1);
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6ObjectIntIntObjectTuple5 arg_68 = v_1;
    int arg_69 = len_10;
    int arg_70 = (i_3 + 1);
    v_1 = arg_68;
    len_10 = arg_69;
    i_3 = arg_70;
    goto tailrec_80;
    if_14 = 0;
    goto if_next_81;
else_83:;
    if_14 = 0;
    goto if_next_81;
if_next_81:;
    return 0;
}

struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6ObjectIntIntObjectTuple5 scanIntVector_(int len_10) {
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6ObjectIntIntObjectTuple5 call_44 = vectorNew_1(typeInt_, len_10);
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6ObjectIntIntObjectTuple5 v_1 = call_44;
    int call_45 = go_7(v_1, len_10, 0);
    return v_1;
}

int refCase_(int arg_71) {
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6ObjectIntIntObjectTuple5 call_46 = vectorNew_1(typeInt_, 1);
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6ObjectIntIntObjectTuple5 v_2 = call_46;
    int call_47 = vectorToLength_1(v_2);
    milone_assert((call_47 == 1), 208, 4);
    int call_48 = 0;
    int call_49 = vectorGet_1(0, v_2);
    milone_assert((call_49 == 0), 209, 4);
    int call_50 = 0;
    int call_51 = vectorSet_1(0, 42, v_2);
    int call_52 = vectorGet_1(0, v_2);
    milone_assert((call_52 == 42), 211, 4);
    int call_53 = 0;
    return 0;
}

int vectorOfListTest_(int arg_72) {
    struct IntList* list_6 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_6->head = 3;
    list_6->tail = NULL;
    struct IntList* list_5 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_5->head = 2;
    list_5->tail = list_6;
    struct IntList* list_4 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_4->head = 1;
    list_4->tail = list_5;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6ObjectIntIntObjectTuple5 call_54 = vectorOfList_1(typeInt_, list_4);
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6ObjectIntIntObjectTuple5 v_3 = call_54;
    int call_55 = vectorToLength_1(v_3);
    milone_assert((call_55 == 3), 217, 4);
    int call_56 = 0;
    int call_57 = vectorGet_1(0, v_3);
    milone_assert((call_57 == 1), 218, 4);
    int call_58 = 0;
    int call_59 = vectorGet_1(1, v_3);
    milone_assert((call_59 == 2), 219, 4);
    int call_60 = 0;
    int call_61 = vectorGet_1(2, v_3);
    milone_assert((call_61 == 3), 220, 4);
    int call_62 = 0;
    return 0;
}

int vectorTest_(int arg_73) {
    int call_63 = refCase_(0);
    int call_64 = vectorOfListTest_(0);
    return 0;
}

struct IntIntTuple2 {
    int t0;
    int t1;
};

int intervalIsDisjoint_(struct IntIntTuple2 first_4, struct IntIntTuple2 second_4) {
    int xl_ = first_4.t0;
    int xr_ = first_4.t1;
    int yl_ = second_4.t0;
    int yr_ = second_4.t1;
    int if_15;
    if ((yl_ >= xr_)) {
        goto then_85;
    } else {
        goto else_86;
    }
then_85:;
    if_15 = 1;
    goto if_next_84;
else_86:;
    if_15 = (xl_ >= yr_);
    goto if_next_84;
if_next_84:;
    return if_15;
}

int intervalCovers_(struct IntIntTuple2 first_5, struct IntIntTuple2 second_5) {
    int xl_1 = first_5.t0;
    int xr_1 = first_5.t1;
    int yl_1 = second_5.t0;
    int yr_1 = second_5.t1;
    int if_16;
    if ((yl_1 >= xl_1)) {
        goto then_88;
    } else {
        goto else_89;
    }
then_88:;
    if_16 = (xr_1 >= yr_1);
    goto if_next_87;
else_89:;
    if_16 = 0;
    goto if_next_87;
if_next_87:;
    return if_16;
}

struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 {
    struct StringStringStringFun2 t0;
    struct StringIntIntObjectObjectTuple5 t1;
    void* t2;
    void* t3;
};

struct StringStringStringFun2 segItemTypeToAppend_2(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 arg_74) {
    struct StringStringStringFun2 append_ = arg_74.t0;
    return append_;
}

struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 {
    struct IntIntIntFun2 t0;
    struct IntIntIntObjectObjectTuple5 t1;
    void* t2;
    void* t3;
};

struct IntIntIntFun2 segItemTypeToAppend_1(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 arg_75) {
    struct IntIntIntFun2 append_ = arg_75.t0;
    return append_;
}

struct IntIntIntObjectObjectTuple5 segItemTypeToEmptyNode_2(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 arg_76) {
    struct IntIntIntObjectObjectTuple5 emptyNode_ = arg_76.t1;
    return emptyNode_;
}

struct StringIntIntObjectObjectTuple5 segItemTypeToEmptyNode_1(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 arg_77) {
    struct StringIntIntObjectObjectTuple5 emptyNode_ = arg_77.t1;
    return emptyNode_;
}

void* segItemTypeToNoChildren_1(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 arg_78) {
    void* noChildren_ = arg_78.t2;
    return noChildren_;
}

void* segItemTypeToNoChildren_2(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 arg_79) {
    void* noChildren_ = arg_79.t2;
    return noChildren_;
}

int segItemTypeToEmptyItem_1(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_4) {
    struct IntIntIntObjectObjectTuple5 call_65 = segItemTypeToEmptyNode_2(itemTy_4);
    int call_66 = segNodeToItem_1(call_65);
    return call_66;
}

struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2 {
    struct StringIntIntObjectObjectTuple5 t0;
    struct StringIntIntObjectObjectTuple5 t1;
};

struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 segItemTypeNew_2(struct String emptyItem_, struct StringStringStringFun2 append_1) {
    struct StringIntIntObjectObjectTuple5 call_67 = segNodeNewEmpty_2(emptyItem_);
    struct StringIntIntObjectObjectTuple5 emptyNode_1 = call_67;
    struct String app_6 = append_1.fun(append_1.env, emptyItem_, emptyItem_);
    struct StringList* list_8 = (struct StringList*)milone_mem_alloc(1, sizeof(struct StringList));
    list_8->head = emptyItem_;
    list_8->tail = NULL;
    struct StringList* list_7 = (struct StringList*)milone_mem_alloc(1, sizeof(struct StringList));
    list_7->head = app_6;
    list_7->tail = list_8;
    int call_68 = listIsEmpty_1(list_7);
    milone_assert((!(call_68)), 42, 2);
    int call_69 = 0;
    struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2 tuple_8;
    tuple_8.t0 = emptyNode_1;
    tuple_8.t1 = emptyNode_1;
    void* box_1 = (void*)milone_mem_alloc(1, sizeof(struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2));
    (*(((struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2*)box_1))) = tuple_8;
    struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 tuple_7;
    tuple_7.t0 = append_1;
    tuple_7.t1 = emptyNode_1;
    tuple_7.t2 = box_1;
    tuple_7.t3 = 0;
    struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_5 = tuple_7;
    struct StringStringStringFun2 call_70 = segItemTypeToAppend_2(itemTy_5);
    struct StringStringStringFun2List* list_10 = (struct StringStringStringFun2List*)milone_mem_alloc(1, sizeof(struct StringStringStringFun2List));
    list_10->head = append_1;
    list_10->tail = NULL;
    struct StringStringStringFun2List* list_9 = (struct StringStringStringFun2List*)milone_mem_alloc(1, sizeof(struct StringStringStringFun2List));
    list_9->head = call_70;
    list_9->tail = list_10;
    int call_71 = listIsEmpty_4(list_9);
    milone_assert((!(call_71)), 50, 2);
    int call_72 = 0;
    return itemTy_5;
}

struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 {
    struct IntIntIntObjectObjectTuple5 t0;
    struct IntIntIntObjectObjectTuple5 t1;
};

struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 segItemTypeNew_1(int emptyItem_, struct IntIntIntFun2 append_1) {
    struct IntIntIntObjectObjectTuple5 call_73 = segNodeNewEmpty_1(emptyItem_);
    struct IntIntIntObjectObjectTuple5 emptyNode_1 = call_73;
    int app_7 = append_1.fun(append_1.env, emptyItem_, emptyItem_);
    struct IntList* list_12 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_12->head = emptyItem_;
    list_12->tail = NULL;
    struct IntList* list_11 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_11->head = app_7;
    list_11->tail = list_12;
    int call_74 = listIsEmpty_3(list_11);
    milone_assert((!(call_74)), 42, 2);
    int call_75 = 0;
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 tuple_10;
    tuple_10.t0 = emptyNode_1;
    tuple_10.t1 = emptyNode_1;
    void* box_2 = (void*)milone_mem_alloc(1, sizeof(struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2));
    (*(((struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2*)box_2))) = tuple_10;
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 tuple_9;
    tuple_9.t0 = append_1;
    tuple_9.t1 = emptyNode_1;
    tuple_9.t2 = box_2;
    tuple_9.t3 = 0;
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_5 = tuple_9;
    struct IntIntIntFun2 call_76 = segItemTypeToAppend_1(itemTy_5);
    struct IntIntIntFun2List* list_14 = (struct IntIntIntFun2List*)milone_mem_alloc(1, sizeof(struct IntIntIntFun2List));
    list_14->head = append_1;
    list_14->tail = NULL;
    struct IntIntIntFun2List* list_13 = (struct IntIntIntFun2List*)milone_mem_alloc(1, sizeof(struct IntIntIntFun2List));
    list_13->head = call_76;
    list_13->tail = list_14;
    int call_77 = listIsEmpty_2(list_13);
    milone_assert((!(call_77)), 50, 2);
    int call_78 = 0;
    return itemTy_5;
}

struct StringIntIntObjectObjectTuple5 segNodeNewEmpty_2(struct String emptyItem_1) {
    struct StringIntIntObjectObjectTuple5 tuple_11;
    tuple_11.t0 = emptyItem_1;
    tuple_11.t1 = 0;
    tuple_11.t2 = (0 - 1);
    tuple_11.t3 = unitObj_;
    tuple_11.t4 = 0;
    return tuple_11;
}

struct IntIntIntObjectObjectTuple5 segNodeNewEmpty_1(int emptyItem_1) {
    struct IntIntIntObjectObjectTuple5 tuple_12;
    tuple_12.t0 = emptyItem_1;
    tuple_12.t1 = 0;
    tuple_12.t2 = (0 - 1);
    tuple_12.t3 = unitObj_;
    tuple_12.t4 = 0;
    return tuple_12;
}

struct IntIntIntObjectObjectTuple5 segNodeNewLeaf_1(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_6, int item_1) {
    void* call_79 = segItemTypeToNoChildren_1(itemTy_6);
    void* noChildren_1 = call_79;
    struct IntIntIntObjectObjectTuple5 tuple_13;
    tuple_13.t0 = item_1;
    tuple_13.t1 = 1;
    tuple_13.t2 = 0;
    tuple_13.t3 = noChildren_1;
    tuple_13.t4 = 0;
    return tuple_13;
}

struct StringIntIntObjectObjectTuple5 segNodeNewLeaf_2(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_6, struct String item_1) {
    void* call_80 = segItemTypeToNoChildren_2(itemTy_6);
    void* noChildren_1 = call_80;
    struct StringIntIntObjectObjectTuple5 tuple_14;
    tuple_14.t0 = item_1;
    tuple_14.t1 = 1;
    tuple_14.t2 = 0;
    tuple_14.t3 = noChildren_1;
    tuple_14.t4 = 0;
    return tuple_14;
}

struct IntIntIntObjectObjectTuple5 doNew_1(struct IntIntIntObjectObjectTuple5 right_, struct IntIntIntObjectObjectTuple5 left_, struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_7, int arg_80) {
    int leftItem_ = left_.t0;
    int leftLen_ = left_.t1;
    int leftHeight_ = left_.t2;
    int rightItem_ = right_.t0;
    int rightLen_ = right_.t1;
    int rightHeight_ = right_.t2;
    int if_17;
    if ((leftLen_ >= 1)) {
        goto then_91;
    } else {
        goto else_92;
    }
then_91:;
    if_17 = (rightLen_ >= 1);
    goto if_next_90;
else_92:;
    if_17 = 0;
    goto if_next_90;
if_next_90:;
    milone_assert(if_17, 73, 4);
    int call_81 = 0;
    struct IntIntIntFun2 call_82 = segItemTypeToAppend_1(itemTy_7);
    int app_8 = call_82.fun(call_82.env, leftItem_, rightItem_);
    int item_2 = app_8;
    int len_11 = (leftLen_ + rightLen_);
    int call_83 = intMax_(leftHeight_, rightHeight_);
    int height_ = (1 + call_83);
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 tuple_16;
    tuple_16.t0 = left_;
    tuple_16.t1 = right_;
    void* box_3 = (void*)milone_mem_alloc(1, sizeof(struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2));
    (*(((struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2*)box_3))) = tuple_16;
    struct IntIntIntObjectObjectTuple5 tuple_15;
    tuple_15.t0 = item_2;
    tuple_15.t1 = len_11;
    tuple_15.t2 = height_;
    tuple_15.t3 = box_3;
    tuple_15.t4 = 0;
    return tuple_15;
}

struct StringIntIntObjectObjectTuple5 doNew_2(struct StringIntIntObjectObjectTuple5 right_, struct StringIntIntObjectObjectTuple5 left_, struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_7, int arg_81) {
    struct String leftItem_ = left_.t0;
    int leftLen_ = left_.t1;
    int leftHeight_ = left_.t2;
    struct String rightItem_ = right_.t0;
    int rightLen_ = right_.t1;
    int rightHeight_ = right_.t2;
    int if_18;
    if ((leftLen_ >= 1)) {
        goto then_94;
    } else {
        goto else_95;
    }
then_94:;
    if_18 = (rightLen_ >= 1);
    goto if_next_93;
else_95:;
    if_18 = 0;
    goto if_next_93;
if_next_93:;
    milone_assert(if_18, 73, 4);
    int call_84 = 0;
    struct StringStringStringFun2 call_85 = segItemTypeToAppend_2(itemTy_7);
    struct String app_9 = call_85.fun(call_85.env, leftItem_, rightItem_);
    struct String item_2 = app_9;
    int len_11 = (leftLen_ + rightLen_);
    int call_86 = intMax_(leftHeight_, rightHeight_);
    int height_ = (1 + call_86);
    struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2 tuple_18;
    tuple_18.t0 = left_;
    tuple_18.t1 = right_;
    void* box_4 = (void*)milone_mem_alloc(1, sizeof(struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2));
    (*(((struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2*)box_4))) = tuple_18;
    struct StringIntIntObjectObjectTuple5 tuple_17;
    tuple_17.t0 = item_2;
    tuple_17.t1 = len_11;
    tuple_17.t2 = height_;
    tuple_17.t3 = box_4;
    tuple_17.t4 = 0;
    return tuple_17;
}

struct IntIntIntObjectObjectTuple5 segNodeNew_1(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_7, struct IntIntIntObjectObjectTuple5 left_, struct IntIntIntObjectObjectTuple5 right_) {
    struct IntIntIntObjectObjectTuple5 match_8;
    int call_87 = segNodeToLength_1(left_);
    int call_88 = segNodeToLength_1(right_);
    struct IntIntTuple2 tuple_19;
    tuple_19.t0 = call_87;
    tuple_19.t1 = call_88;
    if ((tuple_19.t0 != 0)) goto next_97;
    if ((tuple_19.t1 != 0)) goto next_97;
    struct IntIntIntObjectObjectTuple5 call_89 = segItemTypeToEmptyNode_2(itemTy_7);
    match_8 = call_89;
    goto end_match_96;
next_97:;
    if ((tuple_19.t0 != 0)) goto next_98;
    match_8 = right_;
    goto end_match_96;
next_98:;
    if ((tuple_19.t1 != 0)) goto next_99;
    match_8 = left_;
    goto end_match_96;
next_99:;
    struct IntIntIntObjectObjectTuple5 call_90 = doNew_1(right_, left_, itemTy_7, 0);
    match_8 = call_90;
    goto end_match_96;
next_100:;
end_match_96:;
    return match_8;
}

struct StringIntIntObjectObjectTuple5 segNodeNew_2(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_7, struct StringIntIntObjectObjectTuple5 left_, struct StringIntIntObjectObjectTuple5 right_) {
    struct StringIntIntObjectObjectTuple5 match_9;
    int call_91 = segNodeToLength_2(left_);
    int call_92 = segNodeToLength_2(right_);
    struct IntIntTuple2 tuple_20;
    tuple_20.t0 = call_91;
    tuple_20.t1 = call_92;
    if ((tuple_20.t0 != 0)) goto next_102;
    if ((tuple_20.t1 != 0)) goto next_102;
    struct StringIntIntObjectObjectTuple5 call_93 = segItemTypeToEmptyNode_1(itemTy_7);
    match_9 = call_93;
    goto end_match_101;
next_102:;
    if ((tuple_20.t0 != 0)) goto next_103;
    match_9 = right_;
    goto end_match_101;
next_103:;
    if ((tuple_20.t1 != 0)) goto next_104;
    match_9 = left_;
    goto end_match_101;
next_104:;
    struct StringIntIntObjectObjectTuple5 call_94 = doNew_2(right_, left_, itemTy_7, 0);
    match_9 = call_94;
    goto end_match_101;
next_105:;
end_match_101:;
    return match_9;
}

int segNodeToItem_1(struct IntIntIntObjectObjectTuple5 node_) {
    int item_3 = node_.t0;
    return item_3;
}

int segNodeToLength_1(struct IntIntIntObjectObjectTuple5 node_1) {
    int len_12 = node_1.t1;
    return len_12;
}

int segNodeToLength_2(struct StringIntIntObjectObjectTuple5 node_1) {
    int len_12 = node_1.t1;
    return len_12;
}

int segNodeToHeight_1(struct IntIntIntObjectObjectTuple5 node_2) {
    int height_1 = node_2.t2;
    return height_1;
}

int segNodeToHeight_2(struct StringIntIntObjectObjectTuple5 node_2) {
    int height_1 = node_2.t2;
    return height_1;
}

struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 segNodeToChildren_1(struct IntIntIntObjectObjectTuple5 node_3) {
    int len_13 = node_3.t1;
    void* children_ = node_3.t3;
    milone_assert((len_13 >= 2), 116, 2);
    int call_95 = 0;
    struct IntIntIntObjectObjectTuple5 left_1 = (*(((struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2*)children_))).t0;
    struct IntIntIntObjectObjectTuple5 right_1 = (*(((struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2*)children_))).t1;
    struct IntIntIntObjectObjectTuple5List* list_17 = (struct IntIntIntObjectObjectTuple5List*)milone_mem_alloc(1, sizeof(struct IntIntIntObjectObjectTuple5List));
    list_17->head = right_1;
    list_17->tail = NULL;
    struct IntIntIntObjectObjectTuple5List* list_16 = (struct IntIntIntObjectObjectTuple5List*)milone_mem_alloc(1, sizeof(struct IntIntIntObjectObjectTuple5List));
    list_16->head = left_1;
    list_16->tail = list_17;
    struct IntIntIntObjectObjectTuple5List* list_15 = (struct IntIntIntObjectObjectTuple5List*)milone_mem_alloc(1, sizeof(struct IntIntIntObjectObjectTuple5List));
    list_15->head = node_3;
    list_15->tail = list_16;
    int call_96 = listIsEmpty_5(list_15);
    milone_assert((!(call_96)), 121, 2);
    int call_97 = 0;
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 tuple_21;
    tuple_21.t0 = left_1;
    tuple_21.t1 = right_1;
    return tuple_21;
}

struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2 segNodeToChildren_2(struct StringIntIntObjectObjectTuple5 node_3) {
    int len_13 = node_3.t1;
    void* children_ = node_3.t3;
    milone_assert((len_13 >= 2), 116, 2);
    int call_98 = 0;
    struct StringIntIntObjectObjectTuple5 left_1 = (*(((struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2*)children_))).t0;
    struct StringIntIntObjectObjectTuple5 right_1 = (*(((struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2*)children_))).t1;
    struct StringIntIntObjectObjectTuple5List* list_20 = (struct StringIntIntObjectObjectTuple5List*)milone_mem_alloc(1, sizeof(struct StringIntIntObjectObjectTuple5List));
    list_20->head = right_1;
    list_20->tail = NULL;
    struct StringIntIntObjectObjectTuple5List* list_19 = (struct StringIntIntObjectObjectTuple5List*)milone_mem_alloc(1, sizeof(struct StringIntIntObjectObjectTuple5List));
    list_19->head = left_1;
    list_19->tail = list_20;
    struct StringIntIntObjectObjectTuple5List* list_18 = (struct StringIntIntObjectObjectTuple5List*)milone_mem_alloc(1, sizeof(struct StringIntIntObjectObjectTuple5List));
    list_18->head = node_3;
    list_18->tail = list_19;
    int call_99 = listIsEmpty_6(list_18);
    milone_assert((!(call_99)), 121, 2);
    int call_100 = 0;
    struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2 tuple_22;
    tuple_22.t0 = left_1;
    tuple_22.t1 = right_1;
    return tuple_22;
}

int segNodeIsEmpty_1(struct IntIntIntObjectObjectTuple5 node_4) {
    int call_101 = segNodeToLength_1(node_4);
    return (call_101 == 0);
}

struct IntIntIntObjectObjectTuple5 segNodeWithLeft_1(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_8, struct IntIntIntObjectObjectTuple5 newLeft_, struct IntIntIntObjectObjectTuple5 node_5) {
    int call_102 = segNodeToLength_1(node_5);
    milone_assert((call_102 >= 1), 128, 2);
    int call_103 = 0;
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 call_104 = segNodeToChildren_1(node_5);
    struct IntIntIntObjectObjectTuple5 right_2 = call_104.t1;
    struct IntIntIntObjectObjectTuple5 call_105 = segNodeNew_1(itemTy_8, newLeft_, right_2);
    return call_105;
}

struct StringIntIntObjectObjectTuple5 segNodeWithLeft_2(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_8, struct StringIntIntObjectObjectTuple5 newLeft_, struct StringIntIntObjectObjectTuple5 node_5) {
    int call_106 = segNodeToLength_2(node_5);
    milone_assert((call_106 >= 1), 128, 2);
    int call_107 = 0;
    struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2 call_108 = segNodeToChildren_2(node_5);
    struct StringIntIntObjectObjectTuple5 right_2 = call_108.t1;
    struct StringIntIntObjectObjectTuple5 call_109 = segNodeNew_2(itemTy_8, newLeft_, right_2);
    return call_109;
}

struct IntIntIntObjectObjectTuple5 segNodeWithRight_1(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_9, struct IntIntIntObjectObjectTuple5 newRight_, struct IntIntIntObjectObjectTuple5 node_6) {
    int call_110 = segNodeToLength_1(node_6);
    milone_assert((call_110 >= 1), 133, 2);
    int call_111 = 0;
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 call_112 = segNodeToChildren_1(node_6);
    struct IntIntIntObjectObjectTuple5 left_2 = call_112.t0;
    struct IntIntIntObjectObjectTuple5 call_113 = segNodeNew_1(itemTy_9, left_2, newRight_);
    return call_113;
}

struct StringIntIntObjectObjectTuple5 segNodeWithRight_2(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_9, struct StringIntIntObjectObjectTuple5 newRight_, struct StringIntIntObjectObjectTuple5 node_6) {
    int call_114 = segNodeToLength_2(node_6);
    milone_assert((call_114 >= 1), 133, 2);
    int call_115 = 0;
    struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2 call_116 = segNodeToChildren_2(node_6);
    struct StringIntIntObjectObjectTuple5 left_2 = call_116.t0;
    struct StringIntIntObjectObjectTuple5 call_117 = segNodeNew_2(itemTy_9, left_2, newRight_);
    return call_117;
}

struct IntIntIntObjectObjectTuple5 rotateLeft_1(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_10, struct IntIntIntObjectObjectTuple5 node_8) {
    int call_118 = segNodeToLength_1(node_8);
    struct IntIntIntObjectObjectTuple5 if_19;
    if ((call_118 < 2)) {
        goto then_107;
    } else {
        goto else_108;
    }
then_107:;
    if_19 = node_8;
    goto if_next_106;
else_108:;
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 call_119 = segNodeToChildren_1(node_8);
    struct IntIntIntObjectObjectTuple5 right_3 = call_119.t1;
    int call_120 = segNodeToLength_1(right_3);
    struct IntIntIntObjectObjectTuple5 if_20;
    if ((call_120 < 2)) {
        goto then_110;
    } else {
        goto else_111;
    }
then_110:;
    if_20 = node_8;
    goto if_next_109;
else_111:;
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 call_121 = segNodeToChildren_1(right_3);
    struct IntIntIntObjectObjectTuple5 x_5 = call_121.t0;
    struct IntIntIntObjectObjectTuple5 call_122 = segNodeWithRight_1(itemTy_10, x_5, node_8);
    struct IntIntIntObjectObjectTuple5 u_ = call_122;
    struct IntIntIntObjectObjectTuple5 call_123 = segNodeWithLeft_1(itemTy_10, u_, right_3);
    struct IntIntIntObjectObjectTuple5 t_ = call_123;
    if_20 = t_;
    goto if_next_109;
if_next_109:;
    if_19 = if_20;
    goto if_next_106;
if_next_106:;
    return if_19;
}

struct StringIntIntObjectObjectTuple5 rotateLeft_2(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_10, struct StringIntIntObjectObjectTuple5 node_8) {
    int call_124 = segNodeToLength_2(node_8);
    struct StringIntIntObjectObjectTuple5 if_21;
    if ((call_124 < 2)) {
        goto then_113;
    } else {
        goto else_114;
    }
then_113:;
    if_21 = node_8;
    goto if_next_112;
else_114:;
    struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2 call_125 = segNodeToChildren_2(node_8);
    struct StringIntIntObjectObjectTuple5 right_3 = call_125.t1;
    int call_126 = segNodeToLength_2(right_3);
    struct StringIntIntObjectObjectTuple5 if_22;
    if ((call_126 < 2)) {
        goto then_116;
    } else {
        goto else_117;
    }
then_116:;
    if_22 = node_8;
    goto if_next_115;
else_117:;
    struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2 call_127 = segNodeToChildren_2(right_3);
    struct StringIntIntObjectObjectTuple5 x_5 = call_127.t0;
    struct StringIntIntObjectObjectTuple5 call_128 = segNodeWithRight_2(itemTy_10, x_5, node_8);
    struct StringIntIntObjectObjectTuple5 u_ = call_128;
    struct StringIntIntObjectObjectTuple5 call_129 = segNodeWithLeft_2(itemTy_10, u_, right_3);
    struct StringIntIntObjectObjectTuple5 t_ = call_129;
    if_22 = t_;
    goto if_next_115;
if_next_115:;
    if_21 = if_22;
    goto if_next_112;
if_next_112:;
    return if_21;
}

struct IntIntIntObjectObjectTuple5 rotateRight_1(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_10, struct IntIntIntObjectObjectTuple5 node_9) {
    int call_130 = segNodeToLength_1(node_9);
    struct IntIntIntObjectObjectTuple5 if_23;
    if ((call_130 < 2)) {
        goto then_119;
    } else {
        goto else_120;
    }
then_119:;
    if_23 = node_9;
    goto if_next_118;
else_120:;
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 call_131 = segNodeToChildren_1(node_9);
    struct IntIntIntObjectObjectTuple5 left_3 = call_131.t0;
    int call_132 = segNodeToLength_1(left_3);
    struct IntIntIntObjectObjectTuple5 if_24;
    if ((call_132 < 2)) {
        goto then_122;
    } else {
        goto else_123;
    }
then_122:;
    if_24 = node_9;
    goto if_next_121;
else_123:;
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 call_133 = segNodeToChildren_1(left_3);
    struct IntIntIntObjectObjectTuple5 y_2 = call_133.t1;
    struct IntIntIntObjectObjectTuple5 call_134 = segNodeWithLeft_1(itemTy_10, y_2, node_9);
    struct IntIntIntObjectObjectTuple5 u_1 = call_134;
    struct IntIntIntObjectObjectTuple5 call_135 = segNodeWithRight_1(itemTy_10, u_1, left_3);
    struct IntIntIntObjectObjectTuple5 t_1 = call_135;
    if_24 = t_1;
    goto if_next_121;
if_next_121:;
    if_23 = if_24;
    goto if_next_118;
if_next_118:;
    return if_23;
}

struct StringIntIntObjectObjectTuple5 rotateRight_2(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_10, struct StringIntIntObjectObjectTuple5 node_9) {
    int call_136 = segNodeToLength_2(node_9);
    struct StringIntIntObjectObjectTuple5 if_25;
    if ((call_136 < 2)) {
        goto then_125;
    } else {
        goto else_126;
    }
then_125:;
    if_25 = node_9;
    goto if_next_124;
else_126:;
    struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2 call_137 = segNodeToChildren_2(node_9);
    struct StringIntIntObjectObjectTuple5 left_3 = call_137.t0;
    int call_138 = segNodeToLength_2(left_3);
    struct StringIntIntObjectObjectTuple5 if_26;
    if ((call_138 < 2)) {
        goto then_128;
    } else {
        goto else_129;
    }
then_128:;
    if_26 = node_9;
    goto if_next_127;
else_129:;
    struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2 call_139 = segNodeToChildren_2(left_3);
    struct StringIntIntObjectObjectTuple5 y_2 = call_139.t1;
    struct StringIntIntObjectObjectTuple5 call_140 = segNodeWithLeft_2(itemTy_10, y_2, node_9);
    struct StringIntIntObjectObjectTuple5 u_1 = call_140;
    struct StringIntIntObjectObjectTuple5 call_141 = segNodeWithRight_2(itemTy_10, u_1, left_3);
    struct StringIntIntObjectObjectTuple5 t_1 = call_141;
    if_26 = t_1;
    goto if_next_127;
if_next_127:;
    if_25 = if_26;
    goto if_next_124;
if_next_124:;
    return if_25;
}

struct IntIntIntObjectObjectTuple5 doubleLeft_1(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_10, struct IntIntIntObjectObjectTuple5 node_10) {
    int call_142 = segNodeToLength_1(node_10);
    struct IntIntIntObjectObjectTuple5 if_27;
    if ((call_142 < 2)) {
        goto then_131;
    } else {
        goto else_132;
    }
then_131:;
    if_27 = node_10;
    goto if_next_130;
else_132:;
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 call_143 = segNodeToChildren_1(node_10);
    struct IntIntIntObjectObjectTuple5 right_4 = call_143.t1;
    struct IntIntIntObjectObjectTuple5 call_144 = rotateRight_1(itemTy_10, right_4);
    struct IntIntIntObjectObjectTuple5 call_145 = segNodeWithRight_1(itemTy_10, call_144, node_10);
    struct IntIntIntObjectObjectTuple5 call_146 = rotateLeft_1(itemTy_10, call_145);
    if_27 = call_146;
    goto if_next_130;
if_next_130:;
    return if_27;
}

struct StringIntIntObjectObjectTuple5 doubleLeft_2(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_10, struct StringIntIntObjectObjectTuple5 node_10) {
    int call_147 = segNodeToLength_2(node_10);
    struct StringIntIntObjectObjectTuple5 if_28;
    if ((call_147 < 2)) {
        goto then_134;
    } else {
        goto else_135;
    }
then_134:;
    if_28 = node_10;
    goto if_next_133;
else_135:;
    struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2 call_148 = segNodeToChildren_2(node_10);
    struct StringIntIntObjectObjectTuple5 right_4 = call_148.t1;
    struct StringIntIntObjectObjectTuple5 call_149 = rotateRight_2(itemTy_10, right_4);
    struct StringIntIntObjectObjectTuple5 call_150 = segNodeWithRight_2(itemTy_10, call_149, node_10);
    struct StringIntIntObjectObjectTuple5 call_151 = rotateLeft_2(itemTy_10, call_150);
    if_28 = call_151;
    goto if_next_133;
if_next_133:;
    return if_28;
}

struct IntIntIntObjectObjectTuple5 doubleRight_1(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_10, struct IntIntIntObjectObjectTuple5 node_11) {
    int call_152 = segNodeToLength_1(node_11);
    struct IntIntIntObjectObjectTuple5 if_29;
    if ((call_152 < 2)) {
        goto then_137;
    } else {
        goto else_138;
    }
then_137:;
    if_29 = node_11;
    goto if_next_136;
else_138:;
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 call_153 = segNodeToChildren_1(node_11);
    struct IntIntIntObjectObjectTuple5 left_4 = call_153.t0;
    struct IntIntIntObjectObjectTuple5 call_154 = rotateLeft_1(itemTy_10, left_4);
    struct IntIntIntObjectObjectTuple5 call_155 = segNodeWithLeft_1(itemTy_10, call_154, node_11);
    struct IntIntIntObjectObjectTuple5 call_156 = rotateRight_1(itemTy_10, call_155);
    if_29 = call_156;
    goto if_next_136;
if_next_136:;
    return if_29;
}

struct StringIntIntObjectObjectTuple5 doubleRight_2(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_10, struct StringIntIntObjectObjectTuple5 node_11) {
    int call_157 = segNodeToLength_2(node_11);
    struct StringIntIntObjectObjectTuple5 if_30;
    if ((call_157 < 2)) {
        goto then_140;
    } else {
        goto else_141;
    }
then_140:;
    if_30 = node_11;
    goto if_next_139;
else_141:;
    struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2 call_158 = segNodeToChildren_2(node_11);
    struct StringIntIntObjectObjectTuple5 left_4 = call_158.t0;
    struct StringIntIntObjectObjectTuple5 call_159 = rotateLeft_2(itemTy_10, left_4);
    struct StringIntIntObjectObjectTuple5 call_160 = segNodeWithLeft_2(itemTy_10, call_159, node_11);
    struct StringIntIntObjectObjectTuple5 call_161 = rotateRight_2(itemTy_10, call_160);
    if_30 = call_161;
    goto if_next_139;
if_next_139:;
    return if_30;
}

int toBalance_1(struct IntIntIntObjectObjectTuple5 node_12) {
    int call_162 = segNodeToLength_1(node_12);
    int if_31;
    if ((call_162 < 2)) {
        goto then_143;
    } else {
        goto else_144;
    }
then_143:;
    if_31 = 0;
    goto if_next_142;
else_144:;
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 call_163 = segNodeToChildren_1(node_12);
    struct IntIntIntObjectObjectTuple5 left_5 = call_163.t0;
    struct IntIntIntObjectObjectTuple5 right_5 = call_163.t1;
    int call_164 = segNodeToHeight_1(right_5);
    int call_165 = segNodeToHeight_1(left_5);
    if_31 = (call_164 - call_165);
    goto if_next_142;
if_next_142:;
    return if_31;
}

int toBalance_2(struct StringIntIntObjectObjectTuple5 node_12) {
    int call_166 = segNodeToLength_2(node_12);
    int if_32;
    if ((call_166 < 2)) {
        goto then_146;
    } else {
        goto else_147;
    }
then_146:;
    if_32 = 0;
    goto if_next_145;
else_147:;
    struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2 call_167 = segNodeToChildren_2(node_12);
    struct StringIntIntObjectObjectTuple5 left_5 = call_167.t0;
    struct StringIntIntObjectObjectTuple5 right_5 = call_167.t1;
    int call_168 = segNodeToHeight_2(right_5);
    int call_169 = segNodeToHeight_2(left_5);
    if_32 = (call_168 - call_169);
    goto if_next_145;
if_next_145:;
    return if_32;
}

struct IntIntIntObjectObjectTuple5 segNodeMakeBalanced_1(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_10, struct IntIntIntObjectObjectTuple5 node_7) {
    int call_170 = toBalance_1(node_7);
    int selfBalance_ = call_170;
    int if_33;
    if ((selfBalance_ >= (0 - 1))) {
        goto then_149;
    } else {
        goto else_150;
    }
then_149:;
    if_33 = (1 >= selfBalance_);
    goto if_next_148;
else_150:;
    if_33 = 0;
    goto if_next_148;
if_next_148:;
    struct IntIntIntObjectObjectTuple5 if_34;
    if (if_33) {
        goto then_152;
    } else {
        goto else_153;
    }
then_152:;
    if_34 = node_7;
    goto if_next_151;
else_153:;
    int call_171 = segNodeToLength_1(node_7);
    struct IntIntIntObjectObjectTuple5 if_35;
    if ((call_171 < 2)) {
        goto then_155;
    } else {
        goto else_156;
    }
then_155:;
    if_35 = node_7;
    goto if_next_154;
else_156:;
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 call_172 = segNodeToChildren_1(node_7);
    struct IntIntIntObjectObjectTuple5 left_6 = call_172.t0;
    struct IntIntIntObjectObjectTuple5 right_6 = call_172.t1;
    struct IntIntIntObjectObjectTuple5 if_36;
    if ((selfBalance_ >= 2)) {
        goto then_158;
    } else {
        goto else_162;
    }
then_158:;
    int call_173 = toBalance_1(right_6);
    struct IntIntIntObjectObjectTuple5 if_37;
    if ((call_173 < 0)) {
        goto then_160;
    } else {
        goto else_161;
    }
then_160:;
    struct IntIntIntObjectObjectTuple5 call_174 = doubleLeft_1(itemTy_10, node_7);
    if_37 = call_174;
    goto if_next_159;
else_161:;
    struct IntIntIntObjectObjectTuple5 call_175 = rotateLeft_1(itemTy_10, node_7);
    if_37 = call_175;
    goto if_next_159;
if_next_159:;
    if_36 = if_37;
    goto if_next_157;
else_162:;
    int call_176 = toBalance_1(left_6);
    struct IntIntIntObjectObjectTuple5 if_38;
    if ((0 < call_176)) {
        goto then_164;
    } else {
        goto else_165;
    }
then_164:;
    struct IntIntIntObjectObjectTuple5 call_177 = doubleRight_1(itemTy_10, node_7);
    if_38 = call_177;
    goto if_next_163;
else_165:;
    struct IntIntIntObjectObjectTuple5 call_178 = rotateRight_1(itemTy_10, node_7);
    if_38 = call_178;
    goto if_next_163;
if_next_163:;
    if_36 = if_38;
    goto if_next_157;
if_next_157:;
    if_35 = if_36;
    goto if_next_154;
if_next_154:;
    if_34 = if_35;
    goto if_next_151;
if_next_151:;
    return if_34;
}

struct StringIntIntObjectObjectTuple5 segNodeMakeBalanced_2(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_10, struct StringIntIntObjectObjectTuple5 node_7) {
    int call_179 = toBalance_2(node_7);
    int selfBalance_ = call_179;
    int if_39;
    if ((selfBalance_ >= (0 - 1))) {
        goto then_167;
    } else {
        goto else_168;
    }
then_167:;
    if_39 = (1 >= selfBalance_);
    goto if_next_166;
else_168:;
    if_39 = 0;
    goto if_next_166;
if_next_166:;
    struct StringIntIntObjectObjectTuple5 if_40;
    if (if_39) {
        goto then_170;
    } else {
        goto else_171;
    }
then_170:;
    if_40 = node_7;
    goto if_next_169;
else_171:;
    int call_180 = segNodeToLength_2(node_7);
    struct StringIntIntObjectObjectTuple5 if_41;
    if ((call_180 < 2)) {
        goto then_173;
    } else {
        goto else_174;
    }
then_173:;
    if_41 = node_7;
    goto if_next_172;
else_174:;
    struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2 call_181 = segNodeToChildren_2(node_7);
    struct StringIntIntObjectObjectTuple5 left_6 = call_181.t0;
    struct StringIntIntObjectObjectTuple5 right_6 = call_181.t1;
    struct StringIntIntObjectObjectTuple5 if_42;
    if ((selfBalance_ >= 2)) {
        goto then_176;
    } else {
        goto else_180;
    }
then_176:;
    int call_182 = toBalance_2(right_6);
    struct StringIntIntObjectObjectTuple5 if_43;
    if ((call_182 < 0)) {
        goto then_178;
    } else {
        goto else_179;
    }
then_178:;
    struct StringIntIntObjectObjectTuple5 call_183 = doubleLeft_2(itemTy_10, node_7);
    if_43 = call_183;
    goto if_next_177;
else_179:;
    struct StringIntIntObjectObjectTuple5 call_184 = rotateLeft_2(itemTy_10, node_7);
    if_43 = call_184;
    goto if_next_177;
if_next_177:;
    if_42 = if_43;
    goto if_next_175;
else_180:;
    int call_185 = toBalance_2(left_6);
    struct StringIntIntObjectObjectTuple5 if_44;
    if ((0 < call_185)) {
        goto then_182;
    } else {
        goto else_183;
    }
then_182:;
    struct StringIntIntObjectObjectTuple5 call_186 = doubleRight_2(itemTy_10, node_7);
    if_44 = call_186;
    goto if_next_181;
else_183:;
    struct StringIntIntObjectObjectTuple5 call_187 = rotateRight_2(itemTy_10, node_7);
    if_44 = call_187;
    goto if_next_181;
if_next_181:;
    if_42 = if_44;
    goto if_next_175;
if_next_175:;
    if_41 = if_42;
    goto if_next_172;
if_next_172:;
    if_40 = if_41;
    goto if_next_169;
if_next_169:;
    return if_40;
}

struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 {
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 t0;
    struct IntIntIntObjectObjectTuple5 t1;
    void* t2;
};

struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 segTreeNew_2(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_11) {
    struct IntIntIntObjectObjectTuple5 call_188 = segItemTypeToEmptyNode_2(itemTy_11);
    struct IntIntIntObjectObjectTuple5 emptyNode_2 = call_188;
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 tuple_23;
    tuple_23.t0 = itemTy_11;
    tuple_23.t1 = emptyNode_2;
    tuple_23.t2 = 0;
    return tuple_23;
}

struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4StringIntIntObjectObjectTuple5ObjectTuple3 {
    struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 t0;
    struct StringIntIntObjectObjectTuple5 t1;
    void* t2;
};

struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4StringIntIntObjectObjectTuple5ObjectTuple3 segTreeNew_1(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_11) {
    struct StringIntIntObjectObjectTuple5 call_189 = segItemTypeToEmptyNode_1(itemTy_11);
    struct StringIntIntObjectObjectTuple5 emptyNode_2 = call_189;
    struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4StringIntIntObjectObjectTuple5ObjectTuple3 tuple_24;
    tuple_24.t0 = itemTy_11;
    tuple_24.t1 = emptyNode_2;
    tuple_24.t2 = 0;
    return tuple_24;
}

struct IntIntIntObjectObjectTuple5 segTreeToRoot_1(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 self_4) {
    struct IntIntIntObjectObjectTuple5 node_13 = self_4.t1;
    return node_13;
}

struct StringIntIntObjectObjectTuple5 segTreeToRoot_2(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4StringIntIntObjectObjectTuple5ObjectTuple3 self_4) {
    struct StringIntIntObjectObjectTuple5 node_13 = self_4.t1;
    return node_13;
}

int segTreeToLength_1(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 self_5) {
    struct IntIntIntObjectObjectTuple5 call_190 = segTreeToRoot_1(self_5);
    int call_191 = segNodeToLength_1(call_190);
    return call_191;
}

int segTreeToLength_2(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4StringIntIntObjectObjectTuple5ObjectTuple3 self_5) {
    struct StringIntIntObjectObjectTuple5 call_192 = segTreeToRoot_2(self_5);
    int call_193 = segNodeToLength_2(call_192);
    return call_193;
}

int segTreeToHeight_1(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 self_6) {
    struct IntIntIntObjectObjectTuple5 call_194 = segTreeToRoot_1(self_6);
    int call_195 = segNodeToHeight_1(call_194);
    return call_195;
}

int go_27(int index_6, struct IntIntIntObjectObjectTuple5 node_14) {
tailrec_184:;
    int item_4 = node_14.t0;
    int len_14 = node_14.t1;
    int if_45;
    if ((index_6 < 0)) {
        goto then_186;
    } else {
        goto else_187;
    }
then_186:;
    if_45 = 1;
    goto if_next_185;
else_187:;
    if_45 = (index_6 >= len_14);
    goto if_next_185;
if_next_185:;
    int if_46;
    if (if_45) {
        goto then_189;
    } else {
        goto else_190;
    }
then_189:;
    printf("ERROR: segNodeGet out of range (index = %d, len = %d)\n", index_6, len_14);
    int call_196 = 0;
    exit(1);
    if_46 = 0;
    goto if_next_188;
else_190:;
    if_46 = 0;
    goto if_next_188;
if_next_188:;
    milone_assert((len_14 != 0), 264, 4);
    int call_197 = 0;
    int if_47;
    if ((len_14 == 1)) {
        goto then_192;
    } else {
        goto else_193;
    }
then_192:;
    if_47 = item_4;
    goto if_next_191;
else_193:;
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 call_198 = segNodeToChildren_1(node_14);
    struct IntIntIntObjectObjectTuple5 left_7 = call_198.t0;
    struct IntIntIntObjectObjectTuple5 right_7 = call_198.t1;
    int call_199 = segNodeToLength_1(left_7);
    int leftLen_1 = call_199;
    int if_48;
    if ((index_6 < leftLen_1)) {
        goto then_195;
    } else {
        goto else_196;
    }
then_195:;
    int arg_82 = index_6;
    struct IntIntIntObjectObjectTuple5 arg_83 = left_7;
    index_6 = arg_82;
    node_14 = arg_83;
    goto tailrec_184;
    if_48 = 0;
    goto if_next_194;
else_196:;
    int arg_84 = (index_6 - leftLen_1);
    struct IntIntIntObjectObjectTuple5 arg_85 = right_7;
    index_6 = arg_84;
    node_14 = arg_85;
    goto tailrec_184;
    if_48 = 0;
    goto if_next_194;
if_next_194:;
    if_47 = if_48;
    goto if_next_191;
if_next_191:;
    return if_47;
}

struct String go_37(int index_6, struct StringIntIntObjectObjectTuple5 node_14) {
tailrec_197:;
    struct String item_4 = node_14.t0;
    int len_14 = node_14.t1;
    int if_49;
    if ((index_6 < 0)) {
        goto then_199;
    } else {
        goto else_200;
    }
then_199:;
    if_49 = 1;
    goto if_next_198;
else_200:;
    if_49 = (index_6 >= len_14);
    goto if_next_198;
if_next_198:;
    int if_50;
    if (if_49) {
        goto then_202;
    } else {
        goto else_203;
    }
then_202:;
    printf("ERROR: segNodeGet out of range (index = %d, len = %d)\n", index_6, len_14);
    int call_200 = 0;
    exit(1);
    if_50 = 0;
    goto if_next_201;
else_203:;
    if_50 = 0;
    goto if_next_201;
if_next_201:;
    milone_assert((len_14 != 0), 264, 4);
    int call_201 = 0;
    struct String if_51;
    if ((len_14 == 1)) {
        goto then_205;
    } else {
        goto else_206;
    }
then_205:;
    if_51 = item_4;
    goto if_next_204;
else_206:;
    struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2 call_202 = segNodeToChildren_2(node_14);
    struct StringIntIntObjectObjectTuple5 left_7 = call_202.t0;
    struct StringIntIntObjectObjectTuple5 right_7 = call_202.t1;
    int call_203 = segNodeToLength_2(left_7);
    int leftLen_1 = call_203;
    struct String if_52;
    if ((index_6 < leftLen_1)) {
        goto then_208;
    } else {
        goto else_209;
    }
then_208:;
    int arg_86 = index_6;
    struct StringIntIntObjectObjectTuple5 arg_87 = left_7;
    index_6 = arg_86;
    node_14 = arg_87;
    goto tailrec_197;
    if_52 = ((struct String){});
    goto if_next_207;
else_209:;
    int arg_88 = (index_6 - leftLen_1);
    struct StringIntIntObjectObjectTuple5 arg_89 = right_7;
    index_6 = arg_88;
    node_14 = arg_89;
    goto tailrec_197;
    if_52 = ((struct String){});
    goto if_next_207;
if_next_207:;
    if_51 = if_52;
    goto if_next_204;
if_next_204:;
    return if_51;
}

int segTreeGet_1(int index_5, struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 self_8) {
    struct IntIntIntObjectObjectTuple5 call_204 = segTreeToRoot_1(self_8);
    int call_205 = go_27(index_5, call_204);
    return call_205;
}

struct String segTreeGet_2(int index_5, struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4StringIntIntObjectObjectTuple5ObjectTuple3 self_8) {
    struct StringIntIntObjectObjectTuple5 call_206 = segTreeToRoot_2(self_8);
    struct String call_207 = go_37(index_5, call_206);
    return call_207;
}

int go_26(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_12, struct IntIntTuple2 e_, struct IntIntTuple2 q_, struct IntIntIntObjectObjectTuple5 node_15) {
    int call_208 = intervalIsDisjoint_(q_, e_);
    int if_53;
    if (call_208) {
        goto then_211;
    } else {
        goto else_212;
    }
then_211:;
    int call_209 = segItemTypeToEmptyItem_1(itemTy_12);
    if_53 = call_209;
    goto if_next_210;
else_212:;
    int call_210 = intervalCovers_(q_, e_);
    int if_54;
    if (call_210) {
        goto then_214;
    } else {
        goto else_215;
    }
then_214:;
    int call_211 = segNodeToItem_1(node_15);
    if_54 = call_211;
    goto if_next_213;
else_215:;
    int call_212 = segNodeIsEmpty_1(node_15);
    milone_assert((!(call_212)), 286, 6);
    int call_213 = 0;
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 call_214 = segNodeToChildren_1(node_15);
    struct IntIntIntObjectObjectTuple5 leftNode_ = call_214.t0;
    struct IntIntIntObjectObjectTuple5 rightNode_ = call_214.t1;
    int el_ = e_.t0;
    int er_ = e_.t1;
    int call_215 = segNodeToLength_1(leftNode_);
    int m_1 = (el_ + call_215);
    struct IntIntTuple2 tuple_25;
    tuple_25.t0 = el_;
    tuple_25.t1 = m_1;
    int call_216 = go_26(itemTy_12, tuple_25, q_, leftNode_);
    int vl_ = call_216;
    struct IntIntTuple2 tuple_26;
    tuple_26.t0 = m_1;
    tuple_26.t1 = er_;
    int call_217 = go_26(itemTy_12, tuple_26, q_, rightNode_);
    int vr_ = call_217;
    struct IntIntIntFun2 call_218 = segItemTypeToAppend_1(itemTy_12);
    int app_10 = call_218.fun(call_218.env, vl_, vr_);
    if_54 = app_10;
    goto if_next_213;
if_next_213:;
    if_53 = if_54;
    goto if_next_210;
if_next_210:;
    return if_53;
}

int segTreeSum_1(int ql_, int qr_, struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 self_9) {
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_12 = self_9.t0;
    struct IntIntIntObjectObjectTuple5 root_ = self_9.t1;
    int call_219 = segNodeToLength_1(root_);
    int len_15 = call_219;
    struct IntIntTuple2 tuple_27;
    tuple_27.t0 = ql_;
    tuple_27.t1 = qr_;
    struct IntIntTuple2 q_1 = tuple_27;
    struct IntIntTuple2 tuple_28;
    tuple_28.t0 = 0;
    tuple_28.t1 = len_15;
    int call_220 = intervalIsDisjoint_(q_1, tuple_28);
    int if_55;
    if (call_220) {
        goto then_217;
    } else {
        goto else_218;
    }
then_217:;
    int call_221 = segItemTypeToEmptyItem_1(itemTy_12);
    if_55 = call_221;
    goto if_next_216;
else_218:;
    struct IntIntTuple2 tuple_29;
    tuple_29.t0 = 0;
    tuple_29.t1 = len_15;
    struct IntIntTuple2 e_1 = tuple_29;
    int call_222 = go_26(itemTy_12, e_1, q_1, root_);
    if_55 = call_222;
    goto if_next_216;
if_next_216:;
    return if_55;
}

struct IntIntIntObjectObjectTuple5 go_25(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_13, int newItem_, int index_8, struct IntIntIntObjectObjectTuple5 node_16) {
    int len_16 = node_16.t1;
    int height_2 = node_16.t2;
    void* children_1 = node_16.t3;
    int if_56;
    if ((index_8 < 0)) {
        goto then_220;
    } else {
        goto else_221;
    }
then_220:;
    if_56 = 1;
    goto if_next_219;
else_221:;
    if_56 = (index_8 >= len_16);
    goto if_next_219;
if_next_219:;
    int if_57;
    if (if_56) {
        goto then_223;
    } else {
        goto else_224;
    }
then_223:;
    printf("ERROR: segNodeSet out of range (index = %d, len = %d)\n", index_8, len_16);
    int call_223 = 0;
    exit(1);
    if_57 = 0;
    goto if_next_222;
else_224:;
    if_57 = 0;
    goto if_next_222;
if_next_222:;
    milone_assert((len_16 != 0), 317, 4);
    int call_224 = 0;
    struct IntIntIntObjectObjectTuple5 if_58;
    if ((len_16 == 1)) {
        goto then_226;
    } else {
        goto else_227;
    }
then_226:;
    struct IntIntIntObjectObjectTuple5 tuple_30;
    tuple_30.t0 = newItem_;
    tuple_30.t1 = len_16;
    tuple_30.t2 = height_2;
    tuple_30.t3 = children_1;
    tuple_30.t4 = 0;
    if_58 = tuple_30;
    goto if_next_225;
else_227:;
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 call_225 = segNodeToChildren_1(node_16);
    struct IntIntIntObjectObjectTuple5 left_8 = call_225.t0;
    struct IntIntIntObjectObjectTuple5 right_8 = call_225.t1;
    int call_226 = segNodeToLength_1(left_8);
    int leftLen_2 = call_226;
    struct IntIntIntObjectObjectTuple5 if_59;
    if ((index_8 < leftLen_2)) {
        goto then_229;
    } else {
        goto else_230;
    }
then_229:;
    struct IntIntIntObjectObjectTuple5 call_227 = go_25(itemTy_13, newItem_, index_8, left_8);
    struct IntIntIntObjectObjectTuple5 call_228 = segNodeWithLeft_1(itemTy_13, call_227, node_16);
    if_59 = call_228;
    goto if_next_228;
else_230:;
    struct IntIntIntObjectObjectTuple5 call_229 = go_25(itemTy_13, newItem_, (index_8 - leftLen_2), right_8);
    struct IntIntIntObjectObjectTuple5 call_230 = segNodeWithRight_1(itemTy_13, call_229, node_16);
    if_59 = call_230;
    goto if_next_228;
if_next_228:;
    if_58 = if_59;
    goto if_next_225;
if_next_225:;
    return if_58;
}

struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 segTreeSet_1(int index_7, int newItem_, struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 self_10) {
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_13 = self_10.t0;
    struct IntIntIntObjectObjectTuple5 root_1 = self_10.t1;
    struct IntIntIntObjectObjectTuple5 call_231 = go_25(itemTy_13, newItem_, index_7, root_1);
    struct IntIntIntObjectObjectTuple5 root_2 = call_231;
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 tuple_31;
    tuple_31.t0 = itemTy_13;
    tuple_31.t1 = root_2;
    tuple_31.t2 = 0;
    return tuple_31;
}

struct IntIntIntObjectObjectTuple5 go_24(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_14, int newItem_1, int index_10, struct IntIntIntObjectObjectTuple5 node_17) {
    int oldItem_ = node_17.t0;
    int len_17 = node_17.t1;
    milone_assert((len_17 >= index_10), 339, 4);
    int call_232 = 0;
    struct IntIntIntObjectObjectTuple5 if_60;
    if ((len_17 == 0)) {
        goto then_232;
    } else {
        goto else_233;
    }
then_232:;
    struct IntIntIntObjectObjectTuple5 call_233 = segNodeNewLeaf_1(itemTy_14, newItem_1);
    if_60 = call_233;
    goto if_next_231;
else_233:;
    struct IntIntIntObjectObjectTuple5 if_61;
    if ((len_17 == 1)) {
        goto then_235;
    } else {
        goto else_239;
    }
then_235:;
    struct IntIntIntObjectObjectTuple5 call_234 = segNodeNewLeaf_1(itemTy_14, oldItem_);
    struct IntIntIntObjectObjectTuple5 oldLeaf_ = call_234;
    struct IntIntIntObjectObjectTuple5 call_235 = segNodeNewLeaf_1(itemTy_14, newItem_1);
    struct IntIntIntObjectObjectTuple5 newLeaf_ = call_235;
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 if_62;
    if ((index_10 == 0)) {
        goto then_237;
    } else {
        goto else_238;
    }
then_237:;
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 tuple_32;
    tuple_32.t0 = newLeaf_;
    tuple_32.t1 = oldLeaf_;
    if_62 = tuple_32;
    goto if_next_236;
else_238:;
    milone_assert((index_10 == 1), 351, 10);
    int call_236 = 0;
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 tuple_33;
    tuple_33.t0 = oldLeaf_;
    tuple_33.t1 = newLeaf_;
    if_62 = tuple_33;
    goto if_next_236;
if_next_236:;
    struct IntIntIntObjectObjectTuple5 left_9 = if_62.t0;
    struct IntIntIntObjectObjectTuple5 right_9 = if_62.t1;
    struct IntIntIntObjectObjectTuple5 call_237 = segNodeNew_1(itemTy_14, left_9, right_9);
    if_61 = call_237;
    goto if_next_234;
else_239:;
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 call_238 = segNodeToChildren_1(node_17);
    struct IntIntIntObjectObjectTuple5 left_10 = call_238.t0;
    struct IntIntIntObjectObjectTuple5 right_10 = call_238.t1;
    int call_239 = segNodeToLength_1(left_10);
    int leftLen_3 = call_239;
    int call_240 = segNodeToLength_1(right_10);
    int rightLen_1 = call_240;
    milone_assert(((leftLen_3 + rightLen_1) == len_17), 360, 6);
    int call_241 = 0;
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 if_63;
    if ((index_10 < leftLen_3)) {
        goto then_241;
    } else {
        goto else_242;
    }
then_241:;
    struct IntIntIntObjectObjectTuple5 call_242 = go_24(itemTy_14, newItem_1, index_10, left_10);
    struct IntIntIntObjectObjectTuple5 left_12 = call_242;
    int call_243 = segNodeToLength_1(left_12);
    milone_assert((call_243 == (leftLen_3 + 1)), 365, 10);
    int call_244 = 0;
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 tuple_34;
    tuple_34.t0 = left_12;
    tuple_34.t1 = right_10;
    if_63 = tuple_34;
    goto if_next_240;
else_242:;
    struct IntIntIntObjectObjectTuple5 call_245 = go_24(itemTy_14, newItem_1, (index_10 - leftLen_3), right_10);
    struct IntIntIntObjectObjectTuple5 right_12 = call_245;
    int call_246 = segNodeToLength_1(right_12);
    milone_assert((call_246 == (rightLen_1 + 1)), 369, 10);
    int call_247 = 0;
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 tuple_35;
    tuple_35.t0 = left_10;
    tuple_35.t1 = right_12;
    if_63 = tuple_35;
    goto if_next_240;
if_next_240:;
    struct IntIntIntObjectObjectTuple5 left_11 = if_63.t0;
    struct IntIntIntObjectObjectTuple5 right_11 = if_63.t1;
    struct IntIntIntObjectObjectTuple5 call_248 = segNodeNew_1(itemTy_14, left_11, right_11);
    struct IntIntIntObjectObjectTuple5 call_249 = segNodeMakeBalanced_1(itemTy_14, call_248);
    if_61 = call_249;
    goto if_next_234;
if_next_234:;
    if_60 = if_61;
    goto if_next_231;
if_next_231:;
    return if_60;
}

struct StringIntIntObjectObjectTuple5 go_36(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_14, struct String newItem_1, int index_10, struct StringIntIntObjectObjectTuple5 node_17) {
    struct String oldItem_ = node_17.t0;
    int len_17 = node_17.t1;
    milone_assert((len_17 >= index_10), 339, 4);
    int call_250 = 0;
    struct StringIntIntObjectObjectTuple5 if_64;
    if ((len_17 == 0)) {
        goto then_244;
    } else {
        goto else_245;
    }
then_244:;
    struct StringIntIntObjectObjectTuple5 call_251 = segNodeNewLeaf_2(itemTy_14, newItem_1);
    if_64 = call_251;
    goto if_next_243;
else_245:;
    struct StringIntIntObjectObjectTuple5 if_65;
    if ((len_17 == 1)) {
        goto then_247;
    } else {
        goto else_251;
    }
then_247:;
    struct StringIntIntObjectObjectTuple5 call_252 = segNodeNewLeaf_2(itemTy_14, oldItem_);
    struct StringIntIntObjectObjectTuple5 oldLeaf_ = call_252;
    struct StringIntIntObjectObjectTuple5 call_253 = segNodeNewLeaf_2(itemTy_14, newItem_1);
    struct StringIntIntObjectObjectTuple5 newLeaf_ = call_253;
    struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2 if_66;
    if ((index_10 == 0)) {
        goto then_249;
    } else {
        goto else_250;
    }
then_249:;
    struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2 tuple_36;
    tuple_36.t0 = newLeaf_;
    tuple_36.t1 = oldLeaf_;
    if_66 = tuple_36;
    goto if_next_248;
else_250:;
    milone_assert((index_10 == 1), 351, 10);
    int call_254 = 0;
    struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2 tuple_37;
    tuple_37.t0 = oldLeaf_;
    tuple_37.t1 = newLeaf_;
    if_66 = tuple_37;
    goto if_next_248;
if_next_248:;
    struct StringIntIntObjectObjectTuple5 left_9 = if_66.t0;
    struct StringIntIntObjectObjectTuple5 right_9 = if_66.t1;
    struct StringIntIntObjectObjectTuple5 call_255 = segNodeNew_2(itemTy_14, left_9, right_9);
    if_65 = call_255;
    goto if_next_246;
else_251:;
    struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2 call_256 = segNodeToChildren_2(node_17);
    struct StringIntIntObjectObjectTuple5 left_10 = call_256.t0;
    struct StringIntIntObjectObjectTuple5 right_10 = call_256.t1;
    int call_257 = segNodeToLength_2(left_10);
    int leftLen_3 = call_257;
    int call_258 = segNodeToLength_2(right_10);
    int rightLen_1 = call_258;
    milone_assert(((leftLen_3 + rightLen_1) == len_17), 360, 6);
    int call_259 = 0;
    struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2 if_67;
    if ((index_10 < leftLen_3)) {
        goto then_253;
    } else {
        goto else_254;
    }
then_253:;
    struct StringIntIntObjectObjectTuple5 call_260 = go_36(itemTy_14, newItem_1, index_10, left_10);
    struct StringIntIntObjectObjectTuple5 left_12 = call_260;
    int call_261 = segNodeToLength_2(left_12);
    milone_assert((call_261 == (leftLen_3 + 1)), 365, 10);
    int call_262 = 0;
    struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2 tuple_38;
    tuple_38.t0 = left_12;
    tuple_38.t1 = right_10;
    if_67 = tuple_38;
    goto if_next_252;
else_254:;
    struct StringIntIntObjectObjectTuple5 call_263 = go_36(itemTy_14, newItem_1, (index_10 - leftLen_3), right_10);
    struct StringIntIntObjectObjectTuple5 right_12 = call_263;
    int call_264 = segNodeToLength_2(right_12);
    milone_assert((call_264 == (rightLen_1 + 1)), 369, 10);
    int call_265 = 0;
    struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2 tuple_39;
    tuple_39.t0 = left_10;
    tuple_39.t1 = right_12;
    if_67 = tuple_39;
    goto if_next_252;
if_next_252:;
    struct StringIntIntObjectObjectTuple5 left_11 = if_67.t0;
    struct StringIntIntObjectObjectTuple5 right_11 = if_67.t1;
    struct StringIntIntObjectObjectTuple5 call_266 = segNodeNew_2(itemTy_14, left_11, right_11);
    struct StringIntIntObjectObjectTuple5 call_267 = segNodeMakeBalanced_2(itemTy_14, call_266);
    if_65 = call_267;
    goto if_next_246;
if_next_246:;
    if_64 = if_65;
    goto if_next_243;
if_next_243:;
    return if_64;
}

struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 segTreeInsert_1(int index_9, int newItem_1, struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 self_11) {
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_14 = self_11.t0;
    struct IntIntIntObjectObjectTuple5 root_3 = self_11.t1;
    struct IntIntIntObjectObjectTuple5 call_268 = go_24(itemTy_14, newItem_1, index_9, root_3);
    struct IntIntIntObjectObjectTuple5 root_4 = call_268;
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 tuple_40;
    tuple_40.t0 = itemTy_14;
    tuple_40.t1 = root_4;
    tuple_40.t2 = 0;
    return tuple_40;
}

struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4StringIntIntObjectObjectTuple5ObjectTuple3 segTreeInsert_2(int index_9, struct String newItem_1, struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4StringIntIntObjectObjectTuple5ObjectTuple3 self_11) {
    struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_14 = self_11.t0;
    struct StringIntIntObjectObjectTuple5 root_3 = self_11.t1;
    struct StringIntIntObjectObjectTuple5 call_269 = go_36(itemTy_14, newItem_1, index_9, root_3);
    struct StringIntIntObjectObjectTuple5 root_4 = call_269;
    struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4StringIntIntObjectObjectTuple5ObjectTuple3 tuple_41;
    tuple_41.t0 = itemTy_14;
    tuple_41.t1 = root_4;
    tuple_41.t2 = 0;
    return tuple_41;
}

struct IntIntIntObjectObjectTuple5 go_35(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_15, int index_12, struct IntIntIntObjectObjectTuple5 node_18) {
    int len_18 = node_18.t1;
    milone_assert((index_12 < len_18), 384, 4);
    int call_270 = 0;
    milone_assert((len_18 != 0), 386, 4);
    int call_271 = 0;
    struct IntIntIntObjectObjectTuple5 if_68;
    if ((len_18 == 1)) {
        goto then_256;
    } else {
        goto else_257;
    }
then_256:;
    struct IntIntIntObjectObjectTuple5 call_272 = segItemTypeToEmptyNode_2(itemTy_15);
    if_68 = call_272;
    goto if_next_255;
else_257:;
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 call_273 = segNodeToChildren_1(node_18);
    struct IntIntIntObjectObjectTuple5 left_13 = call_273.t0;
    struct IntIntIntObjectObjectTuple5 right_13 = call_273.t1;
    int call_274 = segNodeToLength_1(left_13);
    int leftLen_4 = call_274;
    int call_275 = segNodeToLength_1(right_13);
    int rightLen_2 = call_275;
    milone_assert(((leftLen_4 + rightLen_2) == len_18), 394, 6);
    int call_276 = 0;
    struct IntIntIntObjectObjectTuple5 if_69;
    if ((index_12 < leftLen_4)) {
        goto then_259;
    } else {
        goto else_263;
    }
then_259:;
    struct IntIntIntObjectObjectTuple5 if_70;
    if ((leftLen_4 < 2)) {
        goto then_261;
    } else {
        goto else_262;
    }
then_261:;
    if_70 = right_13;
    goto if_next_260;
else_262:;
    struct IntIntIntObjectObjectTuple5 call_277 = go_35(itemTy_15, index_12, left_13);
    struct IntIntIntObjectObjectTuple5 call_278 = segNodeWithLeft_1(itemTy_15, call_277, node_18);
    if_70 = call_278;
    goto if_next_260;
if_next_260:;
    if_69 = if_70;
    goto if_next_258;
else_263:;
    struct IntIntIntObjectObjectTuple5 if_71;
    if ((rightLen_2 < 2)) {
        goto then_265;
    } else {
        goto else_266;
    }
then_265:;
    if_71 = left_13;
    goto if_next_264;
else_266:;
    struct IntIntIntObjectObjectTuple5 call_279 = go_35(itemTy_15, (index_12 - leftLen_4), right_13);
    struct IntIntIntObjectObjectTuple5 call_280 = segNodeWithRight_1(itemTy_15, call_279, node_18);
    if_71 = call_280;
    goto if_next_264;
if_next_264:;
    if_69 = if_71;
    goto if_next_258;
if_next_258:;
    struct IntIntIntObjectObjectTuple5 node_19 = if_69;
    struct IntIntIntObjectObjectTuple5 call_281 = segNodeMakeBalanced_1(itemTy_15, node_19);
    if_68 = call_281;
    goto if_next_255;
if_next_255:;
    return if_68;
}

struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 segTreeRemove_1(int index_11, struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 self_12) {
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_15 = self_12.t0;
    struct IntIntIntObjectObjectTuple5 root_5 = self_12.t1;
    struct IntIntIntObjectObjectTuple5 call_282 = go_35(itemTy_15, index_11, root_5);
    struct IntIntIntObjectObjectTuple5 root_6 = call_282;
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 tuple_42;
    tuple_42.t0 = itemTy_15;
    tuple_42.t1 = root_6;
    tuple_42.t2 = 0;
    return tuple_42;
}

struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4StringIntIntObjectObjectTuple5ObjectTuple3 segTreePush_2(struct String value_4, struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4StringIntIntObjectObjectTuple5ObjectTuple3 self_13) {
    int call_283 = segTreeToLength_2(self_13);
    int index_13 = call_283;
    struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4StringIntIntObjectObjectTuple5ObjectTuple3 call_284 = segTreeInsert_2(index_13, value_4, self_13);
    return call_284;
}

struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 segTreePush_1(int value_4, struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 self_13) {
    int call_285 = segTreeToLength_1(self_13);
    int index_13 = call_285;
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 call_286 = segTreeInsert_1(index_13, value_4, self_13);
    return call_286;
}

struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 segTreePop_1(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 self_14) {
    int call_287 = segTreeToLength_1(self_14);
    int index_14 = (call_287 - 1);
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 call_288 = segTreeRemove_1(index_14, self_14);
    return call_288;
}

struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 go_23(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 t_2, struct IntList* xs_22) {
tailrec_267:;
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 match_10;
    if ((!((!(xs_22))))) goto next_269;
    match_10 = t_2;
    goto end_match_268;
next_269:;
    if ((!(xs_22))) goto next_270;
    int x_6 = xs_22->head;
    struct IntList* xs_23 = xs_22->tail;
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 call_289 = segTreePush_1(x_6, t_2);
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 arg_90 = call_289;
    struct IntList* arg_91 = xs_23;
    t_2 = arg_90;
    xs_22 = arg_91;
    goto tailrec_267;
    match_10 = ((struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3){});
    goto end_match_268;
next_270:;
    exit(1);
end_match_268:;
    return match_10;
}

struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 segTreeOfList_1(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_16, struct IntList* xs_21) {
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 call_290 = segTreeNew_2(itemTy_16);
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 call_291 = go_23(call_290, xs_21);
    return call_291;
}

struct IntList* go_22(int len_19, struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 v_4, struct IntList* acc_3, int i_4) {
tailrec_271:;
    struct IntList* if_72;
    if ((i_4 == len_19)) {
        goto then_273;
    } else {
        goto else_274;
    }
then_273:;
    struct IntList* call_292 = listRev_2(acc_3);
    if_72 = call_292;
    goto if_next_272;
else_274:;
    int call_293 = segTreeGet_1(i_4, v_4);
    int x_7 = call_293;
    int arg_92 = len_19;
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 arg_93 = v_4;
    struct IntList* list_21 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_21->head = x_7;
    list_21->tail = acc_3;
    struct IntList* arg_94 = list_21;
    int arg_95 = (i_4 + 1);
    len_19 = arg_92;
    v_4 = arg_93;
    acc_3 = arg_94;
    i_4 = arg_95;
    goto tailrec_271;
    if_72 = NULL;
    goto if_next_272;
if_next_272:;
    return if_72;
}

struct StringList* go_21(int len_19, struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4StringIntIntObjectObjectTuple5ObjectTuple3 v_4, struct StringList* acc_3, int i_4) {
tailrec_275:;
    struct StringList* if_73;
    if ((i_4 == len_19)) {
        goto then_277;
    } else {
        goto else_278;
    }
then_277:;
    struct StringList* call_294 = listRev_1(acc_3);
    if_73 = call_294;
    goto if_next_276;
else_278:;
    struct String call_295 = segTreeGet_2(i_4, v_4);
    struct String x_7 = call_295;
    int arg_96 = len_19;
    struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4StringIntIntObjectObjectTuple5ObjectTuple3 arg_97 = v_4;
    struct StringList* list_22 = (struct StringList*)milone_mem_alloc(1, sizeof(struct StringList));
    list_22->head = x_7;
    list_22->tail = acc_3;
    struct StringList* arg_98 = list_22;
    int arg_99 = (i_4 + 1);
    len_19 = arg_96;
    v_4 = arg_97;
    acc_3 = arg_98;
    i_4 = arg_99;
    goto tailrec_275;
    if_73 = NULL;
    goto if_next_276;
if_next_276:;
    return if_73;
}

struct IntList* segTreeToList_2(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 v_4) {
    int call_296 = segTreeToLength_1(v_4);
    int len_19 = call_296;
    struct IntList* call_297 = go_22(len_19, v_4, NULL, 0);
    return call_297;
}

struct StringList* segTreeToList_1(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4StringIntIntObjectObjectTuple5ObjectTuple3 v_4) {
    int call_298 = segTreeToLength_2(v_4);
    int len_19 = call_298;
    struct StringList* call_299 = go_21(len_19, v_4, NULL, 0);
    return call_299;
}

int intAdd_(int x_8, int y_3) {
    return (x_8 + y_3);
}

int fun_7(void* env_4, int arg_7, int arg_8) {
    int call_300 = intAdd_(arg_7, arg_8);
    return call_300;
}

struct String strAdd_(struct String x_9, struct String y_4) {
    return str_add(x_9, y_4);
}

struct String fun_8(void* env_5, struct String arg_9, struct String arg_10) {
    struct String call_301 = strAdd_(arg_9, arg_10);
    return call_301;
}

int fun_9(void* env_6, int arg_11, int arg_12) {
    int call_302 = intEq_(arg_11, arg_12);
    return call_302;
}

int fun_10(void* env_7, int arg_13, int arg_14) {
    int call_303 = intEq_(arg_13, arg_14);
    return call_303;
}

int fun_11(void* env_8, int arg_15, int arg_16) {
    int call_304 = intEq_(arg_15, arg_16);
    return call_304;
}

int fun_12(void* env_9, int arg_17, int arg_18) {
    int call_305 = intEq_(arg_17, arg_18);
    return call_305;
}

int fun_13(void* env_10, int arg_19, int arg_20) {
    int call_306 = intEq_(arg_19, arg_20);
    return call_306;
}

int testPushPop_(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 segItemTypeInt_, int arg_100) {
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 call_307 = segTreeNew_2(segItemTypeInt_);
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 call_308 = segTreePush_1(1, call_307);
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 call_309 = segTreePush_1(2, call_308);
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 v_5 = call_309;
    void* box_5 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_5))) = 0;
    void* env_19 = box_5;
    struct IntIntBoolFun2 fun_25 = (struct IntIntBoolFun2){.fun = fun_9, .env = env_19};
    struct IntList* list_24 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_24->head = 2;
    list_24->tail = NULL;
    struct IntList* list_23 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_23->head = 1;
    list_23->tail = list_24;
    struct IntList* call_310 = segTreeToList_2(v_5);
    int call_311 = listEq_2(fun_25, list_23, call_310);
    milone_assert(call_311, 462, 4);
    int call_312 = 0;
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 call_313 = segTreePush_1(3, v_5);
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 v_6 = call_313;
    void* box_6 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_6))) = 0;
    void* env_20 = box_6;
    struct IntIntBoolFun2 fun_26 = (struct IntIntBoolFun2){.fun = fun_10, .env = env_20};
    struct IntList* list_27 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_27->head = 3;
    list_27->tail = NULL;
    struct IntList* list_26 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_26->head = 2;
    list_26->tail = list_27;
    struct IntList* list_25 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_25->head = 1;
    list_25->tail = list_26;
    struct IntList* call_314 = segTreeToList_2(v_6);
    int call_315 = listEq_2(fun_26, list_25, call_314);
    milone_assert(call_315, 465, 4);
    int call_316 = 0;
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 call_317 = segTreePop_1(v_6);
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 v_7 = call_317;
    void* box_7 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_7))) = 0;
    void* env_21 = box_7;
    struct IntIntBoolFun2 fun_27 = (struct IntIntBoolFun2){.fun = fun_11, .env = env_21};
    struct IntList* list_29 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_29->head = 2;
    list_29->tail = NULL;
    struct IntList* list_28 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_28->head = 1;
    list_28->tail = list_29;
    struct IntList* call_318 = segTreeToList_2(v_7);
    int call_319 = listEq_2(fun_27, list_28, call_318);
    milone_assert(call_319, 468, 4);
    int call_320 = 0;
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 call_321 = segTreePop_1(v_7);
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 v_8 = call_321;
    void* box_8 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_8))) = 0;
    void* env_22 = box_8;
    struct IntIntBoolFun2 fun_28 = (struct IntIntBoolFun2){.fun = fun_12, .env = env_22};
    struct IntList* list_30 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_30->head = 1;
    list_30->tail = NULL;
    struct IntList* call_322 = segTreeToList_2(v_8);
    int call_323 = listEq_2(fun_28, list_30, call_322);
    milone_assert(call_323, 471, 4);
    int call_324 = 0;
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 call_325 = segTreePop_1(v_8);
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 v_9 = call_325;
    void* box_9 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_9))) = 0;
    void* env_23 = box_9;
    struct IntIntBoolFun2 fun_29 = (struct IntIntBoolFun2){.fun = fun_13, .env = env_23};
    struct IntList* call_326 = segTreeToList_2(v_9);
    int call_327 = listEq_2(fun_29, NULL, call_326);
    milone_assert(call_327, 474, 4);
    int call_328 = 0;
    return 0;
}

int fun_14(void* env_11, int arg_21, int arg_22) {
    int call_329 = intEq_(arg_21, arg_22);
    return call_329;
}

int fun_15(void* env_12, int arg_23, int arg_24) {
    int call_330 = intEq_(arg_23, arg_24);
    return call_330;
}

int testSet_(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 segItemTypeInt_, int arg_101) {
    struct IntList* list_33 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_33->head = 3;
    list_33->tail = NULL;
    struct IntList* list_32 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_32->head = 2;
    list_32->tail = list_33;
    struct IntList* list_31 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_31->head = 1;
    list_31->tail = list_32;
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 call_331 = segTreeOfList_1(segItemTypeInt_, list_31);
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 call_332 = segTreeSet_1(1, 22, call_331);
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 v_10 = call_332;
    void* box_10 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_10))) = 0;
    void* env_24 = box_10;
    struct IntIntBoolFun2 fun_30 = (struct IntIntBoolFun2){.fun = fun_14, .env = env_24};
    struct IntList* list_36 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_36->head = 3;
    list_36->tail = NULL;
    struct IntList* list_35 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_35->head = 22;
    list_35->tail = list_36;
    struct IntList* list_34 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_34->head = 1;
    list_34->tail = list_35;
    struct IntList* call_333 = segTreeToList_2(v_10);
    int call_334 = listEq_2(fun_30, list_34, call_333);
    milone_assert(call_334, 483, 4);
    int call_335 = 0;
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 call_336 = segTreeSet_1(0, 11, v_10);
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 call_337 = segTreeSet_1(2, 33, call_336);
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 v_11 = call_337;
    void* box_11 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_11))) = 0;
    void* env_25 = box_11;
    struct IntIntBoolFun2 fun_31 = (struct IntIntBoolFun2){.fun = fun_15, .env = env_25};
    struct IntList* list_39 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_39->head = 33;
    list_39->tail = NULL;
    struct IntList* list_38 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_38->head = 22;
    list_38->tail = list_39;
    struct IntList* list_37 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_37->head = 11;
    list_37->tail = list_38;
    struct IntList* call_338 = segTreeToList_2(v_11);
    int call_339 = listEq_2(fun_31, list_37, call_338);
    milone_assert(call_339, 486, 4);
    int call_340 = 0;
    return 0;
}

int testSum_(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 segItemTypeInt_, int arg_102) {
    struct IntList* list_45 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_45->head = 9;
    list_45->tail = NULL;
    struct IntList* list_44 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_44->head = 5;
    list_44->tail = list_45;
    struct IntList* list_43 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_43->head = 1;
    list_43->tail = list_44;
    struct IntList* list_42 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_42->head = 4;
    list_42->tail = list_43;
    struct IntList* list_41 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_41->head = 1;
    list_41->tail = list_42;
    struct IntList* list_40 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_40->head = 3;
    list_40->tail = list_41;
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 call_341 = segTreeOfList_1(segItemTypeInt_, list_40);
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 v_12 = call_341;
    int call_342 = segTreeSum_1(0, 6, v_12);
    milone_assert((call_342 == (((((3 + 1) + 4) + 1) + 5) + 9)), 494, 4);
    int call_343 = 0;
    int call_344 = segTreeSum_1(2, 4, v_12);
    milone_assert((call_344 == (4 + 1)), 495, 4);
    int call_345 = 0;
    return 0;
}

int sum_(int r_1, int l_1, int acc_4, int i_5, struct IntList* xs_25) {
tailrec_279:;
    int if_74;
    if ((i_5 == r_1)) {
        goto then_281;
    } else {
        goto else_282;
    }
then_281:;
    if_74 = acc_4;
    goto if_next_280;
else_282:;
    int match_11;
    if ((!(xs_25))) goto next_284;
    int x_10 = xs_25->head;
    struct IntList* xs_26 = xs_25->tail;
    int if_75;
    if ((i_5 < l_1)) {
        goto then_287;
    } else {
        goto else_288;
    }
then_287:;
    if_75 = acc_4;
    goto if_next_286;
else_288:;
    if_75 = (acc_4 + x_10);
    goto if_next_286;
if_next_286:;
    int acc_5 = if_75;
    int arg_103 = r_1;
    int arg_104 = l_1;
    int arg_105 = acc_5;
    int arg_106 = (i_5 + 1);
    struct IntList* arg_107 = xs_26;
    r_1 = arg_103;
    l_1 = arg_104;
    acc_4 = arg_105;
    i_5 = arg_106;
    xs_25 = arg_107;
    goto tailrec_279;
    match_11 = 0;
    goto end_match_283;
next_284:;
    int call_346 = failwith_1((struct String){.str = "NEVER", .len = 5});
    match_11 = call_346;
    goto end_match_283;
next_285:;
end_match_283:;
    if_74 = match_11;
    goto if_next_280;
if_next_280:;
    return if_74;
}

int go_15(int n_1, struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 v_13, struct IntList* xs_24, int l_1, int r_1) {
tailrec_289:;
    int if_76;
    if ((r_1 == n_1)) {
        goto then_291;
    } else {
        goto else_295;
    }
then_291:;
    int if_77;
    if ((l_1 < n_1)) {
        goto then_293;
    } else {
        goto else_294;
    }
then_293:;
    int arg_108 = n_1;
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 arg_109 = v_13;
    struct IntList* arg_110 = xs_24;
    int arg_111 = (l_1 + 1);
    int arg_112 = (l_1 + 1);
    n_1 = arg_108;
    v_13 = arg_109;
    xs_24 = arg_110;
    l_1 = arg_111;
    r_1 = arg_112;
    goto tailrec_289;
    if_77 = 0;
    goto if_next_292;
else_294:;
    if_77 = 0;
    goto if_next_292;
if_next_292:;
    if_76 = 0;
    goto if_next_290;
else_295:;
    int call_347 = sum_(r_1, l_1, 0, 0, xs_24);
    int expected_ = call_347;
    int call_348 = segTreeSum_1(l_1, r_1, v_13);
    int actual_ = call_348;
    milone_assert((actual_ == expected_), 522, 8);
    int call_349 = 0;
    int arg_113 = n_1;
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 arg_114 = v_13;
    struct IntList* arg_115 = xs_24;
    int arg_116 = l_1;
    int arg_117 = (r_1 + 1);
    n_1 = arg_113;
    v_13 = arg_114;
    xs_24 = arg_115;
    l_1 = arg_116;
    r_1 = arg_117;
    goto tailrec_289;
    if_76 = 0;
    goto if_next_290;
if_next_290:;
    return 0;
}

int testSumMore_(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 segItemTypeInt_, int arg_118) {
    struct IntList* list_51 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_51->head = 9;
    list_51->tail = NULL;
    struct IntList* list_50 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_50->head = 5;
    list_50->tail = list_51;
    struct IntList* list_49 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_49->head = 1;
    list_49->tail = list_50;
    struct IntList* list_48 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_48->head = 4;
    list_48->tail = list_49;
    struct IntList* list_47 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_47->head = 1;
    list_47->tail = list_48;
    struct IntList* list_46 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_46->head = 3;
    list_46->tail = list_47;
    struct IntList* xs_24 = list_46;
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 call_350 = segTreeOfList_1(segItemTypeInt_, xs_24);
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 v_13 = call_350;
    int call_351 = listLength_1(xs_24);
    int n_1 = call_351;
    int call_352 = go_15(n_1, v_13, xs_24, 0, 0);
    return 0;
}

int testBalance_(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 segItemTypeInt_, int arg_119) {
    struct IntList* call_353 = listReplicate_1(1, 1000);
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 call_354 = segTreeOfList_1(segItemTypeInt_, call_353);
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 v_14 = call_354;
    int call_355 = segTreeToHeight_1(v_14);
    milone_assert((call_355 < 100), 533, 4);
    int call_356 = 0;
    return 0;
}

int fun_16(void* env_13, struct String arg_25, struct String arg_26) {
    int call_357 = strEq_(arg_25, arg_26);
    return call_357;
}

int testPolymorphic_(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 segItemTypeStr_, int arg_120) {
    struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4StringIntIntObjectObjectTuple5ObjectTuple3 call_358 = segTreeNew_1(segItemTypeStr_);
    struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4StringIntIntObjectObjectTuple5ObjectTuple3 call_359 = segTreePush_2((struct String){.str = "a", .len = 1}, call_358);
    struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4StringIntIntObjectObjectTuple5ObjectTuple3 call_360 = segTreePush_2((struct String){.str = "b", .len = 1}, call_359);
    struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4StringIntIntObjectObjectTuple5ObjectTuple3 v_15 = call_360;
    void* box_12 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_12))) = 0;
    void* env_26 = box_12;
    struct StringStringBoolFun2 fun_32 = (struct StringStringBoolFun2){.fun = fun_16, .env = env_26};
    struct StringList* list_53 = (struct StringList*)milone_mem_alloc(1, sizeof(struct StringList));
    list_53->head = (struct String){.str = "b", .len = 1};
    list_53->tail = NULL;
    struct StringList* list_52 = (struct StringList*)milone_mem_alloc(1, sizeof(struct StringList));
    list_52->head = (struct String){.str = "a", .len = 1};
    list_52->tail = list_53;
    struct StringList* call_361 = segTreeToList_1(v_15);
    int call_362 = listEq_1(fun_32, list_52, call_361);
    milone_assert(call_362, 543, 4);
    int call_363 = 0;
    return 0;
}

int segTreeTest_(int arg_121) {
    void* box_13 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_13))) = 0;
    void* env_27 = box_13;
    struct IntIntIntFun2 fun_33 = (struct IntIntIntFun2){.fun = fun_7, .env = env_27};
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 call_364 = segItemTypeNew_1(0, fun_33);
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 segItemTypeInt_ = call_364;
    void* box_14 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_14))) = 0;
    void* env_28 = box_14;
    struct StringStringStringFun2 fun_34 = (struct StringStringStringFun2){.fun = fun_8, .env = env_28};
    struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 call_365 = segItemTypeNew_2((struct String){.str = "", .len = 0}, fun_34);
    struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 segItemTypeStr_ = call_365;
    int call_366 = testPushPop_(segItemTypeInt_, 0);
    int call_367 = testSet_(segItemTypeInt_, 0);
    int call_368 = testSum_(segItemTypeInt_, 0);
    int call_369 = testSumMore_(segItemTypeInt_, 0);
    int call_370 = testBalance_(segItemTypeInt_, 0);
    int call_371 = testPolymorphic_(segItemTypeStr_, 0);
    return 0;
}

int abc140aSolve_(int n_2) {
    return ((n_2 * n_2) * n_2);
}

int abc140aTest_(int arg_122) {
    int call_372 = abc140aSolve_(2);
    milone_assert((call_372 == 8), 8, 2);
    int call_373 = 0;
    int call_374 = abc140aSolve_(1);
    milone_assert((call_374 == 1), 9, 2);
    int call_375 = 0;
    return 0;
}

int abc140aMain_(int arg_123) {
    int call_376 = scanInt_(0);
    int n_3 = call_376;
    int call_377 = abc140aSolve_(n_3);
    int m_2 = call_377;
    printf("%d\n", m_2);
    int call_378 = 0;
    return 0;
}

int fun_22(int arg_124, int arg_125) {
    return 0;
}

int fun_17(void* env_14, int arg_27, int arg_28) {
    int call_379 = fun_22(arg_27, arg_28);
    return call_379;
}

int go_16(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 c_1, struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 b_1, struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 a_1, int n_4, int sum_1, int i_6) {
tailrec_296:;
    int if_78;
    if ((i_6 == n_4)) {
        goto then_298;
    } else {
        goto else_299;
    }
then_298:;
    if_78 = sum_1;
    goto if_next_297;
else_299:;
    int call_380 = segTreeGet_1(i_6, a_1);
    int ai_ = call_380;
    int call_381 = segTreeGet_1((ai_ - 1), b_1);
    int eat_ = call_381;
    int if_79;
    if (((i_6 + 1) < n_4)) {
        goto then_301;
    } else {
        goto else_302;
    }
then_301:;
    int call_382 = segTreeGet_1((i_6 + 1), a_1);
    if_79 = (call_382 == (ai_ + 1));
    goto if_next_300;
else_302:;
    if_79 = 0;
    goto if_next_300;
if_next_300:;
    int if_80;
    if (if_79) {
        goto then_304;
    } else {
        goto else_305;
    }
then_304:;
    int call_383 = segTreeGet_1((ai_ - 1), c_1);
    if_80 = call_383;
    goto if_next_303;
else_305:;
    if_80 = 0;
    goto if_next_303;
if_next_303:;
    int bonus_ = if_80;
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 arg_126 = c_1;
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 arg_127 = b_1;
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 arg_128 = a_1;
    int arg_129 = n_4;
    int arg_130 = ((sum_1 + eat_) + bonus_);
    int arg_131 = (i_6 + 1);
    c_1 = arg_126;
    b_1 = arg_127;
    a_1 = arg_128;
    n_4 = arg_129;
    sum_1 = arg_130;
    i_6 = arg_131;
    goto tailrec_296;
    if_78 = 0;
    goto if_next_297;
if_next_297:;
    return if_78;
}

int abc140bSolve_(int n_4, struct IntList* a_, struct IntList* b_, struct IntList* c_) {
    void* box_15 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_15))) = 0;
    void* env_29 = box_15;
    struct IntIntIntFun2 fun_35 = (struct IntIntIntFun2){.fun = fun_17, .env = env_29};
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 call_384 = segItemTypeNew_1(0, fun_35);
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 segItemTypeInt_1 = call_384;
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 call_385 = segTreeOfList_1(segItemTypeInt_1, a_);
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 a_1 = call_385;
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 call_386 = segTreeOfList_1(segItemTypeInt_1, b_);
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 b_1 = call_386;
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 call_387 = segTreeOfList_1(segItemTypeInt_1, c_);
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 c_1 = call_387;
    int call_388 = go_16(c_1, b_1, a_1, n_4, 0, 0);
    return call_388;
}

int f_(struct IntList* a_2, struct IntList* b_2, struct IntList* c_2) {
    int call_389 = listLength_1(a_2);
    int n_5 = call_389;
    int call_390 = listLength_1(b_2);
    milone_assert((call_390 == n_5), 31, 4);
    int call_391 = 0;
    int call_392 = listLength_1(c_2);
    milone_assert((call_392 == (n_5 - 1)), 32, 4);
    int call_393 = 0;
    int call_394 = abc140bSolve_(n_5, a_2, b_2, c_2);
    return call_394;
}

int case1_(int arg_132) {
    struct IntList* list_56 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_56->head = 2;
    list_56->tail = NULL;
    struct IntList* list_55 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_55->head = 1;
    list_55->tail = list_56;
    struct IntList* list_54 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_54->head = 3;
    list_54->tail = list_55;
    struct IntList* a_3 = list_54;
    struct IntList* list_59 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_59->head = 4;
    list_59->tail = NULL;
    struct IntList* list_58 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_58->head = 5;
    list_58->tail = list_59;
    struct IntList* list_57 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_57->head = 2;
    list_57->tail = list_58;
    struct IntList* b_3 = list_57;
    struct IntList* list_61 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_61->head = 6;
    list_61->tail = NULL;
    struct IntList* list_60 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_60->head = 3;
    list_60->tail = list_61;
    struct IntList* c_3 = list_60;
    int call_395 = f_(a_3, b_3, c_3);
    return (call_395 == 14);
}

int case2_(int arg_133) {
    struct IntList* list_65 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_65->head = 1;
    list_65->tail = NULL;
    struct IntList* list_64 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_64->head = 4;
    list_64->tail = list_65;
    struct IntList* list_63 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_63->head = 3;
    list_63->tail = list_64;
    struct IntList* list_62 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_62->head = 2;
    list_62->tail = list_63;
    struct IntList* a_4 = list_62;
    struct IntList* list_69 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_69->head = 24;
    list_69->tail = NULL;
    struct IntList* list_68 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_68->head = 8;
    list_68->tail = list_69;
    struct IntList* list_67 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_67->head = 5;
    list_67->tail = list_68;
    struct IntList* list_66 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_66->head = 13;
    list_66->tail = list_67;
    struct IntList* b_4 = list_66;
    struct IntList* list_72 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_72->head = 15;
    list_72->tail = NULL;
    struct IntList* list_71 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_71->head = 9;
    list_71->tail = list_72;
    struct IntList* list_70 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_70->head = 45;
    list_70->tail = list_71;
    struct IntList* c_4 = list_70;
    int call_396 = f_(a_4, b_4, c_4);
    return (call_396 == 74);
}

int case3_(int arg_134) {
    struct IntList* list_74 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_74->head = 2;
    list_74->tail = NULL;
    struct IntList* list_73 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_73->head = 1;
    list_73->tail = list_74;
    struct IntList* a_5 = list_73;
    struct IntList* list_76 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_76->head = 50;
    list_76->tail = NULL;
    struct IntList* list_75 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_75->head = 50;
    list_75->tail = list_76;
    struct IntList* b_5 = list_75;
    struct IntList* list_77 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_77->head = 50;
    list_77->tail = NULL;
    struct IntList* c_5 = list_77;
    int call_397 = f_(a_5, b_5, c_5);
    return (call_397 == 150);
}

int abc140bTest_(int arg_135) {
    int call_398 = case1_(0);
    milone_assert(call_398, 41, 2);
    int call_399 = 0;
    int call_400 = case2_(0);
    milone_assert(call_400, 49, 2);
    int call_401 = 0;
    int call_402 = case3_(0);
    milone_assert(call_402, 57, 2);
    int call_403 = 0;
    return 0;
}

int abc140bMain_(int arg_136) {
    int call_404 = scanInt_(0);
    int n_6 = call_404;
    struct IntList* call_405 = scanIntList_(n_6);
    struct IntList* a_6 = call_405;
    struct IntList* call_406 = scanIntList_(n_6);
    struct IntList* b_6 = call_406;
    struct IntList* call_407 = scanIntList_((n_6 - 1));
    struct IntList* c_6 = call_407;
    int call_408 = abc140bSolve_(n_6, a_6, b_6, c_6);
    int m_3 = call_408;
    printf("%d\n", m_3);
    int call_409 = 0;
    return 0;
}

int fun_21(int arg_137, int arg_138) {
    return 0;
}

int fun_18(void* env_15, int arg_29, int arg_30) {
    int call_410 = fun_21(arg_29, arg_30);
    return call_410;
}

int fun_19(void* env_16, int arg_31, int arg_32) {
    int call_411 = intMax_(arg_31, arg_32);
    return call_411;
}

int fun_20(void* env_17, int arg_33, int arg_34) {
    int call_412 = intMin_(arg_33, arg_34);
    return call_412;
}

struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 go_20(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 perm_2, int n_7, struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 pos_1, int i_7) {
tailrec_306:;
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 if_81;
    if ((i_7 == (n_7 + 2))) {
        goto then_308;
    } else {
        goto else_309;
    }
then_308:;
    if_81 = pos_1;
    goto if_next_307;
else_309:;
    int call_413 = segTreeGet_1(i_7, perm_2);
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 call_414 = segTreeSet_1(call_413, i_7, pos_1);
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 pos_2 = call_414;
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 arg_139 = perm_2;
    int arg_140 = n_7;
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 arg_141 = pos_2;
    int arg_142 = (i_7 + 1);
    perm_2 = arg_139;
    n_7 = arg_140;
    pos_1 = arg_141;
    i_7 = arg_142;
    goto tailrec_306;
    if_81 = ((struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3){});
    goto if_next_307;
if_next_307:;
    return if_81;
}

int go_19(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 pos_, int n_7, int sum_2, struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 prev_1, struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 next_1, int p_) {
tailrec_310:;
    int if_82;
    if ((p_ < 1)) {
        goto then_312;
    } else {
        goto else_313;
    }
then_312:;
    if_82 = sum_2;
    goto if_next_311;
else_313:;
    int call_415 = segTreeGet_1(p_, pos_);
    int i_8 = call_415;
    int call_416 = segTreeSum_1(0, i_8, prev_1);
    int x_11 = call_416;
    int call_417 = segTreeSum_1(0, x_11, prev_1);
    int w_ = call_417;
    int if_83;
    if ((x_11 >= w_)) {
        goto then_315;
    } else {
        goto else_316;
    }
then_315:;
    if_83 = (x_11 < i_8);
    goto if_next_314;
else_316:;
    if_83 = 0;
    goto if_next_314;
if_next_314:;
    milone_assert(if_83, 58, 6);
    int call_418 = 0;
    int call_419 = segTreeSum_1((i_8 + 1), (n_7 + 2), next_1);
    int y_5 = call_419;
    int call_420 = segTreeSum_1((y_5 + 1), (n_7 + 2), next_1);
    int z_ = call_420;
    int if_84;
    if ((i_8 < y_5)) {
        goto then_318;
    } else {
        goto else_319;
    }
then_318:;
    if_84 = (z_ >= y_5);
    goto if_next_317;
else_319:;
    if_84 = 0;
    goto if_next_317;
if_next_317:;
    milone_assert(if_84, 62, 6);
    int call_421 = 0;
    int count_ = (((x_11 - w_) * (y_5 - i_8)) + ((i_8 - x_11) * (z_ - y_5)));
    int sum_3 = (sum_2 + (count_ * p_));
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 call_422 = segTreeSet_1(i_8, i_8, prev_1);
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 prev_2 = call_422;
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 call_423 = segTreeSet_1(i_8, i_8, next_1);
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 next_2 = call_423;
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 arg_143 = pos_;
    int arg_144 = n_7;
    int arg_145 = sum_3;
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 arg_146 = prev_2;
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 arg_147 = next_2;
    int arg_148 = (p_ - 1);
    pos_ = arg_143;
    n_7 = arg_144;
    sum_2 = arg_145;
    prev_1 = arg_146;
    next_1 = arg_147;
    p_ = arg_148;
    goto tailrec_310;
    if_82 = 0;
    goto if_next_311;
if_next_311:;
    return if_82;
}

int abc140eSolve_(int n_7, struct IntList* perm_) {
    void* box_16 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_16))) = 0;
    void* env_30 = box_16;
    struct IntIntIntFun2 fun_36 = (struct IntIntIntFun2){.fun = fun_18, .env = env_30};
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 call_424 = segItemTypeNew_1(0, fun_36);
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 segItemTypeInt_2 = call_424;
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 call_425 = segTreeOfList_1(segItemTypeInt_2, perm_);
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 perm_1 = call_425;
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 call_426 = segTreeInsert_1(0, (n_7 + 1), perm_1);
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 call_427 = segTreePush_1((n_7 + 2), call_426);
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 perm_2 = call_427;
    int call_428 = segTreeToLength_1(perm_2);
    milone_assert((call_428 == (n_7 + 2)), 22, 2);
    int call_429 = 0;
    void* box_17 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_17))) = 0;
    void* env_31 = box_17;
    struct IntIntIntFun2 fun_37 = (struct IntIntIntFun2){.fun = fun_19, .env = env_31};
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 call_430 = segItemTypeNew_1(0, fun_37);
    struct IntList* call_431 = listReplicate_1(0, (n_7 + 2));
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 call_432 = segTreeOfList_1(call_430, call_431);
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 prev_ = call_432;
    void* box_18 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_18))) = 0;
    void* env_32 = box_18;
    struct IntIntIntFun2 fun_38 = (struct IntIntIntFun2){.fun = fun_20, .env = env_32};
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 call_433 = segItemTypeNew_1((n_7 + 1), fun_38);
    struct IntList* call_434 = listReplicate_1((n_7 + 1), (n_7 + 2));
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 call_435 = segTreeOfList_1(call_433, call_434);
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 next_ = call_435;
    struct IntList* call_436 = listReplicate_1(0, (n_7 + 3));
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 call_437 = segTreeOfList_1(segItemTypeInt_2, call_436);
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 pos_3 = call_437;
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 call_438 = go_20(perm_2, n_7, pos_3, 0);
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 pos_ = call_438;
    int call_439 = go_19(pos_, n_7, 0, prev_, next_, n_7);
    return call_439;
}

int solve_(struct IntList* p_1, int expected_1) {
    int call_440 = listLength_1(p_1);
    int n_8 = call_440;
    int call_441 = abc140eSolve_(n_8, p_1);
    int actual_1 = call_441;
    int if_85;
    if ((actual_1 == expected_1)) {
        goto then_321;
    } else {
        goto else_322;
    }
then_321:;
    if_85 = 1;
    goto if_next_320;
else_322:;
    printf("actual=%d expected=%d\n", actual_1, expected_1);
    int call_442 = 0;
    if_85 = 0;
    goto if_next_320;
if_next_320:;
    return if_85;
}

int abc140eTest_(int arg_149) {
    struct IntList* list_80 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_80->head = 1;
    list_80->tail = NULL;
    struct IntList* list_79 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_79->head = 3;
    list_79->tail = list_80;
    struct IntList* list_78 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_78->head = 2;
    list_78->tail = list_79;
    int call_443 = solve_(list_78, 5);
    milone_assert(call_443, 88, 2);
    int call_444 = 0;
    struct IntList* list_85 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_85->head = 5;
    list_85->tail = NULL;
    struct IntList* list_84 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_84->head = 4;
    list_84->tail = list_85;
    struct IntList* list_83 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_83->head = 3;
    list_83->tail = list_84;
    struct IntList* list_82 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_82->head = 2;
    list_82->tail = list_83;
    struct IntList* list_81 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_81->head = 1;
    list_81->tail = list_82;
    int call_445 = solve_(list_81, 30);
    milone_assert(call_445, 89, 2);
    int call_446 = 0;
    struct IntList* list_93 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_93->head = 1;
    list_93->tail = NULL;
    struct IntList* list_92 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_92->head = 6;
    list_92->tail = list_93;
    struct IntList* list_91 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_91->head = 5;
    list_91->tail = list_92;
    struct IntList* list_90 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_90->head = 4;
    list_90->tail = list_91;
    struct IntList* list_89 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_89->head = 3;
    list_89->tail = list_90;
    struct IntList* list_88 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_88->head = 7;
    list_88->tail = list_89;
    struct IntList* list_87 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_87->head = 2;
    list_87->tail = list_88;
    struct IntList* list_86 = (struct IntList*)milone_mem_alloc(1, sizeof(struct IntList));
    list_86->head = 8;
    list_86->tail = list_87;
    int call_447 = solve_(list_86, 136);
    milone_assert(call_447, 90, 2);
    int call_448 = 0;
    return 0;
}

int abc140eMain_(int arg_150) {
    int call_449 = scanInt_(0);
    int n_9 = call_449;
    struct IntList* call_450 = scanIntList_(n_9);
    struct IntList* p_2 = call_450;
    int call_451 = abc140eSolve_(n_9, p_2);
    int m_4 = call_451;
    printf("%d\n", m_4);
    int call_452 = 0;
    return 0;
}

// static unitObj_;

// static typeInt_;

int main() {
    void* box_19 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_19))) = 0;
    unitObj_ = box_19;
    void* box_20 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_20))) = 0;
    void* env_33 = box_20;
    struct IntObjectFun1 fun_39 = (struct IntObjectFun1){.fun = fun_4, .env = env_33};
    void* box_21 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_21))) = 0;
    void* env_34 = box_21;
    struct ObjectIntIntFun2 fun_40 = (struct ObjectIntIntFun2){.fun = fun_5, .env = env_34};
    void* box_22 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_22))) = 0;
    void* env_35 = box_22;
    struct ObjectIntIntObjectFun3 fun_41 = (struct ObjectIntIntObjectFun3){.fun = fun_6, .env = env_35};
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6 tuple_43;
    tuple_43.t0 = 0;
    tuple_43.t1 = 4;
    tuple_43.t2 = fun_39;
    tuple_43.t3 = fun_40;
    tuple_43.t4 = fun_41;
    tuple_43.t5 = 0;
    typeInt_ = tuple_43;
    int call_453 = vectorTest_(0);
    int call_454 = segTreeTest_(0);
    int call_455 = abc140aTest_(0);
    int call_456 = abc140bTest_(0);
    int call_457 = abc140eTest_(0);
    return 0;
}
