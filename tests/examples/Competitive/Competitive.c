#include "milone.h"

struct StringList;

struct StringStringStringFun2List;

struct IntList;

struct IntIntIntFun2List;

struct IntIntIntObjectUnitTuple5List;

struct StringIntIntObjectUnitTuple5List;

struct StringList;

struct IntList;

struct IntIntBoolFun2;

struct IntListIntListTuple2;

struct StringStringBoolFun2;

struct StringListStringListTuple2;

struct IntIntFun1;

struct StringStringListTuple2;

struct IntVoidMutPtrFun1;

struct VoidMutPtrIntIntFun2;

struct VoidMutPtrIntIntUnitFun3;

struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6;

struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5;

struct IntIntTuple2;

struct StringStringStringFun2;

struct StringIntIntObjectUnitTuple5;

struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4;

struct IntIntIntFun2;

struct IntIntIntObjectUnitTuple5;

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4;

struct StringIntIntObjectUnitTuple5StringIntIntObjectUnitTuple5Tuple2;

struct StringStringStringFun2List;

struct IntIntIntObjectUnitTuple5IntIntIntObjectUnitTuple5Tuple2;

struct IntIntIntFun2List;

struct IntIntIntObjectUnitTuple5List;

struct StringIntIntObjectUnitTuple5List;

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3;

struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4StringIntIntObjectUnitTuple5UnitTuple3;

void* milone_mem_alloc(int, uintptr_t);

void* memAlloc_(int len_, int size_);

void* memcpy(void*, void const*, uintptr_t);

void* memCopy_(void* dest_, void const* src_, int size_1);

int scan_int();

int scanInt_(char arg_35);

void* rawIntArrayNew_(int len_1);

int rawIntArrayGet_(void* array_, int index_);

char rawIntArraySet_(void* array_1, int index_1, int value_);

char rawMemoryCopy_(void* dest_1, void* src_1, int size_2);

bool listIsEmpty_1(struct StringList const* xs_);

bool listIsEmpty_4(struct StringStringStringFun2List const* xs_);

bool listIsEmpty_3(struct IntList const* xs_);

bool listIsEmpty_2(struct IntIntIntFun2List const* xs_);

bool listIsEmpty_5(struct IntIntIntObjectUnitTuple5List const* xs_);

bool listIsEmpty_6(struct StringIntIntObjectUnitTuple5List const* xs_);

int go_22(int len_2, struct StringList const* xs_2);

int go_21(int len_2, struct IntList const* xs_2);

int listLength_2(struct StringList const* xs_1);

int listLength_1(struct IntList const* xs_1);

struct IntList const* go_38(struct IntList const* acc_, struct IntList const* xs_5);

struct StringList const* go_37(struct StringList const* acc_, struct StringList const* xs_5);

struct IntList const* listRev_2(struct IntList const* xs_4);

struct StringList const* listRev_1(struct StringList const* xs_4);

bool go_24(struct IntIntBoolFun2 itemEqual_, struct IntList const* xs_8, struct IntList const* ys_1);

bool go_23(struct StringStringBoolFun2 itemEqual_, struct StringList const* xs_8, struct StringList const* ys_1);

bool listEqual_2(struct IntIntBoolFun2 itemEqual_, struct IntList const* xs_7, struct IntList const* ys_);

bool listEqual_1(struct StringStringBoolFun2 itemEqual_, struct StringList const* xs_7, struct StringList const* ys_);

struct IntList const* go_25(int item_, int len_3, struct IntList const* acc_1, int i_);

struct IntList const* listReplicate_1(int item_, int len_3);

struct IntList const* go_26(int len_4, struct IntIntFun1 gen_, struct IntList const* acc_2, int i_1);

struct IntList const* listInit_1(int len_4, struct IntIntFun1 gen_);

struct StringStringListTuple2 go_5(struct StringList const* xs_11, int xn_);

struct String strConcat_(struct StringList const* xs_10);

bool intEqual_(int first_, int second_);

int intMin_(int first_1, int second_1);

int intMax_(int first_2, int second_2);

bool strEqual_(struct String first_3, struct String second_3);

int failwith_1(struct String msg_);

int fun_21(int arg_58);

int fun_3(void const* env_, int arg_);

struct IntList const* scanIntList_(int len_5);

struct IntVoidMutPtrFun1 typeToArrayNew_1(struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6 arg_59);

struct VoidMutPtrIntIntFun2 typeToArrayGet_1(struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6 arg_60);

struct VoidMutPtrIntIntUnitFun3 typeToArraySet_1(struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6 arg_61);

void* fun_4(void const* env_1, int arg_1);

int fun_5(void const* env_2, void* arg_2, int arg_3);

char fun_6(void const* env_3, void* arg_4, int arg_5, int arg_6);

int vectorToLength_1(struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 arg_62);

struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 vectorNew_1(struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6 itemTy_, int len_7);

char vectorCheckIndex_1(int index_2, struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 self_);

int vectorGet_1(int index_3, struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 self_1);

char vectorSet_1(int index_4, int value_1, struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 self_2);

char go_27(int len_10, struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 v_, int i_2, struct IntList const* xs_19);

struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 vectorOfList_1(struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6 ty_, struct IntList const* xs_18);

char go_7(int len_11, struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 v_1, int i_3);

struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 scanIntVector_(int len_11);

char refCase_(char arg_70);

char vectorOfListTest_(char arg_71);

char vectorTest_(char arg_72);

bool intervalIsDisjoint_(struct IntIntTuple2 first_4, struct IntIntTuple2 second_4);

bool intervalCovers_(struct IntIntTuple2 first_5, struct IntIntTuple2 second_5);

struct StringStringStringFun2 segItemTypeToAppend_2(struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4 arg_73);

struct IntIntIntFun2 segItemTypeToAppend_1(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 arg_74);

struct IntIntIntObjectUnitTuple5 segItemTypeToEmptyNode_2(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 arg_75);

struct StringIntIntObjectUnitTuple5 segItemTypeToEmptyNode_1(struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4 arg_76);

void const* segItemTypeToNoChildren_1(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 arg_77);

void const* segItemTypeToNoChildren_2(struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4 arg_78);

int segItemTypeToEmptyItem_1(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_4);

struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4 segItemTypeNew_2(struct String emptyItem_, struct StringStringStringFun2 append_1);

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 segItemTypeNew_1(int emptyItem_, struct IntIntIntFun2 append_1);

struct StringIntIntObjectUnitTuple5 segNodeNewEmpty_2(struct String emptyItem_1);

struct IntIntIntObjectUnitTuple5 segNodeNewEmpty_1(int emptyItem_1);

struct IntIntIntObjectUnitTuple5 segNodeNewLeaf_1(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_6, int item_1);

struct StringIntIntObjectUnitTuple5 segNodeNewLeaf_2(struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_6, struct String item_1);

struct IntIntIntObjectUnitTuple5 doNew_1(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_7, struct IntIntIntObjectUnitTuple5 left_, struct IntIntIntObjectUnitTuple5 right_, char arg_79);

struct StringIntIntObjectUnitTuple5 doNew_2(struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_7, struct StringIntIntObjectUnitTuple5 left_, struct StringIntIntObjectUnitTuple5 right_, char arg_80);

struct IntIntIntObjectUnitTuple5 segNodeNew_1(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_7, struct IntIntIntObjectUnitTuple5 left_, struct IntIntIntObjectUnitTuple5 right_);

struct StringIntIntObjectUnitTuple5 segNodeNew_2(struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_7, struct StringIntIntObjectUnitTuple5 left_, struct StringIntIntObjectUnitTuple5 right_);

int segNodeToItem_1(struct IntIntIntObjectUnitTuple5 node_);

int segNodeToLength_1(struct IntIntIntObjectUnitTuple5 node_1);

int segNodeToLength_2(struct StringIntIntObjectUnitTuple5 node_1);

int segNodeToHeight_1(struct IntIntIntObjectUnitTuple5 node_2);

int segNodeToHeight_2(struct StringIntIntObjectUnitTuple5 node_2);

struct IntIntIntObjectUnitTuple5IntIntIntObjectUnitTuple5Tuple2 segNodeToChildren_1(struct IntIntIntObjectUnitTuple5 node_3);

struct StringIntIntObjectUnitTuple5StringIntIntObjectUnitTuple5Tuple2 segNodeToChildren_2(struct StringIntIntObjectUnitTuple5 node_3);

bool segNodeIsEmpty_1(struct IntIntIntObjectUnitTuple5 node_4);

struct IntIntIntObjectUnitTuple5 segNodeWithLeft_1(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_8, struct IntIntIntObjectUnitTuple5 newLeft_, struct IntIntIntObjectUnitTuple5 node_5);

struct StringIntIntObjectUnitTuple5 segNodeWithLeft_2(struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_8, struct StringIntIntObjectUnitTuple5 newLeft_, struct StringIntIntObjectUnitTuple5 node_5);

struct IntIntIntObjectUnitTuple5 segNodeWithRight_1(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_9, struct IntIntIntObjectUnitTuple5 newRight_, struct IntIntIntObjectUnitTuple5 node_6);

struct StringIntIntObjectUnitTuple5 segNodeWithRight_2(struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_9, struct StringIntIntObjectUnitTuple5 newRight_, struct StringIntIntObjectUnitTuple5 node_6);

struct IntIntIntObjectUnitTuple5 rotateLeft_1(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_10, struct IntIntIntObjectUnitTuple5 node_8);

struct StringIntIntObjectUnitTuple5 rotateLeft_2(struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_10, struct StringIntIntObjectUnitTuple5 node_8);

struct IntIntIntObjectUnitTuple5 rotateRight_1(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_10, struct IntIntIntObjectUnitTuple5 node_9);

struct StringIntIntObjectUnitTuple5 rotateRight_2(struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_10, struct StringIntIntObjectUnitTuple5 node_9);

struct IntIntIntObjectUnitTuple5 doubleLeft_1(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_10, struct IntIntIntObjectUnitTuple5 node_10);

struct StringIntIntObjectUnitTuple5 doubleLeft_2(struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_10, struct StringIntIntObjectUnitTuple5 node_10);

struct IntIntIntObjectUnitTuple5 doubleRight_1(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_10, struct IntIntIntObjectUnitTuple5 node_11);

struct StringIntIntObjectUnitTuple5 doubleRight_2(struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_10, struct StringIntIntObjectUnitTuple5 node_11);

int toBalance_1(struct IntIntIntObjectUnitTuple5 node_12);

int toBalance_2(struct StringIntIntObjectUnitTuple5 node_12);

struct IntIntIntObjectUnitTuple5 segNodeMakeBalanced_1(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_10, struct IntIntIntObjectUnitTuple5 node_7);

struct StringIntIntObjectUnitTuple5 segNodeMakeBalanced_2(struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_10, struct StringIntIntObjectUnitTuple5 node_7);

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 segTreeNew_2(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_11);

struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4StringIntIntObjectUnitTuple5UnitTuple3 segTreeNew_1(struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_11);

struct IntIntIntObjectUnitTuple5 segTreeToRoot_1(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 self_4);

struct StringIntIntObjectUnitTuple5 segTreeToRoot_2(struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4StringIntIntObjectUnitTuple5UnitTuple3 self_4);

int segTreeToLength_1(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 self_5);

int segTreeToLength_2(struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4StringIntIntObjectUnitTuple5UnitTuple3 self_5);

int segTreeToHeight_1(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 self_6);

int go_28(int index_6, struct IntIntIntObjectUnitTuple5 node_14);

struct String go_39(int index_6, struct StringIntIntObjectUnitTuple5 node_14);

int segTreeGet_1(int index_5, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 self_8);

struct String segTreeGet_2(int index_5, struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4StringIntIntObjectUnitTuple5UnitTuple3 self_8);

int go_29(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_12, struct IntIntTuple2 e_, struct IntIntTuple2 q_, struct IntIntIntObjectUnitTuple5 node_15);

int segTreeSum_1(int ql_, int qr_, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 self_9);

struct IntIntIntObjectUnitTuple5 go_30(int newItem_, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_13, int index_8, struct IntIntIntObjectUnitTuple5 node_16);

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 segTreeSet_1(int index_7, int newItem_, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 self_10);

struct IntIntIntObjectUnitTuple5 go_31(int newItem_1, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_14, int index_10, struct IntIntIntObjectUnitTuple5 node_17);

struct StringIntIntObjectUnitTuple5 go_35(struct String newItem_1, struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_14, int index_10, struct StringIntIntObjectUnitTuple5 node_17);

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 segTreeInsert_1(int index_9, int newItem_1, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 self_11);

struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4StringIntIntObjectUnitTuple5UnitTuple3 segTreeInsert_2(int index_9, struct String newItem_1, struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4StringIntIntObjectUnitTuple5UnitTuple3 self_11);

struct IntIntIntObjectUnitTuple5 go_36(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_15, int index_12, struct IntIntIntObjectUnitTuple5 node_18);

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 segTreeRemove_1(int index_11, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 self_12);

struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4StringIntIntObjectUnitTuple5UnitTuple3 segTreePush_2(struct String value_4, struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4StringIntIntObjectUnitTuple5UnitTuple3 self_13);

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 segTreePush_1(int value_4, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 self_13);

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 segTreePop_1(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 self_14);

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 go_32(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 t_2, struct IntList const* xs_22);

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 segTreeOfList_1(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_16, struct IntList const* xs_21);

struct IntList const* go_34(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 v_4, int len_20, struct IntList const* acc_3, int i_4);

struct StringList const* go_33(struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4StringIntIntObjectUnitTuple5UnitTuple3 v_4, int len_20, struct StringList const* acc_3, int i_4);

struct IntList const* segTreeToList_2(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 v_4);

struct StringList const* segTreeToList_1(struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4StringIntIntObjectUnitTuple5UnitTuple3 v_4);

int intAdd_(int x_8, int y_3);

int fun_7(void const* env_4, int arg_7, int arg_8);

struct String strAdd_(struct String x_9, struct String y_4);

struct String fun_8(void const* env_5, struct String arg_9, struct String arg_10);

bool fun_9(void const* env_6, int arg_11, int arg_12);

bool fun_10(void const* env_7, int arg_13, int arg_14);

bool fun_11(void const* env_8, int arg_15, int arg_16);

bool fun_12(void const* env_9, int arg_17, int arg_18);

bool fun_13(void const* env_10, int arg_19, int arg_20);

char testPushPop_(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 segItemTypeInt_, char arg_99);

bool fun_14(void const* env_11, int arg_21, int arg_22);

bool fun_15(void const* env_12, int arg_23, int arg_24);

char testSet_(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 segItemTypeInt_, char arg_100);

char testSum_(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 segItemTypeInt_, char arg_101);

int sum_(int l_1, int r_1, int acc_4, int i_5, struct IntList const* xs_25);

char go_15(struct IntList const* xs_24, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 v_13, int n_1, int l_1, int r_1);

char testSumMore_(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 segItemTypeInt_, char arg_117);

char testBalance_(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 segItemTypeInt_, char arg_118);

bool fun_16(void const* env_13, struct String arg_25, struct String arg_26);

char testPolymorphic_(struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4 segItemTypeStr_, char arg_119);

char segTreeTest_(char arg_120);

int fun_22(int arg_121, int arg_122);

int fun_17(void const* env_14, int arg_27, int arg_28);

int fun_18(void const* env_15, int arg_29, int arg_30);

int fun_19(void const* env_16, int arg_31, int arg_32);

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 go_19(int n_2, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 perm_2, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 pos_1, int i_6);

int go_20(int n_2, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 pos_, int sum_1, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 prev_1, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 next_1, int p_);

int abc140eSolve_(int n_2, struct IntList const* perm_);

bool solve_(struct IntList const* p_1, int expected_1);

char abc140eTest_(char arg_133);

char abc140eMain_(char arg_134);

int fun_23(int arg_135, int arg_136);

int fun_20(void const* env_17, int arg_33, int arg_34);

int go_18(int n_5, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 a_1, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 b_1, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 c_1, int sum_3, int i_8);

int abc140bSolve_(int n_5, struct IntList const* a_, struct IntList const* b_, struct IntList const* c_);

int f_(struct IntList const* a_2, struct IntList const* b_2, struct IntList const* c_2);

bool case1_(char arg_143);

bool case2_(char arg_144);

bool case3_(char arg_145);

char abc140bTest_(char arg_146);

char abc140bMain_(char arg_147);

int abc140aSolve_(int n_8);

char abc140aTest_(char arg_148);

char abc140aMain_(char arg_149);

int milone_main();

struct StringList {
    struct String head;
    struct StringList const* tail;
};

struct IntList {
    int head;
    struct IntList const* tail;
};

struct IntIntBoolFun2 {
    bool(*fun)(void const*, int, int);
    void const* env;
};

struct IntListIntListTuple2 {
    struct IntList const* t0;
    struct IntList const* t1;
};

struct StringStringBoolFun2 {
    bool(*fun)(void const*, struct String, struct String);
    void const* env;
};

struct StringListStringListTuple2 {
    struct StringList const* t0;
    struct StringList const* t1;
};

struct IntIntFun1 {
    int(*fun)(void const*, int);
    void const* env;
};

struct StringStringListTuple2 {
    struct String t0;
    struct StringList const* t1;
};

struct IntVoidMutPtrFun1 {
    void*(*fun)(void const*, int);
    void const* env;
};

struct VoidMutPtrIntIntFun2 {
    int(*fun)(void const*, void*, int);
    void const* env;
};

struct VoidMutPtrIntIntUnitFun3 {
    char(*fun)(void const*, void*, int, int);
    void const* env;
};

struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6 {
    int t0;
    int t1;
    struct IntVoidMutPtrFun1 t2;
    struct VoidMutPtrIntIntFun2 t3;
    struct VoidMutPtrIntIntUnitFun3 t4;
    char t5;
};

struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 {
    struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6 t0;
    void* t1;
    int t2;
    int t3;
    char t4;
};

struct IntIntTuple2 {
    int t0;
    int t1;
};

struct StringStringStringFun2 {
    struct String(*fun)(void const*, struct String, struct String);
    void const* env;
};

struct StringIntIntObjectUnitTuple5 {
    struct String t0;
    int t1;
    int t2;
    void const* t3;
    char t4;
};

struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4 {
    struct StringStringStringFun2 t0;
    struct StringIntIntObjectUnitTuple5 t1;
    void const* t2;
    char t3;
};

struct IntIntIntFun2 {
    int(*fun)(void const*, int, int);
    void const* env;
};

