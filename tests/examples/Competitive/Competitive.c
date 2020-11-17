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
    int match_;
    if ((!((!(xs_))))) goto next_2;
    match_ = 1;
    goto end_match_1;
next_2:;
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    return match_;
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
    int match_1;
    if ((!((!(xs_))))) goto next_5;
    match_1 = 1;
    goto end_match_4;
next_5:;
    match_1 = 0;
    goto end_match_4;
next_6:;
end_match_4:;
    return match_1;
}

struct IntList {
    int head;
    struct IntList* tail;
};

int listIsEmpty_3(struct IntList* xs_) {
    int match_2;
    if ((!((!(xs_))))) goto next_8;
    match_2 = 1;
    goto end_match_7;
next_8:;
    match_2 = 0;
    goto end_match_7;
next_9:;
end_match_7:;
    return match_2;
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
    int match_3;
    if ((!((!(xs_))))) goto next_11;
    match_3 = 1;
    goto end_match_10;
next_11:;
    match_3 = 0;
    goto end_match_10;
next_12:;
end_match_10:;
    return match_3;
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
    int match_4;
    if ((!((!(xs_))))) goto next_14;
    match_4 = 1;
    goto end_match_13;
next_14:;
    match_4 = 0;
    goto end_match_13;
next_15:;
end_match_13:;
    return match_4;
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
    int match_5;
    if ((!((!(xs_))))) goto next_17;
    match_5 = 1;
    goto end_match_16;
next_17:;
    match_5 = 0;
    goto end_match_16;
next_18:;
end_match_16:;
    return match_5;
}

int go_34(int len_1, struct StringList* xs_2) {
tailrec_19:;
    int match_6;
    if ((!((!(xs_2))))) goto next_21;
    match_6 = len_1;
    goto end_match_20;
next_21:;
    if ((!(xs_2))) goto next_22;
    struct StringList* xs_3 = xs_2->tail;
    int arg_37 = (len_1 + 1);
    struct StringList* arg_38 = xs_3;
    len_1 = arg_37;
    xs_2 = arg_38;
    goto tailrec_19;
    match_6 = 0;
    goto end_match_20;
next_22:;
    exit(1);
end_match_20:;
    return match_6;
}

int go_33(int len_1, struct IntList* xs_2) {
tailrec_23:;
    int match_7;
    if ((!((!(xs_2))))) goto next_25;
    match_7 = len_1;
    goto end_match_24;
next_25:;
    if ((!(xs_2))) goto next_26;
    struct IntList* xs_3 = xs_2->tail;
    int arg_39 = (len_1 + 1);
    struct IntList* arg_40 = xs_3;
    len_1 = arg_39;
    xs_2 = arg_40;
    goto tailrec_23;
    match_7 = 0;
    goto end_match_24;
next_26:;
    exit(1);
end_match_24:;
    return match_7;
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
    struct IntList* match_8;
    if ((!((!(xs_5))))) goto next_29;
    match_8 = acc_;
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
    match_8 = NULL;
    goto end_match_28;
next_30:;
    exit(1);
end_match_28:;
    return match_8;
}

struct StringList* go_38(struct StringList* acc_, struct StringList* xs_5) {
tailrec_31:;
    struct StringList* match_9;
    if ((!((!(xs_5))))) goto next_33;
    match_9 = acc_;
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
    match_9 = NULL;
    goto end_match_32;
next_34:;
    exit(1);
end_match_32:;
    return match_9;
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
    int match_10;
    struct IntListIntListTuple2 tuple_;
    tuple_.t0 = xs_8;
    tuple_.t1 = ys_1;
    if ((!((!(tuple_.t0))))) goto next_37;
    if ((!((!(tuple_.t1))))) goto next_37;
    match_10 = 1;
    goto end_match_36;
next_37:;
    if ((!(tuple_.t0))) goto next_38;
    int x_1 = tuple_.t0->head;
    struct IntList* xs_9 = tuple_.t0->tail;
    if ((!(tuple_.t1))) goto next_38;
    int y_ = tuple_.t1->head;
    struct IntList* ys_2 = tuple_.t1->tail;
    int if_;
    int app_ = itemEq_.fun(itemEq_.env, x_1, y_);
    if ((!(app_))) goto else_40;
    struct IntIntBoolFun2 arg_45 = itemEq_;
    struct IntList* arg_46 = xs_9;
    struct IntList* arg_47 = ys_2;
    itemEq_ = arg_45;
    xs_8 = arg_46;
    ys_1 = arg_47;
    goto tailrec_35;
    if_ = 0;
    goto end_if_41;
else_40:;
    if_ = 0;
end_if_41:;
    match_10 = if_;
    goto end_match_36;
next_38:;
    match_10 = 0;
    goto end_match_36;
next_39:;
end_match_36:;
    return match_10;
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
tailrec_42:;
    int match_11;
    struct StringListStringListTuple2 tuple_1;
    tuple_1.t0 = xs_8;
    tuple_1.t1 = ys_1;
    if ((!((!(tuple_1.t0))))) goto next_44;
    if ((!((!(tuple_1.t1))))) goto next_44;
    match_11 = 1;
    goto end_match_43;
next_44:;
    if ((!(tuple_1.t0))) goto next_45;
    struct String x_1 = tuple_1.t0->head;
    struct StringList* xs_9 = tuple_1.t0->tail;
    if ((!(tuple_1.t1))) goto next_45;
    struct String y_ = tuple_1.t1->head;
    struct StringList* ys_2 = tuple_1.t1->tail;
    int if_1;
    int app_1 = itemEq_.fun(itemEq_.env, x_1, y_);
    if ((!(app_1))) goto else_47;
    struct StringStringBoolFun2 arg_48 = itemEq_;
    struct StringList* arg_49 = xs_9;
    struct StringList* arg_50 = ys_2;
    itemEq_ = arg_48;
    xs_8 = arg_49;
    ys_1 = arg_50;
    goto tailrec_42;
    if_1 = 0;
    goto end_if_48;
else_47:;
    if_1 = 0;
end_if_48:;
    match_11 = if_1;
    goto end_match_43;
next_45:;
    match_11 = 0;
    goto end_match_43;
next_46:;
end_match_43:;
    return match_11;
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
tailrec_49:;
    struct IntList* if_2;
    if ((i_ != len_2)) goto else_50;
    if_2 = acc_1;
    goto end_if_51;
else_50:;
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
    goto tailrec_49;
    if_2 = NULL;
end_if_51:;
    return if_2;
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
tailrec_52:;
    struct IntList* if_3;
    if ((i_1 != len_3)) goto else_53;
    struct IntList* call_12 = listRev_2(acc_2);
    if_3 = call_12;
    goto end_if_54;
else_53:;
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
    goto tailrec_52;
    if_3 = NULL;
end_if_54:;
    return if_3;
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
    struct StringStringListTuple2 match_12;
    if ((!((!(xs_11))))) goto next_56;
    milone_assert((xn_ == 0), 81, 8);
    int call_15 = 0;
    struct StringStringListTuple2 tuple_2;
    tuple_2.t0 = (struct String){.str = "", .len = 0};
    tuple_2.t1 = NULL;
    match_12 = tuple_2;
    goto end_match_55;
next_56:;
    if ((!(xs_11))) goto next_57;
    struct String x_2 = xs_11->head;
    struct StringList* xs_12 = xs_11->tail;
    if ((xn_ != 1)) goto next_57;
    struct StringStringListTuple2 tuple_3;
    tuple_3.t0 = x_2;
    tuple_3.t1 = xs_12;
    match_12 = tuple_3;
    goto end_match_55;
next_57:;
    if ((!(xs_11))) goto next_58;
    struct String x_3 = xs_11->head;
    if ((!(xs_11->tail))) goto next_58;
    struct String y_1 = xs_11->tail->head;
    struct StringList* xs_13 = xs_11->tail->tail;
    if ((xn_ != 2)) goto next_58;
    struct StringStringListTuple2 tuple_4;
    tuple_4.t0 = str_add(x_3, y_1);
    tuple_4.t1 = xs_13;
    match_12 = tuple_4;
    goto end_match_55;
next_58:;
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
    match_12 = tuple_5;
    goto end_match_55;
next_59:;
end_match_55:;
    return match_12;
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
    int if_4;
    if ((second_1 >= first_1)) goto else_60;
    if_4 = second_1;
    goto end_if_61;
else_60:;
    if_4 = first_1;
end_if_61:;
    return if_4;
}

