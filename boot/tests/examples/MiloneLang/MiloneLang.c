#include "milone.h"

struct String failwith_3(struct String str_);

struct StringList;

struct StringList* failwith_2(struct String str_);

enum Token_Tag;

struct Token_;

struct Token_ failwith_1(struct String str_);

enum HExpr_Tag;

struct HExpr_;

struct HExpr_ failwith_4(struct String str_);

enum HPrim_Tag;

struct HPrim_;

struct Op_HPrim_Fun1;

struct Op_HPrim_Fun1 failwithf_3(struct String str_1);

enum HPat_Tag;

struct HPat_;

enum NameCtx_Tag;

struct NameCtx_;

struct HPat_NameCtx_Tuple2;

struct IntHPat_NameCtx_Tuple2Fun1;

struct IntHPat_NameCtx_Tuple2Fun1 failwithf_2(struct String str_1);

struct IntIntTuple2HPat_NameCtx_Tuple2Fun1;

struct IntIntTuple2HPat_NameCtx_Tuple2Fun1 failwithf_1(struct String str_1);

struct IntStringFun1;

struct IntStringFun1 failwithf_4(struct String str_1);

struct StringList* cons_1(struct String head_, struct StringList* tail_);

int listIsEmpty_4(struct StringList* xs_);

enum DumpTree_Tag;

struct DumpTree_;

struct DumpTree_List;

int listIsEmpty_3(struct DumpTree_List* xs_);

enum APat_Tag;

struct APat_;

struct APat_List;

int listIsEmpty_2(struct APat_List* xs_);

enum AExpr_Tag;

struct AExpr_;

struct AExpr_List;

int listIsEmpty_1(struct AExpr_List* xs_);

int go_86(int len_, struct StringList* xs_2);

int listLength_1(struct StringList* xs_1);

struct IntIntTuple2;

struct Token_IntIntTuple2Tuple2;

struct Token_IntIntTuple2Tuple2List;

struct Token_IntIntTuple2Tuple2List* go_85(struct Token_IntIntTuple2Tuple2List* acc_5, struct Token_IntIntTuple2Tuple2List* xs_5);

enum ATy_Tag;

struct ATy_;

struct ATy_List;

struct ATy_List* go_84(struct ATy_List* acc_5, struct ATy_List* xs_5);

enum AVariant_Tag;

struct AVariant_;

struct AVariant_List;

struct AVariant_List* go_83(struct AVariant_List* acc_5, struct AVariant_List* xs_5);

struct APat_List* go_82(struct APat_List* acc_5, struct APat_List* xs_5);

enum AArm_Tag;

struct AArm_;

struct AArm_List;

struct AArm_List* go_81(struct AArm_List* acc_5, struct AArm_List* xs_5);

struct StringList* go_80(struct StringList* acc_5, struct StringList* xs_5);

struct AExpr_List* go_79(struct AExpr_List* acc_5, struct AExpr_List* xs_5);

struct HExpr_List;

struct HExpr_List* go_78(struct HExpr_List* acc_5, struct HExpr_List* xs_5);

struct DumpTree_List* go_95(struct DumpTree_List* acc_5, struct DumpTree_List* xs_5);

struct StringListList;

struct StringListList* go_94(struct StringListList* acc_5, struct StringListList* xs_5);

enum Ty_Tag;

struct Ty_;

struct Ty_List;

struct Ty_List* go_93(struct Ty_List* acc_5, struct Ty_List* xs_5);

struct HPat_HExpr_HExpr_Tuple3;

struct HPat_HExpr_HExpr_Tuple3List;

struct HPat_HExpr_HExpr_Tuple3List* go_92(struct HPat_HExpr_HExpr_Tuple3List* acc_5, struct HPat_HExpr_HExpr_Tuple3List* xs_5);

struct HPat_List;

struct HPat_List* go_91(struct HPat_List* acc_5, struct HPat_List* xs_5);

struct StringIntBoolTy_Tuple4;

struct StringIntBoolTy_Tuple4List;

struct StringIntBoolTy_Tuple4List* go_90(struct StringIntBoolTy_Tuple4List* acc_5, struct StringIntBoolTy_Tuple4List* xs_5);

struct Token_IntIntTuple2Tuple2List* listRev_8(struct Token_IntIntTuple2Tuple2List* xs_4);

struct ATy_List* listRev_7(struct ATy_List* xs_4);

struct AVariant_List* listRev_6(struct AVariant_List* xs_4);

struct APat_List* listRev_5(struct APat_List* xs_4);

struct AArm_List* listRev_4(struct AArm_List* xs_4);

struct StringList* listRev_3(struct StringList* xs_4);

struct AExpr_List* listRev_2(struct AExpr_List* xs_4);

struct HExpr_List* listRev_1(struct HExpr_List* xs_4);

struct DumpTree_List* listRev_14(struct DumpTree_List* xs_4);

struct StringListList* listRev_13(struct StringListList* xs_4);

struct Ty_List* listRev_12(struct Ty_List* xs_4);

struct HPat_HExpr_HExpr_Tuple3List* listRev_11(struct HPat_HExpr_HExpr_Tuple3List* xs_4);

struct HPat_List* listRev_10(struct HPat_List* xs_4);

struct StringIntBoolTy_Tuple4List* listRev_9(struct StringIntBoolTy_Tuple4List* xs_4);

struct StringIntIntTuple2Tuple2UnitFun1;

struct StringIntIntTuple2Tuple2;

struct StringIntIntTuple2Tuple2List;

int listIter_2(struct StringIntIntTuple2Tuple2UnitFun1 f_, struct StringIntIntTuple2Tuple2List* xs_7);

struct StringIntIntTuple2Tuple2ListUnitFun1;

struct StringIntIntTuple2Tuple2ListList;

int listIter_1(struct StringIntIntTuple2Tuple2ListUnitFun1 f_, struct StringIntIntTuple2Tuple2ListList* xs_7);

struct HExpr_Ty_Fun1;

struct Ty_List* go_77(struct HExpr_Ty_Fun1 f_1, struct Ty_List* acc_6, struct HExpr_List* xs_10);

struct HPat_HExpr_HExpr_Tuple3HPat_HExpr_HExpr_Tuple3Fun1;

struct HPat_HExpr_HExpr_Tuple3List* go_76(struct HPat_HExpr_HExpr_Tuple3HPat_HExpr_HExpr_Tuple3Fun1 f_1, struct HPat_HExpr_HExpr_Tuple3List* acc_6, struct HPat_HExpr_HExpr_Tuple3List* xs_10);

struct HExpr_HExpr_Fun1;

struct HExpr_List* go_75(struct HExpr_HExpr_Fun1 f_1, struct HExpr_List* acc_6, struct HExpr_List* xs_10);

struct HPat_HPat_Fun1;

struct HPat_List* go_74(struct HPat_HPat_Fun1 f_1, struct HPat_List* acc_6, struct HPat_List* xs_10);

struct ATy_DumpTree_Fun1;

struct DumpTree_List* go_73(struct ATy_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct ATy_List* xs_10);

struct AArm_DumpTree_Fun1;

struct DumpTree_List* go_72(struct AArm_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct AArm_List* xs_10);

struct APat_DumpTree_Fun1;

struct DumpTree_List* go_71(struct APat_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct APat_List* xs_10);

struct AExpr_DumpTree_Fun1;

struct DumpTree_List* go_70(struct AExpr_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct AExpr_List* xs_10);

struct AVariant_DumpTree_Fun1;

struct DumpTree_List* go_69(struct AVariant_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct AVariant_List* xs_10);

struct HExpr_DumpTree_Fun1;

struct DumpTree_List* go_68(struct HExpr_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct HExpr_List* xs_10);

struct StringDumpTree_Fun1;

struct DumpTree_List* go_67(struct StringDumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct StringList* xs_10);

struct Ty_List* listMap_11(struct HExpr_Ty_Fun1 f_1, struct HExpr_List* xs_9);

struct HPat_HExpr_HExpr_Tuple3List* listMap_10(struct HPat_HExpr_HExpr_Tuple3HPat_HExpr_HExpr_Tuple3Fun1 f_1, struct HPat_HExpr_HExpr_Tuple3List* xs_9);

struct HExpr_List* listMap_9(struct HExpr_HExpr_Fun1 f_1, struct HExpr_List* xs_9);

struct HPat_List* listMap_8(struct HPat_HPat_Fun1 f_1, struct HPat_List* xs_9);

struct DumpTree_List* listMap_7(struct ATy_DumpTree_Fun1 f_1, struct ATy_List* xs_9);

struct DumpTree_List* listMap_6(struct AArm_DumpTree_Fun1 f_1, struct AArm_List* xs_9);

struct DumpTree_List* listMap_5(struct APat_DumpTree_Fun1 f_1, struct APat_List* xs_9);

struct DumpTree_List* listMap_4(struct AExpr_DumpTree_Fun1 f_1, struct AExpr_List* xs_9);

struct DumpTree_List* listMap_3(struct AVariant_DumpTree_Fun1 f_1, struct AVariant_List* xs_9);

struct DumpTree_List* listMap_2(struct HExpr_DumpTree_Fun1 f_1, struct HExpr_List* xs_9);

struct DumpTree_List* listMap_1(struct StringDumpTree_Fun1 f_1, struct StringList* xs_9);

struct StringListStringListFun1;

struct StringList* go_66(struct StringListStringListFun1 f_3, struct StringList* acc_10, struct StringListList* xs_19);

struct StringList* listChoose_1(struct StringListStringListFun1 f_3, struct StringListList* xs_18);

struct StringListList* gogo_1(struct StringListList* acc_12, struct StringListList* ys_);

struct HExpr_StringListListFun1;

struct StringListList* go_65(struct HExpr_StringListListFun1 f_4, struct StringListList* acc_13, struct HExpr_List* xs_22);

struct StringListList* listCollect_1(struct HExpr_StringListListFun1 f_4, struct HExpr_List* xs_21);

struct StringHExpr_Tuple2;

struct StringHExpr_Tuple2List;

struct StringStringIntFun2;

struct StringHExpr_Tuple2ListStringStringIntFun2Tuple2;

struct HExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4;

struct HExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4StringHExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4Fun2;

struct HExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4 go_64(struct HExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4StringHExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4Fun2 folder_, struct HExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4 state_1, struct StringList* xs_31);

struct HExpr_HExpr_HExpr_Fun2;

struct HExpr_ go_89(struct HExpr_HExpr_HExpr_Fun2 folder_, struct HExpr_ state_1, struct HExpr_List* xs_31);

struct HExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4 listFold_1(struct HExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4StringHExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4Fun2 folder_, struct HExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4 state_, struct StringList* xs_30);

struct HExpr_ listFold_2(struct HExpr_HExpr_HExpr_Fun2 folder_, struct HExpr_ state_, struct HExpr_List* xs_30);

struct HExpr_ listReduce_1(struct HExpr_HExpr_HExpr_Fun2 reducer_, struct HExpr_List* xs_33);

struct Ty_NameCtx_Tuple2;

struct ATy_NameCtx_Tuple2Ty_NameCtx_Tuple2Fun1;

struct ATy_ListNameCtx_Tuple2;

struct Ty_ListNameCtx_Tuple2;

struct ATy_NameCtx_Tuple2;

struct Ty_ListNameCtx_Tuple2 go_63(struct ATy_NameCtx_Tuple2Ty_NameCtx_Tuple2Fun1 f_5, struct Ty_List* acc_17, struct ATy_ListNameCtx_Tuple2 arg_119);

struct HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2;

struct AArm_NameCtx_Tuple2HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2Fun1;

struct AArm_ListNameCtx_Tuple2;

struct HPat_HExpr_HExpr_Tuple3ListNameCtx_Tuple2;

struct AArm_NameCtx_Tuple2;

struct HPat_HExpr_HExpr_Tuple3ListNameCtx_Tuple2 go_62(struct AArm_NameCtx_Tuple2HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2Fun1 f_5, struct HPat_HExpr_HExpr_Tuple3List* acc_17, struct AArm_ListNameCtx_Tuple2 arg_120);

struct HExpr_NameCtx_Tuple2;

struct AExpr_NameCtx_Tuple2HExpr_NameCtx_Tuple2Fun1;

struct AExpr_ListNameCtx_Tuple2;

struct HExpr_ListNameCtx_Tuple2;

struct AExpr_NameCtx_Tuple2;

struct HExpr_ListNameCtx_Tuple2 go_61(struct AExpr_NameCtx_Tuple2HExpr_NameCtx_Tuple2Fun1 f_5, struct HExpr_List* acc_17, struct AExpr_ListNameCtx_Tuple2 arg_121);

struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1;

struct APat_ListNameCtx_Tuple2;

struct HPat_ListNameCtx_Tuple2;

struct APat_NameCtx_Tuple2;

struct HPat_ListNameCtx_Tuple2 go_60(struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1 f_5, struct HPat_List* acc_17, struct APat_ListNameCtx_Tuple2 arg_122);

struct StringIntBoolTy_Tuple4NameCtx_Tuple2;

struct AVariant_NameCtx_Tuple2StringIntBoolTy_Tuple4NameCtx_Tuple2Fun1;

struct AVariant_ListNameCtx_Tuple2;

struct StringIntBoolTy_Tuple4ListNameCtx_Tuple2;

struct AVariant_NameCtx_Tuple2;

struct StringIntBoolTy_Tuple4ListNameCtx_Tuple2 go_59(struct AVariant_NameCtx_Tuple2StringIntBoolTy_Tuple4NameCtx_Tuple2Fun1 f_5, struct StringIntBoolTy_Tuple4List* acc_17, struct AVariant_ListNameCtx_Tuple2 arg_123);

struct Ty_ListNameCtx_Tuple2 stMap_5(struct ATy_NameCtx_Tuple2Ty_NameCtx_Tuple2Fun1 f_5, struct ATy_ListNameCtx_Tuple2 arg_124);

struct HPat_HExpr_HExpr_Tuple3ListNameCtx_Tuple2 stMap_4(struct AArm_NameCtx_Tuple2HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2Fun1 f_5, struct AArm_ListNameCtx_Tuple2 arg_125);

struct HExpr_ListNameCtx_Tuple2 stMap_3(struct AExpr_NameCtx_Tuple2HExpr_NameCtx_Tuple2Fun1 f_5, struct AExpr_ListNameCtx_Tuple2 arg_126);

struct HPat_ListNameCtx_Tuple2 stMap_2(struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1 f_5, struct APat_ListNameCtx_Tuple2 arg_127);

struct StringIntBoolTy_Tuple4ListNameCtx_Tuple2 stMap_1(struct AVariant_NameCtx_Tuple2StringIntBoolTy_Tuple4NameCtx_Tuple2Fun1 f_5, struct AVariant_ListNameCtx_Tuple2 arg_128);

struct IntIntIntFun2;

struct IntStringTuple2;

struct IntStringTuple2List;

struct IntStringTuple2ListIntIntIntFun2Tuple2;

struct IntStringTuple2ListIntIntIntFun2Tuple2 mapEmpty_2(struct IntIntIntFun2 cmp_3);

struct StringHExpr_Tuple2ListStringStringIntFun2Tuple2 mapEmpty_1(struct StringStringIntFun2 cmp_3);

struct IntStringTuple2ListIntIntIntFun2Tuple2 mapAdd_2(int key_, struct String value_3, struct IntStringTuple2ListIntIntIntFun2Tuple2 arg_129);

struct StringHExpr_Tuple2ListStringStringIntFun2Tuple2 mapAdd_1(struct String key_, struct HExpr_ value_3, struct StringHExpr_Tuple2ListStringStringIntFun2Tuple2 arg_130);

struct StringList* go_88(struct IntIntIntFun2 cmp_6, int key_2, struct IntStringTuple2List* assoc_3);

struct HExpr_List* go_87(struct StringStringIntFun2 cmp_6, struct String key_2, struct StringHExpr_Tuple2List* assoc_3);

struct StringList* mapTryFind_2(int key_2, struct IntStringTuple2ListIntIntIntFun2Tuple2 arg_131);

struct HExpr_List* mapTryFind_1(struct String key_2, struct StringHExpr_Tuple2ListStringStringIntFun2Tuple2 arg_132);

struct String mapFind_1(int key_3, struct IntStringTuple2ListIntIntIntFun2Tuple2 map_);

int mapContainsKey_1(struct String key_4, struct StringHExpr_Tuple2ListStringStringIntFun2Tuple2 map_1);

int intMin_(int x_19, int y_6);

int intMax_(int x_20, int y_7);

int intEq_(int x_21, int y_8);

int intCmp_(int x_22, int y_9);

struct String go_30(struct String acc_18, int len_2, int n_1);

struct String intToHexWithPadding_(int len_1, int value_5);

int hexDigitToInt_(char c_6);

int go_31(struct String s_4, int r_20, int acc_19, int i_51);

int intFromHex_(int l_8, int r_20, struct String s_4);

int charSub_(char x_23, char y_10);

int charIsControl_(char c_7);

int charIsSpace_(char c_8);

int charIsDigit_(char c_9);

int charIsAlpha_(char c_10);

int charNeedsEscaping_(char c_11);

struct String charEscape_(char c_12);

int strCmp_(struct String x_24, struct String y_11);

struct String strSlice_(int start_, int endIndex_1, struct String s_5);

struct StringStringListTuple2;

struct StringStringListTuple2 go_32(struct StringList* xs_57, int xn_3);

struct String strConcat_(struct StringList* xs_56);

int go_33(struct String str_2, int i_52);

int strNeedsEscaping_(struct String str_2);

int raw_(struct String str_3, int i_54);

struct IntStringListTuple2;

struct StringList* go_34(struct String str_3, struct StringList* acc_20, int i_53);

struct String strEscape_(struct String str_3);

int locX_(struct IntIntTuple2 arg_133);

int locY_(struct IntIntTuple2 arg_134);

int locIsSameRow_(struct IntIntTuple2 first_, struct IntIntTuple2 second_);

int locIsSameColumn_(struct IntIntTuple2 first_1, struct IntIntTuple2 second_1);

int locInside_(struct IntIntTuple2 firstLoc_, struct IntIntTuple2 secondLoc_);

struct IntIntTuple2 locAddX_(int dx_, struct IntIntTuple2 arg_135);

struct IntIntTuple2 locMax_(struct IntIntTuple2 arg_136, struct IntIntTuple2 arg_137);

struct String locToString_(struct IntIntTuple2 arg_138);

int tokenIsExprOrPatFirst_(struct Token_ token_7);

int tokenIsExprFirst_(struct Token_ token_8);

int tokenIsArgFirst_(struct Token_ token_9);

int tokenIsPatFirst_(struct Token_ token_10);

int tokenIsAccessModifier_(struct Token_ token_11);

enum OpLevel_Tag;

struct OpLevel_;

struct OpLevel_ opLevelToNext_(struct OpLevel_ level_);

enum Lit_Tag;

struct Lit_;

struct Lit_IntIntTuple2Tuple2;

struct APat_ apFalse_(struct Lit_ litFalse_, struct IntIntTuple2 loc_2);

struct APat_ apTrue_(struct Lit_ litTrue_, struct IntIntTuple2 loc_3);

struct AExpr_ListIntIntTuple2Tuple2;

struct AExpr_ axUnit_(struct IntIntTuple2 loc_4);

struct AExpr_ axFalse_(struct Lit_ litFalse_, struct IntIntTuple2 loc_5);

struct AExpr_ axTrue_(struct Lit_ litTrue_, struct IntIntTuple2 loc_6);

struct AExpr_ axNil_(struct IntIntTuple2 loc_7);

enum Op_Tag;

struct Op_;

struct Op_AExpr_AExpr_IntIntTuple2Tuple4;

struct AExpr_ app_(struct IntIntTuple2 loc_8, struct AExpr_ x_30, struct AExpr_ f_8);

struct AExpr_ axApp3_(struct AExpr_ f_7, struct AExpr_ x1_, struct AExpr_ x2_, struct AExpr_ x3_, struct IntIntTuple2 loc_8);

struct AExpr_ axNot_(struct Lit_ litFalse_, struct AExpr_ arg_, struct IntIntTuple2 loc_9);

struct StringDumpTree_ListDumpTree_ListTuple3;

struct DumpTree_ dumpTreeNew_(struct String text_43, struct DumpTree_List* children_);

struct DumpTree_ dumpTreeNewLeaf_(struct String text_44);

struct DumpTree_ dumpTreeAttachNext_(struct DumpTree_ next_1, struct DumpTree_ tree_);

struct DumpTree_ dumpTreeFromError_(struct String msg_, struct IntIntTuple2 arg_139);

struct StringList* goChildren_(struct String eol_1, struct DumpTree_List* children_2, struct StringList* acc_23);

struct StringList* goNext_(struct String eol_2, struct DumpTree_List* next_2, struct StringList* acc_24);

struct StringList* go_35(struct String eol_, struct DumpTree_ node_1, struct StringList* acc_22);

struct String dumpTreeToString_(struct DumpTree_ node_);

int fun_9(void* env_3, int arg_14, int arg_15);

struct IntStringTuple2ListIntIntIntFun2Tuple2IntTuple2;

struct NameCtx_ nameCtxEmpty_(int arg_140);

struct IntNameCtx_Tuple2;

struct IntNameCtx_Tuple2 nameCtxAdd_(struct String ident_, struct NameCtx_ arg_141);

struct String nameCtxFind_(int serial_2, struct NameCtx_ arg_142);

struct Ty_Ty_Fun1;

enum Trait_Tag;

struct Trait_;

struct Ty_Ty_Ty_Tuple3;

struct Trait_ traitMapTys_(struct Ty_Ty_Fun1 f_9, struct Trait_ it_);

enum TyCon_Tag;

struct TyCon_;

struct TyCon_Ty_ListTuple2;

struct Ty_ tyTuple_(struct Ty_List* tys_);

struct Ty_ tyList_(struct Ty_ ty_5);

struct Ty_ tyFun_(struct Ty_ sourceTy_, struct Ty_ targetTy_);

struct Ty_ tyRef_(int serial_3, struct Ty_List* tys_1);

struct StringTy_ListTuple2;

struct Ty_ tyPrimFromIdent_(struct Ty_ tyUnit_, struct Ty_ tyObj_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct String ident_1, struct Ty_List* tys_2, struct IntIntTuple2 loc_10);

struct IntIntIntTuple2Tuple2;

int go_36(int tySerial_, struct Ty_ ty_7);

int tyIsFreeIn_(struct Ty_ ty_6, int tySerial_);

int go_37(struct Ty_List* tys_4);

int tyIsMonomorphic_(struct Ty_ ty_9);

enum TyDef_Tag;

struct TyDef_;

struct StringTy_IntIntTuple2Tuple3;

struct IntList;

struct StringIntListIntIntTuple2Tuple3;

struct String tyDefToIdent_(struct TyDef_ tyDef_);

enum VarDef_Tag;

struct VarDef_;

enum TyScheme_Tag;

struct TyScheme_;

struct StringIntTyScheme_IntIntTuple2Tuple4;

struct StringIntBoolTy_Ty_IntIntTuple2Tuple6;

struct String varDefToIdent_(struct VarDef_ varDef_);

struct Ty_ litToTy_(struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Lit_ lit_);

struct Ty_ meta_(struct IntIntTuple2 noLoc_, int id_);

struct Trait_List;

struct Ty_Trait_ListTuple2;

enum TySpec_Tag;

struct TySpec_;

struct TySpec_ mono_(struct Ty_ ty_10);

struct TySpec_ poly_(struct Ty_ ty_11, struct Trait_List* traits_);

struct TySpec_ primToTySpec_(struct Ty_ tyUnit_, struct Ty_ tyObj_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct IntIntTuple2 noLoc_, struct HPrim_ prim_);

struct HPat_ListTy_IntIntTuple2Tuple3;

struct HPat_ patUnit_(struct Ty_ tyUnit_, struct IntIntTuple2 loc_11);

struct Ty_IntIntTuple2Tuple2;

struct HPat_ patNil_(struct Ty_ itemTy_5, struct IntIntTuple2 loc_12);

struct IntTy_IntIntTuple2Tuple3;

struct HPat_StringTy_IntIntTuple2Tuple4;

struct HPat_HPat_ListTy_IntIntTuple2Tuple4;

struct HPat_HPat_Ty_IntIntTuple2Tuple4;

struct HPat_IntIntIntTuple2Tuple3;

struct HPat_Ty_IntIntTuple2Tuple3;

struct Ty_IntIntTuple2Tuple2 patExtract_(struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct HPat_ pat_);

struct IntIntTuple2IntIntTuple2Fun1;

struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2;

struct HPat_ fun_10(void* env_4, struct HPat_ arg_16);

struct HPat_ fun_11(void* env_5, struct HPat_ arg_19);

struct HPat_ go_38(struct IntIntTuple2IntIntTuple2Fun1 g_, struct Ty_Ty_Fun1 f_10, struct HPat_ pat_3);

struct HPat_ patMap_(struct Ty_Ty_Fun1 f_10, struct IntIntTuple2IntIntTuple2Fun1 g_, struct HPat_ pat_2);

struct HExpr_ hxTrue_(struct Lit_ litTrue_, struct IntIntTuple2 loc_13);

struct HExpr_ hxFalse_(struct Lit_ litFalse_, struct IntIntTuple2 loc_14);

enum InfOp_Tag;

struct InfOp_;

struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4;

struct HExpr_ hxApp_(struct HExpr_ f_11, struct HExpr_ x_33, struct Ty_ ty_27, struct IntIntTuple2 loc_15);

struct HExpr_ hxAnno_(struct HExpr_ expr_, struct Ty_ ty_28, struct IntIntTuple2 loc_16);

struct HExpr_ hxSemi_(struct Ty_ noTy_, struct HExpr_List* items_, struct IntIntTuple2 loc_17);

struct HExpr_ hxCallProc_(struct HExpr_ callee_1, struct HExpr_List* args_1, struct Ty_ resultTy_2, struct IntIntTuple2 loc_18);

struct HExpr_ hxCallClosure_(struct HExpr_ callee_2, struct HExpr_List* args_2, struct Ty_ resultTy_3, struct IntIntTuple2 loc_19);

struct Ty_Ty_Ty_Ty_Ty_Tuple5;

struct Ty_ fun_12(void* env_6, struct HExpr_ arg_22);

struct HExpr_ hxTuple_(struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct HExpr_List* items_1, struct IntIntTuple2 loc_20);

struct HExpr_ hxUnit_(struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct IntIntTuple2 loc_21);

struct HPrim_Ty_IntIntTuple2Tuple3;

struct HExpr_ hxNil_(struct Ty_ itemTy_10, struct IntIntTuple2 loc_22);

int hxIsUnitLit_(struct HExpr_ expr_1);

int hxIsAlwaysTrue_(struct HExpr_ expr_2);

struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4;

struct HExpr_StringTy_IntIntTuple2Tuple4;

struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5;

struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7;

enum TyDecl_Tag;

struct TyDecl_;

struct IntTyDecl_IntIntTuple2Tuple3;

struct StringListIntIntTuple2Tuple2;

struct Ty_IntIntTuple2Tuple2 exprExtract_(struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct HExpr_ expr_3);

struct HPat_ goPat_(struct IntIntTuple2IntIntTuple2Fun1 g_1, struct Ty_Ty_Fun1 f_12, struct HPat_ pat_7);

struct HPat_HExpr_HExpr_Tuple3 fun_3(struct IntIntTuple2IntIntTuple2Fun1 g_1, struct Ty_Ty_Fun1 f_12, struct HPat_HExpr_HExpr_Tuple3 arg_143);

struct HPat_HExpr_HExpr_Tuple3 fun_13(void* env_7, struct HPat_HExpr_HExpr_Tuple3 arg_28);

struct HExpr_ fun_14(void* env_8, struct HExpr_ arg_31);

struct HPat_ fun_15(void* env_9, struct HPat_ arg_34);

struct HExpr_ go_39(struct IntIntTuple2IntIntTuple2Fun1 g_1, struct Ty_Ty_Fun1 f_12, struct HExpr_ expr_5);

struct HExpr_ exprMap_(struct Ty_Ty_Fun1 f_12, struct IntIntTuple2IntIntTuple2Fun1 g_1, struct HExpr_ expr_4);

struct Ty_ exprToTy_(struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct HExpr_ expr_6);

struct IntIntTuple2 go_(int r_, struct String text_, int y_1, int x_2, int i_);

struct IntIntTuple2 locShift_(struct String text_, int l_, int r_, struct IntIntTuple2 arg_144);

int charIsIdent_(char c_);

int charIsOp_(char c_1);

int charIsPun_(char c_2);

int go_1(struct String s_, struct String prefix_, int pi_, int si_);

int strIsFollowedBy_(int i_1, struct String prefix_, struct String s_);

int strIsFollowedByRawQuotes_(int i_2, struct String s_1);

int scanError_(struct String arg_145, int i_3);

int lookEof_(struct String text_1, int i_4);

int lookSpace_(struct String text_2, int i_5);

int go_2(struct String text_3, int i_7);

int scanSpace_(struct String text_3, int i_6);

int lookComment_(struct String text_4, int i_8);

int go_3(struct String text_5, int i_10);

int scanLine_(struct String text_5, int i_9);

int lookPun_(struct String text_6, int i_11);

int scanPun_(struct String text_7, int i_12);

int lookOp_(struct String text_8, int i_13);

int go_4(struct String text_9, int i_15);

int scanOp_(struct String text_9, int i_14);

int lookIdent_(struct String text_10, int i_16);

int go_5(struct String text_11, int i_18);

int scanIdent_(struct String text_11, int i_17);

int lookIntLit_(struct String text_12, int i_19);

int go_6(struct String text_13, int i_21);

int scanIntLit_(struct String text_13, int i_20);

int lookCharLit_(struct String text_14, int i_22);

struct BoolIntTuple2;

struct BoolIntTuple2 go_7(struct String text_15, int i_24);

struct BoolIntTuple2 scanCharLit_(struct String text_15, int i_23);

int lookStrLit_(struct String text_16, int i_25);

struct BoolIntTuple2 go_8(struct String text_17, int i_27);

struct BoolIntTuple2 scanStrLit_(struct String text_17, int i_26);

int lookStrLitRaw_(struct String text_18, int i_28);

struct BoolIntTuple2 go_9(struct String text_19, int i_30);

struct BoolIntTuple2 scanStrLitRaw_(struct String text_19, int i_29);

struct Token_ tokenFromIdent_(struct String text_20, int l_1, int r_1);

struct Token_ tokenFromOp_(struct String text_21, int l_2, int r_2);

struct Token_ tokenFromPun_(struct String text_22, int l_3, int r_3);

struct Token_ tokenFromIntLit_(struct String text_23, int l_4, int r_4);

struct Token_ tokenFromCharLit_(char charNull_, struct String text_24, int l_5, int r_5);

int next_(int r_6, struct String text_25, int i_33);

struct String go_10(int r_6, struct String text_25, struct StringList* acc_, int i_32);

struct Token_ tokenFromStrLit_(struct String text_25, int l_6, int r_6);

struct Token_ tokenFromStrLitRaw_(struct String text_26, int l_7, int r_7);

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4;

struct StringIntTuple2;

struct StringIntTuple2 tokCtxToTextIndex_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 arg_146);

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokCtxSkip_(int r_8, struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 arg_147);

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokCtxPush_(struct Token_ kind_, int r_9, struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 arg_148);

struct Token_IntIntTuple2Tuple2List* tokEof_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 arg_149);

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokError_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_);

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokComment_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_1);

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokSpace_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_2);

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokPun_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_3);

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokOp_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_4);

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokIdent_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_5);

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokIntLit_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_6);

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokCharLit_(char charNull_, struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_7);

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokStrLit_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_8);

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokStrLitRaw_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_9);

struct Token_IntIntTuple2Tuple2List* go_11(char charNull_, struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_10);

struct Token_IntIntTuple2Tuple2List* tokenize_(char charNull_, struct String text_41);

int leadsExpr_1(struct Token_IntIntTuple2Tuple2List* tokens_);

int leadsArg_1(struct Token_IntIntTuple2Tuple2List* tokens_1);

int leadsPat_1(struct Token_IntIntTuple2Tuple2List* tokens_2);

struct IntIntTuple2 nextLoc_1(struct Token_IntIntTuple2Tuple2List* tokens_3);

int nextInside_1(struct IntIntTuple2 baseLoc_, struct Token_IntIntTuple2Tuple2List* tokens_4);

struct StringIntIntTuple2Tuple2List* parseErrorCore_(struct String msg_3, struct IntIntTuple2 loc_30, struct StringIntIntTuple2Tuple2List* errors_1);

struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2;

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyError_1(struct String msg_5, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_150);

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatError_1(struct String msg_6, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_151);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseExprError_1(struct String msg_7, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_152);

struct StringIntIntTuple2Tuple2List* parseNewError_1(struct String msg_8, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_153);

struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_40(struct IntIntTuple2 baseLoc_1, struct ATy_List* acc_25, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_154);

struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyArgs_(struct IntIntTuple2 baseLoc_1, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_155);

struct StringATy_ListIntIntTuple2Tuple3;

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyAtom_(struct IntIntTuple2 baseLoc_2, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_156);

struct ATy_StringIntIntTuple2Tuple3;

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_58(struct IntIntTuple2 baseLoc_3, struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 arg_157);

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTySuffix_(struct IntIntTuple2 baseLoc_3, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_158);

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyPrefix_(struct IntIntTuple2 baseLoc_4, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_159);

struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_42(struct IntIntTuple2 baseLoc_5, struct ATy_List* acc_26, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_160);

struct ATy_ListIntIntTuple2Tuple2;

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyTuple_(struct IntIntTuple2 baseLoc_5, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_161);

struct ATy_ATy_IntIntTuple2Tuple3;

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyFun_(struct IntIntTuple2 baseLoc_6, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_162);

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTy_(struct IntIntTuple2 baseLoc_7, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_163);

struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_43(struct IntIntTuple2 baseLoc_8, struct AVariant_List* acc_27, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_164);

enum ATyDecl_Tag;

struct ATyDecl_;

struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyDeclUnion_(struct IntIntTuple2 baseLoc_8, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_165);

struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyDeclBody_(struct IntIntTuple2 baseLoc_9, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_166);

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatParenBody_(struct IntIntTuple2 baseLoc_10, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_167);

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_44(struct IntIntTuple2 baseLoc_11, struct APat_List* patAcc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_168);

struct APat_ListIntIntTuple2Tuple2;

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatListBody_(struct IntIntTuple2 baseLoc_11, struct IntIntTuple2 bracketLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_169);

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatAtom_(struct IntIntTuple2 baseLoc_12, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_170);

struct APat_StringIntIntTuple2Tuple3;

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatNav_(struct IntIntTuple2 baseLoc_13, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_171);

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_45(struct IntIntTuple2 argBaseLoc_, struct IntIntTuple2 baseLoc_14, struct APat_List* acc_28, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_172);

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatCallArgs_(struct IntIntTuple2 baseLoc_14, struct IntIntTuple2 calleeLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_173);

struct APat_APat_ListIntIntTuple2Tuple3;

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatCall_(struct IntIntTuple2 baseLoc_15, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_174);

struct APat_APat_IntIntTuple2Tuple3;

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatCons_(struct IntIntTuple2 baseLoc_16, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_175);

struct APat_ATy_IntIntTuple2Tuple3;

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatAnno_(struct IntIntTuple2 baseLoc_17, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_176);

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_46(struct IntIntTuple2 baseLoc_18, struct APat_List* acc_29, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_177);

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatTuple_(struct IntIntTuple2 baseLoc_18, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_178);

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatAs_(struct IntIntTuple2 baseLoc_19, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_179);

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatOr_(struct IntIntTuple2 baseLoc_20, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_180);

struct StringAPat_ListIntIntTuple2Tuple3;

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatLet_(struct IntIntTuple2 baseLoc_21, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_181);

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePat_(struct IntIntTuple2 baseLoc_22, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_182);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseRange_(struct IntIntTuple2 baseLoc_23, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_183);

struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseList_(struct IntIntTuple2 baseLoc_24, struct IntIntTuple2 bracketLoc_1, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_184);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseThenClause_(struct IntIntTuple2 baseLoc_25, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_185);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseElseClause_(struct IntIntTuple2 baseLoc_26, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_186);

struct AExpr_AExpr_AExpr_IntIntTuple2Tuple4;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseIf_(struct IntIntTuple2 ifLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_187);

struct APat_AExpr_AExpr_IntIntTuple2Tuple4;

struct AArm_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct AArm_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseMatchArm_(struct IntIntTuple2 matchLoc_, struct IntIntTuple2 armLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_188);

struct AArm_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct AArm_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_47(struct IntIntTuple2 matchLoc_1, struct AArm_List* acc_30, struct IntIntTuple2 armLoc_2, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_189);

struct IntIntTuple2Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct AExpr_AArm_ListIntIntTuple2Tuple3;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseMatch_(struct IntIntTuple2 matchLoc_1, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_190);

struct APat_ListAExpr_IntIntTuple2Tuple3;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseFun_(struct IntIntTuple2 baseLoc_27, struct IntIntTuple2 funLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_191);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseParenBody_(struct IntIntTuple2 baseLoc_28, struct IntIntTuple2 parenLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_192);

struct Token_IntIntTuple2Tuple2List* parseAccessModifier_1(struct Token_IntIntTuple2Tuple2List* tokens_146);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseLet_(struct IntIntTuple2 letLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_193);

struct StringATy_IntIntTuple2Tuple3;

struct StringAVariant_ListIntIntTuple2Tuple3;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyDecl_(struct IntIntTuple2 typeLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_194);

struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_48(struct StringList* acc_31, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_195);

struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePath_(struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_196);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseOpen_(struct IntIntTuple2 openLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_197);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseAtom_(struct IntIntTuple2 baseLoc_30, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_198);

struct AExpr_AExpr_IntIntTuple2Tuple3;

struct AExpr_StringIntIntTuple2Tuple3;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_49(struct IntIntTuple2 baseLoc_31, struct AExpr_ acc_32, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_199);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseSuffix_(struct IntIntTuple2 baseLoc_31, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_200);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_50(struct IntIntTuple2 argBaseLoc_1, struct IntIntTuple2 calleeLoc_3, struct IntIntTuple2 baseLoc_32, struct AExpr_ callee_8, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_201);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseApp_(struct IntIntTuple2 baseLoc_32, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_202);

enum UniOp_Tag;

struct UniOp_;

struct UniOp_AExpr_IntIntTuple2Tuple3;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePrefix_(struct IntIntTuple2 baseLoc_33, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_203);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseNextLevelOp_(struct OpLevel_ level_1, struct IntIntTuple2 baseLoc_34, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_204);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 nextL_(struct IntIntTuple2 baseLoc_35, struct OpLevel_ level_2, struct AExpr_ expr_12, struct Op_ op_, struct IntIntTuple2 opLoc_2, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_205);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 nextR_(struct IntIntTuple2 baseLoc_35, struct OpLevel_ level_2, struct AExpr_ expr_14, struct Op_ op_1, struct IntIntTuple2 opLoc_3, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_206);

struct OpLevel_Token_IntIntTuple2Tuple2ListTuple2;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseOps_(struct OpLevel_ level_2, struct IntIntTuple2 baseLoc_35, struct AExpr_ first_3, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_207);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseOp_(struct OpLevel_ level_3, struct IntIntTuple2 baseLoc_36, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_208);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTupleItem_(struct IntIntTuple2 baseLoc_37, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_209);

struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_51(struct IntIntTuple2 baseLoc_38, struct AExpr_List* acc_33, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_210);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTuple_(struct IntIntTuple2 baseLoc_38, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_211);

struct AExpr_ATy_IntIntTuple2Tuple3;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseAnno_(struct IntIntTuple2 baseLoc_39, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_212);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseExpr_(struct IntIntTuple2 baseLoc_40, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_213);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseStmt_(struct IntIntTuple2 baseLoc_41, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_214);

struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_52(struct IntIntTuple2 baseLoc_42, struct AExpr_List* acc_34, struct IntIntTuple2 alignLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_215);

struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseStmts_(struct IntIntTuple2 baseLoc_42, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_216);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseSemi_(struct IntIntTuple2 baseLoc_43, struct IntIntTuple2 mainLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_217);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTopLevel_(struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_218);

struct AExpr_StringIntIntTuple2Tuple2ListTuple2;

struct AExpr_StringIntIntTuple2Tuple2ListTuple2 parse_(struct Token_IntIntTuple2Tuple2List* tokens_250);

struct HPrim_ opToPrim_(struct Op_ op_2);

struct APat_ go_53(struct IntIntTuple2 loc_69, struct APat_List* pats_5);

struct APat_ desugarListLitPat_(struct APat_List* pats_4, struct IntIntTuple2 loc_69);

struct AExpr_ go_54(struct IntIntTuple2 loc_70, struct AExpr_List* items_10);

struct AExpr_ desugarListLitExpr_(struct AExpr_List* items_9, struct IntIntTuple2 loc_70);

struct AExpr_ desugarIf_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct AExpr_ cond_2, struct AExpr_ body_15, struct AExpr_ alt_2, struct IntIntTuple2 loc_71);

struct AExpr_ desugarFun_(struct APat_List* pats_6, struct AExpr_ body_16, struct IntIntTuple2 loc_72);

struct AExpr_ desugarUniNeg_(struct AExpr_ arg_4, struct IntIntTuple2 loc_73);

struct AExpr_ desugarBinNe_(struct Lit_ litFalse_, struct AExpr_ l_19, struct AExpr_ r_33, struct IntIntTuple2 loc_74);

struct AExpr_ desugarBinLe_(struct Lit_ litFalse_, struct AExpr_ l_20, struct AExpr_ r_34, struct IntIntTuple2 loc_75);

struct AExpr_ desugarBinGt_(struct AExpr_ l_21, struct AExpr_ r_35, struct IntIntTuple2 loc_76);

struct AExpr_ desugarBinGe_(struct Lit_ litFalse_, struct AExpr_ l_22, struct AExpr_ r_36, struct IntIntTuple2 loc_77);

struct AExpr_ desugarBinAnd_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct AExpr_ l_23, struct AExpr_ r_37, struct IntIntTuple2 loc_78);

struct AExpr_ desugarBinOr_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct AExpr_ l_24, struct AExpr_ r_38, struct IntIntTuple2 loc_79);

struct AExpr_ desugarBinPipe_(struct AExpr_ l_25, struct AExpr_ r_39, struct IntIntTuple2 loc_80);

struct BoolAExpr_Tuple2;

struct BoolAExpr_Tuple2 tryDesugarIndexRange_(struct AExpr_ expr_19, struct IntIntTuple2 loc_81);

enum ALet_Tag;

struct ALet_;

struct StringAPat_ListAExpr_AExpr_IntIntTuple2Tuple5;

struct ALet_ desugarLet_(struct APat_ pat_24, struct AExpr_ body_17, struct AExpr_ next_13, struct IntIntTuple2 loc_82);

struct Ty_NameCtx_Tuple2 fun_16(void* env_10, struct ATy_NameCtx_Tuple2 arg_37);

struct Ty_NameCtx_Tuple2 fun_17(void* env_11, struct ATy_NameCtx_Tuple2 arg_38);

struct Ty_NameCtx_Tuple2 onTy_(struct ATy_NameCtx_Tuple2 arg_219);

struct Ty_Tuple1;

struct HPat_NameCtx_Tuple2 fun_18(void* env_12, struct APat_NameCtx_Tuple2 arg_39);

struct HPat_NameCtx_Tuple2 fun_19(void* env_13, struct APat_NameCtx_Tuple2 arg_41);

struct HPat_NameCtx_Tuple2 onPat_(struct Ty_ noTy_, struct APat_NameCtx_Tuple2 arg_220);

struct HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2 onArm_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, struct AArm_NameCtx_Tuple2 arg_221);

struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8;

struct HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2 fun_20(void* env_14, struct AArm_NameCtx_Tuple2 arg_43);

struct HExpr_NameCtx_Tuple2 fun_21(void* env_15, struct AExpr_NameCtx_Tuple2 arg_52);

struct HExpr_NameCtx_Tuple2 fun_22(void* env_16, struct AExpr_NameCtx_Tuple2 arg_61);

struct HPat_NameCtx_Tuple2 fun_23(void* env_17, struct APat_NameCtx_Tuple2 arg_70);

struct BoolTy_NameCtx_Tuple3;

struct StringIntBoolTy_Tuple4NameCtx_Tuple2 onVariant_(struct Ty_ tyUnit_, struct AVariant_NameCtx_Tuple2 arg_222);

struct StringIntBoolTy_Tuple4NameCtx_Tuple2 fun_24(void* env_18, struct AVariant_NameCtx_Tuple2 arg_72);

struct StringStringIntBoolTy_Tuple4ListIntIntTuple2Tuple3;

struct HExpr_NameCtx_Tuple2 onExpr_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, struct AExpr_NameCtx_Tuple2 arg_223);

struct HExpr_NameCtx_Tuple2 astToHir_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, struct AExpr_NameCtx_Tuple2 arg_224);

struct StringListList* fun_25(void* env_19, struct HExpr_ arg_74);

struct StringListList* go_55(struct HExpr_ expr_35);

struct StringListList* findOpenPaths_(struct HExpr_ expr_34);

struct StringList* extractor_(struct String projectName_1, struct StringList* path_6);

struct StringTuple1;

struct StringList* fun_26(void* env_20, struct StringList* arg_75);

struct StringList* findOpenModules_(struct String projectName_1, struct HExpr_ expr_36);

struct HExpr_List* goLast_(struct HExpr_ secondExpr_, struct Ty_ noTy_, struct IntIntTuple2 noLoc_, struct HExpr_List* exprs_5);

struct HExpr_ go_56(struct HExpr_ secondExpr_, struct Ty_ noTy_, struct IntIntTuple2 noLoc_, struct HExpr_ expr_37);

struct HExpr_ spliceExpr_(struct Ty_ noTy_, struct IntIntTuple2 noLoc_, struct HExpr_ firstExpr_, struct HExpr_ secondExpr_);

struct StringStringFun1;

struct StringStringStringFun1Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_CharTuple11;

struct HExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4 fun_27(void* env_21, struct HExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4 arg_77, struct String arg_78);

struct HExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4 go_57(struct String projectName_2, struct StringStringFun1 readModuleFile_1, struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, char charNull_, struct HExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4 arg_225, struct String moduleName_2);

int fun_28(void* env_22, struct String arg_90, struct String arg_91);

struct HExpr_ fun_29(void* env_23, struct HExpr_ arg_92, struct HExpr_ arg_93);

struct HExpr_NameCtx_StringIntIntTuple2Tuple2ListListTuple3;

struct HExpr_NameCtx_StringIntIntTuple2Tuple2ListListTuple3 parseProjectModules_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, struct IntIntTuple2 noLoc_, char charNull_, struct StringStringFun1 readModuleFile_1, struct String projectName_2, struct NameCtx_ nameCtx_60);

struct String litToString_(struct Lit_ lit_5);

struct String tokenToString_(struct Token_ token_12);

struct DumpTree_ fun_30(void* env_24, struct ATy_ arg_96);

struct DumpTree_ fun_31(void* env_25, struct ATy_ arg_97);

struct DumpTree_ fun_32(void* env_26, struct ATy_ arg_98);

struct DumpTree_ atDump_(struct ATy_ ty_43);

struct DumpTree_ fun_33(void* env_27, struct APat_ arg_99);

struct DumpTree_ fun_34(void* env_28, struct APat_ arg_100);

struct DumpTree_ fun_35(void* env_29, struct APat_ arg_101);

struct DumpTree_ fun_36(void* env_30, struct APat_ arg_102);

struct DumpTree_ apDump_(struct APat_ pat_10);

struct DumpTree_ fun_37(void* env_31, struct AExpr_ arg_103);

struct DumpTree_ dumpArm_(struct AArm_ arg_226);

struct DumpTree_ fun_38(void* env_32, struct AArm_ arg_104);

struct DumpTree_ fun_39(void* env_33, struct APat_ arg_105);

struct DumpTree_ fun_40(void* env_34, struct AExpr_ arg_106);

struct DumpTree_ fun_41(void* env_35, struct AExpr_ arg_107);

struct DumpTree_ fun_42(void* env_36, struct AExpr_ arg_108);

struct DumpTree_ dumpVariant_(struct AVariant_ arg_227);

struct DumpTree_ fun_43(void* env_37, struct AVariant_ arg_109);

struct DumpTree_ fun_44(void* env_38, struct String arg_110);

struct DumpTree_ axDump_(struct AExpr_ expr_7);

struct String findIdent_(struct NameCtx_ nameCtx_, int serial_9);

struct NameCtx_Tuple1;

struct DumpTree_ fun_45(void* env_39, struct HExpr_ arg_111);

struct DumpTree_ fun_46(void* env_40, struct String arg_113);

struct DumpTree_ hxDump_(struct NameCtx_ nameCtx_, struct HExpr_ expr_8);

struct String readModuleFile_(struct StringStringFun1 fileReadAllText_1, struct String moduleName_);

struct StringStringFun1Tuple1;

struct String fun_47(void* env_41, struct String arg_114);

int fun_5(struct StringIntIntTuple2Tuple2 arg_228);

int fun_48(void* env_42, struct StringIntIntTuple2Tuple2 arg_116);

int fun_4(struct StringIntIntTuple2Tuple2List* errors_);

int fun_49(void* env_43, struct StringIntIntTuple2Tuple2List* arg_117);

int doSelf_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, struct IntIntTuple2 noLoc_, char charNull_, struct StringStringFun1 fileReadAllText_1);

struct String fileReadAllText_(struct String fileName_);

struct String fun_50(void* env_44, struct String arg_118);

int main();

struct String failwith_3(struct String str_) {
    printf("FATAL ERROR: %s\n", str_.str);
    int call_ = 0;
    exit(1);
    return ((struct String){});
}

struct StringList {
    struct String head;
    struct StringList* tail;
};

struct StringList* failwith_2(struct String str_) {
    printf("FATAL ERROR: %s\n", str_.str);
    int call_1 = 0;
    exit(1);
    return NULL;
}

enum Token_Tag {
    Error_,
    Bool_1,
    Int_1,
    Char_1,
    Str_1,
    Ident_,
    ParenL_,
    ParenR_,
    BracketL_,
    BracketR_,
    Amp_,
    AmpAmp_,
    Arrow_,
    Colon_,
    ColonColon_,
    Comma_,
    Dot_,
    DotDot_,
    Eq_,
    Gt_,
    GtEq_,
    Lt_,
    LtEq_,
    LtGt_,
    Minus_,
    Percent_,
    Pipe_,
    PipeGt_,
    PipePipe_,
    Plus_,
    Semi_,
    Star_,
    Slash_,
    As_,
    Do_,
    Else_,
    Fun_,
    If_,
    In_,
    Internal_,
    Let_,
    Match_,
    Module_,
    Namespace_,
    Of_,
    Open_,
    Private_,
    Public_,
    Rec_,
    Then_,
    Type_,
    When_,
    With_,
};

struct Token_ {
    enum Token_Tag tag;
    union {
        int* Bool_1;
        int* Int_1;
        char* Char_1;
        struct String* Str_1;
        struct String* Ident_;
    };
};

struct Token_ failwith_1(struct String str_) {
    printf("FATAL ERROR: %s\n", str_.str);
    int call_2 = 0;
    exit(1);
    return ((struct Token_){});
}

enum HExpr_Tag {
    Lit_3,
    Ref_2,
    Prim_,
    Match_2,
    Nav_3,
    Inf_,
    Let_2,
    LetFun_1,
    TyDecl_,
    Open_2,
    Error_2,
};

struct HExpr_ {
    enum HExpr_Tag tag;
    union {
        struct Lit_IntIntTuple2Tuple2* Lit_3;
        struct IntTy_IntIntTuple2Tuple3* Ref_2;
        struct HPrim_Ty_IntIntTuple2Tuple3* Prim_;
        struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4* Match_2;
        struct HExpr_StringTy_IntIntTuple2Tuple4* Nav_3;
        struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4* Inf_;
        struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5* Let_2;
        struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7* LetFun_1;
        struct IntTyDecl_IntIntTuple2Tuple3* TyDecl_;
        struct StringListIntIntTuple2Tuple2* Open_2;
        struct StringIntIntTuple2Tuple2* Error_2;
    };
};

struct HExpr_ failwith_4(struct String str_) {
    printf("FATAL ERROR: %s\n", str_.str);
    int call_3 = 0;
    exit(1);
    return ((struct HExpr_){});
}

enum HPrim_Tag {
    Add_3,
    Sub_1,
    Mul_2,
    Div_1,
    Mod_1,
    Eq_3,
    Lt_2,
    Nil_1,
    Cons_4,
    Index_2,
    Not_,
    Exit_,
    Assert_,
    Box_,
    Unbox_,
    Printfn_,
    StrLength_,
    StrGetSlice_,
    Char_3,
    Int_3,
    String_,
    NativeFun_,
};

struct HPrim_ {
    enum HPrim_Tag tag;
    union {
        struct StringIntTuple2* NativeFun_;
    };
};

struct Op_HPrim_Fun1 {
    struct HPrim_(*fun)(void*, struct Op_);
    void* env;
};

struct Op_HPrim_Fun1 failwithf_3(struct String str_1) {
    printf("FATAL ERROR: %s\n", str_1.str);
    int call_4 = 0;
    exit(1);
    return ((struct Op_HPrim_Fun1){});
}

enum HPat_Tag {
    Lit_2,
    Nil_,
    Discard_,
    Ref_1,
    Nav_2,
    Call_1,
    Cons_3,
    Tuple_2,
    As_2,
    Anno_2,
    Or_3,
};

struct HPat_ {
    enum HPat_Tag tag;
    union {
        struct Lit_IntIntTuple2Tuple2* Lit_2;
        struct Ty_IntIntTuple2Tuple2* Nil_;
        struct Ty_IntIntTuple2Tuple2* Discard_;
        struct IntTy_IntIntTuple2Tuple3* Ref_1;
        struct HPat_StringTy_IntIntTuple2Tuple4* Nav_2;
        struct HPat_HPat_ListTy_IntIntTuple2Tuple4* Call_1;
        struct HPat_HPat_Ty_IntIntTuple2Tuple4* Cons_3;
        struct HPat_ListTy_IntIntTuple2Tuple3* Tuple_2;
        struct HPat_IntIntIntTuple2Tuple3* As_2;
        struct HPat_Ty_IntIntTuple2Tuple3* Anno_2;
        struct HPat_HPat_Ty_IntIntTuple2Tuple4* Or_3;
    };
};

enum NameCtx_Tag {
    NameCtx_,
};

struct NameCtx_ {
    enum NameCtx_Tag tag;
    union {
        struct IntStringTuple2ListIntIntIntFun2Tuple2IntTuple2* NameCtx_;
    };
};

struct HPat_NameCtx_Tuple2 {
    struct HPat_ t0;
    struct NameCtx_ t1;
};

struct IntHPat_NameCtx_Tuple2Fun1 {
    struct HPat_NameCtx_Tuple2(*fun)(void*, int);
    void* env;
};

struct IntHPat_NameCtx_Tuple2Fun1 failwithf_2(struct String str_1) {
    printf("FATAL ERROR: %s\n", str_1.str);
    int call_5 = 0;
    exit(1);
    return ((struct IntHPat_NameCtx_Tuple2Fun1){});
}

struct IntIntTuple2HPat_NameCtx_Tuple2Fun1 {
    struct HPat_NameCtx_Tuple2(*fun)(void*, struct IntIntTuple2);
    void* env;
};

struct IntIntTuple2HPat_NameCtx_Tuple2Fun1 failwithf_1(struct String str_1) {
    printf("FATAL ERROR: %s\n", str_1.str);
    int call_6 = 0;
    exit(1);
    return ((struct IntIntTuple2HPat_NameCtx_Tuple2Fun1){});
}

struct IntStringFun1 {
    struct String(*fun)(void*, int);
    void* env;
};

struct IntStringFun1 failwithf_4(struct String str_1) {
    printf("FATAL ERROR: %s\n", str_1.str);
    int call_7 = 0;
    exit(1);
    return ((struct IntStringFun1){});
}

struct StringList* cons_1(struct String head_, struct StringList* tail_) {
    struct StringList* list_ = (struct StringList*)malloc(sizeof(struct StringList));
    list_->head = head_;
    list_->tail = tail_;
    return list_;
}

int listIsEmpty_4(struct StringList* xs_) {
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

enum DumpTree_Tag {
    DumpTree_,
};

struct DumpTree_ {
    enum DumpTree_Tag tag;
    union {
        struct StringDumpTree_ListDumpTree_ListTuple3* DumpTree_;
    };
};

struct DumpTree_List {
    struct DumpTree_ head;
    struct DumpTree_List* tail;
};

int listIsEmpty_3(struct DumpTree_List* xs_) {
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

enum APat_Tag {
    Missing_1,
    Lit_,
    Ident_1,
    ListLit_,
    Nav_,
    Call_,
    Cons_2,
    TupleLit_,
    As_1,
    Anno_,
    Or_2,
    Fun_2,
};

struct APat_ {
    enum APat_Tag tag;
    union {
        struct IntIntTuple2* Missing_1;
        struct Lit_IntIntTuple2Tuple2* Lit_;
        struct StringIntIntTuple2Tuple2* Ident_1;
        struct APat_ListIntIntTuple2Tuple2* ListLit_;
        struct APat_StringIntIntTuple2Tuple3* Nav_;
        struct APat_APat_ListIntIntTuple2Tuple3* Call_;
        struct APat_APat_IntIntTuple2Tuple3* Cons_2;
        struct APat_ListIntIntTuple2Tuple2* TupleLit_;
        struct APat_StringIntIntTuple2Tuple3* As_1;
        struct APat_ATy_IntIntTuple2Tuple3* Anno_;
        struct APat_APat_IntIntTuple2Tuple3* Or_2;
        struct StringAPat_ListIntIntTuple2Tuple3* Fun_2;
    };
};

struct APat_List {
    struct APat_ head;
    struct APat_List* tail;
};

int listIsEmpty_2(struct APat_List* xs_) {
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

enum AExpr_Tag {
    Missing_2,
    Lit_1,
    Ident_2,
    ListLit_1,
    If_1,
    Match_1,
    Fun_3,
    Nav_1,
    Index_,
    Uni_,
    Bin_,
    Range_,
    TupleLit_1,
    Anno_1,
    Semi_1,
    Let_1,
    TySynonym_,
    TyUnion_,
    Open_1,
};

struct AExpr_ {
    enum AExpr_Tag tag;
    union {
        struct IntIntTuple2* Missing_2;
        struct Lit_IntIntTuple2Tuple2* Lit_1;
        struct StringIntIntTuple2Tuple2* Ident_2;
        struct AExpr_ListIntIntTuple2Tuple2* ListLit_1;
        struct AExpr_AExpr_AExpr_IntIntTuple2Tuple4* If_1;
        struct AExpr_AArm_ListIntIntTuple2Tuple3* Match_1;
        struct APat_ListAExpr_IntIntTuple2Tuple3* Fun_3;
        struct AExpr_StringIntIntTuple2Tuple3* Nav_1;
        struct AExpr_AExpr_IntIntTuple2Tuple3* Index_;
        struct UniOp_AExpr_IntIntTuple2Tuple3* Uni_;
        struct Op_AExpr_AExpr_IntIntTuple2Tuple4* Bin_;
        struct AExpr_ListIntIntTuple2Tuple2* Range_;
        struct AExpr_ListIntIntTuple2Tuple2* TupleLit_1;
        struct AExpr_ATy_IntIntTuple2Tuple3* Anno_1;
        struct AExpr_ListIntIntTuple2Tuple2* Semi_1;
        struct APat_AExpr_AExpr_IntIntTuple2Tuple4* Let_1;
        struct StringATy_IntIntTuple2Tuple3* TySynonym_;
        struct StringAVariant_ListIntIntTuple2Tuple3* TyUnion_;
        struct StringListIntIntTuple2Tuple2* Open_1;
    };
};

struct AExpr_List {
    struct AExpr_ head;
    struct AExpr_List* tail;
};

int listIsEmpty_1(struct AExpr_List* xs_) {
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

int go_86(int len_, struct StringList* xs_2) {
    int match_4;
    if ((!((!(xs_2))))) goto next_14;
    match_4 = len_;
    goto end_match_13;
next_14:;
    if ((!(xs_2))) goto next_15;
    struct StringList* xs_3 = xs_2->tail;
    int call_8 = go_86((len_ + 1), xs_3);
    match_4 = call_8;
    goto end_match_13;
next_15:;
    exit(1);
end_match_13:;
    return match_4;
}

int listLength_1(struct StringList* xs_1) {
    int call_9 = go_86(0, xs_1);
    return call_9;
}

struct IntIntTuple2 {
    int t0;
    int t1;
};

struct Token_IntIntTuple2Tuple2 {
    struct Token_ t0;
    struct IntIntTuple2 t1;
};

struct Token_IntIntTuple2Tuple2List {
    struct Token_IntIntTuple2Tuple2 head;
    struct Token_IntIntTuple2Tuple2List* tail;
};

struct Token_IntIntTuple2Tuple2List* go_85(struct Token_IntIntTuple2Tuple2List* acc_5, struct Token_IntIntTuple2Tuple2List* xs_5) {
    struct Token_IntIntTuple2Tuple2List* match_5;
    if ((!((!(xs_5))))) goto next_17;
    match_5 = acc_5;
    goto end_match_16;
next_17:;
    if ((!(xs_5))) goto next_18;
    struct Token_IntIntTuple2Tuple2 x_3 = xs_5->head;
    struct Token_IntIntTuple2Tuple2List* xs_6 = xs_5->tail;
    struct Token_IntIntTuple2Tuple2List* list_1 = (struct Token_IntIntTuple2Tuple2List*)malloc(sizeof(struct Token_IntIntTuple2Tuple2List));
    list_1->head = x_3;
    list_1->tail = acc_5;
    struct Token_IntIntTuple2Tuple2List* call_10 = go_85(list_1, xs_6);
    match_5 = call_10;
    goto end_match_16;
next_18:;
    exit(1);
end_match_16:;
    return match_5;
}

enum ATy_Tag {
    Missing_,
    App_1,
    Suffix_,
    Tuple_,
    Fun_1,
};

struct ATy_ {
    enum ATy_Tag tag;
    union {
        struct IntIntTuple2* Missing_;
        struct StringATy_ListIntIntTuple2Tuple3* App_1;
        struct ATy_StringIntIntTuple2Tuple3* Suffix_;
        struct ATy_ListIntIntTuple2Tuple2* Tuple_;
        struct ATy_ATy_IntIntTuple2Tuple3* Fun_1;
    };
};

struct ATy_List {
    struct ATy_ head;
    struct ATy_List* tail;
};

struct ATy_List* go_84(struct ATy_List* acc_5, struct ATy_List* xs_5) {
    struct ATy_List* match_6;
    if ((!((!(xs_5))))) goto next_20;
    match_6 = acc_5;
    goto end_match_19;
next_20:;
    if ((!(xs_5))) goto next_21;
    struct ATy_ x_3 = xs_5->head;
    struct ATy_List* xs_6 = xs_5->tail;
    struct ATy_List* list_2 = (struct ATy_List*)malloc(sizeof(struct ATy_List));
    list_2->head = x_3;
    list_2->tail = acc_5;
    struct ATy_List* call_11 = go_84(list_2, xs_6);
    match_6 = call_11;
    goto end_match_19;
next_21:;
    exit(1);
end_match_19:;
    return match_6;
}

enum AVariant_Tag {
    AVariant_,
};

struct AVariant_ {
    enum AVariant_Tag tag;
    union {
        struct StringATy_ListIntIntTuple2Tuple3* AVariant_;
    };
};

struct AVariant_List {
    struct AVariant_ head;
    struct AVariant_List* tail;
};

struct AVariant_List* go_83(struct AVariant_List* acc_5, struct AVariant_List* xs_5) {
    struct AVariant_List* match_7;
    if ((!((!(xs_5))))) goto next_23;
    match_7 = acc_5;
    goto end_match_22;
next_23:;
    if ((!(xs_5))) goto next_24;
    struct AVariant_ x_3 = xs_5->head;
    struct AVariant_List* xs_6 = xs_5->tail;
    struct AVariant_List* list_3 = (struct AVariant_List*)malloc(sizeof(struct AVariant_List));
    list_3->head = x_3;
    list_3->tail = acc_5;
    struct AVariant_List* call_12 = go_83(list_3, xs_6);
    match_7 = call_12;
    goto end_match_22;
next_24:;
    exit(1);
end_match_22:;
    return match_7;
}

struct APat_List* go_82(struct APat_List* acc_5, struct APat_List* xs_5) {
    struct APat_List* match_8;
    if ((!((!(xs_5))))) goto next_26;
    match_8 = acc_5;
    goto end_match_25;
next_26:;
    if ((!(xs_5))) goto next_27;
    struct APat_ x_3 = xs_5->head;
    struct APat_List* xs_6 = xs_5->tail;
    struct APat_List* list_4 = (struct APat_List*)malloc(sizeof(struct APat_List));
    list_4->head = x_3;
    list_4->tail = acc_5;
    struct APat_List* call_13 = go_82(list_4, xs_6);
    match_8 = call_13;
    goto end_match_25;
next_27:;
    exit(1);
end_match_25:;
    return match_8;
}

enum AArm_Tag {
    AArm_,
};

struct AArm_ {
    enum AArm_Tag tag;
    union {
        struct APat_AExpr_AExpr_IntIntTuple2Tuple4* AArm_;
    };
};

struct AArm_List {
    struct AArm_ head;
    struct AArm_List* tail;
};

struct AArm_List* go_81(struct AArm_List* acc_5, struct AArm_List* xs_5) {
    struct AArm_List* match_9;
    if ((!((!(xs_5))))) goto next_29;
    match_9 = acc_5;
    goto end_match_28;
next_29:;
    if ((!(xs_5))) goto next_30;
    struct AArm_ x_3 = xs_5->head;
    struct AArm_List* xs_6 = xs_5->tail;
    struct AArm_List* list_5 = (struct AArm_List*)malloc(sizeof(struct AArm_List));
    list_5->head = x_3;
    list_5->tail = acc_5;
    struct AArm_List* call_14 = go_81(list_5, xs_6);
    match_9 = call_14;
    goto end_match_28;
next_30:;
    exit(1);
end_match_28:;
    return match_9;
}

struct StringList* go_80(struct StringList* acc_5, struct StringList* xs_5) {
    struct StringList* match_10;
    if ((!((!(xs_5))))) goto next_32;
    match_10 = acc_5;
    goto end_match_31;
next_32:;
    if ((!(xs_5))) goto next_33;
    struct String x_3 = xs_5->head;
    struct StringList* xs_6 = xs_5->tail;
    struct StringList* list_6 = (struct StringList*)malloc(sizeof(struct StringList));
    list_6->head = x_3;
    list_6->tail = acc_5;
    struct StringList* call_15 = go_80(list_6, xs_6);
    match_10 = call_15;
    goto end_match_31;
next_33:;
    exit(1);
end_match_31:;
    return match_10;
}

struct AExpr_List* go_79(struct AExpr_List* acc_5, struct AExpr_List* xs_5) {
    struct AExpr_List* match_11;
    if ((!((!(xs_5))))) goto next_35;
    match_11 = acc_5;
    goto end_match_34;
next_35:;
    if ((!(xs_5))) goto next_36;
    struct AExpr_ x_3 = xs_5->head;
    struct AExpr_List* xs_6 = xs_5->tail;
    struct AExpr_List* list_7 = (struct AExpr_List*)malloc(sizeof(struct AExpr_List));
    list_7->head = x_3;
    list_7->tail = acc_5;
    struct AExpr_List* call_16 = go_79(list_7, xs_6);
    match_11 = call_16;
    goto end_match_34;
next_36:;
    exit(1);
end_match_34:;
    return match_11;
}

struct HExpr_List {
    struct HExpr_ head;
    struct HExpr_List* tail;
};

struct HExpr_List* go_78(struct HExpr_List* acc_5, struct HExpr_List* xs_5) {
    struct HExpr_List* match_12;
    if ((!((!(xs_5))))) goto next_38;
    match_12 = acc_5;
    goto end_match_37;
next_38:;
    if ((!(xs_5))) goto next_39;
    struct HExpr_ x_3 = xs_5->head;
    struct HExpr_List* xs_6 = xs_5->tail;
    struct HExpr_List* list_8 = (struct HExpr_List*)malloc(sizeof(struct HExpr_List));
    list_8->head = x_3;
    list_8->tail = acc_5;
    struct HExpr_List* call_17 = go_78(list_8, xs_6);
    match_12 = call_17;
    goto end_match_37;
next_39:;
    exit(1);
end_match_37:;
    return match_12;
}

struct DumpTree_List* go_95(struct DumpTree_List* acc_5, struct DumpTree_List* xs_5) {
    struct DumpTree_List* match_13;
    if ((!((!(xs_5))))) goto next_41;
    match_13 = acc_5;
    goto end_match_40;
next_41:;
    if ((!(xs_5))) goto next_42;
    struct DumpTree_ x_3 = xs_5->head;
    struct DumpTree_List* xs_6 = xs_5->tail;
    struct DumpTree_List* list_9 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_9->head = x_3;
    list_9->tail = acc_5;
    struct DumpTree_List* call_18 = go_95(list_9, xs_6);
    match_13 = call_18;
    goto end_match_40;
next_42:;
    exit(1);
end_match_40:;
    return match_13;
}

struct StringListList {
    struct StringList* head;
    struct StringListList* tail;
};

struct StringListList* go_94(struct StringListList* acc_5, struct StringListList* xs_5) {
    struct StringListList* match_14;
    if ((!((!(xs_5))))) goto next_44;
    match_14 = acc_5;
    goto end_match_43;
next_44:;
    if ((!(xs_5))) goto next_45;
    struct StringList* x_3 = xs_5->head;
    struct StringListList* xs_6 = xs_5->tail;
    struct StringListList* list_10 = (struct StringListList*)malloc(sizeof(struct StringListList));
    list_10->head = x_3;
    list_10->tail = acc_5;
    struct StringListList* call_19 = go_94(list_10, xs_6);
    match_14 = call_19;
    goto end_match_43;
next_45:;
    exit(1);
end_match_43:;
    return match_14;
}

enum Ty_Tag {
    Error_1,
    Meta_,
    Con_,
};

struct Ty_ {
    enum Ty_Tag tag;
    union {
        struct IntIntTuple2* Error_1;
        struct IntIntIntTuple2Tuple2* Meta_;
        struct TyCon_Ty_ListTuple2* Con_;
    };
};

struct Ty_List {
    struct Ty_ head;
    struct Ty_List* tail;
};

struct Ty_List* go_93(struct Ty_List* acc_5, struct Ty_List* xs_5) {
    struct Ty_List* match_15;
    if ((!((!(xs_5))))) goto next_47;
    match_15 = acc_5;
    goto end_match_46;
next_47:;
    if ((!(xs_5))) goto next_48;
    struct Ty_ x_3 = xs_5->head;
    struct Ty_List* xs_6 = xs_5->tail;
    struct Ty_List* list_11 = (struct Ty_List*)malloc(sizeof(struct Ty_List));
    list_11->head = x_3;
    list_11->tail = acc_5;
    struct Ty_List* call_20 = go_93(list_11, xs_6);
    match_15 = call_20;
    goto end_match_46;
next_48:;
    exit(1);
end_match_46:;
    return match_15;
}

struct HPat_HExpr_HExpr_Tuple3 {
    struct HPat_ t0;
    struct HExpr_ t1;
    struct HExpr_ t2;
};

struct HPat_HExpr_HExpr_Tuple3List {
    struct HPat_HExpr_HExpr_Tuple3 head;
    struct HPat_HExpr_HExpr_Tuple3List* tail;
};

struct HPat_HExpr_HExpr_Tuple3List* go_92(struct HPat_HExpr_HExpr_Tuple3List* acc_5, struct HPat_HExpr_HExpr_Tuple3List* xs_5) {
    struct HPat_HExpr_HExpr_Tuple3List* match_16;
    if ((!((!(xs_5))))) goto next_50;
    match_16 = acc_5;
    goto end_match_49;
next_50:;
    if ((!(xs_5))) goto next_51;
    struct HPat_HExpr_HExpr_Tuple3 x_3 = xs_5->head;
    struct HPat_HExpr_HExpr_Tuple3List* xs_6 = xs_5->tail;
    struct HPat_HExpr_HExpr_Tuple3List* list_12 = (struct HPat_HExpr_HExpr_Tuple3List*)malloc(sizeof(struct HPat_HExpr_HExpr_Tuple3List));
    list_12->head = x_3;
    list_12->tail = acc_5;
    struct HPat_HExpr_HExpr_Tuple3List* call_21 = go_92(list_12, xs_6);
    match_16 = call_21;
    goto end_match_49;
next_51:;
    exit(1);
end_match_49:;
    return match_16;
}

struct HPat_List {
    struct HPat_ head;
    struct HPat_List* tail;
};

struct HPat_List* go_91(struct HPat_List* acc_5, struct HPat_List* xs_5) {
    struct HPat_List* match_17;
    if ((!((!(xs_5))))) goto next_53;
    match_17 = acc_5;
    goto end_match_52;
next_53:;
    if ((!(xs_5))) goto next_54;
    struct HPat_ x_3 = xs_5->head;
    struct HPat_List* xs_6 = xs_5->tail;
    struct HPat_List* list_13 = (struct HPat_List*)malloc(sizeof(struct HPat_List));
    list_13->head = x_3;
    list_13->tail = acc_5;
    struct HPat_List* call_22 = go_91(list_13, xs_6);
    match_17 = call_22;
    goto end_match_52;
next_54:;
    exit(1);
end_match_52:;
    return match_17;
}

struct StringIntBoolTy_Tuple4 {
    struct String t0;
    int t1;
    int t2;
    struct Ty_ t3;
};

struct StringIntBoolTy_Tuple4List {
    struct StringIntBoolTy_Tuple4 head;
    struct StringIntBoolTy_Tuple4List* tail;
};

struct StringIntBoolTy_Tuple4List* go_90(struct StringIntBoolTy_Tuple4List* acc_5, struct StringIntBoolTy_Tuple4List* xs_5) {
    struct StringIntBoolTy_Tuple4List* match_18;
    if ((!((!(xs_5))))) goto next_56;
    match_18 = acc_5;
    goto end_match_55;
next_56:;
    if ((!(xs_5))) goto next_57;
    struct StringIntBoolTy_Tuple4 x_3 = xs_5->head;
    struct StringIntBoolTy_Tuple4List* xs_6 = xs_5->tail;
    struct StringIntBoolTy_Tuple4List* list_14 = (struct StringIntBoolTy_Tuple4List*)malloc(sizeof(struct StringIntBoolTy_Tuple4List));
    list_14->head = x_3;
    list_14->tail = acc_5;
    struct StringIntBoolTy_Tuple4List* call_23 = go_90(list_14, xs_6);
    match_18 = call_23;
    goto end_match_55;
next_57:;
    exit(1);
end_match_55:;
    return match_18;
}

struct Token_IntIntTuple2Tuple2List* listRev_8(struct Token_IntIntTuple2Tuple2List* xs_4) {
    struct Token_IntIntTuple2Tuple2List* call_24 = go_85(NULL, xs_4);
    return call_24;
}

struct ATy_List* listRev_7(struct ATy_List* xs_4) {
    struct ATy_List* call_25 = go_84(NULL, xs_4);
    return call_25;
}

struct AVariant_List* listRev_6(struct AVariant_List* xs_4) {
    struct AVariant_List* call_26 = go_83(NULL, xs_4);
    return call_26;
}

struct APat_List* listRev_5(struct APat_List* xs_4) {
    struct APat_List* call_27 = go_82(NULL, xs_4);
    return call_27;
}

struct AArm_List* listRev_4(struct AArm_List* xs_4) {
    struct AArm_List* call_28 = go_81(NULL, xs_4);
    return call_28;
}

struct StringList* listRev_3(struct StringList* xs_4) {
    struct StringList* call_29 = go_80(NULL, xs_4);
    return call_29;
}

struct AExpr_List* listRev_2(struct AExpr_List* xs_4) {
    struct AExpr_List* call_30 = go_79(NULL, xs_4);
    return call_30;
}

struct HExpr_List* listRev_1(struct HExpr_List* xs_4) {
    struct HExpr_List* call_31 = go_78(NULL, xs_4);
    return call_31;
}

struct DumpTree_List* listRev_14(struct DumpTree_List* xs_4) {
    struct DumpTree_List* call_32 = go_95(NULL, xs_4);
    return call_32;
}

struct StringListList* listRev_13(struct StringListList* xs_4) {
    struct StringListList* call_33 = go_94(NULL, xs_4);
    return call_33;
}

struct Ty_List* listRev_12(struct Ty_List* xs_4) {
    struct Ty_List* call_34 = go_93(NULL, xs_4);
    return call_34;
}

struct HPat_HExpr_HExpr_Tuple3List* listRev_11(struct HPat_HExpr_HExpr_Tuple3List* xs_4) {
    struct HPat_HExpr_HExpr_Tuple3List* call_35 = go_92(NULL, xs_4);
    return call_35;
}

struct HPat_List* listRev_10(struct HPat_List* xs_4) {
    struct HPat_List* call_36 = go_91(NULL, xs_4);
    return call_36;
}

struct StringIntBoolTy_Tuple4List* listRev_9(struct StringIntBoolTy_Tuple4List* xs_4) {
    struct StringIntBoolTy_Tuple4List* call_37 = go_90(NULL, xs_4);
    return call_37;
}

struct StringIntIntTuple2Tuple2UnitFun1 {
    int(*fun)(void*, struct StringIntIntTuple2Tuple2);
    void* env;
};

struct StringIntIntTuple2Tuple2 {
    struct String t0;
    struct IntIntTuple2 t1;
};

struct StringIntIntTuple2Tuple2List {
    struct StringIntIntTuple2Tuple2 head;
    struct StringIntIntTuple2Tuple2List* tail;
};

int listIter_2(struct StringIntIntTuple2Tuple2UnitFun1 f_, struct StringIntIntTuple2Tuple2List* xs_7) {
    int match_19;
    if ((!((!(xs_7))))) goto next_59;
    match_19 = 0;
    goto end_match_58;
next_59:;
    if ((!(xs_7))) goto next_60;
    struct StringIntIntTuple2Tuple2 x_4 = xs_7->head;
    struct StringIntIntTuple2Tuple2List* xs_8 = xs_7->tail;
    int app_1 = f_.fun(f_.env, x_4);
    int call_38 = listIter_2(f_, xs_8);
    match_19 = 0;
    goto end_match_58;
next_60:;
    exit(1);
end_match_58:;
    return 0;
}

struct StringIntIntTuple2Tuple2ListUnitFun1 {
    int(*fun)(void*, struct StringIntIntTuple2Tuple2List*);
    void* env;
};

struct StringIntIntTuple2Tuple2ListList {
    struct StringIntIntTuple2Tuple2List* head;
    struct StringIntIntTuple2Tuple2ListList* tail;
};

int listIter_1(struct StringIntIntTuple2Tuple2ListUnitFun1 f_, struct StringIntIntTuple2Tuple2ListList* xs_7) {
    int match_20;
    if ((!((!(xs_7))))) goto next_62;
    match_20 = 0;
    goto end_match_61;
next_62:;
    if ((!(xs_7))) goto next_63;
    struct StringIntIntTuple2Tuple2List* x_4 = xs_7->head;
    struct StringIntIntTuple2Tuple2ListList* xs_8 = xs_7->tail;
    int app_2 = f_.fun(f_.env, x_4);
    int call_39 = listIter_1(f_, xs_8);
    match_20 = 0;
    goto end_match_61;
next_63:;
    exit(1);
end_match_61:;
    return 0;
}

struct HExpr_Ty_Fun1 {
    struct Ty_(*fun)(void*, struct HExpr_);
    void* env;
};

struct Ty_List* go_77(struct HExpr_Ty_Fun1 f_1, struct Ty_List* acc_6, struct HExpr_List* xs_10) {
    struct Ty_List* match_21;
    if ((!((!(xs_10))))) goto next_65;
    struct Ty_List* call_40 = listRev_12(acc_6);
    match_21 = call_40;
    goto end_match_64;
next_65:;
    if ((!(xs_10))) goto next_66;
    struct HExpr_ x_5 = xs_10->head;
    struct HExpr_List* xs_11 = xs_10->tail;
    struct Ty_ app_3 = f_1.fun(f_1.env, x_5);
    struct Ty_List* list_15 = (struct Ty_List*)malloc(sizeof(struct Ty_List));
    list_15->head = app_3;
    list_15->tail = acc_6;
    struct Ty_List* call_41 = go_77(f_1, list_15, xs_11);
    match_21 = call_41;
    goto end_match_64;
next_66:;
    exit(1);
end_match_64:;
    return match_21;
}

struct HPat_HExpr_HExpr_Tuple3HPat_HExpr_HExpr_Tuple3Fun1 {
    struct HPat_HExpr_HExpr_Tuple3(*fun)(void*, struct HPat_HExpr_HExpr_Tuple3);
    void* env;
};

struct HPat_HExpr_HExpr_Tuple3List* go_76(struct HPat_HExpr_HExpr_Tuple3HPat_HExpr_HExpr_Tuple3Fun1 f_1, struct HPat_HExpr_HExpr_Tuple3List* acc_6, struct HPat_HExpr_HExpr_Tuple3List* xs_10) {
    struct HPat_HExpr_HExpr_Tuple3List* match_22;
    if ((!((!(xs_10))))) goto next_68;
    struct HPat_HExpr_HExpr_Tuple3List* call_42 = listRev_11(acc_6);
    match_22 = call_42;
    goto end_match_67;
next_68:;
    if ((!(xs_10))) goto next_69;
    struct HPat_HExpr_HExpr_Tuple3 x_5 = xs_10->head;
    struct HPat_HExpr_HExpr_Tuple3List* xs_11 = xs_10->tail;
    struct HPat_HExpr_HExpr_Tuple3 app_4 = f_1.fun(f_1.env, x_5);
    struct HPat_HExpr_HExpr_Tuple3List* list_16 = (struct HPat_HExpr_HExpr_Tuple3List*)malloc(sizeof(struct HPat_HExpr_HExpr_Tuple3List));
    list_16->head = app_4;
    list_16->tail = acc_6;
    struct HPat_HExpr_HExpr_Tuple3List* call_43 = go_76(f_1, list_16, xs_11);
    match_22 = call_43;
    goto end_match_67;
next_69:;
    exit(1);
end_match_67:;
    return match_22;
}

struct HExpr_HExpr_Fun1 {
    struct HExpr_(*fun)(void*, struct HExpr_);
    void* env;
};

struct HExpr_List* go_75(struct HExpr_HExpr_Fun1 f_1, struct HExpr_List* acc_6, struct HExpr_List* xs_10) {
    struct HExpr_List* match_23;
    if ((!((!(xs_10))))) goto next_71;
    struct HExpr_List* call_44 = listRev_1(acc_6);
    match_23 = call_44;
    goto end_match_70;
next_71:;
    if ((!(xs_10))) goto next_72;
    struct HExpr_ x_5 = xs_10->head;
    struct HExpr_List* xs_11 = xs_10->tail;
    struct HExpr_ app_5 = f_1.fun(f_1.env, x_5);
    struct HExpr_List* list_17 = (struct HExpr_List*)malloc(sizeof(struct HExpr_List));
    list_17->head = app_5;
    list_17->tail = acc_6;
    struct HExpr_List* call_45 = go_75(f_1, list_17, xs_11);
    match_23 = call_45;
    goto end_match_70;
next_72:;
    exit(1);
end_match_70:;
    return match_23;
}

struct HPat_HPat_Fun1 {
    struct HPat_(*fun)(void*, struct HPat_);
    void* env;
};

struct HPat_List* go_74(struct HPat_HPat_Fun1 f_1, struct HPat_List* acc_6, struct HPat_List* xs_10) {
    struct HPat_List* match_24;
    if ((!((!(xs_10))))) goto next_74;
    struct HPat_List* call_46 = listRev_10(acc_6);
    match_24 = call_46;
    goto end_match_73;
next_74:;
    if ((!(xs_10))) goto next_75;
    struct HPat_ x_5 = xs_10->head;
    struct HPat_List* xs_11 = xs_10->tail;
    struct HPat_ app_6 = f_1.fun(f_1.env, x_5);
    struct HPat_List* list_18 = (struct HPat_List*)malloc(sizeof(struct HPat_List));
    list_18->head = app_6;
    list_18->tail = acc_6;
    struct HPat_List* call_47 = go_74(f_1, list_18, xs_11);
    match_24 = call_47;
    goto end_match_73;
next_75:;
    exit(1);
end_match_73:;
    return match_24;
}

struct ATy_DumpTree_Fun1 {
    struct DumpTree_(*fun)(void*, struct ATy_);
    void* env;
};

struct DumpTree_List* go_73(struct ATy_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct ATy_List* xs_10) {
    struct DumpTree_List* match_25;
    if ((!((!(xs_10))))) goto next_77;
    struct DumpTree_List* call_48 = listRev_14(acc_6);
    match_25 = call_48;
    goto end_match_76;
next_77:;
    if ((!(xs_10))) goto next_78;
    struct ATy_ x_5 = xs_10->head;
    struct ATy_List* xs_11 = xs_10->tail;
    struct DumpTree_ app_7 = f_1.fun(f_1.env, x_5);
    struct DumpTree_List* list_19 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_19->head = app_7;
    list_19->tail = acc_6;
    struct DumpTree_List* call_49 = go_73(f_1, list_19, xs_11);
    match_25 = call_49;
    goto end_match_76;
next_78:;
    exit(1);
end_match_76:;
    return match_25;
}

struct AArm_DumpTree_Fun1 {
    struct DumpTree_(*fun)(void*, struct AArm_);
    void* env;
};

struct DumpTree_List* go_72(struct AArm_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct AArm_List* xs_10) {
    struct DumpTree_List* match_26;
    if ((!((!(xs_10))))) goto next_80;
    struct DumpTree_List* call_50 = listRev_14(acc_6);
    match_26 = call_50;
    goto end_match_79;
next_80:;
    if ((!(xs_10))) goto next_81;
    struct AArm_ x_5 = xs_10->head;
    struct AArm_List* xs_11 = xs_10->tail;
    struct DumpTree_ app_8 = f_1.fun(f_1.env, x_5);
    struct DumpTree_List* list_20 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_20->head = app_8;
    list_20->tail = acc_6;
    struct DumpTree_List* call_51 = go_72(f_1, list_20, xs_11);
    match_26 = call_51;
    goto end_match_79;
next_81:;
    exit(1);
end_match_79:;
    return match_26;
}

struct APat_DumpTree_Fun1 {
    struct DumpTree_(*fun)(void*, struct APat_);
    void* env;
};

struct DumpTree_List* go_71(struct APat_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct APat_List* xs_10) {
    struct DumpTree_List* match_27;
    if ((!((!(xs_10))))) goto next_83;
    struct DumpTree_List* call_52 = listRev_14(acc_6);
    match_27 = call_52;
    goto end_match_82;
next_83:;
    if ((!(xs_10))) goto next_84;
    struct APat_ x_5 = xs_10->head;
    struct APat_List* xs_11 = xs_10->tail;
    struct DumpTree_ app_9 = f_1.fun(f_1.env, x_5);
    struct DumpTree_List* list_21 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_21->head = app_9;
    list_21->tail = acc_6;
    struct DumpTree_List* call_53 = go_71(f_1, list_21, xs_11);
    match_27 = call_53;
    goto end_match_82;
next_84:;
    exit(1);
end_match_82:;
    return match_27;
}

struct AExpr_DumpTree_Fun1 {
    struct DumpTree_(*fun)(void*, struct AExpr_);
    void* env;
};

struct DumpTree_List* go_70(struct AExpr_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct AExpr_List* xs_10) {
    struct DumpTree_List* match_28;
    if ((!((!(xs_10))))) goto next_86;
    struct DumpTree_List* call_54 = listRev_14(acc_6);
    match_28 = call_54;
    goto end_match_85;
next_86:;
    if ((!(xs_10))) goto next_87;
    struct AExpr_ x_5 = xs_10->head;
    struct AExpr_List* xs_11 = xs_10->tail;
    struct DumpTree_ app_10 = f_1.fun(f_1.env, x_5);
    struct DumpTree_List* list_22 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_22->head = app_10;
    list_22->tail = acc_6;
    struct DumpTree_List* call_55 = go_70(f_1, list_22, xs_11);
    match_28 = call_55;
    goto end_match_85;
next_87:;
    exit(1);
end_match_85:;
    return match_28;
}

struct AVariant_DumpTree_Fun1 {
    struct DumpTree_(*fun)(void*, struct AVariant_);
    void* env;
};

struct DumpTree_List* go_69(struct AVariant_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct AVariant_List* xs_10) {
    struct DumpTree_List* match_29;
    if ((!((!(xs_10))))) goto next_89;
    struct DumpTree_List* call_56 = listRev_14(acc_6);
    match_29 = call_56;
    goto end_match_88;
next_89:;
    if ((!(xs_10))) goto next_90;
    struct AVariant_ x_5 = xs_10->head;
    struct AVariant_List* xs_11 = xs_10->tail;
    struct DumpTree_ app_11 = f_1.fun(f_1.env, x_5);
    struct DumpTree_List* list_23 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_23->head = app_11;
    list_23->tail = acc_6;
    struct DumpTree_List* call_57 = go_69(f_1, list_23, xs_11);
    match_29 = call_57;
    goto end_match_88;
next_90:;
    exit(1);
end_match_88:;
    return match_29;
}

struct HExpr_DumpTree_Fun1 {
    struct DumpTree_(*fun)(void*, struct HExpr_);
    void* env;
};

struct DumpTree_List* go_68(struct HExpr_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct HExpr_List* xs_10) {
    struct DumpTree_List* match_30;
    if ((!((!(xs_10))))) goto next_92;
    struct DumpTree_List* call_58 = listRev_14(acc_6);
    match_30 = call_58;
    goto end_match_91;
next_92:;
    if ((!(xs_10))) goto next_93;
    struct HExpr_ x_5 = xs_10->head;
    struct HExpr_List* xs_11 = xs_10->tail;
    struct DumpTree_ app_12 = f_1.fun(f_1.env, x_5);
    struct DumpTree_List* list_24 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_24->head = app_12;
    list_24->tail = acc_6;
    struct DumpTree_List* call_59 = go_68(f_1, list_24, xs_11);
    match_30 = call_59;
    goto end_match_91;
next_93:;
    exit(1);
end_match_91:;
    return match_30;
}

struct StringDumpTree_Fun1 {
    struct DumpTree_(*fun)(void*, struct String);
    void* env;
};

struct DumpTree_List* go_67(struct StringDumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct StringList* xs_10) {
    struct DumpTree_List* match_31;
    if ((!((!(xs_10))))) goto next_95;
    struct DumpTree_List* call_60 = listRev_14(acc_6);
    match_31 = call_60;
    goto end_match_94;
next_95:;
    if ((!(xs_10))) goto next_96;
    struct String x_5 = xs_10->head;
    struct StringList* xs_11 = xs_10->tail;
    struct DumpTree_ app_13 = f_1.fun(f_1.env, x_5);
    struct DumpTree_List* list_25 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_25->head = app_13;
    list_25->tail = acc_6;
    struct DumpTree_List* call_61 = go_67(f_1, list_25, xs_11);
    match_31 = call_61;
    goto end_match_94;
next_96:;
    exit(1);
end_match_94:;
    return match_31;
}

struct Ty_List* listMap_11(struct HExpr_Ty_Fun1 f_1, struct HExpr_List* xs_9) {
    struct Ty_List* call_62 = go_77(f_1, NULL, xs_9);
    return call_62;
}

struct HPat_HExpr_HExpr_Tuple3List* listMap_10(struct HPat_HExpr_HExpr_Tuple3HPat_HExpr_HExpr_Tuple3Fun1 f_1, struct HPat_HExpr_HExpr_Tuple3List* xs_9) {
    struct HPat_HExpr_HExpr_Tuple3List* call_63 = go_76(f_1, NULL, xs_9);
    return call_63;
}

struct HExpr_List* listMap_9(struct HExpr_HExpr_Fun1 f_1, struct HExpr_List* xs_9) {
    struct HExpr_List* call_64 = go_75(f_1, NULL, xs_9);
    return call_64;
}

struct HPat_List* listMap_8(struct HPat_HPat_Fun1 f_1, struct HPat_List* xs_9) {
    struct HPat_List* call_65 = go_74(f_1, NULL, xs_9);
    return call_65;
}

struct DumpTree_List* listMap_7(struct ATy_DumpTree_Fun1 f_1, struct ATy_List* xs_9) {
    struct DumpTree_List* call_66 = go_73(f_1, NULL, xs_9);
    return call_66;
}

struct DumpTree_List* listMap_6(struct AArm_DumpTree_Fun1 f_1, struct AArm_List* xs_9) {
    struct DumpTree_List* call_67 = go_72(f_1, NULL, xs_9);
    return call_67;
}

struct DumpTree_List* listMap_5(struct APat_DumpTree_Fun1 f_1, struct APat_List* xs_9) {
    struct DumpTree_List* call_68 = go_71(f_1, NULL, xs_9);
    return call_68;
}

struct DumpTree_List* listMap_4(struct AExpr_DumpTree_Fun1 f_1, struct AExpr_List* xs_9) {
    struct DumpTree_List* call_69 = go_70(f_1, NULL, xs_9);
    return call_69;
}

struct DumpTree_List* listMap_3(struct AVariant_DumpTree_Fun1 f_1, struct AVariant_List* xs_9) {
    struct DumpTree_List* call_70 = go_69(f_1, NULL, xs_9);
    return call_70;
}

struct DumpTree_List* listMap_2(struct HExpr_DumpTree_Fun1 f_1, struct HExpr_List* xs_9) {
    struct DumpTree_List* call_71 = go_68(f_1, NULL, xs_9);
    return call_71;
}

struct DumpTree_List* listMap_1(struct StringDumpTree_Fun1 f_1, struct StringList* xs_9) {
    struct DumpTree_List* call_72 = go_67(f_1, NULL, xs_9);
    return call_72;
}

struct StringListStringListFun1 {
    struct StringList*(*fun)(void*, struct StringList*);
    void* env;
};

struct StringList* go_66(struct StringListStringListFun1 f_3, struct StringList* acc_10, struct StringListList* xs_19) {
    struct StringList* match_32;
    if ((!((!(xs_19))))) goto next_98;
    struct StringList* call_73 = listRev_3(acc_10);
    match_32 = call_73;
    goto end_match_97;
next_98:;
    if ((!(xs_19))) goto next_99;
    struct StringList* x_8 = xs_19->head;
    struct StringListList* xs_20 = xs_19->tail;
    struct StringList* match_33;
    struct StringList* app_14 = f_3.fun(f_3.env, x_8);
    if ((!(app_14))) goto next_101;
    struct String y_2 = app_14->head;
    if ((!((!(app_14->tail))))) goto next_101;
    struct StringList* list_26 = (struct StringList*)malloc(sizeof(struct StringList));
    list_26->head = y_2;
    list_26->tail = acc_10;
    match_33 = list_26;
    goto end_match_100;
next_101:;
    if ((!((!(app_14))))) goto next_102;
    match_33 = acc_10;
    goto end_match_100;
next_102:;
    exit(1);
end_match_100:;
    struct StringList* acc_11 = match_33;
    struct StringList* call_74 = go_66(f_3, acc_11, xs_20);
    match_32 = call_74;
    goto end_match_97;
next_99:;
    exit(1);
end_match_97:;
    return match_32;
}

struct StringList* listChoose_1(struct StringListStringListFun1 f_3, struct StringListList* xs_18) {
    struct StringList* call_75 = go_66(f_3, NULL, xs_18);
    return call_75;
}

struct StringListList* gogo_1(struct StringListList* acc_12, struct StringListList* ys_) {
    struct StringListList* match_34;
    if ((!((!(ys_))))) goto next_104;
    match_34 = acc_12;
    goto end_match_103;
next_104:;
    if ((!(ys_))) goto next_105;
    struct StringList* y_3 = ys_->head;
    struct StringListList* ys_1 = ys_->tail;
    struct StringListList* list_27 = (struct StringListList*)malloc(sizeof(struct StringListList));
    list_27->head = y_3;
    list_27->tail = acc_12;
    struct StringListList* call_76 = gogo_1(list_27, ys_1);
    match_34 = call_76;
    goto end_match_103;
next_105:;
    exit(1);
end_match_103:;
    return match_34;
}

struct HExpr_StringListListFun1 {
    struct StringListList*(*fun)(void*, struct HExpr_);
    void* env;
};

struct StringListList* go_65(struct HExpr_StringListListFun1 f_4, struct StringListList* acc_13, struct HExpr_List* xs_22) {
    struct StringListList* match_35;
    if ((!((!(xs_22))))) goto next_107;
    struct StringListList* call_77 = listRev_13(acc_13);
    match_35 = call_77;
    goto end_match_106;
next_107:;
    if ((!(xs_22))) goto next_108;
    struct HExpr_ x_9 = xs_22->head;
    struct HExpr_List* xs_23 = xs_22->tail;
    struct StringListList* app_15 = f_4.fun(f_4.env, x_9);
    struct StringListList* call_78 = gogo_1(acc_13, app_15);
    struct StringListList* acc_14 = call_78;
    struct StringListList* call_79 = go_65(f_4, acc_14, xs_23);
    match_35 = call_79;
    goto end_match_106;
next_108:;
    exit(1);
end_match_106:;
    return match_35;
}

struct StringListList* listCollect_1(struct HExpr_StringListListFun1 f_4, struct HExpr_List* xs_21) {
    struct StringListList* call_80 = go_65(f_4, NULL, xs_21);
    return call_80;
}

struct StringHExpr_Tuple2 {
    struct String t0;
    struct HExpr_ t1;
};

struct StringHExpr_Tuple2List {
    struct StringHExpr_Tuple2 head;
    struct StringHExpr_Tuple2List* tail;
};

struct StringStringIntFun2 {
    int(*fun)(void*, struct String, struct String);
    void* env;
};

struct StringHExpr_Tuple2ListStringStringIntFun2Tuple2 {
    struct StringHExpr_Tuple2List* t0;
    struct StringStringIntFun2 t1;
};

struct HExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4 {
    struct HExpr_List* t0;
    struct StringHExpr_Tuple2ListStringStringIntFun2Tuple2 t1;
    struct NameCtx_ t2;
    struct StringIntIntTuple2Tuple2ListList* t3;
};

struct HExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4StringHExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4Fun2 {
    struct HExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4(*fun)(void*, struct HExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4, struct String);
    void* env;
};

struct HExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4 go_64(struct HExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4StringHExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4Fun2 folder_, struct HExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4 state_1, struct StringList* xs_31) {
    struct HExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4 match_36;
    if ((!((!(xs_31))))) goto next_110;
    match_36 = state_1;
    goto end_match_109;
next_110:;
    if ((!(xs_31))) goto next_111;
    struct String x_12 = xs_31->head;
    struct StringList* xs_32 = xs_31->tail;
    struct HExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4 app_16 = folder_.fun(folder_.env, state_1, x_12);
    struct HExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4 call_81 = go_64(folder_, app_16, xs_32);
    match_36 = call_81;
    goto end_match_109;
next_111:;
    exit(1);
end_match_109:;
    return match_36;
}

struct HExpr_HExpr_HExpr_Fun2 {
    struct HExpr_(*fun)(void*, struct HExpr_, struct HExpr_);
    void* env;
};

struct HExpr_ go_89(struct HExpr_HExpr_HExpr_Fun2 folder_, struct HExpr_ state_1, struct HExpr_List* xs_31) {
    struct HExpr_ match_37;
    if ((!((!(xs_31))))) goto next_113;
    match_37 = state_1;
    goto end_match_112;
next_113:;
    if ((!(xs_31))) goto next_114;
    struct HExpr_ x_12 = xs_31->head;
    struct HExpr_List* xs_32 = xs_31->tail;
    struct HExpr_ app_17 = folder_.fun(folder_.env, state_1, x_12);
    struct HExpr_ call_82 = go_89(folder_, app_17, xs_32);
    match_37 = call_82;
    goto end_match_112;
next_114:;
    exit(1);
end_match_112:;
    return match_37;
}

struct HExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4 listFold_1(struct HExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4StringHExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4Fun2 folder_, struct HExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4 state_, struct StringList* xs_30) {
    struct HExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4 call_83 = go_64(folder_, state_, xs_30);
    return call_83;
}

struct HExpr_ listFold_2(struct HExpr_HExpr_HExpr_Fun2 folder_, struct HExpr_ state_, struct HExpr_List* xs_30) {
    struct HExpr_ call_84 = go_89(folder_, state_, xs_30);
    return call_84;
}

struct HExpr_ listReduce_1(struct HExpr_HExpr_HExpr_Fun2 reducer_, struct HExpr_List* xs_33) {
    struct HExpr_ match_38;
    if ((!((!(xs_33))))) goto next_116;
    struct HExpr_ call_85 = failwith_4((struct String){.str = "listReduce: empty", .len = 17});
    match_38 = call_85;
    goto end_match_115;
next_116:;
    if ((!(xs_33))) goto next_117;
    struct HExpr_ x_13 = xs_33->head;
    struct HExpr_List* xs_34 = xs_33->tail;
    struct HExpr_ call_86 = listFold_2(reducer_, x_13, xs_34);
    match_38 = call_86;
    goto end_match_115;
next_117:;
    exit(1);
end_match_115:;
    return match_38;
}

struct Ty_NameCtx_Tuple2 {
    struct Ty_ t0;
    struct NameCtx_ t1;
};

struct ATy_NameCtx_Tuple2Ty_NameCtx_Tuple2Fun1 {
    struct Ty_NameCtx_Tuple2(*fun)(void*, struct ATy_NameCtx_Tuple2);
    void* env;
};

struct ATy_ListNameCtx_Tuple2 {
    struct ATy_List* t0;
    struct NameCtx_ t1;
};

struct Ty_ListNameCtx_Tuple2 {
    struct Ty_List* t0;
    struct NameCtx_ t1;
};

struct ATy_NameCtx_Tuple2 {
    struct ATy_ t0;
    struct NameCtx_ t1;
};

struct Ty_ListNameCtx_Tuple2 go_63(struct ATy_NameCtx_Tuple2Ty_NameCtx_Tuple2Fun1 f_5, struct Ty_List* acc_17, struct ATy_ListNameCtx_Tuple2 arg_119) {
    struct ATy_List* xs_54 = arg_119.t0;
    struct NameCtx_ ctx_1 = arg_119.t1;
    struct Ty_ListNameCtx_Tuple2 match_39;
    if ((!((!(xs_54))))) goto next_119;
    struct Ty_List* call_87 = listRev_12(acc_17);
    struct Ty_ListNameCtx_Tuple2 tuple_;
    tuple_.t0 = call_87;
    tuple_.t1 = ctx_1;
    match_39 = tuple_;
    goto end_match_118;
next_119:;
    if ((!(xs_54))) goto next_120;
    struct ATy_ x_18 = xs_54->head;
    struct ATy_List* xs_55 = xs_54->tail;
    struct ATy_NameCtx_Tuple2 tuple_1;
    tuple_1.t0 = x_18;
    tuple_1.t1 = ctx_1;
    struct Ty_NameCtx_Tuple2 app_18 = f_5.fun(f_5.env, tuple_1);
    struct Ty_ y_5 = app_18.t0;
    struct NameCtx_ ctx_2 = app_18.t1;
    struct Ty_List* list_28 = (struct Ty_List*)malloc(sizeof(struct Ty_List));
    list_28->head = y_5;
    list_28->tail = acc_17;
    struct ATy_ListNameCtx_Tuple2 tuple_2;
    tuple_2.t0 = xs_55;
    tuple_2.t1 = ctx_2;
    struct Ty_ListNameCtx_Tuple2 call_88 = go_63(f_5, list_28, tuple_2);
    match_39 = call_88;
    goto end_match_118;
next_120:;
    exit(1);
end_match_118:;
    return match_39;
}

struct HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2 {
    struct HPat_HExpr_HExpr_Tuple3 t0;
    struct NameCtx_ t1;
};

struct AArm_NameCtx_Tuple2HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2Fun1 {
    struct HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2(*fun)(void*, struct AArm_NameCtx_Tuple2);
    void* env;
};

struct AArm_ListNameCtx_Tuple2 {
    struct AArm_List* t0;
    struct NameCtx_ t1;
};

struct HPat_HExpr_HExpr_Tuple3ListNameCtx_Tuple2 {
    struct HPat_HExpr_HExpr_Tuple3List* t0;
    struct NameCtx_ t1;
};

struct AArm_NameCtx_Tuple2 {
    struct AArm_ t0;
    struct NameCtx_ t1;
};

struct HPat_HExpr_HExpr_Tuple3ListNameCtx_Tuple2 go_62(struct AArm_NameCtx_Tuple2HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2Fun1 f_5, struct HPat_HExpr_HExpr_Tuple3List* acc_17, struct AArm_ListNameCtx_Tuple2 arg_120) {
    struct AArm_List* xs_54 = arg_120.t0;
    struct NameCtx_ ctx_1 = arg_120.t1;
    struct HPat_HExpr_HExpr_Tuple3ListNameCtx_Tuple2 match_40;
    if ((!((!(xs_54))))) goto next_122;
    struct HPat_HExpr_HExpr_Tuple3List* call_89 = listRev_11(acc_17);
    struct HPat_HExpr_HExpr_Tuple3ListNameCtx_Tuple2 tuple_3;
    tuple_3.t0 = call_89;
    tuple_3.t1 = ctx_1;
    match_40 = tuple_3;
    goto end_match_121;
next_122:;
    if ((!(xs_54))) goto next_123;
    struct AArm_ x_18 = xs_54->head;
    struct AArm_List* xs_55 = xs_54->tail;
    struct AArm_NameCtx_Tuple2 tuple_4;
    tuple_4.t0 = x_18;
    tuple_4.t1 = ctx_1;
    struct HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2 app_19 = f_5.fun(f_5.env, tuple_4);
    struct HPat_HExpr_HExpr_Tuple3 y_5 = app_19.t0;
    struct NameCtx_ ctx_2 = app_19.t1;
    struct HPat_HExpr_HExpr_Tuple3List* list_29 = (struct HPat_HExpr_HExpr_Tuple3List*)malloc(sizeof(struct HPat_HExpr_HExpr_Tuple3List));
    list_29->head = y_5;
    list_29->tail = acc_17;
    struct AArm_ListNameCtx_Tuple2 tuple_5;
    tuple_5.t0 = xs_55;
    tuple_5.t1 = ctx_2;
    struct HPat_HExpr_HExpr_Tuple3ListNameCtx_Tuple2 call_90 = go_62(f_5, list_29, tuple_5);
    match_40 = call_90;
    goto end_match_121;
next_123:;
    exit(1);
end_match_121:;
    return match_40;
}

struct HExpr_NameCtx_Tuple2 {
    struct HExpr_ t0;
    struct NameCtx_ t1;
};

struct AExpr_NameCtx_Tuple2HExpr_NameCtx_Tuple2Fun1 {
    struct HExpr_NameCtx_Tuple2(*fun)(void*, struct AExpr_NameCtx_Tuple2);
    void* env;
};

struct AExpr_ListNameCtx_Tuple2 {
    struct AExpr_List* t0;
    struct NameCtx_ t1;
};

struct HExpr_ListNameCtx_Tuple2 {
    struct HExpr_List* t0;
    struct NameCtx_ t1;
};

struct AExpr_NameCtx_Tuple2 {
    struct AExpr_ t0;
    struct NameCtx_ t1;
};

struct HExpr_ListNameCtx_Tuple2 go_61(struct AExpr_NameCtx_Tuple2HExpr_NameCtx_Tuple2Fun1 f_5, struct HExpr_List* acc_17, struct AExpr_ListNameCtx_Tuple2 arg_121) {
    struct AExpr_List* xs_54 = arg_121.t0;
    struct NameCtx_ ctx_1 = arg_121.t1;
    struct HExpr_ListNameCtx_Tuple2 match_41;
    if ((!((!(xs_54))))) goto next_125;
    struct HExpr_List* call_91 = listRev_1(acc_17);
    struct HExpr_ListNameCtx_Tuple2 tuple_6;
    tuple_6.t0 = call_91;
    tuple_6.t1 = ctx_1;
    match_41 = tuple_6;
    goto end_match_124;
next_125:;
    if ((!(xs_54))) goto next_126;
    struct AExpr_ x_18 = xs_54->head;
    struct AExpr_List* xs_55 = xs_54->tail;
    struct AExpr_NameCtx_Tuple2 tuple_7;
    tuple_7.t0 = x_18;
    tuple_7.t1 = ctx_1;
    struct HExpr_NameCtx_Tuple2 app_20 = f_5.fun(f_5.env, tuple_7);
    struct HExpr_ y_5 = app_20.t0;
    struct NameCtx_ ctx_2 = app_20.t1;
    struct HExpr_List* list_30 = (struct HExpr_List*)malloc(sizeof(struct HExpr_List));
    list_30->head = y_5;
    list_30->tail = acc_17;
    struct AExpr_ListNameCtx_Tuple2 tuple_8;
    tuple_8.t0 = xs_55;
    tuple_8.t1 = ctx_2;
    struct HExpr_ListNameCtx_Tuple2 call_92 = go_61(f_5, list_30, tuple_8);
    match_41 = call_92;
    goto end_match_124;
next_126:;
    exit(1);
end_match_124:;
    return match_41;
}

struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1 {
    struct HPat_NameCtx_Tuple2(*fun)(void*, struct APat_NameCtx_Tuple2);
    void* env;
};

struct APat_ListNameCtx_Tuple2 {
    struct APat_List* t0;
    struct NameCtx_ t1;
};

struct HPat_ListNameCtx_Tuple2 {
    struct HPat_List* t0;
    struct NameCtx_ t1;
};

struct APat_NameCtx_Tuple2 {
    struct APat_ t0;
    struct NameCtx_ t1;
};

struct HPat_ListNameCtx_Tuple2 go_60(struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1 f_5, struct HPat_List* acc_17, struct APat_ListNameCtx_Tuple2 arg_122) {
    struct APat_List* xs_54 = arg_122.t0;
    struct NameCtx_ ctx_1 = arg_122.t1;
    struct HPat_ListNameCtx_Tuple2 match_42;
    if ((!((!(xs_54))))) goto next_128;
    struct HPat_List* call_93 = listRev_10(acc_17);
    struct HPat_ListNameCtx_Tuple2 tuple_9;
    tuple_9.t0 = call_93;
    tuple_9.t1 = ctx_1;
    match_42 = tuple_9;
    goto end_match_127;
next_128:;
    if ((!(xs_54))) goto next_129;
    struct APat_ x_18 = xs_54->head;
    struct APat_List* xs_55 = xs_54->tail;
    struct APat_NameCtx_Tuple2 tuple_10;
    tuple_10.t0 = x_18;
    tuple_10.t1 = ctx_1;
    struct HPat_NameCtx_Tuple2 app_21 = f_5.fun(f_5.env, tuple_10);
    struct HPat_ y_5 = app_21.t0;
    struct NameCtx_ ctx_2 = app_21.t1;
    struct HPat_List* list_31 = (struct HPat_List*)malloc(sizeof(struct HPat_List));
    list_31->head = y_5;
    list_31->tail = acc_17;
    struct APat_ListNameCtx_Tuple2 tuple_11;
    tuple_11.t0 = xs_55;
    tuple_11.t1 = ctx_2;
    struct HPat_ListNameCtx_Tuple2 call_94 = go_60(f_5, list_31, tuple_11);
    match_42 = call_94;
    goto end_match_127;
next_129:;
    exit(1);
end_match_127:;
    return match_42;
}

struct StringIntBoolTy_Tuple4NameCtx_Tuple2 {
    struct StringIntBoolTy_Tuple4 t0;
    struct NameCtx_ t1;
};

struct AVariant_NameCtx_Tuple2StringIntBoolTy_Tuple4NameCtx_Tuple2Fun1 {
    struct StringIntBoolTy_Tuple4NameCtx_Tuple2(*fun)(void*, struct AVariant_NameCtx_Tuple2);
    void* env;
};

struct AVariant_ListNameCtx_Tuple2 {
    struct AVariant_List* t0;
    struct NameCtx_ t1;
};

struct StringIntBoolTy_Tuple4ListNameCtx_Tuple2 {
    struct StringIntBoolTy_Tuple4List* t0;
    struct NameCtx_ t1;
};

struct AVariant_NameCtx_Tuple2 {
    struct AVariant_ t0;
    struct NameCtx_ t1;
};

struct StringIntBoolTy_Tuple4ListNameCtx_Tuple2 go_59(struct AVariant_NameCtx_Tuple2StringIntBoolTy_Tuple4NameCtx_Tuple2Fun1 f_5, struct StringIntBoolTy_Tuple4List* acc_17, struct AVariant_ListNameCtx_Tuple2 arg_123) {
    struct AVariant_List* xs_54 = arg_123.t0;
    struct NameCtx_ ctx_1 = arg_123.t1;
    struct StringIntBoolTy_Tuple4ListNameCtx_Tuple2 match_43;
    if ((!((!(xs_54))))) goto next_131;
    struct StringIntBoolTy_Tuple4List* call_95 = listRev_9(acc_17);
    struct StringIntBoolTy_Tuple4ListNameCtx_Tuple2 tuple_12;
    tuple_12.t0 = call_95;
    tuple_12.t1 = ctx_1;
    match_43 = tuple_12;
    goto end_match_130;
next_131:;
    if ((!(xs_54))) goto next_132;
    struct AVariant_ x_18 = xs_54->head;
    struct AVariant_List* xs_55 = xs_54->tail;
    struct AVariant_NameCtx_Tuple2 tuple_13;
    tuple_13.t0 = x_18;
    tuple_13.t1 = ctx_1;
    struct StringIntBoolTy_Tuple4NameCtx_Tuple2 app_22 = f_5.fun(f_5.env, tuple_13);
    struct StringIntBoolTy_Tuple4 y_5 = app_22.t0;
    struct NameCtx_ ctx_2 = app_22.t1;
    struct StringIntBoolTy_Tuple4List* list_32 = (struct StringIntBoolTy_Tuple4List*)malloc(sizeof(struct StringIntBoolTy_Tuple4List));
    list_32->head = y_5;
    list_32->tail = acc_17;
    struct AVariant_ListNameCtx_Tuple2 tuple_14;
    tuple_14.t0 = xs_55;
    tuple_14.t1 = ctx_2;
    struct StringIntBoolTy_Tuple4ListNameCtx_Tuple2 call_96 = go_59(f_5, list_32, tuple_14);
    match_43 = call_96;
    goto end_match_130;
next_132:;
    exit(1);
end_match_130:;
    return match_43;
}

struct Ty_ListNameCtx_Tuple2 stMap_5(struct ATy_NameCtx_Tuple2Ty_NameCtx_Tuple2Fun1 f_5, struct ATy_ListNameCtx_Tuple2 arg_124) {
    struct ATy_List* xs_53 = arg_124.t0;
    struct NameCtx_ ctx_ = arg_124.t1;
    struct ATy_ListNameCtx_Tuple2 tuple_15;
    tuple_15.t0 = xs_53;
    tuple_15.t1 = ctx_;
    struct Ty_ListNameCtx_Tuple2 call_97 = go_63(f_5, NULL, tuple_15);
    return call_97;
}

struct HPat_HExpr_HExpr_Tuple3ListNameCtx_Tuple2 stMap_4(struct AArm_NameCtx_Tuple2HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2Fun1 f_5, struct AArm_ListNameCtx_Tuple2 arg_125) {
    struct AArm_List* xs_53 = arg_125.t0;
    struct NameCtx_ ctx_ = arg_125.t1;
    struct AArm_ListNameCtx_Tuple2 tuple_16;
    tuple_16.t0 = xs_53;
    tuple_16.t1 = ctx_;
    struct HPat_HExpr_HExpr_Tuple3ListNameCtx_Tuple2 call_98 = go_62(f_5, NULL, tuple_16);
    return call_98;
}

struct HExpr_ListNameCtx_Tuple2 stMap_3(struct AExpr_NameCtx_Tuple2HExpr_NameCtx_Tuple2Fun1 f_5, struct AExpr_ListNameCtx_Tuple2 arg_126) {
    struct AExpr_List* xs_53 = arg_126.t0;
    struct NameCtx_ ctx_ = arg_126.t1;
    struct AExpr_ListNameCtx_Tuple2 tuple_17;
    tuple_17.t0 = xs_53;
    tuple_17.t1 = ctx_;
    struct HExpr_ListNameCtx_Tuple2 call_99 = go_61(f_5, NULL, tuple_17);
    return call_99;
}

struct HPat_ListNameCtx_Tuple2 stMap_2(struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1 f_5, struct APat_ListNameCtx_Tuple2 arg_127) {
    struct APat_List* xs_53 = arg_127.t0;
    struct NameCtx_ ctx_ = arg_127.t1;
    struct APat_ListNameCtx_Tuple2 tuple_18;
    tuple_18.t0 = xs_53;
    tuple_18.t1 = ctx_;
    struct HPat_ListNameCtx_Tuple2 call_100 = go_60(f_5, NULL, tuple_18);
    return call_100;
}

struct StringIntBoolTy_Tuple4ListNameCtx_Tuple2 stMap_1(struct AVariant_NameCtx_Tuple2StringIntBoolTy_Tuple4NameCtx_Tuple2Fun1 f_5, struct AVariant_ListNameCtx_Tuple2 arg_128) {
    struct AVariant_List* xs_53 = arg_128.t0;
    struct NameCtx_ ctx_ = arg_128.t1;
    struct AVariant_ListNameCtx_Tuple2 tuple_19;
    tuple_19.t0 = xs_53;
    tuple_19.t1 = ctx_;
    struct StringIntBoolTy_Tuple4ListNameCtx_Tuple2 call_101 = go_59(f_5, NULL, tuple_19);
    return call_101;
}

struct IntIntIntFun2 {
    int(*fun)(void*, int, int);
    void* env;
};

struct IntStringTuple2 {
    int t0;
    struct String t1;
};

struct IntStringTuple2List {
    struct IntStringTuple2 head;
    struct IntStringTuple2List* tail;
};

struct IntStringTuple2ListIntIntIntFun2Tuple2 {
    struct IntStringTuple2List* t0;
    struct IntIntIntFun2 t1;
};

struct IntStringTuple2ListIntIntIntFun2Tuple2 mapEmpty_2(struct IntIntIntFun2 cmp_3) {
    struct IntStringTuple2ListIntIntIntFun2Tuple2 tuple_20;
    tuple_20.t0 = NULL;
    tuple_20.t1 = cmp_3;
    return tuple_20;
}

struct StringHExpr_Tuple2ListStringStringIntFun2Tuple2 mapEmpty_1(struct StringStringIntFun2 cmp_3) {
    struct StringHExpr_Tuple2ListStringStringIntFun2Tuple2 tuple_21;
    tuple_21.t0 = NULL;
    tuple_21.t1 = cmp_3;
    return tuple_21;
}

struct IntStringTuple2ListIntIntIntFun2Tuple2 mapAdd_2(int key_, struct String value_3, struct IntStringTuple2ListIntIntIntFun2Tuple2 arg_129) {
    struct IntStringTuple2List* assoc_ = arg_129.t0;
    struct IntIntIntFun2 cmp_4 = arg_129.t1;
    struct IntStringTuple2 tuple_23;
    tuple_23.t0 = key_;
    tuple_23.t1 = value_3;
    struct IntStringTuple2List* list_33 = (struct IntStringTuple2List*)malloc(sizeof(struct IntStringTuple2List));
    list_33->head = tuple_23;
    list_33->tail = assoc_;
    struct IntStringTuple2ListIntIntIntFun2Tuple2 tuple_22;
    tuple_22.t0 = list_33;
    tuple_22.t1 = cmp_4;
    return tuple_22;
}

struct StringHExpr_Tuple2ListStringStringIntFun2Tuple2 mapAdd_1(struct String key_, struct HExpr_ value_3, struct StringHExpr_Tuple2ListStringStringIntFun2Tuple2 arg_130) {
    struct StringHExpr_Tuple2List* assoc_ = arg_130.t0;
    struct StringStringIntFun2 cmp_4 = arg_130.t1;
    struct StringHExpr_Tuple2 tuple_25;
    tuple_25.t0 = key_;
    tuple_25.t1 = value_3;
    struct StringHExpr_Tuple2List* list_34 = (struct StringHExpr_Tuple2List*)malloc(sizeof(struct StringHExpr_Tuple2List));
    list_34->head = tuple_25;
    list_34->tail = assoc_;
    struct StringHExpr_Tuple2ListStringStringIntFun2Tuple2 tuple_24;
    tuple_24.t0 = list_34;
    tuple_24.t1 = cmp_4;
    return tuple_24;
}

struct StringList* go_88(struct IntIntIntFun2 cmp_6, int key_2, struct IntStringTuple2List* assoc_3) {
    struct StringList* match_44;
    if ((!((!(assoc_3))))) goto next_134;
    match_44 = NULL;
    goto end_match_133;
next_134:;
    if ((!(assoc_3))) goto next_135;
    int k_1 = assoc_3->head.t0;
    struct String v_ = assoc_3->head.t1;
    int app_23 = cmp_6.fun(cmp_6.env, k_1, key_2);
    if ((app_23 != 0)) goto next_135;
    struct StringList* some_ = (struct StringList*)malloc(sizeof(struct StringList));
    some_->head = v_;
    some_->tail = NULL;
    match_44 = some_;
    goto end_match_133;
next_135:;
    if ((!(assoc_3))) goto next_136;
    struct IntStringTuple2List* assoc_4 = assoc_3->tail;
    struct StringList* call_102 = go_88(cmp_6, key_2, assoc_4);
    match_44 = call_102;
    goto end_match_133;
next_136:;
    exit(1);
end_match_133:;
    return match_44;
}

struct HExpr_List* go_87(struct StringStringIntFun2 cmp_6, struct String key_2, struct StringHExpr_Tuple2List* assoc_3) {
    struct HExpr_List* match_45;
    if ((!((!(assoc_3))))) goto next_138;
    match_45 = NULL;
    goto end_match_137;
next_138:;
    if ((!(assoc_3))) goto next_139;
    struct String k_1 = assoc_3->head.t0;
    struct HExpr_ v_ = assoc_3->head.t1;
    int app_24 = cmp_6.fun(cmp_6.env, k_1, key_2);
    if ((app_24 != 0)) goto next_139;
    struct HExpr_List* some_1 = (struct HExpr_List*)malloc(sizeof(struct HExpr_List));
    some_1->head = v_;
    some_1->tail = NULL;
    match_45 = some_1;
    goto end_match_137;
next_139:;
    if ((!(assoc_3))) goto next_140;
    struct StringHExpr_Tuple2List* assoc_4 = assoc_3->tail;
    struct HExpr_List* call_103 = go_87(cmp_6, key_2, assoc_4);
    match_45 = call_103;
    goto end_match_137;
next_140:;
    exit(1);
end_match_137:;
    return match_45;
}

struct StringList* mapTryFind_2(int key_2, struct IntStringTuple2ListIntIntIntFun2Tuple2 arg_131) {
    struct IntStringTuple2List* assoc_2 = arg_131.t0;
    struct IntIntIntFun2 cmp_6 = arg_131.t1;
    struct StringList* call_104 = go_88(cmp_6, key_2, assoc_2);
    return call_104;
}

struct HExpr_List* mapTryFind_1(struct String key_2, struct StringHExpr_Tuple2ListStringStringIntFun2Tuple2 arg_132) {
    struct StringHExpr_Tuple2List* assoc_2 = arg_132.t0;
    struct StringStringIntFun2 cmp_6 = arg_132.t1;
    struct HExpr_List* call_105 = go_87(cmp_6, key_2, assoc_2);
    return call_105;
}

struct String mapFind_1(int key_3, struct IntStringTuple2ListIntIntIntFun2Tuple2 map_) {
    struct String match_46;
    struct StringList* call_106 = mapTryFind_2(key_3, map_);
    if ((!(call_106))) goto next_142;
    struct String value_4 = call_106->head;
    if ((!((!(call_106->tail))))) goto next_142;
    match_46 = value_4;
    goto end_match_141;
next_142:;
    if ((!((!(call_106))))) goto next_143;
    struct IntStringFun1 call_107 = failwithf_4((struct String){.str = "mapFind: missing key (%A)", .len = 25});
    struct String app_25 = call_107.fun(call_107.env, key_3);
    match_46 = app_25;
    goto end_match_141;
next_143:;
    exit(1);
end_match_141:;
    return match_46;
}

int mapContainsKey_1(struct String key_4, struct StringHExpr_Tuple2ListStringStringIntFun2Tuple2 map_1) {
    int match_47;
    struct HExpr_List* call_108 = mapTryFind_1(key_4, map_1);
    if ((!(call_108))) goto next_145;
    if ((!((!(call_108->tail))))) goto next_145;
    match_47 = 1;
    goto end_match_144;
next_145:;
    if ((!((!(call_108))))) goto next_146;
    match_47 = 0;
    goto end_match_144;
next_146:;
    exit(1);
end_match_144:;
    return match_47;
}

int intMin_(int x_19, int y_6) {
    int match_48;
    if ((y_6 >= x_19)) goto next_148;
    match_48 = y_6;
    goto end_match_147;
next_148:;
    if ((y_6 < x_19)) goto next_149;
    match_48 = x_19;
    goto end_match_147;
next_149:;
    exit(1);
end_match_147:;
    return match_48;
}

int intMax_(int x_20, int y_7) {
    int match_49;
    if ((x_20 >= y_7)) goto next_151;
    match_49 = y_7;
    goto end_match_150;
next_151:;
    if ((x_20 < y_7)) goto next_152;
    match_49 = x_20;
    goto end_match_150;
next_152:;
    exit(1);
end_match_150:;
    return match_49;
}

int intEq_(int x_21, int y_8) {
    return (x_21 == y_8);
}

int intCmp_(int x_22, int y_9) {
    int match_50;
    if ((y_9 >= x_22)) goto next_154;
    match_50 = 1;
    goto end_match_153;
next_154:;
    if ((y_9 < x_22)) goto next_155;
    int match_51;
    if ((y_9 != x_22)) goto next_157;
    match_51 = 0;
    goto end_match_156;
next_157:;
    if ((y_9 == x_22)) goto next_158;
    match_51 = (0 - 1);
    goto end_match_156;
next_158:;
    exit(1);
end_match_156:;
    match_50 = match_51;
    goto end_match_153;
next_155:;
    exit(1);
end_match_153:;
    return match_50;
}

struct String go_30(struct String acc_18, int len_2, int n_1) {
    struct String match_52;
    int match_53;
    if ((n_1 != 0)) goto next_161;
    match_53 = (0 >= len_2);
    goto end_match_160;
next_161:;
    if ((n_1 == 0)) goto next_162;
    match_53 = 0;
    goto end_match_160;
next_162:;
    exit(1);
end_match_160:;
    if ((!(match_53))) goto next_163;
    match_52 = acc_18;
    goto end_match_159;
next_163:;
    if (match_53) goto next_164;
    int d_4 = (n_1 % 16);
    struct String call_109 = strSlice_(d_4, (d_4 + 1), (struct String){.str = "0123456789abcdef", .len = 16});
    struct String s_3 = call_109;
    struct String call_110 = go_30(str_add(s_3, acc_18), (len_2 - 1), (n_1 / 16));
    match_52 = call_110;
    goto end_match_159;
next_164:;
    exit(1);
end_match_159:;
    return match_52;
}

struct String intToHexWithPadding_(int len_1, int value_5) {
    struct String match_54;
    if ((value_5 >= 0)) goto next_166;
    struct String call_111 = failwith_3((struct String){.str = "intToHexWithPadding: unimplemented negative", .len = 43});
    match_54 = call_111;
    goto end_match_165;
next_166:;
    if ((value_5 < 0)) goto next_167;
    milone_assert((len_1 >= 0), 380, 2);
    int call_112 = 0;
    struct String match_55;
    int match_56;
    if ((value_5 != 0)) goto next_170;
    match_56 = (len_1 == 0);
    goto end_match_169;
next_170:;
    if ((value_5 == 0)) goto next_171;
    match_56 = 0;
    goto end_match_169;
next_171:;
    exit(1);
end_match_169:;
    if ((!(match_56))) goto next_172;
    match_55 = (struct String){.str = "0", .len = 1};
    goto end_match_168;
next_172:;
    if (match_56) goto next_173;
    struct String call_113 = go_30((struct String){.str = "", .len = 0}, len_1, value_5);
    match_55 = call_113;
    goto end_match_168;
next_173:;
    exit(1);
end_match_168:;
    match_54 = match_55;
    goto end_match_165;
next_167:;
    exit(1);
end_match_165:;
    return match_54;
}

int hexDigitToInt_(char c_6) {
    int match_57;
    int match_58;
    if ((c_6 < '0')) goto next_176;
    match_58 = ('9' >= c_6);
    goto end_match_175;
next_176:;
    if ((c_6 >= '0')) goto next_177;
    match_58 = 0;
    goto end_match_175;
next_177:;
    exit(1);
end_match_175:;
    if ((!(match_58))) goto next_178;
    int call_114 = charSub_(c_6, '0');
    match_57 = call_114;
    goto end_match_174;
next_178:;
    if (match_58) goto next_179;
    int match_59;
    int match_60;
    if ((c_6 < 'A')) goto next_182;
    match_60 = ('F' >= c_6);
    goto end_match_181;
next_182:;
    if ((c_6 >= 'A')) goto next_183;
    match_60 = 0;
    goto end_match_181;
next_183:;
    exit(1);
end_match_181:;
    if ((!(match_60))) goto next_184;
    int call_115 = charSub_(c_6, 'A');
    match_59 = (call_115 + 10);
    goto end_match_180;
next_184:;
    if (match_60) goto next_185;
    int match_61;
    int match_62;
    if ((c_6 < 'a')) goto next_188;
    match_62 = ('f' >= c_6);
    goto end_match_187;
next_188:;
    if ((c_6 >= 'a')) goto next_189;
    match_62 = 0;
    goto end_match_187;
next_189:;
    exit(1);
end_match_187:;
    if ((!(match_62))) goto next_190;
    int call_116 = charSub_(c_6, 'a');
    match_61 = (call_116 + 10);
    goto end_match_186;
next_190:;
    if (match_62) goto next_191;
    milone_assert(0, 406, 6);
    int call_117 = 0;
    match_61 = 0;
    goto end_match_186;
next_191:;
    exit(1);
end_match_186:;
    match_59 = match_61;
    goto end_match_180;
next_185:;
    exit(1);
end_match_180:;
    match_57 = match_59;
    goto end_match_174;
next_179:;
    exit(1);
end_match_174:;
    return match_57;
}

int go_31(struct String s_4, int r_20, int acc_19, int i_51) {
    int match_63;
    if ((i_51 != r_20)) goto next_193;
    match_63 = acc_19;
    goto end_match_192;
next_193:;
    if ((i_51 == r_20)) goto next_194;
    int call_118 = hexDigitToInt_(s_4.str[i_51]);
    int d_5 = call_118;
    int call_119 = go_31(s_4, r_20, ((acc_19 * 16) + d_5), (i_51 + 1));
    match_63 = call_119;
    goto end_match_192;
next_194:;
    exit(1);
end_match_192:;
    return match_63;
}

int intFromHex_(int l_8, int r_20, struct String s_4) {
    int match_64;
    int match_65;
    if ((l_8 < 0)) goto next_197;
    match_65 = (l_8 < r_20);
    goto end_match_196;
next_197:;
    if ((l_8 >= 0)) goto next_198;
    match_65 = 0;
    goto end_match_196;
next_198:;
    exit(1);
end_match_196:;
    if ((!(match_65))) goto next_199;
    match_64 = (s_4.len >= r_20);
    goto end_match_195;
next_199:;
    if (match_65) goto next_200;
    match_64 = 0;
    goto end_match_195;
next_200:;
    exit(1);
end_match_195:;
    milone_assert(match_64, 396, 2);
    int call_120 = 0;
    int call_121 = go_31(s_4, r_20, 0, l_8);
    return call_121;
}

int charSub_(char x_23, char y_10) {
    int call_122 = ((int)x_23);
    int call_123 = ((int)y_10);
    return (call_122 - call_123);
}

int charIsControl_(char c_7) {
    int call_124 = ((int)c_7);
    int n_2 = call_124;
    int match_66;
    int match_67;
    if ((n_2 < 0)) goto next_203;
    match_67 = (n_2 < 32);
    goto end_match_202;
next_203:;
    if ((n_2 >= 0)) goto next_204;
    match_67 = 0;
    goto end_match_202;
next_204:;
    exit(1);
end_match_202:;
    if ((!(match_67))) goto next_205;
    match_66 = 1;
    goto end_match_201;
next_205:;
    if (match_67) goto next_206;
    match_66 = (n_2 == 127);
    goto end_match_201;
next_206:;
    exit(1);
end_match_201:;
    return match_66;
}

int charIsSpace_(char c_8) {
    int match_68;
    int match_69;
    int match_70;
    if ((c_8 != ' ')) goto next_210;
    match_70 = 1;
    goto end_match_209;
next_210:;
    if ((c_8 == ' ')) goto next_211;
    match_70 = (c_8 == '\t');
    goto end_match_209;
next_211:;
    exit(1);
end_match_209:;
    if ((!(match_70))) goto next_212;
    match_69 = 1;
    goto end_match_208;
next_212:;
    if (match_70) goto next_213;
    match_69 = (c_8 == '\r');
    goto end_match_208;
next_213:;
    exit(1);
end_match_208:;
    if ((!(match_69))) goto next_214;
    match_68 = 1;
    goto end_match_207;
next_214:;
    if (match_69) goto next_215;
    match_68 = (c_8 == '\n');
    goto end_match_207;
next_215:;
    exit(1);
end_match_207:;
    return match_68;
}

int charIsDigit_(char c_9) {
    int match_71;
    if ((c_9 < '0')) goto next_217;
    match_71 = ('9' >= c_9);
    goto end_match_216;
next_217:;
    if ((c_9 >= '0')) goto next_218;
    match_71 = 0;
    goto end_match_216;
next_218:;
    exit(1);
end_match_216:;
    return match_71;
}

int charIsAlpha_(char c_10) {
    int match_72;
    int match_73;
    if ((c_10 < 'A')) goto next_221;
    match_73 = ('Z' >= c_10);
    goto end_match_220;
next_221:;
    if ((c_10 >= 'A')) goto next_222;
    match_73 = 0;
    goto end_match_220;
next_222:;
    exit(1);
end_match_220:;
    if ((!(match_73))) goto next_223;
    match_72 = 1;
    goto end_match_219;
next_223:;
    if (match_73) goto next_224;
    int match_74;
    if ((c_10 < 'a')) goto next_226;
    match_74 = ('z' >= c_10);
    goto end_match_225;
next_226:;
    if ((c_10 >= 'a')) goto next_227;
    match_74 = 0;
    goto end_match_225;
next_227:;
    exit(1);
end_match_225:;
    match_72 = match_74;
    goto end_match_219;
next_224:;
    exit(1);
end_match_219:;
    return match_72;
}

int charNeedsEscaping_(char c_11) {
    int match_75;
    int match_76;
    int match_77;
    int call_125 = charIsControl_(c_11);
    if ((!(call_125))) goto next_231;
    match_77 = 1;
    goto end_match_230;
next_231:;
    if (call_125) goto next_232;
    match_77 = (c_11 == '\\');
    goto end_match_230;
next_232:;
    exit(1);
end_match_230:;
    if ((!(match_77))) goto next_233;
    match_76 = 1;
    goto end_match_229;
next_233:;
    if (match_77) goto next_234;
    match_76 = (c_11 == '\"');
    goto end_match_229;
next_234:;
    exit(1);
end_match_229:;
    if ((!(match_76))) goto next_235;
    match_75 = 1;
    goto end_match_228;
next_235:;
    if (match_76) goto next_236;
    match_75 = (c_11 == '\'');
    goto end_match_228;
next_236:;
    exit(1);
end_match_228:;
    return match_75;
}

struct String charEscape_(char c_12) {
    int call_126 = charNeedsEscaping_(c_12);
    milone_assert(call_126, 442, 2);
    int call_127 = 0;
    struct String match_78;
    if ((c_12 != '\0')) goto next_238;
    match_78 = (struct String){.str = "\\0", .len = 2};
    goto end_match_237;
next_238:;
    if ((c_12 != '\t')) goto next_239;
    match_78 = (struct String){.str = "\\t", .len = 2};
    goto end_match_237;
next_239:;
    if ((c_12 != '\n')) goto next_240;
    match_78 = (struct String){.str = "\\n", .len = 2};
    goto end_match_237;
next_240:;
    if ((c_12 != '\r')) goto next_241;
    match_78 = (struct String){.str = "\\r", .len = 2};
    goto end_match_237;
next_241:;
    if ((c_12 != '\'')) goto next_242;
    match_78 = (struct String){.str = "\\\'", .len = 2};
    goto end_match_237;
next_242:;
    if ((c_12 != '\"')) goto next_243;
    match_78 = (struct String){.str = "\\\"", .len = 2};
    goto end_match_237;
next_243:;
    if ((c_12 != '\\')) goto next_244;
    match_78 = (struct String){.str = "\\\\", .len = 2};
    goto end_match_237;
next_244:;
    char c_13 = c_12;
    int call_128 = ((int)c_13);
    struct String call_129 = intToHexWithPadding_(2, call_128);
    struct String h_ = call_129;
    match_78 = str_add((struct String){.str = "\\x", .len = 2}, h_);
    goto end_match_237;
next_245:;
end_match_237:;
    return match_78;
}

int strCmp_(struct String x_24, struct String y_11) {
    int match_79;
    if ((str_cmp(y_11, x_24) >= 0)) goto next_247;
    match_79 = 1;
    goto end_match_246;
next_247:;
    if ((str_cmp(y_11, x_24) < 0)) goto next_248;
    int match_80;
    if ((str_cmp(y_11, x_24) != 0)) goto next_250;
    match_80 = 0;
    goto end_match_249;
next_250:;
    if ((str_cmp(y_11, x_24) == 0)) goto next_251;
    match_80 = (0 - 1);
    goto end_match_249;
next_251:;
    exit(1);
end_match_249:;
    match_79 = match_80;
    goto end_match_246;
next_248:;
    exit(1);
end_match_246:;
    return match_79;
}

struct String strSlice_(int start_, int endIndex_1, struct String s_5) {
    int match_81;
    if ((endIndex_1 < start_)) goto next_253;
    match_81 = (s_5.len >= endIndex_1);
    goto end_match_252;
next_253:;
    if ((endIndex_1 >= start_)) goto next_254;
    match_81 = 0;
    goto end_match_252;
next_254:;
    exit(1);
end_match_252:;
    milone_assert(match_81, 484, 2);
    int call_130 = 0;
    struct String match_82;
    if ((start_ < endIndex_1)) goto next_256;
    match_82 = (struct String){.str = "", .len = 0};
    goto end_match_255;
next_256:;
    if ((start_ >= endIndex_1)) goto next_257;
    struct String call_131 = str_get_slice(start_, (endIndex_1 - 1), s_5);
    match_82 = call_131;
    goto end_match_255;
next_257:;
    exit(1);
end_match_255:;
    return match_82;
}

struct StringStringListTuple2 {
    struct String t0;
    struct StringList* t1;
};

struct StringStringListTuple2 go_32(struct StringList* xs_57, int xn_3) {
    struct StringStringListTuple2 match_83;
    if ((!((!(xs_57))))) goto next_259;
    milone_assert((xn_3 == 0), 498, 6);
    int call_132 = 0;
    struct StringStringListTuple2 tuple_26;
    tuple_26.t0 = (struct String){.str = "", .len = 0};
    tuple_26.t1 = NULL;
    match_83 = tuple_26;
    goto end_match_258;
next_259:;
    if ((!(xs_57))) goto next_260;
    struct String x_25 = xs_57->head;
    struct StringList* xs_58 = xs_57->tail;
    if ((xn_3 != 1)) goto next_260;
    struct StringStringListTuple2 tuple_27;
    tuple_27.t0 = x_25;
    tuple_27.t1 = xs_58;
    match_83 = tuple_27;
    goto end_match_258;
next_260:;
    if ((!(xs_57))) goto next_261;
    struct String x_26 = xs_57->head;
    if ((!(xs_57->tail))) goto next_261;
    struct String y_12 = xs_57->tail->head;
    struct StringList* xs_59 = xs_57->tail->tail;
    if ((xn_3 != 2)) goto next_261;
    struct StringStringListTuple2 tuple_28;
    tuple_28.t0 = str_add(x_26, y_12);
    tuple_28.t1 = xs_59;
    match_83 = tuple_28;
    goto end_match_258;
next_261:;
    struct StringList* xs_60 = xs_57;
    int m_1 = (xn_3 / 2);
    struct StringStringListTuple2 call_133 = go_32(xs_60, m_1);
    struct String l_9 = call_133.t0;
    struct StringList* xs_61 = call_133.t1;
    struct StringStringListTuple2 call_134 = go_32(xs_61, (xn_3 - m_1));
    struct String r_21 = call_134.t0;
    struct StringList* xs_62 = call_134.t1;
    struct StringStringListTuple2 tuple_29;
    tuple_29.t0 = str_add(l_9, r_21);
    tuple_29.t1 = xs_62;
    match_83 = tuple_29;
    goto end_match_258;
next_262:;
end_match_258:;
    return match_83;
}

struct String strConcat_(struct StringList* xs_56) {
    int call_135 = listLength_1(xs_56);
    int n_3 = call_135;
    struct StringStringListTuple2 call_136 = go_32(xs_56, n_3);
    struct String s_6 = call_136.t0;
    struct StringList* xs_63 = call_136.t1;
    int call_137 = listIsEmpty_4(xs_63);
    milone_assert(call_137, 511, 2);
    int call_138 = 0;
    return s_6;
}

int go_33(struct String str_2, int i_52) {
    int match_84;
    if ((i_52 >= str_2.len)) goto next_264;
    int match_85;
    int call_139 = charNeedsEscaping_(str_2.str[i_52]);
    if ((!(call_139))) goto next_267;
    match_85 = 1;
    goto end_match_266;
next_267:;
    if (call_139) goto next_268;
    int call_140 = go_33(str_2, (i_52 + 1));
    match_85 = call_140;
    goto end_match_266;
next_268:;
    exit(1);
end_match_266:;
    match_84 = match_85;
    goto end_match_263;
next_264:;
    if ((i_52 < str_2.len)) goto next_265;
    match_84 = 0;
    goto end_match_263;
next_265:;
    exit(1);
end_match_263:;
    return match_84;
}

int strNeedsEscaping_(struct String str_2) {
    int call_141 = go_33(str_2, 0);
    return call_141;
}

int raw_(struct String str_3, int i_54) {
    int match_86;
    int match_87;
    if ((i_54 != str_3.len)) goto next_271;
    match_87 = 1;
    goto end_match_270;
next_271:;
    if ((i_54 == str_3.len)) goto next_272;
    int call_142 = charNeedsEscaping_(str_3.str[i_54]);
    match_87 = call_142;
    goto end_match_270;
next_272:;
    exit(1);
end_match_270:;
    if ((!(match_87))) goto next_273;
    match_86 = i_54;
    goto end_match_269;
next_273:;
    if (match_87) goto next_274;
    int call_143 = raw_(str_3, (i_54 + 1));
    match_86 = call_143;
    goto end_match_269;
next_274:;
    exit(1);
end_match_269:;
    return match_86;
}

struct IntStringListTuple2 {
    int t0;
    struct StringList* t1;
};

struct StringList* go_34(struct String str_3, struct StringList* acc_20, int i_53) {
    int call_144 = raw_(str_3, i_53);
    int r_22 = call_144;
    struct String call_145 = strSlice_(i_53, r_22, str_3);
    struct StringList* list_35 = (struct StringList*)malloc(sizeof(struct StringList));
    list_35->head = call_145;
    list_35->tail = acc_20;
    struct IntStringListTuple2 tuple_30;
    tuple_30.t0 = r_22;
    tuple_30.t1 = list_35;
    int i_55 = tuple_30.t0;
    struct StringList* acc_21 = tuple_30.t1;
    struct StringList* match_88;
    if ((i_55 != str_3.len)) goto next_276;
    match_88 = acc_21;
    goto end_match_275;
next_276:;
    if ((i_55 == str_3.len)) goto next_277;
    struct String call_146 = charEscape_(str_3.str[i_55]);
    struct String t_11 = call_146;
    struct StringList* list_36 = (struct StringList*)malloc(sizeof(struct StringList));
    list_36->head = t_11;
    list_36->tail = acc_21;
    struct StringList* call_147 = go_34(str_3, list_36, (i_55 + 1));
    match_88 = call_147;
    goto end_match_275;
next_277:;
    exit(1);
end_match_275:;
    return match_88;
}

struct String strEscape_(struct String str_3) {
    struct String match_89;
    int call_148 = strNeedsEscaping_(str_3);
    if (call_148) goto next_279;
    match_89 = str_3;
    goto end_match_278;
next_279:;
    if ((!(call_148))) goto next_280;
    struct StringList* call_149 = go_34(str_3, NULL, 0);
    struct StringList* call_150 = listRev_3(call_149);
    struct String call_151 = strConcat_(call_150);
    match_89 = call_151;
    goto end_match_278;
next_280:;
    exit(1);
end_match_278:;
    return match_89;
}

int locX_(struct IntIntTuple2 arg_133) {
    int x_27 = arg_133.t1;
    return x_27;
}

int locY_(struct IntIntTuple2 arg_134) {
    int y_13 = arg_134.t0;
    return y_13;
}

int locIsSameRow_(struct IntIntTuple2 first_, struct IntIntTuple2 second_) {
    int call_152 = locY_(first_);
    int call_153 = locY_(second_);
    return (call_152 == call_153);
}

int locIsSameColumn_(struct IntIntTuple2 first_1, struct IntIntTuple2 second_1) {
    int call_154 = locX_(first_1);
    int call_155 = locX_(second_1);
    return (call_154 == call_155);
}

int locInside_(struct IntIntTuple2 firstLoc_, struct IntIntTuple2 secondLoc_) {
    int call_156 = locX_(secondLoc_);
    int call_157 = locX_(firstLoc_);
    return (call_156 >= call_157);
}

struct IntIntTuple2 locAddX_(int dx_, struct IntIntTuple2 arg_135) {
    int y_14 = arg_135.t0;
    int x_28 = arg_135.t1;
    struct IntIntTuple2 tuple_31;
    tuple_31.t0 = y_14;
    tuple_31.t1 = (x_28 + dx_);
    return tuple_31;
}

struct IntIntTuple2 locMax_(struct IntIntTuple2 arg_136, struct IntIntTuple2 arg_137) {
    int firstY_ = arg_136.t0;
    int firstX_ = arg_136.t1;
    int secondY_ = arg_137.t0;
    int secondX_ = arg_137.t1;
    int call_158 = intMax_(firstY_, secondY_);
    int call_159 = intMax_(firstX_, secondX_);
    struct IntIntTuple2 tuple_32;
    tuple_32.t0 = call_158;
    tuple_32.t1 = call_159;
    return tuple_32;
}

struct String locToString_(struct IntIntTuple2 arg_138) {
    int y_15 = arg_138.t0;
    int x_29 = arg_138.t1;
    struct String call_160 = str_of_int((y_15 + 1));
    struct String call_161 = str_of_int((x_29 + 1));
    return str_add(str_add(call_160, (struct String){.str = ":", .len = 1}), call_161);
}

int tokenIsExprOrPatFirst_(struct Token_ token_7) {
    int match_90;
    if ((token_7.tag != Bool_1)) goto next_283;
    goto match_body_282;
next_283:;
    if ((token_7.tag != Int_1)) goto next_284;
    goto match_body_282;
next_284:;
    if ((token_7.tag != Char_1)) goto next_285;
    goto match_body_282;
next_285:;
    if ((token_7.tag != Str_1)) goto next_286;
    goto match_body_282;
next_286:;
    if ((token_7.tag != Ident_)) goto next_287;
    goto match_body_282;
next_287:;
    if ((token_7.tag != ParenL_)) goto next_288;
    goto match_body_282;
next_288:;
    if ((token_7.tag != BracketL_)) goto next_289;
    goto match_body_282;
match_body_282:;
    match_90 = 1;
    goto end_match_281;
next_289:;
    match_90 = 0;
    goto end_match_281;
next_290:;
end_match_281:;
    return match_90;
}

int tokenIsExprFirst_(struct Token_ token_8) {
    int match_91;
    int call_162 = tokenIsExprOrPatFirst_(token_8);
    if ((!(call_162))) goto next_293;
    match_91 = 1;
    goto end_match_291;
next_293:;
    if ((token_8.tag != Minus_)) goto next_294;
    goto match_body_292;
next_294:;
    if ((token_8.tag != If_)) goto next_295;
    goto match_body_292;
next_295:;
    if ((token_8.tag != Match_)) goto next_296;
    goto match_body_292;
next_296:;
    if ((token_8.tag != Fun_)) goto next_297;
    goto match_body_292;
next_297:;
    if ((token_8.tag != Do_)) goto next_298;
    goto match_body_292;
next_298:;
    if ((token_8.tag != Let_)) goto next_299;
    goto match_body_292;
next_299:;
    if ((token_8.tag != Type_)) goto next_300;
    goto match_body_292;
next_300:;
    if ((token_8.tag != Open_)) goto next_301;
    goto match_body_292;
match_body_292:;
    match_91 = 1;
    goto end_match_291;
next_301:;
    match_91 = 0;
    goto end_match_291;
next_302:;
end_match_291:;
    return match_91;
}

int tokenIsArgFirst_(struct Token_ token_9) {
    int match_92;
    if ((token_9.tag != Minus_)) goto next_304;
    match_92 = 0;
    goto end_match_303;
next_304:;
    int call_163 = tokenIsExprFirst_(token_9);
    match_92 = call_163;
    goto end_match_303;
next_305:;
end_match_303:;
    return match_92;
}

int tokenIsPatFirst_(struct Token_ token_10) {
    int call_164 = tokenIsExprOrPatFirst_(token_10);
    return call_164;
}

int tokenIsAccessModifier_(struct Token_ token_11) {
    int match_93;
    if ((token_11.tag != Private_)) goto next_308;
    goto match_body_307;
next_308:;
    if ((token_11.tag != Internal_)) goto next_309;
    goto match_body_307;
next_309:;
    if ((token_11.tag != Public_)) goto next_310;
    goto match_body_307;
match_body_307:;
    match_93 = 1;
    goto end_match_306;
next_310:;
    match_93 = 0;
    goto end_match_306;
next_311:;
end_match_306:;
    return match_93;
}

enum OpLevel_Tag {
    Prefix_,
    Mul_,
    Add_,
    Cons_,
    Pipe_1,
    Cmp_,
    And_,
    Or_,
};

struct OpLevel_ {
    enum OpLevel_Tag tag;
};

struct OpLevel_ opLevelToNext_(struct OpLevel_ level_) {
    struct OpLevel_ match_94;
    if ((level_.tag != Or_)) goto next_313;
    match_94 = (struct OpLevel_){.tag = And_};
    goto end_match_312;
next_313:;
    if ((level_.tag != And_)) goto next_314;
    match_94 = (struct OpLevel_){.tag = Cmp_};
    goto end_match_312;
next_314:;
    if ((level_.tag != Cmp_)) goto next_315;
    match_94 = (struct OpLevel_){.tag = Pipe_1};
    goto end_match_312;
next_315:;
    if ((level_.tag != Pipe_1)) goto next_316;
    match_94 = (struct OpLevel_){.tag = Cons_};
    goto end_match_312;
next_316:;
    if ((level_.tag != Cons_)) goto next_317;
    match_94 = (struct OpLevel_){.tag = Add_};
    goto end_match_312;
next_317:;
    if ((level_.tag != Add_)) goto next_319;
    match_94 = (struct OpLevel_){.tag = Mul_};
    goto end_match_312;
next_319:;
    if ((level_.tag != Mul_)) goto next_320;
    goto match_body_318;
next_320:;
    if ((level_.tag != Prefix_)) goto next_321;
    goto match_body_318;
match_body_318:;
    match_94 = (struct OpLevel_){.tag = Prefix_};
    goto end_match_312;
next_321:;
end_match_312:;
    return match_94;
}

enum Lit_Tag {
    Bool_,
    Int_,
    Char_,
    Str_,
};

struct Lit_ {
    enum Lit_Tag tag;
    union {
        int* Bool_;
        int* Int_;
        char* Char_;
        struct String* Str_;
    };
};

struct Lit_IntIntTuple2Tuple2 {
    struct Lit_ t0;
    struct IntIntTuple2 t1;
};

struct APat_ apFalse_(struct Lit_ litFalse_, struct IntIntTuple2 loc_2) {
    struct Lit_IntIntTuple2Tuple2 tuple_33;
    tuple_33.t0 = litFalse_;
    tuple_33.t1 = loc_2;
    struct Lit_IntIntTuple2Tuple2* payload_ = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_))) = tuple_33;
    struct APat_ variant_ = (struct APat_){.tag = Lit_, .Lit_ = payload_};
    return variant_;
}

struct APat_ apTrue_(struct Lit_ litTrue_, struct IntIntTuple2 loc_3) {
    struct Lit_IntIntTuple2Tuple2 tuple_34;
    tuple_34.t0 = litTrue_;
    tuple_34.t1 = loc_3;
    struct Lit_IntIntTuple2Tuple2* payload_1 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_1))) = tuple_34;
    struct APat_ variant_1 = (struct APat_){.tag = Lit_, .Lit_ = payload_1};
    return variant_1;
}

struct AExpr_ListIntIntTuple2Tuple2 {
    struct AExpr_List* t0;
    struct IntIntTuple2 t1;
};

struct AExpr_ axUnit_(struct IntIntTuple2 loc_4) {
    struct AExpr_ListIntIntTuple2Tuple2 tuple_35;
    tuple_35.t0 = NULL;
    tuple_35.t1 = loc_4;
    struct AExpr_ListIntIntTuple2Tuple2* payload_2 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_2))) = tuple_35;
    struct AExpr_ variant_2 = (struct AExpr_){.tag = TupleLit_1, .TupleLit_1 = payload_2};
    return variant_2;
}

struct AExpr_ axFalse_(struct Lit_ litFalse_, struct IntIntTuple2 loc_5) {
    struct Lit_IntIntTuple2Tuple2 tuple_36;
    tuple_36.t0 = litFalse_;
    tuple_36.t1 = loc_5;
    struct Lit_IntIntTuple2Tuple2* payload_3 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_3))) = tuple_36;
    struct AExpr_ variant_3 = (struct AExpr_){.tag = Lit_1, .Lit_1 = payload_3};
    return variant_3;
}

struct AExpr_ axTrue_(struct Lit_ litTrue_, struct IntIntTuple2 loc_6) {
    struct Lit_IntIntTuple2Tuple2 tuple_37;
    tuple_37.t0 = litTrue_;
    tuple_37.t1 = loc_6;
    struct Lit_IntIntTuple2Tuple2* payload_4 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_4))) = tuple_37;
    struct AExpr_ variant_4 = (struct AExpr_){.tag = Lit_1, .Lit_1 = payload_4};
    return variant_4;
}

struct AExpr_ axNil_(struct IntIntTuple2 loc_7) {
    struct AExpr_ListIntIntTuple2Tuple2 tuple_38;
    tuple_38.t0 = NULL;
    tuple_38.t1 = loc_7;
    struct AExpr_ListIntIntTuple2Tuple2* payload_5 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_5))) = tuple_38;
    struct AExpr_ variant_5 = (struct AExpr_){.tag = ListLit_1, .ListLit_1 = payload_5};
    return variant_5;
}

enum Op_Tag {
    Mul_1,
    Div_,
    Mod_,
    Add_1,
    Sub_,
    Eq_1,
    Ne_,
    Lt_1,
    Le_,
    Gt_1,
    Ge_,
    Pipe_2,
    And_1,
    Or_1,
    App_,
    Cons_1,
};

struct Op_ {
    enum Op_Tag tag;
};

struct Op_AExpr_AExpr_IntIntTuple2Tuple4 {
    struct Op_ t0;
    struct AExpr_ t1;
    struct AExpr_ t2;
    struct IntIntTuple2 t3;
};

struct AExpr_ app_(struct IntIntTuple2 loc_8, struct AExpr_ x_30, struct AExpr_ f_8) {
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_39;
    tuple_39.t0 = (struct Op_){.tag = App_};
    tuple_39.t1 = f_8;
    tuple_39.t2 = x_30;
    tuple_39.t3 = loc_8;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_6 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_6))) = tuple_39;
    struct AExpr_ variant_6 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_6};
    return variant_6;
}

struct AExpr_ axApp3_(struct AExpr_ f_7, struct AExpr_ x1_, struct AExpr_ x2_, struct AExpr_ x3_, struct IntIntTuple2 loc_8) {
    struct AExpr_ call_165 = app_(loc_8, x1_, f_7);
    struct AExpr_ call_166 = app_(loc_8, x2_, call_165);
    struct AExpr_ call_167 = app_(loc_8, x3_, call_166);
    return call_167;
}

struct AExpr_ axNot_(struct Lit_ litFalse_, struct AExpr_ arg_, struct IntIntTuple2 loc_9) {
    struct AExpr_ call_168 = axFalse_(litFalse_, loc_9);
    struct AExpr_ falseExpr_ = call_168;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_40;
    tuple_40.t0 = (struct Op_){.tag = Eq_1};
    tuple_40.t1 = arg_;
    tuple_40.t2 = falseExpr_;
    tuple_40.t3 = loc_9;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_7 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_7))) = tuple_40;
    struct AExpr_ variant_7 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_7};
    return variant_7;
}

struct StringDumpTree_ListDumpTree_ListTuple3 {
    struct String t0;
    struct DumpTree_List* t1;
    struct DumpTree_List* t2;
};

struct DumpTree_ dumpTreeNew_(struct String text_43, struct DumpTree_List* children_) {
    struct StringDumpTree_ListDumpTree_ListTuple3 tuple_41;
    tuple_41.t0 = text_43;
    tuple_41.t1 = children_;
    tuple_41.t2 = NULL;
    struct StringDumpTree_ListDumpTree_ListTuple3* payload_8 = (struct StringDumpTree_ListDumpTree_ListTuple3*)malloc(sizeof(struct StringDumpTree_ListDumpTree_ListTuple3));
    (*(((struct StringDumpTree_ListDumpTree_ListTuple3*)payload_8))) = tuple_41;
    struct DumpTree_ variant_8 = (struct DumpTree_){.tag = DumpTree_, .DumpTree_ = payload_8};
    return variant_8;
}

struct DumpTree_ dumpTreeNewLeaf_(struct String text_44) {
    struct StringDumpTree_ListDumpTree_ListTuple3 tuple_42;
    tuple_42.t0 = text_44;
    tuple_42.t1 = NULL;
    tuple_42.t2 = NULL;
    struct StringDumpTree_ListDumpTree_ListTuple3* payload_9 = (struct StringDumpTree_ListDumpTree_ListTuple3*)malloc(sizeof(struct StringDumpTree_ListDumpTree_ListTuple3));
    (*(((struct StringDumpTree_ListDumpTree_ListTuple3*)payload_9))) = tuple_42;
    struct DumpTree_ variant_9 = (struct DumpTree_){.tag = DumpTree_, .DumpTree_ = payload_9};
    return variant_9;
}

struct DumpTree_ dumpTreeAttachNext_(struct DumpTree_ next_1, struct DumpTree_ tree_) {
    struct DumpTree_ match_95;
    struct String text_45 = (*(tree_.DumpTree_)).t0;
    struct DumpTree_List* children_1 = (*(tree_.DumpTree_)).t1;
    struct DumpTree_List* oldNext_ = (*(tree_.DumpTree_)).t2;
    int call_169 = listIsEmpty_3(children_1);
    milone_assert((!(call_169)), 719, 4);
    int call_170 = 0;
    int call_171 = listIsEmpty_3(oldNext_);
    milone_assert(call_171, 720, 4);
    int call_172 = 0;
    struct DumpTree_List* list_37 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_37->head = next_1;
    list_37->tail = NULL;
    struct StringDumpTree_ListDumpTree_ListTuple3 tuple_43;
    tuple_43.t0 = text_45;
    tuple_43.t1 = children_1;
    tuple_43.t2 = list_37;
    struct StringDumpTree_ListDumpTree_ListTuple3* payload_10 = (struct StringDumpTree_ListDumpTree_ListTuple3*)malloc(sizeof(struct StringDumpTree_ListDumpTree_ListTuple3));
    (*(((struct StringDumpTree_ListDumpTree_ListTuple3*)payload_10))) = tuple_43;
    struct DumpTree_ variant_10 = (struct DumpTree_){.tag = DumpTree_, .DumpTree_ = payload_10};
    match_95 = variant_10;
    goto end_match_322;
next_323:;
    exit(1);
end_match_322:;
    return match_95;
}

struct DumpTree_ dumpTreeFromError_(struct String msg_, struct IntIntTuple2 arg_139) {
    int y_16 = arg_139.t0;
    int x_31 = arg_139.t1;
    struct String call_173 = str_of_int((y_16 + 1));
    struct String y_17 = call_173;
    struct String call_174 = str_of_int((x_31 + 1));
    struct String x_32 = call_174;
    struct DumpTree_ call_175 = dumpTreeNewLeaf_(msg_);
    struct DumpTree_ call_176 = dumpTreeNewLeaf_(str_add(str_add(str_add(str_add((struct String){.str = "(", .len = 1}, y_17), (struct String){.str = ":", .len = 1}), x_32), (struct String){.str = ")", .len = 1}));
    struct DumpTree_List* list_39 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_39->head = call_176;
    list_39->tail = NULL;
    struct DumpTree_List* list_38 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_38->head = call_175;
    list_38->tail = list_39;
    struct DumpTree_ call_177 = dumpTreeNew_((struct String){.str = "ERROR", .len = 5}, list_38);
    return call_177;
}

struct StringList* goChildren_(struct String eol_1, struct DumpTree_List* children_2, struct StringList* acc_23) {
    struct StringList* match_96;
    if ((!((!(children_2))))) goto next_325;
    match_96 = acc_23;
    goto end_match_324;
next_325:;
    if ((!(children_2))) goto next_326;
    struct DumpTree_ child_ = children_2->head;
    struct DumpTree_List* children_3 = children_2->tail;
    struct StringList* call_178 = cons_1(eol_1, acc_23);
    struct StringList* call_179 = cons_1((struct String){.str = "- ", .len = 2}, call_178);
    struct StringList* call_180 = go_35(str_add(eol_1, (struct String){.str = "  ", .len = 2}), child_, call_179);
    struct StringList* call_181 = goChildren_(eol_1, children_3, call_180);
    match_96 = call_181;
    goto end_match_324;
next_326:;
    exit(1);
end_match_324:;
    return match_96;
}

struct StringList* goNext_(struct String eol_2, struct DumpTree_List* next_2, struct StringList* acc_24) {
    struct StringList* match_97;
    if ((!((!(next_2))))) goto next_328;
    match_97 = acc_24;
    goto end_match_327;
next_328:;
    if ((!(next_2))) goto next_329;
    struct DumpTree_ next_3 = next_2->head;
    if ((!((!(next_2->tail))))) goto next_329;
    struct StringList* call_182 = cons_1(eol_2, acc_24);
    struct StringList* call_183 = go_35(eol_2, next_3, call_182);
    match_97 = call_183;
    goto end_match_327;
next_329:;
    struct StringList* call_184 = failwith_2((struct String){.str = "NEVER: DumpTree.next never empty", .len = 32});
    match_97 = call_184;
    goto end_match_327;
next_330:;
end_match_327:;
    return match_97;
}

struct StringList* go_35(struct String eol_, struct DumpTree_ node_1, struct StringList* acc_22) {
    struct StringList* match_98;
    struct String text_46 = (*(node_1.DumpTree_)).t0;
    if ((!((!((*(node_1.DumpTree_)).t1))))) goto next_332;
    if ((!((!((*(node_1.DumpTree_)).t2))))) goto next_332;
    struct String call_185 = strEscape_(text_46);
    struct StringList* call_186 = cons_1(call_185, acc_22);
    match_98 = call_186;
    goto end_match_331;
next_332:;
    struct String text_47 = (*(node_1.DumpTree_)).t0;
    if ((!((*(node_1.DumpTree_)).t1))) goto next_333;
    struct String childText_ = (*((*(node_1.DumpTree_)).t1->head.DumpTree_)).t0;
    if ((!((!((*((*(node_1.DumpTree_)).t1->head.DumpTree_)).t1))))) goto next_333;
    if ((!((!((*((*(node_1.DumpTree_)).t1->head.DumpTree_)).t2))))) goto next_333;
    if ((!((!((*(node_1.DumpTree_)).t1->tail))))) goto next_333;
    struct DumpTree_List* next_4 = (*(node_1.DumpTree_)).t2;
    struct String call_187 = strEscape_(childText_);
    struct String call_188 = strEscape_(text_47);
    struct StringList* call_189 = cons_1(call_188, acc_22);
    struct StringList* call_190 = cons_1((struct String){.str = ": ", .len = 2}, call_189);
    struct StringList* call_191 = cons_1(call_187, call_190);
    struct StringList* call_192 = goNext_(eol_, next_4, call_191);
    match_98 = call_192;
    goto end_match_331;
next_333:;
    struct String text_48 = (*(node_1.DumpTree_)).t0;
    struct DumpTree_List* children_4 = (*(node_1.DumpTree_)).t1;
    struct DumpTree_List* next_5 = (*(node_1.DumpTree_)).t2;
    struct String call_193 = strEscape_(text_48);
    struct StringList* call_194 = cons_1(call_193, acc_22);
    struct StringList* call_195 = cons_1((struct String){.str = ":", .len = 1}, call_194);
    struct StringList* call_196 = goChildren_(eol_, children_4, call_195);
    struct StringList* call_197 = goNext_(eol_, next_5, call_196);
    match_98 = call_197;
    goto end_match_331;
next_334:;
    exit(1);
end_match_331:;
    return match_98;
}

struct String dumpTreeToString_(struct DumpTree_ node_) {
    struct String eol_3 = (struct String){.str = "\n", .len = 1};
    struct StringList* call_198 = go_35(eol_3, node_, NULL);
    struct StringList* call_199 = listRev_3(call_198);
    struct String call_200 = strConcat_(call_199);
    return call_200;
}

int fun_9(void* env_3, int arg_14, int arg_15) {
    int call_201 = intCmp_(arg_14, arg_15);
    return call_201;
}

struct IntStringTuple2ListIntIntIntFun2Tuple2IntTuple2 {
    struct IntStringTuple2ListIntIntIntFun2Tuple2 t0;
    int t1;
};

struct NameCtx_ nameCtxEmpty_(int arg_140) {
    void* box_ = (void*)malloc(sizeof(int));
    (*(((int*)box_))) = 0;
    void* env_45 = box_;
    struct IntIntIntFun2 fun_51 = (struct IntIntIntFun2){.fun = fun_9, .env = env_45};
    struct IntStringTuple2ListIntIntIntFun2Tuple2 call_202 = mapEmpty_2(fun_51);
    struct IntStringTuple2ListIntIntIntFun2Tuple2IntTuple2 tuple_44;
    tuple_44.t0 = call_202;
    tuple_44.t1 = 0;
    struct IntStringTuple2ListIntIntIntFun2Tuple2IntTuple2* payload_11 = (struct IntStringTuple2ListIntIntIntFun2Tuple2IntTuple2*)malloc(sizeof(struct IntStringTuple2ListIntIntIntFun2Tuple2IntTuple2));
    (*(((struct IntStringTuple2ListIntIntIntFun2Tuple2IntTuple2*)payload_11))) = tuple_44;
    struct NameCtx_ variant_11 = (struct NameCtx_){.tag = NameCtx_, .NameCtx_ = payload_11};
    return variant_11;
}

struct IntNameCtx_Tuple2 {
    int t0;
    struct NameCtx_ t1;
};

struct IntNameCtx_Tuple2 nameCtxAdd_(struct String ident_, struct NameCtx_ arg_141) {
    struct IntStringTuple2ListIntIntIntFun2Tuple2 map_4 = (*(arg_141.NameCtx_)).t0;
    int serial_ = (*(arg_141.NameCtx_)).t1;
    int serial_1 = (serial_ + 1);
    struct IntStringTuple2ListIntIntIntFun2Tuple2 call_203 = mapAdd_2(serial_1, ident_, map_4);
    struct IntStringTuple2ListIntIntIntFun2Tuple2 map_5 = call_203;
    struct IntStringTuple2ListIntIntIntFun2Tuple2IntTuple2 tuple_46;
    tuple_46.t0 = map_5;
    tuple_46.t1 = serial_1;
    struct IntStringTuple2ListIntIntIntFun2Tuple2IntTuple2* payload_12 = (struct IntStringTuple2ListIntIntIntFun2Tuple2IntTuple2*)malloc(sizeof(struct IntStringTuple2ListIntIntIntFun2Tuple2IntTuple2));
    (*(((struct IntStringTuple2ListIntIntIntFun2Tuple2IntTuple2*)payload_12))) = tuple_46;
    struct NameCtx_ variant_12 = (struct NameCtx_){.tag = NameCtx_, .NameCtx_ = payload_12};
    struct IntNameCtx_Tuple2 tuple_45;
    tuple_45.t0 = serial_1;
    tuple_45.t1 = variant_12;
    return tuple_45;
}

struct String nameCtxFind_(int serial_2, struct NameCtx_ arg_142) {
    struct IntStringTuple2ListIntIntIntFun2Tuple2 map_6 = (*(arg_142.NameCtx_)).t0;
    struct String call_204 = mapFind_1(serial_2, map_6);
    return call_204;
}

struct Ty_Ty_Fun1 {
    struct Ty_(*fun)(void*, struct Ty_);
    void* env;
};

enum Trait_Tag {
    Add_2,
    Eq_2,
    Cmp_1,
    Index_1,
    ToInt_,
    ToString_,
};

struct Trait_ {
    enum Trait_Tag tag;
    union {
        struct Ty_* Add_2;
        struct Ty_* Eq_2;
        struct Ty_* Cmp_1;
        struct Ty_Ty_Ty_Tuple3* Index_1;
        struct Ty_* ToInt_;
        struct Ty_* ToString_;
    };
};

struct Ty_Ty_Ty_Tuple3 {
    struct Ty_ t0;
    struct Ty_ t1;
    struct Ty_ t2;
};

struct Trait_ traitMapTys_(struct Ty_Ty_Fun1 f_9, struct Trait_ it_) {
    struct Trait_ match_99;
    if ((it_.tag != Add_2)) goto next_336;
    struct Ty_ ty_ = (*(it_.Add_2));
    struct Ty_ app_26 = f_9.fun(f_9.env, ty_);
    struct Ty_* payload_13 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_13))) = app_26;
    struct Trait_ variant_13 = (struct Trait_){.tag = Add_2, .Add_2 = payload_13};
    match_99 = variant_13;
    goto end_match_335;
next_336:;
    if ((it_.tag != Eq_2)) goto next_337;
    struct Ty_ ty_1 = (*(it_.Eq_2));
    struct Ty_ app_27 = f_9.fun(f_9.env, ty_1);
    struct Ty_* payload_14 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_14))) = app_27;
    struct Trait_ variant_14 = (struct Trait_){.tag = Eq_2, .Eq_2 = payload_14};
    match_99 = variant_14;
    goto end_match_335;
next_337:;
    if ((it_.tag != Cmp_1)) goto next_338;
    struct Ty_ ty_2 = (*(it_.Cmp_1));
    struct Ty_ app_28 = f_9.fun(f_9.env, ty_2);
    struct Ty_* payload_15 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_15))) = app_28;
    struct Trait_ variant_15 = (struct Trait_){.tag = Cmp_1, .Cmp_1 = payload_15};
    match_99 = variant_15;
    goto end_match_335;
next_338:;
    if ((it_.tag != Index_1)) goto next_339;
    struct Ty_ lTy_ = (*(it_.Index_1)).t0;
    struct Ty_ rTy_ = (*(it_.Index_1)).t1;
    struct Ty_ outputTy_ = (*(it_.Index_1)).t2;
    struct Ty_ app_29 = f_9.fun(f_9.env, lTy_);
    struct Ty_ app_30 = f_9.fun(f_9.env, rTy_);
    struct Ty_ app_31 = f_9.fun(f_9.env, outputTy_);
    struct Ty_Ty_Ty_Tuple3 tuple_47;
    tuple_47.t0 = app_29;
    tuple_47.t1 = app_30;
    tuple_47.t2 = app_31;
    struct Ty_Ty_Ty_Tuple3* payload_16 = (struct Ty_Ty_Ty_Tuple3*)malloc(sizeof(struct Ty_Ty_Ty_Tuple3));
    (*(((struct Ty_Ty_Ty_Tuple3*)payload_16))) = tuple_47;
    struct Trait_ variant_16 = (struct Trait_){.tag = Index_1, .Index_1 = payload_16};
    match_99 = variant_16;
    goto end_match_335;
next_339:;
    if ((it_.tag != ToInt_)) goto next_340;
    struct Ty_ ty_3 = (*(it_.ToInt_));
    struct Ty_ app_32 = f_9.fun(f_9.env, ty_3);
    struct Ty_* payload_17 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_17))) = app_32;
    struct Trait_ variant_17 = (struct Trait_){.tag = ToInt_, .ToInt_ = payload_17};
    match_99 = variant_17;
    goto end_match_335;
next_340:;
    if ((it_.tag != ToString_)) goto next_341;
    struct Ty_ ty_4 = (*(it_.ToString_));
    struct Ty_ app_33 = f_9.fun(f_9.env, ty_4);
    struct Ty_* payload_18 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_18))) = app_33;
    struct Trait_ variant_18 = (struct Trait_){.tag = ToString_, .ToString_ = payload_18};
    match_99 = variant_18;
    goto end_match_335;
next_341:;
    exit(1);
end_match_335:;
    return match_99;
}

enum TyCon_Tag {
    Bool_2,
    Int_2,
    Char_2,
    Str_2,
    Obj_,
    Fun_4,
    Tuple_1,
    List_,
    Ref_,
};

struct TyCon_ {
    enum TyCon_Tag tag;
    union {
        int* Ref_;
    };
};

struct TyCon_Ty_ListTuple2 {
    struct TyCon_ t0;
    struct Ty_List* t1;
};

struct Ty_ tyTuple_(struct Ty_List* tys_) {
    struct TyCon_Ty_ListTuple2 tuple_48;
    tuple_48.t0 = (struct TyCon_){.tag = Tuple_1};
    tuple_48.t1 = tys_;
    struct TyCon_Ty_ListTuple2* payload_19 = (struct TyCon_Ty_ListTuple2*)malloc(sizeof(struct TyCon_Ty_ListTuple2));
    (*(((struct TyCon_Ty_ListTuple2*)payload_19))) = tuple_48;
    struct Ty_ variant_19 = (struct Ty_){.tag = Con_, .Con_ = payload_19};
    return variant_19;
}

struct Ty_ tyList_(struct Ty_ ty_5) {
    struct Ty_List* list_40 = (struct Ty_List*)malloc(sizeof(struct Ty_List));
    list_40->head = ty_5;
    list_40->tail = NULL;
    struct TyCon_Ty_ListTuple2 tuple_49;
    tuple_49.t0 = (struct TyCon_){.tag = List_};
    tuple_49.t1 = list_40;
    struct TyCon_Ty_ListTuple2* payload_20 = (struct TyCon_Ty_ListTuple2*)malloc(sizeof(struct TyCon_Ty_ListTuple2));
    (*(((struct TyCon_Ty_ListTuple2*)payload_20))) = tuple_49;
    struct Ty_ variant_20 = (struct Ty_){.tag = Con_, .Con_ = payload_20};
    return variant_20;
}

struct Ty_ tyFun_(struct Ty_ sourceTy_, struct Ty_ targetTy_) {
    struct Ty_List* list_42 = (struct Ty_List*)malloc(sizeof(struct Ty_List));
    list_42->head = targetTy_;
    list_42->tail = NULL;
    struct Ty_List* list_41 = (struct Ty_List*)malloc(sizeof(struct Ty_List));
    list_41->head = sourceTy_;
    list_41->tail = list_42;
    struct TyCon_Ty_ListTuple2 tuple_50;
    tuple_50.t0 = (struct TyCon_){.tag = Fun_4};
    tuple_50.t1 = list_41;
    struct TyCon_Ty_ListTuple2* payload_21 = (struct TyCon_Ty_ListTuple2*)malloc(sizeof(struct TyCon_Ty_ListTuple2));
    (*(((struct TyCon_Ty_ListTuple2*)payload_21))) = tuple_50;
    struct Ty_ variant_21 = (struct Ty_){.tag = Con_, .Con_ = payload_21};
    return variant_21;
}

struct Ty_ tyRef_(int serial_3, struct Ty_List* tys_1) {
    int* payload_22 = (int*)malloc(sizeof(int));
    (*(((int*)payload_22))) = serial_3;
    struct TyCon_ variant_22 = (struct TyCon_){.tag = Ref_, .Ref_ = payload_22};
    struct TyCon_Ty_ListTuple2 tuple_51;
    tuple_51.t0 = variant_22;
    tuple_51.t1 = tys_1;
    struct TyCon_Ty_ListTuple2* payload_23 = (struct TyCon_Ty_ListTuple2*)malloc(sizeof(struct TyCon_Ty_ListTuple2));
    (*(((struct TyCon_Ty_ListTuple2*)payload_23))) = tuple_51;
    struct Ty_ variant_23 = (struct Ty_){.tag = Con_, .Con_ = payload_23};
    return variant_23;
}

struct StringTy_ListTuple2 {
    struct String t0;
    struct Ty_List* t1;
};

struct Ty_ tyPrimFromIdent_(struct Ty_ tyUnit_, struct Ty_ tyObj_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct String ident_1, struct Ty_List* tys_2, struct IntIntTuple2 loc_10) {
    struct Ty_ match_100;
    struct StringTy_ListTuple2 tuple_52;
    tuple_52.t0 = ident_1;
    tuple_52.t1 = tys_2;
    if ((str_cmp(tuple_52.t0, (struct String){.str = "unit", .len = 4}) != 0)) goto next_343;
    if ((!((!(tuple_52.t1))))) goto next_343;
    match_100 = tyUnit_;
    goto end_match_342;
next_343:;
    if ((str_cmp(tuple_52.t0, (struct String){.str = "bool", .len = 4}) != 0)) goto next_344;
    if ((!((!(tuple_52.t1))))) goto next_344;
    match_100 = tyBool_;
    goto end_match_342;
next_344:;
    if ((str_cmp(tuple_52.t0, (struct String){.str = "int", .len = 3}) != 0)) goto next_345;
    if ((!((!(tuple_52.t1))))) goto next_345;
    match_100 = tyInt_;
    goto end_match_342;
next_345:;
    if ((str_cmp(tuple_52.t0, (struct String){.str = "char", .len = 4}) != 0)) goto next_346;
    if ((!((!(tuple_52.t1))))) goto next_346;
    match_100 = tyChar_;
    goto end_match_342;
next_346:;
    if ((str_cmp(tuple_52.t0, (struct String){.str = "string", .len = 6}) != 0)) goto next_347;
    if ((!((!(tuple_52.t1))))) goto next_347;
    match_100 = tyStr_;
    goto end_match_342;
next_347:;
    if ((str_cmp(tuple_52.t0, (struct String){.str = "obj", .len = 3}) != 0)) goto next_348;
    if ((!((!(tuple_52.t1))))) goto next_348;
    match_100 = tyObj_;
    goto end_match_342;
next_348:;
    if ((str_cmp(tuple_52.t0, (struct String){.str = "list", .len = 4}) != 0)) goto next_349;
    if ((!(tuple_52.t1))) goto next_349;
    struct Ty_ itemTy_ = tuple_52.t1->head;
    if ((!((!(tuple_52.t1->tail))))) goto next_349;
    struct Ty_ call_205 = tyList_(itemTy_);
    match_100 = call_205;
    goto end_match_342;
next_349:;
    struct IntIntTuple2* payload_24 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_24))) = loc_10;
    struct Ty_ variant_24 = (struct Ty_){.tag = Error_1, .Error_1 = payload_24};
    match_100 = variant_24;
    goto end_match_342;
next_350:;
end_match_342:;
    return match_100;
}

struct IntIntIntTuple2Tuple2 {
    int t0;
    struct IntIntTuple2 t1;
};

int go_36(int tySerial_, struct Ty_ ty_7) {
    int match_101;
    if ((ty_7.tag != Error_1)) goto next_353;
    goto match_body_352;
next_353:;
    if ((ty_7.tag != Con_)) goto next_354;
    if ((!((!((*(ty_7.Con_)).t1))))) goto next_354;
    goto match_body_352;
match_body_352:;
    match_101 = 1;
    goto end_match_351;
next_354:;
    if ((ty_7.tag != Con_)) goto next_355;
    struct TyCon_ tyCon_ = (*(ty_7.Con_)).t0;
    if ((!((*(ty_7.Con_)).t1))) goto next_355;
    struct Ty_ ty_8 = (*(ty_7.Con_)).t1->head;
    struct Ty_List* tys_3 = (*(ty_7.Con_)).t1->tail;
    int match_102;
    int call_206 = go_36(tySerial_, ty_8);
    if ((!(call_206))) goto next_358;
    struct TyCon_Ty_ListTuple2 tuple_53;
    tuple_53.t0 = tyCon_;
    tuple_53.t1 = tys_3;
    struct TyCon_Ty_ListTuple2* payload_25 = (struct TyCon_Ty_ListTuple2*)malloc(sizeof(struct TyCon_Ty_ListTuple2));
    (*(((struct TyCon_Ty_ListTuple2*)payload_25))) = tuple_53;
    struct Ty_ variant_25 = (struct Ty_){.tag = Con_, .Con_ = payload_25};
    int call_207 = go_36(tySerial_, variant_25);
    match_102 = call_207;
    goto end_match_357;
next_358:;
    if (call_206) goto next_359;
    match_102 = 0;
    goto end_match_357;
next_359:;
    exit(1);
end_match_357:;
    match_101 = match_102;
    goto end_match_351;
next_355:;
    if ((ty_7.tag != Meta_)) goto next_356;
    int s_7 = (*(ty_7.Meta_)).t0;
    match_101 = (s_7 != tySerial_);
    goto end_match_351;
next_356:;
    exit(1);
end_match_351:;
    return match_101;
}

int tyIsFreeIn_(struct Ty_ ty_6, int tySerial_) {
    int call_208 = go_36(tySerial_, ty_6);
    return call_208;
}

int go_37(struct Ty_List* tys_4) {
    int match_103;
    if ((!((!(tys_4))))) goto next_361;
    match_103 = 1;
    goto end_match_360;
next_361:;
    if ((!(tys_4))) goto next_362;
    if ((tys_4->head.tag != Meta_)) goto next_362;
    match_103 = 0;
    goto end_match_360;
next_362:;
    if ((!(tys_4))) goto next_363;
    if ((tys_4->head.tag != Error_1)) goto next_363;
    struct Ty_List* tys_5 = tys_4->tail;
    int call_209 = go_37(tys_5);
    match_103 = call_209;
    goto end_match_360;
next_363:;
    if ((!(tys_4))) goto next_364;
    if ((tys_4->head.tag != Con_)) goto next_364;
    struct Ty_List* tys1_ = (*(tys_4->head.Con_)).t1;
    struct Ty_List* tys2_ = tys_4->tail;
    int match_104;
    int call_210 = go_37(tys1_);
    if ((!(call_210))) goto next_366;
    int call_211 = go_37(tys2_);
    match_104 = call_211;
    goto end_match_365;
next_366:;
    if (call_210) goto next_367;
    match_104 = 0;
    goto end_match_365;
next_367:;
    exit(1);
end_match_365:;
    match_103 = match_104;
    goto end_match_360;
next_364:;
    exit(1);
end_match_360:;
    return match_103;
}

int tyIsMonomorphic_(struct Ty_ ty_9) {
    struct Ty_List* list_43 = (struct Ty_List*)malloc(sizeof(struct Ty_List));
    list_43->head = ty_9;
    list_43->tail = NULL;
    int call_212 = go_37(list_43);
    return call_212;
}

enum TyDef_Tag {
    Meta_1,
    Union_2,
};

struct TyDef_ {
    enum TyDef_Tag tag;
    union {
        struct StringTy_IntIntTuple2Tuple3* Meta_1;
        struct StringIntListIntIntTuple2Tuple3* Union_2;
    };
};

struct StringTy_IntIntTuple2Tuple3 {
    struct String t0;
    struct Ty_ t1;
    struct IntIntTuple2 t2;
};

struct IntList {
    int head;
    struct IntList* tail;
};

struct StringIntListIntIntTuple2Tuple3 {
    struct String t0;
    struct IntList* t1;
    struct IntIntTuple2 t2;
};

struct String tyDefToIdent_(struct TyDef_ tyDef_) {
    struct String match_105;
    if ((tyDef_.tag != Meta_1)) goto next_369;
    struct String ident_2 = (*(tyDef_.Meta_1)).t0;
    match_105 = ident_2;
    goto end_match_368;
next_369:;
    if ((tyDef_.tag != Union_2)) goto next_370;
    struct String ident_3 = (*(tyDef_.Union_2)).t0;
    match_105 = ident_3;
    goto end_match_368;
next_370:;
    exit(1);
end_match_368:;
    return match_105;
}

enum VarDef_Tag {
    Var_,
    Fun_5,
    Variant_,
};

struct VarDef_ {
    enum VarDef_Tag tag;
    union {
        struct StringTy_IntIntTuple2Tuple3* Var_;
        struct StringIntTyScheme_IntIntTuple2Tuple4* Fun_5;
        struct StringIntBoolTy_Ty_IntIntTuple2Tuple6* Variant_;
    };
};

enum TyScheme_Tag {
    ForAll_,
};

struct TyScheme_ {
    enum TyScheme_Tag tag;
    union {
        struct IntListTy_Tuple2* ForAll_;
    };
};

struct StringIntTyScheme_IntIntTuple2Tuple4 {
    struct String t0;
    int t1;
    struct TyScheme_ t2;
    struct IntIntTuple2 t3;
};

struct StringIntBoolTy_Ty_IntIntTuple2Tuple6 {
    struct String t0;
    int t1;
    int t2;
    struct Ty_ t3;
    struct Ty_ t4;
    struct IntIntTuple2 t5;
};

struct String varDefToIdent_(struct VarDef_ varDef_) {
    struct String match_106;
    if ((varDef_.tag != Var_)) goto next_372;
    struct String ident_4 = (*(varDef_.Var_)).t0;
    match_106 = ident_4;
    goto end_match_371;
next_372:;
    if ((varDef_.tag != Fun_5)) goto next_373;
    struct String ident_5 = (*(varDef_.Fun_5)).t0;
    match_106 = ident_5;
    goto end_match_371;
next_373:;
    if ((varDef_.tag != Variant_)) goto next_374;
    struct String ident_6 = (*(varDef_.Variant_)).t0;
    match_106 = ident_6;
    goto end_match_371;
next_374:;
    exit(1);
end_match_371:;
    return match_106;
}

struct Ty_ litToTy_(struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Lit_ lit_) {
    struct Ty_ match_107;
    if ((lit_.tag != Bool_)) goto next_376;
    match_107 = tyBool_;
    goto end_match_375;
next_376:;
    if ((lit_.tag != Int_)) goto next_377;
    match_107 = tyInt_;
    goto end_match_375;
next_377:;
    if ((lit_.tag != Char_)) goto next_378;
    match_107 = tyChar_;
    goto end_match_375;
next_378:;
    if ((lit_.tag != Str_)) goto next_379;
    match_107 = tyStr_;
    goto end_match_375;
next_379:;
    exit(1);
end_match_375:;
    return match_107;
}

struct Ty_ meta_(struct IntIntTuple2 noLoc_, int id_) {
    struct IntIntIntTuple2Tuple2 tuple_54;
    tuple_54.t0 = id_;
    tuple_54.t1 = noLoc_;
    struct IntIntIntTuple2Tuple2* payload_26 = (struct IntIntIntTuple2Tuple2*)malloc(sizeof(struct IntIntIntTuple2Tuple2));
    (*(((struct IntIntIntTuple2Tuple2*)payload_26))) = tuple_54;
    struct Ty_ variant_26 = (struct Ty_){.tag = Meta_, .Meta_ = payload_26};
    return variant_26;
}

struct Trait_List {
    struct Trait_ head;
    struct Trait_List* tail;
};

struct Ty_Trait_ListTuple2 {
    struct Ty_ t0;
    struct Trait_List* t1;
};

enum TySpec_Tag {
    TySpec_,
};

struct TySpec_ {
    enum TySpec_Tag tag;
    union {
        struct Ty_Trait_ListTuple2* TySpec_;
    };
};

struct TySpec_ mono_(struct Ty_ ty_10) {
    struct Ty_Trait_ListTuple2 tuple_55;
    tuple_55.t0 = ty_10;
    tuple_55.t1 = NULL;
    struct Ty_Trait_ListTuple2* payload_27 = (struct Ty_Trait_ListTuple2*)malloc(sizeof(struct Ty_Trait_ListTuple2));
    (*(((struct Ty_Trait_ListTuple2*)payload_27))) = tuple_55;
    struct TySpec_ variant_27 = (struct TySpec_){.tag = TySpec_, .TySpec_ = payload_27};
    return variant_27;
}

struct TySpec_ poly_(struct Ty_ ty_11, struct Trait_List* traits_) {
    struct Ty_Trait_ListTuple2 tuple_56;
    tuple_56.t0 = ty_11;
    tuple_56.t1 = traits_;
    struct Ty_Trait_ListTuple2* payload_28 = (struct Ty_Trait_ListTuple2*)malloc(sizeof(struct Ty_Trait_ListTuple2));
    (*(((struct Ty_Trait_ListTuple2*)payload_28))) = tuple_56;
    struct TySpec_ variant_28 = (struct TySpec_){.tag = TySpec_, .TySpec_ = payload_28};
    return variant_28;
}

struct TySpec_ primToTySpec_(struct Ty_ tyUnit_, struct Ty_ tyObj_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct IntIntTuple2 noLoc_, struct HPrim_ prim_) {
    struct TySpec_ match_108;
    if ((prim_.tag != Add_3)) goto next_381;
    struct Ty_ call_213 = meta_(noLoc_, 1);
    struct Ty_ addTy_ = call_213;
    struct Ty_ call_214 = tyFun_(addTy_, addTy_);
    struct Ty_ call_215 = tyFun_(addTy_, call_214);
    struct Ty_* payload_29 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_29))) = addTy_;
    struct Trait_ variant_29 = (struct Trait_){.tag = Add_2, .Add_2 = payload_29};
    struct Trait_List* list_44 = (struct Trait_List*)malloc(sizeof(struct Trait_List));
    list_44->head = variant_29;
    list_44->tail = NULL;
    struct TySpec_ call_216 = poly_(call_215, list_44);
    match_108 = call_216;
    goto end_match_380;
next_381:;
    if ((prim_.tag != Sub_1)) goto next_382;
    struct Ty_ call_217 = tyFun_(tyInt_, tyInt_);
    struct Ty_ call_218 = tyFun_(tyInt_, call_217);
    struct TySpec_ call_219 = mono_(call_218);
    match_108 = call_219;
    goto end_match_380;
next_382:;
    if ((prim_.tag != Mul_2)) goto next_383;
    struct Ty_ call_220 = tyFun_(tyInt_, tyInt_);
    struct Ty_ call_221 = tyFun_(tyInt_, call_220);
    struct TySpec_ call_222 = mono_(call_221);
    match_108 = call_222;
    goto end_match_380;
next_383:;
    if ((prim_.tag != Div_1)) goto next_384;
    struct Ty_ call_223 = tyFun_(tyInt_, tyInt_);
    struct Ty_ call_224 = tyFun_(tyInt_, call_223);
    struct TySpec_ call_225 = mono_(call_224);
    match_108 = call_225;
    goto end_match_380;
next_384:;
    if ((prim_.tag != Mod_1)) goto next_385;
    struct Ty_ call_226 = tyFun_(tyInt_, tyInt_);
    struct Ty_ call_227 = tyFun_(tyInt_, call_226);
    struct TySpec_ call_228 = mono_(call_227);
    match_108 = call_228;
    goto end_match_380;
next_385:;
    if ((prim_.tag != Eq_3)) goto next_386;
    struct Ty_ call_229 = meta_(noLoc_, 1);
    struct Ty_ eqTy_ = call_229;
    struct Ty_ call_230 = tyFun_(eqTy_, tyBool_);
    struct Ty_ call_231 = tyFun_(eqTy_, call_230);
    struct Ty_* payload_30 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_30))) = eqTy_;
    struct Trait_ variant_30 = (struct Trait_){.tag = Eq_2, .Eq_2 = payload_30};
    struct Trait_List* list_45 = (struct Trait_List*)malloc(sizeof(struct Trait_List));
    list_45->head = variant_30;
    list_45->tail = NULL;
    struct TySpec_ call_232 = poly_(call_231, list_45);
    match_108 = call_232;
    goto end_match_380;
next_386:;
    if ((prim_.tag != Lt_2)) goto next_387;
    struct Ty_ call_233 = meta_(noLoc_, 1);
    struct Ty_ cmpTy_ = call_233;
    struct Ty_ call_234 = tyFun_(cmpTy_, tyBool_);
    struct Ty_ call_235 = tyFun_(cmpTy_, call_234);
    struct Ty_* payload_31 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_31))) = cmpTy_;
    struct Trait_ variant_31 = (struct Trait_){.tag = Cmp_1, .Cmp_1 = payload_31};
    struct Trait_List* list_46 = (struct Trait_List*)malloc(sizeof(struct Trait_List));
    list_46->head = variant_31;
    list_46->tail = NULL;
    struct TySpec_ call_236 = poly_(call_235, list_46);
    match_108 = call_236;
    goto end_match_380;
next_387:;
    if ((prim_.tag != Nil_1)) goto next_388;
    struct Ty_ call_237 = meta_(noLoc_, 1);
    struct Ty_ itemTy_1 = call_237;
    struct Ty_ call_238 = tyList_(itemTy_1);
    struct TySpec_ call_239 = poly_(call_238, NULL);
    match_108 = call_239;
    goto end_match_380;
next_388:;
    if ((prim_.tag != Cons_4)) goto next_389;
    struct Ty_ call_240 = meta_(noLoc_, 1);
    struct Ty_ itemTy_2 = call_240;
    struct Ty_ call_241 = tyList_(itemTy_2);
    struct Ty_ listTy_ = call_241;
    struct Ty_ call_242 = tyFun_(listTy_, listTy_);
    struct Ty_ call_243 = tyFun_(itemTy_2, call_242);
    struct TySpec_ call_244 = poly_(call_243, NULL);
    match_108 = call_244;
    goto end_match_380;
next_389:;
    if ((prim_.tag != Index_2)) goto next_390;
    struct Ty_ call_245 = meta_(noLoc_, 1);
    struct Ty_ lTy_1 = call_245;
    struct Ty_ call_246 = meta_(noLoc_, 2);
    struct Ty_ rTy_1 = call_246;
    struct Ty_ call_247 = meta_(noLoc_, 3);
    struct Ty_ resultTy_ = call_247;
    struct Ty_ call_248 = tyFun_(rTy_1, resultTy_);
    struct Ty_ call_249 = tyFun_(lTy_1, call_248);
    struct Ty_Ty_Ty_Tuple3 tuple_57;
    tuple_57.t0 = lTy_1;
    tuple_57.t1 = rTy_1;
    tuple_57.t2 = resultTy_;
    struct Ty_Ty_Ty_Tuple3* payload_32 = (struct Ty_Ty_Ty_Tuple3*)malloc(sizeof(struct Ty_Ty_Ty_Tuple3));
    (*(((struct Ty_Ty_Ty_Tuple3*)payload_32))) = tuple_57;
    struct Trait_ variant_32 = (struct Trait_){.tag = Index_1, .Index_1 = payload_32};
    struct Trait_List* list_47 = (struct Trait_List*)malloc(sizeof(struct Trait_List));
    list_47->head = variant_32;
    list_47->tail = NULL;
    struct TySpec_ call_250 = poly_(call_249, list_47);
    match_108 = call_250;
    goto end_match_380;
next_390:;
    if ((prim_.tag != Not_)) goto next_391;
    struct Ty_ call_251 = tyFun_(tyBool_, tyBool_);
    struct TySpec_ call_252 = mono_(call_251);
    match_108 = call_252;
    goto end_match_380;
next_391:;
    if ((prim_.tag != Exit_)) goto next_392;
    struct Ty_ call_253 = meta_(noLoc_, 1);
    struct Ty_ resultTy_1 = call_253;
    struct Ty_ call_254 = tyFun_(tyInt_, resultTy_1);
    struct TySpec_ call_255 = poly_(call_254, NULL);
    match_108 = call_255;
    goto end_match_380;
next_392:;
    if ((prim_.tag != Assert_)) goto next_393;
    struct Ty_ call_256 = tyFun_(tyBool_, tyUnit_);
    struct TySpec_ call_257 = mono_(call_256);
    match_108 = call_257;
    goto end_match_380;
next_393:;
    if ((prim_.tag != Box_)) goto next_394;
    struct Ty_ call_258 = meta_(noLoc_, 1);
    struct Ty_ itemTy_3 = call_258;
    struct Ty_ call_259 = tyFun_(itemTy_3, tyObj_);
    struct TySpec_ call_260 = poly_(call_259, NULL);
    match_108 = call_260;
    goto end_match_380;
next_394:;
    if ((prim_.tag != Unbox_)) goto next_395;
    struct Ty_ call_261 = meta_(noLoc_, 1);
    struct Ty_ itemTy_4 = call_261;
    struct Ty_ call_262 = tyFun_(tyObj_, itemTy_4);
    struct TySpec_ call_263 = poly_(call_262, NULL);
    match_108 = call_263;
    goto end_match_380;
next_395:;
    if ((prim_.tag != Char_3)) goto next_396;
    struct Ty_ call_264 = tyFun_(tyInt_, tyChar_);
    struct TySpec_ call_265 = mono_(call_264);
    match_108 = call_265;
    goto end_match_380;
next_396:;
    if ((prim_.tag != Int_3)) goto next_397;
    struct Ty_ call_266 = meta_(noLoc_, 1);
    struct Ty_ toIntTy_ = call_266;
    struct Ty_ call_267 = tyFun_(toIntTy_, tyInt_);
    struct Ty_* payload_33 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_33))) = toIntTy_;
    struct Trait_ variant_33 = (struct Trait_){.tag = ToInt_, .ToInt_ = payload_33};
    struct Trait_List* list_48 = (struct Trait_List*)malloc(sizeof(struct Trait_List));
    list_48->head = variant_33;
    list_48->tail = NULL;
    struct TySpec_ call_268 = poly_(call_267, list_48);
    match_108 = call_268;
    goto end_match_380;
next_397:;
    if ((prim_.tag != String_)) goto next_398;
    struct Ty_ call_269 = meta_(noLoc_, 1);
    struct Ty_ toStrTy_ = call_269;
    struct Ty_ call_270 = tyFun_(toStrTy_, tyStr_);
    struct Ty_* payload_34 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_34))) = toStrTy_;
    struct Trait_ variant_34 = (struct Trait_){.tag = ToString_, .ToString_ = payload_34};
    struct Trait_List* list_49 = (struct Trait_List*)malloc(sizeof(struct Trait_List));
    list_49->head = variant_34;
    list_49->tail = NULL;
    struct TySpec_ call_271 = poly_(call_270, list_49);
    match_108 = call_271;
    goto end_match_380;
next_398:;
    if ((prim_.tag != StrLength_)) goto next_399;
    struct Ty_ call_272 = tyFun_(tyStr_, tyInt_);
    struct TySpec_ call_273 = mono_(call_272);
    match_108 = call_273;
    goto end_match_380;
next_399:;
    if ((prim_.tag != StrGetSlice_)) goto next_401;
    struct Ty_ call_274 = tyFun_(tyStr_, tyStr_);
    struct Ty_ call_275 = tyFun_(tyInt_, call_274);
    struct Ty_ call_276 = tyFun_(tyInt_, call_275);
    struct TySpec_ call_277 = mono_(call_276);
    match_108 = call_277;
    goto end_match_380;
next_401:;
    if ((prim_.tag != Printfn_)) goto next_402;
    goto match_body_400;
next_402:;
    if ((prim_.tag != NativeFun_)) goto next_403;
    goto match_body_400;
match_body_400:;
    struct Ty_ call_278 = meta_(noLoc_, 1);
    struct TySpec_ call_279 = poly_(call_278, NULL);
    match_108 = call_279;
    goto end_match_380;
next_403:;
end_match_380:;
    return match_108;
}

struct HPat_ListTy_IntIntTuple2Tuple3 {
    struct HPat_List* t0;
    struct Ty_ t1;
    struct IntIntTuple2 t2;
};

struct HPat_ patUnit_(struct Ty_ tyUnit_, struct IntIntTuple2 loc_11) {
    struct HPat_ListTy_IntIntTuple2Tuple3 tuple_58;
    tuple_58.t0 = NULL;
    tuple_58.t1 = tyUnit_;
    tuple_58.t2 = loc_11;
    struct HPat_ListTy_IntIntTuple2Tuple3* payload_35 = (struct HPat_ListTy_IntIntTuple2Tuple3*)malloc(sizeof(struct HPat_ListTy_IntIntTuple2Tuple3));
    (*(((struct HPat_ListTy_IntIntTuple2Tuple3*)payload_35))) = tuple_58;
    struct HPat_ variant_35 = (struct HPat_){.tag = Tuple_2, .Tuple_2 = payload_35};
    return variant_35;
}

struct Ty_IntIntTuple2Tuple2 {
    struct Ty_ t0;
    struct IntIntTuple2 t1;
};

struct HPat_ patNil_(struct Ty_ itemTy_5, struct IntIntTuple2 loc_12) {
    struct Ty_IntIntTuple2Tuple2 tuple_59;
    tuple_59.t0 = itemTy_5;
    tuple_59.t1 = loc_12;
    struct Ty_IntIntTuple2Tuple2* payload_36 = (struct Ty_IntIntTuple2Tuple2*)malloc(sizeof(struct Ty_IntIntTuple2Tuple2));
    (*(((struct Ty_IntIntTuple2Tuple2*)payload_36))) = tuple_59;
    struct HPat_ variant_36 = (struct HPat_){.tag = Nil_, .Nil_ = payload_36};
    return variant_36;
}

struct IntTy_IntIntTuple2Tuple3 {
    int t0;
    struct Ty_ t1;
    struct IntIntTuple2 t2;
};

struct HPat_StringTy_IntIntTuple2Tuple4 {
    struct HPat_ t0;
    struct String t1;
    struct Ty_ t2;
    struct IntIntTuple2 t3;
};

struct HPat_HPat_ListTy_IntIntTuple2Tuple4 {
    struct HPat_ t0;
    struct HPat_List* t1;
    struct Ty_ t2;
    struct IntIntTuple2 t3;
};

struct HPat_HPat_Ty_IntIntTuple2Tuple4 {
    struct HPat_ t0;
    struct HPat_ t1;
    struct Ty_ t2;
    struct IntIntTuple2 t3;
};

struct HPat_IntIntIntTuple2Tuple3 {
    struct HPat_ t0;
    int t1;
    struct IntIntTuple2 t2;
};

struct HPat_Ty_IntIntTuple2Tuple3 {
    struct HPat_ t0;
    struct Ty_ t1;
    struct IntIntTuple2 t2;
};

struct Ty_IntIntTuple2Tuple2 patExtract_(struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct HPat_ pat_) {
    struct Ty_IntIntTuple2Tuple2 match_109;
    if ((pat_.tag != Lit_2)) goto next_405;
    struct Lit_ lit_1 = (*(pat_.Lit_2)).t0;
    struct IntIntTuple2 a_ = (*(pat_.Lit_2)).t1;
    struct Ty_ call_280 = litToTy_(tyStr_, tyChar_, tyInt_, tyBool_, lit_1);
    struct Ty_IntIntTuple2Tuple2 tuple_60;
    tuple_60.t0 = call_280;
    tuple_60.t1 = a_;
    match_109 = tuple_60;
    goto end_match_404;
next_405:;
    if ((pat_.tag != Nil_)) goto next_406;
    struct Ty_ itemTy_6 = (*(pat_.Nil_)).t0;
    struct IntIntTuple2 a_1 = (*(pat_.Nil_)).t1;
    struct Ty_ call_281 = tyList_(itemTy_6);
    struct Ty_IntIntTuple2Tuple2 tuple_61;
    tuple_61.t0 = call_281;
    tuple_61.t1 = a_1;
    match_109 = tuple_61;
    goto end_match_404;
next_406:;
    if ((pat_.tag != Discard_)) goto next_407;
    struct Ty_ ty_12 = (*(pat_.Discard_)).t0;
    struct IntIntTuple2 a_2 = (*(pat_.Discard_)).t1;
    struct Ty_IntIntTuple2Tuple2 tuple_62;
    tuple_62.t0 = ty_12;
    tuple_62.t1 = a_2;
    match_109 = tuple_62;
    goto end_match_404;
next_407:;
    if ((pat_.tag != Ref_1)) goto next_408;
    struct Ty_ ty_13 = (*(pat_.Ref_1)).t1;
    struct IntIntTuple2 a_3 = (*(pat_.Ref_1)).t2;
    struct Ty_IntIntTuple2Tuple2 tuple_63;
    tuple_63.t0 = ty_13;
    tuple_63.t1 = a_3;
    match_109 = tuple_63;
    goto end_match_404;
next_408:;
    if ((pat_.tag != Nav_2)) goto next_409;
    struct Ty_ ty_14 = (*(pat_.Nav_2)).t2;
    struct IntIntTuple2 a_4 = (*(pat_.Nav_2)).t3;
    struct Ty_IntIntTuple2Tuple2 tuple_64;
    tuple_64.t0 = ty_14;
    tuple_64.t1 = a_4;
    match_109 = tuple_64;
    goto end_match_404;
next_409:;
    if ((pat_.tag != Call_1)) goto next_410;
    struct Ty_ ty_15 = (*(pat_.Call_1)).t2;
    struct IntIntTuple2 a_5 = (*(pat_.Call_1)).t3;
    struct Ty_IntIntTuple2Tuple2 tuple_65;
    tuple_65.t0 = ty_15;
    tuple_65.t1 = a_5;
    match_109 = tuple_65;
    goto end_match_404;
next_410:;
    if ((pat_.tag != Cons_3)) goto next_411;
    struct Ty_ itemTy_7 = (*(pat_.Cons_3)).t2;
    struct IntIntTuple2 a_6 = (*(pat_.Cons_3)).t3;
    struct Ty_ call_282 = tyList_(itemTy_7);
    struct Ty_IntIntTuple2Tuple2 tuple_66;
    tuple_66.t0 = call_282;
    tuple_66.t1 = a_6;
    match_109 = tuple_66;
    goto end_match_404;
next_411:;
    if ((pat_.tag != Tuple_2)) goto next_412;
    struct Ty_ ty_16 = (*(pat_.Tuple_2)).t1;
    struct IntIntTuple2 a_7 = (*(pat_.Tuple_2)).t2;
    struct Ty_IntIntTuple2Tuple2 tuple_67;
    tuple_67.t0 = ty_16;
    tuple_67.t1 = a_7;
    match_109 = tuple_67;
    goto end_match_404;
next_412:;
    if ((pat_.tag != As_2)) goto next_413;
    struct HPat_ pat_1 = (*(pat_.As_2)).t0;
    struct IntIntTuple2 a_8 = (*(pat_.As_2)).t2;
    struct Ty_IntIntTuple2Tuple2 call_283 = patExtract_(tyStr_, tyChar_, tyInt_, tyBool_, pat_1);
    struct Ty_ ty_17 = call_283.t0;
    struct Ty_IntIntTuple2Tuple2 tuple_68;
    tuple_68.t0 = ty_17;
    tuple_68.t1 = a_8;
    match_109 = tuple_68;
    goto end_match_404;
next_413:;
    if ((pat_.tag != Anno_2)) goto next_414;
    struct Ty_ ty_18 = (*(pat_.Anno_2)).t1;
    struct IntIntTuple2 a_9 = (*(pat_.Anno_2)).t2;
    struct Ty_IntIntTuple2Tuple2 tuple_69;
    tuple_69.t0 = ty_18;
    tuple_69.t1 = a_9;
    match_109 = tuple_69;
    goto end_match_404;
next_414:;
    if ((pat_.tag != Or_3)) goto next_415;
    struct Ty_ ty_19 = (*(pat_.Or_3)).t2;
    struct IntIntTuple2 a_10 = (*(pat_.Or_3)).t3;
    struct Ty_IntIntTuple2Tuple2 tuple_70;
    tuple_70.t0 = ty_19;
    tuple_70.t1 = a_10;
    match_109 = tuple_70;
    goto end_match_404;
next_415:;
    exit(1);
end_match_404:;
    return match_109;
}

struct IntIntTuple2IntIntTuple2Fun1 {
    struct IntIntTuple2(*fun)(void*, struct IntIntTuple2);
    void* env;
};

struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2 {
    struct IntIntTuple2IntIntTuple2Fun1 t0;
    struct Ty_Ty_Fun1 t1;
};

struct HPat_ fun_10(void* env_4, struct HPat_ arg_16) {
    struct IntIntTuple2IntIntTuple2Fun1 arg_17 = (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)env_4))).t0;
    struct Ty_Ty_Fun1 arg_18 = (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)env_4))).t1;
    struct HPat_ call_284 = go_38(arg_17, arg_18, arg_16);
    return call_284;
}

struct HPat_ fun_11(void* env_5, struct HPat_ arg_19) {
    struct IntIntTuple2IntIntTuple2Fun1 arg_20 = (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)env_5))).t0;
    struct Ty_Ty_Fun1 arg_21 = (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)env_5))).t1;
    struct HPat_ call_285 = go_38(arg_20, arg_21, arg_19);
    return call_285;
}

struct HPat_ go_38(struct IntIntTuple2IntIntTuple2Fun1 g_, struct Ty_Ty_Fun1 f_10, struct HPat_ pat_3) {
    struct HPat_ match_110;
    if ((pat_3.tag != Lit_2)) goto next_417;
    struct Lit_ lit_2 = (*(pat_3.Lit_2)).t0;
    struct IntIntTuple2 a_11 = (*(pat_3.Lit_2)).t1;
    struct IntIntTuple2 app_34 = g_.fun(g_.env, a_11);
    struct Lit_IntIntTuple2Tuple2 tuple_71;
    tuple_71.t0 = lit_2;
    tuple_71.t1 = app_34;
    struct Lit_IntIntTuple2Tuple2* payload_37 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_37))) = tuple_71;
    struct HPat_ variant_37 = (struct HPat_){.tag = Lit_2, .Lit_2 = payload_37};
    match_110 = variant_37;
    goto end_match_416;
next_417:;
    if ((pat_3.tag != Nil_)) goto next_418;
    struct Ty_ itemTy_8 = (*(pat_3.Nil_)).t0;
    struct IntIntTuple2 a_12 = (*(pat_3.Nil_)).t1;
    struct Ty_ app_35 = f_10.fun(f_10.env, itemTy_8);
    struct IntIntTuple2 app_36 = g_.fun(g_.env, a_12);
    struct Ty_IntIntTuple2Tuple2 tuple_72;
    tuple_72.t0 = app_35;
    tuple_72.t1 = app_36;
    struct Ty_IntIntTuple2Tuple2* payload_38 = (struct Ty_IntIntTuple2Tuple2*)malloc(sizeof(struct Ty_IntIntTuple2Tuple2));
    (*(((struct Ty_IntIntTuple2Tuple2*)payload_38))) = tuple_72;
    struct HPat_ variant_38 = (struct HPat_){.tag = Nil_, .Nil_ = payload_38};
    match_110 = variant_38;
    goto end_match_416;
next_418:;
    if ((pat_3.tag != Discard_)) goto next_419;
    struct Ty_ ty_20 = (*(pat_3.Discard_)).t0;
    struct IntIntTuple2 a_13 = (*(pat_3.Discard_)).t1;
    struct Ty_ app_37 = f_10.fun(f_10.env, ty_20);
    struct IntIntTuple2 app_38 = g_.fun(g_.env, a_13);
    struct Ty_IntIntTuple2Tuple2 tuple_73;
    tuple_73.t0 = app_37;
    tuple_73.t1 = app_38;
    struct Ty_IntIntTuple2Tuple2* payload_39 = (struct Ty_IntIntTuple2Tuple2*)malloc(sizeof(struct Ty_IntIntTuple2Tuple2));
    (*(((struct Ty_IntIntTuple2Tuple2*)payload_39))) = tuple_73;
    struct HPat_ variant_39 = (struct HPat_){.tag = Discard_, .Discard_ = payload_39};
    match_110 = variant_39;
    goto end_match_416;
next_419:;
    if ((pat_3.tag != Ref_1)) goto next_420;
    int serial_4 = (*(pat_3.Ref_1)).t0;
    struct Ty_ ty_21 = (*(pat_3.Ref_1)).t1;
    struct IntIntTuple2 a_14 = (*(pat_3.Ref_1)).t2;
    struct Ty_ app_39 = f_10.fun(f_10.env, ty_21);
    struct IntIntTuple2 app_40 = g_.fun(g_.env, a_14);
    struct IntTy_IntIntTuple2Tuple3 tuple_74;
    tuple_74.t0 = serial_4;
    tuple_74.t1 = app_39;
    tuple_74.t2 = app_40;
    struct IntTy_IntIntTuple2Tuple3* payload_40 = (struct IntTy_IntIntTuple2Tuple3*)malloc(sizeof(struct IntTy_IntIntTuple2Tuple3));
    (*(((struct IntTy_IntIntTuple2Tuple3*)payload_40))) = tuple_74;
    struct HPat_ variant_40 = (struct HPat_){.tag = Ref_1, .Ref_1 = payload_40};
    match_110 = variant_40;
    goto end_match_416;
next_420:;
    if ((pat_3.tag != Nav_2)) goto next_421;
    struct HPat_ pat_4 = (*(pat_3.Nav_2)).t0;
    struct String ident_7 = (*(pat_3.Nav_2)).t1;
    struct Ty_ ty_22 = (*(pat_3.Nav_2)).t2;
    struct IntIntTuple2 a_15 = (*(pat_3.Nav_2)).t3;
    struct Ty_ app_41 = f_10.fun(f_10.env, ty_22);
    struct IntIntTuple2 app_42 = g_.fun(g_.env, a_15);
    struct HPat_StringTy_IntIntTuple2Tuple4 tuple_75;
    tuple_75.t0 = pat_4;
    tuple_75.t1 = ident_7;
    tuple_75.t2 = app_41;
    tuple_75.t3 = app_42;
    struct HPat_StringTy_IntIntTuple2Tuple4* payload_41 = (struct HPat_StringTy_IntIntTuple2Tuple4*)malloc(sizeof(struct HPat_StringTy_IntIntTuple2Tuple4));
    (*(((struct HPat_StringTy_IntIntTuple2Tuple4*)payload_41))) = tuple_75;
    struct HPat_ variant_41 = (struct HPat_){.tag = Nav_2, .Nav_2 = payload_41};
    match_110 = variant_41;
    goto end_match_416;
next_421:;
    if ((pat_3.tag != Call_1)) goto next_422;
    struct HPat_ callee_ = (*(pat_3.Call_1)).t0;
    struct HPat_List* args_ = (*(pat_3.Call_1)).t1;
    struct Ty_ ty_23 = (*(pat_3.Call_1)).t2;
    struct IntIntTuple2 a_16 = (*(pat_3.Call_1)).t3;
    struct HPat_ call_286 = go_38(g_, f_10, callee_);
    struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2 tuple_77;
    tuple_77.t0 = g_;
    tuple_77.t1 = f_10;
    void* box_1 = (void*)malloc(sizeof(struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2));
    (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)box_1))) = tuple_77;
    void* env_46 = box_1;
    struct HPat_HPat_Fun1 fun_52 = (struct HPat_HPat_Fun1){.fun = fun_10, .env = env_46};
    struct HPat_List* call_287 = listMap_8(fun_52, args_);
    struct Ty_ app_43 = f_10.fun(f_10.env, ty_23);
    struct IntIntTuple2 app_44 = g_.fun(g_.env, a_16);
    struct HPat_HPat_ListTy_IntIntTuple2Tuple4 tuple_76;
    tuple_76.t0 = call_286;
    tuple_76.t1 = call_287;
    tuple_76.t2 = app_43;
    tuple_76.t3 = app_44;
    struct HPat_HPat_ListTy_IntIntTuple2Tuple4* payload_42 = (struct HPat_HPat_ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct HPat_HPat_ListTy_IntIntTuple2Tuple4));
    (*(((struct HPat_HPat_ListTy_IntIntTuple2Tuple4*)payload_42))) = tuple_76;
    struct HPat_ variant_42 = (struct HPat_){.tag = Call_1, .Call_1 = payload_42};
    match_110 = variant_42;
    goto end_match_416;
next_422:;
    if ((pat_3.tag != Cons_3)) goto next_423;
    struct HPat_ l_10 = (*(pat_3.Cons_3)).t0;
    struct HPat_ r_23 = (*(pat_3.Cons_3)).t1;
    struct Ty_ itemTy_9 = (*(pat_3.Cons_3)).t2;
    struct IntIntTuple2 a_17 = (*(pat_3.Cons_3)).t3;
    struct HPat_ call_288 = go_38(g_, f_10, l_10);
    struct HPat_ call_289 = go_38(g_, f_10, r_23);
    struct Ty_ app_45 = f_10.fun(f_10.env, itemTy_9);
    struct IntIntTuple2 app_46 = g_.fun(g_.env, a_17);
    struct HPat_HPat_Ty_IntIntTuple2Tuple4 tuple_78;
    tuple_78.t0 = call_288;
    tuple_78.t1 = call_289;
    tuple_78.t2 = app_45;
    tuple_78.t3 = app_46;
    struct HPat_HPat_Ty_IntIntTuple2Tuple4* payload_43 = (struct HPat_HPat_Ty_IntIntTuple2Tuple4*)malloc(sizeof(struct HPat_HPat_Ty_IntIntTuple2Tuple4));
    (*(((struct HPat_HPat_Ty_IntIntTuple2Tuple4*)payload_43))) = tuple_78;
    struct HPat_ variant_43 = (struct HPat_){.tag = Cons_3, .Cons_3 = payload_43};
    match_110 = variant_43;
    goto end_match_416;
next_423:;
    if ((pat_3.tag != Tuple_2)) goto next_424;
    struct HPat_List* itemPats_ = (*(pat_3.Tuple_2)).t0;
    struct Ty_ ty_24 = (*(pat_3.Tuple_2)).t1;
    struct IntIntTuple2 a_18 = (*(pat_3.Tuple_2)).t2;
    struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2 tuple_80;
    tuple_80.t0 = g_;
    tuple_80.t1 = f_10;
    void* box_2 = (void*)malloc(sizeof(struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2));
    (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)box_2))) = tuple_80;
    void* env_47 = box_2;
    struct HPat_HPat_Fun1 fun_53 = (struct HPat_HPat_Fun1){.fun = fun_11, .env = env_47};
    struct HPat_List* call_290 = listMap_8(fun_53, itemPats_);
    struct Ty_ app_47 = f_10.fun(f_10.env, ty_24);
    struct IntIntTuple2 app_48 = g_.fun(g_.env, a_18);
    struct HPat_ListTy_IntIntTuple2Tuple3 tuple_79;
    tuple_79.t0 = call_290;
    tuple_79.t1 = app_47;
    tuple_79.t2 = app_48;
    struct HPat_ListTy_IntIntTuple2Tuple3* payload_44 = (struct HPat_ListTy_IntIntTuple2Tuple3*)malloc(sizeof(struct HPat_ListTy_IntIntTuple2Tuple3));
    (*(((struct HPat_ListTy_IntIntTuple2Tuple3*)payload_44))) = tuple_79;
    struct HPat_ variant_44 = (struct HPat_){.tag = Tuple_2, .Tuple_2 = payload_44};
    match_110 = variant_44;
    goto end_match_416;
next_424:;
    if ((pat_3.tag != As_2)) goto next_425;
    struct HPat_ pat_5 = (*(pat_3.As_2)).t0;
    int serial_5 = (*(pat_3.As_2)).t1;
    struct IntIntTuple2 a_19 = (*(pat_3.As_2)).t2;
    struct HPat_ call_291 = go_38(g_, f_10, pat_5);
    struct IntIntTuple2 app_49 = g_.fun(g_.env, a_19);
    struct HPat_IntIntIntTuple2Tuple3 tuple_81;
    tuple_81.t0 = call_291;
    tuple_81.t1 = serial_5;
    tuple_81.t2 = app_49;
    struct HPat_IntIntIntTuple2Tuple3* payload_45 = (struct HPat_IntIntIntTuple2Tuple3*)malloc(sizeof(struct HPat_IntIntIntTuple2Tuple3));
    (*(((struct HPat_IntIntIntTuple2Tuple3*)payload_45))) = tuple_81;
    struct HPat_ variant_45 = (struct HPat_){.tag = As_2, .As_2 = payload_45};
    match_110 = variant_45;
    goto end_match_416;
next_425:;
    if ((pat_3.tag != Anno_2)) goto next_426;
    struct HPat_ pat_6 = (*(pat_3.Anno_2)).t0;
    struct Ty_ ty_25 = (*(pat_3.Anno_2)).t1;
    struct IntIntTuple2 a_20 = (*(pat_3.Anno_2)).t2;
    struct HPat_ call_292 = go_38(g_, f_10, pat_6);
    struct Ty_ app_50 = f_10.fun(f_10.env, ty_25);
    struct IntIntTuple2 app_51 = g_.fun(g_.env, a_20);
    struct HPat_Ty_IntIntTuple2Tuple3 tuple_82;
    tuple_82.t0 = call_292;
    tuple_82.t1 = app_50;
    tuple_82.t2 = app_51;
    struct HPat_Ty_IntIntTuple2Tuple3* payload_46 = (struct HPat_Ty_IntIntTuple2Tuple3*)malloc(sizeof(struct HPat_Ty_IntIntTuple2Tuple3));
    (*(((struct HPat_Ty_IntIntTuple2Tuple3*)payload_46))) = tuple_82;
    struct HPat_ variant_46 = (struct HPat_){.tag = Anno_2, .Anno_2 = payload_46};
    match_110 = variant_46;
    goto end_match_416;
next_426:;
    if ((pat_3.tag != Or_3)) goto next_427;
    struct HPat_ first_2 = (*(pat_3.Or_3)).t0;
    struct HPat_ second_2 = (*(pat_3.Or_3)).t1;
    struct Ty_ ty_26 = (*(pat_3.Or_3)).t2;
    struct IntIntTuple2 a_21 = (*(pat_3.Or_3)).t3;
    struct HPat_ call_293 = go_38(g_, f_10, first_2);
    struct HPat_ call_294 = go_38(g_, f_10, second_2);
    struct Ty_ app_52 = f_10.fun(f_10.env, ty_26);
    struct IntIntTuple2 app_53 = g_.fun(g_.env, a_21);
    struct HPat_HPat_Ty_IntIntTuple2Tuple4 tuple_83;
    tuple_83.t0 = call_293;
    tuple_83.t1 = call_294;
    tuple_83.t2 = app_52;
    tuple_83.t3 = app_53;
    struct HPat_HPat_Ty_IntIntTuple2Tuple4* payload_47 = (struct HPat_HPat_Ty_IntIntTuple2Tuple4*)malloc(sizeof(struct HPat_HPat_Ty_IntIntTuple2Tuple4));
    (*(((struct HPat_HPat_Ty_IntIntTuple2Tuple4*)payload_47))) = tuple_83;
    struct HPat_ variant_47 = (struct HPat_){.tag = Or_3, .Or_3 = payload_47};
    match_110 = variant_47;
    goto end_match_416;
next_427:;
    exit(1);
end_match_416:;
    return match_110;
}

struct HPat_ patMap_(struct Ty_Ty_Fun1 f_10, struct IntIntTuple2IntIntTuple2Fun1 g_, struct HPat_ pat_2) {
    struct HPat_ call_295 = go_38(g_, f_10, pat_2);
    return call_295;
}

struct HExpr_ hxTrue_(struct Lit_ litTrue_, struct IntIntTuple2 loc_13) {
    struct Lit_IntIntTuple2Tuple2 tuple_84;
    tuple_84.t0 = litTrue_;
    tuple_84.t1 = loc_13;
    struct Lit_IntIntTuple2Tuple2* payload_48 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_48))) = tuple_84;
    struct HExpr_ variant_48 = (struct HExpr_){.tag = Lit_3, .Lit_3 = payload_48};
    return variant_48;
}

struct HExpr_ hxFalse_(struct Lit_ litFalse_, struct IntIntTuple2 loc_14) {
    struct Lit_IntIntTuple2Tuple2 tuple_85;
    tuple_85.t0 = litFalse_;
    tuple_85.t1 = loc_14;
    struct Lit_IntIntTuple2Tuple2* payload_49 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_49))) = tuple_85;
    struct HExpr_ variant_49 = (struct HExpr_){.tag = Lit_3, .Lit_3 = payload_49};
    return variant_49;
}

enum InfOp_Tag {
    App_2,
    Anno_3,
    Semi_2,
    CallProc_,
    CallClosure_,
    Tuple_3,
    Closure_,
};

struct InfOp_ {
    enum InfOp_Tag tag;
};

struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4 {
    struct InfOp_ t0;
    struct HExpr_List* t1;
    struct Ty_ t2;
    struct IntIntTuple2 t3;
};

struct HExpr_ hxApp_(struct HExpr_ f_11, struct HExpr_ x_33, struct Ty_ ty_27, struct IntIntTuple2 loc_15) {
    struct HExpr_List* list_51 = (struct HExpr_List*)malloc(sizeof(struct HExpr_List));
    list_51->head = x_33;
    list_51->tail = NULL;
    struct HExpr_List* list_50 = (struct HExpr_List*)malloc(sizeof(struct HExpr_List));
    list_50->head = f_11;
    list_50->tail = list_51;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4 tuple_86;
    tuple_86.t0 = (struct InfOp_){.tag = App_2};
    tuple_86.t1 = list_50;
    tuple_86.t2 = ty_27;
    tuple_86.t3 = loc_15;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4* payload_50 = (struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4));
    (*(((struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)payload_50))) = tuple_86;
    struct HExpr_ variant_50 = (struct HExpr_){.tag = Inf_, .Inf_ = payload_50};
    return variant_50;
}

struct HExpr_ hxAnno_(struct HExpr_ expr_, struct Ty_ ty_28, struct IntIntTuple2 loc_16) {
    struct HExpr_List* list_52 = (struct HExpr_List*)malloc(sizeof(struct HExpr_List));
    list_52->head = expr_;
    list_52->tail = NULL;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4 tuple_87;
    tuple_87.t0 = (struct InfOp_){.tag = Anno_3};
    tuple_87.t1 = list_52;
    tuple_87.t2 = ty_28;
    tuple_87.t3 = loc_16;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4* payload_51 = (struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4));
    (*(((struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)payload_51))) = tuple_87;
    struct HExpr_ variant_51 = (struct HExpr_){.tag = Inf_, .Inf_ = payload_51};
    return variant_51;
}

struct HExpr_ hxSemi_(struct Ty_ noTy_, struct HExpr_List* items_, struct IntIntTuple2 loc_17) {
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4 tuple_88;
    tuple_88.t0 = (struct InfOp_){.tag = Semi_2};
    tuple_88.t1 = items_;
    tuple_88.t2 = noTy_;
    tuple_88.t3 = loc_17;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4* payload_52 = (struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4));
    (*(((struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)payload_52))) = tuple_88;
    struct HExpr_ variant_52 = (struct HExpr_){.tag = Inf_, .Inf_ = payload_52};
    return variant_52;
}

struct HExpr_ hxCallProc_(struct HExpr_ callee_1, struct HExpr_List* args_1, struct Ty_ resultTy_2, struct IntIntTuple2 loc_18) {
    struct HExpr_List* list_53 = (struct HExpr_List*)malloc(sizeof(struct HExpr_List));
    list_53->head = callee_1;
    list_53->tail = args_1;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4 tuple_89;
    tuple_89.t0 = (struct InfOp_){.tag = CallProc_};
    tuple_89.t1 = list_53;
    tuple_89.t2 = resultTy_2;
    tuple_89.t3 = loc_18;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4* payload_53 = (struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4));
    (*(((struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)payload_53))) = tuple_89;
    struct HExpr_ variant_53 = (struct HExpr_){.tag = Inf_, .Inf_ = payload_53};
    return variant_53;
}

struct HExpr_ hxCallClosure_(struct HExpr_ callee_2, struct HExpr_List* args_2, struct Ty_ resultTy_3, struct IntIntTuple2 loc_19) {
    struct HExpr_List* list_54 = (struct HExpr_List*)malloc(sizeof(struct HExpr_List));
    list_54->head = callee_2;
    list_54->tail = args_2;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4 tuple_90;
    tuple_90.t0 = (struct InfOp_){.tag = CallClosure_};
    tuple_90.t1 = list_54;
    tuple_90.t2 = resultTy_3;
    tuple_90.t3 = loc_19;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4* payload_54 = (struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4));
    (*(((struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)payload_54))) = tuple_90;
    struct HExpr_ variant_54 = (struct HExpr_){.tag = Inf_, .Inf_ = payload_54};
    return variant_54;
}

struct Ty_Ty_Ty_Ty_Ty_Tuple5 {
    struct Ty_ t0;
    struct Ty_ t1;
    struct Ty_ t2;
    struct Ty_ t3;
    struct Ty_ t4;
};

struct Ty_ fun_12(void* env_6, struct HExpr_ arg_22) {
    struct Ty_ arg_23 = (*(((struct Ty_Ty_Ty_Ty_Ty_Tuple5*)env_6))).t0;
    struct Ty_ arg_24 = (*(((struct Ty_Ty_Ty_Ty_Ty_Tuple5*)env_6))).t1;
    struct Ty_ arg_25 = (*(((struct Ty_Ty_Ty_Ty_Ty_Tuple5*)env_6))).t2;
    struct Ty_ arg_26 = (*(((struct Ty_Ty_Ty_Ty_Ty_Tuple5*)env_6))).t3;
    struct Ty_ arg_27 = (*(((struct Ty_Ty_Ty_Ty_Ty_Tuple5*)env_6))).t4;
    struct Ty_ call_296 = exprToTy_(arg_23, arg_24, arg_25, arg_26, arg_27, arg_22);
    return call_296;
}

struct HExpr_ hxTuple_(struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct HExpr_List* items_1, struct IntIntTuple2 loc_20) {
    struct Ty_Ty_Ty_Ty_Ty_Tuple5 tuple_92;
    tuple_92.t0 = tyUnit_;
    tuple_92.t1 = tyStr_;
    tuple_92.t2 = tyChar_;
    tuple_92.t3 = tyInt_;
    tuple_92.t4 = tyBool_;
    void* box_3 = (void*)malloc(sizeof(struct Ty_Ty_Ty_Ty_Ty_Tuple5));
    (*(((struct Ty_Ty_Ty_Ty_Ty_Tuple5*)box_3))) = tuple_92;
    void* env_48 = box_3;
    struct HExpr_Ty_Fun1 fun_54 = (struct HExpr_Ty_Fun1){.fun = fun_12, .env = env_48};
    struct Ty_List* call_297 = listMap_11(fun_54, items_1);
    struct Ty_ call_298 = tyTuple_(call_297);
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4 tuple_91;
    tuple_91.t0 = (struct InfOp_){.tag = Tuple_3};
    tuple_91.t1 = items_1;
    tuple_91.t2 = call_298;
    tuple_91.t3 = loc_20;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4* payload_55 = (struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4));
    (*(((struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)payload_55))) = tuple_91;
    struct HExpr_ variant_55 = (struct HExpr_){.tag = Inf_, .Inf_ = payload_55};
    return variant_55;
}

struct HExpr_ hxUnit_(struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct IntIntTuple2 loc_21) {
    struct HExpr_ call_299 = hxTuple_(tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, NULL, loc_21);
    return call_299;
}

struct HPrim_Ty_IntIntTuple2Tuple3 {
    struct HPrim_ t0;
    struct Ty_ t1;
    struct IntIntTuple2 t2;
};

struct HExpr_ hxNil_(struct Ty_ itemTy_10, struct IntIntTuple2 loc_22) {
    struct Ty_ call_300 = tyList_(itemTy_10);
    struct HPrim_Ty_IntIntTuple2Tuple3 tuple_93;
    tuple_93.t0 = (struct HPrim_){.tag = Nil_1};
    tuple_93.t1 = call_300;
    tuple_93.t2 = loc_22;
    struct HPrim_Ty_IntIntTuple2Tuple3* payload_56 = (struct HPrim_Ty_IntIntTuple2Tuple3*)malloc(sizeof(struct HPrim_Ty_IntIntTuple2Tuple3));
    (*(((struct HPrim_Ty_IntIntTuple2Tuple3*)payload_56))) = tuple_93;
    struct HExpr_ variant_56 = (struct HExpr_){.tag = Prim_, .Prim_ = payload_56};
    return variant_56;
}

int hxIsUnitLit_(struct HExpr_ expr_1) {
    int match_111;
    if ((expr_1.tag != Inf_)) goto next_429;
    if (((*(expr_1.Inf_)).t0.tag != Tuple_3)) goto next_429;
    if ((!((!((*(expr_1.Inf_)).t1))))) goto next_429;
    match_111 = 1;
    goto end_match_428;
next_429:;
    match_111 = 0;
    goto end_match_428;
next_430:;
end_match_428:;
    return match_111;
}

int hxIsAlwaysTrue_(struct HExpr_ expr_2) {
    int match_112;
    if ((expr_2.tag != Lit_3)) goto next_432;
    if (((*(expr_2.Lit_3)).t0.tag != Bool_)) goto next_432;
    if ((!((*((*(expr_2.Lit_3)).t0.Bool_))))) goto next_432;
    match_112 = 1;
    goto end_match_431;
next_432:;
    match_112 = 0;
    goto end_match_431;
next_433:;
end_match_431:;
    return match_112;
}

struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4 {
    struct HExpr_ t0;
    struct HPat_HExpr_HExpr_Tuple3List* t1;
    struct Ty_ t2;
    struct IntIntTuple2 t3;
};

struct HExpr_StringTy_IntIntTuple2Tuple4 {
    struct HExpr_ t0;
    struct String t1;
    struct Ty_ t2;
    struct IntIntTuple2 t3;
};

struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5 {
    struct HPat_ t0;
    struct HExpr_ t1;
    struct HExpr_ t2;
    struct Ty_ t3;
    struct IntIntTuple2 t4;
};

struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7 {
    int t0;
    int t1;
    struct HPat_List* t2;
    struct HExpr_ t3;
    struct HExpr_ t4;
    struct Ty_ t5;
    struct IntIntTuple2 t6;
};

enum TyDecl_Tag {
    Synonym_1,
    Union_1,
};

struct TyDecl_ {
    enum TyDecl_Tag tag;
    union {
        struct Ty_IntIntTuple2Tuple2* Synonym_1;
        struct StringStringIntBoolTy_Tuple4ListIntIntTuple2Tuple3* Union_1;
    };
};

struct IntTyDecl_IntIntTuple2Tuple3 {
    int t0;
    struct TyDecl_ t1;
    struct IntIntTuple2 t2;
};

struct StringListIntIntTuple2Tuple2 {
    struct StringList* t0;
    struct IntIntTuple2 t1;
};

struct Ty_IntIntTuple2Tuple2 exprExtract_(struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct HExpr_ expr_3) {
    struct Ty_IntIntTuple2Tuple2 match_113;
    if ((expr_3.tag != Lit_3)) goto next_435;
    struct Lit_ lit_3 = (*(expr_3.Lit_3)).t0;
    struct IntIntTuple2 a_22 = (*(expr_3.Lit_3)).t1;
    struct Ty_ call_301 = litToTy_(tyStr_, tyChar_, tyInt_, tyBool_, lit_3);
    struct Ty_IntIntTuple2Tuple2 tuple_94;
    tuple_94.t0 = call_301;
    tuple_94.t1 = a_22;
    match_113 = tuple_94;
    goto end_match_434;
next_435:;
    if ((expr_3.tag != Ref_2)) goto next_436;
    struct Ty_ ty_29 = (*(expr_3.Ref_2)).t1;
    struct IntIntTuple2 a_23 = (*(expr_3.Ref_2)).t2;
    struct Ty_IntIntTuple2Tuple2 tuple_95;
    tuple_95.t0 = ty_29;
    tuple_95.t1 = a_23;
    match_113 = tuple_95;
    goto end_match_434;
next_436:;
    if ((expr_3.tag != Prim_)) goto next_437;
    struct Ty_ ty_30 = (*(expr_3.Prim_)).t1;
    struct IntIntTuple2 a_24 = (*(expr_3.Prim_)).t2;
    struct Ty_IntIntTuple2Tuple2 tuple_96;
    tuple_96.t0 = ty_30;
    tuple_96.t1 = a_24;
    match_113 = tuple_96;
    goto end_match_434;
next_437:;
    if ((expr_3.tag != Match_2)) goto next_438;
    struct Ty_ ty_31 = (*(expr_3.Match_2)).t2;
    struct IntIntTuple2 a_25 = (*(expr_3.Match_2)).t3;
    struct Ty_IntIntTuple2Tuple2 tuple_97;
    tuple_97.t0 = ty_31;
    tuple_97.t1 = a_25;
    match_113 = tuple_97;
    goto end_match_434;
next_438:;
    if ((expr_3.tag != Nav_3)) goto next_439;
    struct Ty_ ty_32 = (*(expr_3.Nav_3)).t2;
    struct IntIntTuple2 a_26 = (*(expr_3.Nav_3)).t3;
    struct Ty_IntIntTuple2Tuple2 tuple_98;
    tuple_98.t0 = ty_32;
    tuple_98.t1 = a_26;
    match_113 = tuple_98;
    goto end_match_434;
next_439:;
    if ((expr_3.tag != Inf_)) goto next_440;
    struct Ty_ ty_33 = (*(expr_3.Inf_)).t2;
    struct IntIntTuple2 a_27 = (*(expr_3.Inf_)).t3;
    struct Ty_IntIntTuple2Tuple2 tuple_99;
    tuple_99.t0 = ty_33;
    tuple_99.t1 = a_27;
    match_113 = tuple_99;
    goto end_match_434;
next_440:;
    if ((expr_3.tag != Let_2)) goto next_441;
    struct Ty_ ty_34 = (*(expr_3.Let_2)).t3;
    struct IntIntTuple2 a_28 = (*(expr_3.Let_2)).t4;
    struct Ty_IntIntTuple2Tuple2 tuple_100;
    tuple_100.t0 = ty_34;
    tuple_100.t1 = a_28;
    match_113 = tuple_100;
    goto end_match_434;
next_441:;
    if ((expr_3.tag != LetFun_1)) goto next_442;
    struct Ty_ ty_35 = (*(expr_3.LetFun_1)).t5;
    struct IntIntTuple2 a_29 = (*(expr_3.LetFun_1)).t6;
    struct Ty_IntIntTuple2Tuple2 tuple_101;
    tuple_101.t0 = ty_35;
    tuple_101.t1 = a_29;
    match_113 = tuple_101;
    goto end_match_434;
next_442:;
    if ((expr_3.tag != TyDecl_)) goto next_443;
    struct IntIntTuple2 a_30 = (*(expr_3.TyDecl_)).t2;
    struct Ty_IntIntTuple2Tuple2 tuple_102;
    tuple_102.t0 = tyUnit_;
    tuple_102.t1 = a_30;
    match_113 = tuple_102;
    goto end_match_434;
next_443:;
    if ((expr_3.tag != Open_2)) goto next_444;
    struct IntIntTuple2 a_31 = (*(expr_3.Open_2)).t1;
    struct Ty_IntIntTuple2Tuple2 tuple_103;
    tuple_103.t0 = tyUnit_;
    tuple_103.t1 = a_31;
    match_113 = tuple_103;
    goto end_match_434;
next_444:;
    if ((expr_3.tag != Error_2)) goto next_445;
    struct IntIntTuple2 a_32 = (*(expr_3.Error_2)).t1;
    struct IntIntTuple2* payload_57 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_57))) = a_32;
    struct Ty_ variant_57 = (struct Ty_){.tag = Error_1, .Error_1 = payload_57};
    struct Ty_IntIntTuple2Tuple2 tuple_104;
    tuple_104.t0 = variant_57;
    tuple_104.t1 = a_32;
    match_113 = tuple_104;
    goto end_match_434;
next_445:;
    exit(1);
end_match_434:;
    return match_113;
}

struct HPat_ goPat_(struct IntIntTuple2IntIntTuple2Fun1 g_1, struct Ty_Ty_Fun1 f_12, struct HPat_ pat_7) {
    struct HPat_ call_302 = patMap_(f_12, g_1, pat_7);
    return call_302;
}

struct HPat_HExpr_HExpr_Tuple3 fun_3(struct IntIntTuple2IntIntTuple2Fun1 g_1, struct Ty_Ty_Fun1 f_12, struct HPat_HExpr_HExpr_Tuple3 arg_143) {
    struct HPat_ pat_8 = arg_143.t0;
    struct HExpr_ guard_ = arg_143.t1;
    struct HExpr_ body_ = arg_143.t2;
    struct HPat_ call_303 = goPat_(g_1, f_12, pat_8);
    struct HExpr_ call_304 = go_39(g_1, f_12, guard_);
    struct HExpr_ call_305 = go_39(g_1, f_12, body_);
    struct HPat_HExpr_HExpr_Tuple3 tuple_105;
    tuple_105.t0 = call_303;
    tuple_105.t1 = call_304;
    tuple_105.t2 = call_305;
    return tuple_105;
}

struct HPat_HExpr_HExpr_Tuple3 fun_13(void* env_7, struct HPat_HExpr_HExpr_Tuple3 arg_28) {
    struct IntIntTuple2IntIntTuple2Fun1 arg_29 = (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)env_7))).t0;
    struct Ty_Ty_Fun1 arg_30 = (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)env_7))).t1;
    struct HPat_HExpr_HExpr_Tuple3 call_306 = fun_3(arg_29, arg_30, arg_28);
    return call_306;
}

struct HExpr_ fun_14(void* env_8, struct HExpr_ arg_31) {
    struct IntIntTuple2IntIntTuple2Fun1 arg_32 = (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)env_8))).t0;
    struct Ty_Ty_Fun1 arg_33 = (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)env_8))).t1;
    struct HExpr_ call_307 = go_39(arg_32, arg_33, arg_31);
    return call_307;
}

struct HPat_ fun_15(void* env_9, struct HPat_ arg_34) {
    struct IntIntTuple2IntIntTuple2Fun1 arg_35 = (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)env_9))).t0;
    struct Ty_Ty_Fun1 arg_36 = (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)env_9))).t1;
    struct HPat_ call_308 = goPat_(arg_35, arg_36, arg_34);
    return call_308;
}

struct HExpr_ go_39(struct IntIntTuple2IntIntTuple2Fun1 g_1, struct Ty_Ty_Fun1 f_12, struct HExpr_ expr_5) {
    struct HExpr_ match_114;
    if ((expr_5.tag != Lit_3)) goto next_447;
    struct Lit_ lit_4 = (*(expr_5.Lit_3)).t0;
    struct IntIntTuple2 a_33 = (*(expr_5.Lit_3)).t1;
    struct IntIntTuple2 app_54 = g_1.fun(g_1.env, a_33);
    struct Lit_IntIntTuple2Tuple2 tuple_106;
    tuple_106.t0 = lit_4;
    tuple_106.t1 = app_54;
    struct Lit_IntIntTuple2Tuple2* payload_58 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_58))) = tuple_106;
    struct HExpr_ variant_58 = (struct HExpr_){.tag = Lit_3, .Lit_3 = payload_58};
    match_114 = variant_58;
    goto end_match_446;
next_447:;
    if ((expr_5.tag != Ref_2)) goto next_448;
    int serial_6 = (*(expr_5.Ref_2)).t0;
    struct Ty_ ty_36 = (*(expr_5.Ref_2)).t1;
    struct IntIntTuple2 a_34 = (*(expr_5.Ref_2)).t2;
    struct Ty_ app_55 = f_12.fun(f_12.env, ty_36);
    struct IntIntTuple2 app_56 = g_1.fun(g_1.env, a_34);
    struct IntTy_IntIntTuple2Tuple3 tuple_107;
    tuple_107.t0 = serial_6;
    tuple_107.t1 = app_55;
    tuple_107.t2 = app_56;
    struct IntTy_IntIntTuple2Tuple3* payload_59 = (struct IntTy_IntIntTuple2Tuple3*)malloc(sizeof(struct IntTy_IntIntTuple2Tuple3));
    (*(((struct IntTy_IntIntTuple2Tuple3*)payload_59))) = tuple_107;
    struct HExpr_ variant_59 = (struct HExpr_){.tag = Ref_2, .Ref_2 = payload_59};
    match_114 = variant_59;
    goto end_match_446;
next_448:;
    if ((expr_5.tag != Prim_)) goto next_449;
    struct HPrim_ prim_1 = (*(expr_5.Prim_)).t0;
    struct Ty_ ty_37 = (*(expr_5.Prim_)).t1;
    struct IntIntTuple2 a_35 = (*(expr_5.Prim_)).t2;
    struct Ty_ app_57 = f_12.fun(f_12.env, ty_37);
    struct IntIntTuple2 app_58 = g_1.fun(g_1.env, a_35);
    struct HPrim_Ty_IntIntTuple2Tuple3 tuple_108;
    tuple_108.t0 = prim_1;
    tuple_108.t1 = app_57;
    tuple_108.t2 = app_58;
    struct HPrim_Ty_IntIntTuple2Tuple3* payload_60 = (struct HPrim_Ty_IntIntTuple2Tuple3*)malloc(sizeof(struct HPrim_Ty_IntIntTuple2Tuple3));
    (*(((struct HPrim_Ty_IntIntTuple2Tuple3*)payload_60))) = tuple_108;
    struct HExpr_ variant_60 = (struct HExpr_){.tag = Prim_, .Prim_ = payload_60};
    match_114 = variant_60;
    goto end_match_446;
next_449:;
    if ((expr_5.tag != Match_2)) goto next_450;
    struct HExpr_ target_ = (*(expr_5.Match_2)).t0;
    struct HPat_HExpr_HExpr_Tuple3List* arms_ = (*(expr_5.Match_2)).t1;
    struct Ty_ ty_38 = (*(expr_5.Match_2)).t2;
    struct IntIntTuple2 a_36 = (*(expr_5.Match_2)).t3;
    struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2 tuple_109;
    tuple_109.t0 = g_1;
    tuple_109.t1 = f_12;
    void* box_4 = (void*)malloc(sizeof(struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2));
    (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)box_4))) = tuple_109;
    void* env_49 = box_4;
    struct HPat_HExpr_HExpr_Tuple3HPat_HExpr_HExpr_Tuple3Fun1 fun_55 = (struct HPat_HExpr_HExpr_Tuple3HPat_HExpr_HExpr_Tuple3Fun1){.fun = fun_13, .env = env_49};
    struct HPat_HExpr_HExpr_Tuple3List* call_309 = listMap_10(fun_55, arms_);
    struct HPat_HExpr_HExpr_Tuple3List* arms_1 = call_309;
    struct HExpr_ call_310 = go_39(g_1, f_12, target_);
    struct Ty_ app_59 = f_12.fun(f_12.env, ty_38);
    struct IntIntTuple2 app_60 = g_1.fun(g_1.env, a_36);
    struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4 tuple_110;
    tuple_110.t0 = call_310;
    tuple_110.t1 = arms_1;
    tuple_110.t2 = app_59;
    tuple_110.t3 = app_60;
    struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4* payload_61 = (struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4));
    (*(((struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4*)payload_61))) = tuple_110;
    struct HExpr_ variant_61 = (struct HExpr_){.tag = Match_2, .Match_2 = payload_61};
    match_114 = variant_61;
    goto end_match_446;
next_450:;
    if ((expr_5.tag != Nav_3)) goto next_451;
    struct HExpr_ sub_ = (*(expr_5.Nav_3)).t0;
    struct String mes_ = (*(expr_5.Nav_3)).t1;
    struct Ty_ ty_39 = (*(expr_5.Nav_3)).t2;
    struct IntIntTuple2 a_37 = (*(expr_5.Nav_3)).t3;
    struct HExpr_ call_311 = go_39(g_1, f_12, sub_);
    struct Ty_ app_61 = f_12.fun(f_12.env, ty_39);
    struct IntIntTuple2 app_62 = g_1.fun(g_1.env, a_37);
    struct HExpr_StringTy_IntIntTuple2Tuple4 tuple_111;
    tuple_111.t0 = call_311;
    tuple_111.t1 = mes_;
    tuple_111.t2 = app_61;
    tuple_111.t3 = app_62;
    struct HExpr_StringTy_IntIntTuple2Tuple4* payload_62 = (struct HExpr_StringTy_IntIntTuple2Tuple4*)malloc(sizeof(struct HExpr_StringTy_IntIntTuple2Tuple4));
    (*(((struct HExpr_StringTy_IntIntTuple2Tuple4*)payload_62))) = tuple_111;
    struct HExpr_ variant_62 = (struct HExpr_){.tag = Nav_3, .Nav_3 = payload_62};
    match_114 = variant_62;
    goto end_match_446;
next_451:;
    if ((expr_5.tag != Inf_)) goto next_452;
    struct InfOp_ infOp_ = (*(expr_5.Inf_)).t0;
    struct HExpr_List* args_3 = (*(expr_5.Inf_)).t1;
    struct Ty_ resultTy_4 = (*(expr_5.Inf_)).t2;
    struct IntIntTuple2 a_38 = (*(expr_5.Inf_)).t3;
    struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2 tuple_113;
    tuple_113.t0 = g_1;
    tuple_113.t1 = f_12;
    void* box_5 = (void*)malloc(sizeof(struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2));
    (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)box_5))) = tuple_113;
    void* env_50 = box_5;
    struct HExpr_HExpr_Fun1 fun_56 = (struct HExpr_HExpr_Fun1){.fun = fun_14, .env = env_50};
    struct HExpr_List* call_312 = listMap_9(fun_56, args_3);
    struct Ty_ app_63 = f_12.fun(f_12.env, resultTy_4);
    struct IntIntTuple2 app_64 = g_1.fun(g_1.env, a_38);
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4 tuple_112;
    tuple_112.t0 = infOp_;
    tuple_112.t1 = call_312;
    tuple_112.t2 = app_63;
    tuple_112.t3 = app_64;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4* payload_63 = (struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4));
    (*(((struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)payload_63))) = tuple_112;
    struct HExpr_ variant_63 = (struct HExpr_){.tag = Inf_, .Inf_ = payload_63};
    match_114 = variant_63;
    goto end_match_446;
next_452:;
    if ((expr_5.tag != Let_2)) goto next_453;
    struct HPat_ pat_9 = (*(expr_5.Let_2)).t0;
    struct HExpr_ init_ = (*(expr_5.Let_2)).t1;
    struct HExpr_ next_6 = (*(expr_5.Let_2)).t2;
    struct Ty_ ty_40 = (*(expr_5.Let_2)).t3;
    struct IntIntTuple2 a_39 = (*(expr_5.Let_2)).t4;
    struct HPat_ call_313 = goPat_(g_1, f_12, pat_9);
    struct HExpr_ call_314 = go_39(g_1, f_12, init_);
    struct HExpr_ call_315 = go_39(g_1, f_12, next_6);
    struct Ty_ app_65 = f_12.fun(f_12.env, ty_40);
    struct IntIntTuple2 app_66 = g_1.fun(g_1.env, a_39);
    struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5 tuple_114;
    tuple_114.t0 = call_313;
    tuple_114.t1 = call_314;
    tuple_114.t2 = call_315;
    tuple_114.t3 = app_65;
    tuple_114.t4 = app_66;
    struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5* payload_64 = (struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5*)malloc(sizeof(struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5));
    (*(((struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5*)payload_64))) = tuple_114;
    struct HExpr_ variant_64 = (struct HExpr_){.tag = Let_2, .Let_2 = payload_64};
    match_114 = variant_64;
    goto end_match_446;
next_453:;
    if ((expr_5.tag != LetFun_1)) goto next_454;
    int serial_7 = (*(expr_5.LetFun_1)).t0;
    int isMainFun_ = (*(expr_5.LetFun_1)).t1;
    struct HPat_List* args_4 = (*(expr_5.LetFun_1)).t2;
    struct HExpr_ body_1 = (*(expr_5.LetFun_1)).t3;
    struct HExpr_ next_7 = (*(expr_5.LetFun_1)).t4;
    struct Ty_ ty_41 = (*(expr_5.LetFun_1)).t5;
    struct IntIntTuple2 a_40 = (*(expr_5.LetFun_1)).t6;
    struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2 tuple_116;
    tuple_116.t0 = g_1;
    tuple_116.t1 = f_12;
    void* box_6 = (void*)malloc(sizeof(struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2));
    (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)box_6))) = tuple_116;
    void* env_51 = box_6;
    struct HPat_HPat_Fun1 fun_57 = (struct HPat_HPat_Fun1){.fun = fun_15, .env = env_51};
    struct HPat_List* call_316 = listMap_8(fun_57, args_4);
    struct HExpr_ call_317 = go_39(g_1, f_12, body_1);
    struct HExpr_ call_318 = go_39(g_1, f_12, next_7);
    struct Ty_ app_67 = f_12.fun(f_12.env, ty_41);
    struct IntIntTuple2 app_68 = g_1.fun(g_1.env, a_40);
    struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7 tuple_115;
    tuple_115.t0 = serial_7;
    tuple_115.t1 = isMainFun_;
    tuple_115.t2 = call_316;
    tuple_115.t3 = call_317;
    tuple_115.t4 = call_318;
    tuple_115.t5 = app_67;
    tuple_115.t6 = app_68;
    struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7* payload_65 = (struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7*)malloc(sizeof(struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7));
    (*(((struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7*)payload_65))) = tuple_115;
    struct HExpr_ variant_65 = (struct HExpr_){.tag = LetFun_1, .LetFun_1 = payload_65};
    match_114 = variant_65;
    goto end_match_446;
next_454:;
    if ((expr_5.tag != TyDecl_)) goto next_455;
    int serial_8 = (*(expr_5.TyDecl_)).t0;
    struct TyDecl_ tyDef_1 = (*(expr_5.TyDecl_)).t1;
    struct IntIntTuple2 a_41 = (*(expr_5.TyDecl_)).t2;
    struct IntIntTuple2 app_69 = g_1.fun(g_1.env, a_41);
    struct IntTyDecl_IntIntTuple2Tuple3 tuple_117;
    tuple_117.t0 = serial_8;
    tuple_117.t1 = tyDef_1;
    tuple_117.t2 = app_69;
    struct IntTyDecl_IntIntTuple2Tuple3* payload_66 = (struct IntTyDecl_IntIntTuple2Tuple3*)malloc(sizeof(struct IntTyDecl_IntIntTuple2Tuple3));
    (*(((struct IntTyDecl_IntIntTuple2Tuple3*)payload_66))) = tuple_117;
    struct HExpr_ variant_66 = (struct HExpr_){.tag = TyDecl_, .TyDecl_ = payload_66};
    match_114 = variant_66;
    goto end_match_446;
next_455:;
    if ((expr_5.tag != Open_2)) goto next_456;
    struct StringList* path_ = (*(expr_5.Open_2)).t0;
    struct IntIntTuple2 a_42 = (*(expr_5.Open_2)).t1;
    struct IntIntTuple2 app_70 = g_1.fun(g_1.env, a_42);
    struct StringListIntIntTuple2Tuple2 tuple_118;
    tuple_118.t0 = path_;
    tuple_118.t1 = app_70;
    struct StringListIntIntTuple2Tuple2* payload_67 = (struct StringListIntIntTuple2Tuple2*)malloc(sizeof(struct StringListIntIntTuple2Tuple2));
    (*(((struct StringListIntIntTuple2Tuple2*)payload_67))) = tuple_118;
    struct HExpr_ variant_67 = (struct HExpr_){.tag = Open_2, .Open_2 = payload_67};
    match_114 = variant_67;
    goto end_match_446;
next_456:;
    if ((expr_5.tag != Error_2)) goto next_457;
    struct String error_ = (*(expr_5.Error_2)).t0;
    struct IntIntTuple2 a_43 = (*(expr_5.Error_2)).t1;
    struct IntIntTuple2 app_71 = g_1.fun(g_1.env, a_43);
    struct StringIntIntTuple2Tuple2 tuple_119;
    tuple_119.t0 = error_;
    tuple_119.t1 = app_71;
    struct StringIntIntTuple2Tuple2* payload_68 = (struct StringIntIntTuple2Tuple2*)malloc(sizeof(struct StringIntIntTuple2Tuple2));
    (*(((struct StringIntIntTuple2Tuple2*)payload_68))) = tuple_119;
    struct HExpr_ variant_68 = (struct HExpr_){.tag = Error_2, .Error_2 = payload_68};
    match_114 = variant_68;
    goto end_match_446;
next_457:;
    exit(1);
end_match_446:;
    return match_114;
}

struct HExpr_ exprMap_(struct Ty_Ty_Fun1 f_12, struct IntIntTuple2IntIntTuple2Fun1 g_1, struct HExpr_ expr_4) {
    struct HExpr_ call_319 = go_39(g_1, f_12, expr_4);
    return call_319;
}

struct Ty_ exprToTy_(struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct HExpr_ expr_6) {
    struct Ty_IntIntTuple2Tuple2 call_320 = exprExtract_(tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, expr_6);
    struct Ty_ ty_42 = call_320.t0;
    return ty_42;
}

struct IntIntTuple2 go_(int r_, struct String text_, int y_1, int x_2, int i_) {
    struct IntIntTuple2 match_115;
    if ((i_ != r_)) goto next_459;
    struct IntIntTuple2 tuple_120;
    tuple_120.t0 = y_1;
    tuple_120.t1 = x_2;
    match_115 = tuple_120;
    goto end_match_458;
next_459:;
    if ((i_ == r_)) goto next_460;
    struct IntIntTuple2 match_116;
    if ((text_.str[i_] != '\n')) goto next_462;
    struct IntIntTuple2 call_321 = go_(r_, text_, (y_1 + 1), 0, (i_ + 1));
    match_116 = call_321;
    goto end_match_461;
next_462:;
    if ((text_.str[i_] == '\n')) goto next_463;
    struct IntIntTuple2 call_322 = go_(r_, text_, y_1, (x_2 + 1), (i_ + 1));
    match_116 = call_322;
    goto end_match_461;
next_463:;
    exit(1);
end_match_461:;
    match_115 = match_116;
    goto end_match_458;
next_460:;
    exit(1);
end_match_458:;
    return match_115;
}

struct IntIntTuple2 locShift_(struct String text_, int l_, int r_, struct IntIntTuple2 arg_144) {
    int y_ = arg_144.t0;
    int x_1 = arg_144.t1;
    int match_117;
    int match_118;
    if ((l_ < 0)) goto next_466;
    match_118 = (r_ >= l_);
    goto end_match_465;
next_466:;
    if ((l_ >= 0)) goto next_467;
    match_118 = 0;
    goto end_match_465;
next_467:;
    exit(1);
end_match_465:;
    if ((!(match_118))) goto next_468;
    match_117 = (text_.len >= r_);
    goto end_match_464;
next_468:;
    if (match_118) goto next_469;
    match_117 = 0;
    goto end_match_464;
next_469:;
    exit(1);
end_match_464:;
    milone_assert(match_117, 40, 2);
    int call_323 = 0;
    struct IntIntTuple2 call_324 = go_(r_, text_, y_, x_1, l_);
    return call_324;
}

int charIsIdent_(char c_) {
    int match_119;
    int match_120;
    if ((c_ != '_')) goto next_472;
    match_120 = 1;
    goto end_match_471;
next_472:;
    if ((c_ == '_')) goto next_473;
    int call_325 = charIsDigit_(c_);
    match_120 = call_325;
    goto end_match_471;
next_473:;
    exit(1);
end_match_471:;
    if ((!(match_120))) goto next_474;
    match_119 = 1;
    goto end_match_470;
next_474:;
    if (match_120) goto next_475;
    int call_326 = charIsAlpha_(c_);
    match_119 = call_326;
    goto end_match_470;
next_475:;
    exit(1);
end_match_470:;
    return match_119;
}

int charIsOp_(char c_1) {
    int match_121;
    int match_122;
    int match_123;
    int match_124;
    int match_125;
    int match_126;
    int match_127;
    int match_128;
    int match_129;
    int match_130;
    int match_131;
    int match_132;
    int match_133;
    int match_134;
    if ((c_1 != '+')) goto next_490;
    match_134 = 1;
    goto end_match_489;
next_490:;
    if ((c_1 == '+')) goto next_491;
    match_134 = (c_1 == '-');
    goto end_match_489;
next_491:;
    exit(1);
end_match_489:;
    if ((!(match_134))) goto next_492;
    match_133 = 1;
    goto end_match_488;
next_492:;
    if (match_134) goto next_493;
    match_133 = (c_1 == '*');
    goto end_match_488;
next_493:;
    exit(1);
end_match_488:;
    if ((!(match_133))) goto next_494;
    match_132 = 1;
    goto end_match_487;
next_494:;
    if (match_133) goto next_495;
    match_132 = (c_1 == '/');
    goto end_match_487;
next_495:;
    exit(1);
end_match_487:;
    if ((!(match_132))) goto next_496;
    match_131 = 1;
    goto end_match_486;
next_496:;
    if (match_132) goto next_497;
    match_131 = (c_1 == '%');
    goto end_match_486;
next_497:;
    exit(1);
end_match_486:;
    if ((!(match_131))) goto next_498;
    match_130 = 1;
    goto end_match_485;
next_498:;
    if (match_131) goto next_499;
    match_130 = (c_1 == '=');
    goto end_match_485;
next_499:;
    exit(1);
end_match_485:;
    if ((!(match_130))) goto next_500;
    match_129 = 1;
    goto end_match_484;
next_500:;
    if (match_130) goto next_501;
    match_129 = (c_1 == '<');
    goto end_match_484;
next_501:;
    exit(1);
end_match_484:;
    if ((!(match_129))) goto next_502;
    match_128 = 1;
    goto end_match_483;
next_502:;
    if (match_129) goto next_503;
    match_128 = (c_1 == '>');
    goto end_match_483;
next_503:;
    exit(1);
end_match_483:;
    if ((!(match_128))) goto next_504;
    match_127 = 1;
    goto end_match_482;
next_504:;
    if (match_128) goto next_505;
    match_127 = (c_1 == '^');
    goto end_match_482;
next_505:;
    exit(1);
end_match_482:;
    if ((!(match_127))) goto next_506;
    match_126 = 1;
    goto end_match_481;
next_506:;
    if (match_127) goto next_507;
    match_126 = (c_1 == '&');
    goto end_match_481;
next_507:;
    exit(1);
end_match_481:;
    if ((!(match_126))) goto next_508;
    match_125 = 1;
    goto end_match_480;
next_508:;
    if (match_126) goto next_509;
    match_125 = (c_1 == '|');
    goto end_match_480;
next_509:;
    exit(1);
end_match_480:;
    if ((!(match_125))) goto next_510;
    match_124 = 1;
    goto end_match_479;
next_510:;
    if (match_125) goto next_511;
    match_124 = (c_1 == ':');
    goto end_match_479;
next_511:;
    exit(1);
end_match_479:;
    if ((!(match_124))) goto next_512;
    match_123 = 1;
    goto end_match_478;
next_512:;
    if (match_124) goto next_513;
    match_123 = (c_1 == '@');
    goto end_match_478;
next_513:;
    exit(1);
end_match_478:;
    if ((!(match_123))) goto next_514;
    match_122 = 1;
    goto end_match_477;
next_514:;
    if (match_123) goto next_515;
    match_122 = (c_1 == ';');
    goto end_match_477;
next_515:;
    exit(1);
end_match_477:;
    if ((!(match_122))) goto next_516;
    match_121 = 1;
    goto end_match_476;
next_516:;
    if (match_122) goto next_517;
    match_121 = (c_1 == '.');
    goto end_match_476;
next_517:;
    exit(1);
end_match_476:;
    return match_121;
}

int charIsPun_(char c_2) {
    int match_135;
    int match_136;
    int match_137;
    int match_138;
    if ((c_2 != ',')) goto next_522;
    match_138 = 1;
    goto end_match_521;
next_522:;
    if ((c_2 == ',')) goto next_523;
    match_138 = (c_2 == '(');
    goto end_match_521;
next_523:;
    exit(1);
end_match_521:;
    if ((!(match_138))) goto next_524;
    match_137 = 1;
    goto end_match_520;
next_524:;
    if (match_138) goto next_525;
    match_137 = (c_2 == ')');
    goto end_match_520;
next_525:;
    exit(1);
end_match_520:;
    if ((!(match_137))) goto next_526;
    match_136 = 1;
    goto end_match_519;
next_526:;
    if (match_137) goto next_527;
    match_136 = (c_2 == '[');
    goto end_match_519;
next_527:;
    exit(1);
end_match_519:;
    if ((!(match_136))) goto next_528;
    match_135 = 1;
    goto end_match_518;
next_528:;
    if (match_136) goto next_529;
    match_135 = (c_2 == ']');
    goto end_match_518;
next_529:;
    exit(1);
end_match_518:;
    return match_135;
}

int go_1(struct String s_, struct String prefix_, int pi_, int si_) {
    int match_139;
    if ((pi_ != prefix_.len)) goto next_531;
    match_139 = 1;
    goto end_match_530;
next_531:;
    if ((pi_ == prefix_.len)) goto next_532;
    int match_140;
    int match_141;
    if ((si_ >= s_.len)) goto next_535;
    match_141 = (prefix_.str[pi_] == s_.str[si_]);
    goto end_match_534;
next_535:;
    if ((si_ < s_.len)) goto next_536;
    match_141 = 0;
    goto end_match_534;
next_536:;
    exit(1);
end_match_534:;
    if ((!(match_141))) goto next_537;
    int call_327 = go_1(s_, prefix_, (pi_ + 1), (si_ + 1));
    match_140 = call_327;
    goto end_match_533;
next_537:;
    if (match_141) goto next_538;
    match_140 = 0;
    goto end_match_533;
next_538:;
    exit(1);
end_match_533:;
    match_139 = match_140;
    goto end_match_530;
next_532:;
    exit(1);
end_match_530:;
    return match_139;
}

int strIsFollowedBy_(int i_1, struct String prefix_, struct String s_) {
    int match_142;
    if ((s_.len < (i_1 + prefix_.len))) goto next_540;
    int call_328 = go_1(s_, prefix_, 0, i_1);
    match_142 = call_328;
    goto end_match_539;
next_540:;
    if ((s_.len >= (i_1 + prefix_.len))) goto next_541;
    match_142 = 0;
    goto end_match_539;
next_541:;
    exit(1);
end_match_539:;
    return match_142;
}

int strIsFollowedByRawQuotes_(int i_2, struct String s_1) {
    int call_329 = strIsFollowedBy_(i_2, (struct String){.str = "\"\"\"", .len = 3}, s_1);
    return call_329;
}

int scanError_(struct String arg_145, int i_3) {
    return (i_3 + 1);
}

int lookEof_(struct String text_1, int i_4) {
    return (i_4 >= text_1.len);
}

int lookSpace_(struct String text_2, int i_5) {
    int call_330 = charIsSpace_(text_2.str[i_5]);
    return call_330;
}

int go_2(struct String text_3, int i_7) {
    int match_143;
    int match_144;
    if ((i_7 >= text_3.len)) goto next_544;
    int call_331 = charIsSpace_(text_3.str[i_7]);
    match_144 = call_331;
    goto end_match_543;
next_544:;
    if ((i_7 < text_3.len)) goto next_545;
    match_144 = 0;
    goto end_match_543;
next_545:;
    exit(1);
end_match_543:;
    if ((!(match_144))) goto next_546;
    int call_332 = go_2(text_3, (i_7 + 1));
    match_143 = call_332;
    goto end_match_542;
next_546:;
    if (match_144) goto next_547;
    match_143 = i_7;
    goto end_match_542;
next_547:;
    exit(1);
end_match_542:;
    return match_143;
}

int scanSpace_(struct String text_3, int i_6) {
    int call_333 = lookSpace_(text_3, i_6);
    milone_assert(call_333, 103, 2);
    int call_334 = 0;
    int call_335 = go_2(text_3, i_6);
    return call_335;
}

int lookComment_(struct String text_4, int i_8) {
    int match_145;
    int call_336 = strIsFollowedBy_(i_8, (struct String){.str = "//", .len = 2}, text_4);
    if ((!(call_336))) goto next_549;
    match_145 = 1;
    goto end_match_548;
next_549:;
    if (call_336) goto next_550;
    int call_337 = strIsFollowedBy_(i_8, (struct String){.str = "[<", .len = 2}, text_4);
    match_145 = call_337;
    goto end_match_548;
next_550:;
    exit(1);
end_match_548:;
    return match_145;
}

int go_3(struct String text_5, int i_10) {
    int match_146;
    if ((i_10 != text_5.len)) goto next_552;
    match_146 = i_10;
    goto end_match_551;
next_552:;
    if ((i_10 == text_5.len)) goto next_553;
    int match_147;
    if ((text_5.str[i_10] != '\n')) goto next_555;
    match_147 = (i_10 + 1);
    goto end_match_554;
next_555:;
    if ((text_5.str[i_10] == '\n')) goto next_556;
    int call_338 = go_3(text_5, (i_10 + 1));
    match_147 = call_338;
    goto end_match_554;
next_556:;
    exit(1);
end_match_554:;
    match_146 = match_147;
    goto end_match_551;
next_553:;
    exit(1);
end_match_551:;
    return match_146;
}

int scanLine_(struct String text_5, int i_9) {
    int call_339 = lookComment_(text_5, i_9);
    milone_assert(call_339, 117, 2);
    int call_340 = 0;
    int call_341 = go_3(text_5, i_9);
    return call_341;
}

int lookPun_(struct String text_6, int i_11) {
    int call_342 = charIsPun_(text_6.str[i_11]);
    return call_342;
}

int scanPun_(struct String text_7, int i_12) {
    int call_343 = lookPun_(text_7, i_12);
    milone_assert(call_343, 131, 2);
    int call_344 = 0;
    return (i_12 + 1);
}

int lookOp_(struct String text_8, int i_13) {
    int call_345 = charIsOp_(text_8.str[i_13]);
    return call_345;
}

int go_4(struct String text_9, int i_15) {
    int match_148;
    int match_149;
    if ((i_15 >= text_9.len)) goto next_559;
    int call_346 = charIsOp_(text_9.str[i_15]);
    match_149 = call_346;
    goto end_match_558;
next_559:;
    if ((i_15 < text_9.len)) goto next_560;
    match_149 = 0;
    goto end_match_558;
next_560:;
    exit(1);
end_match_558:;
    if ((!(match_149))) goto next_561;
    int call_347 = go_4(text_9, (i_15 + 1));
    match_148 = call_347;
    goto end_match_557;
next_561:;
    if (match_149) goto next_562;
    match_148 = i_15;
    goto end_match_557;
next_562:;
    exit(1);
end_match_557:;
    return match_148;
}

int scanOp_(struct String text_9, int i_14) {
    int call_348 = lookOp_(text_9, i_14);
    milone_assert(call_348, 138, 2);
    int call_349 = 0;
    int call_350 = go_4(text_9, i_14);
    return call_350;
}

int lookIdent_(struct String text_10, int i_16) {
    int match_150;
    int call_351 = charIsIdent_(text_10.str[i_16]);
    if ((!(call_351))) goto next_564;
    int call_352 = charIsDigit_(text_10.str[i_16]);
    match_150 = (!(call_352));
    goto end_match_563;
next_564:;
    if (call_351) goto next_565;
    match_150 = 0;
    goto end_match_563;
next_565:;
    exit(1);
end_match_563:;
    return match_150;
}

int go_5(struct String text_11, int i_18) {
    int match_151;
    int match_152;
    if ((i_18 >= text_11.len)) goto next_568;
    int call_353 = charIsIdent_(text_11.str[i_18]);
    match_152 = call_353;
    goto end_match_567;
next_568:;
    if ((i_18 < text_11.len)) goto next_569;
    match_152 = 0;
    goto end_match_567;
next_569:;
    exit(1);
end_match_567:;
    if ((!(match_152))) goto next_570;
    int call_354 = go_5(text_11, (i_18 + 1));
    match_151 = call_354;
    goto end_match_566;
next_570:;
    if (match_152) goto next_571;
    match_151 = i_18;
    goto end_match_566;
next_571:;
    exit(1);
end_match_566:;
    return match_151;
}

int scanIdent_(struct String text_11, int i_17) {
    int call_355 = lookIdent_(text_11, i_17);
    milone_assert(call_355, 151, 2);
    int call_356 = 0;
    int call_357 = go_5(text_11, i_17);
    return call_357;
}

int lookIntLit_(struct String text_12, int i_19) {
    int call_358 = charIsDigit_(text_12.str[i_19]);
    return call_358;
}

int go_6(struct String text_13, int i_21) {
    int match_153;
    int match_154;
    if ((i_21 >= text_13.len)) goto next_574;
    int call_359 = charIsDigit_(text_13.str[i_21]);
    match_154 = call_359;
    goto end_match_573;
next_574:;
    if ((i_21 < text_13.len)) goto next_575;
    match_154 = 0;
    goto end_match_573;
next_575:;
    exit(1);
end_match_573:;
    if ((!(match_154))) goto next_576;
    int call_360 = go_6(text_13, (i_21 + 1));
    match_153 = call_360;
    goto end_match_572;
next_576:;
    if (match_154) goto next_577;
    match_153 = i_21;
    goto end_match_572;
next_577:;
    exit(1);
end_match_572:;
    return match_153;
}

int scanIntLit_(struct String text_13, int i_20) {
    int call_361 = lookIntLit_(text_13, i_20);
    milone_assert(call_361, 163, 2);
    int call_362 = 0;
    int call_363 = go_6(text_13, i_20);
    return call_363;
}

int lookCharLit_(struct String text_14, int i_22) {
    return (text_14.str[i_22] == '\'');
}

struct BoolIntTuple2 {
    int t0;
    int t1;
};

struct BoolIntTuple2 go_7(struct String text_15, int i_24) {
    struct BoolIntTuple2 match_155;
    int match_156;
    if (((i_24 + 1) >= text_15.len)) goto next_580;
    match_156 = (text_15.str[i_24] == '\\');
    goto end_match_579;
next_580:;
    if (((i_24 + 1) < text_15.len)) goto next_581;
    match_156 = 0;
    goto end_match_579;
next_581:;
    exit(1);
end_match_579:;
    if ((!(match_156))) goto next_582;
    struct BoolIntTuple2 call_364 = go_7(text_15, (i_24 + 2));
    match_155 = call_364;
    goto end_match_578;
next_582:;
    if (match_156) goto next_583;
    struct BoolIntTuple2 match_157;
    int match_158;
    if ((i_24 >= text_15.len)) goto next_586;
    match_158 = (text_15.str[i_24] == '\'');
    goto end_match_585;
next_586:;
    if ((i_24 < text_15.len)) goto next_587;
    match_158 = 0;
    goto end_match_585;
next_587:;
    exit(1);
end_match_585:;
    if ((!(match_158))) goto next_588;
    struct BoolIntTuple2 tuple_121;
    tuple_121.t0 = 1;
    tuple_121.t1 = (i_24 + 1);
    match_157 = tuple_121;
    goto end_match_584;
next_588:;
    if (match_158) goto next_589;
    struct BoolIntTuple2 match_159;
    int match_160;
    if ((i_24 >= text_15.len)) goto next_592;
    match_160 = (text_15.str[i_24] != '\n');
    goto end_match_591;
next_592:;
    if ((i_24 < text_15.len)) goto next_593;
    match_160 = 0;
    goto end_match_591;
next_593:;
    exit(1);
end_match_591:;
    if ((!(match_160))) goto next_594;
    struct BoolIntTuple2 call_365 = go_7(text_15, (i_24 + 1));
    match_159 = call_365;
    goto end_match_590;
next_594:;
    if (match_160) goto next_595;
    int match_161;
    if ((i_24 != text_15.len)) goto next_597;
    match_161 = 1;
    goto end_match_596;
next_597:;
    if ((i_24 == text_15.len)) goto next_598;
    match_161 = (text_15.str[i_24] == '\n');
    goto end_match_596;
next_598:;
    exit(1);
end_match_596:;
    milone_assert(match_161, 188, 6);
    int call_366 = 0;
    struct BoolIntTuple2 tuple_122;
    tuple_122.t0 = 0;
    tuple_122.t1 = i_24;
    match_159 = tuple_122;
    goto end_match_590;
next_595:;
    exit(1);
end_match_590:;
    match_157 = match_159;
    goto end_match_584;
next_589:;
    exit(1);
end_match_584:;
    match_155 = match_157;
    goto end_match_578;
next_583:;
    exit(1);
end_match_578:;
    return match_155;
}

struct BoolIntTuple2 scanCharLit_(struct String text_15, int i_23) {
    int call_367 = lookCharLit_(text_15, i_23);
    milone_assert(call_367, 175, 2);
    int call_368 = 0;
    struct BoolIntTuple2 call_369 = go_7(text_15, (i_23 + 1));
    return call_369;
}

int lookStrLit_(struct String text_16, int i_25) {
    return (text_16.str[i_25] == '\"');
}

struct BoolIntTuple2 go_8(struct String text_17, int i_27) {
    struct BoolIntTuple2 match_162;
    int match_163;
    if (((i_27 + 1) >= text_17.len)) goto next_601;
    match_163 = (text_17.str[i_27] == '\\');
    goto end_match_600;
next_601:;
    if (((i_27 + 1) < text_17.len)) goto next_602;
    match_163 = 0;
    goto end_match_600;
next_602:;
    exit(1);
end_match_600:;
    if ((!(match_163))) goto next_603;
    struct BoolIntTuple2 call_370 = go_8(text_17, (i_27 + 2));
    match_162 = call_370;
    goto end_match_599;
next_603:;
    if (match_163) goto next_604;
    struct BoolIntTuple2 match_164;
    int match_165;
    if ((i_27 >= text_17.len)) goto next_607;
    match_165 = (text_17.str[i_27] == '\"');
    goto end_match_606;
next_607:;
    if ((i_27 < text_17.len)) goto next_608;
    match_165 = 0;
    goto end_match_606;
next_608:;
    exit(1);
end_match_606:;
    if ((!(match_165))) goto next_609;
    struct BoolIntTuple2 tuple_123;
    tuple_123.t0 = 1;
    tuple_123.t1 = (i_27 + 1);
    match_164 = tuple_123;
    goto end_match_605;
next_609:;
    if (match_165) goto next_610;
    struct BoolIntTuple2 match_166;
    int match_167;
    if ((i_27 >= text_17.len)) goto next_613;
    match_167 = (text_17.str[i_27] != '\n');
    goto end_match_612;
next_613:;
    if ((i_27 < text_17.len)) goto next_614;
    match_167 = 0;
    goto end_match_612;
next_614:;
    exit(1);
end_match_612:;
    if ((!(match_167))) goto next_615;
    struct BoolIntTuple2 call_371 = go_8(text_17, (i_27 + 1));
    match_166 = call_371;
    goto end_match_611;
next_615:;
    if (match_167) goto next_616;
    int match_168;
    if ((i_27 != text_17.len)) goto next_618;
    match_168 = 1;
    goto end_match_617;
next_618:;
    if ((i_27 == text_17.len)) goto next_619;
    match_168 = (text_17.str[i_27] == '\n');
    goto end_match_617;
next_619:;
    exit(1);
end_match_617:;
    milone_assert(match_168, 209, 6);
    int call_372 = 0;
    struct BoolIntTuple2 tuple_124;
    tuple_124.t0 = 0;
    tuple_124.t1 = i_27;
    match_166 = tuple_124;
    goto end_match_611;
next_616:;
    exit(1);
end_match_611:;
    match_164 = match_166;
    goto end_match_605;
next_610:;
    exit(1);
end_match_605:;
    match_162 = match_164;
    goto end_match_599;
next_604:;
    exit(1);
end_match_599:;
    return match_162;
}

struct BoolIntTuple2 scanStrLit_(struct String text_17, int i_26) {
    int call_373 = lookStrLit_(text_17, i_26);
    milone_assert(call_373, 196, 2);
    int call_374 = 0;
    struct BoolIntTuple2 call_375 = go_8(text_17, (i_26 + 1));
    return call_375;
}

int lookStrLitRaw_(struct String text_18, int i_28) {
    int call_376 = strIsFollowedByRawQuotes_(i_28, text_18);
    return call_376;
}

struct BoolIntTuple2 go_9(struct String text_19, int i_30) {
    struct BoolIntTuple2 match_169;
    int call_377 = strIsFollowedByRawQuotes_(i_30, text_19);
    if ((!(call_377))) goto next_621;
    struct BoolIntTuple2 tuple_125;
    tuple_125.t0 = 1;
    tuple_125.t1 = (i_30 + 3);
    match_169 = tuple_125;
    goto end_match_620;
next_621:;
    if (call_377) goto next_622;
    struct BoolIntTuple2 match_170;
    if (((i_30 + 1) >= text_19.len)) goto next_624;
    struct BoolIntTuple2 call_378 = go_9(text_19, (i_30 + 1));
    match_170 = call_378;
    goto end_match_623;
next_624:;
    if (((i_30 + 1) < text_19.len)) goto next_625;
    milone_assert((i_30 == text_19.len), 224, 6);
    int call_379 = 0;
    struct BoolIntTuple2 tuple_126;
    tuple_126.t0 = 0;
    tuple_126.t1 = i_30;
    match_170 = tuple_126;
    goto end_match_623;
next_625:;
    exit(1);
end_match_623:;
    match_169 = match_170;
    goto end_match_620;
next_622:;
    exit(1);
end_match_620:;
    return match_169;
}

struct BoolIntTuple2 scanStrLitRaw_(struct String text_19, int i_29) {
    int call_380 = lookStrLitRaw_(text_19, i_29);
    milone_assert(call_380, 217, 2);
    int call_381 = 0;
    struct BoolIntTuple2 call_382 = go_9(text_19, (i_29 + 3));
    return call_382;
}

struct Token_ tokenFromIdent_(struct String text_20, int l_1, int r_1) {
    struct Token_ match_171;
    struct String call_383 = strSlice_(l_1, r_1, text_20);
    if ((str_cmp(call_383, (struct String){.str = "true", .len = 4}) != 0)) goto next_627;
    int* payload_69 = (int*)malloc(sizeof(int));
    (*(((int*)payload_69))) = 1;
    struct Token_ variant_69 = (struct Token_){.tag = Bool_1, .Bool_1 = payload_69};
    match_171 = variant_69;
    goto end_match_626;
next_627:;
    if ((str_cmp(call_383, (struct String){.str = "false", .len = 5}) != 0)) goto next_628;
    int* payload_70 = (int*)malloc(sizeof(int));
    (*(((int*)payload_70))) = 0;
    struct Token_ variant_70 = (struct Token_){.tag = Bool_1, .Bool_1 = payload_70};
    match_171 = variant_70;
    goto end_match_626;
next_628:;
    if ((str_cmp(call_383, (struct String){.str = "do", .len = 2}) != 0)) goto next_629;
    match_171 = (struct Token_){.tag = Do_};
    goto end_match_626;
next_629:;
    if ((str_cmp(call_383, (struct String){.str = "let", .len = 3}) != 0)) goto next_630;
    match_171 = (struct Token_){.tag = Let_};
    goto end_match_626;
next_630:;
    if ((str_cmp(call_383, (struct String){.str = "if", .len = 2}) != 0)) goto next_631;
    match_171 = (struct Token_){.tag = If_};
    goto end_match_626;
next_631:;
    if ((str_cmp(call_383, (struct String){.str = "then", .len = 4}) != 0)) goto next_632;
    match_171 = (struct Token_){.tag = Then_};
    goto end_match_626;
next_632:;
    if ((str_cmp(call_383, (struct String){.str = "else", .len = 4}) != 0)) goto next_633;
    match_171 = (struct Token_){.tag = Else_};
    goto end_match_626;
next_633:;
    if ((str_cmp(call_383, (struct String){.str = "match", .len = 5}) != 0)) goto next_634;
    match_171 = (struct Token_){.tag = Match_};
    goto end_match_626;
next_634:;
    if ((str_cmp(call_383, (struct String){.str = "with", .len = 4}) != 0)) goto next_635;
    match_171 = (struct Token_){.tag = With_};
    goto end_match_626;
next_635:;
    if ((str_cmp(call_383, (struct String){.str = "as", .len = 2}) != 0)) goto next_636;
    match_171 = (struct Token_){.tag = As_};
    goto end_match_626;
next_636:;
    if ((str_cmp(call_383, (struct String){.str = "when", .len = 4}) != 0)) goto next_637;
    match_171 = (struct Token_){.tag = When_};
    goto end_match_626;
next_637:;
    if ((str_cmp(call_383, (struct String){.str = "rec", .len = 3}) != 0)) goto next_638;
    match_171 = (struct Token_){.tag = Rec_};
    goto end_match_626;
next_638:;
    if ((str_cmp(call_383, (struct String){.str = "private", .len = 7}) != 0)) goto next_639;
    match_171 = (struct Token_){.tag = Private_};
    goto end_match_626;
next_639:;
    if ((str_cmp(call_383, (struct String){.str = "internal", .len = 8}) != 0)) goto next_640;
    match_171 = (struct Token_){.tag = Internal_};
    goto end_match_626;
next_640:;
    if ((str_cmp(call_383, (struct String){.str = "public", .len = 6}) != 0)) goto next_641;
    match_171 = (struct Token_){.tag = Public_};
    goto end_match_626;
next_641:;
    if ((str_cmp(call_383, (struct String){.str = "module", .len = 6}) != 0)) goto next_642;
    match_171 = (struct Token_){.tag = Module_};
    goto end_match_626;
next_642:;
    if ((str_cmp(call_383, (struct String){.str = "namespace", .len = 9}) != 0)) goto next_643;
    match_171 = (struct Token_){.tag = Namespace_};
    goto end_match_626;
next_643:;
    if ((str_cmp(call_383, (struct String){.str = "open", .len = 4}) != 0)) goto next_644;
    match_171 = (struct Token_){.tag = Open_};
    goto end_match_626;
next_644:;
    if ((str_cmp(call_383, (struct String){.str = "type", .len = 4}) != 0)) goto next_645;
    match_171 = (struct Token_){.tag = Type_};
    goto end_match_626;
next_645:;
    if ((str_cmp(call_383, (struct String){.str = "of", .len = 2}) != 0)) goto next_646;
    match_171 = (struct Token_){.tag = Of_};
    goto end_match_626;
next_646:;
    if ((str_cmp(call_383, (struct String){.str = "fun", .len = 3}) != 0)) goto next_647;
    match_171 = (struct Token_){.tag = Fun_};
    goto end_match_626;
next_647:;
    if ((str_cmp(call_383, (struct String){.str = "in", .len = 2}) != 0)) goto next_648;
    match_171 = (struct Token_){.tag = In_};
    goto end_match_626;
next_648:;
    struct String s_2 = call_383;
    struct String* payload_71 = (struct String*)malloc(sizeof(struct String));
    (*(((struct String*)payload_71))) = s_2;
    struct Token_ variant_71 = (struct Token_){.tag = Ident_, .Ident_ = payload_71};
    match_171 = variant_71;
    goto end_match_626;
next_649:;
end_match_626:;
    return match_171;
}

struct Token_ tokenFromOp_(struct String text_21, int l_2, int r_2) {
    struct Token_ match_172;
    struct String call_384 = strSlice_(l_2, r_2, text_21);
    if ((str_cmp(call_384, (struct String){.str = "&", .len = 1}) != 0)) goto next_651;
    match_172 = (struct Token_){.tag = Amp_};
    goto end_match_650;
next_651:;
    if ((str_cmp(call_384, (struct String){.str = "&&", .len = 2}) != 0)) goto next_652;
    match_172 = (struct Token_){.tag = AmpAmp_};
    goto end_match_650;
next_652:;
    if ((str_cmp(call_384, (struct String){.str = "->", .len = 2}) != 0)) goto next_653;
    match_172 = (struct Token_){.tag = Arrow_};
    goto end_match_650;
next_653:;
    if ((str_cmp(call_384, (struct String){.str = ":", .len = 1}) != 0)) goto next_654;
    match_172 = (struct Token_){.tag = Colon_};
    goto end_match_650;
next_654:;
    if ((str_cmp(call_384, (struct String){.str = "::", .len = 2}) != 0)) goto next_655;
    match_172 = (struct Token_){.tag = ColonColon_};
    goto end_match_650;
next_655:;
    if ((str_cmp(call_384, (struct String){.str = ".", .len = 1}) != 0)) goto next_656;
    match_172 = (struct Token_){.tag = Dot_};
    goto end_match_650;
next_656:;
    if ((str_cmp(call_384, (struct String){.str = "..", .len = 2}) != 0)) goto next_657;
    match_172 = (struct Token_){.tag = DotDot_};
    goto end_match_650;
next_657:;
    if ((str_cmp(call_384, (struct String){.str = "=", .len = 1}) != 0)) goto next_658;
    match_172 = (struct Token_){.tag = Eq_};
    goto end_match_650;
next_658:;
    if ((str_cmp(call_384, (struct String){.str = ">", .len = 1}) != 0)) goto next_659;
    match_172 = (struct Token_){.tag = Gt_};
    goto end_match_650;
next_659:;
    if ((str_cmp(call_384, (struct String){.str = ">=", .len = 2}) != 0)) goto next_660;
    match_172 = (struct Token_){.tag = GtEq_};
    goto end_match_650;
next_660:;
    if ((str_cmp(call_384, (struct String){.str = "<", .len = 1}) != 0)) goto next_661;
    match_172 = (struct Token_){.tag = Lt_};
    goto end_match_650;
next_661:;
    if ((str_cmp(call_384, (struct String){.str = "<=", .len = 2}) != 0)) goto next_662;
    match_172 = (struct Token_){.tag = LtEq_};
    goto end_match_650;
next_662:;
    if ((str_cmp(call_384, (struct String){.str = "<>", .len = 2}) != 0)) goto next_663;
    match_172 = (struct Token_){.tag = LtGt_};
    goto end_match_650;
next_663:;
    if ((str_cmp(call_384, (struct String){.str = "-", .len = 1}) != 0)) goto next_664;
    match_172 = (struct Token_){.tag = Minus_};
    goto end_match_650;
next_664:;
    if ((str_cmp(call_384, (struct String){.str = "%", .len = 1}) != 0)) goto next_665;
    match_172 = (struct Token_){.tag = Percent_};
    goto end_match_650;
next_665:;
    if ((str_cmp(call_384, (struct String){.str = "|", .len = 1}) != 0)) goto next_666;
    match_172 = (struct Token_){.tag = Pipe_};
    goto end_match_650;
next_666:;
    if ((str_cmp(call_384, (struct String){.str = "|>", .len = 2}) != 0)) goto next_667;
    match_172 = (struct Token_){.tag = PipeGt_};
    goto end_match_650;
next_667:;
    if ((str_cmp(call_384, (struct String){.str = "||", .len = 2}) != 0)) goto next_668;
    match_172 = (struct Token_){.tag = PipePipe_};
    goto end_match_650;
next_668:;
    if ((str_cmp(call_384, (struct String){.str = "+", .len = 1}) != 0)) goto next_669;
    match_172 = (struct Token_){.tag = Plus_};
    goto end_match_650;
next_669:;
    if ((str_cmp(call_384, (struct String){.str = ";", .len = 1}) != 0)) goto next_670;
    match_172 = (struct Token_){.tag = Semi_};
    goto end_match_650;
next_670:;
    if ((str_cmp(call_384, (struct String){.str = "*", .len = 1}) != 0)) goto next_671;
    match_172 = (struct Token_){.tag = Star_};
    goto end_match_650;
next_671:;
    if ((str_cmp(call_384, (struct String){.str = "/", .len = 1}) != 0)) goto next_672;
    match_172 = (struct Token_){.tag = Slash_};
    goto end_match_650;
next_672:;
    match_172 = (struct Token_){.tag = Error_};
    goto end_match_650;
next_673:;
end_match_650:;
    return match_172;
}

struct Token_ tokenFromPun_(struct String text_22, int l_3, int r_3) {
    milone_assert(((r_3 - l_3) == 1), 331, 2);
    int call_385 = 0;
    struct Token_ match_173;
    if ((text_22.str[l_3] != ',')) goto next_675;
    match_173 = (struct Token_){.tag = Comma_};
    goto end_match_674;
next_675:;
    if ((text_22.str[l_3] != '(')) goto next_676;
    match_173 = (struct Token_){.tag = ParenL_};
    goto end_match_674;
next_676:;
    if ((text_22.str[l_3] != ')')) goto next_677;
    match_173 = (struct Token_){.tag = ParenR_};
    goto end_match_674;
next_677:;
    if ((text_22.str[l_3] != '[')) goto next_678;
    match_173 = (struct Token_){.tag = BracketL_};
    goto end_match_674;
next_678:;
    if ((text_22.str[l_3] != ']')) goto next_679;
    match_173 = (struct Token_){.tag = BracketR_};
    goto end_match_674;
next_679:;
    struct Token_ call_386 = failwith_1((struct String){.str = "NEVER! charIsPun is broken", .len = 26});
    match_173 = call_386;
    goto end_match_674;
next_680:;
end_match_674:;
    return match_173;
}

struct Token_ tokenFromIntLit_(struct String text_23, int l_4, int r_4) {
    struct String call_387 = strSlice_(l_4, r_4, text_23);
    int call_388 = str_to_int(call_387);
    int value_ = call_388;
    int* payload_72 = (int*)malloc(sizeof(int));
    (*(((int*)payload_72))) = value_;
    struct Token_ variant_72 = (struct Token_){.tag = Int_1, .Int_1 = payload_72};
    return variant_72;
}

struct Token_ tokenFromCharLit_(char charNull_, struct String text_24, int l_5, int r_5) {
    int match_174;
    int match_175;
    if ((r_5 < (l_5 + 2))) goto next_683;
    match_175 = (text_24.str[l_5] == '\'');
    goto end_match_682;
next_683:;
    if ((r_5 >= (l_5 + 2))) goto next_684;
    match_175 = 0;
    goto end_match_682;
next_684:;
    exit(1);
end_match_682:;
    if ((!(match_175))) goto next_685;
    match_174 = (text_24.str[(r_5 - 1)] == '\'');
    goto end_match_681;
next_685:;
    if (match_175) goto next_686;
    match_174 = 0;
    goto end_match_681;
next_686:;
    exit(1);
end_match_681:;
    milone_assert(match_174, 351, 2);
    int call_389 = 0;
    int i_31 = (l_5 + 1);
    char match_176;
    if ((text_24.str[i_31] != '\\')) goto next_688;
    char match_177;
    if ((text_24.str[(i_31 + 1)] != 'x')) goto next_691;
    match_177 = charNull_;
    goto end_match_690;
next_691:;
    if ((text_24.str[(i_31 + 1)] != 't')) goto next_692;
    match_177 = '\t';
    goto end_match_690;
next_692:;
    if ((text_24.str[(i_31 + 1)] != 'r')) goto next_693;
    match_177 = '\r';
    goto end_match_690;
next_693:;
    if ((text_24.str[(i_31 + 1)] != 'n')) goto next_694;
    match_177 = '\n';
    goto end_match_690;
next_694:;
    char c_3 = text_24.str[(i_31 + 1)];
    match_177 = c_3;
    goto end_match_690;
next_695:;
end_match_690:;
    match_176 = match_177;
    goto end_match_687;
next_688:;
    char c_4 = text_24.str[i_31];
    match_176 = c_4;
    goto end_match_687;
next_689:;
end_match_687:;
    char value_1 = match_176;
    char* payload_73 = (char*)malloc(sizeof(char));
    (*(((char*)payload_73))) = value_1;
    struct Token_ variant_73 = (struct Token_){.tag = Char_1, .Char_1 = payload_73};
    return variant_73;
}

int next_(int r_6, struct String text_25, int i_33) {
    int match_178;
    int match_179;
    if ((i_33 != (r_6 - 1))) goto next_698;
    match_179 = 1;
    goto end_match_697;
next_698:;
    if ((i_33 == (r_6 - 1))) goto next_699;
    match_179 = (text_25.str[i_33] == '\\');
    goto end_match_697;
next_699:;
    exit(1);
end_match_697:;
    if ((!(match_179))) goto next_700;
    match_178 = i_33;
    goto end_match_696;
next_700:;
    if (match_179) goto next_701;
    int call_390 = next_(r_6, text_25, (i_33 + 1));
    match_178 = call_390;
    goto end_match_696;
next_701:;
    exit(1);
end_match_696:;
    return match_178;
}

struct String go_10(int r_6, struct String text_25, struct StringList* acc_, int i_32) {
    int call_391 = next_(r_6, text_25, i_32);
    int endIndex_ = call_391;
    struct String call_392 = strSlice_(i_32, endIndex_, text_25);
    struct StringList* list_55 = (struct StringList*)malloc(sizeof(struct StringList));
    list_55->head = call_392;
    list_55->tail = acc_;
    struct StringList* acc_1 = list_55;
    int i_34 = endIndex_;
    struct String match_180;
    if ((i_34 != (r_6 - 1))) goto next_703;
    struct StringList* call_393 = listRev_3(acc_1);
    struct String call_394 = strConcat_(call_393);
    match_180 = call_394;
    goto end_match_702;
next_703:;
    if ((i_34 == (r_6 - 1))) goto next_704;
    milone_assert((text_25.str[i_34] == '\\'), 394, 6);
    int call_395 = 0;
    struct String match_181;
    if ((text_25.str[(i_34 + 1)] != 'x')) goto next_706;
    struct StringList* list_56 = (struct StringList*)malloc(sizeof(struct StringList));
    list_56->head = (struct String){.str = "\0", .len = 1};
    list_56->tail = acc_1;
    struct String call_396 = go_10(r_6, text_25, list_56, (i_34 + 4));
    match_181 = call_396;
    goto end_match_705;
next_706:;
    if ((text_25.str[(i_34 + 1)] != 't')) goto next_707;
    struct StringList* list_57 = (struct StringList*)malloc(sizeof(struct StringList));
    list_57->head = (struct String){.str = "\t", .len = 1};
    list_57->tail = acc_1;
    struct String call_397 = go_10(r_6, text_25, list_57, (i_34 + 2));
    match_181 = call_397;
    goto end_match_705;
next_707:;
    if ((text_25.str[(i_34 + 1)] != 'r')) goto next_708;
    struct StringList* list_58 = (struct StringList*)malloc(sizeof(struct StringList));
    list_58->head = (struct String){.str = "\r", .len = 1};
    list_58->tail = acc_1;
    struct String call_398 = go_10(r_6, text_25, list_58, (i_34 + 2));
    match_181 = call_398;
    goto end_match_705;
next_708:;
    if ((text_25.str[(i_34 + 1)] != 'n')) goto next_709;
    struct StringList* list_59 = (struct StringList*)malloc(sizeof(struct StringList));
    list_59->head = (struct String){.str = "\n", .len = 1};
    list_59->tail = acc_1;
    struct String call_399 = go_10(r_6, text_25, list_59, (i_34 + 2));
    match_181 = call_399;
    goto end_match_705;
next_709:;
    struct String call_400 = strSlice_((i_34 + 1), (i_34 + 2), text_25);
    struct StringList* list_60 = (struct StringList*)malloc(sizeof(struct StringList));
    list_60->head = call_400;
    list_60->tail = acc_1;
    struct String call_401 = go_10(r_6, text_25, list_60, (i_34 + 2));
    match_181 = call_401;
    goto end_match_705;
next_710:;
end_match_705:;
    match_180 = match_181;
    goto end_match_702;
next_704:;
    exit(1);
end_match_702:;
    return match_180;
}

struct Token_ tokenFromStrLit_(struct String text_25, int l_6, int r_6) {
    int match_182;
    int match_183;
    if ((r_6 < (l_6 + 2))) goto next_713;
    match_183 = (text_25.str[l_6] == '\"');
    goto end_match_712;
next_713:;
    if ((r_6 >= (l_6 + 2))) goto next_714;
    match_183 = 0;
    goto end_match_712;
next_714:;
    exit(1);
end_match_712:;
    if ((!(match_183))) goto next_715;
    match_182 = (text_25.str[(r_6 - 1)] == '\"');
    goto end_match_711;
next_715:;
    if (match_183) goto next_716;
    match_182 = 0;
    goto end_match_711;
next_716:;
    exit(1);
end_match_711:;
    milone_assert(match_182, 375, 2);
    int call_402 = 0;
    struct String call_403 = go_10(r_6, text_25, NULL, (l_6 + 1));
    struct String value_2 = call_403;
    struct String* payload_74 = (struct String*)malloc(sizeof(struct String));
    (*(((struct String*)payload_74))) = value_2;
    struct Token_ variant_74 = (struct Token_){.tag = Str_1, .Str_1 = payload_74};
    return variant_74;
}

struct Token_ tokenFromStrLitRaw_(struct String text_26, int l_7, int r_7) {
    int match_184;
    int match_185;
    if ((r_7 < (l_7 + 6))) goto next_719;
    int call_404 = strIsFollowedByRawQuotes_(l_7, text_26);
    match_185 = call_404;
    goto end_match_718;
next_719:;
    if ((r_7 >= (l_7 + 6))) goto next_720;
    match_185 = 0;
    goto end_match_718;
next_720:;
    exit(1);
end_match_718:;
    if ((!(match_185))) goto next_721;
    int call_405 = strIsFollowedByRawQuotes_((r_7 - 3), text_26);
    match_184 = call_405;
    goto end_match_717;
next_721:;
    if (match_185) goto next_722;
    match_184 = 0;
    goto end_match_717;
next_722:;
    exit(1);
end_match_717:;
    milone_assert(match_184, 411, 2);
    int call_406 = 0;
    struct String call_407 = strSlice_((l_7 + 3), (r_7 - 3), text_26);
    struct String* payload_75 = (struct String*)malloc(sizeof(struct String));
    (*(((struct String*)payload_75))) = call_407;
    struct Token_ variant_75 = (struct Token_){.tag = Str_1, .Str_1 = payload_75};
    return variant_75;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 {
    struct String t0;
    int t1;
    struct IntIntTuple2 t2;
    struct Token_IntIntTuple2Tuple2List* t3;
};

struct StringIntTuple2 {
    struct String t0;
    int t1;
};

struct StringIntTuple2 tokCtxToTextIndex_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 arg_146) {
    struct String text_27 = arg_146.t0;
    int i_35 = arg_146.t1;
    struct StringIntTuple2 tuple_127;
    tuple_127.t0 = text_27;
    tuple_127.t1 = i_35;
    return tuple_127;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokCtxSkip_(int r_8, struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 arg_147) {
    struct String text_28 = arg_147.t0;
    int i_36 = arg_147.t1;
    struct IntIntTuple2 loc_ = arg_147.t2;
    struct Token_IntIntTuple2Tuple2List* acc_2 = arg_147.t3;
    int match_186;
    int match_187;
    if ((i_36 < 0)) goto next_725;
    match_187 = (r_8 >= i_36);
    goto end_match_724;
next_725:;
    if ((i_36 >= 0)) goto next_726;
    match_187 = 0;
    goto end_match_724;
next_726:;
    exit(1);
end_match_724:;
    if ((!(match_187))) goto next_727;
    match_186 = (text_28.len >= r_8);
    goto end_match_723;
next_727:;
    if (match_187) goto next_728;
    match_186 = 0;
    goto end_match_723;
next_728:;
    exit(1);
end_match_723:;
    milone_assert(match_186, 424, 2);
    int call_408 = 0;
    struct IntIntTuple2 call_409 = locShift_(text_28, i_36, r_8, loc_);
    struct IntIntTuple2 newLoc_ = call_409;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tuple_128;
    tuple_128.t0 = text_28;
    tuple_128.t1 = r_8;
    tuple_128.t2 = newLoc_;
    tuple_128.t3 = acc_2;
    return tuple_128;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokCtxPush_(struct Token_ kind_, int r_9, struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 arg_148) {
    struct String text_29 = arg_148.t0;
    int i_37 = arg_148.t1;
    struct IntIntTuple2 loc_1 = arg_148.t2;
    struct Token_IntIntTuple2Tuple2List* acc_3 = arg_148.t3;
    int match_188;
    int match_189;
    if ((i_37 < 0)) goto next_731;
    match_189 = (r_9 >= i_37);
    goto end_match_730;
next_731:;
    if ((i_37 >= 0)) goto next_732;
    match_189 = 0;
    goto end_match_730;
next_732:;
    exit(1);
end_match_730:;
    if ((!(match_189))) goto next_733;
    match_188 = (text_29.len >= r_9);
    goto end_match_729;
next_733:;
    if (match_189) goto next_734;
    match_188 = 0;
    goto end_match_729;
next_734:;
    exit(1);
end_match_729:;
    milone_assert(match_188, 431, 2);
    int call_410 = 0;
    struct Token_IntIntTuple2Tuple2 tuple_129;
    tuple_129.t0 = kind_;
    tuple_129.t1 = loc_1;
    struct Token_IntIntTuple2Tuple2List* list_61 = (struct Token_IntIntTuple2Tuple2List*)malloc(sizeof(struct Token_IntIntTuple2Tuple2List));
    list_61->head = tuple_129;
    list_61->tail = acc_3;
    struct Token_IntIntTuple2Tuple2List* newAcc_ = list_61;
    struct IntIntTuple2 call_411 = locShift_(text_29, i_37, r_9, loc_1);
    struct IntIntTuple2 newLoc_1 = call_411;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tuple_130;
    tuple_130.t0 = text_29;
    tuple_130.t1 = r_9;
    tuple_130.t2 = newLoc_1;
    tuple_130.t3 = newAcc_;
    return tuple_130;
}

struct Token_IntIntTuple2Tuple2List* tokEof_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 arg_149) {
    struct String text_30 = arg_149.t0;
    int i_38 = arg_149.t1;
    struct Token_IntIntTuple2Tuple2List* acc_4 = arg_149.t3;
    int call_412 = lookEof_(text_30, i_38);
    milone_assert(call_412, 437, 2);
    int call_413 = 0;
    struct Token_IntIntTuple2Tuple2List* call_414 = listRev_8(acc_4);
    return call_414;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokError_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_) {
    struct StringIntTuple2 call_415 = tokCtxToTextIndex_(t_);
    struct String text_31 = call_415.t0;
    int i_39 = call_415.t1;
    int call_416 = scanError_(text_31, i_39);
    int r_10 = call_416;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_417 = tokCtxSkip_(r_10, t_);
    return call_417;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokComment_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_1) {
    struct StringIntTuple2 call_418 = tokCtxToTextIndex_(t_1);
    struct String text_32 = call_418.t0;
    int i_40 = call_418.t1;
    int call_419 = scanLine_(text_32, i_40);
    int r_11 = call_419;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_420 = tokCtxSkip_(r_11, t_1);
    return call_420;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokSpace_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_2) {
    struct StringIntTuple2 call_421 = tokCtxToTextIndex_(t_2);
    struct String text_33 = call_421.t0;
    int i_41 = call_421.t1;
    int call_422 = scanSpace_(text_33, i_41);
    int r_12 = call_422;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_423 = tokCtxSkip_(r_12, t_2);
    return call_423;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokPun_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_3) {
    struct StringIntTuple2 call_424 = tokCtxToTextIndex_(t_3);
    struct String text_34 = call_424.t0;
    int i_42 = call_424.t1;
    int call_425 = scanPun_(text_34, i_42);
    int r_13 = call_425;
    struct Token_ call_426 = tokenFromPun_(text_34, i_42, r_13);
    struct Token_ token_ = call_426;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_427 = tokCtxPush_(token_, r_13, t_3);
    return call_427;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokOp_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_4) {
    struct StringIntTuple2 call_428 = tokCtxToTextIndex_(t_4);
    struct String text_35 = call_428.t0;
    int i_43 = call_428.t1;
    int call_429 = scanOp_(text_35, i_43);
    int r_14 = call_429;
    struct Token_ call_430 = tokenFromOp_(text_35, i_43, r_14);
    struct Token_ token_1 = call_430;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_431 = tokCtxPush_(token_1, r_14, t_4);
    return call_431;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokIdent_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_5) {
    struct StringIntTuple2 call_432 = tokCtxToTextIndex_(t_5);
    struct String text_36 = call_432.t0;
    int i_44 = call_432.t1;
    int call_433 = scanIdent_(text_36, i_44);
    int r_15 = call_433;
    struct Token_ call_434 = tokenFromIdent_(text_36, i_44, r_15);
    struct Token_ token_2 = call_434;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_435 = tokCtxPush_(token_2, r_15, t_5);
    return call_435;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokIntLit_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_6) {
    struct StringIntTuple2 call_436 = tokCtxToTextIndex_(t_6);
    struct String text_37 = call_436.t0;
    int i_45 = call_436.t1;
    int call_437 = scanIntLit_(text_37, i_45);
    int r_16 = call_437;
    struct Token_ call_438 = tokenFromIntLit_(text_37, i_45, r_16);
    struct Token_ token_3 = call_438;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_439 = tokCtxPush_(token_3, r_16, t_6);
    return call_439;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokCharLit_(char charNull_, struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_7) {
    struct StringIntTuple2 call_440 = tokCtxToTextIndex_(t_7);
    struct String text_38 = call_440.t0;
    int i_46 = call_440.t1;
    struct BoolIntTuple2 call_441 = scanCharLit_(text_38, i_46);
    int ok_ = call_441.t0;
    int r_17 = call_441.t1;
    struct Token_ match_190;
    if ((!(ok_))) goto next_736;
    struct Token_ call_442 = tokenFromCharLit_(charNull_, text_38, i_46, r_17);
    match_190 = call_442;
    goto end_match_735;
next_736:;
    if (ok_) goto next_737;
    match_190 = (struct Token_){.tag = Error_};
    goto end_match_735;
next_737:;
    exit(1);
end_match_735:;
    struct Token_ token_4 = match_190;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_443 = tokCtxPush_(token_4, r_17, t_7);
    return call_443;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokStrLit_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_8) {
    struct StringIntTuple2 call_444 = tokCtxToTextIndex_(t_8);
    struct String text_39 = call_444.t0;
    int i_47 = call_444.t1;
    struct BoolIntTuple2 call_445 = scanStrLit_(text_39, i_47);
    int ok_1 = call_445.t0;
    int r_18 = call_445.t1;
    struct Token_ match_191;
    if ((!(ok_1))) goto next_739;
    struct Token_ call_446 = tokenFromStrLit_(text_39, i_47, r_18);
    match_191 = call_446;
    goto end_match_738;
next_739:;
    if (ok_1) goto next_740;
    match_191 = (struct Token_){.tag = Error_};
    goto end_match_738;
next_740:;
    exit(1);
end_match_738:;
    struct Token_ token_5 = match_191;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_447 = tokCtxPush_(token_5, r_18, t_8);
    return call_447;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokStrLitRaw_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_9) {
    struct StringIntTuple2 call_448 = tokCtxToTextIndex_(t_9);
    struct String text_40 = call_448.t0;
    int i_48 = call_448.t1;
    struct BoolIntTuple2 call_449 = scanStrLitRaw_(text_40, i_48);
    int ok_2 = call_449.t0;
    int r_19 = call_449.t1;
    struct Token_ match_192;
    if ((!(ok_2))) goto next_742;
    struct Token_ call_450 = tokenFromStrLitRaw_(text_40, i_48, r_19);
    match_192 = call_450;
    goto end_match_741;
next_742:;
    if (ok_2) goto next_743;
    match_192 = (struct Token_){.tag = Error_};
    goto end_match_741;
next_743:;
    exit(1);
end_match_741:;
    struct Token_ token_6 = match_192;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_451 = tokCtxPush_(token_6, r_19, t_9);
    return call_451;
}

struct Token_IntIntTuple2Tuple2List* go_11(char charNull_, struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_10) {
    struct StringIntTuple2 call_452 = tokCtxToTextIndex_(t_10);
    struct String text_42 = call_452.t0;
    int i_49 = call_452.t1;
    struct Token_IntIntTuple2Tuple2List* match_193;
    int call_453 = lookEof_(text_42, i_49);
    if ((!(call_453))) goto next_745;
    struct Token_IntIntTuple2Tuple2List* call_454 = tokEof_(t_10);
    match_193 = call_454;
    goto end_match_744;
next_745:;
    if (call_453) goto next_746;
    struct Token_IntIntTuple2Tuple2List* match_194;
    int call_455 = lookComment_(text_42, i_49);
    if ((!(call_455))) goto next_748;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_456 = tokComment_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_457 = go_11(charNull_, call_456);
    match_194 = call_457;
    goto end_match_747;
next_748:;
    if (call_455) goto next_749;
    struct Token_IntIntTuple2Tuple2List* match_195;
    int call_458 = lookSpace_(text_42, i_49);
    if ((!(call_458))) goto next_751;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_459 = tokSpace_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_460 = go_11(charNull_, call_459);
    match_195 = call_460;
    goto end_match_750;
next_751:;
    if (call_458) goto next_752;
    struct Token_IntIntTuple2Tuple2List* match_196;
    int call_461 = lookOp_(text_42, i_49);
    if ((!(call_461))) goto next_754;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_462 = tokOp_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_463 = go_11(charNull_, call_462);
    match_196 = call_463;
    goto end_match_753;
next_754:;
    if (call_461) goto next_755;
    struct Token_IntIntTuple2Tuple2List* match_197;
    int call_464 = lookIntLit_(text_42, i_49);
    if ((!(call_464))) goto next_757;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_465 = tokIntLit_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_466 = go_11(charNull_, call_465);
    match_197 = call_466;
    goto end_match_756;
next_757:;
    if (call_464) goto next_758;
    struct Token_IntIntTuple2Tuple2List* match_198;
    int call_467 = lookIdent_(text_42, i_49);
    if ((!(call_467))) goto next_760;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_468 = tokIdent_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_469 = go_11(charNull_, call_468);
    match_198 = call_469;
    goto end_match_759;
next_760:;
    if (call_467) goto next_761;
    struct Token_IntIntTuple2Tuple2List* match_199;
    int call_470 = lookCharLit_(text_42, i_49);
    if ((!(call_470))) goto next_763;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_471 = tokCharLit_(charNull_, t_10);
    struct Token_IntIntTuple2Tuple2List* call_472 = go_11(charNull_, call_471);
    match_199 = call_472;
    goto end_match_762;
next_763:;
    if (call_470) goto next_764;
    struct Token_IntIntTuple2Tuple2List* match_200;
    int call_473 = lookStrLitRaw_(text_42, i_49);
    if ((!(call_473))) goto next_766;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_474 = tokStrLitRaw_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_475 = go_11(charNull_, call_474);
    match_200 = call_475;
    goto end_match_765;
next_766:;
    if (call_473) goto next_767;
    struct Token_IntIntTuple2Tuple2List* match_201;
    int call_476 = lookStrLit_(text_42, i_49);
    if ((!(call_476))) goto next_769;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_477 = tokStrLit_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_478 = go_11(charNull_, call_477);
    match_201 = call_478;
    goto end_match_768;
next_769:;
    if (call_476) goto next_770;
    struct Token_IntIntTuple2Tuple2List* match_202;
    int call_479 = lookPun_(text_42, i_49);
    if ((!(call_479))) goto next_772;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_480 = tokPun_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_481 = go_11(charNull_, call_480);
    match_202 = call_481;
    goto end_match_771;
next_772:;
    if (call_479) goto next_773;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_482 = tokError_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_483 = go_11(charNull_, call_482);
    match_202 = call_483;
    goto end_match_771;
next_773:;
    exit(1);
end_match_771:;
    match_201 = match_202;
    goto end_match_768;
next_770:;
    exit(1);
end_match_768:;
    match_200 = match_201;
    goto end_match_765;
next_767:;
    exit(1);
end_match_765:;
    match_199 = match_200;
    goto end_match_762;
next_764:;
    exit(1);
end_match_762:;
    match_198 = match_199;
    goto end_match_759;
next_761:;
    exit(1);
end_match_759:;
    match_197 = match_198;
    goto end_match_756;
next_758:;
    exit(1);
end_match_756:;
    match_196 = match_197;
    goto end_match_753;
next_755:;
    exit(1);
end_match_753:;
    match_195 = match_196;
    goto end_match_750;
next_752:;
    exit(1);
end_match_750:;
    match_194 = match_195;
    goto end_match_747;
next_749:;
    exit(1);
end_match_747:;
    match_193 = match_194;
    goto end_match_744;
next_746:;
    exit(1);
end_match_744:;
    return match_193;
}

struct Token_IntIntTuple2Tuple2List* tokenize_(char charNull_, struct String text_41) {
    struct IntIntTuple2 tuple_132;
    tuple_132.t0 = 0;
    tuple_132.t1 = 0;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tuple_131;
    tuple_131.t0 = text_41;
    tuple_131.t1 = 0;
    tuple_131.t2 = tuple_132;
    tuple_131.t3 = NULL;
    struct Token_IntIntTuple2Tuple2List* call_484 = go_11(charNull_, tuple_131);
    return call_484;
}

int leadsExpr_1(struct Token_IntIntTuple2Tuple2List* tokens_) {
    int match_203;
    if ((!(tokens_))) goto next_775;
    struct Token_ token_13 = tokens_->head.t0;
    int call_485 = tokenIsExprFirst_(token_13);
    match_203 = call_485;
    goto end_match_774;
next_775:;
    match_203 = 0;
    goto end_match_774;
next_776:;
end_match_774:;
    return match_203;
}

int leadsArg_1(struct Token_IntIntTuple2Tuple2List* tokens_1) {
    int match_204;
    if ((!(tokens_1))) goto next_778;
    struct Token_ token_14 = tokens_1->head.t0;
    int call_486 = tokenIsArgFirst_(token_14);
    match_204 = call_486;
    goto end_match_777;
next_778:;
    match_204 = 0;
    goto end_match_777;
next_779:;
end_match_777:;
    return match_204;
}

int leadsPat_1(struct Token_IntIntTuple2Tuple2List* tokens_2) {
    int match_205;
    if ((!(tokens_2))) goto next_781;
    struct Token_ token_15 = tokens_2->head.t0;
    int call_487 = tokenIsPatFirst_(token_15);
    match_205 = call_487;
    goto end_match_780;
next_781:;
    match_205 = 0;
    goto end_match_780;
next_782:;
end_match_780:;
    return match_205;
}

struct IntIntTuple2 nextLoc_1(struct Token_IntIntTuple2Tuple2List* tokens_3) {
    struct IntIntTuple2 match_206;
    if ((!((!(tokens_3))))) goto next_784;
    struct IntIntTuple2 tuple_133;
    tuple_133.t0 = (0 - 1);
    tuple_133.t1 = 0;
    match_206 = tuple_133;
    goto end_match_783;
next_784:;
    if ((!(tokens_3))) goto next_785;
    struct IntIntTuple2 loc_28 = tokens_3->head.t1;
    match_206 = loc_28;
    goto end_match_783;
next_785:;
    exit(1);
end_match_783:;
    return match_206;
}

int nextInside_1(struct IntIntTuple2 baseLoc_, struct Token_IntIntTuple2Tuple2List* tokens_4) {
    int match_207;
    if ((!((!(tokens_4))))) goto next_787;
    match_207 = 0;
    goto end_match_786;
next_787:;
    if ((!(tokens_4))) goto next_788;
    struct IntIntTuple2 loc_29 = tokens_4->head.t1;
    int call_488 = locInside_(baseLoc_, loc_29);
    if ((!(call_488))) goto next_788;
    match_207 = 1;
    goto end_match_786;
next_788:;
    match_207 = 0;
    goto end_match_786;
next_789:;
end_match_786:;
    return match_207;
}

struct StringIntIntTuple2Tuple2List* parseErrorCore_(struct String msg_3, struct IntIntTuple2 loc_30, struct StringIntIntTuple2Tuple2List* errors_1) {
    struct String call_489 = locToString_(loc_30);
    struct String msg_4 = str_add(str_add(str_add(str_add((struct String){.str = "PARSE ERROR: ", .len = 13}, msg_3), (struct String){.str = " (", .len = 2}), call_489), (struct String){.str = ")", .len = 1});
    struct StringIntIntTuple2Tuple2 tuple_134;
    tuple_134.t0 = msg_4;
    tuple_134.t1 = loc_30;
    struct StringIntIntTuple2Tuple2List* list_62 = (struct StringIntIntTuple2Tuple2List*)malloc(sizeof(struct StringIntIntTuple2Tuple2List));
    list_62->head = tuple_134;
    list_62->tail = errors_1;
    return list_62;
}

struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 {
    struct Token_IntIntTuple2Tuple2List* t0;
    struct StringIntIntTuple2Tuple2List* t1;
};

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct ATy_ t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyError_1(struct String msg_5, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_150) {
    struct Token_IntIntTuple2Tuple2List* tokens_5 = arg_150.t0;
    struct StringIntIntTuple2Tuple2List* errors_2 = arg_150.t1;
    struct IntIntTuple2 call_490 = nextLoc_1(tokens_5);
    struct IntIntTuple2 loc_31 = call_490;
    struct StringIntIntTuple2Tuple2List* call_491 = parseErrorCore_(msg_5, loc_31, errors_2);
    struct StringIntIntTuple2Tuple2List* errors_3 = call_491;
    struct IntIntTuple2* payload_76 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_76))) = loc_31;
    struct ATy_ variant_76 = (struct ATy_){.tag = Missing_, .Missing_ = payload_76};
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_135;
    tuple_135.t0 = variant_76;
    tuple_135.t1 = tokens_5;
    tuple_135.t2 = errors_3;
    return tuple_135;
}

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct APat_ t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatError_1(struct String msg_6, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_151) {
    struct Token_IntIntTuple2Tuple2List* tokens_6 = arg_151.t0;
    struct StringIntIntTuple2Tuple2List* errors_4 = arg_151.t1;
    struct IntIntTuple2 call_492 = nextLoc_1(tokens_6);
    struct IntIntTuple2 loc_32 = call_492;
    struct StringIntIntTuple2Tuple2List* call_493 = parseErrorCore_(msg_6, loc_32, errors_4);
    struct StringIntIntTuple2Tuple2List* errors_5 = call_493;
    struct IntIntTuple2* payload_77 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_77))) = loc_32;
    struct APat_ variant_77 = (struct APat_){.tag = Missing_1, .Missing_1 = payload_77};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_136;
    tuple_136.t0 = variant_77;
    tuple_136.t1 = tokens_6;
    tuple_136.t2 = errors_5;
    return tuple_136;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct AExpr_ t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseExprError_1(struct String msg_7, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_152) {
    struct Token_IntIntTuple2Tuple2List* tokens_7 = arg_152.t0;
    struct StringIntIntTuple2Tuple2List* errors_6 = arg_152.t1;
    struct IntIntTuple2 call_494 = nextLoc_1(tokens_7);
    struct IntIntTuple2 loc_33 = call_494;
    struct StringIntIntTuple2Tuple2List* call_495 = parseErrorCore_(msg_7, loc_33, errors_6);
    struct StringIntIntTuple2Tuple2List* errors_7 = call_495;
    struct IntIntTuple2* payload_78 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_78))) = loc_33;
    struct AExpr_ variant_78 = (struct AExpr_){.tag = Missing_2, .Missing_2 = payload_78};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_137;
    tuple_137.t0 = variant_78;
    tuple_137.t1 = tokens_7;
    tuple_137.t2 = errors_7;
    return tuple_137;
}

struct StringIntIntTuple2Tuple2List* parseNewError_1(struct String msg_8, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_153) {
    struct Token_IntIntTuple2Tuple2List* tokens_8 = arg_153.t0;
    struct StringIntIntTuple2Tuple2List* errors_8 = arg_153.t1;
    struct IntIntTuple2 call_496 = nextLoc_1(tokens_8);
    struct IntIntTuple2 loc_34 = call_496;
    struct StringIntIntTuple2Tuple2List* call_497 = parseErrorCore_(msg_8, loc_34, errors_8);
    return call_497;
}

struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct ATy_List* t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_40(struct IntIntTuple2 baseLoc_1, struct ATy_List* acc_25, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_154) {
    struct Token_IntIntTuple2Tuple2List* tokens_11 = arg_154.t0;
    struct StringIntIntTuple2Tuple2List* errors_10 = arg_154.t1;
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_208;
    if ((!(tokens_11))) goto next_791;
    if ((tokens_11->head.t0.tag != Comma_)) goto next_791;
    struct Token_IntIntTuple2Tuple2List* tokens_12 = tokens_11->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_138;
    tuple_138.t0 = tokens_12;
    tuple_138.t1 = errors_10;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_498 = parseTy_(baseLoc_1, tuple_138);
    struct ATy_ argTy_ = call_498.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_13 = call_498.t1;
    struct StringIntIntTuple2Tuple2List* errors_11 = call_498.t2;
    struct ATy_List* list_63 = (struct ATy_List*)malloc(sizeof(struct ATy_List));
    list_63->head = argTy_;
    list_63->tail = acc_25;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_139;
    tuple_139.t0 = tokens_13;
    tuple_139.t1 = errors_11;
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_499 = go_40(baseLoc_1, list_63, tuple_139);
    match_208 = call_499;
    goto end_match_790;
next_791:;
    struct ATy_List* call_500 = listRev_7(acc_25);
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_140;
    tuple_140.t0 = call_500;
    tuple_140.t1 = tokens_11;
    tuple_140.t2 = errors_10;
    match_208 = tuple_140;
    goto end_match_790;
next_792:;
end_match_790:;
    return match_208;
}

struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyArgs_(struct IntIntTuple2 baseLoc_1, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_155) {
    struct Token_IntIntTuple2Tuple2List* tokens_9 = arg_155.t0;
    struct StringIntIntTuple2Tuple2List* errors_9 = arg_155.t1;
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_209;
    if ((!(tokens_9))) goto next_794;
    if ((tokens_9->head.t0.tag != Lt_)) goto next_794;
    struct IntIntTuple2 ltLoc_ = tokens_9->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_10 = tokens_9->tail;
    int call_501 = locInside_(baseLoc_1, ltLoc_);
    if ((!(call_501))) goto next_794;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_141;
    tuple_141.t0 = tokens_10;
    tuple_141.t1 = errors_9;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_502 = parseTy_(baseLoc_1, tuple_141);
    struct ATy_ argTy_1 = call_502.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_14 = call_502.t1;
    struct StringIntIntTuple2Tuple2List* errors_12 = call_502.t2;
    struct ATy_List* list_64 = (struct ATy_List*)malloc(sizeof(struct ATy_List));
    list_64->head = argTy_1;
    list_64->tail = NULL;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_142;
    tuple_142.t0 = tokens_14;
    tuple_142.t1 = errors_12;
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_503 = go_40(baseLoc_1, list_64, tuple_142);
    struct ATy_List* argTys_ = call_503.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_15 = call_503.t1;
    struct StringIntIntTuple2Tuple2List* errors_13 = call_503.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 match_210;
    if ((!(tokens_15))) goto next_797;
    if ((tokens_15->head.t0.tag != Gt_)) goto next_797;
    struct Token_IntIntTuple2Tuple2List* tokens_17 = tokens_15->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_143;
    tuple_143.t0 = tokens_17;
    tuple_143.t1 = errors_13;
    match_210 = tuple_143;
    goto end_match_796;
next_797:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_144;
    tuple_144.t0 = tokens_15;
    tuple_144.t1 = errors_13;
    struct StringIntIntTuple2Tuple2List* call_504 = parseNewError_1((struct String){.str = "Expected \'>\'", .len = 12}, tuple_144);
    struct StringIntIntTuple2Tuple2List* errors_15 = call_504;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_145;
    tuple_145.t0 = tokens_15;
    tuple_145.t1 = errors_15;
    match_210 = tuple_145;
    goto end_match_796;
next_798:;
end_match_796:;
    struct Token_IntIntTuple2Tuple2List* tokens_16 = match_210.t0;
    struct StringIntIntTuple2Tuple2List* errors_14 = match_210.t1;
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_146;
    tuple_146.t0 = argTys_;
    tuple_146.t1 = tokens_16;
    tuple_146.t2 = errors_14;
    match_209 = tuple_146;
    goto end_match_793;
next_794:;
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_147;
    tuple_147.t0 = NULL;
    tuple_147.t1 = tokens_9;
    tuple_147.t2 = errors_9;
    match_209 = tuple_147;
    goto end_match_793;
next_795:;
end_match_793:;
    return match_209;
}

struct StringATy_ListIntIntTuple2Tuple3 {
    struct String t0;
    struct ATy_List* t1;
    struct IntIntTuple2 t2;
};

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyAtom_(struct IntIntTuple2 baseLoc_2, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_156) {
    struct Token_IntIntTuple2Tuple2List* tokens_18 = arg_156.t0;
    struct StringIntIntTuple2Tuple2List* errors_16 = arg_156.t1;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_211;
    int call_505 = nextInside_1(baseLoc_2, tokens_18);
    if (call_505) goto next_800;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_148;
    tuple_148.t0 = tokens_18;
    tuple_148.t1 = errors_16;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_506 = parseTyError_1((struct String){.str = "Expected a type atom", .len = 20}, tuple_148);
    match_211 = call_506;
    goto end_match_799;
next_800:;
    if ((!(tokens_18))) goto next_801;
    if ((tokens_18->head.t0.tag != Ident_)) goto next_801;
    struct String ident_18 = (*(tokens_18->head.t0.Ident_));
    struct IntIntTuple2 loc_35 = tokens_18->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_19 = tokens_18->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_149;
    tuple_149.t0 = tokens_19;
    tuple_149.t1 = errors_16;
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_507 = parseTyArgs_(baseLoc_2, tuple_149);
    struct ATy_List* argTys_1 = call_507.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_20 = call_507.t1;
    struct StringIntIntTuple2Tuple2List* errors_17 = call_507.t2;
    struct StringATy_ListIntIntTuple2Tuple3 tuple_151;
    tuple_151.t0 = ident_18;
    tuple_151.t1 = argTys_1;
    tuple_151.t2 = loc_35;
    struct StringATy_ListIntIntTuple2Tuple3* payload_79 = (struct StringATy_ListIntIntTuple2Tuple3*)malloc(sizeof(struct StringATy_ListIntIntTuple2Tuple3));
    (*(((struct StringATy_ListIntIntTuple2Tuple3*)payload_79))) = tuple_151;
    struct ATy_ variant_79 = (struct ATy_){.tag = App_1, .App_1 = payload_79};
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_150;
    tuple_150.t0 = variant_79;
    tuple_150.t1 = tokens_20;
    tuple_150.t2 = errors_17;
    match_211 = tuple_150;
    goto end_match_799;
next_801:;
    if ((!(tokens_18))) goto next_802;
    if ((tokens_18->head.t0.tag != ParenL_)) goto next_802;
    struct Token_IntIntTuple2Tuple2List* tokens_21 = tokens_18->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_152;
    tuple_152.t0 = tokens_21;
    tuple_152.t1 = errors_16;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_508 = parseTy_(baseLoc_2, tuple_152);
    struct ATy_ ty_47 = call_508.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_22 = call_508.t1;
    struct StringIntIntTuple2Tuple2List* errors_18 = call_508.t2;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_212;
    if ((!(tokens_22))) goto next_805;
    if ((tokens_22->head.t0.tag != ParenR_)) goto next_805;
    struct Token_IntIntTuple2Tuple2List* tokens_23 = tokens_22->tail;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_153;
    tuple_153.t0 = ty_47;
    tuple_153.t1 = tokens_23;
    tuple_153.t2 = errors_18;
    match_212 = tuple_153;
    goto end_match_804;
next_805:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_154;
    tuple_154.t0 = tokens_22;
    tuple_154.t1 = errors_18;
    struct StringIntIntTuple2Tuple2List* call_509 = parseNewError_1((struct String){.str = "Expected \')\'", .len = 12}, tuple_154);
    struct StringIntIntTuple2Tuple2List* errors_19 = call_509;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_155;
    tuple_155.t0 = ty_47;
    tuple_155.t1 = tokens_22;
    tuple_155.t2 = errors_19;
    match_212 = tuple_155;
    goto end_match_804;
next_806:;
end_match_804:;
    match_211 = match_212;
    goto end_match_799;
next_802:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_156;
    tuple_156.t0 = tokens_18;
    tuple_156.t1 = errors_16;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_510 = parseTyError_1((struct String){.str = "Expected a type atom", .len = 20}, tuple_156);
    match_211 = call_510;
    goto end_match_799;
next_803:;
end_match_799:;
    return match_211;
}

struct ATy_StringIntIntTuple2Tuple3 {
    struct ATy_ t0;
    struct String t1;
    struct IntIntTuple2 t2;
};

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_58(struct IntIntTuple2 baseLoc_3, struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 arg_157) {
    struct ATy_ ty_48 = arg_157.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_25 = arg_157.t1;
    struct StringIntIntTuple2Tuple2List* errors_21 = arg_157.t2;
    int call_511 = nextInside_1(baseLoc_3, tokens_25);
    int inside_ = call_511;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_213;
    if ((!(tokens_25))) goto next_808;
    if ((tokens_25->head.t0.tag != Ident_)) goto next_808;
    struct String ident_19 = (*(tokens_25->head.t0.Ident_));
    struct IntIntTuple2 loc_36 = tokens_25->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_26 = tokens_25->tail;
    if ((!(inside_))) goto next_808;
    struct ATy_StringIntIntTuple2Tuple3 tuple_158;
    tuple_158.t0 = ty_48;
    tuple_158.t1 = ident_19;
    tuple_158.t2 = loc_36;
    struct ATy_StringIntIntTuple2Tuple3* payload_80 = (struct ATy_StringIntIntTuple2Tuple3*)malloc(sizeof(struct ATy_StringIntIntTuple2Tuple3));
    (*(((struct ATy_StringIntIntTuple2Tuple3*)payload_80))) = tuple_158;
    struct ATy_ variant_80 = (struct ATy_){.tag = Suffix_, .Suffix_ = payload_80};
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_157;
    tuple_157.t0 = variant_80;
    tuple_157.t1 = tokens_26;
    tuple_157.t2 = errors_21;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_512 = go_58(baseLoc_3, tuple_157);
    match_213 = call_512;
    goto end_match_807;
next_808:;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_159;
    tuple_159.t0 = ty_48;
    tuple_159.t1 = tokens_25;
    tuple_159.t2 = errors_21;
    match_213 = tuple_159;
    goto end_match_807;
next_809:;
end_match_807:;
    return match_213;
}

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTySuffix_(struct IntIntTuple2 baseLoc_3, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_158) {
    struct Token_IntIntTuple2Tuple2List* tokens_24 = arg_158.t0;
    struct StringIntIntTuple2Tuple2List* errors_20 = arg_158.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_160;
    tuple_160.t0 = tokens_24;
    tuple_160.t1 = errors_20;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_513 = parseTyAtom_(baseLoc_3, tuple_160);
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_514 = go_58(baseLoc_3, call_513);
    return call_514;
}

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyPrefix_(struct IntIntTuple2 baseLoc_4, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_159) {
    struct Token_IntIntTuple2Tuple2List* tokens_27 = arg_159.t0;
    struct StringIntIntTuple2Tuple2List* errors_22 = arg_159.t1;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_214;
    if ((!(tokens_27))) goto next_811;
    if ((tokens_27->head.t0.tag != Ident_)) goto next_811;
    if ((!(tokens_27->tail))) goto next_811;
    if ((tokens_27->tail->head.t0.tag != Colon_)) goto next_811;
    struct Token_IntIntTuple2Tuple2List* tokens_28 = tokens_27->tail->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_161;
    tuple_161.t0 = tokens_28;
    tuple_161.t1 = errors_22;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_515 = parseTySuffix_(baseLoc_4, tuple_161);
    match_214 = call_515;
    goto end_match_810;
next_811:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_162;
    tuple_162.t0 = tokens_27;
    tuple_162.t1 = errors_22;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_516 = parseTySuffix_(baseLoc_4, tuple_162);
    match_214 = call_516;
    goto end_match_810;
next_812:;
end_match_810:;
    return match_214;
}

struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_42(struct IntIntTuple2 baseLoc_5, struct ATy_List* acc_26, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_160) {
    struct Token_IntIntTuple2Tuple2List* tokens_30 = arg_160.t0;
    struct StringIntIntTuple2Tuple2List* errors_24 = arg_160.t1;
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_215;
    if ((!(tokens_30))) goto next_814;
    if ((tokens_30->head.t0.tag != Star_)) goto next_814;
    struct Token_IntIntTuple2Tuple2List* tokens_31 = tokens_30->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_163;
    tuple_163.t0 = tokens_31;
    tuple_163.t1 = errors_24;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_517 = parseTyPrefix_(baseLoc_5, tuple_163);
    struct ATy_ itemTy_11 = call_517.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_32 = call_517.t1;
    struct StringIntIntTuple2Tuple2List* errors_25 = call_517.t2;
    struct ATy_List* list_65 = (struct ATy_List*)malloc(sizeof(struct ATy_List));
    list_65->head = itemTy_11;
    list_65->tail = acc_26;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_164;
    tuple_164.t0 = tokens_32;
    tuple_164.t1 = errors_25;
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_518 = go_42(baseLoc_5, list_65, tuple_164);
    match_215 = call_518;
    goto end_match_813;
next_814:;
    struct ATy_List* call_519 = listRev_7(acc_26);
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_165;
    tuple_165.t0 = call_519;
    tuple_165.t1 = tokens_30;
    tuple_165.t2 = errors_24;
    match_215 = tuple_165;
    goto end_match_813;
next_815:;
end_match_813:;
    return match_215;
}

struct ATy_ListIntIntTuple2Tuple2 {
    struct ATy_List* t0;
    struct IntIntTuple2 t1;
};

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyTuple_(struct IntIntTuple2 baseLoc_5, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_161) {
    struct Token_IntIntTuple2Tuple2List* tokens_29 = arg_161.t0;
    struct StringIntIntTuple2Tuple2List* errors_23 = arg_161.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_166;
    tuple_166.t0 = tokens_29;
    tuple_166.t1 = errors_23;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_520 = parseTyPrefix_(baseLoc_5, tuple_166);
    struct ATy_ itemTy_12 = call_520.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_33 = call_520.t1;
    struct StringIntIntTuple2Tuple2List* errors_26 = call_520.t2;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_216;
    if ((!(tokens_33))) goto next_817;
    if ((tokens_33->head.t0.tag != Star_)) goto next_817;
    struct IntIntTuple2 opLoc_ = tokens_33->head.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_167;
    tuple_167.t0 = tokens_33;
    tuple_167.t1 = errors_26;
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_521 = go_42(baseLoc_5, NULL, tuple_167);
    struct ATy_List* itemTys_1 = call_521.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_34 = call_521.t1;
    struct StringIntIntTuple2Tuple2List* errors_27 = call_521.t2;
    struct ATy_List* list_66 = (struct ATy_List*)malloc(sizeof(struct ATy_List));
    list_66->head = itemTy_12;
    list_66->tail = itemTys_1;
    struct ATy_ListIntIntTuple2Tuple2 tuple_169;
    tuple_169.t0 = list_66;
    tuple_169.t1 = opLoc_;
    struct ATy_ListIntIntTuple2Tuple2* payload_81 = (struct ATy_ListIntIntTuple2Tuple2*)malloc(sizeof(struct ATy_ListIntIntTuple2Tuple2));
    (*(((struct ATy_ListIntIntTuple2Tuple2*)payload_81))) = tuple_169;
    struct ATy_ variant_81 = (struct ATy_){.tag = Tuple_, .Tuple_ = payload_81};
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_168;
    tuple_168.t0 = variant_81;
    tuple_168.t1 = tokens_34;
    tuple_168.t2 = errors_27;
    match_216 = tuple_168;
    goto end_match_816;
next_817:;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_170;
    tuple_170.t0 = itemTy_12;
    tuple_170.t1 = tokens_33;
    tuple_170.t2 = errors_26;
    match_216 = tuple_170;
    goto end_match_816;
next_818:;
end_match_816:;
    return match_216;
}

struct ATy_ATy_IntIntTuple2Tuple3 {
    struct ATy_ t0;
    struct ATy_ t1;
    struct IntIntTuple2 t2;
};

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyFun_(struct IntIntTuple2 baseLoc_6, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_162) {
    struct Token_IntIntTuple2Tuple2List* tokens_35 = arg_162.t0;
    struct StringIntIntTuple2Tuple2List* errors_28 = arg_162.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_171;
    tuple_171.t0 = tokens_35;
    tuple_171.t1 = errors_28;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_522 = parseTyTuple_(baseLoc_6, tuple_171);
    struct ATy_ sTy_1 = call_522.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_36 = call_522.t1;
    struct StringIntIntTuple2Tuple2List* errors_29 = call_522.t2;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_217;
    if ((!(tokens_36))) goto next_820;
    if ((tokens_36->head.t0.tag != Arrow_)) goto next_820;
    struct IntIntTuple2 opLoc_1 = tokens_36->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_37 = tokens_36->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_172;
    tuple_172.t0 = tokens_37;
    tuple_172.t1 = errors_29;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_523 = parseTyFun_(baseLoc_6, tuple_172);
    struct ATy_ tTy_1 = call_523.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_38 = call_523.t1;
    struct StringIntIntTuple2Tuple2List* errors_30 = call_523.t2;
    struct ATy_ATy_IntIntTuple2Tuple3 tuple_174;
    tuple_174.t0 = sTy_1;
    tuple_174.t1 = tTy_1;
    tuple_174.t2 = opLoc_1;
    struct ATy_ATy_IntIntTuple2Tuple3* payload_82 = (struct ATy_ATy_IntIntTuple2Tuple3*)malloc(sizeof(struct ATy_ATy_IntIntTuple2Tuple3));
    (*(((struct ATy_ATy_IntIntTuple2Tuple3*)payload_82))) = tuple_174;
    struct ATy_ variant_82 = (struct ATy_){.tag = Fun_1, .Fun_1 = payload_82};
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_173;
    tuple_173.t0 = variant_82;
    tuple_173.t1 = tokens_38;
    tuple_173.t2 = errors_30;
    match_217 = tuple_173;
    goto end_match_819;
next_820:;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_175;
    tuple_175.t0 = sTy_1;
    tuple_175.t1 = tokens_36;
    tuple_175.t2 = errors_29;
    match_217 = tuple_175;
    goto end_match_819;
next_821:;
end_match_819:;
    return match_217;
}

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTy_(struct IntIntTuple2 baseLoc_7, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_163) {
    struct Token_IntIntTuple2Tuple2List* tokens_39 = arg_163.t0;
    struct StringIntIntTuple2Tuple2List* errors_31 = arg_163.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_176;
    tuple_176.t0 = tokens_39;
    tuple_176.t1 = errors_31;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_524 = parseTyFun_(baseLoc_7, tuple_176);
    return call_524;
}

struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct AVariant_List* t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_43(struct IntIntTuple2 baseLoc_8, struct AVariant_List* acc_27, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_164) {
    struct Token_IntIntTuple2Tuple2List* tokens_41 = arg_164.t0;
    struct StringIntIntTuple2Tuple2List* errors_33 = arg_164.t1;
    struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_218;
    if ((!(tokens_41))) goto next_823;
    if ((tokens_41->head.t0.tag != Pipe_)) goto next_823;
    if ((!(tokens_41->tail))) goto next_823;
    if ((tokens_41->tail->head.t0.tag != Ident_)) goto next_823;
    struct String variantIdent_ = (*(tokens_41->tail->head.t0.Ident_));
    struct IntIntTuple2 loc_37 = tokens_41->tail->head.t1;
    if ((!(tokens_41->tail->tail))) goto next_823;
    if ((tokens_41->tail->tail->head.t0.tag != Of_)) goto next_823;
    struct Token_IntIntTuple2Tuple2List* tokens_42 = tokens_41->tail->tail->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_177;
    tuple_177.t0 = tokens_42;
    tuple_177.t1 = errors_33;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_525 = parseTy_(baseLoc_8, tuple_177);
    struct ATy_ payloadTy_ = call_525.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_43 = call_525.t1;
    struct StringIntIntTuple2Tuple2List* errors_34 = call_525.t2;
    struct ATy_List* some_2 = (struct ATy_List*)malloc(sizeof(struct ATy_List));
    some_2->head = payloadTy_;
    some_2->tail = NULL;
    struct StringATy_ListIntIntTuple2Tuple3 tuple_178;
    tuple_178.t0 = variantIdent_;
    tuple_178.t1 = some_2;
    tuple_178.t2 = loc_37;
    struct StringATy_ListIntIntTuple2Tuple3* payload_83 = (struct StringATy_ListIntIntTuple2Tuple3*)malloc(sizeof(struct StringATy_ListIntIntTuple2Tuple3));
    (*(((struct StringATy_ListIntIntTuple2Tuple3*)payload_83))) = tuple_178;
    struct AVariant_ variant_83 = (struct AVariant_){.tag = AVariant_, .AVariant_ = payload_83};
    struct AVariant_List* list_67 = (struct AVariant_List*)malloc(sizeof(struct AVariant_List));
    list_67->head = variant_83;
    list_67->tail = acc_27;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_179;
    tuple_179.t0 = tokens_43;
    tuple_179.t1 = errors_34;
    struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_526 = go_43(baseLoc_8, list_67, tuple_179);
    match_218 = call_526;
    goto end_match_822;
next_823:;
    if ((!(tokens_41))) goto next_824;
    if ((tokens_41->head.t0.tag != Pipe_)) goto next_824;
    if ((!(tokens_41->tail))) goto next_824;
    if ((tokens_41->tail->head.t0.tag != Ident_)) goto next_824;
    struct String variantIdent_1 = (*(tokens_41->tail->head.t0.Ident_));
    struct IntIntTuple2 loc_38 = tokens_41->tail->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_44 = tokens_41->tail->tail;
    struct StringATy_ListIntIntTuple2Tuple3 tuple_180;
    tuple_180.t0 = variantIdent_1;
    tuple_180.t1 = NULL;
    tuple_180.t2 = loc_38;
    struct StringATy_ListIntIntTuple2Tuple3* payload_84 = (struct StringATy_ListIntIntTuple2Tuple3*)malloc(sizeof(struct StringATy_ListIntIntTuple2Tuple3));
    (*(((struct StringATy_ListIntIntTuple2Tuple3*)payload_84))) = tuple_180;
    struct AVariant_ variant_84 = (struct AVariant_){.tag = AVariant_, .AVariant_ = payload_84};
    struct AVariant_List* list_68 = (struct AVariant_List*)malloc(sizeof(struct AVariant_List));
    list_68->head = variant_84;
    list_68->tail = acc_27;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_181;
    tuple_181.t0 = tokens_44;
    tuple_181.t1 = errors_33;
    struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_527 = go_43(baseLoc_8, list_68, tuple_181);
    match_218 = call_527;
    goto end_match_822;
next_824:;
    struct AVariant_List* call_528 = listRev_6(acc_27);
    struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_182;
    tuple_182.t0 = call_528;
    tuple_182.t1 = tokens_41;
    tuple_182.t2 = errors_33;
    match_218 = tuple_182;
    goto end_match_822;
next_825:;
end_match_822:;
    return match_218;
}

enum ATyDecl_Tag {
    Synonym_,
    Union_,
};

struct ATyDecl_ {
    enum ATyDecl_Tag tag;
    union {
        struct ATy_* Synonym_;
        struct AVariant_List** Union_;
    };
};

struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct ATyDecl_ t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyDeclUnion_(struct IntIntTuple2 baseLoc_8, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_165) {
    struct Token_IntIntTuple2Tuple2List* tokens_40 = arg_165.t0;
    struct StringIntIntTuple2Tuple2List* errors_32 = arg_165.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_183;
    tuple_183.t0 = tokens_40;
    tuple_183.t1 = errors_32;
    struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_529 = go_43(baseLoc_8, NULL, tuple_183);
    struct AVariant_List* variants_1 = call_529.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_45 = call_529.t1;
    struct StringIntIntTuple2Tuple2List* errors_35 = call_529.t2;
    struct AVariant_List** payload_85 = (struct AVariant_List**)malloc(sizeof(struct AVariant_List*));
    (*(((struct AVariant_List**)payload_85))) = variants_1;
    struct ATyDecl_ variant_85 = (struct ATyDecl_){.tag = Union_, .Union_ = payload_85};
    struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_184;
    tuple_184.t0 = variant_85;
    tuple_184.t1 = tokens_45;
    tuple_184.t2 = errors_35;
    return tuple_184;
}

struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyDeclBody_(struct IntIntTuple2 baseLoc_9, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_166) {
    struct Token_IntIntTuple2Tuple2List* tokens_46 = arg_166.t0;
    struct StringIntIntTuple2Tuple2List* errors_36 = arg_166.t1;
    struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_219;
    if ((!(tokens_46))) goto next_827;
    if ((tokens_46->head.t0.tag != Pipe_)) goto next_827;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_185;
    tuple_185.t0 = tokens_46;
    tuple_185.t1 = errors_36;
    struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_530 = parseTyDeclUnion_(baseLoc_9, tuple_185);
    match_219 = call_530;
    goto end_match_826;
next_827:;
    if ((!(tokens_46))) goto next_828;
    if ((tokens_46->head.t0.tag != Ident_)) goto next_828;
    if ((!(tokens_46->tail))) goto next_828;
    if ((tokens_46->tail->head.t0.tag != Of_)) goto next_828;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_186;
    tuple_186.t0 = tokens_46;
    tuple_186.t1 = errors_36;
    struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_531 = parseTyDeclUnion_(baseLoc_9, tuple_186);
    match_219 = call_531;
    goto end_match_826;
next_828:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_187;
    tuple_187.t0 = tokens_46;
    tuple_187.t1 = errors_36;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_532 = parseTy_(baseLoc_9, tuple_187);
    struct ATy_ ty_49 = call_532.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_47 = call_532.t1;
    struct StringIntIntTuple2Tuple2List* errors_37 = call_532.t2;
    struct ATy_* payload_86 = (struct ATy_*)malloc(sizeof(struct ATy_));
    (*(((struct ATy_*)payload_86))) = ty_49;
    struct ATyDecl_ variant_86 = (struct ATyDecl_){.tag = Synonym_, .Synonym_ = payload_86};
    struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_188;
    tuple_188.t0 = variant_86;
    tuple_188.t1 = tokens_47;
    tuple_188.t2 = errors_37;
    match_219 = tuple_188;
    goto end_match_826;
next_829:;
end_match_826:;
    return match_219;
}

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatParenBody_(struct IntIntTuple2 baseLoc_10, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_167) {
    struct Token_IntIntTuple2Tuple2List* tokens_48 = arg_167.t0;
    struct StringIntIntTuple2Tuple2List* errors_38 = arg_167.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_189;
    tuple_189.t0 = tokens_48;
    tuple_189.t1 = errors_38;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_533 = parsePat_(baseLoc_10, tuple_189);
    struct APat_ pat_15 = call_533.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_49 = call_533.t1;
    struct StringIntIntTuple2Tuple2List* errors_39 = call_533.t2;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_220;
    if ((!(tokens_49))) goto next_831;
    if ((tokens_49->head.t0.tag != ParenR_)) goto next_831;
    struct Token_IntIntTuple2Tuple2List* tokens_50 = tokens_49->tail;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_190;
    tuple_190.t0 = pat_15;
    tuple_190.t1 = tokens_50;
    tuple_190.t2 = errors_39;
    match_220 = tuple_190;
    goto end_match_830;
next_831:;
    struct Token_IntIntTuple2Tuple2List* tokens_51 = tokens_49;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_191;
    tuple_191.t0 = tokens_51;
    tuple_191.t1 = errors_39;
    struct StringIntIntTuple2Tuple2List* call_534 = parseNewError_1((struct String){.str = "Expected \')\'", .len = 12}, tuple_191);
    struct StringIntIntTuple2Tuple2List* errors_40 = call_534;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_192;
    tuple_192.t0 = pat_15;
    tuple_192.t1 = tokens_51;
    tuple_192.t2 = errors_40;
    match_220 = tuple_192;
    goto end_match_830;
next_832:;
end_match_830:;
    return match_220;
}

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct APat_List* t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_44(struct IntIntTuple2 baseLoc_11, struct APat_List* patAcc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_168) {
    struct Token_IntIntTuple2Tuple2List* tokens_53 = arg_168.t0;
    struct StringIntIntTuple2Tuple2List* errors_42 = arg_168.t1;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_221;
    if ((!(tokens_53))) goto next_834;
    if ((tokens_53->head.t0.tag != BracketR_)) goto next_834;
    struct Token_IntIntTuple2Tuple2List* tokens_54 = tokens_53->tail;
    struct APat_List* call_535 = listRev_5(patAcc_);
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_193;
    tuple_193.t0 = call_535;
    tuple_193.t1 = tokens_54;
    tuple_193.t2 = errors_42;
    match_221 = tuple_193;
    goto end_match_833;
next_834:;
    if ((!(tokens_53))) goto next_835;
    if ((tokens_53->head.t0.tag != Semi_)) goto next_835;
    struct Token_IntIntTuple2Tuple2List* tokens_55 = tokens_53->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_194;
    tuple_194.t0 = tokens_55;
    tuple_194.t1 = errors_42;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_536 = parsePat_(baseLoc_11, tuple_194);
    struct APat_ pat_16 = call_536.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_56 = call_536.t1;
    struct StringIntIntTuple2Tuple2List* errors_43 = call_536.t2;
    struct APat_List* list_69 = (struct APat_List*)malloc(sizeof(struct APat_List));
    list_69->head = pat_16;
    list_69->tail = patAcc_;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_195;
    tuple_195.t0 = tokens_56;
    tuple_195.t1 = errors_43;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_537 = go_44(baseLoc_11, list_69, tuple_195);
    match_221 = call_537;
    goto end_match_833;
next_835:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_196;
    tuple_196.t0 = tokens_53;
    tuple_196.t1 = errors_42;
    struct StringIntIntTuple2Tuple2List* call_538 = parseNewError_1((struct String){.str = "Expected \';\' or \']\'", .len = 19}, tuple_196);
    struct StringIntIntTuple2Tuple2List* errors_44 = call_538;
    struct APat_List* call_539 = listRev_5(patAcc_);
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_197;
    tuple_197.t0 = call_539;
    tuple_197.t1 = tokens_53;
    tuple_197.t2 = errors_44;
    match_221 = tuple_197;
    goto end_match_833;
next_836:;
end_match_833:;
    return match_221;
}

struct APat_ListIntIntTuple2Tuple2 {
    struct APat_List* t0;
    struct IntIntTuple2 t1;
};

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatListBody_(struct IntIntTuple2 baseLoc_11, struct IntIntTuple2 bracketLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_169) {
    struct Token_IntIntTuple2Tuple2List* tokens_52 = arg_169.t0;
    struct StringIntIntTuple2Tuple2List* errors_41 = arg_169.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_198;
    tuple_198.t0 = tokens_52;
    tuple_198.t1 = errors_41;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_540 = parsePat_(baseLoc_11, tuple_198);
    struct APat_ itemPat_ = call_540.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_57 = call_540.t1;
    struct StringIntIntTuple2Tuple2List* errors_45 = call_540.t2;
    struct APat_List* list_70 = (struct APat_List*)malloc(sizeof(struct APat_List));
    list_70->head = itemPat_;
    list_70->tail = NULL;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_199;
    tuple_199.t0 = tokens_57;
    tuple_199.t1 = errors_45;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_541 = go_44(baseLoc_11, list_70, tuple_199);
    struct APat_List* itemPats_1 = call_541.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_58 = call_541.t1;
    struct StringIntIntTuple2Tuple2List* errors_46 = call_541.t2;
    struct APat_ListIntIntTuple2Tuple2 tuple_201;
    tuple_201.t0 = itemPats_1;
    tuple_201.t1 = bracketLoc_;
    struct APat_ListIntIntTuple2Tuple2* payload_87 = (struct APat_ListIntIntTuple2Tuple2*)malloc(sizeof(struct APat_ListIntIntTuple2Tuple2));
    (*(((struct APat_ListIntIntTuple2Tuple2*)payload_87))) = tuple_201;
    struct APat_ variant_87 = (struct APat_){.tag = ListLit_, .ListLit_ = payload_87};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_200;
    tuple_200.t0 = variant_87;
    tuple_200.t1 = tokens_58;
    tuple_200.t2 = errors_46;
    return tuple_200;
}

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatAtom_(struct IntIntTuple2 baseLoc_12, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_170) {
    struct Token_IntIntTuple2Tuple2List* tokens_59 = arg_170.t0;
    struct StringIntIntTuple2Tuple2List* errors_47 = arg_170.t1;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_222;
    int match_223;
    int call_542 = nextInside_1(baseLoc_12, tokens_59);
    if ((!(call_542))) goto next_850;
    int call_543 = leadsPat_1(tokens_59);
    match_223 = call_543;
    goto end_match_849;
next_850:;
    if (call_542) goto next_851;
    match_223 = 0;
    goto end_match_849;
next_851:;
    exit(1);
end_match_849:;
    if (match_223) goto next_838;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_202;
    tuple_202.t0 = tokens_59;
    tuple_202.t1 = errors_47;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_544 = parsePatError_1((struct String){.str = "Expected a pattern atom", .len = 23}, tuple_202);
    match_222 = call_544;
    goto end_match_837;
next_838:;
    if ((!(tokens_59))) goto next_839;
    if ((tokens_59->head.t0.tag != Bool_1)) goto next_839;
    int value_12 = (*(tokens_59->head.t0.Bool_1));
    struct IntIntTuple2 loc_39 = tokens_59->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_60 = tokens_59->tail;
    int* payload_88 = (int*)malloc(sizeof(int));
    (*(((int*)payload_88))) = value_12;
    struct Lit_ variant_88 = (struct Lit_){.tag = Bool_, .Bool_ = payload_88};
    struct Lit_IntIntTuple2Tuple2 tuple_204;
    tuple_204.t0 = variant_88;
    tuple_204.t1 = loc_39;
    struct Lit_IntIntTuple2Tuple2* payload_89 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_89))) = tuple_204;
    struct APat_ variant_89 = (struct APat_){.tag = Lit_, .Lit_ = payload_89};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_203;
    tuple_203.t0 = variant_89;
    tuple_203.t1 = tokens_60;
    tuple_203.t2 = errors_47;
    match_222 = tuple_203;
    goto end_match_837;
next_839:;
    if ((!(tokens_59))) goto next_840;
    if ((tokens_59->head.t0.tag != Int_1)) goto next_840;
    int value_13 = (*(tokens_59->head.t0.Int_1));
    struct IntIntTuple2 loc_40 = tokens_59->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_61 = tokens_59->tail;
    int* payload_90 = (int*)malloc(sizeof(int));
    (*(((int*)payload_90))) = value_13;
    struct Lit_ variant_90 = (struct Lit_){.tag = Int_, .Int_ = payload_90};
    struct Lit_IntIntTuple2Tuple2 tuple_206;
    tuple_206.t0 = variant_90;
    tuple_206.t1 = loc_40;
    struct Lit_IntIntTuple2Tuple2* payload_91 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_91))) = tuple_206;
    struct APat_ variant_91 = (struct APat_){.tag = Lit_, .Lit_ = payload_91};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_205;
    tuple_205.t0 = variant_91;
    tuple_205.t1 = tokens_61;
    tuple_205.t2 = errors_47;
    match_222 = tuple_205;
    goto end_match_837;
next_840:;
    if ((!(tokens_59))) goto next_841;
    if ((tokens_59->head.t0.tag != Char_1)) goto next_841;
    char value_14 = (*(tokens_59->head.t0.Char_1));
    struct IntIntTuple2 loc_41 = tokens_59->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_62 = tokens_59->tail;
    char* payload_92 = (char*)malloc(sizeof(char));
    (*(((char*)payload_92))) = value_14;
    struct Lit_ variant_92 = (struct Lit_){.tag = Char_, .Char_ = payload_92};
    struct Lit_IntIntTuple2Tuple2 tuple_208;
    tuple_208.t0 = variant_92;
    tuple_208.t1 = loc_41;
    struct Lit_IntIntTuple2Tuple2* payload_93 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_93))) = tuple_208;
    struct APat_ variant_93 = (struct APat_){.tag = Lit_, .Lit_ = payload_93};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_207;
    tuple_207.t0 = variant_93;
    tuple_207.t1 = tokens_62;
    tuple_207.t2 = errors_47;
    match_222 = tuple_207;
    goto end_match_837;
next_841:;
    if ((!(tokens_59))) goto next_842;
    if ((tokens_59->head.t0.tag != Str_1)) goto next_842;
    struct String value_15 = (*(tokens_59->head.t0.Str_1));
    struct IntIntTuple2 loc_42 = tokens_59->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_63 = tokens_59->tail;
    struct String* payload_94 = (struct String*)malloc(sizeof(struct String));
    (*(((struct String*)payload_94))) = value_15;
    struct Lit_ variant_94 = (struct Lit_){.tag = Str_, .Str_ = payload_94};
    struct Lit_IntIntTuple2Tuple2 tuple_210;
    tuple_210.t0 = variant_94;
    tuple_210.t1 = loc_42;
    struct Lit_IntIntTuple2Tuple2* payload_95 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_95))) = tuple_210;
    struct APat_ variant_95 = (struct APat_){.tag = Lit_, .Lit_ = payload_95};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_209;
    tuple_209.t0 = variant_95;
    tuple_209.t1 = tokens_63;
    tuple_209.t2 = errors_47;
    match_222 = tuple_209;
    goto end_match_837;
next_842:;
    if ((!(tokens_59))) goto next_843;
    if ((tokens_59->head.t0.tag != Ident_)) goto next_843;
    struct String ident_20 = (*(tokens_59->head.t0.Ident_));
    struct IntIntTuple2 loc_43 = tokens_59->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_64 = tokens_59->tail;
    struct StringIntIntTuple2Tuple2 tuple_212;
    tuple_212.t0 = ident_20;
    tuple_212.t1 = loc_43;
    struct StringIntIntTuple2Tuple2* payload_96 = (struct StringIntIntTuple2Tuple2*)malloc(sizeof(struct StringIntIntTuple2Tuple2));
    (*(((struct StringIntIntTuple2Tuple2*)payload_96))) = tuple_212;
    struct APat_ variant_96 = (struct APat_){.tag = Ident_1, .Ident_1 = payload_96};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_211;
    tuple_211.t0 = variant_96;
    tuple_211.t1 = tokens_64;
    tuple_211.t2 = errors_47;
    match_222 = tuple_211;
    goto end_match_837;
next_843:;
    if ((!(tokens_59))) goto next_844;
    if ((tokens_59->head.t0.tag != ParenL_)) goto next_844;
    struct IntIntTuple2 loc_44 = tokens_59->head.t1;
    if ((!(tokens_59->tail))) goto next_844;
    if ((tokens_59->tail->head.t0.tag != ParenR_)) goto next_844;
    struct Token_IntIntTuple2Tuple2List* tokens_65 = tokens_59->tail->tail;
    struct APat_ListIntIntTuple2Tuple2 tuple_214;
    tuple_214.t0 = NULL;
    tuple_214.t1 = loc_44;
    struct APat_ListIntIntTuple2Tuple2* payload_97 = (struct APat_ListIntIntTuple2Tuple2*)malloc(sizeof(struct APat_ListIntIntTuple2Tuple2));
    (*(((struct APat_ListIntIntTuple2Tuple2*)payload_97))) = tuple_214;
    struct APat_ variant_97 = (struct APat_){.tag = TupleLit_, .TupleLit_ = payload_97};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_213;
    tuple_213.t0 = variant_97;
    tuple_213.t1 = tokens_65;
    tuple_213.t2 = errors_47;
    match_222 = tuple_213;
    goto end_match_837;
next_844:;
    if ((!(tokens_59))) goto next_845;
    if ((tokens_59->head.t0.tag != ParenL_)) goto next_845;
    struct Token_IntIntTuple2Tuple2List* tokens_66 = tokens_59->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_215;
    tuple_215.t0 = tokens_66;
    tuple_215.t1 = errors_47;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_545 = parsePatParenBody_(baseLoc_12, tuple_215);
    match_222 = call_545;
    goto end_match_837;
next_845:;
    if ((!(tokens_59))) goto next_846;
    if ((tokens_59->head.t0.tag != BracketL_)) goto next_846;
    struct IntIntTuple2 loc_45 = tokens_59->head.t1;
    if ((!(tokens_59->tail))) goto next_846;
    if ((tokens_59->tail->head.t0.tag != BracketR_)) goto next_846;
    struct Token_IntIntTuple2Tuple2List* tokens_67 = tokens_59->tail->tail;
    struct APat_ListIntIntTuple2Tuple2 tuple_217;
    tuple_217.t0 = NULL;
    tuple_217.t1 = loc_45;
    struct APat_ListIntIntTuple2Tuple2* payload_98 = (struct APat_ListIntIntTuple2Tuple2*)malloc(sizeof(struct APat_ListIntIntTuple2Tuple2));
    (*(((struct APat_ListIntIntTuple2Tuple2*)payload_98))) = tuple_217;
    struct APat_ variant_98 = (struct APat_){.tag = ListLit_, .ListLit_ = payload_98};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_216;
    tuple_216.t0 = variant_98;
    tuple_216.t1 = tokens_67;
    tuple_216.t2 = errors_47;
    match_222 = tuple_216;
    goto end_match_837;
next_846:;
    if ((!(tokens_59))) goto next_847;
    if ((tokens_59->head.t0.tag != BracketL_)) goto next_847;
    struct IntIntTuple2 loc_46 = tokens_59->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_68 = tokens_59->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_218;
    tuple_218.t0 = tokens_68;
    tuple_218.t1 = errors_47;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_546 = parsePatListBody_(baseLoc_12, loc_46, tuple_218);
    match_222 = call_546;
    goto end_match_837;
next_847:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_219;
    tuple_219.t0 = tokens_59;
    tuple_219.t1 = errors_47;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_547 = parsePatError_1((struct String){.str = "NEVER: The token must be a pat", .len = 30}, tuple_219);
    match_222 = call_547;
    goto end_match_837;
next_848:;
end_match_837:;
    return match_222;
}

struct APat_StringIntIntTuple2Tuple3 {
    struct APat_ t0;
    struct String t1;
    struct IntIntTuple2 t2;
};

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatNav_(struct IntIntTuple2 baseLoc_13, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_171) {
    struct Token_IntIntTuple2Tuple2List* tokens_69 = arg_171.t0;
    struct StringIntIntTuple2Tuple2List* errors_48 = arg_171.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_220;
    tuple_220.t0 = tokens_69;
    tuple_220.t1 = errors_48;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_548 = parsePatAtom_(baseLoc_13, tuple_220);
    struct APat_ pat_17 = call_548.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_70 = call_548.t1;
    struct StringIntIntTuple2Tuple2List* errors_49 = call_548.t2;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_224;
    if ((!(tokens_70))) goto next_853;
    if ((tokens_70->head.t0.tag != Dot_)) goto next_853;
    struct IntIntTuple2 loc_47 = tokens_70->head.t1;
    if ((!(tokens_70->tail))) goto next_853;
    if ((tokens_70->tail->head.t0.tag != Ident_)) goto next_853;
    struct String ident_21 = (*(tokens_70->tail->head.t0.Ident_));
    struct Token_IntIntTuple2Tuple2List* tokens_71 = tokens_70->tail->tail;
    struct APat_StringIntIntTuple2Tuple3 tuple_222;
    tuple_222.t0 = pat_17;
    tuple_222.t1 = ident_21;
    tuple_222.t2 = loc_47;
    struct APat_StringIntIntTuple2Tuple3* payload_99 = (struct APat_StringIntIntTuple2Tuple3*)malloc(sizeof(struct APat_StringIntIntTuple2Tuple3));
    (*(((struct APat_StringIntIntTuple2Tuple3*)payload_99))) = tuple_222;
    struct APat_ variant_99 = (struct APat_){.tag = Nav_, .Nav_ = payload_99};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_221;
    tuple_221.t0 = variant_99;
    tuple_221.t1 = tokens_71;
    tuple_221.t2 = errors_49;
    match_224 = tuple_221;
    goto end_match_852;
next_853:;
    if ((!(tokens_70))) goto next_854;
    if ((tokens_70->head.t0.tag != Dot_)) goto next_854;
    struct Token_IntIntTuple2Tuple2List* tokens_72 = tokens_70->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_223;
    tuple_223.t0 = tokens_72;
    tuple_223.t1 = errors_49;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_549 = parsePatError_1((struct String){.str = "Expected identifier", .len = 19}, tuple_223);
    match_224 = call_549;
    goto end_match_852;
next_854:;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_224;
    tuple_224.t0 = pat_17;
    tuple_224.t1 = tokens_70;
    tuple_224.t2 = errors_49;
    match_224 = tuple_224;
    goto end_match_852;
next_855:;
end_match_852:;
    return match_224;
}

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_45(struct IntIntTuple2 argBaseLoc_, struct IntIntTuple2 baseLoc_14, struct APat_List* acc_28, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_172) {
    struct Token_IntIntTuple2Tuple2List* tokens_74 = arg_172.t0;
    struct StringIntIntTuple2Tuple2List* errors_51 = arg_172.t1;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_225;
    int match_226;
    int call_550 = nextInside_1(argBaseLoc_, tokens_74);
    if ((!(call_550))) goto next_858;
    int call_551 = leadsPat_1(tokens_74);
    match_226 = call_551;
    goto end_match_857;
next_858:;
    if (call_550) goto next_859;
    match_226 = 0;
    goto end_match_857;
next_859:;
    exit(1);
end_match_857:;
    if ((!(match_226))) goto next_860;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_225;
    tuple_225.t0 = tokens_74;
    tuple_225.t1 = errors_51;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_552 = parsePatNav_(baseLoc_14, tuple_225);
    struct APat_ expr_10 = call_552.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_75 = call_552.t1;
    struct StringIntIntTuple2Tuple2List* errors_52 = call_552.t2;
    struct APat_List* list_71 = (struct APat_List*)malloc(sizeof(struct APat_List));
    list_71->head = expr_10;
    list_71->tail = acc_28;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_226;
    tuple_226.t0 = tokens_75;
    tuple_226.t1 = errors_52;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_553 = go_45(argBaseLoc_, baseLoc_14, list_71, tuple_226);
    match_225 = call_553;
    goto end_match_856;
next_860:;
    if (match_226) goto next_861;
    struct APat_List* call_554 = listRev_5(acc_28);
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_227;
    tuple_227.t0 = call_554;
    tuple_227.t1 = tokens_74;
    tuple_227.t2 = errors_51;
    match_225 = tuple_227;
    goto end_match_856;
next_861:;
    exit(1);
end_match_856:;
    return match_225;
}

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatCallArgs_(struct IntIntTuple2 baseLoc_14, struct IntIntTuple2 calleeLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_173) {
    struct Token_IntIntTuple2Tuple2List* tokens_73 = arg_173.t0;
    struct StringIntIntTuple2Tuple2List* errors_50 = arg_173.t1;
    struct IntIntTuple2 call_555 = locMax_(baseLoc_14, calleeLoc_);
    struct IntIntTuple2 call_556 = locAddX_(1, call_555);
    struct IntIntTuple2 argBaseLoc_ = call_556;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_228;
    tuple_228.t0 = tokens_73;
    tuple_228.t1 = errors_50;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_557 = go_45(argBaseLoc_, baseLoc_14, NULL, tuple_228);
    return call_557;
}

struct APat_APat_ListIntIntTuple2Tuple3 {
    struct APat_ t0;
    struct APat_List* t1;
    struct IntIntTuple2 t2;
};

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatCall_(struct IntIntTuple2 baseLoc_15, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_174) {
    struct Token_IntIntTuple2Tuple2List* tokens_76 = arg_174.t0;
    struct StringIntIntTuple2Tuple2List* errors_53 = arg_174.t1;
    struct IntIntTuple2 call_558 = nextLoc_1(tokens_76);
    struct IntIntTuple2 calleeLoc_1 = call_558;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_229;
    tuple_229.t0 = tokens_76;
    tuple_229.t1 = errors_53;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_559 = parsePatNav_(baseLoc_15, tuple_229);
    struct APat_ callee_5 = call_559.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_77 = call_559.t1;
    struct StringIntIntTuple2Tuple2List* errors_54 = call_559.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_230;
    tuple_230.t0 = tokens_77;
    tuple_230.t1 = errors_54;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_560 = parsePatCallArgs_(baseLoc_15, calleeLoc_1, tuple_230);
    struct APat_List* args_6 = call_560.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_78 = call_560.t1;
    struct StringIntIntTuple2Tuple2List* errors_55 = call_560.t2;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_227;
    if ((!((!(args_6))))) goto next_863;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_231;
    tuple_231.t0 = callee_5;
    tuple_231.t1 = tokens_78;
    tuple_231.t2 = errors_55;
    match_227 = tuple_231;
    goto end_match_862;
next_863:;
    struct APat_APat_ListIntIntTuple2Tuple3 tuple_233;
    tuple_233.t0 = callee_5;
    tuple_233.t1 = args_6;
    tuple_233.t2 = calleeLoc_1;
    struct APat_APat_ListIntIntTuple2Tuple3* payload_100 = (struct APat_APat_ListIntIntTuple2Tuple3*)malloc(sizeof(struct APat_APat_ListIntIntTuple2Tuple3));
    (*(((struct APat_APat_ListIntIntTuple2Tuple3*)payload_100))) = tuple_233;
    struct APat_ variant_100 = (struct APat_){.tag = Call_, .Call_ = payload_100};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_232;
    tuple_232.t0 = variant_100;
    tuple_232.t1 = tokens_78;
    tuple_232.t2 = errors_55;
    match_227 = tuple_232;
    goto end_match_862;
next_864:;
end_match_862:;
    return match_227;
}

struct APat_APat_IntIntTuple2Tuple3 {
    struct APat_ t0;
    struct APat_ t1;
    struct IntIntTuple2 t2;
};

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatCons_(struct IntIntTuple2 baseLoc_16, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_175) {
    struct Token_IntIntTuple2Tuple2List* tokens_79 = arg_175.t0;
    struct StringIntIntTuple2Tuple2List* errors_56 = arg_175.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_234;
    tuple_234.t0 = tokens_79;
    tuple_234.t1 = errors_56;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_561 = parsePatCall_(baseLoc_16, tuple_234);
    struct APat_ head_2 = call_561.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_80 = call_561.t1;
    struct StringIntIntTuple2Tuple2List* errors_57 = call_561.t2;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_228;
    if ((!(tokens_80))) goto next_866;
    if ((tokens_80->head.t0.tag != ColonColon_)) goto next_866;
    struct IntIntTuple2 loc_48 = tokens_80->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_81 = tokens_80->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_235;
    tuple_235.t0 = tokens_81;
    tuple_235.t1 = errors_57;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_562 = parsePatCons_(baseLoc_16, tuple_235);
    struct APat_ tail_2 = call_562.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_82 = call_562.t1;
    struct StringIntIntTuple2Tuple2List* errors_58 = call_562.t2;
    struct APat_APat_IntIntTuple2Tuple3 tuple_237;
    tuple_237.t0 = head_2;
    tuple_237.t1 = tail_2;
    tuple_237.t2 = loc_48;
    struct APat_APat_IntIntTuple2Tuple3* payload_101 = (struct APat_APat_IntIntTuple2Tuple3*)malloc(sizeof(struct APat_APat_IntIntTuple2Tuple3));
    (*(((struct APat_APat_IntIntTuple2Tuple3*)payload_101))) = tuple_237;
    struct APat_ variant_101 = (struct APat_){.tag = Cons_2, .Cons_2 = payload_101};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_236;
    tuple_236.t0 = variant_101;
    tuple_236.t1 = tokens_82;
    tuple_236.t2 = errors_58;
    match_228 = tuple_236;
    goto end_match_865;
next_866:;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_238;
    tuple_238.t0 = head_2;
    tuple_238.t1 = tokens_80;
    tuple_238.t2 = errors_57;
    match_228 = tuple_238;
    goto end_match_865;
next_867:;
end_match_865:;
    return match_228;
}

struct APat_ATy_IntIntTuple2Tuple3 {
    struct APat_ t0;
    struct ATy_ t1;
    struct IntIntTuple2 t2;
};

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatAnno_(struct IntIntTuple2 baseLoc_17, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_176) {
    struct Token_IntIntTuple2Tuple2List* tokens_83 = arg_176.t0;
    struct StringIntIntTuple2Tuple2List* errors_59 = arg_176.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_239;
    tuple_239.t0 = tokens_83;
    tuple_239.t1 = errors_59;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_563 = parsePatCons_(baseLoc_17, tuple_239);
    struct APat_ pat_18 = call_563.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_84 = call_563.t1;
    struct StringIntIntTuple2Tuple2List* errors_60 = call_563.t2;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_229;
    if ((!(tokens_84))) goto next_869;
    if ((tokens_84->head.t0.tag != Colon_)) goto next_869;
    struct IntIntTuple2 loc_49 = tokens_84->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_85 = tokens_84->tail;
    struct IntIntTuple2 call_564 = nextLoc_1(tokens_85);
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_240;
    tuple_240.t0 = tokens_85;
    tuple_240.t1 = errors_60;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_565 = parseTy_(call_564, tuple_240);
    struct ATy_ ty_50 = call_565.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_86 = call_565.t1;
    struct StringIntIntTuple2Tuple2List* errors_61 = call_565.t2;
    struct APat_ATy_IntIntTuple2Tuple3 tuple_242;
    tuple_242.t0 = pat_18;
    tuple_242.t1 = ty_50;
    tuple_242.t2 = loc_49;
    struct APat_ATy_IntIntTuple2Tuple3* payload_102 = (struct APat_ATy_IntIntTuple2Tuple3*)malloc(sizeof(struct APat_ATy_IntIntTuple2Tuple3));
    (*(((struct APat_ATy_IntIntTuple2Tuple3*)payload_102))) = tuple_242;
    struct APat_ variant_102 = (struct APat_){.tag = Anno_, .Anno_ = payload_102};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_241;
    tuple_241.t0 = variant_102;
    tuple_241.t1 = tokens_86;
    tuple_241.t2 = errors_61;
    match_229 = tuple_241;
    goto end_match_868;
next_869:;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_243;
    tuple_243.t0 = pat_18;
    tuple_243.t1 = tokens_84;
    tuple_243.t2 = errors_60;
    match_229 = tuple_243;
    goto end_match_868;
next_870:;
end_match_868:;
    return match_229;
}

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_46(struct IntIntTuple2 baseLoc_18, struct APat_List* acc_29, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_177) {
    struct Token_IntIntTuple2Tuple2List* tokens_88 = arg_177.t0;
    struct StringIntIntTuple2Tuple2List* errors_63 = arg_177.t1;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_230;
    if ((!(tokens_88))) goto next_872;
    if ((tokens_88->head.t0.tag != Comma_)) goto next_872;
    struct Token_IntIntTuple2Tuple2List* tokens_89 = tokens_88->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_244;
    tuple_244.t0 = tokens_89;
    tuple_244.t1 = errors_63;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_566 = parsePatAnno_(baseLoc_18, tuple_244);
    struct APat_ second_3 = call_566.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_90 = call_566.t1;
    struct StringIntIntTuple2Tuple2List* errors_64 = call_566.t2;
    struct APat_List* list_72 = (struct APat_List*)malloc(sizeof(struct APat_List));
    list_72->head = second_3;
    list_72->tail = acc_29;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_245;
    tuple_245.t0 = tokens_90;
    tuple_245.t1 = errors_64;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_567 = go_46(baseLoc_18, list_72, tuple_245);
    match_230 = call_567;
    goto end_match_871;
next_872:;
    struct APat_List* call_568 = listRev_5(acc_29);
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_246;
    tuple_246.t0 = call_568;
    tuple_246.t1 = tokens_88;
    tuple_246.t2 = errors_63;
    match_230 = tuple_246;
    goto end_match_871;
next_873:;
end_match_871:;
    return match_230;
}

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatTuple_(struct IntIntTuple2 baseLoc_18, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_178) {
    struct Token_IntIntTuple2Tuple2List* tokens_87 = arg_178.t0;
    struct StringIntIntTuple2Tuple2List* errors_62 = arg_178.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_247;
    tuple_247.t0 = tokens_87;
    tuple_247.t1 = errors_62;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_569 = parsePatAnno_(baseLoc_18, tuple_247);
    struct APat_ itemPat_1 = call_569.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_91 = call_569.t1;
    struct StringIntIntTuple2Tuple2List* errors_65 = call_569.t2;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_231;
    if ((!(tokens_91))) goto next_875;
    if ((tokens_91->head.t0.tag != Comma_)) goto next_875;
    struct IntIntTuple2 loc_50 = tokens_91->head.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_248;
    tuple_248.t0 = tokens_91;
    tuple_248.t1 = errors_65;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_570 = go_46(baseLoc_18, NULL, tuple_248);
    struct APat_List* itemPats_2 = call_570.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_92 = call_570.t1;
    struct StringIntIntTuple2Tuple2List* errors_66 = call_570.t2;
    struct APat_List* list_73 = (struct APat_List*)malloc(sizeof(struct APat_List));
    list_73->head = itemPat_1;
    list_73->tail = itemPats_2;
    struct APat_ListIntIntTuple2Tuple2 tuple_250;
    tuple_250.t0 = list_73;
    tuple_250.t1 = loc_50;
    struct APat_ListIntIntTuple2Tuple2* payload_103 = (struct APat_ListIntIntTuple2Tuple2*)malloc(sizeof(struct APat_ListIntIntTuple2Tuple2));
    (*(((struct APat_ListIntIntTuple2Tuple2*)payload_103))) = tuple_250;
    struct APat_ variant_103 = (struct APat_){.tag = TupleLit_, .TupleLit_ = payload_103};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_249;
    tuple_249.t0 = variant_103;
    tuple_249.t1 = tokens_92;
    tuple_249.t2 = errors_66;
    match_231 = tuple_249;
    goto end_match_874;
next_875:;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_251;
    tuple_251.t0 = itemPat_1;
    tuple_251.t1 = tokens_91;
    tuple_251.t2 = errors_65;
    match_231 = tuple_251;
    goto end_match_874;
next_876:;
end_match_874:;
    return match_231;
}

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatAs_(struct IntIntTuple2 baseLoc_19, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_179) {
    struct Token_IntIntTuple2Tuple2List* tokens_93 = arg_179.t0;
    struct StringIntIntTuple2Tuple2List* errors_67 = arg_179.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_252;
    tuple_252.t0 = tokens_93;
    tuple_252.t1 = errors_67;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_571 = parsePatTuple_(baseLoc_19, tuple_252);
    struct APat_ pat_19 = call_571.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_94 = call_571.t1;
    struct StringIntIntTuple2Tuple2List* errors_68 = call_571.t2;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_232;
    if ((!(tokens_94))) goto next_878;
    if ((tokens_94->head.t0.tag != As_)) goto next_878;
    struct IntIntTuple2 loc_51 = tokens_94->head.t1;
    if ((!(tokens_94->tail))) goto next_878;
    if ((tokens_94->tail->head.t0.tag != Ident_)) goto next_878;
    struct String ident_22 = (*(tokens_94->tail->head.t0.Ident_));
    struct Token_IntIntTuple2Tuple2List* tokens_95 = tokens_94->tail->tail;
    struct APat_StringIntIntTuple2Tuple3 tuple_254;
    tuple_254.t0 = pat_19;
    tuple_254.t1 = ident_22;
    tuple_254.t2 = loc_51;
    struct APat_StringIntIntTuple2Tuple3* payload_104 = (struct APat_StringIntIntTuple2Tuple3*)malloc(sizeof(struct APat_StringIntIntTuple2Tuple3));
    (*(((struct APat_StringIntIntTuple2Tuple3*)payload_104))) = tuple_254;
    struct APat_ variant_104 = (struct APat_){.tag = As_1, .As_1 = payload_104};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_253;
    tuple_253.t0 = variant_104;
    tuple_253.t1 = tokens_95;
    tuple_253.t2 = errors_68;
    match_232 = tuple_253;
    goto end_match_877;
next_878:;
    if ((!(tokens_94))) goto next_879;
    if ((tokens_94->head.t0.tag != As_)) goto next_879;
    struct Token_IntIntTuple2Tuple2List* tokens_96 = tokens_94->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_255;
    tuple_255.t0 = tokens_96;
    tuple_255.t1 = errors_68;
    struct StringIntIntTuple2Tuple2List* call_572 = parseNewError_1((struct String){.str = "Expected an identifier", .len = 22}, tuple_255);
    struct StringIntIntTuple2Tuple2List* errors_69 = call_572;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_256;
    tuple_256.t0 = pat_19;
    tuple_256.t1 = tokens_96;
    tuple_256.t2 = errors_69;
    match_232 = tuple_256;
    goto end_match_877;
next_879:;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_257;
    tuple_257.t0 = pat_19;
    tuple_257.t1 = tokens_94;
    tuple_257.t2 = errors_68;
    match_232 = tuple_257;
    goto end_match_877;
next_880:;
end_match_877:;
    return match_232;
}

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatOr_(struct IntIntTuple2 baseLoc_20, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_180) {
    struct Token_IntIntTuple2Tuple2List* tokens_97 = arg_180.t0;
    struct StringIntIntTuple2Tuple2List* errors_70 = arg_180.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_258;
    tuple_258.t0 = tokens_97;
    tuple_258.t1 = errors_70;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_573 = parsePatAs_(baseLoc_20, tuple_258);
    struct APat_ lPat_ = call_573.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_98 = call_573.t1;
    struct StringIntIntTuple2Tuple2List* errors_71 = call_573.t2;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_233;
    if ((!(tokens_98))) goto next_882;
    if ((tokens_98->head.t0.tag != Pipe_)) goto next_882;
    struct IntIntTuple2 loc_52 = tokens_98->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_99 = tokens_98->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_259;
    tuple_259.t0 = tokens_99;
    tuple_259.t1 = errors_71;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_574 = parsePatOr_(baseLoc_20, tuple_259);
    struct APat_ rPat_ = call_574.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_100 = call_574.t1;
    struct StringIntIntTuple2Tuple2List* errors_72 = call_574.t2;
    struct APat_APat_IntIntTuple2Tuple3 tuple_261;
    tuple_261.t0 = lPat_;
    tuple_261.t1 = rPat_;
    tuple_261.t2 = loc_52;
    struct APat_APat_IntIntTuple2Tuple3* payload_105 = (struct APat_APat_IntIntTuple2Tuple3*)malloc(sizeof(struct APat_APat_IntIntTuple2Tuple3));
    (*(((struct APat_APat_IntIntTuple2Tuple3*)payload_105))) = tuple_261;
    struct APat_ variant_105 = (struct APat_){.tag = Or_2, .Or_2 = payload_105};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_260;
    tuple_260.t0 = variant_105;
    tuple_260.t1 = tokens_100;
    tuple_260.t2 = errors_72;
    match_233 = tuple_260;
    goto end_match_881;
next_882:;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_262;
    tuple_262.t0 = lPat_;
    tuple_262.t1 = tokens_98;
    tuple_262.t2 = errors_71;
    match_233 = tuple_262;
    goto end_match_881;
next_883:;
end_match_881:;
    return match_233;
}

struct StringAPat_ListIntIntTuple2Tuple3 {
    struct String t0;
    struct APat_List* t1;
    struct IntIntTuple2 t2;
};

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatLet_(struct IntIntTuple2 baseLoc_21, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_181) {
    struct Token_IntIntTuple2Tuple2List* tokens_101 = arg_181.t0;
    struct StringIntIntTuple2Tuple2List* errors_73 = arg_181.t1;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_234;
    if ((!(tokens_101))) goto next_885;
    if ((tokens_101->head.t0.tag != Ident_)) goto next_885;
    struct String callee_6 = (*(tokens_101->head.t0.Ident_));
    struct IntIntTuple2 calleeLoc_2 = tokens_101->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_102 = tokens_101->tail;
    int match_235;
    int call_575 = locInside_(baseLoc_21, calleeLoc_2);
    if ((!(call_575))) goto next_888;
    int call_576 = leadsPat_1(tokens_102);
    match_235 = call_576;
    goto end_match_887;
next_888:;
    if (call_575) goto next_889;
    match_235 = 0;
    goto end_match_887;
next_889:;
    exit(1);
end_match_887:;
    if ((!(match_235))) goto next_885;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_263;
    tuple_263.t0 = tokens_102;
    tuple_263.t1 = errors_73;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_577 = parsePatCallArgs_(baseLoc_21, calleeLoc_2, tuple_263);
    struct APat_List* args_7 = call_577.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_103 = call_577.t1;
    struct StringIntIntTuple2Tuple2List* errors_74 = call_577.t2;
    struct StringAPat_ListIntIntTuple2Tuple3 tuple_264;
    tuple_264.t0 = callee_6;
    tuple_264.t1 = args_7;
    tuple_264.t2 = calleeLoc_2;
    struct StringAPat_ListIntIntTuple2Tuple3* payload_106 = (struct StringAPat_ListIntIntTuple2Tuple3*)malloc(sizeof(struct StringAPat_ListIntIntTuple2Tuple3));
    (*(((struct StringAPat_ListIntIntTuple2Tuple3*)payload_106))) = tuple_264;
    struct APat_ variant_106 = (struct APat_){.tag = Fun_2, .Fun_2 = payload_106};
    struct APat_ pat_20 = variant_106;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_236;
    if ((!(tokens_103))) goto next_891;
    if ((tokens_103->head.t0.tag != Colon_)) goto next_891;
    struct IntIntTuple2 loc_53 = tokens_103->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_104 = tokens_103->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_265;
    tuple_265.t0 = tokens_104;
    tuple_265.t1 = errors_74;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_578 = parseTy_(baseLoc_21, tuple_265);
    struct ATy_ ty_51 = call_578.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_105 = call_578.t1;
    struct StringIntIntTuple2Tuple2List* errors_75 = call_578.t2;
    struct APat_ATy_IntIntTuple2Tuple3 tuple_267;
    tuple_267.t0 = pat_20;
    tuple_267.t1 = ty_51;
    tuple_267.t2 = loc_53;
    struct APat_ATy_IntIntTuple2Tuple3* payload_107 = (struct APat_ATy_IntIntTuple2Tuple3*)malloc(sizeof(struct APat_ATy_IntIntTuple2Tuple3));
    (*(((struct APat_ATy_IntIntTuple2Tuple3*)payload_107))) = tuple_267;
    struct APat_ variant_107 = (struct APat_){.tag = Anno_, .Anno_ = payload_107};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_266;
    tuple_266.t0 = variant_107;
    tuple_266.t1 = tokens_105;
    tuple_266.t2 = errors_75;
    match_236 = tuple_266;
    goto end_match_890;
next_891:;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_268;
    tuple_268.t0 = pat_20;
    tuple_268.t1 = tokens_103;
    tuple_268.t2 = errors_74;
    match_236 = tuple_268;
    goto end_match_890;
next_892:;
end_match_890:;
    match_234 = match_236;
    goto end_match_884;
next_885:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_269;
    tuple_269.t0 = tokens_101;
    tuple_269.t1 = errors_73;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_579 = parsePat_(baseLoc_21, tuple_269);
    match_234 = call_579;
    goto end_match_884;
next_886:;
end_match_884:;
    return match_234;
}

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePat_(struct IntIntTuple2 baseLoc_22, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_182) {
    struct Token_IntIntTuple2Tuple2List* tokens_106 = arg_182.t0;
    struct StringIntIntTuple2Tuple2List* errors_76 = arg_182.t1;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_237;
    int match_238;
    int call_580 = nextInside_1(baseLoc_22, tokens_106);
    if ((!(call_580))) goto next_895;
    int call_581 = leadsPat_1(tokens_106);
    match_238 = call_581;
    goto end_match_894;
next_895:;
    if (call_580) goto next_896;
    match_238 = 0;
    goto end_match_894;
next_896:;
    exit(1);
end_match_894:;
    if (match_238) goto next_897;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_270;
    tuple_270.t0 = tokens_106;
    tuple_270.t1 = errors_76;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_582 = parsePatError_1((struct String){.str = "Expected a pattern", .len = 18}, tuple_270);
    match_237 = call_582;
    goto end_match_893;
next_897:;
    if ((!(match_238))) goto next_898;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_271;
    tuple_271.t0 = tokens_106;
    tuple_271.t1 = errors_76;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_583 = parsePatOr_(baseLoc_22, tuple_271);
    match_237 = call_583;
    goto end_match_893;
next_898:;
    exit(1);
end_match_893:;
    return match_237;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseRange_(struct IntIntTuple2 baseLoc_23, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_183) {
    struct Token_IntIntTuple2Tuple2List* tokens_107 = arg_183.t0;
    struct StringIntIntTuple2Tuple2List* errors_77 = arg_183.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_272;
    tuple_272.t0 = tokens_107;
    tuple_272.t1 = errors_77;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_584 = parseExpr_(baseLoc_23, tuple_272);
    struct AExpr_ l_17 = call_584.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_108 = call_584.t1;
    struct StringIntIntTuple2Tuple2List* errors_78 = call_584.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_239;
    if ((!(tokens_108))) goto next_900;
    if ((tokens_108->head.t0.tag != DotDot_)) goto next_900;
    struct IntIntTuple2 loc_54 = tokens_108->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_109 = tokens_108->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_273;
    tuple_273.t0 = tokens_109;
    tuple_273.t1 = errors_78;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_585 = parseExpr_(baseLoc_23, tuple_273);
    struct AExpr_ r_30 = call_585.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_110 = call_585.t1;
    struct StringIntIntTuple2Tuple2List* errors_79 = call_585.t2;
    struct AExpr_List* list_75 = (struct AExpr_List*)malloc(sizeof(struct AExpr_List));
    list_75->head = r_30;
    list_75->tail = NULL;
    struct AExpr_List* list_74 = (struct AExpr_List*)malloc(sizeof(struct AExpr_List));
    list_74->head = l_17;
    list_74->tail = list_75;
    struct AExpr_ListIntIntTuple2Tuple2 tuple_275;
    tuple_275.t0 = list_74;
    tuple_275.t1 = loc_54;
    struct AExpr_ListIntIntTuple2Tuple2* payload_108 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_108))) = tuple_275;
    struct AExpr_ variant_108 = (struct AExpr_){.tag = Range_, .Range_ = payload_108};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_274;
    tuple_274.t0 = variant_108;
    tuple_274.t1 = tokens_110;
    tuple_274.t2 = errors_79;
    match_239 = tuple_274;
    goto end_match_899;
next_900:;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_276;
    tuple_276.t0 = l_17;
    tuple_276.t1 = tokens_108;
    tuple_276.t2 = errors_78;
    match_239 = tuple_276;
    goto end_match_899;
next_901:;
end_match_899:;
    return match_239;
}

struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct AExpr_List* t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseList_(struct IntIntTuple2 baseLoc_24, struct IntIntTuple2 bracketLoc_1, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_184) {
    struct Token_IntIntTuple2Tuple2List* tokens_111 = arg_184.t0;
    struct StringIntIntTuple2Tuple2List* errors_80 = arg_184.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_277;
    tuple_277.t0 = tokens_111;
    tuple_277.t1 = errors_80;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_586 = parseStmts_(baseLoc_24, tuple_277);
    struct AExpr_List* items_6 = call_586.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_112 = call_586.t1;
    struct StringIntIntTuple2Tuple2List* errors_81 = call_586.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 match_240;
    if ((!(tokens_112))) goto next_903;
    if ((tokens_112->head.t0.tag != BracketR_)) goto next_903;
    struct Token_IntIntTuple2Tuple2List* tokens_114 = tokens_112->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_278;
    tuple_278.t0 = tokens_114;
    tuple_278.t1 = errors_81;
    match_240 = tuple_278;
    goto end_match_902;
next_903:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_279;
    tuple_279.t0 = tokens_112;
    tuple_279.t1 = errors_81;
    struct StringIntIntTuple2Tuple2List* call_587 = parseNewError_1((struct String){.str = "Expected \']\'", .len = 12}, tuple_279);
    struct StringIntIntTuple2Tuple2List* errors_83 = call_587;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_280;
    tuple_280.t0 = tokens_112;
    tuple_280.t1 = errors_83;
    match_240 = tuple_280;
    goto end_match_902;
next_904:;
end_match_902:;
    struct Token_IntIntTuple2Tuple2List* tokens_113 = match_240.t0;
    struct StringIntIntTuple2Tuple2List* errors_82 = match_240.t1;
    struct AExpr_ListIntIntTuple2Tuple2 tuple_282;
    tuple_282.t0 = items_6;
    tuple_282.t1 = bracketLoc_1;
    struct AExpr_ListIntIntTuple2Tuple2* payload_109 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_109))) = tuple_282;
    struct AExpr_ variant_109 = (struct AExpr_){.tag = ListLit_1, .ListLit_1 = payload_109};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_281;
    tuple_281.t0 = variant_109;
    tuple_281.t1 = tokens_113;
    tuple_281.t2 = errors_82;
    return tuple_281;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseThenClause_(struct IntIntTuple2 baseLoc_25, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_185) {
    struct Token_IntIntTuple2Tuple2List* tokens_115 = arg_185.t0;
    struct StringIntIntTuple2Tuple2List* errors_84 = arg_185.t1;
    struct IntIntTuple2 call_588 = locAddX_(1, baseLoc_25);
    struct IntIntTuple2 innerBaseLoc_ = call_588;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_241;
    if ((!(tokens_115))) goto next_906;
    if ((tokens_115->head.t0.tag != Then_)) goto next_906;
    struct IntIntTuple2 thenLoc_ = tokens_115->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_116 = tokens_115->tail;
    int call_589 = locInside_(baseLoc_25, thenLoc_);
    if ((!(call_589))) goto next_906;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_283;
    tuple_283.t0 = tokens_116;
    tuple_283.t1 = errors_84;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_590 = parseSemi_(innerBaseLoc_, thenLoc_, tuple_283);
    match_241 = call_590;
    goto end_match_905;
next_906:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_284;
    tuple_284.t0 = tokens_115;
    tuple_284.t1 = errors_84;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_591 = parseExprError_1((struct String){.str = "Expected \'then\'", .len = 15}, tuple_284);
    match_241 = call_591;
    goto end_match_905;
next_907:;
end_match_905:;
    return match_241;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseElseClause_(struct IntIntTuple2 baseLoc_26, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_186) {
    struct Token_IntIntTuple2Tuple2List* tokens_117 = arg_186.t0;
    struct StringIntIntTuple2Tuple2List* errors_85 = arg_186.t1;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_242;
    if ((!(tokens_117))) goto next_909;
    if ((tokens_117->head.t0.tag != Else_)) goto next_909;
    struct IntIntTuple2 elseLoc_ = tokens_117->head.t1;
    if ((!(tokens_117->tail))) goto next_909;
    if ((tokens_117->tail->head.t0.tag != If_)) goto next_909;
    struct IntIntTuple2 nextIfLoc_ = tokens_117->tail->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_118 = tokens_117->tail->tail;
    int match_243;
    int call_592 = locInside_(baseLoc_26, elseLoc_);
    if ((!(call_592))) goto next_913;
    int call_593 = locIsSameRow_(elseLoc_, nextIfLoc_);
    match_243 = call_593;
    goto end_match_912;
next_913:;
    if (call_592) goto next_914;
    match_243 = 0;
    goto end_match_912;
next_914:;
    exit(1);
end_match_912:;
    if ((!(match_243))) goto next_909;
    struct Token_IntIntTuple2Tuple2 tuple_286;
    tuple_286.t0 = (struct Token_){.tag = If_};
    tuple_286.t1 = elseLoc_;
    struct Token_IntIntTuple2Tuple2List* list_76 = (struct Token_IntIntTuple2Tuple2List*)malloc(sizeof(struct Token_IntIntTuple2Tuple2List));
    list_76->head = tuple_286;
    list_76->tail = tokens_118;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_285;
    tuple_285.t0 = list_76;
    tuple_285.t1 = errors_85;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_594 = parseExpr_(baseLoc_26, tuple_285);
    match_242 = call_594;
    goto end_match_908;
next_909:;
    if ((!(tokens_117))) goto next_910;
    if ((tokens_117->head.t0.tag != Else_)) goto next_910;
    struct IntIntTuple2 elseLoc_1 = tokens_117->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_119 = tokens_117->tail;
    int call_595 = locInside_(baseLoc_26, elseLoc_1);
    if ((!(call_595))) goto next_910;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_287;
    tuple_287.t0 = tokens_119;
    tuple_287.t1 = errors_85;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_596 = parseSemi_(baseLoc_26, elseLoc_1, tuple_287);
    match_242 = call_596;
    goto end_match_908;
next_910:;
    struct IntIntTuple2* payload_110 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_110))) = baseLoc_26;
    struct AExpr_ variant_110 = (struct AExpr_){.tag = Missing_2, .Missing_2 = payload_110};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_288;
    tuple_288.t0 = variant_110;
    tuple_288.t1 = tokens_117;
    tuple_288.t2 = errors_85;
    match_242 = tuple_288;
    goto end_match_908;
next_911:;
end_match_908:;
    return match_242;
}

struct AExpr_AExpr_AExpr_IntIntTuple2Tuple4 {
    struct AExpr_ t0;
    struct AExpr_ t1;
    struct AExpr_ t2;
    struct IntIntTuple2 t3;
};

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseIf_(struct IntIntTuple2 ifLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_187) {
    struct Token_IntIntTuple2Tuple2List* tokens_120 = arg_187.t0;
    struct StringIntIntTuple2Tuple2List* errors_86 = arg_187.t1;
    struct IntIntTuple2 call_597 = locAddX_(1, ifLoc_);
    struct IntIntTuple2 innerBaseLoc_1 = call_597;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_289;
    tuple_289.t0 = tokens_120;
    tuple_289.t1 = errors_86;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_598 = parseExpr_(innerBaseLoc_1, tuple_289);
    struct AExpr_ cond_1 = call_598.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_121 = call_598.t1;
    struct StringIntIntTuple2Tuple2List* errors_87 = call_598.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_290;
    tuple_290.t0 = tokens_121;
    tuple_290.t1 = errors_87;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_599 = parseThenClause_(ifLoc_, tuple_290);
    struct AExpr_ body_9 = call_599.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_122 = call_599.t1;
    struct StringIntIntTuple2Tuple2List* errors_88 = call_599.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_291;
    tuple_291.t0 = tokens_122;
    tuple_291.t1 = errors_88;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_600 = parseElseClause_(ifLoc_, tuple_291);
    struct AExpr_ alt_1 = call_600.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_123 = call_600.t1;
    struct StringIntIntTuple2Tuple2List* errors_89 = call_600.t2;
    struct AExpr_AExpr_AExpr_IntIntTuple2Tuple4 tuple_293;
    tuple_293.t0 = cond_1;
    tuple_293.t1 = body_9;
    tuple_293.t2 = alt_1;
    tuple_293.t3 = ifLoc_;
    struct AExpr_AExpr_AExpr_IntIntTuple2Tuple4* payload_111 = (struct AExpr_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct AExpr_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct AExpr_AExpr_AExpr_IntIntTuple2Tuple4*)payload_111))) = tuple_293;
    struct AExpr_ variant_111 = (struct AExpr_){.tag = If_1, .If_1 = payload_111};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_292;
    tuple_292.t0 = variant_111;
    tuple_292.t1 = tokens_123;
    tuple_292.t2 = errors_89;
    return tuple_292;
}

struct APat_AExpr_AExpr_IntIntTuple2Tuple4 {
    struct APat_ t0;
    struct AExpr_ t1;
    struct AExpr_ t2;
    struct IntIntTuple2 t3;
};

struct AArm_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct AArm_ t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct AArm_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseMatchArm_(struct IntIntTuple2 matchLoc_, struct IntIntTuple2 armLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_188) {
    struct Token_IntIntTuple2Tuple2List* tokens_124 = arg_188.t0;
    struct StringIntIntTuple2Tuple2List* errors_90 = arg_188.t1;
    struct IntIntTuple2 call_601 = locAddX_(1, matchLoc_);
    struct IntIntTuple2 innerBaseLoc_2 = call_601;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_294;
    tuple_294.t0 = tokens_124;
    tuple_294.t1 = errors_90;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_602 = parsePat_(innerBaseLoc_2, tuple_294);
    struct APat_ pat_21 = call_602.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_125 = call_602.t1;
    struct StringIntIntTuple2Tuple2List* errors_91 = call_602.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_244;
    if ((!(tokens_125))) goto next_916;
    if ((tokens_125->head.t0.tag != When_)) goto next_916;
    struct Token_IntIntTuple2Tuple2List* tokens_127 = tokens_125->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_295;
    tuple_295.t0 = tokens_127;
    tuple_295.t1 = errors_91;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_603 = parseExpr_(innerBaseLoc_2, tuple_295);
    match_244 = call_603;
    goto end_match_915;
next_916:;
    struct IntIntTuple2 call_604 = nextLoc_1(tokens_125);
    struct IntIntTuple2* payload_112 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_112))) = call_604;
    struct AExpr_ variant_112 = (struct AExpr_){.tag = Missing_2, .Missing_2 = payload_112};
    struct AExpr_ guard_3 = variant_112;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_296;
    tuple_296.t0 = guard_3;
    tuple_296.t1 = tokens_125;
    tuple_296.t2 = errors_91;
    match_244 = tuple_296;
    goto end_match_915;
next_917:;
end_match_915:;
    struct AExpr_ guard_2 = match_244.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_126 = match_244.t1;
    struct StringIntIntTuple2Tuple2List* errors_92 = match_244.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_245;
    if ((!(tokens_126))) goto next_919;
    if ((tokens_126->head.t0.tag != Arrow_)) goto next_919;
    struct IntIntTuple2 arrowLoc_ = tokens_126->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_129 = tokens_126->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_297;
    tuple_297.t0 = tokens_129;
    tuple_297.t1 = errors_92;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_605 = parseSemi_(matchLoc_, arrowLoc_, tuple_297);
    match_245 = call_605;
    goto end_match_918;
next_919:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_298;
    tuple_298.t0 = tokens_126;
    tuple_298.t1 = errors_92;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_606 = parseExprError_1((struct String){.str = "Expected \'->\'", .len = 13}, tuple_298);
    match_245 = call_606;
    goto end_match_918;
next_920:;
end_match_918:;
    struct AExpr_ body_10 = match_245.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_128 = match_245.t1;
    struct StringIntIntTuple2Tuple2List* errors_93 = match_245.t2;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4 tuple_300;
    tuple_300.t0 = pat_21;
    tuple_300.t1 = guard_2;
    tuple_300.t2 = body_10;
    tuple_300.t3 = armLoc_;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4* payload_113 = (struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct APat_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)payload_113))) = tuple_300;
    struct AArm_ variant_113 = (struct AArm_){.tag = AArm_, .AArm_ = payload_113};
    struct AArm_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_299;
    tuple_299.t0 = variant_113;
    tuple_299.t1 = tokens_128;
    tuple_299.t2 = errors_93;
    return tuple_299;
}

struct AArm_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct AArm_List* t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct AArm_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_47(struct IntIntTuple2 matchLoc_1, struct AArm_List* acc_30, struct IntIntTuple2 armLoc_2, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_189) {
    struct Token_IntIntTuple2Tuple2List* tokens_135 = arg_189.t0;
    struct StringIntIntTuple2Tuple2List* errors_98 = arg_189.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_301;
    tuple_301.t0 = tokens_135;
    tuple_301.t1 = errors_98;
    struct AArm_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_607 = parseMatchArm_(matchLoc_1, armLoc_2, tuple_301);
    struct AArm_ arm_ = call_607.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_136 = call_607.t1;
    struct StringIntIntTuple2Tuple2List* errors_99 = call_607.t2;
    struct AArm_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_246;
    if ((!(tokens_136))) goto next_922;
    if ((tokens_136->head.t0.tag != Pipe_)) goto next_922;
    struct IntIntTuple2 pipeLoc_1 = tokens_136->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_137 = tokens_136->tail;
    int call_608 = locInside_(matchLoc_1, pipeLoc_1);
    if ((!(call_608))) goto next_922;
    struct AArm_List* list_77 = (struct AArm_List*)malloc(sizeof(struct AArm_List));
    list_77->head = arm_;
    list_77->tail = acc_30;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_302;
    tuple_302.t0 = tokens_137;
    tuple_302.t1 = errors_99;
    struct AArm_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_609 = go_47(matchLoc_1, list_77, pipeLoc_1, tuple_302);
    match_246 = call_609;
    goto end_match_921;
next_922:;
    struct AArm_List* list_78 = (struct AArm_List*)malloc(sizeof(struct AArm_List));
    list_78->head = arm_;
    list_78->tail = acc_30;
    struct AArm_List* call_610 = listRev_4(list_78);
    struct AArm_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_303;
    tuple_303.t0 = call_610;
    tuple_303.t1 = tokens_136;
    tuple_303.t2 = errors_99;
    match_246 = tuple_303;
    goto end_match_921;
next_923:;
end_match_921:;
    return match_246;
}

struct IntIntTuple2Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct IntIntTuple2 t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct AExpr_AArm_ListIntIntTuple2Tuple3 {
    struct AExpr_ t0;
    struct AArm_List* t1;
    struct IntIntTuple2 t2;
};

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseMatch_(struct IntIntTuple2 matchLoc_1, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_190) {
    struct Token_IntIntTuple2Tuple2List* tokens_130 = arg_190.t0;
    struct StringIntIntTuple2Tuple2List* errors_94 = arg_190.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_304;
    tuple_304.t0 = tokens_130;
    tuple_304.t1 = errors_94;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_611 = parseExpr_(matchLoc_1, tuple_304);
    struct AExpr_ target_3 = call_611.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_131 = call_611.t1;
    struct StringIntIntTuple2Tuple2List* errors_95 = call_611.t2;
    struct IntIntTuple2Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_247;
    if ((!(tokens_131))) goto next_925;
    if ((tokens_131->head.t0.tag != With_)) goto next_925;
    if ((!(tokens_131->tail))) goto next_925;
    if ((tokens_131->tail->head.t0.tag != Pipe_)) goto next_925;
    struct IntIntTuple2 pipeLoc_ = tokens_131->tail->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_133 = tokens_131->tail->tail;
    struct IntIntTuple2Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_305;
    tuple_305.t0 = pipeLoc_;
    tuple_305.t1 = tokens_133;
    tuple_305.t2 = errors_95;
    match_247 = tuple_305;
    goto end_match_924;
next_925:;
    if ((!(tokens_131))) goto next_926;
    if ((tokens_131->head.t0.tag != With_)) goto next_926;
    struct IntIntTuple2 withLoc_ = tokens_131->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_134 = tokens_131->tail;
    struct IntIntTuple2Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_306;
    tuple_306.t0 = withLoc_;
    tuple_306.t1 = tokens_134;
    tuple_306.t2 = errors_95;
    match_247 = tuple_306;
    goto end_match_924;
next_926:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_307;
    tuple_307.t0 = tokens_131;
    tuple_307.t1 = errors_95;
    struct StringIntIntTuple2Tuple2List* call_612 = parseNewError_1((struct String){.str = "Expected \'with\'", .len = 15}, tuple_307);
    struct StringIntIntTuple2Tuple2List* errors_97 = call_612;
    struct IntIntTuple2Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_308;
    tuple_308.t0 = matchLoc_1;
    tuple_308.t1 = tokens_131;
    tuple_308.t2 = errors_97;
    match_247 = tuple_308;
    goto end_match_924;
next_927:;
end_match_924:;
    struct IntIntTuple2 armLoc_1 = match_247.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_132 = match_247.t1;
    struct StringIntIntTuple2Tuple2List* errors_96 = match_247.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_309;
    tuple_309.t0 = tokens_132;
    tuple_309.t1 = errors_96;
    struct AArm_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_613 = go_47(matchLoc_1, NULL, armLoc_1, tuple_309);
    struct AArm_List* arms_3 = call_613.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_138 = call_613.t1;
    struct StringIntIntTuple2Tuple2List* errors_100 = call_613.t2;
    struct AExpr_AArm_ListIntIntTuple2Tuple3 tuple_311;
    tuple_311.t0 = target_3;
    tuple_311.t1 = arms_3;
    tuple_311.t2 = matchLoc_1;
    struct AExpr_AArm_ListIntIntTuple2Tuple3* payload_114 = (struct AExpr_AArm_ListIntIntTuple2Tuple3*)malloc(sizeof(struct AExpr_AArm_ListIntIntTuple2Tuple3));
    (*(((struct AExpr_AArm_ListIntIntTuple2Tuple3*)payload_114))) = tuple_311;
    struct AExpr_ variant_114 = (struct AExpr_){.tag = Match_1, .Match_1 = payload_114};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_310;
    tuple_310.t0 = variant_114;
    tuple_310.t1 = tokens_138;
    tuple_310.t2 = errors_100;
    return tuple_310;
}

struct APat_ListAExpr_IntIntTuple2Tuple3 {
    struct APat_List* t0;
    struct AExpr_ t1;
    struct IntIntTuple2 t2;
};

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseFun_(struct IntIntTuple2 baseLoc_27, struct IntIntTuple2 funLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_191) {
    struct Token_IntIntTuple2Tuple2List* tokens_139 = arg_191.t0;
    struct StringIntIntTuple2Tuple2List* errors_101 = arg_191.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_312;
    tuple_312.t0 = tokens_139;
    tuple_312.t1 = errors_101;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_614 = parsePatCallArgs_(baseLoc_27, funLoc_, tuple_312);
    struct APat_List* pats_3 = call_614.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_140 = call_614.t1;
    struct StringIntIntTuple2Tuple2List* errors_102 = call_614.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_248;
    if ((!(tokens_140))) goto next_929;
    if ((tokens_140->head.t0.tag != Arrow_)) goto next_929;
    struct IntIntTuple2 arrowLoc_1 = tokens_140->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_142 = tokens_140->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_313;
    tuple_313.t0 = tokens_142;
    tuple_313.t1 = errors_102;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_615 = parseSemi_(baseLoc_27, arrowLoc_1, tuple_313);
    match_248 = call_615;
    goto end_match_928;
next_929:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_314;
    tuple_314.t0 = tokens_140;
    tuple_314.t1 = errors_102;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_616 = parseExprError_1((struct String){.str = "Missing \'->\'", .len = 12}, tuple_314);
    match_248 = call_616;
    goto end_match_928;
next_930:;
end_match_928:;
    struct AExpr_ body_11 = match_248.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_141 = match_248.t1;
    struct StringIntIntTuple2Tuple2List* errors_103 = match_248.t2;
    struct APat_ListAExpr_IntIntTuple2Tuple3 tuple_316;
    tuple_316.t0 = pats_3;
    tuple_316.t1 = body_11;
    tuple_316.t2 = funLoc_;
    struct APat_ListAExpr_IntIntTuple2Tuple3* payload_115 = (struct APat_ListAExpr_IntIntTuple2Tuple3*)malloc(sizeof(struct APat_ListAExpr_IntIntTuple2Tuple3));
    (*(((struct APat_ListAExpr_IntIntTuple2Tuple3*)payload_115))) = tuple_316;
    struct AExpr_ variant_115 = (struct AExpr_){.tag = Fun_3, .Fun_3 = payload_115};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_315;
    tuple_315.t0 = variant_115;
    tuple_315.t1 = tokens_141;
    tuple_315.t2 = errors_103;
    return tuple_315;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseParenBody_(struct IntIntTuple2 baseLoc_28, struct IntIntTuple2 parenLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_192) {
    struct Token_IntIntTuple2Tuple2List* tokens_143 = arg_192.t0;
    struct StringIntIntTuple2Tuple2List* errors_104 = arg_192.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_317;
    tuple_317.t0 = tokens_143;
    tuple_317.t1 = errors_104;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_617 = parseSemi_(baseLoc_28, parenLoc_, tuple_317);
    struct AExpr_ body_12 = call_617.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_144 = call_617.t1;
    struct StringIntIntTuple2Tuple2List* errors_105 = call_617.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_249;
    if ((!(tokens_144))) goto next_932;
    if ((tokens_144->head.t0.tag != ParenR_)) goto next_932;
    struct Token_IntIntTuple2Tuple2List* tokens_145 = tokens_144->tail;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_318;
    tuple_318.t0 = body_12;
    tuple_318.t1 = tokens_145;
    tuple_318.t2 = errors_105;
    match_249 = tuple_318;
    goto end_match_931;
next_932:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_319;
    tuple_319.t0 = tokens_144;
    tuple_319.t1 = errors_105;
    struct StringIntIntTuple2Tuple2List* call_618 = parseNewError_1((struct String){.str = "Expected \')\'", .len = 12}, tuple_319);
    struct StringIntIntTuple2Tuple2List* errors_106 = call_618;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_320;
    tuple_320.t0 = body_12;
    tuple_320.t1 = tokens_144;
    tuple_320.t2 = errors_106;
    match_249 = tuple_320;
    goto end_match_931;
next_933:;
end_match_931:;
    return match_249;
}

struct Token_IntIntTuple2Tuple2List* parseAccessModifier_1(struct Token_IntIntTuple2Tuple2List* tokens_146) {
    struct Token_IntIntTuple2Tuple2List* match_250;
    if ((!(tokens_146))) goto next_935;
    struct Token_ t_12 = tokens_146->head.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_147 = tokens_146->tail;
    int call_619 = tokenIsAccessModifier_(t_12);
    if ((!(call_619))) goto next_935;
    match_250 = tokens_147;
    goto end_match_934;
next_935:;
    match_250 = tokens_146;
    goto end_match_934;
next_936:;
end_match_934:;
    return match_250;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseLet_(struct IntIntTuple2 letLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_193) {
    struct Token_IntIntTuple2Tuple2List* tokens_148 = arg_193.t0;
    struct StringIntIntTuple2Tuple2List* errors_107 = arg_193.t1;
    struct IntIntTuple2 call_620 = locAddX_(1, letLoc_);
    struct IntIntTuple2 innerBaseLoc_3 = call_620;
    struct Token_IntIntTuple2Tuple2List* call_621 = parseAccessModifier_1(tokens_148);
    struct Token_IntIntTuple2Tuple2List* tokens_149 = call_621;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_321;
    tuple_321.t0 = tokens_149;
    tuple_321.t1 = errors_107;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_622 = parsePatLet_(innerBaseLoc_3, tuple_321);
    struct APat_ pat_22 = call_622.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_150 = call_622.t1;
    struct StringIntIntTuple2Tuple2List* errors_108 = call_622.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_251;
    if ((!(tokens_150))) goto next_938;
    if ((tokens_150->head.t0.tag != Eq_)) goto next_938;
    struct IntIntTuple2 eqLoc_ = tokens_150->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_152 = tokens_150->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_322;
    tuple_322.t0 = tokens_152;
    tuple_322.t1 = errors_108;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_623 = parseSemi_(innerBaseLoc_3, eqLoc_, tuple_322);
    match_251 = call_623;
    goto end_match_937;
next_938:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_323;
    tuple_323.t0 = tokens_150;
    tuple_323.t1 = errors_108;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_624 = parseExprError_1((struct String){.str = "Missing \'=\'", .len = 11}, tuple_323);
    match_251 = call_624;
    goto end_match_937;
next_939:;
end_match_937:;
    struct AExpr_ body_13 = match_251.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_151 = match_251.t1;
    struct StringIntIntTuple2Tuple2List* errors_109 = match_251.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_252;
    if ((!(tokens_151))) goto next_941;
    if ((tokens_151->head.t0.tag != In_)) goto next_941;
    struct IntIntTuple2 inLoc_ = tokens_151->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_154 = tokens_151->tail;
    int call_625 = locInside_(letLoc_, inLoc_);
    if ((!(call_625))) goto next_941;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_324;
    tuple_324.t0 = tokens_154;
    tuple_324.t1 = errors_109;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_626 = parseSemi_(letLoc_, inLoc_, tuple_324);
    match_252 = call_626;
    goto end_match_940;
next_941:;
    if ((!(tokens_151))) goto next_942;
    struct IntIntTuple2 call_627 = nextLoc_1(tokens_151);
    int call_628 = locIsSameColumn_(call_627, letLoc_);
    if ((!(call_628))) goto next_942;
    struct IntIntTuple2 call_629 = nextLoc_1(tokens_151);
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_325;
    tuple_325.t0 = tokens_151;
    tuple_325.t1 = errors_109;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_630 = parseSemi_(letLoc_, call_629, tuple_325);
    match_252 = call_630;
    goto end_match_940;
next_942:;
    struct Token_IntIntTuple2Tuple2List* tokens_155 = tokens_151;
    struct AExpr_ListIntIntTuple2Tuple2 tuple_327;
    tuple_327.t0 = NULL;
    tuple_327.t1 = letLoc_;
    struct AExpr_ListIntIntTuple2Tuple2* payload_116 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_116))) = tuple_327;
    struct AExpr_ variant_116 = (struct AExpr_){.tag = TupleLit_1, .TupleLit_1 = payload_116};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_326;
    tuple_326.t0 = variant_116;
    tuple_326.t1 = tokens_155;
    tuple_326.t2 = errors_109;
    match_252 = tuple_326;
    goto end_match_940;
next_943:;
end_match_940:;
    struct AExpr_ next_11 = match_252.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_153 = match_252.t1;
    struct StringIntIntTuple2Tuple2List* errors_110 = match_252.t2;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4 tuple_329;
    tuple_329.t0 = pat_22;
    tuple_329.t1 = body_13;
    tuple_329.t2 = next_11;
    tuple_329.t3 = letLoc_;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4* payload_117 = (struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct APat_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)payload_117))) = tuple_329;
    struct AExpr_ variant_117 = (struct AExpr_){.tag = Let_1, .Let_1 = payload_117};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_328;
    tuple_328.t0 = variant_117;
    tuple_328.t1 = tokens_153;
    tuple_328.t2 = errors_110;
    return tuple_328;
}

struct StringATy_IntIntTuple2Tuple3 {
    struct String t0;
    struct ATy_ t1;
    struct IntIntTuple2 t2;
};

struct StringAVariant_ListIntIntTuple2Tuple3 {
    struct String t0;
    struct AVariant_List* t1;
    struct IntIntTuple2 t2;
};

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyDecl_(struct IntIntTuple2 typeLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_194) {
    struct Token_IntIntTuple2Tuple2List* tokens_156 = arg_194.t0;
    struct StringIntIntTuple2Tuple2List* errors_111 = arg_194.t1;
    struct IntIntTuple2 call_631 = locAddX_(1, typeLoc_);
    struct IntIntTuple2 baseLoc_29 = call_631;
    struct Token_IntIntTuple2Tuple2List* call_632 = parseAccessModifier_1(tokens_156);
    struct Token_IntIntTuple2Tuple2List* tokens_157 = call_632;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_253;
    if ((!(tokens_157))) goto next_945;
    if ((tokens_157->head.t0.tag != Ident_)) goto next_945;
    struct String tyIdent_ = (*(tokens_157->head.t0.Ident_));
    struct Token_IntIntTuple2Tuple2List* tokens_158 = tokens_157->tail;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_254;
    if ((!(tokens_158))) goto next_948;
    if ((tokens_158->head.t0.tag != Eq_)) goto next_948;
    struct Token_IntIntTuple2Tuple2List* tokens_159 = tokens_158->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_330;
    tuple_330.t0 = tokens_159;
    tuple_330.t1 = errors_111;
    struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_633 = parseTyDeclBody_(baseLoc_29, tuple_330);
    struct ATyDecl_ tyDecl_ = call_633.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_160 = call_633.t1;
    struct StringIntIntTuple2Tuple2List* errors_112 = call_633.t2;
    struct AExpr_ match_255;
    if ((tyDecl_.tag != Synonym_)) goto next_951;
    struct ATy_ ty_52 = (*(tyDecl_.Synonym_));
    struct StringATy_IntIntTuple2Tuple3 tuple_331;
    tuple_331.t0 = tyIdent_;
    tuple_331.t1 = ty_52;
    tuple_331.t2 = typeLoc_;
    struct StringATy_IntIntTuple2Tuple3* payload_118 = (struct StringATy_IntIntTuple2Tuple3*)malloc(sizeof(struct StringATy_IntIntTuple2Tuple3));
    (*(((struct StringATy_IntIntTuple2Tuple3*)payload_118))) = tuple_331;
    struct AExpr_ variant_118 = (struct AExpr_){.tag = TySynonym_, .TySynonym_ = payload_118};
    match_255 = variant_118;
    goto end_match_950;
next_951:;
    if ((tyDecl_.tag != Union_)) goto next_952;
    struct AVariant_List* variants_2 = (*(tyDecl_.Union_));
    struct StringAVariant_ListIntIntTuple2Tuple3 tuple_332;
    tuple_332.t0 = tyIdent_;
    tuple_332.t1 = variants_2;
    tuple_332.t2 = typeLoc_;
    struct StringAVariant_ListIntIntTuple2Tuple3* payload_119 = (struct StringAVariant_ListIntIntTuple2Tuple3*)malloc(sizeof(struct StringAVariant_ListIntIntTuple2Tuple3));
    (*(((struct StringAVariant_ListIntIntTuple2Tuple3*)payload_119))) = tuple_332;
    struct AExpr_ variant_119 = (struct AExpr_){.tag = TyUnion_, .TyUnion_ = payload_119};
    match_255 = variant_119;
    goto end_match_950;
next_952:;
    exit(1);
end_match_950:;
    struct AExpr_ expr_11 = match_255;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_333;
    tuple_333.t0 = expr_11;
    tuple_333.t1 = tokens_160;
    tuple_333.t2 = errors_112;
    match_254 = tuple_333;
    goto end_match_947;
next_948:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_334;
    tuple_334.t0 = tokens_158;
    tuple_334.t1 = errors_111;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_634 = parseTyError_1((struct String){.str = "Expected \'=\'", .len = 12}, tuple_334);
    struct ATy_ ty_53 = call_634.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_161 = call_634.t1;
    struct StringIntIntTuple2Tuple2List* errors_113 = call_634.t2;
    struct StringATy_IntIntTuple2Tuple3 tuple_336;
    tuple_336.t0 = tyIdent_;
    tuple_336.t1 = ty_53;
    tuple_336.t2 = typeLoc_;
    struct StringATy_IntIntTuple2Tuple3* payload_120 = (struct StringATy_IntIntTuple2Tuple3*)malloc(sizeof(struct StringATy_IntIntTuple2Tuple3));
    (*(((struct StringATy_IntIntTuple2Tuple3*)payload_120))) = tuple_336;
    struct AExpr_ variant_120 = (struct AExpr_){.tag = TySynonym_, .TySynonym_ = payload_120};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_335;
    tuple_335.t0 = variant_120;
    tuple_335.t1 = tokens_161;
    tuple_335.t2 = errors_113;
    match_254 = tuple_335;
    goto end_match_947;
next_949:;
end_match_947:;
    match_253 = match_254;
    goto end_match_944;
next_945:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_337;
    tuple_337.t0 = tokens_157;
    tuple_337.t1 = errors_111;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_635 = parseExprError_1((struct String){.str = "Expected identifier", .len = 19}, tuple_337);
    match_253 = call_635;
    goto end_match_944;
next_946:;
end_match_944:;
    return match_253;
}

struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct StringList* t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_48(struct StringList* acc_31, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_195) {
    struct Token_IntIntTuple2Tuple2List* tokens_164 = arg_195.t0;
    struct StringIntIntTuple2Tuple2List* errors_116 = arg_195.t1;
    struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_256;
    if ((!(tokens_164))) goto next_954;
    if ((tokens_164->head.t0.tag != Dot_)) goto next_954;
    if ((!(tokens_164->tail))) goto next_954;
    if ((tokens_164->tail->head.t0.tag != Ident_)) goto next_954;
    struct String ident_23 = (*(tokens_164->tail->head.t0.Ident_));
    struct Token_IntIntTuple2Tuple2List* tokens_165 = tokens_164->tail->tail;
    struct StringList* list_79 = (struct StringList*)malloc(sizeof(struct StringList));
    list_79->head = ident_23;
    list_79->tail = acc_31;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_338;
    tuple_338.t0 = tokens_165;
    tuple_338.t1 = errors_116;
    struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_636 = go_48(list_79, tuple_338);
    match_256 = call_636;
    goto end_match_953;
next_954:;
    if ((!(tokens_164))) goto next_955;
    if ((tokens_164->head.t0.tag != Dot_)) goto next_955;
    struct Token_IntIntTuple2Tuple2List* tokens_166 = tokens_164->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_339;
    tuple_339.t0 = tokens_166;
    tuple_339.t1 = errors_116;
    struct StringIntIntTuple2Tuple2List* call_637 = parseNewError_1((struct String){.str = "Expected identifier", .len = 19}, tuple_339);
    struct StringIntIntTuple2Tuple2List* errors_117 = call_637;
    struct StringList* call_638 = listRev_3(acc_31);
    struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_340;
    tuple_340.t0 = call_638;
    tuple_340.t1 = tokens_166;
    tuple_340.t2 = errors_117;
    match_256 = tuple_340;
    goto end_match_953;
next_955:;
    struct StringList* call_639 = listRev_3(acc_31);
    struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_341;
    tuple_341.t0 = call_639;
    tuple_341.t1 = tokens_164;
    tuple_341.t2 = errors_116;
    match_256 = tuple_341;
    goto end_match_953;
next_956:;
end_match_953:;
    return match_256;
}

struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePath_(struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_196) {
    struct Token_IntIntTuple2Tuple2List* tokens_163 = arg_196.t0;
    struct StringIntIntTuple2Tuple2List* errors_115 = arg_196.t1;
    struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_257;
    if ((!(tokens_163))) goto next_958;
    if ((tokens_163->head.t0.tag != Ident_)) goto next_958;
    struct String ident_24 = (*(tokens_163->head.t0.Ident_));
    struct Token_IntIntTuple2Tuple2List* tokens_167 = tokens_163->tail;
    struct StringList* list_80 = (struct StringList*)malloc(sizeof(struct StringList));
    list_80->head = ident_24;
    list_80->tail = NULL;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_342;
    tuple_342.t0 = tokens_167;
    tuple_342.t1 = errors_115;
    struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_640 = go_48(list_80, tuple_342);
    match_257 = call_640;
    goto end_match_957;
next_958:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_343;
    tuple_343.t0 = tokens_163;
    tuple_343.t1 = errors_115;
    struct StringIntIntTuple2Tuple2List* call_641 = parseNewError_1((struct String){.str = "Expected identifier", .len = 19}, tuple_343);
    struct StringIntIntTuple2Tuple2List* errors_118 = call_641;
    struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_344;
    tuple_344.t0 = NULL;
    tuple_344.t1 = tokens_163;
    tuple_344.t2 = errors_118;
    match_257 = tuple_344;
    goto end_match_957;
next_959:;
end_match_957:;
    return match_257;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseOpen_(struct IntIntTuple2 openLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_197) {
    struct Token_IntIntTuple2Tuple2List* tokens_162 = arg_197.t0;
    struct StringIntIntTuple2Tuple2List* errors_114 = arg_197.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_345;
    tuple_345.t0 = tokens_162;
    tuple_345.t1 = errors_114;
    struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_642 = parsePath_(tuple_345);
    struct StringList* path_3 = call_642.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_168 = call_642.t1;
    struct StringIntIntTuple2Tuple2List* errors_119 = call_642.t2;
    struct StringListIntIntTuple2Tuple2 tuple_347;
    tuple_347.t0 = path_3;
    tuple_347.t1 = openLoc_;
    struct StringListIntIntTuple2Tuple2* payload_121 = (struct StringListIntIntTuple2Tuple2*)malloc(sizeof(struct StringListIntIntTuple2Tuple2));
    (*(((struct StringListIntIntTuple2Tuple2*)payload_121))) = tuple_347;
    struct AExpr_ variant_121 = (struct AExpr_){.tag = Open_1, .Open_1 = payload_121};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_346;
    tuple_346.t0 = variant_121;
    tuple_346.t1 = tokens_168;
    tuple_346.t2 = errors_119;
    return tuple_346;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseAtom_(struct IntIntTuple2 baseLoc_30, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_198) {
    struct Token_IntIntTuple2Tuple2List* tokens_169 = arg_198.t0;
    struct StringIntIntTuple2Tuple2List* errors_120 = arg_198.t1;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_258;
    int call_643 = nextInside_1(baseLoc_30, tokens_169);
    if (call_643) goto next_961;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_348;
    tuple_348.t0 = tokens_169;
    tuple_348.t1 = errors_120;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_644 = parseExprError_1((struct String){.str = "Expected an expression", .len = 22}, tuple_348);
    match_258 = call_644;
    goto end_match_960;
next_961:;
    if ((!(tokens_169))) goto next_962;
    if ((tokens_169->head.t0.tag != ParenL_)) goto next_962;
    struct IntIntTuple2 loc_55 = tokens_169->head.t1;
    if ((!(tokens_169->tail))) goto next_962;
    if ((tokens_169->tail->head.t0.tag != ParenR_)) goto next_962;
    struct Token_IntIntTuple2Tuple2List* tokens_170 = tokens_169->tail->tail;
    struct AExpr_ListIntIntTuple2Tuple2 tuple_350;
    tuple_350.t0 = NULL;
    tuple_350.t1 = loc_55;
    struct AExpr_ListIntIntTuple2Tuple2* payload_122 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_122))) = tuple_350;
    struct AExpr_ variant_122 = (struct AExpr_){.tag = TupleLit_1, .TupleLit_1 = payload_122};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_349;
    tuple_349.t0 = variant_122;
    tuple_349.t1 = tokens_170;
    tuple_349.t2 = errors_120;
    match_258 = tuple_349;
    goto end_match_960;
next_962:;
    if ((!(tokens_169))) goto next_963;
    if ((tokens_169->head.t0.tag != Bool_1)) goto next_963;
    int value_16 = (*(tokens_169->head.t0.Bool_1));
    struct IntIntTuple2 loc_56 = tokens_169->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_171 = tokens_169->tail;
    int* payload_123 = (int*)malloc(sizeof(int));
    (*(((int*)payload_123))) = value_16;
    struct Lit_ variant_123 = (struct Lit_){.tag = Bool_, .Bool_ = payload_123};
    struct Lit_IntIntTuple2Tuple2 tuple_352;
    tuple_352.t0 = variant_123;
    tuple_352.t1 = loc_56;
    struct Lit_IntIntTuple2Tuple2* payload_124 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_124))) = tuple_352;
    struct AExpr_ variant_124 = (struct AExpr_){.tag = Lit_1, .Lit_1 = payload_124};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_351;
    tuple_351.t0 = variant_124;
    tuple_351.t1 = tokens_171;
    tuple_351.t2 = errors_120;
    match_258 = tuple_351;
    goto end_match_960;
next_963:;
    if ((!(tokens_169))) goto next_964;
    if ((tokens_169->head.t0.tag != Int_1)) goto next_964;
    int value_17 = (*(tokens_169->head.t0.Int_1));
    struct IntIntTuple2 loc_57 = tokens_169->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_172 = tokens_169->tail;
    int* payload_125 = (int*)malloc(sizeof(int));
    (*(((int*)payload_125))) = value_17;
    struct Lit_ variant_125 = (struct Lit_){.tag = Int_, .Int_ = payload_125};
    struct Lit_IntIntTuple2Tuple2 tuple_354;
    tuple_354.t0 = variant_125;
    tuple_354.t1 = loc_57;
    struct Lit_IntIntTuple2Tuple2* payload_126 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_126))) = tuple_354;
    struct AExpr_ variant_126 = (struct AExpr_){.tag = Lit_1, .Lit_1 = payload_126};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_353;
    tuple_353.t0 = variant_126;
    tuple_353.t1 = tokens_172;
    tuple_353.t2 = errors_120;
    match_258 = tuple_353;
    goto end_match_960;
next_964:;
    if ((!(tokens_169))) goto next_965;
    if ((tokens_169->head.t0.tag != Char_1)) goto next_965;
    char value_18 = (*(tokens_169->head.t0.Char_1));
    struct IntIntTuple2 loc_58 = tokens_169->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_173 = tokens_169->tail;
    char* payload_127 = (char*)malloc(sizeof(char));
    (*(((char*)payload_127))) = value_18;
    struct Lit_ variant_127 = (struct Lit_){.tag = Char_, .Char_ = payload_127};
    struct Lit_IntIntTuple2Tuple2 tuple_356;
    tuple_356.t0 = variant_127;
    tuple_356.t1 = loc_58;
    struct Lit_IntIntTuple2Tuple2* payload_128 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_128))) = tuple_356;
    struct AExpr_ variant_128 = (struct AExpr_){.tag = Lit_1, .Lit_1 = payload_128};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_355;
    tuple_355.t0 = variant_128;
    tuple_355.t1 = tokens_173;
    tuple_355.t2 = errors_120;
    match_258 = tuple_355;
    goto end_match_960;
next_965:;
    if ((!(tokens_169))) goto next_966;
    if ((tokens_169->head.t0.tag != Str_1)) goto next_966;
    struct String value_19 = (*(tokens_169->head.t0.Str_1));
    struct IntIntTuple2 loc_59 = tokens_169->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_174 = tokens_169->tail;
    struct String* payload_129 = (struct String*)malloc(sizeof(struct String));
    (*(((struct String*)payload_129))) = value_19;
    struct Lit_ variant_129 = (struct Lit_){.tag = Str_, .Str_ = payload_129};
    struct Lit_IntIntTuple2Tuple2 tuple_358;
    tuple_358.t0 = variant_129;
    tuple_358.t1 = loc_59;
    struct Lit_IntIntTuple2Tuple2* payload_130 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_130))) = tuple_358;
    struct AExpr_ variant_130 = (struct AExpr_){.tag = Lit_1, .Lit_1 = payload_130};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_357;
    tuple_357.t0 = variant_130;
    tuple_357.t1 = tokens_174;
    tuple_357.t2 = errors_120;
    match_258 = tuple_357;
    goto end_match_960;
next_966:;
    if ((!(tokens_169))) goto next_967;
    if ((tokens_169->head.t0.tag != Ident_)) goto next_967;
    struct String ident_25 = (*(tokens_169->head.t0.Ident_));
    struct IntIntTuple2 loc_60 = tokens_169->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_175 = tokens_169->tail;
    struct StringIntIntTuple2Tuple2 tuple_360;
    tuple_360.t0 = ident_25;
    tuple_360.t1 = loc_60;
    struct StringIntIntTuple2Tuple2* payload_131 = (struct StringIntIntTuple2Tuple2*)malloc(sizeof(struct StringIntIntTuple2Tuple2));
    (*(((struct StringIntIntTuple2Tuple2*)payload_131))) = tuple_360;
    struct AExpr_ variant_131 = (struct AExpr_){.tag = Ident_2, .Ident_2 = payload_131};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_359;
    tuple_359.t0 = variant_131;
    tuple_359.t1 = tokens_175;
    tuple_359.t2 = errors_120;
    match_258 = tuple_359;
    goto end_match_960;
next_967:;
    if ((!(tokens_169))) goto next_968;
    if ((tokens_169->head.t0.tag != ParenL_)) goto next_968;
    struct IntIntTuple2 parenLoc_1 = tokens_169->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_176 = tokens_169->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_361;
    tuple_361.t0 = tokens_176;
    tuple_361.t1 = errors_120;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_645 = parseParenBody_(baseLoc_30, parenLoc_1, tuple_361);
    match_258 = call_645;
    goto end_match_960;
next_968:;
    if ((!(tokens_169))) goto next_969;
    if ((tokens_169->head.t0.tag != BracketL_)) goto next_969;
    struct IntIntTuple2 bracketLoc_2 = tokens_169->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_177 = tokens_169->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_362;
    tuple_362.t0 = tokens_177;
    tuple_362.t1 = errors_120;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_646 = parseList_(baseLoc_30, bracketLoc_2, tuple_362);
    match_258 = call_646;
    goto end_match_960;
next_969:;
    if ((!(tokens_169))) goto next_970;
    if ((tokens_169->head.t0.tag != If_)) goto next_970;
    struct IntIntTuple2 loc_61 = tokens_169->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_178 = tokens_169->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_363;
    tuple_363.t0 = tokens_178;
    tuple_363.t1 = errors_120;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_647 = parseIf_(loc_61, tuple_363);
    match_258 = call_647;
    goto end_match_960;
next_970:;
    if ((!(tokens_169))) goto next_971;
    if ((tokens_169->head.t0.tag != Match_)) goto next_971;
    struct IntIntTuple2 loc_62 = tokens_169->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_179 = tokens_169->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_364;
    tuple_364.t0 = tokens_179;
    tuple_364.t1 = errors_120;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_648 = parseMatch_(loc_62, tuple_364);
    match_258 = call_648;
    goto end_match_960;
next_971:;
    if ((!(tokens_169))) goto next_972;
    if ((tokens_169->head.t0.tag != Fun_)) goto next_972;
    struct IntIntTuple2 loc_63 = tokens_169->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_180 = tokens_169->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_365;
    tuple_365.t0 = tokens_180;
    tuple_365.t1 = errors_120;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_649 = parseFun_(baseLoc_30, loc_63, tuple_365);
    match_258 = call_649;
    goto end_match_960;
next_972:;
    if ((!(tokens_169))) goto next_973;
    if ((tokens_169->head.t0.tag != Let_)) goto next_973;
    struct IntIntTuple2 letLoc_1 = tokens_169->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_181 = tokens_169->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_366;
    tuple_366.t0 = tokens_181;
    tuple_366.t1 = errors_120;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_650 = parseLet_(letLoc_1, tuple_366);
    match_258 = call_650;
    goto end_match_960;
next_973:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_367;
    tuple_367.t0 = tokens_169;
    tuple_367.t1 = errors_120;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_651 = parseExprError_1((struct String){.str = "Expected an expression", .len = 22}, tuple_367);
    match_258 = call_651;
    goto end_match_960;
next_974:;
end_match_960:;
    return match_258;
}

struct AExpr_AExpr_IntIntTuple2Tuple3 {
    struct AExpr_ t0;
    struct AExpr_ t1;
    struct IntIntTuple2 t2;
};

struct AExpr_StringIntIntTuple2Tuple3 {
    struct AExpr_ t0;
    struct String t1;
    struct IntIntTuple2 t2;
};

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_49(struct IntIntTuple2 baseLoc_31, struct AExpr_ acc_32, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_199) {
    struct Token_IntIntTuple2Tuple2List* tokens_184 = arg_199.t0;
    struct StringIntIntTuple2Tuple2List* errors_123 = arg_199.t1;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_259;
    if ((!(tokens_184))) goto next_976;
    if ((tokens_184->head.t0.tag != Dot_)) goto next_976;
    struct IntIntTuple2 loc_64 = tokens_184->head.t1;
    if ((!(tokens_184->tail))) goto next_976;
    if ((tokens_184->tail->head.t0.tag != BracketL_)) goto next_976;
    struct Token_IntIntTuple2Tuple2List* tokens_185 = tokens_184->tail->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_368;
    tuple_368.t0 = tokens_185;
    tuple_368.t1 = errors_123;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_652 = parseRange_(baseLoc_31, tuple_368);
    struct AExpr_ r_31 = call_652.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_186 = call_652.t1;
    struct StringIntIntTuple2Tuple2List* errors_124 = call_652.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 match_260;
    if ((!(tokens_186))) goto next_981;
    if ((tokens_186->head.t0.tag != BracketR_)) goto next_981;
    struct Token_IntIntTuple2Tuple2List* tokens_188 = tokens_186->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_369;
    tuple_369.t0 = tokens_188;
    tuple_369.t1 = errors_124;
    match_260 = tuple_369;
    goto end_match_980;
next_981:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_370;
    tuple_370.t0 = tokens_186;
    tuple_370.t1 = errors_124;
    struct StringIntIntTuple2Tuple2List* call_653 = parseNewError_1((struct String){.str = "Expected closing \']\'", .len = 20}, tuple_370);
    struct StringIntIntTuple2Tuple2List* errors_126 = call_653;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_371;
    tuple_371.t0 = tokens_186;
    tuple_371.t1 = errors_126;
    match_260 = tuple_371;
    goto end_match_980;
next_982:;
end_match_980:;
    struct Token_IntIntTuple2Tuple2List* tokens_187 = match_260.t0;
    struct StringIntIntTuple2Tuple2List* errors_125 = match_260.t1;
    struct AExpr_AExpr_IntIntTuple2Tuple3 tuple_372;
    tuple_372.t0 = acc_32;
    tuple_372.t1 = r_31;
    tuple_372.t2 = loc_64;
    struct AExpr_AExpr_IntIntTuple2Tuple3* payload_132 = (struct AExpr_AExpr_IntIntTuple2Tuple3*)malloc(sizeof(struct AExpr_AExpr_IntIntTuple2Tuple3));
    (*(((struct AExpr_AExpr_IntIntTuple2Tuple3*)payload_132))) = tuple_372;
    struct AExpr_ variant_132 = (struct AExpr_){.tag = Index_, .Index_ = payload_132};
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_373;
    tuple_373.t0 = tokens_187;
    tuple_373.t1 = errors_125;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_654 = go_49(baseLoc_31, variant_132, tuple_373);
    match_259 = call_654;
    goto end_match_975;
next_976:;
    if ((!(tokens_184))) goto next_977;
    if ((tokens_184->head.t0.tag != Dot_)) goto next_977;
    struct IntIntTuple2 loc_65 = tokens_184->head.t1;
    if ((!(tokens_184->tail))) goto next_977;
    if ((tokens_184->tail->head.t0.tag != Ident_)) goto next_977;
    struct String r_32 = (*(tokens_184->tail->head.t0.Ident_));
    struct Token_IntIntTuple2Tuple2List* tokens_189 = tokens_184->tail->tail;
    struct AExpr_StringIntIntTuple2Tuple3 tuple_374;
    tuple_374.t0 = acc_32;
    tuple_374.t1 = r_32;
    tuple_374.t2 = loc_65;
    struct AExpr_StringIntIntTuple2Tuple3* payload_133 = (struct AExpr_StringIntIntTuple2Tuple3*)malloc(sizeof(struct AExpr_StringIntIntTuple2Tuple3));
    (*(((struct AExpr_StringIntIntTuple2Tuple3*)payload_133))) = tuple_374;
    struct AExpr_ variant_133 = (struct AExpr_){.tag = Nav_1, .Nav_1 = payload_133};
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_375;
    tuple_375.t0 = tokens_189;
    tuple_375.t1 = errors_123;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_655 = go_49(baseLoc_31, variant_133, tuple_375);
    match_259 = call_655;
    goto end_match_975;
next_977:;
    if ((!(tokens_184))) goto next_978;
    if ((tokens_184->head.t0.tag != Dot_)) goto next_978;
    struct Token_IntIntTuple2Tuple2List* tokens_190 = tokens_184->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_376;
    tuple_376.t0 = tokens_190;
    tuple_376.t1 = errors_123;
    struct StringIntIntTuple2Tuple2List* call_656 = parseNewError_1((struct String){.str = "Expected .[] or .field", .len = 22}, tuple_376);
    struct StringIntIntTuple2Tuple2List* errors_127 = call_656;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_377;
    tuple_377.t0 = acc_32;
    tuple_377.t1 = tokens_190;
    tuple_377.t2 = errors_127;
    match_259 = tuple_377;
    goto end_match_975;
next_978:;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_378;
    tuple_378.t0 = acc_32;
    tuple_378.t1 = tokens_184;
    tuple_378.t2 = errors_123;
    match_259 = tuple_378;
    goto end_match_975;
next_979:;
end_match_975:;
    return match_259;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseSuffix_(struct IntIntTuple2 baseLoc_31, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_200) {
    struct Token_IntIntTuple2Tuple2List* tokens_182 = arg_200.t0;
    struct StringIntIntTuple2Tuple2List* errors_121 = arg_200.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_379;
    tuple_379.t0 = tokens_182;
    tuple_379.t1 = errors_121;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_657 = parseAtom_(baseLoc_31, tuple_379);
    struct AExpr_ l_18 = call_657.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_183 = call_657.t1;
    struct StringIntIntTuple2Tuple2List* errors_122 = call_657.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_380;
    tuple_380.t0 = tokens_183;
    tuple_380.t1 = errors_122;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_658 = go_49(baseLoc_31, l_18, tuple_380);
    return call_658;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_50(struct IntIntTuple2 argBaseLoc_1, struct IntIntTuple2 calleeLoc_3, struct IntIntTuple2 baseLoc_32, struct AExpr_ callee_8, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_201) {
    struct Token_IntIntTuple2Tuple2List* tokens_193 = arg_201.t0;
    struct StringIntIntTuple2Tuple2List* errors_130 = arg_201.t1;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_261;
    int match_262;
    int call_659 = nextInside_1(argBaseLoc_1, tokens_193);
    if ((!(call_659))) goto next_985;
    int call_660 = leadsArg_1(tokens_193);
    match_262 = call_660;
    goto end_match_984;
next_985:;
    if (call_659) goto next_986;
    match_262 = 0;
    goto end_match_984;
next_986:;
    exit(1);
end_match_984:;
    if ((!(match_262))) goto next_987;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_381;
    tuple_381.t0 = tokens_193;
    tuple_381.t1 = errors_130;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_661 = parseSuffix_(baseLoc_32, tuple_381);
    struct AExpr_ arg_2 = call_661.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_194 = call_661.t1;
    struct StringIntIntTuple2Tuple2List* errors_131 = call_661.t2;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_382;
    tuple_382.t0 = (struct Op_){.tag = App_};
    tuple_382.t1 = callee_8;
    tuple_382.t2 = arg_2;
    tuple_382.t3 = calleeLoc_3;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_134 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_134))) = tuple_382;
    struct AExpr_ variant_134 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_134};
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_383;
    tuple_383.t0 = tokens_194;
    tuple_383.t1 = errors_131;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_662 = go_50(argBaseLoc_1, calleeLoc_3, baseLoc_32, variant_134, tuple_383);
    match_261 = call_662;
    goto end_match_983;
next_987:;
    if (match_262) goto next_988;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_384;
    tuple_384.t0 = callee_8;
    tuple_384.t1 = tokens_193;
    tuple_384.t2 = errors_130;
    match_261 = tuple_384;
    goto end_match_983;
next_988:;
    exit(1);
end_match_983:;
    return match_261;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseApp_(struct IntIntTuple2 baseLoc_32, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_202) {
    struct Token_IntIntTuple2Tuple2List* tokens_191 = arg_202.t0;
    struct StringIntIntTuple2Tuple2List* errors_128 = arg_202.t1;
    struct IntIntTuple2 call_663 = nextLoc_1(tokens_191);
    struct IntIntTuple2 calleeLoc_3 = call_663;
    struct IntIntTuple2 call_664 = locAddX_(1, calleeLoc_3);
    struct IntIntTuple2 argBaseLoc_1 = call_664;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_385;
    tuple_385.t0 = tokens_191;
    tuple_385.t1 = errors_128;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_665 = parseSuffix_(baseLoc_32, tuple_385);
    struct AExpr_ callee_7 = call_665.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_192 = call_665.t1;
    struct StringIntIntTuple2Tuple2List* errors_129 = call_665.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_386;
    tuple_386.t0 = tokens_192;
    tuple_386.t1 = errors_129;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_666 = go_50(argBaseLoc_1, calleeLoc_3, baseLoc_32, callee_7, tuple_386);
    return call_666;
}

enum UniOp_Tag {
    Neg_,
};

struct UniOp_ {
    enum UniOp_Tag tag;
};

struct UniOp_AExpr_IntIntTuple2Tuple3 {
    struct UniOp_ t0;
    struct AExpr_ t1;
    struct IntIntTuple2 t2;
};

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePrefix_(struct IntIntTuple2 baseLoc_33, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_203) {
    struct Token_IntIntTuple2Tuple2List* tokens_195 = arg_203.t0;
    struct StringIntIntTuple2Tuple2List* errors_132 = arg_203.t1;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_263;
    if ((!(tokens_195))) goto next_990;
    if ((tokens_195->head.t0.tag != Minus_)) goto next_990;
    struct IntIntTuple2 loc_66 = tokens_195->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_196 = tokens_195->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_387;
    tuple_387.t0 = tokens_196;
    tuple_387.t1 = errors_132;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_667 = parseApp_(baseLoc_33, tuple_387);
    struct AExpr_ arg_3 = call_667.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_197 = call_667.t1;
    struct StringIntIntTuple2Tuple2List* errors_133 = call_667.t2;
    struct UniOp_AExpr_IntIntTuple2Tuple3 tuple_389;
    tuple_389.t0 = (struct UniOp_){.tag = Neg_};
    tuple_389.t1 = arg_3;
    tuple_389.t2 = loc_66;
    struct UniOp_AExpr_IntIntTuple2Tuple3* payload_135 = (struct UniOp_AExpr_IntIntTuple2Tuple3*)malloc(sizeof(struct UniOp_AExpr_IntIntTuple2Tuple3));
    (*(((struct UniOp_AExpr_IntIntTuple2Tuple3*)payload_135))) = tuple_389;
    struct AExpr_ variant_135 = (struct AExpr_){.tag = Uni_, .Uni_ = payload_135};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_388;
    tuple_388.t0 = variant_135;
    tuple_388.t1 = tokens_197;
    tuple_388.t2 = errors_133;
    match_263 = tuple_388;
    goto end_match_989;
next_990:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_390;
    tuple_390.t0 = tokens_195;
    tuple_390.t1 = errors_132;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_668 = parseApp_(baseLoc_33, tuple_390);
    match_263 = call_668;
    goto end_match_989;
next_991:;
end_match_989:;
    return match_263;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseNextLevelOp_(struct OpLevel_ level_1, struct IntIntTuple2 baseLoc_34, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_204) {
    struct Token_IntIntTuple2Tuple2List* tokens_198 = arg_204.t0;
    struct StringIntIntTuple2Tuple2List* errors_134 = arg_204.t1;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_264;
    struct OpLevel_ call_669 = opLevelToNext_(level_1);
    if ((call_669.tag != Prefix_)) goto next_993;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_391;
    tuple_391.t0 = tokens_198;
    tuple_391.t1 = errors_134;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_670 = parsePrefix_(baseLoc_34, tuple_391);
    match_264 = call_670;
    goto end_match_992;
next_993:;
    struct OpLevel_ nextLevel_ = call_669;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_392;
    tuple_392.t0 = tokens_198;
    tuple_392.t1 = errors_134;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_671 = parseOp_(nextLevel_, baseLoc_34, tuple_392);
    match_264 = call_671;
    goto end_match_992;
next_994:;
end_match_992:;
    return match_264;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 nextL_(struct IntIntTuple2 baseLoc_35, struct OpLevel_ level_2, struct AExpr_ expr_12, struct Op_ op_, struct IntIntTuple2 opLoc_2, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_205) {
    struct Token_IntIntTuple2Tuple2List* tokens_200 = arg_205.t0;
    struct StringIntIntTuple2Tuple2List* errors_136 = arg_205.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_393;
    tuple_393.t0 = tokens_200;
    tuple_393.t1 = errors_136;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_672 = parseNextLevelOp_(level_2, baseLoc_35, tuple_393);
    struct AExpr_ second_4 = call_672.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_201 = call_672.t1;
    struct StringIntIntTuple2Tuple2List* errors_137 = call_672.t2;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_394;
    tuple_394.t0 = op_;
    tuple_394.t1 = expr_12;
    tuple_394.t2 = second_4;
    tuple_394.t3 = opLoc_2;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_136 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_136))) = tuple_394;
    struct AExpr_ variant_136 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_136};
    struct AExpr_ expr_13 = variant_136;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_395;
    tuple_395.t0 = tokens_201;
    tuple_395.t1 = errors_137;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_673 = parseOps_(level_2, baseLoc_35, expr_13, tuple_395);
    return call_673;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 nextR_(struct IntIntTuple2 baseLoc_35, struct OpLevel_ level_2, struct AExpr_ expr_14, struct Op_ op_1, struct IntIntTuple2 opLoc_3, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_206) {
    struct Token_IntIntTuple2Tuple2List* tokens_202 = arg_206.t0;
    struct StringIntIntTuple2Tuple2List* errors_138 = arg_206.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_396;
    tuple_396.t0 = tokens_202;
    tuple_396.t1 = errors_138;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_674 = parseOp_(level_2, baseLoc_35, tuple_396);
    struct AExpr_ second_5 = call_674.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_203 = call_674.t1;
    struct StringIntIntTuple2Tuple2List* errors_139 = call_674.t2;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_397;
    tuple_397.t0 = op_1;
    tuple_397.t1 = expr_14;
    tuple_397.t2 = second_5;
    tuple_397.t3 = opLoc_3;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_137 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_137))) = tuple_397;
    struct AExpr_ variant_137 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_137};
    struct AExpr_ expr_15 = variant_137;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_398;
    tuple_398.t0 = tokens_203;
    tuple_398.t1 = errors_139;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_675 = parseOps_(level_2, baseLoc_35, expr_15, tuple_398);
    return call_675;
}

struct OpLevel_Token_IntIntTuple2Tuple2ListTuple2 {
    struct OpLevel_ t0;
    struct Token_IntIntTuple2Tuple2List* t1;
};

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseOps_(struct OpLevel_ level_2, struct IntIntTuple2 baseLoc_35, struct AExpr_ first_3, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_207) {
    struct Token_IntIntTuple2Tuple2List* tokens_199 = arg_207.t0;
    struct StringIntIntTuple2Tuple2List* errors_135 = arg_207.t1;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_265;
    struct OpLevel_Token_IntIntTuple2Tuple2ListTuple2 tuple_399;
    tuple_399.t0 = level_2;
    tuple_399.t1 = tokens_199;
    if ((tuple_399.t0.tag != Or_)) goto next_996;
    if ((!(tuple_399.t1))) goto next_996;
    if ((tuple_399.t1->head.t0.tag != PipePipe_)) goto next_996;
    struct IntIntTuple2 opLoc_4 = tuple_399.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_204 = tuple_399.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_400;
    tuple_400.t0 = tokens_204;
    tuple_400.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_676 = nextL_(baseLoc_35, level_2, first_3, (struct Op_){.tag = Or_1}, opLoc_4, tuple_400);
    match_265 = call_676;
    goto end_match_995;
next_996:;
    if ((tuple_399.t0.tag != And_)) goto next_997;
    if ((!(tuple_399.t1))) goto next_997;
    if ((tuple_399.t1->head.t0.tag != AmpAmp_)) goto next_997;
    struct IntIntTuple2 opLoc_5 = tuple_399.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_205 = tuple_399.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_401;
    tuple_401.t0 = tokens_205;
    tuple_401.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_677 = nextL_(baseLoc_35, level_2, first_3, (struct Op_){.tag = And_1}, opLoc_5, tuple_401);
    match_265 = call_677;
    goto end_match_995;
next_997:;
    if ((tuple_399.t0.tag != Cmp_)) goto next_998;
    if ((!(tuple_399.t1))) goto next_998;
    if ((tuple_399.t1->head.t0.tag != Eq_)) goto next_998;
    struct IntIntTuple2 opLoc_6 = tuple_399.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_206 = tuple_399.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_402;
    tuple_402.t0 = tokens_206;
    tuple_402.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_678 = nextL_(baseLoc_35, level_2, first_3, (struct Op_){.tag = Eq_1}, opLoc_6, tuple_402);
    match_265 = call_678;
    goto end_match_995;
next_998:;
    if ((tuple_399.t0.tag != Cmp_)) goto next_999;
    if ((!(tuple_399.t1))) goto next_999;
    if ((tuple_399.t1->head.t0.tag != LtGt_)) goto next_999;
    struct IntIntTuple2 opLoc_7 = tuple_399.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_207 = tuple_399.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_403;
    tuple_403.t0 = tokens_207;
    tuple_403.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_679 = nextL_(baseLoc_35, level_2, first_3, (struct Op_){.tag = Ne_}, opLoc_7, tuple_403);
    match_265 = call_679;
    goto end_match_995;
next_999:;
    if ((tuple_399.t0.tag != Cmp_)) goto next_1000;
    if ((!(tuple_399.t1))) goto next_1000;
    if ((tuple_399.t1->head.t0.tag != Lt_)) goto next_1000;
    struct IntIntTuple2 opLoc_8 = tuple_399.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_208 = tuple_399.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_404;
    tuple_404.t0 = tokens_208;
    tuple_404.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_680 = nextL_(baseLoc_35, level_2, first_3, (struct Op_){.tag = Lt_1}, opLoc_8, tuple_404);
    match_265 = call_680;
    goto end_match_995;
next_1000:;
    if ((tuple_399.t0.tag != Cmp_)) goto next_1001;
    if ((!(tuple_399.t1))) goto next_1001;
    if ((tuple_399.t1->head.t0.tag != LtEq_)) goto next_1001;
    struct IntIntTuple2 opLoc_9 = tuple_399.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_209 = tuple_399.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_405;
    tuple_405.t0 = tokens_209;
    tuple_405.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_681 = nextL_(baseLoc_35, level_2, first_3, (struct Op_){.tag = Le_}, opLoc_9, tuple_405);
    match_265 = call_681;
    goto end_match_995;
next_1001:;
    if ((tuple_399.t0.tag != Cmp_)) goto next_1002;
    if ((!(tuple_399.t1))) goto next_1002;
    if ((tuple_399.t1->head.t0.tag != Gt_)) goto next_1002;
    struct IntIntTuple2 opLoc_10 = tuple_399.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_210 = tuple_399.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_406;
    tuple_406.t0 = tokens_210;
    tuple_406.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_682 = nextL_(baseLoc_35, level_2, first_3, (struct Op_){.tag = Gt_1}, opLoc_10, tuple_406);
    match_265 = call_682;
    goto end_match_995;
next_1002:;
    if ((tuple_399.t0.tag != Cmp_)) goto next_1003;
    if ((!(tuple_399.t1))) goto next_1003;
    if ((tuple_399.t1->head.t0.tag != GtEq_)) goto next_1003;
    struct IntIntTuple2 opLoc_11 = tuple_399.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_211 = tuple_399.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_407;
    tuple_407.t0 = tokens_211;
    tuple_407.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_683 = nextL_(baseLoc_35, level_2, first_3, (struct Op_){.tag = Ge_}, opLoc_11, tuple_407);
    match_265 = call_683;
    goto end_match_995;
next_1003:;
    if ((tuple_399.t0.tag != Pipe_1)) goto next_1004;
    if ((!(tuple_399.t1))) goto next_1004;
    if ((tuple_399.t1->head.t0.tag != PipeGt_)) goto next_1004;
    struct IntIntTuple2 opLoc_12 = tuple_399.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_212 = tuple_399.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_408;
    tuple_408.t0 = tokens_212;
    tuple_408.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_684 = nextL_(baseLoc_35, level_2, first_3, (struct Op_){.tag = Pipe_2}, opLoc_12, tuple_408);
    match_265 = call_684;
    goto end_match_995;
next_1004:;
    if ((tuple_399.t0.tag != Cons_)) goto next_1005;
    if ((!(tuple_399.t1))) goto next_1005;
    if ((tuple_399.t1->head.t0.tag != ColonColon_)) goto next_1005;
    struct IntIntTuple2 opLoc_13 = tuple_399.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_213 = tuple_399.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_409;
    tuple_409.t0 = tokens_213;
    tuple_409.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_685 = nextR_(baseLoc_35, level_2, first_3, (struct Op_){.tag = Cons_1}, opLoc_13, tuple_409);
    match_265 = call_685;
    goto end_match_995;
next_1005:;
    if ((tuple_399.t0.tag != Add_)) goto next_1006;
    if ((!(tuple_399.t1))) goto next_1006;
    if ((tuple_399.t1->head.t0.tag != Plus_)) goto next_1006;
    struct IntIntTuple2 opLoc_14 = tuple_399.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_214 = tuple_399.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_410;
    tuple_410.t0 = tokens_214;
    tuple_410.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_686 = nextL_(baseLoc_35, level_2, first_3, (struct Op_){.tag = Add_1}, opLoc_14, tuple_410);
    match_265 = call_686;
    goto end_match_995;
next_1006:;
    if ((tuple_399.t0.tag != Add_)) goto next_1007;
    if ((!(tuple_399.t1))) goto next_1007;
    if ((tuple_399.t1->head.t0.tag != Minus_)) goto next_1007;
    struct IntIntTuple2 opLoc_15 = tuple_399.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_215 = tuple_399.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_411;
    tuple_411.t0 = tokens_215;
    tuple_411.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_687 = nextL_(baseLoc_35, level_2, first_3, (struct Op_){.tag = Sub_}, opLoc_15, tuple_411);
    match_265 = call_687;
    goto end_match_995;
next_1007:;
    if ((tuple_399.t0.tag != Mul_)) goto next_1008;
    if ((!(tuple_399.t1))) goto next_1008;
    if ((tuple_399.t1->head.t0.tag != Star_)) goto next_1008;
    struct IntIntTuple2 opLoc_16 = tuple_399.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_216 = tuple_399.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_412;
    tuple_412.t0 = tokens_216;
    tuple_412.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_688 = nextL_(baseLoc_35, level_2, first_3, (struct Op_){.tag = Mul_1}, opLoc_16, tuple_412);
    match_265 = call_688;
    goto end_match_995;
next_1008:;
    if ((tuple_399.t0.tag != Mul_)) goto next_1009;
    if ((!(tuple_399.t1))) goto next_1009;
    if ((tuple_399.t1->head.t0.tag != Slash_)) goto next_1009;
    struct IntIntTuple2 opLoc_17 = tuple_399.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_217 = tuple_399.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_413;
    tuple_413.t0 = tokens_217;
    tuple_413.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_689 = nextL_(baseLoc_35, level_2, first_3, (struct Op_){.tag = Div_}, opLoc_17, tuple_413);
    match_265 = call_689;
    goto end_match_995;
next_1009:;
    if ((tuple_399.t0.tag != Mul_)) goto next_1010;
    if ((!(tuple_399.t1))) goto next_1010;
    if ((tuple_399.t1->head.t0.tag != Percent_)) goto next_1010;
    struct IntIntTuple2 opLoc_18 = tuple_399.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_218 = tuple_399.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_414;
    tuple_414.t0 = tokens_218;
    tuple_414.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_690 = nextL_(baseLoc_35, level_2, first_3, (struct Op_){.tag = Mod_}, opLoc_18, tuple_414);
    match_265 = call_690;
    goto end_match_995;
next_1010:;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_415;
    tuple_415.t0 = first_3;
    tuple_415.t1 = tokens_199;
    tuple_415.t2 = errors_135;
    match_265 = tuple_415;
    goto end_match_995;
next_1011:;
end_match_995:;
    return match_265;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseOp_(struct OpLevel_ level_3, struct IntIntTuple2 baseLoc_36, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_208) {
    struct Token_IntIntTuple2Tuple2List* tokens_219 = arg_208.t0;
    struct StringIntIntTuple2Tuple2List* errors_140 = arg_208.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_416;
    tuple_416.t0 = tokens_219;
    tuple_416.t1 = errors_140;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_691 = parseNextLevelOp_(level_3, baseLoc_36, tuple_416);
    struct AExpr_ first_4 = call_691.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_220 = call_691.t1;
    struct StringIntIntTuple2Tuple2List* errors_141 = call_691.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_417;
    tuple_417.t0 = tokens_220;
    tuple_417.t1 = errors_141;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_692 = parseOps_(level_3, baseLoc_36, first_4, tuple_417);
    return call_692;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTupleItem_(struct IntIntTuple2 baseLoc_37, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_209) {
    struct Token_IntIntTuple2Tuple2List* tokens_221 = arg_209.t0;
    struct StringIntIntTuple2Tuple2List* errors_142 = arg_209.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_418;
    tuple_418.t0 = tokens_221;
    tuple_418.t1 = errors_142;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_693 = parseOp_((struct OpLevel_){.tag = Or_}, baseLoc_37, tuple_418);
    return call_693;
}

struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_51(struct IntIntTuple2 baseLoc_38, struct AExpr_List* acc_33, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_210) {
    struct Token_IntIntTuple2Tuple2List* tokens_223 = arg_210.t0;
    struct StringIntIntTuple2Tuple2List* errors_144 = arg_210.t1;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_266;
    if ((!(tokens_223))) goto next_1013;
    if ((tokens_223->head.t0.tag != Comma_)) goto next_1013;
    struct Token_IntIntTuple2Tuple2List* tokens_224 = tokens_223->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_419;
    tuple_419.t0 = tokens_224;
    tuple_419.t1 = errors_144;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_694 = parseTupleItem_(baseLoc_38, tuple_419);
    struct AExpr_ second_6 = call_694.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_225 = call_694.t1;
    struct StringIntIntTuple2Tuple2List* errors_145 = call_694.t2;
    struct AExpr_List* list_81 = (struct AExpr_List*)malloc(sizeof(struct AExpr_List));
    list_81->head = second_6;
    list_81->tail = acc_33;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_420;
    tuple_420.t0 = tokens_225;
    tuple_420.t1 = errors_145;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_695 = go_51(baseLoc_38, list_81, tuple_420);
    match_266 = call_695;
    goto end_match_1012;
next_1013:;
    struct Token_IntIntTuple2Tuple2List* tokens_226 = tokens_223;
    struct AExpr_List* call_696 = listRev_2(acc_33);
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_421;
    tuple_421.t0 = call_696;
    tuple_421.t1 = tokens_226;
    tuple_421.t2 = errors_144;
    match_266 = tuple_421;
    goto end_match_1012;
next_1014:;
end_match_1012:;
    return match_266;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTuple_(struct IntIntTuple2 baseLoc_38, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_211) {
    struct Token_IntIntTuple2Tuple2List* tokens_222 = arg_211.t0;
    struct StringIntIntTuple2Tuple2List* errors_143 = arg_211.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_422;
    tuple_422.t0 = tokens_222;
    tuple_422.t1 = errors_143;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_697 = parseTupleItem_(baseLoc_38, tuple_422);
    struct AExpr_ item_ = call_697.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_227 = call_697.t1;
    struct StringIntIntTuple2Tuple2List* errors_146 = call_697.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_267;
    if ((!(tokens_227))) goto next_1016;
    if ((tokens_227->head.t0.tag != Comma_)) goto next_1016;
    struct IntIntTuple2 loc_67 = tokens_227->head.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_423;
    tuple_423.t0 = tokens_227;
    tuple_423.t1 = errors_146;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_698 = go_51(baseLoc_38, NULL, tuple_423);
    struct AExpr_List* items_7 = call_698.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_228 = call_698.t1;
    struct StringIntIntTuple2Tuple2List* errors_147 = call_698.t2;
    struct AExpr_List* list_82 = (struct AExpr_List*)malloc(sizeof(struct AExpr_List));
    list_82->head = item_;
    list_82->tail = items_7;
    struct AExpr_ListIntIntTuple2Tuple2 tuple_425;
    tuple_425.t0 = list_82;
    tuple_425.t1 = loc_67;
    struct AExpr_ListIntIntTuple2Tuple2* payload_138 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_138))) = tuple_425;
    struct AExpr_ variant_138 = (struct AExpr_){.tag = TupleLit_1, .TupleLit_1 = payload_138};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_424;
    tuple_424.t0 = variant_138;
    tuple_424.t1 = tokens_228;
    tuple_424.t2 = errors_147;
    match_267 = tuple_424;
    goto end_match_1015;
next_1016:;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_426;
    tuple_426.t0 = item_;
    tuple_426.t1 = tokens_227;
    tuple_426.t2 = errors_146;
    match_267 = tuple_426;
    goto end_match_1015;
next_1017:;
end_match_1015:;
    return match_267;
}

struct AExpr_ATy_IntIntTuple2Tuple3 {
    struct AExpr_ t0;
    struct ATy_ t1;
    struct IntIntTuple2 t2;
};

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseAnno_(struct IntIntTuple2 baseLoc_39, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_212) {
    struct Token_IntIntTuple2Tuple2List* tokens_229 = arg_212.t0;
    struct StringIntIntTuple2Tuple2List* errors_148 = arg_212.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_427;
    tuple_427.t0 = tokens_229;
    tuple_427.t1 = errors_148;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_699 = parseTuple_(baseLoc_39, tuple_427);
    struct AExpr_ body_14 = call_699.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_230 = call_699.t1;
    struct StringIntIntTuple2Tuple2List* errors_149 = call_699.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_268;
    if ((!(tokens_230))) goto next_1019;
    if ((tokens_230->head.t0.tag != Colon_)) goto next_1019;
    struct IntIntTuple2 loc_68 = tokens_230->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_231 = tokens_230->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_428;
    tuple_428.t0 = tokens_231;
    tuple_428.t1 = errors_149;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_700 = parseTy_(baseLoc_39, tuple_428);
    struct ATy_ ty_54 = call_700.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_232 = call_700.t1;
    struct StringIntIntTuple2Tuple2List* errors_150 = call_700.t2;
    struct AExpr_ATy_IntIntTuple2Tuple3 tuple_430;
    tuple_430.t0 = body_14;
    tuple_430.t1 = ty_54;
    tuple_430.t2 = loc_68;
    struct AExpr_ATy_IntIntTuple2Tuple3* payload_139 = (struct AExpr_ATy_IntIntTuple2Tuple3*)malloc(sizeof(struct AExpr_ATy_IntIntTuple2Tuple3));
    (*(((struct AExpr_ATy_IntIntTuple2Tuple3*)payload_139))) = tuple_430;
    struct AExpr_ variant_139 = (struct AExpr_){.tag = Anno_1, .Anno_1 = payload_139};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_429;
    tuple_429.t0 = variant_139;
    tuple_429.t1 = tokens_232;
    tuple_429.t2 = errors_150;
    match_268 = tuple_429;
    goto end_match_1018;
next_1019:;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_431;
    tuple_431.t0 = body_14;
    tuple_431.t1 = tokens_230;
    tuple_431.t2 = errors_149;
    match_268 = tuple_431;
    goto end_match_1018;
next_1020:;
end_match_1018:;
    return match_268;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseExpr_(struct IntIntTuple2 baseLoc_40, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_213) {
    struct Token_IntIntTuple2Tuple2List* tokens_233 = arg_213.t0;
    struct StringIntIntTuple2Tuple2List* errors_151 = arg_213.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_432;
    tuple_432.t0 = tokens_233;
    tuple_432.t1 = errors_151;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_701 = parseAnno_(baseLoc_40, tuple_432);
    return call_701;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseStmt_(struct IntIntTuple2 baseLoc_41, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_214) {
    struct Token_IntIntTuple2Tuple2List* tokens_234 = arg_214.t0;
    struct StringIntIntTuple2Tuple2List* errors_152 = arg_214.t1;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_269;
    if ((!(tokens_234))) goto next_1022;
    if ((tokens_234->head.t0.tag != Let_)) goto next_1022;
    struct IntIntTuple2 letLoc_2 = tokens_234->head.t1;
    if ((!(tokens_234->tail))) goto next_1022;
    if ((tokens_234->tail->head.t0.tag != Rec_)) goto next_1022;
    struct Token_IntIntTuple2Tuple2List* tokens_235 = tokens_234->tail->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_433;
    tuple_433.t0 = tokens_235;
    tuple_433.t1 = errors_152;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_702 = parseLet_(letLoc_2, tuple_433);
    match_269 = call_702;
    goto end_match_1021;
next_1022:;
    if ((!(tokens_234))) goto next_1023;
    if ((tokens_234->head.t0.tag != Let_)) goto next_1023;
    struct IntIntTuple2 letLoc_3 = tokens_234->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_236 = tokens_234->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_434;
    tuple_434.t0 = tokens_236;
    tuple_434.t1 = errors_152;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_703 = parseLet_(letLoc_3, tuple_434);
    match_269 = call_703;
    goto end_match_1021;
next_1023:;
    if ((!(tokens_234))) goto next_1024;
    if ((tokens_234->head.t0.tag != Type_)) goto next_1024;
    struct IntIntTuple2 typeLoc_1 = tokens_234->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_237 = tokens_234->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_435;
    tuple_435.t0 = tokens_237;
    tuple_435.t1 = errors_152;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_704 = parseTyDecl_(typeLoc_1, tuple_435);
    match_269 = call_704;
    goto end_match_1021;
next_1024:;
    if ((!(tokens_234))) goto next_1025;
    if ((tokens_234->head.t0.tag != Open_)) goto next_1025;
    struct IntIntTuple2 typeLoc_2 = tokens_234->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_238 = tokens_234->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_436;
    tuple_436.t0 = tokens_238;
    tuple_436.t1 = errors_152;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_705 = parseOpen_(typeLoc_2, tuple_436);
    match_269 = call_705;
    goto end_match_1021;
next_1025:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_437;
    tuple_437.t0 = tokens_234;
    tuple_437.t1 = errors_152;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_706 = parseExpr_(baseLoc_41, tuple_437);
    match_269 = call_706;
    goto end_match_1021;
next_1026:;
end_match_1021:;
    return match_269;
}

struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_52(struct IntIntTuple2 baseLoc_42, struct AExpr_List* acc_34, struct IntIntTuple2 alignLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_215) {
    struct Token_IntIntTuple2Tuple2List* tokens_240 = arg_215.t0;
    struct StringIntIntTuple2Tuple2List* errors_154 = arg_215.t1;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_270;
    if ((!(tokens_240))) goto next_1028;
    if ((tokens_240->head.t0.tag != Semi_)) goto next_1028;
    struct IntIntTuple2 semiLoc_ = tokens_240->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_241 = tokens_240->tail;
    int call_707 = locInside_(alignLoc_, semiLoc_);
    if ((!(call_707))) goto next_1028;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_438;
    tuple_438.t0 = tokens_241;
    tuple_438.t1 = errors_154;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_708 = parseStmt_(baseLoc_42, tuple_438);
    struct AExpr_ expr_16 = call_708.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_242 = call_708.t1;
    struct StringIntIntTuple2Tuple2List* errors_155 = call_708.t2;
    struct AExpr_List* list_83 = (struct AExpr_List*)malloc(sizeof(struct AExpr_List));
    list_83->head = expr_16;
    list_83->tail = acc_34;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_439;
    tuple_439.t0 = tokens_242;
    tuple_439.t1 = errors_155;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_709 = go_52(baseLoc_42, list_83, alignLoc_, tuple_439);
    match_270 = call_709;
    goto end_match_1027;
next_1028:;
    int match_271;
    struct IntIntTuple2 call_710 = nextLoc_1(tokens_240);
    int call_711 = locIsSameColumn_(alignLoc_, call_710);
    if ((!(call_711))) goto next_1032;
    int call_712 = leadsExpr_1(tokens_240);
    match_271 = call_712;
    goto end_match_1031;
next_1032:;
    if (call_711) goto next_1033;
    match_271 = 0;
    goto end_match_1031;
next_1033:;
    exit(1);
end_match_1031:;
    if ((!(match_271))) goto next_1029;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_440;
    tuple_440.t0 = tokens_240;
    tuple_440.t1 = errors_154;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_713 = parseStmt_(baseLoc_42, tuple_440);
    struct AExpr_ expr_17 = call_713.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_243 = call_713.t1;
    struct StringIntIntTuple2Tuple2List* errors_156 = call_713.t2;
    struct AExpr_List* list_84 = (struct AExpr_List*)malloc(sizeof(struct AExpr_List));
    list_84->head = expr_17;
    list_84->tail = acc_34;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_441;
    tuple_441.t0 = tokens_243;
    tuple_441.t1 = errors_156;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_714 = go_52(baseLoc_42, list_84, alignLoc_, tuple_441);
    match_270 = call_714;
    goto end_match_1027;
next_1029:;
    struct AExpr_List* call_715 = listRev_2(acc_34);
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_442;
    tuple_442.t0 = call_715;
    tuple_442.t1 = tokens_240;
    tuple_442.t2 = errors_154;
    match_270 = tuple_442;
    goto end_match_1027;
next_1030:;
end_match_1027:;
    return match_270;
}

struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseStmts_(struct IntIntTuple2 baseLoc_42, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_216) {
    struct Token_IntIntTuple2Tuple2List* tokens_239 = arg_216.t0;
    struct StringIntIntTuple2Tuple2List* errors_153 = arg_216.t1;
    struct IntIntTuple2 call_716 = nextLoc_1(tokens_239);
    struct IntIntTuple2 alignLoc_1 = call_716;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_272;
    int call_717 = locInside_(baseLoc_42, alignLoc_1);
    if ((!(call_717))) goto next_1035;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_443;
    tuple_443.t0 = tokens_239;
    tuple_443.t1 = errors_153;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_718 = go_52(baseLoc_42, NULL, alignLoc_1, tuple_443);
    match_272 = call_718;
    goto end_match_1034;
next_1035:;
    if (call_717) goto next_1036;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_444;
    tuple_444.t0 = NULL;
    tuple_444.t1 = tokens_239;
    tuple_444.t2 = errors_153;
    match_272 = tuple_444;
    goto end_match_1034;
next_1036:;
    exit(1);
end_match_1034:;
    return match_272;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseSemi_(struct IntIntTuple2 baseLoc_43, struct IntIntTuple2 mainLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_217) {
    struct Token_IntIntTuple2Tuple2List* tokens_244 = arg_217.t0;
    struct StringIntIntTuple2Tuple2List* errors_157 = arg_217.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_445;
    tuple_445.t0 = tokens_244;
    tuple_445.t1 = errors_157;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_719 = parseStmts_(baseLoc_43, tuple_445);
    struct AExpr_List* items_8 = call_719.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_245 = call_719.t1;
    struct StringIntIntTuple2Tuple2List* errors_158 = call_719.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_273;
    if ((!((!(items_8))))) goto next_1038;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_446;
    tuple_446.t0 = tokens_245;
    tuple_446.t1 = errors_158;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_720 = parseExprError_1((struct String){.str = "Expected statements", .len = 19}, tuple_446);
    match_273 = call_720;
    goto end_match_1037;
next_1038:;
    if ((!(items_8))) goto next_1039;
    struct AExpr_ item_1 = items_8->head;
    if ((!((!(items_8->tail))))) goto next_1039;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_447;
    tuple_447.t0 = item_1;
    tuple_447.t1 = tokens_245;
    tuple_447.t2 = errors_158;
    match_273 = tuple_447;
    goto end_match_1037;
next_1039:;
    struct AExpr_ListIntIntTuple2Tuple2 tuple_449;
    tuple_449.t0 = items_8;
    tuple_449.t1 = mainLoc_;
    struct AExpr_ListIntIntTuple2Tuple2* payload_140 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_140))) = tuple_449;
    struct AExpr_ variant_140 = (struct AExpr_){.tag = Semi_1, .Semi_1 = payload_140};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_448;
    tuple_448.t0 = variant_140;
    tuple_448.t1 = tokens_245;
    tuple_448.t2 = errors_158;
    match_273 = tuple_448;
    goto end_match_1037;
next_1040:;
end_match_1037:;
    return match_273;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTopLevel_(struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_218) {
    struct Token_IntIntTuple2Tuple2List* tokens_246 = arg_218.t0;
    struct StringIntIntTuple2Tuple2List* errors_159 = arg_218.t1;
    struct IntIntTuple2 tuple_450;
    tuple_450.t0 = 0;
    tuple_450.t1 = 0;
    struct IntIntTuple2 topLoc_ = tuple_450;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_274;
    if ((!((!(tokens_246))))) goto next_1042;
    struct AExpr_ListIntIntTuple2Tuple2 tuple_452;
    tuple_452.t0 = NULL;
    tuple_452.t1 = topLoc_;
    struct AExpr_ListIntIntTuple2Tuple2* payload_141 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_141))) = tuple_452;
    struct AExpr_ variant_141 = (struct AExpr_){.tag = TupleLit_1, .TupleLit_1 = payload_141};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_451;
    tuple_451.t0 = variant_141;
    tuple_451.t1 = tokens_246;
    tuple_451.t2 = errors_159;
    match_274 = tuple_451;
    goto end_match_1041;
next_1042:;
    if ((!(tokens_246))) goto next_1043;
    if ((tokens_246->head.t0.tag != Module_)) goto next_1043;
    struct IntIntTuple2 moduleLoc_ = tokens_246->head.t1;
    if ((!(tokens_246->tail))) goto next_1043;
    if ((tokens_246->tail->head.t0.tag != Rec_)) goto next_1043;
    if ((!(tokens_246->tail->tail))) goto next_1043;
    if ((tokens_246->tail->tail->head.t0.tag != Ident_)) goto next_1043;
    if ((!(tokens_246->tail->tail->tail))) goto next_1043;
    if ((tokens_246->tail->tail->tail->head.t0.tag != Dot_)) goto next_1043;
    if ((!(tokens_246->tail->tail->tail->tail))) goto next_1043;
    if ((tokens_246->tail->tail->tail->tail->head.t0.tag != Ident_)) goto next_1043;
    struct Token_IntIntTuple2Tuple2List* tokens_247 = tokens_246->tail->tail->tail->tail->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_453;
    tuple_453.t0 = tokens_247;
    tuple_453.t1 = errors_159;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_721 = parseSemi_(moduleLoc_, moduleLoc_, tuple_453);
    match_274 = call_721;
    goto end_match_1041;
next_1043:;
    if ((!(tokens_246))) goto next_1044;
    if ((tokens_246->head.t0.tag != Module_)) goto next_1044;
    struct IntIntTuple2 moduleLoc_1 = tokens_246->head.t1;
    if ((!(tokens_246->tail))) goto next_1044;
    if ((tokens_246->tail->head.t0.tag != Rec_)) goto next_1044;
    if ((!(tokens_246->tail->tail))) goto next_1044;
    if ((tokens_246->tail->tail->head.t0.tag != Ident_)) goto next_1044;
    struct Token_IntIntTuple2Tuple2List* tokens_248 = tokens_246->tail->tail->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_454;
    tuple_454.t0 = tokens_248;
    tuple_454.t1 = errors_159;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_722 = parseSemi_(moduleLoc_1, moduleLoc_1, tuple_454);
    match_274 = call_722;
    goto end_match_1041;
next_1044:;
    if ((!(tokens_246))) goto next_1045;
    if ((tokens_246->head.t0.tag != Module_)) goto next_1045;
    struct IntIntTuple2 moduleLoc_2 = tokens_246->head.t1;
    if ((!(tokens_246->tail))) goto next_1045;
    if ((tokens_246->tail->head.t0.tag != Ident_)) goto next_1045;
    struct Token_IntIntTuple2Tuple2List* tokens_249 = tokens_246->tail->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_455;
    tuple_455.t0 = tokens_249;
    tuple_455.t1 = errors_159;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_723 = parseSemi_(moduleLoc_2, moduleLoc_2, tuple_455);
    match_274 = call_723;
    goto end_match_1041;
next_1045:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_456;
    tuple_456.t0 = tokens_246;
    tuple_456.t1 = errors_159;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_724 = parseSemi_(topLoc_, topLoc_, tuple_456);
    match_274 = call_724;
    goto end_match_1041;
next_1046:;
end_match_1041:;
    return match_274;
}

struct AExpr_StringIntIntTuple2Tuple2ListTuple2 {
    struct AExpr_ t0;
    struct StringIntIntTuple2Tuple2List* t1;
};

struct AExpr_StringIntIntTuple2Tuple2ListTuple2 parse_(struct Token_IntIntTuple2Tuple2List* tokens_250) {
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_457;
    tuple_457.t0 = tokens_250;
    tuple_457.t1 = NULL;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_725 = parseTopLevel_(tuple_457);
    struct AExpr_ expr_18 = call_725.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_251 = call_725.t1;
    struct StringIntIntTuple2Tuple2List* errors_160 = call_725.t2;
    struct StringIntIntTuple2Tuple2List* match_275;
    if ((!((!(tokens_251))))) goto next_1048;
    match_275 = errors_160;
    goto end_match_1047;
next_1048:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_458;
    tuple_458.t0 = tokens_251;
    tuple_458.t1 = errors_160;
    struct StringIntIntTuple2Tuple2List* call_726 = parseNewError_1((struct String){.str = "Expected eof", .len = 12}, tuple_458);
    match_275 = call_726;
    goto end_match_1047;
next_1049:;
end_match_1047:;
    struct StringIntIntTuple2Tuple2List* errors_161 = match_275;
    struct AExpr_StringIntIntTuple2Tuple2ListTuple2 tuple_459;
    tuple_459.t0 = expr_18;
    tuple_459.t1 = errors_161;
    return tuple_459;
}

struct HPrim_ opToPrim_(struct Op_ op_2) {
    struct HPrim_ match_276;
    if ((op_2.tag != Add_1)) goto next_1051;
    match_276 = (struct HPrim_){.tag = Add_3};
    goto end_match_1050;
next_1051:;
    if ((op_2.tag != Sub_)) goto next_1052;
    match_276 = (struct HPrim_){.tag = Sub_1};
    goto end_match_1050;
next_1052:;
    if ((op_2.tag != Mul_1)) goto next_1053;
    match_276 = (struct HPrim_){.tag = Mul_2};
    goto end_match_1050;
next_1053:;
    if ((op_2.tag != Div_)) goto next_1054;
    match_276 = (struct HPrim_){.tag = Div_1};
    goto end_match_1050;
next_1054:;
    if ((op_2.tag != Mod_)) goto next_1055;
    match_276 = (struct HPrim_){.tag = Mod_1};
    goto end_match_1050;
next_1055:;
    if ((op_2.tag != Eq_1)) goto next_1056;
    match_276 = (struct HPrim_){.tag = Eq_3};
    goto end_match_1050;
next_1056:;
    if ((op_2.tag != Lt_1)) goto next_1057;
    match_276 = (struct HPrim_){.tag = Lt_2};
    goto end_match_1050;
next_1057:;
    if ((op_2.tag != Cons_1)) goto next_1059;
    match_276 = (struct HPrim_){.tag = Cons_4};
    goto end_match_1050;
next_1059:;
    if ((op_2.tag != Ne_)) goto next_1060;
    goto match_body_1058;
next_1060:;
    if ((op_2.tag != Le_)) goto next_1061;
    goto match_body_1058;
next_1061:;
    if ((op_2.tag != Gt_1)) goto next_1062;
    goto match_body_1058;
next_1062:;
    if ((op_2.tag != Ge_)) goto next_1063;
    goto match_body_1058;
next_1063:;
    if ((op_2.tag != And_1)) goto next_1064;
    goto match_body_1058;
next_1064:;
    if ((op_2.tag != Or_1)) goto next_1065;
    goto match_body_1058;
next_1065:;
    if ((op_2.tag != App_)) goto next_1066;
    goto match_body_1058;
next_1066:;
    if ((op_2.tag != Pipe_2)) goto next_1067;
    goto match_body_1058;
match_body_1058:;
    struct Op_HPrim_Fun1 call_727 = failwithf_3((struct String){.str = "NEVER: %A", .len = 9});
    struct HPrim_ app_72 = call_727.fun(call_727.env, op_2);
    match_276 = app_72;
    goto end_match_1050;
next_1067:;
end_match_1050:;
    return match_276;
}

struct APat_ go_53(struct IntIntTuple2 loc_69, struct APat_List* pats_5) {
    struct APat_ match_277;
    if ((!((!(pats_5))))) goto next_1069;
    struct APat_ListIntIntTuple2Tuple2 tuple_460;
    tuple_460.t0 = NULL;
    tuple_460.t1 = loc_69;
    struct APat_ListIntIntTuple2Tuple2* payload_142 = (struct APat_ListIntIntTuple2Tuple2*)malloc(sizeof(struct APat_ListIntIntTuple2Tuple2));
    (*(((struct APat_ListIntIntTuple2Tuple2*)payload_142))) = tuple_460;
    struct APat_ variant_142 = (struct APat_){.tag = ListLit_, .ListLit_ = payload_142};
    match_277 = variant_142;
    goto end_match_1068;
next_1069:;
    if ((!(pats_5))) goto next_1070;
    struct APat_ head_3 = pats_5->head;
    struct APat_List* tail_3 = pats_5->tail;
    struct APat_ call_728 = go_53(loc_69, tail_3);
    struct APat_ tail_4 = call_728;
    struct APat_APat_IntIntTuple2Tuple3 tuple_461;
    tuple_461.t0 = head_3;
    tuple_461.t1 = tail_4;
    tuple_461.t2 = loc_69;
    struct APat_APat_IntIntTuple2Tuple3* payload_143 = (struct APat_APat_IntIntTuple2Tuple3*)malloc(sizeof(struct APat_APat_IntIntTuple2Tuple3));
    (*(((struct APat_APat_IntIntTuple2Tuple3*)payload_143))) = tuple_461;
    struct APat_ variant_143 = (struct APat_){.tag = Cons_2, .Cons_2 = payload_143};
    match_277 = variant_143;
    goto end_match_1068;
next_1070:;
    exit(1);
end_match_1068:;
    return match_277;
}

struct APat_ desugarListLitPat_(struct APat_List* pats_4, struct IntIntTuple2 loc_69) {
    int call_729 = listIsEmpty_2(pats_4);
    milone_assert((!(call_729)), 64, 2);
    int call_730 = 0;
    struct APat_ call_731 = go_53(loc_69, pats_4);
    return call_731;
}

struct AExpr_ go_54(struct IntIntTuple2 loc_70, struct AExpr_List* items_10) {
    struct AExpr_ match_278;
    if ((!((!(items_10))))) goto next_1072;
    struct AExpr_ListIntIntTuple2Tuple2 tuple_462;
    tuple_462.t0 = NULL;
    tuple_462.t1 = loc_70;
    struct AExpr_ListIntIntTuple2Tuple2* payload_144 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_144))) = tuple_462;
    struct AExpr_ variant_144 = (struct AExpr_){.tag = ListLit_1, .ListLit_1 = payload_144};
    match_278 = variant_144;
    goto end_match_1071;
next_1072:;
    if ((!(items_10))) goto next_1073;
    struct AExpr_ head_4 = items_10->head;
    struct AExpr_List* tail_5 = items_10->tail;
    struct AExpr_ call_732 = go_54(loc_70, tail_5);
    struct AExpr_ tail_6 = call_732;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_463;
    tuple_463.t0 = (struct Op_){.tag = Cons_1};
    tuple_463.t1 = head_4;
    tuple_463.t2 = tail_6;
    tuple_463.t3 = loc_70;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_145 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_145))) = tuple_463;
    struct AExpr_ variant_145 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_145};
    match_278 = variant_145;
    goto end_match_1071;
next_1073:;
    exit(1);
end_match_1071:;
    return match_278;
}

struct AExpr_ desugarListLitExpr_(struct AExpr_List* items_9, struct IntIntTuple2 loc_70) {
    int call_733 = listIsEmpty_1(items_9);
    milone_assert((!(call_733)), 79, 2);
    int call_734 = 0;
    struct AExpr_ call_735 = go_54(loc_70, items_9);
    return call_735;
}

struct AExpr_ desugarIf_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct AExpr_ cond_2, struct AExpr_ body_15, struct AExpr_ alt_2, struct IntIntTuple2 loc_71) {
    struct AExpr_ match_279;
    if ((alt_2.tag != Missing_2)) goto next_1075;
    struct AExpr_ call_736 = axUnit_(loc_71);
    match_279 = call_736;
    goto end_match_1074;
next_1075:;
    match_279 = alt_2;
    goto end_match_1074;
next_1076:;
end_match_1074:;
    struct AExpr_ alt_3 = match_279;
    struct APat_ call_737 = apTrue_(litTrue_, loc_71);
    struct AExpr_ call_738 = axTrue_(litTrue_, loc_71);
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4 tuple_464;
    tuple_464.t0 = call_737;
    tuple_464.t1 = call_738;
    tuple_464.t2 = body_15;
    tuple_464.t3 = loc_71;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4* payload_146 = (struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct APat_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)payload_146))) = tuple_464;
    struct AArm_ variant_146 = (struct AArm_){.tag = AArm_, .AArm_ = payload_146};
    struct APat_ call_739 = apFalse_(litFalse_, loc_71);
    struct AExpr_ call_740 = axTrue_(litTrue_, loc_71);
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4 tuple_465;
    tuple_465.t0 = call_739;
    tuple_465.t1 = call_740;
    tuple_465.t2 = alt_3;
    tuple_465.t3 = loc_71;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4* payload_147 = (struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct APat_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)payload_147))) = tuple_465;
    struct AArm_ variant_147 = (struct AArm_){.tag = AArm_, .AArm_ = payload_147};
    struct AArm_List* list_86 = (struct AArm_List*)malloc(sizeof(struct AArm_List));
    list_86->head = variant_147;
    list_86->tail = NULL;
    struct AArm_List* list_85 = (struct AArm_List*)malloc(sizeof(struct AArm_List));
    list_85->head = variant_146;
    list_85->tail = list_86;
    struct AArm_List* arms_4 = list_85;
    struct AExpr_AArm_ListIntIntTuple2Tuple3 tuple_466;
    tuple_466.t0 = cond_2;
    tuple_466.t1 = arms_4;
    tuple_466.t2 = loc_71;
    struct AExpr_AArm_ListIntIntTuple2Tuple3* payload_148 = (struct AExpr_AArm_ListIntIntTuple2Tuple3*)malloc(sizeof(struct AExpr_AArm_ListIntIntTuple2Tuple3));
    (*(((struct AExpr_AArm_ListIntIntTuple2Tuple3*)payload_148))) = tuple_466;
    struct AExpr_ variant_148 = (struct AExpr_){.tag = Match_1, .Match_1 = payload_148};
    return variant_148;
}

struct AExpr_ desugarFun_(struct APat_List* pats_6, struct AExpr_ body_16, struct IntIntTuple2 loc_72) {
    struct String ident_26 = (struct String){.str = "fun", .len = 3};
    struct StringAPat_ListIntIntTuple2Tuple3 tuple_467;
    tuple_467.t0 = ident_26;
    tuple_467.t1 = pats_6;
    tuple_467.t2 = loc_72;
    struct StringAPat_ListIntIntTuple2Tuple3* payload_149 = (struct StringAPat_ListIntIntTuple2Tuple3*)malloc(sizeof(struct StringAPat_ListIntIntTuple2Tuple3));
    (*(((struct StringAPat_ListIntIntTuple2Tuple3*)payload_149))) = tuple_467;
    struct APat_ variant_149 = (struct APat_){.tag = Fun_2, .Fun_2 = payload_149};
    struct APat_ pat_23 = variant_149;
    struct StringIntIntTuple2Tuple2 tuple_468;
    tuple_468.t0 = ident_26;
    tuple_468.t1 = loc_72;
    struct StringIntIntTuple2Tuple2* payload_150 = (struct StringIntIntTuple2Tuple2*)malloc(sizeof(struct StringIntIntTuple2Tuple2));
    (*(((struct StringIntIntTuple2Tuple2*)payload_150))) = tuple_468;
    struct AExpr_ variant_150 = (struct AExpr_){.tag = Ident_2, .Ident_2 = payload_150};
    struct AExpr_ next_12 = variant_150;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4 tuple_469;
    tuple_469.t0 = pat_23;
    tuple_469.t1 = body_16;
    tuple_469.t2 = next_12;
    tuple_469.t3 = loc_72;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4* payload_151 = (struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct APat_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)payload_151))) = tuple_469;
    struct AExpr_ variant_151 = (struct AExpr_){.tag = Let_1, .Let_1 = payload_151};
    return variant_151;
}

struct AExpr_ desugarUniNeg_(struct AExpr_ arg_4, struct IntIntTuple2 loc_73) {
    int* payload_152 = (int*)malloc(sizeof(int));
    (*(((int*)payload_152))) = 0;
    struct Lit_ variant_152 = (struct Lit_){.tag = Int_, .Int_ = payload_152};
    struct Lit_IntIntTuple2Tuple2 tuple_470;
    tuple_470.t0 = variant_152;
    tuple_470.t1 = loc_73;
    struct Lit_IntIntTuple2Tuple2* payload_153 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_153))) = tuple_470;
    struct AExpr_ variant_153 = (struct AExpr_){.tag = Lit_1, .Lit_1 = payload_153};
    struct AExpr_ zero_ = variant_153;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_471;
    tuple_471.t0 = (struct Op_){.tag = Sub_};
    tuple_471.t1 = zero_;
    tuple_471.t2 = arg_4;
    tuple_471.t3 = loc_73;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_154 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_154))) = tuple_471;
    struct AExpr_ variant_154 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_154};
    return variant_154;
}

struct AExpr_ desugarBinNe_(struct Lit_ litFalse_, struct AExpr_ l_19, struct AExpr_ r_33, struct IntIntTuple2 loc_74) {
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_472;
    tuple_472.t0 = (struct Op_){.tag = Eq_1};
    tuple_472.t1 = l_19;
    tuple_472.t2 = r_33;
    tuple_472.t3 = loc_74;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_155 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_155))) = tuple_472;
    struct AExpr_ variant_155 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_155};
    struct AExpr_ eqExpr_ = variant_155;
    struct AExpr_ call_741 = axNot_(litFalse_, eqExpr_, loc_74);
    return call_741;
}

struct AExpr_ desugarBinLe_(struct Lit_ litFalse_, struct AExpr_ l_20, struct AExpr_ r_34, struct IntIntTuple2 loc_75) {
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_473;
    tuple_473.t0 = (struct Op_){.tag = Lt_1};
    tuple_473.t1 = r_34;
    tuple_473.t2 = l_20;
    tuple_473.t3 = loc_75;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_156 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_156))) = tuple_473;
    struct AExpr_ variant_156 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_156};
    struct AExpr_ ltExpr_ = variant_156;
    struct AExpr_ call_742 = axNot_(litFalse_, ltExpr_, loc_75);
    return call_742;
}

struct AExpr_ desugarBinGt_(struct AExpr_ l_21, struct AExpr_ r_35, struct IntIntTuple2 loc_76) {
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_474;
    tuple_474.t0 = (struct Op_){.tag = Lt_1};
    tuple_474.t1 = r_35;
    tuple_474.t2 = l_21;
    tuple_474.t3 = loc_76;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_157 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_157))) = tuple_474;
    struct AExpr_ variant_157 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_157};
    return variant_157;
}

struct AExpr_ desugarBinGe_(struct Lit_ litFalse_, struct AExpr_ l_22, struct AExpr_ r_36, struct IntIntTuple2 loc_77) {
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_475;
    tuple_475.t0 = (struct Op_){.tag = Lt_1};
    tuple_475.t1 = l_22;
    tuple_475.t2 = r_36;
    tuple_475.t3 = loc_77;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_158 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_158))) = tuple_475;
    struct AExpr_ variant_158 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_158};
    struct AExpr_ ltExpr_1 = variant_158;
    struct AExpr_ call_743 = axNot_(litFalse_, ltExpr_1, loc_77);
    return call_743;
}

struct AExpr_ desugarBinAnd_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct AExpr_ l_23, struct AExpr_ r_37, struct IntIntTuple2 loc_78) {
    struct AExpr_ call_744 = axFalse_(litFalse_, loc_78);
    struct AExpr_ call_745 = desugarIf_(litFalse_, litTrue_, l_23, r_37, call_744, loc_78);
    return call_745;
}

struct AExpr_ desugarBinOr_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct AExpr_ l_24, struct AExpr_ r_38, struct IntIntTuple2 loc_79) {
    struct AExpr_ call_746 = axTrue_(litTrue_, loc_79);
    struct AExpr_ call_747 = desugarIf_(litFalse_, litTrue_, l_24, call_746, r_38, loc_79);
    return call_747;
}

struct AExpr_ desugarBinPipe_(struct AExpr_ l_25, struct AExpr_ r_39, struct IntIntTuple2 loc_80) {
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_476;
    tuple_476.t0 = (struct Op_){.tag = App_};
    tuple_476.t1 = r_39;
    tuple_476.t2 = l_25;
    tuple_476.t3 = loc_80;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_159 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_159))) = tuple_476;
    struct AExpr_ variant_159 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_159};
    return variant_159;
}

struct BoolAExpr_Tuple2 {
    int t0;
    struct AExpr_ t1;
};

struct BoolAExpr_Tuple2 tryDesugarIndexRange_(struct AExpr_ expr_19, struct IntIntTuple2 loc_81) {
    struct BoolAExpr_Tuple2 match_280;
    if ((expr_19.tag != Index_)) goto next_1078;
    struct AExpr_ s_8 = (*(expr_19.Index_)).t0;
    if (((*(expr_19.Index_)).t1.tag != Range_)) goto next_1078;
    if ((!((*((*(expr_19.Index_)).t1.Range_)).t0))) goto next_1078;
    struct AExpr_ l_26 = (*((*(expr_19.Index_)).t1.Range_)).t0->head;
    if ((!((*((*(expr_19.Index_)).t1.Range_)).t0->tail))) goto next_1078;
    struct AExpr_ r_40 = (*((*(expr_19.Index_)).t1.Range_)).t0->tail->head;
    if ((!((!((*((*(expr_19.Index_)).t1.Range_)).t0->tail->tail))))) goto next_1078;
    struct StringIntIntTuple2Tuple2 tuple_478;
    tuple_478.t0 = (struct String){.str = "String", .len = 6};
    tuple_478.t1 = loc_81;
    struct StringIntIntTuple2Tuple2* payload_160 = (struct StringIntIntTuple2Tuple2*)malloc(sizeof(struct StringIntIntTuple2Tuple2));
    (*(((struct StringIntIntTuple2Tuple2*)payload_160))) = tuple_478;
    struct AExpr_ variant_160 = (struct AExpr_){.tag = Ident_2, .Ident_2 = payload_160};
    struct AExpr_StringIntIntTuple2Tuple3 tuple_477;
    tuple_477.t0 = variant_160;
    tuple_477.t1 = (struct String){.str = "getSlice", .len = 8};
    tuple_477.t2 = loc_81;
    struct AExpr_StringIntIntTuple2Tuple3* payload_161 = (struct AExpr_StringIntIntTuple2Tuple3*)malloc(sizeof(struct AExpr_StringIntIntTuple2Tuple3));
    (*(((struct AExpr_StringIntIntTuple2Tuple3*)payload_161))) = tuple_477;
    struct AExpr_ variant_161 = (struct AExpr_){.tag = Nav_1, .Nav_1 = payload_161};
    struct AExpr_ getSlice_ = variant_161;
    struct AExpr_ call_748 = axApp3_(getSlice_, l_26, r_40, s_8, loc_81);
    struct BoolAExpr_Tuple2 tuple_479;
    tuple_479.t0 = 1;
    tuple_479.t1 = call_748;
    match_280 = tuple_479;
    goto end_match_1077;
next_1078:;
    struct BoolAExpr_Tuple2 tuple_480;
    tuple_480.t0 = 0;
    tuple_480.t1 = expr_19;
    match_280 = tuple_480;
    goto end_match_1077;
next_1079:;
end_match_1077:;
    return match_280;
}

enum ALet_Tag {
    LetVal_,
    LetFun_,
};

struct ALet_ {
    enum ALet_Tag tag;
    union {
        struct APat_AExpr_AExpr_IntIntTuple2Tuple4* LetVal_;
        struct StringAPat_ListAExpr_AExpr_IntIntTuple2Tuple5* LetFun_;
    };
};

struct StringAPat_ListAExpr_AExpr_IntIntTuple2Tuple5 {
    struct String t0;
    struct APat_List* t1;
    struct AExpr_ t2;
    struct AExpr_ t3;
    struct IntIntTuple2 t4;
};

struct ALet_ desugarLet_(struct APat_ pat_24, struct AExpr_ body_17, struct AExpr_ next_13, struct IntIntTuple2 loc_82) {
    struct ALet_ match_281;
    if ((pat_24.tag != Anno_)) goto next_1081;
    struct APat_ pat_25 = (*(pat_24.Anno_)).t0;
    struct ATy_ annoTy_ = (*(pat_24.Anno_)).t1;
    struct IntIntTuple2 annoLoc_ = (*(pat_24.Anno_)).t2;
    struct AExpr_ATy_IntIntTuple2Tuple3 tuple_481;
    tuple_481.t0 = body_17;
    tuple_481.t1 = annoTy_;
    tuple_481.t2 = annoLoc_;
    struct AExpr_ATy_IntIntTuple2Tuple3* payload_162 = (struct AExpr_ATy_IntIntTuple2Tuple3*)malloc(sizeof(struct AExpr_ATy_IntIntTuple2Tuple3));
    (*(((struct AExpr_ATy_IntIntTuple2Tuple3*)payload_162))) = tuple_481;
    struct AExpr_ variant_162 = (struct AExpr_){.tag = Anno_1, .Anno_1 = payload_162};
    struct AExpr_ body_18 = variant_162;
    struct ALet_ call_749 = desugarLet_(pat_25, body_18, next_13, loc_82);
    match_281 = call_749;
    goto end_match_1080;
next_1081:;
    if ((pat_24.tag != Fun_2)) goto next_1082;
    struct String ident_27 = (*(pat_24.Fun_2)).t0;
    struct APat_List* args_8 = (*(pat_24.Fun_2)).t1;
    struct StringAPat_ListAExpr_AExpr_IntIntTuple2Tuple5 tuple_482;
    tuple_482.t0 = ident_27;
    tuple_482.t1 = args_8;
    tuple_482.t2 = body_17;
    tuple_482.t3 = next_13;
    tuple_482.t4 = loc_82;
    struct StringAPat_ListAExpr_AExpr_IntIntTuple2Tuple5* payload_163 = (struct StringAPat_ListAExpr_AExpr_IntIntTuple2Tuple5*)malloc(sizeof(struct StringAPat_ListAExpr_AExpr_IntIntTuple2Tuple5));
    (*(((struct StringAPat_ListAExpr_AExpr_IntIntTuple2Tuple5*)payload_163))) = tuple_482;
    struct ALet_ variant_163 = (struct ALet_){.tag = LetFun_, .LetFun_ = payload_163};
    match_281 = variant_163;
    goto end_match_1080;
next_1082:;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4 tuple_483;
    tuple_483.t0 = pat_24;
    tuple_483.t1 = body_17;
    tuple_483.t2 = next_13;
    tuple_483.t3 = loc_82;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4* payload_164 = (struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct APat_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)payload_164))) = tuple_483;
    struct ALet_ variant_164 = (struct ALet_){.tag = LetVal_, .LetVal_ = payload_164};
    match_281 = variant_164;
    goto end_match_1080;
next_1083:;
end_match_1080:;
    return match_281;
}

struct Ty_NameCtx_Tuple2 fun_16(void* env_10, struct ATy_NameCtx_Tuple2 arg_37) {
    struct Ty_NameCtx_Tuple2 call_750 = onTy_(arg_37);
    return call_750;
}

struct Ty_NameCtx_Tuple2 fun_17(void* env_11, struct ATy_NameCtx_Tuple2 arg_38) {
    struct Ty_NameCtx_Tuple2 call_751 = onTy_(arg_38);
    return call_751;
}

struct Ty_NameCtx_Tuple2 onTy_(struct ATy_NameCtx_Tuple2 arg_219) {
    struct ATy_ ty_55 = arg_219.t0;
    struct NameCtx_ nameCtx_3 = arg_219.t1;
    struct Ty_NameCtx_Tuple2 match_282;
    if ((ty_55.tag != Missing_)) goto next_1085;
    struct IntIntTuple2 loc_83 = (*(ty_55.Missing_));
    struct IntIntTuple2* payload_165 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_165))) = loc_83;
    struct Ty_ variant_165 = (struct Ty_){.tag = Error_1, .Error_1 = payload_165};
    struct Ty_NameCtx_Tuple2 tuple_484;
    tuple_484.t0 = variant_165;
    tuple_484.t1 = nameCtx_3;
    match_282 = tuple_484;
    goto end_match_1084;
next_1085:;
    if ((ty_55.tag != App_1)) goto next_1086;
    struct String ident_28 = (*(ty_55.App_1)).t0;
    struct ATy_List* argTys_2 = (*(ty_55.App_1)).t1;
    struct IntNameCtx_Tuple2 call_752 = nameCtxAdd_(ident_28, nameCtx_3);
    int tySerial_1 = call_752.t0;
    struct NameCtx_ nameCtx_4 = call_752.t1;
    void* box_7 = (void*)malloc(sizeof(int));
    (*(((int*)box_7))) = 0;
    void* env_52 = box_7;
    struct ATy_NameCtx_Tuple2Ty_NameCtx_Tuple2Fun1 fun_58 = (struct ATy_NameCtx_Tuple2Ty_NameCtx_Tuple2Fun1){.fun = fun_16, .env = env_52};
    struct ATy_ListNameCtx_Tuple2 tuple_485;
    tuple_485.t0 = argTys_2;
    tuple_485.t1 = nameCtx_4;
    struct Ty_ListNameCtx_Tuple2 call_753 = stMap_5(fun_58, tuple_485);
    struct Ty_List* argTys_3 = call_753.t0;
    struct NameCtx_ nameCtx_5 = call_753.t1;
    struct Ty_ call_754 = tyRef_(tySerial_1, argTys_3);
    struct Ty_NameCtx_Tuple2 tuple_486;
    tuple_486.t0 = call_754;
    tuple_486.t1 = nameCtx_5;
    match_282 = tuple_486;
    goto end_match_1084;
next_1086:;
    if ((ty_55.tag != Suffix_)) goto next_1087;
    struct ATy_ lTy_3 = (*(ty_55.Suffix_)).t0;
    struct String ident_29 = (*(ty_55.Suffix_)).t1;
    struct ATy_NameCtx_Tuple2 tuple_487;
    tuple_487.t0 = lTy_3;
    tuple_487.t1 = nameCtx_3;
    struct Ty_NameCtx_Tuple2 call_755 = onTy_(tuple_487);
    struct Ty_ lTy_4 = call_755.t0;
    struct NameCtx_ nameCtx_6 = call_755.t1;
    struct IntNameCtx_Tuple2 call_756 = nameCtxAdd_(ident_29, nameCtx_6);
    int tySerial_2 = call_756.t0;
    struct NameCtx_ nameCtx_7 = call_756.t1;
    struct Ty_List* list_87 = (struct Ty_List*)malloc(sizeof(struct Ty_List));
    list_87->head = lTy_4;
    list_87->tail = NULL;
    struct Ty_ call_757 = tyRef_(tySerial_2, list_87);
    struct Ty_NameCtx_Tuple2 tuple_488;
    tuple_488.t0 = call_757;
    tuple_488.t1 = nameCtx_7;
    match_282 = tuple_488;
    goto end_match_1084;
next_1087:;
    if ((ty_55.tag != Tuple_)) goto next_1088;
    struct ATy_List* itemTys_2 = (*(ty_55.Tuple_)).t0;
    void* box_8 = (void*)malloc(sizeof(int));
    (*(((int*)box_8))) = 0;
    void* env_53 = box_8;
    struct ATy_NameCtx_Tuple2Ty_NameCtx_Tuple2Fun1 fun_59 = (struct ATy_NameCtx_Tuple2Ty_NameCtx_Tuple2Fun1){.fun = fun_17, .env = env_53};
    struct ATy_ListNameCtx_Tuple2 tuple_489;
    tuple_489.t0 = itemTys_2;
    tuple_489.t1 = nameCtx_3;
    struct Ty_ListNameCtx_Tuple2 call_758 = stMap_5(fun_59, tuple_489);
    struct Ty_List* itemTys_3 = call_758.t0;
    struct NameCtx_ nameCtx_8 = call_758.t1;
    struct Ty_ call_759 = tyTuple_(itemTys_3);
    struct Ty_NameCtx_Tuple2 tuple_490;
    tuple_490.t0 = call_759;
    tuple_490.t1 = nameCtx_8;
    match_282 = tuple_490;
    goto end_match_1084;
next_1088:;
    if ((ty_55.tag != Fun_1)) goto next_1089;
    struct ATy_ sTy_2 = (*(ty_55.Fun_1)).t0;
    struct ATy_ tTy_2 = (*(ty_55.Fun_1)).t1;
    struct ATy_NameCtx_Tuple2 tuple_491;
    tuple_491.t0 = sTy_2;
    tuple_491.t1 = nameCtx_3;
    struct Ty_NameCtx_Tuple2 call_760 = onTy_(tuple_491);
    struct Ty_ sTy_3 = call_760.t0;
    struct NameCtx_ nameCtx_9 = call_760.t1;
    struct ATy_NameCtx_Tuple2 tuple_492;
    tuple_492.t0 = tTy_2;
    tuple_492.t1 = nameCtx_9;
    struct Ty_NameCtx_Tuple2 call_761 = onTy_(tuple_492);
    struct Ty_ tTy_3 = call_761.t0;
    struct NameCtx_ nameCtx_10 = call_761.t1;
    struct Ty_ call_762 = tyFun_(sTy_3, tTy_3);
    struct Ty_NameCtx_Tuple2 tuple_493;
    tuple_493.t0 = call_762;
    tuple_493.t1 = nameCtx_10;
    match_282 = tuple_493;
    goto end_match_1084;
next_1089:;
    exit(1);
end_match_1084:;
    return match_282;
}

struct Ty_Tuple1 {
    struct Ty_ t0;
};

struct HPat_NameCtx_Tuple2 fun_18(void* env_12, struct APat_NameCtx_Tuple2 arg_39) {
    struct Ty_ arg_40 = (*(((struct Ty_Tuple1*)env_12))).t0;
    struct HPat_NameCtx_Tuple2 call_763 = onPat_(arg_40, arg_39);
    return call_763;
}

struct HPat_NameCtx_Tuple2 fun_19(void* env_13, struct APat_NameCtx_Tuple2 arg_41) {
    struct Ty_ arg_42 = (*(((struct Ty_Tuple1*)env_13))).t0;
    struct HPat_NameCtx_Tuple2 call_764 = onPat_(arg_42, arg_41);
    return call_764;
}

struct HPat_NameCtx_Tuple2 onPat_(struct Ty_ noTy_, struct APat_NameCtx_Tuple2 arg_220) {
    struct APat_ pat_26 = arg_220.t0;
    struct NameCtx_ nameCtx_11 = arg_220.t1;
    struct HPat_NameCtx_Tuple2 match_283;
    if ((pat_26.tag != Missing_1)) goto next_1091;
    int loc_84 = (*(pat_26.Missing_1)).t1;
    struct IntHPat_NameCtx_Tuple2Fun1 call_765 = failwithf_2((struct String){.str = "Missing pattern %A", .len = 18});
    struct HPat_NameCtx_Tuple2 app_73 = call_765.fun(call_765.env, loc_84);
    match_283 = app_73;
    goto end_match_1090;
next_1091:;
    if ((pat_26.tag != Lit_)) goto next_1092;
    struct Lit_ lit_9 = (*(pat_26.Lit_)).t0;
    struct IntIntTuple2 loc_85 = (*(pat_26.Lit_)).t1;
    struct Lit_IntIntTuple2Tuple2 tuple_495;
    tuple_495.t0 = lit_9;
    tuple_495.t1 = loc_85;
    struct Lit_IntIntTuple2Tuple2* payload_166 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_166))) = tuple_495;
    struct HPat_ variant_166 = (struct HPat_){.tag = Lit_2, .Lit_2 = payload_166};
    struct HPat_NameCtx_Tuple2 tuple_494;
    tuple_494.t0 = variant_166;
    tuple_494.t1 = nameCtx_11;
    match_283 = tuple_494;
    goto end_match_1090;
next_1092:;
    if ((pat_26.tag != Ident_1)) goto next_1093;
    struct String ident_30 = (*(pat_26.Ident_1)).t0;
    struct IntIntTuple2 loc_86 = (*(pat_26.Ident_1)).t1;
    struct IntNameCtx_Tuple2 call_766 = nameCtxAdd_(ident_30, nameCtx_11);
    int serial_11 = call_766.t0;
    struct NameCtx_ nameCtx_12 = call_766.t1;
    struct IntTy_IntIntTuple2Tuple3 tuple_497;
    tuple_497.t0 = serial_11;
    tuple_497.t1 = noTy_;
    tuple_497.t2 = loc_86;
    struct IntTy_IntIntTuple2Tuple3* payload_167 = (struct IntTy_IntIntTuple2Tuple3*)malloc(sizeof(struct IntTy_IntIntTuple2Tuple3));
    (*(((struct IntTy_IntIntTuple2Tuple3*)payload_167))) = tuple_497;
    struct HPat_ variant_167 = (struct HPat_){.tag = Ref_1, .Ref_1 = payload_167};
    struct HPat_NameCtx_Tuple2 tuple_496;
    tuple_496.t0 = variant_167;
    tuple_496.t1 = nameCtx_12;
    match_283 = tuple_496;
    goto end_match_1090;
next_1093:;
    if ((pat_26.tag != ListLit_)) goto next_1094;
    if ((!((!((*(pat_26.ListLit_)).t0))))) goto next_1094;
    struct IntIntTuple2 loc_87 = (*(pat_26.ListLit_)).t1;
    struct HPat_ call_767 = patNil_(noTy_, loc_87);
    struct HPat_NameCtx_Tuple2 tuple_498;
    tuple_498.t0 = call_767;
    tuple_498.t1 = nameCtx_11;
    match_283 = tuple_498;
    goto end_match_1090;
next_1094:;
    if ((pat_26.tag != ListLit_)) goto next_1095;
    struct APat_List* pats_7 = (*(pat_26.ListLit_)).t0;
    struct IntIntTuple2 loc_88 = (*(pat_26.ListLit_)).t1;
    struct APat_ call_768 = desugarListLitPat_(pats_7, loc_88);
    struct APat_ pat_27 = call_768;
    struct APat_NameCtx_Tuple2 tuple_499;
    tuple_499.t0 = pat_27;
    tuple_499.t1 = nameCtx_11;
    struct HPat_NameCtx_Tuple2 call_769 = onPat_(noTy_, tuple_499);
    match_283 = call_769;
    goto end_match_1090;
next_1095:;
    if ((pat_26.tag != Nav_)) goto next_1096;
    struct APat_ l_27 = (*(pat_26.Nav_)).t0;
    struct String r_41 = (*(pat_26.Nav_)).t1;
    struct IntIntTuple2 loc_89 = (*(pat_26.Nav_)).t2;
    struct APat_NameCtx_Tuple2 tuple_500;
    tuple_500.t0 = l_27;
    tuple_500.t1 = nameCtx_11;
    struct HPat_NameCtx_Tuple2 call_770 = onPat_(noTy_, tuple_500);
    struct HPat_ l_28 = call_770.t0;
    struct NameCtx_ nameCtx_13 = call_770.t1;
    struct HPat_StringTy_IntIntTuple2Tuple4 tuple_502;
    tuple_502.t0 = l_28;
    tuple_502.t1 = r_41;
    tuple_502.t2 = noTy_;
    tuple_502.t3 = loc_89;
    struct HPat_StringTy_IntIntTuple2Tuple4* payload_168 = (struct HPat_StringTy_IntIntTuple2Tuple4*)malloc(sizeof(struct HPat_StringTy_IntIntTuple2Tuple4));
    (*(((struct HPat_StringTy_IntIntTuple2Tuple4*)payload_168))) = tuple_502;
    struct HPat_ variant_168 = (struct HPat_){.tag = Nav_2, .Nav_2 = payload_168};
    struct HPat_NameCtx_Tuple2 tuple_501;
    tuple_501.t0 = variant_168;
    tuple_501.t1 = nameCtx_13;
    match_283 = tuple_501;
    goto end_match_1090;
next_1096:;
    if ((pat_26.tag != Call_)) goto next_1097;
    struct APat_ calleePat_1 = (*(pat_26.Call_)).t0;
    struct APat_List* argPats_1 = (*(pat_26.Call_)).t1;
    struct IntIntTuple2 loc_90 = (*(pat_26.Call_)).t2;
    struct APat_NameCtx_Tuple2 tuple_503;
    tuple_503.t0 = calleePat_1;
    tuple_503.t1 = nameCtx_11;
    struct HPat_NameCtx_Tuple2 call_771 = onPat_(noTy_, tuple_503);
    struct HPat_ calleePat_2 = call_771.t0;
    struct NameCtx_ nameCtx_14 = call_771.t1;
    struct Ty_Tuple1 tuple_504;
    tuple_504.t0 = noTy_;
    void* box_9 = (void*)malloc(sizeof(struct Ty_Tuple1));
    (*(((struct Ty_Tuple1*)box_9))) = tuple_504;
    void* env_54 = box_9;
    struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1 fun_60 = (struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1){.fun = fun_18, .env = env_54};
    struct APat_ListNameCtx_Tuple2 tuple_505;
    tuple_505.t0 = argPats_1;
    tuple_505.t1 = nameCtx_14;
    struct HPat_ListNameCtx_Tuple2 call_772 = stMap_2(fun_60, tuple_505);
    struct HPat_List* argPats_2 = call_772.t0;
    struct NameCtx_ nameCtx_15 = call_772.t1;
    struct HPat_HPat_ListTy_IntIntTuple2Tuple4 tuple_507;
    tuple_507.t0 = calleePat_2;
    tuple_507.t1 = argPats_2;
    tuple_507.t2 = noTy_;
    tuple_507.t3 = loc_90;
    struct HPat_HPat_ListTy_IntIntTuple2Tuple4* payload_169 = (struct HPat_HPat_ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct HPat_HPat_ListTy_IntIntTuple2Tuple4));
    (*(((struct HPat_HPat_ListTy_IntIntTuple2Tuple4*)payload_169))) = tuple_507;
    struct HPat_ variant_169 = (struct HPat_){.tag = Call_1, .Call_1 = payload_169};
    struct HPat_NameCtx_Tuple2 tuple_506;
    tuple_506.t0 = variant_169;
    tuple_506.t1 = nameCtx_15;
    match_283 = tuple_506;
    goto end_match_1090;
next_1097:;
    if ((pat_26.tag != Cons_2)) goto next_1098;
    struct APat_ head_5 = (*(pat_26.Cons_2)).t0;
    struct APat_ tail_7 = (*(pat_26.Cons_2)).t1;
    struct IntIntTuple2 loc_91 = (*(pat_26.Cons_2)).t2;
    struct APat_NameCtx_Tuple2 tuple_508;
    tuple_508.t0 = head_5;
    tuple_508.t1 = nameCtx_11;
    struct HPat_NameCtx_Tuple2 call_773 = onPat_(noTy_, tuple_508);
    struct HPat_ head_6 = call_773.t0;
    struct NameCtx_ nameCtx_16 = call_773.t1;
    struct APat_NameCtx_Tuple2 tuple_509;
    tuple_509.t0 = tail_7;
    tuple_509.t1 = nameCtx_16;
    struct HPat_NameCtx_Tuple2 call_774 = onPat_(noTy_, tuple_509);
    struct HPat_ tail_8 = call_774.t0;
    struct NameCtx_ nameCtx_17 = call_774.t1;
    struct HPat_HPat_Ty_IntIntTuple2Tuple4 tuple_511;
    tuple_511.t0 = head_6;
    tuple_511.t1 = tail_8;
    tuple_511.t2 = noTy_;
    tuple_511.t3 = loc_91;
    struct HPat_HPat_Ty_IntIntTuple2Tuple4* payload_170 = (struct HPat_HPat_Ty_IntIntTuple2Tuple4*)malloc(sizeof(struct HPat_HPat_Ty_IntIntTuple2Tuple4));
    (*(((struct HPat_HPat_Ty_IntIntTuple2Tuple4*)payload_170))) = tuple_511;
    struct HPat_ variant_170 = (struct HPat_){.tag = Cons_3, .Cons_3 = payload_170};
    struct HPat_NameCtx_Tuple2 tuple_510;
    tuple_510.t0 = variant_170;
    tuple_510.t1 = nameCtx_17;
    match_283 = tuple_510;
    goto end_match_1090;
next_1098:;
    if ((pat_26.tag != TupleLit_)) goto next_1099;
    struct APat_List* pats_8 = (*(pat_26.TupleLit_)).t0;
    struct IntIntTuple2 loc_92 = (*(pat_26.TupleLit_)).t1;
    struct Ty_Tuple1 tuple_512;
    tuple_512.t0 = noTy_;
    void* box_10 = (void*)malloc(sizeof(struct Ty_Tuple1));
    (*(((struct Ty_Tuple1*)box_10))) = tuple_512;
    void* env_55 = box_10;
    struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1 fun_61 = (struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1){.fun = fun_19, .env = env_55};
    struct APat_ListNameCtx_Tuple2 tuple_513;
    tuple_513.t0 = pats_8;
    tuple_513.t1 = nameCtx_11;
    struct HPat_ListNameCtx_Tuple2 call_775 = stMap_2(fun_61, tuple_513);
    struct HPat_List* pats_9 = call_775.t0;
    struct NameCtx_ nameCtx_18 = call_775.t1;
    struct HPat_ListTy_IntIntTuple2Tuple3 tuple_515;
    tuple_515.t0 = pats_9;
    tuple_515.t1 = noTy_;
    tuple_515.t2 = loc_92;
    struct HPat_ListTy_IntIntTuple2Tuple3* payload_171 = (struct HPat_ListTy_IntIntTuple2Tuple3*)malloc(sizeof(struct HPat_ListTy_IntIntTuple2Tuple3));
    (*(((struct HPat_ListTy_IntIntTuple2Tuple3*)payload_171))) = tuple_515;
    struct HPat_ variant_171 = (struct HPat_){.tag = Tuple_2, .Tuple_2 = payload_171};
    struct HPat_NameCtx_Tuple2 tuple_514;
    tuple_514.t0 = variant_171;
    tuple_514.t1 = nameCtx_18;
    match_283 = tuple_514;
    goto end_match_1090;
next_1099:;
    if ((pat_26.tag != As_1)) goto next_1100;
    struct APat_ pat_28 = (*(pat_26.As_1)).t0;
    struct String ident_31 = (*(pat_26.As_1)).t1;
    struct IntIntTuple2 loc_93 = (*(pat_26.As_1)).t2;
    struct IntNameCtx_Tuple2 call_776 = nameCtxAdd_(ident_31, nameCtx_11);
    int serial_12 = call_776.t0;
    struct NameCtx_ nameCtx_19 = call_776.t1;
    struct APat_NameCtx_Tuple2 tuple_516;
    tuple_516.t0 = pat_28;
    tuple_516.t1 = nameCtx_19;
    struct HPat_NameCtx_Tuple2 call_777 = onPat_(noTy_, tuple_516);
    struct HPat_ pat_29 = call_777.t0;
    struct NameCtx_ nameCtx_20 = call_777.t1;
    struct HPat_IntIntIntTuple2Tuple3 tuple_518;
    tuple_518.t0 = pat_29;
    tuple_518.t1 = serial_12;
    tuple_518.t2 = loc_93;
    struct HPat_IntIntIntTuple2Tuple3* payload_172 = (struct HPat_IntIntIntTuple2Tuple3*)malloc(sizeof(struct HPat_IntIntIntTuple2Tuple3));
    (*(((struct HPat_IntIntIntTuple2Tuple3*)payload_172))) = tuple_518;
    struct HPat_ variant_172 = (struct HPat_){.tag = As_2, .As_2 = payload_172};
    struct HPat_NameCtx_Tuple2 tuple_517;
    tuple_517.t0 = variant_172;
    tuple_517.t1 = nameCtx_20;
    match_283 = tuple_517;
    goto end_match_1090;
next_1100:;
    if ((pat_26.tag != Anno_)) goto next_1101;
    struct APat_ pat_30 = (*(pat_26.Anno_)).t0;
    struct ATy_ ty_56 = (*(pat_26.Anno_)).t1;
    struct IntIntTuple2 loc_94 = (*(pat_26.Anno_)).t2;
    struct APat_NameCtx_Tuple2 tuple_519;
    tuple_519.t0 = pat_30;
    tuple_519.t1 = nameCtx_11;
    struct HPat_NameCtx_Tuple2 call_778 = onPat_(noTy_, tuple_519);
    struct HPat_ pat_31 = call_778.t0;
    struct NameCtx_ nameCtx_21 = call_778.t1;
    struct ATy_NameCtx_Tuple2 tuple_520;
    tuple_520.t0 = ty_56;
    tuple_520.t1 = nameCtx_21;
    struct Ty_NameCtx_Tuple2 call_779 = onTy_(tuple_520);
    struct Ty_ ty_57 = call_779.t0;
    struct NameCtx_ nameCtx_22 = call_779.t1;
    struct HPat_Ty_IntIntTuple2Tuple3 tuple_522;
    tuple_522.t0 = pat_31;
    tuple_522.t1 = ty_57;
    tuple_522.t2 = loc_94;
    struct HPat_Ty_IntIntTuple2Tuple3* payload_173 = (struct HPat_Ty_IntIntTuple2Tuple3*)malloc(sizeof(struct HPat_Ty_IntIntTuple2Tuple3));
    (*(((struct HPat_Ty_IntIntTuple2Tuple3*)payload_173))) = tuple_522;
    struct HPat_ variant_173 = (struct HPat_){.tag = Anno_2, .Anno_2 = payload_173};
    struct HPat_NameCtx_Tuple2 tuple_521;
    tuple_521.t0 = variant_173;
    tuple_521.t1 = nameCtx_22;
    match_283 = tuple_521;
    goto end_match_1090;
next_1101:;
    if ((pat_26.tag != Or_2)) goto next_1102;
    struct APat_ l_29 = (*(pat_26.Or_2)).t0;
    struct APat_ r_42 = (*(pat_26.Or_2)).t1;
    struct IntIntTuple2 loc_95 = (*(pat_26.Or_2)).t2;
    struct APat_NameCtx_Tuple2 tuple_523;
    tuple_523.t0 = l_29;
    tuple_523.t1 = nameCtx_11;
    struct HPat_NameCtx_Tuple2 call_780 = onPat_(noTy_, tuple_523);
    struct HPat_ l_30 = call_780.t0;
    struct NameCtx_ nameCtx_23 = call_780.t1;
    struct APat_NameCtx_Tuple2 tuple_524;
    tuple_524.t0 = r_42;
    tuple_524.t1 = nameCtx_23;
    struct HPat_NameCtx_Tuple2 call_781 = onPat_(noTy_, tuple_524);
    struct HPat_ r_43 = call_781.t0;
    struct NameCtx_ nameCtx_24 = call_781.t1;
    struct HPat_HPat_Ty_IntIntTuple2Tuple4 tuple_526;
    tuple_526.t0 = l_30;
    tuple_526.t1 = r_43;
    tuple_526.t2 = noTy_;
    tuple_526.t3 = loc_95;
    struct HPat_HPat_Ty_IntIntTuple2Tuple4* payload_174 = (struct HPat_HPat_Ty_IntIntTuple2Tuple4*)malloc(sizeof(struct HPat_HPat_Ty_IntIntTuple2Tuple4));
    (*(((struct HPat_HPat_Ty_IntIntTuple2Tuple4*)payload_174))) = tuple_526;
    struct HPat_ variant_174 = (struct HPat_){.tag = Or_3, .Or_3 = payload_174};
    struct HPat_NameCtx_Tuple2 tuple_525;
    tuple_525.t0 = variant_174;
    tuple_525.t1 = nameCtx_24;
    match_283 = tuple_525;
    goto end_match_1090;
next_1102:;
    if ((pat_26.tag != Fun_2)) goto next_1103;
    struct IntIntTuple2 loc_96 = (*(pat_26.Fun_2)).t2;
    struct IntIntTuple2HPat_NameCtx_Tuple2Fun1 call_782 = failwithf_1((struct String){.str = "Invalid occurrence of fun pattern: %A", .len = 37});
    struct HPat_NameCtx_Tuple2 app_74 = call_782.fun(call_782.env, loc_96);
    match_283 = app_74;
    goto end_match_1090;
next_1103:;
    exit(1);
end_match_1090:;
    return match_283;
}

struct HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2 onArm_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, struct AArm_NameCtx_Tuple2 arg_221) {
    struct APat_ pat_32 = (*(arg_221.t0.AArm_)).t0;
    struct AExpr_ guard_4 = (*(arg_221.t0.AArm_)).t1;
    struct AExpr_ body_20 = (*(arg_221.t0.AArm_)).t2;
    struct IntIntTuple2 loc_104 = (*(arg_221.t0.AArm_)).t3;
    struct NameCtx_ nameCtx_27 = arg_221.t1;
    struct APat_NameCtx_Tuple2 tuple_527;
    tuple_527.t0 = pat_32;
    tuple_527.t1 = nameCtx_27;
    struct HPat_NameCtx_Tuple2 call_783 = onPat_(noTy_, tuple_527);
    struct HPat_ pat_33 = call_783.t0;
    struct NameCtx_ nameCtx_28 = call_783.t1;
    struct HExpr_NameCtx_Tuple2 match_284;
    if ((guard_4.tag != Missing_2)) goto next_1105;
    struct HExpr_ call_784 = hxTrue_(litTrue_, loc_104);
    struct HExpr_NameCtx_Tuple2 tuple_528;
    tuple_528.t0 = call_784;
    tuple_528.t1 = nameCtx_28;
    match_284 = tuple_528;
    goto end_match_1104;
next_1105:;
    struct AExpr_NameCtx_Tuple2 tuple_529;
    tuple_529.t0 = guard_4;
    tuple_529.t1 = nameCtx_28;
    struct HExpr_NameCtx_Tuple2 call_785 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_529);
    match_284 = call_785;
    goto end_match_1104;
next_1106:;
end_match_1104:;
    struct HExpr_ guard_5 = match_284.t0;
    struct NameCtx_ nameCtx_29 = match_284.t1;
    struct AExpr_NameCtx_Tuple2 tuple_530;
    tuple_530.t0 = body_20;
    tuple_530.t1 = nameCtx_29;
    struct HExpr_NameCtx_Tuple2 call_786 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_530);
    struct HExpr_ body_21 = call_786.t0;
    struct NameCtx_ nameCtx_30 = call_786.t1;
    struct HPat_HExpr_HExpr_Tuple3 tuple_532;
    tuple_532.t0 = pat_33;
    tuple_532.t1 = guard_5;
    tuple_532.t2 = body_21;
    struct HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2 tuple_531;
    tuple_531.t0 = tuple_532;
    tuple_531.t1 = nameCtx_30;
    return tuple_531;
}

struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8 {
    struct Lit_ t0;
    struct Lit_ t1;
    struct Ty_ t2;
    struct Ty_ t3;
    struct Ty_ t4;
    struct Ty_ t5;
    struct Ty_ t6;
    struct Ty_ t7;
};

struct HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2 fun_20(void* env_14, struct AArm_NameCtx_Tuple2 arg_43) {
    struct Lit_ arg_44 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_14))).t0;
    struct Lit_ arg_45 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_14))).t1;
    struct Ty_ arg_46 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_14))).t2;
    struct Ty_ arg_47 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_14))).t3;
    struct Ty_ arg_48 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_14))).t4;
    struct Ty_ arg_49 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_14))).t5;
    struct Ty_ arg_50 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_14))).t6;
    struct Ty_ arg_51 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_14))).t7;
    struct HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2 call_787 = onArm_(arg_44, arg_45, arg_46, arg_47, arg_48, arg_49, arg_50, arg_51, arg_43);
    return call_787;
}

struct HExpr_NameCtx_Tuple2 fun_21(void* env_15, struct AExpr_NameCtx_Tuple2 arg_52) {
    struct Lit_ arg_53 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_15))).t0;
    struct Lit_ arg_54 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_15))).t1;
    struct Ty_ arg_55 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_15))).t2;
    struct Ty_ arg_56 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_15))).t3;
    struct Ty_ arg_57 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_15))).t4;
    struct Ty_ arg_58 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_15))).t5;
    struct Ty_ arg_59 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_15))).t6;
    struct Ty_ arg_60 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_15))).t7;
    struct HExpr_NameCtx_Tuple2 call_788 = onExpr_(arg_53, arg_54, arg_55, arg_56, arg_57, arg_58, arg_59, arg_60, arg_52);
    return call_788;
}

struct HExpr_NameCtx_Tuple2 fun_22(void* env_16, struct AExpr_NameCtx_Tuple2 arg_61) {
    struct Lit_ arg_62 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_16))).t0;
    struct Lit_ arg_63 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_16))).t1;
    struct Ty_ arg_64 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_16))).t2;
    struct Ty_ arg_65 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_16))).t3;
    struct Ty_ arg_66 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_16))).t4;
    struct Ty_ arg_67 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_16))).t5;
    struct Ty_ arg_68 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_16))).t6;
    struct Ty_ arg_69 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_16))).t7;
    struct HExpr_NameCtx_Tuple2 call_789 = onExpr_(arg_62, arg_63, arg_64, arg_65, arg_66, arg_67, arg_68, arg_69, arg_61);
    return call_789;
}

struct HPat_NameCtx_Tuple2 fun_23(void* env_17, struct APat_NameCtx_Tuple2 arg_70) {
    struct Ty_ arg_71 = (*(((struct Ty_Tuple1*)env_17))).t0;
    struct HPat_NameCtx_Tuple2 call_790 = onPat_(arg_71, arg_70);
    return call_790;
}

struct BoolTy_NameCtx_Tuple3 {
    int t0;
    struct Ty_ t1;
    struct NameCtx_ t2;
};

struct StringIntBoolTy_Tuple4NameCtx_Tuple2 onVariant_(struct Ty_ tyUnit_, struct AVariant_NameCtx_Tuple2 arg_222) {
    struct String ident_36 = (*(arg_222.t0.AVariant_)).t0;
    struct ATy_List* payloadTy_1 = (*(arg_222.t0.AVariant_)).t1;
    struct IntIntTuple2 _variantLoc_ = (*(arg_222.t0.AVariant_)).t2;
    struct NameCtx_ nameCtx_53 = arg_222.t1;
    struct IntNameCtx_Tuple2 call_791 = nameCtxAdd_(ident_36, nameCtx_53);
    int serial_16 = call_791.t0;
    struct NameCtx_ nameCtx_54 = call_791.t1;
    struct BoolTy_NameCtx_Tuple3 match_285;
    if ((!(payloadTy_1))) goto next_1108;
    struct ATy_ ty_62 = payloadTy_1->head;
    if ((!((!(payloadTy_1->tail))))) goto next_1108;
    struct ATy_NameCtx_Tuple2 tuple_533;
    tuple_533.t0 = ty_62;
    tuple_533.t1 = nameCtx_54;
    struct Ty_NameCtx_Tuple2 call_792 = onTy_(tuple_533);
    struct Ty_ ty_63 = call_792.t0;
    struct NameCtx_ nameCtx_56 = call_792.t1;
    struct BoolTy_NameCtx_Tuple3 tuple_534;
    tuple_534.t0 = 1;
    tuple_534.t1 = ty_63;
    tuple_534.t2 = nameCtx_56;
    match_285 = tuple_534;
    goto end_match_1107;
next_1108:;
    if ((!((!(payloadTy_1))))) goto next_1109;
    struct BoolTy_NameCtx_Tuple3 tuple_535;
    tuple_535.t0 = 0;
    tuple_535.t1 = tyUnit_;
    tuple_535.t2 = nameCtx_54;
    match_285 = tuple_535;
    goto end_match_1107;
next_1109:;
    exit(1);
end_match_1107:;
    int hasPayload_ = match_285.t0;
    struct Ty_ payloadTy_2 = match_285.t1;
    struct NameCtx_ nameCtx_55 = match_285.t2;
    struct StringIntBoolTy_Tuple4 tuple_537;
    tuple_537.t0 = ident_36;
    tuple_537.t1 = serial_16;
    tuple_537.t2 = hasPayload_;
    tuple_537.t3 = payloadTy_2;
    struct StringIntBoolTy_Tuple4NameCtx_Tuple2 tuple_536;
    tuple_536.t0 = tuple_537;
    tuple_536.t1 = nameCtx_55;
    return tuple_536;
}

struct StringIntBoolTy_Tuple4NameCtx_Tuple2 fun_24(void* env_18, struct AVariant_NameCtx_Tuple2 arg_72) {
    struct Ty_ arg_73 = (*(((struct Ty_Tuple1*)env_18))).t0;
    struct StringIntBoolTy_Tuple4NameCtx_Tuple2 call_793 = onVariant_(arg_73, arg_72);
    return call_793;
}

struct StringStringIntBoolTy_Tuple4ListIntIntTuple2Tuple3 {
    struct String t0;
    struct StringIntBoolTy_Tuple4List* t1;
    struct IntIntTuple2 t2;
};

struct HExpr_NameCtx_Tuple2 onExpr_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, struct AExpr_NameCtx_Tuple2 arg_223) {
    struct AExpr_ expr_20 = arg_223.t0;
    struct NameCtx_ nameCtx_25 = arg_223.t1;
    struct HExpr_NameCtx_Tuple2 match_286;
    if ((expr_20.tag != Missing_2)) goto next_1111;
    struct IntIntTuple2 loc_97 = (*(expr_20.Missing_2));
    struct StringIntIntTuple2Tuple2 tuple_539;
    tuple_539.t0 = (struct String){.str = "Missing expression", .len = 18};
    tuple_539.t1 = loc_97;
    struct StringIntIntTuple2Tuple2* payload_175 = (struct StringIntIntTuple2Tuple2*)malloc(sizeof(struct StringIntIntTuple2Tuple2));
    (*(((struct StringIntIntTuple2Tuple2*)payload_175))) = tuple_539;
    struct HExpr_ variant_175 = (struct HExpr_){.tag = Error_2, .Error_2 = payload_175};
    struct HExpr_NameCtx_Tuple2 tuple_538;
    tuple_538.t0 = variant_175;
    tuple_538.t1 = nameCtx_25;
    match_286 = tuple_538;
    goto end_match_1110;
next_1111:;
    if ((expr_20.tag != Lit_1)) goto next_1112;
    struct Lit_ lit_10 = (*(expr_20.Lit_1)).t0;
    struct IntIntTuple2 loc_98 = (*(expr_20.Lit_1)).t1;
    struct Lit_IntIntTuple2Tuple2 tuple_541;
    tuple_541.t0 = lit_10;
    tuple_541.t1 = loc_98;
    struct Lit_IntIntTuple2Tuple2* payload_176 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_176))) = tuple_541;
    struct HExpr_ variant_176 = (struct HExpr_){.tag = Lit_3, .Lit_3 = payload_176};
    struct HExpr_NameCtx_Tuple2 tuple_540;
    tuple_540.t0 = variant_176;
    tuple_540.t1 = nameCtx_25;
    match_286 = tuple_540;
    goto end_match_1110;
next_1112:;
    if ((expr_20.tag != Ident_2)) goto next_1113;
    struct String ident_32 = (*(expr_20.Ident_2)).t0;
    struct IntIntTuple2 loc_99 = (*(expr_20.Ident_2)).t1;
    struct IntNameCtx_Tuple2 call_794 = nameCtxAdd_(ident_32, nameCtx_25);
    int serial_13 = call_794.t0;
    struct NameCtx_ nameCtx_26 = call_794.t1;
    struct IntTy_IntIntTuple2Tuple3 tuple_543;
    tuple_543.t0 = serial_13;
    tuple_543.t1 = noTy_;
    tuple_543.t2 = loc_99;
    struct IntTy_IntIntTuple2Tuple3* payload_177 = (struct IntTy_IntIntTuple2Tuple3*)malloc(sizeof(struct IntTy_IntIntTuple2Tuple3));
    (*(((struct IntTy_IntIntTuple2Tuple3*)payload_177))) = tuple_543;
    struct HExpr_ variant_177 = (struct HExpr_){.tag = Ref_2, .Ref_2 = payload_177};
    struct HExpr_NameCtx_Tuple2 tuple_542;
    tuple_542.t0 = variant_177;
    tuple_542.t1 = nameCtx_26;
    match_286 = tuple_542;
    goto end_match_1110;
next_1113:;
    if ((expr_20.tag != ListLit_1)) goto next_1114;
    if ((!((!((*(expr_20.ListLit_1)).t0))))) goto next_1114;
    struct IntIntTuple2 loc_100 = (*(expr_20.ListLit_1)).t1;
    struct HExpr_ call_795 = hxNil_(noTy_, loc_100);
    struct HExpr_NameCtx_Tuple2 tuple_544;
    tuple_544.t0 = call_795;
    tuple_544.t1 = nameCtx_25;
    match_286 = tuple_544;
    goto end_match_1110;
next_1114:;
    if ((expr_20.tag != ListLit_1)) goto next_1115;
    struct AExpr_List* items_11 = (*(expr_20.ListLit_1)).t0;
    struct IntIntTuple2 loc_101 = (*(expr_20.ListLit_1)).t1;
    struct AExpr_ call_796 = desugarListLitExpr_(items_11, loc_101);
    struct AExpr_ expr_21 = call_796;
    struct AExpr_NameCtx_Tuple2 tuple_545;
    tuple_545.t0 = expr_21;
    tuple_545.t1 = nameCtx_25;
    struct HExpr_NameCtx_Tuple2 call_797 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_545);
    match_286 = call_797;
    goto end_match_1110;
next_1115:;
    if ((expr_20.tag != If_1)) goto next_1116;
    struct AExpr_ cond_3 = (*(expr_20.If_1)).t0;
    struct AExpr_ body_19 = (*(expr_20.If_1)).t1;
    struct AExpr_ alt_4 = (*(expr_20.If_1)).t2;
    struct IntIntTuple2 loc_102 = (*(expr_20.If_1)).t3;
    struct AExpr_ call_798 = desugarIf_(litFalse_, litTrue_, cond_3, body_19, alt_4, loc_102);
    struct AExpr_ expr_22 = call_798;
    struct AExpr_NameCtx_Tuple2 tuple_546;
    tuple_546.t0 = expr_22;
    tuple_546.t1 = nameCtx_25;
    struct HExpr_NameCtx_Tuple2 call_799 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_546);
    match_286 = call_799;
    goto end_match_1110;
next_1116:;
    if ((expr_20.tag != Match_1)) goto next_1117;
    struct AExpr_ target_4 = (*(expr_20.Match_1)).t0;
    struct AArm_List* arms_5 = (*(expr_20.Match_1)).t1;
    struct IntIntTuple2 loc_103 = (*(expr_20.Match_1)).t2;
    struct AExpr_NameCtx_Tuple2 tuple_547;
    tuple_547.t0 = target_4;
    tuple_547.t1 = nameCtx_25;
    struct HExpr_NameCtx_Tuple2 call_800 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_547);
    struct HExpr_ target_5 = call_800.t0;
    struct NameCtx_ nameCtx_31 = call_800.t1;
    struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8 tuple_548;
    tuple_548.t0 = litFalse_;
    tuple_548.t1 = litTrue_;
    tuple_548.t2 = tyUnit_;
    tuple_548.t3 = tyStr_;
    tuple_548.t4 = tyChar_;
    tuple_548.t5 = tyInt_;
    tuple_548.t6 = tyBool_;
    tuple_548.t7 = noTy_;
    void* box_11 = (void*)malloc(sizeof(struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8));
    (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)box_11))) = tuple_548;
    void* env_56 = box_11;
    struct AArm_NameCtx_Tuple2HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2Fun1 fun_62 = (struct AArm_NameCtx_Tuple2HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2Fun1){.fun = fun_20, .env = env_56};
    struct AArm_ListNameCtx_Tuple2 tuple_549;
    tuple_549.t0 = arms_5;
    tuple_549.t1 = nameCtx_31;
    struct HPat_HExpr_HExpr_Tuple3ListNameCtx_Tuple2 call_801 = stMap_4(fun_62, tuple_549);
    struct HPat_HExpr_HExpr_Tuple3List* arms_6 = call_801.t0;
    struct NameCtx_ nameCtx_32 = call_801.t1;
    struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4 tuple_551;
    tuple_551.t0 = target_5;
    tuple_551.t1 = arms_6;
    tuple_551.t2 = noTy_;
    tuple_551.t3 = loc_103;
    struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4* payload_178 = (struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4));
    (*(((struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4*)payload_178))) = tuple_551;
    struct HExpr_ variant_178 = (struct HExpr_){.tag = Match_2, .Match_2 = payload_178};
    struct HExpr_NameCtx_Tuple2 tuple_550;
    tuple_550.t0 = variant_178;
    tuple_550.t1 = nameCtx_32;
    match_286 = tuple_550;
    goto end_match_1110;
next_1117:;
    if ((expr_20.tag != Fun_3)) goto next_1118;
    struct APat_List* pats_10 = (*(expr_20.Fun_3)).t0;
    struct AExpr_ body_22 = (*(expr_20.Fun_3)).t1;
    struct IntIntTuple2 loc_105 = (*(expr_20.Fun_3)).t2;
    struct AExpr_ call_802 = desugarFun_(pats_10, body_22, loc_105);
    struct AExpr_ expr_23 = call_802;
    struct AExpr_NameCtx_Tuple2 tuple_552;
    tuple_552.t0 = expr_23;
    tuple_552.t1 = nameCtx_25;
    struct HExpr_NameCtx_Tuple2 call_803 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_552);
    match_286 = call_803;
    goto end_match_1110;
next_1118:;
    if ((expr_20.tag != Nav_1)) goto next_1119;
    struct AExpr_ l_31 = (*(expr_20.Nav_1)).t0;
    struct String r_44 = (*(expr_20.Nav_1)).t1;
    struct IntIntTuple2 loc_106 = (*(expr_20.Nav_1)).t2;
    struct AExpr_NameCtx_Tuple2 tuple_553;
    tuple_553.t0 = l_31;
    tuple_553.t1 = nameCtx_25;
    struct HExpr_NameCtx_Tuple2 call_804 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_553);
    struct HExpr_ l_32 = call_804.t0;
    struct NameCtx_ nameCtx_33 = call_804.t1;
    struct HExpr_StringTy_IntIntTuple2Tuple4 tuple_555;
    tuple_555.t0 = l_32;
    tuple_555.t1 = r_44;
    tuple_555.t2 = noTy_;
    tuple_555.t3 = loc_106;
    struct HExpr_StringTy_IntIntTuple2Tuple4* payload_179 = (struct HExpr_StringTy_IntIntTuple2Tuple4*)malloc(sizeof(struct HExpr_StringTy_IntIntTuple2Tuple4));
    (*(((struct HExpr_StringTy_IntIntTuple2Tuple4*)payload_179))) = tuple_555;
    struct HExpr_ variant_179 = (struct HExpr_){.tag = Nav_3, .Nav_3 = payload_179};
    struct HExpr_NameCtx_Tuple2 tuple_554;
    tuple_554.t0 = variant_179;
    tuple_554.t1 = nameCtx_33;
    match_286 = tuple_554;
    goto end_match_1110;
next_1119:;
    if ((expr_20.tag != Index_)) goto next_1120;
    struct AExpr_ l_33 = (*(expr_20.Index_)).t0;
    struct AExpr_ r_45 = (*(expr_20.Index_)).t1;
    struct IntIntTuple2 loc_107 = (*(expr_20.Index_)).t2;
    struct HExpr_NameCtx_Tuple2 match_287;
    struct BoolAExpr_Tuple2 call_805 = tryDesugarIndexRange_(expr_20, loc_107);
    if ((!(call_805.t0))) goto next_1140;
    struct AExpr_ expr_24 = call_805.t1;
    struct AExpr_NameCtx_Tuple2 tuple_556;
    tuple_556.t0 = expr_24;
    tuple_556.t1 = nameCtx_25;
    struct HExpr_NameCtx_Tuple2 call_806 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_556);
    match_287 = call_806;
    goto end_match_1139;
next_1140:;
    if (call_805.t0) goto next_1141;
    struct AExpr_NameCtx_Tuple2 tuple_557;
    tuple_557.t0 = l_33;
    tuple_557.t1 = nameCtx_25;
    struct HExpr_NameCtx_Tuple2 call_807 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_557);
    struct HExpr_ l_34 = call_807.t0;
    struct NameCtx_ nameCtx_34 = call_807.t1;
    struct AExpr_NameCtx_Tuple2 tuple_558;
    tuple_558.t0 = r_45;
    tuple_558.t1 = nameCtx_34;
    struct HExpr_NameCtx_Tuple2 call_808 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_558);
    struct HExpr_ r_46 = call_808.t0;
    struct NameCtx_ nameCtx_35 = call_808.t1;
    struct HPrim_Ty_IntIntTuple2Tuple3 tuple_559;
    tuple_559.t0 = (struct HPrim_){.tag = Index_2};
    tuple_559.t1 = noTy_;
    tuple_559.t2 = loc_107;
    struct HPrim_Ty_IntIntTuple2Tuple3* payload_180 = (struct HPrim_Ty_IntIntTuple2Tuple3*)malloc(sizeof(struct HPrim_Ty_IntIntTuple2Tuple3));
    (*(((struct HPrim_Ty_IntIntTuple2Tuple3*)payload_180))) = tuple_559;
    struct HExpr_ variant_180 = (struct HExpr_){.tag = Prim_, .Prim_ = payload_180};
    struct HExpr_ call_809 = hxApp_(variant_180, l_34, noTy_, loc_107);
    struct HExpr_ call_810 = hxApp_(call_809, r_46, noTy_, loc_107);
    struct HExpr_ hxIndex_ = call_810;
    struct HExpr_NameCtx_Tuple2 tuple_560;
    tuple_560.t0 = hxIndex_;
    tuple_560.t1 = nameCtx_35;
    match_287 = tuple_560;
    goto end_match_1139;
next_1141:;
    exit(1);
end_match_1139:;
    match_286 = match_287;
    goto end_match_1110;
next_1120:;
    if ((expr_20.tag != Uni_)) goto next_1121;
    if (((*(expr_20.Uni_)).t0.tag != Neg_)) goto next_1121;
    struct AExpr_ arg_5 = (*(expr_20.Uni_)).t1;
    struct IntIntTuple2 loc_108 = (*(expr_20.Uni_)).t2;
    struct AExpr_ call_811 = desugarUniNeg_(arg_5, loc_108);
    struct AExpr_ expr_25 = call_811;
    struct AExpr_NameCtx_Tuple2 tuple_561;
    tuple_561.t0 = expr_25;
    tuple_561.t1 = nameCtx_25;
    struct HExpr_NameCtx_Tuple2 call_812 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_561);
    match_286 = call_812;
    goto end_match_1110;
next_1121:;
    if ((expr_20.tag != Bin_)) goto next_1122;
    if (((*(expr_20.Bin_)).t0.tag != Ne_)) goto next_1122;
    struct AExpr_ l_35 = (*(expr_20.Bin_)).t1;
    struct AExpr_ r_47 = (*(expr_20.Bin_)).t2;
    struct IntIntTuple2 loc_109 = (*(expr_20.Bin_)).t3;
    struct AExpr_ call_813 = desugarBinNe_(litFalse_, l_35, r_47, loc_109);
    struct AExpr_ expr_26 = call_813;
    struct AExpr_NameCtx_Tuple2 tuple_562;
    tuple_562.t0 = expr_26;
    tuple_562.t1 = nameCtx_25;
    struct HExpr_NameCtx_Tuple2 call_814 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_562);
    match_286 = call_814;
    goto end_match_1110;
next_1122:;
    if ((expr_20.tag != Bin_)) goto next_1123;
    if (((*(expr_20.Bin_)).t0.tag != Le_)) goto next_1123;
    struct AExpr_ l_36 = (*(expr_20.Bin_)).t1;
    struct AExpr_ r_48 = (*(expr_20.Bin_)).t2;
    struct IntIntTuple2 loc_110 = (*(expr_20.Bin_)).t3;
    struct AExpr_ call_815 = desugarBinLe_(litFalse_, l_36, r_48, loc_110);
    struct AExpr_ expr_27 = call_815;
    struct AExpr_NameCtx_Tuple2 tuple_563;
    tuple_563.t0 = expr_27;
    tuple_563.t1 = nameCtx_25;
    struct HExpr_NameCtx_Tuple2 call_816 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_563);
    match_286 = call_816;
    goto end_match_1110;
next_1123:;
    if ((expr_20.tag != Bin_)) goto next_1124;
    if (((*(expr_20.Bin_)).t0.tag != Gt_1)) goto next_1124;
    struct AExpr_ l_37 = (*(expr_20.Bin_)).t1;
    struct AExpr_ r_49 = (*(expr_20.Bin_)).t2;
    struct IntIntTuple2 loc_111 = (*(expr_20.Bin_)).t3;
    struct AExpr_ call_817 = desugarBinGt_(l_37, r_49, loc_111);
    struct AExpr_ expr_28 = call_817;
    struct AExpr_NameCtx_Tuple2 tuple_564;
    tuple_564.t0 = expr_28;
    tuple_564.t1 = nameCtx_25;
    struct HExpr_NameCtx_Tuple2 call_818 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_564);
    match_286 = call_818;
    goto end_match_1110;
next_1124:;
    if ((expr_20.tag != Bin_)) goto next_1125;
    if (((*(expr_20.Bin_)).t0.tag != Ge_)) goto next_1125;
    struct AExpr_ l_38 = (*(expr_20.Bin_)).t1;
    struct AExpr_ r_50 = (*(expr_20.Bin_)).t2;
    struct IntIntTuple2 loc_112 = (*(expr_20.Bin_)).t3;
    struct AExpr_ call_819 = desugarBinGe_(litFalse_, l_38, r_50, loc_112);
    struct AExpr_ expr_29 = call_819;
    struct AExpr_NameCtx_Tuple2 tuple_565;
    tuple_565.t0 = expr_29;
    tuple_565.t1 = nameCtx_25;
    struct HExpr_NameCtx_Tuple2 call_820 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_565);
    match_286 = call_820;
    goto end_match_1110;
next_1125:;
    if ((expr_20.tag != Bin_)) goto next_1126;
    if (((*(expr_20.Bin_)).t0.tag != And_1)) goto next_1126;
    struct AExpr_ l_39 = (*(expr_20.Bin_)).t1;
    struct AExpr_ r_51 = (*(expr_20.Bin_)).t2;
    struct IntIntTuple2 loc_113 = (*(expr_20.Bin_)).t3;
    struct AExpr_ call_821 = desugarBinAnd_(litFalse_, litTrue_, l_39, r_51, loc_113);
    struct AExpr_ expr_30 = call_821;
    struct AExpr_NameCtx_Tuple2 tuple_566;
    tuple_566.t0 = expr_30;
    tuple_566.t1 = nameCtx_25;
    struct HExpr_NameCtx_Tuple2 call_822 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_566);
    match_286 = call_822;
    goto end_match_1110;
next_1126:;
    if ((expr_20.tag != Bin_)) goto next_1127;
    if (((*(expr_20.Bin_)).t0.tag != Or_1)) goto next_1127;
    struct AExpr_ l_40 = (*(expr_20.Bin_)).t1;
    struct AExpr_ r_52 = (*(expr_20.Bin_)).t2;
    struct IntIntTuple2 loc_114 = (*(expr_20.Bin_)).t3;
    struct AExpr_ call_823 = desugarBinOr_(litFalse_, litTrue_, l_40, r_52, loc_114);
    struct AExpr_ expr_31 = call_823;
    struct AExpr_NameCtx_Tuple2 tuple_567;
    tuple_567.t0 = expr_31;
    tuple_567.t1 = nameCtx_25;
    struct HExpr_NameCtx_Tuple2 call_824 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_567);
    match_286 = call_824;
    goto end_match_1110;
next_1127:;
    if ((expr_20.tag != Bin_)) goto next_1128;
    if (((*(expr_20.Bin_)).t0.tag != Pipe_2)) goto next_1128;
    struct AExpr_ l_41 = (*(expr_20.Bin_)).t1;
    struct AExpr_ r_53 = (*(expr_20.Bin_)).t2;
    struct IntIntTuple2 loc_115 = (*(expr_20.Bin_)).t3;
    struct AExpr_ call_825 = desugarBinPipe_(l_41, r_53, loc_115);
    struct AExpr_ expr_32 = call_825;
    struct AExpr_NameCtx_Tuple2 tuple_568;
    tuple_568.t0 = expr_32;
    tuple_568.t1 = nameCtx_25;
    struct HExpr_NameCtx_Tuple2 call_826 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_568);
    match_286 = call_826;
    goto end_match_1110;
next_1128:;
    if ((expr_20.tag != Bin_)) goto next_1129;
    if (((*(expr_20.Bin_)).t0.tag != App_)) goto next_1129;
    struct AExpr_ l_42 = (*(expr_20.Bin_)).t1;
    struct AExpr_ r_54 = (*(expr_20.Bin_)).t2;
    struct IntIntTuple2 loc_116 = (*(expr_20.Bin_)).t3;
    struct AExpr_NameCtx_Tuple2 tuple_569;
    tuple_569.t0 = l_42;
    tuple_569.t1 = nameCtx_25;
    struct HExpr_NameCtx_Tuple2 call_827 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_569);
    struct HExpr_ l_43 = call_827.t0;
    struct NameCtx_ nameCtx_36 = call_827.t1;
    struct AExpr_NameCtx_Tuple2 tuple_570;
    tuple_570.t0 = r_54;
    tuple_570.t1 = nameCtx_36;
    struct HExpr_NameCtx_Tuple2 call_828 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_570);
    struct HExpr_ r_55 = call_828.t0;
    struct NameCtx_ nameCtx_37 = call_828.t1;
    struct HExpr_ call_829 = hxApp_(l_43, r_55, noTy_, loc_116);
    struct HExpr_NameCtx_Tuple2 tuple_571;
    tuple_571.t0 = call_829;
    tuple_571.t1 = nameCtx_37;
    match_286 = tuple_571;
    goto end_match_1110;
next_1129:;
    if ((expr_20.tag != Bin_)) goto next_1130;
    struct Op_ op_3 = (*(expr_20.Bin_)).t0;
    struct AExpr_ l_44 = (*(expr_20.Bin_)).t1;
    struct AExpr_ r_56 = (*(expr_20.Bin_)).t2;
    struct IntIntTuple2 loc_117 = (*(expr_20.Bin_)).t3;
    struct HPrim_ call_830 = opToPrim_(op_3);
    struct HPrim_ prim_2 = call_830;
    struct AExpr_NameCtx_Tuple2 tuple_572;
    tuple_572.t0 = l_44;
    tuple_572.t1 = nameCtx_25;
    struct HExpr_NameCtx_Tuple2 call_831 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_572);
    struct HExpr_ l_45 = call_831.t0;
    struct NameCtx_ nameCtx_38 = call_831.t1;
    struct AExpr_NameCtx_Tuple2 tuple_573;
    tuple_573.t0 = r_56;
    tuple_573.t1 = nameCtx_38;
    struct HExpr_NameCtx_Tuple2 call_832 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_573);
    struct HExpr_ r_57 = call_832.t0;
    struct NameCtx_ nameCtx_39 = call_832.t1;
    struct HPrim_Ty_IntIntTuple2Tuple3 tuple_574;
    tuple_574.t0 = prim_2;
    tuple_574.t1 = noTy_;
    tuple_574.t2 = loc_117;
    struct HPrim_Ty_IntIntTuple2Tuple3* payload_181 = (struct HPrim_Ty_IntIntTuple2Tuple3*)malloc(sizeof(struct HPrim_Ty_IntIntTuple2Tuple3));
    (*(((struct HPrim_Ty_IntIntTuple2Tuple3*)payload_181))) = tuple_574;
    struct HExpr_ variant_181 = (struct HExpr_){.tag = Prim_, .Prim_ = payload_181};
    struct HExpr_ primExpr_ = variant_181;
    struct HExpr_ call_833 = hxApp_(primExpr_, l_45, noTy_, loc_117);
    struct HExpr_ call_834 = hxApp_(call_833, r_57, noTy_, loc_117);
    struct HExpr_NameCtx_Tuple2 tuple_575;
    tuple_575.t0 = call_834;
    tuple_575.t1 = nameCtx_39;
    match_286 = tuple_575;
    goto end_match_1110;
next_1130:;
    if ((expr_20.tag != Range_)) goto next_1131;
    struct IntIntTuple2 loc_118 = (*(expr_20.Range_)).t1;
    struct StringIntIntTuple2Tuple2 tuple_577;
    tuple_577.t0 = (struct String){.str = "Invalid use of range syntax.", .len = 28};
    tuple_577.t1 = loc_118;
    struct StringIntIntTuple2Tuple2* payload_182 = (struct StringIntIntTuple2Tuple2*)malloc(sizeof(struct StringIntIntTuple2Tuple2));
    (*(((struct StringIntIntTuple2Tuple2*)payload_182))) = tuple_577;
    struct HExpr_ variant_182 = (struct HExpr_){.tag = Error_2, .Error_2 = payload_182};
    struct HExpr_NameCtx_Tuple2 tuple_576;
    tuple_576.t0 = variant_182;
    tuple_576.t1 = nameCtx_25;
    match_286 = tuple_576;
    goto end_match_1110;
next_1131:;
    if ((expr_20.tag != TupleLit_1)) goto next_1132;
    struct AExpr_List* items_12 = (*(expr_20.TupleLit_1)).t0;
    struct IntIntTuple2 loc_119 = (*(expr_20.TupleLit_1)).t1;
    struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8 tuple_578;
    tuple_578.t0 = litFalse_;
    tuple_578.t1 = litTrue_;
    tuple_578.t2 = tyUnit_;
    tuple_578.t3 = tyStr_;
    tuple_578.t4 = tyChar_;
    tuple_578.t5 = tyInt_;
    tuple_578.t6 = tyBool_;
    tuple_578.t7 = noTy_;
    void* box_12 = (void*)malloc(sizeof(struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8));
    (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)box_12))) = tuple_578;
    void* env_57 = box_12;
    struct AExpr_NameCtx_Tuple2HExpr_NameCtx_Tuple2Fun1 fun_63 = (struct AExpr_NameCtx_Tuple2HExpr_NameCtx_Tuple2Fun1){.fun = fun_21, .env = env_57};
    struct AExpr_ListNameCtx_Tuple2 tuple_579;
    tuple_579.t0 = items_12;
    tuple_579.t1 = nameCtx_25;
    struct HExpr_ListNameCtx_Tuple2 call_835 = stMap_3(fun_63, tuple_579);
    struct HExpr_List* items_13 = call_835.t0;
    struct NameCtx_ nameCtx_40 = call_835.t1;
    struct HExpr_ call_836 = hxTuple_(tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, items_13, loc_119);
    struct HExpr_NameCtx_Tuple2 tuple_580;
    tuple_580.t0 = call_836;
    tuple_580.t1 = nameCtx_40;
    match_286 = tuple_580;
    goto end_match_1110;
next_1132:;
    if ((expr_20.tag != Anno_1)) goto next_1133;
    struct AExpr_ body_23 = (*(expr_20.Anno_1)).t0;
    struct ATy_ ty_58 = (*(expr_20.Anno_1)).t1;
    struct IntIntTuple2 loc_120 = (*(expr_20.Anno_1)).t2;
    struct AExpr_NameCtx_Tuple2 tuple_581;
    tuple_581.t0 = body_23;
    tuple_581.t1 = nameCtx_25;
    struct HExpr_NameCtx_Tuple2 call_837 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_581);
    struct HExpr_ body_24 = call_837.t0;
    struct NameCtx_ nameCtx_41 = call_837.t1;
    struct ATy_NameCtx_Tuple2 tuple_582;
    tuple_582.t0 = ty_58;
    tuple_582.t1 = nameCtx_41;
    struct Ty_NameCtx_Tuple2 call_838 = onTy_(tuple_582);
    struct Ty_ ty_59 = call_838.t0;
    struct NameCtx_ nameCtx_42 = call_838.t1;
    struct HExpr_ call_839 = hxAnno_(body_24, ty_59, loc_120);
    struct HExpr_NameCtx_Tuple2 tuple_583;
    tuple_583.t0 = call_839;
    tuple_583.t1 = nameCtx_42;
    match_286 = tuple_583;
    goto end_match_1110;
next_1133:;
    if ((expr_20.tag != Semi_1)) goto next_1134;
    struct AExpr_List* exprs_1 = (*(expr_20.Semi_1)).t0;
    struct IntIntTuple2 loc_121 = (*(expr_20.Semi_1)).t1;
    int call_840 = listIsEmpty_1(exprs_1);
    milone_assert((!(call_840)), 390, 4);
    int call_841 = 0;
    struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8 tuple_584;
    tuple_584.t0 = litFalse_;
    tuple_584.t1 = litTrue_;
    tuple_584.t2 = tyUnit_;
    tuple_584.t3 = tyStr_;
    tuple_584.t4 = tyChar_;
    tuple_584.t5 = tyInt_;
    tuple_584.t6 = tyBool_;
    tuple_584.t7 = noTy_;
    void* box_13 = (void*)malloc(sizeof(struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8));
    (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)box_13))) = tuple_584;
    void* env_58 = box_13;
    struct AExpr_NameCtx_Tuple2HExpr_NameCtx_Tuple2Fun1 fun_64 = (struct AExpr_NameCtx_Tuple2HExpr_NameCtx_Tuple2Fun1){.fun = fun_22, .env = env_58};
    struct AExpr_ListNameCtx_Tuple2 tuple_585;
    tuple_585.t0 = exprs_1;
    tuple_585.t1 = nameCtx_25;
    struct HExpr_ListNameCtx_Tuple2 call_842 = stMap_3(fun_64, tuple_585);
    struct HExpr_List* exprs_2 = call_842.t0;
    struct NameCtx_ nameCtx_43 = call_842.t1;
    struct HExpr_ call_843 = hxSemi_(noTy_, exprs_2, loc_121);
    struct HExpr_NameCtx_Tuple2 tuple_586;
    tuple_586.t0 = call_843;
    tuple_586.t1 = nameCtx_43;
    match_286 = tuple_586;
    goto end_match_1110;
next_1134:;
    if ((expr_20.tag != Let_1)) goto next_1135;
    struct APat_ pat_34 = (*(expr_20.Let_1)).t0;
    struct AExpr_ body_25 = (*(expr_20.Let_1)).t1;
    struct AExpr_ next_14 = (*(expr_20.Let_1)).t2;
    struct IntIntTuple2 loc_122 = (*(expr_20.Let_1)).t3;
    struct HExpr_NameCtx_Tuple2 match_288;
    struct ALet_ call_844 = desugarLet_(pat_34, body_25, next_14, loc_122);
    if ((call_844.tag != LetFun_)) goto next_1143;
    struct String ident_33 = (*(call_844.LetFun_)).t0;
    struct APat_List* args_9 = (*(call_844.LetFun_)).t1;
    struct AExpr_ body_26 = (*(call_844.LetFun_)).t2;
    struct AExpr_ next_15 = (*(call_844.LetFun_)).t3;
    struct IntIntTuple2 loc_123 = (*(call_844.LetFun_)).t4;
    struct IntNameCtx_Tuple2 call_845 = nameCtxAdd_(ident_33, nameCtx_25);
    int serial_14 = call_845.t0;
    struct NameCtx_ nameCtx_44 = call_845.t1;
    int isMainFun_1 = 0;
    struct Ty_Tuple1 tuple_587;
    tuple_587.t0 = noTy_;
    void* box_14 = (void*)malloc(sizeof(struct Ty_Tuple1));
    (*(((struct Ty_Tuple1*)box_14))) = tuple_587;
    void* env_59 = box_14;
    struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1 fun_65 = (struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1){.fun = fun_23, .env = env_59};
    struct APat_ListNameCtx_Tuple2 tuple_588;
    tuple_588.t0 = args_9;
    tuple_588.t1 = nameCtx_44;
    struct HPat_ListNameCtx_Tuple2 call_846 = stMap_2(fun_65, tuple_588);
    struct HPat_List* args_10 = call_846.t0;
    struct NameCtx_ nameCtx_45 = call_846.t1;
    struct AExpr_NameCtx_Tuple2 tuple_589;
    tuple_589.t0 = body_26;
    tuple_589.t1 = nameCtx_45;
    struct HExpr_NameCtx_Tuple2 call_847 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_589);
    struct HExpr_ body_27 = call_847.t0;
    struct NameCtx_ nameCtx_46 = call_847.t1;
    struct AExpr_NameCtx_Tuple2 tuple_590;
    tuple_590.t0 = next_15;
    tuple_590.t1 = nameCtx_46;
    struct HExpr_NameCtx_Tuple2 call_848 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_590);
    struct HExpr_ next_16 = call_848.t0;
    struct NameCtx_ nameCtx_47 = call_848.t1;
    struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7 tuple_592;
    tuple_592.t0 = serial_14;
    tuple_592.t1 = isMainFun_1;
    tuple_592.t2 = args_10;
    tuple_592.t3 = body_27;
    tuple_592.t4 = next_16;
    tuple_592.t5 = noTy_;
    tuple_592.t6 = loc_123;
    struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7* payload_183 = (struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7*)malloc(sizeof(struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7));
    (*(((struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7*)payload_183))) = tuple_592;
    struct HExpr_ variant_183 = (struct HExpr_){.tag = LetFun_1, .LetFun_1 = payload_183};
    struct HExpr_NameCtx_Tuple2 tuple_591;
    tuple_591.t0 = variant_183;
    tuple_591.t1 = nameCtx_47;
    match_288 = tuple_591;
    goto end_match_1142;
next_1143:;
    if ((call_844.tag != LetVal_)) goto next_1144;
    struct APat_ pat_35 = (*(call_844.LetVal_)).t0;
    struct AExpr_ body_28 = (*(call_844.LetVal_)).t1;
    struct AExpr_ next_17 = (*(call_844.LetVal_)).t2;
    struct IntIntTuple2 loc_124 = (*(call_844.LetVal_)).t3;
    struct APat_NameCtx_Tuple2 tuple_593;
    tuple_593.t0 = pat_35;
    tuple_593.t1 = nameCtx_25;
    struct HPat_NameCtx_Tuple2 call_849 = onPat_(noTy_, tuple_593);
    struct HPat_ pat_36 = call_849.t0;
    struct NameCtx_ nameCtx_48 = call_849.t1;
    struct AExpr_NameCtx_Tuple2 tuple_594;
    tuple_594.t0 = body_28;
    tuple_594.t1 = nameCtx_48;
    struct HExpr_NameCtx_Tuple2 call_850 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_594);
    struct HExpr_ body_29 = call_850.t0;
    struct NameCtx_ nameCtx_49 = call_850.t1;
    struct AExpr_NameCtx_Tuple2 tuple_595;
    tuple_595.t0 = next_17;
    tuple_595.t1 = nameCtx_49;
    struct HExpr_NameCtx_Tuple2 call_851 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_595);
    struct HExpr_ next_18 = call_851.t0;
    struct NameCtx_ nameCtx_50 = call_851.t1;
    struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5 tuple_597;
    tuple_597.t0 = pat_36;
    tuple_597.t1 = body_29;
    tuple_597.t2 = next_18;
    tuple_597.t3 = noTy_;
    tuple_597.t4 = loc_124;
    struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5* payload_184 = (struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5*)malloc(sizeof(struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5));
    (*(((struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5*)payload_184))) = tuple_597;
    struct HExpr_ variant_184 = (struct HExpr_){.tag = Let_2, .Let_2 = payload_184};
    struct HExpr_NameCtx_Tuple2 tuple_596;
    tuple_596.t0 = variant_184;
    tuple_596.t1 = nameCtx_50;
    match_288 = tuple_596;
    goto end_match_1142;
next_1144:;
    exit(1);
end_match_1142:;
    match_286 = match_288;
    goto end_match_1110;
next_1135:;
    if ((expr_20.tag != TySynonym_)) goto next_1136;
    struct String ident_34 = (*(expr_20.TySynonym_)).t0;
    struct ATy_ ty_60 = (*(expr_20.TySynonym_)).t1;
    struct IntIntTuple2 loc_125 = (*(expr_20.TySynonym_)).t2;
    struct IntNameCtx_Tuple2 call_852 = nameCtxAdd_(ident_34, nameCtx_25);
    int serial_15 = call_852.t0;
    struct NameCtx_ nameCtx_51 = call_852.t1;
    struct ATy_NameCtx_Tuple2 tuple_598;
    tuple_598.t0 = ty_60;
    tuple_598.t1 = nameCtx_51;
    struct Ty_NameCtx_Tuple2 call_853 = onTy_(tuple_598);
    struct Ty_ ty_61 = call_853.t0;
    struct NameCtx_ nameCtx_52 = call_853.t1;
    struct Ty_IntIntTuple2Tuple2 tuple_601;
    tuple_601.t0 = ty_61;
    tuple_601.t1 = loc_125;
    struct Ty_IntIntTuple2Tuple2* payload_185 = (struct Ty_IntIntTuple2Tuple2*)malloc(sizeof(struct Ty_IntIntTuple2Tuple2));
    (*(((struct Ty_IntIntTuple2Tuple2*)payload_185))) = tuple_601;
    struct TyDecl_ variant_185 = (struct TyDecl_){.tag = Synonym_1, .Synonym_1 = payload_185};
    struct IntTyDecl_IntIntTuple2Tuple3 tuple_600;
    tuple_600.t0 = serial_15;
    tuple_600.t1 = variant_185;
    tuple_600.t2 = loc_125;
    struct IntTyDecl_IntIntTuple2Tuple3* payload_186 = (struct IntTyDecl_IntIntTuple2Tuple3*)malloc(sizeof(struct IntTyDecl_IntIntTuple2Tuple3));
    (*(((struct IntTyDecl_IntIntTuple2Tuple3*)payload_186))) = tuple_600;
    struct HExpr_ variant_186 = (struct HExpr_){.tag = TyDecl_, .TyDecl_ = payload_186};
    struct HExpr_NameCtx_Tuple2 tuple_599;
    tuple_599.t0 = variant_186;
    tuple_599.t1 = nameCtx_52;
    match_286 = tuple_599;
    goto end_match_1110;
next_1136:;
    if ((expr_20.tag != TyUnion_)) goto next_1137;
    struct String ident_35 = (*(expr_20.TyUnion_)).t0;
    struct AVariant_List* variants_3 = (*(expr_20.TyUnion_)).t1;
    struct IntIntTuple2 loc_126 = (*(expr_20.TyUnion_)).t2;
    struct IntNameCtx_Tuple2 call_854 = nameCtxAdd_(ident_35, nameCtx_25);
    int unionSerial_ = call_854.t0;
    struct NameCtx_ nameCtx_57 = call_854.t1;
    struct Ty_Tuple1 tuple_602;
    tuple_602.t0 = tyUnit_;
    void* box_15 = (void*)malloc(sizeof(struct Ty_Tuple1));
    (*(((struct Ty_Tuple1*)box_15))) = tuple_602;
    void* env_60 = box_15;
    struct AVariant_NameCtx_Tuple2StringIntBoolTy_Tuple4NameCtx_Tuple2Fun1 fun_66 = (struct AVariant_NameCtx_Tuple2StringIntBoolTy_Tuple4NameCtx_Tuple2Fun1){.fun = fun_24, .env = env_60};
    struct AVariant_ListNameCtx_Tuple2 tuple_603;
    tuple_603.t0 = variants_3;
    tuple_603.t1 = nameCtx_57;
    struct StringIntBoolTy_Tuple4ListNameCtx_Tuple2 call_855 = stMap_1(fun_66, tuple_603);
    struct StringIntBoolTy_Tuple4List* variants_4 = call_855.t0;
    struct NameCtx_ nameCtx_58 = call_855.t1;
    struct StringStringIntBoolTy_Tuple4ListIntIntTuple2Tuple3 tuple_606;
    tuple_606.t0 = ident_35;
    tuple_606.t1 = variants_4;
    tuple_606.t2 = loc_126;
    struct StringStringIntBoolTy_Tuple4ListIntIntTuple2Tuple3* payload_187 = (struct StringStringIntBoolTy_Tuple4ListIntIntTuple2Tuple3*)malloc(sizeof(struct StringStringIntBoolTy_Tuple4ListIntIntTuple2Tuple3));
    (*(((struct StringStringIntBoolTy_Tuple4ListIntIntTuple2Tuple3*)payload_187))) = tuple_606;
    struct TyDecl_ variant_187 = (struct TyDecl_){.tag = Union_1, .Union_1 = payload_187};
    struct IntTyDecl_IntIntTuple2Tuple3 tuple_605;
    tuple_605.t0 = unionSerial_;
    tuple_605.t1 = variant_187;
    tuple_605.t2 = loc_126;
    struct IntTyDecl_IntIntTuple2Tuple3* payload_188 = (struct IntTyDecl_IntIntTuple2Tuple3*)malloc(sizeof(struct IntTyDecl_IntIntTuple2Tuple3));
    (*(((struct IntTyDecl_IntIntTuple2Tuple3*)payload_188))) = tuple_605;
    struct HExpr_ variant_188 = (struct HExpr_){.tag = TyDecl_, .TyDecl_ = payload_188};
    struct HExpr_NameCtx_Tuple2 tuple_604;
    tuple_604.t0 = variant_188;
    tuple_604.t1 = nameCtx_58;
    match_286 = tuple_604;
    goto end_match_1110;
next_1137:;
    if ((expr_20.tag != Open_1)) goto next_1138;
    struct StringList* path_4 = (*(expr_20.Open_1)).t0;
    struct IntIntTuple2 loc_127 = (*(expr_20.Open_1)).t1;
    struct StringListIntIntTuple2Tuple2 tuple_608;
    tuple_608.t0 = path_4;
    tuple_608.t1 = loc_127;
    struct StringListIntIntTuple2Tuple2* payload_189 = (struct StringListIntIntTuple2Tuple2*)malloc(sizeof(struct StringListIntIntTuple2Tuple2));
    (*(((struct StringListIntIntTuple2Tuple2*)payload_189))) = tuple_608;
    struct HExpr_ variant_189 = (struct HExpr_){.tag = Open_2, .Open_2 = payload_189};
    struct HExpr_NameCtx_Tuple2 tuple_607;
    tuple_607.t0 = variant_189;
    tuple_607.t1 = nameCtx_25;
    match_286 = tuple_607;
    goto end_match_1110;
next_1138:;
    exit(1);
end_match_1110:;
    return match_286;
}

struct HExpr_NameCtx_Tuple2 astToHir_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, struct AExpr_NameCtx_Tuple2 arg_224) {
    struct AExpr_ expr_33 = arg_224.t0;
    struct NameCtx_ nameCtx_59 = arg_224.t1;
    struct AExpr_NameCtx_Tuple2 tuple_609;
    tuple_609.t0 = expr_33;
    tuple_609.t1 = nameCtx_59;
    struct HExpr_NameCtx_Tuple2 call_856 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_609);
    return call_856;
}

struct StringListList* fun_25(void* env_19, struct HExpr_ arg_74) {
    struct StringListList* call_857 = go_55(arg_74);
    return call_857;
}

struct StringListList* go_55(struct HExpr_ expr_35) {
    struct StringListList* match_289;
    if ((expr_35.tag != Open_2)) goto next_1146;
    struct StringList* path_5 = (*(expr_35.Open_2)).t0;
    struct StringListList* list_88 = (struct StringListList*)malloc(sizeof(struct StringListList));
    list_88->head = path_5;
    list_88->tail = NULL;
    match_289 = list_88;
    goto end_match_1145;
next_1146:;
    if ((expr_35.tag != Inf_)) goto next_1147;
    if (((*(expr_35.Inf_)).t0.tag != Semi_2)) goto next_1147;
    struct HExpr_List* exprs_3 = (*(expr_35.Inf_)).t1;
    void* box_16 = (void*)malloc(sizeof(int));
    (*(((int*)box_16))) = 0;
    void* env_61 = box_16;
    struct HExpr_StringListListFun1 fun_67 = (struct HExpr_StringListListFun1){.fun = fun_25, .env = env_61};
    struct StringListList* call_858 = listCollect_1(fun_67, exprs_3);
    match_289 = call_858;
    goto end_match_1145;
next_1147:;
    match_289 = NULL;
    goto end_match_1145;
next_1148:;
end_match_1145:;
    return match_289;
}

struct StringListList* findOpenPaths_(struct HExpr_ expr_34) {
    struct StringListList* call_859 = go_55(expr_34);
    return call_859;
}

struct StringList* extractor_(struct String projectName_1, struct StringList* path_6) {
    struct StringList* match_290;
    if ((!(path_6))) goto next_1150;
    struct String prefix_1 = path_6->head;
    if ((!(path_6->tail))) goto next_1150;
    struct String moduleName_1 = path_6->tail->head;
    if ((str_cmp(prefix_1, projectName_1) != 0)) goto next_1150;
    struct StringList* some_3 = (struct StringList*)malloc(sizeof(struct StringList));
    some_3->head = moduleName_1;
    some_3->tail = NULL;
    match_290 = some_3;
    goto end_match_1149;
next_1150:;
    match_290 = NULL;
    goto end_match_1149;
next_1151:;
end_match_1149:;
    return match_290;
}

struct StringTuple1 {
    struct String t0;
};

struct StringList* fun_26(void* env_20, struct StringList* arg_75) {
    struct String arg_76 = (*(((struct StringTuple1*)env_20))).t0;
    struct StringList* call_860 = extractor_(arg_76, arg_75);
    return call_860;
}

struct StringList* findOpenModules_(struct String projectName_1, struct HExpr_ expr_36) {
    struct StringTuple1 tuple_610;
    tuple_610.t0 = projectName_1;
    void* box_17 = (void*)malloc(sizeof(struct StringTuple1));
    (*(((struct StringTuple1*)box_17))) = tuple_610;
    void* env_62 = box_17;
    struct StringListStringListFun1 fun_68 = (struct StringListStringListFun1){.fun = fun_26, .env = env_62};
    struct StringListList* call_861 = findOpenPaths_(expr_36);
    struct StringList* call_862 = listChoose_1(fun_68, call_861);
    return call_862;
}

struct HExpr_List* goLast_(struct HExpr_ secondExpr_, struct Ty_ noTy_, struct IntIntTuple2 noLoc_, struct HExpr_List* exprs_5) {
    struct HExpr_List* match_291;
    if ((!((!(exprs_5))))) goto next_1153;
    struct HExpr_List* list_89 = (struct HExpr_List*)malloc(sizeof(struct HExpr_List));
    list_89->head = secondExpr_;
    list_89->tail = NULL;
    match_291 = list_89;
    goto end_match_1152;
next_1153:;
    if ((!(exprs_5))) goto next_1154;
    struct HExpr_ lastExpr_ = exprs_5->head;
    if ((!((!(exprs_5->tail))))) goto next_1154;
    struct HExpr_ call_863 = go_56(secondExpr_, noTy_, noLoc_, lastExpr_);
    struct HExpr_List* list_90 = (struct HExpr_List*)malloc(sizeof(struct HExpr_List));
    list_90->head = call_863;
    list_90->tail = NULL;
    match_291 = list_90;
    goto end_match_1152;
next_1154:;
    if ((!(exprs_5))) goto next_1155;
    struct HExpr_ x_34 = exprs_5->head;
    struct HExpr_List* xs_64 = exprs_5->tail;
    struct HExpr_List* call_864 = goLast_(secondExpr_, noTy_, noLoc_, xs_64);
    struct HExpr_List* list_91 = (struct HExpr_List*)malloc(sizeof(struct HExpr_List));
    list_91->head = x_34;
    list_91->tail = call_864;
    match_291 = list_91;
    goto end_match_1152;
next_1155:;
    exit(1);
end_match_1152:;
    return match_291;
}

struct HExpr_ go_56(struct HExpr_ secondExpr_, struct Ty_ noTy_, struct IntIntTuple2 noLoc_, struct HExpr_ expr_37) {
    struct HExpr_ match_292;
    if ((expr_37.tag != Let_2)) goto next_1157;
    struct HPat_ pat_37 = (*(expr_37.Let_2)).t0;
    struct HExpr_ init_1 = (*(expr_37.Let_2)).t1;
    struct HExpr_ next_19 = (*(expr_37.Let_2)).t2;
    struct Ty_ ty_64 = (*(expr_37.Let_2)).t3;
    struct IntIntTuple2 loc_128 = (*(expr_37.Let_2)).t4;
    struct HExpr_ call_865 = go_56(secondExpr_, noTy_, noLoc_, next_19);
    struct HExpr_ next_20 = call_865;
    struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5 tuple_611;
    tuple_611.t0 = pat_37;
    tuple_611.t1 = init_1;
    tuple_611.t2 = next_20;
    tuple_611.t3 = ty_64;
    tuple_611.t4 = loc_128;
    struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5* payload_190 = (struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5*)malloc(sizeof(struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5));
    (*(((struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5*)payload_190))) = tuple_611;
    struct HExpr_ variant_190 = (struct HExpr_){.tag = Let_2, .Let_2 = payload_190};
    match_292 = variant_190;
    goto end_match_1156;
next_1157:;
    if ((expr_37.tag != LetFun_1)) goto next_1158;
    int serial_17 = (*(expr_37.LetFun_1)).t0;
    int isMainFun_2 = (*(expr_37.LetFun_1)).t1;
    struct HPat_List* args_11 = (*(expr_37.LetFun_1)).t2;
    struct HExpr_ body_30 = (*(expr_37.LetFun_1)).t3;
    struct HExpr_ next_21 = (*(expr_37.LetFun_1)).t4;
    struct Ty_ ty_65 = (*(expr_37.LetFun_1)).t5;
    struct IntIntTuple2 loc_129 = (*(expr_37.LetFun_1)).t6;
    struct HExpr_ call_866 = go_56(secondExpr_, noTy_, noLoc_, next_21);
    struct HExpr_ next_22 = call_866;
    struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7 tuple_612;
    tuple_612.t0 = serial_17;
    tuple_612.t1 = isMainFun_2;
    tuple_612.t2 = args_11;
    tuple_612.t3 = body_30;
    tuple_612.t4 = next_22;
    tuple_612.t5 = ty_65;
    tuple_612.t6 = loc_129;
    struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7* payload_191 = (struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7*)malloc(sizeof(struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7));
    (*(((struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7*)payload_191))) = tuple_612;
    struct HExpr_ variant_191 = (struct HExpr_){.tag = LetFun_1, .LetFun_1 = payload_191};
    match_292 = variant_191;
    goto end_match_1156;
next_1158:;
    if ((expr_37.tag != Inf_)) goto next_1159;
    if (((*(expr_37.Inf_)).t0.tag != Semi_2)) goto next_1159;
    struct HExpr_List* exprs_4 = (*(expr_37.Inf_)).t1;
    struct Ty_ ty_66 = (*(expr_37.Inf_)).t2;
    struct IntIntTuple2 loc_130 = (*(expr_37.Inf_)).t3;
    struct HExpr_List* call_867 = goLast_(secondExpr_, noTy_, noLoc_, exprs_4);
    struct HExpr_List* exprs_6 = call_867;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4 tuple_613;
    tuple_613.t0 = (struct InfOp_){.tag = Semi_2};
    tuple_613.t1 = exprs_6;
    tuple_613.t2 = ty_66;
    tuple_613.t3 = loc_130;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4* payload_192 = (struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4));
    (*(((struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)payload_192))) = tuple_613;
    struct HExpr_ variant_192 = (struct HExpr_){.tag = Inf_, .Inf_ = payload_192};
    match_292 = variant_192;
    goto end_match_1156;
next_1159:;
    struct HExpr_List* list_93 = (struct HExpr_List*)malloc(sizeof(struct HExpr_List));
    list_93->head = secondExpr_;
    list_93->tail = NULL;
    struct HExpr_List* list_92 = (struct HExpr_List*)malloc(sizeof(struct HExpr_List));
    list_92->head = expr_37;
    list_92->tail = list_93;
    struct HExpr_ call_868 = hxSemi_(noTy_, list_92, noLoc_);
    match_292 = call_868;
    goto end_match_1156;
next_1160:;
end_match_1156:;
    return match_292;
}

struct HExpr_ spliceExpr_(struct Ty_ noTy_, struct IntIntTuple2 noLoc_, struct HExpr_ firstExpr_, struct HExpr_ secondExpr_) {
    struct HExpr_ call_869 = go_56(secondExpr_, noTy_, noLoc_, firstExpr_);
    return call_869;
}

struct StringStringFun1 {
    struct String(*fun)(void*, struct String);
    void* env;
};

struct StringStringStringFun1Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_CharTuple11 {
    struct String t0;
    struct StringStringFun1 t1;
    struct Lit_ t2;
    struct Lit_ t3;
    struct Ty_ t4;
    struct Ty_ t5;
    struct Ty_ t6;
    struct Ty_ t7;
    struct Ty_ t8;
    struct Ty_ t9;
    char t10;
};

struct HExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4 fun_27(void* env_21, struct HExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4 arg_77, struct String arg_78) {
    struct String arg_79 = (*(((struct StringStringStringFun1Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_CharTuple11*)env_21))).t0;
    struct StringStringFun1 arg_80 = (*(((struct StringStringStringFun1Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_CharTuple11*)env_21))).t1;
    struct Lit_ arg_81 = (*(((struct StringStringStringFun1Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_CharTuple11*)env_21))).t2;
    struct Lit_ arg_82 = (*(((struct StringStringStringFun1Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_CharTuple11*)env_21))).t3;
    struct Ty_ arg_83 = (*(((struct StringStringStringFun1Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_CharTuple11*)env_21))).t4;
    struct Ty_ arg_84 = (*(((struct StringStringStringFun1Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_CharTuple11*)env_21))).t5;
    struct Ty_ arg_85 = (*(((struct StringStringStringFun1Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_CharTuple11*)env_21))).t6;
    struct Ty_ arg_86 = (*(((struct StringStringStringFun1Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_CharTuple11*)env_21))).t7;
    struct Ty_ arg_87 = (*(((struct StringStringStringFun1Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_CharTuple11*)env_21))).t8;
    struct Ty_ arg_88 = (*(((struct StringStringStringFun1Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_CharTuple11*)env_21))).t9;
    char arg_89 = (*(((struct StringStringStringFun1Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_CharTuple11*)env_21))).t10;
    struct HExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4 call_870 = go_57(arg_79, arg_80, arg_81, arg_82, arg_83, arg_84, arg_85, arg_86, arg_87, arg_88, arg_89, arg_77, arg_78);
    return call_870;
}

struct HExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4 go_57(struct String projectName_2, struct StringStringFun1 readModuleFile_1, struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, char charNull_, struct HExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4 arg_225, struct String moduleName_2) {
    struct HExpr_List* moduleAcc_ = arg_225.t0;
    struct StringHExpr_Tuple2ListStringStringIntFun2Tuple2 moduleMap_ = arg_225.t1;
    struct NameCtx_ nameCtx_61 = arg_225.t2;
    struct StringIntIntTuple2Tuple2ListList* errorAcc_ = arg_225.t3;
    struct HExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4 match_293;
    int call_871 = mapContainsKey_1(moduleName_2, moduleMap_);
    if ((!(call_871))) goto next_1162;
    struct HExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4 tuple_614;
    tuple_614.t0 = moduleAcc_;
    tuple_614.t1 = moduleMap_;
    tuple_614.t2 = nameCtx_61;
    tuple_614.t3 = errorAcc_;
    match_293 = tuple_614;
    goto end_match_1161;
next_1162:;
    if (call_871) goto next_1163;
    struct String app_75 = readModuleFile_1.fun(readModuleFile_1.env, moduleName_2);
    struct String source_ = app_75;
    struct Token_IntIntTuple2Tuple2List* call_872 = tokenize_(charNull_, source_);
    struct Token_IntIntTuple2Tuple2List* tokens_252 = call_872;
    struct AExpr_StringIntIntTuple2Tuple2ListTuple2 call_873 = parse_(tokens_252);
    struct AExpr_ moduleAst_ = call_873.t0;
    struct StringIntIntTuple2Tuple2List* errors_162 = call_873.t1;
    struct AExpr_NameCtx_Tuple2 tuple_615;
    tuple_615.t0 = moduleAst_;
    tuple_615.t1 = nameCtx_61;
    struct HExpr_NameCtx_Tuple2 call_874 = astToHir_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_615);
    struct HExpr_ moduleHir_ = call_874.t0;
    struct NameCtx_ nameCtx_62 = call_874.t1;
    struct StringList* call_875 = findOpenModules_(projectName_2, moduleHir_);
    struct StringList* dependencies_ = call_875;
    struct StringHExpr_Tuple2ListStringStringIntFun2Tuple2 call_876 = mapAdd_1(moduleName_2, moduleHir_, moduleMap_);
    struct StringHExpr_Tuple2ListStringStringIntFun2Tuple2 moduleMap_1 = call_876;
    struct StringStringStringFun1Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_CharTuple11 tuple_616;
    tuple_616.t0 = projectName_2;
    tuple_616.t1 = readModuleFile_1;
    tuple_616.t2 = litFalse_;
    tuple_616.t3 = litTrue_;
    tuple_616.t4 = tyUnit_;
    tuple_616.t5 = tyStr_;
    tuple_616.t6 = tyChar_;
    tuple_616.t7 = tyInt_;
    tuple_616.t8 = tyBool_;
    tuple_616.t9 = noTy_;
    tuple_616.t10 = charNull_;
    void* box_18 = (void*)malloc(sizeof(struct StringStringStringFun1Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_CharTuple11));
    (*(((struct StringStringStringFun1Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_CharTuple11*)box_18))) = tuple_616;
    void* env_63 = box_18;
    struct HExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4StringHExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4Fun2 fun_69 = (struct HExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4StringHExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4Fun2){.fun = fun_27, .env = env_63};
    struct HExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4 tuple_617;
    tuple_617.t0 = moduleAcc_;
    tuple_617.t1 = moduleMap_1;
    tuple_617.t2 = nameCtx_62;
    tuple_617.t3 = errorAcc_;
    struct HExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4 call_877 = listFold_1(fun_69, tuple_617, dependencies_);
    struct HExpr_List* moduleAcc_1 = call_877.t0;
    struct StringHExpr_Tuple2ListStringStringIntFun2Tuple2 moduleMap_2 = call_877.t1;
    struct NameCtx_ nameCtx_63 = call_877.t2;
    struct StringIntIntTuple2Tuple2ListList* errorAcc_1 = call_877.t3;
    struct HExpr_List* list_94 = (struct HExpr_List*)malloc(sizeof(struct HExpr_List));
    list_94->head = moduleHir_;
    list_94->tail = moduleAcc_1;
    struct StringIntIntTuple2Tuple2ListList* list_95 = (struct StringIntIntTuple2Tuple2ListList*)malloc(sizeof(struct StringIntIntTuple2Tuple2ListList));
    list_95->head = errors_162;
    list_95->tail = errorAcc_1;
    struct HExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4 tuple_618;
    tuple_618.t0 = list_94;
    tuple_618.t1 = moduleMap_2;
    tuple_618.t2 = nameCtx_63;
    tuple_618.t3 = list_95;
    match_293 = tuple_618;
    goto end_match_1161;
next_1163:;
    exit(1);
end_match_1161:;
    return match_293;
}

int fun_28(void* env_22, struct String arg_90, struct String arg_91) {
    int call_878 = strCmp_(arg_90, arg_91);
    return call_878;
}

struct HExpr_ fun_29(void* env_23, struct HExpr_ arg_92, struct HExpr_ arg_93) {
    struct Ty_ arg_94 = (*(((struct Ty_IntIntTuple2Tuple2*)env_23))).t0;
    struct IntIntTuple2 arg_95 = (*(((struct Ty_IntIntTuple2Tuple2*)env_23))).t1;
    struct HExpr_ call_879 = spliceExpr_(arg_94, arg_95, arg_92, arg_93);
    return call_879;
}

struct HExpr_NameCtx_StringIntIntTuple2Tuple2ListListTuple3 {
    struct HExpr_ t0;
    struct NameCtx_ t1;
    struct StringIntIntTuple2Tuple2ListList* t2;
};

struct HExpr_NameCtx_StringIntIntTuple2Tuple2ListListTuple3 parseProjectModules_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, struct IntIntTuple2 noLoc_, char charNull_, struct StringStringFun1 readModuleFile_1, struct String projectName_2, struct NameCtx_ nameCtx_60) {
    void* box_19 = (void*)malloc(sizeof(int));
    (*(((int*)box_19))) = 0;
    void* env_64 = box_19;
    struct StringStringIntFun2 fun_70 = (struct StringStringIntFun2){.fun = fun_28, .env = env_64};
    struct StringHExpr_Tuple2ListStringStringIntFun2Tuple2 call_880 = mapEmpty_1(fun_70);
    struct HExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4 tuple_619;
    tuple_619.t0 = NULL;
    tuple_619.t1 = call_880;
    tuple_619.t2 = nameCtx_60;
    tuple_619.t3 = NULL;
    struct HExpr_ListStringHExpr_Tuple2ListStringStringIntFun2Tuple2NameCtx_StringIntIntTuple2Tuple2ListListTuple4 call_881 = go_57(projectName_2, readModuleFile_1, litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, charNull_, tuple_619, projectName_2);
    struct HExpr_List* moduleAcc_2 = call_881.t0;
    struct NameCtx_ nameCtx_64 = call_881.t2;
    struct StringIntIntTuple2Tuple2ListList* errorAcc_2 = call_881.t3;
    struct HExpr_List* call_882 = listRev_1(moduleAcc_2);
    struct HExpr_List* modules_ = call_882;
    struct Ty_IntIntTuple2Tuple2 tuple_621;
    tuple_621.t0 = noTy_;
    tuple_621.t1 = noLoc_;
    void* box_20 = (void*)malloc(sizeof(struct Ty_IntIntTuple2Tuple2));
    (*(((struct Ty_IntIntTuple2Tuple2*)box_20))) = tuple_621;
    void* env_65 = box_20;
    struct HExpr_HExpr_HExpr_Fun2 fun_71 = (struct HExpr_HExpr_HExpr_Fun2){.fun = fun_29, .env = env_65};
    struct HExpr_ call_883 = listReduce_1(fun_71, modules_);
    struct HExpr_NameCtx_StringIntIntTuple2Tuple2ListListTuple3 tuple_620;
    tuple_620.t0 = call_883;
    tuple_620.t1 = nameCtx_64;
    tuple_620.t2 = errorAcc_2;
    return tuple_620;
}

struct String litToString_(struct Lit_ lit_5) {
    struct String match_294;
    if ((lit_5.tag != Bool_)) goto next_1165;
    if ((!((*(lit_5.Bool_))))) goto next_1165;
    match_294 = (struct String){.str = "true", .len = 4};
    goto end_match_1164;
next_1165:;
    if ((lit_5.tag != Bool_)) goto next_1166;
    if ((*(lit_5.Bool_))) goto next_1166;
    match_294 = (struct String){.str = "false", .len = 5};
    goto end_match_1164;
next_1166:;
    if ((lit_5.tag != Int_)) goto next_1167;
    int value_6 = (*(lit_5.Int_));
    struct String call_884 = str_of_int(value_6);
    match_294 = call_884;
    goto end_match_1164;
next_1167:;
    if ((lit_5.tag != Char_)) goto next_1168;
    char value_7 = (*(lit_5.Char_));
    struct String match_295;
    int call_885 = charNeedsEscaping_(value_7);
    if ((!(call_885))) goto next_1171;
    struct String call_886 = charEscape_(value_7);
    match_295 = call_886;
    goto end_match_1170;
next_1171:;
    if (call_885) goto next_1172;
    struct String call_887 = str_of_char(value_7);
    match_295 = call_887;
    goto end_match_1170;
next_1172:;
    exit(1);
end_match_1170:;
    match_294 = str_add(str_add((struct String){.str = "\'", .len = 1}, match_295), (struct String){.str = "\'", .len = 1});
    goto end_match_1164;
next_1168:;
    if ((lit_5.tag != Str_)) goto next_1169;
    struct String value_8 = (*(lit_5.Str_));
    struct String call_888 = strEscape_(value_8);
    match_294 = str_add(str_add((struct String){.str = "\"", .len = 1}, call_888), (struct String){.str = "\"", .len = 1});
    goto end_match_1164;
next_1169:;
    exit(1);
end_match_1164:;
    return match_294;
}

struct String tokenToString_(struct Token_ token_12) {
    struct String match_296;
    if ((token_12.tag != Error_)) goto next_1174;
    match_296 = (struct String){.str = "Error", .len = 5};
    goto end_match_1173;
next_1174:;
    if ((token_12.tag != Bool_1)) goto next_1175;
    if ((*(token_12.Bool_1))) goto next_1175;
    match_296 = (struct String){.str = "false", .len = 5};
    goto end_match_1173;
next_1175:;
    if ((token_12.tag != Bool_1)) goto next_1176;
    if ((!((*(token_12.Bool_1))))) goto next_1176;
    match_296 = (struct String){.str = "true", .len = 4};
    goto end_match_1173;
next_1176:;
    if ((token_12.tag != Int_1)) goto next_1177;
    int value_9 = (*(token_12.Int_1));
    struct String call_889 = str_of_int(value_9);
    match_296 = call_889;
    goto end_match_1173;
next_1177:;
    if ((token_12.tag != Char_1)) goto next_1178;
    char value_10 = (*(token_12.Char_1));
    char* payload_193 = (char*)malloc(sizeof(char));
    (*(((char*)payload_193))) = value_10;
    struct Lit_ variant_193 = (struct Lit_){.tag = Char_, .Char_ = payload_193};
    struct String call_890 = litToString_(variant_193);
    match_296 = call_890;
    goto end_match_1173;
next_1178:;
    if ((token_12.tag != Str_1)) goto next_1179;
    struct String value_11 = (*(token_12.Str_1));
    struct String* payload_194 = (struct String*)malloc(sizeof(struct String));
    (*(((struct String*)payload_194))) = value_11;
    struct Lit_ variant_194 = (struct Lit_){.tag = Str_, .Str_ = payload_194};
    struct String call_891 = litToString_(variant_194);
    match_296 = call_891;
    goto end_match_1173;
next_1179:;
    if ((token_12.tag != Ident_)) goto next_1180;
    struct String ident_8 = (*(token_12.Ident_));
    match_296 = ident_8;
    goto end_match_1173;
next_1180:;
    if ((token_12.tag != ParenL_)) goto next_1181;
    match_296 = (struct String){.str = "(", .len = 1};
    goto end_match_1173;
next_1181:;
    if ((token_12.tag != ParenR_)) goto next_1182;
    match_296 = (struct String){.str = ")", .len = 1};
    goto end_match_1173;
next_1182:;
    if ((token_12.tag != BracketL_)) goto next_1183;
    match_296 = (struct String){.str = "[", .len = 1};
    goto end_match_1173;
next_1183:;
    if ((token_12.tag != BracketR_)) goto next_1184;
    match_296 = (struct String){.str = "]", .len = 1};
    goto end_match_1173;
next_1184:;
    if ((token_12.tag != Amp_)) goto next_1185;
    match_296 = (struct String){.str = "&", .len = 1};
    goto end_match_1173;
next_1185:;
    if ((token_12.tag != AmpAmp_)) goto next_1186;
    match_296 = (struct String){.str = "&&", .len = 2};
    goto end_match_1173;
next_1186:;
    if ((token_12.tag != Arrow_)) goto next_1187;
    match_296 = (struct String){.str = "->", .len = 2};
    goto end_match_1173;
next_1187:;
    if ((token_12.tag != Colon_)) goto next_1188;
    match_296 = (struct String){.str = ":", .len = 1};
    goto end_match_1173;
next_1188:;
    if ((token_12.tag != ColonColon_)) goto next_1189;
    match_296 = (struct String){.str = "::", .len = 2};
    goto end_match_1173;
next_1189:;
    if ((token_12.tag != Comma_)) goto next_1190;
    match_296 = (struct String){.str = ",", .len = 1};
    goto end_match_1173;
next_1190:;
    if ((token_12.tag != Dot_)) goto next_1191;
    match_296 = (struct String){.str = ".", .len = 1};
    goto end_match_1173;
next_1191:;
    if ((token_12.tag != DotDot_)) goto next_1192;
    match_296 = (struct String){.str = "..", .len = 2};
    goto end_match_1173;
next_1192:;
    if ((token_12.tag != Eq_)) goto next_1193;
    match_296 = (struct String){.str = "=", .len = 1};
    goto end_match_1173;
next_1193:;
    if ((token_12.tag != Gt_)) goto next_1194;
    match_296 = (struct String){.str = ">", .len = 1};
    goto end_match_1173;
next_1194:;
    if ((token_12.tag != GtEq_)) goto next_1195;
    match_296 = (struct String){.str = ">=", .len = 2};
    goto end_match_1173;
next_1195:;
    if ((token_12.tag != Lt_)) goto next_1196;
    match_296 = (struct String){.str = "<", .len = 1};
    goto end_match_1173;
next_1196:;
    if ((token_12.tag != LtEq_)) goto next_1197;
    match_296 = (struct String){.str = "<=", .len = 2};
    goto end_match_1173;
next_1197:;
    if ((token_12.tag != LtGt_)) goto next_1198;
    match_296 = (struct String){.str = "<>", .len = 2};
    goto end_match_1173;
next_1198:;
    if ((token_12.tag != Minus_)) goto next_1199;
    match_296 = (struct String){.str = "-", .len = 1};
    goto end_match_1173;
next_1199:;
    if ((token_12.tag != Percent_)) goto next_1200;
    match_296 = (struct String){.str = "%", .len = 1};
    goto end_match_1173;
next_1200:;
    if ((token_12.tag != Pipe_)) goto next_1201;
    match_296 = (struct String){.str = "|", .len = 1};
    goto end_match_1173;
next_1201:;
    if ((token_12.tag != PipeGt_)) goto next_1202;
    match_296 = (struct String){.str = "|>", .len = 2};
    goto end_match_1173;
next_1202:;
    if ((token_12.tag != PipePipe_)) goto next_1203;
    match_296 = (struct String){.str = "||", .len = 2};
    goto end_match_1173;
next_1203:;
    if ((token_12.tag != Plus_)) goto next_1204;
    match_296 = (struct String){.str = "+", .len = 1};
    goto end_match_1173;
next_1204:;
    if ((token_12.tag != Semi_)) goto next_1205;
    match_296 = (struct String){.str = ";", .len = 1};
    goto end_match_1173;
next_1205:;
    if ((token_12.tag != Star_)) goto next_1206;
    match_296 = (struct String){.str = "*", .len = 1};
    goto end_match_1173;
next_1206:;
    if ((token_12.tag != Slash_)) goto next_1207;
    match_296 = (struct String){.str = "/", .len = 1};
    goto end_match_1173;
next_1207:;
    if ((token_12.tag != As_)) goto next_1208;
    match_296 = (struct String){.str = "as", .len = 2};
    goto end_match_1173;
next_1208:;
    if ((token_12.tag != Do_)) goto next_1209;
    match_296 = (struct String){.str = "do", .len = 2};
    goto end_match_1173;
next_1209:;
    if ((token_12.tag != Else_)) goto next_1210;
    match_296 = (struct String){.str = "else", .len = 4};
    goto end_match_1173;
next_1210:;
    if ((token_12.tag != Fun_)) goto next_1211;
    match_296 = (struct String){.str = "fun", .len = 3};
    goto end_match_1173;
next_1211:;
    if ((token_12.tag != If_)) goto next_1212;
    match_296 = (struct String){.str = "if", .len = 2};
    goto end_match_1173;
next_1212:;
    if ((token_12.tag != In_)) goto next_1213;
    match_296 = (struct String){.str = "in", .len = 2};
    goto end_match_1173;
next_1213:;
    if ((token_12.tag != Internal_)) goto next_1214;
    match_296 = (struct String){.str = "internal", .len = 8};
    goto end_match_1173;
next_1214:;
    if ((token_12.tag != Let_)) goto next_1215;
    match_296 = (struct String){.str = "let", .len = 3};
    goto end_match_1173;
next_1215:;
    if ((token_12.tag != Match_)) goto next_1216;
    match_296 = (struct String){.str = "match", .len = 5};
    goto end_match_1173;
next_1216:;
    if ((token_12.tag != Module_)) goto next_1217;
    match_296 = (struct String){.str = "module", .len = 6};
    goto end_match_1173;
next_1217:;
    if ((token_12.tag != Namespace_)) goto next_1218;
    match_296 = (struct String){.str = "namespace", .len = 9};
    goto end_match_1173;
next_1218:;
    if ((token_12.tag != Of_)) goto next_1219;
    match_296 = (struct String){.str = "of", .len = 2};
    goto end_match_1173;
next_1219:;
    if ((token_12.tag != Open_)) goto next_1220;
    match_296 = (struct String){.str = "open", .len = 4};
    goto end_match_1173;
next_1220:;
    if ((token_12.tag != Private_)) goto next_1221;
    match_296 = (struct String){.str = "private", .len = 7};
    goto end_match_1173;
next_1221:;
    if ((token_12.tag != Public_)) goto next_1222;
    match_296 = (struct String){.str = "public", .len = 6};
    goto end_match_1173;
next_1222:;
    if ((token_12.tag != Rec_)) goto next_1223;
    match_296 = (struct String){.str = "rec", .len = 3};
    goto end_match_1173;
next_1223:;
    if ((token_12.tag != Then_)) goto next_1224;
    match_296 = (struct String){.str = "then", .len = 4};
    goto end_match_1173;
next_1224:;
    if ((token_12.tag != Type_)) goto next_1225;
    match_296 = (struct String){.str = "type", .len = 4};
    goto end_match_1173;
next_1225:;
    if ((token_12.tag != When_)) goto next_1226;
    match_296 = (struct String){.str = "when", .len = 4};
    goto end_match_1173;
next_1226:;
    if ((token_12.tag != With_)) goto next_1227;
    match_296 = (struct String){.str = "with", .len = 4};
    goto end_match_1173;
next_1227:;
end_match_1173:;
    return match_296;
}

struct DumpTree_ fun_30(void* env_24, struct ATy_ arg_96) {
    struct DumpTree_ call_892 = atDump_(arg_96);
    return call_892;
}

struct DumpTree_ fun_31(void* env_25, struct ATy_ arg_97) {
    struct DumpTree_ call_893 = atDump_(arg_97);
    return call_893;
}

struct DumpTree_ fun_32(void* env_26, struct ATy_ arg_98) {
    struct DumpTree_ call_894 = atDump_(arg_98);
    return call_894;
}

struct DumpTree_ atDump_(struct ATy_ ty_43) {
    struct DumpTree_ match_297;
    if ((ty_43.tag != Missing_)) goto next_1229;
    struct IntIntTuple2 loc_23 = (*(ty_43.Missing_));
    struct DumpTree_ call_895 = dumpTreeFromError_((struct String){.str = "missing", .len = 7}, loc_23);
    match_297 = call_895;
    goto end_match_1228;
next_1229:;
    if ((ty_43.tag != App_1)) goto next_1230;
    struct String ident_9 = (*(ty_43.App_1)).t0;
    struct ATy_List* tys_6 = (*(ty_43.App_1)).t1;
    void* box_21 = (void*)malloc(sizeof(int));
    (*(((int*)box_21))) = 0;
    void* env_66 = box_21;
    struct ATy_DumpTree_Fun1 fun_72 = (struct ATy_DumpTree_Fun1){.fun = fun_30, .env = env_66};
    struct DumpTree_List* call_896 = listMap_7(fun_72, tys_6);
    struct DumpTree_ call_897 = dumpTreeNew_(ident_9, call_896);
    match_297 = call_897;
    goto end_match_1228;
next_1230:;
    if ((ty_43.tag != Suffix_)) goto next_1231;
    struct ATy_ lTy_2 = (*(ty_43.Suffix_)).t0;
    struct String ident_10 = (*(ty_43.Suffix_)).t1;
    struct DumpTree_ call_898 = atDump_(lTy_2);
    struct DumpTree_List* list_96 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_96->head = call_898;
    list_96->tail = NULL;
    struct DumpTree_ call_899 = dumpTreeNew_(ident_10, list_96);
    match_297 = call_899;
    goto end_match_1228;
next_1231:;
    if ((ty_43.tag != Tuple_)) goto next_1232;
    struct ATy_List* itemTys_ = (*(ty_43.Tuple_)).t0;
    void* box_22 = (void*)malloc(sizeof(int));
    (*(((int*)box_22))) = 0;
    void* env_67 = box_22;
    struct ATy_DumpTree_Fun1 fun_73 = (struct ATy_DumpTree_Fun1){.fun = fun_31, .env = env_67};
    struct DumpTree_List* call_900 = listMap_7(fun_73, itemTys_);
    struct DumpTree_ call_901 = dumpTreeNew_((struct String){.str = "tuple", .len = 5}, call_900);
    match_297 = call_901;
    goto end_match_1228;
next_1232:;
    if ((ty_43.tag != Fun_1)) goto next_1233;
    struct ATy_ sTy_ = (*(ty_43.Fun_1)).t0;
    struct ATy_ tTy_ = (*(ty_43.Fun_1)).t1;
    void* box_23 = (void*)malloc(sizeof(int));
    (*(((int*)box_23))) = 0;
    void* env_68 = box_23;
    struct ATy_DumpTree_Fun1 fun_74 = (struct ATy_DumpTree_Fun1){.fun = fun_32, .env = env_68};
    struct ATy_List* list_98 = (struct ATy_List*)malloc(sizeof(struct ATy_List));
    list_98->head = tTy_;
    list_98->tail = NULL;
    struct ATy_List* list_97 = (struct ATy_List*)malloc(sizeof(struct ATy_List));
    list_97->head = sTy_;
    list_97->tail = list_98;
    struct DumpTree_List* call_902 = listMap_7(fun_74, list_97);
    struct DumpTree_ call_903 = dumpTreeNew_((struct String){.str = "fun", .len = 3}, call_902);
    match_297 = call_903;
    goto end_match_1228;
next_1233:;
    exit(1);
end_match_1228:;
    return match_297;
}

struct DumpTree_ fun_33(void* env_27, struct APat_ arg_99) {
    struct DumpTree_ call_904 = apDump_(arg_99);
    return call_904;
}

struct DumpTree_ fun_34(void* env_28, struct APat_ arg_100) {
    struct DumpTree_ call_905 = apDump_(arg_100);
    return call_905;
}

struct DumpTree_ fun_35(void* env_29, struct APat_ arg_101) {
    struct DumpTree_ call_906 = apDump_(arg_101);
    return call_906;
}

struct DumpTree_ fun_36(void* env_30, struct APat_ arg_102) {
    struct DumpTree_ call_907 = apDump_(arg_102);
    return call_907;
}

struct DumpTree_ apDump_(struct APat_ pat_10) {
    struct DumpTree_ match_298;
    if ((pat_10.tag != Missing_1)) goto next_1235;
    struct IntIntTuple2 loc_24 = (*(pat_10.Missing_1));
    struct DumpTree_ call_908 = dumpTreeFromError_((struct String){.str = "missing", .len = 7}, loc_24);
    match_298 = call_908;
    goto end_match_1234;
next_1235:;
    if ((pat_10.tag != Lit_)) goto next_1236;
    struct Lit_ lit_6 = (*(pat_10.Lit_)).t0;
    struct String call_909 = litToString_(lit_6);
    struct DumpTree_ call_910 = dumpTreeNewLeaf_(call_909);
    match_298 = call_910;
    goto end_match_1234;
next_1236:;
    if ((pat_10.tag != Ident_1)) goto next_1237;
    struct String ident_11 = (*(pat_10.Ident_1)).t0;
    struct DumpTree_ call_911 = dumpTreeNewLeaf_(ident_11);
    match_298 = call_911;
    goto end_match_1234;
next_1237:;
    if ((pat_10.tag != ListLit_)) goto next_1238;
    struct APat_List* pats_ = (*(pat_10.ListLit_)).t0;
    void* box_24 = (void*)malloc(sizeof(int));
    (*(((int*)box_24))) = 0;
    void* env_69 = box_24;
    struct APat_DumpTree_Fun1 fun_75 = (struct APat_DumpTree_Fun1){.fun = fun_33, .env = env_69};
    struct DumpTree_List* call_912 = listMap_5(fun_75, pats_);
    struct DumpTree_ call_913 = dumpTreeNew_((struct String){.str = "list", .len = 4}, call_912);
    match_298 = call_913;
    goto end_match_1234;
next_1238:;
    if ((pat_10.tag != Nav_)) goto next_1239;
    struct APat_ l_11 = (*(pat_10.Nav_)).t0;
    struct String r_24 = (*(pat_10.Nav_)).t1;
    struct DumpTree_ call_914 = apDump_(l_11);
    struct DumpTree_List* list_99 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_99->head = call_914;
    list_99->tail = NULL;
    struct DumpTree_ call_915 = dumpTreeNew_(str_add((struct String){.str = ".", .len = 1}, r_24), list_99);
    match_298 = call_915;
    goto end_match_1234;
next_1239:;
    if ((pat_10.tag != Call_)) goto next_1240;
    struct APat_ calleePat_ = (*(pat_10.Call_)).t0;
    struct APat_List* argPats_ = (*(pat_10.Call_)).t1;
    struct DumpTree_ call_916 = apDump_(calleePat_);
    void* box_25 = (void*)malloc(sizeof(int));
    (*(((int*)box_25))) = 0;
    void* env_70 = box_25;
    struct APat_DumpTree_Fun1 fun_76 = (struct APat_DumpTree_Fun1){.fun = fun_34, .env = env_70};
    struct DumpTree_List* call_917 = listMap_5(fun_76, argPats_);
    struct DumpTree_List* list_100 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_100->head = call_916;
    list_100->tail = call_917;
    struct DumpTree_ call_918 = dumpTreeNew_((struct String){.str = "call", .len = 4}, list_100);
    match_298 = call_918;
    goto end_match_1234;
next_1240:;
    if ((pat_10.tag != Cons_2)) goto next_1241;
    struct APat_ head_1 = (*(pat_10.Cons_2)).t0;
    struct APat_ tail_1 = (*(pat_10.Cons_2)).t1;
    struct DumpTree_ call_919 = apDump_(tail_1);
    struct DumpTree_ call_920 = apDump_(head_1);
    struct DumpTree_List* list_101 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_101->head = call_920;
    list_101->tail = NULL;
    struct DumpTree_ call_921 = dumpTreeNew_((struct String){.str = "cons", .len = 4}, list_101);
    struct DumpTree_ call_922 = dumpTreeAttachNext_(call_919, call_921);
    match_298 = call_922;
    goto end_match_1234;
next_1241:;
    if ((pat_10.tag != TupleLit_)) goto next_1242;
    struct APat_List* pats_1 = (*(pat_10.TupleLit_)).t0;
    void* box_26 = (void*)malloc(sizeof(int));
    (*(((int*)box_26))) = 0;
    void* env_71 = box_26;
    struct APat_DumpTree_Fun1 fun_77 = (struct APat_DumpTree_Fun1){.fun = fun_35, .env = env_71};
    struct DumpTree_List* call_923 = listMap_5(fun_77, pats_1);
    struct DumpTree_ call_924 = dumpTreeNew_((struct String){.str = "tuple", .len = 5}, call_923);
    match_298 = call_924;
    goto end_match_1234;
next_1242:;
    if ((pat_10.tag != As_1)) goto next_1243;
    struct APat_ pat_11 = (*(pat_10.As_1)).t0;
    struct String ident_12 = (*(pat_10.As_1)).t1;
    struct DumpTree_ call_925 = apDump_(pat_11);
    struct DumpTree_List* list_102 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_102->head = call_925;
    list_102->tail = NULL;
    struct DumpTree_ call_926 = dumpTreeNew_(str_add((struct String){.str = "as ", .len = 3}, ident_12), list_102);
    match_298 = call_926;
    goto end_match_1234;
next_1243:;
    if ((pat_10.tag != Anno_)) goto next_1244;
    struct APat_ pat_12 = (*(pat_10.Anno_)).t0;
    struct ATy_ ty_44 = (*(pat_10.Anno_)).t1;
    struct DumpTree_ call_927 = apDump_(pat_12);
    struct DumpTree_ call_928 = atDump_(ty_44);
    struct DumpTree_List* list_104 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_104->head = call_928;
    list_104->tail = NULL;
    struct DumpTree_List* list_103 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_103->head = call_927;
    list_103->tail = list_104;
    struct DumpTree_ call_929 = dumpTreeNew_((struct String){.str = "anno", .len = 4}, list_103);
    match_298 = call_929;
    goto end_match_1234;
next_1244:;
    if ((pat_10.tag != Or_2)) goto next_1245;
    struct APat_ l_12 = (*(pat_10.Or_2)).t0;
    struct APat_ r_25 = (*(pat_10.Or_2)).t1;
    struct DumpTree_ call_930 = apDump_(r_25);
    struct DumpTree_ call_931 = apDump_(l_12);
    struct DumpTree_List* list_105 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_105->head = call_931;
    list_105->tail = NULL;
    struct DumpTree_ call_932 = dumpTreeNew_((struct String){.str = "or", .len = 2}, list_105);
    struct DumpTree_ call_933 = dumpTreeAttachNext_(call_930, call_932);
    match_298 = call_933;
    goto end_match_1234;
next_1245:;
    if ((pat_10.tag != Fun_2)) goto next_1246;
    struct String callee_3 = (*(pat_10.Fun_2)).t0;
    struct APat_List* args_5 = (*(pat_10.Fun_2)).t1;
    struct DumpTree_ call_934 = dumpTreeNewLeaf_(callee_3);
    void* box_27 = (void*)malloc(sizeof(int));
    (*(((int*)box_27))) = 0;
    void* env_72 = box_27;
    struct APat_DumpTree_Fun1 fun_78 = (struct APat_DumpTree_Fun1){.fun = fun_36, .env = env_72};
    struct DumpTree_List* call_935 = listMap_5(fun_78, args_5);
    struct DumpTree_List* list_106 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_106->head = call_934;
    list_106->tail = call_935;
    struct DumpTree_ call_936 = dumpTreeNew_((struct String){.str = "fun", .len = 3}, list_106);
    match_298 = call_936;
    goto end_match_1234;
next_1246:;
    exit(1);
end_match_1234:;
    return match_298;
}

struct DumpTree_ fun_37(void* env_31, struct AExpr_ arg_103) {
    struct DumpTree_ call_937 = axDump_(arg_103);
    return call_937;
}

struct DumpTree_ dumpArm_(struct AArm_ arg_226) {
    struct APat_ pat_13 = (*(arg_226.AArm_)).t0;
    struct AExpr_ guard_1 = (*(arg_226.AArm_)).t1;
    struct AExpr_ body_3 = (*(arg_226.AArm_)).t2;
    struct DumpTree_ call_938 = axDump_(body_3);
    struct DumpTree_ call_939 = apDump_(pat_13);
    struct DumpTree_ call_940 = axDump_(guard_1);
    struct DumpTree_List* list_108 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_108->head = call_940;
    list_108->tail = NULL;
    struct DumpTree_List* list_107 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_107->head = call_939;
    list_107->tail = list_108;
    struct DumpTree_ call_941 = dumpTreeNew_((struct String){.str = "arm", .len = 3}, list_107);
    struct DumpTree_ call_942 = dumpTreeAttachNext_(call_938, call_941);
    return call_942;
}

struct DumpTree_ fun_38(void* env_32, struct AArm_ arg_104) {
    struct DumpTree_ call_943 = dumpArm_(arg_104);
    return call_943;
}

struct DumpTree_ fun_39(void* env_33, struct APat_ arg_105) {
    struct DumpTree_ call_944 = apDump_(arg_105);
    return call_944;
}

struct DumpTree_ fun_40(void* env_34, struct AExpr_ arg_106) {
    struct DumpTree_ call_945 = axDump_(arg_106);
    return call_945;
}

struct DumpTree_ fun_41(void* env_35, struct AExpr_ arg_107) {
    struct DumpTree_ call_946 = axDump_(arg_107);
    return call_946;
}

struct DumpTree_ fun_42(void* env_36, struct AExpr_ arg_108) {
    struct DumpTree_ call_947 = axDump_(arg_108);
    return call_947;
}

struct DumpTree_ dumpVariant_(struct AVariant_ arg_227) {
    struct String ident_16 = (*(arg_227.AVariant_)).t0;
    struct DumpTree_ call_948 = dumpTreeNewLeaf_(ident_16);
    return call_948;
}

struct DumpTree_ fun_43(void* env_37, struct AVariant_ arg_109) {
    struct DumpTree_ call_949 = dumpVariant_(arg_109);
    return call_949;
}

struct DumpTree_ fun_44(void* env_38, struct String arg_110) {
    struct DumpTree_ call_950 = dumpTreeNewLeaf_(arg_110);
    return call_950;
}

struct DumpTree_ axDump_(struct AExpr_ expr_7) {
    struct DumpTree_ match_299;
    if ((expr_7.tag != Missing_2)) goto next_1248;
    struct IntIntTuple2 loc_25 = (*(expr_7.Missing_2));
    struct DumpTree_ call_951 = dumpTreeFromError_((struct String){.str = "missing", .len = 7}, loc_25);
    match_299 = call_951;
    goto end_match_1247;
next_1248:;
    if ((expr_7.tag != Lit_1)) goto next_1249;
    struct Lit_ lit_7 = (*(expr_7.Lit_1)).t0;
    struct String call_952 = litToString_(lit_7);
    struct DumpTree_ call_953 = dumpTreeNewLeaf_(call_952);
    match_299 = call_953;
    goto end_match_1247;
next_1249:;
    if ((expr_7.tag != Ident_2)) goto next_1250;
    struct String ident_13 = (*(expr_7.Ident_2)).t0;
    struct DumpTree_ call_954 = dumpTreeNewLeaf_(ident_13);
    match_299 = call_954;
    goto end_match_1247;
next_1250:;
    if ((expr_7.tag != ListLit_1)) goto next_1251;
    struct AExpr_List* items_2 = (*(expr_7.ListLit_1)).t0;
    void* box_28 = (void*)malloc(sizeof(int));
    (*(((int*)box_28))) = 0;
    void* env_73 = box_28;
    struct AExpr_DumpTree_Fun1 fun_79 = (struct AExpr_DumpTree_Fun1){.fun = fun_37, .env = env_73};
    struct DumpTree_List* call_955 = listMap_4(fun_79, items_2);
    struct DumpTree_ call_956 = dumpTreeNew_((struct String){.str = "list", .len = 4}, call_955);
    match_299 = call_956;
    goto end_match_1247;
next_1251:;
    if ((expr_7.tag != If_1)) goto next_1252;
    struct AExpr_ cond_ = (*(expr_7.If_1)).t0;
    struct AExpr_ body_2 = (*(expr_7.If_1)).t1;
    struct AExpr_ alt_ = (*(expr_7.If_1)).t2;
    struct DumpTree_ call_957 = axDump_(cond_);
    struct DumpTree_ call_958 = axDump_(body_2);
    struct DumpTree_ call_959 = axDump_(alt_);
    struct DumpTree_List* list_111 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_111->head = call_959;
    list_111->tail = NULL;
    struct DumpTree_List* list_110 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_110->head = call_958;
    list_110->tail = list_111;
    struct DumpTree_List* list_109 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_109->head = call_957;
    list_109->tail = list_110;
    struct DumpTree_ call_960 = dumpTreeNew_((struct String){.str = "if", .len = 2}, list_109);
    match_299 = call_960;
    goto end_match_1247;
next_1252:;
    if ((expr_7.tag != Match_1)) goto next_1253;
    struct AExpr_ target_1 = (*(expr_7.Match_1)).t0;
    struct AArm_List* arms_2 = (*(expr_7.Match_1)).t1;
    struct DumpTree_ call_961 = axDump_(target_1);
    void* box_29 = (void*)malloc(sizeof(int));
    (*(((int*)box_29))) = 0;
    void* env_74 = box_29;
    struct AArm_DumpTree_Fun1 fun_80 = (struct AArm_DumpTree_Fun1){.fun = fun_38, .env = env_74};
    struct DumpTree_List* call_962 = listMap_6(fun_80, arms_2);
    struct DumpTree_List* list_112 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_112->head = call_961;
    list_112->tail = call_962;
    struct DumpTree_ call_963 = dumpTreeNew_((struct String){.str = "match", .len = 5}, list_112);
    match_299 = call_963;
    goto end_match_1247;
next_1253:;
    if ((expr_7.tag != Fun_3)) goto next_1254;
    struct APat_List* pats_2 = (*(expr_7.Fun_3)).t0;
    struct AExpr_ body_4 = (*(expr_7.Fun_3)).t1;
    struct DumpTree_ call_964 = axDump_(body_4);
    void* box_30 = (void*)malloc(sizeof(int));
    (*(((int*)box_30))) = 0;
    void* env_75 = box_30;
    struct APat_DumpTree_Fun1 fun_81 = (struct APat_DumpTree_Fun1){.fun = fun_39, .env = env_75};
    struct DumpTree_List* call_965 = listMap_5(fun_81, pats_2);
    struct DumpTree_ call_966 = dumpTreeNew_((struct String){.str = "fun", .len = 3}, call_965);
    struct DumpTree_ call_967 = dumpTreeAttachNext_(call_964, call_966);
    match_299 = call_967;
    goto end_match_1247;
next_1254:;
    if ((expr_7.tag != Nav_1)) goto next_1255;
    struct AExpr_ l_13 = (*(expr_7.Nav_1)).t0;
    struct String r_26 = (*(expr_7.Nav_1)).t1;
    struct DumpTree_ call_968 = axDump_(l_13);
    struct DumpTree_List* list_113 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_113->head = call_968;
    list_113->tail = NULL;
    struct DumpTree_ call_969 = dumpTreeNew_(str_add((struct String){.str = ".", .len = 1}, r_26), list_113);
    match_299 = call_969;
    goto end_match_1247;
next_1255:;
    if ((expr_7.tag != Index_)) goto next_1256;
    struct AExpr_ l_14 = (*(expr_7.Index_)).t0;
    struct AExpr_ r_27 = (*(expr_7.Index_)).t1;
    struct DumpTree_ call_970 = axDump_(l_14);
    struct DumpTree_List* list_114 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_114->head = call_970;
    list_114->tail = NULL;
    struct DumpTree_ call_971 = dumpTreeNew_((struct String){.str = "index", .len = 5}, list_114);
    match_299 = call_971;
    goto end_match_1247;
next_1256:;
    if ((expr_7.tag != Uni_)) goto next_1257;
    if (((*(expr_7.Uni_)).t0.tag != Neg_)) goto next_1257;
    struct AExpr_ arg_1 = (*(expr_7.Uni_)).t1;
    struct DumpTree_ call_972 = axDump_(arg_1);
    struct DumpTree_List* list_115 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_115->head = call_972;
    list_115->tail = NULL;
    struct DumpTree_ call_973 = dumpTreeNew_((struct String){.str = "-", .len = 1}, list_115);
    match_299 = call_973;
    goto end_match_1247;
next_1257:;
    if ((expr_7.tag != Bin_)) goto next_1258;
    struct AExpr_ l_15 = (*(expr_7.Bin_)).t1;
    struct AExpr_ r_28 = (*(expr_7.Bin_)).t2;
    struct DumpTree_ call_974 = axDump_(l_15);
    struct DumpTree_ call_975 = axDump_(r_28);
    struct DumpTree_List* list_117 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_117->head = call_975;
    list_117->tail = NULL;
    struct DumpTree_List* list_116 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_116->head = call_974;
    list_116->tail = list_117;
    struct DumpTree_ call_976 = dumpTreeNew_((struct String){.str = "bin", .len = 3}, list_116);
    match_299 = call_976;
    goto end_match_1247;
next_1258:;
    if ((expr_7.tag != Range_)) goto next_1259;
    struct AExpr_List* items_3 = (*(expr_7.Range_)).t0;
    void* box_31 = (void*)malloc(sizeof(int));
    (*(((int*)box_31))) = 0;
    void* env_76 = box_31;
    struct AExpr_DumpTree_Fun1 fun_82 = (struct AExpr_DumpTree_Fun1){.fun = fun_40, .env = env_76};
    struct DumpTree_List* call_977 = listMap_4(fun_82, items_3);
    struct DumpTree_ call_978 = dumpTreeNew_((struct String){.str = "range", .len = 5}, call_977);
    match_299 = call_978;
    goto end_match_1247;
next_1259:;
    if ((expr_7.tag != TupleLit_1)) goto next_1260;
    struct AExpr_List* items_4 = (*(expr_7.TupleLit_1)).t0;
    void* box_32 = (void*)malloc(sizeof(int));
    (*(((int*)box_32))) = 0;
    void* env_77 = box_32;
    struct AExpr_DumpTree_Fun1 fun_83 = (struct AExpr_DumpTree_Fun1){.fun = fun_41, .env = env_77};
    struct DumpTree_List* call_979 = listMap_4(fun_83, items_4);
    struct DumpTree_ call_980 = dumpTreeNew_((struct String){.str = "tuple", .len = 5}, call_979);
    match_299 = call_980;
    goto end_match_1247;
next_1260:;
    if ((expr_7.tag != Anno_1)) goto next_1261;
    struct AExpr_ body_5 = (*(expr_7.Anno_1)).t0;
    struct ATy_ ty_45 = (*(expr_7.Anno_1)).t1;
    struct DumpTree_ call_981 = axDump_(body_5);
    struct DumpTree_ call_982 = atDump_(ty_45);
    struct DumpTree_List* list_119 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_119->head = call_982;
    list_119->tail = NULL;
    struct DumpTree_List* list_118 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_118->head = call_981;
    list_118->tail = list_119;
    struct DumpTree_ call_983 = dumpTreeNew_((struct String){.str = "anno", .len = 4}, list_118);
    match_299 = call_983;
    goto end_match_1247;
next_1261:;
    if ((expr_7.tag != Semi_1)) goto next_1262;
    struct AExpr_List* exprs_ = (*(expr_7.Semi_1)).t0;
    void* box_33 = (void*)malloc(sizeof(int));
    (*(((int*)box_33))) = 0;
    void* env_78 = box_33;
    struct AExpr_DumpTree_Fun1 fun_84 = (struct AExpr_DumpTree_Fun1){.fun = fun_42, .env = env_78};
    struct DumpTree_List* call_984 = listMap_4(fun_84, exprs_);
    struct DumpTree_ call_985 = dumpTreeNew_((struct String){.str = "semi", .len = 4}, call_984);
    match_299 = call_985;
    goto end_match_1247;
next_1262:;
    if ((expr_7.tag != Let_1)) goto next_1263;
    struct APat_ pat_14 = (*(expr_7.Let_1)).t0;
    struct AExpr_ body_6 = (*(expr_7.Let_1)).t1;
    struct AExpr_ next_8 = (*(expr_7.Let_1)).t2;
    struct DumpTree_ call_986 = axDump_(next_8);
    struct DumpTree_ call_987 = apDump_(pat_14);
    struct DumpTree_ call_988 = axDump_(body_6);
    struct DumpTree_List* list_121 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_121->head = call_988;
    list_121->tail = NULL;
    struct DumpTree_List* list_120 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_120->head = call_987;
    list_120->tail = list_121;
    struct DumpTree_ call_989 = dumpTreeNew_((struct String){.str = "let", .len = 3}, list_120);
    struct DumpTree_ call_990 = dumpTreeAttachNext_(call_986, call_989);
    match_299 = call_990;
    goto end_match_1247;
next_1263:;
    if ((expr_7.tag != TySynonym_)) goto next_1264;
    struct String ident_14 = (*(expr_7.TySynonym_)).t0;
    struct ATy_ ty_46 = (*(expr_7.TySynonym_)).t1;
    struct DumpTree_ call_991 = atDump_(ty_46);
    struct DumpTree_ call_992 = dumpTreeNewLeaf_(ident_14);
    struct DumpTree_List* list_122 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_122->head = call_992;
    list_122->tail = NULL;
    struct DumpTree_ call_993 = dumpTreeNew_((struct String){.str = "synonym", .len = 7}, list_122);
    struct DumpTree_ call_994 = dumpTreeAttachNext_(call_991, call_993);
    match_299 = call_994;
    goto end_match_1247;
next_1264:;
    if ((expr_7.tag != TyUnion_)) goto next_1265;
    struct String ident_15 = (*(expr_7.TyUnion_)).t0;
    struct AVariant_List* variants_ = (*(expr_7.TyUnion_)).t1;
    struct DumpTree_ call_995 = dumpTreeNewLeaf_(ident_15);
    void* box_34 = (void*)malloc(sizeof(int));
    (*(((int*)box_34))) = 0;
    void* env_79 = box_34;
    struct AVariant_DumpTree_Fun1 fun_85 = (struct AVariant_DumpTree_Fun1){.fun = fun_43, .env = env_79};
    struct DumpTree_List* call_996 = listMap_3(fun_85, variants_);
    struct DumpTree_List* list_123 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_123->head = call_995;
    list_123->tail = call_996;
    struct DumpTree_ call_997 = dumpTreeNew_((struct String){.str = "union", .len = 5}, list_123);
    match_299 = call_997;
    goto end_match_1247;
next_1265:;
    if ((expr_7.tag != Open_1)) goto next_1266;
    struct StringList* path_1 = (*(expr_7.Open_1)).t0;
    void* box_35 = (void*)malloc(sizeof(int));
    (*(((int*)box_35))) = 0;
    void* env_80 = box_35;
    struct StringDumpTree_Fun1 fun_86 = (struct StringDumpTree_Fun1){.fun = fun_44, .env = env_80};
    struct DumpTree_List* call_998 = listMap_1(fun_86, path_1);
    struct DumpTree_ call_999 = dumpTreeNew_((struct String){.str = "open", .len = 4}, call_998);
    match_299 = call_999;
    goto end_match_1247;
next_1266:;
    exit(1);
end_match_1247:;
    return match_299;
}

struct String findIdent_(struct NameCtx_ nameCtx_, int serial_9) {
    struct String call_1000 = nameCtxFind_(serial_9, nameCtx_);
    return call_1000;
}

struct NameCtx_Tuple1 {
    struct NameCtx_ t0;
};

struct DumpTree_ fun_45(void* env_39, struct HExpr_ arg_111) {
    struct NameCtx_ arg_112 = (*(((struct NameCtx_Tuple1*)env_39))).t0;
    struct DumpTree_ call_1001 = hxDump_(arg_112, arg_111);
    return call_1001;
}

struct DumpTree_ fun_46(void* env_40, struct String arg_113) {
    struct DumpTree_ call_1002 = dumpTreeNewLeaf_(arg_113);
    return call_1002;
}

struct DumpTree_ hxDump_(struct NameCtx_ nameCtx_, struct HExpr_ expr_8) {
    struct DumpTree_ match_300;
    if ((expr_8.tag != Lit_3)) goto next_1268;
    struct Lit_ lit_8 = (*(expr_8.Lit_3)).t0;
    struct String call_1003 = litToString_(lit_8);
    struct DumpTree_ call_1004 = dumpTreeNewLeaf_(call_1003);
    match_300 = call_1004;
    goto end_match_1267;
next_1268:;
    if ((expr_8.tag != Prim_)) goto next_1269;
    struct DumpTree_ call_1005 = dumpTreeNewLeaf_((struct String){.str = "prim", .len = 4});
    match_300 = call_1005;
    goto end_match_1267;
next_1269:;
    if ((expr_8.tag != Ref_2)) goto next_1270;
    int serial_10 = (*(expr_8.Ref_2)).t0;
    struct String call_1006 = findIdent_(nameCtx_, serial_10);
    struct DumpTree_ call_1007 = dumpTreeNewLeaf_(call_1006);
    match_300 = call_1007;
    goto end_match_1267;
next_1270:;
    if ((expr_8.tag != Match_2)) goto next_1271;
    struct HExpr_ target_2 = (*(expr_8.Match_2)).t0;
    struct HPat_HExpr_HExpr_Tuple3List* _arms_ = (*(expr_8.Match_2)).t1;
    struct Ty_ _ty_ = (*(expr_8.Match_2)).t2;
    struct IntIntTuple2 _loc_ = (*(expr_8.Match_2)).t3;
    struct DumpTree_ call_1008 = hxDump_(nameCtx_, target_2);
    struct DumpTree_List* list_124 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_124->head = call_1008;
    list_124->tail = NULL;
    struct DumpTree_ call_1009 = dumpTreeNew_((struct String){.str = "match", .len = 5}, list_124);
    match_300 = call_1009;
    goto end_match_1267;
next_1271:;
    if ((expr_8.tag != Nav_3)) goto next_1272;
    struct HExpr_ l_16 = (*(expr_8.Nav_3)).t0;
    struct String r_29 = (*(expr_8.Nav_3)).t1;
    struct Ty_ _ty_1 = (*(expr_8.Nav_3)).t2;
    struct IntIntTuple2 _loc_1 = (*(expr_8.Nav_3)).t3;
    struct DumpTree_ call_1010 = hxDump_(nameCtx_, l_16);
    struct DumpTree_List* list_125 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_125->head = call_1010;
    list_125->tail = NULL;
    struct DumpTree_ call_1011 = dumpTreeNew_(str_add((struct String){.str = ".", .len = 1}, r_29), list_125);
    match_300 = call_1011;
    goto end_match_1267;
next_1272:;
    if ((expr_8.tag != Inf_)) goto next_1273;
    struct HExpr_List* items_5 = (*(expr_8.Inf_)).t1;
    struct Ty_ _ty_2 = (*(expr_8.Inf_)).t2;
    struct IntIntTuple2 _loc_2 = (*(expr_8.Inf_)).t3;
    struct NameCtx_Tuple1 tuple_622;
    tuple_622.t0 = nameCtx_;
    void* box_36 = (void*)malloc(sizeof(struct NameCtx_Tuple1));
    (*(((struct NameCtx_Tuple1*)box_36))) = tuple_622;
    void* env_81 = box_36;
    struct HExpr_DumpTree_Fun1 fun_87 = (struct HExpr_DumpTree_Fun1){.fun = fun_45, .env = env_81};
    struct DumpTree_List* call_1012 = listMap_2(fun_87, items_5);
    struct DumpTree_ call_1013 = dumpTreeNew_((struct String){.str = "inf", .len = 3}, call_1012);
    match_300 = call_1013;
    goto end_match_1267;
next_1273:;
    if ((expr_8.tag != Let_2)) goto next_1274;
    struct HPat_ _pat_ = (*(expr_8.Let_2)).t0;
    struct HExpr_ body_7 = (*(expr_8.Let_2)).t1;
    struct HExpr_ next_9 = (*(expr_8.Let_2)).t2;
    struct Ty_ _ty_3 = (*(expr_8.Let_2)).t3;
    struct IntIntTuple2 _loc_3 = (*(expr_8.Let_2)).t4;
    struct DumpTree_ call_1014 = hxDump_(nameCtx_, next_9);
    struct DumpTree_ call_1015 = hxDump_(nameCtx_, body_7);
    struct DumpTree_List* list_126 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_126->head = call_1015;
    list_126->tail = NULL;
    struct DumpTree_ call_1016 = dumpTreeNew_((struct String){.str = "let-val", .len = 7}, list_126);
    struct DumpTree_ call_1017 = dumpTreeAttachNext_(call_1014, call_1016);
    match_300 = call_1017;
    goto end_match_1267;
next_1274:;
    if ((expr_8.tag != LetFun_1)) goto next_1275;
    int callee_4 = (*(expr_8.LetFun_1)).t0;
    struct HPat_List* _args_ = (*(expr_8.LetFun_1)).t2;
    struct HExpr_ body_8 = (*(expr_8.LetFun_1)).t3;
    struct HExpr_ next_10 = (*(expr_8.LetFun_1)).t4;
    struct Ty_ _ty_4 = (*(expr_8.LetFun_1)).t5;
    struct IntIntTuple2 _loc_4 = (*(expr_8.LetFun_1)).t6;
    struct DumpTree_ call_1018 = hxDump_(nameCtx_, next_10);
    struct String call_1019 = findIdent_(nameCtx_, callee_4);
    struct DumpTree_ call_1020 = dumpTreeNewLeaf_(call_1019);
    struct DumpTree_ call_1021 = hxDump_(nameCtx_, body_8);
    struct DumpTree_List* list_128 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_128->head = call_1021;
    list_128->tail = NULL;
    struct DumpTree_List* list_127 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_127->head = call_1020;
    list_127->tail = list_128;
    struct DumpTree_ call_1022 = dumpTreeNew_((struct String){.str = "let-fun", .len = 7}, list_127);
    struct DumpTree_ call_1023 = dumpTreeAttachNext_(call_1018, call_1022);
    match_300 = call_1023;
    goto end_match_1267;
next_1275:;
    if ((expr_8.tag != TyDecl_)) goto next_1276;
    if (((*(expr_8.TyDecl_)).t1.tag != Synonym_1)) goto next_1276;
    struct Ty_ _ty_5 = (*((*(expr_8.TyDecl_)).t1.Synonym_1)).t0;
    struct IntIntTuple2 _loc_5 = (*((*(expr_8.TyDecl_)).t1.Synonym_1)).t1;
    struct DumpTree_ call_1024 = dumpTreeNew_((struct String){.str = "synonym", .len = 7}, NULL);
    match_300 = call_1024;
    goto end_match_1267;
next_1276:;
    if ((expr_8.tag != TyDecl_)) goto next_1277;
    if (((*(expr_8.TyDecl_)).t1.tag != Union_1)) goto next_1277;
    struct String ident_17 = (*((*(expr_8.TyDecl_)).t1.Union_1)).t0;
    struct DumpTree_ call_1025 = dumpTreeNewLeaf_(ident_17);
    struct DumpTree_List* list_129 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_129->head = call_1025;
    list_129->tail = NULL;
    struct DumpTree_ call_1026 = dumpTreeNew_((struct String){.str = "union", .len = 5}, list_129);
    match_300 = call_1026;
    goto end_match_1267;
next_1277:;
    if ((expr_8.tag != Open_2)) goto next_1278;
    struct StringList* path_2 = (*(expr_8.Open_2)).t0;
    void* box_37 = (void*)malloc(sizeof(int));
    (*(((int*)box_37))) = 0;
    void* env_82 = box_37;
    struct StringDumpTree_Fun1 fun_88 = (struct StringDumpTree_Fun1){.fun = fun_46, .env = env_82};
    struct DumpTree_List* call_1027 = listMap_1(fun_88, path_2);
    struct DumpTree_ call_1028 = dumpTreeNew_((struct String){.str = "open", .len = 4}, call_1027);
    match_300 = call_1028;
    goto end_match_1267;
next_1278:;
    if ((expr_8.tag != Error_2)) goto next_1279;
    struct String msg_1 = (*(expr_8.Error_2)).t0;
    struct IntIntTuple2 loc_26 = (*(expr_8.Error_2)).t1;
    struct DumpTree_ call_1029 = dumpTreeFromError_(msg_1, loc_26);
    match_300 = call_1029;
    goto end_match_1267;
next_1279:;
    exit(1);
end_match_1267:;
    return match_300;
}

struct String readModuleFile_(struct StringStringFun1 fileReadAllText_1, struct String moduleName_) {
    struct String app_76 = fileReadAllText_1.fun(fileReadAllText_1.env, str_add(str_add((struct String){.str = "tests/examples/MiloneLang/", .len = 26}, moduleName_), (struct String){.str = ".fs", .len = 3}));
    return app_76;
}

struct StringStringFun1Tuple1 {
    struct StringStringFun1 t0;
};

struct String fun_47(void* env_41, struct String arg_114) {
    struct StringStringFun1 arg_115 = (*(((struct StringStringFun1Tuple1*)env_41))).t0;
    struct String call_1030 = readModuleFile_(arg_115, arg_114);
    return call_1030;
}

int fun_5(struct StringIntIntTuple2Tuple2 arg_228) {
    struct String msg_2 = arg_228.t0;
    struct IntIntTuple2 loc_27 = arg_228.t1;
    struct String call_1031 = locToString_(loc_27);
    printf("ERROR %s (%s)\n", msg_2.str, call_1031.str);
    int call_1032 = 0;
    return 0;
}

int fun_48(void* env_42, struct StringIntIntTuple2Tuple2 arg_116) {
    int call_1033 = fun_5(arg_116);
    return 0;
}

int fun_4(struct StringIntIntTuple2Tuple2List* errors_) {
    void* box_38 = (void*)malloc(sizeof(int));
    (*(((int*)box_38))) = 0;
    void* env_83 = box_38;
    struct StringIntIntTuple2Tuple2UnitFun1 fun_89 = (struct StringIntIntTuple2Tuple2UnitFun1){.fun = fun_48, .env = env_83};
    int call_1034 = listIter_2(fun_89, errors_);
    return 0;
}

int fun_49(void* env_43, struct StringIntIntTuple2Tuple2List* arg_117) {
    int call_1035 = fun_4(arg_117);
    return 0;
}

int doSelf_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, struct IntIntTuple2 noLoc_, char charNull_, struct StringStringFun1 fileReadAllText_1) {
    struct String projectName_ = (struct String){.str = "MiloneLang", .len = 10};
    struct NameCtx_ call_1036 = nameCtxEmpty_(0);
    struct NameCtx_ nameCtx_1 = call_1036;
    struct StringStringFun1Tuple1 tuple_623;
    tuple_623.t0 = fileReadAllText_1;
    void* box_39 = (void*)malloc(sizeof(struct StringStringFun1Tuple1));
    (*(((struct StringStringFun1Tuple1*)box_39))) = tuple_623;
    void* env_84 = box_39;
    struct StringStringFun1 fun_90 = (struct StringStringFun1){.fun = fun_47, .env = env_84};
    struct HExpr_NameCtx_StringIntIntTuple2Tuple2ListListTuple3 call_1037 = parseProjectModules_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, noLoc_, charNull_, fun_90, projectName_, nameCtx_1);
    struct HExpr_ expr_9 = call_1037.t0;
    struct NameCtx_ nameCtx_2 = call_1037.t1;
    struct StringIntIntTuple2Tuple2ListList* errorListList_ = call_1037.t2;
    printf("HIR:\n");
    int call_1038 = 0;
    struct DumpTree_ call_1039 = hxDump_(nameCtx_2, expr_9);
    struct String call_1040 = dumpTreeToString_(call_1039);
    printf("%s\n", call_1040.str);
    int call_1041 = 0;
    void* box_40 = (void*)malloc(sizeof(int));
    (*(((int*)box_40))) = 0;
    void* env_85 = box_40;
    struct StringIntIntTuple2Tuple2ListUnitFun1 fun_91 = (struct StringIntIntTuple2Tuple2ListUnitFun1){.fun = fun_49, .env = env_85};
    int call_1042 = listIter_1(fun_91, errorListList_);
    return 0;
}

struct String fileReadAllText_(struct String fileName_) {
    struct String call_1043 = file_read_all_text(fileName_);
    return call_1043;
}

struct String fun_50(void* env_44, struct String arg_118) {
    struct String call_1044 = fileReadAllText_(arg_118);
    return call_1044;
}

int main() {
    struct IntIntTuple2 tuple_624;
    tuple_624.t0 = (0 - 1);
    tuple_624.t1 = (0 - 1);
    struct IntIntTuple2 noLoc_ = tuple_624;
    struct IntIntTuple2* payload_195 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_195))) = noLoc_;
    struct Ty_ variant_195 = (struct Ty_){.tag = Error_1, .Error_1 = payload_195};
    struct Ty_ noTy_ = variant_195;
    struct TyCon_Ty_ListTuple2 tuple_625;
    tuple_625.t0 = (struct TyCon_){.tag = Bool_2};
    tuple_625.t1 = NULL;
    struct TyCon_Ty_ListTuple2* payload_196 = (struct TyCon_Ty_ListTuple2*)malloc(sizeof(struct TyCon_Ty_ListTuple2));
    (*(((struct TyCon_Ty_ListTuple2*)payload_196))) = tuple_625;
    struct Ty_ variant_196 = (struct Ty_){.tag = Con_, .Con_ = payload_196};
    struct Ty_ tyBool_ = variant_196;
    struct TyCon_Ty_ListTuple2 tuple_626;
    tuple_626.t0 = (struct TyCon_){.tag = Int_2};
    tuple_626.t1 = NULL;
    struct TyCon_Ty_ListTuple2* payload_197 = (struct TyCon_Ty_ListTuple2*)malloc(sizeof(struct TyCon_Ty_ListTuple2));
    (*(((struct TyCon_Ty_ListTuple2*)payload_197))) = tuple_626;
    struct Ty_ variant_197 = (struct Ty_){.tag = Con_, .Con_ = payload_197};
    struct Ty_ tyInt_ = variant_197;
    struct TyCon_Ty_ListTuple2 tuple_627;
    tuple_627.t0 = (struct TyCon_){.tag = Char_2};
    tuple_627.t1 = NULL;
    struct TyCon_Ty_ListTuple2* payload_198 = (struct TyCon_Ty_ListTuple2*)malloc(sizeof(struct TyCon_Ty_ListTuple2));
    (*(((struct TyCon_Ty_ListTuple2*)payload_198))) = tuple_627;
    struct Ty_ variant_198 = (struct Ty_){.tag = Con_, .Con_ = payload_198};
    struct Ty_ tyChar_ = variant_198;
    struct TyCon_Ty_ListTuple2 tuple_628;
    tuple_628.t0 = (struct TyCon_){.tag = Str_2};
    tuple_628.t1 = NULL;
    struct TyCon_Ty_ListTuple2* payload_199 = (struct TyCon_Ty_ListTuple2*)malloc(sizeof(struct TyCon_Ty_ListTuple2));
    (*(((struct TyCon_Ty_ListTuple2*)payload_199))) = tuple_628;
    struct Ty_ variant_199 = (struct Ty_){.tag = Con_, .Con_ = payload_199};
    struct Ty_ tyStr_ = variant_199;
    struct TyCon_Ty_ListTuple2 tuple_629;
    tuple_629.t0 = (struct TyCon_){.tag = Obj_};
    tuple_629.t1 = NULL;
    struct TyCon_Ty_ListTuple2* payload_200 = (struct TyCon_Ty_ListTuple2*)malloc(sizeof(struct TyCon_Ty_ListTuple2));
    (*(((struct TyCon_Ty_ListTuple2*)payload_200))) = tuple_629;
    struct Ty_ variant_200 = (struct Ty_){.tag = Con_, .Con_ = payload_200};
    struct Ty_ tyObj_ = variant_200;
    struct Ty_ call_1045 = tyTuple_(NULL);
    struct Ty_ tyUnit_ = call_1045;
    int* payload_201 = (int*)malloc(sizeof(int));
    (*(((int*)payload_201))) = 1;
    struct Lit_ variant_201 = (struct Lit_){.tag = Bool_, .Bool_ = payload_201};
    struct Lit_ litTrue_ = variant_201;
    int* payload_202 = (int*)malloc(sizeof(int));
    (*(((int*)payload_202))) = 0;
    struct Lit_ variant_202 = (struct Lit_){.tag = Bool_, .Bool_ = payload_202};
    struct Lit_ litFalse_ = variant_202;
    char call_1046 = ((char)0);
    char charNull_ = call_1046;
    void* box_41 = (void*)malloc(sizeof(int));
    (*(((int*)box_41))) = 0;
    void* env_86 = box_41;
    struct StringStringFun1 fun_92 = (struct StringStringFun1){.fun = fun_50, .env = env_86};
    int call_1047 = doSelf_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, noLoc_, charNull_, fun_92);
    return call_1047;
}