struct IntIntIntObjectUnitTuple5 {
    int t0;
    int t1;
    int t2;
    void const* t3;
    char t4;
};

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 {
    struct IntIntIntFun2 t0;
    struct IntIntIntObjectUnitTuple5 t1;
    void const* t2;
    char t3;
};

struct StringIntIntObjectUnitTuple5StringIntIntObjectUnitTuple5Tuple2 {
    struct StringIntIntObjectUnitTuple5 t0;
    struct StringIntIntObjectUnitTuple5 t1;
};

struct StringStringStringFun2List {
    struct StringStringStringFun2 head;
    struct StringStringStringFun2List const* tail;
};

struct IntIntIntObjectUnitTuple5IntIntIntObjectUnitTuple5Tuple2 {
    struct IntIntIntObjectUnitTuple5 t0;
    struct IntIntIntObjectUnitTuple5 t1;
};

struct IntIntIntFun2List {
    struct IntIntIntFun2 head;
    struct IntIntIntFun2List const* tail;
};

struct IntIntIntObjectUnitTuple5List {
    struct IntIntIntObjectUnitTuple5 head;
    struct IntIntIntObjectUnitTuple5List const* tail;
};

struct StringIntIntObjectUnitTuple5List {
    struct StringIntIntObjectUnitTuple5 head;
    struct StringIntIntObjectUnitTuple5List const* tail;
};

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 {
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 t0;
    struct IntIntIntObjectUnitTuple5 t1;
    char t2;
};

struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4StringIntIntObjectUnitTuple5UnitTuple3 {
    struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4 t0;
    struct StringIntIntObjectUnitTuple5 t1;
    char t2;
};

static void const* unitObj_;

static struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6 typeInt_;

void* memAlloc_(int len_, int size_) {
    void* milone_mem_alloc_result_ = milone_mem_alloc(len_, ((uintptr_t)size_));
    return milone_mem_alloc_result_;
}

void* memCopy_(void* dest_, void const* src_, int size_1) {
    void* memcpy_result_ = memcpy(dest_, src_, ((uintptr_t)size_1));
    return memcpy_result_;
}

int scanInt_(char arg_35) {
    int scan_int_result_ = scan_int();
    return scan_int_result_;
}

void* rawIntArrayNew_(int len_1) {
    void* call_ = memAlloc_(len_1, sizeof(int));
    return ((void*)call_);
}

int rawIntArrayGet_(void* array_, int index_) {
    int read_ = ((int const*)array_)[index_];
    return read_;
}

char rawIntArraySet_(void* array_1, int index_1, int value_) {
    ((int*)array_1)[index_1] = value_;
    return 0;
}

char rawMemoryCopy_(void* dest_1, void* src_1, int size_2) {
    void* call_1 = memCopy_(dest_1, ((void const*)src_1), (size_2 * sizeof(int)));
    return 0;
}

bool listIsEmpty_1(struct StringList const* xs_) {
    bool if_;
    if ((!(xs_))) {
        goto nil_cl_2;
    } else {
        goto cons_cl_3;
    }
nil_cl_2:;
    if_ = true;
    goto if_next_1;
cons_cl_3:;
    if_ = false;
    goto if_next_1;
if_next_1:;
    return if_;
}

bool listIsEmpty_4(struct StringStringStringFun2List const* xs_) {
    bool if_1;
    if ((!(xs_))) {
        goto nil_cl_5;
    } else {
        goto cons_cl_6;
    }
nil_cl_5:;
    if_1 = true;
    goto if_next_4;
cons_cl_6:;
    if_1 = false;
    goto if_next_4;
if_next_4:;
    return if_1;
}

bool listIsEmpty_3(struct IntList const* xs_) {
    bool if_2;
    if ((!(xs_))) {
        goto nil_cl_8;
    } else {
        goto cons_cl_9;
    }
nil_cl_8:;
    if_2 = true;
    goto if_next_7;
cons_cl_9:;
    if_2 = false;
    goto if_next_7;
if_next_7:;
    return if_2;
}

bool listIsEmpty_2(struct IntIntIntFun2List const* xs_) {
    bool if_3;
    if ((!(xs_))) {
        goto nil_cl_11;
    } else {
        goto cons_cl_12;
    }
nil_cl_11:;
    if_3 = true;
    goto if_next_10;
cons_cl_12:;
    if_3 = false;
    goto if_next_10;
if_next_10:;
    return if_3;
}

bool listIsEmpty_5(struct IntIntIntObjectUnitTuple5List const* xs_) {
    bool if_4;
    if ((!(xs_))) {
        goto nil_cl_14;
    } else {
        goto cons_cl_15;
    }
nil_cl_14:;
    if_4 = true;
    goto if_next_13;
cons_cl_15:;
    if_4 = false;
    goto if_next_13;
if_next_13:;
    return if_4;
}

bool listIsEmpty_6(struct StringIntIntObjectUnitTuple5List const* xs_) {
    bool if_5;
    if ((!(xs_))) {
        goto nil_cl_17;
    } else {
        goto cons_cl_18;
    }
nil_cl_17:;
    if_5 = true;
    goto if_next_16;
cons_cl_18:;
    if_5 = false;
    goto if_next_16;
if_next_16:;
    return if_5;
}

int go_22(int len_2, struct StringList const* xs_2) {
tailrec_19:;
    int match_;
    if ((!((!(xs_2))))) goto next_21;
    match_ = len_2;
    goto end_match_20;
next_21:;
    if ((!(xs_2))) goto next_22;
    struct StringList const* xs_3 = xs_2->tail;
    int arg_36 = (len_2 + 1);
    struct StringList const* arg_37 = xs_3;
    len_2 = arg_36;
    xs_2 = arg_37;
    goto tailrec_19;
next_22:;
    exit(1);
end_match_20:;
    return match_;
}

int go_21(int len_2, struct IntList const* xs_2) {
tailrec_23:;
    int match_1;
    if ((!((!(xs_2))))) goto next_25;
    match_1 = len_2;
    goto end_match_24;
next_25:;
    if ((!(xs_2))) goto next_26;
    struct IntList const* xs_3 = xs_2->tail;
    int arg_38 = (len_2 + 1);
    struct IntList const* arg_39 = xs_3;
    len_2 = arg_38;
    xs_2 = arg_39;
    goto tailrec_23;
next_26:;
    exit(1);
end_match_24:;
    return match_1;
}

int listLength_2(struct StringList const* xs_1) {
    int call_2 = go_22(0, xs_1);
    return call_2;
}

int listLength_1(struct IntList const* xs_1) {
    int call_3 = go_21(0, xs_1);
    return call_3;
}

struct IntList const* go_38(struct IntList const* acc_, struct IntList const* xs_5) {
tailrec_27:;
    struct IntList const* match_2;
    if ((!((!(xs_5))))) goto next_29;
    match_2 = acc_;
    goto end_match_28;
next_29:;
    if ((!(xs_5))) goto next_30;
    int x_ = xs_5->head;
    struct IntList const* xs_6 = xs_5->tail;
    struct IntList const* list_ = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_))) = (struct IntList){.head = x_, .tail = acc_};
    struct IntList const* arg_40 = list_;
    struct IntList const* arg_41 = xs_6;
    acc_ = arg_40;
    xs_5 = arg_41;
    goto tailrec_27;
next_30:;
    exit(1);
end_match_28:;
    return match_2;
}

struct StringList const* go_37(struct StringList const* acc_, struct StringList const* xs_5) {
tailrec_31:;
    struct StringList const* match_3;
    if ((!((!(xs_5))))) goto next_33;
    match_3 = acc_;
    goto end_match_32;
next_33:;
    if ((!(xs_5))) goto next_34;
    struct String x_ = xs_5->head;
    struct StringList const* xs_6 = xs_5->tail;
    struct StringList const* list_1 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_1))) = (struct StringList){.head = x_, .tail = acc_};
    struct StringList const* arg_42 = list_1;
    struct StringList const* arg_43 = xs_6;
    acc_ = arg_42;
    xs_5 = arg_43;
    goto tailrec_31;
next_34:;
    exit(1);
end_match_32:;
    return match_3;
}

struct IntList const* listRev_2(struct IntList const* xs_4) {
    struct IntList const* call_4 = go_38(NULL, xs_4);
    return call_4;
}

struct StringList const* listRev_1(struct StringList const* xs_4) {
    struct StringList const* call_5 = go_37(NULL, xs_4);
    return call_5;
}

bool go_24(struct IntIntBoolFun2 itemEqual_, struct IntList const* xs_8, struct IntList const* ys_1) {
tailrec_35:;
    bool match_4;
    struct IntListIntListTuple2 tuple_ = (struct IntListIntListTuple2){.t0 = xs_8, .t1 = ys_1};
    if ((!((!(tuple_.t0))))) goto next_37;
    if ((!((!(tuple_.t1))))) goto next_37;
    match_4 = true;
    goto end_match_36;
next_37:;
    if ((!(tuple_.t0))) goto next_38;
    int x_1 = tuple_.t0->head;
    struct IntList const* xs_9 = tuple_.t0->tail;
    if ((!(tuple_.t1))) goto next_38;
    int y_ = tuple_.t1->head;
    struct IntList const* ys_2 = tuple_.t1->tail;
    bool app_ = itemEqual_.fun(itemEqual_.env, x_1, y_);
    bool if_6;
    if (app_) {
        goto then_41;
    } else {
        goto else_42;
    }
then_41:;
    struct IntIntBoolFun2 arg_44 = itemEqual_;
    struct IntList const* arg_45 = xs_9;
    struct IntList const* arg_46 = ys_2;
    itemEqual_ = arg_44;
    xs_8 = arg_45;
    ys_1 = arg_46;
    goto tailrec_35;
else_42:;
    if_6 = false;
    goto if_next_40;
if_next_40:;
    match_4 = if_6;
    goto end_match_36;
next_38:;
    match_4 = false;
    goto end_match_36;
next_39:;
end_match_36:;
    return match_4;
}

bool go_23(struct StringStringBoolFun2 itemEqual_, struct StringList const* xs_8, struct StringList const* ys_1) {
tailrec_43:;
    bool match_5;
    struct StringListStringListTuple2 tuple_1 = (struct StringListStringListTuple2){.t0 = xs_8, .t1 = ys_1};
    if ((!((!(tuple_1.t0))))) goto next_45;
    if ((!((!(tuple_1.t1))))) goto next_45;
    match_5 = true;
    goto end_match_44;
next_45:;
    if ((!(tuple_1.t0))) goto next_46;
    struct String x_1 = tuple_1.t0->head;
    struct StringList const* xs_9 = tuple_1.t0->tail;
    if ((!(tuple_1.t1))) goto next_46;
    struct String y_ = tuple_1.t1->head;
    struct StringList const* ys_2 = tuple_1.t1->tail;
    bool app_1 = itemEqual_.fun(itemEqual_.env, x_1, y_);
    bool if_7;
    if (app_1) {
        goto then_49;
    } else {
        goto else_50;
    }
then_49:;
    struct StringStringBoolFun2 arg_47 = itemEqual_;
    struct StringList const* arg_48 = xs_9;
    struct StringList const* arg_49 = ys_2;
    itemEqual_ = arg_47;
    xs_8 = arg_48;
    ys_1 = arg_49;
    goto tailrec_43;
else_50:;
    if_7 = false;
    goto if_next_48;
if_next_48:;
    match_5 = if_7;
    goto end_match_44;
next_46:;
    match_5 = false;
    goto end_match_44;
next_47:;
end_match_44:;
    return match_5;
}

bool listEqual_2(struct IntIntBoolFun2 itemEqual_, struct IntList const* xs_7, struct IntList const* ys_) {
    bool call_6 = go_24(itemEqual_, xs_7, ys_);
    return call_6;
}

bool listEqual_1(struct StringStringBoolFun2 itemEqual_, struct StringList const* xs_7, struct StringList const* ys_) {
    bool call_7 = go_23(itemEqual_, xs_7, ys_);
    return call_7;
}

struct IntList const* go_25(int item_, int len_3, struct IntList const* acc_1, int i_) {
tailrec_51:;
    struct IntList const* if_8;
    if ((i_ == len_3)) {
        goto then_53;
    } else {
        goto else_54;
    }
then_53:;
    if_8 = acc_1;
    goto if_next_52;
else_54:;
    int arg_50 = item_;
    int arg_51 = len_3;
    struct IntList const* list_2 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_2))) = (struct IntList){.head = item_, .tail = acc_1};
    struct IntList const* arg_52 = list_2;
    int arg_53 = (i_ + 1);
    item_ = arg_50;
    len_3 = arg_51;
    acc_1 = arg_52;
    i_ = arg_53;
    goto tailrec_51;
if_next_52:;
    return if_8;
}

struct IntList const* listReplicate_1(int item_, int len_3) {
    struct IntList const* call_8 = go_25(item_, len_3, NULL, 0);
    return call_8;
}

struct IntList const* go_26(int len_4, struct IntIntFun1 gen_, struct IntList const* acc_2, int i_1) {
tailrec_55:;
    struct IntList const* if_9;
    if ((i_1 == len_4)) {
        goto then_57;
    } else {
        goto else_58;
    }
then_57:;
    struct IntList const* call_9 = listRev_2(acc_2);
    if_9 = call_9;
    goto if_next_56;
else_58:;
    int arg_54 = len_4;
    struct IntIntFun1 arg_55 = gen_;
    int app_2 = gen_.fun(gen_.env, i_1);
    struct IntList const* list_3 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_3))) = (struct IntList){.head = app_2, .tail = acc_2};
    struct IntList const* arg_56 = list_3;
    int arg_57 = (i_1 + 1);
    len_4 = arg_54;
    gen_ = arg_55;
    acc_2 = arg_56;
    i_1 = arg_57;
    goto tailrec_55;
if_next_56:;
    return if_9;
}

struct IntList const* listInit_1(int len_4, struct IntIntFun1 gen_) {
    milone_assert((len_4 >= 0), 79, 2);
    struct IntList const* call_10 = go_26(len_4, gen_, NULL, 0);
    return call_10;
}

struct StringStringListTuple2 go_5(struct StringList const* xs_11, int xn_) {
    struct StringStringListTuple2 match_6;
    if ((!((!(xs_11))))) goto next_60;
    milone_assert((xn_ == 0), 97, 8);
    struct StringStringListTuple2 tuple_2 = (struct StringStringListTuple2){.t0 = (struct String){.str = "", .len = 0}, .t1 = NULL};
    match_6 = tuple_2;
    goto end_match_59;
next_60:;
    if ((!(xs_11))) goto next_61;
    struct String x_2 = xs_11->head;
    struct StringList const* xs_12 = xs_11->tail;
    if ((xn_ != 1)) goto next_61;
    struct StringStringListTuple2 tuple_3 = (struct StringStringListTuple2){.t0 = x_2, .t1 = xs_12};
    match_6 = tuple_3;
    goto end_match_59;
next_61:;
    if ((!(xs_11))) goto next_62;
    struct String x_3 = xs_11->head;
    if ((!(xs_11->tail))) goto next_62;
    struct String y_1 = xs_11->tail->head;
    struct StringList const* xs_13 = xs_11->tail->tail;
    if ((xn_ != 2)) goto next_62;
    struct StringStringListTuple2 tuple_4 = (struct StringStringListTuple2){.t0 = str_add(x_3, y_1), .t1 = xs_13};
    match_6 = tuple_4;
    goto end_match_59;
next_62:;
    struct StringList const* xs_14 = xs_11;
    int m_ = (xn_ / 2);
    struct StringStringListTuple2 call_11 = go_5(xs_14, m_);
    struct String l_ = call_11.t0;
    struct StringList const* xs_15 = call_11.t1;
    struct StringStringListTuple2 call_12 = go_5(xs_15, (xn_ - m_));
    struct String r_ = call_12.t0;
    struct StringList const* xs_16 = call_12.t1;
    struct StringStringListTuple2 tuple_5 = (struct StringStringListTuple2){.t0 = str_add(l_, r_), .t1 = xs_16};
    match_6 = tuple_5;
    goto end_match_59;
next_63:;
end_match_59:;
    return match_6;
}

struct String strConcat_(struct StringList const* xs_10) {
    int call_13 = listLength_2(xs_10);
    int n_ = call_13;
    struct StringStringListTuple2 call_14 = go_5(xs_10, n_);
    struct String s_ = call_14.t0;
    struct StringList const* xs_17 = call_14.t1;
    bool call_15 = listIsEmpty_1(xs_17);
    milone_assert(call_15, 109, 2);
    return s_;
}