int intMax_(int first_2, int second_2) {
    int if_5;
    if ((first_2 >= second_2)) goto else_62;
    if_5 = second_2;
    goto end_if_63;
else_62:;
    if_5 = first_2;
end_if_63:;
    return if_5;
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
    int if_6;
    int if_7;
    if ((index_2 >= 0)) goto else_66;
    if_7 = 1;
    goto end_if_67;
else_66:;
    if_7 = (index_2 >= len_7);
end_if_67:;
    if ((!(if_7))) goto else_64;
    printf("ERROR: Out of range (len = %d, index = %d)\n", len_7, index_2);
    int call_31 = 0;
    exit(1);
    if_6 = 0;
    goto end_if_65;
else_64:;
    if_6 = 0;
end_if_65:;
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
tailrec_68:;
    int match_13;
    if ((!((!(xs_19))))) goto next_70;
    milone_assert((i_2 == len_9), 185, 12);
    int call_37 = 0;
    match_13 = 0;
    goto end_match_69;
next_70:;
    if ((!(xs_19))) goto next_71;
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
    goto tailrec_68;
    match_13 = 0;
    goto end_match_69;
next_71:;
    exit(1);
end_match_69:;
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
tailrec_72:;
    int if_8;
    if ((i_3 >= len_10)) goto else_73;
    int call_42 = scanInt_(0);
    int value_3 = call_42;
    int call_43 = vectorSet_1(i_3, value_3, v_1);
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3ObjectTuple6ObjectIntIntObjectTuple5 arg_68 = v_1;
    int arg_69 = len_10;
    int arg_70 = (i_3 + 1);
    v_1 = arg_68;
    len_10 = arg_69;
    i_3 = arg_70;
    goto tailrec_72;
    if_8 = 0;
    goto end_if_74;
else_73:;
    if_8 = 0;
end_if_74:;
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
    int if_9;
    if ((yl_ < xr_)) goto else_75;
    if_9 = 1;
    goto end_if_76;
else_75:;
    if_9 = (xl_ >= yr_);
end_if_76:;
    return if_9;
}

int intervalCovers_(struct IntIntTuple2 first_5, struct IntIntTuple2 second_5) {
    int xl_1 = first_5.t0;
    int xr_1 = first_5.t1;
    int yl_1 = second_5.t0;
    int yr_1 = second_5.t1;
    int if_10;
    if ((yl_1 < xl_1)) goto else_77;
    if_10 = (xr_1 >= yr_1);
    goto end_if_78;
else_77:;
    if_10 = 0;
end_if_78:;
    return if_10;
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
    int if_11;
    if ((leftLen_ < 1)) goto else_79;
    if_11 = (rightLen_ >= 1);
    goto end_if_80;
else_79:;
    if_11 = 0;
end_if_80:;
    milone_assert(if_11, 73, 4);
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
    int if_12;
    if ((leftLen_ < 1)) goto else_81;
    if_12 = (rightLen_ >= 1);
    goto end_if_82;
else_81:;
    if_12 = 0;
end_if_82:;
    milone_assert(if_12, 73, 4);
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
    struct IntIntIntObjectObjectTuple5 match_14;
    int call_87 = segNodeToLength_1(left_);
    int call_88 = segNodeToLength_1(right_);
    struct IntIntTuple2 tuple_19;
    tuple_19.t0 = call_87;
    tuple_19.t1 = call_88;
    if ((tuple_19.t0 != 0)) goto next_84;
    if ((tuple_19.t1 != 0)) goto next_84;
    struct IntIntIntObjectObjectTuple5 call_89 = segItemTypeToEmptyNode_2(itemTy_7);
    match_14 = call_89;
    goto end_match_83;
next_84:;
    if ((tuple_19.t0 != 0)) goto next_85;
    match_14 = right_;
    goto end_match_83;
next_85:;
    if ((tuple_19.t1 != 0)) goto next_86;
    match_14 = left_;
    goto end_match_83;
next_86:;
    struct IntIntIntObjectObjectTuple5 call_90 = doNew_1(right_, left_, itemTy_7, 0);
    match_14 = call_90;
    goto end_match_83;
next_87:;
end_match_83:;
    return match_14;
}

