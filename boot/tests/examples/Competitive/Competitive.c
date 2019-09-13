#include "milone.h"

int scanInt_(int arg_35);

void* rawIntArrayNew_(int len_);

int rawIntArrayGet_(void* array_, int index_);

void* rawIntArraySet_(void* array_1, int index_1, int value_);

void* rawMemoryCopy_(void* dest_, void* src_, int size_);

int ignore_1(void* __1);

struct StringList;

int listIsEmpty_1(struct StringList* xs_);

struct StringStringStringFun2;

struct StringStringStringFun2List;

int listIsEmpty_5(struct StringStringStringFun2List* xs_);

struct IntList;

int listIsEmpty_4(struct IntList* xs_);

struct IntIntIntFun2;

struct IntIntIntFun2List;

int listIsEmpty_3(struct IntIntIntFun2List* xs_);

enum SegNodeTag_Tag;

struct SegNodeTag_;

struct IntIntIntObjectSegNodeTag_Tuple5;

struct IntIntIntObjectSegNodeTag_Tuple5List;

int listIsEmpty_2(struct IntIntIntObjectSegNodeTag_Tuple5List* xs_);

struct StringIntIntObjectSegNodeTag_Tuple5;

struct StringIntIntObjectSegNodeTag_Tuple5List;

int listIsEmpty_6(struct StringIntIntObjectSegNodeTag_Tuple5List* xs_);

int go_34(int len_1, struct StringList* xs_2);

int go_33(int len_1, struct IntList* xs_2);

int listLength_2(struct StringList* xs_1);

int listLength_1(struct IntList* xs_1);

struct IntList* go_39(struct IntList* acc_, struct IntList* xs_5);

struct StringList* go_38(struct StringList* acc_, struct StringList* xs_5);

struct IntList* listRev_2(struct IntList* xs_4);

struct StringList* listRev_1(struct StringList* xs_4);

struct IntIntBoolFun2;

struct IntIntBoolFun2Tuple1;

struct IntListIntListTuple2;

int go_32(struct IntIntBoolFun2Tuple1 arg_36, struct IntList* xs_8, struct IntList* ys_1);

struct StringStringBoolFun2;

struct StringStringBoolFun2Tuple1;

struct StringListStringListTuple2;

int go_31(struct StringStringBoolFun2Tuple1 arg_37, struct StringList* xs_8, struct StringList* ys_1);

int listEq_2(struct IntIntBoolFun2 itemEq_, struct IntList* xs_7, struct IntList* ys_);

int listEq_1(struct StringStringBoolFun2 itemEq_, struct StringList* xs_7, struct StringList* ys_);

struct IntIntTuple2;

struct IntList* go_30(struct IntIntTuple2 arg_38, struct IntList* acc_1, int i_);

struct IntList* listReplicate_1(int item_, int len_2);

struct IntIntFun1;

struct IntIntIntFun1Tuple2;

struct IntList* go_29(struct IntIntIntFun1Tuple2 arg_39, struct IntList* acc_2, int i_1);

struct IntList* listInit_1(int len_3, struct IntIntFun1 gen_);

struct StringStringListTuple2;

struct StringStringListTuple2 go_5(struct StringList* xs_11, int xn_);

struct String strConcat_(struct StringList* xs_10);

int intEq_(int first_, int second_);

int intMin_(int first_1, int second_1);

int intMax_(int first_2, int second_2);

int strEq_(struct String first_3, struct String second_3);

int failwith_1(struct String msg_);

int fun_23(int __5);

int fun_3(void* env_, int arg_);

struct IntList* scanIntList_(int len_4);

struct IntObjectFun1;

struct ObjectIntIntFun2;

struct ObjectIntIntObjectFun3;

enum TypeTag_Tag;

struct TypeTag_;

struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6;

struct IntObjectFun1 typeToArrayNew_1(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 arg_40);

struct ObjectIntIntFun2 typeToArrayGet_1(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 arg_41);

struct ObjectIntIntObjectFun3 typeToArraySet_1(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 arg_42);

void* fun_4(void* env_1, int arg_1);

int fun_5(void* env_2, void* arg_2, int arg_3);

void* fun_6(void* env_3, void* arg_4, int arg_5, int arg_6);

enum VectorTag_Tag;

struct VectorTag_;

struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5;

int vectorToLength_1(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 arg_43);

struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 vectorNew_1(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 itemTy_, int len_6);

int vectorCheckIndex_1(int index_2, struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 self_);

int vectorGet_1(int index_3, struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 self_1);

int vectorSet_1(int index_4, int value_1, struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 self_2);

struct IntIntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5Tuple2;

int go_28(struct IntIntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5Tuple2 arg_44, int i_2, struct IntList* xs_19);

struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 vectorOfList_1(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 ty_, struct IntList* xs_18);

int go_7(struct IntIntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5Tuple2 arg_45, int i_3);

struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1;

struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 scanIntVector_(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 arg_46, int len_10);

int refCase_(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 arg_47, int arg_48);

int vectorOfListTest_(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 arg_49, int arg_50);

int vectorTest_(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 arg_51, int arg_52);

int intervalIsDisjoint_(struct IntIntTuple2 first_4, struct IntIntTuple2 second_4);

int intervalCovers_(struct IntIntTuple2 first_5, struct IntIntTuple2 second_5);

enum SegItemTypeTag_Tag;

struct SegItemTypeTag_;

struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4;

struct StringStringStringFun2 segItemTypeToAppend_2(struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 arg_53);

struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4;

struct IntIntIntFun2 segItemTypeToAppend_1(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 arg_54);

struct IntIntIntObjectSegNodeTag_Tuple5 segItemTypeToEmptyNode_2(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 arg_55);

struct StringIntIntObjectSegNodeTag_Tuple5 segItemTypeToEmptyNode_1(struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 arg_56);

void* segItemTypeToNoChildren_1(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 arg_57);

void* segItemTypeToNoChildren_2(struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 arg_58);

int segItemTypeToEmptyItem_1(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_4);

struct ObjectTuple1;

struct StringIntIntObjectSegNodeTag_Tuple5StringIntIntObjectSegNodeTag_Tuple5Tuple2;

struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 segItemTypeNew_2(struct ObjectTuple1 arg_59, struct String emptyItem_, struct StringStringStringFun2 append_1);

struct IntIntIntObjectSegNodeTag_Tuple5IntIntIntObjectSegNodeTag_Tuple5Tuple2;

struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 segItemTypeNew_1(struct ObjectTuple1 arg_60, int emptyItem_, struct IntIntIntFun2 append_1);

struct StringIntIntObjectSegNodeTag_Tuple5 segNodeNewEmpty_2(struct ObjectTuple1 arg_61, struct String emptyItem_1);

struct IntIntIntObjectSegNodeTag_Tuple5 segNodeNewEmpty_1(struct ObjectTuple1 arg_62, int emptyItem_1);

struct IntIntIntObjectSegNodeTag_Tuple5 segNodeNewLeaf_1(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_6, int item_1);

struct StringIntIntObjectSegNodeTag_Tuple5 segNodeNewLeaf_2(struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_6, struct String item_1);

struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5IntIntIntObjectSegNodeTag_Tuple5Tuple3;

struct IntIntIntObjectSegNodeTag_Tuple5 doNew_1(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5IntIntIntObjectSegNodeTag_Tuple5Tuple3 arg_63, int arg_64);

struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4StringIntIntObjectSegNodeTag_Tuple5StringIntIntObjectSegNodeTag_Tuple5Tuple3;

struct StringIntIntObjectSegNodeTag_Tuple5 doNew_2(struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4StringIntIntObjectSegNodeTag_Tuple5StringIntIntObjectSegNodeTag_Tuple5Tuple3 arg_65, int arg_66);

struct IntIntIntObjectSegNodeTag_Tuple5 segNodeNew_1(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_7, struct IntIntIntObjectSegNodeTag_Tuple5 left_, struct IntIntIntObjectSegNodeTag_Tuple5 right_);

struct StringIntIntObjectSegNodeTag_Tuple5 segNodeNew_2(struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_7, struct StringIntIntObjectSegNodeTag_Tuple5 left_, struct StringIntIntObjectSegNodeTag_Tuple5 right_);

int segNodeToItem_1(struct IntIntIntObjectSegNodeTag_Tuple5 node_);

int segNodeToLength_1(struct IntIntIntObjectSegNodeTag_Tuple5 node_1);

int segNodeToLength_2(struct StringIntIntObjectSegNodeTag_Tuple5 node_1);

int segNodeToHeight_1(struct IntIntIntObjectSegNodeTag_Tuple5 node_2);

int segNodeToHeight_2(struct StringIntIntObjectSegNodeTag_Tuple5 node_2);

struct IntIntIntObjectSegNodeTag_Tuple5IntIntIntObjectSegNodeTag_Tuple5Tuple2 segNodeToChildren_1(struct IntIntIntObjectSegNodeTag_Tuple5 node_3);

struct StringIntIntObjectSegNodeTag_Tuple5StringIntIntObjectSegNodeTag_Tuple5Tuple2 segNodeToChildren_2(struct StringIntIntObjectSegNodeTag_Tuple5 node_3);

int segNodeIsEmpty_1(struct IntIntIntObjectSegNodeTag_Tuple5 node_4);

struct IntIntIntObjectSegNodeTag_Tuple5 segNodeWithLeft_1(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_8, struct IntIntIntObjectSegNodeTag_Tuple5 newLeft_, struct IntIntIntObjectSegNodeTag_Tuple5 node_5);

struct StringIntIntObjectSegNodeTag_Tuple5 segNodeWithLeft_2(struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_8, struct StringIntIntObjectSegNodeTag_Tuple5 newLeft_, struct StringIntIntObjectSegNodeTag_Tuple5 node_5);

struct IntIntIntObjectSegNodeTag_Tuple5 segNodeWithRight_1(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_9, struct IntIntIntObjectSegNodeTag_Tuple5 newRight_, struct IntIntIntObjectSegNodeTag_Tuple5 node_6);

struct StringIntIntObjectSegNodeTag_Tuple5 segNodeWithRight_2(struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_9, struct StringIntIntObjectSegNodeTag_Tuple5 newRight_, struct StringIntIntObjectSegNodeTag_Tuple5 node_6);

struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1;

struct IntIntIntObjectSegNodeTag_Tuple5 rotateLeft_1(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 arg_67, struct IntIntIntObjectSegNodeTag_Tuple5 node_8);

struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1;

struct StringIntIntObjectSegNodeTag_Tuple5 rotateLeft_2(struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 arg_68, struct StringIntIntObjectSegNodeTag_Tuple5 node_8);

struct IntIntIntObjectSegNodeTag_Tuple5 rotateRight_1(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 arg_69, struct IntIntIntObjectSegNodeTag_Tuple5 node_9);

struct StringIntIntObjectSegNodeTag_Tuple5 rotateRight_2(struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 arg_70, struct StringIntIntObjectSegNodeTag_Tuple5 node_9);

struct IntIntIntObjectSegNodeTag_Tuple5 doubleLeft_1(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 arg_71, struct IntIntIntObjectSegNodeTag_Tuple5 node_10);

struct StringIntIntObjectSegNodeTag_Tuple5 doubleLeft_2(struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 arg_72, struct StringIntIntObjectSegNodeTag_Tuple5 node_10);

struct IntIntIntObjectSegNodeTag_Tuple5 doubleRight_1(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 arg_73, struct IntIntIntObjectSegNodeTag_Tuple5 node_11);

struct StringIntIntObjectSegNodeTag_Tuple5 doubleRight_2(struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 arg_74, struct StringIntIntObjectSegNodeTag_Tuple5 node_11);

int toBalance_1(struct IntIntIntObjectSegNodeTag_Tuple5 node_12);

int toBalance_2(struct StringIntIntObjectSegNodeTag_Tuple5 node_12);

struct IntIntIntObjectSegNodeTag_Tuple5 segNodeMakeBalanced_1(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_10, struct IntIntIntObjectSegNodeTag_Tuple5 node_7);

struct StringIntIntObjectSegNodeTag_Tuple5 segNodeMakeBalanced_2(struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_10, struct StringIntIntObjectSegNodeTag_Tuple5 node_7);

enum SegTreeTag_Tag;

struct SegTreeTag_;

struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3;

struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 segTreeNew_2(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_11);

struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4StringIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3;

struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4StringIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 segTreeNew_1(struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_11);

struct IntIntIntObjectSegNodeTag_Tuple5 segTreeToRoot_1(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 self_4);

struct StringIntIntObjectSegNodeTag_Tuple5 segTreeToRoot_2(struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4StringIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 self_4);

int segTreeToLength_1(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 self_5);

int segTreeToLength_2(struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4StringIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 self_5);

int segTreeToHeight_1(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 self_6);

int go_27(int index_6, struct IntIntIntObjectSegNodeTag_Tuple5 node_14);

struct String go_37(int index_6, struct StringIntIntObjectSegNodeTag_Tuple5 node_14);

int segTreeGet_1(int index_5, struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 self_8);

struct String segTreeGet_2(int index_5, struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4StringIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 self_8);

int go_26(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 arg_75, struct IntIntTuple2 e_, struct IntIntTuple2 q_, struct IntIntIntObjectSegNodeTag_Tuple5 node_15);

int segTreeSum_1(int ql_, int qr_, struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 self_9);

struct IntIntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple2;

struct IntIntIntObjectSegNodeTag_Tuple5 go_25(struct IntIntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple2 arg_76, int index_8, struct IntIntIntObjectSegNodeTag_Tuple5 node_16);

struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 segTreeSet_1(int index_7, int newItem_, struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 self_10);

struct IntIntIntObjectSegNodeTag_Tuple5 go_24(struct IntIntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple2 arg_77, int index_10, struct IntIntIntObjectSegNodeTag_Tuple5 node_17);

struct StringStringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple2;

struct StringIntIntObjectSegNodeTag_Tuple5 go_36(struct StringStringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple2 arg_78, int index_10, struct StringIntIntObjectSegNodeTag_Tuple5 node_17);

struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 segTreeInsert_1(int index_9, int newItem_1, struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 self_11);

struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4StringIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 segTreeInsert_2(int index_9, struct String newItem_1, struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4StringIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 self_11);

struct IntIntIntObjectSegNodeTag_Tuple5 go_35(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 arg_79, int index_12, struct IntIntIntObjectSegNodeTag_Tuple5 node_18);

struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 segTreeRemove_1(int index_11, struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 self_12);

struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4StringIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 segTreePush_2(struct String value_4, struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4StringIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 self_13);

struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 segTreePush_1(int value_4, struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 self_13);

struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 segTreePop_1(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 self_14);

struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 go_23(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 t_2, struct IntList* xs_22);

struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 segTreeOfList_1(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_16, struct IntList* xs_21);

struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3IntTuple2;

struct IntList* go_22(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3IntTuple2 arg_80, struct IntList* acc_3, int i_4);

struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4StringIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3IntTuple2;

struct StringList* go_21(struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4StringIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3IntTuple2 arg_81, struct StringList* acc_3, int i_4);

struct IntList* segTreeToList_2(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 v_4);

struct StringList* segTreeToList_1(struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4StringIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 v_4);

int intAdd_(int x_8, int y_3);

int fun_7(void* env_4, int arg_7, int arg_8);

struct String strAdd_(struct String x_9, struct String y_4);

struct String fun_8(void* env_5, struct String arg_9, struct String arg_10);

int fun_9(void* env_6, int arg_11, int arg_12);

int fun_10(void* env_7, int arg_13, int arg_14);

int fun_11(void* env_8, int arg_15, int arg_16);

int fun_12(void* env_9, int arg_17, int arg_18);

int fun_13(void* env_10, int arg_19, int arg_20);

int testPushPop_(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 arg_82, int arg_83);

int fun_14(void* env_11, int arg_21, int arg_22);

int fun_15(void* env_12, int arg_23, int arg_24);

int testSet_(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 arg_84, int arg_85);

int testSum_(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 arg_86, int arg_87);

int sum_(struct IntIntTuple2 arg_88, int acc_4, int i_5, struct IntList* xs_25);

struct IntListIntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3IntTuple3;

int go_15(struct IntListIntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3IntTuple3 arg_89, int l_1, int r_1);

int testSumMore_(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 arg_90, int arg_91);

int testBalance_(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 arg_92, int arg_93);

int fun_16(void* env_13, struct String arg_25, struct String arg_26);

int testPolymorphic_(struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 arg_94, int arg_95);

int segTreeTest_(struct ObjectTuple1 arg_96, int arg_97);

int abc140aSolve_(int n_2);

int abc140aTest_(int arg_98);

int abc140aMain_(int arg_99);

int fun_22(int __91, int __92);

int fun_17(void* env_14, int arg_27, int arg_28);

struct IntIntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3Tuple4;

int go_16(struct IntIntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3Tuple4 arg_100, int sum_1, int i_6);

int abc140bSolve_(struct ObjectTuple1 arg_101, int n_4, struct IntList* a_, struct IntList* b_, struct IntList* c_);

int f_(struct ObjectTuple1 arg_102, struct IntList* a_2, struct IntList* b_2, struct IntList* c_2);

int case1_(struct ObjectTuple1 arg_103, int arg_104);

int case2_(struct ObjectTuple1 arg_105, int arg_106);

int case3_(struct ObjectTuple1 arg_107, int arg_108);

int abc140bTest_(struct ObjectTuple1 arg_109, int arg_110);

int abc140bMain_(struct ObjectTuple1 arg_111, int arg_112);

int fun_21(int __93, int __94);

int fun_18(void* env_15, int arg_29, int arg_30);

int fun_19(void* env_16, int arg_31, int arg_32);

int fun_20(void* env_17, int arg_33, int arg_34);

struct IntIntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3Tuple2;

struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 go_20(struct IntIntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3Tuple2 arg_113, struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 pos_1, int i_7);

int go_19(struct IntIntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3Tuple2 arg_114, int sum_2, struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 prev_1, struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 next_1, int p_);

int abc140eSolve_(struct ObjectTuple1 arg_115, int n_7, struct IntList* perm_);

int solve_(struct ObjectTuple1 arg_116, struct IntList* p_1, int expected_1);

int abc140eTest_(struct ObjectTuple1 arg_117, int arg_118);

int abc140eMain_(struct ObjectTuple1 arg_119, int arg_120);

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

int ignore_1(void* __1) {
    return 0;
}

struct StringList {
    struct String head;
    struct StringList* tail;
};