bool intEqual_(int first_, int second_) {
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

bool strEqual_(struct String first_3, struct String second_3) {
    return (str_compare(first_3, second_3) == 0);
}

int failwith_1(struct String msg_) {
    printf("ERROR %s\n", str_to_c_str(msg_));
    exit(1);
}

int fun_21(int arg_58) {
    int call_16 = scanInt_(0);
    return call_16;
}

int fun_3(void const* env_, int arg_) {
    int call_17 = fun_21(arg_);
    return call_17;
}

struct IntList const* scanIntList_(int len_5) {
    struct IntIntFun1 fun_24 = (struct IntIntFun1){.fun = fun_3, .env = NULL};
    struct IntList const* call_18 = listInit_1(len_5, fun_24);
    return call_18;
}

struct IntVoidMutPtrFun1 typeToArrayNew_1(struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6 arg_59) {
    struct IntVoidMutPtrFun1 arrayNew_ = arg_59.t2;
    char _typeTag_2 = arg_59.t5;
    return arrayNew_;
}

struct VoidMutPtrIntIntFun2 typeToArrayGet_1(struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6 arg_60) {
    struct VoidMutPtrIntIntFun2 arrayGet_ = arg_60.t3;
    char _typeTag_3 = arg_60.t5;
    return arrayGet_;
}

struct VoidMutPtrIntIntUnitFun3 typeToArraySet_1(struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6 arg_61) {
    struct VoidMutPtrIntIntUnitFun3 arraySet_ = arg_61.t4;
    char _typeTag_4 = arg_61.t5;
    return arraySet_;
}

void* fun_4(void const* env_1, int arg_1) {
    void* call_19 = rawIntArrayNew_(arg_1);
    return call_19;
}

int fun_5(void const* env_2, void* arg_2, int arg_3) {
    int call_20 = rawIntArrayGet_(arg_2, arg_3);
    return call_20;
}

char fun_6(void const* env_3, void* arg_4, int arg_5, int arg_6) {
    char call_21 = rawIntArraySet_(arg_4, arg_5, arg_6);
    return 0;
}

int vectorToLength_1(struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 arg_62) {
    int len_6 = arg_62.t2;
    char _vectorTag_ = arg_62.t4;
    return len_6;
}

struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 vectorNew_1(struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6 itemTy_, int len_7) {
    struct IntVoidMutPtrFun1 call_22 = typeToArrayNew_1(itemTy_);
    void* app_3 = call_22.fun(call_22.env, len_7);
    void* array_2 = app_3;
    struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 tuple_6 = (struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5){.t0 = itemTy_, .t1 = array_2, .t2 = len_7, .t3 = len_7, .t4 = 0};
    return tuple_6;
}

char vectorCheckIndex_1(int index_2, struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 self_) {
    int call_23 = vectorToLength_1(self_);
    int len_8 = call_23;
    bool if_12;
    if ((index_2 < 0)) {
        goto then_71;
    } else {
        goto else_72;
    }
then_71:;
    if_12 = true;
    goto if_next_70;
else_72:;
    if_12 = (index_2 >= len_8);
    goto if_next_70;
if_next_70:;
    char if_13;
    if (if_12) {
        goto then_74;
    } else {
        goto else_75;
    }
then_74:;
    printf("ERROR: Out of range (len = %d, index = %d)\n", len_8, index_2);
    exit(1);
else_75:;
    if_13 = 0;
    goto if_next_73;
if_next_73:;
    return 0;
}

int vectorGet_1(int index_3, struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 self_1) {
    char call_24 = vectorCheckIndex_1(index_3, self_1);
    struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6 itemTy_1 = self_1.t0;
    void* array_3 = self_1.t1;
    char _vectorTag_1 = self_1.t4;
    struct VoidMutPtrIntIntFun2 call_25 = typeToArrayGet_1(itemTy_1);
    int app_4 = call_25.fun(call_25.env, array_3, index_3);
    return app_4;
}

char vectorSet_1(int index_4, int value_1, struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 self_2) {
    char call_26 = vectorCheckIndex_1(index_4, self_2);
    struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6 itemTy_2 = self_2.t0;
    void* array_4 = self_2.t1;
    char _vectorTag_2 = self_2.t4;
    struct VoidMutPtrIntIntUnitFun3 call_27 = typeToArraySet_1(itemTy_2);
    char app_5 = call_27.fun(call_27.env, array_4, index_4, value_1);
    return 0;
}

char go_27(int len_10, struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 v_, int i_2, struct IntList const* xs_19) {
tailrec_76:;
    char match_7;
    if ((!((!(xs_19))))) goto next_78;
    milone_assert((i_2 == len_10), 205, 12);
    match_7 = 0;
    goto end_match_77;
next_78:;
    if ((!(xs_19))) goto next_79;
    int x_4 = xs_19->head;
    struct IntList const* xs_20 = xs_19->tail;
    char call_28 = vectorSet_1(i_2, x_4, v_);
    int arg_63 = len_10;
    struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 arg_64 = v_;
    int arg_65 = (i_2 + 1);
    struct IntList const* arg_66 = xs_20;
    len_10 = arg_63;
    v_ = arg_64;
    i_2 = arg_65;
    xs_19 = arg_66;
    goto tailrec_76;
next_79:;
    exit(1);
end_match_77:;
    return 0;
}

struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 vectorOfList_1(struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6 ty_, struct IntList const* xs_18) {
    int call_29 = listLength_1(xs_18);
    int len_10 = call_29;
    struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 call_30 = vectorNew_1(ty_, len_10);
    struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 v_ = call_30;
    char call_31 = go_27(len_10, v_, 0, xs_18);
    return v_;
}

char go_7(int len_11, struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 v_1, int i_3) {
tailrec_80:;
    char if_14;
    if ((i_3 < len_11)) {
        goto then_82;
    } else {
        goto else_83;
    }
then_82:;
    int call_32 = scanInt_(0);
    int value_3 = call_32;
    char call_33 = vectorSet_1(i_3, value_3, v_1);
    int arg_67 = len_11;
    struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 arg_68 = v_1;
    int arg_69 = (i_3 + 1);
    len_11 = arg_67;
    v_1 = arg_68;
    i_3 = arg_69;
    goto tailrec_80;
else_83:;
    if_14 = 0;
    goto if_next_81;
if_next_81:;
    return 0;
}

struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 scanIntVector_(int len_11) {
    struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 call_34 = vectorNew_1(typeInt_, len_11);
    struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 v_1 = call_34;
    char call_35 = go_7(len_11, v_1, 0);
    return v_1;
}

char refCase_(char arg_70) {
    struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 call_36 = vectorNew_1(typeInt_, 1);
    struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 v_2 = call_36;
    int call_37 = vectorToLength_1(v_2);
    milone_assert((call_37 == 1), 228, 4);
    int call_38 = vectorGet_1(0, v_2);
    milone_assert((call_38 == 0), 229, 4);
    char call_39 = vectorSet_1(0, 42, v_2);
    int call_40 = vectorGet_1(0, v_2);
    milone_assert((call_40 == 42), 231, 4);
    return 0;
}

char vectorOfListTest_(char arg_71) {
    struct IntList const* list_6 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_6))) = (struct IntList){.head = 3, .tail = NULL};
    struct IntList const* list_5 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_5))) = (struct IntList){.head = 2, .tail = list_6};
    struct IntList const* list_4 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_4))) = (struct IntList){.head = 1, .tail = list_5};
    struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 call_41 = vectorOfList_1(typeInt_, list_4);
    struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6VoidMutPtrIntIntUnitTuple5 v_3 = call_41;
    int call_42 = vectorToLength_1(v_3);
    milone_assert((call_42 == 3), 237, 4);
    int call_43 = vectorGet_1(0, v_3);
    milone_assert((call_43 == 1), 238, 4);
    int call_44 = vectorGet_1(1, v_3);
    milone_assert((call_44 == 2), 239, 4);
    int call_45 = vectorGet_1(2, v_3);
    milone_assert((call_45 == 3), 240, 4);
    return 0;
}

char vectorTest_(char arg_72) {
    char call_46 = refCase_(0);
    char call_47 = vectorOfListTest_(0);
    return 0;
}

bool intervalIsDisjoint_(struct IntIntTuple2 first_4, struct IntIntTuple2 second_4) {
    int xl_ = first_4.t0;
    int xr_ = first_4.t1;
    int yl_ = second_4.t0;
    int yr_ = second_4.t1;
    bool if_15;
    if ((yl_ >= xr_)) {
        goto then_85;
    } else {
        goto else_86;
    }
then_85:;
    if_15 = true;
    goto if_next_84;
else_86:;
    if_15 = (xl_ >= yr_);
    goto if_next_84;
if_next_84:;
    return if_15;
}

bool intervalCovers_(struct IntIntTuple2 first_5, struct IntIntTuple2 second_5) {
    int xl_1 = first_5.t0;
    int xr_1 = first_5.t1;
    int yl_1 = second_5.t0;
    int yr_1 = second_5.t1;
    bool if_16;
    if ((yl_1 >= xl_1)) {
        goto then_88;
    } else {
        goto else_89;
    }
then_88:;
    if_16 = (xr_1 >= yr_1);
    goto if_next_87;
else_89:;
    if_16 = false;
    goto if_next_87;
if_next_87:;
    return if_16;
}

struct StringStringStringFun2 segItemTypeToAppend_2(struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4 arg_73) {
    struct StringStringStringFun2 append_ = arg_73.t0;
    return append_;
}

struct IntIntIntFun2 segItemTypeToAppend_1(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 arg_74) {
    struct IntIntIntFun2 append_ = arg_74.t0;
    return append_;
}

struct IntIntIntObjectUnitTuple5 segItemTypeToEmptyNode_2(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 arg_75) {
    struct IntIntIntObjectUnitTuple5 emptyNode_ = arg_75.t1;
    return emptyNode_;
}

struct StringIntIntObjectUnitTuple5 segItemTypeToEmptyNode_1(struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4 arg_76) {
    struct StringIntIntObjectUnitTuple5 emptyNode_ = arg_76.t1;
    return emptyNode_;
}

void const* segItemTypeToNoChildren_1(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 arg_77) {
    void const* noChildren_ = arg_77.t2;
    return noChildren_;
}

void const* segItemTypeToNoChildren_2(struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4 arg_78) {
    void const* noChildren_ = arg_78.t2;
    return noChildren_;
}

int segItemTypeToEmptyItem_1(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_4) {
    struct IntIntIntObjectUnitTuple5 call_48 = segItemTypeToEmptyNode_2(itemTy_4);
    int call_49 = segNodeToItem_1(call_48);
    return call_49;
}

struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4 segItemTypeNew_2(struct String emptyItem_, struct StringStringStringFun2 append_1) {
    struct StringIntIntObjectUnitTuple5 call_50 = segNodeNewEmpty_2(emptyItem_);
    struct StringIntIntObjectUnitTuple5 emptyNode_1 = call_50;
    struct String app_6 = append_1.fun(append_1.env, emptyItem_, emptyItem_);
    struct StringList const* list_8 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_8))) = (struct StringList){.head = emptyItem_, .tail = NULL};
    struct StringList const* list_7 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_7))) = (struct StringList){.head = app_6, .tail = list_8};
    bool call_51 = listIsEmpty_1(list_7);
    milone_assert((!(call_51)), 42, 2);
    struct StringIntIntObjectUnitTuple5StringIntIntObjectUnitTuple5Tuple2 tuple_8 = (struct StringIntIntObjectUnitTuple5StringIntIntObjectUnitTuple5Tuple2){.t0 = emptyNode_1, .t1 = emptyNode_1};
    void const* box_ = milone_mem_alloc(1, sizeof(struct StringIntIntObjectUnitTuple5StringIntIntObjectUnitTuple5Tuple2));
    (*(((struct StringIntIntObjectUnitTuple5StringIntIntObjectUnitTuple5Tuple2*)box_))) = tuple_8;
    struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4 tuple_7 = (struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4){.t0 = append_1, .t1 = emptyNode_1, .t2 = box_, .t3 = 0};
    struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_5 = tuple_7;
    struct StringStringStringFun2 call_52 = segItemTypeToAppend_2(itemTy_5);
    struct StringStringStringFun2List const* list_10 = milone_mem_alloc(1, sizeof(struct StringStringStringFun2List));
    (*(((struct StringStringStringFun2List*)list_10))) = (struct StringStringStringFun2List){.head = append_1, .tail = NULL};
    struct StringStringStringFun2List const* list_9 = milone_mem_alloc(1, sizeof(struct StringStringStringFun2List));
    (*(((struct StringStringStringFun2List*)list_9))) = (struct StringStringStringFun2List){.head = call_52, .tail = list_10};
    bool call_53 = listIsEmpty_4(list_9);
    milone_assert((!(call_53)), 50, 2);
    return itemTy_5;
}

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 segItemTypeNew_1(int emptyItem_, struct IntIntIntFun2 append_1) {
    struct IntIntIntObjectUnitTuple5 call_54 = segNodeNewEmpty_1(emptyItem_);
    struct IntIntIntObjectUnitTuple5 emptyNode_1 = call_54;
    int app_7 = append_1.fun(append_1.env, emptyItem_, emptyItem_);
    struct IntList const* list_12 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_12))) = (struct IntList){.head = emptyItem_, .tail = NULL};
    struct IntList const* list_11 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_11))) = (struct IntList){.head = app_7, .tail = list_12};
    bool call_55 = listIsEmpty_3(list_11);
    milone_assert((!(call_55)), 42, 2);
    struct IntIntIntObjectUnitTuple5IntIntIntObjectUnitTuple5Tuple2 tuple_10 = (struct IntIntIntObjectUnitTuple5IntIntIntObjectUnitTuple5Tuple2){.t0 = emptyNode_1, .t1 = emptyNode_1};
    void const* box_1 = milone_mem_alloc(1, sizeof(struct IntIntIntObjectUnitTuple5IntIntIntObjectUnitTuple5Tuple2));
    (*(((struct IntIntIntObjectUnitTuple5IntIntIntObjectUnitTuple5Tuple2*)box_1))) = tuple_10;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 tuple_9 = (struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4){.t0 = append_1, .t1 = emptyNode_1, .t2 = box_1, .t3 = 0};
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_5 = tuple_9;
    struct IntIntIntFun2 call_56 = segItemTypeToAppend_1(itemTy_5);
    struct IntIntIntFun2List const* list_14 = milone_mem_alloc(1, sizeof(struct IntIntIntFun2List));
    (*(((struct IntIntIntFun2List*)list_14))) = (struct IntIntIntFun2List){.head = append_1, .tail = NULL};
    struct IntIntIntFun2List const* list_13 = milone_mem_alloc(1, sizeof(struct IntIntIntFun2List));
    (*(((struct IntIntIntFun2List*)list_13))) = (struct IntIntIntFun2List){.head = call_56, .tail = list_14};
    bool call_57 = listIsEmpty_2(list_13);
    milone_assert((!(call_57)), 50, 2);
    return itemTy_5;
}

struct StringIntIntObjectUnitTuple5 segNodeNewEmpty_2(struct String emptyItem_1) {
    struct StringIntIntObjectUnitTuple5 tuple_11 = (struct StringIntIntObjectUnitTuple5){.t0 = emptyItem_1, .t1 = 0, .t2 = -1, .t3 = unitObj_, .t4 = 0};
    return tuple_11;
}

struct IntIntIntObjectUnitTuple5 segNodeNewEmpty_1(int emptyItem_1) {
    struct IntIntIntObjectUnitTuple5 tuple_12 = (struct IntIntIntObjectUnitTuple5){.t0 = emptyItem_1, .t1 = 0, .t2 = -1, .t3 = unitObj_, .t4 = 0};
    return tuple_12;
}

struct IntIntIntObjectUnitTuple5 segNodeNewLeaf_1(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_6, int item_1) {
    void const* call_58 = segItemTypeToNoChildren_1(itemTy_6);
    void const* noChildren_1 = call_58;
    struct IntIntIntObjectUnitTuple5 tuple_13 = (struct IntIntIntObjectUnitTuple5){.t0 = item_1, .t1 = 1, .t2 = 0, .t3 = noChildren_1, .t4 = 0};
    return tuple_13;
}

struct StringIntIntObjectUnitTuple5 segNodeNewLeaf_2(struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_6, struct String item_1) {
    void const* call_59 = segItemTypeToNoChildren_2(itemTy_6);
    void const* noChildren_1 = call_59;
    struct StringIntIntObjectUnitTuple5 tuple_14 = (struct StringIntIntObjectUnitTuple5){.t0 = item_1, .t1 = 1, .t2 = 0, .t3 = noChildren_1, .t4 = 0};
    return tuple_14;
}

struct IntIntIntObjectUnitTuple5 doNew_1(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_7, struct IntIntIntObjectUnitTuple5 left_, struct IntIntIntObjectUnitTuple5 right_, char arg_79) {
    int leftItem_ = left_.t0;
    int leftLen_ = left_.t1;
    int leftHeight_ = left_.t2;
    int rightItem_ = right_.t0;
    int rightLen_ = right_.t1;
    int rightHeight_ = right_.t2;
    bool if_17;
    if ((leftLen_ >= 1)) {
        goto then_91;
    } else {
        goto else_92;
    }
then_91:;
    if_17 = (rightLen_ >= 1);
    goto if_next_90;
else_92:;
    if_17 = false;
    goto if_next_90;
if_next_90:;
    milone_assert(if_17, 73, 4);
    struct IntIntIntFun2 call_60 = segItemTypeToAppend_1(itemTy_7);
    int app_8 = call_60.fun(call_60.env, leftItem_, rightItem_);
    int item_2 = app_8;
    int len_12 = (leftLen_ + rightLen_);
    int call_61 = intMax_(leftHeight_, rightHeight_);
    int height_ = (1 + call_61);
    struct IntIntIntObjectUnitTuple5IntIntIntObjectUnitTuple5Tuple2 tuple_16 = (struct IntIntIntObjectUnitTuple5IntIntIntObjectUnitTuple5Tuple2){.t0 = left_, .t1 = right_};
    void const* box_2 = milone_mem_alloc(1, sizeof(struct IntIntIntObjectUnitTuple5IntIntIntObjectUnitTuple5Tuple2));
    (*(((struct IntIntIntObjectUnitTuple5IntIntIntObjectUnitTuple5Tuple2*)box_2))) = tuple_16;
    struct IntIntIntObjectUnitTuple5 tuple_15 = (struct IntIntIntObjectUnitTuple5){.t0 = item_2, .t1 = len_12, .t2 = height_, .t3 = box_2, .t4 = 0};
    return tuple_15;
}

struct StringIntIntObjectUnitTuple5 doNew_2(struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_7, struct StringIntIntObjectUnitTuple5 left_, struct StringIntIntObjectUnitTuple5 right_, char arg_80) {
    struct String leftItem_ = left_.t0;
    int leftLen_ = left_.t1;
    int leftHeight_ = left_.t2;
    struct String rightItem_ = right_.t0;
    int rightLen_ = right_.t1;
    int rightHeight_ = right_.t2;
    bool if_18;
    if ((leftLen_ >= 1)) {
        goto then_94;
    } else {
        goto else_95;
    }
then_94:;
    if_18 = (rightLen_ >= 1);
    goto if_next_93;
else_95:;
    if_18 = false;
    goto if_next_93;
if_next_93:;
    milone_assert(if_18, 73, 4);
    struct StringStringStringFun2 call_62 = segItemTypeToAppend_2(itemTy_7);
    struct String app_9 = call_62.fun(call_62.env, leftItem_, rightItem_);
    struct String item_2 = app_9;
    int len_12 = (leftLen_ + rightLen_);
    int call_63 = intMax_(leftHeight_, rightHeight_);
    int height_ = (1 + call_63);
    struct StringIntIntObjectUnitTuple5StringIntIntObjectUnitTuple5Tuple2 tuple_18 = (struct StringIntIntObjectUnitTuple5StringIntIntObjectUnitTuple5Tuple2){.t0 = left_, .t1 = right_};
    void const* box_3 = milone_mem_alloc(1, sizeof(struct StringIntIntObjectUnitTuple5StringIntIntObjectUnitTuple5Tuple2));
    (*(((struct StringIntIntObjectUnitTuple5StringIntIntObjectUnitTuple5Tuple2*)box_3))) = tuple_18;
    struct StringIntIntObjectUnitTuple5 tuple_17 = (struct StringIntIntObjectUnitTuple5){.t0 = item_2, .t1 = len_12, .t2 = height_, .t3 = box_3, .t4 = 0};
    return tuple_17;
}