struct StringIntIntObjectObjectTuple5 segNodeNew_2(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_7, struct StringIntIntObjectObjectTuple5 left_, struct StringIntIntObjectObjectTuple5 right_) {
    struct StringIntIntObjectObjectTuple5 match_15;
    int call_91 = segNodeToLength_2(left_);
    int call_92 = segNodeToLength_2(right_);
    struct IntIntTuple2 tuple_20;
    tuple_20.t0 = call_91;
    tuple_20.t1 = call_92;
    if ((tuple_20.t0 != 0)) goto next_89;
    if ((tuple_20.t1 != 0)) goto next_89;
    struct StringIntIntObjectObjectTuple5 call_93 = segItemTypeToEmptyNode_1(itemTy_7);
    match_15 = call_93;
    goto end_match_88;
next_89:;
    if ((tuple_20.t0 != 0)) goto next_90;
    match_15 = right_;
    goto end_match_88;
next_90:;
    if ((tuple_20.t1 != 0)) goto next_91;
    match_15 = left_;
    goto end_match_88;
next_91:;
    struct StringIntIntObjectObjectTuple5 call_94 = doNew_2(right_, left_, itemTy_7, 0);
    match_15 = call_94;
    goto end_match_88;
next_92:;
end_match_88:;
    return match_15;
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
    struct IntIntIntObjectObjectTuple5 if_13;
    int call_118 = segNodeToLength_1(node_8);
    if ((call_118 >= 2)) goto else_93;
    if_13 = node_8;
    goto end_if_94;
else_93:;
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 call_119 = segNodeToChildren_1(node_8);
    struct IntIntIntObjectObjectTuple5 right_3 = call_119.t1;
    struct IntIntIntObjectObjectTuple5 if_14;
    int call_120 = segNodeToLength_1(right_3);
    if ((call_120 >= 2)) goto else_95;
    if_14 = node_8;
    goto end_if_96;
else_95:;
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 call_121 = segNodeToChildren_1(right_3);
    struct IntIntIntObjectObjectTuple5 x_5 = call_121.t0;
    struct IntIntIntObjectObjectTuple5 call_122 = segNodeWithRight_1(itemTy_10, x_5, node_8);
    struct IntIntIntObjectObjectTuple5 u_ = call_122;
    struct IntIntIntObjectObjectTuple5 call_123 = segNodeWithLeft_1(itemTy_10, u_, right_3);
    struct IntIntIntObjectObjectTuple5 t_ = call_123;
    if_14 = t_;
end_if_96:;
    if_13 = if_14;
end_if_94:;
    return if_13;
}

struct StringIntIntObjectObjectTuple5 rotateLeft_2(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_10, struct StringIntIntObjectObjectTuple5 node_8) {
    struct StringIntIntObjectObjectTuple5 if_15;
    int call_124 = segNodeToLength_2(node_8);
    if ((call_124 >= 2)) goto else_97;
    if_15 = node_8;
    goto end_if_98;
else_97:;
    struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2 call_125 = segNodeToChildren_2(node_8);
    struct StringIntIntObjectObjectTuple5 right_3 = call_125.t1;
    struct StringIntIntObjectObjectTuple5 if_16;
    int call_126 = segNodeToLength_2(right_3);
    if ((call_126 >= 2)) goto else_99;
    if_16 = node_8;
    goto end_if_100;
else_99:;
    struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2 call_127 = segNodeToChildren_2(right_3);
    struct StringIntIntObjectObjectTuple5 x_5 = call_127.t0;
    struct StringIntIntObjectObjectTuple5 call_128 = segNodeWithRight_2(itemTy_10, x_5, node_8);
    struct StringIntIntObjectObjectTuple5 u_ = call_128;
    struct StringIntIntObjectObjectTuple5 call_129 = segNodeWithLeft_2(itemTy_10, u_, right_3);
    struct StringIntIntObjectObjectTuple5 t_ = call_129;
    if_16 = t_;
end_if_100:;
    if_15 = if_16;
end_if_98:;
    return if_15;
}

struct IntIntIntObjectObjectTuple5 rotateRight_1(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_10, struct IntIntIntObjectObjectTuple5 node_9) {
    struct IntIntIntObjectObjectTuple5 if_17;
    int call_130 = segNodeToLength_1(node_9);
    if ((call_130 >= 2)) goto else_101;
    if_17 = node_9;
    goto end_if_102;
else_101:;
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 call_131 = segNodeToChildren_1(node_9);
    struct IntIntIntObjectObjectTuple5 left_3 = call_131.t0;
    struct IntIntIntObjectObjectTuple5 if_18;
    int call_132 = segNodeToLength_1(left_3);
    if ((call_132 >= 2)) goto else_103;
    if_18 = node_9;
    goto end_if_104;
else_103:;
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 call_133 = segNodeToChildren_1(left_3);
    struct IntIntIntObjectObjectTuple5 y_2 = call_133.t1;
    struct IntIntIntObjectObjectTuple5 call_134 = segNodeWithLeft_1(itemTy_10, y_2, node_9);
    struct IntIntIntObjectObjectTuple5 u_1 = call_134;
    struct IntIntIntObjectObjectTuple5 call_135 = segNodeWithRight_1(itemTy_10, u_1, left_3);
    struct IntIntIntObjectObjectTuple5 t_1 = call_135;
    if_18 = t_1;
end_if_104:;
    if_17 = if_18;
end_if_102:;
    return if_17;
}

struct StringIntIntObjectObjectTuple5 rotateRight_2(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_10, struct StringIntIntObjectObjectTuple5 node_9) {
    struct StringIntIntObjectObjectTuple5 if_19;
    int call_136 = segNodeToLength_2(node_9);
    if ((call_136 >= 2)) goto else_105;
    if_19 = node_9;
    goto end_if_106;
else_105:;
    struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2 call_137 = segNodeToChildren_2(node_9);
    struct StringIntIntObjectObjectTuple5 left_3 = call_137.t0;
    struct StringIntIntObjectObjectTuple5 if_20;
    int call_138 = segNodeToLength_2(left_3);
    if ((call_138 >= 2)) goto else_107;
    if_20 = node_9;
    goto end_if_108;
else_107:;
    struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2 call_139 = segNodeToChildren_2(left_3);
    struct StringIntIntObjectObjectTuple5 y_2 = call_139.t1;
    struct StringIntIntObjectObjectTuple5 call_140 = segNodeWithLeft_2(itemTy_10, y_2, node_9);
    struct StringIntIntObjectObjectTuple5 u_1 = call_140;
    struct StringIntIntObjectObjectTuple5 call_141 = segNodeWithRight_2(itemTy_10, u_1, left_3);
    struct StringIntIntObjectObjectTuple5 t_1 = call_141;
    if_20 = t_1;
end_if_108:;
    if_19 = if_20;
end_if_106:;
    return if_19;
}

struct IntIntIntObjectObjectTuple5 doubleLeft_1(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_10, struct IntIntIntObjectObjectTuple5 node_10) {
    struct IntIntIntObjectObjectTuple5 if_21;
    int call_142 = segNodeToLength_1(node_10);
    if ((call_142 >= 2)) goto else_109;
    if_21 = node_10;
    goto end_if_110;
else_109:;
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 call_143 = segNodeToChildren_1(node_10);
    struct IntIntIntObjectObjectTuple5 right_4 = call_143.t1;
    struct IntIntIntObjectObjectTuple5 call_144 = rotateRight_1(itemTy_10, right_4);
    struct IntIntIntObjectObjectTuple5 call_145 = segNodeWithRight_1(itemTy_10, call_144, node_10);
    struct IntIntIntObjectObjectTuple5 call_146 = rotateLeft_1(itemTy_10, call_145);
    if_21 = call_146;
end_if_110:;
    return if_21;
}

