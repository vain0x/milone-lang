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

struct IntIntTuple2;

struct Token_IntIntTuple2Tuple2;

struct Token_ fst_1(struct Token_IntIntTuple2Tuple2 arg_85);

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

struct Token_IntIntTuple2Tuple2List;

struct Token_IntIntTuple2Tuple2List* go_65(struct Token_IntIntTuple2Tuple2List* acc_5, struct Token_IntIntTuple2Tuple2List* xs_2);

enum ATy_Tag;

struct ATy_;

struct ATy_List;

struct ATy_List* go_64(struct ATy_List* acc_5, struct ATy_List* xs_2);

enum AVariant_Tag;

struct AVariant_;

struct AVariant_List;

struct AVariant_List* go_63(struct AVariant_List* acc_5, struct AVariant_List* xs_2);

struct APat_List* go_62(struct APat_List* acc_5, struct APat_List* xs_2);

enum AArm_Tag;

struct AArm_;

struct AArm_List;

struct AArm_List* go_61(struct AArm_List* acc_5, struct AArm_List* xs_2);

struct StringList* go_60(struct StringList* acc_5, struct StringList* xs_2);

struct AExpr_List* go_59(struct AExpr_List* acc_5, struct AExpr_List* xs_2);

struct DumpTree_List* go_74(struct DumpTree_List* acc_5, struct DumpTree_List* xs_2);

enum Ty_Tag;

struct Ty_;

struct Ty_List;

struct Ty_List* go_73(struct Ty_List* acc_5, struct Ty_List* xs_2);

enum HExpr_Tag;

struct HExpr_;

struct HPat_HExpr_HExpr_Tuple3;

struct HPat_HExpr_HExpr_Tuple3List;

struct HPat_HExpr_HExpr_Tuple3List* go_72(struct HPat_HExpr_HExpr_Tuple3List* acc_5, struct HPat_HExpr_HExpr_Tuple3List* xs_2);

struct HExpr_List;

struct HExpr_List* go_71(struct HExpr_List* acc_5, struct HExpr_List* xs_2);

struct HPat_List;

struct HPat_List* go_70(struct HPat_List* acc_5, struct HPat_List* xs_2);

struct StringIntBoolTy_Tuple4;

struct StringIntBoolTy_Tuple4List;

struct StringIntBoolTy_Tuple4List* go_69(struct StringIntBoolTy_Tuple4List* acc_5, struct StringIntBoolTy_Tuple4List* xs_2);

struct Token_List;

struct Token_List* go_75(struct Token_List* acc_5, struct Token_List* xs_2);

struct Token_IntIntTuple2Tuple2List* listRev_7(struct Token_IntIntTuple2Tuple2List* xs_1);

struct ATy_List* listRev_6(struct ATy_List* xs_1);

struct AVariant_List* listRev_5(struct AVariant_List* xs_1);

struct APat_List* listRev_4(struct APat_List* xs_1);

struct AArm_List* listRev_3(struct AArm_List* xs_1);

struct StringList* listRev_2(struct StringList* xs_1);

struct AExpr_List* listRev_1(struct AExpr_List* xs_1);

struct DumpTree_List* listRev_13(struct DumpTree_List* xs_1);

struct Ty_List* listRev_12(struct Ty_List* xs_1);

struct HPat_HExpr_HExpr_Tuple3List* listRev_11(struct HPat_HExpr_HExpr_Tuple3List* xs_1);

struct HExpr_List* listRev_10(struct HExpr_List* xs_1);

struct HPat_List* listRev_9(struct HPat_List* xs_1);

struct StringIntBoolTy_Tuple4List* listRev_8(struct StringIntBoolTy_Tuple4List* xs_1);

struct Token_List* listRev_14(struct Token_List* xs_1);

int go_58(int len_, struct StringList* xs_5);

int listLength_1(struct StringList* xs_4);

struct Token_IntIntTuple2Tuple2UnitFun1;

int listIter_2(struct Token_IntIntTuple2Tuple2UnitFun1 f_, struct Token_IntIntTuple2Tuple2List* xs_7);

struct StringIntIntTuple2Tuple2UnitFun1;

struct StringIntIntTuple2Tuple2;

struct StringIntIntTuple2Tuple2List;

int listIter_1(struct StringIntIntTuple2Tuple2UnitFun1 f_, struct StringIntIntTuple2Tuple2List* xs_7);

struct HExpr_Ty_Fun1;

struct Ty_List* go_57(struct HExpr_Ty_Fun1 f_1, struct Ty_List* acc_6, struct HExpr_List* xs_10);

struct HPat_HExpr_HExpr_Tuple3HPat_HExpr_HExpr_Tuple3Fun1;

struct HPat_HExpr_HExpr_Tuple3List* go_56(struct HPat_HExpr_HExpr_Tuple3HPat_HExpr_HExpr_Tuple3Fun1 f_1, struct HPat_HExpr_HExpr_Tuple3List* acc_6, struct HPat_HExpr_HExpr_Tuple3List* xs_10);

struct HExpr_HExpr_Fun1;

struct HExpr_List* go_55(struct HExpr_HExpr_Fun1 f_1, struct HExpr_List* acc_6, struct HExpr_List* xs_10);

struct HPat_HPat_Fun1;

struct HPat_List* go_54(struct HPat_HPat_Fun1 f_1, struct HPat_List* acc_6, struct HPat_List* xs_10);

struct ATy_DumpTree_Fun1;

struct DumpTree_List* go_53(struct ATy_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct ATy_List* xs_10);

struct AArm_DumpTree_Fun1;

struct DumpTree_List* go_52(struct AArm_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct AArm_List* xs_10);

struct APat_DumpTree_Fun1;

struct DumpTree_List* go_51(struct APat_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct APat_List* xs_10);

struct AExpr_DumpTree_Fun1;

struct DumpTree_List* go_50(struct AExpr_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct AExpr_List* xs_10);

struct AVariant_DumpTree_Fun1;

struct DumpTree_List* go_49(struct AVariant_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct AVariant_List* xs_10);

struct HExpr_DumpTree_Fun1;

struct DumpTree_List* go_48(struct HExpr_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct HExpr_List* xs_10);

struct StringDumpTree_Fun1;

struct DumpTree_List* go_47(struct StringDumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct StringList* xs_10);

struct Token_IntIntTuple2Tuple2Token_Fun1;

struct Token_List* go_68(struct Token_IntIntTuple2Tuple2Token_Fun1 f_1, struct Token_List* acc_6, struct Token_IntIntTuple2Tuple2List* xs_10);

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

struct Token_List* listMap_12(struct Token_IntIntTuple2Tuple2Token_Fun1 f_1, struct Token_IntIntTuple2Tuple2List* xs_9);

struct Token_List* go_67(int count_1, struct Token_List* xs_13);

struct Token_List* listTruncate_1(int count_, struct Token_List* xs_12);

struct Ty_NameCtx_Tuple2;

struct ATy_NameCtx_Tuple2Ty_NameCtx_Tuple2Fun1;

struct ATy_ListNameCtx_Tuple2;

struct Ty_ListNameCtx_Tuple2;

struct ATy_NameCtx_Tuple2;

struct Ty_ListNameCtx_Tuple2 go_46(struct ATy_NameCtx_Tuple2Ty_NameCtx_Tuple2Fun1 f_2, struct Ty_List* acc_7, struct ATy_ListNameCtx_Tuple2 arg_86);

struct HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2;

struct AArm_NameCtx_Tuple2HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2Fun1;

struct AArm_ListNameCtx_Tuple2;

struct HPat_HExpr_HExpr_Tuple3ListNameCtx_Tuple2;

struct AArm_NameCtx_Tuple2;

struct HPat_HExpr_HExpr_Tuple3ListNameCtx_Tuple2 go_45(struct AArm_NameCtx_Tuple2HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2Fun1 f_2, struct HPat_HExpr_HExpr_Tuple3List* acc_7, struct AArm_ListNameCtx_Tuple2 arg_87);

struct HExpr_NameCtx_Tuple2;

struct AExpr_NameCtx_Tuple2HExpr_NameCtx_Tuple2Fun1;

struct AExpr_ListNameCtx_Tuple2;

struct HExpr_ListNameCtx_Tuple2;

struct AExpr_NameCtx_Tuple2;

struct HExpr_ListNameCtx_Tuple2 go_44(struct AExpr_NameCtx_Tuple2HExpr_NameCtx_Tuple2Fun1 f_2, struct HExpr_List* acc_7, struct AExpr_ListNameCtx_Tuple2 arg_88);

struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1;

struct APat_ListNameCtx_Tuple2;

struct HPat_ListNameCtx_Tuple2;

struct APat_NameCtx_Tuple2;

struct HPat_ListNameCtx_Tuple2 go_43(struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1 f_2, struct HPat_List* acc_7, struct APat_ListNameCtx_Tuple2 arg_89);

struct StringIntBoolTy_Tuple4NameCtx_Tuple2;

struct AVariant_NameCtx_Tuple2StringIntBoolTy_Tuple4NameCtx_Tuple2Fun1;

struct AVariant_ListNameCtx_Tuple2;

struct StringIntBoolTy_Tuple4ListNameCtx_Tuple2;

struct AVariant_NameCtx_Tuple2;

struct StringIntBoolTy_Tuple4ListNameCtx_Tuple2 go_42(struct AVariant_NameCtx_Tuple2StringIntBoolTy_Tuple4NameCtx_Tuple2Fun1 f_2, struct StringIntBoolTy_Tuple4List* acc_7, struct AVariant_ListNameCtx_Tuple2 arg_90);

struct Ty_ListNameCtx_Tuple2 stMap_5(struct ATy_NameCtx_Tuple2Ty_NameCtx_Tuple2Fun1 f_2, struct ATy_ListNameCtx_Tuple2 arg_91);

struct HPat_HExpr_HExpr_Tuple3ListNameCtx_Tuple2 stMap_4(struct AArm_NameCtx_Tuple2HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2Fun1 f_2, struct AArm_ListNameCtx_Tuple2 arg_92);

struct HExpr_ListNameCtx_Tuple2 stMap_3(struct AExpr_NameCtx_Tuple2HExpr_NameCtx_Tuple2Fun1 f_2, struct AExpr_ListNameCtx_Tuple2 arg_93);

struct HPat_ListNameCtx_Tuple2 stMap_2(struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1 f_2, struct APat_ListNameCtx_Tuple2 arg_94);

struct StringIntBoolTy_Tuple4ListNameCtx_Tuple2 stMap_1(struct AVariant_NameCtx_Tuple2StringIntBoolTy_Tuple4NameCtx_Tuple2Fun1 f_2, struct AVariant_ListNameCtx_Tuple2 arg_95);

int intMin_(int x_8, int y_3);

int intMax_(int x_9, int y_4);

int intEq_(int x_10, int y_5);

struct String go_17(struct String acc_8, int len_2, int n_);

struct String intToHexWithPadding_(int len_1, int value_3);

int hexDigitToInt_(char c_5);

int go_18(struct String s_4, int r_20, int acc_9, int i_50);

int intFromHex_(int l_8, int r_20, struct String s_4);

int charSub_(char x_11, char y_6);

int charIsControl_(char c_6);

int charIsSpace_(char c_7);

int charIsDigit_(char c_8);

int charIsAlpha_(char c_9);

int charNeedsEscaping_(char c_10);

struct String charEscape_(char c_11);

struct String strSlice_(int start_, int endIndex_1, struct String s_5);

struct StringStringListTuple2;

struct StringStringListTuple2 go_19(struct StringList* xs_19, int xn_);

struct String strConcat_(struct StringList* xs_18);

int go_20(struct String str_2, int i_51);

int strNeedsEscaping_(struct String str_2);

int raw_(struct String str_3, int i_53);

struct IntStringListTuple2;

struct StringList* go_21(struct String str_3, struct StringList* acc_10, int i_52);

struct String strEscape_(struct String str_3);

int locX_(struct IntIntTuple2 arg_96);

int locY_(struct IntIntTuple2 arg_97);

int locIsSameRow_(struct IntIntTuple2 first_, struct IntIntTuple2 second_);

int locIsSameColumn_(struct IntIntTuple2 first_1, struct IntIntTuple2 second_1);

int locInside_(struct IntIntTuple2 firstLoc_, struct IntIntTuple2 secondLoc_);

struct IntIntTuple2 locAddX_(int dx_, struct IntIntTuple2 arg_98);

struct IntIntTuple2 locMax_(struct IntIntTuple2 arg_99, struct IntIntTuple2 arg_100);

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

struct AExpr_ app_(struct IntIntTuple2 loc_8, struct AExpr_ x_16, struct AExpr_ f_4);

struct AExpr_ axApp3_(struct AExpr_ f_3, struct AExpr_ x1_, struct AExpr_ x2_, struct AExpr_ x3_, struct IntIntTuple2 loc_8);

struct AExpr_ axNot_(struct Lit_ litFalse_, struct AExpr_ arg_, struct IntIntTuple2 loc_9);

struct StringDumpTree_ListDumpTree_ListTuple3;

struct DumpTree_ dumpTreeNew_(struct String text_43, struct DumpTree_List* children_);

struct DumpTree_ dumpTreeNewLeaf_(struct String text_44);

struct DumpTree_ dumpTreeAttachNext_(struct DumpTree_ next_1, struct DumpTree_ tree_);

struct DumpTree_ dumpTreeFromError_(struct String msg_, struct IntIntTuple2 arg_101);

struct StringList* goChildren_(struct String eol_1, struct DumpTree_List* children_2, struct StringList* acc_13);

struct StringList* goNext_(struct String eol_2, struct DumpTree_List* next_2, struct StringList* acc_14);

struct StringList* go_22(struct String eol_, struct DumpTree_ node_1, struct StringList* acc_12);

struct String dumpTreeToString_(struct DumpTree_ node_);

struct IntStringTuple2;

struct IntStringTuple2List;

struct IntStringTuple2ListIntTuple2;

struct NameCtx_ nameCtxEmpty_(int arg_102);

struct IntNameCtx_Tuple2;

struct IntNameCtx_Tuple2 nameCtxAdd_1(struct String ident_, struct NameCtx_ arg_103);

struct Ty_Ty_Fun1;

enum Trait_Tag;

struct Trait_;

struct Ty_Ty_Ty_Tuple3;

struct Trait_ traitMapTys_(struct Ty_Ty_Fun1 f_5, struct Trait_ it_);

enum TyCon_Tag;

struct TyCon_;

struct TyCon_Ty_ListTuple2;

struct Ty_ tyTuple_(struct Ty_List* tys_);

struct Ty_ tyList_(struct Ty_ ty_5);

struct Ty_ tyFun_(struct Ty_ sourceTy_, struct Ty_ targetTy_);

struct Ty_ tyRef_(int serial_2, struct Ty_List* tys_1);

struct StringTy_ListTuple2;

struct Ty_ tyPrimFromIdent_(struct Ty_ tyUnit_, struct Ty_ tyObj_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct String ident_1, struct Ty_List* tys_2, struct IntIntTuple2 loc_10);

struct IntIntIntTuple2Tuple2;

int go_23(int tySerial_, struct Ty_ ty_7);

int tyIsFreeIn_(struct Ty_ ty_6, int tySerial_);

int go_24(struct Ty_List* tys_4);

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

struct HPat_ fun_3(void* env_, struct HPat_ arg_6);

struct HPat_ fun_4(void* env_1, struct HPat_ arg_9);

struct HPat_ go_25(struct IntIntTuple2IntIntTuple2Fun1 g_, struct Ty_Ty_Fun1 f_6, struct HPat_ pat_3);

struct HPat_ patMap_(struct Ty_Ty_Fun1 f_6, struct IntIntTuple2IntIntTuple2Fun1 g_, struct HPat_ pat_2);

struct HExpr_ hxTrue_(struct Lit_ litTrue_, struct IntIntTuple2 loc_13);

struct HExpr_ hxFalse_(struct Lit_ litFalse_, struct IntIntTuple2 loc_14);

enum InfOp_Tag;

struct InfOp_;

struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4;

struct HExpr_ hxApp_(struct HExpr_ f_7, struct HExpr_ x_19, struct Ty_ ty_27, struct IntIntTuple2 loc_15);

struct HExpr_ hxAnno_(struct HExpr_ expr_, struct Ty_ ty_28, struct IntIntTuple2 loc_16);

struct HExpr_ hxSemi_(struct Ty_ noTy_, struct HExpr_List* items_, struct IntIntTuple2 loc_17);

struct HExpr_ hxCallProc_(struct HExpr_ callee_1, struct HExpr_List* args_1, struct Ty_ resultTy_2, struct IntIntTuple2 loc_18);

struct HExpr_ hxCallClosure_(struct HExpr_ callee_2, struct HExpr_List* args_2, struct Ty_ resultTy_3, struct IntIntTuple2 loc_19);

struct Ty_Ty_Ty_Ty_Ty_Tuple5;

struct Ty_ fun_5(void* env_2, struct HExpr_ arg_12);

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

struct HPat_ goPat_(struct IntIntTuple2IntIntTuple2Fun1 g_1, struct Ty_Ty_Fun1 f_8, struct HPat_ pat_7);

struct HPat_HExpr_HExpr_Tuple3 fun_(struct IntIntTuple2IntIntTuple2Fun1 g_1, struct Ty_Ty_Fun1 f_8, struct HPat_HExpr_HExpr_Tuple3 arg_104);

struct HPat_HExpr_HExpr_Tuple3 fun_6(void* env_3, struct HPat_HExpr_HExpr_Tuple3 arg_18);

struct HExpr_ fun_7(void* env_4, struct HExpr_ arg_21);

struct HPat_ fun_8(void* env_5, struct HPat_ arg_24);

struct HExpr_ go_26(struct IntIntTuple2IntIntTuple2Fun1 g_1, struct Ty_Ty_Fun1 f_8, struct HExpr_ expr_5);

struct HExpr_ exprMap_(struct Ty_Ty_Fun1 f_8, struct IntIntTuple2IntIntTuple2Fun1 g_1, struct HExpr_ expr_4);

struct Ty_ exprToTy_(struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct HExpr_ expr_6);

struct IntIntTuple2 go_(int r_, struct String text_, int y_1, int x_2, int i_);

struct IntIntTuple2 locShift_(struct String text_, int l_, int r_, struct IntIntTuple2 arg_105);

int charIsIdent_(char c_);

int charIsOp_(char c_1);

int charIsPun_(char c_2);

int go_1(struct String s_, struct String prefix_, int pi_, int si_);

int strIsFollowedBy_(int i_1, struct String prefix_, struct String s_);

int strIsFollowedByRawQuotes_(int i_2, struct String s_1);

int scanError_(struct String arg_106, int i_3);

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

struct StringIntTuple2 tokCtxToTextIndex_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 arg_107);

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokCtxSkip_(int r_8, struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 arg_108);

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokCtxPush_(struct Token_ kind_, int r_9, struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 arg_109);

struct Token_IntIntTuple2Tuple2List* tokEof_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 arg_110);

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

struct Token_ fun_39(void* env_6, struct Token_IntIntTuple2Tuple2 arg_27);

struct StringStringToken_ListStringFun3;

struct StringIntIntTuple2Tuple2List* parseErrorCore_1(struct String msg_3, struct IntIntTuple2 loc_29, struct Token_IntIntTuple2Tuple2List* tokens_6, struct StringIntIntTuple2Tuple2List* errors_1);

struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2;

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyError_1(struct String msg_5, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_111);

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatError_1(struct String msg_6, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_112);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseExprError_1(struct String msg_7, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_113);

struct StringIntIntTuple2Tuple2List* parseNewError_1(struct String msg_8, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_114);

struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_86(struct IntIntTuple2 baseLoc_1, struct ATy_List* acc_15, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_115);

struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyArgs_1(struct IntIntTuple2 baseLoc_1, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_116);

struct StringATy_ListIntIntTuple2Tuple3;

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyAtom_1(struct IntIntTuple2 baseLoc_2, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_117);

struct ATy_StringIntIntTuple2Tuple3;

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_83(struct IntIntTuple2 baseLoc_3, struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 arg_118);

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTySuffix_1(struct IntIntTuple2 baseLoc_3, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_119);

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyPrefix_1(struct IntIntTuple2 baseLoc_4, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_120);

struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_80(struct IntIntTuple2 baseLoc_5, struct ATy_List* acc_16, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_121);

struct ATy_ListIntIntTuple2Tuple2;

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyTuple_1(struct IntIntTuple2 baseLoc_5, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_122);

struct ATy_ATy_IntIntTuple2Tuple3;

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyFun_1(struct IntIntTuple2 baseLoc_6, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_123);

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTy_1(struct IntIntTuple2 baseLoc_7, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_124);

struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_79(struct IntIntTuple2 baseLoc_8, struct AVariant_List* acc_17, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_125);

enum ATyDecl_Tag;

struct ATyDecl_;

struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyDeclUnion_1(struct IntIntTuple2 baseLoc_8, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_126);

struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyDeclBody_1(struct IntIntTuple2 baseLoc_9, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_127);

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatParenBody_1(struct IntIntTuple2 baseLoc_10, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_128);

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_82(struct IntIntTuple2 baseLoc_11, struct APat_List* patAcc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_129);

struct APat_ListIntIntTuple2Tuple2;

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatListBody_1(struct IntIntTuple2 baseLoc_11, struct IntIntTuple2 bracketLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_130);

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatAtom_1(struct IntIntTuple2 baseLoc_12, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_131);

struct APat_StringIntIntTuple2Tuple3;

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatNav_1(struct IntIntTuple2 baseLoc_13, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_132);

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_78(struct IntIntTuple2 argBaseLoc_, struct IntIntTuple2 baseLoc_14, struct APat_List* acc_18, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_133);

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatCallArgs_1(struct IntIntTuple2 baseLoc_14, struct IntIntTuple2 calleeLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_134);

struct APat_APat_ListIntIntTuple2Tuple3;

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatCall_1(struct IntIntTuple2 baseLoc_15, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_135);

struct APat_APat_IntIntTuple2Tuple3;

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatCons_1(struct IntIntTuple2 baseLoc_16, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_136);

struct APat_ATy_IntIntTuple2Tuple3;

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatAnno_1(struct IntIntTuple2 baseLoc_17, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_137);

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_81(struct IntIntTuple2 baseLoc_18, struct APat_List* acc_19, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_138);

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatTuple_1(struct IntIntTuple2 baseLoc_18, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_139);

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatAs_1(struct IntIntTuple2 baseLoc_19, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_140);

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatOr_1(struct IntIntTuple2 baseLoc_20, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_141);

struct StringAPat_ListIntIntTuple2Tuple3;

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatLet_1(struct IntIntTuple2 baseLoc_21, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_142);

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePat_1(struct IntIntTuple2 baseLoc_22, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_143);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseRange_1(struct IntIntTuple2 baseLoc_23, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_144);

struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseList_1(struct IntIntTuple2 baseLoc_24, struct IntIntTuple2 bracketLoc_1, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_145);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseThenClause_1(struct IntIntTuple2 baseLoc_25, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_146);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseElseClause_1(struct IntIntTuple2 baseLoc_26, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_147);

struct AExpr_AExpr_AExpr_IntIntTuple2Tuple4;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseIf_1(struct IntIntTuple2 ifLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_148);

struct APat_AExpr_AExpr_IntIntTuple2Tuple4;

struct AArm_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct AArm_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseMatchArm_1(struct IntIntTuple2 matchLoc_, struct IntIntTuple2 armLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_149);

struct AArm_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct AArm_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_87(struct IntIntTuple2 matchLoc_1, struct AArm_List* acc_20, struct IntIntTuple2 armLoc_2, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_150);

struct IntIntTuple2Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct AExpr_AArm_ListIntIntTuple2Tuple3;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseMatch_1(struct IntIntTuple2 matchLoc_1, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_151);

struct APat_ListAExpr_IntIntTuple2Tuple3;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseFun_1(struct IntIntTuple2 baseLoc_27, struct IntIntTuple2 funLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_152);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseParenBody_1(struct IntIntTuple2 baseLoc_28, struct IntIntTuple2 parenLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_153);

struct Token_IntIntTuple2Tuple2List* parseAccessModifier_1(struct Token_IntIntTuple2Tuple2List* tokens_148);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseLet_1(struct IntIntTuple2 letLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_154);

struct StringATy_IntIntTuple2Tuple3;

struct StringAVariant_ListIntIntTuple2Tuple3;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyDecl_1(struct IntIntTuple2 typeLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_155);

struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_76(struct StringList* acc_21, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_156);

struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePath_1(struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_157);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseOpen_1(struct IntIntTuple2 openLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_158);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseAtom_1(struct IntIntTuple2 baseLoc_30, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_159);

struct AExpr_AExpr_IntIntTuple2Tuple3;

struct AExpr_StringIntIntTuple2Tuple3;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_85(struct IntIntTuple2 baseLoc_31, struct AExpr_ acc_22, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_160);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseSuffix_1(struct IntIntTuple2 baseLoc_31, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_161);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_84(struct IntIntTuple2 argBaseLoc_1, struct IntIntTuple2 calleeLoc_3, struct IntIntTuple2 baseLoc_32, struct AExpr_ callee_8, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_162);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseApp_1(struct IntIntTuple2 baseLoc_32, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_163);

enum UniOp_Tag;

struct UniOp_;

struct UniOp_AExpr_IntIntTuple2Tuple3;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePrefix_1(struct IntIntTuple2 baseLoc_33, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_164);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseNextLevelOp_1(struct OpLevel_ level_1, struct IntIntTuple2 baseLoc_34, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_165);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 nextL_1(struct IntIntTuple2 baseLoc_35, struct OpLevel_ level_2, struct AExpr_ expr_12, struct Op_ op_, struct IntIntTuple2 opLoc_2, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_166);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 nextR_1(struct IntIntTuple2 baseLoc_35, struct OpLevel_ level_2, struct AExpr_ expr_14, struct Op_ op_1, struct IntIntTuple2 opLoc_3, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_167);

struct OpLevel_Token_IntIntTuple2Tuple2ListTuple2;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseOps_1(struct OpLevel_ level_2, struct IntIntTuple2 baseLoc_35, struct AExpr_ first_3, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_168);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseOp_1(struct OpLevel_ level_3, struct IntIntTuple2 baseLoc_36, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_169);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTupleItem_1(struct IntIntTuple2 baseLoc_37, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_170);

struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_77(struct IntIntTuple2 baseLoc_38, struct AExpr_List* acc_23, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_171);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTuple_1(struct IntIntTuple2 baseLoc_38, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_172);

struct AExpr_ATy_IntIntTuple2Tuple3;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseAnno_1(struct IntIntTuple2 baseLoc_39, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_173);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseExpr_1(struct IntIntTuple2 baseLoc_40, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_174);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseStmt_1(struct IntIntTuple2 baseLoc_41, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_175);

struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_66(struct IntIntTuple2 baseLoc_42, struct AExpr_List* acc_24, struct IntIntTuple2 alignLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_176);

struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseStmts_1(struct IntIntTuple2 baseLoc_42, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_177);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseSemi_1(struct IntIntTuple2 baseLoc_43, struct IntIntTuple2 mainLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_178);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTopLevel_1(struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_179);

struct AExpr_StringIntIntTuple2Tuple2ListTuple2;

struct AExpr_StringIntIntTuple2Tuple2ListTuple2 parse_(struct Token_IntIntTuple2Tuple2List* tokens_252);

struct HPrim_ opToPrim_(struct Op_ op_2);

struct APat_ go_40(struct IntIntTuple2 loc_68, struct APat_List* pats_5);

struct APat_ desugarListLitPat_(struct APat_List* pats_4, struct IntIntTuple2 loc_68);

struct AExpr_ go_41(struct IntIntTuple2 loc_69, struct AExpr_List* items_10);

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

struct Ty_NameCtx_Tuple2 fun_10(void* env_7, struct ATy_NameCtx_Tuple2 arg_28);

struct Ty_NameCtx_Tuple2 fun_11(void* env_8, struct ATy_NameCtx_Tuple2 arg_29);

struct Ty_NameCtx_Tuple2 onTy_(struct ATy_NameCtx_Tuple2 arg_180);

struct Ty_Tuple1;

struct HPat_NameCtx_Tuple2 fun_12(void* env_9, struct APat_NameCtx_Tuple2 arg_30);

struct HPat_NameCtx_Tuple2 fun_13(void* env_10, struct APat_NameCtx_Tuple2 arg_32);

struct HPat_NameCtx_Tuple2 onPat_(struct Ty_ noTy_, struct APat_NameCtx_Tuple2 arg_181);

struct HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2 onArm_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, struct AArm_NameCtx_Tuple2 arg_182);

struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8;

struct HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2 fun_14(void* env_11, struct AArm_NameCtx_Tuple2 arg_34);

struct HExpr_NameCtx_Tuple2 fun_15(void* env_12, struct AExpr_NameCtx_Tuple2 arg_43);

struct HExpr_NameCtx_Tuple2 fun_16(void* env_13, struct AExpr_NameCtx_Tuple2 arg_52);

struct HPat_NameCtx_Tuple2 fun_17(void* env_14, struct APat_NameCtx_Tuple2 arg_61);

struct BoolTy_NameCtx_Tuple3;

struct StringIntBoolTy_Tuple4NameCtx_Tuple2 onVariant_(struct Ty_ tyUnit_, struct AVariant_NameCtx_Tuple2 arg_183);

struct StringIntBoolTy_Tuple4NameCtx_Tuple2 fun_18(void* env_15, struct AVariant_NameCtx_Tuple2 arg_63);

struct StringStringIntBoolTy_Tuple4ListIntIntTuple2Tuple3;

struct HExpr_NameCtx_Tuple2 onExpr_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, struct AExpr_NameCtx_Tuple2 arg_184);

struct HExpr_NameCtx_Tuple2 astToHir_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, struct AExpr_NameCtx_Tuple2 arg_185);

struct String litToString_(struct Lit_ lit_5);

struct String tokenToString_(struct Token_ token_12);

struct DumpTree_ fun_19(void* env_16, struct ATy_ arg_65);

struct DumpTree_ fun_20(void* env_17, struct ATy_ arg_66);

struct DumpTree_ fun_21(void* env_18, struct ATy_ arg_67);

struct DumpTree_ atDump_(struct ATy_ ty_43);

struct DumpTree_ fun_22(void* env_19, struct APat_ arg_68);

struct DumpTree_ fun_23(void* env_20, struct APat_ arg_69);

struct DumpTree_ fun_24(void* env_21, struct APat_ arg_70);

struct DumpTree_ fun_25(void* env_22, struct APat_ arg_71);

struct DumpTree_ apDump_(struct APat_ pat_10);

struct DumpTree_ fun_26(void* env_23, struct AExpr_ arg_72);

struct DumpTree_ dumpArm_(struct AArm_ arg_186);

struct DumpTree_ fun_27(void* env_24, struct AArm_ arg_73);

struct DumpTree_ fun_28(void* env_25, struct APat_ arg_74);

struct DumpTree_ fun_29(void* env_26, struct AExpr_ arg_75);

struct DumpTree_ fun_30(void* env_27, struct AExpr_ arg_76);

struct DumpTree_ fun_31(void* env_28, struct AExpr_ arg_77);

struct DumpTree_ dumpVariant_(struct AVariant_ arg_187);

struct DumpTree_ fun_32(void* env_29, struct AVariant_ arg_78);

struct DumpTree_ fun_33(void* env_30, struct String arg_79);

struct DumpTree_ axDump_(struct AExpr_ expr_7);

struct DumpTree_ fun_34(void* env_31, struct HExpr_ arg_80);

struct DumpTree_ fun_35(void* env_32, struct String arg_81);

struct DumpTree_ hxDump_(struct HExpr_ expr_8);

int fun_1(struct Token_IntIntTuple2Tuple2 arg_188);

int fun_36(void* env_33, struct Token_IntIntTuple2Tuple2 arg_82);

int fun_2(struct StringIntIntTuple2Tuple2 arg_189);

int fun_37(void* env_34, struct StringIntIntTuple2Tuple2 arg_83);

struct StringStringFun1;

int doFile_(struct StringStringFun1 fileReadAllText_1, struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, char charNull_, struct String filePath_);

int doSelf_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, char charNull_, struct StringStringFun1 fileReadAllText_1);

struct String fileReadAllText_(struct String fileName_);

struct String fun_38(void* env_35, struct String arg_84);

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
        struct IntStringTuple2ListIntTuple2* NameCtx_;
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

struct IntIntTuple2 {
    int t0;
    int t1;
};

struct Token_IntIntTuple2Tuple2 {
    struct Token_ t0;
    struct IntIntTuple2 t1;
};

struct Token_ fst_1(struct Token_IntIntTuple2Tuple2 arg_85) {
    struct Token_ x_ = arg_85.t0;
    return x_;
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

struct Token_IntIntTuple2Tuple2List {
    struct Token_IntIntTuple2Tuple2 head;
    struct Token_IntIntTuple2Tuple2List* tail;
};

struct Token_IntIntTuple2Tuple2List* go_65(struct Token_IntIntTuple2Tuple2List* acc_5, struct Token_IntIntTuple2Tuple2List* xs_2) {
    struct Token_IntIntTuple2Tuple2List* match_4;
    if ((!((!(xs_2))))) goto next_14;
    match_4 = acc_5;
    goto end_match_13;
next_14:;
    if ((!(xs_2))) goto next_15;
    struct Token_IntIntTuple2Tuple2 x_3 = xs_2->head;
    struct Token_IntIntTuple2Tuple2List* xs_3 = xs_2->tail;
    struct Token_IntIntTuple2Tuple2List* list_1 = (struct Token_IntIntTuple2Tuple2List*)malloc(sizeof(struct Token_IntIntTuple2Tuple2List));
    list_1->head = x_3;
    list_1->tail = acc_5;
    struct Token_IntIntTuple2Tuple2List* call_6 = go_65(list_1, xs_3);
    match_4 = call_6;
    goto end_match_13;
next_15:;
    exit(1);
end_match_13:;
    return match_4;
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

struct ATy_List* go_64(struct ATy_List* acc_5, struct ATy_List* xs_2) {
    struct ATy_List* match_5;
    if ((!((!(xs_2))))) goto next_17;
    match_5 = acc_5;
    goto end_match_16;
next_17:;
    if ((!(xs_2))) goto next_18;
    struct ATy_ x_3 = xs_2->head;
    struct ATy_List* xs_3 = xs_2->tail;
    struct ATy_List* list_2 = (struct ATy_List*)malloc(sizeof(struct ATy_List));
    list_2->head = x_3;
    list_2->tail = acc_5;
    struct ATy_List* call_7 = go_64(list_2, xs_3);
    match_5 = call_7;
    goto end_match_16;
next_18:;
    exit(1);
end_match_16:;
    return match_5;
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

struct AVariant_List* go_63(struct AVariant_List* acc_5, struct AVariant_List* xs_2) {
    struct AVariant_List* match_6;
    if ((!((!(xs_2))))) goto next_20;
    match_6 = acc_5;
    goto end_match_19;
next_20:;
    if ((!(xs_2))) goto next_21;
    struct AVariant_ x_3 = xs_2->head;
    struct AVariant_List* xs_3 = xs_2->tail;
    struct AVariant_List* list_3 = (struct AVariant_List*)malloc(sizeof(struct AVariant_List));
    list_3->head = x_3;
    list_3->tail = acc_5;
    struct AVariant_List* call_8 = go_63(list_3, xs_3);
    match_6 = call_8;
    goto end_match_19;
next_21:;
    exit(1);
end_match_19:;
    return match_6;
}

struct APat_List* go_62(struct APat_List* acc_5, struct APat_List* xs_2) {
    struct APat_List* match_7;
    if ((!((!(xs_2))))) goto next_23;
    match_7 = acc_5;
    goto end_match_22;
next_23:;
    if ((!(xs_2))) goto next_24;
    struct APat_ x_3 = xs_2->head;
    struct APat_List* xs_3 = xs_2->tail;
    struct APat_List* list_4 = (struct APat_List*)malloc(sizeof(struct APat_List));
    list_4->head = x_3;
    list_4->tail = acc_5;
    struct APat_List* call_9 = go_62(list_4, xs_3);
    match_7 = call_9;
    goto end_match_22;
next_24:;
    exit(1);
end_match_22:;
    return match_7;
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

struct AArm_List* go_61(struct AArm_List* acc_5, struct AArm_List* xs_2) {
    struct AArm_List* match_8;
    if ((!((!(xs_2))))) goto next_26;
    match_8 = acc_5;
    goto end_match_25;
next_26:;
    if ((!(xs_2))) goto next_27;
    struct AArm_ x_3 = xs_2->head;
    struct AArm_List* xs_3 = xs_2->tail;
    struct AArm_List* list_5 = (struct AArm_List*)malloc(sizeof(struct AArm_List));
    list_5->head = x_3;
    list_5->tail = acc_5;
    struct AArm_List* call_10 = go_61(list_5, xs_3);
    match_8 = call_10;
    goto end_match_25;
next_27:;
    exit(1);
end_match_25:;
    return match_8;
}

struct StringList* go_60(struct StringList* acc_5, struct StringList* xs_2) {
    struct StringList* match_9;
    if ((!((!(xs_2))))) goto next_29;
    match_9 = acc_5;
    goto end_match_28;
next_29:;
    if ((!(xs_2))) goto next_30;
    struct String x_3 = xs_2->head;
    struct StringList* xs_3 = xs_2->tail;
    struct StringList* list_6 = (struct StringList*)malloc(sizeof(struct StringList));
    list_6->head = x_3;
    list_6->tail = acc_5;
    struct StringList* call_11 = go_60(list_6, xs_3);
    match_9 = call_11;
    goto end_match_28;
next_30:;
    exit(1);
end_match_28:;
    return match_9;
}

struct AExpr_List* go_59(struct AExpr_List* acc_5, struct AExpr_List* xs_2) {
    struct AExpr_List* match_10;
    if ((!((!(xs_2))))) goto next_32;
    match_10 = acc_5;
    goto end_match_31;
next_32:;
    if ((!(xs_2))) goto next_33;
    struct AExpr_ x_3 = xs_2->head;
    struct AExpr_List* xs_3 = xs_2->tail;
    struct AExpr_List* list_7 = (struct AExpr_List*)malloc(sizeof(struct AExpr_List));
    list_7->head = x_3;
    list_7->tail = acc_5;
    struct AExpr_List* call_12 = go_59(list_7, xs_3);
    match_10 = call_12;
    goto end_match_31;
next_33:;
    exit(1);
end_match_31:;
    return match_10;
}

struct DumpTree_List* go_74(struct DumpTree_List* acc_5, struct DumpTree_List* xs_2) {
    struct DumpTree_List* match_11;
    if ((!((!(xs_2))))) goto next_35;
    match_11 = acc_5;
    goto end_match_34;
next_35:;
    if ((!(xs_2))) goto next_36;
    struct DumpTree_ x_3 = xs_2->head;
    struct DumpTree_List* xs_3 = xs_2->tail;
    struct DumpTree_List* list_8 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_8->head = x_3;
    list_8->tail = acc_5;
    struct DumpTree_List* call_13 = go_74(list_8, xs_3);
    match_11 = call_13;
    goto end_match_34;
next_36:;
    exit(1);
end_match_34:;
    return match_11;
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

struct Ty_List* go_73(struct Ty_List* acc_5, struct Ty_List* xs_2) {
    struct Ty_List* match_12;
    if ((!((!(xs_2))))) goto next_38;
    match_12 = acc_5;
    goto end_match_37;
next_38:;
    if ((!(xs_2))) goto next_39;
    struct Ty_ x_3 = xs_2->head;
    struct Ty_List* xs_3 = xs_2->tail;
    struct Ty_List* list_9 = (struct Ty_List*)malloc(sizeof(struct Ty_List));
    list_9->head = x_3;
    list_9->tail = acc_5;
    struct Ty_List* call_14 = go_73(list_9, xs_3);
    match_12 = call_14;
    goto end_match_37;
next_39:;
    exit(1);
end_match_37:;
    return match_12;
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

struct HPat_HExpr_HExpr_Tuple3List* go_72(struct HPat_HExpr_HExpr_Tuple3List* acc_5, struct HPat_HExpr_HExpr_Tuple3List* xs_2) {
    struct HPat_HExpr_HExpr_Tuple3List* match_13;
    if ((!((!(xs_2))))) goto next_41;
    match_13 = acc_5;
    goto end_match_40;
next_41:;
    if ((!(xs_2))) goto next_42;
    struct HPat_HExpr_HExpr_Tuple3 x_3 = xs_2->head;
    struct HPat_HExpr_HExpr_Tuple3List* xs_3 = xs_2->tail;
    struct HPat_HExpr_HExpr_Tuple3List* list_10 = (struct HPat_HExpr_HExpr_Tuple3List*)malloc(sizeof(struct HPat_HExpr_HExpr_Tuple3List));
    list_10->head = x_3;
    list_10->tail = acc_5;
    struct HPat_HExpr_HExpr_Tuple3List* call_15 = go_72(list_10, xs_3);
    match_13 = call_15;
    goto end_match_40;
next_42:;
    exit(1);
end_match_40:;
    return match_13;
}

struct HExpr_List {
    struct HExpr_ head;
    struct HExpr_List* tail;
};

struct HExpr_List* go_71(struct HExpr_List* acc_5, struct HExpr_List* xs_2) {
    struct HExpr_List* match_14;
    if ((!((!(xs_2))))) goto next_44;
    match_14 = acc_5;
    goto end_match_43;
next_44:;
    if ((!(xs_2))) goto next_45;
    struct HExpr_ x_3 = xs_2->head;
    struct HExpr_List* xs_3 = xs_2->tail;
    struct HExpr_List* list_11 = (struct HExpr_List*)malloc(sizeof(struct HExpr_List));
    list_11->head = x_3;
    list_11->tail = acc_5;
    struct HExpr_List* call_16 = go_71(list_11, xs_3);
    match_14 = call_16;
    goto end_match_43;
next_45:;
    exit(1);
end_match_43:;
    return match_14;
}

struct HPat_List {
    struct HPat_ head;
    struct HPat_List* tail;
};

struct HPat_List* go_70(struct HPat_List* acc_5, struct HPat_List* xs_2) {
    struct HPat_List* match_15;
    if ((!((!(xs_2))))) goto next_47;
    match_15 = acc_5;
    goto end_match_46;
next_47:;
    if ((!(xs_2))) goto next_48;
    struct HPat_ x_3 = xs_2->head;
    struct HPat_List* xs_3 = xs_2->tail;
    struct HPat_List* list_12 = (struct HPat_List*)malloc(sizeof(struct HPat_List));
    list_12->head = x_3;
    list_12->tail = acc_5;
    struct HPat_List* call_17 = go_70(list_12, xs_3);
    match_15 = call_17;
    goto end_match_46;
next_48:;
    exit(1);
end_match_46:;
    return match_15;
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

struct StringIntBoolTy_Tuple4List* go_69(struct StringIntBoolTy_Tuple4List* acc_5, struct StringIntBoolTy_Tuple4List* xs_2) {
    struct StringIntBoolTy_Tuple4List* match_16;
    if ((!((!(xs_2))))) goto next_50;
    match_16 = acc_5;
    goto end_match_49;
next_50:;
    if ((!(xs_2))) goto next_51;
    struct StringIntBoolTy_Tuple4 x_3 = xs_2->head;
    struct StringIntBoolTy_Tuple4List* xs_3 = xs_2->tail;
    struct StringIntBoolTy_Tuple4List* list_13 = (struct StringIntBoolTy_Tuple4List*)malloc(sizeof(struct StringIntBoolTy_Tuple4List));
    list_13->head = x_3;
    list_13->tail = acc_5;
    struct StringIntBoolTy_Tuple4List* call_18 = go_69(list_13, xs_3);
    match_16 = call_18;
    goto end_match_49;
next_51:;
    exit(1);
end_match_49:;
    return match_16;
}

struct Token_List {
    struct Token_ head;
    struct Token_List* tail;
};

struct Token_List* go_75(struct Token_List* acc_5, struct Token_List* xs_2) {
    struct Token_List* match_17;
    if ((!((!(xs_2))))) goto next_53;
    match_17 = acc_5;
    goto end_match_52;
next_53:;
    if ((!(xs_2))) goto next_54;
    struct Token_ x_3 = xs_2->head;
    struct Token_List* xs_3 = xs_2->tail;
    struct Token_List* list_14 = (struct Token_List*)malloc(sizeof(struct Token_List));
    list_14->head = x_3;
    list_14->tail = acc_5;
    struct Token_List* call_19 = go_75(list_14, xs_3);
    match_17 = call_19;
    goto end_match_52;
next_54:;
    exit(1);
end_match_52:;
    return match_17;
}

struct Token_IntIntTuple2Tuple2List* listRev_7(struct Token_IntIntTuple2Tuple2List* xs_1) {
    struct Token_IntIntTuple2Tuple2List* call_20 = go_65(NULL, xs_1);
    return call_20;
}

struct ATy_List* listRev_6(struct ATy_List* xs_1) {
    struct ATy_List* call_21 = go_64(NULL, xs_1);
    return call_21;
}

struct AVariant_List* listRev_5(struct AVariant_List* xs_1) {
    struct AVariant_List* call_22 = go_63(NULL, xs_1);
    return call_22;
}

struct APat_List* listRev_4(struct APat_List* xs_1) {
    struct APat_List* call_23 = go_62(NULL, xs_1);
    return call_23;
}

struct AArm_List* listRev_3(struct AArm_List* xs_1) {
    struct AArm_List* call_24 = go_61(NULL, xs_1);
    return call_24;
}

struct StringList* listRev_2(struct StringList* xs_1) {
    struct StringList* call_25 = go_60(NULL, xs_1);
    return call_25;
}

struct AExpr_List* listRev_1(struct AExpr_List* xs_1) {
    struct AExpr_List* call_26 = go_59(NULL, xs_1);
    return call_26;
}

struct DumpTree_List* listRev_13(struct DumpTree_List* xs_1) {
    struct DumpTree_List* call_27 = go_74(NULL, xs_1);
    return call_27;
}

struct Ty_List* listRev_12(struct Ty_List* xs_1) {
    struct Ty_List* call_28 = go_73(NULL, xs_1);
    return call_28;
}

struct HPat_HExpr_HExpr_Tuple3List* listRev_11(struct HPat_HExpr_HExpr_Tuple3List* xs_1) {
    struct HPat_HExpr_HExpr_Tuple3List* call_29 = go_72(NULL, xs_1);
    return call_29;
}

struct HExpr_List* listRev_10(struct HExpr_List* xs_1) {
    struct HExpr_List* call_30 = go_71(NULL, xs_1);
    return call_30;
}

struct HPat_List* listRev_9(struct HPat_List* xs_1) {
    struct HPat_List* call_31 = go_70(NULL, xs_1);
    return call_31;
}

struct StringIntBoolTy_Tuple4List* listRev_8(struct StringIntBoolTy_Tuple4List* xs_1) {
    struct StringIntBoolTy_Tuple4List* call_32 = go_69(NULL, xs_1);
    return call_32;
}

struct Token_List* listRev_14(struct Token_List* xs_1) {
    struct Token_List* call_33 = go_75(NULL, xs_1);
    return call_33;
}

int go_58(int len_, struct StringList* xs_5) {
    int match_18;
    if ((!((!(xs_5))))) goto next_56;
    match_18 = len_;
    goto end_match_55;
next_56:;
    if ((!(xs_5))) goto next_57;
    struct StringList* xs_6 = xs_5->tail;
    int call_34 = go_58((len_ + 1), xs_6);
    match_18 = call_34;
    goto end_match_55;
next_57:;
    exit(1);
end_match_55:;
    return match_18;
}

int listLength_1(struct StringList* xs_4) {
    int call_35 = go_58(0, xs_4);
    return call_35;
}

struct Token_IntIntTuple2Tuple2UnitFun1 {
    int(*fun)(void*, struct Token_IntIntTuple2Tuple2);
    void* env;
};

int listIter_2(struct Token_IntIntTuple2Tuple2UnitFun1 f_, struct Token_IntIntTuple2Tuple2List* xs_7) {
    int match_19;
    if ((!((!(xs_7))))) goto next_59;
    match_19 = 0;
    goto end_match_58;
next_59:;
    if ((!(xs_7))) goto next_60;
    struct Token_IntIntTuple2Tuple2 x_4 = xs_7->head;
    struct Token_IntIntTuple2Tuple2List* xs_8 = xs_7->tail;
    int app_1 = f_.fun(f_.env, x_4);
    int call_36 = listIter_2(f_, xs_8);
    match_19 = 0;
    goto end_match_58;
next_60:;
    exit(1);
end_match_58:;
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
    int match_20;
    if ((!((!(xs_7))))) goto next_62;
    match_20 = 0;
    goto end_match_61;
next_62:;
    if ((!(xs_7))) goto next_63;
    struct StringIntIntTuple2Tuple2 x_4 = xs_7->head;
    struct StringIntIntTuple2Tuple2List* xs_8 = xs_7->tail;
    int app_2 = f_.fun(f_.env, x_4);
    int call_37 = listIter_1(f_, xs_8);
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

struct Ty_List* go_57(struct HExpr_Ty_Fun1 f_1, struct Ty_List* acc_6, struct HExpr_List* xs_10) {
    struct Ty_List* match_21;
    if ((!((!(xs_10))))) goto next_65;
    struct Ty_List* call_38 = listRev_12(acc_6);
    match_21 = call_38;
    goto end_match_64;
next_65:;
    if ((!(xs_10))) goto next_66;
    struct HExpr_ x_5 = xs_10->head;
    struct HExpr_List* xs_11 = xs_10->tail;
    struct Ty_ app_3 = f_1.fun(f_1.env, x_5);
    struct Ty_List* list_15 = (struct Ty_List*)malloc(sizeof(struct Ty_List));
    list_15->head = app_3;
    list_15->tail = acc_6;
    struct Ty_List* call_39 = go_57(f_1, list_15, xs_11);
    match_21 = call_39;
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

struct HPat_HExpr_HExpr_Tuple3List* go_56(struct HPat_HExpr_HExpr_Tuple3HPat_HExpr_HExpr_Tuple3Fun1 f_1, struct HPat_HExpr_HExpr_Tuple3List* acc_6, struct HPat_HExpr_HExpr_Tuple3List* xs_10) {
    struct HPat_HExpr_HExpr_Tuple3List* match_22;
    if ((!((!(xs_10))))) goto next_68;
    struct HPat_HExpr_HExpr_Tuple3List* call_40 = listRev_11(acc_6);
    match_22 = call_40;
    goto end_match_67;
next_68:;
    if ((!(xs_10))) goto next_69;
    struct HPat_HExpr_HExpr_Tuple3 x_5 = xs_10->head;
    struct HPat_HExpr_HExpr_Tuple3List* xs_11 = xs_10->tail;
    struct HPat_HExpr_HExpr_Tuple3 app_4 = f_1.fun(f_1.env, x_5);
    struct HPat_HExpr_HExpr_Tuple3List* list_16 = (struct HPat_HExpr_HExpr_Tuple3List*)malloc(sizeof(struct HPat_HExpr_HExpr_Tuple3List));
    list_16->head = app_4;
    list_16->tail = acc_6;
    struct HPat_HExpr_HExpr_Tuple3List* call_41 = go_56(f_1, list_16, xs_11);
    match_22 = call_41;
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

struct HExpr_List* go_55(struct HExpr_HExpr_Fun1 f_1, struct HExpr_List* acc_6, struct HExpr_List* xs_10) {
    struct HExpr_List* match_23;
    if ((!((!(xs_10))))) goto next_71;
    struct HExpr_List* call_42 = listRev_10(acc_6);
    match_23 = call_42;
    goto end_match_70;
next_71:;
    if ((!(xs_10))) goto next_72;
    struct HExpr_ x_5 = xs_10->head;
    struct HExpr_List* xs_11 = xs_10->tail;
    struct HExpr_ app_5 = f_1.fun(f_1.env, x_5);
    struct HExpr_List* list_17 = (struct HExpr_List*)malloc(sizeof(struct HExpr_List));
    list_17->head = app_5;
    list_17->tail = acc_6;
    struct HExpr_List* call_43 = go_55(f_1, list_17, xs_11);
    match_23 = call_43;
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

struct HPat_List* go_54(struct HPat_HPat_Fun1 f_1, struct HPat_List* acc_6, struct HPat_List* xs_10) {
    struct HPat_List* match_24;
    if ((!((!(xs_10))))) goto next_74;
    struct HPat_List* call_44 = listRev_9(acc_6);
    match_24 = call_44;
    goto end_match_73;
next_74:;
    if ((!(xs_10))) goto next_75;
    struct HPat_ x_5 = xs_10->head;
    struct HPat_List* xs_11 = xs_10->tail;
    struct HPat_ app_6 = f_1.fun(f_1.env, x_5);
    struct HPat_List* list_18 = (struct HPat_List*)malloc(sizeof(struct HPat_List));
    list_18->head = app_6;
    list_18->tail = acc_6;
    struct HPat_List* call_45 = go_54(f_1, list_18, xs_11);
    match_24 = call_45;
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

struct DumpTree_List* go_53(struct ATy_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct ATy_List* xs_10) {
    struct DumpTree_List* match_25;
    if ((!((!(xs_10))))) goto next_77;
    struct DumpTree_List* call_46 = listRev_13(acc_6);
    match_25 = call_46;
    goto end_match_76;
next_77:;
    if ((!(xs_10))) goto next_78;
    struct ATy_ x_5 = xs_10->head;
    struct ATy_List* xs_11 = xs_10->tail;
    struct DumpTree_ app_7 = f_1.fun(f_1.env, x_5);
    struct DumpTree_List* list_19 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_19->head = app_7;
    list_19->tail = acc_6;
    struct DumpTree_List* call_47 = go_53(f_1, list_19, xs_11);
    match_25 = call_47;
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

struct DumpTree_List* go_52(struct AArm_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct AArm_List* xs_10) {
    struct DumpTree_List* match_26;
    if ((!((!(xs_10))))) goto next_80;
    struct DumpTree_List* call_48 = listRev_13(acc_6);
    match_26 = call_48;
    goto end_match_79;
next_80:;
    if ((!(xs_10))) goto next_81;
    struct AArm_ x_5 = xs_10->head;
    struct AArm_List* xs_11 = xs_10->tail;
    struct DumpTree_ app_8 = f_1.fun(f_1.env, x_5);
    struct DumpTree_List* list_20 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_20->head = app_8;
    list_20->tail = acc_6;
    struct DumpTree_List* call_49 = go_52(f_1, list_20, xs_11);
    match_26 = call_49;
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

struct DumpTree_List* go_51(struct APat_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct APat_List* xs_10) {
    struct DumpTree_List* match_27;
    if ((!((!(xs_10))))) goto next_83;
    struct DumpTree_List* call_50 = listRev_13(acc_6);
    match_27 = call_50;
    goto end_match_82;
next_83:;
    if ((!(xs_10))) goto next_84;
    struct APat_ x_5 = xs_10->head;
    struct APat_List* xs_11 = xs_10->tail;
    struct DumpTree_ app_9 = f_1.fun(f_1.env, x_5);
    struct DumpTree_List* list_21 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_21->head = app_9;
    list_21->tail = acc_6;
    struct DumpTree_List* call_51 = go_51(f_1, list_21, xs_11);
    match_27 = call_51;
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

struct DumpTree_List* go_50(struct AExpr_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct AExpr_List* xs_10) {
    struct DumpTree_List* match_28;
    if ((!((!(xs_10))))) goto next_86;
    struct DumpTree_List* call_52 = listRev_13(acc_6);
    match_28 = call_52;
    goto end_match_85;
next_86:;
    if ((!(xs_10))) goto next_87;
    struct AExpr_ x_5 = xs_10->head;
    struct AExpr_List* xs_11 = xs_10->tail;
    struct DumpTree_ app_10 = f_1.fun(f_1.env, x_5);
    struct DumpTree_List* list_22 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_22->head = app_10;
    list_22->tail = acc_6;
    struct DumpTree_List* call_53 = go_50(f_1, list_22, xs_11);
    match_28 = call_53;
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

struct DumpTree_List* go_49(struct AVariant_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct AVariant_List* xs_10) {
    struct DumpTree_List* match_29;
    if ((!((!(xs_10))))) goto next_89;
    struct DumpTree_List* call_54 = listRev_13(acc_6);
    match_29 = call_54;
    goto end_match_88;
next_89:;
    if ((!(xs_10))) goto next_90;
    struct AVariant_ x_5 = xs_10->head;
    struct AVariant_List* xs_11 = xs_10->tail;
    struct DumpTree_ app_11 = f_1.fun(f_1.env, x_5);
    struct DumpTree_List* list_23 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_23->head = app_11;
    list_23->tail = acc_6;
    struct DumpTree_List* call_55 = go_49(f_1, list_23, xs_11);
    match_29 = call_55;
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

struct DumpTree_List* go_48(struct HExpr_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct HExpr_List* xs_10) {
    struct DumpTree_List* match_30;
    if ((!((!(xs_10))))) goto next_92;
    struct DumpTree_List* call_56 = listRev_13(acc_6);
    match_30 = call_56;
    goto end_match_91;
next_92:;
    if ((!(xs_10))) goto next_93;
    struct HExpr_ x_5 = xs_10->head;
    struct HExpr_List* xs_11 = xs_10->tail;
    struct DumpTree_ app_12 = f_1.fun(f_1.env, x_5);
    struct DumpTree_List* list_24 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_24->head = app_12;
    list_24->tail = acc_6;
    struct DumpTree_List* call_57 = go_48(f_1, list_24, xs_11);
    match_30 = call_57;
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

struct DumpTree_List* go_47(struct StringDumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct StringList* xs_10) {
    struct DumpTree_List* match_31;
    if ((!((!(xs_10))))) goto next_95;
    struct DumpTree_List* call_58 = listRev_13(acc_6);
    match_31 = call_58;
    goto end_match_94;
next_95:;
    if ((!(xs_10))) goto next_96;
    struct String x_5 = xs_10->head;
    struct StringList* xs_11 = xs_10->tail;
    struct DumpTree_ app_13 = f_1.fun(f_1.env, x_5);
    struct DumpTree_List* list_25 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_25->head = app_13;
    list_25->tail = acc_6;
    struct DumpTree_List* call_59 = go_47(f_1, list_25, xs_11);
    match_31 = call_59;
    goto end_match_94;
next_96:;
    exit(1);
end_match_94:;
    return match_31;
}

struct Token_IntIntTuple2Tuple2Token_Fun1 {
    struct Token_(*fun)(void*, struct Token_IntIntTuple2Tuple2);
    void* env;
};

struct Token_List* go_68(struct Token_IntIntTuple2Tuple2Token_Fun1 f_1, struct Token_List* acc_6, struct Token_IntIntTuple2Tuple2List* xs_10) {
    struct Token_List* match_32;
    if ((!((!(xs_10))))) goto next_98;
    struct Token_List* call_60 = listRev_14(acc_6);
    match_32 = call_60;
    goto end_match_97;
next_98:;
    if ((!(xs_10))) goto next_99;
    struct Token_IntIntTuple2Tuple2 x_5 = xs_10->head;
    struct Token_IntIntTuple2Tuple2List* xs_11 = xs_10->tail;
    struct Token_ app_14 = f_1.fun(f_1.env, x_5);
    struct Token_List* list_26 = (struct Token_List*)malloc(sizeof(struct Token_List));
    list_26->head = app_14;
    list_26->tail = acc_6;
    struct Token_List* call_61 = go_68(f_1, list_26, xs_11);
    match_32 = call_61;
    goto end_match_97;
next_99:;
    exit(1);
end_match_97:;
    return match_32;
}

struct Ty_List* listMap_11(struct HExpr_Ty_Fun1 f_1, struct HExpr_List* xs_9) {
    struct Ty_List* call_62 = go_57(f_1, NULL, xs_9);
    return call_62;
}

struct HPat_HExpr_HExpr_Tuple3List* listMap_10(struct HPat_HExpr_HExpr_Tuple3HPat_HExpr_HExpr_Tuple3Fun1 f_1, struct HPat_HExpr_HExpr_Tuple3List* xs_9) {
    struct HPat_HExpr_HExpr_Tuple3List* call_63 = go_56(f_1, NULL, xs_9);
    return call_63;
}

struct HExpr_List* listMap_9(struct HExpr_HExpr_Fun1 f_1, struct HExpr_List* xs_9) {
    struct HExpr_List* call_64 = go_55(f_1, NULL, xs_9);
    return call_64;
}

struct HPat_List* listMap_8(struct HPat_HPat_Fun1 f_1, struct HPat_List* xs_9) {
    struct HPat_List* call_65 = go_54(f_1, NULL, xs_9);
    return call_65;
}

struct DumpTree_List* listMap_7(struct ATy_DumpTree_Fun1 f_1, struct ATy_List* xs_9) {
    struct DumpTree_List* call_66 = go_53(f_1, NULL, xs_9);
    return call_66;
}

struct DumpTree_List* listMap_6(struct AArm_DumpTree_Fun1 f_1, struct AArm_List* xs_9) {
    struct DumpTree_List* call_67 = go_52(f_1, NULL, xs_9);
    return call_67;
}

struct DumpTree_List* listMap_5(struct APat_DumpTree_Fun1 f_1, struct APat_List* xs_9) {
    struct DumpTree_List* call_68 = go_51(f_1, NULL, xs_9);
    return call_68;
}

struct DumpTree_List* listMap_4(struct AExpr_DumpTree_Fun1 f_1, struct AExpr_List* xs_9) {
    struct DumpTree_List* call_69 = go_50(f_1, NULL, xs_9);
    return call_69;
}

struct DumpTree_List* listMap_3(struct AVariant_DumpTree_Fun1 f_1, struct AVariant_List* xs_9) {
    struct DumpTree_List* call_70 = go_49(f_1, NULL, xs_9);
    return call_70;
}

struct DumpTree_List* listMap_2(struct HExpr_DumpTree_Fun1 f_1, struct HExpr_List* xs_9) {
    struct DumpTree_List* call_71 = go_48(f_1, NULL, xs_9);
    return call_71;
}

struct DumpTree_List* listMap_1(struct StringDumpTree_Fun1 f_1, struct StringList* xs_9) {
    struct DumpTree_List* call_72 = go_47(f_1, NULL, xs_9);
    return call_72;
}

struct Token_List* listMap_12(struct Token_IntIntTuple2Tuple2Token_Fun1 f_1, struct Token_IntIntTuple2Tuple2List* xs_9) {
    struct Token_List* call_73 = go_68(f_1, NULL, xs_9);
    return call_73;
}

struct Token_List* go_67(int count_1, struct Token_List* xs_13) {
    struct Token_List* match_33;
    if ((!((!(xs_13))))) goto next_101;
    match_33 = NULL;
    goto end_match_100;
next_101:;
    if ((0 < count_1)) goto next_102;
    match_33 = NULL;
    goto end_match_100;
next_102:;
    if ((!(xs_13))) goto next_103;
    struct Token_ x_6 = xs_13->head;
    struct Token_List* xs_14 = xs_13->tail;
    struct Token_List* call_74 = go_67((count_1 - 1), xs_14);
    struct Token_List* list_27 = (struct Token_List*)malloc(sizeof(struct Token_List));
    list_27->head = x_6;
    list_27->tail = call_74;
    match_33 = list_27;
    goto end_match_100;
next_103:;
    exit(1);
end_match_100:;
    return match_33;
}

struct Token_List* listTruncate_1(int count_, struct Token_List* xs_12) {
    struct Token_List* call_75 = go_67(count_, xs_12);
    return call_75;
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

struct Ty_ListNameCtx_Tuple2 go_46(struct ATy_NameCtx_Tuple2Ty_NameCtx_Tuple2Fun1 f_2, struct Ty_List* acc_7, struct ATy_ListNameCtx_Tuple2 arg_86) {
    struct ATy_List* xs_16 = arg_86.t0;
    struct NameCtx_ ctx_1 = arg_86.t1;
    struct Ty_ListNameCtx_Tuple2 match_34;
    if ((!((!(xs_16))))) goto next_105;
    struct Ty_List* call_76 = listRev_12(acc_7);
    struct Ty_ListNameCtx_Tuple2 tuple_;
    tuple_.t0 = call_76;
    tuple_.t1 = ctx_1;
    match_34 = tuple_;
    goto end_match_104;
next_105:;
    if ((!(xs_16))) goto next_106;
    struct ATy_ x_7 = xs_16->head;
    struct ATy_List* xs_17 = xs_16->tail;
    struct ATy_NameCtx_Tuple2 tuple_1;
    tuple_1.t0 = x_7;
    tuple_1.t1 = ctx_1;
    struct Ty_NameCtx_Tuple2 app_15 = f_2.fun(f_2.env, tuple_1);
    struct Ty_ y_2 = app_15.t0;
    struct NameCtx_ ctx_2 = app_15.t1;
    struct Ty_List* list_28 = (struct Ty_List*)malloc(sizeof(struct Ty_List));
    list_28->head = y_2;
    list_28->tail = acc_7;
    struct ATy_ListNameCtx_Tuple2 tuple_2;
    tuple_2.t0 = xs_17;
    tuple_2.t1 = ctx_2;
    struct Ty_ListNameCtx_Tuple2 call_77 = go_46(f_2, list_28, tuple_2);
    match_34 = call_77;
    goto end_match_104;
next_106:;
    exit(1);
end_match_104:;
    return match_34;
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

struct HPat_HExpr_HExpr_Tuple3ListNameCtx_Tuple2 go_45(struct AArm_NameCtx_Tuple2HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2Fun1 f_2, struct HPat_HExpr_HExpr_Tuple3List* acc_7, struct AArm_ListNameCtx_Tuple2 arg_87) {
    struct AArm_List* xs_16 = arg_87.t0;
    struct NameCtx_ ctx_1 = arg_87.t1;
    struct HPat_HExpr_HExpr_Tuple3ListNameCtx_Tuple2 match_35;
    if ((!((!(xs_16))))) goto next_108;
    struct HPat_HExpr_HExpr_Tuple3List* call_78 = listRev_11(acc_7);
    struct HPat_HExpr_HExpr_Tuple3ListNameCtx_Tuple2 tuple_3;
    tuple_3.t0 = call_78;
    tuple_3.t1 = ctx_1;
    match_35 = tuple_3;
    goto end_match_107;
next_108:;
    if ((!(xs_16))) goto next_109;
    struct AArm_ x_7 = xs_16->head;
    struct AArm_List* xs_17 = xs_16->tail;
    struct AArm_NameCtx_Tuple2 tuple_4;
    tuple_4.t0 = x_7;
    tuple_4.t1 = ctx_1;
    struct HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2 app_16 = f_2.fun(f_2.env, tuple_4);
    struct HPat_HExpr_HExpr_Tuple3 y_2 = app_16.t0;
    struct NameCtx_ ctx_2 = app_16.t1;
    struct HPat_HExpr_HExpr_Tuple3List* list_29 = (struct HPat_HExpr_HExpr_Tuple3List*)malloc(sizeof(struct HPat_HExpr_HExpr_Tuple3List));
    list_29->head = y_2;
    list_29->tail = acc_7;
    struct AArm_ListNameCtx_Tuple2 tuple_5;
    tuple_5.t0 = xs_17;
    tuple_5.t1 = ctx_2;
    struct HPat_HExpr_HExpr_Tuple3ListNameCtx_Tuple2 call_79 = go_45(f_2, list_29, tuple_5);
    match_35 = call_79;
    goto end_match_107;
next_109:;
    exit(1);
end_match_107:;
    return match_35;
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

struct HExpr_ListNameCtx_Tuple2 go_44(struct AExpr_NameCtx_Tuple2HExpr_NameCtx_Tuple2Fun1 f_2, struct HExpr_List* acc_7, struct AExpr_ListNameCtx_Tuple2 arg_88) {
    struct AExpr_List* xs_16 = arg_88.t0;
    struct NameCtx_ ctx_1 = arg_88.t1;
    struct HExpr_ListNameCtx_Tuple2 match_36;
    if ((!((!(xs_16))))) goto next_111;
    struct HExpr_List* call_80 = listRev_10(acc_7);
    struct HExpr_ListNameCtx_Tuple2 tuple_6;
    tuple_6.t0 = call_80;
    tuple_6.t1 = ctx_1;
    match_36 = tuple_6;
    goto end_match_110;
next_111:;
    if ((!(xs_16))) goto next_112;
    struct AExpr_ x_7 = xs_16->head;
    struct AExpr_List* xs_17 = xs_16->tail;
    struct AExpr_NameCtx_Tuple2 tuple_7;
    tuple_7.t0 = x_7;
    tuple_7.t1 = ctx_1;
    struct HExpr_NameCtx_Tuple2 app_17 = f_2.fun(f_2.env, tuple_7);
    struct HExpr_ y_2 = app_17.t0;
    struct NameCtx_ ctx_2 = app_17.t1;
    struct HExpr_List* list_30 = (struct HExpr_List*)malloc(sizeof(struct HExpr_List));
    list_30->head = y_2;
    list_30->tail = acc_7;
    struct AExpr_ListNameCtx_Tuple2 tuple_8;
    tuple_8.t0 = xs_17;
    tuple_8.t1 = ctx_2;
    struct HExpr_ListNameCtx_Tuple2 call_81 = go_44(f_2, list_30, tuple_8);
    match_36 = call_81;
    goto end_match_110;
next_112:;
    exit(1);
end_match_110:;
    return match_36;
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

struct HPat_ListNameCtx_Tuple2 go_43(struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1 f_2, struct HPat_List* acc_7, struct APat_ListNameCtx_Tuple2 arg_89) {
    struct APat_List* xs_16 = arg_89.t0;
    struct NameCtx_ ctx_1 = arg_89.t1;
    struct HPat_ListNameCtx_Tuple2 match_37;
    if ((!((!(xs_16))))) goto next_114;
    struct HPat_List* call_82 = listRev_9(acc_7);
    struct HPat_ListNameCtx_Tuple2 tuple_9;
    tuple_9.t0 = call_82;
    tuple_9.t1 = ctx_1;
    match_37 = tuple_9;
    goto end_match_113;
next_114:;
    if ((!(xs_16))) goto next_115;
    struct APat_ x_7 = xs_16->head;
    struct APat_List* xs_17 = xs_16->tail;
    struct APat_NameCtx_Tuple2 tuple_10;
    tuple_10.t0 = x_7;
    tuple_10.t1 = ctx_1;
    struct HPat_NameCtx_Tuple2 app_18 = f_2.fun(f_2.env, tuple_10);
    struct HPat_ y_2 = app_18.t0;
    struct NameCtx_ ctx_2 = app_18.t1;
    struct HPat_List* list_31 = (struct HPat_List*)malloc(sizeof(struct HPat_List));
    list_31->head = y_2;
    list_31->tail = acc_7;
    struct APat_ListNameCtx_Tuple2 tuple_11;
    tuple_11.t0 = xs_17;
    tuple_11.t1 = ctx_2;
    struct HPat_ListNameCtx_Tuple2 call_83 = go_43(f_2, list_31, tuple_11);
    match_37 = call_83;
    goto end_match_113;
next_115:;
    exit(1);
end_match_113:;
    return match_37;
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

struct StringIntBoolTy_Tuple4ListNameCtx_Tuple2 go_42(struct AVariant_NameCtx_Tuple2StringIntBoolTy_Tuple4NameCtx_Tuple2Fun1 f_2, struct StringIntBoolTy_Tuple4List* acc_7, struct AVariant_ListNameCtx_Tuple2 arg_90) {
    struct AVariant_List* xs_16 = arg_90.t0;
    struct NameCtx_ ctx_1 = arg_90.t1;
    struct StringIntBoolTy_Tuple4ListNameCtx_Tuple2 match_38;
    if ((!((!(xs_16))))) goto next_117;
    struct StringIntBoolTy_Tuple4List* call_84 = listRev_8(acc_7);
    struct StringIntBoolTy_Tuple4ListNameCtx_Tuple2 tuple_12;
    tuple_12.t0 = call_84;
    tuple_12.t1 = ctx_1;
    match_38 = tuple_12;
    goto end_match_116;
next_117:;
    if ((!(xs_16))) goto next_118;
    struct AVariant_ x_7 = xs_16->head;
    struct AVariant_List* xs_17 = xs_16->tail;
    struct AVariant_NameCtx_Tuple2 tuple_13;
    tuple_13.t0 = x_7;
    tuple_13.t1 = ctx_1;
    struct StringIntBoolTy_Tuple4NameCtx_Tuple2 app_19 = f_2.fun(f_2.env, tuple_13);
    struct StringIntBoolTy_Tuple4 y_2 = app_19.t0;
    struct NameCtx_ ctx_2 = app_19.t1;
    struct StringIntBoolTy_Tuple4List* list_32 = (struct StringIntBoolTy_Tuple4List*)malloc(sizeof(struct StringIntBoolTy_Tuple4List));
    list_32->head = y_2;
    list_32->tail = acc_7;
    struct AVariant_ListNameCtx_Tuple2 tuple_14;
    tuple_14.t0 = xs_17;
    tuple_14.t1 = ctx_2;
    struct StringIntBoolTy_Tuple4ListNameCtx_Tuple2 call_85 = go_42(f_2, list_32, tuple_14);
    match_38 = call_85;
    goto end_match_116;
next_118:;
    exit(1);
end_match_116:;
    return match_38;
}

struct Ty_ListNameCtx_Tuple2 stMap_5(struct ATy_NameCtx_Tuple2Ty_NameCtx_Tuple2Fun1 f_2, struct ATy_ListNameCtx_Tuple2 arg_91) {
    struct ATy_List* xs_15 = arg_91.t0;
    struct NameCtx_ ctx_ = arg_91.t1;
    struct ATy_ListNameCtx_Tuple2 tuple_15;
    tuple_15.t0 = xs_15;
    tuple_15.t1 = ctx_;
    struct Ty_ListNameCtx_Tuple2 call_86 = go_46(f_2, NULL, tuple_15);
    return call_86;
}

struct HPat_HExpr_HExpr_Tuple3ListNameCtx_Tuple2 stMap_4(struct AArm_NameCtx_Tuple2HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2Fun1 f_2, struct AArm_ListNameCtx_Tuple2 arg_92) {
    struct AArm_List* xs_15 = arg_92.t0;
    struct NameCtx_ ctx_ = arg_92.t1;
    struct AArm_ListNameCtx_Tuple2 tuple_16;
    tuple_16.t0 = xs_15;
    tuple_16.t1 = ctx_;
    struct HPat_HExpr_HExpr_Tuple3ListNameCtx_Tuple2 call_87 = go_45(f_2, NULL, tuple_16);
    return call_87;
}

struct HExpr_ListNameCtx_Tuple2 stMap_3(struct AExpr_NameCtx_Tuple2HExpr_NameCtx_Tuple2Fun1 f_2, struct AExpr_ListNameCtx_Tuple2 arg_93) {
    struct AExpr_List* xs_15 = arg_93.t0;
    struct NameCtx_ ctx_ = arg_93.t1;
    struct AExpr_ListNameCtx_Tuple2 tuple_17;
    tuple_17.t0 = xs_15;
    tuple_17.t1 = ctx_;
    struct HExpr_ListNameCtx_Tuple2 call_88 = go_44(f_2, NULL, tuple_17);
    return call_88;
}

struct HPat_ListNameCtx_Tuple2 stMap_2(struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1 f_2, struct APat_ListNameCtx_Tuple2 arg_94) {
    struct APat_List* xs_15 = arg_94.t0;
    struct NameCtx_ ctx_ = arg_94.t1;
    struct APat_ListNameCtx_Tuple2 tuple_18;
    tuple_18.t0 = xs_15;
    tuple_18.t1 = ctx_;
    struct HPat_ListNameCtx_Tuple2 call_89 = go_43(f_2, NULL, tuple_18);
    return call_89;
}

struct StringIntBoolTy_Tuple4ListNameCtx_Tuple2 stMap_1(struct AVariant_NameCtx_Tuple2StringIntBoolTy_Tuple4NameCtx_Tuple2Fun1 f_2, struct AVariant_ListNameCtx_Tuple2 arg_95) {
    struct AVariant_List* xs_15 = arg_95.t0;
    struct NameCtx_ ctx_ = arg_95.t1;
    struct AVariant_ListNameCtx_Tuple2 tuple_19;
    tuple_19.t0 = xs_15;
    tuple_19.t1 = ctx_;
    struct StringIntBoolTy_Tuple4ListNameCtx_Tuple2 call_90 = go_42(f_2, NULL, tuple_19);
    return call_90;
}

int intMin_(int x_8, int y_3) {
    int match_39;
    if ((y_3 >= x_8)) goto next_120;
    match_39 = y_3;
    goto end_match_119;
next_120:;
    if ((y_3 < x_8)) goto next_121;
    match_39 = x_8;
    goto end_match_119;
next_121:;
    exit(1);
end_match_119:;
    return match_39;
}

int intMax_(int x_9, int y_4) {
    int match_40;
    if ((x_9 >= y_4)) goto next_123;
    match_40 = y_4;
    goto end_match_122;
next_123:;
    if ((x_9 < y_4)) goto next_124;
    match_40 = x_9;
    goto end_match_122;
next_124:;
    exit(1);
end_match_122:;
    return match_40;
}

int intEq_(int x_10, int y_5) {
    return (x_10 == y_5);
}

struct String go_17(struct String acc_8, int len_2, int n_) {
    struct String match_41;
    int match_42;
    if ((n_ != 0)) goto next_127;
    match_42 = (0 >= len_2);
    goto end_match_126;
next_127:;
    if ((n_ == 0)) goto next_128;
    match_42 = 0;
    goto end_match_126;
next_128:;
    exit(1);
end_match_126:;
    if ((!(match_42))) goto next_129;
    match_41 = acc_8;
    goto end_match_125;
next_129:;
    if (match_42) goto next_130;
    int d_ = (n_ % 16);
    struct String call_91 = strSlice_(d_, (d_ + 1), (struct String){.str = "0123456789abcdef", .len = 16});
    struct String s_3 = call_91;
    struct String call_92 = go_17(str_add(s_3, acc_8), (len_2 - 1), (n_ / 16));
    match_41 = call_92;
    goto end_match_125;
next_130:;
    exit(1);
end_match_125:;
    return match_41;
}

struct String intToHexWithPadding_(int len_1, int value_3) {
    struct String match_43;
    if ((value_3 >= 0)) goto next_132;
    struct String call_93 = failwith_3((struct String){.str = "intToHexWithPadding: unimplemented negative", .len = 43});
    match_43 = call_93;
    goto end_match_131;
next_132:;
    if ((value_3 < 0)) goto next_133;
    milone_assert((len_1 >= 0), 100, 2);
    int call_94 = 0;
    struct String match_44;
    int match_45;
    if ((value_3 != 0)) goto next_136;
    match_45 = (len_1 == 0);
    goto end_match_135;
next_136:;
    if ((value_3 == 0)) goto next_137;
    match_45 = 0;
    goto end_match_135;
next_137:;
    exit(1);
end_match_135:;
    if ((!(match_45))) goto next_138;
    match_44 = (struct String){.str = "0", .len = 1};
    goto end_match_134;
next_138:;
    if (match_45) goto next_139;
    struct String call_95 = go_17((struct String){.str = "", .len = 0}, len_1, value_3);
    match_44 = call_95;
    goto end_match_134;
next_139:;
    exit(1);
end_match_134:;
    match_43 = match_44;
    goto end_match_131;
next_133:;
    exit(1);
end_match_131:;
    return match_43;
}

int hexDigitToInt_(char c_5) {
    int match_46;
    int match_47;
    if ((c_5 < '0')) goto next_142;
    match_47 = ('9' >= c_5);
    goto end_match_141;
next_142:;
    if ((c_5 >= '0')) goto next_143;
    match_47 = 0;
    goto end_match_141;
next_143:;
    exit(1);
end_match_141:;
    if ((!(match_47))) goto next_144;
    int call_96 = charSub_(c_5, '0');
    match_46 = call_96;
    goto end_match_140;
next_144:;
    if (match_47) goto next_145;
    int match_48;
    int match_49;
    if ((c_5 < 'A')) goto next_148;
    match_49 = ('F' >= c_5);
    goto end_match_147;
next_148:;
    if ((c_5 >= 'A')) goto next_149;
    match_49 = 0;
    goto end_match_147;
next_149:;
    exit(1);
end_match_147:;
    if ((!(match_49))) goto next_150;
    int call_97 = charSub_(c_5, 'A');
    match_48 = (call_97 + 10);
    goto end_match_146;
next_150:;
    if (match_49) goto next_151;
    int match_50;
    int match_51;
    if ((c_5 < 'a')) goto next_154;
    match_51 = ('f' >= c_5);
    goto end_match_153;
next_154:;
    if ((c_5 >= 'a')) goto next_155;
    match_51 = 0;
    goto end_match_153;
next_155:;
    exit(1);
end_match_153:;
    if ((!(match_51))) goto next_156;
    int call_98 = charSub_(c_5, 'a');
    match_50 = (call_98 + 10);
    goto end_match_152;
next_156:;
    if (match_51) goto next_157;
    milone_assert(0, 126, 6);
    int call_99 = 0;
    match_50 = 0;
    goto end_match_152;
next_157:;
    exit(1);
end_match_152:;
    match_48 = match_50;
    goto end_match_146;
next_151:;
    exit(1);
end_match_146:;
    match_46 = match_48;
    goto end_match_140;
next_145:;
    exit(1);
end_match_140:;
    return match_46;
}

int go_18(struct String s_4, int r_20, int acc_9, int i_50) {
    int match_52;
    if ((i_50 != r_20)) goto next_159;
    match_52 = acc_9;
    goto end_match_158;
next_159:;
    if ((i_50 == r_20)) goto next_160;
    int call_100 = hexDigitToInt_(s_4.str[i_50]);
    int d_1 = call_100;
    int call_101 = go_18(s_4, r_20, ((acc_9 * 16) + d_1), (i_50 + 1));
    match_52 = call_101;
    goto end_match_158;
next_160:;
    exit(1);
end_match_158:;
    return match_52;
}

int intFromHex_(int l_8, int r_20, struct String s_4) {
    int match_53;
    int match_54;
    if ((l_8 < 0)) goto next_163;
    match_54 = (l_8 < r_20);
    goto end_match_162;
next_163:;
    if ((l_8 >= 0)) goto next_164;
    match_54 = 0;
    goto end_match_162;
next_164:;
    exit(1);
end_match_162:;
    if ((!(match_54))) goto next_165;
    match_53 = (s_4.len >= r_20);
    goto end_match_161;
next_165:;
    if (match_54) goto next_166;
    match_53 = 0;
    goto end_match_161;
next_166:;
    exit(1);
end_match_161:;
    milone_assert(match_53, 116, 2);
    int call_102 = 0;
    int call_103 = go_18(s_4, r_20, 0, l_8);
    return call_103;
}

int charSub_(char x_11, char y_6) {
    int call_104 = ((int)x_11);
    int call_105 = ((int)y_6);
    return (call_104 - call_105);
}

int charIsControl_(char c_6) {
    int call_106 = ((int)c_6);
    int n_1 = call_106;
    int match_55;
    int match_56;
    if ((n_1 < 0)) goto next_169;
    match_56 = (n_1 < 32);
    goto end_match_168;
next_169:;
    if ((n_1 >= 0)) goto next_170;
    match_56 = 0;
    goto end_match_168;
next_170:;
    exit(1);
end_match_168:;
    if ((!(match_56))) goto next_171;
    match_55 = 1;
    goto end_match_167;
next_171:;
    if (match_56) goto next_172;
    match_55 = (n_1 == 127);
    goto end_match_167;
next_172:;
    exit(1);
end_match_167:;
    return match_55;
}

int charIsSpace_(char c_7) {
    int match_57;
    int match_58;
    int match_59;
    if ((c_7 != ' ')) goto next_176;
    match_59 = 1;
    goto end_match_175;
next_176:;
    if ((c_7 == ' ')) goto next_177;
    match_59 = (c_7 == '\t');
    goto end_match_175;
next_177:;
    exit(1);
end_match_175:;
    if ((!(match_59))) goto next_178;
    match_58 = 1;
    goto end_match_174;
next_178:;
    if (match_59) goto next_179;
    match_58 = (c_7 == '\r');
    goto end_match_174;
next_179:;
    exit(1);
end_match_174:;
    if ((!(match_58))) goto next_180;
    match_57 = 1;
    goto end_match_173;
next_180:;
    if (match_58) goto next_181;
    match_57 = (c_7 == '\n');
    goto end_match_173;
next_181:;
    exit(1);
end_match_173:;
    return match_57;
}

int charIsDigit_(char c_8) {
    int match_60;
    if ((c_8 < '0')) goto next_183;
    match_60 = ('9' >= c_8);
    goto end_match_182;
next_183:;
    if ((c_8 >= '0')) goto next_184;
    match_60 = 0;
    goto end_match_182;
next_184:;
    exit(1);
end_match_182:;
    return match_60;
}

int charIsAlpha_(char c_9) {
    int match_61;
    int match_62;
    if ((c_9 < 'A')) goto next_187;
    match_62 = ('Z' >= c_9);
    goto end_match_186;
next_187:;
    if ((c_9 >= 'A')) goto next_188;
    match_62 = 0;
    goto end_match_186;
next_188:;
    exit(1);
end_match_186:;
    if ((!(match_62))) goto next_189;
    match_61 = 1;
    goto end_match_185;
next_189:;
    if (match_62) goto next_190;
    int match_63;
    if ((c_9 < 'a')) goto next_192;
    match_63 = ('z' >= c_9);
    goto end_match_191;
next_192:;
    if ((c_9 >= 'a')) goto next_193;
    match_63 = 0;
    goto end_match_191;
next_193:;
    exit(1);
end_match_191:;
    match_61 = match_63;
    goto end_match_185;
next_190:;
    exit(1);
end_match_185:;
    return match_61;
}

int charNeedsEscaping_(char c_10) {
    int match_64;
    int match_65;
    int match_66;
    int call_107 = charIsControl_(c_10);
    if ((!(call_107))) goto next_197;
    match_66 = 1;
    goto end_match_196;
next_197:;
    if (call_107) goto next_198;
    match_66 = (c_10 == '\\');
    goto end_match_196;
next_198:;
    exit(1);
end_match_196:;
    if ((!(match_66))) goto next_199;
    match_65 = 1;
    goto end_match_195;
next_199:;
    if (match_66) goto next_200;
    match_65 = (c_10 == '\"');
    goto end_match_195;
next_200:;
    exit(1);
end_match_195:;
    if ((!(match_65))) goto next_201;
    match_64 = 1;
    goto end_match_194;
next_201:;
    if (match_65) goto next_202;
    match_64 = (c_10 == '\'');
    goto end_match_194;
next_202:;
    exit(1);
end_match_194:;
    return match_64;
}

struct String charEscape_(char c_11) {
    int call_108 = charNeedsEscaping_(c_11);
    milone_assert(call_108, 162, 2);
    int call_109 = 0;
    struct String match_67;
    if ((c_11 != '\0')) goto next_204;
    match_67 = (struct String){.str = "\\0", .len = 2};
    goto end_match_203;
next_204:;
    if ((c_11 != '\t')) goto next_205;
    match_67 = (struct String){.str = "\\t", .len = 2};
    goto end_match_203;
next_205:;
    if ((c_11 != '\n')) goto next_206;
    match_67 = (struct String){.str = "\\n", .len = 2};
    goto end_match_203;
next_206:;
    if ((c_11 != '\r')) goto next_207;
    match_67 = (struct String){.str = "\\r", .len = 2};
    goto end_match_203;
next_207:;
    if ((c_11 != '\'')) goto next_208;
    match_67 = (struct String){.str = "\\\'", .len = 2};
    goto end_match_203;
next_208:;
    if ((c_11 != '\"')) goto next_209;
    match_67 = (struct String){.str = "\\\"", .len = 2};
    goto end_match_203;
next_209:;
    if ((c_11 != '\\')) goto next_210;
    match_67 = (struct String){.str = "\\\\", .len = 2};
    goto end_match_203;
next_210:;
    char c_12 = c_11;
    int call_110 = ((int)c_12);
    struct String call_111 = intToHexWithPadding_(2, call_110);
    struct String h_ = call_111;
    match_67 = str_add((struct String){.str = "\\x", .len = 2}, h_);
    goto end_match_203;
next_211:;
end_match_203:;
    return match_67;
}

struct String strSlice_(int start_, int endIndex_1, struct String s_5) {
    int match_68;
    if ((endIndex_1 < start_)) goto next_213;
    match_68 = (s_5.len >= endIndex_1);
    goto end_match_212;
next_213:;
    if ((endIndex_1 >= start_)) goto next_214;
    match_68 = 0;
    goto end_match_212;
next_214:;
    exit(1);
end_match_212:;
    milone_assert(match_68, 196, 2);
    int call_112 = 0;
    struct String match_69;
    if ((start_ < endIndex_1)) goto next_216;
    match_69 = (struct String){.str = "", .len = 0};
    goto end_match_215;
next_216:;
    if ((start_ >= endIndex_1)) goto next_217;
    struct String call_113 = str_get_slice(start_, (endIndex_1 - 1), s_5);
    match_69 = call_113;
    goto end_match_215;
next_217:;
    exit(1);
end_match_215:;
    return match_69;
}

struct StringStringListTuple2 {
    struct String t0;
    struct StringList* t1;
};

struct StringStringListTuple2 go_19(struct StringList* xs_19, int xn_) {
    struct StringStringListTuple2 match_70;
    if ((!((!(xs_19))))) goto next_219;
    milone_assert((xn_ == 0), 210, 6);
    int call_114 = 0;
    struct StringStringListTuple2 tuple_20;
    tuple_20.t0 = (struct String){.str = "", .len = 0};
    tuple_20.t1 = NULL;
    match_70 = tuple_20;
    goto end_match_218;
next_219:;
    if ((!(xs_19))) goto next_220;
    struct String x_12 = xs_19->head;
    struct StringList* xs_20 = xs_19->tail;
    if ((xn_ != 1)) goto next_220;
    struct StringStringListTuple2 tuple_21;
    tuple_21.t0 = x_12;
    tuple_21.t1 = xs_20;
    match_70 = tuple_21;
    goto end_match_218;
next_220:;
    if ((!(xs_19))) goto next_221;
    struct String x_13 = xs_19->head;
    if ((!(xs_19->tail))) goto next_221;
    struct String y_7 = xs_19->tail->head;
    struct StringList* xs_21 = xs_19->tail->tail;
    if ((xn_ != 2)) goto next_221;
    struct StringStringListTuple2 tuple_22;
    tuple_22.t0 = str_add(x_13, y_7);
    tuple_22.t1 = xs_21;
    match_70 = tuple_22;
    goto end_match_218;
next_221:;
    struct StringList* xs_22 = xs_19;
    int m_ = (xn_ / 2);
    struct StringStringListTuple2 call_115 = go_19(xs_22, m_);
    struct String l_9 = call_115.t0;
    struct StringList* xs_23 = call_115.t1;
    struct StringStringListTuple2 call_116 = go_19(xs_23, (xn_ - m_));
    struct String r_21 = call_116.t0;
    struct StringList* xs_24 = call_116.t1;
    struct StringStringListTuple2 tuple_23;
    tuple_23.t0 = str_add(l_9, r_21);
    tuple_23.t1 = xs_24;
    match_70 = tuple_23;
    goto end_match_218;
next_222:;
end_match_218:;
    return match_70;
}

struct String strConcat_(struct StringList* xs_18) {
    int call_117 = listLength_1(xs_18);
    int n_2 = call_117;
    struct StringStringListTuple2 call_118 = go_19(xs_18, n_2);
    struct String s_6 = call_118.t0;
    struct StringList* xs_25 = call_118.t1;
    int call_119 = listIsEmpty_4(xs_25);
    milone_assert(call_119, 223, 2);
    int call_120 = 0;
    return s_6;
}

int go_20(struct String str_2, int i_51) {
    int match_71;
    if ((i_51 >= str_2.len)) goto next_224;
    int match_72;
    int call_121 = charNeedsEscaping_(str_2.str[i_51]);
    if ((!(call_121))) goto next_227;
    match_72 = 1;
    goto end_match_226;
next_227:;
    if (call_121) goto next_228;
    int call_122 = go_20(str_2, (i_51 + 1));
    match_72 = call_122;
    goto end_match_226;
next_228:;
    exit(1);
end_match_226:;
    match_71 = match_72;
    goto end_match_223;
next_224:;
    if ((i_51 < str_2.len)) goto next_225;
    match_71 = 0;
    goto end_match_223;
next_225:;
    exit(1);
end_match_223:;
    return match_71;
}

int strNeedsEscaping_(struct String str_2) {
    int call_123 = go_20(str_2, 0);
    return call_123;
}

int raw_(struct String str_3, int i_53) {
    int match_73;
    int match_74;
    if ((i_53 != str_3.len)) goto next_231;
    match_74 = 1;
    goto end_match_230;
next_231:;
    if ((i_53 == str_3.len)) goto next_232;
    int call_124 = charNeedsEscaping_(str_3.str[i_53]);
    match_74 = call_124;
    goto end_match_230;
next_232:;
    exit(1);
end_match_230:;
    if ((!(match_74))) goto next_233;
    match_73 = i_53;
    goto end_match_229;
next_233:;
    if (match_74) goto next_234;
    int call_125 = raw_(str_3, (i_53 + 1));
    match_73 = call_125;
    goto end_match_229;
next_234:;
    exit(1);
end_match_229:;
    return match_73;
}

struct IntStringListTuple2 {
    int t0;
    struct StringList* t1;
};

struct StringList* go_21(struct String str_3, struct StringList* acc_10, int i_52) {
    int call_126 = raw_(str_3, i_52);
    int r_22 = call_126;
    struct String call_127 = strSlice_(i_52, r_22, str_3);
    struct StringList* list_33 = (struct StringList*)malloc(sizeof(struct StringList));
    list_33->head = call_127;
    list_33->tail = acc_10;
    struct IntStringListTuple2 tuple_24;
    tuple_24.t0 = r_22;
    tuple_24.t1 = list_33;
    int i_54 = tuple_24.t0;
    struct StringList* acc_11 = tuple_24.t1;
    struct StringList* match_75;
    if ((i_54 != str_3.len)) goto next_236;
    match_75 = acc_11;
    goto end_match_235;
next_236:;
    if ((i_54 == str_3.len)) goto next_237;
    struct String call_128 = charEscape_(str_3.str[i_54]);
    struct String t_11 = call_128;
    struct StringList* list_34 = (struct StringList*)malloc(sizeof(struct StringList));
    list_34->head = t_11;
    list_34->tail = acc_11;
    struct StringList* call_129 = go_21(str_3, list_34, (i_54 + 1));
    match_75 = call_129;
    goto end_match_235;
next_237:;
    exit(1);
end_match_235:;
    return match_75;
}

struct String strEscape_(struct String str_3) {
    struct String match_76;
    int call_130 = strNeedsEscaping_(str_3);
    if (call_130) goto next_239;
    match_76 = str_3;
    goto end_match_238;
next_239:;
    if ((!(call_130))) goto next_240;
    struct StringList* call_131 = go_21(str_3, NULL, 0);
    struct StringList* call_132 = listRev_2(call_131);
    struct String call_133 = strConcat_(call_132);
    match_76 = call_133;
    goto end_match_238;
next_240:;
    exit(1);
end_match_238:;
    return match_76;
}

int locX_(struct IntIntTuple2 arg_96) {
    int x_14 = arg_96.t1;
    return x_14;
}

int locY_(struct IntIntTuple2 arg_97) {
    int y_8 = arg_97.t0;
    return y_8;
}

int locIsSameRow_(struct IntIntTuple2 first_, struct IntIntTuple2 second_) {
    int call_134 = locY_(first_);
    int call_135 = locY_(second_);
    return (call_134 == call_135);
}

int locIsSameColumn_(struct IntIntTuple2 first_1, struct IntIntTuple2 second_1) {
    int call_136 = locX_(first_1);
    int call_137 = locX_(second_1);
    return (call_136 == call_137);
}

int locInside_(struct IntIntTuple2 firstLoc_, struct IntIntTuple2 secondLoc_) {
    int call_138 = locX_(secondLoc_);
    int call_139 = locX_(firstLoc_);
    return (call_138 >= call_139);
}

struct IntIntTuple2 locAddX_(int dx_, struct IntIntTuple2 arg_98) {
    int y_9 = arg_98.t0;
    int x_15 = arg_98.t1;
    struct IntIntTuple2 tuple_25;
    tuple_25.t0 = y_9;
    tuple_25.t1 = (x_15 + dx_);
    return tuple_25;
}

struct IntIntTuple2 locMax_(struct IntIntTuple2 arg_99, struct IntIntTuple2 arg_100) {
    int firstY_ = arg_99.t0;
    int firstX_ = arg_99.t1;
    int secondY_ = arg_100.t0;
    int secondX_ = arg_100.t1;
    int call_140 = intMax_(firstY_, secondY_);
    int call_141 = intMax_(firstX_, secondX_);
    struct IntIntTuple2 tuple_26;
    tuple_26.t0 = call_140;
    tuple_26.t1 = call_141;
    return tuple_26;
}

int tokenIsExprOrPatFirst_(struct Token_ token_7) {
    int match_77;
    if ((token_7.tag != Bool_1)) goto next_243;
    goto match_body_242;
next_243:;
    if ((token_7.tag != Int_1)) goto next_244;
    goto match_body_242;
next_244:;
    if ((token_7.tag != Char_1)) goto next_245;
    goto match_body_242;
next_245:;
    if ((token_7.tag != Str_1)) goto next_246;
    goto match_body_242;
next_246:;
    if ((token_7.tag != Ident_)) goto next_247;
    goto match_body_242;
next_247:;
    if ((token_7.tag != ParenL_)) goto next_248;
    goto match_body_242;
next_248:;
    if ((token_7.tag != BracketL_)) goto next_249;
    goto match_body_242;
match_body_242:;
    match_77 = 1;
    goto end_match_241;
next_249:;
    match_77 = 0;
    goto end_match_241;
next_250:;
end_match_241:;
    return match_77;
}

int tokenIsExprFirst_(struct Token_ token_8) {
    int match_78;
    int call_142 = tokenIsExprOrPatFirst_(token_8);
    if ((!(call_142))) goto next_253;
    match_78 = 1;
    goto end_match_251;
next_253:;
    if ((token_8.tag != Minus_)) goto next_254;
    goto match_body_252;
next_254:;
    if ((token_8.tag != If_)) goto next_255;
    goto match_body_252;
next_255:;
    if ((token_8.tag != Match_)) goto next_256;
    goto match_body_252;
next_256:;
    if ((token_8.tag != Fun_)) goto next_257;
    goto match_body_252;
next_257:;
    if ((token_8.tag != Do_)) goto next_258;
    goto match_body_252;
next_258:;
    if ((token_8.tag != Let_)) goto next_259;
    goto match_body_252;
next_259:;
    if ((token_8.tag != Type_)) goto next_260;
    goto match_body_252;
next_260:;
    if ((token_8.tag != Open_)) goto next_261;
    goto match_body_252;
match_body_252:;
    match_78 = 1;
    goto end_match_251;
next_261:;
    match_78 = 0;
    goto end_match_251;
next_262:;
end_match_251:;
    return match_78;
}

int tokenIsArgFirst_(struct Token_ token_9) {
    int match_79;
    if ((token_9.tag != Minus_)) goto next_264;
    match_79 = 0;
    goto end_match_263;
next_264:;
    int call_143 = tokenIsExprFirst_(token_9);
    match_79 = call_143;
    goto end_match_263;
next_265:;
end_match_263:;
    return match_79;
}

int tokenIsPatFirst_(struct Token_ token_10) {
    int call_144 = tokenIsExprOrPatFirst_(token_10);
    return call_144;
}

int tokenIsAccessModifier_(struct Token_ token_11) {
    int match_80;
    if ((token_11.tag != Private_)) goto next_268;
    goto match_body_267;
next_268:;
    if ((token_11.tag != Internal_)) goto next_269;
    goto match_body_267;
next_269:;
    if ((token_11.tag != Public_)) goto next_270;
    goto match_body_267;
match_body_267:;
    match_80 = 1;
    goto end_match_266;
next_270:;
    match_80 = 0;
    goto end_match_266;
next_271:;
end_match_266:;
    return match_80;
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
    struct OpLevel_ match_81;
    if ((level_.tag != Or_)) goto next_273;
    match_81 = (struct OpLevel_){.tag = And_};
    goto end_match_272;
next_273:;
    if ((level_.tag != And_)) goto next_274;
    match_81 = (struct OpLevel_){.tag = Cmp_};
    goto end_match_272;
next_274:;
    if ((level_.tag != Cmp_)) goto next_275;
    match_81 = (struct OpLevel_){.tag = Pipe_1};
    goto end_match_272;
next_275:;
    if ((level_.tag != Pipe_1)) goto next_276;
    match_81 = (struct OpLevel_){.tag = Cons_};
    goto end_match_272;
next_276:;
    if ((level_.tag != Cons_)) goto next_277;
    match_81 = (struct OpLevel_){.tag = Add_};
    goto end_match_272;
next_277:;
    if ((level_.tag != Add_)) goto next_279;
    match_81 = (struct OpLevel_){.tag = Mul_};
    goto end_match_272;
next_279:;
    if ((level_.tag != Mul_)) goto next_280;
    goto match_body_278;
next_280:;
    if ((level_.tag != Prefix_)) goto next_281;
    goto match_body_278;
match_body_278:;
    match_81 = (struct OpLevel_){.tag = Prefix_};
    goto end_match_272;
next_281:;
end_match_272:;
    return match_81;
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
    struct Lit_IntIntTuple2Tuple2 tuple_27;
    tuple_27.t0 = litFalse_;
    tuple_27.t1 = loc_2;
    struct Lit_IntIntTuple2Tuple2* payload_ = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_))) = tuple_27;
    struct APat_ variant_ = (struct APat_){.tag = Lit_, .Lit_ = payload_};
    return variant_;
}

struct APat_ apTrue_(struct Lit_ litTrue_, struct IntIntTuple2 loc_3) {
    struct Lit_IntIntTuple2Tuple2 tuple_28;
    tuple_28.t0 = litTrue_;
    tuple_28.t1 = loc_3;
    struct Lit_IntIntTuple2Tuple2* payload_1 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_1))) = tuple_28;
    struct APat_ variant_1 = (struct APat_){.tag = Lit_, .Lit_ = payload_1};
    return variant_1;
}

struct AExpr_ListIntIntTuple2Tuple2 {
    struct AExpr_List* t0;
    struct IntIntTuple2 t1;
};

struct AExpr_ axUnit_(struct IntIntTuple2 loc_4) {
    struct AExpr_ListIntIntTuple2Tuple2 tuple_29;
    tuple_29.t0 = NULL;
    tuple_29.t1 = loc_4;
    struct AExpr_ListIntIntTuple2Tuple2* payload_2 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_2))) = tuple_29;
    struct AExpr_ variant_2 = (struct AExpr_){.tag = TupleLit_1, .TupleLit_1 = payload_2};
    return variant_2;
}

struct AExpr_ axFalse_(struct Lit_ litFalse_, struct IntIntTuple2 loc_5) {
    struct Lit_IntIntTuple2Tuple2 tuple_30;
    tuple_30.t0 = litFalse_;
    tuple_30.t1 = loc_5;
    struct Lit_IntIntTuple2Tuple2* payload_3 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_3))) = tuple_30;
    struct AExpr_ variant_3 = (struct AExpr_){.tag = Lit_1, .Lit_1 = payload_3};
    return variant_3;
}

struct AExpr_ axTrue_(struct Lit_ litTrue_, struct IntIntTuple2 loc_6) {
    struct Lit_IntIntTuple2Tuple2 tuple_31;
    tuple_31.t0 = litTrue_;
    tuple_31.t1 = loc_6;
    struct Lit_IntIntTuple2Tuple2* payload_4 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_4))) = tuple_31;
    struct AExpr_ variant_4 = (struct AExpr_){.tag = Lit_1, .Lit_1 = payload_4};
    return variant_4;
}

struct AExpr_ axNil_(struct IntIntTuple2 loc_7) {
    struct AExpr_ListIntIntTuple2Tuple2 tuple_32;
    tuple_32.t0 = NULL;
    tuple_32.t1 = loc_7;
    struct AExpr_ListIntIntTuple2Tuple2* payload_5 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_5))) = tuple_32;
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

struct AExpr_ app_(struct IntIntTuple2 loc_8, struct AExpr_ x_16, struct AExpr_ f_4) {
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_33;
    tuple_33.t0 = (struct Op_){.tag = App_};
    tuple_33.t1 = f_4;
    tuple_33.t2 = x_16;
    tuple_33.t3 = loc_8;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_6 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_6))) = tuple_33;
    struct AExpr_ variant_6 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_6};
    return variant_6;
}

struct AExpr_ axApp3_(struct AExpr_ f_3, struct AExpr_ x1_, struct AExpr_ x2_, struct AExpr_ x3_, struct IntIntTuple2 loc_8) {
    struct AExpr_ call_145 = app_(loc_8, x1_, f_3);
    struct AExpr_ call_146 = app_(loc_8, x2_, call_145);
    struct AExpr_ call_147 = app_(loc_8, x3_, call_146);
    return call_147;
}

struct AExpr_ axNot_(struct Lit_ litFalse_, struct AExpr_ arg_, struct IntIntTuple2 loc_9) {
    struct AExpr_ call_148 = axFalse_(litFalse_, loc_9);
    struct AExpr_ falseExpr_ = call_148;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_34;
    tuple_34.t0 = (struct Op_){.tag = Eq_1};
    tuple_34.t1 = arg_;
    tuple_34.t2 = falseExpr_;
    tuple_34.t3 = loc_9;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_7 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_7))) = tuple_34;
    struct AExpr_ variant_7 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_7};
    return variant_7;
}

struct StringDumpTree_ListDumpTree_ListTuple3 {
    struct String t0;
    struct DumpTree_List* t1;
    struct DumpTree_List* t2;
};

struct DumpTree_ dumpTreeNew_(struct String text_43, struct DumpTree_List* children_) {
    struct StringDumpTree_ListDumpTree_ListTuple3 tuple_35;
    tuple_35.t0 = text_43;
    tuple_35.t1 = children_;
    tuple_35.t2 = NULL;
    struct StringDumpTree_ListDumpTree_ListTuple3* payload_8 = (struct StringDumpTree_ListDumpTree_ListTuple3*)malloc(sizeof(struct StringDumpTree_ListDumpTree_ListTuple3));
    (*(((struct StringDumpTree_ListDumpTree_ListTuple3*)payload_8))) = tuple_35;
    struct DumpTree_ variant_8 = (struct DumpTree_){.tag = DumpTree_, .DumpTree_ = payload_8};
    return variant_8;
}

struct DumpTree_ dumpTreeNewLeaf_(struct String text_44) {
    struct StringDumpTree_ListDumpTree_ListTuple3 tuple_36;
    tuple_36.t0 = text_44;
    tuple_36.t1 = NULL;
    tuple_36.t2 = NULL;
    struct StringDumpTree_ListDumpTree_ListTuple3* payload_9 = (struct StringDumpTree_ListDumpTree_ListTuple3*)malloc(sizeof(struct StringDumpTree_ListDumpTree_ListTuple3));
    (*(((struct StringDumpTree_ListDumpTree_ListTuple3*)payload_9))) = tuple_36;
    struct DumpTree_ variant_9 = (struct DumpTree_){.tag = DumpTree_, .DumpTree_ = payload_9};
    return variant_9;
}

struct DumpTree_ dumpTreeAttachNext_(struct DumpTree_ next_1, struct DumpTree_ tree_) {
    struct DumpTree_ match_82;
    struct String text_45 = (*(tree_.DumpTree_)).t0;
    struct DumpTree_List* children_1 = (*(tree_.DumpTree_)).t1;
    struct DumpTree_List* oldNext_ = (*(tree_.DumpTree_)).t2;
    int call_149 = listIsEmpty_3(children_1);
    milone_assert((!(call_149)), 428, 4);
    int call_150 = 0;
    int call_151 = listIsEmpty_3(oldNext_);
    milone_assert(call_151, 429, 4);
    int call_152 = 0;
    struct DumpTree_List* list_35 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_35->head = next_1;
    list_35->tail = NULL;
    struct StringDumpTree_ListDumpTree_ListTuple3 tuple_37;
    tuple_37.t0 = text_45;
    tuple_37.t1 = children_1;
    tuple_37.t2 = list_35;
    struct StringDumpTree_ListDumpTree_ListTuple3* payload_10 = (struct StringDumpTree_ListDumpTree_ListTuple3*)malloc(sizeof(struct StringDumpTree_ListDumpTree_ListTuple3));
    (*(((struct StringDumpTree_ListDumpTree_ListTuple3*)payload_10))) = tuple_37;
    struct DumpTree_ variant_10 = (struct DumpTree_){.tag = DumpTree_, .DumpTree_ = payload_10};
    match_82 = variant_10;
    goto end_match_282;
next_283:;
    exit(1);
end_match_282:;
    return match_82;
}

struct DumpTree_ dumpTreeFromError_(struct String msg_, struct IntIntTuple2 arg_101) {
    int y_10 = arg_101.t0;
    int x_17 = arg_101.t1;
    struct String call_153 = str_of_int((y_10 + 1));
    struct String y_11 = call_153;
    struct String call_154 = str_of_int((x_17 + 1));
    struct String x_18 = call_154;
    struct DumpTree_ call_155 = dumpTreeNewLeaf_(msg_);
    struct DumpTree_ call_156 = dumpTreeNewLeaf_(str_add(str_add(str_add(str_add((struct String){.str = "(", .len = 1}, y_11), (struct String){.str = ":", .len = 1}), x_18), (struct String){.str = ")", .len = 1}));
    struct DumpTree_List* list_37 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_37->head = call_156;
    list_37->tail = NULL;
    struct DumpTree_List* list_36 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_36->head = call_155;
    list_36->tail = list_37;
    struct DumpTree_ call_157 = dumpTreeNew_((struct String){.str = "ERROR", .len = 5}, list_36);
    return call_157;
}

struct StringList* goChildren_(struct String eol_1, struct DumpTree_List* children_2, struct StringList* acc_13) {
    struct StringList* match_83;
    if ((!((!(children_2))))) goto next_285;
    match_83 = acc_13;
    goto end_match_284;
next_285:;
    if ((!(children_2))) goto next_286;
    struct DumpTree_ child_ = children_2->head;
    struct DumpTree_List* children_3 = children_2->tail;
    struct StringList* call_158 = cons_1(eol_1, acc_13);
    struct StringList* call_159 = cons_1((struct String){.str = "- ", .len = 2}, call_158);
    struct StringList* call_160 = go_22(str_add(eol_1, (struct String){.str = "  ", .len = 2}), child_, call_159);
    struct StringList* call_161 = goChildren_(eol_1, children_3, call_160);
    match_83 = call_161;
    goto end_match_284;
next_286:;
    exit(1);
end_match_284:;
    return match_83;
}

struct StringList* goNext_(struct String eol_2, struct DumpTree_List* next_2, struct StringList* acc_14) {
    struct StringList* match_84;
    if ((!((!(next_2))))) goto next_288;
    match_84 = acc_14;
    goto end_match_287;
next_288:;
    if ((!(next_2))) goto next_289;
    struct DumpTree_ next_3 = next_2->head;
    if ((!((!(next_2->tail))))) goto next_289;
    struct StringList* call_162 = cons_1(eol_2, acc_14);
    struct StringList* call_163 = go_22(eol_2, next_3, call_162);
    match_84 = call_163;
    goto end_match_287;
next_289:;
    struct StringList* call_164 = failwith_2((struct String){.str = "NEVER: DumpTree.next never empty", .len = 32});
    match_84 = call_164;
    goto end_match_287;
next_290:;
end_match_287:;
    return match_84;
}

struct StringList* go_22(struct String eol_, struct DumpTree_ node_1, struct StringList* acc_12) {
    struct StringList* match_85;
    struct String text_46 = (*(node_1.DumpTree_)).t0;
    if ((!((!((*(node_1.DumpTree_)).t1))))) goto next_292;
    if ((!((!((*(node_1.DumpTree_)).t2))))) goto next_292;
    struct String call_165 = strEscape_(text_46);
    struct StringList* call_166 = cons_1(call_165, acc_12);
    match_85 = call_166;
    goto end_match_291;
next_292:;
    struct String text_47 = (*(node_1.DumpTree_)).t0;
    if ((!((*(node_1.DumpTree_)).t1))) goto next_293;
    struct String childText_ = (*((*(node_1.DumpTree_)).t1->head.DumpTree_)).t0;
    if ((!((!((*((*(node_1.DumpTree_)).t1->head.DumpTree_)).t1))))) goto next_293;
    if ((!((!((*((*(node_1.DumpTree_)).t1->head.DumpTree_)).t2))))) goto next_293;
    if ((!((!((*(node_1.DumpTree_)).t1->tail))))) goto next_293;
    struct DumpTree_List* next_4 = (*(node_1.DumpTree_)).t2;
    struct String call_167 = strEscape_(childText_);
    struct String call_168 = strEscape_(text_47);
    struct StringList* call_169 = cons_1(call_168, acc_12);
    struct StringList* call_170 = cons_1((struct String){.str = ": ", .len = 2}, call_169);
    struct StringList* call_171 = cons_1(call_167, call_170);
    struct StringList* call_172 = goNext_(eol_, next_4, call_171);
    match_85 = call_172;
    goto end_match_291;
next_293:;
    struct String text_48 = (*(node_1.DumpTree_)).t0;
    struct DumpTree_List* children_4 = (*(node_1.DumpTree_)).t1;
    struct DumpTree_List* next_5 = (*(node_1.DumpTree_)).t2;
    struct String call_173 = strEscape_(text_48);
    struct StringList* call_174 = cons_1(call_173, acc_12);
    struct StringList* call_175 = cons_1((struct String){.str = ":", .len = 1}, call_174);
    struct StringList* call_176 = goChildren_(eol_, children_4, call_175);
    struct StringList* call_177 = goNext_(eol_, next_5, call_176);
    match_85 = call_177;
    goto end_match_291;
next_294:;
    exit(1);
end_match_291:;
    return match_85;
}

struct String dumpTreeToString_(struct DumpTree_ node_) {
    struct String eol_3 = (struct String){.str = "\n", .len = 1};
    struct StringList* call_178 = go_22(eol_3, node_, NULL);
    struct StringList* call_179 = listRev_2(call_178);
    struct String call_180 = strConcat_(call_179);
    return call_180;
}

struct IntStringTuple2 {
    int t0;
    struct String t1;
};

struct IntStringTuple2List {
    struct IntStringTuple2 head;
    struct IntStringTuple2List* tail;
};

struct IntStringTuple2ListIntTuple2 {
    struct IntStringTuple2List* t0;
    int t1;
};

struct NameCtx_ nameCtxEmpty_(int arg_102) {
    struct IntStringTuple2ListIntTuple2 tuple_38;
    tuple_38.t0 = NULL;
    tuple_38.t1 = 0;
    struct IntStringTuple2ListIntTuple2* payload_11 = (struct IntStringTuple2ListIntTuple2*)malloc(sizeof(struct IntStringTuple2ListIntTuple2));
    (*(((struct IntStringTuple2ListIntTuple2*)payload_11))) = tuple_38;
    struct NameCtx_ variant_11 = (struct NameCtx_){.tag = NameCtx_, .NameCtx_ = payload_11};
    return variant_11;
}

struct IntNameCtx_Tuple2 {
    int t0;
    struct NameCtx_ t1;
};

struct IntNameCtx_Tuple2 nameCtxAdd_1(struct String ident_, struct NameCtx_ arg_103) {
    struct IntStringTuple2List* map_ = (*(arg_103.NameCtx_)).t0;
    int serial_ = (*(arg_103.NameCtx_)).t1;
    int serial_1 = (serial_ + 1);
    struct IntStringTuple2ListIntTuple2 tuple_40;
    tuple_40.t0 = map_;
    tuple_40.t1 = serial_1;
    struct IntStringTuple2ListIntTuple2* payload_12 = (struct IntStringTuple2ListIntTuple2*)malloc(sizeof(struct IntStringTuple2ListIntTuple2));
    (*(((struct IntStringTuple2ListIntTuple2*)payload_12))) = tuple_40;
    struct NameCtx_ variant_12 = (struct NameCtx_){.tag = NameCtx_, .NameCtx_ = payload_12};
    struct IntNameCtx_Tuple2 tuple_39;
    tuple_39.t0 = serial_1;
    tuple_39.t1 = variant_12;
    return tuple_39;
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

struct Trait_ traitMapTys_(struct Ty_Ty_Fun1 f_5, struct Trait_ it_) {
    struct Trait_ match_86;
    if ((it_.tag != Add_2)) goto next_296;
    struct Ty_ ty_ = (*(it_.Add_2));
    struct Ty_ app_20 = f_5.fun(f_5.env, ty_);
    struct Ty_* payload_13 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_13))) = app_20;
    struct Trait_ variant_13 = (struct Trait_){.tag = Add_2, .Add_2 = payload_13};
    match_86 = variant_13;
    goto end_match_295;
next_296:;
    if ((it_.tag != Eq_2)) goto next_297;
    struct Ty_ ty_1 = (*(it_.Eq_2));
    struct Ty_ app_21 = f_5.fun(f_5.env, ty_1);
    struct Ty_* payload_14 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_14))) = app_21;
    struct Trait_ variant_14 = (struct Trait_){.tag = Eq_2, .Eq_2 = payload_14};
    match_86 = variant_14;
    goto end_match_295;
next_297:;
    if ((it_.tag != Cmp_1)) goto next_298;
    struct Ty_ ty_2 = (*(it_.Cmp_1));
    struct Ty_ app_22 = f_5.fun(f_5.env, ty_2);
    struct Ty_* payload_15 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_15))) = app_22;
    struct Trait_ variant_15 = (struct Trait_){.tag = Cmp_1, .Cmp_1 = payload_15};
    match_86 = variant_15;
    goto end_match_295;
next_298:;
    if ((it_.tag != Index_1)) goto next_299;
    struct Ty_ lTy_ = (*(it_.Index_1)).t0;
    struct Ty_ rTy_ = (*(it_.Index_1)).t1;
    struct Ty_ outputTy_ = (*(it_.Index_1)).t2;
    struct Ty_ app_23 = f_5.fun(f_5.env, lTy_);
    struct Ty_ app_24 = f_5.fun(f_5.env, rTy_);
    struct Ty_ app_25 = f_5.fun(f_5.env, outputTy_);
    struct Ty_Ty_Ty_Tuple3 tuple_41;
    tuple_41.t0 = app_23;
    tuple_41.t1 = app_24;
    tuple_41.t2 = app_25;
    struct Ty_Ty_Ty_Tuple3* payload_16 = (struct Ty_Ty_Ty_Tuple3*)malloc(sizeof(struct Ty_Ty_Ty_Tuple3));
    (*(((struct Ty_Ty_Ty_Tuple3*)payload_16))) = tuple_41;
    struct Trait_ variant_16 = (struct Trait_){.tag = Index_1, .Index_1 = payload_16};
    match_86 = variant_16;
    goto end_match_295;
next_299:;
    if ((it_.tag != ToInt_)) goto next_300;
    struct Ty_ ty_3 = (*(it_.ToInt_));
    struct Ty_ app_26 = f_5.fun(f_5.env, ty_3);
    struct Ty_* payload_17 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_17))) = app_26;
    struct Trait_ variant_17 = (struct Trait_){.tag = ToInt_, .ToInt_ = payload_17};
    match_86 = variant_17;
    goto end_match_295;
next_300:;
    if ((it_.tag != ToString_)) goto next_301;
    struct Ty_ ty_4 = (*(it_.ToString_));
    struct Ty_ app_27 = f_5.fun(f_5.env, ty_4);
    struct Ty_* payload_18 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_18))) = app_27;
    struct Trait_ variant_18 = (struct Trait_){.tag = ToString_, .ToString_ = payload_18};
    match_86 = variant_18;
    goto end_match_295;
next_301:;
    exit(1);
end_match_295:;
    return match_86;
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
    struct TyCon_Ty_ListTuple2 tuple_42;
    tuple_42.t0 = (struct TyCon_){.tag = Tuple_1};
    tuple_42.t1 = tys_;
    struct TyCon_Ty_ListTuple2* payload_19 = (struct TyCon_Ty_ListTuple2*)malloc(sizeof(struct TyCon_Ty_ListTuple2));
    (*(((struct TyCon_Ty_ListTuple2*)payload_19))) = tuple_42;
    struct Ty_ variant_19 = (struct Ty_){.tag = Con_, .Con_ = payload_19};
    return variant_19;
}

struct Ty_ tyList_(struct Ty_ ty_5) {
    struct Ty_List* list_38 = (struct Ty_List*)malloc(sizeof(struct Ty_List));
    list_38->head = ty_5;
    list_38->tail = NULL;
    struct TyCon_Ty_ListTuple2 tuple_43;
    tuple_43.t0 = (struct TyCon_){.tag = List_};
    tuple_43.t1 = list_38;
    struct TyCon_Ty_ListTuple2* payload_20 = (struct TyCon_Ty_ListTuple2*)malloc(sizeof(struct TyCon_Ty_ListTuple2));
    (*(((struct TyCon_Ty_ListTuple2*)payload_20))) = tuple_43;
    struct Ty_ variant_20 = (struct Ty_){.tag = Con_, .Con_ = payload_20};
    return variant_20;
}

struct Ty_ tyFun_(struct Ty_ sourceTy_, struct Ty_ targetTy_) {
    struct Ty_List* list_40 = (struct Ty_List*)malloc(sizeof(struct Ty_List));
    list_40->head = targetTy_;
    list_40->tail = NULL;
    struct Ty_List* list_39 = (struct Ty_List*)malloc(sizeof(struct Ty_List));
    list_39->head = sourceTy_;
    list_39->tail = list_40;
    struct TyCon_Ty_ListTuple2 tuple_44;
    tuple_44.t0 = (struct TyCon_){.tag = Fun_4};
    tuple_44.t1 = list_39;
    struct TyCon_Ty_ListTuple2* payload_21 = (struct TyCon_Ty_ListTuple2*)malloc(sizeof(struct TyCon_Ty_ListTuple2));
    (*(((struct TyCon_Ty_ListTuple2*)payload_21))) = tuple_44;
    struct Ty_ variant_21 = (struct Ty_){.tag = Con_, .Con_ = payload_21};
    return variant_21;
}

struct Ty_ tyRef_(int serial_2, struct Ty_List* tys_1) {
    int* payload_22 = (int*)malloc(sizeof(int));
    (*(((int*)payload_22))) = serial_2;
    struct TyCon_ variant_22 = (struct TyCon_){.tag = Ref_, .Ref_ = payload_22};
    struct TyCon_Ty_ListTuple2 tuple_45;
    tuple_45.t0 = variant_22;
    tuple_45.t1 = tys_1;
    struct TyCon_Ty_ListTuple2* payload_23 = (struct TyCon_Ty_ListTuple2*)malloc(sizeof(struct TyCon_Ty_ListTuple2));
    (*(((struct TyCon_Ty_ListTuple2*)payload_23))) = tuple_45;
    struct Ty_ variant_23 = (struct Ty_){.tag = Con_, .Con_ = payload_23};
    return variant_23;
}

struct StringTy_ListTuple2 {
    struct String t0;
    struct Ty_List* t1;
};

struct Ty_ tyPrimFromIdent_(struct Ty_ tyUnit_, struct Ty_ tyObj_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct String ident_1, struct Ty_List* tys_2, struct IntIntTuple2 loc_10) {
    struct Ty_ match_87;
    struct StringTy_ListTuple2 tuple_46;
    tuple_46.t0 = ident_1;
    tuple_46.t1 = tys_2;
    if ((str_cmp(tuple_46.t0, (struct String){.str = "unit", .len = 4}) != 0)) goto next_303;
    if ((!((!(tuple_46.t1))))) goto next_303;
    match_87 = tyUnit_;
    goto end_match_302;
next_303:;
    if ((str_cmp(tuple_46.t0, (struct String){.str = "bool", .len = 4}) != 0)) goto next_304;
    if ((!((!(tuple_46.t1))))) goto next_304;
    match_87 = tyBool_;
    goto end_match_302;
next_304:;
    if ((str_cmp(tuple_46.t0, (struct String){.str = "int", .len = 3}) != 0)) goto next_305;
    if ((!((!(tuple_46.t1))))) goto next_305;
    match_87 = tyInt_;
    goto end_match_302;
next_305:;
    if ((str_cmp(tuple_46.t0, (struct String){.str = "char", .len = 4}) != 0)) goto next_306;
    if ((!((!(tuple_46.t1))))) goto next_306;
    match_87 = tyChar_;
    goto end_match_302;
next_306:;
    if ((str_cmp(tuple_46.t0, (struct String){.str = "string", .len = 6}) != 0)) goto next_307;
    if ((!((!(tuple_46.t1))))) goto next_307;
    match_87 = tyStr_;
    goto end_match_302;
next_307:;
    if ((str_cmp(tuple_46.t0, (struct String){.str = "obj", .len = 3}) != 0)) goto next_308;
    if ((!((!(tuple_46.t1))))) goto next_308;
    match_87 = tyObj_;
    goto end_match_302;
next_308:;
    if ((str_cmp(tuple_46.t0, (struct String){.str = "list", .len = 4}) != 0)) goto next_309;
    if ((!(tuple_46.t1))) goto next_309;
    struct Ty_ itemTy_ = tuple_46.t1->head;
    if ((!((!(tuple_46.t1->tail))))) goto next_309;
    struct Ty_ call_181 = tyList_(itemTy_);
    match_87 = call_181;
    goto end_match_302;
next_309:;
    struct IntIntTuple2* payload_24 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_24))) = loc_10;
    struct Ty_ variant_24 = (struct Ty_){.tag = Error_1, .Error_1 = payload_24};
    match_87 = variant_24;
    goto end_match_302;
next_310:;
end_match_302:;
    return match_87;
}

struct IntIntIntTuple2Tuple2 {
    int t0;
    struct IntIntTuple2 t1;
};

int go_23(int tySerial_, struct Ty_ ty_7) {
    int match_88;
    if ((ty_7.tag != Error_1)) goto next_313;
    goto match_body_312;
next_313:;
    if ((ty_7.tag != Con_)) goto next_314;
    if ((!((!((*(ty_7.Con_)).t1))))) goto next_314;
    goto match_body_312;
match_body_312:;
    match_88 = 1;
    goto end_match_311;
next_314:;
    if ((ty_7.tag != Con_)) goto next_315;
    struct TyCon_ tyCon_ = (*(ty_7.Con_)).t0;
    if ((!((*(ty_7.Con_)).t1))) goto next_315;
    struct Ty_ ty_8 = (*(ty_7.Con_)).t1->head;
    struct Ty_List* tys_3 = (*(ty_7.Con_)).t1->tail;
    int match_89;
    int call_182 = go_23(tySerial_, ty_8);
    if ((!(call_182))) goto next_318;
    struct TyCon_Ty_ListTuple2 tuple_47;
    tuple_47.t0 = tyCon_;
    tuple_47.t1 = tys_3;
    struct TyCon_Ty_ListTuple2* payload_25 = (struct TyCon_Ty_ListTuple2*)malloc(sizeof(struct TyCon_Ty_ListTuple2));
    (*(((struct TyCon_Ty_ListTuple2*)payload_25))) = tuple_47;
    struct Ty_ variant_25 = (struct Ty_){.tag = Con_, .Con_ = payload_25};
    int call_183 = go_23(tySerial_, variant_25);
    match_89 = call_183;
    goto end_match_317;
next_318:;
    if (call_182) goto next_319;
    match_89 = 0;
    goto end_match_317;
next_319:;
    exit(1);
end_match_317:;
    match_88 = match_89;
    goto end_match_311;
next_315:;
    if ((ty_7.tag != Meta_)) goto next_316;
    int s_7 = (*(ty_7.Meta_)).t0;
    match_88 = (s_7 != tySerial_);
    goto end_match_311;
next_316:;
    exit(1);
end_match_311:;
    return match_88;
}

int tyIsFreeIn_(struct Ty_ ty_6, int tySerial_) {
    int call_184 = go_23(tySerial_, ty_6);
    return call_184;
}

int go_24(struct Ty_List* tys_4) {
    int match_90;
    if ((!((!(tys_4))))) goto next_321;
    match_90 = 1;
    goto end_match_320;
next_321:;
    if ((!(tys_4))) goto next_322;
    if ((tys_4->head.tag != Meta_)) goto next_322;
    match_90 = 0;
    goto end_match_320;
next_322:;
    if ((!(tys_4))) goto next_323;
    if ((tys_4->head.tag != Error_1)) goto next_323;
    struct Ty_List* tys_5 = tys_4->tail;
    int call_185 = go_24(tys_5);
    match_90 = call_185;
    goto end_match_320;
next_323:;
    if ((!(tys_4))) goto next_324;
    if ((tys_4->head.tag != Con_)) goto next_324;
    struct Ty_List* tys1_ = (*(tys_4->head.Con_)).t1;
    struct Ty_List* tys2_ = tys_4->tail;
    int match_91;
    int call_186 = go_24(tys1_);
    if ((!(call_186))) goto next_326;
    int call_187 = go_24(tys2_);
    match_91 = call_187;
    goto end_match_325;
next_326:;
    if (call_186) goto next_327;
    match_91 = 0;
    goto end_match_325;
next_327:;
    exit(1);
end_match_325:;
    match_90 = match_91;
    goto end_match_320;
next_324:;
    exit(1);
end_match_320:;
    return match_90;
}

int tyIsMonomorphic_(struct Ty_ ty_9) {
    struct Ty_List* list_41 = (struct Ty_List*)malloc(sizeof(struct Ty_List));
    list_41->head = ty_9;
    list_41->tail = NULL;
    int call_188 = go_24(list_41);
    return call_188;
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
    struct String match_92;
    if ((tyDef_.tag != Meta_1)) goto next_329;
    struct String ident_2 = (*(tyDef_.Meta_1)).t0;
    match_92 = ident_2;
    goto end_match_328;
next_329:;
    if ((tyDef_.tag != Union_2)) goto next_330;
    struct String ident_3 = (*(tyDef_.Union_2)).t0;
    match_92 = ident_3;
    goto end_match_328;
next_330:;
    exit(1);
end_match_328:;
    return match_92;
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
    struct String match_93;
    if ((varDef_.tag != Var_)) goto next_332;
    struct String ident_4 = (*(varDef_.Var_)).t0;
    match_93 = ident_4;
    goto end_match_331;
next_332:;
    if ((varDef_.tag != Fun_5)) goto next_333;
    struct String ident_5 = (*(varDef_.Fun_5)).t0;
    match_93 = ident_5;
    goto end_match_331;
next_333:;
    if ((varDef_.tag != Variant_)) goto next_334;
    struct String ident_6 = (*(varDef_.Variant_)).t0;
    match_93 = ident_6;
    goto end_match_331;
next_334:;
    exit(1);
end_match_331:;
    return match_93;
}

struct Ty_ litToTy_(struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Lit_ lit_) {
    struct Ty_ match_94;
    if ((lit_.tag != Bool_)) goto next_336;
    match_94 = tyBool_;
    goto end_match_335;
next_336:;
    if ((lit_.tag != Int_)) goto next_337;
    match_94 = tyInt_;
    goto end_match_335;
next_337:;
    if ((lit_.tag != Char_)) goto next_338;
    match_94 = tyChar_;
    goto end_match_335;
next_338:;
    if ((lit_.tag != Str_)) goto next_339;
    match_94 = tyStr_;
    goto end_match_335;
next_339:;
    exit(1);
end_match_335:;
    return match_94;
}

struct Ty_ meta_(struct IntIntTuple2 noLoc_, int id_) {
    struct IntIntIntTuple2Tuple2 tuple_48;
    tuple_48.t0 = id_;
    tuple_48.t1 = noLoc_;
    struct IntIntIntTuple2Tuple2* payload_26 = (struct IntIntIntTuple2Tuple2*)malloc(sizeof(struct IntIntIntTuple2Tuple2));
    (*(((struct IntIntIntTuple2Tuple2*)payload_26))) = tuple_48;
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
    struct Ty_Trait_ListTuple2 tuple_49;
    tuple_49.t0 = ty_10;
    tuple_49.t1 = NULL;
    struct Ty_Trait_ListTuple2* payload_27 = (struct Ty_Trait_ListTuple2*)malloc(sizeof(struct Ty_Trait_ListTuple2));
    (*(((struct Ty_Trait_ListTuple2*)payload_27))) = tuple_49;
    struct TySpec_ variant_27 = (struct TySpec_){.tag = TySpec_, .TySpec_ = payload_27};
    return variant_27;
}

struct TySpec_ poly_(struct Ty_ ty_11, struct Trait_List* traits_) {
    struct Ty_Trait_ListTuple2 tuple_50;
    tuple_50.t0 = ty_11;
    tuple_50.t1 = traits_;
    struct Ty_Trait_ListTuple2* payload_28 = (struct Ty_Trait_ListTuple2*)malloc(sizeof(struct Ty_Trait_ListTuple2));
    (*(((struct Ty_Trait_ListTuple2*)payload_28))) = tuple_50;
    struct TySpec_ variant_28 = (struct TySpec_){.tag = TySpec_, .TySpec_ = payload_28};
    return variant_28;
}

struct TySpec_ primToTySpec_(struct Ty_ tyUnit_, struct Ty_ tyObj_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct IntIntTuple2 noLoc_, struct HPrim_ prim_) {
    struct TySpec_ match_95;
    if ((prim_.tag != Add_3)) goto next_341;
    struct Ty_ call_189 = meta_(noLoc_, 1);
    struct Ty_ addTy_ = call_189;
    struct Ty_ call_190 = tyFun_(addTy_, addTy_);
    struct Ty_ call_191 = tyFun_(addTy_, call_190);
    struct Ty_* payload_29 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_29))) = addTy_;
    struct Trait_ variant_29 = (struct Trait_){.tag = Add_2, .Add_2 = payload_29};
    struct Trait_List* list_42 = (struct Trait_List*)malloc(sizeof(struct Trait_List));
    list_42->head = variant_29;
    list_42->tail = NULL;
    struct TySpec_ call_192 = poly_(call_191, list_42);
    match_95 = call_192;
    goto end_match_340;
next_341:;
    if ((prim_.tag != Sub_1)) goto next_342;
    struct Ty_ call_193 = tyFun_(tyInt_, tyInt_);
    struct Ty_ call_194 = tyFun_(tyInt_, call_193);
    struct TySpec_ call_195 = mono_(call_194);
    match_95 = call_195;
    goto end_match_340;
next_342:;
    if ((prim_.tag != Mul_2)) goto next_343;
    struct Ty_ call_196 = tyFun_(tyInt_, tyInt_);
    struct Ty_ call_197 = tyFun_(tyInt_, call_196);
    struct TySpec_ call_198 = mono_(call_197);
    match_95 = call_198;
    goto end_match_340;
next_343:;
    if ((prim_.tag != Div_1)) goto next_344;
    struct Ty_ call_199 = tyFun_(tyInt_, tyInt_);
    struct Ty_ call_200 = tyFun_(tyInt_, call_199);
    struct TySpec_ call_201 = mono_(call_200);
    match_95 = call_201;
    goto end_match_340;
next_344:;
    if ((prim_.tag != Mod_1)) goto next_345;
    struct Ty_ call_202 = tyFun_(tyInt_, tyInt_);
    struct Ty_ call_203 = tyFun_(tyInt_, call_202);
    struct TySpec_ call_204 = mono_(call_203);
    match_95 = call_204;
    goto end_match_340;
next_345:;
    if ((prim_.tag != Eq_3)) goto next_346;
    struct Ty_ call_205 = meta_(noLoc_, 1);
    struct Ty_ eqTy_ = call_205;
    struct Ty_ call_206 = tyFun_(eqTy_, tyBool_);
    struct Ty_ call_207 = tyFun_(eqTy_, call_206);
    struct Ty_* payload_30 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_30))) = eqTy_;
    struct Trait_ variant_30 = (struct Trait_){.tag = Eq_2, .Eq_2 = payload_30};
    struct Trait_List* list_43 = (struct Trait_List*)malloc(sizeof(struct Trait_List));
    list_43->head = variant_30;
    list_43->tail = NULL;
    struct TySpec_ call_208 = poly_(call_207, list_43);
    match_95 = call_208;
    goto end_match_340;
next_346:;
    if ((prim_.tag != Lt_2)) goto next_347;
    struct Ty_ call_209 = meta_(noLoc_, 1);
    struct Ty_ cmpTy_ = call_209;
    struct Ty_ call_210 = tyFun_(cmpTy_, tyBool_);
    struct Ty_ call_211 = tyFun_(cmpTy_, call_210);
    struct Ty_* payload_31 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_31))) = cmpTy_;
    struct Trait_ variant_31 = (struct Trait_){.tag = Cmp_1, .Cmp_1 = payload_31};
    struct Trait_List* list_44 = (struct Trait_List*)malloc(sizeof(struct Trait_List));
    list_44->head = variant_31;
    list_44->tail = NULL;
    struct TySpec_ call_212 = poly_(call_211, list_44);
    match_95 = call_212;
    goto end_match_340;
next_347:;
    if ((prim_.tag != Nil_1)) goto next_348;
    struct Ty_ call_213 = meta_(noLoc_, 1);
    struct Ty_ itemTy_1 = call_213;
    struct Ty_ call_214 = tyList_(itemTy_1);
    struct TySpec_ call_215 = poly_(call_214, NULL);
    match_95 = call_215;
    goto end_match_340;
next_348:;
    if ((prim_.tag != Cons_4)) goto next_349;
    struct Ty_ call_216 = meta_(noLoc_, 1);
    struct Ty_ itemTy_2 = call_216;
    struct Ty_ call_217 = tyList_(itemTy_2);
    struct Ty_ listTy_ = call_217;
    struct Ty_ call_218 = tyFun_(listTy_, listTy_);
    struct Ty_ call_219 = tyFun_(itemTy_2, call_218);
    struct TySpec_ call_220 = poly_(call_219, NULL);
    match_95 = call_220;
    goto end_match_340;
next_349:;
    if ((prim_.tag != Index_2)) goto next_350;
    struct Ty_ call_221 = meta_(noLoc_, 1);
    struct Ty_ lTy_1 = call_221;
    struct Ty_ call_222 = meta_(noLoc_, 2);
    struct Ty_ rTy_1 = call_222;
    struct Ty_ call_223 = meta_(noLoc_, 3);
    struct Ty_ resultTy_ = call_223;
    struct Ty_ call_224 = tyFun_(rTy_1, resultTy_);
    struct Ty_ call_225 = tyFun_(lTy_1, call_224);
    struct Ty_Ty_Ty_Tuple3 tuple_51;
    tuple_51.t0 = lTy_1;
    tuple_51.t1 = rTy_1;
    tuple_51.t2 = resultTy_;
    struct Ty_Ty_Ty_Tuple3* payload_32 = (struct Ty_Ty_Ty_Tuple3*)malloc(sizeof(struct Ty_Ty_Ty_Tuple3));
    (*(((struct Ty_Ty_Ty_Tuple3*)payload_32))) = tuple_51;
    struct Trait_ variant_32 = (struct Trait_){.tag = Index_1, .Index_1 = payload_32};
    struct Trait_List* list_45 = (struct Trait_List*)malloc(sizeof(struct Trait_List));
    list_45->head = variant_32;
    list_45->tail = NULL;
    struct TySpec_ call_226 = poly_(call_225, list_45);
    match_95 = call_226;
    goto end_match_340;
next_350:;
    if ((prim_.tag != Not_)) goto next_351;
    struct Ty_ call_227 = tyFun_(tyBool_, tyBool_);
    struct TySpec_ call_228 = mono_(call_227);
    match_95 = call_228;
    goto end_match_340;
next_351:;
    if ((prim_.tag != Exit_)) goto next_352;
    struct Ty_ call_229 = meta_(noLoc_, 1);
    struct Ty_ resultTy_1 = call_229;
    struct Ty_ call_230 = tyFun_(tyInt_, resultTy_1);
    struct TySpec_ call_231 = poly_(call_230, NULL);
    match_95 = call_231;
    goto end_match_340;
next_352:;
    if ((prim_.tag != Assert_)) goto next_353;
    struct Ty_ call_232 = tyFun_(tyBool_, tyUnit_);
    struct TySpec_ call_233 = mono_(call_232);
    match_95 = call_233;
    goto end_match_340;
next_353:;
    if ((prim_.tag != Box_)) goto next_354;
    struct Ty_ call_234 = meta_(noLoc_, 1);
    struct Ty_ itemTy_3 = call_234;
    struct Ty_ call_235 = tyFun_(itemTy_3, tyObj_);
    struct TySpec_ call_236 = poly_(call_235, NULL);
    match_95 = call_236;
    goto end_match_340;
next_354:;
    if ((prim_.tag != Unbox_)) goto next_355;
    struct Ty_ call_237 = meta_(noLoc_, 1);
    struct Ty_ itemTy_4 = call_237;
    struct Ty_ call_238 = tyFun_(tyObj_, itemTy_4);
    struct TySpec_ call_239 = poly_(call_238, NULL);
    match_95 = call_239;
    goto end_match_340;
next_355:;
    if ((prim_.tag != Char_3)) goto next_356;
    struct Ty_ call_240 = tyFun_(tyInt_, tyChar_);
    struct TySpec_ call_241 = mono_(call_240);
    match_95 = call_241;
    goto end_match_340;
next_356:;
    if ((prim_.tag != Int_3)) goto next_357;
    struct Ty_ call_242 = meta_(noLoc_, 1);
    struct Ty_ toIntTy_ = call_242;
    struct Ty_ call_243 = tyFun_(toIntTy_, tyInt_);
    struct Ty_* payload_33 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_33))) = toIntTy_;
    struct Trait_ variant_33 = (struct Trait_){.tag = ToInt_, .ToInt_ = payload_33};
    struct Trait_List* list_46 = (struct Trait_List*)malloc(sizeof(struct Trait_List));
    list_46->head = variant_33;
    list_46->tail = NULL;
    struct TySpec_ call_244 = poly_(call_243, list_46);
    match_95 = call_244;
    goto end_match_340;
next_357:;
    if ((prim_.tag != String_)) goto next_358;
    struct Ty_ call_245 = meta_(noLoc_, 1);
    struct Ty_ toStrTy_ = call_245;
    struct Ty_ call_246 = tyFun_(toStrTy_, tyStr_);
    struct Ty_* payload_34 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_34))) = toStrTy_;
    struct Trait_ variant_34 = (struct Trait_){.tag = ToString_, .ToString_ = payload_34};
    struct Trait_List* list_47 = (struct Trait_List*)malloc(sizeof(struct Trait_List));
    list_47->head = variant_34;
    list_47->tail = NULL;
    struct TySpec_ call_247 = poly_(call_246, list_47);
    match_95 = call_247;
    goto end_match_340;
next_358:;
    if ((prim_.tag != StrLength_)) goto next_359;
    struct Ty_ call_248 = tyFun_(tyStr_, tyInt_);
    struct TySpec_ call_249 = mono_(call_248);
    match_95 = call_249;
    goto end_match_340;
next_359:;
    if ((prim_.tag != StrGetSlice_)) goto next_361;
    struct Ty_ call_250 = tyFun_(tyStr_, tyStr_);
    struct Ty_ call_251 = tyFun_(tyInt_, call_250);
    struct Ty_ call_252 = tyFun_(tyInt_, call_251);
    struct TySpec_ call_253 = mono_(call_252);
    match_95 = call_253;
    goto end_match_340;
next_361:;
    if ((prim_.tag != Printfn_)) goto next_362;
    goto match_body_360;
next_362:;
    if ((prim_.tag != NativeFun_)) goto next_363;
    goto match_body_360;
match_body_360:;
    struct Ty_ call_254 = meta_(noLoc_, 1);
    struct TySpec_ call_255 = poly_(call_254, NULL);
    match_95 = call_255;
    goto end_match_340;
next_363:;
end_match_340:;
    return match_95;
}

struct HPat_ListTy_IntIntTuple2Tuple3 {
    struct HPat_List* t0;
    struct Ty_ t1;
    struct IntIntTuple2 t2;
};

struct HPat_ patUnit_(struct Ty_ tyUnit_, struct IntIntTuple2 loc_11) {
    struct HPat_ListTy_IntIntTuple2Tuple3 tuple_52;
    tuple_52.t0 = NULL;
    tuple_52.t1 = tyUnit_;
    tuple_52.t2 = loc_11;
    struct HPat_ListTy_IntIntTuple2Tuple3* payload_35 = (struct HPat_ListTy_IntIntTuple2Tuple3*)malloc(sizeof(struct HPat_ListTy_IntIntTuple2Tuple3));
    (*(((struct HPat_ListTy_IntIntTuple2Tuple3*)payload_35))) = tuple_52;
    struct HPat_ variant_35 = (struct HPat_){.tag = Tuple_2, .Tuple_2 = payload_35};
    return variant_35;
}

struct Ty_IntIntTuple2Tuple2 {
    struct Ty_ t0;
    struct IntIntTuple2 t1;
};

struct HPat_ patNil_(struct Ty_ itemTy_5, struct IntIntTuple2 loc_12) {
    struct Ty_IntIntTuple2Tuple2 tuple_53;
    tuple_53.t0 = itemTy_5;
    tuple_53.t1 = loc_12;
    struct Ty_IntIntTuple2Tuple2* payload_36 = (struct Ty_IntIntTuple2Tuple2*)malloc(sizeof(struct Ty_IntIntTuple2Tuple2));
    (*(((struct Ty_IntIntTuple2Tuple2*)payload_36))) = tuple_53;
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
    struct Ty_IntIntTuple2Tuple2 match_96;
    if ((pat_.tag != Lit_2)) goto next_365;
    struct Lit_ lit_1 = (*(pat_.Lit_2)).t0;
    struct IntIntTuple2 a_ = (*(pat_.Lit_2)).t1;
    struct Ty_ call_256 = litToTy_(tyStr_, tyChar_, tyInt_, tyBool_, lit_1);
    struct Ty_IntIntTuple2Tuple2 tuple_54;
    tuple_54.t0 = call_256;
    tuple_54.t1 = a_;
    match_96 = tuple_54;
    goto end_match_364;
next_365:;
    if ((pat_.tag != Nil_)) goto next_366;
    struct Ty_ itemTy_6 = (*(pat_.Nil_)).t0;
    struct IntIntTuple2 a_1 = (*(pat_.Nil_)).t1;
    struct Ty_ call_257 = tyList_(itemTy_6);
    struct Ty_IntIntTuple2Tuple2 tuple_55;
    tuple_55.t0 = call_257;
    tuple_55.t1 = a_1;
    match_96 = tuple_55;
    goto end_match_364;
next_366:;
    if ((pat_.tag != Discard_)) goto next_367;
    struct Ty_ ty_12 = (*(pat_.Discard_)).t0;
    struct IntIntTuple2 a_2 = (*(pat_.Discard_)).t1;
    struct Ty_IntIntTuple2Tuple2 tuple_56;
    tuple_56.t0 = ty_12;
    tuple_56.t1 = a_2;
    match_96 = tuple_56;
    goto end_match_364;
next_367:;
    if ((pat_.tag != Ref_1)) goto next_368;
    struct Ty_ ty_13 = (*(pat_.Ref_1)).t1;
    struct IntIntTuple2 a_3 = (*(pat_.Ref_1)).t2;
    struct Ty_IntIntTuple2Tuple2 tuple_57;
    tuple_57.t0 = ty_13;
    tuple_57.t1 = a_3;
    match_96 = tuple_57;
    goto end_match_364;
next_368:;
    if ((pat_.tag != Nav_2)) goto next_369;
    struct Ty_ ty_14 = (*(pat_.Nav_2)).t2;
    struct IntIntTuple2 a_4 = (*(pat_.Nav_2)).t3;
    struct Ty_IntIntTuple2Tuple2 tuple_58;
    tuple_58.t0 = ty_14;
    tuple_58.t1 = a_4;
    match_96 = tuple_58;
    goto end_match_364;
next_369:;
    if ((pat_.tag != Call_1)) goto next_370;
    struct Ty_ ty_15 = (*(pat_.Call_1)).t2;
    struct IntIntTuple2 a_5 = (*(pat_.Call_1)).t3;
    struct Ty_IntIntTuple2Tuple2 tuple_59;
    tuple_59.t0 = ty_15;
    tuple_59.t1 = a_5;
    match_96 = tuple_59;
    goto end_match_364;
next_370:;
    if ((pat_.tag != Cons_3)) goto next_371;
    struct Ty_ itemTy_7 = (*(pat_.Cons_3)).t2;
    struct IntIntTuple2 a_6 = (*(pat_.Cons_3)).t3;
    struct Ty_ call_258 = tyList_(itemTy_7);
    struct Ty_IntIntTuple2Tuple2 tuple_60;
    tuple_60.t0 = call_258;
    tuple_60.t1 = a_6;
    match_96 = tuple_60;
    goto end_match_364;
next_371:;
    if ((pat_.tag != Tuple_2)) goto next_372;
    struct Ty_ ty_16 = (*(pat_.Tuple_2)).t1;
    struct IntIntTuple2 a_7 = (*(pat_.Tuple_2)).t2;
    struct Ty_IntIntTuple2Tuple2 tuple_61;
    tuple_61.t0 = ty_16;
    tuple_61.t1 = a_7;
    match_96 = tuple_61;
    goto end_match_364;
next_372:;
    if ((pat_.tag != As_2)) goto next_373;
    struct HPat_ pat_1 = (*(pat_.As_2)).t0;
    struct IntIntTuple2 a_8 = (*(pat_.As_2)).t2;
    struct Ty_IntIntTuple2Tuple2 call_259 = patExtract_(tyStr_, tyChar_, tyInt_, tyBool_, pat_1);
    struct Ty_ ty_17 = call_259.t0;
    struct Ty_IntIntTuple2Tuple2 tuple_62;
    tuple_62.t0 = ty_17;
    tuple_62.t1 = a_8;
    match_96 = tuple_62;
    goto end_match_364;
next_373:;
    if ((pat_.tag != Anno_2)) goto next_374;
    struct Ty_ ty_18 = (*(pat_.Anno_2)).t1;
    struct IntIntTuple2 a_9 = (*(pat_.Anno_2)).t2;
    struct Ty_IntIntTuple2Tuple2 tuple_63;
    tuple_63.t0 = ty_18;
    tuple_63.t1 = a_9;
    match_96 = tuple_63;
    goto end_match_364;
next_374:;
    if ((pat_.tag != Or_3)) goto next_375;
    struct Ty_ ty_19 = (*(pat_.Or_3)).t2;
    struct IntIntTuple2 a_10 = (*(pat_.Or_3)).t3;
    struct Ty_IntIntTuple2Tuple2 tuple_64;
    tuple_64.t0 = ty_19;
    tuple_64.t1 = a_10;
    match_96 = tuple_64;
    goto end_match_364;
next_375:;
    exit(1);
end_match_364:;
    return match_96;
}

struct IntIntTuple2IntIntTuple2Fun1 {
    struct IntIntTuple2(*fun)(void*, struct IntIntTuple2);
    void* env;
};

struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2 {
    struct IntIntTuple2IntIntTuple2Fun1 t0;
    struct Ty_Ty_Fun1 t1;
};

struct HPat_ fun_3(void* env_, struct HPat_ arg_6) {
    struct IntIntTuple2IntIntTuple2Fun1 arg_7 = (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)env_))).t0;
    struct Ty_Ty_Fun1 arg_8 = (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)env_))).t1;
    struct HPat_ call_260 = go_25(arg_7, arg_8, arg_6);
    return call_260;
}

struct HPat_ fun_4(void* env_1, struct HPat_ arg_9) {
    struct IntIntTuple2IntIntTuple2Fun1 arg_10 = (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)env_1))).t0;
    struct Ty_Ty_Fun1 arg_11 = (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)env_1))).t1;
    struct HPat_ call_261 = go_25(arg_10, arg_11, arg_9);
    return call_261;
}

struct HPat_ go_25(struct IntIntTuple2IntIntTuple2Fun1 g_, struct Ty_Ty_Fun1 f_6, struct HPat_ pat_3) {
    struct HPat_ match_97;
    if ((pat_3.tag != Lit_2)) goto next_377;
    struct Lit_ lit_2 = (*(pat_3.Lit_2)).t0;
    struct IntIntTuple2 a_11 = (*(pat_3.Lit_2)).t1;
    struct IntIntTuple2 app_28 = g_.fun(g_.env, a_11);
    struct Lit_IntIntTuple2Tuple2 tuple_65;
    tuple_65.t0 = lit_2;
    tuple_65.t1 = app_28;
    struct Lit_IntIntTuple2Tuple2* payload_37 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_37))) = tuple_65;
    struct HPat_ variant_37 = (struct HPat_){.tag = Lit_2, .Lit_2 = payload_37};
    match_97 = variant_37;
    goto end_match_376;
next_377:;
    if ((pat_3.tag != Nil_)) goto next_378;
    struct Ty_ itemTy_8 = (*(pat_3.Nil_)).t0;
    struct IntIntTuple2 a_12 = (*(pat_3.Nil_)).t1;
    struct Ty_ app_29 = f_6.fun(f_6.env, itemTy_8);
    struct IntIntTuple2 app_30 = g_.fun(g_.env, a_12);
    struct Ty_IntIntTuple2Tuple2 tuple_66;
    tuple_66.t0 = app_29;
    tuple_66.t1 = app_30;
    struct Ty_IntIntTuple2Tuple2* payload_38 = (struct Ty_IntIntTuple2Tuple2*)malloc(sizeof(struct Ty_IntIntTuple2Tuple2));
    (*(((struct Ty_IntIntTuple2Tuple2*)payload_38))) = tuple_66;
    struct HPat_ variant_38 = (struct HPat_){.tag = Nil_, .Nil_ = payload_38};
    match_97 = variant_38;
    goto end_match_376;
next_378:;
    if ((pat_3.tag != Discard_)) goto next_379;
    struct Ty_ ty_20 = (*(pat_3.Discard_)).t0;
    struct IntIntTuple2 a_13 = (*(pat_3.Discard_)).t1;
    struct Ty_ app_31 = f_6.fun(f_6.env, ty_20);
    struct IntIntTuple2 app_32 = g_.fun(g_.env, a_13);
    struct Ty_IntIntTuple2Tuple2 tuple_67;
    tuple_67.t0 = app_31;
    tuple_67.t1 = app_32;
    struct Ty_IntIntTuple2Tuple2* payload_39 = (struct Ty_IntIntTuple2Tuple2*)malloc(sizeof(struct Ty_IntIntTuple2Tuple2));
    (*(((struct Ty_IntIntTuple2Tuple2*)payload_39))) = tuple_67;
    struct HPat_ variant_39 = (struct HPat_){.tag = Discard_, .Discard_ = payload_39};
    match_97 = variant_39;
    goto end_match_376;
next_379:;
    if ((pat_3.tag != Ref_1)) goto next_380;
    int serial_3 = (*(pat_3.Ref_1)).t0;
    struct Ty_ ty_21 = (*(pat_3.Ref_1)).t1;
    struct IntIntTuple2 a_14 = (*(pat_3.Ref_1)).t2;
    struct Ty_ app_33 = f_6.fun(f_6.env, ty_21);
    struct IntIntTuple2 app_34 = g_.fun(g_.env, a_14);
    struct IntTy_IntIntTuple2Tuple3 tuple_68;
    tuple_68.t0 = serial_3;
    tuple_68.t1 = app_33;
    tuple_68.t2 = app_34;
    struct IntTy_IntIntTuple2Tuple3* payload_40 = (struct IntTy_IntIntTuple2Tuple3*)malloc(sizeof(struct IntTy_IntIntTuple2Tuple3));
    (*(((struct IntTy_IntIntTuple2Tuple3*)payload_40))) = tuple_68;
    struct HPat_ variant_40 = (struct HPat_){.tag = Ref_1, .Ref_1 = payload_40};
    match_97 = variant_40;
    goto end_match_376;
next_380:;
    if ((pat_3.tag != Nav_2)) goto next_381;
    struct HPat_ pat_4 = (*(pat_3.Nav_2)).t0;
    struct String ident_7 = (*(pat_3.Nav_2)).t1;
    struct Ty_ ty_22 = (*(pat_3.Nav_2)).t2;
    struct IntIntTuple2 a_15 = (*(pat_3.Nav_2)).t3;
    struct Ty_ app_35 = f_6.fun(f_6.env, ty_22);
    struct IntIntTuple2 app_36 = g_.fun(g_.env, a_15);
    struct HPat_StringTy_IntIntTuple2Tuple4 tuple_69;
    tuple_69.t0 = pat_4;
    tuple_69.t1 = ident_7;
    tuple_69.t2 = app_35;
    tuple_69.t3 = app_36;
    struct HPat_StringTy_IntIntTuple2Tuple4* payload_41 = (struct HPat_StringTy_IntIntTuple2Tuple4*)malloc(sizeof(struct HPat_StringTy_IntIntTuple2Tuple4));
    (*(((struct HPat_StringTy_IntIntTuple2Tuple4*)payload_41))) = tuple_69;
    struct HPat_ variant_41 = (struct HPat_){.tag = Nav_2, .Nav_2 = payload_41};
    match_97 = variant_41;
    goto end_match_376;
next_381:;
    if ((pat_3.tag != Call_1)) goto next_382;
    struct HPat_ callee_ = (*(pat_3.Call_1)).t0;
    struct HPat_List* args_ = (*(pat_3.Call_1)).t1;
    struct Ty_ ty_23 = (*(pat_3.Call_1)).t2;
    struct IntIntTuple2 a_16 = (*(pat_3.Call_1)).t3;
    struct HPat_ call_262 = go_25(g_, f_6, callee_);
    struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2 tuple_71;
    tuple_71.t0 = g_;
    tuple_71.t1 = f_6;
    void* box_ = (void*)malloc(sizeof(struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2));
    (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)box_))) = tuple_71;
    void* env_36 = box_;
    struct HPat_HPat_Fun1 fun_40 = (struct HPat_HPat_Fun1){.fun = fun_3, .env = env_36};
    struct HPat_List* call_263 = listMap_8(fun_40, args_);
    struct Ty_ app_37 = f_6.fun(f_6.env, ty_23);
    struct IntIntTuple2 app_38 = g_.fun(g_.env, a_16);
    struct HPat_HPat_ListTy_IntIntTuple2Tuple4 tuple_70;
    tuple_70.t0 = call_262;
    tuple_70.t1 = call_263;
    tuple_70.t2 = app_37;
    tuple_70.t3 = app_38;
    struct HPat_HPat_ListTy_IntIntTuple2Tuple4* payload_42 = (struct HPat_HPat_ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct HPat_HPat_ListTy_IntIntTuple2Tuple4));
    (*(((struct HPat_HPat_ListTy_IntIntTuple2Tuple4*)payload_42))) = tuple_70;
    struct HPat_ variant_42 = (struct HPat_){.tag = Call_1, .Call_1 = payload_42};
    match_97 = variant_42;
    goto end_match_376;
next_382:;
    if ((pat_3.tag != Cons_3)) goto next_383;
    struct HPat_ l_10 = (*(pat_3.Cons_3)).t0;
    struct HPat_ r_23 = (*(pat_3.Cons_3)).t1;
    struct Ty_ itemTy_9 = (*(pat_3.Cons_3)).t2;
    struct IntIntTuple2 a_17 = (*(pat_3.Cons_3)).t3;
    struct HPat_ call_264 = go_25(g_, f_6, l_10);
    struct HPat_ call_265 = go_25(g_, f_6, r_23);
    struct Ty_ app_39 = f_6.fun(f_6.env, itemTy_9);
    struct IntIntTuple2 app_40 = g_.fun(g_.env, a_17);
    struct HPat_HPat_Ty_IntIntTuple2Tuple4 tuple_72;
    tuple_72.t0 = call_264;
    tuple_72.t1 = call_265;
    tuple_72.t2 = app_39;
    tuple_72.t3 = app_40;
    struct HPat_HPat_Ty_IntIntTuple2Tuple4* payload_43 = (struct HPat_HPat_Ty_IntIntTuple2Tuple4*)malloc(sizeof(struct HPat_HPat_Ty_IntIntTuple2Tuple4));
    (*(((struct HPat_HPat_Ty_IntIntTuple2Tuple4*)payload_43))) = tuple_72;
    struct HPat_ variant_43 = (struct HPat_){.tag = Cons_3, .Cons_3 = payload_43};
    match_97 = variant_43;
    goto end_match_376;
next_383:;
    if ((pat_3.tag != Tuple_2)) goto next_384;
    struct HPat_List* itemPats_ = (*(pat_3.Tuple_2)).t0;
    struct Ty_ ty_24 = (*(pat_3.Tuple_2)).t1;
    struct IntIntTuple2 a_18 = (*(pat_3.Tuple_2)).t2;
    struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2 tuple_74;
    tuple_74.t0 = g_;
    tuple_74.t1 = f_6;
    void* box_1 = (void*)malloc(sizeof(struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2));
    (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)box_1))) = tuple_74;
    void* env_37 = box_1;
    struct HPat_HPat_Fun1 fun_41 = (struct HPat_HPat_Fun1){.fun = fun_4, .env = env_37};
    struct HPat_List* call_266 = listMap_8(fun_41, itemPats_);
    struct Ty_ app_41 = f_6.fun(f_6.env, ty_24);
    struct IntIntTuple2 app_42 = g_.fun(g_.env, a_18);
    struct HPat_ListTy_IntIntTuple2Tuple3 tuple_73;
    tuple_73.t0 = call_266;
    tuple_73.t1 = app_41;
    tuple_73.t2 = app_42;
    struct HPat_ListTy_IntIntTuple2Tuple3* payload_44 = (struct HPat_ListTy_IntIntTuple2Tuple3*)malloc(sizeof(struct HPat_ListTy_IntIntTuple2Tuple3));
    (*(((struct HPat_ListTy_IntIntTuple2Tuple3*)payload_44))) = tuple_73;
    struct HPat_ variant_44 = (struct HPat_){.tag = Tuple_2, .Tuple_2 = payload_44};
    match_97 = variant_44;
    goto end_match_376;
next_384:;
    if ((pat_3.tag != As_2)) goto next_385;
    struct HPat_ pat_5 = (*(pat_3.As_2)).t0;
    int serial_4 = (*(pat_3.As_2)).t1;
    struct IntIntTuple2 a_19 = (*(pat_3.As_2)).t2;
    struct HPat_ call_267 = go_25(g_, f_6, pat_5);
    struct IntIntTuple2 app_43 = g_.fun(g_.env, a_19);
    struct HPat_IntIntIntTuple2Tuple3 tuple_75;
    tuple_75.t0 = call_267;
    tuple_75.t1 = serial_4;
    tuple_75.t2 = app_43;
    struct HPat_IntIntIntTuple2Tuple3* payload_45 = (struct HPat_IntIntIntTuple2Tuple3*)malloc(sizeof(struct HPat_IntIntIntTuple2Tuple3));
    (*(((struct HPat_IntIntIntTuple2Tuple3*)payload_45))) = tuple_75;
    struct HPat_ variant_45 = (struct HPat_){.tag = As_2, .As_2 = payload_45};
    match_97 = variant_45;
    goto end_match_376;
next_385:;
    if ((pat_3.tag != Anno_2)) goto next_386;
    struct HPat_ pat_6 = (*(pat_3.Anno_2)).t0;
    struct Ty_ ty_25 = (*(pat_3.Anno_2)).t1;
    struct IntIntTuple2 a_20 = (*(pat_3.Anno_2)).t2;
    struct HPat_ call_268 = go_25(g_, f_6, pat_6);
    struct Ty_ app_44 = f_6.fun(f_6.env, ty_25);
    struct IntIntTuple2 app_45 = g_.fun(g_.env, a_20);
    struct HPat_Ty_IntIntTuple2Tuple3 tuple_76;
    tuple_76.t0 = call_268;
    tuple_76.t1 = app_44;
    tuple_76.t2 = app_45;
    struct HPat_Ty_IntIntTuple2Tuple3* payload_46 = (struct HPat_Ty_IntIntTuple2Tuple3*)malloc(sizeof(struct HPat_Ty_IntIntTuple2Tuple3));
    (*(((struct HPat_Ty_IntIntTuple2Tuple3*)payload_46))) = tuple_76;
    struct HPat_ variant_46 = (struct HPat_){.tag = Anno_2, .Anno_2 = payload_46};
    match_97 = variant_46;
    goto end_match_376;
next_386:;
    if ((pat_3.tag != Or_3)) goto next_387;
    struct HPat_ first_2 = (*(pat_3.Or_3)).t0;
    struct HPat_ second_2 = (*(pat_3.Or_3)).t1;
    struct Ty_ ty_26 = (*(pat_3.Or_3)).t2;
    struct IntIntTuple2 a_21 = (*(pat_3.Or_3)).t3;
    struct HPat_ call_269 = go_25(g_, f_6, first_2);
    struct HPat_ call_270 = go_25(g_, f_6, second_2);
    struct Ty_ app_46 = f_6.fun(f_6.env, ty_26);
    struct IntIntTuple2 app_47 = g_.fun(g_.env, a_21);
    struct HPat_HPat_Ty_IntIntTuple2Tuple4 tuple_77;
    tuple_77.t0 = call_269;
    tuple_77.t1 = call_270;
    tuple_77.t2 = app_46;
    tuple_77.t3 = app_47;
    struct HPat_HPat_Ty_IntIntTuple2Tuple4* payload_47 = (struct HPat_HPat_Ty_IntIntTuple2Tuple4*)malloc(sizeof(struct HPat_HPat_Ty_IntIntTuple2Tuple4));
    (*(((struct HPat_HPat_Ty_IntIntTuple2Tuple4*)payload_47))) = tuple_77;
    struct HPat_ variant_47 = (struct HPat_){.tag = Or_3, .Or_3 = payload_47};
    match_97 = variant_47;
    goto end_match_376;
next_387:;
    exit(1);
end_match_376:;
    return match_97;
}

struct HPat_ patMap_(struct Ty_Ty_Fun1 f_6, struct IntIntTuple2IntIntTuple2Fun1 g_, struct HPat_ pat_2) {
    struct HPat_ call_271 = go_25(g_, f_6, pat_2);
    return call_271;
}

struct HExpr_ hxTrue_(struct Lit_ litTrue_, struct IntIntTuple2 loc_13) {
    struct Lit_IntIntTuple2Tuple2 tuple_78;
    tuple_78.t0 = litTrue_;
    tuple_78.t1 = loc_13;
    struct Lit_IntIntTuple2Tuple2* payload_48 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_48))) = tuple_78;
    struct HExpr_ variant_48 = (struct HExpr_){.tag = Lit_3, .Lit_3 = payload_48};
    return variant_48;
}

struct HExpr_ hxFalse_(struct Lit_ litFalse_, struct IntIntTuple2 loc_14) {
    struct Lit_IntIntTuple2Tuple2 tuple_79;
    tuple_79.t0 = litFalse_;
    tuple_79.t1 = loc_14;
    struct Lit_IntIntTuple2Tuple2* payload_49 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_49))) = tuple_79;
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

struct HExpr_ hxApp_(struct HExpr_ f_7, struct HExpr_ x_19, struct Ty_ ty_27, struct IntIntTuple2 loc_15) {
    struct HExpr_List* list_49 = (struct HExpr_List*)malloc(sizeof(struct HExpr_List));
    list_49->head = x_19;
    list_49->tail = NULL;
    struct HExpr_List* list_48 = (struct HExpr_List*)malloc(sizeof(struct HExpr_List));
    list_48->head = f_7;
    list_48->tail = list_49;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4 tuple_80;
    tuple_80.t0 = (struct InfOp_){.tag = App_2};
    tuple_80.t1 = list_48;
    tuple_80.t2 = ty_27;
    tuple_80.t3 = loc_15;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4* payload_50 = (struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4));
    (*(((struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)payload_50))) = tuple_80;
    struct HExpr_ variant_50 = (struct HExpr_){.tag = Inf_, .Inf_ = payload_50};
    return variant_50;
}

struct HExpr_ hxAnno_(struct HExpr_ expr_, struct Ty_ ty_28, struct IntIntTuple2 loc_16) {
    struct HExpr_List* list_50 = (struct HExpr_List*)malloc(sizeof(struct HExpr_List));
    list_50->head = expr_;
    list_50->tail = NULL;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4 tuple_81;
    tuple_81.t0 = (struct InfOp_){.tag = Anno_3};
    tuple_81.t1 = list_50;
    tuple_81.t2 = ty_28;
    tuple_81.t3 = loc_16;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4* payload_51 = (struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4));
    (*(((struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)payload_51))) = tuple_81;
    struct HExpr_ variant_51 = (struct HExpr_){.tag = Inf_, .Inf_ = payload_51};
    return variant_51;
}

struct HExpr_ hxSemi_(struct Ty_ noTy_, struct HExpr_List* items_, struct IntIntTuple2 loc_17) {
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4 tuple_82;
    tuple_82.t0 = (struct InfOp_){.tag = Semi_2};
    tuple_82.t1 = items_;
    tuple_82.t2 = noTy_;
    tuple_82.t3 = loc_17;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4* payload_52 = (struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4));
    (*(((struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)payload_52))) = tuple_82;
    struct HExpr_ variant_52 = (struct HExpr_){.tag = Inf_, .Inf_ = payload_52};
    return variant_52;
}

struct HExpr_ hxCallProc_(struct HExpr_ callee_1, struct HExpr_List* args_1, struct Ty_ resultTy_2, struct IntIntTuple2 loc_18) {
    struct HExpr_List* list_51 = (struct HExpr_List*)malloc(sizeof(struct HExpr_List));
    list_51->head = callee_1;
    list_51->tail = args_1;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4 tuple_83;
    tuple_83.t0 = (struct InfOp_){.tag = CallProc_};
    tuple_83.t1 = list_51;
    tuple_83.t2 = resultTy_2;
    tuple_83.t3 = loc_18;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4* payload_53 = (struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4));
    (*(((struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)payload_53))) = tuple_83;
    struct HExpr_ variant_53 = (struct HExpr_){.tag = Inf_, .Inf_ = payload_53};
    return variant_53;
}

struct HExpr_ hxCallClosure_(struct HExpr_ callee_2, struct HExpr_List* args_2, struct Ty_ resultTy_3, struct IntIntTuple2 loc_19) {
    struct HExpr_List* list_52 = (struct HExpr_List*)malloc(sizeof(struct HExpr_List));
    list_52->head = callee_2;
    list_52->tail = args_2;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4 tuple_84;
    tuple_84.t0 = (struct InfOp_){.tag = CallClosure_};
    tuple_84.t1 = list_52;
    tuple_84.t2 = resultTy_3;
    tuple_84.t3 = loc_19;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4* payload_54 = (struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4));
    (*(((struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)payload_54))) = tuple_84;
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

struct Ty_ fun_5(void* env_2, struct HExpr_ arg_12) {
    struct Ty_ arg_13 = (*(((struct Ty_Ty_Ty_Ty_Ty_Tuple5*)env_2))).t0;
    struct Ty_ arg_14 = (*(((struct Ty_Ty_Ty_Ty_Ty_Tuple5*)env_2))).t1;
    struct Ty_ arg_15 = (*(((struct Ty_Ty_Ty_Ty_Ty_Tuple5*)env_2))).t2;
    struct Ty_ arg_16 = (*(((struct Ty_Ty_Ty_Ty_Ty_Tuple5*)env_2))).t3;
    struct Ty_ arg_17 = (*(((struct Ty_Ty_Ty_Ty_Ty_Tuple5*)env_2))).t4;
    struct Ty_ call_272 = exprToTy_(arg_13, arg_14, arg_15, arg_16, arg_17, arg_12);
    return call_272;
}

struct HExpr_ hxTuple_(struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct HExpr_List* items_1, struct IntIntTuple2 loc_20) {
    struct Ty_Ty_Ty_Ty_Ty_Tuple5 tuple_86;
    tuple_86.t0 = tyUnit_;
    tuple_86.t1 = tyStr_;
    tuple_86.t2 = tyChar_;
    tuple_86.t3 = tyInt_;
    tuple_86.t4 = tyBool_;
    void* box_2 = (void*)malloc(sizeof(struct Ty_Ty_Ty_Ty_Ty_Tuple5));
    (*(((struct Ty_Ty_Ty_Ty_Ty_Tuple5*)box_2))) = tuple_86;
    void* env_38 = box_2;
    struct HExpr_Ty_Fun1 fun_42 = (struct HExpr_Ty_Fun1){.fun = fun_5, .env = env_38};
    struct Ty_List* call_273 = listMap_11(fun_42, items_1);
    struct Ty_ call_274 = tyTuple_(call_273);
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4 tuple_85;
    tuple_85.t0 = (struct InfOp_){.tag = Tuple_3};
    tuple_85.t1 = items_1;
    tuple_85.t2 = call_274;
    tuple_85.t3 = loc_20;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4* payload_55 = (struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4));
    (*(((struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)payload_55))) = tuple_85;
    struct HExpr_ variant_55 = (struct HExpr_){.tag = Inf_, .Inf_ = payload_55};
    return variant_55;
}

struct HExpr_ hxUnit_(struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct IntIntTuple2 loc_21) {
    struct HExpr_ call_275 = hxTuple_(tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, NULL, loc_21);
    return call_275;
}

struct HPrim_Ty_IntIntTuple2Tuple3 {
    struct HPrim_ t0;
    struct Ty_ t1;
    struct IntIntTuple2 t2;
};

struct HExpr_ hxNil_(struct Ty_ itemTy_10, struct IntIntTuple2 loc_22) {
    struct Ty_ call_276 = tyList_(itemTy_10);
    struct HPrim_Ty_IntIntTuple2Tuple3 tuple_87;
    tuple_87.t0 = (struct HPrim_){.tag = Nil_1};
    tuple_87.t1 = call_276;
    tuple_87.t2 = loc_22;
    struct HPrim_Ty_IntIntTuple2Tuple3* payload_56 = (struct HPrim_Ty_IntIntTuple2Tuple3*)malloc(sizeof(struct HPrim_Ty_IntIntTuple2Tuple3));
    (*(((struct HPrim_Ty_IntIntTuple2Tuple3*)payload_56))) = tuple_87;
    struct HExpr_ variant_56 = (struct HExpr_){.tag = Prim_, .Prim_ = payload_56};
    return variant_56;
}

int hxIsUnitLit_(struct HExpr_ expr_1) {
    int match_98;
    if ((expr_1.tag != Inf_)) goto next_389;
    if (((*(expr_1.Inf_)).t0.tag != Tuple_3)) goto next_389;
    if ((!((!((*(expr_1.Inf_)).t1))))) goto next_389;
    match_98 = 1;
    goto end_match_388;
next_389:;
    match_98 = 0;
    goto end_match_388;
next_390:;
end_match_388:;
    return match_98;
}

int hxIsAlwaysTrue_(struct HExpr_ expr_2) {
    int match_99;
    if ((expr_2.tag != Lit_3)) goto next_392;
    if (((*(expr_2.Lit_3)).t0.tag != Bool_)) goto next_392;
    if ((!((*((*(expr_2.Lit_3)).t0.Bool_))))) goto next_392;
    match_99 = 1;
    goto end_match_391;
next_392:;
    match_99 = 0;
    goto end_match_391;
next_393:;
end_match_391:;
    return match_99;
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
    struct Ty_IntIntTuple2Tuple2 match_100;
    if ((expr_3.tag != Lit_3)) goto next_395;
    struct Lit_ lit_3 = (*(expr_3.Lit_3)).t0;
    struct IntIntTuple2 a_22 = (*(expr_3.Lit_3)).t1;
    struct Ty_ call_277 = litToTy_(tyStr_, tyChar_, tyInt_, tyBool_, lit_3);
    struct Ty_IntIntTuple2Tuple2 tuple_88;
    tuple_88.t0 = call_277;
    tuple_88.t1 = a_22;
    match_100 = tuple_88;
    goto end_match_394;
next_395:;
    if ((expr_3.tag != Ref_2)) goto next_396;
    struct Ty_ ty_29 = (*(expr_3.Ref_2)).t1;
    struct IntIntTuple2 a_23 = (*(expr_3.Ref_2)).t2;
    struct Ty_IntIntTuple2Tuple2 tuple_89;
    tuple_89.t0 = ty_29;
    tuple_89.t1 = a_23;
    match_100 = tuple_89;
    goto end_match_394;
next_396:;
    if ((expr_3.tag != Prim_)) goto next_397;
    struct Ty_ ty_30 = (*(expr_3.Prim_)).t1;
    struct IntIntTuple2 a_24 = (*(expr_3.Prim_)).t2;
    struct Ty_IntIntTuple2Tuple2 tuple_90;
    tuple_90.t0 = ty_30;
    tuple_90.t1 = a_24;
    match_100 = tuple_90;
    goto end_match_394;
next_397:;
    if ((expr_3.tag != Match_2)) goto next_398;
    struct Ty_ ty_31 = (*(expr_3.Match_2)).t2;
    struct IntIntTuple2 a_25 = (*(expr_3.Match_2)).t3;
    struct Ty_IntIntTuple2Tuple2 tuple_91;
    tuple_91.t0 = ty_31;
    tuple_91.t1 = a_25;
    match_100 = tuple_91;
    goto end_match_394;
next_398:;
    if ((expr_3.tag != Nav_3)) goto next_399;
    struct Ty_ ty_32 = (*(expr_3.Nav_3)).t2;
    struct IntIntTuple2 a_26 = (*(expr_3.Nav_3)).t3;
    struct Ty_IntIntTuple2Tuple2 tuple_92;
    tuple_92.t0 = ty_32;
    tuple_92.t1 = a_26;
    match_100 = tuple_92;
    goto end_match_394;
next_399:;
    if ((expr_3.tag != Inf_)) goto next_400;
    struct Ty_ ty_33 = (*(expr_3.Inf_)).t2;
    struct IntIntTuple2 a_27 = (*(expr_3.Inf_)).t3;
    struct Ty_IntIntTuple2Tuple2 tuple_93;
    tuple_93.t0 = ty_33;
    tuple_93.t1 = a_27;
    match_100 = tuple_93;
    goto end_match_394;
next_400:;
    if ((expr_3.tag != Let_2)) goto next_401;
    struct Ty_ ty_34 = (*(expr_3.Let_2)).t3;
    struct IntIntTuple2 a_28 = (*(expr_3.Let_2)).t4;
    struct Ty_IntIntTuple2Tuple2 tuple_94;
    tuple_94.t0 = ty_34;
    tuple_94.t1 = a_28;
    match_100 = tuple_94;
    goto end_match_394;
next_401:;
    if ((expr_3.tag != LetFun_1)) goto next_402;
    struct Ty_ ty_35 = (*(expr_3.LetFun_1)).t5;
    struct IntIntTuple2 a_29 = (*(expr_3.LetFun_1)).t6;
    struct Ty_IntIntTuple2Tuple2 tuple_95;
    tuple_95.t0 = ty_35;
    tuple_95.t1 = a_29;
    match_100 = tuple_95;
    goto end_match_394;
next_402:;
    if ((expr_3.tag != TyDecl_)) goto next_403;
    struct IntIntTuple2 a_30 = (*(expr_3.TyDecl_)).t2;
    struct Ty_IntIntTuple2Tuple2 tuple_96;
    tuple_96.t0 = tyUnit_;
    tuple_96.t1 = a_30;
    match_100 = tuple_96;
    goto end_match_394;
next_403:;
    if ((expr_3.tag != Open_2)) goto next_404;
    struct IntIntTuple2 a_31 = (*(expr_3.Open_2)).t1;
    struct Ty_IntIntTuple2Tuple2 tuple_97;
    tuple_97.t0 = tyUnit_;
    tuple_97.t1 = a_31;
    match_100 = tuple_97;
    goto end_match_394;
next_404:;
    if ((expr_3.tag != Error_2)) goto next_405;
    struct IntIntTuple2 a_32 = (*(expr_3.Error_2)).t1;
    struct IntIntTuple2* payload_57 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_57))) = a_32;
    struct Ty_ variant_57 = (struct Ty_){.tag = Error_1, .Error_1 = payload_57};
    struct Ty_IntIntTuple2Tuple2 tuple_98;
    tuple_98.t0 = variant_57;
    tuple_98.t1 = a_32;
    match_100 = tuple_98;
    goto end_match_394;
next_405:;
    exit(1);
end_match_394:;
    return match_100;
}

struct HPat_ goPat_(struct IntIntTuple2IntIntTuple2Fun1 g_1, struct Ty_Ty_Fun1 f_8, struct HPat_ pat_7) {
    struct HPat_ call_278 = patMap_(f_8, g_1, pat_7);
    return call_278;
}

struct HPat_HExpr_HExpr_Tuple3 fun_(struct IntIntTuple2IntIntTuple2Fun1 g_1, struct Ty_Ty_Fun1 f_8, struct HPat_HExpr_HExpr_Tuple3 arg_104) {
    struct HPat_ pat_8 = arg_104.t0;
    struct HExpr_ guard_ = arg_104.t1;
    struct HExpr_ body_ = arg_104.t2;
    struct HPat_ call_279 = goPat_(g_1, f_8, pat_8);
    struct HExpr_ call_280 = go_26(g_1, f_8, guard_);
    struct HExpr_ call_281 = go_26(g_1, f_8, body_);
    struct HPat_HExpr_HExpr_Tuple3 tuple_99;
    tuple_99.t0 = call_279;
    tuple_99.t1 = call_280;
    tuple_99.t2 = call_281;
    return tuple_99;
}

struct HPat_HExpr_HExpr_Tuple3 fun_6(void* env_3, struct HPat_HExpr_HExpr_Tuple3 arg_18) {
    struct IntIntTuple2IntIntTuple2Fun1 arg_19 = (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)env_3))).t0;
    struct Ty_Ty_Fun1 arg_20 = (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)env_3))).t1;
    struct HPat_HExpr_HExpr_Tuple3 call_282 = fun_(arg_19, arg_20, arg_18);
    return call_282;
}

struct HExpr_ fun_7(void* env_4, struct HExpr_ arg_21) {
    struct IntIntTuple2IntIntTuple2Fun1 arg_22 = (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)env_4))).t0;
    struct Ty_Ty_Fun1 arg_23 = (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)env_4))).t1;
    struct HExpr_ call_283 = go_26(arg_22, arg_23, arg_21);
    return call_283;
}

struct HPat_ fun_8(void* env_5, struct HPat_ arg_24) {
    struct IntIntTuple2IntIntTuple2Fun1 arg_25 = (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)env_5))).t0;
    struct Ty_Ty_Fun1 arg_26 = (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)env_5))).t1;
    struct HPat_ call_284 = goPat_(arg_25, arg_26, arg_24);
    return call_284;
}

struct HExpr_ go_26(struct IntIntTuple2IntIntTuple2Fun1 g_1, struct Ty_Ty_Fun1 f_8, struct HExpr_ expr_5) {
    struct HExpr_ match_101;
    if ((expr_5.tag != Lit_3)) goto next_407;
    struct Lit_ lit_4 = (*(expr_5.Lit_3)).t0;
    struct IntIntTuple2 a_33 = (*(expr_5.Lit_3)).t1;
    struct IntIntTuple2 app_48 = g_1.fun(g_1.env, a_33);
    struct Lit_IntIntTuple2Tuple2 tuple_100;
    tuple_100.t0 = lit_4;
    tuple_100.t1 = app_48;
    struct Lit_IntIntTuple2Tuple2* payload_58 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_58))) = tuple_100;
    struct HExpr_ variant_58 = (struct HExpr_){.tag = Lit_3, .Lit_3 = payload_58};
    match_101 = variant_58;
    goto end_match_406;
next_407:;
    if ((expr_5.tag != Ref_2)) goto next_408;
    int serial_5 = (*(expr_5.Ref_2)).t0;
    struct Ty_ ty_36 = (*(expr_5.Ref_2)).t1;
    struct IntIntTuple2 a_34 = (*(expr_5.Ref_2)).t2;
    struct Ty_ app_49 = f_8.fun(f_8.env, ty_36);
    struct IntIntTuple2 app_50 = g_1.fun(g_1.env, a_34);
    struct IntTy_IntIntTuple2Tuple3 tuple_101;
    tuple_101.t0 = serial_5;
    tuple_101.t1 = app_49;
    tuple_101.t2 = app_50;
    struct IntTy_IntIntTuple2Tuple3* payload_59 = (struct IntTy_IntIntTuple2Tuple3*)malloc(sizeof(struct IntTy_IntIntTuple2Tuple3));
    (*(((struct IntTy_IntIntTuple2Tuple3*)payload_59))) = tuple_101;
    struct HExpr_ variant_59 = (struct HExpr_){.tag = Ref_2, .Ref_2 = payload_59};
    match_101 = variant_59;
    goto end_match_406;
next_408:;
    if ((expr_5.tag != Prim_)) goto next_409;
    struct HPrim_ prim_1 = (*(expr_5.Prim_)).t0;
    struct Ty_ ty_37 = (*(expr_5.Prim_)).t1;
    struct IntIntTuple2 a_35 = (*(expr_5.Prim_)).t2;
    struct Ty_ app_51 = f_8.fun(f_8.env, ty_37);
    struct IntIntTuple2 app_52 = g_1.fun(g_1.env, a_35);
    struct HPrim_Ty_IntIntTuple2Tuple3 tuple_102;
    tuple_102.t0 = prim_1;
    tuple_102.t1 = app_51;
    tuple_102.t2 = app_52;
    struct HPrim_Ty_IntIntTuple2Tuple3* payload_60 = (struct HPrim_Ty_IntIntTuple2Tuple3*)malloc(sizeof(struct HPrim_Ty_IntIntTuple2Tuple3));
    (*(((struct HPrim_Ty_IntIntTuple2Tuple3*)payload_60))) = tuple_102;
    struct HExpr_ variant_60 = (struct HExpr_){.tag = Prim_, .Prim_ = payload_60};
    match_101 = variant_60;
    goto end_match_406;
next_409:;
    if ((expr_5.tag != Match_2)) goto next_410;
    struct HExpr_ target_ = (*(expr_5.Match_2)).t0;
    struct HPat_HExpr_HExpr_Tuple3List* arms_ = (*(expr_5.Match_2)).t1;
    struct Ty_ ty_38 = (*(expr_5.Match_2)).t2;
    struct IntIntTuple2 a_36 = (*(expr_5.Match_2)).t3;
    struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2 tuple_103;
    tuple_103.t0 = g_1;
    tuple_103.t1 = f_8;
    void* box_3 = (void*)malloc(sizeof(struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2));
    (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)box_3))) = tuple_103;
    void* env_39 = box_3;
    struct HPat_HExpr_HExpr_Tuple3HPat_HExpr_HExpr_Tuple3Fun1 fun_43 = (struct HPat_HExpr_HExpr_Tuple3HPat_HExpr_HExpr_Tuple3Fun1){.fun = fun_6, .env = env_39};
    struct HPat_HExpr_HExpr_Tuple3List* call_285 = listMap_10(fun_43, arms_);
    struct HPat_HExpr_HExpr_Tuple3List* arms_1 = call_285;
    struct HExpr_ call_286 = go_26(g_1, f_8, target_);
    struct Ty_ app_53 = f_8.fun(f_8.env, ty_38);
    struct IntIntTuple2 app_54 = g_1.fun(g_1.env, a_36);
    struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4 tuple_104;
    tuple_104.t0 = call_286;
    tuple_104.t1 = arms_1;
    tuple_104.t2 = app_53;
    tuple_104.t3 = app_54;
    struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4* payload_61 = (struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4));
    (*(((struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4*)payload_61))) = tuple_104;
    struct HExpr_ variant_61 = (struct HExpr_){.tag = Match_2, .Match_2 = payload_61};
    match_101 = variant_61;
    goto end_match_406;
next_410:;
    if ((expr_5.tag != Nav_3)) goto next_411;
    struct HExpr_ sub_ = (*(expr_5.Nav_3)).t0;
    struct String mes_ = (*(expr_5.Nav_3)).t1;
    struct Ty_ ty_39 = (*(expr_5.Nav_3)).t2;
    struct IntIntTuple2 a_37 = (*(expr_5.Nav_3)).t3;
    struct HExpr_ call_287 = go_26(g_1, f_8, sub_);
    struct Ty_ app_55 = f_8.fun(f_8.env, ty_39);
    struct IntIntTuple2 app_56 = g_1.fun(g_1.env, a_37);
    struct HExpr_StringTy_IntIntTuple2Tuple4 tuple_105;
    tuple_105.t0 = call_287;
    tuple_105.t1 = mes_;
    tuple_105.t2 = app_55;
    tuple_105.t3 = app_56;
    struct HExpr_StringTy_IntIntTuple2Tuple4* payload_62 = (struct HExpr_StringTy_IntIntTuple2Tuple4*)malloc(sizeof(struct HExpr_StringTy_IntIntTuple2Tuple4));
    (*(((struct HExpr_StringTy_IntIntTuple2Tuple4*)payload_62))) = tuple_105;
    struct HExpr_ variant_62 = (struct HExpr_){.tag = Nav_3, .Nav_3 = payload_62};
    match_101 = variant_62;
    goto end_match_406;
next_411:;
    if ((expr_5.tag != Inf_)) goto next_412;
    struct InfOp_ infOp_ = (*(expr_5.Inf_)).t0;
    struct HExpr_List* args_3 = (*(expr_5.Inf_)).t1;
    struct Ty_ resultTy_4 = (*(expr_5.Inf_)).t2;
    struct IntIntTuple2 a_38 = (*(expr_5.Inf_)).t3;
    struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2 tuple_107;
    tuple_107.t0 = g_1;
    tuple_107.t1 = f_8;
    void* box_4 = (void*)malloc(sizeof(struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2));
    (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)box_4))) = tuple_107;
    void* env_40 = box_4;
    struct HExpr_HExpr_Fun1 fun_44 = (struct HExpr_HExpr_Fun1){.fun = fun_7, .env = env_40};
    struct HExpr_List* call_288 = listMap_9(fun_44, args_3);
    struct Ty_ app_57 = f_8.fun(f_8.env, resultTy_4);
    struct IntIntTuple2 app_58 = g_1.fun(g_1.env, a_38);
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4 tuple_106;
    tuple_106.t0 = infOp_;
    tuple_106.t1 = call_288;
    tuple_106.t2 = app_57;
    tuple_106.t3 = app_58;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4* payload_63 = (struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4));
    (*(((struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)payload_63))) = tuple_106;
    struct HExpr_ variant_63 = (struct HExpr_){.tag = Inf_, .Inf_ = payload_63};
    match_101 = variant_63;
    goto end_match_406;
next_412:;
    if ((expr_5.tag != Let_2)) goto next_413;
    struct HPat_ pat_9 = (*(expr_5.Let_2)).t0;
    struct HExpr_ init_ = (*(expr_5.Let_2)).t1;
    struct HExpr_ next_6 = (*(expr_5.Let_2)).t2;
    struct Ty_ ty_40 = (*(expr_5.Let_2)).t3;
    struct IntIntTuple2 a_39 = (*(expr_5.Let_2)).t4;
    struct HPat_ call_289 = goPat_(g_1, f_8, pat_9);
    struct HExpr_ call_290 = go_26(g_1, f_8, init_);
    struct HExpr_ call_291 = go_26(g_1, f_8, next_6);
    struct Ty_ app_59 = f_8.fun(f_8.env, ty_40);
    struct IntIntTuple2 app_60 = g_1.fun(g_1.env, a_39);
    struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5 tuple_108;
    tuple_108.t0 = call_289;
    tuple_108.t1 = call_290;
    tuple_108.t2 = call_291;
    tuple_108.t3 = app_59;
    tuple_108.t4 = app_60;
    struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5* payload_64 = (struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5*)malloc(sizeof(struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5));
    (*(((struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5*)payload_64))) = tuple_108;
    struct HExpr_ variant_64 = (struct HExpr_){.tag = Let_2, .Let_2 = payload_64};
    match_101 = variant_64;
    goto end_match_406;
next_413:;
    if ((expr_5.tag != LetFun_1)) goto next_414;
    int serial_6 = (*(expr_5.LetFun_1)).t0;
    int isMainFun_ = (*(expr_5.LetFun_1)).t1;
    struct HPat_List* args_4 = (*(expr_5.LetFun_1)).t2;
    struct HExpr_ body_1 = (*(expr_5.LetFun_1)).t3;
    struct HExpr_ next_7 = (*(expr_5.LetFun_1)).t4;
    struct Ty_ ty_41 = (*(expr_5.LetFun_1)).t5;
    struct IntIntTuple2 a_40 = (*(expr_5.LetFun_1)).t6;
    struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2 tuple_110;
    tuple_110.t0 = g_1;
    tuple_110.t1 = f_8;
    void* box_5 = (void*)malloc(sizeof(struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2));
    (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)box_5))) = tuple_110;
    void* env_41 = box_5;
    struct HPat_HPat_Fun1 fun_45 = (struct HPat_HPat_Fun1){.fun = fun_8, .env = env_41};
    struct HPat_List* call_292 = listMap_8(fun_45, args_4);
    struct HExpr_ call_293 = go_26(g_1, f_8, body_1);
    struct HExpr_ call_294 = go_26(g_1, f_8, next_7);
    struct Ty_ app_61 = f_8.fun(f_8.env, ty_41);
    struct IntIntTuple2 app_62 = g_1.fun(g_1.env, a_40);
    struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7 tuple_109;
    tuple_109.t0 = serial_6;
    tuple_109.t1 = isMainFun_;
    tuple_109.t2 = call_292;
    tuple_109.t3 = call_293;
    tuple_109.t4 = call_294;
    tuple_109.t5 = app_61;
    tuple_109.t6 = app_62;
    struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7* payload_65 = (struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7*)malloc(sizeof(struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7));
    (*(((struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7*)payload_65))) = tuple_109;
    struct HExpr_ variant_65 = (struct HExpr_){.tag = LetFun_1, .LetFun_1 = payload_65};
    match_101 = variant_65;
    goto end_match_406;
next_414:;
    if ((expr_5.tag != TyDecl_)) goto next_415;
    int serial_7 = (*(expr_5.TyDecl_)).t0;
    struct TyDecl_ tyDef_1 = (*(expr_5.TyDecl_)).t1;
    struct IntIntTuple2 a_41 = (*(expr_5.TyDecl_)).t2;
    struct IntIntTuple2 app_63 = g_1.fun(g_1.env, a_41);
    struct IntTyDecl_IntIntTuple2Tuple3 tuple_111;
    tuple_111.t0 = serial_7;
    tuple_111.t1 = tyDef_1;
    tuple_111.t2 = app_63;
    struct IntTyDecl_IntIntTuple2Tuple3* payload_66 = (struct IntTyDecl_IntIntTuple2Tuple3*)malloc(sizeof(struct IntTyDecl_IntIntTuple2Tuple3));
    (*(((struct IntTyDecl_IntIntTuple2Tuple3*)payload_66))) = tuple_111;
    struct HExpr_ variant_66 = (struct HExpr_){.tag = TyDecl_, .TyDecl_ = payload_66};
    match_101 = variant_66;
    goto end_match_406;
next_415:;
    if ((expr_5.tag != Open_2)) goto next_416;
    struct StringList* path_ = (*(expr_5.Open_2)).t0;
    struct IntIntTuple2 a_42 = (*(expr_5.Open_2)).t1;
    struct IntIntTuple2 app_64 = g_1.fun(g_1.env, a_42);
    struct StringListIntIntTuple2Tuple2 tuple_112;
    tuple_112.t0 = path_;
    tuple_112.t1 = app_64;
    struct StringListIntIntTuple2Tuple2* payload_67 = (struct StringListIntIntTuple2Tuple2*)malloc(sizeof(struct StringListIntIntTuple2Tuple2));
    (*(((struct StringListIntIntTuple2Tuple2*)payload_67))) = tuple_112;
    struct HExpr_ variant_67 = (struct HExpr_){.tag = Open_2, .Open_2 = payload_67};
    match_101 = variant_67;
    goto end_match_406;
next_416:;
    if ((expr_5.tag != Error_2)) goto next_417;
    struct String error_ = (*(expr_5.Error_2)).t0;
    struct IntIntTuple2 a_43 = (*(expr_5.Error_2)).t1;
    struct IntIntTuple2 app_65 = g_1.fun(g_1.env, a_43);
    struct StringIntIntTuple2Tuple2 tuple_113;
    tuple_113.t0 = error_;
    tuple_113.t1 = app_65;
    struct StringIntIntTuple2Tuple2* payload_68 = (struct StringIntIntTuple2Tuple2*)malloc(sizeof(struct StringIntIntTuple2Tuple2));
    (*(((struct StringIntIntTuple2Tuple2*)payload_68))) = tuple_113;
    struct HExpr_ variant_68 = (struct HExpr_){.tag = Error_2, .Error_2 = payload_68};
    match_101 = variant_68;
    goto end_match_406;
next_417:;
    exit(1);
end_match_406:;
    return match_101;
}

struct HExpr_ exprMap_(struct Ty_Ty_Fun1 f_8, struct IntIntTuple2IntIntTuple2Fun1 g_1, struct HExpr_ expr_4) {
    struct HExpr_ call_295 = go_26(g_1, f_8, expr_4);
    return call_295;
}

struct Ty_ exprToTy_(struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct HExpr_ expr_6) {
    struct Ty_IntIntTuple2Tuple2 call_296 = exprExtract_(tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, expr_6);
    struct Ty_ ty_42 = call_296.t0;
    return ty_42;
}

struct IntIntTuple2 go_(int r_, struct String text_, int y_1, int x_2, int i_) {
    struct IntIntTuple2 match_102;
    if ((i_ != r_)) goto next_419;
    struct IntIntTuple2 tuple_114;
    tuple_114.t0 = y_1;
    tuple_114.t1 = x_2;
    match_102 = tuple_114;
    goto end_match_418;
next_419:;
    if ((i_ == r_)) goto next_420;
    struct IntIntTuple2 match_103;
    if ((text_.str[i_] != '\n')) goto next_422;
    struct IntIntTuple2 call_297 = go_(r_, text_, (y_1 + 1), 0, (i_ + 1));
    match_103 = call_297;
    goto end_match_421;
next_422:;
    if ((text_.str[i_] == '\n')) goto next_423;
    struct IntIntTuple2 call_298 = go_(r_, text_, y_1, (x_2 + 1), (i_ + 1));
    match_103 = call_298;
    goto end_match_421;
next_423:;
    exit(1);
end_match_421:;
    match_102 = match_103;
    goto end_match_418;
next_420:;
    exit(1);
end_match_418:;
    return match_102;
}

struct IntIntTuple2 locShift_(struct String text_, int l_, int r_, struct IntIntTuple2 arg_105) {
    int y_ = arg_105.t0;
    int x_1 = arg_105.t1;
    int match_104;
    int match_105;
    if ((l_ < 0)) goto next_426;
    match_105 = (r_ >= l_);
    goto end_match_425;
next_426:;
    if ((l_ >= 0)) goto next_427;
    match_105 = 0;
    goto end_match_425;
next_427:;
    exit(1);
end_match_425:;
    if ((!(match_105))) goto next_428;
    match_104 = (text_.len >= r_);
    goto end_match_424;
next_428:;
    if (match_105) goto next_429;
    match_104 = 0;
    goto end_match_424;
next_429:;
    exit(1);
end_match_424:;
    milone_assert(match_104, 40, 2);
    int call_299 = 0;
    struct IntIntTuple2 call_300 = go_(r_, text_, y_, x_1, l_);
    return call_300;
}

int charIsIdent_(char c_) {
    int match_106;
    int match_107;
    if ((c_ != '_')) goto next_432;
    match_107 = 1;
    goto end_match_431;
next_432:;
    if ((c_ == '_')) goto next_433;
    int call_301 = charIsDigit_(c_);
    match_107 = call_301;
    goto end_match_431;
next_433:;
    exit(1);
end_match_431:;
    if ((!(match_107))) goto next_434;
    match_106 = 1;
    goto end_match_430;
next_434:;
    if (match_107) goto next_435;
    int call_302 = charIsAlpha_(c_);
    match_106 = call_302;
    goto end_match_430;
next_435:;
    exit(1);
end_match_430:;
    return match_106;
}

int charIsOp_(char c_1) {
    int match_108;
    int match_109;
    int match_110;
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
    if ((c_1 != '+')) goto next_450;
    match_121 = 1;
    goto end_match_449;
next_450:;
    if ((c_1 == '+')) goto next_451;
    match_121 = (c_1 == '-');
    goto end_match_449;
next_451:;
    exit(1);
end_match_449:;
    if ((!(match_121))) goto next_452;
    match_120 = 1;
    goto end_match_448;
next_452:;
    if (match_121) goto next_453;
    match_120 = (c_1 == '*');
    goto end_match_448;
next_453:;
    exit(1);
end_match_448:;
    if ((!(match_120))) goto next_454;
    match_119 = 1;
    goto end_match_447;
next_454:;
    if (match_120) goto next_455;
    match_119 = (c_1 == '/');
    goto end_match_447;
next_455:;
    exit(1);
end_match_447:;
    if ((!(match_119))) goto next_456;
    match_118 = 1;
    goto end_match_446;
next_456:;
    if (match_119) goto next_457;
    match_118 = (c_1 == '%');
    goto end_match_446;
next_457:;
    exit(1);
end_match_446:;
    if ((!(match_118))) goto next_458;
    match_117 = 1;
    goto end_match_445;
next_458:;
    if (match_118) goto next_459;
    match_117 = (c_1 == '=');
    goto end_match_445;
next_459:;
    exit(1);
end_match_445:;
    if ((!(match_117))) goto next_460;
    match_116 = 1;
    goto end_match_444;
next_460:;
    if (match_117) goto next_461;
    match_116 = (c_1 == '<');
    goto end_match_444;
next_461:;
    exit(1);
end_match_444:;
    if ((!(match_116))) goto next_462;
    match_115 = 1;
    goto end_match_443;
next_462:;
    if (match_116) goto next_463;
    match_115 = (c_1 == '>');
    goto end_match_443;
next_463:;
    exit(1);
end_match_443:;
    if ((!(match_115))) goto next_464;
    match_114 = 1;
    goto end_match_442;
next_464:;
    if (match_115) goto next_465;
    match_114 = (c_1 == '^');
    goto end_match_442;
next_465:;
    exit(1);
end_match_442:;
    if ((!(match_114))) goto next_466;
    match_113 = 1;
    goto end_match_441;
next_466:;
    if (match_114) goto next_467;
    match_113 = (c_1 == '&');
    goto end_match_441;
next_467:;
    exit(1);
end_match_441:;
    if ((!(match_113))) goto next_468;
    match_112 = 1;
    goto end_match_440;
next_468:;
    if (match_113) goto next_469;
    match_112 = (c_1 == '|');
    goto end_match_440;
next_469:;
    exit(1);
end_match_440:;
    if ((!(match_112))) goto next_470;
    match_111 = 1;
    goto end_match_439;
next_470:;
    if (match_112) goto next_471;
    match_111 = (c_1 == ':');
    goto end_match_439;
next_471:;
    exit(1);
end_match_439:;
    if ((!(match_111))) goto next_472;
    match_110 = 1;
    goto end_match_438;
next_472:;
    if (match_111) goto next_473;
    match_110 = (c_1 == '@');
    goto end_match_438;
next_473:;
    exit(1);
end_match_438:;
    if ((!(match_110))) goto next_474;
    match_109 = 1;
    goto end_match_437;
next_474:;
    if (match_110) goto next_475;
    match_109 = (c_1 == ';');
    goto end_match_437;
next_475:;
    exit(1);
end_match_437:;
    if ((!(match_109))) goto next_476;
    match_108 = 1;
    goto end_match_436;
next_476:;
    if (match_109) goto next_477;
    match_108 = (c_1 == '.');
    goto end_match_436;
next_477:;
    exit(1);
end_match_436:;
    return match_108;
}

int charIsPun_(char c_2) {
    int match_122;
    int match_123;
    int match_124;
    int match_125;
    if ((c_2 != ',')) goto next_482;
    match_125 = 1;
    goto end_match_481;
next_482:;
    if ((c_2 == ',')) goto next_483;
    match_125 = (c_2 == '(');
    goto end_match_481;
next_483:;
    exit(1);
end_match_481:;
    if ((!(match_125))) goto next_484;
    match_124 = 1;
    goto end_match_480;
next_484:;
    if (match_125) goto next_485;
    match_124 = (c_2 == ')');
    goto end_match_480;
next_485:;
    exit(1);
end_match_480:;
    if ((!(match_124))) goto next_486;
    match_123 = 1;
    goto end_match_479;
next_486:;
    if (match_124) goto next_487;
    match_123 = (c_2 == '[');
    goto end_match_479;
next_487:;
    exit(1);
end_match_479:;
    if ((!(match_123))) goto next_488;
    match_122 = 1;
    goto end_match_478;
next_488:;
    if (match_123) goto next_489;
    match_122 = (c_2 == ']');
    goto end_match_478;
next_489:;
    exit(1);
end_match_478:;
    return match_122;
}

int go_1(struct String s_, struct String prefix_, int pi_, int si_) {
    int match_126;
    if ((pi_ != prefix_.len)) goto next_491;
    match_126 = 1;
    goto end_match_490;
next_491:;
    if ((pi_ == prefix_.len)) goto next_492;
    int match_127;
    int match_128;
    if ((si_ >= s_.len)) goto next_495;
    match_128 = (prefix_.str[pi_] == s_.str[si_]);
    goto end_match_494;
next_495:;
    if ((si_ < s_.len)) goto next_496;
    match_128 = 0;
    goto end_match_494;
next_496:;
    exit(1);
end_match_494:;
    if ((!(match_128))) goto next_497;
    int call_303 = go_1(s_, prefix_, (pi_ + 1), (si_ + 1));
    match_127 = call_303;
    goto end_match_493;
next_497:;
    if (match_128) goto next_498;
    match_127 = 0;
    goto end_match_493;
next_498:;
    exit(1);
end_match_493:;
    match_126 = match_127;
    goto end_match_490;
next_492:;
    exit(1);
end_match_490:;
    return match_126;
}

int strIsFollowedBy_(int i_1, struct String prefix_, struct String s_) {
    int match_129;
    if ((s_.len < (i_1 + prefix_.len))) goto next_500;
    int call_304 = go_1(s_, prefix_, 0, i_1);
    match_129 = call_304;
    goto end_match_499;
next_500:;
    if ((s_.len >= (i_1 + prefix_.len))) goto next_501;
    match_129 = 0;
    goto end_match_499;
next_501:;
    exit(1);
end_match_499:;
    return match_129;
}

int strIsFollowedByRawQuotes_(int i_2, struct String s_1) {
    int call_305 = strIsFollowedBy_(i_2, (struct String){.str = "\"\"\"", .len = 3}, s_1);
    return call_305;
}

int scanError_(struct String arg_106, int i_3) {
    return (i_3 + 1);
}

int lookEof_(struct String text_1, int i_4) {
    return (i_4 >= text_1.len);
}

int lookSpace_(struct String text_2, int i_5) {
    int call_306 = charIsSpace_(text_2.str[i_5]);
    return call_306;
}

int go_2(struct String text_3, int i_7) {
    int match_130;
    int match_131;
    if ((i_7 >= text_3.len)) goto next_504;
    int call_307 = charIsSpace_(text_3.str[i_7]);
    match_131 = call_307;
    goto end_match_503;
next_504:;
    if ((i_7 < text_3.len)) goto next_505;
    match_131 = 0;
    goto end_match_503;
next_505:;
    exit(1);
end_match_503:;
    if ((!(match_131))) goto next_506;
    int call_308 = go_2(text_3, (i_7 + 1));
    match_130 = call_308;
    goto end_match_502;
next_506:;
    if (match_131) goto next_507;
    match_130 = i_7;
    goto end_match_502;
next_507:;
    exit(1);
end_match_502:;
    return match_130;
}

int scanSpace_(struct String text_3, int i_6) {
    int call_309 = lookSpace_(text_3, i_6);
    milone_assert(call_309, 103, 2);
    int call_310 = 0;
    int call_311 = go_2(text_3, i_6);
    return call_311;
}

int lookComment_(struct String text_4, int i_8) {
    int match_132;
    int call_312 = strIsFollowedBy_(i_8, (struct String){.str = "//", .len = 2}, text_4);
    if ((!(call_312))) goto next_509;
    match_132 = 1;
    goto end_match_508;
next_509:;
    if (call_312) goto next_510;
    int call_313 = strIsFollowedBy_(i_8, (struct String){.str = "[<", .len = 2}, text_4);
    match_132 = call_313;
    goto end_match_508;
next_510:;
    exit(1);
end_match_508:;
    return match_132;
}

int go_3(struct String text_5, int i_10) {
    int match_133;
    if ((i_10 != text_5.len)) goto next_512;
    match_133 = i_10;
    goto end_match_511;
next_512:;
    if ((i_10 == text_5.len)) goto next_513;
    int match_134;
    if ((text_5.str[i_10] != '\n')) goto next_515;
    match_134 = (i_10 + 1);
    goto end_match_514;
next_515:;
    if ((text_5.str[i_10] == '\n')) goto next_516;
    int call_314 = go_3(text_5, (i_10 + 1));
    match_134 = call_314;
    goto end_match_514;
next_516:;
    exit(1);
end_match_514:;
    match_133 = match_134;
    goto end_match_511;
next_513:;
    exit(1);
end_match_511:;
    return match_133;
}

int scanLine_(struct String text_5, int i_9) {
    int call_315 = lookComment_(text_5, i_9);
    milone_assert(call_315, 117, 2);
    int call_316 = 0;
    int call_317 = go_3(text_5, i_9);
    return call_317;
}

int lookPun_(struct String text_6, int i_11) {
    int call_318 = charIsPun_(text_6.str[i_11]);
    return call_318;
}

int scanPun_(struct String text_7, int i_12) {
    int call_319 = lookPun_(text_7, i_12);
    milone_assert(call_319, 131, 2);
    int call_320 = 0;
    return (i_12 + 1);
}

int lookOp_(struct String text_8, int i_13) {
    int call_321 = charIsOp_(text_8.str[i_13]);
    return call_321;
}

int go_4(struct String text_9, int i_15) {
    int match_135;
    int match_136;
    if ((i_15 >= text_9.len)) goto next_519;
    int call_322 = charIsOp_(text_9.str[i_15]);
    match_136 = call_322;
    goto end_match_518;
next_519:;
    if ((i_15 < text_9.len)) goto next_520;
    match_136 = 0;
    goto end_match_518;
next_520:;
    exit(1);
end_match_518:;
    if ((!(match_136))) goto next_521;
    int call_323 = go_4(text_9, (i_15 + 1));
    match_135 = call_323;
    goto end_match_517;
next_521:;
    if (match_136) goto next_522;
    match_135 = i_15;
    goto end_match_517;
next_522:;
    exit(1);
end_match_517:;
    return match_135;
}

int scanOp_(struct String text_9, int i_14) {
    int call_324 = lookOp_(text_9, i_14);
    milone_assert(call_324, 138, 2);
    int call_325 = 0;
    int call_326 = go_4(text_9, i_14);
    return call_326;
}

int lookIdent_(struct String text_10, int i_16) {
    int match_137;
    int call_327 = charIsIdent_(text_10.str[i_16]);
    if ((!(call_327))) goto next_524;
    int call_328 = charIsDigit_(text_10.str[i_16]);
    match_137 = (!(call_328));
    goto end_match_523;
next_524:;
    if (call_327) goto next_525;
    match_137 = 0;
    goto end_match_523;
next_525:;
    exit(1);
end_match_523:;
    return match_137;
}

int go_5(struct String text_11, int i_18) {
    int match_138;
    int match_139;
    if ((i_18 >= text_11.len)) goto next_528;
    int call_329 = charIsIdent_(text_11.str[i_18]);
    match_139 = call_329;
    goto end_match_527;
next_528:;
    if ((i_18 < text_11.len)) goto next_529;
    match_139 = 0;
    goto end_match_527;
next_529:;
    exit(1);
end_match_527:;
    if ((!(match_139))) goto next_530;
    int call_330 = go_5(text_11, (i_18 + 1));
    match_138 = call_330;
    goto end_match_526;
next_530:;
    if (match_139) goto next_531;
    match_138 = i_18;
    goto end_match_526;
next_531:;
    exit(1);
end_match_526:;
    return match_138;
}

int scanIdent_(struct String text_11, int i_17) {
    int call_331 = lookIdent_(text_11, i_17);
    milone_assert(call_331, 151, 2);
    int call_332 = 0;
    int call_333 = go_5(text_11, i_17);
    return call_333;
}

int lookIntLit_(struct String text_12, int i_19) {
    int call_334 = charIsDigit_(text_12.str[i_19]);
    return call_334;
}

int go_6(struct String text_13, int i_21) {
    int match_140;
    int match_141;
    if ((i_21 >= text_13.len)) goto next_534;
    int call_335 = charIsDigit_(text_13.str[i_21]);
    match_141 = call_335;
    goto end_match_533;
next_534:;
    if ((i_21 < text_13.len)) goto next_535;
    match_141 = 0;
    goto end_match_533;
next_535:;
    exit(1);
end_match_533:;
    if ((!(match_141))) goto next_536;
    int call_336 = go_6(text_13, (i_21 + 1));
    match_140 = call_336;
    goto end_match_532;
next_536:;
    if (match_141) goto next_537;
    match_140 = i_21;
    goto end_match_532;
next_537:;
    exit(1);
end_match_532:;
    return match_140;
}

int scanIntLit_(struct String text_13, int i_20) {
    int call_337 = lookIntLit_(text_13, i_20);
    milone_assert(call_337, 163, 2);
    int call_338 = 0;
    int call_339 = go_6(text_13, i_20);
    return call_339;
}

int lookCharLit_(struct String text_14, int i_22) {
    return (text_14.str[i_22] == '\'');
}

struct BoolIntTuple2 {
    int t0;
    int t1;
};

struct BoolIntTuple2 go_7(struct String text_15, int i_24) {
    struct BoolIntTuple2 match_142;
    int match_143;
    if (((i_24 + 1) >= text_15.len)) goto next_540;
    match_143 = (text_15.str[i_24] == '\\');
    goto end_match_539;
next_540:;
    if (((i_24 + 1) < text_15.len)) goto next_541;
    match_143 = 0;
    goto end_match_539;
next_541:;
    exit(1);
end_match_539:;
    if ((!(match_143))) goto next_542;
    struct BoolIntTuple2 call_340 = go_7(text_15, (i_24 + 2));
    match_142 = call_340;
    goto end_match_538;
next_542:;
    if (match_143) goto next_543;
    struct BoolIntTuple2 match_144;
    int match_145;
    if ((i_24 >= text_15.len)) goto next_546;
    match_145 = (text_15.str[i_24] == '\'');
    goto end_match_545;
next_546:;
    if ((i_24 < text_15.len)) goto next_547;
    match_145 = 0;
    goto end_match_545;
next_547:;
    exit(1);
end_match_545:;
    if ((!(match_145))) goto next_548;
    struct BoolIntTuple2 tuple_115;
    tuple_115.t0 = 1;
    tuple_115.t1 = (i_24 + 1);
    match_144 = tuple_115;
    goto end_match_544;
next_548:;
    if (match_145) goto next_549;
    struct BoolIntTuple2 match_146;
    int match_147;
    if ((i_24 >= text_15.len)) goto next_552;
    match_147 = (text_15.str[i_24] != '\n');
    goto end_match_551;
next_552:;
    if ((i_24 < text_15.len)) goto next_553;
    match_147 = 0;
    goto end_match_551;
next_553:;
    exit(1);
end_match_551:;
    if ((!(match_147))) goto next_554;
    struct BoolIntTuple2 call_341 = go_7(text_15, (i_24 + 1));
    match_146 = call_341;
    goto end_match_550;
next_554:;
    if (match_147) goto next_555;
    int match_148;
    if ((i_24 != text_15.len)) goto next_557;
    match_148 = 1;
    goto end_match_556;
next_557:;
    if ((i_24 == text_15.len)) goto next_558;
    match_148 = (text_15.str[i_24] == '\n');
    goto end_match_556;
next_558:;
    exit(1);
end_match_556:;
    milone_assert(match_148, 188, 6);
    int call_342 = 0;
    struct BoolIntTuple2 tuple_116;
    tuple_116.t0 = 0;
    tuple_116.t1 = i_24;
    match_146 = tuple_116;
    goto end_match_550;
next_555:;
    exit(1);
end_match_550:;
    match_144 = match_146;
    goto end_match_544;
next_549:;
    exit(1);
end_match_544:;
    match_142 = match_144;
    goto end_match_538;
next_543:;
    exit(1);
end_match_538:;
    return match_142;
}

struct BoolIntTuple2 scanCharLit_(struct String text_15, int i_23) {
    int call_343 = lookCharLit_(text_15, i_23);
    milone_assert(call_343, 175, 2);
    int call_344 = 0;
    struct BoolIntTuple2 call_345 = go_7(text_15, (i_23 + 1));
    return call_345;
}

int lookStrLit_(struct String text_16, int i_25) {
    return (text_16.str[i_25] == '\"');
}

struct BoolIntTuple2 go_8(struct String text_17, int i_27) {
    struct BoolIntTuple2 match_149;
    int match_150;
    if (((i_27 + 1) >= text_17.len)) goto next_561;
    match_150 = (text_17.str[i_27] == '\\');
    goto end_match_560;
next_561:;
    if (((i_27 + 1) < text_17.len)) goto next_562;
    match_150 = 0;
    goto end_match_560;
next_562:;
    exit(1);
end_match_560:;
    if ((!(match_150))) goto next_563;
    struct BoolIntTuple2 call_346 = go_8(text_17, (i_27 + 2));
    match_149 = call_346;
    goto end_match_559;
next_563:;
    if (match_150) goto next_564;
    struct BoolIntTuple2 match_151;
    int match_152;
    if ((i_27 >= text_17.len)) goto next_567;
    match_152 = (text_17.str[i_27] == '\"');
    goto end_match_566;
next_567:;
    if ((i_27 < text_17.len)) goto next_568;
    match_152 = 0;
    goto end_match_566;
next_568:;
    exit(1);
end_match_566:;
    if ((!(match_152))) goto next_569;
    struct BoolIntTuple2 tuple_117;
    tuple_117.t0 = 1;
    tuple_117.t1 = (i_27 + 1);
    match_151 = tuple_117;
    goto end_match_565;
next_569:;
    if (match_152) goto next_570;
    struct BoolIntTuple2 match_153;
    int match_154;
    if ((i_27 >= text_17.len)) goto next_573;
    match_154 = (text_17.str[i_27] != '\n');
    goto end_match_572;
next_573:;
    if ((i_27 < text_17.len)) goto next_574;
    match_154 = 0;
    goto end_match_572;
next_574:;
    exit(1);
end_match_572:;
    if ((!(match_154))) goto next_575;
    struct BoolIntTuple2 call_347 = go_8(text_17, (i_27 + 1));
    match_153 = call_347;
    goto end_match_571;
next_575:;
    if (match_154) goto next_576;
    int match_155;
    if ((i_27 != text_17.len)) goto next_578;
    match_155 = 1;
    goto end_match_577;
next_578:;
    if ((i_27 == text_17.len)) goto next_579;
    match_155 = (text_17.str[i_27] == '\n');
    goto end_match_577;
next_579:;
    exit(1);
end_match_577:;
    milone_assert(match_155, 209, 6);
    int call_348 = 0;
    struct BoolIntTuple2 tuple_118;
    tuple_118.t0 = 0;
    tuple_118.t1 = i_27;
    match_153 = tuple_118;
    goto end_match_571;
next_576:;
    exit(1);
end_match_571:;
    match_151 = match_153;
    goto end_match_565;
next_570:;
    exit(1);
end_match_565:;
    match_149 = match_151;
    goto end_match_559;
next_564:;
    exit(1);
end_match_559:;
    return match_149;
}

struct BoolIntTuple2 scanStrLit_(struct String text_17, int i_26) {
    int call_349 = lookStrLit_(text_17, i_26);
    milone_assert(call_349, 196, 2);
    int call_350 = 0;
    struct BoolIntTuple2 call_351 = go_8(text_17, (i_26 + 1));
    return call_351;
}

int lookStrLitRaw_(struct String text_18, int i_28) {
    int call_352 = strIsFollowedByRawQuotes_(i_28, text_18);
    return call_352;
}

struct BoolIntTuple2 go_9(struct String text_19, int i_30) {
    struct BoolIntTuple2 match_156;
    int call_353 = strIsFollowedByRawQuotes_(i_30, text_19);
    if ((!(call_353))) goto next_581;
    struct BoolIntTuple2 tuple_119;
    tuple_119.t0 = 1;
    tuple_119.t1 = (i_30 + 3);
    match_156 = tuple_119;
    goto end_match_580;
next_581:;
    if (call_353) goto next_582;
    struct BoolIntTuple2 match_157;
    if (((i_30 + 1) >= text_19.len)) goto next_584;
    struct BoolIntTuple2 call_354 = go_9(text_19, (i_30 + 1));
    match_157 = call_354;
    goto end_match_583;
next_584:;
    if (((i_30 + 1) < text_19.len)) goto next_585;
    milone_assert((i_30 == text_19.len), 224, 6);
    int call_355 = 0;
    struct BoolIntTuple2 tuple_120;
    tuple_120.t0 = 0;
    tuple_120.t1 = i_30;
    match_157 = tuple_120;
    goto end_match_583;
next_585:;
    exit(1);
end_match_583:;
    match_156 = match_157;
    goto end_match_580;
next_582:;
    exit(1);
end_match_580:;
    return match_156;
}

struct BoolIntTuple2 scanStrLitRaw_(struct String text_19, int i_29) {
    int call_356 = lookStrLitRaw_(text_19, i_29);
    milone_assert(call_356, 217, 2);
    int call_357 = 0;
    struct BoolIntTuple2 call_358 = go_9(text_19, (i_29 + 3));
    return call_358;
}

struct Token_ tokenFromIdent_(struct String text_20, int l_1, int r_1) {
    struct Token_ match_158;
    struct String call_359 = strSlice_(l_1, r_1, text_20);
    if ((str_cmp(call_359, (struct String){.str = "true", .len = 4}) != 0)) goto next_587;
    int* payload_69 = (int*)malloc(sizeof(int));
    (*(((int*)payload_69))) = 1;
    struct Token_ variant_69 = (struct Token_){.tag = Bool_1, .Bool_1 = payload_69};
    match_158 = variant_69;
    goto end_match_586;
next_587:;
    if ((str_cmp(call_359, (struct String){.str = "false", .len = 5}) != 0)) goto next_588;
    int* payload_70 = (int*)malloc(sizeof(int));
    (*(((int*)payload_70))) = 0;
    struct Token_ variant_70 = (struct Token_){.tag = Bool_1, .Bool_1 = payload_70};
    match_158 = variant_70;
    goto end_match_586;
next_588:;
    if ((str_cmp(call_359, (struct String){.str = "do", .len = 2}) != 0)) goto next_589;
    match_158 = (struct Token_){.tag = Do_};
    goto end_match_586;
next_589:;
    if ((str_cmp(call_359, (struct String){.str = "let", .len = 3}) != 0)) goto next_590;
    match_158 = (struct Token_){.tag = Let_};
    goto end_match_586;
next_590:;
    if ((str_cmp(call_359, (struct String){.str = "if", .len = 2}) != 0)) goto next_591;
    match_158 = (struct Token_){.tag = If_};
    goto end_match_586;
next_591:;
    if ((str_cmp(call_359, (struct String){.str = "then", .len = 4}) != 0)) goto next_592;
    match_158 = (struct Token_){.tag = Then_};
    goto end_match_586;
next_592:;
    if ((str_cmp(call_359, (struct String){.str = "else", .len = 4}) != 0)) goto next_593;
    match_158 = (struct Token_){.tag = Else_};
    goto end_match_586;
next_593:;
    if ((str_cmp(call_359, (struct String){.str = "match", .len = 5}) != 0)) goto next_594;
    match_158 = (struct Token_){.tag = Match_};
    goto end_match_586;
next_594:;
    if ((str_cmp(call_359, (struct String){.str = "with", .len = 4}) != 0)) goto next_595;
    match_158 = (struct Token_){.tag = With_};
    goto end_match_586;
next_595:;
    if ((str_cmp(call_359, (struct String){.str = "as", .len = 2}) != 0)) goto next_596;
    match_158 = (struct Token_){.tag = As_};
    goto end_match_586;
next_596:;
    if ((str_cmp(call_359, (struct String){.str = "when", .len = 4}) != 0)) goto next_597;
    match_158 = (struct Token_){.tag = When_};
    goto end_match_586;
next_597:;
    if ((str_cmp(call_359, (struct String){.str = "rec", .len = 3}) != 0)) goto next_598;
    match_158 = (struct Token_){.tag = Rec_};
    goto end_match_586;
next_598:;
    if ((str_cmp(call_359, (struct String){.str = "private", .len = 7}) != 0)) goto next_599;
    match_158 = (struct Token_){.tag = Private_};
    goto end_match_586;
next_599:;
    if ((str_cmp(call_359, (struct String){.str = "internal", .len = 8}) != 0)) goto next_600;
    match_158 = (struct Token_){.tag = Internal_};
    goto end_match_586;
next_600:;
    if ((str_cmp(call_359, (struct String){.str = "public", .len = 6}) != 0)) goto next_601;
    match_158 = (struct Token_){.tag = Public_};
    goto end_match_586;
next_601:;
    if ((str_cmp(call_359, (struct String){.str = "module", .len = 6}) != 0)) goto next_602;
    match_158 = (struct Token_){.tag = Module_};
    goto end_match_586;
next_602:;
    if ((str_cmp(call_359, (struct String){.str = "namespace", .len = 9}) != 0)) goto next_603;
    match_158 = (struct Token_){.tag = Namespace_};
    goto end_match_586;
next_603:;
    if ((str_cmp(call_359, (struct String){.str = "open", .len = 4}) != 0)) goto next_604;
    match_158 = (struct Token_){.tag = Open_};
    goto end_match_586;
next_604:;
    if ((str_cmp(call_359, (struct String){.str = "type", .len = 4}) != 0)) goto next_605;
    match_158 = (struct Token_){.tag = Type_};
    goto end_match_586;
next_605:;
    if ((str_cmp(call_359, (struct String){.str = "of", .len = 2}) != 0)) goto next_606;
    match_158 = (struct Token_){.tag = Of_};
    goto end_match_586;
next_606:;
    if ((str_cmp(call_359, (struct String){.str = "fun", .len = 3}) != 0)) goto next_607;
    match_158 = (struct Token_){.tag = Fun_};
    goto end_match_586;
next_607:;
    if ((str_cmp(call_359, (struct String){.str = "in", .len = 2}) != 0)) goto next_608;
    match_158 = (struct Token_){.tag = In_};
    goto end_match_586;
next_608:;
    struct String s_2 = call_359;
    struct String* payload_71 = (struct String*)malloc(sizeof(struct String));
    (*(((struct String*)payload_71))) = s_2;
    struct Token_ variant_71 = (struct Token_){.tag = Ident_, .Ident_ = payload_71};
    match_158 = variant_71;
    goto end_match_586;
next_609:;
end_match_586:;
    return match_158;
}

struct Token_ tokenFromOp_(struct String text_21, int l_2, int r_2) {
    struct Token_ match_159;
    struct String call_360 = strSlice_(l_2, r_2, text_21);
    if ((str_cmp(call_360, (struct String){.str = "&", .len = 1}) != 0)) goto next_611;
    match_159 = (struct Token_){.tag = Amp_};
    goto end_match_610;
next_611:;
    if ((str_cmp(call_360, (struct String){.str = "&&", .len = 2}) != 0)) goto next_612;
    match_159 = (struct Token_){.tag = AmpAmp_};
    goto end_match_610;
next_612:;
    if ((str_cmp(call_360, (struct String){.str = "->", .len = 2}) != 0)) goto next_613;
    match_159 = (struct Token_){.tag = Arrow_};
    goto end_match_610;
next_613:;
    if ((str_cmp(call_360, (struct String){.str = ":", .len = 1}) != 0)) goto next_614;
    match_159 = (struct Token_){.tag = Colon_};
    goto end_match_610;
next_614:;
    if ((str_cmp(call_360, (struct String){.str = "::", .len = 2}) != 0)) goto next_615;
    match_159 = (struct Token_){.tag = ColonColon_};
    goto end_match_610;
next_615:;
    if ((str_cmp(call_360, (struct String){.str = ".", .len = 1}) != 0)) goto next_616;
    match_159 = (struct Token_){.tag = Dot_};
    goto end_match_610;
next_616:;
    if ((str_cmp(call_360, (struct String){.str = "..", .len = 2}) != 0)) goto next_617;
    match_159 = (struct Token_){.tag = DotDot_};
    goto end_match_610;
next_617:;
    if ((str_cmp(call_360, (struct String){.str = "=", .len = 1}) != 0)) goto next_618;
    match_159 = (struct Token_){.tag = Eq_};
    goto end_match_610;
next_618:;
    if ((str_cmp(call_360, (struct String){.str = ">", .len = 1}) != 0)) goto next_619;
    match_159 = (struct Token_){.tag = Gt_};
    goto end_match_610;
next_619:;
    if ((str_cmp(call_360, (struct String){.str = ">=", .len = 2}) != 0)) goto next_620;
    match_159 = (struct Token_){.tag = GtEq_};
    goto end_match_610;
next_620:;
    if ((str_cmp(call_360, (struct String){.str = "<", .len = 1}) != 0)) goto next_621;
    match_159 = (struct Token_){.tag = Lt_};
    goto end_match_610;
next_621:;
    if ((str_cmp(call_360, (struct String){.str = "<=", .len = 2}) != 0)) goto next_622;
    match_159 = (struct Token_){.tag = LtEq_};
    goto end_match_610;
next_622:;
    if ((str_cmp(call_360, (struct String){.str = "<>", .len = 2}) != 0)) goto next_623;
    match_159 = (struct Token_){.tag = LtGt_};
    goto end_match_610;
next_623:;
    if ((str_cmp(call_360, (struct String){.str = "-", .len = 1}) != 0)) goto next_624;
    match_159 = (struct Token_){.tag = Minus_};
    goto end_match_610;
next_624:;
    if ((str_cmp(call_360, (struct String){.str = "%", .len = 1}) != 0)) goto next_625;
    match_159 = (struct Token_){.tag = Percent_};
    goto end_match_610;
next_625:;
    if ((str_cmp(call_360, (struct String){.str = "|", .len = 1}) != 0)) goto next_626;
    match_159 = (struct Token_){.tag = Pipe_};
    goto end_match_610;
next_626:;
    if ((str_cmp(call_360, (struct String){.str = "|>", .len = 2}) != 0)) goto next_627;
    match_159 = (struct Token_){.tag = PipeGt_};
    goto end_match_610;
next_627:;
    if ((str_cmp(call_360, (struct String){.str = "||", .len = 2}) != 0)) goto next_628;
    match_159 = (struct Token_){.tag = PipePipe_};
    goto end_match_610;
next_628:;
    if ((str_cmp(call_360, (struct String){.str = "+", .len = 1}) != 0)) goto next_629;
    match_159 = (struct Token_){.tag = Plus_};
    goto end_match_610;
next_629:;
    if ((str_cmp(call_360, (struct String){.str = ";", .len = 1}) != 0)) goto next_630;
    match_159 = (struct Token_){.tag = Semi_};
    goto end_match_610;
next_630:;
    if ((str_cmp(call_360, (struct String){.str = "*", .len = 1}) != 0)) goto next_631;
    match_159 = (struct Token_){.tag = Star_};
    goto end_match_610;
next_631:;
    if ((str_cmp(call_360, (struct String){.str = "/", .len = 1}) != 0)) goto next_632;
    match_159 = (struct Token_){.tag = Slash_};
    goto end_match_610;
next_632:;
    match_159 = (struct Token_){.tag = Error_};
    goto end_match_610;
next_633:;
end_match_610:;
    return match_159;
}

struct Token_ tokenFromPun_(struct String text_22, int l_3, int r_3) {
    milone_assert(((r_3 - l_3) == 1), 331, 2);
    int call_361 = 0;
    struct Token_ match_160;
    if ((text_22.str[l_3] != ',')) goto next_635;
    match_160 = (struct Token_){.tag = Comma_};
    goto end_match_634;
next_635:;
    if ((text_22.str[l_3] != '(')) goto next_636;
    match_160 = (struct Token_){.tag = ParenL_};
    goto end_match_634;
next_636:;
    if ((text_22.str[l_3] != ')')) goto next_637;
    match_160 = (struct Token_){.tag = ParenR_};
    goto end_match_634;
next_637:;
    if ((text_22.str[l_3] != '[')) goto next_638;
    match_160 = (struct Token_){.tag = BracketL_};
    goto end_match_634;
next_638:;
    if ((text_22.str[l_3] != ']')) goto next_639;
    match_160 = (struct Token_){.tag = BracketR_};
    goto end_match_634;
next_639:;
    struct Token_ call_362 = failwith_1((struct String){.str = "NEVER! charIsPun is broken", .len = 26});
    match_160 = call_362;
    goto end_match_634;
next_640:;
end_match_634:;
    return match_160;
}

struct Token_ tokenFromIntLit_(struct String text_23, int l_4, int r_4) {
    struct String call_363 = strSlice_(l_4, r_4, text_23);
    int call_364 = str_to_int(call_363);
    int value_ = call_364;
    int* payload_72 = (int*)malloc(sizeof(int));
    (*(((int*)payload_72))) = value_;
    struct Token_ variant_72 = (struct Token_){.tag = Int_1, .Int_1 = payload_72};
    return variant_72;
}

struct Token_ tokenFromCharLit_(char charNull_, struct String text_24, int l_5, int r_5) {
    int match_161;
    int match_162;
    if ((r_5 < (l_5 + 2))) goto next_643;
    match_162 = (text_24.str[l_5] == '\'');
    goto end_match_642;
next_643:;
    if ((r_5 >= (l_5 + 2))) goto next_644;
    match_162 = 0;
    goto end_match_642;
next_644:;
    exit(1);
end_match_642:;
    if ((!(match_162))) goto next_645;
    match_161 = (text_24.str[(r_5 - 1)] == '\'');
    goto end_match_641;
next_645:;
    if (match_162) goto next_646;
    match_161 = 0;
    goto end_match_641;
next_646:;
    exit(1);
end_match_641:;
    milone_assert(match_161, 351, 2);
    int call_365 = 0;
    int i_31 = (l_5 + 1);
    char match_163;
    if ((text_24.str[i_31] != '\\')) goto next_648;
    char match_164;
    if ((text_24.str[(i_31 + 1)] != 'x')) goto next_651;
    match_164 = charNull_;
    goto end_match_650;
next_651:;
    if ((text_24.str[(i_31 + 1)] != 't')) goto next_652;
    match_164 = '\t';
    goto end_match_650;
next_652:;
    if ((text_24.str[(i_31 + 1)] != 'r')) goto next_653;
    match_164 = '\r';
    goto end_match_650;
next_653:;
    if ((text_24.str[(i_31 + 1)] != 'n')) goto next_654;
    match_164 = '\n';
    goto end_match_650;
next_654:;
    char c_3 = text_24.str[(i_31 + 1)];
    match_164 = c_3;
    goto end_match_650;
next_655:;
end_match_650:;
    match_163 = match_164;
    goto end_match_647;
next_648:;
    char c_4 = text_24.str[i_31];
    match_163 = c_4;
    goto end_match_647;
next_649:;
end_match_647:;
    char value_1 = match_163;
    char* payload_73 = (char*)malloc(sizeof(char));
    (*(((char*)payload_73))) = value_1;
    struct Token_ variant_73 = (struct Token_){.tag = Char_1, .Char_1 = payload_73};
    return variant_73;
}

int next_(int r_6, struct String text_25, int i_33) {
    int match_165;
    int match_166;
    if ((i_33 != (r_6 - 1))) goto next_658;
    match_166 = 1;
    goto end_match_657;
next_658:;
    if ((i_33 == (r_6 - 1))) goto next_659;
    match_166 = (text_25.str[i_33] == '\\');
    goto end_match_657;
next_659:;
    exit(1);
end_match_657:;
    if ((!(match_166))) goto next_660;
    match_165 = i_33;
    goto end_match_656;
next_660:;
    if (match_166) goto next_661;
    int call_366 = next_(r_6, text_25, (i_33 + 1));
    match_165 = call_366;
    goto end_match_656;
next_661:;
    exit(1);
end_match_656:;
    return match_165;
}

struct String go_10(int r_6, struct String text_25, struct StringList* acc_, int i_32) {
    int call_367 = next_(r_6, text_25, i_32);
    int endIndex_ = call_367;
    struct String call_368 = strSlice_(i_32, endIndex_, text_25);
    struct StringList* list_53 = (struct StringList*)malloc(sizeof(struct StringList));
    list_53->head = call_368;
    list_53->tail = acc_;
    struct StringList* acc_1 = list_53;
    int i_34 = endIndex_;
    struct String match_167;
    if ((i_34 != (r_6 - 1))) goto next_663;
    struct StringList* call_369 = listRev_2(acc_1);
    struct String call_370 = strConcat_(call_369);
    match_167 = call_370;
    goto end_match_662;
next_663:;
    if ((i_34 == (r_6 - 1))) goto next_664;
    milone_assert((text_25.str[i_34] == '\\'), 394, 6);
    int call_371 = 0;
    struct String match_168;
    if ((text_25.str[(i_34 + 1)] != 'x')) goto next_666;
    struct StringList* list_54 = (struct StringList*)malloc(sizeof(struct StringList));
    list_54->head = (struct String){.str = "\0", .len = 1};
    list_54->tail = acc_1;
    struct String call_372 = go_10(r_6, text_25, list_54, (i_34 + 4));
    match_168 = call_372;
    goto end_match_665;
next_666:;
    if ((text_25.str[(i_34 + 1)] != 't')) goto next_667;
    struct StringList* list_55 = (struct StringList*)malloc(sizeof(struct StringList));
    list_55->head = (struct String){.str = "\t", .len = 1};
    list_55->tail = acc_1;
    struct String call_373 = go_10(r_6, text_25, list_55, (i_34 + 2));
    match_168 = call_373;
    goto end_match_665;
next_667:;
    if ((text_25.str[(i_34 + 1)] != 'r')) goto next_668;
    struct StringList* list_56 = (struct StringList*)malloc(sizeof(struct StringList));
    list_56->head = (struct String){.str = "\r", .len = 1};
    list_56->tail = acc_1;
    struct String call_374 = go_10(r_6, text_25, list_56, (i_34 + 2));
    match_168 = call_374;
    goto end_match_665;
next_668:;
    if ((text_25.str[(i_34 + 1)] != 'n')) goto next_669;
    struct StringList* list_57 = (struct StringList*)malloc(sizeof(struct StringList));
    list_57->head = (struct String){.str = "\n", .len = 1};
    list_57->tail = acc_1;
    struct String call_375 = go_10(r_6, text_25, list_57, (i_34 + 2));
    match_168 = call_375;
    goto end_match_665;
next_669:;
    struct String call_376 = strSlice_((i_34 + 1), (i_34 + 2), text_25);
    struct StringList* list_58 = (struct StringList*)malloc(sizeof(struct StringList));
    list_58->head = call_376;
    list_58->tail = acc_1;
    struct String call_377 = go_10(r_6, text_25, list_58, (i_34 + 2));
    match_168 = call_377;
    goto end_match_665;
next_670:;
end_match_665:;
    match_167 = match_168;
    goto end_match_662;
next_664:;
    exit(1);
end_match_662:;
    return match_167;
}

struct Token_ tokenFromStrLit_(struct String text_25, int l_6, int r_6) {
    int match_169;
    int match_170;
    if ((r_6 < (l_6 + 2))) goto next_673;
    match_170 = (text_25.str[l_6] == '\"');
    goto end_match_672;
next_673:;
    if ((r_6 >= (l_6 + 2))) goto next_674;
    match_170 = 0;
    goto end_match_672;
next_674:;
    exit(1);
end_match_672:;
    if ((!(match_170))) goto next_675;
    match_169 = (text_25.str[(r_6 - 1)] == '\"');
    goto end_match_671;
next_675:;
    if (match_170) goto next_676;
    match_169 = 0;
    goto end_match_671;
next_676:;
    exit(1);
end_match_671:;
    milone_assert(match_169, 375, 2);
    int call_378 = 0;
    struct String call_379 = go_10(r_6, text_25, NULL, (l_6 + 1));
    struct String value_2 = call_379;
    struct String* payload_74 = (struct String*)malloc(sizeof(struct String));
    (*(((struct String*)payload_74))) = value_2;
    struct Token_ variant_74 = (struct Token_){.tag = Str_1, .Str_1 = payload_74};
    return variant_74;
}

struct Token_ tokenFromStrLitRaw_(struct String text_26, int l_7, int r_7) {
    int match_171;
    int match_172;
    if ((r_7 < (l_7 + 6))) goto next_679;
    int call_380 = strIsFollowedByRawQuotes_(l_7, text_26);
    match_172 = call_380;
    goto end_match_678;
next_679:;
    if ((r_7 >= (l_7 + 6))) goto next_680;
    match_172 = 0;
    goto end_match_678;
next_680:;
    exit(1);
end_match_678:;
    if ((!(match_172))) goto next_681;
    int call_381 = strIsFollowedByRawQuotes_((r_7 - 3), text_26);
    match_171 = call_381;
    goto end_match_677;
next_681:;
    if (match_172) goto next_682;
    match_171 = 0;
    goto end_match_677;
next_682:;
    exit(1);
end_match_677:;
    milone_assert(match_171, 411, 2);
    int call_382 = 0;
    struct String call_383 = strSlice_((l_7 + 3), (r_7 - 3), text_26);
    struct String* payload_75 = (struct String*)malloc(sizeof(struct String));
    (*(((struct String*)payload_75))) = call_383;
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

struct StringIntTuple2 tokCtxToTextIndex_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 arg_107) {
    struct String text_27 = arg_107.t0;
    int i_35 = arg_107.t1;
    struct StringIntTuple2 tuple_121;
    tuple_121.t0 = text_27;
    tuple_121.t1 = i_35;
    return tuple_121;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokCtxSkip_(int r_8, struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 arg_108) {
    struct String text_28 = arg_108.t0;
    int i_36 = arg_108.t1;
    struct IntIntTuple2 loc_ = arg_108.t2;
    struct Token_IntIntTuple2Tuple2List* acc_2 = arg_108.t3;
    int match_173;
    int match_174;
    if ((i_36 < 0)) goto next_685;
    match_174 = (r_8 >= i_36);
    goto end_match_684;
next_685:;
    if ((i_36 >= 0)) goto next_686;
    match_174 = 0;
    goto end_match_684;
next_686:;
    exit(1);
end_match_684:;
    if ((!(match_174))) goto next_687;
    match_173 = (text_28.len >= r_8);
    goto end_match_683;
next_687:;
    if (match_174) goto next_688;
    match_173 = 0;
    goto end_match_683;
next_688:;
    exit(1);
end_match_683:;
    milone_assert(match_173, 424, 2);
    int call_384 = 0;
    struct IntIntTuple2 call_385 = locShift_(text_28, i_36, r_8, loc_);
    struct IntIntTuple2 newLoc_ = call_385;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tuple_122;
    tuple_122.t0 = text_28;
    tuple_122.t1 = r_8;
    tuple_122.t2 = newLoc_;
    tuple_122.t3 = acc_2;
    return tuple_122;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokCtxPush_(struct Token_ kind_, int r_9, struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 arg_109) {
    struct String text_29 = arg_109.t0;
    int i_37 = arg_109.t1;
    struct IntIntTuple2 loc_1 = arg_109.t2;
    struct Token_IntIntTuple2Tuple2List* acc_3 = arg_109.t3;
    int match_175;
    int match_176;
    if ((i_37 < 0)) goto next_691;
    match_176 = (r_9 >= i_37);
    goto end_match_690;
next_691:;
    if ((i_37 >= 0)) goto next_692;
    match_176 = 0;
    goto end_match_690;
next_692:;
    exit(1);
end_match_690:;
    if ((!(match_176))) goto next_693;
    match_175 = (text_29.len >= r_9);
    goto end_match_689;
next_693:;
    if (match_176) goto next_694;
    match_175 = 0;
    goto end_match_689;
next_694:;
    exit(1);
end_match_689:;
    milone_assert(match_175, 431, 2);
    int call_386 = 0;
    struct Token_IntIntTuple2Tuple2 tuple_123;
    tuple_123.t0 = kind_;
    tuple_123.t1 = loc_1;
    struct Token_IntIntTuple2Tuple2List* list_59 = (struct Token_IntIntTuple2Tuple2List*)malloc(sizeof(struct Token_IntIntTuple2Tuple2List));
    list_59->head = tuple_123;
    list_59->tail = acc_3;
    struct Token_IntIntTuple2Tuple2List* newAcc_ = list_59;
    struct IntIntTuple2 call_387 = locShift_(text_29, i_37, r_9, loc_1);
    struct IntIntTuple2 newLoc_1 = call_387;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tuple_124;
    tuple_124.t0 = text_29;
    tuple_124.t1 = r_9;
    tuple_124.t2 = newLoc_1;
    tuple_124.t3 = newAcc_;
    return tuple_124;
}

struct Token_IntIntTuple2Tuple2List* tokEof_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 arg_110) {
    struct String text_30 = arg_110.t0;
    int i_38 = arg_110.t1;
    struct Token_IntIntTuple2Tuple2List* acc_4 = arg_110.t3;
    int call_388 = lookEof_(text_30, i_38);
    milone_assert(call_388, 437, 2);
    int call_389 = 0;
    struct Token_IntIntTuple2Tuple2List* call_390 = listRev_7(acc_4);
    return call_390;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokError_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_) {
    struct StringIntTuple2 call_391 = tokCtxToTextIndex_(t_);
    struct String text_31 = call_391.t0;
    int i_39 = call_391.t1;
    int call_392 = scanError_(text_31, i_39);
    int r_10 = call_392;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_393 = tokCtxSkip_(r_10, t_);
    return call_393;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokComment_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_1) {
    struct StringIntTuple2 call_394 = tokCtxToTextIndex_(t_1);
    struct String text_32 = call_394.t0;
    int i_40 = call_394.t1;
    int call_395 = scanLine_(text_32, i_40);
    int r_11 = call_395;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_396 = tokCtxSkip_(r_11, t_1);
    return call_396;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokSpace_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_2) {
    struct StringIntTuple2 call_397 = tokCtxToTextIndex_(t_2);
    struct String text_33 = call_397.t0;
    int i_41 = call_397.t1;
    int call_398 = scanSpace_(text_33, i_41);
    int r_12 = call_398;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_399 = tokCtxSkip_(r_12, t_2);
    return call_399;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokPun_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_3) {
    struct StringIntTuple2 call_400 = tokCtxToTextIndex_(t_3);
    struct String text_34 = call_400.t0;
    int i_42 = call_400.t1;
    int call_401 = scanPun_(text_34, i_42);
    int r_13 = call_401;
    struct Token_ call_402 = tokenFromPun_(text_34, i_42, r_13);
    struct Token_ token_ = call_402;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_403 = tokCtxPush_(token_, r_13, t_3);
    return call_403;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokOp_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_4) {
    struct StringIntTuple2 call_404 = tokCtxToTextIndex_(t_4);
    struct String text_35 = call_404.t0;
    int i_43 = call_404.t1;
    int call_405 = scanOp_(text_35, i_43);
    int r_14 = call_405;
    struct Token_ call_406 = tokenFromOp_(text_35, i_43, r_14);
    struct Token_ token_1 = call_406;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_407 = tokCtxPush_(token_1, r_14, t_4);
    return call_407;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokIdent_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_5) {
    struct StringIntTuple2 call_408 = tokCtxToTextIndex_(t_5);
    struct String text_36 = call_408.t0;
    int i_44 = call_408.t1;
    int call_409 = scanIdent_(text_36, i_44);
    int r_15 = call_409;
    struct Token_ call_410 = tokenFromIdent_(text_36, i_44, r_15);
    struct Token_ token_2 = call_410;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_411 = tokCtxPush_(token_2, r_15, t_5);
    return call_411;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokIntLit_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_6) {
    struct StringIntTuple2 call_412 = tokCtxToTextIndex_(t_6);
    struct String text_37 = call_412.t0;
    int i_45 = call_412.t1;
    int call_413 = scanIntLit_(text_37, i_45);
    int r_16 = call_413;
    struct Token_ call_414 = tokenFromIntLit_(text_37, i_45, r_16);
    struct Token_ token_3 = call_414;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_415 = tokCtxPush_(token_3, r_16, t_6);
    return call_415;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokCharLit_(char charNull_, struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_7) {
    struct StringIntTuple2 call_416 = tokCtxToTextIndex_(t_7);
    struct String text_38 = call_416.t0;
    int i_46 = call_416.t1;
    struct BoolIntTuple2 call_417 = scanCharLit_(text_38, i_46);
    int ok_ = call_417.t0;
    int r_17 = call_417.t1;
    struct Token_ match_177;
    if ((!(ok_))) goto next_696;
    struct Token_ call_418 = tokenFromCharLit_(charNull_, text_38, i_46, r_17);
    match_177 = call_418;
    goto end_match_695;
next_696:;
    if (ok_) goto next_697;
    match_177 = (struct Token_){.tag = Error_};
    goto end_match_695;
next_697:;
    exit(1);
end_match_695:;
    struct Token_ token_4 = match_177;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_419 = tokCtxPush_(token_4, r_17, t_7);
    return call_419;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokStrLit_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_8) {
    struct StringIntTuple2 call_420 = tokCtxToTextIndex_(t_8);
    struct String text_39 = call_420.t0;
    int i_47 = call_420.t1;
    struct BoolIntTuple2 call_421 = scanStrLit_(text_39, i_47);
    int ok_1 = call_421.t0;
    int r_18 = call_421.t1;
    struct Token_ match_178;
    if ((!(ok_1))) goto next_699;
    struct Token_ call_422 = tokenFromStrLit_(text_39, i_47, r_18);
    match_178 = call_422;
    goto end_match_698;
next_699:;
    if (ok_1) goto next_700;
    match_178 = (struct Token_){.tag = Error_};
    goto end_match_698;
next_700:;
    exit(1);
end_match_698:;
    struct Token_ token_5 = match_178;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_423 = tokCtxPush_(token_5, r_18, t_8);
    return call_423;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokStrLitRaw_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_9) {
    struct StringIntTuple2 call_424 = tokCtxToTextIndex_(t_9);
    struct String text_40 = call_424.t0;
    int i_48 = call_424.t1;
    struct BoolIntTuple2 call_425 = scanStrLitRaw_(text_40, i_48);
    int ok_2 = call_425.t0;
    int r_19 = call_425.t1;
    struct Token_ match_179;
    if ((!(ok_2))) goto next_702;
    struct Token_ call_426 = tokenFromStrLitRaw_(text_40, i_48, r_19);
    match_179 = call_426;
    goto end_match_701;
next_702:;
    if (ok_2) goto next_703;
    match_179 = (struct Token_){.tag = Error_};
    goto end_match_701;
next_703:;
    exit(1);
end_match_701:;
    struct Token_ token_6 = match_179;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_427 = tokCtxPush_(token_6, r_19, t_9);
    return call_427;
}

struct Token_IntIntTuple2Tuple2List* go_11(char charNull_, struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_10) {
    struct StringIntTuple2 call_428 = tokCtxToTextIndex_(t_10);
    struct String text_42 = call_428.t0;
    int i_49 = call_428.t1;
    struct Token_IntIntTuple2Tuple2List* match_180;
    int call_429 = lookEof_(text_42, i_49);
    if ((!(call_429))) goto next_705;
    struct Token_IntIntTuple2Tuple2List* call_430 = tokEof_(t_10);
    match_180 = call_430;
    goto end_match_704;
next_705:;
    if (call_429) goto next_706;
    struct Token_IntIntTuple2Tuple2List* match_181;
    int call_431 = lookComment_(text_42, i_49);
    if ((!(call_431))) goto next_708;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_432 = tokComment_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_433 = go_11(charNull_, call_432);
    match_181 = call_433;
    goto end_match_707;
next_708:;
    if (call_431) goto next_709;
    struct Token_IntIntTuple2Tuple2List* match_182;
    int call_434 = lookSpace_(text_42, i_49);
    if ((!(call_434))) goto next_711;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_435 = tokSpace_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_436 = go_11(charNull_, call_435);
    match_182 = call_436;
    goto end_match_710;
next_711:;
    if (call_434) goto next_712;
    struct Token_IntIntTuple2Tuple2List* match_183;
    int call_437 = lookOp_(text_42, i_49);
    if ((!(call_437))) goto next_714;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_438 = tokOp_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_439 = go_11(charNull_, call_438);
    match_183 = call_439;
    goto end_match_713;
next_714:;
    if (call_437) goto next_715;
    struct Token_IntIntTuple2Tuple2List* match_184;
    int call_440 = lookIntLit_(text_42, i_49);
    if ((!(call_440))) goto next_717;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_441 = tokIntLit_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_442 = go_11(charNull_, call_441);
    match_184 = call_442;
    goto end_match_716;
next_717:;
    if (call_440) goto next_718;
    struct Token_IntIntTuple2Tuple2List* match_185;
    int call_443 = lookIdent_(text_42, i_49);
    if ((!(call_443))) goto next_720;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_444 = tokIdent_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_445 = go_11(charNull_, call_444);
    match_185 = call_445;
    goto end_match_719;
next_720:;
    if (call_443) goto next_721;
    struct Token_IntIntTuple2Tuple2List* match_186;
    int call_446 = lookCharLit_(text_42, i_49);
    if ((!(call_446))) goto next_723;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_447 = tokCharLit_(charNull_, t_10);
    struct Token_IntIntTuple2Tuple2List* call_448 = go_11(charNull_, call_447);
    match_186 = call_448;
    goto end_match_722;
next_723:;
    if (call_446) goto next_724;
    struct Token_IntIntTuple2Tuple2List* match_187;
    int call_449 = lookStrLitRaw_(text_42, i_49);
    if ((!(call_449))) goto next_726;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_450 = tokStrLitRaw_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_451 = go_11(charNull_, call_450);
    match_187 = call_451;
    goto end_match_725;
next_726:;
    if (call_449) goto next_727;
    struct Token_IntIntTuple2Tuple2List* match_188;
    int call_452 = lookStrLit_(text_42, i_49);
    if ((!(call_452))) goto next_729;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_453 = tokStrLit_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_454 = go_11(charNull_, call_453);
    match_188 = call_454;
    goto end_match_728;
next_729:;
    if (call_452) goto next_730;
    struct Token_IntIntTuple2Tuple2List* match_189;
    int call_455 = lookPun_(text_42, i_49);
    if ((!(call_455))) goto next_732;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_456 = tokPun_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_457 = go_11(charNull_, call_456);
    match_189 = call_457;
    goto end_match_731;
next_732:;
    if (call_455) goto next_733;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_458 = tokError_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_459 = go_11(charNull_, call_458);
    match_189 = call_459;
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
    match_182 = match_183;
    goto end_match_710;
next_712:;
    exit(1);
end_match_710:;
    match_181 = match_182;
    goto end_match_707;
next_709:;
    exit(1);
end_match_707:;
    match_180 = match_181;
    goto end_match_704;
next_706:;
    exit(1);
end_match_704:;
    return match_180;
}

struct Token_IntIntTuple2Tuple2List* tokenize_(char charNull_, struct String text_41) {
    struct IntIntTuple2 tuple_126;
    tuple_126.t0 = 0;
    tuple_126.t1 = 0;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tuple_125;
    tuple_125.t0 = text_41;
    tuple_125.t1 = 0;
    tuple_125.t2 = tuple_126;
    tuple_125.t3 = NULL;
    struct Token_IntIntTuple2Tuple2List* call_460 = go_11(charNull_, tuple_125);
    return call_460;
}

int leadsExpr_1(struct Token_IntIntTuple2Tuple2List* tokens_1) {
    int match_190;
    if ((!(tokens_1))) goto next_735;
    struct Token_ token_14 = tokens_1->head.t0;
    int call_461 = tokenIsExprFirst_(token_14);
    match_190 = call_461;
    goto end_match_734;
next_735:;
    match_190 = 0;
    goto end_match_734;
next_736:;
end_match_734:;
    return match_190;
}

int leadsArg_1(struct Token_IntIntTuple2Tuple2List* tokens_2) {
    int match_191;
    if ((!(tokens_2))) goto next_738;
    struct Token_ token_15 = tokens_2->head.t0;
    int call_462 = tokenIsArgFirst_(token_15);
    match_191 = call_462;
    goto end_match_737;
next_738:;
    match_191 = 0;
    goto end_match_737;
next_739:;
end_match_737:;
    return match_191;
}

int leadsPat_1(struct Token_IntIntTuple2Tuple2List* tokens_3) {
    int match_192;
    if ((!(tokens_3))) goto next_741;
    struct Token_ token_16 = tokens_3->head.t0;
    int call_463 = tokenIsPatFirst_(token_16);
    match_192 = call_463;
    goto end_match_740;
next_741:;
    match_192 = 0;
    goto end_match_740;
next_742:;
end_match_740:;
    return match_192;
}

struct IntIntTuple2 nextLoc_1(struct Token_IntIntTuple2Tuple2List* tokens_4) {
    struct IntIntTuple2 match_193;
    if ((!((!(tokens_4))))) goto next_744;
    struct IntIntTuple2 tuple_127;
    tuple_127.t0 = (0 - 1);
    tuple_127.t1 = 0;
    match_193 = tuple_127;
    goto end_match_743;
next_744:;
    if ((!(tokens_4))) goto next_745;
    struct IntIntTuple2 loc_27 = tokens_4->head.t1;
    match_193 = loc_27;
    goto end_match_743;
next_745:;
    exit(1);
end_match_743:;
    return match_193;
}

int nextInside_1(struct IntIntTuple2 baseLoc_, struct Token_IntIntTuple2Tuple2List* tokens_5) {
    int match_194;
    if ((!((!(tokens_5))))) goto next_747;
    match_194 = 0;
    goto end_match_746;
next_747:;
    if ((!(tokens_5))) goto next_748;
    struct IntIntTuple2 loc_28 = tokens_5->head.t1;
    int call_464 = locInside_(baseLoc_, loc_28);
    if ((!(call_464))) goto next_748;
    match_194 = 1;
    goto end_match_746;
next_748:;
    match_194 = 0;
    goto end_match_746;
next_749:;
end_match_746:;
    return match_194;
}

struct Token_ fun_39(void* env_6, struct Token_IntIntTuple2Tuple2 arg_27) {
    struct Token_ call_465 = fst_1(arg_27);
    return call_465;
}

struct StringStringToken_ListStringFun3 {
    struct String(*fun)(void*, struct String, struct String, struct Token_List*);
    void* env;
};

struct StringIntIntTuple2Tuple2List* parseErrorCore_1(struct String msg_3, struct IntIntTuple2 loc_29, struct Token_IntIntTuple2Tuple2List* tokens_6, struct StringIntIntTuple2Tuple2List* errors_1) {
    void* box_6 = (void*)malloc(sizeof(int));
    (*(((int*)box_6))) = 0;
    void* env_42 = box_6;
    struct Token_IntIntTuple2Tuple2Token_Fun1 fun_46 = (struct Token_IntIntTuple2Tuple2Token_Fun1){.fun = fun_39, .env = env_42};
    struct Token_List* call_466 = listMap_12(fun_46, tokens_6);
    struct Token_List* call_467 = listTruncate_1(6, call_466);
    struct Token_List* near_ = call_467;
    exit(1);
    struct String app_66 = ((struct StringStringToken_ListStringFun3){}).fun(((struct StringStringToken_ListStringFun3){}).env, (struct String){.str = "Parse error %s near %A", .len = 22}, msg_3, near_);
    struct String msg_4 = app_66;
    struct StringIntIntTuple2Tuple2 tuple_128;
    tuple_128.t0 = msg_4;
    tuple_128.t1 = loc_29;
    struct StringIntIntTuple2Tuple2List* list_60 = (struct StringIntIntTuple2Tuple2List*)malloc(sizeof(struct StringIntIntTuple2Tuple2List));
    list_60->head = tuple_128;
    list_60->tail = errors_1;
    return list_60;
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

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyError_1(struct String msg_5, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_111) {
    struct Token_IntIntTuple2Tuple2List* tokens_7 = arg_111.t0;
    struct StringIntIntTuple2Tuple2List* errors_2 = arg_111.t1;
    struct IntIntTuple2 call_468 = nextLoc_1(tokens_7);
    struct IntIntTuple2 loc_30 = call_468;
    struct StringIntIntTuple2Tuple2List* call_469 = parseErrorCore_1(msg_5, loc_30, tokens_7, errors_2);
    struct StringIntIntTuple2Tuple2List* errors_3 = call_469;
    struct IntIntTuple2* payload_76 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_76))) = loc_30;
    struct ATy_ variant_76 = (struct ATy_){.tag = Missing_, .Missing_ = payload_76};
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_129;
    tuple_129.t0 = variant_76;
    tuple_129.t1 = tokens_7;
    tuple_129.t2 = errors_3;
    return tuple_129;
}

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct APat_ t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatError_1(struct String msg_6, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_112) {
    struct Token_IntIntTuple2Tuple2List* tokens_8 = arg_112.t0;
    struct StringIntIntTuple2Tuple2List* errors_4 = arg_112.t1;
    struct IntIntTuple2 call_470 = nextLoc_1(tokens_8);
    struct IntIntTuple2 loc_31 = call_470;
    struct StringIntIntTuple2Tuple2List* call_471 = parseErrorCore_1(msg_6, loc_31, tokens_8, errors_4);
    struct StringIntIntTuple2Tuple2List* errors_5 = call_471;
    struct IntIntTuple2* payload_77 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_77))) = loc_31;
    struct APat_ variant_77 = (struct APat_){.tag = Missing_1, .Missing_1 = payload_77};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_130;
    tuple_130.t0 = variant_77;
    tuple_130.t1 = tokens_8;
    tuple_130.t2 = errors_5;
    return tuple_130;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct AExpr_ t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseExprError_1(struct String msg_7, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_113) {
    struct Token_IntIntTuple2Tuple2List* tokens_9 = arg_113.t0;
    struct StringIntIntTuple2Tuple2List* errors_6 = arg_113.t1;
    struct IntIntTuple2 call_472 = nextLoc_1(tokens_9);
    struct IntIntTuple2 loc_32 = call_472;
    struct StringIntIntTuple2Tuple2List* call_473 = parseErrorCore_1(msg_7, loc_32, tokens_9, errors_6);
    struct StringIntIntTuple2Tuple2List* errors_7 = call_473;
    struct IntIntTuple2* payload_78 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_78))) = loc_32;
    struct AExpr_ variant_78 = (struct AExpr_){.tag = Missing_2, .Missing_2 = payload_78};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_131;
    tuple_131.t0 = variant_78;
    tuple_131.t1 = tokens_9;
    tuple_131.t2 = errors_7;
    return tuple_131;
}

struct StringIntIntTuple2Tuple2List* parseNewError_1(struct String msg_8, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_114) {
    struct Token_IntIntTuple2Tuple2List* tokens_10 = arg_114.t0;
    struct StringIntIntTuple2Tuple2List* errors_8 = arg_114.t1;
    struct IntIntTuple2 call_474 = nextLoc_1(tokens_10);
    struct IntIntTuple2 loc_33 = call_474;
    struct StringIntIntTuple2Tuple2List* call_475 = parseErrorCore_1(msg_8, loc_33, tokens_10, errors_8);
    return call_475;
}

struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct ATy_List* t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_86(struct IntIntTuple2 baseLoc_1, struct ATy_List* acc_15, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_115) {
    struct Token_IntIntTuple2Tuple2List* tokens_13 = arg_115.t0;
    struct StringIntIntTuple2Tuple2List* errors_10 = arg_115.t1;
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_195;
    if ((!(tokens_13))) goto next_751;
    if ((tokens_13->head.t0.tag != Comma_)) goto next_751;
    struct Token_IntIntTuple2Tuple2List* tokens_14 = tokens_13->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_132;
    tuple_132.t0 = tokens_14;
    tuple_132.t1 = errors_10;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_476 = parseTy_1(baseLoc_1, tuple_132);
    struct ATy_ argTy_ = call_476.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_15 = call_476.t1;
    struct StringIntIntTuple2Tuple2List* errors_11 = call_476.t2;
    struct ATy_List* list_61 = (struct ATy_List*)malloc(sizeof(struct ATy_List));
    list_61->head = argTy_;
    list_61->tail = acc_15;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_133;
    tuple_133.t0 = tokens_15;
    tuple_133.t1 = errors_11;
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_477 = go_86(baseLoc_1, list_61, tuple_133);
    match_195 = call_477;
    goto end_match_750;
next_751:;
    struct ATy_List* call_478 = listRev_6(acc_15);
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_134;
    tuple_134.t0 = call_478;
    tuple_134.t1 = tokens_13;
    tuple_134.t2 = errors_10;
    match_195 = tuple_134;
    goto end_match_750;
next_752:;
end_match_750:;
    return match_195;
}

struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyArgs_1(struct IntIntTuple2 baseLoc_1, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_116) {
    struct Token_IntIntTuple2Tuple2List* tokens_11 = arg_116.t0;
    struct StringIntIntTuple2Tuple2List* errors_9 = arg_116.t1;
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_196;
    if ((!(tokens_11))) goto next_754;
    if ((tokens_11->head.t0.tag != Lt_)) goto next_754;
    struct IntIntTuple2 ltLoc_ = tokens_11->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_12 = tokens_11->tail;
    int call_479 = locInside_(baseLoc_1, ltLoc_);
    if ((!(call_479))) goto next_754;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_135;
    tuple_135.t0 = tokens_12;
    tuple_135.t1 = errors_9;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_480 = parseTy_1(baseLoc_1, tuple_135);
    struct ATy_ argTy_1 = call_480.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_16 = call_480.t1;
    struct StringIntIntTuple2Tuple2List* errors_12 = call_480.t2;
    struct ATy_List* list_62 = (struct ATy_List*)malloc(sizeof(struct ATy_List));
    list_62->head = argTy_1;
    list_62->tail = NULL;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_136;
    tuple_136.t0 = tokens_16;
    tuple_136.t1 = errors_12;
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_481 = go_86(baseLoc_1, list_62, tuple_136);
    struct ATy_List* argTys_ = call_481.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_17 = call_481.t1;
    struct StringIntIntTuple2Tuple2List* errors_13 = call_481.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 match_197;
    if ((!(tokens_17))) goto next_757;
    if ((tokens_17->head.t0.tag != Gt_)) goto next_757;
    struct Token_IntIntTuple2Tuple2List* tokens_19 = tokens_17->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_137;
    tuple_137.t0 = tokens_19;
    tuple_137.t1 = errors_13;
    match_197 = tuple_137;
    goto end_match_756;
next_757:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_138;
    tuple_138.t0 = tokens_17;
    tuple_138.t1 = errors_13;
    struct StringIntIntTuple2Tuple2List* call_482 = parseNewError_1((struct String){.str = "Expected \'>\'", .len = 12}, tuple_138);
    struct StringIntIntTuple2Tuple2List* errors_15 = call_482;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_139;
    tuple_139.t0 = tokens_17;
    tuple_139.t1 = errors_15;
    match_197 = tuple_139;
    goto end_match_756;
next_758:;
end_match_756:;
    struct Token_IntIntTuple2Tuple2List* tokens_18 = match_197.t0;
    struct StringIntIntTuple2Tuple2List* errors_14 = match_197.t1;
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_140;
    tuple_140.t0 = argTys_;
    tuple_140.t1 = tokens_18;
    tuple_140.t2 = errors_14;
    match_196 = tuple_140;
    goto end_match_753;
next_754:;
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_141;
    tuple_141.t0 = NULL;
    tuple_141.t1 = tokens_11;
    tuple_141.t2 = errors_9;
    match_196 = tuple_141;
    goto end_match_753;
next_755:;
end_match_753:;
    return match_196;
}

struct StringATy_ListIntIntTuple2Tuple3 {
    struct String t0;
    struct ATy_List* t1;
    struct IntIntTuple2 t2;
};

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyAtom_1(struct IntIntTuple2 baseLoc_2, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_117) {
    struct Token_IntIntTuple2Tuple2List* tokens_20 = arg_117.t0;
    struct StringIntIntTuple2Tuple2List* errors_16 = arg_117.t1;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_198;
    int call_483 = nextInside_1(baseLoc_2, tokens_20);
    if (call_483) goto next_760;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_142;
    tuple_142.t0 = tokens_20;
    tuple_142.t1 = errors_16;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_484 = parseTyError_1((struct String){.str = "Expected a type atom", .len = 20}, tuple_142);
    match_198 = call_484;
    goto end_match_759;
next_760:;
    if ((!(tokens_20))) goto next_761;
    if ((tokens_20->head.t0.tag != Ident_)) goto next_761;
    struct String ident_18 = (*(tokens_20->head.t0.Ident_));
    struct IntIntTuple2 loc_34 = tokens_20->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_21 = tokens_20->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_143;
    tuple_143.t0 = tokens_21;
    tuple_143.t1 = errors_16;
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_485 = parseTyArgs_1(baseLoc_2, tuple_143);
    struct ATy_List* argTys_1 = call_485.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_22 = call_485.t1;
    struct StringIntIntTuple2Tuple2List* errors_17 = call_485.t2;
    struct StringATy_ListIntIntTuple2Tuple3 tuple_145;
    tuple_145.t0 = ident_18;
    tuple_145.t1 = argTys_1;
    tuple_145.t2 = loc_34;
    struct StringATy_ListIntIntTuple2Tuple3* payload_79 = (struct StringATy_ListIntIntTuple2Tuple3*)malloc(sizeof(struct StringATy_ListIntIntTuple2Tuple3));
    (*(((struct StringATy_ListIntIntTuple2Tuple3*)payload_79))) = tuple_145;
    struct ATy_ variant_79 = (struct ATy_){.tag = App_1, .App_1 = payload_79};
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_144;
    tuple_144.t0 = variant_79;
    tuple_144.t1 = tokens_22;
    tuple_144.t2 = errors_17;
    match_198 = tuple_144;
    goto end_match_759;
next_761:;
    if ((!(tokens_20))) goto next_762;
    if ((tokens_20->head.t0.tag != ParenL_)) goto next_762;
    struct Token_IntIntTuple2Tuple2List* tokens_23 = tokens_20->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_146;
    tuple_146.t0 = tokens_23;
    tuple_146.t1 = errors_16;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_486 = parseTy_1(baseLoc_2, tuple_146);
    struct ATy_ ty_47 = call_486.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_24 = call_486.t1;
    struct StringIntIntTuple2Tuple2List* errors_18 = call_486.t2;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_199;
    if ((!(tokens_24))) goto next_765;
    if ((tokens_24->head.t0.tag != ParenR_)) goto next_765;
    struct Token_IntIntTuple2Tuple2List* tokens_25 = tokens_24->tail;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_147;
    tuple_147.t0 = ty_47;
    tuple_147.t1 = tokens_25;
    tuple_147.t2 = errors_18;
    match_199 = tuple_147;
    goto end_match_764;
next_765:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_148;
    tuple_148.t0 = tokens_24;
    tuple_148.t1 = errors_18;
    struct StringIntIntTuple2Tuple2List* call_487 = parseNewError_1((struct String){.str = "Expected \')\'", .len = 12}, tuple_148);
    struct StringIntIntTuple2Tuple2List* errors_19 = call_487;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_149;
    tuple_149.t0 = ty_47;
    tuple_149.t1 = tokens_24;
    tuple_149.t2 = errors_19;
    match_199 = tuple_149;
    goto end_match_764;
next_766:;
end_match_764:;
    match_198 = match_199;
    goto end_match_759;
next_762:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_150;
    tuple_150.t0 = tokens_20;
    tuple_150.t1 = errors_16;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_488 = parseTyError_1((struct String){.str = "Expected a type atom", .len = 20}, tuple_150);
    match_198 = call_488;
    goto end_match_759;
next_763:;
end_match_759:;
    return match_198;
}

struct ATy_StringIntIntTuple2Tuple3 {
    struct ATy_ t0;
    struct String t1;
    struct IntIntTuple2 t2;
};

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_83(struct IntIntTuple2 baseLoc_3, struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 arg_118) {
    struct ATy_ ty_48 = arg_118.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_27 = arg_118.t1;
    struct StringIntIntTuple2Tuple2List* errors_21 = arg_118.t2;
    int call_489 = nextInside_1(baseLoc_3, tokens_27);
    int inside_ = call_489;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_200;
    if ((!(tokens_27))) goto next_768;
    if ((tokens_27->head.t0.tag != Ident_)) goto next_768;
    struct String ident_19 = (*(tokens_27->head.t0.Ident_));
    struct IntIntTuple2 loc_35 = tokens_27->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_28 = tokens_27->tail;
    if ((!(inside_))) goto next_768;
    struct ATy_StringIntIntTuple2Tuple3 tuple_152;
    tuple_152.t0 = ty_48;
    tuple_152.t1 = ident_19;
    tuple_152.t2 = loc_35;
    struct ATy_StringIntIntTuple2Tuple3* payload_80 = (struct ATy_StringIntIntTuple2Tuple3*)malloc(sizeof(struct ATy_StringIntIntTuple2Tuple3));
    (*(((struct ATy_StringIntIntTuple2Tuple3*)payload_80))) = tuple_152;
    struct ATy_ variant_80 = (struct ATy_){.tag = Suffix_, .Suffix_ = payload_80};
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_151;
    tuple_151.t0 = variant_80;
    tuple_151.t1 = tokens_28;
    tuple_151.t2 = errors_21;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_490 = go_83(baseLoc_3, tuple_151);
    match_200 = call_490;
    goto end_match_767;
next_768:;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_153;
    tuple_153.t0 = ty_48;
    tuple_153.t1 = tokens_27;
    tuple_153.t2 = errors_21;
    match_200 = tuple_153;
    goto end_match_767;
next_769:;
end_match_767:;
    return match_200;
}

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTySuffix_1(struct IntIntTuple2 baseLoc_3, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_119) {
    struct Token_IntIntTuple2Tuple2List* tokens_26 = arg_119.t0;
    struct StringIntIntTuple2Tuple2List* errors_20 = arg_119.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_154;
    tuple_154.t0 = tokens_26;
    tuple_154.t1 = errors_20;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_491 = parseTyAtom_1(baseLoc_3, tuple_154);
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_492 = go_83(baseLoc_3, call_491);
    return call_492;
}

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyPrefix_1(struct IntIntTuple2 baseLoc_4, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_120) {
    struct Token_IntIntTuple2Tuple2List* tokens_29 = arg_120.t0;
    struct StringIntIntTuple2Tuple2List* errors_22 = arg_120.t1;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_201;
    if ((!(tokens_29))) goto next_771;
    if ((tokens_29->head.t0.tag != Ident_)) goto next_771;
    if ((!(tokens_29->tail))) goto next_771;
    if ((tokens_29->tail->head.t0.tag != Colon_)) goto next_771;
    struct Token_IntIntTuple2Tuple2List* tokens_30 = tokens_29->tail->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_155;
    tuple_155.t0 = tokens_30;
    tuple_155.t1 = errors_22;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_493 = parseTySuffix_1(baseLoc_4, tuple_155);
    match_201 = call_493;
    goto end_match_770;
next_771:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_156;
    tuple_156.t0 = tokens_29;
    tuple_156.t1 = errors_22;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_494 = parseTySuffix_1(baseLoc_4, tuple_156);
    match_201 = call_494;
    goto end_match_770;
next_772:;
end_match_770:;
    return match_201;
}

struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_80(struct IntIntTuple2 baseLoc_5, struct ATy_List* acc_16, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_121) {
    struct Token_IntIntTuple2Tuple2List* tokens_32 = arg_121.t0;
    struct StringIntIntTuple2Tuple2List* errors_24 = arg_121.t1;
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_202;
    if ((!(tokens_32))) goto next_774;
    if ((tokens_32->head.t0.tag != Star_)) goto next_774;
    struct Token_IntIntTuple2Tuple2List* tokens_33 = tokens_32->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_157;
    tuple_157.t0 = tokens_33;
    tuple_157.t1 = errors_24;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_495 = parseTyPrefix_1(baseLoc_5, tuple_157);
    struct ATy_ itemTy_11 = call_495.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_34 = call_495.t1;
    struct StringIntIntTuple2Tuple2List* errors_25 = call_495.t2;
    struct ATy_List* list_63 = (struct ATy_List*)malloc(sizeof(struct ATy_List));
    list_63->head = itemTy_11;
    list_63->tail = acc_16;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_158;
    tuple_158.t0 = tokens_34;
    tuple_158.t1 = errors_25;
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_496 = go_80(baseLoc_5, list_63, tuple_158);
    match_202 = call_496;
    goto end_match_773;
next_774:;
    struct ATy_List* call_497 = listRev_6(acc_16);
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_159;
    tuple_159.t0 = call_497;
    tuple_159.t1 = tokens_32;
    tuple_159.t2 = errors_24;
    match_202 = tuple_159;
    goto end_match_773;
next_775:;
end_match_773:;
    return match_202;
}

struct ATy_ListIntIntTuple2Tuple2 {
    struct ATy_List* t0;
    struct IntIntTuple2 t1;
};

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyTuple_1(struct IntIntTuple2 baseLoc_5, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_122) {
    struct Token_IntIntTuple2Tuple2List* tokens_31 = arg_122.t0;
    struct StringIntIntTuple2Tuple2List* errors_23 = arg_122.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_160;
    tuple_160.t0 = tokens_31;
    tuple_160.t1 = errors_23;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_498 = parseTyPrefix_1(baseLoc_5, tuple_160);
    struct ATy_ itemTy_12 = call_498.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_35 = call_498.t1;
    struct StringIntIntTuple2Tuple2List* errors_26 = call_498.t2;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_203;
    if ((!(tokens_35))) goto next_777;
    if ((tokens_35->head.t0.tag != Star_)) goto next_777;
    struct IntIntTuple2 opLoc_ = tokens_35->head.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_161;
    tuple_161.t0 = tokens_35;
    tuple_161.t1 = errors_26;
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_499 = go_80(baseLoc_5, NULL, tuple_161);
    struct ATy_List* itemTys_1 = call_499.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_36 = call_499.t1;
    struct StringIntIntTuple2Tuple2List* errors_27 = call_499.t2;
    struct ATy_List* list_64 = (struct ATy_List*)malloc(sizeof(struct ATy_List));
    list_64->head = itemTy_12;
    list_64->tail = itemTys_1;
    struct ATy_ListIntIntTuple2Tuple2 tuple_163;
    tuple_163.t0 = list_64;
    tuple_163.t1 = opLoc_;
    struct ATy_ListIntIntTuple2Tuple2* payload_81 = (struct ATy_ListIntIntTuple2Tuple2*)malloc(sizeof(struct ATy_ListIntIntTuple2Tuple2));
    (*(((struct ATy_ListIntIntTuple2Tuple2*)payload_81))) = tuple_163;
    struct ATy_ variant_81 = (struct ATy_){.tag = Tuple_, .Tuple_ = payload_81};
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_162;
    tuple_162.t0 = variant_81;
    tuple_162.t1 = tokens_36;
    tuple_162.t2 = errors_27;
    match_203 = tuple_162;
    goto end_match_776;
next_777:;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_164;
    tuple_164.t0 = itemTy_12;
    tuple_164.t1 = tokens_35;
    tuple_164.t2 = errors_26;
    match_203 = tuple_164;
    goto end_match_776;
next_778:;
end_match_776:;
    return match_203;
}

struct ATy_ATy_IntIntTuple2Tuple3 {
    struct ATy_ t0;
    struct ATy_ t1;
    struct IntIntTuple2 t2;
};

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyFun_1(struct IntIntTuple2 baseLoc_6, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_123) {
    struct Token_IntIntTuple2Tuple2List* tokens_37 = arg_123.t0;
    struct StringIntIntTuple2Tuple2List* errors_28 = arg_123.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_165;
    tuple_165.t0 = tokens_37;
    tuple_165.t1 = errors_28;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_500 = parseTyTuple_1(baseLoc_6, tuple_165);
    struct ATy_ sTy_1 = call_500.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_38 = call_500.t1;
    struct StringIntIntTuple2Tuple2List* errors_29 = call_500.t2;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_204;
    if ((!(tokens_38))) goto next_780;
    if ((tokens_38->head.t0.tag != Arrow_)) goto next_780;
    struct IntIntTuple2 opLoc_1 = tokens_38->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_39 = tokens_38->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_166;
    tuple_166.t0 = tokens_39;
    tuple_166.t1 = errors_29;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_501 = parseTyFun_1(baseLoc_6, tuple_166);
    struct ATy_ tTy_1 = call_501.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_40 = call_501.t1;
    struct StringIntIntTuple2Tuple2List* errors_30 = call_501.t2;
    struct ATy_ATy_IntIntTuple2Tuple3 tuple_168;
    tuple_168.t0 = sTy_1;
    tuple_168.t1 = tTy_1;
    tuple_168.t2 = opLoc_1;
    struct ATy_ATy_IntIntTuple2Tuple3* payload_82 = (struct ATy_ATy_IntIntTuple2Tuple3*)malloc(sizeof(struct ATy_ATy_IntIntTuple2Tuple3));
    (*(((struct ATy_ATy_IntIntTuple2Tuple3*)payload_82))) = tuple_168;
    struct ATy_ variant_82 = (struct ATy_){.tag = Fun_1, .Fun_1 = payload_82};
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_167;
    tuple_167.t0 = variant_82;
    tuple_167.t1 = tokens_40;
    tuple_167.t2 = errors_30;
    match_204 = tuple_167;
    goto end_match_779;
next_780:;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_169;
    tuple_169.t0 = sTy_1;
    tuple_169.t1 = tokens_38;
    tuple_169.t2 = errors_29;
    match_204 = tuple_169;
    goto end_match_779;
next_781:;
end_match_779:;
    return match_204;
}

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTy_1(struct IntIntTuple2 baseLoc_7, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_124) {
    struct Token_IntIntTuple2Tuple2List* tokens_41 = arg_124.t0;
    struct StringIntIntTuple2Tuple2List* errors_31 = arg_124.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_170;
    tuple_170.t0 = tokens_41;
    tuple_170.t1 = errors_31;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_502 = parseTyFun_1(baseLoc_7, tuple_170);
    return call_502;
}

struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct AVariant_List* t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_79(struct IntIntTuple2 baseLoc_8, struct AVariant_List* acc_17, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_125) {
    struct Token_IntIntTuple2Tuple2List* tokens_43 = arg_125.t0;
    struct StringIntIntTuple2Tuple2List* errors_33 = arg_125.t1;
    struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_205;
    if ((!(tokens_43))) goto next_783;
    if ((tokens_43->head.t0.tag != Pipe_)) goto next_783;
    if ((!(tokens_43->tail))) goto next_783;
    if ((tokens_43->tail->head.t0.tag != Ident_)) goto next_783;
    struct String variantIdent_ = (*(tokens_43->tail->head.t0.Ident_));
    struct IntIntTuple2 loc_36 = tokens_43->tail->head.t1;
    if ((!(tokens_43->tail->tail))) goto next_783;
    if ((tokens_43->tail->tail->head.t0.tag != Of_)) goto next_783;
    struct Token_IntIntTuple2Tuple2List* tokens_44 = tokens_43->tail->tail->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_171;
    tuple_171.t0 = tokens_44;
    tuple_171.t1 = errors_33;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_503 = parseTy_1(baseLoc_8, tuple_171);
    struct ATy_ payloadTy_ = call_503.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_45 = call_503.t1;
    struct StringIntIntTuple2Tuple2List* errors_34 = call_503.t2;
    struct ATy_List* some_ = (struct ATy_List*)malloc(sizeof(struct ATy_List));
    some_->head = payloadTy_;
    some_->tail = NULL;
    struct StringATy_ListIntIntTuple2Tuple3 tuple_172;
    tuple_172.t0 = variantIdent_;
    tuple_172.t1 = some_;
    tuple_172.t2 = loc_36;
    struct StringATy_ListIntIntTuple2Tuple3* payload_83 = (struct StringATy_ListIntIntTuple2Tuple3*)malloc(sizeof(struct StringATy_ListIntIntTuple2Tuple3));
    (*(((struct StringATy_ListIntIntTuple2Tuple3*)payload_83))) = tuple_172;
    struct AVariant_ variant_83 = (struct AVariant_){.tag = AVariant_, .AVariant_ = payload_83};
    struct AVariant_List* list_65 = (struct AVariant_List*)malloc(sizeof(struct AVariant_List));
    list_65->head = variant_83;
    list_65->tail = acc_17;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_173;
    tuple_173.t0 = tokens_45;
    tuple_173.t1 = errors_34;
    struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_504 = go_79(baseLoc_8, list_65, tuple_173);
    match_205 = call_504;
    goto end_match_782;
next_783:;
    if ((!(tokens_43))) goto next_784;
    if ((tokens_43->head.t0.tag != Pipe_)) goto next_784;
    if ((!(tokens_43->tail))) goto next_784;
    if ((tokens_43->tail->head.t0.tag != Ident_)) goto next_784;
    struct String variantIdent_1 = (*(tokens_43->tail->head.t0.Ident_));
    struct IntIntTuple2 loc_37 = tokens_43->tail->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_46 = tokens_43->tail->tail;
    struct StringATy_ListIntIntTuple2Tuple3 tuple_174;
    tuple_174.t0 = variantIdent_1;
    tuple_174.t1 = NULL;
    tuple_174.t2 = loc_37;
    struct StringATy_ListIntIntTuple2Tuple3* payload_84 = (struct StringATy_ListIntIntTuple2Tuple3*)malloc(sizeof(struct StringATy_ListIntIntTuple2Tuple3));
    (*(((struct StringATy_ListIntIntTuple2Tuple3*)payload_84))) = tuple_174;
    struct AVariant_ variant_84 = (struct AVariant_){.tag = AVariant_, .AVariant_ = payload_84};
    struct AVariant_List* list_66 = (struct AVariant_List*)malloc(sizeof(struct AVariant_List));
    list_66->head = variant_84;
    list_66->tail = acc_17;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_175;
    tuple_175.t0 = tokens_46;
    tuple_175.t1 = errors_33;
    struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_505 = go_79(baseLoc_8, list_66, tuple_175);
    match_205 = call_505;
    goto end_match_782;
next_784:;
    struct AVariant_List* call_506 = listRev_5(acc_17);
    struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_176;
    tuple_176.t0 = call_506;
    tuple_176.t1 = tokens_43;
    tuple_176.t2 = errors_33;
    match_205 = tuple_176;
    goto end_match_782;
next_785:;
end_match_782:;
    return match_205;
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

struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyDeclUnion_1(struct IntIntTuple2 baseLoc_8, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_126) {
    struct Token_IntIntTuple2Tuple2List* tokens_42 = arg_126.t0;
    struct StringIntIntTuple2Tuple2List* errors_32 = arg_126.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_177;
    tuple_177.t0 = tokens_42;
    tuple_177.t1 = errors_32;
    struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_507 = go_79(baseLoc_8, NULL, tuple_177);
    struct AVariant_List* variants_1 = call_507.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_47 = call_507.t1;
    struct StringIntIntTuple2Tuple2List* errors_35 = call_507.t2;
    struct AVariant_List** payload_85 = (struct AVariant_List**)malloc(sizeof(struct AVariant_List*));
    (*(((struct AVariant_List**)payload_85))) = variants_1;
    struct ATyDecl_ variant_85 = (struct ATyDecl_){.tag = Union_, .Union_ = payload_85};
    struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_178;
    tuple_178.t0 = variant_85;
    tuple_178.t1 = tokens_47;
    tuple_178.t2 = errors_35;
    return tuple_178;
}

struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyDeclBody_1(struct IntIntTuple2 baseLoc_9, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_127) {
    struct Token_IntIntTuple2Tuple2List* tokens_48 = arg_127.t0;
    struct StringIntIntTuple2Tuple2List* errors_36 = arg_127.t1;
    struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_206;
    if ((!(tokens_48))) goto next_787;
    if ((tokens_48->head.t0.tag != Pipe_)) goto next_787;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_179;
    tuple_179.t0 = tokens_48;
    tuple_179.t1 = errors_36;
    struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_508 = parseTyDeclUnion_1(baseLoc_9, tuple_179);
    match_206 = call_508;
    goto end_match_786;
next_787:;
    if ((!(tokens_48))) goto next_788;
    if ((tokens_48->head.t0.tag != Ident_)) goto next_788;
    if ((!(tokens_48->tail))) goto next_788;
    if ((tokens_48->tail->head.t0.tag != Of_)) goto next_788;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_180;
    tuple_180.t0 = tokens_48;
    tuple_180.t1 = errors_36;
    struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_509 = parseTyDeclUnion_1(baseLoc_9, tuple_180);
    match_206 = call_509;
    goto end_match_786;
next_788:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_181;
    tuple_181.t0 = tokens_48;
    tuple_181.t1 = errors_36;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_510 = parseTy_1(baseLoc_9, tuple_181);
    struct ATy_ ty_49 = call_510.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_49 = call_510.t1;
    struct StringIntIntTuple2Tuple2List* errors_37 = call_510.t2;
    struct ATy_* payload_86 = (struct ATy_*)malloc(sizeof(struct ATy_));
    (*(((struct ATy_*)payload_86))) = ty_49;
    struct ATyDecl_ variant_86 = (struct ATyDecl_){.tag = Synonym_, .Synonym_ = payload_86};
    struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_182;
    tuple_182.t0 = variant_86;
    tuple_182.t1 = tokens_49;
    tuple_182.t2 = errors_37;
    match_206 = tuple_182;
    goto end_match_786;
next_789:;
end_match_786:;
    return match_206;
}

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatParenBody_1(struct IntIntTuple2 baseLoc_10, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_128) {
    struct Token_IntIntTuple2Tuple2List* tokens_50 = arg_128.t0;
    struct StringIntIntTuple2Tuple2List* errors_38 = arg_128.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_183;
    tuple_183.t0 = tokens_50;
    tuple_183.t1 = errors_38;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_511 = parsePat_1(baseLoc_10, tuple_183);
    struct APat_ pat_15 = call_511.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_51 = call_511.t1;
    struct StringIntIntTuple2Tuple2List* errors_39 = call_511.t2;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_207;
    if ((!(tokens_51))) goto next_791;
    if ((tokens_51->head.t0.tag != ParenR_)) goto next_791;
    struct Token_IntIntTuple2Tuple2List* tokens_52 = tokens_51->tail;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_184;
    tuple_184.t0 = pat_15;
    tuple_184.t1 = tokens_52;
    tuple_184.t2 = errors_39;
    match_207 = tuple_184;
    goto end_match_790;
next_791:;
    struct Token_IntIntTuple2Tuple2List* tokens_53 = tokens_51;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_185;
    tuple_185.t0 = tokens_53;
    tuple_185.t1 = errors_39;
    struct StringIntIntTuple2Tuple2List* call_512 = parseNewError_1((struct String){.str = "Expected \')\'", .len = 12}, tuple_185);
    struct StringIntIntTuple2Tuple2List* errors_40 = call_512;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_186;
    tuple_186.t0 = pat_15;
    tuple_186.t1 = tokens_53;
    tuple_186.t2 = errors_40;
    match_207 = tuple_186;
    goto end_match_790;
next_792:;
end_match_790:;
    return match_207;
}

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct APat_List* t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_82(struct IntIntTuple2 baseLoc_11, struct APat_List* patAcc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_129) {
    struct Token_IntIntTuple2Tuple2List* tokens_55 = arg_129.t0;
    struct StringIntIntTuple2Tuple2List* errors_42 = arg_129.t1;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_208;
    if ((!(tokens_55))) goto next_794;
    if ((tokens_55->head.t0.tag != BracketR_)) goto next_794;
    struct Token_IntIntTuple2Tuple2List* tokens_56 = tokens_55->tail;
    struct APat_List* call_513 = listRev_4(patAcc_);
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_187;
    tuple_187.t0 = call_513;
    tuple_187.t1 = tokens_56;
    tuple_187.t2 = errors_42;
    match_208 = tuple_187;
    goto end_match_793;
next_794:;
    if ((!(tokens_55))) goto next_795;
    if ((tokens_55->head.t0.tag != Semi_)) goto next_795;
    struct Token_IntIntTuple2Tuple2List* tokens_57 = tokens_55->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_188;
    tuple_188.t0 = tokens_57;
    tuple_188.t1 = errors_42;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_514 = parsePat_1(baseLoc_11, tuple_188);
    struct APat_ pat_16 = call_514.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_58 = call_514.t1;
    struct StringIntIntTuple2Tuple2List* errors_43 = call_514.t2;
    struct APat_List* list_67 = (struct APat_List*)malloc(sizeof(struct APat_List));
    list_67->head = pat_16;
    list_67->tail = patAcc_;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_189;
    tuple_189.t0 = tokens_58;
    tuple_189.t1 = errors_43;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_515 = go_82(baseLoc_11, list_67, tuple_189);
    match_208 = call_515;
    goto end_match_793;
next_795:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_190;
    tuple_190.t0 = tokens_55;
    tuple_190.t1 = errors_42;
    struct StringIntIntTuple2Tuple2List* call_516 = parseNewError_1((struct String){.str = "Expected \';\' or \']\'", .len = 19}, tuple_190);
    struct StringIntIntTuple2Tuple2List* errors_44 = call_516;
    struct APat_List* call_517 = listRev_4(patAcc_);
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_191;
    tuple_191.t0 = call_517;
    tuple_191.t1 = tokens_55;
    tuple_191.t2 = errors_44;
    match_208 = tuple_191;
    goto end_match_793;
next_796:;
end_match_793:;
    return match_208;
}

struct APat_ListIntIntTuple2Tuple2 {
    struct APat_List* t0;
    struct IntIntTuple2 t1;
};

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatListBody_1(struct IntIntTuple2 baseLoc_11, struct IntIntTuple2 bracketLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_130) {
    struct Token_IntIntTuple2Tuple2List* tokens_54 = arg_130.t0;
    struct StringIntIntTuple2Tuple2List* errors_41 = arg_130.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_192;
    tuple_192.t0 = tokens_54;
    tuple_192.t1 = errors_41;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_518 = parsePat_1(baseLoc_11, tuple_192);
    struct APat_ itemPat_ = call_518.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_59 = call_518.t1;
    struct StringIntIntTuple2Tuple2List* errors_45 = call_518.t2;
    struct APat_List* list_68 = (struct APat_List*)malloc(sizeof(struct APat_List));
    list_68->head = itemPat_;
    list_68->tail = NULL;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_193;
    tuple_193.t0 = tokens_59;
    tuple_193.t1 = errors_45;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_519 = go_82(baseLoc_11, list_68, tuple_193);
    struct APat_List* itemPats_1 = call_519.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_60 = call_519.t1;
    struct StringIntIntTuple2Tuple2List* errors_46 = call_519.t2;
    struct APat_ListIntIntTuple2Tuple2 tuple_195;
    tuple_195.t0 = itemPats_1;
    tuple_195.t1 = bracketLoc_;
    struct APat_ListIntIntTuple2Tuple2* payload_87 = (struct APat_ListIntIntTuple2Tuple2*)malloc(sizeof(struct APat_ListIntIntTuple2Tuple2));
    (*(((struct APat_ListIntIntTuple2Tuple2*)payload_87))) = tuple_195;
    struct APat_ variant_87 = (struct APat_){.tag = ListLit_, .ListLit_ = payload_87};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_194;
    tuple_194.t0 = variant_87;
    tuple_194.t1 = tokens_60;
    tuple_194.t2 = errors_46;
    return tuple_194;
}

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatAtom_1(struct IntIntTuple2 baseLoc_12, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_131) {
    struct Token_IntIntTuple2Tuple2List* tokens_61 = arg_131.t0;
    struct StringIntIntTuple2Tuple2List* errors_47 = arg_131.t1;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_209;
    int match_210;
    int call_520 = nextInside_1(baseLoc_12, tokens_61);
    if ((!(call_520))) goto next_810;
    int call_521 = leadsPat_1(tokens_61);
    match_210 = call_521;
    goto end_match_809;
next_810:;
    if (call_520) goto next_811;
    match_210 = 0;
    goto end_match_809;
next_811:;
    exit(1);
end_match_809:;
    if (match_210) goto next_798;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_196;
    tuple_196.t0 = tokens_61;
    tuple_196.t1 = errors_47;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_522 = parsePatError_1((struct String){.str = "Expected a pattern atom", .len = 23}, tuple_196);
    match_209 = call_522;
    goto end_match_797;
next_798:;
    if ((!(tokens_61))) goto next_799;
    if ((tokens_61->head.t0.tag != Bool_1)) goto next_799;
    int value_10 = (*(tokens_61->head.t0.Bool_1));
    struct IntIntTuple2 loc_38 = tokens_61->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_62 = tokens_61->tail;
    int* payload_88 = (int*)malloc(sizeof(int));
    (*(((int*)payload_88))) = value_10;
    struct Lit_ variant_88 = (struct Lit_){.tag = Bool_, .Bool_ = payload_88};
    struct Lit_IntIntTuple2Tuple2 tuple_198;
    tuple_198.t0 = variant_88;
    tuple_198.t1 = loc_38;
    struct Lit_IntIntTuple2Tuple2* payload_89 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_89))) = tuple_198;
    struct APat_ variant_89 = (struct APat_){.tag = Lit_, .Lit_ = payload_89};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_197;
    tuple_197.t0 = variant_89;
    tuple_197.t1 = tokens_62;
    tuple_197.t2 = errors_47;
    match_209 = tuple_197;
    goto end_match_797;
next_799:;
    if ((!(tokens_61))) goto next_800;
    if ((tokens_61->head.t0.tag != Int_1)) goto next_800;
    int value_11 = (*(tokens_61->head.t0.Int_1));
    struct IntIntTuple2 loc_39 = tokens_61->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_63 = tokens_61->tail;
    int* payload_90 = (int*)malloc(sizeof(int));
    (*(((int*)payload_90))) = value_11;
    struct Lit_ variant_90 = (struct Lit_){.tag = Int_, .Int_ = payload_90};
    struct Lit_IntIntTuple2Tuple2 tuple_200;
    tuple_200.t0 = variant_90;
    tuple_200.t1 = loc_39;
    struct Lit_IntIntTuple2Tuple2* payload_91 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_91))) = tuple_200;
    struct APat_ variant_91 = (struct APat_){.tag = Lit_, .Lit_ = payload_91};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_199;
    tuple_199.t0 = variant_91;
    tuple_199.t1 = tokens_63;
    tuple_199.t2 = errors_47;
    match_209 = tuple_199;
    goto end_match_797;
next_800:;
    if ((!(tokens_61))) goto next_801;
    if ((tokens_61->head.t0.tag != Char_1)) goto next_801;
    char value_12 = (*(tokens_61->head.t0.Char_1));
    struct IntIntTuple2 loc_40 = tokens_61->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_64 = tokens_61->tail;
    char* payload_92 = (char*)malloc(sizeof(char));
    (*(((char*)payload_92))) = value_12;
    struct Lit_ variant_92 = (struct Lit_){.tag = Char_, .Char_ = payload_92};
    struct Lit_IntIntTuple2Tuple2 tuple_202;
    tuple_202.t0 = variant_92;
    tuple_202.t1 = loc_40;
    struct Lit_IntIntTuple2Tuple2* payload_93 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_93))) = tuple_202;
    struct APat_ variant_93 = (struct APat_){.tag = Lit_, .Lit_ = payload_93};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_201;
    tuple_201.t0 = variant_93;
    tuple_201.t1 = tokens_64;
    tuple_201.t2 = errors_47;
    match_209 = tuple_201;
    goto end_match_797;
next_801:;
    if ((!(tokens_61))) goto next_802;
    if ((tokens_61->head.t0.tag != Str_1)) goto next_802;
    struct String value_13 = (*(tokens_61->head.t0.Str_1));
    struct IntIntTuple2 loc_41 = tokens_61->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_65 = tokens_61->tail;
    struct String* payload_94 = (struct String*)malloc(sizeof(struct String));
    (*(((struct String*)payload_94))) = value_13;
    struct Lit_ variant_94 = (struct Lit_){.tag = Str_, .Str_ = payload_94};
    struct Lit_IntIntTuple2Tuple2 tuple_204;
    tuple_204.t0 = variant_94;
    tuple_204.t1 = loc_41;
    struct Lit_IntIntTuple2Tuple2* payload_95 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_95))) = tuple_204;
    struct APat_ variant_95 = (struct APat_){.tag = Lit_, .Lit_ = payload_95};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_203;
    tuple_203.t0 = variant_95;
    tuple_203.t1 = tokens_65;
    tuple_203.t2 = errors_47;
    match_209 = tuple_203;
    goto end_match_797;
next_802:;
    if ((!(tokens_61))) goto next_803;
    if ((tokens_61->head.t0.tag != Ident_)) goto next_803;
    struct String ident_20 = (*(tokens_61->head.t0.Ident_));
    struct IntIntTuple2 loc_42 = tokens_61->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_66 = tokens_61->tail;
    struct StringIntIntTuple2Tuple2 tuple_206;
    tuple_206.t0 = ident_20;
    tuple_206.t1 = loc_42;
    struct StringIntIntTuple2Tuple2* payload_96 = (struct StringIntIntTuple2Tuple2*)malloc(sizeof(struct StringIntIntTuple2Tuple2));
    (*(((struct StringIntIntTuple2Tuple2*)payload_96))) = tuple_206;
    struct APat_ variant_96 = (struct APat_){.tag = Ident_1, .Ident_1 = payload_96};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_205;
    tuple_205.t0 = variant_96;
    tuple_205.t1 = tokens_66;
    tuple_205.t2 = errors_47;
    match_209 = tuple_205;
    goto end_match_797;
next_803:;
    if ((!(tokens_61))) goto next_804;
    if ((tokens_61->head.t0.tag != ParenL_)) goto next_804;
    struct IntIntTuple2 loc_43 = tokens_61->head.t1;
    if ((!(tokens_61->tail))) goto next_804;
    if ((tokens_61->tail->head.t0.tag != ParenR_)) goto next_804;
    struct Token_IntIntTuple2Tuple2List* tokens_67 = tokens_61->tail->tail;
    struct APat_ListIntIntTuple2Tuple2 tuple_208;
    tuple_208.t0 = NULL;
    tuple_208.t1 = loc_43;
    struct APat_ListIntIntTuple2Tuple2* payload_97 = (struct APat_ListIntIntTuple2Tuple2*)malloc(sizeof(struct APat_ListIntIntTuple2Tuple2));
    (*(((struct APat_ListIntIntTuple2Tuple2*)payload_97))) = tuple_208;
    struct APat_ variant_97 = (struct APat_){.tag = TupleLit_, .TupleLit_ = payload_97};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_207;
    tuple_207.t0 = variant_97;
    tuple_207.t1 = tokens_67;
    tuple_207.t2 = errors_47;
    match_209 = tuple_207;
    goto end_match_797;
next_804:;
    if ((!(tokens_61))) goto next_805;
    if ((tokens_61->head.t0.tag != ParenL_)) goto next_805;
    struct Token_IntIntTuple2Tuple2List* tokens_68 = tokens_61->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_209;
    tuple_209.t0 = tokens_68;
    tuple_209.t1 = errors_47;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_523 = parsePatParenBody_1(baseLoc_12, tuple_209);
    match_209 = call_523;
    goto end_match_797;
next_805:;
    if ((!(tokens_61))) goto next_806;
    if ((tokens_61->head.t0.tag != BracketL_)) goto next_806;
    struct IntIntTuple2 loc_44 = tokens_61->head.t1;
    if ((!(tokens_61->tail))) goto next_806;
    if ((tokens_61->tail->head.t0.tag != BracketR_)) goto next_806;
    struct Token_IntIntTuple2Tuple2List* tokens_69 = tokens_61->tail->tail;
    struct APat_ListIntIntTuple2Tuple2 tuple_211;
    tuple_211.t0 = NULL;
    tuple_211.t1 = loc_44;
    struct APat_ListIntIntTuple2Tuple2* payload_98 = (struct APat_ListIntIntTuple2Tuple2*)malloc(sizeof(struct APat_ListIntIntTuple2Tuple2));
    (*(((struct APat_ListIntIntTuple2Tuple2*)payload_98))) = tuple_211;
    struct APat_ variant_98 = (struct APat_){.tag = ListLit_, .ListLit_ = payload_98};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_210;
    tuple_210.t0 = variant_98;
    tuple_210.t1 = tokens_69;
    tuple_210.t2 = errors_47;
    match_209 = tuple_210;
    goto end_match_797;
next_806:;
    if ((!(tokens_61))) goto next_807;
    if ((tokens_61->head.t0.tag != BracketL_)) goto next_807;
    struct IntIntTuple2 loc_45 = tokens_61->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_70 = tokens_61->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_212;
    tuple_212.t0 = tokens_70;
    tuple_212.t1 = errors_47;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_524 = parsePatListBody_1(baseLoc_12, loc_45, tuple_212);
    match_209 = call_524;
    goto end_match_797;
next_807:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_213;
    tuple_213.t0 = tokens_61;
    tuple_213.t1 = errors_47;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_525 = parsePatError_1((struct String){.str = "NEVER: The token must be a pat", .len = 30}, tuple_213);
    match_209 = call_525;
    goto end_match_797;
next_808:;
end_match_797:;
    return match_209;
}

struct APat_StringIntIntTuple2Tuple3 {
    struct APat_ t0;
    struct String t1;
    struct IntIntTuple2 t2;
};

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatNav_1(struct IntIntTuple2 baseLoc_13, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_132) {
    struct Token_IntIntTuple2Tuple2List* tokens_71 = arg_132.t0;
    struct StringIntIntTuple2Tuple2List* errors_48 = arg_132.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_214;
    tuple_214.t0 = tokens_71;
    tuple_214.t1 = errors_48;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_526 = parsePatAtom_1(baseLoc_13, tuple_214);
    struct APat_ pat_17 = call_526.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_72 = call_526.t1;
    struct StringIntIntTuple2Tuple2List* errors_49 = call_526.t2;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_211;
    if ((!(tokens_72))) goto next_813;
    if ((tokens_72->head.t0.tag != Dot_)) goto next_813;
    struct IntIntTuple2 loc_46 = tokens_72->head.t1;
    if ((!(tokens_72->tail))) goto next_813;
    if ((tokens_72->tail->head.t0.tag != Ident_)) goto next_813;
    struct String ident_21 = (*(tokens_72->tail->head.t0.Ident_));
    struct Token_IntIntTuple2Tuple2List* tokens_73 = tokens_72->tail->tail;
    struct APat_StringIntIntTuple2Tuple3 tuple_216;
    tuple_216.t0 = pat_17;
    tuple_216.t1 = ident_21;
    tuple_216.t2 = loc_46;
    struct APat_StringIntIntTuple2Tuple3* payload_99 = (struct APat_StringIntIntTuple2Tuple3*)malloc(sizeof(struct APat_StringIntIntTuple2Tuple3));
    (*(((struct APat_StringIntIntTuple2Tuple3*)payload_99))) = tuple_216;
    struct APat_ variant_99 = (struct APat_){.tag = Nav_, .Nav_ = payload_99};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_215;
    tuple_215.t0 = variant_99;
    tuple_215.t1 = tokens_73;
    tuple_215.t2 = errors_49;
    match_211 = tuple_215;
    goto end_match_812;
next_813:;
    if ((!(tokens_72))) goto next_814;
    if ((tokens_72->head.t0.tag != Dot_)) goto next_814;
    struct Token_IntIntTuple2Tuple2List* tokens_74 = tokens_72->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_217;
    tuple_217.t0 = tokens_74;
    tuple_217.t1 = errors_49;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_527 = parsePatError_1((struct String){.str = "Expected identifier", .len = 19}, tuple_217);
    match_211 = call_527;
    goto end_match_812;
next_814:;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_218;
    tuple_218.t0 = pat_17;
    tuple_218.t1 = tokens_72;
    tuple_218.t2 = errors_49;
    match_211 = tuple_218;
    goto end_match_812;
next_815:;
end_match_812:;
    return match_211;
}

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_78(struct IntIntTuple2 argBaseLoc_, struct IntIntTuple2 baseLoc_14, struct APat_List* acc_18, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_133) {
    struct Token_IntIntTuple2Tuple2List* tokens_76 = arg_133.t0;
    struct StringIntIntTuple2Tuple2List* errors_51 = arg_133.t1;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_212;
    int match_213;
    int call_528 = nextInside_1(argBaseLoc_, tokens_76);
    if ((!(call_528))) goto next_818;
    int call_529 = leadsPat_1(tokens_76);
    match_213 = call_529;
    goto end_match_817;
next_818:;
    if (call_528) goto next_819;
    match_213 = 0;
    goto end_match_817;
next_819:;
    exit(1);
end_match_817:;
    if ((!(match_213))) goto next_820;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_219;
    tuple_219.t0 = tokens_76;
    tuple_219.t1 = errors_51;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_530 = parsePatNav_1(baseLoc_14, tuple_219);
    struct APat_ expr_10 = call_530.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_77 = call_530.t1;
    struct StringIntIntTuple2Tuple2List* errors_52 = call_530.t2;
    struct APat_List* list_69 = (struct APat_List*)malloc(sizeof(struct APat_List));
    list_69->head = expr_10;
    list_69->tail = acc_18;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_220;
    tuple_220.t0 = tokens_77;
    tuple_220.t1 = errors_52;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_531 = go_78(argBaseLoc_, baseLoc_14, list_69, tuple_220);
    match_212 = call_531;
    goto end_match_816;
next_820:;
    if (match_213) goto next_821;
    struct APat_List* call_532 = listRev_4(acc_18);
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_221;
    tuple_221.t0 = call_532;
    tuple_221.t1 = tokens_76;
    tuple_221.t2 = errors_51;
    match_212 = tuple_221;
    goto end_match_816;
next_821:;
    exit(1);
end_match_816:;
    return match_212;
}

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatCallArgs_1(struct IntIntTuple2 baseLoc_14, struct IntIntTuple2 calleeLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_134) {
    struct Token_IntIntTuple2Tuple2List* tokens_75 = arg_134.t0;
    struct StringIntIntTuple2Tuple2List* errors_50 = arg_134.t1;
    struct IntIntTuple2 call_533 = locMax_(baseLoc_14, calleeLoc_);
    struct IntIntTuple2 call_534 = locAddX_(1, call_533);
    struct IntIntTuple2 argBaseLoc_ = call_534;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_222;
    tuple_222.t0 = tokens_75;
    tuple_222.t1 = errors_50;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_535 = go_78(argBaseLoc_, baseLoc_14, NULL, tuple_222);
    return call_535;
}

struct APat_APat_ListIntIntTuple2Tuple3 {
    struct APat_ t0;
    struct APat_List* t1;
    struct IntIntTuple2 t2;
};

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatCall_1(struct IntIntTuple2 baseLoc_15, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_135) {
    struct Token_IntIntTuple2Tuple2List* tokens_78 = arg_135.t0;
    struct StringIntIntTuple2Tuple2List* errors_53 = arg_135.t1;
    struct IntIntTuple2 call_536 = nextLoc_1(tokens_78);
    struct IntIntTuple2 calleeLoc_1 = call_536;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_223;
    tuple_223.t0 = tokens_78;
    tuple_223.t1 = errors_53;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_537 = parsePatNav_1(baseLoc_15, tuple_223);
    struct APat_ callee_5 = call_537.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_79 = call_537.t1;
    struct StringIntIntTuple2Tuple2List* errors_54 = call_537.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_224;
    tuple_224.t0 = tokens_79;
    tuple_224.t1 = errors_54;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_538 = parsePatCallArgs_1(baseLoc_15, calleeLoc_1, tuple_224);
    struct APat_List* args_6 = call_538.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_80 = call_538.t1;
    struct StringIntIntTuple2Tuple2List* errors_55 = call_538.t2;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_214;
    if ((!((!(args_6))))) goto next_823;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_225;
    tuple_225.t0 = callee_5;
    tuple_225.t1 = tokens_80;
    tuple_225.t2 = errors_55;
    match_214 = tuple_225;
    goto end_match_822;
next_823:;
    struct APat_APat_ListIntIntTuple2Tuple3 tuple_227;
    tuple_227.t0 = callee_5;
    tuple_227.t1 = args_6;
    tuple_227.t2 = calleeLoc_1;
    struct APat_APat_ListIntIntTuple2Tuple3* payload_100 = (struct APat_APat_ListIntIntTuple2Tuple3*)malloc(sizeof(struct APat_APat_ListIntIntTuple2Tuple3));
    (*(((struct APat_APat_ListIntIntTuple2Tuple3*)payload_100))) = tuple_227;
    struct APat_ variant_100 = (struct APat_){.tag = Call_, .Call_ = payload_100};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_226;
    tuple_226.t0 = variant_100;
    tuple_226.t1 = tokens_80;
    tuple_226.t2 = errors_55;
    match_214 = tuple_226;
    goto end_match_822;
next_824:;
end_match_822:;
    return match_214;
}

struct APat_APat_IntIntTuple2Tuple3 {
    struct APat_ t0;
    struct APat_ t1;
    struct IntIntTuple2 t2;
};

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatCons_1(struct IntIntTuple2 baseLoc_16, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_136) {
    struct Token_IntIntTuple2Tuple2List* tokens_81 = arg_136.t0;
    struct StringIntIntTuple2Tuple2List* errors_56 = arg_136.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_228;
    tuple_228.t0 = tokens_81;
    tuple_228.t1 = errors_56;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_539 = parsePatCall_1(baseLoc_16, tuple_228);
    struct APat_ head_2 = call_539.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_82 = call_539.t1;
    struct StringIntIntTuple2Tuple2List* errors_57 = call_539.t2;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_215;
    if ((!(tokens_82))) goto next_826;
    if ((tokens_82->head.t0.tag != ColonColon_)) goto next_826;
    struct IntIntTuple2 loc_47 = tokens_82->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_83 = tokens_82->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_229;
    tuple_229.t0 = tokens_83;
    tuple_229.t1 = errors_57;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_540 = parsePatCons_1(baseLoc_16, tuple_229);
    struct APat_ tail_2 = call_540.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_84 = call_540.t1;
    struct StringIntIntTuple2Tuple2List* errors_58 = call_540.t2;
    struct APat_APat_IntIntTuple2Tuple3 tuple_231;
    tuple_231.t0 = head_2;
    tuple_231.t1 = tail_2;
    tuple_231.t2 = loc_47;
    struct APat_APat_IntIntTuple2Tuple3* payload_101 = (struct APat_APat_IntIntTuple2Tuple3*)malloc(sizeof(struct APat_APat_IntIntTuple2Tuple3));
    (*(((struct APat_APat_IntIntTuple2Tuple3*)payload_101))) = tuple_231;
    struct APat_ variant_101 = (struct APat_){.tag = Cons_2, .Cons_2 = payload_101};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_230;
    tuple_230.t0 = variant_101;
    tuple_230.t1 = tokens_84;
    tuple_230.t2 = errors_58;
    match_215 = tuple_230;
    goto end_match_825;
next_826:;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_232;
    tuple_232.t0 = head_2;
    tuple_232.t1 = tokens_82;
    tuple_232.t2 = errors_57;
    match_215 = tuple_232;
    goto end_match_825;
next_827:;
end_match_825:;
    return match_215;
}

struct APat_ATy_IntIntTuple2Tuple3 {
    struct APat_ t0;
    struct ATy_ t1;
    struct IntIntTuple2 t2;
};

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatAnno_1(struct IntIntTuple2 baseLoc_17, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_137) {
    struct Token_IntIntTuple2Tuple2List* tokens_85 = arg_137.t0;
    struct StringIntIntTuple2Tuple2List* errors_59 = arg_137.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_233;
    tuple_233.t0 = tokens_85;
    tuple_233.t1 = errors_59;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_541 = parsePatCons_1(baseLoc_17, tuple_233);
    struct APat_ pat_18 = call_541.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_86 = call_541.t1;
    struct StringIntIntTuple2Tuple2List* errors_60 = call_541.t2;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_216;
    if ((!(tokens_86))) goto next_829;
    if ((tokens_86->head.t0.tag != Colon_)) goto next_829;
    struct IntIntTuple2 loc_48 = tokens_86->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_87 = tokens_86->tail;
    struct IntIntTuple2 call_542 = nextLoc_1(tokens_87);
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_234;
    tuple_234.t0 = tokens_87;
    tuple_234.t1 = errors_60;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_543 = parseTy_1(call_542, tuple_234);
    struct ATy_ ty_50 = call_543.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_88 = call_543.t1;
    struct StringIntIntTuple2Tuple2List* errors_61 = call_543.t2;
    struct APat_ATy_IntIntTuple2Tuple3 tuple_236;
    tuple_236.t0 = pat_18;
    tuple_236.t1 = ty_50;
    tuple_236.t2 = loc_48;
    struct APat_ATy_IntIntTuple2Tuple3* payload_102 = (struct APat_ATy_IntIntTuple2Tuple3*)malloc(sizeof(struct APat_ATy_IntIntTuple2Tuple3));
    (*(((struct APat_ATy_IntIntTuple2Tuple3*)payload_102))) = tuple_236;
    struct APat_ variant_102 = (struct APat_){.tag = Anno_, .Anno_ = payload_102};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_235;
    tuple_235.t0 = variant_102;
    tuple_235.t1 = tokens_88;
    tuple_235.t2 = errors_61;
    match_216 = tuple_235;
    goto end_match_828;
next_829:;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_237;
    tuple_237.t0 = pat_18;
    tuple_237.t1 = tokens_86;
    tuple_237.t2 = errors_60;
    match_216 = tuple_237;
    goto end_match_828;
next_830:;
end_match_828:;
    return match_216;
}

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_81(struct IntIntTuple2 baseLoc_18, struct APat_List* acc_19, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_138) {
    struct Token_IntIntTuple2Tuple2List* tokens_90 = arg_138.t0;
    struct StringIntIntTuple2Tuple2List* errors_63 = arg_138.t1;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_217;
    if ((!(tokens_90))) goto next_832;
    if ((tokens_90->head.t0.tag != Comma_)) goto next_832;
    struct Token_IntIntTuple2Tuple2List* tokens_91 = tokens_90->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_238;
    tuple_238.t0 = tokens_91;
    tuple_238.t1 = errors_63;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_544 = parsePatAnno_1(baseLoc_18, tuple_238);
    struct APat_ second_3 = call_544.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_92 = call_544.t1;
    struct StringIntIntTuple2Tuple2List* errors_64 = call_544.t2;
    struct APat_List* list_70 = (struct APat_List*)malloc(sizeof(struct APat_List));
    list_70->head = second_3;
    list_70->tail = acc_19;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_239;
    tuple_239.t0 = tokens_92;
    tuple_239.t1 = errors_64;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_545 = go_81(baseLoc_18, list_70, tuple_239);
    match_217 = call_545;
    goto end_match_831;
next_832:;
    struct APat_List* call_546 = listRev_4(acc_19);
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_240;
    tuple_240.t0 = call_546;
    tuple_240.t1 = tokens_90;
    tuple_240.t2 = errors_63;
    match_217 = tuple_240;
    goto end_match_831;
next_833:;
end_match_831:;
    return match_217;
}

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatTuple_1(struct IntIntTuple2 baseLoc_18, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_139) {
    struct Token_IntIntTuple2Tuple2List* tokens_89 = arg_139.t0;
    struct StringIntIntTuple2Tuple2List* errors_62 = arg_139.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_241;
    tuple_241.t0 = tokens_89;
    tuple_241.t1 = errors_62;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_547 = parsePatAnno_1(baseLoc_18, tuple_241);
    struct APat_ itemPat_1 = call_547.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_93 = call_547.t1;
    struct StringIntIntTuple2Tuple2List* errors_65 = call_547.t2;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_218;
    if ((!(tokens_93))) goto next_835;
    if ((tokens_93->head.t0.tag != Comma_)) goto next_835;
    struct IntIntTuple2 loc_49 = tokens_93->head.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_242;
    tuple_242.t0 = tokens_93;
    tuple_242.t1 = errors_65;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_548 = go_81(baseLoc_18, NULL, tuple_242);
    struct APat_List* itemPats_2 = call_548.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_94 = call_548.t1;
    struct StringIntIntTuple2Tuple2List* errors_66 = call_548.t2;
    struct APat_List* list_71 = (struct APat_List*)malloc(sizeof(struct APat_List));
    list_71->head = itemPat_1;
    list_71->tail = itemPats_2;
    struct APat_ListIntIntTuple2Tuple2 tuple_244;
    tuple_244.t0 = list_71;
    tuple_244.t1 = loc_49;
    struct APat_ListIntIntTuple2Tuple2* payload_103 = (struct APat_ListIntIntTuple2Tuple2*)malloc(sizeof(struct APat_ListIntIntTuple2Tuple2));
    (*(((struct APat_ListIntIntTuple2Tuple2*)payload_103))) = tuple_244;
    struct APat_ variant_103 = (struct APat_){.tag = TupleLit_, .TupleLit_ = payload_103};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_243;
    tuple_243.t0 = variant_103;
    tuple_243.t1 = tokens_94;
    tuple_243.t2 = errors_66;
    match_218 = tuple_243;
    goto end_match_834;
next_835:;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_245;
    tuple_245.t0 = itemPat_1;
    tuple_245.t1 = tokens_93;
    tuple_245.t2 = errors_65;
    match_218 = tuple_245;
    goto end_match_834;
next_836:;
end_match_834:;
    return match_218;
}

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatAs_1(struct IntIntTuple2 baseLoc_19, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_140) {
    struct Token_IntIntTuple2Tuple2List* tokens_95 = arg_140.t0;
    struct StringIntIntTuple2Tuple2List* errors_67 = arg_140.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_246;
    tuple_246.t0 = tokens_95;
    tuple_246.t1 = errors_67;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_549 = parsePatTuple_1(baseLoc_19, tuple_246);
    struct APat_ pat_19 = call_549.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_96 = call_549.t1;
    struct StringIntIntTuple2Tuple2List* errors_68 = call_549.t2;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_219;
    if ((!(tokens_96))) goto next_838;
    if ((tokens_96->head.t0.tag != As_)) goto next_838;
    struct IntIntTuple2 loc_50 = tokens_96->head.t1;
    if ((!(tokens_96->tail))) goto next_838;
    if ((tokens_96->tail->head.t0.tag != Ident_)) goto next_838;
    struct String ident_22 = (*(tokens_96->tail->head.t0.Ident_));
    struct Token_IntIntTuple2Tuple2List* tokens_97 = tokens_96->tail->tail;
    struct APat_StringIntIntTuple2Tuple3 tuple_248;
    tuple_248.t0 = pat_19;
    tuple_248.t1 = ident_22;
    tuple_248.t2 = loc_50;
    struct APat_StringIntIntTuple2Tuple3* payload_104 = (struct APat_StringIntIntTuple2Tuple3*)malloc(sizeof(struct APat_StringIntIntTuple2Tuple3));
    (*(((struct APat_StringIntIntTuple2Tuple3*)payload_104))) = tuple_248;
    struct APat_ variant_104 = (struct APat_){.tag = As_1, .As_1 = payload_104};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_247;
    tuple_247.t0 = variant_104;
    tuple_247.t1 = tokens_97;
    tuple_247.t2 = errors_68;
    match_219 = tuple_247;
    goto end_match_837;
next_838:;
    if ((!(tokens_96))) goto next_839;
    if ((tokens_96->head.t0.tag != As_)) goto next_839;
    struct Token_IntIntTuple2Tuple2List* tokens_98 = tokens_96->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_249;
    tuple_249.t0 = tokens_98;
    tuple_249.t1 = errors_68;
    struct StringIntIntTuple2Tuple2List* call_550 = parseNewError_1((struct String){.str = "Expected an identifier", .len = 22}, tuple_249);
    struct StringIntIntTuple2Tuple2List* errors_69 = call_550;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_250;
    tuple_250.t0 = pat_19;
    tuple_250.t1 = tokens_98;
    tuple_250.t2 = errors_69;
    match_219 = tuple_250;
    goto end_match_837;
next_839:;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_251;
    tuple_251.t0 = pat_19;
    tuple_251.t1 = tokens_96;
    tuple_251.t2 = errors_68;
    match_219 = tuple_251;
    goto end_match_837;
next_840:;
end_match_837:;
    return match_219;
}

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatOr_1(struct IntIntTuple2 baseLoc_20, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_141) {
    struct Token_IntIntTuple2Tuple2List* tokens_99 = arg_141.t0;
    struct StringIntIntTuple2Tuple2List* errors_70 = arg_141.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_252;
    tuple_252.t0 = tokens_99;
    tuple_252.t1 = errors_70;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_551 = parsePatAs_1(baseLoc_20, tuple_252);
    struct APat_ lPat_ = call_551.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_100 = call_551.t1;
    struct StringIntIntTuple2Tuple2List* errors_71 = call_551.t2;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_220;
    if ((!(tokens_100))) goto next_842;
    if ((tokens_100->head.t0.tag != Pipe_)) goto next_842;
    struct IntIntTuple2 loc_51 = tokens_100->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_101 = tokens_100->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_253;
    tuple_253.t0 = tokens_101;
    tuple_253.t1 = errors_71;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_552 = parsePatOr_1(baseLoc_20, tuple_253);
    struct APat_ rPat_ = call_552.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_102 = call_552.t1;
    struct StringIntIntTuple2Tuple2List* errors_72 = call_552.t2;
    struct APat_APat_IntIntTuple2Tuple3 tuple_255;
    tuple_255.t0 = lPat_;
    tuple_255.t1 = rPat_;
    tuple_255.t2 = loc_51;
    struct APat_APat_IntIntTuple2Tuple3* payload_105 = (struct APat_APat_IntIntTuple2Tuple3*)malloc(sizeof(struct APat_APat_IntIntTuple2Tuple3));
    (*(((struct APat_APat_IntIntTuple2Tuple3*)payload_105))) = tuple_255;
    struct APat_ variant_105 = (struct APat_){.tag = Or_2, .Or_2 = payload_105};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_254;
    tuple_254.t0 = variant_105;
    tuple_254.t1 = tokens_102;
    tuple_254.t2 = errors_72;
    match_220 = tuple_254;
    goto end_match_841;
next_842:;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_256;
    tuple_256.t0 = lPat_;
    tuple_256.t1 = tokens_100;
    tuple_256.t2 = errors_71;
    match_220 = tuple_256;
    goto end_match_841;
next_843:;
end_match_841:;
    return match_220;
}

struct StringAPat_ListIntIntTuple2Tuple3 {
    struct String t0;
    struct APat_List* t1;
    struct IntIntTuple2 t2;
};

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatLet_1(struct IntIntTuple2 baseLoc_21, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_142) {
    struct Token_IntIntTuple2Tuple2List* tokens_103 = arg_142.t0;
    struct StringIntIntTuple2Tuple2List* errors_73 = arg_142.t1;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_221;
    if ((!(tokens_103))) goto next_845;
    if ((tokens_103->head.t0.tag != Ident_)) goto next_845;
    struct String callee_6 = (*(tokens_103->head.t0.Ident_));
    struct IntIntTuple2 calleeLoc_2 = tokens_103->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_104 = tokens_103->tail;
    int match_222;
    int call_553 = locInside_(baseLoc_21, calleeLoc_2);
    if ((!(call_553))) goto next_848;
    int call_554 = leadsPat_1(tokens_104);
    match_222 = call_554;
    goto end_match_847;
next_848:;
    if (call_553) goto next_849;
    match_222 = 0;
    goto end_match_847;
next_849:;
    exit(1);
end_match_847:;
    if ((!(match_222))) goto next_845;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_257;
    tuple_257.t0 = tokens_104;
    tuple_257.t1 = errors_73;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_555 = parsePatCallArgs_1(baseLoc_21, calleeLoc_2, tuple_257);
    struct APat_List* args_7 = call_555.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_105 = call_555.t1;
    struct StringIntIntTuple2Tuple2List* errors_74 = call_555.t2;
    struct StringAPat_ListIntIntTuple2Tuple3 tuple_258;
    tuple_258.t0 = callee_6;
    tuple_258.t1 = args_7;
    tuple_258.t2 = calleeLoc_2;
    struct StringAPat_ListIntIntTuple2Tuple3* payload_106 = (struct StringAPat_ListIntIntTuple2Tuple3*)malloc(sizeof(struct StringAPat_ListIntIntTuple2Tuple3));
    (*(((struct StringAPat_ListIntIntTuple2Tuple3*)payload_106))) = tuple_258;
    struct APat_ variant_106 = (struct APat_){.tag = Fun_2, .Fun_2 = payload_106};
    struct APat_ pat_20 = variant_106;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_223;
    if ((!(tokens_105))) goto next_851;
    if ((tokens_105->head.t0.tag != Colon_)) goto next_851;
    struct IntIntTuple2 loc_52 = tokens_105->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_106 = tokens_105->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_259;
    tuple_259.t0 = tokens_106;
    tuple_259.t1 = errors_74;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_556 = parseTy_1(baseLoc_21, tuple_259);
    struct ATy_ ty_51 = call_556.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_107 = call_556.t1;
    struct StringIntIntTuple2Tuple2List* errors_75 = call_556.t2;
    struct APat_ATy_IntIntTuple2Tuple3 tuple_261;
    tuple_261.t0 = pat_20;
    tuple_261.t1 = ty_51;
    tuple_261.t2 = loc_52;
    struct APat_ATy_IntIntTuple2Tuple3* payload_107 = (struct APat_ATy_IntIntTuple2Tuple3*)malloc(sizeof(struct APat_ATy_IntIntTuple2Tuple3));
    (*(((struct APat_ATy_IntIntTuple2Tuple3*)payload_107))) = tuple_261;
    struct APat_ variant_107 = (struct APat_){.tag = Anno_, .Anno_ = payload_107};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_260;
    tuple_260.t0 = variant_107;
    tuple_260.t1 = tokens_107;
    tuple_260.t2 = errors_75;
    match_223 = tuple_260;
    goto end_match_850;
next_851:;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_262;
    tuple_262.t0 = pat_20;
    tuple_262.t1 = tokens_105;
    tuple_262.t2 = errors_74;
    match_223 = tuple_262;
    goto end_match_850;
next_852:;
end_match_850:;
    match_221 = match_223;
    goto end_match_844;
next_845:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_263;
    tuple_263.t0 = tokens_103;
    tuple_263.t1 = errors_73;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_557 = parsePat_1(baseLoc_21, tuple_263);
    match_221 = call_557;
    goto end_match_844;
next_846:;
end_match_844:;
    return match_221;
}

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePat_1(struct IntIntTuple2 baseLoc_22, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_143) {
    struct Token_IntIntTuple2Tuple2List* tokens_108 = arg_143.t0;
    struct StringIntIntTuple2Tuple2List* errors_76 = arg_143.t1;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_224;
    int match_225;
    int call_558 = nextInside_1(baseLoc_22, tokens_108);
    if ((!(call_558))) goto next_855;
    int call_559 = leadsPat_1(tokens_108);
    match_225 = call_559;
    goto end_match_854;
next_855:;
    if (call_558) goto next_856;
    match_225 = 0;
    goto end_match_854;
next_856:;
    exit(1);
end_match_854:;
    if (match_225) goto next_857;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_264;
    tuple_264.t0 = tokens_108;
    tuple_264.t1 = errors_76;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_560 = parsePatError_1((struct String){.str = "Expected a pattern", .len = 18}, tuple_264);
    match_224 = call_560;
    goto end_match_853;
next_857:;
    if ((!(match_225))) goto next_858;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_265;
    tuple_265.t0 = tokens_108;
    tuple_265.t1 = errors_76;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_561 = parsePatOr_1(baseLoc_22, tuple_265);
    match_224 = call_561;
    goto end_match_853;
next_858:;
    exit(1);
end_match_853:;
    return match_224;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseRange_1(struct IntIntTuple2 baseLoc_23, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_144) {
    struct Token_IntIntTuple2Tuple2List* tokens_109 = arg_144.t0;
    struct StringIntIntTuple2Tuple2List* errors_77 = arg_144.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_266;
    tuple_266.t0 = tokens_109;
    tuple_266.t1 = errors_77;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_562 = parseExpr_1(baseLoc_23, tuple_266);
    struct AExpr_ l_17 = call_562.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_110 = call_562.t1;
    struct StringIntIntTuple2Tuple2List* errors_78 = call_562.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_226;
    if ((!(tokens_110))) goto next_860;
    if ((tokens_110->head.t0.tag != DotDot_)) goto next_860;
    struct IntIntTuple2 loc_53 = tokens_110->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_111 = tokens_110->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_267;
    tuple_267.t0 = tokens_111;
    tuple_267.t1 = errors_78;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_563 = parseExpr_1(baseLoc_23, tuple_267);
    struct AExpr_ r_30 = call_563.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_112 = call_563.t1;
    struct StringIntIntTuple2Tuple2List* errors_79 = call_563.t2;
    struct AExpr_List* list_73 = (struct AExpr_List*)malloc(sizeof(struct AExpr_List));
    list_73->head = r_30;
    list_73->tail = NULL;
    struct AExpr_List* list_72 = (struct AExpr_List*)malloc(sizeof(struct AExpr_List));
    list_72->head = l_17;
    list_72->tail = list_73;
    struct AExpr_ListIntIntTuple2Tuple2 tuple_269;
    tuple_269.t0 = list_72;
    tuple_269.t1 = loc_53;
    struct AExpr_ListIntIntTuple2Tuple2* payload_108 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_108))) = tuple_269;
    struct AExpr_ variant_108 = (struct AExpr_){.tag = Range_, .Range_ = payload_108};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_268;
    tuple_268.t0 = variant_108;
    tuple_268.t1 = tokens_112;
    tuple_268.t2 = errors_79;
    match_226 = tuple_268;
    goto end_match_859;
next_860:;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_270;
    tuple_270.t0 = l_17;
    tuple_270.t1 = tokens_110;
    tuple_270.t2 = errors_78;
    match_226 = tuple_270;
    goto end_match_859;
next_861:;
end_match_859:;
    return match_226;
}

struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct AExpr_List* t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseList_1(struct IntIntTuple2 baseLoc_24, struct IntIntTuple2 bracketLoc_1, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_145) {
    struct Token_IntIntTuple2Tuple2List* tokens_113 = arg_145.t0;
    struct StringIntIntTuple2Tuple2List* errors_80 = arg_145.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_271;
    tuple_271.t0 = tokens_113;
    tuple_271.t1 = errors_80;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_564 = parseStmts_1(baseLoc_24, tuple_271);
    struct AExpr_List* items_6 = call_564.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_114 = call_564.t1;
    struct StringIntIntTuple2Tuple2List* errors_81 = call_564.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 match_227;
    if ((!(tokens_114))) goto next_863;
    if ((tokens_114->head.t0.tag != BracketR_)) goto next_863;
    struct Token_IntIntTuple2Tuple2List* tokens_116 = tokens_114->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_272;
    tuple_272.t0 = tokens_116;
    tuple_272.t1 = errors_81;
    match_227 = tuple_272;
    goto end_match_862;
next_863:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_273;
    tuple_273.t0 = tokens_114;
    tuple_273.t1 = errors_81;
    struct StringIntIntTuple2Tuple2List* call_565 = parseNewError_1((struct String){.str = "Expected \']\'", .len = 12}, tuple_273);
    struct StringIntIntTuple2Tuple2List* errors_83 = call_565;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_274;
    tuple_274.t0 = tokens_114;
    tuple_274.t1 = errors_83;
    match_227 = tuple_274;
    goto end_match_862;
next_864:;
end_match_862:;
    struct Token_IntIntTuple2Tuple2List* tokens_115 = match_227.t0;
    struct StringIntIntTuple2Tuple2List* errors_82 = match_227.t1;
    struct AExpr_ListIntIntTuple2Tuple2 tuple_276;
    tuple_276.t0 = items_6;
    tuple_276.t1 = bracketLoc_1;
    struct AExpr_ListIntIntTuple2Tuple2* payload_109 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_109))) = tuple_276;
    struct AExpr_ variant_109 = (struct AExpr_){.tag = ListLit_1, .ListLit_1 = payload_109};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_275;
    tuple_275.t0 = variant_109;
    tuple_275.t1 = tokens_115;
    tuple_275.t2 = errors_82;
    return tuple_275;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseThenClause_1(struct IntIntTuple2 baseLoc_25, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_146) {
    struct Token_IntIntTuple2Tuple2List* tokens_117 = arg_146.t0;
    struct StringIntIntTuple2Tuple2List* errors_84 = arg_146.t1;
    struct IntIntTuple2 call_566 = locAddX_(1, baseLoc_25);
    struct IntIntTuple2 innerBaseLoc_ = call_566;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_228;
    if ((!(tokens_117))) goto next_866;
    if ((tokens_117->head.t0.tag != Then_)) goto next_866;
    struct IntIntTuple2 thenLoc_ = tokens_117->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_118 = tokens_117->tail;
    int call_567 = locInside_(baseLoc_25, thenLoc_);
    if ((!(call_567))) goto next_866;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_277;
    tuple_277.t0 = tokens_118;
    tuple_277.t1 = errors_84;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_568 = parseSemi_1(innerBaseLoc_, thenLoc_, tuple_277);
    match_228 = call_568;
    goto end_match_865;
next_866:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_278;
    tuple_278.t0 = tokens_117;
    tuple_278.t1 = errors_84;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_569 = parseExprError_1((struct String){.str = "Expected \'then\'", .len = 15}, tuple_278);
    match_228 = call_569;
    goto end_match_865;
next_867:;
end_match_865:;
    return match_228;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseElseClause_1(struct IntIntTuple2 baseLoc_26, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_147) {
    struct Token_IntIntTuple2Tuple2List* tokens_119 = arg_147.t0;
    struct StringIntIntTuple2Tuple2List* errors_85 = arg_147.t1;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_229;
    if ((!(tokens_119))) goto next_869;
    if ((tokens_119->head.t0.tag != Else_)) goto next_869;
    struct IntIntTuple2 elseLoc_ = tokens_119->head.t1;
    if ((!(tokens_119->tail))) goto next_869;
    if ((tokens_119->tail->head.t0.tag != If_)) goto next_869;
    struct IntIntTuple2 nextIfLoc_ = tokens_119->tail->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_120 = tokens_119->tail->tail;
    int match_230;
    int call_570 = locInside_(baseLoc_26, elseLoc_);
    if ((!(call_570))) goto next_873;
    int call_571 = locIsSameRow_(elseLoc_, nextIfLoc_);
    match_230 = call_571;
    goto end_match_872;
next_873:;
    if (call_570) goto next_874;
    match_230 = 0;
    goto end_match_872;
next_874:;
    exit(1);
end_match_872:;
    if ((!(match_230))) goto next_869;
    struct Token_IntIntTuple2Tuple2 tuple_280;
    tuple_280.t0 = (struct Token_){.tag = If_};
    tuple_280.t1 = elseLoc_;
    struct Token_IntIntTuple2Tuple2List* list_74 = (struct Token_IntIntTuple2Tuple2List*)malloc(sizeof(struct Token_IntIntTuple2Tuple2List));
    list_74->head = tuple_280;
    list_74->tail = tokens_120;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_279;
    tuple_279.t0 = list_74;
    tuple_279.t1 = errors_85;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_572 = parseExpr_1(baseLoc_26, tuple_279);
    match_229 = call_572;
    goto end_match_868;
next_869:;
    if ((!(tokens_119))) goto next_870;
    if ((tokens_119->head.t0.tag != Else_)) goto next_870;
    struct IntIntTuple2 elseLoc_1 = tokens_119->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_121 = tokens_119->tail;
    int call_573 = locInside_(baseLoc_26, elseLoc_1);
    if ((!(call_573))) goto next_870;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_281;
    tuple_281.t0 = tokens_121;
    tuple_281.t1 = errors_85;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_574 = parseSemi_1(baseLoc_26, elseLoc_1, tuple_281);
    match_229 = call_574;
    goto end_match_868;
next_870:;
    struct IntIntTuple2* payload_110 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_110))) = baseLoc_26;
    struct AExpr_ variant_110 = (struct AExpr_){.tag = Missing_2, .Missing_2 = payload_110};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_282;
    tuple_282.t0 = variant_110;
    tuple_282.t1 = tokens_119;
    tuple_282.t2 = errors_85;
    match_229 = tuple_282;
    goto end_match_868;
next_871:;
end_match_868:;
    return match_229;
}

struct AExpr_AExpr_AExpr_IntIntTuple2Tuple4 {
    struct AExpr_ t0;
    struct AExpr_ t1;
    struct AExpr_ t2;
    struct IntIntTuple2 t3;
};

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseIf_1(struct IntIntTuple2 ifLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_148) {
    struct Token_IntIntTuple2Tuple2List* tokens_122 = arg_148.t0;
    struct StringIntIntTuple2Tuple2List* errors_86 = arg_148.t1;
    struct IntIntTuple2 call_575 = locAddX_(1, ifLoc_);
    struct IntIntTuple2 innerBaseLoc_1 = call_575;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_283;
    tuple_283.t0 = tokens_122;
    tuple_283.t1 = errors_86;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_576 = parseExpr_1(innerBaseLoc_1, tuple_283);
    struct AExpr_ cond_1 = call_576.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_123 = call_576.t1;
    struct StringIntIntTuple2Tuple2List* errors_87 = call_576.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_284;
    tuple_284.t0 = tokens_123;
    tuple_284.t1 = errors_87;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_577 = parseThenClause_1(ifLoc_, tuple_284);
    struct AExpr_ body_9 = call_577.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_124 = call_577.t1;
    struct StringIntIntTuple2Tuple2List* errors_88 = call_577.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_285;
    tuple_285.t0 = tokens_124;
    tuple_285.t1 = errors_88;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_578 = parseElseClause_1(ifLoc_, tuple_285);
    struct AExpr_ alt_1 = call_578.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_125 = call_578.t1;
    struct StringIntIntTuple2Tuple2List* errors_89 = call_578.t2;
    struct AExpr_AExpr_AExpr_IntIntTuple2Tuple4 tuple_287;
    tuple_287.t0 = cond_1;
    tuple_287.t1 = body_9;
    tuple_287.t2 = alt_1;
    tuple_287.t3 = ifLoc_;
    struct AExpr_AExpr_AExpr_IntIntTuple2Tuple4* payload_111 = (struct AExpr_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct AExpr_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct AExpr_AExpr_AExpr_IntIntTuple2Tuple4*)payload_111))) = tuple_287;
    struct AExpr_ variant_111 = (struct AExpr_){.tag = If_1, .If_1 = payload_111};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_286;
    tuple_286.t0 = variant_111;
    tuple_286.t1 = tokens_125;
    tuple_286.t2 = errors_89;
    return tuple_286;
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

struct AArm_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseMatchArm_1(struct IntIntTuple2 matchLoc_, struct IntIntTuple2 armLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_149) {
    struct Token_IntIntTuple2Tuple2List* tokens_126 = arg_149.t0;
    struct StringIntIntTuple2Tuple2List* errors_90 = arg_149.t1;
    struct IntIntTuple2 call_579 = locAddX_(1, matchLoc_);
    struct IntIntTuple2 innerBaseLoc_2 = call_579;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_288;
    tuple_288.t0 = tokens_126;
    tuple_288.t1 = errors_90;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_580 = parsePat_1(innerBaseLoc_2, tuple_288);
    struct APat_ pat_21 = call_580.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_127 = call_580.t1;
    struct StringIntIntTuple2Tuple2List* errors_91 = call_580.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_231;
    if ((!(tokens_127))) goto next_876;
    if ((tokens_127->head.t0.tag != When_)) goto next_876;
    struct Token_IntIntTuple2Tuple2List* tokens_129 = tokens_127->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_289;
    tuple_289.t0 = tokens_129;
    tuple_289.t1 = errors_91;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_581 = parseExpr_1(innerBaseLoc_2, tuple_289);
    match_231 = call_581;
    goto end_match_875;
next_876:;
    struct IntIntTuple2 call_582 = nextLoc_1(tokens_127);
    struct IntIntTuple2* payload_112 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_112))) = call_582;
    struct AExpr_ variant_112 = (struct AExpr_){.tag = Missing_2, .Missing_2 = payload_112};
    struct AExpr_ guard_3 = variant_112;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_290;
    tuple_290.t0 = guard_3;
    tuple_290.t1 = tokens_127;
    tuple_290.t2 = errors_91;
    match_231 = tuple_290;
    goto end_match_875;
next_877:;
end_match_875:;
    struct AExpr_ guard_2 = match_231.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_128 = match_231.t1;
    struct StringIntIntTuple2Tuple2List* errors_92 = match_231.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_232;
    if ((!(tokens_128))) goto next_879;
    if ((tokens_128->head.t0.tag != Arrow_)) goto next_879;
    struct IntIntTuple2 arrowLoc_ = tokens_128->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_131 = tokens_128->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_291;
    tuple_291.t0 = tokens_131;
    tuple_291.t1 = errors_92;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_583 = parseSemi_1(matchLoc_, arrowLoc_, tuple_291);
    match_232 = call_583;
    goto end_match_878;
next_879:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_292;
    tuple_292.t0 = tokens_128;
    tuple_292.t1 = errors_92;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_584 = parseExprError_1((struct String){.str = "Expected \'->\'", .len = 13}, tuple_292);
    match_232 = call_584;
    goto end_match_878;
next_880:;
end_match_878:;
    struct AExpr_ body_10 = match_232.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_130 = match_232.t1;
    struct StringIntIntTuple2Tuple2List* errors_93 = match_232.t2;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4 tuple_294;
    tuple_294.t0 = pat_21;
    tuple_294.t1 = guard_2;
    tuple_294.t2 = body_10;
    tuple_294.t3 = armLoc_;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4* payload_113 = (struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct APat_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)payload_113))) = tuple_294;
    struct AArm_ variant_113 = (struct AArm_){.tag = AArm_, .AArm_ = payload_113};
    struct AArm_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_293;
    tuple_293.t0 = variant_113;
    tuple_293.t1 = tokens_130;
    tuple_293.t2 = errors_93;
    return tuple_293;
}

struct AArm_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct AArm_List* t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct AArm_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_87(struct IntIntTuple2 matchLoc_1, struct AArm_List* acc_20, struct IntIntTuple2 armLoc_2, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_150) {
    struct Token_IntIntTuple2Tuple2List* tokens_137 = arg_150.t0;
    struct StringIntIntTuple2Tuple2List* errors_98 = arg_150.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_295;
    tuple_295.t0 = tokens_137;
    tuple_295.t1 = errors_98;
    struct AArm_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_585 = parseMatchArm_1(matchLoc_1, armLoc_2, tuple_295);
    struct AArm_ arm_ = call_585.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_138 = call_585.t1;
    struct StringIntIntTuple2Tuple2List* errors_99 = call_585.t2;
    struct AArm_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_233;
    if ((!(tokens_138))) goto next_882;
    if ((tokens_138->head.t0.tag != Pipe_)) goto next_882;
    struct IntIntTuple2 pipeLoc_1 = tokens_138->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_139 = tokens_138->tail;
    int call_586 = locInside_(matchLoc_1, pipeLoc_1);
    if ((!(call_586))) goto next_882;
    struct AArm_List* list_75 = (struct AArm_List*)malloc(sizeof(struct AArm_List));
    list_75->head = arm_;
    list_75->tail = acc_20;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_296;
    tuple_296.t0 = tokens_139;
    tuple_296.t1 = errors_99;
    struct AArm_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_587 = go_87(matchLoc_1, list_75, pipeLoc_1, tuple_296);
    match_233 = call_587;
    goto end_match_881;
next_882:;
    struct AArm_List* list_76 = (struct AArm_List*)malloc(sizeof(struct AArm_List));
    list_76->head = arm_;
    list_76->tail = acc_20;
    struct AArm_List* call_588 = listRev_3(list_76);
    struct AArm_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_297;
    tuple_297.t0 = call_588;
    tuple_297.t1 = tokens_138;
    tuple_297.t2 = errors_99;
    match_233 = tuple_297;
    goto end_match_881;
next_883:;
end_match_881:;
    return match_233;
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

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseMatch_1(struct IntIntTuple2 matchLoc_1, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_151) {
    struct Token_IntIntTuple2Tuple2List* tokens_132 = arg_151.t0;
    struct StringIntIntTuple2Tuple2List* errors_94 = arg_151.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_298;
    tuple_298.t0 = tokens_132;
    tuple_298.t1 = errors_94;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_589 = parseExpr_1(matchLoc_1, tuple_298);
    struct AExpr_ target_3 = call_589.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_133 = call_589.t1;
    struct StringIntIntTuple2Tuple2List* errors_95 = call_589.t2;
    struct IntIntTuple2Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_234;
    if ((!(tokens_133))) goto next_885;
    if ((tokens_133->head.t0.tag != With_)) goto next_885;
    if ((!(tokens_133->tail))) goto next_885;
    if ((tokens_133->tail->head.t0.tag != Pipe_)) goto next_885;
    struct IntIntTuple2 pipeLoc_ = tokens_133->tail->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_135 = tokens_133->tail->tail;
    struct IntIntTuple2Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_299;
    tuple_299.t0 = pipeLoc_;
    tuple_299.t1 = tokens_135;
    tuple_299.t2 = errors_95;
    match_234 = tuple_299;
    goto end_match_884;
next_885:;
    if ((!(tokens_133))) goto next_886;
    if ((tokens_133->head.t0.tag != With_)) goto next_886;
    struct IntIntTuple2 withLoc_ = tokens_133->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_136 = tokens_133->tail;
    struct IntIntTuple2Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_300;
    tuple_300.t0 = withLoc_;
    tuple_300.t1 = tokens_136;
    tuple_300.t2 = errors_95;
    match_234 = tuple_300;
    goto end_match_884;
next_886:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_301;
    tuple_301.t0 = tokens_133;
    tuple_301.t1 = errors_95;
    struct StringIntIntTuple2Tuple2List* call_590 = parseNewError_1((struct String){.str = "Expected \'with\'", .len = 15}, tuple_301);
    struct StringIntIntTuple2Tuple2List* errors_97 = call_590;
    struct IntIntTuple2Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_302;
    tuple_302.t0 = matchLoc_1;
    tuple_302.t1 = tokens_133;
    tuple_302.t2 = errors_97;
    match_234 = tuple_302;
    goto end_match_884;
next_887:;
end_match_884:;
    struct IntIntTuple2 armLoc_1 = match_234.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_134 = match_234.t1;
    struct StringIntIntTuple2Tuple2List* errors_96 = match_234.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_303;
    tuple_303.t0 = tokens_134;
    tuple_303.t1 = errors_96;
    struct AArm_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_591 = go_87(matchLoc_1, NULL, armLoc_1, tuple_303);
    struct AArm_List* arms_3 = call_591.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_140 = call_591.t1;
    struct StringIntIntTuple2Tuple2List* errors_100 = call_591.t2;
    struct AExpr_AArm_ListIntIntTuple2Tuple3 tuple_305;
    tuple_305.t0 = target_3;
    tuple_305.t1 = arms_3;
    tuple_305.t2 = matchLoc_1;
    struct AExpr_AArm_ListIntIntTuple2Tuple3* payload_114 = (struct AExpr_AArm_ListIntIntTuple2Tuple3*)malloc(sizeof(struct AExpr_AArm_ListIntIntTuple2Tuple3));
    (*(((struct AExpr_AArm_ListIntIntTuple2Tuple3*)payload_114))) = tuple_305;
    struct AExpr_ variant_114 = (struct AExpr_){.tag = Match_1, .Match_1 = payload_114};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_304;
    tuple_304.t0 = variant_114;
    tuple_304.t1 = tokens_140;
    tuple_304.t2 = errors_100;
    return tuple_304;
}

struct APat_ListAExpr_IntIntTuple2Tuple3 {
    struct APat_List* t0;
    struct AExpr_ t1;
    struct IntIntTuple2 t2;
};

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseFun_1(struct IntIntTuple2 baseLoc_27, struct IntIntTuple2 funLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_152) {
    struct Token_IntIntTuple2Tuple2List* tokens_141 = arg_152.t0;
    struct StringIntIntTuple2Tuple2List* errors_101 = arg_152.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_306;
    tuple_306.t0 = tokens_141;
    tuple_306.t1 = errors_101;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_592 = parsePatCallArgs_1(baseLoc_27, funLoc_, tuple_306);
    struct APat_List* pats_3 = call_592.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_142 = call_592.t1;
    struct StringIntIntTuple2Tuple2List* errors_102 = call_592.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_235;
    if ((!(tokens_142))) goto next_889;
    if ((tokens_142->head.t0.tag != Arrow_)) goto next_889;
    struct IntIntTuple2 arrowLoc_1 = tokens_142->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_144 = tokens_142->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_307;
    tuple_307.t0 = tokens_144;
    tuple_307.t1 = errors_102;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_593 = parseSemi_1(baseLoc_27, arrowLoc_1, tuple_307);
    match_235 = call_593;
    goto end_match_888;
next_889:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_308;
    tuple_308.t0 = tokens_142;
    tuple_308.t1 = errors_102;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_594 = parseExprError_1((struct String){.str = "Missing \'->\'", .len = 12}, tuple_308);
    match_235 = call_594;
    goto end_match_888;
next_890:;
end_match_888:;
    struct AExpr_ body_11 = match_235.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_143 = match_235.t1;
    struct StringIntIntTuple2Tuple2List* errors_103 = match_235.t2;
    struct APat_ListAExpr_IntIntTuple2Tuple3 tuple_310;
    tuple_310.t0 = pats_3;
    tuple_310.t1 = body_11;
    tuple_310.t2 = funLoc_;
    struct APat_ListAExpr_IntIntTuple2Tuple3* payload_115 = (struct APat_ListAExpr_IntIntTuple2Tuple3*)malloc(sizeof(struct APat_ListAExpr_IntIntTuple2Tuple3));
    (*(((struct APat_ListAExpr_IntIntTuple2Tuple3*)payload_115))) = tuple_310;
    struct AExpr_ variant_115 = (struct AExpr_){.tag = Fun_3, .Fun_3 = payload_115};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_309;
    tuple_309.t0 = variant_115;
    tuple_309.t1 = tokens_143;
    tuple_309.t2 = errors_103;
    return tuple_309;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseParenBody_1(struct IntIntTuple2 baseLoc_28, struct IntIntTuple2 parenLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_153) {
    struct Token_IntIntTuple2Tuple2List* tokens_145 = arg_153.t0;
    struct StringIntIntTuple2Tuple2List* errors_104 = arg_153.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_311;
    tuple_311.t0 = tokens_145;
    tuple_311.t1 = errors_104;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_595 = parseSemi_1(baseLoc_28, parenLoc_, tuple_311);
    struct AExpr_ body_12 = call_595.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_146 = call_595.t1;
    struct StringIntIntTuple2Tuple2List* errors_105 = call_595.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_236;
    if ((!(tokens_146))) goto next_892;
    if ((tokens_146->head.t0.tag != ParenR_)) goto next_892;
    struct Token_IntIntTuple2Tuple2List* tokens_147 = tokens_146->tail;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_312;
    tuple_312.t0 = body_12;
    tuple_312.t1 = tokens_147;
    tuple_312.t2 = errors_105;
    match_236 = tuple_312;
    goto end_match_891;
next_892:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_313;
    tuple_313.t0 = tokens_146;
    tuple_313.t1 = errors_105;
    struct StringIntIntTuple2Tuple2List* call_596 = parseNewError_1((struct String){.str = "Expected \')\'", .len = 12}, tuple_313);
    struct StringIntIntTuple2Tuple2List* errors_106 = call_596;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_314;
    tuple_314.t0 = body_12;
    tuple_314.t1 = tokens_146;
    tuple_314.t2 = errors_106;
    match_236 = tuple_314;
    goto end_match_891;
next_893:;
end_match_891:;
    return match_236;
}

struct Token_IntIntTuple2Tuple2List* parseAccessModifier_1(struct Token_IntIntTuple2Tuple2List* tokens_148) {
    struct Token_IntIntTuple2Tuple2List* match_237;
    if ((!(tokens_148))) goto next_895;
    struct Token_ t_12 = tokens_148->head.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_149 = tokens_148->tail;
    int call_597 = tokenIsAccessModifier_(t_12);
    if ((!(call_597))) goto next_895;
    match_237 = tokens_149;
    goto end_match_894;
next_895:;
    match_237 = tokens_148;
    goto end_match_894;
next_896:;
end_match_894:;
    return match_237;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseLet_1(struct IntIntTuple2 letLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_154) {
    struct Token_IntIntTuple2Tuple2List* tokens_150 = arg_154.t0;
    struct StringIntIntTuple2Tuple2List* errors_107 = arg_154.t1;
    struct IntIntTuple2 call_598 = locAddX_(1, letLoc_);
    struct IntIntTuple2 innerBaseLoc_3 = call_598;
    struct Token_IntIntTuple2Tuple2List* call_599 = parseAccessModifier_1(tokens_150);
    struct Token_IntIntTuple2Tuple2List* tokens_151 = call_599;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_315;
    tuple_315.t0 = tokens_151;
    tuple_315.t1 = errors_107;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_600 = parsePatLet_1(innerBaseLoc_3, tuple_315);
    struct APat_ pat_22 = call_600.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_152 = call_600.t1;
    struct StringIntIntTuple2Tuple2List* errors_108 = call_600.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_238;
    if ((!(tokens_152))) goto next_898;
    if ((tokens_152->head.t0.tag != Eq_)) goto next_898;
    struct IntIntTuple2 eqLoc_ = tokens_152->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_154 = tokens_152->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_316;
    tuple_316.t0 = tokens_154;
    tuple_316.t1 = errors_108;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_601 = parseSemi_1(innerBaseLoc_3, eqLoc_, tuple_316);
    match_238 = call_601;
    goto end_match_897;
next_898:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_317;
    tuple_317.t0 = tokens_152;
    tuple_317.t1 = errors_108;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_602 = parseExprError_1((struct String){.str = "Missing \'=\'", .len = 11}, tuple_317);
    match_238 = call_602;
    goto end_match_897;
next_899:;
end_match_897:;
    struct AExpr_ body_13 = match_238.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_153 = match_238.t1;
    struct StringIntIntTuple2Tuple2List* errors_109 = match_238.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_239;
    if ((!(tokens_153))) goto next_901;
    if ((tokens_153->head.t0.tag != In_)) goto next_901;
    struct IntIntTuple2 inLoc_ = tokens_153->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_156 = tokens_153->tail;
    int call_603 = locInside_(letLoc_, inLoc_);
    if ((!(call_603))) goto next_901;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_318;
    tuple_318.t0 = tokens_156;
    tuple_318.t1 = errors_109;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_604 = parseSemi_1(letLoc_, inLoc_, tuple_318);
    match_239 = call_604;
    goto end_match_900;
next_901:;
    if ((!(tokens_153))) goto next_902;
    struct IntIntTuple2 call_605 = nextLoc_1(tokens_153);
    int call_606 = locIsSameColumn_(call_605, letLoc_);
    if ((!(call_606))) goto next_902;
    struct IntIntTuple2 call_607 = nextLoc_1(tokens_153);
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_319;
    tuple_319.t0 = tokens_153;
    tuple_319.t1 = errors_109;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_608 = parseSemi_1(letLoc_, call_607, tuple_319);
    match_239 = call_608;
    goto end_match_900;
next_902:;
    struct Token_IntIntTuple2Tuple2List* tokens_157 = tokens_153;
    struct AExpr_ListIntIntTuple2Tuple2 tuple_321;
    tuple_321.t0 = NULL;
    tuple_321.t1 = letLoc_;
    struct AExpr_ListIntIntTuple2Tuple2* payload_116 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_116))) = tuple_321;
    struct AExpr_ variant_116 = (struct AExpr_){.tag = TupleLit_1, .TupleLit_1 = payload_116};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_320;
    tuple_320.t0 = variant_116;
    tuple_320.t1 = tokens_157;
    tuple_320.t2 = errors_109;
    match_239 = tuple_320;
    goto end_match_900;
next_903:;
end_match_900:;
    struct AExpr_ next_11 = match_239.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_155 = match_239.t1;
    struct StringIntIntTuple2Tuple2List* errors_110 = match_239.t2;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4 tuple_323;
    tuple_323.t0 = pat_22;
    tuple_323.t1 = body_13;
    tuple_323.t2 = next_11;
    tuple_323.t3 = letLoc_;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4* payload_117 = (struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct APat_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)payload_117))) = tuple_323;
    struct AExpr_ variant_117 = (struct AExpr_){.tag = Let_1, .Let_1 = payload_117};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_322;
    tuple_322.t0 = variant_117;
    tuple_322.t1 = tokens_155;
    tuple_322.t2 = errors_110;
    return tuple_322;
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

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyDecl_1(struct IntIntTuple2 typeLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_155) {
    struct Token_IntIntTuple2Tuple2List* tokens_158 = arg_155.t0;
    struct StringIntIntTuple2Tuple2List* errors_111 = arg_155.t1;
    struct IntIntTuple2 call_609 = locAddX_(1, typeLoc_);
    struct IntIntTuple2 baseLoc_29 = call_609;
    struct Token_IntIntTuple2Tuple2List* call_610 = parseAccessModifier_1(tokens_158);
    struct Token_IntIntTuple2Tuple2List* tokens_159 = call_610;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_240;
    if ((!(tokens_159))) goto next_905;
    if ((tokens_159->head.t0.tag != Ident_)) goto next_905;
    struct String tyIdent_ = (*(tokens_159->head.t0.Ident_));
    struct Token_IntIntTuple2Tuple2List* tokens_160 = tokens_159->tail;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_241;
    if ((!(tokens_160))) goto next_908;
    if ((tokens_160->head.t0.tag != Eq_)) goto next_908;
    struct Token_IntIntTuple2Tuple2List* tokens_161 = tokens_160->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_324;
    tuple_324.t0 = tokens_161;
    tuple_324.t1 = errors_111;
    struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_611 = parseTyDeclBody_1(baseLoc_29, tuple_324);
    struct ATyDecl_ tyDecl_ = call_611.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_162 = call_611.t1;
    struct StringIntIntTuple2Tuple2List* errors_112 = call_611.t2;
    struct AExpr_ match_242;
    if ((tyDecl_.tag != Synonym_)) goto next_911;
    struct ATy_ ty_52 = (*(tyDecl_.Synonym_));
    struct StringATy_IntIntTuple2Tuple3 tuple_325;
    tuple_325.t0 = tyIdent_;
    tuple_325.t1 = ty_52;
    tuple_325.t2 = typeLoc_;
    struct StringATy_IntIntTuple2Tuple3* payload_118 = (struct StringATy_IntIntTuple2Tuple3*)malloc(sizeof(struct StringATy_IntIntTuple2Tuple3));
    (*(((struct StringATy_IntIntTuple2Tuple3*)payload_118))) = tuple_325;
    struct AExpr_ variant_118 = (struct AExpr_){.tag = TySynonym_, .TySynonym_ = payload_118};
    match_242 = variant_118;
    goto end_match_910;
next_911:;
    if ((tyDecl_.tag != Union_)) goto next_912;
    struct AVariant_List* variants_2 = (*(tyDecl_.Union_));
    struct StringAVariant_ListIntIntTuple2Tuple3 tuple_326;
    tuple_326.t0 = tyIdent_;
    tuple_326.t1 = variants_2;
    tuple_326.t2 = typeLoc_;
    struct StringAVariant_ListIntIntTuple2Tuple3* payload_119 = (struct StringAVariant_ListIntIntTuple2Tuple3*)malloc(sizeof(struct StringAVariant_ListIntIntTuple2Tuple3));
    (*(((struct StringAVariant_ListIntIntTuple2Tuple3*)payload_119))) = tuple_326;
    struct AExpr_ variant_119 = (struct AExpr_){.tag = TyUnion_, .TyUnion_ = payload_119};
    match_242 = variant_119;
    goto end_match_910;
next_912:;
    exit(1);
end_match_910:;
    struct AExpr_ expr_11 = match_242;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_327;
    tuple_327.t0 = expr_11;
    tuple_327.t1 = tokens_162;
    tuple_327.t2 = errors_112;
    match_241 = tuple_327;
    goto end_match_907;
next_908:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_328;
    tuple_328.t0 = tokens_160;
    tuple_328.t1 = errors_111;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_612 = parseTyError_1((struct String){.str = "Expected \'=\'", .len = 12}, tuple_328);
    struct ATy_ ty_53 = call_612.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_163 = call_612.t1;
    struct StringIntIntTuple2Tuple2List* errors_113 = call_612.t2;
    struct StringATy_IntIntTuple2Tuple3 tuple_330;
    tuple_330.t0 = tyIdent_;
    tuple_330.t1 = ty_53;
    tuple_330.t2 = typeLoc_;
    struct StringATy_IntIntTuple2Tuple3* payload_120 = (struct StringATy_IntIntTuple2Tuple3*)malloc(sizeof(struct StringATy_IntIntTuple2Tuple3));
    (*(((struct StringATy_IntIntTuple2Tuple3*)payload_120))) = tuple_330;
    struct AExpr_ variant_120 = (struct AExpr_){.tag = TySynonym_, .TySynonym_ = payload_120};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_329;
    tuple_329.t0 = variant_120;
    tuple_329.t1 = tokens_163;
    tuple_329.t2 = errors_113;
    match_241 = tuple_329;
    goto end_match_907;
next_909:;
end_match_907:;
    match_240 = match_241;
    goto end_match_904;
next_905:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_331;
    tuple_331.t0 = tokens_159;
    tuple_331.t1 = errors_111;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_613 = parseExprError_1((struct String){.str = "Expected identifier", .len = 19}, tuple_331);
    match_240 = call_613;
    goto end_match_904;
next_906:;
end_match_904:;
    return match_240;
}

struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct StringList* t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_76(struct StringList* acc_21, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_156) {
    struct Token_IntIntTuple2Tuple2List* tokens_166 = arg_156.t0;
    struct StringIntIntTuple2Tuple2List* errors_116 = arg_156.t1;
    struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_243;
    if ((!(tokens_166))) goto next_914;
    if ((tokens_166->head.t0.tag != Dot_)) goto next_914;
    if ((!(tokens_166->tail))) goto next_914;
    if ((tokens_166->tail->head.t0.tag != Ident_)) goto next_914;
    struct String ident_23 = (*(tokens_166->tail->head.t0.Ident_));
    struct Token_IntIntTuple2Tuple2List* tokens_167 = tokens_166->tail->tail;
    struct StringList* list_77 = (struct StringList*)malloc(sizeof(struct StringList));
    list_77->head = ident_23;
    list_77->tail = acc_21;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_332;
    tuple_332.t0 = tokens_167;
    tuple_332.t1 = errors_116;
    struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_614 = go_76(list_77, tuple_332);
    match_243 = call_614;
    goto end_match_913;
next_914:;
    if ((!(tokens_166))) goto next_915;
    if ((tokens_166->head.t0.tag != Dot_)) goto next_915;
    struct Token_IntIntTuple2Tuple2List* tokens_168 = tokens_166->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_333;
    tuple_333.t0 = tokens_168;
    tuple_333.t1 = errors_116;
    struct StringIntIntTuple2Tuple2List* call_615 = parseNewError_1((struct String){.str = "Expected identifier", .len = 19}, tuple_333);
    struct StringIntIntTuple2Tuple2List* errors_117 = call_615;
    struct StringList* call_616 = listRev_2(acc_21);
    struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_334;
    tuple_334.t0 = call_616;
    tuple_334.t1 = tokens_168;
    tuple_334.t2 = errors_117;
    match_243 = tuple_334;
    goto end_match_913;
next_915:;
    struct StringList* call_617 = listRev_2(acc_21);
    struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_335;
    tuple_335.t0 = call_617;
    tuple_335.t1 = tokens_166;
    tuple_335.t2 = errors_116;
    match_243 = tuple_335;
    goto end_match_913;
next_916:;
end_match_913:;
    return match_243;
}

struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePath_1(struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_157) {
    struct Token_IntIntTuple2Tuple2List* tokens_165 = arg_157.t0;
    struct StringIntIntTuple2Tuple2List* errors_115 = arg_157.t1;
    struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_244;
    if ((!(tokens_165))) goto next_918;
    if ((tokens_165->head.t0.tag != Ident_)) goto next_918;
    struct String ident_24 = (*(tokens_165->head.t0.Ident_));
    struct Token_IntIntTuple2Tuple2List* tokens_169 = tokens_165->tail;
    struct StringList* list_78 = (struct StringList*)malloc(sizeof(struct StringList));
    list_78->head = ident_24;
    list_78->tail = NULL;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_336;
    tuple_336.t0 = tokens_169;
    tuple_336.t1 = errors_115;
    struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_618 = go_76(list_78, tuple_336);
    match_244 = call_618;
    goto end_match_917;
next_918:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_337;
    tuple_337.t0 = tokens_165;
    tuple_337.t1 = errors_115;
    struct StringIntIntTuple2Tuple2List* call_619 = parseNewError_1((struct String){.str = "Expected identifier", .len = 19}, tuple_337);
    struct StringIntIntTuple2Tuple2List* errors_118 = call_619;
    struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_338;
    tuple_338.t0 = NULL;
    tuple_338.t1 = tokens_165;
    tuple_338.t2 = errors_118;
    match_244 = tuple_338;
    goto end_match_917;
next_919:;
end_match_917:;
    return match_244;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseOpen_1(struct IntIntTuple2 openLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_158) {
    struct Token_IntIntTuple2Tuple2List* tokens_164 = arg_158.t0;
    struct StringIntIntTuple2Tuple2List* errors_114 = arg_158.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_339;
    tuple_339.t0 = tokens_164;
    tuple_339.t1 = errors_114;
    struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_620 = parsePath_1(tuple_339);
    struct StringList* path_3 = call_620.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_170 = call_620.t1;
    struct StringIntIntTuple2Tuple2List* errors_119 = call_620.t2;
    struct StringListIntIntTuple2Tuple2 tuple_341;
    tuple_341.t0 = path_3;
    tuple_341.t1 = openLoc_;
    struct StringListIntIntTuple2Tuple2* payload_121 = (struct StringListIntIntTuple2Tuple2*)malloc(sizeof(struct StringListIntIntTuple2Tuple2));
    (*(((struct StringListIntIntTuple2Tuple2*)payload_121))) = tuple_341;
    struct AExpr_ variant_121 = (struct AExpr_){.tag = Open_1, .Open_1 = payload_121};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_340;
    tuple_340.t0 = variant_121;
    tuple_340.t1 = tokens_170;
    tuple_340.t2 = errors_119;
    return tuple_340;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseAtom_1(struct IntIntTuple2 baseLoc_30, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_159) {
    struct Token_IntIntTuple2Tuple2List* tokens_171 = arg_159.t0;
    struct StringIntIntTuple2Tuple2List* errors_120 = arg_159.t1;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_245;
    int call_621 = nextInside_1(baseLoc_30, tokens_171);
    if (call_621) goto next_921;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_342;
    tuple_342.t0 = tokens_171;
    tuple_342.t1 = errors_120;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_622 = parseExprError_1((struct String){.str = "Expected an expression", .len = 22}, tuple_342);
    match_245 = call_622;
    goto end_match_920;
next_921:;
    if ((!(tokens_171))) goto next_922;
    if ((tokens_171->head.t0.tag != ParenL_)) goto next_922;
    struct IntIntTuple2 loc_54 = tokens_171->head.t1;
    if ((!(tokens_171->tail))) goto next_922;
    if ((tokens_171->tail->head.t0.tag != ParenR_)) goto next_922;
    struct Token_IntIntTuple2Tuple2List* tokens_172 = tokens_171->tail->tail;
    struct AExpr_ListIntIntTuple2Tuple2 tuple_344;
    tuple_344.t0 = NULL;
    tuple_344.t1 = loc_54;
    struct AExpr_ListIntIntTuple2Tuple2* payload_122 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_122))) = tuple_344;
    struct AExpr_ variant_122 = (struct AExpr_){.tag = TupleLit_1, .TupleLit_1 = payload_122};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_343;
    tuple_343.t0 = variant_122;
    tuple_343.t1 = tokens_172;
    tuple_343.t2 = errors_120;
    match_245 = tuple_343;
    goto end_match_920;
next_922:;
    if ((!(tokens_171))) goto next_923;
    if ((tokens_171->head.t0.tag != Bool_1)) goto next_923;
    int value_14 = (*(tokens_171->head.t0.Bool_1));
    struct IntIntTuple2 loc_55 = tokens_171->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_173 = tokens_171->tail;
    int* payload_123 = (int*)malloc(sizeof(int));
    (*(((int*)payload_123))) = value_14;
    struct Lit_ variant_123 = (struct Lit_){.tag = Bool_, .Bool_ = payload_123};
    struct Lit_IntIntTuple2Tuple2 tuple_346;
    tuple_346.t0 = variant_123;
    tuple_346.t1 = loc_55;
    struct Lit_IntIntTuple2Tuple2* payload_124 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_124))) = tuple_346;
    struct AExpr_ variant_124 = (struct AExpr_){.tag = Lit_1, .Lit_1 = payload_124};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_345;
    tuple_345.t0 = variant_124;
    tuple_345.t1 = tokens_173;
    tuple_345.t2 = errors_120;
    match_245 = tuple_345;
    goto end_match_920;
next_923:;
    if ((!(tokens_171))) goto next_924;
    if ((tokens_171->head.t0.tag != Int_1)) goto next_924;
    int value_15 = (*(tokens_171->head.t0.Int_1));
    struct IntIntTuple2 loc_56 = tokens_171->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_174 = tokens_171->tail;
    int* payload_125 = (int*)malloc(sizeof(int));
    (*(((int*)payload_125))) = value_15;
    struct Lit_ variant_125 = (struct Lit_){.tag = Int_, .Int_ = payload_125};
    struct Lit_IntIntTuple2Tuple2 tuple_348;
    tuple_348.t0 = variant_125;
    tuple_348.t1 = loc_56;
    struct Lit_IntIntTuple2Tuple2* payload_126 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_126))) = tuple_348;
    struct AExpr_ variant_126 = (struct AExpr_){.tag = Lit_1, .Lit_1 = payload_126};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_347;
    tuple_347.t0 = variant_126;
    tuple_347.t1 = tokens_174;
    tuple_347.t2 = errors_120;
    match_245 = tuple_347;
    goto end_match_920;
next_924:;
    if ((!(tokens_171))) goto next_925;
    if ((tokens_171->head.t0.tag != Char_1)) goto next_925;
    char value_16 = (*(tokens_171->head.t0.Char_1));
    struct IntIntTuple2 loc_57 = tokens_171->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_175 = tokens_171->tail;
    char* payload_127 = (char*)malloc(sizeof(char));
    (*(((char*)payload_127))) = value_16;
    struct Lit_ variant_127 = (struct Lit_){.tag = Char_, .Char_ = payload_127};
    struct Lit_IntIntTuple2Tuple2 tuple_350;
    tuple_350.t0 = variant_127;
    tuple_350.t1 = loc_57;
    struct Lit_IntIntTuple2Tuple2* payload_128 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_128))) = tuple_350;
    struct AExpr_ variant_128 = (struct AExpr_){.tag = Lit_1, .Lit_1 = payload_128};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_349;
    tuple_349.t0 = variant_128;
    tuple_349.t1 = tokens_175;
    tuple_349.t2 = errors_120;
    match_245 = tuple_349;
    goto end_match_920;
next_925:;
    if ((!(tokens_171))) goto next_926;
    if ((tokens_171->head.t0.tag != Str_1)) goto next_926;
    struct String value_17 = (*(tokens_171->head.t0.Str_1));
    struct IntIntTuple2 loc_58 = tokens_171->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_176 = tokens_171->tail;
    struct String* payload_129 = (struct String*)malloc(sizeof(struct String));
    (*(((struct String*)payload_129))) = value_17;
    struct Lit_ variant_129 = (struct Lit_){.tag = Str_, .Str_ = payload_129};
    struct Lit_IntIntTuple2Tuple2 tuple_352;
    tuple_352.t0 = variant_129;
    tuple_352.t1 = loc_58;
    struct Lit_IntIntTuple2Tuple2* payload_130 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_130))) = tuple_352;
    struct AExpr_ variant_130 = (struct AExpr_){.tag = Lit_1, .Lit_1 = payload_130};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_351;
    tuple_351.t0 = variant_130;
    tuple_351.t1 = tokens_176;
    tuple_351.t2 = errors_120;
    match_245 = tuple_351;
    goto end_match_920;
next_926:;
    if ((!(tokens_171))) goto next_927;
    if ((tokens_171->head.t0.tag != Ident_)) goto next_927;
    struct String ident_25 = (*(tokens_171->head.t0.Ident_));
    struct IntIntTuple2 loc_59 = tokens_171->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_177 = tokens_171->tail;
    struct StringIntIntTuple2Tuple2 tuple_354;
    tuple_354.t0 = ident_25;
    tuple_354.t1 = loc_59;
    struct StringIntIntTuple2Tuple2* payload_131 = (struct StringIntIntTuple2Tuple2*)malloc(sizeof(struct StringIntIntTuple2Tuple2));
    (*(((struct StringIntIntTuple2Tuple2*)payload_131))) = tuple_354;
    struct AExpr_ variant_131 = (struct AExpr_){.tag = Ident_2, .Ident_2 = payload_131};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_353;
    tuple_353.t0 = variant_131;
    tuple_353.t1 = tokens_177;
    tuple_353.t2 = errors_120;
    match_245 = tuple_353;
    goto end_match_920;
next_927:;
    if ((!(tokens_171))) goto next_928;
    if ((tokens_171->head.t0.tag != ParenL_)) goto next_928;
    struct IntIntTuple2 parenLoc_1 = tokens_171->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_178 = tokens_171->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_355;
    tuple_355.t0 = tokens_178;
    tuple_355.t1 = errors_120;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_623 = parseParenBody_1(baseLoc_30, parenLoc_1, tuple_355);
    match_245 = call_623;
    goto end_match_920;
next_928:;
    if ((!(tokens_171))) goto next_929;
    if ((tokens_171->head.t0.tag != BracketL_)) goto next_929;
    struct IntIntTuple2 bracketLoc_2 = tokens_171->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_179 = tokens_171->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_356;
    tuple_356.t0 = tokens_179;
    tuple_356.t1 = errors_120;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_624 = parseList_1(baseLoc_30, bracketLoc_2, tuple_356);
    match_245 = call_624;
    goto end_match_920;
next_929:;
    if ((!(tokens_171))) goto next_930;
    if ((tokens_171->head.t0.tag != If_)) goto next_930;
    struct IntIntTuple2 loc_60 = tokens_171->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_180 = tokens_171->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_357;
    tuple_357.t0 = tokens_180;
    tuple_357.t1 = errors_120;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_625 = parseIf_1(loc_60, tuple_357);
    match_245 = call_625;
    goto end_match_920;
next_930:;
    if ((!(tokens_171))) goto next_931;
    if ((tokens_171->head.t0.tag != Match_)) goto next_931;
    struct IntIntTuple2 loc_61 = tokens_171->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_181 = tokens_171->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_358;
    tuple_358.t0 = tokens_181;
    tuple_358.t1 = errors_120;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_626 = parseMatch_1(loc_61, tuple_358);
    match_245 = call_626;
    goto end_match_920;
next_931:;
    if ((!(tokens_171))) goto next_932;
    if ((tokens_171->head.t0.tag != Fun_)) goto next_932;
    struct IntIntTuple2 loc_62 = tokens_171->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_182 = tokens_171->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_359;
    tuple_359.t0 = tokens_182;
    tuple_359.t1 = errors_120;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_627 = parseFun_1(baseLoc_30, loc_62, tuple_359);
    match_245 = call_627;
    goto end_match_920;
next_932:;
    if ((!(tokens_171))) goto next_933;
    if ((tokens_171->head.t0.tag != Let_)) goto next_933;
    struct IntIntTuple2 letLoc_1 = tokens_171->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_183 = tokens_171->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_360;
    tuple_360.t0 = tokens_183;
    tuple_360.t1 = errors_120;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_628 = parseLet_1(letLoc_1, tuple_360);
    match_245 = call_628;
    goto end_match_920;
next_933:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_361;
    tuple_361.t0 = tokens_171;
    tuple_361.t1 = errors_120;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_629 = parseExprError_1((struct String){.str = "Expected an expression", .len = 22}, tuple_361);
    match_245 = call_629;
    goto end_match_920;
next_934:;
end_match_920:;
    return match_245;
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

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_85(struct IntIntTuple2 baseLoc_31, struct AExpr_ acc_22, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_160) {
    struct Token_IntIntTuple2Tuple2List* tokens_186 = arg_160.t0;
    struct StringIntIntTuple2Tuple2List* errors_123 = arg_160.t1;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_246;
    if ((!(tokens_186))) goto next_936;
    if ((tokens_186->head.t0.tag != Dot_)) goto next_936;
    struct IntIntTuple2 loc_63 = tokens_186->head.t1;
    if ((!(tokens_186->tail))) goto next_936;
    if ((tokens_186->tail->head.t0.tag != BracketL_)) goto next_936;
    struct Token_IntIntTuple2Tuple2List* tokens_187 = tokens_186->tail->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_362;
    tuple_362.t0 = tokens_187;
    tuple_362.t1 = errors_123;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_630 = parseRange_1(baseLoc_31, tuple_362);
    struct AExpr_ r_31 = call_630.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_188 = call_630.t1;
    struct StringIntIntTuple2Tuple2List* errors_124 = call_630.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 match_247;
    if ((!(tokens_188))) goto next_941;
    if ((tokens_188->head.t0.tag != BracketR_)) goto next_941;
    struct Token_IntIntTuple2Tuple2List* tokens_190 = tokens_188->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_363;
    tuple_363.t0 = tokens_190;
    tuple_363.t1 = errors_124;
    match_247 = tuple_363;
    goto end_match_940;
next_941:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_364;
    tuple_364.t0 = tokens_188;
    tuple_364.t1 = errors_124;
    struct StringIntIntTuple2Tuple2List* call_631 = parseNewError_1((struct String){.str = "Expected closing \']\'", .len = 20}, tuple_364);
    struct StringIntIntTuple2Tuple2List* errors_126 = call_631;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_365;
    tuple_365.t0 = tokens_188;
    tuple_365.t1 = errors_126;
    match_247 = tuple_365;
    goto end_match_940;
next_942:;
end_match_940:;
    struct Token_IntIntTuple2Tuple2List* tokens_189 = match_247.t0;
    struct StringIntIntTuple2Tuple2List* errors_125 = match_247.t1;
    struct AExpr_AExpr_IntIntTuple2Tuple3 tuple_366;
    tuple_366.t0 = acc_22;
    tuple_366.t1 = r_31;
    tuple_366.t2 = loc_63;
    struct AExpr_AExpr_IntIntTuple2Tuple3* payload_132 = (struct AExpr_AExpr_IntIntTuple2Tuple3*)malloc(sizeof(struct AExpr_AExpr_IntIntTuple2Tuple3));
    (*(((struct AExpr_AExpr_IntIntTuple2Tuple3*)payload_132))) = tuple_366;
    struct AExpr_ variant_132 = (struct AExpr_){.tag = Index_, .Index_ = payload_132};
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_367;
    tuple_367.t0 = tokens_189;
    tuple_367.t1 = errors_125;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_632 = go_85(baseLoc_31, variant_132, tuple_367);
    match_246 = call_632;
    goto end_match_935;
next_936:;
    if ((!(tokens_186))) goto next_937;
    if ((tokens_186->head.t0.tag != Dot_)) goto next_937;
    struct IntIntTuple2 loc_64 = tokens_186->head.t1;
    if ((!(tokens_186->tail))) goto next_937;
    if ((tokens_186->tail->head.t0.tag != Ident_)) goto next_937;
    struct String r_32 = (*(tokens_186->tail->head.t0.Ident_));
    struct Token_IntIntTuple2Tuple2List* tokens_191 = tokens_186->tail->tail;
    struct AExpr_StringIntIntTuple2Tuple3 tuple_368;
    tuple_368.t0 = acc_22;
    tuple_368.t1 = r_32;
    tuple_368.t2 = loc_64;
    struct AExpr_StringIntIntTuple2Tuple3* payload_133 = (struct AExpr_StringIntIntTuple2Tuple3*)malloc(sizeof(struct AExpr_StringIntIntTuple2Tuple3));
    (*(((struct AExpr_StringIntIntTuple2Tuple3*)payload_133))) = tuple_368;
    struct AExpr_ variant_133 = (struct AExpr_){.tag = Nav_1, .Nav_1 = payload_133};
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_369;
    tuple_369.t0 = tokens_191;
    tuple_369.t1 = errors_123;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_633 = go_85(baseLoc_31, variant_133, tuple_369);
    match_246 = call_633;
    goto end_match_935;
next_937:;
    if ((!(tokens_186))) goto next_938;
    if ((tokens_186->head.t0.tag != Dot_)) goto next_938;
    struct Token_IntIntTuple2Tuple2List* tokens_192 = tokens_186->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_370;
    tuple_370.t0 = tokens_192;
    tuple_370.t1 = errors_123;
    struct StringIntIntTuple2Tuple2List* call_634 = parseNewError_1((struct String){.str = "Expected .[] or .field", .len = 22}, tuple_370);
    struct StringIntIntTuple2Tuple2List* errors_127 = call_634;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_371;
    tuple_371.t0 = acc_22;
    tuple_371.t1 = tokens_192;
    tuple_371.t2 = errors_127;
    match_246 = tuple_371;
    goto end_match_935;
next_938:;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_372;
    tuple_372.t0 = acc_22;
    tuple_372.t1 = tokens_186;
    tuple_372.t2 = errors_123;
    match_246 = tuple_372;
    goto end_match_935;
next_939:;
end_match_935:;
    return match_246;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseSuffix_1(struct IntIntTuple2 baseLoc_31, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_161) {
    struct Token_IntIntTuple2Tuple2List* tokens_184 = arg_161.t0;
    struct StringIntIntTuple2Tuple2List* errors_121 = arg_161.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_373;
    tuple_373.t0 = tokens_184;
    tuple_373.t1 = errors_121;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_635 = parseAtom_1(baseLoc_31, tuple_373);
    struct AExpr_ l_18 = call_635.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_185 = call_635.t1;
    struct StringIntIntTuple2Tuple2List* errors_122 = call_635.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_374;
    tuple_374.t0 = tokens_185;
    tuple_374.t1 = errors_122;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_636 = go_85(baseLoc_31, l_18, tuple_374);
    return call_636;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_84(struct IntIntTuple2 argBaseLoc_1, struct IntIntTuple2 calleeLoc_3, struct IntIntTuple2 baseLoc_32, struct AExpr_ callee_8, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_162) {
    struct Token_IntIntTuple2Tuple2List* tokens_195 = arg_162.t0;
    struct StringIntIntTuple2Tuple2List* errors_130 = arg_162.t1;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_248;
    int match_249;
    int call_637 = nextInside_1(argBaseLoc_1, tokens_195);
    if ((!(call_637))) goto next_945;
    int call_638 = leadsArg_1(tokens_195);
    match_249 = call_638;
    goto end_match_944;
next_945:;
    if (call_637) goto next_946;
    match_249 = 0;
    goto end_match_944;
next_946:;
    exit(1);
end_match_944:;
    if ((!(match_249))) goto next_947;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_375;
    tuple_375.t0 = tokens_195;
    tuple_375.t1 = errors_130;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_639 = parseSuffix_1(baseLoc_32, tuple_375);
    struct AExpr_ arg_2 = call_639.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_196 = call_639.t1;
    struct StringIntIntTuple2Tuple2List* errors_131 = call_639.t2;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_376;
    tuple_376.t0 = (struct Op_){.tag = App_};
    tuple_376.t1 = callee_8;
    tuple_376.t2 = arg_2;
    tuple_376.t3 = calleeLoc_3;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_134 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_134))) = tuple_376;
    struct AExpr_ variant_134 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_134};
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_377;
    tuple_377.t0 = tokens_196;
    tuple_377.t1 = errors_131;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_640 = go_84(argBaseLoc_1, calleeLoc_3, baseLoc_32, variant_134, tuple_377);
    match_248 = call_640;
    goto end_match_943;
next_947:;
    if (match_249) goto next_948;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_378;
    tuple_378.t0 = callee_8;
    tuple_378.t1 = tokens_195;
    tuple_378.t2 = errors_130;
    match_248 = tuple_378;
    goto end_match_943;
next_948:;
    exit(1);
end_match_943:;
    return match_248;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseApp_1(struct IntIntTuple2 baseLoc_32, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_163) {
    struct Token_IntIntTuple2Tuple2List* tokens_193 = arg_163.t0;
    struct StringIntIntTuple2Tuple2List* errors_128 = arg_163.t1;
    struct IntIntTuple2 call_641 = nextLoc_1(tokens_193);
    struct IntIntTuple2 calleeLoc_3 = call_641;
    struct IntIntTuple2 call_642 = locAddX_(1, calleeLoc_3);
    struct IntIntTuple2 argBaseLoc_1 = call_642;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_379;
    tuple_379.t0 = tokens_193;
    tuple_379.t1 = errors_128;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_643 = parseSuffix_1(baseLoc_32, tuple_379);
    struct AExpr_ callee_7 = call_643.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_194 = call_643.t1;
    struct StringIntIntTuple2Tuple2List* errors_129 = call_643.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_380;
    tuple_380.t0 = tokens_194;
    tuple_380.t1 = errors_129;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_644 = go_84(argBaseLoc_1, calleeLoc_3, baseLoc_32, callee_7, tuple_380);
    return call_644;
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

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePrefix_1(struct IntIntTuple2 baseLoc_33, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_164) {
    struct Token_IntIntTuple2Tuple2List* tokens_197 = arg_164.t0;
    struct StringIntIntTuple2Tuple2List* errors_132 = arg_164.t1;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_250;
    if ((!(tokens_197))) goto next_950;
    if ((tokens_197->head.t0.tag != Minus_)) goto next_950;
    struct IntIntTuple2 loc_65 = tokens_197->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_198 = tokens_197->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_381;
    tuple_381.t0 = tokens_198;
    tuple_381.t1 = errors_132;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_645 = parseApp_1(baseLoc_33, tuple_381);
    struct AExpr_ arg_3 = call_645.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_199 = call_645.t1;
    struct StringIntIntTuple2Tuple2List* errors_133 = call_645.t2;
    struct UniOp_AExpr_IntIntTuple2Tuple3 tuple_383;
    tuple_383.t0 = (struct UniOp_){.tag = Neg_};
    tuple_383.t1 = arg_3;
    tuple_383.t2 = loc_65;
    struct UniOp_AExpr_IntIntTuple2Tuple3* payload_135 = (struct UniOp_AExpr_IntIntTuple2Tuple3*)malloc(sizeof(struct UniOp_AExpr_IntIntTuple2Tuple3));
    (*(((struct UniOp_AExpr_IntIntTuple2Tuple3*)payload_135))) = tuple_383;
    struct AExpr_ variant_135 = (struct AExpr_){.tag = Uni_, .Uni_ = payload_135};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_382;
    tuple_382.t0 = variant_135;
    tuple_382.t1 = tokens_199;
    tuple_382.t2 = errors_133;
    match_250 = tuple_382;
    goto end_match_949;
next_950:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_384;
    tuple_384.t0 = tokens_197;
    tuple_384.t1 = errors_132;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_646 = parseApp_1(baseLoc_33, tuple_384);
    match_250 = call_646;
    goto end_match_949;
next_951:;
end_match_949:;
    return match_250;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseNextLevelOp_1(struct OpLevel_ level_1, struct IntIntTuple2 baseLoc_34, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_165) {
    struct Token_IntIntTuple2Tuple2List* tokens_200 = arg_165.t0;
    struct StringIntIntTuple2Tuple2List* errors_134 = arg_165.t1;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_251;
    struct OpLevel_ call_647 = opLevelToNext_(level_1);
    if ((call_647.tag != Prefix_)) goto next_953;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_385;
    tuple_385.t0 = tokens_200;
    tuple_385.t1 = errors_134;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_648 = parsePrefix_1(baseLoc_34, tuple_385);
    match_251 = call_648;
    goto end_match_952;
next_953:;
    struct OpLevel_ nextLevel_ = call_647;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_386;
    tuple_386.t0 = tokens_200;
    tuple_386.t1 = errors_134;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_649 = parseOp_1(nextLevel_, baseLoc_34, tuple_386);
    match_251 = call_649;
    goto end_match_952;
next_954:;
end_match_952:;
    return match_251;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 nextL_1(struct IntIntTuple2 baseLoc_35, struct OpLevel_ level_2, struct AExpr_ expr_12, struct Op_ op_, struct IntIntTuple2 opLoc_2, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_166) {
    struct Token_IntIntTuple2Tuple2List* tokens_202 = arg_166.t0;
    struct StringIntIntTuple2Tuple2List* errors_136 = arg_166.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_387;
    tuple_387.t0 = tokens_202;
    tuple_387.t1 = errors_136;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_650 = parseNextLevelOp_1(level_2, baseLoc_35, tuple_387);
    struct AExpr_ second_4 = call_650.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_203 = call_650.t1;
    struct StringIntIntTuple2Tuple2List* errors_137 = call_650.t2;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_388;
    tuple_388.t0 = op_;
    tuple_388.t1 = expr_12;
    tuple_388.t2 = second_4;
    tuple_388.t3 = opLoc_2;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_136 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_136))) = tuple_388;
    struct AExpr_ variant_136 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_136};
    struct AExpr_ expr_13 = variant_136;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_389;
    tuple_389.t0 = tokens_203;
    tuple_389.t1 = errors_137;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_651 = parseOps_1(level_2, baseLoc_35, expr_13, tuple_389);
    return call_651;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 nextR_1(struct IntIntTuple2 baseLoc_35, struct OpLevel_ level_2, struct AExpr_ expr_14, struct Op_ op_1, struct IntIntTuple2 opLoc_3, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_167) {
    struct Token_IntIntTuple2Tuple2List* tokens_204 = arg_167.t0;
    struct StringIntIntTuple2Tuple2List* errors_138 = arg_167.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_390;
    tuple_390.t0 = tokens_204;
    tuple_390.t1 = errors_138;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_652 = parseOp_1(level_2, baseLoc_35, tuple_390);
    struct AExpr_ second_5 = call_652.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_205 = call_652.t1;
    struct StringIntIntTuple2Tuple2List* errors_139 = call_652.t2;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_391;
    tuple_391.t0 = op_1;
    tuple_391.t1 = expr_14;
    tuple_391.t2 = second_5;
    tuple_391.t3 = opLoc_3;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_137 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_137))) = tuple_391;
    struct AExpr_ variant_137 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_137};
    struct AExpr_ expr_15 = variant_137;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_392;
    tuple_392.t0 = tokens_205;
    tuple_392.t1 = errors_139;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_653 = parseOps_1(level_2, baseLoc_35, expr_15, tuple_392);
    return call_653;
}

struct OpLevel_Token_IntIntTuple2Tuple2ListTuple2 {
    struct OpLevel_ t0;
    struct Token_IntIntTuple2Tuple2List* t1;
};

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseOps_1(struct OpLevel_ level_2, struct IntIntTuple2 baseLoc_35, struct AExpr_ first_3, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_168) {
    struct Token_IntIntTuple2Tuple2List* tokens_201 = arg_168.t0;
    struct StringIntIntTuple2Tuple2List* errors_135 = arg_168.t1;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_252;
    struct OpLevel_Token_IntIntTuple2Tuple2ListTuple2 tuple_393;
    tuple_393.t0 = level_2;
    tuple_393.t1 = tokens_201;
    if ((tuple_393.t0.tag != Or_)) goto next_956;
    if ((!(tuple_393.t1))) goto next_956;
    if ((tuple_393.t1->head.t0.tag != PipePipe_)) goto next_956;
    struct IntIntTuple2 opLoc_4 = tuple_393.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_206 = tuple_393.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_394;
    tuple_394.t0 = tokens_206;
    tuple_394.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_654 = nextL_1(baseLoc_35, level_2, first_3, (struct Op_){.tag = Or_1}, opLoc_4, tuple_394);
    match_252 = call_654;
    goto end_match_955;
next_956:;
    if ((tuple_393.t0.tag != And_)) goto next_957;
    if ((!(tuple_393.t1))) goto next_957;
    if ((tuple_393.t1->head.t0.tag != AmpAmp_)) goto next_957;
    struct IntIntTuple2 opLoc_5 = tuple_393.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_207 = tuple_393.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_395;
    tuple_395.t0 = tokens_207;
    tuple_395.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_655 = nextL_1(baseLoc_35, level_2, first_3, (struct Op_){.tag = And_1}, opLoc_5, tuple_395);
    match_252 = call_655;
    goto end_match_955;
next_957:;
    if ((tuple_393.t0.tag != Cmp_)) goto next_958;
    if ((!(tuple_393.t1))) goto next_958;
    if ((tuple_393.t1->head.t0.tag != Eq_)) goto next_958;
    struct IntIntTuple2 opLoc_6 = tuple_393.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_208 = tuple_393.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_396;
    tuple_396.t0 = tokens_208;
    tuple_396.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_656 = nextL_1(baseLoc_35, level_2, first_3, (struct Op_){.tag = Eq_1}, opLoc_6, tuple_396);
    match_252 = call_656;
    goto end_match_955;
next_958:;
    if ((tuple_393.t0.tag != Cmp_)) goto next_959;
    if ((!(tuple_393.t1))) goto next_959;
    if ((tuple_393.t1->head.t0.tag != LtGt_)) goto next_959;
    struct IntIntTuple2 opLoc_7 = tuple_393.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_209 = tuple_393.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_397;
    tuple_397.t0 = tokens_209;
    tuple_397.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_657 = nextL_1(baseLoc_35, level_2, first_3, (struct Op_){.tag = Ne_}, opLoc_7, tuple_397);
    match_252 = call_657;
    goto end_match_955;
next_959:;
    if ((tuple_393.t0.tag != Cmp_)) goto next_960;
    if ((!(tuple_393.t1))) goto next_960;
    if ((tuple_393.t1->head.t0.tag != Lt_)) goto next_960;
    struct IntIntTuple2 opLoc_8 = tuple_393.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_210 = tuple_393.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_398;
    tuple_398.t0 = tokens_210;
    tuple_398.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_658 = nextL_1(baseLoc_35, level_2, first_3, (struct Op_){.tag = Lt_1}, opLoc_8, tuple_398);
    match_252 = call_658;
    goto end_match_955;
next_960:;
    if ((tuple_393.t0.tag != Cmp_)) goto next_961;
    if ((!(tuple_393.t1))) goto next_961;
    if ((tuple_393.t1->head.t0.tag != LtEq_)) goto next_961;
    struct IntIntTuple2 opLoc_9 = tuple_393.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_211 = tuple_393.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_399;
    tuple_399.t0 = tokens_211;
    tuple_399.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_659 = nextL_1(baseLoc_35, level_2, first_3, (struct Op_){.tag = Le_}, opLoc_9, tuple_399);
    match_252 = call_659;
    goto end_match_955;
next_961:;
    if ((tuple_393.t0.tag != Cmp_)) goto next_962;
    if ((!(tuple_393.t1))) goto next_962;
    if ((tuple_393.t1->head.t0.tag != Gt_)) goto next_962;
    struct IntIntTuple2 opLoc_10 = tuple_393.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_212 = tuple_393.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_400;
    tuple_400.t0 = tokens_212;
    tuple_400.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_660 = nextL_1(baseLoc_35, level_2, first_3, (struct Op_){.tag = Gt_1}, opLoc_10, tuple_400);
    match_252 = call_660;
    goto end_match_955;
next_962:;
    if ((tuple_393.t0.tag != Cmp_)) goto next_963;
    if ((!(tuple_393.t1))) goto next_963;
    if ((tuple_393.t1->head.t0.tag != GtEq_)) goto next_963;
    struct IntIntTuple2 opLoc_11 = tuple_393.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_213 = tuple_393.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_401;
    tuple_401.t0 = tokens_213;
    tuple_401.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_661 = nextL_1(baseLoc_35, level_2, first_3, (struct Op_){.tag = Ge_}, opLoc_11, tuple_401);
    match_252 = call_661;
    goto end_match_955;
next_963:;
    if ((tuple_393.t0.tag != Pipe_1)) goto next_964;
    if ((!(tuple_393.t1))) goto next_964;
    if ((tuple_393.t1->head.t0.tag != PipeGt_)) goto next_964;
    struct IntIntTuple2 opLoc_12 = tuple_393.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_214 = tuple_393.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_402;
    tuple_402.t0 = tokens_214;
    tuple_402.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_662 = nextL_1(baseLoc_35, level_2, first_3, (struct Op_){.tag = Pipe_2}, opLoc_12, tuple_402);
    match_252 = call_662;
    goto end_match_955;
next_964:;
    if ((tuple_393.t0.tag != Cons_)) goto next_965;
    if ((!(tuple_393.t1))) goto next_965;
    if ((tuple_393.t1->head.t0.tag != ColonColon_)) goto next_965;
    struct IntIntTuple2 opLoc_13 = tuple_393.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_215 = tuple_393.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_403;
    tuple_403.t0 = tokens_215;
    tuple_403.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_663 = nextR_1(baseLoc_35, level_2, first_3, (struct Op_){.tag = Cons_1}, opLoc_13, tuple_403);
    match_252 = call_663;
    goto end_match_955;
next_965:;
    if ((tuple_393.t0.tag != Add_)) goto next_966;
    if ((!(tuple_393.t1))) goto next_966;
    if ((tuple_393.t1->head.t0.tag != Plus_)) goto next_966;
    struct IntIntTuple2 opLoc_14 = tuple_393.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_216 = tuple_393.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_404;
    tuple_404.t0 = tokens_216;
    tuple_404.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_664 = nextL_1(baseLoc_35, level_2, first_3, (struct Op_){.tag = Add_1}, opLoc_14, tuple_404);
    match_252 = call_664;
    goto end_match_955;
next_966:;
    if ((tuple_393.t0.tag != Add_)) goto next_967;
    if ((!(tuple_393.t1))) goto next_967;
    if ((tuple_393.t1->head.t0.tag != Minus_)) goto next_967;
    struct IntIntTuple2 opLoc_15 = tuple_393.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_217 = tuple_393.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_405;
    tuple_405.t0 = tokens_217;
    tuple_405.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_665 = nextL_1(baseLoc_35, level_2, first_3, (struct Op_){.tag = Sub_}, opLoc_15, tuple_405);
    match_252 = call_665;
    goto end_match_955;
next_967:;
    if ((tuple_393.t0.tag != Mul_)) goto next_968;
    if ((!(tuple_393.t1))) goto next_968;
    if ((tuple_393.t1->head.t0.tag != Star_)) goto next_968;
    struct IntIntTuple2 opLoc_16 = tuple_393.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_218 = tuple_393.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_406;
    tuple_406.t0 = tokens_218;
    tuple_406.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_666 = nextL_1(baseLoc_35, level_2, first_3, (struct Op_){.tag = Mul_1}, opLoc_16, tuple_406);
    match_252 = call_666;
    goto end_match_955;
next_968:;
    if ((tuple_393.t0.tag != Mul_)) goto next_969;
    if ((!(tuple_393.t1))) goto next_969;
    if ((tuple_393.t1->head.t0.tag != Slash_)) goto next_969;
    struct IntIntTuple2 opLoc_17 = tuple_393.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_219 = tuple_393.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_407;
    tuple_407.t0 = tokens_219;
    tuple_407.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_667 = nextL_1(baseLoc_35, level_2, first_3, (struct Op_){.tag = Div_}, opLoc_17, tuple_407);
    match_252 = call_667;
    goto end_match_955;
next_969:;
    if ((tuple_393.t0.tag != Mul_)) goto next_970;
    if ((!(tuple_393.t1))) goto next_970;
    if ((tuple_393.t1->head.t0.tag != Percent_)) goto next_970;
    struct IntIntTuple2 opLoc_18 = tuple_393.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_220 = tuple_393.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_408;
    tuple_408.t0 = tokens_220;
    tuple_408.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_668 = nextL_1(baseLoc_35, level_2, first_3, (struct Op_){.tag = Mod_}, opLoc_18, tuple_408);
    match_252 = call_668;
    goto end_match_955;
next_970:;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_409;
    tuple_409.t0 = first_3;
    tuple_409.t1 = tokens_201;
    tuple_409.t2 = errors_135;
    match_252 = tuple_409;
    goto end_match_955;
next_971:;
end_match_955:;
    return match_252;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseOp_1(struct OpLevel_ level_3, struct IntIntTuple2 baseLoc_36, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_169) {
    struct Token_IntIntTuple2Tuple2List* tokens_221 = arg_169.t0;
    struct StringIntIntTuple2Tuple2List* errors_140 = arg_169.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_410;
    tuple_410.t0 = tokens_221;
    tuple_410.t1 = errors_140;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_669 = parseNextLevelOp_1(level_3, baseLoc_36, tuple_410);
    struct AExpr_ first_4 = call_669.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_222 = call_669.t1;
    struct StringIntIntTuple2Tuple2List* errors_141 = call_669.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_411;
    tuple_411.t0 = tokens_222;
    tuple_411.t1 = errors_141;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_670 = parseOps_1(level_3, baseLoc_36, first_4, tuple_411);
    return call_670;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTupleItem_1(struct IntIntTuple2 baseLoc_37, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_170) {
    struct Token_IntIntTuple2Tuple2List* tokens_223 = arg_170.t0;
    struct StringIntIntTuple2Tuple2List* errors_142 = arg_170.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_412;
    tuple_412.t0 = tokens_223;
    tuple_412.t1 = errors_142;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_671 = parseOp_1((struct OpLevel_){.tag = Or_}, baseLoc_37, tuple_412);
    return call_671;
}

struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_77(struct IntIntTuple2 baseLoc_38, struct AExpr_List* acc_23, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_171) {
    struct Token_IntIntTuple2Tuple2List* tokens_225 = arg_171.t0;
    struct StringIntIntTuple2Tuple2List* errors_144 = arg_171.t1;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_253;
    if ((!(tokens_225))) goto next_973;
    if ((tokens_225->head.t0.tag != Comma_)) goto next_973;
    struct Token_IntIntTuple2Tuple2List* tokens_226 = tokens_225->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_413;
    tuple_413.t0 = tokens_226;
    tuple_413.t1 = errors_144;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_672 = parseTupleItem_1(baseLoc_38, tuple_413);
    struct AExpr_ second_6 = call_672.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_227 = call_672.t1;
    struct StringIntIntTuple2Tuple2List* errors_145 = call_672.t2;
    struct AExpr_List* list_79 = (struct AExpr_List*)malloc(sizeof(struct AExpr_List));
    list_79->head = second_6;
    list_79->tail = acc_23;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_414;
    tuple_414.t0 = tokens_227;
    tuple_414.t1 = errors_145;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_673 = go_77(baseLoc_38, list_79, tuple_414);
    match_253 = call_673;
    goto end_match_972;
next_973:;
    struct Token_IntIntTuple2Tuple2List* tokens_228 = tokens_225;
    struct AExpr_List* call_674 = listRev_1(acc_23);
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_415;
    tuple_415.t0 = call_674;
    tuple_415.t1 = tokens_228;
    tuple_415.t2 = errors_144;
    match_253 = tuple_415;
    goto end_match_972;
next_974:;
end_match_972:;
    return match_253;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTuple_1(struct IntIntTuple2 baseLoc_38, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_172) {
    struct Token_IntIntTuple2Tuple2List* tokens_224 = arg_172.t0;
    struct StringIntIntTuple2Tuple2List* errors_143 = arg_172.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_416;
    tuple_416.t0 = tokens_224;
    tuple_416.t1 = errors_143;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_675 = parseTupleItem_1(baseLoc_38, tuple_416);
    struct AExpr_ item_ = call_675.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_229 = call_675.t1;
    struct StringIntIntTuple2Tuple2List* errors_146 = call_675.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_254;
    if ((!(tokens_229))) goto next_976;
    if ((tokens_229->head.t0.tag != Comma_)) goto next_976;
    struct IntIntTuple2 loc_66 = tokens_229->head.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_417;
    tuple_417.t0 = tokens_229;
    tuple_417.t1 = errors_146;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_676 = go_77(baseLoc_38, NULL, tuple_417);
    struct AExpr_List* items_7 = call_676.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_230 = call_676.t1;
    struct StringIntIntTuple2Tuple2List* errors_147 = call_676.t2;
    struct AExpr_List* list_80 = (struct AExpr_List*)malloc(sizeof(struct AExpr_List));
    list_80->head = item_;
    list_80->tail = items_7;
    struct AExpr_ListIntIntTuple2Tuple2 tuple_419;
    tuple_419.t0 = list_80;
    tuple_419.t1 = loc_66;
    struct AExpr_ListIntIntTuple2Tuple2* payload_138 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_138))) = tuple_419;
    struct AExpr_ variant_138 = (struct AExpr_){.tag = TupleLit_1, .TupleLit_1 = payload_138};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_418;
    tuple_418.t0 = variant_138;
    tuple_418.t1 = tokens_230;
    tuple_418.t2 = errors_147;
    match_254 = tuple_418;
    goto end_match_975;
next_976:;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_420;
    tuple_420.t0 = item_;
    tuple_420.t1 = tokens_229;
    tuple_420.t2 = errors_146;
    match_254 = tuple_420;
    goto end_match_975;
next_977:;
end_match_975:;
    return match_254;
}

struct AExpr_ATy_IntIntTuple2Tuple3 {
    struct AExpr_ t0;
    struct ATy_ t1;
    struct IntIntTuple2 t2;
};

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseAnno_1(struct IntIntTuple2 baseLoc_39, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_173) {
    struct Token_IntIntTuple2Tuple2List* tokens_231 = arg_173.t0;
    struct StringIntIntTuple2Tuple2List* errors_148 = arg_173.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_421;
    tuple_421.t0 = tokens_231;
    tuple_421.t1 = errors_148;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_677 = parseTuple_1(baseLoc_39, tuple_421);
    struct AExpr_ body_14 = call_677.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_232 = call_677.t1;
    struct StringIntIntTuple2Tuple2List* errors_149 = call_677.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_255;
    if ((!(tokens_232))) goto next_979;
    if ((tokens_232->head.t0.tag != Colon_)) goto next_979;
    struct IntIntTuple2 loc_67 = tokens_232->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_233 = tokens_232->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_422;
    tuple_422.t0 = tokens_233;
    tuple_422.t1 = errors_149;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_678 = parseTy_1(baseLoc_39, tuple_422);
    struct ATy_ ty_54 = call_678.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_234 = call_678.t1;
    struct StringIntIntTuple2Tuple2List* errors_150 = call_678.t2;
    struct AExpr_ATy_IntIntTuple2Tuple3 tuple_424;
    tuple_424.t0 = body_14;
    tuple_424.t1 = ty_54;
    tuple_424.t2 = loc_67;
    struct AExpr_ATy_IntIntTuple2Tuple3* payload_139 = (struct AExpr_ATy_IntIntTuple2Tuple3*)malloc(sizeof(struct AExpr_ATy_IntIntTuple2Tuple3));
    (*(((struct AExpr_ATy_IntIntTuple2Tuple3*)payload_139))) = tuple_424;
    struct AExpr_ variant_139 = (struct AExpr_){.tag = Anno_1, .Anno_1 = payload_139};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_423;
    tuple_423.t0 = variant_139;
    tuple_423.t1 = tokens_234;
    tuple_423.t2 = errors_150;
    match_255 = tuple_423;
    goto end_match_978;
next_979:;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_425;
    tuple_425.t0 = body_14;
    tuple_425.t1 = tokens_232;
    tuple_425.t2 = errors_149;
    match_255 = tuple_425;
    goto end_match_978;
next_980:;
end_match_978:;
    return match_255;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseExpr_1(struct IntIntTuple2 baseLoc_40, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_174) {
    struct Token_IntIntTuple2Tuple2List* tokens_235 = arg_174.t0;
    struct StringIntIntTuple2Tuple2List* errors_151 = arg_174.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_426;
    tuple_426.t0 = tokens_235;
    tuple_426.t1 = errors_151;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_679 = parseAnno_1(baseLoc_40, tuple_426);
    return call_679;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseStmt_1(struct IntIntTuple2 baseLoc_41, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_175) {
    struct Token_IntIntTuple2Tuple2List* tokens_236 = arg_175.t0;
    struct StringIntIntTuple2Tuple2List* errors_152 = arg_175.t1;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_256;
    if ((!(tokens_236))) goto next_982;
    if ((tokens_236->head.t0.tag != Let_)) goto next_982;
    struct IntIntTuple2 letLoc_2 = tokens_236->head.t1;
    if ((!(tokens_236->tail))) goto next_982;
    if ((tokens_236->tail->head.t0.tag != Rec_)) goto next_982;
    struct Token_IntIntTuple2Tuple2List* tokens_237 = tokens_236->tail->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_427;
    tuple_427.t0 = tokens_237;
    tuple_427.t1 = errors_152;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_680 = parseLet_1(letLoc_2, tuple_427);
    match_256 = call_680;
    goto end_match_981;
next_982:;
    if ((!(tokens_236))) goto next_983;
    if ((tokens_236->head.t0.tag != Let_)) goto next_983;
    struct IntIntTuple2 letLoc_3 = tokens_236->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_238 = tokens_236->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_428;
    tuple_428.t0 = tokens_238;
    tuple_428.t1 = errors_152;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_681 = parseLet_1(letLoc_3, tuple_428);
    match_256 = call_681;
    goto end_match_981;
next_983:;
    if ((!(tokens_236))) goto next_984;
    if ((tokens_236->head.t0.tag != Type_)) goto next_984;
    struct IntIntTuple2 typeLoc_1 = tokens_236->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_239 = tokens_236->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_429;
    tuple_429.t0 = tokens_239;
    tuple_429.t1 = errors_152;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_682 = parseTyDecl_1(typeLoc_1, tuple_429);
    match_256 = call_682;
    goto end_match_981;
next_984:;
    if ((!(tokens_236))) goto next_985;
    if ((tokens_236->head.t0.tag != Open_)) goto next_985;
    struct IntIntTuple2 typeLoc_2 = tokens_236->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_240 = tokens_236->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_430;
    tuple_430.t0 = tokens_240;
    tuple_430.t1 = errors_152;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_683 = parseOpen_1(typeLoc_2, tuple_430);
    match_256 = call_683;
    goto end_match_981;
next_985:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_431;
    tuple_431.t0 = tokens_236;
    tuple_431.t1 = errors_152;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_684 = parseExpr_1(baseLoc_41, tuple_431);
    match_256 = call_684;
    goto end_match_981;
next_986:;
end_match_981:;
    return match_256;
}

struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_66(struct IntIntTuple2 baseLoc_42, struct AExpr_List* acc_24, struct IntIntTuple2 alignLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_176) {
    struct Token_IntIntTuple2Tuple2List* tokens_242 = arg_176.t0;
    struct StringIntIntTuple2Tuple2List* errors_154 = arg_176.t1;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_257;
    if ((!(tokens_242))) goto next_988;
    if ((tokens_242->head.t0.tag != Semi_)) goto next_988;
    struct IntIntTuple2 semiLoc_ = tokens_242->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_243 = tokens_242->tail;
    int call_685 = locInside_(alignLoc_, semiLoc_);
    if ((!(call_685))) goto next_988;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_432;
    tuple_432.t0 = tokens_243;
    tuple_432.t1 = errors_154;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_686 = parseStmt_1(baseLoc_42, tuple_432);
    struct AExpr_ expr_16 = call_686.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_244 = call_686.t1;
    struct StringIntIntTuple2Tuple2List* errors_155 = call_686.t2;
    struct AExpr_List* list_81 = (struct AExpr_List*)malloc(sizeof(struct AExpr_List));
    list_81->head = expr_16;
    list_81->tail = acc_24;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_433;
    tuple_433.t0 = tokens_244;
    tuple_433.t1 = errors_155;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_687 = go_66(baseLoc_42, list_81, alignLoc_, tuple_433);
    match_257 = call_687;
    goto end_match_987;
next_988:;
    int match_258;
    struct IntIntTuple2 call_688 = nextLoc_1(tokens_242);
    int call_689 = locIsSameColumn_(alignLoc_, call_688);
    if ((!(call_689))) goto next_992;
    int call_690 = leadsExpr_1(tokens_242);
    match_258 = call_690;
    goto end_match_991;
next_992:;
    if (call_689) goto next_993;
    match_258 = 0;
    goto end_match_991;
next_993:;
    exit(1);
end_match_991:;
    if ((!(match_258))) goto next_989;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_434;
    tuple_434.t0 = tokens_242;
    tuple_434.t1 = errors_154;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_691 = parseStmt_1(baseLoc_42, tuple_434);
    struct AExpr_ expr_17 = call_691.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_245 = call_691.t1;
    struct StringIntIntTuple2Tuple2List* errors_156 = call_691.t2;
    struct AExpr_List* list_82 = (struct AExpr_List*)malloc(sizeof(struct AExpr_List));
    list_82->head = expr_17;
    list_82->tail = acc_24;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_435;
    tuple_435.t0 = tokens_245;
    tuple_435.t1 = errors_156;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_692 = go_66(baseLoc_42, list_82, alignLoc_, tuple_435);
    match_257 = call_692;
    goto end_match_987;
next_989:;
    struct AExpr_List* call_693 = listRev_1(acc_24);
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_436;
    tuple_436.t0 = call_693;
    tuple_436.t1 = tokens_242;
    tuple_436.t2 = errors_154;
    match_257 = tuple_436;
    goto end_match_987;
next_990:;
end_match_987:;
    return match_257;
}

struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseStmts_1(struct IntIntTuple2 baseLoc_42, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_177) {
    struct Token_IntIntTuple2Tuple2List* tokens_241 = arg_177.t0;
    struct StringIntIntTuple2Tuple2List* errors_153 = arg_177.t1;
    struct IntIntTuple2 call_694 = nextLoc_1(tokens_241);
    struct IntIntTuple2 alignLoc_1 = call_694;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_259;
    int call_695 = locInside_(baseLoc_42, alignLoc_1);
    if ((!(call_695))) goto next_995;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_437;
    tuple_437.t0 = tokens_241;
    tuple_437.t1 = errors_153;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_696 = go_66(baseLoc_42, NULL, alignLoc_1, tuple_437);
    match_259 = call_696;
    goto end_match_994;
next_995:;
    if (call_695) goto next_996;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_438;
    tuple_438.t0 = NULL;
    tuple_438.t1 = tokens_241;
    tuple_438.t2 = errors_153;
    match_259 = tuple_438;
    goto end_match_994;
next_996:;
    exit(1);
end_match_994:;
    return match_259;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseSemi_1(struct IntIntTuple2 baseLoc_43, struct IntIntTuple2 mainLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_178) {
    struct Token_IntIntTuple2Tuple2List* tokens_246 = arg_178.t0;
    struct StringIntIntTuple2Tuple2List* errors_157 = arg_178.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_439;
    tuple_439.t0 = tokens_246;
    tuple_439.t1 = errors_157;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_697 = parseStmts_1(baseLoc_43, tuple_439);
    struct AExpr_List* items_8 = call_697.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_247 = call_697.t1;
    struct StringIntIntTuple2Tuple2List* errors_158 = call_697.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_260;
    if ((!((!(items_8))))) goto next_998;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_440;
    tuple_440.t0 = tokens_247;
    tuple_440.t1 = errors_158;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_698 = parseExprError_1((struct String){.str = "Expected statements", .len = 19}, tuple_440);
    match_260 = call_698;
    goto end_match_997;
next_998:;
    if ((!(items_8))) goto next_999;
    struct AExpr_ item_1 = items_8->head;
    if ((!((!(items_8->tail))))) goto next_999;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_441;
    tuple_441.t0 = item_1;
    tuple_441.t1 = tokens_247;
    tuple_441.t2 = errors_158;
    match_260 = tuple_441;
    goto end_match_997;
next_999:;
    struct AExpr_ListIntIntTuple2Tuple2 tuple_443;
    tuple_443.t0 = items_8;
    tuple_443.t1 = mainLoc_;
    struct AExpr_ListIntIntTuple2Tuple2* payload_140 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_140))) = tuple_443;
    struct AExpr_ variant_140 = (struct AExpr_){.tag = Semi_1, .Semi_1 = payload_140};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_442;
    tuple_442.t0 = variant_140;
    tuple_442.t1 = tokens_247;
    tuple_442.t2 = errors_158;
    match_260 = tuple_442;
    goto end_match_997;
next_1000:;
end_match_997:;
    return match_260;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTopLevel_1(struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_179) {
    struct Token_IntIntTuple2Tuple2List* tokens_248 = arg_179.t0;
    struct StringIntIntTuple2Tuple2List* errors_159 = arg_179.t1;
    struct IntIntTuple2 tuple_444;
    tuple_444.t0 = 0;
    tuple_444.t1 = 0;
    struct IntIntTuple2 topLoc_ = tuple_444;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_261;
    if ((!((!(tokens_248))))) goto next_1002;
    struct AExpr_ListIntIntTuple2Tuple2 tuple_446;
    tuple_446.t0 = NULL;
    tuple_446.t1 = topLoc_;
    struct AExpr_ListIntIntTuple2Tuple2* payload_141 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_141))) = tuple_446;
    struct AExpr_ variant_141 = (struct AExpr_){.tag = TupleLit_1, .TupleLit_1 = payload_141};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_445;
    tuple_445.t0 = variant_141;
    tuple_445.t1 = tokens_248;
    tuple_445.t2 = errors_159;
    match_261 = tuple_445;
    goto end_match_1001;
next_1002:;
    if ((!(tokens_248))) goto next_1003;
    if ((tokens_248->head.t0.tag != Module_)) goto next_1003;
    struct IntIntTuple2 moduleLoc_ = tokens_248->head.t1;
    if ((!(tokens_248->tail))) goto next_1003;
    if ((tokens_248->tail->head.t0.tag != Rec_)) goto next_1003;
    if ((!(tokens_248->tail->tail))) goto next_1003;
    if ((tokens_248->tail->tail->head.t0.tag != Ident_)) goto next_1003;
    if ((!(tokens_248->tail->tail->tail))) goto next_1003;
    if ((tokens_248->tail->tail->tail->head.t0.tag != Dot_)) goto next_1003;
    if ((!(tokens_248->tail->tail->tail->tail))) goto next_1003;
    if ((tokens_248->tail->tail->tail->tail->head.t0.tag != Ident_)) goto next_1003;
    struct Token_IntIntTuple2Tuple2List* tokens_249 = tokens_248->tail->tail->tail->tail->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_447;
    tuple_447.t0 = tokens_249;
    tuple_447.t1 = errors_159;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_699 = parseSemi_1(moduleLoc_, moduleLoc_, tuple_447);
    match_261 = call_699;
    goto end_match_1001;
next_1003:;
    if ((!(tokens_248))) goto next_1004;
    if ((tokens_248->head.t0.tag != Module_)) goto next_1004;
    struct IntIntTuple2 moduleLoc_1 = tokens_248->head.t1;
    if ((!(tokens_248->tail))) goto next_1004;
    if ((tokens_248->tail->head.t0.tag != Rec_)) goto next_1004;
    if ((!(tokens_248->tail->tail))) goto next_1004;
    if ((tokens_248->tail->tail->head.t0.tag != Ident_)) goto next_1004;
    struct Token_IntIntTuple2Tuple2List* tokens_250 = tokens_248->tail->tail->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_448;
    tuple_448.t0 = tokens_250;
    tuple_448.t1 = errors_159;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_700 = parseSemi_1(moduleLoc_1, moduleLoc_1, tuple_448);
    match_261 = call_700;
    goto end_match_1001;
next_1004:;
    if ((!(tokens_248))) goto next_1005;
    if ((tokens_248->head.t0.tag != Module_)) goto next_1005;
    struct IntIntTuple2 moduleLoc_2 = tokens_248->head.t1;
    if ((!(tokens_248->tail))) goto next_1005;
    if ((tokens_248->tail->head.t0.tag != Ident_)) goto next_1005;
    struct Token_IntIntTuple2Tuple2List* tokens_251 = tokens_248->tail->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_449;
    tuple_449.t0 = tokens_251;
    tuple_449.t1 = errors_159;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_701 = parseSemi_1(moduleLoc_2, moduleLoc_2, tuple_449);
    match_261 = call_701;
    goto end_match_1001;
next_1005:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_450;
    tuple_450.t0 = tokens_248;
    tuple_450.t1 = errors_159;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_702 = parseSemi_1(topLoc_, topLoc_, tuple_450);
    match_261 = call_702;
    goto end_match_1001;
next_1006:;
end_match_1001:;
    return match_261;
}

struct AExpr_StringIntIntTuple2Tuple2ListTuple2 {
    struct AExpr_ t0;
    struct StringIntIntTuple2Tuple2List* t1;
};

struct AExpr_StringIntIntTuple2Tuple2ListTuple2 parse_(struct Token_IntIntTuple2Tuple2List* tokens_252) {
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_451;
    tuple_451.t0 = tokens_252;
    tuple_451.t1 = NULL;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_703 = parseTopLevel_1(tuple_451);
    struct AExpr_ expr_18 = call_703.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_253 = call_703.t1;
    struct StringIntIntTuple2Tuple2List* errors_160 = call_703.t2;
    struct StringIntIntTuple2Tuple2List* match_262;
    if ((!((!(tokens_253))))) goto next_1008;
    match_262 = errors_160;
    goto end_match_1007;
next_1008:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_452;
    tuple_452.t0 = tokens_253;
    tuple_452.t1 = errors_160;
    struct StringIntIntTuple2Tuple2List* call_704 = parseNewError_1((struct String){.str = "Expected eof", .len = 12}, tuple_452);
    match_262 = call_704;
    goto end_match_1007;
next_1009:;
end_match_1007:;
    struct StringIntIntTuple2Tuple2List* errors_161 = match_262;
    struct AExpr_StringIntIntTuple2Tuple2ListTuple2 tuple_453;
    tuple_453.t0 = expr_18;
    tuple_453.t1 = errors_161;
    return tuple_453;
}

struct HPrim_ opToPrim_(struct Op_ op_2) {
    struct HPrim_ match_263;
    if ((op_2.tag != Add_1)) goto next_1011;
    match_263 = (struct HPrim_){.tag = Add_3};
    goto end_match_1010;
next_1011:;
    if ((op_2.tag != Sub_)) goto next_1012;
    match_263 = (struct HPrim_){.tag = Sub_1};
    goto end_match_1010;
next_1012:;
    if ((op_2.tag != Mul_1)) goto next_1013;
    match_263 = (struct HPrim_){.tag = Mul_2};
    goto end_match_1010;
next_1013:;
    if ((op_2.tag != Div_)) goto next_1014;
    match_263 = (struct HPrim_){.tag = Div_1};
    goto end_match_1010;
next_1014:;
    if ((op_2.tag != Mod_)) goto next_1015;
    match_263 = (struct HPrim_){.tag = Mod_1};
    goto end_match_1010;
next_1015:;
    if ((op_2.tag != Eq_1)) goto next_1016;
    match_263 = (struct HPrim_){.tag = Eq_3};
    goto end_match_1010;
next_1016:;
    if ((op_2.tag != Lt_1)) goto next_1017;
    match_263 = (struct HPrim_){.tag = Lt_2};
    goto end_match_1010;
next_1017:;
    if ((op_2.tag != Cons_1)) goto next_1019;
    match_263 = (struct HPrim_){.tag = Cons_4};
    goto end_match_1010;
next_1019:;
    if ((op_2.tag != Ne_)) goto next_1020;
    goto match_body_1018;
next_1020:;
    if ((op_2.tag != Le_)) goto next_1021;
    goto match_body_1018;
next_1021:;
    if ((op_2.tag != Gt_1)) goto next_1022;
    goto match_body_1018;
next_1022:;
    if ((op_2.tag != Ge_)) goto next_1023;
    goto match_body_1018;
next_1023:;
    if ((op_2.tag != And_1)) goto next_1024;
    goto match_body_1018;
next_1024:;
    if ((op_2.tag != Or_1)) goto next_1025;
    goto match_body_1018;
next_1025:;
    if ((op_2.tag != App_)) goto next_1026;
    goto match_body_1018;
next_1026:;
    if ((op_2.tag != Pipe_2)) goto next_1027;
    goto match_body_1018;
match_body_1018:;
    struct Op_HPrim_Fun1 call_705 = failwithf_3((struct String){.str = "NEVER: %A", .len = 9});
    struct HPrim_ app_67 = call_705.fun(call_705.env, op_2);
    match_263 = app_67;
    goto end_match_1010;
next_1027:;
end_match_1010:;
    return match_263;
}

struct APat_ go_40(struct IntIntTuple2 loc_68, struct APat_List* pats_5) {
    struct APat_ match_264;
    if ((!((!(pats_5))))) goto next_1029;
    struct APat_ListIntIntTuple2Tuple2 tuple_454;
    tuple_454.t0 = NULL;
    tuple_454.t1 = loc_68;
    struct APat_ListIntIntTuple2Tuple2* payload_142 = (struct APat_ListIntIntTuple2Tuple2*)malloc(sizeof(struct APat_ListIntIntTuple2Tuple2));
    (*(((struct APat_ListIntIntTuple2Tuple2*)payload_142))) = tuple_454;
    struct APat_ variant_142 = (struct APat_){.tag = ListLit_, .ListLit_ = payload_142};
    match_264 = variant_142;
    goto end_match_1028;
next_1029:;
    if ((!(pats_5))) goto next_1030;
    struct APat_ head_3 = pats_5->head;
    struct APat_List* tail_3 = pats_5->tail;
    struct APat_ call_706 = go_40(loc_68, tail_3);
    struct APat_ tail_4 = call_706;
    struct APat_APat_IntIntTuple2Tuple3 tuple_455;
    tuple_455.t0 = head_3;
    tuple_455.t1 = tail_4;
    tuple_455.t2 = loc_68;
    struct APat_APat_IntIntTuple2Tuple3* payload_143 = (struct APat_APat_IntIntTuple2Tuple3*)malloc(sizeof(struct APat_APat_IntIntTuple2Tuple3));
    (*(((struct APat_APat_IntIntTuple2Tuple3*)payload_143))) = tuple_455;
    struct APat_ variant_143 = (struct APat_){.tag = Cons_2, .Cons_2 = payload_143};
    match_264 = variant_143;
    goto end_match_1028;
next_1030:;
    exit(1);
end_match_1028:;
    return match_264;
}

struct APat_ desugarListLitPat_(struct APat_List* pats_4, struct IntIntTuple2 loc_68) {
    int call_707 = listIsEmpty_2(pats_4);
    milone_assert((!(call_707)), 64, 2);
    int call_708 = 0;
    struct APat_ call_709 = go_40(loc_68, pats_4);
    return call_709;
}

struct AExpr_ go_41(struct IntIntTuple2 loc_69, struct AExpr_List* items_10) {
    struct AExpr_ match_265;
    if ((!((!(items_10))))) goto next_1032;
    struct AExpr_ListIntIntTuple2Tuple2 tuple_456;
    tuple_456.t0 = NULL;
    tuple_456.t1 = loc_69;
    struct AExpr_ListIntIntTuple2Tuple2* payload_144 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_144))) = tuple_456;
    struct AExpr_ variant_144 = (struct AExpr_){.tag = ListLit_1, .ListLit_1 = payload_144};
    match_265 = variant_144;
    goto end_match_1031;
next_1032:;
    if ((!(items_10))) goto next_1033;
    struct AExpr_ head_4 = items_10->head;
    struct AExpr_List* tail_5 = items_10->tail;
    struct AExpr_ call_710 = go_41(loc_69, tail_5);
    struct AExpr_ tail_6 = call_710;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_457;
    tuple_457.t0 = (struct Op_){.tag = Cons_1};
    tuple_457.t1 = head_4;
    tuple_457.t2 = tail_6;
    tuple_457.t3 = loc_69;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_145 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_145))) = tuple_457;
    struct AExpr_ variant_145 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_145};
    match_265 = variant_145;
    goto end_match_1031;
next_1033:;
    exit(1);
end_match_1031:;
    return match_265;
}

struct AExpr_ desugarListLitExpr_(struct AExpr_List* items_9, struct IntIntTuple2 loc_69) {
    int call_711 = listIsEmpty_1(items_9);
    milone_assert((!(call_711)), 79, 2);
    int call_712 = 0;
    struct AExpr_ call_713 = go_41(loc_69, items_9);
    return call_713;
}

struct AExpr_ desugarIf_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct AExpr_ cond_2, struct AExpr_ body_15, struct AExpr_ alt_2, struct IntIntTuple2 loc_70) {
    struct AExpr_ match_266;
    if ((alt_2.tag != Missing_2)) goto next_1035;
    struct AExpr_ call_714 = axUnit_(loc_70);
    match_266 = call_714;
    goto end_match_1034;
next_1035:;
    match_266 = alt_2;
    goto end_match_1034;
next_1036:;
end_match_1034:;
    struct AExpr_ alt_3 = match_266;
    struct APat_ call_715 = apTrue_(litTrue_, loc_70);
    struct AExpr_ call_716 = axTrue_(litTrue_, loc_70);
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4 tuple_458;
    tuple_458.t0 = call_715;
    tuple_458.t1 = call_716;
    tuple_458.t2 = body_15;
    tuple_458.t3 = loc_70;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4* payload_146 = (struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct APat_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)payload_146))) = tuple_458;
    struct AArm_ variant_146 = (struct AArm_){.tag = AArm_, .AArm_ = payload_146};
    struct APat_ call_717 = apFalse_(litFalse_, loc_70);
    struct AExpr_ call_718 = axTrue_(litTrue_, loc_70);
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4 tuple_459;
    tuple_459.t0 = call_717;
    tuple_459.t1 = call_718;
    tuple_459.t2 = alt_3;
    tuple_459.t3 = loc_70;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4* payload_147 = (struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct APat_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)payload_147))) = tuple_459;
    struct AArm_ variant_147 = (struct AArm_){.tag = AArm_, .AArm_ = payload_147};
    struct AArm_List* list_84 = (struct AArm_List*)malloc(sizeof(struct AArm_List));
    list_84->head = variant_147;
    list_84->tail = NULL;
    struct AArm_List* list_83 = (struct AArm_List*)malloc(sizeof(struct AArm_List));
    list_83->head = variant_146;
    list_83->tail = list_84;
    struct AArm_List* arms_4 = list_83;
    struct AExpr_AArm_ListIntIntTuple2Tuple3 tuple_460;
    tuple_460.t0 = cond_2;
    tuple_460.t1 = arms_4;
    tuple_460.t2 = loc_70;
    struct AExpr_AArm_ListIntIntTuple2Tuple3* payload_148 = (struct AExpr_AArm_ListIntIntTuple2Tuple3*)malloc(sizeof(struct AExpr_AArm_ListIntIntTuple2Tuple3));
    (*(((struct AExpr_AArm_ListIntIntTuple2Tuple3*)payload_148))) = tuple_460;
    struct AExpr_ variant_148 = (struct AExpr_){.tag = Match_1, .Match_1 = payload_148};
    return variant_148;
}

struct AExpr_ desugarFun_(struct APat_List* pats_6, struct AExpr_ body_16, struct IntIntTuple2 loc_71) {
    struct String ident_26 = (struct String){.str = "fun", .len = 3};
    struct StringAPat_ListIntIntTuple2Tuple3 tuple_461;
    tuple_461.t0 = ident_26;
    tuple_461.t1 = pats_6;
    tuple_461.t2 = loc_71;
    struct StringAPat_ListIntIntTuple2Tuple3* payload_149 = (struct StringAPat_ListIntIntTuple2Tuple3*)malloc(sizeof(struct StringAPat_ListIntIntTuple2Tuple3));
    (*(((struct StringAPat_ListIntIntTuple2Tuple3*)payload_149))) = tuple_461;
    struct APat_ variant_149 = (struct APat_){.tag = Fun_2, .Fun_2 = payload_149};
    struct APat_ pat_23 = variant_149;
    struct StringIntIntTuple2Tuple2 tuple_462;
    tuple_462.t0 = ident_26;
    tuple_462.t1 = loc_71;
    struct StringIntIntTuple2Tuple2* payload_150 = (struct StringIntIntTuple2Tuple2*)malloc(sizeof(struct StringIntIntTuple2Tuple2));
    (*(((struct StringIntIntTuple2Tuple2*)payload_150))) = tuple_462;
    struct AExpr_ variant_150 = (struct AExpr_){.tag = Ident_2, .Ident_2 = payload_150};
    struct AExpr_ next_12 = variant_150;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4 tuple_463;
    tuple_463.t0 = pat_23;
    tuple_463.t1 = body_16;
    tuple_463.t2 = next_12;
    tuple_463.t3 = loc_71;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4* payload_151 = (struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct APat_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)payload_151))) = tuple_463;
    struct AExpr_ variant_151 = (struct AExpr_){.tag = Let_1, .Let_1 = payload_151};
    return variant_151;
}

struct AExpr_ desugarUniNeg_(struct AExpr_ arg_4, struct IntIntTuple2 loc_72) {
    int* payload_152 = (int*)malloc(sizeof(int));
    (*(((int*)payload_152))) = 0;
    struct Lit_ variant_152 = (struct Lit_){.tag = Int_, .Int_ = payload_152};
    struct Lit_IntIntTuple2Tuple2 tuple_464;
    tuple_464.t0 = variant_152;
    tuple_464.t1 = loc_72;
    struct Lit_IntIntTuple2Tuple2* payload_153 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_153))) = tuple_464;
    struct AExpr_ variant_153 = (struct AExpr_){.tag = Lit_1, .Lit_1 = payload_153};
    struct AExpr_ zero_ = variant_153;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_465;
    tuple_465.t0 = (struct Op_){.tag = Sub_};
    tuple_465.t1 = zero_;
    tuple_465.t2 = arg_4;
    tuple_465.t3 = loc_72;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_154 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_154))) = tuple_465;
    struct AExpr_ variant_154 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_154};
    return variant_154;
}

struct AExpr_ desugarBinNe_(struct Lit_ litFalse_, struct AExpr_ l_19, struct AExpr_ r_33, struct IntIntTuple2 loc_73) {
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_466;
    tuple_466.t0 = (struct Op_){.tag = Eq_1};
    tuple_466.t1 = l_19;
    tuple_466.t2 = r_33;
    tuple_466.t3 = loc_73;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_155 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_155))) = tuple_466;
    struct AExpr_ variant_155 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_155};
    struct AExpr_ eqExpr_ = variant_155;
    struct AExpr_ call_719 = axNot_(litFalse_, eqExpr_, loc_73);
    return call_719;
}

struct AExpr_ desugarBinLe_(struct Lit_ litFalse_, struct AExpr_ l_20, struct AExpr_ r_34, struct IntIntTuple2 loc_74) {
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_467;
    tuple_467.t0 = (struct Op_){.tag = Lt_1};
    tuple_467.t1 = r_34;
    tuple_467.t2 = l_20;
    tuple_467.t3 = loc_74;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_156 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_156))) = tuple_467;
    struct AExpr_ variant_156 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_156};
    struct AExpr_ ltExpr_ = variant_156;
    struct AExpr_ call_720 = axNot_(litFalse_, ltExpr_, loc_74);
    return call_720;
}

struct AExpr_ desugarBinGt_(struct AExpr_ l_21, struct AExpr_ r_35, struct IntIntTuple2 loc_75) {
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_468;
    tuple_468.t0 = (struct Op_){.tag = Lt_1};
    tuple_468.t1 = r_35;
    tuple_468.t2 = l_21;
    tuple_468.t3 = loc_75;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_157 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_157))) = tuple_468;
    struct AExpr_ variant_157 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_157};
    return variant_157;
}

struct AExpr_ desugarBinGe_(struct Lit_ litFalse_, struct AExpr_ l_22, struct AExpr_ r_36, struct IntIntTuple2 loc_76) {
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_469;
    tuple_469.t0 = (struct Op_){.tag = Lt_1};
    tuple_469.t1 = l_22;
    tuple_469.t2 = r_36;
    tuple_469.t3 = loc_76;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_158 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_158))) = tuple_469;
    struct AExpr_ variant_158 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_158};
    struct AExpr_ ltExpr_1 = variant_158;
    struct AExpr_ call_721 = axNot_(litFalse_, ltExpr_1, loc_76);
    return call_721;
}

struct AExpr_ desugarBinAnd_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct AExpr_ l_23, struct AExpr_ r_37, struct IntIntTuple2 loc_77) {
    struct AExpr_ call_722 = axFalse_(litFalse_, loc_77);
    struct AExpr_ call_723 = desugarIf_(litFalse_, litTrue_, l_23, r_37, call_722, loc_77);
    return call_723;
}

struct AExpr_ desugarBinOr_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct AExpr_ l_24, struct AExpr_ r_38, struct IntIntTuple2 loc_78) {
    struct AExpr_ call_724 = axTrue_(litTrue_, loc_78);
    struct AExpr_ call_725 = desugarIf_(litFalse_, litTrue_, l_24, call_724, r_38, loc_78);
    return call_725;
}

struct AExpr_ desugarBinPipe_(struct AExpr_ l_25, struct AExpr_ r_39, struct IntIntTuple2 loc_79) {
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_470;
    tuple_470.t0 = (struct Op_){.tag = App_};
    tuple_470.t1 = r_39;
    tuple_470.t2 = l_25;
    tuple_470.t3 = loc_79;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_159 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_159))) = tuple_470;
    struct AExpr_ variant_159 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_159};
    return variant_159;
}

struct BoolAExpr_Tuple2 {
    int t0;
    struct AExpr_ t1;
};

struct BoolAExpr_Tuple2 tryDesugarIndexRange_(struct AExpr_ expr_19, struct IntIntTuple2 loc_80) {
    struct BoolAExpr_Tuple2 match_267;
    if ((expr_19.tag != Index_)) goto next_1038;
    struct AExpr_ s_8 = (*(expr_19.Index_)).t0;
    if (((*(expr_19.Index_)).t1.tag != Range_)) goto next_1038;
    if ((!((*((*(expr_19.Index_)).t1.Range_)).t0))) goto next_1038;
    struct AExpr_ l_26 = (*((*(expr_19.Index_)).t1.Range_)).t0->head;
    if ((!((*((*(expr_19.Index_)).t1.Range_)).t0->tail))) goto next_1038;
    struct AExpr_ r_40 = (*((*(expr_19.Index_)).t1.Range_)).t0->tail->head;
    if ((!((!((*((*(expr_19.Index_)).t1.Range_)).t0->tail->tail))))) goto next_1038;
    struct StringIntIntTuple2Tuple2 tuple_472;
    tuple_472.t0 = (struct String){.str = "String", .len = 6};
    tuple_472.t1 = loc_80;
    struct StringIntIntTuple2Tuple2* payload_160 = (struct StringIntIntTuple2Tuple2*)malloc(sizeof(struct StringIntIntTuple2Tuple2));
    (*(((struct StringIntIntTuple2Tuple2*)payload_160))) = tuple_472;
    struct AExpr_ variant_160 = (struct AExpr_){.tag = Ident_2, .Ident_2 = payload_160};
    struct AExpr_StringIntIntTuple2Tuple3 tuple_471;
    tuple_471.t0 = variant_160;
    tuple_471.t1 = (struct String){.str = "getSlice", .len = 8};
    tuple_471.t2 = loc_80;
    struct AExpr_StringIntIntTuple2Tuple3* payload_161 = (struct AExpr_StringIntIntTuple2Tuple3*)malloc(sizeof(struct AExpr_StringIntIntTuple2Tuple3));
    (*(((struct AExpr_StringIntIntTuple2Tuple3*)payload_161))) = tuple_471;
    struct AExpr_ variant_161 = (struct AExpr_){.tag = Nav_1, .Nav_1 = payload_161};
    struct AExpr_ getSlice_ = variant_161;
    struct AExpr_ call_726 = axApp3_(getSlice_, l_26, r_40, s_8, loc_80);
    struct BoolAExpr_Tuple2 tuple_473;
    tuple_473.t0 = 1;
    tuple_473.t1 = call_726;
    match_267 = tuple_473;
    goto end_match_1037;
next_1038:;
    struct BoolAExpr_Tuple2 tuple_474;
    tuple_474.t0 = 0;
    tuple_474.t1 = expr_19;
    match_267 = tuple_474;
    goto end_match_1037;
next_1039:;
end_match_1037:;
    return match_267;
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
    struct ALet_ match_268;
    if ((pat_24.tag != Anno_)) goto next_1041;
    struct APat_ pat_25 = (*(pat_24.Anno_)).t0;
    struct ATy_ annoTy_ = (*(pat_24.Anno_)).t1;
    struct IntIntTuple2 annoLoc_ = (*(pat_24.Anno_)).t2;
    struct AExpr_ATy_IntIntTuple2Tuple3 tuple_475;
    tuple_475.t0 = body_17;
    tuple_475.t1 = annoTy_;
    tuple_475.t2 = annoLoc_;
    struct AExpr_ATy_IntIntTuple2Tuple3* payload_162 = (struct AExpr_ATy_IntIntTuple2Tuple3*)malloc(sizeof(struct AExpr_ATy_IntIntTuple2Tuple3));
    (*(((struct AExpr_ATy_IntIntTuple2Tuple3*)payload_162))) = tuple_475;
    struct AExpr_ variant_162 = (struct AExpr_){.tag = Anno_1, .Anno_1 = payload_162};
    struct AExpr_ body_18 = variant_162;
    struct ALet_ call_727 = desugarLet_(pat_25, body_18, next_13, loc_81);
    match_268 = call_727;
    goto end_match_1040;
next_1041:;
    if ((pat_24.tag != Fun_2)) goto next_1042;
    struct String ident_27 = (*(pat_24.Fun_2)).t0;
    struct APat_List* args_8 = (*(pat_24.Fun_2)).t1;
    struct StringAPat_ListAExpr_AExpr_IntIntTuple2Tuple5 tuple_476;
    tuple_476.t0 = ident_27;
    tuple_476.t1 = args_8;
    tuple_476.t2 = body_17;
    tuple_476.t3 = next_13;
    tuple_476.t4 = loc_81;
    struct StringAPat_ListAExpr_AExpr_IntIntTuple2Tuple5* payload_163 = (struct StringAPat_ListAExpr_AExpr_IntIntTuple2Tuple5*)malloc(sizeof(struct StringAPat_ListAExpr_AExpr_IntIntTuple2Tuple5));
    (*(((struct StringAPat_ListAExpr_AExpr_IntIntTuple2Tuple5*)payload_163))) = tuple_476;
    struct ALet_ variant_163 = (struct ALet_){.tag = LetFun_, .LetFun_ = payload_163};
    match_268 = variant_163;
    goto end_match_1040;
next_1042:;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4 tuple_477;
    tuple_477.t0 = pat_24;
    tuple_477.t1 = body_17;
    tuple_477.t2 = next_13;
    tuple_477.t3 = loc_81;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4* payload_164 = (struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct APat_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)payload_164))) = tuple_477;
    struct ALet_ variant_164 = (struct ALet_){.tag = LetVal_, .LetVal_ = payload_164};
    match_268 = variant_164;
    goto end_match_1040;
next_1043:;
end_match_1040:;
    return match_268;
}

struct Ty_NameCtx_Tuple2 fun_10(void* env_7, struct ATy_NameCtx_Tuple2 arg_28) {
    struct Ty_NameCtx_Tuple2 call_728 = onTy_(arg_28);
    return call_728;
}

struct Ty_NameCtx_Tuple2 fun_11(void* env_8, struct ATy_NameCtx_Tuple2 arg_29) {
    struct Ty_NameCtx_Tuple2 call_729 = onTy_(arg_29);
    return call_729;
}

struct Ty_NameCtx_Tuple2 onTy_(struct ATy_NameCtx_Tuple2 arg_180) {
    struct ATy_ ty_55 = arg_180.t0;
    struct NameCtx_ nameCtx_1 = arg_180.t1;
    struct Ty_NameCtx_Tuple2 match_269;
    if ((ty_55.tag != Missing_)) goto next_1045;
    struct IntIntTuple2 loc_82 = (*(ty_55.Missing_));
    struct IntIntTuple2* payload_165 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_165))) = loc_82;
    struct Ty_ variant_165 = (struct Ty_){.tag = Error_1, .Error_1 = payload_165};
    struct Ty_NameCtx_Tuple2 tuple_478;
    tuple_478.t0 = variant_165;
    tuple_478.t1 = nameCtx_1;
    match_269 = tuple_478;
    goto end_match_1044;
next_1045:;
    if ((ty_55.tag != App_1)) goto next_1046;
    struct String ident_28 = (*(ty_55.App_1)).t0;
    struct ATy_List* argTys_2 = (*(ty_55.App_1)).t1;
    struct IntNameCtx_Tuple2 call_730 = nameCtxAdd_1(ident_28, nameCtx_1);
    int tySerial_1 = call_730.t0;
    struct NameCtx_ nameCtx_2 = call_730.t1;
    void* box_7 = (void*)malloc(sizeof(int));
    (*(((int*)box_7))) = 0;
    void* env_43 = box_7;
    struct ATy_NameCtx_Tuple2Ty_NameCtx_Tuple2Fun1 fun_47 = (struct ATy_NameCtx_Tuple2Ty_NameCtx_Tuple2Fun1){.fun = fun_10, .env = env_43};
    struct ATy_ListNameCtx_Tuple2 tuple_479;
    tuple_479.t0 = argTys_2;
    tuple_479.t1 = nameCtx_2;
    struct Ty_ListNameCtx_Tuple2 call_731 = stMap_5(fun_47, tuple_479);
    struct Ty_List* argTys_3 = call_731.t0;
    struct NameCtx_ nameCtx_3 = call_731.t1;
    struct Ty_ call_732 = tyRef_(tySerial_1, argTys_3);
    struct Ty_NameCtx_Tuple2 tuple_480;
    tuple_480.t0 = call_732;
    tuple_480.t1 = nameCtx_3;
    match_269 = tuple_480;
    goto end_match_1044;
next_1046:;
    if ((ty_55.tag != Suffix_)) goto next_1047;
    struct ATy_ lTy_3 = (*(ty_55.Suffix_)).t0;
    struct String ident_29 = (*(ty_55.Suffix_)).t1;
    struct ATy_NameCtx_Tuple2 tuple_481;
    tuple_481.t0 = lTy_3;
    tuple_481.t1 = nameCtx_1;
    struct Ty_NameCtx_Tuple2 call_733 = onTy_(tuple_481);
    struct Ty_ lTy_4 = call_733.t0;
    struct NameCtx_ nameCtx_4 = call_733.t1;
    struct IntNameCtx_Tuple2 call_734 = nameCtxAdd_1(ident_29, nameCtx_4);
    int tySerial_2 = call_734.t0;
    struct NameCtx_ nameCtx_5 = call_734.t1;
    struct Ty_List* list_85 = (struct Ty_List*)malloc(sizeof(struct Ty_List));
    list_85->head = lTy_4;
    list_85->tail = NULL;
    struct Ty_ call_735 = tyRef_(tySerial_2, list_85);
    struct Ty_NameCtx_Tuple2 tuple_482;
    tuple_482.t0 = call_735;
    tuple_482.t1 = nameCtx_5;
    match_269 = tuple_482;
    goto end_match_1044;
next_1047:;
    if ((ty_55.tag != Tuple_)) goto next_1048;
    struct ATy_List* itemTys_2 = (*(ty_55.Tuple_)).t0;
    void* box_8 = (void*)malloc(sizeof(int));
    (*(((int*)box_8))) = 0;
    void* env_44 = box_8;
    struct ATy_NameCtx_Tuple2Ty_NameCtx_Tuple2Fun1 fun_48 = (struct ATy_NameCtx_Tuple2Ty_NameCtx_Tuple2Fun1){.fun = fun_11, .env = env_44};
    struct ATy_ListNameCtx_Tuple2 tuple_483;
    tuple_483.t0 = itemTys_2;
    tuple_483.t1 = nameCtx_1;
    struct Ty_ListNameCtx_Tuple2 call_736 = stMap_5(fun_48, tuple_483);
    struct Ty_List* itemTys_3 = call_736.t0;
    struct NameCtx_ nameCtx_6 = call_736.t1;
    struct Ty_ call_737 = tyTuple_(itemTys_3);
    struct Ty_NameCtx_Tuple2 tuple_484;
    tuple_484.t0 = call_737;
    tuple_484.t1 = nameCtx_6;
    match_269 = tuple_484;
    goto end_match_1044;
next_1048:;
    if ((ty_55.tag != Fun_1)) goto next_1049;
    struct ATy_ sTy_2 = (*(ty_55.Fun_1)).t0;
    struct ATy_ tTy_2 = (*(ty_55.Fun_1)).t1;
    struct ATy_NameCtx_Tuple2 tuple_485;
    tuple_485.t0 = sTy_2;
    tuple_485.t1 = nameCtx_1;
    struct Ty_NameCtx_Tuple2 call_738 = onTy_(tuple_485);
    struct Ty_ sTy_3 = call_738.t0;
    struct NameCtx_ nameCtx_7 = call_738.t1;
    struct ATy_NameCtx_Tuple2 tuple_486;
    tuple_486.t0 = tTy_2;
    tuple_486.t1 = nameCtx_7;
    struct Ty_NameCtx_Tuple2 call_739 = onTy_(tuple_486);
    struct Ty_ tTy_3 = call_739.t0;
    struct NameCtx_ nameCtx_8 = call_739.t1;
    struct Ty_ call_740 = tyFun_(sTy_3, tTy_3);
    struct Ty_NameCtx_Tuple2 tuple_487;
    tuple_487.t0 = call_740;
    tuple_487.t1 = nameCtx_8;
    match_269 = tuple_487;
    goto end_match_1044;
next_1049:;
    exit(1);
end_match_1044:;
    return match_269;
}

struct Ty_Tuple1 {
    struct Ty_ t0;
};

struct HPat_NameCtx_Tuple2 fun_12(void* env_9, struct APat_NameCtx_Tuple2 arg_30) {
    struct Ty_ arg_31 = (*(((struct Ty_Tuple1*)env_9))).t0;
    struct HPat_NameCtx_Tuple2 call_741 = onPat_(arg_31, arg_30);
    return call_741;
}

struct HPat_NameCtx_Tuple2 fun_13(void* env_10, struct APat_NameCtx_Tuple2 arg_32) {
    struct Ty_ arg_33 = (*(((struct Ty_Tuple1*)env_10))).t0;
    struct HPat_NameCtx_Tuple2 call_742 = onPat_(arg_33, arg_32);
    return call_742;
}

struct HPat_NameCtx_Tuple2 onPat_(struct Ty_ noTy_, struct APat_NameCtx_Tuple2 arg_181) {
    struct APat_ pat_26 = arg_181.t0;
    struct NameCtx_ nameCtx_9 = arg_181.t1;
    struct HPat_NameCtx_Tuple2 match_270;
    if ((pat_26.tag != Missing_1)) goto next_1051;
    int loc_83 = (*(pat_26.Missing_1)).t1;
    struct IntHPat_NameCtx_Tuple2Fun1 call_743 = failwithf_2((struct String){.str = "Missing pattern %A", .len = 18});
    struct HPat_NameCtx_Tuple2 app_68 = call_743.fun(call_743.env, loc_83);
    match_270 = app_68;
    goto end_match_1050;
next_1051:;
    if ((pat_26.tag != Lit_)) goto next_1052;
    struct Lit_ lit_9 = (*(pat_26.Lit_)).t0;
    struct IntIntTuple2 loc_84 = (*(pat_26.Lit_)).t1;
    struct Lit_IntIntTuple2Tuple2 tuple_489;
    tuple_489.t0 = lit_9;
    tuple_489.t1 = loc_84;
    struct Lit_IntIntTuple2Tuple2* payload_166 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_166))) = tuple_489;
    struct HPat_ variant_166 = (struct HPat_){.tag = Lit_2, .Lit_2 = payload_166};
    struct HPat_NameCtx_Tuple2 tuple_488;
    tuple_488.t0 = variant_166;
    tuple_488.t1 = nameCtx_9;
    match_270 = tuple_488;
    goto end_match_1050;
next_1052:;
    if ((pat_26.tag != Ident_1)) goto next_1053;
    struct String ident_30 = (*(pat_26.Ident_1)).t0;
    struct IntIntTuple2 loc_85 = (*(pat_26.Ident_1)).t1;
    struct IntNameCtx_Tuple2 call_744 = nameCtxAdd_1(ident_30, nameCtx_9);
    int serial_9 = call_744.t0;
    struct NameCtx_ nameCtx_10 = call_744.t1;
    struct IntTy_IntIntTuple2Tuple3 tuple_491;
    tuple_491.t0 = serial_9;
    tuple_491.t1 = noTy_;
    tuple_491.t2 = loc_85;
    struct IntTy_IntIntTuple2Tuple3* payload_167 = (struct IntTy_IntIntTuple2Tuple3*)malloc(sizeof(struct IntTy_IntIntTuple2Tuple3));
    (*(((struct IntTy_IntIntTuple2Tuple3*)payload_167))) = tuple_491;
    struct HPat_ variant_167 = (struct HPat_){.tag = Ref_1, .Ref_1 = payload_167};
    struct HPat_NameCtx_Tuple2 tuple_490;
    tuple_490.t0 = variant_167;
    tuple_490.t1 = nameCtx_10;
    match_270 = tuple_490;
    goto end_match_1050;
next_1053:;
    if ((pat_26.tag != ListLit_)) goto next_1054;
    if ((!((!((*(pat_26.ListLit_)).t0))))) goto next_1054;
    struct IntIntTuple2 loc_86 = (*(pat_26.ListLit_)).t1;
    struct HPat_ call_745 = patNil_(noTy_, loc_86);
    struct HPat_NameCtx_Tuple2 tuple_492;
    tuple_492.t0 = call_745;
    tuple_492.t1 = nameCtx_9;
    match_270 = tuple_492;
    goto end_match_1050;
next_1054:;
    if ((pat_26.tag != ListLit_)) goto next_1055;
    struct APat_List* pats_7 = (*(pat_26.ListLit_)).t0;
    struct IntIntTuple2 loc_87 = (*(pat_26.ListLit_)).t1;
    struct APat_ call_746 = desugarListLitPat_(pats_7, loc_87);
    struct APat_ pat_27 = call_746;
    struct APat_NameCtx_Tuple2 tuple_493;
    tuple_493.t0 = pat_27;
    tuple_493.t1 = nameCtx_9;
    struct HPat_NameCtx_Tuple2 call_747 = onPat_(noTy_, tuple_493);
    match_270 = call_747;
    goto end_match_1050;
next_1055:;
    if ((pat_26.tag != Nav_)) goto next_1056;
    struct APat_ l_27 = (*(pat_26.Nav_)).t0;
    struct String r_41 = (*(pat_26.Nav_)).t1;
    struct IntIntTuple2 loc_88 = (*(pat_26.Nav_)).t2;
    struct APat_NameCtx_Tuple2 tuple_494;
    tuple_494.t0 = l_27;
    tuple_494.t1 = nameCtx_9;
    struct HPat_NameCtx_Tuple2 call_748 = onPat_(noTy_, tuple_494);
    struct HPat_ l_28 = call_748.t0;
    struct NameCtx_ nameCtx_11 = call_748.t1;
    struct HPat_StringTy_IntIntTuple2Tuple4 tuple_496;
    tuple_496.t0 = l_28;
    tuple_496.t1 = r_41;
    tuple_496.t2 = noTy_;
    tuple_496.t3 = loc_88;
    struct HPat_StringTy_IntIntTuple2Tuple4* payload_168 = (struct HPat_StringTy_IntIntTuple2Tuple4*)malloc(sizeof(struct HPat_StringTy_IntIntTuple2Tuple4));
    (*(((struct HPat_StringTy_IntIntTuple2Tuple4*)payload_168))) = tuple_496;
    struct HPat_ variant_168 = (struct HPat_){.tag = Nav_2, .Nav_2 = payload_168};
    struct HPat_NameCtx_Tuple2 tuple_495;
    tuple_495.t0 = variant_168;
    tuple_495.t1 = nameCtx_11;
    match_270 = tuple_495;
    goto end_match_1050;
next_1056:;
    if ((pat_26.tag != Call_)) goto next_1057;
    struct APat_ calleePat_1 = (*(pat_26.Call_)).t0;
    struct APat_List* argPats_1 = (*(pat_26.Call_)).t1;
    struct IntIntTuple2 loc_89 = (*(pat_26.Call_)).t2;
    struct APat_NameCtx_Tuple2 tuple_497;
    tuple_497.t0 = calleePat_1;
    tuple_497.t1 = nameCtx_9;
    struct HPat_NameCtx_Tuple2 call_749 = onPat_(noTy_, tuple_497);
    struct HPat_ calleePat_2 = call_749.t0;
    struct NameCtx_ nameCtx_12 = call_749.t1;
    struct Ty_Tuple1 tuple_498;
    tuple_498.t0 = noTy_;
    void* box_9 = (void*)malloc(sizeof(struct Ty_Tuple1));
    (*(((struct Ty_Tuple1*)box_9))) = tuple_498;
    void* env_45 = box_9;
    struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1 fun_49 = (struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1){.fun = fun_12, .env = env_45};
    struct APat_ListNameCtx_Tuple2 tuple_499;
    tuple_499.t0 = argPats_1;
    tuple_499.t1 = nameCtx_12;
    struct HPat_ListNameCtx_Tuple2 call_750 = stMap_2(fun_49, tuple_499);
    struct HPat_List* argPats_2 = call_750.t0;
    struct NameCtx_ nameCtx_13 = call_750.t1;
    struct HPat_HPat_ListTy_IntIntTuple2Tuple4 tuple_501;
    tuple_501.t0 = calleePat_2;
    tuple_501.t1 = argPats_2;
    tuple_501.t2 = noTy_;
    tuple_501.t3 = loc_89;
    struct HPat_HPat_ListTy_IntIntTuple2Tuple4* payload_169 = (struct HPat_HPat_ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct HPat_HPat_ListTy_IntIntTuple2Tuple4));
    (*(((struct HPat_HPat_ListTy_IntIntTuple2Tuple4*)payload_169))) = tuple_501;
    struct HPat_ variant_169 = (struct HPat_){.tag = Call_1, .Call_1 = payload_169};
    struct HPat_NameCtx_Tuple2 tuple_500;
    tuple_500.t0 = variant_169;
    tuple_500.t1 = nameCtx_13;
    match_270 = tuple_500;
    goto end_match_1050;
next_1057:;
    if ((pat_26.tag != Cons_2)) goto next_1058;
    struct APat_ head_5 = (*(pat_26.Cons_2)).t0;
    struct APat_ tail_7 = (*(pat_26.Cons_2)).t1;
    struct IntIntTuple2 loc_90 = (*(pat_26.Cons_2)).t2;
    struct APat_NameCtx_Tuple2 tuple_502;
    tuple_502.t0 = head_5;
    tuple_502.t1 = nameCtx_9;
    struct HPat_NameCtx_Tuple2 call_751 = onPat_(noTy_, tuple_502);
    struct HPat_ head_6 = call_751.t0;
    struct NameCtx_ nameCtx_14 = call_751.t1;
    struct APat_NameCtx_Tuple2 tuple_503;
    tuple_503.t0 = tail_7;
    tuple_503.t1 = nameCtx_14;
    struct HPat_NameCtx_Tuple2 call_752 = onPat_(noTy_, tuple_503);
    struct HPat_ tail_8 = call_752.t0;
    struct NameCtx_ nameCtx_15 = call_752.t1;
    struct HPat_HPat_Ty_IntIntTuple2Tuple4 tuple_505;
    tuple_505.t0 = head_6;
    tuple_505.t1 = tail_8;
    tuple_505.t2 = noTy_;
    tuple_505.t3 = loc_90;
    struct HPat_HPat_Ty_IntIntTuple2Tuple4* payload_170 = (struct HPat_HPat_Ty_IntIntTuple2Tuple4*)malloc(sizeof(struct HPat_HPat_Ty_IntIntTuple2Tuple4));
    (*(((struct HPat_HPat_Ty_IntIntTuple2Tuple4*)payload_170))) = tuple_505;
    struct HPat_ variant_170 = (struct HPat_){.tag = Cons_3, .Cons_3 = payload_170};
    struct HPat_NameCtx_Tuple2 tuple_504;
    tuple_504.t0 = variant_170;
    tuple_504.t1 = nameCtx_15;
    match_270 = tuple_504;
    goto end_match_1050;
next_1058:;
    if ((pat_26.tag != TupleLit_)) goto next_1059;
    struct APat_List* pats_8 = (*(pat_26.TupleLit_)).t0;
    struct IntIntTuple2 loc_91 = (*(pat_26.TupleLit_)).t1;
    struct Ty_Tuple1 tuple_506;
    tuple_506.t0 = noTy_;
    void* box_10 = (void*)malloc(sizeof(struct Ty_Tuple1));
    (*(((struct Ty_Tuple1*)box_10))) = tuple_506;
    void* env_46 = box_10;
    struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1 fun_50 = (struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1){.fun = fun_13, .env = env_46};
    struct APat_ListNameCtx_Tuple2 tuple_507;
    tuple_507.t0 = pats_8;
    tuple_507.t1 = nameCtx_9;
    struct HPat_ListNameCtx_Tuple2 call_753 = stMap_2(fun_50, tuple_507);
    struct HPat_List* pats_9 = call_753.t0;
    struct NameCtx_ nameCtx_16 = call_753.t1;
    struct HPat_ListTy_IntIntTuple2Tuple3 tuple_509;
    tuple_509.t0 = pats_9;
    tuple_509.t1 = noTy_;
    tuple_509.t2 = loc_91;
    struct HPat_ListTy_IntIntTuple2Tuple3* payload_171 = (struct HPat_ListTy_IntIntTuple2Tuple3*)malloc(sizeof(struct HPat_ListTy_IntIntTuple2Tuple3));
    (*(((struct HPat_ListTy_IntIntTuple2Tuple3*)payload_171))) = tuple_509;
    struct HPat_ variant_171 = (struct HPat_){.tag = Tuple_2, .Tuple_2 = payload_171};
    struct HPat_NameCtx_Tuple2 tuple_508;
    tuple_508.t0 = variant_171;
    tuple_508.t1 = nameCtx_16;
    match_270 = tuple_508;
    goto end_match_1050;
next_1059:;
    if ((pat_26.tag != As_1)) goto next_1060;
    struct APat_ pat_28 = (*(pat_26.As_1)).t0;
    struct String ident_31 = (*(pat_26.As_1)).t1;
    struct IntIntTuple2 loc_92 = (*(pat_26.As_1)).t2;
    struct IntNameCtx_Tuple2 call_754 = nameCtxAdd_1(ident_31, nameCtx_9);
    int serial_10 = call_754.t0;
    struct NameCtx_ nameCtx_17 = call_754.t1;
    struct APat_NameCtx_Tuple2 tuple_510;
    tuple_510.t0 = pat_28;
    tuple_510.t1 = nameCtx_17;
    struct HPat_NameCtx_Tuple2 call_755 = onPat_(noTy_, tuple_510);
    struct HPat_ pat_29 = call_755.t0;
    struct NameCtx_ nameCtx_18 = call_755.t1;
    struct HPat_IntIntIntTuple2Tuple3 tuple_512;
    tuple_512.t0 = pat_29;
    tuple_512.t1 = serial_10;
    tuple_512.t2 = loc_92;
    struct HPat_IntIntIntTuple2Tuple3* payload_172 = (struct HPat_IntIntIntTuple2Tuple3*)malloc(sizeof(struct HPat_IntIntIntTuple2Tuple3));
    (*(((struct HPat_IntIntIntTuple2Tuple3*)payload_172))) = tuple_512;
    struct HPat_ variant_172 = (struct HPat_){.tag = As_2, .As_2 = payload_172};
    struct HPat_NameCtx_Tuple2 tuple_511;
    tuple_511.t0 = variant_172;
    tuple_511.t1 = nameCtx_18;
    match_270 = tuple_511;
    goto end_match_1050;
next_1060:;
    if ((pat_26.tag != Anno_)) goto next_1061;
    struct APat_ pat_30 = (*(pat_26.Anno_)).t0;
    struct ATy_ ty_56 = (*(pat_26.Anno_)).t1;
    struct IntIntTuple2 loc_93 = (*(pat_26.Anno_)).t2;
    struct APat_NameCtx_Tuple2 tuple_513;
    tuple_513.t0 = pat_30;
    tuple_513.t1 = nameCtx_9;
    struct HPat_NameCtx_Tuple2 call_756 = onPat_(noTy_, tuple_513);
    struct HPat_ pat_31 = call_756.t0;
    struct NameCtx_ nameCtx_19 = call_756.t1;
    struct ATy_NameCtx_Tuple2 tuple_514;
    tuple_514.t0 = ty_56;
    tuple_514.t1 = nameCtx_19;
    struct Ty_NameCtx_Tuple2 call_757 = onTy_(tuple_514);
    struct Ty_ ty_57 = call_757.t0;
    struct NameCtx_ nameCtx_20 = call_757.t1;
    struct HPat_Ty_IntIntTuple2Tuple3 tuple_516;
    tuple_516.t0 = pat_31;
    tuple_516.t1 = ty_57;
    tuple_516.t2 = loc_93;
    struct HPat_Ty_IntIntTuple2Tuple3* payload_173 = (struct HPat_Ty_IntIntTuple2Tuple3*)malloc(sizeof(struct HPat_Ty_IntIntTuple2Tuple3));
    (*(((struct HPat_Ty_IntIntTuple2Tuple3*)payload_173))) = tuple_516;
    struct HPat_ variant_173 = (struct HPat_){.tag = Anno_2, .Anno_2 = payload_173};
    struct HPat_NameCtx_Tuple2 tuple_515;
    tuple_515.t0 = variant_173;
    tuple_515.t1 = nameCtx_20;
    match_270 = tuple_515;
    goto end_match_1050;
next_1061:;
    if ((pat_26.tag != Or_2)) goto next_1062;
    struct APat_ l_29 = (*(pat_26.Or_2)).t0;
    struct APat_ r_42 = (*(pat_26.Or_2)).t1;
    struct IntIntTuple2 loc_94 = (*(pat_26.Or_2)).t2;
    struct APat_NameCtx_Tuple2 tuple_517;
    tuple_517.t0 = l_29;
    tuple_517.t1 = nameCtx_9;
    struct HPat_NameCtx_Tuple2 call_758 = onPat_(noTy_, tuple_517);
    struct HPat_ l_30 = call_758.t0;
    struct NameCtx_ nameCtx_21 = call_758.t1;
    struct APat_NameCtx_Tuple2 tuple_518;
    tuple_518.t0 = r_42;
    tuple_518.t1 = nameCtx_21;
    struct HPat_NameCtx_Tuple2 call_759 = onPat_(noTy_, tuple_518);
    struct HPat_ r_43 = call_759.t0;
    struct NameCtx_ nameCtx_22 = call_759.t1;
    struct HPat_HPat_Ty_IntIntTuple2Tuple4 tuple_520;
    tuple_520.t0 = l_30;
    tuple_520.t1 = r_43;
    tuple_520.t2 = noTy_;
    tuple_520.t3 = loc_94;
    struct HPat_HPat_Ty_IntIntTuple2Tuple4* payload_174 = (struct HPat_HPat_Ty_IntIntTuple2Tuple4*)malloc(sizeof(struct HPat_HPat_Ty_IntIntTuple2Tuple4));
    (*(((struct HPat_HPat_Ty_IntIntTuple2Tuple4*)payload_174))) = tuple_520;
    struct HPat_ variant_174 = (struct HPat_){.tag = Or_3, .Or_3 = payload_174};
    struct HPat_NameCtx_Tuple2 tuple_519;
    tuple_519.t0 = variant_174;
    tuple_519.t1 = nameCtx_22;
    match_270 = tuple_519;
    goto end_match_1050;
next_1062:;
    if ((pat_26.tag != Fun_2)) goto next_1063;
    struct IntIntTuple2 loc_95 = (*(pat_26.Fun_2)).t2;
    struct IntIntTuple2HPat_NameCtx_Tuple2Fun1 call_760 = failwithf_1((struct String){.str = "Invalid occurrence of fun pattern: %A", .len = 37});
    struct HPat_NameCtx_Tuple2 app_69 = call_760.fun(call_760.env, loc_95);
    match_270 = app_69;
    goto end_match_1050;
next_1063:;
    exit(1);
end_match_1050:;
    return match_270;
}

struct HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2 onArm_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, struct AArm_NameCtx_Tuple2 arg_182) {
    struct APat_ pat_32 = (*(arg_182.t0.AArm_)).t0;
    struct AExpr_ guard_4 = (*(arg_182.t0.AArm_)).t1;
    struct AExpr_ body_20 = (*(arg_182.t0.AArm_)).t2;
    struct IntIntTuple2 loc_103 = (*(arg_182.t0.AArm_)).t3;
    struct NameCtx_ nameCtx_25 = arg_182.t1;
    struct APat_NameCtx_Tuple2 tuple_521;
    tuple_521.t0 = pat_32;
    tuple_521.t1 = nameCtx_25;
    struct HPat_NameCtx_Tuple2 call_761 = onPat_(noTy_, tuple_521);
    struct HPat_ pat_33 = call_761.t0;
    struct NameCtx_ nameCtx_26 = call_761.t1;
    struct HExpr_NameCtx_Tuple2 match_271;
    if ((guard_4.tag != Missing_2)) goto next_1065;
    struct HExpr_ call_762 = hxTrue_(litTrue_, loc_103);
    struct HExpr_NameCtx_Tuple2 tuple_522;
    tuple_522.t0 = call_762;
    tuple_522.t1 = nameCtx_26;
    match_271 = tuple_522;
    goto end_match_1064;
next_1065:;
    struct AExpr_NameCtx_Tuple2 tuple_523;
    tuple_523.t0 = guard_4;
    tuple_523.t1 = nameCtx_26;
    struct HExpr_NameCtx_Tuple2 call_763 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_523);
    match_271 = call_763;
    goto end_match_1064;
next_1066:;
end_match_1064:;
    struct HExpr_ guard_5 = match_271.t0;
    struct NameCtx_ nameCtx_27 = match_271.t1;
    struct AExpr_NameCtx_Tuple2 tuple_524;
    tuple_524.t0 = body_20;
    tuple_524.t1 = nameCtx_27;
    struct HExpr_NameCtx_Tuple2 call_764 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_524);
    struct HExpr_ body_21 = call_764.t0;
    struct NameCtx_ nameCtx_28 = call_764.t1;
    struct HPat_HExpr_HExpr_Tuple3 tuple_526;
    tuple_526.t0 = pat_33;
    tuple_526.t1 = guard_5;
    tuple_526.t2 = body_21;
    struct HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2 tuple_525;
    tuple_525.t0 = tuple_526;
    tuple_525.t1 = nameCtx_28;
    return tuple_525;
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

struct HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2 fun_14(void* env_11, struct AArm_NameCtx_Tuple2 arg_34) {
    struct Lit_ arg_35 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_11))).t0;
    struct Lit_ arg_36 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_11))).t1;
    struct Ty_ arg_37 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_11))).t2;
    struct Ty_ arg_38 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_11))).t3;
    struct Ty_ arg_39 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_11))).t4;
    struct Ty_ arg_40 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_11))).t5;
    struct Ty_ arg_41 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_11))).t6;
    struct Ty_ arg_42 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_11))).t7;
    struct HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2 call_765 = onArm_(arg_35, arg_36, arg_37, arg_38, arg_39, arg_40, arg_41, arg_42, arg_34);
    return call_765;
}

struct HExpr_NameCtx_Tuple2 fun_15(void* env_12, struct AExpr_NameCtx_Tuple2 arg_43) {
    struct Lit_ arg_44 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_12))).t0;
    struct Lit_ arg_45 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_12))).t1;
    struct Ty_ arg_46 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_12))).t2;
    struct Ty_ arg_47 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_12))).t3;
    struct Ty_ arg_48 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_12))).t4;
    struct Ty_ arg_49 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_12))).t5;
    struct Ty_ arg_50 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_12))).t6;
    struct Ty_ arg_51 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_12))).t7;
    struct HExpr_NameCtx_Tuple2 call_766 = onExpr_(arg_44, arg_45, arg_46, arg_47, arg_48, arg_49, arg_50, arg_51, arg_43);
    return call_766;
}

struct HExpr_NameCtx_Tuple2 fun_16(void* env_13, struct AExpr_NameCtx_Tuple2 arg_52) {
    struct Lit_ arg_53 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_13))).t0;
    struct Lit_ arg_54 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_13))).t1;
    struct Ty_ arg_55 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_13))).t2;
    struct Ty_ arg_56 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_13))).t3;
    struct Ty_ arg_57 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_13))).t4;
    struct Ty_ arg_58 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_13))).t5;
    struct Ty_ arg_59 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_13))).t6;
    struct Ty_ arg_60 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_13))).t7;
    struct HExpr_NameCtx_Tuple2 call_767 = onExpr_(arg_53, arg_54, arg_55, arg_56, arg_57, arg_58, arg_59, arg_60, arg_52);
    return call_767;
}

struct HPat_NameCtx_Tuple2 fun_17(void* env_14, struct APat_NameCtx_Tuple2 arg_61) {
    struct Ty_ arg_62 = (*(((struct Ty_Tuple1*)env_14))).t0;
    struct HPat_NameCtx_Tuple2 call_768 = onPat_(arg_62, arg_61);
    return call_768;
}

struct BoolTy_NameCtx_Tuple3 {
    int t0;
    struct Ty_ t1;
    struct NameCtx_ t2;
};

struct StringIntBoolTy_Tuple4NameCtx_Tuple2 onVariant_(struct Ty_ tyUnit_, struct AVariant_NameCtx_Tuple2 arg_183) {
    struct String ident_36 = (*(arg_183.t0.AVariant_)).t0;
    struct ATy_List* payloadTy_1 = (*(arg_183.t0.AVariant_)).t1;
    struct IntIntTuple2 _variantLoc_ = (*(arg_183.t0.AVariant_)).t2;
    struct NameCtx_ nameCtx_51 = arg_183.t1;
    struct IntNameCtx_Tuple2 call_769 = nameCtxAdd_1(ident_36, nameCtx_51);
    int serial_14 = call_769.t0;
    struct NameCtx_ nameCtx_52 = call_769.t1;
    struct BoolTy_NameCtx_Tuple3 match_272;
    if ((!(payloadTy_1))) goto next_1068;
    struct ATy_ ty_62 = payloadTy_1->head;
    if ((!((!(payloadTy_1->tail))))) goto next_1068;
    struct ATy_NameCtx_Tuple2 tuple_527;
    tuple_527.t0 = ty_62;
    tuple_527.t1 = nameCtx_52;
    struct Ty_NameCtx_Tuple2 call_770 = onTy_(tuple_527);
    struct Ty_ ty_63 = call_770.t0;
    struct NameCtx_ nameCtx_54 = call_770.t1;
    struct BoolTy_NameCtx_Tuple3 tuple_528;
    tuple_528.t0 = 1;
    tuple_528.t1 = ty_63;
    tuple_528.t2 = nameCtx_54;
    match_272 = tuple_528;
    goto end_match_1067;
next_1068:;
    if ((!((!(payloadTy_1))))) goto next_1069;
    struct BoolTy_NameCtx_Tuple3 tuple_529;
    tuple_529.t0 = 0;
    tuple_529.t1 = tyUnit_;
    tuple_529.t2 = nameCtx_52;
    match_272 = tuple_529;
    goto end_match_1067;
next_1069:;
    exit(1);
end_match_1067:;
    int hasPayload_ = match_272.t0;
    struct Ty_ payloadTy_2 = match_272.t1;
    struct NameCtx_ nameCtx_53 = match_272.t2;
    struct StringIntBoolTy_Tuple4 tuple_531;
    tuple_531.t0 = ident_36;
    tuple_531.t1 = serial_14;
    tuple_531.t2 = hasPayload_;
    tuple_531.t3 = payloadTy_2;
    struct StringIntBoolTy_Tuple4NameCtx_Tuple2 tuple_530;
    tuple_530.t0 = tuple_531;
    tuple_530.t1 = nameCtx_53;
    return tuple_530;
}

struct StringIntBoolTy_Tuple4NameCtx_Tuple2 fun_18(void* env_15, struct AVariant_NameCtx_Tuple2 arg_63) {
    struct Ty_ arg_64 = (*(((struct Ty_Tuple1*)env_15))).t0;
    struct StringIntBoolTy_Tuple4NameCtx_Tuple2 call_771 = onVariant_(arg_64, arg_63);
    return call_771;
}

struct StringStringIntBoolTy_Tuple4ListIntIntTuple2Tuple3 {
    struct String t0;
    struct StringIntBoolTy_Tuple4List* t1;
    struct IntIntTuple2 t2;
};

struct HExpr_NameCtx_Tuple2 onExpr_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, struct AExpr_NameCtx_Tuple2 arg_184) {
    struct AExpr_ expr_20 = arg_184.t0;
    struct NameCtx_ nameCtx_23 = arg_184.t1;
    struct HExpr_NameCtx_Tuple2 match_273;
    if ((expr_20.tag != Missing_2)) goto next_1071;
    struct IntIntTuple2 loc_96 = (*(expr_20.Missing_2));
    struct StringIntIntTuple2Tuple2 tuple_533;
    tuple_533.t0 = (struct String){.str = "Missing expression", .len = 18};
    tuple_533.t1 = loc_96;
    struct StringIntIntTuple2Tuple2* payload_175 = (struct StringIntIntTuple2Tuple2*)malloc(sizeof(struct StringIntIntTuple2Tuple2));
    (*(((struct StringIntIntTuple2Tuple2*)payload_175))) = tuple_533;
    struct HExpr_ variant_175 = (struct HExpr_){.tag = Error_2, .Error_2 = payload_175};
    struct HExpr_NameCtx_Tuple2 tuple_532;
    tuple_532.t0 = variant_175;
    tuple_532.t1 = nameCtx_23;
    match_273 = tuple_532;
    goto end_match_1070;
next_1071:;
    if ((expr_20.tag != Lit_1)) goto next_1072;
    struct Lit_ lit_10 = (*(expr_20.Lit_1)).t0;
    struct IntIntTuple2 loc_97 = (*(expr_20.Lit_1)).t1;
    struct Lit_IntIntTuple2Tuple2 tuple_535;
    tuple_535.t0 = lit_10;
    tuple_535.t1 = loc_97;
    struct Lit_IntIntTuple2Tuple2* payload_176 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_176))) = tuple_535;
    struct HExpr_ variant_176 = (struct HExpr_){.tag = Lit_3, .Lit_3 = payload_176};
    struct HExpr_NameCtx_Tuple2 tuple_534;
    tuple_534.t0 = variant_176;
    tuple_534.t1 = nameCtx_23;
    match_273 = tuple_534;
    goto end_match_1070;
next_1072:;
    if ((expr_20.tag != Ident_2)) goto next_1073;
    struct String ident_32 = (*(expr_20.Ident_2)).t0;
    struct IntIntTuple2 loc_98 = (*(expr_20.Ident_2)).t1;
    struct IntNameCtx_Tuple2 call_772 = nameCtxAdd_1(ident_32, nameCtx_23);
    int serial_11 = call_772.t0;
    struct NameCtx_ nameCtx_24 = call_772.t1;
    struct IntTy_IntIntTuple2Tuple3 tuple_537;
    tuple_537.t0 = serial_11;
    tuple_537.t1 = noTy_;
    tuple_537.t2 = loc_98;
    struct IntTy_IntIntTuple2Tuple3* payload_177 = (struct IntTy_IntIntTuple2Tuple3*)malloc(sizeof(struct IntTy_IntIntTuple2Tuple3));
    (*(((struct IntTy_IntIntTuple2Tuple3*)payload_177))) = tuple_537;
    struct HExpr_ variant_177 = (struct HExpr_){.tag = Ref_2, .Ref_2 = payload_177};
    struct HExpr_NameCtx_Tuple2 tuple_536;
    tuple_536.t0 = variant_177;
    tuple_536.t1 = nameCtx_24;
    match_273 = tuple_536;
    goto end_match_1070;
next_1073:;
    if ((expr_20.tag != ListLit_1)) goto next_1074;
    if ((!((!((*(expr_20.ListLit_1)).t0))))) goto next_1074;
    struct IntIntTuple2 loc_99 = (*(expr_20.ListLit_1)).t1;
    struct HExpr_ call_773 = hxNil_(noTy_, loc_99);
    struct HExpr_NameCtx_Tuple2 tuple_538;
    tuple_538.t0 = call_773;
    tuple_538.t1 = nameCtx_23;
    match_273 = tuple_538;
    goto end_match_1070;
next_1074:;
    if ((expr_20.tag != ListLit_1)) goto next_1075;
    struct AExpr_List* items_11 = (*(expr_20.ListLit_1)).t0;
    struct IntIntTuple2 loc_100 = (*(expr_20.ListLit_1)).t1;
    struct AExpr_ call_774 = desugarListLitExpr_(items_11, loc_100);
    struct AExpr_ expr_21 = call_774;
    struct AExpr_NameCtx_Tuple2 tuple_539;
    tuple_539.t0 = expr_21;
    tuple_539.t1 = nameCtx_23;
    struct HExpr_NameCtx_Tuple2 call_775 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_539);
    match_273 = call_775;
    goto end_match_1070;
next_1075:;
    if ((expr_20.tag != If_1)) goto next_1076;
    struct AExpr_ cond_3 = (*(expr_20.If_1)).t0;
    struct AExpr_ body_19 = (*(expr_20.If_1)).t1;
    struct AExpr_ alt_4 = (*(expr_20.If_1)).t2;
    struct IntIntTuple2 loc_101 = (*(expr_20.If_1)).t3;
    struct AExpr_ call_776 = desugarIf_(litFalse_, litTrue_, cond_3, body_19, alt_4, loc_101);
    struct AExpr_ expr_22 = call_776;
    struct AExpr_NameCtx_Tuple2 tuple_540;
    tuple_540.t0 = expr_22;
    tuple_540.t1 = nameCtx_23;
    struct HExpr_NameCtx_Tuple2 call_777 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_540);
    match_273 = call_777;
    goto end_match_1070;
next_1076:;
    if ((expr_20.tag != Match_1)) goto next_1077;
    struct AExpr_ target_4 = (*(expr_20.Match_1)).t0;
    struct AArm_List* arms_5 = (*(expr_20.Match_1)).t1;
    struct IntIntTuple2 loc_102 = (*(expr_20.Match_1)).t2;
    struct AExpr_NameCtx_Tuple2 tuple_541;
    tuple_541.t0 = target_4;
    tuple_541.t1 = nameCtx_23;
    struct HExpr_NameCtx_Tuple2 call_778 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_541);
    struct HExpr_ target_5 = call_778.t0;
    struct NameCtx_ nameCtx_29 = call_778.t1;
    struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8 tuple_542;
    tuple_542.t0 = litFalse_;
    tuple_542.t1 = litTrue_;
    tuple_542.t2 = tyUnit_;
    tuple_542.t3 = tyStr_;
    tuple_542.t4 = tyChar_;
    tuple_542.t5 = tyInt_;
    tuple_542.t6 = tyBool_;
    tuple_542.t7 = noTy_;
    void* box_11 = (void*)malloc(sizeof(struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8));
    (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)box_11))) = tuple_542;
    void* env_47 = box_11;
    struct AArm_NameCtx_Tuple2HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2Fun1 fun_51 = (struct AArm_NameCtx_Tuple2HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2Fun1){.fun = fun_14, .env = env_47};
    struct AArm_ListNameCtx_Tuple2 tuple_543;
    tuple_543.t0 = arms_5;
    tuple_543.t1 = nameCtx_29;
    struct HPat_HExpr_HExpr_Tuple3ListNameCtx_Tuple2 call_779 = stMap_4(fun_51, tuple_543);
    struct HPat_HExpr_HExpr_Tuple3List* arms_6 = call_779.t0;
    struct NameCtx_ nameCtx_30 = call_779.t1;
    struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4 tuple_545;
    tuple_545.t0 = target_5;
    tuple_545.t1 = arms_6;
    tuple_545.t2 = noTy_;
    tuple_545.t3 = loc_102;
    struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4* payload_178 = (struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4));
    (*(((struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4*)payload_178))) = tuple_545;
    struct HExpr_ variant_178 = (struct HExpr_){.tag = Match_2, .Match_2 = payload_178};
    struct HExpr_NameCtx_Tuple2 tuple_544;
    tuple_544.t0 = variant_178;
    tuple_544.t1 = nameCtx_30;
    match_273 = tuple_544;
    goto end_match_1070;
next_1077:;
    if ((expr_20.tag != Fun_3)) goto next_1078;
    struct APat_List* pats_10 = (*(expr_20.Fun_3)).t0;
    struct AExpr_ body_22 = (*(expr_20.Fun_3)).t1;
    struct IntIntTuple2 loc_104 = (*(expr_20.Fun_3)).t2;
    struct AExpr_ call_780 = desugarFun_(pats_10, body_22, loc_104);
    struct AExpr_ expr_23 = call_780;
    struct AExpr_NameCtx_Tuple2 tuple_546;
    tuple_546.t0 = expr_23;
    tuple_546.t1 = nameCtx_23;
    struct HExpr_NameCtx_Tuple2 call_781 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_546);
    match_273 = call_781;
    goto end_match_1070;
next_1078:;
    if ((expr_20.tag != Nav_1)) goto next_1079;
    struct AExpr_ l_31 = (*(expr_20.Nav_1)).t0;
    struct String r_44 = (*(expr_20.Nav_1)).t1;
    struct IntIntTuple2 loc_105 = (*(expr_20.Nav_1)).t2;
    struct AExpr_NameCtx_Tuple2 tuple_547;
    tuple_547.t0 = l_31;
    tuple_547.t1 = nameCtx_23;
    struct HExpr_NameCtx_Tuple2 call_782 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_547);
    struct HExpr_ l_32 = call_782.t0;
    struct NameCtx_ nameCtx_31 = call_782.t1;
    struct HExpr_StringTy_IntIntTuple2Tuple4 tuple_549;
    tuple_549.t0 = l_32;
    tuple_549.t1 = r_44;
    tuple_549.t2 = noTy_;
    tuple_549.t3 = loc_105;
    struct HExpr_StringTy_IntIntTuple2Tuple4* payload_179 = (struct HExpr_StringTy_IntIntTuple2Tuple4*)malloc(sizeof(struct HExpr_StringTy_IntIntTuple2Tuple4));
    (*(((struct HExpr_StringTy_IntIntTuple2Tuple4*)payload_179))) = tuple_549;
    struct HExpr_ variant_179 = (struct HExpr_){.tag = Nav_3, .Nav_3 = payload_179};
    struct HExpr_NameCtx_Tuple2 tuple_548;
    tuple_548.t0 = variant_179;
    tuple_548.t1 = nameCtx_31;
    match_273 = tuple_548;
    goto end_match_1070;
next_1079:;
    if ((expr_20.tag != Index_)) goto next_1080;
    struct AExpr_ l_33 = (*(expr_20.Index_)).t0;
    struct AExpr_ r_45 = (*(expr_20.Index_)).t1;
    struct IntIntTuple2 loc_106 = (*(expr_20.Index_)).t2;
    struct HExpr_NameCtx_Tuple2 match_274;
    struct BoolAExpr_Tuple2 call_783 = tryDesugarIndexRange_(expr_20, loc_106);
    if ((!(call_783.t0))) goto next_1100;
    struct AExpr_ expr_24 = call_783.t1;
    struct AExpr_NameCtx_Tuple2 tuple_550;
    tuple_550.t0 = expr_24;
    tuple_550.t1 = nameCtx_23;
    struct HExpr_NameCtx_Tuple2 call_784 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_550);
    match_274 = call_784;
    goto end_match_1099;
next_1100:;
    if (call_783.t0) goto next_1101;
    struct AExpr_NameCtx_Tuple2 tuple_551;
    tuple_551.t0 = l_33;
    tuple_551.t1 = nameCtx_23;
    struct HExpr_NameCtx_Tuple2 call_785 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_551);
    struct HExpr_ l_34 = call_785.t0;
    struct NameCtx_ nameCtx_32 = call_785.t1;
    struct AExpr_NameCtx_Tuple2 tuple_552;
    tuple_552.t0 = r_45;
    tuple_552.t1 = nameCtx_32;
    struct HExpr_NameCtx_Tuple2 call_786 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_552);
    struct HExpr_ r_46 = call_786.t0;
    struct NameCtx_ nameCtx_33 = call_786.t1;
    struct HPrim_Ty_IntIntTuple2Tuple3 tuple_553;
    tuple_553.t0 = (struct HPrim_){.tag = Index_2};
    tuple_553.t1 = noTy_;
    tuple_553.t2 = loc_106;
    struct HPrim_Ty_IntIntTuple2Tuple3* payload_180 = (struct HPrim_Ty_IntIntTuple2Tuple3*)malloc(sizeof(struct HPrim_Ty_IntIntTuple2Tuple3));
    (*(((struct HPrim_Ty_IntIntTuple2Tuple3*)payload_180))) = tuple_553;
    struct HExpr_ variant_180 = (struct HExpr_){.tag = Prim_, .Prim_ = payload_180};
    struct HExpr_ call_787 = hxApp_(variant_180, l_34, noTy_, loc_106);
    struct HExpr_ call_788 = hxApp_(call_787, r_46, noTy_, loc_106);
    struct HExpr_ hxIndex_ = call_788;
    struct HExpr_NameCtx_Tuple2 tuple_554;
    tuple_554.t0 = hxIndex_;
    tuple_554.t1 = nameCtx_33;
    match_274 = tuple_554;
    goto end_match_1099;
next_1101:;
    exit(1);
end_match_1099:;
    match_273 = match_274;
    goto end_match_1070;
next_1080:;
    if ((expr_20.tag != Uni_)) goto next_1081;
    if (((*(expr_20.Uni_)).t0.tag != Neg_)) goto next_1081;
    struct AExpr_ arg_5 = (*(expr_20.Uni_)).t1;
    struct IntIntTuple2 loc_107 = (*(expr_20.Uni_)).t2;
    struct AExpr_ call_789 = desugarUniNeg_(arg_5, loc_107);
    struct AExpr_ expr_25 = call_789;
    struct AExpr_NameCtx_Tuple2 tuple_555;
    tuple_555.t0 = expr_25;
    tuple_555.t1 = nameCtx_23;
    struct HExpr_NameCtx_Tuple2 call_790 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_555);
    match_273 = call_790;
    goto end_match_1070;
next_1081:;
    if ((expr_20.tag != Bin_)) goto next_1082;
    if (((*(expr_20.Bin_)).t0.tag != Ne_)) goto next_1082;
    struct AExpr_ l_35 = (*(expr_20.Bin_)).t1;
    struct AExpr_ r_47 = (*(expr_20.Bin_)).t2;
    struct IntIntTuple2 loc_108 = (*(expr_20.Bin_)).t3;
    struct AExpr_ call_791 = desugarBinNe_(litFalse_, l_35, r_47, loc_108);
    struct AExpr_ expr_26 = call_791;
    struct AExpr_NameCtx_Tuple2 tuple_556;
    tuple_556.t0 = expr_26;
    tuple_556.t1 = nameCtx_23;
    struct HExpr_NameCtx_Tuple2 call_792 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_556);
    match_273 = call_792;
    goto end_match_1070;
next_1082:;
    if ((expr_20.tag != Bin_)) goto next_1083;
    if (((*(expr_20.Bin_)).t0.tag != Le_)) goto next_1083;
    struct AExpr_ l_36 = (*(expr_20.Bin_)).t1;
    struct AExpr_ r_48 = (*(expr_20.Bin_)).t2;
    struct IntIntTuple2 loc_109 = (*(expr_20.Bin_)).t3;
    struct AExpr_ call_793 = desugarBinLe_(litFalse_, l_36, r_48, loc_109);
    struct AExpr_ expr_27 = call_793;
    struct AExpr_NameCtx_Tuple2 tuple_557;
    tuple_557.t0 = expr_27;
    tuple_557.t1 = nameCtx_23;
    struct HExpr_NameCtx_Tuple2 call_794 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_557);
    match_273 = call_794;
    goto end_match_1070;
next_1083:;
    if ((expr_20.tag != Bin_)) goto next_1084;
    if (((*(expr_20.Bin_)).t0.tag != Gt_1)) goto next_1084;
    struct AExpr_ l_37 = (*(expr_20.Bin_)).t1;
    struct AExpr_ r_49 = (*(expr_20.Bin_)).t2;
    struct IntIntTuple2 loc_110 = (*(expr_20.Bin_)).t3;
    struct AExpr_ call_795 = desugarBinGt_(l_37, r_49, loc_110);
    struct AExpr_ expr_28 = call_795;
    struct AExpr_NameCtx_Tuple2 tuple_558;
    tuple_558.t0 = expr_28;
    tuple_558.t1 = nameCtx_23;
    struct HExpr_NameCtx_Tuple2 call_796 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_558);
    match_273 = call_796;
    goto end_match_1070;
next_1084:;
    if ((expr_20.tag != Bin_)) goto next_1085;
    if (((*(expr_20.Bin_)).t0.tag != Ge_)) goto next_1085;
    struct AExpr_ l_38 = (*(expr_20.Bin_)).t1;
    struct AExpr_ r_50 = (*(expr_20.Bin_)).t2;
    struct IntIntTuple2 loc_111 = (*(expr_20.Bin_)).t3;
    struct AExpr_ call_797 = desugarBinGe_(litFalse_, l_38, r_50, loc_111);
    struct AExpr_ expr_29 = call_797;
    struct AExpr_NameCtx_Tuple2 tuple_559;
    tuple_559.t0 = expr_29;
    tuple_559.t1 = nameCtx_23;
    struct HExpr_NameCtx_Tuple2 call_798 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_559);
    match_273 = call_798;
    goto end_match_1070;
next_1085:;
    if ((expr_20.tag != Bin_)) goto next_1086;
    if (((*(expr_20.Bin_)).t0.tag != And_1)) goto next_1086;
    struct AExpr_ l_39 = (*(expr_20.Bin_)).t1;
    struct AExpr_ r_51 = (*(expr_20.Bin_)).t2;
    struct IntIntTuple2 loc_112 = (*(expr_20.Bin_)).t3;
    struct AExpr_ call_799 = desugarBinAnd_(litFalse_, litTrue_, l_39, r_51, loc_112);
    struct AExpr_ expr_30 = call_799;
    struct AExpr_NameCtx_Tuple2 tuple_560;
    tuple_560.t0 = expr_30;
    tuple_560.t1 = nameCtx_23;
    struct HExpr_NameCtx_Tuple2 call_800 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_560);
    match_273 = call_800;
    goto end_match_1070;
next_1086:;
    if ((expr_20.tag != Bin_)) goto next_1087;
    if (((*(expr_20.Bin_)).t0.tag != Or_1)) goto next_1087;
    struct AExpr_ l_40 = (*(expr_20.Bin_)).t1;
    struct AExpr_ r_52 = (*(expr_20.Bin_)).t2;
    struct IntIntTuple2 loc_113 = (*(expr_20.Bin_)).t3;
    struct AExpr_ call_801 = desugarBinOr_(litFalse_, litTrue_, l_40, r_52, loc_113);
    struct AExpr_ expr_31 = call_801;
    struct AExpr_NameCtx_Tuple2 tuple_561;
    tuple_561.t0 = expr_31;
    tuple_561.t1 = nameCtx_23;
    struct HExpr_NameCtx_Tuple2 call_802 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_561);
    match_273 = call_802;
    goto end_match_1070;
next_1087:;
    if ((expr_20.tag != Bin_)) goto next_1088;
    if (((*(expr_20.Bin_)).t0.tag != Pipe_2)) goto next_1088;
    struct AExpr_ l_41 = (*(expr_20.Bin_)).t1;
    struct AExpr_ r_53 = (*(expr_20.Bin_)).t2;
    struct IntIntTuple2 loc_114 = (*(expr_20.Bin_)).t3;
    struct AExpr_ call_803 = desugarBinPipe_(l_41, r_53, loc_114);
    struct AExpr_ expr_32 = call_803;
    struct AExpr_NameCtx_Tuple2 tuple_562;
    tuple_562.t0 = expr_32;
    tuple_562.t1 = nameCtx_23;
    struct HExpr_NameCtx_Tuple2 call_804 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_562);
    match_273 = call_804;
    goto end_match_1070;
next_1088:;
    if ((expr_20.tag != Bin_)) goto next_1089;
    if (((*(expr_20.Bin_)).t0.tag != App_)) goto next_1089;
    struct AExpr_ l_42 = (*(expr_20.Bin_)).t1;
    struct AExpr_ r_54 = (*(expr_20.Bin_)).t2;
    struct IntIntTuple2 loc_115 = (*(expr_20.Bin_)).t3;
    struct AExpr_NameCtx_Tuple2 tuple_563;
    tuple_563.t0 = l_42;
    tuple_563.t1 = nameCtx_23;
    struct HExpr_NameCtx_Tuple2 call_805 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_563);
    struct HExpr_ l_43 = call_805.t0;
    struct NameCtx_ nameCtx_34 = call_805.t1;
    struct AExpr_NameCtx_Tuple2 tuple_564;
    tuple_564.t0 = r_54;
    tuple_564.t1 = nameCtx_34;
    struct HExpr_NameCtx_Tuple2 call_806 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_564);
    struct HExpr_ r_55 = call_806.t0;
    struct NameCtx_ nameCtx_35 = call_806.t1;
    struct HExpr_ call_807 = hxApp_(l_43, r_55, noTy_, loc_115);
    struct HExpr_NameCtx_Tuple2 tuple_565;
    tuple_565.t0 = call_807;
    tuple_565.t1 = nameCtx_35;
    match_273 = tuple_565;
    goto end_match_1070;
next_1089:;
    if ((expr_20.tag != Bin_)) goto next_1090;
    struct Op_ op_3 = (*(expr_20.Bin_)).t0;
    struct AExpr_ l_44 = (*(expr_20.Bin_)).t1;
    struct AExpr_ r_56 = (*(expr_20.Bin_)).t2;
    struct IntIntTuple2 loc_116 = (*(expr_20.Bin_)).t3;
    struct HPrim_ call_808 = opToPrim_(op_3);
    struct HPrim_ prim_2 = call_808;
    struct AExpr_NameCtx_Tuple2 tuple_566;
    tuple_566.t0 = l_44;
    tuple_566.t1 = nameCtx_23;
    struct HExpr_NameCtx_Tuple2 call_809 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_566);
    struct HExpr_ l_45 = call_809.t0;
    struct NameCtx_ nameCtx_36 = call_809.t1;
    struct AExpr_NameCtx_Tuple2 tuple_567;
    tuple_567.t0 = r_56;
    tuple_567.t1 = nameCtx_36;
    struct HExpr_NameCtx_Tuple2 call_810 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_567);
    struct HExpr_ r_57 = call_810.t0;
    struct NameCtx_ nameCtx_37 = call_810.t1;
    struct HPrim_Ty_IntIntTuple2Tuple3 tuple_568;
    tuple_568.t0 = prim_2;
    tuple_568.t1 = noTy_;
    tuple_568.t2 = loc_116;
    struct HPrim_Ty_IntIntTuple2Tuple3* payload_181 = (struct HPrim_Ty_IntIntTuple2Tuple3*)malloc(sizeof(struct HPrim_Ty_IntIntTuple2Tuple3));
    (*(((struct HPrim_Ty_IntIntTuple2Tuple3*)payload_181))) = tuple_568;
    struct HExpr_ variant_181 = (struct HExpr_){.tag = Prim_, .Prim_ = payload_181};
    struct HExpr_ primExpr_ = variant_181;
    struct HExpr_ call_811 = hxApp_(primExpr_, l_45, noTy_, loc_116);
    struct HExpr_ call_812 = hxApp_(call_811, r_57, noTy_, loc_116);
    struct HExpr_NameCtx_Tuple2 tuple_569;
    tuple_569.t0 = call_812;
    tuple_569.t1 = nameCtx_37;
    match_273 = tuple_569;
    goto end_match_1070;
next_1090:;
    if ((expr_20.tag != Range_)) goto next_1091;
    struct IntIntTuple2 loc_117 = (*(expr_20.Range_)).t1;
    struct StringIntIntTuple2Tuple2 tuple_571;
    tuple_571.t0 = (struct String){.str = "Invalid use of range syntax.", .len = 28};
    tuple_571.t1 = loc_117;
    struct StringIntIntTuple2Tuple2* payload_182 = (struct StringIntIntTuple2Tuple2*)malloc(sizeof(struct StringIntIntTuple2Tuple2));
    (*(((struct StringIntIntTuple2Tuple2*)payload_182))) = tuple_571;
    struct HExpr_ variant_182 = (struct HExpr_){.tag = Error_2, .Error_2 = payload_182};
    struct HExpr_NameCtx_Tuple2 tuple_570;
    tuple_570.t0 = variant_182;
    tuple_570.t1 = nameCtx_23;
    match_273 = tuple_570;
    goto end_match_1070;
next_1091:;
    if ((expr_20.tag != TupleLit_1)) goto next_1092;
    struct AExpr_List* items_12 = (*(expr_20.TupleLit_1)).t0;
    struct IntIntTuple2 loc_118 = (*(expr_20.TupleLit_1)).t1;
    struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8 tuple_572;
    tuple_572.t0 = litFalse_;
    tuple_572.t1 = litTrue_;
    tuple_572.t2 = tyUnit_;
    tuple_572.t3 = tyStr_;
    tuple_572.t4 = tyChar_;
    tuple_572.t5 = tyInt_;
    tuple_572.t6 = tyBool_;
    tuple_572.t7 = noTy_;
    void* box_12 = (void*)malloc(sizeof(struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8));
    (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)box_12))) = tuple_572;
    void* env_48 = box_12;
    struct AExpr_NameCtx_Tuple2HExpr_NameCtx_Tuple2Fun1 fun_52 = (struct AExpr_NameCtx_Tuple2HExpr_NameCtx_Tuple2Fun1){.fun = fun_15, .env = env_48};
    struct AExpr_ListNameCtx_Tuple2 tuple_573;
    tuple_573.t0 = items_12;
    tuple_573.t1 = nameCtx_23;
    struct HExpr_ListNameCtx_Tuple2 call_813 = stMap_3(fun_52, tuple_573);
    struct HExpr_List* items_13 = call_813.t0;
    struct NameCtx_ nameCtx_38 = call_813.t1;
    struct HExpr_ call_814 = hxTuple_(tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, items_13, loc_118);
    struct HExpr_NameCtx_Tuple2 tuple_574;
    tuple_574.t0 = call_814;
    tuple_574.t1 = nameCtx_38;
    match_273 = tuple_574;
    goto end_match_1070;
next_1092:;
    if ((expr_20.tag != Anno_1)) goto next_1093;
    struct AExpr_ body_23 = (*(expr_20.Anno_1)).t0;
    struct ATy_ ty_58 = (*(expr_20.Anno_1)).t1;
    struct IntIntTuple2 loc_119 = (*(expr_20.Anno_1)).t2;
    struct AExpr_NameCtx_Tuple2 tuple_575;
    tuple_575.t0 = body_23;
    tuple_575.t1 = nameCtx_23;
    struct HExpr_NameCtx_Tuple2 call_815 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_575);
    struct HExpr_ body_24 = call_815.t0;
    struct NameCtx_ nameCtx_39 = call_815.t1;
    struct ATy_NameCtx_Tuple2 tuple_576;
    tuple_576.t0 = ty_58;
    tuple_576.t1 = nameCtx_39;
    struct Ty_NameCtx_Tuple2 call_816 = onTy_(tuple_576);
    struct Ty_ ty_59 = call_816.t0;
    struct NameCtx_ nameCtx_40 = call_816.t1;
    struct HExpr_ call_817 = hxAnno_(body_24, ty_59, loc_119);
    struct HExpr_NameCtx_Tuple2 tuple_577;
    tuple_577.t0 = call_817;
    tuple_577.t1 = nameCtx_40;
    match_273 = tuple_577;
    goto end_match_1070;
next_1093:;
    if ((expr_20.tag != Semi_1)) goto next_1094;
    struct AExpr_List* exprs_1 = (*(expr_20.Semi_1)).t0;
    struct IntIntTuple2 loc_120 = (*(expr_20.Semi_1)).t1;
    int call_818 = listIsEmpty_1(exprs_1);
    milone_assert((!(call_818)), 390, 4);
    int call_819 = 0;
    struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8 tuple_578;
    tuple_578.t0 = litFalse_;
    tuple_578.t1 = litTrue_;
    tuple_578.t2 = tyUnit_;
    tuple_578.t3 = tyStr_;
    tuple_578.t4 = tyChar_;
    tuple_578.t5 = tyInt_;
    tuple_578.t6 = tyBool_;
    tuple_578.t7 = noTy_;
    void* box_13 = (void*)malloc(sizeof(struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8));
    (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)box_13))) = tuple_578;
    void* env_49 = box_13;
    struct AExpr_NameCtx_Tuple2HExpr_NameCtx_Tuple2Fun1 fun_53 = (struct AExpr_NameCtx_Tuple2HExpr_NameCtx_Tuple2Fun1){.fun = fun_16, .env = env_49};
    struct AExpr_ListNameCtx_Tuple2 tuple_579;
    tuple_579.t0 = exprs_1;
    tuple_579.t1 = nameCtx_23;
    struct HExpr_ListNameCtx_Tuple2 call_820 = stMap_3(fun_53, tuple_579);
    struct HExpr_List* exprs_2 = call_820.t0;
    struct NameCtx_ nameCtx_41 = call_820.t1;
    struct HExpr_ call_821 = hxSemi_(noTy_, exprs_2, loc_120);
    struct HExpr_NameCtx_Tuple2 tuple_580;
    tuple_580.t0 = call_821;
    tuple_580.t1 = nameCtx_41;
    match_273 = tuple_580;
    goto end_match_1070;
next_1094:;
    if ((expr_20.tag != Let_1)) goto next_1095;
    struct APat_ pat_34 = (*(expr_20.Let_1)).t0;
    struct AExpr_ body_25 = (*(expr_20.Let_1)).t1;
    struct AExpr_ next_14 = (*(expr_20.Let_1)).t2;
    struct IntIntTuple2 loc_121 = (*(expr_20.Let_1)).t3;
    struct HExpr_NameCtx_Tuple2 match_275;
    struct ALet_ call_822 = desugarLet_(pat_34, body_25, next_14, loc_121);
    if ((call_822.tag != LetFun_)) goto next_1103;
    struct String ident_33 = (*(call_822.LetFun_)).t0;
    struct APat_List* args_9 = (*(call_822.LetFun_)).t1;
    struct AExpr_ body_26 = (*(call_822.LetFun_)).t2;
    struct AExpr_ next_15 = (*(call_822.LetFun_)).t3;
    struct IntIntTuple2 loc_122 = (*(call_822.LetFun_)).t4;
    struct IntNameCtx_Tuple2 call_823 = nameCtxAdd_1(ident_33, nameCtx_23);
    int serial_12 = call_823.t0;
    struct NameCtx_ nameCtx_42 = call_823.t1;
    int isMainFun_1 = 0;
    struct Ty_Tuple1 tuple_581;
    tuple_581.t0 = noTy_;
    void* box_14 = (void*)malloc(sizeof(struct Ty_Tuple1));
    (*(((struct Ty_Tuple1*)box_14))) = tuple_581;
    void* env_50 = box_14;
    struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1 fun_54 = (struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1){.fun = fun_17, .env = env_50};
    struct APat_ListNameCtx_Tuple2 tuple_582;
    tuple_582.t0 = args_9;
    tuple_582.t1 = nameCtx_42;
    struct HPat_ListNameCtx_Tuple2 call_824 = stMap_2(fun_54, tuple_582);
    struct HPat_List* args_10 = call_824.t0;
    struct NameCtx_ nameCtx_43 = call_824.t1;
    struct AExpr_NameCtx_Tuple2 tuple_583;
    tuple_583.t0 = body_26;
    tuple_583.t1 = nameCtx_43;
    struct HExpr_NameCtx_Tuple2 call_825 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_583);
    struct HExpr_ body_27 = call_825.t0;
    struct NameCtx_ nameCtx_44 = call_825.t1;
    struct AExpr_NameCtx_Tuple2 tuple_584;
    tuple_584.t0 = next_15;
    tuple_584.t1 = nameCtx_44;
    struct HExpr_NameCtx_Tuple2 call_826 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_584);
    struct HExpr_ next_16 = call_826.t0;
    struct NameCtx_ nameCtx_45 = call_826.t1;
    struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7 tuple_586;
    tuple_586.t0 = serial_12;
    tuple_586.t1 = isMainFun_1;
    tuple_586.t2 = args_10;
    tuple_586.t3 = body_27;
    tuple_586.t4 = next_16;
    tuple_586.t5 = noTy_;
    tuple_586.t6 = loc_122;
    struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7* payload_183 = (struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7*)malloc(sizeof(struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7));
    (*(((struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7*)payload_183))) = tuple_586;
    struct HExpr_ variant_183 = (struct HExpr_){.tag = LetFun_1, .LetFun_1 = payload_183};
    struct HExpr_NameCtx_Tuple2 tuple_585;
    tuple_585.t0 = variant_183;
    tuple_585.t1 = nameCtx_45;
    match_275 = tuple_585;
    goto end_match_1102;
next_1103:;
    if ((call_822.tag != LetVal_)) goto next_1104;
    struct APat_ pat_35 = (*(call_822.LetVal_)).t0;
    struct AExpr_ body_28 = (*(call_822.LetVal_)).t1;
    struct AExpr_ next_17 = (*(call_822.LetVal_)).t2;
    struct IntIntTuple2 loc_123 = (*(call_822.LetVal_)).t3;
    struct APat_NameCtx_Tuple2 tuple_587;
    tuple_587.t0 = pat_35;
    tuple_587.t1 = nameCtx_23;
    struct HPat_NameCtx_Tuple2 call_827 = onPat_(noTy_, tuple_587);
    struct HPat_ pat_36 = call_827.t0;
    struct NameCtx_ nameCtx_46 = call_827.t1;
    struct AExpr_NameCtx_Tuple2 tuple_588;
    tuple_588.t0 = body_28;
    tuple_588.t1 = nameCtx_46;
    struct HExpr_NameCtx_Tuple2 call_828 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_588);
    struct HExpr_ body_29 = call_828.t0;
    struct NameCtx_ nameCtx_47 = call_828.t1;
    struct AExpr_NameCtx_Tuple2 tuple_589;
    tuple_589.t0 = next_17;
    tuple_589.t1 = nameCtx_47;
    struct HExpr_NameCtx_Tuple2 call_829 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_589);
    struct HExpr_ next_18 = call_829.t0;
    struct NameCtx_ nameCtx_48 = call_829.t1;
    struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5 tuple_591;
    tuple_591.t0 = pat_36;
    tuple_591.t1 = body_29;
    tuple_591.t2 = next_18;
    tuple_591.t3 = noTy_;
    tuple_591.t4 = loc_123;
    struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5* payload_184 = (struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5*)malloc(sizeof(struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5));
    (*(((struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5*)payload_184))) = tuple_591;
    struct HExpr_ variant_184 = (struct HExpr_){.tag = Let_2, .Let_2 = payload_184};
    struct HExpr_NameCtx_Tuple2 tuple_590;
    tuple_590.t0 = variant_184;
    tuple_590.t1 = nameCtx_48;
    match_275 = tuple_590;
    goto end_match_1102;
next_1104:;
    exit(1);
end_match_1102:;
    match_273 = match_275;
    goto end_match_1070;
next_1095:;
    if ((expr_20.tag != TySynonym_)) goto next_1096;
    struct String ident_34 = (*(expr_20.TySynonym_)).t0;
    struct ATy_ ty_60 = (*(expr_20.TySynonym_)).t1;
    struct IntIntTuple2 loc_124 = (*(expr_20.TySynonym_)).t2;
    struct IntNameCtx_Tuple2 call_830 = nameCtxAdd_1(ident_34, nameCtx_23);
    int serial_13 = call_830.t0;
    struct NameCtx_ nameCtx_49 = call_830.t1;
    struct ATy_NameCtx_Tuple2 tuple_592;
    tuple_592.t0 = ty_60;
    tuple_592.t1 = nameCtx_49;
    struct Ty_NameCtx_Tuple2 call_831 = onTy_(tuple_592);
    struct Ty_ ty_61 = call_831.t0;
    struct NameCtx_ nameCtx_50 = call_831.t1;
    struct Ty_IntIntTuple2Tuple2 tuple_595;
    tuple_595.t0 = ty_61;
    tuple_595.t1 = loc_124;
    struct Ty_IntIntTuple2Tuple2* payload_185 = (struct Ty_IntIntTuple2Tuple2*)malloc(sizeof(struct Ty_IntIntTuple2Tuple2));
    (*(((struct Ty_IntIntTuple2Tuple2*)payload_185))) = tuple_595;
    struct TyDecl_ variant_185 = (struct TyDecl_){.tag = Synonym_1, .Synonym_1 = payload_185};
    struct IntTyDecl_IntIntTuple2Tuple3 tuple_594;
    tuple_594.t0 = serial_13;
    tuple_594.t1 = variant_185;
    tuple_594.t2 = loc_124;
    struct IntTyDecl_IntIntTuple2Tuple3* payload_186 = (struct IntTyDecl_IntIntTuple2Tuple3*)malloc(sizeof(struct IntTyDecl_IntIntTuple2Tuple3));
    (*(((struct IntTyDecl_IntIntTuple2Tuple3*)payload_186))) = tuple_594;
    struct HExpr_ variant_186 = (struct HExpr_){.tag = TyDecl_, .TyDecl_ = payload_186};
    struct HExpr_NameCtx_Tuple2 tuple_593;
    tuple_593.t0 = variant_186;
    tuple_593.t1 = nameCtx_50;
    match_273 = tuple_593;
    goto end_match_1070;
next_1096:;
    if ((expr_20.tag != TyUnion_)) goto next_1097;
    struct String ident_35 = (*(expr_20.TyUnion_)).t0;
    struct AVariant_List* variants_3 = (*(expr_20.TyUnion_)).t1;
    struct IntIntTuple2 loc_125 = (*(expr_20.TyUnion_)).t2;
    struct IntNameCtx_Tuple2 call_832 = nameCtxAdd_1(ident_35, nameCtx_23);
    int unionSerial_ = call_832.t0;
    struct NameCtx_ nameCtx_55 = call_832.t1;
    struct Ty_Tuple1 tuple_596;
    tuple_596.t0 = tyUnit_;
    void* box_15 = (void*)malloc(sizeof(struct Ty_Tuple1));
    (*(((struct Ty_Tuple1*)box_15))) = tuple_596;
    void* env_51 = box_15;
    struct AVariant_NameCtx_Tuple2StringIntBoolTy_Tuple4NameCtx_Tuple2Fun1 fun_55 = (struct AVariant_NameCtx_Tuple2StringIntBoolTy_Tuple4NameCtx_Tuple2Fun1){.fun = fun_18, .env = env_51};
    struct AVariant_ListNameCtx_Tuple2 tuple_597;
    tuple_597.t0 = variants_3;
    tuple_597.t1 = nameCtx_55;
    struct StringIntBoolTy_Tuple4ListNameCtx_Tuple2 call_833 = stMap_1(fun_55, tuple_597);
    struct StringIntBoolTy_Tuple4List* variants_4 = call_833.t0;
    struct NameCtx_ nameCtx_56 = call_833.t1;
    struct StringStringIntBoolTy_Tuple4ListIntIntTuple2Tuple3 tuple_600;
    tuple_600.t0 = ident_35;
    tuple_600.t1 = variants_4;
    tuple_600.t2 = loc_125;
    struct StringStringIntBoolTy_Tuple4ListIntIntTuple2Tuple3* payload_187 = (struct StringStringIntBoolTy_Tuple4ListIntIntTuple2Tuple3*)malloc(sizeof(struct StringStringIntBoolTy_Tuple4ListIntIntTuple2Tuple3));
    (*(((struct StringStringIntBoolTy_Tuple4ListIntIntTuple2Tuple3*)payload_187))) = tuple_600;
    struct TyDecl_ variant_187 = (struct TyDecl_){.tag = Union_1, .Union_1 = payload_187};
    struct IntTyDecl_IntIntTuple2Tuple3 tuple_599;
    tuple_599.t0 = unionSerial_;
    tuple_599.t1 = variant_187;
    tuple_599.t2 = loc_125;
    struct IntTyDecl_IntIntTuple2Tuple3* payload_188 = (struct IntTyDecl_IntIntTuple2Tuple3*)malloc(sizeof(struct IntTyDecl_IntIntTuple2Tuple3));
    (*(((struct IntTyDecl_IntIntTuple2Tuple3*)payload_188))) = tuple_599;
    struct HExpr_ variant_188 = (struct HExpr_){.tag = TyDecl_, .TyDecl_ = payload_188};
    struct HExpr_NameCtx_Tuple2 tuple_598;
    tuple_598.t0 = variant_188;
    tuple_598.t1 = nameCtx_56;
    match_273 = tuple_598;
    goto end_match_1070;
next_1097:;
    if ((expr_20.tag != Open_1)) goto next_1098;
    struct StringList* path_4 = (*(expr_20.Open_1)).t0;
    struct IntIntTuple2 loc_126 = (*(expr_20.Open_1)).t1;
    struct StringListIntIntTuple2Tuple2 tuple_602;
    tuple_602.t0 = path_4;
    tuple_602.t1 = loc_126;
    struct StringListIntIntTuple2Tuple2* payload_189 = (struct StringListIntIntTuple2Tuple2*)malloc(sizeof(struct StringListIntIntTuple2Tuple2));
    (*(((struct StringListIntIntTuple2Tuple2*)payload_189))) = tuple_602;
    struct HExpr_ variant_189 = (struct HExpr_){.tag = Open_2, .Open_2 = payload_189};
    struct HExpr_NameCtx_Tuple2 tuple_601;
    tuple_601.t0 = variant_189;
    tuple_601.t1 = nameCtx_23;
    match_273 = tuple_601;
    goto end_match_1070;
next_1098:;
    exit(1);
end_match_1070:;
    return match_273;
}

struct HExpr_NameCtx_Tuple2 astToHir_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, struct AExpr_NameCtx_Tuple2 arg_185) {
    struct AExpr_ expr_33 = arg_185.t0;
    struct NameCtx_ nameCtx_57 = arg_185.t1;
    struct AExpr_NameCtx_Tuple2 tuple_603;
    tuple_603.t0 = expr_33;
    tuple_603.t1 = nameCtx_57;
    struct HExpr_NameCtx_Tuple2 call_834 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_603);
    return call_834;
}

struct String litToString_(struct Lit_ lit_5) {
    struct String match_276;
    if ((lit_5.tag != Bool_)) goto next_1106;
    if ((!((*(lit_5.Bool_))))) goto next_1106;
    match_276 = (struct String){.str = "true", .len = 4};
    goto end_match_1105;
next_1106:;
    if ((lit_5.tag != Bool_)) goto next_1107;
    if ((*(lit_5.Bool_))) goto next_1107;
    match_276 = (struct String){.str = "false", .len = 5};
    goto end_match_1105;
next_1107:;
    if ((lit_5.tag != Int_)) goto next_1108;
    int value_4 = (*(lit_5.Int_));
    struct String call_835 = str_of_int(value_4);
    match_276 = call_835;
    goto end_match_1105;
next_1108:;
    if ((lit_5.tag != Char_)) goto next_1109;
    char value_5 = (*(lit_5.Char_));
    struct String match_277;
    int call_836 = charNeedsEscaping_(value_5);
    if ((!(call_836))) goto next_1112;
    struct String call_837 = charEscape_(value_5);
    match_277 = call_837;
    goto end_match_1111;
next_1112:;
    if (call_836) goto next_1113;
    struct String call_838 = str_of_char(value_5);
    match_277 = call_838;
    goto end_match_1111;
next_1113:;
    exit(1);
end_match_1111:;
    match_276 = str_add(str_add((struct String){.str = "\'", .len = 1}, match_277), (struct String){.str = "\'", .len = 1});
    goto end_match_1105;
next_1109:;
    if ((lit_5.tag != Str_)) goto next_1110;
    struct String value_6 = (*(lit_5.Str_));
    struct String call_839 = strEscape_(value_6);
    match_276 = str_add(str_add((struct String){.str = "\"", .len = 1}, call_839), (struct String){.str = "\"", .len = 1});
    goto end_match_1105;
next_1110:;
    exit(1);
end_match_1105:;
    return match_276;
}

struct String tokenToString_(struct Token_ token_12) {
    struct String match_278;
    if ((token_12.tag != Error_)) goto next_1115;
    match_278 = (struct String){.str = "Error", .len = 5};
    goto end_match_1114;
next_1115:;
    if ((token_12.tag != Bool_1)) goto next_1116;
    if ((*(token_12.Bool_1))) goto next_1116;
    match_278 = (struct String){.str = "false", .len = 5};
    goto end_match_1114;
next_1116:;
    if ((token_12.tag != Bool_1)) goto next_1117;
    if ((!((*(token_12.Bool_1))))) goto next_1117;
    match_278 = (struct String){.str = "true", .len = 4};
    goto end_match_1114;
next_1117:;
    if ((token_12.tag != Int_1)) goto next_1118;
    int value_7 = (*(token_12.Int_1));
    struct String call_840 = str_of_int(value_7);
    match_278 = call_840;
    goto end_match_1114;
next_1118:;
    if ((token_12.tag != Char_1)) goto next_1119;
    char value_8 = (*(token_12.Char_1));
    char* payload_190 = (char*)malloc(sizeof(char));
    (*(((char*)payload_190))) = value_8;
    struct Lit_ variant_190 = (struct Lit_){.tag = Char_, .Char_ = payload_190};
    struct String call_841 = litToString_(variant_190);
    match_278 = call_841;
    goto end_match_1114;
next_1119:;
    if ((token_12.tag != Str_1)) goto next_1120;
    struct String value_9 = (*(token_12.Str_1));
    struct String* payload_191 = (struct String*)malloc(sizeof(struct String));
    (*(((struct String*)payload_191))) = value_9;
    struct Lit_ variant_191 = (struct Lit_){.tag = Str_, .Str_ = payload_191};
    struct String call_842 = litToString_(variant_191);
    match_278 = call_842;
    goto end_match_1114;
next_1120:;
    if ((token_12.tag != Ident_)) goto next_1121;
    struct String ident_8 = (*(token_12.Ident_));
    match_278 = ident_8;
    goto end_match_1114;
next_1121:;
    if ((token_12.tag != ParenL_)) goto next_1122;
    match_278 = (struct String){.str = "(", .len = 1};
    goto end_match_1114;
next_1122:;
    if ((token_12.tag != ParenR_)) goto next_1123;
    match_278 = (struct String){.str = ")", .len = 1};
    goto end_match_1114;
next_1123:;
    if ((token_12.tag != BracketL_)) goto next_1124;
    match_278 = (struct String){.str = "[", .len = 1};
    goto end_match_1114;
next_1124:;
    if ((token_12.tag != BracketR_)) goto next_1125;
    match_278 = (struct String){.str = "]", .len = 1};
    goto end_match_1114;
next_1125:;
    if ((token_12.tag != Amp_)) goto next_1126;
    match_278 = (struct String){.str = "&", .len = 1};
    goto end_match_1114;
next_1126:;
    if ((token_12.tag != AmpAmp_)) goto next_1127;
    match_278 = (struct String){.str = "&&", .len = 2};
    goto end_match_1114;
next_1127:;
    if ((token_12.tag != Arrow_)) goto next_1128;
    match_278 = (struct String){.str = "->", .len = 2};
    goto end_match_1114;
next_1128:;
    if ((token_12.tag != Colon_)) goto next_1129;
    match_278 = (struct String){.str = ":", .len = 1};
    goto end_match_1114;
next_1129:;
    if ((token_12.tag != ColonColon_)) goto next_1130;
    match_278 = (struct String){.str = "::", .len = 2};
    goto end_match_1114;
next_1130:;
    if ((token_12.tag != Comma_)) goto next_1131;
    match_278 = (struct String){.str = ",", .len = 1};
    goto end_match_1114;
next_1131:;
    if ((token_12.tag != Dot_)) goto next_1132;
    match_278 = (struct String){.str = ".", .len = 1};
    goto end_match_1114;
next_1132:;
    if ((token_12.tag != DotDot_)) goto next_1133;
    match_278 = (struct String){.str = "..", .len = 2};
    goto end_match_1114;
next_1133:;
    if ((token_12.tag != Eq_)) goto next_1134;
    match_278 = (struct String){.str = "=", .len = 1};
    goto end_match_1114;
next_1134:;
    if ((token_12.tag != Gt_)) goto next_1135;
    match_278 = (struct String){.str = ">", .len = 1};
    goto end_match_1114;
next_1135:;
    if ((token_12.tag != GtEq_)) goto next_1136;
    match_278 = (struct String){.str = ">=", .len = 2};
    goto end_match_1114;
next_1136:;
    if ((token_12.tag != Lt_)) goto next_1137;
    match_278 = (struct String){.str = "<", .len = 1};
    goto end_match_1114;
next_1137:;
    if ((token_12.tag != LtEq_)) goto next_1138;
    match_278 = (struct String){.str = "<=", .len = 2};
    goto end_match_1114;
next_1138:;
    if ((token_12.tag != LtGt_)) goto next_1139;
    match_278 = (struct String){.str = "<>", .len = 2};
    goto end_match_1114;
next_1139:;
    if ((token_12.tag != Minus_)) goto next_1140;
    match_278 = (struct String){.str = "-", .len = 1};
    goto end_match_1114;
next_1140:;
    if ((token_12.tag != Percent_)) goto next_1141;
    match_278 = (struct String){.str = "%", .len = 1};
    goto end_match_1114;
next_1141:;
    if ((token_12.tag != Pipe_)) goto next_1142;
    match_278 = (struct String){.str = "|", .len = 1};
    goto end_match_1114;
next_1142:;
    if ((token_12.tag != PipeGt_)) goto next_1143;
    match_278 = (struct String){.str = "|>", .len = 2};
    goto end_match_1114;
next_1143:;
    if ((token_12.tag != PipePipe_)) goto next_1144;
    match_278 = (struct String){.str = "||", .len = 2};
    goto end_match_1114;
next_1144:;
    if ((token_12.tag != Plus_)) goto next_1145;
    match_278 = (struct String){.str = "+", .len = 1};
    goto end_match_1114;
next_1145:;
    if ((token_12.tag != Semi_)) goto next_1146;
    match_278 = (struct String){.str = ";", .len = 1};
    goto end_match_1114;
next_1146:;
    if ((token_12.tag != Star_)) goto next_1147;
    match_278 = (struct String){.str = "*", .len = 1};
    goto end_match_1114;
next_1147:;
    if ((token_12.tag != Slash_)) goto next_1148;
    match_278 = (struct String){.str = "/", .len = 1};
    goto end_match_1114;
next_1148:;
    if ((token_12.tag != As_)) goto next_1149;
    match_278 = (struct String){.str = "as", .len = 2};
    goto end_match_1114;
next_1149:;
    if ((token_12.tag != Do_)) goto next_1150;
    match_278 = (struct String){.str = "do", .len = 2};
    goto end_match_1114;
next_1150:;
    if ((token_12.tag != Else_)) goto next_1151;
    match_278 = (struct String){.str = "else", .len = 4};
    goto end_match_1114;
next_1151:;
    if ((token_12.tag != Fun_)) goto next_1152;
    match_278 = (struct String){.str = "fun", .len = 3};
    goto end_match_1114;
next_1152:;
    if ((token_12.tag != If_)) goto next_1153;
    match_278 = (struct String){.str = "if", .len = 2};
    goto end_match_1114;
next_1153:;
    if ((token_12.tag != In_)) goto next_1154;
    match_278 = (struct String){.str = "in", .len = 2};
    goto end_match_1114;
next_1154:;
    if ((token_12.tag != Internal_)) goto next_1155;
    match_278 = (struct String){.str = "internal", .len = 8};
    goto end_match_1114;
next_1155:;
    if ((token_12.tag != Let_)) goto next_1156;
    match_278 = (struct String){.str = "let", .len = 3};
    goto end_match_1114;
next_1156:;
    if ((token_12.tag != Match_)) goto next_1157;
    match_278 = (struct String){.str = "match", .len = 5};
    goto end_match_1114;
next_1157:;
    if ((token_12.tag != Module_)) goto next_1158;
    match_278 = (struct String){.str = "module", .len = 6};
    goto end_match_1114;
next_1158:;
    if ((token_12.tag != Namespace_)) goto next_1159;
    match_278 = (struct String){.str = "namespace", .len = 9};
    goto end_match_1114;
next_1159:;
    if ((token_12.tag != Of_)) goto next_1160;
    match_278 = (struct String){.str = "of", .len = 2};
    goto end_match_1114;
next_1160:;
    if ((token_12.tag != Open_)) goto next_1161;
    match_278 = (struct String){.str = "open", .len = 4};
    goto end_match_1114;
next_1161:;
    if ((token_12.tag != Private_)) goto next_1162;
    match_278 = (struct String){.str = "private", .len = 7};
    goto end_match_1114;
next_1162:;
    if ((token_12.tag != Public_)) goto next_1163;
    match_278 = (struct String){.str = "public", .len = 6};
    goto end_match_1114;
next_1163:;
    if ((token_12.tag != Rec_)) goto next_1164;
    match_278 = (struct String){.str = "rec", .len = 3};
    goto end_match_1114;
next_1164:;
    if ((token_12.tag != Then_)) goto next_1165;
    match_278 = (struct String){.str = "then", .len = 4};
    goto end_match_1114;
next_1165:;
    if ((token_12.tag != Type_)) goto next_1166;
    match_278 = (struct String){.str = "type", .len = 4};
    goto end_match_1114;
next_1166:;
    if ((token_12.tag != When_)) goto next_1167;
    match_278 = (struct String){.str = "when", .len = 4};
    goto end_match_1114;
next_1167:;
    if ((token_12.tag != With_)) goto next_1168;
    match_278 = (struct String){.str = "with", .len = 4};
    goto end_match_1114;
next_1168:;
end_match_1114:;
    return match_278;
}

struct DumpTree_ fun_19(void* env_16, struct ATy_ arg_65) {
    struct DumpTree_ call_843 = atDump_(arg_65);
    return call_843;
}

struct DumpTree_ fun_20(void* env_17, struct ATy_ arg_66) {
    struct DumpTree_ call_844 = atDump_(arg_66);
    return call_844;
}

struct DumpTree_ fun_21(void* env_18, struct ATy_ arg_67) {
    struct DumpTree_ call_845 = atDump_(arg_67);
    return call_845;
}

struct DumpTree_ atDump_(struct ATy_ ty_43) {
    struct DumpTree_ match_279;
    if ((ty_43.tag != Missing_)) goto next_1170;
    struct IntIntTuple2 loc_23 = (*(ty_43.Missing_));
    struct DumpTree_ call_846 = dumpTreeFromError_((struct String){.str = "missing", .len = 7}, loc_23);
    match_279 = call_846;
    goto end_match_1169;
next_1170:;
    if ((ty_43.tag != App_1)) goto next_1171;
    struct String ident_9 = (*(ty_43.App_1)).t0;
    struct ATy_List* tys_6 = (*(ty_43.App_1)).t1;
    void* box_16 = (void*)malloc(sizeof(int));
    (*(((int*)box_16))) = 0;
    void* env_52 = box_16;
    struct ATy_DumpTree_Fun1 fun_56 = (struct ATy_DumpTree_Fun1){.fun = fun_19, .env = env_52};
    struct DumpTree_List* call_847 = listMap_7(fun_56, tys_6);
    struct DumpTree_ call_848 = dumpTreeNew_(ident_9, call_847);
    match_279 = call_848;
    goto end_match_1169;
next_1171:;
    if ((ty_43.tag != Suffix_)) goto next_1172;
    struct ATy_ lTy_2 = (*(ty_43.Suffix_)).t0;
    struct String ident_10 = (*(ty_43.Suffix_)).t1;
    struct DumpTree_ call_849 = atDump_(lTy_2);
    struct DumpTree_List* list_86 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_86->head = call_849;
    list_86->tail = NULL;
    struct DumpTree_ call_850 = dumpTreeNew_(ident_10, list_86);
    match_279 = call_850;
    goto end_match_1169;
next_1172:;
    if ((ty_43.tag != Tuple_)) goto next_1173;
    struct ATy_List* itemTys_ = (*(ty_43.Tuple_)).t0;
    void* box_17 = (void*)malloc(sizeof(int));
    (*(((int*)box_17))) = 0;
    void* env_53 = box_17;
    struct ATy_DumpTree_Fun1 fun_57 = (struct ATy_DumpTree_Fun1){.fun = fun_20, .env = env_53};
    struct DumpTree_List* call_851 = listMap_7(fun_57, itemTys_);
    struct DumpTree_ call_852 = dumpTreeNew_((struct String){.str = "tuple", .len = 5}, call_851);
    match_279 = call_852;
    goto end_match_1169;
next_1173:;
    if ((ty_43.tag != Fun_1)) goto next_1174;
    struct ATy_ sTy_ = (*(ty_43.Fun_1)).t0;
    struct ATy_ tTy_ = (*(ty_43.Fun_1)).t1;
    void* box_18 = (void*)malloc(sizeof(int));
    (*(((int*)box_18))) = 0;
    void* env_54 = box_18;
    struct ATy_DumpTree_Fun1 fun_58 = (struct ATy_DumpTree_Fun1){.fun = fun_21, .env = env_54};
    struct ATy_List* list_88 = (struct ATy_List*)malloc(sizeof(struct ATy_List));
    list_88->head = tTy_;
    list_88->tail = NULL;
    struct ATy_List* list_87 = (struct ATy_List*)malloc(sizeof(struct ATy_List));
    list_87->head = sTy_;
    list_87->tail = list_88;
    struct DumpTree_List* call_853 = listMap_7(fun_58, list_87);
    struct DumpTree_ call_854 = dumpTreeNew_((struct String){.str = "fun", .len = 3}, call_853);
    match_279 = call_854;
    goto end_match_1169;
next_1174:;
    exit(1);
end_match_1169:;
    return match_279;
}

struct DumpTree_ fun_22(void* env_19, struct APat_ arg_68) {
    struct DumpTree_ call_855 = apDump_(arg_68);
    return call_855;
}

struct DumpTree_ fun_23(void* env_20, struct APat_ arg_69) {
    struct DumpTree_ call_856 = apDump_(arg_69);
    return call_856;
}

struct DumpTree_ fun_24(void* env_21, struct APat_ arg_70) {
    struct DumpTree_ call_857 = apDump_(arg_70);
    return call_857;
}

struct DumpTree_ fun_25(void* env_22, struct APat_ arg_71) {
    struct DumpTree_ call_858 = apDump_(arg_71);
    return call_858;
}

struct DumpTree_ apDump_(struct APat_ pat_10) {
    struct DumpTree_ match_280;
    if ((pat_10.tag != Missing_1)) goto next_1176;
    struct IntIntTuple2 loc_24 = (*(pat_10.Missing_1));
    struct DumpTree_ call_859 = dumpTreeFromError_((struct String){.str = "missing", .len = 7}, loc_24);
    match_280 = call_859;
    goto end_match_1175;
next_1176:;
    if ((pat_10.tag != Lit_)) goto next_1177;
    struct Lit_ lit_6 = (*(pat_10.Lit_)).t0;
    struct String call_860 = litToString_(lit_6);
    struct DumpTree_ call_861 = dumpTreeNewLeaf_(call_860);
    match_280 = call_861;
    goto end_match_1175;
next_1177:;
    if ((pat_10.tag != Ident_1)) goto next_1178;
    struct String ident_11 = (*(pat_10.Ident_1)).t0;
    struct DumpTree_ call_862 = dumpTreeNewLeaf_(ident_11);
    match_280 = call_862;
    goto end_match_1175;
next_1178:;
    if ((pat_10.tag != ListLit_)) goto next_1179;
    struct APat_List* pats_ = (*(pat_10.ListLit_)).t0;
    void* box_19 = (void*)malloc(sizeof(int));
    (*(((int*)box_19))) = 0;
    void* env_55 = box_19;
    struct APat_DumpTree_Fun1 fun_59 = (struct APat_DumpTree_Fun1){.fun = fun_22, .env = env_55};
    struct DumpTree_List* call_863 = listMap_5(fun_59, pats_);
    struct DumpTree_ call_864 = dumpTreeNew_((struct String){.str = "list", .len = 4}, call_863);
    match_280 = call_864;
    goto end_match_1175;
next_1179:;
    if ((pat_10.tag != Nav_)) goto next_1180;
    struct APat_ l_11 = (*(pat_10.Nav_)).t0;
    struct String r_24 = (*(pat_10.Nav_)).t1;
    struct DumpTree_ call_865 = apDump_(l_11);
    struct DumpTree_List* list_89 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_89->head = call_865;
    list_89->tail = NULL;
    struct DumpTree_ call_866 = dumpTreeNew_(str_add((struct String){.str = ".", .len = 1}, r_24), list_89);
    match_280 = call_866;
    goto end_match_1175;
next_1180:;
    if ((pat_10.tag != Call_)) goto next_1181;
    struct APat_ calleePat_ = (*(pat_10.Call_)).t0;
    struct APat_List* argPats_ = (*(pat_10.Call_)).t1;
    struct DumpTree_ call_867 = apDump_(calleePat_);
    void* box_20 = (void*)malloc(sizeof(int));
    (*(((int*)box_20))) = 0;
    void* env_56 = box_20;
    struct APat_DumpTree_Fun1 fun_60 = (struct APat_DumpTree_Fun1){.fun = fun_23, .env = env_56};
    struct DumpTree_List* call_868 = listMap_5(fun_60, argPats_);
    struct DumpTree_List* list_90 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_90->head = call_867;
    list_90->tail = call_868;
    struct DumpTree_ call_869 = dumpTreeNew_((struct String){.str = "call", .len = 4}, list_90);
    match_280 = call_869;
    goto end_match_1175;
next_1181:;
    if ((pat_10.tag != Cons_2)) goto next_1182;
    struct APat_ head_1 = (*(pat_10.Cons_2)).t0;
    struct APat_ tail_1 = (*(pat_10.Cons_2)).t1;
    struct DumpTree_ call_870 = apDump_(tail_1);
    struct DumpTree_ call_871 = apDump_(head_1);
    struct DumpTree_List* list_91 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_91->head = call_871;
    list_91->tail = NULL;
    struct DumpTree_ call_872 = dumpTreeNew_((struct String){.str = "cons", .len = 4}, list_91);
    struct DumpTree_ call_873 = dumpTreeAttachNext_(call_870, call_872);
    match_280 = call_873;
    goto end_match_1175;
next_1182:;
    if ((pat_10.tag != TupleLit_)) goto next_1183;
    struct APat_List* pats_1 = (*(pat_10.TupleLit_)).t0;
    void* box_21 = (void*)malloc(sizeof(int));
    (*(((int*)box_21))) = 0;
    void* env_57 = box_21;
    struct APat_DumpTree_Fun1 fun_61 = (struct APat_DumpTree_Fun1){.fun = fun_24, .env = env_57};
    struct DumpTree_List* call_874 = listMap_5(fun_61, pats_1);
    struct DumpTree_ call_875 = dumpTreeNew_((struct String){.str = "tuple", .len = 5}, call_874);
    match_280 = call_875;
    goto end_match_1175;
next_1183:;
    if ((pat_10.tag != As_1)) goto next_1184;
    struct APat_ pat_11 = (*(pat_10.As_1)).t0;
    struct String ident_12 = (*(pat_10.As_1)).t1;
    struct DumpTree_ call_876 = apDump_(pat_11);
    struct DumpTree_List* list_92 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_92->head = call_876;
    list_92->tail = NULL;
    struct DumpTree_ call_877 = dumpTreeNew_(str_add((struct String){.str = "as ", .len = 3}, ident_12), list_92);
    match_280 = call_877;
    goto end_match_1175;
next_1184:;
    if ((pat_10.tag != Anno_)) goto next_1185;
    struct APat_ pat_12 = (*(pat_10.Anno_)).t0;
    struct ATy_ ty_44 = (*(pat_10.Anno_)).t1;
    struct DumpTree_ call_878 = apDump_(pat_12);
    struct DumpTree_ call_879 = atDump_(ty_44);
    struct DumpTree_List* list_94 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_94->head = call_879;
    list_94->tail = NULL;
    struct DumpTree_List* list_93 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_93->head = call_878;
    list_93->tail = list_94;
    struct DumpTree_ call_880 = dumpTreeNew_((struct String){.str = "anno", .len = 4}, list_93);
    match_280 = call_880;
    goto end_match_1175;
next_1185:;
    if ((pat_10.tag != Or_2)) goto next_1186;
    struct APat_ l_12 = (*(pat_10.Or_2)).t0;
    struct APat_ r_25 = (*(pat_10.Or_2)).t1;
    struct DumpTree_ call_881 = apDump_(r_25);
    struct DumpTree_ call_882 = apDump_(l_12);
    struct DumpTree_List* list_95 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_95->head = call_882;
    list_95->tail = NULL;
    struct DumpTree_ call_883 = dumpTreeNew_((struct String){.str = "or", .len = 2}, list_95);
    struct DumpTree_ call_884 = dumpTreeAttachNext_(call_881, call_883);
    match_280 = call_884;
    goto end_match_1175;
next_1186:;
    if ((pat_10.tag != Fun_2)) goto next_1187;
    struct String callee_3 = (*(pat_10.Fun_2)).t0;
    struct APat_List* args_5 = (*(pat_10.Fun_2)).t1;
    struct DumpTree_ call_885 = dumpTreeNewLeaf_(callee_3);
    void* box_22 = (void*)malloc(sizeof(int));
    (*(((int*)box_22))) = 0;
    void* env_58 = box_22;
    struct APat_DumpTree_Fun1 fun_62 = (struct APat_DumpTree_Fun1){.fun = fun_25, .env = env_58};
    struct DumpTree_List* call_886 = listMap_5(fun_62, args_5);
    struct DumpTree_List* list_96 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_96->head = call_885;
    list_96->tail = call_886;
    struct DumpTree_ call_887 = dumpTreeNew_((struct String){.str = "fun", .len = 3}, list_96);
    match_280 = call_887;
    goto end_match_1175;
next_1187:;
    exit(1);
end_match_1175:;
    return match_280;
}

struct DumpTree_ fun_26(void* env_23, struct AExpr_ arg_72) {
    struct DumpTree_ call_888 = axDump_(arg_72);
    return call_888;
}

struct DumpTree_ dumpArm_(struct AArm_ arg_186) {
    struct APat_ pat_13 = (*(arg_186.AArm_)).t0;
    struct AExpr_ guard_1 = (*(arg_186.AArm_)).t1;
    struct AExpr_ body_3 = (*(arg_186.AArm_)).t2;
    struct DumpTree_ call_889 = axDump_(body_3);
    struct DumpTree_ call_890 = apDump_(pat_13);
    struct DumpTree_ call_891 = axDump_(guard_1);
    struct DumpTree_List* list_98 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_98->head = call_891;
    list_98->tail = NULL;
    struct DumpTree_List* list_97 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_97->head = call_890;
    list_97->tail = list_98;
    struct DumpTree_ call_892 = dumpTreeNew_((struct String){.str = "arm", .len = 3}, list_97);
    struct DumpTree_ call_893 = dumpTreeAttachNext_(call_889, call_892);
    return call_893;
}

struct DumpTree_ fun_27(void* env_24, struct AArm_ arg_73) {
    struct DumpTree_ call_894 = dumpArm_(arg_73);
    return call_894;
}

struct DumpTree_ fun_28(void* env_25, struct APat_ arg_74) {
    struct DumpTree_ call_895 = apDump_(arg_74);
    return call_895;
}

struct DumpTree_ fun_29(void* env_26, struct AExpr_ arg_75) {
    struct DumpTree_ call_896 = axDump_(arg_75);
    return call_896;
}

struct DumpTree_ fun_30(void* env_27, struct AExpr_ arg_76) {
    struct DumpTree_ call_897 = axDump_(arg_76);
    return call_897;
}

struct DumpTree_ fun_31(void* env_28, struct AExpr_ arg_77) {
    struct DumpTree_ call_898 = axDump_(arg_77);
    return call_898;
}

struct DumpTree_ dumpVariant_(struct AVariant_ arg_187) {
    struct String ident_16 = (*(arg_187.AVariant_)).t0;
    struct DumpTree_ call_899 = dumpTreeNewLeaf_(ident_16);
    return call_899;
}

struct DumpTree_ fun_32(void* env_29, struct AVariant_ arg_78) {
    struct DumpTree_ call_900 = dumpVariant_(arg_78);
    return call_900;
}

struct DumpTree_ fun_33(void* env_30, struct String arg_79) {
    struct DumpTree_ call_901 = dumpTreeNewLeaf_(arg_79);
    return call_901;
}

struct DumpTree_ axDump_(struct AExpr_ expr_7) {
    struct DumpTree_ match_281;
    if ((expr_7.tag != Missing_2)) goto next_1189;
    struct IntIntTuple2 loc_25 = (*(expr_7.Missing_2));
    struct DumpTree_ call_902 = dumpTreeFromError_((struct String){.str = "missing", .len = 7}, loc_25);
    match_281 = call_902;
    goto end_match_1188;
next_1189:;
    if ((expr_7.tag != Lit_1)) goto next_1190;
    struct Lit_ lit_7 = (*(expr_7.Lit_1)).t0;
    struct String call_903 = litToString_(lit_7);
    struct DumpTree_ call_904 = dumpTreeNewLeaf_(call_903);
    match_281 = call_904;
    goto end_match_1188;
next_1190:;
    if ((expr_7.tag != Ident_2)) goto next_1191;
    struct String ident_13 = (*(expr_7.Ident_2)).t0;
    struct DumpTree_ call_905 = dumpTreeNewLeaf_(ident_13);
    match_281 = call_905;
    goto end_match_1188;
next_1191:;
    if ((expr_7.tag != ListLit_1)) goto next_1192;
    struct AExpr_List* items_2 = (*(expr_7.ListLit_1)).t0;
    void* box_23 = (void*)malloc(sizeof(int));
    (*(((int*)box_23))) = 0;
    void* env_59 = box_23;
    struct AExpr_DumpTree_Fun1 fun_63 = (struct AExpr_DumpTree_Fun1){.fun = fun_26, .env = env_59};
    struct DumpTree_List* call_906 = listMap_4(fun_63, items_2);
    struct DumpTree_ call_907 = dumpTreeNew_((struct String){.str = "list", .len = 4}, call_906);
    match_281 = call_907;
    goto end_match_1188;
next_1192:;
    if ((expr_7.tag != If_1)) goto next_1193;
    struct AExpr_ cond_ = (*(expr_7.If_1)).t0;
    struct AExpr_ body_2 = (*(expr_7.If_1)).t1;
    struct AExpr_ alt_ = (*(expr_7.If_1)).t2;
    struct DumpTree_ call_908 = axDump_(cond_);
    struct DumpTree_ call_909 = axDump_(body_2);
    struct DumpTree_ call_910 = axDump_(alt_);
    struct DumpTree_List* list_101 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_101->head = call_910;
    list_101->tail = NULL;
    struct DumpTree_List* list_100 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_100->head = call_909;
    list_100->tail = list_101;
    struct DumpTree_List* list_99 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_99->head = call_908;
    list_99->tail = list_100;
    struct DumpTree_ call_911 = dumpTreeNew_((struct String){.str = "if", .len = 2}, list_99);
    match_281 = call_911;
    goto end_match_1188;
next_1193:;
    if ((expr_7.tag != Match_1)) goto next_1194;
    struct AExpr_ target_1 = (*(expr_7.Match_1)).t0;
    struct AArm_List* arms_2 = (*(expr_7.Match_1)).t1;
    struct DumpTree_ call_912 = axDump_(target_1);
    void* box_24 = (void*)malloc(sizeof(int));
    (*(((int*)box_24))) = 0;
    void* env_60 = box_24;
    struct AArm_DumpTree_Fun1 fun_64 = (struct AArm_DumpTree_Fun1){.fun = fun_27, .env = env_60};
    struct DumpTree_List* call_913 = listMap_6(fun_64, arms_2);
    struct DumpTree_List* list_102 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_102->head = call_912;
    list_102->tail = call_913;
    struct DumpTree_ call_914 = dumpTreeNew_((struct String){.str = "match", .len = 5}, list_102);
    match_281 = call_914;
    goto end_match_1188;
next_1194:;
    if ((expr_7.tag != Fun_3)) goto next_1195;
    struct APat_List* pats_2 = (*(expr_7.Fun_3)).t0;
    struct AExpr_ body_4 = (*(expr_7.Fun_3)).t1;
    struct DumpTree_ call_915 = axDump_(body_4);
    void* box_25 = (void*)malloc(sizeof(int));
    (*(((int*)box_25))) = 0;
    void* env_61 = box_25;
    struct APat_DumpTree_Fun1 fun_65 = (struct APat_DumpTree_Fun1){.fun = fun_28, .env = env_61};
    struct DumpTree_List* call_916 = listMap_5(fun_65, pats_2);
    struct DumpTree_ call_917 = dumpTreeNew_((struct String){.str = "fun", .len = 3}, call_916);
    struct DumpTree_ call_918 = dumpTreeAttachNext_(call_915, call_917);
    match_281 = call_918;
    goto end_match_1188;
next_1195:;
    if ((expr_7.tag != Nav_1)) goto next_1196;
    struct AExpr_ l_13 = (*(expr_7.Nav_1)).t0;
    struct String r_26 = (*(expr_7.Nav_1)).t1;
    struct DumpTree_ call_919 = axDump_(l_13);
    struct DumpTree_List* list_103 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_103->head = call_919;
    list_103->tail = NULL;
    struct DumpTree_ call_920 = dumpTreeNew_(str_add((struct String){.str = ".", .len = 1}, r_26), list_103);
    match_281 = call_920;
    goto end_match_1188;
next_1196:;
    if ((expr_7.tag != Index_)) goto next_1197;
    struct AExpr_ l_14 = (*(expr_7.Index_)).t0;
    struct AExpr_ r_27 = (*(expr_7.Index_)).t1;
    struct DumpTree_ call_921 = axDump_(l_14);
    struct DumpTree_List* list_104 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_104->head = call_921;
    list_104->tail = NULL;
    struct DumpTree_ call_922 = dumpTreeNew_((struct String){.str = "index", .len = 5}, list_104);
    match_281 = call_922;
    goto end_match_1188;
next_1197:;
    if ((expr_7.tag != Uni_)) goto next_1198;
    if (((*(expr_7.Uni_)).t0.tag != Neg_)) goto next_1198;
    struct AExpr_ arg_1 = (*(expr_7.Uni_)).t1;
    struct DumpTree_ call_923 = axDump_(arg_1);
    struct DumpTree_List* list_105 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_105->head = call_923;
    list_105->tail = NULL;
    struct DumpTree_ call_924 = dumpTreeNew_((struct String){.str = "-", .len = 1}, list_105);
    match_281 = call_924;
    goto end_match_1188;
next_1198:;
    if ((expr_7.tag != Bin_)) goto next_1199;
    struct AExpr_ l_15 = (*(expr_7.Bin_)).t1;
    struct AExpr_ r_28 = (*(expr_7.Bin_)).t2;
    struct DumpTree_ call_925 = axDump_(l_15);
    struct DumpTree_ call_926 = axDump_(r_28);
    struct DumpTree_List* list_107 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_107->head = call_926;
    list_107->tail = NULL;
    struct DumpTree_List* list_106 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_106->head = call_925;
    list_106->tail = list_107;
    struct DumpTree_ call_927 = dumpTreeNew_((struct String){.str = "bin", .len = 3}, list_106);
    match_281 = call_927;
    goto end_match_1188;
next_1199:;
    if ((expr_7.tag != Range_)) goto next_1200;
    struct AExpr_List* items_3 = (*(expr_7.Range_)).t0;
    void* box_26 = (void*)malloc(sizeof(int));
    (*(((int*)box_26))) = 0;
    void* env_62 = box_26;
    struct AExpr_DumpTree_Fun1 fun_66 = (struct AExpr_DumpTree_Fun1){.fun = fun_29, .env = env_62};
    struct DumpTree_List* call_928 = listMap_4(fun_66, items_3);
    struct DumpTree_ call_929 = dumpTreeNew_((struct String){.str = "range", .len = 5}, call_928);
    match_281 = call_929;
    goto end_match_1188;
next_1200:;
    if ((expr_7.tag != TupleLit_1)) goto next_1201;
    struct AExpr_List* items_4 = (*(expr_7.TupleLit_1)).t0;
    void* box_27 = (void*)malloc(sizeof(int));
    (*(((int*)box_27))) = 0;
    void* env_63 = box_27;
    struct AExpr_DumpTree_Fun1 fun_67 = (struct AExpr_DumpTree_Fun1){.fun = fun_30, .env = env_63};
    struct DumpTree_List* call_930 = listMap_4(fun_67, items_4);
    struct DumpTree_ call_931 = dumpTreeNew_((struct String){.str = "tuple", .len = 5}, call_930);
    match_281 = call_931;
    goto end_match_1188;
next_1201:;
    if ((expr_7.tag != Anno_1)) goto next_1202;
    struct AExpr_ body_5 = (*(expr_7.Anno_1)).t0;
    struct ATy_ ty_45 = (*(expr_7.Anno_1)).t1;
    struct DumpTree_ call_932 = axDump_(body_5);
    struct DumpTree_ call_933 = atDump_(ty_45);
    struct DumpTree_List* list_109 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_109->head = call_933;
    list_109->tail = NULL;
    struct DumpTree_List* list_108 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_108->head = call_932;
    list_108->tail = list_109;
    struct DumpTree_ call_934 = dumpTreeNew_((struct String){.str = "anno", .len = 4}, list_108);
    match_281 = call_934;
    goto end_match_1188;
next_1202:;
    if ((expr_7.tag != Semi_1)) goto next_1203;
    struct AExpr_List* exprs_ = (*(expr_7.Semi_1)).t0;
    void* box_28 = (void*)malloc(sizeof(int));
    (*(((int*)box_28))) = 0;
    void* env_64 = box_28;
    struct AExpr_DumpTree_Fun1 fun_68 = (struct AExpr_DumpTree_Fun1){.fun = fun_31, .env = env_64};
    struct DumpTree_List* call_935 = listMap_4(fun_68, exprs_);
    struct DumpTree_ call_936 = dumpTreeNew_((struct String){.str = "semi", .len = 4}, call_935);
    match_281 = call_936;
    goto end_match_1188;
next_1203:;
    if ((expr_7.tag != Let_1)) goto next_1204;
    struct APat_ pat_14 = (*(expr_7.Let_1)).t0;
    struct AExpr_ body_6 = (*(expr_7.Let_1)).t1;
    struct AExpr_ next_8 = (*(expr_7.Let_1)).t2;
    struct DumpTree_ call_937 = axDump_(next_8);
    struct DumpTree_ call_938 = apDump_(pat_14);
    struct DumpTree_ call_939 = axDump_(body_6);
    struct DumpTree_List* list_111 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_111->head = call_939;
    list_111->tail = NULL;
    struct DumpTree_List* list_110 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_110->head = call_938;
    list_110->tail = list_111;
    struct DumpTree_ call_940 = dumpTreeNew_((struct String){.str = "let", .len = 3}, list_110);
    struct DumpTree_ call_941 = dumpTreeAttachNext_(call_937, call_940);
    match_281 = call_941;
    goto end_match_1188;
next_1204:;
    if ((expr_7.tag != TySynonym_)) goto next_1205;
    struct String ident_14 = (*(expr_7.TySynonym_)).t0;
    struct ATy_ ty_46 = (*(expr_7.TySynonym_)).t1;
    struct DumpTree_ call_942 = atDump_(ty_46);
    struct DumpTree_ call_943 = dumpTreeNewLeaf_(ident_14);
    struct DumpTree_List* list_112 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_112->head = call_943;
    list_112->tail = NULL;
    struct DumpTree_ call_944 = dumpTreeNew_((struct String){.str = "synonym", .len = 7}, list_112);
    struct DumpTree_ call_945 = dumpTreeAttachNext_(call_942, call_944);
    match_281 = call_945;
    goto end_match_1188;
next_1205:;
    if ((expr_7.tag != TyUnion_)) goto next_1206;
    struct String ident_15 = (*(expr_7.TyUnion_)).t0;
    struct AVariant_List* variants_ = (*(expr_7.TyUnion_)).t1;
    struct DumpTree_ call_946 = dumpTreeNewLeaf_(ident_15);
    void* box_29 = (void*)malloc(sizeof(int));
    (*(((int*)box_29))) = 0;
    void* env_65 = box_29;
    struct AVariant_DumpTree_Fun1 fun_69 = (struct AVariant_DumpTree_Fun1){.fun = fun_32, .env = env_65};
    struct DumpTree_List* call_947 = listMap_3(fun_69, variants_);
    struct DumpTree_List* list_113 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_113->head = call_946;
    list_113->tail = call_947;
    struct DumpTree_ call_948 = dumpTreeNew_((struct String){.str = "union", .len = 5}, list_113);
    match_281 = call_948;
    goto end_match_1188;
next_1206:;
    if ((expr_7.tag != Open_1)) goto next_1207;
    struct StringList* path_1 = (*(expr_7.Open_1)).t0;
    void* box_30 = (void*)malloc(sizeof(int));
    (*(((int*)box_30))) = 0;
    void* env_66 = box_30;
    struct StringDumpTree_Fun1 fun_70 = (struct StringDumpTree_Fun1){.fun = fun_33, .env = env_66};
    struct DumpTree_List* call_949 = listMap_1(fun_70, path_1);
    struct DumpTree_ call_950 = dumpTreeNew_((struct String){.str = "open", .len = 4}, call_949);
    match_281 = call_950;
    goto end_match_1188;
next_1207:;
    exit(1);
end_match_1188:;
    return match_281;
}

struct DumpTree_ fun_34(void* env_31, struct HExpr_ arg_80) {
    struct DumpTree_ call_951 = hxDump_(arg_80);
    return call_951;
}

struct DumpTree_ fun_35(void* env_32, struct String arg_81) {
    struct DumpTree_ call_952 = dumpTreeNewLeaf_(arg_81);
    return call_952;
}

struct DumpTree_ hxDump_(struct HExpr_ expr_8) {
    struct DumpTree_ match_282;
    if ((expr_8.tag != Lit_3)) goto next_1209;
    struct Lit_ lit_8 = (*(expr_8.Lit_3)).t0;
    struct String call_953 = litToString_(lit_8);
    struct DumpTree_ call_954 = dumpTreeNewLeaf_(call_953);
    match_282 = call_954;
    goto end_match_1208;
next_1209:;
    if ((expr_8.tag != Prim_)) goto next_1210;
    struct DumpTree_ call_955 = dumpTreeNewLeaf_((struct String){.str = "prim", .len = 4});
    match_282 = call_955;
    goto end_match_1208;
next_1210:;
    if ((expr_8.tag != Ref_2)) goto next_1211;
    int serial_8 = (*(expr_8.Ref_2)).t0;
    struct String call_956 = str_of_int(serial_8);
    struct DumpTree_ call_957 = dumpTreeNewLeaf_(call_956);
    match_282 = call_957;
    goto end_match_1208;
next_1211:;
    if ((expr_8.tag != Match_2)) goto next_1212;
    struct HExpr_ target_2 = (*(expr_8.Match_2)).t0;
    struct HPat_HExpr_HExpr_Tuple3List* _arms_ = (*(expr_8.Match_2)).t1;
    struct Ty_ _ty_ = (*(expr_8.Match_2)).t2;
    struct IntIntTuple2 _loc_ = (*(expr_8.Match_2)).t3;
    struct DumpTree_ call_958 = hxDump_(target_2);
    struct DumpTree_List* list_114 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_114->head = call_958;
    list_114->tail = NULL;
    struct DumpTree_ call_959 = dumpTreeNew_((struct String){.str = "match", .len = 5}, list_114);
    match_282 = call_959;
    goto end_match_1208;
next_1212:;
    if ((expr_8.tag != Nav_3)) goto next_1213;
    struct HExpr_ l_16 = (*(expr_8.Nav_3)).t0;
    struct String r_29 = (*(expr_8.Nav_3)).t1;
    struct Ty_ _ty_1 = (*(expr_8.Nav_3)).t2;
    struct IntIntTuple2 _loc_1 = (*(expr_8.Nav_3)).t3;
    struct DumpTree_ call_960 = hxDump_(l_16);
    struct DumpTree_List* list_115 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_115->head = call_960;
    list_115->tail = NULL;
    struct DumpTree_ call_961 = dumpTreeNew_(str_add((struct String){.str = ".", .len = 1}, r_29), list_115);
    match_282 = call_961;
    goto end_match_1208;
next_1213:;
    if ((expr_8.tag != Inf_)) goto next_1214;
    struct HExpr_List* items_5 = (*(expr_8.Inf_)).t1;
    struct Ty_ _ty_2 = (*(expr_8.Inf_)).t2;
    struct IntIntTuple2 _loc_2 = (*(expr_8.Inf_)).t3;
    void* box_31 = (void*)malloc(sizeof(int));
    (*(((int*)box_31))) = 0;
    void* env_67 = box_31;
    struct HExpr_DumpTree_Fun1 fun_71 = (struct HExpr_DumpTree_Fun1){.fun = fun_34, .env = env_67};
    struct DumpTree_List* call_962 = listMap_2(fun_71, items_5);
    struct DumpTree_ call_963 = dumpTreeNew_((struct String){.str = "inf", .len = 3}, call_962);
    match_282 = call_963;
    goto end_match_1208;
next_1214:;
    if ((expr_8.tag != Let_2)) goto next_1215;
    struct HPat_ _pat_ = (*(expr_8.Let_2)).t0;
    struct HExpr_ body_7 = (*(expr_8.Let_2)).t1;
    struct HExpr_ next_9 = (*(expr_8.Let_2)).t2;
    struct Ty_ _ty_3 = (*(expr_8.Let_2)).t3;
    struct IntIntTuple2 _loc_3 = (*(expr_8.Let_2)).t4;
    struct DumpTree_ call_964 = hxDump_(next_9);
    struct DumpTree_ call_965 = hxDump_(body_7);
    struct DumpTree_List* list_116 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_116->head = call_965;
    list_116->tail = NULL;
    struct DumpTree_ call_966 = dumpTreeNew_((struct String){.str = "let-val", .len = 7}, list_116);
    struct DumpTree_ call_967 = dumpTreeAttachNext_(call_964, call_966);
    match_282 = call_967;
    goto end_match_1208;
next_1215:;
    if ((expr_8.tag != LetFun_1)) goto next_1216;
    int callee_4 = (*(expr_8.LetFun_1)).t0;
    struct HPat_List* _args_ = (*(expr_8.LetFun_1)).t2;
    struct HExpr_ body_8 = (*(expr_8.LetFun_1)).t3;
    struct HExpr_ next_10 = (*(expr_8.LetFun_1)).t4;
    struct Ty_ _ty_4 = (*(expr_8.LetFun_1)).t5;
    struct IntIntTuple2 _loc_4 = (*(expr_8.LetFun_1)).t6;
    struct DumpTree_ call_968 = hxDump_(next_10);
    struct String call_969 = str_of_int(callee_4);
    struct DumpTree_ call_970 = dumpTreeNewLeaf_(call_969);
    struct DumpTree_ call_971 = hxDump_(body_8);
    struct DumpTree_List* list_118 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_118->head = call_971;
    list_118->tail = NULL;
    struct DumpTree_List* list_117 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_117->head = call_970;
    list_117->tail = list_118;
    struct DumpTree_ call_972 = dumpTreeNew_((struct String){.str = "let-fun", .len = 7}, list_117);
    struct DumpTree_ call_973 = dumpTreeAttachNext_(call_968, call_972);
    match_282 = call_973;
    goto end_match_1208;
next_1216:;
    if ((expr_8.tag != TyDecl_)) goto next_1217;
    if (((*(expr_8.TyDecl_)).t1.tag != Synonym_1)) goto next_1217;
    struct Ty_ _ty_5 = (*((*(expr_8.TyDecl_)).t1.Synonym_1)).t0;
    struct IntIntTuple2 _loc_5 = (*((*(expr_8.TyDecl_)).t1.Synonym_1)).t1;
    struct DumpTree_ call_974 = dumpTreeNew_((struct String){.str = "synonym", .len = 7}, NULL);
    match_282 = call_974;
    goto end_match_1208;
next_1217:;
    if ((expr_8.tag != TyDecl_)) goto next_1218;
    if (((*(expr_8.TyDecl_)).t1.tag != Union_1)) goto next_1218;
    struct String ident_17 = (*((*(expr_8.TyDecl_)).t1.Union_1)).t0;
    struct DumpTree_ call_975 = dumpTreeNewLeaf_(ident_17);
    struct DumpTree_List* list_119 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_119->head = call_975;
    list_119->tail = NULL;
    struct DumpTree_ call_976 = dumpTreeNew_((struct String){.str = "union", .len = 5}, list_119);
    match_282 = call_976;
    goto end_match_1208;
next_1218:;
    if ((expr_8.tag != Open_2)) goto next_1219;
    struct StringList* path_2 = (*(expr_8.Open_2)).t0;
    void* box_32 = (void*)malloc(sizeof(int));
    (*(((int*)box_32))) = 0;
    void* env_68 = box_32;
    struct StringDumpTree_Fun1 fun_72 = (struct StringDumpTree_Fun1){.fun = fun_35, .env = env_68};
    struct DumpTree_List* call_977 = listMap_1(fun_72, path_2);
    struct DumpTree_ call_978 = dumpTreeNew_((struct String){.str = "open", .len = 4}, call_977);
    match_282 = call_978;
    goto end_match_1208;
next_1219:;
    if ((expr_8.tag != Error_2)) goto next_1220;
    struct String msg_1 = (*(expr_8.Error_2)).t0;
    struct IntIntTuple2 loc_26 = (*(expr_8.Error_2)).t1;
    struct DumpTree_ call_979 = dumpTreeFromError_(msg_1, loc_26);
    match_282 = call_979;
    goto end_match_1208;
next_1220:;
    exit(1);
end_match_1208:;
    return match_282;
}

int fun_1(struct Token_IntIntTuple2Tuple2 arg_188) {
    struct Token_ token_13 = arg_188.t0;
    int y_12 = arg_188.t1.t0;
    int x_20 = arg_188.t1.t1;
    struct String call_980 = tokenToString_(token_13);
    printf("%s (%d, %d)\n", call_980.str, y_12, x_20);
    int call_981 = 0;
    return 0;
}

int fun_36(void* env_33, struct Token_IntIntTuple2Tuple2 arg_82) {
    int call_982 = fun_1(arg_82);
    return 0;
}

int fun_2(struct StringIntIntTuple2Tuple2 arg_189) {
    struct String msg_2 = arg_189.t0;
    int y_13 = arg_189.t1.t0;
    int x_21 = arg_189.t1.t1;
    printf("ERROR %s (%d:%d)\n", msg_2.str, (y_13 + 1), (x_21 + 1));
    int call_983 = 0;
    return 0;
}

int fun_37(void* env_34, struct StringIntIntTuple2Tuple2 arg_83) {
    int call_984 = fun_2(arg_83);
    return 0;
}

struct StringStringFun1 {
    struct String(*fun)(void*, struct String);
    void* env;
};

int doFile_(struct StringStringFun1 fileReadAllText_1, struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, char charNull_, struct String filePath_) {
    printf("FILE %s\n", filePath_.str);
    int call_985 = 0;
    struct String app_70 = fileReadAllText_1.fun(fileReadAllText_1.env, filePath_);
    struct String source_ = app_70;
    struct Token_IntIntTuple2Tuple2List* call_986 = tokenize_(charNull_, source_);
    struct Token_IntIntTuple2Tuple2List* tokens_ = call_986;
    void* box_33 = (void*)malloc(sizeof(int));
    (*(((int*)box_33))) = 0;
    void* env_69 = box_33;
    struct Token_IntIntTuple2Tuple2UnitFun1 fun_73 = (struct Token_IntIntTuple2Tuple2UnitFun1){.fun = fun_36, .env = env_69};
    int call_987 = listIter_2(fun_73, tokens_);
    struct AExpr_StringIntIntTuple2Tuple2ListTuple2 call_988 = parse_(tokens_);
    struct AExpr_ ast_ = call_988.t0;
    struct StringIntIntTuple2Tuple2List* errors_ = call_988.t1;
    printf("AST:\n");
    int call_989 = 0;
    struct DumpTree_ call_990 = axDump_(ast_);
    struct String call_991 = dumpTreeToString_(call_990);
    printf("%s\n", call_991.str);
    int call_992 = 0;
    void* box_34 = (void*)malloc(sizeof(int));
    (*(((int*)box_34))) = 0;
    void* env_70 = box_34;
    struct StringIntIntTuple2Tuple2UnitFun1 fun_74 = (struct StringIntIntTuple2Tuple2UnitFun1){.fun = fun_37, .env = env_70};
    int call_993 = listIter_1(fun_74, errors_);
    struct NameCtx_ call_994 = nameCtxEmpty_(0);
    struct NameCtx_ nameCtx_ = call_994;
    struct AExpr_NameCtx_Tuple2 tuple_604;
    tuple_604.t0 = ast_;
    tuple_604.t1 = nameCtx_;
    struct HExpr_NameCtx_Tuple2 call_995 = astToHir_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_604);
    struct HExpr_ expr_9 = call_995.t0;
    printf("HIR:\n");
    int call_996 = 0;
    struct DumpTree_ call_997 = hxDump_(expr_9);
    struct String call_998 = dumpTreeToString_(call_997);
    printf("%s\n", call_998.str);
    int call_999 = 0;
    return 0;
}

int doSelf_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, char charNull_, struct StringStringFun1 fileReadAllText_1) {
    int call_1000 = doFile_(fileReadAllText_1, litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, charNull_, (struct String){.str = "MiloneLang/Lexing.fs", .len = 20});
    int call_1001 = doFile_(fileReadAllText_1, litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, charNull_, (struct String){.str = "MiloneLang/Parsing.fs", .len = 21});
    int call_1002 = doFile_(fileReadAllText_1, litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, charNull_, (struct String){.str = "MiloneLang/AstToHir.fs", .len = 22});
    return 0;
}

struct String fileReadAllText_(struct String fileName_) {
    struct String call_1003 = file_read_all_text(fileName_);
    return call_1003;
}

struct String fun_38(void* env_35, struct String arg_84) {
    struct String call_1004 = fileReadAllText_(arg_84);
    return call_1004;
}

int main() {
    struct IntIntTuple2 tuple_605;
    tuple_605.t0 = (0 - 1);
    tuple_605.t1 = (0 - 1);
    struct IntIntTuple2 noLoc_ = tuple_605;
    struct IntIntTuple2* payload_192 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_192))) = noLoc_;
    struct Ty_ variant_192 = (struct Ty_){.tag = Error_1, .Error_1 = payload_192};
    struct Ty_ noTy_ = variant_192;
    struct TyCon_Ty_ListTuple2 tuple_606;
    tuple_606.t0 = (struct TyCon_){.tag = Bool_2};
    tuple_606.t1 = NULL;
    struct TyCon_Ty_ListTuple2* payload_193 = (struct TyCon_Ty_ListTuple2*)malloc(sizeof(struct TyCon_Ty_ListTuple2));
    (*(((struct TyCon_Ty_ListTuple2*)payload_193))) = tuple_606;
    struct Ty_ variant_193 = (struct Ty_){.tag = Con_, .Con_ = payload_193};
    struct Ty_ tyBool_ = variant_193;
    struct TyCon_Ty_ListTuple2 tuple_607;
    tuple_607.t0 = (struct TyCon_){.tag = Int_2};
    tuple_607.t1 = NULL;
    struct TyCon_Ty_ListTuple2* payload_194 = (struct TyCon_Ty_ListTuple2*)malloc(sizeof(struct TyCon_Ty_ListTuple2));
    (*(((struct TyCon_Ty_ListTuple2*)payload_194))) = tuple_607;
    struct Ty_ variant_194 = (struct Ty_){.tag = Con_, .Con_ = payload_194};
    struct Ty_ tyInt_ = variant_194;
    struct TyCon_Ty_ListTuple2 tuple_608;
    tuple_608.t0 = (struct TyCon_){.tag = Char_2};
    tuple_608.t1 = NULL;
    struct TyCon_Ty_ListTuple2* payload_195 = (struct TyCon_Ty_ListTuple2*)malloc(sizeof(struct TyCon_Ty_ListTuple2));
    (*(((struct TyCon_Ty_ListTuple2*)payload_195))) = tuple_608;
    struct Ty_ variant_195 = (struct Ty_){.tag = Con_, .Con_ = payload_195};
    struct Ty_ tyChar_ = variant_195;
    struct TyCon_Ty_ListTuple2 tuple_609;
    tuple_609.t0 = (struct TyCon_){.tag = Str_2};
    tuple_609.t1 = NULL;
    struct TyCon_Ty_ListTuple2* payload_196 = (struct TyCon_Ty_ListTuple2*)malloc(sizeof(struct TyCon_Ty_ListTuple2));
    (*(((struct TyCon_Ty_ListTuple2*)payload_196))) = tuple_609;
    struct Ty_ variant_196 = (struct Ty_){.tag = Con_, .Con_ = payload_196};
    struct Ty_ tyStr_ = variant_196;
    struct TyCon_Ty_ListTuple2 tuple_610;
    tuple_610.t0 = (struct TyCon_){.tag = Obj_};
    tuple_610.t1 = NULL;
    struct TyCon_Ty_ListTuple2* payload_197 = (struct TyCon_Ty_ListTuple2*)malloc(sizeof(struct TyCon_Ty_ListTuple2));
    (*(((struct TyCon_Ty_ListTuple2*)payload_197))) = tuple_610;
    struct Ty_ variant_197 = (struct Ty_){.tag = Con_, .Con_ = payload_197};
    struct Ty_ tyObj_ = variant_197;
    struct Ty_ call_1005 = tyTuple_(NULL);
    struct Ty_ tyUnit_ = call_1005;
    int* payload_198 = (int*)malloc(sizeof(int));
    (*(((int*)payload_198))) = 1;
    struct Lit_ variant_198 = (struct Lit_){.tag = Bool_, .Bool_ = payload_198};
    struct Lit_ litTrue_ = variant_198;
    int* payload_199 = (int*)malloc(sizeof(int));
    (*(((int*)payload_199))) = 0;
    struct Lit_ variant_199 = (struct Lit_){.tag = Bool_, .Bool_ = payload_199};
    struct Lit_ litFalse_ = variant_199;
    char call_1006 = ((char)0);
    char charNull_ = call_1006;
    void* box_35 = (void*)malloc(sizeof(int));
    (*(((int*)box_35))) = 0;
    void* env_71 = box_35;
    struct StringStringFun1 fun_75 = (struct StringStringFun1){.fun = fun_38, .env = env_71};
    int call_1007 = doSelf_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, charNull_, fun_75);
    return call_1007;
}

#line 139
#error 139:13 Undefined variable sprintf