struct IntIntIntObjectUnitTuple5 segNodeNew_1(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_7, struct IntIntIntObjectUnitTuple5 left_, struct IntIntIntObjectUnitTuple5 right_) {
    struct IntIntIntObjectUnitTuple5 match_8;
    int call_64 = segNodeToLength_1(left_);
    int call_65 = segNodeToLength_1(right_);
    struct IntIntTuple2 tuple_19 = (struct IntIntTuple2){.t0 = call_64, .t1 = call_65};
    if ((tuple_19.t0 != 0)) goto next_97;
    if ((tuple_19.t1 != 0)) goto next_97;
    struct IntIntIntObjectUnitTuple5 call_66 = segItemTypeToEmptyNode_2(itemTy_7);
    match_8 = call_66;
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
    struct IntIntIntObjectUnitTuple5 call_67 = doNew_1(itemTy_7, left_, right_, 0);
    match_8 = call_67;
    goto end_match_96;
next_100:;
end_match_96:;
    return match_8;
}

struct StringIntIntObjectUnitTuple5 segNodeNew_2(struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_7, struct StringIntIntObjectUnitTuple5 left_, struct StringIntIntObjectUnitTuple5 right_) {
    struct StringIntIntObjectUnitTuple5 match_9;
    int call_68 = segNodeToLength_2(left_);
    int call_69 = segNodeToLength_2(right_);
    struct IntIntTuple2 tuple_20 = (struct IntIntTuple2){.t0 = call_68, .t1 = call_69};
    if ((tuple_20.t0 != 0)) goto next_102;
    if ((tuple_20.t1 != 0)) goto next_102;
    struct StringIntIntObjectUnitTuple5 call_70 = segItemTypeToEmptyNode_1(itemTy_7);
    match_9 = call_70;
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
    struct StringIntIntObjectUnitTuple5 call_71 = doNew_2(itemTy_7, left_, right_, 0);
    match_9 = call_71;
    goto end_match_101;
next_105:;
end_match_101:;
    return match_9;
}

int segNodeToItem_1(struct IntIntIntObjectUnitTuple5 node_) {
    int item_3 = node_.t0;
    return item_3;
}

int segNodeToLength_1(struct IntIntIntObjectUnitTuple5 node_1) {
    int len_13 = node_1.t1;
    return len_13;
}

int segNodeToLength_2(struct StringIntIntObjectUnitTuple5 node_1) {
    int len_13 = node_1.t1;
    return len_13;
}

int segNodeToHeight_1(struct IntIntIntObjectUnitTuple5 node_2) {
    int height_1 = node_2.t2;
    return height_1;
}

int segNodeToHeight_2(struct StringIntIntObjectUnitTuple5 node_2) {
    int height_1 = node_2.t2;
    return height_1;
}

struct IntIntIntObjectUnitTuple5IntIntIntObjectUnitTuple5Tuple2 segNodeToChildren_1(struct IntIntIntObjectUnitTuple5 node_3) {
    int len_14 = node_3.t1;
    void const* children_ = node_3.t3;
    milone_assert((len_14 >= 2), 116, 2);
    struct IntIntIntObjectUnitTuple5 left_1 = (*(((struct IntIntIntObjectUnitTuple5IntIntIntObjectUnitTuple5Tuple2 const*)children_))).t0;
    struct IntIntIntObjectUnitTuple5 right_1 = (*(((struct IntIntIntObjectUnitTuple5IntIntIntObjectUnitTuple5Tuple2 const*)children_))).t1;
    struct IntIntIntObjectUnitTuple5List const* list_17 = milone_mem_alloc(1, sizeof(struct IntIntIntObjectUnitTuple5List));
    (*(((struct IntIntIntObjectUnitTuple5List*)list_17))) = (struct IntIntIntObjectUnitTuple5List){.head = right_1, .tail = NULL};
    struct IntIntIntObjectUnitTuple5List const* list_16 = milone_mem_alloc(1, sizeof(struct IntIntIntObjectUnitTuple5List));
    (*(((struct IntIntIntObjectUnitTuple5List*)list_16))) = (struct IntIntIntObjectUnitTuple5List){.head = left_1, .tail = list_17};
    struct IntIntIntObjectUnitTuple5List const* list_15 = milone_mem_alloc(1, sizeof(struct IntIntIntObjectUnitTuple5List));
    (*(((struct IntIntIntObjectUnitTuple5List*)list_15))) = (struct IntIntIntObjectUnitTuple5List){.head = node_3, .tail = list_16};
    bool call_72 = listIsEmpty_5(list_15);
    milone_assert((!(call_72)), 121, 2);
    struct IntIntIntObjectUnitTuple5IntIntIntObjectUnitTuple5Tuple2 tuple_21 = (struct IntIntIntObjectUnitTuple5IntIntIntObjectUnitTuple5Tuple2){.t0 = left_1, .t1 = right_1};
    return tuple_21;
}

struct StringIntIntObjectUnitTuple5StringIntIntObjectUnitTuple5Tuple2 segNodeToChildren_2(struct StringIntIntObjectUnitTuple5 node_3) {
    int len_14 = node_3.t1;
    void const* children_ = node_3.t3;
    milone_assert((len_14 >= 2), 116, 2);
    struct StringIntIntObjectUnitTuple5 left_1 = (*(((struct StringIntIntObjectUnitTuple5StringIntIntObjectUnitTuple5Tuple2 const*)children_))).t0;
    struct StringIntIntObjectUnitTuple5 right_1 = (*(((struct StringIntIntObjectUnitTuple5StringIntIntObjectUnitTuple5Tuple2 const*)children_))).t1;
    struct StringIntIntObjectUnitTuple5List const* list_20 = milone_mem_alloc(1, sizeof(struct StringIntIntObjectUnitTuple5List));
    (*(((struct StringIntIntObjectUnitTuple5List*)list_20))) = (struct StringIntIntObjectUnitTuple5List){.head = right_1, .tail = NULL};
    struct StringIntIntObjectUnitTuple5List const* list_19 = milone_mem_alloc(1, sizeof(struct StringIntIntObjectUnitTuple5List));
    (*(((struct StringIntIntObjectUnitTuple5List*)list_19))) = (struct StringIntIntObjectUnitTuple5List){.head = left_1, .tail = list_20};
    struct StringIntIntObjectUnitTuple5List const* list_18 = milone_mem_alloc(1, sizeof(struct StringIntIntObjectUnitTuple5List));
    (*(((struct StringIntIntObjectUnitTuple5List*)list_18))) = (struct StringIntIntObjectUnitTuple5List){.head = node_3, .tail = list_19};
    bool call_73 = listIsEmpty_6(list_18);
    milone_assert((!(call_73)), 121, 2);
    struct StringIntIntObjectUnitTuple5StringIntIntObjectUnitTuple5Tuple2 tuple_22 = (struct StringIntIntObjectUnitTuple5StringIntIntObjectUnitTuple5Tuple2){.t0 = left_1, .t1 = right_1};
    return tuple_22;
}

bool segNodeIsEmpty_1(struct IntIntIntObjectUnitTuple5 node_4) {
    int call_74 = segNodeToLength_1(node_4);
    return (call_74 == 0);
}

struct IntIntIntObjectUnitTuple5 segNodeWithLeft_1(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_8, struct IntIntIntObjectUnitTuple5 newLeft_, struct IntIntIntObjectUnitTuple5 node_5) {
    int call_75 = segNodeToLength_1(node_5);
    milone_assert((call_75 >= 1), 128, 2);
    struct IntIntIntObjectUnitTuple5IntIntIntObjectUnitTuple5Tuple2 call_76 = segNodeToChildren_1(node_5);
    struct IntIntIntObjectUnitTuple5 right_2 = call_76.t1;
    struct IntIntIntObjectUnitTuple5 call_77 = segNodeNew_1(itemTy_8, newLeft_, right_2);
    return call_77;
}

struct StringIntIntObjectUnitTuple5 segNodeWithLeft_2(struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_8, struct StringIntIntObjectUnitTuple5 newLeft_, struct StringIntIntObjectUnitTuple5 node_5) {
    int call_78 = segNodeToLength_2(node_5);
    milone_assert((call_78 >= 1), 128, 2);
    struct StringIntIntObjectUnitTuple5StringIntIntObjectUnitTuple5Tuple2 call_79 = segNodeToChildren_2(node_5);
    struct StringIntIntObjectUnitTuple5 right_2 = call_79.t1;
    struct StringIntIntObjectUnitTuple5 call_80 = segNodeNew_2(itemTy_8, newLeft_, right_2);
    return call_80;
}

struct IntIntIntObjectUnitTuple5 segNodeWithRight_1(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_9, struct IntIntIntObjectUnitTuple5 newRight_, struct IntIntIntObjectUnitTuple5 node_6) {
    int call_81 = segNodeToLength_1(node_6);
    milone_assert((call_81 >= 1), 133, 2);
    struct IntIntIntObjectUnitTuple5IntIntIntObjectUnitTuple5Tuple2 call_82 = segNodeToChildren_1(node_6);
    struct IntIntIntObjectUnitTuple5 left_2 = call_82.t0;
    struct IntIntIntObjectUnitTuple5 call_83 = segNodeNew_1(itemTy_9, left_2, newRight_);
    return call_83;
}

struct StringIntIntObjectUnitTuple5 segNodeWithRight_2(struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_9, struct StringIntIntObjectUnitTuple5 newRight_, struct StringIntIntObjectUnitTuple5 node_6) {
    int call_84 = segNodeToLength_2(node_6);
    milone_assert((call_84 >= 1), 133, 2);
    struct StringIntIntObjectUnitTuple5StringIntIntObjectUnitTuple5Tuple2 call_85 = segNodeToChildren_2(node_6);
    struct StringIntIntObjectUnitTuple5 left_2 = call_85.t0;
    struct StringIntIntObjectUnitTuple5 call_86 = segNodeNew_2(itemTy_9, left_2, newRight_);
    return call_86;
}

struct IntIntIntObjectUnitTuple5 rotateLeft_1(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_10, struct IntIntIntObjectUnitTuple5 node_8) {
    int call_87 = segNodeToLength_1(node_8);
    struct IntIntIntObjectUnitTuple5 if_19;
    if ((call_87 < 2)) {
        goto then_107;
    } else {
        goto else_108;
    }
then_107:;
    if_19 = node_8;
    goto if_next_106;
else_108:;
    struct IntIntIntObjectUnitTuple5IntIntIntObjectUnitTuple5Tuple2 call_88 = segNodeToChildren_1(node_8);
    struct IntIntIntObjectUnitTuple5 right_3 = call_88.t1;
    int call_89 = segNodeToLength_1(right_3);
    struct IntIntIntObjectUnitTuple5 if_20;
    if ((call_89 < 2)) {
        goto then_110;
    } else {
        goto else_111;
    }
then_110:;
    if_20 = node_8;
    goto if_next_109;
else_111:;
    struct IntIntIntObjectUnitTuple5IntIntIntObjectUnitTuple5Tuple2 call_90 = segNodeToChildren_1(right_3);
    struct IntIntIntObjectUnitTuple5 x_5 = call_90.t0;
    struct IntIntIntObjectUnitTuple5 call_91 = segNodeWithRight_1(itemTy_10, x_5, node_8);
    struct IntIntIntObjectUnitTuple5 u_ = call_91;
    struct IntIntIntObjectUnitTuple5 call_92 = segNodeWithLeft_1(itemTy_10, u_, right_3);
    struct IntIntIntObjectUnitTuple5 t_ = call_92;
    if_20 = t_;
    goto if_next_109;
if_next_109:;
    if_19 = if_20;
    goto if_next_106;
if_next_106:;
    return if_19;
}

struct StringIntIntObjectUnitTuple5 rotateLeft_2(struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_10, struct StringIntIntObjectUnitTuple5 node_8) {
    int call_93 = segNodeToLength_2(node_8);
    struct StringIntIntObjectUnitTuple5 if_21;
    if ((call_93 < 2)) {
        goto then_113;
    } else {
        goto else_114;
    }
then_113:;
    if_21 = node_8;
    goto if_next_112;
else_114:;
    struct StringIntIntObjectUnitTuple5StringIntIntObjectUnitTuple5Tuple2 call_94 = segNodeToChildren_2(node_8);
    struct StringIntIntObjectUnitTuple5 right_3 = call_94.t1;
    int call_95 = segNodeToLength_2(right_3);
    struct StringIntIntObjectUnitTuple5 if_22;
    if ((call_95 < 2)) {
        goto then_116;
    } else {
        goto else_117;
    }
then_116:;
    if_22 = node_8;
    goto if_next_115;
else_117:;
    struct StringIntIntObjectUnitTuple5StringIntIntObjectUnitTuple5Tuple2 call_96 = segNodeToChildren_2(right_3);
    struct StringIntIntObjectUnitTuple5 x_5 = call_96.t0;
    struct StringIntIntObjectUnitTuple5 call_97 = segNodeWithRight_2(itemTy_10, x_5, node_8);
    struct StringIntIntObjectUnitTuple5 u_ = call_97;
    struct StringIntIntObjectUnitTuple5 call_98 = segNodeWithLeft_2(itemTy_10, u_, right_3);
    struct StringIntIntObjectUnitTuple5 t_ = call_98;
    if_22 = t_;
    goto if_next_115;
if_next_115:;
    if_21 = if_22;
    goto if_next_112;
if_next_112:;
    return if_21;
}

struct IntIntIntObjectUnitTuple5 rotateRight_1(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_10, struct IntIntIntObjectUnitTuple5 node_9) {
    int call_99 = segNodeToLength_1(node_9);
    struct IntIntIntObjectUnitTuple5 if_23;
    if ((call_99 < 2)) {
        goto then_119;
    } else {
        goto else_120;
    }
then_119:;
    if_23 = node_9;
    goto if_next_118;
else_120:;
    struct IntIntIntObjectUnitTuple5IntIntIntObjectUnitTuple5Tuple2 call_100 = segNodeToChildren_1(node_9);
    struct IntIntIntObjectUnitTuple5 left_3 = call_100.t0;
    int call_101 = segNodeToLength_1(left_3);
    struct IntIntIntObjectUnitTuple5 if_24;
    if ((call_101 < 2)) {
        goto then_122;
    } else {
        goto else_123;
    }
then_122:;
    if_24 = node_9;
    goto if_next_121;
else_123:;
    struct IntIntIntObjectUnitTuple5IntIntIntObjectUnitTuple5Tuple2 call_102 = segNodeToChildren_1(left_3);
    struct IntIntIntObjectUnitTuple5 y_2 = call_102.t1;
    struct IntIntIntObjectUnitTuple5 call_103 = segNodeWithLeft_1(itemTy_10, y_2, node_9);
    struct IntIntIntObjectUnitTuple5 u_1 = call_103;
    struct IntIntIntObjectUnitTuple5 call_104 = segNodeWithRight_1(itemTy_10, u_1, left_3);
    struct IntIntIntObjectUnitTuple5 t_1 = call_104;
    if_24 = t_1;
    goto if_next_121;
if_next_121:;
    if_23 = if_24;
    goto if_next_118;
if_next_118:;
    return if_23;
}

struct StringIntIntObjectUnitTuple5 rotateRight_2(struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_10, struct StringIntIntObjectUnitTuple5 node_9) {
    int call_105 = segNodeToLength_2(node_9);
    struct StringIntIntObjectUnitTuple5 if_25;
    if ((call_105 < 2)) {
        goto then_125;
    } else {
        goto else_126;
    }
then_125:;
    if_25 = node_9;
    goto if_next_124;
else_126:;
    struct StringIntIntObjectUnitTuple5StringIntIntObjectUnitTuple5Tuple2 call_106 = segNodeToChildren_2(node_9);
    struct StringIntIntObjectUnitTuple5 left_3 = call_106.t0;
    int call_107 = segNodeToLength_2(left_3);
    struct StringIntIntObjectUnitTuple5 if_26;
    if ((call_107 < 2)) {
        goto then_128;
    } else {
        goto else_129;
    }
then_128:;
    if_26 = node_9;
    goto if_next_127;
else_129:;
    struct StringIntIntObjectUnitTuple5StringIntIntObjectUnitTuple5Tuple2 call_108 = segNodeToChildren_2(left_3);
    struct StringIntIntObjectUnitTuple5 y_2 = call_108.t1;
    struct StringIntIntObjectUnitTuple5 call_109 = segNodeWithLeft_2(itemTy_10, y_2, node_9);
    struct StringIntIntObjectUnitTuple5 u_1 = call_109;
    struct StringIntIntObjectUnitTuple5 call_110 = segNodeWithRight_2(itemTy_10, u_1, left_3);
    struct StringIntIntObjectUnitTuple5 t_1 = call_110;
    if_26 = t_1;
    goto if_next_127;
if_next_127:;
    if_25 = if_26;
    goto if_next_124;
if_next_124:;
    return if_25;
}

struct IntIntIntObjectUnitTuple5 doubleLeft_1(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_10, struct IntIntIntObjectUnitTuple5 node_10) {
    int call_111 = segNodeToLength_1(node_10);
    struct IntIntIntObjectUnitTuple5 if_27;
    if ((call_111 < 2)) {
        goto then_131;
    } else {
        goto else_132;
    }
then_131:;
    if_27 = node_10;
    goto if_next_130;
else_132:;
    struct IntIntIntObjectUnitTuple5IntIntIntObjectUnitTuple5Tuple2 call_112 = segNodeToChildren_1(node_10);
    struct IntIntIntObjectUnitTuple5 right_4 = call_112.t1;
    struct IntIntIntObjectUnitTuple5 call_113 = rotateRight_1(itemTy_10, right_4);
    struct IntIntIntObjectUnitTuple5 call_114 = segNodeWithRight_1(itemTy_10, call_113, node_10);
    struct IntIntIntObjectUnitTuple5 call_115 = rotateLeft_1(itemTy_10, call_114);
    if_27 = call_115;
    goto if_next_130;
if_next_130:;
    return if_27;
}