struct StringIntIntObjectObjectTuple5 doubleLeft_2(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_10, struct StringIntIntObjectObjectTuple5 node_10) {
    struct StringIntIntObjectObjectTuple5 if_22;
    int call_147 = segNodeToLength_2(node_10);
    if ((call_147 >= 2)) goto else_111;
    if_22 = node_10;
    goto end_if_112;
else_111:;
    struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2 call_148 = segNodeToChildren_2(node_10);
    struct StringIntIntObjectObjectTuple5 right_4 = call_148.t1;
    struct StringIntIntObjectObjectTuple5 call_149 = rotateRight_2(itemTy_10, right_4);
    struct StringIntIntObjectObjectTuple5 call_150 = segNodeWithRight_2(itemTy_10, call_149, node_10);
    struct StringIntIntObjectObjectTuple5 call_151 = rotateLeft_2(itemTy_10, call_150);
    if_22 = call_151;
end_if_112:;
    return if_22;
}

struct IntIntIntObjectObjectTuple5 doubleRight_1(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_10, struct IntIntIntObjectObjectTuple5 node_11) {
    struct IntIntIntObjectObjectTuple5 if_23;
    int call_152 = segNodeToLength_1(node_11);
    if ((call_152 >= 2)) goto else_113;
    if_23 = node_11;
    goto end_if_114;
else_113:;
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 call_153 = segNodeToChildren_1(node_11);
    struct IntIntIntObjectObjectTuple5 left_4 = call_153.t0;
    struct IntIntIntObjectObjectTuple5 call_154 = rotateLeft_1(itemTy_10, left_4);
    struct IntIntIntObjectObjectTuple5 call_155 = segNodeWithLeft_1(itemTy_10, call_154, node_11);
    struct IntIntIntObjectObjectTuple5 call_156 = rotateRight_1(itemTy_10, call_155);
    if_23 = call_156;
end_if_114:;
    return if_23;
}

struct StringIntIntObjectObjectTuple5 doubleRight_2(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_10, struct StringIntIntObjectObjectTuple5 node_11) {
    struct StringIntIntObjectObjectTuple5 if_24;
    int call_157 = segNodeToLength_2(node_11);
    if ((call_157 >= 2)) goto else_115;
    if_24 = node_11;
    goto end_if_116;
else_115:;
    struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2 call_158 = segNodeToChildren_2(node_11);
    struct StringIntIntObjectObjectTuple5 left_4 = call_158.t0;
    struct StringIntIntObjectObjectTuple5 call_159 = rotateLeft_2(itemTy_10, left_4);
    struct StringIntIntObjectObjectTuple5 call_160 = segNodeWithLeft_2(itemTy_10, call_159, node_11);
    struct StringIntIntObjectObjectTuple5 call_161 = rotateRight_2(itemTy_10, call_160);
    if_24 = call_161;
end_if_116:;
    return if_24;
}

int toBalance_1(struct IntIntIntObjectObjectTuple5 node_12) {
    int if_25;
    int call_162 = segNodeToLength_1(node_12);
    if ((call_162 >= 2)) goto else_117;
    if_25 = 0;
    goto end_if_118;
else_117:;
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 call_163 = segNodeToChildren_1(node_12);
    struct IntIntIntObjectObjectTuple5 left_5 = call_163.t0;
    struct IntIntIntObjectObjectTuple5 right_5 = call_163.t1;
    int call_164 = segNodeToHeight_1(right_5);
    int call_165 = segNodeToHeight_1(left_5);
    if_25 = (call_164 - call_165);
end_if_118:;
    return if_25;
}

int toBalance_2(struct StringIntIntObjectObjectTuple5 node_12) {
    int if_26;
    int call_166 = segNodeToLength_2(node_12);
    if ((call_166 >= 2)) goto else_119;
    if_26 = 0;
    goto end_if_120;
else_119:;
    struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2 call_167 = segNodeToChildren_2(node_12);
    struct StringIntIntObjectObjectTuple5 left_5 = call_167.t0;
    struct StringIntIntObjectObjectTuple5 right_5 = call_167.t1;
    int call_168 = segNodeToHeight_2(right_5);
    int call_169 = segNodeToHeight_2(left_5);
    if_26 = (call_168 - call_169);
end_if_120:;
    return if_26;
}

struct IntIntIntObjectObjectTuple5 segNodeMakeBalanced_1(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_10, struct IntIntIntObjectObjectTuple5 node_7) {
    int call_170 = toBalance_1(node_7);
    int selfBalance_ = call_170;
    struct IntIntIntObjectObjectTuple5 if_27;
    int if_28;
    if ((selfBalance_ < (0 - 1))) goto else_123;
    if_28 = (1 >= selfBalance_);
    goto end_if_124;
else_123:;
    if_28 = 0;
end_if_124:;
    if ((!(if_28))) goto else_121;
    if_27 = node_7;
    goto end_if_122;
else_121:;
    struct IntIntIntObjectObjectTuple5 if_29;
    int call_171 = segNodeToLength_1(node_7);
    if ((call_171 >= 2)) goto else_125;
    if_29 = node_7;
    goto end_if_126;
else_125:;
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 call_172 = segNodeToChildren_1(node_7);
    struct IntIntIntObjectObjectTuple5 left_6 = call_172.t0;
    struct IntIntIntObjectObjectTuple5 right_6 = call_172.t1;
    struct IntIntIntObjectObjectTuple5 if_30;
    if ((selfBalance_ < 2)) goto else_127;
    struct IntIntIntObjectObjectTuple5 if_31;
    int call_173 = toBalance_1(right_6);
    if ((call_173 >= 0)) goto else_129;
    struct IntIntIntObjectObjectTuple5 call_174 = doubleLeft_1(itemTy_10, node_7);
    if_31 = call_174;
    goto end_if_130;
else_129:;
    struct IntIntIntObjectObjectTuple5 call_175 = rotateLeft_1(itemTy_10, node_7);
    if_31 = call_175;
end_if_130:;
    if_30 = if_31;
    goto end_if_128;
else_127:;
    struct IntIntIntObjectObjectTuple5 if_32;
    int call_176 = toBalance_1(left_6);
    if ((0 >= call_176)) goto else_131;
    struct IntIntIntObjectObjectTuple5 call_177 = doubleRight_1(itemTy_10, node_7);
    if_32 = call_177;
    goto end_if_132;
else_131:;
    struct IntIntIntObjectObjectTuple5 call_178 = rotateRight_1(itemTy_10, node_7);
    if_32 = call_178;
end_if_132:;
    if_30 = if_32;
end_if_128:;
    if_29 = if_30;
end_if_126:;
    if_27 = if_29;
end_if_122:;
    return if_27;
}