int listIsEmpty_1(struct StringList* xs_) {
    int match_;
    if (!((!(xs_)))) goto next_2;
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

int listIsEmpty_5(struct StringStringStringFun2List* xs_) {
    int match_1;
    if (!((!(xs_)))) goto next_5;
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

int listIsEmpty_4(struct IntList* xs_) {
    int match_2;
    if (!((!(xs_)))) goto next_8;
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

int listIsEmpty_3(struct IntIntIntFun2List* xs_) {
    int match_3;
    if (!((!(xs_)))) goto next_11;
    match_3 = 1;
    goto end_match_10;
next_11:;
    match_3 = 0;
    goto end_match_10;
next_12:;
end_match_10:;
    return match_3;
}

enum SegNodeTag_Tag {
    SegNodeTag_,
};

struct SegNodeTag_ {
    enum SegNodeTag_Tag tag;
};

struct IntIntIntObjectSegNodeTag_Tuple5 {
    int t0;
    int t1;
    int t2;
    void* t3;
    struct SegNodeTag_ t4;
};

struct IntIntIntObjectSegNodeTag_Tuple5List {
    struct IntIntIntObjectSegNodeTag_Tuple5 head;
    struct IntIntIntObjectSegNodeTag_Tuple5List* tail;
};

int listIsEmpty_2(struct IntIntIntObjectSegNodeTag_Tuple5List* xs_) {
    int match_4;
    if (!((!(xs_)))) goto next_14;
    match_4 = 1;
    goto end_match_13;
next_14:;
    match_4 = 0;
    goto end_match_13;
next_15:;
end_match_13:;
    return match_4;
}

struct StringIntIntObjectSegNodeTag_Tuple5 {
    struct String t0;
    int t1;
    int t2;
    void* t3;
    struct SegNodeTag_ t4;
};

struct StringIntIntObjectSegNodeTag_Tuple5List {
    struct StringIntIntObjectSegNodeTag_Tuple5 head;
    struct StringIntIntObjectSegNodeTag_Tuple5List* tail;
};

int listIsEmpty_6(struct StringIntIntObjectSegNodeTag_Tuple5List* xs_) {
    int match_5;
    if (!((!(xs_)))) goto next_17;
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
    int match_6;
    if (!((!(xs_2)))) goto next_20;
    match_6 = len_1;
    goto end_match_19;
next_20:;
    if (!((!((!(xs_2)))))) goto next_21;
    struct StringList* xs_3 = xs_2->tail;
    int call_5 = go_34((len_1 + 1), xs_3);
    match_6 = call_5;
    goto end_match_19;
next_21:;
    exit(1);
end_match_19:;
    return match_6;
}

int go_33(int len_1, struct IntList* xs_2) {
    int match_7;
    if (!((!(xs_2)))) goto next_23;
    match_7 = len_1;
    goto end_match_22;
next_23:;
    if (!((!((!(xs_2)))))) goto next_24;
    struct IntList* xs_3 = xs_2->tail;
    int call_6 = go_33((len_1 + 1), xs_3);
    match_7 = call_6;
    goto end_match_22;
next_24:;
    exit(1);
end_match_22:;
    return match_7;
}

int listLength_2(struct StringList* xs_1) {
    int call_7 = go_34(0, xs_1);
    return call_7;
}

int listLength_1(struct IntList* xs_1) {
    int call_8 = go_33(0, xs_1);
    return call_8;
}

struct IntList* go_39(struct IntList* acc_, struct IntList* xs_5) {
    struct IntList* match_8;
    if (!((!(xs_5)))) goto next_26;
    match_8 = acc_;
    goto end_match_25;
next_26:;
    if (!((!((!(xs_5)))))) goto next_27;
    int x_ = xs_5->head;
    struct IntList* xs_6 = xs_5->tail;
    struct IntList* list_ = (struct IntList*)malloc(sizeof(struct IntList));
    list_->head = x_;
    list_->tail = acc_;
    struct IntList* call_9 = go_39(list_, xs_6);
    match_8 = call_9;
    goto end_match_25;
next_27:;
    exit(1);
end_match_25:;
    return match_8;
}

struct StringList* go_38(struct StringList* acc_, struct StringList* xs_5) {
    struct StringList* match_9;
    if (!((!(xs_5)))) goto next_29;
    match_9 = acc_;
    goto end_match_28;
next_29:;
    if (!((!((!(xs_5)))))) goto next_30;
    struct String x_ = xs_5->head;
    struct StringList* xs_6 = xs_5->tail;
    struct StringList* list_1 = (struct StringList*)malloc(sizeof(struct StringList));
    list_1->head = x_;
    list_1->tail = acc_;
    struct StringList* call_10 = go_38(list_1, xs_6);
    match_9 = call_10;
    goto end_match_28;
next_30:;
    exit(1);
end_match_28:;
    return match_9;
}

struct IntList* listRev_2(struct IntList* xs_4) {
    struct IntList* call_11 = go_39(NULL, xs_4);
    return call_11;
}

struct StringList* listRev_1(struct StringList* xs_4) {
    struct StringList* call_12 = go_38(NULL, xs_4);
    return call_12;
}

struct IntIntBoolFun2 {
    int(*fun)(void*, int, int);
    void* env;
};

struct IntIntBoolFun2Tuple1 {
    struct IntIntBoolFun2 t0;
};

struct IntListIntListTuple2 {
    struct IntList* t0;
    struct IntList* t1;
};

int go_32(struct IntIntBoolFun2Tuple1 arg_36, struct IntList* xs_8, struct IntList* ys_1) {
    struct IntIntBoolFun2 itemEq_ = arg_36.t0;
    int match_10;
    struct IntListIntListTuple2 tuple_;
    tuple_.t0 = xs_8;
    tuple_.t1 = ys_1;
    if (!((!(tuple_.t0)))) goto next_32;
    if (!((!(tuple_.t1)))) goto next_32;
    match_10 = 1;
    goto end_match_31;
next_32:;
    if (!((!((!(tuple_.t0)))))) goto next_33;
    int x_1 = tuple_.t0->head;
    struct IntList* xs_9 = tuple_.t0->tail;
    if (!((!((!(tuple_.t1)))))) goto next_33;
    int y_ = tuple_.t1->head;
    struct IntList* ys_2 = tuple_.t1->tail;
    int match_11;
    int app_ = itemEq_.fun(itemEq_.env, x_1, y_);
    if (!((app_ == 1))) goto next_36;
    struct IntIntBoolFun2Tuple1 tuple_1;
    tuple_1.t0 = itemEq_;
    int call_13 = go_32(tuple_1, xs_9, ys_2);
    match_11 = call_13;
    goto end_match_35;
next_36:;
    if (!((app_ == 0))) goto next_37;
    match_11 = 0;
    goto end_match_35;
next_37:;
    exit(1);
end_match_35:;
    match_10 = match_11;
    goto end_match_31;
next_33:;
    match_10 = 0;
    goto end_match_31;
next_34:;
end_match_31:;
    return match_10;
}

struct StringStringBoolFun2 {
    int(*fun)(void*, struct String, struct String);
    void* env;
};

struct StringStringBoolFun2Tuple1 {
    struct StringStringBoolFun2 t0;
};

struct StringListStringListTuple2 {
    struct StringList* t0;
    struct StringList* t1;
};

int go_31(struct StringStringBoolFun2Tuple1 arg_37, struct StringList* xs_8, struct StringList* ys_1) {
    struct StringStringBoolFun2 itemEq_ = arg_37.t0;
    int match_12;
    struct StringListStringListTuple2 tuple_2;
    tuple_2.t0 = xs_8;
    tuple_2.t1 = ys_1;
    if (!((!(tuple_2.t0)))) goto next_39;
    if (!((!(tuple_2.t1)))) goto next_39;
    match_12 = 1;
    goto end_match_38;
next_39:;
    if (!((!((!(tuple_2.t0)))))) goto next_40;
    struct String x_1 = tuple_2.t0->head;
    struct StringList* xs_9 = tuple_2.t0->tail;
    if (!((!((!(tuple_2.t1)))))) goto next_40;
    struct String y_ = tuple_2.t1->head;
    struct StringList* ys_2 = tuple_2.t1->tail;
    int match_13;
    int app_1 = itemEq_.fun(itemEq_.env, x_1, y_);
    if (!((app_1 == 1))) goto next_43;
    struct StringStringBoolFun2Tuple1 tuple_3;
    tuple_3.t0 = itemEq_;
    int call_14 = go_31(tuple_3, xs_9, ys_2);
    match_13 = call_14;
    goto end_match_42;
next_43:;
    if (!((app_1 == 0))) goto next_44;
    match_13 = 0;
    goto end_match_42;
next_44:;
    exit(1);
end_match_42:;
    match_12 = match_13;
    goto end_match_38;
next_40:;
    match_12 = 0;
    goto end_match_38;
next_41:;
end_match_38:;
    return match_12;
}

int listEq_2(struct IntIntBoolFun2 itemEq_, struct IntList* xs_7, struct IntList* ys_) {
    struct IntIntBoolFun2Tuple1 tuple_4;
    tuple_4.t0 = itemEq_;
    int call_15 = go_32(tuple_4, xs_7, ys_);
    return call_15;
}

int listEq_1(struct StringStringBoolFun2 itemEq_, struct StringList* xs_7, struct StringList* ys_) {
    struct StringStringBoolFun2Tuple1 tuple_5;
    tuple_5.t0 = itemEq_;
    int call_16 = go_31(tuple_5, xs_7, ys_);
    return call_16;
}

struct IntIntTuple2 {
    int t0;
    int t1;
};

struct IntList* go_30(struct IntIntTuple2 arg_38, struct IntList* acc_1, int i_) {
    int item_ = arg_38.t0;
    int len_2 = arg_38.t1;
    struct IntList* match_14;
    if (!(((i_ == len_2) == 1))) goto next_46;
    match_14 = acc_1;
    goto end_match_45;
next_46:;
    if (!(((i_ == len_2) == 0))) goto next_47;
    struct IntIntTuple2 tuple_6;
    tuple_6.t0 = item_;
    tuple_6.t1 = len_2;
    struct IntList* list_2 = (struct IntList*)malloc(sizeof(struct IntList));
    list_2->head = item_;
    list_2->tail = acc_1;
    struct IntList* call_17 = go_30(tuple_6, list_2, (i_ + 1));
    match_14 = call_17;
    goto end_match_45;
next_47:;
    exit(1);
end_match_45:;
    return match_14;
}

struct IntList* listReplicate_1(int item_, int len_2) {
    struct IntIntTuple2 tuple_7;
    tuple_7.t0 = item_;
    tuple_7.t1 = len_2;
    struct IntList* call_18 = go_30(tuple_7, NULL, 0);
    return call_18;
}

struct IntIntFun1 {
    int(*fun)(void*, int);
    void* env;
};

struct IntIntIntFun1Tuple2 {
    int t0;
    struct IntIntFun1 t1;
};

struct IntList* go_29(struct IntIntIntFun1Tuple2 arg_39, struct IntList* acc_2, int i_1) {
    int len_3 = arg_39.t0;
    struct IntIntFun1 gen_ = arg_39.t1;
    struct IntList* match_15;
    if (!(((i_1 == len_3) == 1))) goto next_49;
    struct IntList* call_19 = listRev_2(acc_2);
    match_15 = call_19;
    goto end_match_48;
next_49:;
    if (!(((i_1 == len_3) == 0))) goto next_50;
    struct IntIntIntFun1Tuple2 tuple_8;
    tuple_8.t0 = len_3;
    tuple_8.t1 = gen_;
    int app_2 = gen_.fun(gen_.env, i_1);
    struct IntList* list_3 = (struct IntList*)malloc(sizeof(struct IntList));
    list_3->head = app_2;
    list_3->tail = acc_2;
    struct IntList* call_20 = go_29(tuple_8, list_3, (i_1 + 1));
    match_15 = call_20;
    goto end_match_48;
next_50:;
    exit(1);
end_match_48:;
    return match_15;
}

struct IntList* listInit_1(int len_3, struct IntIntFun1 gen_) {
    milone_assert((0 <= len_3));
    int call_21 = 0;
    struct IntIntIntFun1Tuple2 tuple_9;
    tuple_9.t0 = len_3;
    tuple_9.t1 = gen_;
    struct IntList* call_22 = go_29(tuple_9, NULL, 0);
    return call_22;
}

struct StringStringListTuple2 {
    struct String t0;
    struct StringList* t1;
};

struct StringStringListTuple2 go_5(struct StringList* xs_11, int xn_) {
    struct StringStringListTuple2 match_16;
    if (!((!(xs_11)))) goto next_52;
    milone_assert((xn_ == 0));
    int call_23 = 0;
    struct StringStringListTuple2 tuple_10;
    tuple_10.t0 = (struct String){.str = "", .len = 0};
    tuple_10.t1 = NULL;
    match_16 = tuple_10;
    goto end_match_51;
next_52:;
    if (!((!((!(xs_11)))))) goto next_53;
    struct String x_2 = xs_11->head;
    struct StringList* xs_12 = xs_11->tail;
    if (!((xn_ == 1))) goto next_53;
    struct StringStringListTuple2 tuple_11;
    tuple_11.t0 = x_2;
    tuple_11.t1 = xs_12;
    match_16 = tuple_11;
    goto end_match_51;
next_53:;
    if (!((!((!(xs_11)))))) goto next_54;
    struct String x_3 = xs_11->head;
    if (!((!((!(xs_11->tail)))))) goto next_54;
    struct String y_1 = xs_11->tail->head;
    struct StringList* xs_13 = xs_11->tail->tail;
    if (!((xn_ == 2))) goto next_54;
    struct StringStringListTuple2 tuple_12;
    tuple_12.t0 = str_add(x_3, y_1);
    tuple_12.t1 = xs_13;
    match_16 = tuple_12;
    goto end_match_51;
next_54:;
    struct StringList* xs_14 = xs_11;
    int m_ = (xn_ / 2);
    struct StringStringListTuple2 call_24 = go_5(xs_14, m_);
    struct String l_ = call_24.t0;
    struct StringList* xs_15 = call_24.t1;
    struct StringStringListTuple2 call_25 = go_5(xs_15, (xn_ - m_));
    struct String r_ = call_25.t0;
    struct StringList* xs_16 = call_25.t1;
    struct StringStringListTuple2 tuple_13;
    tuple_13.t0 = str_add(l_, r_);
    tuple_13.t1 = xs_16;
    match_16 = tuple_13;
    goto end_match_51;
next_55:;
end_match_51:;
    return match_16;
}

struct String strConcat_(struct StringList* xs_10) {
    int call_26 = listLength_2(xs_10);
    int n_ = call_26;
    struct StringStringListTuple2 call_27 = go_5(xs_10, n_);
    struct String s_ = call_27.t0;
    struct StringList* xs_17 = call_27.t1;
    int call_28 = listIsEmpty_1(xs_17);
    milone_assert(call_28);
    int call_29 = 0;
    return s_;
}

int intEq_(int first_, int second_) {
    return (first_ == second_);
}

int intMin_(int first_1, int second_1) {
    int match_17;
    if (!(((second_1 < first_1) == 1))) goto next_57;
    match_17 = second_1;
    goto end_match_56;
next_57:;
    if (!(((second_1 < first_1) == 0))) goto next_58;
    match_17 = first_1;
    goto end_match_56;
next_58:;
    exit(1);
end_match_56:;
    return match_17;
}

int intMax_(int first_2, int second_2) {
    int match_18;
    if (!(((first_2 < second_2) == 1))) goto next_60;
    match_18 = second_2;
    goto end_match_59;
next_60:;
    if (!(((first_2 < second_2) == 0))) goto next_61;
    match_18 = first_2;
    goto end_match_59;
next_61:;
    exit(1);
end_match_59:;
    return match_18;
}

int strEq_(struct String first_3, struct String second_3) {
    return (str_cmp(first_3, second_3) == 0);
}

int failwith_1(struct String msg_) {
    printf("ERROR %s\n", msg_.str);
    int call_30 = 0;
    exit(1);
    return 0;
}

int fun_23(int __5) {
    int call_31 = scanInt_(0);
    return call_31;
}

int fun_3(void* env_, int arg_) {
    int call_32 = fun_23(arg_);
    return call_32;
}

struct IntList* scanIntList_(int len_4) {
    void* box_ = (void*)malloc(sizeof(int));
    (*(((int*)box_))) = 0;
    void* env_18 = box_;
    struct IntIntFun1 fun_24 = (struct IntIntFun1){.fun = fun_3, .env = env_18};
    struct IntList* call_33 = listInit_1(len_4, fun_24);
    return call_33;
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

struct IntObjectFun1 typeToArrayNew_1(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 arg_40) {
    struct IntObjectFun1 arrayNew_ = arg_40.t2;
    struct TypeTag_ _typeTag_2 = arg_40.t5;
    return arrayNew_;
}

struct ObjectIntIntFun2 typeToArrayGet_1(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 arg_41) {
    struct ObjectIntIntFun2 arrayGet_ = arg_41.t3;
    struct TypeTag_ _typeTag_3 = arg_41.t5;
    return arrayGet_;
}

struct ObjectIntIntObjectFun3 typeToArraySet_1(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 arg_42) {
    struct ObjectIntIntObjectFun3 arraySet_ = arg_42.t4;
    struct TypeTag_ _typeTag_4 = arg_42.t5;
    return arraySet_;
}

void* fun_4(void* env_1, int arg_1) {
    void* call_34 = rawIntArrayNew_(arg_1);
    return call_34;
}

int fun_5(void* env_2, void* arg_2, int arg_3) {
    int call_35 = rawIntArrayGet_(arg_2, arg_3);
    return call_35;
}

void* fun_6(void* env_3, void* arg_4, int arg_5, int arg_6) {
    void* call_36 = rawIntArraySet_(arg_4, arg_5, arg_6);
    return call_36;
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

int vectorToLength_1(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 arg_43) {
    int len_5 = arg_43.t2;
    struct VectorTag_ _vectorTag_ = arg_43.t4;
    return len_5;
}

struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 vectorNew_1(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 itemTy_, int len_6) {
    struct IntObjectFun1 call_37 = typeToArrayNew_1(itemTy_);
    void* app_3 = call_37.fun(call_37.env, len_6);
    void* array_2 = app_3;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 tuple_14;
    tuple_14.t0 = itemTy_;
    tuple_14.t1 = array_2;
    tuple_14.t2 = len_6;
    tuple_14.t3 = len_6;
    tuple_14.t4 = (struct VectorTag_){.tag = VectorTag_};
    return tuple_14;
}

int vectorCheckIndex_1(int index_2, struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 self_) {
    int call_38 = vectorToLength_1(self_);
    int len_7 = call_38;
    int match_19;
    int match_20;
    if (!(((index_2 < 0) == 1))) goto next_64;
    match_20 = 1;
    goto end_match_63;
next_64:;
    if (!(((index_2 < 0) == 0))) goto next_65;
    match_20 = (len_7 <= index_2);
    goto end_match_63;
next_65:;
    exit(1);
end_match_63:;
    if (!((match_20 == 1))) goto next_66;
    printf("ERROR: Out of range (len = %d, index = %d)\n", len_7, index_2);
    int call_39 = 0;
    exit(1);
    match_19 = 0;
    goto end_match_62;
next_66:;
    if (!((match_20 == 0))) goto next_67;
    match_19 = 0;
    goto end_match_62;
next_67:;
    exit(1);
end_match_62:;
    return 0;
}

int vectorGet_1(int index_3, struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 self_1) {
    int call_40 = vectorCheckIndex_1(index_3, self_1);
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 itemTy_1 = self_1.t0;
    void* array_3 = self_1.t1;
    struct VectorTag_ _vectorTag_1 = self_1.t4;
    struct ObjectIntIntFun2 call_41 = typeToArrayGet_1(itemTy_1);
    int app_4 = call_41.fun(call_41.env, array_3, index_3);
    return app_4;
}

int vectorSet_1(int index_4, int value_1, struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 self_2) {
    int call_42 = vectorCheckIndex_1(index_4, self_2);
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 itemTy_2 = self_2.t0;
    void* array_4 = self_2.t1;
    struct VectorTag_ _vectorTag_2 = self_2.t4;
    struct ObjectIntIntObjectFun3 call_43 = typeToArraySet_1(itemTy_2);
    void* app_5 = call_43.fun(call_43.env, array_4, index_4, value_1);
    int call_44 = ignore_1(app_5);
    return 0;
}

struct IntIntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5Tuple2 {
    int t0;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 t1;
};

int go_28(struct IntIntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5Tuple2 arg_44, int i_2, struct IntList* xs_19) {
    int len_9 = arg_44.t0;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 v_ = arg_44.t1;
    int match_21;
    if (!((!(xs_19)))) goto next_69;
    milone_assert((i_2 == len_9));
    int call_45 = 0;
    match_21 = 0;
    goto end_match_68;
next_69:;
    if (!((!((!(xs_19)))))) goto next_70;
    int x_4 = xs_19->head;
    struct IntList* xs_20 = xs_19->tail;
    int call_46 = vectorSet_1(i_2, x_4, v_);
    struct IntIntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5Tuple2 tuple_15;
    tuple_15.t0 = len_9;
    tuple_15.t1 = v_;
    int call_47 = go_28(tuple_15, (i_2 + 1), xs_20);
    match_21 = 0;
    goto end_match_68;
next_70:;
    exit(1);
end_match_68:;
    return 0;
}

struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 vectorOfList_1(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 ty_, struct IntList* xs_18) {
    int call_48 = listLength_1(xs_18);
    int len_9 = call_48;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 call_49 = vectorNew_1(ty_, len_9);
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 v_ = call_49;
    struct IntIntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5Tuple2 tuple_16;
    tuple_16.t0 = len_9;
    tuple_16.t1 = v_;
    int call_50 = go_28(tuple_16, 0, xs_18);
    return v_;
}

int go_7(struct IntIntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5Tuple2 arg_45, int i_3) {
    int len_10 = arg_45.t0;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 v_1 = arg_45.t1;
    int match_22;
    if (!(((i_3 < len_10) == 1))) goto next_72;
    int call_51 = scanInt_(0);
    int value_3 = call_51;
    int call_52 = vectorSet_1(i_3, value_3, v_1);
    struct IntIntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5Tuple2 tuple_17;
    tuple_17.t0 = len_10;
    tuple_17.t1 = v_1;
    int call_53 = go_7(tuple_17, (i_3 + 1));
    match_22 = 0;
    goto end_match_71;
next_72:;
    if (!(((i_3 < len_10) == 0))) goto next_73;
    match_22 = 0;
    goto end_match_71;
next_73:;
    exit(1);
end_match_71:;
    return 0;
}

struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 {
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 t0;
};

struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 scanIntVector_(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 arg_46, int len_10) {
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 typeInt_ = arg_46.t0;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 call_54 = vectorNew_1(typeInt_, len_10);
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 v_1 = call_54;
    struct IntIntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5Tuple2 tuple_18;
    tuple_18.t0 = len_10;
    tuple_18.t1 = v_1;
    int call_55 = go_7(tuple_18, 0);
    return v_1;
}

int refCase_(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 arg_47, int arg_48) {
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 typeInt_ = arg_47.t0;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 call_56 = vectorNew_1(typeInt_, 1);
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 v_2 = call_56;
    int call_57 = vectorToLength_1(v_2);
    milone_assert((call_57 == 1));
    int call_58 = 0;
    int call_59 = vectorGet_1(0, v_2);
    milone_assert((call_59 == 0));
    int call_60 = 0;
    int call_61 = vectorSet_1(0, 42, v_2);
    int call_62 = vectorGet_1(0, v_2);
    milone_assert((call_62 == 42));
    int call_63 = 0;
    return 0;
}

int vectorOfListTest_(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 arg_49, int arg_50) {
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 typeInt_ = arg_49.t0;
    struct IntList* list_6 = (struct IntList*)malloc(sizeof(struct IntList));
    list_6->head = 3;
    list_6->tail = NULL;
    struct IntList* list_5 = (struct IntList*)malloc(sizeof(struct IntList));
    list_5->head = 2;
    list_5->tail = list_6;
    struct IntList* list_4 = (struct IntList*)malloc(sizeof(struct IntList));
    list_4->head = 1;
    list_4->tail = list_5;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 call_64 = vectorOfList_1(typeInt_, list_4);
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6ObjectIntIntVectorTag_Tuple5 v_3 = call_64;
    int call_65 = vectorToLength_1(v_3);
    milone_assert((call_65 == 3));
    int call_66 = 0;
    int call_67 = vectorGet_1(0, v_3);
    milone_assert((call_67 == 1));
    int call_68 = 0;
    int call_69 = vectorGet_1(1, v_3);
    milone_assert((call_69 == 2));
    int call_70 = 0;
    int call_71 = vectorGet_1(2, v_3);
    milone_assert((call_71 == 3));
    int call_72 = 0;
    return 0;
}

int vectorTest_(struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 arg_51, int arg_52) {
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 typeInt_ = arg_51.t0;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 tuple_19;
    tuple_19.t0 = typeInt_;
    int call_73 = refCase_(tuple_19, 0);
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 tuple_20;
    tuple_20.t0 = typeInt_;
    int call_74 = vectorOfListTest_(tuple_20, 0);
    return 0;
}

int intervalIsDisjoint_(struct IntIntTuple2 first_4, struct IntIntTuple2 second_4) {
    int xl_ = first_4.t0;
    int xr_ = first_4.t1;
    int yl_ = second_4.t0;
    int yr_ = second_4.t1;
    int match_23;
    if (!(((xr_ <= yl_) == 1))) goto next_75;
    match_23 = 1;
    goto end_match_74;
next_75:;
    if (!(((xr_ <= yl_) == 0))) goto next_76;
    match_23 = (yr_ <= xl_);
    goto end_match_74;
next_76:;
    exit(1);
end_match_74:;
    return match_23;
}

int intervalCovers_(struct IntIntTuple2 first_5, struct IntIntTuple2 second_5) {
    int xl_1 = first_5.t0;
    int xr_1 = first_5.t1;
    int yl_1 = second_5.t0;
    int yr_1 = second_5.t1;
    int match_24;
    if (!(((xl_1 <= yl_1) == 1))) goto next_78;
    match_24 = (yr_1 <= xr_1);
    goto end_match_77;
next_78:;
    if (!(((xl_1 <= yl_1) == 0))) goto next_79;
    match_24 = 0;
    goto end_match_77;
next_79:;
    exit(1);
end_match_77:;
    return match_24;
}

enum SegItemTypeTag_Tag {
    SegItemTypeTag_,
};

struct SegItemTypeTag_ {
    enum SegItemTypeTag_Tag tag;
};

struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 {
    struct StringStringStringFun2 t0;
    struct StringIntIntObjectSegNodeTag_Tuple5 t1;
    void* t2;
    struct SegItemTypeTag_ t3;
};

struct StringStringStringFun2 segItemTypeToAppend_2(struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 arg_53) {
    struct StringStringStringFun2 append_ = arg_53.t0;
    return append_;
}

struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 {
    struct IntIntIntFun2 t0;
    struct IntIntIntObjectSegNodeTag_Tuple5 t1;
    void* t2;
    struct SegItemTypeTag_ t3;
};

struct IntIntIntFun2 segItemTypeToAppend_1(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 arg_54) {
    struct IntIntIntFun2 append_ = arg_54.t0;
    return append_;
}

struct IntIntIntObjectSegNodeTag_Tuple5 segItemTypeToEmptyNode_2(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 arg_55) {
    struct IntIntIntObjectSegNodeTag_Tuple5 emptyNode_ = arg_55.t1;
    return emptyNode_;
}

struct StringIntIntObjectSegNodeTag_Tuple5 segItemTypeToEmptyNode_1(struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 arg_56) {
    struct StringIntIntObjectSegNodeTag_Tuple5 emptyNode_ = arg_56.t1;
    return emptyNode_;
}

void* segItemTypeToNoChildren_1(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 arg_57) {
    void* noChildren_ = arg_57.t2;
    return noChildren_;
}

void* segItemTypeToNoChildren_2(struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 arg_58) {
    void* noChildren_ = arg_58.t2;
    return noChildren_;
}

int segItemTypeToEmptyItem_1(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_4) {
    struct IntIntIntObjectSegNodeTag_Tuple5 call_75 = segItemTypeToEmptyNode_2(itemTy_4);
    int call_76 = segNodeToItem_1(call_75);
    return call_76;
}

struct ObjectTuple1 {
    void* t0;
};

struct StringIntIntObjectSegNodeTag_Tuple5StringIntIntObjectSegNodeTag_Tuple5Tuple2 {
    struct StringIntIntObjectSegNodeTag_Tuple5 t0;
    struct StringIntIntObjectSegNodeTag_Tuple5 t1;
};

struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 segItemTypeNew_2(struct ObjectTuple1 arg_59, struct String emptyItem_, struct StringStringStringFun2 append_1) {
    void* unitObj_ = arg_59.t0;
    struct ObjectTuple1 tuple_21;
    tuple_21.t0 = unitObj_;
    struct StringIntIntObjectSegNodeTag_Tuple5 call_77 = segNodeNewEmpty_2(tuple_21, emptyItem_);
    struct StringIntIntObjectSegNodeTag_Tuple5 emptyNode_1 = call_77;
    struct String app_6 = append_1.fun(append_1.env, emptyItem_, emptyItem_);
    struct StringList* list_8 = (struct StringList*)malloc(sizeof(struct StringList));
    list_8->head = emptyItem_;
    list_8->tail = NULL;
    struct StringList* list_7 = (struct StringList*)malloc(sizeof(struct StringList));
    list_7->head = app_6;
    list_7->tail = list_8;
    int call_78 = listIsEmpty_1(list_7);
    milone_assert((!(call_78)));
    int call_79 = 0;
    struct StringIntIntObjectSegNodeTag_Tuple5StringIntIntObjectSegNodeTag_Tuple5Tuple2 tuple_23;
    tuple_23.t0 = emptyNode_1;
    tuple_23.t1 = emptyNode_1;
    void* box_1 = (void*)malloc(sizeof(struct StringIntIntObjectSegNodeTag_Tuple5StringIntIntObjectSegNodeTag_Tuple5Tuple2));
    (*(((struct StringIntIntObjectSegNodeTag_Tuple5StringIntIntObjectSegNodeTag_Tuple5Tuple2*)box_1))) = tuple_23;
    struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 tuple_22;
    tuple_22.t0 = append_1;
    tuple_22.t1 = emptyNode_1;
    tuple_22.t2 = box_1;
    tuple_22.t3 = (struct SegItemTypeTag_){.tag = SegItemTypeTag_};
    struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_5 = tuple_22;
    struct StringStringStringFun2 call_80 = segItemTypeToAppend_2(itemTy_5);
    struct StringStringStringFun2List* list_10 = (struct StringStringStringFun2List*)malloc(sizeof(struct StringStringStringFun2List));
    list_10->head = append_1;
    list_10->tail = NULL;
    struct StringStringStringFun2List* list_9 = (struct StringStringStringFun2List*)malloc(sizeof(struct StringStringStringFun2List));
    list_9->head = call_80;
    list_9->tail = list_10;
    int call_81 = listIsEmpty_5(list_9);
    milone_assert((!(call_81)));
    int call_82 = 0;
    return itemTy_5;
}

struct IntIntIntObjectSegNodeTag_Tuple5IntIntIntObjectSegNodeTag_Tuple5Tuple2 {
    struct IntIntIntObjectSegNodeTag_Tuple5 t0;
    struct IntIntIntObjectSegNodeTag_Tuple5 t1;
};

struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 segItemTypeNew_1(struct ObjectTuple1 arg_60, int emptyItem_, struct IntIntIntFun2 append_1) {
    void* unitObj_ = arg_60.t0;
    struct ObjectTuple1 tuple_24;
    tuple_24.t0 = unitObj_;
    struct IntIntIntObjectSegNodeTag_Tuple5 call_83 = segNodeNewEmpty_1(tuple_24, emptyItem_);
    struct IntIntIntObjectSegNodeTag_Tuple5 emptyNode_1 = call_83;
    int app_7 = append_1.fun(append_1.env, emptyItem_, emptyItem_);
    struct IntList* list_12 = (struct IntList*)malloc(sizeof(struct IntList));
    list_12->head = emptyItem_;
    list_12->tail = NULL;
    struct IntList* list_11 = (struct IntList*)malloc(sizeof(struct IntList));
    list_11->head = app_7;
    list_11->tail = list_12;
    int call_84 = listIsEmpty_4(list_11);
    milone_assert((!(call_84)));
    int call_85 = 0;
    struct IntIntIntObjectSegNodeTag_Tuple5IntIntIntObjectSegNodeTag_Tuple5Tuple2 tuple_26;
    tuple_26.t0 = emptyNode_1;
    tuple_26.t1 = emptyNode_1;
    void* box_2 = (void*)malloc(sizeof(struct IntIntIntObjectSegNodeTag_Tuple5IntIntIntObjectSegNodeTag_Tuple5Tuple2));
    (*(((struct IntIntIntObjectSegNodeTag_Tuple5IntIntIntObjectSegNodeTag_Tuple5Tuple2*)box_2))) = tuple_26;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 tuple_25;
    tuple_25.t0 = append_1;
    tuple_25.t1 = emptyNode_1;
    tuple_25.t2 = box_2;
    tuple_25.t3 = (struct SegItemTypeTag_){.tag = SegItemTypeTag_};
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_5 = tuple_25;
    struct IntIntIntFun2 call_86 = segItemTypeToAppend_1(itemTy_5);
    struct IntIntIntFun2List* list_14 = (struct IntIntIntFun2List*)malloc(sizeof(struct IntIntIntFun2List));
    list_14->head = append_1;
    list_14->tail = NULL;
    struct IntIntIntFun2List* list_13 = (struct IntIntIntFun2List*)malloc(sizeof(struct IntIntIntFun2List));
    list_13->head = call_86;
    list_13->tail = list_14;
    int call_87 = listIsEmpty_3(list_13);
    milone_assert((!(call_87)));
    int call_88 = 0;
    return itemTy_5;
}

struct StringIntIntObjectSegNodeTag_Tuple5 segNodeNewEmpty_2(struct ObjectTuple1 arg_61, struct String emptyItem_1) {
    void* unitObj_ = arg_61.t0;
    struct StringIntIntObjectSegNodeTag_Tuple5 tuple_27;
    tuple_27.t0 = emptyItem_1;
    tuple_27.t1 = 0;
    tuple_27.t2 = (0 - 1);
    tuple_27.t3 = unitObj_;
    tuple_27.t4 = (struct SegNodeTag_){.tag = SegNodeTag_};
    return tuple_27;
}

struct IntIntIntObjectSegNodeTag_Tuple5 segNodeNewEmpty_1(struct ObjectTuple1 arg_62, int emptyItem_1) {
    void* unitObj_ = arg_62.t0;
    struct IntIntIntObjectSegNodeTag_Tuple5 tuple_28;
    tuple_28.t0 = emptyItem_1;
    tuple_28.t1 = 0;
    tuple_28.t2 = (0 - 1);
    tuple_28.t3 = unitObj_;
    tuple_28.t4 = (struct SegNodeTag_){.tag = SegNodeTag_};
    return tuple_28;
}

struct IntIntIntObjectSegNodeTag_Tuple5 segNodeNewLeaf_1(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_6, int item_1) {
    void* call_89 = segItemTypeToNoChildren_1(itemTy_6);
    void* noChildren_1 = call_89;
    struct IntIntIntObjectSegNodeTag_Tuple5 tuple_29;
    tuple_29.t0 = item_1;
    tuple_29.t1 = 1;
    tuple_29.t2 = 0;
    tuple_29.t3 = noChildren_1;
    tuple_29.t4 = (struct SegNodeTag_){.tag = SegNodeTag_};
    return tuple_29;
}

struct StringIntIntObjectSegNodeTag_Tuple5 segNodeNewLeaf_2(struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_6, struct String item_1) {
    void* call_90 = segItemTypeToNoChildren_2(itemTy_6);
    void* noChildren_1 = call_90;
    struct StringIntIntObjectSegNodeTag_Tuple5 tuple_30;
    tuple_30.t0 = item_1;
    tuple_30.t1 = 1;
    tuple_30.t2 = 0;
    tuple_30.t3 = noChildren_1;
    tuple_30.t4 = (struct SegNodeTag_){.tag = SegNodeTag_};
    return tuple_30;
}

struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5IntIntIntObjectSegNodeTag_Tuple5Tuple3 {
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 t0;
    struct IntIntIntObjectSegNodeTag_Tuple5 t1;
    struct IntIntIntObjectSegNodeTag_Tuple5 t2;
};

struct IntIntIntObjectSegNodeTag_Tuple5 doNew_1(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5IntIntIntObjectSegNodeTag_Tuple5Tuple3 arg_63, int arg_64) {
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_7 = arg_63.t0;
    struct IntIntIntObjectSegNodeTag_Tuple5 left_ = arg_63.t1;
    struct IntIntIntObjectSegNodeTag_Tuple5 right_ = arg_63.t2;
    int leftItem_ = left_.t0;
    int leftLen_ = left_.t1;
    int leftHeight_ = left_.t2;
    int rightItem_ = right_.t0;
    int rightLen_ = right_.t1;
    int rightHeight_ = right_.t2;
    int match_25;
    if (!(((1 <= leftLen_) == 1))) goto next_81;
    match_25 = (1 <= rightLen_);
    goto end_match_80;
next_81:;
    if (!(((1 <= leftLen_) == 0))) goto next_82;
    match_25 = 0;
    goto end_match_80;
next_82:;
    exit(1);
end_match_80:;
    milone_assert(match_25);
    int call_91 = 0;
    struct IntIntIntFun2 call_92 = segItemTypeToAppend_1(itemTy_7);
    int app_8 = call_92.fun(call_92.env, leftItem_, rightItem_);
    int item_2 = app_8;
    int len_11 = (leftLen_ + rightLen_);
    int call_93 = intMax_(leftHeight_, rightHeight_);
    int height_ = (1 + call_93);
    struct IntIntIntObjectSegNodeTag_Tuple5IntIntIntObjectSegNodeTag_Tuple5Tuple2 tuple_32;
    tuple_32.t0 = left_;
    tuple_32.t1 = right_;
    void* box_3 = (void*)malloc(sizeof(struct IntIntIntObjectSegNodeTag_Tuple5IntIntIntObjectSegNodeTag_Tuple5Tuple2));
    (*(((struct IntIntIntObjectSegNodeTag_Tuple5IntIntIntObjectSegNodeTag_Tuple5Tuple2*)box_3))) = tuple_32;
    struct IntIntIntObjectSegNodeTag_Tuple5 tuple_31;
    tuple_31.t0 = item_2;
    tuple_31.t1 = len_11;
    tuple_31.t2 = height_;
    tuple_31.t3 = box_3;
    tuple_31.t4 = (struct SegNodeTag_){.tag = SegNodeTag_};
    return tuple_31;
}

struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4StringIntIntObjectSegNodeTag_Tuple5StringIntIntObjectSegNodeTag_Tuple5Tuple3 {
    struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 t0;
    struct StringIntIntObjectSegNodeTag_Tuple5 t1;
    struct StringIntIntObjectSegNodeTag_Tuple5 t2;
};

struct StringIntIntObjectSegNodeTag_Tuple5 doNew_2(struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4StringIntIntObjectSegNodeTag_Tuple5StringIntIntObjectSegNodeTag_Tuple5Tuple3 arg_65, int arg_66) {
    struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_7 = arg_65.t0;
    struct StringIntIntObjectSegNodeTag_Tuple5 left_ = arg_65.t1;
    struct StringIntIntObjectSegNodeTag_Tuple5 right_ = arg_65.t2;
    struct String leftItem_ = left_.t0;
    int leftLen_ = left_.t1;
    int leftHeight_ = left_.t2;
    struct String rightItem_ = right_.t0;
    int rightLen_ = right_.t1;
    int rightHeight_ = right_.t2;
    int match_26;
    if (!(((1 <= leftLen_) == 1))) goto next_84;
    match_26 = (1 <= rightLen_);
    goto end_match_83;
next_84:;
    if (!(((1 <= leftLen_) == 0))) goto next_85;
    match_26 = 0;
    goto end_match_83;
next_85:;
    exit(1);
end_match_83:;
    milone_assert(match_26);
    int call_94 = 0;
    struct StringStringStringFun2 call_95 = segItemTypeToAppend_2(itemTy_7);
    struct String app_9 = call_95.fun(call_95.env, leftItem_, rightItem_);
    struct String item_2 = app_9;
    int len_11 = (leftLen_ + rightLen_);
    int call_96 = intMax_(leftHeight_, rightHeight_);
    int height_ = (1 + call_96);
    struct StringIntIntObjectSegNodeTag_Tuple5StringIntIntObjectSegNodeTag_Tuple5Tuple2 tuple_34;
    tuple_34.t0 = left_;
    tuple_34.t1 = right_;
    void* box_4 = (void*)malloc(sizeof(struct StringIntIntObjectSegNodeTag_Tuple5StringIntIntObjectSegNodeTag_Tuple5Tuple2));
    (*(((struct StringIntIntObjectSegNodeTag_Tuple5StringIntIntObjectSegNodeTag_Tuple5Tuple2*)box_4))) = tuple_34;
    struct StringIntIntObjectSegNodeTag_Tuple5 tuple_33;
    tuple_33.t0 = item_2;
    tuple_33.t1 = len_11;
    tuple_33.t2 = height_;
    tuple_33.t3 = box_4;
    tuple_33.t4 = (struct SegNodeTag_){.tag = SegNodeTag_};
    return tuple_33;
}

struct IntIntIntObjectSegNodeTag_Tuple5 segNodeNew_1(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_7, struct IntIntIntObjectSegNodeTag_Tuple5 left_, struct IntIntIntObjectSegNodeTag_Tuple5 right_) {
    struct IntIntIntObjectSegNodeTag_Tuple5 match_27;
    int call_97 = segNodeToLength_1(left_);
    int call_98 = segNodeToLength_1(right_);
    struct IntIntTuple2 tuple_35;
    tuple_35.t0 = call_97;
    tuple_35.t1 = call_98;
    if (!((tuple_35.t0 == 0))) goto next_87;
    if (!((tuple_35.t1 == 0))) goto next_87;
    struct IntIntIntObjectSegNodeTag_Tuple5 call_99 = segItemTypeToEmptyNode_2(itemTy_7);
    match_27 = call_99;
    goto end_match_86;
next_87:;
    if (!((tuple_35.t0 == 0))) goto next_88;
    match_27 = right_;
    goto end_match_86;
next_88:;
    if (!((tuple_35.t1 == 0))) goto next_89;
    match_27 = left_;
    goto end_match_86;
next_89:;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5IntIntIntObjectSegNodeTag_Tuple5Tuple3 tuple_36;
    tuple_36.t0 = itemTy_7;
    tuple_36.t1 = left_;
    tuple_36.t2 = right_;
    struct IntIntIntObjectSegNodeTag_Tuple5 call_100 = doNew_1(tuple_36, 0);
    match_27 = call_100;
    goto end_match_86;
next_90:;
end_match_86:;
    return match_27;
}

struct StringIntIntObjectSegNodeTag_Tuple5 segNodeNew_2(struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_7, struct StringIntIntObjectSegNodeTag_Tuple5 left_, struct StringIntIntObjectSegNodeTag_Tuple5 right_) {
    struct StringIntIntObjectSegNodeTag_Tuple5 match_28;
    int call_101 = segNodeToLength_2(left_);
    int call_102 = segNodeToLength_2(right_);
    struct IntIntTuple2 tuple_37;
    tuple_37.t0 = call_101;
    tuple_37.t1 = call_102;
    if (!((tuple_37.t0 == 0))) goto next_92;
    if (!((tuple_37.t1 == 0))) goto next_92;
    struct StringIntIntObjectSegNodeTag_Tuple5 call_103 = segItemTypeToEmptyNode_1(itemTy_7);
    match_28 = call_103;
    goto end_match_91;
next_92:;
    if (!((tuple_37.t0 == 0))) goto next_93;
    match_28 = right_;
    goto end_match_91;
next_93:;
    if (!((tuple_37.t1 == 0))) goto next_94;
    match_28 = left_;
    goto end_match_91;
next_94:;
    struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4StringIntIntObjectSegNodeTag_Tuple5StringIntIntObjectSegNodeTag_Tuple5Tuple3 tuple_38;
    tuple_38.t0 = itemTy_7;
    tuple_38.t1 = left_;
    tuple_38.t2 = right_;
    struct StringIntIntObjectSegNodeTag_Tuple5 call_104 = doNew_2(tuple_38, 0);
    match_28 = call_104;
    goto end_match_91;
next_95:;
end_match_91:;
    return match_28;
}

int segNodeToItem_1(struct IntIntIntObjectSegNodeTag_Tuple5 node_) {
    int item_3 = node_.t0;
    return item_3;
}

int segNodeToLength_1(struct IntIntIntObjectSegNodeTag_Tuple5 node_1) {
    int len_12 = node_1.t1;
    return len_12;
}

int segNodeToLength_2(struct StringIntIntObjectSegNodeTag_Tuple5 node_1) {
    int len_12 = node_1.t1;
    return len_12;
}

int segNodeToHeight_1(struct IntIntIntObjectSegNodeTag_Tuple5 node_2) {
    int height_1 = node_2.t2;
    return height_1;
}

int segNodeToHeight_2(struct StringIntIntObjectSegNodeTag_Tuple5 node_2) {
    int height_1 = node_2.t2;
    return height_1;
}

struct IntIntIntObjectSegNodeTag_Tuple5IntIntIntObjectSegNodeTag_Tuple5Tuple2 segNodeToChildren_1(struct IntIntIntObjectSegNodeTag_Tuple5 node_3) {
    int len_13 = node_3.t1;
    void* children_ = node_3.t3;
    milone_assert((2 <= len_13));
    int call_105 = 0;
    struct IntIntIntObjectSegNodeTag_Tuple5 left_1 = (*(((struct IntIntIntObjectSegNodeTag_Tuple5IntIntIntObjectSegNodeTag_Tuple5Tuple2*)children_))).t0;
    struct IntIntIntObjectSegNodeTag_Tuple5 right_1 = (*(((struct IntIntIntObjectSegNodeTag_Tuple5IntIntIntObjectSegNodeTag_Tuple5Tuple2*)children_))).t1;
    struct IntIntIntObjectSegNodeTag_Tuple5List* list_17 = (struct IntIntIntObjectSegNodeTag_Tuple5List*)malloc(sizeof(struct IntIntIntObjectSegNodeTag_Tuple5List));
    list_17->head = right_1;
    list_17->tail = NULL;
    struct IntIntIntObjectSegNodeTag_Tuple5List* list_16 = (struct IntIntIntObjectSegNodeTag_Tuple5List*)malloc(sizeof(struct IntIntIntObjectSegNodeTag_Tuple5List));
    list_16->head = left_1;
    list_16->tail = list_17;
    struct IntIntIntObjectSegNodeTag_Tuple5List* list_15 = (struct IntIntIntObjectSegNodeTag_Tuple5List*)malloc(sizeof(struct IntIntIntObjectSegNodeTag_Tuple5List));
    list_15->head = node_3;
    list_15->tail = list_16;
    int call_106 = listIsEmpty_2(list_15);
    milone_assert((!(call_106)));
    int call_107 = 0;
    struct IntIntIntObjectSegNodeTag_Tuple5IntIntIntObjectSegNodeTag_Tuple5Tuple2 tuple_39;
    tuple_39.t0 = left_1;
    tuple_39.t1 = right_1;
    return tuple_39;
}

struct StringIntIntObjectSegNodeTag_Tuple5StringIntIntObjectSegNodeTag_Tuple5Tuple2 segNodeToChildren_2(struct StringIntIntObjectSegNodeTag_Tuple5 node_3) {
    int len_13 = node_3.t1;
    void* children_ = node_3.t3;
    milone_assert((2 <= len_13));
    int call_108 = 0;
    struct StringIntIntObjectSegNodeTag_Tuple5 left_1 = (*(((struct StringIntIntObjectSegNodeTag_Tuple5StringIntIntObjectSegNodeTag_Tuple5Tuple2*)children_))).t0;
    struct StringIntIntObjectSegNodeTag_Tuple5 right_1 = (*(((struct StringIntIntObjectSegNodeTag_Tuple5StringIntIntObjectSegNodeTag_Tuple5Tuple2*)children_))).t1;
    struct StringIntIntObjectSegNodeTag_Tuple5List* list_20 = (struct StringIntIntObjectSegNodeTag_Tuple5List*)malloc(sizeof(struct StringIntIntObjectSegNodeTag_Tuple5List));
    list_20->head = right_1;
    list_20->tail = NULL;
    struct StringIntIntObjectSegNodeTag_Tuple5List* list_19 = (struct StringIntIntObjectSegNodeTag_Tuple5List*)malloc(sizeof(struct StringIntIntObjectSegNodeTag_Tuple5List));
    list_19->head = left_1;
    list_19->tail = list_20;
    struct StringIntIntObjectSegNodeTag_Tuple5List* list_18 = (struct StringIntIntObjectSegNodeTag_Tuple5List*)malloc(sizeof(struct StringIntIntObjectSegNodeTag_Tuple5List));
    list_18->head = node_3;
    list_18->tail = list_19;
    int call_109 = listIsEmpty_6(list_18);
    milone_assert((!(call_109)));
    int call_110 = 0;
    struct StringIntIntObjectSegNodeTag_Tuple5StringIntIntObjectSegNodeTag_Tuple5Tuple2 tuple_40;
    tuple_40.t0 = left_1;
    tuple_40.t1 = right_1;
    return tuple_40;
}

int segNodeIsEmpty_1(struct IntIntIntObjectSegNodeTag_Tuple5 node_4) {
    int call_111 = segNodeToLength_1(node_4);
    return (call_111 == 0);
}

struct IntIntIntObjectSegNodeTag_Tuple5 segNodeWithLeft_1(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_8, struct IntIntIntObjectSegNodeTag_Tuple5 newLeft_, struct IntIntIntObjectSegNodeTag_Tuple5 node_5) {
    int call_112 = segNodeToLength_1(node_5);
    milone_assert((1 <= call_112));
    int call_113 = 0;
    struct IntIntIntObjectSegNodeTag_Tuple5IntIntIntObjectSegNodeTag_Tuple5Tuple2 call_114 = segNodeToChildren_1(node_5);
    struct IntIntIntObjectSegNodeTag_Tuple5 right_2 = call_114.t1;
    struct IntIntIntObjectSegNodeTag_Tuple5 call_115 = segNodeNew_1(itemTy_8, newLeft_, right_2);
    return call_115;
}

struct StringIntIntObjectSegNodeTag_Tuple5 segNodeWithLeft_2(struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_8, struct StringIntIntObjectSegNodeTag_Tuple5 newLeft_, struct StringIntIntObjectSegNodeTag_Tuple5 node_5) {
    int call_116 = segNodeToLength_2(node_5);
    milone_assert((1 <= call_116));
    int call_117 = 0;
    struct StringIntIntObjectSegNodeTag_Tuple5StringIntIntObjectSegNodeTag_Tuple5Tuple2 call_118 = segNodeToChildren_2(node_5);
    struct StringIntIntObjectSegNodeTag_Tuple5 right_2 = call_118.t1;
    struct StringIntIntObjectSegNodeTag_Tuple5 call_119 = segNodeNew_2(itemTy_8, newLeft_, right_2);
    return call_119;
}

struct IntIntIntObjectSegNodeTag_Tuple5 segNodeWithRight_1(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_9, struct IntIntIntObjectSegNodeTag_Tuple5 newRight_, struct IntIntIntObjectSegNodeTag_Tuple5 node_6) {
    int call_120 = segNodeToLength_1(node_6);
    milone_assert((1 <= call_120));
    int call_121 = 0;
    struct IntIntIntObjectSegNodeTag_Tuple5IntIntIntObjectSegNodeTag_Tuple5Tuple2 call_122 = segNodeToChildren_1(node_6);
    struct IntIntIntObjectSegNodeTag_Tuple5 left_2 = call_122.t0;
    struct IntIntIntObjectSegNodeTag_Tuple5 call_123 = segNodeNew_1(itemTy_9, left_2, newRight_);
    return call_123;
}

struct StringIntIntObjectSegNodeTag_Tuple5 segNodeWithRight_2(struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_9, struct StringIntIntObjectSegNodeTag_Tuple5 newRight_, struct StringIntIntObjectSegNodeTag_Tuple5 node_6) {
    int call_124 = segNodeToLength_2(node_6);
    milone_assert((1 <= call_124));
    int call_125 = 0;
    struct StringIntIntObjectSegNodeTag_Tuple5StringIntIntObjectSegNodeTag_Tuple5Tuple2 call_126 = segNodeToChildren_2(node_6);
    struct StringIntIntObjectSegNodeTag_Tuple5 left_2 = call_126.t0;
    struct StringIntIntObjectSegNodeTag_Tuple5 call_127 = segNodeNew_2(itemTy_9, left_2, newRight_);
    return call_127;
}

struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 {
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 t0;
};

struct IntIntIntObjectSegNodeTag_Tuple5 rotateLeft_1(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 arg_67, struct IntIntIntObjectSegNodeTag_Tuple5 node_8) {
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_10 = arg_67.t0;
    struct IntIntIntObjectSegNodeTag_Tuple5 match_29;
    int call_128 = segNodeToLength_1(node_8);
    if (!(((call_128 < 2) == 1))) goto next_97;
    match_29 = node_8;
    goto end_match_96;
next_97:;
    if (!(((call_128 < 2) == 0))) goto next_98;
    struct IntIntIntObjectSegNodeTag_Tuple5IntIntIntObjectSegNodeTag_Tuple5Tuple2 call_129 = segNodeToChildren_1(node_8);
    struct IntIntIntObjectSegNodeTag_Tuple5 right_3 = call_129.t1;
    struct IntIntIntObjectSegNodeTag_Tuple5 match_30;
    int call_130 = segNodeToLength_1(right_3);
    if (!(((call_130 < 2) == 1))) goto next_100;
    match_30 = node_8;
    goto end_match_99;
next_100:;
    if (!(((call_130 < 2) == 0))) goto next_101;
    struct IntIntIntObjectSegNodeTag_Tuple5IntIntIntObjectSegNodeTag_Tuple5Tuple2 call_131 = segNodeToChildren_1(right_3);
    struct IntIntIntObjectSegNodeTag_Tuple5 x_5 = call_131.t0;
    struct IntIntIntObjectSegNodeTag_Tuple5 call_132 = segNodeWithRight_1(itemTy_10, x_5, node_8);
    struct IntIntIntObjectSegNodeTag_Tuple5 u_ = call_132;
    struct IntIntIntObjectSegNodeTag_Tuple5 call_133 = segNodeWithLeft_1(itemTy_10, u_, right_3);
    struct IntIntIntObjectSegNodeTag_Tuple5 t_ = call_133;
    match_30 = t_;
    goto end_match_99;
next_101:;
    exit(1);
end_match_99:;
    match_29 = match_30;
    goto end_match_96;
next_98:;
    exit(1);
end_match_96:;
    return match_29;
}

struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 {
    struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 t0;
};

struct StringIntIntObjectSegNodeTag_Tuple5 rotateLeft_2(struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 arg_68, struct StringIntIntObjectSegNodeTag_Tuple5 node_8) {
    struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_10 = arg_68.t0;
    struct StringIntIntObjectSegNodeTag_Tuple5 match_31;
    int call_134 = segNodeToLength_2(node_8);
    if (!(((call_134 < 2) == 1))) goto next_103;
    match_31 = node_8;
    goto end_match_102;
next_103:;
    if (!(((call_134 < 2) == 0))) goto next_104;
    struct StringIntIntObjectSegNodeTag_Tuple5StringIntIntObjectSegNodeTag_Tuple5Tuple2 call_135 = segNodeToChildren_2(node_8);
    struct StringIntIntObjectSegNodeTag_Tuple5 right_3 = call_135.t1;
    struct StringIntIntObjectSegNodeTag_Tuple5 match_32;
    int call_136 = segNodeToLength_2(right_3);
    if (!(((call_136 < 2) == 1))) goto next_106;
    match_32 = node_8;
    goto end_match_105;
next_106:;
    if (!(((call_136 < 2) == 0))) goto next_107;
    struct StringIntIntObjectSegNodeTag_Tuple5StringIntIntObjectSegNodeTag_Tuple5Tuple2 call_137 = segNodeToChildren_2(right_3);
    struct StringIntIntObjectSegNodeTag_Tuple5 x_5 = call_137.t0;
    struct StringIntIntObjectSegNodeTag_Tuple5 call_138 = segNodeWithRight_2(itemTy_10, x_5, node_8);
    struct StringIntIntObjectSegNodeTag_Tuple5 u_ = call_138;
    struct StringIntIntObjectSegNodeTag_Tuple5 call_139 = segNodeWithLeft_2(itemTy_10, u_, right_3);
    struct StringIntIntObjectSegNodeTag_Tuple5 t_ = call_139;
    match_32 = t_;
    goto end_match_105;
next_107:;
    exit(1);
end_match_105:;
    match_31 = match_32;
    goto end_match_102;
next_104:;
    exit(1);
end_match_102:;
    return match_31;
}

struct IntIntIntObjectSegNodeTag_Tuple5 rotateRight_1(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 arg_69, struct IntIntIntObjectSegNodeTag_Tuple5 node_9) {
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_10 = arg_69.t0;
    struct IntIntIntObjectSegNodeTag_Tuple5 match_33;
    int call_140 = segNodeToLength_1(node_9);
    if (!(((call_140 < 2) == 1))) goto next_109;
    match_33 = node_9;
    goto end_match_108;
next_109:;
    if (!(((call_140 < 2) == 0))) goto next_110;
    struct IntIntIntObjectSegNodeTag_Tuple5IntIntIntObjectSegNodeTag_Tuple5Tuple2 call_141 = segNodeToChildren_1(node_9);
    struct IntIntIntObjectSegNodeTag_Tuple5 left_3 = call_141.t0;
    struct IntIntIntObjectSegNodeTag_Tuple5 match_34;
    int call_142 = segNodeToLength_1(left_3);
    if (!(((call_142 < 2) == 1))) goto next_112;
    match_34 = node_9;
    goto end_match_111;
next_112:;
    if (!(((call_142 < 2) == 0))) goto next_113;
    struct IntIntIntObjectSegNodeTag_Tuple5IntIntIntObjectSegNodeTag_Tuple5Tuple2 call_143 = segNodeToChildren_1(left_3);
    struct IntIntIntObjectSegNodeTag_Tuple5 y_2 = call_143.t1;
    struct IntIntIntObjectSegNodeTag_Tuple5 call_144 = segNodeWithLeft_1(itemTy_10, y_2, node_9);
    struct IntIntIntObjectSegNodeTag_Tuple5 u_1 = call_144;
    struct IntIntIntObjectSegNodeTag_Tuple5 call_145 = segNodeWithRight_1(itemTy_10, u_1, left_3);
    struct IntIntIntObjectSegNodeTag_Tuple5 t_1 = call_145;
    match_34 = t_1;
    goto end_match_111;
next_113:;
    exit(1);
end_match_111:;
    match_33 = match_34;
    goto end_match_108;
next_110:;
    exit(1);
end_match_108:;
    return match_33;
}

struct StringIntIntObjectSegNodeTag_Tuple5 rotateRight_2(struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 arg_70, struct StringIntIntObjectSegNodeTag_Tuple5 node_9) {
    struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_10 = arg_70.t0;
    struct StringIntIntObjectSegNodeTag_Tuple5 match_35;
    int call_146 = segNodeToLength_2(node_9);
    if (!(((call_146 < 2) == 1))) goto next_115;
    match_35 = node_9;
    goto end_match_114;
next_115:;
    if (!(((call_146 < 2) == 0))) goto next_116;
    struct StringIntIntObjectSegNodeTag_Tuple5StringIntIntObjectSegNodeTag_Tuple5Tuple2 call_147 = segNodeToChildren_2(node_9);
    struct StringIntIntObjectSegNodeTag_Tuple5 left_3 = call_147.t0;
    struct StringIntIntObjectSegNodeTag_Tuple5 match_36;
    int call_148 = segNodeToLength_2(left_3);
    if (!(((call_148 < 2) == 1))) goto next_118;
    match_36 = node_9;
    goto end_match_117;
next_118:;
    if (!(((call_148 < 2) == 0))) goto next_119;
    struct StringIntIntObjectSegNodeTag_Tuple5StringIntIntObjectSegNodeTag_Tuple5Tuple2 call_149 = segNodeToChildren_2(left_3);
    struct StringIntIntObjectSegNodeTag_Tuple5 y_2 = call_149.t1;
    struct StringIntIntObjectSegNodeTag_Tuple5 call_150 = segNodeWithLeft_2(itemTy_10, y_2, node_9);
    struct StringIntIntObjectSegNodeTag_Tuple5 u_1 = call_150;
    struct StringIntIntObjectSegNodeTag_Tuple5 call_151 = segNodeWithRight_2(itemTy_10, u_1, left_3);
    struct StringIntIntObjectSegNodeTag_Tuple5 t_1 = call_151;
    match_36 = t_1;
    goto end_match_117;
next_119:;
    exit(1);
end_match_117:;
    match_35 = match_36;
    goto end_match_114;
next_116:;
    exit(1);
end_match_114:;
    return match_35;
}

struct IntIntIntObjectSegNodeTag_Tuple5 doubleLeft_1(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 arg_71, struct IntIntIntObjectSegNodeTag_Tuple5 node_10) {
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_10 = arg_71.t0;
    struct IntIntIntObjectSegNodeTag_Tuple5 match_37;
    int call_152 = segNodeToLength_1(node_10);
    if (!(((call_152 < 2) == 1))) goto next_121;
    match_37 = node_10;
    goto end_match_120;
next_121:;
    if (!(((call_152 < 2) == 0))) goto next_122;
    struct IntIntIntObjectSegNodeTag_Tuple5IntIntIntObjectSegNodeTag_Tuple5Tuple2 call_153 = segNodeToChildren_1(node_10);
    struct IntIntIntObjectSegNodeTag_Tuple5 right_4 = call_153.t1;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 tuple_41;
    tuple_41.t0 = itemTy_10;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 tuple_42;
    tuple_42.t0 = itemTy_10;
    struct IntIntIntObjectSegNodeTag_Tuple5 call_154 = rotateRight_1(tuple_42, right_4);
    struct IntIntIntObjectSegNodeTag_Tuple5 call_155 = segNodeWithRight_1(itemTy_10, call_154, node_10);
    struct IntIntIntObjectSegNodeTag_Tuple5 call_156 = rotateLeft_1(tuple_41, call_155);
    match_37 = call_156;
    goto end_match_120;
next_122:;
    exit(1);
end_match_120:;
    return match_37;
}

struct StringIntIntObjectSegNodeTag_Tuple5 doubleLeft_2(struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 arg_72, struct StringIntIntObjectSegNodeTag_Tuple5 node_10) {
    struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_10 = arg_72.t0;
    struct StringIntIntObjectSegNodeTag_Tuple5 match_38;
    int call_157 = segNodeToLength_2(node_10);
    if (!(((call_157 < 2) == 1))) goto next_124;
    match_38 = node_10;
    goto end_match_123;
next_124:;
    if (!(((call_157 < 2) == 0))) goto next_125;
    struct StringIntIntObjectSegNodeTag_Tuple5StringIntIntObjectSegNodeTag_Tuple5Tuple2 call_158 = segNodeToChildren_2(node_10);
    struct StringIntIntObjectSegNodeTag_Tuple5 right_4 = call_158.t1;
    struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 tuple_43;
    tuple_43.t0 = itemTy_10;
    struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 tuple_44;
    tuple_44.t0 = itemTy_10;
    struct StringIntIntObjectSegNodeTag_Tuple5 call_159 = rotateRight_2(tuple_44, right_4);
    struct StringIntIntObjectSegNodeTag_Tuple5 call_160 = segNodeWithRight_2(itemTy_10, call_159, node_10);
    struct StringIntIntObjectSegNodeTag_Tuple5 call_161 = rotateLeft_2(tuple_43, call_160);
    match_38 = call_161;
    goto end_match_123;
next_125:;
    exit(1);
end_match_123:;
    return match_38;
}

struct IntIntIntObjectSegNodeTag_Tuple5 doubleRight_1(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 arg_73, struct IntIntIntObjectSegNodeTag_Tuple5 node_11) {
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_10 = arg_73.t0;
    struct IntIntIntObjectSegNodeTag_Tuple5 match_39;
    int call_162 = segNodeToLength_1(node_11);
    if (!(((call_162 < 2) == 1))) goto next_127;
    match_39 = node_11;
    goto end_match_126;
next_127:;
    if (!(((call_162 < 2) == 0))) goto next_128;
    struct IntIntIntObjectSegNodeTag_Tuple5IntIntIntObjectSegNodeTag_Tuple5Tuple2 call_163 = segNodeToChildren_1(node_11);
    struct IntIntIntObjectSegNodeTag_Tuple5 left_4 = call_163.t0;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 tuple_45;
    tuple_45.t0 = itemTy_10;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 tuple_46;
    tuple_46.t0 = itemTy_10;
    struct IntIntIntObjectSegNodeTag_Tuple5 call_164 = rotateLeft_1(tuple_46, left_4);
    struct IntIntIntObjectSegNodeTag_Tuple5 call_165 = segNodeWithLeft_1(itemTy_10, call_164, node_11);
    struct IntIntIntObjectSegNodeTag_Tuple5 call_166 = rotateRight_1(tuple_45, call_165);
    match_39 = call_166;
    goto end_match_126;
next_128:;
    exit(1);
end_match_126:;
    return match_39;
}

struct StringIntIntObjectSegNodeTag_Tuple5 doubleRight_2(struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 arg_74, struct StringIntIntObjectSegNodeTag_Tuple5 node_11) {
    struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_10 = arg_74.t0;
    struct StringIntIntObjectSegNodeTag_Tuple5 match_40;
    int call_167 = segNodeToLength_2(node_11);
    if (!(((call_167 < 2) == 1))) goto next_130;
    match_40 = node_11;
    goto end_match_129;
next_130:;
    if (!(((call_167 < 2) == 0))) goto next_131;
    struct StringIntIntObjectSegNodeTag_Tuple5StringIntIntObjectSegNodeTag_Tuple5Tuple2 call_168 = segNodeToChildren_2(node_11);
    struct StringIntIntObjectSegNodeTag_Tuple5 left_4 = call_168.t0;
    struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 tuple_47;
    tuple_47.t0 = itemTy_10;
    struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 tuple_48;
    tuple_48.t0 = itemTy_10;
    struct StringIntIntObjectSegNodeTag_Tuple5 call_169 = rotateLeft_2(tuple_48, left_4);
    struct StringIntIntObjectSegNodeTag_Tuple5 call_170 = segNodeWithLeft_2(itemTy_10, call_169, node_11);
    struct StringIntIntObjectSegNodeTag_Tuple5 call_171 = rotateRight_2(tuple_47, call_170);
    match_40 = call_171;
    goto end_match_129;
next_131:;
    exit(1);
end_match_129:;
    return match_40;
}

int toBalance_1(struct IntIntIntObjectSegNodeTag_Tuple5 node_12) {
    int match_41;
    int call_172 = segNodeToLength_1(node_12);
    if (!(((call_172 < 2) == 1))) goto next_133;
    match_41 = 0;
    goto end_match_132;
next_133:;
    if (!(((call_172 < 2) == 0))) goto next_134;
    struct IntIntIntObjectSegNodeTag_Tuple5IntIntIntObjectSegNodeTag_Tuple5Tuple2 call_173 = segNodeToChildren_1(node_12);
    struct IntIntIntObjectSegNodeTag_Tuple5 left_5 = call_173.t0;
    struct IntIntIntObjectSegNodeTag_Tuple5 right_5 = call_173.t1;
    int call_174 = segNodeToHeight_1(right_5);
    int call_175 = segNodeToHeight_1(left_5);
    match_41 = (call_174 - call_175);
    goto end_match_132;
next_134:;
    exit(1);
end_match_132:;
    return match_41;
}

int toBalance_2(struct StringIntIntObjectSegNodeTag_Tuple5 node_12) {
    int match_42;
    int call_176 = segNodeToLength_2(node_12);
    if (!(((call_176 < 2) == 1))) goto next_136;
    match_42 = 0;
    goto end_match_135;
next_136:;
    if (!(((call_176 < 2) == 0))) goto next_137;
    struct StringIntIntObjectSegNodeTag_Tuple5StringIntIntObjectSegNodeTag_Tuple5Tuple2 call_177 = segNodeToChildren_2(node_12);
    struct StringIntIntObjectSegNodeTag_Tuple5 left_5 = call_177.t0;
    struct StringIntIntObjectSegNodeTag_Tuple5 right_5 = call_177.t1;
    int call_178 = segNodeToHeight_2(right_5);
    int call_179 = segNodeToHeight_2(left_5);
    match_42 = (call_178 - call_179);
    goto end_match_135;
next_137:;
    exit(1);
end_match_135:;
    return match_42;
}

struct IntIntIntObjectSegNodeTag_Tuple5 segNodeMakeBalanced_1(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_10, struct IntIntIntObjectSegNodeTag_Tuple5 node_7) {
    int call_180 = toBalance_1(node_7);
    int selfBalance_ = call_180;
    struct IntIntIntObjectSegNodeTag_Tuple5 match_43;
    int match_44;
    if (!((((0 - 1) <= selfBalance_) == 1))) goto next_140;
    match_44 = (selfBalance_ <= 1);
    goto end_match_139;
next_140:;
    if (!((((0 - 1) <= selfBalance_) == 0))) goto next_141;
    match_44 = 0;
    goto end_match_139;
next_141:;
    exit(1);
end_match_139:;
    if (!((match_44 == 1))) goto next_142;
    match_43 = node_7;
    goto end_match_138;
next_142:;
    if (!((match_44 == 0))) goto next_143;
    struct IntIntIntObjectSegNodeTag_Tuple5 match_45;
    int call_181 = segNodeToLength_1(node_7);
    if (!(((call_181 < 2) == 1))) goto next_145;
    match_45 = node_7;
    goto end_match_144;
next_145:;
    if (!(((call_181 < 2) == 0))) goto next_146;
    struct IntIntIntObjectSegNodeTag_Tuple5IntIntIntObjectSegNodeTag_Tuple5Tuple2 call_182 = segNodeToChildren_1(node_7);
    struct IntIntIntObjectSegNodeTag_Tuple5 left_6 = call_182.t0;
    struct IntIntIntObjectSegNodeTag_Tuple5 right_6 = call_182.t1;
    struct IntIntIntObjectSegNodeTag_Tuple5 match_46;
    if (!(((2 <= selfBalance_) == 1))) goto next_148;
    struct IntIntIntObjectSegNodeTag_Tuple5 match_47;
    int call_183 = toBalance_1(right_6);
    if (!(((call_183 < 0) == 1))) goto next_151;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 tuple_49;
    tuple_49.t0 = itemTy_10;
    struct IntIntIntObjectSegNodeTag_Tuple5 call_184 = doubleLeft_1(tuple_49, node_7);
    match_47 = call_184;
    goto end_match_150;
next_151:;
    if (!(((call_183 < 0) == 0))) goto next_152;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 tuple_50;
    tuple_50.t0 = itemTy_10;
    struct IntIntIntObjectSegNodeTag_Tuple5 call_185 = rotateLeft_1(tuple_50, node_7);
    match_47 = call_185;
    goto end_match_150;
next_152:;
    exit(1);
end_match_150:;
    match_46 = match_47;
    goto end_match_147;
next_148:;
    if (!(((2 <= selfBalance_) == 0))) goto next_149;
    struct IntIntIntObjectSegNodeTag_Tuple5 match_48;
    int call_186 = toBalance_1(left_6);
    if (!(((0 < call_186) == 1))) goto next_154;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 tuple_51;
    tuple_51.t0 = itemTy_10;
    struct IntIntIntObjectSegNodeTag_Tuple5 call_187 = doubleRight_1(tuple_51, node_7);
    match_48 = call_187;
    goto end_match_153;
next_154:;
    if (!(((0 < call_186) == 0))) goto next_155;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 tuple_52;
    tuple_52.t0 = itemTy_10;
    struct IntIntIntObjectSegNodeTag_Tuple5 call_188 = rotateRight_1(tuple_52, node_7);
    match_48 = call_188;
    goto end_match_153;
next_155:;
    exit(1);
end_match_153:;
    match_46 = match_48;
    goto end_match_147;
next_149:;
    exit(1);
end_match_147:;
    match_45 = match_46;
    goto end_match_144;
next_146:;
    exit(1);
end_match_144:;
    match_43 = match_45;
    goto end_match_138;
next_143:;
    exit(1);
end_match_138:;
    return match_43;
}

struct StringIntIntObjectSegNodeTag_Tuple5 segNodeMakeBalanced_2(struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_10, struct StringIntIntObjectSegNodeTag_Tuple5 node_7) {
    int call_189 = toBalance_2(node_7);
    int selfBalance_ = call_189;
    struct StringIntIntObjectSegNodeTag_Tuple5 match_49;
    int match_50;
    if (!((((0 - 1) <= selfBalance_) == 1))) goto next_158;
    match_50 = (selfBalance_ <= 1);
    goto end_match_157;
next_158:;
    if (!((((0 - 1) <= selfBalance_) == 0))) goto next_159;
    match_50 = 0;
    goto end_match_157;
next_159:;
    exit(1);
end_match_157:;
    if (!((match_50 == 1))) goto next_160;
    match_49 = node_7;
    goto end_match_156;
next_160:;
    if (!((match_50 == 0))) goto next_161;
    struct StringIntIntObjectSegNodeTag_Tuple5 match_51;
    int call_190 = segNodeToLength_2(node_7);
    if (!(((call_190 < 2) == 1))) goto next_163;
    match_51 = node_7;
    goto end_match_162;
next_163:;
    if (!(((call_190 < 2) == 0))) goto next_164;
    struct StringIntIntObjectSegNodeTag_Tuple5StringIntIntObjectSegNodeTag_Tuple5Tuple2 call_191 = segNodeToChildren_2(node_7);
    struct StringIntIntObjectSegNodeTag_Tuple5 left_6 = call_191.t0;
    struct StringIntIntObjectSegNodeTag_Tuple5 right_6 = call_191.t1;
    struct StringIntIntObjectSegNodeTag_Tuple5 match_52;
    if (!(((2 <= selfBalance_) == 1))) goto next_166;
    struct StringIntIntObjectSegNodeTag_Tuple5 match_53;
    int call_192 = toBalance_2(right_6);
    if (!(((call_192 < 0) == 1))) goto next_169;
    struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 tuple_53;
    tuple_53.t0 = itemTy_10;
    struct StringIntIntObjectSegNodeTag_Tuple5 call_193 = doubleLeft_2(tuple_53, node_7);
    match_53 = call_193;
    goto end_match_168;
next_169:;
    if (!(((call_192 < 0) == 0))) goto next_170;
    struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 tuple_54;
    tuple_54.t0 = itemTy_10;
    struct StringIntIntObjectSegNodeTag_Tuple5 call_194 = rotateLeft_2(tuple_54, node_7);
    match_53 = call_194;
    goto end_match_168;
next_170:;
    exit(1);
end_match_168:;
    match_52 = match_53;
    goto end_match_165;
next_166:;
    if (!(((2 <= selfBalance_) == 0))) goto next_167;
    struct StringIntIntObjectSegNodeTag_Tuple5 match_54;
    int call_195 = toBalance_2(left_6);
    if (!(((0 < call_195) == 1))) goto next_172;
    struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 tuple_55;
    tuple_55.t0 = itemTy_10;
    struct StringIntIntObjectSegNodeTag_Tuple5 call_196 = doubleRight_2(tuple_55, node_7);
    match_54 = call_196;
    goto end_match_171;
next_172:;
    if (!(((0 < call_195) == 0))) goto next_173;
    struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 tuple_56;
    tuple_56.t0 = itemTy_10;
    struct StringIntIntObjectSegNodeTag_Tuple5 call_197 = rotateRight_2(tuple_56, node_7);
    match_54 = call_197;
    goto end_match_171;
next_173:;
    exit(1);
end_match_171:;
    match_52 = match_54;
    goto end_match_165;
next_167:;
    exit(1);
end_match_165:;
    match_51 = match_52;
    goto end_match_162;
next_164:;
    exit(1);
end_match_162:;
    match_49 = match_51;
    goto end_match_156;
next_161:;
    exit(1);
end_match_156:;
    return match_49;
}

enum SegTreeTag_Tag {
    SegTreeTag_,
};

struct SegTreeTag_ {
    enum SegTreeTag_Tag tag;
};

struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 {
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 t0;
    struct IntIntIntObjectSegNodeTag_Tuple5 t1;
    struct SegTreeTag_ t2;
};

struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 segTreeNew_2(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_11) {
    struct IntIntIntObjectSegNodeTag_Tuple5 call_198 = segItemTypeToEmptyNode_2(itemTy_11);
    struct IntIntIntObjectSegNodeTag_Tuple5 emptyNode_2 = call_198;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 tuple_57;
    tuple_57.t0 = itemTy_11;
    tuple_57.t1 = emptyNode_2;
    tuple_57.t2 = (struct SegTreeTag_){.tag = SegTreeTag_};
    return tuple_57;
}

struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4StringIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 {
    struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 t0;
    struct StringIntIntObjectSegNodeTag_Tuple5 t1;
    struct SegTreeTag_ t2;
};

struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4StringIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 segTreeNew_1(struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_11) {
    struct StringIntIntObjectSegNodeTag_Tuple5 call_199 = segItemTypeToEmptyNode_1(itemTy_11);
    struct StringIntIntObjectSegNodeTag_Tuple5 emptyNode_2 = call_199;
    struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4StringIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 tuple_58;
    tuple_58.t0 = itemTy_11;
    tuple_58.t1 = emptyNode_2;
    tuple_58.t2 = (struct SegTreeTag_){.tag = SegTreeTag_};
    return tuple_58;
}

struct IntIntIntObjectSegNodeTag_Tuple5 segTreeToRoot_1(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 self_4) {
    struct IntIntIntObjectSegNodeTag_Tuple5 node_13 = self_4.t1;
    return node_13;
}

struct StringIntIntObjectSegNodeTag_Tuple5 segTreeToRoot_2(struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4StringIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 self_4) {
    struct StringIntIntObjectSegNodeTag_Tuple5 node_13 = self_4.t1;
    return node_13;
}

int segTreeToLength_1(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 self_5) {
    struct IntIntIntObjectSegNodeTag_Tuple5 call_200 = segTreeToRoot_1(self_5);
    int call_201 = segNodeToLength_1(call_200);
    return call_201;
}

int segTreeToLength_2(struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4StringIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 self_5) {
    struct StringIntIntObjectSegNodeTag_Tuple5 call_202 = segTreeToRoot_2(self_5);
    int call_203 = segNodeToLength_2(call_202);
    return call_203;
}

int segTreeToHeight_1(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 self_6) {
    struct IntIntIntObjectSegNodeTag_Tuple5 call_204 = segTreeToRoot_1(self_6);
    int call_205 = segNodeToHeight_1(call_204);
    return call_205;
}

int go_27(int index_6, struct IntIntIntObjectSegNodeTag_Tuple5 node_14) {
    int item_4 = node_14.t0;
    int len_14 = node_14.t1;
    int match_55;
    int match_56;
    if (!(((index_6 < 0) == 1))) goto next_176;
    match_56 = 1;
    goto end_match_175;
next_176:;
    if (!(((index_6 < 0) == 0))) goto next_177;
    match_56 = (len_14 <= index_6);
    goto end_match_175;
next_177:;
    exit(1);
end_match_175:;
    if (!((match_56 == 1))) goto next_178;
    printf("ERROR: segNodeGet out of range (index = %d, len = %d)\n", index_6, len_14);
    int call_206 = 0;
    exit(1);
    match_55 = 0;
    goto end_match_174;
next_178:;
    if (!((match_56 == 0))) goto next_179;
    match_55 = 0;
    goto end_match_174;
next_179:;
    exit(1);
end_match_174:;
    milone_assert((len_14 != 0));
    int call_207 = 0;
    int match_57;
    if (!(((len_14 == 1) == 1))) goto next_181;
    match_57 = item_4;
    goto end_match_180;
next_181:;
    if (!(((len_14 == 1) == 0))) goto next_182;
    struct IntIntIntObjectSegNodeTag_Tuple5IntIntIntObjectSegNodeTag_Tuple5Tuple2 call_208 = segNodeToChildren_1(node_14);
    struct IntIntIntObjectSegNodeTag_Tuple5 left_7 = call_208.t0;
    struct IntIntIntObjectSegNodeTag_Tuple5 right_7 = call_208.t1;
    int call_209 = segNodeToLength_1(left_7);
    int leftLen_1 = call_209;
    int match_58;
    if (!(((index_6 < leftLen_1) == 1))) goto next_184;
    int call_210 = go_27(index_6, left_7);
    match_58 = call_210;
    goto end_match_183;
next_184:;
    if (!(((index_6 < leftLen_1) == 0))) goto next_185;
    int call_211 = go_27((index_6 - leftLen_1), right_7);
    match_58 = call_211;
    goto end_match_183;
next_185:;
    exit(1);
end_match_183:;
    match_57 = match_58;
    goto end_match_180;
next_182:;
    exit(1);
end_match_180:;
    return match_57;
}

struct String go_37(int index_6, struct StringIntIntObjectSegNodeTag_Tuple5 node_14) {
    struct String item_4 = node_14.t0;
    int len_14 = node_14.t1;
    int match_59;
    int match_60;
    if (!(((index_6 < 0) == 1))) goto next_188;
    match_60 = 1;
    goto end_match_187;
next_188:;
    if (!(((index_6 < 0) == 0))) goto next_189;
    match_60 = (len_14 <= index_6);
    goto end_match_187;
next_189:;
    exit(1);
end_match_187:;
    if (!((match_60 == 1))) goto next_190;
    printf("ERROR: segNodeGet out of range (index = %d, len = %d)\n", index_6, len_14);
    int call_212 = 0;
    exit(1);
    match_59 = 0;
    goto end_match_186;
next_190:;
    if (!((match_60 == 0))) goto next_191;
    match_59 = 0;
    goto end_match_186;
next_191:;
    exit(1);
end_match_186:;
    milone_assert((len_14 != 0));
    int call_213 = 0;
    struct String match_61;
    if (!(((len_14 == 1) == 1))) goto next_193;
    match_61 = item_4;
    goto end_match_192;
next_193:;
    if (!(((len_14 == 1) == 0))) goto next_194;
    struct StringIntIntObjectSegNodeTag_Tuple5StringIntIntObjectSegNodeTag_Tuple5Tuple2 call_214 = segNodeToChildren_2(node_14);
    struct StringIntIntObjectSegNodeTag_Tuple5 left_7 = call_214.t0;
    struct StringIntIntObjectSegNodeTag_Tuple5 right_7 = call_214.t1;
    int call_215 = segNodeToLength_2(left_7);
    int leftLen_1 = call_215;
    struct String match_62;
    if (!(((index_6 < leftLen_1) == 1))) goto next_196;
    struct String call_216 = go_37(index_6, left_7);
    match_62 = call_216;
    goto end_match_195;
next_196:;
    if (!(((index_6 < leftLen_1) == 0))) goto next_197;
    struct String call_217 = go_37((index_6 - leftLen_1), right_7);
    match_62 = call_217;
    goto end_match_195;
next_197:;
    exit(1);
end_match_195:;
    match_61 = match_62;
    goto end_match_192;
next_194:;
    exit(1);
end_match_192:;
    return match_61;
}

int segTreeGet_1(int index_5, struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 self_8) {
    struct IntIntIntObjectSegNodeTag_Tuple5 call_218 = segTreeToRoot_1(self_8);
    int call_219 = go_27(index_5, call_218);
    return call_219;
}

struct String segTreeGet_2(int index_5, struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4StringIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 self_8) {
    struct StringIntIntObjectSegNodeTag_Tuple5 call_220 = segTreeToRoot_2(self_8);
    struct String call_221 = go_37(index_5, call_220);
    return call_221;
}

int go_26(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 arg_75, struct IntIntTuple2 e_, struct IntIntTuple2 q_, struct IntIntIntObjectSegNodeTag_Tuple5 node_15) {
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_12 = arg_75.t0;
    int match_63;
    int call_222 = intervalIsDisjoint_(q_, e_);
    if (!((call_222 == 1))) goto next_199;
    int call_223 = segItemTypeToEmptyItem_1(itemTy_12);
    match_63 = call_223;
    goto end_match_198;
next_199:;
    if (!((call_222 == 0))) goto next_200;
    int match_64;
    int call_224 = intervalCovers_(q_, e_);
    if (!((call_224 == 1))) goto next_202;
    int call_225 = segNodeToItem_1(node_15);
    match_64 = call_225;
    goto end_match_201;
next_202:;
    if (!((call_224 == 0))) goto next_203;
    int call_226 = segNodeIsEmpty_1(node_15);
    milone_assert((!(call_226)));
    int call_227 = 0;
    struct IntIntIntObjectSegNodeTag_Tuple5IntIntIntObjectSegNodeTag_Tuple5Tuple2 call_228 = segNodeToChildren_1(node_15);
    struct IntIntIntObjectSegNodeTag_Tuple5 leftNode_ = call_228.t0;
    struct IntIntIntObjectSegNodeTag_Tuple5 rightNode_ = call_228.t1;
    int el_ = e_.t0;
    int er_ = e_.t1;
    int call_229 = segNodeToLength_1(leftNode_);
    int m_1 = (el_ + call_229);
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 tuple_59;
    tuple_59.t0 = itemTy_12;
    struct IntIntTuple2 tuple_60;
    tuple_60.t0 = el_;
    tuple_60.t1 = m_1;
    int call_230 = go_26(tuple_59, tuple_60, q_, leftNode_);
    int vl_ = call_230;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 tuple_61;
    tuple_61.t0 = itemTy_12;
    struct IntIntTuple2 tuple_62;
    tuple_62.t0 = m_1;
    tuple_62.t1 = er_;
    int call_231 = go_26(tuple_61, tuple_62, q_, rightNode_);
    int vr_ = call_231;
    struct IntIntIntFun2 call_232 = segItemTypeToAppend_1(itemTy_12);
    int app_10 = call_232.fun(call_232.env, vl_, vr_);
    match_64 = app_10;
    goto end_match_201;
next_203:;
    exit(1);
end_match_201:;
    match_63 = match_64;
    goto end_match_198;
next_200:;
    exit(1);
end_match_198:;
    return match_63;
}

int segTreeSum_1(int ql_, int qr_, struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 self_9) {
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_12 = self_9.t0;
    struct IntIntIntObjectSegNodeTag_Tuple5 root_ = self_9.t1;
    int call_233 = segNodeToLength_1(root_);
    int len_15 = call_233;
    struct IntIntTuple2 tuple_63;
    tuple_63.t0 = ql_;
    tuple_63.t1 = qr_;
    struct IntIntTuple2 q_1 = tuple_63;
    int match_65;
    struct IntIntTuple2 tuple_64;
    tuple_64.t0 = 0;
    tuple_64.t1 = len_15;
    int call_234 = intervalIsDisjoint_(q_1, tuple_64);
    if (!((call_234 == 1))) goto next_205;
    int call_235 = segItemTypeToEmptyItem_1(itemTy_12);
    match_65 = call_235;
    goto end_match_204;
next_205:;
    if (!((call_234 == 0))) goto next_206;
    struct IntIntTuple2 tuple_65;
    tuple_65.t0 = 0;
    tuple_65.t1 = len_15;
    struct IntIntTuple2 e_1 = tuple_65;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 tuple_66;
    tuple_66.t0 = itemTy_12;
    int call_236 = go_26(tuple_66, e_1, q_1, root_);
    match_65 = call_236;
    goto end_match_204;
next_206:;
    exit(1);
end_match_204:;
    return match_65;
}

struct IntIntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple2 {
    int t0;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 t1;
};

struct IntIntIntObjectSegNodeTag_Tuple5 go_25(struct IntIntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple2 arg_76, int index_8, struct IntIntIntObjectSegNodeTag_Tuple5 node_16) {
    int newItem_ = arg_76.t0;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_13 = arg_76.t1;
    int len_16 = node_16.t1;
    int height_2 = node_16.t2;
    void* children_1 = node_16.t3;
    int match_66;
    int match_67;
    if (!(((index_8 < 0) == 1))) goto next_209;
    match_67 = 1;
    goto end_match_208;
next_209:;
    if (!(((index_8 < 0) == 0))) goto next_210;
    match_67 = (len_16 <= index_8);
    goto end_match_208;
next_210:;
    exit(1);
end_match_208:;
    if (!((match_67 == 1))) goto next_211;
    printf("ERROR: segNodeSet out of range (index = %d, len = %d)\n", index_8, len_16);
    int call_237 = 0;
    exit(1);
    match_66 = 0;
    goto end_match_207;
next_211:;
    if (!((match_67 == 0))) goto next_212;
    match_66 = 0;
    goto end_match_207;
next_212:;
    exit(1);
end_match_207:;
    milone_assert((len_16 != 0));
    int call_238 = 0;
    struct IntIntIntObjectSegNodeTag_Tuple5 match_68;
    if (!(((len_16 == 1) == 1))) goto next_214;
    struct IntIntIntObjectSegNodeTag_Tuple5 tuple_67;
    tuple_67.t0 = newItem_;
    tuple_67.t1 = len_16;
    tuple_67.t2 = height_2;
    tuple_67.t3 = children_1;
    tuple_67.t4 = (struct SegNodeTag_){.tag = SegNodeTag_};
    match_68 = tuple_67;
    goto end_match_213;
next_214:;
    if (!(((len_16 == 1) == 0))) goto next_215;
    struct IntIntIntObjectSegNodeTag_Tuple5IntIntIntObjectSegNodeTag_Tuple5Tuple2 call_239 = segNodeToChildren_1(node_16);
    struct IntIntIntObjectSegNodeTag_Tuple5 left_8 = call_239.t0;
    struct IntIntIntObjectSegNodeTag_Tuple5 right_8 = call_239.t1;
    int call_240 = segNodeToLength_1(left_8);
    int leftLen_2 = call_240;
    struct IntIntIntObjectSegNodeTag_Tuple5 match_69;
    if (!(((index_8 < leftLen_2) == 1))) goto next_217;
    struct IntIntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple2 tuple_68;
    tuple_68.t0 = newItem_;
    tuple_68.t1 = itemTy_13;
    struct IntIntIntObjectSegNodeTag_Tuple5 call_241 = go_25(tuple_68, index_8, left_8);
    struct IntIntIntObjectSegNodeTag_Tuple5 call_242 = segNodeWithLeft_1(itemTy_13, call_241, node_16);
    match_69 = call_242;
    goto end_match_216;
next_217:;
    if (!(((index_8 < leftLen_2) == 0))) goto next_218;
    struct IntIntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple2 tuple_69;
    tuple_69.t0 = newItem_;
    tuple_69.t1 = itemTy_13;
    struct IntIntIntObjectSegNodeTag_Tuple5 call_243 = go_25(tuple_69, (index_8 - leftLen_2), right_8);
    struct IntIntIntObjectSegNodeTag_Tuple5 call_244 = segNodeWithRight_1(itemTy_13, call_243, node_16);
    match_69 = call_244;
    goto end_match_216;
next_218:;
    exit(1);
end_match_216:;
    match_68 = match_69;
    goto end_match_213;
next_215:;
    exit(1);
end_match_213:;
    return match_68;
}

struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 segTreeSet_1(int index_7, int newItem_, struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 self_10) {
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_13 = self_10.t0;
    struct IntIntIntObjectSegNodeTag_Tuple5 root_1 = self_10.t1;
    struct IntIntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple2 tuple_70;
    tuple_70.t0 = newItem_;
    tuple_70.t1 = itemTy_13;
    struct IntIntIntObjectSegNodeTag_Tuple5 call_245 = go_25(tuple_70, index_7, root_1);
    struct IntIntIntObjectSegNodeTag_Tuple5 root_2 = call_245;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 tuple_71;
    tuple_71.t0 = itemTy_13;
    tuple_71.t1 = root_2;
    tuple_71.t2 = (struct SegTreeTag_){.tag = SegTreeTag_};
    return tuple_71;
}

struct IntIntIntObjectSegNodeTag_Tuple5 go_24(struct IntIntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple2 arg_77, int index_10, struct IntIntIntObjectSegNodeTag_Tuple5 node_17) {
    int newItem_1 = arg_77.t0;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_14 = arg_77.t1;
    int oldItem_ = node_17.t0;
    int len_17 = node_17.t1;
    milone_assert((index_10 <= len_17));
    int call_246 = 0;
    struct IntIntIntObjectSegNodeTag_Tuple5 match_70;
    if (!(((len_17 == 0) == 1))) goto next_220;
    struct IntIntIntObjectSegNodeTag_Tuple5 call_247 = segNodeNewLeaf_1(itemTy_14, newItem_1);
    match_70 = call_247;
    goto end_match_219;
next_220:;
    if (!(((len_17 == 0) == 0))) goto next_221;
    struct IntIntIntObjectSegNodeTag_Tuple5 match_71;
    if (!(((len_17 == 1) == 1))) goto next_223;
    struct IntIntIntObjectSegNodeTag_Tuple5 call_248 = segNodeNewLeaf_1(itemTy_14, oldItem_);
    struct IntIntIntObjectSegNodeTag_Tuple5 oldLeaf_ = call_248;
    struct IntIntIntObjectSegNodeTag_Tuple5 call_249 = segNodeNewLeaf_1(itemTy_14, newItem_1);
    struct IntIntIntObjectSegNodeTag_Tuple5 newLeaf_ = call_249;
    struct IntIntIntObjectSegNodeTag_Tuple5IntIntIntObjectSegNodeTag_Tuple5Tuple2 match_72;
    if (!(((index_10 == 0) == 1))) goto next_226;
    struct IntIntIntObjectSegNodeTag_Tuple5IntIntIntObjectSegNodeTag_Tuple5Tuple2 tuple_72;
    tuple_72.t0 = newLeaf_;
    tuple_72.t1 = oldLeaf_;
    match_72 = tuple_72;
    goto end_match_225;
next_226:;
    if (!(((index_10 == 0) == 0))) goto next_227;
    milone_assert((index_10 == 1));
    int call_250 = 0;
    struct IntIntIntObjectSegNodeTag_Tuple5IntIntIntObjectSegNodeTag_Tuple5Tuple2 tuple_73;
    tuple_73.t0 = oldLeaf_;
    tuple_73.t1 = newLeaf_;
    match_72 = tuple_73;
    goto end_match_225;
next_227:;
    exit(1);
end_match_225:;
    struct IntIntIntObjectSegNodeTag_Tuple5 left_9 = match_72.t0;
    struct IntIntIntObjectSegNodeTag_Tuple5 right_9 = match_72.t1;
    struct IntIntIntObjectSegNodeTag_Tuple5 call_251 = segNodeNew_1(itemTy_14, left_9, right_9);
    match_71 = call_251;
    goto end_match_222;
next_223:;
    if (!(((len_17 == 1) == 0))) goto next_224;
    struct IntIntIntObjectSegNodeTag_Tuple5IntIntIntObjectSegNodeTag_Tuple5Tuple2 call_252 = segNodeToChildren_1(node_17);
    struct IntIntIntObjectSegNodeTag_Tuple5 left_10 = call_252.t0;
    struct IntIntIntObjectSegNodeTag_Tuple5 right_10 = call_252.t1;
    int call_253 = segNodeToLength_1(left_10);
    int leftLen_3 = call_253;
    int call_254 = segNodeToLength_1(right_10);
    int rightLen_1 = call_254;
    milone_assert(((leftLen_3 + rightLen_1) == len_17));
    int call_255 = 0;
    struct IntIntIntObjectSegNodeTag_Tuple5IntIntIntObjectSegNodeTag_Tuple5Tuple2 match_73;
    if (!(((index_10 < leftLen_3) == 1))) goto next_229;
    struct IntIntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple2 tuple_74;
    tuple_74.t0 = newItem_1;
    tuple_74.t1 = itemTy_14;
    struct IntIntIntObjectSegNodeTag_Tuple5 call_256 = go_24(tuple_74, index_10, left_10);
    struct IntIntIntObjectSegNodeTag_Tuple5 left_12 = call_256;
    int call_257 = segNodeToLength_1(left_12);
    milone_assert((call_257 == (leftLen_3 + 1)));
    int call_258 = 0;
    struct IntIntIntObjectSegNodeTag_Tuple5IntIntIntObjectSegNodeTag_Tuple5Tuple2 tuple_75;
    tuple_75.t0 = left_12;
    tuple_75.t1 = right_10;
    match_73 = tuple_75;
    goto end_match_228;
next_229:;
    if (!(((index_10 < leftLen_3) == 0))) goto next_230;
    struct IntIntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple2 tuple_76;
    tuple_76.t0 = newItem_1;
    tuple_76.t1 = itemTy_14;
    struct IntIntIntObjectSegNodeTag_Tuple5 call_259 = go_24(tuple_76, (index_10 - leftLen_3), right_10);
    struct IntIntIntObjectSegNodeTag_Tuple5 right_12 = call_259;
    int call_260 = segNodeToLength_1(right_12);
    milone_assert((call_260 == (rightLen_1 + 1)));
    int call_261 = 0;
    struct IntIntIntObjectSegNodeTag_Tuple5IntIntIntObjectSegNodeTag_Tuple5Tuple2 tuple_77;
    tuple_77.t0 = left_10;
    tuple_77.t1 = right_12;
    match_73 = tuple_77;
    goto end_match_228;
next_230:;
    exit(1);
end_match_228:;
    struct IntIntIntObjectSegNodeTag_Tuple5 left_11 = match_73.t0;
    struct IntIntIntObjectSegNodeTag_Tuple5 right_11 = match_73.t1;
    struct IntIntIntObjectSegNodeTag_Tuple5 call_262 = segNodeNew_1(itemTy_14, left_11, right_11);
    struct IntIntIntObjectSegNodeTag_Tuple5 call_263 = segNodeMakeBalanced_1(itemTy_14, call_262);
    match_71 = call_263;
    goto end_match_222;
next_224:;
    exit(1);
end_match_222:;
    match_70 = match_71;
    goto end_match_219;
next_221:;
    exit(1);
end_match_219:;
    return match_70;
}

struct StringStringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple2 {
    struct String t0;
    struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 t1;
};

struct StringIntIntObjectSegNodeTag_Tuple5 go_36(struct StringStringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple2 arg_78, int index_10, struct StringIntIntObjectSegNodeTag_Tuple5 node_17) {
    struct String newItem_1 = arg_78.t0;
    struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_14 = arg_78.t1;
    struct String oldItem_ = node_17.t0;
    int len_17 = node_17.t1;
    milone_assert((index_10 <= len_17));
    int call_264 = 0;
    struct StringIntIntObjectSegNodeTag_Tuple5 match_74;
    if (!(((len_17 == 0) == 1))) goto next_232;
    struct StringIntIntObjectSegNodeTag_Tuple5 call_265 = segNodeNewLeaf_2(itemTy_14, newItem_1);
    match_74 = call_265;
    goto end_match_231;
next_232:;
    if (!(((len_17 == 0) == 0))) goto next_233;
    struct StringIntIntObjectSegNodeTag_Tuple5 match_75;
    if (!(((len_17 == 1) == 1))) goto next_235;
    struct StringIntIntObjectSegNodeTag_Tuple5 call_266 = segNodeNewLeaf_2(itemTy_14, oldItem_);
    struct StringIntIntObjectSegNodeTag_Tuple5 oldLeaf_ = call_266;
    struct StringIntIntObjectSegNodeTag_Tuple5 call_267 = segNodeNewLeaf_2(itemTy_14, newItem_1);
    struct StringIntIntObjectSegNodeTag_Tuple5 newLeaf_ = call_267;
    struct StringIntIntObjectSegNodeTag_Tuple5StringIntIntObjectSegNodeTag_Tuple5Tuple2 match_76;
    if (!(((index_10 == 0) == 1))) goto next_238;
    struct StringIntIntObjectSegNodeTag_Tuple5StringIntIntObjectSegNodeTag_Tuple5Tuple2 tuple_78;
    tuple_78.t0 = newLeaf_;
    tuple_78.t1 = oldLeaf_;
    match_76 = tuple_78;
    goto end_match_237;
next_238:;
    if (!(((index_10 == 0) == 0))) goto next_239;
    milone_assert((index_10 == 1));
    int call_268 = 0;
    struct StringIntIntObjectSegNodeTag_Tuple5StringIntIntObjectSegNodeTag_Tuple5Tuple2 tuple_79;
    tuple_79.t0 = oldLeaf_;
    tuple_79.t1 = newLeaf_;
    match_76 = tuple_79;
    goto end_match_237;
next_239:;
    exit(1);
end_match_237:;
    struct StringIntIntObjectSegNodeTag_Tuple5 left_9 = match_76.t0;
    struct StringIntIntObjectSegNodeTag_Tuple5 right_9 = match_76.t1;
    struct StringIntIntObjectSegNodeTag_Tuple5 call_269 = segNodeNew_2(itemTy_14, left_9, right_9);
    match_75 = call_269;
    goto end_match_234;
next_235:;
    if (!(((len_17 == 1) == 0))) goto next_236;
    struct StringIntIntObjectSegNodeTag_Tuple5StringIntIntObjectSegNodeTag_Tuple5Tuple2 call_270 = segNodeToChildren_2(node_17);
    struct StringIntIntObjectSegNodeTag_Tuple5 left_10 = call_270.t0;
    struct StringIntIntObjectSegNodeTag_Tuple5 right_10 = call_270.t1;
    int call_271 = segNodeToLength_2(left_10);
    int leftLen_3 = call_271;
    int call_272 = segNodeToLength_2(right_10);
    int rightLen_1 = call_272;
    milone_assert(((leftLen_3 + rightLen_1) == len_17));
    int call_273 = 0;
    struct StringIntIntObjectSegNodeTag_Tuple5StringIntIntObjectSegNodeTag_Tuple5Tuple2 match_77;
    if (!(((index_10 < leftLen_3) == 1))) goto next_241;
    struct StringStringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple2 tuple_80;
    tuple_80.t0 = newItem_1;
    tuple_80.t1 = itemTy_14;
    struct StringIntIntObjectSegNodeTag_Tuple5 call_274 = go_36(tuple_80, index_10, left_10);
    struct StringIntIntObjectSegNodeTag_Tuple5 left_12 = call_274;
    int call_275 = segNodeToLength_2(left_12);
    milone_assert((call_275 == (leftLen_3 + 1)));
    int call_276 = 0;
    struct StringIntIntObjectSegNodeTag_Tuple5StringIntIntObjectSegNodeTag_Tuple5Tuple2 tuple_81;
    tuple_81.t0 = left_12;
    tuple_81.t1 = right_10;
    match_77 = tuple_81;
    goto end_match_240;
next_241:;
    if (!(((index_10 < leftLen_3) == 0))) goto next_242;
    struct StringStringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple2 tuple_82;
    tuple_82.t0 = newItem_1;
    tuple_82.t1 = itemTy_14;
    struct StringIntIntObjectSegNodeTag_Tuple5 call_277 = go_36(tuple_82, (index_10 - leftLen_3), right_10);
    struct StringIntIntObjectSegNodeTag_Tuple5 right_12 = call_277;
    int call_278 = segNodeToLength_2(right_12);
    milone_assert((call_278 == (rightLen_1 + 1)));
    int call_279 = 0;
    struct StringIntIntObjectSegNodeTag_Tuple5StringIntIntObjectSegNodeTag_Tuple5Tuple2 tuple_83;
    tuple_83.t0 = left_10;
    tuple_83.t1 = right_12;
    match_77 = tuple_83;
    goto end_match_240;
next_242:;
    exit(1);
end_match_240:;
    struct StringIntIntObjectSegNodeTag_Tuple5 left_11 = match_77.t0;
    struct StringIntIntObjectSegNodeTag_Tuple5 right_11 = match_77.t1;
    struct StringIntIntObjectSegNodeTag_Tuple5 call_280 = segNodeNew_2(itemTy_14, left_11, right_11);
    struct StringIntIntObjectSegNodeTag_Tuple5 call_281 = segNodeMakeBalanced_2(itemTy_14, call_280);
    match_75 = call_281;
    goto end_match_234;
next_236:;
    exit(1);
end_match_234:;
    match_74 = match_75;
    goto end_match_231;
next_233:;
    exit(1);
end_match_231:;
    return match_74;
}

struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 segTreeInsert_1(int index_9, int newItem_1, struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 self_11) {
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_14 = self_11.t0;
    struct IntIntIntObjectSegNodeTag_Tuple5 root_3 = self_11.t1;
    struct IntIntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple2 tuple_84;
    tuple_84.t0 = newItem_1;
    tuple_84.t1 = itemTy_14;
    struct IntIntIntObjectSegNodeTag_Tuple5 call_282 = go_24(tuple_84, index_9, root_3);
    struct IntIntIntObjectSegNodeTag_Tuple5 root_4 = call_282;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 tuple_85;
    tuple_85.t0 = itemTy_14;
    tuple_85.t1 = root_4;
    tuple_85.t2 = (struct SegTreeTag_){.tag = SegTreeTag_};
    return tuple_85;
}

struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4StringIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 segTreeInsert_2(int index_9, struct String newItem_1, struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4StringIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 self_11) {
    struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_14 = self_11.t0;
    struct StringIntIntObjectSegNodeTag_Tuple5 root_3 = self_11.t1;
    struct StringStringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple2 tuple_86;
    tuple_86.t0 = newItem_1;
    tuple_86.t1 = itemTy_14;
    struct StringIntIntObjectSegNodeTag_Tuple5 call_283 = go_36(tuple_86, index_9, root_3);
    struct StringIntIntObjectSegNodeTag_Tuple5 root_4 = call_283;
    struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4StringIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 tuple_87;
    tuple_87.t0 = itemTy_14;
    tuple_87.t1 = root_4;
    tuple_87.t2 = (struct SegTreeTag_){.tag = SegTreeTag_};
    return tuple_87;
}

struct IntIntIntObjectSegNodeTag_Tuple5 go_35(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 arg_79, int index_12, struct IntIntIntObjectSegNodeTag_Tuple5 node_18) {
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_15 = arg_79.t0;
    int len_18 = node_18.t1;
    milone_assert((index_12 < len_18));
    int call_284 = 0;
    milone_assert((len_18 != 0));
    int call_285 = 0;
    struct IntIntIntObjectSegNodeTag_Tuple5 match_78;
    if (!(((len_18 == 1) == 1))) goto next_244;
    struct IntIntIntObjectSegNodeTag_Tuple5 call_286 = segItemTypeToEmptyNode_2(itemTy_15);
    match_78 = call_286;
    goto end_match_243;
next_244:;
    if (!(((len_18 == 1) == 0))) goto next_245;
    struct IntIntIntObjectSegNodeTag_Tuple5IntIntIntObjectSegNodeTag_Tuple5Tuple2 call_287 = segNodeToChildren_1(node_18);
    struct IntIntIntObjectSegNodeTag_Tuple5 left_13 = call_287.t0;
    struct IntIntIntObjectSegNodeTag_Tuple5 right_13 = call_287.t1;
    int call_288 = segNodeToLength_1(left_13);
    int leftLen_4 = call_288;
    int call_289 = segNodeToLength_1(right_13);
    int rightLen_2 = call_289;
    milone_assert(((leftLen_4 + rightLen_2) == len_18));
    int call_290 = 0;
    struct IntIntIntObjectSegNodeTag_Tuple5 match_79;
    if (!(((index_12 < leftLen_4) == 1))) goto next_247;
    struct IntIntIntObjectSegNodeTag_Tuple5 match_80;
    if (!(((leftLen_4 < 2) == 1))) goto next_250;
    match_80 = right_13;
    goto end_match_249;
next_250:;
    if (!(((leftLen_4 < 2) == 0))) goto next_251;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 tuple_88;
    tuple_88.t0 = itemTy_15;
    struct IntIntIntObjectSegNodeTag_Tuple5 call_291 = go_35(tuple_88, index_12, left_13);
    struct IntIntIntObjectSegNodeTag_Tuple5 call_292 = segNodeWithLeft_1(itemTy_15, call_291, node_18);
    match_80 = call_292;
    goto end_match_249;
next_251:;
    exit(1);
end_match_249:;
    match_79 = match_80;
    goto end_match_246;
next_247:;
    if (!(((index_12 < leftLen_4) == 0))) goto next_248;
    struct IntIntIntObjectSegNodeTag_Tuple5 match_81;
    if (!(((rightLen_2 < 2) == 1))) goto next_253;
    match_81 = left_13;
    goto end_match_252;
next_253:;
    if (!(((rightLen_2 < 2) == 0))) goto next_254;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 tuple_89;
    tuple_89.t0 = itemTy_15;
    struct IntIntIntObjectSegNodeTag_Tuple5 call_293 = go_35(tuple_89, (index_12 - leftLen_4), right_13);
    struct IntIntIntObjectSegNodeTag_Tuple5 call_294 = segNodeWithRight_1(itemTy_15, call_293, node_18);
    match_81 = call_294;
    goto end_match_252;
next_254:;
    exit(1);
end_match_252:;
    match_79 = match_81;
    goto end_match_246;
next_248:;
    exit(1);
end_match_246:;
    struct IntIntIntObjectSegNodeTag_Tuple5 node_19 = match_79;
    struct IntIntIntObjectSegNodeTag_Tuple5 call_295 = segNodeMakeBalanced_1(itemTy_15, node_19);
    match_78 = call_295;
    goto end_match_243;
next_245:;
    exit(1);
end_match_243:;
    return match_78;
}

struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 segTreeRemove_1(int index_11, struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 self_12) {
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_15 = self_12.t0;
    struct IntIntIntObjectSegNodeTag_Tuple5 root_5 = self_12.t1;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 tuple_90;
    tuple_90.t0 = itemTy_15;
    struct IntIntIntObjectSegNodeTag_Tuple5 call_296 = go_35(tuple_90, index_11, root_5);
    struct IntIntIntObjectSegNodeTag_Tuple5 root_6 = call_296;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 tuple_91;
    tuple_91.t0 = itemTy_15;
    tuple_91.t1 = root_6;
    tuple_91.t2 = (struct SegTreeTag_){.tag = SegTreeTag_};
    return tuple_91;
}

struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4StringIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 segTreePush_2(struct String value_4, struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4StringIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 self_13) {
    int call_297 = segTreeToLength_2(self_13);
    int index_13 = call_297;
    struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4StringIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 call_298 = segTreeInsert_2(index_13, value_4, self_13);
    return call_298;
}

struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 segTreePush_1(int value_4, struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 self_13) {
    int call_299 = segTreeToLength_1(self_13);
    int index_13 = call_299;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 call_300 = segTreeInsert_1(index_13, value_4, self_13);
    return call_300;
}

struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 segTreePop_1(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 self_14) {
    int call_301 = segTreeToLength_1(self_14);
    int index_14 = (call_301 - 1);
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 call_302 = segTreeRemove_1(index_14, self_14);
    return call_302;
}

struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 go_23(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 t_2, struct IntList* xs_22) {
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 match_82;
    if (!((!(xs_22)))) goto next_256;
    match_82 = t_2;
    goto end_match_255;
next_256:;
    if (!((!((!(xs_22)))))) goto next_257;
    int x_6 = xs_22->head;
    struct IntList* xs_23 = xs_22->tail;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 call_303 = segTreePush_1(x_6, t_2);
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 call_304 = go_23(call_303, xs_23);
    match_82 = call_304;
    goto end_match_255;
next_257:;
    exit(1);
end_match_255:;
    return match_82;
}

struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 segTreeOfList_1(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 itemTy_16, struct IntList* xs_21) {
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 call_305 = segTreeNew_2(itemTy_16);
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 call_306 = go_23(call_305, xs_21);
    return call_306;
}

struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3IntTuple2 {
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 t0;
    int t1;
};

struct IntList* go_22(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3IntTuple2 arg_80, struct IntList* acc_3, int i_4) {
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 v_4 = arg_80.t0;
    int len_19 = arg_80.t1;
    struct IntList* match_83;
    if (!(((i_4 == len_19) == 1))) goto next_259;
    struct IntList* call_307 = listRev_2(acc_3);
    match_83 = call_307;
    goto end_match_258;
next_259:;
    if (!(((i_4 == len_19) == 0))) goto next_260;
    int call_308 = segTreeGet_1(i_4, v_4);
    int x_7 = call_308;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3IntTuple2 tuple_92;
    tuple_92.t0 = v_4;
    tuple_92.t1 = len_19;
    struct IntList* list_21 = (struct IntList*)malloc(sizeof(struct IntList));
    list_21->head = x_7;
    list_21->tail = acc_3;
    struct IntList* call_309 = go_22(tuple_92, list_21, (i_4 + 1));
    match_83 = call_309;
    goto end_match_258;
next_260:;
    exit(1);
end_match_258:;
    return match_83;
}

struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4StringIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3IntTuple2 {
    struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4StringIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 t0;
    int t1;
};

struct StringList* go_21(struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4StringIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3IntTuple2 arg_81, struct StringList* acc_3, int i_4) {
    struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4StringIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 v_4 = arg_81.t0;
    int len_19 = arg_81.t1;
    struct StringList* match_84;
    if (!(((i_4 == len_19) == 1))) goto next_262;
    struct StringList* call_310 = listRev_1(acc_3);
    match_84 = call_310;
    goto end_match_261;
next_262:;
    if (!(((i_4 == len_19) == 0))) goto next_263;
    struct String call_311 = segTreeGet_2(i_4, v_4);
    struct String x_7 = call_311;
    struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4StringIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3IntTuple2 tuple_93;
    tuple_93.t0 = v_4;
    tuple_93.t1 = len_19;
    struct StringList* list_22 = (struct StringList*)malloc(sizeof(struct StringList));
    list_22->head = x_7;
    list_22->tail = acc_3;
    struct StringList* call_312 = go_21(tuple_93, list_22, (i_4 + 1));
    match_84 = call_312;
    goto end_match_261;
next_263:;
    exit(1);
end_match_261:;
    return match_84;
}

struct IntList* segTreeToList_2(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 v_4) {
    int call_313 = segTreeToLength_1(v_4);
    int len_19 = call_313;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3IntTuple2 tuple_94;
    tuple_94.t0 = v_4;
    tuple_94.t1 = len_19;
    struct IntList* call_314 = go_22(tuple_94, NULL, 0);
    return call_314;
}

struct StringList* segTreeToList_1(struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4StringIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 v_4) {
    int call_315 = segTreeToLength_2(v_4);
    int len_19 = call_315;
    struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4StringIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3IntTuple2 tuple_95;
    tuple_95.t0 = v_4;
    tuple_95.t1 = len_19;
    struct StringList* call_316 = go_21(tuple_95, NULL, 0);
    return call_316;
}

int intAdd_(int x_8, int y_3) {
    return (x_8 + y_3);
}

int fun_7(void* env_4, int arg_7, int arg_8) {
    int call_317 = intAdd_(arg_7, arg_8);
    return call_317;
}

struct String strAdd_(struct String x_9, struct String y_4) {
    return str_add(x_9, y_4);
}

struct String fun_8(void* env_5, struct String arg_9, struct String arg_10) {
    struct String call_318 = strAdd_(arg_9, arg_10);
    return call_318;
}

int fun_9(void* env_6, int arg_11, int arg_12) {
    int call_319 = intEq_(arg_11, arg_12);
    return call_319;
}

int fun_10(void* env_7, int arg_13, int arg_14) {
    int call_320 = intEq_(arg_13, arg_14);
    return call_320;
}

int fun_11(void* env_8, int arg_15, int arg_16) {
    int call_321 = intEq_(arg_15, arg_16);
    return call_321;
}

int fun_12(void* env_9, int arg_17, int arg_18) {
    int call_322 = intEq_(arg_17, arg_18);
    return call_322;
}

int fun_13(void* env_10, int arg_19, int arg_20) {
    int call_323 = intEq_(arg_19, arg_20);
    return call_323;
}

int testPushPop_(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 arg_82, int arg_83) {
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 segItemTypeInt_ = arg_82.t0;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 call_324 = segTreeNew_2(segItemTypeInt_);
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 call_325 = segTreePush_1(1, call_324);
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 call_326 = segTreePush_1(2, call_325);
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 v_5 = call_326;
    void* box_5 = (void*)malloc(sizeof(int));
    (*(((int*)box_5))) = 0;
    void* env_19 = box_5;
    struct IntIntBoolFun2 fun_25 = (struct IntIntBoolFun2){.fun = fun_9, .env = env_19};
    struct IntList* list_24 = (struct IntList*)malloc(sizeof(struct IntList));
    list_24->head = 2;
    list_24->tail = NULL;
    struct IntList* list_23 = (struct IntList*)malloc(sizeof(struct IntList));
    list_23->head = 1;
    list_23->tail = list_24;
    struct IntList* call_327 = segTreeToList_2(v_5);
    int call_328 = listEq_2(fun_25, list_23, call_327);
    milone_assert(call_328);
    int call_329 = 0;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 call_330 = segTreePush_1(3, v_5);
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 v_6 = call_330;
    void* box_6 = (void*)malloc(sizeof(int));
    (*(((int*)box_6))) = 0;
    void* env_20 = box_6;
    struct IntIntBoolFun2 fun_26 = (struct IntIntBoolFun2){.fun = fun_10, .env = env_20};
    struct IntList* list_27 = (struct IntList*)malloc(sizeof(struct IntList));
    list_27->head = 3;
    list_27->tail = NULL;
    struct IntList* list_26 = (struct IntList*)malloc(sizeof(struct IntList));
    list_26->head = 2;
    list_26->tail = list_27;
    struct IntList* list_25 = (struct IntList*)malloc(sizeof(struct IntList));
    list_25->head = 1;
    list_25->tail = list_26;
    struct IntList* call_331 = segTreeToList_2(v_6);
    int call_332 = listEq_2(fun_26, list_25, call_331);
    milone_assert(call_332);
    int call_333 = 0;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 call_334 = segTreePop_1(v_6);
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 v_7 = call_334;
    void* box_7 = (void*)malloc(sizeof(int));
    (*(((int*)box_7))) = 0;
    void* env_21 = box_7;
    struct IntIntBoolFun2 fun_27 = (struct IntIntBoolFun2){.fun = fun_11, .env = env_21};
    struct IntList* list_29 = (struct IntList*)malloc(sizeof(struct IntList));
    list_29->head = 2;
    list_29->tail = NULL;
    struct IntList* list_28 = (struct IntList*)malloc(sizeof(struct IntList));
    list_28->head = 1;
    list_28->tail = list_29;
    struct IntList* call_335 = segTreeToList_2(v_7);
    int call_336 = listEq_2(fun_27, list_28, call_335);
    milone_assert(call_336);
    int call_337 = 0;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 call_338 = segTreePop_1(v_7);
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 v_8 = call_338;
    void* box_8 = (void*)malloc(sizeof(int));
    (*(((int*)box_8))) = 0;
    void* env_22 = box_8;
    struct IntIntBoolFun2 fun_28 = (struct IntIntBoolFun2){.fun = fun_12, .env = env_22};
    struct IntList* list_30 = (struct IntList*)malloc(sizeof(struct IntList));
    list_30->head = 1;
    list_30->tail = NULL;
    struct IntList* call_339 = segTreeToList_2(v_8);
    int call_340 = listEq_2(fun_28, list_30, call_339);
    milone_assert(call_340);
    int call_341 = 0;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 call_342 = segTreePop_1(v_8);
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 v_9 = call_342;
    void* box_9 = (void*)malloc(sizeof(int));
    (*(((int*)box_9))) = 0;
    void* env_23 = box_9;
    struct IntIntBoolFun2 fun_29 = (struct IntIntBoolFun2){.fun = fun_13, .env = env_23};
    struct IntList* call_343 = segTreeToList_2(v_9);
    int call_344 = listEq_2(fun_29, NULL, call_343);
    milone_assert(call_344);
    int call_345 = 0;
    return 0;
}

int fun_14(void* env_11, int arg_21, int arg_22) {
    int call_346 = intEq_(arg_21, arg_22);
    return call_346;
}

int fun_15(void* env_12, int arg_23, int arg_24) {
    int call_347 = intEq_(arg_23, arg_24);
    return call_347;
}

int testSet_(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 arg_84, int arg_85) {
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 segItemTypeInt_ = arg_84.t0;
    struct IntList* list_33 = (struct IntList*)malloc(sizeof(struct IntList));
    list_33->head = 3;
    list_33->tail = NULL;
    struct IntList* list_32 = (struct IntList*)malloc(sizeof(struct IntList));
    list_32->head = 2;
    list_32->tail = list_33;
    struct IntList* list_31 = (struct IntList*)malloc(sizeof(struct IntList));
    list_31->head = 1;
    list_31->tail = list_32;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 call_348 = segTreeOfList_1(segItemTypeInt_, list_31);
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 call_349 = segTreeSet_1(1, 22, call_348);
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 v_10 = call_349;
    void* box_10 = (void*)malloc(sizeof(int));
    (*(((int*)box_10))) = 0;
    void* env_24 = box_10;
    struct IntIntBoolFun2 fun_30 = (struct IntIntBoolFun2){.fun = fun_14, .env = env_24};
    struct IntList* list_36 = (struct IntList*)malloc(sizeof(struct IntList));
    list_36->head = 3;
    list_36->tail = NULL;
    struct IntList* list_35 = (struct IntList*)malloc(sizeof(struct IntList));
    list_35->head = 22;
    list_35->tail = list_36;
    struct IntList* list_34 = (struct IntList*)malloc(sizeof(struct IntList));
    list_34->head = 1;
    list_34->tail = list_35;
    struct IntList* call_350 = segTreeToList_2(v_10);
    int call_351 = listEq_2(fun_30, list_34, call_350);
    milone_assert(call_351);
    int call_352 = 0;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 call_353 = segTreeSet_1(0, 11, v_10);
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 call_354 = segTreeSet_1(2, 33, call_353);
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 v_11 = call_354;
    void* box_11 = (void*)malloc(sizeof(int));
    (*(((int*)box_11))) = 0;
    void* env_25 = box_11;
    struct IntIntBoolFun2 fun_31 = (struct IntIntBoolFun2){.fun = fun_15, .env = env_25};
    struct IntList* list_39 = (struct IntList*)malloc(sizeof(struct IntList));
    list_39->head = 33;
    list_39->tail = NULL;
    struct IntList* list_38 = (struct IntList*)malloc(sizeof(struct IntList));
    list_38->head = 22;
    list_38->tail = list_39;
    struct IntList* list_37 = (struct IntList*)malloc(sizeof(struct IntList));
    list_37->head = 11;
    list_37->tail = list_38;
    struct IntList* call_355 = segTreeToList_2(v_11);
    int call_356 = listEq_2(fun_31, list_37, call_355);
    milone_assert(call_356);
    int call_357 = 0;
    return 0;
}

int testSum_(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 arg_86, int arg_87) {
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 segItemTypeInt_ = arg_86.t0;
    struct IntList* list_45 = (struct IntList*)malloc(sizeof(struct IntList));
    list_45->head = 9;
    list_45->tail = NULL;
    struct IntList* list_44 = (struct IntList*)malloc(sizeof(struct IntList));
    list_44->head = 5;
    list_44->tail = list_45;
    struct IntList* list_43 = (struct IntList*)malloc(sizeof(struct IntList));
    list_43->head = 1;
    list_43->tail = list_44;
    struct IntList* list_42 = (struct IntList*)malloc(sizeof(struct IntList));
    list_42->head = 4;
    list_42->tail = list_43;
    struct IntList* list_41 = (struct IntList*)malloc(sizeof(struct IntList));
    list_41->head = 1;
    list_41->tail = list_42;
    struct IntList* list_40 = (struct IntList*)malloc(sizeof(struct IntList));
    list_40->head = 3;
    list_40->tail = list_41;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 call_358 = segTreeOfList_1(segItemTypeInt_, list_40);
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 v_12 = call_358;
    int call_359 = segTreeSum_1(0, 6, v_12);
    milone_assert((call_359 == (((((3 + 1) + 4) + 1) + 5) + 9)));
    int call_360 = 0;
    int call_361 = segTreeSum_1(2, 4, v_12);
    milone_assert((call_361 == (4 + 1)));
    int call_362 = 0;
    return 0;
}

int sum_(struct IntIntTuple2 arg_88, int acc_4, int i_5, struct IntList* xs_25) {
    int l_1 = arg_88.t0;
    int r_1 = arg_88.t1;
    int match_85;
    if (!(((i_5 == r_1) == 1))) goto next_265;
    match_85 = acc_4;
    goto end_match_264;
next_265:;
    if (!(((i_5 == r_1) == 0))) goto next_266;
    int match_86;
    if (!((!((!(xs_25)))))) goto next_268;
    int x_10 = xs_25->head;
    struct IntList* xs_26 = xs_25->tail;
    int match_87;
    if (!(((i_5 < l_1) == 1))) goto next_271;
    match_87 = acc_4;
    goto end_match_270;
next_271:;
    if (!(((i_5 < l_1) == 0))) goto next_272;
    match_87 = (acc_4 + x_10);
    goto end_match_270;
next_272:;
    exit(1);
end_match_270:;
    int acc_5 = match_87;
    struct IntIntTuple2 tuple_96;
    tuple_96.t0 = l_1;
    tuple_96.t1 = r_1;
    int call_363 = sum_(tuple_96, acc_5, (i_5 + 1), xs_26);
    match_86 = call_363;
    goto end_match_267;
next_268:;
    int call_364 = failwith_1((struct String){.str = "NEVER", .len = 5});
    match_86 = call_364;
    goto end_match_267;
next_269:;
end_match_267:;
    match_85 = match_86;
    goto end_match_264;
next_266:;
    exit(1);
end_match_264:;
    return match_85;
}

struct IntListIntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3IntTuple3 {
    struct IntList* t0;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 t1;
    int t2;
};

int go_15(struct IntListIntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3IntTuple3 arg_89, int l_1, int r_1) {
    struct IntList* xs_24 = arg_89.t0;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 v_13 = arg_89.t1;
    int n_1 = arg_89.t2;
    int match_88;
    if (!(((r_1 == n_1) == 1))) goto next_274;
    int match_89;
    if (!(((l_1 < n_1) == 1))) goto next_277;
    struct IntListIntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3IntTuple3 tuple_97;
    tuple_97.t0 = xs_24;
    tuple_97.t1 = v_13;
    tuple_97.t2 = n_1;
    int call_365 = go_15(tuple_97, (l_1 + 1), (l_1 + 1));
    match_89 = 0;
    goto end_match_276;
next_277:;
    if (!(((l_1 < n_1) == 0))) goto next_278;
    struct IntIntTuple2 tuple_98;
    tuple_98.t0 = l_1;
    tuple_98.t1 = r_1;
    int call_366 = sum_(tuple_98, 0, 0, xs_24);
    int expected_ = call_366;
    int call_367 = segTreeSum_1(l_1, r_1, v_13);
    int actual_ = call_367;
    milone_assert((actual_ == expected_));
    int call_368 = 0;
    struct IntListIntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3IntTuple3 tuple_99;
    tuple_99.t0 = xs_24;
    tuple_99.t1 = v_13;
    tuple_99.t2 = n_1;
    int call_369 = go_15(tuple_99, l_1, (r_1 + 1));
    match_89 = 0;
    goto end_match_276;
next_278:;
    exit(1);
end_match_276:;
    match_88 = 0;
    goto end_match_273;
next_274:;
    if (!(((r_1 == n_1) == 0))) goto next_275;
    match_88 = 0;
    goto end_match_273;
next_275:;
    exit(1);
end_match_273:;
    return 0;
}

int testSumMore_(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 arg_90, int arg_91) {
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 segItemTypeInt_ = arg_90.t0;
    struct IntList* list_51 = (struct IntList*)malloc(sizeof(struct IntList));
    list_51->head = 9;
    list_51->tail = NULL;
    struct IntList* list_50 = (struct IntList*)malloc(sizeof(struct IntList));
    list_50->head = 5;
    list_50->tail = list_51;
    struct IntList* list_49 = (struct IntList*)malloc(sizeof(struct IntList));
    list_49->head = 1;
    list_49->tail = list_50;
    struct IntList* list_48 = (struct IntList*)malloc(sizeof(struct IntList));
    list_48->head = 4;
    list_48->tail = list_49;
    struct IntList* list_47 = (struct IntList*)malloc(sizeof(struct IntList));
    list_47->head = 1;
    list_47->tail = list_48;
    struct IntList* list_46 = (struct IntList*)malloc(sizeof(struct IntList));
    list_46->head = 3;
    list_46->tail = list_47;
    struct IntList* xs_24 = list_46;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 call_370 = segTreeOfList_1(segItemTypeInt_, xs_24);
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 v_13 = call_370;
    int call_371 = listLength_1(xs_24);
    int n_1 = call_371;
    struct IntListIntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3IntTuple3 tuple_100;
    tuple_100.t0 = xs_24;
    tuple_100.t1 = v_13;
    tuple_100.t2 = n_1;
    int call_372 = go_15(tuple_100, 0, 0);
    return 0;
}

int testBalance_(struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 arg_92, int arg_93) {
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 segItemTypeInt_ = arg_92.t0;
    struct IntList* call_373 = listReplicate_1(1, 1000);
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 call_374 = segTreeOfList_1(segItemTypeInt_, call_373);
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 v_14 = call_374;
    int call_375 = segTreeToHeight_1(v_14);
    milone_assert((call_375 < 100));
    int call_376 = 0;
    return 0;
}

int fun_16(void* env_13, struct String arg_25, struct String arg_26) {
    int call_377 = strEq_(arg_25, arg_26);
    return call_377;
}

int testPolymorphic_(struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 arg_94, int arg_95) {
    struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 segItemTypeStr_ = arg_94.t0;
    struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4StringIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 call_378 = segTreeNew_1(segItemTypeStr_);
    struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4StringIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 call_379 = segTreePush_2((struct String){.str = "a", .len = 1}, call_378);
    struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4StringIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 call_380 = segTreePush_2((struct String){.str = "b", .len = 1}, call_379);
    struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4StringIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 v_15 = call_380;
    void* box_12 = (void*)malloc(sizeof(int));
    (*(((int*)box_12))) = 0;
    void* env_26 = box_12;
    struct StringStringBoolFun2 fun_32 = (struct StringStringBoolFun2){.fun = fun_16, .env = env_26};
    struct StringList* list_53 = (struct StringList*)malloc(sizeof(struct StringList));
    list_53->head = (struct String){.str = "b", .len = 1};
    list_53->tail = NULL;
    struct StringList* list_52 = (struct StringList*)malloc(sizeof(struct StringList));
    list_52->head = (struct String){.str = "a", .len = 1};
    list_52->tail = list_53;
    struct StringList* call_381 = segTreeToList_1(v_15);
    int call_382 = listEq_1(fun_32, list_52, call_381);
    milone_assert(call_382);
    int call_383 = 0;
    return 0;
}

int segTreeTest_(struct ObjectTuple1 arg_96, int arg_97) {
    void* unitObj_ = arg_96.t0;
    struct ObjectTuple1 tuple_101;
    tuple_101.t0 = unitObj_;
    void* box_13 = (void*)malloc(sizeof(int));
    (*(((int*)box_13))) = 0;
    void* env_27 = box_13;
    struct IntIntIntFun2 fun_33 = (struct IntIntIntFun2){.fun = fun_7, .env = env_27};
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 call_384 = segItemTypeNew_1(tuple_101, 0, fun_33);
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 segItemTypeInt_ = call_384;
    struct ObjectTuple1 tuple_102;
    tuple_102.t0 = unitObj_;
    void* box_14 = (void*)malloc(sizeof(int));
    (*(((int*)box_14))) = 0;
    void* env_28 = box_14;
    struct StringStringStringFun2 fun_34 = (struct StringStringStringFun2){.fun = fun_8, .env = env_28};
    struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 call_385 = segItemTypeNew_2(tuple_102, (struct String){.str = "", .len = 0}, fun_34);
    struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 segItemTypeStr_ = call_385;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 tuple_103;
    tuple_103.t0 = segItemTypeInt_;
    int call_386 = testPushPop_(tuple_103, 0);
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 tuple_104;
    tuple_104.t0 = segItemTypeInt_;
    int call_387 = testSet_(tuple_104, 0);
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 tuple_105;
    tuple_105.t0 = segItemTypeInt_;
    int call_388 = testSum_(tuple_105, 0);
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 tuple_106;
    tuple_106.t0 = segItemTypeInt_;
    int call_389 = testSumMore_(tuple_106, 0);
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 tuple_107;
    tuple_107.t0 = segItemTypeInt_;
    int call_390 = testBalance_(tuple_107, 0);
    struct StringStringStringFun2StringIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4Tuple1 tuple_108;
    tuple_108.t0 = segItemTypeStr_;
    int call_391 = testPolymorphic_(tuple_108, 0);
    return 0;
}

int abc140aSolve_(int n_2) {
    return ((n_2 * n_2) * n_2);
}

int abc140aTest_(int arg_98) {
    int call_392 = abc140aSolve_(2);
    milone_assert((call_392 == 8));
    int call_393 = 0;
    int call_394 = abc140aSolve_(1);
    milone_assert((call_394 == 1));
    int call_395 = 0;
    return 0;
}

int abc140aMain_(int arg_99) {
    int call_396 = scanInt_(0);
    int n_3 = call_396;
    int call_397 = abc140aSolve_(n_3);
    int m_2 = call_397;
    printf("%d\n", m_2);
    int call_398 = 0;
    return 0;
}

int fun_22(int __91, int __92) {
    return 0;
}

int fun_17(void* env_14, int arg_27, int arg_28) {
    int call_399 = fun_22(arg_27, arg_28);
    return call_399;
}

struct IntIntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3Tuple4 {
    int t0;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 t1;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 t2;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 t3;
};

int go_16(struct IntIntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3Tuple4 arg_100, int sum_1, int i_6) {
    int n_4 = arg_100.t0;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 a_1 = arg_100.t1;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 b_1 = arg_100.t2;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 c_1 = arg_100.t3;
    int match_90;
    if (!(((i_6 == n_4) == 1))) goto next_280;
    match_90 = sum_1;
    goto end_match_279;
next_280:;
    if (!(((i_6 == n_4) == 0))) goto next_281;
    int call_400 = segTreeGet_1(i_6, a_1);
    int ai_ = call_400;
    int call_401 = segTreeGet_1((ai_ - 1), b_1);
    int eat_ = call_401;
    int match_91;
    int match_92;
    if (!((((i_6 + 1) < n_4) == 1))) goto next_284;
    int call_402 = segTreeGet_1((i_6 + 1), a_1);
    match_92 = (call_402 == (ai_ + 1));
    goto end_match_283;
next_284:;
    if (!((((i_6 + 1) < n_4) == 0))) goto next_285;
    match_92 = 0;
    goto end_match_283;
next_285:;
    exit(1);
end_match_283:;
    if (!((match_92 == 1))) goto next_286;
    int call_403 = segTreeGet_1((ai_ - 1), c_1);
    match_91 = call_403;
    goto end_match_282;
next_286:;
    if (!((match_92 == 0))) goto next_287;
    match_91 = 0;
    goto end_match_282;
next_287:;
    exit(1);
end_match_282:;
    int bonus_ = match_91;
    struct IntIntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3Tuple4 tuple_109;
    tuple_109.t0 = n_4;
    tuple_109.t1 = a_1;
    tuple_109.t2 = b_1;
    tuple_109.t3 = c_1;
    int call_404 = go_16(tuple_109, ((sum_1 + eat_) + bonus_), (i_6 + 1));
    match_90 = call_404;
    goto end_match_279;
next_281:;
    exit(1);
end_match_279:;
    return match_90;
}

int abc140bSolve_(struct ObjectTuple1 arg_101, int n_4, struct IntList* a_, struct IntList* b_, struct IntList* c_) {
    void* unitObj_ = arg_101.t0;
    struct ObjectTuple1 tuple_110;
    tuple_110.t0 = unitObj_;
    void* box_15 = (void*)malloc(sizeof(int));
    (*(((int*)box_15))) = 0;
    void* env_29 = box_15;
    struct IntIntIntFun2 fun_35 = (struct IntIntIntFun2){.fun = fun_17, .env = env_29};
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 call_405 = segItemTypeNew_1(tuple_110, 0, fun_35);
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 segItemTypeInt_1 = call_405;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 call_406 = segTreeOfList_1(segItemTypeInt_1, a_);
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 a_1 = call_406;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 call_407 = segTreeOfList_1(segItemTypeInt_1, b_);
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 b_1 = call_407;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 call_408 = segTreeOfList_1(segItemTypeInt_1, c_);
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 c_1 = call_408;
    struct IntIntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3Tuple4 tuple_111;
    tuple_111.t0 = n_4;
    tuple_111.t1 = a_1;
    tuple_111.t2 = b_1;
    tuple_111.t3 = c_1;
    int call_409 = go_16(tuple_111, 0, 0);
    return call_409;
}

int f_(struct ObjectTuple1 arg_102, struct IntList* a_2, struct IntList* b_2, struct IntList* c_2) {
    void* unitObj_ = arg_102.t0;
    int call_410 = listLength_1(a_2);
    int n_5 = call_410;
    int call_411 = listLength_1(b_2);
    milone_assert((call_411 == n_5));
    int call_412 = 0;
    int call_413 = listLength_1(c_2);
    milone_assert((call_413 == (n_5 - 1)));
    int call_414 = 0;
    struct ObjectTuple1 tuple_112;
    tuple_112.t0 = unitObj_;
    int call_415 = abc140bSolve_(tuple_112, n_5, a_2, b_2, c_2);
    return call_415;
}

int case1_(struct ObjectTuple1 arg_103, int arg_104) {
    void* unitObj_ = arg_103.t0;
    struct IntList* list_56 = (struct IntList*)malloc(sizeof(struct IntList));
    list_56->head = 2;
    list_56->tail = NULL;
    struct IntList* list_55 = (struct IntList*)malloc(sizeof(struct IntList));
    list_55->head = 1;
    list_55->tail = list_56;
    struct IntList* list_54 = (struct IntList*)malloc(sizeof(struct IntList));
    list_54->head = 3;
    list_54->tail = list_55;
    struct IntList* a_3 = list_54;
    struct IntList* list_59 = (struct IntList*)malloc(sizeof(struct IntList));
    list_59->head = 4;
    list_59->tail = NULL;
    struct IntList* list_58 = (struct IntList*)malloc(sizeof(struct IntList));
    list_58->head = 5;
    list_58->tail = list_59;
    struct IntList* list_57 = (struct IntList*)malloc(sizeof(struct IntList));
    list_57->head = 2;
    list_57->tail = list_58;
    struct IntList* b_3 = list_57;
    struct IntList* list_61 = (struct IntList*)malloc(sizeof(struct IntList));
    list_61->head = 6;
    list_61->tail = NULL;
    struct IntList* list_60 = (struct IntList*)malloc(sizeof(struct IntList));
    list_60->head = 3;
    list_60->tail = list_61;
    struct IntList* c_3 = list_60;
    struct ObjectTuple1 tuple_113;
    tuple_113.t0 = unitObj_;
    int call_416 = f_(tuple_113, a_3, b_3, c_3);
    return (call_416 == 14);
}

int case2_(struct ObjectTuple1 arg_105, int arg_106) {
    void* unitObj_ = arg_105.t0;
    struct IntList* list_65 = (struct IntList*)malloc(sizeof(struct IntList));
    list_65->head = 1;
    list_65->tail = NULL;
    struct IntList* list_64 = (struct IntList*)malloc(sizeof(struct IntList));
    list_64->head = 4;
    list_64->tail = list_65;
    struct IntList* list_63 = (struct IntList*)malloc(sizeof(struct IntList));
    list_63->head = 3;
    list_63->tail = list_64;
    struct IntList* list_62 = (struct IntList*)malloc(sizeof(struct IntList));
    list_62->head = 2;
    list_62->tail = list_63;
    struct IntList* a_4 = list_62;
    struct IntList* list_69 = (struct IntList*)malloc(sizeof(struct IntList));
    list_69->head = 24;
    list_69->tail = NULL;
    struct IntList* list_68 = (struct IntList*)malloc(sizeof(struct IntList));
    list_68->head = 8;
    list_68->tail = list_69;
    struct IntList* list_67 = (struct IntList*)malloc(sizeof(struct IntList));
    list_67->head = 5;
    list_67->tail = list_68;
    struct IntList* list_66 = (struct IntList*)malloc(sizeof(struct IntList));
    list_66->head = 13;
    list_66->tail = list_67;
    struct IntList* b_4 = list_66;
    struct IntList* list_72 = (struct IntList*)malloc(sizeof(struct IntList));
    list_72->head = 15;
    list_72->tail = NULL;
    struct IntList* list_71 = (struct IntList*)malloc(sizeof(struct IntList));
    list_71->head = 9;
    list_71->tail = list_72;
    struct IntList* list_70 = (struct IntList*)malloc(sizeof(struct IntList));
    list_70->head = 45;
    list_70->tail = list_71;
    struct IntList* c_4 = list_70;
    struct ObjectTuple1 tuple_114;
    tuple_114.t0 = unitObj_;
    int call_417 = f_(tuple_114, a_4, b_4, c_4);
    return (call_417 == 74);
}

int case3_(struct ObjectTuple1 arg_107, int arg_108) {
    void* unitObj_ = arg_107.t0;
    struct IntList* list_74 = (struct IntList*)malloc(sizeof(struct IntList));
    list_74->head = 2;
    list_74->tail = NULL;
    struct IntList* list_73 = (struct IntList*)malloc(sizeof(struct IntList));
    list_73->head = 1;
    list_73->tail = list_74;
    struct IntList* a_5 = list_73;
    struct IntList* list_76 = (struct IntList*)malloc(sizeof(struct IntList));
    list_76->head = 50;
    list_76->tail = NULL;
    struct IntList* list_75 = (struct IntList*)malloc(sizeof(struct IntList));
    list_75->head = 50;
    list_75->tail = list_76;
    struct IntList* b_5 = list_75;
    struct IntList* list_77 = (struct IntList*)malloc(sizeof(struct IntList));
    list_77->head = 50;
    list_77->tail = NULL;
    struct IntList* c_5 = list_77;
    struct ObjectTuple1 tuple_115;
    tuple_115.t0 = unitObj_;
    int call_418 = f_(tuple_115, a_5, b_5, c_5);
    return (call_418 == 150);
}

int abc140bTest_(struct ObjectTuple1 arg_109, int arg_110) {
    void* unitObj_ = arg_109.t0;
    struct ObjectTuple1 tuple_116;
    tuple_116.t0 = unitObj_;
    int call_419 = case1_(tuple_116, 0);
    milone_assert(call_419);
    int call_420 = 0;
    struct ObjectTuple1 tuple_117;
    tuple_117.t0 = unitObj_;
    int call_421 = case2_(tuple_117, 0);
    milone_assert(call_421);
    int call_422 = 0;
    struct ObjectTuple1 tuple_118;
    tuple_118.t0 = unitObj_;
    int call_423 = case3_(tuple_118, 0);
    milone_assert(call_423);
    int call_424 = 0;
    return 0;
}

int abc140bMain_(struct ObjectTuple1 arg_111, int arg_112) {
    void* unitObj_ = arg_111.t0;
    int call_425 = scanInt_(0);
    int n_6 = call_425;
    struct IntList* call_426 = scanIntList_(n_6);
    struct IntList* a_6 = call_426;
    struct IntList* call_427 = scanIntList_(n_6);
    struct IntList* b_6 = call_427;
    struct IntList* call_428 = scanIntList_((n_6 - 1));
    struct IntList* c_6 = call_428;
    struct ObjectTuple1 tuple_119;
    tuple_119.t0 = unitObj_;
    int call_429 = abc140bSolve_(tuple_119, n_6, a_6, b_6, c_6);
    int m_3 = call_429;
    printf("%d\n", m_3);
    int call_430 = 0;
    return 0;
}

int fun_21(int __93, int __94) {
    return 0;
}

int fun_18(void* env_15, int arg_29, int arg_30) {
    int call_431 = fun_21(arg_29, arg_30);
    return call_431;
}

int fun_19(void* env_16, int arg_31, int arg_32) {
    int call_432 = intMax_(arg_31, arg_32);
    return call_432;
}

int fun_20(void* env_17, int arg_33, int arg_34) {
    int call_433 = intMin_(arg_33, arg_34);
    return call_433;
}

struct IntIntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3Tuple2 {
    int t0;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 t1;
};

struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 go_20(struct IntIntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3Tuple2 arg_113, struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 pos_1, int i_7) {
    int n_7 = arg_113.t0;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 perm_2 = arg_113.t1;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 match_93;
    if (!(((i_7 == (n_7 + 2)) == 1))) goto next_289;
    match_93 = pos_1;
    goto end_match_288;
next_289:;
    if (!(((i_7 == (n_7 + 2)) == 0))) goto next_290;
    int call_434 = segTreeGet_1(i_7, perm_2);
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 call_435 = segTreeSet_1(call_434, i_7, pos_1);
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 pos_2 = call_435;
    struct IntIntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3Tuple2 tuple_120;
    tuple_120.t0 = n_7;
    tuple_120.t1 = perm_2;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 call_436 = go_20(tuple_120, pos_2, (i_7 + 1));
    match_93 = call_436;
    goto end_match_288;
next_290:;
    exit(1);
end_match_288:;
    return match_93;
}

int go_19(struct IntIntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3Tuple2 arg_114, int sum_2, struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 prev_1, struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 next_1, int p_) {
    int n_7 = arg_114.t0;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 pos_ = arg_114.t1;
    int match_94;
    if (!(((p_ < 1) == 1))) goto next_292;
    match_94 = sum_2;
    goto end_match_291;
next_292:;
    if (!(((p_ < 1) == 0))) goto next_293;
    int call_437 = segTreeGet_1(p_, pos_);
    int i_8 = call_437;
    int call_438 = segTreeSum_1(0, i_8, prev_1);
    int x_11 = call_438;
    int call_439 = segTreeSum_1(0, x_11, prev_1);
    int w_ = call_439;
    int match_95;
    if (!(((w_ <= x_11) == 1))) goto next_295;
    match_95 = (x_11 < i_8);
    goto end_match_294;
next_295:;
    if (!(((w_ <= x_11) == 0))) goto next_296;
    match_95 = 0;
    goto end_match_294;
next_296:;
    exit(1);
end_match_294:;
    milone_assert(match_95);
    int call_440 = 0;
    int call_441 = segTreeSum_1((i_8 + 1), (n_7 + 2), next_1);
    int y_5 = call_441;
    int call_442 = segTreeSum_1((y_5 + 1), (n_7 + 2), next_1);
    int z_ = call_442;
    int match_96;
    if (!(((i_8 < y_5) == 1))) goto next_298;
    match_96 = (y_5 <= z_);
    goto end_match_297;
next_298:;
    if (!(((i_8 < y_5) == 0))) goto next_299;
    match_96 = 0;
    goto end_match_297;
next_299:;
    exit(1);
end_match_297:;
    milone_assert(match_96);
    int call_443 = 0;
    int count_ = (((x_11 - w_) * (y_5 - i_8)) + ((i_8 - x_11) * (z_ - y_5)));
    int sum_3 = (sum_2 + (count_ * p_));
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 call_444 = segTreeSet_1(i_8, i_8, prev_1);
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 prev_2 = call_444;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 call_445 = segTreeSet_1(i_8, i_8, next_1);
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 next_2 = call_445;
    struct IntIntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3Tuple2 tuple_121;
    tuple_121.t0 = n_7;
    tuple_121.t1 = pos_;
    int call_446 = go_19(tuple_121, sum_3, prev_2, next_2, (p_ - 1));
    match_94 = call_446;
    goto end_match_291;
next_293:;
    exit(1);
end_match_291:;
    return match_94;
}

int abc140eSolve_(struct ObjectTuple1 arg_115, int n_7, struct IntList* perm_) {
    void* unitObj_ = arg_115.t0;
    struct ObjectTuple1 tuple_122;
    tuple_122.t0 = unitObj_;
    void* box_16 = (void*)malloc(sizeof(int));
    (*(((int*)box_16))) = 0;
    void* env_30 = box_16;
    struct IntIntIntFun2 fun_36 = (struct IntIntIntFun2){.fun = fun_18, .env = env_30};
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 call_447 = segItemTypeNew_1(tuple_122, 0, fun_36);
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 segItemTypeInt_2 = call_447;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 call_448 = segTreeOfList_1(segItemTypeInt_2, perm_);
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 perm_1 = call_448;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 call_449 = segTreeInsert_1(0, (n_7 + 1), perm_1);
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 call_450 = segTreePush_1((n_7 + 2), call_449);
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 perm_2 = call_450;
    int call_451 = segTreeToLength_1(perm_2);
    milone_assert((call_451 == (n_7 + 2)));
    int call_452 = 0;
    struct ObjectTuple1 tuple_123;
    tuple_123.t0 = unitObj_;
    void* box_17 = (void*)malloc(sizeof(int));
    (*(((int*)box_17))) = 0;
    void* env_31 = box_17;
    struct IntIntIntFun2 fun_37 = (struct IntIntIntFun2){.fun = fun_19, .env = env_31};
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 call_453 = segItemTypeNew_1(tuple_123, 0, fun_37);
    struct IntList* call_454 = listReplicate_1(0, (n_7 + 2));
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 call_455 = segTreeOfList_1(call_453, call_454);
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 prev_ = call_455;
    struct ObjectTuple1 tuple_124;
    tuple_124.t0 = unitObj_;
    void* box_18 = (void*)malloc(sizeof(int));
    (*(((int*)box_18))) = 0;
    void* env_32 = box_18;
    struct IntIntIntFun2 fun_38 = (struct IntIntIntFun2){.fun = fun_20, .env = env_32};
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4 call_456 = segItemTypeNew_1(tuple_124, (n_7 + 1), fun_38);
    struct IntList* call_457 = listReplicate_1((n_7 + 1), (n_7 + 2));
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 call_458 = segTreeOfList_1(call_456, call_457);
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 next_ = call_458;
    struct IntList* call_459 = listReplicate_1(0, (n_7 + 3));
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 call_460 = segTreeOfList_1(segItemTypeInt_2, call_459);
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 pos_3 = call_460;
    struct IntIntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3Tuple2 tuple_125;
    tuple_125.t0 = n_7;
    tuple_125.t1 = perm_2;
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 call_461 = go_20(tuple_125, pos_3, 0);
    struct IntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3 pos_ = call_461;
    struct IntIntIntIntFun2IntIntIntObjectSegNodeTag_Tuple5ObjectSegItemTypeTag_Tuple4IntIntIntObjectSegNodeTag_Tuple5SegTreeTag_Tuple3Tuple2 tuple_126;
    tuple_126.t0 = n_7;
    tuple_126.t1 = pos_;
    int call_462 = go_19(tuple_126, 0, prev_, next_, n_7);
    return call_462;
}

int solve_(struct ObjectTuple1 arg_116, struct IntList* p_1, int expected_1) {
    void* unitObj_ = arg_116.t0;
    int call_463 = listLength_1(p_1);
    int n_8 = call_463;
    struct ObjectTuple1 tuple_127;
    tuple_127.t0 = unitObj_;
    int call_464 = abc140eSolve_(tuple_127, n_8, p_1);
    int actual_1 = call_464;
    int match_97;
    if (!(((actual_1 == expected_1) == 1))) goto next_301;
    match_97 = 1;
    goto end_match_300;
next_301:;
    if (!(((actual_1 == expected_1) == 0))) goto next_302;
    printf("actual=%d expected=%d\n", actual_1, expected_1);
    int call_465 = 0;
    match_97 = 0;
    goto end_match_300;
next_302:;
    exit(1);
end_match_300:;
    return match_97;
}

int abc140eTest_(struct ObjectTuple1 arg_117, int arg_118) {
    void* unitObj_ = arg_117.t0;
    struct ObjectTuple1 tuple_128;
    tuple_128.t0 = unitObj_;
    struct IntList* list_80 = (struct IntList*)malloc(sizeof(struct IntList));
    list_80->head = 1;
    list_80->tail = NULL;
    struct IntList* list_79 = (struct IntList*)malloc(sizeof(struct IntList));
    list_79->head = 3;
    list_79->tail = list_80;
    struct IntList* list_78 = (struct IntList*)malloc(sizeof(struct IntList));
    list_78->head = 2;
    list_78->tail = list_79;
    int call_466 = solve_(tuple_128, list_78, 5);
    milone_assert(call_466);
    int call_467 = 0;
    struct ObjectTuple1 tuple_129;
    tuple_129.t0 = unitObj_;
    struct IntList* list_85 = (struct IntList*)malloc(sizeof(struct IntList));
    list_85->head = 5;
    list_85->tail = NULL;
    struct IntList* list_84 = (struct IntList*)malloc(sizeof(struct IntList));
    list_84->head = 4;
    list_84->tail = list_85;
    struct IntList* list_83 = (struct IntList*)malloc(sizeof(struct IntList));
    list_83->head = 3;
    list_83->tail = list_84;
    struct IntList* list_82 = (struct IntList*)malloc(sizeof(struct IntList));
    list_82->head = 2;
    list_82->tail = list_83;
    struct IntList* list_81 = (struct IntList*)malloc(sizeof(struct IntList));
    list_81->head = 1;
    list_81->tail = list_82;
    int call_468 = solve_(tuple_129, list_81, 30);
    milone_assert(call_468);
    int call_469 = 0;
    struct ObjectTuple1 tuple_130;
    tuple_130.t0 = unitObj_;
    struct IntList* list_93 = (struct IntList*)malloc(sizeof(struct IntList));
    list_93->head = 1;
    list_93->tail = NULL;
    struct IntList* list_92 = (struct IntList*)malloc(sizeof(struct IntList));
    list_92->head = 6;
    list_92->tail = list_93;
    struct IntList* list_91 = (struct IntList*)malloc(sizeof(struct IntList));
    list_91->head = 5;
    list_91->tail = list_92;
    struct IntList* list_90 = (struct IntList*)malloc(sizeof(struct IntList));
    list_90->head = 4;
    list_90->tail = list_91;
    struct IntList* list_89 = (struct IntList*)malloc(sizeof(struct IntList));
    list_89->head = 3;
    list_89->tail = list_90;
    struct IntList* list_88 = (struct IntList*)malloc(sizeof(struct IntList));
    list_88->head = 7;
    list_88->tail = list_89;
    struct IntList* list_87 = (struct IntList*)malloc(sizeof(struct IntList));
    list_87->head = 2;
    list_87->tail = list_88;
    struct IntList* list_86 = (struct IntList*)malloc(sizeof(struct IntList));
    list_86->head = 8;
    list_86->tail = list_87;
    int call_470 = solve_(tuple_130, list_86, 136);
    milone_assert(call_470);
    int call_471 = 0;
    return 0;
}

int abc140eMain_(struct ObjectTuple1 arg_119, int arg_120) {
    void* unitObj_ = arg_119.t0;
    int call_472 = scanInt_(0);
    int n_9 = call_472;
    struct IntList* call_473 = scanIntList_(n_9);
    struct IntList* p_2 = call_473;
    struct ObjectTuple1 tuple_131;
    tuple_131.t0 = unitObj_;
    int call_474 = abc140eSolve_(tuple_131, n_9, p_2);
    int m_4 = call_474;
    printf("%d\n", m_4);
    int call_475 = 0;
    return 0;
}

int main() {
    void* box_19 = (void*)malloc(sizeof(int));
    (*(((int*)box_19))) = 0;
    void* unitObj_ = box_19;
    void* box_20 = (void*)malloc(sizeof(int));
    (*(((int*)box_20))) = 0;
    void* env_33 = box_20;
    struct IntObjectFun1 fun_39 = (struct IntObjectFun1){.fun = fun_4, .env = env_33};
    void* box_21 = (void*)malloc(sizeof(int));
    (*(((int*)box_21))) = 0;
    void* env_34 = box_21;
    struct ObjectIntIntFun2 fun_40 = (struct ObjectIntIntFun2){.fun = fun_5, .env = env_34};
    void* box_22 = (void*)malloc(sizeof(int));
    (*(((int*)box_22))) = 0;
    void* env_35 = box_22;
    struct ObjectIntIntObjectFun3 fun_41 = (struct ObjectIntIntObjectFun3){.fun = fun_6, .env = env_35};
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 tuple_132;
    tuple_132.t0 = 0;
    tuple_132.t1 = 4;
    tuple_132.t2 = fun_39;
    tuple_132.t3 = fun_40;
    tuple_132.t4 = fun_41;
    tuple_132.t5 = (struct TypeTag_){.tag = TypeTag_};
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6 typeInt_ = tuple_132;
    struct IntIntIntObjectFun1ObjectIntIntFun2ObjectIntIntObjectFun3TypeTag_Tuple6Tuple1 tuple_133;
    tuple_133.t0 = typeInt_;
    int call_476 = vectorTest_(tuple_133, 0);
    struct ObjectTuple1 tuple_134;
    tuple_134.t0 = unitObj_;
    int call_477 = segTreeTest_(tuple_134, 0);
    int call_478 = abc140aTest_(0);
    struct ObjectTuple1 tuple_135;
    tuple_135.t0 = unitObj_;
    int call_479 = abc140bTest_(tuple_135, 0);
    struct ObjectTuple1 tuple_136;
    tuple_136.t0 = unitObj_;
    int call_480 = abc140eTest_(tuple_136, 0);
    return 0;
}