struct StringIntIntObjectUnitTuple5 doubleLeft_2(struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_10, struct StringIntIntObjectUnitTuple5 node_10) {
    int call_116 = segNodeToLength_2(node_10);
    struct StringIntIntObjectUnitTuple5 if_28;
    if ((call_116 < 2)) {
        goto then_134;
    } else {
        goto else_135;
    }
then_134:;
    if_28 = node_10;
    goto if_next_133;
else_135:;
    struct StringIntIntObjectUnitTuple5StringIntIntObjectUnitTuple5Tuple2 call_117 = segNodeToChildren_2(node_10);
    struct StringIntIntObjectUnitTuple5 right_4 = call_117.t1;
    struct StringIntIntObjectUnitTuple5 call_118 = rotateRight_2(itemTy_10, right_4);
    struct StringIntIntObjectUnitTuple5 call_119 = segNodeWithRight_2(itemTy_10, call_118, node_10);
    struct StringIntIntObjectUnitTuple5 call_120 = rotateLeft_2(itemTy_10, call_119);
    if_28 = call_120;
    goto if_next_133;
if_next_133:;
    return if_28;
}

struct IntIntIntObjectUnitTuple5 doubleRight_1(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_10, struct IntIntIntObjectUnitTuple5 node_11) {
    int call_121 = segNodeToLength_1(node_11);
    struct IntIntIntObjectUnitTuple5 if_29;
    if ((call_121 < 2)) {
        goto then_137;
    } else {
        goto else_138;
    }
then_137:;
    if_29 = node_11;
    goto if_next_136;
else_138:;
    struct IntIntIntObjectUnitTuple5IntIntIntObjectUnitTuple5Tuple2 call_122 = segNodeToChildren_1(node_11);
    struct IntIntIntObjectUnitTuple5 left_4 = call_122.t0;
    struct IntIntIntObjectUnitTuple5 call_123 = rotateLeft_1(itemTy_10, left_4);
    struct IntIntIntObjectUnitTuple5 call_124 = segNodeWithLeft_1(itemTy_10, call_123, node_11);
    struct IntIntIntObjectUnitTuple5 call_125 = rotateRight_1(itemTy_10, call_124);
    if_29 = call_125;
    goto if_next_136;
if_next_136:;
    return if_29;
}

struct StringIntIntObjectUnitTuple5 doubleRight_2(struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_10, struct StringIntIntObjectUnitTuple5 node_11) {
    int call_126 = segNodeToLength_2(node_11);
    struct StringIntIntObjectUnitTuple5 if_30;
    if ((call_126 < 2)) {
        goto then_140;
    } else {
        goto else_141;
    }
then_140:;
    if_30 = node_11;
    goto if_next_139;
else_141:;
    struct StringIntIntObjectUnitTuple5StringIntIntObjectUnitTuple5Tuple2 call_127 = segNodeToChildren_2(node_11);
    struct StringIntIntObjectUnitTuple5 left_4 = call_127.t0;
    struct StringIntIntObjectUnitTuple5 call_128 = rotateLeft_2(itemTy_10, left_4);
    struct StringIntIntObjectUnitTuple5 call_129 = segNodeWithLeft_2(itemTy_10, call_128, node_11);
    struct StringIntIntObjectUnitTuple5 call_130 = rotateRight_2(itemTy_10, call_129);
    if_30 = call_130;
    goto if_next_139;
if_next_139:;
    return if_30;
}

int toBalance_1(struct IntIntIntObjectUnitTuple5 node_12) {
    int call_131 = segNodeToLength_1(node_12);
    int if_31;
    if ((call_131 < 2)) {
        goto then_143;
    } else {
        goto else_144;
    }
then_143:;
    if_31 = 0;
    goto if_next_142;
else_144:;
    struct IntIntIntObjectUnitTuple5IntIntIntObjectUnitTuple5Tuple2 call_132 = segNodeToChildren_1(node_12);
    struct IntIntIntObjectUnitTuple5 left_5 = call_132.t0;
    struct IntIntIntObjectUnitTuple5 right_5 = call_132.t1;
    int call_133 = segNodeToHeight_1(right_5);
    int call_134 = segNodeToHeight_1(left_5);
    if_31 = (call_133 - call_134);
    goto if_next_142;
if_next_142:;
    return if_31;
}

int toBalance_2(struct StringIntIntObjectUnitTuple5 node_12) {
    int call_135 = segNodeToLength_2(node_12);
    int if_32;
    if ((call_135 < 2)) {
        goto then_146;
    } else {
        goto else_147;
    }
then_146:;
    if_32 = 0;
    goto if_next_145;
else_147:;
    struct StringIntIntObjectUnitTuple5StringIntIntObjectUnitTuple5Tuple2 call_136 = segNodeToChildren_2(node_12);
    struct StringIntIntObjectUnitTuple5 left_5 = call_136.t0;
    struct StringIntIntObjectUnitTuple5 right_5 = call_136.t1;
    int call_137 = segNodeToHeight_2(right_5);
    int call_138 = segNodeToHeight_2(left_5);
    if_32 = (call_137 - call_138);
    goto if_next_145;
if_next_145:;
    return if_32;
}