struct StringIntIntObjectObjectTuple5 segNodeMakeBalanced_2(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_10, struct StringIntIntObjectObjectTuple5 node_7) {
    int call_179 = toBalance_2(node_7);
    int selfBalance_ = call_179;
    struct StringIntIntObjectObjectTuple5 if_33;
    int if_34;
    if ((selfBalance_ < (0 - 1))) goto else_135;
    if_34 = (1 >= selfBalance_);
    goto end_if_136;
else_135:;
    if_34 = 0;
end_if_136:;
    if ((!(if_34))) goto else_133;
    if_33 = node_7;
    goto end_if_134;
else_133:;
    struct StringIntIntObjectObjectTuple5 if_35;
    int call_180 = segNodeToLength_2(node_7);
    if ((call_180 >= 2)) goto else_137;
    if_35 = node_7;
    goto end_if_138;
else_137:;
    struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2 call_181 = segNodeToChildren_2(node_7);
    struct StringIntIntObjectObjectTuple5 left_6 = call_181.t0;
    struct StringIntIntObjectObjectTuple5 right_6 = call_181.t1;
    struct StringIntIntObjectObjectTuple5 if_36;
    if ((selfBalance_ < 2)) goto else_139;
    struct StringIntIntObjectObjectTuple5 if_37;
    int call_182 = toBalance_2(right_6);
    if ((call_182 >= 0)) goto else_141;
    struct StringIntIntObjectObjectTuple5 call_183 = doubleLeft_2(itemTy_10, node_7);
    if_37 = call_183;
    goto end_if_142;
else_141:;
    struct StringIntIntObjectObjectTuple5 call_184 = rotateLeft_2(itemTy_10, node_7);
    if_37 = call_184;
end_if_142:;
    if_36 = if_37;
    goto end_if_140;
else_139:;
    struct StringIntIntObjectObjectTuple5 if_38;
    int call_185 = toBalance_2(left_6);
    if ((0 >= call_185)) goto else_143;
    struct StringIntIntObjectObjectTuple5 call_186 = doubleRight_2(itemTy_10, node_7);
    if_38 = call_186;
    goto end_if_144;
else_143:;
    struct StringIntIntObjectObjectTuple5 call_187 = rotateRight_2(itemTy_10, node_7);
    if_38 = call_187;
end_if_144:;
    if_36 = if_38;
end_if_140:;
    if_35 = if_36;
end_if_138:;
    if_33 = if_35;
end_if_134:;
    return if_33;
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
tailrec_145:;
    int item_4 = node_14.t0;
    int len_14 = node_14.t1;
    int if_39;
    int if_40;
    if ((index_6 >= 0)) goto else_148;
    if_40 = 1;
    goto end_if_149;
else_148:;
    if_40 = (index_6 >= len_14);
end_if_149:;
    if ((!(if_40))) goto else_146;
    printf("ERROR: segNodeGet out of range (index = %d, len = %d)\n", index_6, len_14);
    int call_196 = 0;
    exit(1);
    if_39 = 0;
    goto end_if_147;
else_146:;
    if_39 = 0;
end_if_147:;
    milone_assert((len_14 != 0), 264, 4);
    int call_197 = 0;
    int if_41;
    if ((len_14 != 1)) goto else_150;
    if_41 = item_4;
    goto end_if_151;
else_150:;
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 call_198 = segNodeToChildren_1(node_14);
    struct IntIntIntObjectObjectTuple5 left_7 = call_198.t0;
    struct IntIntIntObjectObjectTuple5 right_7 = call_198.t1;
    int call_199 = segNodeToLength_1(left_7);
    int leftLen_1 = call_199;
    int if_42;
    if ((index_6 >= leftLen_1)) goto else_152;
    int arg_82 = index_6;
    struct IntIntIntObjectObjectTuple5 arg_83 = left_7;
    index_6 = arg_82;
    node_14 = arg_83;
    goto tailrec_145;
    if_42 = 0;
    goto end_if_153;
else_152:;
    int arg_84 = (index_6 - leftLen_1);
    struct IntIntIntObjectObjectTuple5 arg_85 = right_7;
    index_6 = arg_84;
    node_14 = arg_85;
    goto tailrec_145;
    if_42 = 0;
end_if_153:;
    if_41 = if_42;
end_if_151:;
    return if_41;
}

struct String go_37(int index_6, struct StringIntIntObjectObjectTuple5 node_14) {
tailrec_154:;
    struct String item_4 = node_14.t0;
    int len_14 = node_14.t1;
    int if_43;
    int if_44;
    if ((index_6 >= 0)) goto else_157;
    if_44 = 1;
    goto end_if_158;
else_157:;
    if_44 = (index_6 >= len_14);
end_if_158:;
    if ((!(if_44))) goto else_155;
    printf("ERROR: segNodeGet out of range (index = %d, len = %d)\n", index_6, len_14);
    int call_200 = 0;
    exit(1);
    if_43 = 0;
    goto end_if_156;
else_155:;
    if_43 = 0;
end_if_156:;
    milone_assert((len_14 != 0), 264, 4);
    int call_201 = 0;
    struct String if_45;
    if ((len_14 != 1)) goto else_159;
    if_45 = item_4;
    goto end_if_160;
else_159:;
    struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2 call_202 = segNodeToChildren_2(node_14);
    struct StringIntIntObjectObjectTuple5 left_7 = call_202.t0;
    struct StringIntIntObjectObjectTuple5 right_7 = call_202.t1;
    int call_203 = segNodeToLength_2(left_7);
    int leftLen_1 = call_203;
    struct String if_46;
    if ((index_6 >= leftLen_1)) goto else_161;
    int arg_86 = index_6;
    struct StringIntIntObjectObjectTuple5 arg_87 = left_7;
    index_6 = arg_86;
    node_14 = arg_87;
    goto tailrec_154;
    if_46 = ((struct String){});
    goto end_if_162;
else_161:;
    int arg_88 = (index_6 - leftLen_1);
    struct StringIntIntObjectObjectTuple5 arg_89 = right_7;
    index_6 = arg_88;
    node_14 = arg_89;
    goto tailrec_154;
    if_46 = ((struct String){});
end_if_162:;
    if_45 = if_46;
end_if_160:;
    return if_45;
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
    int if_47;
    int call_208 = intervalIsDisjoint_(q_, e_);
    if ((!(call_208))) goto else_163;
    int call_209 = segItemTypeToEmptyItem_1(itemTy_12);
    if_47 = call_209;
    goto end_if_164;
else_163:;
    int if_48;
    int call_210 = intervalCovers_(q_, e_);
    if ((!(call_210))) goto else_165;
    int call_211 = segNodeToItem_1(node_15);
    if_48 = call_211;
    goto end_if_166;
else_165:;
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
    if_48 = app_10;
end_if_166:;
    if_47 = if_48;
end_if_164:;
    return if_47;
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
    int if_49;
    struct IntIntTuple2 tuple_28;
    tuple_28.t0 = 0;
    tuple_28.t1 = len_15;
    int call_220 = intervalIsDisjoint_(q_1, tuple_28);
    if ((!(call_220))) goto else_167;
    int call_221 = segItemTypeToEmptyItem_1(itemTy_12);
    if_49 = call_221;
    goto end_if_168;
else_167:;
    struct IntIntTuple2 tuple_29;
    tuple_29.t0 = 0;
    tuple_29.t1 = len_15;
    struct IntIntTuple2 e_1 = tuple_29;
    int call_222 = go_26(itemTy_12, e_1, q_1, root_);
    if_49 = call_222;
end_if_168:;
    return if_49;
}

