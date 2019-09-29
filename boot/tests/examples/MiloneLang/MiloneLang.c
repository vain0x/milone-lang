#include "milone.h"

struct String failwith_3(struct String str_);

struct StringList;

struct StringList* failwith_2(struct String str_);

enum Token_Tag;

struct Token_;

struct Token_ failwith_1(struct String str_);

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

int go_79(int len_, struct StringList* xs_2);

int listLength_1(struct StringList* xs_1);

struct IntIntTuple2;

struct Token_IntIntTuple2Tuple2;

struct Token_IntIntTuple2Tuple2List;

struct Token_IntIntTuple2Tuple2List* go_78(struct Token_IntIntTuple2Tuple2List* acc_5, struct Token_IntIntTuple2Tuple2List* xs_5);

enum ATy_Tag;

struct ATy_;

struct ATy_List;

struct ATy_List* go_77(struct ATy_List* acc_5, struct ATy_List* xs_5);

enum AVariant_Tag;

struct AVariant_;

struct AVariant_List;

struct AVariant_List* go_76(struct AVariant_List* acc_5, struct AVariant_List* xs_5);

struct APat_List* go_75(struct APat_List* acc_5, struct APat_List* xs_5);

enum AArm_Tag;

struct AArm_;

struct AArm_List;

struct AArm_List* go_74(struct AArm_List* acc_5, struct AArm_List* xs_5);

struct StringList* go_73(struct StringList* acc_5, struct StringList* xs_5);

struct AExpr_List* go_72(struct AExpr_List* acc_5, struct AExpr_List* xs_5);

struct DumpTree_List* go_86(struct DumpTree_List* acc_5, struct DumpTree_List* xs_5);

enum Ty_Tag;

struct Ty_;

struct Ty_List;

struct Ty_List* go_85(struct Ty_List* acc_5, struct Ty_List* xs_5);

enum HExpr_Tag;

struct HExpr_;

struct HPat_HExpr_HExpr_Tuple3;

struct HPat_HExpr_HExpr_Tuple3List;

struct HPat_HExpr_HExpr_Tuple3List* go_84(struct HPat_HExpr_HExpr_Tuple3List* acc_5, struct HPat_HExpr_HExpr_Tuple3List* xs_5);

struct HExpr_List;

struct HExpr_List* go_83(struct HExpr_List* acc_5, struct HExpr_List* xs_5);

struct HPat_List;

struct HPat_List* go_82(struct HPat_List* acc_5, struct HPat_List* xs_5);

struct StringIntBoolTy_Tuple4;

struct StringIntBoolTy_Tuple4List;

struct StringIntBoolTy_Tuple4List* go_81(struct StringIntBoolTy_Tuple4List* acc_5, struct StringIntBoolTy_Tuple4List* xs_5);

struct Token_IntIntTuple2Tuple2List* listRev_7(struct Token_IntIntTuple2Tuple2List* xs_4);

struct ATy_List* listRev_6(struct ATy_List* xs_4);

struct AVariant_List* listRev_5(struct AVariant_List* xs_4);

struct APat_List* listRev_4(struct APat_List* xs_4);

struct AArm_List* listRev_3(struct AArm_List* xs_4);

struct StringList* listRev_2(struct StringList* xs_4);

struct AExpr_List* listRev_1(struct AExpr_List* xs_4);

struct DumpTree_List* listRev_13(struct DumpTree_List* xs_4);

struct Ty_List* listRev_12(struct Ty_List* xs_4);

struct HPat_HExpr_HExpr_Tuple3List* listRev_11(struct HPat_HExpr_HExpr_Tuple3List* xs_4);

struct HExpr_List* listRev_10(struct HExpr_List* xs_4);

struct HPat_List* listRev_9(struct HPat_List* xs_4);

struct StringIntBoolTy_Tuple4List* listRev_8(struct StringIntBoolTy_Tuple4List* xs_4);

struct Token_IntIntTuple2Tuple2UnitFun1;

int listIter_2(struct Token_IntIntTuple2Tuple2UnitFun1 f_, struct Token_IntIntTuple2Tuple2List* xs_7);

struct StringIntIntTuple2Tuple2UnitFun1;

struct StringIntIntTuple2Tuple2;

struct StringIntIntTuple2Tuple2List;

int listIter_1(struct StringIntIntTuple2Tuple2UnitFun1 f_, struct StringIntIntTuple2Tuple2List* xs_7);

struct HExpr_Ty_Fun1;

struct Ty_List* go_71(struct HExpr_Ty_Fun1 f_1, struct Ty_List* acc_6, struct HExpr_List* xs_10);

struct HPat_HExpr_HExpr_Tuple3HPat_HExpr_HExpr_Tuple3Fun1;

struct HPat_HExpr_HExpr_Tuple3List* go_70(struct HPat_HExpr_HExpr_Tuple3HPat_HExpr_HExpr_Tuple3Fun1 f_1, struct HPat_HExpr_HExpr_Tuple3List* acc_6, struct HPat_HExpr_HExpr_Tuple3List* xs_10);

struct HExpr_HExpr_Fun1;

struct HExpr_List* go_69(struct HExpr_HExpr_Fun1 f_1, struct HExpr_List* acc_6, struct HExpr_List* xs_10);

struct HPat_HPat_Fun1;

struct HPat_List* go_68(struct HPat_HPat_Fun1 f_1, struct HPat_List* acc_6, struct HPat_List* xs_10);

struct ATy_DumpTree_Fun1;

struct DumpTree_List* go_67(struct ATy_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct ATy_List* xs_10);

struct AArm_DumpTree_Fun1;

struct DumpTree_List* go_66(struct AArm_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct AArm_List* xs_10);

struct APat_DumpTree_Fun1;

struct DumpTree_List* go_65(struct APat_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct APat_List* xs_10);

struct AExpr_DumpTree_Fun1;

struct DumpTree_List* go_64(struct AExpr_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct AExpr_List* xs_10);

struct AVariant_DumpTree_Fun1;

struct DumpTree_List* go_63(struct AVariant_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct AVariant_List* xs_10);

struct HExpr_DumpTree_Fun1;

struct DumpTree_List* go_62(struct HExpr_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct HExpr_List* xs_10);

struct StringDumpTree_Fun1;

struct DumpTree_List* go_61(struct StringDumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct StringList* xs_10);

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

struct Ty_NameCtx_Tuple2;

struct ATy_NameCtx_Tuple2Ty_NameCtx_Tuple2Fun1;

struct ATy_ListNameCtx_Tuple2;

struct Ty_ListNameCtx_Tuple2;

struct ATy_NameCtx_Tuple2;

struct Ty_ListNameCtx_Tuple2 go_60(struct ATy_NameCtx_Tuple2Ty_NameCtx_Tuple2Fun1 f_5, struct Ty_List* acc_17, struct ATy_ListNameCtx_Tuple2 arg_95);

struct HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2;

struct AArm_NameCtx_Tuple2HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2Fun1;

struct AArm_ListNameCtx_Tuple2;

struct HPat_HExpr_HExpr_Tuple3ListNameCtx_Tuple2;

struct AArm_NameCtx_Tuple2;

struct HPat_HExpr_HExpr_Tuple3ListNameCtx_Tuple2 go_59(struct AArm_NameCtx_Tuple2HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2Fun1 f_5, struct HPat_HExpr_HExpr_Tuple3List* acc_17, struct AArm_ListNameCtx_Tuple2 arg_96);

struct HExpr_NameCtx_Tuple2;

struct AExpr_NameCtx_Tuple2HExpr_NameCtx_Tuple2Fun1;

struct AExpr_ListNameCtx_Tuple2;

struct HExpr_ListNameCtx_Tuple2;

struct AExpr_NameCtx_Tuple2;

struct HExpr_ListNameCtx_Tuple2 go_58(struct AExpr_NameCtx_Tuple2HExpr_NameCtx_Tuple2Fun1 f_5, struct HExpr_List* acc_17, struct AExpr_ListNameCtx_Tuple2 arg_97);

struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1;

struct APat_ListNameCtx_Tuple2;

struct HPat_ListNameCtx_Tuple2;

struct APat_NameCtx_Tuple2;

struct HPat_ListNameCtx_Tuple2 go_57(struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1 f_5, struct HPat_List* acc_17, struct APat_ListNameCtx_Tuple2 arg_98);

struct StringIntBoolTy_Tuple4NameCtx_Tuple2;

struct AVariant_NameCtx_Tuple2StringIntBoolTy_Tuple4NameCtx_Tuple2Fun1;

struct AVariant_ListNameCtx_Tuple2;

struct StringIntBoolTy_Tuple4ListNameCtx_Tuple2;

struct AVariant_NameCtx_Tuple2;

struct StringIntBoolTy_Tuple4ListNameCtx_Tuple2 go_56(struct AVariant_NameCtx_Tuple2StringIntBoolTy_Tuple4NameCtx_Tuple2Fun1 f_5, struct StringIntBoolTy_Tuple4List* acc_17, struct AVariant_ListNameCtx_Tuple2 arg_99);

struct Ty_ListNameCtx_Tuple2 stMap_5(struct ATy_NameCtx_Tuple2Ty_NameCtx_Tuple2Fun1 f_5, struct ATy_ListNameCtx_Tuple2 arg_100);

struct HPat_HExpr_HExpr_Tuple3ListNameCtx_Tuple2 stMap_4(struct AArm_NameCtx_Tuple2HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2Fun1 f_5, struct AArm_ListNameCtx_Tuple2 arg_101);

struct HExpr_ListNameCtx_Tuple2 stMap_3(struct AExpr_NameCtx_Tuple2HExpr_NameCtx_Tuple2Fun1 f_5, struct AExpr_ListNameCtx_Tuple2 arg_102);

struct HPat_ListNameCtx_Tuple2 stMap_2(struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1 f_5, struct APat_ListNameCtx_Tuple2 arg_103);

struct StringIntBoolTy_Tuple4ListNameCtx_Tuple2 stMap_1(struct AVariant_NameCtx_Tuple2StringIntBoolTy_Tuple4NameCtx_Tuple2Fun1 f_5, struct AVariant_ListNameCtx_Tuple2 arg_104);

struct IntIntIntFun2;

struct IntStringTuple2;

struct IntStringTuple2List;

struct IntStringTuple2ListIntIntIntFun2Tuple2;

struct IntStringTuple2ListIntIntIntFun2Tuple2 mapEmpty_1(struct IntIntIntFun2 cmp_3);

struct IntStringTuple2ListIntIntIntFun2Tuple2 mapAdd_1(int key_, struct String value_3, struct IntStringTuple2ListIntIntIntFun2Tuple2 arg_105);

struct StringList* go_80(struct IntIntIntFun2 cmp_6, int key_2, struct IntStringTuple2List* assoc_3);

struct StringList* mapTryFind_1(int key_2, struct IntStringTuple2ListIntIntIntFun2Tuple2 arg_106);

struct String mapFind_1(int key_3, struct IntStringTuple2ListIntIntIntFun2Tuple2 map_);

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

int locX_(struct IntIntTuple2 arg_107);

int locY_(struct IntIntTuple2 arg_108);

int locIsSameRow_(struct IntIntTuple2 first_, struct IntIntTuple2 second_);

int locIsSameColumn_(struct IntIntTuple2 first_1, struct IntIntTuple2 second_1);

int locInside_(struct IntIntTuple2 firstLoc_, struct IntIntTuple2 secondLoc_);

struct IntIntTuple2 locAddX_(int dx_, struct IntIntTuple2 arg_109);

struct IntIntTuple2 locMax_(struct IntIntTuple2 arg_110, struct IntIntTuple2 arg_111);

struct String locToString_(struct IntIntTuple2 arg_112);

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

struct DumpTree_ dumpTreeFromError_(struct String msg_, struct IntIntTuple2 arg_113);

struct StringList* goChildren_(struct String eol_1, struct DumpTree_List* children_2, struct StringList* acc_23);

struct StringList* goNext_(struct String eol_2, struct DumpTree_List* next_2, struct StringList* acc_24);

struct StringList* go_35(struct String eol_, struct DumpTree_ node_1, struct StringList* acc_22);

struct String dumpTreeToString_(struct DumpTree_ node_);

int fun_9(void* env_3, int arg_14, int arg_15);

struct IntStringTuple2ListIntIntIntFun2Tuple2IntTuple2;

struct NameCtx_ nameCtxEmpty_(int arg_114);

struct IntNameCtx_Tuple2;

struct IntNameCtx_Tuple2 nameCtxAdd_(struct String ident_, struct NameCtx_ arg_115);

struct String nameCtxFind_(int serial_2, struct NameCtx_ arg_116);

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

struct HPat_HExpr_HExpr_Tuple3 fun_3(struct IntIntTuple2IntIntTuple2Fun1 g_1, struct Ty_Ty_Fun1 f_12, struct HPat_HExpr_HExpr_Tuple3 arg_117);

struct HPat_HExpr_HExpr_Tuple3 fun_13(void* env_7, struct HPat_HExpr_HExpr_Tuple3 arg_28);

struct HExpr_ fun_14(void* env_8, struct HExpr_ arg_31);

struct HPat_ fun_15(void* env_9, struct HPat_ arg_34);

struct HExpr_ go_39(struct IntIntTuple2IntIntTuple2Fun1 g_1, struct Ty_Ty_Fun1 f_12, struct HExpr_ expr_5);

struct HExpr_ exprMap_(struct Ty_Ty_Fun1 f_12, struct IntIntTuple2IntIntTuple2Fun1 g_1, struct HExpr_ expr_4);

struct Ty_ exprToTy_(struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct HExpr_ expr_6);

struct IntIntTuple2 go_(int r_, struct String text_, int y_1, int x_2, int i_);

struct IntIntTuple2 locShift_(struct String text_, int l_, int r_, struct IntIntTuple2 arg_118);

int charIsIdent_(char c_);

int charIsOp_(char c_1);

int charIsPun_(char c_2);

int go_1(struct String s_, struct String prefix_, int pi_, int si_);

int strIsFollowedBy_(int i_1, struct String prefix_, struct String s_);

int strIsFollowedByRawQuotes_(int i_2, struct String s_1);

int scanError_(struct String arg_119, int i_3);

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

struct StringIntTuple2 tokCtxToTextIndex_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 arg_120);

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokCtxSkip_(int r_8, struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 arg_121);

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokCtxPush_(struct Token_ kind_, int r_9, struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 arg_122);

struct Token_IntIntTuple2Tuple2List* tokEof_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 arg_123);

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

int leadsExpr_1(struct Token_IntIntTuple2Tuple2List* tokens_1);

int leadsArg_1(struct Token_IntIntTuple2Tuple2List* tokens_2);

int leadsPat_1(struct Token_IntIntTuple2Tuple2List* tokens_3);

struct IntIntTuple2 nextLoc_1(struct Token_IntIntTuple2Tuple2List* tokens_4);

int nextInside_1(struct IntIntTuple2 baseLoc_, struct Token_IntIntTuple2Tuple2List* tokens_5);

struct StringIntIntTuple2Tuple2List* parseErrorCore_(struct String msg_3, struct IntIntTuple2 loc_29, struct StringIntIntTuple2Tuple2List* errors_1);

struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2;

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyError_1(struct String msg_5, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_124);

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatError_1(struct String msg_6, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_125);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseExprError_1(struct String msg_7, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_126);

struct StringIntIntTuple2Tuple2List* parseNewError_1(struct String msg_8, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_127);

struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_40(struct IntIntTuple2 baseLoc_1, struct ATy_List* acc_25, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_128);

struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyArgs_(struct IntIntTuple2 baseLoc_1, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_129);

struct StringATy_ListIntIntTuple2Tuple3;

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyAtom_(struct IntIntTuple2 baseLoc_2, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_130);

struct ATy_StringIntIntTuple2Tuple3;

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_55(struct IntIntTuple2 baseLoc_3, struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 arg_131);

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTySuffix_(struct IntIntTuple2 baseLoc_3, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_132);

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyPrefix_(struct IntIntTuple2 baseLoc_4, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_133);

struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_42(struct IntIntTuple2 baseLoc_5, struct ATy_List* acc_26, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_134);

struct ATy_ListIntIntTuple2Tuple2;

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyTuple_(struct IntIntTuple2 baseLoc_5, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_135);

struct ATy_ATy_IntIntTuple2Tuple3;

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyFun_(struct IntIntTuple2 baseLoc_6, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_136);

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTy_(struct IntIntTuple2 baseLoc_7, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_137);

struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_43(struct IntIntTuple2 baseLoc_8, struct AVariant_List* acc_27, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_138);

enum ATyDecl_Tag;

struct ATyDecl_;

struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyDeclUnion_(struct IntIntTuple2 baseLoc_8, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_139);

struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyDeclBody_(struct IntIntTuple2 baseLoc_9, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_140);

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatParenBody_(struct IntIntTuple2 baseLoc_10, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_141);

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_44(struct IntIntTuple2 baseLoc_11, struct APat_List* patAcc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_142);

struct APat_ListIntIntTuple2Tuple2;

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatListBody_(struct IntIntTuple2 baseLoc_11, struct IntIntTuple2 bracketLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_143);

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatAtom_(struct IntIntTuple2 baseLoc_12, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_144);

struct APat_StringIntIntTuple2Tuple3;

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatNav_(struct IntIntTuple2 baseLoc_13, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_145);

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_45(struct IntIntTuple2 argBaseLoc_, struct IntIntTuple2 baseLoc_14, struct APat_List* acc_28, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_146);

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatCallArgs_(struct IntIntTuple2 baseLoc_14, struct IntIntTuple2 calleeLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_147);

struct APat_APat_ListIntIntTuple2Tuple3;

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatCall_(struct IntIntTuple2 baseLoc_15, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_148);

struct APat_APat_IntIntTuple2Tuple3;

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatCons_(struct IntIntTuple2 baseLoc_16, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_149);

struct APat_ATy_IntIntTuple2Tuple3;

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatAnno_(struct IntIntTuple2 baseLoc_17, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_150);

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_46(struct IntIntTuple2 baseLoc_18, struct APat_List* acc_29, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_151);

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatTuple_(struct IntIntTuple2 baseLoc_18, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_152);

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatAs_(struct IntIntTuple2 baseLoc_19, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_153);

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatOr_(struct IntIntTuple2 baseLoc_20, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_154);

struct StringAPat_ListIntIntTuple2Tuple3;

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatLet_(struct IntIntTuple2 baseLoc_21, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_155);

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePat_(struct IntIntTuple2 baseLoc_22, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_156);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseRange_(struct IntIntTuple2 baseLoc_23, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_157);

struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseList_(struct IntIntTuple2 baseLoc_24, struct IntIntTuple2 bracketLoc_1, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_158);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseThenClause_(struct IntIntTuple2 baseLoc_25, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_159);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseElseClause_(struct IntIntTuple2 baseLoc_26, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_160);

struct AExpr_AExpr_AExpr_IntIntTuple2Tuple4;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseIf_(struct IntIntTuple2 ifLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_161);

struct APat_AExpr_AExpr_IntIntTuple2Tuple4;

struct AArm_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct AArm_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseMatchArm_(struct IntIntTuple2 matchLoc_, struct IntIntTuple2 armLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_162);

struct AArm_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct AArm_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_47(struct IntIntTuple2 matchLoc_1, struct AArm_List* acc_30, struct IntIntTuple2 armLoc_2, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_163);

struct IntIntTuple2Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct AExpr_AArm_ListIntIntTuple2Tuple3;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseMatch_(struct IntIntTuple2 matchLoc_1, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_164);

struct APat_ListAExpr_IntIntTuple2Tuple3;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseFun_(struct IntIntTuple2 baseLoc_27, struct IntIntTuple2 funLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_165);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseParenBody_(struct IntIntTuple2 baseLoc_28, struct IntIntTuple2 parenLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_166);

struct Token_IntIntTuple2Tuple2List* parseAccessModifier_1(struct Token_IntIntTuple2Tuple2List* tokens_147);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseLet_(struct IntIntTuple2 letLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_167);

struct StringATy_IntIntTuple2Tuple3;

struct StringAVariant_ListIntIntTuple2Tuple3;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyDecl_(struct IntIntTuple2 typeLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_168);

struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_48(struct StringList* acc_31, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_169);

struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePath_(struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_170);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseOpen_(struct IntIntTuple2 openLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_171);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseAtom_(struct IntIntTuple2 baseLoc_30, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_172);

struct AExpr_AExpr_IntIntTuple2Tuple3;

struct AExpr_StringIntIntTuple2Tuple3;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_49(struct IntIntTuple2 baseLoc_31, struct AExpr_ acc_32, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_173);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseSuffix_(struct IntIntTuple2 baseLoc_31, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_174);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_50(struct IntIntTuple2 argBaseLoc_1, struct IntIntTuple2 calleeLoc_3, struct IntIntTuple2 baseLoc_32, struct AExpr_ callee_8, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_175);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseApp_(struct IntIntTuple2 baseLoc_32, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_176);

enum UniOp_Tag;

struct UniOp_;

struct UniOp_AExpr_IntIntTuple2Tuple3;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePrefix_(struct IntIntTuple2 baseLoc_33, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_177);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseNextLevelOp_(struct OpLevel_ level_1, struct IntIntTuple2 baseLoc_34, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_178);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 nextL_(struct IntIntTuple2 baseLoc_35, struct OpLevel_ level_2, struct AExpr_ expr_12, struct Op_ op_, struct IntIntTuple2 opLoc_2, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_179);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 nextR_(struct IntIntTuple2 baseLoc_35, struct OpLevel_ level_2, struct AExpr_ expr_14, struct Op_ op_1, struct IntIntTuple2 opLoc_3, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_180);

struct OpLevel_Token_IntIntTuple2Tuple2ListTuple2;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseOps_(struct OpLevel_ level_2, struct IntIntTuple2 baseLoc_35, struct AExpr_ first_3, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_181);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseOp_(struct OpLevel_ level_3, struct IntIntTuple2 baseLoc_36, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_182);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTupleItem_(struct IntIntTuple2 baseLoc_37, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_183);

struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_51(struct IntIntTuple2 baseLoc_38, struct AExpr_List* acc_33, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_184);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTuple_(struct IntIntTuple2 baseLoc_38, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_185);

struct AExpr_ATy_IntIntTuple2Tuple3;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseAnno_(struct IntIntTuple2 baseLoc_39, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_186);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseExpr_(struct IntIntTuple2 baseLoc_40, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_187);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseStmt_(struct IntIntTuple2 baseLoc_41, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_188);

struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_52(struct IntIntTuple2 baseLoc_42, struct AExpr_List* acc_34, struct IntIntTuple2 alignLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_189);

struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseStmts_(struct IntIntTuple2 baseLoc_42, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_190);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseSemi_(struct IntIntTuple2 baseLoc_43, struct IntIntTuple2 mainLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_191);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTopLevel_(struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_192);

struct AExpr_StringIntIntTuple2Tuple2ListTuple2;

struct AExpr_StringIntIntTuple2Tuple2ListTuple2 parse_(struct Token_IntIntTuple2Tuple2List* tokens_251);

struct HPrim_ opToPrim_(struct Op_ op_2);

struct APat_ go_53(struct IntIntTuple2 loc_68, struct APat_List* pats_5);

struct APat_ desugarListLitPat_(struct APat_List* pats_4, struct IntIntTuple2 loc_68);

struct AExpr_ go_54(struct IntIntTuple2 loc_69, struct AExpr_List* items_10);

struct AExpr_ desugarListLitExpr_(struct AExpr_List* items_9, struct IntIntTuple2 loc_69);

struct AExpr_ desugarIf_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct AExpr_ cond_2, struct AExpr_ body_15, struct AExpr_ alt_2, struct IntIntTuple2 loc_70);

struct AExpr_ desugarFun_(struct APat_List* pats_6, struct AExpr_ body_16, struct IntIntTuple2 loc_71);

struct AExpr_ desugarUniNeg_(struct AExpr_ arg_4, struct IntIntTuple2 loc_72);

struct AExpr_ desugarBinNe_(struct Lit_ litFalse_, struct AExpr_ l_19, struct AExpr_ r_33, struct IntIntTuple2 loc_73);

struct AExpr_ desugarBinLe_(struct Lit_ litFalse_, struct AExpr_ l_20, struct AExpr_ r_34, struct IntIntTuple2 loc_74);

struct AExpr_ desugarBinGt_(struct AExpr_ l_21, struct AExpr_ r_35, struct IntIntTuple2 loc_75);

struct AExpr_ desugarBinGe_(struct Lit_ litFalse_, struct AExpr_ l_22, struct AExpr_ r_36, struct IntIntTuple2 loc_76);

struct AExpr_ desugarBinAnd_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct AExpr_ l_23, struct AExpr_ r_37, struct IntIntTuple2 loc_77);

struct AExpr_ desugarBinOr_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct AExpr_ l_24, struct AExpr_ r_38, struct IntIntTuple2 loc_78);

struct AExpr_ desugarBinPipe_(struct AExpr_ l_25, struct AExpr_ r_39, struct IntIntTuple2 loc_79);

struct BoolAExpr_Tuple2;

struct BoolAExpr_Tuple2 tryDesugarIndexRange_(struct AExpr_ expr_19, struct IntIntTuple2 loc_80);

enum ALet_Tag;

struct ALet_;

struct StringAPat_ListAExpr_AExpr_IntIntTuple2Tuple5;

struct ALet_ desugarLet_(struct APat_ pat_24, struct AExpr_ body_17, struct AExpr_ next_13, struct IntIntTuple2 loc_81);

struct Ty_NameCtx_Tuple2 fun_16(void* env_10, struct ATy_NameCtx_Tuple2 arg_37);

struct Ty_NameCtx_Tuple2 fun_17(void* env_11, struct ATy_NameCtx_Tuple2 arg_38);

struct Ty_NameCtx_Tuple2 onTy_(struct ATy_NameCtx_Tuple2 arg_193);

struct Ty_Tuple1;

struct HPat_NameCtx_Tuple2 fun_18(void* env_12, struct APat_NameCtx_Tuple2 arg_39);

struct HPat_NameCtx_Tuple2 fun_19(void* env_13, struct APat_NameCtx_Tuple2 arg_41);

struct HPat_NameCtx_Tuple2 onPat_(struct Ty_ noTy_, struct APat_NameCtx_Tuple2 arg_194);

struct HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2 onArm_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, struct AArm_NameCtx_Tuple2 arg_195);

struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8;

struct HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2 fun_20(void* env_14, struct AArm_NameCtx_Tuple2 arg_43);

struct HExpr_NameCtx_Tuple2 fun_21(void* env_15, struct AExpr_NameCtx_Tuple2 arg_52);

struct HExpr_NameCtx_Tuple2 fun_22(void* env_16, struct AExpr_NameCtx_Tuple2 arg_61);

struct HPat_NameCtx_Tuple2 fun_23(void* env_17, struct APat_NameCtx_Tuple2 arg_70);

struct BoolTy_NameCtx_Tuple3;

struct StringIntBoolTy_Tuple4NameCtx_Tuple2 onVariant_(struct Ty_ tyUnit_, struct AVariant_NameCtx_Tuple2 arg_196);

struct StringIntBoolTy_Tuple4NameCtx_Tuple2 fun_24(void* env_18, struct AVariant_NameCtx_Tuple2 arg_72);

struct StringStringIntBoolTy_Tuple4ListIntIntTuple2Tuple3;

struct HExpr_NameCtx_Tuple2 onExpr_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, struct AExpr_NameCtx_Tuple2 arg_197);

struct HExpr_NameCtx_Tuple2 astToHir_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, struct AExpr_NameCtx_Tuple2 arg_198);

struct String litToString_(struct Lit_ lit_5);

struct String tokenToString_(struct Token_ token_12);

struct DumpTree_ fun_25(void* env_19, struct ATy_ arg_74);

struct DumpTree_ fun_26(void* env_20, struct ATy_ arg_75);

struct DumpTree_ fun_27(void* env_21, struct ATy_ arg_76);

struct DumpTree_ atDump_(struct ATy_ ty_43);

struct DumpTree_ fun_28(void* env_22, struct APat_ arg_77);

struct DumpTree_ fun_29(void* env_23, struct APat_ arg_78);

struct DumpTree_ fun_30(void* env_24, struct APat_ arg_79);

struct DumpTree_ fun_31(void* env_25, struct APat_ arg_80);

struct DumpTree_ apDump_(struct APat_ pat_10);

struct DumpTree_ fun_32(void* env_26, struct AExpr_ arg_81);

struct DumpTree_ dumpArm_(struct AArm_ arg_199);

struct DumpTree_ fun_33(void* env_27, struct AArm_ arg_82);

struct DumpTree_ fun_34(void* env_28, struct APat_ arg_83);

struct DumpTree_ fun_35(void* env_29, struct AExpr_ arg_84);

struct DumpTree_ fun_36(void* env_30, struct AExpr_ arg_85);

struct DumpTree_ fun_37(void* env_31, struct AExpr_ arg_86);

struct DumpTree_ dumpVariant_(struct AVariant_ arg_200);

struct DumpTree_ fun_38(void* env_32, struct AVariant_ arg_87);

struct DumpTree_ fun_39(void* env_33, struct String arg_88);

struct DumpTree_ axDump_(struct AExpr_ expr_7);

struct String findIdent_(struct NameCtx_ nameCtx_, int serial_9);

struct NameCtx_Tuple1;

struct DumpTree_ fun_40(void* env_34, struct HExpr_ arg_89);

struct DumpTree_ fun_41(void* env_35, struct String arg_91);

struct DumpTree_ hxDump_(struct NameCtx_ nameCtx_, struct HExpr_ expr_8);

int fun_4(struct Token_IntIntTuple2Tuple2 arg_201);

int fun_42(void* env_36, struct Token_IntIntTuple2Tuple2 arg_92);

int fun_5(struct StringIntIntTuple2Tuple2 arg_202);

int fun_43(void* env_37, struct StringIntIntTuple2Tuple2 arg_93);

struct StringStringFun1;

int doFile_(struct StringStringFun1 fileReadAllText_1, struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, char charNull_, struct String filePath_);

int doSelf_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, char charNull_, struct StringStringFun1 fileReadAllText_1);

struct String fileReadAllText_(struct String fileName_);

struct String fun_44(void* env_38, struct String arg_94);

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
    int call_3 = 0;
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
    int call_4 = 0;
    exit(1);
    return ((struct IntHPat_NameCtx_Tuple2Fun1){});
}

struct IntIntTuple2HPat_NameCtx_Tuple2Fun1 {
    struct HPat_NameCtx_Tuple2(*fun)(void*, struct IntIntTuple2);
    void* env;
};

struct IntIntTuple2HPat_NameCtx_Tuple2Fun1 failwithf_1(struct String str_1) {
    printf("FATAL ERROR: %s\n", str_1.str);
    int call_5 = 0;
    exit(1);
    return ((struct IntIntTuple2HPat_NameCtx_Tuple2Fun1){});
}

struct IntStringFun1 {
    struct String(*fun)(void*, int);
    void* env;
};

struct IntStringFun1 failwithf_4(struct String str_1) {
    printf("FATAL ERROR: %s\n", str_1.str);
    int call_6 = 0;
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

int go_79(int len_, struct StringList* xs_2) {
    int match_4;
    if ((!((!(xs_2))))) goto next_14;
    match_4 = len_;
    goto end_match_13;
next_14:;
    if ((!(xs_2))) goto next_15;
    struct StringList* xs_3 = xs_2->tail;
    int call_7 = go_79((len_ + 1), xs_3);
    match_4 = call_7;
    goto end_match_13;
next_15:;
    exit(1);
end_match_13:;
    return match_4;
}

int listLength_1(struct StringList* xs_1) {
    int call_8 = go_79(0, xs_1);
    return call_8;
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

struct Token_IntIntTuple2Tuple2List* go_78(struct Token_IntIntTuple2Tuple2List* acc_5, struct Token_IntIntTuple2Tuple2List* xs_5) {
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
    struct Token_IntIntTuple2Tuple2List* call_9 = go_78(list_1, xs_6);
    match_5 = call_9;
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

struct ATy_List* go_77(struct ATy_List* acc_5, struct ATy_List* xs_5) {
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
    struct ATy_List* call_10 = go_77(list_2, xs_6);
    match_6 = call_10;
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

struct AVariant_List* go_76(struct AVariant_List* acc_5, struct AVariant_List* xs_5) {
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
    struct AVariant_List* call_11 = go_76(list_3, xs_6);
    match_7 = call_11;
    goto end_match_22;
next_24:;
    exit(1);
end_match_22:;
    return match_7;
}

struct APat_List* go_75(struct APat_List* acc_5, struct APat_List* xs_5) {
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
    struct APat_List* call_12 = go_75(list_4, xs_6);
    match_8 = call_12;
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

struct AArm_List* go_74(struct AArm_List* acc_5, struct AArm_List* xs_5) {
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
    struct AArm_List* call_13 = go_74(list_5, xs_6);
    match_9 = call_13;
    goto end_match_28;
next_30:;
    exit(1);
end_match_28:;
    return match_9;
}

struct StringList* go_73(struct StringList* acc_5, struct StringList* xs_5) {
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
    struct StringList* call_14 = go_73(list_6, xs_6);
    match_10 = call_14;
    goto end_match_31;
next_33:;
    exit(1);
end_match_31:;
    return match_10;
}

struct AExpr_List* go_72(struct AExpr_List* acc_5, struct AExpr_List* xs_5) {
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
    struct AExpr_List* call_15 = go_72(list_7, xs_6);
    match_11 = call_15;
    goto end_match_34;
next_36:;
    exit(1);
end_match_34:;
    return match_11;
}

struct DumpTree_List* go_86(struct DumpTree_List* acc_5, struct DumpTree_List* xs_5) {
    struct DumpTree_List* match_12;
    if ((!((!(xs_5))))) goto next_38;
    match_12 = acc_5;
    goto end_match_37;
next_38:;
    if ((!(xs_5))) goto next_39;
    struct DumpTree_ x_3 = xs_5->head;
    struct DumpTree_List* xs_6 = xs_5->tail;
    struct DumpTree_List* list_8 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_8->head = x_3;
    list_8->tail = acc_5;
    struct DumpTree_List* call_16 = go_86(list_8, xs_6);
    match_12 = call_16;
    goto end_match_37;
next_39:;
    exit(1);
end_match_37:;
    return match_12;
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

struct Ty_List* go_85(struct Ty_List* acc_5, struct Ty_List* xs_5) {
    struct Ty_List* match_13;
    if ((!((!(xs_5))))) goto next_41;
    match_13 = acc_5;
    goto end_match_40;
next_41:;
    if ((!(xs_5))) goto next_42;
    struct Ty_ x_3 = xs_5->head;
    struct Ty_List* xs_6 = xs_5->tail;
    struct Ty_List* list_9 = (struct Ty_List*)malloc(sizeof(struct Ty_List));
    list_9->head = x_3;
    list_9->tail = acc_5;
    struct Ty_List* call_17 = go_85(list_9, xs_6);
    match_13 = call_17;
    goto end_match_40;
next_42:;
    exit(1);
end_match_40:;
    return match_13;
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

struct HPat_HExpr_HExpr_Tuple3 {
    struct HPat_ t0;
    struct HExpr_ t1;
    struct HExpr_ t2;
};

struct HPat_HExpr_HExpr_Tuple3List {
    struct HPat_HExpr_HExpr_Tuple3 head;
    struct HPat_HExpr_HExpr_Tuple3List* tail;
};

struct HPat_HExpr_HExpr_Tuple3List* go_84(struct HPat_HExpr_HExpr_Tuple3List* acc_5, struct HPat_HExpr_HExpr_Tuple3List* xs_5) {
    struct HPat_HExpr_HExpr_Tuple3List* match_14;
    if ((!((!(xs_5))))) goto next_44;
    match_14 = acc_5;
    goto end_match_43;
next_44:;
    if ((!(xs_5))) goto next_45;
    struct HPat_HExpr_HExpr_Tuple3 x_3 = xs_5->head;
    struct HPat_HExpr_HExpr_Tuple3List* xs_6 = xs_5->tail;
    struct HPat_HExpr_HExpr_Tuple3List* list_10 = (struct HPat_HExpr_HExpr_Tuple3List*)malloc(sizeof(struct HPat_HExpr_HExpr_Tuple3List));
    list_10->head = x_3;
    list_10->tail = acc_5;
    struct HPat_HExpr_HExpr_Tuple3List* call_18 = go_84(list_10, xs_6);
    match_14 = call_18;
    goto end_match_43;
next_45:;
    exit(1);
end_match_43:;
    return match_14;
}

struct HExpr_List {
    struct HExpr_ head;
    struct HExpr_List* tail;
};

struct HExpr_List* go_83(struct HExpr_List* acc_5, struct HExpr_List* xs_5) {
    struct HExpr_List* match_15;
    if ((!((!(xs_5))))) goto next_47;
    match_15 = acc_5;
    goto end_match_46;
next_47:;
    if ((!(xs_5))) goto next_48;
    struct HExpr_ x_3 = xs_5->head;
    struct HExpr_List* xs_6 = xs_5->tail;
    struct HExpr_List* list_11 = (struct HExpr_List*)malloc(sizeof(struct HExpr_List));
    list_11->head = x_3;
    list_11->tail = acc_5;
    struct HExpr_List* call_19 = go_83(list_11, xs_6);
    match_15 = call_19;
    goto end_match_46;
next_48:;
    exit(1);
end_match_46:;
    return match_15;
}

struct HPat_List {
    struct HPat_ head;
    struct HPat_List* tail;
};

struct HPat_List* go_82(struct HPat_List* acc_5, struct HPat_List* xs_5) {
    struct HPat_List* match_16;
    if ((!((!(xs_5))))) goto next_50;
    match_16 = acc_5;
    goto end_match_49;
next_50:;
    if ((!(xs_5))) goto next_51;
    struct HPat_ x_3 = xs_5->head;
    struct HPat_List* xs_6 = xs_5->tail;
    struct HPat_List* list_12 = (struct HPat_List*)malloc(sizeof(struct HPat_List));
    list_12->head = x_3;
    list_12->tail = acc_5;
    struct HPat_List* call_20 = go_82(list_12, xs_6);
    match_16 = call_20;
    goto end_match_49;
next_51:;
    exit(1);
end_match_49:;
    return match_16;
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

struct StringIntBoolTy_Tuple4List* go_81(struct StringIntBoolTy_Tuple4List* acc_5, struct StringIntBoolTy_Tuple4List* xs_5) {
    struct StringIntBoolTy_Tuple4List* match_17;
    if ((!((!(xs_5))))) goto next_53;
    match_17 = acc_5;
    goto end_match_52;
next_53:;
    if ((!(xs_5))) goto next_54;
    struct StringIntBoolTy_Tuple4 x_3 = xs_5->head;
    struct StringIntBoolTy_Tuple4List* xs_6 = xs_5->tail;
    struct StringIntBoolTy_Tuple4List* list_13 = (struct StringIntBoolTy_Tuple4List*)malloc(sizeof(struct StringIntBoolTy_Tuple4List));
    list_13->head = x_3;
    list_13->tail = acc_5;
    struct StringIntBoolTy_Tuple4List* call_21 = go_81(list_13, xs_6);
    match_17 = call_21;
    goto end_match_52;
next_54:;
    exit(1);
end_match_52:;
    return match_17;
}

struct Token_IntIntTuple2Tuple2List* listRev_7(struct Token_IntIntTuple2Tuple2List* xs_4) {
    struct Token_IntIntTuple2Tuple2List* call_22 = go_78(NULL, xs_4);
    return call_22;
}

struct ATy_List* listRev_6(struct ATy_List* xs_4) {
    struct ATy_List* call_23 = go_77(NULL, xs_4);
    return call_23;
}

struct AVariant_List* listRev_5(struct AVariant_List* xs_4) {
    struct AVariant_List* call_24 = go_76(NULL, xs_4);
    return call_24;
}

struct APat_List* listRev_4(struct APat_List* xs_4) {
    struct APat_List* call_25 = go_75(NULL, xs_4);
    return call_25;
}

struct AArm_List* listRev_3(struct AArm_List* xs_4) {
    struct AArm_List* call_26 = go_74(NULL, xs_4);
    return call_26;
}

struct StringList* listRev_2(struct StringList* xs_4) {
    struct StringList* call_27 = go_73(NULL, xs_4);
    return call_27;
}

struct AExpr_List* listRev_1(struct AExpr_List* xs_4) {
    struct AExpr_List* call_28 = go_72(NULL, xs_4);
    return call_28;
}

struct DumpTree_List* listRev_13(struct DumpTree_List* xs_4) {
    struct DumpTree_List* call_29 = go_86(NULL, xs_4);
    return call_29;
}

struct Ty_List* listRev_12(struct Ty_List* xs_4) {
    struct Ty_List* call_30 = go_85(NULL, xs_4);
    return call_30;
}

struct HPat_HExpr_HExpr_Tuple3List* listRev_11(struct HPat_HExpr_HExpr_Tuple3List* xs_4) {
    struct HPat_HExpr_HExpr_Tuple3List* call_31 = go_84(NULL, xs_4);
    return call_31;
}

struct HExpr_List* listRev_10(struct HExpr_List* xs_4) {
    struct HExpr_List* call_32 = go_83(NULL, xs_4);
    return call_32;
}

struct HPat_List* listRev_9(struct HPat_List* xs_4) {
    struct HPat_List* call_33 = go_82(NULL, xs_4);
    return call_33;
}

struct StringIntBoolTy_Tuple4List* listRev_8(struct StringIntBoolTy_Tuple4List* xs_4) {
    struct StringIntBoolTy_Tuple4List* call_34 = go_81(NULL, xs_4);
    return call_34;
}

struct Token_IntIntTuple2Tuple2UnitFun1 {
    int(*fun)(void*, struct Token_IntIntTuple2Tuple2);
    void* env;
};

int listIter_2(struct Token_IntIntTuple2Tuple2UnitFun1 f_, struct Token_IntIntTuple2Tuple2List* xs_7) {
    int match_18;
    if ((!((!(xs_7))))) goto next_56;
    match_18 = 0;
    goto end_match_55;
next_56:;
    if ((!(xs_7))) goto next_57;
    struct Token_IntIntTuple2Tuple2 x_4 = xs_7->head;
    struct Token_IntIntTuple2Tuple2List* xs_8 = xs_7->tail;
    int app_1 = f_.fun(f_.env, x_4);
    int call_35 = listIter_2(f_, xs_8);
    match_18 = 0;
    goto end_match_55;
next_57:;
    exit(1);
end_match_55:;
    return 0;
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

int listIter_1(struct StringIntIntTuple2Tuple2UnitFun1 f_, struct StringIntIntTuple2Tuple2List* xs_7) {
    int match_19;
    if ((!((!(xs_7))))) goto next_59;
    match_19 = 0;
    goto end_match_58;
next_59:;
    if ((!(xs_7))) goto next_60;
    struct StringIntIntTuple2Tuple2 x_4 = xs_7->head;
    struct StringIntIntTuple2Tuple2List* xs_8 = xs_7->tail;
    int app_2 = f_.fun(f_.env, x_4);
    int call_36 = listIter_1(f_, xs_8);
    match_19 = 0;
    goto end_match_58;
next_60:;
    exit(1);
end_match_58:;
    return 0;
}

struct HExpr_Ty_Fun1 {
    struct Ty_(*fun)(void*, struct HExpr_);
    void* env;
};

struct Ty_List* go_71(struct HExpr_Ty_Fun1 f_1, struct Ty_List* acc_6, struct HExpr_List* xs_10) {
    struct Ty_List* match_20;
    if ((!((!(xs_10))))) goto next_62;
    struct Ty_List* call_37 = listRev_12(acc_6);
    match_20 = call_37;
    goto end_match_61;
next_62:;
    if ((!(xs_10))) goto next_63;
    struct HExpr_ x_5 = xs_10->head;
    struct HExpr_List* xs_11 = xs_10->tail;
    struct Ty_ app_3 = f_1.fun(f_1.env, x_5);
    struct Ty_List* list_14 = (struct Ty_List*)malloc(sizeof(struct Ty_List));
    list_14->head = app_3;
    list_14->tail = acc_6;
    struct Ty_List* call_38 = go_71(f_1, list_14, xs_11);
    match_20 = call_38;
    goto end_match_61;
next_63:;
    exit(1);
end_match_61:;
    return match_20;
}

struct HPat_HExpr_HExpr_Tuple3HPat_HExpr_HExpr_Tuple3Fun1 {
    struct HPat_HExpr_HExpr_Tuple3(*fun)(void*, struct HPat_HExpr_HExpr_Tuple3);
    void* env;
};

struct HPat_HExpr_HExpr_Tuple3List* go_70(struct HPat_HExpr_HExpr_Tuple3HPat_HExpr_HExpr_Tuple3Fun1 f_1, struct HPat_HExpr_HExpr_Tuple3List* acc_6, struct HPat_HExpr_HExpr_Tuple3List* xs_10) {
    struct HPat_HExpr_HExpr_Tuple3List* match_21;
    if ((!((!(xs_10))))) goto next_65;
    struct HPat_HExpr_HExpr_Tuple3List* call_39 = listRev_11(acc_6);
    match_21 = call_39;
    goto end_match_64;
next_65:;
    if ((!(xs_10))) goto next_66;
    struct HPat_HExpr_HExpr_Tuple3 x_5 = xs_10->head;
    struct HPat_HExpr_HExpr_Tuple3List* xs_11 = xs_10->tail;
    struct HPat_HExpr_HExpr_Tuple3 app_4 = f_1.fun(f_1.env, x_5);
    struct HPat_HExpr_HExpr_Tuple3List* list_15 = (struct HPat_HExpr_HExpr_Tuple3List*)malloc(sizeof(struct HPat_HExpr_HExpr_Tuple3List));
    list_15->head = app_4;
    list_15->tail = acc_6;
    struct HPat_HExpr_HExpr_Tuple3List* call_40 = go_70(f_1, list_15, xs_11);
    match_21 = call_40;
    goto end_match_64;
next_66:;
    exit(1);
end_match_64:;
    return match_21;
}

struct HExpr_HExpr_Fun1 {
    struct HExpr_(*fun)(void*, struct HExpr_);
    void* env;
};

struct HExpr_List* go_69(struct HExpr_HExpr_Fun1 f_1, struct HExpr_List* acc_6, struct HExpr_List* xs_10) {
    struct HExpr_List* match_22;
    if ((!((!(xs_10))))) goto next_68;
    struct HExpr_List* call_41 = listRev_10(acc_6);
    match_22 = call_41;
    goto end_match_67;
next_68:;
    if ((!(xs_10))) goto next_69;
    struct HExpr_ x_5 = xs_10->head;
    struct HExpr_List* xs_11 = xs_10->tail;
    struct HExpr_ app_5 = f_1.fun(f_1.env, x_5);
    struct HExpr_List* list_16 = (struct HExpr_List*)malloc(sizeof(struct HExpr_List));
    list_16->head = app_5;
    list_16->tail = acc_6;
    struct HExpr_List* call_42 = go_69(f_1, list_16, xs_11);
    match_22 = call_42;
    goto end_match_67;
next_69:;
    exit(1);
end_match_67:;
    return match_22;
}

struct HPat_HPat_Fun1 {
    struct HPat_(*fun)(void*, struct HPat_);
    void* env;
};

struct HPat_List* go_68(struct HPat_HPat_Fun1 f_1, struct HPat_List* acc_6, struct HPat_List* xs_10) {
    struct HPat_List* match_23;
    if ((!((!(xs_10))))) goto next_71;
    struct HPat_List* call_43 = listRev_9(acc_6);
    match_23 = call_43;
    goto end_match_70;
next_71:;
    if ((!(xs_10))) goto next_72;
    struct HPat_ x_5 = xs_10->head;
    struct HPat_List* xs_11 = xs_10->tail;
    struct HPat_ app_6 = f_1.fun(f_1.env, x_5);
    struct HPat_List* list_17 = (struct HPat_List*)malloc(sizeof(struct HPat_List));
    list_17->head = app_6;
    list_17->tail = acc_6;
    struct HPat_List* call_44 = go_68(f_1, list_17, xs_11);
    match_23 = call_44;
    goto end_match_70;
next_72:;
    exit(1);
end_match_70:;
    return match_23;
}

struct ATy_DumpTree_Fun1 {
    struct DumpTree_(*fun)(void*, struct ATy_);
    void* env;
};

struct DumpTree_List* go_67(struct ATy_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct ATy_List* xs_10) {
    struct DumpTree_List* match_24;
    if ((!((!(xs_10))))) goto next_74;
    struct DumpTree_List* call_45 = listRev_13(acc_6);
    match_24 = call_45;
    goto end_match_73;
next_74:;
    if ((!(xs_10))) goto next_75;
    struct ATy_ x_5 = xs_10->head;
    struct ATy_List* xs_11 = xs_10->tail;
    struct DumpTree_ app_7 = f_1.fun(f_1.env, x_5);
    struct DumpTree_List* list_18 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_18->head = app_7;
    list_18->tail = acc_6;
    struct DumpTree_List* call_46 = go_67(f_1, list_18, xs_11);
    match_24 = call_46;
    goto end_match_73;
next_75:;
    exit(1);
end_match_73:;
    return match_24;
}

struct AArm_DumpTree_Fun1 {
    struct DumpTree_(*fun)(void*, struct AArm_);
    void* env;
};

struct DumpTree_List* go_66(struct AArm_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct AArm_List* xs_10) {
    struct DumpTree_List* match_25;
    if ((!((!(xs_10))))) goto next_77;
    struct DumpTree_List* call_47 = listRev_13(acc_6);
    match_25 = call_47;
    goto end_match_76;
next_77:;
    if ((!(xs_10))) goto next_78;
    struct AArm_ x_5 = xs_10->head;
    struct AArm_List* xs_11 = xs_10->tail;
    struct DumpTree_ app_8 = f_1.fun(f_1.env, x_5);
    struct DumpTree_List* list_19 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_19->head = app_8;
    list_19->tail = acc_6;
    struct DumpTree_List* call_48 = go_66(f_1, list_19, xs_11);
    match_25 = call_48;
    goto end_match_76;
next_78:;
    exit(1);
end_match_76:;
    return match_25;
}

struct APat_DumpTree_Fun1 {
    struct DumpTree_(*fun)(void*, struct APat_);
    void* env;
};

struct DumpTree_List* go_65(struct APat_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct APat_List* xs_10) {
    struct DumpTree_List* match_26;
    if ((!((!(xs_10))))) goto next_80;
    struct DumpTree_List* call_49 = listRev_13(acc_6);
    match_26 = call_49;
    goto end_match_79;
next_80:;
    if ((!(xs_10))) goto next_81;
    struct APat_ x_5 = xs_10->head;
    struct APat_List* xs_11 = xs_10->tail;
    struct DumpTree_ app_9 = f_1.fun(f_1.env, x_5);
    struct DumpTree_List* list_20 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_20->head = app_9;
    list_20->tail = acc_6;
    struct DumpTree_List* call_50 = go_65(f_1, list_20, xs_11);
    match_26 = call_50;
    goto end_match_79;
next_81:;
    exit(1);
end_match_79:;
    return match_26;
}

struct AExpr_DumpTree_Fun1 {
    struct DumpTree_(*fun)(void*, struct AExpr_);
    void* env;
};

struct DumpTree_List* go_64(struct AExpr_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct AExpr_List* xs_10) {
    struct DumpTree_List* match_27;
    if ((!((!(xs_10))))) goto next_83;
    struct DumpTree_List* call_51 = listRev_13(acc_6);
    match_27 = call_51;
    goto end_match_82;
next_83:;
    if ((!(xs_10))) goto next_84;
    struct AExpr_ x_5 = xs_10->head;
    struct AExpr_List* xs_11 = xs_10->tail;
    struct DumpTree_ app_10 = f_1.fun(f_1.env, x_5);
    struct DumpTree_List* list_21 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_21->head = app_10;
    list_21->tail = acc_6;
    struct DumpTree_List* call_52 = go_64(f_1, list_21, xs_11);
    match_27 = call_52;
    goto end_match_82;
next_84:;
    exit(1);
end_match_82:;
    return match_27;
}

struct AVariant_DumpTree_Fun1 {
    struct DumpTree_(*fun)(void*, struct AVariant_);
    void* env;
};

struct DumpTree_List* go_63(struct AVariant_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct AVariant_List* xs_10) {
    struct DumpTree_List* match_28;
    if ((!((!(xs_10))))) goto next_86;
    struct DumpTree_List* call_53 = listRev_13(acc_6);
    match_28 = call_53;
    goto end_match_85;
next_86:;
    if ((!(xs_10))) goto next_87;
    struct AVariant_ x_5 = xs_10->head;
    struct AVariant_List* xs_11 = xs_10->tail;
    struct DumpTree_ app_11 = f_1.fun(f_1.env, x_5);
    struct DumpTree_List* list_22 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_22->head = app_11;
    list_22->tail = acc_6;
    struct DumpTree_List* call_54 = go_63(f_1, list_22, xs_11);
    match_28 = call_54;
    goto end_match_85;
next_87:;
    exit(1);
end_match_85:;
    return match_28;
}

struct HExpr_DumpTree_Fun1 {
    struct DumpTree_(*fun)(void*, struct HExpr_);
    void* env;
};

struct DumpTree_List* go_62(struct HExpr_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct HExpr_List* xs_10) {
    struct DumpTree_List* match_29;
    if ((!((!(xs_10))))) goto next_89;
    struct DumpTree_List* call_55 = listRev_13(acc_6);
    match_29 = call_55;
    goto end_match_88;
next_89:;
    if ((!(xs_10))) goto next_90;
    struct HExpr_ x_5 = xs_10->head;
    struct HExpr_List* xs_11 = xs_10->tail;
    struct DumpTree_ app_12 = f_1.fun(f_1.env, x_5);
    struct DumpTree_List* list_23 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_23->head = app_12;
    list_23->tail = acc_6;
    struct DumpTree_List* call_56 = go_62(f_1, list_23, xs_11);
    match_29 = call_56;
    goto end_match_88;
next_90:;
    exit(1);
end_match_88:;
    return match_29;
}

struct StringDumpTree_Fun1 {
    struct DumpTree_(*fun)(void*, struct String);
    void* env;
};

struct DumpTree_List* go_61(struct StringDumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct StringList* xs_10) {
    struct DumpTree_List* match_30;
    if ((!((!(xs_10))))) goto next_92;
    struct DumpTree_List* call_57 = listRev_13(acc_6);
    match_30 = call_57;
    goto end_match_91;
next_92:;
    if ((!(xs_10))) goto next_93;
    struct String x_5 = xs_10->head;
    struct StringList* xs_11 = xs_10->tail;
    struct DumpTree_ app_13 = f_1.fun(f_1.env, x_5);
    struct DumpTree_List* list_24 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_24->head = app_13;
    list_24->tail = acc_6;
    struct DumpTree_List* call_58 = go_61(f_1, list_24, xs_11);
    match_30 = call_58;
    goto end_match_91;
next_93:;
    exit(1);
end_match_91:;
    return match_30;
}

struct Ty_List* listMap_11(struct HExpr_Ty_Fun1 f_1, struct HExpr_List* xs_9) {
    struct Ty_List* call_59 = go_71(f_1, NULL, xs_9);
    return call_59;
}

struct HPat_HExpr_HExpr_Tuple3List* listMap_10(struct HPat_HExpr_HExpr_Tuple3HPat_HExpr_HExpr_Tuple3Fun1 f_1, struct HPat_HExpr_HExpr_Tuple3List* xs_9) {
    struct HPat_HExpr_HExpr_Tuple3List* call_60 = go_70(f_1, NULL, xs_9);
    return call_60;
}

struct HExpr_List* listMap_9(struct HExpr_HExpr_Fun1 f_1, struct HExpr_List* xs_9) {
    struct HExpr_List* call_61 = go_69(f_1, NULL, xs_9);
    return call_61;
}

struct HPat_List* listMap_8(struct HPat_HPat_Fun1 f_1, struct HPat_List* xs_9) {
    struct HPat_List* call_62 = go_68(f_1, NULL, xs_9);
    return call_62;
}

struct DumpTree_List* listMap_7(struct ATy_DumpTree_Fun1 f_1, struct ATy_List* xs_9) {
    struct DumpTree_List* call_63 = go_67(f_1, NULL, xs_9);
    return call_63;
}

struct DumpTree_List* listMap_6(struct AArm_DumpTree_Fun1 f_1, struct AArm_List* xs_9) {
    struct DumpTree_List* call_64 = go_66(f_1, NULL, xs_9);
    return call_64;
}

struct DumpTree_List* listMap_5(struct APat_DumpTree_Fun1 f_1, struct APat_List* xs_9) {
    struct DumpTree_List* call_65 = go_65(f_1, NULL, xs_9);
    return call_65;
}

struct DumpTree_List* listMap_4(struct AExpr_DumpTree_Fun1 f_1, struct AExpr_List* xs_9) {
    struct DumpTree_List* call_66 = go_64(f_1, NULL, xs_9);
    return call_66;
}

struct DumpTree_List* listMap_3(struct AVariant_DumpTree_Fun1 f_1, struct AVariant_List* xs_9) {
    struct DumpTree_List* call_67 = go_63(f_1, NULL, xs_9);
    return call_67;
}

struct DumpTree_List* listMap_2(struct HExpr_DumpTree_Fun1 f_1, struct HExpr_List* xs_9) {
    struct DumpTree_List* call_68 = go_62(f_1, NULL, xs_9);
    return call_68;
}

struct DumpTree_List* listMap_1(struct StringDumpTree_Fun1 f_1, struct StringList* xs_9) {
    struct DumpTree_List* call_69 = go_61(f_1, NULL, xs_9);
    return call_69;
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

struct Ty_ListNameCtx_Tuple2 go_60(struct ATy_NameCtx_Tuple2Ty_NameCtx_Tuple2Fun1 f_5, struct Ty_List* acc_17, struct ATy_ListNameCtx_Tuple2 arg_95) {
    struct ATy_List* xs_54 = arg_95.t0;
    struct NameCtx_ ctx_1 = arg_95.t1;
    struct Ty_ListNameCtx_Tuple2 match_31;
    if ((!((!(xs_54))))) goto next_95;
    struct Ty_List* call_70 = listRev_12(acc_17);
    struct Ty_ListNameCtx_Tuple2 tuple_;
    tuple_.t0 = call_70;
    tuple_.t1 = ctx_1;
    match_31 = tuple_;
    goto end_match_94;
next_95:;
    if ((!(xs_54))) goto next_96;
    struct ATy_ x_18 = xs_54->head;
    struct ATy_List* xs_55 = xs_54->tail;
    struct ATy_NameCtx_Tuple2 tuple_1;
    tuple_1.t0 = x_18;
    tuple_1.t1 = ctx_1;
    struct Ty_NameCtx_Tuple2 app_14 = f_5.fun(f_5.env, tuple_1);
    struct Ty_ y_5 = app_14.t0;
    struct NameCtx_ ctx_2 = app_14.t1;
    struct Ty_List* list_25 = (struct Ty_List*)malloc(sizeof(struct Ty_List));
    list_25->head = y_5;
    list_25->tail = acc_17;
    struct ATy_ListNameCtx_Tuple2 tuple_2;
    tuple_2.t0 = xs_55;
    tuple_2.t1 = ctx_2;
    struct Ty_ListNameCtx_Tuple2 call_71 = go_60(f_5, list_25, tuple_2);
    match_31 = call_71;
    goto end_match_94;
next_96:;
    exit(1);
end_match_94:;
    return match_31;
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

struct HPat_HExpr_HExpr_Tuple3ListNameCtx_Tuple2 go_59(struct AArm_NameCtx_Tuple2HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2Fun1 f_5, struct HPat_HExpr_HExpr_Tuple3List* acc_17, struct AArm_ListNameCtx_Tuple2 arg_96) {
    struct AArm_List* xs_54 = arg_96.t0;
    struct NameCtx_ ctx_1 = arg_96.t1;
    struct HPat_HExpr_HExpr_Tuple3ListNameCtx_Tuple2 match_32;
    if ((!((!(xs_54))))) goto next_98;
    struct HPat_HExpr_HExpr_Tuple3List* call_72 = listRev_11(acc_17);
    struct HPat_HExpr_HExpr_Tuple3ListNameCtx_Tuple2 tuple_3;
    tuple_3.t0 = call_72;
    tuple_3.t1 = ctx_1;
    match_32 = tuple_3;
    goto end_match_97;
next_98:;
    if ((!(xs_54))) goto next_99;
    struct AArm_ x_18 = xs_54->head;
    struct AArm_List* xs_55 = xs_54->tail;
    struct AArm_NameCtx_Tuple2 tuple_4;
    tuple_4.t0 = x_18;
    tuple_4.t1 = ctx_1;
    struct HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2 app_15 = f_5.fun(f_5.env, tuple_4);
    struct HPat_HExpr_HExpr_Tuple3 y_5 = app_15.t0;
    struct NameCtx_ ctx_2 = app_15.t1;
    struct HPat_HExpr_HExpr_Tuple3List* list_26 = (struct HPat_HExpr_HExpr_Tuple3List*)malloc(sizeof(struct HPat_HExpr_HExpr_Tuple3List));
    list_26->head = y_5;
    list_26->tail = acc_17;
    struct AArm_ListNameCtx_Tuple2 tuple_5;
    tuple_5.t0 = xs_55;
    tuple_5.t1 = ctx_2;
    struct HPat_HExpr_HExpr_Tuple3ListNameCtx_Tuple2 call_73 = go_59(f_5, list_26, tuple_5);
    match_32 = call_73;
    goto end_match_97;
next_99:;
    exit(1);
end_match_97:;
    return match_32;
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

struct HExpr_ListNameCtx_Tuple2 go_58(struct AExpr_NameCtx_Tuple2HExpr_NameCtx_Tuple2Fun1 f_5, struct HExpr_List* acc_17, struct AExpr_ListNameCtx_Tuple2 arg_97) {
    struct AExpr_List* xs_54 = arg_97.t0;
    struct NameCtx_ ctx_1 = arg_97.t1;
    struct HExpr_ListNameCtx_Tuple2 match_33;
    if ((!((!(xs_54))))) goto next_101;
    struct HExpr_List* call_74 = listRev_10(acc_17);
    struct HExpr_ListNameCtx_Tuple2 tuple_6;
    tuple_6.t0 = call_74;
    tuple_6.t1 = ctx_1;
    match_33 = tuple_6;
    goto end_match_100;
next_101:;
    if ((!(xs_54))) goto next_102;
    struct AExpr_ x_18 = xs_54->head;
    struct AExpr_List* xs_55 = xs_54->tail;
    struct AExpr_NameCtx_Tuple2 tuple_7;
    tuple_7.t0 = x_18;
    tuple_7.t1 = ctx_1;
    struct HExpr_NameCtx_Tuple2 app_16 = f_5.fun(f_5.env, tuple_7);
    struct HExpr_ y_5 = app_16.t0;
    struct NameCtx_ ctx_2 = app_16.t1;
    struct HExpr_List* list_27 = (struct HExpr_List*)malloc(sizeof(struct HExpr_List));
    list_27->head = y_5;
    list_27->tail = acc_17;
    struct AExpr_ListNameCtx_Tuple2 tuple_8;
    tuple_8.t0 = xs_55;
    tuple_8.t1 = ctx_2;
    struct HExpr_ListNameCtx_Tuple2 call_75 = go_58(f_5, list_27, tuple_8);
    match_33 = call_75;
    goto end_match_100;
next_102:;
    exit(1);
end_match_100:;
    return match_33;
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

struct HPat_ListNameCtx_Tuple2 go_57(struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1 f_5, struct HPat_List* acc_17, struct APat_ListNameCtx_Tuple2 arg_98) {
    struct APat_List* xs_54 = arg_98.t0;
    struct NameCtx_ ctx_1 = arg_98.t1;
    struct HPat_ListNameCtx_Tuple2 match_34;
    if ((!((!(xs_54))))) goto next_104;
    struct HPat_List* call_76 = listRev_9(acc_17);
    struct HPat_ListNameCtx_Tuple2 tuple_9;
    tuple_9.t0 = call_76;
    tuple_9.t1 = ctx_1;
    match_34 = tuple_9;
    goto end_match_103;
next_104:;
    if ((!(xs_54))) goto next_105;
    struct APat_ x_18 = xs_54->head;
    struct APat_List* xs_55 = xs_54->tail;
    struct APat_NameCtx_Tuple2 tuple_10;
    tuple_10.t0 = x_18;
    tuple_10.t1 = ctx_1;
    struct HPat_NameCtx_Tuple2 app_17 = f_5.fun(f_5.env, tuple_10);
    struct HPat_ y_5 = app_17.t0;
    struct NameCtx_ ctx_2 = app_17.t1;
    struct HPat_List* list_28 = (struct HPat_List*)malloc(sizeof(struct HPat_List));
    list_28->head = y_5;
    list_28->tail = acc_17;
    struct APat_ListNameCtx_Tuple2 tuple_11;
    tuple_11.t0 = xs_55;
    tuple_11.t1 = ctx_2;
    struct HPat_ListNameCtx_Tuple2 call_77 = go_57(f_5, list_28, tuple_11);
    match_34 = call_77;
    goto end_match_103;
next_105:;
    exit(1);
end_match_103:;
    return match_34;
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

struct StringIntBoolTy_Tuple4ListNameCtx_Tuple2 go_56(struct AVariant_NameCtx_Tuple2StringIntBoolTy_Tuple4NameCtx_Tuple2Fun1 f_5, struct StringIntBoolTy_Tuple4List* acc_17, struct AVariant_ListNameCtx_Tuple2 arg_99) {
    struct AVariant_List* xs_54 = arg_99.t0;
    struct NameCtx_ ctx_1 = arg_99.t1;
    struct StringIntBoolTy_Tuple4ListNameCtx_Tuple2 match_35;
    if ((!((!(xs_54))))) goto next_107;
    struct StringIntBoolTy_Tuple4List* call_78 = listRev_8(acc_17);
    struct StringIntBoolTy_Tuple4ListNameCtx_Tuple2 tuple_12;
    tuple_12.t0 = call_78;
    tuple_12.t1 = ctx_1;
    match_35 = tuple_12;
    goto end_match_106;
next_107:;
    if ((!(xs_54))) goto next_108;
    struct AVariant_ x_18 = xs_54->head;
    struct AVariant_List* xs_55 = xs_54->tail;
    struct AVariant_NameCtx_Tuple2 tuple_13;
    tuple_13.t0 = x_18;
    tuple_13.t1 = ctx_1;
    struct StringIntBoolTy_Tuple4NameCtx_Tuple2 app_18 = f_5.fun(f_5.env, tuple_13);
    struct StringIntBoolTy_Tuple4 y_5 = app_18.t0;
    struct NameCtx_ ctx_2 = app_18.t1;
    struct StringIntBoolTy_Tuple4List* list_29 = (struct StringIntBoolTy_Tuple4List*)malloc(sizeof(struct StringIntBoolTy_Tuple4List));
    list_29->head = y_5;
    list_29->tail = acc_17;
    struct AVariant_ListNameCtx_Tuple2 tuple_14;
    tuple_14.t0 = xs_55;
    tuple_14.t1 = ctx_2;
    struct StringIntBoolTy_Tuple4ListNameCtx_Tuple2 call_79 = go_56(f_5, list_29, tuple_14);
    match_35 = call_79;
    goto end_match_106;
next_108:;
    exit(1);
end_match_106:;
    return match_35;
}

struct Ty_ListNameCtx_Tuple2 stMap_5(struct ATy_NameCtx_Tuple2Ty_NameCtx_Tuple2Fun1 f_5, struct ATy_ListNameCtx_Tuple2 arg_100) {
    struct ATy_List* xs_53 = arg_100.t0;
    struct NameCtx_ ctx_ = arg_100.t1;
    struct ATy_ListNameCtx_Tuple2 tuple_15;
    tuple_15.t0 = xs_53;
    tuple_15.t1 = ctx_;
    struct Ty_ListNameCtx_Tuple2 call_80 = go_60(f_5, NULL, tuple_15);
    return call_80;
}

struct HPat_HExpr_HExpr_Tuple3ListNameCtx_Tuple2 stMap_4(struct AArm_NameCtx_Tuple2HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2Fun1 f_5, struct AArm_ListNameCtx_Tuple2 arg_101) {
    struct AArm_List* xs_53 = arg_101.t0;
    struct NameCtx_ ctx_ = arg_101.t1;
    struct AArm_ListNameCtx_Tuple2 tuple_16;
    tuple_16.t0 = xs_53;
    tuple_16.t1 = ctx_;
    struct HPat_HExpr_HExpr_Tuple3ListNameCtx_Tuple2 call_81 = go_59(f_5, NULL, tuple_16);
    return call_81;
}

struct HExpr_ListNameCtx_Tuple2 stMap_3(struct AExpr_NameCtx_Tuple2HExpr_NameCtx_Tuple2Fun1 f_5, struct AExpr_ListNameCtx_Tuple2 arg_102) {
    struct AExpr_List* xs_53 = arg_102.t0;
    struct NameCtx_ ctx_ = arg_102.t1;
    struct AExpr_ListNameCtx_Tuple2 tuple_17;
    tuple_17.t0 = xs_53;
    tuple_17.t1 = ctx_;
    struct HExpr_ListNameCtx_Tuple2 call_82 = go_58(f_5, NULL, tuple_17);
    return call_82;
}

struct HPat_ListNameCtx_Tuple2 stMap_2(struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1 f_5, struct APat_ListNameCtx_Tuple2 arg_103) {
    struct APat_List* xs_53 = arg_103.t0;
    struct NameCtx_ ctx_ = arg_103.t1;
    struct APat_ListNameCtx_Tuple2 tuple_18;
    tuple_18.t0 = xs_53;
    tuple_18.t1 = ctx_;
    struct HPat_ListNameCtx_Tuple2 call_83 = go_57(f_5, NULL, tuple_18);
    return call_83;
}

struct StringIntBoolTy_Tuple4ListNameCtx_Tuple2 stMap_1(struct AVariant_NameCtx_Tuple2StringIntBoolTy_Tuple4NameCtx_Tuple2Fun1 f_5, struct AVariant_ListNameCtx_Tuple2 arg_104) {
    struct AVariant_List* xs_53 = arg_104.t0;
    struct NameCtx_ ctx_ = arg_104.t1;
    struct AVariant_ListNameCtx_Tuple2 tuple_19;
    tuple_19.t0 = xs_53;
    tuple_19.t1 = ctx_;
    struct StringIntBoolTy_Tuple4ListNameCtx_Tuple2 call_84 = go_56(f_5, NULL, tuple_19);
    return call_84;
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

struct IntStringTuple2ListIntIntIntFun2Tuple2 mapEmpty_1(struct IntIntIntFun2 cmp_3) {
    struct IntStringTuple2ListIntIntIntFun2Tuple2 tuple_20;
    tuple_20.t0 = NULL;
    tuple_20.t1 = cmp_3;
    return tuple_20;
}

struct IntStringTuple2ListIntIntIntFun2Tuple2 mapAdd_1(int key_, struct String value_3, struct IntStringTuple2ListIntIntIntFun2Tuple2 arg_105) {
    struct IntStringTuple2List* assoc_ = arg_105.t0;
    struct IntIntIntFun2 cmp_4 = arg_105.t1;
    struct IntStringTuple2 tuple_22;
    tuple_22.t0 = key_;
    tuple_22.t1 = value_3;
    struct IntStringTuple2List* list_30 = (struct IntStringTuple2List*)malloc(sizeof(struct IntStringTuple2List));
    list_30->head = tuple_22;
    list_30->tail = assoc_;
    struct IntStringTuple2ListIntIntIntFun2Tuple2 tuple_21;
    tuple_21.t0 = list_30;
    tuple_21.t1 = cmp_4;
    return tuple_21;
}

struct StringList* go_80(struct IntIntIntFun2 cmp_6, int key_2, struct IntStringTuple2List* assoc_3) {
    struct StringList* match_36;
    if ((!((!(assoc_3))))) goto next_110;
    match_36 = NULL;
    goto end_match_109;
next_110:;
    if ((!(assoc_3))) goto next_111;
    int k_1 = assoc_3->head.t0;
    struct String v_ = assoc_3->head.t1;
    int app_19 = cmp_6.fun(cmp_6.env, k_1, key_2);
    if ((app_19 != 0)) goto next_111;
    struct StringList* some_ = (struct StringList*)malloc(sizeof(struct StringList));
    some_->head = v_;
    some_->tail = NULL;
    match_36 = some_;
    goto end_match_109;
next_111:;
    if ((!(assoc_3))) goto next_112;
    struct IntStringTuple2List* assoc_4 = assoc_3->tail;
    struct StringList* call_85 = go_80(cmp_6, key_2, assoc_4);
    match_36 = call_85;
    goto end_match_109;
next_112:;
    exit(1);
end_match_109:;
    return match_36;
}

struct StringList* mapTryFind_1(int key_2, struct IntStringTuple2ListIntIntIntFun2Tuple2 arg_106) {
    struct IntStringTuple2List* assoc_2 = arg_106.t0;
    struct IntIntIntFun2 cmp_6 = arg_106.t1;
    struct StringList* call_86 = go_80(cmp_6, key_2, assoc_2);
    return call_86;
}

struct String mapFind_1(int key_3, struct IntStringTuple2ListIntIntIntFun2Tuple2 map_) {
    struct String match_37;
    struct StringList* call_87 = mapTryFind_1(key_3, map_);
    if ((!(call_87))) goto next_114;
    struct String value_4 = call_87->head;
    if ((!((!(call_87->tail))))) goto next_114;
    match_37 = value_4;
    goto end_match_113;
next_114:;
    if ((!((!(call_87))))) goto next_115;
    struct IntStringFun1 call_88 = failwithf_4((struct String){.str = "mapFind: missing key (%A)", .len = 25});
    struct String app_20 = call_88.fun(call_88.env, key_3);
    match_37 = app_20;
    goto end_match_113;
next_115:;
    exit(1);
end_match_113:;
    return match_37;
}

int intMin_(int x_19, int y_6) {
    int match_38;
    if ((y_6 >= x_19)) goto next_117;
    match_38 = y_6;
    goto end_match_116;
next_117:;
    if ((y_6 < x_19)) goto next_118;
    match_38 = x_19;
    goto end_match_116;
next_118:;
    exit(1);
end_match_116:;
    return match_38;
}

int intMax_(int x_20, int y_7) {
    int match_39;
    if ((x_20 >= y_7)) goto next_120;
    match_39 = y_7;
    goto end_match_119;
next_120:;
    if ((x_20 < y_7)) goto next_121;
    match_39 = x_20;
    goto end_match_119;
next_121:;
    exit(1);
end_match_119:;
    return match_39;
}

int intEq_(int x_21, int y_8) {
    return (x_21 == y_8);
}

int intCmp_(int x_22, int y_9) {
    int match_40;
    if ((y_9 >= x_22)) goto next_123;
    match_40 = 1;
    goto end_match_122;
next_123:;
    if ((y_9 < x_22)) goto next_124;
    int match_41;
    if ((y_9 != x_22)) goto next_126;
    match_41 = 0;
    goto end_match_125;
next_126:;
    if ((y_9 == x_22)) goto next_127;
    match_41 = (0 - 1);
    goto end_match_125;
next_127:;
    exit(1);
end_match_125:;
    match_40 = match_41;
    goto end_match_122;
next_124:;
    exit(1);
end_match_122:;
    return match_40;
}

struct String go_30(struct String acc_18, int len_2, int n_1) {
    struct String match_42;
    int match_43;
    if ((n_1 != 0)) goto next_130;
    match_43 = (0 >= len_2);
    goto end_match_129;
next_130:;
    if ((n_1 == 0)) goto next_131;
    match_43 = 0;
    goto end_match_129;
next_131:;
    exit(1);
end_match_129:;
    if ((!(match_43))) goto next_132;
    match_42 = acc_18;
    goto end_match_128;
next_132:;
    if (match_43) goto next_133;
    int d_4 = (n_1 % 16);
    struct String call_89 = strSlice_(d_4, (d_4 + 1), (struct String){.str = "0123456789abcdef", .len = 16});
    struct String s_3 = call_89;
    struct String call_90 = go_30(str_add(s_3, acc_18), (len_2 - 1), (n_1 / 16));
    match_42 = call_90;
    goto end_match_128;
next_133:;
    exit(1);
end_match_128:;
    return match_42;
}

struct String intToHexWithPadding_(int len_1, int value_5) {
    struct String match_44;
    if ((value_5 >= 0)) goto next_135;
    struct String call_91 = failwith_3((struct String){.str = "intToHexWithPadding: unimplemented negative", .len = 43});
    match_44 = call_91;
    goto end_match_134;
next_135:;
    if ((value_5 < 0)) goto next_136;
    milone_assert((len_1 >= 0), 380, 2);
    int call_92 = 0;
    struct String match_45;
    int match_46;
    if ((value_5 != 0)) goto next_139;
    match_46 = (len_1 == 0);
    goto end_match_138;
next_139:;
    if ((value_5 == 0)) goto next_140;
    match_46 = 0;
    goto end_match_138;
next_140:;
    exit(1);
end_match_138:;
    if ((!(match_46))) goto next_141;
    match_45 = (struct String){.str = "0", .len = 1};
    goto end_match_137;
next_141:;
    if (match_46) goto next_142;
    struct String call_93 = go_30((struct String){.str = "", .len = 0}, len_1, value_5);
    match_45 = call_93;
    goto end_match_137;
next_142:;
    exit(1);
end_match_137:;
    match_44 = match_45;
    goto end_match_134;
next_136:;
    exit(1);
end_match_134:;
    return match_44;
}

int hexDigitToInt_(char c_6) {
    int match_47;
    int match_48;
    if ((c_6 < '0')) goto next_145;
    match_48 = ('9' >= c_6);
    goto end_match_144;
next_145:;
    if ((c_6 >= '0')) goto next_146;
    match_48 = 0;
    goto end_match_144;
next_146:;
    exit(1);
end_match_144:;
    if ((!(match_48))) goto next_147;
    int call_94 = charSub_(c_6, '0');
    match_47 = call_94;
    goto end_match_143;
next_147:;
    if (match_48) goto next_148;
    int match_49;
    int match_50;
    if ((c_6 < 'A')) goto next_151;
    match_50 = ('F' >= c_6);
    goto end_match_150;
next_151:;
    if ((c_6 >= 'A')) goto next_152;
    match_50 = 0;
    goto end_match_150;
next_152:;
    exit(1);
end_match_150:;
    if ((!(match_50))) goto next_153;
    int call_95 = charSub_(c_6, 'A');
    match_49 = (call_95 + 10);
    goto end_match_149;
next_153:;
    if (match_50) goto next_154;
    int match_51;
    int match_52;
    if ((c_6 < 'a')) goto next_157;
    match_52 = ('f' >= c_6);
    goto end_match_156;
next_157:;
    if ((c_6 >= 'a')) goto next_158;
    match_52 = 0;
    goto end_match_156;
next_158:;
    exit(1);
end_match_156:;
    if ((!(match_52))) goto next_159;
    int call_96 = charSub_(c_6, 'a');
    match_51 = (call_96 + 10);
    goto end_match_155;
next_159:;
    if (match_52) goto next_160;
    milone_assert(0, 406, 6);
    int call_97 = 0;
    match_51 = 0;
    goto end_match_155;
next_160:;
    exit(1);
end_match_155:;
    match_49 = match_51;
    goto end_match_149;
next_154:;
    exit(1);
end_match_149:;
    match_47 = match_49;
    goto end_match_143;
next_148:;
    exit(1);
end_match_143:;
    return match_47;
}

int go_31(struct String s_4, int r_20, int acc_19, int i_51) {
    int match_53;
    if ((i_51 != r_20)) goto next_162;
    match_53 = acc_19;
    goto end_match_161;
next_162:;
    if ((i_51 == r_20)) goto next_163;
    int call_98 = hexDigitToInt_(s_4.str[i_51]);
    int d_5 = call_98;
    int call_99 = go_31(s_4, r_20, ((acc_19 * 16) + d_5), (i_51 + 1));
    match_53 = call_99;
    goto end_match_161;
next_163:;
    exit(1);
end_match_161:;
    return match_53;
}

int intFromHex_(int l_8, int r_20, struct String s_4) {
    int match_54;
    int match_55;
    if ((l_8 < 0)) goto next_166;
    match_55 = (l_8 < r_20);
    goto end_match_165;
next_166:;
    if ((l_8 >= 0)) goto next_167;
    match_55 = 0;
    goto end_match_165;
next_167:;
    exit(1);
end_match_165:;
    if ((!(match_55))) goto next_168;
    match_54 = (s_4.len >= r_20);
    goto end_match_164;
next_168:;
    if (match_55) goto next_169;
    match_54 = 0;
    goto end_match_164;
next_169:;
    exit(1);
end_match_164:;
    milone_assert(match_54, 396, 2);
    int call_100 = 0;
    int call_101 = go_31(s_4, r_20, 0, l_8);
    return call_101;
}

int charSub_(char x_23, char y_10) {
    int call_102 = ((int)x_23);
    int call_103 = ((int)y_10);
    return (call_102 - call_103);
}

int charIsControl_(char c_7) {
    int call_104 = ((int)c_7);
    int n_2 = call_104;
    int match_56;
    int match_57;
    if ((n_2 < 0)) goto next_172;
    match_57 = (n_2 < 32);
    goto end_match_171;
next_172:;
    if ((n_2 >= 0)) goto next_173;
    match_57 = 0;
    goto end_match_171;
next_173:;
    exit(1);
end_match_171:;
    if ((!(match_57))) goto next_174;
    match_56 = 1;
    goto end_match_170;
next_174:;
    if (match_57) goto next_175;
    match_56 = (n_2 == 127);
    goto end_match_170;
next_175:;
    exit(1);
end_match_170:;
    return match_56;
}

int charIsSpace_(char c_8) {
    int match_58;
    int match_59;
    int match_60;
    if ((c_8 != ' ')) goto next_179;
    match_60 = 1;
    goto end_match_178;
next_179:;
    if ((c_8 == ' ')) goto next_180;
    match_60 = (c_8 == '\t');
    goto end_match_178;
next_180:;
    exit(1);
end_match_178:;
    if ((!(match_60))) goto next_181;
    match_59 = 1;
    goto end_match_177;
next_181:;
    if (match_60) goto next_182;
    match_59 = (c_8 == '\r');
    goto end_match_177;
next_182:;
    exit(1);
end_match_177:;
    if ((!(match_59))) goto next_183;
    match_58 = 1;
    goto end_match_176;
next_183:;
    if (match_59) goto next_184;
    match_58 = (c_8 == '\n');
    goto end_match_176;
next_184:;
    exit(1);
end_match_176:;
    return match_58;
}

int charIsDigit_(char c_9) {
    int match_61;
    if ((c_9 < '0')) goto next_186;
    match_61 = ('9' >= c_9);
    goto end_match_185;
next_186:;
    if ((c_9 >= '0')) goto next_187;
    match_61 = 0;
    goto end_match_185;
next_187:;
    exit(1);
end_match_185:;
    return match_61;
}

int charIsAlpha_(char c_10) {
    int match_62;
    int match_63;
    if ((c_10 < 'A')) goto next_190;
    match_63 = ('Z' >= c_10);
    goto end_match_189;
next_190:;
    if ((c_10 >= 'A')) goto next_191;
    match_63 = 0;
    goto end_match_189;
next_191:;
    exit(1);
end_match_189:;
    if ((!(match_63))) goto next_192;
    match_62 = 1;
    goto end_match_188;
next_192:;
    if (match_63) goto next_193;
    int match_64;
    if ((c_10 < 'a')) goto next_195;
    match_64 = ('z' >= c_10);
    goto end_match_194;
next_195:;
    if ((c_10 >= 'a')) goto next_196;
    match_64 = 0;
    goto end_match_194;
next_196:;
    exit(1);
end_match_194:;
    match_62 = match_64;
    goto end_match_188;
next_193:;
    exit(1);
end_match_188:;
    return match_62;
}

int charNeedsEscaping_(char c_11) {
    int match_65;
    int match_66;
    int match_67;
    int call_105 = charIsControl_(c_11);
    if ((!(call_105))) goto next_200;
    match_67 = 1;
    goto end_match_199;
next_200:;
    if (call_105) goto next_201;
    match_67 = (c_11 == '\\');
    goto end_match_199;
next_201:;
    exit(1);
end_match_199:;
    if ((!(match_67))) goto next_202;
    match_66 = 1;
    goto end_match_198;
next_202:;
    if (match_67) goto next_203;
    match_66 = (c_11 == '\"');
    goto end_match_198;
next_203:;
    exit(1);
end_match_198:;
    if ((!(match_66))) goto next_204;
    match_65 = 1;
    goto end_match_197;
next_204:;
    if (match_66) goto next_205;
    match_65 = (c_11 == '\'');
    goto end_match_197;
next_205:;
    exit(1);
end_match_197:;
    return match_65;
}

struct String charEscape_(char c_12) {
    int call_106 = charNeedsEscaping_(c_12);
    milone_assert(call_106, 442, 2);
    int call_107 = 0;
    struct String match_68;
    if ((c_12 != '\0')) goto next_207;
    match_68 = (struct String){.str = "\\0", .len = 2};
    goto end_match_206;
next_207:;
    if ((c_12 != '\t')) goto next_208;
    match_68 = (struct String){.str = "\\t", .len = 2};
    goto end_match_206;
next_208:;
    if ((c_12 != '\n')) goto next_209;
    match_68 = (struct String){.str = "\\n", .len = 2};
    goto end_match_206;
next_209:;
    if ((c_12 != '\r')) goto next_210;
    match_68 = (struct String){.str = "\\r", .len = 2};
    goto end_match_206;
next_210:;
    if ((c_12 != '\'')) goto next_211;
    match_68 = (struct String){.str = "\\\'", .len = 2};
    goto end_match_206;
next_211:;
    if ((c_12 != '\"')) goto next_212;
    match_68 = (struct String){.str = "\\\"", .len = 2};
    goto end_match_206;
next_212:;
    if ((c_12 != '\\')) goto next_213;
    match_68 = (struct String){.str = "\\\\", .len = 2};
    goto end_match_206;
next_213:;
    char c_13 = c_12;
    int call_108 = ((int)c_13);
    struct String call_109 = intToHexWithPadding_(2, call_108);
    struct String h_ = call_109;
    match_68 = str_add((struct String){.str = "\\x", .len = 2}, h_);
    goto end_match_206;
next_214:;
end_match_206:;
    return match_68;
}

int strCmp_(struct String x_24, struct String y_11) {
    int match_69;
    if ((str_cmp(y_11, x_24) >= 0)) goto next_216;
    match_69 = 1;
    goto end_match_215;
next_216:;
    if ((str_cmp(y_11, x_24) < 0)) goto next_217;
    int match_70;
    if ((str_cmp(y_11, x_24) != 0)) goto next_219;
    match_70 = 0;
    goto end_match_218;
next_219:;
    if ((str_cmp(y_11, x_24) == 0)) goto next_220;
    match_70 = (0 - 1);
    goto end_match_218;
next_220:;
    exit(1);
end_match_218:;
    match_69 = match_70;
    goto end_match_215;
next_217:;
    exit(1);
end_match_215:;
    return match_69;
}

struct String strSlice_(int start_, int endIndex_1, struct String s_5) {
    int match_71;
    if ((endIndex_1 < start_)) goto next_222;
    match_71 = (s_5.len >= endIndex_1);
    goto end_match_221;
next_222:;
    if ((endIndex_1 >= start_)) goto next_223;
    match_71 = 0;
    goto end_match_221;
next_223:;
    exit(1);
end_match_221:;
    milone_assert(match_71, 484, 2);
    int call_110 = 0;
    struct String match_72;
    if ((start_ < endIndex_1)) goto next_225;
    match_72 = (struct String){.str = "", .len = 0};
    goto end_match_224;
next_225:;
    if ((start_ >= endIndex_1)) goto next_226;
    struct String call_111 = str_get_slice(start_, (endIndex_1 - 1), s_5);
    match_72 = call_111;
    goto end_match_224;
next_226:;
    exit(1);
end_match_224:;
    return match_72;
}

struct StringStringListTuple2 {
    struct String t0;
    struct StringList* t1;
};

struct StringStringListTuple2 go_32(struct StringList* xs_57, int xn_3) {
    struct StringStringListTuple2 match_73;
    if ((!((!(xs_57))))) goto next_228;
    milone_assert((xn_3 == 0), 498, 6);
    int call_112 = 0;
    struct StringStringListTuple2 tuple_23;
    tuple_23.t0 = (struct String){.str = "", .len = 0};
    tuple_23.t1 = NULL;
    match_73 = tuple_23;
    goto end_match_227;
next_228:;
    if ((!(xs_57))) goto next_229;
    struct String x_25 = xs_57->head;
    struct StringList* xs_58 = xs_57->tail;
    if ((xn_3 != 1)) goto next_229;
    struct StringStringListTuple2 tuple_24;
    tuple_24.t0 = x_25;
    tuple_24.t1 = xs_58;
    match_73 = tuple_24;
    goto end_match_227;
next_229:;
    if ((!(xs_57))) goto next_230;
    struct String x_26 = xs_57->head;
    if ((!(xs_57->tail))) goto next_230;
    struct String y_12 = xs_57->tail->head;
    struct StringList* xs_59 = xs_57->tail->tail;
    if ((xn_3 != 2)) goto next_230;
    struct StringStringListTuple2 tuple_25;
    tuple_25.t0 = str_add(x_26, y_12);
    tuple_25.t1 = xs_59;
    match_73 = tuple_25;
    goto end_match_227;
next_230:;
    struct StringList* xs_60 = xs_57;
    int m_1 = (xn_3 / 2);
    struct StringStringListTuple2 call_113 = go_32(xs_60, m_1);
    struct String l_9 = call_113.t0;
    struct StringList* xs_61 = call_113.t1;
    struct StringStringListTuple2 call_114 = go_32(xs_61, (xn_3 - m_1));
    struct String r_21 = call_114.t0;
    struct StringList* xs_62 = call_114.t1;
    struct StringStringListTuple2 tuple_26;
    tuple_26.t0 = str_add(l_9, r_21);
    tuple_26.t1 = xs_62;
    match_73 = tuple_26;
    goto end_match_227;
next_231:;
end_match_227:;
    return match_73;
}

struct String strConcat_(struct StringList* xs_56) {
    int call_115 = listLength_1(xs_56);
    int n_3 = call_115;
    struct StringStringListTuple2 call_116 = go_32(xs_56, n_3);
    struct String s_6 = call_116.t0;
    struct StringList* xs_63 = call_116.t1;
    int call_117 = listIsEmpty_4(xs_63);
    milone_assert(call_117, 511, 2);
    int call_118 = 0;
    return s_6;
}

int go_33(struct String str_2, int i_52) {
    int match_74;
    if ((i_52 >= str_2.len)) goto next_233;
    int match_75;
    int call_119 = charNeedsEscaping_(str_2.str[i_52]);
    if ((!(call_119))) goto next_236;
    match_75 = 1;
    goto end_match_235;
next_236:;
    if (call_119) goto next_237;
    int call_120 = go_33(str_2, (i_52 + 1));
    match_75 = call_120;
    goto end_match_235;
next_237:;
    exit(1);
end_match_235:;
    match_74 = match_75;
    goto end_match_232;
next_233:;
    if ((i_52 < str_2.len)) goto next_234;
    match_74 = 0;
    goto end_match_232;
next_234:;
    exit(1);
end_match_232:;
    return match_74;
}

int strNeedsEscaping_(struct String str_2) {
    int call_121 = go_33(str_2, 0);
    return call_121;
}

int raw_(struct String str_3, int i_54) {
    int match_76;
    int match_77;
    if ((i_54 != str_3.len)) goto next_240;
    match_77 = 1;
    goto end_match_239;
next_240:;
    if ((i_54 == str_3.len)) goto next_241;
    int call_122 = charNeedsEscaping_(str_3.str[i_54]);
    match_77 = call_122;
    goto end_match_239;
next_241:;
    exit(1);
end_match_239:;
    if ((!(match_77))) goto next_242;
    match_76 = i_54;
    goto end_match_238;
next_242:;
    if (match_77) goto next_243;
    int call_123 = raw_(str_3, (i_54 + 1));
    match_76 = call_123;
    goto end_match_238;
next_243:;
    exit(1);
end_match_238:;
    return match_76;
}

struct IntStringListTuple2 {
    int t0;
    struct StringList* t1;
};

struct StringList* go_34(struct String str_3, struct StringList* acc_20, int i_53) {
    int call_124 = raw_(str_3, i_53);
    int r_22 = call_124;
    struct String call_125 = strSlice_(i_53, r_22, str_3);
    struct StringList* list_31 = (struct StringList*)malloc(sizeof(struct StringList));
    list_31->head = call_125;
    list_31->tail = acc_20;
    struct IntStringListTuple2 tuple_27;
    tuple_27.t0 = r_22;
    tuple_27.t1 = list_31;
    int i_55 = tuple_27.t0;
    struct StringList* acc_21 = tuple_27.t1;
    struct StringList* match_78;
    if ((i_55 != str_3.len)) goto next_245;
    match_78 = acc_21;
    goto end_match_244;
next_245:;
    if ((i_55 == str_3.len)) goto next_246;
    struct String call_126 = charEscape_(str_3.str[i_55]);
    struct String t_11 = call_126;
    struct StringList* list_32 = (struct StringList*)malloc(sizeof(struct StringList));
    list_32->head = t_11;
    list_32->tail = acc_21;
    struct StringList* call_127 = go_34(str_3, list_32, (i_55 + 1));
    match_78 = call_127;
    goto end_match_244;
next_246:;
    exit(1);
end_match_244:;
    return match_78;
}

struct String strEscape_(struct String str_3) {
    struct String match_79;
    int call_128 = strNeedsEscaping_(str_3);
    if (call_128) goto next_248;
    match_79 = str_3;
    goto end_match_247;
next_248:;
    if ((!(call_128))) goto next_249;
    struct StringList* call_129 = go_34(str_3, NULL, 0);
    struct StringList* call_130 = listRev_2(call_129);
    struct String call_131 = strConcat_(call_130);
    match_79 = call_131;
    goto end_match_247;
next_249:;
    exit(1);
end_match_247:;
    return match_79;
}

int locX_(struct IntIntTuple2 arg_107) {
    int x_27 = arg_107.t1;
    return x_27;
}

int locY_(struct IntIntTuple2 arg_108) {
    int y_13 = arg_108.t0;
    return y_13;
}

int locIsSameRow_(struct IntIntTuple2 first_, struct IntIntTuple2 second_) {
    int call_132 = locY_(first_);
    int call_133 = locY_(second_);
    return (call_132 == call_133);
}

int locIsSameColumn_(struct IntIntTuple2 first_1, struct IntIntTuple2 second_1) {
    int call_134 = locX_(first_1);
    int call_135 = locX_(second_1);
    return (call_134 == call_135);
}

int locInside_(struct IntIntTuple2 firstLoc_, struct IntIntTuple2 secondLoc_) {
    int call_136 = locX_(secondLoc_);
    int call_137 = locX_(firstLoc_);
    return (call_136 >= call_137);
}

struct IntIntTuple2 locAddX_(int dx_, struct IntIntTuple2 arg_109) {
    int y_14 = arg_109.t0;
    int x_28 = arg_109.t1;
    struct IntIntTuple2 tuple_28;
    tuple_28.t0 = y_14;
    tuple_28.t1 = (x_28 + dx_);
    return tuple_28;
}

struct IntIntTuple2 locMax_(struct IntIntTuple2 arg_110, struct IntIntTuple2 arg_111) {
    int firstY_ = arg_110.t0;
    int firstX_ = arg_110.t1;
    int secondY_ = arg_111.t0;
    int secondX_ = arg_111.t1;
    int call_138 = intMax_(firstY_, secondY_);
    int call_139 = intMax_(firstX_, secondX_);
    struct IntIntTuple2 tuple_29;
    tuple_29.t0 = call_138;
    tuple_29.t1 = call_139;
    return tuple_29;
}

struct String locToString_(struct IntIntTuple2 arg_112) {
    int y_15 = arg_112.t0;
    int x_29 = arg_112.t1;
    struct String call_140 = str_of_int((y_15 + 1));
    struct String call_141 = str_of_int((x_29 + 1));
    return str_add(str_add(call_140, (struct String){.str = ":", .len = 1}), call_141);
}

int tokenIsExprOrPatFirst_(struct Token_ token_7) {
    int match_80;
    if ((token_7.tag != Bool_1)) goto next_252;
    goto match_body_251;
next_252:;
    if ((token_7.tag != Int_1)) goto next_253;
    goto match_body_251;
next_253:;
    if ((token_7.tag != Char_1)) goto next_254;
    goto match_body_251;
next_254:;
    if ((token_7.tag != Str_1)) goto next_255;
    goto match_body_251;
next_255:;
    if ((token_7.tag != Ident_)) goto next_256;
    goto match_body_251;
next_256:;
    if ((token_7.tag != ParenL_)) goto next_257;
    goto match_body_251;
next_257:;
    if ((token_7.tag != BracketL_)) goto next_258;
    goto match_body_251;
match_body_251:;
    match_80 = 1;
    goto end_match_250;
next_258:;
    match_80 = 0;
    goto end_match_250;
next_259:;
end_match_250:;
    return match_80;
}

int tokenIsExprFirst_(struct Token_ token_8) {
    int match_81;
    int call_142 = tokenIsExprOrPatFirst_(token_8);
    if ((!(call_142))) goto next_262;
    match_81 = 1;
    goto end_match_260;
next_262:;
    if ((token_8.tag != Minus_)) goto next_263;
    goto match_body_261;
next_263:;
    if ((token_8.tag != If_)) goto next_264;
    goto match_body_261;
next_264:;
    if ((token_8.tag != Match_)) goto next_265;
    goto match_body_261;
next_265:;
    if ((token_8.tag != Fun_)) goto next_266;
    goto match_body_261;
next_266:;
    if ((token_8.tag != Do_)) goto next_267;
    goto match_body_261;
next_267:;
    if ((token_8.tag != Let_)) goto next_268;
    goto match_body_261;
next_268:;
    if ((token_8.tag != Type_)) goto next_269;
    goto match_body_261;
next_269:;
    if ((token_8.tag != Open_)) goto next_270;
    goto match_body_261;
match_body_261:;
    match_81 = 1;
    goto end_match_260;
next_270:;
    match_81 = 0;
    goto end_match_260;
next_271:;
end_match_260:;
    return match_81;
}

int tokenIsArgFirst_(struct Token_ token_9) {
    int match_82;
    if ((token_9.tag != Minus_)) goto next_273;
    match_82 = 0;
    goto end_match_272;
next_273:;
    int call_143 = tokenIsExprFirst_(token_9);
    match_82 = call_143;
    goto end_match_272;
next_274:;
end_match_272:;
    return match_82;
}

int tokenIsPatFirst_(struct Token_ token_10) {
    int call_144 = tokenIsExprOrPatFirst_(token_10);
    return call_144;
}

int tokenIsAccessModifier_(struct Token_ token_11) {
    int match_83;
    if ((token_11.tag != Private_)) goto next_277;
    goto match_body_276;
next_277:;
    if ((token_11.tag != Internal_)) goto next_278;
    goto match_body_276;
next_278:;
    if ((token_11.tag != Public_)) goto next_279;
    goto match_body_276;
match_body_276:;
    match_83 = 1;
    goto end_match_275;
next_279:;
    match_83 = 0;
    goto end_match_275;
next_280:;
end_match_275:;
    return match_83;
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
    struct OpLevel_ match_84;
    if ((level_.tag != Or_)) goto next_282;
    match_84 = (struct OpLevel_){.tag = And_};
    goto end_match_281;
next_282:;
    if ((level_.tag != And_)) goto next_283;
    match_84 = (struct OpLevel_){.tag = Cmp_};
    goto end_match_281;
next_283:;
    if ((level_.tag != Cmp_)) goto next_284;
    match_84 = (struct OpLevel_){.tag = Pipe_1};
    goto end_match_281;
next_284:;
    if ((level_.tag != Pipe_1)) goto next_285;
    match_84 = (struct OpLevel_){.tag = Cons_};
    goto end_match_281;
next_285:;
    if ((level_.tag != Cons_)) goto next_286;
    match_84 = (struct OpLevel_){.tag = Add_};
    goto end_match_281;
next_286:;
    if ((level_.tag != Add_)) goto next_288;
    match_84 = (struct OpLevel_){.tag = Mul_};
    goto end_match_281;
next_288:;
    if ((level_.tag != Mul_)) goto next_289;
    goto match_body_287;
next_289:;
    if ((level_.tag != Prefix_)) goto next_290;
    goto match_body_287;
match_body_287:;
    match_84 = (struct OpLevel_){.tag = Prefix_};
    goto end_match_281;
next_290:;
end_match_281:;
    return match_84;
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
    struct Lit_IntIntTuple2Tuple2 tuple_30;
    tuple_30.t0 = litFalse_;
    tuple_30.t1 = loc_2;
    struct Lit_IntIntTuple2Tuple2* payload_ = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_))) = tuple_30;
    struct APat_ variant_ = (struct APat_){.tag = Lit_, .Lit_ = payload_};
    return variant_;
}

struct APat_ apTrue_(struct Lit_ litTrue_, struct IntIntTuple2 loc_3) {
    struct Lit_IntIntTuple2Tuple2 tuple_31;
    tuple_31.t0 = litTrue_;
    tuple_31.t1 = loc_3;
    struct Lit_IntIntTuple2Tuple2* payload_1 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_1))) = tuple_31;
    struct APat_ variant_1 = (struct APat_){.tag = Lit_, .Lit_ = payload_1};
    return variant_1;
}

struct AExpr_ListIntIntTuple2Tuple2 {
    struct AExpr_List* t0;
    struct IntIntTuple2 t1;
};

struct AExpr_ axUnit_(struct IntIntTuple2 loc_4) {
    struct AExpr_ListIntIntTuple2Tuple2 tuple_32;
    tuple_32.t0 = NULL;
    tuple_32.t1 = loc_4;
    struct AExpr_ListIntIntTuple2Tuple2* payload_2 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_2))) = tuple_32;
    struct AExpr_ variant_2 = (struct AExpr_){.tag = TupleLit_1, .TupleLit_1 = payload_2};
    return variant_2;
}

struct AExpr_ axFalse_(struct Lit_ litFalse_, struct IntIntTuple2 loc_5) {
    struct Lit_IntIntTuple2Tuple2 tuple_33;
    tuple_33.t0 = litFalse_;
    tuple_33.t1 = loc_5;
    struct Lit_IntIntTuple2Tuple2* payload_3 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_3))) = tuple_33;
    struct AExpr_ variant_3 = (struct AExpr_){.tag = Lit_1, .Lit_1 = payload_3};
    return variant_3;
}

struct AExpr_ axTrue_(struct Lit_ litTrue_, struct IntIntTuple2 loc_6) {
    struct Lit_IntIntTuple2Tuple2 tuple_34;
    tuple_34.t0 = litTrue_;
    tuple_34.t1 = loc_6;
    struct Lit_IntIntTuple2Tuple2* payload_4 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_4))) = tuple_34;
    struct AExpr_ variant_4 = (struct AExpr_){.tag = Lit_1, .Lit_1 = payload_4};
    return variant_4;
}

struct AExpr_ axNil_(struct IntIntTuple2 loc_7) {
    struct AExpr_ListIntIntTuple2Tuple2 tuple_35;
    tuple_35.t0 = NULL;
    tuple_35.t1 = loc_7;
    struct AExpr_ListIntIntTuple2Tuple2* payload_5 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_5))) = tuple_35;
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
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_36;
    tuple_36.t0 = (struct Op_){.tag = App_};
    tuple_36.t1 = f_8;
    tuple_36.t2 = x_30;
    tuple_36.t3 = loc_8;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_6 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_6))) = tuple_36;
    struct AExpr_ variant_6 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_6};
    return variant_6;
}

struct AExpr_ axApp3_(struct AExpr_ f_7, struct AExpr_ x1_, struct AExpr_ x2_, struct AExpr_ x3_, struct IntIntTuple2 loc_8) {
    struct AExpr_ call_145 = app_(loc_8, x1_, f_7);
    struct AExpr_ call_146 = app_(loc_8, x2_, call_145);
    struct AExpr_ call_147 = app_(loc_8, x3_, call_146);
    return call_147;
}

struct AExpr_ axNot_(struct Lit_ litFalse_, struct AExpr_ arg_, struct IntIntTuple2 loc_9) {
    struct AExpr_ call_148 = axFalse_(litFalse_, loc_9);
    struct AExpr_ falseExpr_ = call_148;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_37;
    tuple_37.t0 = (struct Op_){.tag = Eq_1};
    tuple_37.t1 = arg_;
    tuple_37.t2 = falseExpr_;
    tuple_37.t3 = loc_9;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_7 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_7))) = tuple_37;
    struct AExpr_ variant_7 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_7};
    return variant_7;
}

struct StringDumpTree_ListDumpTree_ListTuple3 {
    struct String t0;
    struct DumpTree_List* t1;
    struct DumpTree_List* t2;
};

struct DumpTree_ dumpTreeNew_(struct String text_43, struct DumpTree_List* children_) {
    struct StringDumpTree_ListDumpTree_ListTuple3 tuple_38;
    tuple_38.t0 = text_43;
    tuple_38.t1 = children_;
    tuple_38.t2 = NULL;
    struct StringDumpTree_ListDumpTree_ListTuple3* payload_8 = (struct StringDumpTree_ListDumpTree_ListTuple3*)malloc(sizeof(struct StringDumpTree_ListDumpTree_ListTuple3));
    (*(((struct StringDumpTree_ListDumpTree_ListTuple3*)payload_8))) = tuple_38;
    struct DumpTree_ variant_8 = (struct DumpTree_){.tag = DumpTree_, .DumpTree_ = payload_8};
    return variant_8;
}

struct DumpTree_ dumpTreeNewLeaf_(struct String text_44) {
    struct StringDumpTree_ListDumpTree_ListTuple3 tuple_39;
    tuple_39.t0 = text_44;
    tuple_39.t1 = NULL;
    tuple_39.t2 = NULL;
    struct StringDumpTree_ListDumpTree_ListTuple3* payload_9 = (struct StringDumpTree_ListDumpTree_ListTuple3*)malloc(sizeof(struct StringDumpTree_ListDumpTree_ListTuple3));
    (*(((struct StringDumpTree_ListDumpTree_ListTuple3*)payload_9))) = tuple_39;
    struct DumpTree_ variant_9 = (struct DumpTree_){.tag = DumpTree_, .DumpTree_ = payload_9};
    return variant_9;
}

struct DumpTree_ dumpTreeAttachNext_(struct DumpTree_ next_1, struct DumpTree_ tree_) {
    struct DumpTree_ match_85;
    struct String text_45 = (*(tree_.DumpTree_)).t0;
    struct DumpTree_List* children_1 = (*(tree_.DumpTree_)).t1;
    struct DumpTree_List* oldNext_ = (*(tree_.DumpTree_)).t2;
    int call_149 = listIsEmpty_3(children_1);
    milone_assert((!(call_149)), 719, 4);
    int call_150 = 0;
    int call_151 = listIsEmpty_3(oldNext_);
    milone_assert(call_151, 720, 4);
    int call_152 = 0;
    struct DumpTree_List* list_33 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_33->head = next_1;
    list_33->tail = NULL;
    struct StringDumpTree_ListDumpTree_ListTuple3 tuple_40;
    tuple_40.t0 = text_45;
    tuple_40.t1 = children_1;
    tuple_40.t2 = list_33;
    struct StringDumpTree_ListDumpTree_ListTuple3* payload_10 = (struct StringDumpTree_ListDumpTree_ListTuple3*)malloc(sizeof(struct StringDumpTree_ListDumpTree_ListTuple3));
    (*(((struct StringDumpTree_ListDumpTree_ListTuple3*)payload_10))) = tuple_40;
    struct DumpTree_ variant_10 = (struct DumpTree_){.tag = DumpTree_, .DumpTree_ = payload_10};
    match_85 = variant_10;
    goto end_match_291;
next_292:;
    exit(1);
end_match_291:;
    return match_85;
}

struct DumpTree_ dumpTreeFromError_(struct String msg_, struct IntIntTuple2 arg_113) {
    int y_16 = arg_113.t0;
    int x_31 = arg_113.t1;
    struct String call_153 = str_of_int((y_16 + 1));
    struct String y_17 = call_153;
    struct String call_154 = str_of_int((x_31 + 1));
    struct String x_32 = call_154;
    struct DumpTree_ call_155 = dumpTreeNewLeaf_(msg_);
    struct DumpTree_ call_156 = dumpTreeNewLeaf_(str_add(str_add(str_add(str_add((struct String){.str = "(", .len = 1}, y_17), (struct String){.str = ":", .len = 1}), x_32), (struct String){.str = ")", .len = 1}));
    struct DumpTree_List* list_35 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_35->head = call_156;
    list_35->tail = NULL;
    struct DumpTree_List* list_34 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_34->head = call_155;
    list_34->tail = list_35;
    struct DumpTree_ call_157 = dumpTreeNew_((struct String){.str = "ERROR", .len = 5}, list_34);
    return call_157;
}

struct StringList* goChildren_(struct String eol_1, struct DumpTree_List* children_2, struct StringList* acc_23) {
    struct StringList* match_86;
    if ((!((!(children_2))))) goto next_294;
    match_86 = acc_23;
    goto end_match_293;
next_294:;
    if ((!(children_2))) goto next_295;
    struct DumpTree_ child_ = children_2->head;
    struct DumpTree_List* children_3 = children_2->tail;
    struct StringList* call_158 = cons_1(eol_1, acc_23);
    struct StringList* call_159 = cons_1((struct String){.str = "- ", .len = 2}, call_158);
    struct StringList* call_160 = go_35(str_add(eol_1, (struct String){.str = "  ", .len = 2}), child_, call_159);
    struct StringList* call_161 = goChildren_(eol_1, children_3, call_160);
    match_86 = call_161;
    goto end_match_293;
next_295:;
    exit(1);
end_match_293:;
    return match_86;
}

struct StringList* goNext_(struct String eol_2, struct DumpTree_List* next_2, struct StringList* acc_24) {
    struct StringList* match_87;
    if ((!((!(next_2))))) goto next_297;
    match_87 = acc_24;
    goto end_match_296;
next_297:;
    if ((!(next_2))) goto next_298;
    struct DumpTree_ next_3 = next_2->head;
    if ((!((!(next_2->tail))))) goto next_298;
    struct StringList* call_162 = cons_1(eol_2, acc_24);
    struct StringList* call_163 = go_35(eol_2, next_3, call_162);
    match_87 = call_163;
    goto end_match_296;
next_298:;
    struct StringList* call_164 = failwith_2((struct String){.str = "NEVER: DumpTree.next never empty", .len = 32});
    match_87 = call_164;
    goto end_match_296;
next_299:;
end_match_296:;
    return match_87;
}

struct StringList* go_35(struct String eol_, struct DumpTree_ node_1, struct StringList* acc_22) {
    struct StringList* match_88;
    struct String text_46 = (*(node_1.DumpTree_)).t0;
    if ((!((!((*(node_1.DumpTree_)).t1))))) goto next_301;
    if ((!((!((*(node_1.DumpTree_)).t2))))) goto next_301;
    struct String call_165 = strEscape_(text_46);
    struct StringList* call_166 = cons_1(call_165, acc_22);
    match_88 = call_166;
    goto end_match_300;
next_301:;
    struct String text_47 = (*(node_1.DumpTree_)).t0;
    if ((!((*(node_1.DumpTree_)).t1))) goto next_302;
    struct String childText_ = (*((*(node_1.DumpTree_)).t1->head.DumpTree_)).t0;
    if ((!((!((*((*(node_1.DumpTree_)).t1->head.DumpTree_)).t1))))) goto next_302;
    if ((!((!((*((*(node_1.DumpTree_)).t1->head.DumpTree_)).t2))))) goto next_302;
    if ((!((!((*(node_1.DumpTree_)).t1->tail))))) goto next_302;
    struct DumpTree_List* next_4 = (*(node_1.DumpTree_)).t2;
    struct String call_167 = strEscape_(childText_);
    struct String call_168 = strEscape_(text_47);
    struct StringList* call_169 = cons_1(call_168, acc_22);
    struct StringList* call_170 = cons_1((struct String){.str = ": ", .len = 2}, call_169);
    struct StringList* call_171 = cons_1(call_167, call_170);
    struct StringList* call_172 = goNext_(eol_, next_4, call_171);
    match_88 = call_172;
    goto end_match_300;
next_302:;
    struct String text_48 = (*(node_1.DumpTree_)).t0;
    struct DumpTree_List* children_4 = (*(node_1.DumpTree_)).t1;
    struct DumpTree_List* next_5 = (*(node_1.DumpTree_)).t2;
    struct String call_173 = strEscape_(text_48);
    struct StringList* call_174 = cons_1(call_173, acc_22);
    struct StringList* call_175 = cons_1((struct String){.str = ":", .len = 1}, call_174);
    struct StringList* call_176 = goChildren_(eol_, children_4, call_175);
    struct StringList* call_177 = goNext_(eol_, next_5, call_176);
    match_88 = call_177;
    goto end_match_300;
next_303:;
    exit(1);
end_match_300:;
    return match_88;
}

struct String dumpTreeToString_(struct DumpTree_ node_) {
    struct String eol_3 = (struct String){.str = "\n", .len = 1};
    struct StringList* call_178 = go_35(eol_3, node_, NULL);
    struct StringList* call_179 = listRev_2(call_178);
    struct String call_180 = strConcat_(call_179);
    return call_180;
}

int fun_9(void* env_3, int arg_14, int arg_15) {
    int call_181 = intCmp_(arg_14, arg_15);
    return call_181;
}

struct IntStringTuple2ListIntIntIntFun2Tuple2IntTuple2 {
    struct IntStringTuple2ListIntIntIntFun2Tuple2 t0;
    int t1;
};

struct NameCtx_ nameCtxEmpty_(int arg_114) {
    void* box_ = (void*)malloc(sizeof(int));
    (*(((int*)box_))) = 0;
    void* env_39 = box_;
    struct IntIntIntFun2 fun_45 = (struct IntIntIntFun2){.fun = fun_9, .env = env_39};
    struct IntStringTuple2ListIntIntIntFun2Tuple2 call_182 = mapEmpty_1(fun_45);
    struct IntStringTuple2ListIntIntIntFun2Tuple2IntTuple2 tuple_41;
    tuple_41.t0 = call_182;
    tuple_41.t1 = 0;
    struct IntStringTuple2ListIntIntIntFun2Tuple2IntTuple2* payload_11 = (struct IntStringTuple2ListIntIntIntFun2Tuple2IntTuple2*)malloc(sizeof(struct IntStringTuple2ListIntIntIntFun2Tuple2IntTuple2));
    (*(((struct IntStringTuple2ListIntIntIntFun2Tuple2IntTuple2*)payload_11))) = tuple_41;
    struct NameCtx_ variant_11 = (struct NameCtx_){.tag = NameCtx_, .NameCtx_ = payload_11};
    return variant_11;
}

struct IntNameCtx_Tuple2 {
    int t0;
    struct NameCtx_ t1;
};

struct IntNameCtx_Tuple2 nameCtxAdd_(struct String ident_, struct NameCtx_ arg_115) {
    struct IntStringTuple2ListIntIntIntFun2Tuple2 map_4 = (*(arg_115.NameCtx_)).t0;
    int serial_ = (*(arg_115.NameCtx_)).t1;
    int serial_1 = (serial_ + 1);
    struct IntStringTuple2ListIntIntIntFun2Tuple2 call_183 = mapAdd_1(serial_1, ident_, map_4);
    struct IntStringTuple2ListIntIntIntFun2Tuple2 map_5 = call_183;
    struct IntStringTuple2ListIntIntIntFun2Tuple2IntTuple2 tuple_43;
    tuple_43.t0 = map_5;
    tuple_43.t1 = serial_1;
    struct IntStringTuple2ListIntIntIntFun2Tuple2IntTuple2* payload_12 = (struct IntStringTuple2ListIntIntIntFun2Tuple2IntTuple2*)malloc(sizeof(struct IntStringTuple2ListIntIntIntFun2Tuple2IntTuple2));
    (*(((struct IntStringTuple2ListIntIntIntFun2Tuple2IntTuple2*)payload_12))) = tuple_43;
    struct NameCtx_ variant_12 = (struct NameCtx_){.tag = NameCtx_, .NameCtx_ = payload_12};
    struct IntNameCtx_Tuple2 tuple_42;
    tuple_42.t0 = serial_1;
    tuple_42.t1 = variant_12;
    return tuple_42;
}

struct String nameCtxFind_(int serial_2, struct NameCtx_ arg_116) {
    struct IntStringTuple2ListIntIntIntFun2Tuple2 map_6 = (*(arg_116.NameCtx_)).t0;
    struct String call_184 = mapFind_1(serial_2, map_6);
    return call_184;
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
    struct Trait_ match_89;
    if ((it_.tag != Add_2)) goto next_305;
    struct Ty_ ty_ = (*(it_.Add_2));
    struct Ty_ app_21 = f_9.fun(f_9.env, ty_);
    struct Ty_* payload_13 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_13))) = app_21;
    struct Trait_ variant_13 = (struct Trait_){.tag = Add_2, .Add_2 = payload_13};
    match_89 = variant_13;
    goto end_match_304;
next_305:;
    if ((it_.tag != Eq_2)) goto next_306;
    struct Ty_ ty_1 = (*(it_.Eq_2));
    struct Ty_ app_22 = f_9.fun(f_9.env, ty_1);
    struct Ty_* payload_14 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_14))) = app_22;
    struct Trait_ variant_14 = (struct Trait_){.tag = Eq_2, .Eq_2 = payload_14};
    match_89 = variant_14;
    goto end_match_304;
next_306:;
    if ((it_.tag != Cmp_1)) goto next_307;
    struct Ty_ ty_2 = (*(it_.Cmp_1));
    struct Ty_ app_23 = f_9.fun(f_9.env, ty_2);
    struct Ty_* payload_15 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_15))) = app_23;
    struct Trait_ variant_15 = (struct Trait_){.tag = Cmp_1, .Cmp_1 = payload_15};
    match_89 = variant_15;
    goto end_match_304;
next_307:;
    if ((it_.tag != Index_1)) goto next_308;
    struct Ty_ lTy_ = (*(it_.Index_1)).t0;
    struct Ty_ rTy_ = (*(it_.Index_1)).t1;
    struct Ty_ outputTy_ = (*(it_.Index_1)).t2;
    struct Ty_ app_24 = f_9.fun(f_9.env, lTy_);
    struct Ty_ app_25 = f_9.fun(f_9.env, rTy_);
    struct Ty_ app_26 = f_9.fun(f_9.env, outputTy_);
    struct Ty_Ty_Ty_Tuple3 tuple_44;
    tuple_44.t0 = app_24;
    tuple_44.t1 = app_25;
    tuple_44.t2 = app_26;
    struct Ty_Ty_Ty_Tuple3* payload_16 = (struct Ty_Ty_Ty_Tuple3*)malloc(sizeof(struct Ty_Ty_Ty_Tuple3));
    (*(((struct Ty_Ty_Ty_Tuple3*)payload_16))) = tuple_44;
    struct Trait_ variant_16 = (struct Trait_){.tag = Index_1, .Index_1 = payload_16};
    match_89 = variant_16;
    goto end_match_304;
next_308:;
    if ((it_.tag != ToInt_)) goto next_309;
    struct Ty_ ty_3 = (*(it_.ToInt_));
    struct Ty_ app_27 = f_9.fun(f_9.env, ty_3);
    struct Ty_* payload_17 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_17))) = app_27;
    struct Trait_ variant_17 = (struct Trait_){.tag = ToInt_, .ToInt_ = payload_17};
    match_89 = variant_17;
    goto end_match_304;
next_309:;
    if ((it_.tag != ToString_)) goto next_310;
    struct Ty_ ty_4 = (*(it_.ToString_));
    struct Ty_ app_28 = f_9.fun(f_9.env, ty_4);
    struct Ty_* payload_18 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_18))) = app_28;
    struct Trait_ variant_18 = (struct Trait_){.tag = ToString_, .ToString_ = payload_18};
    match_89 = variant_18;
    goto end_match_304;
next_310:;
    exit(1);
end_match_304:;
    return match_89;
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
    struct TyCon_Ty_ListTuple2 tuple_45;
    tuple_45.t0 = (struct TyCon_){.tag = Tuple_1};
    tuple_45.t1 = tys_;
    struct TyCon_Ty_ListTuple2* payload_19 = (struct TyCon_Ty_ListTuple2*)malloc(sizeof(struct TyCon_Ty_ListTuple2));
    (*(((struct TyCon_Ty_ListTuple2*)payload_19))) = tuple_45;
    struct Ty_ variant_19 = (struct Ty_){.tag = Con_, .Con_ = payload_19};
    return variant_19;
}

struct Ty_ tyList_(struct Ty_ ty_5) {
    struct Ty_List* list_36 = (struct Ty_List*)malloc(sizeof(struct Ty_List));
    list_36->head = ty_5;
    list_36->tail = NULL;
    struct TyCon_Ty_ListTuple2 tuple_46;
    tuple_46.t0 = (struct TyCon_){.tag = List_};
    tuple_46.t1 = list_36;
    struct TyCon_Ty_ListTuple2* payload_20 = (struct TyCon_Ty_ListTuple2*)malloc(sizeof(struct TyCon_Ty_ListTuple2));
    (*(((struct TyCon_Ty_ListTuple2*)payload_20))) = tuple_46;
    struct Ty_ variant_20 = (struct Ty_){.tag = Con_, .Con_ = payload_20};
    return variant_20;
}

struct Ty_ tyFun_(struct Ty_ sourceTy_, struct Ty_ targetTy_) {
    struct Ty_List* list_38 = (struct Ty_List*)malloc(sizeof(struct Ty_List));
    list_38->head = targetTy_;
    list_38->tail = NULL;
    struct Ty_List* list_37 = (struct Ty_List*)malloc(sizeof(struct Ty_List));
    list_37->head = sourceTy_;
    list_37->tail = list_38;
    struct TyCon_Ty_ListTuple2 tuple_47;
    tuple_47.t0 = (struct TyCon_){.tag = Fun_4};
    tuple_47.t1 = list_37;
    struct TyCon_Ty_ListTuple2* payload_21 = (struct TyCon_Ty_ListTuple2*)malloc(sizeof(struct TyCon_Ty_ListTuple2));
    (*(((struct TyCon_Ty_ListTuple2*)payload_21))) = tuple_47;
    struct Ty_ variant_21 = (struct Ty_){.tag = Con_, .Con_ = payload_21};
    return variant_21;
}

struct Ty_ tyRef_(int serial_3, struct Ty_List* tys_1) {
    int* payload_22 = (int*)malloc(sizeof(int));
    (*(((int*)payload_22))) = serial_3;
    struct TyCon_ variant_22 = (struct TyCon_){.tag = Ref_, .Ref_ = payload_22};
    struct TyCon_Ty_ListTuple2 tuple_48;
    tuple_48.t0 = variant_22;
    tuple_48.t1 = tys_1;
    struct TyCon_Ty_ListTuple2* payload_23 = (struct TyCon_Ty_ListTuple2*)malloc(sizeof(struct TyCon_Ty_ListTuple2));
    (*(((struct TyCon_Ty_ListTuple2*)payload_23))) = tuple_48;
    struct Ty_ variant_23 = (struct Ty_){.tag = Con_, .Con_ = payload_23};
    return variant_23;
}

struct StringTy_ListTuple2 {
    struct String t0;
    struct Ty_List* t1;
};

struct Ty_ tyPrimFromIdent_(struct Ty_ tyUnit_, struct Ty_ tyObj_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct String ident_1, struct Ty_List* tys_2, struct IntIntTuple2 loc_10) {
    struct Ty_ match_90;
    struct StringTy_ListTuple2 tuple_49;
    tuple_49.t0 = ident_1;
    tuple_49.t1 = tys_2;
    if ((str_cmp(tuple_49.t0, (struct String){.str = "unit", .len = 4}) != 0)) goto next_312;
    if ((!((!(tuple_49.t1))))) goto next_312;
    match_90 = tyUnit_;
    goto end_match_311;
next_312:;
    if ((str_cmp(tuple_49.t0, (struct String){.str = "bool", .len = 4}) != 0)) goto next_313;
    if ((!((!(tuple_49.t1))))) goto next_313;
    match_90 = tyBool_;
    goto end_match_311;
next_313:;
    if ((str_cmp(tuple_49.t0, (struct String){.str = "int", .len = 3}) != 0)) goto next_314;
    if ((!((!(tuple_49.t1))))) goto next_314;
    match_90 = tyInt_;
    goto end_match_311;
next_314:;
    if ((str_cmp(tuple_49.t0, (struct String){.str = "char", .len = 4}) != 0)) goto next_315;
    if ((!((!(tuple_49.t1))))) goto next_315;
    match_90 = tyChar_;
    goto end_match_311;
next_315:;
    if ((str_cmp(tuple_49.t0, (struct String){.str = "string", .len = 6}) != 0)) goto next_316;
    if ((!((!(tuple_49.t1))))) goto next_316;
    match_90 = tyStr_;
    goto end_match_311;
next_316:;
    if ((str_cmp(tuple_49.t0, (struct String){.str = "obj", .len = 3}) != 0)) goto next_317;
    if ((!((!(tuple_49.t1))))) goto next_317;
    match_90 = tyObj_;
    goto end_match_311;
next_317:;
    if ((str_cmp(tuple_49.t0, (struct String){.str = "list", .len = 4}) != 0)) goto next_318;
    if ((!(tuple_49.t1))) goto next_318;
    struct Ty_ itemTy_ = tuple_49.t1->head;
    if ((!((!(tuple_49.t1->tail))))) goto next_318;
    struct Ty_ call_185 = tyList_(itemTy_);
    match_90 = call_185;
    goto end_match_311;
next_318:;
    struct IntIntTuple2* payload_24 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_24))) = loc_10;
    struct Ty_ variant_24 = (struct Ty_){.tag = Error_1, .Error_1 = payload_24};
    match_90 = variant_24;
    goto end_match_311;
next_319:;
end_match_311:;
    return match_90;
}

struct IntIntIntTuple2Tuple2 {
    int t0;
    struct IntIntTuple2 t1;
};

int go_36(int tySerial_, struct Ty_ ty_7) {
    int match_91;
    if ((ty_7.tag != Error_1)) goto next_322;
    goto match_body_321;
next_322:;
    if ((ty_7.tag != Con_)) goto next_323;
    if ((!((!((*(ty_7.Con_)).t1))))) goto next_323;
    goto match_body_321;
match_body_321:;
    match_91 = 1;
    goto end_match_320;
next_323:;
    if ((ty_7.tag != Con_)) goto next_324;
    struct TyCon_ tyCon_ = (*(ty_7.Con_)).t0;
    if ((!((*(ty_7.Con_)).t1))) goto next_324;
    struct Ty_ ty_8 = (*(ty_7.Con_)).t1->head;
    struct Ty_List* tys_3 = (*(ty_7.Con_)).t1->tail;
    int match_92;
    int call_186 = go_36(tySerial_, ty_8);
    if ((!(call_186))) goto next_327;
    struct TyCon_Ty_ListTuple2 tuple_50;
    tuple_50.t0 = tyCon_;
    tuple_50.t1 = tys_3;
    struct TyCon_Ty_ListTuple2* payload_25 = (struct TyCon_Ty_ListTuple2*)malloc(sizeof(struct TyCon_Ty_ListTuple2));
    (*(((struct TyCon_Ty_ListTuple2*)payload_25))) = tuple_50;
    struct Ty_ variant_25 = (struct Ty_){.tag = Con_, .Con_ = payload_25};
    int call_187 = go_36(tySerial_, variant_25);
    match_92 = call_187;
    goto end_match_326;
next_327:;
    if (call_186) goto next_328;
    match_92 = 0;
    goto end_match_326;
next_328:;
    exit(1);
end_match_326:;
    match_91 = match_92;
    goto end_match_320;
next_324:;
    if ((ty_7.tag != Meta_)) goto next_325;
    int s_7 = (*(ty_7.Meta_)).t0;
    match_91 = (s_7 != tySerial_);
    goto end_match_320;
next_325:;
    exit(1);
end_match_320:;
    return match_91;
}

int tyIsFreeIn_(struct Ty_ ty_6, int tySerial_) {
    int call_188 = go_36(tySerial_, ty_6);
    return call_188;
}

int go_37(struct Ty_List* tys_4) {
    int match_93;
    if ((!((!(tys_4))))) goto next_330;
    match_93 = 1;
    goto end_match_329;
next_330:;
    if ((!(tys_4))) goto next_331;
    if ((tys_4->head.tag != Meta_)) goto next_331;
    match_93 = 0;
    goto end_match_329;
next_331:;
    if ((!(tys_4))) goto next_332;
    if ((tys_4->head.tag != Error_1)) goto next_332;
    struct Ty_List* tys_5 = tys_4->tail;
    int call_189 = go_37(tys_5);
    match_93 = call_189;
    goto end_match_329;
next_332:;
    if ((!(tys_4))) goto next_333;
    if ((tys_4->head.tag != Con_)) goto next_333;
    struct Ty_List* tys1_ = (*(tys_4->head.Con_)).t1;
    struct Ty_List* tys2_ = tys_4->tail;
    int match_94;
    int call_190 = go_37(tys1_);
    if ((!(call_190))) goto next_335;
    int call_191 = go_37(tys2_);
    match_94 = call_191;
    goto end_match_334;
next_335:;
    if (call_190) goto next_336;
    match_94 = 0;
    goto end_match_334;
next_336:;
    exit(1);
end_match_334:;
    match_93 = match_94;
    goto end_match_329;
next_333:;
    exit(1);
end_match_329:;
    return match_93;
}

int tyIsMonomorphic_(struct Ty_ ty_9) {
    struct Ty_List* list_39 = (struct Ty_List*)malloc(sizeof(struct Ty_List));
    list_39->head = ty_9;
    list_39->tail = NULL;
    int call_192 = go_37(list_39);
    return call_192;
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
    struct String match_95;
    if ((tyDef_.tag != Meta_1)) goto next_338;
    struct String ident_2 = (*(tyDef_.Meta_1)).t0;
    match_95 = ident_2;
    goto end_match_337;
next_338:;
    if ((tyDef_.tag != Union_2)) goto next_339;
    struct String ident_3 = (*(tyDef_.Union_2)).t0;
    match_95 = ident_3;
    goto end_match_337;
next_339:;
    exit(1);
end_match_337:;
    return match_95;
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
    struct String match_96;
    if ((varDef_.tag != Var_)) goto next_341;
    struct String ident_4 = (*(varDef_.Var_)).t0;
    match_96 = ident_4;
    goto end_match_340;
next_341:;
    if ((varDef_.tag != Fun_5)) goto next_342;
    struct String ident_5 = (*(varDef_.Fun_5)).t0;
    match_96 = ident_5;
    goto end_match_340;
next_342:;
    if ((varDef_.tag != Variant_)) goto next_343;
    struct String ident_6 = (*(varDef_.Variant_)).t0;
    match_96 = ident_6;
    goto end_match_340;
next_343:;
    exit(1);
end_match_340:;
    return match_96;
}

struct Ty_ litToTy_(struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Lit_ lit_) {
    struct Ty_ match_97;
    if ((lit_.tag != Bool_)) goto next_345;
    match_97 = tyBool_;
    goto end_match_344;
next_345:;
    if ((lit_.tag != Int_)) goto next_346;
    match_97 = tyInt_;
    goto end_match_344;
next_346:;
    if ((lit_.tag != Char_)) goto next_347;
    match_97 = tyChar_;
    goto end_match_344;
next_347:;
    if ((lit_.tag != Str_)) goto next_348;
    match_97 = tyStr_;
    goto end_match_344;
next_348:;
    exit(1);
end_match_344:;
    return match_97;
}

struct Ty_ meta_(struct IntIntTuple2 noLoc_, int id_) {
    struct IntIntIntTuple2Tuple2 tuple_51;
    tuple_51.t0 = id_;
    tuple_51.t1 = noLoc_;
    struct IntIntIntTuple2Tuple2* payload_26 = (struct IntIntIntTuple2Tuple2*)malloc(sizeof(struct IntIntIntTuple2Tuple2));
    (*(((struct IntIntIntTuple2Tuple2*)payload_26))) = tuple_51;
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
    struct Ty_Trait_ListTuple2 tuple_52;
    tuple_52.t0 = ty_10;
    tuple_52.t1 = NULL;
    struct Ty_Trait_ListTuple2* payload_27 = (struct Ty_Trait_ListTuple2*)malloc(sizeof(struct Ty_Trait_ListTuple2));
    (*(((struct Ty_Trait_ListTuple2*)payload_27))) = tuple_52;
    struct TySpec_ variant_27 = (struct TySpec_){.tag = TySpec_, .TySpec_ = payload_27};
    return variant_27;
}

struct TySpec_ poly_(struct Ty_ ty_11, struct Trait_List* traits_) {
    struct Ty_Trait_ListTuple2 tuple_53;
    tuple_53.t0 = ty_11;
    tuple_53.t1 = traits_;
    struct Ty_Trait_ListTuple2* payload_28 = (struct Ty_Trait_ListTuple2*)malloc(sizeof(struct Ty_Trait_ListTuple2));
    (*(((struct Ty_Trait_ListTuple2*)payload_28))) = tuple_53;
    struct TySpec_ variant_28 = (struct TySpec_){.tag = TySpec_, .TySpec_ = payload_28};
    return variant_28;
}

struct TySpec_ primToTySpec_(struct Ty_ tyUnit_, struct Ty_ tyObj_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct IntIntTuple2 noLoc_, struct HPrim_ prim_) {
    struct TySpec_ match_98;
    if ((prim_.tag != Add_3)) goto next_350;
    struct Ty_ call_193 = meta_(noLoc_, 1);
    struct Ty_ addTy_ = call_193;
    struct Ty_ call_194 = tyFun_(addTy_, addTy_);
    struct Ty_ call_195 = tyFun_(addTy_, call_194);
    struct Ty_* payload_29 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_29))) = addTy_;
    struct Trait_ variant_29 = (struct Trait_){.tag = Add_2, .Add_2 = payload_29};
    struct Trait_List* list_40 = (struct Trait_List*)malloc(sizeof(struct Trait_List));
    list_40->head = variant_29;
    list_40->tail = NULL;
    struct TySpec_ call_196 = poly_(call_195, list_40);
    match_98 = call_196;
    goto end_match_349;
next_350:;
    if ((prim_.tag != Sub_1)) goto next_351;
    struct Ty_ call_197 = tyFun_(tyInt_, tyInt_);
    struct Ty_ call_198 = tyFun_(tyInt_, call_197);
    struct TySpec_ call_199 = mono_(call_198);
    match_98 = call_199;
    goto end_match_349;
next_351:;
    if ((prim_.tag != Mul_2)) goto next_352;
    struct Ty_ call_200 = tyFun_(tyInt_, tyInt_);
    struct Ty_ call_201 = tyFun_(tyInt_, call_200);
    struct TySpec_ call_202 = mono_(call_201);
    match_98 = call_202;
    goto end_match_349;
next_352:;
    if ((prim_.tag != Div_1)) goto next_353;
    struct Ty_ call_203 = tyFun_(tyInt_, tyInt_);
    struct Ty_ call_204 = tyFun_(tyInt_, call_203);
    struct TySpec_ call_205 = mono_(call_204);
    match_98 = call_205;
    goto end_match_349;
next_353:;
    if ((prim_.tag != Mod_1)) goto next_354;
    struct Ty_ call_206 = tyFun_(tyInt_, tyInt_);
    struct Ty_ call_207 = tyFun_(tyInt_, call_206);
    struct TySpec_ call_208 = mono_(call_207);
    match_98 = call_208;
    goto end_match_349;
next_354:;
    if ((prim_.tag != Eq_3)) goto next_355;
    struct Ty_ call_209 = meta_(noLoc_, 1);
    struct Ty_ eqTy_ = call_209;
    struct Ty_ call_210 = tyFun_(eqTy_, tyBool_);
    struct Ty_ call_211 = tyFun_(eqTy_, call_210);
    struct Ty_* payload_30 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_30))) = eqTy_;
    struct Trait_ variant_30 = (struct Trait_){.tag = Eq_2, .Eq_2 = payload_30};
    struct Trait_List* list_41 = (struct Trait_List*)malloc(sizeof(struct Trait_List));
    list_41->head = variant_30;
    list_41->tail = NULL;
    struct TySpec_ call_212 = poly_(call_211, list_41);
    match_98 = call_212;
    goto end_match_349;
next_355:;
    if ((prim_.tag != Lt_2)) goto next_356;
    struct Ty_ call_213 = meta_(noLoc_, 1);
    struct Ty_ cmpTy_ = call_213;
    struct Ty_ call_214 = tyFun_(cmpTy_, tyBool_);
    struct Ty_ call_215 = tyFun_(cmpTy_, call_214);
    struct Ty_* payload_31 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_31))) = cmpTy_;
    struct Trait_ variant_31 = (struct Trait_){.tag = Cmp_1, .Cmp_1 = payload_31};
    struct Trait_List* list_42 = (struct Trait_List*)malloc(sizeof(struct Trait_List));
    list_42->head = variant_31;
    list_42->tail = NULL;
    struct TySpec_ call_216 = poly_(call_215, list_42);
    match_98 = call_216;
    goto end_match_349;
next_356:;
    if ((prim_.tag != Nil_1)) goto next_357;
    struct Ty_ call_217 = meta_(noLoc_, 1);
    struct Ty_ itemTy_1 = call_217;
    struct Ty_ call_218 = tyList_(itemTy_1);
    struct TySpec_ call_219 = poly_(call_218, NULL);
    match_98 = call_219;
    goto end_match_349;
next_357:;
    if ((prim_.tag != Cons_4)) goto next_358;
    struct Ty_ call_220 = meta_(noLoc_, 1);
    struct Ty_ itemTy_2 = call_220;
    struct Ty_ call_221 = tyList_(itemTy_2);
    struct Ty_ listTy_ = call_221;
    struct Ty_ call_222 = tyFun_(listTy_, listTy_);
    struct Ty_ call_223 = tyFun_(itemTy_2, call_222);
    struct TySpec_ call_224 = poly_(call_223, NULL);
    match_98 = call_224;
    goto end_match_349;
next_358:;
    if ((prim_.tag != Index_2)) goto next_359;
    struct Ty_ call_225 = meta_(noLoc_, 1);
    struct Ty_ lTy_1 = call_225;
    struct Ty_ call_226 = meta_(noLoc_, 2);
    struct Ty_ rTy_1 = call_226;
    struct Ty_ call_227 = meta_(noLoc_, 3);
    struct Ty_ resultTy_ = call_227;
    struct Ty_ call_228 = tyFun_(rTy_1, resultTy_);
    struct Ty_ call_229 = tyFun_(lTy_1, call_228);
    struct Ty_Ty_Ty_Tuple3 tuple_54;
    tuple_54.t0 = lTy_1;
    tuple_54.t1 = rTy_1;
    tuple_54.t2 = resultTy_;
    struct Ty_Ty_Ty_Tuple3* payload_32 = (struct Ty_Ty_Ty_Tuple3*)malloc(sizeof(struct Ty_Ty_Ty_Tuple3));
    (*(((struct Ty_Ty_Ty_Tuple3*)payload_32))) = tuple_54;
    struct Trait_ variant_32 = (struct Trait_){.tag = Index_1, .Index_1 = payload_32};
    struct Trait_List* list_43 = (struct Trait_List*)malloc(sizeof(struct Trait_List));
    list_43->head = variant_32;
    list_43->tail = NULL;
    struct TySpec_ call_230 = poly_(call_229, list_43);
    match_98 = call_230;
    goto end_match_349;
next_359:;
    if ((prim_.tag != Not_)) goto next_360;
    struct Ty_ call_231 = tyFun_(tyBool_, tyBool_);
    struct TySpec_ call_232 = mono_(call_231);
    match_98 = call_232;
    goto end_match_349;
next_360:;
    if ((prim_.tag != Exit_)) goto next_361;
    struct Ty_ call_233 = meta_(noLoc_, 1);
    struct Ty_ resultTy_1 = call_233;
    struct Ty_ call_234 = tyFun_(tyInt_, resultTy_1);
    struct TySpec_ call_235 = poly_(call_234, NULL);
    match_98 = call_235;
    goto end_match_349;
next_361:;
    if ((prim_.tag != Assert_)) goto next_362;
    struct Ty_ call_236 = tyFun_(tyBool_, tyUnit_);
    struct TySpec_ call_237 = mono_(call_236);
    match_98 = call_237;
    goto end_match_349;
next_362:;
    if ((prim_.tag != Box_)) goto next_363;
    struct Ty_ call_238 = meta_(noLoc_, 1);
    struct Ty_ itemTy_3 = call_238;
    struct Ty_ call_239 = tyFun_(itemTy_3, tyObj_);
    struct TySpec_ call_240 = poly_(call_239, NULL);
    match_98 = call_240;
    goto end_match_349;
next_363:;
    if ((prim_.tag != Unbox_)) goto next_364;
    struct Ty_ call_241 = meta_(noLoc_, 1);
    struct Ty_ itemTy_4 = call_241;
    struct Ty_ call_242 = tyFun_(tyObj_, itemTy_4);
    struct TySpec_ call_243 = poly_(call_242, NULL);
    match_98 = call_243;
    goto end_match_349;
next_364:;
    if ((prim_.tag != Char_3)) goto next_365;
    struct Ty_ call_244 = tyFun_(tyInt_, tyChar_);
    struct TySpec_ call_245 = mono_(call_244);
    match_98 = call_245;
    goto end_match_349;
next_365:;
    if ((prim_.tag != Int_3)) goto next_366;
    struct Ty_ call_246 = meta_(noLoc_, 1);
    struct Ty_ toIntTy_ = call_246;
    struct Ty_ call_247 = tyFun_(toIntTy_, tyInt_);
    struct Ty_* payload_33 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_33))) = toIntTy_;
    struct Trait_ variant_33 = (struct Trait_){.tag = ToInt_, .ToInt_ = payload_33};
    struct Trait_List* list_44 = (struct Trait_List*)malloc(sizeof(struct Trait_List));
    list_44->head = variant_33;
    list_44->tail = NULL;
    struct TySpec_ call_248 = poly_(call_247, list_44);
    match_98 = call_248;
    goto end_match_349;
next_366:;
    if ((prim_.tag != String_)) goto next_367;
    struct Ty_ call_249 = meta_(noLoc_, 1);
    struct Ty_ toStrTy_ = call_249;
    struct Ty_ call_250 = tyFun_(toStrTy_, tyStr_);
    struct Ty_* payload_34 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_34))) = toStrTy_;
    struct Trait_ variant_34 = (struct Trait_){.tag = ToString_, .ToString_ = payload_34};
    struct Trait_List* list_45 = (struct Trait_List*)malloc(sizeof(struct Trait_List));
    list_45->head = variant_34;
    list_45->tail = NULL;
    struct TySpec_ call_251 = poly_(call_250, list_45);
    match_98 = call_251;
    goto end_match_349;
next_367:;
    if ((prim_.tag != StrLength_)) goto next_368;
    struct Ty_ call_252 = tyFun_(tyStr_, tyInt_);
    struct TySpec_ call_253 = mono_(call_252);
    match_98 = call_253;
    goto end_match_349;
next_368:;
    if ((prim_.tag != StrGetSlice_)) goto next_370;
    struct Ty_ call_254 = tyFun_(tyStr_, tyStr_);
    struct Ty_ call_255 = tyFun_(tyInt_, call_254);
    struct Ty_ call_256 = tyFun_(tyInt_, call_255);
    struct TySpec_ call_257 = mono_(call_256);
    match_98 = call_257;
    goto end_match_349;
next_370:;
    if ((prim_.tag != Printfn_)) goto next_371;
    goto match_body_369;
next_371:;
    if ((prim_.tag != NativeFun_)) goto next_372;
    goto match_body_369;
match_body_369:;
    struct Ty_ call_258 = meta_(noLoc_, 1);
    struct TySpec_ call_259 = poly_(call_258, NULL);
    match_98 = call_259;
    goto end_match_349;
next_372:;
end_match_349:;
    return match_98;
}

struct HPat_ListTy_IntIntTuple2Tuple3 {
    struct HPat_List* t0;
    struct Ty_ t1;
    struct IntIntTuple2 t2;
};

struct HPat_ patUnit_(struct Ty_ tyUnit_, struct IntIntTuple2 loc_11) {
    struct HPat_ListTy_IntIntTuple2Tuple3 tuple_55;
    tuple_55.t0 = NULL;
    tuple_55.t1 = tyUnit_;
    tuple_55.t2 = loc_11;
    struct HPat_ListTy_IntIntTuple2Tuple3* payload_35 = (struct HPat_ListTy_IntIntTuple2Tuple3*)malloc(sizeof(struct HPat_ListTy_IntIntTuple2Tuple3));
    (*(((struct HPat_ListTy_IntIntTuple2Tuple3*)payload_35))) = tuple_55;
    struct HPat_ variant_35 = (struct HPat_){.tag = Tuple_2, .Tuple_2 = payload_35};
    return variant_35;
}

struct Ty_IntIntTuple2Tuple2 {
    struct Ty_ t0;
    struct IntIntTuple2 t1;
};

struct HPat_ patNil_(struct Ty_ itemTy_5, struct IntIntTuple2 loc_12) {
    struct Ty_IntIntTuple2Tuple2 tuple_56;
    tuple_56.t0 = itemTy_5;
    tuple_56.t1 = loc_12;
    struct Ty_IntIntTuple2Tuple2* payload_36 = (struct Ty_IntIntTuple2Tuple2*)malloc(sizeof(struct Ty_IntIntTuple2Tuple2));
    (*(((struct Ty_IntIntTuple2Tuple2*)payload_36))) = tuple_56;
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
    struct Ty_IntIntTuple2Tuple2 match_99;
    if ((pat_.tag != Lit_2)) goto next_374;
    struct Lit_ lit_1 = (*(pat_.Lit_2)).t0;
    struct IntIntTuple2 a_ = (*(pat_.Lit_2)).t1;
    struct Ty_ call_260 = litToTy_(tyStr_, tyChar_, tyInt_, tyBool_, lit_1);
    struct Ty_IntIntTuple2Tuple2 tuple_57;
    tuple_57.t0 = call_260;
    tuple_57.t1 = a_;
    match_99 = tuple_57;
    goto end_match_373;
next_374:;
    if ((pat_.tag != Nil_)) goto next_375;
    struct Ty_ itemTy_6 = (*(pat_.Nil_)).t0;
    struct IntIntTuple2 a_1 = (*(pat_.Nil_)).t1;
    struct Ty_ call_261 = tyList_(itemTy_6);
    struct Ty_IntIntTuple2Tuple2 tuple_58;
    tuple_58.t0 = call_261;
    tuple_58.t1 = a_1;
    match_99 = tuple_58;
    goto end_match_373;
next_375:;
    if ((pat_.tag != Discard_)) goto next_376;
    struct Ty_ ty_12 = (*(pat_.Discard_)).t0;
    struct IntIntTuple2 a_2 = (*(pat_.Discard_)).t1;
    struct Ty_IntIntTuple2Tuple2 tuple_59;
    tuple_59.t0 = ty_12;
    tuple_59.t1 = a_2;
    match_99 = tuple_59;
    goto end_match_373;
next_376:;
    if ((pat_.tag != Ref_1)) goto next_377;
    struct Ty_ ty_13 = (*(pat_.Ref_1)).t1;
    struct IntIntTuple2 a_3 = (*(pat_.Ref_1)).t2;
    struct Ty_IntIntTuple2Tuple2 tuple_60;
    tuple_60.t0 = ty_13;
    tuple_60.t1 = a_3;
    match_99 = tuple_60;
    goto end_match_373;
next_377:;
    if ((pat_.tag != Nav_2)) goto next_378;
    struct Ty_ ty_14 = (*(pat_.Nav_2)).t2;
    struct IntIntTuple2 a_4 = (*(pat_.Nav_2)).t3;
    struct Ty_IntIntTuple2Tuple2 tuple_61;
    tuple_61.t0 = ty_14;
    tuple_61.t1 = a_4;
    match_99 = tuple_61;
    goto end_match_373;
next_378:;
    if ((pat_.tag != Call_1)) goto next_379;
    struct Ty_ ty_15 = (*(pat_.Call_1)).t2;
    struct IntIntTuple2 a_5 = (*(pat_.Call_1)).t3;
    struct Ty_IntIntTuple2Tuple2 tuple_62;
    tuple_62.t0 = ty_15;
    tuple_62.t1 = a_5;
    match_99 = tuple_62;
    goto end_match_373;
next_379:;
    if ((pat_.tag != Cons_3)) goto next_380;
    struct Ty_ itemTy_7 = (*(pat_.Cons_3)).t2;
    struct IntIntTuple2 a_6 = (*(pat_.Cons_3)).t3;
    struct Ty_ call_262 = tyList_(itemTy_7);
    struct Ty_IntIntTuple2Tuple2 tuple_63;
    tuple_63.t0 = call_262;
    tuple_63.t1 = a_6;
    match_99 = tuple_63;
    goto end_match_373;
next_380:;
    if ((pat_.tag != Tuple_2)) goto next_381;
    struct Ty_ ty_16 = (*(pat_.Tuple_2)).t1;
    struct IntIntTuple2 a_7 = (*(pat_.Tuple_2)).t2;
    struct Ty_IntIntTuple2Tuple2 tuple_64;
    tuple_64.t0 = ty_16;
    tuple_64.t1 = a_7;
    match_99 = tuple_64;
    goto end_match_373;
next_381:;
    if ((pat_.tag != As_2)) goto next_382;
    struct HPat_ pat_1 = (*(pat_.As_2)).t0;
    struct IntIntTuple2 a_8 = (*(pat_.As_2)).t2;
    struct Ty_IntIntTuple2Tuple2 call_263 = patExtract_(tyStr_, tyChar_, tyInt_, tyBool_, pat_1);
    struct Ty_ ty_17 = call_263.t0;
    struct Ty_IntIntTuple2Tuple2 tuple_65;
    tuple_65.t0 = ty_17;
    tuple_65.t1 = a_8;
    match_99 = tuple_65;
    goto end_match_373;
next_382:;
    if ((pat_.tag != Anno_2)) goto next_383;
    struct Ty_ ty_18 = (*(pat_.Anno_2)).t1;
    struct IntIntTuple2 a_9 = (*(pat_.Anno_2)).t2;
    struct Ty_IntIntTuple2Tuple2 tuple_66;
    tuple_66.t0 = ty_18;
    tuple_66.t1 = a_9;
    match_99 = tuple_66;
    goto end_match_373;
next_383:;
    if ((pat_.tag != Or_3)) goto next_384;
    struct Ty_ ty_19 = (*(pat_.Or_3)).t2;
    struct IntIntTuple2 a_10 = (*(pat_.Or_3)).t3;
    struct Ty_IntIntTuple2Tuple2 tuple_67;
    tuple_67.t0 = ty_19;
    tuple_67.t1 = a_10;
    match_99 = tuple_67;
    goto end_match_373;
next_384:;
    exit(1);
end_match_373:;
    return match_99;
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
    struct HPat_ call_264 = go_38(arg_17, arg_18, arg_16);
    return call_264;
}

struct HPat_ fun_11(void* env_5, struct HPat_ arg_19) {
    struct IntIntTuple2IntIntTuple2Fun1 arg_20 = (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)env_5))).t0;
    struct Ty_Ty_Fun1 arg_21 = (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)env_5))).t1;
    struct HPat_ call_265 = go_38(arg_20, arg_21, arg_19);
    return call_265;
}

struct HPat_ go_38(struct IntIntTuple2IntIntTuple2Fun1 g_, struct Ty_Ty_Fun1 f_10, struct HPat_ pat_3) {
    struct HPat_ match_100;
    if ((pat_3.tag != Lit_2)) goto next_386;
    struct Lit_ lit_2 = (*(pat_3.Lit_2)).t0;
    struct IntIntTuple2 a_11 = (*(pat_3.Lit_2)).t1;
    struct IntIntTuple2 app_29 = g_.fun(g_.env, a_11);
    struct Lit_IntIntTuple2Tuple2 tuple_68;
    tuple_68.t0 = lit_2;
    tuple_68.t1 = app_29;
    struct Lit_IntIntTuple2Tuple2* payload_37 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_37))) = tuple_68;
    struct HPat_ variant_37 = (struct HPat_){.tag = Lit_2, .Lit_2 = payload_37};
    match_100 = variant_37;
    goto end_match_385;
next_386:;
    if ((pat_3.tag != Nil_)) goto next_387;
    struct Ty_ itemTy_8 = (*(pat_3.Nil_)).t0;
    struct IntIntTuple2 a_12 = (*(pat_3.Nil_)).t1;
    struct Ty_ app_30 = f_10.fun(f_10.env, itemTy_8);
    struct IntIntTuple2 app_31 = g_.fun(g_.env, a_12);
    struct Ty_IntIntTuple2Tuple2 tuple_69;
    tuple_69.t0 = app_30;
    tuple_69.t1 = app_31;
    struct Ty_IntIntTuple2Tuple2* payload_38 = (struct Ty_IntIntTuple2Tuple2*)malloc(sizeof(struct Ty_IntIntTuple2Tuple2));
    (*(((struct Ty_IntIntTuple2Tuple2*)payload_38))) = tuple_69;
    struct HPat_ variant_38 = (struct HPat_){.tag = Nil_, .Nil_ = payload_38};
    match_100 = variant_38;
    goto end_match_385;
next_387:;
    if ((pat_3.tag != Discard_)) goto next_388;
    struct Ty_ ty_20 = (*(pat_3.Discard_)).t0;
    struct IntIntTuple2 a_13 = (*(pat_3.Discard_)).t1;
    struct Ty_ app_32 = f_10.fun(f_10.env, ty_20);
    struct IntIntTuple2 app_33 = g_.fun(g_.env, a_13);
    struct Ty_IntIntTuple2Tuple2 tuple_70;
    tuple_70.t0 = app_32;
    tuple_70.t1 = app_33;
    struct Ty_IntIntTuple2Tuple2* payload_39 = (struct Ty_IntIntTuple2Tuple2*)malloc(sizeof(struct Ty_IntIntTuple2Tuple2));
    (*(((struct Ty_IntIntTuple2Tuple2*)payload_39))) = tuple_70;
    struct HPat_ variant_39 = (struct HPat_){.tag = Discard_, .Discard_ = payload_39};
    match_100 = variant_39;
    goto end_match_385;
next_388:;
    if ((pat_3.tag != Ref_1)) goto next_389;
    int serial_4 = (*(pat_3.Ref_1)).t0;
    struct Ty_ ty_21 = (*(pat_3.Ref_1)).t1;
    struct IntIntTuple2 a_14 = (*(pat_3.Ref_1)).t2;
    struct Ty_ app_34 = f_10.fun(f_10.env, ty_21);
    struct IntIntTuple2 app_35 = g_.fun(g_.env, a_14);
    struct IntTy_IntIntTuple2Tuple3 tuple_71;
    tuple_71.t0 = serial_4;
    tuple_71.t1 = app_34;
    tuple_71.t2 = app_35;
    struct IntTy_IntIntTuple2Tuple3* payload_40 = (struct IntTy_IntIntTuple2Tuple3*)malloc(sizeof(struct IntTy_IntIntTuple2Tuple3));
    (*(((struct IntTy_IntIntTuple2Tuple3*)payload_40))) = tuple_71;
    struct HPat_ variant_40 = (struct HPat_){.tag = Ref_1, .Ref_1 = payload_40};
    match_100 = variant_40;
    goto end_match_385;
next_389:;
    if ((pat_3.tag != Nav_2)) goto next_390;
    struct HPat_ pat_4 = (*(pat_3.Nav_2)).t0;
    struct String ident_7 = (*(pat_3.Nav_2)).t1;
    struct Ty_ ty_22 = (*(pat_3.Nav_2)).t2;
    struct IntIntTuple2 a_15 = (*(pat_3.Nav_2)).t3;
    struct Ty_ app_36 = f_10.fun(f_10.env, ty_22);
    struct IntIntTuple2 app_37 = g_.fun(g_.env, a_15);
    struct HPat_StringTy_IntIntTuple2Tuple4 tuple_72;
    tuple_72.t0 = pat_4;
    tuple_72.t1 = ident_7;
    tuple_72.t2 = app_36;
    tuple_72.t3 = app_37;
    struct HPat_StringTy_IntIntTuple2Tuple4* payload_41 = (struct HPat_StringTy_IntIntTuple2Tuple4*)malloc(sizeof(struct HPat_StringTy_IntIntTuple2Tuple4));
    (*(((struct HPat_StringTy_IntIntTuple2Tuple4*)payload_41))) = tuple_72;
    struct HPat_ variant_41 = (struct HPat_){.tag = Nav_2, .Nav_2 = payload_41};
    match_100 = variant_41;
    goto end_match_385;
next_390:;
    if ((pat_3.tag != Call_1)) goto next_391;
    struct HPat_ callee_ = (*(pat_3.Call_1)).t0;
    struct HPat_List* args_ = (*(pat_3.Call_1)).t1;
    struct Ty_ ty_23 = (*(pat_3.Call_1)).t2;
    struct IntIntTuple2 a_16 = (*(pat_3.Call_1)).t3;
    struct HPat_ call_266 = go_38(g_, f_10, callee_);
    struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2 tuple_74;
    tuple_74.t0 = g_;
    tuple_74.t1 = f_10;
    void* box_1 = (void*)malloc(sizeof(struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2));
    (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)box_1))) = tuple_74;
    void* env_40 = box_1;
    struct HPat_HPat_Fun1 fun_46 = (struct HPat_HPat_Fun1){.fun = fun_10, .env = env_40};
    struct HPat_List* call_267 = listMap_8(fun_46, args_);
    struct Ty_ app_38 = f_10.fun(f_10.env, ty_23);
    struct IntIntTuple2 app_39 = g_.fun(g_.env, a_16);
    struct HPat_HPat_ListTy_IntIntTuple2Tuple4 tuple_73;
    tuple_73.t0 = call_266;
    tuple_73.t1 = call_267;
    tuple_73.t2 = app_38;
    tuple_73.t3 = app_39;
    struct HPat_HPat_ListTy_IntIntTuple2Tuple4* payload_42 = (struct HPat_HPat_ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct HPat_HPat_ListTy_IntIntTuple2Tuple4));
    (*(((struct HPat_HPat_ListTy_IntIntTuple2Tuple4*)payload_42))) = tuple_73;
    struct HPat_ variant_42 = (struct HPat_){.tag = Call_1, .Call_1 = payload_42};
    match_100 = variant_42;
    goto end_match_385;
next_391:;
    if ((pat_3.tag != Cons_3)) goto next_392;
    struct HPat_ l_10 = (*(pat_3.Cons_3)).t0;
    struct HPat_ r_23 = (*(pat_3.Cons_3)).t1;
    struct Ty_ itemTy_9 = (*(pat_3.Cons_3)).t2;
    struct IntIntTuple2 a_17 = (*(pat_3.Cons_3)).t3;
    struct HPat_ call_268 = go_38(g_, f_10, l_10);
    struct HPat_ call_269 = go_38(g_, f_10, r_23);
    struct Ty_ app_40 = f_10.fun(f_10.env, itemTy_9);
    struct IntIntTuple2 app_41 = g_.fun(g_.env, a_17);
    struct HPat_HPat_Ty_IntIntTuple2Tuple4 tuple_75;
    tuple_75.t0 = call_268;
    tuple_75.t1 = call_269;
    tuple_75.t2 = app_40;
    tuple_75.t3 = app_41;
    struct HPat_HPat_Ty_IntIntTuple2Tuple4* payload_43 = (struct HPat_HPat_Ty_IntIntTuple2Tuple4*)malloc(sizeof(struct HPat_HPat_Ty_IntIntTuple2Tuple4));
    (*(((struct HPat_HPat_Ty_IntIntTuple2Tuple4*)payload_43))) = tuple_75;
    struct HPat_ variant_43 = (struct HPat_){.tag = Cons_3, .Cons_3 = payload_43};
    match_100 = variant_43;
    goto end_match_385;
next_392:;
    if ((pat_3.tag != Tuple_2)) goto next_393;
    struct HPat_List* itemPats_ = (*(pat_3.Tuple_2)).t0;
    struct Ty_ ty_24 = (*(pat_3.Tuple_2)).t1;
    struct IntIntTuple2 a_18 = (*(pat_3.Tuple_2)).t2;
    struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2 tuple_77;
    tuple_77.t0 = g_;
    tuple_77.t1 = f_10;
    void* box_2 = (void*)malloc(sizeof(struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2));
    (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)box_2))) = tuple_77;
    void* env_41 = box_2;
    struct HPat_HPat_Fun1 fun_47 = (struct HPat_HPat_Fun1){.fun = fun_11, .env = env_41};
    struct HPat_List* call_270 = listMap_8(fun_47, itemPats_);
    struct Ty_ app_42 = f_10.fun(f_10.env, ty_24);
    struct IntIntTuple2 app_43 = g_.fun(g_.env, a_18);
    struct HPat_ListTy_IntIntTuple2Tuple3 tuple_76;
    tuple_76.t0 = call_270;
    tuple_76.t1 = app_42;
    tuple_76.t2 = app_43;
    struct HPat_ListTy_IntIntTuple2Tuple3* payload_44 = (struct HPat_ListTy_IntIntTuple2Tuple3*)malloc(sizeof(struct HPat_ListTy_IntIntTuple2Tuple3));
    (*(((struct HPat_ListTy_IntIntTuple2Tuple3*)payload_44))) = tuple_76;
    struct HPat_ variant_44 = (struct HPat_){.tag = Tuple_2, .Tuple_2 = payload_44};
    match_100 = variant_44;
    goto end_match_385;
next_393:;
    if ((pat_3.tag != As_2)) goto next_394;
    struct HPat_ pat_5 = (*(pat_3.As_2)).t0;
    int serial_5 = (*(pat_3.As_2)).t1;
    struct IntIntTuple2 a_19 = (*(pat_3.As_2)).t2;
    struct HPat_ call_271 = go_38(g_, f_10, pat_5);
    struct IntIntTuple2 app_44 = g_.fun(g_.env, a_19);
    struct HPat_IntIntIntTuple2Tuple3 tuple_78;
    tuple_78.t0 = call_271;
    tuple_78.t1 = serial_5;
    tuple_78.t2 = app_44;
    struct HPat_IntIntIntTuple2Tuple3* payload_45 = (struct HPat_IntIntIntTuple2Tuple3*)malloc(sizeof(struct HPat_IntIntIntTuple2Tuple3));
    (*(((struct HPat_IntIntIntTuple2Tuple3*)payload_45))) = tuple_78;
    struct HPat_ variant_45 = (struct HPat_){.tag = As_2, .As_2 = payload_45};
    match_100 = variant_45;
    goto end_match_385;
next_394:;
    if ((pat_3.tag != Anno_2)) goto next_395;
    struct HPat_ pat_6 = (*(pat_3.Anno_2)).t0;
    struct Ty_ ty_25 = (*(pat_3.Anno_2)).t1;
    struct IntIntTuple2 a_20 = (*(pat_3.Anno_2)).t2;
    struct HPat_ call_272 = go_38(g_, f_10, pat_6);
    struct Ty_ app_45 = f_10.fun(f_10.env, ty_25);
    struct IntIntTuple2 app_46 = g_.fun(g_.env, a_20);
    struct HPat_Ty_IntIntTuple2Tuple3 tuple_79;
    tuple_79.t0 = call_272;
    tuple_79.t1 = app_45;
    tuple_79.t2 = app_46;
    struct HPat_Ty_IntIntTuple2Tuple3* payload_46 = (struct HPat_Ty_IntIntTuple2Tuple3*)malloc(sizeof(struct HPat_Ty_IntIntTuple2Tuple3));
    (*(((struct HPat_Ty_IntIntTuple2Tuple3*)payload_46))) = tuple_79;
    struct HPat_ variant_46 = (struct HPat_){.tag = Anno_2, .Anno_2 = payload_46};
    match_100 = variant_46;
    goto end_match_385;
next_395:;
    if ((pat_3.tag != Or_3)) goto next_396;
    struct HPat_ first_2 = (*(pat_3.Or_3)).t0;
    struct HPat_ second_2 = (*(pat_3.Or_3)).t1;
    struct Ty_ ty_26 = (*(pat_3.Or_3)).t2;
    struct IntIntTuple2 a_21 = (*(pat_3.Or_3)).t3;
    struct HPat_ call_273 = go_38(g_, f_10, first_2);
    struct HPat_ call_274 = go_38(g_, f_10, second_2);
    struct Ty_ app_47 = f_10.fun(f_10.env, ty_26);
    struct IntIntTuple2 app_48 = g_.fun(g_.env, a_21);
    struct HPat_HPat_Ty_IntIntTuple2Tuple4 tuple_80;
    tuple_80.t0 = call_273;
    tuple_80.t1 = call_274;
    tuple_80.t2 = app_47;
    tuple_80.t3 = app_48;
    struct HPat_HPat_Ty_IntIntTuple2Tuple4* payload_47 = (struct HPat_HPat_Ty_IntIntTuple2Tuple4*)malloc(sizeof(struct HPat_HPat_Ty_IntIntTuple2Tuple4));
    (*(((struct HPat_HPat_Ty_IntIntTuple2Tuple4*)payload_47))) = tuple_80;
    struct HPat_ variant_47 = (struct HPat_){.tag = Or_3, .Or_3 = payload_47};
    match_100 = variant_47;
    goto end_match_385;
next_396:;
    exit(1);
end_match_385:;
    return match_100;
}

struct HPat_ patMap_(struct Ty_Ty_Fun1 f_10, struct IntIntTuple2IntIntTuple2Fun1 g_, struct HPat_ pat_2) {
    struct HPat_ call_275 = go_38(g_, f_10, pat_2);
    return call_275;
}

struct HExpr_ hxTrue_(struct Lit_ litTrue_, struct IntIntTuple2 loc_13) {
    struct Lit_IntIntTuple2Tuple2 tuple_81;
    tuple_81.t0 = litTrue_;
    tuple_81.t1 = loc_13;
    struct Lit_IntIntTuple2Tuple2* payload_48 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_48))) = tuple_81;
    struct HExpr_ variant_48 = (struct HExpr_){.tag = Lit_3, .Lit_3 = payload_48};
    return variant_48;
}

struct HExpr_ hxFalse_(struct Lit_ litFalse_, struct IntIntTuple2 loc_14) {
    struct Lit_IntIntTuple2Tuple2 tuple_82;
    tuple_82.t0 = litFalse_;
    tuple_82.t1 = loc_14;
    struct Lit_IntIntTuple2Tuple2* payload_49 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_49))) = tuple_82;
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
    struct HExpr_List* list_47 = (struct HExpr_List*)malloc(sizeof(struct HExpr_List));
    list_47->head = x_33;
    list_47->tail = NULL;
    struct HExpr_List* list_46 = (struct HExpr_List*)malloc(sizeof(struct HExpr_List));
    list_46->head = f_11;
    list_46->tail = list_47;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4 tuple_83;
    tuple_83.t0 = (struct InfOp_){.tag = App_2};
    tuple_83.t1 = list_46;
    tuple_83.t2 = ty_27;
    tuple_83.t3 = loc_15;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4* payload_50 = (struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4));
    (*(((struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)payload_50))) = tuple_83;
    struct HExpr_ variant_50 = (struct HExpr_){.tag = Inf_, .Inf_ = payload_50};
    return variant_50;
}

struct HExpr_ hxAnno_(struct HExpr_ expr_, struct Ty_ ty_28, struct IntIntTuple2 loc_16) {
    struct HExpr_List* list_48 = (struct HExpr_List*)malloc(sizeof(struct HExpr_List));
    list_48->head = expr_;
    list_48->tail = NULL;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4 tuple_84;
    tuple_84.t0 = (struct InfOp_){.tag = Anno_3};
    tuple_84.t1 = list_48;
    tuple_84.t2 = ty_28;
    tuple_84.t3 = loc_16;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4* payload_51 = (struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4));
    (*(((struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)payload_51))) = tuple_84;
    struct HExpr_ variant_51 = (struct HExpr_){.tag = Inf_, .Inf_ = payload_51};
    return variant_51;
}

struct HExpr_ hxSemi_(struct Ty_ noTy_, struct HExpr_List* items_, struct IntIntTuple2 loc_17) {
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4 tuple_85;
    tuple_85.t0 = (struct InfOp_){.tag = Semi_2};
    tuple_85.t1 = items_;
    tuple_85.t2 = noTy_;
    tuple_85.t3 = loc_17;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4* payload_52 = (struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4));
    (*(((struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)payload_52))) = tuple_85;
    struct HExpr_ variant_52 = (struct HExpr_){.tag = Inf_, .Inf_ = payload_52};
    return variant_52;
}

struct HExpr_ hxCallProc_(struct HExpr_ callee_1, struct HExpr_List* args_1, struct Ty_ resultTy_2, struct IntIntTuple2 loc_18) {
    struct HExpr_List* list_49 = (struct HExpr_List*)malloc(sizeof(struct HExpr_List));
    list_49->head = callee_1;
    list_49->tail = args_1;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4 tuple_86;
    tuple_86.t0 = (struct InfOp_){.tag = CallProc_};
    tuple_86.t1 = list_49;
    tuple_86.t2 = resultTy_2;
    tuple_86.t3 = loc_18;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4* payload_53 = (struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4));
    (*(((struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)payload_53))) = tuple_86;
    struct HExpr_ variant_53 = (struct HExpr_){.tag = Inf_, .Inf_ = payload_53};
    return variant_53;
}

struct HExpr_ hxCallClosure_(struct HExpr_ callee_2, struct HExpr_List* args_2, struct Ty_ resultTy_3, struct IntIntTuple2 loc_19) {
    struct HExpr_List* list_50 = (struct HExpr_List*)malloc(sizeof(struct HExpr_List));
    list_50->head = callee_2;
    list_50->tail = args_2;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4 tuple_87;
    tuple_87.t0 = (struct InfOp_){.tag = CallClosure_};
    tuple_87.t1 = list_50;
    tuple_87.t2 = resultTy_3;
    tuple_87.t3 = loc_19;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4* payload_54 = (struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4));
    (*(((struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)payload_54))) = tuple_87;
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
    struct Ty_ call_276 = exprToTy_(arg_23, arg_24, arg_25, arg_26, arg_27, arg_22);
    return call_276;
}

struct HExpr_ hxTuple_(struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct HExpr_List* items_1, struct IntIntTuple2 loc_20) {
    struct Ty_Ty_Ty_Ty_Ty_Tuple5 tuple_89;
    tuple_89.t0 = tyUnit_;
    tuple_89.t1 = tyStr_;
    tuple_89.t2 = tyChar_;
    tuple_89.t3 = tyInt_;
    tuple_89.t4 = tyBool_;
    void* box_3 = (void*)malloc(sizeof(struct Ty_Ty_Ty_Ty_Ty_Tuple5));
    (*(((struct Ty_Ty_Ty_Ty_Ty_Tuple5*)box_3))) = tuple_89;
    void* env_42 = box_3;
    struct HExpr_Ty_Fun1 fun_48 = (struct HExpr_Ty_Fun1){.fun = fun_12, .env = env_42};
    struct Ty_List* call_277 = listMap_11(fun_48, items_1);
    struct Ty_ call_278 = tyTuple_(call_277);
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4 tuple_88;
    tuple_88.t0 = (struct InfOp_){.tag = Tuple_3};
    tuple_88.t1 = items_1;
    tuple_88.t2 = call_278;
    tuple_88.t3 = loc_20;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4* payload_55 = (struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4));
    (*(((struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)payload_55))) = tuple_88;
    struct HExpr_ variant_55 = (struct HExpr_){.tag = Inf_, .Inf_ = payload_55};
    return variant_55;
}

struct HExpr_ hxUnit_(struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct IntIntTuple2 loc_21) {
    struct HExpr_ call_279 = hxTuple_(tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, NULL, loc_21);
    return call_279;
}

struct HPrim_Ty_IntIntTuple2Tuple3 {
    struct HPrim_ t0;
    struct Ty_ t1;
    struct IntIntTuple2 t2;
};

struct HExpr_ hxNil_(struct Ty_ itemTy_10, struct IntIntTuple2 loc_22) {
    struct Ty_ call_280 = tyList_(itemTy_10);
    struct HPrim_Ty_IntIntTuple2Tuple3 tuple_90;
    tuple_90.t0 = (struct HPrim_){.tag = Nil_1};
    tuple_90.t1 = call_280;
    tuple_90.t2 = loc_22;
    struct HPrim_Ty_IntIntTuple2Tuple3* payload_56 = (struct HPrim_Ty_IntIntTuple2Tuple3*)malloc(sizeof(struct HPrim_Ty_IntIntTuple2Tuple3));
    (*(((struct HPrim_Ty_IntIntTuple2Tuple3*)payload_56))) = tuple_90;
    struct HExpr_ variant_56 = (struct HExpr_){.tag = Prim_, .Prim_ = payload_56};
    return variant_56;
}

int hxIsUnitLit_(struct HExpr_ expr_1) {
    int match_101;
    if ((expr_1.tag != Inf_)) goto next_398;
    if (((*(expr_1.Inf_)).t0.tag != Tuple_3)) goto next_398;
    if ((!((!((*(expr_1.Inf_)).t1))))) goto next_398;
    match_101 = 1;
    goto end_match_397;
next_398:;
    match_101 = 0;
    goto end_match_397;
next_399:;
end_match_397:;
    return match_101;
}

int hxIsAlwaysTrue_(struct HExpr_ expr_2) {
    int match_102;
    if ((expr_2.tag != Lit_3)) goto next_401;
    if (((*(expr_2.Lit_3)).t0.tag != Bool_)) goto next_401;
    if ((!((*((*(expr_2.Lit_3)).t0.Bool_))))) goto next_401;
    match_102 = 1;
    goto end_match_400;
next_401:;
    match_102 = 0;
    goto end_match_400;
next_402:;
end_match_400:;
    return match_102;
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
    struct Ty_IntIntTuple2Tuple2 match_103;
    if ((expr_3.tag != Lit_3)) goto next_404;
    struct Lit_ lit_3 = (*(expr_3.Lit_3)).t0;
    struct IntIntTuple2 a_22 = (*(expr_3.Lit_3)).t1;
    struct Ty_ call_281 = litToTy_(tyStr_, tyChar_, tyInt_, tyBool_, lit_3);
    struct Ty_IntIntTuple2Tuple2 tuple_91;
    tuple_91.t0 = call_281;
    tuple_91.t1 = a_22;
    match_103 = tuple_91;
    goto end_match_403;
next_404:;
    if ((expr_3.tag != Ref_2)) goto next_405;
    struct Ty_ ty_29 = (*(expr_3.Ref_2)).t1;
    struct IntIntTuple2 a_23 = (*(expr_3.Ref_2)).t2;
    struct Ty_IntIntTuple2Tuple2 tuple_92;
    tuple_92.t0 = ty_29;
    tuple_92.t1 = a_23;
    match_103 = tuple_92;
    goto end_match_403;
next_405:;
    if ((expr_3.tag != Prim_)) goto next_406;
    struct Ty_ ty_30 = (*(expr_3.Prim_)).t1;
    struct IntIntTuple2 a_24 = (*(expr_3.Prim_)).t2;
    struct Ty_IntIntTuple2Tuple2 tuple_93;
    tuple_93.t0 = ty_30;
    tuple_93.t1 = a_24;
    match_103 = tuple_93;
    goto end_match_403;
next_406:;
    if ((expr_3.tag != Match_2)) goto next_407;
    struct Ty_ ty_31 = (*(expr_3.Match_2)).t2;
    struct IntIntTuple2 a_25 = (*(expr_3.Match_2)).t3;
    struct Ty_IntIntTuple2Tuple2 tuple_94;
    tuple_94.t0 = ty_31;
    tuple_94.t1 = a_25;
    match_103 = tuple_94;
    goto end_match_403;
next_407:;
    if ((expr_3.tag != Nav_3)) goto next_408;
    struct Ty_ ty_32 = (*(expr_3.Nav_3)).t2;
    struct IntIntTuple2 a_26 = (*(expr_3.Nav_3)).t3;
    struct Ty_IntIntTuple2Tuple2 tuple_95;
    tuple_95.t0 = ty_32;
    tuple_95.t1 = a_26;
    match_103 = tuple_95;
    goto end_match_403;
next_408:;
    if ((expr_3.tag != Inf_)) goto next_409;
    struct Ty_ ty_33 = (*(expr_3.Inf_)).t2;
    struct IntIntTuple2 a_27 = (*(expr_3.Inf_)).t3;
    struct Ty_IntIntTuple2Tuple2 tuple_96;
    tuple_96.t0 = ty_33;
    tuple_96.t1 = a_27;
    match_103 = tuple_96;
    goto end_match_403;
next_409:;
    if ((expr_3.tag != Let_2)) goto next_410;
    struct Ty_ ty_34 = (*(expr_3.Let_2)).t3;
    struct IntIntTuple2 a_28 = (*(expr_3.Let_2)).t4;
    struct Ty_IntIntTuple2Tuple2 tuple_97;
    tuple_97.t0 = ty_34;
    tuple_97.t1 = a_28;
    match_103 = tuple_97;
    goto end_match_403;
next_410:;
    if ((expr_3.tag != LetFun_1)) goto next_411;
    struct Ty_ ty_35 = (*(expr_3.LetFun_1)).t5;
    struct IntIntTuple2 a_29 = (*(expr_3.LetFun_1)).t6;
    struct Ty_IntIntTuple2Tuple2 tuple_98;
    tuple_98.t0 = ty_35;
    tuple_98.t1 = a_29;
    match_103 = tuple_98;
    goto end_match_403;
next_411:;
    if ((expr_3.tag != TyDecl_)) goto next_412;
    struct IntIntTuple2 a_30 = (*(expr_3.TyDecl_)).t2;
    struct Ty_IntIntTuple2Tuple2 tuple_99;
    tuple_99.t0 = tyUnit_;
    tuple_99.t1 = a_30;
    match_103 = tuple_99;
    goto end_match_403;
next_412:;
    if ((expr_3.tag != Open_2)) goto next_413;
    struct IntIntTuple2 a_31 = (*(expr_3.Open_2)).t1;
    struct Ty_IntIntTuple2Tuple2 tuple_100;
    tuple_100.t0 = tyUnit_;
    tuple_100.t1 = a_31;
    match_103 = tuple_100;
    goto end_match_403;
next_413:;
    if ((expr_3.tag != Error_2)) goto next_414;
    struct IntIntTuple2 a_32 = (*(expr_3.Error_2)).t1;
    struct IntIntTuple2* payload_57 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_57))) = a_32;
    struct Ty_ variant_57 = (struct Ty_){.tag = Error_1, .Error_1 = payload_57};
    struct Ty_IntIntTuple2Tuple2 tuple_101;
    tuple_101.t0 = variant_57;
    tuple_101.t1 = a_32;
    match_103 = tuple_101;
    goto end_match_403;
next_414:;
    exit(1);
end_match_403:;
    return match_103;
}

struct HPat_ goPat_(struct IntIntTuple2IntIntTuple2Fun1 g_1, struct Ty_Ty_Fun1 f_12, struct HPat_ pat_7) {
    struct HPat_ call_282 = patMap_(f_12, g_1, pat_7);
    return call_282;
}

struct HPat_HExpr_HExpr_Tuple3 fun_3(struct IntIntTuple2IntIntTuple2Fun1 g_1, struct Ty_Ty_Fun1 f_12, struct HPat_HExpr_HExpr_Tuple3 arg_117) {
    struct HPat_ pat_8 = arg_117.t0;
    struct HExpr_ guard_ = arg_117.t1;
    struct HExpr_ body_ = arg_117.t2;
    struct HPat_ call_283 = goPat_(g_1, f_12, pat_8);
    struct HExpr_ call_284 = go_39(g_1, f_12, guard_);
    struct HExpr_ call_285 = go_39(g_1, f_12, body_);
    struct HPat_HExpr_HExpr_Tuple3 tuple_102;
    tuple_102.t0 = call_283;
    tuple_102.t1 = call_284;
    tuple_102.t2 = call_285;
    return tuple_102;
}

struct HPat_HExpr_HExpr_Tuple3 fun_13(void* env_7, struct HPat_HExpr_HExpr_Tuple3 arg_28) {
    struct IntIntTuple2IntIntTuple2Fun1 arg_29 = (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)env_7))).t0;
    struct Ty_Ty_Fun1 arg_30 = (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)env_7))).t1;
    struct HPat_HExpr_HExpr_Tuple3 call_286 = fun_3(arg_29, arg_30, arg_28);
    return call_286;
}

struct HExpr_ fun_14(void* env_8, struct HExpr_ arg_31) {
    struct IntIntTuple2IntIntTuple2Fun1 arg_32 = (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)env_8))).t0;
    struct Ty_Ty_Fun1 arg_33 = (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)env_8))).t1;
    struct HExpr_ call_287 = go_39(arg_32, arg_33, arg_31);
    return call_287;
}

struct HPat_ fun_15(void* env_9, struct HPat_ arg_34) {
    struct IntIntTuple2IntIntTuple2Fun1 arg_35 = (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)env_9))).t0;
    struct Ty_Ty_Fun1 arg_36 = (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)env_9))).t1;
    struct HPat_ call_288 = goPat_(arg_35, arg_36, arg_34);
    return call_288;
}

struct HExpr_ go_39(struct IntIntTuple2IntIntTuple2Fun1 g_1, struct Ty_Ty_Fun1 f_12, struct HExpr_ expr_5) {
    struct HExpr_ match_104;
    if ((expr_5.tag != Lit_3)) goto next_416;
    struct Lit_ lit_4 = (*(expr_5.Lit_3)).t0;
    struct IntIntTuple2 a_33 = (*(expr_5.Lit_3)).t1;
    struct IntIntTuple2 app_49 = g_1.fun(g_1.env, a_33);
    struct Lit_IntIntTuple2Tuple2 tuple_103;
    tuple_103.t0 = lit_4;
    tuple_103.t1 = app_49;
    struct Lit_IntIntTuple2Tuple2* payload_58 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_58))) = tuple_103;
    struct HExpr_ variant_58 = (struct HExpr_){.tag = Lit_3, .Lit_3 = payload_58};
    match_104 = variant_58;
    goto end_match_415;
next_416:;
    if ((expr_5.tag != Ref_2)) goto next_417;
    int serial_6 = (*(expr_5.Ref_2)).t0;
    struct Ty_ ty_36 = (*(expr_5.Ref_2)).t1;
    struct IntIntTuple2 a_34 = (*(expr_5.Ref_2)).t2;
    struct Ty_ app_50 = f_12.fun(f_12.env, ty_36);
    struct IntIntTuple2 app_51 = g_1.fun(g_1.env, a_34);
    struct IntTy_IntIntTuple2Tuple3 tuple_104;
    tuple_104.t0 = serial_6;
    tuple_104.t1 = app_50;
    tuple_104.t2 = app_51;
    struct IntTy_IntIntTuple2Tuple3* payload_59 = (struct IntTy_IntIntTuple2Tuple3*)malloc(sizeof(struct IntTy_IntIntTuple2Tuple3));
    (*(((struct IntTy_IntIntTuple2Tuple3*)payload_59))) = tuple_104;
    struct HExpr_ variant_59 = (struct HExpr_){.tag = Ref_2, .Ref_2 = payload_59};
    match_104 = variant_59;
    goto end_match_415;
next_417:;
    if ((expr_5.tag != Prim_)) goto next_418;
    struct HPrim_ prim_1 = (*(expr_5.Prim_)).t0;
    struct Ty_ ty_37 = (*(expr_5.Prim_)).t1;
    struct IntIntTuple2 a_35 = (*(expr_5.Prim_)).t2;
    struct Ty_ app_52 = f_12.fun(f_12.env, ty_37);
    struct IntIntTuple2 app_53 = g_1.fun(g_1.env, a_35);
    struct HPrim_Ty_IntIntTuple2Tuple3 tuple_105;
    tuple_105.t0 = prim_1;
    tuple_105.t1 = app_52;
    tuple_105.t2 = app_53;
    struct HPrim_Ty_IntIntTuple2Tuple3* payload_60 = (struct HPrim_Ty_IntIntTuple2Tuple3*)malloc(sizeof(struct HPrim_Ty_IntIntTuple2Tuple3));
    (*(((struct HPrim_Ty_IntIntTuple2Tuple3*)payload_60))) = tuple_105;
    struct HExpr_ variant_60 = (struct HExpr_){.tag = Prim_, .Prim_ = payload_60};
    match_104 = variant_60;
    goto end_match_415;
next_418:;
    if ((expr_5.tag != Match_2)) goto next_419;
    struct HExpr_ target_ = (*(expr_5.Match_2)).t0;
    struct HPat_HExpr_HExpr_Tuple3List* arms_ = (*(expr_5.Match_2)).t1;
    struct Ty_ ty_38 = (*(expr_5.Match_2)).t2;
    struct IntIntTuple2 a_36 = (*(expr_5.Match_2)).t3;
    struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2 tuple_106;
    tuple_106.t0 = g_1;
    tuple_106.t1 = f_12;
    void* box_4 = (void*)malloc(sizeof(struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2));
    (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)box_4))) = tuple_106;
    void* env_43 = box_4;
    struct HPat_HExpr_HExpr_Tuple3HPat_HExpr_HExpr_Tuple3Fun1 fun_49 = (struct HPat_HExpr_HExpr_Tuple3HPat_HExpr_HExpr_Tuple3Fun1){.fun = fun_13, .env = env_43};
    struct HPat_HExpr_HExpr_Tuple3List* call_289 = listMap_10(fun_49, arms_);
    struct HPat_HExpr_HExpr_Tuple3List* arms_1 = call_289;
    struct HExpr_ call_290 = go_39(g_1, f_12, target_);
    struct Ty_ app_54 = f_12.fun(f_12.env, ty_38);
    struct IntIntTuple2 app_55 = g_1.fun(g_1.env, a_36);
    struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4 tuple_107;
    tuple_107.t0 = call_290;
    tuple_107.t1 = arms_1;
    tuple_107.t2 = app_54;
    tuple_107.t3 = app_55;
    struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4* payload_61 = (struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4));
    (*(((struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4*)payload_61))) = tuple_107;
    struct HExpr_ variant_61 = (struct HExpr_){.tag = Match_2, .Match_2 = payload_61};
    match_104 = variant_61;
    goto end_match_415;
next_419:;
    if ((expr_5.tag != Nav_3)) goto next_420;
    struct HExpr_ sub_ = (*(expr_5.Nav_3)).t0;
    struct String mes_ = (*(expr_5.Nav_3)).t1;
    struct Ty_ ty_39 = (*(expr_5.Nav_3)).t2;
    struct IntIntTuple2 a_37 = (*(expr_5.Nav_3)).t3;
    struct HExpr_ call_291 = go_39(g_1, f_12, sub_);
    struct Ty_ app_56 = f_12.fun(f_12.env, ty_39);
    struct IntIntTuple2 app_57 = g_1.fun(g_1.env, a_37);
    struct HExpr_StringTy_IntIntTuple2Tuple4 tuple_108;
    tuple_108.t0 = call_291;
    tuple_108.t1 = mes_;
    tuple_108.t2 = app_56;
    tuple_108.t3 = app_57;
    struct HExpr_StringTy_IntIntTuple2Tuple4* payload_62 = (struct HExpr_StringTy_IntIntTuple2Tuple4*)malloc(sizeof(struct HExpr_StringTy_IntIntTuple2Tuple4));
    (*(((struct HExpr_StringTy_IntIntTuple2Tuple4*)payload_62))) = tuple_108;
    struct HExpr_ variant_62 = (struct HExpr_){.tag = Nav_3, .Nav_3 = payload_62};
    match_104 = variant_62;
    goto end_match_415;
next_420:;
    if ((expr_5.tag != Inf_)) goto next_421;
    struct InfOp_ infOp_ = (*(expr_5.Inf_)).t0;
    struct HExpr_List* args_3 = (*(expr_5.Inf_)).t1;
    struct Ty_ resultTy_4 = (*(expr_5.Inf_)).t2;
    struct IntIntTuple2 a_38 = (*(expr_5.Inf_)).t3;
    struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2 tuple_110;
    tuple_110.t0 = g_1;
    tuple_110.t1 = f_12;
    void* box_5 = (void*)malloc(sizeof(struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2));
    (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)box_5))) = tuple_110;
    void* env_44 = box_5;
    struct HExpr_HExpr_Fun1 fun_50 = (struct HExpr_HExpr_Fun1){.fun = fun_14, .env = env_44};
    struct HExpr_List* call_292 = listMap_9(fun_50, args_3);
    struct Ty_ app_58 = f_12.fun(f_12.env, resultTy_4);
    struct IntIntTuple2 app_59 = g_1.fun(g_1.env, a_38);
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4 tuple_109;
    tuple_109.t0 = infOp_;
    tuple_109.t1 = call_292;
    tuple_109.t2 = app_58;
    tuple_109.t3 = app_59;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4* payload_63 = (struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4));
    (*(((struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)payload_63))) = tuple_109;
    struct HExpr_ variant_63 = (struct HExpr_){.tag = Inf_, .Inf_ = payload_63};
    match_104 = variant_63;
    goto end_match_415;
next_421:;
    if ((expr_5.tag != Let_2)) goto next_422;
    struct HPat_ pat_9 = (*(expr_5.Let_2)).t0;
    struct HExpr_ init_ = (*(expr_5.Let_2)).t1;
    struct HExpr_ next_6 = (*(expr_5.Let_2)).t2;
    struct Ty_ ty_40 = (*(expr_5.Let_2)).t3;
    struct IntIntTuple2 a_39 = (*(expr_5.Let_2)).t4;
    struct HPat_ call_293 = goPat_(g_1, f_12, pat_9);
    struct HExpr_ call_294 = go_39(g_1, f_12, init_);
    struct HExpr_ call_295 = go_39(g_1, f_12, next_6);
    struct Ty_ app_60 = f_12.fun(f_12.env, ty_40);
    struct IntIntTuple2 app_61 = g_1.fun(g_1.env, a_39);
    struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5 tuple_111;
    tuple_111.t0 = call_293;
    tuple_111.t1 = call_294;
    tuple_111.t2 = call_295;
    tuple_111.t3 = app_60;
    tuple_111.t4 = app_61;
    struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5* payload_64 = (struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5*)malloc(sizeof(struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5));
    (*(((struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5*)payload_64))) = tuple_111;
    struct HExpr_ variant_64 = (struct HExpr_){.tag = Let_2, .Let_2 = payload_64};
    match_104 = variant_64;
    goto end_match_415;
next_422:;
    if ((expr_5.tag != LetFun_1)) goto next_423;
    int serial_7 = (*(expr_5.LetFun_1)).t0;
    int isMainFun_ = (*(expr_5.LetFun_1)).t1;
    struct HPat_List* args_4 = (*(expr_5.LetFun_1)).t2;
    struct HExpr_ body_1 = (*(expr_5.LetFun_1)).t3;
    struct HExpr_ next_7 = (*(expr_5.LetFun_1)).t4;
    struct Ty_ ty_41 = (*(expr_5.LetFun_1)).t5;
    struct IntIntTuple2 a_40 = (*(expr_5.LetFun_1)).t6;
    struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2 tuple_113;
    tuple_113.t0 = g_1;
    tuple_113.t1 = f_12;
    void* box_6 = (void*)malloc(sizeof(struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2));
    (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)box_6))) = tuple_113;
    void* env_45 = box_6;
    struct HPat_HPat_Fun1 fun_51 = (struct HPat_HPat_Fun1){.fun = fun_15, .env = env_45};
    struct HPat_List* call_296 = listMap_8(fun_51, args_4);
    struct HExpr_ call_297 = go_39(g_1, f_12, body_1);
    struct HExpr_ call_298 = go_39(g_1, f_12, next_7);
    struct Ty_ app_62 = f_12.fun(f_12.env, ty_41);
    struct IntIntTuple2 app_63 = g_1.fun(g_1.env, a_40);
    struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7 tuple_112;
    tuple_112.t0 = serial_7;
    tuple_112.t1 = isMainFun_;
    tuple_112.t2 = call_296;
    tuple_112.t3 = call_297;
    tuple_112.t4 = call_298;
    tuple_112.t5 = app_62;
    tuple_112.t6 = app_63;
    struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7* payload_65 = (struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7*)malloc(sizeof(struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7));
    (*(((struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7*)payload_65))) = tuple_112;
    struct HExpr_ variant_65 = (struct HExpr_){.tag = LetFun_1, .LetFun_1 = payload_65};
    match_104 = variant_65;
    goto end_match_415;
next_423:;
    if ((expr_5.tag != TyDecl_)) goto next_424;
    int serial_8 = (*(expr_5.TyDecl_)).t0;
    struct TyDecl_ tyDef_1 = (*(expr_5.TyDecl_)).t1;
    struct IntIntTuple2 a_41 = (*(expr_5.TyDecl_)).t2;
    struct IntIntTuple2 app_64 = g_1.fun(g_1.env, a_41);
    struct IntTyDecl_IntIntTuple2Tuple3 tuple_114;
    tuple_114.t0 = serial_8;
    tuple_114.t1 = tyDef_1;
    tuple_114.t2 = app_64;
    struct IntTyDecl_IntIntTuple2Tuple3* payload_66 = (struct IntTyDecl_IntIntTuple2Tuple3*)malloc(sizeof(struct IntTyDecl_IntIntTuple2Tuple3));
    (*(((struct IntTyDecl_IntIntTuple2Tuple3*)payload_66))) = tuple_114;
    struct HExpr_ variant_66 = (struct HExpr_){.tag = TyDecl_, .TyDecl_ = payload_66};
    match_104 = variant_66;
    goto end_match_415;
next_424:;
    if ((expr_5.tag != Open_2)) goto next_425;
    struct StringList* path_ = (*(expr_5.Open_2)).t0;
    struct IntIntTuple2 a_42 = (*(expr_5.Open_2)).t1;
    struct IntIntTuple2 app_65 = g_1.fun(g_1.env, a_42);
    struct StringListIntIntTuple2Tuple2 tuple_115;
    tuple_115.t0 = path_;
    tuple_115.t1 = app_65;
    struct StringListIntIntTuple2Tuple2* payload_67 = (struct StringListIntIntTuple2Tuple2*)malloc(sizeof(struct StringListIntIntTuple2Tuple2));
    (*(((struct StringListIntIntTuple2Tuple2*)payload_67))) = tuple_115;
    struct HExpr_ variant_67 = (struct HExpr_){.tag = Open_2, .Open_2 = payload_67};
    match_104 = variant_67;
    goto end_match_415;
next_425:;
    if ((expr_5.tag != Error_2)) goto next_426;
    struct String error_ = (*(expr_5.Error_2)).t0;
    struct IntIntTuple2 a_43 = (*(expr_5.Error_2)).t1;
    struct IntIntTuple2 app_66 = g_1.fun(g_1.env, a_43);
    struct StringIntIntTuple2Tuple2 tuple_116;
    tuple_116.t0 = error_;
    tuple_116.t1 = app_66;
    struct StringIntIntTuple2Tuple2* payload_68 = (struct StringIntIntTuple2Tuple2*)malloc(sizeof(struct StringIntIntTuple2Tuple2));
    (*(((struct StringIntIntTuple2Tuple2*)payload_68))) = tuple_116;
    struct HExpr_ variant_68 = (struct HExpr_){.tag = Error_2, .Error_2 = payload_68};
    match_104 = variant_68;
    goto end_match_415;
next_426:;
    exit(1);
end_match_415:;
    return match_104;
}

struct HExpr_ exprMap_(struct Ty_Ty_Fun1 f_12, struct IntIntTuple2IntIntTuple2Fun1 g_1, struct HExpr_ expr_4) {
    struct HExpr_ call_299 = go_39(g_1, f_12, expr_4);
    return call_299;
}

struct Ty_ exprToTy_(struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct HExpr_ expr_6) {
    struct Ty_IntIntTuple2Tuple2 call_300 = exprExtract_(tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, expr_6);
    struct Ty_ ty_42 = call_300.t0;
    return ty_42;
}

struct IntIntTuple2 go_(int r_, struct String text_, int y_1, int x_2, int i_) {
    struct IntIntTuple2 match_105;
    if ((i_ != r_)) goto next_428;
    struct IntIntTuple2 tuple_117;
    tuple_117.t0 = y_1;
    tuple_117.t1 = x_2;
    match_105 = tuple_117;
    goto end_match_427;
next_428:;
    if ((i_ == r_)) goto next_429;
    struct IntIntTuple2 match_106;
    if ((text_.str[i_] != '\n')) goto next_431;
    struct IntIntTuple2 call_301 = go_(r_, text_, (y_1 + 1), 0, (i_ + 1));
    match_106 = call_301;
    goto end_match_430;
next_431:;
    if ((text_.str[i_] == '\n')) goto next_432;
    struct IntIntTuple2 call_302 = go_(r_, text_, y_1, (x_2 + 1), (i_ + 1));
    match_106 = call_302;
    goto end_match_430;
next_432:;
    exit(1);
end_match_430:;
    match_105 = match_106;
    goto end_match_427;
next_429:;
    exit(1);
end_match_427:;
    return match_105;
}

struct IntIntTuple2 locShift_(struct String text_, int l_, int r_, struct IntIntTuple2 arg_118) {
    int y_ = arg_118.t0;
    int x_1 = arg_118.t1;
    int match_107;
    int match_108;
    if ((l_ < 0)) goto next_435;
    match_108 = (r_ >= l_);
    goto end_match_434;
next_435:;
    if ((l_ >= 0)) goto next_436;
    match_108 = 0;
    goto end_match_434;
next_436:;
    exit(1);
end_match_434:;
    if ((!(match_108))) goto next_437;
    match_107 = (text_.len >= r_);
    goto end_match_433;
next_437:;
    if (match_108) goto next_438;
    match_107 = 0;
    goto end_match_433;
next_438:;
    exit(1);
end_match_433:;
    milone_assert(match_107, 40, 2);
    int call_303 = 0;
    struct IntIntTuple2 call_304 = go_(r_, text_, y_, x_1, l_);
    return call_304;
}

int charIsIdent_(char c_) {
    int match_109;
    int match_110;
    if ((c_ != '_')) goto next_441;
    match_110 = 1;
    goto end_match_440;
next_441:;
    if ((c_ == '_')) goto next_442;
    int call_305 = charIsDigit_(c_);
    match_110 = call_305;
    goto end_match_440;
next_442:;
    exit(1);
end_match_440:;
    if ((!(match_110))) goto next_443;
    match_109 = 1;
    goto end_match_439;
next_443:;
    if (match_110) goto next_444;
    int call_306 = charIsAlpha_(c_);
    match_109 = call_306;
    goto end_match_439;
next_444:;
    exit(1);
end_match_439:;
    return match_109;
}

int charIsOp_(char c_1) {
    int match_111;
    int match_112;
    int match_113;
    int match_114;
    int match_115;
    int match_116;
    int match_117;
    int match_118;
    int match_119;
    int match_120;
    int match_121;
    int match_122;
    int match_123;
    int match_124;
    if ((c_1 != '+')) goto next_459;
    match_124 = 1;
    goto end_match_458;
next_459:;
    if ((c_1 == '+')) goto next_460;
    match_124 = (c_1 == '-');
    goto end_match_458;
next_460:;
    exit(1);
end_match_458:;
    if ((!(match_124))) goto next_461;
    match_123 = 1;
    goto end_match_457;
next_461:;
    if (match_124) goto next_462;
    match_123 = (c_1 == '*');
    goto end_match_457;
next_462:;
    exit(1);
end_match_457:;
    if ((!(match_123))) goto next_463;
    match_122 = 1;
    goto end_match_456;
next_463:;
    if (match_123) goto next_464;
    match_122 = (c_1 == '/');
    goto end_match_456;
next_464:;
    exit(1);
end_match_456:;
    if ((!(match_122))) goto next_465;
    match_121 = 1;
    goto end_match_455;
next_465:;
    if (match_122) goto next_466;
    match_121 = (c_1 == '%');
    goto end_match_455;
next_466:;
    exit(1);
end_match_455:;
    if ((!(match_121))) goto next_467;
    match_120 = 1;
    goto end_match_454;
next_467:;
    if (match_121) goto next_468;
    match_120 = (c_1 == '=');
    goto end_match_454;
next_468:;
    exit(1);
end_match_454:;
    if ((!(match_120))) goto next_469;
    match_119 = 1;
    goto end_match_453;
next_469:;
    if (match_120) goto next_470;
    match_119 = (c_1 == '<');
    goto end_match_453;
next_470:;
    exit(1);
end_match_453:;
    if ((!(match_119))) goto next_471;
    match_118 = 1;
    goto end_match_452;
next_471:;
    if (match_119) goto next_472;
    match_118 = (c_1 == '>');
    goto end_match_452;
next_472:;
    exit(1);
end_match_452:;
    if ((!(match_118))) goto next_473;
    match_117 = 1;
    goto end_match_451;
next_473:;
    if (match_118) goto next_474;
    match_117 = (c_1 == '^');
    goto end_match_451;
next_474:;
    exit(1);
end_match_451:;
    if ((!(match_117))) goto next_475;
    match_116 = 1;
    goto end_match_450;
next_475:;
    if (match_117) goto next_476;
    match_116 = (c_1 == '&');
    goto end_match_450;
next_476:;
    exit(1);
end_match_450:;
    if ((!(match_116))) goto next_477;
    match_115 = 1;
    goto end_match_449;
next_477:;
    if (match_116) goto next_478;
    match_115 = (c_1 == '|');
    goto end_match_449;
next_478:;
    exit(1);
end_match_449:;
    if ((!(match_115))) goto next_479;
    match_114 = 1;
    goto end_match_448;
next_479:;
    if (match_115) goto next_480;
    match_114 = (c_1 == ':');
    goto end_match_448;
next_480:;
    exit(1);
end_match_448:;
    if ((!(match_114))) goto next_481;
    match_113 = 1;
    goto end_match_447;
next_481:;
    if (match_114) goto next_482;
    match_113 = (c_1 == '@');
    goto end_match_447;
next_482:;
    exit(1);
end_match_447:;
    if ((!(match_113))) goto next_483;
    match_112 = 1;
    goto end_match_446;
next_483:;
    if (match_113) goto next_484;
    match_112 = (c_1 == ';');
    goto end_match_446;
next_484:;
    exit(1);
end_match_446:;
    if ((!(match_112))) goto next_485;
    match_111 = 1;
    goto end_match_445;
next_485:;
    if (match_112) goto next_486;
    match_111 = (c_1 == '.');
    goto end_match_445;
next_486:;
    exit(1);
end_match_445:;
    return match_111;
}

int charIsPun_(char c_2) {
    int match_125;
    int match_126;
    int match_127;
    int match_128;
    if ((c_2 != ',')) goto next_491;
    match_128 = 1;
    goto end_match_490;
next_491:;
    if ((c_2 == ',')) goto next_492;
    match_128 = (c_2 == '(');
    goto end_match_490;
next_492:;
    exit(1);
end_match_490:;
    if ((!(match_128))) goto next_493;
    match_127 = 1;
    goto end_match_489;
next_493:;
    if (match_128) goto next_494;
    match_127 = (c_2 == ')');
    goto end_match_489;
next_494:;
    exit(1);
end_match_489:;
    if ((!(match_127))) goto next_495;
    match_126 = 1;
    goto end_match_488;
next_495:;
    if (match_127) goto next_496;
    match_126 = (c_2 == '[');
    goto end_match_488;
next_496:;
    exit(1);
end_match_488:;
    if ((!(match_126))) goto next_497;
    match_125 = 1;
    goto end_match_487;
next_497:;
    if (match_126) goto next_498;
    match_125 = (c_2 == ']');
    goto end_match_487;
next_498:;
    exit(1);
end_match_487:;
    return match_125;
}

int go_1(struct String s_, struct String prefix_, int pi_, int si_) {
    int match_129;
    if ((pi_ != prefix_.len)) goto next_500;
    match_129 = 1;
    goto end_match_499;
next_500:;
    if ((pi_ == prefix_.len)) goto next_501;
    int match_130;
    int match_131;
    if ((si_ >= s_.len)) goto next_504;
    match_131 = (prefix_.str[pi_] == s_.str[si_]);
    goto end_match_503;
next_504:;
    if ((si_ < s_.len)) goto next_505;
    match_131 = 0;
    goto end_match_503;
next_505:;
    exit(1);
end_match_503:;
    if ((!(match_131))) goto next_506;
    int call_307 = go_1(s_, prefix_, (pi_ + 1), (si_ + 1));
    match_130 = call_307;
    goto end_match_502;
next_506:;
    if (match_131) goto next_507;
    match_130 = 0;
    goto end_match_502;
next_507:;
    exit(1);
end_match_502:;
    match_129 = match_130;
    goto end_match_499;
next_501:;
    exit(1);
end_match_499:;
    return match_129;
}

int strIsFollowedBy_(int i_1, struct String prefix_, struct String s_) {
    int match_132;
    if ((s_.len < (i_1 + prefix_.len))) goto next_509;
    int call_308 = go_1(s_, prefix_, 0, i_1);
    match_132 = call_308;
    goto end_match_508;
next_509:;
    if ((s_.len >= (i_1 + prefix_.len))) goto next_510;
    match_132 = 0;
    goto end_match_508;
next_510:;
    exit(1);
end_match_508:;
    return match_132;
}

int strIsFollowedByRawQuotes_(int i_2, struct String s_1) {
    int call_309 = strIsFollowedBy_(i_2, (struct String){.str = "\"\"\"", .len = 3}, s_1);
    return call_309;
}

int scanError_(struct String arg_119, int i_3) {
    return (i_3 + 1);
}

int lookEof_(struct String text_1, int i_4) {
    return (i_4 >= text_1.len);
}

int lookSpace_(struct String text_2, int i_5) {
    int call_310 = charIsSpace_(text_2.str[i_5]);
    return call_310;
}

int go_2(struct String text_3, int i_7) {
    int match_133;
    int match_134;
    if ((i_7 >= text_3.len)) goto next_513;
    int call_311 = charIsSpace_(text_3.str[i_7]);
    match_134 = call_311;
    goto end_match_512;
next_513:;
    if ((i_7 < text_3.len)) goto next_514;
    match_134 = 0;
    goto end_match_512;
next_514:;
    exit(1);
end_match_512:;
    if ((!(match_134))) goto next_515;
    int call_312 = go_2(text_3, (i_7 + 1));
    match_133 = call_312;
    goto end_match_511;
next_515:;
    if (match_134) goto next_516;
    match_133 = i_7;
    goto end_match_511;
next_516:;
    exit(1);
end_match_511:;
    return match_133;
}

int scanSpace_(struct String text_3, int i_6) {
    int call_313 = lookSpace_(text_3, i_6);
    milone_assert(call_313, 103, 2);
    int call_314 = 0;
    int call_315 = go_2(text_3, i_6);
    return call_315;
}

int lookComment_(struct String text_4, int i_8) {
    int match_135;
    int call_316 = strIsFollowedBy_(i_8, (struct String){.str = "//", .len = 2}, text_4);
    if ((!(call_316))) goto next_518;
    match_135 = 1;
    goto end_match_517;
next_518:;
    if (call_316) goto next_519;
    int call_317 = strIsFollowedBy_(i_8, (struct String){.str = "[<", .len = 2}, text_4);
    match_135 = call_317;
    goto end_match_517;
next_519:;
    exit(1);
end_match_517:;
    return match_135;
}

int go_3(struct String text_5, int i_10) {
    int match_136;
    if ((i_10 != text_5.len)) goto next_521;
    match_136 = i_10;
    goto end_match_520;
next_521:;
    if ((i_10 == text_5.len)) goto next_522;
    int match_137;
    if ((text_5.str[i_10] != '\n')) goto next_524;
    match_137 = (i_10 + 1);
    goto end_match_523;
next_524:;
    if ((text_5.str[i_10] == '\n')) goto next_525;
    int call_318 = go_3(text_5, (i_10 + 1));
    match_137 = call_318;
    goto end_match_523;
next_525:;
    exit(1);
end_match_523:;
    match_136 = match_137;
    goto end_match_520;
next_522:;
    exit(1);
end_match_520:;
    return match_136;
}

int scanLine_(struct String text_5, int i_9) {
    int call_319 = lookComment_(text_5, i_9);
    milone_assert(call_319, 117, 2);
    int call_320 = 0;
    int call_321 = go_3(text_5, i_9);
    return call_321;
}

int lookPun_(struct String text_6, int i_11) {
    int call_322 = charIsPun_(text_6.str[i_11]);
    return call_322;
}

int scanPun_(struct String text_7, int i_12) {
    int call_323 = lookPun_(text_7, i_12);
    milone_assert(call_323, 131, 2);
    int call_324 = 0;
    return (i_12 + 1);
}

int lookOp_(struct String text_8, int i_13) {
    int call_325 = charIsOp_(text_8.str[i_13]);
    return call_325;
}

int go_4(struct String text_9, int i_15) {
    int match_138;
    int match_139;
    if ((i_15 >= text_9.len)) goto next_528;
    int call_326 = charIsOp_(text_9.str[i_15]);
    match_139 = call_326;
    goto end_match_527;
next_528:;
    if ((i_15 < text_9.len)) goto next_529;
    match_139 = 0;
    goto end_match_527;
next_529:;
    exit(1);
end_match_527:;
    if ((!(match_139))) goto next_530;
    int call_327 = go_4(text_9, (i_15 + 1));
    match_138 = call_327;
    goto end_match_526;
next_530:;
    if (match_139) goto next_531;
    match_138 = i_15;
    goto end_match_526;
next_531:;
    exit(1);
end_match_526:;
    return match_138;
}

int scanOp_(struct String text_9, int i_14) {
    int call_328 = lookOp_(text_9, i_14);
    milone_assert(call_328, 138, 2);
    int call_329 = 0;
    int call_330 = go_4(text_9, i_14);
    return call_330;
}

int lookIdent_(struct String text_10, int i_16) {
    int match_140;
    int call_331 = charIsIdent_(text_10.str[i_16]);
    if ((!(call_331))) goto next_533;
    int call_332 = charIsDigit_(text_10.str[i_16]);
    match_140 = (!(call_332));
    goto end_match_532;
next_533:;
    if (call_331) goto next_534;
    match_140 = 0;
    goto end_match_532;
next_534:;
    exit(1);
end_match_532:;
    return match_140;
}

int go_5(struct String text_11, int i_18) {
    int match_141;
    int match_142;
    if ((i_18 >= text_11.len)) goto next_537;
    int call_333 = charIsIdent_(text_11.str[i_18]);
    match_142 = call_333;
    goto end_match_536;
next_537:;
    if ((i_18 < text_11.len)) goto next_538;
    match_142 = 0;
    goto end_match_536;
next_538:;
    exit(1);
end_match_536:;
    if ((!(match_142))) goto next_539;
    int call_334 = go_5(text_11, (i_18 + 1));
    match_141 = call_334;
    goto end_match_535;
next_539:;
    if (match_142) goto next_540;
    match_141 = i_18;
    goto end_match_535;
next_540:;
    exit(1);
end_match_535:;
    return match_141;
}

int scanIdent_(struct String text_11, int i_17) {
    int call_335 = lookIdent_(text_11, i_17);
    milone_assert(call_335, 151, 2);
    int call_336 = 0;
    int call_337 = go_5(text_11, i_17);
    return call_337;
}

int lookIntLit_(struct String text_12, int i_19) {
    int call_338 = charIsDigit_(text_12.str[i_19]);
    return call_338;
}

int go_6(struct String text_13, int i_21) {
    int match_143;
    int match_144;
    if ((i_21 >= text_13.len)) goto next_543;
    int call_339 = charIsDigit_(text_13.str[i_21]);
    match_144 = call_339;
    goto end_match_542;
next_543:;
    if ((i_21 < text_13.len)) goto next_544;
    match_144 = 0;
    goto end_match_542;
next_544:;
    exit(1);
end_match_542:;
    if ((!(match_144))) goto next_545;
    int call_340 = go_6(text_13, (i_21 + 1));
    match_143 = call_340;
    goto end_match_541;
next_545:;
    if (match_144) goto next_546;
    match_143 = i_21;
    goto end_match_541;
next_546:;
    exit(1);
end_match_541:;
    return match_143;
}

int scanIntLit_(struct String text_13, int i_20) {
    int call_341 = lookIntLit_(text_13, i_20);
    milone_assert(call_341, 163, 2);
    int call_342 = 0;
    int call_343 = go_6(text_13, i_20);
    return call_343;
}

int lookCharLit_(struct String text_14, int i_22) {
    return (text_14.str[i_22] == '\'');
}

struct BoolIntTuple2 {
    int t0;
    int t1;
};

struct BoolIntTuple2 go_7(struct String text_15, int i_24) {
    struct BoolIntTuple2 match_145;
    int match_146;
    if (((i_24 + 1) >= text_15.len)) goto next_549;
    match_146 = (text_15.str[i_24] == '\\');
    goto end_match_548;
next_549:;
    if (((i_24 + 1) < text_15.len)) goto next_550;
    match_146 = 0;
    goto end_match_548;
next_550:;
    exit(1);
end_match_548:;
    if ((!(match_146))) goto next_551;
    struct BoolIntTuple2 call_344 = go_7(text_15, (i_24 + 2));
    match_145 = call_344;
    goto end_match_547;
next_551:;
    if (match_146) goto next_552;
    struct BoolIntTuple2 match_147;
    int match_148;
    if ((i_24 >= text_15.len)) goto next_555;
    match_148 = (text_15.str[i_24] == '\'');
    goto end_match_554;
next_555:;
    if ((i_24 < text_15.len)) goto next_556;
    match_148 = 0;
    goto end_match_554;
next_556:;
    exit(1);
end_match_554:;
    if ((!(match_148))) goto next_557;
    struct BoolIntTuple2 tuple_118;
    tuple_118.t0 = 1;
    tuple_118.t1 = (i_24 + 1);
    match_147 = tuple_118;
    goto end_match_553;
next_557:;
    if (match_148) goto next_558;
    struct BoolIntTuple2 match_149;
    int match_150;
    if ((i_24 >= text_15.len)) goto next_561;
    match_150 = (text_15.str[i_24] != '\n');
    goto end_match_560;
next_561:;
    if ((i_24 < text_15.len)) goto next_562;
    match_150 = 0;
    goto end_match_560;
next_562:;
    exit(1);
end_match_560:;
    if ((!(match_150))) goto next_563;
    struct BoolIntTuple2 call_345 = go_7(text_15, (i_24 + 1));
    match_149 = call_345;
    goto end_match_559;
next_563:;
    if (match_150) goto next_564;
    int match_151;
    if ((i_24 != text_15.len)) goto next_566;
    match_151 = 1;
    goto end_match_565;
next_566:;
    if ((i_24 == text_15.len)) goto next_567;
    match_151 = (text_15.str[i_24] == '\n');
    goto end_match_565;
next_567:;
    exit(1);
end_match_565:;
    milone_assert(match_151, 188, 6);
    int call_346 = 0;
    struct BoolIntTuple2 tuple_119;
    tuple_119.t0 = 0;
    tuple_119.t1 = i_24;
    match_149 = tuple_119;
    goto end_match_559;
next_564:;
    exit(1);
end_match_559:;
    match_147 = match_149;
    goto end_match_553;
next_558:;
    exit(1);
end_match_553:;
    match_145 = match_147;
    goto end_match_547;
next_552:;
    exit(1);
end_match_547:;
    return match_145;
}

struct BoolIntTuple2 scanCharLit_(struct String text_15, int i_23) {
    int call_347 = lookCharLit_(text_15, i_23);
    milone_assert(call_347, 175, 2);
    int call_348 = 0;
    struct BoolIntTuple2 call_349 = go_7(text_15, (i_23 + 1));
    return call_349;
}

int lookStrLit_(struct String text_16, int i_25) {
    return (text_16.str[i_25] == '\"');
}

struct BoolIntTuple2 go_8(struct String text_17, int i_27) {
    struct BoolIntTuple2 match_152;
    int match_153;
    if (((i_27 + 1) >= text_17.len)) goto next_570;
    match_153 = (text_17.str[i_27] == '\\');
    goto end_match_569;
next_570:;
    if (((i_27 + 1) < text_17.len)) goto next_571;
    match_153 = 0;
    goto end_match_569;
next_571:;
    exit(1);
end_match_569:;
    if ((!(match_153))) goto next_572;
    struct BoolIntTuple2 call_350 = go_8(text_17, (i_27 + 2));
    match_152 = call_350;
    goto end_match_568;
next_572:;
    if (match_153) goto next_573;
    struct BoolIntTuple2 match_154;
    int match_155;
    if ((i_27 >= text_17.len)) goto next_576;
    match_155 = (text_17.str[i_27] == '\"');
    goto end_match_575;
next_576:;
    if ((i_27 < text_17.len)) goto next_577;
    match_155 = 0;
    goto end_match_575;
next_577:;
    exit(1);
end_match_575:;
    if ((!(match_155))) goto next_578;
    struct BoolIntTuple2 tuple_120;
    tuple_120.t0 = 1;
    tuple_120.t1 = (i_27 + 1);
    match_154 = tuple_120;
    goto end_match_574;
next_578:;
    if (match_155) goto next_579;
    struct BoolIntTuple2 match_156;
    int match_157;
    if ((i_27 >= text_17.len)) goto next_582;
    match_157 = (text_17.str[i_27] != '\n');
    goto end_match_581;
next_582:;
    if ((i_27 < text_17.len)) goto next_583;
    match_157 = 0;
    goto end_match_581;
next_583:;
    exit(1);
end_match_581:;
    if ((!(match_157))) goto next_584;
    struct BoolIntTuple2 call_351 = go_8(text_17, (i_27 + 1));
    match_156 = call_351;
    goto end_match_580;
next_584:;
    if (match_157) goto next_585;
    int match_158;
    if ((i_27 != text_17.len)) goto next_587;
    match_158 = 1;
    goto end_match_586;
next_587:;
    if ((i_27 == text_17.len)) goto next_588;
    match_158 = (text_17.str[i_27] == '\n');
    goto end_match_586;
next_588:;
    exit(1);
end_match_586:;
    milone_assert(match_158, 209, 6);
    int call_352 = 0;
    struct BoolIntTuple2 tuple_121;
    tuple_121.t0 = 0;
    tuple_121.t1 = i_27;
    match_156 = tuple_121;
    goto end_match_580;
next_585:;
    exit(1);
end_match_580:;
    match_154 = match_156;
    goto end_match_574;
next_579:;
    exit(1);
end_match_574:;
    match_152 = match_154;
    goto end_match_568;
next_573:;
    exit(1);
end_match_568:;
    return match_152;
}

struct BoolIntTuple2 scanStrLit_(struct String text_17, int i_26) {
    int call_353 = lookStrLit_(text_17, i_26);
    milone_assert(call_353, 196, 2);
    int call_354 = 0;
    struct BoolIntTuple2 call_355 = go_8(text_17, (i_26 + 1));
    return call_355;
}

int lookStrLitRaw_(struct String text_18, int i_28) {
    int call_356 = strIsFollowedByRawQuotes_(i_28, text_18);
    return call_356;
}

struct BoolIntTuple2 go_9(struct String text_19, int i_30) {
    struct BoolIntTuple2 match_159;
    int call_357 = strIsFollowedByRawQuotes_(i_30, text_19);
    if ((!(call_357))) goto next_590;
    struct BoolIntTuple2 tuple_122;
    tuple_122.t0 = 1;
    tuple_122.t1 = (i_30 + 3);
    match_159 = tuple_122;
    goto end_match_589;
next_590:;
    if (call_357) goto next_591;
    struct BoolIntTuple2 match_160;
    if (((i_30 + 1) >= text_19.len)) goto next_593;
    struct BoolIntTuple2 call_358 = go_9(text_19, (i_30 + 1));
    match_160 = call_358;
    goto end_match_592;
next_593:;
    if (((i_30 + 1) < text_19.len)) goto next_594;
    milone_assert((i_30 == text_19.len), 224, 6);
    int call_359 = 0;
    struct BoolIntTuple2 tuple_123;
    tuple_123.t0 = 0;
    tuple_123.t1 = i_30;
    match_160 = tuple_123;
    goto end_match_592;
next_594:;
    exit(1);
end_match_592:;
    match_159 = match_160;
    goto end_match_589;
next_591:;
    exit(1);
end_match_589:;
    return match_159;
}

struct BoolIntTuple2 scanStrLitRaw_(struct String text_19, int i_29) {
    int call_360 = lookStrLitRaw_(text_19, i_29);
    milone_assert(call_360, 217, 2);
    int call_361 = 0;
    struct BoolIntTuple2 call_362 = go_9(text_19, (i_29 + 3));
    return call_362;
}

struct Token_ tokenFromIdent_(struct String text_20, int l_1, int r_1) {
    struct Token_ match_161;
    struct String call_363 = strSlice_(l_1, r_1, text_20);
    if ((str_cmp(call_363, (struct String){.str = "true", .len = 4}) != 0)) goto next_596;
    int* payload_69 = (int*)malloc(sizeof(int));
    (*(((int*)payload_69))) = 1;
    struct Token_ variant_69 = (struct Token_){.tag = Bool_1, .Bool_1 = payload_69};
    match_161 = variant_69;
    goto end_match_595;
next_596:;
    if ((str_cmp(call_363, (struct String){.str = "false", .len = 5}) != 0)) goto next_597;
    int* payload_70 = (int*)malloc(sizeof(int));
    (*(((int*)payload_70))) = 0;
    struct Token_ variant_70 = (struct Token_){.tag = Bool_1, .Bool_1 = payload_70};
    match_161 = variant_70;
    goto end_match_595;
next_597:;
    if ((str_cmp(call_363, (struct String){.str = "do", .len = 2}) != 0)) goto next_598;
    match_161 = (struct Token_){.tag = Do_};
    goto end_match_595;
next_598:;
    if ((str_cmp(call_363, (struct String){.str = "let", .len = 3}) != 0)) goto next_599;
    match_161 = (struct Token_){.tag = Let_};
    goto end_match_595;
next_599:;
    if ((str_cmp(call_363, (struct String){.str = "if", .len = 2}) != 0)) goto next_600;
    match_161 = (struct Token_){.tag = If_};
    goto end_match_595;
next_600:;
    if ((str_cmp(call_363, (struct String){.str = "then", .len = 4}) != 0)) goto next_601;
    match_161 = (struct Token_){.tag = Then_};
    goto end_match_595;
next_601:;
    if ((str_cmp(call_363, (struct String){.str = "else", .len = 4}) != 0)) goto next_602;
    match_161 = (struct Token_){.tag = Else_};
    goto end_match_595;
next_602:;
    if ((str_cmp(call_363, (struct String){.str = "match", .len = 5}) != 0)) goto next_603;
    match_161 = (struct Token_){.tag = Match_};
    goto end_match_595;
next_603:;
    if ((str_cmp(call_363, (struct String){.str = "with", .len = 4}) != 0)) goto next_604;
    match_161 = (struct Token_){.tag = With_};
    goto end_match_595;
next_604:;
    if ((str_cmp(call_363, (struct String){.str = "as", .len = 2}) != 0)) goto next_605;
    match_161 = (struct Token_){.tag = As_};
    goto end_match_595;
next_605:;
    if ((str_cmp(call_363, (struct String){.str = "when", .len = 4}) != 0)) goto next_606;
    match_161 = (struct Token_){.tag = When_};
    goto end_match_595;
next_606:;
    if ((str_cmp(call_363, (struct String){.str = "rec", .len = 3}) != 0)) goto next_607;
    match_161 = (struct Token_){.tag = Rec_};
    goto end_match_595;
next_607:;
    if ((str_cmp(call_363, (struct String){.str = "private", .len = 7}) != 0)) goto next_608;
    match_161 = (struct Token_){.tag = Private_};
    goto end_match_595;
next_608:;
    if ((str_cmp(call_363, (struct String){.str = "internal", .len = 8}) != 0)) goto next_609;
    match_161 = (struct Token_){.tag = Internal_};
    goto end_match_595;
next_609:;
    if ((str_cmp(call_363, (struct String){.str = "public", .len = 6}) != 0)) goto next_610;
    match_161 = (struct Token_){.tag = Public_};
    goto end_match_595;
next_610:;
    if ((str_cmp(call_363, (struct String){.str = "module", .len = 6}) != 0)) goto next_611;
    match_161 = (struct Token_){.tag = Module_};
    goto end_match_595;
next_611:;
    if ((str_cmp(call_363, (struct String){.str = "namespace", .len = 9}) != 0)) goto next_612;
    match_161 = (struct Token_){.tag = Namespace_};
    goto end_match_595;
next_612:;
    if ((str_cmp(call_363, (struct String){.str = "open", .len = 4}) != 0)) goto next_613;
    match_161 = (struct Token_){.tag = Open_};
    goto end_match_595;
next_613:;
    if ((str_cmp(call_363, (struct String){.str = "type", .len = 4}) != 0)) goto next_614;
    match_161 = (struct Token_){.tag = Type_};
    goto end_match_595;
next_614:;
    if ((str_cmp(call_363, (struct String){.str = "of", .len = 2}) != 0)) goto next_615;
    match_161 = (struct Token_){.tag = Of_};
    goto end_match_595;
next_615:;
    if ((str_cmp(call_363, (struct String){.str = "fun", .len = 3}) != 0)) goto next_616;
    match_161 = (struct Token_){.tag = Fun_};
    goto end_match_595;
next_616:;
    if ((str_cmp(call_363, (struct String){.str = "in", .len = 2}) != 0)) goto next_617;
    match_161 = (struct Token_){.tag = In_};
    goto end_match_595;
next_617:;
    struct String s_2 = call_363;
    struct String* payload_71 = (struct String*)malloc(sizeof(struct String));
    (*(((struct String*)payload_71))) = s_2;
    struct Token_ variant_71 = (struct Token_){.tag = Ident_, .Ident_ = payload_71};
    match_161 = variant_71;
    goto end_match_595;
next_618:;
end_match_595:;
    return match_161;
}

struct Token_ tokenFromOp_(struct String text_21, int l_2, int r_2) {
    struct Token_ match_162;
    struct String call_364 = strSlice_(l_2, r_2, text_21);
    if ((str_cmp(call_364, (struct String){.str = "&", .len = 1}) != 0)) goto next_620;
    match_162 = (struct Token_){.tag = Amp_};
    goto end_match_619;
next_620:;
    if ((str_cmp(call_364, (struct String){.str = "&&", .len = 2}) != 0)) goto next_621;
    match_162 = (struct Token_){.tag = AmpAmp_};
    goto end_match_619;
next_621:;
    if ((str_cmp(call_364, (struct String){.str = "->", .len = 2}) != 0)) goto next_622;
    match_162 = (struct Token_){.tag = Arrow_};
    goto end_match_619;
next_622:;
    if ((str_cmp(call_364, (struct String){.str = ":", .len = 1}) != 0)) goto next_623;
    match_162 = (struct Token_){.tag = Colon_};
    goto end_match_619;
next_623:;
    if ((str_cmp(call_364, (struct String){.str = "::", .len = 2}) != 0)) goto next_624;
    match_162 = (struct Token_){.tag = ColonColon_};
    goto end_match_619;
next_624:;
    if ((str_cmp(call_364, (struct String){.str = ".", .len = 1}) != 0)) goto next_625;
    match_162 = (struct Token_){.tag = Dot_};
    goto end_match_619;
next_625:;
    if ((str_cmp(call_364, (struct String){.str = "..", .len = 2}) != 0)) goto next_626;
    match_162 = (struct Token_){.tag = DotDot_};
    goto end_match_619;
next_626:;
    if ((str_cmp(call_364, (struct String){.str = "=", .len = 1}) != 0)) goto next_627;
    match_162 = (struct Token_){.tag = Eq_};
    goto end_match_619;
next_627:;
    if ((str_cmp(call_364, (struct String){.str = ">", .len = 1}) != 0)) goto next_628;
    match_162 = (struct Token_){.tag = Gt_};
    goto end_match_619;
next_628:;
    if ((str_cmp(call_364, (struct String){.str = ">=", .len = 2}) != 0)) goto next_629;
    match_162 = (struct Token_){.tag = GtEq_};
    goto end_match_619;
next_629:;
    if ((str_cmp(call_364, (struct String){.str = "<", .len = 1}) != 0)) goto next_630;
    match_162 = (struct Token_){.tag = Lt_};
    goto end_match_619;
next_630:;
    if ((str_cmp(call_364, (struct String){.str = "<=", .len = 2}) != 0)) goto next_631;
    match_162 = (struct Token_){.tag = LtEq_};
    goto end_match_619;
next_631:;
    if ((str_cmp(call_364, (struct String){.str = "<>", .len = 2}) != 0)) goto next_632;
    match_162 = (struct Token_){.tag = LtGt_};
    goto end_match_619;
next_632:;
    if ((str_cmp(call_364, (struct String){.str = "-", .len = 1}) != 0)) goto next_633;
    match_162 = (struct Token_){.tag = Minus_};
    goto end_match_619;
next_633:;
    if ((str_cmp(call_364, (struct String){.str = "%", .len = 1}) != 0)) goto next_634;
    match_162 = (struct Token_){.tag = Percent_};
    goto end_match_619;
next_634:;
    if ((str_cmp(call_364, (struct String){.str = "|", .len = 1}) != 0)) goto next_635;
    match_162 = (struct Token_){.tag = Pipe_};
    goto end_match_619;
next_635:;
    if ((str_cmp(call_364, (struct String){.str = "|>", .len = 2}) != 0)) goto next_636;
    match_162 = (struct Token_){.tag = PipeGt_};
    goto end_match_619;
next_636:;
    if ((str_cmp(call_364, (struct String){.str = "||", .len = 2}) != 0)) goto next_637;
    match_162 = (struct Token_){.tag = PipePipe_};
    goto end_match_619;
next_637:;
    if ((str_cmp(call_364, (struct String){.str = "+", .len = 1}) != 0)) goto next_638;
    match_162 = (struct Token_){.tag = Plus_};
    goto end_match_619;
next_638:;
    if ((str_cmp(call_364, (struct String){.str = ";", .len = 1}) != 0)) goto next_639;
    match_162 = (struct Token_){.tag = Semi_};
    goto end_match_619;
next_639:;
    if ((str_cmp(call_364, (struct String){.str = "*", .len = 1}) != 0)) goto next_640;
    match_162 = (struct Token_){.tag = Star_};
    goto end_match_619;
next_640:;
    if ((str_cmp(call_364, (struct String){.str = "/", .len = 1}) != 0)) goto next_641;
    match_162 = (struct Token_){.tag = Slash_};
    goto end_match_619;
next_641:;
    match_162 = (struct Token_){.tag = Error_};
    goto end_match_619;
next_642:;
end_match_619:;
    return match_162;
}

struct Token_ tokenFromPun_(struct String text_22, int l_3, int r_3) {
    milone_assert(((r_3 - l_3) == 1), 331, 2);
    int call_365 = 0;
    struct Token_ match_163;
    if ((text_22.str[l_3] != ',')) goto next_644;
    match_163 = (struct Token_){.tag = Comma_};
    goto end_match_643;
next_644:;
    if ((text_22.str[l_3] != '(')) goto next_645;
    match_163 = (struct Token_){.tag = ParenL_};
    goto end_match_643;
next_645:;
    if ((text_22.str[l_3] != ')')) goto next_646;
    match_163 = (struct Token_){.tag = ParenR_};
    goto end_match_643;
next_646:;
    if ((text_22.str[l_3] != '[')) goto next_647;
    match_163 = (struct Token_){.tag = BracketL_};
    goto end_match_643;
next_647:;
    if ((text_22.str[l_3] != ']')) goto next_648;
    match_163 = (struct Token_){.tag = BracketR_};
    goto end_match_643;
next_648:;
    struct Token_ call_366 = failwith_1((struct String){.str = "NEVER! charIsPun is broken", .len = 26});
    match_163 = call_366;
    goto end_match_643;
next_649:;
end_match_643:;
    return match_163;
}

struct Token_ tokenFromIntLit_(struct String text_23, int l_4, int r_4) {
    struct String call_367 = strSlice_(l_4, r_4, text_23);
    int call_368 = str_to_int(call_367);
    int value_ = call_368;
    int* payload_72 = (int*)malloc(sizeof(int));
    (*(((int*)payload_72))) = value_;
    struct Token_ variant_72 = (struct Token_){.tag = Int_1, .Int_1 = payload_72};
    return variant_72;
}

struct Token_ tokenFromCharLit_(char charNull_, struct String text_24, int l_5, int r_5) {
    int match_164;
    int match_165;
    if ((r_5 < (l_5 + 2))) goto next_652;
    match_165 = (text_24.str[l_5] == '\'');
    goto end_match_651;
next_652:;
    if ((r_5 >= (l_5 + 2))) goto next_653;
    match_165 = 0;
    goto end_match_651;
next_653:;
    exit(1);
end_match_651:;
    if ((!(match_165))) goto next_654;
    match_164 = (text_24.str[(r_5 - 1)] == '\'');
    goto end_match_650;
next_654:;
    if (match_165) goto next_655;
    match_164 = 0;
    goto end_match_650;
next_655:;
    exit(1);
end_match_650:;
    milone_assert(match_164, 351, 2);
    int call_369 = 0;
    int i_31 = (l_5 + 1);
    char match_166;
    if ((text_24.str[i_31] != '\\')) goto next_657;
    char match_167;
    if ((text_24.str[(i_31 + 1)] != 'x')) goto next_660;
    match_167 = charNull_;
    goto end_match_659;
next_660:;
    if ((text_24.str[(i_31 + 1)] != 't')) goto next_661;
    match_167 = '\t';
    goto end_match_659;
next_661:;
    if ((text_24.str[(i_31 + 1)] != 'r')) goto next_662;
    match_167 = '\r';
    goto end_match_659;
next_662:;
    if ((text_24.str[(i_31 + 1)] != 'n')) goto next_663;
    match_167 = '\n';
    goto end_match_659;
next_663:;
    char c_3 = text_24.str[(i_31 + 1)];
    match_167 = c_3;
    goto end_match_659;
next_664:;
end_match_659:;
    match_166 = match_167;
    goto end_match_656;
next_657:;
    char c_4 = text_24.str[i_31];
    match_166 = c_4;
    goto end_match_656;
next_658:;
end_match_656:;
    char value_1 = match_166;
    char* payload_73 = (char*)malloc(sizeof(char));
    (*(((char*)payload_73))) = value_1;
    struct Token_ variant_73 = (struct Token_){.tag = Char_1, .Char_1 = payload_73};
    return variant_73;
}

int next_(int r_6, struct String text_25, int i_33) {
    int match_168;
    int match_169;
    if ((i_33 != (r_6 - 1))) goto next_667;
    match_169 = 1;
    goto end_match_666;
next_667:;
    if ((i_33 == (r_6 - 1))) goto next_668;
    match_169 = (text_25.str[i_33] == '\\');
    goto end_match_666;
next_668:;
    exit(1);
end_match_666:;
    if ((!(match_169))) goto next_669;
    match_168 = i_33;
    goto end_match_665;
next_669:;
    if (match_169) goto next_670;
    int call_370 = next_(r_6, text_25, (i_33 + 1));
    match_168 = call_370;
    goto end_match_665;
next_670:;
    exit(1);
end_match_665:;
    return match_168;
}

struct String go_10(int r_6, struct String text_25, struct StringList* acc_, int i_32) {
    int call_371 = next_(r_6, text_25, i_32);
    int endIndex_ = call_371;
    struct String call_372 = strSlice_(i_32, endIndex_, text_25);
    struct StringList* list_51 = (struct StringList*)malloc(sizeof(struct StringList));
    list_51->head = call_372;
    list_51->tail = acc_;
    struct StringList* acc_1 = list_51;
    int i_34 = endIndex_;
    struct String match_170;
    if ((i_34 != (r_6 - 1))) goto next_672;
    struct StringList* call_373 = listRev_2(acc_1);
    struct String call_374 = strConcat_(call_373);
    match_170 = call_374;
    goto end_match_671;
next_672:;
    if ((i_34 == (r_6 - 1))) goto next_673;
    milone_assert((text_25.str[i_34] == '\\'), 394, 6);
    int call_375 = 0;
    struct String match_171;
    if ((text_25.str[(i_34 + 1)] != 'x')) goto next_675;
    struct StringList* list_52 = (struct StringList*)malloc(sizeof(struct StringList));
    list_52->head = (struct String){.str = "\0", .len = 1};
    list_52->tail = acc_1;
    struct String call_376 = go_10(r_6, text_25, list_52, (i_34 + 4));
    match_171 = call_376;
    goto end_match_674;
next_675:;
    if ((text_25.str[(i_34 + 1)] != 't')) goto next_676;
    struct StringList* list_53 = (struct StringList*)malloc(sizeof(struct StringList));
    list_53->head = (struct String){.str = "\t", .len = 1};
    list_53->tail = acc_1;
    struct String call_377 = go_10(r_6, text_25, list_53, (i_34 + 2));
    match_171 = call_377;
    goto end_match_674;
next_676:;
    if ((text_25.str[(i_34 + 1)] != 'r')) goto next_677;
    struct StringList* list_54 = (struct StringList*)malloc(sizeof(struct StringList));
    list_54->head = (struct String){.str = "\r", .len = 1};
    list_54->tail = acc_1;
    struct String call_378 = go_10(r_6, text_25, list_54, (i_34 + 2));
    match_171 = call_378;
    goto end_match_674;
next_677:;
    if ((text_25.str[(i_34 + 1)] != 'n')) goto next_678;
    struct StringList* list_55 = (struct StringList*)malloc(sizeof(struct StringList));
    list_55->head = (struct String){.str = "\n", .len = 1};
    list_55->tail = acc_1;
    struct String call_379 = go_10(r_6, text_25, list_55, (i_34 + 2));
    match_171 = call_379;
    goto end_match_674;
next_678:;
    struct String call_380 = strSlice_((i_34 + 1), (i_34 + 2), text_25);
    struct StringList* list_56 = (struct StringList*)malloc(sizeof(struct StringList));
    list_56->head = call_380;
    list_56->tail = acc_1;
    struct String call_381 = go_10(r_6, text_25, list_56, (i_34 + 2));
    match_171 = call_381;
    goto end_match_674;
next_679:;
end_match_674:;
    match_170 = match_171;
    goto end_match_671;
next_673:;
    exit(1);
end_match_671:;
    return match_170;
}

struct Token_ tokenFromStrLit_(struct String text_25, int l_6, int r_6) {
    int match_172;
    int match_173;
    if ((r_6 < (l_6 + 2))) goto next_682;
    match_173 = (text_25.str[l_6] == '\"');
    goto end_match_681;
next_682:;
    if ((r_6 >= (l_6 + 2))) goto next_683;
    match_173 = 0;
    goto end_match_681;
next_683:;
    exit(1);
end_match_681:;
    if ((!(match_173))) goto next_684;
    match_172 = (text_25.str[(r_6 - 1)] == '\"');
    goto end_match_680;
next_684:;
    if (match_173) goto next_685;
    match_172 = 0;
    goto end_match_680;
next_685:;
    exit(1);
end_match_680:;
    milone_assert(match_172, 375, 2);
    int call_382 = 0;
    struct String call_383 = go_10(r_6, text_25, NULL, (l_6 + 1));
    struct String value_2 = call_383;
    struct String* payload_74 = (struct String*)malloc(sizeof(struct String));
    (*(((struct String*)payload_74))) = value_2;
    struct Token_ variant_74 = (struct Token_){.tag = Str_1, .Str_1 = payload_74};
    return variant_74;
}

struct Token_ tokenFromStrLitRaw_(struct String text_26, int l_7, int r_7) {
    int match_174;
    int match_175;
    if ((r_7 < (l_7 + 6))) goto next_688;
    int call_384 = strIsFollowedByRawQuotes_(l_7, text_26);
    match_175 = call_384;
    goto end_match_687;
next_688:;
    if ((r_7 >= (l_7 + 6))) goto next_689;
    match_175 = 0;
    goto end_match_687;
next_689:;
    exit(1);
end_match_687:;
    if ((!(match_175))) goto next_690;
    int call_385 = strIsFollowedByRawQuotes_((r_7 - 3), text_26);
    match_174 = call_385;
    goto end_match_686;
next_690:;
    if (match_175) goto next_691;
    match_174 = 0;
    goto end_match_686;
next_691:;
    exit(1);
end_match_686:;
    milone_assert(match_174, 411, 2);
    int call_386 = 0;
    struct String call_387 = strSlice_((l_7 + 3), (r_7 - 3), text_26);
    struct String* payload_75 = (struct String*)malloc(sizeof(struct String));
    (*(((struct String*)payload_75))) = call_387;
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

struct StringIntTuple2 tokCtxToTextIndex_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 arg_120) {
    struct String text_27 = arg_120.t0;
    int i_35 = arg_120.t1;
    struct StringIntTuple2 tuple_124;
    tuple_124.t0 = text_27;
    tuple_124.t1 = i_35;
    return tuple_124;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokCtxSkip_(int r_8, struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 arg_121) {
    struct String text_28 = arg_121.t0;
    int i_36 = arg_121.t1;
    struct IntIntTuple2 loc_ = arg_121.t2;
    struct Token_IntIntTuple2Tuple2List* acc_2 = arg_121.t3;
    int match_176;
    int match_177;
    if ((i_36 < 0)) goto next_694;
    match_177 = (r_8 >= i_36);
    goto end_match_693;
next_694:;
    if ((i_36 >= 0)) goto next_695;
    match_177 = 0;
    goto end_match_693;
next_695:;
    exit(1);
end_match_693:;
    if ((!(match_177))) goto next_696;
    match_176 = (text_28.len >= r_8);
    goto end_match_692;
next_696:;
    if (match_177) goto next_697;
    match_176 = 0;
    goto end_match_692;
next_697:;
    exit(1);
end_match_692:;
    milone_assert(match_176, 424, 2);
    int call_388 = 0;
    struct IntIntTuple2 call_389 = locShift_(text_28, i_36, r_8, loc_);
    struct IntIntTuple2 newLoc_ = call_389;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tuple_125;
    tuple_125.t0 = text_28;
    tuple_125.t1 = r_8;
    tuple_125.t2 = newLoc_;
    tuple_125.t3 = acc_2;
    return tuple_125;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokCtxPush_(struct Token_ kind_, int r_9, struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 arg_122) {
    struct String text_29 = arg_122.t0;
    int i_37 = arg_122.t1;
    struct IntIntTuple2 loc_1 = arg_122.t2;
    struct Token_IntIntTuple2Tuple2List* acc_3 = arg_122.t3;
    int match_178;
    int match_179;
    if ((i_37 < 0)) goto next_700;
    match_179 = (r_9 >= i_37);
    goto end_match_699;
next_700:;
    if ((i_37 >= 0)) goto next_701;
    match_179 = 0;
    goto end_match_699;
next_701:;
    exit(1);
end_match_699:;
    if ((!(match_179))) goto next_702;
    match_178 = (text_29.len >= r_9);
    goto end_match_698;
next_702:;
    if (match_179) goto next_703;
    match_178 = 0;
    goto end_match_698;
next_703:;
    exit(1);
end_match_698:;
    milone_assert(match_178, 431, 2);
    int call_390 = 0;
    struct Token_IntIntTuple2Tuple2 tuple_126;
    tuple_126.t0 = kind_;
    tuple_126.t1 = loc_1;
    struct Token_IntIntTuple2Tuple2List* list_57 = (struct Token_IntIntTuple2Tuple2List*)malloc(sizeof(struct Token_IntIntTuple2Tuple2List));
    list_57->head = tuple_126;
    list_57->tail = acc_3;
    struct Token_IntIntTuple2Tuple2List* newAcc_ = list_57;
    struct IntIntTuple2 call_391 = locShift_(text_29, i_37, r_9, loc_1);
    struct IntIntTuple2 newLoc_1 = call_391;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tuple_127;
    tuple_127.t0 = text_29;
    tuple_127.t1 = r_9;
    tuple_127.t2 = newLoc_1;
    tuple_127.t3 = newAcc_;
    return tuple_127;
}

struct Token_IntIntTuple2Tuple2List* tokEof_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 arg_123) {
    struct String text_30 = arg_123.t0;
    int i_38 = arg_123.t1;
    struct Token_IntIntTuple2Tuple2List* acc_4 = arg_123.t3;
    int call_392 = lookEof_(text_30, i_38);
    milone_assert(call_392, 437, 2);
    int call_393 = 0;
    struct Token_IntIntTuple2Tuple2List* call_394 = listRev_7(acc_4);
    return call_394;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokError_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_) {
    struct StringIntTuple2 call_395 = tokCtxToTextIndex_(t_);
    struct String text_31 = call_395.t0;
    int i_39 = call_395.t1;
    int call_396 = scanError_(text_31, i_39);
    int r_10 = call_396;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_397 = tokCtxSkip_(r_10, t_);
    return call_397;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokComment_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_1) {
    struct StringIntTuple2 call_398 = tokCtxToTextIndex_(t_1);
    struct String text_32 = call_398.t0;
    int i_40 = call_398.t1;
    int call_399 = scanLine_(text_32, i_40);
    int r_11 = call_399;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_400 = tokCtxSkip_(r_11, t_1);
    return call_400;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokSpace_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_2) {
    struct StringIntTuple2 call_401 = tokCtxToTextIndex_(t_2);
    struct String text_33 = call_401.t0;
    int i_41 = call_401.t1;
    int call_402 = scanSpace_(text_33, i_41);
    int r_12 = call_402;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_403 = tokCtxSkip_(r_12, t_2);
    return call_403;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokPun_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_3) {
    struct StringIntTuple2 call_404 = tokCtxToTextIndex_(t_3);
    struct String text_34 = call_404.t0;
    int i_42 = call_404.t1;
    int call_405 = scanPun_(text_34, i_42);
    int r_13 = call_405;
    struct Token_ call_406 = tokenFromPun_(text_34, i_42, r_13);
    struct Token_ token_ = call_406;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_407 = tokCtxPush_(token_, r_13, t_3);
    return call_407;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokOp_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_4) {
    struct StringIntTuple2 call_408 = tokCtxToTextIndex_(t_4);
    struct String text_35 = call_408.t0;
    int i_43 = call_408.t1;
    int call_409 = scanOp_(text_35, i_43);
    int r_14 = call_409;
    struct Token_ call_410 = tokenFromOp_(text_35, i_43, r_14);
    struct Token_ token_1 = call_410;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_411 = tokCtxPush_(token_1, r_14, t_4);
    return call_411;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokIdent_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_5) {
    struct StringIntTuple2 call_412 = tokCtxToTextIndex_(t_5);
    struct String text_36 = call_412.t0;
    int i_44 = call_412.t1;
    int call_413 = scanIdent_(text_36, i_44);
    int r_15 = call_413;
    struct Token_ call_414 = tokenFromIdent_(text_36, i_44, r_15);
    struct Token_ token_2 = call_414;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_415 = tokCtxPush_(token_2, r_15, t_5);
    return call_415;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokIntLit_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_6) {
    struct StringIntTuple2 call_416 = tokCtxToTextIndex_(t_6);
    struct String text_37 = call_416.t0;
    int i_45 = call_416.t1;
    int call_417 = scanIntLit_(text_37, i_45);
    int r_16 = call_417;
    struct Token_ call_418 = tokenFromIntLit_(text_37, i_45, r_16);
    struct Token_ token_3 = call_418;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_419 = tokCtxPush_(token_3, r_16, t_6);
    return call_419;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokCharLit_(char charNull_, struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_7) {
    struct StringIntTuple2 call_420 = tokCtxToTextIndex_(t_7);
    struct String text_38 = call_420.t0;
    int i_46 = call_420.t1;
    struct BoolIntTuple2 call_421 = scanCharLit_(text_38, i_46);
    int ok_ = call_421.t0;
    int r_17 = call_421.t1;
    struct Token_ match_180;
    if ((!(ok_))) goto next_705;
    struct Token_ call_422 = tokenFromCharLit_(charNull_, text_38, i_46, r_17);
    match_180 = call_422;
    goto end_match_704;
next_705:;
    if (ok_) goto next_706;
    match_180 = (struct Token_){.tag = Error_};
    goto end_match_704;
next_706:;
    exit(1);
end_match_704:;
    struct Token_ token_4 = match_180;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_423 = tokCtxPush_(token_4, r_17, t_7);
    return call_423;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokStrLit_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_8) {
    struct StringIntTuple2 call_424 = tokCtxToTextIndex_(t_8);
    struct String text_39 = call_424.t0;
    int i_47 = call_424.t1;
    struct BoolIntTuple2 call_425 = scanStrLit_(text_39, i_47);
    int ok_1 = call_425.t0;
    int r_18 = call_425.t1;
    struct Token_ match_181;
    if ((!(ok_1))) goto next_708;
    struct Token_ call_426 = tokenFromStrLit_(text_39, i_47, r_18);
    match_181 = call_426;
    goto end_match_707;
next_708:;
    if (ok_1) goto next_709;
    match_181 = (struct Token_){.tag = Error_};
    goto end_match_707;
next_709:;
    exit(1);
end_match_707:;
    struct Token_ token_5 = match_181;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_427 = tokCtxPush_(token_5, r_18, t_8);
    return call_427;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokStrLitRaw_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_9) {
    struct StringIntTuple2 call_428 = tokCtxToTextIndex_(t_9);
    struct String text_40 = call_428.t0;
    int i_48 = call_428.t1;
    struct BoolIntTuple2 call_429 = scanStrLitRaw_(text_40, i_48);
    int ok_2 = call_429.t0;
    int r_19 = call_429.t1;
    struct Token_ match_182;
    if ((!(ok_2))) goto next_711;
    struct Token_ call_430 = tokenFromStrLitRaw_(text_40, i_48, r_19);
    match_182 = call_430;
    goto end_match_710;
next_711:;
    if (ok_2) goto next_712;
    match_182 = (struct Token_){.tag = Error_};
    goto end_match_710;
next_712:;
    exit(1);
end_match_710:;
    struct Token_ token_6 = match_182;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_431 = tokCtxPush_(token_6, r_19, t_9);
    return call_431;
}

struct Token_IntIntTuple2Tuple2List* go_11(char charNull_, struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_10) {
    struct StringIntTuple2 call_432 = tokCtxToTextIndex_(t_10);
    struct String text_42 = call_432.t0;
    int i_49 = call_432.t1;
    struct Token_IntIntTuple2Tuple2List* match_183;
    int call_433 = lookEof_(text_42, i_49);
    if ((!(call_433))) goto next_714;
    struct Token_IntIntTuple2Tuple2List* call_434 = tokEof_(t_10);
    match_183 = call_434;
    goto end_match_713;
next_714:;
    if (call_433) goto next_715;
    struct Token_IntIntTuple2Tuple2List* match_184;
    int call_435 = lookComment_(text_42, i_49);
    if ((!(call_435))) goto next_717;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_436 = tokComment_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_437 = go_11(charNull_, call_436);
    match_184 = call_437;
    goto end_match_716;
next_717:;
    if (call_435) goto next_718;
    struct Token_IntIntTuple2Tuple2List* match_185;
    int call_438 = lookSpace_(text_42, i_49);
    if ((!(call_438))) goto next_720;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_439 = tokSpace_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_440 = go_11(charNull_, call_439);
    match_185 = call_440;
    goto end_match_719;
next_720:;
    if (call_438) goto next_721;
    struct Token_IntIntTuple2Tuple2List* match_186;
    int call_441 = lookOp_(text_42, i_49);
    if ((!(call_441))) goto next_723;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_442 = tokOp_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_443 = go_11(charNull_, call_442);
    match_186 = call_443;
    goto end_match_722;
next_723:;
    if (call_441) goto next_724;
    struct Token_IntIntTuple2Tuple2List* match_187;
    int call_444 = lookIntLit_(text_42, i_49);
    if ((!(call_444))) goto next_726;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_445 = tokIntLit_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_446 = go_11(charNull_, call_445);
    match_187 = call_446;
    goto end_match_725;
next_726:;
    if (call_444) goto next_727;
    struct Token_IntIntTuple2Tuple2List* match_188;
    int call_447 = lookIdent_(text_42, i_49);
    if ((!(call_447))) goto next_729;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_448 = tokIdent_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_449 = go_11(charNull_, call_448);
    match_188 = call_449;
    goto end_match_728;
next_729:;
    if (call_447) goto next_730;
    struct Token_IntIntTuple2Tuple2List* match_189;
    int call_450 = lookCharLit_(text_42, i_49);
    if ((!(call_450))) goto next_732;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_451 = tokCharLit_(charNull_, t_10);
    struct Token_IntIntTuple2Tuple2List* call_452 = go_11(charNull_, call_451);
    match_189 = call_452;
    goto end_match_731;
next_732:;
    if (call_450) goto next_733;
    struct Token_IntIntTuple2Tuple2List* match_190;
    int call_453 = lookStrLitRaw_(text_42, i_49);
    if ((!(call_453))) goto next_735;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_454 = tokStrLitRaw_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_455 = go_11(charNull_, call_454);
    match_190 = call_455;
    goto end_match_734;
next_735:;
    if (call_453) goto next_736;
    struct Token_IntIntTuple2Tuple2List* match_191;
    int call_456 = lookStrLit_(text_42, i_49);
    if ((!(call_456))) goto next_738;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_457 = tokStrLit_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_458 = go_11(charNull_, call_457);
    match_191 = call_458;
    goto end_match_737;
next_738:;
    if (call_456) goto next_739;
    struct Token_IntIntTuple2Tuple2List* match_192;
    int call_459 = lookPun_(text_42, i_49);
    if ((!(call_459))) goto next_741;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_460 = tokPun_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_461 = go_11(charNull_, call_460);
    match_192 = call_461;
    goto end_match_740;
next_741:;
    if (call_459) goto next_742;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_462 = tokError_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_463 = go_11(charNull_, call_462);
    match_192 = call_463;
    goto end_match_740;
next_742:;
    exit(1);
end_match_740:;
    match_191 = match_192;
    goto end_match_737;
next_739:;
    exit(1);
end_match_737:;
    match_190 = match_191;
    goto end_match_734;
next_736:;
    exit(1);
end_match_734:;
    match_189 = match_190;
    goto end_match_731;
next_733:;
    exit(1);
end_match_731:;
    match_188 = match_189;
    goto end_match_728;
next_730:;
    exit(1);
end_match_728:;
    match_187 = match_188;
    goto end_match_725;
next_727:;
    exit(1);
end_match_725:;
    match_186 = match_187;
    goto end_match_722;
next_724:;
    exit(1);
end_match_722:;
    match_185 = match_186;
    goto end_match_719;
next_721:;
    exit(1);
end_match_719:;
    match_184 = match_185;
    goto end_match_716;
next_718:;
    exit(1);
end_match_716:;
    match_183 = match_184;
    goto end_match_713;
next_715:;
    exit(1);
end_match_713:;
    return match_183;
}

struct Token_IntIntTuple2Tuple2List* tokenize_(char charNull_, struct String text_41) {
    struct IntIntTuple2 tuple_129;
    tuple_129.t0 = 0;
    tuple_129.t1 = 0;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tuple_128;
    tuple_128.t0 = text_41;
    tuple_128.t1 = 0;
    tuple_128.t2 = tuple_129;
    tuple_128.t3 = NULL;
    struct Token_IntIntTuple2Tuple2List* call_464 = go_11(charNull_, tuple_128);
    return call_464;
}

int leadsExpr_1(struct Token_IntIntTuple2Tuple2List* tokens_1) {
    int match_193;
    if ((!(tokens_1))) goto next_744;
    struct Token_ token_14 = tokens_1->head.t0;
    int call_465 = tokenIsExprFirst_(token_14);
    match_193 = call_465;
    goto end_match_743;
next_744:;
    match_193 = 0;
    goto end_match_743;
next_745:;
end_match_743:;
    return match_193;
}

int leadsArg_1(struct Token_IntIntTuple2Tuple2List* tokens_2) {
    int match_194;
    if ((!(tokens_2))) goto next_747;
    struct Token_ token_15 = tokens_2->head.t0;
    int call_466 = tokenIsArgFirst_(token_15);
    match_194 = call_466;
    goto end_match_746;
next_747:;
    match_194 = 0;
    goto end_match_746;
next_748:;
end_match_746:;
    return match_194;
}

int leadsPat_1(struct Token_IntIntTuple2Tuple2List* tokens_3) {
    int match_195;
    if ((!(tokens_3))) goto next_750;
    struct Token_ token_16 = tokens_3->head.t0;
    int call_467 = tokenIsPatFirst_(token_16);
    match_195 = call_467;
    goto end_match_749;
next_750:;
    match_195 = 0;
    goto end_match_749;
next_751:;
end_match_749:;
    return match_195;
}

struct IntIntTuple2 nextLoc_1(struct Token_IntIntTuple2Tuple2List* tokens_4) {
    struct IntIntTuple2 match_196;
    if ((!((!(tokens_4))))) goto next_753;
    struct IntIntTuple2 tuple_130;
    tuple_130.t0 = (0 - 1);
    tuple_130.t1 = 0;
    match_196 = tuple_130;
    goto end_match_752;
next_753:;
    if ((!(tokens_4))) goto next_754;
    struct IntIntTuple2 loc_27 = tokens_4->head.t1;
    match_196 = loc_27;
    goto end_match_752;
next_754:;
    exit(1);
end_match_752:;
    return match_196;
}

int nextInside_1(struct IntIntTuple2 baseLoc_, struct Token_IntIntTuple2Tuple2List* tokens_5) {
    int match_197;
    if ((!((!(tokens_5))))) goto next_756;
    match_197 = 0;
    goto end_match_755;
next_756:;
    if ((!(tokens_5))) goto next_757;
    struct IntIntTuple2 loc_28 = tokens_5->head.t1;
    int call_468 = locInside_(baseLoc_, loc_28);
    if ((!(call_468))) goto next_757;
    match_197 = 1;
    goto end_match_755;
next_757:;
    match_197 = 0;
    goto end_match_755;
next_758:;
end_match_755:;
    return match_197;
}

struct StringIntIntTuple2Tuple2List* parseErrorCore_(struct String msg_3, struct IntIntTuple2 loc_29, struct StringIntIntTuple2Tuple2List* errors_1) {
    struct String call_469 = locToString_(loc_29);
    struct String msg_4 = str_add(str_add(str_add(str_add((struct String){.str = "PARSE ERROR: ", .len = 13}, msg_3), (struct String){.str = " (", .len = 2}), call_469), (struct String){.str = ")", .len = 1});
    struct StringIntIntTuple2Tuple2 tuple_131;
    tuple_131.t0 = msg_4;
    tuple_131.t1 = loc_29;
    struct StringIntIntTuple2Tuple2List* list_58 = (struct StringIntIntTuple2Tuple2List*)malloc(sizeof(struct StringIntIntTuple2Tuple2List));
    list_58->head = tuple_131;
    list_58->tail = errors_1;
    return list_58;
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

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyError_1(struct String msg_5, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_124) {
    struct Token_IntIntTuple2Tuple2List* tokens_6 = arg_124.t0;
    struct StringIntIntTuple2Tuple2List* errors_2 = arg_124.t1;
    struct IntIntTuple2 call_470 = nextLoc_1(tokens_6);
    struct IntIntTuple2 loc_30 = call_470;
    struct StringIntIntTuple2Tuple2List* call_471 = parseErrorCore_(msg_5, loc_30, errors_2);
    struct StringIntIntTuple2Tuple2List* errors_3 = call_471;
    struct IntIntTuple2* payload_76 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_76))) = loc_30;
    struct ATy_ variant_76 = (struct ATy_){.tag = Missing_, .Missing_ = payload_76};
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_132;
    tuple_132.t0 = variant_76;
    tuple_132.t1 = tokens_6;
    tuple_132.t2 = errors_3;
    return tuple_132;
}

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct APat_ t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatError_1(struct String msg_6, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_125) {
    struct Token_IntIntTuple2Tuple2List* tokens_7 = arg_125.t0;
    struct StringIntIntTuple2Tuple2List* errors_4 = arg_125.t1;
    struct IntIntTuple2 call_472 = nextLoc_1(tokens_7);
    struct IntIntTuple2 loc_31 = call_472;
    struct StringIntIntTuple2Tuple2List* call_473 = parseErrorCore_(msg_6, loc_31, errors_4);
    struct StringIntIntTuple2Tuple2List* errors_5 = call_473;
    struct IntIntTuple2* payload_77 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_77))) = loc_31;
    struct APat_ variant_77 = (struct APat_){.tag = Missing_1, .Missing_1 = payload_77};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_133;
    tuple_133.t0 = variant_77;
    tuple_133.t1 = tokens_7;
    tuple_133.t2 = errors_5;
    return tuple_133;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct AExpr_ t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseExprError_1(struct String msg_7, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_126) {
    struct Token_IntIntTuple2Tuple2List* tokens_8 = arg_126.t0;
    struct StringIntIntTuple2Tuple2List* errors_6 = arg_126.t1;
    struct IntIntTuple2 call_474 = nextLoc_1(tokens_8);
    struct IntIntTuple2 loc_32 = call_474;
    struct StringIntIntTuple2Tuple2List* call_475 = parseErrorCore_(msg_7, loc_32, errors_6);
    struct StringIntIntTuple2Tuple2List* errors_7 = call_475;
    struct IntIntTuple2* payload_78 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_78))) = loc_32;
    struct AExpr_ variant_78 = (struct AExpr_){.tag = Missing_2, .Missing_2 = payload_78};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_134;
    tuple_134.t0 = variant_78;
    tuple_134.t1 = tokens_8;
    tuple_134.t2 = errors_7;
    return tuple_134;
}

struct StringIntIntTuple2Tuple2List* parseNewError_1(struct String msg_8, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_127) {
    struct Token_IntIntTuple2Tuple2List* tokens_9 = arg_127.t0;
    struct StringIntIntTuple2Tuple2List* errors_8 = arg_127.t1;
    struct IntIntTuple2 call_476 = nextLoc_1(tokens_9);
    struct IntIntTuple2 loc_33 = call_476;
    struct StringIntIntTuple2Tuple2List* call_477 = parseErrorCore_(msg_8, loc_33, errors_8);
    return call_477;
}

struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct ATy_List* t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_40(struct IntIntTuple2 baseLoc_1, struct ATy_List* acc_25, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_128) {
    struct Token_IntIntTuple2Tuple2List* tokens_12 = arg_128.t0;
    struct StringIntIntTuple2Tuple2List* errors_10 = arg_128.t1;
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_198;
    if ((!(tokens_12))) goto next_760;
    if ((tokens_12->head.t0.tag != Comma_)) goto next_760;
    struct Token_IntIntTuple2Tuple2List* tokens_13 = tokens_12->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_135;
    tuple_135.t0 = tokens_13;
    tuple_135.t1 = errors_10;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_478 = parseTy_(baseLoc_1, tuple_135);
    struct ATy_ argTy_ = call_478.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_14 = call_478.t1;
    struct StringIntIntTuple2Tuple2List* errors_11 = call_478.t2;
    struct ATy_List* list_59 = (struct ATy_List*)malloc(sizeof(struct ATy_List));
    list_59->head = argTy_;
    list_59->tail = acc_25;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_136;
    tuple_136.t0 = tokens_14;
    tuple_136.t1 = errors_11;
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_479 = go_40(baseLoc_1, list_59, tuple_136);
    match_198 = call_479;
    goto end_match_759;
next_760:;
    struct ATy_List* call_480 = listRev_6(acc_25);
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_137;
    tuple_137.t0 = call_480;
    tuple_137.t1 = tokens_12;
    tuple_137.t2 = errors_10;
    match_198 = tuple_137;
    goto end_match_759;
next_761:;
end_match_759:;
    return match_198;
}

struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyArgs_(struct IntIntTuple2 baseLoc_1, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_129) {
    struct Token_IntIntTuple2Tuple2List* tokens_10 = arg_129.t0;
    struct StringIntIntTuple2Tuple2List* errors_9 = arg_129.t1;
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_199;
    if ((!(tokens_10))) goto next_763;
    if ((tokens_10->head.t0.tag != Lt_)) goto next_763;
    struct IntIntTuple2 ltLoc_ = tokens_10->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_11 = tokens_10->tail;
    int call_481 = locInside_(baseLoc_1, ltLoc_);
    if ((!(call_481))) goto next_763;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_138;
    tuple_138.t0 = tokens_11;
    tuple_138.t1 = errors_9;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_482 = parseTy_(baseLoc_1, tuple_138);
    struct ATy_ argTy_1 = call_482.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_15 = call_482.t1;
    struct StringIntIntTuple2Tuple2List* errors_12 = call_482.t2;
    struct ATy_List* list_60 = (struct ATy_List*)malloc(sizeof(struct ATy_List));
    list_60->head = argTy_1;
    list_60->tail = NULL;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_139;
    tuple_139.t0 = tokens_15;
    tuple_139.t1 = errors_12;
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_483 = go_40(baseLoc_1, list_60, tuple_139);
    struct ATy_List* argTys_ = call_483.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_16 = call_483.t1;
    struct StringIntIntTuple2Tuple2List* errors_13 = call_483.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 match_200;
    if ((!(tokens_16))) goto next_766;
    if ((tokens_16->head.t0.tag != Gt_)) goto next_766;
    struct Token_IntIntTuple2Tuple2List* tokens_18 = tokens_16->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_140;
    tuple_140.t0 = tokens_18;
    tuple_140.t1 = errors_13;
    match_200 = tuple_140;
    goto end_match_765;
next_766:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_141;
    tuple_141.t0 = tokens_16;
    tuple_141.t1 = errors_13;
    struct StringIntIntTuple2Tuple2List* call_484 = parseNewError_1((struct String){.str = "Expected \'>\'", .len = 12}, tuple_141);
    struct StringIntIntTuple2Tuple2List* errors_15 = call_484;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_142;
    tuple_142.t0 = tokens_16;
    tuple_142.t1 = errors_15;
    match_200 = tuple_142;
    goto end_match_765;
next_767:;
end_match_765:;
    struct Token_IntIntTuple2Tuple2List* tokens_17 = match_200.t0;
    struct StringIntIntTuple2Tuple2List* errors_14 = match_200.t1;
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_143;
    tuple_143.t0 = argTys_;
    tuple_143.t1 = tokens_17;
    tuple_143.t2 = errors_14;
    match_199 = tuple_143;
    goto end_match_762;
next_763:;
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_144;
    tuple_144.t0 = NULL;
    tuple_144.t1 = tokens_10;
    tuple_144.t2 = errors_9;
    match_199 = tuple_144;
    goto end_match_762;
next_764:;
end_match_762:;
    return match_199;
}

struct StringATy_ListIntIntTuple2Tuple3 {
    struct String t0;
    struct ATy_List* t1;
    struct IntIntTuple2 t2;
};

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyAtom_(struct IntIntTuple2 baseLoc_2, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_130) {
    struct Token_IntIntTuple2Tuple2List* tokens_19 = arg_130.t0;
    struct StringIntIntTuple2Tuple2List* errors_16 = arg_130.t1;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_201;
    int call_485 = nextInside_1(baseLoc_2, tokens_19);
    if (call_485) goto next_769;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_145;
    tuple_145.t0 = tokens_19;
    tuple_145.t1 = errors_16;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_486 = parseTyError_1((struct String){.str = "Expected a type atom", .len = 20}, tuple_145);
    match_201 = call_486;
    goto end_match_768;
next_769:;
    if ((!(tokens_19))) goto next_770;
    if ((tokens_19->head.t0.tag != Ident_)) goto next_770;
    struct String ident_18 = (*(tokens_19->head.t0.Ident_));
    struct IntIntTuple2 loc_34 = tokens_19->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_20 = tokens_19->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_146;
    tuple_146.t0 = tokens_20;
    tuple_146.t1 = errors_16;
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_487 = parseTyArgs_(baseLoc_2, tuple_146);
    struct ATy_List* argTys_1 = call_487.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_21 = call_487.t1;
    struct StringIntIntTuple2Tuple2List* errors_17 = call_487.t2;
    struct StringATy_ListIntIntTuple2Tuple3 tuple_148;
    tuple_148.t0 = ident_18;
    tuple_148.t1 = argTys_1;
    tuple_148.t2 = loc_34;
    struct StringATy_ListIntIntTuple2Tuple3* payload_79 = (struct StringATy_ListIntIntTuple2Tuple3*)malloc(sizeof(struct StringATy_ListIntIntTuple2Tuple3));
    (*(((struct StringATy_ListIntIntTuple2Tuple3*)payload_79))) = tuple_148;
    struct ATy_ variant_79 = (struct ATy_){.tag = App_1, .App_1 = payload_79};
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_147;
    tuple_147.t0 = variant_79;
    tuple_147.t1 = tokens_21;
    tuple_147.t2 = errors_17;
    match_201 = tuple_147;
    goto end_match_768;
next_770:;
    if ((!(tokens_19))) goto next_771;
    if ((tokens_19->head.t0.tag != ParenL_)) goto next_771;
    struct Token_IntIntTuple2Tuple2List* tokens_22 = tokens_19->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_149;
    tuple_149.t0 = tokens_22;
    tuple_149.t1 = errors_16;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_488 = parseTy_(baseLoc_2, tuple_149);
    struct ATy_ ty_47 = call_488.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_23 = call_488.t1;
    struct StringIntIntTuple2Tuple2List* errors_18 = call_488.t2;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_202;
    if ((!(tokens_23))) goto next_774;
    if ((tokens_23->head.t0.tag != ParenR_)) goto next_774;
    struct Token_IntIntTuple2Tuple2List* tokens_24 = tokens_23->tail;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_150;
    tuple_150.t0 = ty_47;
    tuple_150.t1 = tokens_24;
    tuple_150.t2 = errors_18;
    match_202 = tuple_150;
    goto end_match_773;
next_774:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_151;
    tuple_151.t0 = tokens_23;
    tuple_151.t1 = errors_18;
    struct StringIntIntTuple2Tuple2List* call_489 = parseNewError_1((struct String){.str = "Expected \')\'", .len = 12}, tuple_151);
    struct StringIntIntTuple2Tuple2List* errors_19 = call_489;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_152;
    tuple_152.t0 = ty_47;
    tuple_152.t1 = tokens_23;
    tuple_152.t2 = errors_19;
    match_202 = tuple_152;
    goto end_match_773;
next_775:;
end_match_773:;
    match_201 = match_202;
    goto end_match_768;
next_771:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_153;
    tuple_153.t0 = tokens_19;
    tuple_153.t1 = errors_16;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_490 = parseTyError_1((struct String){.str = "Expected a type atom", .len = 20}, tuple_153);
    match_201 = call_490;
    goto end_match_768;
next_772:;
end_match_768:;
    return match_201;
}

struct ATy_StringIntIntTuple2Tuple3 {
    struct ATy_ t0;
    struct String t1;
    struct IntIntTuple2 t2;
};

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_55(struct IntIntTuple2 baseLoc_3, struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 arg_131) {
    struct ATy_ ty_48 = arg_131.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_26 = arg_131.t1;
    struct StringIntIntTuple2Tuple2List* errors_21 = arg_131.t2;
    int call_491 = nextInside_1(baseLoc_3, tokens_26);
    int inside_ = call_491;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_203;
    if ((!(tokens_26))) goto next_777;
    if ((tokens_26->head.t0.tag != Ident_)) goto next_777;
    struct String ident_19 = (*(tokens_26->head.t0.Ident_));
    struct IntIntTuple2 loc_35 = tokens_26->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_27 = tokens_26->tail;
    if ((!(inside_))) goto next_777;
    struct ATy_StringIntIntTuple2Tuple3 tuple_155;
    tuple_155.t0 = ty_48;
    tuple_155.t1 = ident_19;
    tuple_155.t2 = loc_35;
    struct ATy_StringIntIntTuple2Tuple3* payload_80 = (struct ATy_StringIntIntTuple2Tuple3*)malloc(sizeof(struct ATy_StringIntIntTuple2Tuple3));
    (*(((struct ATy_StringIntIntTuple2Tuple3*)payload_80))) = tuple_155;
    struct ATy_ variant_80 = (struct ATy_){.tag = Suffix_, .Suffix_ = payload_80};
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_154;
    tuple_154.t0 = variant_80;
    tuple_154.t1 = tokens_27;
    tuple_154.t2 = errors_21;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_492 = go_55(baseLoc_3, tuple_154);
    match_203 = call_492;
    goto end_match_776;
next_777:;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_156;
    tuple_156.t0 = ty_48;
    tuple_156.t1 = tokens_26;
    tuple_156.t2 = errors_21;
    match_203 = tuple_156;
    goto end_match_776;
next_778:;
end_match_776:;
    return match_203;
}

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTySuffix_(struct IntIntTuple2 baseLoc_3, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_132) {
    struct Token_IntIntTuple2Tuple2List* tokens_25 = arg_132.t0;
    struct StringIntIntTuple2Tuple2List* errors_20 = arg_132.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_157;
    tuple_157.t0 = tokens_25;
    tuple_157.t1 = errors_20;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_493 = parseTyAtom_(baseLoc_3, tuple_157);
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_494 = go_55(baseLoc_3, call_493);
    return call_494;
}

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyPrefix_(struct IntIntTuple2 baseLoc_4, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_133) {
    struct Token_IntIntTuple2Tuple2List* tokens_28 = arg_133.t0;
    struct StringIntIntTuple2Tuple2List* errors_22 = arg_133.t1;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_204;
    if ((!(tokens_28))) goto next_780;
    if ((tokens_28->head.t0.tag != Ident_)) goto next_780;
    if ((!(tokens_28->tail))) goto next_780;
    if ((tokens_28->tail->head.t0.tag != Colon_)) goto next_780;
    struct Token_IntIntTuple2Tuple2List* tokens_29 = tokens_28->tail->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_158;
    tuple_158.t0 = tokens_29;
    tuple_158.t1 = errors_22;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_495 = parseTySuffix_(baseLoc_4, tuple_158);
    match_204 = call_495;
    goto end_match_779;
next_780:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_159;
    tuple_159.t0 = tokens_28;
    tuple_159.t1 = errors_22;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_496 = parseTySuffix_(baseLoc_4, tuple_159);
    match_204 = call_496;
    goto end_match_779;
next_781:;
end_match_779:;
    return match_204;
}

struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_42(struct IntIntTuple2 baseLoc_5, struct ATy_List* acc_26, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_134) {
    struct Token_IntIntTuple2Tuple2List* tokens_31 = arg_134.t0;
    struct StringIntIntTuple2Tuple2List* errors_24 = arg_134.t1;
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_205;
    if ((!(tokens_31))) goto next_783;
    if ((tokens_31->head.t0.tag != Star_)) goto next_783;
    struct Token_IntIntTuple2Tuple2List* tokens_32 = tokens_31->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_160;
    tuple_160.t0 = tokens_32;
    tuple_160.t1 = errors_24;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_497 = parseTyPrefix_(baseLoc_5, tuple_160);
    struct ATy_ itemTy_11 = call_497.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_33 = call_497.t1;
    struct StringIntIntTuple2Tuple2List* errors_25 = call_497.t2;
    struct ATy_List* list_61 = (struct ATy_List*)malloc(sizeof(struct ATy_List));
    list_61->head = itemTy_11;
    list_61->tail = acc_26;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_161;
    tuple_161.t0 = tokens_33;
    tuple_161.t1 = errors_25;
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_498 = go_42(baseLoc_5, list_61, tuple_161);
    match_205 = call_498;
    goto end_match_782;
next_783:;
    struct ATy_List* call_499 = listRev_6(acc_26);
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_162;
    tuple_162.t0 = call_499;
    tuple_162.t1 = tokens_31;
    tuple_162.t2 = errors_24;
    match_205 = tuple_162;
    goto end_match_782;
next_784:;
end_match_782:;
    return match_205;
}

struct ATy_ListIntIntTuple2Tuple2 {
    struct ATy_List* t0;
    struct IntIntTuple2 t1;
};

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyTuple_(struct IntIntTuple2 baseLoc_5, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_135) {
    struct Token_IntIntTuple2Tuple2List* tokens_30 = arg_135.t0;
    struct StringIntIntTuple2Tuple2List* errors_23 = arg_135.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_163;
    tuple_163.t0 = tokens_30;
    tuple_163.t1 = errors_23;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_500 = parseTyPrefix_(baseLoc_5, tuple_163);
    struct ATy_ itemTy_12 = call_500.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_34 = call_500.t1;
    struct StringIntIntTuple2Tuple2List* errors_26 = call_500.t2;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_206;
    if ((!(tokens_34))) goto next_786;
    if ((tokens_34->head.t0.tag != Star_)) goto next_786;
    struct IntIntTuple2 opLoc_ = tokens_34->head.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_164;
    tuple_164.t0 = tokens_34;
    tuple_164.t1 = errors_26;
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_501 = go_42(baseLoc_5, NULL, tuple_164);
    struct ATy_List* itemTys_1 = call_501.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_35 = call_501.t1;
    struct StringIntIntTuple2Tuple2List* errors_27 = call_501.t2;
    struct ATy_List* list_62 = (struct ATy_List*)malloc(sizeof(struct ATy_List));
    list_62->head = itemTy_12;
    list_62->tail = itemTys_1;
    struct ATy_ListIntIntTuple2Tuple2 tuple_166;
    tuple_166.t0 = list_62;
    tuple_166.t1 = opLoc_;
    struct ATy_ListIntIntTuple2Tuple2* payload_81 = (struct ATy_ListIntIntTuple2Tuple2*)malloc(sizeof(struct ATy_ListIntIntTuple2Tuple2));
    (*(((struct ATy_ListIntIntTuple2Tuple2*)payload_81))) = tuple_166;
    struct ATy_ variant_81 = (struct ATy_){.tag = Tuple_, .Tuple_ = payload_81};
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_165;
    tuple_165.t0 = variant_81;
    tuple_165.t1 = tokens_35;
    tuple_165.t2 = errors_27;
    match_206 = tuple_165;
    goto end_match_785;
next_786:;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_167;
    tuple_167.t0 = itemTy_12;
    tuple_167.t1 = tokens_34;
    tuple_167.t2 = errors_26;
    match_206 = tuple_167;
    goto end_match_785;
next_787:;
end_match_785:;
    return match_206;
}

struct ATy_ATy_IntIntTuple2Tuple3 {
    struct ATy_ t0;
    struct ATy_ t1;
    struct IntIntTuple2 t2;
};

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyFun_(struct IntIntTuple2 baseLoc_6, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_136) {
    struct Token_IntIntTuple2Tuple2List* tokens_36 = arg_136.t0;
    struct StringIntIntTuple2Tuple2List* errors_28 = arg_136.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_168;
    tuple_168.t0 = tokens_36;
    tuple_168.t1 = errors_28;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_502 = parseTyTuple_(baseLoc_6, tuple_168);
    struct ATy_ sTy_1 = call_502.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_37 = call_502.t1;
    struct StringIntIntTuple2Tuple2List* errors_29 = call_502.t2;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_207;
    if ((!(tokens_37))) goto next_789;
    if ((tokens_37->head.t0.tag != Arrow_)) goto next_789;
    struct IntIntTuple2 opLoc_1 = tokens_37->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_38 = tokens_37->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_169;
    tuple_169.t0 = tokens_38;
    tuple_169.t1 = errors_29;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_503 = parseTyFun_(baseLoc_6, tuple_169);
    struct ATy_ tTy_1 = call_503.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_39 = call_503.t1;
    struct StringIntIntTuple2Tuple2List* errors_30 = call_503.t2;
    struct ATy_ATy_IntIntTuple2Tuple3 tuple_171;
    tuple_171.t0 = sTy_1;
    tuple_171.t1 = tTy_1;
    tuple_171.t2 = opLoc_1;
    struct ATy_ATy_IntIntTuple2Tuple3* payload_82 = (struct ATy_ATy_IntIntTuple2Tuple3*)malloc(sizeof(struct ATy_ATy_IntIntTuple2Tuple3));
    (*(((struct ATy_ATy_IntIntTuple2Tuple3*)payload_82))) = tuple_171;
    struct ATy_ variant_82 = (struct ATy_){.tag = Fun_1, .Fun_1 = payload_82};
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_170;
    tuple_170.t0 = variant_82;
    tuple_170.t1 = tokens_39;
    tuple_170.t2 = errors_30;
    match_207 = tuple_170;
    goto end_match_788;
next_789:;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_172;
    tuple_172.t0 = sTy_1;
    tuple_172.t1 = tokens_37;
    tuple_172.t2 = errors_29;
    match_207 = tuple_172;
    goto end_match_788;
next_790:;
end_match_788:;
    return match_207;
}

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTy_(struct IntIntTuple2 baseLoc_7, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_137) {
    struct Token_IntIntTuple2Tuple2List* tokens_40 = arg_137.t0;
    struct StringIntIntTuple2Tuple2List* errors_31 = arg_137.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_173;
    tuple_173.t0 = tokens_40;
    tuple_173.t1 = errors_31;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_504 = parseTyFun_(baseLoc_7, tuple_173);
    return call_504;
}

struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct AVariant_List* t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_43(struct IntIntTuple2 baseLoc_8, struct AVariant_List* acc_27, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_138) {
    struct Token_IntIntTuple2Tuple2List* tokens_42 = arg_138.t0;
    struct StringIntIntTuple2Tuple2List* errors_33 = arg_138.t1;
    struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_208;
    if ((!(tokens_42))) goto next_792;
    if ((tokens_42->head.t0.tag != Pipe_)) goto next_792;
    if ((!(tokens_42->tail))) goto next_792;
    if ((tokens_42->tail->head.t0.tag != Ident_)) goto next_792;
    struct String variantIdent_ = (*(tokens_42->tail->head.t0.Ident_));
    struct IntIntTuple2 loc_36 = tokens_42->tail->head.t1;
    if ((!(tokens_42->tail->tail))) goto next_792;
    if ((tokens_42->tail->tail->head.t0.tag != Of_)) goto next_792;
    struct Token_IntIntTuple2Tuple2List* tokens_43 = tokens_42->tail->tail->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_174;
    tuple_174.t0 = tokens_43;
    tuple_174.t1 = errors_33;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_505 = parseTy_(baseLoc_8, tuple_174);
    struct ATy_ payloadTy_ = call_505.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_44 = call_505.t1;
    struct StringIntIntTuple2Tuple2List* errors_34 = call_505.t2;
    struct ATy_List* some_1 = (struct ATy_List*)malloc(sizeof(struct ATy_List));
    some_1->head = payloadTy_;
    some_1->tail = NULL;
    struct StringATy_ListIntIntTuple2Tuple3 tuple_175;
    tuple_175.t0 = variantIdent_;
    tuple_175.t1 = some_1;
    tuple_175.t2 = loc_36;
    struct StringATy_ListIntIntTuple2Tuple3* payload_83 = (struct StringATy_ListIntIntTuple2Tuple3*)malloc(sizeof(struct StringATy_ListIntIntTuple2Tuple3));
    (*(((struct StringATy_ListIntIntTuple2Tuple3*)payload_83))) = tuple_175;
    struct AVariant_ variant_83 = (struct AVariant_){.tag = AVariant_, .AVariant_ = payload_83};
    struct AVariant_List* list_63 = (struct AVariant_List*)malloc(sizeof(struct AVariant_List));
    list_63->head = variant_83;
    list_63->tail = acc_27;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_176;
    tuple_176.t0 = tokens_44;
    tuple_176.t1 = errors_34;
    struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_506 = go_43(baseLoc_8, list_63, tuple_176);
    match_208 = call_506;
    goto end_match_791;
next_792:;
    if ((!(tokens_42))) goto next_793;
    if ((tokens_42->head.t0.tag != Pipe_)) goto next_793;
    if ((!(tokens_42->tail))) goto next_793;
    if ((tokens_42->tail->head.t0.tag != Ident_)) goto next_793;
    struct String variantIdent_1 = (*(tokens_42->tail->head.t0.Ident_));
    struct IntIntTuple2 loc_37 = tokens_42->tail->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_45 = tokens_42->tail->tail;
    struct StringATy_ListIntIntTuple2Tuple3 tuple_177;
    tuple_177.t0 = variantIdent_1;
    tuple_177.t1 = NULL;
    tuple_177.t2 = loc_37;
    struct StringATy_ListIntIntTuple2Tuple3* payload_84 = (struct StringATy_ListIntIntTuple2Tuple3*)malloc(sizeof(struct StringATy_ListIntIntTuple2Tuple3));
    (*(((struct StringATy_ListIntIntTuple2Tuple3*)payload_84))) = tuple_177;
    struct AVariant_ variant_84 = (struct AVariant_){.tag = AVariant_, .AVariant_ = payload_84};
    struct AVariant_List* list_64 = (struct AVariant_List*)malloc(sizeof(struct AVariant_List));
    list_64->head = variant_84;
    list_64->tail = acc_27;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_178;
    tuple_178.t0 = tokens_45;
    tuple_178.t1 = errors_33;
    struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_507 = go_43(baseLoc_8, list_64, tuple_178);
    match_208 = call_507;
    goto end_match_791;
next_793:;
    struct AVariant_List* call_508 = listRev_5(acc_27);
    struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_179;
    tuple_179.t0 = call_508;
    tuple_179.t1 = tokens_42;
    tuple_179.t2 = errors_33;
    match_208 = tuple_179;
    goto end_match_791;
next_794:;
end_match_791:;
    return match_208;
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

struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyDeclUnion_(struct IntIntTuple2 baseLoc_8, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_139) {
    struct Token_IntIntTuple2Tuple2List* tokens_41 = arg_139.t0;
    struct StringIntIntTuple2Tuple2List* errors_32 = arg_139.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_180;
    tuple_180.t0 = tokens_41;
    tuple_180.t1 = errors_32;
    struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_509 = go_43(baseLoc_8, NULL, tuple_180);
    struct AVariant_List* variants_1 = call_509.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_46 = call_509.t1;
    struct StringIntIntTuple2Tuple2List* errors_35 = call_509.t2;
    struct AVariant_List** payload_85 = (struct AVariant_List**)malloc(sizeof(struct AVariant_List*));
    (*(((struct AVariant_List**)payload_85))) = variants_1;
    struct ATyDecl_ variant_85 = (struct ATyDecl_){.tag = Union_, .Union_ = payload_85};
    struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_181;
    tuple_181.t0 = variant_85;
    tuple_181.t1 = tokens_46;
    tuple_181.t2 = errors_35;
    return tuple_181;
}

struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyDeclBody_(struct IntIntTuple2 baseLoc_9, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_140) {
    struct Token_IntIntTuple2Tuple2List* tokens_47 = arg_140.t0;
    struct StringIntIntTuple2Tuple2List* errors_36 = arg_140.t1;
    struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_209;
    if ((!(tokens_47))) goto next_796;
    if ((tokens_47->head.t0.tag != Pipe_)) goto next_796;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_182;
    tuple_182.t0 = tokens_47;
    tuple_182.t1 = errors_36;
    struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_510 = parseTyDeclUnion_(baseLoc_9, tuple_182);
    match_209 = call_510;
    goto end_match_795;
next_796:;
    if ((!(tokens_47))) goto next_797;
    if ((tokens_47->head.t0.tag != Ident_)) goto next_797;
    if ((!(tokens_47->tail))) goto next_797;
    if ((tokens_47->tail->head.t0.tag != Of_)) goto next_797;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_183;
    tuple_183.t0 = tokens_47;
    tuple_183.t1 = errors_36;
    struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_511 = parseTyDeclUnion_(baseLoc_9, tuple_183);
    match_209 = call_511;
    goto end_match_795;
next_797:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_184;
    tuple_184.t0 = tokens_47;
    tuple_184.t1 = errors_36;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_512 = parseTy_(baseLoc_9, tuple_184);
    struct ATy_ ty_49 = call_512.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_48 = call_512.t1;
    struct StringIntIntTuple2Tuple2List* errors_37 = call_512.t2;
    struct ATy_* payload_86 = (struct ATy_*)malloc(sizeof(struct ATy_));
    (*(((struct ATy_*)payload_86))) = ty_49;
    struct ATyDecl_ variant_86 = (struct ATyDecl_){.tag = Synonym_, .Synonym_ = payload_86};
    struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_185;
    tuple_185.t0 = variant_86;
    tuple_185.t1 = tokens_48;
    tuple_185.t2 = errors_37;
    match_209 = tuple_185;
    goto end_match_795;
next_798:;
end_match_795:;
    return match_209;
}

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatParenBody_(struct IntIntTuple2 baseLoc_10, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_141) {
    struct Token_IntIntTuple2Tuple2List* tokens_49 = arg_141.t0;
    struct StringIntIntTuple2Tuple2List* errors_38 = arg_141.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_186;
    tuple_186.t0 = tokens_49;
    tuple_186.t1 = errors_38;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_513 = parsePat_(baseLoc_10, tuple_186);
    struct APat_ pat_15 = call_513.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_50 = call_513.t1;
    struct StringIntIntTuple2Tuple2List* errors_39 = call_513.t2;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_210;
    if ((!(tokens_50))) goto next_800;
    if ((tokens_50->head.t0.tag != ParenR_)) goto next_800;
    struct Token_IntIntTuple2Tuple2List* tokens_51 = tokens_50->tail;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_187;
    tuple_187.t0 = pat_15;
    tuple_187.t1 = tokens_51;
    tuple_187.t2 = errors_39;
    match_210 = tuple_187;
    goto end_match_799;
next_800:;
    struct Token_IntIntTuple2Tuple2List* tokens_52 = tokens_50;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_188;
    tuple_188.t0 = tokens_52;
    tuple_188.t1 = errors_39;
    struct StringIntIntTuple2Tuple2List* call_514 = parseNewError_1((struct String){.str = "Expected \')\'", .len = 12}, tuple_188);
    struct StringIntIntTuple2Tuple2List* errors_40 = call_514;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_189;
    tuple_189.t0 = pat_15;
    tuple_189.t1 = tokens_52;
    tuple_189.t2 = errors_40;
    match_210 = tuple_189;
    goto end_match_799;
next_801:;
end_match_799:;
    return match_210;
}

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct APat_List* t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_44(struct IntIntTuple2 baseLoc_11, struct APat_List* patAcc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_142) {
    struct Token_IntIntTuple2Tuple2List* tokens_54 = arg_142.t0;
    struct StringIntIntTuple2Tuple2List* errors_42 = arg_142.t1;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_211;
    if ((!(tokens_54))) goto next_803;
    if ((tokens_54->head.t0.tag != BracketR_)) goto next_803;
    struct Token_IntIntTuple2Tuple2List* tokens_55 = tokens_54->tail;
    struct APat_List* call_515 = listRev_4(patAcc_);
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_190;
    tuple_190.t0 = call_515;
    tuple_190.t1 = tokens_55;
    tuple_190.t2 = errors_42;
    match_211 = tuple_190;
    goto end_match_802;
next_803:;
    if ((!(tokens_54))) goto next_804;
    if ((tokens_54->head.t0.tag != Semi_)) goto next_804;
    struct Token_IntIntTuple2Tuple2List* tokens_56 = tokens_54->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_191;
    tuple_191.t0 = tokens_56;
    tuple_191.t1 = errors_42;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_516 = parsePat_(baseLoc_11, tuple_191);
    struct APat_ pat_16 = call_516.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_57 = call_516.t1;
    struct StringIntIntTuple2Tuple2List* errors_43 = call_516.t2;
    struct APat_List* list_65 = (struct APat_List*)malloc(sizeof(struct APat_List));
    list_65->head = pat_16;
    list_65->tail = patAcc_;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_192;
    tuple_192.t0 = tokens_57;
    tuple_192.t1 = errors_43;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_517 = go_44(baseLoc_11, list_65, tuple_192);
    match_211 = call_517;
    goto end_match_802;
next_804:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_193;
    tuple_193.t0 = tokens_54;
    tuple_193.t1 = errors_42;
    struct StringIntIntTuple2Tuple2List* call_518 = parseNewError_1((struct String){.str = "Expected \';\' or \']\'", .len = 19}, tuple_193);
    struct StringIntIntTuple2Tuple2List* errors_44 = call_518;
    struct APat_List* call_519 = listRev_4(patAcc_);
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_194;
    tuple_194.t0 = call_519;
    tuple_194.t1 = tokens_54;
    tuple_194.t2 = errors_44;
    match_211 = tuple_194;
    goto end_match_802;
next_805:;
end_match_802:;
    return match_211;
}

struct APat_ListIntIntTuple2Tuple2 {
    struct APat_List* t0;
    struct IntIntTuple2 t1;
};

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatListBody_(struct IntIntTuple2 baseLoc_11, struct IntIntTuple2 bracketLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_143) {
    struct Token_IntIntTuple2Tuple2List* tokens_53 = arg_143.t0;
    struct StringIntIntTuple2Tuple2List* errors_41 = arg_143.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_195;
    tuple_195.t0 = tokens_53;
    tuple_195.t1 = errors_41;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_520 = parsePat_(baseLoc_11, tuple_195);
    struct APat_ itemPat_ = call_520.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_58 = call_520.t1;
    struct StringIntIntTuple2Tuple2List* errors_45 = call_520.t2;
    struct APat_List* list_66 = (struct APat_List*)malloc(sizeof(struct APat_List));
    list_66->head = itemPat_;
    list_66->tail = NULL;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_196;
    tuple_196.t0 = tokens_58;
    tuple_196.t1 = errors_45;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_521 = go_44(baseLoc_11, list_66, tuple_196);
    struct APat_List* itemPats_1 = call_521.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_59 = call_521.t1;
    struct StringIntIntTuple2Tuple2List* errors_46 = call_521.t2;
    struct APat_ListIntIntTuple2Tuple2 tuple_198;
    tuple_198.t0 = itemPats_1;
    tuple_198.t1 = bracketLoc_;
    struct APat_ListIntIntTuple2Tuple2* payload_87 = (struct APat_ListIntIntTuple2Tuple2*)malloc(sizeof(struct APat_ListIntIntTuple2Tuple2));
    (*(((struct APat_ListIntIntTuple2Tuple2*)payload_87))) = tuple_198;
    struct APat_ variant_87 = (struct APat_){.tag = ListLit_, .ListLit_ = payload_87};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_197;
    tuple_197.t0 = variant_87;
    tuple_197.t1 = tokens_59;
    tuple_197.t2 = errors_46;
    return tuple_197;
}

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatAtom_(struct IntIntTuple2 baseLoc_12, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_144) {
    struct Token_IntIntTuple2Tuple2List* tokens_60 = arg_144.t0;
    struct StringIntIntTuple2Tuple2List* errors_47 = arg_144.t1;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_212;
    int match_213;
    int call_522 = nextInside_1(baseLoc_12, tokens_60);
    if ((!(call_522))) goto next_819;
    int call_523 = leadsPat_1(tokens_60);
    match_213 = call_523;
    goto end_match_818;
next_819:;
    if (call_522) goto next_820;
    match_213 = 0;
    goto end_match_818;
next_820:;
    exit(1);
end_match_818:;
    if (match_213) goto next_807;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_199;
    tuple_199.t0 = tokens_60;
    tuple_199.t1 = errors_47;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_524 = parsePatError_1((struct String){.str = "Expected a pattern atom", .len = 23}, tuple_199);
    match_212 = call_524;
    goto end_match_806;
next_807:;
    if ((!(tokens_60))) goto next_808;
    if ((tokens_60->head.t0.tag != Bool_1)) goto next_808;
    int value_12 = (*(tokens_60->head.t0.Bool_1));
    struct IntIntTuple2 loc_38 = tokens_60->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_61 = tokens_60->tail;
    int* payload_88 = (int*)malloc(sizeof(int));
    (*(((int*)payload_88))) = value_12;
    struct Lit_ variant_88 = (struct Lit_){.tag = Bool_, .Bool_ = payload_88};
    struct Lit_IntIntTuple2Tuple2 tuple_201;
    tuple_201.t0 = variant_88;
    tuple_201.t1 = loc_38;
    struct Lit_IntIntTuple2Tuple2* payload_89 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_89))) = tuple_201;
    struct APat_ variant_89 = (struct APat_){.tag = Lit_, .Lit_ = payload_89};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_200;
    tuple_200.t0 = variant_89;
    tuple_200.t1 = tokens_61;
    tuple_200.t2 = errors_47;
    match_212 = tuple_200;
    goto end_match_806;
next_808:;
    if ((!(tokens_60))) goto next_809;
    if ((tokens_60->head.t0.tag != Int_1)) goto next_809;
    int value_13 = (*(tokens_60->head.t0.Int_1));
    struct IntIntTuple2 loc_39 = tokens_60->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_62 = tokens_60->tail;
    int* payload_90 = (int*)malloc(sizeof(int));
    (*(((int*)payload_90))) = value_13;
    struct Lit_ variant_90 = (struct Lit_){.tag = Int_, .Int_ = payload_90};
    struct Lit_IntIntTuple2Tuple2 tuple_203;
    tuple_203.t0 = variant_90;
    tuple_203.t1 = loc_39;
    struct Lit_IntIntTuple2Tuple2* payload_91 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_91))) = tuple_203;
    struct APat_ variant_91 = (struct APat_){.tag = Lit_, .Lit_ = payload_91};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_202;
    tuple_202.t0 = variant_91;
    tuple_202.t1 = tokens_62;
    tuple_202.t2 = errors_47;
    match_212 = tuple_202;
    goto end_match_806;
next_809:;
    if ((!(tokens_60))) goto next_810;
    if ((tokens_60->head.t0.tag != Char_1)) goto next_810;
    char value_14 = (*(tokens_60->head.t0.Char_1));
    struct IntIntTuple2 loc_40 = tokens_60->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_63 = tokens_60->tail;
    char* payload_92 = (char*)malloc(sizeof(char));
    (*(((char*)payload_92))) = value_14;
    struct Lit_ variant_92 = (struct Lit_){.tag = Char_, .Char_ = payload_92};
    struct Lit_IntIntTuple2Tuple2 tuple_205;
    tuple_205.t0 = variant_92;
    tuple_205.t1 = loc_40;
    struct Lit_IntIntTuple2Tuple2* payload_93 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_93))) = tuple_205;
    struct APat_ variant_93 = (struct APat_){.tag = Lit_, .Lit_ = payload_93};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_204;
    tuple_204.t0 = variant_93;
    tuple_204.t1 = tokens_63;
    tuple_204.t2 = errors_47;
    match_212 = tuple_204;
    goto end_match_806;
next_810:;
    if ((!(tokens_60))) goto next_811;
    if ((tokens_60->head.t0.tag != Str_1)) goto next_811;
    struct String value_15 = (*(tokens_60->head.t0.Str_1));
    struct IntIntTuple2 loc_41 = tokens_60->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_64 = tokens_60->tail;
    struct String* payload_94 = (struct String*)malloc(sizeof(struct String));
    (*(((struct String*)payload_94))) = value_15;
    struct Lit_ variant_94 = (struct Lit_){.tag = Str_, .Str_ = payload_94};
    struct Lit_IntIntTuple2Tuple2 tuple_207;
    tuple_207.t0 = variant_94;
    tuple_207.t1 = loc_41;
    struct Lit_IntIntTuple2Tuple2* payload_95 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_95))) = tuple_207;
    struct APat_ variant_95 = (struct APat_){.tag = Lit_, .Lit_ = payload_95};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_206;
    tuple_206.t0 = variant_95;
    tuple_206.t1 = tokens_64;
    tuple_206.t2 = errors_47;
    match_212 = tuple_206;
    goto end_match_806;
next_811:;
    if ((!(tokens_60))) goto next_812;
    if ((tokens_60->head.t0.tag != Ident_)) goto next_812;
    struct String ident_20 = (*(tokens_60->head.t0.Ident_));
    struct IntIntTuple2 loc_42 = tokens_60->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_65 = tokens_60->tail;
    struct StringIntIntTuple2Tuple2 tuple_209;
    tuple_209.t0 = ident_20;
    tuple_209.t1 = loc_42;
    struct StringIntIntTuple2Tuple2* payload_96 = (struct StringIntIntTuple2Tuple2*)malloc(sizeof(struct StringIntIntTuple2Tuple2));
    (*(((struct StringIntIntTuple2Tuple2*)payload_96))) = tuple_209;
    struct APat_ variant_96 = (struct APat_){.tag = Ident_1, .Ident_1 = payload_96};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_208;
    tuple_208.t0 = variant_96;
    tuple_208.t1 = tokens_65;
    tuple_208.t2 = errors_47;
    match_212 = tuple_208;
    goto end_match_806;
next_812:;
    if ((!(tokens_60))) goto next_813;
    if ((tokens_60->head.t0.tag != ParenL_)) goto next_813;
    struct IntIntTuple2 loc_43 = tokens_60->head.t1;
    if ((!(tokens_60->tail))) goto next_813;
    if ((tokens_60->tail->head.t0.tag != ParenR_)) goto next_813;
    struct Token_IntIntTuple2Tuple2List* tokens_66 = tokens_60->tail->tail;
    struct APat_ListIntIntTuple2Tuple2 tuple_211;
    tuple_211.t0 = NULL;
    tuple_211.t1 = loc_43;
    struct APat_ListIntIntTuple2Tuple2* payload_97 = (struct APat_ListIntIntTuple2Tuple2*)malloc(sizeof(struct APat_ListIntIntTuple2Tuple2));
    (*(((struct APat_ListIntIntTuple2Tuple2*)payload_97))) = tuple_211;
    struct APat_ variant_97 = (struct APat_){.tag = TupleLit_, .TupleLit_ = payload_97};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_210;
    tuple_210.t0 = variant_97;
    tuple_210.t1 = tokens_66;
    tuple_210.t2 = errors_47;
    match_212 = tuple_210;
    goto end_match_806;
next_813:;
    if ((!(tokens_60))) goto next_814;
    if ((tokens_60->head.t0.tag != ParenL_)) goto next_814;
    struct Token_IntIntTuple2Tuple2List* tokens_67 = tokens_60->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_212;
    tuple_212.t0 = tokens_67;
    tuple_212.t1 = errors_47;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_525 = parsePatParenBody_(baseLoc_12, tuple_212);
    match_212 = call_525;
    goto end_match_806;
next_814:;
    if ((!(tokens_60))) goto next_815;
    if ((tokens_60->head.t0.tag != BracketL_)) goto next_815;
    struct IntIntTuple2 loc_44 = tokens_60->head.t1;
    if ((!(tokens_60->tail))) goto next_815;
    if ((tokens_60->tail->head.t0.tag != BracketR_)) goto next_815;
    struct Token_IntIntTuple2Tuple2List* tokens_68 = tokens_60->tail->tail;
    struct APat_ListIntIntTuple2Tuple2 tuple_214;
    tuple_214.t0 = NULL;
    tuple_214.t1 = loc_44;
    struct APat_ListIntIntTuple2Tuple2* payload_98 = (struct APat_ListIntIntTuple2Tuple2*)malloc(sizeof(struct APat_ListIntIntTuple2Tuple2));
    (*(((struct APat_ListIntIntTuple2Tuple2*)payload_98))) = tuple_214;
    struct APat_ variant_98 = (struct APat_){.tag = ListLit_, .ListLit_ = payload_98};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_213;
    tuple_213.t0 = variant_98;
    tuple_213.t1 = tokens_68;
    tuple_213.t2 = errors_47;
    match_212 = tuple_213;
    goto end_match_806;
next_815:;
    if ((!(tokens_60))) goto next_816;
    if ((tokens_60->head.t0.tag != BracketL_)) goto next_816;
    struct IntIntTuple2 loc_45 = tokens_60->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_69 = tokens_60->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_215;
    tuple_215.t0 = tokens_69;
    tuple_215.t1 = errors_47;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_526 = parsePatListBody_(baseLoc_12, loc_45, tuple_215);
    match_212 = call_526;
    goto end_match_806;
next_816:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_216;
    tuple_216.t0 = tokens_60;
    tuple_216.t1 = errors_47;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_527 = parsePatError_1((struct String){.str = "NEVER: The token must be a pat", .len = 30}, tuple_216);
    match_212 = call_527;
    goto end_match_806;
next_817:;
end_match_806:;
    return match_212;
}

struct APat_StringIntIntTuple2Tuple3 {
    struct APat_ t0;
    struct String t1;
    struct IntIntTuple2 t2;
};

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatNav_(struct IntIntTuple2 baseLoc_13, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_145) {
    struct Token_IntIntTuple2Tuple2List* tokens_70 = arg_145.t0;
    struct StringIntIntTuple2Tuple2List* errors_48 = arg_145.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_217;
    tuple_217.t0 = tokens_70;
    tuple_217.t1 = errors_48;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_528 = parsePatAtom_(baseLoc_13, tuple_217);
    struct APat_ pat_17 = call_528.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_71 = call_528.t1;
    struct StringIntIntTuple2Tuple2List* errors_49 = call_528.t2;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_214;
    if ((!(tokens_71))) goto next_822;
    if ((tokens_71->head.t0.tag != Dot_)) goto next_822;
    struct IntIntTuple2 loc_46 = tokens_71->head.t1;
    if ((!(tokens_71->tail))) goto next_822;
    if ((tokens_71->tail->head.t0.tag != Ident_)) goto next_822;
    struct String ident_21 = (*(tokens_71->tail->head.t0.Ident_));
    struct Token_IntIntTuple2Tuple2List* tokens_72 = tokens_71->tail->tail;
    struct APat_StringIntIntTuple2Tuple3 tuple_219;
    tuple_219.t0 = pat_17;
    tuple_219.t1 = ident_21;
    tuple_219.t2 = loc_46;
    struct APat_StringIntIntTuple2Tuple3* payload_99 = (struct APat_StringIntIntTuple2Tuple3*)malloc(sizeof(struct APat_StringIntIntTuple2Tuple3));
    (*(((struct APat_StringIntIntTuple2Tuple3*)payload_99))) = tuple_219;
    struct APat_ variant_99 = (struct APat_){.tag = Nav_, .Nav_ = payload_99};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_218;
    tuple_218.t0 = variant_99;
    tuple_218.t1 = tokens_72;
    tuple_218.t2 = errors_49;
    match_214 = tuple_218;
    goto end_match_821;
next_822:;
    if ((!(tokens_71))) goto next_823;
    if ((tokens_71->head.t0.tag != Dot_)) goto next_823;
    struct Token_IntIntTuple2Tuple2List* tokens_73 = tokens_71->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_220;
    tuple_220.t0 = tokens_73;
    tuple_220.t1 = errors_49;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_529 = parsePatError_1((struct String){.str = "Expected identifier", .len = 19}, tuple_220);
    match_214 = call_529;
    goto end_match_821;
next_823:;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_221;
    tuple_221.t0 = pat_17;
    tuple_221.t1 = tokens_71;
    tuple_221.t2 = errors_49;
    match_214 = tuple_221;
    goto end_match_821;
next_824:;
end_match_821:;
    return match_214;
}

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_45(struct IntIntTuple2 argBaseLoc_, struct IntIntTuple2 baseLoc_14, struct APat_List* acc_28, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_146) {
    struct Token_IntIntTuple2Tuple2List* tokens_75 = arg_146.t0;
    struct StringIntIntTuple2Tuple2List* errors_51 = arg_146.t1;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_215;
    int match_216;
    int call_530 = nextInside_1(argBaseLoc_, tokens_75);
    if ((!(call_530))) goto next_827;
    int call_531 = leadsPat_1(tokens_75);
    match_216 = call_531;
    goto end_match_826;
next_827:;
    if (call_530) goto next_828;
    match_216 = 0;
    goto end_match_826;
next_828:;
    exit(1);
end_match_826:;
    if ((!(match_216))) goto next_829;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_222;
    tuple_222.t0 = tokens_75;
    tuple_222.t1 = errors_51;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_532 = parsePatNav_(baseLoc_14, tuple_222);
    struct APat_ expr_10 = call_532.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_76 = call_532.t1;
    struct StringIntIntTuple2Tuple2List* errors_52 = call_532.t2;
    struct APat_List* list_67 = (struct APat_List*)malloc(sizeof(struct APat_List));
    list_67->head = expr_10;
    list_67->tail = acc_28;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_223;
    tuple_223.t0 = tokens_76;
    tuple_223.t1 = errors_52;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_533 = go_45(argBaseLoc_, baseLoc_14, list_67, tuple_223);
    match_215 = call_533;
    goto end_match_825;
next_829:;
    if (match_216) goto next_830;
    struct APat_List* call_534 = listRev_4(acc_28);
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_224;
    tuple_224.t0 = call_534;
    tuple_224.t1 = tokens_75;
    tuple_224.t2 = errors_51;
    match_215 = tuple_224;
    goto end_match_825;
next_830:;
    exit(1);
end_match_825:;
    return match_215;
}

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatCallArgs_(struct IntIntTuple2 baseLoc_14, struct IntIntTuple2 calleeLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_147) {
    struct Token_IntIntTuple2Tuple2List* tokens_74 = arg_147.t0;
    struct StringIntIntTuple2Tuple2List* errors_50 = arg_147.t1;
    struct IntIntTuple2 call_535 = locMax_(baseLoc_14, calleeLoc_);
    struct IntIntTuple2 call_536 = locAddX_(1, call_535);
    struct IntIntTuple2 argBaseLoc_ = call_536;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_225;
    tuple_225.t0 = tokens_74;
    tuple_225.t1 = errors_50;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_537 = go_45(argBaseLoc_, baseLoc_14, NULL, tuple_225);
    return call_537;
}

struct APat_APat_ListIntIntTuple2Tuple3 {
    struct APat_ t0;
    struct APat_List* t1;
    struct IntIntTuple2 t2;
};

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatCall_(struct IntIntTuple2 baseLoc_15, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_148) {
    struct Token_IntIntTuple2Tuple2List* tokens_77 = arg_148.t0;
    struct StringIntIntTuple2Tuple2List* errors_53 = arg_148.t1;
    struct IntIntTuple2 call_538 = nextLoc_1(tokens_77);
    struct IntIntTuple2 calleeLoc_1 = call_538;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_226;
    tuple_226.t0 = tokens_77;
    tuple_226.t1 = errors_53;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_539 = parsePatNav_(baseLoc_15, tuple_226);
    struct APat_ callee_5 = call_539.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_78 = call_539.t1;
    struct StringIntIntTuple2Tuple2List* errors_54 = call_539.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_227;
    tuple_227.t0 = tokens_78;
    tuple_227.t1 = errors_54;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_540 = parsePatCallArgs_(baseLoc_15, calleeLoc_1, tuple_227);
    struct APat_List* args_6 = call_540.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_79 = call_540.t1;
    struct StringIntIntTuple2Tuple2List* errors_55 = call_540.t2;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_217;
    if ((!((!(args_6))))) goto next_832;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_228;
    tuple_228.t0 = callee_5;
    tuple_228.t1 = tokens_79;
    tuple_228.t2 = errors_55;
    match_217 = tuple_228;
    goto end_match_831;
next_832:;
    struct APat_APat_ListIntIntTuple2Tuple3 tuple_230;
    tuple_230.t0 = callee_5;
    tuple_230.t1 = args_6;
    tuple_230.t2 = calleeLoc_1;
    struct APat_APat_ListIntIntTuple2Tuple3* payload_100 = (struct APat_APat_ListIntIntTuple2Tuple3*)malloc(sizeof(struct APat_APat_ListIntIntTuple2Tuple3));
    (*(((struct APat_APat_ListIntIntTuple2Tuple3*)payload_100))) = tuple_230;
    struct APat_ variant_100 = (struct APat_){.tag = Call_, .Call_ = payload_100};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_229;
    tuple_229.t0 = variant_100;
    tuple_229.t1 = tokens_79;
    tuple_229.t2 = errors_55;
    match_217 = tuple_229;
    goto end_match_831;
next_833:;
end_match_831:;
    return match_217;
}

struct APat_APat_IntIntTuple2Tuple3 {
    struct APat_ t0;
    struct APat_ t1;
    struct IntIntTuple2 t2;
};

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatCons_(struct IntIntTuple2 baseLoc_16, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_149) {
    struct Token_IntIntTuple2Tuple2List* tokens_80 = arg_149.t0;
    struct StringIntIntTuple2Tuple2List* errors_56 = arg_149.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_231;
    tuple_231.t0 = tokens_80;
    tuple_231.t1 = errors_56;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_541 = parsePatCall_(baseLoc_16, tuple_231);
    struct APat_ head_2 = call_541.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_81 = call_541.t1;
    struct StringIntIntTuple2Tuple2List* errors_57 = call_541.t2;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_218;
    if ((!(tokens_81))) goto next_835;
    if ((tokens_81->head.t0.tag != ColonColon_)) goto next_835;
    struct IntIntTuple2 loc_47 = tokens_81->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_82 = tokens_81->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_232;
    tuple_232.t0 = tokens_82;
    tuple_232.t1 = errors_57;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_542 = parsePatCons_(baseLoc_16, tuple_232);
    struct APat_ tail_2 = call_542.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_83 = call_542.t1;
    struct StringIntIntTuple2Tuple2List* errors_58 = call_542.t2;
    struct APat_APat_IntIntTuple2Tuple3 tuple_234;
    tuple_234.t0 = head_2;
    tuple_234.t1 = tail_2;
    tuple_234.t2 = loc_47;
    struct APat_APat_IntIntTuple2Tuple3* payload_101 = (struct APat_APat_IntIntTuple2Tuple3*)malloc(sizeof(struct APat_APat_IntIntTuple2Tuple3));
    (*(((struct APat_APat_IntIntTuple2Tuple3*)payload_101))) = tuple_234;
    struct APat_ variant_101 = (struct APat_){.tag = Cons_2, .Cons_2 = payload_101};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_233;
    tuple_233.t0 = variant_101;
    tuple_233.t1 = tokens_83;
    tuple_233.t2 = errors_58;
    match_218 = tuple_233;
    goto end_match_834;
next_835:;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_235;
    tuple_235.t0 = head_2;
    tuple_235.t1 = tokens_81;
    tuple_235.t2 = errors_57;
    match_218 = tuple_235;
    goto end_match_834;
next_836:;
end_match_834:;
    return match_218;
}

struct APat_ATy_IntIntTuple2Tuple3 {
    struct APat_ t0;
    struct ATy_ t1;
    struct IntIntTuple2 t2;
};

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatAnno_(struct IntIntTuple2 baseLoc_17, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_150) {
    struct Token_IntIntTuple2Tuple2List* tokens_84 = arg_150.t0;
    struct StringIntIntTuple2Tuple2List* errors_59 = arg_150.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_236;
    tuple_236.t0 = tokens_84;
    tuple_236.t1 = errors_59;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_543 = parsePatCons_(baseLoc_17, tuple_236);
    struct APat_ pat_18 = call_543.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_85 = call_543.t1;
    struct StringIntIntTuple2Tuple2List* errors_60 = call_543.t2;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_219;
    if ((!(tokens_85))) goto next_838;
    if ((tokens_85->head.t0.tag != Colon_)) goto next_838;
    struct IntIntTuple2 loc_48 = tokens_85->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_86 = tokens_85->tail;
    struct IntIntTuple2 call_544 = nextLoc_1(tokens_86);
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_237;
    tuple_237.t0 = tokens_86;
    tuple_237.t1 = errors_60;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_545 = parseTy_(call_544, tuple_237);
    struct ATy_ ty_50 = call_545.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_87 = call_545.t1;
    struct StringIntIntTuple2Tuple2List* errors_61 = call_545.t2;
    struct APat_ATy_IntIntTuple2Tuple3 tuple_239;
    tuple_239.t0 = pat_18;
    tuple_239.t1 = ty_50;
    tuple_239.t2 = loc_48;
    struct APat_ATy_IntIntTuple2Tuple3* payload_102 = (struct APat_ATy_IntIntTuple2Tuple3*)malloc(sizeof(struct APat_ATy_IntIntTuple2Tuple3));
    (*(((struct APat_ATy_IntIntTuple2Tuple3*)payload_102))) = tuple_239;
    struct APat_ variant_102 = (struct APat_){.tag = Anno_, .Anno_ = payload_102};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_238;
    tuple_238.t0 = variant_102;
    tuple_238.t1 = tokens_87;
    tuple_238.t2 = errors_61;
    match_219 = tuple_238;
    goto end_match_837;
next_838:;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_240;
    tuple_240.t0 = pat_18;
    tuple_240.t1 = tokens_85;
    tuple_240.t2 = errors_60;
    match_219 = tuple_240;
    goto end_match_837;
next_839:;
end_match_837:;
    return match_219;
}

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_46(struct IntIntTuple2 baseLoc_18, struct APat_List* acc_29, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_151) {
    struct Token_IntIntTuple2Tuple2List* tokens_89 = arg_151.t0;
    struct StringIntIntTuple2Tuple2List* errors_63 = arg_151.t1;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_220;
    if ((!(tokens_89))) goto next_841;
    if ((tokens_89->head.t0.tag != Comma_)) goto next_841;
    struct Token_IntIntTuple2Tuple2List* tokens_90 = tokens_89->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_241;
    tuple_241.t0 = tokens_90;
    tuple_241.t1 = errors_63;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_546 = parsePatAnno_(baseLoc_18, tuple_241);
    struct APat_ second_3 = call_546.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_91 = call_546.t1;
    struct StringIntIntTuple2Tuple2List* errors_64 = call_546.t2;
    struct APat_List* list_68 = (struct APat_List*)malloc(sizeof(struct APat_List));
    list_68->head = second_3;
    list_68->tail = acc_29;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_242;
    tuple_242.t0 = tokens_91;
    tuple_242.t1 = errors_64;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_547 = go_46(baseLoc_18, list_68, tuple_242);
    match_220 = call_547;
    goto end_match_840;
next_841:;
    struct APat_List* call_548 = listRev_4(acc_29);
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_243;
    tuple_243.t0 = call_548;
    tuple_243.t1 = tokens_89;
    tuple_243.t2 = errors_63;
    match_220 = tuple_243;
    goto end_match_840;
next_842:;
end_match_840:;
    return match_220;
}

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatTuple_(struct IntIntTuple2 baseLoc_18, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_152) {
    struct Token_IntIntTuple2Tuple2List* tokens_88 = arg_152.t0;
    struct StringIntIntTuple2Tuple2List* errors_62 = arg_152.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_244;
    tuple_244.t0 = tokens_88;
    tuple_244.t1 = errors_62;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_549 = parsePatAnno_(baseLoc_18, tuple_244);
    struct APat_ itemPat_1 = call_549.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_92 = call_549.t1;
    struct StringIntIntTuple2Tuple2List* errors_65 = call_549.t2;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_221;
    if ((!(tokens_92))) goto next_844;
    if ((tokens_92->head.t0.tag != Comma_)) goto next_844;
    struct IntIntTuple2 loc_49 = tokens_92->head.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_245;
    tuple_245.t0 = tokens_92;
    tuple_245.t1 = errors_65;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_550 = go_46(baseLoc_18, NULL, tuple_245);
    struct APat_List* itemPats_2 = call_550.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_93 = call_550.t1;
    struct StringIntIntTuple2Tuple2List* errors_66 = call_550.t2;
    struct APat_List* list_69 = (struct APat_List*)malloc(sizeof(struct APat_List));
    list_69->head = itemPat_1;
    list_69->tail = itemPats_2;
    struct APat_ListIntIntTuple2Tuple2 tuple_247;
    tuple_247.t0 = list_69;
    tuple_247.t1 = loc_49;
    struct APat_ListIntIntTuple2Tuple2* payload_103 = (struct APat_ListIntIntTuple2Tuple2*)malloc(sizeof(struct APat_ListIntIntTuple2Tuple2));
    (*(((struct APat_ListIntIntTuple2Tuple2*)payload_103))) = tuple_247;
    struct APat_ variant_103 = (struct APat_){.tag = TupleLit_, .TupleLit_ = payload_103};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_246;
    tuple_246.t0 = variant_103;
    tuple_246.t1 = tokens_93;
    tuple_246.t2 = errors_66;
    match_221 = tuple_246;
    goto end_match_843;
next_844:;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_248;
    tuple_248.t0 = itemPat_1;
    tuple_248.t1 = tokens_92;
    tuple_248.t2 = errors_65;
    match_221 = tuple_248;
    goto end_match_843;
next_845:;
end_match_843:;
    return match_221;
}

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatAs_(struct IntIntTuple2 baseLoc_19, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_153) {
    struct Token_IntIntTuple2Tuple2List* tokens_94 = arg_153.t0;
    struct StringIntIntTuple2Tuple2List* errors_67 = arg_153.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_249;
    tuple_249.t0 = tokens_94;
    tuple_249.t1 = errors_67;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_551 = parsePatTuple_(baseLoc_19, tuple_249);
    struct APat_ pat_19 = call_551.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_95 = call_551.t1;
    struct StringIntIntTuple2Tuple2List* errors_68 = call_551.t2;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_222;
    if ((!(tokens_95))) goto next_847;
    if ((tokens_95->head.t0.tag != As_)) goto next_847;
    struct IntIntTuple2 loc_50 = tokens_95->head.t1;
    if ((!(tokens_95->tail))) goto next_847;
    if ((tokens_95->tail->head.t0.tag != Ident_)) goto next_847;
    struct String ident_22 = (*(tokens_95->tail->head.t0.Ident_));
    struct Token_IntIntTuple2Tuple2List* tokens_96 = tokens_95->tail->tail;
    struct APat_StringIntIntTuple2Tuple3 tuple_251;
    tuple_251.t0 = pat_19;
    tuple_251.t1 = ident_22;
    tuple_251.t2 = loc_50;
    struct APat_StringIntIntTuple2Tuple3* payload_104 = (struct APat_StringIntIntTuple2Tuple3*)malloc(sizeof(struct APat_StringIntIntTuple2Tuple3));
    (*(((struct APat_StringIntIntTuple2Tuple3*)payload_104))) = tuple_251;
    struct APat_ variant_104 = (struct APat_){.tag = As_1, .As_1 = payload_104};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_250;
    tuple_250.t0 = variant_104;
    tuple_250.t1 = tokens_96;
    tuple_250.t2 = errors_68;
    match_222 = tuple_250;
    goto end_match_846;
next_847:;
    if ((!(tokens_95))) goto next_848;
    if ((tokens_95->head.t0.tag != As_)) goto next_848;
    struct Token_IntIntTuple2Tuple2List* tokens_97 = tokens_95->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_252;
    tuple_252.t0 = tokens_97;
    tuple_252.t1 = errors_68;
    struct StringIntIntTuple2Tuple2List* call_552 = parseNewError_1((struct String){.str = "Expected an identifier", .len = 22}, tuple_252);
    struct StringIntIntTuple2Tuple2List* errors_69 = call_552;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_253;
    tuple_253.t0 = pat_19;
    tuple_253.t1 = tokens_97;
    tuple_253.t2 = errors_69;
    match_222 = tuple_253;
    goto end_match_846;
next_848:;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_254;
    tuple_254.t0 = pat_19;
    tuple_254.t1 = tokens_95;
    tuple_254.t2 = errors_68;
    match_222 = tuple_254;
    goto end_match_846;
next_849:;
end_match_846:;
    return match_222;
}

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatOr_(struct IntIntTuple2 baseLoc_20, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_154) {
    struct Token_IntIntTuple2Tuple2List* tokens_98 = arg_154.t0;
    struct StringIntIntTuple2Tuple2List* errors_70 = arg_154.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_255;
    tuple_255.t0 = tokens_98;
    tuple_255.t1 = errors_70;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_553 = parsePatAs_(baseLoc_20, tuple_255);
    struct APat_ lPat_ = call_553.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_99 = call_553.t1;
    struct StringIntIntTuple2Tuple2List* errors_71 = call_553.t2;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_223;
    if ((!(tokens_99))) goto next_851;
    if ((tokens_99->head.t0.tag != Pipe_)) goto next_851;
    struct IntIntTuple2 loc_51 = tokens_99->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_100 = tokens_99->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_256;
    tuple_256.t0 = tokens_100;
    tuple_256.t1 = errors_71;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_554 = parsePatOr_(baseLoc_20, tuple_256);
    struct APat_ rPat_ = call_554.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_101 = call_554.t1;
    struct StringIntIntTuple2Tuple2List* errors_72 = call_554.t2;
    struct APat_APat_IntIntTuple2Tuple3 tuple_258;
    tuple_258.t0 = lPat_;
    tuple_258.t1 = rPat_;
    tuple_258.t2 = loc_51;
    struct APat_APat_IntIntTuple2Tuple3* payload_105 = (struct APat_APat_IntIntTuple2Tuple3*)malloc(sizeof(struct APat_APat_IntIntTuple2Tuple3));
    (*(((struct APat_APat_IntIntTuple2Tuple3*)payload_105))) = tuple_258;
    struct APat_ variant_105 = (struct APat_){.tag = Or_2, .Or_2 = payload_105};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_257;
    tuple_257.t0 = variant_105;
    tuple_257.t1 = tokens_101;
    tuple_257.t2 = errors_72;
    match_223 = tuple_257;
    goto end_match_850;
next_851:;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_259;
    tuple_259.t0 = lPat_;
    tuple_259.t1 = tokens_99;
    tuple_259.t2 = errors_71;
    match_223 = tuple_259;
    goto end_match_850;
next_852:;
end_match_850:;
    return match_223;
}

struct StringAPat_ListIntIntTuple2Tuple3 {
    struct String t0;
    struct APat_List* t1;
    struct IntIntTuple2 t2;
};

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatLet_(struct IntIntTuple2 baseLoc_21, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_155) {
    struct Token_IntIntTuple2Tuple2List* tokens_102 = arg_155.t0;
    struct StringIntIntTuple2Tuple2List* errors_73 = arg_155.t1;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_224;
    if ((!(tokens_102))) goto next_854;
    if ((tokens_102->head.t0.tag != Ident_)) goto next_854;
    struct String callee_6 = (*(tokens_102->head.t0.Ident_));
    struct IntIntTuple2 calleeLoc_2 = tokens_102->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_103 = tokens_102->tail;
    int match_225;
    int call_555 = locInside_(baseLoc_21, calleeLoc_2);
    if ((!(call_555))) goto next_857;
    int call_556 = leadsPat_1(tokens_103);
    match_225 = call_556;
    goto end_match_856;
next_857:;
    if (call_555) goto next_858;
    match_225 = 0;
    goto end_match_856;
next_858:;
    exit(1);
end_match_856:;
    if ((!(match_225))) goto next_854;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_260;
    tuple_260.t0 = tokens_103;
    tuple_260.t1 = errors_73;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_557 = parsePatCallArgs_(baseLoc_21, calleeLoc_2, tuple_260);
    struct APat_List* args_7 = call_557.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_104 = call_557.t1;
    struct StringIntIntTuple2Tuple2List* errors_74 = call_557.t2;
    struct StringAPat_ListIntIntTuple2Tuple3 tuple_261;
    tuple_261.t0 = callee_6;
    tuple_261.t1 = args_7;
    tuple_261.t2 = calleeLoc_2;
    struct StringAPat_ListIntIntTuple2Tuple3* payload_106 = (struct StringAPat_ListIntIntTuple2Tuple3*)malloc(sizeof(struct StringAPat_ListIntIntTuple2Tuple3));
    (*(((struct StringAPat_ListIntIntTuple2Tuple3*)payload_106))) = tuple_261;
    struct APat_ variant_106 = (struct APat_){.tag = Fun_2, .Fun_2 = payload_106};
    struct APat_ pat_20 = variant_106;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_226;
    if ((!(tokens_104))) goto next_860;
    if ((tokens_104->head.t0.tag != Colon_)) goto next_860;
    struct IntIntTuple2 loc_52 = tokens_104->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_105 = tokens_104->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_262;
    tuple_262.t0 = tokens_105;
    tuple_262.t1 = errors_74;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_558 = parseTy_(baseLoc_21, tuple_262);
    struct ATy_ ty_51 = call_558.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_106 = call_558.t1;
    struct StringIntIntTuple2Tuple2List* errors_75 = call_558.t2;
    struct APat_ATy_IntIntTuple2Tuple3 tuple_264;
    tuple_264.t0 = pat_20;
    tuple_264.t1 = ty_51;
    tuple_264.t2 = loc_52;
    struct APat_ATy_IntIntTuple2Tuple3* payload_107 = (struct APat_ATy_IntIntTuple2Tuple3*)malloc(sizeof(struct APat_ATy_IntIntTuple2Tuple3));
    (*(((struct APat_ATy_IntIntTuple2Tuple3*)payload_107))) = tuple_264;
    struct APat_ variant_107 = (struct APat_){.tag = Anno_, .Anno_ = payload_107};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_263;
    tuple_263.t0 = variant_107;
    tuple_263.t1 = tokens_106;
    tuple_263.t2 = errors_75;
    match_226 = tuple_263;
    goto end_match_859;
next_860:;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_265;
    tuple_265.t0 = pat_20;
    tuple_265.t1 = tokens_104;
    tuple_265.t2 = errors_74;
    match_226 = tuple_265;
    goto end_match_859;
next_861:;
end_match_859:;
    match_224 = match_226;
    goto end_match_853;
next_854:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_266;
    tuple_266.t0 = tokens_102;
    tuple_266.t1 = errors_73;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_559 = parsePat_(baseLoc_21, tuple_266);
    match_224 = call_559;
    goto end_match_853;
next_855:;
end_match_853:;
    return match_224;
}

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePat_(struct IntIntTuple2 baseLoc_22, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_156) {
    struct Token_IntIntTuple2Tuple2List* tokens_107 = arg_156.t0;
    struct StringIntIntTuple2Tuple2List* errors_76 = arg_156.t1;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_227;
    int match_228;
    int call_560 = nextInside_1(baseLoc_22, tokens_107);
    if ((!(call_560))) goto next_864;
    int call_561 = leadsPat_1(tokens_107);
    match_228 = call_561;
    goto end_match_863;
next_864:;
    if (call_560) goto next_865;
    match_228 = 0;
    goto end_match_863;
next_865:;
    exit(1);
end_match_863:;
    if (match_228) goto next_866;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_267;
    tuple_267.t0 = tokens_107;
    tuple_267.t1 = errors_76;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_562 = parsePatError_1((struct String){.str = "Expected a pattern", .len = 18}, tuple_267);
    match_227 = call_562;
    goto end_match_862;
next_866:;
    if ((!(match_228))) goto next_867;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_268;
    tuple_268.t0 = tokens_107;
    tuple_268.t1 = errors_76;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_563 = parsePatOr_(baseLoc_22, tuple_268);
    match_227 = call_563;
    goto end_match_862;
next_867:;
    exit(1);
end_match_862:;
    return match_227;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseRange_(struct IntIntTuple2 baseLoc_23, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_157) {
    struct Token_IntIntTuple2Tuple2List* tokens_108 = arg_157.t0;
    struct StringIntIntTuple2Tuple2List* errors_77 = arg_157.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_269;
    tuple_269.t0 = tokens_108;
    tuple_269.t1 = errors_77;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_564 = parseExpr_(baseLoc_23, tuple_269);
    struct AExpr_ l_17 = call_564.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_109 = call_564.t1;
    struct StringIntIntTuple2Tuple2List* errors_78 = call_564.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_229;
    if ((!(tokens_109))) goto next_869;
    if ((tokens_109->head.t0.tag != DotDot_)) goto next_869;
    struct IntIntTuple2 loc_53 = tokens_109->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_110 = tokens_109->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_270;
    tuple_270.t0 = tokens_110;
    tuple_270.t1 = errors_78;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_565 = parseExpr_(baseLoc_23, tuple_270);
    struct AExpr_ r_30 = call_565.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_111 = call_565.t1;
    struct StringIntIntTuple2Tuple2List* errors_79 = call_565.t2;
    struct AExpr_List* list_71 = (struct AExpr_List*)malloc(sizeof(struct AExpr_List));
    list_71->head = r_30;
    list_71->tail = NULL;
    struct AExpr_List* list_70 = (struct AExpr_List*)malloc(sizeof(struct AExpr_List));
    list_70->head = l_17;
    list_70->tail = list_71;
    struct AExpr_ListIntIntTuple2Tuple2 tuple_272;
    tuple_272.t0 = list_70;
    tuple_272.t1 = loc_53;
    struct AExpr_ListIntIntTuple2Tuple2* payload_108 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_108))) = tuple_272;
    struct AExpr_ variant_108 = (struct AExpr_){.tag = Range_, .Range_ = payload_108};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_271;
    tuple_271.t0 = variant_108;
    tuple_271.t1 = tokens_111;
    tuple_271.t2 = errors_79;
    match_229 = tuple_271;
    goto end_match_868;
next_869:;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_273;
    tuple_273.t0 = l_17;
    tuple_273.t1 = tokens_109;
    tuple_273.t2 = errors_78;
    match_229 = tuple_273;
    goto end_match_868;
next_870:;
end_match_868:;
    return match_229;
}

struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct AExpr_List* t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseList_(struct IntIntTuple2 baseLoc_24, struct IntIntTuple2 bracketLoc_1, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_158) {
    struct Token_IntIntTuple2Tuple2List* tokens_112 = arg_158.t0;
    struct StringIntIntTuple2Tuple2List* errors_80 = arg_158.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_274;
    tuple_274.t0 = tokens_112;
    tuple_274.t1 = errors_80;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_566 = parseStmts_(baseLoc_24, tuple_274);
    struct AExpr_List* items_6 = call_566.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_113 = call_566.t1;
    struct StringIntIntTuple2Tuple2List* errors_81 = call_566.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 match_230;
    if ((!(tokens_113))) goto next_872;
    if ((tokens_113->head.t0.tag != BracketR_)) goto next_872;
    struct Token_IntIntTuple2Tuple2List* tokens_115 = tokens_113->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_275;
    tuple_275.t0 = tokens_115;
    tuple_275.t1 = errors_81;
    match_230 = tuple_275;
    goto end_match_871;
next_872:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_276;
    tuple_276.t0 = tokens_113;
    tuple_276.t1 = errors_81;
    struct StringIntIntTuple2Tuple2List* call_567 = parseNewError_1((struct String){.str = "Expected \']\'", .len = 12}, tuple_276);
    struct StringIntIntTuple2Tuple2List* errors_83 = call_567;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_277;
    tuple_277.t0 = tokens_113;
    tuple_277.t1 = errors_83;
    match_230 = tuple_277;
    goto end_match_871;
next_873:;
end_match_871:;
    struct Token_IntIntTuple2Tuple2List* tokens_114 = match_230.t0;
    struct StringIntIntTuple2Tuple2List* errors_82 = match_230.t1;
    struct AExpr_ListIntIntTuple2Tuple2 tuple_279;
    tuple_279.t0 = items_6;
    tuple_279.t1 = bracketLoc_1;
    struct AExpr_ListIntIntTuple2Tuple2* payload_109 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_109))) = tuple_279;
    struct AExpr_ variant_109 = (struct AExpr_){.tag = ListLit_1, .ListLit_1 = payload_109};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_278;
    tuple_278.t0 = variant_109;
    tuple_278.t1 = tokens_114;
    tuple_278.t2 = errors_82;
    return tuple_278;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseThenClause_(struct IntIntTuple2 baseLoc_25, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_159) {
    struct Token_IntIntTuple2Tuple2List* tokens_116 = arg_159.t0;
    struct StringIntIntTuple2Tuple2List* errors_84 = arg_159.t1;
    struct IntIntTuple2 call_568 = locAddX_(1, baseLoc_25);
    struct IntIntTuple2 innerBaseLoc_ = call_568;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_231;
    if ((!(tokens_116))) goto next_875;
    if ((tokens_116->head.t0.tag != Then_)) goto next_875;
    struct IntIntTuple2 thenLoc_ = tokens_116->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_117 = tokens_116->tail;
    int call_569 = locInside_(baseLoc_25, thenLoc_);
    if ((!(call_569))) goto next_875;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_280;
    tuple_280.t0 = tokens_117;
    tuple_280.t1 = errors_84;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_570 = parseSemi_(innerBaseLoc_, thenLoc_, tuple_280);
    match_231 = call_570;
    goto end_match_874;
next_875:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_281;
    tuple_281.t0 = tokens_116;
    tuple_281.t1 = errors_84;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_571 = parseExprError_1((struct String){.str = "Expected \'then\'", .len = 15}, tuple_281);
    match_231 = call_571;
    goto end_match_874;
next_876:;
end_match_874:;
    return match_231;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseElseClause_(struct IntIntTuple2 baseLoc_26, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_160) {
    struct Token_IntIntTuple2Tuple2List* tokens_118 = arg_160.t0;
    struct StringIntIntTuple2Tuple2List* errors_85 = arg_160.t1;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_232;
    if ((!(tokens_118))) goto next_878;
    if ((tokens_118->head.t0.tag != Else_)) goto next_878;
    struct IntIntTuple2 elseLoc_ = tokens_118->head.t1;
    if ((!(tokens_118->tail))) goto next_878;
    if ((tokens_118->tail->head.t0.tag != If_)) goto next_878;
    struct IntIntTuple2 nextIfLoc_ = tokens_118->tail->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_119 = tokens_118->tail->tail;
    int match_233;
    int call_572 = locInside_(baseLoc_26, elseLoc_);
    if ((!(call_572))) goto next_882;
    int call_573 = locIsSameRow_(elseLoc_, nextIfLoc_);
    match_233 = call_573;
    goto end_match_881;
next_882:;
    if (call_572) goto next_883;
    match_233 = 0;
    goto end_match_881;
next_883:;
    exit(1);
end_match_881:;
    if ((!(match_233))) goto next_878;
    struct Token_IntIntTuple2Tuple2 tuple_283;
    tuple_283.t0 = (struct Token_){.tag = If_};
    tuple_283.t1 = elseLoc_;
    struct Token_IntIntTuple2Tuple2List* list_72 = (struct Token_IntIntTuple2Tuple2List*)malloc(sizeof(struct Token_IntIntTuple2Tuple2List));
    list_72->head = tuple_283;
    list_72->tail = tokens_119;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_282;
    tuple_282.t0 = list_72;
    tuple_282.t1 = errors_85;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_574 = parseExpr_(baseLoc_26, tuple_282);
    match_232 = call_574;
    goto end_match_877;
next_878:;
    if ((!(tokens_118))) goto next_879;
    if ((tokens_118->head.t0.tag != Else_)) goto next_879;
    struct IntIntTuple2 elseLoc_1 = tokens_118->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_120 = tokens_118->tail;
    int call_575 = locInside_(baseLoc_26, elseLoc_1);
    if ((!(call_575))) goto next_879;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_284;
    tuple_284.t0 = tokens_120;
    tuple_284.t1 = errors_85;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_576 = parseSemi_(baseLoc_26, elseLoc_1, tuple_284);
    match_232 = call_576;
    goto end_match_877;
next_879:;
    struct IntIntTuple2* payload_110 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_110))) = baseLoc_26;
    struct AExpr_ variant_110 = (struct AExpr_){.tag = Missing_2, .Missing_2 = payload_110};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_285;
    tuple_285.t0 = variant_110;
    tuple_285.t1 = tokens_118;
    tuple_285.t2 = errors_85;
    match_232 = tuple_285;
    goto end_match_877;
next_880:;
end_match_877:;
    return match_232;
}

struct AExpr_AExpr_AExpr_IntIntTuple2Tuple4 {
    struct AExpr_ t0;
    struct AExpr_ t1;
    struct AExpr_ t2;
    struct IntIntTuple2 t3;
};

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseIf_(struct IntIntTuple2 ifLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_161) {
    struct Token_IntIntTuple2Tuple2List* tokens_121 = arg_161.t0;
    struct StringIntIntTuple2Tuple2List* errors_86 = arg_161.t1;
    struct IntIntTuple2 call_577 = locAddX_(1, ifLoc_);
    struct IntIntTuple2 innerBaseLoc_1 = call_577;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_286;
    tuple_286.t0 = tokens_121;
    tuple_286.t1 = errors_86;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_578 = parseExpr_(innerBaseLoc_1, tuple_286);
    struct AExpr_ cond_1 = call_578.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_122 = call_578.t1;
    struct StringIntIntTuple2Tuple2List* errors_87 = call_578.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_287;
    tuple_287.t0 = tokens_122;
    tuple_287.t1 = errors_87;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_579 = parseThenClause_(ifLoc_, tuple_287);
    struct AExpr_ body_9 = call_579.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_123 = call_579.t1;
    struct StringIntIntTuple2Tuple2List* errors_88 = call_579.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_288;
    tuple_288.t0 = tokens_123;
    tuple_288.t1 = errors_88;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_580 = parseElseClause_(ifLoc_, tuple_288);
    struct AExpr_ alt_1 = call_580.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_124 = call_580.t1;
    struct StringIntIntTuple2Tuple2List* errors_89 = call_580.t2;
    struct AExpr_AExpr_AExpr_IntIntTuple2Tuple4 tuple_290;
    tuple_290.t0 = cond_1;
    tuple_290.t1 = body_9;
    tuple_290.t2 = alt_1;
    tuple_290.t3 = ifLoc_;
    struct AExpr_AExpr_AExpr_IntIntTuple2Tuple4* payload_111 = (struct AExpr_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct AExpr_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct AExpr_AExpr_AExpr_IntIntTuple2Tuple4*)payload_111))) = tuple_290;
    struct AExpr_ variant_111 = (struct AExpr_){.tag = If_1, .If_1 = payload_111};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_289;
    tuple_289.t0 = variant_111;
    tuple_289.t1 = tokens_124;
    tuple_289.t2 = errors_89;
    return tuple_289;
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

struct AArm_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseMatchArm_(struct IntIntTuple2 matchLoc_, struct IntIntTuple2 armLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_162) {
    struct Token_IntIntTuple2Tuple2List* tokens_125 = arg_162.t0;
    struct StringIntIntTuple2Tuple2List* errors_90 = arg_162.t1;
    struct IntIntTuple2 call_581 = locAddX_(1, matchLoc_);
    struct IntIntTuple2 innerBaseLoc_2 = call_581;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_291;
    tuple_291.t0 = tokens_125;
    tuple_291.t1 = errors_90;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_582 = parsePat_(innerBaseLoc_2, tuple_291);
    struct APat_ pat_21 = call_582.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_126 = call_582.t1;
    struct StringIntIntTuple2Tuple2List* errors_91 = call_582.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_234;
    if ((!(tokens_126))) goto next_885;
    if ((tokens_126->head.t0.tag != When_)) goto next_885;
    struct Token_IntIntTuple2Tuple2List* tokens_128 = tokens_126->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_292;
    tuple_292.t0 = tokens_128;
    tuple_292.t1 = errors_91;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_583 = parseExpr_(innerBaseLoc_2, tuple_292);
    match_234 = call_583;
    goto end_match_884;
next_885:;
    struct IntIntTuple2 call_584 = nextLoc_1(tokens_126);
    struct IntIntTuple2* payload_112 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_112))) = call_584;
    struct AExpr_ variant_112 = (struct AExpr_){.tag = Missing_2, .Missing_2 = payload_112};
    struct AExpr_ guard_3 = variant_112;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_293;
    tuple_293.t0 = guard_3;
    tuple_293.t1 = tokens_126;
    tuple_293.t2 = errors_91;
    match_234 = tuple_293;
    goto end_match_884;
next_886:;
end_match_884:;
    struct AExpr_ guard_2 = match_234.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_127 = match_234.t1;
    struct StringIntIntTuple2Tuple2List* errors_92 = match_234.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_235;
    if ((!(tokens_127))) goto next_888;
    if ((tokens_127->head.t0.tag != Arrow_)) goto next_888;
    struct IntIntTuple2 arrowLoc_ = tokens_127->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_130 = tokens_127->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_294;
    tuple_294.t0 = tokens_130;
    tuple_294.t1 = errors_92;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_585 = parseSemi_(matchLoc_, arrowLoc_, tuple_294);
    match_235 = call_585;
    goto end_match_887;
next_888:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_295;
    tuple_295.t0 = tokens_127;
    tuple_295.t1 = errors_92;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_586 = parseExprError_1((struct String){.str = "Expected \'->\'", .len = 13}, tuple_295);
    match_235 = call_586;
    goto end_match_887;
next_889:;
end_match_887:;
    struct AExpr_ body_10 = match_235.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_129 = match_235.t1;
    struct StringIntIntTuple2Tuple2List* errors_93 = match_235.t2;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4 tuple_297;
    tuple_297.t0 = pat_21;
    tuple_297.t1 = guard_2;
    tuple_297.t2 = body_10;
    tuple_297.t3 = armLoc_;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4* payload_113 = (struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct APat_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)payload_113))) = tuple_297;
    struct AArm_ variant_113 = (struct AArm_){.tag = AArm_, .AArm_ = payload_113};
    struct AArm_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_296;
    tuple_296.t0 = variant_113;
    tuple_296.t1 = tokens_129;
    tuple_296.t2 = errors_93;
    return tuple_296;
}

struct AArm_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct AArm_List* t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct AArm_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_47(struct IntIntTuple2 matchLoc_1, struct AArm_List* acc_30, struct IntIntTuple2 armLoc_2, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_163) {
    struct Token_IntIntTuple2Tuple2List* tokens_136 = arg_163.t0;
    struct StringIntIntTuple2Tuple2List* errors_98 = arg_163.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_298;
    tuple_298.t0 = tokens_136;
    tuple_298.t1 = errors_98;
    struct AArm_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_587 = parseMatchArm_(matchLoc_1, armLoc_2, tuple_298);
    struct AArm_ arm_ = call_587.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_137 = call_587.t1;
    struct StringIntIntTuple2Tuple2List* errors_99 = call_587.t2;
    struct AArm_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_236;
    if ((!(tokens_137))) goto next_891;
    if ((tokens_137->head.t0.tag != Pipe_)) goto next_891;
    struct IntIntTuple2 pipeLoc_1 = tokens_137->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_138 = tokens_137->tail;
    int call_588 = locInside_(matchLoc_1, pipeLoc_1);
    if ((!(call_588))) goto next_891;
    struct AArm_List* list_73 = (struct AArm_List*)malloc(sizeof(struct AArm_List));
    list_73->head = arm_;
    list_73->tail = acc_30;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_299;
    tuple_299.t0 = tokens_138;
    tuple_299.t1 = errors_99;
    struct AArm_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_589 = go_47(matchLoc_1, list_73, pipeLoc_1, tuple_299);
    match_236 = call_589;
    goto end_match_890;
next_891:;
    struct AArm_List* list_74 = (struct AArm_List*)malloc(sizeof(struct AArm_List));
    list_74->head = arm_;
    list_74->tail = acc_30;
    struct AArm_List* call_590 = listRev_3(list_74);
    struct AArm_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_300;
    tuple_300.t0 = call_590;
    tuple_300.t1 = tokens_137;
    tuple_300.t2 = errors_99;
    match_236 = tuple_300;
    goto end_match_890;
next_892:;
end_match_890:;
    return match_236;
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

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseMatch_(struct IntIntTuple2 matchLoc_1, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_164) {
    struct Token_IntIntTuple2Tuple2List* tokens_131 = arg_164.t0;
    struct StringIntIntTuple2Tuple2List* errors_94 = arg_164.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_301;
    tuple_301.t0 = tokens_131;
    tuple_301.t1 = errors_94;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_591 = parseExpr_(matchLoc_1, tuple_301);
    struct AExpr_ target_3 = call_591.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_132 = call_591.t1;
    struct StringIntIntTuple2Tuple2List* errors_95 = call_591.t2;
    struct IntIntTuple2Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_237;
    if ((!(tokens_132))) goto next_894;
    if ((tokens_132->head.t0.tag != With_)) goto next_894;
    if ((!(tokens_132->tail))) goto next_894;
    if ((tokens_132->tail->head.t0.tag != Pipe_)) goto next_894;
    struct IntIntTuple2 pipeLoc_ = tokens_132->tail->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_134 = tokens_132->tail->tail;
    struct IntIntTuple2Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_302;
    tuple_302.t0 = pipeLoc_;
    tuple_302.t1 = tokens_134;
    tuple_302.t2 = errors_95;
    match_237 = tuple_302;
    goto end_match_893;
next_894:;
    if ((!(tokens_132))) goto next_895;
    if ((tokens_132->head.t0.tag != With_)) goto next_895;
    struct IntIntTuple2 withLoc_ = tokens_132->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_135 = tokens_132->tail;
    struct IntIntTuple2Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_303;
    tuple_303.t0 = withLoc_;
    tuple_303.t1 = tokens_135;
    tuple_303.t2 = errors_95;
    match_237 = tuple_303;
    goto end_match_893;
next_895:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_304;
    tuple_304.t0 = tokens_132;
    tuple_304.t1 = errors_95;
    struct StringIntIntTuple2Tuple2List* call_592 = parseNewError_1((struct String){.str = "Expected \'with\'", .len = 15}, tuple_304);
    struct StringIntIntTuple2Tuple2List* errors_97 = call_592;
    struct IntIntTuple2Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_305;
    tuple_305.t0 = matchLoc_1;
    tuple_305.t1 = tokens_132;
    tuple_305.t2 = errors_97;
    match_237 = tuple_305;
    goto end_match_893;
next_896:;
end_match_893:;
    struct IntIntTuple2 armLoc_1 = match_237.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_133 = match_237.t1;
    struct StringIntIntTuple2Tuple2List* errors_96 = match_237.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_306;
    tuple_306.t0 = tokens_133;
    tuple_306.t1 = errors_96;
    struct AArm_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_593 = go_47(matchLoc_1, NULL, armLoc_1, tuple_306);
    struct AArm_List* arms_3 = call_593.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_139 = call_593.t1;
    struct StringIntIntTuple2Tuple2List* errors_100 = call_593.t2;
    struct AExpr_AArm_ListIntIntTuple2Tuple3 tuple_308;
    tuple_308.t0 = target_3;
    tuple_308.t1 = arms_3;
    tuple_308.t2 = matchLoc_1;
    struct AExpr_AArm_ListIntIntTuple2Tuple3* payload_114 = (struct AExpr_AArm_ListIntIntTuple2Tuple3*)malloc(sizeof(struct AExpr_AArm_ListIntIntTuple2Tuple3));
    (*(((struct AExpr_AArm_ListIntIntTuple2Tuple3*)payload_114))) = tuple_308;
    struct AExpr_ variant_114 = (struct AExpr_){.tag = Match_1, .Match_1 = payload_114};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_307;
    tuple_307.t0 = variant_114;
    tuple_307.t1 = tokens_139;
    tuple_307.t2 = errors_100;
    return tuple_307;
}

struct APat_ListAExpr_IntIntTuple2Tuple3 {
    struct APat_List* t0;
    struct AExpr_ t1;
    struct IntIntTuple2 t2;
};

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseFun_(struct IntIntTuple2 baseLoc_27, struct IntIntTuple2 funLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_165) {
    struct Token_IntIntTuple2Tuple2List* tokens_140 = arg_165.t0;
    struct StringIntIntTuple2Tuple2List* errors_101 = arg_165.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_309;
    tuple_309.t0 = tokens_140;
    tuple_309.t1 = errors_101;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_594 = parsePatCallArgs_(baseLoc_27, funLoc_, tuple_309);
    struct APat_List* pats_3 = call_594.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_141 = call_594.t1;
    struct StringIntIntTuple2Tuple2List* errors_102 = call_594.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_238;
    if ((!(tokens_141))) goto next_898;
    if ((tokens_141->head.t0.tag != Arrow_)) goto next_898;
    struct IntIntTuple2 arrowLoc_1 = tokens_141->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_143 = tokens_141->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_310;
    tuple_310.t0 = tokens_143;
    tuple_310.t1 = errors_102;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_595 = parseSemi_(baseLoc_27, arrowLoc_1, tuple_310);
    match_238 = call_595;
    goto end_match_897;
next_898:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_311;
    tuple_311.t0 = tokens_141;
    tuple_311.t1 = errors_102;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_596 = parseExprError_1((struct String){.str = "Missing \'->\'", .len = 12}, tuple_311);
    match_238 = call_596;
    goto end_match_897;
next_899:;
end_match_897:;
    struct AExpr_ body_11 = match_238.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_142 = match_238.t1;
    struct StringIntIntTuple2Tuple2List* errors_103 = match_238.t2;
    struct APat_ListAExpr_IntIntTuple2Tuple3 tuple_313;
    tuple_313.t0 = pats_3;
    tuple_313.t1 = body_11;
    tuple_313.t2 = funLoc_;
    struct APat_ListAExpr_IntIntTuple2Tuple3* payload_115 = (struct APat_ListAExpr_IntIntTuple2Tuple3*)malloc(sizeof(struct APat_ListAExpr_IntIntTuple2Tuple3));
    (*(((struct APat_ListAExpr_IntIntTuple2Tuple3*)payload_115))) = tuple_313;
    struct AExpr_ variant_115 = (struct AExpr_){.tag = Fun_3, .Fun_3 = payload_115};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_312;
    tuple_312.t0 = variant_115;
    tuple_312.t1 = tokens_142;
    tuple_312.t2 = errors_103;
    return tuple_312;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseParenBody_(struct IntIntTuple2 baseLoc_28, struct IntIntTuple2 parenLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_166) {
    struct Token_IntIntTuple2Tuple2List* tokens_144 = arg_166.t0;
    struct StringIntIntTuple2Tuple2List* errors_104 = arg_166.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_314;
    tuple_314.t0 = tokens_144;
    tuple_314.t1 = errors_104;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_597 = parseSemi_(baseLoc_28, parenLoc_, tuple_314);
    struct AExpr_ body_12 = call_597.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_145 = call_597.t1;
    struct StringIntIntTuple2Tuple2List* errors_105 = call_597.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_239;
    if ((!(tokens_145))) goto next_901;
    if ((tokens_145->head.t0.tag != ParenR_)) goto next_901;
    struct Token_IntIntTuple2Tuple2List* tokens_146 = tokens_145->tail;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_315;
    tuple_315.t0 = body_12;
    tuple_315.t1 = tokens_146;
    tuple_315.t2 = errors_105;
    match_239 = tuple_315;
    goto end_match_900;
next_901:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_316;
    tuple_316.t0 = tokens_145;
    tuple_316.t1 = errors_105;
    struct StringIntIntTuple2Tuple2List* call_598 = parseNewError_1((struct String){.str = "Expected \')\'", .len = 12}, tuple_316);
    struct StringIntIntTuple2Tuple2List* errors_106 = call_598;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_317;
    tuple_317.t0 = body_12;
    tuple_317.t1 = tokens_145;
    tuple_317.t2 = errors_106;
    match_239 = tuple_317;
    goto end_match_900;
next_902:;
end_match_900:;
    return match_239;
}

struct Token_IntIntTuple2Tuple2List* parseAccessModifier_1(struct Token_IntIntTuple2Tuple2List* tokens_147) {
    struct Token_IntIntTuple2Tuple2List* match_240;
    if ((!(tokens_147))) goto next_904;
    struct Token_ t_12 = tokens_147->head.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_148 = tokens_147->tail;
    int call_599 = tokenIsAccessModifier_(t_12);
    if ((!(call_599))) goto next_904;
    match_240 = tokens_148;
    goto end_match_903;
next_904:;
    match_240 = tokens_147;
    goto end_match_903;
next_905:;
end_match_903:;
    return match_240;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseLet_(struct IntIntTuple2 letLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_167) {
    struct Token_IntIntTuple2Tuple2List* tokens_149 = arg_167.t0;
    struct StringIntIntTuple2Tuple2List* errors_107 = arg_167.t1;
    struct IntIntTuple2 call_600 = locAddX_(1, letLoc_);
    struct IntIntTuple2 innerBaseLoc_3 = call_600;
    struct Token_IntIntTuple2Tuple2List* call_601 = parseAccessModifier_1(tokens_149);
    struct Token_IntIntTuple2Tuple2List* tokens_150 = call_601;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_318;
    tuple_318.t0 = tokens_150;
    tuple_318.t1 = errors_107;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_602 = parsePatLet_(innerBaseLoc_3, tuple_318);
    struct APat_ pat_22 = call_602.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_151 = call_602.t1;
    struct StringIntIntTuple2Tuple2List* errors_108 = call_602.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_241;
    if ((!(tokens_151))) goto next_907;
    if ((tokens_151->head.t0.tag != Eq_)) goto next_907;
    struct IntIntTuple2 eqLoc_ = tokens_151->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_153 = tokens_151->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_319;
    tuple_319.t0 = tokens_153;
    tuple_319.t1 = errors_108;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_603 = parseSemi_(innerBaseLoc_3, eqLoc_, tuple_319);
    match_241 = call_603;
    goto end_match_906;
next_907:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_320;
    tuple_320.t0 = tokens_151;
    tuple_320.t1 = errors_108;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_604 = parseExprError_1((struct String){.str = "Missing \'=\'", .len = 11}, tuple_320);
    match_241 = call_604;
    goto end_match_906;
next_908:;
end_match_906:;
    struct AExpr_ body_13 = match_241.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_152 = match_241.t1;
    struct StringIntIntTuple2Tuple2List* errors_109 = match_241.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_242;
    if ((!(tokens_152))) goto next_910;
    if ((tokens_152->head.t0.tag != In_)) goto next_910;
    struct IntIntTuple2 inLoc_ = tokens_152->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_155 = tokens_152->tail;
    int call_605 = locInside_(letLoc_, inLoc_);
    if ((!(call_605))) goto next_910;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_321;
    tuple_321.t0 = tokens_155;
    tuple_321.t1 = errors_109;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_606 = parseSemi_(letLoc_, inLoc_, tuple_321);
    match_242 = call_606;
    goto end_match_909;
next_910:;
    if ((!(tokens_152))) goto next_911;
    struct IntIntTuple2 call_607 = nextLoc_1(tokens_152);
    int call_608 = locIsSameColumn_(call_607, letLoc_);
    if ((!(call_608))) goto next_911;
    struct IntIntTuple2 call_609 = nextLoc_1(tokens_152);
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_322;
    tuple_322.t0 = tokens_152;
    tuple_322.t1 = errors_109;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_610 = parseSemi_(letLoc_, call_609, tuple_322);
    match_242 = call_610;
    goto end_match_909;
next_911:;
    struct Token_IntIntTuple2Tuple2List* tokens_156 = tokens_152;
    struct AExpr_ListIntIntTuple2Tuple2 tuple_324;
    tuple_324.t0 = NULL;
    tuple_324.t1 = letLoc_;
    struct AExpr_ListIntIntTuple2Tuple2* payload_116 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_116))) = tuple_324;
    struct AExpr_ variant_116 = (struct AExpr_){.tag = TupleLit_1, .TupleLit_1 = payload_116};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_323;
    tuple_323.t0 = variant_116;
    tuple_323.t1 = tokens_156;
    tuple_323.t2 = errors_109;
    match_242 = tuple_323;
    goto end_match_909;
next_912:;
end_match_909:;
    struct AExpr_ next_11 = match_242.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_154 = match_242.t1;
    struct StringIntIntTuple2Tuple2List* errors_110 = match_242.t2;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4 tuple_326;
    tuple_326.t0 = pat_22;
    tuple_326.t1 = body_13;
    tuple_326.t2 = next_11;
    tuple_326.t3 = letLoc_;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4* payload_117 = (struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct APat_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)payload_117))) = tuple_326;
    struct AExpr_ variant_117 = (struct AExpr_){.tag = Let_1, .Let_1 = payload_117};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_325;
    tuple_325.t0 = variant_117;
    tuple_325.t1 = tokens_154;
    tuple_325.t2 = errors_110;
    return tuple_325;
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

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyDecl_(struct IntIntTuple2 typeLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_168) {
    struct Token_IntIntTuple2Tuple2List* tokens_157 = arg_168.t0;
    struct StringIntIntTuple2Tuple2List* errors_111 = arg_168.t1;
    struct IntIntTuple2 call_611 = locAddX_(1, typeLoc_);
    struct IntIntTuple2 baseLoc_29 = call_611;
    struct Token_IntIntTuple2Tuple2List* call_612 = parseAccessModifier_1(tokens_157);
    struct Token_IntIntTuple2Tuple2List* tokens_158 = call_612;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_243;
    if ((!(tokens_158))) goto next_914;
    if ((tokens_158->head.t0.tag != Ident_)) goto next_914;
    struct String tyIdent_ = (*(tokens_158->head.t0.Ident_));
    struct Token_IntIntTuple2Tuple2List* tokens_159 = tokens_158->tail;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_244;
    if ((!(tokens_159))) goto next_917;
    if ((tokens_159->head.t0.tag != Eq_)) goto next_917;
    struct Token_IntIntTuple2Tuple2List* tokens_160 = tokens_159->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_327;
    tuple_327.t0 = tokens_160;
    tuple_327.t1 = errors_111;
    struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_613 = parseTyDeclBody_(baseLoc_29, tuple_327);
    struct ATyDecl_ tyDecl_ = call_613.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_161 = call_613.t1;
    struct StringIntIntTuple2Tuple2List* errors_112 = call_613.t2;
    struct AExpr_ match_245;
    if ((tyDecl_.tag != Synonym_)) goto next_920;
    struct ATy_ ty_52 = (*(tyDecl_.Synonym_));
    struct StringATy_IntIntTuple2Tuple3 tuple_328;
    tuple_328.t0 = tyIdent_;
    tuple_328.t1 = ty_52;
    tuple_328.t2 = typeLoc_;
    struct StringATy_IntIntTuple2Tuple3* payload_118 = (struct StringATy_IntIntTuple2Tuple3*)malloc(sizeof(struct StringATy_IntIntTuple2Tuple3));
    (*(((struct StringATy_IntIntTuple2Tuple3*)payload_118))) = tuple_328;
    struct AExpr_ variant_118 = (struct AExpr_){.tag = TySynonym_, .TySynonym_ = payload_118};
    match_245 = variant_118;
    goto end_match_919;
next_920:;
    if ((tyDecl_.tag != Union_)) goto next_921;
    struct AVariant_List* variants_2 = (*(tyDecl_.Union_));
    struct StringAVariant_ListIntIntTuple2Tuple3 tuple_329;
    tuple_329.t0 = tyIdent_;
    tuple_329.t1 = variants_2;
    tuple_329.t2 = typeLoc_;
    struct StringAVariant_ListIntIntTuple2Tuple3* payload_119 = (struct StringAVariant_ListIntIntTuple2Tuple3*)malloc(sizeof(struct StringAVariant_ListIntIntTuple2Tuple3));
    (*(((struct StringAVariant_ListIntIntTuple2Tuple3*)payload_119))) = tuple_329;
    struct AExpr_ variant_119 = (struct AExpr_){.tag = TyUnion_, .TyUnion_ = payload_119};
    match_245 = variant_119;
    goto end_match_919;
next_921:;
    exit(1);
end_match_919:;
    struct AExpr_ expr_11 = match_245;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_330;
    tuple_330.t0 = expr_11;
    tuple_330.t1 = tokens_161;
    tuple_330.t2 = errors_112;
    match_244 = tuple_330;
    goto end_match_916;
next_917:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_331;
    tuple_331.t0 = tokens_159;
    tuple_331.t1 = errors_111;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_614 = parseTyError_1((struct String){.str = "Expected \'=\'", .len = 12}, tuple_331);
    struct ATy_ ty_53 = call_614.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_162 = call_614.t1;
    struct StringIntIntTuple2Tuple2List* errors_113 = call_614.t2;
    struct StringATy_IntIntTuple2Tuple3 tuple_333;
    tuple_333.t0 = tyIdent_;
    tuple_333.t1 = ty_53;
    tuple_333.t2 = typeLoc_;
    struct StringATy_IntIntTuple2Tuple3* payload_120 = (struct StringATy_IntIntTuple2Tuple3*)malloc(sizeof(struct StringATy_IntIntTuple2Tuple3));
    (*(((struct StringATy_IntIntTuple2Tuple3*)payload_120))) = tuple_333;
    struct AExpr_ variant_120 = (struct AExpr_){.tag = TySynonym_, .TySynonym_ = payload_120};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_332;
    tuple_332.t0 = variant_120;
    tuple_332.t1 = tokens_162;
    tuple_332.t2 = errors_113;
    match_244 = tuple_332;
    goto end_match_916;
next_918:;
end_match_916:;
    match_243 = match_244;
    goto end_match_913;
next_914:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_334;
    tuple_334.t0 = tokens_158;
    tuple_334.t1 = errors_111;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_615 = parseExprError_1((struct String){.str = "Expected identifier", .len = 19}, tuple_334);
    match_243 = call_615;
    goto end_match_913;
next_915:;
end_match_913:;
    return match_243;
}

struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct StringList* t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_48(struct StringList* acc_31, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_169) {
    struct Token_IntIntTuple2Tuple2List* tokens_165 = arg_169.t0;
    struct StringIntIntTuple2Tuple2List* errors_116 = arg_169.t1;
    struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_246;
    if ((!(tokens_165))) goto next_923;
    if ((tokens_165->head.t0.tag != Dot_)) goto next_923;
    if ((!(tokens_165->tail))) goto next_923;
    if ((tokens_165->tail->head.t0.tag != Ident_)) goto next_923;
    struct String ident_23 = (*(tokens_165->tail->head.t0.Ident_));
    struct Token_IntIntTuple2Tuple2List* tokens_166 = tokens_165->tail->tail;
    struct StringList* list_75 = (struct StringList*)malloc(sizeof(struct StringList));
    list_75->head = ident_23;
    list_75->tail = acc_31;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_335;
    tuple_335.t0 = tokens_166;
    tuple_335.t1 = errors_116;
    struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_616 = go_48(list_75, tuple_335);
    match_246 = call_616;
    goto end_match_922;
next_923:;
    if ((!(tokens_165))) goto next_924;
    if ((tokens_165->head.t0.tag != Dot_)) goto next_924;
    struct Token_IntIntTuple2Tuple2List* tokens_167 = tokens_165->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_336;
    tuple_336.t0 = tokens_167;
    tuple_336.t1 = errors_116;
    struct StringIntIntTuple2Tuple2List* call_617 = parseNewError_1((struct String){.str = "Expected identifier", .len = 19}, tuple_336);
    struct StringIntIntTuple2Tuple2List* errors_117 = call_617;
    struct StringList* call_618 = listRev_2(acc_31);
    struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_337;
    tuple_337.t0 = call_618;
    tuple_337.t1 = tokens_167;
    tuple_337.t2 = errors_117;
    match_246 = tuple_337;
    goto end_match_922;
next_924:;
    struct StringList* call_619 = listRev_2(acc_31);
    struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_338;
    tuple_338.t0 = call_619;
    tuple_338.t1 = tokens_165;
    tuple_338.t2 = errors_116;
    match_246 = tuple_338;
    goto end_match_922;
next_925:;
end_match_922:;
    return match_246;
}

struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePath_(struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_170) {
    struct Token_IntIntTuple2Tuple2List* tokens_164 = arg_170.t0;
    struct StringIntIntTuple2Tuple2List* errors_115 = arg_170.t1;
    struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_247;
    if ((!(tokens_164))) goto next_927;
    if ((tokens_164->head.t0.tag != Ident_)) goto next_927;
    struct String ident_24 = (*(tokens_164->head.t0.Ident_));
    struct Token_IntIntTuple2Tuple2List* tokens_168 = tokens_164->tail;
    struct StringList* list_76 = (struct StringList*)malloc(sizeof(struct StringList));
    list_76->head = ident_24;
    list_76->tail = NULL;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_339;
    tuple_339.t0 = tokens_168;
    tuple_339.t1 = errors_115;
    struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_620 = go_48(list_76, tuple_339);
    match_247 = call_620;
    goto end_match_926;
next_927:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_340;
    tuple_340.t0 = tokens_164;
    tuple_340.t1 = errors_115;
    struct StringIntIntTuple2Tuple2List* call_621 = parseNewError_1((struct String){.str = "Expected identifier", .len = 19}, tuple_340);
    struct StringIntIntTuple2Tuple2List* errors_118 = call_621;
    struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_341;
    tuple_341.t0 = NULL;
    tuple_341.t1 = tokens_164;
    tuple_341.t2 = errors_118;
    match_247 = tuple_341;
    goto end_match_926;
next_928:;
end_match_926:;
    return match_247;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseOpen_(struct IntIntTuple2 openLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_171) {
    struct Token_IntIntTuple2Tuple2List* tokens_163 = arg_171.t0;
    struct StringIntIntTuple2Tuple2List* errors_114 = arg_171.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_342;
    tuple_342.t0 = tokens_163;
    tuple_342.t1 = errors_114;
    struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_622 = parsePath_(tuple_342);
    struct StringList* path_3 = call_622.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_169 = call_622.t1;
    struct StringIntIntTuple2Tuple2List* errors_119 = call_622.t2;
    struct StringListIntIntTuple2Tuple2 tuple_344;
    tuple_344.t0 = path_3;
    tuple_344.t1 = openLoc_;
    struct StringListIntIntTuple2Tuple2* payload_121 = (struct StringListIntIntTuple2Tuple2*)malloc(sizeof(struct StringListIntIntTuple2Tuple2));
    (*(((struct StringListIntIntTuple2Tuple2*)payload_121))) = tuple_344;
    struct AExpr_ variant_121 = (struct AExpr_){.tag = Open_1, .Open_1 = payload_121};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_343;
    tuple_343.t0 = variant_121;
    tuple_343.t1 = tokens_169;
    tuple_343.t2 = errors_119;
    return tuple_343;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseAtom_(struct IntIntTuple2 baseLoc_30, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_172) {
    struct Token_IntIntTuple2Tuple2List* tokens_170 = arg_172.t0;
    struct StringIntIntTuple2Tuple2List* errors_120 = arg_172.t1;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_248;
    int call_623 = nextInside_1(baseLoc_30, tokens_170);
    if (call_623) goto next_930;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_345;
    tuple_345.t0 = tokens_170;
    tuple_345.t1 = errors_120;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_624 = parseExprError_1((struct String){.str = "Expected an expression", .len = 22}, tuple_345);
    match_248 = call_624;
    goto end_match_929;
next_930:;
    if ((!(tokens_170))) goto next_931;
    if ((tokens_170->head.t0.tag != ParenL_)) goto next_931;
    struct IntIntTuple2 loc_54 = tokens_170->head.t1;
    if ((!(tokens_170->tail))) goto next_931;
    if ((tokens_170->tail->head.t0.tag != ParenR_)) goto next_931;
    struct Token_IntIntTuple2Tuple2List* tokens_171 = tokens_170->tail->tail;
    struct AExpr_ListIntIntTuple2Tuple2 tuple_347;
    tuple_347.t0 = NULL;
    tuple_347.t1 = loc_54;
    struct AExpr_ListIntIntTuple2Tuple2* payload_122 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_122))) = tuple_347;
    struct AExpr_ variant_122 = (struct AExpr_){.tag = TupleLit_1, .TupleLit_1 = payload_122};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_346;
    tuple_346.t0 = variant_122;
    tuple_346.t1 = tokens_171;
    tuple_346.t2 = errors_120;
    match_248 = tuple_346;
    goto end_match_929;
next_931:;
    if ((!(tokens_170))) goto next_932;
    if ((tokens_170->head.t0.tag != Bool_1)) goto next_932;
    int value_16 = (*(tokens_170->head.t0.Bool_1));
    struct IntIntTuple2 loc_55 = tokens_170->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_172 = tokens_170->tail;
    int* payload_123 = (int*)malloc(sizeof(int));
    (*(((int*)payload_123))) = value_16;
    struct Lit_ variant_123 = (struct Lit_){.tag = Bool_, .Bool_ = payload_123};
    struct Lit_IntIntTuple2Tuple2 tuple_349;
    tuple_349.t0 = variant_123;
    tuple_349.t1 = loc_55;
    struct Lit_IntIntTuple2Tuple2* payload_124 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_124))) = tuple_349;
    struct AExpr_ variant_124 = (struct AExpr_){.tag = Lit_1, .Lit_1 = payload_124};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_348;
    tuple_348.t0 = variant_124;
    tuple_348.t1 = tokens_172;
    tuple_348.t2 = errors_120;
    match_248 = tuple_348;
    goto end_match_929;
next_932:;
    if ((!(tokens_170))) goto next_933;
    if ((tokens_170->head.t0.tag != Int_1)) goto next_933;
    int value_17 = (*(tokens_170->head.t0.Int_1));
    struct IntIntTuple2 loc_56 = tokens_170->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_173 = tokens_170->tail;
    int* payload_125 = (int*)malloc(sizeof(int));
    (*(((int*)payload_125))) = value_17;
    struct Lit_ variant_125 = (struct Lit_){.tag = Int_, .Int_ = payload_125};
    struct Lit_IntIntTuple2Tuple2 tuple_351;
    tuple_351.t0 = variant_125;
    tuple_351.t1 = loc_56;
    struct Lit_IntIntTuple2Tuple2* payload_126 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_126))) = tuple_351;
    struct AExpr_ variant_126 = (struct AExpr_){.tag = Lit_1, .Lit_1 = payload_126};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_350;
    tuple_350.t0 = variant_126;
    tuple_350.t1 = tokens_173;
    tuple_350.t2 = errors_120;
    match_248 = tuple_350;
    goto end_match_929;
next_933:;
    if ((!(tokens_170))) goto next_934;
    if ((tokens_170->head.t0.tag != Char_1)) goto next_934;
    char value_18 = (*(tokens_170->head.t0.Char_1));
    struct IntIntTuple2 loc_57 = tokens_170->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_174 = tokens_170->tail;
    char* payload_127 = (char*)malloc(sizeof(char));
    (*(((char*)payload_127))) = value_18;
    struct Lit_ variant_127 = (struct Lit_){.tag = Char_, .Char_ = payload_127};
    struct Lit_IntIntTuple2Tuple2 tuple_353;
    tuple_353.t0 = variant_127;
    tuple_353.t1 = loc_57;
    struct Lit_IntIntTuple2Tuple2* payload_128 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_128))) = tuple_353;
    struct AExpr_ variant_128 = (struct AExpr_){.tag = Lit_1, .Lit_1 = payload_128};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_352;
    tuple_352.t0 = variant_128;
    tuple_352.t1 = tokens_174;
    tuple_352.t2 = errors_120;
    match_248 = tuple_352;
    goto end_match_929;
next_934:;
    if ((!(tokens_170))) goto next_935;
    if ((tokens_170->head.t0.tag != Str_1)) goto next_935;
    struct String value_19 = (*(tokens_170->head.t0.Str_1));
    struct IntIntTuple2 loc_58 = tokens_170->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_175 = tokens_170->tail;
    struct String* payload_129 = (struct String*)malloc(sizeof(struct String));
    (*(((struct String*)payload_129))) = value_19;
    struct Lit_ variant_129 = (struct Lit_){.tag = Str_, .Str_ = payload_129};
    struct Lit_IntIntTuple2Tuple2 tuple_355;
    tuple_355.t0 = variant_129;
    tuple_355.t1 = loc_58;
    struct Lit_IntIntTuple2Tuple2* payload_130 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_130))) = tuple_355;
    struct AExpr_ variant_130 = (struct AExpr_){.tag = Lit_1, .Lit_1 = payload_130};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_354;
    tuple_354.t0 = variant_130;
    tuple_354.t1 = tokens_175;
    tuple_354.t2 = errors_120;
    match_248 = tuple_354;
    goto end_match_929;
next_935:;
    if ((!(tokens_170))) goto next_936;
    if ((tokens_170->head.t0.tag != Ident_)) goto next_936;
    struct String ident_25 = (*(tokens_170->head.t0.Ident_));
    struct IntIntTuple2 loc_59 = tokens_170->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_176 = tokens_170->tail;
    struct StringIntIntTuple2Tuple2 tuple_357;
    tuple_357.t0 = ident_25;
    tuple_357.t1 = loc_59;
    struct StringIntIntTuple2Tuple2* payload_131 = (struct StringIntIntTuple2Tuple2*)malloc(sizeof(struct StringIntIntTuple2Tuple2));
    (*(((struct StringIntIntTuple2Tuple2*)payload_131))) = tuple_357;
    struct AExpr_ variant_131 = (struct AExpr_){.tag = Ident_2, .Ident_2 = payload_131};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_356;
    tuple_356.t0 = variant_131;
    tuple_356.t1 = tokens_176;
    tuple_356.t2 = errors_120;
    match_248 = tuple_356;
    goto end_match_929;
next_936:;
    if ((!(tokens_170))) goto next_937;
    if ((tokens_170->head.t0.tag != ParenL_)) goto next_937;
    struct IntIntTuple2 parenLoc_1 = tokens_170->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_177 = tokens_170->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_358;
    tuple_358.t0 = tokens_177;
    tuple_358.t1 = errors_120;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_625 = parseParenBody_(baseLoc_30, parenLoc_1, tuple_358);
    match_248 = call_625;
    goto end_match_929;
next_937:;
    if ((!(tokens_170))) goto next_938;
    if ((tokens_170->head.t0.tag != BracketL_)) goto next_938;
    struct IntIntTuple2 bracketLoc_2 = tokens_170->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_178 = tokens_170->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_359;
    tuple_359.t0 = tokens_178;
    tuple_359.t1 = errors_120;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_626 = parseList_(baseLoc_30, bracketLoc_2, tuple_359);
    match_248 = call_626;
    goto end_match_929;
next_938:;
    if ((!(tokens_170))) goto next_939;
    if ((tokens_170->head.t0.tag != If_)) goto next_939;
    struct IntIntTuple2 loc_60 = tokens_170->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_179 = tokens_170->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_360;
    tuple_360.t0 = tokens_179;
    tuple_360.t1 = errors_120;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_627 = parseIf_(loc_60, tuple_360);
    match_248 = call_627;
    goto end_match_929;
next_939:;
    if ((!(tokens_170))) goto next_940;
    if ((tokens_170->head.t0.tag != Match_)) goto next_940;
    struct IntIntTuple2 loc_61 = tokens_170->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_180 = tokens_170->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_361;
    tuple_361.t0 = tokens_180;
    tuple_361.t1 = errors_120;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_628 = parseMatch_(loc_61, tuple_361);
    match_248 = call_628;
    goto end_match_929;
next_940:;
    if ((!(tokens_170))) goto next_941;
    if ((tokens_170->head.t0.tag != Fun_)) goto next_941;
    struct IntIntTuple2 loc_62 = tokens_170->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_181 = tokens_170->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_362;
    tuple_362.t0 = tokens_181;
    tuple_362.t1 = errors_120;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_629 = parseFun_(baseLoc_30, loc_62, tuple_362);
    match_248 = call_629;
    goto end_match_929;
next_941:;
    if ((!(tokens_170))) goto next_942;
    if ((tokens_170->head.t0.tag != Let_)) goto next_942;
    struct IntIntTuple2 letLoc_1 = tokens_170->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_182 = tokens_170->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_363;
    tuple_363.t0 = tokens_182;
    tuple_363.t1 = errors_120;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_630 = parseLet_(letLoc_1, tuple_363);
    match_248 = call_630;
    goto end_match_929;
next_942:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_364;
    tuple_364.t0 = tokens_170;
    tuple_364.t1 = errors_120;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_631 = parseExprError_1((struct String){.str = "Expected an expression", .len = 22}, tuple_364);
    match_248 = call_631;
    goto end_match_929;
next_943:;
end_match_929:;
    return match_248;
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

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_49(struct IntIntTuple2 baseLoc_31, struct AExpr_ acc_32, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_173) {
    struct Token_IntIntTuple2Tuple2List* tokens_185 = arg_173.t0;
    struct StringIntIntTuple2Tuple2List* errors_123 = arg_173.t1;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_249;
    if ((!(tokens_185))) goto next_945;
    if ((tokens_185->head.t0.tag != Dot_)) goto next_945;
    struct IntIntTuple2 loc_63 = tokens_185->head.t1;
    if ((!(tokens_185->tail))) goto next_945;
    if ((tokens_185->tail->head.t0.tag != BracketL_)) goto next_945;
    struct Token_IntIntTuple2Tuple2List* tokens_186 = tokens_185->tail->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_365;
    tuple_365.t0 = tokens_186;
    tuple_365.t1 = errors_123;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_632 = parseRange_(baseLoc_31, tuple_365);
    struct AExpr_ r_31 = call_632.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_187 = call_632.t1;
    struct StringIntIntTuple2Tuple2List* errors_124 = call_632.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 match_250;
    if ((!(tokens_187))) goto next_950;
    if ((tokens_187->head.t0.tag != BracketR_)) goto next_950;
    struct Token_IntIntTuple2Tuple2List* tokens_189 = tokens_187->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_366;
    tuple_366.t0 = tokens_189;
    tuple_366.t1 = errors_124;
    match_250 = tuple_366;
    goto end_match_949;
next_950:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_367;
    tuple_367.t0 = tokens_187;
    tuple_367.t1 = errors_124;
    struct StringIntIntTuple2Tuple2List* call_633 = parseNewError_1((struct String){.str = "Expected closing \']\'", .len = 20}, tuple_367);
    struct StringIntIntTuple2Tuple2List* errors_126 = call_633;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_368;
    tuple_368.t0 = tokens_187;
    tuple_368.t1 = errors_126;
    match_250 = tuple_368;
    goto end_match_949;
next_951:;
end_match_949:;
    struct Token_IntIntTuple2Tuple2List* tokens_188 = match_250.t0;
    struct StringIntIntTuple2Tuple2List* errors_125 = match_250.t1;
    struct AExpr_AExpr_IntIntTuple2Tuple3 tuple_369;
    tuple_369.t0 = acc_32;
    tuple_369.t1 = r_31;
    tuple_369.t2 = loc_63;
    struct AExpr_AExpr_IntIntTuple2Tuple3* payload_132 = (struct AExpr_AExpr_IntIntTuple2Tuple3*)malloc(sizeof(struct AExpr_AExpr_IntIntTuple2Tuple3));
    (*(((struct AExpr_AExpr_IntIntTuple2Tuple3*)payload_132))) = tuple_369;
    struct AExpr_ variant_132 = (struct AExpr_){.tag = Index_, .Index_ = payload_132};
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_370;
    tuple_370.t0 = tokens_188;
    tuple_370.t1 = errors_125;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_634 = go_49(baseLoc_31, variant_132, tuple_370);
    match_249 = call_634;
    goto end_match_944;
next_945:;
    if ((!(tokens_185))) goto next_946;
    if ((tokens_185->head.t0.tag != Dot_)) goto next_946;
    struct IntIntTuple2 loc_64 = tokens_185->head.t1;
    if ((!(tokens_185->tail))) goto next_946;
    if ((tokens_185->tail->head.t0.tag != Ident_)) goto next_946;
    struct String r_32 = (*(tokens_185->tail->head.t0.Ident_));
    struct Token_IntIntTuple2Tuple2List* tokens_190 = tokens_185->tail->tail;
    struct AExpr_StringIntIntTuple2Tuple3 tuple_371;
    tuple_371.t0 = acc_32;
    tuple_371.t1 = r_32;
    tuple_371.t2 = loc_64;
    struct AExpr_StringIntIntTuple2Tuple3* payload_133 = (struct AExpr_StringIntIntTuple2Tuple3*)malloc(sizeof(struct AExpr_StringIntIntTuple2Tuple3));
    (*(((struct AExpr_StringIntIntTuple2Tuple3*)payload_133))) = tuple_371;
    struct AExpr_ variant_133 = (struct AExpr_){.tag = Nav_1, .Nav_1 = payload_133};
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_372;
    tuple_372.t0 = tokens_190;
    tuple_372.t1 = errors_123;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_635 = go_49(baseLoc_31, variant_133, tuple_372);
    match_249 = call_635;
    goto end_match_944;
next_946:;
    if ((!(tokens_185))) goto next_947;
    if ((tokens_185->head.t0.tag != Dot_)) goto next_947;
    struct Token_IntIntTuple2Tuple2List* tokens_191 = tokens_185->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_373;
    tuple_373.t0 = tokens_191;
    tuple_373.t1 = errors_123;
    struct StringIntIntTuple2Tuple2List* call_636 = parseNewError_1((struct String){.str = "Expected .[] or .field", .len = 22}, tuple_373);
    struct StringIntIntTuple2Tuple2List* errors_127 = call_636;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_374;
    tuple_374.t0 = acc_32;
    tuple_374.t1 = tokens_191;
    tuple_374.t2 = errors_127;
    match_249 = tuple_374;
    goto end_match_944;
next_947:;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_375;
    tuple_375.t0 = acc_32;
    tuple_375.t1 = tokens_185;
    tuple_375.t2 = errors_123;
    match_249 = tuple_375;
    goto end_match_944;
next_948:;
end_match_944:;
    return match_249;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseSuffix_(struct IntIntTuple2 baseLoc_31, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_174) {
    struct Token_IntIntTuple2Tuple2List* tokens_183 = arg_174.t0;
    struct StringIntIntTuple2Tuple2List* errors_121 = arg_174.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_376;
    tuple_376.t0 = tokens_183;
    tuple_376.t1 = errors_121;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_637 = parseAtom_(baseLoc_31, tuple_376);
    struct AExpr_ l_18 = call_637.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_184 = call_637.t1;
    struct StringIntIntTuple2Tuple2List* errors_122 = call_637.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_377;
    tuple_377.t0 = tokens_184;
    tuple_377.t1 = errors_122;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_638 = go_49(baseLoc_31, l_18, tuple_377);
    return call_638;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_50(struct IntIntTuple2 argBaseLoc_1, struct IntIntTuple2 calleeLoc_3, struct IntIntTuple2 baseLoc_32, struct AExpr_ callee_8, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_175) {
    struct Token_IntIntTuple2Tuple2List* tokens_194 = arg_175.t0;
    struct StringIntIntTuple2Tuple2List* errors_130 = arg_175.t1;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_251;
    int match_252;
    int call_639 = nextInside_1(argBaseLoc_1, tokens_194);
    if ((!(call_639))) goto next_954;
    int call_640 = leadsArg_1(tokens_194);
    match_252 = call_640;
    goto end_match_953;
next_954:;
    if (call_639) goto next_955;
    match_252 = 0;
    goto end_match_953;
next_955:;
    exit(1);
end_match_953:;
    if ((!(match_252))) goto next_956;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_378;
    tuple_378.t0 = tokens_194;
    tuple_378.t1 = errors_130;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_641 = parseSuffix_(baseLoc_32, tuple_378);
    struct AExpr_ arg_2 = call_641.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_195 = call_641.t1;
    struct StringIntIntTuple2Tuple2List* errors_131 = call_641.t2;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_379;
    tuple_379.t0 = (struct Op_){.tag = App_};
    tuple_379.t1 = callee_8;
    tuple_379.t2 = arg_2;
    tuple_379.t3 = calleeLoc_3;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_134 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_134))) = tuple_379;
    struct AExpr_ variant_134 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_134};
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_380;
    tuple_380.t0 = tokens_195;
    tuple_380.t1 = errors_131;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_642 = go_50(argBaseLoc_1, calleeLoc_3, baseLoc_32, variant_134, tuple_380);
    match_251 = call_642;
    goto end_match_952;
next_956:;
    if (match_252) goto next_957;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_381;
    tuple_381.t0 = callee_8;
    tuple_381.t1 = tokens_194;
    tuple_381.t2 = errors_130;
    match_251 = tuple_381;
    goto end_match_952;
next_957:;
    exit(1);
end_match_952:;
    return match_251;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseApp_(struct IntIntTuple2 baseLoc_32, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_176) {
    struct Token_IntIntTuple2Tuple2List* tokens_192 = arg_176.t0;
    struct StringIntIntTuple2Tuple2List* errors_128 = arg_176.t1;
    struct IntIntTuple2 call_643 = nextLoc_1(tokens_192);
    struct IntIntTuple2 calleeLoc_3 = call_643;
    struct IntIntTuple2 call_644 = locAddX_(1, calleeLoc_3);
    struct IntIntTuple2 argBaseLoc_1 = call_644;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_382;
    tuple_382.t0 = tokens_192;
    tuple_382.t1 = errors_128;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_645 = parseSuffix_(baseLoc_32, tuple_382);
    struct AExpr_ callee_7 = call_645.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_193 = call_645.t1;
    struct StringIntIntTuple2Tuple2List* errors_129 = call_645.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_383;
    tuple_383.t0 = tokens_193;
    tuple_383.t1 = errors_129;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_646 = go_50(argBaseLoc_1, calleeLoc_3, baseLoc_32, callee_7, tuple_383);
    return call_646;
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

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePrefix_(struct IntIntTuple2 baseLoc_33, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_177) {
    struct Token_IntIntTuple2Tuple2List* tokens_196 = arg_177.t0;
    struct StringIntIntTuple2Tuple2List* errors_132 = arg_177.t1;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_253;
    if ((!(tokens_196))) goto next_959;
    if ((tokens_196->head.t0.tag != Minus_)) goto next_959;
    struct IntIntTuple2 loc_65 = tokens_196->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_197 = tokens_196->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_384;
    tuple_384.t0 = tokens_197;
    tuple_384.t1 = errors_132;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_647 = parseApp_(baseLoc_33, tuple_384);
    struct AExpr_ arg_3 = call_647.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_198 = call_647.t1;
    struct StringIntIntTuple2Tuple2List* errors_133 = call_647.t2;
    struct UniOp_AExpr_IntIntTuple2Tuple3 tuple_386;
    tuple_386.t0 = (struct UniOp_){.tag = Neg_};
    tuple_386.t1 = arg_3;
    tuple_386.t2 = loc_65;
    struct UniOp_AExpr_IntIntTuple2Tuple3* payload_135 = (struct UniOp_AExpr_IntIntTuple2Tuple3*)malloc(sizeof(struct UniOp_AExpr_IntIntTuple2Tuple3));
    (*(((struct UniOp_AExpr_IntIntTuple2Tuple3*)payload_135))) = tuple_386;
    struct AExpr_ variant_135 = (struct AExpr_){.tag = Uni_, .Uni_ = payload_135};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_385;
    tuple_385.t0 = variant_135;
    tuple_385.t1 = tokens_198;
    tuple_385.t2 = errors_133;
    match_253 = tuple_385;
    goto end_match_958;
next_959:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_387;
    tuple_387.t0 = tokens_196;
    tuple_387.t1 = errors_132;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_648 = parseApp_(baseLoc_33, tuple_387);
    match_253 = call_648;
    goto end_match_958;
next_960:;
end_match_958:;
    return match_253;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseNextLevelOp_(struct OpLevel_ level_1, struct IntIntTuple2 baseLoc_34, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_178) {
    struct Token_IntIntTuple2Tuple2List* tokens_199 = arg_178.t0;
    struct StringIntIntTuple2Tuple2List* errors_134 = arg_178.t1;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_254;
    struct OpLevel_ call_649 = opLevelToNext_(level_1);
    if ((call_649.tag != Prefix_)) goto next_962;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_388;
    tuple_388.t0 = tokens_199;
    tuple_388.t1 = errors_134;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_650 = parsePrefix_(baseLoc_34, tuple_388);
    match_254 = call_650;
    goto end_match_961;
next_962:;
    struct OpLevel_ nextLevel_ = call_649;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_389;
    tuple_389.t0 = tokens_199;
    tuple_389.t1 = errors_134;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_651 = parseOp_(nextLevel_, baseLoc_34, tuple_389);
    match_254 = call_651;
    goto end_match_961;
next_963:;
end_match_961:;
    return match_254;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 nextL_(struct IntIntTuple2 baseLoc_35, struct OpLevel_ level_2, struct AExpr_ expr_12, struct Op_ op_, struct IntIntTuple2 opLoc_2, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_179) {
    struct Token_IntIntTuple2Tuple2List* tokens_201 = arg_179.t0;
    struct StringIntIntTuple2Tuple2List* errors_136 = arg_179.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_390;
    tuple_390.t0 = tokens_201;
    tuple_390.t1 = errors_136;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_652 = parseNextLevelOp_(level_2, baseLoc_35, tuple_390);
    struct AExpr_ second_4 = call_652.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_202 = call_652.t1;
    struct StringIntIntTuple2Tuple2List* errors_137 = call_652.t2;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_391;
    tuple_391.t0 = op_;
    tuple_391.t1 = expr_12;
    tuple_391.t2 = second_4;
    tuple_391.t3 = opLoc_2;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_136 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_136))) = tuple_391;
    struct AExpr_ variant_136 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_136};
    struct AExpr_ expr_13 = variant_136;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_392;
    tuple_392.t0 = tokens_202;
    tuple_392.t1 = errors_137;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_653 = parseOps_(level_2, baseLoc_35, expr_13, tuple_392);
    return call_653;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 nextR_(struct IntIntTuple2 baseLoc_35, struct OpLevel_ level_2, struct AExpr_ expr_14, struct Op_ op_1, struct IntIntTuple2 opLoc_3, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_180) {
    struct Token_IntIntTuple2Tuple2List* tokens_203 = arg_180.t0;
    struct StringIntIntTuple2Tuple2List* errors_138 = arg_180.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_393;
    tuple_393.t0 = tokens_203;
    tuple_393.t1 = errors_138;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_654 = parseOp_(level_2, baseLoc_35, tuple_393);
    struct AExpr_ second_5 = call_654.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_204 = call_654.t1;
    struct StringIntIntTuple2Tuple2List* errors_139 = call_654.t2;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_394;
    tuple_394.t0 = op_1;
    tuple_394.t1 = expr_14;
    tuple_394.t2 = second_5;
    tuple_394.t3 = opLoc_3;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_137 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_137))) = tuple_394;
    struct AExpr_ variant_137 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_137};
    struct AExpr_ expr_15 = variant_137;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_395;
    tuple_395.t0 = tokens_204;
    tuple_395.t1 = errors_139;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_655 = parseOps_(level_2, baseLoc_35, expr_15, tuple_395);
    return call_655;
}

struct OpLevel_Token_IntIntTuple2Tuple2ListTuple2 {
    struct OpLevel_ t0;
    struct Token_IntIntTuple2Tuple2List* t1;
};

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseOps_(struct OpLevel_ level_2, struct IntIntTuple2 baseLoc_35, struct AExpr_ first_3, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_181) {
    struct Token_IntIntTuple2Tuple2List* tokens_200 = arg_181.t0;
    struct StringIntIntTuple2Tuple2List* errors_135 = arg_181.t1;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_255;
    struct OpLevel_Token_IntIntTuple2Tuple2ListTuple2 tuple_396;
    tuple_396.t0 = level_2;
    tuple_396.t1 = tokens_200;
    if ((tuple_396.t0.tag != Or_)) goto next_965;
    if ((!(tuple_396.t1))) goto next_965;
    if ((tuple_396.t1->head.t0.tag != PipePipe_)) goto next_965;
    struct IntIntTuple2 opLoc_4 = tuple_396.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_205 = tuple_396.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_397;
    tuple_397.t0 = tokens_205;
    tuple_397.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_656 = nextL_(baseLoc_35, level_2, first_3, (struct Op_){.tag = Or_1}, opLoc_4, tuple_397);
    match_255 = call_656;
    goto end_match_964;
next_965:;
    if ((tuple_396.t0.tag != And_)) goto next_966;
    if ((!(tuple_396.t1))) goto next_966;
    if ((tuple_396.t1->head.t0.tag != AmpAmp_)) goto next_966;
    struct IntIntTuple2 opLoc_5 = tuple_396.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_206 = tuple_396.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_398;
    tuple_398.t0 = tokens_206;
    tuple_398.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_657 = nextL_(baseLoc_35, level_2, first_3, (struct Op_){.tag = And_1}, opLoc_5, tuple_398);
    match_255 = call_657;
    goto end_match_964;
next_966:;
    if ((tuple_396.t0.tag != Cmp_)) goto next_967;
    if ((!(tuple_396.t1))) goto next_967;
    if ((tuple_396.t1->head.t0.tag != Eq_)) goto next_967;
    struct IntIntTuple2 opLoc_6 = tuple_396.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_207 = tuple_396.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_399;
    tuple_399.t0 = tokens_207;
    tuple_399.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_658 = nextL_(baseLoc_35, level_2, first_3, (struct Op_){.tag = Eq_1}, opLoc_6, tuple_399);
    match_255 = call_658;
    goto end_match_964;
next_967:;
    if ((tuple_396.t0.tag != Cmp_)) goto next_968;
    if ((!(tuple_396.t1))) goto next_968;
    if ((tuple_396.t1->head.t0.tag != LtGt_)) goto next_968;
    struct IntIntTuple2 opLoc_7 = tuple_396.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_208 = tuple_396.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_400;
    tuple_400.t0 = tokens_208;
    tuple_400.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_659 = nextL_(baseLoc_35, level_2, first_3, (struct Op_){.tag = Ne_}, opLoc_7, tuple_400);
    match_255 = call_659;
    goto end_match_964;
next_968:;
    if ((tuple_396.t0.tag != Cmp_)) goto next_969;
    if ((!(tuple_396.t1))) goto next_969;
    if ((tuple_396.t1->head.t0.tag != Lt_)) goto next_969;
    struct IntIntTuple2 opLoc_8 = tuple_396.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_209 = tuple_396.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_401;
    tuple_401.t0 = tokens_209;
    tuple_401.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_660 = nextL_(baseLoc_35, level_2, first_3, (struct Op_){.tag = Lt_1}, opLoc_8, tuple_401);
    match_255 = call_660;
    goto end_match_964;
next_969:;
    if ((tuple_396.t0.tag != Cmp_)) goto next_970;
    if ((!(tuple_396.t1))) goto next_970;
    if ((tuple_396.t1->head.t0.tag != LtEq_)) goto next_970;
    struct IntIntTuple2 opLoc_9 = tuple_396.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_210 = tuple_396.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_402;
    tuple_402.t0 = tokens_210;
    tuple_402.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_661 = nextL_(baseLoc_35, level_2, first_3, (struct Op_){.tag = Le_}, opLoc_9, tuple_402);
    match_255 = call_661;
    goto end_match_964;
next_970:;
    if ((tuple_396.t0.tag != Cmp_)) goto next_971;
    if ((!(tuple_396.t1))) goto next_971;
    if ((tuple_396.t1->head.t0.tag != Gt_)) goto next_971;
    struct IntIntTuple2 opLoc_10 = tuple_396.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_211 = tuple_396.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_403;
    tuple_403.t0 = tokens_211;
    tuple_403.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_662 = nextL_(baseLoc_35, level_2, first_3, (struct Op_){.tag = Gt_1}, opLoc_10, tuple_403);
    match_255 = call_662;
    goto end_match_964;
next_971:;
    if ((tuple_396.t0.tag != Cmp_)) goto next_972;
    if ((!(tuple_396.t1))) goto next_972;
    if ((tuple_396.t1->head.t0.tag != GtEq_)) goto next_972;
    struct IntIntTuple2 opLoc_11 = tuple_396.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_212 = tuple_396.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_404;
    tuple_404.t0 = tokens_212;
    tuple_404.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_663 = nextL_(baseLoc_35, level_2, first_3, (struct Op_){.tag = Ge_}, opLoc_11, tuple_404);
    match_255 = call_663;
    goto end_match_964;
next_972:;
    if ((tuple_396.t0.tag != Pipe_1)) goto next_973;
    if ((!(tuple_396.t1))) goto next_973;
    if ((tuple_396.t1->head.t0.tag != PipeGt_)) goto next_973;
    struct IntIntTuple2 opLoc_12 = tuple_396.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_213 = tuple_396.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_405;
    tuple_405.t0 = tokens_213;
    tuple_405.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_664 = nextL_(baseLoc_35, level_2, first_3, (struct Op_){.tag = Pipe_2}, opLoc_12, tuple_405);
    match_255 = call_664;
    goto end_match_964;
next_973:;
    if ((tuple_396.t0.tag != Cons_)) goto next_974;
    if ((!(tuple_396.t1))) goto next_974;
    if ((tuple_396.t1->head.t0.tag != ColonColon_)) goto next_974;
    struct IntIntTuple2 opLoc_13 = tuple_396.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_214 = tuple_396.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_406;
    tuple_406.t0 = tokens_214;
    tuple_406.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_665 = nextR_(baseLoc_35, level_2, first_3, (struct Op_){.tag = Cons_1}, opLoc_13, tuple_406);
    match_255 = call_665;
    goto end_match_964;
next_974:;
    if ((tuple_396.t0.tag != Add_)) goto next_975;
    if ((!(tuple_396.t1))) goto next_975;
    if ((tuple_396.t1->head.t0.tag != Plus_)) goto next_975;
    struct IntIntTuple2 opLoc_14 = tuple_396.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_215 = tuple_396.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_407;
    tuple_407.t0 = tokens_215;
    tuple_407.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_666 = nextL_(baseLoc_35, level_2, first_3, (struct Op_){.tag = Add_1}, opLoc_14, tuple_407);
    match_255 = call_666;
    goto end_match_964;
next_975:;
    if ((tuple_396.t0.tag != Add_)) goto next_976;
    if ((!(tuple_396.t1))) goto next_976;
    if ((tuple_396.t1->head.t0.tag != Minus_)) goto next_976;
    struct IntIntTuple2 opLoc_15 = tuple_396.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_216 = tuple_396.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_408;
    tuple_408.t0 = tokens_216;
    tuple_408.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_667 = nextL_(baseLoc_35, level_2, first_3, (struct Op_){.tag = Sub_}, opLoc_15, tuple_408);
    match_255 = call_667;
    goto end_match_964;
next_976:;
    if ((tuple_396.t0.tag != Mul_)) goto next_977;
    if ((!(tuple_396.t1))) goto next_977;
    if ((tuple_396.t1->head.t0.tag != Star_)) goto next_977;
    struct IntIntTuple2 opLoc_16 = tuple_396.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_217 = tuple_396.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_409;
    tuple_409.t0 = tokens_217;
    tuple_409.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_668 = nextL_(baseLoc_35, level_2, first_3, (struct Op_){.tag = Mul_1}, opLoc_16, tuple_409);
    match_255 = call_668;
    goto end_match_964;
next_977:;
    if ((tuple_396.t0.tag != Mul_)) goto next_978;
    if ((!(tuple_396.t1))) goto next_978;
    if ((tuple_396.t1->head.t0.tag != Slash_)) goto next_978;
    struct IntIntTuple2 opLoc_17 = tuple_396.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_218 = tuple_396.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_410;
    tuple_410.t0 = tokens_218;
    tuple_410.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_669 = nextL_(baseLoc_35, level_2, first_3, (struct Op_){.tag = Div_}, opLoc_17, tuple_410);
    match_255 = call_669;
    goto end_match_964;
next_978:;
    if ((tuple_396.t0.tag != Mul_)) goto next_979;
    if ((!(tuple_396.t1))) goto next_979;
    if ((tuple_396.t1->head.t0.tag != Percent_)) goto next_979;
    struct IntIntTuple2 opLoc_18 = tuple_396.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_219 = tuple_396.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_411;
    tuple_411.t0 = tokens_219;
    tuple_411.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_670 = nextL_(baseLoc_35, level_2, first_3, (struct Op_){.tag = Mod_}, opLoc_18, tuple_411);
    match_255 = call_670;
    goto end_match_964;
next_979:;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_412;
    tuple_412.t0 = first_3;
    tuple_412.t1 = tokens_200;
    tuple_412.t2 = errors_135;
    match_255 = tuple_412;
    goto end_match_964;
next_980:;
end_match_964:;
    return match_255;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseOp_(struct OpLevel_ level_3, struct IntIntTuple2 baseLoc_36, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_182) {
    struct Token_IntIntTuple2Tuple2List* tokens_220 = arg_182.t0;
    struct StringIntIntTuple2Tuple2List* errors_140 = arg_182.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_413;
    tuple_413.t0 = tokens_220;
    tuple_413.t1 = errors_140;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_671 = parseNextLevelOp_(level_3, baseLoc_36, tuple_413);
    struct AExpr_ first_4 = call_671.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_221 = call_671.t1;
    struct StringIntIntTuple2Tuple2List* errors_141 = call_671.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_414;
    tuple_414.t0 = tokens_221;
    tuple_414.t1 = errors_141;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_672 = parseOps_(level_3, baseLoc_36, first_4, tuple_414);
    return call_672;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTupleItem_(struct IntIntTuple2 baseLoc_37, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_183) {
    struct Token_IntIntTuple2Tuple2List* tokens_222 = arg_183.t0;
    struct StringIntIntTuple2Tuple2List* errors_142 = arg_183.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_415;
    tuple_415.t0 = tokens_222;
    tuple_415.t1 = errors_142;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_673 = parseOp_((struct OpLevel_){.tag = Or_}, baseLoc_37, tuple_415);
    return call_673;
}

struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_51(struct IntIntTuple2 baseLoc_38, struct AExpr_List* acc_33, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_184) {
    struct Token_IntIntTuple2Tuple2List* tokens_224 = arg_184.t0;
    struct StringIntIntTuple2Tuple2List* errors_144 = arg_184.t1;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_256;
    if ((!(tokens_224))) goto next_982;
    if ((tokens_224->head.t0.tag != Comma_)) goto next_982;
    struct Token_IntIntTuple2Tuple2List* tokens_225 = tokens_224->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_416;
    tuple_416.t0 = tokens_225;
    tuple_416.t1 = errors_144;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_674 = parseTupleItem_(baseLoc_38, tuple_416);
    struct AExpr_ second_6 = call_674.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_226 = call_674.t1;
    struct StringIntIntTuple2Tuple2List* errors_145 = call_674.t2;
    struct AExpr_List* list_77 = (struct AExpr_List*)malloc(sizeof(struct AExpr_List));
    list_77->head = second_6;
    list_77->tail = acc_33;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_417;
    tuple_417.t0 = tokens_226;
    tuple_417.t1 = errors_145;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_675 = go_51(baseLoc_38, list_77, tuple_417);
    match_256 = call_675;
    goto end_match_981;
next_982:;
    struct Token_IntIntTuple2Tuple2List* tokens_227 = tokens_224;
    struct AExpr_List* call_676 = listRev_1(acc_33);
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_418;
    tuple_418.t0 = call_676;
    tuple_418.t1 = tokens_227;
    tuple_418.t2 = errors_144;
    match_256 = tuple_418;
    goto end_match_981;
next_983:;
end_match_981:;
    return match_256;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTuple_(struct IntIntTuple2 baseLoc_38, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_185) {
    struct Token_IntIntTuple2Tuple2List* tokens_223 = arg_185.t0;
    struct StringIntIntTuple2Tuple2List* errors_143 = arg_185.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_419;
    tuple_419.t0 = tokens_223;
    tuple_419.t1 = errors_143;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_677 = parseTupleItem_(baseLoc_38, tuple_419);
    struct AExpr_ item_ = call_677.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_228 = call_677.t1;
    struct StringIntIntTuple2Tuple2List* errors_146 = call_677.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_257;
    if ((!(tokens_228))) goto next_985;
    if ((tokens_228->head.t0.tag != Comma_)) goto next_985;
    struct IntIntTuple2 loc_66 = tokens_228->head.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_420;
    tuple_420.t0 = tokens_228;
    tuple_420.t1 = errors_146;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_678 = go_51(baseLoc_38, NULL, tuple_420);
    struct AExpr_List* items_7 = call_678.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_229 = call_678.t1;
    struct StringIntIntTuple2Tuple2List* errors_147 = call_678.t2;
    struct AExpr_List* list_78 = (struct AExpr_List*)malloc(sizeof(struct AExpr_List));
    list_78->head = item_;
    list_78->tail = items_7;
    struct AExpr_ListIntIntTuple2Tuple2 tuple_422;
    tuple_422.t0 = list_78;
    tuple_422.t1 = loc_66;
    struct AExpr_ListIntIntTuple2Tuple2* payload_138 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_138))) = tuple_422;
    struct AExpr_ variant_138 = (struct AExpr_){.tag = TupleLit_1, .TupleLit_1 = payload_138};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_421;
    tuple_421.t0 = variant_138;
    tuple_421.t1 = tokens_229;
    tuple_421.t2 = errors_147;
    match_257 = tuple_421;
    goto end_match_984;
next_985:;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_423;
    tuple_423.t0 = item_;
    tuple_423.t1 = tokens_228;
    tuple_423.t2 = errors_146;
    match_257 = tuple_423;
    goto end_match_984;
next_986:;
end_match_984:;
    return match_257;
}

struct AExpr_ATy_IntIntTuple2Tuple3 {
    struct AExpr_ t0;
    struct ATy_ t1;
    struct IntIntTuple2 t2;
};

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseAnno_(struct IntIntTuple2 baseLoc_39, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_186) {
    struct Token_IntIntTuple2Tuple2List* tokens_230 = arg_186.t0;
    struct StringIntIntTuple2Tuple2List* errors_148 = arg_186.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_424;
    tuple_424.t0 = tokens_230;
    tuple_424.t1 = errors_148;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_679 = parseTuple_(baseLoc_39, tuple_424);
    struct AExpr_ body_14 = call_679.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_231 = call_679.t1;
    struct StringIntIntTuple2Tuple2List* errors_149 = call_679.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_258;
    if ((!(tokens_231))) goto next_988;
    if ((tokens_231->head.t0.tag != Colon_)) goto next_988;
    struct IntIntTuple2 loc_67 = tokens_231->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_232 = tokens_231->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_425;
    tuple_425.t0 = tokens_232;
    tuple_425.t1 = errors_149;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_680 = parseTy_(baseLoc_39, tuple_425);
    struct ATy_ ty_54 = call_680.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_233 = call_680.t1;
    struct StringIntIntTuple2Tuple2List* errors_150 = call_680.t2;
    struct AExpr_ATy_IntIntTuple2Tuple3 tuple_427;
    tuple_427.t0 = body_14;
    tuple_427.t1 = ty_54;
    tuple_427.t2 = loc_67;
    struct AExpr_ATy_IntIntTuple2Tuple3* payload_139 = (struct AExpr_ATy_IntIntTuple2Tuple3*)malloc(sizeof(struct AExpr_ATy_IntIntTuple2Tuple3));
    (*(((struct AExpr_ATy_IntIntTuple2Tuple3*)payload_139))) = tuple_427;
    struct AExpr_ variant_139 = (struct AExpr_){.tag = Anno_1, .Anno_1 = payload_139};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_426;
    tuple_426.t0 = variant_139;
    tuple_426.t1 = tokens_233;
    tuple_426.t2 = errors_150;
    match_258 = tuple_426;
    goto end_match_987;
next_988:;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_428;
    tuple_428.t0 = body_14;
    tuple_428.t1 = tokens_231;
    tuple_428.t2 = errors_149;
    match_258 = tuple_428;
    goto end_match_987;
next_989:;
end_match_987:;
    return match_258;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseExpr_(struct IntIntTuple2 baseLoc_40, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_187) {
    struct Token_IntIntTuple2Tuple2List* tokens_234 = arg_187.t0;
    struct StringIntIntTuple2Tuple2List* errors_151 = arg_187.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_429;
    tuple_429.t0 = tokens_234;
    tuple_429.t1 = errors_151;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_681 = parseAnno_(baseLoc_40, tuple_429);
    return call_681;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseStmt_(struct IntIntTuple2 baseLoc_41, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_188) {
    struct Token_IntIntTuple2Tuple2List* tokens_235 = arg_188.t0;
    struct StringIntIntTuple2Tuple2List* errors_152 = arg_188.t1;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_259;
    if ((!(tokens_235))) goto next_991;
    if ((tokens_235->head.t0.tag != Let_)) goto next_991;
    struct IntIntTuple2 letLoc_2 = tokens_235->head.t1;
    if ((!(tokens_235->tail))) goto next_991;
    if ((tokens_235->tail->head.t0.tag != Rec_)) goto next_991;
    struct Token_IntIntTuple2Tuple2List* tokens_236 = tokens_235->tail->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_430;
    tuple_430.t0 = tokens_236;
    tuple_430.t1 = errors_152;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_682 = parseLet_(letLoc_2, tuple_430);
    match_259 = call_682;
    goto end_match_990;
next_991:;
    if ((!(tokens_235))) goto next_992;
    if ((tokens_235->head.t0.tag != Let_)) goto next_992;
    struct IntIntTuple2 letLoc_3 = tokens_235->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_237 = tokens_235->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_431;
    tuple_431.t0 = tokens_237;
    tuple_431.t1 = errors_152;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_683 = parseLet_(letLoc_3, tuple_431);
    match_259 = call_683;
    goto end_match_990;
next_992:;
    if ((!(tokens_235))) goto next_993;
    if ((tokens_235->head.t0.tag != Type_)) goto next_993;
    struct IntIntTuple2 typeLoc_1 = tokens_235->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_238 = tokens_235->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_432;
    tuple_432.t0 = tokens_238;
    tuple_432.t1 = errors_152;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_684 = parseTyDecl_(typeLoc_1, tuple_432);
    match_259 = call_684;
    goto end_match_990;
next_993:;
    if ((!(tokens_235))) goto next_994;
    if ((tokens_235->head.t0.tag != Open_)) goto next_994;
    struct IntIntTuple2 typeLoc_2 = tokens_235->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_239 = tokens_235->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_433;
    tuple_433.t0 = tokens_239;
    tuple_433.t1 = errors_152;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_685 = parseOpen_(typeLoc_2, tuple_433);
    match_259 = call_685;
    goto end_match_990;
next_994:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_434;
    tuple_434.t0 = tokens_235;
    tuple_434.t1 = errors_152;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_686 = parseExpr_(baseLoc_41, tuple_434);
    match_259 = call_686;
    goto end_match_990;
next_995:;
end_match_990:;
    return match_259;
}

struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_52(struct IntIntTuple2 baseLoc_42, struct AExpr_List* acc_34, struct IntIntTuple2 alignLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_189) {
    struct Token_IntIntTuple2Tuple2List* tokens_241 = arg_189.t0;
    struct StringIntIntTuple2Tuple2List* errors_154 = arg_189.t1;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_260;
    if ((!(tokens_241))) goto next_997;
    if ((tokens_241->head.t0.tag != Semi_)) goto next_997;
    struct IntIntTuple2 semiLoc_ = tokens_241->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_242 = tokens_241->tail;
    int call_687 = locInside_(alignLoc_, semiLoc_);
    if ((!(call_687))) goto next_997;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_435;
    tuple_435.t0 = tokens_242;
    tuple_435.t1 = errors_154;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_688 = parseStmt_(baseLoc_42, tuple_435);
    struct AExpr_ expr_16 = call_688.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_243 = call_688.t1;
    struct StringIntIntTuple2Tuple2List* errors_155 = call_688.t2;
    struct AExpr_List* list_79 = (struct AExpr_List*)malloc(sizeof(struct AExpr_List));
    list_79->head = expr_16;
    list_79->tail = acc_34;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_436;
    tuple_436.t0 = tokens_243;
    tuple_436.t1 = errors_155;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_689 = go_52(baseLoc_42, list_79, alignLoc_, tuple_436);
    match_260 = call_689;
    goto end_match_996;
next_997:;
    int match_261;
    struct IntIntTuple2 call_690 = nextLoc_1(tokens_241);
    int call_691 = locIsSameColumn_(alignLoc_, call_690);
    if ((!(call_691))) goto next_1001;
    int call_692 = leadsExpr_1(tokens_241);
    match_261 = call_692;
    goto end_match_1000;
next_1001:;
    if (call_691) goto next_1002;
    match_261 = 0;
    goto end_match_1000;
next_1002:;
    exit(1);
end_match_1000:;
    if ((!(match_261))) goto next_998;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_437;
    tuple_437.t0 = tokens_241;
    tuple_437.t1 = errors_154;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_693 = parseStmt_(baseLoc_42, tuple_437);
    struct AExpr_ expr_17 = call_693.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_244 = call_693.t1;
    struct StringIntIntTuple2Tuple2List* errors_156 = call_693.t2;
    struct AExpr_List* list_80 = (struct AExpr_List*)malloc(sizeof(struct AExpr_List));
    list_80->head = expr_17;
    list_80->tail = acc_34;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_438;
    tuple_438.t0 = tokens_244;
    tuple_438.t1 = errors_156;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_694 = go_52(baseLoc_42, list_80, alignLoc_, tuple_438);
    match_260 = call_694;
    goto end_match_996;
next_998:;
    struct AExpr_List* call_695 = listRev_1(acc_34);
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_439;
    tuple_439.t0 = call_695;
    tuple_439.t1 = tokens_241;
    tuple_439.t2 = errors_154;
    match_260 = tuple_439;
    goto end_match_996;
next_999:;
end_match_996:;
    return match_260;
}

struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseStmts_(struct IntIntTuple2 baseLoc_42, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_190) {
    struct Token_IntIntTuple2Tuple2List* tokens_240 = arg_190.t0;
    struct StringIntIntTuple2Tuple2List* errors_153 = arg_190.t1;
    struct IntIntTuple2 call_696 = nextLoc_1(tokens_240);
    struct IntIntTuple2 alignLoc_1 = call_696;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_262;
    int call_697 = locInside_(baseLoc_42, alignLoc_1);
    if ((!(call_697))) goto next_1004;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_440;
    tuple_440.t0 = tokens_240;
    tuple_440.t1 = errors_153;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_698 = go_52(baseLoc_42, NULL, alignLoc_1, tuple_440);
    match_262 = call_698;
    goto end_match_1003;
next_1004:;
    if (call_697) goto next_1005;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_441;
    tuple_441.t0 = NULL;
    tuple_441.t1 = tokens_240;
    tuple_441.t2 = errors_153;
    match_262 = tuple_441;
    goto end_match_1003;
next_1005:;
    exit(1);
end_match_1003:;
    return match_262;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseSemi_(struct IntIntTuple2 baseLoc_43, struct IntIntTuple2 mainLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_191) {
    struct Token_IntIntTuple2Tuple2List* tokens_245 = arg_191.t0;
    struct StringIntIntTuple2Tuple2List* errors_157 = arg_191.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_442;
    tuple_442.t0 = tokens_245;
    tuple_442.t1 = errors_157;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_699 = parseStmts_(baseLoc_43, tuple_442);
    struct AExpr_List* items_8 = call_699.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_246 = call_699.t1;
    struct StringIntIntTuple2Tuple2List* errors_158 = call_699.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_263;
    if ((!((!(items_8))))) goto next_1007;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_443;
    tuple_443.t0 = tokens_246;
    tuple_443.t1 = errors_158;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_700 = parseExprError_1((struct String){.str = "Expected statements", .len = 19}, tuple_443);
    match_263 = call_700;
    goto end_match_1006;
next_1007:;
    if ((!(items_8))) goto next_1008;
    struct AExpr_ item_1 = items_8->head;
    if ((!((!(items_8->tail))))) goto next_1008;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_444;
    tuple_444.t0 = item_1;
    tuple_444.t1 = tokens_246;
    tuple_444.t2 = errors_158;
    match_263 = tuple_444;
    goto end_match_1006;
next_1008:;
    struct AExpr_ListIntIntTuple2Tuple2 tuple_446;
    tuple_446.t0 = items_8;
    tuple_446.t1 = mainLoc_;
    struct AExpr_ListIntIntTuple2Tuple2* payload_140 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_140))) = tuple_446;
    struct AExpr_ variant_140 = (struct AExpr_){.tag = Semi_1, .Semi_1 = payload_140};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_445;
    tuple_445.t0 = variant_140;
    tuple_445.t1 = tokens_246;
    tuple_445.t2 = errors_158;
    match_263 = tuple_445;
    goto end_match_1006;
next_1009:;
end_match_1006:;
    return match_263;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTopLevel_(struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_192) {
    struct Token_IntIntTuple2Tuple2List* tokens_247 = arg_192.t0;
    struct StringIntIntTuple2Tuple2List* errors_159 = arg_192.t1;
    struct IntIntTuple2 tuple_447;
    tuple_447.t0 = 0;
    tuple_447.t1 = 0;
    struct IntIntTuple2 topLoc_ = tuple_447;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_264;
    if ((!((!(tokens_247))))) goto next_1011;
    struct AExpr_ListIntIntTuple2Tuple2 tuple_449;
    tuple_449.t0 = NULL;
    tuple_449.t1 = topLoc_;
    struct AExpr_ListIntIntTuple2Tuple2* payload_141 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_141))) = tuple_449;
    struct AExpr_ variant_141 = (struct AExpr_){.tag = TupleLit_1, .TupleLit_1 = payload_141};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_448;
    tuple_448.t0 = variant_141;
    tuple_448.t1 = tokens_247;
    tuple_448.t2 = errors_159;
    match_264 = tuple_448;
    goto end_match_1010;
next_1011:;
    if ((!(tokens_247))) goto next_1012;
    if ((tokens_247->head.t0.tag != Module_)) goto next_1012;
    struct IntIntTuple2 moduleLoc_ = tokens_247->head.t1;
    if ((!(tokens_247->tail))) goto next_1012;
    if ((tokens_247->tail->head.t0.tag != Rec_)) goto next_1012;
    if ((!(tokens_247->tail->tail))) goto next_1012;
    if ((tokens_247->tail->tail->head.t0.tag != Ident_)) goto next_1012;
    if ((!(tokens_247->tail->tail->tail))) goto next_1012;
    if ((tokens_247->tail->tail->tail->head.t0.tag != Dot_)) goto next_1012;
    if ((!(tokens_247->tail->tail->tail->tail))) goto next_1012;
    if ((tokens_247->tail->tail->tail->tail->head.t0.tag != Ident_)) goto next_1012;
    struct Token_IntIntTuple2Tuple2List* tokens_248 = tokens_247->tail->tail->tail->tail->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_450;
    tuple_450.t0 = tokens_248;
    tuple_450.t1 = errors_159;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_701 = parseSemi_(moduleLoc_, moduleLoc_, tuple_450);
    match_264 = call_701;
    goto end_match_1010;
next_1012:;
    if ((!(tokens_247))) goto next_1013;
    if ((tokens_247->head.t0.tag != Module_)) goto next_1013;
    struct IntIntTuple2 moduleLoc_1 = tokens_247->head.t1;
    if ((!(tokens_247->tail))) goto next_1013;
    if ((tokens_247->tail->head.t0.tag != Rec_)) goto next_1013;
    if ((!(tokens_247->tail->tail))) goto next_1013;
    if ((tokens_247->tail->tail->head.t0.tag != Ident_)) goto next_1013;
    struct Token_IntIntTuple2Tuple2List* tokens_249 = tokens_247->tail->tail->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_451;
    tuple_451.t0 = tokens_249;
    tuple_451.t1 = errors_159;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_702 = parseSemi_(moduleLoc_1, moduleLoc_1, tuple_451);
    match_264 = call_702;
    goto end_match_1010;
next_1013:;
    if ((!(tokens_247))) goto next_1014;
    if ((tokens_247->head.t0.tag != Module_)) goto next_1014;
    struct IntIntTuple2 moduleLoc_2 = tokens_247->head.t1;
    if ((!(tokens_247->tail))) goto next_1014;
    if ((tokens_247->tail->head.t0.tag != Ident_)) goto next_1014;
    struct Token_IntIntTuple2Tuple2List* tokens_250 = tokens_247->tail->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_452;
    tuple_452.t0 = tokens_250;
    tuple_452.t1 = errors_159;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_703 = parseSemi_(moduleLoc_2, moduleLoc_2, tuple_452);
    match_264 = call_703;
    goto end_match_1010;
next_1014:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_453;
    tuple_453.t0 = tokens_247;
    tuple_453.t1 = errors_159;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_704 = parseSemi_(topLoc_, topLoc_, tuple_453);
    match_264 = call_704;
    goto end_match_1010;
next_1015:;
end_match_1010:;
    return match_264;
}

struct AExpr_StringIntIntTuple2Tuple2ListTuple2 {
    struct AExpr_ t0;
    struct StringIntIntTuple2Tuple2List* t1;
};

struct AExpr_StringIntIntTuple2Tuple2ListTuple2 parse_(struct Token_IntIntTuple2Tuple2List* tokens_251) {
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_454;
    tuple_454.t0 = tokens_251;
    tuple_454.t1 = NULL;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_705 = parseTopLevel_(tuple_454);
    struct AExpr_ expr_18 = call_705.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_252 = call_705.t1;
    struct StringIntIntTuple2Tuple2List* errors_160 = call_705.t2;
    struct StringIntIntTuple2Tuple2List* match_265;
    if ((!((!(tokens_252))))) goto next_1017;
    match_265 = errors_160;
    goto end_match_1016;
next_1017:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_455;
    tuple_455.t0 = tokens_252;
    tuple_455.t1 = errors_160;
    struct StringIntIntTuple2Tuple2List* call_706 = parseNewError_1((struct String){.str = "Expected eof", .len = 12}, tuple_455);
    match_265 = call_706;
    goto end_match_1016;
next_1018:;
end_match_1016:;
    struct StringIntIntTuple2Tuple2List* errors_161 = match_265;
    struct AExpr_StringIntIntTuple2Tuple2ListTuple2 tuple_456;
    tuple_456.t0 = expr_18;
    tuple_456.t1 = errors_161;
    return tuple_456;
}

struct HPrim_ opToPrim_(struct Op_ op_2) {
    struct HPrim_ match_266;
    if ((op_2.tag != Add_1)) goto next_1020;
    match_266 = (struct HPrim_){.tag = Add_3};
    goto end_match_1019;
next_1020:;
    if ((op_2.tag != Sub_)) goto next_1021;
    match_266 = (struct HPrim_){.tag = Sub_1};
    goto end_match_1019;
next_1021:;
    if ((op_2.tag != Mul_1)) goto next_1022;
    match_266 = (struct HPrim_){.tag = Mul_2};
    goto end_match_1019;
next_1022:;
    if ((op_2.tag != Div_)) goto next_1023;
    match_266 = (struct HPrim_){.tag = Div_1};
    goto end_match_1019;
next_1023:;
    if ((op_2.tag != Mod_)) goto next_1024;
    match_266 = (struct HPrim_){.tag = Mod_1};
    goto end_match_1019;
next_1024:;
    if ((op_2.tag != Eq_1)) goto next_1025;
    match_266 = (struct HPrim_){.tag = Eq_3};
    goto end_match_1019;
next_1025:;
    if ((op_2.tag != Lt_1)) goto next_1026;
    match_266 = (struct HPrim_){.tag = Lt_2};
    goto end_match_1019;
next_1026:;
    if ((op_2.tag != Cons_1)) goto next_1028;
    match_266 = (struct HPrim_){.tag = Cons_4};
    goto end_match_1019;
next_1028:;
    if ((op_2.tag != Ne_)) goto next_1029;
    goto match_body_1027;
next_1029:;
    if ((op_2.tag != Le_)) goto next_1030;
    goto match_body_1027;
next_1030:;
    if ((op_2.tag != Gt_1)) goto next_1031;
    goto match_body_1027;
next_1031:;
    if ((op_2.tag != Ge_)) goto next_1032;
    goto match_body_1027;
next_1032:;
    if ((op_2.tag != And_1)) goto next_1033;
    goto match_body_1027;
next_1033:;
    if ((op_2.tag != Or_1)) goto next_1034;
    goto match_body_1027;
next_1034:;
    if ((op_2.tag != App_)) goto next_1035;
    goto match_body_1027;
next_1035:;
    if ((op_2.tag != Pipe_2)) goto next_1036;
    goto match_body_1027;
match_body_1027:;
    struct Op_HPrim_Fun1 call_707 = failwithf_3((struct String){.str = "NEVER: %A", .len = 9});
    struct HPrim_ app_67 = call_707.fun(call_707.env, op_2);
    match_266 = app_67;
    goto end_match_1019;
next_1036:;
end_match_1019:;
    return match_266;
}

struct APat_ go_53(struct IntIntTuple2 loc_68, struct APat_List* pats_5) {
    struct APat_ match_267;
    if ((!((!(pats_5))))) goto next_1038;
    struct APat_ListIntIntTuple2Tuple2 tuple_457;
    tuple_457.t0 = NULL;
    tuple_457.t1 = loc_68;
    struct APat_ListIntIntTuple2Tuple2* payload_142 = (struct APat_ListIntIntTuple2Tuple2*)malloc(sizeof(struct APat_ListIntIntTuple2Tuple2));
    (*(((struct APat_ListIntIntTuple2Tuple2*)payload_142))) = tuple_457;
    struct APat_ variant_142 = (struct APat_){.tag = ListLit_, .ListLit_ = payload_142};
    match_267 = variant_142;
    goto end_match_1037;
next_1038:;
    if ((!(pats_5))) goto next_1039;
    struct APat_ head_3 = pats_5->head;
    struct APat_List* tail_3 = pats_5->tail;
    struct APat_ call_708 = go_53(loc_68, tail_3);
    struct APat_ tail_4 = call_708;
    struct APat_APat_IntIntTuple2Tuple3 tuple_458;
    tuple_458.t0 = head_3;
    tuple_458.t1 = tail_4;
    tuple_458.t2 = loc_68;
    struct APat_APat_IntIntTuple2Tuple3* payload_143 = (struct APat_APat_IntIntTuple2Tuple3*)malloc(sizeof(struct APat_APat_IntIntTuple2Tuple3));
    (*(((struct APat_APat_IntIntTuple2Tuple3*)payload_143))) = tuple_458;
    struct APat_ variant_143 = (struct APat_){.tag = Cons_2, .Cons_2 = payload_143};
    match_267 = variant_143;
    goto end_match_1037;
next_1039:;
    exit(1);
end_match_1037:;
    return match_267;
}

struct APat_ desugarListLitPat_(struct APat_List* pats_4, struct IntIntTuple2 loc_68) {
    int call_709 = listIsEmpty_2(pats_4);
    milone_assert((!(call_709)), 64, 2);
    int call_710 = 0;
    struct APat_ call_711 = go_53(loc_68, pats_4);
    return call_711;
}

struct AExpr_ go_54(struct IntIntTuple2 loc_69, struct AExpr_List* items_10) {
    struct AExpr_ match_268;
    if ((!((!(items_10))))) goto next_1041;
    struct AExpr_ListIntIntTuple2Tuple2 tuple_459;
    tuple_459.t0 = NULL;
    tuple_459.t1 = loc_69;
    struct AExpr_ListIntIntTuple2Tuple2* payload_144 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_144))) = tuple_459;
    struct AExpr_ variant_144 = (struct AExpr_){.tag = ListLit_1, .ListLit_1 = payload_144};
    match_268 = variant_144;
    goto end_match_1040;
next_1041:;
    if ((!(items_10))) goto next_1042;
    struct AExpr_ head_4 = items_10->head;
    struct AExpr_List* tail_5 = items_10->tail;
    struct AExpr_ call_712 = go_54(loc_69, tail_5);
    struct AExpr_ tail_6 = call_712;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_460;
    tuple_460.t0 = (struct Op_){.tag = Cons_1};
    tuple_460.t1 = head_4;
    tuple_460.t2 = tail_6;
    tuple_460.t3 = loc_69;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_145 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_145))) = tuple_460;
    struct AExpr_ variant_145 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_145};
    match_268 = variant_145;
    goto end_match_1040;
next_1042:;
    exit(1);
end_match_1040:;
    return match_268;
}

struct AExpr_ desugarListLitExpr_(struct AExpr_List* items_9, struct IntIntTuple2 loc_69) {
    int call_713 = listIsEmpty_1(items_9);
    milone_assert((!(call_713)), 79, 2);
    int call_714 = 0;
    struct AExpr_ call_715 = go_54(loc_69, items_9);
    return call_715;
}

struct AExpr_ desugarIf_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct AExpr_ cond_2, struct AExpr_ body_15, struct AExpr_ alt_2, struct IntIntTuple2 loc_70) {
    struct AExpr_ match_269;
    if ((alt_2.tag != Missing_2)) goto next_1044;
    struct AExpr_ call_716 = axUnit_(loc_70);
    match_269 = call_716;
    goto end_match_1043;
next_1044:;
    match_269 = alt_2;
    goto end_match_1043;
next_1045:;
end_match_1043:;
    struct AExpr_ alt_3 = match_269;
    struct APat_ call_717 = apTrue_(litTrue_, loc_70);
    struct AExpr_ call_718 = axTrue_(litTrue_, loc_70);
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4 tuple_461;
    tuple_461.t0 = call_717;
    tuple_461.t1 = call_718;
    tuple_461.t2 = body_15;
    tuple_461.t3 = loc_70;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4* payload_146 = (struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct APat_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)payload_146))) = tuple_461;
    struct AArm_ variant_146 = (struct AArm_){.tag = AArm_, .AArm_ = payload_146};
    struct APat_ call_719 = apFalse_(litFalse_, loc_70);
    struct AExpr_ call_720 = axTrue_(litTrue_, loc_70);
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4 tuple_462;
    tuple_462.t0 = call_719;
    tuple_462.t1 = call_720;
    tuple_462.t2 = alt_3;
    tuple_462.t3 = loc_70;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4* payload_147 = (struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct APat_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)payload_147))) = tuple_462;
    struct AArm_ variant_147 = (struct AArm_){.tag = AArm_, .AArm_ = payload_147};
    struct AArm_List* list_82 = (struct AArm_List*)malloc(sizeof(struct AArm_List));
    list_82->head = variant_147;
    list_82->tail = NULL;
    struct AArm_List* list_81 = (struct AArm_List*)malloc(sizeof(struct AArm_List));
    list_81->head = variant_146;
    list_81->tail = list_82;
    struct AArm_List* arms_4 = list_81;
    struct AExpr_AArm_ListIntIntTuple2Tuple3 tuple_463;
    tuple_463.t0 = cond_2;
    tuple_463.t1 = arms_4;
    tuple_463.t2 = loc_70;
    struct AExpr_AArm_ListIntIntTuple2Tuple3* payload_148 = (struct AExpr_AArm_ListIntIntTuple2Tuple3*)malloc(sizeof(struct AExpr_AArm_ListIntIntTuple2Tuple3));
    (*(((struct AExpr_AArm_ListIntIntTuple2Tuple3*)payload_148))) = tuple_463;
    struct AExpr_ variant_148 = (struct AExpr_){.tag = Match_1, .Match_1 = payload_148};
    return variant_148;
}

struct AExpr_ desugarFun_(struct APat_List* pats_6, struct AExpr_ body_16, struct IntIntTuple2 loc_71) {
    struct String ident_26 = (struct String){.str = "fun", .len = 3};
    struct StringAPat_ListIntIntTuple2Tuple3 tuple_464;
    tuple_464.t0 = ident_26;
    tuple_464.t1 = pats_6;
    tuple_464.t2 = loc_71;
    struct StringAPat_ListIntIntTuple2Tuple3* payload_149 = (struct StringAPat_ListIntIntTuple2Tuple3*)malloc(sizeof(struct StringAPat_ListIntIntTuple2Tuple3));
    (*(((struct StringAPat_ListIntIntTuple2Tuple3*)payload_149))) = tuple_464;
    struct APat_ variant_149 = (struct APat_){.tag = Fun_2, .Fun_2 = payload_149};
    struct APat_ pat_23 = variant_149;
    struct StringIntIntTuple2Tuple2 tuple_465;
    tuple_465.t0 = ident_26;
    tuple_465.t1 = loc_71;
    struct StringIntIntTuple2Tuple2* payload_150 = (struct StringIntIntTuple2Tuple2*)malloc(sizeof(struct StringIntIntTuple2Tuple2));
    (*(((struct StringIntIntTuple2Tuple2*)payload_150))) = tuple_465;
    struct AExpr_ variant_150 = (struct AExpr_){.tag = Ident_2, .Ident_2 = payload_150};
    struct AExpr_ next_12 = variant_150;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4 tuple_466;
    tuple_466.t0 = pat_23;
    tuple_466.t1 = body_16;
    tuple_466.t2 = next_12;
    tuple_466.t3 = loc_71;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4* payload_151 = (struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct APat_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)payload_151))) = tuple_466;
    struct AExpr_ variant_151 = (struct AExpr_){.tag = Let_1, .Let_1 = payload_151};
    return variant_151;
}

struct AExpr_ desugarUniNeg_(struct AExpr_ arg_4, struct IntIntTuple2 loc_72) {
    int* payload_152 = (int*)malloc(sizeof(int));
    (*(((int*)payload_152))) = 0;
    struct Lit_ variant_152 = (struct Lit_){.tag = Int_, .Int_ = payload_152};
    struct Lit_IntIntTuple2Tuple2 tuple_467;
    tuple_467.t0 = variant_152;
    tuple_467.t1 = loc_72;
    struct Lit_IntIntTuple2Tuple2* payload_153 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_153))) = tuple_467;
    struct AExpr_ variant_153 = (struct AExpr_){.tag = Lit_1, .Lit_1 = payload_153};
    struct AExpr_ zero_ = variant_153;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_468;
    tuple_468.t0 = (struct Op_){.tag = Sub_};
    tuple_468.t1 = zero_;
    tuple_468.t2 = arg_4;
    tuple_468.t3 = loc_72;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_154 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_154))) = tuple_468;
    struct AExpr_ variant_154 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_154};
    return variant_154;
}

struct AExpr_ desugarBinNe_(struct Lit_ litFalse_, struct AExpr_ l_19, struct AExpr_ r_33, struct IntIntTuple2 loc_73) {
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_469;
    tuple_469.t0 = (struct Op_){.tag = Eq_1};
    tuple_469.t1 = l_19;
    tuple_469.t2 = r_33;
    tuple_469.t3 = loc_73;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_155 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_155))) = tuple_469;
    struct AExpr_ variant_155 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_155};
    struct AExpr_ eqExpr_ = variant_155;
    struct AExpr_ call_721 = axNot_(litFalse_, eqExpr_, loc_73);
    return call_721;
}

struct AExpr_ desugarBinLe_(struct Lit_ litFalse_, struct AExpr_ l_20, struct AExpr_ r_34, struct IntIntTuple2 loc_74) {
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_470;
    tuple_470.t0 = (struct Op_){.tag = Lt_1};
    tuple_470.t1 = r_34;
    tuple_470.t2 = l_20;
    tuple_470.t3 = loc_74;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_156 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_156))) = tuple_470;
    struct AExpr_ variant_156 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_156};
    struct AExpr_ ltExpr_ = variant_156;
    struct AExpr_ call_722 = axNot_(litFalse_, ltExpr_, loc_74);
    return call_722;
}

struct AExpr_ desugarBinGt_(struct AExpr_ l_21, struct AExpr_ r_35, struct IntIntTuple2 loc_75) {
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_471;
    tuple_471.t0 = (struct Op_){.tag = Lt_1};
    tuple_471.t1 = r_35;
    tuple_471.t2 = l_21;
    tuple_471.t3 = loc_75;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_157 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_157))) = tuple_471;
    struct AExpr_ variant_157 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_157};
    return variant_157;
}

struct AExpr_ desugarBinGe_(struct Lit_ litFalse_, struct AExpr_ l_22, struct AExpr_ r_36, struct IntIntTuple2 loc_76) {
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_472;
    tuple_472.t0 = (struct Op_){.tag = Lt_1};
    tuple_472.t1 = l_22;
    tuple_472.t2 = r_36;
    tuple_472.t3 = loc_76;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_158 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_158))) = tuple_472;
    struct AExpr_ variant_158 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_158};
    struct AExpr_ ltExpr_1 = variant_158;
    struct AExpr_ call_723 = axNot_(litFalse_, ltExpr_1, loc_76);
    return call_723;
}

struct AExpr_ desugarBinAnd_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct AExpr_ l_23, struct AExpr_ r_37, struct IntIntTuple2 loc_77) {
    struct AExpr_ call_724 = axFalse_(litFalse_, loc_77);
    struct AExpr_ call_725 = desugarIf_(litFalse_, litTrue_, l_23, r_37, call_724, loc_77);
    return call_725;
}

struct AExpr_ desugarBinOr_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct AExpr_ l_24, struct AExpr_ r_38, struct IntIntTuple2 loc_78) {
    struct AExpr_ call_726 = axTrue_(litTrue_, loc_78);
    struct AExpr_ call_727 = desugarIf_(litFalse_, litTrue_, l_24, call_726, r_38, loc_78);
    return call_727;
}

struct AExpr_ desugarBinPipe_(struct AExpr_ l_25, struct AExpr_ r_39, struct IntIntTuple2 loc_79) {
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_473;
    tuple_473.t0 = (struct Op_){.tag = App_};
    tuple_473.t1 = r_39;
    tuple_473.t2 = l_25;
    tuple_473.t3 = loc_79;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_159 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_159))) = tuple_473;
    struct AExpr_ variant_159 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_159};
    return variant_159;
}

struct BoolAExpr_Tuple2 {
    int t0;
    struct AExpr_ t1;
};

struct BoolAExpr_Tuple2 tryDesugarIndexRange_(struct AExpr_ expr_19, struct IntIntTuple2 loc_80) {
    struct BoolAExpr_Tuple2 match_270;
    if ((expr_19.tag != Index_)) goto next_1047;
    struct AExpr_ s_8 = (*(expr_19.Index_)).t0;
    if (((*(expr_19.Index_)).t1.tag != Range_)) goto next_1047;
    if ((!((*((*(expr_19.Index_)).t1.Range_)).t0))) goto next_1047;
    struct AExpr_ l_26 = (*((*(expr_19.Index_)).t1.Range_)).t0->head;
    if ((!((*((*(expr_19.Index_)).t1.Range_)).t0->tail))) goto next_1047;
    struct AExpr_ r_40 = (*((*(expr_19.Index_)).t1.Range_)).t0->tail->head;
    if ((!((!((*((*(expr_19.Index_)).t1.Range_)).t0->tail->tail))))) goto next_1047;
    struct StringIntIntTuple2Tuple2 tuple_475;
    tuple_475.t0 = (struct String){.str = "String", .len = 6};
    tuple_475.t1 = loc_80;
    struct StringIntIntTuple2Tuple2* payload_160 = (struct StringIntIntTuple2Tuple2*)malloc(sizeof(struct StringIntIntTuple2Tuple2));
    (*(((struct StringIntIntTuple2Tuple2*)payload_160))) = tuple_475;
    struct AExpr_ variant_160 = (struct AExpr_){.tag = Ident_2, .Ident_2 = payload_160};
    struct AExpr_StringIntIntTuple2Tuple3 tuple_474;
    tuple_474.t0 = variant_160;
    tuple_474.t1 = (struct String){.str = "getSlice", .len = 8};
    tuple_474.t2 = loc_80;
    struct AExpr_StringIntIntTuple2Tuple3* payload_161 = (struct AExpr_StringIntIntTuple2Tuple3*)malloc(sizeof(struct AExpr_StringIntIntTuple2Tuple3));
    (*(((struct AExpr_StringIntIntTuple2Tuple3*)payload_161))) = tuple_474;
    struct AExpr_ variant_161 = (struct AExpr_){.tag = Nav_1, .Nav_1 = payload_161};
    struct AExpr_ getSlice_ = variant_161;
    struct AExpr_ call_728 = axApp3_(getSlice_, l_26, r_40, s_8, loc_80);
    struct BoolAExpr_Tuple2 tuple_476;
    tuple_476.t0 = 1;
    tuple_476.t1 = call_728;
    match_270 = tuple_476;
    goto end_match_1046;
next_1047:;
    struct BoolAExpr_Tuple2 tuple_477;
    tuple_477.t0 = 0;
    tuple_477.t1 = expr_19;
    match_270 = tuple_477;
    goto end_match_1046;
next_1048:;
end_match_1046:;
    return match_270;
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

struct ALet_ desugarLet_(struct APat_ pat_24, struct AExpr_ body_17, struct AExpr_ next_13, struct IntIntTuple2 loc_81) {
    struct ALet_ match_271;
    if ((pat_24.tag != Anno_)) goto next_1050;
    struct APat_ pat_25 = (*(pat_24.Anno_)).t0;
    struct ATy_ annoTy_ = (*(pat_24.Anno_)).t1;
    struct IntIntTuple2 annoLoc_ = (*(pat_24.Anno_)).t2;
    struct AExpr_ATy_IntIntTuple2Tuple3 tuple_478;
    tuple_478.t0 = body_17;
    tuple_478.t1 = annoTy_;
    tuple_478.t2 = annoLoc_;
    struct AExpr_ATy_IntIntTuple2Tuple3* payload_162 = (struct AExpr_ATy_IntIntTuple2Tuple3*)malloc(sizeof(struct AExpr_ATy_IntIntTuple2Tuple3));
    (*(((struct AExpr_ATy_IntIntTuple2Tuple3*)payload_162))) = tuple_478;
    struct AExpr_ variant_162 = (struct AExpr_){.tag = Anno_1, .Anno_1 = payload_162};
    struct AExpr_ body_18 = variant_162;
    struct ALet_ call_729 = desugarLet_(pat_25, body_18, next_13, loc_81);
    match_271 = call_729;
    goto end_match_1049;
next_1050:;
    if ((pat_24.tag != Fun_2)) goto next_1051;
    struct String ident_27 = (*(pat_24.Fun_2)).t0;
    struct APat_List* args_8 = (*(pat_24.Fun_2)).t1;
    struct StringAPat_ListAExpr_AExpr_IntIntTuple2Tuple5 tuple_479;
    tuple_479.t0 = ident_27;
    tuple_479.t1 = args_8;
    tuple_479.t2 = body_17;
    tuple_479.t3 = next_13;
    tuple_479.t4 = loc_81;
    struct StringAPat_ListAExpr_AExpr_IntIntTuple2Tuple5* payload_163 = (struct StringAPat_ListAExpr_AExpr_IntIntTuple2Tuple5*)malloc(sizeof(struct StringAPat_ListAExpr_AExpr_IntIntTuple2Tuple5));
    (*(((struct StringAPat_ListAExpr_AExpr_IntIntTuple2Tuple5*)payload_163))) = tuple_479;
    struct ALet_ variant_163 = (struct ALet_){.tag = LetFun_, .LetFun_ = payload_163};
    match_271 = variant_163;
    goto end_match_1049;
next_1051:;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4 tuple_480;
    tuple_480.t0 = pat_24;
    tuple_480.t1 = body_17;
    tuple_480.t2 = next_13;
    tuple_480.t3 = loc_81;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4* payload_164 = (struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct APat_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)payload_164))) = tuple_480;
    struct ALet_ variant_164 = (struct ALet_){.tag = LetVal_, .LetVal_ = payload_164};
    match_271 = variant_164;
    goto end_match_1049;
next_1052:;
end_match_1049:;
    return match_271;
}

struct Ty_NameCtx_Tuple2 fun_16(void* env_10, struct ATy_NameCtx_Tuple2 arg_37) {
    struct Ty_NameCtx_Tuple2 call_730 = onTy_(arg_37);
    return call_730;
}

struct Ty_NameCtx_Tuple2 fun_17(void* env_11, struct ATy_NameCtx_Tuple2 arg_38) {
    struct Ty_NameCtx_Tuple2 call_731 = onTy_(arg_38);
    return call_731;
}

struct Ty_NameCtx_Tuple2 onTy_(struct ATy_NameCtx_Tuple2 arg_193) {
    struct ATy_ ty_55 = arg_193.t0;
    struct NameCtx_ nameCtx_3 = arg_193.t1;
    struct Ty_NameCtx_Tuple2 match_272;
    if ((ty_55.tag != Missing_)) goto next_1054;
    struct IntIntTuple2 loc_82 = (*(ty_55.Missing_));
    struct IntIntTuple2* payload_165 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_165))) = loc_82;
    struct Ty_ variant_165 = (struct Ty_){.tag = Error_1, .Error_1 = payload_165};
    struct Ty_NameCtx_Tuple2 tuple_481;
    tuple_481.t0 = variant_165;
    tuple_481.t1 = nameCtx_3;
    match_272 = tuple_481;
    goto end_match_1053;
next_1054:;
    if ((ty_55.tag != App_1)) goto next_1055;
    struct String ident_28 = (*(ty_55.App_1)).t0;
    struct ATy_List* argTys_2 = (*(ty_55.App_1)).t1;
    struct IntNameCtx_Tuple2 call_732 = nameCtxAdd_(ident_28, nameCtx_3);
    int tySerial_1 = call_732.t0;
    struct NameCtx_ nameCtx_4 = call_732.t1;
    void* box_7 = (void*)malloc(sizeof(int));
    (*(((int*)box_7))) = 0;
    void* env_46 = box_7;
    struct ATy_NameCtx_Tuple2Ty_NameCtx_Tuple2Fun1 fun_52 = (struct ATy_NameCtx_Tuple2Ty_NameCtx_Tuple2Fun1){.fun = fun_16, .env = env_46};
    struct ATy_ListNameCtx_Tuple2 tuple_482;
    tuple_482.t0 = argTys_2;
    tuple_482.t1 = nameCtx_4;
    struct Ty_ListNameCtx_Tuple2 call_733 = stMap_5(fun_52, tuple_482);
    struct Ty_List* argTys_3 = call_733.t0;
    struct NameCtx_ nameCtx_5 = call_733.t1;
    struct Ty_ call_734 = tyRef_(tySerial_1, argTys_3);
    struct Ty_NameCtx_Tuple2 tuple_483;
    tuple_483.t0 = call_734;
    tuple_483.t1 = nameCtx_5;
    match_272 = tuple_483;
    goto end_match_1053;
next_1055:;
    if ((ty_55.tag != Suffix_)) goto next_1056;
    struct ATy_ lTy_3 = (*(ty_55.Suffix_)).t0;
    struct String ident_29 = (*(ty_55.Suffix_)).t1;
    struct ATy_NameCtx_Tuple2 tuple_484;
    tuple_484.t0 = lTy_3;
    tuple_484.t1 = nameCtx_3;
    struct Ty_NameCtx_Tuple2 call_735 = onTy_(tuple_484);
    struct Ty_ lTy_4 = call_735.t0;
    struct NameCtx_ nameCtx_6 = call_735.t1;
    struct IntNameCtx_Tuple2 call_736 = nameCtxAdd_(ident_29, nameCtx_6);
    int tySerial_2 = call_736.t0;
    struct NameCtx_ nameCtx_7 = call_736.t1;
    struct Ty_List* list_83 = (struct Ty_List*)malloc(sizeof(struct Ty_List));
    list_83->head = lTy_4;
    list_83->tail = NULL;
    struct Ty_ call_737 = tyRef_(tySerial_2, list_83);
    struct Ty_NameCtx_Tuple2 tuple_485;
    tuple_485.t0 = call_737;
    tuple_485.t1 = nameCtx_7;
    match_272 = tuple_485;
    goto end_match_1053;
next_1056:;
    if ((ty_55.tag != Tuple_)) goto next_1057;
    struct ATy_List* itemTys_2 = (*(ty_55.Tuple_)).t0;
    void* box_8 = (void*)malloc(sizeof(int));
    (*(((int*)box_8))) = 0;
    void* env_47 = box_8;
    struct ATy_NameCtx_Tuple2Ty_NameCtx_Tuple2Fun1 fun_53 = (struct ATy_NameCtx_Tuple2Ty_NameCtx_Tuple2Fun1){.fun = fun_17, .env = env_47};
    struct ATy_ListNameCtx_Tuple2 tuple_486;
    tuple_486.t0 = itemTys_2;
    tuple_486.t1 = nameCtx_3;
    struct Ty_ListNameCtx_Tuple2 call_738 = stMap_5(fun_53, tuple_486);
    struct Ty_List* itemTys_3 = call_738.t0;
    struct NameCtx_ nameCtx_8 = call_738.t1;
    struct Ty_ call_739 = tyTuple_(itemTys_3);
    struct Ty_NameCtx_Tuple2 tuple_487;
    tuple_487.t0 = call_739;
    tuple_487.t1 = nameCtx_8;
    match_272 = tuple_487;
    goto end_match_1053;
next_1057:;
    if ((ty_55.tag != Fun_1)) goto next_1058;
    struct ATy_ sTy_2 = (*(ty_55.Fun_1)).t0;
    struct ATy_ tTy_2 = (*(ty_55.Fun_1)).t1;
    struct ATy_NameCtx_Tuple2 tuple_488;
    tuple_488.t0 = sTy_2;
    tuple_488.t1 = nameCtx_3;
    struct Ty_NameCtx_Tuple2 call_740 = onTy_(tuple_488);
    struct Ty_ sTy_3 = call_740.t0;
    struct NameCtx_ nameCtx_9 = call_740.t1;
    struct ATy_NameCtx_Tuple2 tuple_489;
    tuple_489.t0 = tTy_2;
    tuple_489.t1 = nameCtx_9;
    struct Ty_NameCtx_Tuple2 call_741 = onTy_(tuple_489);
    struct Ty_ tTy_3 = call_741.t0;
    struct NameCtx_ nameCtx_10 = call_741.t1;
    struct Ty_ call_742 = tyFun_(sTy_3, tTy_3);
    struct Ty_NameCtx_Tuple2 tuple_490;
    tuple_490.t0 = call_742;
    tuple_490.t1 = nameCtx_10;
    match_272 = tuple_490;
    goto end_match_1053;
next_1058:;
    exit(1);
end_match_1053:;
    return match_272;
}

struct Ty_Tuple1 {
    struct Ty_ t0;
};

struct HPat_NameCtx_Tuple2 fun_18(void* env_12, struct APat_NameCtx_Tuple2 arg_39) {
    struct Ty_ arg_40 = (*(((struct Ty_Tuple1*)env_12))).t0;
    struct HPat_NameCtx_Tuple2 call_743 = onPat_(arg_40, arg_39);
    return call_743;
}

struct HPat_NameCtx_Tuple2 fun_19(void* env_13, struct APat_NameCtx_Tuple2 arg_41) {
    struct Ty_ arg_42 = (*(((struct Ty_Tuple1*)env_13))).t0;
    struct HPat_NameCtx_Tuple2 call_744 = onPat_(arg_42, arg_41);
    return call_744;
}

struct HPat_NameCtx_Tuple2 onPat_(struct Ty_ noTy_, struct APat_NameCtx_Tuple2 arg_194) {
    struct APat_ pat_26 = arg_194.t0;
    struct NameCtx_ nameCtx_11 = arg_194.t1;
    struct HPat_NameCtx_Tuple2 match_273;
    if ((pat_26.tag != Missing_1)) goto next_1060;
    int loc_83 = (*(pat_26.Missing_1)).t1;
    struct IntHPat_NameCtx_Tuple2Fun1 call_745 = failwithf_2((struct String){.str = "Missing pattern %A", .len = 18});
    struct HPat_NameCtx_Tuple2 app_68 = call_745.fun(call_745.env, loc_83);
    match_273 = app_68;
    goto end_match_1059;
next_1060:;
    if ((pat_26.tag != Lit_)) goto next_1061;
    struct Lit_ lit_9 = (*(pat_26.Lit_)).t0;
    struct IntIntTuple2 loc_84 = (*(pat_26.Lit_)).t1;
    struct Lit_IntIntTuple2Tuple2 tuple_492;
    tuple_492.t0 = lit_9;
    tuple_492.t1 = loc_84;
    struct Lit_IntIntTuple2Tuple2* payload_166 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_166))) = tuple_492;
    struct HPat_ variant_166 = (struct HPat_){.tag = Lit_2, .Lit_2 = payload_166};
    struct HPat_NameCtx_Tuple2 tuple_491;
    tuple_491.t0 = variant_166;
    tuple_491.t1 = nameCtx_11;
    match_273 = tuple_491;
    goto end_match_1059;
next_1061:;
    if ((pat_26.tag != Ident_1)) goto next_1062;
    struct String ident_30 = (*(pat_26.Ident_1)).t0;
    struct IntIntTuple2 loc_85 = (*(pat_26.Ident_1)).t1;
    struct IntNameCtx_Tuple2 call_746 = nameCtxAdd_(ident_30, nameCtx_11);
    int serial_11 = call_746.t0;
    struct NameCtx_ nameCtx_12 = call_746.t1;
    struct IntTy_IntIntTuple2Tuple3 tuple_494;
    tuple_494.t0 = serial_11;
    tuple_494.t1 = noTy_;
    tuple_494.t2 = loc_85;
    struct IntTy_IntIntTuple2Tuple3* payload_167 = (struct IntTy_IntIntTuple2Tuple3*)malloc(sizeof(struct IntTy_IntIntTuple2Tuple3));
    (*(((struct IntTy_IntIntTuple2Tuple3*)payload_167))) = tuple_494;
    struct HPat_ variant_167 = (struct HPat_){.tag = Ref_1, .Ref_1 = payload_167};
    struct HPat_NameCtx_Tuple2 tuple_493;
    tuple_493.t0 = variant_167;
    tuple_493.t1 = nameCtx_12;
    match_273 = tuple_493;
    goto end_match_1059;
next_1062:;
    if ((pat_26.tag != ListLit_)) goto next_1063;
    if ((!((!((*(pat_26.ListLit_)).t0))))) goto next_1063;
    struct IntIntTuple2 loc_86 = (*(pat_26.ListLit_)).t1;
    struct HPat_ call_747 = patNil_(noTy_, loc_86);
    struct HPat_NameCtx_Tuple2 tuple_495;
    tuple_495.t0 = call_747;
    tuple_495.t1 = nameCtx_11;
    match_273 = tuple_495;
    goto end_match_1059;
next_1063:;
    if ((pat_26.tag != ListLit_)) goto next_1064;
    struct APat_List* pats_7 = (*(pat_26.ListLit_)).t0;
    struct IntIntTuple2 loc_87 = (*(pat_26.ListLit_)).t1;
    struct APat_ call_748 = desugarListLitPat_(pats_7, loc_87);
    struct APat_ pat_27 = call_748;
    struct APat_NameCtx_Tuple2 tuple_496;
    tuple_496.t0 = pat_27;
    tuple_496.t1 = nameCtx_11;
    struct HPat_NameCtx_Tuple2 call_749 = onPat_(noTy_, tuple_496);
    match_273 = call_749;
    goto end_match_1059;
next_1064:;
    if ((pat_26.tag != Nav_)) goto next_1065;
    struct APat_ l_27 = (*(pat_26.Nav_)).t0;
    struct String r_41 = (*(pat_26.Nav_)).t1;
    struct IntIntTuple2 loc_88 = (*(pat_26.Nav_)).t2;
    struct APat_NameCtx_Tuple2 tuple_497;
    tuple_497.t0 = l_27;
    tuple_497.t1 = nameCtx_11;
    struct HPat_NameCtx_Tuple2 call_750 = onPat_(noTy_, tuple_497);
    struct HPat_ l_28 = call_750.t0;
    struct NameCtx_ nameCtx_13 = call_750.t1;
    struct HPat_StringTy_IntIntTuple2Tuple4 tuple_499;
    tuple_499.t0 = l_28;
    tuple_499.t1 = r_41;
    tuple_499.t2 = noTy_;
    tuple_499.t3 = loc_88;
    struct HPat_StringTy_IntIntTuple2Tuple4* payload_168 = (struct HPat_StringTy_IntIntTuple2Tuple4*)malloc(sizeof(struct HPat_StringTy_IntIntTuple2Tuple4));
    (*(((struct HPat_StringTy_IntIntTuple2Tuple4*)payload_168))) = tuple_499;
    struct HPat_ variant_168 = (struct HPat_){.tag = Nav_2, .Nav_2 = payload_168};
    struct HPat_NameCtx_Tuple2 tuple_498;
    tuple_498.t0 = variant_168;
    tuple_498.t1 = nameCtx_13;
    match_273 = tuple_498;
    goto end_match_1059;
next_1065:;
    if ((pat_26.tag != Call_)) goto next_1066;
    struct APat_ calleePat_1 = (*(pat_26.Call_)).t0;
    struct APat_List* argPats_1 = (*(pat_26.Call_)).t1;
    struct IntIntTuple2 loc_89 = (*(pat_26.Call_)).t2;
    struct APat_NameCtx_Tuple2 tuple_500;
    tuple_500.t0 = calleePat_1;
    tuple_500.t1 = nameCtx_11;
    struct HPat_NameCtx_Tuple2 call_751 = onPat_(noTy_, tuple_500);
    struct HPat_ calleePat_2 = call_751.t0;
    struct NameCtx_ nameCtx_14 = call_751.t1;
    struct Ty_Tuple1 tuple_501;
    tuple_501.t0 = noTy_;
    void* box_9 = (void*)malloc(sizeof(struct Ty_Tuple1));
    (*(((struct Ty_Tuple1*)box_9))) = tuple_501;
    void* env_48 = box_9;
    struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1 fun_54 = (struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1){.fun = fun_18, .env = env_48};
    struct APat_ListNameCtx_Tuple2 tuple_502;
    tuple_502.t0 = argPats_1;
    tuple_502.t1 = nameCtx_14;
    struct HPat_ListNameCtx_Tuple2 call_752 = stMap_2(fun_54, tuple_502);
    struct HPat_List* argPats_2 = call_752.t0;
    struct NameCtx_ nameCtx_15 = call_752.t1;
    struct HPat_HPat_ListTy_IntIntTuple2Tuple4 tuple_504;
    tuple_504.t0 = calleePat_2;
    tuple_504.t1 = argPats_2;
    tuple_504.t2 = noTy_;
    tuple_504.t3 = loc_89;
    struct HPat_HPat_ListTy_IntIntTuple2Tuple4* payload_169 = (struct HPat_HPat_ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct HPat_HPat_ListTy_IntIntTuple2Tuple4));
    (*(((struct HPat_HPat_ListTy_IntIntTuple2Tuple4*)payload_169))) = tuple_504;
    struct HPat_ variant_169 = (struct HPat_){.tag = Call_1, .Call_1 = payload_169};
    struct HPat_NameCtx_Tuple2 tuple_503;
    tuple_503.t0 = variant_169;
    tuple_503.t1 = nameCtx_15;
    match_273 = tuple_503;
    goto end_match_1059;
next_1066:;
    if ((pat_26.tag != Cons_2)) goto next_1067;
    struct APat_ head_5 = (*(pat_26.Cons_2)).t0;
    struct APat_ tail_7 = (*(pat_26.Cons_2)).t1;
    struct IntIntTuple2 loc_90 = (*(pat_26.Cons_2)).t2;
    struct APat_NameCtx_Tuple2 tuple_505;
    tuple_505.t0 = head_5;
    tuple_505.t1 = nameCtx_11;
    struct HPat_NameCtx_Tuple2 call_753 = onPat_(noTy_, tuple_505);
    struct HPat_ head_6 = call_753.t0;
    struct NameCtx_ nameCtx_16 = call_753.t1;
    struct APat_NameCtx_Tuple2 tuple_506;
    tuple_506.t0 = tail_7;
    tuple_506.t1 = nameCtx_16;
    struct HPat_NameCtx_Tuple2 call_754 = onPat_(noTy_, tuple_506);
    struct HPat_ tail_8 = call_754.t0;
    struct NameCtx_ nameCtx_17 = call_754.t1;
    struct HPat_HPat_Ty_IntIntTuple2Tuple4 tuple_508;
    tuple_508.t0 = head_6;
    tuple_508.t1 = tail_8;
    tuple_508.t2 = noTy_;
    tuple_508.t3 = loc_90;
    struct HPat_HPat_Ty_IntIntTuple2Tuple4* payload_170 = (struct HPat_HPat_Ty_IntIntTuple2Tuple4*)malloc(sizeof(struct HPat_HPat_Ty_IntIntTuple2Tuple4));
    (*(((struct HPat_HPat_Ty_IntIntTuple2Tuple4*)payload_170))) = tuple_508;
    struct HPat_ variant_170 = (struct HPat_){.tag = Cons_3, .Cons_3 = payload_170};
    struct HPat_NameCtx_Tuple2 tuple_507;
    tuple_507.t0 = variant_170;
    tuple_507.t1 = nameCtx_17;
    match_273 = tuple_507;
    goto end_match_1059;
next_1067:;
    if ((pat_26.tag != TupleLit_)) goto next_1068;
    struct APat_List* pats_8 = (*(pat_26.TupleLit_)).t0;
    struct IntIntTuple2 loc_91 = (*(pat_26.TupleLit_)).t1;
    struct Ty_Tuple1 tuple_509;
    tuple_509.t0 = noTy_;
    void* box_10 = (void*)malloc(sizeof(struct Ty_Tuple1));
    (*(((struct Ty_Tuple1*)box_10))) = tuple_509;
    void* env_49 = box_10;
    struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1 fun_55 = (struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1){.fun = fun_19, .env = env_49};
    struct APat_ListNameCtx_Tuple2 tuple_510;
    tuple_510.t0 = pats_8;
    tuple_510.t1 = nameCtx_11;
    struct HPat_ListNameCtx_Tuple2 call_755 = stMap_2(fun_55, tuple_510);
    struct HPat_List* pats_9 = call_755.t0;
    struct NameCtx_ nameCtx_18 = call_755.t1;
    struct HPat_ListTy_IntIntTuple2Tuple3 tuple_512;
    tuple_512.t0 = pats_9;
    tuple_512.t1 = noTy_;
    tuple_512.t2 = loc_91;
    struct HPat_ListTy_IntIntTuple2Tuple3* payload_171 = (struct HPat_ListTy_IntIntTuple2Tuple3*)malloc(sizeof(struct HPat_ListTy_IntIntTuple2Tuple3));
    (*(((struct HPat_ListTy_IntIntTuple2Tuple3*)payload_171))) = tuple_512;
    struct HPat_ variant_171 = (struct HPat_){.tag = Tuple_2, .Tuple_2 = payload_171};
    struct HPat_NameCtx_Tuple2 tuple_511;
    tuple_511.t0 = variant_171;
    tuple_511.t1 = nameCtx_18;
    match_273 = tuple_511;
    goto end_match_1059;
next_1068:;
    if ((pat_26.tag != As_1)) goto next_1069;
    struct APat_ pat_28 = (*(pat_26.As_1)).t0;
    struct String ident_31 = (*(pat_26.As_1)).t1;
    struct IntIntTuple2 loc_92 = (*(pat_26.As_1)).t2;
    struct IntNameCtx_Tuple2 call_756 = nameCtxAdd_(ident_31, nameCtx_11);
    int serial_12 = call_756.t0;
    struct NameCtx_ nameCtx_19 = call_756.t1;
    struct APat_NameCtx_Tuple2 tuple_513;
    tuple_513.t0 = pat_28;
    tuple_513.t1 = nameCtx_19;
    struct HPat_NameCtx_Tuple2 call_757 = onPat_(noTy_, tuple_513);
    struct HPat_ pat_29 = call_757.t0;
    struct NameCtx_ nameCtx_20 = call_757.t1;
    struct HPat_IntIntIntTuple2Tuple3 tuple_515;
    tuple_515.t0 = pat_29;
    tuple_515.t1 = serial_12;
    tuple_515.t2 = loc_92;
    struct HPat_IntIntIntTuple2Tuple3* payload_172 = (struct HPat_IntIntIntTuple2Tuple3*)malloc(sizeof(struct HPat_IntIntIntTuple2Tuple3));
    (*(((struct HPat_IntIntIntTuple2Tuple3*)payload_172))) = tuple_515;
    struct HPat_ variant_172 = (struct HPat_){.tag = As_2, .As_2 = payload_172};
    struct HPat_NameCtx_Tuple2 tuple_514;
    tuple_514.t0 = variant_172;
    tuple_514.t1 = nameCtx_20;
    match_273 = tuple_514;
    goto end_match_1059;
next_1069:;
    if ((pat_26.tag != Anno_)) goto next_1070;
    struct APat_ pat_30 = (*(pat_26.Anno_)).t0;
    struct ATy_ ty_56 = (*(pat_26.Anno_)).t1;
    struct IntIntTuple2 loc_93 = (*(pat_26.Anno_)).t2;
    struct APat_NameCtx_Tuple2 tuple_516;
    tuple_516.t0 = pat_30;
    tuple_516.t1 = nameCtx_11;
    struct HPat_NameCtx_Tuple2 call_758 = onPat_(noTy_, tuple_516);
    struct HPat_ pat_31 = call_758.t0;
    struct NameCtx_ nameCtx_21 = call_758.t1;
    struct ATy_NameCtx_Tuple2 tuple_517;
    tuple_517.t0 = ty_56;
    tuple_517.t1 = nameCtx_21;
    struct Ty_NameCtx_Tuple2 call_759 = onTy_(tuple_517);
    struct Ty_ ty_57 = call_759.t0;
    struct NameCtx_ nameCtx_22 = call_759.t1;
    struct HPat_Ty_IntIntTuple2Tuple3 tuple_519;
    tuple_519.t0 = pat_31;
    tuple_519.t1 = ty_57;
    tuple_519.t2 = loc_93;
    struct HPat_Ty_IntIntTuple2Tuple3* payload_173 = (struct HPat_Ty_IntIntTuple2Tuple3*)malloc(sizeof(struct HPat_Ty_IntIntTuple2Tuple3));
    (*(((struct HPat_Ty_IntIntTuple2Tuple3*)payload_173))) = tuple_519;
    struct HPat_ variant_173 = (struct HPat_){.tag = Anno_2, .Anno_2 = payload_173};
    struct HPat_NameCtx_Tuple2 tuple_518;
    tuple_518.t0 = variant_173;
    tuple_518.t1 = nameCtx_22;
    match_273 = tuple_518;
    goto end_match_1059;
next_1070:;
    if ((pat_26.tag != Or_2)) goto next_1071;
    struct APat_ l_29 = (*(pat_26.Or_2)).t0;
    struct APat_ r_42 = (*(pat_26.Or_2)).t1;
    struct IntIntTuple2 loc_94 = (*(pat_26.Or_2)).t2;
    struct APat_NameCtx_Tuple2 tuple_520;
    tuple_520.t0 = l_29;
    tuple_520.t1 = nameCtx_11;
    struct HPat_NameCtx_Tuple2 call_760 = onPat_(noTy_, tuple_520);
    struct HPat_ l_30 = call_760.t0;
    struct NameCtx_ nameCtx_23 = call_760.t1;
    struct APat_NameCtx_Tuple2 tuple_521;
    tuple_521.t0 = r_42;
    tuple_521.t1 = nameCtx_23;
    struct HPat_NameCtx_Tuple2 call_761 = onPat_(noTy_, tuple_521);
    struct HPat_ r_43 = call_761.t0;
    struct NameCtx_ nameCtx_24 = call_761.t1;
    struct HPat_HPat_Ty_IntIntTuple2Tuple4 tuple_523;
    tuple_523.t0 = l_30;
    tuple_523.t1 = r_43;
    tuple_523.t2 = noTy_;
    tuple_523.t3 = loc_94;
    struct HPat_HPat_Ty_IntIntTuple2Tuple4* payload_174 = (struct HPat_HPat_Ty_IntIntTuple2Tuple4*)malloc(sizeof(struct HPat_HPat_Ty_IntIntTuple2Tuple4));
    (*(((struct HPat_HPat_Ty_IntIntTuple2Tuple4*)payload_174))) = tuple_523;
    struct HPat_ variant_174 = (struct HPat_){.tag = Or_3, .Or_3 = payload_174};
    struct HPat_NameCtx_Tuple2 tuple_522;
    tuple_522.t0 = variant_174;
    tuple_522.t1 = nameCtx_24;
    match_273 = tuple_522;
    goto end_match_1059;
next_1071:;
    if ((pat_26.tag != Fun_2)) goto next_1072;
    struct IntIntTuple2 loc_95 = (*(pat_26.Fun_2)).t2;
    struct IntIntTuple2HPat_NameCtx_Tuple2Fun1 call_762 = failwithf_1((struct String){.str = "Invalid occurrence of fun pattern: %A", .len = 37});
    struct HPat_NameCtx_Tuple2 app_69 = call_762.fun(call_762.env, loc_95);
    match_273 = app_69;
    goto end_match_1059;
next_1072:;
    exit(1);
end_match_1059:;
    return match_273;
}

struct HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2 onArm_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, struct AArm_NameCtx_Tuple2 arg_195) {
    struct APat_ pat_32 = (*(arg_195.t0.AArm_)).t0;
    struct AExpr_ guard_4 = (*(arg_195.t0.AArm_)).t1;
    struct AExpr_ body_20 = (*(arg_195.t0.AArm_)).t2;
    struct IntIntTuple2 loc_103 = (*(arg_195.t0.AArm_)).t3;
    struct NameCtx_ nameCtx_27 = arg_195.t1;
    struct APat_NameCtx_Tuple2 tuple_524;
    tuple_524.t0 = pat_32;
    tuple_524.t1 = nameCtx_27;
    struct HPat_NameCtx_Tuple2 call_763 = onPat_(noTy_, tuple_524);
    struct HPat_ pat_33 = call_763.t0;
    struct NameCtx_ nameCtx_28 = call_763.t1;
    struct HExpr_NameCtx_Tuple2 match_274;
    if ((guard_4.tag != Missing_2)) goto next_1074;
    struct HExpr_ call_764 = hxTrue_(litTrue_, loc_103);
    struct HExpr_NameCtx_Tuple2 tuple_525;
    tuple_525.t0 = call_764;
    tuple_525.t1 = nameCtx_28;
    match_274 = tuple_525;
    goto end_match_1073;
next_1074:;
    struct AExpr_NameCtx_Tuple2 tuple_526;
    tuple_526.t0 = guard_4;
    tuple_526.t1 = nameCtx_28;
    struct HExpr_NameCtx_Tuple2 call_765 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_526);
    match_274 = call_765;
    goto end_match_1073;
next_1075:;
end_match_1073:;
    struct HExpr_ guard_5 = match_274.t0;
    struct NameCtx_ nameCtx_29 = match_274.t1;
    struct AExpr_NameCtx_Tuple2 tuple_527;
    tuple_527.t0 = body_20;
    tuple_527.t1 = nameCtx_29;
    struct HExpr_NameCtx_Tuple2 call_766 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_527);
    struct HExpr_ body_21 = call_766.t0;
    struct NameCtx_ nameCtx_30 = call_766.t1;
    struct HPat_HExpr_HExpr_Tuple3 tuple_529;
    tuple_529.t0 = pat_33;
    tuple_529.t1 = guard_5;
    tuple_529.t2 = body_21;
    struct HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2 tuple_528;
    tuple_528.t0 = tuple_529;
    tuple_528.t1 = nameCtx_30;
    return tuple_528;
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
    struct HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2 call_767 = onArm_(arg_44, arg_45, arg_46, arg_47, arg_48, arg_49, arg_50, arg_51, arg_43);
    return call_767;
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
    struct HExpr_NameCtx_Tuple2 call_768 = onExpr_(arg_53, arg_54, arg_55, arg_56, arg_57, arg_58, arg_59, arg_60, arg_52);
    return call_768;
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
    struct HExpr_NameCtx_Tuple2 call_769 = onExpr_(arg_62, arg_63, arg_64, arg_65, arg_66, arg_67, arg_68, arg_69, arg_61);
    return call_769;
}

struct HPat_NameCtx_Tuple2 fun_23(void* env_17, struct APat_NameCtx_Tuple2 arg_70) {
    struct Ty_ arg_71 = (*(((struct Ty_Tuple1*)env_17))).t0;
    struct HPat_NameCtx_Tuple2 call_770 = onPat_(arg_71, arg_70);
    return call_770;
}

struct BoolTy_NameCtx_Tuple3 {
    int t0;
    struct Ty_ t1;
    struct NameCtx_ t2;
};

struct StringIntBoolTy_Tuple4NameCtx_Tuple2 onVariant_(struct Ty_ tyUnit_, struct AVariant_NameCtx_Tuple2 arg_196) {
    struct String ident_36 = (*(arg_196.t0.AVariant_)).t0;
    struct ATy_List* payloadTy_1 = (*(arg_196.t0.AVariant_)).t1;
    struct IntIntTuple2 _variantLoc_ = (*(arg_196.t0.AVariant_)).t2;
    struct NameCtx_ nameCtx_53 = arg_196.t1;
    struct IntNameCtx_Tuple2 call_771 = nameCtxAdd_(ident_36, nameCtx_53);
    int serial_16 = call_771.t0;
    struct NameCtx_ nameCtx_54 = call_771.t1;
    struct BoolTy_NameCtx_Tuple3 match_275;
    if ((!(payloadTy_1))) goto next_1077;
    struct ATy_ ty_62 = payloadTy_1->head;
    if ((!((!(payloadTy_1->tail))))) goto next_1077;
    struct ATy_NameCtx_Tuple2 tuple_530;
    tuple_530.t0 = ty_62;
    tuple_530.t1 = nameCtx_54;
    struct Ty_NameCtx_Tuple2 call_772 = onTy_(tuple_530);
    struct Ty_ ty_63 = call_772.t0;
    struct NameCtx_ nameCtx_56 = call_772.t1;
    struct BoolTy_NameCtx_Tuple3 tuple_531;
    tuple_531.t0 = 1;
    tuple_531.t1 = ty_63;
    tuple_531.t2 = nameCtx_56;
    match_275 = tuple_531;
    goto end_match_1076;
next_1077:;
    if ((!((!(payloadTy_1))))) goto next_1078;
    struct BoolTy_NameCtx_Tuple3 tuple_532;
    tuple_532.t0 = 0;
    tuple_532.t1 = tyUnit_;
    tuple_532.t2 = nameCtx_54;
    match_275 = tuple_532;
    goto end_match_1076;
next_1078:;
    exit(1);
end_match_1076:;
    int hasPayload_ = match_275.t0;
    struct Ty_ payloadTy_2 = match_275.t1;
    struct NameCtx_ nameCtx_55 = match_275.t2;
    struct StringIntBoolTy_Tuple4 tuple_534;
    tuple_534.t0 = ident_36;
    tuple_534.t1 = serial_16;
    tuple_534.t2 = hasPayload_;
    tuple_534.t3 = payloadTy_2;
    struct StringIntBoolTy_Tuple4NameCtx_Tuple2 tuple_533;
    tuple_533.t0 = tuple_534;
    tuple_533.t1 = nameCtx_55;
    return tuple_533;
}

struct StringIntBoolTy_Tuple4NameCtx_Tuple2 fun_24(void* env_18, struct AVariant_NameCtx_Tuple2 arg_72) {
    struct Ty_ arg_73 = (*(((struct Ty_Tuple1*)env_18))).t0;
    struct StringIntBoolTy_Tuple4NameCtx_Tuple2 call_773 = onVariant_(arg_73, arg_72);
    return call_773;
}

struct StringStringIntBoolTy_Tuple4ListIntIntTuple2Tuple3 {
    struct String t0;
    struct StringIntBoolTy_Tuple4List* t1;
    struct IntIntTuple2 t2;
};

struct HExpr_NameCtx_Tuple2 onExpr_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, struct AExpr_NameCtx_Tuple2 arg_197) {
    struct AExpr_ expr_20 = arg_197.t0;
    struct NameCtx_ nameCtx_25 = arg_197.t1;
    struct HExpr_NameCtx_Tuple2 match_276;
    if ((expr_20.tag != Missing_2)) goto next_1080;
    struct IntIntTuple2 loc_96 = (*(expr_20.Missing_2));
    struct StringIntIntTuple2Tuple2 tuple_536;
    tuple_536.t0 = (struct String){.str = "Missing expression", .len = 18};
    tuple_536.t1 = loc_96;
    struct StringIntIntTuple2Tuple2* payload_175 = (struct StringIntIntTuple2Tuple2*)malloc(sizeof(struct StringIntIntTuple2Tuple2));
    (*(((struct StringIntIntTuple2Tuple2*)payload_175))) = tuple_536;
    struct HExpr_ variant_175 = (struct HExpr_){.tag = Error_2, .Error_2 = payload_175};
    struct HExpr_NameCtx_Tuple2 tuple_535;
    tuple_535.t0 = variant_175;
    tuple_535.t1 = nameCtx_25;
    match_276 = tuple_535;
    goto end_match_1079;
next_1080:;
    if ((expr_20.tag != Lit_1)) goto next_1081;
    struct Lit_ lit_10 = (*(expr_20.Lit_1)).t0;
    struct IntIntTuple2 loc_97 = (*(expr_20.Lit_1)).t1;
    struct Lit_IntIntTuple2Tuple2 tuple_538;
    tuple_538.t0 = lit_10;
    tuple_538.t1 = loc_97;
    struct Lit_IntIntTuple2Tuple2* payload_176 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_176))) = tuple_538;
    struct HExpr_ variant_176 = (struct HExpr_){.tag = Lit_3, .Lit_3 = payload_176};
    struct HExpr_NameCtx_Tuple2 tuple_537;
    tuple_537.t0 = variant_176;
    tuple_537.t1 = nameCtx_25;
    match_276 = tuple_537;
    goto end_match_1079;
next_1081:;
    if ((expr_20.tag != Ident_2)) goto next_1082;
    struct String ident_32 = (*(expr_20.Ident_2)).t0;
    struct IntIntTuple2 loc_98 = (*(expr_20.Ident_2)).t1;
    struct IntNameCtx_Tuple2 call_774 = nameCtxAdd_(ident_32, nameCtx_25);
    int serial_13 = call_774.t0;
    struct NameCtx_ nameCtx_26 = call_774.t1;
    struct IntTy_IntIntTuple2Tuple3 tuple_540;
    tuple_540.t0 = serial_13;
    tuple_540.t1 = noTy_;
    tuple_540.t2 = loc_98;
    struct IntTy_IntIntTuple2Tuple3* payload_177 = (struct IntTy_IntIntTuple2Tuple3*)malloc(sizeof(struct IntTy_IntIntTuple2Tuple3));
    (*(((struct IntTy_IntIntTuple2Tuple3*)payload_177))) = tuple_540;
    struct HExpr_ variant_177 = (struct HExpr_){.tag = Ref_2, .Ref_2 = payload_177};
    struct HExpr_NameCtx_Tuple2 tuple_539;
    tuple_539.t0 = variant_177;
    tuple_539.t1 = nameCtx_26;
    match_276 = tuple_539;
    goto end_match_1079;
next_1082:;
    if ((expr_20.tag != ListLit_1)) goto next_1083;
    if ((!((!((*(expr_20.ListLit_1)).t0))))) goto next_1083;
    struct IntIntTuple2 loc_99 = (*(expr_20.ListLit_1)).t1;
    struct HExpr_ call_775 = hxNil_(noTy_, loc_99);
    struct HExpr_NameCtx_Tuple2 tuple_541;
    tuple_541.t0 = call_775;
    tuple_541.t1 = nameCtx_25;
    match_276 = tuple_541;
    goto end_match_1079;
next_1083:;
    if ((expr_20.tag != ListLit_1)) goto next_1084;
    struct AExpr_List* items_11 = (*(expr_20.ListLit_1)).t0;
    struct IntIntTuple2 loc_100 = (*(expr_20.ListLit_1)).t1;
    struct AExpr_ call_776 = desugarListLitExpr_(items_11, loc_100);
    struct AExpr_ expr_21 = call_776;
    struct AExpr_NameCtx_Tuple2 tuple_542;
    tuple_542.t0 = expr_21;
    tuple_542.t1 = nameCtx_25;
    struct HExpr_NameCtx_Tuple2 call_777 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_542);
    match_276 = call_777;
    goto end_match_1079;
next_1084:;
    if ((expr_20.tag != If_1)) goto next_1085;
    struct AExpr_ cond_3 = (*(expr_20.If_1)).t0;
    struct AExpr_ body_19 = (*(expr_20.If_1)).t1;
    struct AExpr_ alt_4 = (*(expr_20.If_1)).t2;
    struct IntIntTuple2 loc_101 = (*(expr_20.If_1)).t3;
    struct AExpr_ call_778 = desugarIf_(litFalse_, litTrue_, cond_3, body_19, alt_4, loc_101);
    struct AExpr_ expr_22 = call_778;
    struct AExpr_NameCtx_Tuple2 tuple_543;
    tuple_543.t0 = expr_22;
    tuple_543.t1 = nameCtx_25;
    struct HExpr_NameCtx_Tuple2 call_779 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_543);
    match_276 = call_779;
    goto end_match_1079;
next_1085:;
    if ((expr_20.tag != Match_1)) goto next_1086;
    struct AExpr_ target_4 = (*(expr_20.Match_1)).t0;
    struct AArm_List* arms_5 = (*(expr_20.Match_1)).t1;
    struct IntIntTuple2 loc_102 = (*(expr_20.Match_1)).t2;
    struct AExpr_NameCtx_Tuple2 tuple_544;
    tuple_544.t0 = target_4;
    tuple_544.t1 = nameCtx_25;
    struct HExpr_NameCtx_Tuple2 call_780 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_544);
    struct HExpr_ target_5 = call_780.t0;
    struct NameCtx_ nameCtx_31 = call_780.t1;
    struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8 tuple_545;
    tuple_545.t0 = litFalse_;
    tuple_545.t1 = litTrue_;
    tuple_545.t2 = tyUnit_;
    tuple_545.t3 = tyStr_;
    tuple_545.t4 = tyChar_;
    tuple_545.t5 = tyInt_;
    tuple_545.t6 = tyBool_;
    tuple_545.t7 = noTy_;
    void* box_11 = (void*)malloc(sizeof(struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8));
    (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)box_11))) = tuple_545;
    void* env_50 = box_11;
    struct AArm_NameCtx_Tuple2HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2Fun1 fun_56 = (struct AArm_NameCtx_Tuple2HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2Fun1){.fun = fun_20, .env = env_50};
    struct AArm_ListNameCtx_Tuple2 tuple_546;
    tuple_546.t0 = arms_5;
    tuple_546.t1 = nameCtx_31;
    struct HPat_HExpr_HExpr_Tuple3ListNameCtx_Tuple2 call_781 = stMap_4(fun_56, tuple_546);
    struct HPat_HExpr_HExpr_Tuple3List* arms_6 = call_781.t0;
    struct NameCtx_ nameCtx_32 = call_781.t1;
    struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4 tuple_548;
    tuple_548.t0 = target_5;
    tuple_548.t1 = arms_6;
    tuple_548.t2 = noTy_;
    tuple_548.t3 = loc_102;
    struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4* payload_178 = (struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4));
    (*(((struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4*)payload_178))) = tuple_548;
    struct HExpr_ variant_178 = (struct HExpr_){.tag = Match_2, .Match_2 = payload_178};
    struct HExpr_NameCtx_Tuple2 tuple_547;
    tuple_547.t0 = variant_178;
    tuple_547.t1 = nameCtx_32;
    match_276 = tuple_547;
    goto end_match_1079;
next_1086:;
    if ((expr_20.tag != Fun_3)) goto next_1087;
    struct APat_List* pats_10 = (*(expr_20.Fun_3)).t0;
    struct AExpr_ body_22 = (*(expr_20.Fun_3)).t1;
    struct IntIntTuple2 loc_104 = (*(expr_20.Fun_3)).t2;
    struct AExpr_ call_782 = desugarFun_(pats_10, body_22, loc_104);
    struct AExpr_ expr_23 = call_782;
    struct AExpr_NameCtx_Tuple2 tuple_549;
    tuple_549.t0 = expr_23;
    tuple_549.t1 = nameCtx_25;
    struct HExpr_NameCtx_Tuple2 call_783 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_549);
    match_276 = call_783;
    goto end_match_1079;
next_1087:;
    if ((expr_20.tag != Nav_1)) goto next_1088;
    struct AExpr_ l_31 = (*(expr_20.Nav_1)).t0;
    struct String r_44 = (*(expr_20.Nav_1)).t1;
    struct IntIntTuple2 loc_105 = (*(expr_20.Nav_1)).t2;
    struct AExpr_NameCtx_Tuple2 tuple_550;
    tuple_550.t0 = l_31;
    tuple_550.t1 = nameCtx_25;
    struct HExpr_NameCtx_Tuple2 call_784 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_550);
    struct HExpr_ l_32 = call_784.t0;
    struct NameCtx_ nameCtx_33 = call_784.t1;
    struct HExpr_StringTy_IntIntTuple2Tuple4 tuple_552;
    tuple_552.t0 = l_32;
    tuple_552.t1 = r_44;
    tuple_552.t2 = noTy_;
    tuple_552.t3 = loc_105;
    struct HExpr_StringTy_IntIntTuple2Tuple4* payload_179 = (struct HExpr_StringTy_IntIntTuple2Tuple4*)malloc(sizeof(struct HExpr_StringTy_IntIntTuple2Tuple4));
    (*(((struct HExpr_StringTy_IntIntTuple2Tuple4*)payload_179))) = tuple_552;
    struct HExpr_ variant_179 = (struct HExpr_){.tag = Nav_3, .Nav_3 = payload_179};
    struct HExpr_NameCtx_Tuple2 tuple_551;
    tuple_551.t0 = variant_179;
    tuple_551.t1 = nameCtx_33;
    match_276 = tuple_551;
    goto end_match_1079;
next_1088:;
    if ((expr_20.tag != Index_)) goto next_1089;
    struct AExpr_ l_33 = (*(expr_20.Index_)).t0;
    struct AExpr_ r_45 = (*(expr_20.Index_)).t1;
    struct IntIntTuple2 loc_106 = (*(expr_20.Index_)).t2;
    struct HExpr_NameCtx_Tuple2 match_277;
    struct BoolAExpr_Tuple2 call_785 = tryDesugarIndexRange_(expr_20, loc_106);
    if ((!(call_785.t0))) goto next_1109;
    struct AExpr_ expr_24 = call_785.t1;
    struct AExpr_NameCtx_Tuple2 tuple_553;
    tuple_553.t0 = expr_24;
    tuple_553.t1 = nameCtx_25;
    struct HExpr_NameCtx_Tuple2 call_786 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_553);
    match_277 = call_786;
    goto end_match_1108;
next_1109:;
    if (call_785.t0) goto next_1110;
    struct AExpr_NameCtx_Tuple2 tuple_554;
    tuple_554.t0 = l_33;
    tuple_554.t1 = nameCtx_25;
    struct HExpr_NameCtx_Tuple2 call_787 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_554);
    struct HExpr_ l_34 = call_787.t0;
    struct NameCtx_ nameCtx_34 = call_787.t1;
    struct AExpr_NameCtx_Tuple2 tuple_555;
    tuple_555.t0 = r_45;
    tuple_555.t1 = nameCtx_34;
    struct HExpr_NameCtx_Tuple2 call_788 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_555);
    struct HExpr_ r_46 = call_788.t0;
    struct NameCtx_ nameCtx_35 = call_788.t1;
    struct HPrim_Ty_IntIntTuple2Tuple3 tuple_556;
    tuple_556.t0 = (struct HPrim_){.tag = Index_2};
    tuple_556.t1 = noTy_;
    tuple_556.t2 = loc_106;
    struct HPrim_Ty_IntIntTuple2Tuple3* payload_180 = (struct HPrim_Ty_IntIntTuple2Tuple3*)malloc(sizeof(struct HPrim_Ty_IntIntTuple2Tuple3));
    (*(((struct HPrim_Ty_IntIntTuple2Tuple3*)payload_180))) = tuple_556;
    struct HExpr_ variant_180 = (struct HExpr_){.tag = Prim_, .Prim_ = payload_180};
    struct HExpr_ call_789 = hxApp_(variant_180, l_34, noTy_, loc_106);
    struct HExpr_ call_790 = hxApp_(call_789, r_46, noTy_, loc_106);
    struct HExpr_ hxIndex_ = call_790;
    struct HExpr_NameCtx_Tuple2 tuple_557;
    tuple_557.t0 = hxIndex_;
    tuple_557.t1 = nameCtx_35;
    match_277 = tuple_557;
    goto end_match_1108;
next_1110:;
    exit(1);
end_match_1108:;
    match_276 = match_277;
    goto end_match_1079;
next_1089:;
    if ((expr_20.tag != Uni_)) goto next_1090;
    if (((*(expr_20.Uni_)).t0.tag != Neg_)) goto next_1090;
    struct AExpr_ arg_5 = (*(expr_20.Uni_)).t1;
    struct IntIntTuple2 loc_107 = (*(expr_20.Uni_)).t2;
    struct AExpr_ call_791 = desugarUniNeg_(arg_5, loc_107);
    struct AExpr_ expr_25 = call_791;
    struct AExpr_NameCtx_Tuple2 tuple_558;
    tuple_558.t0 = expr_25;
    tuple_558.t1 = nameCtx_25;
    struct HExpr_NameCtx_Tuple2 call_792 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_558);
    match_276 = call_792;
    goto end_match_1079;
next_1090:;
    if ((expr_20.tag != Bin_)) goto next_1091;
    if (((*(expr_20.Bin_)).t0.tag != Ne_)) goto next_1091;
    struct AExpr_ l_35 = (*(expr_20.Bin_)).t1;
    struct AExpr_ r_47 = (*(expr_20.Bin_)).t2;
    struct IntIntTuple2 loc_108 = (*(expr_20.Bin_)).t3;
    struct AExpr_ call_793 = desugarBinNe_(litFalse_, l_35, r_47, loc_108);
    struct AExpr_ expr_26 = call_793;
    struct AExpr_NameCtx_Tuple2 tuple_559;
    tuple_559.t0 = expr_26;
    tuple_559.t1 = nameCtx_25;
    struct HExpr_NameCtx_Tuple2 call_794 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_559);
    match_276 = call_794;
    goto end_match_1079;
next_1091:;
    if ((expr_20.tag != Bin_)) goto next_1092;
    if (((*(expr_20.Bin_)).t0.tag != Le_)) goto next_1092;
    struct AExpr_ l_36 = (*(expr_20.Bin_)).t1;
    struct AExpr_ r_48 = (*(expr_20.Bin_)).t2;
    struct IntIntTuple2 loc_109 = (*(expr_20.Bin_)).t3;
    struct AExpr_ call_795 = desugarBinLe_(litFalse_, l_36, r_48, loc_109);
    struct AExpr_ expr_27 = call_795;
    struct AExpr_NameCtx_Tuple2 tuple_560;
    tuple_560.t0 = expr_27;
    tuple_560.t1 = nameCtx_25;
    struct HExpr_NameCtx_Tuple2 call_796 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_560);
    match_276 = call_796;
    goto end_match_1079;
next_1092:;
    if ((expr_20.tag != Bin_)) goto next_1093;
    if (((*(expr_20.Bin_)).t0.tag != Gt_1)) goto next_1093;
    struct AExpr_ l_37 = (*(expr_20.Bin_)).t1;
    struct AExpr_ r_49 = (*(expr_20.Bin_)).t2;
    struct IntIntTuple2 loc_110 = (*(expr_20.Bin_)).t3;
    struct AExpr_ call_797 = desugarBinGt_(l_37, r_49, loc_110);
    struct AExpr_ expr_28 = call_797;
    struct AExpr_NameCtx_Tuple2 tuple_561;
    tuple_561.t0 = expr_28;
    tuple_561.t1 = nameCtx_25;
    struct HExpr_NameCtx_Tuple2 call_798 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_561);
    match_276 = call_798;
    goto end_match_1079;
next_1093:;
    if ((expr_20.tag != Bin_)) goto next_1094;
    if (((*(expr_20.Bin_)).t0.tag != Ge_)) goto next_1094;
    struct AExpr_ l_38 = (*(expr_20.Bin_)).t1;
    struct AExpr_ r_50 = (*(expr_20.Bin_)).t2;
    struct IntIntTuple2 loc_111 = (*(expr_20.Bin_)).t3;
    struct AExpr_ call_799 = desugarBinGe_(litFalse_, l_38, r_50, loc_111);
    struct AExpr_ expr_29 = call_799;
    struct AExpr_NameCtx_Tuple2 tuple_562;
    tuple_562.t0 = expr_29;
    tuple_562.t1 = nameCtx_25;
    struct HExpr_NameCtx_Tuple2 call_800 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_562);
    match_276 = call_800;
    goto end_match_1079;
next_1094:;
    if ((expr_20.tag != Bin_)) goto next_1095;
    if (((*(expr_20.Bin_)).t0.tag != And_1)) goto next_1095;
    struct AExpr_ l_39 = (*(expr_20.Bin_)).t1;
    struct AExpr_ r_51 = (*(expr_20.Bin_)).t2;
    struct IntIntTuple2 loc_112 = (*(expr_20.Bin_)).t3;
    struct AExpr_ call_801 = desugarBinAnd_(litFalse_, litTrue_, l_39, r_51, loc_112);
    struct AExpr_ expr_30 = call_801;
    struct AExpr_NameCtx_Tuple2 tuple_563;
    tuple_563.t0 = expr_30;
    tuple_563.t1 = nameCtx_25;
    struct HExpr_NameCtx_Tuple2 call_802 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_563);
    match_276 = call_802;
    goto end_match_1079;
next_1095:;
    if ((expr_20.tag != Bin_)) goto next_1096;
    if (((*(expr_20.Bin_)).t0.tag != Or_1)) goto next_1096;
    struct AExpr_ l_40 = (*(expr_20.Bin_)).t1;
    struct AExpr_ r_52 = (*(expr_20.Bin_)).t2;
    struct IntIntTuple2 loc_113 = (*(expr_20.Bin_)).t3;
    struct AExpr_ call_803 = desugarBinOr_(litFalse_, litTrue_, l_40, r_52, loc_113);
    struct AExpr_ expr_31 = call_803;
    struct AExpr_NameCtx_Tuple2 tuple_564;
    tuple_564.t0 = expr_31;
    tuple_564.t1 = nameCtx_25;
    struct HExpr_NameCtx_Tuple2 call_804 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_564);
    match_276 = call_804;
    goto end_match_1079;
next_1096:;
    if ((expr_20.tag != Bin_)) goto next_1097;
    if (((*(expr_20.Bin_)).t0.tag != Pipe_2)) goto next_1097;
    struct AExpr_ l_41 = (*(expr_20.Bin_)).t1;
    struct AExpr_ r_53 = (*(expr_20.Bin_)).t2;
    struct IntIntTuple2 loc_114 = (*(expr_20.Bin_)).t3;
    struct AExpr_ call_805 = desugarBinPipe_(l_41, r_53, loc_114);
    struct AExpr_ expr_32 = call_805;
    struct AExpr_NameCtx_Tuple2 tuple_565;
    tuple_565.t0 = expr_32;
    tuple_565.t1 = nameCtx_25;
    struct HExpr_NameCtx_Tuple2 call_806 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_565);
    match_276 = call_806;
    goto end_match_1079;
next_1097:;
    if ((expr_20.tag != Bin_)) goto next_1098;
    if (((*(expr_20.Bin_)).t0.tag != App_)) goto next_1098;
    struct AExpr_ l_42 = (*(expr_20.Bin_)).t1;
    struct AExpr_ r_54 = (*(expr_20.Bin_)).t2;
    struct IntIntTuple2 loc_115 = (*(expr_20.Bin_)).t3;
    struct AExpr_NameCtx_Tuple2 tuple_566;
    tuple_566.t0 = l_42;
    tuple_566.t1 = nameCtx_25;
    struct HExpr_NameCtx_Tuple2 call_807 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_566);
    struct HExpr_ l_43 = call_807.t0;
    struct NameCtx_ nameCtx_36 = call_807.t1;
    struct AExpr_NameCtx_Tuple2 tuple_567;
    tuple_567.t0 = r_54;
    tuple_567.t1 = nameCtx_36;
    struct HExpr_NameCtx_Tuple2 call_808 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_567);
    struct HExpr_ r_55 = call_808.t0;
    struct NameCtx_ nameCtx_37 = call_808.t1;
    struct HExpr_ call_809 = hxApp_(l_43, r_55, noTy_, loc_115);
    struct HExpr_NameCtx_Tuple2 tuple_568;
    tuple_568.t0 = call_809;
    tuple_568.t1 = nameCtx_37;
    match_276 = tuple_568;
    goto end_match_1079;
next_1098:;
    if ((expr_20.tag != Bin_)) goto next_1099;
    struct Op_ op_3 = (*(expr_20.Bin_)).t0;
    struct AExpr_ l_44 = (*(expr_20.Bin_)).t1;
    struct AExpr_ r_56 = (*(expr_20.Bin_)).t2;
    struct IntIntTuple2 loc_116 = (*(expr_20.Bin_)).t3;
    struct HPrim_ call_810 = opToPrim_(op_3);
    struct HPrim_ prim_2 = call_810;
    struct AExpr_NameCtx_Tuple2 tuple_569;
    tuple_569.t0 = l_44;
    tuple_569.t1 = nameCtx_25;
    struct HExpr_NameCtx_Tuple2 call_811 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_569);
    struct HExpr_ l_45 = call_811.t0;
    struct NameCtx_ nameCtx_38 = call_811.t1;
    struct AExpr_NameCtx_Tuple2 tuple_570;
    tuple_570.t0 = r_56;
    tuple_570.t1 = nameCtx_38;
    struct HExpr_NameCtx_Tuple2 call_812 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_570);
    struct HExpr_ r_57 = call_812.t0;
    struct NameCtx_ nameCtx_39 = call_812.t1;
    struct HPrim_Ty_IntIntTuple2Tuple3 tuple_571;
    tuple_571.t0 = prim_2;
    tuple_571.t1 = noTy_;
    tuple_571.t2 = loc_116;
    struct HPrim_Ty_IntIntTuple2Tuple3* payload_181 = (struct HPrim_Ty_IntIntTuple2Tuple3*)malloc(sizeof(struct HPrim_Ty_IntIntTuple2Tuple3));
    (*(((struct HPrim_Ty_IntIntTuple2Tuple3*)payload_181))) = tuple_571;
    struct HExpr_ variant_181 = (struct HExpr_){.tag = Prim_, .Prim_ = payload_181};
    struct HExpr_ primExpr_ = variant_181;
    struct HExpr_ call_813 = hxApp_(primExpr_, l_45, noTy_, loc_116);
    struct HExpr_ call_814 = hxApp_(call_813, r_57, noTy_, loc_116);
    struct HExpr_NameCtx_Tuple2 tuple_572;
    tuple_572.t0 = call_814;
    tuple_572.t1 = nameCtx_39;
    match_276 = tuple_572;
    goto end_match_1079;
next_1099:;
    if ((expr_20.tag != Range_)) goto next_1100;
    struct IntIntTuple2 loc_117 = (*(expr_20.Range_)).t1;
    struct StringIntIntTuple2Tuple2 tuple_574;
    tuple_574.t0 = (struct String){.str = "Invalid use of range syntax.", .len = 28};
    tuple_574.t1 = loc_117;
    struct StringIntIntTuple2Tuple2* payload_182 = (struct StringIntIntTuple2Tuple2*)malloc(sizeof(struct StringIntIntTuple2Tuple2));
    (*(((struct StringIntIntTuple2Tuple2*)payload_182))) = tuple_574;
    struct HExpr_ variant_182 = (struct HExpr_){.tag = Error_2, .Error_2 = payload_182};
    struct HExpr_NameCtx_Tuple2 tuple_573;
    tuple_573.t0 = variant_182;
    tuple_573.t1 = nameCtx_25;
    match_276 = tuple_573;
    goto end_match_1079;
next_1100:;
    if ((expr_20.tag != TupleLit_1)) goto next_1101;
    struct AExpr_List* items_12 = (*(expr_20.TupleLit_1)).t0;
    struct IntIntTuple2 loc_118 = (*(expr_20.TupleLit_1)).t1;
    struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8 tuple_575;
    tuple_575.t0 = litFalse_;
    tuple_575.t1 = litTrue_;
    tuple_575.t2 = tyUnit_;
    tuple_575.t3 = tyStr_;
    tuple_575.t4 = tyChar_;
    tuple_575.t5 = tyInt_;
    tuple_575.t6 = tyBool_;
    tuple_575.t7 = noTy_;
    void* box_12 = (void*)malloc(sizeof(struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8));
    (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)box_12))) = tuple_575;
    void* env_51 = box_12;
    struct AExpr_NameCtx_Tuple2HExpr_NameCtx_Tuple2Fun1 fun_57 = (struct AExpr_NameCtx_Tuple2HExpr_NameCtx_Tuple2Fun1){.fun = fun_21, .env = env_51};
    struct AExpr_ListNameCtx_Tuple2 tuple_576;
    tuple_576.t0 = items_12;
    tuple_576.t1 = nameCtx_25;
    struct HExpr_ListNameCtx_Tuple2 call_815 = stMap_3(fun_57, tuple_576);
    struct HExpr_List* items_13 = call_815.t0;
    struct NameCtx_ nameCtx_40 = call_815.t1;
    struct HExpr_ call_816 = hxTuple_(tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, items_13, loc_118);
    struct HExpr_NameCtx_Tuple2 tuple_577;
    tuple_577.t0 = call_816;
    tuple_577.t1 = nameCtx_40;
    match_276 = tuple_577;
    goto end_match_1079;
next_1101:;
    if ((expr_20.tag != Anno_1)) goto next_1102;
    struct AExpr_ body_23 = (*(expr_20.Anno_1)).t0;
    struct ATy_ ty_58 = (*(expr_20.Anno_1)).t1;
    struct IntIntTuple2 loc_119 = (*(expr_20.Anno_1)).t2;
    struct AExpr_NameCtx_Tuple2 tuple_578;
    tuple_578.t0 = body_23;
    tuple_578.t1 = nameCtx_25;
    struct HExpr_NameCtx_Tuple2 call_817 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_578);
    struct HExpr_ body_24 = call_817.t0;
    struct NameCtx_ nameCtx_41 = call_817.t1;
    struct ATy_NameCtx_Tuple2 tuple_579;
    tuple_579.t0 = ty_58;
    tuple_579.t1 = nameCtx_41;
    struct Ty_NameCtx_Tuple2 call_818 = onTy_(tuple_579);
    struct Ty_ ty_59 = call_818.t0;
    struct NameCtx_ nameCtx_42 = call_818.t1;
    struct HExpr_ call_819 = hxAnno_(body_24, ty_59, loc_119);
    struct HExpr_NameCtx_Tuple2 tuple_580;
    tuple_580.t0 = call_819;
    tuple_580.t1 = nameCtx_42;
    match_276 = tuple_580;
    goto end_match_1079;
next_1102:;
    if ((expr_20.tag != Semi_1)) goto next_1103;
    struct AExpr_List* exprs_1 = (*(expr_20.Semi_1)).t0;
    struct IntIntTuple2 loc_120 = (*(expr_20.Semi_1)).t1;
    int call_820 = listIsEmpty_1(exprs_1);
    milone_assert((!(call_820)), 390, 4);
    int call_821 = 0;
    struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8 tuple_581;
    tuple_581.t0 = litFalse_;
    tuple_581.t1 = litTrue_;
    tuple_581.t2 = tyUnit_;
    tuple_581.t3 = tyStr_;
    tuple_581.t4 = tyChar_;
    tuple_581.t5 = tyInt_;
    tuple_581.t6 = tyBool_;
    tuple_581.t7 = noTy_;
    void* box_13 = (void*)malloc(sizeof(struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8));
    (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)box_13))) = tuple_581;
    void* env_52 = box_13;
    struct AExpr_NameCtx_Tuple2HExpr_NameCtx_Tuple2Fun1 fun_58 = (struct AExpr_NameCtx_Tuple2HExpr_NameCtx_Tuple2Fun1){.fun = fun_22, .env = env_52};
    struct AExpr_ListNameCtx_Tuple2 tuple_582;
    tuple_582.t0 = exprs_1;
    tuple_582.t1 = nameCtx_25;
    struct HExpr_ListNameCtx_Tuple2 call_822 = stMap_3(fun_58, tuple_582);
    struct HExpr_List* exprs_2 = call_822.t0;
    struct NameCtx_ nameCtx_43 = call_822.t1;
    struct HExpr_ call_823 = hxSemi_(noTy_, exprs_2, loc_120);
    struct HExpr_NameCtx_Tuple2 tuple_583;
    tuple_583.t0 = call_823;
    tuple_583.t1 = nameCtx_43;
    match_276 = tuple_583;
    goto end_match_1079;
next_1103:;
    if ((expr_20.tag != Let_1)) goto next_1104;
    struct APat_ pat_34 = (*(expr_20.Let_1)).t0;
    struct AExpr_ body_25 = (*(expr_20.Let_1)).t1;
    struct AExpr_ next_14 = (*(expr_20.Let_1)).t2;
    struct IntIntTuple2 loc_121 = (*(expr_20.Let_1)).t3;
    struct HExpr_NameCtx_Tuple2 match_278;
    struct ALet_ call_824 = desugarLet_(pat_34, body_25, next_14, loc_121);
    if ((call_824.tag != LetFun_)) goto next_1112;
    struct String ident_33 = (*(call_824.LetFun_)).t0;
    struct APat_List* args_9 = (*(call_824.LetFun_)).t1;
    struct AExpr_ body_26 = (*(call_824.LetFun_)).t2;
    struct AExpr_ next_15 = (*(call_824.LetFun_)).t3;
    struct IntIntTuple2 loc_122 = (*(call_824.LetFun_)).t4;
    struct IntNameCtx_Tuple2 call_825 = nameCtxAdd_(ident_33, nameCtx_25);
    int serial_14 = call_825.t0;
    struct NameCtx_ nameCtx_44 = call_825.t1;
    int isMainFun_1 = 0;
    struct Ty_Tuple1 tuple_584;
    tuple_584.t0 = noTy_;
    void* box_14 = (void*)malloc(sizeof(struct Ty_Tuple1));
    (*(((struct Ty_Tuple1*)box_14))) = tuple_584;
    void* env_53 = box_14;
    struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1 fun_59 = (struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1){.fun = fun_23, .env = env_53};
    struct APat_ListNameCtx_Tuple2 tuple_585;
    tuple_585.t0 = args_9;
    tuple_585.t1 = nameCtx_44;
    struct HPat_ListNameCtx_Tuple2 call_826 = stMap_2(fun_59, tuple_585);
    struct HPat_List* args_10 = call_826.t0;
    struct NameCtx_ nameCtx_45 = call_826.t1;
    struct AExpr_NameCtx_Tuple2 tuple_586;
    tuple_586.t0 = body_26;
    tuple_586.t1 = nameCtx_45;
    struct HExpr_NameCtx_Tuple2 call_827 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_586);
    struct HExpr_ body_27 = call_827.t0;
    struct NameCtx_ nameCtx_46 = call_827.t1;
    struct AExpr_NameCtx_Tuple2 tuple_587;
    tuple_587.t0 = next_15;
    tuple_587.t1 = nameCtx_46;
    struct HExpr_NameCtx_Tuple2 call_828 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_587);
    struct HExpr_ next_16 = call_828.t0;
    struct NameCtx_ nameCtx_47 = call_828.t1;
    struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7 tuple_589;
    tuple_589.t0 = serial_14;
    tuple_589.t1 = isMainFun_1;
    tuple_589.t2 = args_10;
    tuple_589.t3 = body_27;
    tuple_589.t4 = next_16;
    tuple_589.t5 = noTy_;
    tuple_589.t6 = loc_122;
    struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7* payload_183 = (struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7*)malloc(sizeof(struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7));
    (*(((struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7*)payload_183))) = tuple_589;
    struct HExpr_ variant_183 = (struct HExpr_){.tag = LetFun_1, .LetFun_1 = payload_183};
    struct HExpr_NameCtx_Tuple2 tuple_588;
    tuple_588.t0 = variant_183;
    tuple_588.t1 = nameCtx_47;
    match_278 = tuple_588;
    goto end_match_1111;
next_1112:;
    if ((call_824.tag != LetVal_)) goto next_1113;
    struct APat_ pat_35 = (*(call_824.LetVal_)).t0;
    struct AExpr_ body_28 = (*(call_824.LetVal_)).t1;
    struct AExpr_ next_17 = (*(call_824.LetVal_)).t2;
    struct IntIntTuple2 loc_123 = (*(call_824.LetVal_)).t3;
    struct APat_NameCtx_Tuple2 tuple_590;
    tuple_590.t0 = pat_35;
    tuple_590.t1 = nameCtx_25;
    struct HPat_NameCtx_Tuple2 call_829 = onPat_(noTy_, tuple_590);
    struct HPat_ pat_36 = call_829.t0;
    struct NameCtx_ nameCtx_48 = call_829.t1;
    struct AExpr_NameCtx_Tuple2 tuple_591;
    tuple_591.t0 = body_28;
    tuple_591.t1 = nameCtx_48;
    struct HExpr_NameCtx_Tuple2 call_830 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_591);
    struct HExpr_ body_29 = call_830.t0;
    struct NameCtx_ nameCtx_49 = call_830.t1;
    struct AExpr_NameCtx_Tuple2 tuple_592;
    tuple_592.t0 = next_17;
    tuple_592.t1 = nameCtx_49;
    struct HExpr_NameCtx_Tuple2 call_831 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_592);
    struct HExpr_ next_18 = call_831.t0;
    struct NameCtx_ nameCtx_50 = call_831.t1;
    struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5 tuple_594;
    tuple_594.t0 = pat_36;
    tuple_594.t1 = body_29;
    tuple_594.t2 = next_18;
    tuple_594.t3 = noTy_;
    tuple_594.t4 = loc_123;
    struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5* payload_184 = (struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5*)malloc(sizeof(struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5));
    (*(((struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5*)payload_184))) = tuple_594;
    struct HExpr_ variant_184 = (struct HExpr_){.tag = Let_2, .Let_2 = payload_184};
    struct HExpr_NameCtx_Tuple2 tuple_593;
    tuple_593.t0 = variant_184;
    tuple_593.t1 = nameCtx_50;
    match_278 = tuple_593;
    goto end_match_1111;
next_1113:;
    exit(1);
end_match_1111:;
    match_276 = match_278;
    goto end_match_1079;
next_1104:;
    if ((expr_20.tag != TySynonym_)) goto next_1105;
    struct String ident_34 = (*(expr_20.TySynonym_)).t0;
    struct ATy_ ty_60 = (*(expr_20.TySynonym_)).t1;
    struct IntIntTuple2 loc_124 = (*(expr_20.TySynonym_)).t2;
    struct IntNameCtx_Tuple2 call_832 = nameCtxAdd_(ident_34, nameCtx_25);
    int serial_15 = call_832.t0;
    struct NameCtx_ nameCtx_51 = call_832.t1;
    struct ATy_NameCtx_Tuple2 tuple_595;
    tuple_595.t0 = ty_60;
    tuple_595.t1 = nameCtx_51;
    struct Ty_NameCtx_Tuple2 call_833 = onTy_(tuple_595);
    struct Ty_ ty_61 = call_833.t0;
    struct NameCtx_ nameCtx_52 = call_833.t1;
    struct Ty_IntIntTuple2Tuple2 tuple_598;
    tuple_598.t0 = ty_61;
    tuple_598.t1 = loc_124;
    struct Ty_IntIntTuple2Tuple2* payload_185 = (struct Ty_IntIntTuple2Tuple2*)malloc(sizeof(struct Ty_IntIntTuple2Tuple2));
    (*(((struct Ty_IntIntTuple2Tuple2*)payload_185))) = tuple_598;
    struct TyDecl_ variant_185 = (struct TyDecl_){.tag = Synonym_1, .Synonym_1 = payload_185};
    struct IntTyDecl_IntIntTuple2Tuple3 tuple_597;
    tuple_597.t0 = serial_15;
    tuple_597.t1 = variant_185;
    tuple_597.t2 = loc_124;
    struct IntTyDecl_IntIntTuple2Tuple3* payload_186 = (struct IntTyDecl_IntIntTuple2Tuple3*)malloc(sizeof(struct IntTyDecl_IntIntTuple2Tuple3));
    (*(((struct IntTyDecl_IntIntTuple2Tuple3*)payload_186))) = tuple_597;
    struct HExpr_ variant_186 = (struct HExpr_){.tag = TyDecl_, .TyDecl_ = payload_186};
    struct HExpr_NameCtx_Tuple2 tuple_596;
    tuple_596.t0 = variant_186;
    tuple_596.t1 = nameCtx_52;
    match_276 = tuple_596;
    goto end_match_1079;
next_1105:;
    if ((expr_20.tag != TyUnion_)) goto next_1106;
    struct String ident_35 = (*(expr_20.TyUnion_)).t0;
    struct AVariant_List* variants_3 = (*(expr_20.TyUnion_)).t1;
    struct IntIntTuple2 loc_125 = (*(expr_20.TyUnion_)).t2;
    struct IntNameCtx_Tuple2 call_834 = nameCtxAdd_(ident_35, nameCtx_25);
    int unionSerial_ = call_834.t0;
    struct NameCtx_ nameCtx_57 = call_834.t1;
    struct Ty_Tuple1 tuple_599;
    tuple_599.t0 = tyUnit_;
    void* box_15 = (void*)malloc(sizeof(struct Ty_Tuple1));
    (*(((struct Ty_Tuple1*)box_15))) = tuple_599;
    void* env_54 = box_15;
    struct AVariant_NameCtx_Tuple2StringIntBoolTy_Tuple4NameCtx_Tuple2Fun1 fun_60 = (struct AVariant_NameCtx_Tuple2StringIntBoolTy_Tuple4NameCtx_Tuple2Fun1){.fun = fun_24, .env = env_54};
    struct AVariant_ListNameCtx_Tuple2 tuple_600;
    tuple_600.t0 = variants_3;
    tuple_600.t1 = nameCtx_57;
    struct StringIntBoolTy_Tuple4ListNameCtx_Tuple2 call_835 = stMap_1(fun_60, tuple_600);
    struct StringIntBoolTy_Tuple4List* variants_4 = call_835.t0;
    struct NameCtx_ nameCtx_58 = call_835.t1;
    struct StringStringIntBoolTy_Tuple4ListIntIntTuple2Tuple3 tuple_603;
    tuple_603.t0 = ident_35;
    tuple_603.t1 = variants_4;
    tuple_603.t2 = loc_125;
    struct StringStringIntBoolTy_Tuple4ListIntIntTuple2Tuple3* payload_187 = (struct StringStringIntBoolTy_Tuple4ListIntIntTuple2Tuple3*)malloc(sizeof(struct StringStringIntBoolTy_Tuple4ListIntIntTuple2Tuple3));
    (*(((struct StringStringIntBoolTy_Tuple4ListIntIntTuple2Tuple3*)payload_187))) = tuple_603;
    struct TyDecl_ variant_187 = (struct TyDecl_){.tag = Union_1, .Union_1 = payload_187};
    struct IntTyDecl_IntIntTuple2Tuple3 tuple_602;
    tuple_602.t0 = unionSerial_;
    tuple_602.t1 = variant_187;
    tuple_602.t2 = loc_125;
    struct IntTyDecl_IntIntTuple2Tuple3* payload_188 = (struct IntTyDecl_IntIntTuple2Tuple3*)malloc(sizeof(struct IntTyDecl_IntIntTuple2Tuple3));
    (*(((struct IntTyDecl_IntIntTuple2Tuple3*)payload_188))) = tuple_602;
    struct HExpr_ variant_188 = (struct HExpr_){.tag = TyDecl_, .TyDecl_ = payload_188};
    struct HExpr_NameCtx_Tuple2 tuple_601;
    tuple_601.t0 = variant_188;
    tuple_601.t1 = nameCtx_58;
    match_276 = tuple_601;
    goto end_match_1079;
next_1106:;
    if ((expr_20.tag != Open_1)) goto next_1107;
    struct StringList* path_4 = (*(expr_20.Open_1)).t0;
    struct IntIntTuple2 loc_126 = (*(expr_20.Open_1)).t1;
    struct StringListIntIntTuple2Tuple2 tuple_605;
    tuple_605.t0 = path_4;
    tuple_605.t1 = loc_126;
    struct StringListIntIntTuple2Tuple2* payload_189 = (struct StringListIntIntTuple2Tuple2*)malloc(sizeof(struct StringListIntIntTuple2Tuple2));
    (*(((struct StringListIntIntTuple2Tuple2*)payload_189))) = tuple_605;
    struct HExpr_ variant_189 = (struct HExpr_){.tag = Open_2, .Open_2 = payload_189};
    struct HExpr_NameCtx_Tuple2 tuple_604;
    tuple_604.t0 = variant_189;
    tuple_604.t1 = nameCtx_25;
    match_276 = tuple_604;
    goto end_match_1079;
next_1107:;
    exit(1);
end_match_1079:;
    return match_276;
}

struct HExpr_NameCtx_Tuple2 astToHir_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, struct AExpr_NameCtx_Tuple2 arg_198) {
    struct AExpr_ expr_33 = arg_198.t0;
    struct NameCtx_ nameCtx_59 = arg_198.t1;
    struct AExpr_NameCtx_Tuple2 tuple_606;
    tuple_606.t0 = expr_33;
    tuple_606.t1 = nameCtx_59;
    struct HExpr_NameCtx_Tuple2 call_836 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_606);
    return call_836;
}

struct String litToString_(struct Lit_ lit_5) {
    struct String match_279;
    if ((lit_5.tag != Bool_)) goto next_1115;
    if ((!((*(lit_5.Bool_))))) goto next_1115;
    match_279 = (struct String){.str = "true", .len = 4};
    goto end_match_1114;
next_1115:;
    if ((lit_5.tag != Bool_)) goto next_1116;
    if ((*(lit_5.Bool_))) goto next_1116;
    match_279 = (struct String){.str = "false", .len = 5};
    goto end_match_1114;
next_1116:;
    if ((lit_5.tag != Int_)) goto next_1117;
    int value_6 = (*(lit_5.Int_));
    struct String call_837 = str_of_int(value_6);
    match_279 = call_837;
    goto end_match_1114;
next_1117:;
    if ((lit_5.tag != Char_)) goto next_1118;
    char value_7 = (*(lit_5.Char_));
    struct String match_280;
    int call_838 = charNeedsEscaping_(value_7);
    if ((!(call_838))) goto next_1121;
    struct String call_839 = charEscape_(value_7);
    match_280 = call_839;
    goto end_match_1120;
next_1121:;
    if (call_838) goto next_1122;
    struct String call_840 = str_of_char(value_7);
    match_280 = call_840;
    goto end_match_1120;
next_1122:;
    exit(1);
end_match_1120:;
    match_279 = str_add(str_add((struct String){.str = "\'", .len = 1}, match_280), (struct String){.str = "\'", .len = 1});
    goto end_match_1114;
next_1118:;
    if ((lit_5.tag != Str_)) goto next_1119;
    struct String value_8 = (*(lit_5.Str_));
    struct String call_841 = strEscape_(value_8);
    match_279 = str_add(str_add((struct String){.str = "\"", .len = 1}, call_841), (struct String){.str = "\"", .len = 1});
    goto end_match_1114;
next_1119:;
    exit(1);
end_match_1114:;
    return match_279;
}

struct String tokenToString_(struct Token_ token_12) {
    struct String match_281;
    if ((token_12.tag != Error_)) goto next_1124;
    match_281 = (struct String){.str = "Error", .len = 5};
    goto end_match_1123;
next_1124:;
    if ((token_12.tag != Bool_1)) goto next_1125;
    if ((*(token_12.Bool_1))) goto next_1125;
    match_281 = (struct String){.str = "false", .len = 5};
    goto end_match_1123;
next_1125:;
    if ((token_12.tag != Bool_1)) goto next_1126;
    if ((!((*(token_12.Bool_1))))) goto next_1126;
    match_281 = (struct String){.str = "true", .len = 4};
    goto end_match_1123;
next_1126:;
    if ((token_12.tag != Int_1)) goto next_1127;
    int value_9 = (*(token_12.Int_1));
    struct String call_842 = str_of_int(value_9);
    match_281 = call_842;
    goto end_match_1123;
next_1127:;
    if ((token_12.tag != Char_1)) goto next_1128;
    char value_10 = (*(token_12.Char_1));
    char* payload_190 = (char*)malloc(sizeof(char));
    (*(((char*)payload_190))) = value_10;
    struct Lit_ variant_190 = (struct Lit_){.tag = Char_, .Char_ = payload_190};
    struct String call_843 = litToString_(variant_190);
    match_281 = call_843;
    goto end_match_1123;
next_1128:;
    if ((token_12.tag != Str_1)) goto next_1129;
    struct String value_11 = (*(token_12.Str_1));
    struct String* payload_191 = (struct String*)malloc(sizeof(struct String));
    (*(((struct String*)payload_191))) = value_11;
    struct Lit_ variant_191 = (struct Lit_){.tag = Str_, .Str_ = payload_191};
    struct String call_844 = litToString_(variant_191);
    match_281 = call_844;
    goto end_match_1123;
next_1129:;
    if ((token_12.tag != Ident_)) goto next_1130;
    struct String ident_8 = (*(token_12.Ident_));
    match_281 = ident_8;
    goto end_match_1123;
next_1130:;
    if ((token_12.tag != ParenL_)) goto next_1131;
    match_281 = (struct String){.str = "(", .len = 1};
    goto end_match_1123;
next_1131:;
    if ((token_12.tag != ParenR_)) goto next_1132;
    match_281 = (struct String){.str = ")", .len = 1};
    goto end_match_1123;
next_1132:;
    if ((token_12.tag != BracketL_)) goto next_1133;
    match_281 = (struct String){.str = "[", .len = 1};
    goto end_match_1123;
next_1133:;
    if ((token_12.tag != BracketR_)) goto next_1134;
    match_281 = (struct String){.str = "]", .len = 1};
    goto end_match_1123;
next_1134:;
    if ((token_12.tag != Amp_)) goto next_1135;
    match_281 = (struct String){.str = "&", .len = 1};
    goto end_match_1123;
next_1135:;
    if ((token_12.tag != AmpAmp_)) goto next_1136;
    match_281 = (struct String){.str = "&&", .len = 2};
    goto end_match_1123;
next_1136:;
    if ((token_12.tag != Arrow_)) goto next_1137;
    match_281 = (struct String){.str = "->", .len = 2};
    goto end_match_1123;
next_1137:;
    if ((token_12.tag != Colon_)) goto next_1138;
    match_281 = (struct String){.str = ":", .len = 1};
    goto end_match_1123;
next_1138:;
    if ((token_12.tag != ColonColon_)) goto next_1139;
    match_281 = (struct String){.str = "::", .len = 2};
    goto end_match_1123;
next_1139:;
    if ((token_12.tag != Comma_)) goto next_1140;
    match_281 = (struct String){.str = ",", .len = 1};
    goto end_match_1123;
next_1140:;
    if ((token_12.tag != Dot_)) goto next_1141;
    match_281 = (struct String){.str = ".", .len = 1};
    goto end_match_1123;
next_1141:;
    if ((token_12.tag != DotDot_)) goto next_1142;
    match_281 = (struct String){.str = "..", .len = 2};
    goto end_match_1123;
next_1142:;
    if ((token_12.tag != Eq_)) goto next_1143;
    match_281 = (struct String){.str = "=", .len = 1};
    goto end_match_1123;
next_1143:;
    if ((token_12.tag != Gt_)) goto next_1144;
    match_281 = (struct String){.str = ">", .len = 1};
    goto end_match_1123;
next_1144:;
    if ((token_12.tag != GtEq_)) goto next_1145;
    match_281 = (struct String){.str = ">=", .len = 2};
    goto end_match_1123;
next_1145:;
    if ((token_12.tag != Lt_)) goto next_1146;
    match_281 = (struct String){.str = "<", .len = 1};
    goto end_match_1123;
next_1146:;
    if ((token_12.tag != LtEq_)) goto next_1147;
    match_281 = (struct String){.str = "<=", .len = 2};
    goto end_match_1123;
next_1147:;
    if ((token_12.tag != LtGt_)) goto next_1148;
    match_281 = (struct String){.str = "<>", .len = 2};
    goto end_match_1123;
next_1148:;
    if ((token_12.tag != Minus_)) goto next_1149;
    match_281 = (struct String){.str = "-", .len = 1};
    goto end_match_1123;
next_1149:;
    if ((token_12.tag != Percent_)) goto next_1150;
    match_281 = (struct String){.str = "%", .len = 1};
    goto end_match_1123;
next_1150:;
    if ((token_12.tag != Pipe_)) goto next_1151;
    match_281 = (struct String){.str = "|", .len = 1};
    goto end_match_1123;
next_1151:;
    if ((token_12.tag != PipeGt_)) goto next_1152;
    match_281 = (struct String){.str = "|>", .len = 2};
    goto end_match_1123;
next_1152:;
    if ((token_12.tag != PipePipe_)) goto next_1153;
    match_281 = (struct String){.str = "||", .len = 2};
    goto end_match_1123;
next_1153:;
    if ((token_12.tag != Plus_)) goto next_1154;
    match_281 = (struct String){.str = "+", .len = 1};
    goto end_match_1123;
next_1154:;
    if ((token_12.tag != Semi_)) goto next_1155;
    match_281 = (struct String){.str = ";", .len = 1};
    goto end_match_1123;
next_1155:;
    if ((token_12.tag != Star_)) goto next_1156;
    match_281 = (struct String){.str = "*", .len = 1};
    goto end_match_1123;
next_1156:;
    if ((token_12.tag != Slash_)) goto next_1157;
    match_281 = (struct String){.str = "/", .len = 1};
    goto end_match_1123;
next_1157:;
    if ((token_12.tag != As_)) goto next_1158;
    match_281 = (struct String){.str = "as", .len = 2};
    goto end_match_1123;
next_1158:;
    if ((token_12.tag != Do_)) goto next_1159;
    match_281 = (struct String){.str = "do", .len = 2};
    goto end_match_1123;
next_1159:;
    if ((token_12.tag != Else_)) goto next_1160;
    match_281 = (struct String){.str = "else", .len = 4};
    goto end_match_1123;
next_1160:;
    if ((token_12.tag != Fun_)) goto next_1161;
    match_281 = (struct String){.str = "fun", .len = 3};
    goto end_match_1123;
next_1161:;
    if ((token_12.tag != If_)) goto next_1162;
    match_281 = (struct String){.str = "if", .len = 2};
    goto end_match_1123;
next_1162:;
    if ((token_12.tag != In_)) goto next_1163;
    match_281 = (struct String){.str = "in", .len = 2};
    goto end_match_1123;
next_1163:;
    if ((token_12.tag != Internal_)) goto next_1164;
    match_281 = (struct String){.str = "internal", .len = 8};
    goto end_match_1123;
next_1164:;
    if ((token_12.tag != Let_)) goto next_1165;
    match_281 = (struct String){.str = "let", .len = 3};
    goto end_match_1123;
next_1165:;
    if ((token_12.tag != Match_)) goto next_1166;
    match_281 = (struct String){.str = "match", .len = 5};
    goto end_match_1123;
next_1166:;
    if ((token_12.tag != Module_)) goto next_1167;
    match_281 = (struct String){.str = "module", .len = 6};
    goto end_match_1123;
next_1167:;
    if ((token_12.tag != Namespace_)) goto next_1168;
    match_281 = (struct String){.str = "namespace", .len = 9};
    goto end_match_1123;
next_1168:;
    if ((token_12.tag != Of_)) goto next_1169;
    match_281 = (struct String){.str = "of", .len = 2};
    goto end_match_1123;
next_1169:;
    if ((token_12.tag != Open_)) goto next_1170;
    match_281 = (struct String){.str = "open", .len = 4};
    goto end_match_1123;
next_1170:;
    if ((token_12.tag != Private_)) goto next_1171;
    match_281 = (struct String){.str = "private", .len = 7};
    goto end_match_1123;
next_1171:;
    if ((token_12.tag != Public_)) goto next_1172;
    match_281 = (struct String){.str = "public", .len = 6};
    goto end_match_1123;
next_1172:;
    if ((token_12.tag != Rec_)) goto next_1173;
    match_281 = (struct String){.str = "rec", .len = 3};
    goto end_match_1123;
next_1173:;
    if ((token_12.tag != Then_)) goto next_1174;
    match_281 = (struct String){.str = "then", .len = 4};
    goto end_match_1123;
next_1174:;
    if ((token_12.tag != Type_)) goto next_1175;
    match_281 = (struct String){.str = "type", .len = 4};
    goto end_match_1123;
next_1175:;
    if ((token_12.tag != When_)) goto next_1176;
    match_281 = (struct String){.str = "when", .len = 4};
    goto end_match_1123;
next_1176:;
    if ((token_12.tag != With_)) goto next_1177;
    match_281 = (struct String){.str = "with", .len = 4};
    goto end_match_1123;
next_1177:;
end_match_1123:;
    return match_281;
}

struct DumpTree_ fun_25(void* env_19, struct ATy_ arg_74) {
    struct DumpTree_ call_845 = atDump_(arg_74);
    return call_845;
}

struct DumpTree_ fun_26(void* env_20, struct ATy_ arg_75) {
    struct DumpTree_ call_846 = atDump_(arg_75);
    return call_846;
}

struct DumpTree_ fun_27(void* env_21, struct ATy_ arg_76) {
    struct DumpTree_ call_847 = atDump_(arg_76);
    return call_847;
}

struct DumpTree_ atDump_(struct ATy_ ty_43) {
    struct DumpTree_ match_282;
    if ((ty_43.tag != Missing_)) goto next_1179;
    struct IntIntTuple2 loc_23 = (*(ty_43.Missing_));
    struct DumpTree_ call_848 = dumpTreeFromError_((struct String){.str = "missing", .len = 7}, loc_23);
    match_282 = call_848;
    goto end_match_1178;
next_1179:;
    if ((ty_43.tag != App_1)) goto next_1180;
    struct String ident_9 = (*(ty_43.App_1)).t0;
    struct ATy_List* tys_6 = (*(ty_43.App_1)).t1;
    void* box_16 = (void*)malloc(sizeof(int));
    (*(((int*)box_16))) = 0;
    void* env_55 = box_16;
    struct ATy_DumpTree_Fun1 fun_61 = (struct ATy_DumpTree_Fun1){.fun = fun_25, .env = env_55};
    struct DumpTree_List* call_849 = listMap_7(fun_61, tys_6);
    struct DumpTree_ call_850 = dumpTreeNew_(ident_9, call_849);
    match_282 = call_850;
    goto end_match_1178;
next_1180:;
    if ((ty_43.tag != Suffix_)) goto next_1181;
    struct ATy_ lTy_2 = (*(ty_43.Suffix_)).t0;
    struct String ident_10 = (*(ty_43.Suffix_)).t1;
    struct DumpTree_ call_851 = atDump_(lTy_2);
    struct DumpTree_List* list_84 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_84->head = call_851;
    list_84->tail = NULL;
    struct DumpTree_ call_852 = dumpTreeNew_(ident_10, list_84);
    match_282 = call_852;
    goto end_match_1178;
next_1181:;
    if ((ty_43.tag != Tuple_)) goto next_1182;
    struct ATy_List* itemTys_ = (*(ty_43.Tuple_)).t0;
    void* box_17 = (void*)malloc(sizeof(int));
    (*(((int*)box_17))) = 0;
    void* env_56 = box_17;
    struct ATy_DumpTree_Fun1 fun_62 = (struct ATy_DumpTree_Fun1){.fun = fun_26, .env = env_56};
    struct DumpTree_List* call_853 = listMap_7(fun_62, itemTys_);
    struct DumpTree_ call_854 = dumpTreeNew_((struct String){.str = "tuple", .len = 5}, call_853);
    match_282 = call_854;
    goto end_match_1178;
next_1182:;
    if ((ty_43.tag != Fun_1)) goto next_1183;
    struct ATy_ sTy_ = (*(ty_43.Fun_1)).t0;
    struct ATy_ tTy_ = (*(ty_43.Fun_1)).t1;
    void* box_18 = (void*)malloc(sizeof(int));
    (*(((int*)box_18))) = 0;
    void* env_57 = box_18;
    struct ATy_DumpTree_Fun1 fun_63 = (struct ATy_DumpTree_Fun1){.fun = fun_27, .env = env_57};
    struct ATy_List* list_86 = (struct ATy_List*)malloc(sizeof(struct ATy_List));
    list_86->head = tTy_;
    list_86->tail = NULL;
    struct ATy_List* list_85 = (struct ATy_List*)malloc(sizeof(struct ATy_List));
    list_85->head = sTy_;
    list_85->tail = list_86;
    struct DumpTree_List* call_855 = listMap_7(fun_63, list_85);
    struct DumpTree_ call_856 = dumpTreeNew_((struct String){.str = "fun", .len = 3}, call_855);
    match_282 = call_856;
    goto end_match_1178;
next_1183:;
    exit(1);
end_match_1178:;
    return match_282;
}

struct DumpTree_ fun_28(void* env_22, struct APat_ arg_77) {
    struct DumpTree_ call_857 = apDump_(arg_77);
    return call_857;
}

struct DumpTree_ fun_29(void* env_23, struct APat_ arg_78) {
    struct DumpTree_ call_858 = apDump_(arg_78);
    return call_858;
}

struct DumpTree_ fun_30(void* env_24, struct APat_ arg_79) {
    struct DumpTree_ call_859 = apDump_(arg_79);
    return call_859;
}

struct DumpTree_ fun_31(void* env_25, struct APat_ arg_80) {
    struct DumpTree_ call_860 = apDump_(arg_80);
    return call_860;
}

struct DumpTree_ apDump_(struct APat_ pat_10) {
    struct DumpTree_ match_283;
    if ((pat_10.tag != Missing_1)) goto next_1185;
    struct IntIntTuple2 loc_24 = (*(pat_10.Missing_1));
    struct DumpTree_ call_861 = dumpTreeFromError_((struct String){.str = "missing", .len = 7}, loc_24);
    match_283 = call_861;
    goto end_match_1184;
next_1185:;
    if ((pat_10.tag != Lit_)) goto next_1186;
    struct Lit_ lit_6 = (*(pat_10.Lit_)).t0;
    struct String call_862 = litToString_(lit_6);
    struct DumpTree_ call_863 = dumpTreeNewLeaf_(call_862);
    match_283 = call_863;
    goto end_match_1184;
next_1186:;
    if ((pat_10.tag != Ident_1)) goto next_1187;
    struct String ident_11 = (*(pat_10.Ident_1)).t0;
    struct DumpTree_ call_864 = dumpTreeNewLeaf_(ident_11);
    match_283 = call_864;
    goto end_match_1184;
next_1187:;
    if ((pat_10.tag != ListLit_)) goto next_1188;
    struct APat_List* pats_ = (*(pat_10.ListLit_)).t0;
    void* box_19 = (void*)malloc(sizeof(int));
    (*(((int*)box_19))) = 0;
    void* env_58 = box_19;
    struct APat_DumpTree_Fun1 fun_64 = (struct APat_DumpTree_Fun1){.fun = fun_28, .env = env_58};
    struct DumpTree_List* call_865 = listMap_5(fun_64, pats_);
    struct DumpTree_ call_866 = dumpTreeNew_((struct String){.str = "list", .len = 4}, call_865);
    match_283 = call_866;
    goto end_match_1184;
next_1188:;
    if ((pat_10.tag != Nav_)) goto next_1189;
    struct APat_ l_11 = (*(pat_10.Nav_)).t0;
    struct String r_24 = (*(pat_10.Nav_)).t1;
    struct DumpTree_ call_867 = apDump_(l_11);
    struct DumpTree_List* list_87 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_87->head = call_867;
    list_87->tail = NULL;
    struct DumpTree_ call_868 = dumpTreeNew_(str_add((struct String){.str = ".", .len = 1}, r_24), list_87);
    match_283 = call_868;
    goto end_match_1184;
next_1189:;
    if ((pat_10.tag != Call_)) goto next_1190;
    struct APat_ calleePat_ = (*(pat_10.Call_)).t0;
    struct APat_List* argPats_ = (*(pat_10.Call_)).t1;
    struct DumpTree_ call_869 = apDump_(calleePat_);
    void* box_20 = (void*)malloc(sizeof(int));
    (*(((int*)box_20))) = 0;
    void* env_59 = box_20;
    struct APat_DumpTree_Fun1 fun_65 = (struct APat_DumpTree_Fun1){.fun = fun_29, .env = env_59};
    struct DumpTree_List* call_870 = listMap_5(fun_65, argPats_);
    struct DumpTree_List* list_88 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_88->head = call_869;
    list_88->tail = call_870;
    struct DumpTree_ call_871 = dumpTreeNew_((struct String){.str = "call", .len = 4}, list_88);
    match_283 = call_871;
    goto end_match_1184;
next_1190:;
    if ((pat_10.tag != Cons_2)) goto next_1191;
    struct APat_ head_1 = (*(pat_10.Cons_2)).t0;
    struct APat_ tail_1 = (*(pat_10.Cons_2)).t1;
    struct DumpTree_ call_872 = apDump_(tail_1);
    struct DumpTree_ call_873 = apDump_(head_1);
    struct DumpTree_List* list_89 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_89->head = call_873;
    list_89->tail = NULL;
    struct DumpTree_ call_874 = dumpTreeNew_((struct String){.str = "cons", .len = 4}, list_89);
    struct DumpTree_ call_875 = dumpTreeAttachNext_(call_872, call_874);
    match_283 = call_875;
    goto end_match_1184;
next_1191:;
    if ((pat_10.tag != TupleLit_)) goto next_1192;
    struct APat_List* pats_1 = (*(pat_10.TupleLit_)).t0;
    void* box_21 = (void*)malloc(sizeof(int));
    (*(((int*)box_21))) = 0;
    void* env_60 = box_21;
    struct APat_DumpTree_Fun1 fun_66 = (struct APat_DumpTree_Fun1){.fun = fun_30, .env = env_60};
    struct DumpTree_List* call_876 = listMap_5(fun_66, pats_1);
    struct DumpTree_ call_877 = dumpTreeNew_((struct String){.str = "tuple", .len = 5}, call_876);
    match_283 = call_877;
    goto end_match_1184;
next_1192:;
    if ((pat_10.tag != As_1)) goto next_1193;
    struct APat_ pat_11 = (*(pat_10.As_1)).t0;
    struct String ident_12 = (*(pat_10.As_1)).t1;
    struct DumpTree_ call_878 = apDump_(pat_11);
    struct DumpTree_List* list_90 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_90->head = call_878;
    list_90->tail = NULL;
    struct DumpTree_ call_879 = dumpTreeNew_(str_add((struct String){.str = "as ", .len = 3}, ident_12), list_90);
    match_283 = call_879;
    goto end_match_1184;
next_1193:;
    if ((pat_10.tag != Anno_)) goto next_1194;
    struct APat_ pat_12 = (*(pat_10.Anno_)).t0;
    struct ATy_ ty_44 = (*(pat_10.Anno_)).t1;
    struct DumpTree_ call_880 = apDump_(pat_12);
    struct DumpTree_ call_881 = atDump_(ty_44);
    struct DumpTree_List* list_92 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_92->head = call_881;
    list_92->tail = NULL;
    struct DumpTree_List* list_91 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_91->head = call_880;
    list_91->tail = list_92;
    struct DumpTree_ call_882 = dumpTreeNew_((struct String){.str = "anno", .len = 4}, list_91);
    match_283 = call_882;
    goto end_match_1184;
next_1194:;
    if ((pat_10.tag != Or_2)) goto next_1195;
    struct APat_ l_12 = (*(pat_10.Or_2)).t0;
    struct APat_ r_25 = (*(pat_10.Or_2)).t1;
    struct DumpTree_ call_883 = apDump_(r_25);
    struct DumpTree_ call_884 = apDump_(l_12);
    struct DumpTree_List* list_93 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_93->head = call_884;
    list_93->tail = NULL;
    struct DumpTree_ call_885 = dumpTreeNew_((struct String){.str = "or", .len = 2}, list_93);
    struct DumpTree_ call_886 = dumpTreeAttachNext_(call_883, call_885);
    match_283 = call_886;
    goto end_match_1184;
next_1195:;
    if ((pat_10.tag != Fun_2)) goto next_1196;
    struct String callee_3 = (*(pat_10.Fun_2)).t0;
    struct APat_List* args_5 = (*(pat_10.Fun_2)).t1;
    struct DumpTree_ call_887 = dumpTreeNewLeaf_(callee_3);
    void* box_22 = (void*)malloc(sizeof(int));
    (*(((int*)box_22))) = 0;
    void* env_61 = box_22;
    struct APat_DumpTree_Fun1 fun_67 = (struct APat_DumpTree_Fun1){.fun = fun_31, .env = env_61};
    struct DumpTree_List* call_888 = listMap_5(fun_67, args_5);
    struct DumpTree_List* list_94 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_94->head = call_887;
    list_94->tail = call_888;
    struct DumpTree_ call_889 = dumpTreeNew_((struct String){.str = "fun", .len = 3}, list_94);
    match_283 = call_889;
    goto end_match_1184;
next_1196:;
    exit(1);
end_match_1184:;
    return match_283;
}

struct DumpTree_ fun_32(void* env_26, struct AExpr_ arg_81) {
    struct DumpTree_ call_890 = axDump_(arg_81);
    return call_890;
}

struct DumpTree_ dumpArm_(struct AArm_ arg_199) {
    struct APat_ pat_13 = (*(arg_199.AArm_)).t0;
    struct AExpr_ guard_1 = (*(arg_199.AArm_)).t1;
    struct AExpr_ body_3 = (*(arg_199.AArm_)).t2;
    struct DumpTree_ call_891 = axDump_(body_3);
    struct DumpTree_ call_892 = apDump_(pat_13);
    struct DumpTree_ call_893 = axDump_(guard_1);
    struct DumpTree_List* list_96 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_96->head = call_893;
    list_96->tail = NULL;
    struct DumpTree_List* list_95 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_95->head = call_892;
    list_95->tail = list_96;
    struct DumpTree_ call_894 = dumpTreeNew_((struct String){.str = "arm", .len = 3}, list_95);
    struct DumpTree_ call_895 = dumpTreeAttachNext_(call_891, call_894);
    return call_895;
}

struct DumpTree_ fun_33(void* env_27, struct AArm_ arg_82) {
    struct DumpTree_ call_896 = dumpArm_(arg_82);
    return call_896;
}

struct DumpTree_ fun_34(void* env_28, struct APat_ arg_83) {
    struct DumpTree_ call_897 = apDump_(arg_83);
    return call_897;
}

struct DumpTree_ fun_35(void* env_29, struct AExpr_ arg_84) {
    struct DumpTree_ call_898 = axDump_(arg_84);
    return call_898;
}

struct DumpTree_ fun_36(void* env_30, struct AExpr_ arg_85) {
    struct DumpTree_ call_899 = axDump_(arg_85);
    return call_899;
}

struct DumpTree_ fun_37(void* env_31, struct AExpr_ arg_86) {
    struct DumpTree_ call_900 = axDump_(arg_86);
    return call_900;
}

struct DumpTree_ dumpVariant_(struct AVariant_ arg_200) {
    struct String ident_16 = (*(arg_200.AVariant_)).t0;
    struct DumpTree_ call_901 = dumpTreeNewLeaf_(ident_16);
    return call_901;
}

struct DumpTree_ fun_38(void* env_32, struct AVariant_ arg_87) {
    struct DumpTree_ call_902 = dumpVariant_(arg_87);
    return call_902;
}

struct DumpTree_ fun_39(void* env_33, struct String arg_88) {
    struct DumpTree_ call_903 = dumpTreeNewLeaf_(arg_88);
    return call_903;
}

struct DumpTree_ axDump_(struct AExpr_ expr_7) {
    struct DumpTree_ match_284;
    if ((expr_7.tag != Missing_2)) goto next_1198;
    struct IntIntTuple2 loc_25 = (*(expr_7.Missing_2));
    struct DumpTree_ call_904 = dumpTreeFromError_((struct String){.str = "missing", .len = 7}, loc_25);
    match_284 = call_904;
    goto end_match_1197;
next_1198:;
    if ((expr_7.tag != Lit_1)) goto next_1199;
    struct Lit_ lit_7 = (*(expr_7.Lit_1)).t0;
    struct String call_905 = litToString_(lit_7);
    struct DumpTree_ call_906 = dumpTreeNewLeaf_(call_905);
    match_284 = call_906;
    goto end_match_1197;
next_1199:;
    if ((expr_7.tag != Ident_2)) goto next_1200;
    struct String ident_13 = (*(expr_7.Ident_2)).t0;
    struct DumpTree_ call_907 = dumpTreeNewLeaf_(ident_13);
    match_284 = call_907;
    goto end_match_1197;
next_1200:;
    if ((expr_7.tag != ListLit_1)) goto next_1201;
    struct AExpr_List* items_2 = (*(expr_7.ListLit_1)).t0;
    void* box_23 = (void*)malloc(sizeof(int));
    (*(((int*)box_23))) = 0;
    void* env_62 = box_23;
    struct AExpr_DumpTree_Fun1 fun_68 = (struct AExpr_DumpTree_Fun1){.fun = fun_32, .env = env_62};
    struct DumpTree_List* call_908 = listMap_4(fun_68, items_2);
    struct DumpTree_ call_909 = dumpTreeNew_((struct String){.str = "list", .len = 4}, call_908);
    match_284 = call_909;
    goto end_match_1197;
next_1201:;
    if ((expr_7.tag != If_1)) goto next_1202;
    struct AExpr_ cond_ = (*(expr_7.If_1)).t0;
    struct AExpr_ body_2 = (*(expr_7.If_1)).t1;
    struct AExpr_ alt_ = (*(expr_7.If_1)).t2;
    struct DumpTree_ call_910 = axDump_(cond_);
    struct DumpTree_ call_911 = axDump_(body_2);
    struct DumpTree_ call_912 = axDump_(alt_);
    struct DumpTree_List* list_99 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_99->head = call_912;
    list_99->tail = NULL;
    struct DumpTree_List* list_98 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_98->head = call_911;
    list_98->tail = list_99;
    struct DumpTree_List* list_97 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_97->head = call_910;
    list_97->tail = list_98;
    struct DumpTree_ call_913 = dumpTreeNew_((struct String){.str = "if", .len = 2}, list_97);
    match_284 = call_913;
    goto end_match_1197;
next_1202:;
    if ((expr_7.tag != Match_1)) goto next_1203;
    struct AExpr_ target_1 = (*(expr_7.Match_1)).t0;
    struct AArm_List* arms_2 = (*(expr_7.Match_1)).t1;
    struct DumpTree_ call_914 = axDump_(target_1);
    void* box_24 = (void*)malloc(sizeof(int));
    (*(((int*)box_24))) = 0;
    void* env_63 = box_24;
    struct AArm_DumpTree_Fun1 fun_69 = (struct AArm_DumpTree_Fun1){.fun = fun_33, .env = env_63};
    struct DumpTree_List* call_915 = listMap_6(fun_69, arms_2);
    struct DumpTree_List* list_100 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_100->head = call_914;
    list_100->tail = call_915;
    struct DumpTree_ call_916 = dumpTreeNew_((struct String){.str = "match", .len = 5}, list_100);
    match_284 = call_916;
    goto end_match_1197;
next_1203:;
    if ((expr_7.tag != Fun_3)) goto next_1204;
    struct APat_List* pats_2 = (*(expr_7.Fun_3)).t0;
    struct AExpr_ body_4 = (*(expr_7.Fun_3)).t1;
    struct DumpTree_ call_917 = axDump_(body_4);
    void* box_25 = (void*)malloc(sizeof(int));
    (*(((int*)box_25))) = 0;
    void* env_64 = box_25;
    struct APat_DumpTree_Fun1 fun_70 = (struct APat_DumpTree_Fun1){.fun = fun_34, .env = env_64};
    struct DumpTree_List* call_918 = listMap_5(fun_70, pats_2);
    struct DumpTree_ call_919 = dumpTreeNew_((struct String){.str = "fun", .len = 3}, call_918);
    struct DumpTree_ call_920 = dumpTreeAttachNext_(call_917, call_919);
    match_284 = call_920;
    goto end_match_1197;
next_1204:;
    if ((expr_7.tag != Nav_1)) goto next_1205;
    struct AExpr_ l_13 = (*(expr_7.Nav_1)).t0;
    struct String r_26 = (*(expr_7.Nav_1)).t1;
    struct DumpTree_ call_921 = axDump_(l_13);
    struct DumpTree_List* list_101 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_101->head = call_921;
    list_101->tail = NULL;
    struct DumpTree_ call_922 = dumpTreeNew_(str_add((struct String){.str = ".", .len = 1}, r_26), list_101);
    match_284 = call_922;
    goto end_match_1197;
next_1205:;
    if ((expr_7.tag != Index_)) goto next_1206;
    struct AExpr_ l_14 = (*(expr_7.Index_)).t0;
    struct AExpr_ r_27 = (*(expr_7.Index_)).t1;
    struct DumpTree_ call_923 = axDump_(l_14);
    struct DumpTree_List* list_102 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_102->head = call_923;
    list_102->tail = NULL;
    struct DumpTree_ call_924 = dumpTreeNew_((struct String){.str = "index", .len = 5}, list_102);
    match_284 = call_924;
    goto end_match_1197;
next_1206:;
    if ((expr_7.tag != Uni_)) goto next_1207;
    if (((*(expr_7.Uni_)).t0.tag != Neg_)) goto next_1207;
    struct AExpr_ arg_1 = (*(expr_7.Uni_)).t1;
    struct DumpTree_ call_925 = axDump_(arg_1);
    struct DumpTree_List* list_103 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_103->head = call_925;
    list_103->tail = NULL;
    struct DumpTree_ call_926 = dumpTreeNew_((struct String){.str = "-", .len = 1}, list_103);
    match_284 = call_926;
    goto end_match_1197;
next_1207:;
    if ((expr_7.tag != Bin_)) goto next_1208;
    struct AExpr_ l_15 = (*(expr_7.Bin_)).t1;
    struct AExpr_ r_28 = (*(expr_7.Bin_)).t2;
    struct DumpTree_ call_927 = axDump_(l_15);
    struct DumpTree_ call_928 = axDump_(r_28);
    struct DumpTree_List* list_105 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_105->head = call_928;
    list_105->tail = NULL;
    struct DumpTree_List* list_104 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_104->head = call_927;
    list_104->tail = list_105;
    struct DumpTree_ call_929 = dumpTreeNew_((struct String){.str = "bin", .len = 3}, list_104);
    match_284 = call_929;
    goto end_match_1197;
next_1208:;
    if ((expr_7.tag != Range_)) goto next_1209;
    struct AExpr_List* items_3 = (*(expr_7.Range_)).t0;
    void* box_26 = (void*)malloc(sizeof(int));
    (*(((int*)box_26))) = 0;
    void* env_65 = box_26;
    struct AExpr_DumpTree_Fun1 fun_71 = (struct AExpr_DumpTree_Fun1){.fun = fun_35, .env = env_65};
    struct DumpTree_List* call_930 = listMap_4(fun_71, items_3);
    struct DumpTree_ call_931 = dumpTreeNew_((struct String){.str = "range", .len = 5}, call_930);
    match_284 = call_931;
    goto end_match_1197;
next_1209:;
    if ((expr_7.tag != TupleLit_1)) goto next_1210;
    struct AExpr_List* items_4 = (*(expr_7.TupleLit_1)).t0;
    void* box_27 = (void*)malloc(sizeof(int));
    (*(((int*)box_27))) = 0;
    void* env_66 = box_27;
    struct AExpr_DumpTree_Fun1 fun_72 = (struct AExpr_DumpTree_Fun1){.fun = fun_36, .env = env_66};
    struct DumpTree_List* call_932 = listMap_4(fun_72, items_4);
    struct DumpTree_ call_933 = dumpTreeNew_((struct String){.str = "tuple", .len = 5}, call_932);
    match_284 = call_933;
    goto end_match_1197;
next_1210:;
    if ((expr_7.tag != Anno_1)) goto next_1211;
    struct AExpr_ body_5 = (*(expr_7.Anno_1)).t0;
    struct ATy_ ty_45 = (*(expr_7.Anno_1)).t1;
    struct DumpTree_ call_934 = axDump_(body_5);
    struct DumpTree_ call_935 = atDump_(ty_45);
    struct DumpTree_List* list_107 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_107->head = call_935;
    list_107->tail = NULL;
    struct DumpTree_List* list_106 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_106->head = call_934;
    list_106->tail = list_107;
    struct DumpTree_ call_936 = dumpTreeNew_((struct String){.str = "anno", .len = 4}, list_106);
    match_284 = call_936;
    goto end_match_1197;
next_1211:;
    if ((expr_7.tag != Semi_1)) goto next_1212;
    struct AExpr_List* exprs_ = (*(expr_7.Semi_1)).t0;
    void* box_28 = (void*)malloc(sizeof(int));
    (*(((int*)box_28))) = 0;
    void* env_67 = box_28;
    struct AExpr_DumpTree_Fun1 fun_73 = (struct AExpr_DumpTree_Fun1){.fun = fun_37, .env = env_67};
    struct DumpTree_List* call_937 = listMap_4(fun_73, exprs_);
    struct DumpTree_ call_938 = dumpTreeNew_((struct String){.str = "semi", .len = 4}, call_937);
    match_284 = call_938;
    goto end_match_1197;
next_1212:;
    if ((expr_7.tag != Let_1)) goto next_1213;
    struct APat_ pat_14 = (*(expr_7.Let_1)).t0;
    struct AExpr_ body_6 = (*(expr_7.Let_1)).t1;
    struct AExpr_ next_8 = (*(expr_7.Let_1)).t2;
    struct DumpTree_ call_939 = axDump_(next_8);
    struct DumpTree_ call_940 = apDump_(pat_14);
    struct DumpTree_ call_941 = axDump_(body_6);
    struct DumpTree_List* list_109 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_109->head = call_941;
    list_109->tail = NULL;
    struct DumpTree_List* list_108 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_108->head = call_940;
    list_108->tail = list_109;
    struct DumpTree_ call_942 = dumpTreeNew_((struct String){.str = "let", .len = 3}, list_108);
    struct DumpTree_ call_943 = dumpTreeAttachNext_(call_939, call_942);
    match_284 = call_943;
    goto end_match_1197;
next_1213:;
    if ((expr_7.tag != TySynonym_)) goto next_1214;
    struct String ident_14 = (*(expr_7.TySynonym_)).t0;
    struct ATy_ ty_46 = (*(expr_7.TySynonym_)).t1;
    struct DumpTree_ call_944 = atDump_(ty_46);
    struct DumpTree_ call_945 = dumpTreeNewLeaf_(ident_14);
    struct DumpTree_List* list_110 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_110->head = call_945;
    list_110->tail = NULL;
    struct DumpTree_ call_946 = dumpTreeNew_((struct String){.str = "synonym", .len = 7}, list_110);
    struct DumpTree_ call_947 = dumpTreeAttachNext_(call_944, call_946);
    match_284 = call_947;
    goto end_match_1197;
next_1214:;
    if ((expr_7.tag != TyUnion_)) goto next_1215;
    struct String ident_15 = (*(expr_7.TyUnion_)).t0;
    struct AVariant_List* variants_ = (*(expr_7.TyUnion_)).t1;
    struct DumpTree_ call_948 = dumpTreeNewLeaf_(ident_15);
    void* box_29 = (void*)malloc(sizeof(int));
    (*(((int*)box_29))) = 0;
    void* env_68 = box_29;
    struct AVariant_DumpTree_Fun1 fun_74 = (struct AVariant_DumpTree_Fun1){.fun = fun_38, .env = env_68};
    struct DumpTree_List* call_949 = listMap_3(fun_74, variants_);
    struct DumpTree_List* list_111 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_111->head = call_948;
    list_111->tail = call_949;
    struct DumpTree_ call_950 = dumpTreeNew_((struct String){.str = "union", .len = 5}, list_111);
    match_284 = call_950;
    goto end_match_1197;
next_1215:;
    if ((expr_7.tag != Open_1)) goto next_1216;
    struct StringList* path_1 = (*(expr_7.Open_1)).t0;
    void* box_30 = (void*)malloc(sizeof(int));
    (*(((int*)box_30))) = 0;
    void* env_69 = box_30;
    struct StringDumpTree_Fun1 fun_75 = (struct StringDumpTree_Fun1){.fun = fun_39, .env = env_69};
    struct DumpTree_List* call_951 = listMap_1(fun_75, path_1);
    struct DumpTree_ call_952 = dumpTreeNew_((struct String){.str = "open", .len = 4}, call_951);
    match_284 = call_952;
    goto end_match_1197;
next_1216:;
    exit(1);
end_match_1197:;
    return match_284;
}

struct String findIdent_(struct NameCtx_ nameCtx_, int serial_9) {
    struct String call_953 = nameCtxFind_(serial_9, nameCtx_);
    return call_953;
}

struct NameCtx_Tuple1 {
    struct NameCtx_ t0;
};

struct DumpTree_ fun_40(void* env_34, struct HExpr_ arg_89) {
    struct NameCtx_ arg_90 = (*(((struct NameCtx_Tuple1*)env_34))).t0;
    struct DumpTree_ call_954 = hxDump_(arg_90, arg_89);
    return call_954;
}

struct DumpTree_ fun_41(void* env_35, struct String arg_91) {
    struct DumpTree_ call_955 = dumpTreeNewLeaf_(arg_91);
    return call_955;
}

struct DumpTree_ hxDump_(struct NameCtx_ nameCtx_, struct HExpr_ expr_8) {
    struct DumpTree_ match_285;
    if ((expr_8.tag != Lit_3)) goto next_1218;
    struct Lit_ lit_8 = (*(expr_8.Lit_3)).t0;
    struct String call_956 = litToString_(lit_8);
    struct DumpTree_ call_957 = dumpTreeNewLeaf_(call_956);
    match_285 = call_957;
    goto end_match_1217;
next_1218:;
    if ((expr_8.tag != Prim_)) goto next_1219;
    struct DumpTree_ call_958 = dumpTreeNewLeaf_((struct String){.str = "prim", .len = 4});
    match_285 = call_958;
    goto end_match_1217;
next_1219:;
    if ((expr_8.tag != Ref_2)) goto next_1220;
    int serial_10 = (*(expr_8.Ref_2)).t0;
    struct String call_959 = findIdent_(nameCtx_, serial_10);
    struct DumpTree_ call_960 = dumpTreeNewLeaf_(call_959);
    match_285 = call_960;
    goto end_match_1217;
next_1220:;
    if ((expr_8.tag != Match_2)) goto next_1221;
    struct HExpr_ target_2 = (*(expr_8.Match_2)).t0;
    struct HPat_HExpr_HExpr_Tuple3List* _arms_ = (*(expr_8.Match_2)).t1;
    struct Ty_ _ty_ = (*(expr_8.Match_2)).t2;
    struct IntIntTuple2 _loc_ = (*(expr_8.Match_2)).t3;
    struct DumpTree_ call_961 = hxDump_(nameCtx_, target_2);
    struct DumpTree_List* list_112 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_112->head = call_961;
    list_112->tail = NULL;
    struct DumpTree_ call_962 = dumpTreeNew_((struct String){.str = "match", .len = 5}, list_112);
    match_285 = call_962;
    goto end_match_1217;
next_1221:;
    if ((expr_8.tag != Nav_3)) goto next_1222;
    struct HExpr_ l_16 = (*(expr_8.Nav_3)).t0;
    struct String r_29 = (*(expr_8.Nav_3)).t1;
    struct Ty_ _ty_1 = (*(expr_8.Nav_3)).t2;
    struct IntIntTuple2 _loc_1 = (*(expr_8.Nav_3)).t3;
    struct DumpTree_ call_963 = hxDump_(nameCtx_, l_16);
    struct DumpTree_List* list_113 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_113->head = call_963;
    list_113->tail = NULL;
    struct DumpTree_ call_964 = dumpTreeNew_(str_add((struct String){.str = ".", .len = 1}, r_29), list_113);
    match_285 = call_964;
    goto end_match_1217;
next_1222:;
    if ((expr_8.tag != Inf_)) goto next_1223;
    struct HExpr_List* items_5 = (*(expr_8.Inf_)).t1;
    struct Ty_ _ty_2 = (*(expr_8.Inf_)).t2;
    struct IntIntTuple2 _loc_2 = (*(expr_8.Inf_)).t3;
    struct NameCtx_Tuple1 tuple_607;
    tuple_607.t0 = nameCtx_;
    void* box_31 = (void*)malloc(sizeof(struct NameCtx_Tuple1));
    (*(((struct NameCtx_Tuple1*)box_31))) = tuple_607;
    void* env_70 = box_31;
    struct HExpr_DumpTree_Fun1 fun_76 = (struct HExpr_DumpTree_Fun1){.fun = fun_40, .env = env_70};
    struct DumpTree_List* call_965 = listMap_2(fun_76, items_5);
    struct DumpTree_ call_966 = dumpTreeNew_((struct String){.str = "inf", .len = 3}, call_965);
    match_285 = call_966;
    goto end_match_1217;
next_1223:;
    if ((expr_8.tag != Let_2)) goto next_1224;
    struct HPat_ _pat_ = (*(expr_8.Let_2)).t0;
    struct HExpr_ body_7 = (*(expr_8.Let_2)).t1;
    struct HExpr_ next_9 = (*(expr_8.Let_2)).t2;
    struct Ty_ _ty_3 = (*(expr_8.Let_2)).t3;
    struct IntIntTuple2 _loc_3 = (*(expr_8.Let_2)).t4;
    struct DumpTree_ call_967 = hxDump_(nameCtx_, next_9);
    struct DumpTree_ call_968 = hxDump_(nameCtx_, body_7);
    struct DumpTree_List* list_114 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_114->head = call_968;
    list_114->tail = NULL;
    struct DumpTree_ call_969 = dumpTreeNew_((struct String){.str = "let-val", .len = 7}, list_114);
    struct DumpTree_ call_970 = dumpTreeAttachNext_(call_967, call_969);
    match_285 = call_970;
    goto end_match_1217;
next_1224:;
    if ((expr_8.tag != LetFun_1)) goto next_1225;
    int callee_4 = (*(expr_8.LetFun_1)).t0;
    struct HPat_List* _args_ = (*(expr_8.LetFun_1)).t2;
    struct HExpr_ body_8 = (*(expr_8.LetFun_1)).t3;
    struct HExpr_ next_10 = (*(expr_8.LetFun_1)).t4;
    struct Ty_ _ty_4 = (*(expr_8.LetFun_1)).t5;
    struct IntIntTuple2 _loc_4 = (*(expr_8.LetFun_1)).t6;
    struct DumpTree_ call_971 = hxDump_(nameCtx_, next_10);
    struct String call_972 = findIdent_(nameCtx_, callee_4);
    struct DumpTree_ call_973 = dumpTreeNewLeaf_(call_972);
    struct DumpTree_ call_974 = hxDump_(nameCtx_, body_8);
    struct DumpTree_List* list_116 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_116->head = call_974;
    list_116->tail = NULL;
    struct DumpTree_List* list_115 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_115->head = call_973;
    list_115->tail = list_116;
    struct DumpTree_ call_975 = dumpTreeNew_((struct String){.str = "let-fun", .len = 7}, list_115);
    struct DumpTree_ call_976 = dumpTreeAttachNext_(call_971, call_975);
    match_285 = call_976;
    goto end_match_1217;
next_1225:;
    if ((expr_8.tag != TyDecl_)) goto next_1226;
    if (((*(expr_8.TyDecl_)).t1.tag != Synonym_1)) goto next_1226;
    struct Ty_ _ty_5 = (*((*(expr_8.TyDecl_)).t1.Synonym_1)).t0;
    struct IntIntTuple2 _loc_5 = (*((*(expr_8.TyDecl_)).t1.Synonym_1)).t1;
    struct DumpTree_ call_977 = dumpTreeNew_((struct String){.str = "synonym", .len = 7}, NULL);
    match_285 = call_977;
    goto end_match_1217;
next_1226:;
    if ((expr_8.tag != TyDecl_)) goto next_1227;
    if (((*(expr_8.TyDecl_)).t1.tag != Union_1)) goto next_1227;
    struct String ident_17 = (*((*(expr_8.TyDecl_)).t1.Union_1)).t0;
    struct DumpTree_ call_978 = dumpTreeNewLeaf_(ident_17);
    struct DumpTree_List* list_117 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_117->head = call_978;
    list_117->tail = NULL;
    struct DumpTree_ call_979 = dumpTreeNew_((struct String){.str = "union", .len = 5}, list_117);
    match_285 = call_979;
    goto end_match_1217;
next_1227:;
    if ((expr_8.tag != Open_2)) goto next_1228;
    struct StringList* path_2 = (*(expr_8.Open_2)).t0;
    void* box_32 = (void*)malloc(sizeof(int));
    (*(((int*)box_32))) = 0;
    void* env_71 = box_32;
    struct StringDumpTree_Fun1 fun_77 = (struct StringDumpTree_Fun1){.fun = fun_41, .env = env_71};
    struct DumpTree_List* call_980 = listMap_1(fun_77, path_2);
    struct DumpTree_ call_981 = dumpTreeNew_((struct String){.str = "open", .len = 4}, call_980);
    match_285 = call_981;
    goto end_match_1217;
next_1228:;
    if ((expr_8.tag != Error_2)) goto next_1229;
    struct String msg_1 = (*(expr_8.Error_2)).t0;
    struct IntIntTuple2 loc_26 = (*(expr_8.Error_2)).t1;
    struct DumpTree_ call_982 = dumpTreeFromError_(msg_1, loc_26);
    match_285 = call_982;
    goto end_match_1217;
next_1229:;
    exit(1);
end_match_1217:;
    return match_285;
}

int fun_4(struct Token_IntIntTuple2Tuple2 arg_201) {
    struct Token_ token_13 = arg_201.t0;
    int y_18 = arg_201.t1.t0;
    int x_34 = arg_201.t1.t1;
    struct String call_983 = tokenToString_(token_13);
    printf("%s (%d, %d)\n", call_983.str, y_18, x_34);
    int call_984 = 0;
    return 0;
}

int fun_42(void* env_36, struct Token_IntIntTuple2Tuple2 arg_92) {
    int call_985 = fun_4(arg_92);
    return 0;
}

int fun_5(struct StringIntIntTuple2Tuple2 arg_202) {
    struct String msg_2 = arg_202.t0;
    int y_19 = arg_202.t1.t0;
    int x_35 = arg_202.t1.t1;
    printf("ERROR %s (%d:%d)\n", msg_2.str, (y_19 + 1), (x_35 + 1));
    int call_986 = 0;
    return 0;
}

int fun_43(void* env_37, struct StringIntIntTuple2Tuple2 arg_93) {
    int call_987 = fun_5(arg_93);
    return 0;
}

struct StringStringFun1 {
    struct String(*fun)(void*, struct String);
    void* env;
};

int doFile_(struct StringStringFun1 fileReadAllText_1, struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, char charNull_, struct String filePath_) {
    printf("FILE %s\n", filePath_.str);
    int call_988 = 0;
    struct String app_70 = fileReadAllText_1.fun(fileReadAllText_1.env, filePath_);
    struct String source_ = app_70;
    struct Token_IntIntTuple2Tuple2List* call_989 = tokenize_(charNull_, source_);
    struct Token_IntIntTuple2Tuple2List* tokens_ = call_989;
    void* box_33 = (void*)malloc(sizeof(int));
    (*(((int*)box_33))) = 0;
    void* env_72 = box_33;
    struct Token_IntIntTuple2Tuple2UnitFun1 fun_78 = (struct Token_IntIntTuple2Tuple2UnitFun1){.fun = fun_42, .env = env_72};
    int call_990 = listIter_2(fun_78, tokens_);
    struct AExpr_StringIntIntTuple2Tuple2ListTuple2 call_991 = parse_(tokens_);
    struct AExpr_ ast_ = call_991.t0;
    struct StringIntIntTuple2Tuple2List* errors_ = call_991.t1;
    printf("AST:\n");
    int call_992 = 0;
    struct DumpTree_ call_993 = axDump_(ast_);
    struct String call_994 = dumpTreeToString_(call_993);
    printf("%s\n", call_994.str);
    int call_995 = 0;
    void* box_34 = (void*)malloc(sizeof(int));
    (*(((int*)box_34))) = 0;
    void* env_73 = box_34;
    struct StringIntIntTuple2Tuple2UnitFun1 fun_79 = (struct StringIntIntTuple2Tuple2UnitFun1){.fun = fun_43, .env = env_73};
    int call_996 = listIter_1(fun_79, errors_);
    struct NameCtx_ call_997 = nameCtxEmpty_(0);
    struct NameCtx_ nameCtx_1 = call_997;
    struct AExpr_NameCtx_Tuple2 tuple_608;
    tuple_608.t0 = ast_;
    tuple_608.t1 = nameCtx_1;
    struct HExpr_NameCtx_Tuple2 call_998 = astToHir_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_608);
    struct HExpr_ expr_9 = call_998.t0;
    struct NameCtx_ nameCtx_2 = call_998.t1;
    printf("HIR:\n");
    int call_999 = 0;
    struct DumpTree_ call_1000 = hxDump_(nameCtx_2, expr_9);
    struct String call_1001 = dumpTreeToString_(call_1000);
    printf("%s\n", call_1001.str);
    int call_1002 = 0;
    return 0;
}

int doSelf_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, char charNull_, struct StringStringFun1 fileReadAllText_1) {
    int call_1003 = doFile_(fileReadAllText_1, litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, charNull_, (struct String){.str = "MiloneLang/Lexing.fs", .len = 20});
    int call_1004 = doFile_(fileReadAllText_1, litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, charNull_, (struct String){.str = "MiloneLang/Parsing.fs", .len = 21});
    int call_1005 = doFile_(fileReadAllText_1, litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, charNull_, (struct String){.str = "MiloneLang/AstToHir.fs", .len = 22});
    return 0;
}

struct String fileReadAllText_(struct String fileName_) {
    struct String call_1006 = file_read_all_text(fileName_);
    return call_1006;
}

struct String fun_44(void* env_38, struct String arg_94) {
    struct String call_1007 = fileReadAllText_(arg_94);
    return call_1007;
}

int main() {
    struct IntIntTuple2 tuple_609;
    tuple_609.t0 = (0 - 1);
    tuple_609.t1 = (0 - 1);
    struct IntIntTuple2 noLoc_ = tuple_609;
    struct IntIntTuple2* payload_192 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_192))) = noLoc_;
    struct Ty_ variant_192 = (struct Ty_){.tag = Error_1, .Error_1 = payload_192};
    struct Ty_ noTy_ = variant_192;
    struct TyCon_Ty_ListTuple2 tuple_610;
    tuple_610.t0 = (struct TyCon_){.tag = Bool_2};
    tuple_610.t1 = NULL;
    struct TyCon_Ty_ListTuple2* payload_193 = (struct TyCon_Ty_ListTuple2*)malloc(sizeof(struct TyCon_Ty_ListTuple2));
    (*(((struct TyCon_Ty_ListTuple2*)payload_193))) = tuple_610;
    struct Ty_ variant_193 = (struct Ty_){.tag = Con_, .Con_ = payload_193};
    struct Ty_ tyBool_ = variant_193;
    struct TyCon_Ty_ListTuple2 tuple_611;
    tuple_611.t0 = (struct TyCon_){.tag = Int_2};
    tuple_611.t1 = NULL;
    struct TyCon_Ty_ListTuple2* payload_194 = (struct TyCon_Ty_ListTuple2*)malloc(sizeof(struct TyCon_Ty_ListTuple2));
    (*(((struct TyCon_Ty_ListTuple2*)payload_194))) = tuple_611;
    struct Ty_ variant_194 = (struct Ty_){.tag = Con_, .Con_ = payload_194};
    struct Ty_ tyInt_ = variant_194;
    struct TyCon_Ty_ListTuple2 tuple_612;
    tuple_612.t0 = (struct TyCon_){.tag = Char_2};
    tuple_612.t1 = NULL;
    struct TyCon_Ty_ListTuple2* payload_195 = (struct TyCon_Ty_ListTuple2*)malloc(sizeof(struct TyCon_Ty_ListTuple2));
    (*(((struct TyCon_Ty_ListTuple2*)payload_195))) = tuple_612;
    struct Ty_ variant_195 = (struct Ty_){.tag = Con_, .Con_ = payload_195};
    struct Ty_ tyChar_ = variant_195;
    struct TyCon_Ty_ListTuple2 tuple_613;
    tuple_613.t0 = (struct TyCon_){.tag = Str_2};
    tuple_613.t1 = NULL;
    struct TyCon_Ty_ListTuple2* payload_196 = (struct TyCon_Ty_ListTuple2*)malloc(sizeof(struct TyCon_Ty_ListTuple2));
    (*(((struct TyCon_Ty_ListTuple2*)payload_196))) = tuple_613;
    struct Ty_ variant_196 = (struct Ty_){.tag = Con_, .Con_ = payload_196};
    struct Ty_ tyStr_ = variant_196;
    struct TyCon_Ty_ListTuple2 tuple_614;
    tuple_614.t0 = (struct TyCon_){.tag = Obj_};
    tuple_614.t1 = NULL;
    struct TyCon_Ty_ListTuple2* payload_197 = (struct TyCon_Ty_ListTuple2*)malloc(sizeof(struct TyCon_Ty_ListTuple2));
    (*(((struct TyCon_Ty_ListTuple2*)payload_197))) = tuple_614;
    struct Ty_ variant_197 = (struct Ty_){.tag = Con_, .Con_ = payload_197};
    struct Ty_ tyObj_ = variant_197;
    struct Ty_ call_1008 = tyTuple_(NULL);
    struct Ty_ tyUnit_ = call_1008;
    int* payload_198 = (int*)malloc(sizeof(int));
    (*(((int*)payload_198))) = 1;
    struct Lit_ variant_198 = (struct Lit_){.tag = Bool_, .Bool_ = payload_198};
    struct Lit_ litTrue_ = variant_198;
    int* payload_199 = (int*)malloc(sizeof(int));
    (*(((int*)payload_199))) = 0;
    struct Lit_ variant_199 = (struct Lit_){.tag = Bool_, .Bool_ = payload_199};
    struct Lit_ litFalse_ = variant_199;
    char call_1009 = ((char)0);
    char charNull_ = call_1009;
    void* box_35 = (void*)malloc(sizeof(int));
    (*(((int*)box_35))) = 0;
    void* env_74 = box_35;
    struct StringStringFun1 fun_80 = (struct StringStringFun1){.fun = fun_44, .env = env_74};
    int call_1010 = doSelf_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, charNull_, fun_80);
    return call_1010;
}