struct IntIntIntObjectUnitTuple5 segNodeMakeBalanced_1(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_10, struct IntIntIntObjectUnitTuple5 node_7) {
    int call_139 = toBalance_1(node_7);
    int selfBalance_ = call_139;
    bool if_33;
    if ((selfBalance_ >= -1)) {
        goto then_149;
    } else {
        goto else_150;
    }
then_149:;
    if_33 = (1 >= selfBalance_);
    goto if_next_148;
else_150:;
    if_33 = false;
    goto if_next_148;
if_next_148:;
    struct IntIntIntObjectUnitTuple5 if_34;
    if (if_33) {
        goto then_152;
    } else {
        goto else_153;
    }
then_152:;
    if_34 = node_7;
    goto if_next_151;
else_153:;
    int call_140 = segNodeToLength_1(node_7);
    struct IntIntIntObjectUnitTuple5 if_35;
    if ((call_140 < 2)) {
        goto then_155;
    } else {
        goto else_156;
    }
then_155:;
    if_35 = node_7;
    goto if_next_154;
else_156:;
    struct IntIntIntObjectUnitTuple5IntIntIntObjectUnitTuple5Tuple2 call_141 = segNodeToChildren_1(node_7);
    struct IntIntIntObjectUnitTuple5 left_6 = call_141.t0;
    struct IntIntIntObjectUnitTuple5 right_6 = call_141.t1;
    struct IntIntIntObjectUnitTuple5 if_36;
    if ((selfBalance_ >= 2)) {
        goto then_158;
    } else {
        goto else_162;
    }
then_158:;
    int call_142 = toBalance_1(right_6);
    struct IntIntIntObjectUnitTuple5 if_37;
    if ((call_142 < 0)) {
        goto then_160;
    } else {
        goto else_161;
    }
then_160:;
    struct IntIntIntObjectUnitTuple5 call_143 = doubleLeft_1(itemTy_10, node_7);
    if_37 = call_143;
    goto if_next_159;
else_161:;
    struct IntIntIntObjectUnitTuple5 call_144 = rotateLeft_1(itemTy_10, node_7);
    if_37 = call_144;
    goto if_next_159;
if_next_159:;
    if_36 = if_37;
    goto if_next_157;
else_162:;
    int call_145 = toBalance_1(left_6);
    struct IntIntIntObjectUnitTuple5 if_38;
    if ((0 < call_145)) {
        goto then_164;
    } else {
        goto else_165;
    }
then_164:;
    struct IntIntIntObjectUnitTuple5 call_146 = doubleRight_1(itemTy_10, node_7);
    if_38 = call_146;
    goto if_next_163;
else_165:;
    struct IntIntIntObjectUnitTuple5 call_147 = rotateRight_1(itemTy_10, node_7);
    if_38 = call_147;
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

struct StringIntIntObjectUnitTuple5 segNodeMakeBalanced_2(struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_10, struct StringIntIntObjectUnitTuple5 node_7) {
    int call_148 = toBalance_2(node_7);
    int selfBalance_ = call_148;
    bool if_39;
    if ((selfBalance_ >= -1)) {
        goto then_167;
    } else {
        goto else_168;
    }
then_167:;
    if_39 = (1 >= selfBalance_);
    goto if_next_166;
else_168:;
    if_39 = false;
    goto if_next_166;
if_next_166:;
    struct StringIntIntObjectUnitTuple5 if_40;
    if (if_39) {
        goto then_170;
    } else {
        goto else_171;
    }
then_170:;
    if_40 = node_7;
    goto if_next_169;
else_171:;
    int call_149 = segNodeToLength_2(node_7);
    struct StringIntIntObjectUnitTuple5 if_41;
    if ((call_149 < 2)) {
        goto then_173;
    } else {
        goto else_174;
    }
then_173:;
    if_41 = node_7;
    goto if_next_172;
else_174:;
    struct StringIntIntObjectUnitTuple5StringIntIntObjectUnitTuple5Tuple2 call_150 = segNodeToChildren_2(node_7);
    struct StringIntIntObjectUnitTuple5 left_6 = call_150.t0;
    struct StringIntIntObjectUnitTuple5 right_6 = call_150.t1;
    struct StringIntIntObjectUnitTuple5 if_42;
    if ((selfBalance_ >= 2)) {
        goto then_176;
    } else {
        goto else_180;
    }
then_176:;
    int call_151 = toBalance_2(right_6);
    struct StringIntIntObjectUnitTuple5 if_43;
    if ((call_151 < 0)) {
        goto then_178;
    } else {
        goto else_179;
    }
then_178:;
    struct StringIntIntObjectUnitTuple5 call_152 = doubleLeft_2(itemTy_10, node_7);
    if_43 = call_152;
    goto if_next_177;
else_179:;
    struct StringIntIntObjectUnitTuple5 call_153 = rotateLeft_2(itemTy_10, node_7);
    if_43 = call_153;
    goto if_next_177;
if_next_177:;
    if_42 = if_43;
    goto if_next_175;
else_180:;
    int call_154 = toBalance_2(left_6);
    struct StringIntIntObjectUnitTuple5 if_44;
    if ((0 < call_154)) {
        goto then_182;
    } else {
        goto else_183;
    }
then_182:;
    struct StringIntIntObjectUnitTuple5 call_155 = doubleRight_2(itemTy_10, node_7);
    if_44 = call_155;
    goto if_next_181;
else_183:;
    struct StringIntIntObjectUnitTuple5 call_156 = rotateRight_2(itemTy_10, node_7);
    if_44 = call_156;
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

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 segTreeNew_2(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_11) {
    struct IntIntIntObjectUnitTuple5 call_157 = segItemTypeToEmptyNode_2(itemTy_11);
    struct IntIntIntObjectUnitTuple5 emptyNode_2 = call_157;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 tuple_23 = (struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3){.t0 = itemTy_11, .t1 = emptyNode_2, .t2 = 0};
    return tuple_23;
}

struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4StringIntIntObjectUnitTuple5UnitTuple3 segTreeNew_1(struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_11) {
    struct StringIntIntObjectUnitTuple5 call_158 = segItemTypeToEmptyNode_1(itemTy_11);
    struct StringIntIntObjectUnitTuple5 emptyNode_2 = call_158;
    struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4StringIntIntObjectUnitTuple5UnitTuple3 tuple_24 = (struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4StringIntIntObjectUnitTuple5UnitTuple3){.t0 = itemTy_11, .t1 = emptyNode_2, .t2 = 0};
    return tuple_24;
}

struct IntIntIntObjectUnitTuple5 segTreeToRoot_1(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 self_4) {
    struct IntIntIntObjectUnitTuple5 node_13 = self_4.t1;
    return node_13;
}

struct StringIntIntObjectUnitTuple5 segTreeToRoot_2(struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4StringIntIntObjectUnitTuple5UnitTuple3 self_4) {
    struct StringIntIntObjectUnitTuple5 node_13 = self_4.t1;
    return node_13;
}

int segTreeToLength_1(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 self_5) {
    struct IntIntIntObjectUnitTuple5 call_159 = segTreeToRoot_1(self_5);
    int call_160 = segNodeToLength_1(call_159);
    return call_160;
}

int segTreeToLength_2(struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4StringIntIntObjectUnitTuple5UnitTuple3 self_5) {
    struct StringIntIntObjectUnitTuple5 call_161 = segTreeToRoot_2(self_5);
    int call_162 = segNodeToLength_2(call_161);
    return call_162;
}

int segTreeToHeight_1(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 self_6) {
    struct IntIntIntObjectUnitTuple5 call_163 = segTreeToRoot_1(self_6);
    int call_164 = segNodeToHeight_1(call_163);
    return call_164;
}

int go_28(int index_6, struct IntIntIntObjectUnitTuple5 node_14) {
tailrec_184:;
    int item_4 = node_14.t0;
    int len_15 = node_14.t1;
    bool if_45;
    if ((index_6 < 0)) {
        goto then_186;
    } else {
        goto else_187;
    }
then_186:;
    if_45 = true;
    goto if_next_185;
else_187:;
    if_45 = (index_6 >= len_15);
    goto if_next_185;
if_next_185:;
    char if_46;
    if (if_45) {
        goto then_189;
    } else {
        goto else_190;
    }
then_189:;
    printf("ERROR: segNodeGet out of range (index = %d, len = %d)\n", index_6, len_15);
    exit(1);
else_190:;
    if_46 = 0;
    goto if_next_188;
if_next_188:;
    milone_assert((len_15 != 0), 277, 4);
    int if_47;
    if ((len_15 == 1)) {
        goto then_192;
    } else {
        goto else_193;
    }
then_192:;
    if_47 = item_4;
    goto if_next_191;
else_193:;
    struct IntIntIntObjectUnitTuple5IntIntIntObjectUnitTuple5Tuple2 call_165 = segNodeToChildren_1(node_14);
    struct IntIntIntObjectUnitTuple5 left_7 = call_165.t0;
    struct IntIntIntObjectUnitTuple5 right_7 = call_165.t1;
    int call_166 = segNodeToLength_1(left_7);
    int leftLen_1 = call_166;
    int if_48;
    if ((index_6 < leftLen_1)) {
        goto then_195;
    } else {
        goto else_196;
    }
then_195:;
    int arg_81 = index_6;
    struct IntIntIntObjectUnitTuple5 arg_82 = left_7;
    index_6 = arg_81;
    node_14 = arg_82;
    goto tailrec_184;
else_196:;
    int arg_83 = (index_6 - leftLen_1);
    struct IntIntIntObjectUnitTuple5 arg_84 = right_7;
    index_6 = arg_83;
    node_14 = arg_84;
    goto tailrec_184;
if_next_194:;
    if_47 = if_48;
    goto if_next_191;
if_next_191:;
    return if_47;
}

struct String go_39(int index_6, struct StringIntIntObjectUnitTuple5 node_14) {
tailrec_197:;
    struct String item_4 = node_14.t0;
    int len_15 = node_14.t1;
    bool if_49;
    if ((index_6 < 0)) {
        goto then_199;
    } else {
        goto else_200;
    }
then_199:;
    if_49 = true;
    goto if_next_198;
else_200:;
    if_49 = (index_6 >= len_15);
    goto if_next_198;
if_next_198:;
    char if_50;
    if (if_49) {
        goto then_202;
    } else {
        goto else_203;
    }
then_202:;
    printf("ERROR: segNodeGet out of range (index = %d, len = %d)\n", index_6, len_15);
    exit(1);
else_203:;
    if_50 = 0;
    goto if_next_201;
if_next_201:;
    milone_assert((len_15 != 0), 277, 4);
    struct String if_51;
    if ((len_15 == 1)) {
        goto then_205;
    } else {
        goto else_206;
    }
then_205:;
    if_51 = item_4;
    goto if_next_204;
else_206:;
    struct StringIntIntObjectUnitTuple5StringIntIntObjectUnitTuple5Tuple2 call_167 = segNodeToChildren_2(node_14);
    struct StringIntIntObjectUnitTuple5 left_7 = call_167.t0;
    struct StringIntIntObjectUnitTuple5 right_7 = call_167.t1;
    int call_168 = segNodeToLength_2(left_7);
    int leftLen_1 = call_168;
    struct String if_52;
    if ((index_6 < leftLen_1)) {
        goto then_208;
    } else {
        goto else_209;
    }
then_208:;
    int arg_85 = index_6;
    struct StringIntIntObjectUnitTuple5 arg_86 = left_7;
    index_6 = arg_85;
    node_14 = arg_86;
    goto tailrec_197;
else_209:;
    int arg_87 = (index_6 - leftLen_1);
    struct StringIntIntObjectUnitTuple5 arg_88 = right_7;
    index_6 = arg_87;
    node_14 = arg_88;
    goto tailrec_197;
if_next_207:;
    if_51 = if_52;
    goto if_next_204;
if_next_204:;
    return if_51;
}

int segTreeGet_1(int index_5, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 self_8) {
    struct IntIntIntObjectUnitTuple5 call_169 = segTreeToRoot_1(self_8);
    int call_170 = go_28(index_5, call_169);
    return call_170;
}

struct String segTreeGet_2(int index_5, struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4StringIntIntObjectUnitTuple5UnitTuple3 self_8) {
    struct StringIntIntObjectUnitTuple5 call_171 = segTreeToRoot_2(self_8);
    struct String call_172 = go_39(index_5, call_171);
    return call_172;
}

int go_29(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_12, struct IntIntTuple2 e_, struct IntIntTuple2 q_, struct IntIntIntObjectUnitTuple5 node_15) {
    bool call_173 = intervalIsDisjoint_(q_, e_);
    int if_53;
    if (call_173) {
        goto then_211;
    } else {
        goto else_212;
    }
then_211:;
    int call_174 = segItemTypeToEmptyItem_1(itemTy_12);
    if_53 = call_174;
    goto if_next_210;
else_212:;
    bool call_175 = intervalCovers_(q_, e_);
    int if_54;
    if (call_175) {
        goto then_214;
    } else {
        goto else_215;
    }
then_214:;
    int call_176 = segNodeToItem_1(node_15);
    if_54 = call_176;
    goto if_next_213;
else_215:;
    bool call_177 = segNodeIsEmpty_1(node_15);
    milone_assert((!(call_177)), 304, 6);
    struct IntIntIntObjectUnitTuple5IntIntIntObjectUnitTuple5Tuple2 call_178 = segNodeToChildren_1(node_15);
    struct IntIntIntObjectUnitTuple5 leftNode_ = call_178.t0;
    struct IntIntIntObjectUnitTuple5 rightNode_ = call_178.t1;
    int el_ = e_.t0;
    int er_ = e_.t1;
    int call_179 = segNodeToLength_1(leftNode_);
    int m_1 = (el_ + call_179);
    struct IntIntTuple2 tuple_25 = (struct IntIntTuple2){.t0 = el_, .t1 = m_1};
    int call_180 = go_29(itemTy_12, tuple_25, q_, leftNode_);
    int vl_ = call_180;
    struct IntIntTuple2 tuple_26 = (struct IntIntTuple2){.t0 = m_1, .t1 = er_};
    int call_181 = go_29(itemTy_12, tuple_26, q_, rightNode_);
    int vr_ = call_181;
    struct IntIntIntFun2 call_182 = segItemTypeToAppend_1(itemTy_12);
    int app_10 = call_182.fun(call_182.env, vl_, vr_);
    if_54 = app_10;
    goto if_next_213;
if_next_213:;
    if_53 = if_54;
    goto if_next_210;
if_next_210:;
    return if_53;
}

int segTreeSum_1(int ql_, int qr_, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 self_9) {
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_12 = self_9.t0;
    struct IntIntIntObjectUnitTuple5 root_ = self_9.t1;
    int call_183 = segNodeToLength_1(root_);
    int len_16 = call_183;
    struct IntIntTuple2 tuple_27 = (struct IntIntTuple2){.t0 = ql_, .t1 = qr_};
    struct IntIntTuple2 q_1 = tuple_27;
    struct IntIntTuple2 tuple_28 = (struct IntIntTuple2){.t0 = 0, .t1 = len_16};
    bool call_184 = intervalIsDisjoint_(q_1, tuple_28);
    int if_55;
    if (call_184) {
        goto then_217;
    } else {
        goto else_218;
    }
then_217:;
    int call_185 = segItemTypeToEmptyItem_1(itemTy_12);
    if_55 = call_185;
    goto if_next_216;
else_218:;
    struct IntIntTuple2 tuple_29 = (struct IntIntTuple2){.t0 = 0, .t1 = len_16};
    struct IntIntTuple2 e_1 = tuple_29;
    int call_186 = go_29(itemTy_12, e_1, q_1, root_);
    if_55 = call_186;
    goto if_next_216;
if_next_216:;
    return if_55;
}

struct IntIntIntObjectUnitTuple5 go_30(int newItem_, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_13, int index_8, struct IntIntIntObjectUnitTuple5 node_16) {
    int len_17 = node_16.t1;
    int height_2 = node_16.t2;
    void const* children_1 = node_16.t3;
    bool if_56;
    if ((index_8 < 0)) {
        goto then_220;
    } else {
        goto else_221;
    }
then_220:;
    if_56 = true;
    goto if_next_219;
else_221:;
    if_56 = (index_8 >= len_17);
    goto if_next_219;
if_next_219:;
    char if_57;
    if (if_56) {
        goto then_223;
    } else {
        goto else_224;
    }
then_223:;
    printf("ERROR: segNodeSet out of range (index = %d, len = %d)\n", index_8, len_17);
    exit(1);
else_224:;
    if_57 = 0;
    goto if_next_222;
if_next_222:;
    milone_assert((len_17 != 0), 336, 4);
    struct IntIntIntObjectUnitTuple5 if_58;
    if ((len_17 == 1)) {
        goto then_226;
    } else {
        goto else_227;
    }
then_226:;
    struct IntIntIntObjectUnitTuple5 tuple_30 = (struct IntIntIntObjectUnitTuple5){.t0 = newItem_, .t1 = len_17, .t2 = height_2, .t3 = children_1, .t4 = 0};
    if_58 = tuple_30;
    goto if_next_225;
else_227:;
    struct IntIntIntObjectUnitTuple5IntIntIntObjectUnitTuple5Tuple2 call_187 = segNodeToChildren_1(node_16);
    struct IntIntIntObjectUnitTuple5 left_8 = call_187.t0;
    struct IntIntIntObjectUnitTuple5 right_8 = call_187.t1;
    int call_188 = segNodeToLength_1(left_8);
    int leftLen_2 = call_188;
    struct IntIntIntObjectUnitTuple5 if_59;
    if ((index_8 < leftLen_2)) {
        goto then_229;
    } else {
        goto else_230;
    }
then_229:;
    struct IntIntIntObjectUnitTuple5 call_189 = go_30(newItem_, itemTy_13, index_8, left_8);
    struct IntIntIntObjectUnitTuple5 call_190 = segNodeWithLeft_1(itemTy_13, call_189, node_16);
    if_59 = call_190;
    goto if_next_228;
else_230:;
    struct IntIntIntObjectUnitTuple5 call_191 = go_30(newItem_, itemTy_13, (index_8 - leftLen_2), right_8);
    struct IntIntIntObjectUnitTuple5 call_192 = segNodeWithRight_1(itemTy_13, call_191, node_16);
    if_59 = call_192;
    goto if_next_228;
if_next_228:;
    if_58 = if_59;
    goto if_next_225;
if_next_225:;
    return if_58;
}

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 segTreeSet_1(int index_7, int newItem_, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 self_10) {
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_13 = self_10.t0;
    struct IntIntIntObjectUnitTuple5 root_1 = self_10.t1;
    struct IntIntIntObjectUnitTuple5 call_193 = go_30(newItem_, itemTy_13, index_7, root_1);
    struct IntIntIntObjectUnitTuple5 root_2 = call_193;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 tuple_31 = (struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3){.t0 = itemTy_13, .t1 = root_2, .t2 = 0};
    return tuple_31;
}

struct IntIntIntObjectUnitTuple5 go_31(int newItem_1, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_14, int index_10, struct IntIntIntObjectUnitTuple5 node_17) {
    int oldItem_ = node_17.t0;
    int len_18 = node_17.t1;
    milone_assert((len_18 >= index_10), 360, 4);
    struct IntIntIntObjectUnitTuple5 if_60;
    if ((len_18 == 0)) {
        goto then_232;
    } else {
        goto else_233;
    }
then_232:;
    struct IntIntIntObjectUnitTuple5 call_194 = segNodeNewLeaf_1(itemTy_14, newItem_1);
    if_60 = call_194;
    goto if_next_231;
else_233:;
    struct IntIntIntObjectUnitTuple5 if_61;
    if ((len_18 == 1)) {
        goto then_235;
    } else {
        goto else_239;
    }
then_235:;
    struct IntIntIntObjectUnitTuple5 call_195 = segNodeNewLeaf_1(itemTy_14, oldItem_);
    struct IntIntIntObjectUnitTuple5 oldLeaf_ = call_195;
    struct IntIntIntObjectUnitTuple5 call_196 = segNodeNewLeaf_1(itemTy_14, newItem_1);
    struct IntIntIntObjectUnitTuple5 newLeaf_ = call_196;
    struct IntIntIntObjectUnitTuple5IntIntIntObjectUnitTuple5Tuple2 if_62;
    if ((index_10 == 0)) {
        goto then_237;
    } else {
        goto else_238;
    }
then_237:;
    struct IntIntIntObjectUnitTuple5IntIntIntObjectUnitTuple5Tuple2 tuple_32 = (struct IntIntIntObjectUnitTuple5IntIntIntObjectUnitTuple5Tuple2){.t0 = newLeaf_, .t1 = oldLeaf_};
    if_62 = tuple_32;
    goto if_next_236;
else_238:;
    milone_assert((index_10 == 1), 372, 10);
    struct IntIntIntObjectUnitTuple5IntIntIntObjectUnitTuple5Tuple2 tuple_33 = (struct IntIntIntObjectUnitTuple5IntIntIntObjectUnitTuple5Tuple2){.t0 = oldLeaf_, .t1 = newLeaf_};
    if_62 = tuple_33;
    goto if_next_236;
if_next_236:;
    struct IntIntIntObjectUnitTuple5 left_9 = if_62.t0;
    struct IntIntIntObjectUnitTuple5 right_9 = if_62.t1;
    struct IntIntIntObjectUnitTuple5 call_197 = segNodeNew_1(itemTy_14, left_9, right_9);
    if_61 = call_197;
    goto if_next_234;
else_239:;
    struct IntIntIntObjectUnitTuple5IntIntIntObjectUnitTuple5Tuple2 call_198 = segNodeToChildren_1(node_17);
    struct IntIntIntObjectUnitTuple5 left_10 = call_198.t0;
    struct IntIntIntObjectUnitTuple5 right_10 = call_198.t1;
    int call_199 = segNodeToLength_1(left_10);
    int leftLen_3 = call_199;
    int call_200 = segNodeToLength_1(right_10);
    int rightLen_1 = call_200;
    milone_assert(((leftLen_3 + rightLen_1) == len_18), 381, 6);
    struct IntIntIntObjectUnitTuple5IntIntIntObjectUnitTuple5Tuple2 if_63;
    if ((index_10 < leftLen_3)) {
        goto then_241;
    } else {
        goto else_242;
    }
then_241:;
    struct IntIntIntObjectUnitTuple5 call_201 = go_31(newItem_1, itemTy_14, index_10, left_10);
    struct IntIntIntObjectUnitTuple5 left_12 = call_201;
    int call_202 = segNodeToLength_1(left_12);
    milone_assert((call_202 == (leftLen_3 + 1)), 386, 10);
    struct IntIntIntObjectUnitTuple5IntIntIntObjectUnitTuple5Tuple2 tuple_34 = (struct IntIntIntObjectUnitTuple5IntIntIntObjectUnitTuple5Tuple2){.t0 = left_12, .t1 = right_10};
    if_63 = tuple_34;
    goto if_next_240;
else_242:;
    struct IntIntIntObjectUnitTuple5 call_203 = go_31(newItem_1, itemTy_14, (index_10 - leftLen_3), right_10);
    struct IntIntIntObjectUnitTuple5 right_12 = call_203;
    int call_204 = segNodeToLength_1(right_12);
    milone_assert((call_204 == (rightLen_1 + 1)), 390, 10);
    struct IntIntIntObjectUnitTuple5IntIntIntObjectUnitTuple5Tuple2 tuple_35 = (struct IntIntIntObjectUnitTuple5IntIntIntObjectUnitTuple5Tuple2){.t0 = left_10, .t1 = right_12};
    if_63 = tuple_35;
    goto if_next_240;
if_next_240:;
    struct IntIntIntObjectUnitTuple5 left_11 = if_63.t0;
    struct IntIntIntObjectUnitTuple5 right_11 = if_63.t1;
    struct IntIntIntObjectUnitTuple5 call_205 = segNodeNew_1(itemTy_14, left_11, right_11);
    struct IntIntIntObjectUnitTuple5 call_206 = segNodeMakeBalanced_1(itemTy_14, call_205);
    if_61 = call_206;
    goto if_next_234;
if_next_234:;
    if_60 = if_61;
    goto if_next_231;
if_next_231:;
    return if_60;
}

struct StringIntIntObjectUnitTuple5 go_35(struct String newItem_1, struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_14, int index_10, struct StringIntIntObjectUnitTuple5 node_17) {
    struct String oldItem_ = node_17.t0;
    int len_18 = node_17.t1;
    milone_assert((len_18 >= index_10), 360, 4);
    struct StringIntIntObjectUnitTuple5 if_64;
    if ((len_18 == 0)) {
        goto then_244;
    } else {
        goto else_245;
    }
then_244:;
    struct StringIntIntObjectUnitTuple5 call_207 = segNodeNewLeaf_2(itemTy_14, newItem_1);
    if_64 = call_207;
    goto if_next_243;
else_245:;
    struct StringIntIntObjectUnitTuple5 if_65;
    if ((len_18 == 1)) {
        goto then_247;
    } else {
        goto else_251;
    }
then_247:;
    struct StringIntIntObjectUnitTuple5 call_208 = segNodeNewLeaf_2(itemTy_14, oldItem_);
    struct StringIntIntObjectUnitTuple5 oldLeaf_ = call_208;
    struct StringIntIntObjectUnitTuple5 call_209 = segNodeNewLeaf_2(itemTy_14, newItem_1);
    struct StringIntIntObjectUnitTuple5 newLeaf_ = call_209;
    struct StringIntIntObjectUnitTuple5StringIntIntObjectUnitTuple5Tuple2 if_66;
    if ((index_10 == 0)) {
        goto then_249;
    } else {
        goto else_250;
    }
then_249:;
    struct StringIntIntObjectUnitTuple5StringIntIntObjectUnitTuple5Tuple2 tuple_36 = (struct StringIntIntObjectUnitTuple5StringIntIntObjectUnitTuple5Tuple2){.t0 = newLeaf_, .t1 = oldLeaf_};
    if_66 = tuple_36;
    goto if_next_248;
else_250:;
    milone_assert((index_10 == 1), 372, 10);
    struct StringIntIntObjectUnitTuple5StringIntIntObjectUnitTuple5Tuple2 tuple_37 = (struct StringIntIntObjectUnitTuple5StringIntIntObjectUnitTuple5Tuple2){.t0 = oldLeaf_, .t1 = newLeaf_};
    if_66 = tuple_37;
    goto if_next_248;
if_next_248:;
    struct StringIntIntObjectUnitTuple5 left_9 = if_66.t0;
    struct StringIntIntObjectUnitTuple5 right_9 = if_66.t1;
    struct StringIntIntObjectUnitTuple5 call_210 = segNodeNew_2(itemTy_14, left_9, right_9);
    if_65 = call_210;
    goto if_next_246;
else_251:;
    struct StringIntIntObjectUnitTuple5StringIntIntObjectUnitTuple5Tuple2 call_211 = segNodeToChildren_2(node_17);
    struct StringIntIntObjectUnitTuple5 left_10 = call_211.t0;
    struct StringIntIntObjectUnitTuple5 right_10 = call_211.t1;
    int call_212 = segNodeToLength_2(left_10);
    int leftLen_3 = call_212;
    int call_213 = segNodeToLength_2(right_10);
    int rightLen_1 = call_213;
    milone_assert(((leftLen_3 + rightLen_1) == len_18), 381, 6);
    struct StringIntIntObjectUnitTuple5StringIntIntObjectUnitTuple5Tuple2 if_67;
    if ((index_10 < leftLen_3)) {
        goto then_253;
    } else {
        goto else_254;
    }
then_253:;
    struct StringIntIntObjectUnitTuple5 call_214 = go_35(newItem_1, itemTy_14, index_10, left_10);
    struct StringIntIntObjectUnitTuple5 left_12 = call_214;
    int call_215 = segNodeToLength_2(left_12);
    milone_assert((call_215 == (leftLen_3 + 1)), 386, 10);
    struct StringIntIntObjectUnitTuple5StringIntIntObjectUnitTuple5Tuple2 tuple_38 = (struct StringIntIntObjectUnitTuple5StringIntIntObjectUnitTuple5Tuple2){.t0 = left_12, .t1 = right_10};
    if_67 = tuple_38;
    goto if_next_252;
else_254:;
    struct StringIntIntObjectUnitTuple5 call_216 = go_35(newItem_1, itemTy_14, (index_10 - leftLen_3), right_10);
    struct StringIntIntObjectUnitTuple5 right_12 = call_216;
    int call_217 = segNodeToLength_2(right_12);
    milone_assert((call_217 == (rightLen_1 + 1)), 390, 10);
    struct StringIntIntObjectUnitTuple5StringIntIntObjectUnitTuple5Tuple2 tuple_39 = (struct StringIntIntObjectUnitTuple5StringIntIntObjectUnitTuple5Tuple2){.t0 = left_10, .t1 = right_12};
    if_67 = tuple_39;
    goto if_next_252;
if_next_252:;
    struct StringIntIntObjectUnitTuple5 left_11 = if_67.t0;
    struct StringIntIntObjectUnitTuple5 right_11 = if_67.t1;
    struct StringIntIntObjectUnitTuple5 call_218 = segNodeNew_2(itemTy_14, left_11, right_11);
    struct StringIntIntObjectUnitTuple5 call_219 = segNodeMakeBalanced_2(itemTy_14, call_218);
    if_65 = call_219;
    goto if_next_246;
if_next_246:;
    if_64 = if_65;
    goto if_next_243;
if_next_243:;
    return if_64;
}

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 segTreeInsert_1(int index_9, int newItem_1, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 self_11) {
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_14 = self_11.t0;
    struct IntIntIntObjectUnitTuple5 root_3 = self_11.t1;
    struct IntIntIntObjectUnitTuple5 call_220 = go_31(newItem_1, itemTy_14, index_9, root_3);
    struct IntIntIntObjectUnitTuple5 root_4 = call_220;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 tuple_40 = (struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3){.t0 = itemTy_14, .t1 = root_4, .t2 = 0};
    return tuple_40;
}

struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4StringIntIntObjectUnitTuple5UnitTuple3 segTreeInsert_2(int index_9, struct String newItem_1, struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4StringIntIntObjectUnitTuple5UnitTuple3 self_11) {
    struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_14 = self_11.t0;
    struct StringIntIntObjectUnitTuple5 root_3 = self_11.t1;
    struct StringIntIntObjectUnitTuple5 call_221 = go_35(newItem_1, itemTy_14, index_9, root_3);
    struct StringIntIntObjectUnitTuple5 root_4 = call_221;
    struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4StringIntIntObjectUnitTuple5UnitTuple3 tuple_41 = (struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4StringIntIntObjectUnitTuple5UnitTuple3){.t0 = itemTy_14, .t1 = root_4, .t2 = 0};
    return tuple_41;
}

struct IntIntIntObjectUnitTuple5 go_36(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_15, int index_12, struct IntIntIntObjectUnitTuple5 node_18) {
    int len_19 = node_18.t1;
    milone_assert((index_12 < len_19), 405, 4);
    milone_assert((len_19 != 0), 407, 4);
    struct IntIntIntObjectUnitTuple5 if_68;
    if ((len_19 == 1)) {
        goto then_256;
    } else {
        goto else_257;
    }
then_256:;
    struct IntIntIntObjectUnitTuple5 call_222 = segItemTypeToEmptyNode_2(itemTy_15);
    if_68 = call_222;
    goto if_next_255;
else_257:;
    struct IntIntIntObjectUnitTuple5IntIntIntObjectUnitTuple5Tuple2 call_223 = segNodeToChildren_1(node_18);
    struct IntIntIntObjectUnitTuple5 left_13 = call_223.t0;
    struct IntIntIntObjectUnitTuple5 right_13 = call_223.t1;
    int call_224 = segNodeToLength_1(left_13);
    int leftLen_4 = call_224;
    int call_225 = segNodeToLength_1(right_13);
    int rightLen_2 = call_225;
    milone_assert(((leftLen_4 + rightLen_2) == len_19), 416, 6);
    struct IntIntIntObjectUnitTuple5 if_69;
    if ((index_12 < leftLen_4)) {
        goto then_259;
    } else {
        goto else_263;
    }
then_259:;
    struct IntIntIntObjectUnitTuple5 if_70;
    if ((leftLen_4 < 2)) {
        goto then_261;
    } else {
        goto else_262;
    }
then_261:;
    if_70 = right_13;
    goto if_next_260;
else_262:;
    struct IntIntIntObjectUnitTuple5 call_226 = go_36(itemTy_15, index_12, left_13);
    struct IntIntIntObjectUnitTuple5 call_227 = segNodeWithLeft_1(itemTy_15, call_226, node_18);
    if_70 = call_227;
    goto if_next_260;
if_next_260:;
    if_69 = if_70;
    goto if_next_258;
else_263:;
    struct IntIntIntObjectUnitTuple5 if_71;
    if ((rightLen_2 < 2)) {
        goto then_265;
    } else {
        goto else_266;
    }
then_265:;
    if_71 = left_13;
    goto if_next_264;
else_266:;
    struct IntIntIntObjectUnitTuple5 call_228 = go_36(itemTy_15, (index_12 - leftLen_4), right_13);
    struct IntIntIntObjectUnitTuple5 call_229 = segNodeWithRight_1(itemTy_15, call_228, node_18);
    if_71 = call_229;
    goto if_next_264;
if_next_264:;
    if_69 = if_71;
    goto if_next_258;
if_next_258:;
    struct IntIntIntObjectUnitTuple5 node_19 = if_69;
    struct IntIntIntObjectUnitTuple5 call_230 = segNodeMakeBalanced_1(itemTy_15, node_19);
    if_68 = call_230;
    goto if_next_255;
if_next_255:;
    return if_68;
}

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 segTreeRemove_1(int index_11, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 self_12) {
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_15 = self_12.t0;
    struct IntIntIntObjectUnitTuple5 root_5 = self_12.t1;
    struct IntIntIntObjectUnitTuple5 call_231 = go_36(itemTy_15, index_11, root_5);
    struct IntIntIntObjectUnitTuple5 root_6 = call_231;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 tuple_42 = (struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3){.t0 = itemTy_15, .t1 = root_6, .t2 = 0};
    return tuple_42;
}

struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4StringIntIntObjectUnitTuple5UnitTuple3 segTreePush_2(struct String value_4, struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4StringIntIntObjectUnitTuple5UnitTuple3 self_13) {
    int call_232 = segTreeToLength_2(self_13);
    int index_13 = call_232;
    struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4StringIntIntObjectUnitTuple5UnitTuple3 call_233 = segTreeInsert_2(index_13, value_4, self_13);
    return call_233;
}

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 segTreePush_1(int value_4, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 self_13) {
    int call_234 = segTreeToLength_1(self_13);
    int index_13 = call_234;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 call_235 = segTreeInsert_1(index_13, value_4, self_13);
    return call_235;
}

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 segTreePop_1(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 self_14) {
    int call_236 = segTreeToLength_1(self_14);
    int index_14 = (call_236 - 1);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 call_237 = segTreeRemove_1(index_14, self_14);
    return call_237;
}

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 go_32(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 t_2, struct IntList const* xs_22) {
tailrec_267:;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 match_10;
    if ((!((!(xs_22))))) goto next_269;
    match_10 = t_2;
    goto end_match_268;
next_269:;
    if ((!(xs_22))) goto next_270;
    int x_6 = xs_22->head;
    struct IntList const* xs_23 = xs_22->tail;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 call_238 = segTreePush_1(x_6, t_2);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 arg_89 = call_238;
    struct IntList const* arg_90 = xs_23;
    t_2 = arg_89;
    xs_22 = arg_90;
    goto tailrec_267;
next_270:;
    exit(1);
end_match_268:;
    return match_10;
}

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 segTreeOfList_1(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 itemTy_16, struct IntList const* xs_21) {
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 call_239 = segTreeNew_2(itemTy_16);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 call_240 = go_32(call_239, xs_21);
    return call_240;
}

struct IntList const* go_34(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 v_4, int len_20, struct IntList const* acc_3, int i_4) {
tailrec_271:;
    struct IntList const* if_72;
    if ((i_4 == len_20)) {
        goto then_273;
    } else {
        goto else_274;
    }
then_273:;
    struct IntList const* call_241 = listRev_2(acc_3);
    if_72 = call_241;
    goto if_next_272;
else_274:;
    int call_242 = segTreeGet_1(i_4, v_4);
    int x_7 = call_242;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 arg_91 = v_4;
    int arg_92 = len_20;
    struct IntList const* list_21 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_21))) = (struct IntList){.head = x_7, .tail = acc_3};
    struct IntList const* arg_93 = list_21;
    int arg_94 = (i_4 + 1);
    v_4 = arg_91;
    len_20 = arg_92;
    acc_3 = arg_93;
    i_4 = arg_94;
    goto tailrec_271;