struct IntIntIntObjectObjectTuple5 go_25(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_13, int newItem_, int index_8, struct IntIntIntObjectObjectTuple5 node_16) {
    int len_16 = node_16.t1;
    int height_2 = node_16.t2;
    void* children_1 = node_16.t3;
    int if_50;
    int if_51;
    if ((index_8 >= 0)) goto else_171;
    if_51 = 1;
    goto end_if_172;
else_171:;
    if_51 = (index_8 >= len_16);
end_if_172:;
    if ((!(if_51))) goto else_169;
    printf("ERROR: segNodeSet out of range (index = %d, len = %d)\n", index_8, len_16);
    int call_223 = 0;
    exit(1);
    if_50 = 0;
    goto end_if_170;
else_169:;
    if_50 = 0;
end_if_170:;
    milone_assert((len_16 != 0), 317, 4);
    int call_224 = 0;
    struct IntIntIntObjectObjectTuple5 if_52;
    if ((len_16 != 1)) goto else_173;
    struct IntIntIntObjectObjectTuple5 tuple_30;
    tuple_30.t0 = newItem_;
    tuple_30.t1 = len_16;
    tuple_30.t2 = height_2;
    tuple_30.t3 = children_1;
    tuple_30.t4 = 0;
    if_52 = tuple_30;
    goto end_if_174;
else_173:;
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 call_225 = segNodeToChildren_1(node_16);
    struct IntIntIntObjectObjectTuple5 left_8 = call_225.t0;
    struct IntIntIntObjectObjectTuple5 right_8 = call_225.t1;
    int call_226 = segNodeToLength_1(left_8);
    int leftLen_2 = call_226;
    struct IntIntIntObjectObjectTuple5 if_53;
    if ((index_8 >= leftLen_2)) goto else_175;
    struct IntIntIntObjectObjectTuple5 call_227 = go_25(itemTy_13, newItem_, index_8, left_8);
    struct IntIntIntObjectObjectTuple5 call_228 = segNodeWithLeft_1(itemTy_13, call_227, node_16);
    if_53 = call_228;
    goto end_if_176;
else_175:;
    struct IntIntIntObjectObjectTuple5 call_229 = go_25(itemTy_13, newItem_, (index_8 - leftLen_2), right_8);
    struct IntIntIntObjectObjectTuple5 call_230 = segNodeWithRight_1(itemTy_13, call_229, node_16);
    if_53 = call_230;
end_if_176:;
    if_52 = if_53;
end_if_174:;
    return if_52;
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
    struct IntIntIntObjectObjectTuple5 if_54;
    if ((len_17 != 0)) goto else_177;
    struct IntIntIntObjectObjectTuple5 call_233 = segNodeNewLeaf_1(itemTy_14, newItem_1);
    if_54 = call_233;
    goto end_if_178;
else_177:;
    struct IntIntIntObjectObjectTuple5 if_55;
    if ((len_17 != 1)) goto else_179;
    struct IntIntIntObjectObjectTuple5 call_234 = segNodeNewLeaf_1(itemTy_14, oldItem_);
    struct IntIntIntObjectObjectTuple5 oldLeaf_ = call_234;
    struct IntIntIntObjectObjectTuple5 call_235 = segNodeNewLeaf_1(itemTy_14, newItem_1);
    struct IntIntIntObjectObjectTuple5 newLeaf_ = call_235;
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 if_56;
    if ((index_10 != 0)) goto else_181;
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 tuple_32;
    tuple_32.t0 = newLeaf_;
    tuple_32.t1 = oldLeaf_;
    if_56 = tuple_32;
    goto end_if_182;
else_181:;
    milone_assert((index_10 == 1), 351, 10);
    int call_236 = 0;
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 tuple_33;
    tuple_33.t0 = oldLeaf_;
    tuple_33.t1 = newLeaf_;
    if_56 = tuple_33;
end_if_182:;
    struct IntIntIntObjectObjectTuple5 left_9 = if_56.t0;
    struct IntIntIntObjectObjectTuple5 right_9 = if_56.t1;
    struct IntIntIntObjectObjectTuple5 call_237 = segNodeNew_1(itemTy_14, left_9, right_9);
    if_55 = call_237;
    goto end_if_180;
else_179:;
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 call_238 = segNodeToChildren_1(node_17);
    struct IntIntIntObjectObjectTuple5 left_10 = call_238.t0;
    struct IntIntIntObjectObjectTuple5 right_10 = call_238.t1;
    int call_239 = segNodeToLength_1(left_10);
    int leftLen_3 = call_239;
    int call_240 = segNodeToLength_1(right_10);
    int rightLen_1 = call_240;
    milone_assert(((leftLen_3 + rightLen_1) == len_17), 360, 6);
    int call_241 = 0;
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 if_57;
    if ((index_10 >= leftLen_3)) goto else_183;
    struct IntIntIntObjectObjectTuple5 call_242 = go_24(itemTy_14, newItem_1, index_10, left_10);
    struct IntIntIntObjectObjectTuple5 left_12 = call_242;
    int call_243 = segNodeToLength_1(left_12);
    milone_assert((call_243 == (leftLen_3 + 1)), 365, 10);
    int call_244 = 0;
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 tuple_34;
    tuple_34.t0 = left_12;
    tuple_34.t1 = right_10;
    if_57 = tuple_34;
    goto end_if_184;
else_183:;
    struct IntIntIntObjectObjectTuple5 call_245 = go_24(itemTy_14, newItem_1, (index_10 - leftLen_3), right_10);
    struct IntIntIntObjectObjectTuple5 right_12 = call_245;
    int call_246 = segNodeToLength_1(right_12);
    milone_assert((call_246 == (rightLen_1 + 1)), 369, 10);
    int call_247 = 0;
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 tuple_35;
    tuple_35.t0 = left_10;
    tuple_35.t1 = right_12;
    if_57 = tuple_35;
end_if_184:;
    struct IntIntIntObjectObjectTuple5 left_11 = if_57.t0;
    struct IntIntIntObjectObjectTuple5 right_11 = if_57.t1;
    struct IntIntIntObjectObjectTuple5 call_248 = segNodeNew_1(itemTy_14, left_11, right_11);
    struct IntIntIntObjectObjectTuple5 call_249 = segNodeMakeBalanced_1(itemTy_14, call_248);
    if_55 = call_249;
end_if_180:;
    if_54 = if_55;
end_if_178:;
    return if_54;
}