if_next_272:;
    return if_72;
}

struct StringList const* go_33(struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4StringIntIntObjectUnitTuple5UnitTuple3 v_4, int len_20, struct StringList const* acc_3, int i_4) {
tailrec_275:;
    struct StringList const* if_73;
    if ((i_4 == len_20)) {
        goto then_277;
    } else {
        goto else_278;
    }
then_277:;
    struct StringList const* call_243 = listRev_1(acc_3);
    if_73 = call_243;
    goto if_next_276;
else_278:;
    struct String call_244 = segTreeGet_2(i_4, v_4);
    struct String x_7 = call_244;
    struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4StringIntIntObjectUnitTuple5UnitTuple3 arg_95 = v_4;
    int arg_96 = len_20;
    struct StringList const* list_22 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_22))) = (struct StringList){.head = x_7, .tail = acc_3};
    struct StringList const* arg_97 = list_22;
    int arg_98 = (i_4 + 1);
    v_4 = arg_95;
    len_20 = arg_96;
    acc_3 = arg_97;
    i_4 = arg_98;
    goto tailrec_275;
if_next_276:;
    return if_73;
}

struct IntList const* segTreeToList_2(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 v_4) {
    int call_245 = segTreeToLength_1(v_4);
    int len_20 = call_245;
    struct IntList const* call_246 = go_34(v_4, len_20, NULL, 0);
    return call_246;
}

struct StringList const* segTreeToList_1(struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4StringIntIntObjectUnitTuple5UnitTuple3 v_4) {
    int call_247 = segTreeToLength_2(v_4);
    int len_20 = call_247;
    struct StringList const* call_248 = go_33(v_4, len_20, NULL, 0);
    return call_248;
}

int intAdd_(int x_8, int y_3) {
    return (x_8 + y_3);
}

int fun_7(void const* env_4, int arg_7, int arg_8) {
    int call_249 = intAdd_(arg_7, arg_8);
    return call_249;
}

struct String strAdd_(struct String x_9, struct String y_4) {
    return str_add(x_9, y_4);
}

struct String fun_8(void const* env_5, struct String arg_9, struct String arg_10) {
    struct String call_250 = strAdd_(arg_9, arg_10);
    return call_250;
}

bool fun_9(void const* env_6, int arg_11, int arg_12) {
    bool call_251 = intEqual_(arg_11, arg_12);
    return call_251;
}

bool fun_10(void const* env_7, int arg_13, int arg_14) {
    bool call_252 = intEqual_(arg_13, arg_14);
    return call_252;
}

bool fun_11(void const* env_8, int arg_15, int arg_16) {
    bool call_253 = intEqual_(arg_15, arg_16);
    return call_253;
}

bool fun_12(void const* env_9, int arg_17, int arg_18) {
    bool call_254 = intEqual_(arg_17, arg_18);
    return call_254;
}

bool fun_13(void const* env_10, int arg_19, int arg_20) {
    bool call_255 = intEqual_(arg_19, arg_20);
    return call_255;
}

char testPushPop_(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 segItemTypeInt_, char arg_99) {
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 call_256 = segTreeNew_2(segItemTypeInt_);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 call_257 = segTreePush_1(1, call_256);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 call_258 = segTreePush_1(2, call_257);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 v_5 = call_258;
    struct IntIntBoolFun2 fun_25 = (struct IntIntBoolFun2){.fun = fun_9, .env = NULL};
    struct IntList const* list_24 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_24))) = (struct IntList){.head = 2, .tail = NULL};
    struct IntList const* list_23 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_23))) = (struct IntList){.head = 1, .tail = list_24};
    struct IntList const* call_259 = segTreeToList_2(v_5);
    bool call_260 = listEqual_2(fun_25, list_23, call_259);
    milone_assert(call_260, 485, 4);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 call_261 = segTreePush_1(3, v_5);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 v_6 = call_261;
    struct IntIntBoolFun2 fun_26 = (struct IntIntBoolFun2){.fun = fun_10, .env = NULL};
    struct IntList const* list_27 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_27))) = (struct IntList){.head = 3, .tail = NULL};
    struct IntList const* list_26 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_26))) = (struct IntList){.head = 2, .tail = list_27};
    struct IntList const* list_25 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_25))) = (struct IntList){.head = 1, .tail = list_26};
    struct IntList const* call_262 = segTreeToList_2(v_6);
    bool call_263 = listEqual_2(fun_26, list_25, call_262);
    milone_assert(call_263, 489, 4);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 call_264 = segTreePop_1(v_6);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 v_7 = call_264;
    struct IntIntBoolFun2 fun_27 = (struct IntIntBoolFun2){.fun = fun_11, .env = NULL};
    struct IntList const* list_29 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_29))) = (struct IntList){.head = 2, .tail = NULL};
    struct IntList const* list_28 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_28))) = (struct IntList){.head = 1, .tail = list_29};
    struct IntList const* call_265 = segTreeToList_2(v_7);
    bool call_266 = listEqual_2(fun_27, list_28, call_265);
    milone_assert(call_266, 494, 4);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 call_267 = segTreePop_1(v_7);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 v_8 = call_267;
    struct IntIntBoolFun2 fun_28 = (struct IntIntBoolFun2){.fun = fun_12, .env = NULL};
    struct IntList const* list_30 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_30))) = (struct IntList){.head = 1, .tail = NULL};
    struct IntList const* call_268 = segTreeToList_2(v_8);
    bool call_269 = listEqual_2(fun_28, list_30, call_268);
    milone_assert(call_269, 497, 4);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 call_270 = segTreePop_1(v_8);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 v_9 = call_270;
    struct IntIntBoolFun2 fun_29 = (struct IntIntBoolFun2){.fun = fun_13, .env = NULL};
    struct IntList const* call_271 = segTreeToList_2(v_9);
    bool call_272 = listEqual_2(fun_29, NULL, call_271);
    milone_assert(call_272, 500, 4);
    return 0;
}

bool fun_14(void const* env_11, int arg_21, int arg_22) {
    bool call_273 = intEqual_(arg_21, arg_22);
    return call_273;
}

bool fun_15(void const* env_12, int arg_23, int arg_24) {
    bool call_274 = intEqual_(arg_23, arg_24);
    return call_274;
}

char testSet_(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 segItemTypeInt_, char arg_100) {
    struct IntList const* list_33 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_33))) = (struct IntList){.head = 3, .tail = NULL};
    struct IntList const* list_32 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_32))) = (struct IntList){.head = 2, .tail = list_33};
    struct IntList const* list_31 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_31))) = (struct IntList){.head = 1, .tail = list_32};
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 call_275 = segTreeOfList_1(segItemTypeInt_, list_31);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 call_276 = segTreeSet_1(1, 22, call_275);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 v_10 = call_276;
    struct IntIntBoolFun2 fun_30 = (struct IntIntBoolFun2){.fun = fun_14, .env = NULL};
    struct IntList const* list_36 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_36))) = (struct IntList){.head = 3, .tail = NULL};
    struct IntList const* list_35 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_35))) = (struct IntList){.head = 22, .tail = list_36};
    struct IntList const* list_34 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_34))) = (struct IntList){.head = 1, .tail = list_35};
    struct IntList const* call_277 = segTreeToList_2(v_10);
    bool call_278 = listEqual_2(fun_30, list_34, call_277);
    milone_assert(call_278, 509, 4);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 call_279 = segTreeSet_1(0, 11, v_10);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 call_280 = segTreeSet_1(2, 33, call_279);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 v_11 = call_280;
    struct IntIntBoolFun2 fun_31 = (struct IntIntBoolFun2){.fun = fun_15, .env = NULL};
    struct IntList const* list_39 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_39))) = (struct IntList){.head = 33, .tail = NULL};
    struct IntList const* list_38 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_38))) = (struct IntList){.head = 22, .tail = list_39};
    struct IntList const* list_37 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_37))) = (struct IntList){.head = 11, .tail = list_38};
    struct IntList const* call_281 = segTreeToList_2(v_11);
    bool call_282 = listEqual_2(fun_31, list_37, call_281);
    milone_assert(call_282, 515, 4);
    return 0;
}

char testSum_(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 segItemTypeInt_, char arg_101) {
    struct IntList const* list_45 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_45))) = (struct IntList){.head = 9, .tail = NULL};
    struct IntList const* list_44 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_44))) = (struct IntList){.head = 5, .tail = list_45};
    struct IntList const* list_43 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_43))) = (struct IntList){.head = 1, .tail = list_44};
    struct IntList const* list_42 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_42))) = (struct IntList){.head = 4, .tail = list_43};
    struct IntList const* list_41 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_41))) = (struct IntList){.head = 1, .tail = list_42};
    struct IntList const* list_40 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_40))) = (struct IntList){.head = 3, .tail = list_41};
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 call_283 = segTreeOfList_1(segItemTypeInt_, list_40);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 v_12 = call_283;
    int call_284 = segTreeSum_1(0, 6, v_12);
    milone_assert((call_284 == (((((3 + 1) + 4) + 1) + 5) + 9)), 525, 4);
    int call_285 = segTreeSum_1(2, 4, v_12);
    milone_assert((call_285 == (4 + 1)), 526, 4);
    return 0;
}

int sum_(int l_1, int r_1, int acc_4, int i_5, struct IntList const* xs_25) {
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
    struct IntList const* xs_26 = xs_25->tail;
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
    int arg_102 = l_1;
    int arg_103 = r_1;
    int arg_104 = acc_5;
    int arg_105 = (i_5 + 1);
    struct IntList const* arg_106 = xs_26;
    l_1 = arg_102;
    r_1 = arg_103;
    acc_4 = arg_104;
    i_5 = arg_105;
    xs_25 = arg_106;
    goto tailrec_279;
next_284:;
    int call_286 = failwith_1((struct String){.str = "NEVER", .len = 5});
    match_11 = call_286;
    goto end_match_283;
next_285:;
end_match_283:;
    if_74 = match_11;
    goto if_next_280;
if_next_280:;
    return if_74;
}

char go_15(struct IntList const* xs_24, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 v_13, int n_1, int l_1, int r_1) {
tailrec_289:;
    char if_76;
    if ((r_1 == n_1)) {
        goto then_291;
    } else {
        goto else_295;
    }
then_291:;
    char if_77;
    if ((l_1 < n_1)) {
        goto then_293;
    } else {
        goto else_294;
    }
then_293:;
    struct IntList const* arg_107 = xs_24;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 arg_108 = v_13;
    int arg_109 = n_1;
    int arg_110 = (l_1 + 1);
    int arg_111 = (l_1 + 1);
    xs_24 = arg_107;
    v_13 = arg_108;
    n_1 = arg_109;
    l_1 = arg_110;
    r_1 = arg_111;
    goto tailrec_289;
else_294:;
    if_77 = 0;
    goto if_next_292;
if_next_292:;
    if_76 = 0;
    goto if_next_290;
else_295:;
    int call_287 = sum_(l_1, r_1, 0, 0, xs_24);
    int expected_ = call_287;
    int call_288 = segTreeSum_1(l_1, r_1, v_13);
    int actual_ = call_288;
    milone_assert((actual_ == expected_), 553, 8);
    struct IntList const* arg_112 = xs_24;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 arg_113 = v_13;
    int arg_114 = n_1;
    int arg_115 = l_1;
    int arg_116 = (r_1 + 1);
    xs_24 = arg_112;
    v_13 = arg_113;
    n_1 = arg_114;
    l_1 = arg_115;
    r_1 = arg_116;
    goto tailrec_289;
if_next_290:;
    return 0;
}

char testSumMore_(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 segItemTypeInt_, char arg_117) {
    struct IntList const* list_51 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_51))) = (struct IntList){.head = 9, .tail = NULL};
    struct IntList const* list_50 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_50))) = (struct IntList){.head = 5, .tail = list_51};
    struct IntList const* list_49 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_49))) = (struct IntList){.head = 1, .tail = list_50};
    struct IntList const* list_48 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_48))) = (struct IntList){.head = 4, .tail = list_49};
    struct IntList const* list_47 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_47))) = (struct IntList){.head = 1, .tail = list_48};
    struct IntList const* list_46 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_46))) = (struct IntList){.head = 3, .tail = list_47};
    struct IntList const* xs_24 = list_46;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 call_289 = segTreeOfList_1(segItemTypeInt_, xs_24);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 v_13 = call_289;
    int call_290 = listLength_1(xs_24);
    int n_1 = call_290;
    char call_291 = go_15(xs_24, v_13, n_1, 0, 0);
    return 0;
}

char testBalance_(struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 segItemTypeInt_, char arg_118) {
    struct IntList const* call_292 = listReplicate_1(1, 1000);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 call_293 = segTreeOfList_1(segItemTypeInt_, call_292);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 v_14 = call_293;
    int call_294 = segTreeToHeight_1(v_14);
    milone_assert((call_294 < 100), 564, 4);
    return 0;
}

bool fun_16(void const* env_13, struct String arg_25, struct String arg_26) {
    bool call_295 = strEqual_(arg_25, arg_26);
    return call_295;
}

char testPolymorphic_(struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4 segItemTypeStr_, char arg_119) {
    struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4StringIntIntObjectUnitTuple5UnitTuple3 call_296 = segTreeNew_1(segItemTypeStr_);
    struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4StringIntIntObjectUnitTuple5UnitTuple3 call_297 = segTreePush_2((struct String){.str = "a", .len = 1}, call_296);
    struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4StringIntIntObjectUnitTuple5UnitTuple3 call_298 = segTreePush_2((struct String){.str = "b", .len = 1}, call_297);
    struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4StringIntIntObjectUnitTuple5UnitTuple3 v_15 = call_298;
    struct StringStringBoolFun2 fun_32 = (struct StringStringBoolFun2){.fun = fun_16, .env = NULL};
    struct StringList const* list_53 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_53))) = (struct StringList){.head = (struct String){.str = "b", .len = 1}, .tail = NULL};
    struct StringList const* list_52 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_52))) = (struct StringList){.head = (struct String){.str = "a", .len = 1}, .tail = list_53};
    struct StringList const* call_299 = segTreeToList_1(v_15);
    bool call_300 = listEqual_1(fun_32, list_52, call_299);
    milone_assert(call_300, 574, 4);
    return 0;
}

char segTreeTest_(char arg_120) {
    struct IntIntIntFun2 fun_33 = (struct IntIntIntFun2){.fun = fun_7, .env = NULL};
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 call_301 = segItemTypeNew_1(0, fun_33);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 segItemTypeInt_ = call_301;
    struct StringStringStringFun2 fun_34 = (struct StringStringStringFun2){.fun = fun_8, .env = NULL};
    struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4 call_302 = segItemTypeNew_2((struct String){.str = "", .len = 0}, fun_34);
    struct StringStringStringFun2StringIntIntObjectUnitTuple5ObjectUnitTuple4 segItemTypeStr_ = call_302;
    char call_303 = testPushPop_(segItemTypeInt_, 0);
    char call_304 = testSet_(segItemTypeInt_, 0);
    char call_305 = testSum_(segItemTypeInt_, 0);
    char call_306 = testSumMore_(segItemTypeInt_, 0);
    char call_307 = testBalance_(segItemTypeInt_, 0);
    char call_308 = testPolymorphic_(segItemTypeStr_, 0);
    return 0;
}

int fun_22(int arg_121, int arg_122) {
    return 0;
}

int fun_17(void const* env_14, int arg_27, int arg_28) {
    int call_309 = fun_22(arg_27, arg_28);
    return call_309;
}

int fun_18(void const* env_15, int arg_29, int arg_30) {
    int call_310 = intMax_(arg_29, arg_30);
    return call_310;
}

int fun_19(void const* env_16, int arg_31, int arg_32) {
    int call_311 = intMin_(arg_31, arg_32);
    return call_311;
}

struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 go_19(int n_2, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 perm_2, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 pos_1, int i_6) {
tailrec_296:;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 if_78;
    if ((i_6 == (n_2 + 2))) {
        goto then_298;
    } else {
        goto else_299;
    }
then_298:;
    if_78 = pos_1;
    goto if_next_297;
else_299:;
    int call_312 = segTreeGet_1(i_6, perm_2);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 call_313 = segTreeSet_1(call_312, i_6, pos_1);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 pos_2 = call_313;
    int arg_123 = n_2;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 arg_124 = perm_2;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 arg_125 = pos_2;
    int arg_126 = (i_6 + 1);
    n_2 = arg_123;
    perm_2 = arg_124;
    pos_1 = arg_125;
    i_6 = arg_126;
    goto tailrec_296;
if_next_297:;
    return if_78;
}

int go_20(int n_2, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 pos_, int sum_1, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 prev_1, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 next_1, int p_) {
tailrec_300:;
    int if_79;
    if ((p_ < 1)) {
        goto then_302;
    } else {
        goto else_303;
    }
then_302:;
    if_79 = sum_1;
    goto if_next_301;
else_303:;
    int call_314 = segTreeGet_1(p_, pos_);
    int i_7 = call_314;
    int call_315 = segTreeSum_1(0, i_7, prev_1);
    int x_11 = call_315;
    int call_316 = segTreeSum_1(0, x_11, prev_1);
    int w_ = call_316;
    bool if_80;
    if ((x_11 >= w_)) {
        goto then_305;
    } else {
        goto else_306;
    }
then_305:;
    if_80 = (x_11 < i_7);
    goto if_next_304;
else_306:;
    if_80 = false;
    goto if_next_304;
if_next_304:;
    milone_assert(if_80, 58, 6);
    int call_317 = segTreeSum_1((i_7 + 1), (n_2 + 2), next_1);
    int y_5 = call_317;
    int call_318 = segTreeSum_1((y_5 + 1), (n_2 + 2), next_1);
    int z_ = call_318;
    bool if_81;
    if ((i_7 < y_5)) {
        goto then_308;
    } else {
        goto else_309;
    }
then_308:;
    if_81 = (z_ >= y_5);
    goto if_next_307;
else_309:;
    if_81 = false;
    goto if_next_307;
if_next_307:;
    milone_assert(if_81, 62, 6);
    int count_ = (((x_11 - w_) * (y_5 - i_7)) + ((i_7 - x_11) * (z_ - y_5)));
    int sum_2 = (sum_1 + (count_ * p_));
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 call_319 = segTreeSet_1(i_7, i_7, prev_1);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 prev_2 = call_319;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 call_320 = segTreeSet_1(i_7, i_7, next_1);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 next_2 = call_320;
    int arg_127 = n_2;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 arg_128 = pos_;
    int arg_129 = sum_2;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 arg_130 = prev_2;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 arg_131 = next_2;
    int arg_132 = (p_ - 1);
    n_2 = arg_127;
    pos_ = arg_128;
    sum_1 = arg_129;
    prev_1 = arg_130;
    next_1 = arg_131;
    p_ = arg_132;
    goto tailrec_300;
if_next_301:;
    return if_79;
}

int abc140eSolve_(int n_2, struct IntList const* perm_) {
    struct IntIntIntFun2 fun_35 = (struct IntIntIntFun2){.fun = fun_17, .env = NULL};
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 call_321 = segItemTypeNew_1(0, fun_35);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 segItemTypeInt_1 = call_321;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 call_322 = segTreeOfList_1(segItemTypeInt_1, perm_);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 perm_1 = call_322;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 call_323 = segTreeInsert_1(0, (n_2 + 1), perm_1);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 call_324 = segTreePush_1((n_2 + 2), call_323);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 perm_2 = call_324;
    int call_325 = segTreeToLength_1(perm_2);
    milone_assert((call_325 == (n_2 + 2)), 22, 2);
    struct IntIntIntFun2 fun_36 = (struct IntIntIntFun2){.fun = fun_18, .env = NULL};
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 call_326 = segItemTypeNew_1(0, fun_36);
    struct IntList const* call_327 = listReplicate_1(0, (n_2 + 2));
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 call_328 = segTreeOfList_1(call_326, call_327);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 prev_ = call_328;
    struct IntIntIntFun2 fun_37 = (struct IntIntIntFun2){.fun = fun_19, .env = NULL};
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 call_329 = segItemTypeNew_1((n_2 + 1), fun_37);
    struct IntList const* call_330 = listReplicate_1((n_2 + 1), (n_2 + 2));
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 call_331 = segTreeOfList_1(call_329, call_330);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 next_ = call_331;
    struct IntList const* call_332 = listReplicate_1(0, (n_2 + 3));
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 call_333 = segTreeOfList_1(segItemTypeInt_1, call_332);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 pos_3 = call_333;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 call_334 = go_19(n_2, perm_2, pos_3, 0);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 pos_ = call_334;
    int call_335 = go_20(n_2, pos_, 0, prev_, next_, n_2);
    return call_335;
}

bool solve_(struct IntList const* p_1, int expected_1) {
    int call_336 = listLength_1(p_1);
    int n_3 = call_336;
    int call_337 = abc140eSolve_(n_3, p_1);
    int actual_1 = call_337;
    bool if_82;
    if ((actual_1 == expected_1)) {
        goto then_311;
    } else {
        goto else_312;
    }
then_311:;
    if_82 = true;
    goto if_next_310;
else_312:;
    printf("actual=%d expected=%d\n", actual_1, expected_1);
    if_82 = false;
    goto if_next_310;
if_next_310:;
    return if_82;
}

char abc140eTest_(char arg_133) {
    struct IntList const* list_56 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_56))) = (struct IntList){.head = 1, .tail = NULL};
    struct IntList const* list_55 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_55))) = (struct IntList){.head = 3, .tail = list_56};
    struct IntList const* list_54 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_54))) = (struct IntList){.head = 2, .tail = list_55};
    bool call_338 = solve_(list_54, 5);
    milone_assert(call_338, 88, 2);
    struct IntList const* list_61 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_61))) = (struct IntList){.head = 5, .tail = NULL};
    struct IntList const* list_60 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_60))) = (struct IntList){.head = 4, .tail = list_61};
    struct IntList const* list_59 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_59))) = (struct IntList){.head = 3, .tail = list_60};
    struct IntList const* list_58 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_58))) = (struct IntList){.head = 2, .tail = list_59};
    struct IntList const* list_57 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_57))) = (struct IntList){.head = 1, .tail = list_58};
    bool call_339 = solve_(list_57, 30);
    milone_assert(call_339, 89, 2);
    struct IntList const* list_69 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_69))) = (struct IntList){.head = 1, .tail = NULL};
    struct IntList const* list_68 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_68))) = (struct IntList){.head = 6, .tail = list_69};
    struct IntList const* list_67 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_67))) = (struct IntList){.head = 5, .tail = list_68};
    struct IntList const* list_66 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_66))) = (struct IntList){.head = 4, .tail = list_67};
    struct IntList const* list_65 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_65))) = (struct IntList){.head = 3, .tail = list_66};
    struct IntList const* list_64 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_64))) = (struct IntList){.head = 7, .tail = list_65};
    struct IntList const* list_63 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_63))) = (struct IntList){.head = 2, .tail = list_64};
    struct IntList const* list_62 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_62))) = (struct IntList){.head = 8, .tail = list_63};
    bool call_340 = solve_(list_62, 136);
    milone_assert(call_340, 90, 2);
    return 0;
}

char abc140eMain_(char arg_134) {
    int call_341 = scanInt_(0);
    int n_4 = call_341;
    struct IntList const* call_342 = scanIntList_(n_4);
    struct IntList const* p_2 = call_342;
    int call_343 = abc140eSolve_(n_4, p_2);
    int m_2 = call_343;
    printf("%d\n", m_2);
    return 0;
}

int fun_23(int arg_135, int arg_136) {
    return 0;
}

int fun_20(void const* env_17, int arg_33, int arg_34) {
    int call_344 = fun_23(arg_33, arg_34);
    return call_344;
}

int go_18(int n_5, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 a_1, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 b_1, struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 c_1, int sum_3, int i_8) {
tailrec_313:;
    int if_83;
    if ((i_8 == n_5)) {
        goto then_315;
    } else {
        goto else_316;
    }
then_315:;
    if_83 = sum_3;
    goto if_next_314;
else_316:;
    int call_345 = segTreeGet_1(i_8, a_1);
    int ai_ = call_345;
    int call_346 = segTreeGet_1((ai_ - 1), b_1);
    int eat_ = call_346;
    bool if_84;
    if (((i_8 + 1) < n_5)) {
        goto then_318;
    } else {
        goto else_319;
    }
then_318:;
    int call_347 = segTreeGet_1((i_8 + 1), a_1);
    if_84 = (call_347 == (ai_ + 1));
    goto if_next_317;
else_319:;
    if_84 = false;
    goto if_next_317;
if_next_317:;
    int if_85;
    if (if_84) {
        goto then_321;
    } else {
        goto else_322;
    }
then_321:;
    int call_348 = segTreeGet_1((ai_ - 1), c_1);
    if_85 = call_348;
    goto if_next_320;
else_322:;
    if_85 = 0;
    goto if_next_320;
if_next_320:;
    int bonus_ = if_85;
    int arg_137 = n_5;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 arg_138 = a_1;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 arg_139 = b_1;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 arg_140 = c_1;
    int arg_141 = ((sum_3 + eat_) + bonus_);
    int arg_142 = (i_8 + 1);
    n_5 = arg_137;
    a_1 = arg_138;
    b_1 = arg_139;
    c_1 = arg_140;
    sum_3 = arg_141;
    i_8 = arg_142;
    goto tailrec_313;
if_next_314:;
    return if_83;
}

int abc140bSolve_(int n_5, struct IntList const* a_, struct IntList const* b_, struct IntList const* c_) {
    struct IntIntIntFun2 fun_38 = (struct IntIntIntFun2){.fun = fun_20, .env = NULL};
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 call_349 = segItemTypeNew_1(0, fun_38);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4 segItemTypeInt_2 = call_349;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 call_350 = segTreeOfList_1(segItemTypeInt_2, a_);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 a_1 = call_350;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 call_351 = segTreeOfList_1(segItemTypeInt_2, b_);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 b_1 = call_351;
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 call_352 = segTreeOfList_1(segItemTypeInt_2, c_);
    struct IntIntIntFun2IntIntIntObjectUnitTuple5ObjectUnitTuple4IntIntIntObjectUnitTuple5UnitTuple3 c_1 = call_352;
    int call_353 = go_18(n_5, a_1, b_1, c_1, 0, 0);
    return call_353;
}

int f_(struct IntList const* a_2, struct IntList const* b_2, struct IntList const* c_2) {
    int call_354 = listLength_1(a_2);
    int n_6 = call_354;
    int call_355 = listLength_1(b_2);
    milone_assert((call_355 == n_6), 32, 4);
    int call_356 = listLength_1(c_2);
    milone_assert((call_356 == (n_6 - 1)), 33, 4);
    int call_357 = abc140bSolve_(n_6, a_2, b_2, c_2);
    return call_357;
}

bool case1_(char arg_143) {
    struct IntList const* list_72 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_72))) = (struct IntList){.head = 2, .tail = NULL};
    struct IntList const* list_71 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_71))) = (struct IntList){.head = 1, .tail = list_72};
    struct IntList const* list_70 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_70))) = (struct IntList){.head = 3, .tail = list_71};
    struct IntList const* a_3 = list_70;
    struct IntList const* list_75 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_75))) = (struct IntList){.head = 4, .tail = NULL};
    struct IntList const* list_74 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_74))) = (struct IntList){.head = 5, .tail = list_75};
    struct IntList const* list_73 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_73))) = (struct IntList){.head = 2, .tail = list_74};
    struct IntList const* b_3 = list_73;
    struct IntList const* list_77 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_77))) = (struct IntList){.head = 6, .tail = NULL};
    struct IntList const* list_76 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_76))) = (struct IntList){.head = 3, .tail = list_77};
    struct IntList const* c_3 = list_76;
    int call_358 = f_(a_3, b_3, c_3);
    return (call_358 == 14);
}

bool case2_(char arg_144) {
    struct IntList const* list_81 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_81))) = (struct IntList){.head = 1, .tail = NULL};
    struct IntList const* list_80 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_80))) = (struct IntList){.head = 4, .tail = list_81};
    struct IntList const* list_79 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_79))) = (struct IntList){.head = 3, .tail = list_80};
    struct IntList const* list_78 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_78))) = (struct IntList){.head = 2, .tail = list_79};
    struct IntList const* a_4 = list_78;
    struct IntList const* list_85 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_85))) = (struct IntList){.head = 24, .tail = NULL};
    struct IntList const* list_84 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_84))) = (struct IntList){.head = 8, .tail = list_85};
    struct IntList const* list_83 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_83))) = (struct IntList){.head = 5, .tail = list_84};
    struct IntList const* list_82 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_82))) = (struct IntList){.head = 13, .tail = list_83};
    struct IntList const* b_4 = list_82;
    struct IntList const* list_88 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_88))) = (struct IntList){.head = 15, .tail = NULL};
    struct IntList const* list_87 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_87))) = (struct IntList){.head = 9, .tail = list_88};
    struct IntList const* list_86 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_86))) = (struct IntList){.head = 45, .tail = list_87};
    struct IntList const* c_4 = list_86;
    int call_359 = f_(a_4, b_4, c_4);
    return (call_359 == 74);
}

bool case3_(char arg_145) {
    struct IntList const* list_90 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_90))) = (struct IntList){.head = 2, .tail = NULL};
    struct IntList const* list_89 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_89))) = (struct IntList){.head = 1, .tail = list_90};
    struct IntList const* a_5 = list_89;
    struct IntList const* list_92 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_92))) = (struct IntList){.head = 50, .tail = NULL};
    struct IntList const* list_91 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_91))) = (struct IntList){.head = 50, .tail = list_92};
    struct IntList const* b_5 = list_91;
    struct IntList const* list_93 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_93))) = (struct IntList){.head = 50, .tail = NULL};
    struct IntList const* c_5 = list_93;
    int call_360 = f_(a_5, b_5, c_5);
    return (call_360 == 150);
}

char abc140bTest_(char arg_146) {
    bool call_361 = case1_(0);
    milone_assert(call_361, 42, 2);
    bool call_362 = case2_(0);
    milone_assert(call_362, 50, 2);
    bool call_363 = case3_(0);
    milone_assert(call_363, 58, 2);
    return 0;
}

char abc140bMain_(char arg_147) {
    int call_364 = scanInt_(0);
    int n_7 = call_364;
    struct IntList const* call_365 = scanIntList_(n_7);
    struct IntList const* a_6 = call_365;
    struct IntList const* call_366 = scanIntList_(n_7);
    struct IntList const* b_6 = call_366;
    struct IntList const* call_367 = scanIntList_((n_7 - 1));
    struct IntList const* c_6 = call_367;
    int call_368 = abc140bSolve_(n_7, a_6, b_6, c_6);
    int m_3 = call_368;
    printf("%d\n", m_3);
    return 0;
}

int abc140aSolve_(int n_8) {
    return ((n_8 * n_8) * n_8);
}

char abc140aTest_(char arg_148) {
    int call_369 = abc140aSolve_(2);
    milone_assert((call_369 == 8), 8, 2);
    int call_370 = abc140aSolve_(1);
    milone_assert((call_370 == 1), 9, 2);
    return 0;
}

char abc140aMain_(char arg_149) {
    int call_371 = scanInt_(0);
    int n_9 = call_371;
    int call_372 = abc140aSolve_(n_9);
    int m_4 = call_372;
    printf("%d\n", m_4);
    return 0;
}

int milone_main() {
    unitObj_ = NULL;
    struct IntVoidMutPtrFun1 fun_39 = (struct IntVoidMutPtrFun1){.fun = fun_4, .env = NULL};
    struct VoidMutPtrIntIntFun2 fun_40 = (struct VoidMutPtrIntIntFun2){.fun = fun_5, .env = NULL};
    struct VoidMutPtrIntIntUnitFun3 fun_41 = (struct VoidMutPtrIntIntUnitFun3){.fun = fun_6, .env = NULL};
    struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6 tuple_43 = (struct IntIntIntVoidMutPtrFun1VoidMutPtrIntIntFun2VoidMutPtrIntIntUnitFun3UnitTuple6){.t0 = 0, .t1 = 4, .t2 = fun_39, .t3 = fun_40, .t4 = fun_41, .t5 = 0};
    typeInt_ = tuple_43;
    char call_373 = vectorTest_(0);
    char call_374 = segTreeTest_(0);
    char call_375 = abc140aTest_(0);
    char call_376 = abc140bTest_(0);
    char call_377 = abc140eTest_(0);
    return 0;
}