struct StringIntIntObjectObjectTuple5 go_36(struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_14, struct String newItem_1, int index_10, struct StringIntIntObjectObjectTuple5 node_17) {
    struct String oldItem_ = node_17.t0;
    int len_17 = node_17.t1;
    milone_assert((len_17 >= index_10), 339, 4);
    int call_250 = 0;
    struct StringIntIntObjectObjectTuple5 if_58;
    if ((len_17 != 0)) goto else_185;
    struct StringIntIntObjectObjectTuple5 call_251 = segNodeNewLeaf_2(itemTy_14, newItem_1);
    if_58 = call_251;
    goto end_if_186;
else_185:;
    struct StringIntIntObjectObjectTuple5 if_59;
    if ((len_17 != 1)) goto else_187;
    struct StringIntIntObjectObjectTuple5 call_252 = segNodeNewLeaf_2(itemTy_14, oldItem_);
    struct StringIntIntObjectObjectTuple5 oldLeaf_ = call_252;
    struct StringIntIntObjectObjectTuple5 call_253 = segNodeNewLeaf_2(itemTy_14, newItem_1);
    struct StringIntIntObjectObjectTuple5 newLeaf_ = call_253;
    struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2 if_60;
    if ((index_10 != 0)) goto else_189;
    struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2 tuple_36;
    tuple_36.t0 = newLeaf_;
    tuple_36.t1 = oldLeaf_;
    if_60 = tuple_36;
    goto end_if_190;
else_189:;
    milone_assert((index_10 == 1), 351, 10);
    int call_254 = 0;
    struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2 tuple_37;
    tuple_37.t0 = oldLeaf_;
    tuple_37.t1 = newLeaf_;
    if_60 = tuple_37;
end_if_190:;
    struct StringIntIntObjectObjectTuple5 left_9 = if_60.t0;
    struct StringIntIntObjectObjectTuple5 right_9 = if_60.t1;
    struct StringIntIntObjectObjectTuple5 call_255 = segNodeNew_2(itemTy_14, left_9, right_9);
    if_59 = call_255;
    goto end_if_188;
else_187:;
    struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2 call_256 = segNodeToChildren_2(node_17);
    struct StringIntIntObjectObjectTuple5 left_10 = call_256.t0;
    struct StringIntIntObjectObjectTuple5 right_10 = call_256.t1;
    int call_257 = segNodeToLength_2(left_10);
    int leftLen_3 = call_257;
    int call_258 = segNodeToLength_2(right_10);
    int rightLen_1 = call_258;
    milone_assert(((leftLen_3 + rightLen_1) == len_17), 360, 6);
    int call_259 = 0;
    struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2 if_61;
    if ((index_10 >= leftLen_3)) goto else_191;
    struct StringIntIntObjectObjectTuple5 call_260 = go_36(itemTy_14, newItem_1, index_10, left_10);
    struct StringIntIntObjectObjectTuple5 left_12 = call_260;
    int call_261 = segNodeToLength_2(left_12);
    milone_assert((call_261 == (leftLen_3 + 1)), 365, 10);
    int call_262 = 0;
    struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2 tuple_38;
    tuple_38.t0 = left_12;
    tuple_38.t1 = right_10;
    if_61 = tuple_38;
    goto end_if_192;
else_191:;
    struct StringIntIntObjectObjectTuple5 call_263 = go_36(itemTy_14, newItem_1, (index_10 - leftLen_3), right_10);
    struct StringIntIntObjectObjectTuple5 right_12 = call_263;
    int call_264 = segNodeToLength_2(right_12);
    milone_assert((call_264 == (rightLen_1 + 1)), 369, 10);
    int call_265 = 0;
    struct StringIntIntObjectObjectTuple5StringIntIntObjectObjectTuple5Tuple2 tuple_39;
    tuple_39.t0 = left_10;
    tuple_39.t1 = right_12;
    if_61 = tuple_39;
end_if_192:;
    struct StringIntIntObjectObjectTuple5 left_11 = if_61.t0;
    struct StringIntIntObjectObjectTuple5 right_11 = if_61.t1;
    struct StringIntIntObjectObjectTuple5 call_266 = segNodeNew_2(itemTy_14, left_11, right_11);
    struct StringIntIntObjectObjectTuple5 call_267 = segNodeMakeBalanced_2(itemTy_14, call_266);
    if_59 = call_267;
end_if_188:;
    if_58 = if_59;
end_if_186:;
    return if_58;
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
    struct IntIntIntObjectObjectTuple5 if_62;
    if ((len_18 != 1)) goto else_193;
    struct IntIntIntObjectObjectTuple5 call_272 = segItemTypeToEmptyNode_2(itemTy_15);
    if_62 = call_272;
    goto end_if_194;
else_193:;
    struct IntIntIntObjectObjectTuple5IntIntIntObjectObjectTuple5Tuple2 call_273 = segNodeToChildren_1(node_18);
    struct IntIntIntObjectObjectTuple5 left_13 = call_273.t0;
    struct IntIntIntObjectObjectTuple5 right_13 = call_273.t1;
    int call_274 = segNodeToLength_1(left_13);
    int leftLen_4 = call_274;
    int call_275 = segNodeToLength_1(right_13);
    int rightLen_2 = call_275;
    milone_assert(((leftLen_4 + rightLen_2) == len_18), 394, 6);
    int call_276 = 0;
    struct IntIntIntObjectObjectTuple5 if_63;
    if ((index_12 >= leftLen_4)) goto else_195;
    struct IntIntIntObjectObjectTuple5 if_64;
    if ((leftLen_4 >= 2)) goto else_197;
    if_64 = right_13;
    goto end_if_198;
else_197:;
    struct IntIntIntObjectObjectTuple5 call_277 = go_35(itemTy_15, index_12, left_13);
    struct IntIntIntObjectObjectTuple5 call_278 = segNodeWithLeft_1(itemTy_15, call_277, node_18);
    if_64 = call_278;
end_if_198:;
    if_63 = if_64;
    goto end_if_196;
else_195:;
    struct IntIntIntObjectObjectTuple5 if_65;
    if ((rightLen_2 >= 2)) goto else_199;
    if_65 = left_13;
    goto end_if_200;
else_199:;
    struct IntIntIntObjectObjectTuple5 call_279 = go_35(itemTy_15, (index_12 - leftLen_4), right_13);
    struct IntIntIntObjectObjectTuple5 call_280 = segNodeWithRight_1(itemTy_15, call_279, node_18);
    if_65 = call_280;
end_if_200:;
    if_63 = if_65;
end_if_196:;
    struct IntIntIntObjectObjectTuple5 node_19 = if_63;
    struct IntIntIntObjectObjectTuple5 call_281 = segNodeMakeBalanced_1(itemTy_15, node_19);
    if_62 = call_281;
end_if_194:;
    return if_62;
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
tailrec_201:;
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 match_16;
    if ((!((!(xs_22))))) goto next_203;
    match_16 = t_2;
    goto end_match_202;
next_203:;
    if ((!(xs_22))) goto next_204;
    int x_6 = xs_22->head;
    struct IntList* xs_23 = xs_22->tail;
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 call_289 = segTreePush_1(x_6, t_2);
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 arg_90 = call_289;
    struct IntList* arg_91 = xs_23;
    t_2 = arg_90;
    xs_22 = arg_91;
    goto tailrec_201;
    match_16 = ((struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3){});
    goto end_match_202;
next_204:;
    exit(1);
end_match_202:;
    return match_16;
}

struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 segTreeOfList_1(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4 itemTy_16, struct IntList* xs_21) {
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 call_290 = segTreeNew_2(itemTy_16);
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 call_291 = go_23(call_290, xs_21);
    return call_291;
}

struct IntList* go_22(int len_19, struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 v_4, struct IntList* acc_3, int i_4) {
tailrec_205:;
    struct IntList* if_66;
    if ((i_4 != len_19)) goto else_206;
    struct IntList* call_292 = listRev_2(acc_3);
    if_66 = call_292;
    goto end_if_207;
else_206:;
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
    goto tailrec_205;
    if_66 = NULL;
end_if_207:;
    return if_66;
}

struct StringList* go_21(int len_19, struct StringStringStringFun2StringIntIntObjectObjectTuple5ObjectObjectTuple4StringIntIntObjectObjectTuple5ObjectTuple3 v_4, struct StringList* acc_3, int i_4) {
tailrec_208:;
    struct StringList* if_67;
    if ((i_4 != len_19)) goto else_209;
    struct StringList* call_294 = listRev_1(acc_3);
    if_67 = call_294;
    goto end_if_210;
else_209:;
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
    goto tailrec_208;
    if_67 = NULL;
end_if_210:;
    return if_67;
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
tailrec_211:;
    int if_68;
    if ((i_5 != r_1)) goto else_212;
    if_68 = acc_4;
    goto end_if_213;
else_212:;
    int match_17;
    if ((!(xs_25))) goto next_215;
    int x_10 = xs_25->head;
    struct IntList* xs_26 = xs_25->tail;
    int if_69;
    if ((i_5 >= l_1)) goto else_217;
    if_69 = acc_4;
    goto end_if_218;
else_217:;
    if_69 = (acc_4 + x_10);
end_if_218:;
    int acc_5 = if_69;
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
    goto tailrec_211;
    match_17 = 0;
    goto end_match_214;
next_215:;
    int call_346 = failwith_1((struct String){.str = "NEVER", .len = 5});
    match_17 = call_346;
    goto end_match_214;
next_216:;
end_match_214:;
    if_68 = match_17;
end_if_213:;
    return if_68;
}

int go_15(int n_1, struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 v_13, struct IntList* xs_24, int l_1, int r_1) {
tailrec_219:;
    int if_70;
    if ((r_1 != n_1)) goto else_220;
    int if_71;
    if ((l_1 >= n_1)) goto else_222;
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
    goto tailrec_219;
    if_71 = 0;
    goto end_if_223;
else_222:;
    if_71 = 0;
end_if_223:;
    if_70 = 0;
    goto end_if_221;
else_220:;
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
    goto tailrec_219;
    if_70 = 0;
end_if_221:;
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
tailrec_224:;
    int if_72;
    if ((i_6 != n_4)) goto else_225;
    if_72 = sum_1;
    goto end_if_226;
else_225:;
    int call_380 = segTreeGet_1(i_6, a_1);
    int ai_ = call_380;
    int call_381 = segTreeGet_1((ai_ - 1), b_1);
    int eat_ = call_381;
    int if_73;
    int if_74;
    if (((i_6 + 1) >= n_4)) goto else_229;
    int call_382 = segTreeGet_1((i_6 + 1), a_1);
    if_74 = (call_382 == (ai_ + 1));
    goto end_if_230;
else_229:;
    if_74 = 0;
end_if_230:;
    if ((!(if_74))) goto else_227;
    int call_383 = segTreeGet_1((ai_ - 1), c_1);
    if_73 = call_383;
    goto end_if_228;
else_227:;
    if_73 = 0;
end_if_228:;
    int bonus_ = if_73;
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
    goto tailrec_224;
    if_72 = 0;
end_if_226:;
    return if_72;
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
tailrec_231:;
    struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 if_75;
    if ((i_7 != (n_7 + 2))) goto else_232;
    if_75 = pos_1;
    goto end_if_233;
else_232:;
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
    goto tailrec_231;
    if_75 = ((struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3){});
end_if_233:;
    return if_75;
}

int go_19(struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 pos_, int n_7, int sum_2, struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 prev_1, struct IntIntIntFun2IntIntIntObjectObjectTuple5ObjectObjectTuple4IntIntIntObjectObjectTuple5ObjectTuple3 next_1, int p_) {
tailrec_234:;
    int if_76;
    if ((p_ >= 1)) goto else_235;
    if_76 = sum_2;
    goto end_if_236;
else_235:;
    int call_415 = segTreeGet_1(p_, pos_);
    int i_8 = call_415;
    int call_416 = segTreeSum_1(0, i_8, prev_1);
    int x_11 = call_416;
    int call_417 = segTreeSum_1(0, x_11, prev_1);
    int w_ = call_417;
    int if_77;
    if ((x_11 < w_)) goto else_237;
    if_77 = (x_11 < i_8);
    goto end_if_238;
else_237:;
    if_77 = 0;
end_if_238:;
    milone_assert(if_77, 58, 6);
    int call_418 = 0;
    int call_419 = segTreeSum_1((i_8 + 1), (n_7 + 2), next_1);
    int y_5 = call_419;
    int call_420 = segTreeSum_1((y_5 + 1), (n_7 + 2), next_1);
    int z_ = call_420;
    int if_78;
    if ((i_8 >= y_5)) goto else_239;
    if_78 = (z_ >= y_5);
    goto end_if_240;
else_239:;
    if_78 = 0;
end_if_240:;
    milone_assert(if_78, 62, 6);
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
    goto tailrec_234;
    if_76 = 0;
end_if_236:;
    return if_76;
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
    int if_79;
    if ((actual_1 != expected_1)) goto else_241;
    if_79 = 1;
    goto end_if_242;
else_241:;
    printf("actual=%d expected=%d\n", actual_1, expected_1);
    int call_442 = 0;
    if_79 = 0;
end_if_242:;
    return if_79;
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
