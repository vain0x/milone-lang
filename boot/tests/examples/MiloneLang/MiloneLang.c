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

enum Ty_Tag;

struct Ty_;

struct Ty_NameCtx_Tuple2;

struct ATy_NameCtx_Tuple2Ty_NameCtx_Tuple2Fun1;

struct Ty_List;

enum ATy_Tag;

struct ATy_;

struct ATy_List;

struct ATy_ListNameCtx_Tuple2;

struct Ty_ListNameCtx_Tuple2;

struct ATy_NameCtx_Tuple2;

struct Ty_ListNameCtx_Tuple2 go_63(struct ATy_NameCtx_Tuple2Ty_NameCtx_Tuple2Fun1 f_, struct Ty_List* acc_5, struct ATy_ListNameCtx_Tuple2 arg_77);

enum HExpr_Tag;

struct HExpr_;

struct HPat_HExpr_HExpr_Tuple3;

struct HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2;

struct AArm_NameCtx_Tuple2HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2Fun1;

struct HPat_HExpr_HExpr_Tuple3List;

enum AArm_Tag;

struct AArm_;

struct AArm_List;

struct AArm_ListNameCtx_Tuple2;

struct HPat_HExpr_HExpr_Tuple3ListNameCtx_Tuple2;

struct AArm_NameCtx_Tuple2;

struct HPat_HExpr_HExpr_Tuple3ListNameCtx_Tuple2 go_62(struct AArm_NameCtx_Tuple2HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2Fun1 f_, struct HPat_HExpr_HExpr_Tuple3List* acc_5, struct AArm_ListNameCtx_Tuple2 arg_78);

struct HExpr_NameCtx_Tuple2;

struct AExpr_NameCtx_Tuple2HExpr_NameCtx_Tuple2Fun1;

struct HExpr_List;

enum AExpr_Tag;

struct AExpr_;

struct AExpr_List;

struct AExpr_ListNameCtx_Tuple2;

struct HExpr_ListNameCtx_Tuple2;

struct AExpr_NameCtx_Tuple2;

struct HExpr_ListNameCtx_Tuple2 go_61(struct AExpr_NameCtx_Tuple2HExpr_NameCtx_Tuple2Fun1 f_, struct HExpr_List* acc_5, struct AExpr_ListNameCtx_Tuple2 arg_79);

struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1;

struct HPat_List;

enum APat_Tag;

struct APat_;

struct APat_List;

struct APat_ListNameCtx_Tuple2;

struct HPat_ListNameCtx_Tuple2;

struct APat_NameCtx_Tuple2;

struct HPat_ListNameCtx_Tuple2 go_60(struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1 f_, struct HPat_List* acc_5, struct APat_ListNameCtx_Tuple2 arg_80);

struct Ty_ListNameCtx_Tuple2 stMap_4(struct ATy_NameCtx_Tuple2Ty_NameCtx_Tuple2Fun1 f_, struct ATy_ListNameCtx_Tuple2 arg_81);

struct HPat_HExpr_HExpr_Tuple3ListNameCtx_Tuple2 stMap_3(struct AArm_NameCtx_Tuple2HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2Fun1 f_, struct AArm_ListNameCtx_Tuple2 arg_82);

struct HExpr_ListNameCtx_Tuple2 stMap_2(struct AExpr_NameCtx_Tuple2HExpr_NameCtx_Tuple2Fun1 f_, struct AExpr_ListNameCtx_Tuple2 arg_83);

struct HPat_ListNameCtx_Tuple2 stMap_1(struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1 f_, struct APat_ListNameCtx_Tuple2 arg_84);

struct StringList* cons_1(struct String head_, struct StringList* tail_);

int listIsEmpty_4(struct StringList* xs_6);

enum DumpTree_Tag;

struct DumpTree_;

struct DumpTree_List;

int listIsEmpty_3(struct DumpTree_List* xs_6);

int listIsEmpty_2(struct APat_List* xs_6);

int listIsEmpty_1(struct AExpr_List* xs_6);

struct IntIntTuple2;

struct Token_IntIntTuple2Tuple2;

struct Token_IntIntTuple2Tuple2List;

struct Token_IntIntTuple2Tuple2List* go_59(struct Token_IntIntTuple2Tuple2List* acc_8, struct Token_IntIntTuple2Tuple2List* xs_8);

struct ATy_List* go_58(struct ATy_List* acc_8, struct ATy_List* xs_8);

enum AVariant_Tag;

struct AVariant_;

struct AVariant_List;

struct AVariant_List* go_57(struct AVariant_List* acc_8, struct AVariant_List* xs_8);

struct APat_List* go_56(struct APat_List* acc_8, struct APat_List* xs_8);

struct AArm_List* go_55(struct AArm_List* acc_8, struct AArm_List* xs_8);

struct StringList* go_54(struct StringList* acc_8, struct StringList* xs_8);

struct AExpr_List* go_53(struct AExpr_List* acc_8, struct AExpr_List* xs_8);

struct Ty_List* go_68(struct Ty_List* acc_8, struct Ty_List* xs_8);

struct HPat_HExpr_HExpr_Tuple3List* go_67(struct HPat_HExpr_HExpr_Tuple3List* acc_8, struct HPat_HExpr_HExpr_Tuple3List* xs_8);

struct HExpr_List* go_66(struct HExpr_List* acc_8, struct HExpr_List* xs_8);

struct HPat_List* go_65(struct HPat_List* acc_8, struct HPat_List* xs_8);

struct DumpTree_List* go_64(struct DumpTree_List* acc_8, struct DumpTree_List* xs_8);

struct Token_IntIntTuple2Tuple2List* listRev_7(struct Token_IntIntTuple2Tuple2List* xs_7);

struct ATy_List* listRev_6(struct ATy_List* xs_7);

struct AVariant_List* listRev_5(struct AVariant_List* xs_7);

struct APat_List* listRev_4(struct APat_List* xs_7);

struct AArm_List* listRev_3(struct AArm_List* xs_7);

struct StringList* listRev_2(struct StringList* xs_7);

struct AExpr_List* listRev_1(struct AExpr_List* xs_7);

struct Ty_List* listRev_12(struct Ty_List* xs_7);

struct HPat_HExpr_HExpr_Tuple3List* listRev_11(struct HPat_HExpr_HExpr_Tuple3List* xs_7);

struct HExpr_List* listRev_10(struct HExpr_List* xs_7);

struct HPat_List* listRev_9(struct HPat_List* xs_7);

struct DumpTree_List* listRev_8(struct DumpTree_List* xs_7);

int go_52(int len_, struct StringList* xs_11);

int listLength_1(struct StringList* xs_10);

struct StringIntIntTuple2Tuple2UnitFun1;

struct StringIntIntTuple2Tuple2;

struct StringIntIntTuple2Tuple2List;

int listIter_1(struct StringIntIntTuple2Tuple2UnitFun1 f_2, struct StringIntIntTuple2Tuple2List* xs_13);

struct HExpr_Ty_Fun1;

struct Ty_List* go_51(struct HExpr_Ty_Fun1 f_3, struct Ty_List* acc_9, struct HExpr_List* xs_16);

struct HPat_HExpr_HExpr_Tuple3HPat_HExpr_HExpr_Tuple3Fun1;

struct HPat_HExpr_HExpr_Tuple3List* go_50(struct HPat_HExpr_HExpr_Tuple3HPat_HExpr_HExpr_Tuple3Fun1 f_3, struct HPat_HExpr_HExpr_Tuple3List* acc_9, struct HPat_HExpr_HExpr_Tuple3List* xs_16);

struct HExpr_HExpr_Fun1;

struct HExpr_List* go_49(struct HExpr_HExpr_Fun1 f_3, struct HExpr_List* acc_9, struct HExpr_List* xs_16);

struct HPat_HPat_Fun1;

struct HPat_List* go_48(struct HPat_HPat_Fun1 f_3, struct HPat_List* acc_9, struct HPat_List* xs_16);

struct ATy_DumpTree_Fun1;

struct DumpTree_List* go_47(struct ATy_DumpTree_Fun1 f_3, struct DumpTree_List* acc_9, struct ATy_List* xs_16);

struct AArm_DumpTree_Fun1;

struct DumpTree_List* go_46(struct AArm_DumpTree_Fun1 f_3, struct DumpTree_List* acc_9, struct AArm_List* xs_16);

struct APat_DumpTree_Fun1;

struct DumpTree_List* go_45(struct APat_DumpTree_Fun1 f_3, struct DumpTree_List* acc_9, struct APat_List* xs_16);

struct AExpr_DumpTree_Fun1;

struct DumpTree_List* go_44(struct AExpr_DumpTree_Fun1 f_3, struct DumpTree_List* acc_9, struct AExpr_List* xs_16);

struct AVariant_DumpTree_Fun1;

struct DumpTree_List* go_43(struct AVariant_DumpTree_Fun1 f_3, struct DumpTree_List* acc_9, struct AVariant_List* xs_16);

struct StringDumpTree_Fun1;

struct DumpTree_List* go_42(struct StringDumpTree_Fun1 f_3, struct DumpTree_List* acc_9, struct StringList* xs_16);

struct Ty_List* listMap_10(struct HExpr_Ty_Fun1 f_3, struct HExpr_List* xs_15);

struct HPat_HExpr_HExpr_Tuple3List* listMap_9(struct HPat_HExpr_HExpr_Tuple3HPat_HExpr_HExpr_Tuple3Fun1 f_3, struct HPat_HExpr_HExpr_Tuple3List* xs_15);

struct HExpr_List* listMap_8(struct HExpr_HExpr_Fun1 f_3, struct HExpr_List* xs_15);

struct HPat_List* listMap_7(struct HPat_HPat_Fun1 f_3, struct HPat_List* xs_15);

struct DumpTree_List* listMap_6(struct ATy_DumpTree_Fun1 f_3, struct ATy_List* xs_15);

struct DumpTree_List* listMap_5(struct AArm_DumpTree_Fun1 f_3, struct AArm_List* xs_15);

struct DumpTree_List* listMap_4(struct APat_DumpTree_Fun1 f_3, struct APat_List* xs_15);

struct DumpTree_List* listMap_3(struct AExpr_DumpTree_Fun1 f_3, struct AExpr_List* xs_15);

struct DumpTree_List* listMap_2(struct AVariant_DumpTree_Fun1 f_3, struct AVariant_List* xs_15);

struct DumpTree_List* listMap_1(struct StringDumpTree_Fun1 f_3, struct StringList* xs_15);

int intMin_(int x_9, int y_3);

int intMax_(int x_10, int y_4);

int intEq_(int x_11, int y_5);

struct String strSlice_(int start_, int endIndex_1, struct String s_3);

struct StringStringListTuple2;

struct StringStringListTuple2 go_18(struct StringList* xs_22, int xn_);

struct String strConcat_(struct StringList* xs_21);

int locX_(struct IntIntTuple2 arg_85);

int locY_(struct IntIntTuple2 arg_86);

int locIsSameRow_(struct IntIntTuple2 first_, struct IntIntTuple2 second_);

int locIsSameColumn_(struct IntIntTuple2 first_1, struct IntIntTuple2 second_1);

int locInside_(struct IntIntTuple2 firstLoc_, struct IntIntTuple2 secondLoc_);

struct IntIntTuple2 locAddX_(int dx_, struct IntIntTuple2 arg_87);

struct IntIntTuple2 locMax_(struct IntIntTuple2 arg_88, struct IntIntTuple2 arg_89);

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

struct AExpr_ app_(struct IntIntTuple2 loc_8, struct AExpr_ x_16, struct AExpr_ f_5);

struct AExpr_ axApp3_(struct AExpr_ f_4, struct AExpr_ x1_, struct AExpr_ x2_, struct AExpr_ x3_, struct IntIntTuple2 loc_8);

struct AExpr_ axNot_(struct Lit_ litFalse_, struct AExpr_ arg_, struct IntIntTuple2 loc_9);

struct String go_19(struct String acc_10, int len_2, int n_1);

struct String intToHexWithPadding_(int len_1, int value_3);

struct StringDumpTree_ListDumpTree_ListTuple3;

struct DumpTree_ dumpTreeNew_(struct String text_43, struct DumpTree_List* children_);

struct DumpTree_ dumpTreeNewLeaf_(struct String text_44);

struct DumpTree_ dumpTreeAttachNext_(struct DumpTree_ next_1, struct DumpTree_ tree_);

struct DumpTree_ dumpTreeFromError_(struct String msg_, struct IntIntTuple2 arg_90);

int charIsControl_(char c_8);

int charNeedsEscaping_(char c_9);

int go_20(struct String str_2, int i_50);

int strNeedsEscaping_(struct String str_2);

struct IntStringTuple2;

struct IntStringTuple2 strEscapeCore_(int i_51, struct String str_3);

int raw_(struct String str_4, int i_53);

struct IntStringListTuple2;

struct StringList* go_21(struct String str_4, struct StringList* acc_11, int i_52);

struct String strEscape_(struct String str_4);

struct StringList* goChildren_(struct String eol_1, struct DumpTree_List* children_2, struct StringList* acc_14);

struct StringList* goNext_(struct String eol_2, struct DumpTree_List* next_2, struct StringList* acc_15);

struct StringList* go_22(struct String eol_, struct DumpTree_ node_1, struct StringList* acc_13);

struct String dumpTreeToString_(struct DumpTree_ node_);

struct IntStringTuple2List;

struct IntStringTuple2ListIntTuple2;

struct NameCtx_ nameCtxEmpty_(int arg_91);

struct IntNameCtx_Tuple2;

struct IntNameCtx_Tuple2 nameCtxAdd_1(struct String ident_, struct NameCtx_ arg_92);

struct Ty_Ty_Fun1;

enum Trait_Tag;

struct Trait_;

struct Ty_Ty_Ty_Tuple3;

struct Trait_ traitMapTys_(struct Ty_Ty_Fun1 f_6, struct Trait_ it_);

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

struct HPat_ fun_2(void* env_, struct HPat_ arg_6);

struct HPat_ fun_3(void* env_1, struct HPat_ arg_9);

struct HPat_ go_25(struct IntIntTuple2IntIntTuple2Fun1 g_, struct Ty_Ty_Fun1 f_7, struct HPat_ pat_3);

struct HPat_ patMap_(struct Ty_Ty_Fun1 f_7, struct IntIntTuple2IntIntTuple2Fun1 g_, struct HPat_ pat_2);

struct HExpr_ hxTrue_(struct Lit_ litTrue_, struct IntIntTuple2 loc_13);

struct HExpr_ hxFalse_(struct Lit_ litFalse_, struct IntIntTuple2 loc_14);

enum InfOp_Tag;

struct InfOp_;

struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4;

struct HExpr_ hxApp_(struct HExpr_ f_8, struct HExpr_ x_19, struct Ty_ ty_27, struct IntIntTuple2 loc_15);

struct HExpr_ hxAnno_(struct HExpr_ expr_, struct Ty_ ty_28, struct IntIntTuple2 loc_16);

struct HExpr_ hxSemi_(struct Ty_ noTy_, struct HExpr_List* items_, struct IntIntTuple2 loc_17);

struct HExpr_ hxCallProc_(struct HExpr_ callee_1, struct HExpr_List* args_1, struct Ty_ resultTy_2, struct IntIntTuple2 loc_18);

struct HExpr_ hxCallClosure_(struct HExpr_ callee_2, struct HExpr_List* args_2, struct Ty_ resultTy_3, struct IntIntTuple2 loc_19);

struct Ty_Ty_Ty_Ty_Ty_Tuple5;

struct Ty_ fun_4(void* env_2, struct HExpr_ arg_12);

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

struct HPat_ goPat_(struct IntIntTuple2IntIntTuple2Fun1 g_1, struct Ty_Ty_Fun1 f_9, struct HPat_ pat_7);

struct HPat_HExpr_HExpr_Tuple3 fun_(struct IntIntTuple2IntIntTuple2Fun1 g_1, struct Ty_Ty_Fun1 f_9, struct HPat_HExpr_HExpr_Tuple3 arg_93);

struct HPat_HExpr_HExpr_Tuple3 fun_5(void* env_3, struct HPat_HExpr_HExpr_Tuple3 arg_18);

struct HExpr_ fun_6(void* env_4, struct HExpr_ arg_21);

struct HPat_ fun_7(void* env_5, struct HPat_ arg_24);

struct HExpr_ go_26(struct IntIntTuple2IntIntTuple2Fun1 g_1, struct Ty_Ty_Fun1 f_9, struct HExpr_ expr_5);

struct HExpr_ exprMap_(struct Ty_Ty_Fun1 f_9, struct IntIntTuple2IntIntTuple2Fun1 g_1, struct HExpr_ expr_4);

struct Ty_ exprToTy_(struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct HExpr_ expr_6);

struct IntIntTuple2 go_(int r_, struct String text_, int y_1, int x_2, int i_);

struct IntIntTuple2 locShift_(struct String text_, int l_, int r_, struct IntIntTuple2 arg_94);

int charIsSpace_(char c_);

int charIsDigit_(char c_1);

int charIsAlpha_(char c_2);

int charIsIdent_(char c_3);

int charIsOp_(char c_4);

int charIsPun_(char c_5);

int go_1(struct String s_, struct String prefix_, int pi_, int si_);

int strIsFollowedBy_(int i_1, struct String prefix_, struct String s_);

int strIsFollowedByRawQuotes_(int i_2, struct String s_1);

int scanError_(struct String arg_95, int i_3);

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

struct Token_ tokenFromCharLit_(struct String text_24, int l_5, int r_5);

int next_(int r_6, struct String text_25, int i_33);

struct String go_10(int r_6, struct String text_25, struct StringList* acc_, int i_32);

struct Token_ tokenFromStrLit_(struct String text_25, int l_6, int r_6);

struct Token_ tokenFromStrLitRaw_(struct String text_26, int l_7, int r_7);

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4;

struct StringIntTuple2;

struct StringIntTuple2 tokCtxToTextIndex_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 arg_96);

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokCtxSkip_(int r_8, struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 arg_97);

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokCtxPush_(struct Token_ kind_, int r_9, struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 arg_98);

struct Token_IntIntTuple2Tuple2List* tokEof_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 arg_99);

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokError_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_);

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokComment_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_1);

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokSpace_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_2);

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokPun_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_3);

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokOp_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_4);

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokIdent_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_5);

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokIntLit_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_6);

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokCharLit_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_7);

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokStrLit_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_8);

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokStrLitRaw_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_9);

struct Token_IntIntTuple2Tuple2List* go_11(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_10);

struct Token_IntIntTuple2Tuple2List* tokenize_(struct String text_41);

int leadsExpr_1(struct Token_IntIntTuple2Tuple2List* tokens_1);

int leadsArg_1(struct Token_IntIntTuple2Tuple2List* tokens_2);

int leadsPat_1(struct Token_IntIntTuple2Tuple2List* tokens_3);

struct IntIntTuple2 nextLoc_1(struct Token_IntIntTuple2Tuple2List* tokens_4);

int nextInside_1(struct IntIntTuple2 baseLoc_, struct Token_IntIntTuple2Tuple2List* tokens_5);

struct StringIntIntTuple2Tuple2List* parseErrorCore_1(struct String msg_2, struct IntIntTuple2 loc_30, struct Token_IntIntTuple2Tuple2List* tokens_6, struct StringIntIntTuple2Tuple2List* errors_1);

struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2;

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyError_1(struct String msg_3, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_100);

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatError_1(struct String msg_4, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_101);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseExprError_1(struct String msg_5, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_102);

struct StringIntIntTuple2Tuple2List* parseNewError_1(struct String msg_6, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_103);

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyAtom_(struct IntIntTuple2 baseLoc_1, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_104);

struct ATy_StringIntIntTuple2Tuple3;

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_41(struct IntIntTuple2 baseLoc_2, struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 arg_105);

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTySuffix_(struct IntIntTuple2 baseLoc_2, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_106);

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyPrefix_(struct IntIntTuple2 baseLoc_3, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_107);

struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_28(struct IntIntTuple2 baseLoc_4, struct ATy_List* acc_16, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_108);

struct ATy_ListIntIntTuple2Tuple2;

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyTuple_(struct IntIntTuple2 baseLoc_4, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_109);

struct ATy_ATy_IntIntTuple2Tuple3;

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyFun_(struct IntIntTuple2 baseLoc_5, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_110);

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTy_(struct IntIntTuple2 baseLoc_6, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_111);

struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct StringATy_ListIntIntTuple2Tuple3;

struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_29(struct IntIntTuple2 baseLoc_7, struct AVariant_List* acc_17, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_112);

enum ATyDecl_Tag;

struct ATyDecl_;

struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyDeclUnion_(struct IntIntTuple2 baseLoc_7, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_113);

struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyDeclBody_(struct IntIntTuple2 baseLoc_8, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_114);

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatParenBody_(struct IntIntTuple2 baseLoc_9, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_115);

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_30(struct IntIntTuple2 baseLoc_10, struct APat_List* patAcc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_116);

struct APat_ListIntIntTuple2Tuple2;

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatListBody_(struct IntIntTuple2 baseLoc_10, struct IntIntTuple2 bracketLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_117);

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatAtom_(struct IntIntTuple2 baseLoc_11, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_118);

struct APat_StringIntIntTuple2Tuple3;

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatNav_(struct IntIntTuple2 baseLoc_12, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_119);

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_31(struct IntIntTuple2 argBaseLoc_, struct IntIntTuple2 baseLoc_13, struct APat_List* acc_18, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_120);

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatCallArgs_(struct IntIntTuple2 baseLoc_13, struct IntIntTuple2 calleeLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_121);

struct APat_APat_ListIntIntTuple2Tuple3;

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatCall_(struct IntIntTuple2 baseLoc_14, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_122);

struct APat_APat_IntIntTuple2Tuple3;

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatCons_(struct IntIntTuple2 baseLoc_15, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_123);

struct APat_ATy_IntIntTuple2Tuple3;

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatAnno_(struct IntIntTuple2 baseLoc_16, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_124);

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_32(struct IntIntTuple2 baseLoc_17, struct APat_List* acc_19, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_125);

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatTuple_(struct IntIntTuple2 baseLoc_17, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_126);

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatAs_(struct IntIntTuple2 baseLoc_18, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_127);

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatOr_(struct IntIntTuple2 baseLoc_19, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_128);

struct StringAPat_ListIntIntTuple2Tuple3;

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatLet_(struct IntIntTuple2 baseLoc_20, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_129);

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePat_(struct IntIntTuple2 baseLoc_21, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_130);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseRange_(struct IntIntTuple2 baseLoc_22, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_131);

struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseList_(struct IntIntTuple2 baseLoc_23, struct IntIntTuple2 bracketLoc_1, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_132);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseThenClause_(struct IntIntTuple2 baseLoc_24, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_133);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseElseClause_(struct IntIntTuple2 baseLoc_25, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_134);

struct AExpr_AExpr_AExpr_IntIntTuple2Tuple4;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseIf_(struct IntIntTuple2 ifLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_135);

struct APat_AExpr_AExpr_IntIntTuple2Tuple4;

struct AArm_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct AArm_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseMatchArm_(struct IntIntTuple2 matchLoc_, struct IntIntTuple2 armLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_136);

struct AArm_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct AArm_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_33(struct IntIntTuple2 matchLoc_1, struct AArm_List* acc_20, struct IntIntTuple2 armLoc_2, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_137);

struct IntIntTuple2Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct AExpr_AArm_ListIntIntTuple2Tuple3;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseMatch_(struct IntIntTuple2 matchLoc_1, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_138);

struct APat_ListAExpr_IntIntTuple2Tuple3;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseFun_(struct IntIntTuple2 baseLoc_26, struct IntIntTuple2 funLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_139);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseParenBody_(struct IntIntTuple2 baseLoc_27, struct IntIntTuple2 parenLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_140);

struct Token_IntIntTuple2Tuple2List* parseAccessModifier_1(struct Token_IntIntTuple2Tuple2List* tokens_138);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseLet_(struct IntIntTuple2 letLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_141);

struct StringATy_IntIntTuple2Tuple3;

struct StringAVariant_ListIntIntTuple2Tuple3;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyDecl_(struct IntIntTuple2 typeLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_142);

struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_34(struct StringList* acc_21, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_143);

struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePath_(struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_144);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseOpen_(struct IntIntTuple2 openLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_145);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseAtom_(struct IntIntTuple2 baseLoc_29, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_146);

struct AExpr_AExpr_IntIntTuple2Tuple3;

struct AExpr_StringIntIntTuple2Tuple3;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_35(struct IntIntTuple2 baseLoc_30, struct AExpr_ acc_22, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_147);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseSuffix_(struct IntIntTuple2 baseLoc_30, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_148);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_36(struct IntIntTuple2 argBaseLoc_1, struct IntIntTuple2 calleeLoc_3, struct IntIntTuple2 baseLoc_31, struct AExpr_ callee_7, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_149);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseApp_(struct IntIntTuple2 baseLoc_31, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_150);

enum UniOp_Tag;

struct UniOp_;

struct UniOp_AExpr_IntIntTuple2Tuple3;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePrefix_(struct IntIntTuple2 baseLoc_32, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_151);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseNextLevelOp_(struct OpLevel_ level_1, struct IntIntTuple2 baseLoc_33, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_152);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 nextL_(struct IntIntTuple2 baseLoc_34, struct OpLevel_ level_2, struct AExpr_ expr_10, struct Op_ op_, struct IntIntTuple2 opLoc_2, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_153);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 nextR_(struct IntIntTuple2 baseLoc_34, struct OpLevel_ level_2, struct AExpr_ expr_12, struct Op_ op_1, struct IntIntTuple2 opLoc_3, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_154);

struct OpLevel_Token_IntIntTuple2Tuple2ListTuple2;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseOps_(struct OpLevel_ level_2, struct IntIntTuple2 baseLoc_34, struct AExpr_ first_3, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_155);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseOp_(struct OpLevel_ level_3, struct IntIntTuple2 baseLoc_35, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_156);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTupleItem_(struct IntIntTuple2 baseLoc_36, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_157);

struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_37(struct IntIntTuple2 baseLoc_37, struct AExpr_List* acc_23, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_158);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTuple_(struct IntIntTuple2 baseLoc_37, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_159);

struct AExpr_ATy_IntIntTuple2Tuple3;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseAnno_(struct IntIntTuple2 baseLoc_38, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_160);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseExpr_(struct IntIntTuple2 baseLoc_39, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_161);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseStmt_(struct IntIntTuple2 baseLoc_40, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_162);

struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_38(struct IntIntTuple2 baseLoc_41, struct AExpr_List* acc_24, struct IntIntTuple2 alignLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_163);

struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseStmts_(struct IntIntTuple2 baseLoc_41, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_164);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseSemi_(struct IntIntTuple2 baseLoc_42, struct IntIntTuple2 mainLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_165);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTopLevel_(struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_166);

struct AExpr_StringIntIntTuple2Tuple2ListTuple2;

struct AExpr_StringIntIntTuple2Tuple2ListTuple2 parse_(struct Token_IntIntTuple2Tuple2List* tokens_242);

struct HPrim_ opToPrim_(struct Op_ op_2);

struct APat_ go_39(struct IntIntTuple2 loc_69, struct APat_List* pats_5);

struct APat_ desugarListLitPat_(struct APat_List* pats_4, struct IntIntTuple2 loc_69);

struct AExpr_ go_40(struct IntIntTuple2 loc_70, struct AExpr_List* items_9);

struct AExpr_ desugarListLitExpr_(struct AExpr_List* items_8, struct IntIntTuple2 loc_70);

struct AExpr_ desugarIf_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct AExpr_ cond_2, struct AExpr_ body_13, struct AExpr_ alt_2, struct IntIntTuple2 loc_71);

struct AExpr_ desugarFun_(struct APat_List* pats_6, struct AExpr_ body_14, struct IntIntTuple2 loc_72);

struct AExpr_ desugarUniNeg_(struct AExpr_ arg_4, struct IntIntTuple2 loc_73);

struct AExpr_ desugarBinNe_(struct Lit_ litFalse_, struct AExpr_ l_17, struct AExpr_ r_31, struct IntIntTuple2 loc_74);

struct AExpr_ desugarBinLe_(struct Lit_ litFalse_, struct AExpr_ l_18, struct AExpr_ r_32, struct IntIntTuple2 loc_75);

struct AExpr_ desugarBinGt_(struct AExpr_ l_19, struct AExpr_ r_33, struct IntIntTuple2 loc_76);

struct AExpr_ desugarBinGe_(struct Lit_ litFalse_, struct AExpr_ l_20, struct AExpr_ r_34, struct IntIntTuple2 loc_77);

struct AExpr_ desugarBinAnd_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct AExpr_ l_21, struct AExpr_ r_35, struct IntIntTuple2 loc_78);

struct AExpr_ desugarBinOr_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct AExpr_ l_22, struct AExpr_ r_36, struct IntIntTuple2 loc_79);

struct AExpr_ desugarBinPipe_(struct AExpr_ l_23, struct AExpr_ r_37, struct IntIntTuple2 loc_80);

struct BoolAExpr_Tuple2;

struct BoolAExpr_Tuple2 tryDesugarIndexRange_(struct AExpr_ expr_17, struct IntIntTuple2 loc_81);

enum ALet_Tag;

struct ALet_;

struct StringAPat_ListAExpr_AExpr_IntIntTuple2Tuple5;

struct ALet_ desugarLet_(struct APat_ pat_24, struct AExpr_ body_15, struct AExpr_ next_11, struct IntIntTuple2 loc_82);

struct Ty_NameCtx_Tuple2 fun_8(void* env_6, struct ATy_NameCtx_Tuple2 arg_27);

struct Ty_NameCtx_Tuple2 onTy_(struct ATy_NameCtx_Tuple2 arg_167);

struct Ty_Tuple1;

struct HPat_NameCtx_Tuple2 fun_9(void* env_7, struct APat_NameCtx_Tuple2 arg_28);

struct HPat_NameCtx_Tuple2 fun_10(void* env_8, struct APat_NameCtx_Tuple2 arg_30);

struct HPat_NameCtx_Tuple2 onPat_(struct Ty_ noTy_, struct APat_NameCtx_Tuple2 arg_168);

struct HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2 onArm_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, struct AArm_NameCtx_Tuple2 arg_169);

struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8;

struct HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2 fun_11(void* env_9, struct AArm_NameCtx_Tuple2 arg_32);

struct HExpr_NameCtx_Tuple2 fun_12(void* env_10, struct AExpr_NameCtx_Tuple2 arg_41);

struct HExpr_NameCtx_Tuple2 fun_13(void* env_11, struct AExpr_NameCtx_Tuple2 arg_50);

struct HPat_NameCtx_Tuple2 fun_14(void* env_12, struct APat_NameCtx_Tuple2 arg_59);

struct HExpr_NameCtx_Tuple2 onExpr_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, struct AExpr_NameCtx_Tuple2 arg_170);

struct HExpr_NameCtx_Tuple2 astToHir_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, struct AExpr_NameCtx_Tuple2 arg_171);

struct String litToString_(struct Lit_ lit_5);

struct String tokenToString_(struct Token_ token_12);

struct DumpTree_ fun_15(void* env_13, struct ATy_ arg_61);

struct DumpTree_ fun_16(void* env_14, struct ATy_ arg_62);

struct DumpTree_ atDump_(struct ATy_ ty_43);

struct DumpTree_ fun_17(void* env_15, struct APat_ arg_63);

struct DumpTree_ fun_18(void* env_16, struct APat_ arg_64);

struct DumpTree_ fun_19(void* env_17, struct APat_ arg_65);

struct DumpTree_ fun_20(void* env_18, struct APat_ arg_66);

struct DumpTree_ apDump_(struct APat_ pat_10);

struct DumpTree_ fun_21(void* env_19, struct AExpr_ arg_67);

struct DumpTree_ dumpArm_(struct AArm_ arg_172);

struct DumpTree_ fun_22(void* env_20, struct AArm_ arg_68);

struct DumpTree_ fun_23(void* env_21, struct APat_ arg_69);

struct DumpTree_ fun_24(void* env_22, struct AExpr_ arg_70);

struct DumpTree_ fun_25(void* env_23, struct AExpr_ arg_71);

struct DumpTree_ fun_26(void* env_24, struct AExpr_ arg_72);

struct DumpTree_ dumpVariant_(struct AVariant_ arg_173);

struct DumpTree_ fun_27(void* env_25, struct AVariant_ arg_73);

struct DumpTree_ fun_28(void* env_26, struct String arg_74);

struct DumpTree_ axDump_(struct AExpr_ expr_7);

int fun_1(struct StringIntIntTuple2Tuple2 arg_174);

int fun_29(void* env_27, struct StringIntIntTuple2Tuple2 arg_75);

struct StringStringFun1;

int doFile_(struct StringStringFun1 fileReadAllText_1, struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, struct String filePath_);

int doSelf_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, struct StringStringFun1 fileReadAllText_1);

struct String fileReadAllText_(struct String fileName_);

struct String fun_30(void* env_28, struct String arg_76);

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

struct Ty_NameCtx_Tuple2 {
    struct Ty_ t0;
    struct NameCtx_ t1;
};

struct ATy_NameCtx_Tuple2Ty_NameCtx_Tuple2Fun1 {
    struct Ty_NameCtx_Tuple2(*fun)(void*, struct ATy_NameCtx_Tuple2);
    void* env;
};

struct Ty_List {
    struct Ty_ head;
    struct Ty_List* tail;
};

enum ATy_Tag {
    Missing_,
    Ident_1,
    Suffix_,
    Tuple_,
    Fun_1,
};

struct ATy_ {
    enum ATy_Tag tag;
    union {
        struct IntIntTuple2* Missing_;
        struct StringIntIntTuple2Tuple2* Ident_1;
        struct ATy_StringIntIntTuple2Tuple3* Suffix_;
        struct ATy_ListIntIntTuple2Tuple2* Tuple_;
        struct ATy_ATy_IntIntTuple2Tuple3* Fun_1;
    };
};

struct ATy_List {
    struct ATy_ head;
    struct ATy_List* tail;
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

struct Ty_ListNameCtx_Tuple2 go_63(struct ATy_NameCtx_Tuple2Ty_NameCtx_Tuple2Fun1 f_, struct Ty_List* acc_5, struct ATy_ListNameCtx_Tuple2 arg_77) {
    struct ATy_List* xs_1 = arg_77.t0;
    struct NameCtx_ ctx_1 = arg_77.t1;
    struct Ty_ListNameCtx_Tuple2 match_;
    if ((!((!(xs_1))))) goto next_2;
    struct Ty_List* call_6 = listRev_12(acc_5);
    struct Ty_ListNameCtx_Tuple2 tuple_;
    tuple_.t0 = call_6;
    tuple_.t1 = ctx_1;
    match_ = tuple_;
    goto end_match_1;
next_2:;
    if ((!(xs_1))) goto next_3;
    struct ATy_ x_3 = xs_1->head;
    struct ATy_List* xs_2 = xs_1->tail;
    struct ATy_NameCtx_Tuple2 tuple_1;
    tuple_1.t0 = x_3;
    tuple_1.t1 = ctx_1;
    struct Ty_NameCtx_Tuple2 app_1 = f_.fun(f_.env, tuple_1);
    struct Ty_ y_2 = app_1.t0;
    struct NameCtx_ ctx_2 = app_1.t1;
    struct Ty_List* list_ = (struct Ty_List*)malloc(sizeof(struct Ty_List));
    list_->head = y_2;
    list_->tail = acc_5;
    struct ATy_ListNameCtx_Tuple2 tuple_2;
    tuple_2.t0 = xs_2;
    tuple_2.t1 = ctx_2;
    struct Ty_ListNameCtx_Tuple2 call_7 = go_63(f_, list_, tuple_2);
    match_ = call_7;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return match_;
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

struct HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2 {
    struct HPat_HExpr_HExpr_Tuple3 t0;
    struct NameCtx_ t1;
};

struct AArm_NameCtx_Tuple2HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2Fun1 {
    struct HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2(*fun)(void*, struct AArm_NameCtx_Tuple2);
    void* env;
};

struct HPat_HExpr_HExpr_Tuple3List {
    struct HPat_HExpr_HExpr_Tuple3 head;
    struct HPat_HExpr_HExpr_Tuple3List* tail;
};

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

struct HPat_HExpr_HExpr_Tuple3ListNameCtx_Tuple2 go_62(struct AArm_NameCtx_Tuple2HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2Fun1 f_, struct HPat_HExpr_HExpr_Tuple3List* acc_5, struct AArm_ListNameCtx_Tuple2 arg_78) {
    struct AArm_List* xs_1 = arg_78.t0;
    struct NameCtx_ ctx_1 = arg_78.t1;
    struct HPat_HExpr_HExpr_Tuple3ListNameCtx_Tuple2 match_1;
    if ((!((!(xs_1))))) goto next_5;
    struct HPat_HExpr_HExpr_Tuple3List* call_8 = listRev_11(acc_5);
    struct HPat_HExpr_HExpr_Tuple3ListNameCtx_Tuple2 tuple_3;
    tuple_3.t0 = call_8;
    tuple_3.t1 = ctx_1;
    match_1 = tuple_3;
    goto end_match_4;
next_5:;
    if ((!(xs_1))) goto next_6;
    struct AArm_ x_3 = xs_1->head;
    struct AArm_List* xs_2 = xs_1->tail;
    struct AArm_NameCtx_Tuple2 tuple_4;
    tuple_4.t0 = x_3;
    tuple_4.t1 = ctx_1;
    struct HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2 app_2 = f_.fun(f_.env, tuple_4);
    struct HPat_HExpr_HExpr_Tuple3 y_2 = app_2.t0;
    struct NameCtx_ ctx_2 = app_2.t1;
    struct HPat_HExpr_HExpr_Tuple3List* list_1 = (struct HPat_HExpr_HExpr_Tuple3List*)malloc(sizeof(struct HPat_HExpr_HExpr_Tuple3List));
    list_1->head = y_2;
    list_1->tail = acc_5;
    struct AArm_ListNameCtx_Tuple2 tuple_5;
    tuple_5.t0 = xs_2;
    tuple_5.t1 = ctx_2;
    struct HPat_HExpr_HExpr_Tuple3ListNameCtx_Tuple2 call_9 = go_62(f_, list_1, tuple_5);
    match_1 = call_9;
    goto end_match_4;
next_6:;
    exit(1);
end_match_4:;
    return match_1;
}

struct HExpr_NameCtx_Tuple2 {
    struct HExpr_ t0;
    struct NameCtx_ t1;
};

struct AExpr_NameCtx_Tuple2HExpr_NameCtx_Tuple2Fun1 {
    struct HExpr_NameCtx_Tuple2(*fun)(void*, struct AExpr_NameCtx_Tuple2);
    void* env;
};

struct HExpr_List {
    struct HExpr_ head;
    struct HExpr_List* tail;
};

enum AExpr_Tag {
    Missing_2,
    Lit_1,
    Ident_3,
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
        struct StringIntIntTuple2Tuple2* Ident_3;
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

struct HExpr_ListNameCtx_Tuple2 go_61(struct AExpr_NameCtx_Tuple2HExpr_NameCtx_Tuple2Fun1 f_, struct HExpr_List* acc_5, struct AExpr_ListNameCtx_Tuple2 arg_79) {
    struct AExpr_List* xs_1 = arg_79.t0;
    struct NameCtx_ ctx_1 = arg_79.t1;
    struct HExpr_ListNameCtx_Tuple2 match_2;
    if ((!((!(xs_1))))) goto next_8;
    struct HExpr_List* call_10 = listRev_10(acc_5);
    struct HExpr_ListNameCtx_Tuple2 tuple_6;
    tuple_6.t0 = call_10;
    tuple_6.t1 = ctx_1;
    match_2 = tuple_6;
    goto end_match_7;
next_8:;
    if ((!(xs_1))) goto next_9;
    struct AExpr_ x_3 = xs_1->head;
    struct AExpr_List* xs_2 = xs_1->tail;
    struct AExpr_NameCtx_Tuple2 tuple_7;
    tuple_7.t0 = x_3;
    tuple_7.t1 = ctx_1;
    struct HExpr_NameCtx_Tuple2 app_3 = f_.fun(f_.env, tuple_7);
    struct HExpr_ y_2 = app_3.t0;
    struct NameCtx_ ctx_2 = app_3.t1;
    struct HExpr_List* list_2 = (struct HExpr_List*)malloc(sizeof(struct HExpr_List));
    list_2->head = y_2;
    list_2->tail = acc_5;
    struct AExpr_ListNameCtx_Tuple2 tuple_8;
    tuple_8.t0 = xs_2;
    tuple_8.t1 = ctx_2;
    struct HExpr_ListNameCtx_Tuple2 call_11 = go_61(f_, list_2, tuple_8);
    match_2 = call_11;
    goto end_match_7;
next_9:;
    exit(1);
end_match_7:;
    return match_2;
}

struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1 {
    struct HPat_NameCtx_Tuple2(*fun)(void*, struct APat_NameCtx_Tuple2);
    void* env;
};

struct HPat_List {
    struct HPat_ head;
    struct HPat_List* tail;
};

enum APat_Tag {
    Missing_1,
    Lit_,
    Ident_2,
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
        struct StringIntIntTuple2Tuple2* Ident_2;
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

struct HPat_ListNameCtx_Tuple2 go_60(struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1 f_, struct HPat_List* acc_5, struct APat_ListNameCtx_Tuple2 arg_80) {
    struct APat_List* xs_1 = arg_80.t0;
    struct NameCtx_ ctx_1 = arg_80.t1;
    struct HPat_ListNameCtx_Tuple2 match_3;
    if ((!((!(xs_1))))) goto next_11;
    struct HPat_List* call_12 = listRev_9(acc_5);
    struct HPat_ListNameCtx_Tuple2 tuple_9;
    tuple_9.t0 = call_12;
    tuple_9.t1 = ctx_1;
    match_3 = tuple_9;
    goto end_match_10;
next_11:;
    if ((!(xs_1))) goto next_12;
    struct APat_ x_3 = xs_1->head;
    struct APat_List* xs_2 = xs_1->tail;
    struct APat_NameCtx_Tuple2 tuple_10;
    tuple_10.t0 = x_3;
    tuple_10.t1 = ctx_1;
    struct HPat_NameCtx_Tuple2 app_4 = f_.fun(f_.env, tuple_10);
    struct HPat_ y_2 = app_4.t0;
    struct NameCtx_ ctx_2 = app_4.t1;
    struct HPat_List* list_3 = (struct HPat_List*)malloc(sizeof(struct HPat_List));
    list_3->head = y_2;
    list_3->tail = acc_5;
    struct APat_ListNameCtx_Tuple2 tuple_11;
    tuple_11.t0 = xs_2;
    tuple_11.t1 = ctx_2;
    struct HPat_ListNameCtx_Tuple2 call_13 = go_60(f_, list_3, tuple_11);
    match_3 = call_13;
    goto end_match_10;
next_12:;
    exit(1);
end_match_10:;
    return match_3;
}

struct Ty_ListNameCtx_Tuple2 stMap_4(struct ATy_NameCtx_Tuple2Ty_NameCtx_Tuple2Fun1 f_, struct ATy_ListNameCtx_Tuple2 arg_81) {
    struct ATy_List* xs_ = arg_81.t0;
    struct NameCtx_ ctx_ = arg_81.t1;
    struct ATy_ListNameCtx_Tuple2 tuple_12;
    tuple_12.t0 = xs_;
    tuple_12.t1 = ctx_;
    struct Ty_ListNameCtx_Tuple2 call_14 = go_63(f_, NULL, tuple_12);
    return call_14;
}

struct HPat_HExpr_HExpr_Tuple3ListNameCtx_Tuple2 stMap_3(struct AArm_NameCtx_Tuple2HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2Fun1 f_, struct AArm_ListNameCtx_Tuple2 arg_82) {
    struct AArm_List* xs_ = arg_82.t0;
    struct NameCtx_ ctx_ = arg_82.t1;
    struct AArm_ListNameCtx_Tuple2 tuple_13;
    tuple_13.t0 = xs_;
    tuple_13.t1 = ctx_;
    struct HPat_HExpr_HExpr_Tuple3ListNameCtx_Tuple2 call_15 = go_62(f_, NULL, tuple_13);
    return call_15;
}

struct HExpr_ListNameCtx_Tuple2 stMap_2(struct AExpr_NameCtx_Tuple2HExpr_NameCtx_Tuple2Fun1 f_, struct AExpr_ListNameCtx_Tuple2 arg_83) {
    struct AExpr_List* xs_ = arg_83.t0;
    struct NameCtx_ ctx_ = arg_83.t1;
    struct AExpr_ListNameCtx_Tuple2 tuple_14;
    tuple_14.t0 = xs_;
    tuple_14.t1 = ctx_;
    struct HExpr_ListNameCtx_Tuple2 call_16 = go_61(f_, NULL, tuple_14);
    return call_16;
}

struct HPat_ListNameCtx_Tuple2 stMap_1(struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1 f_, struct APat_ListNameCtx_Tuple2 arg_84) {
    struct APat_List* xs_ = arg_84.t0;
    struct NameCtx_ ctx_ = arg_84.t1;
    struct APat_ListNameCtx_Tuple2 tuple_15;
    tuple_15.t0 = xs_;
    tuple_15.t1 = ctx_;
    struct HPat_ListNameCtx_Tuple2 call_17 = go_60(f_, NULL, tuple_15);
    return call_17;
}

struct StringList* cons_1(struct String head_, struct StringList* tail_) {
    struct StringList* list_4 = (struct StringList*)malloc(sizeof(struct StringList));
    list_4->head = head_;
    list_4->tail = tail_;
    return list_4;
}

int listIsEmpty_4(struct StringList* xs_6) {
    int match_4;
    if ((!((!(xs_6))))) goto next_14;
    match_4 = 1;
    goto end_match_13;
next_14:;
    match_4 = 0;
    goto end_match_13;
next_15:;
end_match_13:;
    return match_4;
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

int listIsEmpty_3(struct DumpTree_List* xs_6) {
    int match_5;
    if ((!((!(xs_6))))) goto next_17;
    match_5 = 1;
    goto end_match_16;
next_17:;
    match_5 = 0;
    goto end_match_16;
next_18:;
end_match_16:;
    return match_5;
}

int listIsEmpty_2(struct APat_List* xs_6) {
    int match_6;
    if ((!((!(xs_6))))) goto next_20;
    match_6 = 1;
    goto end_match_19;
next_20:;
    match_6 = 0;
    goto end_match_19;
next_21:;
end_match_19:;
    return match_6;
}

int listIsEmpty_1(struct AExpr_List* xs_6) {
    int match_7;
    if ((!((!(xs_6))))) goto next_23;
    match_7 = 1;
    goto end_match_22;
next_23:;
    match_7 = 0;
    goto end_match_22;
next_24:;
end_match_22:;
    return match_7;
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

struct Token_IntIntTuple2Tuple2List* go_59(struct Token_IntIntTuple2Tuple2List* acc_8, struct Token_IntIntTuple2Tuple2List* xs_8) {
    struct Token_IntIntTuple2Tuple2List* match_8;
    if ((!((!(xs_8))))) goto next_26;
    match_8 = acc_8;
    goto end_match_25;
next_26:;
    if ((!(xs_8))) goto next_27;
    struct Token_IntIntTuple2Tuple2 x_5 = xs_8->head;
    struct Token_IntIntTuple2Tuple2List* xs_9 = xs_8->tail;
    struct Token_IntIntTuple2Tuple2List* list_5 = (struct Token_IntIntTuple2Tuple2List*)malloc(sizeof(struct Token_IntIntTuple2Tuple2List));
    list_5->head = x_5;
    list_5->tail = acc_8;
    struct Token_IntIntTuple2Tuple2List* call_18 = go_59(list_5, xs_9);
    match_8 = call_18;
    goto end_match_25;
next_27:;
    exit(1);
end_match_25:;
    return match_8;
}

struct ATy_List* go_58(struct ATy_List* acc_8, struct ATy_List* xs_8) {
    struct ATy_List* match_9;
    if ((!((!(xs_8))))) goto next_29;
    match_9 = acc_8;
    goto end_match_28;
next_29:;
    if ((!(xs_8))) goto next_30;
    struct ATy_ x_5 = xs_8->head;
    struct ATy_List* xs_9 = xs_8->tail;
    struct ATy_List* list_6 = (struct ATy_List*)malloc(sizeof(struct ATy_List));
    list_6->head = x_5;
    list_6->tail = acc_8;
    struct ATy_List* call_19 = go_58(list_6, xs_9);
    match_9 = call_19;
    goto end_match_28;
next_30:;
    exit(1);
end_match_28:;
    return match_9;
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

struct AVariant_List* go_57(struct AVariant_List* acc_8, struct AVariant_List* xs_8) {
    struct AVariant_List* match_10;
    if ((!((!(xs_8))))) goto next_32;
    match_10 = acc_8;
    goto end_match_31;
next_32:;
    if ((!(xs_8))) goto next_33;
    struct AVariant_ x_5 = xs_8->head;
    struct AVariant_List* xs_9 = xs_8->tail;
    struct AVariant_List* list_7 = (struct AVariant_List*)malloc(sizeof(struct AVariant_List));
    list_7->head = x_5;
    list_7->tail = acc_8;
    struct AVariant_List* call_20 = go_57(list_7, xs_9);
    match_10 = call_20;
    goto end_match_31;
next_33:;
    exit(1);
end_match_31:;
    return match_10;
}

struct APat_List* go_56(struct APat_List* acc_8, struct APat_List* xs_8) {
    struct APat_List* match_11;
    if ((!((!(xs_8))))) goto next_35;
    match_11 = acc_8;
    goto end_match_34;
next_35:;
    if ((!(xs_8))) goto next_36;
    struct APat_ x_5 = xs_8->head;
    struct APat_List* xs_9 = xs_8->tail;
    struct APat_List* list_8 = (struct APat_List*)malloc(sizeof(struct APat_List));
    list_8->head = x_5;
    list_8->tail = acc_8;
    struct APat_List* call_21 = go_56(list_8, xs_9);
    match_11 = call_21;
    goto end_match_34;
next_36:;
    exit(1);
end_match_34:;
    return match_11;
}

struct AArm_List* go_55(struct AArm_List* acc_8, struct AArm_List* xs_8) {
    struct AArm_List* match_12;
    if ((!((!(xs_8))))) goto next_38;
    match_12 = acc_8;
    goto end_match_37;
next_38:;
    if ((!(xs_8))) goto next_39;
    struct AArm_ x_5 = xs_8->head;
    struct AArm_List* xs_9 = xs_8->tail;
    struct AArm_List* list_9 = (struct AArm_List*)malloc(sizeof(struct AArm_List));
    list_9->head = x_5;
    list_9->tail = acc_8;
    struct AArm_List* call_22 = go_55(list_9, xs_9);
    match_12 = call_22;
    goto end_match_37;
next_39:;
    exit(1);
end_match_37:;
    return match_12;
}

struct StringList* go_54(struct StringList* acc_8, struct StringList* xs_8) {
    struct StringList* match_13;
    if ((!((!(xs_8))))) goto next_41;
    match_13 = acc_8;
    goto end_match_40;
next_41:;
    if ((!(xs_8))) goto next_42;
    struct String x_5 = xs_8->head;
    struct StringList* xs_9 = xs_8->tail;
    struct StringList* list_10 = (struct StringList*)malloc(sizeof(struct StringList));
    list_10->head = x_5;
    list_10->tail = acc_8;
    struct StringList* call_23 = go_54(list_10, xs_9);
    match_13 = call_23;
    goto end_match_40;
next_42:;
    exit(1);
end_match_40:;
    return match_13;
}

struct AExpr_List* go_53(struct AExpr_List* acc_8, struct AExpr_List* xs_8) {
    struct AExpr_List* match_14;
    if ((!((!(xs_8))))) goto next_44;
    match_14 = acc_8;
    goto end_match_43;
next_44:;
    if ((!(xs_8))) goto next_45;
    struct AExpr_ x_5 = xs_8->head;
    struct AExpr_List* xs_9 = xs_8->tail;
    struct AExpr_List* list_11 = (struct AExpr_List*)malloc(sizeof(struct AExpr_List));
    list_11->head = x_5;
    list_11->tail = acc_8;
    struct AExpr_List* call_24 = go_53(list_11, xs_9);
    match_14 = call_24;
    goto end_match_43;
next_45:;
    exit(1);
end_match_43:;
    return match_14;
}

struct Ty_List* go_68(struct Ty_List* acc_8, struct Ty_List* xs_8) {
    struct Ty_List* match_15;
    if ((!((!(xs_8))))) goto next_47;
    match_15 = acc_8;
    goto end_match_46;
next_47:;
    if ((!(xs_8))) goto next_48;
    struct Ty_ x_5 = xs_8->head;
    struct Ty_List* xs_9 = xs_8->tail;
    struct Ty_List* list_12 = (struct Ty_List*)malloc(sizeof(struct Ty_List));
    list_12->head = x_5;
    list_12->tail = acc_8;
    struct Ty_List* call_25 = go_68(list_12, xs_9);
    match_15 = call_25;
    goto end_match_46;
next_48:;
    exit(1);
end_match_46:;
    return match_15;
}

struct HPat_HExpr_HExpr_Tuple3List* go_67(struct HPat_HExpr_HExpr_Tuple3List* acc_8, struct HPat_HExpr_HExpr_Tuple3List* xs_8) {
    struct HPat_HExpr_HExpr_Tuple3List* match_16;
    if ((!((!(xs_8))))) goto next_50;
    match_16 = acc_8;
    goto end_match_49;
next_50:;
    if ((!(xs_8))) goto next_51;
    struct HPat_HExpr_HExpr_Tuple3 x_5 = xs_8->head;
    struct HPat_HExpr_HExpr_Tuple3List* xs_9 = xs_8->tail;
    struct HPat_HExpr_HExpr_Tuple3List* list_13 = (struct HPat_HExpr_HExpr_Tuple3List*)malloc(sizeof(struct HPat_HExpr_HExpr_Tuple3List));
    list_13->head = x_5;
    list_13->tail = acc_8;
    struct HPat_HExpr_HExpr_Tuple3List* call_26 = go_67(list_13, xs_9);
    match_16 = call_26;
    goto end_match_49;
next_51:;
    exit(1);
end_match_49:;
    return match_16;
}

struct HExpr_List* go_66(struct HExpr_List* acc_8, struct HExpr_List* xs_8) {
    struct HExpr_List* match_17;
    if ((!((!(xs_8))))) goto next_53;
    match_17 = acc_8;
    goto end_match_52;
next_53:;
    if ((!(xs_8))) goto next_54;
    struct HExpr_ x_5 = xs_8->head;
    struct HExpr_List* xs_9 = xs_8->tail;
    struct HExpr_List* list_14 = (struct HExpr_List*)malloc(sizeof(struct HExpr_List));
    list_14->head = x_5;
    list_14->tail = acc_8;
    struct HExpr_List* call_27 = go_66(list_14, xs_9);
    match_17 = call_27;
    goto end_match_52;
next_54:;
    exit(1);
end_match_52:;
    return match_17;
}

struct HPat_List* go_65(struct HPat_List* acc_8, struct HPat_List* xs_8) {
    struct HPat_List* match_18;
    if ((!((!(xs_8))))) goto next_56;
    match_18 = acc_8;
    goto end_match_55;
next_56:;
    if ((!(xs_8))) goto next_57;
    struct HPat_ x_5 = xs_8->head;
    struct HPat_List* xs_9 = xs_8->tail;
    struct HPat_List* list_15 = (struct HPat_List*)malloc(sizeof(struct HPat_List));
    list_15->head = x_5;
    list_15->tail = acc_8;
    struct HPat_List* call_28 = go_65(list_15, xs_9);
    match_18 = call_28;
    goto end_match_55;
next_57:;
    exit(1);
end_match_55:;
    return match_18;
}

struct DumpTree_List* go_64(struct DumpTree_List* acc_8, struct DumpTree_List* xs_8) {
    struct DumpTree_List* match_19;
    if ((!((!(xs_8))))) goto next_59;
    match_19 = acc_8;
    goto end_match_58;
next_59:;
    if ((!(xs_8))) goto next_60;
    struct DumpTree_ x_5 = xs_8->head;
    struct DumpTree_List* xs_9 = xs_8->tail;
    struct DumpTree_List* list_16 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_16->head = x_5;
    list_16->tail = acc_8;
    struct DumpTree_List* call_29 = go_64(list_16, xs_9);
    match_19 = call_29;
    goto end_match_58;
next_60:;
    exit(1);
end_match_58:;
    return match_19;
}

struct Token_IntIntTuple2Tuple2List* listRev_7(struct Token_IntIntTuple2Tuple2List* xs_7) {
    struct Token_IntIntTuple2Tuple2List* call_30 = go_59(NULL, xs_7);
    return call_30;
}

struct ATy_List* listRev_6(struct ATy_List* xs_7) {
    struct ATy_List* call_31 = go_58(NULL, xs_7);
    return call_31;
}

struct AVariant_List* listRev_5(struct AVariant_List* xs_7) {
    struct AVariant_List* call_32 = go_57(NULL, xs_7);
    return call_32;
}

struct APat_List* listRev_4(struct APat_List* xs_7) {
    struct APat_List* call_33 = go_56(NULL, xs_7);
    return call_33;
}

struct AArm_List* listRev_3(struct AArm_List* xs_7) {
    struct AArm_List* call_34 = go_55(NULL, xs_7);
    return call_34;
}

struct StringList* listRev_2(struct StringList* xs_7) {
    struct StringList* call_35 = go_54(NULL, xs_7);
    return call_35;
}

struct AExpr_List* listRev_1(struct AExpr_List* xs_7) {
    struct AExpr_List* call_36 = go_53(NULL, xs_7);
    return call_36;
}

struct Ty_List* listRev_12(struct Ty_List* xs_7) {
    struct Ty_List* call_37 = go_68(NULL, xs_7);
    return call_37;
}

struct HPat_HExpr_HExpr_Tuple3List* listRev_11(struct HPat_HExpr_HExpr_Tuple3List* xs_7) {
    struct HPat_HExpr_HExpr_Tuple3List* call_38 = go_67(NULL, xs_7);
    return call_38;
}

struct HExpr_List* listRev_10(struct HExpr_List* xs_7) {
    struct HExpr_List* call_39 = go_66(NULL, xs_7);
    return call_39;
}

struct HPat_List* listRev_9(struct HPat_List* xs_7) {
    struct HPat_List* call_40 = go_65(NULL, xs_7);
    return call_40;
}

struct DumpTree_List* listRev_8(struct DumpTree_List* xs_7) {
    struct DumpTree_List* call_41 = go_64(NULL, xs_7);
    return call_41;
}

int go_52(int len_, struct StringList* xs_11) {
    int match_20;
    if ((!((!(xs_11))))) goto next_62;
    match_20 = len_;
    goto end_match_61;
next_62:;
    if ((!(xs_11))) goto next_63;
    struct StringList* xs_12 = xs_11->tail;
    int call_42 = go_52((len_ + 1), xs_12);
    match_20 = call_42;
    goto end_match_61;
next_63:;
    exit(1);
end_match_61:;
    return match_20;
}

int listLength_1(struct StringList* xs_10) {
    int call_43 = go_52(0, xs_10);
    return call_43;
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

int listIter_1(struct StringIntIntTuple2Tuple2UnitFun1 f_2, struct StringIntIntTuple2Tuple2List* xs_13) {
    int match_21;
    if ((!((!(xs_13))))) goto next_65;
    match_21 = 0;
    goto end_match_64;
next_65:;
    if ((!(xs_13))) goto next_66;
    struct StringIntIntTuple2Tuple2 x_6 = xs_13->head;
    struct StringIntIntTuple2Tuple2List* xs_14 = xs_13->tail;
    int app_5 = f_2.fun(f_2.env, x_6);
    int call_44 = listIter_1(f_2, xs_14);
    match_21 = 0;
    goto end_match_64;
next_66:;
    exit(1);
end_match_64:;
    return 0;
}

struct HExpr_Ty_Fun1 {
    struct Ty_(*fun)(void*, struct HExpr_);
    void* env;
};

struct Ty_List* go_51(struct HExpr_Ty_Fun1 f_3, struct Ty_List* acc_9, struct HExpr_List* xs_16) {
    struct Ty_List* match_22;
    if ((!((!(xs_16))))) goto next_68;
    struct Ty_List* call_45 = listRev_12(acc_9);
    match_22 = call_45;
    goto end_match_67;
next_68:;
    if ((!(xs_16))) goto next_69;
    struct HExpr_ x_7 = xs_16->head;
    struct HExpr_List* xs_17 = xs_16->tail;
    struct Ty_ app_6 = f_3.fun(f_3.env, x_7);
    struct Ty_List* list_17 = (struct Ty_List*)malloc(sizeof(struct Ty_List));
    list_17->head = app_6;
    list_17->tail = acc_9;
    struct Ty_List* call_46 = go_51(f_3, list_17, xs_17);
    match_22 = call_46;
    goto end_match_67;
next_69:;
    exit(1);
end_match_67:;
    return match_22;
}

struct HPat_HExpr_HExpr_Tuple3HPat_HExpr_HExpr_Tuple3Fun1 {
    struct HPat_HExpr_HExpr_Tuple3(*fun)(void*, struct HPat_HExpr_HExpr_Tuple3);
    void* env;
};

struct HPat_HExpr_HExpr_Tuple3List* go_50(struct HPat_HExpr_HExpr_Tuple3HPat_HExpr_HExpr_Tuple3Fun1 f_3, struct HPat_HExpr_HExpr_Tuple3List* acc_9, struct HPat_HExpr_HExpr_Tuple3List* xs_16) {
    struct HPat_HExpr_HExpr_Tuple3List* match_23;
    if ((!((!(xs_16))))) goto next_71;
    struct HPat_HExpr_HExpr_Tuple3List* call_47 = listRev_11(acc_9);
    match_23 = call_47;
    goto end_match_70;
next_71:;
    if ((!(xs_16))) goto next_72;
    struct HPat_HExpr_HExpr_Tuple3 x_7 = xs_16->head;
    struct HPat_HExpr_HExpr_Tuple3List* xs_17 = xs_16->tail;
    struct HPat_HExpr_HExpr_Tuple3 app_7 = f_3.fun(f_3.env, x_7);
    struct HPat_HExpr_HExpr_Tuple3List* list_18 = (struct HPat_HExpr_HExpr_Tuple3List*)malloc(sizeof(struct HPat_HExpr_HExpr_Tuple3List));
    list_18->head = app_7;
    list_18->tail = acc_9;
    struct HPat_HExpr_HExpr_Tuple3List* call_48 = go_50(f_3, list_18, xs_17);
    match_23 = call_48;
    goto end_match_70;
next_72:;
    exit(1);
end_match_70:;
    return match_23;
}

struct HExpr_HExpr_Fun1 {
    struct HExpr_(*fun)(void*, struct HExpr_);
    void* env;
};

struct HExpr_List* go_49(struct HExpr_HExpr_Fun1 f_3, struct HExpr_List* acc_9, struct HExpr_List* xs_16) {
    struct HExpr_List* match_24;
    if ((!((!(xs_16))))) goto next_74;
    struct HExpr_List* call_49 = listRev_10(acc_9);
    match_24 = call_49;
    goto end_match_73;
next_74:;
    if ((!(xs_16))) goto next_75;
    struct HExpr_ x_7 = xs_16->head;
    struct HExpr_List* xs_17 = xs_16->tail;
    struct HExpr_ app_8 = f_3.fun(f_3.env, x_7);
    struct HExpr_List* list_19 = (struct HExpr_List*)malloc(sizeof(struct HExpr_List));
    list_19->head = app_8;
    list_19->tail = acc_9;
    struct HExpr_List* call_50 = go_49(f_3, list_19, xs_17);
    match_24 = call_50;
    goto end_match_73;
next_75:;
    exit(1);
end_match_73:;
    return match_24;
}

struct HPat_HPat_Fun1 {
    struct HPat_(*fun)(void*, struct HPat_);
    void* env;
};

struct HPat_List* go_48(struct HPat_HPat_Fun1 f_3, struct HPat_List* acc_9, struct HPat_List* xs_16) {
    struct HPat_List* match_25;
    if ((!((!(xs_16))))) goto next_77;
    struct HPat_List* call_51 = listRev_9(acc_9);
    match_25 = call_51;
    goto end_match_76;
next_77:;
    if ((!(xs_16))) goto next_78;
    struct HPat_ x_7 = xs_16->head;
    struct HPat_List* xs_17 = xs_16->tail;
    struct HPat_ app_9 = f_3.fun(f_3.env, x_7);
    struct HPat_List* list_20 = (struct HPat_List*)malloc(sizeof(struct HPat_List));
    list_20->head = app_9;
    list_20->tail = acc_9;
    struct HPat_List* call_52 = go_48(f_3, list_20, xs_17);
    match_25 = call_52;
    goto end_match_76;
next_78:;
    exit(1);
end_match_76:;
    return match_25;
}

struct ATy_DumpTree_Fun1 {
    struct DumpTree_(*fun)(void*, struct ATy_);
    void* env;
};

struct DumpTree_List* go_47(struct ATy_DumpTree_Fun1 f_3, struct DumpTree_List* acc_9, struct ATy_List* xs_16) {
    struct DumpTree_List* match_26;
    if ((!((!(xs_16))))) goto next_80;
    struct DumpTree_List* call_53 = listRev_8(acc_9);
    match_26 = call_53;
    goto end_match_79;
next_80:;
    if ((!(xs_16))) goto next_81;
    struct ATy_ x_7 = xs_16->head;
    struct ATy_List* xs_17 = xs_16->tail;
    struct DumpTree_ app_10 = f_3.fun(f_3.env, x_7);
    struct DumpTree_List* list_21 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_21->head = app_10;
    list_21->tail = acc_9;
    struct DumpTree_List* call_54 = go_47(f_3, list_21, xs_17);
    match_26 = call_54;
    goto end_match_79;
next_81:;
    exit(1);
end_match_79:;
    return match_26;
}

struct AArm_DumpTree_Fun1 {
    struct DumpTree_(*fun)(void*, struct AArm_);
    void* env;
};

struct DumpTree_List* go_46(struct AArm_DumpTree_Fun1 f_3, struct DumpTree_List* acc_9, struct AArm_List* xs_16) {
    struct DumpTree_List* match_27;
    if ((!((!(xs_16))))) goto next_83;
    struct DumpTree_List* call_55 = listRev_8(acc_9);
    match_27 = call_55;
    goto end_match_82;
next_83:;
    if ((!(xs_16))) goto next_84;
    struct AArm_ x_7 = xs_16->head;
    struct AArm_List* xs_17 = xs_16->tail;
    struct DumpTree_ app_11 = f_3.fun(f_3.env, x_7);
    struct DumpTree_List* list_22 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_22->head = app_11;
    list_22->tail = acc_9;
    struct DumpTree_List* call_56 = go_46(f_3, list_22, xs_17);
    match_27 = call_56;
    goto end_match_82;
next_84:;
    exit(1);
end_match_82:;
    return match_27;
}

struct APat_DumpTree_Fun1 {
    struct DumpTree_(*fun)(void*, struct APat_);
    void* env;
};

struct DumpTree_List* go_45(struct APat_DumpTree_Fun1 f_3, struct DumpTree_List* acc_9, struct APat_List* xs_16) {
    struct DumpTree_List* match_28;
    if ((!((!(xs_16))))) goto next_86;
    struct DumpTree_List* call_57 = listRev_8(acc_9);
    match_28 = call_57;
    goto end_match_85;
next_86:;
    if ((!(xs_16))) goto next_87;
    struct APat_ x_7 = xs_16->head;
    struct APat_List* xs_17 = xs_16->tail;
    struct DumpTree_ app_12 = f_3.fun(f_3.env, x_7);
    struct DumpTree_List* list_23 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_23->head = app_12;
    list_23->tail = acc_9;
    struct DumpTree_List* call_58 = go_45(f_3, list_23, xs_17);
    match_28 = call_58;
    goto end_match_85;
next_87:;
    exit(1);
end_match_85:;
    return match_28;
}

struct AExpr_DumpTree_Fun1 {
    struct DumpTree_(*fun)(void*, struct AExpr_);
    void* env;
};

struct DumpTree_List* go_44(struct AExpr_DumpTree_Fun1 f_3, struct DumpTree_List* acc_9, struct AExpr_List* xs_16) {
    struct DumpTree_List* match_29;
    if ((!((!(xs_16))))) goto next_89;
    struct DumpTree_List* call_59 = listRev_8(acc_9);
    match_29 = call_59;
    goto end_match_88;
next_89:;
    if ((!(xs_16))) goto next_90;
    struct AExpr_ x_7 = xs_16->head;
    struct AExpr_List* xs_17 = xs_16->tail;
    struct DumpTree_ app_13 = f_3.fun(f_3.env, x_7);
    struct DumpTree_List* list_24 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_24->head = app_13;
    list_24->tail = acc_9;
    struct DumpTree_List* call_60 = go_44(f_3, list_24, xs_17);
    match_29 = call_60;
    goto end_match_88;
next_90:;
    exit(1);
end_match_88:;
    return match_29;
}

struct AVariant_DumpTree_Fun1 {
    struct DumpTree_(*fun)(void*, struct AVariant_);
    void* env;
};

struct DumpTree_List* go_43(struct AVariant_DumpTree_Fun1 f_3, struct DumpTree_List* acc_9, struct AVariant_List* xs_16) {
    struct DumpTree_List* match_30;
    if ((!((!(xs_16))))) goto next_92;
    struct DumpTree_List* call_61 = listRev_8(acc_9);
    match_30 = call_61;
    goto end_match_91;
next_92:;
    if ((!(xs_16))) goto next_93;
    struct AVariant_ x_7 = xs_16->head;
    struct AVariant_List* xs_17 = xs_16->tail;
    struct DumpTree_ app_14 = f_3.fun(f_3.env, x_7);
    struct DumpTree_List* list_25 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_25->head = app_14;
    list_25->tail = acc_9;
    struct DumpTree_List* call_62 = go_43(f_3, list_25, xs_17);
    match_30 = call_62;
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

struct DumpTree_List* go_42(struct StringDumpTree_Fun1 f_3, struct DumpTree_List* acc_9, struct StringList* xs_16) {
    struct DumpTree_List* match_31;
    if ((!((!(xs_16))))) goto next_95;
    struct DumpTree_List* call_63 = listRev_8(acc_9);
    match_31 = call_63;
    goto end_match_94;
next_95:;
    if ((!(xs_16))) goto next_96;
    struct String x_7 = xs_16->head;
    struct StringList* xs_17 = xs_16->tail;
    struct DumpTree_ app_15 = f_3.fun(f_3.env, x_7);
    struct DumpTree_List* list_26 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_26->head = app_15;
    list_26->tail = acc_9;
    struct DumpTree_List* call_64 = go_42(f_3, list_26, xs_17);
    match_31 = call_64;
    goto end_match_94;
next_96:;
    exit(1);
end_match_94:;
    return match_31;
}

struct Ty_List* listMap_10(struct HExpr_Ty_Fun1 f_3, struct HExpr_List* xs_15) {
    struct Ty_List* call_65 = go_51(f_3, NULL, xs_15);
    return call_65;
}

struct HPat_HExpr_HExpr_Tuple3List* listMap_9(struct HPat_HExpr_HExpr_Tuple3HPat_HExpr_HExpr_Tuple3Fun1 f_3, struct HPat_HExpr_HExpr_Tuple3List* xs_15) {
    struct HPat_HExpr_HExpr_Tuple3List* call_66 = go_50(f_3, NULL, xs_15);
    return call_66;
}

struct HExpr_List* listMap_8(struct HExpr_HExpr_Fun1 f_3, struct HExpr_List* xs_15) {
    struct HExpr_List* call_67 = go_49(f_3, NULL, xs_15);
    return call_67;
}

struct HPat_List* listMap_7(struct HPat_HPat_Fun1 f_3, struct HPat_List* xs_15) {
    struct HPat_List* call_68 = go_48(f_3, NULL, xs_15);
    return call_68;
}

struct DumpTree_List* listMap_6(struct ATy_DumpTree_Fun1 f_3, struct ATy_List* xs_15) {
    struct DumpTree_List* call_69 = go_47(f_3, NULL, xs_15);
    return call_69;
}

struct DumpTree_List* listMap_5(struct AArm_DumpTree_Fun1 f_3, struct AArm_List* xs_15) {
    struct DumpTree_List* call_70 = go_46(f_3, NULL, xs_15);
    return call_70;
}

struct DumpTree_List* listMap_4(struct APat_DumpTree_Fun1 f_3, struct APat_List* xs_15) {
    struct DumpTree_List* call_71 = go_45(f_3, NULL, xs_15);
    return call_71;
}

struct DumpTree_List* listMap_3(struct AExpr_DumpTree_Fun1 f_3, struct AExpr_List* xs_15) {
    struct DumpTree_List* call_72 = go_44(f_3, NULL, xs_15);
    return call_72;
}

struct DumpTree_List* listMap_2(struct AVariant_DumpTree_Fun1 f_3, struct AVariant_List* xs_15) {
    struct DumpTree_List* call_73 = go_43(f_3, NULL, xs_15);
    return call_73;
}

struct DumpTree_List* listMap_1(struct StringDumpTree_Fun1 f_3, struct StringList* xs_15) {
    struct DumpTree_List* call_74 = go_42(f_3, NULL, xs_15);
    return call_74;
}

int intMin_(int x_9, int y_3) {
    int match_32;
    if ((y_3 >= x_9)) goto next_98;
    match_32 = y_3;
    goto end_match_97;
next_98:;
    if ((y_3 < x_9)) goto next_99;
    match_32 = x_9;
    goto end_match_97;
next_99:;
    exit(1);
end_match_97:;
    return match_32;
}

int intMax_(int x_10, int y_4) {
    int match_33;
    if ((x_10 >= y_4)) goto next_101;
    match_33 = y_4;
    goto end_match_100;
next_101:;
    if ((x_10 < y_4)) goto next_102;
    match_33 = x_10;
    goto end_match_100;
next_102:;
    exit(1);
end_match_100:;
    return match_33;
}

int intEq_(int x_11, int y_5) {
    return (x_11 == y_5);
}

struct String strSlice_(int start_, int endIndex_1, struct String s_3) {
    int match_34;
    if ((endIndex_1 < start_)) goto next_104;
    match_34 = (s_3.len >= endIndex_1);
    goto end_match_103;
next_104:;
    if ((endIndex_1 >= start_)) goto next_105;
    match_34 = 0;
    goto end_match_103;
next_105:;
    exit(1);
end_match_103:;
    milone_assert(match_34, 114, 2);
    int call_75 = 0;
    struct String match_35;
    if ((start_ < endIndex_1)) goto next_107;
    match_35 = (struct String){.str = "", .len = 0};
    goto end_match_106;
next_107:;
    if ((start_ >= endIndex_1)) goto next_108;
    struct String call_76 = str_get_slice(start_, (endIndex_1 - 1), s_3);
    match_35 = call_76;
    goto end_match_106;
next_108:;
    exit(1);
end_match_106:;
    return match_35;
}

struct StringStringListTuple2 {
    struct String t0;
    struct StringList* t1;
};

struct StringStringListTuple2 go_18(struct StringList* xs_22, int xn_) {
    struct StringStringListTuple2 match_36;
    if ((!((!(xs_22))))) goto next_110;
    milone_assert((xn_ == 0), 128, 6);
    int call_77 = 0;
    struct StringStringListTuple2 tuple_16;
    tuple_16.t0 = (struct String){.str = "", .len = 0};
    tuple_16.t1 = NULL;
    match_36 = tuple_16;
    goto end_match_109;
next_110:;
    if ((!(xs_22))) goto next_111;
    struct String x_12 = xs_22->head;
    struct StringList* xs_23 = xs_22->tail;
    if ((xn_ != 1)) goto next_111;
    struct StringStringListTuple2 tuple_17;
    tuple_17.t0 = x_12;
    tuple_17.t1 = xs_23;
    match_36 = tuple_17;
    goto end_match_109;
next_111:;
    if ((!(xs_22))) goto next_112;
    struct String x_13 = xs_22->head;
    if ((!(xs_22->tail))) goto next_112;
    struct String y_6 = xs_22->tail->head;
    struct StringList* xs_24 = xs_22->tail->tail;
    if ((xn_ != 2)) goto next_112;
    struct StringStringListTuple2 tuple_18;
    tuple_18.t0 = str_add(x_13, y_6);
    tuple_18.t1 = xs_24;
    match_36 = tuple_18;
    goto end_match_109;
next_112:;
    struct StringList* xs_25 = xs_22;
    int m_ = (xn_ / 2);
    struct StringStringListTuple2 call_78 = go_18(xs_25, m_);
    struct String l_8 = call_78.t0;
    struct StringList* xs_26 = call_78.t1;
    struct StringStringListTuple2 call_79 = go_18(xs_26, (xn_ - m_));
    struct String r_20 = call_79.t0;
    struct StringList* xs_27 = call_79.t1;
    struct StringStringListTuple2 tuple_19;
    tuple_19.t0 = str_add(l_8, r_20);
    tuple_19.t1 = xs_27;
    match_36 = tuple_19;
    goto end_match_109;
next_113:;
end_match_109:;
    return match_36;
}

struct String strConcat_(struct StringList* xs_21) {
    int call_80 = listLength_1(xs_21);
    int n_ = call_80;
    struct StringStringListTuple2 call_81 = go_18(xs_21, n_);
    struct String s_4 = call_81.t0;
    struct StringList* xs_28 = call_81.t1;
    int call_82 = listIsEmpty_4(xs_28);
    milone_assert(call_82, 141, 2);
    int call_83 = 0;
    return s_4;
}

int locX_(struct IntIntTuple2 arg_85) {
    int x_14 = arg_85.t1;
    return x_14;
}

int locY_(struct IntIntTuple2 arg_86) {
    int y_7 = arg_86.t0;
    return y_7;
}

int locIsSameRow_(struct IntIntTuple2 first_, struct IntIntTuple2 second_) {
    int call_84 = locY_(first_);
    int call_85 = locY_(second_);
    return (call_84 == call_85);
}

int locIsSameColumn_(struct IntIntTuple2 first_1, struct IntIntTuple2 second_1) {
    int call_86 = locX_(first_1);
    int call_87 = locX_(second_1);
    return (call_86 == call_87);
}

int locInside_(struct IntIntTuple2 firstLoc_, struct IntIntTuple2 secondLoc_) {
    int call_88 = locX_(secondLoc_);
    int call_89 = locX_(firstLoc_);
    return (call_88 >= call_89);
}

struct IntIntTuple2 locAddX_(int dx_, struct IntIntTuple2 arg_87) {
    int y_8 = arg_87.t0;
    int x_15 = arg_87.t1;
    struct IntIntTuple2 tuple_20;
    tuple_20.t0 = y_8;
    tuple_20.t1 = (x_15 + dx_);
    return tuple_20;
}

struct IntIntTuple2 locMax_(struct IntIntTuple2 arg_88, struct IntIntTuple2 arg_89) {
    int firstY_ = arg_88.t0;
    int firstX_ = arg_88.t1;
    int secondY_ = arg_89.t0;
    int secondX_ = arg_89.t1;
    int call_90 = intMax_(firstY_, secondY_);
    int call_91 = intMax_(firstX_, secondX_);
    struct IntIntTuple2 tuple_21;
    tuple_21.t0 = call_90;
    tuple_21.t1 = call_91;
    return tuple_21;
}

int tokenIsExprOrPatFirst_(struct Token_ token_7) {
    int match_37;
    if ((token_7.tag != Bool_1)) goto next_116;
    goto match_body_115;
next_116:;
    if ((token_7.tag != Int_1)) goto next_117;
    goto match_body_115;
next_117:;
    if ((token_7.tag != Char_1)) goto next_118;
    goto match_body_115;
next_118:;
    if ((token_7.tag != Str_1)) goto next_119;
    goto match_body_115;
next_119:;
    if ((token_7.tag != Ident_)) goto next_120;
    goto match_body_115;
next_120:;
    if ((token_7.tag != ParenL_)) goto next_121;
    goto match_body_115;
next_121:;
    if ((token_7.tag != BracketL_)) goto next_122;
    goto match_body_115;
match_body_115:;
    match_37 = 1;
    goto end_match_114;
next_122:;
    match_37 = 0;
    goto end_match_114;
next_123:;
end_match_114:;
    return match_37;
}

int tokenIsExprFirst_(struct Token_ token_8) {
    int match_38;
    int call_92 = tokenIsExprOrPatFirst_(token_8);
    if ((!(call_92))) goto next_126;
    match_38 = 1;
    goto end_match_124;
next_126:;
    if ((token_8.tag != Minus_)) goto next_127;
    goto match_body_125;
next_127:;
    if ((token_8.tag != If_)) goto next_128;
    goto match_body_125;
next_128:;
    if ((token_8.tag != Match_)) goto next_129;
    goto match_body_125;
next_129:;
    if ((token_8.tag != Fun_)) goto next_130;
    goto match_body_125;
next_130:;
    if ((token_8.tag != Do_)) goto next_131;
    goto match_body_125;
next_131:;
    if ((token_8.tag != Let_)) goto next_132;
    goto match_body_125;
next_132:;
    if ((token_8.tag != Type_)) goto next_133;
    goto match_body_125;
next_133:;
    if ((token_8.tag != Open_)) goto next_134;
    goto match_body_125;
match_body_125:;
    match_38 = 1;
    goto end_match_124;
next_134:;
    match_38 = 0;
    goto end_match_124;
next_135:;
end_match_124:;
    return match_38;
}

int tokenIsArgFirst_(struct Token_ token_9) {
    int match_39;
    if ((token_9.tag != Minus_)) goto next_137;
    match_39 = 0;
    goto end_match_136;
next_137:;
    int call_93 = tokenIsExprFirst_(token_9);
    match_39 = call_93;
    goto end_match_136;
next_138:;
end_match_136:;
    return match_39;
}

int tokenIsPatFirst_(struct Token_ token_10) {
    int call_94 = tokenIsExprOrPatFirst_(token_10);
    return call_94;
}

int tokenIsAccessModifier_(struct Token_ token_11) {
    int match_40;
    if ((token_11.tag != Private_)) goto next_141;
    goto match_body_140;
next_141:;
    if ((token_11.tag != Internal_)) goto next_142;
    goto match_body_140;
next_142:;
    if ((token_11.tag != Public_)) goto next_143;
    goto match_body_140;
match_body_140:;
    match_40 = 1;
    goto end_match_139;
next_143:;
    match_40 = 0;
    goto end_match_139;
next_144:;
end_match_139:;
    return match_40;
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
    struct OpLevel_ match_41;
    if ((level_.tag != Or_)) goto next_146;
    match_41 = (struct OpLevel_){.tag = And_};
    goto end_match_145;
next_146:;
    if ((level_.tag != And_)) goto next_147;
    match_41 = (struct OpLevel_){.tag = Cmp_};
    goto end_match_145;
next_147:;
    if ((level_.tag != Cmp_)) goto next_148;
    match_41 = (struct OpLevel_){.tag = Pipe_1};
    goto end_match_145;
next_148:;
    if ((level_.tag != Pipe_1)) goto next_149;
    match_41 = (struct OpLevel_){.tag = Cons_};
    goto end_match_145;
next_149:;
    if ((level_.tag != Cons_)) goto next_150;
    match_41 = (struct OpLevel_){.tag = Add_};
    goto end_match_145;
next_150:;
    if ((level_.tag != Add_)) goto next_152;
    match_41 = (struct OpLevel_){.tag = Mul_};
    goto end_match_145;
next_152:;
    if ((level_.tag != Mul_)) goto next_153;
    goto match_body_151;
next_153:;
    if ((level_.tag != Prefix_)) goto next_154;
    goto match_body_151;
match_body_151:;
    match_41 = (struct OpLevel_){.tag = Prefix_};
    goto end_match_145;
next_154:;
end_match_145:;
    return match_41;
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
    struct Lit_IntIntTuple2Tuple2 tuple_22;
    tuple_22.t0 = litFalse_;
    tuple_22.t1 = loc_2;
    struct Lit_IntIntTuple2Tuple2* payload_ = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_))) = tuple_22;
    struct APat_ variant_ = (struct APat_){.tag = Lit_, .Lit_ = payload_};
    return variant_;
}

struct APat_ apTrue_(struct Lit_ litTrue_, struct IntIntTuple2 loc_3) {
    struct Lit_IntIntTuple2Tuple2 tuple_23;
    tuple_23.t0 = litTrue_;
    tuple_23.t1 = loc_3;
    struct Lit_IntIntTuple2Tuple2* payload_1 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_1))) = tuple_23;
    struct APat_ variant_1 = (struct APat_){.tag = Lit_, .Lit_ = payload_1};
    return variant_1;
}

struct AExpr_ListIntIntTuple2Tuple2 {
    struct AExpr_List* t0;
    struct IntIntTuple2 t1;
};

struct AExpr_ axUnit_(struct IntIntTuple2 loc_4) {
    struct AExpr_ListIntIntTuple2Tuple2 tuple_24;
    tuple_24.t0 = NULL;
    tuple_24.t1 = loc_4;
    struct AExpr_ListIntIntTuple2Tuple2* payload_2 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_2))) = tuple_24;
    struct AExpr_ variant_2 = (struct AExpr_){.tag = TupleLit_1, .TupleLit_1 = payload_2};
    return variant_2;
}

struct AExpr_ axFalse_(struct Lit_ litFalse_, struct IntIntTuple2 loc_5) {
    struct Lit_IntIntTuple2Tuple2 tuple_25;
    tuple_25.t0 = litFalse_;
    tuple_25.t1 = loc_5;
    struct Lit_IntIntTuple2Tuple2* payload_3 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_3))) = tuple_25;
    struct AExpr_ variant_3 = (struct AExpr_){.tag = Lit_1, .Lit_1 = payload_3};
    return variant_3;
}

struct AExpr_ axTrue_(struct Lit_ litTrue_, struct IntIntTuple2 loc_6) {
    struct Lit_IntIntTuple2Tuple2 tuple_26;
    tuple_26.t0 = litTrue_;
    tuple_26.t1 = loc_6;
    struct Lit_IntIntTuple2Tuple2* payload_4 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_4))) = tuple_26;
    struct AExpr_ variant_4 = (struct AExpr_){.tag = Lit_1, .Lit_1 = payload_4};
    return variant_4;
}

struct AExpr_ axNil_(struct IntIntTuple2 loc_7) {
    struct AExpr_ListIntIntTuple2Tuple2 tuple_27;
    tuple_27.t0 = NULL;
    tuple_27.t1 = loc_7;
    struct AExpr_ListIntIntTuple2Tuple2* payload_5 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_5))) = tuple_27;
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

struct AExpr_ app_(struct IntIntTuple2 loc_8, struct AExpr_ x_16, struct AExpr_ f_5) {
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_28;
    tuple_28.t0 = (struct Op_){.tag = App_};
    tuple_28.t1 = f_5;
    tuple_28.t2 = x_16;
    tuple_28.t3 = loc_8;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_6 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_6))) = tuple_28;
    struct AExpr_ variant_6 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_6};
    return variant_6;
}

struct AExpr_ axApp3_(struct AExpr_ f_4, struct AExpr_ x1_, struct AExpr_ x2_, struct AExpr_ x3_, struct IntIntTuple2 loc_8) {
    struct AExpr_ call_95 = app_(loc_8, x1_, f_4);
    struct AExpr_ call_96 = app_(loc_8, x2_, call_95);
    struct AExpr_ call_97 = app_(loc_8, x3_, call_96);
    return call_97;
}

struct AExpr_ axNot_(struct Lit_ litFalse_, struct AExpr_ arg_, struct IntIntTuple2 loc_9) {
    struct AExpr_ call_98 = axFalse_(litFalse_, loc_9);
    struct AExpr_ falseExpr_ = call_98;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_29;
    tuple_29.t0 = (struct Op_){.tag = Eq_1};
    tuple_29.t1 = arg_;
    tuple_29.t2 = falseExpr_;
    tuple_29.t3 = loc_9;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_7 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_7))) = tuple_29;
    struct AExpr_ variant_7 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_7};
    return variant_7;
}

struct String go_19(struct String acc_10, int len_2, int n_1) {
    struct String match_42;
    int match_43;
    if ((n_1 != 0)) goto next_157;
    match_43 = (0 >= len_2);
    goto end_match_156;
next_157:;
    if ((n_1 == 0)) goto next_158;
    match_43 = 0;
    goto end_match_156;
next_158:;
    exit(1);
end_match_156:;
    if ((!(match_43))) goto next_159;
    match_42 = acc_10;
    goto end_match_155;
next_159:;
    if (match_43) goto next_160;
    int d_ = (n_1 % 16);
    struct String call_99 = strSlice_(d_, (d_ + 1), (struct String){.str = "0123456789abcdef", .len = 16});
    struct String s_5 = call_99;
    struct String call_100 = go_19(str_add(s_5, acc_10), (len_2 - 1), (n_1 / 16));
    match_42 = call_100;
    goto end_match_155;
next_160:;
    exit(1);
end_match_155:;
    return match_42;
}

struct String intToHexWithPadding_(int len_1, int value_3) {
    struct String match_44;
    if ((value_3 >= 0)) goto next_162;
    struct String call_101 = failwith_3((struct String){.str = "intToHexWithPadding: unimplemented negative", .len = 43});
    match_44 = call_101;
    goto end_match_161;
next_162:;
    if ((value_3 < 0)) goto next_163;
    milone_assert((len_1 >= 0), 312, 2);
    int call_102 = 0;
    struct String match_45;
    int match_46;
    if ((value_3 != 0)) goto next_166;
    match_46 = (len_1 == 0);
    goto end_match_165;
next_166:;
    if ((value_3 == 0)) goto next_167;
    match_46 = 0;
    goto end_match_165;
next_167:;
    exit(1);
end_match_165:;
    if ((!(match_46))) goto next_168;
    match_45 = (struct String){.str = "0", .len = 1};
    goto end_match_164;
next_168:;
    if (match_46) goto next_169;
    struct String call_103 = go_19((struct String){.str = "", .len = 0}, len_1, value_3);
    match_45 = call_103;
    goto end_match_164;
next_169:;
    exit(1);
end_match_164:;
    match_44 = match_45;
    goto end_match_161;
next_163:;
    exit(1);
end_match_161:;
    return match_44;
}

struct StringDumpTree_ListDumpTree_ListTuple3 {
    struct String t0;
    struct DumpTree_List* t1;
    struct DumpTree_List* t2;
};

struct DumpTree_ dumpTreeNew_(struct String text_43, struct DumpTree_List* children_) {
    struct StringDumpTree_ListDumpTree_ListTuple3 tuple_30;
    tuple_30.t0 = text_43;
    tuple_30.t1 = children_;
    tuple_30.t2 = NULL;
    struct StringDumpTree_ListDumpTree_ListTuple3* payload_8 = (struct StringDumpTree_ListDumpTree_ListTuple3*)malloc(sizeof(struct StringDumpTree_ListDumpTree_ListTuple3));
    (*(((struct StringDumpTree_ListDumpTree_ListTuple3*)payload_8))) = tuple_30;
    struct DumpTree_ variant_8 = (struct DumpTree_){.tag = DumpTree_, .DumpTree_ = payload_8};
    return variant_8;
}

struct DumpTree_ dumpTreeNewLeaf_(struct String text_44) {
    struct StringDumpTree_ListDumpTree_ListTuple3 tuple_31;
    tuple_31.t0 = text_44;
    tuple_31.t1 = NULL;
    tuple_31.t2 = NULL;
    struct StringDumpTree_ListDumpTree_ListTuple3* payload_9 = (struct StringDumpTree_ListDumpTree_ListTuple3*)malloc(sizeof(struct StringDumpTree_ListDumpTree_ListTuple3));
    (*(((struct StringDumpTree_ListDumpTree_ListTuple3*)payload_9))) = tuple_31;
    struct DumpTree_ variant_9 = (struct DumpTree_){.tag = DumpTree_, .DumpTree_ = payload_9};
    return variant_9;
}

struct DumpTree_ dumpTreeAttachNext_(struct DumpTree_ next_1, struct DumpTree_ tree_) {
    struct DumpTree_ match_47;
    struct String text_45 = (*(tree_.DumpTree_)).t0;
    struct DumpTree_List* children_1 = (*(tree_.DumpTree_)).t1;
    struct DumpTree_List* oldNext_ = (*(tree_.DumpTree_)).t2;
    int call_104 = listIsEmpty_3(children_1);
    milone_assert((!(call_104)), 336, 4);
    int call_105 = 0;
    int call_106 = listIsEmpty_3(oldNext_);
    milone_assert(call_106, 337, 4);
    int call_107 = 0;
    struct DumpTree_List* list_27 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_27->head = next_1;
    list_27->tail = NULL;
    struct StringDumpTree_ListDumpTree_ListTuple3 tuple_32;
    tuple_32.t0 = text_45;
    tuple_32.t1 = children_1;
    tuple_32.t2 = list_27;
    struct StringDumpTree_ListDumpTree_ListTuple3* payload_10 = (struct StringDumpTree_ListDumpTree_ListTuple3*)malloc(sizeof(struct StringDumpTree_ListDumpTree_ListTuple3));
    (*(((struct StringDumpTree_ListDumpTree_ListTuple3*)payload_10))) = tuple_32;
    struct DumpTree_ variant_10 = (struct DumpTree_){.tag = DumpTree_, .DumpTree_ = payload_10};
    match_47 = variant_10;
    goto end_match_170;
next_171:;
    exit(1);
end_match_170:;
    return match_47;
}

struct DumpTree_ dumpTreeFromError_(struct String msg_, struct IntIntTuple2 arg_90) {
    int y_9 = arg_90.t0;
    int x_17 = arg_90.t1;
    struct String call_108 = str_of_int((y_9 + 1));
    struct String y_10 = call_108;
    struct String call_109 = str_of_int((x_17 + 1));
    struct String x_18 = call_109;
    struct DumpTree_ call_110 = dumpTreeNewLeaf_(msg_);
    struct DumpTree_ call_111 = dumpTreeNewLeaf_(str_add(str_add(str_add(str_add((struct String){.str = "(", .len = 1}, y_10), (struct String){.str = ":", .len = 1}), x_18), (struct String){.str = ")", .len = 1}));
    struct DumpTree_List* list_29 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_29->head = call_111;
    list_29->tail = NULL;
    struct DumpTree_List* list_28 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_28->head = call_110;
    list_28->tail = list_29;
    struct DumpTree_ call_112 = dumpTreeNew_((struct String){.str = "ERROR", .len = 5}, list_28);
    return call_112;
}

int charIsControl_(char c_8) {
    int call_113 = ((int)c_8);
    int n_2 = call_113;
    int match_48;
    int match_49;
    if ((n_2 < 0)) goto next_174;
    match_49 = (n_2 < 32);
    goto end_match_173;
next_174:;
    if ((n_2 >= 0)) goto next_175;
    match_49 = 0;
    goto end_match_173;
next_175:;
    exit(1);
end_match_173:;
    if ((!(match_49))) goto next_176;
    match_48 = 1;
    goto end_match_172;
next_176:;
    if (match_49) goto next_177;
    match_48 = (n_2 == 127);
    goto end_match_172;
next_177:;
    exit(1);
end_match_172:;
    return match_48;
}

int charNeedsEscaping_(char c_9) {
    int match_50;
    int match_51;
    int match_52;
    int call_114 = charIsControl_(c_9);
    if ((!(call_114))) goto next_181;
    match_52 = 1;
    goto end_match_180;
next_181:;
    if (call_114) goto next_182;
    match_52 = (c_9 == '\\');
    goto end_match_180;
next_182:;
    exit(1);
end_match_180:;
    if ((!(match_52))) goto next_183;
    match_51 = 1;
    goto end_match_179;
next_183:;
    if (match_52) goto next_184;
    match_51 = (c_9 == '"');
    goto end_match_179;
next_184:;
    exit(1);
end_match_179:;
    if ((!(match_51))) goto next_185;
    match_50 = 1;
    goto end_match_178;
next_185:;
    if (match_51) goto next_186;
    match_50 = (c_9 == '\'');
    goto end_match_178;
next_186:;
    exit(1);
end_match_178:;
    return match_50;
}

int go_20(struct String str_2, int i_50) {
    int match_53;
    if ((i_50 >= str_2.len)) goto next_188;
    int match_54;
    int call_115 = charNeedsEscaping_(str_2.str[i_50]);
    if ((!(call_115))) goto next_191;
    match_54 = 1;
    goto end_match_190;
next_191:;
    if (call_115) goto next_192;
    int call_116 = go_20(str_2, (i_50 + 1));
    match_54 = call_116;
    goto end_match_190;
next_192:;
    exit(1);
end_match_190:;
    match_53 = match_54;
    goto end_match_187;
next_188:;
    if ((i_50 < str_2.len)) goto next_189;
    match_53 = 0;
    goto end_match_187;
next_189:;
    exit(1);
end_match_187:;
    return match_53;
}

int strNeedsEscaping_(struct String str_2) {
    int call_117 = go_20(str_2, 0);
    return call_117;
}

struct IntStringTuple2 {
    int t0;
    struct String t1;
};

struct IntStringTuple2 strEscapeCore_(int i_51, struct String str_3) {
    int call_118 = charNeedsEscaping_(str_3.str[i_51]);
    milone_assert(call_118, 361, 4);
    int call_119 = 0;
    struct IntStringTuple2 match_55;
    if ((str_3.str[i_51] != '\0')) goto next_194;
    struct IntStringTuple2 tuple_33;
    tuple_33.t0 = (i_51 + 1);
    tuple_33.t1 = (struct String){.str = "\\0", .len = 2};
    match_55 = tuple_33;
    goto end_match_193;
next_194:;
    if ((str_3.str[i_51] != '\t')) goto next_195;
    struct IntStringTuple2 tuple_34;
    tuple_34.t0 = (i_51 + 1);
    tuple_34.t1 = (struct String){.str = "\\t", .len = 2};
    match_55 = tuple_34;
    goto end_match_193;
next_195:;
    if ((str_3.str[i_51] != '\n')) goto next_196;
    struct IntStringTuple2 tuple_35;
    tuple_35.t0 = (i_51 + 1);
    tuple_35.t1 = (struct String){.str = "\\n", .len = 2};
    match_55 = tuple_35;
    goto end_match_193;
next_196:;
    if ((str_3.str[i_51] != '\r')) goto next_197;
    struct IntStringTuple2 tuple_36;
    tuple_36.t0 = (i_51 + 1);
    tuple_36.t1 = (struct String){.str = "\\r", .len = 2};
    match_55 = tuple_36;
    goto end_match_193;
next_197:;
    if ((str_3.str[i_51] != '\'')) goto next_198;
    struct IntStringTuple2 tuple_37;
    tuple_37.t0 = (i_51 + 1);
    tuple_37.t1 = (struct String){.str = "\\'", .len = 2};
    match_55 = tuple_37;
    goto end_match_193;
next_198:;
    if ((str_3.str[i_51] != '"')) goto next_199;
    struct IntStringTuple2 tuple_38;
    tuple_38.t0 = (i_51 + 1);
    tuple_38.t1 = (struct String){.str = "\\\"", .len = 2};
    match_55 = tuple_38;
    goto end_match_193;
next_199:;
    if ((str_3.str[i_51] != '\\')) goto next_200;
    struct IntStringTuple2 tuple_39;
    tuple_39.t0 = (i_51 + 1);
    tuple_39.t1 = (struct String){.str = "\\\\", .len = 2};
    match_55 = tuple_39;
    goto end_match_193;
next_200:;
    char c_10 = str_3.str[i_51];
    int call_120 = ((int)c_10);
    struct String call_121 = intToHexWithPadding_(2, call_120);
    struct String h_ = call_121;
    struct IntStringTuple2 tuple_40;
    tuple_40.t0 = (i_51 + 1);
    tuple_40.t1 = str_add((struct String){.str = "\\x", .len = 2}, h_);
    match_55 = tuple_40;
    goto end_match_193;
next_201:;
end_match_193:;
    return match_55;
}

int raw_(struct String str_4, int i_53) {
    int match_56;
    int match_57;
    if ((i_53 != str_4.len)) goto next_204;
    match_57 = 1;
    goto end_match_203;
next_204:;
    if ((i_53 == str_4.len)) goto next_205;
    int call_122 = charNeedsEscaping_(str_4.str[i_53]);
    match_57 = call_122;
    goto end_match_203;
next_205:;
    exit(1);
end_match_203:;
    if ((!(match_57))) goto next_206;
    match_56 = i_53;
    goto end_match_202;
next_206:;
    if (match_57) goto next_207;
    int call_123 = raw_(str_4, (i_53 + 1));
    match_56 = call_123;
    goto end_match_202;
next_207:;
    exit(1);
end_match_202:;
    return match_56;
}

struct IntStringListTuple2 {
    int t0;
    struct StringList* t1;
};

struct StringList* go_21(struct String str_4, struct StringList* acc_11, int i_52) {
    int call_124 = raw_(str_4, i_52);
    int r_21 = call_124;
    struct String call_125 = strSlice_(i_52, r_21, str_4);
    struct StringList* list_30 = (struct StringList*)malloc(sizeof(struct StringList));
    list_30->head = call_125;
    list_30->tail = acc_11;
    struct IntStringListTuple2 tuple_41;
    tuple_41.t0 = r_21;
    tuple_41.t1 = list_30;
    int i_54 = tuple_41.t0;
    struct StringList* acc_12 = tuple_41.t1;
    struct StringList* match_58;
    if ((i_54 != str_4.len)) goto next_209;
    match_58 = acc_12;
    goto end_match_208;
next_209:;
    if ((i_54 == str_4.len)) goto next_210;
    struct IntStringTuple2 call_126 = strEscapeCore_(i_54, str_4);
    int i_55 = call_126.t0;
    struct String s_6 = call_126.t1;
    struct StringList* list_31 = (struct StringList*)malloc(sizeof(struct StringList));
    list_31->head = s_6;
    list_31->tail = acc_12;
    struct StringList* call_127 = go_21(str_4, list_31, i_55);
    match_58 = call_127;
    goto end_match_208;
next_210:;
    exit(1);
end_match_208:;
    return match_58;
}

struct String strEscape_(struct String str_4) {
    struct String match_59;
    int call_128 = strNeedsEscaping_(str_4);
    if (call_128) goto next_212;
    match_59 = str_4;
    goto end_match_211;
next_212:;
    if ((!(call_128))) goto next_213;
    struct StringList* call_129 = go_21(str_4, NULL, 0);
    struct StringList* call_130 = listRev_2(call_129);
    struct String call_131 = strConcat_(call_130);
    match_59 = call_131;
    goto end_match_211;
next_213:;
    exit(1);
end_match_211:;
    return match_59;
}

struct StringList* goChildren_(struct String eol_1, struct DumpTree_List* children_2, struct StringList* acc_14) {
    struct StringList* match_60;
    if ((!((!(children_2))))) goto next_215;
    match_60 = acc_14;
    goto end_match_214;
next_215:;
    if ((!(children_2))) goto next_216;
    struct DumpTree_ child_ = children_2->head;
    struct DumpTree_List* children_3 = children_2->tail;
    struct StringList* call_132 = cons_1(eol_1, acc_14);
    struct StringList* call_133 = cons_1((struct String){.str = "- ", .len = 2}, call_132);
    struct StringList* call_134 = go_22(str_add(eol_1, (struct String){.str = "  ", .len = 2}), child_, call_133);
    struct StringList* call_135 = goChildren_(eol_1, children_3, call_134);
    match_60 = call_135;
    goto end_match_214;
next_216:;
    exit(1);
end_match_214:;
    return match_60;
}

struct StringList* goNext_(struct String eol_2, struct DumpTree_List* next_2, struct StringList* acc_15) {
    struct StringList* match_61;
    if ((!((!(next_2))))) goto next_218;
    match_61 = acc_15;
    goto end_match_217;
next_218:;
    if ((!(next_2))) goto next_219;
    struct DumpTree_ next_3 = next_2->head;
    if ((!((!(next_2->tail))))) goto next_219;
    struct StringList* call_136 = cons_1(eol_2, acc_15);
    struct StringList* call_137 = go_22(eol_2, next_3, call_136);
    match_61 = call_137;
    goto end_match_217;
next_219:;
    struct StringList* call_138 = failwith_2((struct String){.str = "NEVER: DumpTree.next never empty", .len = 32});
    match_61 = call_138;
    goto end_match_217;
next_220:;
end_match_217:;
    return match_61;
}

struct StringList* go_22(struct String eol_, struct DumpTree_ node_1, struct StringList* acc_13) {
    struct StringList* match_62;
    struct String text_46 = (*(node_1.DumpTree_)).t0;
    if ((!((!((*(node_1.DumpTree_)).t1))))) goto next_222;
    if ((!((!((*(node_1.DumpTree_)).t2))))) goto next_222;
    struct String call_139 = strEscape_(text_46);
    struct StringList* call_140 = cons_1(call_139, acc_13);
    match_62 = call_140;
    goto end_match_221;
next_222:;
    struct String text_47 = (*(node_1.DumpTree_)).t0;
    if ((!((*(node_1.DumpTree_)).t1))) goto next_223;
    struct String childText_ = (*((*(node_1.DumpTree_)).t1->head.DumpTree_)).t0;
    if ((!((!((*((*(node_1.DumpTree_)).t1->head.DumpTree_)).t1))))) goto next_223;
    if ((!((!((*((*(node_1.DumpTree_)).t1->head.DumpTree_)).t2))))) goto next_223;
    if ((!((!((*(node_1.DumpTree_)).t1->tail))))) goto next_223;
    struct DumpTree_List* next_4 = (*(node_1.DumpTree_)).t2;
    struct String call_141 = strEscape_(childText_);
    struct String call_142 = strEscape_(text_47);
    struct StringList* call_143 = cons_1(call_142, acc_13);
    struct StringList* call_144 = cons_1((struct String){.str = ": ", .len = 2}, call_143);
    struct StringList* call_145 = cons_1(call_141, call_144);
    struct StringList* call_146 = goNext_(eol_, next_4, call_145);
    match_62 = call_146;
    goto end_match_221;
next_223:;
    struct String text_48 = (*(node_1.DumpTree_)).t0;
    struct DumpTree_List* children_4 = (*(node_1.DumpTree_)).t1;
    struct DumpTree_List* next_5 = (*(node_1.DumpTree_)).t2;
    struct String call_147 = strEscape_(text_48);
    struct StringList* call_148 = cons_1(call_147, acc_13);
    struct StringList* call_149 = cons_1((struct String){.str = ":", .len = 1}, call_148);
    struct StringList* call_150 = goChildren_(eol_, children_4, call_149);
    struct StringList* call_151 = goNext_(eol_, next_5, call_150);
    match_62 = call_151;
    goto end_match_221;
next_224:;
    exit(1);
end_match_221:;
    return match_62;
}

struct String dumpTreeToString_(struct DumpTree_ node_) {
    struct String eol_3 = (struct String){.str = "\n", .len = 1};
    struct StringList* call_152 = go_22(eol_3, node_, NULL);
    struct StringList* call_153 = listRev_2(call_152);
    struct String call_154 = strConcat_(call_153);
    return call_154;
}

struct IntStringTuple2List {
    struct IntStringTuple2 head;
    struct IntStringTuple2List* tail;
};

struct IntStringTuple2ListIntTuple2 {
    struct IntStringTuple2List* t0;
    int t1;
};

struct NameCtx_ nameCtxEmpty_(int arg_91) {
    struct IntStringTuple2ListIntTuple2 tuple_42;
    tuple_42.t0 = NULL;
    tuple_42.t1 = 0;
    struct IntStringTuple2ListIntTuple2* payload_11 = (struct IntStringTuple2ListIntTuple2*)malloc(sizeof(struct IntStringTuple2ListIntTuple2));
    (*(((struct IntStringTuple2ListIntTuple2*)payload_11))) = tuple_42;
    struct NameCtx_ variant_11 = (struct NameCtx_){.tag = NameCtx_, .NameCtx_ = payload_11};
    return variant_11;
}

struct IntNameCtx_Tuple2 {
    int t0;
    struct NameCtx_ t1;
};

struct IntNameCtx_Tuple2 nameCtxAdd_1(struct String ident_, struct NameCtx_ arg_92) {
    struct IntStringTuple2List* map_ = (*(arg_92.NameCtx_)).t0;
    int serial_ = (*(arg_92.NameCtx_)).t1;
    int serial_1 = (serial_ + 1);
    struct IntStringTuple2ListIntTuple2 tuple_44;
    tuple_44.t0 = map_;
    tuple_44.t1 = serial_1;
    struct IntStringTuple2ListIntTuple2* payload_12 = (struct IntStringTuple2ListIntTuple2*)malloc(sizeof(struct IntStringTuple2ListIntTuple2));
    (*(((struct IntStringTuple2ListIntTuple2*)payload_12))) = tuple_44;
    struct NameCtx_ variant_12 = (struct NameCtx_){.tag = NameCtx_, .NameCtx_ = payload_12};
    struct IntNameCtx_Tuple2 tuple_43;
    tuple_43.t0 = serial_1;
    tuple_43.t1 = variant_12;
    return tuple_43;
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

struct Trait_ traitMapTys_(struct Ty_Ty_Fun1 f_6, struct Trait_ it_) {
    struct Trait_ match_63;
    if ((it_.tag != Add_2)) goto next_226;
    struct Ty_ ty_ = (*(it_.Add_2));
    struct Ty_ app_16 = f_6.fun(f_6.env, ty_);
    struct Ty_* payload_13 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_13))) = app_16;
    struct Trait_ variant_13 = (struct Trait_){.tag = Add_2, .Add_2 = payload_13};
    match_63 = variant_13;
    goto end_match_225;
next_226:;
    if ((it_.tag != Eq_2)) goto next_227;
    struct Ty_ ty_1 = (*(it_.Eq_2));
    struct Ty_ app_17 = f_6.fun(f_6.env, ty_1);
    struct Ty_* payload_14 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_14))) = app_17;
    struct Trait_ variant_14 = (struct Trait_){.tag = Eq_2, .Eq_2 = payload_14};
    match_63 = variant_14;
    goto end_match_225;
next_227:;
    if ((it_.tag != Cmp_1)) goto next_228;
    struct Ty_ ty_2 = (*(it_.Cmp_1));
    struct Ty_ app_18 = f_6.fun(f_6.env, ty_2);
    struct Ty_* payload_15 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_15))) = app_18;
    struct Trait_ variant_15 = (struct Trait_){.tag = Cmp_1, .Cmp_1 = payload_15};
    match_63 = variant_15;
    goto end_match_225;
next_228:;
    if ((it_.tag != Index_1)) goto next_229;
    struct Ty_ lTy_ = (*(it_.Index_1)).t0;
    struct Ty_ rTy_ = (*(it_.Index_1)).t1;
    struct Ty_ outputTy_ = (*(it_.Index_1)).t2;
    struct Ty_ app_19 = f_6.fun(f_6.env, lTy_);
    struct Ty_ app_20 = f_6.fun(f_6.env, rTy_);
    struct Ty_ app_21 = f_6.fun(f_6.env, outputTy_);
    struct Ty_Ty_Ty_Tuple3 tuple_45;
    tuple_45.t0 = app_19;
    tuple_45.t1 = app_20;
    tuple_45.t2 = app_21;
    struct Ty_Ty_Ty_Tuple3* payload_16 = (struct Ty_Ty_Ty_Tuple3*)malloc(sizeof(struct Ty_Ty_Ty_Tuple3));
    (*(((struct Ty_Ty_Ty_Tuple3*)payload_16))) = tuple_45;
    struct Trait_ variant_16 = (struct Trait_){.tag = Index_1, .Index_1 = payload_16};
    match_63 = variant_16;
    goto end_match_225;
next_229:;
    if ((it_.tag != ToInt_)) goto next_230;
    struct Ty_ ty_3 = (*(it_.ToInt_));
    struct Ty_ app_22 = f_6.fun(f_6.env, ty_3);
    struct Ty_* payload_17 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_17))) = app_22;
    struct Trait_ variant_17 = (struct Trait_){.tag = ToInt_, .ToInt_ = payload_17};
    match_63 = variant_17;
    goto end_match_225;
next_230:;
    if ((it_.tag != ToString_)) goto next_231;
    struct Ty_ ty_4 = (*(it_.ToString_));
    struct Ty_ app_23 = f_6.fun(f_6.env, ty_4);
    struct Ty_* payload_18 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_18))) = app_23;
    struct Trait_ variant_18 = (struct Trait_){.tag = ToString_, .ToString_ = payload_18};
    match_63 = variant_18;
    goto end_match_225;
next_231:;
    exit(1);
end_match_225:;
    return match_63;
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
    struct TyCon_Ty_ListTuple2 tuple_46;
    tuple_46.t0 = (struct TyCon_){.tag = Tuple_1};
    tuple_46.t1 = tys_;
    struct TyCon_Ty_ListTuple2* payload_19 = (struct TyCon_Ty_ListTuple2*)malloc(sizeof(struct TyCon_Ty_ListTuple2));
    (*(((struct TyCon_Ty_ListTuple2*)payload_19))) = tuple_46;
    struct Ty_ variant_19 = (struct Ty_){.tag = Con_, .Con_ = payload_19};
    return variant_19;
}

struct Ty_ tyList_(struct Ty_ ty_5) {
    struct Ty_List* list_32 = (struct Ty_List*)malloc(sizeof(struct Ty_List));
    list_32->head = ty_5;
    list_32->tail = NULL;
    struct TyCon_Ty_ListTuple2 tuple_47;
    tuple_47.t0 = (struct TyCon_){.tag = List_};
    tuple_47.t1 = list_32;
    struct TyCon_Ty_ListTuple2* payload_20 = (struct TyCon_Ty_ListTuple2*)malloc(sizeof(struct TyCon_Ty_ListTuple2));
    (*(((struct TyCon_Ty_ListTuple2*)payload_20))) = tuple_47;
    struct Ty_ variant_20 = (struct Ty_){.tag = Con_, .Con_ = payload_20};
    return variant_20;
}

struct Ty_ tyFun_(struct Ty_ sourceTy_, struct Ty_ targetTy_) {
    struct Ty_List* list_34 = (struct Ty_List*)malloc(sizeof(struct Ty_List));
    list_34->head = targetTy_;
    list_34->tail = NULL;
    struct Ty_List* list_33 = (struct Ty_List*)malloc(sizeof(struct Ty_List));
    list_33->head = sourceTy_;
    list_33->tail = list_34;
    struct TyCon_Ty_ListTuple2 tuple_48;
    tuple_48.t0 = (struct TyCon_){.tag = Fun_4};
    tuple_48.t1 = list_33;
    struct TyCon_Ty_ListTuple2* payload_21 = (struct TyCon_Ty_ListTuple2*)malloc(sizeof(struct TyCon_Ty_ListTuple2));
    (*(((struct TyCon_Ty_ListTuple2*)payload_21))) = tuple_48;
    struct Ty_ variant_21 = (struct Ty_){.tag = Con_, .Con_ = payload_21};
    return variant_21;
}

struct Ty_ tyRef_(int serial_2, struct Ty_List* tys_1) {
    int* payload_22 = (int*)malloc(sizeof(int));
    (*(((int*)payload_22))) = serial_2;
    struct TyCon_ variant_22 = (struct TyCon_){.tag = Ref_, .Ref_ = payload_22};
    struct TyCon_Ty_ListTuple2 tuple_49;
    tuple_49.t0 = variant_22;
    tuple_49.t1 = tys_1;
    struct TyCon_Ty_ListTuple2* payload_23 = (struct TyCon_Ty_ListTuple2*)malloc(sizeof(struct TyCon_Ty_ListTuple2));
    (*(((struct TyCon_Ty_ListTuple2*)payload_23))) = tuple_49;
    struct Ty_ variant_23 = (struct Ty_){.tag = Con_, .Con_ = payload_23};
    return variant_23;
}

struct StringTy_ListTuple2 {
    struct String t0;
    struct Ty_List* t1;
};

struct Ty_ tyPrimFromIdent_(struct Ty_ tyUnit_, struct Ty_ tyObj_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct String ident_1, struct Ty_List* tys_2, struct IntIntTuple2 loc_10) {
    struct Ty_ match_64;
    struct StringTy_ListTuple2 tuple_50;
    tuple_50.t0 = ident_1;
    tuple_50.t1 = tys_2;
    if ((str_cmp(tuple_50.t0, (struct String){.str = "unit", .len = 4}) != 0)) goto next_233;
    if ((!((!(tuple_50.t1))))) goto next_233;
    match_64 = tyUnit_;
    goto end_match_232;
next_233:;
    if ((str_cmp(tuple_50.t0, (struct String){.str = "bool", .len = 4}) != 0)) goto next_234;
    if ((!((!(tuple_50.t1))))) goto next_234;
    match_64 = tyBool_;
    goto end_match_232;
next_234:;
    if ((str_cmp(tuple_50.t0, (struct String){.str = "int", .len = 3}) != 0)) goto next_235;
    if ((!((!(tuple_50.t1))))) goto next_235;
    match_64 = tyInt_;
    goto end_match_232;
next_235:;
    if ((str_cmp(tuple_50.t0, (struct String){.str = "char", .len = 4}) != 0)) goto next_236;
    if ((!((!(tuple_50.t1))))) goto next_236;
    match_64 = tyChar_;
    goto end_match_232;
next_236:;
    if ((str_cmp(tuple_50.t0, (struct String){.str = "string", .len = 6}) != 0)) goto next_237;
    if ((!((!(tuple_50.t1))))) goto next_237;
    match_64 = tyStr_;
    goto end_match_232;
next_237:;
    if ((str_cmp(tuple_50.t0, (struct String){.str = "obj", .len = 3}) != 0)) goto next_238;
    if ((!((!(tuple_50.t1))))) goto next_238;
    match_64 = tyObj_;
    goto end_match_232;
next_238:;
    if ((str_cmp(tuple_50.t0, (struct String){.str = "list", .len = 4}) != 0)) goto next_239;
    if ((!(tuple_50.t1))) goto next_239;
    struct Ty_ itemTy_ = tuple_50.t1->head;
    if ((!((!(tuple_50.t1->tail))))) goto next_239;
    struct Ty_ call_155 = tyList_(itemTy_);
    match_64 = call_155;
    goto end_match_232;
next_239:;
    struct IntIntTuple2* payload_24 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_24))) = loc_10;
    struct Ty_ variant_24 = (struct Ty_){.tag = Error_1, .Error_1 = payload_24};
    match_64 = variant_24;
    goto end_match_232;
next_240:;
end_match_232:;
    return match_64;
}

struct IntIntIntTuple2Tuple2 {
    int t0;
    struct IntIntTuple2 t1;
};

int go_23(int tySerial_, struct Ty_ ty_7) {
    int match_65;
    if ((ty_7.tag != Error_1)) goto next_243;
    goto match_body_242;
next_243:;
    if ((ty_7.tag != Con_)) goto next_244;
    if ((!((!((*(ty_7.Con_)).t1))))) goto next_244;
    goto match_body_242;
match_body_242:;
    match_65 = 1;
    goto end_match_241;
next_244:;
    if ((ty_7.tag != Con_)) goto next_245;
    struct TyCon_ tyCon_ = (*(ty_7.Con_)).t0;
    if ((!((*(ty_7.Con_)).t1))) goto next_245;
    struct Ty_ ty_8 = (*(ty_7.Con_)).t1->head;
    struct Ty_List* tys_3 = (*(ty_7.Con_)).t1->tail;
    int match_66;
    int call_156 = go_23(tySerial_, ty_8);
    if ((!(call_156))) goto next_248;
    struct TyCon_Ty_ListTuple2 tuple_51;
    tuple_51.t0 = tyCon_;
    tuple_51.t1 = tys_3;
    struct TyCon_Ty_ListTuple2* payload_25 = (struct TyCon_Ty_ListTuple2*)malloc(sizeof(struct TyCon_Ty_ListTuple2));
    (*(((struct TyCon_Ty_ListTuple2*)payload_25))) = tuple_51;
    struct Ty_ variant_25 = (struct Ty_){.tag = Con_, .Con_ = payload_25};
    int call_157 = go_23(tySerial_, variant_25);
    match_66 = call_157;
    goto end_match_247;
next_248:;
    if (call_156) goto next_249;
    match_66 = 0;
    goto end_match_247;
next_249:;
    exit(1);
end_match_247:;
    match_65 = match_66;
    goto end_match_241;
next_245:;
    if ((ty_7.tag != Meta_)) goto next_246;
    int s_7 = (*(ty_7.Meta_)).t0;
    match_65 = (s_7 != tySerial_);
    goto end_match_241;
next_246:;
    exit(1);
end_match_241:;
    return match_65;
}

int tyIsFreeIn_(struct Ty_ ty_6, int tySerial_) {
    int call_158 = go_23(tySerial_, ty_6);
    return call_158;
}

int go_24(struct Ty_List* tys_4) {
    int match_67;
    if ((!((!(tys_4))))) goto next_251;
    match_67 = 1;
    goto end_match_250;
next_251:;
    if ((!(tys_4))) goto next_252;
    if ((tys_4->head.tag != Meta_)) goto next_252;
    match_67 = 0;
    goto end_match_250;
next_252:;
    if ((!(tys_4))) goto next_253;
    if ((tys_4->head.tag != Error_1)) goto next_253;
    struct Ty_List* tys_5 = tys_4->tail;
    int call_159 = go_24(tys_5);
    match_67 = call_159;
    goto end_match_250;
next_253:;
    if ((!(tys_4))) goto next_254;
    if ((tys_4->head.tag != Con_)) goto next_254;
    struct Ty_List* tys1_ = (*(tys_4->head.Con_)).t1;
    struct Ty_List* tys2_ = tys_4->tail;
    int match_68;
    int call_160 = go_24(tys1_);
    if ((!(call_160))) goto next_256;
    int call_161 = go_24(tys2_);
    match_68 = call_161;
    goto end_match_255;
next_256:;
    if (call_160) goto next_257;
    match_68 = 0;
    goto end_match_255;
next_257:;
    exit(1);
end_match_255:;
    match_67 = match_68;
    goto end_match_250;
next_254:;
    exit(1);
end_match_250:;
    return match_67;
}

int tyIsMonomorphic_(struct Ty_ ty_9) {
    struct Ty_List* list_35 = (struct Ty_List*)malloc(sizeof(struct Ty_List));
    list_35->head = ty_9;
    list_35->tail = NULL;
    int call_162 = go_24(list_35);
    return call_162;
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
    struct String match_69;
    if ((tyDef_.tag != Meta_1)) goto next_259;
    struct String ident_2 = (*(tyDef_.Meta_1)).t0;
    match_69 = ident_2;
    goto end_match_258;
next_259:;
    if ((tyDef_.tag != Union_2)) goto next_260;
    struct String ident_3 = (*(tyDef_.Union_2)).t0;
    match_69 = ident_3;
    goto end_match_258;
next_260:;
    exit(1);
end_match_258:;
    return match_69;
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
    struct String match_70;
    if ((varDef_.tag != Var_)) goto next_262;
    struct String ident_4 = (*(varDef_.Var_)).t0;
    match_70 = ident_4;
    goto end_match_261;
next_262:;
    if ((varDef_.tag != Fun_5)) goto next_263;
    struct String ident_5 = (*(varDef_.Fun_5)).t0;
    match_70 = ident_5;
    goto end_match_261;
next_263:;
    if ((varDef_.tag != Variant_)) goto next_264;
    struct String ident_6 = (*(varDef_.Variant_)).t0;
    match_70 = ident_6;
    goto end_match_261;
next_264:;
    exit(1);
end_match_261:;
    return match_70;
}

struct Ty_ litToTy_(struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Lit_ lit_) {
    struct Ty_ match_71;
    if ((lit_.tag != Bool_)) goto next_266;
    match_71 = tyBool_;
    goto end_match_265;
next_266:;
    if ((lit_.tag != Int_)) goto next_267;
    match_71 = tyInt_;
    goto end_match_265;
next_267:;
    if ((lit_.tag != Char_)) goto next_268;
    match_71 = tyChar_;
    goto end_match_265;
next_268:;
    if ((lit_.tag != Str_)) goto next_269;
    match_71 = tyStr_;
    goto end_match_265;
next_269:;
    exit(1);
end_match_265:;
    return match_71;
}

struct Ty_ meta_(struct IntIntTuple2 noLoc_, int id_) {
    struct IntIntIntTuple2Tuple2 tuple_52;
    tuple_52.t0 = id_;
    tuple_52.t1 = noLoc_;
    struct IntIntIntTuple2Tuple2* payload_26 = (struct IntIntIntTuple2Tuple2*)malloc(sizeof(struct IntIntIntTuple2Tuple2));
    (*(((struct IntIntIntTuple2Tuple2*)payload_26))) = tuple_52;
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
    struct Ty_Trait_ListTuple2 tuple_53;
    tuple_53.t0 = ty_10;
    tuple_53.t1 = NULL;
    struct Ty_Trait_ListTuple2* payload_27 = (struct Ty_Trait_ListTuple2*)malloc(sizeof(struct Ty_Trait_ListTuple2));
    (*(((struct Ty_Trait_ListTuple2*)payload_27))) = tuple_53;
    struct TySpec_ variant_27 = (struct TySpec_){.tag = TySpec_, .TySpec_ = payload_27};
    return variant_27;
}

struct TySpec_ poly_(struct Ty_ ty_11, struct Trait_List* traits_) {
    struct Ty_Trait_ListTuple2 tuple_54;
    tuple_54.t0 = ty_11;
    tuple_54.t1 = traits_;
    struct Ty_Trait_ListTuple2* payload_28 = (struct Ty_Trait_ListTuple2*)malloc(sizeof(struct Ty_Trait_ListTuple2));
    (*(((struct Ty_Trait_ListTuple2*)payload_28))) = tuple_54;
    struct TySpec_ variant_28 = (struct TySpec_){.tag = TySpec_, .TySpec_ = payload_28};
    return variant_28;
}

struct TySpec_ primToTySpec_(struct Ty_ tyUnit_, struct Ty_ tyObj_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct IntIntTuple2 noLoc_, struct HPrim_ prim_) {
    struct TySpec_ match_72;
    if ((prim_.tag != Add_3)) goto next_271;
    struct Ty_ call_163 = meta_(noLoc_, 1);
    struct Ty_ addTy_ = call_163;
    struct Ty_ call_164 = tyFun_(addTy_, addTy_);
    struct Ty_ call_165 = tyFun_(addTy_, call_164);
    struct Ty_* payload_29 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_29))) = addTy_;
    struct Trait_ variant_29 = (struct Trait_){.tag = Add_2, .Add_2 = payload_29};
    struct Trait_List* list_36 = (struct Trait_List*)malloc(sizeof(struct Trait_List));
    list_36->head = variant_29;
    list_36->tail = NULL;
    struct TySpec_ call_166 = poly_(call_165, list_36);
    match_72 = call_166;
    goto end_match_270;
next_271:;
    if ((prim_.tag != Sub_1)) goto next_272;
    struct Ty_ call_167 = tyFun_(tyInt_, tyInt_);
    struct Ty_ call_168 = tyFun_(tyInt_, call_167);
    struct TySpec_ call_169 = mono_(call_168);
    match_72 = call_169;
    goto end_match_270;
next_272:;
    if ((prim_.tag != Mul_2)) goto next_273;
    struct Ty_ call_170 = tyFun_(tyInt_, tyInt_);
    struct Ty_ call_171 = tyFun_(tyInt_, call_170);
    struct TySpec_ call_172 = mono_(call_171);
    match_72 = call_172;
    goto end_match_270;
next_273:;
    if ((prim_.tag != Div_1)) goto next_274;
    struct Ty_ call_173 = tyFun_(tyInt_, tyInt_);
    struct Ty_ call_174 = tyFun_(tyInt_, call_173);
    struct TySpec_ call_175 = mono_(call_174);
    match_72 = call_175;
    goto end_match_270;
next_274:;
    if ((prim_.tag != Mod_1)) goto next_275;
    struct Ty_ call_176 = tyFun_(tyInt_, tyInt_);
    struct Ty_ call_177 = tyFun_(tyInt_, call_176);
    struct TySpec_ call_178 = mono_(call_177);
    match_72 = call_178;
    goto end_match_270;
next_275:;
    if ((prim_.tag != Eq_3)) goto next_276;
    struct Ty_ call_179 = meta_(noLoc_, 1);
    struct Ty_ eqTy_ = call_179;
    struct Ty_ call_180 = tyFun_(eqTy_, tyBool_);
    struct Ty_ call_181 = tyFun_(eqTy_, call_180);
    struct Ty_* payload_30 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_30))) = eqTy_;
    struct Trait_ variant_30 = (struct Trait_){.tag = Eq_2, .Eq_2 = payload_30};
    struct Trait_List* list_37 = (struct Trait_List*)malloc(sizeof(struct Trait_List));
    list_37->head = variant_30;
    list_37->tail = NULL;
    struct TySpec_ call_182 = poly_(call_181, list_37);
    match_72 = call_182;
    goto end_match_270;
next_276:;
    if ((prim_.tag != Lt_2)) goto next_277;
    struct Ty_ call_183 = meta_(noLoc_, 1);
    struct Ty_ cmpTy_ = call_183;
    struct Ty_ call_184 = tyFun_(cmpTy_, tyBool_);
    struct Ty_ call_185 = tyFun_(cmpTy_, call_184);
    struct Ty_* payload_31 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_31))) = cmpTy_;
    struct Trait_ variant_31 = (struct Trait_){.tag = Cmp_1, .Cmp_1 = payload_31};
    struct Trait_List* list_38 = (struct Trait_List*)malloc(sizeof(struct Trait_List));
    list_38->head = variant_31;
    list_38->tail = NULL;
    struct TySpec_ call_186 = poly_(call_185, list_38);
    match_72 = call_186;
    goto end_match_270;
next_277:;
    if ((prim_.tag != Nil_1)) goto next_278;
    struct Ty_ call_187 = meta_(noLoc_, 1);
    struct Ty_ itemTy_1 = call_187;
    struct Ty_ call_188 = tyList_(itemTy_1);
    struct TySpec_ call_189 = poly_(call_188, NULL);
    match_72 = call_189;
    goto end_match_270;
next_278:;
    if ((prim_.tag != Cons_4)) goto next_279;
    struct Ty_ call_190 = meta_(noLoc_, 1);
    struct Ty_ itemTy_2 = call_190;
    struct Ty_ call_191 = tyList_(itemTy_2);
    struct Ty_ listTy_ = call_191;
    struct Ty_ call_192 = tyFun_(listTy_, listTy_);
    struct Ty_ call_193 = tyFun_(itemTy_2, call_192);
    struct TySpec_ call_194 = poly_(call_193, NULL);
    match_72 = call_194;
    goto end_match_270;
next_279:;
    if ((prim_.tag != Index_2)) goto next_280;
    struct Ty_ call_195 = meta_(noLoc_, 1);
    struct Ty_ lTy_1 = call_195;
    struct Ty_ call_196 = meta_(noLoc_, 2);
    struct Ty_ rTy_1 = call_196;
    struct Ty_ call_197 = meta_(noLoc_, 3);
    struct Ty_ resultTy_ = call_197;
    struct Ty_ call_198 = tyFun_(rTy_1, resultTy_);
    struct Ty_ call_199 = tyFun_(lTy_1, call_198);
    struct Ty_Ty_Ty_Tuple3 tuple_55;
    tuple_55.t0 = lTy_1;
    tuple_55.t1 = rTy_1;
    tuple_55.t2 = resultTy_;
    struct Ty_Ty_Ty_Tuple3* payload_32 = (struct Ty_Ty_Ty_Tuple3*)malloc(sizeof(struct Ty_Ty_Ty_Tuple3));
    (*(((struct Ty_Ty_Ty_Tuple3*)payload_32))) = tuple_55;
    struct Trait_ variant_32 = (struct Trait_){.tag = Index_1, .Index_1 = payload_32};
    struct Trait_List* list_39 = (struct Trait_List*)malloc(sizeof(struct Trait_List));
    list_39->head = variant_32;
    list_39->tail = NULL;
    struct TySpec_ call_200 = poly_(call_199, list_39);
    match_72 = call_200;
    goto end_match_270;
next_280:;
    if ((prim_.tag != Not_)) goto next_281;
    struct Ty_ call_201 = tyFun_(tyBool_, tyBool_);
    struct TySpec_ call_202 = mono_(call_201);
    match_72 = call_202;
    goto end_match_270;
next_281:;
    if ((prim_.tag != Exit_)) goto next_282;
    struct Ty_ call_203 = meta_(noLoc_, 1);
    struct Ty_ resultTy_1 = call_203;
    struct Ty_ call_204 = tyFun_(tyInt_, resultTy_1);
    struct TySpec_ call_205 = poly_(call_204, NULL);
    match_72 = call_205;
    goto end_match_270;
next_282:;
    if ((prim_.tag != Assert_)) goto next_283;
    struct Ty_ call_206 = tyFun_(tyBool_, tyUnit_);
    struct TySpec_ call_207 = mono_(call_206);
    match_72 = call_207;
    goto end_match_270;
next_283:;
    if ((prim_.tag != Box_)) goto next_284;
    struct Ty_ call_208 = meta_(noLoc_, 1);
    struct Ty_ itemTy_3 = call_208;
    struct Ty_ call_209 = tyFun_(itemTy_3, tyObj_);
    struct TySpec_ call_210 = poly_(call_209, NULL);
    match_72 = call_210;
    goto end_match_270;
next_284:;
    if ((prim_.tag != Unbox_)) goto next_285;
    struct Ty_ call_211 = meta_(noLoc_, 1);
    struct Ty_ itemTy_4 = call_211;
    struct Ty_ call_212 = tyFun_(tyObj_, itemTy_4);
    struct TySpec_ call_213 = poly_(call_212, NULL);
    match_72 = call_213;
    goto end_match_270;
next_285:;
    if ((prim_.tag != Char_3)) goto next_286;
    struct Ty_ call_214 = tyFun_(tyInt_, tyChar_);
    struct TySpec_ call_215 = mono_(call_214);
    match_72 = call_215;
    goto end_match_270;
next_286:;
    if ((prim_.tag != Int_3)) goto next_287;
    struct Ty_ call_216 = meta_(noLoc_, 1);
    struct Ty_ toIntTy_ = call_216;
    struct Ty_ call_217 = tyFun_(toIntTy_, tyInt_);
    struct Ty_* payload_33 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_33))) = toIntTy_;
    struct Trait_ variant_33 = (struct Trait_){.tag = ToInt_, .ToInt_ = payload_33};
    struct Trait_List* list_40 = (struct Trait_List*)malloc(sizeof(struct Trait_List));
    list_40->head = variant_33;
    list_40->tail = NULL;
    struct TySpec_ call_218 = poly_(call_217, list_40);
    match_72 = call_218;
    goto end_match_270;
next_287:;
    if ((prim_.tag != String_)) goto next_288;
    struct Ty_ call_219 = meta_(noLoc_, 1);
    struct Ty_ toStrTy_ = call_219;
    struct Ty_ call_220 = tyFun_(toStrTy_, tyStr_);
    struct Ty_* payload_34 = (struct Ty_*)malloc(sizeof(struct Ty_));
    (*(((struct Ty_*)payload_34))) = toStrTy_;
    struct Trait_ variant_34 = (struct Trait_){.tag = ToString_, .ToString_ = payload_34};
    struct Trait_List* list_41 = (struct Trait_List*)malloc(sizeof(struct Trait_List));
    list_41->head = variant_34;
    list_41->tail = NULL;
    struct TySpec_ call_221 = poly_(call_220, list_41);
    match_72 = call_221;
    goto end_match_270;
next_288:;
    if ((prim_.tag != StrLength_)) goto next_289;
    struct Ty_ call_222 = tyFun_(tyStr_, tyInt_);
    struct TySpec_ call_223 = mono_(call_222);
    match_72 = call_223;
    goto end_match_270;
next_289:;
    if ((prim_.tag != StrGetSlice_)) goto next_291;
    struct Ty_ call_224 = tyFun_(tyStr_, tyStr_);
    struct Ty_ call_225 = tyFun_(tyInt_, call_224);
    struct Ty_ call_226 = tyFun_(tyInt_, call_225);
    struct TySpec_ call_227 = mono_(call_226);
    match_72 = call_227;
    goto end_match_270;
next_291:;
    if ((prim_.tag != Printfn_)) goto next_292;
    goto match_body_290;
next_292:;
    if ((prim_.tag != NativeFun_)) goto next_293;
    goto match_body_290;
match_body_290:;
    struct Ty_ call_228 = meta_(noLoc_, 1);
    struct TySpec_ call_229 = poly_(call_228, NULL);
    match_72 = call_229;
    goto end_match_270;
next_293:;
end_match_270:;
    return match_72;
}

struct HPat_ListTy_IntIntTuple2Tuple3 {
    struct HPat_List* t0;
    struct Ty_ t1;
    struct IntIntTuple2 t2;
};

struct HPat_ patUnit_(struct Ty_ tyUnit_, struct IntIntTuple2 loc_11) {
    struct HPat_ListTy_IntIntTuple2Tuple3 tuple_56;
    tuple_56.t0 = NULL;
    tuple_56.t1 = tyUnit_;
    tuple_56.t2 = loc_11;
    struct HPat_ListTy_IntIntTuple2Tuple3* payload_35 = (struct HPat_ListTy_IntIntTuple2Tuple3*)malloc(sizeof(struct HPat_ListTy_IntIntTuple2Tuple3));
    (*(((struct HPat_ListTy_IntIntTuple2Tuple3*)payload_35))) = tuple_56;
    struct HPat_ variant_35 = (struct HPat_){.tag = Tuple_2, .Tuple_2 = payload_35};
    return variant_35;
}

struct Ty_IntIntTuple2Tuple2 {
    struct Ty_ t0;
    struct IntIntTuple2 t1;
};

struct HPat_ patNil_(struct Ty_ itemTy_5, struct IntIntTuple2 loc_12) {
    struct Ty_IntIntTuple2Tuple2 tuple_57;
    tuple_57.t0 = itemTy_5;
    tuple_57.t1 = loc_12;
    struct Ty_IntIntTuple2Tuple2* payload_36 = (struct Ty_IntIntTuple2Tuple2*)malloc(sizeof(struct Ty_IntIntTuple2Tuple2));
    (*(((struct Ty_IntIntTuple2Tuple2*)payload_36))) = tuple_57;
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
    struct Ty_IntIntTuple2Tuple2 match_73;
    if ((pat_.tag != Lit_2)) goto next_295;
    struct Lit_ lit_1 = (*(pat_.Lit_2)).t0;
    struct IntIntTuple2 a_ = (*(pat_.Lit_2)).t1;
    struct Ty_ call_230 = litToTy_(tyStr_, tyChar_, tyInt_, tyBool_, lit_1);
    struct Ty_IntIntTuple2Tuple2 tuple_58;
    tuple_58.t0 = call_230;
    tuple_58.t1 = a_;
    match_73 = tuple_58;
    goto end_match_294;
next_295:;
    if ((pat_.tag != Nil_)) goto next_296;
    struct Ty_ itemTy_6 = (*(pat_.Nil_)).t0;
    struct IntIntTuple2 a_1 = (*(pat_.Nil_)).t1;
    struct Ty_ call_231 = tyList_(itemTy_6);
    struct Ty_IntIntTuple2Tuple2 tuple_59;
    tuple_59.t0 = call_231;
    tuple_59.t1 = a_1;
    match_73 = tuple_59;
    goto end_match_294;
next_296:;
    if ((pat_.tag != Discard_)) goto next_297;
    struct Ty_ ty_12 = (*(pat_.Discard_)).t0;
    struct IntIntTuple2 a_2 = (*(pat_.Discard_)).t1;
    struct Ty_IntIntTuple2Tuple2 tuple_60;
    tuple_60.t0 = ty_12;
    tuple_60.t1 = a_2;
    match_73 = tuple_60;
    goto end_match_294;
next_297:;
    if ((pat_.tag != Ref_1)) goto next_298;
    struct Ty_ ty_13 = (*(pat_.Ref_1)).t1;
    struct IntIntTuple2 a_3 = (*(pat_.Ref_1)).t2;
    struct Ty_IntIntTuple2Tuple2 tuple_61;
    tuple_61.t0 = ty_13;
    tuple_61.t1 = a_3;
    match_73 = tuple_61;
    goto end_match_294;
next_298:;
    if ((pat_.tag != Nav_2)) goto next_299;
    struct Ty_ ty_14 = (*(pat_.Nav_2)).t2;
    struct IntIntTuple2 a_4 = (*(pat_.Nav_2)).t3;
    struct Ty_IntIntTuple2Tuple2 tuple_62;
    tuple_62.t0 = ty_14;
    tuple_62.t1 = a_4;
    match_73 = tuple_62;
    goto end_match_294;
next_299:;
    if ((pat_.tag != Call_1)) goto next_300;
    struct Ty_ ty_15 = (*(pat_.Call_1)).t2;
    struct IntIntTuple2 a_5 = (*(pat_.Call_1)).t3;
    struct Ty_IntIntTuple2Tuple2 tuple_63;
    tuple_63.t0 = ty_15;
    tuple_63.t1 = a_5;
    match_73 = tuple_63;
    goto end_match_294;
next_300:;
    if ((pat_.tag != Cons_3)) goto next_301;
    struct Ty_ itemTy_7 = (*(pat_.Cons_3)).t2;
    struct IntIntTuple2 a_6 = (*(pat_.Cons_3)).t3;
    struct Ty_ call_232 = tyList_(itemTy_7);
    struct Ty_IntIntTuple2Tuple2 tuple_64;
    tuple_64.t0 = call_232;
    tuple_64.t1 = a_6;
    match_73 = tuple_64;
    goto end_match_294;
next_301:;
    if ((pat_.tag != Tuple_2)) goto next_302;
    struct Ty_ ty_16 = (*(pat_.Tuple_2)).t1;
    struct IntIntTuple2 a_7 = (*(pat_.Tuple_2)).t2;
    struct Ty_IntIntTuple2Tuple2 tuple_65;
    tuple_65.t0 = ty_16;
    tuple_65.t1 = a_7;
    match_73 = tuple_65;
    goto end_match_294;
next_302:;
    if ((pat_.tag != As_2)) goto next_303;
    struct HPat_ pat_1 = (*(pat_.As_2)).t0;
    struct IntIntTuple2 a_8 = (*(pat_.As_2)).t2;
    struct Ty_IntIntTuple2Tuple2 call_233 = patExtract_(tyStr_, tyChar_, tyInt_, tyBool_, pat_1);
    struct Ty_ ty_17 = call_233.t0;
    struct Ty_IntIntTuple2Tuple2 tuple_66;
    tuple_66.t0 = ty_17;
    tuple_66.t1 = a_8;
    match_73 = tuple_66;
    goto end_match_294;
next_303:;
    if ((pat_.tag != Anno_2)) goto next_304;
    struct Ty_ ty_18 = (*(pat_.Anno_2)).t1;
    struct IntIntTuple2 a_9 = (*(pat_.Anno_2)).t2;
    struct Ty_IntIntTuple2Tuple2 tuple_67;
    tuple_67.t0 = ty_18;
    tuple_67.t1 = a_9;
    match_73 = tuple_67;
    goto end_match_294;
next_304:;
    if ((pat_.tag != Or_3)) goto next_305;
    struct Ty_ ty_19 = (*(pat_.Or_3)).t2;
    struct IntIntTuple2 a_10 = (*(pat_.Or_3)).t3;
    struct Ty_IntIntTuple2Tuple2 tuple_68;
    tuple_68.t0 = ty_19;
    tuple_68.t1 = a_10;
    match_73 = tuple_68;
    goto end_match_294;
next_305:;
    exit(1);
end_match_294:;
    return match_73;
}

struct IntIntTuple2IntIntTuple2Fun1 {
    struct IntIntTuple2(*fun)(void*, struct IntIntTuple2);
    void* env;
};

struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2 {
    struct IntIntTuple2IntIntTuple2Fun1 t0;
    struct Ty_Ty_Fun1 t1;
};

struct HPat_ fun_2(void* env_, struct HPat_ arg_6) {
    struct IntIntTuple2IntIntTuple2Fun1 arg_7 = (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)env_))).t0;
    struct Ty_Ty_Fun1 arg_8 = (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)env_))).t1;
    struct HPat_ call_234 = go_25(arg_7, arg_8, arg_6);
    return call_234;
}

struct HPat_ fun_3(void* env_1, struct HPat_ arg_9) {
    struct IntIntTuple2IntIntTuple2Fun1 arg_10 = (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)env_1))).t0;
    struct Ty_Ty_Fun1 arg_11 = (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)env_1))).t1;
    struct HPat_ call_235 = go_25(arg_10, arg_11, arg_9);
    return call_235;
}

struct HPat_ go_25(struct IntIntTuple2IntIntTuple2Fun1 g_, struct Ty_Ty_Fun1 f_7, struct HPat_ pat_3) {
    struct HPat_ match_74;
    if ((pat_3.tag != Lit_2)) goto next_307;
    struct Lit_ lit_2 = (*(pat_3.Lit_2)).t0;
    struct IntIntTuple2 a_11 = (*(pat_3.Lit_2)).t1;
    struct IntIntTuple2 app_24 = g_.fun(g_.env, a_11);
    struct Lit_IntIntTuple2Tuple2 tuple_69;
    tuple_69.t0 = lit_2;
    tuple_69.t1 = app_24;
    struct Lit_IntIntTuple2Tuple2* payload_37 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_37))) = tuple_69;
    struct HPat_ variant_37 = (struct HPat_){.tag = Lit_2, .Lit_2 = payload_37};
    match_74 = variant_37;
    goto end_match_306;
next_307:;
    if ((pat_3.tag != Nil_)) goto next_308;
    struct Ty_ itemTy_8 = (*(pat_3.Nil_)).t0;
    struct IntIntTuple2 a_12 = (*(pat_3.Nil_)).t1;
    struct Ty_ app_25 = f_7.fun(f_7.env, itemTy_8);
    struct IntIntTuple2 app_26 = g_.fun(g_.env, a_12);
    struct Ty_IntIntTuple2Tuple2 tuple_70;
    tuple_70.t0 = app_25;
    tuple_70.t1 = app_26;
    struct Ty_IntIntTuple2Tuple2* payload_38 = (struct Ty_IntIntTuple2Tuple2*)malloc(sizeof(struct Ty_IntIntTuple2Tuple2));
    (*(((struct Ty_IntIntTuple2Tuple2*)payload_38))) = tuple_70;
    struct HPat_ variant_38 = (struct HPat_){.tag = Nil_, .Nil_ = payload_38};
    match_74 = variant_38;
    goto end_match_306;
next_308:;
    if ((pat_3.tag != Discard_)) goto next_309;
    struct Ty_ ty_20 = (*(pat_3.Discard_)).t0;
    struct IntIntTuple2 a_13 = (*(pat_3.Discard_)).t1;
    struct Ty_ app_27 = f_7.fun(f_7.env, ty_20);
    struct IntIntTuple2 app_28 = g_.fun(g_.env, a_13);
    struct Ty_IntIntTuple2Tuple2 tuple_71;
    tuple_71.t0 = app_27;
    tuple_71.t1 = app_28;
    struct Ty_IntIntTuple2Tuple2* payload_39 = (struct Ty_IntIntTuple2Tuple2*)malloc(sizeof(struct Ty_IntIntTuple2Tuple2));
    (*(((struct Ty_IntIntTuple2Tuple2*)payload_39))) = tuple_71;
    struct HPat_ variant_39 = (struct HPat_){.tag = Discard_, .Discard_ = payload_39};
    match_74 = variant_39;
    goto end_match_306;
next_309:;
    if ((pat_3.tag != Ref_1)) goto next_310;
    int serial_3 = (*(pat_3.Ref_1)).t0;
    struct Ty_ ty_21 = (*(pat_3.Ref_1)).t1;
    struct IntIntTuple2 a_14 = (*(pat_3.Ref_1)).t2;
    struct Ty_ app_29 = f_7.fun(f_7.env, ty_21);
    struct IntIntTuple2 app_30 = g_.fun(g_.env, a_14);
    struct IntTy_IntIntTuple2Tuple3 tuple_72;
    tuple_72.t0 = serial_3;
    tuple_72.t1 = app_29;
    tuple_72.t2 = app_30;
    struct IntTy_IntIntTuple2Tuple3* payload_40 = (struct IntTy_IntIntTuple2Tuple3*)malloc(sizeof(struct IntTy_IntIntTuple2Tuple3));
    (*(((struct IntTy_IntIntTuple2Tuple3*)payload_40))) = tuple_72;
    struct HPat_ variant_40 = (struct HPat_){.tag = Ref_1, .Ref_1 = payload_40};
    match_74 = variant_40;
    goto end_match_306;
next_310:;
    if ((pat_3.tag != Nav_2)) goto next_311;
    struct HPat_ pat_4 = (*(pat_3.Nav_2)).t0;
    struct String ident_7 = (*(pat_3.Nav_2)).t1;
    struct Ty_ ty_22 = (*(pat_3.Nav_2)).t2;
    struct IntIntTuple2 a_15 = (*(pat_3.Nav_2)).t3;
    struct Ty_ app_31 = f_7.fun(f_7.env, ty_22);
    struct IntIntTuple2 app_32 = g_.fun(g_.env, a_15);
    struct HPat_StringTy_IntIntTuple2Tuple4 tuple_73;
    tuple_73.t0 = pat_4;
    tuple_73.t1 = ident_7;
    tuple_73.t2 = app_31;
    tuple_73.t3 = app_32;
    struct HPat_StringTy_IntIntTuple2Tuple4* payload_41 = (struct HPat_StringTy_IntIntTuple2Tuple4*)malloc(sizeof(struct HPat_StringTy_IntIntTuple2Tuple4));
    (*(((struct HPat_StringTy_IntIntTuple2Tuple4*)payload_41))) = tuple_73;
    struct HPat_ variant_41 = (struct HPat_){.tag = Nav_2, .Nav_2 = payload_41};
    match_74 = variant_41;
    goto end_match_306;
next_311:;
    if ((pat_3.tag != Call_1)) goto next_312;
    struct HPat_ callee_ = (*(pat_3.Call_1)).t0;
    struct HPat_List* args_ = (*(pat_3.Call_1)).t1;
    struct Ty_ ty_23 = (*(pat_3.Call_1)).t2;
    struct IntIntTuple2 a_16 = (*(pat_3.Call_1)).t3;
    struct HPat_ call_236 = go_25(g_, f_7, callee_);
    struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2 tuple_75;
    tuple_75.t0 = g_;
    tuple_75.t1 = f_7;
    void* box_ = (void*)malloc(sizeof(struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2));
    (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)box_))) = tuple_75;
    void* env_29 = box_;
    struct HPat_HPat_Fun1 fun_31 = (struct HPat_HPat_Fun1){.fun = fun_2, .env = env_29};
    struct HPat_List* call_237 = listMap_7(fun_31, args_);
    struct Ty_ app_33 = f_7.fun(f_7.env, ty_23);
    struct IntIntTuple2 app_34 = g_.fun(g_.env, a_16);
    struct HPat_HPat_ListTy_IntIntTuple2Tuple4 tuple_74;
    tuple_74.t0 = call_236;
    tuple_74.t1 = call_237;
    tuple_74.t2 = app_33;
    tuple_74.t3 = app_34;
    struct HPat_HPat_ListTy_IntIntTuple2Tuple4* payload_42 = (struct HPat_HPat_ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct HPat_HPat_ListTy_IntIntTuple2Tuple4));
    (*(((struct HPat_HPat_ListTy_IntIntTuple2Tuple4*)payload_42))) = tuple_74;
    struct HPat_ variant_42 = (struct HPat_){.tag = Call_1, .Call_1 = payload_42};
    match_74 = variant_42;
    goto end_match_306;
next_312:;
    if ((pat_3.tag != Cons_3)) goto next_313;
    struct HPat_ l_9 = (*(pat_3.Cons_3)).t0;
    struct HPat_ r_22 = (*(pat_3.Cons_3)).t1;
    struct Ty_ itemTy_9 = (*(pat_3.Cons_3)).t2;
    struct IntIntTuple2 a_17 = (*(pat_3.Cons_3)).t3;
    struct HPat_ call_238 = go_25(g_, f_7, l_9);
    struct HPat_ call_239 = go_25(g_, f_7, r_22);
    struct Ty_ app_35 = f_7.fun(f_7.env, itemTy_9);
    struct IntIntTuple2 app_36 = g_.fun(g_.env, a_17);
    struct HPat_HPat_Ty_IntIntTuple2Tuple4 tuple_76;
    tuple_76.t0 = call_238;
    tuple_76.t1 = call_239;
    tuple_76.t2 = app_35;
    tuple_76.t3 = app_36;
    struct HPat_HPat_Ty_IntIntTuple2Tuple4* payload_43 = (struct HPat_HPat_Ty_IntIntTuple2Tuple4*)malloc(sizeof(struct HPat_HPat_Ty_IntIntTuple2Tuple4));
    (*(((struct HPat_HPat_Ty_IntIntTuple2Tuple4*)payload_43))) = tuple_76;
    struct HPat_ variant_43 = (struct HPat_){.tag = Cons_3, .Cons_3 = payload_43};
    match_74 = variant_43;
    goto end_match_306;
next_313:;
    if ((pat_3.tag != Tuple_2)) goto next_314;
    struct HPat_List* itemPats_ = (*(pat_3.Tuple_2)).t0;
    struct Ty_ ty_24 = (*(pat_3.Tuple_2)).t1;
    struct IntIntTuple2 a_18 = (*(pat_3.Tuple_2)).t2;
    struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2 tuple_78;
    tuple_78.t0 = g_;
    tuple_78.t1 = f_7;
    void* box_1 = (void*)malloc(sizeof(struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2));
    (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)box_1))) = tuple_78;
    void* env_30 = box_1;
    struct HPat_HPat_Fun1 fun_32 = (struct HPat_HPat_Fun1){.fun = fun_3, .env = env_30};
    struct HPat_List* call_240 = listMap_7(fun_32, itemPats_);
    struct Ty_ app_37 = f_7.fun(f_7.env, ty_24);
    struct IntIntTuple2 app_38 = g_.fun(g_.env, a_18);
    struct HPat_ListTy_IntIntTuple2Tuple3 tuple_77;
    tuple_77.t0 = call_240;
    tuple_77.t1 = app_37;
    tuple_77.t2 = app_38;
    struct HPat_ListTy_IntIntTuple2Tuple3* payload_44 = (struct HPat_ListTy_IntIntTuple2Tuple3*)malloc(sizeof(struct HPat_ListTy_IntIntTuple2Tuple3));
    (*(((struct HPat_ListTy_IntIntTuple2Tuple3*)payload_44))) = tuple_77;
    struct HPat_ variant_44 = (struct HPat_){.tag = Tuple_2, .Tuple_2 = payload_44};
    match_74 = variant_44;
    goto end_match_306;
next_314:;
    if ((pat_3.tag != As_2)) goto next_315;
    struct HPat_ pat_5 = (*(pat_3.As_2)).t0;
    int serial_4 = (*(pat_3.As_2)).t1;
    struct IntIntTuple2 a_19 = (*(pat_3.As_2)).t2;
    struct HPat_ call_241 = go_25(g_, f_7, pat_5);
    struct IntIntTuple2 app_39 = g_.fun(g_.env, a_19);
    struct HPat_IntIntIntTuple2Tuple3 tuple_79;
    tuple_79.t0 = call_241;
    tuple_79.t1 = serial_4;
    tuple_79.t2 = app_39;
    struct HPat_IntIntIntTuple2Tuple3* payload_45 = (struct HPat_IntIntIntTuple2Tuple3*)malloc(sizeof(struct HPat_IntIntIntTuple2Tuple3));
    (*(((struct HPat_IntIntIntTuple2Tuple3*)payload_45))) = tuple_79;
    struct HPat_ variant_45 = (struct HPat_){.tag = As_2, .As_2 = payload_45};
    match_74 = variant_45;
    goto end_match_306;
next_315:;
    if ((pat_3.tag != Anno_2)) goto next_316;
    struct HPat_ pat_6 = (*(pat_3.Anno_2)).t0;
    struct Ty_ ty_25 = (*(pat_3.Anno_2)).t1;
    struct IntIntTuple2 a_20 = (*(pat_3.Anno_2)).t2;
    struct HPat_ call_242 = go_25(g_, f_7, pat_6);
    struct Ty_ app_40 = f_7.fun(f_7.env, ty_25);
    struct IntIntTuple2 app_41 = g_.fun(g_.env, a_20);
    struct HPat_Ty_IntIntTuple2Tuple3 tuple_80;
    tuple_80.t0 = call_242;
    tuple_80.t1 = app_40;
    tuple_80.t2 = app_41;
    struct HPat_Ty_IntIntTuple2Tuple3* payload_46 = (struct HPat_Ty_IntIntTuple2Tuple3*)malloc(sizeof(struct HPat_Ty_IntIntTuple2Tuple3));
    (*(((struct HPat_Ty_IntIntTuple2Tuple3*)payload_46))) = tuple_80;
    struct HPat_ variant_46 = (struct HPat_){.tag = Anno_2, .Anno_2 = payload_46};
    match_74 = variant_46;
    goto end_match_306;
next_316:;
    if ((pat_3.tag != Or_3)) goto next_317;
    struct HPat_ first_2 = (*(pat_3.Or_3)).t0;
    struct HPat_ second_2 = (*(pat_3.Or_3)).t1;
    struct Ty_ ty_26 = (*(pat_3.Or_3)).t2;
    struct IntIntTuple2 a_21 = (*(pat_3.Or_3)).t3;
    struct HPat_ call_243 = go_25(g_, f_7, first_2);
    struct HPat_ call_244 = go_25(g_, f_7, second_2);
    struct Ty_ app_42 = f_7.fun(f_7.env, ty_26);
    struct IntIntTuple2 app_43 = g_.fun(g_.env, a_21);
    struct HPat_HPat_Ty_IntIntTuple2Tuple4 tuple_81;
    tuple_81.t0 = call_243;
    tuple_81.t1 = call_244;
    tuple_81.t2 = app_42;
    tuple_81.t3 = app_43;
    struct HPat_HPat_Ty_IntIntTuple2Tuple4* payload_47 = (struct HPat_HPat_Ty_IntIntTuple2Tuple4*)malloc(sizeof(struct HPat_HPat_Ty_IntIntTuple2Tuple4));
    (*(((struct HPat_HPat_Ty_IntIntTuple2Tuple4*)payload_47))) = tuple_81;
    struct HPat_ variant_47 = (struct HPat_){.tag = Or_3, .Or_3 = payload_47};
    match_74 = variant_47;
    goto end_match_306;
next_317:;
    exit(1);
end_match_306:;
    return match_74;
}

struct HPat_ patMap_(struct Ty_Ty_Fun1 f_7, struct IntIntTuple2IntIntTuple2Fun1 g_, struct HPat_ pat_2) {
    struct HPat_ call_245 = go_25(g_, f_7, pat_2);
    return call_245;
}

struct HExpr_ hxTrue_(struct Lit_ litTrue_, struct IntIntTuple2 loc_13) {
    struct Lit_IntIntTuple2Tuple2 tuple_82;
    tuple_82.t0 = litTrue_;
    tuple_82.t1 = loc_13;
    struct Lit_IntIntTuple2Tuple2* payload_48 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_48))) = tuple_82;
    struct HExpr_ variant_48 = (struct HExpr_){.tag = Lit_3, .Lit_3 = payload_48};
    return variant_48;
}

struct HExpr_ hxFalse_(struct Lit_ litFalse_, struct IntIntTuple2 loc_14) {
    struct Lit_IntIntTuple2Tuple2 tuple_83;
    tuple_83.t0 = litFalse_;
    tuple_83.t1 = loc_14;
    struct Lit_IntIntTuple2Tuple2* payload_49 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_49))) = tuple_83;
    struct HExpr_ variant_49 = (struct HExpr_){.tag = Lit_3, .Lit_3 = payload_49};
    return variant_49;
}

enum InfOp_Tag {
    App_1,
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

struct HExpr_ hxApp_(struct HExpr_ f_8, struct HExpr_ x_19, struct Ty_ ty_27, struct IntIntTuple2 loc_15) {
    struct HExpr_List* list_43 = (struct HExpr_List*)malloc(sizeof(struct HExpr_List));
    list_43->head = x_19;
    list_43->tail = NULL;
    struct HExpr_List* list_42 = (struct HExpr_List*)malloc(sizeof(struct HExpr_List));
    list_42->head = f_8;
    list_42->tail = list_43;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4 tuple_84;
    tuple_84.t0 = (struct InfOp_){.tag = App_1};
    tuple_84.t1 = list_42;
    tuple_84.t2 = ty_27;
    tuple_84.t3 = loc_15;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4* payload_50 = (struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4));
    (*(((struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)payload_50))) = tuple_84;
    struct HExpr_ variant_50 = (struct HExpr_){.tag = Inf_, .Inf_ = payload_50};
    return variant_50;
}

struct HExpr_ hxAnno_(struct HExpr_ expr_, struct Ty_ ty_28, struct IntIntTuple2 loc_16) {
    struct HExpr_List* list_44 = (struct HExpr_List*)malloc(sizeof(struct HExpr_List));
    list_44->head = expr_;
    list_44->tail = NULL;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4 tuple_85;
    tuple_85.t0 = (struct InfOp_){.tag = Anno_3};
    tuple_85.t1 = list_44;
    tuple_85.t2 = ty_28;
    tuple_85.t3 = loc_16;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4* payload_51 = (struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4));
    (*(((struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)payload_51))) = tuple_85;
    struct HExpr_ variant_51 = (struct HExpr_){.tag = Inf_, .Inf_ = payload_51};
    return variant_51;
}

struct HExpr_ hxSemi_(struct Ty_ noTy_, struct HExpr_List* items_, struct IntIntTuple2 loc_17) {
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4 tuple_86;
    tuple_86.t0 = (struct InfOp_){.tag = Semi_2};
    tuple_86.t1 = items_;
    tuple_86.t2 = noTy_;
    tuple_86.t3 = loc_17;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4* payload_52 = (struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4));
    (*(((struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)payload_52))) = tuple_86;
    struct HExpr_ variant_52 = (struct HExpr_){.tag = Inf_, .Inf_ = payload_52};
    return variant_52;
}

struct HExpr_ hxCallProc_(struct HExpr_ callee_1, struct HExpr_List* args_1, struct Ty_ resultTy_2, struct IntIntTuple2 loc_18) {
    struct HExpr_List* list_45 = (struct HExpr_List*)malloc(sizeof(struct HExpr_List));
    list_45->head = callee_1;
    list_45->tail = args_1;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4 tuple_87;
    tuple_87.t0 = (struct InfOp_){.tag = CallProc_};
    tuple_87.t1 = list_45;
    tuple_87.t2 = resultTy_2;
    tuple_87.t3 = loc_18;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4* payload_53 = (struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4));
    (*(((struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)payload_53))) = tuple_87;
    struct HExpr_ variant_53 = (struct HExpr_){.tag = Inf_, .Inf_ = payload_53};
    return variant_53;
}

struct HExpr_ hxCallClosure_(struct HExpr_ callee_2, struct HExpr_List* args_2, struct Ty_ resultTy_3, struct IntIntTuple2 loc_19) {
    struct HExpr_List* list_46 = (struct HExpr_List*)malloc(sizeof(struct HExpr_List));
    list_46->head = callee_2;
    list_46->tail = args_2;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4 tuple_88;
    tuple_88.t0 = (struct InfOp_){.tag = CallClosure_};
    tuple_88.t1 = list_46;
    tuple_88.t2 = resultTy_3;
    tuple_88.t3 = loc_19;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4* payload_54 = (struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4));
    (*(((struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)payload_54))) = tuple_88;
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

struct Ty_ fun_4(void* env_2, struct HExpr_ arg_12) {
    struct Ty_ arg_13 = (*(((struct Ty_Ty_Ty_Ty_Ty_Tuple5*)env_2))).t0;
    struct Ty_ arg_14 = (*(((struct Ty_Ty_Ty_Ty_Ty_Tuple5*)env_2))).t1;
    struct Ty_ arg_15 = (*(((struct Ty_Ty_Ty_Ty_Ty_Tuple5*)env_2))).t2;
    struct Ty_ arg_16 = (*(((struct Ty_Ty_Ty_Ty_Ty_Tuple5*)env_2))).t3;
    struct Ty_ arg_17 = (*(((struct Ty_Ty_Ty_Ty_Ty_Tuple5*)env_2))).t4;
    struct Ty_ call_246 = exprToTy_(arg_13, arg_14, arg_15, arg_16, arg_17, arg_12);
    return call_246;
}

struct HExpr_ hxTuple_(struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct HExpr_List* items_1, struct IntIntTuple2 loc_20) {
    struct Ty_Ty_Ty_Ty_Ty_Tuple5 tuple_90;
    tuple_90.t0 = tyUnit_;
    tuple_90.t1 = tyStr_;
    tuple_90.t2 = tyChar_;
    tuple_90.t3 = tyInt_;
    tuple_90.t4 = tyBool_;
    void* box_2 = (void*)malloc(sizeof(struct Ty_Ty_Ty_Ty_Ty_Tuple5));
    (*(((struct Ty_Ty_Ty_Ty_Ty_Tuple5*)box_2))) = tuple_90;
    void* env_31 = box_2;
    struct HExpr_Ty_Fun1 fun_33 = (struct HExpr_Ty_Fun1){.fun = fun_4, .env = env_31};
    struct Ty_List* call_247 = listMap_10(fun_33, items_1);
    struct Ty_ call_248 = tyTuple_(call_247);
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4 tuple_89;
    tuple_89.t0 = (struct InfOp_){.tag = Tuple_3};
    tuple_89.t1 = items_1;
    tuple_89.t2 = call_248;
    tuple_89.t3 = loc_20;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4* payload_55 = (struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4));
    (*(((struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)payload_55))) = tuple_89;
    struct HExpr_ variant_55 = (struct HExpr_){.tag = Inf_, .Inf_ = payload_55};
    return variant_55;
}

struct HExpr_ hxUnit_(struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct IntIntTuple2 loc_21) {
    struct HExpr_ call_249 = hxTuple_(tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, NULL, loc_21);
    return call_249;
}

struct HPrim_Ty_IntIntTuple2Tuple3 {
    struct HPrim_ t0;
    struct Ty_ t1;
    struct IntIntTuple2 t2;
};

struct HExpr_ hxNil_(struct Ty_ itemTy_10, struct IntIntTuple2 loc_22) {
    struct Ty_ call_250 = tyList_(itemTy_10);
    struct HPrim_Ty_IntIntTuple2Tuple3 tuple_91;
    tuple_91.t0 = (struct HPrim_){.tag = Nil_1};
    tuple_91.t1 = call_250;
    tuple_91.t2 = loc_22;
    struct HPrim_Ty_IntIntTuple2Tuple3* payload_56 = (struct HPrim_Ty_IntIntTuple2Tuple3*)malloc(sizeof(struct HPrim_Ty_IntIntTuple2Tuple3));
    (*(((struct HPrim_Ty_IntIntTuple2Tuple3*)payload_56))) = tuple_91;
    struct HExpr_ variant_56 = (struct HExpr_){.tag = Prim_, .Prim_ = payload_56};
    return variant_56;
}

int hxIsUnitLit_(struct HExpr_ expr_1) {
    int match_75;
    if ((expr_1.tag != Inf_)) goto next_319;
    if (((*(expr_1.Inf_)).t0.tag != Tuple_3)) goto next_319;
    if ((!((!((*(expr_1.Inf_)).t1))))) goto next_319;
    match_75 = 1;
    goto end_match_318;
next_319:;
    match_75 = 0;
    goto end_match_318;
next_320:;
end_match_318:;
    return match_75;
}

int hxIsAlwaysTrue_(struct HExpr_ expr_2) {
    int match_76;
    if ((expr_2.tag != Lit_3)) goto next_322;
    if (((*(expr_2.Lit_3)).t0.tag != Bool_)) goto next_322;
    if ((!((*((*(expr_2.Lit_3)).t0.Bool_))))) goto next_322;
    match_76 = 1;
    goto end_match_321;
next_322:;
    match_76 = 0;
    goto end_match_321;
next_323:;
end_match_321:;
    return match_76;
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
    struct Ty_IntIntTuple2Tuple2 match_77;
    if ((expr_3.tag != Lit_3)) goto next_325;
    struct Lit_ lit_3 = (*(expr_3.Lit_3)).t0;
    struct IntIntTuple2 a_22 = (*(expr_3.Lit_3)).t1;
    struct Ty_ call_251 = litToTy_(tyStr_, tyChar_, tyInt_, tyBool_, lit_3);
    struct Ty_IntIntTuple2Tuple2 tuple_92;
    tuple_92.t0 = call_251;
    tuple_92.t1 = a_22;
    match_77 = tuple_92;
    goto end_match_324;
next_325:;
    if ((expr_3.tag != Ref_2)) goto next_326;
    struct Ty_ ty_29 = (*(expr_3.Ref_2)).t1;
    struct IntIntTuple2 a_23 = (*(expr_3.Ref_2)).t2;
    struct Ty_IntIntTuple2Tuple2 tuple_93;
    tuple_93.t0 = ty_29;
    tuple_93.t1 = a_23;
    match_77 = tuple_93;
    goto end_match_324;
next_326:;
    if ((expr_3.tag != Prim_)) goto next_327;
    struct Ty_ ty_30 = (*(expr_3.Prim_)).t1;
    struct IntIntTuple2 a_24 = (*(expr_3.Prim_)).t2;
    struct Ty_IntIntTuple2Tuple2 tuple_94;
    tuple_94.t0 = ty_30;
    tuple_94.t1 = a_24;
    match_77 = tuple_94;
    goto end_match_324;
next_327:;
    if ((expr_3.tag != Match_2)) goto next_328;
    struct Ty_ ty_31 = (*(expr_3.Match_2)).t2;
    struct IntIntTuple2 a_25 = (*(expr_3.Match_2)).t3;
    struct Ty_IntIntTuple2Tuple2 tuple_95;
    tuple_95.t0 = ty_31;
    tuple_95.t1 = a_25;
    match_77 = tuple_95;
    goto end_match_324;
next_328:;
    if ((expr_3.tag != Nav_3)) goto next_329;
    struct Ty_ ty_32 = (*(expr_3.Nav_3)).t2;
    struct IntIntTuple2 a_26 = (*(expr_3.Nav_3)).t3;
    struct Ty_IntIntTuple2Tuple2 tuple_96;
    tuple_96.t0 = ty_32;
    tuple_96.t1 = a_26;
    match_77 = tuple_96;
    goto end_match_324;
next_329:;
    if ((expr_3.tag != Inf_)) goto next_330;
    struct Ty_ ty_33 = (*(expr_3.Inf_)).t2;
    struct IntIntTuple2 a_27 = (*(expr_3.Inf_)).t3;
    struct Ty_IntIntTuple2Tuple2 tuple_97;
    tuple_97.t0 = ty_33;
    tuple_97.t1 = a_27;
    match_77 = tuple_97;
    goto end_match_324;
next_330:;
    if ((expr_3.tag != Let_2)) goto next_331;
    struct Ty_ ty_34 = (*(expr_3.Let_2)).t3;
    struct IntIntTuple2 a_28 = (*(expr_3.Let_2)).t4;
    struct Ty_IntIntTuple2Tuple2 tuple_98;
    tuple_98.t0 = ty_34;
    tuple_98.t1 = a_28;
    match_77 = tuple_98;
    goto end_match_324;
next_331:;
    if ((expr_3.tag != LetFun_1)) goto next_332;
    struct Ty_ ty_35 = (*(expr_3.LetFun_1)).t5;
    struct IntIntTuple2 a_29 = (*(expr_3.LetFun_1)).t6;
    struct Ty_IntIntTuple2Tuple2 tuple_99;
    tuple_99.t0 = ty_35;
    tuple_99.t1 = a_29;
    match_77 = tuple_99;
    goto end_match_324;
next_332:;
    if ((expr_3.tag != TyDecl_)) goto next_333;
    struct IntIntTuple2 a_30 = (*(expr_3.TyDecl_)).t2;
    struct Ty_IntIntTuple2Tuple2 tuple_100;
    tuple_100.t0 = tyUnit_;
    tuple_100.t1 = a_30;
    match_77 = tuple_100;
    goto end_match_324;
next_333:;
    if ((expr_3.tag != Open_2)) goto next_334;
    struct IntIntTuple2 a_31 = (*(expr_3.Open_2)).t1;
    struct Ty_IntIntTuple2Tuple2 tuple_101;
    tuple_101.t0 = tyUnit_;
    tuple_101.t1 = a_31;
    match_77 = tuple_101;
    goto end_match_324;
next_334:;
    if ((expr_3.tag != Error_2)) goto next_335;
    struct IntIntTuple2 a_32 = (*(expr_3.Error_2)).t1;
    struct IntIntTuple2* payload_57 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_57))) = a_32;
    struct Ty_ variant_57 = (struct Ty_){.tag = Error_1, .Error_1 = payload_57};
    struct Ty_IntIntTuple2Tuple2 tuple_102;
    tuple_102.t0 = variant_57;
    tuple_102.t1 = a_32;
    match_77 = tuple_102;
    goto end_match_324;
next_335:;
    exit(1);
end_match_324:;
    return match_77;
}

struct HPat_ goPat_(struct IntIntTuple2IntIntTuple2Fun1 g_1, struct Ty_Ty_Fun1 f_9, struct HPat_ pat_7) {
    struct HPat_ call_252 = patMap_(f_9, g_1, pat_7);
    return call_252;
}

struct HPat_HExpr_HExpr_Tuple3 fun_(struct IntIntTuple2IntIntTuple2Fun1 g_1, struct Ty_Ty_Fun1 f_9, struct HPat_HExpr_HExpr_Tuple3 arg_93) {
    struct HPat_ pat_8 = arg_93.t0;
    struct HExpr_ guard_ = arg_93.t1;
    struct HExpr_ body_ = arg_93.t2;
    struct HPat_ call_253 = goPat_(g_1, f_9, pat_8);
    struct HExpr_ call_254 = go_26(g_1, f_9, guard_);
    struct HExpr_ call_255 = go_26(g_1, f_9, body_);
    struct HPat_HExpr_HExpr_Tuple3 tuple_103;
    tuple_103.t0 = call_253;
    tuple_103.t1 = call_254;
    tuple_103.t2 = call_255;
    return tuple_103;
}

struct HPat_HExpr_HExpr_Tuple3 fun_5(void* env_3, struct HPat_HExpr_HExpr_Tuple3 arg_18) {
    struct IntIntTuple2IntIntTuple2Fun1 arg_19 = (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)env_3))).t0;
    struct Ty_Ty_Fun1 arg_20 = (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)env_3))).t1;
    struct HPat_HExpr_HExpr_Tuple3 call_256 = fun_(arg_19, arg_20, arg_18);
    return call_256;
}

struct HExpr_ fun_6(void* env_4, struct HExpr_ arg_21) {
    struct IntIntTuple2IntIntTuple2Fun1 arg_22 = (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)env_4))).t0;
    struct Ty_Ty_Fun1 arg_23 = (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)env_4))).t1;
    struct HExpr_ call_257 = go_26(arg_22, arg_23, arg_21);
    return call_257;
}

struct HPat_ fun_7(void* env_5, struct HPat_ arg_24) {
    struct IntIntTuple2IntIntTuple2Fun1 arg_25 = (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)env_5))).t0;
    struct Ty_Ty_Fun1 arg_26 = (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)env_5))).t1;
    struct HPat_ call_258 = goPat_(arg_25, arg_26, arg_24);
    return call_258;
}

struct HExpr_ go_26(struct IntIntTuple2IntIntTuple2Fun1 g_1, struct Ty_Ty_Fun1 f_9, struct HExpr_ expr_5) {
    struct HExpr_ match_78;
    if ((expr_5.tag != Lit_3)) goto next_337;
    struct Lit_ lit_4 = (*(expr_5.Lit_3)).t0;
    struct IntIntTuple2 a_33 = (*(expr_5.Lit_3)).t1;
    struct IntIntTuple2 app_44 = g_1.fun(g_1.env, a_33);
    struct Lit_IntIntTuple2Tuple2 tuple_104;
    tuple_104.t0 = lit_4;
    tuple_104.t1 = app_44;
    struct Lit_IntIntTuple2Tuple2* payload_58 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_58))) = tuple_104;
    struct HExpr_ variant_58 = (struct HExpr_){.tag = Lit_3, .Lit_3 = payload_58};
    match_78 = variant_58;
    goto end_match_336;
next_337:;
    if ((expr_5.tag != Ref_2)) goto next_338;
    int serial_5 = (*(expr_5.Ref_2)).t0;
    struct Ty_ ty_36 = (*(expr_5.Ref_2)).t1;
    struct IntIntTuple2 a_34 = (*(expr_5.Ref_2)).t2;
    struct Ty_ app_45 = f_9.fun(f_9.env, ty_36);
    struct IntIntTuple2 app_46 = g_1.fun(g_1.env, a_34);
    struct IntTy_IntIntTuple2Tuple3 tuple_105;
    tuple_105.t0 = serial_5;
    tuple_105.t1 = app_45;
    tuple_105.t2 = app_46;
    struct IntTy_IntIntTuple2Tuple3* payload_59 = (struct IntTy_IntIntTuple2Tuple3*)malloc(sizeof(struct IntTy_IntIntTuple2Tuple3));
    (*(((struct IntTy_IntIntTuple2Tuple3*)payload_59))) = tuple_105;
    struct HExpr_ variant_59 = (struct HExpr_){.tag = Ref_2, .Ref_2 = payload_59};
    match_78 = variant_59;
    goto end_match_336;
next_338:;
    if ((expr_5.tag != Prim_)) goto next_339;
    struct HPrim_ prim_1 = (*(expr_5.Prim_)).t0;
    struct Ty_ ty_37 = (*(expr_5.Prim_)).t1;
    struct IntIntTuple2 a_35 = (*(expr_5.Prim_)).t2;
    struct Ty_ app_47 = f_9.fun(f_9.env, ty_37);
    struct IntIntTuple2 app_48 = g_1.fun(g_1.env, a_35);
    struct HPrim_Ty_IntIntTuple2Tuple3 tuple_106;
    tuple_106.t0 = prim_1;
    tuple_106.t1 = app_47;
    tuple_106.t2 = app_48;
    struct HPrim_Ty_IntIntTuple2Tuple3* payload_60 = (struct HPrim_Ty_IntIntTuple2Tuple3*)malloc(sizeof(struct HPrim_Ty_IntIntTuple2Tuple3));
    (*(((struct HPrim_Ty_IntIntTuple2Tuple3*)payload_60))) = tuple_106;
    struct HExpr_ variant_60 = (struct HExpr_){.tag = Prim_, .Prim_ = payload_60};
    match_78 = variant_60;
    goto end_match_336;
next_339:;
    if ((expr_5.tag != Match_2)) goto next_340;
    struct HExpr_ target_ = (*(expr_5.Match_2)).t0;
    struct HPat_HExpr_HExpr_Tuple3List* arms_ = (*(expr_5.Match_2)).t1;
    struct Ty_ ty_38 = (*(expr_5.Match_2)).t2;
    struct IntIntTuple2 a_36 = (*(expr_5.Match_2)).t3;
    struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2 tuple_107;
    tuple_107.t0 = g_1;
    tuple_107.t1 = f_9;
    void* box_3 = (void*)malloc(sizeof(struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2));
    (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)box_3))) = tuple_107;
    void* env_32 = box_3;
    struct HPat_HExpr_HExpr_Tuple3HPat_HExpr_HExpr_Tuple3Fun1 fun_34 = (struct HPat_HExpr_HExpr_Tuple3HPat_HExpr_HExpr_Tuple3Fun1){.fun = fun_5, .env = env_32};
    struct HPat_HExpr_HExpr_Tuple3List* call_259 = listMap_9(fun_34, arms_);
    struct HPat_HExpr_HExpr_Tuple3List* arms_1 = call_259;
    struct HExpr_ call_260 = go_26(g_1, f_9, target_);
    struct Ty_ app_49 = f_9.fun(f_9.env, ty_38);
    struct IntIntTuple2 app_50 = g_1.fun(g_1.env, a_36);
    struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4 tuple_108;
    tuple_108.t0 = call_260;
    tuple_108.t1 = arms_1;
    tuple_108.t2 = app_49;
    tuple_108.t3 = app_50;
    struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4* payload_61 = (struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4));
    (*(((struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4*)payload_61))) = tuple_108;
    struct HExpr_ variant_61 = (struct HExpr_){.tag = Match_2, .Match_2 = payload_61};
    match_78 = variant_61;
    goto end_match_336;
next_340:;
    if ((expr_5.tag != Nav_3)) goto next_341;
    struct HExpr_ sub_ = (*(expr_5.Nav_3)).t0;
    struct String mes_ = (*(expr_5.Nav_3)).t1;
    struct Ty_ ty_39 = (*(expr_5.Nav_3)).t2;
    struct IntIntTuple2 a_37 = (*(expr_5.Nav_3)).t3;
    struct HExpr_ call_261 = go_26(g_1, f_9, sub_);
    struct Ty_ app_51 = f_9.fun(f_9.env, ty_39);
    struct IntIntTuple2 app_52 = g_1.fun(g_1.env, a_37);
    struct HExpr_StringTy_IntIntTuple2Tuple4 tuple_109;
    tuple_109.t0 = call_261;
    tuple_109.t1 = mes_;
    tuple_109.t2 = app_51;
    tuple_109.t3 = app_52;
    struct HExpr_StringTy_IntIntTuple2Tuple4* payload_62 = (struct HExpr_StringTy_IntIntTuple2Tuple4*)malloc(sizeof(struct HExpr_StringTy_IntIntTuple2Tuple4));
    (*(((struct HExpr_StringTy_IntIntTuple2Tuple4*)payload_62))) = tuple_109;
    struct HExpr_ variant_62 = (struct HExpr_){.tag = Nav_3, .Nav_3 = payload_62};
    match_78 = variant_62;
    goto end_match_336;
next_341:;
    if ((expr_5.tag != Inf_)) goto next_342;
    struct InfOp_ infOp_ = (*(expr_5.Inf_)).t0;
    struct HExpr_List* args_3 = (*(expr_5.Inf_)).t1;
    struct Ty_ resultTy_4 = (*(expr_5.Inf_)).t2;
    struct IntIntTuple2 a_38 = (*(expr_5.Inf_)).t3;
    struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2 tuple_111;
    tuple_111.t0 = g_1;
    tuple_111.t1 = f_9;
    void* box_4 = (void*)malloc(sizeof(struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2));
    (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)box_4))) = tuple_111;
    void* env_33 = box_4;
    struct HExpr_HExpr_Fun1 fun_35 = (struct HExpr_HExpr_Fun1){.fun = fun_6, .env = env_33};
    struct HExpr_List* call_262 = listMap_8(fun_35, args_3);
    struct Ty_ app_53 = f_9.fun(f_9.env, resultTy_4);
    struct IntIntTuple2 app_54 = g_1.fun(g_1.env, a_38);
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4 tuple_110;
    tuple_110.t0 = infOp_;
    tuple_110.t1 = call_262;
    tuple_110.t2 = app_53;
    tuple_110.t3 = app_54;
    struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4* payload_63 = (struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4));
    (*(((struct InfOp_HExpr_ListTy_IntIntTuple2Tuple4*)payload_63))) = tuple_110;
    struct HExpr_ variant_63 = (struct HExpr_){.tag = Inf_, .Inf_ = payload_63};
    match_78 = variant_63;
    goto end_match_336;
next_342:;
    if ((expr_5.tag != Let_2)) goto next_343;
    struct HPat_ pat_9 = (*(expr_5.Let_2)).t0;
    struct HExpr_ init_ = (*(expr_5.Let_2)).t1;
    struct HExpr_ next_6 = (*(expr_5.Let_2)).t2;
    struct Ty_ ty_40 = (*(expr_5.Let_2)).t3;
    struct IntIntTuple2 a_39 = (*(expr_5.Let_2)).t4;
    struct HPat_ call_263 = goPat_(g_1, f_9, pat_9);
    struct HExpr_ call_264 = go_26(g_1, f_9, init_);
    struct HExpr_ call_265 = go_26(g_1, f_9, next_6);
    struct Ty_ app_55 = f_9.fun(f_9.env, ty_40);
    struct IntIntTuple2 app_56 = g_1.fun(g_1.env, a_39);
    struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5 tuple_112;
    tuple_112.t0 = call_263;
    tuple_112.t1 = call_264;
    tuple_112.t2 = call_265;
    tuple_112.t3 = app_55;
    tuple_112.t4 = app_56;
    struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5* payload_64 = (struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5*)malloc(sizeof(struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5));
    (*(((struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5*)payload_64))) = tuple_112;
    struct HExpr_ variant_64 = (struct HExpr_){.tag = Let_2, .Let_2 = payload_64};
    match_78 = variant_64;
    goto end_match_336;
next_343:;
    if ((expr_5.tag != LetFun_1)) goto next_344;
    int serial_6 = (*(expr_5.LetFun_1)).t0;
    int isMainFun_ = (*(expr_5.LetFun_1)).t1;
    struct HPat_List* args_4 = (*(expr_5.LetFun_1)).t2;
    struct HExpr_ body_1 = (*(expr_5.LetFun_1)).t3;
    struct HExpr_ next_7 = (*(expr_5.LetFun_1)).t4;
    struct Ty_ ty_41 = (*(expr_5.LetFun_1)).t5;
    struct IntIntTuple2 a_40 = (*(expr_5.LetFun_1)).t6;
    struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2 tuple_114;
    tuple_114.t0 = g_1;
    tuple_114.t1 = f_9;
    void* box_5 = (void*)malloc(sizeof(struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2));
    (*(((struct IntIntTuple2IntIntTuple2Fun1Ty_Ty_Fun1Tuple2*)box_5))) = tuple_114;
    void* env_34 = box_5;
    struct HPat_HPat_Fun1 fun_36 = (struct HPat_HPat_Fun1){.fun = fun_7, .env = env_34};
    struct HPat_List* call_266 = listMap_7(fun_36, args_4);
    struct HExpr_ call_267 = go_26(g_1, f_9, body_1);
    struct HExpr_ call_268 = go_26(g_1, f_9, next_7);
    struct Ty_ app_57 = f_9.fun(f_9.env, ty_41);
    struct IntIntTuple2 app_58 = g_1.fun(g_1.env, a_40);
    struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7 tuple_113;
    tuple_113.t0 = serial_6;
    tuple_113.t1 = isMainFun_;
    tuple_113.t2 = call_266;
    tuple_113.t3 = call_267;
    tuple_113.t4 = call_268;
    tuple_113.t5 = app_57;
    tuple_113.t6 = app_58;
    struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7* payload_65 = (struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7*)malloc(sizeof(struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7));
    (*(((struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7*)payload_65))) = tuple_113;
    struct HExpr_ variant_65 = (struct HExpr_){.tag = LetFun_1, .LetFun_1 = payload_65};
    match_78 = variant_65;
    goto end_match_336;
next_344:;
    if ((expr_5.tag != TyDecl_)) goto next_345;
    int serial_7 = (*(expr_5.TyDecl_)).t0;
    struct TyDecl_ tyDef_1 = (*(expr_5.TyDecl_)).t1;
    struct IntIntTuple2 a_41 = (*(expr_5.TyDecl_)).t2;
    struct IntIntTuple2 app_59 = g_1.fun(g_1.env, a_41);
    struct IntTyDecl_IntIntTuple2Tuple3 tuple_115;
    tuple_115.t0 = serial_7;
    tuple_115.t1 = tyDef_1;
    tuple_115.t2 = app_59;
    struct IntTyDecl_IntIntTuple2Tuple3* payload_66 = (struct IntTyDecl_IntIntTuple2Tuple3*)malloc(sizeof(struct IntTyDecl_IntIntTuple2Tuple3));
    (*(((struct IntTyDecl_IntIntTuple2Tuple3*)payload_66))) = tuple_115;
    struct HExpr_ variant_66 = (struct HExpr_){.tag = TyDecl_, .TyDecl_ = payload_66};
    match_78 = variant_66;
    goto end_match_336;
next_345:;
    if ((expr_5.tag != Open_2)) goto next_346;
    struct StringList* path_ = (*(expr_5.Open_2)).t0;
    struct IntIntTuple2 a_42 = (*(expr_5.Open_2)).t1;
    struct IntIntTuple2 app_60 = g_1.fun(g_1.env, a_42);
    struct StringListIntIntTuple2Tuple2 tuple_116;
    tuple_116.t0 = path_;
    tuple_116.t1 = app_60;
    struct StringListIntIntTuple2Tuple2* payload_67 = (struct StringListIntIntTuple2Tuple2*)malloc(sizeof(struct StringListIntIntTuple2Tuple2));
    (*(((struct StringListIntIntTuple2Tuple2*)payload_67))) = tuple_116;
    struct HExpr_ variant_67 = (struct HExpr_){.tag = Open_2, .Open_2 = payload_67};
    match_78 = variant_67;
    goto end_match_336;
next_346:;
    if ((expr_5.tag != Error_2)) goto next_347;
    struct String error_ = (*(expr_5.Error_2)).t0;
    struct IntIntTuple2 a_43 = (*(expr_5.Error_2)).t1;
    struct IntIntTuple2 app_61 = g_1.fun(g_1.env, a_43);
    struct StringIntIntTuple2Tuple2 tuple_117;
    tuple_117.t0 = error_;
    tuple_117.t1 = app_61;
    struct StringIntIntTuple2Tuple2* payload_68 = (struct StringIntIntTuple2Tuple2*)malloc(sizeof(struct StringIntIntTuple2Tuple2));
    (*(((struct StringIntIntTuple2Tuple2*)payload_68))) = tuple_117;
    struct HExpr_ variant_68 = (struct HExpr_){.tag = Error_2, .Error_2 = payload_68};
    match_78 = variant_68;
    goto end_match_336;
next_347:;
    exit(1);
end_match_336:;
    return match_78;
}

struct HExpr_ exprMap_(struct Ty_Ty_Fun1 f_9, struct IntIntTuple2IntIntTuple2Fun1 g_1, struct HExpr_ expr_4) {
    struct HExpr_ call_269 = go_26(g_1, f_9, expr_4);
    return call_269;
}

struct Ty_ exprToTy_(struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct HExpr_ expr_6) {
    struct Ty_IntIntTuple2Tuple2 call_270 = exprExtract_(tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, expr_6);
    struct Ty_ ty_42 = call_270.t0;
    return ty_42;
}

struct IntIntTuple2 go_(int r_, struct String text_, int y_1, int x_2, int i_) {
    struct IntIntTuple2 match_79;
    if ((i_ != r_)) goto next_349;
    struct IntIntTuple2 tuple_118;
    tuple_118.t0 = y_1;
    tuple_118.t1 = x_2;
    match_79 = tuple_118;
    goto end_match_348;
next_349:;
    if ((i_ == r_)) goto next_350;
    struct IntIntTuple2 match_80;
    if ((text_.str[i_] != '\n')) goto next_352;
    struct IntIntTuple2 call_271 = go_(r_, text_, (y_1 + 1), 0, (i_ + 1));
    match_80 = call_271;
    goto end_match_351;
next_352:;
    if ((text_.str[i_] == '\n')) goto next_353;
    struct IntIntTuple2 call_272 = go_(r_, text_, y_1, (x_2 + 1), (i_ + 1));
    match_80 = call_272;
    goto end_match_351;
next_353:;
    exit(1);
end_match_351:;
    match_79 = match_80;
    goto end_match_348;
next_350:;
    exit(1);
end_match_348:;
    return match_79;
}

struct IntIntTuple2 locShift_(struct String text_, int l_, int r_, struct IntIntTuple2 arg_94) {
    int y_ = arg_94.t0;
    int x_1 = arg_94.t1;
    int match_81;
    int match_82;
    if ((l_ < 0)) goto next_356;
    match_82 = (r_ >= l_);
    goto end_match_355;
next_356:;
    if ((l_ >= 0)) goto next_357;
    match_82 = 0;
    goto end_match_355;
next_357:;
    exit(1);
end_match_355:;
    if ((!(match_82))) goto next_358;
    match_81 = (text_.len >= r_);
    goto end_match_354;
next_358:;
    if (match_82) goto next_359;
    match_81 = 0;
    goto end_match_354;
next_359:;
    exit(1);
end_match_354:;
    milone_assert(match_81, 40, 2);
    int call_273 = 0;
    struct IntIntTuple2 call_274 = go_(r_, text_, y_, x_1, l_);
    return call_274;
}

int charIsSpace_(char c_) {
    int match_83;
    int match_84;
    int match_85;
    if ((c_ != ' ')) goto next_363;
    match_85 = 1;
    goto end_match_362;
next_363:;
    if ((c_ == ' ')) goto next_364;
    match_85 = (c_ == '\t');
    goto end_match_362;
next_364:;
    exit(1);
end_match_362:;
    if ((!(match_85))) goto next_365;
    match_84 = 1;
    goto end_match_361;
next_365:;
    if (match_85) goto next_366;
    match_84 = (c_ == '\r');
    goto end_match_361;
next_366:;
    exit(1);
end_match_361:;
    if ((!(match_84))) goto next_367;
    match_83 = 1;
    goto end_match_360;
next_367:;
    if (match_84) goto next_368;
    match_83 = (c_ == '\n');
    goto end_match_360;
next_368:;
    exit(1);
end_match_360:;
    return match_83;
}

int charIsDigit_(char c_1) {
    int match_86;
    if ((c_1 < '0')) goto next_370;
    match_86 = ('9' >= c_1);
    goto end_match_369;
next_370:;
    if ((c_1 >= '0')) goto next_371;
    match_86 = 0;
    goto end_match_369;
next_371:;
    exit(1);
end_match_369:;
    return match_86;
}

int charIsAlpha_(char c_2) {
    int match_87;
    int match_88;
    if ((c_2 < 'a')) goto next_374;
    match_88 = ('z' >= c_2);
    goto end_match_373;
next_374:;
    if ((c_2 >= 'a')) goto next_375;
    match_88 = 0;
    goto end_match_373;
next_375:;
    exit(1);
end_match_373:;
    if ((!(match_88))) goto next_376;
    match_87 = 1;
    goto end_match_372;
next_376:;
    if (match_88) goto next_377;
    int match_89;
    if ((c_2 < 'A')) goto next_379;
    match_89 = ('Z' >= c_2);
    goto end_match_378;
next_379:;
    if ((c_2 >= 'A')) goto next_380;
    match_89 = 0;
    goto end_match_378;
next_380:;
    exit(1);
end_match_378:;
    match_87 = match_89;
    goto end_match_372;
next_377:;
    exit(1);
end_match_372:;
    return match_87;
}

int charIsIdent_(char c_3) {
    int match_90;
    int match_91;
    if ((c_3 != '_')) goto next_383;
    match_91 = 1;
    goto end_match_382;
next_383:;
    if ((c_3 == '_')) goto next_384;
    int call_275 = charIsDigit_(c_3);
    match_91 = call_275;
    goto end_match_382;
next_384:;
    exit(1);
end_match_382:;
    if ((!(match_91))) goto next_385;
    match_90 = 1;
    goto end_match_381;
next_385:;
    if (match_91) goto next_386;
    int call_276 = charIsAlpha_(c_3);
    match_90 = call_276;
    goto end_match_381;
next_386:;
    exit(1);
end_match_381:;
    return match_90;
}

int charIsOp_(char c_4) {
    int match_92;
    int match_93;
    int match_94;
    int match_95;
    int match_96;
    int match_97;
    int match_98;
    int match_99;
    int match_100;
    int match_101;
    int match_102;
    int match_103;
    int match_104;
    int match_105;
    if ((c_4 != '+')) goto next_401;
    match_105 = 1;
    goto end_match_400;
next_401:;
    if ((c_4 == '+')) goto next_402;
    match_105 = (c_4 == '-');
    goto end_match_400;
next_402:;
    exit(1);
end_match_400:;
    if ((!(match_105))) goto next_403;
    match_104 = 1;
    goto end_match_399;
next_403:;
    if (match_105) goto next_404;
    match_104 = (c_4 == '*');
    goto end_match_399;
next_404:;
    exit(1);
end_match_399:;
    if ((!(match_104))) goto next_405;
    match_103 = 1;
    goto end_match_398;
next_405:;
    if (match_104) goto next_406;
    match_103 = (c_4 == '/');
    goto end_match_398;
next_406:;
    exit(1);
end_match_398:;
    if ((!(match_103))) goto next_407;
    match_102 = 1;
    goto end_match_397;
next_407:;
    if (match_103) goto next_408;
    match_102 = (c_4 == '%');
    goto end_match_397;
next_408:;
    exit(1);
end_match_397:;
    if ((!(match_102))) goto next_409;
    match_101 = 1;
    goto end_match_396;
next_409:;
    if (match_102) goto next_410;
    match_101 = (c_4 == '=');
    goto end_match_396;
next_410:;
    exit(1);
end_match_396:;
    if ((!(match_101))) goto next_411;
    match_100 = 1;
    goto end_match_395;
next_411:;
    if (match_101) goto next_412;
    match_100 = (c_4 == '<');
    goto end_match_395;
next_412:;
    exit(1);
end_match_395:;
    if ((!(match_100))) goto next_413;
    match_99 = 1;
    goto end_match_394;
next_413:;
    if (match_100) goto next_414;
    match_99 = (c_4 == '>');
    goto end_match_394;
next_414:;
    exit(1);
end_match_394:;
    if ((!(match_99))) goto next_415;
    match_98 = 1;
    goto end_match_393;
next_415:;
    if (match_99) goto next_416;
    match_98 = (c_4 == '^');
    goto end_match_393;
next_416:;
    exit(1);
end_match_393:;
    if ((!(match_98))) goto next_417;
    match_97 = 1;
    goto end_match_392;
next_417:;
    if (match_98) goto next_418;
    match_97 = (c_4 == '&');
    goto end_match_392;
next_418:;
    exit(1);
end_match_392:;
    if ((!(match_97))) goto next_419;
    match_96 = 1;
    goto end_match_391;
next_419:;
    if (match_97) goto next_420;
    match_96 = (c_4 == '|');
    goto end_match_391;
next_420:;
    exit(1);
end_match_391:;
    if ((!(match_96))) goto next_421;
    match_95 = 1;
    goto end_match_390;
next_421:;
    if (match_96) goto next_422;
    match_95 = (c_4 == ':');
    goto end_match_390;
next_422:;
    exit(1);
end_match_390:;
    if ((!(match_95))) goto next_423;
    match_94 = 1;
    goto end_match_389;
next_423:;
    if (match_95) goto next_424;
    match_94 = (c_4 == '@');
    goto end_match_389;
next_424:;
    exit(1);
end_match_389:;
    if ((!(match_94))) goto next_425;
    match_93 = 1;
    goto end_match_388;
next_425:;
    if (match_94) goto next_426;
    match_93 = (c_4 == ';');
    goto end_match_388;
next_426:;
    exit(1);
end_match_388:;
    if ((!(match_93))) goto next_427;
    match_92 = 1;
    goto end_match_387;
next_427:;
    if (match_93) goto next_428;
    match_92 = (c_4 == '.');
    goto end_match_387;
next_428:;
    exit(1);
end_match_387:;
    return match_92;
}

int charIsPun_(char c_5) {
    int match_106;
    int match_107;
    int match_108;
    int match_109;
    if ((c_5 != ',')) goto next_433;
    match_109 = 1;
    goto end_match_432;
next_433:;
    if ((c_5 == ',')) goto next_434;
    match_109 = (c_5 == '(');
    goto end_match_432;
next_434:;
    exit(1);
end_match_432:;
    if ((!(match_109))) goto next_435;
    match_108 = 1;
    goto end_match_431;
next_435:;
    if (match_109) goto next_436;
    match_108 = (c_5 == ')');
    goto end_match_431;
next_436:;
    exit(1);
end_match_431:;
    if ((!(match_108))) goto next_437;
    match_107 = 1;
    goto end_match_430;
next_437:;
    if (match_108) goto next_438;
    match_107 = (c_5 == '[');
    goto end_match_430;
next_438:;
    exit(1);
end_match_430:;
    if ((!(match_107))) goto next_439;
    match_106 = 1;
    goto end_match_429;
next_439:;
    if (match_107) goto next_440;
    match_106 = (c_5 == ']');
    goto end_match_429;
next_440:;
    exit(1);
end_match_429:;
    return match_106;
}

int go_1(struct String s_, struct String prefix_, int pi_, int si_) {
    int match_110;
    if ((pi_ != prefix_.len)) goto next_442;
    match_110 = 1;
    goto end_match_441;
next_442:;
    if ((pi_ == prefix_.len)) goto next_443;
    int match_111;
    int match_112;
    if ((si_ >= s_.len)) goto next_446;
    match_112 = (prefix_.str[pi_] == s_.str[si_]);
    goto end_match_445;
next_446:;
    if ((si_ < s_.len)) goto next_447;
    match_112 = 0;
    goto end_match_445;
next_447:;
    exit(1);
end_match_445:;
    if ((!(match_112))) goto next_448;
    int call_277 = go_1(s_, prefix_, (pi_ + 1), (si_ + 1));
    match_111 = call_277;
    goto end_match_444;
next_448:;
    if (match_112) goto next_449;
    match_111 = 0;
    goto end_match_444;
next_449:;
    exit(1);
end_match_444:;
    match_110 = match_111;
    goto end_match_441;
next_443:;
    exit(1);
end_match_441:;
    return match_110;
}

int strIsFollowedBy_(int i_1, struct String prefix_, struct String s_) {
    int match_113;
    if ((s_.len < (i_1 + prefix_.len))) goto next_451;
    int call_278 = go_1(s_, prefix_, 0, i_1);
    match_113 = call_278;
    goto end_match_450;
next_451:;
    if ((s_.len >= (i_1 + prefix_.len))) goto next_452;
    match_113 = 0;
    goto end_match_450;
next_452:;
    exit(1);
end_match_450:;
    return match_113;
}

int strIsFollowedByRawQuotes_(int i_2, struct String s_1) {
    int call_279 = strIsFollowedBy_(i_2, (struct String){.str = "\"\"\"", .len = 3}, s_1);
    return call_279;
}

int scanError_(struct String arg_95, int i_3) {
    return (i_3 + 1);
}

int lookEof_(struct String text_1, int i_4) {
    return (i_4 >= text_1.len);
}

int lookSpace_(struct String text_2, int i_5) {
    int call_280 = charIsSpace_(text_2.str[i_5]);
    return call_280;
}

int go_2(struct String text_3, int i_7) {
    int match_114;
    int match_115;
    if ((i_7 >= text_3.len)) goto next_455;
    int call_281 = charIsSpace_(text_3.str[i_7]);
    match_115 = call_281;
    goto end_match_454;
next_455:;
    if ((i_7 < text_3.len)) goto next_456;
    match_115 = 0;
    goto end_match_454;
next_456:;
    exit(1);
end_match_454:;
    if ((!(match_115))) goto next_457;
    int call_282 = go_2(text_3, (i_7 + 1));
    match_114 = call_282;
    goto end_match_453;
next_457:;
    if (match_115) goto next_458;
    match_114 = i_7;
    goto end_match_453;
next_458:;
    exit(1);
end_match_453:;
    return match_114;
}

int scanSpace_(struct String text_3, int i_6) {
    int call_283 = lookSpace_(text_3, i_6);
    milone_assert(call_283, 112, 2);
    int call_284 = 0;
    int call_285 = go_2(text_3, i_6);
    return call_285;
}

int lookComment_(struct String text_4, int i_8) {
    int match_116;
    int call_286 = strIsFollowedBy_(i_8, (struct String){.str = "//", .len = 2}, text_4);
    if ((!(call_286))) goto next_460;
    match_116 = 1;
    goto end_match_459;
next_460:;
    if (call_286) goto next_461;
    int call_287 = strIsFollowedBy_(i_8, (struct String){.str = "[<", .len = 2}, text_4);
    match_116 = call_287;
    goto end_match_459;
next_461:;
    exit(1);
end_match_459:;
    return match_116;
}

int go_3(struct String text_5, int i_10) {
    int match_117;
    if ((i_10 != text_5.len)) goto next_463;
    match_117 = i_10;
    goto end_match_462;
next_463:;
    if ((i_10 == text_5.len)) goto next_464;
    int match_118;
    if ((text_5.str[i_10] != '\n')) goto next_466;
    match_118 = (i_10 + 1);
    goto end_match_465;
next_466:;
    if ((text_5.str[i_10] == '\n')) goto next_467;
    int call_288 = go_3(text_5, (i_10 + 1));
    match_118 = call_288;
    goto end_match_465;
next_467:;
    exit(1);
end_match_465:;
    match_117 = match_118;
    goto end_match_462;
next_464:;
    exit(1);
end_match_462:;
    return match_117;
}

int scanLine_(struct String text_5, int i_9) {
    int call_289 = lookComment_(text_5, i_9);
    milone_assert(call_289, 126, 2);
    int call_290 = 0;
    int call_291 = go_3(text_5, i_9);
    return call_291;
}

int lookPun_(struct String text_6, int i_11) {
    int call_292 = charIsPun_(text_6.str[i_11]);
    return call_292;
}

int scanPun_(struct String text_7, int i_12) {
    int call_293 = lookPun_(text_7, i_12);
    milone_assert(call_293, 140, 2);
    int call_294 = 0;
    return (i_12 + 1);
}

int lookOp_(struct String text_8, int i_13) {
    int call_295 = charIsOp_(text_8.str[i_13]);
    return call_295;
}

int go_4(struct String text_9, int i_15) {
    int match_119;
    int match_120;
    if ((i_15 >= text_9.len)) goto next_470;
    int call_296 = charIsOp_(text_9.str[i_15]);
    match_120 = call_296;
    goto end_match_469;
next_470:;
    if ((i_15 < text_9.len)) goto next_471;
    match_120 = 0;
    goto end_match_469;
next_471:;
    exit(1);
end_match_469:;
    if ((!(match_120))) goto next_472;
    int call_297 = go_4(text_9, (i_15 + 1));
    match_119 = call_297;
    goto end_match_468;
next_472:;
    if (match_120) goto next_473;
    match_119 = i_15;
    goto end_match_468;
next_473:;
    exit(1);
end_match_468:;
    return match_119;
}

int scanOp_(struct String text_9, int i_14) {
    int call_298 = lookOp_(text_9, i_14);
    milone_assert(call_298, 147, 2);
    int call_299 = 0;
    int call_300 = go_4(text_9, i_14);
    return call_300;
}

int lookIdent_(struct String text_10, int i_16) {
    int match_121;
    int call_301 = charIsIdent_(text_10.str[i_16]);
    if ((!(call_301))) goto next_475;
    int call_302 = charIsDigit_(text_10.str[i_16]);
    match_121 = (!(call_302));
    goto end_match_474;
next_475:;
    if (call_301) goto next_476;
    match_121 = 0;
    goto end_match_474;
next_476:;
    exit(1);
end_match_474:;
    return match_121;
}

int go_5(struct String text_11, int i_18) {
    int match_122;
    int match_123;
    if ((i_18 >= text_11.len)) goto next_479;
    int call_303 = charIsIdent_(text_11.str[i_18]);
    match_123 = call_303;
    goto end_match_478;
next_479:;
    if ((i_18 < text_11.len)) goto next_480;
    match_123 = 0;
    goto end_match_478;
next_480:;
    exit(1);
end_match_478:;
    if ((!(match_123))) goto next_481;
    int call_304 = go_5(text_11, (i_18 + 1));
    match_122 = call_304;
    goto end_match_477;
next_481:;
    if (match_123) goto next_482;
    match_122 = i_18;
    goto end_match_477;
next_482:;
    exit(1);
end_match_477:;
    return match_122;
}

int scanIdent_(struct String text_11, int i_17) {
    int call_305 = lookIdent_(text_11, i_17);
    milone_assert(call_305, 160, 2);
    int call_306 = 0;
    int call_307 = go_5(text_11, i_17);
    return call_307;
}

int lookIntLit_(struct String text_12, int i_19) {
    int call_308 = charIsDigit_(text_12.str[i_19]);
    return call_308;
}

int go_6(struct String text_13, int i_21) {
    int match_124;
    int match_125;
    if ((i_21 >= text_13.len)) goto next_485;
    int call_309 = charIsDigit_(text_13.str[i_21]);
    match_125 = call_309;
    goto end_match_484;
next_485:;
    if ((i_21 < text_13.len)) goto next_486;
    match_125 = 0;
    goto end_match_484;
next_486:;
    exit(1);
end_match_484:;
    if ((!(match_125))) goto next_487;
    int call_310 = go_6(text_13, (i_21 + 1));
    match_124 = call_310;
    goto end_match_483;
next_487:;
    if (match_125) goto next_488;
    match_124 = i_21;
    goto end_match_483;
next_488:;
    exit(1);
end_match_483:;
    return match_124;
}

int scanIntLit_(struct String text_13, int i_20) {
    int call_311 = lookIntLit_(text_13, i_20);
    milone_assert(call_311, 172, 2);
    int call_312 = 0;
    int call_313 = go_6(text_13, i_20);
    return call_313;
}

int lookCharLit_(struct String text_14, int i_22) {
    return (text_14.str[i_22] == '\'');
}

struct BoolIntTuple2 {
    int t0;
    int t1;
};

struct BoolIntTuple2 go_7(struct String text_15, int i_24) {
    struct BoolIntTuple2 match_126;
    int match_127;
    if (((i_24 + 1) >= text_15.len)) goto next_491;
    match_127 = (text_15.str[i_24] == '\\');
    goto end_match_490;
next_491:;
    if (((i_24 + 1) < text_15.len)) goto next_492;
    match_127 = 0;
    goto end_match_490;
next_492:;
    exit(1);
end_match_490:;
    if ((!(match_127))) goto next_493;
    struct BoolIntTuple2 call_314 = go_7(text_15, (i_24 + 2));
    match_126 = call_314;
    goto end_match_489;
next_493:;
    if (match_127) goto next_494;
    struct BoolIntTuple2 match_128;
    int match_129;
    if ((i_24 >= text_15.len)) goto next_497;
    match_129 = (text_15.str[i_24] == '\'');
    goto end_match_496;
next_497:;
    if ((i_24 < text_15.len)) goto next_498;
    match_129 = 0;
    goto end_match_496;
next_498:;
    exit(1);
end_match_496:;
    if ((!(match_129))) goto next_499;
    struct BoolIntTuple2 tuple_119;
    tuple_119.t0 = 1;
    tuple_119.t1 = (i_24 + 1);
    match_128 = tuple_119;
    goto end_match_495;
next_499:;
    if (match_129) goto next_500;
    struct BoolIntTuple2 match_130;
    int match_131;
    if ((i_24 >= text_15.len)) goto next_503;
    match_131 = (text_15.str[i_24] != '\n');
    goto end_match_502;
next_503:;
    if ((i_24 < text_15.len)) goto next_504;
    match_131 = 0;
    goto end_match_502;
next_504:;
    exit(1);
end_match_502:;
    if ((!(match_131))) goto next_505;
    struct BoolIntTuple2 call_315 = go_7(text_15, (i_24 + 1));
    match_130 = call_315;
    goto end_match_501;
next_505:;
    if (match_131) goto next_506;
    int match_132;
    if ((i_24 != text_15.len)) goto next_508;
    match_132 = 1;
    goto end_match_507;
next_508:;
    if ((i_24 == text_15.len)) goto next_509;
    match_132 = (text_15.str[i_24] == '\n');
    goto end_match_507;
next_509:;
    exit(1);
end_match_507:;
    milone_assert(match_132, 197, 6);
    int call_316 = 0;
    struct BoolIntTuple2 tuple_120;
    tuple_120.t0 = 0;
    tuple_120.t1 = i_24;
    match_130 = tuple_120;
    goto end_match_501;
next_506:;
    exit(1);
end_match_501:;
    match_128 = match_130;
    goto end_match_495;
next_500:;
    exit(1);
end_match_495:;
    match_126 = match_128;
    goto end_match_489;
next_494:;
    exit(1);
end_match_489:;
    return match_126;
}

struct BoolIntTuple2 scanCharLit_(struct String text_15, int i_23) {
    int call_317 = lookCharLit_(text_15, i_23);
    milone_assert(call_317, 184, 2);
    int call_318 = 0;
    struct BoolIntTuple2 call_319 = go_7(text_15, (i_23 + 1));
    return call_319;
}

int lookStrLit_(struct String text_16, int i_25) {
    return (text_16.str[i_25] == '"');
}

struct BoolIntTuple2 go_8(struct String text_17, int i_27) {
    struct BoolIntTuple2 match_133;
    int match_134;
    if (((i_27 + 1) >= text_17.len)) goto next_512;
    match_134 = (text_17.str[i_27] == '\\');
    goto end_match_511;
next_512:;
    if (((i_27 + 1) < text_17.len)) goto next_513;
    match_134 = 0;
    goto end_match_511;
next_513:;
    exit(1);
end_match_511:;
    if ((!(match_134))) goto next_514;
    struct BoolIntTuple2 call_320 = go_8(text_17, (i_27 + 2));
    match_133 = call_320;
    goto end_match_510;
next_514:;
    if (match_134) goto next_515;
    struct BoolIntTuple2 match_135;
    int match_136;
    if ((i_27 >= text_17.len)) goto next_518;
    match_136 = (text_17.str[i_27] == '"');
    goto end_match_517;
next_518:;
    if ((i_27 < text_17.len)) goto next_519;
    match_136 = 0;
    goto end_match_517;
next_519:;
    exit(1);
end_match_517:;
    if ((!(match_136))) goto next_520;
    struct BoolIntTuple2 tuple_121;
    tuple_121.t0 = 1;
    tuple_121.t1 = (i_27 + 1);
    match_135 = tuple_121;
    goto end_match_516;
next_520:;
    if (match_136) goto next_521;
    struct BoolIntTuple2 match_137;
    int match_138;
    if ((i_27 >= text_17.len)) goto next_524;
    match_138 = (text_17.str[i_27] != '\n');
    goto end_match_523;
next_524:;
    if ((i_27 < text_17.len)) goto next_525;
    match_138 = 0;
    goto end_match_523;
next_525:;
    exit(1);
end_match_523:;
    if ((!(match_138))) goto next_526;
    struct BoolIntTuple2 call_321 = go_8(text_17, (i_27 + 1));
    match_137 = call_321;
    goto end_match_522;
next_526:;
    if (match_138) goto next_527;
    int match_139;
    if ((i_27 != text_17.len)) goto next_529;
    match_139 = 1;
    goto end_match_528;
next_529:;
    if ((i_27 == text_17.len)) goto next_530;
    match_139 = (text_17.str[i_27] == '\n');
    goto end_match_528;
next_530:;
    exit(1);
end_match_528:;
    milone_assert(match_139, 218, 6);
    int call_322 = 0;
    struct BoolIntTuple2 tuple_122;
    tuple_122.t0 = 0;
    tuple_122.t1 = i_27;
    match_137 = tuple_122;
    goto end_match_522;
next_527:;
    exit(1);
end_match_522:;
    match_135 = match_137;
    goto end_match_516;
next_521:;
    exit(1);
end_match_516:;
    match_133 = match_135;
    goto end_match_510;
next_515:;
    exit(1);
end_match_510:;
    return match_133;
}

struct BoolIntTuple2 scanStrLit_(struct String text_17, int i_26) {
    int call_323 = lookStrLit_(text_17, i_26);
    milone_assert(call_323, 205, 2);
    int call_324 = 0;
    struct BoolIntTuple2 call_325 = go_8(text_17, (i_26 + 1));
    return call_325;
}

int lookStrLitRaw_(struct String text_18, int i_28) {
    int call_326 = strIsFollowedByRawQuotes_(i_28, text_18);
    return call_326;
}

struct BoolIntTuple2 go_9(struct String text_19, int i_30) {
    struct BoolIntTuple2 match_140;
    int call_327 = strIsFollowedByRawQuotes_(i_30, text_19);
    if ((!(call_327))) goto next_532;
    struct BoolIntTuple2 tuple_123;
    tuple_123.t0 = 1;
    tuple_123.t1 = (i_30 + 3);
    match_140 = tuple_123;
    goto end_match_531;
next_532:;
    if (call_327) goto next_533;
    struct BoolIntTuple2 match_141;
    if (((i_30 + 1) >= text_19.len)) goto next_535;
    struct BoolIntTuple2 call_328 = go_9(text_19, (i_30 + 1));
    match_141 = call_328;
    goto end_match_534;
next_535:;
    if (((i_30 + 1) < text_19.len)) goto next_536;
    milone_assert((i_30 == text_19.len), 233, 6);
    int call_329 = 0;
    struct BoolIntTuple2 tuple_124;
    tuple_124.t0 = 0;
    tuple_124.t1 = i_30;
    match_141 = tuple_124;
    goto end_match_534;
next_536:;
    exit(1);
end_match_534:;
    match_140 = match_141;
    goto end_match_531;
next_533:;
    exit(1);
end_match_531:;
    return match_140;
}

struct BoolIntTuple2 scanStrLitRaw_(struct String text_19, int i_29) {
    int call_330 = lookStrLitRaw_(text_19, i_29);
    milone_assert(call_330, 226, 2);
    int call_331 = 0;
    struct BoolIntTuple2 call_332 = go_9(text_19, (i_29 + 3));
    return call_332;
}

struct Token_ tokenFromIdent_(struct String text_20, int l_1, int r_1) {
    struct Token_ match_142;
    struct String call_333 = strSlice_(l_1, r_1, text_20);
    if ((str_cmp(call_333, (struct String){.str = "true", .len = 4}) != 0)) goto next_538;
    int* payload_69 = (int*)malloc(sizeof(int));
    (*(((int*)payload_69))) = 1;
    struct Token_ variant_69 = (struct Token_){.tag = Bool_1, .Bool_1 = payload_69};
    match_142 = variant_69;
    goto end_match_537;
next_538:;
    if ((str_cmp(call_333, (struct String){.str = "false", .len = 5}) != 0)) goto next_539;
    int* payload_70 = (int*)malloc(sizeof(int));
    (*(((int*)payload_70))) = 0;
    struct Token_ variant_70 = (struct Token_){.tag = Bool_1, .Bool_1 = payload_70};
    match_142 = variant_70;
    goto end_match_537;
next_539:;
    if ((str_cmp(call_333, (struct String){.str = "do", .len = 2}) != 0)) goto next_540;
    match_142 = (struct Token_){.tag = Do_};
    goto end_match_537;
next_540:;
    if ((str_cmp(call_333, (struct String){.str = "let", .len = 3}) != 0)) goto next_541;
    match_142 = (struct Token_){.tag = Let_};
    goto end_match_537;
next_541:;
    if ((str_cmp(call_333, (struct String){.str = "if", .len = 2}) != 0)) goto next_542;
    match_142 = (struct Token_){.tag = If_};
    goto end_match_537;
next_542:;
    if ((str_cmp(call_333, (struct String){.str = "then", .len = 4}) != 0)) goto next_543;
    match_142 = (struct Token_){.tag = Then_};
    goto end_match_537;
next_543:;
    if ((str_cmp(call_333, (struct String){.str = "else", .len = 4}) != 0)) goto next_544;
    match_142 = (struct Token_){.tag = Else_};
    goto end_match_537;
next_544:;
    if ((str_cmp(call_333, (struct String){.str = "match", .len = 5}) != 0)) goto next_545;
    match_142 = (struct Token_){.tag = Match_};
    goto end_match_537;
next_545:;
    if ((str_cmp(call_333, (struct String){.str = "with", .len = 4}) != 0)) goto next_546;
    match_142 = (struct Token_){.tag = With_};
    goto end_match_537;
next_546:;
    if ((str_cmp(call_333, (struct String){.str = "as", .len = 2}) != 0)) goto next_547;
    match_142 = (struct Token_){.tag = As_};
    goto end_match_537;
next_547:;
    if ((str_cmp(call_333, (struct String){.str = "when", .len = 4}) != 0)) goto next_548;
    match_142 = (struct Token_){.tag = When_};
    goto end_match_537;
next_548:;
    if ((str_cmp(call_333, (struct String){.str = "rec", .len = 3}) != 0)) goto next_549;
    match_142 = (struct Token_){.tag = Rec_};
    goto end_match_537;
next_549:;
    if ((str_cmp(call_333, (struct String){.str = "private", .len = 7}) != 0)) goto next_550;
    match_142 = (struct Token_){.tag = Private_};
    goto end_match_537;
next_550:;
    if ((str_cmp(call_333, (struct String){.str = "internal", .len = 8}) != 0)) goto next_551;
    match_142 = (struct Token_){.tag = Internal_};
    goto end_match_537;
next_551:;
    if ((str_cmp(call_333, (struct String){.str = "public", .len = 6}) != 0)) goto next_552;
    match_142 = (struct Token_){.tag = Public_};
    goto end_match_537;
next_552:;
    if ((str_cmp(call_333, (struct String){.str = "module", .len = 6}) != 0)) goto next_553;
    match_142 = (struct Token_){.tag = Module_};
    goto end_match_537;
next_553:;
    if ((str_cmp(call_333, (struct String){.str = "namespace", .len = 9}) != 0)) goto next_554;
    match_142 = (struct Token_){.tag = Namespace_};
    goto end_match_537;
next_554:;
    if ((str_cmp(call_333, (struct String){.str = "open", .len = 4}) != 0)) goto next_555;
    match_142 = (struct Token_){.tag = Open_};
    goto end_match_537;
next_555:;
    if ((str_cmp(call_333, (struct String){.str = "type", .len = 4}) != 0)) goto next_556;
    match_142 = (struct Token_){.tag = Type_};
    goto end_match_537;
next_556:;
    if ((str_cmp(call_333, (struct String){.str = "of", .len = 2}) != 0)) goto next_557;
    match_142 = (struct Token_){.tag = Of_};
    goto end_match_537;
next_557:;
    if ((str_cmp(call_333, (struct String){.str = "fun", .len = 3}) != 0)) goto next_558;
    match_142 = (struct Token_){.tag = Fun_};
    goto end_match_537;
next_558:;
    if ((str_cmp(call_333, (struct String){.str = "in", .len = 2}) != 0)) goto next_559;
    match_142 = (struct Token_){.tag = In_};
    goto end_match_537;
next_559:;
    struct String s_2 = call_333;
    struct String* payload_71 = (struct String*)malloc(sizeof(struct String));
    (*(((struct String*)payload_71))) = s_2;
    struct Token_ variant_71 = (struct Token_){.tag = Ident_, .Ident_ = payload_71};
    match_142 = variant_71;
    goto end_match_537;
next_560:;
end_match_537:;
    return match_142;
}

struct Token_ tokenFromOp_(struct String text_21, int l_2, int r_2) {
    struct Token_ match_143;
    struct String call_334 = strSlice_(l_2, r_2, text_21);
    if ((str_cmp(call_334, (struct String){.str = "&", .len = 1}) != 0)) goto next_562;
    match_143 = (struct Token_){.tag = Amp_};
    goto end_match_561;
next_562:;
    if ((str_cmp(call_334, (struct String){.str = "&&", .len = 2}) != 0)) goto next_563;
    match_143 = (struct Token_){.tag = AmpAmp_};
    goto end_match_561;
next_563:;
    if ((str_cmp(call_334, (struct String){.str = "->", .len = 2}) != 0)) goto next_564;
    match_143 = (struct Token_){.tag = Arrow_};
    goto end_match_561;
next_564:;
    if ((str_cmp(call_334, (struct String){.str = ":", .len = 1}) != 0)) goto next_565;
    match_143 = (struct Token_){.tag = Colon_};
    goto end_match_561;
next_565:;
    if ((str_cmp(call_334, (struct String){.str = "::", .len = 2}) != 0)) goto next_566;
    match_143 = (struct Token_){.tag = ColonColon_};
    goto end_match_561;
next_566:;
    if ((str_cmp(call_334, (struct String){.str = ".", .len = 1}) != 0)) goto next_567;
    match_143 = (struct Token_){.tag = Dot_};
    goto end_match_561;
next_567:;
    if ((str_cmp(call_334, (struct String){.str = "..", .len = 2}) != 0)) goto next_568;
    match_143 = (struct Token_){.tag = DotDot_};
    goto end_match_561;
next_568:;
    if ((str_cmp(call_334, (struct String){.str = "=", .len = 1}) != 0)) goto next_569;
    match_143 = (struct Token_){.tag = Eq_};
    goto end_match_561;
next_569:;
    if ((str_cmp(call_334, (struct String){.str = ">", .len = 1}) != 0)) goto next_570;
    match_143 = (struct Token_){.tag = Gt_};
    goto end_match_561;
next_570:;
    if ((str_cmp(call_334, (struct String){.str = ">=", .len = 2}) != 0)) goto next_571;
    match_143 = (struct Token_){.tag = GtEq_};
    goto end_match_561;
next_571:;
    if ((str_cmp(call_334, (struct String){.str = "<", .len = 1}) != 0)) goto next_572;
    match_143 = (struct Token_){.tag = Lt_};
    goto end_match_561;
next_572:;
    if ((str_cmp(call_334, (struct String){.str = "<=", .len = 2}) != 0)) goto next_573;
    match_143 = (struct Token_){.tag = LtEq_};
    goto end_match_561;
next_573:;
    if ((str_cmp(call_334, (struct String){.str = "<>", .len = 2}) != 0)) goto next_574;
    match_143 = (struct Token_){.tag = LtGt_};
    goto end_match_561;
next_574:;
    if ((str_cmp(call_334, (struct String){.str = "-", .len = 1}) != 0)) goto next_575;
    match_143 = (struct Token_){.tag = Minus_};
    goto end_match_561;
next_575:;
    if ((str_cmp(call_334, (struct String){.str = "%", .len = 1}) != 0)) goto next_576;
    match_143 = (struct Token_){.tag = Percent_};
    goto end_match_561;
next_576:;
    if ((str_cmp(call_334, (struct String){.str = "|", .len = 1}) != 0)) goto next_577;
    match_143 = (struct Token_){.tag = Pipe_};
    goto end_match_561;
next_577:;
    if ((str_cmp(call_334, (struct String){.str = "|>", .len = 2}) != 0)) goto next_578;
    match_143 = (struct Token_){.tag = PipeGt_};
    goto end_match_561;
next_578:;
    if ((str_cmp(call_334, (struct String){.str = "||", .len = 2}) != 0)) goto next_579;
    match_143 = (struct Token_){.tag = PipePipe_};
    goto end_match_561;
next_579:;
    if ((str_cmp(call_334, (struct String){.str = "+", .len = 1}) != 0)) goto next_580;
    match_143 = (struct Token_){.tag = Plus_};
    goto end_match_561;
next_580:;
    if ((str_cmp(call_334, (struct String){.str = ";", .len = 1}) != 0)) goto next_581;
    match_143 = (struct Token_){.tag = Semi_};
    goto end_match_561;
next_581:;
    if ((str_cmp(call_334, (struct String){.str = "*", .len = 1}) != 0)) goto next_582;
    match_143 = (struct Token_){.tag = Star_};
    goto end_match_561;
next_582:;
    if ((str_cmp(call_334, (struct String){.str = "/", .len = 1}) != 0)) goto next_583;
    match_143 = (struct Token_){.tag = Slash_};
    goto end_match_561;
next_583:;
    match_143 = (struct Token_){.tag = Error_};
    goto end_match_561;
next_584:;
end_match_561:;
    return match_143;
}

struct Token_ tokenFromPun_(struct String text_22, int l_3, int r_3) {
    milone_assert(((r_3 - l_3) == 1), 340, 2);
    int call_335 = 0;
    struct Token_ match_144;
    if ((text_22.str[l_3] != ',')) goto next_586;
    match_144 = (struct Token_){.tag = Comma_};
    goto end_match_585;
next_586:;
    if ((text_22.str[l_3] != '(')) goto next_587;
    match_144 = (struct Token_){.tag = ParenL_};
    goto end_match_585;
next_587:;
    if ((text_22.str[l_3] != ')')) goto next_588;
    match_144 = (struct Token_){.tag = ParenR_};
    goto end_match_585;
next_588:;
    if ((text_22.str[l_3] != '[')) goto next_589;
    match_144 = (struct Token_){.tag = BracketL_};
    goto end_match_585;
next_589:;
    if ((text_22.str[l_3] != ']')) goto next_590;
    match_144 = (struct Token_){.tag = BracketR_};
    goto end_match_585;
next_590:;
    struct Token_ call_336 = failwith_1((struct String){.str = "NEVER! charIsPun is broken", .len = 26});
    match_144 = call_336;
    goto end_match_585;
next_591:;
end_match_585:;
    return match_144;
}

struct Token_ tokenFromIntLit_(struct String text_23, int l_4, int r_4) {
    struct String call_337 = strSlice_(l_4, r_4, text_23);
    int call_338 = str_to_int(call_337);
    int value_ = call_338;
    int* payload_72 = (int*)malloc(sizeof(int));
    (*(((int*)payload_72))) = value_;
    struct Token_ variant_72 = (struct Token_){.tag = Int_1, .Int_1 = payload_72};
    return variant_72;
}

struct Token_ tokenFromCharLit_(struct String text_24, int l_5, int r_5) {
    int match_145;
    int match_146;
    if ((r_5 < (l_5 + 2))) goto next_594;
    match_146 = (text_24.str[l_5] == '\'');
    goto end_match_593;
next_594:;
    if ((r_5 >= (l_5 + 2))) goto next_595;
    match_146 = 0;
    goto end_match_593;
next_595:;
    exit(1);
end_match_593:;
    if ((!(match_146))) goto next_596;
    match_145 = (text_24.str[(r_5 - 1)] == '\'');
    goto end_match_592;
next_596:;
    if (match_146) goto next_597;
    match_145 = 0;
    goto end_match_592;
next_597:;
    exit(1);
end_match_592:;
    milone_assert(match_145, 360, 2);
    int call_339 = 0;
    int i_31 = (l_5 + 1);
    char match_147;
    if ((text_24.str[i_31] != '\\')) goto next_599;
    char match_148;
    if ((text_24.str[(i_31 + 1)] != 'u')) goto next_602;
    char call_340 = ((char)0);
    match_148 = call_340;
    goto end_match_601;
next_602:;
    if ((text_24.str[(i_31 + 1)] != 't')) goto next_603;
    match_148 = '\t';
    goto end_match_601;
next_603:;
    if ((text_24.str[(i_31 + 1)] != 'r')) goto next_604;
    match_148 = '\r';
    goto end_match_601;
next_604:;
    if ((text_24.str[(i_31 + 1)] != 'n')) goto next_605;
    match_148 = '\n';
    goto end_match_601;
next_605:;
    char c_6 = text_24.str[(i_31 + 1)];
    match_148 = c_6;
    goto end_match_601;
next_606:;
end_match_601:;
    match_147 = match_148;
    goto end_match_598;
next_599:;
    char c_7 = text_24.str[i_31];
    match_147 = c_7;
    goto end_match_598;
next_600:;
end_match_598:;
    char value_1 = match_147;
    char* payload_73 = (char*)malloc(sizeof(char));
    (*(((char*)payload_73))) = value_1;
    struct Token_ variant_73 = (struct Token_){.tag = Char_1, .Char_1 = payload_73};
    return variant_73;
}

int next_(int r_6, struct String text_25, int i_33) {
    int match_149;
    int match_150;
    if ((i_33 != (r_6 - 1))) goto next_609;
    match_150 = 1;
    goto end_match_608;
next_609:;
    if ((i_33 == (r_6 - 1))) goto next_610;
    match_150 = (text_25.str[i_33] == '\\');
    goto end_match_608;
next_610:;
    exit(1);
end_match_608:;
    if ((!(match_150))) goto next_611;
    match_149 = i_33;
    goto end_match_607;
next_611:;
    if (match_150) goto next_612;
    int call_341 = next_(r_6, text_25, (i_33 + 1));
    match_149 = call_341;
    goto end_match_607;
next_612:;
    exit(1);
end_match_607:;
    return match_149;
}

struct String go_10(int r_6, struct String text_25, struct StringList* acc_, int i_32) {
    int call_342 = next_(r_6, text_25, i_32);
    int endIndex_ = call_342;
    struct String call_343 = strSlice_(i_32, endIndex_, text_25);
    struct StringList* list_47 = (struct StringList*)malloc(sizeof(struct StringList));
    list_47->head = call_343;
    list_47->tail = acc_;
    struct StringList* acc_1 = list_47;
    int i_34 = endIndex_;
    struct String match_151;
    if ((i_34 != (r_6 - 1))) goto next_614;
    struct StringList* call_344 = listRev_2(acc_1);
    struct String call_345 = strConcat_(call_344);
    match_151 = call_345;
    goto end_match_613;
next_614:;
    if ((i_34 == (r_6 - 1))) goto next_615;
    milone_assert((text_25.str[i_34] == '\\'), 403, 6);
    int call_346 = 0;
    struct String match_152;
    if ((text_25.str[(i_34 + 1)] != 'u')) goto next_617;
    struct StringList* list_48 = (struct StringList*)malloc(sizeof(struct StringList));
    list_48->head = (struct String){.str = "\0", .len = 1};
    list_48->tail = acc_1;
    struct String call_347 = go_10(r_6, text_25, list_48, (i_34 + 6));
    match_152 = call_347;
    goto end_match_616;
next_617:;
    if ((text_25.str[(i_34 + 1)] != 't')) goto next_618;
    struct StringList* list_49 = (struct StringList*)malloc(sizeof(struct StringList));
    list_49->head = (struct String){.str = "\t", .len = 1};
    list_49->tail = acc_1;
    struct String call_348 = go_10(r_6, text_25, list_49, (i_34 + 2));
    match_152 = call_348;
    goto end_match_616;
next_618:;
    if ((text_25.str[(i_34 + 1)] != 'r')) goto next_619;
    struct StringList* list_50 = (struct StringList*)malloc(sizeof(struct StringList));
    list_50->head = (struct String){.str = "\r", .len = 1};
    list_50->tail = acc_1;
    struct String call_349 = go_10(r_6, text_25, list_50, (i_34 + 2));
    match_152 = call_349;
    goto end_match_616;
next_619:;
    if ((text_25.str[(i_34 + 1)] != 'n')) goto next_620;
    struct StringList* list_51 = (struct StringList*)malloc(sizeof(struct StringList));
    list_51->head = (struct String){.str = "\n", .len = 1};
    list_51->tail = acc_1;
    struct String call_350 = go_10(r_6, text_25, list_51, (i_34 + 2));
    match_152 = call_350;
    goto end_match_616;
next_620:;
    struct String call_351 = strSlice_((i_34 + 1), (i_34 + 2), text_25);
    struct StringList* list_52 = (struct StringList*)malloc(sizeof(struct StringList));
    list_52->head = call_351;
    list_52->tail = acc_1;
    struct String call_352 = go_10(r_6, text_25, list_52, (i_34 + 2));
    match_152 = call_352;
    goto end_match_616;
next_621:;
end_match_616:;
    match_151 = match_152;
    goto end_match_613;
next_615:;
    exit(1);
end_match_613:;
    return match_151;
}

struct Token_ tokenFromStrLit_(struct String text_25, int l_6, int r_6) {
    int match_153;
    int match_154;
    if ((r_6 < (l_6 + 2))) goto next_624;
    match_154 = (text_25.str[l_6] == '"');
    goto end_match_623;
next_624:;
    if ((r_6 >= (l_6 + 2))) goto next_625;
    match_154 = 0;
    goto end_match_623;
next_625:;
    exit(1);
end_match_623:;
    if ((!(match_154))) goto next_626;
    match_153 = (text_25.str[(r_6 - 1)] == '"');
    goto end_match_622;
next_626:;
    if (match_154) goto next_627;
    match_153 = 0;
    goto end_match_622;
next_627:;
    exit(1);
end_match_622:;
    milone_assert(match_153, 384, 2);
    int call_353 = 0;
    struct String call_354 = go_10(r_6, text_25, NULL, (l_6 + 1));
    struct String value_2 = call_354;
    struct String* payload_74 = (struct String*)malloc(sizeof(struct String));
    (*(((struct String*)payload_74))) = value_2;
    struct Token_ variant_74 = (struct Token_){.tag = Str_1, .Str_1 = payload_74};
    return variant_74;
}

struct Token_ tokenFromStrLitRaw_(struct String text_26, int l_7, int r_7) {
    int match_155;
    int match_156;
    if ((r_7 < (l_7 + 6))) goto next_630;
    int call_355 = strIsFollowedByRawQuotes_(l_7, text_26);
    match_156 = call_355;
    goto end_match_629;
next_630:;
    if ((r_7 >= (l_7 + 6))) goto next_631;
    match_156 = 0;
    goto end_match_629;
next_631:;
    exit(1);
end_match_629:;
    if ((!(match_156))) goto next_632;
    int call_356 = strIsFollowedByRawQuotes_((r_7 - 3), text_26);
    match_155 = call_356;
    goto end_match_628;
next_632:;
    if (match_156) goto next_633;
    match_155 = 0;
    goto end_match_628;
next_633:;
    exit(1);
end_match_628:;
    milone_assert(match_155, 420, 2);
    int call_357 = 0;
    struct String call_358 = strSlice_((l_7 + 3), (r_7 - 3), text_26);
    struct String* payload_75 = (struct String*)malloc(sizeof(struct String));
    (*(((struct String*)payload_75))) = call_358;
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

struct StringIntTuple2 tokCtxToTextIndex_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 arg_96) {
    struct String text_27 = arg_96.t0;
    int i_35 = arg_96.t1;
    struct StringIntTuple2 tuple_125;
    tuple_125.t0 = text_27;
    tuple_125.t1 = i_35;
    return tuple_125;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokCtxSkip_(int r_8, struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 arg_97) {
    struct String text_28 = arg_97.t0;
    int i_36 = arg_97.t1;
    struct IntIntTuple2 loc_ = arg_97.t2;
    struct Token_IntIntTuple2Tuple2List* acc_2 = arg_97.t3;
    int match_157;
    int match_158;
    if ((i_36 < 0)) goto next_636;
    match_158 = (r_8 >= i_36);
    goto end_match_635;
next_636:;
    if ((i_36 >= 0)) goto next_637;
    match_158 = 0;
    goto end_match_635;
next_637:;
    exit(1);
end_match_635:;
    if ((!(match_158))) goto next_638;
    match_157 = (text_28.len >= r_8);
    goto end_match_634;
next_638:;
    if (match_158) goto next_639;
    match_157 = 0;
    goto end_match_634;
next_639:;
    exit(1);
end_match_634:;
    milone_assert(match_157, 433, 2);
    int call_359 = 0;
    struct IntIntTuple2 call_360 = locShift_(text_28, i_36, r_8, loc_);
    struct IntIntTuple2 newLoc_ = call_360;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tuple_126;
    tuple_126.t0 = text_28;
    tuple_126.t1 = r_8;
    tuple_126.t2 = newLoc_;
    tuple_126.t3 = acc_2;
    return tuple_126;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokCtxPush_(struct Token_ kind_, int r_9, struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 arg_98) {
    struct String text_29 = arg_98.t0;
    int i_37 = arg_98.t1;
    struct IntIntTuple2 loc_1 = arg_98.t2;
    struct Token_IntIntTuple2Tuple2List* acc_3 = arg_98.t3;
    int match_159;
    int match_160;
    if ((i_37 < 0)) goto next_642;
    match_160 = (r_9 >= i_37);
    goto end_match_641;
next_642:;
    if ((i_37 >= 0)) goto next_643;
    match_160 = 0;
    goto end_match_641;
next_643:;
    exit(1);
end_match_641:;
    if ((!(match_160))) goto next_644;
    match_159 = (text_29.len >= r_9);
    goto end_match_640;
next_644:;
    if (match_160) goto next_645;
    match_159 = 0;
    goto end_match_640;
next_645:;
    exit(1);
end_match_640:;
    milone_assert(match_159, 440, 2);
    int call_361 = 0;
    struct Token_IntIntTuple2Tuple2 tuple_127;
    tuple_127.t0 = kind_;
    tuple_127.t1 = loc_1;
    struct Token_IntIntTuple2Tuple2List* list_53 = (struct Token_IntIntTuple2Tuple2List*)malloc(sizeof(struct Token_IntIntTuple2Tuple2List));
    list_53->head = tuple_127;
    list_53->tail = acc_3;
    struct Token_IntIntTuple2Tuple2List* newAcc_ = list_53;
    struct IntIntTuple2 call_362 = locShift_(text_29, i_37, r_9, loc_1);
    struct IntIntTuple2 newLoc_1 = call_362;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tuple_128;
    tuple_128.t0 = text_29;
    tuple_128.t1 = r_9;
    tuple_128.t2 = newLoc_1;
    tuple_128.t3 = newAcc_;
    return tuple_128;
}

struct Token_IntIntTuple2Tuple2List* tokEof_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 arg_99) {
    struct String text_30 = arg_99.t0;
    int i_38 = arg_99.t1;
    struct Token_IntIntTuple2Tuple2List* acc_4 = arg_99.t3;
    int call_363 = lookEof_(text_30, i_38);
    milone_assert(call_363, 446, 2);
    int call_364 = 0;
    struct Token_IntIntTuple2Tuple2List* call_365 = listRev_7(acc_4);
    return call_365;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokError_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_) {
    struct StringIntTuple2 call_366 = tokCtxToTextIndex_(t_);
    struct String text_31 = call_366.t0;
    int i_39 = call_366.t1;
    int call_367 = scanError_(text_31, i_39);
    int r_10 = call_367;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_368 = tokCtxSkip_(r_10, t_);
    return call_368;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokComment_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_1) {
    struct StringIntTuple2 call_369 = tokCtxToTextIndex_(t_1);
    struct String text_32 = call_369.t0;
    int i_40 = call_369.t1;
    int call_370 = scanLine_(text_32, i_40);
    int r_11 = call_370;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_371 = tokCtxSkip_(r_11, t_1);
    return call_371;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokSpace_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_2) {
    struct StringIntTuple2 call_372 = tokCtxToTextIndex_(t_2);
    struct String text_33 = call_372.t0;
    int i_41 = call_372.t1;
    int call_373 = scanSpace_(text_33, i_41);
    int r_12 = call_373;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_374 = tokCtxSkip_(r_12, t_2);
    return call_374;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokPun_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_3) {
    struct StringIntTuple2 call_375 = tokCtxToTextIndex_(t_3);
    struct String text_34 = call_375.t0;
    int i_42 = call_375.t1;
    int call_376 = scanPun_(text_34, i_42);
    int r_13 = call_376;
    struct Token_ call_377 = tokenFromPun_(text_34, i_42, r_13);
    struct Token_ token_ = call_377;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_378 = tokCtxPush_(token_, r_13, t_3);
    return call_378;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokOp_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_4) {
    struct StringIntTuple2 call_379 = tokCtxToTextIndex_(t_4);
    struct String text_35 = call_379.t0;
    int i_43 = call_379.t1;
    int call_380 = scanOp_(text_35, i_43);
    int r_14 = call_380;
    struct Token_ call_381 = tokenFromOp_(text_35, i_43, r_14);
    struct Token_ token_1 = call_381;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_382 = tokCtxPush_(token_1, r_14, t_4);
    return call_382;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokIdent_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_5) {
    struct StringIntTuple2 call_383 = tokCtxToTextIndex_(t_5);
    struct String text_36 = call_383.t0;
    int i_44 = call_383.t1;
    int call_384 = scanIdent_(text_36, i_44);
    int r_15 = call_384;
    struct Token_ call_385 = tokenFromIdent_(text_36, i_44, r_15);
    struct Token_ token_2 = call_385;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_386 = tokCtxPush_(token_2, r_15, t_5);
    return call_386;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokIntLit_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_6) {
    struct StringIntTuple2 call_387 = tokCtxToTextIndex_(t_6);
    struct String text_37 = call_387.t0;
    int i_45 = call_387.t1;
    int call_388 = scanIntLit_(text_37, i_45);
    int r_16 = call_388;
    struct Token_ call_389 = tokenFromIntLit_(text_37, i_45, r_16);
    struct Token_ token_3 = call_389;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_390 = tokCtxPush_(token_3, r_16, t_6);
    return call_390;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokCharLit_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_7) {
    struct StringIntTuple2 call_391 = tokCtxToTextIndex_(t_7);
    struct String text_38 = call_391.t0;
    int i_46 = call_391.t1;
    struct BoolIntTuple2 call_392 = scanCharLit_(text_38, i_46);
    int ok_ = call_392.t0;
    int r_17 = call_392.t1;
    struct Token_ match_161;
    if ((!(ok_))) goto next_647;
    struct Token_ call_393 = tokenFromCharLit_(text_38, i_46, r_17);
    match_161 = call_393;
    goto end_match_646;
next_647:;
    if (ok_) goto next_648;
    match_161 = (struct Token_){.tag = Error_};
    goto end_match_646;
next_648:;
    exit(1);
end_match_646:;
    struct Token_ token_4 = match_161;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_394 = tokCtxPush_(token_4, r_17, t_7);
    return call_394;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokStrLit_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_8) {
    struct StringIntTuple2 call_395 = tokCtxToTextIndex_(t_8);
    struct String text_39 = call_395.t0;
    int i_47 = call_395.t1;
    struct BoolIntTuple2 call_396 = scanStrLit_(text_39, i_47);
    int ok_1 = call_396.t0;
    int r_18 = call_396.t1;
    struct Token_ match_162;
    if ((!(ok_1))) goto next_650;
    struct Token_ call_397 = tokenFromStrLit_(text_39, i_47, r_18);
    match_162 = call_397;
    goto end_match_649;
next_650:;
    if (ok_1) goto next_651;
    match_162 = (struct Token_){.tag = Error_};
    goto end_match_649;
next_651:;
    exit(1);
end_match_649:;
    struct Token_ token_5 = match_162;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_398 = tokCtxPush_(token_5, r_18, t_8);
    return call_398;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokStrLitRaw_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_9) {
    struct StringIntTuple2 call_399 = tokCtxToTextIndex_(t_9);
    struct String text_40 = call_399.t0;
    int i_48 = call_399.t1;
    struct BoolIntTuple2 call_400 = scanStrLitRaw_(text_40, i_48);
    int ok_2 = call_400.t0;
    int r_19 = call_400.t1;
    struct Token_ match_163;
    if ((!(ok_2))) goto next_653;
    struct Token_ call_401 = tokenFromStrLitRaw_(text_40, i_48, r_19);
    match_163 = call_401;
    goto end_match_652;
next_653:;
    if (ok_2) goto next_654;
    match_163 = (struct Token_){.tag = Error_};
    goto end_match_652;
next_654:;
    exit(1);
end_match_652:;
    struct Token_ token_6 = match_163;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_402 = tokCtxPush_(token_6, r_19, t_9);
    return call_402;
}

struct Token_IntIntTuple2Tuple2List* go_11(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_10) {
    struct StringIntTuple2 call_403 = tokCtxToTextIndex_(t_10);
    struct String text_42 = call_403.t0;
    int i_49 = call_403.t1;
    struct Token_IntIntTuple2Tuple2List* match_164;
    int call_404 = lookEof_(text_42, i_49);
    if ((!(call_404))) goto next_656;
    struct Token_IntIntTuple2Tuple2List* call_405 = tokEof_(t_10);
    match_164 = call_405;
    goto end_match_655;
next_656:;
    if (call_404) goto next_657;
    struct Token_IntIntTuple2Tuple2List* match_165;
    int call_406 = lookComment_(text_42, i_49);
    if ((!(call_406))) goto next_659;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_407 = tokComment_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_408 = go_11(call_407);
    match_165 = call_408;
    goto end_match_658;
next_659:;
    if (call_406) goto next_660;
    struct Token_IntIntTuple2Tuple2List* match_166;
    int call_409 = lookSpace_(text_42, i_49);
    if ((!(call_409))) goto next_662;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_410 = tokSpace_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_411 = go_11(call_410);
    match_166 = call_411;
    goto end_match_661;
next_662:;
    if (call_409) goto next_663;
    struct Token_IntIntTuple2Tuple2List* match_167;
    int call_412 = lookOp_(text_42, i_49);
    if ((!(call_412))) goto next_665;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_413 = tokOp_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_414 = go_11(call_413);
    match_167 = call_414;
    goto end_match_664;
next_665:;
    if (call_412) goto next_666;
    struct Token_IntIntTuple2Tuple2List* match_168;
    int call_415 = lookIntLit_(text_42, i_49);
    if ((!(call_415))) goto next_668;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_416 = tokIntLit_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_417 = go_11(call_416);
    match_168 = call_417;
    goto end_match_667;
next_668:;
    if (call_415) goto next_669;
    struct Token_IntIntTuple2Tuple2List* match_169;
    int call_418 = lookIdent_(text_42, i_49);
    if ((!(call_418))) goto next_671;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_419 = tokIdent_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_420 = go_11(call_419);
    match_169 = call_420;
    goto end_match_670;
next_671:;
    if (call_418) goto next_672;
    struct Token_IntIntTuple2Tuple2List* match_170;
    int call_421 = lookCharLit_(text_42, i_49);
    if ((!(call_421))) goto next_674;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_422 = tokCharLit_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_423 = go_11(call_422);
    match_170 = call_423;
    goto end_match_673;
next_674:;
    if (call_421) goto next_675;
    struct Token_IntIntTuple2Tuple2List* match_171;
    int call_424 = lookStrLitRaw_(text_42, i_49);
    if ((!(call_424))) goto next_677;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_425 = tokStrLitRaw_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_426 = go_11(call_425);
    match_171 = call_426;
    goto end_match_676;
next_677:;
    if (call_424) goto next_678;
    struct Token_IntIntTuple2Tuple2List* match_172;
    int call_427 = lookStrLit_(text_42, i_49);
    if ((!(call_427))) goto next_680;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_428 = tokStrLit_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_429 = go_11(call_428);
    match_172 = call_429;
    goto end_match_679;
next_680:;
    if (call_427) goto next_681;
    struct Token_IntIntTuple2Tuple2List* match_173;
    int call_430 = lookPun_(text_42, i_49);
    if ((!(call_430))) goto next_683;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_431 = tokPun_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_432 = go_11(call_431);
    match_173 = call_432;
    goto end_match_682;
next_683:;
    if (call_430) goto next_684;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_433 = tokError_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_434 = go_11(call_433);
    match_173 = call_434;
    goto end_match_682;
next_684:;
    exit(1);
end_match_682:;
    match_172 = match_173;
    goto end_match_679;
next_681:;
    exit(1);
end_match_679:;
    match_171 = match_172;
    goto end_match_676;
next_678:;
    exit(1);
end_match_676:;
    match_170 = match_171;
    goto end_match_673;
next_675:;
    exit(1);
end_match_673:;
    match_169 = match_170;
    goto end_match_670;
next_672:;
    exit(1);
end_match_670:;
    match_168 = match_169;
    goto end_match_667;
next_669:;
    exit(1);
end_match_667:;
    match_167 = match_168;
    goto end_match_664;
next_666:;
    exit(1);
end_match_664:;
    match_166 = match_167;
    goto end_match_661;
next_663:;
    exit(1);
end_match_661:;
    match_165 = match_166;
    goto end_match_658;
next_660:;
    exit(1);
end_match_658:;
    match_164 = match_165;
    goto end_match_655;
next_657:;
    exit(1);
end_match_655:;
    return match_164;
}

struct Token_IntIntTuple2Tuple2List* tokenize_(struct String text_41) {
    struct IntIntTuple2 tuple_130;
    tuple_130.t0 = 0;
    tuple_130.t1 = 0;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tuple_129;
    tuple_129.t0 = text_41;
    tuple_129.t1 = 0;
    tuple_129.t2 = tuple_130;
    tuple_129.t3 = NULL;
    struct Token_IntIntTuple2Tuple2List* call_435 = go_11(tuple_129);
    return call_435;
}

int leadsExpr_1(struct Token_IntIntTuple2Tuple2List* tokens_1) {
    int match_174;
    if ((!(tokens_1))) goto next_686;
    struct Token_ token_13 = tokens_1->head.t0;
    int call_436 = tokenIsExprFirst_(token_13);
    match_174 = call_436;
    goto end_match_685;
next_686:;
    match_174 = 0;
    goto end_match_685;
next_687:;
end_match_685:;
    return match_174;
}

int leadsArg_1(struct Token_IntIntTuple2Tuple2List* tokens_2) {
    int match_175;
    if ((!(tokens_2))) goto next_689;
    struct Token_ token_14 = tokens_2->head.t0;
    int call_437 = tokenIsArgFirst_(token_14);
    match_175 = call_437;
    goto end_match_688;
next_689:;
    match_175 = 0;
    goto end_match_688;
next_690:;
end_match_688:;
    return match_175;
}

int leadsPat_1(struct Token_IntIntTuple2Tuple2List* tokens_3) {
    int match_176;
    if ((!(tokens_3))) goto next_692;
    struct Token_ token_15 = tokens_3->head.t0;
    int call_438 = tokenIsPatFirst_(token_15);
    match_176 = call_438;
    goto end_match_691;
next_692:;
    match_176 = 0;
    goto end_match_691;
next_693:;
end_match_691:;
    return match_176;
}

struct IntIntTuple2 nextLoc_1(struct Token_IntIntTuple2Tuple2List* tokens_4) {
    struct IntIntTuple2 match_177;
    if ((!((!(tokens_4))))) goto next_695;
    struct IntIntTuple2 tuple_131;
    tuple_131.t0 = (0 - 1);
    tuple_131.t1 = 0;
    match_177 = tuple_131;
    goto end_match_694;
next_695:;
    if ((!(tokens_4))) goto next_696;
    struct IntIntTuple2 loc_28 = tokens_4->head.t1;
    match_177 = loc_28;
    goto end_match_694;
next_696:;
    exit(1);
end_match_694:;
    return match_177;
}

int nextInside_1(struct IntIntTuple2 baseLoc_, struct Token_IntIntTuple2Tuple2List* tokens_5) {
    int match_178;
    if ((!((!(tokens_5))))) goto next_698;
    match_178 = 0;
    goto end_match_697;
next_698:;
    if ((!(tokens_5))) goto next_699;
    struct IntIntTuple2 loc_29 = tokens_5->head.t1;
    int call_439 = locInside_(baseLoc_, loc_29);
    if ((!(call_439))) goto next_699;
    match_178 = 1;
    goto end_match_697;
next_699:;
    match_178 = 0;
    goto end_match_697;
next_700:;
end_match_697:;
    return match_178;
}

struct StringIntIntTuple2Tuple2List* parseErrorCore_1(struct String msg_2, struct IntIntTuple2 loc_30, struct Token_IntIntTuple2Tuple2List* tokens_6, struct StringIntIntTuple2Tuple2List* errors_1) {
    struct StringIntIntTuple2Tuple2 tuple_132;
    tuple_132.t0 = msg_2;
    tuple_132.t1 = loc_30;
    struct StringIntIntTuple2Tuple2List* list_54 = (struct StringIntIntTuple2Tuple2List*)malloc(sizeof(struct StringIntIntTuple2Tuple2List));
    list_54->head = tuple_132;
    list_54->tail = errors_1;
    return list_54;
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

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyError_1(struct String msg_3, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_100) {
    struct Token_IntIntTuple2Tuple2List* tokens_7 = arg_100.t0;
    struct StringIntIntTuple2Tuple2List* errors_2 = arg_100.t1;
    struct IntIntTuple2 call_440 = nextLoc_1(tokens_7);
    struct IntIntTuple2 loc_31 = call_440;
    struct StringIntIntTuple2Tuple2List* call_441 = parseErrorCore_1(msg_3, loc_31, tokens_7, errors_2);
    struct StringIntIntTuple2Tuple2List* errors_3 = call_441;
    struct IntIntTuple2* payload_76 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_76))) = loc_31;
    struct ATy_ variant_76 = (struct ATy_){.tag = Missing_, .Missing_ = payload_76};
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_133;
    tuple_133.t0 = variant_76;
    tuple_133.t1 = tokens_7;
    tuple_133.t2 = errors_3;
    return tuple_133;
}

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct APat_ t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatError_1(struct String msg_4, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_101) {
    struct Token_IntIntTuple2Tuple2List* tokens_8 = arg_101.t0;
    struct StringIntIntTuple2Tuple2List* errors_4 = arg_101.t1;
    struct IntIntTuple2 call_442 = nextLoc_1(tokens_8);
    struct IntIntTuple2 loc_32 = call_442;
    struct StringIntIntTuple2Tuple2List* call_443 = parseErrorCore_1(msg_4, loc_32, tokens_8, errors_4);
    struct StringIntIntTuple2Tuple2List* errors_5 = call_443;
    struct IntIntTuple2* payload_77 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_77))) = loc_32;
    struct APat_ variant_77 = (struct APat_){.tag = Missing_1, .Missing_1 = payload_77};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_134;
    tuple_134.t0 = variant_77;
    tuple_134.t1 = tokens_8;
    tuple_134.t2 = errors_5;
    return tuple_134;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct AExpr_ t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseExprError_1(struct String msg_5, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_102) {
    struct Token_IntIntTuple2Tuple2List* tokens_9 = arg_102.t0;
    struct StringIntIntTuple2Tuple2List* errors_6 = arg_102.t1;
    struct IntIntTuple2 call_444 = nextLoc_1(tokens_9);
    struct IntIntTuple2 loc_33 = call_444;
    struct StringIntIntTuple2Tuple2List* call_445 = parseErrorCore_1(msg_5, loc_33, tokens_9, errors_6);
    struct StringIntIntTuple2Tuple2List* errors_7 = call_445;
    struct IntIntTuple2* payload_78 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_78))) = loc_33;
    struct AExpr_ variant_78 = (struct AExpr_){.tag = Missing_2, .Missing_2 = payload_78};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_135;
    tuple_135.t0 = variant_78;
    tuple_135.t1 = tokens_9;
    tuple_135.t2 = errors_7;
    return tuple_135;
}

struct StringIntIntTuple2Tuple2List* parseNewError_1(struct String msg_6, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_103) {
    struct Token_IntIntTuple2Tuple2List* tokens_10 = arg_103.t0;
    struct StringIntIntTuple2Tuple2List* errors_8 = arg_103.t1;
    struct IntIntTuple2 call_446 = nextLoc_1(tokens_10);
    struct IntIntTuple2 loc_34 = call_446;
    struct StringIntIntTuple2Tuple2List* call_447 = parseErrorCore_1(msg_6, loc_34, tokens_10, errors_8);
    return call_447;
}

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyAtom_(struct IntIntTuple2 baseLoc_1, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_104) {
    struct Token_IntIntTuple2Tuple2List* tokens_11 = arg_104.t0;
    struct StringIntIntTuple2Tuple2List* errors_9 = arg_104.t1;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_179;
    int call_448 = nextInside_1(baseLoc_1, tokens_11);
    if (call_448) goto next_702;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_136;
    tuple_136.t0 = tokens_11;
    tuple_136.t1 = errors_9;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_449 = parseTyError_1((struct String){.str = "Expected a type atom", .len = 20}, tuple_136);
    match_179 = call_449;
    goto end_match_701;
next_702:;
    if ((!(tokens_11))) goto next_703;
    if ((tokens_11->head.t0.tag != Ident_)) goto next_703;
    struct String ident_17 = (*(tokens_11->head.t0.Ident_));
    struct IntIntTuple2 loc_35 = tokens_11->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_12 = tokens_11->tail;
    struct StringIntIntTuple2Tuple2 tuple_138;
    tuple_138.t0 = ident_17;
    tuple_138.t1 = loc_35;
    struct StringIntIntTuple2Tuple2* payload_79 = (struct StringIntIntTuple2Tuple2*)malloc(sizeof(struct StringIntIntTuple2Tuple2));
    (*(((struct StringIntIntTuple2Tuple2*)payload_79))) = tuple_138;
    struct ATy_ variant_79 = (struct ATy_){.tag = Ident_1, .Ident_1 = payload_79};
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_137;
    tuple_137.t0 = variant_79;
    tuple_137.t1 = tokens_12;
    tuple_137.t2 = errors_9;
    match_179 = tuple_137;
    goto end_match_701;
next_703:;
    if ((!(tokens_11))) goto next_704;
    if ((tokens_11->head.t0.tag != ParenL_)) goto next_704;
    struct Token_IntIntTuple2Tuple2List* tokens_13 = tokens_11->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_139;
    tuple_139.t0 = tokens_13;
    tuple_139.t1 = errors_9;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_450 = parseTy_(baseLoc_1, tuple_139);
    struct ATy_ ty_47 = call_450.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_14 = call_450.t1;
    struct StringIntIntTuple2Tuple2List* errors_10 = call_450.t2;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_180;
    if ((!(tokens_14))) goto next_707;
    if ((tokens_14->head.t0.tag != ParenR_)) goto next_707;
    struct Token_IntIntTuple2Tuple2List* tokens_15 = tokens_14->tail;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_140;
    tuple_140.t0 = ty_47;
    tuple_140.t1 = tokens_15;
    tuple_140.t2 = errors_10;
    match_180 = tuple_140;
    goto end_match_706;
next_707:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_141;
    tuple_141.t0 = tokens_14;
    tuple_141.t1 = errors_10;
    struct StringIntIntTuple2Tuple2List* call_451 = parseNewError_1((struct String){.str = "Expected ')'", .len = 12}, tuple_141);
    struct StringIntIntTuple2Tuple2List* errors_11 = call_451;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_142;
    tuple_142.t0 = ty_47;
    tuple_142.t1 = tokens_14;
    tuple_142.t2 = errors_11;
    match_180 = tuple_142;
    goto end_match_706;
next_708:;
end_match_706:;
    match_179 = match_180;
    goto end_match_701;
next_704:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_143;
    tuple_143.t0 = tokens_11;
    tuple_143.t1 = errors_9;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_452 = parseTyError_1((struct String){.str = "Expected a type atom", .len = 20}, tuple_143);
    match_179 = call_452;
    goto end_match_701;
next_705:;
end_match_701:;
    return match_179;
}

struct ATy_StringIntIntTuple2Tuple3 {
    struct ATy_ t0;
    struct String t1;
    struct IntIntTuple2 t2;
};

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_41(struct IntIntTuple2 baseLoc_2, struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 arg_105) {
    struct ATy_ ty_48 = arg_105.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_17 = arg_105.t1;
    struct StringIntIntTuple2Tuple2List* errors_13 = arg_105.t2;
    int call_453 = nextInside_1(baseLoc_2, tokens_17);
    int inside_ = call_453;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_181;
    if ((!(tokens_17))) goto next_710;
    if ((tokens_17->head.t0.tag != Ident_)) goto next_710;
    struct String ident_18 = (*(tokens_17->head.t0.Ident_));
    struct IntIntTuple2 loc_36 = tokens_17->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_18 = tokens_17->tail;
    if ((!(inside_))) goto next_710;
    struct ATy_StringIntIntTuple2Tuple3 tuple_145;
    tuple_145.t0 = ty_48;
    tuple_145.t1 = ident_18;
    tuple_145.t2 = loc_36;
    struct ATy_StringIntIntTuple2Tuple3* payload_80 = (struct ATy_StringIntIntTuple2Tuple3*)malloc(sizeof(struct ATy_StringIntIntTuple2Tuple3));
    (*(((struct ATy_StringIntIntTuple2Tuple3*)payload_80))) = tuple_145;
    struct ATy_ variant_80 = (struct ATy_){.tag = Suffix_, .Suffix_ = payload_80};
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_144;
    tuple_144.t0 = variant_80;
    tuple_144.t1 = tokens_18;
    tuple_144.t2 = errors_13;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_454 = go_41(baseLoc_2, tuple_144);
    match_181 = call_454;
    goto end_match_709;
next_710:;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_146;
    tuple_146.t0 = ty_48;
    tuple_146.t1 = tokens_17;
    tuple_146.t2 = errors_13;
    match_181 = tuple_146;
    goto end_match_709;
next_711:;
end_match_709:;
    return match_181;
}

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTySuffix_(struct IntIntTuple2 baseLoc_2, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_106) {
    struct Token_IntIntTuple2Tuple2List* tokens_16 = arg_106.t0;
    struct StringIntIntTuple2Tuple2List* errors_12 = arg_106.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_147;
    tuple_147.t0 = tokens_16;
    tuple_147.t1 = errors_12;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_455 = parseTyAtom_(baseLoc_2, tuple_147);
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_456 = go_41(baseLoc_2, call_455);
    return call_456;
}

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyPrefix_(struct IntIntTuple2 baseLoc_3, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_107) {
    struct Token_IntIntTuple2Tuple2List* tokens_19 = arg_107.t0;
    struct StringIntIntTuple2Tuple2List* errors_14 = arg_107.t1;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_182;
    if ((!(tokens_19))) goto next_713;
    if ((tokens_19->head.t0.tag != Ident_)) goto next_713;
    if ((!(tokens_19->tail))) goto next_713;
    if ((tokens_19->tail->head.t0.tag != Colon_)) goto next_713;
    struct Token_IntIntTuple2Tuple2List* tokens_20 = tokens_19->tail->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_148;
    tuple_148.t0 = tokens_20;
    tuple_148.t1 = errors_14;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_457 = parseTySuffix_(baseLoc_3, tuple_148);
    match_182 = call_457;
    goto end_match_712;
next_713:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_149;
    tuple_149.t0 = tokens_19;
    tuple_149.t1 = errors_14;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_458 = parseTySuffix_(baseLoc_3, tuple_149);
    match_182 = call_458;
    goto end_match_712;
next_714:;
end_match_712:;
    return match_182;
}

struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct ATy_List* t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_28(struct IntIntTuple2 baseLoc_4, struct ATy_List* acc_16, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_108) {
    struct Token_IntIntTuple2Tuple2List* tokens_22 = arg_108.t0;
    struct StringIntIntTuple2Tuple2List* errors_16 = arg_108.t1;
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_183;
    if ((!(tokens_22))) goto next_716;
    if ((tokens_22->head.t0.tag != Star_)) goto next_716;
    struct Token_IntIntTuple2Tuple2List* tokens_23 = tokens_22->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_150;
    tuple_150.t0 = tokens_23;
    tuple_150.t1 = errors_16;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_459 = parseTyPrefix_(baseLoc_4, tuple_150);
    struct ATy_ itemTy_11 = call_459.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_24 = call_459.t1;
    struct StringIntIntTuple2Tuple2List* errors_17 = call_459.t2;
    struct ATy_List* list_55 = (struct ATy_List*)malloc(sizeof(struct ATy_List));
    list_55->head = itemTy_11;
    list_55->tail = acc_16;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_151;
    tuple_151.t0 = tokens_24;
    tuple_151.t1 = errors_17;
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_460 = go_28(baseLoc_4, list_55, tuple_151);
    match_183 = call_460;
    goto end_match_715;
next_716:;
    struct ATy_List* call_461 = listRev_6(acc_16);
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_152;
    tuple_152.t0 = call_461;
    tuple_152.t1 = tokens_22;
    tuple_152.t2 = errors_16;
    match_183 = tuple_152;
    goto end_match_715;
next_717:;
end_match_715:;
    return match_183;
}

struct ATy_ListIntIntTuple2Tuple2 {
    struct ATy_List* t0;
    struct IntIntTuple2 t1;
};

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyTuple_(struct IntIntTuple2 baseLoc_4, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_109) {
    struct Token_IntIntTuple2Tuple2List* tokens_21 = arg_109.t0;
    struct StringIntIntTuple2Tuple2List* errors_15 = arg_109.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_153;
    tuple_153.t0 = tokens_21;
    tuple_153.t1 = errors_15;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_462 = parseTyPrefix_(baseLoc_4, tuple_153);
    struct ATy_ itemTy_12 = call_462.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_25 = call_462.t1;
    struct StringIntIntTuple2Tuple2List* errors_18 = call_462.t2;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_184;
    if ((!(tokens_25))) goto next_719;
    if ((tokens_25->head.t0.tag != Star_)) goto next_719;
    struct IntIntTuple2 opLoc_ = tokens_25->head.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_154;
    tuple_154.t0 = tokens_25;
    tuple_154.t1 = errors_18;
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_463 = go_28(baseLoc_4, NULL, tuple_154);
    struct ATy_List* itemTys_1 = call_463.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_26 = call_463.t1;
    struct StringIntIntTuple2Tuple2List* errors_19 = call_463.t2;
    struct ATy_List* list_56 = (struct ATy_List*)malloc(sizeof(struct ATy_List));
    list_56->head = itemTy_12;
    list_56->tail = itemTys_1;
    struct ATy_ListIntIntTuple2Tuple2 tuple_156;
    tuple_156.t0 = list_56;
    tuple_156.t1 = opLoc_;
    struct ATy_ListIntIntTuple2Tuple2* payload_81 = (struct ATy_ListIntIntTuple2Tuple2*)malloc(sizeof(struct ATy_ListIntIntTuple2Tuple2));
    (*(((struct ATy_ListIntIntTuple2Tuple2*)payload_81))) = tuple_156;
    struct ATy_ variant_81 = (struct ATy_){.tag = Tuple_, .Tuple_ = payload_81};
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_155;
    tuple_155.t0 = variant_81;
    tuple_155.t1 = tokens_26;
    tuple_155.t2 = errors_19;
    match_184 = tuple_155;
    goto end_match_718;
next_719:;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_157;
    tuple_157.t0 = itemTy_12;
    tuple_157.t1 = tokens_25;
    tuple_157.t2 = errors_18;
    match_184 = tuple_157;
    goto end_match_718;
next_720:;
end_match_718:;
    return match_184;
}

struct ATy_ATy_IntIntTuple2Tuple3 {
    struct ATy_ t0;
    struct ATy_ t1;
    struct IntIntTuple2 t2;
};

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyFun_(struct IntIntTuple2 baseLoc_5, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_110) {
    struct Token_IntIntTuple2Tuple2List* tokens_27 = arg_110.t0;
    struct StringIntIntTuple2Tuple2List* errors_20 = arg_110.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_158;
    tuple_158.t0 = tokens_27;
    tuple_158.t1 = errors_20;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_464 = parseTyTuple_(baseLoc_5, tuple_158);
    struct ATy_ sTy_1 = call_464.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_28 = call_464.t1;
    struct StringIntIntTuple2Tuple2List* errors_21 = call_464.t2;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_185;
    if ((!(tokens_28))) goto next_722;
    if ((tokens_28->head.t0.tag != Arrow_)) goto next_722;
    struct IntIntTuple2 opLoc_1 = tokens_28->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_29 = tokens_28->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_159;
    tuple_159.t0 = tokens_29;
    tuple_159.t1 = errors_21;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_465 = parseTyFun_(baseLoc_5, tuple_159);
    struct ATy_ tTy_1 = call_465.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_30 = call_465.t1;
    struct StringIntIntTuple2Tuple2List* errors_22 = call_465.t2;
    struct ATy_ATy_IntIntTuple2Tuple3 tuple_161;
    tuple_161.t0 = sTy_1;
    tuple_161.t1 = tTy_1;
    tuple_161.t2 = opLoc_1;
    struct ATy_ATy_IntIntTuple2Tuple3* payload_82 = (struct ATy_ATy_IntIntTuple2Tuple3*)malloc(sizeof(struct ATy_ATy_IntIntTuple2Tuple3));
    (*(((struct ATy_ATy_IntIntTuple2Tuple3*)payload_82))) = tuple_161;
    struct ATy_ variant_82 = (struct ATy_){.tag = Fun_1, .Fun_1 = payload_82};
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_160;
    tuple_160.t0 = variant_82;
    tuple_160.t1 = tokens_30;
    tuple_160.t2 = errors_22;
    match_185 = tuple_160;
    goto end_match_721;
next_722:;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_162;
    tuple_162.t0 = sTy_1;
    tuple_162.t1 = tokens_28;
    tuple_162.t2 = errors_21;
    match_185 = tuple_162;
    goto end_match_721;
next_723:;
end_match_721:;
    return match_185;
}

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTy_(struct IntIntTuple2 baseLoc_6, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_111) {
    struct Token_IntIntTuple2Tuple2List* tokens_31 = arg_111.t0;
    struct StringIntIntTuple2Tuple2List* errors_23 = arg_111.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_163;
    tuple_163.t0 = tokens_31;
    tuple_163.t1 = errors_23;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_466 = parseTyFun_(baseLoc_6, tuple_163);
    return call_466;
}

struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct AVariant_List* t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct StringATy_ListIntIntTuple2Tuple3 {
    struct String t0;
    struct ATy_List* t1;
    struct IntIntTuple2 t2;
};

struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_29(struct IntIntTuple2 baseLoc_7, struct AVariant_List* acc_17, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_112) {
    struct Token_IntIntTuple2Tuple2List* tokens_33 = arg_112.t0;
    struct StringIntIntTuple2Tuple2List* errors_25 = arg_112.t1;
    struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_186;
    if ((!(tokens_33))) goto next_725;
    if ((tokens_33->head.t0.tag != Pipe_)) goto next_725;
    if ((!(tokens_33->tail))) goto next_725;
    if ((tokens_33->tail->head.t0.tag != Ident_)) goto next_725;
    struct String variantIdent_ = (*(tokens_33->tail->head.t0.Ident_));
    struct IntIntTuple2 loc_37 = tokens_33->tail->head.t1;
    if ((!(tokens_33->tail->tail))) goto next_725;
    if ((tokens_33->tail->tail->head.t0.tag != Of_)) goto next_725;
    struct Token_IntIntTuple2Tuple2List* tokens_34 = tokens_33->tail->tail->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_164;
    tuple_164.t0 = tokens_34;
    tuple_164.t1 = errors_25;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_467 = parseTy_(baseLoc_7, tuple_164);
    struct ATy_ payloadTy_ = call_467.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_35 = call_467.t1;
    struct StringIntIntTuple2Tuple2List* errors_26 = call_467.t2;
    struct ATy_List* list_58 = (struct ATy_List*)malloc(sizeof(struct ATy_List));
    list_58->head = payloadTy_;
    list_58->tail = NULL;
    struct StringATy_ListIntIntTuple2Tuple3 tuple_165;
    tuple_165.t0 = variantIdent_;
    tuple_165.t1 = list_58;
    tuple_165.t2 = loc_37;
    struct StringATy_ListIntIntTuple2Tuple3* payload_83 = (struct StringATy_ListIntIntTuple2Tuple3*)malloc(sizeof(struct StringATy_ListIntIntTuple2Tuple3));
    (*(((struct StringATy_ListIntIntTuple2Tuple3*)payload_83))) = tuple_165;
    struct AVariant_ variant_83 = (struct AVariant_){.tag = AVariant_, .AVariant_ = payload_83};
    struct AVariant_List* list_57 = (struct AVariant_List*)malloc(sizeof(struct AVariant_List));
    list_57->head = variant_83;
    list_57->tail = acc_17;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_166;
    tuple_166.t0 = tokens_35;
    tuple_166.t1 = errors_26;
    struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_468 = go_29(baseLoc_7, list_57, tuple_166);
    match_186 = call_468;
    goto end_match_724;
next_725:;
    if ((!(tokens_33))) goto next_726;
    if ((tokens_33->head.t0.tag != Pipe_)) goto next_726;
    if ((!(tokens_33->tail))) goto next_726;
    if ((tokens_33->tail->head.t0.tag != Ident_)) goto next_726;
    struct String variantIdent_1 = (*(tokens_33->tail->head.t0.Ident_));
    struct IntIntTuple2 loc_38 = tokens_33->tail->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_36 = tokens_33->tail->tail;
    struct StringATy_ListIntIntTuple2Tuple3 tuple_167;
    tuple_167.t0 = variantIdent_1;
    tuple_167.t1 = NULL;
    tuple_167.t2 = loc_38;
    struct StringATy_ListIntIntTuple2Tuple3* payload_84 = (struct StringATy_ListIntIntTuple2Tuple3*)malloc(sizeof(struct StringATy_ListIntIntTuple2Tuple3));
    (*(((struct StringATy_ListIntIntTuple2Tuple3*)payload_84))) = tuple_167;
    struct AVariant_ variant_84 = (struct AVariant_){.tag = AVariant_, .AVariant_ = payload_84};
    struct AVariant_List* list_59 = (struct AVariant_List*)malloc(sizeof(struct AVariant_List));
    list_59->head = variant_84;
    list_59->tail = acc_17;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_168;
    tuple_168.t0 = tokens_36;
    tuple_168.t1 = errors_25;
    struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_469 = go_29(baseLoc_7, list_59, tuple_168);
    match_186 = call_469;
    goto end_match_724;
next_726:;
    struct AVariant_List* call_470 = listRev_5(acc_17);
    struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_169;
    tuple_169.t0 = call_470;
    tuple_169.t1 = tokens_33;
    tuple_169.t2 = errors_25;
    match_186 = tuple_169;
    goto end_match_724;
next_727:;
end_match_724:;
    return match_186;
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

struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyDeclUnion_(struct IntIntTuple2 baseLoc_7, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_113) {
    struct Token_IntIntTuple2Tuple2List* tokens_32 = arg_113.t0;
    struct StringIntIntTuple2Tuple2List* errors_24 = arg_113.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_170;
    tuple_170.t0 = tokens_32;
    tuple_170.t1 = errors_24;
    struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_471 = go_29(baseLoc_7, NULL, tuple_170);
    struct AVariant_List* variants_1 = call_471.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_37 = call_471.t1;
    struct StringIntIntTuple2Tuple2List* errors_27 = call_471.t2;
    struct AVariant_List** payload_85 = (struct AVariant_List**)malloc(sizeof(struct AVariant_List*));
    (*(((struct AVariant_List**)payload_85))) = variants_1;
    struct ATyDecl_ variant_85 = (struct ATyDecl_){.tag = Union_, .Union_ = payload_85};
    struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_171;
    tuple_171.t0 = variant_85;
    tuple_171.t1 = tokens_37;
    tuple_171.t2 = errors_27;
    return tuple_171;
}

struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyDeclBody_(struct IntIntTuple2 baseLoc_8, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_114) {
    struct Token_IntIntTuple2Tuple2List* tokens_38 = arg_114.t0;
    struct StringIntIntTuple2Tuple2List* errors_28 = arg_114.t1;
    struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_187;
    if ((!(tokens_38))) goto next_729;
    if ((tokens_38->head.t0.tag != Pipe_)) goto next_729;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_172;
    tuple_172.t0 = tokens_38;
    tuple_172.t1 = errors_28;
    struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_472 = parseTyDeclUnion_(baseLoc_8, tuple_172);
    match_187 = call_472;
    goto end_match_728;
next_729:;
    if ((!(tokens_38))) goto next_730;
    if ((tokens_38->head.t0.tag != Ident_)) goto next_730;
    if ((!(tokens_38->tail))) goto next_730;
    if ((tokens_38->tail->head.t0.tag != Of_)) goto next_730;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_173;
    tuple_173.t0 = tokens_38;
    tuple_173.t1 = errors_28;
    struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_473 = parseTyDeclUnion_(baseLoc_8, tuple_173);
    match_187 = call_473;
    goto end_match_728;
next_730:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_174;
    tuple_174.t0 = tokens_38;
    tuple_174.t1 = errors_28;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_474 = parseTy_(baseLoc_8, tuple_174);
    struct ATy_ ty_49 = call_474.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_39 = call_474.t1;
    struct StringIntIntTuple2Tuple2List* errors_29 = call_474.t2;
    struct ATy_* payload_86 = (struct ATy_*)malloc(sizeof(struct ATy_));
    (*(((struct ATy_*)payload_86))) = ty_49;
    struct ATyDecl_ variant_86 = (struct ATyDecl_){.tag = Synonym_, .Synonym_ = payload_86};
    struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_175;
    tuple_175.t0 = variant_86;
    tuple_175.t1 = tokens_39;
    tuple_175.t2 = errors_29;
    match_187 = tuple_175;
    goto end_match_728;
next_731:;
end_match_728:;
    return match_187;
}

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatParenBody_(struct IntIntTuple2 baseLoc_9, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_115) {
    struct Token_IntIntTuple2Tuple2List* tokens_40 = arg_115.t0;
    struct StringIntIntTuple2Tuple2List* errors_30 = arg_115.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_176;
    tuple_176.t0 = tokens_40;
    tuple_176.t1 = errors_30;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_475 = parsePat_(baseLoc_9, tuple_176);
    struct APat_ pat_15 = call_475.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_41 = call_475.t1;
    struct StringIntIntTuple2Tuple2List* errors_31 = call_475.t2;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_188;
    if ((!(tokens_41))) goto next_733;
    if ((tokens_41->head.t0.tag != ParenR_)) goto next_733;
    struct Token_IntIntTuple2Tuple2List* tokens_42 = tokens_41->tail;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_177;
    tuple_177.t0 = pat_15;
    tuple_177.t1 = tokens_42;
    tuple_177.t2 = errors_31;
    match_188 = tuple_177;
    goto end_match_732;
next_733:;
    struct Token_IntIntTuple2Tuple2List* tokens_43 = tokens_41;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_178;
    tuple_178.t0 = tokens_43;
    tuple_178.t1 = errors_31;
    struct StringIntIntTuple2Tuple2List* call_476 = parseNewError_1((struct String){.str = "Expected ')'", .len = 12}, tuple_178);
    struct StringIntIntTuple2Tuple2List* errors_32 = call_476;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_179;
    tuple_179.t0 = pat_15;
    tuple_179.t1 = tokens_43;
    tuple_179.t2 = errors_32;
    match_188 = tuple_179;
    goto end_match_732;
next_734:;
end_match_732:;
    return match_188;
}

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct APat_List* t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_30(struct IntIntTuple2 baseLoc_10, struct APat_List* patAcc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_116) {
    struct Token_IntIntTuple2Tuple2List* tokens_45 = arg_116.t0;
    struct StringIntIntTuple2Tuple2List* errors_34 = arg_116.t1;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_189;
    if ((!(tokens_45))) goto next_736;
    if ((tokens_45->head.t0.tag != BracketR_)) goto next_736;
    struct Token_IntIntTuple2Tuple2List* tokens_46 = tokens_45->tail;
    struct APat_List* call_477 = listRev_4(patAcc_);
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_180;
    tuple_180.t0 = call_477;
    tuple_180.t1 = tokens_46;
    tuple_180.t2 = errors_34;
    match_189 = tuple_180;
    goto end_match_735;
next_736:;
    if ((!(tokens_45))) goto next_737;
    if ((tokens_45->head.t0.tag != Semi_)) goto next_737;
    struct Token_IntIntTuple2Tuple2List* tokens_47 = tokens_45->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_181;
    tuple_181.t0 = tokens_47;
    tuple_181.t1 = errors_34;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_478 = parsePat_(baseLoc_10, tuple_181);
    struct APat_ pat_16 = call_478.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_48 = call_478.t1;
    struct StringIntIntTuple2Tuple2List* errors_35 = call_478.t2;
    struct APat_List* list_60 = (struct APat_List*)malloc(sizeof(struct APat_List));
    list_60->head = pat_16;
    list_60->tail = patAcc_;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_182;
    tuple_182.t0 = tokens_48;
    tuple_182.t1 = errors_35;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_479 = go_30(baseLoc_10, list_60, tuple_182);
    match_189 = call_479;
    goto end_match_735;
next_737:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_183;
    tuple_183.t0 = tokens_45;
    tuple_183.t1 = errors_34;
    struct StringIntIntTuple2Tuple2List* call_480 = parseNewError_1((struct String){.str = "Expected ';' or ']'", .len = 19}, tuple_183);
    struct StringIntIntTuple2Tuple2List* errors_36 = call_480;
    struct APat_List* call_481 = listRev_4(patAcc_);
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_184;
    tuple_184.t0 = call_481;
    tuple_184.t1 = tokens_45;
    tuple_184.t2 = errors_36;
    match_189 = tuple_184;
    goto end_match_735;
next_738:;
end_match_735:;
    return match_189;
}

struct APat_ListIntIntTuple2Tuple2 {
    struct APat_List* t0;
    struct IntIntTuple2 t1;
};

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatListBody_(struct IntIntTuple2 baseLoc_10, struct IntIntTuple2 bracketLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_117) {
    struct Token_IntIntTuple2Tuple2List* tokens_44 = arg_117.t0;
    struct StringIntIntTuple2Tuple2List* errors_33 = arg_117.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_185;
    tuple_185.t0 = tokens_44;
    tuple_185.t1 = errors_33;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_482 = parsePat_(baseLoc_10, tuple_185);
    struct APat_ itemPat_ = call_482.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_49 = call_482.t1;
    struct StringIntIntTuple2Tuple2List* errors_37 = call_482.t2;
    struct APat_List* list_61 = (struct APat_List*)malloc(sizeof(struct APat_List));
    list_61->head = itemPat_;
    list_61->tail = NULL;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_186;
    tuple_186.t0 = tokens_49;
    tuple_186.t1 = errors_37;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_483 = go_30(baseLoc_10, list_61, tuple_186);
    struct APat_List* itemPats_1 = call_483.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_50 = call_483.t1;
    struct StringIntIntTuple2Tuple2List* errors_38 = call_483.t2;
    struct APat_ListIntIntTuple2Tuple2 tuple_188;
    tuple_188.t0 = itemPats_1;
    tuple_188.t1 = bracketLoc_;
    struct APat_ListIntIntTuple2Tuple2* payload_87 = (struct APat_ListIntIntTuple2Tuple2*)malloc(sizeof(struct APat_ListIntIntTuple2Tuple2));
    (*(((struct APat_ListIntIntTuple2Tuple2*)payload_87))) = tuple_188;
    struct APat_ variant_87 = (struct APat_){.tag = ListLit_, .ListLit_ = payload_87};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_187;
    tuple_187.t0 = variant_87;
    tuple_187.t1 = tokens_50;
    tuple_187.t2 = errors_38;
    return tuple_187;
}

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatAtom_(struct IntIntTuple2 baseLoc_11, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_118) {
    struct Token_IntIntTuple2Tuple2List* tokens_51 = arg_118.t0;
    struct StringIntIntTuple2Tuple2List* errors_39 = arg_118.t1;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_190;
    int match_191;
    int call_484 = nextInside_1(baseLoc_11, tokens_51);
    if ((!(call_484))) goto next_752;
    int call_485 = leadsPat_1(tokens_51);
    match_191 = call_485;
    goto end_match_751;
next_752:;
    if (call_484) goto next_753;
    match_191 = 0;
    goto end_match_751;
next_753:;
    exit(1);
end_match_751:;
    if (match_191) goto next_740;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_189;
    tuple_189.t0 = tokens_51;
    tuple_189.t1 = errors_39;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_486 = parsePatError_1((struct String){.str = "Expected a pattern atom", .len = 23}, tuple_189);
    match_190 = call_486;
    goto end_match_739;
next_740:;
    if ((!(tokens_51))) goto next_741;
    if ((tokens_51->head.t0.tag != Bool_1)) goto next_741;
    int value_7 = (*(tokens_51->head.t0.Bool_1));
    struct IntIntTuple2 loc_39 = tokens_51->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_52 = tokens_51->tail;
    int* payload_88 = (int*)malloc(sizeof(int));
    (*(((int*)payload_88))) = value_7;
    struct Lit_ variant_88 = (struct Lit_){.tag = Bool_, .Bool_ = payload_88};
    struct Lit_IntIntTuple2Tuple2 tuple_191;
    tuple_191.t0 = variant_88;
    tuple_191.t1 = loc_39;
    struct Lit_IntIntTuple2Tuple2* payload_89 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_89))) = tuple_191;
    struct APat_ variant_89 = (struct APat_){.tag = Lit_, .Lit_ = payload_89};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_190;
    tuple_190.t0 = variant_89;
    tuple_190.t1 = tokens_52;
    tuple_190.t2 = errors_39;
    match_190 = tuple_190;
    goto end_match_739;
next_741:;
    if ((!(tokens_51))) goto next_742;
    if ((tokens_51->head.t0.tag != Int_1)) goto next_742;
    int value_8 = (*(tokens_51->head.t0.Int_1));
    struct IntIntTuple2 loc_40 = tokens_51->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_53 = tokens_51->tail;
    int* payload_90 = (int*)malloc(sizeof(int));
    (*(((int*)payload_90))) = value_8;
    struct Lit_ variant_90 = (struct Lit_){.tag = Int_, .Int_ = payload_90};
    struct Lit_IntIntTuple2Tuple2 tuple_193;
    tuple_193.t0 = variant_90;
    tuple_193.t1 = loc_40;
    struct Lit_IntIntTuple2Tuple2* payload_91 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_91))) = tuple_193;
    struct APat_ variant_91 = (struct APat_){.tag = Lit_, .Lit_ = payload_91};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_192;
    tuple_192.t0 = variant_91;
    tuple_192.t1 = tokens_53;
    tuple_192.t2 = errors_39;
    match_190 = tuple_192;
    goto end_match_739;
next_742:;
    if ((!(tokens_51))) goto next_743;
    if ((tokens_51->head.t0.tag != Char_1)) goto next_743;
    char value_9 = (*(tokens_51->head.t0.Char_1));
    struct IntIntTuple2 loc_41 = tokens_51->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_54 = tokens_51->tail;
    char* payload_92 = (char*)malloc(sizeof(char));
    (*(((char*)payload_92))) = value_9;
    struct Lit_ variant_92 = (struct Lit_){.tag = Char_, .Char_ = payload_92};
    struct Lit_IntIntTuple2Tuple2 tuple_195;
    tuple_195.t0 = variant_92;
    tuple_195.t1 = loc_41;
    struct Lit_IntIntTuple2Tuple2* payload_93 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_93))) = tuple_195;
    struct APat_ variant_93 = (struct APat_){.tag = Lit_, .Lit_ = payload_93};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_194;
    tuple_194.t0 = variant_93;
    tuple_194.t1 = tokens_54;
    tuple_194.t2 = errors_39;
    match_190 = tuple_194;
    goto end_match_739;
next_743:;
    if ((!(tokens_51))) goto next_744;
    if ((tokens_51->head.t0.tag != Str_1)) goto next_744;
    struct String value_10 = (*(tokens_51->head.t0.Str_1));
    struct IntIntTuple2 loc_42 = tokens_51->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_55 = tokens_51->tail;
    struct String* payload_94 = (struct String*)malloc(sizeof(struct String));
    (*(((struct String*)payload_94))) = value_10;
    struct Lit_ variant_94 = (struct Lit_){.tag = Str_, .Str_ = payload_94};
    struct Lit_IntIntTuple2Tuple2 tuple_197;
    tuple_197.t0 = variant_94;
    tuple_197.t1 = loc_42;
    struct Lit_IntIntTuple2Tuple2* payload_95 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_95))) = tuple_197;
    struct APat_ variant_95 = (struct APat_){.tag = Lit_, .Lit_ = payload_95};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_196;
    tuple_196.t0 = variant_95;
    tuple_196.t1 = tokens_55;
    tuple_196.t2 = errors_39;
    match_190 = tuple_196;
    goto end_match_739;
next_744:;
    if ((!(tokens_51))) goto next_745;
    if ((tokens_51->head.t0.tag != Ident_)) goto next_745;
    struct String ident_19 = (*(tokens_51->head.t0.Ident_));
    struct IntIntTuple2 loc_43 = tokens_51->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_56 = tokens_51->tail;
    struct StringIntIntTuple2Tuple2 tuple_199;
    tuple_199.t0 = ident_19;
    tuple_199.t1 = loc_43;
    struct StringIntIntTuple2Tuple2* payload_96 = (struct StringIntIntTuple2Tuple2*)malloc(sizeof(struct StringIntIntTuple2Tuple2));
    (*(((struct StringIntIntTuple2Tuple2*)payload_96))) = tuple_199;
    struct APat_ variant_96 = (struct APat_){.tag = Ident_2, .Ident_2 = payload_96};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_198;
    tuple_198.t0 = variant_96;
    tuple_198.t1 = tokens_56;
    tuple_198.t2 = errors_39;
    match_190 = tuple_198;
    goto end_match_739;
next_745:;
    if ((!(tokens_51))) goto next_746;
    if ((tokens_51->head.t0.tag != ParenL_)) goto next_746;
    struct IntIntTuple2 loc_44 = tokens_51->head.t1;
    if ((!(tokens_51->tail))) goto next_746;
    if ((tokens_51->tail->head.t0.tag != ParenR_)) goto next_746;
    struct Token_IntIntTuple2Tuple2List* tokens_57 = tokens_51->tail->tail;
    struct APat_ListIntIntTuple2Tuple2 tuple_201;
    tuple_201.t0 = NULL;
    tuple_201.t1 = loc_44;
    struct APat_ListIntIntTuple2Tuple2* payload_97 = (struct APat_ListIntIntTuple2Tuple2*)malloc(sizeof(struct APat_ListIntIntTuple2Tuple2));
    (*(((struct APat_ListIntIntTuple2Tuple2*)payload_97))) = tuple_201;
    struct APat_ variant_97 = (struct APat_){.tag = TupleLit_, .TupleLit_ = payload_97};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_200;
    tuple_200.t0 = variant_97;
    tuple_200.t1 = tokens_57;
    tuple_200.t2 = errors_39;
    match_190 = tuple_200;
    goto end_match_739;
next_746:;
    if ((!(tokens_51))) goto next_747;
    if ((tokens_51->head.t0.tag != ParenL_)) goto next_747;
    struct Token_IntIntTuple2Tuple2List* tokens_58 = tokens_51->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_202;
    tuple_202.t0 = tokens_58;
    tuple_202.t1 = errors_39;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_487 = parsePatParenBody_(baseLoc_11, tuple_202);
    match_190 = call_487;
    goto end_match_739;
next_747:;
    if ((!(tokens_51))) goto next_748;
    if ((tokens_51->head.t0.tag != BracketL_)) goto next_748;
    struct IntIntTuple2 loc_45 = tokens_51->head.t1;
    if ((!(tokens_51->tail))) goto next_748;
    if ((tokens_51->tail->head.t0.tag != BracketR_)) goto next_748;
    struct Token_IntIntTuple2Tuple2List* tokens_59 = tokens_51->tail->tail;
    struct APat_ListIntIntTuple2Tuple2 tuple_204;
    tuple_204.t0 = NULL;
    tuple_204.t1 = loc_45;
    struct APat_ListIntIntTuple2Tuple2* payload_98 = (struct APat_ListIntIntTuple2Tuple2*)malloc(sizeof(struct APat_ListIntIntTuple2Tuple2));
    (*(((struct APat_ListIntIntTuple2Tuple2*)payload_98))) = tuple_204;
    struct APat_ variant_98 = (struct APat_){.tag = ListLit_, .ListLit_ = payload_98};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_203;
    tuple_203.t0 = variant_98;
    tuple_203.t1 = tokens_59;
    tuple_203.t2 = errors_39;
    match_190 = tuple_203;
    goto end_match_739;
next_748:;
    if ((!(tokens_51))) goto next_749;
    if ((tokens_51->head.t0.tag != BracketL_)) goto next_749;
    struct IntIntTuple2 loc_46 = tokens_51->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_60 = tokens_51->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_205;
    tuple_205.t0 = tokens_60;
    tuple_205.t1 = errors_39;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_488 = parsePatListBody_(baseLoc_11, loc_46, tuple_205);
    match_190 = call_488;
    goto end_match_739;
next_749:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_206;
    tuple_206.t0 = tokens_51;
    tuple_206.t1 = errors_39;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_489 = parsePatError_1((struct String){.str = "NEVER: The token must be a pat", .len = 30}, tuple_206);
    match_190 = call_489;
    goto end_match_739;
next_750:;
end_match_739:;
    return match_190;
}

struct APat_StringIntIntTuple2Tuple3 {
    struct APat_ t0;
    struct String t1;
    struct IntIntTuple2 t2;
};

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatNav_(struct IntIntTuple2 baseLoc_12, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_119) {
    struct Token_IntIntTuple2Tuple2List* tokens_61 = arg_119.t0;
    struct StringIntIntTuple2Tuple2List* errors_40 = arg_119.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_207;
    tuple_207.t0 = tokens_61;
    tuple_207.t1 = errors_40;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_490 = parsePatAtom_(baseLoc_12, tuple_207);
    struct APat_ pat_17 = call_490.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_62 = call_490.t1;
    struct StringIntIntTuple2Tuple2List* errors_41 = call_490.t2;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_192;
    if ((!(tokens_62))) goto next_755;
    if ((tokens_62->head.t0.tag != Dot_)) goto next_755;
    struct IntIntTuple2 loc_47 = tokens_62->head.t1;
    if ((!(tokens_62->tail))) goto next_755;
    if ((tokens_62->tail->head.t0.tag != Ident_)) goto next_755;
    struct String ident_20 = (*(tokens_62->tail->head.t0.Ident_));
    struct Token_IntIntTuple2Tuple2List* tokens_63 = tokens_62->tail->tail;
    struct APat_StringIntIntTuple2Tuple3 tuple_209;
    tuple_209.t0 = pat_17;
    tuple_209.t1 = ident_20;
    tuple_209.t2 = loc_47;
    struct APat_StringIntIntTuple2Tuple3* payload_99 = (struct APat_StringIntIntTuple2Tuple3*)malloc(sizeof(struct APat_StringIntIntTuple2Tuple3));
    (*(((struct APat_StringIntIntTuple2Tuple3*)payload_99))) = tuple_209;
    struct APat_ variant_99 = (struct APat_){.tag = Nav_, .Nav_ = payload_99};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_208;
    tuple_208.t0 = variant_99;
    tuple_208.t1 = tokens_63;
    tuple_208.t2 = errors_41;
    match_192 = tuple_208;
    goto end_match_754;
next_755:;
    if ((!(tokens_62))) goto next_756;
    if ((tokens_62->head.t0.tag != Dot_)) goto next_756;
    struct Token_IntIntTuple2Tuple2List* tokens_64 = tokens_62->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_210;
    tuple_210.t0 = tokens_64;
    tuple_210.t1 = errors_41;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_491 = parsePatError_1((struct String){.str = "Expected identifier", .len = 19}, tuple_210);
    match_192 = call_491;
    goto end_match_754;
next_756:;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_211;
    tuple_211.t0 = pat_17;
    tuple_211.t1 = tokens_62;
    tuple_211.t2 = errors_41;
    match_192 = tuple_211;
    goto end_match_754;
next_757:;
end_match_754:;
    return match_192;
}

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_31(struct IntIntTuple2 argBaseLoc_, struct IntIntTuple2 baseLoc_13, struct APat_List* acc_18, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_120) {
    struct Token_IntIntTuple2Tuple2List* tokens_66 = arg_120.t0;
    struct StringIntIntTuple2Tuple2List* errors_43 = arg_120.t1;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_193;
    int match_194;
    int call_492 = nextInside_1(argBaseLoc_, tokens_66);
    if ((!(call_492))) goto next_760;
    int call_493 = leadsPat_1(tokens_66);
    match_194 = call_493;
    goto end_match_759;
next_760:;
    if (call_492) goto next_761;
    match_194 = 0;
    goto end_match_759;
next_761:;
    exit(1);
end_match_759:;
    if ((!(match_194))) goto next_762;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_212;
    tuple_212.t0 = tokens_66;
    tuple_212.t1 = errors_43;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_494 = parsePatNav_(baseLoc_13, tuple_212);
    struct APat_ expr_8 = call_494.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_67 = call_494.t1;
    struct StringIntIntTuple2Tuple2List* errors_44 = call_494.t2;
    struct APat_List* list_62 = (struct APat_List*)malloc(sizeof(struct APat_List));
    list_62->head = expr_8;
    list_62->tail = acc_18;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_213;
    tuple_213.t0 = tokens_67;
    tuple_213.t1 = errors_44;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_495 = go_31(argBaseLoc_, baseLoc_13, list_62, tuple_213);
    match_193 = call_495;
    goto end_match_758;
next_762:;
    if (match_194) goto next_763;
    struct APat_List* call_496 = listRev_4(acc_18);
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_214;
    tuple_214.t0 = call_496;
    tuple_214.t1 = tokens_66;
    tuple_214.t2 = errors_43;
    match_193 = tuple_214;
    goto end_match_758;
next_763:;
    exit(1);
end_match_758:;
    return match_193;
}

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatCallArgs_(struct IntIntTuple2 baseLoc_13, struct IntIntTuple2 calleeLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_121) {
    struct Token_IntIntTuple2Tuple2List* tokens_65 = arg_121.t0;
    struct StringIntIntTuple2Tuple2List* errors_42 = arg_121.t1;
    struct IntIntTuple2 call_497 = locMax_(baseLoc_13, calleeLoc_);
    struct IntIntTuple2 call_498 = locAddX_(1, call_497);
    struct IntIntTuple2 argBaseLoc_ = call_498;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_215;
    tuple_215.t0 = tokens_65;
    tuple_215.t1 = errors_42;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_499 = go_31(argBaseLoc_, baseLoc_13, NULL, tuple_215);
    return call_499;
}

struct APat_APat_ListIntIntTuple2Tuple3 {
    struct APat_ t0;
    struct APat_List* t1;
    struct IntIntTuple2 t2;
};

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatCall_(struct IntIntTuple2 baseLoc_14, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_122) {
    struct Token_IntIntTuple2Tuple2List* tokens_68 = arg_122.t0;
    struct StringIntIntTuple2Tuple2List* errors_45 = arg_122.t1;
    struct IntIntTuple2 call_500 = nextLoc_1(tokens_68);
    struct IntIntTuple2 calleeLoc_1 = call_500;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_216;
    tuple_216.t0 = tokens_68;
    tuple_216.t1 = errors_45;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_501 = parsePatNav_(baseLoc_14, tuple_216);
    struct APat_ callee_4 = call_501.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_69 = call_501.t1;
    struct StringIntIntTuple2Tuple2List* errors_46 = call_501.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_217;
    tuple_217.t0 = tokens_69;
    tuple_217.t1 = errors_46;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_502 = parsePatCallArgs_(baseLoc_14, calleeLoc_1, tuple_217);
    struct APat_List* args_6 = call_502.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_70 = call_502.t1;
    struct StringIntIntTuple2Tuple2List* errors_47 = call_502.t2;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_195;
    if ((!((!(args_6))))) goto next_765;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_218;
    tuple_218.t0 = callee_4;
    tuple_218.t1 = tokens_70;
    tuple_218.t2 = errors_47;
    match_195 = tuple_218;
    goto end_match_764;
next_765:;
    struct APat_APat_ListIntIntTuple2Tuple3 tuple_220;
    tuple_220.t0 = callee_4;
    tuple_220.t1 = args_6;
    tuple_220.t2 = calleeLoc_1;
    struct APat_APat_ListIntIntTuple2Tuple3* payload_100 = (struct APat_APat_ListIntIntTuple2Tuple3*)malloc(sizeof(struct APat_APat_ListIntIntTuple2Tuple3));
    (*(((struct APat_APat_ListIntIntTuple2Tuple3*)payload_100))) = tuple_220;
    struct APat_ variant_100 = (struct APat_){.tag = Call_, .Call_ = payload_100};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_219;
    tuple_219.t0 = variant_100;
    tuple_219.t1 = tokens_70;
    tuple_219.t2 = errors_47;
    match_195 = tuple_219;
    goto end_match_764;
next_766:;
end_match_764:;
    return match_195;
}

struct APat_APat_IntIntTuple2Tuple3 {
    struct APat_ t0;
    struct APat_ t1;
    struct IntIntTuple2 t2;
};

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatCons_(struct IntIntTuple2 baseLoc_15, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_123) {
    struct Token_IntIntTuple2Tuple2List* tokens_71 = arg_123.t0;
    struct StringIntIntTuple2Tuple2List* errors_48 = arg_123.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_221;
    tuple_221.t0 = tokens_71;
    tuple_221.t1 = errors_48;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_503 = parsePatCall_(baseLoc_15, tuple_221);
    struct APat_ head_2 = call_503.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_72 = call_503.t1;
    struct StringIntIntTuple2Tuple2List* errors_49 = call_503.t2;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_196;
    if ((!(tokens_72))) goto next_768;
    if ((tokens_72->head.t0.tag != ColonColon_)) goto next_768;
    struct IntIntTuple2 loc_48 = tokens_72->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_73 = tokens_72->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_222;
    tuple_222.t0 = tokens_73;
    tuple_222.t1 = errors_49;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_504 = parsePatCons_(baseLoc_15, tuple_222);
    struct APat_ tail_2 = call_504.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_74 = call_504.t1;
    struct StringIntIntTuple2Tuple2List* errors_50 = call_504.t2;
    struct APat_APat_IntIntTuple2Tuple3 tuple_224;
    tuple_224.t0 = head_2;
    tuple_224.t1 = tail_2;
    tuple_224.t2 = loc_48;
    struct APat_APat_IntIntTuple2Tuple3* payload_101 = (struct APat_APat_IntIntTuple2Tuple3*)malloc(sizeof(struct APat_APat_IntIntTuple2Tuple3));
    (*(((struct APat_APat_IntIntTuple2Tuple3*)payload_101))) = tuple_224;
    struct APat_ variant_101 = (struct APat_){.tag = Cons_2, .Cons_2 = payload_101};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_223;
    tuple_223.t0 = variant_101;
    tuple_223.t1 = tokens_74;
    tuple_223.t2 = errors_50;
    match_196 = tuple_223;
    goto end_match_767;
next_768:;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_225;
    tuple_225.t0 = head_2;
    tuple_225.t1 = tokens_72;
    tuple_225.t2 = errors_49;
    match_196 = tuple_225;
    goto end_match_767;
next_769:;
end_match_767:;
    return match_196;
}

struct APat_ATy_IntIntTuple2Tuple3 {
    struct APat_ t0;
    struct ATy_ t1;
    struct IntIntTuple2 t2;
};

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatAnno_(struct IntIntTuple2 baseLoc_16, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_124) {
    struct Token_IntIntTuple2Tuple2List* tokens_75 = arg_124.t0;
    struct StringIntIntTuple2Tuple2List* errors_51 = arg_124.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_226;
    tuple_226.t0 = tokens_75;
    tuple_226.t1 = errors_51;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_505 = parsePatCons_(baseLoc_16, tuple_226);
    struct APat_ pat_18 = call_505.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_76 = call_505.t1;
    struct StringIntIntTuple2Tuple2List* errors_52 = call_505.t2;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_197;
    if ((!(tokens_76))) goto next_771;
    if ((tokens_76->head.t0.tag != Colon_)) goto next_771;
    struct IntIntTuple2 loc_49 = tokens_76->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_77 = tokens_76->tail;
    struct IntIntTuple2 call_506 = nextLoc_1(tokens_77);
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_227;
    tuple_227.t0 = tokens_77;
    tuple_227.t1 = errors_52;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_507 = parseTy_(call_506, tuple_227);
    struct ATy_ ty_50 = call_507.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_78 = call_507.t1;
    struct StringIntIntTuple2Tuple2List* errors_53 = call_507.t2;
    struct APat_ATy_IntIntTuple2Tuple3 tuple_229;
    tuple_229.t0 = pat_18;
    tuple_229.t1 = ty_50;
    tuple_229.t2 = loc_49;
    struct APat_ATy_IntIntTuple2Tuple3* payload_102 = (struct APat_ATy_IntIntTuple2Tuple3*)malloc(sizeof(struct APat_ATy_IntIntTuple2Tuple3));
    (*(((struct APat_ATy_IntIntTuple2Tuple3*)payload_102))) = tuple_229;
    struct APat_ variant_102 = (struct APat_){.tag = Anno_, .Anno_ = payload_102};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_228;
    tuple_228.t0 = variant_102;
    tuple_228.t1 = tokens_78;
    tuple_228.t2 = errors_53;
    match_197 = tuple_228;
    goto end_match_770;
next_771:;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_230;
    tuple_230.t0 = pat_18;
    tuple_230.t1 = tokens_76;
    tuple_230.t2 = errors_52;
    match_197 = tuple_230;
    goto end_match_770;
next_772:;
end_match_770:;
    return match_197;
}

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_32(struct IntIntTuple2 baseLoc_17, struct APat_List* acc_19, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_125) {
    struct Token_IntIntTuple2Tuple2List* tokens_80 = arg_125.t0;
    struct StringIntIntTuple2Tuple2List* errors_55 = arg_125.t1;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_198;
    if ((!(tokens_80))) goto next_774;
    if ((tokens_80->head.t0.tag != Comma_)) goto next_774;
    struct Token_IntIntTuple2Tuple2List* tokens_81 = tokens_80->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_231;
    tuple_231.t0 = tokens_81;
    tuple_231.t1 = errors_55;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_508 = parsePatAnno_(baseLoc_17, tuple_231);
    struct APat_ second_3 = call_508.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_82 = call_508.t1;
    struct StringIntIntTuple2Tuple2List* errors_56 = call_508.t2;
    struct APat_List* list_63 = (struct APat_List*)malloc(sizeof(struct APat_List));
    list_63->head = second_3;
    list_63->tail = acc_19;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_232;
    tuple_232.t0 = tokens_82;
    tuple_232.t1 = errors_56;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_509 = go_32(baseLoc_17, list_63, tuple_232);
    match_198 = call_509;
    goto end_match_773;
next_774:;
    struct APat_List* call_510 = listRev_4(acc_19);
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_233;
    tuple_233.t0 = call_510;
    tuple_233.t1 = tokens_80;
    tuple_233.t2 = errors_55;
    match_198 = tuple_233;
    goto end_match_773;
next_775:;
end_match_773:;
    return match_198;
}

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatTuple_(struct IntIntTuple2 baseLoc_17, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_126) {
    struct Token_IntIntTuple2Tuple2List* tokens_79 = arg_126.t0;
    struct StringIntIntTuple2Tuple2List* errors_54 = arg_126.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_234;
    tuple_234.t0 = tokens_79;
    tuple_234.t1 = errors_54;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_511 = parsePatAnno_(baseLoc_17, tuple_234);
    struct APat_ itemPat_1 = call_511.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_83 = call_511.t1;
    struct StringIntIntTuple2Tuple2List* errors_57 = call_511.t2;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_199;
    if ((!(tokens_83))) goto next_777;
    if ((tokens_83->head.t0.tag != Comma_)) goto next_777;
    struct IntIntTuple2 loc_50 = tokens_83->head.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_235;
    tuple_235.t0 = tokens_83;
    tuple_235.t1 = errors_57;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_512 = go_32(baseLoc_17, NULL, tuple_235);
    struct APat_List* itemPats_2 = call_512.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_84 = call_512.t1;
    struct StringIntIntTuple2Tuple2List* errors_58 = call_512.t2;
    struct APat_List* list_64 = (struct APat_List*)malloc(sizeof(struct APat_List));
    list_64->head = itemPat_1;
    list_64->tail = itemPats_2;
    struct APat_ListIntIntTuple2Tuple2 tuple_237;
    tuple_237.t0 = list_64;
    tuple_237.t1 = loc_50;
    struct APat_ListIntIntTuple2Tuple2* payload_103 = (struct APat_ListIntIntTuple2Tuple2*)malloc(sizeof(struct APat_ListIntIntTuple2Tuple2));
    (*(((struct APat_ListIntIntTuple2Tuple2*)payload_103))) = tuple_237;
    struct APat_ variant_103 = (struct APat_){.tag = TupleLit_, .TupleLit_ = payload_103};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_236;
    tuple_236.t0 = variant_103;
    tuple_236.t1 = tokens_84;
    tuple_236.t2 = errors_58;
    match_199 = tuple_236;
    goto end_match_776;
next_777:;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_238;
    tuple_238.t0 = itemPat_1;
    tuple_238.t1 = tokens_83;
    tuple_238.t2 = errors_57;
    match_199 = tuple_238;
    goto end_match_776;
next_778:;
end_match_776:;
    return match_199;
}

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatAs_(struct IntIntTuple2 baseLoc_18, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_127) {
    struct Token_IntIntTuple2Tuple2List* tokens_85 = arg_127.t0;
    struct StringIntIntTuple2Tuple2List* errors_59 = arg_127.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_239;
    tuple_239.t0 = tokens_85;
    tuple_239.t1 = errors_59;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_513 = parsePatTuple_(baseLoc_18, tuple_239);
    struct APat_ pat_19 = call_513.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_86 = call_513.t1;
    struct StringIntIntTuple2Tuple2List* errors_60 = call_513.t2;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_200;
    if ((!(tokens_86))) goto next_780;
    if ((tokens_86->head.t0.tag != As_)) goto next_780;
    struct IntIntTuple2 loc_51 = tokens_86->head.t1;
    if ((!(tokens_86->tail))) goto next_780;
    if ((tokens_86->tail->head.t0.tag != Ident_)) goto next_780;
    struct String ident_21 = (*(tokens_86->tail->head.t0.Ident_));
    struct Token_IntIntTuple2Tuple2List* tokens_87 = tokens_86->tail->tail;
    struct APat_StringIntIntTuple2Tuple3 tuple_241;
    tuple_241.t0 = pat_19;
    tuple_241.t1 = ident_21;
    tuple_241.t2 = loc_51;
    struct APat_StringIntIntTuple2Tuple3* payload_104 = (struct APat_StringIntIntTuple2Tuple3*)malloc(sizeof(struct APat_StringIntIntTuple2Tuple3));
    (*(((struct APat_StringIntIntTuple2Tuple3*)payload_104))) = tuple_241;
    struct APat_ variant_104 = (struct APat_){.tag = As_1, .As_1 = payload_104};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_240;
    tuple_240.t0 = variant_104;
    tuple_240.t1 = tokens_87;
    tuple_240.t2 = errors_60;
    match_200 = tuple_240;
    goto end_match_779;
next_780:;
    if ((!(tokens_86))) goto next_781;
    if ((tokens_86->head.t0.tag != As_)) goto next_781;
    struct Token_IntIntTuple2Tuple2List* tokens_88 = tokens_86->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_242;
    tuple_242.t0 = tokens_88;
    tuple_242.t1 = errors_60;
    struct StringIntIntTuple2Tuple2List* call_514 = parseNewError_1((struct String){.str = "Expected an identifier", .len = 22}, tuple_242);
    struct StringIntIntTuple2Tuple2List* errors_61 = call_514;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_243;
    tuple_243.t0 = pat_19;
    tuple_243.t1 = tokens_88;
    tuple_243.t2 = errors_61;
    match_200 = tuple_243;
    goto end_match_779;
next_781:;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_244;
    tuple_244.t0 = pat_19;
    tuple_244.t1 = tokens_86;
    tuple_244.t2 = errors_60;
    match_200 = tuple_244;
    goto end_match_779;
next_782:;
end_match_779:;
    return match_200;
}

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatOr_(struct IntIntTuple2 baseLoc_19, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_128) {
    struct Token_IntIntTuple2Tuple2List* tokens_89 = arg_128.t0;
    struct StringIntIntTuple2Tuple2List* errors_62 = arg_128.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_245;
    tuple_245.t0 = tokens_89;
    tuple_245.t1 = errors_62;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_515 = parsePatAs_(baseLoc_19, tuple_245);
    struct APat_ lPat_ = call_515.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_90 = call_515.t1;
    struct StringIntIntTuple2Tuple2List* errors_63 = call_515.t2;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_201;
    if ((!(tokens_90))) goto next_784;
    if ((tokens_90->head.t0.tag != Pipe_)) goto next_784;
    struct IntIntTuple2 loc_52 = tokens_90->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_91 = tokens_90->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_246;
    tuple_246.t0 = tokens_91;
    tuple_246.t1 = errors_63;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_516 = parsePatOr_(baseLoc_19, tuple_246);
    struct APat_ rPat_ = call_516.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_92 = call_516.t1;
    struct StringIntIntTuple2Tuple2List* errors_64 = call_516.t2;
    struct APat_APat_IntIntTuple2Tuple3 tuple_248;
    tuple_248.t0 = lPat_;
    tuple_248.t1 = rPat_;
    tuple_248.t2 = loc_52;
    struct APat_APat_IntIntTuple2Tuple3* payload_105 = (struct APat_APat_IntIntTuple2Tuple3*)malloc(sizeof(struct APat_APat_IntIntTuple2Tuple3));
    (*(((struct APat_APat_IntIntTuple2Tuple3*)payload_105))) = tuple_248;
    struct APat_ variant_105 = (struct APat_){.tag = Or_2, .Or_2 = payload_105};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_247;
    tuple_247.t0 = variant_105;
    tuple_247.t1 = tokens_92;
    tuple_247.t2 = errors_64;
    match_201 = tuple_247;
    goto end_match_783;
next_784:;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_249;
    tuple_249.t0 = lPat_;
    tuple_249.t1 = tokens_90;
    tuple_249.t2 = errors_63;
    match_201 = tuple_249;
    goto end_match_783;
next_785:;
end_match_783:;
    return match_201;
}

struct StringAPat_ListIntIntTuple2Tuple3 {
    struct String t0;
    struct APat_List* t1;
    struct IntIntTuple2 t2;
};

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatLet_(struct IntIntTuple2 baseLoc_20, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_129) {
    struct Token_IntIntTuple2Tuple2List* tokens_93 = arg_129.t0;
    struct StringIntIntTuple2Tuple2List* errors_65 = arg_129.t1;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_202;
    if ((!(tokens_93))) goto next_787;
    if ((tokens_93->head.t0.tag != Ident_)) goto next_787;
    struct String callee_5 = (*(tokens_93->head.t0.Ident_));
    struct IntIntTuple2 calleeLoc_2 = tokens_93->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_94 = tokens_93->tail;
    int match_203;
    int call_517 = locInside_(baseLoc_20, calleeLoc_2);
    if ((!(call_517))) goto next_790;
    int call_518 = leadsPat_1(tokens_94);
    match_203 = call_518;
    goto end_match_789;
next_790:;
    if (call_517) goto next_791;
    match_203 = 0;
    goto end_match_789;
next_791:;
    exit(1);
end_match_789:;
    if ((!(match_203))) goto next_787;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_250;
    tuple_250.t0 = tokens_94;
    tuple_250.t1 = errors_65;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_519 = parsePatCallArgs_(baseLoc_20, calleeLoc_2, tuple_250);
    struct APat_List* args_7 = call_519.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_95 = call_519.t1;
    struct StringIntIntTuple2Tuple2List* errors_66 = call_519.t2;
    struct StringAPat_ListIntIntTuple2Tuple3 tuple_251;
    tuple_251.t0 = callee_5;
    tuple_251.t1 = args_7;
    tuple_251.t2 = calleeLoc_2;
    struct StringAPat_ListIntIntTuple2Tuple3* payload_106 = (struct StringAPat_ListIntIntTuple2Tuple3*)malloc(sizeof(struct StringAPat_ListIntIntTuple2Tuple3));
    (*(((struct StringAPat_ListIntIntTuple2Tuple3*)payload_106))) = tuple_251;
    struct APat_ variant_106 = (struct APat_){.tag = Fun_2, .Fun_2 = payload_106};
    struct APat_ pat_20 = variant_106;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_204;
    if ((!(tokens_95))) goto next_793;
    if ((tokens_95->head.t0.tag != Colon_)) goto next_793;
    struct IntIntTuple2 loc_53 = tokens_95->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_96 = tokens_95->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_252;
    tuple_252.t0 = tokens_96;
    tuple_252.t1 = errors_66;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_520 = parseTy_(baseLoc_20, tuple_252);
    struct ATy_ ty_51 = call_520.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_97 = call_520.t1;
    struct StringIntIntTuple2Tuple2List* errors_67 = call_520.t2;
    struct APat_ATy_IntIntTuple2Tuple3 tuple_254;
    tuple_254.t0 = pat_20;
    tuple_254.t1 = ty_51;
    tuple_254.t2 = loc_53;
    struct APat_ATy_IntIntTuple2Tuple3* payload_107 = (struct APat_ATy_IntIntTuple2Tuple3*)malloc(sizeof(struct APat_ATy_IntIntTuple2Tuple3));
    (*(((struct APat_ATy_IntIntTuple2Tuple3*)payload_107))) = tuple_254;
    struct APat_ variant_107 = (struct APat_){.tag = Anno_, .Anno_ = payload_107};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_253;
    tuple_253.t0 = variant_107;
    tuple_253.t1 = tokens_97;
    tuple_253.t2 = errors_67;
    match_204 = tuple_253;
    goto end_match_792;
next_793:;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_255;
    tuple_255.t0 = pat_20;
    tuple_255.t1 = tokens_95;
    tuple_255.t2 = errors_66;
    match_204 = tuple_255;
    goto end_match_792;
next_794:;
end_match_792:;
    match_202 = match_204;
    goto end_match_786;
next_787:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_256;
    tuple_256.t0 = tokens_93;
    tuple_256.t1 = errors_65;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_521 = parsePat_(baseLoc_20, tuple_256);
    match_202 = call_521;
    goto end_match_786;
next_788:;
end_match_786:;
    return match_202;
}

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePat_(struct IntIntTuple2 baseLoc_21, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_130) {
    struct Token_IntIntTuple2Tuple2List* tokens_98 = arg_130.t0;
    struct StringIntIntTuple2Tuple2List* errors_68 = arg_130.t1;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_205;
    int match_206;
    int call_522 = nextInside_1(baseLoc_21, tokens_98);
    if ((!(call_522))) goto next_797;
    int call_523 = leadsPat_1(tokens_98);
    match_206 = call_523;
    goto end_match_796;
next_797:;
    if (call_522) goto next_798;
    match_206 = 0;
    goto end_match_796;
next_798:;
    exit(1);
end_match_796:;
    if (match_206) goto next_799;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_257;
    tuple_257.t0 = tokens_98;
    tuple_257.t1 = errors_68;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_524 = parsePatError_1((struct String){.str = "Expected a pattern", .len = 18}, tuple_257);
    match_205 = call_524;
    goto end_match_795;
next_799:;
    if ((!(match_206))) goto next_800;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_258;
    tuple_258.t0 = tokens_98;
    tuple_258.t1 = errors_68;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_525 = parsePatOr_(baseLoc_21, tuple_258);
    match_205 = call_525;
    goto end_match_795;
next_800:;
    exit(1);
end_match_795:;
    return match_205;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseRange_(struct IntIntTuple2 baseLoc_22, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_131) {
    struct Token_IntIntTuple2Tuple2List* tokens_99 = arg_131.t0;
    struct StringIntIntTuple2Tuple2List* errors_69 = arg_131.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_259;
    tuple_259.t0 = tokens_99;
    tuple_259.t1 = errors_69;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_526 = parseExpr_(baseLoc_22, tuple_259);
    struct AExpr_ l_15 = call_526.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_100 = call_526.t1;
    struct StringIntIntTuple2Tuple2List* errors_70 = call_526.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_207;
    if ((!(tokens_100))) goto next_802;
    if ((tokens_100->head.t0.tag != DotDot_)) goto next_802;
    struct IntIntTuple2 loc_54 = tokens_100->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_101 = tokens_100->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_260;
    tuple_260.t0 = tokens_101;
    tuple_260.t1 = errors_70;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_527 = parseExpr_(baseLoc_22, tuple_260);
    struct AExpr_ r_28 = call_527.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_102 = call_527.t1;
    struct StringIntIntTuple2Tuple2List* errors_71 = call_527.t2;
    struct AExpr_List* list_66 = (struct AExpr_List*)malloc(sizeof(struct AExpr_List));
    list_66->head = r_28;
    list_66->tail = NULL;
    struct AExpr_List* list_65 = (struct AExpr_List*)malloc(sizeof(struct AExpr_List));
    list_65->head = l_15;
    list_65->tail = list_66;
    struct AExpr_ListIntIntTuple2Tuple2 tuple_262;
    tuple_262.t0 = list_65;
    tuple_262.t1 = loc_54;
    struct AExpr_ListIntIntTuple2Tuple2* payload_108 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_108))) = tuple_262;
    struct AExpr_ variant_108 = (struct AExpr_){.tag = Range_, .Range_ = payload_108};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_261;
    tuple_261.t0 = variant_108;
    tuple_261.t1 = tokens_102;
    tuple_261.t2 = errors_71;
    match_207 = tuple_261;
    goto end_match_801;
next_802:;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_263;
    tuple_263.t0 = l_15;
    tuple_263.t1 = tokens_100;
    tuple_263.t2 = errors_70;
    match_207 = tuple_263;
    goto end_match_801;
next_803:;
end_match_801:;
    return match_207;
}

struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct AExpr_List* t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseList_(struct IntIntTuple2 baseLoc_23, struct IntIntTuple2 bracketLoc_1, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_132) {
    struct Token_IntIntTuple2Tuple2List* tokens_103 = arg_132.t0;
    struct StringIntIntTuple2Tuple2List* errors_72 = arg_132.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_264;
    tuple_264.t0 = tokens_103;
    tuple_264.t1 = errors_72;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_528 = parseStmts_(baseLoc_23, tuple_264);
    struct AExpr_List* items_5 = call_528.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_104 = call_528.t1;
    struct StringIntIntTuple2Tuple2List* errors_73 = call_528.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 match_208;
    if ((!(tokens_104))) goto next_805;
    if ((tokens_104->head.t0.tag != BracketR_)) goto next_805;
    struct Token_IntIntTuple2Tuple2List* tokens_106 = tokens_104->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_265;
    tuple_265.t0 = tokens_106;
    tuple_265.t1 = errors_73;
    match_208 = tuple_265;
    goto end_match_804;
next_805:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_266;
    tuple_266.t0 = tokens_104;
    tuple_266.t1 = errors_73;
    struct StringIntIntTuple2Tuple2List* call_529 = parseNewError_1((struct String){.str = "Expected ']'", .len = 12}, tuple_266);
    struct StringIntIntTuple2Tuple2List* errors_75 = call_529;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_267;
    tuple_267.t0 = tokens_104;
    tuple_267.t1 = errors_75;
    match_208 = tuple_267;
    goto end_match_804;
next_806:;
end_match_804:;
    struct Token_IntIntTuple2Tuple2List* tokens_105 = match_208.t0;
    struct StringIntIntTuple2Tuple2List* errors_74 = match_208.t1;
    struct AExpr_ListIntIntTuple2Tuple2 tuple_269;
    tuple_269.t0 = items_5;
    tuple_269.t1 = bracketLoc_1;
    struct AExpr_ListIntIntTuple2Tuple2* payload_109 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_109))) = tuple_269;
    struct AExpr_ variant_109 = (struct AExpr_){.tag = ListLit_1, .ListLit_1 = payload_109};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_268;
    tuple_268.t0 = variant_109;
    tuple_268.t1 = tokens_105;
    tuple_268.t2 = errors_74;
    return tuple_268;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseThenClause_(struct IntIntTuple2 baseLoc_24, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_133) {
    struct Token_IntIntTuple2Tuple2List* tokens_107 = arg_133.t0;
    struct StringIntIntTuple2Tuple2List* errors_76 = arg_133.t1;
    struct IntIntTuple2 call_530 = locAddX_(1, baseLoc_24);
    struct IntIntTuple2 innerBaseLoc_ = call_530;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_209;
    if ((!(tokens_107))) goto next_808;
    if ((tokens_107->head.t0.tag != Then_)) goto next_808;
    struct IntIntTuple2 thenLoc_ = tokens_107->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_108 = tokens_107->tail;
    int call_531 = locInside_(baseLoc_24, thenLoc_);
    if ((!(call_531))) goto next_808;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_270;
    tuple_270.t0 = tokens_108;
    tuple_270.t1 = errors_76;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_532 = parseSemi_(innerBaseLoc_, thenLoc_, tuple_270);
    match_209 = call_532;
    goto end_match_807;
next_808:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_271;
    tuple_271.t0 = tokens_107;
    tuple_271.t1 = errors_76;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_533 = parseExprError_1((struct String){.str = "Expected 'then'", .len = 15}, tuple_271);
    match_209 = call_533;
    goto end_match_807;
next_809:;
end_match_807:;
    return match_209;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseElseClause_(struct IntIntTuple2 baseLoc_25, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_134) {
    struct Token_IntIntTuple2Tuple2List* tokens_109 = arg_134.t0;
    struct StringIntIntTuple2Tuple2List* errors_77 = arg_134.t1;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_210;
    if ((!(tokens_109))) goto next_811;
    if ((tokens_109->head.t0.tag != Else_)) goto next_811;
    struct IntIntTuple2 elseLoc_ = tokens_109->head.t1;
    if ((!(tokens_109->tail))) goto next_811;
    if ((tokens_109->tail->head.t0.tag != If_)) goto next_811;
    struct IntIntTuple2 nextIfLoc_ = tokens_109->tail->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_110 = tokens_109->tail->tail;
    int match_211;
    int call_534 = locInside_(baseLoc_25, elseLoc_);
    if ((!(call_534))) goto next_815;
    int call_535 = locIsSameRow_(elseLoc_, nextIfLoc_);
    match_211 = call_535;
    goto end_match_814;
next_815:;
    if (call_534) goto next_816;
    match_211 = 0;
    goto end_match_814;
next_816:;
    exit(1);
end_match_814:;
    if ((!(match_211))) goto next_811;
    struct Token_IntIntTuple2Tuple2 tuple_273;
    tuple_273.t0 = (struct Token_){.tag = If_};
    tuple_273.t1 = elseLoc_;
    struct Token_IntIntTuple2Tuple2List* list_67 = (struct Token_IntIntTuple2Tuple2List*)malloc(sizeof(struct Token_IntIntTuple2Tuple2List));
    list_67->head = tuple_273;
    list_67->tail = tokens_110;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_272;
    tuple_272.t0 = list_67;
    tuple_272.t1 = errors_77;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_536 = parseExpr_(baseLoc_25, tuple_272);
    match_210 = call_536;
    goto end_match_810;
next_811:;
    if ((!(tokens_109))) goto next_812;
    if ((tokens_109->head.t0.tag != Else_)) goto next_812;
    struct IntIntTuple2 elseLoc_1 = tokens_109->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_111 = tokens_109->tail;
    int call_537 = locInside_(baseLoc_25, elseLoc_1);
    if ((!(call_537))) goto next_812;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_274;
    tuple_274.t0 = tokens_111;
    tuple_274.t1 = errors_77;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_538 = parseSemi_(baseLoc_25, elseLoc_1, tuple_274);
    match_210 = call_538;
    goto end_match_810;
next_812:;
    struct IntIntTuple2* payload_110 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_110))) = baseLoc_25;
    struct AExpr_ variant_110 = (struct AExpr_){.tag = Missing_2, .Missing_2 = payload_110};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_275;
    tuple_275.t0 = variant_110;
    tuple_275.t1 = tokens_109;
    tuple_275.t2 = errors_77;
    match_210 = tuple_275;
    goto end_match_810;
next_813:;
end_match_810:;
    return match_210;
}

struct AExpr_AExpr_AExpr_IntIntTuple2Tuple4 {
    struct AExpr_ t0;
    struct AExpr_ t1;
    struct AExpr_ t2;
    struct IntIntTuple2 t3;
};

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseIf_(struct IntIntTuple2 ifLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_135) {
    struct Token_IntIntTuple2Tuple2List* tokens_112 = arg_135.t0;
    struct StringIntIntTuple2Tuple2List* errors_78 = arg_135.t1;
    struct IntIntTuple2 call_539 = locAddX_(1, ifLoc_);
    struct IntIntTuple2 innerBaseLoc_1 = call_539;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_276;
    tuple_276.t0 = tokens_112;
    tuple_276.t1 = errors_78;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_540 = parseExpr_(innerBaseLoc_1, tuple_276);
    struct AExpr_ cond_1 = call_540.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_113 = call_540.t1;
    struct StringIntIntTuple2Tuple2List* errors_79 = call_540.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_277;
    tuple_277.t0 = tokens_113;
    tuple_277.t1 = errors_79;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_541 = parseThenClause_(ifLoc_, tuple_277);
    struct AExpr_ body_7 = call_541.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_114 = call_541.t1;
    struct StringIntIntTuple2Tuple2List* errors_80 = call_541.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_278;
    tuple_278.t0 = tokens_114;
    tuple_278.t1 = errors_80;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_542 = parseElseClause_(ifLoc_, tuple_278);
    struct AExpr_ alt_1 = call_542.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_115 = call_542.t1;
    struct StringIntIntTuple2Tuple2List* errors_81 = call_542.t2;
    struct AExpr_AExpr_AExpr_IntIntTuple2Tuple4 tuple_280;
    tuple_280.t0 = cond_1;
    tuple_280.t1 = body_7;
    tuple_280.t2 = alt_1;
    tuple_280.t3 = ifLoc_;
    struct AExpr_AExpr_AExpr_IntIntTuple2Tuple4* payload_111 = (struct AExpr_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct AExpr_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct AExpr_AExpr_AExpr_IntIntTuple2Tuple4*)payload_111))) = tuple_280;
    struct AExpr_ variant_111 = (struct AExpr_){.tag = If_1, .If_1 = payload_111};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_279;
    tuple_279.t0 = variant_111;
    tuple_279.t1 = tokens_115;
    tuple_279.t2 = errors_81;
    return tuple_279;
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

struct AArm_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseMatchArm_(struct IntIntTuple2 matchLoc_, struct IntIntTuple2 armLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_136) {
    struct Token_IntIntTuple2Tuple2List* tokens_116 = arg_136.t0;
    struct StringIntIntTuple2Tuple2List* errors_82 = arg_136.t1;
    struct IntIntTuple2 call_543 = locAddX_(1, matchLoc_);
    struct IntIntTuple2 innerBaseLoc_2 = call_543;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_281;
    tuple_281.t0 = tokens_116;
    tuple_281.t1 = errors_82;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_544 = parsePat_(innerBaseLoc_2, tuple_281);
    struct APat_ pat_21 = call_544.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_117 = call_544.t1;
    struct StringIntIntTuple2Tuple2List* errors_83 = call_544.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_212;
    if ((!(tokens_117))) goto next_818;
    if ((tokens_117->head.t0.tag != When_)) goto next_818;
    struct Token_IntIntTuple2Tuple2List* tokens_119 = tokens_117->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_282;
    tuple_282.t0 = tokens_119;
    tuple_282.t1 = errors_83;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_545 = parseExpr_(innerBaseLoc_2, tuple_282);
    match_212 = call_545;
    goto end_match_817;
next_818:;
    struct IntIntTuple2 call_546 = nextLoc_1(tokens_117);
    struct IntIntTuple2* payload_112 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_112))) = call_546;
    struct AExpr_ variant_112 = (struct AExpr_){.tag = Missing_2, .Missing_2 = payload_112};
    struct AExpr_ guard_3 = variant_112;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_283;
    tuple_283.t0 = guard_3;
    tuple_283.t1 = tokens_117;
    tuple_283.t2 = errors_83;
    match_212 = tuple_283;
    goto end_match_817;
next_819:;
end_match_817:;
    struct AExpr_ guard_2 = match_212.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_118 = match_212.t1;
    struct StringIntIntTuple2Tuple2List* errors_84 = match_212.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_213;
    if ((!(tokens_118))) goto next_821;
    if ((tokens_118->head.t0.tag != Arrow_)) goto next_821;
    struct IntIntTuple2 arrowLoc_ = tokens_118->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_121 = tokens_118->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_284;
    tuple_284.t0 = tokens_121;
    tuple_284.t1 = errors_84;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_547 = parseSemi_(matchLoc_, arrowLoc_, tuple_284);
    match_213 = call_547;
    goto end_match_820;
next_821:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_285;
    tuple_285.t0 = tokens_118;
    tuple_285.t1 = errors_84;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_548 = parseExprError_1((struct String){.str = "Expected '->'", .len = 13}, tuple_285);
    match_213 = call_548;
    goto end_match_820;
next_822:;
end_match_820:;
    struct AExpr_ body_8 = match_213.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_120 = match_213.t1;
    struct StringIntIntTuple2Tuple2List* errors_85 = match_213.t2;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4 tuple_287;
    tuple_287.t0 = pat_21;
    tuple_287.t1 = guard_2;
    tuple_287.t2 = body_8;
    tuple_287.t3 = armLoc_;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4* payload_113 = (struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct APat_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)payload_113))) = tuple_287;
    struct AArm_ variant_113 = (struct AArm_){.tag = AArm_, .AArm_ = payload_113};
    struct AArm_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_286;
    tuple_286.t0 = variant_113;
    tuple_286.t1 = tokens_120;
    tuple_286.t2 = errors_85;
    return tuple_286;
}

struct AArm_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct AArm_List* t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct AArm_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_33(struct IntIntTuple2 matchLoc_1, struct AArm_List* acc_20, struct IntIntTuple2 armLoc_2, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_137) {
    struct Token_IntIntTuple2Tuple2List* tokens_127 = arg_137.t0;
    struct StringIntIntTuple2Tuple2List* errors_90 = arg_137.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_288;
    tuple_288.t0 = tokens_127;
    tuple_288.t1 = errors_90;
    struct AArm_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_549 = parseMatchArm_(matchLoc_1, armLoc_2, tuple_288);
    struct AArm_ arm_ = call_549.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_128 = call_549.t1;
    struct StringIntIntTuple2Tuple2List* errors_91 = call_549.t2;
    struct AArm_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_214;
    if ((!(tokens_128))) goto next_824;
    if ((tokens_128->head.t0.tag != Pipe_)) goto next_824;
    struct IntIntTuple2 pipeLoc_1 = tokens_128->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_129 = tokens_128->tail;
    int call_550 = locInside_(matchLoc_1, pipeLoc_1);
    if ((!(call_550))) goto next_824;
    struct AArm_List* list_68 = (struct AArm_List*)malloc(sizeof(struct AArm_List));
    list_68->head = arm_;
    list_68->tail = acc_20;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_289;
    tuple_289.t0 = tokens_129;
    tuple_289.t1 = errors_91;
    struct AArm_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_551 = go_33(matchLoc_1, list_68, pipeLoc_1, tuple_289);
    match_214 = call_551;
    goto end_match_823;
next_824:;
    struct AArm_List* list_69 = (struct AArm_List*)malloc(sizeof(struct AArm_List));
    list_69->head = arm_;
    list_69->tail = acc_20;
    struct AArm_List* call_552 = listRev_3(list_69);
    struct AArm_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_290;
    tuple_290.t0 = call_552;
    tuple_290.t1 = tokens_128;
    tuple_290.t2 = errors_91;
    match_214 = tuple_290;
    goto end_match_823;
next_825:;
end_match_823:;
    return match_214;
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

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseMatch_(struct IntIntTuple2 matchLoc_1, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_138) {
    struct Token_IntIntTuple2Tuple2List* tokens_122 = arg_138.t0;
    struct StringIntIntTuple2Tuple2List* errors_86 = arg_138.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_291;
    tuple_291.t0 = tokens_122;
    tuple_291.t1 = errors_86;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_553 = parseExpr_(matchLoc_1, tuple_291);
    struct AExpr_ target_2 = call_553.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_123 = call_553.t1;
    struct StringIntIntTuple2Tuple2List* errors_87 = call_553.t2;
    struct IntIntTuple2Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_215;
    if ((!(tokens_123))) goto next_827;
    if ((tokens_123->head.t0.tag != With_)) goto next_827;
    if ((!(tokens_123->tail))) goto next_827;
    if ((tokens_123->tail->head.t0.tag != Pipe_)) goto next_827;
    struct IntIntTuple2 pipeLoc_ = tokens_123->tail->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_125 = tokens_123->tail->tail;
    struct IntIntTuple2Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_292;
    tuple_292.t0 = pipeLoc_;
    tuple_292.t1 = tokens_125;
    tuple_292.t2 = errors_87;
    match_215 = tuple_292;
    goto end_match_826;
next_827:;
    if ((!(tokens_123))) goto next_828;
    if ((tokens_123->head.t0.tag != With_)) goto next_828;
    struct IntIntTuple2 withLoc_ = tokens_123->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_126 = tokens_123->tail;
    struct IntIntTuple2Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_293;
    tuple_293.t0 = withLoc_;
    tuple_293.t1 = tokens_126;
    tuple_293.t2 = errors_87;
    match_215 = tuple_293;
    goto end_match_826;
next_828:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_294;
    tuple_294.t0 = tokens_123;
    tuple_294.t1 = errors_87;
    struct StringIntIntTuple2Tuple2List* call_554 = parseNewError_1((struct String){.str = "Expected 'with'", .len = 15}, tuple_294);
    struct StringIntIntTuple2Tuple2List* errors_89 = call_554;
    struct IntIntTuple2Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_295;
    tuple_295.t0 = matchLoc_1;
    tuple_295.t1 = tokens_123;
    tuple_295.t2 = errors_89;
    match_215 = tuple_295;
    goto end_match_826;
next_829:;
end_match_826:;
    struct IntIntTuple2 armLoc_1 = match_215.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_124 = match_215.t1;
    struct StringIntIntTuple2Tuple2List* errors_88 = match_215.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_296;
    tuple_296.t0 = tokens_124;
    tuple_296.t1 = errors_88;
    struct AArm_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_555 = go_33(matchLoc_1, NULL, armLoc_1, tuple_296);
    struct AArm_List* arms_3 = call_555.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_130 = call_555.t1;
    struct StringIntIntTuple2Tuple2List* errors_92 = call_555.t2;
    struct AExpr_AArm_ListIntIntTuple2Tuple3 tuple_298;
    tuple_298.t0 = target_2;
    tuple_298.t1 = arms_3;
    tuple_298.t2 = matchLoc_1;
    struct AExpr_AArm_ListIntIntTuple2Tuple3* payload_114 = (struct AExpr_AArm_ListIntIntTuple2Tuple3*)malloc(sizeof(struct AExpr_AArm_ListIntIntTuple2Tuple3));
    (*(((struct AExpr_AArm_ListIntIntTuple2Tuple3*)payload_114))) = tuple_298;
    struct AExpr_ variant_114 = (struct AExpr_){.tag = Match_1, .Match_1 = payload_114};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_297;
    tuple_297.t0 = variant_114;
    tuple_297.t1 = tokens_130;
    tuple_297.t2 = errors_92;
    return tuple_297;
}

struct APat_ListAExpr_IntIntTuple2Tuple3 {
    struct APat_List* t0;
    struct AExpr_ t1;
    struct IntIntTuple2 t2;
};

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseFun_(struct IntIntTuple2 baseLoc_26, struct IntIntTuple2 funLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_139) {
    struct Token_IntIntTuple2Tuple2List* tokens_131 = arg_139.t0;
    struct StringIntIntTuple2Tuple2List* errors_93 = arg_139.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_299;
    tuple_299.t0 = tokens_131;
    tuple_299.t1 = errors_93;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_556 = parsePatCallArgs_(baseLoc_26, funLoc_, tuple_299);
    struct APat_List* pats_3 = call_556.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_132 = call_556.t1;
    struct StringIntIntTuple2Tuple2List* errors_94 = call_556.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_216;
    if ((!(tokens_132))) goto next_831;
    if ((tokens_132->head.t0.tag != Arrow_)) goto next_831;
    struct IntIntTuple2 arrowLoc_1 = tokens_132->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_134 = tokens_132->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_300;
    tuple_300.t0 = tokens_134;
    tuple_300.t1 = errors_94;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_557 = parseSemi_(baseLoc_26, arrowLoc_1, tuple_300);
    match_216 = call_557;
    goto end_match_830;
next_831:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_301;
    tuple_301.t0 = tokens_132;
    tuple_301.t1 = errors_94;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_558 = parseExprError_1((struct String){.str = "Missing '->'", .len = 12}, tuple_301);
    match_216 = call_558;
    goto end_match_830;
next_832:;
end_match_830:;
    struct AExpr_ body_9 = match_216.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_133 = match_216.t1;
    struct StringIntIntTuple2Tuple2List* errors_95 = match_216.t2;
    struct APat_ListAExpr_IntIntTuple2Tuple3 tuple_303;
    tuple_303.t0 = pats_3;
    tuple_303.t1 = body_9;
    tuple_303.t2 = funLoc_;
    struct APat_ListAExpr_IntIntTuple2Tuple3* payload_115 = (struct APat_ListAExpr_IntIntTuple2Tuple3*)malloc(sizeof(struct APat_ListAExpr_IntIntTuple2Tuple3));
    (*(((struct APat_ListAExpr_IntIntTuple2Tuple3*)payload_115))) = tuple_303;
    struct AExpr_ variant_115 = (struct AExpr_){.tag = Fun_3, .Fun_3 = payload_115};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_302;
    tuple_302.t0 = variant_115;
    tuple_302.t1 = tokens_133;
    tuple_302.t2 = errors_95;
    return tuple_302;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseParenBody_(struct IntIntTuple2 baseLoc_27, struct IntIntTuple2 parenLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_140) {
    struct Token_IntIntTuple2Tuple2List* tokens_135 = arg_140.t0;
    struct StringIntIntTuple2Tuple2List* errors_96 = arg_140.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_304;
    tuple_304.t0 = tokens_135;
    tuple_304.t1 = errors_96;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_559 = parseSemi_(baseLoc_27, parenLoc_, tuple_304);
    struct AExpr_ body_10 = call_559.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_136 = call_559.t1;
    struct StringIntIntTuple2Tuple2List* errors_97 = call_559.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_217;
    if ((!(tokens_136))) goto next_834;
    if ((tokens_136->head.t0.tag != ParenR_)) goto next_834;
    struct Token_IntIntTuple2Tuple2List* tokens_137 = tokens_136->tail;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_305;
    tuple_305.t0 = body_10;
    tuple_305.t1 = tokens_137;
    tuple_305.t2 = errors_97;
    match_217 = tuple_305;
    goto end_match_833;
next_834:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_306;
    tuple_306.t0 = tokens_136;
    tuple_306.t1 = errors_97;
    struct StringIntIntTuple2Tuple2List* call_560 = parseNewError_1((struct String){.str = "Expected ')'", .len = 12}, tuple_306);
    struct StringIntIntTuple2Tuple2List* errors_98 = call_560;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_307;
    tuple_307.t0 = body_10;
    tuple_307.t1 = tokens_136;
    tuple_307.t2 = errors_98;
    match_217 = tuple_307;
    goto end_match_833;
next_835:;
end_match_833:;
    return match_217;
}

struct Token_IntIntTuple2Tuple2List* parseAccessModifier_1(struct Token_IntIntTuple2Tuple2List* tokens_138) {
    struct Token_IntIntTuple2Tuple2List* match_218;
    if ((!(tokens_138))) goto next_837;
    struct Token_ t_11 = tokens_138->head.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_139 = tokens_138->tail;
    int call_561 = tokenIsAccessModifier_(t_11);
    if ((!(call_561))) goto next_837;
    match_218 = tokens_139;
    goto end_match_836;
next_837:;
    match_218 = tokens_138;
    goto end_match_836;
next_838:;
end_match_836:;
    return match_218;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseLet_(struct IntIntTuple2 letLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_141) {
    struct Token_IntIntTuple2Tuple2List* tokens_140 = arg_141.t0;
    struct StringIntIntTuple2Tuple2List* errors_99 = arg_141.t1;
    struct IntIntTuple2 call_562 = locAddX_(1, letLoc_);
    struct IntIntTuple2 innerBaseLoc_3 = call_562;
    struct Token_IntIntTuple2Tuple2List* call_563 = parseAccessModifier_1(tokens_140);
    struct Token_IntIntTuple2Tuple2List* tokens_141 = call_563;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_308;
    tuple_308.t0 = tokens_141;
    tuple_308.t1 = errors_99;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_564 = parsePatLet_(innerBaseLoc_3, tuple_308);
    struct APat_ pat_22 = call_564.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_142 = call_564.t1;
    struct StringIntIntTuple2Tuple2List* errors_100 = call_564.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_219;
    if ((!(tokens_142))) goto next_840;
    if ((tokens_142->head.t0.tag != Eq_)) goto next_840;
    struct IntIntTuple2 eqLoc_ = tokens_142->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_144 = tokens_142->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_309;
    tuple_309.t0 = tokens_144;
    tuple_309.t1 = errors_100;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_565 = parseSemi_(innerBaseLoc_3, eqLoc_, tuple_309);
    match_219 = call_565;
    goto end_match_839;
next_840:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_310;
    tuple_310.t0 = tokens_142;
    tuple_310.t1 = errors_100;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_566 = parseExprError_1((struct String){.str = "Missing '='", .len = 11}, tuple_310);
    match_219 = call_566;
    goto end_match_839;
next_841:;
end_match_839:;
    struct AExpr_ body_11 = match_219.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_143 = match_219.t1;
    struct StringIntIntTuple2Tuple2List* errors_101 = match_219.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_220;
    if ((!(tokens_143))) goto next_843;
    if ((tokens_143->head.t0.tag != In_)) goto next_843;
    struct IntIntTuple2 inLoc_ = tokens_143->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_146 = tokens_143->tail;
    int call_567 = locInside_(letLoc_, inLoc_);
    if ((!(call_567))) goto next_843;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_311;
    tuple_311.t0 = tokens_146;
    tuple_311.t1 = errors_101;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_568 = parseSemi_(letLoc_, inLoc_, tuple_311);
    match_220 = call_568;
    goto end_match_842;
next_843:;
    if ((!(tokens_143))) goto next_844;
    struct IntIntTuple2 call_569 = nextLoc_1(tokens_143);
    int call_570 = locIsSameColumn_(call_569, letLoc_);
    if ((!(call_570))) goto next_844;
    struct IntIntTuple2 call_571 = nextLoc_1(tokens_143);
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_312;
    tuple_312.t0 = tokens_143;
    tuple_312.t1 = errors_101;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_572 = parseSemi_(letLoc_, call_571, tuple_312);
    match_220 = call_572;
    goto end_match_842;
next_844:;
    struct Token_IntIntTuple2Tuple2List* tokens_147 = tokens_143;
    struct AExpr_ListIntIntTuple2Tuple2 tuple_314;
    tuple_314.t0 = NULL;
    tuple_314.t1 = letLoc_;
    struct AExpr_ListIntIntTuple2Tuple2* payload_116 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_116))) = tuple_314;
    struct AExpr_ variant_116 = (struct AExpr_){.tag = TupleLit_1, .TupleLit_1 = payload_116};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_313;
    tuple_313.t0 = variant_116;
    tuple_313.t1 = tokens_147;
    tuple_313.t2 = errors_101;
    match_220 = tuple_313;
    goto end_match_842;
next_845:;
end_match_842:;
    struct AExpr_ next_9 = match_220.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_145 = match_220.t1;
    struct StringIntIntTuple2Tuple2List* errors_102 = match_220.t2;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4 tuple_316;
    tuple_316.t0 = pat_22;
    tuple_316.t1 = body_11;
    tuple_316.t2 = next_9;
    tuple_316.t3 = letLoc_;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4* payload_117 = (struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct APat_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)payload_117))) = tuple_316;
    struct AExpr_ variant_117 = (struct AExpr_){.tag = Let_1, .Let_1 = payload_117};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_315;
    tuple_315.t0 = variant_117;
    tuple_315.t1 = tokens_145;
    tuple_315.t2 = errors_102;
    return tuple_315;
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

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyDecl_(struct IntIntTuple2 typeLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_142) {
    struct Token_IntIntTuple2Tuple2List* tokens_148 = arg_142.t0;
    struct StringIntIntTuple2Tuple2List* errors_103 = arg_142.t1;
    struct IntIntTuple2 call_573 = locAddX_(1, typeLoc_);
    struct IntIntTuple2 baseLoc_28 = call_573;
    struct Token_IntIntTuple2Tuple2List* call_574 = parseAccessModifier_1(tokens_148);
    struct Token_IntIntTuple2Tuple2List* tokens_149 = call_574;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_221;
    if ((!(tokens_149))) goto next_847;
    if ((tokens_149->head.t0.tag != Ident_)) goto next_847;
    struct String tyIdent_ = (*(tokens_149->head.t0.Ident_));
    struct Token_IntIntTuple2Tuple2List* tokens_150 = tokens_149->tail;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_222;
    if ((!(tokens_150))) goto next_850;
    if ((tokens_150->head.t0.tag != Eq_)) goto next_850;
    struct Token_IntIntTuple2Tuple2List* tokens_151 = tokens_150->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_317;
    tuple_317.t0 = tokens_151;
    tuple_317.t1 = errors_103;
    struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_575 = parseTyDeclBody_(baseLoc_28, tuple_317);
    struct ATyDecl_ tyDecl_ = call_575.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_152 = call_575.t1;
    struct StringIntIntTuple2Tuple2List* errors_104 = call_575.t2;
    struct AExpr_ match_223;
    if ((tyDecl_.tag != Synonym_)) goto next_853;
    struct ATy_ ty_52 = (*(tyDecl_.Synonym_));
    struct StringATy_IntIntTuple2Tuple3 tuple_318;
    tuple_318.t0 = tyIdent_;
    tuple_318.t1 = ty_52;
    tuple_318.t2 = typeLoc_;
    struct StringATy_IntIntTuple2Tuple3* payload_118 = (struct StringATy_IntIntTuple2Tuple3*)malloc(sizeof(struct StringATy_IntIntTuple2Tuple3));
    (*(((struct StringATy_IntIntTuple2Tuple3*)payload_118))) = tuple_318;
    struct AExpr_ variant_118 = (struct AExpr_){.tag = TySynonym_, .TySynonym_ = payload_118};
    match_223 = variant_118;
    goto end_match_852;
next_853:;
    if ((tyDecl_.tag != Union_)) goto next_854;
    struct AVariant_List* variants_2 = (*(tyDecl_.Union_));
    struct StringAVariant_ListIntIntTuple2Tuple3 tuple_319;
    tuple_319.t0 = tyIdent_;
    tuple_319.t1 = variants_2;
    tuple_319.t2 = typeLoc_;
    struct StringAVariant_ListIntIntTuple2Tuple3* payload_119 = (struct StringAVariant_ListIntIntTuple2Tuple3*)malloc(sizeof(struct StringAVariant_ListIntIntTuple2Tuple3));
    (*(((struct StringAVariant_ListIntIntTuple2Tuple3*)payload_119))) = tuple_319;
    struct AExpr_ variant_119 = (struct AExpr_){.tag = TyUnion_, .TyUnion_ = payload_119};
    match_223 = variant_119;
    goto end_match_852;
next_854:;
    exit(1);
end_match_852:;
    struct AExpr_ expr_9 = match_223;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_320;
    tuple_320.t0 = expr_9;
    tuple_320.t1 = tokens_152;
    tuple_320.t2 = errors_104;
    match_222 = tuple_320;
    goto end_match_849;
next_850:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_321;
    tuple_321.t0 = tokens_150;
    tuple_321.t1 = errors_103;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_576 = parseTyError_1((struct String){.str = "Expected '='", .len = 12}, tuple_321);
    struct ATy_ ty_53 = call_576.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_153 = call_576.t1;
    struct StringIntIntTuple2Tuple2List* errors_105 = call_576.t2;
    struct StringATy_IntIntTuple2Tuple3 tuple_323;
    tuple_323.t0 = tyIdent_;
    tuple_323.t1 = ty_53;
    tuple_323.t2 = typeLoc_;
    struct StringATy_IntIntTuple2Tuple3* payload_120 = (struct StringATy_IntIntTuple2Tuple3*)malloc(sizeof(struct StringATy_IntIntTuple2Tuple3));
    (*(((struct StringATy_IntIntTuple2Tuple3*)payload_120))) = tuple_323;
    struct AExpr_ variant_120 = (struct AExpr_){.tag = TySynonym_, .TySynonym_ = payload_120};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_322;
    tuple_322.t0 = variant_120;
    tuple_322.t1 = tokens_153;
    tuple_322.t2 = errors_105;
    match_222 = tuple_322;
    goto end_match_849;
next_851:;
end_match_849:;
    match_221 = match_222;
    goto end_match_846;
next_847:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_324;
    tuple_324.t0 = tokens_149;
    tuple_324.t1 = errors_103;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_577 = parseExprError_1((struct String){.str = "Expected identifier", .len = 19}, tuple_324);
    match_221 = call_577;
    goto end_match_846;
next_848:;
end_match_846:;
    return match_221;
}

struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct StringList* t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_34(struct StringList* acc_21, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_143) {
    struct Token_IntIntTuple2Tuple2List* tokens_156 = arg_143.t0;
    struct StringIntIntTuple2Tuple2List* errors_108 = arg_143.t1;
    struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_224;
    if ((!(tokens_156))) goto next_856;
    if ((tokens_156->head.t0.tag != Dot_)) goto next_856;
    if ((!(tokens_156->tail))) goto next_856;
    if ((tokens_156->tail->head.t0.tag != Ident_)) goto next_856;
    struct String ident_22 = (*(tokens_156->tail->head.t0.Ident_));
    struct Token_IntIntTuple2Tuple2List* tokens_157 = tokens_156->tail->tail;
    struct StringList* list_70 = (struct StringList*)malloc(sizeof(struct StringList));
    list_70->head = ident_22;
    list_70->tail = acc_21;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_325;
    tuple_325.t0 = tokens_157;
    tuple_325.t1 = errors_108;
    struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_578 = go_34(list_70, tuple_325);
    match_224 = call_578;
    goto end_match_855;
next_856:;
    if ((!(tokens_156))) goto next_857;
    if ((tokens_156->head.t0.tag != Dot_)) goto next_857;
    struct Token_IntIntTuple2Tuple2List* tokens_158 = tokens_156->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_326;
    tuple_326.t0 = tokens_158;
    tuple_326.t1 = errors_108;
    struct StringIntIntTuple2Tuple2List* call_579 = parseNewError_1((struct String){.str = "Expected identifier", .len = 19}, tuple_326);
    struct StringIntIntTuple2Tuple2List* errors_109 = call_579;
    struct StringList* call_580 = listRev_2(acc_21);
    struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_327;
    tuple_327.t0 = call_580;
    tuple_327.t1 = tokens_158;
    tuple_327.t2 = errors_109;
    match_224 = tuple_327;
    goto end_match_855;
next_857:;
    struct StringList* call_581 = listRev_2(acc_21);
    struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_328;
    tuple_328.t0 = call_581;
    tuple_328.t1 = tokens_156;
    tuple_328.t2 = errors_108;
    match_224 = tuple_328;
    goto end_match_855;
next_858:;
end_match_855:;
    return match_224;
}

struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePath_(struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_144) {
    struct Token_IntIntTuple2Tuple2List* tokens_155 = arg_144.t0;
    struct StringIntIntTuple2Tuple2List* errors_107 = arg_144.t1;
    struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_225;
    if ((!(tokens_155))) goto next_860;
    if ((tokens_155->head.t0.tag != Ident_)) goto next_860;
    struct String ident_23 = (*(tokens_155->head.t0.Ident_));
    struct Token_IntIntTuple2Tuple2List* tokens_159 = tokens_155->tail;
    struct StringList* list_71 = (struct StringList*)malloc(sizeof(struct StringList));
    list_71->head = ident_23;
    list_71->tail = NULL;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_329;
    tuple_329.t0 = tokens_159;
    tuple_329.t1 = errors_107;
    struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_582 = go_34(list_71, tuple_329);
    match_225 = call_582;
    goto end_match_859;
next_860:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_330;
    tuple_330.t0 = tokens_155;
    tuple_330.t1 = errors_107;
    struct StringIntIntTuple2Tuple2List* call_583 = parseNewError_1((struct String){.str = "Expected identifier", .len = 19}, tuple_330);
    struct StringIntIntTuple2Tuple2List* errors_110 = call_583;
    struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_331;
    tuple_331.t0 = NULL;
    tuple_331.t1 = tokens_155;
    tuple_331.t2 = errors_110;
    match_225 = tuple_331;
    goto end_match_859;
next_861:;
end_match_859:;
    return match_225;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseOpen_(struct IntIntTuple2 openLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_145) {
    struct Token_IntIntTuple2Tuple2List* tokens_154 = arg_145.t0;
    struct StringIntIntTuple2Tuple2List* errors_106 = arg_145.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_332;
    tuple_332.t0 = tokens_154;
    tuple_332.t1 = errors_106;
    struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_584 = parsePath_(tuple_332);
    struct StringList* path_2 = call_584.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_160 = call_584.t1;
    struct StringIntIntTuple2Tuple2List* errors_111 = call_584.t2;
    struct StringListIntIntTuple2Tuple2 tuple_334;
    tuple_334.t0 = path_2;
    tuple_334.t1 = openLoc_;
    struct StringListIntIntTuple2Tuple2* payload_121 = (struct StringListIntIntTuple2Tuple2*)malloc(sizeof(struct StringListIntIntTuple2Tuple2));
    (*(((struct StringListIntIntTuple2Tuple2*)payload_121))) = tuple_334;
    struct AExpr_ variant_121 = (struct AExpr_){.tag = Open_1, .Open_1 = payload_121};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_333;
    tuple_333.t0 = variant_121;
    tuple_333.t1 = tokens_160;
    tuple_333.t2 = errors_111;
    return tuple_333;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseAtom_(struct IntIntTuple2 baseLoc_29, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_146) {
    struct Token_IntIntTuple2Tuple2List* tokens_161 = arg_146.t0;
    struct StringIntIntTuple2Tuple2List* errors_112 = arg_146.t1;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_226;
    int call_585 = nextInside_1(baseLoc_29, tokens_161);
    if (call_585) goto next_863;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_335;
    tuple_335.t0 = tokens_161;
    tuple_335.t1 = errors_112;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_586 = parseExprError_1((struct String){.str = "Expected an expression", .len = 22}, tuple_335);
    match_226 = call_586;
    goto end_match_862;
next_863:;
    if ((!(tokens_161))) goto next_864;
    if ((tokens_161->head.t0.tag != ParenL_)) goto next_864;
    struct IntIntTuple2 loc_55 = tokens_161->head.t1;
    if ((!(tokens_161->tail))) goto next_864;
    if ((tokens_161->tail->head.t0.tag != ParenR_)) goto next_864;
    struct Token_IntIntTuple2Tuple2List* tokens_162 = tokens_161->tail->tail;
    struct AExpr_ListIntIntTuple2Tuple2 tuple_337;
    tuple_337.t0 = NULL;
    tuple_337.t1 = loc_55;
    struct AExpr_ListIntIntTuple2Tuple2* payload_122 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_122))) = tuple_337;
    struct AExpr_ variant_122 = (struct AExpr_){.tag = TupleLit_1, .TupleLit_1 = payload_122};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_336;
    tuple_336.t0 = variant_122;
    tuple_336.t1 = tokens_162;
    tuple_336.t2 = errors_112;
    match_226 = tuple_336;
    goto end_match_862;
next_864:;
    if ((!(tokens_161))) goto next_865;
    if ((tokens_161->head.t0.tag != Bool_1)) goto next_865;
    int value_11 = (*(tokens_161->head.t0.Bool_1));
    struct IntIntTuple2 loc_56 = tokens_161->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_163 = tokens_161->tail;
    int* payload_123 = (int*)malloc(sizeof(int));
    (*(((int*)payload_123))) = value_11;
    struct Lit_ variant_123 = (struct Lit_){.tag = Bool_, .Bool_ = payload_123};
    struct Lit_IntIntTuple2Tuple2 tuple_339;
    tuple_339.t0 = variant_123;
    tuple_339.t1 = loc_56;
    struct Lit_IntIntTuple2Tuple2* payload_124 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_124))) = tuple_339;
    struct AExpr_ variant_124 = (struct AExpr_){.tag = Lit_1, .Lit_1 = payload_124};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_338;
    tuple_338.t0 = variant_124;
    tuple_338.t1 = tokens_163;
    tuple_338.t2 = errors_112;
    match_226 = tuple_338;
    goto end_match_862;
next_865:;
    if ((!(tokens_161))) goto next_866;
    if ((tokens_161->head.t0.tag != Int_1)) goto next_866;
    int value_12 = (*(tokens_161->head.t0.Int_1));
    struct IntIntTuple2 loc_57 = tokens_161->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_164 = tokens_161->tail;
    int* payload_125 = (int*)malloc(sizeof(int));
    (*(((int*)payload_125))) = value_12;
    struct Lit_ variant_125 = (struct Lit_){.tag = Int_, .Int_ = payload_125};
    struct Lit_IntIntTuple2Tuple2 tuple_341;
    tuple_341.t0 = variant_125;
    tuple_341.t1 = loc_57;
    struct Lit_IntIntTuple2Tuple2* payload_126 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_126))) = tuple_341;
    struct AExpr_ variant_126 = (struct AExpr_){.tag = Lit_1, .Lit_1 = payload_126};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_340;
    tuple_340.t0 = variant_126;
    tuple_340.t1 = tokens_164;
    tuple_340.t2 = errors_112;
    match_226 = tuple_340;
    goto end_match_862;
next_866:;
    if ((!(tokens_161))) goto next_867;
    if ((tokens_161->head.t0.tag != Char_1)) goto next_867;
    char value_13 = (*(tokens_161->head.t0.Char_1));
    struct IntIntTuple2 loc_58 = tokens_161->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_165 = tokens_161->tail;
    char* payload_127 = (char*)malloc(sizeof(char));
    (*(((char*)payload_127))) = value_13;
    struct Lit_ variant_127 = (struct Lit_){.tag = Char_, .Char_ = payload_127};
    struct Lit_IntIntTuple2Tuple2 tuple_343;
    tuple_343.t0 = variant_127;
    tuple_343.t1 = loc_58;
    struct Lit_IntIntTuple2Tuple2* payload_128 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_128))) = tuple_343;
    struct AExpr_ variant_128 = (struct AExpr_){.tag = Lit_1, .Lit_1 = payload_128};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_342;
    tuple_342.t0 = variant_128;
    tuple_342.t1 = tokens_165;
    tuple_342.t2 = errors_112;
    match_226 = tuple_342;
    goto end_match_862;
next_867:;
    if ((!(tokens_161))) goto next_868;
    if ((tokens_161->head.t0.tag != Str_1)) goto next_868;
    struct String value_14 = (*(tokens_161->head.t0.Str_1));
    struct IntIntTuple2 loc_59 = tokens_161->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_166 = tokens_161->tail;
    struct String* payload_129 = (struct String*)malloc(sizeof(struct String));
    (*(((struct String*)payload_129))) = value_14;
    struct Lit_ variant_129 = (struct Lit_){.tag = Str_, .Str_ = payload_129};
    struct Lit_IntIntTuple2Tuple2 tuple_345;
    tuple_345.t0 = variant_129;
    tuple_345.t1 = loc_59;
    struct Lit_IntIntTuple2Tuple2* payload_130 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_130))) = tuple_345;
    struct AExpr_ variant_130 = (struct AExpr_){.tag = Lit_1, .Lit_1 = payload_130};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_344;
    tuple_344.t0 = variant_130;
    tuple_344.t1 = tokens_166;
    tuple_344.t2 = errors_112;
    match_226 = tuple_344;
    goto end_match_862;
next_868:;
    if ((!(tokens_161))) goto next_869;
    if ((tokens_161->head.t0.tag != Ident_)) goto next_869;
    struct String ident_24 = (*(tokens_161->head.t0.Ident_));
    struct IntIntTuple2 loc_60 = tokens_161->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_167 = tokens_161->tail;
    struct StringIntIntTuple2Tuple2 tuple_347;
    tuple_347.t0 = ident_24;
    tuple_347.t1 = loc_60;
    struct StringIntIntTuple2Tuple2* payload_131 = (struct StringIntIntTuple2Tuple2*)malloc(sizeof(struct StringIntIntTuple2Tuple2));
    (*(((struct StringIntIntTuple2Tuple2*)payload_131))) = tuple_347;
    struct AExpr_ variant_131 = (struct AExpr_){.tag = Ident_3, .Ident_3 = payload_131};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_346;
    tuple_346.t0 = variant_131;
    tuple_346.t1 = tokens_167;
    tuple_346.t2 = errors_112;
    match_226 = tuple_346;
    goto end_match_862;
next_869:;
    if ((!(tokens_161))) goto next_870;
    if ((tokens_161->head.t0.tag != ParenL_)) goto next_870;
    struct IntIntTuple2 parenLoc_1 = tokens_161->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_168 = tokens_161->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_348;
    tuple_348.t0 = tokens_168;
    tuple_348.t1 = errors_112;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_587 = parseParenBody_(baseLoc_29, parenLoc_1, tuple_348);
    match_226 = call_587;
    goto end_match_862;
next_870:;
    if ((!(tokens_161))) goto next_871;
    if ((tokens_161->head.t0.tag != BracketL_)) goto next_871;
    struct IntIntTuple2 bracketLoc_2 = tokens_161->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_169 = tokens_161->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_349;
    tuple_349.t0 = tokens_169;
    tuple_349.t1 = errors_112;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_588 = parseList_(baseLoc_29, bracketLoc_2, tuple_349);
    match_226 = call_588;
    goto end_match_862;
next_871:;
    if ((!(tokens_161))) goto next_872;
    if ((tokens_161->head.t0.tag != If_)) goto next_872;
    struct IntIntTuple2 loc_61 = tokens_161->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_170 = tokens_161->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_350;
    tuple_350.t0 = tokens_170;
    tuple_350.t1 = errors_112;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_589 = parseIf_(loc_61, tuple_350);
    match_226 = call_589;
    goto end_match_862;
next_872:;
    if ((!(tokens_161))) goto next_873;
    if ((tokens_161->head.t0.tag != Match_)) goto next_873;
    struct IntIntTuple2 loc_62 = tokens_161->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_171 = tokens_161->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_351;
    tuple_351.t0 = tokens_171;
    tuple_351.t1 = errors_112;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_590 = parseMatch_(loc_62, tuple_351);
    match_226 = call_590;
    goto end_match_862;
next_873:;
    if ((!(tokens_161))) goto next_874;
    if ((tokens_161->head.t0.tag != Fun_)) goto next_874;
    struct IntIntTuple2 loc_63 = tokens_161->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_172 = tokens_161->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_352;
    tuple_352.t0 = tokens_172;
    tuple_352.t1 = errors_112;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_591 = parseFun_(baseLoc_29, loc_63, tuple_352);
    match_226 = call_591;
    goto end_match_862;
next_874:;
    if ((!(tokens_161))) goto next_875;
    if ((tokens_161->head.t0.tag != Let_)) goto next_875;
    struct IntIntTuple2 letLoc_1 = tokens_161->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_173 = tokens_161->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_353;
    tuple_353.t0 = tokens_173;
    tuple_353.t1 = errors_112;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_592 = parseLet_(letLoc_1, tuple_353);
    match_226 = call_592;
    goto end_match_862;
next_875:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_354;
    tuple_354.t0 = tokens_161;
    tuple_354.t1 = errors_112;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_593 = parseExprError_1((struct String){.str = "Expected an expression", .len = 22}, tuple_354);
    match_226 = call_593;
    goto end_match_862;
next_876:;
end_match_862:;
    return match_226;
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

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_35(struct IntIntTuple2 baseLoc_30, struct AExpr_ acc_22, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_147) {
    struct Token_IntIntTuple2Tuple2List* tokens_176 = arg_147.t0;
    struct StringIntIntTuple2Tuple2List* errors_115 = arg_147.t1;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_227;
    if ((!(tokens_176))) goto next_878;
    if ((tokens_176->head.t0.tag != Dot_)) goto next_878;
    struct IntIntTuple2 loc_64 = tokens_176->head.t1;
    if ((!(tokens_176->tail))) goto next_878;
    if ((tokens_176->tail->head.t0.tag != BracketL_)) goto next_878;
    struct Token_IntIntTuple2Tuple2List* tokens_177 = tokens_176->tail->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_355;
    tuple_355.t0 = tokens_177;
    tuple_355.t1 = errors_115;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_594 = parseRange_(baseLoc_30, tuple_355);
    struct AExpr_ r_29 = call_594.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_178 = call_594.t1;
    struct StringIntIntTuple2Tuple2List* errors_116 = call_594.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 match_228;
    if ((!(tokens_178))) goto next_883;
    if ((tokens_178->head.t0.tag != BracketR_)) goto next_883;
    struct Token_IntIntTuple2Tuple2List* tokens_180 = tokens_178->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_356;
    tuple_356.t0 = tokens_180;
    tuple_356.t1 = errors_116;
    match_228 = tuple_356;
    goto end_match_882;
next_883:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_357;
    tuple_357.t0 = tokens_178;
    tuple_357.t1 = errors_116;
    struct StringIntIntTuple2Tuple2List* call_595 = parseNewError_1((struct String){.str = "Expected closing ']'", .len = 20}, tuple_357);
    struct StringIntIntTuple2Tuple2List* errors_118 = call_595;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_358;
    tuple_358.t0 = tokens_178;
    tuple_358.t1 = errors_118;
    match_228 = tuple_358;
    goto end_match_882;
next_884:;
end_match_882:;
    struct Token_IntIntTuple2Tuple2List* tokens_179 = match_228.t0;
    struct StringIntIntTuple2Tuple2List* errors_117 = match_228.t1;
    struct AExpr_AExpr_IntIntTuple2Tuple3 tuple_359;
    tuple_359.t0 = acc_22;
    tuple_359.t1 = r_29;
    tuple_359.t2 = loc_64;
    struct AExpr_AExpr_IntIntTuple2Tuple3* payload_132 = (struct AExpr_AExpr_IntIntTuple2Tuple3*)malloc(sizeof(struct AExpr_AExpr_IntIntTuple2Tuple3));
    (*(((struct AExpr_AExpr_IntIntTuple2Tuple3*)payload_132))) = tuple_359;
    struct AExpr_ variant_132 = (struct AExpr_){.tag = Index_, .Index_ = payload_132};
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_360;
    tuple_360.t0 = tokens_179;
    tuple_360.t1 = errors_117;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_596 = go_35(baseLoc_30, variant_132, tuple_360);
    match_227 = call_596;
    goto end_match_877;
next_878:;
    if ((!(tokens_176))) goto next_879;
    if ((tokens_176->head.t0.tag != Dot_)) goto next_879;
    struct IntIntTuple2 loc_65 = tokens_176->head.t1;
    if ((!(tokens_176->tail))) goto next_879;
    if ((tokens_176->tail->head.t0.tag != Ident_)) goto next_879;
    struct String r_30 = (*(tokens_176->tail->head.t0.Ident_));
    struct Token_IntIntTuple2Tuple2List* tokens_181 = tokens_176->tail->tail;
    struct AExpr_StringIntIntTuple2Tuple3 tuple_361;
    tuple_361.t0 = acc_22;
    tuple_361.t1 = r_30;
    tuple_361.t2 = loc_65;
    struct AExpr_StringIntIntTuple2Tuple3* payload_133 = (struct AExpr_StringIntIntTuple2Tuple3*)malloc(sizeof(struct AExpr_StringIntIntTuple2Tuple3));
    (*(((struct AExpr_StringIntIntTuple2Tuple3*)payload_133))) = tuple_361;
    struct AExpr_ variant_133 = (struct AExpr_){.tag = Nav_1, .Nav_1 = payload_133};
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_362;
    tuple_362.t0 = tokens_181;
    tuple_362.t1 = errors_115;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_597 = go_35(baseLoc_30, variant_133, tuple_362);
    match_227 = call_597;
    goto end_match_877;
next_879:;
    if ((!(tokens_176))) goto next_880;
    if ((tokens_176->head.t0.tag != Dot_)) goto next_880;
    struct Token_IntIntTuple2Tuple2List* tokens_182 = tokens_176->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_363;
    tuple_363.t0 = tokens_182;
    tuple_363.t1 = errors_115;
    struct StringIntIntTuple2Tuple2List* call_598 = parseNewError_1((struct String){.str = "Expected .[] or .field", .len = 22}, tuple_363);
    struct StringIntIntTuple2Tuple2List* errors_119 = call_598;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_364;
    tuple_364.t0 = acc_22;
    tuple_364.t1 = tokens_182;
    tuple_364.t2 = errors_119;
    match_227 = tuple_364;
    goto end_match_877;
next_880:;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_365;
    tuple_365.t0 = acc_22;
    tuple_365.t1 = tokens_176;
    tuple_365.t2 = errors_115;
    match_227 = tuple_365;
    goto end_match_877;
next_881:;
end_match_877:;
    return match_227;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseSuffix_(struct IntIntTuple2 baseLoc_30, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_148) {
    struct Token_IntIntTuple2Tuple2List* tokens_174 = arg_148.t0;
    struct StringIntIntTuple2Tuple2List* errors_113 = arg_148.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_366;
    tuple_366.t0 = tokens_174;
    tuple_366.t1 = errors_113;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_599 = parseAtom_(baseLoc_30, tuple_366);
    struct AExpr_ l_16 = call_599.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_175 = call_599.t1;
    struct StringIntIntTuple2Tuple2List* errors_114 = call_599.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_367;
    tuple_367.t0 = tokens_175;
    tuple_367.t1 = errors_114;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_600 = go_35(baseLoc_30, l_16, tuple_367);
    return call_600;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_36(struct IntIntTuple2 argBaseLoc_1, struct IntIntTuple2 calleeLoc_3, struct IntIntTuple2 baseLoc_31, struct AExpr_ callee_7, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_149) {
    struct Token_IntIntTuple2Tuple2List* tokens_185 = arg_149.t0;
    struct StringIntIntTuple2Tuple2List* errors_122 = arg_149.t1;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_229;
    int match_230;
    int call_601 = nextInside_1(argBaseLoc_1, tokens_185);
    if ((!(call_601))) goto next_887;
    int call_602 = leadsArg_1(tokens_185);
    match_230 = call_602;
    goto end_match_886;
next_887:;
    if (call_601) goto next_888;
    match_230 = 0;
    goto end_match_886;
next_888:;
    exit(1);
end_match_886:;
    if ((!(match_230))) goto next_889;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_368;
    tuple_368.t0 = tokens_185;
    tuple_368.t1 = errors_122;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_603 = parseSuffix_(baseLoc_31, tuple_368);
    struct AExpr_ arg_2 = call_603.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_186 = call_603.t1;
    struct StringIntIntTuple2Tuple2List* errors_123 = call_603.t2;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_369;
    tuple_369.t0 = (struct Op_){.tag = App_};
    tuple_369.t1 = callee_7;
    tuple_369.t2 = arg_2;
    tuple_369.t3 = calleeLoc_3;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_134 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_134))) = tuple_369;
    struct AExpr_ variant_134 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_134};
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_370;
    tuple_370.t0 = tokens_186;
    tuple_370.t1 = errors_123;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_604 = go_36(argBaseLoc_1, calleeLoc_3, baseLoc_31, variant_134, tuple_370);
    match_229 = call_604;
    goto end_match_885;
next_889:;
    if (match_230) goto next_890;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_371;
    tuple_371.t0 = callee_7;
    tuple_371.t1 = tokens_185;
    tuple_371.t2 = errors_122;
    match_229 = tuple_371;
    goto end_match_885;
next_890:;
    exit(1);
end_match_885:;
    return match_229;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseApp_(struct IntIntTuple2 baseLoc_31, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_150) {
    struct Token_IntIntTuple2Tuple2List* tokens_183 = arg_150.t0;
    struct StringIntIntTuple2Tuple2List* errors_120 = arg_150.t1;
    struct IntIntTuple2 call_605 = nextLoc_1(tokens_183);
    struct IntIntTuple2 calleeLoc_3 = call_605;
    struct IntIntTuple2 call_606 = locAddX_(1, calleeLoc_3);
    struct IntIntTuple2 argBaseLoc_1 = call_606;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_372;
    tuple_372.t0 = tokens_183;
    tuple_372.t1 = errors_120;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_607 = parseSuffix_(baseLoc_31, tuple_372);
    struct AExpr_ callee_6 = call_607.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_184 = call_607.t1;
    struct StringIntIntTuple2Tuple2List* errors_121 = call_607.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_373;
    tuple_373.t0 = tokens_184;
    tuple_373.t1 = errors_121;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_608 = go_36(argBaseLoc_1, calleeLoc_3, baseLoc_31, callee_6, tuple_373);
    return call_608;
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

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePrefix_(struct IntIntTuple2 baseLoc_32, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_151) {
    struct Token_IntIntTuple2Tuple2List* tokens_187 = arg_151.t0;
    struct StringIntIntTuple2Tuple2List* errors_124 = arg_151.t1;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_231;
    if ((!(tokens_187))) goto next_892;
    if ((tokens_187->head.t0.tag != Minus_)) goto next_892;
    struct IntIntTuple2 loc_66 = tokens_187->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_188 = tokens_187->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_374;
    tuple_374.t0 = tokens_188;
    tuple_374.t1 = errors_124;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_609 = parseApp_(baseLoc_32, tuple_374);
    struct AExpr_ arg_3 = call_609.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_189 = call_609.t1;
    struct StringIntIntTuple2Tuple2List* errors_125 = call_609.t2;
    struct UniOp_AExpr_IntIntTuple2Tuple3 tuple_376;
    tuple_376.t0 = (struct UniOp_){.tag = Neg_};
    tuple_376.t1 = arg_3;
    tuple_376.t2 = loc_66;
    struct UniOp_AExpr_IntIntTuple2Tuple3* payload_135 = (struct UniOp_AExpr_IntIntTuple2Tuple3*)malloc(sizeof(struct UniOp_AExpr_IntIntTuple2Tuple3));
    (*(((struct UniOp_AExpr_IntIntTuple2Tuple3*)payload_135))) = tuple_376;
    struct AExpr_ variant_135 = (struct AExpr_){.tag = Uni_, .Uni_ = payload_135};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_375;
    tuple_375.t0 = variant_135;
    tuple_375.t1 = tokens_189;
    tuple_375.t2 = errors_125;
    match_231 = tuple_375;
    goto end_match_891;
next_892:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_377;
    tuple_377.t0 = tokens_187;
    tuple_377.t1 = errors_124;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_610 = parseApp_(baseLoc_32, tuple_377);
    match_231 = call_610;
    goto end_match_891;
next_893:;
end_match_891:;
    return match_231;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseNextLevelOp_(struct OpLevel_ level_1, struct IntIntTuple2 baseLoc_33, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_152) {
    struct Token_IntIntTuple2Tuple2List* tokens_190 = arg_152.t0;
    struct StringIntIntTuple2Tuple2List* errors_126 = arg_152.t1;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_232;
    struct OpLevel_ call_611 = opLevelToNext_(level_1);
    if ((call_611.tag != Prefix_)) goto next_895;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_378;
    tuple_378.t0 = tokens_190;
    tuple_378.t1 = errors_126;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_612 = parsePrefix_(baseLoc_33, tuple_378);
    match_232 = call_612;
    goto end_match_894;
next_895:;
    struct OpLevel_ nextLevel_ = call_611;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_379;
    tuple_379.t0 = tokens_190;
    tuple_379.t1 = errors_126;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_613 = parseOp_(nextLevel_, baseLoc_33, tuple_379);
    match_232 = call_613;
    goto end_match_894;
next_896:;
end_match_894:;
    return match_232;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 nextL_(struct IntIntTuple2 baseLoc_34, struct OpLevel_ level_2, struct AExpr_ expr_10, struct Op_ op_, struct IntIntTuple2 opLoc_2, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_153) {
    struct Token_IntIntTuple2Tuple2List* tokens_192 = arg_153.t0;
    struct StringIntIntTuple2Tuple2List* errors_128 = arg_153.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_380;
    tuple_380.t0 = tokens_192;
    tuple_380.t1 = errors_128;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_614 = parseNextLevelOp_(level_2, baseLoc_34, tuple_380);
    struct AExpr_ second_4 = call_614.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_193 = call_614.t1;
    struct StringIntIntTuple2Tuple2List* errors_129 = call_614.t2;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_381;
    tuple_381.t0 = op_;
    tuple_381.t1 = expr_10;
    tuple_381.t2 = second_4;
    tuple_381.t3 = opLoc_2;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_136 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_136))) = tuple_381;
    struct AExpr_ variant_136 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_136};
    struct AExpr_ expr_11 = variant_136;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_382;
    tuple_382.t0 = tokens_193;
    tuple_382.t1 = errors_129;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_615 = parseOps_(level_2, baseLoc_34, expr_11, tuple_382);
    return call_615;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 nextR_(struct IntIntTuple2 baseLoc_34, struct OpLevel_ level_2, struct AExpr_ expr_12, struct Op_ op_1, struct IntIntTuple2 opLoc_3, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_154) {
    struct Token_IntIntTuple2Tuple2List* tokens_194 = arg_154.t0;
    struct StringIntIntTuple2Tuple2List* errors_130 = arg_154.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_383;
    tuple_383.t0 = tokens_194;
    tuple_383.t1 = errors_130;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_616 = parseOp_(level_2, baseLoc_34, tuple_383);
    struct AExpr_ second_5 = call_616.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_195 = call_616.t1;
    struct StringIntIntTuple2Tuple2List* errors_131 = call_616.t2;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_384;
    tuple_384.t0 = op_1;
    tuple_384.t1 = expr_12;
    tuple_384.t2 = second_5;
    tuple_384.t3 = opLoc_3;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_137 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_137))) = tuple_384;
    struct AExpr_ variant_137 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_137};
    struct AExpr_ expr_13 = variant_137;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_385;
    tuple_385.t0 = tokens_195;
    tuple_385.t1 = errors_131;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_617 = parseOps_(level_2, baseLoc_34, expr_13, tuple_385);
    return call_617;
}

struct OpLevel_Token_IntIntTuple2Tuple2ListTuple2 {
    struct OpLevel_ t0;
    struct Token_IntIntTuple2Tuple2List* t1;
};

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseOps_(struct OpLevel_ level_2, struct IntIntTuple2 baseLoc_34, struct AExpr_ first_3, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_155) {
    struct Token_IntIntTuple2Tuple2List* tokens_191 = arg_155.t0;
    struct StringIntIntTuple2Tuple2List* errors_127 = arg_155.t1;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_233;
    struct OpLevel_Token_IntIntTuple2Tuple2ListTuple2 tuple_386;
    tuple_386.t0 = level_2;
    tuple_386.t1 = tokens_191;
    if ((tuple_386.t0.tag != Or_)) goto next_898;
    if ((!(tuple_386.t1))) goto next_898;
    if ((tuple_386.t1->head.t0.tag != PipePipe_)) goto next_898;
    struct IntIntTuple2 opLoc_4 = tuple_386.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_196 = tuple_386.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_387;
    tuple_387.t0 = tokens_196;
    tuple_387.t1 = errors_127;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_618 = nextL_(baseLoc_34, level_2, first_3, (struct Op_){.tag = Or_1}, opLoc_4, tuple_387);
    match_233 = call_618;
    goto end_match_897;
next_898:;
    if ((tuple_386.t0.tag != And_)) goto next_899;
    if ((!(tuple_386.t1))) goto next_899;
    if ((tuple_386.t1->head.t0.tag != AmpAmp_)) goto next_899;
    struct IntIntTuple2 opLoc_5 = tuple_386.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_197 = tuple_386.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_388;
    tuple_388.t0 = tokens_197;
    tuple_388.t1 = errors_127;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_619 = nextL_(baseLoc_34, level_2, first_3, (struct Op_){.tag = And_1}, opLoc_5, tuple_388);
    match_233 = call_619;
    goto end_match_897;
next_899:;
    if ((tuple_386.t0.tag != Cmp_)) goto next_900;
    if ((!(tuple_386.t1))) goto next_900;
    if ((tuple_386.t1->head.t0.tag != Eq_)) goto next_900;
    struct IntIntTuple2 opLoc_6 = tuple_386.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_198 = tuple_386.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_389;
    tuple_389.t0 = tokens_198;
    tuple_389.t1 = errors_127;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_620 = nextL_(baseLoc_34, level_2, first_3, (struct Op_){.tag = Eq_1}, opLoc_6, tuple_389);
    match_233 = call_620;
    goto end_match_897;
next_900:;
    if ((tuple_386.t0.tag != Cmp_)) goto next_901;
    if ((!(tuple_386.t1))) goto next_901;
    if ((tuple_386.t1->head.t0.tag != LtGt_)) goto next_901;
    struct IntIntTuple2 opLoc_7 = tuple_386.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_199 = tuple_386.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_390;
    tuple_390.t0 = tokens_199;
    tuple_390.t1 = errors_127;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_621 = nextL_(baseLoc_34, level_2, first_3, (struct Op_){.tag = Ne_}, opLoc_7, tuple_390);
    match_233 = call_621;
    goto end_match_897;
next_901:;
    if ((tuple_386.t0.tag != Cmp_)) goto next_902;
    if ((!(tuple_386.t1))) goto next_902;
    if ((tuple_386.t1->head.t0.tag != Lt_)) goto next_902;
    struct IntIntTuple2 opLoc_8 = tuple_386.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_200 = tuple_386.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_391;
    tuple_391.t0 = tokens_200;
    tuple_391.t1 = errors_127;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_622 = nextL_(baseLoc_34, level_2, first_3, (struct Op_){.tag = Lt_1}, opLoc_8, tuple_391);
    match_233 = call_622;
    goto end_match_897;
next_902:;
    if ((tuple_386.t0.tag != Cmp_)) goto next_903;
    if ((!(tuple_386.t1))) goto next_903;
    if ((tuple_386.t1->head.t0.tag != LtEq_)) goto next_903;
    struct IntIntTuple2 opLoc_9 = tuple_386.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_201 = tuple_386.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_392;
    tuple_392.t0 = tokens_201;
    tuple_392.t1 = errors_127;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_623 = nextL_(baseLoc_34, level_2, first_3, (struct Op_){.tag = Le_}, opLoc_9, tuple_392);
    match_233 = call_623;
    goto end_match_897;
next_903:;
    if ((tuple_386.t0.tag != Cmp_)) goto next_904;
    if ((!(tuple_386.t1))) goto next_904;
    if ((tuple_386.t1->head.t0.tag != Gt_)) goto next_904;
    struct IntIntTuple2 opLoc_10 = tuple_386.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_202 = tuple_386.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_393;
    tuple_393.t0 = tokens_202;
    tuple_393.t1 = errors_127;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_624 = nextL_(baseLoc_34, level_2, first_3, (struct Op_){.tag = Gt_1}, opLoc_10, tuple_393);
    match_233 = call_624;
    goto end_match_897;
next_904:;
    if ((tuple_386.t0.tag != Cmp_)) goto next_905;
    if ((!(tuple_386.t1))) goto next_905;
    if ((tuple_386.t1->head.t0.tag != GtEq_)) goto next_905;
    struct IntIntTuple2 opLoc_11 = tuple_386.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_203 = tuple_386.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_394;
    tuple_394.t0 = tokens_203;
    tuple_394.t1 = errors_127;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_625 = nextL_(baseLoc_34, level_2, first_3, (struct Op_){.tag = Ge_}, opLoc_11, tuple_394);
    match_233 = call_625;
    goto end_match_897;
next_905:;
    if ((tuple_386.t0.tag != Pipe_1)) goto next_906;
    if ((!(tuple_386.t1))) goto next_906;
    if ((tuple_386.t1->head.t0.tag != PipeGt_)) goto next_906;
    struct IntIntTuple2 opLoc_12 = tuple_386.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_204 = tuple_386.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_395;
    tuple_395.t0 = tokens_204;
    tuple_395.t1 = errors_127;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_626 = nextL_(baseLoc_34, level_2, first_3, (struct Op_){.tag = Pipe_2}, opLoc_12, tuple_395);
    match_233 = call_626;
    goto end_match_897;
next_906:;
    if ((tuple_386.t0.tag != Cons_)) goto next_907;
    if ((!(tuple_386.t1))) goto next_907;
    if ((tuple_386.t1->head.t0.tag != ColonColon_)) goto next_907;
    struct IntIntTuple2 opLoc_13 = tuple_386.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_205 = tuple_386.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_396;
    tuple_396.t0 = tokens_205;
    tuple_396.t1 = errors_127;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_627 = nextR_(baseLoc_34, level_2, first_3, (struct Op_){.tag = Cons_1}, opLoc_13, tuple_396);
    match_233 = call_627;
    goto end_match_897;
next_907:;
    if ((tuple_386.t0.tag != Add_)) goto next_908;
    if ((!(tuple_386.t1))) goto next_908;
    if ((tuple_386.t1->head.t0.tag != Plus_)) goto next_908;
    struct IntIntTuple2 opLoc_14 = tuple_386.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_206 = tuple_386.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_397;
    tuple_397.t0 = tokens_206;
    tuple_397.t1 = errors_127;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_628 = nextL_(baseLoc_34, level_2, first_3, (struct Op_){.tag = Add_1}, opLoc_14, tuple_397);
    match_233 = call_628;
    goto end_match_897;
next_908:;
    if ((tuple_386.t0.tag != Add_)) goto next_909;
    if ((!(tuple_386.t1))) goto next_909;
    if ((tuple_386.t1->head.t0.tag != Minus_)) goto next_909;
    struct IntIntTuple2 opLoc_15 = tuple_386.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_207 = tuple_386.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_398;
    tuple_398.t0 = tokens_207;
    tuple_398.t1 = errors_127;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_629 = nextL_(baseLoc_34, level_2, first_3, (struct Op_){.tag = Sub_}, opLoc_15, tuple_398);
    match_233 = call_629;
    goto end_match_897;
next_909:;
    if ((tuple_386.t0.tag != Mul_)) goto next_910;
    if ((!(tuple_386.t1))) goto next_910;
    if ((tuple_386.t1->head.t0.tag != Star_)) goto next_910;
    struct IntIntTuple2 opLoc_16 = tuple_386.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_208 = tuple_386.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_399;
    tuple_399.t0 = tokens_208;
    tuple_399.t1 = errors_127;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_630 = nextL_(baseLoc_34, level_2, first_3, (struct Op_){.tag = Mul_1}, opLoc_16, tuple_399);
    match_233 = call_630;
    goto end_match_897;
next_910:;
    if ((tuple_386.t0.tag != Mul_)) goto next_911;
    if ((!(tuple_386.t1))) goto next_911;
    if ((tuple_386.t1->head.t0.tag != Slash_)) goto next_911;
    struct IntIntTuple2 opLoc_17 = tuple_386.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_209 = tuple_386.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_400;
    tuple_400.t0 = tokens_209;
    tuple_400.t1 = errors_127;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_631 = nextL_(baseLoc_34, level_2, first_3, (struct Op_){.tag = Div_}, opLoc_17, tuple_400);
    match_233 = call_631;
    goto end_match_897;
next_911:;
    if ((tuple_386.t0.tag != Mul_)) goto next_912;
    if ((!(tuple_386.t1))) goto next_912;
    if ((tuple_386.t1->head.t0.tag != Percent_)) goto next_912;
    struct IntIntTuple2 opLoc_18 = tuple_386.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_210 = tuple_386.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_401;
    tuple_401.t0 = tokens_210;
    tuple_401.t1 = errors_127;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_632 = nextL_(baseLoc_34, level_2, first_3, (struct Op_){.tag = Mod_}, opLoc_18, tuple_401);
    match_233 = call_632;
    goto end_match_897;
next_912:;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_402;
    tuple_402.t0 = first_3;
    tuple_402.t1 = tokens_191;
    tuple_402.t2 = errors_127;
    match_233 = tuple_402;
    goto end_match_897;
next_913:;
end_match_897:;
    return match_233;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseOp_(struct OpLevel_ level_3, struct IntIntTuple2 baseLoc_35, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_156) {
    struct Token_IntIntTuple2Tuple2List* tokens_211 = arg_156.t0;
    struct StringIntIntTuple2Tuple2List* errors_132 = arg_156.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_403;
    tuple_403.t0 = tokens_211;
    tuple_403.t1 = errors_132;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_633 = parseNextLevelOp_(level_3, baseLoc_35, tuple_403);
    struct AExpr_ first_4 = call_633.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_212 = call_633.t1;
    struct StringIntIntTuple2Tuple2List* errors_133 = call_633.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_404;
    tuple_404.t0 = tokens_212;
    tuple_404.t1 = errors_133;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_634 = parseOps_(level_3, baseLoc_35, first_4, tuple_404);
    return call_634;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTupleItem_(struct IntIntTuple2 baseLoc_36, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_157) {
    struct Token_IntIntTuple2Tuple2List* tokens_213 = arg_157.t0;
    struct StringIntIntTuple2Tuple2List* errors_134 = arg_157.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_405;
    tuple_405.t0 = tokens_213;
    tuple_405.t1 = errors_134;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_635 = parseOp_((struct OpLevel_){.tag = Or_}, baseLoc_36, tuple_405);
    return call_635;
}

struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_37(struct IntIntTuple2 baseLoc_37, struct AExpr_List* acc_23, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_158) {
    struct Token_IntIntTuple2Tuple2List* tokens_215 = arg_158.t0;
    struct StringIntIntTuple2Tuple2List* errors_136 = arg_158.t1;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_234;
    if ((!(tokens_215))) goto next_915;
    if ((tokens_215->head.t0.tag != Comma_)) goto next_915;
    struct Token_IntIntTuple2Tuple2List* tokens_216 = tokens_215->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_406;
    tuple_406.t0 = tokens_216;
    tuple_406.t1 = errors_136;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_636 = parseTupleItem_(baseLoc_37, tuple_406);
    struct AExpr_ second_6 = call_636.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_217 = call_636.t1;
    struct StringIntIntTuple2Tuple2List* errors_137 = call_636.t2;
    struct AExpr_List* list_72 = (struct AExpr_List*)malloc(sizeof(struct AExpr_List));
    list_72->head = second_6;
    list_72->tail = acc_23;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_407;
    tuple_407.t0 = tokens_217;
    tuple_407.t1 = errors_137;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_637 = go_37(baseLoc_37, list_72, tuple_407);
    match_234 = call_637;
    goto end_match_914;
next_915:;
    struct Token_IntIntTuple2Tuple2List* tokens_218 = tokens_215;
    struct AExpr_List* call_638 = listRev_1(acc_23);
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_408;
    tuple_408.t0 = call_638;
    tuple_408.t1 = tokens_218;
    tuple_408.t2 = errors_136;
    match_234 = tuple_408;
    goto end_match_914;
next_916:;
end_match_914:;
    return match_234;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTuple_(struct IntIntTuple2 baseLoc_37, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_159) {
    struct Token_IntIntTuple2Tuple2List* tokens_214 = arg_159.t0;
    struct StringIntIntTuple2Tuple2List* errors_135 = arg_159.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_409;
    tuple_409.t0 = tokens_214;
    tuple_409.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_639 = parseTupleItem_(baseLoc_37, tuple_409);
    struct AExpr_ item_ = call_639.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_219 = call_639.t1;
    struct StringIntIntTuple2Tuple2List* errors_138 = call_639.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_235;
    if ((!(tokens_219))) goto next_918;
    if ((tokens_219->head.t0.tag != Comma_)) goto next_918;
    struct IntIntTuple2 loc_67 = tokens_219->head.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_410;
    tuple_410.t0 = tokens_219;
    tuple_410.t1 = errors_138;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_640 = go_37(baseLoc_37, NULL, tuple_410);
    struct AExpr_List* items_6 = call_640.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_220 = call_640.t1;
    struct StringIntIntTuple2Tuple2List* errors_139 = call_640.t2;
    struct AExpr_List* list_73 = (struct AExpr_List*)malloc(sizeof(struct AExpr_List));
    list_73->head = item_;
    list_73->tail = items_6;
    struct AExpr_ListIntIntTuple2Tuple2 tuple_412;
    tuple_412.t0 = list_73;
    tuple_412.t1 = loc_67;
    struct AExpr_ListIntIntTuple2Tuple2* payload_138 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_138))) = tuple_412;
    struct AExpr_ variant_138 = (struct AExpr_){.tag = TupleLit_1, .TupleLit_1 = payload_138};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_411;
    tuple_411.t0 = variant_138;
    tuple_411.t1 = tokens_220;
    tuple_411.t2 = errors_139;
    match_235 = tuple_411;
    goto end_match_917;
next_918:;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_413;
    tuple_413.t0 = item_;
    tuple_413.t1 = tokens_219;
    tuple_413.t2 = errors_138;
    match_235 = tuple_413;
    goto end_match_917;
next_919:;
end_match_917:;
    return match_235;
}

struct AExpr_ATy_IntIntTuple2Tuple3 {
    struct AExpr_ t0;
    struct ATy_ t1;
    struct IntIntTuple2 t2;
};

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseAnno_(struct IntIntTuple2 baseLoc_38, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_160) {
    struct Token_IntIntTuple2Tuple2List* tokens_221 = arg_160.t0;
    struct StringIntIntTuple2Tuple2List* errors_140 = arg_160.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_414;
    tuple_414.t0 = tokens_221;
    tuple_414.t1 = errors_140;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_641 = parseTuple_(baseLoc_38, tuple_414);
    struct AExpr_ body_12 = call_641.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_222 = call_641.t1;
    struct StringIntIntTuple2Tuple2List* errors_141 = call_641.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_236;
    if ((!(tokens_222))) goto next_921;
    if ((tokens_222->head.t0.tag != Colon_)) goto next_921;
    struct IntIntTuple2 loc_68 = tokens_222->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_223 = tokens_222->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_415;
    tuple_415.t0 = tokens_223;
    tuple_415.t1 = errors_141;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_642 = parseTy_(baseLoc_38, tuple_415);
    struct ATy_ ty_54 = call_642.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_224 = call_642.t1;
    struct StringIntIntTuple2Tuple2List* errors_142 = call_642.t2;
    struct AExpr_ATy_IntIntTuple2Tuple3 tuple_417;
    tuple_417.t0 = body_12;
    tuple_417.t1 = ty_54;
    tuple_417.t2 = loc_68;
    struct AExpr_ATy_IntIntTuple2Tuple3* payload_139 = (struct AExpr_ATy_IntIntTuple2Tuple3*)malloc(sizeof(struct AExpr_ATy_IntIntTuple2Tuple3));
    (*(((struct AExpr_ATy_IntIntTuple2Tuple3*)payload_139))) = tuple_417;
    struct AExpr_ variant_139 = (struct AExpr_){.tag = Anno_1, .Anno_1 = payload_139};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_416;
    tuple_416.t0 = variant_139;
    tuple_416.t1 = tokens_224;
    tuple_416.t2 = errors_142;
    match_236 = tuple_416;
    goto end_match_920;
next_921:;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_418;
    tuple_418.t0 = body_12;
    tuple_418.t1 = tokens_222;
    tuple_418.t2 = errors_141;
    match_236 = tuple_418;
    goto end_match_920;
next_922:;
end_match_920:;
    return match_236;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseExpr_(struct IntIntTuple2 baseLoc_39, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_161) {
    struct Token_IntIntTuple2Tuple2List* tokens_225 = arg_161.t0;
    struct StringIntIntTuple2Tuple2List* errors_143 = arg_161.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_419;
    tuple_419.t0 = tokens_225;
    tuple_419.t1 = errors_143;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_643 = parseAnno_(baseLoc_39, tuple_419);
    return call_643;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseStmt_(struct IntIntTuple2 baseLoc_40, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_162) {
    struct Token_IntIntTuple2Tuple2List* tokens_226 = arg_162.t0;
    struct StringIntIntTuple2Tuple2List* errors_144 = arg_162.t1;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_237;
    if ((!(tokens_226))) goto next_924;
    if ((tokens_226->head.t0.tag != Let_)) goto next_924;
    struct IntIntTuple2 letLoc_2 = tokens_226->head.t1;
    if ((!(tokens_226->tail))) goto next_924;
    if ((tokens_226->tail->head.t0.tag != Rec_)) goto next_924;
    struct Token_IntIntTuple2Tuple2List* tokens_227 = tokens_226->tail->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_420;
    tuple_420.t0 = tokens_227;
    tuple_420.t1 = errors_144;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_644 = parseLet_(letLoc_2, tuple_420);
    match_237 = call_644;
    goto end_match_923;
next_924:;
    if ((!(tokens_226))) goto next_925;
    if ((tokens_226->head.t0.tag != Let_)) goto next_925;
    struct IntIntTuple2 letLoc_3 = tokens_226->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_228 = tokens_226->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_421;
    tuple_421.t0 = tokens_228;
    tuple_421.t1 = errors_144;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_645 = parseLet_(letLoc_3, tuple_421);
    match_237 = call_645;
    goto end_match_923;
next_925:;
    if ((!(tokens_226))) goto next_926;
    if ((tokens_226->head.t0.tag != Type_)) goto next_926;
    struct IntIntTuple2 typeLoc_1 = tokens_226->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_229 = tokens_226->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_422;
    tuple_422.t0 = tokens_229;
    tuple_422.t1 = errors_144;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_646 = parseTyDecl_(typeLoc_1, tuple_422);
    match_237 = call_646;
    goto end_match_923;
next_926:;
    if ((!(tokens_226))) goto next_927;
    if ((tokens_226->head.t0.tag != Open_)) goto next_927;
    struct IntIntTuple2 typeLoc_2 = tokens_226->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_230 = tokens_226->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_423;
    tuple_423.t0 = tokens_230;
    tuple_423.t1 = errors_144;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_647 = parseOpen_(typeLoc_2, tuple_423);
    match_237 = call_647;
    goto end_match_923;
next_927:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_424;
    tuple_424.t0 = tokens_226;
    tuple_424.t1 = errors_144;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_648 = parseExpr_(baseLoc_40, tuple_424);
    match_237 = call_648;
    goto end_match_923;
next_928:;
end_match_923:;
    return match_237;
}

struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_38(struct IntIntTuple2 baseLoc_41, struct AExpr_List* acc_24, struct IntIntTuple2 alignLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_163) {
    struct Token_IntIntTuple2Tuple2List* tokens_232 = arg_163.t0;
    struct StringIntIntTuple2Tuple2List* errors_146 = arg_163.t1;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_238;
    if ((!(tokens_232))) goto next_930;
    if ((tokens_232->head.t0.tag != Semi_)) goto next_930;
    struct IntIntTuple2 semiLoc_ = tokens_232->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_233 = tokens_232->tail;
    int call_649 = locInside_(alignLoc_, semiLoc_);
    if ((!(call_649))) goto next_930;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_425;
    tuple_425.t0 = tokens_233;
    tuple_425.t1 = errors_146;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_650 = parseStmt_(baseLoc_41, tuple_425);
    struct AExpr_ expr_14 = call_650.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_234 = call_650.t1;
    struct StringIntIntTuple2Tuple2List* errors_147 = call_650.t2;
    struct AExpr_List* list_74 = (struct AExpr_List*)malloc(sizeof(struct AExpr_List));
    list_74->head = expr_14;
    list_74->tail = acc_24;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_426;
    tuple_426.t0 = tokens_234;
    tuple_426.t1 = errors_147;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_651 = go_38(baseLoc_41, list_74, alignLoc_, tuple_426);
    match_238 = call_651;
    goto end_match_929;
next_930:;
    int match_239;
    struct IntIntTuple2 call_652 = nextLoc_1(tokens_232);
    int call_653 = locIsSameColumn_(alignLoc_, call_652);
    if ((!(call_653))) goto next_934;
    int call_654 = leadsExpr_1(tokens_232);
    match_239 = call_654;
    goto end_match_933;
next_934:;
    if (call_653) goto next_935;
    match_239 = 0;
    goto end_match_933;
next_935:;
    exit(1);
end_match_933:;
    if ((!(match_239))) goto next_931;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_427;
    tuple_427.t0 = tokens_232;
    tuple_427.t1 = errors_146;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_655 = parseStmt_(baseLoc_41, tuple_427);
    struct AExpr_ expr_15 = call_655.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_235 = call_655.t1;
    struct StringIntIntTuple2Tuple2List* errors_148 = call_655.t2;
    struct AExpr_List* list_75 = (struct AExpr_List*)malloc(sizeof(struct AExpr_List));
    list_75->head = expr_15;
    list_75->tail = acc_24;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_428;
    tuple_428.t0 = tokens_235;
    tuple_428.t1 = errors_148;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_656 = go_38(baseLoc_41, list_75, alignLoc_, tuple_428);
    match_238 = call_656;
    goto end_match_929;
next_931:;
    struct AExpr_List* call_657 = listRev_1(acc_24);
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_429;
    tuple_429.t0 = call_657;
    tuple_429.t1 = tokens_232;
    tuple_429.t2 = errors_146;
    match_238 = tuple_429;
    goto end_match_929;
next_932:;
end_match_929:;
    return match_238;
}

struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseStmts_(struct IntIntTuple2 baseLoc_41, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_164) {
    struct Token_IntIntTuple2Tuple2List* tokens_231 = arg_164.t0;
    struct StringIntIntTuple2Tuple2List* errors_145 = arg_164.t1;
    struct IntIntTuple2 call_658 = nextLoc_1(tokens_231);
    struct IntIntTuple2 alignLoc_1 = call_658;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_240;
    int call_659 = locInside_(baseLoc_41, alignLoc_1);
    if ((!(call_659))) goto next_937;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_430;
    tuple_430.t0 = tokens_231;
    tuple_430.t1 = errors_145;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_660 = go_38(baseLoc_41, NULL, alignLoc_1, tuple_430);
    match_240 = call_660;
    goto end_match_936;
next_937:;
    if (call_659) goto next_938;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_431;
    tuple_431.t0 = NULL;
    tuple_431.t1 = tokens_231;
    tuple_431.t2 = errors_145;
    match_240 = tuple_431;
    goto end_match_936;
next_938:;
    exit(1);
end_match_936:;
    return match_240;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseSemi_(struct IntIntTuple2 baseLoc_42, struct IntIntTuple2 mainLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_165) {
    struct Token_IntIntTuple2Tuple2List* tokens_236 = arg_165.t0;
    struct StringIntIntTuple2Tuple2List* errors_149 = arg_165.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_432;
    tuple_432.t0 = tokens_236;
    tuple_432.t1 = errors_149;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_661 = parseStmts_(baseLoc_42, tuple_432);
    struct AExpr_List* items_7 = call_661.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_237 = call_661.t1;
    struct StringIntIntTuple2Tuple2List* errors_150 = call_661.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_241;
    if ((!((!(items_7))))) goto next_940;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_433;
    tuple_433.t0 = tokens_237;
    tuple_433.t1 = errors_150;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_662 = parseExprError_1((struct String){.str = "Expected statements", .len = 19}, tuple_433);
    match_241 = call_662;
    goto end_match_939;
next_940:;
    if ((!(items_7))) goto next_941;
    struct AExpr_ item_1 = items_7->head;
    if ((!((!(items_7->tail))))) goto next_941;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_434;
    tuple_434.t0 = item_1;
    tuple_434.t1 = tokens_237;
    tuple_434.t2 = errors_150;
    match_241 = tuple_434;
    goto end_match_939;
next_941:;
    struct AExpr_ListIntIntTuple2Tuple2 tuple_436;
    tuple_436.t0 = items_7;
    tuple_436.t1 = mainLoc_;
    struct AExpr_ListIntIntTuple2Tuple2* payload_140 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_140))) = tuple_436;
    struct AExpr_ variant_140 = (struct AExpr_){.tag = Semi_1, .Semi_1 = payload_140};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_435;
    tuple_435.t0 = variant_140;
    tuple_435.t1 = tokens_237;
    tuple_435.t2 = errors_150;
    match_241 = tuple_435;
    goto end_match_939;
next_942:;
end_match_939:;
    return match_241;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTopLevel_(struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_166) {
    struct Token_IntIntTuple2Tuple2List* tokens_238 = arg_166.t0;
    struct StringIntIntTuple2Tuple2List* errors_151 = arg_166.t1;
    struct IntIntTuple2 tuple_437;
    tuple_437.t0 = 0;
    tuple_437.t1 = 0;
    struct IntIntTuple2 topLoc_ = tuple_437;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_242;
    if ((!((!(tokens_238))))) goto next_944;
    struct AExpr_ListIntIntTuple2Tuple2 tuple_439;
    tuple_439.t0 = NULL;
    tuple_439.t1 = topLoc_;
    struct AExpr_ListIntIntTuple2Tuple2* payload_141 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_141))) = tuple_439;
    struct AExpr_ variant_141 = (struct AExpr_){.tag = TupleLit_1, .TupleLit_1 = payload_141};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_438;
    tuple_438.t0 = variant_141;
    tuple_438.t1 = tokens_238;
    tuple_438.t2 = errors_151;
    match_242 = tuple_438;
    goto end_match_943;
next_944:;
    if ((!(tokens_238))) goto next_945;
    if ((tokens_238->head.t0.tag != Module_)) goto next_945;
    struct IntIntTuple2 moduleLoc_ = tokens_238->head.t1;
    if ((!(tokens_238->tail))) goto next_945;
    if ((tokens_238->tail->head.t0.tag != Rec_)) goto next_945;
    if ((!(tokens_238->tail->tail))) goto next_945;
    if ((tokens_238->tail->tail->head.t0.tag != Ident_)) goto next_945;
    if ((!(tokens_238->tail->tail->tail))) goto next_945;
    if ((tokens_238->tail->tail->tail->head.t0.tag != Dot_)) goto next_945;
    if ((!(tokens_238->tail->tail->tail->tail))) goto next_945;
    if ((tokens_238->tail->tail->tail->tail->head.t0.tag != Ident_)) goto next_945;
    struct Token_IntIntTuple2Tuple2List* tokens_239 = tokens_238->tail->tail->tail->tail->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_440;
    tuple_440.t0 = tokens_239;
    tuple_440.t1 = errors_151;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_663 = parseSemi_(moduleLoc_, moduleLoc_, tuple_440);
    match_242 = call_663;
    goto end_match_943;
next_945:;
    if ((!(tokens_238))) goto next_946;
    if ((tokens_238->head.t0.tag != Module_)) goto next_946;
    struct IntIntTuple2 moduleLoc_1 = tokens_238->head.t1;
    if ((!(tokens_238->tail))) goto next_946;
    if ((tokens_238->tail->head.t0.tag != Rec_)) goto next_946;
    if ((!(tokens_238->tail->tail))) goto next_946;
    if ((tokens_238->tail->tail->head.t0.tag != Ident_)) goto next_946;
    struct Token_IntIntTuple2Tuple2List* tokens_240 = tokens_238->tail->tail->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_441;
    tuple_441.t0 = tokens_240;
    tuple_441.t1 = errors_151;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_664 = parseSemi_(moduleLoc_1, moduleLoc_1, tuple_441);
    match_242 = call_664;
    goto end_match_943;
next_946:;
    if ((!(tokens_238))) goto next_947;
    if ((tokens_238->head.t0.tag != Module_)) goto next_947;
    struct IntIntTuple2 moduleLoc_2 = tokens_238->head.t1;
    if ((!(tokens_238->tail))) goto next_947;
    if ((tokens_238->tail->head.t0.tag != Ident_)) goto next_947;
    struct Token_IntIntTuple2Tuple2List* tokens_241 = tokens_238->tail->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_442;
    tuple_442.t0 = tokens_241;
    tuple_442.t1 = errors_151;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_665 = parseSemi_(moduleLoc_2, moduleLoc_2, tuple_442);
    match_242 = call_665;
    goto end_match_943;
next_947:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_443;
    tuple_443.t0 = tokens_238;
    tuple_443.t1 = errors_151;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_666 = parseSemi_(topLoc_, topLoc_, tuple_443);
    match_242 = call_666;
    goto end_match_943;
next_948:;
end_match_943:;
    return match_242;
}

struct AExpr_StringIntIntTuple2Tuple2ListTuple2 {
    struct AExpr_ t0;
    struct StringIntIntTuple2Tuple2List* t1;
};

struct AExpr_StringIntIntTuple2Tuple2ListTuple2 parse_(struct Token_IntIntTuple2Tuple2List* tokens_242) {
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_444;
    tuple_444.t0 = tokens_242;
    tuple_444.t1 = NULL;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_667 = parseTopLevel_(tuple_444);
    struct AExpr_ expr_16 = call_667.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_243 = call_667.t1;
    struct StringIntIntTuple2Tuple2List* errors_152 = call_667.t2;
    struct StringIntIntTuple2Tuple2List* match_243;
    if ((!((!(tokens_243))))) goto next_950;
    match_243 = errors_152;
    goto end_match_949;
next_950:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_445;
    tuple_445.t0 = tokens_243;
    tuple_445.t1 = errors_152;
    struct StringIntIntTuple2Tuple2List* call_668 = parseNewError_1((struct String){.str = "Expected eof", .len = 12}, tuple_445);
    match_243 = call_668;
    goto end_match_949;
next_951:;
end_match_949:;
    struct StringIntIntTuple2Tuple2List* errors_153 = match_243;
    struct AExpr_StringIntIntTuple2Tuple2ListTuple2 tuple_446;
    tuple_446.t0 = expr_16;
    tuple_446.t1 = errors_153;
    return tuple_446;
}

struct HPrim_ opToPrim_(struct Op_ op_2) {
    struct HPrim_ match_244;
    if ((op_2.tag != Add_1)) goto next_953;
    match_244 = (struct HPrim_){.tag = Add_3};
    goto end_match_952;
next_953:;
    if ((op_2.tag != Sub_)) goto next_954;
    match_244 = (struct HPrim_){.tag = Sub_1};
    goto end_match_952;
next_954:;
    if ((op_2.tag != Mul_1)) goto next_955;
    match_244 = (struct HPrim_){.tag = Mul_2};
    goto end_match_952;
next_955:;
    if ((op_2.tag != Div_)) goto next_956;
    match_244 = (struct HPrim_){.tag = Div_1};
    goto end_match_952;
next_956:;
    if ((op_2.tag != Mod_)) goto next_957;
    match_244 = (struct HPrim_){.tag = Mod_1};
    goto end_match_952;
next_957:;
    if ((op_2.tag != Eq_1)) goto next_958;
    match_244 = (struct HPrim_){.tag = Eq_3};
    goto end_match_952;
next_958:;
    if ((op_2.tag != Lt_1)) goto next_959;
    match_244 = (struct HPrim_){.tag = Lt_2};
    goto end_match_952;
next_959:;
    if ((op_2.tag != Cons_1)) goto next_961;
    match_244 = (struct HPrim_){.tag = Cons_4};
    goto end_match_952;
next_961:;
    if ((op_2.tag != Ne_)) goto next_962;
    goto match_body_960;
next_962:;
    if ((op_2.tag != Le_)) goto next_963;
    goto match_body_960;
next_963:;
    if ((op_2.tag != Gt_1)) goto next_964;
    goto match_body_960;
next_964:;
    if ((op_2.tag != Ge_)) goto next_965;
    goto match_body_960;
next_965:;
    if ((op_2.tag != And_1)) goto next_966;
    goto match_body_960;
next_966:;
    if ((op_2.tag != Or_1)) goto next_967;
    goto match_body_960;
next_967:;
    if ((op_2.tag != App_)) goto next_968;
    goto match_body_960;
next_968:;
    if ((op_2.tag != Pipe_2)) goto next_969;
    goto match_body_960;
match_body_960:;
    struct Op_HPrim_Fun1 call_669 = failwithf_3((struct String){.str = "NEVER: %A", .len = 9});
    struct HPrim_ app_62 = call_669.fun(call_669.env, op_2);
    match_244 = app_62;
    goto end_match_952;
next_969:;
end_match_952:;
    return match_244;
}

struct APat_ go_39(struct IntIntTuple2 loc_69, struct APat_List* pats_5) {
    struct APat_ match_245;
    if ((!((!(pats_5))))) goto next_971;
    struct APat_ListIntIntTuple2Tuple2 tuple_447;
    tuple_447.t0 = NULL;
    tuple_447.t1 = loc_69;
    struct APat_ListIntIntTuple2Tuple2* payload_142 = (struct APat_ListIntIntTuple2Tuple2*)malloc(sizeof(struct APat_ListIntIntTuple2Tuple2));
    (*(((struct APat_ListIntIntTuple2Tuple2*)payload_142))) = tuple_447;
    struct APat_ variant_142 = (struct APat_){.tag = ListLit_, .ListLit_ = payload_142};
    match_245 = variant_142;
    goto end_match_970;
next_971:;
    if ((!(pats_5))) goto next_972;
    struct APat_ head_3 = pats_5->head;
    struct APat_List* tail_3 = pats_5->tail;
    struct APat_ call_670 = go_39(loc_69, tail_3);
    struct APat_ tail_4 = call_670;
    struct APat_APat_IntIntTuple2Tuple3 tuple_448;
    tuple_448.t0 = head_3;
    tuple_448.t1 = tail_4;
    tuple_448.t2 = loc_69;
    struct APat_APat_IntIntTuple2Tuple3* payload_143 = (struct APat_APat_IntIntTuple2Tuple3*)malloc(sizeof(struct APat_APat_IntIntTuple2Tuple3));
    (*(((struct APat_APat_IntIntTuple2Tuple3*)payload_143))) = tuple_448;
    struct APat_ variant_143 = (struct APat_){.tag = Cons_2, .Cons_2 = payload_143};
    match_245 = variant_143;
    goto end_match_970;
next_972:;
    exit(1);
end_match_970:;
    return match_245;
}

struct APat_ desugarListLitPat_(struct APat_List* pats_4, struct IntIntTuple2 loc_69) {
    int call_671 = listIsEmpty_2(pats_4);
    milone_assert((!(call_671)), 64, 2);
    int call_672 = 0;
    struct APat_ call_673 = go_39(loc_69, pats_4);
    return call_673;
}

struct AExpr_ go_40(struct IntIntTuple2 loc_70, struct AExpr_List* items_9) {
    struct AExpr_ match_246;
    if ((!((!(items_9))))) goto next_974;
    struct AExpr_ListIntIntTuple2Tuple2 tuple_449;
    tuple_449.t0 = NULL;
    tuple_449.t1 = loc_70;
    struct AExpr_ListIntIntTuple2Tuple2* payload_144 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_144))) = tuple_449;
    struct AExpr_ variant_144 = (struct AExpr_){.tag = ListLit_1, .ListLit_1 = payload_144};
    match_246 = variant_144;
    goto end_match_973;
next_974:;
    if ((!(items_9))) goto next_975;
    struct AExpr_ head_4 = items_9->head;
    struct AExpr_List* tail_5 = items_9->tail;
    struct AExpr_ call_674 = go_40(loc_70, tail_5);
    struct AExpr_ tail_6 = call_674;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_450;
    tuple_450.t0 = (struct Op_){.tag = Cons_1};
    tuple_450.t1 = head_4;
    tuple_450.t2 = tail_6;
    tuple_450.t3 = loc_70;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_145 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_145))) = tuple_450;
    struct AExpr_ variant_145 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_145};
    match_246 = variant_145;
    goto end_match_973;
next_975:;
    exit(1);
end_match_973:;
    return match_246;
}

struct AExpr_ desugarListLitExpr_(struct AExpr_List* items_8, struct IntIntTuple2 loc_70) {
    int call_675 = listIsEmpty_1(items_8);
    milone_assert((!(call_675)), 79, 2);
    int call_676 = 0;
    struct AExpr_ call_677 = go_40(loc_70, items_8);
    return call_677;
}

struct AExpr_ desugarIf_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct AExpr_ cond_2, struct AExpr_ body_13, struct AExpr_ alt_2, struct IntIntTuple2 loc_71) {
    struct AExpr_ match_247;
    if ((alt_2.tag != Missing_2)) goto next_977;
    struct AExpr_ call_678 = axUnit_(loc_71);
    match_247 = call_678;
    goto end_match_976;
next_977:;
    match_247 = alt_2;
    goto end_match_976;
next_978:;
end_match_976:;
    struct AExpr_ alt_3 = match_247;
    struct APat_ call_679 = apTrue_(litTrue_, loc_71);
    struct AExpr_ call_680 = axTrue_(litTrue_, loc_71);
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4 tuple_451;
    tuple_451.t0 = call_679;
    tuple_451.t1 = call_680;
    tuple_451.t2 = body_13;
    tuple_451.t3 = loc_71;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4* payload_146 = (struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct APat_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)payload_146))) = tuple_451;
    struct AArm_ variant_146 = (struct AArm_){.tag = AArm_, .AArm_ = payload_146};
    struct APat_ call_681 = apFalse_(litFalse_, loc_71);
    struct AExpr_ call_682 = axTrue_(litTrue_, loc_71);
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4 tuple_452;
    tuple_452.t0 = call_681;
    tuple_452.t1 = call_682;
    tuple_452.t2 = alt_3;
    tuple_452.t3 = loc_71;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4* payload_147 = (struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct APat_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)payload_147))) = tuple_452;
    struct AArm_ variant_147 = (struct AArm_){.tag = AArm_, .AArm_ = payload_147};
    struct AArm_List* list_77 = (struct AArm_List*)malloc(sizeof(struct AArm_List));
    list_77->head = variant_147;
    list_77->tail = NULL;
    struct AArm_List* list_76 = (struct AArm_List*)malloc(sizeof(struct AArm_List));
    list_76->head = variant_146;
    list_76->tail = list_77;
    struct AArm_List* arms_4 = list_76;
    struct AExpr_AArm_ListIntIntTuple2Tuple3 tuple_453;
    tuple_453.t0 = cond_2;
    tuple_453.t1 = arms_4;
    tuple_453.t2 = loc_71;
    struct AExpr_AArm_ListIntIntTuple2Tuple3* payload_148 = (struct AExpr_AArm_ListIntIntTuple2Tuple3*)malloc(sizeof(struct AExpr_AArm_ListIntIntTuple2Tuple3));
    (*(((struct AExpr_AArm_ListIntIntTuple2Tuple3*)payload_148))) = tuple_453;
    struct AExpr_ variant_148 = (struct AExpr_){.tag = Match_1, .Match_1 = payload_148};
    return variant_148;
}

struct AExpr_ desugarFun_(struct APat_List* pats_6, struct AExpr_ body_14, struct IntIntTuple2 loc_72) {
    struct String ident_25 = (struct String){.str = "fun", .len = 3};
    struct StringAPat_ListIntIntTuple2Tuple3 tuple_454;
    tuple_454.t0 = ident_25;
    tuple_454.t1 = pats_6;
    tuple_454.t2 = loc_72;
    struct StringAPat_ListIntIntTuple2Tuple3* payload_149 = (struct StringAPat_ListIntIntTuple2Tuple3*)malloc(sizeof(struct StringAPat_ListIntIntTuple2Tuple3));
    (*(((struct StringAPat_ListIntIntTuple2Tuple3*)payload_149))) = tuple_454;
    struct APat_ variant_149 = (struct APat_){.tag = Fun_2, .Fun_2 = payload_149};
    struct APat_ pat_23 = variant_149;
    struct StringIntIntTuple2Tuple2 tuple_455;
    tuple_455.t0 = ident_25;
    tuple_455.t1 = loc_72;
    struct StringIntIntTuple2Tuple2* payload_150 = (struct StringIntIntTuple2Tuple2*)malloc(sizeof(struct StringIntIntTuple2Tuple2));
    (*(((struct StringIntIntTuple2Tuple2*)payload_150))) = tuple_455;
    struct AExpr_ variant_150 = (struct AExpr_){.tag = Ident_3, .Ident_3 = payload_150};
    struct AExpr_ next_10 = variant_150;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4 tuple_456;
    tuple_456.t0 = pat_23;
    tuple_456.t1 = body_14;
    tuple_456.t2 = next_10;
    tuple_456.t3 = loc_72;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4* payload_151 = (struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct APat_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)payload_151))) = tuple_456;
    struct AExpr_ variant_151 = (struct AExpr_){.tag = Let_1, .Let_1 = payload_151};
    return variant_151;
}

struct AExpr_ desugarUniNeg_(struct AExpr_ arg_4, struct IntIntTuple2 loc_73) {
    int* payload_152 = (int*)malloc(sizeof(int));
    (*(((int*)payload_152))) = 0;
    struct Lit_ variant_152 = (struct Lit_){.tag = Int_, .Int_ = payload_152};
    struct Lit_IntIntTuple2Tuple2 tuple_457;
    tuple_457.t0 = variant_152;
    tuple_457.t1 = loc_73;
    struct Lit_IntIntTuple2Tuple2* payload_153 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_153))) = tuple_457;
    struct AExpr_ variant_153 = (struct AExpr_){.tag = Lit_1, .Lit_1 = payload_153};
    struct AExpr_ zero_ = variant_153;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_458;
    tuple_458.t0 = (struct Op_){.tag = Sub_};
    tuple_458.t1 = zero_;
    tuple_458.t2 = arg_4;
    tuple_458.t3 = loc_73;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_154 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_154))) = tuple_458;
    struct AExpr_ variant_154 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_154};
    return variant_154;
}

struct AExpr_ desugarBinNe_(struct Lit_ litFalse_, struct AExpr_ l_17, struct AExpr_ r_31, struct IntIntTuple2 loc_74) {
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_459;
    tuple_459.t0 = (struct Op_){.tag = Eq_1};
    tuple_459.t1 = l_17;
    tuple_459.t2 = r_31;
    tuple_459.t3 = loc_74;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_155 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_155))) = tuple_459;
    struct AExpr_ variant_155 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_155};
    struct AExpr_ eqExpr_ = variant_155;
    struct AExpr_ call_683 = axNot_(litFalse_, eqExpr_, loc_74);
    return call_683;
}

struct AExpr_ desugarBinLe_(struct Lit_ litFalse_, struct AExpr_ l_18, struct AExpr_ r_32, struct IntIntTuple2 loc_75) {
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_460;
    tuple_460.t0 = (struct Op_){.tag = Lt_1};
    tuple_460.t1 = r_32;
    tuple_460.t2 = l_18;
    tuple_460.t3 = loc_75;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_156 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_156))) = tuple_460;
    struct AExpr_ variant_156 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_156};
    struct AExpr_ ltExpr_ = variant_156;
    struct AExpr_ call_684 = axNot_(litFalse_, ltExpr_, loc_75);
    return call_684;
}

struct AExpr_ desugarBinGt_(struct AExpr_ l_19, struct AExpr_ r_33, struct IntIntTuple2 loc_76) {
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_461;
    tuple_461.t0 = (struct Op_){.tag = Lt_1};
    tuple_461.t1 = r_33;
    tuple_461.t2 = l_19;
    tuple_461.t3 = loc_76;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_157 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_157))) = tuple_461;
    struct AExpr_ variant_157 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_157};
    return variant_157;
}

struct AExpr_ desugarBinGe_(struct Lit_ litFalse_, struct AExpr_ l_20, struct AExpr_ r_34, struct IntIntTuple2 loc_77) {
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_462;
    tuple_462.t0 = (struct Op_){.tag = Lt_1};
    tuple_462.t1 = l_20;
    tuple_462.t2 = r_34;
    tuple_462.t3 = loc_77;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_158 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_158))) = tuple_462;
    struct AExpr_ variant_158 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_158};
    struct AExpr_ ltExpr_1 = variant_158;
    struct AExpr_ call_685 = axNot_(litFalse_, ltExpr_1, loc_77);
    return call_685;
}

struct AExpr_ desugarBinAnd_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct AExpr_ l_21, struct AExpr_ r_35, struct IntIntTuple2 loc_78) {
    struct AExpr_ call_686 = axFalse_(litFalse_, loc_78);
    struct AExpr_ call_687 = desugarIf_(litFalse_, litTrue_, l_21, r_35, call_686, loc_78);
    return call_687;
}

struct AExpr_ desugarBinOr_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct AExpr_ l_22, struct AExpr_ r_36, struct IntIntTuple2 loc_79) {
    struct AExpr_ call_688 = axTrue_(litTrue_, loc_79);
    struct AExpr_ call_689 = desugarIf_(litFalse_, litTrue_, l_22, call_688, r_36, loc_79);
    return call_689;
}

struct AExpr_ desugarBinPipe_(struct AExpr_ l_23, struct AExpr_ r_37, struct IntIntTuple2 loc_80) {
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_463;
    tuple_463.t0 = (struct Op_){.tag = App_};
    tuple_463.t1 = r_37;
    tuple_463.t2 = l_23;
    tuple_463.t3 = loc_80;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_159 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_159))) = tuple_463;
    struct AExpr_ variant_159 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_159};
    return variant_159;
}

struct BoolAExpr_Tuple2 {
    int t0;
    struct AExpr_ t1;
};

struct BoolAExpr_Tuple2 tryDesugarIndexRange_(struct AExpr_ expr_17, struct IntIntTuple2 loc_81) {
    struct BoolAExpr_Tuple2 match_248;
    if ((expr_17.tag != Index_)) goto next_980;
    struct AExpr_ s_8 = (*(expr_17.Index_)).t0;
    if (((*(expr_17.Index_)).t1.tag != Range_)) goto next_980;
    if ((!((*((*(expr_17.Index_)).t1.Range_)).t0))) goto next_980;
    struct AExpr_ l_24 = (*((*(expr_17.Index_)).t1.Range_)).t0->head;
    if ((!((*((*(expr_17.Index_)).t1.Range_)).t0->tail))) goto next_980;
    struct AExpr_ r_38 = (*((*(expr_17.Index_)).t1.Range_)).t0->tail->head;
    if ((!((!((*((*(expr_17.Index_)).t1.Range_)).t0->tail->tail))))) goto next_980;
    struct StringIntIntTuple2Tuple2 tuple_465;
    tuple_465.t0 = (struct String){.str = "String", .len = 6};
    tuple_465.t1 = loc_81;
    struct StringIntIntTuple2Tuple2* payload_160 = (struct StringIntIntTuple2Tuple2*)malloc(sizeof(struct StringIntIntTuple2Tuple2));
    (*(((struct StringIntIntTuple2Tuple2*)payload_160))) = tuple_465;
    struct AExpr_ variant_160 = (struct AExpr_){.tag = Ident_3, .Ident_3 = payload_160};
    struct AExpr_StringIntIntTuple2Tuple3 tuple_464;
    tuple_464.t0 = variant_160;
    tuple_464.t1 = (struct String){.str = "getSlice", .len = 8};
    tuple_464.t2 = loc_81;
    struct AExpr_StringIntIntTuple2Tuple3* payload_161 = (struct AExpr_StringIntIntTuple2Tuple3*)malloc(sizeof(struct AExpr_StringIntIntTuple2Tuple3));
    (*(((struct AExpr_StringIntIntTuple2Tuple3*)payload_161))) = tuple_464;
    struct AExpr_ variant_161 = (struct AExpr_){.tag = Nav_1, .Nav_1 = payload_161};
    struct AExpr_ getSlice_ = variant_161;
    struct AExpr_ call_690 = axApp3_(getSlice_, l_24, r_38, s_8, loc_81);
    struct BoolAExpr_Tuple2 tuple_466;
    tuple_466.t0 = 1;
    tuple_466.t1 = call_690;
    match_248 = tuple_466;
    goto end_match_979;
next_980:;
    struct BoolAExpr_Tuple2 tuple_467;
    tuple_467.t0 = 0;
    tuple_467.t1 = expr_17;
    match_248 = tuple_467;
    goto end_match_979;
next_981:;
end_match_979:;
    return match_248;
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

struct ALet_ desugarLet_(struct APat_ pat_24, struct AExpr_ body_15, struct AExpr_ next_11, struct IntIntTuple2 loc_82) {
    struct ALet_ match_249;
    if ((pat_24.tag != Anno_)) goto next_983;
    struct APat_ pat_25 = (*(pat_24.Anno_)).t0;
    struct ATy_ annoTy_ = (*(pat_24.Anno_)).t1;
    struct IntIntTuple2 annoLoc_ = (*(pat_24.Anno_)).t2;
    struct AExpr_ATy_IntIntTuple2Tuple3 tuple_468;
    tuple_468.t0 = body_15;
    tuple_468.t1 = annoTy_;
    tuple_468.t2 = annoLoc_;
    struct AExpr_ATy_IntIntTuple2Tuple3* payload_162 = (struct AExpr_ATy_IntIntTuple2Tuple3*)malloc(sizeof(struct AExpr_ATy_IntIntTuple2Tuple3));
    (*(((struct AExpr_ATy_IntIntTuple2Tuple3*)payload_162))) = tuple_468;
    struct AExpr_ variant_162 = (struct AExpr_){.tag = Anno_1, .Anno_1 = payload_162};
    struct AExpr_ body_16 = variant_162;
    struct ALet_ call_691 = desugarLet_(pat_25, body_16, next_11, loc_82);
    match_249 = call_691;
    goto end_match_982;
next_983:;
    if ((pat_24.tag != Fun_2)) goto next_984;
    struct String ident_26 = (*(pat_24.Fun_2)).t0;
    struct APat_List* args_8 = (*(pat_24.Fun_2)).t1;
    struct StringAPat_ListAExpr_AExpr_IntIntTuple2Tuple5 tuple_469;
    tuple_469.t0 = ident_26;
    tuple_469.t1 = args_8;
    tuple_469.t2 = body_15;
    tuple_469.t3 = next_11;
    tuple_469.t4 = loc_82;
    struct StringAPat_ListAExpr_AExpr_IntIntTuple2Tuple5* payload_163 = (struct StringAPat_ListAExpr_AExpr_IntIntTuple2Tuple5*)malloc(sizeof(struct StringAPat_ListAExpr_AExpr_IntIntTuple2Tuple5));
    (*(((struct StringAPat_ListAExpr_AExpr_IntIntTuple2Tuple5*)payload_163))) = tuple_469;
    struct ALet_ variant_163 = (struct ALet_){.tag = LetFun_, .LetFun_ = payload_163};
    match_249 = variant_163;
    goto end_match_982;
next_984:;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4 tuple_470;
    tuple_470.t0 = pat_24;
    tuple_470.t1 = body_15;
    tuple_470.t2 = next_11;
    tuple_470.t3 = loc_82;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4* payload_164 = (struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct APat_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)payload_164))) = tuple_470;
    struct ALet_ variant_164 = (struct ALet_){.tag = LetVal_, .LetVal_ = payload_164};
    match_249 = variant_164;
    goto end_match_982;
next_985:;
end_match_982:;
    return match_249;
}

struct Ty_NameCtx_Tuple2 fun_8(void* env_6, struct ATy_NameCtx_Tuple2 arg_27) {
    struct Ty_NameCtx_Tuple2 call_692 = onTy_(arg_27);
    return call_692;
}

struct Ty_NameCtx_Tuple2 onTy_(struct ATy_NameCtx_Tuple2 arg_167) {
    struct ATy_ ty_55 = arg_167.t0;
    struct NameCtx_ nameCtx_2 = arg_167.t1;
    struct Ty_NameCtx_Tuple2 match_250;
    if ((ty_55.tag != Missing_)) goto next_987;
    struct IntIntTuple2 loc_83 = (*(ty_55.Missing_));
    struct IntIntTuple2* payload_165 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_165))) = loc_83;
    struct Ty_ variant_165 = (struct Ty_){.tag = Error_1, .Error_1 = payload_165};
    struct Ty_NameCtx_Tuple2 tuple_471;
    tuple_471.t0 = variant_165;
    tuple_471.t1 = nameCtx_2;
    match_250 = tuple_471;
    goto end_match_986;
next_987:;
    if ((ty_55.tag != Ident_1)) goto next_988;
    struct String ident_27 = (*(ty_55.Ident_1)).t0;
    struct IntNameCtx_Tuple2 call_693 = nameCtxAdd_1(ident_27, nameCtx_2);
    int tySerial_1 = call_693.t0;
    struct NameCtx_ nameCtx_3 = call_693.t1;
    struct Ty_ call_694 = tyRef_(tySerial_1, NULL);
    struct Ty_NameCtx_Tuple2 tuple_472;
    tuple_472.t0 = call_694;
    tuple_472.t1 = nameCtx_3;
    match_250 = tuple_472;
    goto end_match_986;
next_988:;
    if ((ty_55.tag != Suffix_)) goto next_989;
    struct ATy_ lTy_3 = (*(ty_55.Suffix_)).t0;
    struct String ident_28 = (*(ty_55.Suffix_)).t1;
    struct ATy_NameCtx_Tuple2 tuple_473;
    tuple_473.t0 = lTy_3;
    tuple_473.t1 = nameCtx_2;
    struct Ty_NameCtx_Tuple2 call_695 = onTy_(tuple_473);
    struct Ty_ lTy_4 = call_695.t0;
    struct NameCtx_ nameCtx_4 = call_695.t1;
    struct IntNameCtx_Tuple2 call_696 = nameCtxAdd_1(ident_28, nameCtx_4);
    int tySerial_2 = call_696.t0;
    struct NameCtx_ nameCtx_5 = call_696.t1;
    struct Ty_List* list_78 = (struct Ty_List*)malloc(sizeof(struct Ty_List));
    list_78->head = lTy_4;
    list_78->tail = NULL;
    struct Ty_ call_697 = tyRef_(tySerial_2, list_78);
    struct Ty_NameCtx_Tuple2 tuple_474;
    tuple_474.t0 = call_697;
    tuple_474.t1 = nameCtx_5;
    match_250 = tuple_474;
    goto end_match_986;
next_989:;
    if ((ty_55.tag != Tuple_)) goto next_990;
    struct ATy_List* itemTys_2 = (*(ty_55.Tuple_)).t0;
    void* box_6 = (void*)malloc(sizeof(int));
    (*(((int*)box_6))) = 0;
    void* env_35 = box_6;
    struct ATy_NameCtx_Tuple2Ty_NameCtx_Tuple2Fun1 fun_37 = (struct ATy_NameCtx_Tuple2Ty_NameCtx_Tuple2Fun1){.fun = fun_8, .env = env_35};
    struct ATy_ListNameCtx_Tuple2 tuple_475;
    tuple_475.t0 = itemTys_2;
    tuple_475.t1 = nameCtx_2;
    struct Ty_ListNameCtx_Tuple2 call_698 = stMap_4(fun_37, tuple_475);
    struct Ty_List* itemTys_3 = call_698.t0;
    struct NameCtx_ nameCtx_6 = call_698.t1;
    struct Ty_ call_699 = tyTuple_(itemTys_3);
    struct Ty_NameCtx_Tuple2 tuple_476;
    tuple_476.t0 = call_699;
    tuple_476.t1 = nameCtx_6;
    match_250 = tuple_476;
    goto end_match_986;
next_990:;
    if ((ty_55.tag != Fun_1)) goto next_991;
    struct ATy_ sTy_2 = (*(ty_55.Fun_1)).t0;
    struct ATy_ tTy_2 = (*(ty_55.Fun_1)).t1;
    struct ATy_NameCtx_Tuple2 tuple_477;
    tuple_477.t0 = sTy_2;
    tuple_477.t1 = nameCtx_2;
    struct Ty_NameCtx_Tuple2 call_700 = onTy_(tuple_477);
    struct Ty_ sTy_3 = call_700.t0;
    struct NameCtx_ nameCtx_7 = call_700.t1;
    struct ATy_NameCtx_Tuple2 tuple_478;
    tuple_478.t0 = tTy_2;
    tuple_478.t1 = nameCtx_7;
    struct Ty_NameCtx_Tuple2 call_701 = onTy_(tuple_478);
    struct Ty_ tTy_3 = call_701.t0;
    struct NameCtx_ nameCtx_8 = call_701.t1;
    struct Ty_ call_702 = tyFun_(sTy_3, tTy_3);
    struct Ty_NameCtx_Tuple2 tuple_479;
    tuple_479.t0 = call_702;
    tuple_479.t1 = nameCtx_8;
    match_250 = tuple_479;
    goto end_match_986;
next_991:;
    exit(1);
end_match_986:;
    return match_250;
}

struct Ty_Tuple1 {
    struct Ty_ t0;
};

struct HPat_NameCtx_Tuple2 fun_9(void* env_7, struct APat_NameCtx_Tuple2 arg_28) {
    struct Ty_ arg_29 = (*(((struct Ty_Tuple1*)env_7))).t0;
    struct HPat_NameCtx_Tuple2 call_703 = onPat_(arg_29, arg_28);
    return call_703;
}

struct HPat_NameCtx_Tuple2 fun_10(void* env_8, struct APat_NameCtx_Tuple2 arg_30) {
    struct Ty_ arg_31 = (*(((struct Ty_Tuple1*)env_8))).t0;
    struct HPat_NameCtx_Tuple2 call_704 = onPat_(arg_31, arg_30);
    return call_704;
}

struct HPat_NameCtx_Tuple2 onPat_(struct Ty_ noTy_, struct APat_NameCtx_Tuple2 arg_168) {
    struct APat_ pat_26 = arg_168.t0;
    struct NameCtx_ nameCtx_9 = arg_168.t1;
    struct HPat_NameCtx_Tuple2 match_251;
    if ((pat_26.tag != Missing_1)) goto next_993;
    int loc_84 = (*(pat_26.Missing_1)).t1;
    struct IntHPat_NameCtx_Tuple2Fun1 call_705 = failwithf_2((struct String){.str = "Missing pattern %A", .len = 18});
    struct HPat_NameCtx_Tuple2 app_63 = call_705.fun(call_705.env, loc_84);
    match_251 = app_63;
    goto end_match_992;
next_993:;
    if ((pat_26.tag != Lit_)) goto next_994;
    struct Lit_ lit_8 = (*(pat_26.Lit_)).t0;
    struct IntIntTuple2 loc_85 = (*(pat_26.Lit_)).t1;
    struct Lit_IntIntTuple2Tuple2 tuple_481;
    tuple_481.t0 = lit_8;
    tuple_481.t1 = loc_85;
    struct Lit_IntIntTuple2Tuple2* payload_166 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_166))) = tuple_481;
    struct HPat_ variant_166 = (struct HPat_){.tag = Lit_2, .Lit_2 = payload_166};
    struct HPat_NameCtx_Tuple2 tuple_480;
    tuple_480.t0 = variant_166;
    tuple_480.t1 = nameCtx_9;
    match_251 = tuple_480;
    goto end_match_992;
next_994:;
    if ((pat_26.tag != Ident_2)) goto next_995;
    struct String ident_29 = (*(pat_26.Ident_2)).t0;
    struct IntIntTuple2 loc_86 = (*(pat_26.Ident_2)).t1;
    struct IntNameCtx_Tuple2 call_706 = nameCtxAdd_1(ident_29, nameCtx_9);
    int serial_8 = call_706.t0;
    struct NameCtx_ nameCtx_10 = call_706.t1;
    struct IntTy_IntIntTuple2Tuple3 tuple_483;
    tuple_483.t0 = serial_8;
    tuple_483.t1 = noTy_;
    tuple_483.t2 = loc_86;
    struct IntTy_IntIntTuple2Tuple3* payload_167 = (struct IntTy_IntIntTuple2Tuple3*)malloc(sizeof(struct IntTy_IntIntTuple2Tuple3));
    (*(((struct IntTy_IntIntTuple2Tuple3*)payload_167))) = tuple_483;
    struct HPat_ variant_167 = (struct HPat_){.tag = Ref_1, .Ref_1 = payload_167};
    struct HPat_NameCtx_Tuple2 tuple_482;
    tuple_482.t0 = variant_167;
    tuple_482.t1 = nameCtx_10;
    match_251 = tuple_482;
    goto end_match_992;
next_995:;
    if ((pat_26.tag != ListLit_)) goto next_996;
    if ((!((!((*(pat_26.ListLit_)).t0))))) goto next_996;
    struct IntIntTuple2 loc_87 = (*(pat_26.ListLit_)).t1;
    struct HPat_ call_707 = patNil_(noTy_, loc_87);
    struct HPat_NameCtx_Tuple2 tuple_484;
    tuple_484.t0 = call_707;
    tuple_484.t1 = nameCtx_9;
    match_251 = tuple_484;
    goto end_match_992;
next_996:;
    if ((pat_26.tag != ListLit_)) goto next_997;
    struct APat_List* pats_7 = (*(pat_26.ListLit_)).t0;
    struct IntIntTuple2 loc_88 = (*(pat_26.ListLit_)).t1;
    struct APat_ call_708 = desugarListLitPat_(pats_7, loc_88);
    struct APat_ pat_27 = call_708;
    struct APat_NameCtx_Tuple2 tuple_485;
    tuple_485.t0 = pat_27;
    tuple_485.t1 = nameCtx_9;
    struct HPat_NameCtx_Tuple2 call_709 = onPat_(noTy_, tuple_485);
    match_251 = call_709;
    goto end_match_992;
next_997:;
    if ((pat_26.tag != Nav_)) goto next_998;
    struct APat_ l_25 = (*(pat_26.Nav_)).t0;
    struct String r_39 = (*(pat_26.Nav_)).t1;
    struct IntIntTuple2 loc_89 = (*(pat_26.Nav_)).t2;
    struct APat_NameCtx_Tuple2 tuple_486;
    tuple_486.t0 = l_25;
    tuple_486.t1 = nameCtx_9;
    struct HPat_NameCtx_Tuple2 call_710 = onPat_(noTy_, tuple_486);
    struct HPat_ l_26 = call_710.t0;
    struct NameCtx_ nameCtx_11 = call_710.t1;
    struct HPat_StringTy_IntIntTuple2Tuple4 tuple_488;
    tuple_488.t0 = l_26;
    tuple_488.t1 = r_39;
    tuple_488.t2 = noTy_;
    tuple_488.t3 = loc_89;
    struct HPat_StringTy_IntIntTuple2Tuple4* payload_168 = (struct HPat_StringTy_IntIntTuple2Tuple4*)malloc(sizeof(struct HPat_StringTy_IntIntTuple2Tuple4));
    (*(((struct HPat_StringTy_IntIntTuple2Tuple4*)payload_168))) = tuple_488;
    struct HPat_ variant_168 = (struct HPat_){.tag = Nav_2, .Nav_2 = payload_168};
    struct HPat_NameCtx_Tuple2 tuple_487;
    tuple_487.t0 = variant_168;
    tuple_487.t1 = nameCtx_11;
    match_251 = tuple_487;
    goto end_match_992;
next_998:;
    if ((pat_26.tag != Call_)) goto next_999;
    struct APat_ calleePat_1 = (*(pat_26.Call_)).t0;
    struct APat_List* argPats_1 = (*(pat_26.Call_)).t1;
    struct IntIntTuple2 loc_90 = (*(pat_26.Call_)).t2;
    struct APat_NameCtx_Tuple2 tuple_489;
    tuple_489.t0 = calleePat_1;
    tuple_489.t1 = nameCtx_9;
    struct HPat_NameCtx_Tuple2 call_711 = onPat_(noTy_, tuple_489);
    struct HPat_ calleePat_2 = call_711.t0;
    struct NameCtx_ nameCtx_12 = call_711.t1;
    struct Ty_Tuple1 tuple_490;
    tuple_490.t0 = noTy_;
    void* box_7 = (void*)malloc(sizeof(struct Ty_Tuple1));
    (*(((struct Ty_Tuple1*)box_7))) = tuple_490;
    void* env_36 = box_7;
    struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1 fun_38 = (struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1){.fun = fun_9, .env = env_36};
    struct APat_ListNameCtx_Tuple2 tuple_491;
    tuple_491.t0 = argPats_1;
    tuple_491.t1 = nameCtx_12;
    struct HPat_ListNameCtx_Tuple2 call_712 = stMap_1(fun_38, tuple_491);
    struct HPat_List* argPats_2 = call_712.t0;
    struct NameCtx_ nameCtx_13 = call_712.t1;
    struct HPat_HPat_ListTy_IntIntTuple2Tuple4 tuple_493;
    tuple_493.t0 = calleePat_2;
    tuple_493.t1 = argPats_2;
    tuple_493.t2 = noTy_;
    tuple_493.t3 = loc_90;
    struct HPat_HPat_ListTy_IntIntTuple2Tuple4* payload_169 = (struct HPat_HPat_ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct HPat_HPat_ListTy_IntIntTuple2Tuple4));
    (*(((struct HPat_HPat_ListTy_IntIntTuple2Tuple4*)payload_169))) = tuple_493;
    struct HPat_ variant_169 = (struct HPat_){.tag = Call_1, .Call_1 = payload_169};
    struct HPat_NameCtx_Tuple2 tuple_492;
    tuple_492.t0 = variant_169;
    tuple_492.t1 = nameCtx_13;
    match_251 = tuple_492;
    goto end_match_992;
next_999:;
    if ((pat_26.tag != Cons_2)) goto next_1000;
    struct APat_ head_5 = (*(pat_26.Cons_2)).t0;
    struct APat_ tail_7 = (*(pat_26.Cons_2)).t1;
    struct IntIntTuple2 loc_91 = (*(pat_26.Cons_2)).t2;
    struct APat_NameCtx_Tuple2 tuple_494;
    tuple_494.t0 = head_5;
    tuple_494.t1 = nameCtx_9;
    struct HPat_NameCtx_Tuple2 call_713 = onPat_(noTy_, tuple_494);
    struct HPat_ head_6 = call_713.t0;
    struct NameCtx_ nameCtx_14 = call_713.t1;
    struct APat_NameCtx_Tuple2 tuple_495;
    tuple_495.t0 = tail_7;
    tuple_495.t1 = nameCtx_14;
    struct HPat_NameCtx_Tuple2 call_714 = onPat_(noTy_, tuple_495);
    struct HPat_ tail_8 = call_714.t0;
    struct NameCtx_ nameCtx_15 = call_714.t1;
    struct HPat_HPat_Ty_IntIntTuple2Tuple4 tuple_497;
    tuple_497.t0 = head_6;
    tuple_497.t1 = tail_8;
    tuple_497.t2 = noTy_;
    tuple_497.t3 = loc_91;
    struct HPat_HPat_Ty_IntIntTuple2Tuple4* payload_170 = (struct HPat_HPat_Ty_IntIntTuple2Tuple4*)malloc(sizeof(struct HPat_HPat_Ty_IntIntTuple2Tuple4));
    (*(((struct HPat_HPat_Ty_IntIntTuple2Tuple4*)payload_170))) = tuple_497;
    struct HPat_ variant_170 = (struct HPat_){.tag = Cons_3, .Cons_3 = payload_170};
    struct HPat_NameCtx_Tuple2 tuple_496;
    tuple_496.t0 = variant_170;
    tuple_496.t1 = nameCtx_15;
    match_251 = tuple_496;
    goto end_match_992;
next_1000:;
    if ((pat_26.tag != TupleLit_)) goto next_1001;
    struct APat_List* pats_8 = (*(pat_26.TupleLit_)).t0;
    struct IntIntTuple2 loc_92 = (*(pat_26.TupleLit_)).t1;
    struct Ty_Tuple1 tuple_498;
    tuple_498.t0 = noTy_;
    void* box_8 = (void*)malloc(sizeof(struct Ty_Tuple1));
    (*(((struct Ty_Tuple1*)box_8))) = tuple_498;
    void* env_37 = box_8;
    struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1 fun_39 = (struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1){.fun = fun_10, .env = env_37};
    struct APat_ListNameCtx_Tuple2 tuple_499;
    tuple_499.t0 = pats_8;
    tuple_499.t1 = nameCtx_9;
    struct HPat_ListNameCtx_Tuple2 call_715 = stMap_1(fun_39, tuple_499);
    struct HPat_List* pats_9 = call_715.t0;
    struct NameCtx_ nameCtx_16 = call_715.t1;
    struct HPat_ListTy_IntIntTuple2Tuple3 tuple_501;
    tuple_501.t0 = pats_9;
    tuple_501.t1 = noTy_;
    tuple_501.t2 = loc_92;
    struct HPat_ListTy_IntIntTuple2Tuple3* payload_171 = (struct HPat_ListTy_IntIntTuple2Tuple3*)malloc(sizeof(struct HPat_ListTy_IntIntTuple2Tuple3));
    (*(((struct HPat_ListTy_IntIntTuple2Tuple3*)payload_171))) = tuple_501;
    struct HPat_ variant_171 = (struct HPat_){.tag = Tuple_2, .Tuple_2 = payload_171};
    struct HPat_NameCtx_Tuple2 tuple_500;
    tuple_500.t0 = variant_171;
    tuple_500.t1 = nameCtx_16;
    match_251 = tuple_500;
    goto end_match_992;
next_1001:;
    if ((pat_26.tag != As_1)) goto next_1002;
    struct APat_ pat_28 = (*(pat_26.As_1)).t0;
    struct String ident_30 = (*(pat_26.As_1)).t1;
    struct IntIntTuple2 loc_93 = (*(pat_26.As_1)).t2;
    struct IntNameCtx_Tuple2 call_716 = nameCtxAdd_1(ident_30, nameCtx_9);
    int serial_9 = call_716.t0;
    struct NameCtx_ nameCtx_17 = call_716.t1;
    struct APat_NameCtx_Tuple2 tuple_502;
    tuple_502.t0 = pat_28;
    tuple_502.t1 = nameCtx_17;
    struct HPat_NameCtx_Tuple2 call_717 = onPat_(noTy_, tuple_502);
    struct HPat_ pat_29 = call_717.t0;
    struct NameCtx_ nameCtx_18 = call_717.t1;
    struct HPat_IntIntIntTuple2Tuple3 tuple_504;
    tuple_504.t0 = pat_29;
    tuple_504.t1 = serial_9;
    tuple_504.t2 = loc_93;
    struct HPat_IntIntIntTuple2Tuple3* payload_172 = (struct HPat_IntIntIntTuple2Tuple3*)malloc(sizeof(struct HPat_IntIntIntTuple2Tuple3));
    (*(((struct HPat_IntIntIntTuple2Tuple3*)payload_172))) = tuple_504;
    struct HPat_ variant_172 = (struct HPat_){.tag = As_2, .As_2 = payload_172};
    struct HPat_NameCtx_Tuple2 tuple_503;
    tuple_503.t0 = variant_172;
    tuple_503.t1 = nameCtx_18;
    match_251 = tuple_503;
    goto end_match_992;
next_1002:;
    if ((pat_26.tag != Anno_)) goto next_1003;
    struct APat_ pat_30 = (*(pat_26.Anno_)).t0;
    struct ATy_ ty_56 = (*(pat_26.Anno_)).t1;
    struct IntIntTuple2 loc_94 = (*(pat_26.Anno_)).t2;
    struct APat_NameCtx_Tuple2 tuple_505;
    tuple_505.t0 = pat_30;
    tuple_505.t1 = nameCtx_9;
    struct HPat_NameCtx_Tuple2 call_718 = onPat_(noTy_, tuple_505);
    struct HPat_ pat_31 = call_718.t0;
    struct NameCtx_ nameCtx_19 = call_718.t1;
    struct ATy_NameCtx_Tuple2 tuple_506;
    tuple_506.t0 = ty_56;
    tuple_506.t1 = nameCtx_19;
    struct Ty_NameCtx_Tuple2 call_719 = onTy_(tuple_506);
    struct Ty_ ty_57 = call_719.t0;
    struct NameCtx_ nameCtx_20 = call_719.t1;
    struct HPat_Ty_IntIntTuple2Tuple3 tuple_508;
    tuple_508.t0 = pat_31;
    tuple_508.t1 = ty_57;
    tuple_508.t2 = loc_94;
    struct HPat_Ty_IntIntTuple2Tuple3* payload_173 = (struct HPat_Ty_IntIntTuple2Tuple3*)malloc(sizeof(struct HPat_Ty_IntIntTuple2Tuple3));
    (*(((struct HPat_Ty_IntIntTuple2Tuple3*)payload_173))) = tuple_508;
    struct HPat_ variant_173 = (struct HPat_){.tag = Anno_2, .Anno_2 = payload_173};
    struct HPat_NameCtx_Tuple2 tuple_507;
    tuple_507.t0 = variant_173;
    tuple_507.t1 = nameCtx_20;
    match_251 = tuple_507;
    goto end_match_992;
next_1003:;
    if ((pat_26.tag != Or_2)) goto next_1004;
    struct APat_ l_27 = (*(pat_26.Or_2)).t0;
    struct APat_ r_40 = (*(pat_26.Or_2)).t1;
    struct IntIntTuple2 loc_95 = (*(pat_26.Or_2)).t2;
    struct APat_NameCtx_Tuple2 tuple_509;
    tuple_509.t0 = l_27;
    tuple_509.t1 = nameCtx_9;
    struct HPat_NameCtx_Tuple2 call_720 = onPat_(noTy_, tuple_509);
    struct HPat_ l_28 = call_720.t0;
    struct NameCtx_ nameCtx_21 = call_720.t1;
    struct APat_NameCtx_Tuple2 tuple_510;
    tuple_510.t0 = r_40;
    tuple_510.t1 = nameCtx_21;
    struct HPat_NameCtx_Tuple2 call_721 = onPat_(noTy_, tuple_510);
    struct HPat_ r_41 = call_721.t0;
    struct NameCtx_ nameCtx_22 = call_721.t1;
    struct HPat_HPat_Ty_IntIntTuple2Tuple4 tuple_512;
    tuple_512.t0 = l_28;
    tuple_512.t1 = r_41;
    tuple_512.t2 = noTy_;
    tuple_512.t3 = loc_95;
    struct HPat_HPat_Ty_IntIntTuple2Tuple4* payload_174 = (struct HPat_HPat_Ty_IntIntTuple2Tuple4*)malloc(sizeof(struct HPat_HPat_Ty_IntIntTuple2Tuple4));
    (*(((struct HPat_HPat_Ty_IntIntTuple2Tuple4*)payload_174))) = tuple_512;
    struct HPat_ variant_174 = (struct HPat_){.tag = Or_3, .Or_3 = payload_174};
    struct HPat_NameCtx_Tuple2 tuple_511;
    tuple_511.t0 = variant_174;
    tuple_511.t1 = nameCtx_22;
    match_251 = tuple_511;
    goto end_match_992;
next_1004:;
    if ((pat_26.tag != Fun_2)) goto next_1005;
    struct IntIntTuple2 loc_96 = (*(pat_26.Fun_2)).t2;
    struct IntIntTuple2HPat_NameCtx_Tuple2Fun1 call_722 = failwithf_1((struct String){.str = "Invalid occurrence of fun pattern: %A", .len = 37});
    struct HPat_NameCtx_Tuple2 app_64 = call_722.fun(call_722.env, loc_96);
    match_251 = app_64;
    goto end_match_992;
next_1005:;
    exit(1);
end_match_992:;
    return match_251;
}

struct HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2 onArm_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, struct AArm_NameCtx_Tuple2 arg_169) {
    struct APat_ pat_32 = (*(arg_169.t0.AArm_)).t0;
    struct AExpr_ guard_4 = (*(arg_169.t0.AArm_)).t1;
    struct AExpr_ body_18 = (*(arg_169.t0.AArm_)).t2;
    struct IntIntTuple2 loc_104 = (*(arg_169.t0.AArm_)).t3;
    struct NameCtx_ nameCtx_25 = arg_169.t1;
    struct APat_NameCtx_Tuple2 tuple_513;
    tuple_513.t0 = pat_32;
    tuple_513.t1 = nameCtx_25;
    struct HPat_NameCtx_Tuple2 call_723 = onPat_(noTy_, tuple_513);
    struct HPat_ pat_33 = call_723.t0;
    struct NameCtx_ nameCtx_26 = call_723.t1;
    struct HExpr_NameCtx_Tuple2 match_252;
    if ((guard_4.tag != Missing_2)) goto next_1007;
    struct HExpr_ call_724 = hxTrue_(litTrue_, loc_104);
    struct HExpr_NameCtx_Tuple2 tuple_514;
    tuple_514.t0 = call_724;
    tuple_514.t1 = nameCtx_26;
    match_252 = tuple_514;
    goto end_match_1006;
next_1007:;
    struct AExpr_NameCtx_Tuple2 tuple_515;
    tuple_515.t0 = guard_4;
    tuple_515.t1 = nameCtx_26;
    struct HExpr_NameCtx_Tuple2 call_725 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_515);
    match_252 = call_725;
    goto end_match_1006;
next_1008:;
end_match_1006:;
    struct HExpr_ guard_5 = match_252.t0;
    struct NameCtx_ nameCtx_27 = match_252.t1;
    struct AExpr_NameCtx_Tuple2 tuple_516;
    tuple_516.t0 = body_18;
    tuple_516.t1 = nameCtx_27;
    struct HExpr_NameCtx_Tuple2 call_726 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_516);
    struct HExpr_ body_19 = call_726.t0;
    struct NameCtx_ nameCtx_28 = call_726.t1;
    struct HPat_HExpr_HExpr_Tuple3 tuple_518;
    tuple_518.t0 = pat_33;
    tuple_518.t1 = guard_5;
    tuple_518.t2 = body_19;
    struct HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2 tuple_517;
    tuple_517.t0 = tuple_518;
    tuple_517.t1 = nameCtx_28;
    return tuple_517;
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

struct HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2 fun_11(void* env_9, struct AArm_NameCtx_Tuple2 arg_32) {
    struct Lit_ arg_33 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_9))).t0;
    struct Lit_ arg_34 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_9))).t1;
    struct Ty_ arg_35 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_9))).t2;
    struct Ty_ arg_36 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_9))).t3;
    struct Ty_ arg_37 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_9))).t4;
    struct Ty_ arg_38 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_9))).t5;
    struct Ty_ arg_39 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_9))).t6;
    struct Ty_ arg_40 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_9))).t7;
    struct HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2 call_727 = onArm_(arg_33, arg_34, arg_35, arg_36, arg_37, arg_38, arg_39, arg_40, arg_32);
    return call_727;
}

struct HExpr_NameCtx_Tuple2 fun_12(void* env_10, struct AExpr_NameCtx_Tuple2 arg_41) {
    struct Lit_ arg_42 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_10))).t0;
    struct Lit_ arg_43 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_10))).t1;
    struct Ty_ arg_44 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_10))).t2;
    struct Ty_ arg_45 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_10))).t3;
    struct Ty_ arg_46 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_10))).t4;
    struct Ty_ arg_47 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_10))).t5;
    struct Ty_ arg_48 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_10))).t6;
    struct Ty_ arg_49 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_10))).t7;
    struct HExpr_NameCtx_Tuple2 call_728 = onExpr_(arg_42, arg_43, arg_44, arg_45, arg_46, arg_47, arg_48, arg_49, arg_41);
    return call_728;
}

struct HExpr_NameCtx_Tuple2 fun_13(void* env_11, struct AExpr_NameCtx_Tuple2 arg_50) {
    struct Lit_ arg_51 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_11))).t0;
    struct Lit_ arg_52 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_11))).t1;
    struct Ty_ arg_53 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_11))).t2;
    struct Ty_ arg_54 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_11))).t3;
    struct Ty_ arg_55 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_11))).t4;
    struct Ty_ arg_56 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_11))).t5;
    struct Ty_ arg_57 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_11))).t6;
    struct Ty_ arg_58 = (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)env_11))).t7;
    struct HExpr_NameCtx_Tuple2 call_729 = onExpr_(arg_51, arg_52, arg_53, arg_54, arg_55, arg_56, arg_57, arg_58, arg_50);
    return call_729;
}

struct HPat_NameCtx_Tuple2 fun_14(void* env_12, struct APat_NameCtx_Tuple2 arg_59) {
    struct Ty_ arg_60 = (*(((struct Ty_Tuple1*)env_12))).t0;
    struct HPat_NameCtx_Tuple2 call_730 = onPat_(arg_60, arg_59);
    return call_730;
}

struct HExpr_NameCtx_Tuple2 onExpr_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, struct AExpr_NameCtx_Tuple2 arg_170) {
    struct AExpr_ expr_18 = arg_170.t0;
    struct NameCtx_ nameCtx_23 = arg_170.t1;
    struct HExpr_NameCtx_Tuple2 match_253;
    if ((expr_18.tag != Missing_2)) goto next_1010;
    struct IntIntTuple2 loc_97 = (*(expr_18.Missing_2));
    struct StringIntIntTuple2Tuple2 tuple_520;
    tuple_520.t0 = (struct String){.str = "Missing expression", .len = 18};
    tuple_520.t1 = loc_97;
    struct StringIntIntTuple2Tuple2* payload_175 = (struct StringIntIntTuple2Tuple2*)malloc(sizeof(struct StringIntIntTuple2Tuple2));
    (*(((struct StringIntIntTuple2Tuple2*)payload_175))) = tuple_520;
    struct HExpr_ variant_175 = (struct HExpr_){.tag = Error_2, .Error_2 = payload_175};
    struct HExpr_NameCtx_Tuple2 tuple_519;
    tuple_519.t0 = variant_175;
    tuple_519.t1 = nameCtx_23;
    match_253 = tuple_519;
    goto end_match_1009;
next_1010:;
    if ((expr_18.tag != Lit_1)) goto next_1011;
    struct Lit_ lit_9 = (*(expr_18.Lit_1)).t0;
    struct IntIntTuple2 loc_98 = (*(expr_18.Lit_1)).t1;
    struct Lit_IntIntTuple2Tuple2 tuple_522;
    tuple_522.t0 = lit_9;
    tuple_522.t1 = loc_98;
    struct Lit_IntIntTuple2Tuple2* payload_176 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_176))) = tuple_522;
    struct HExpr_ variant_176 = (struct HExpr_){.tag = Lit_3, .Lit_3 = payload_176};
    struct HExpr_NameCtx_Tuple2 tuple_521;
    tuple_521.t0 = variant_176;
    tuple_521.t1 = nameCtx_23;
    match_253 = tuple_521;
    goto end_match_1009;
next_1011:;
    if ((expr_18.tag != Ident_3)) goto next_1012;
    struct String ident_31 = (*(expr_18.Ident_3)).t0;
    struct IntIntTuple2 loc_99 = (*(expr_18.Ident_3)).t1;
    struct IntNameCtx_Tuple2 call_731 = nameCtxAdd_1(ident_31, nameCtx_23);
    int serial_10 = call_731.t0;
    struct NameCtx_ nameCtx_24 = call_731.t1;
    struct IntTy_IntIntTuple2Tuple3 tuple_524;
    tuple_524.t0 = serial_10;
    tuple_524.t1 = noTy_;
    tuple_524.t2 = loc_99;
    struct IntTy_IntIntTuple2Tuple3* payload_177 = (struct IntTy_IntIntTuple2Tuple3*)malloc(sizeof(struct IntTy_IntIntTuple2Tuple3));
    (*(((struct IntTy_IntIntTuple2Tuple3*)payload_177))) = tuple_524;
    struct HExpr_ variant_177 = (struct HExpr_){.tag = Ref_2, .Ref_2 = payload_177};
    struct HExpr_NameCtx_Tuple2 tuple_523;
    tuple_523.t0 = variant_177;
    tuple_523.t1 = nameCtx_24;
    match_253 = tuple_523;
    goto end_match_1009;
next_1012:;
    if ((expr_18.tag != ListLit_1)) goto next_1013;
    if ((!((!((*(expr_18.ListLit_1)).t0))))) goto next_1013;
    struct IntIntTuple2 loc_100 = (*(expr_18.ListLit_1)).t1;
    struct HExpr_ call_732 = hxNil_(noTy_, loc_100);
    struct HExpr_NameCtx_Tuple2 tuple_525;
    tuple_525.t0 = call_732;
    tuple_525.t1 = nameCtx_23;
    match_253 = tuple_525;
    goto end_match_1009;
next_1013:;
    if ((expr_18.tag != ListLit_1)) goto next_1014;
    struct AExpr_List* items_10 = (*(expr_18.ListLit_1)).t0;
    struct IntIntTuple2 loc_101 = (*(expr_18.ListLit_1)).t1;
    struct AExpr_ call_733 = desugarListLitExpr_(items_10, loc_101);
    struct AExpr_ expr_19 = call_733;
    struct AExpr_NameCtx_Tuple2 tuple_526;
    tuple_526.t0 = expr_19;
    tuple_526.t1 = nameCtx_23;
    struct HExpr_NameCtx_Tuple2 call_734 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_526);
    match_253 = call_734;
    goto end_match_1009;
next_1014:;
    if ((expr_18.tag != If_1)) goto next_1015;
    struct AExpr_ cond_3 = (*(expr_18.If_1)).t0;
    struct AExpr_ body_17 = (*(expr_18.If_1)).t1;
    struct AExpr_ alt_4 = (*(expr_18.If_1)).t2;
    struct IntIntTuple2 loc_102 = (*(expr_18.If_1)).t3;
    struct AExpr_ call_735 = desugarIf_(litFalse_, litTrue_, cond_3, body_17, alt_4, loc_102);
    struct AExpr_ expr_20 = call_735;
    struct AExpr_NameCtx_Tuple2 tuple_527;
    tuple_527.t0 = expr_20;
    tuple_527.t1 = nameCtx_23;
    struct HExpr_NameCtx_Tuple2 call_736 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_527);
    match_253 = call_736;
    goto end_match_1009;
next_1015:;
    if ((expr_18.tag != Match_1)) goto next_1016;
    struct AExpr_ target_3 = (*(expr_18.Match_1)).t0;
    struct AArm_List* arms_5 = (*(expr_18.Match_1)).t1;
    struct IntIntTuple2 loc_103 = (*(expr_18.Match_1)).t2;
    struct AExpr_NameCtx_Tuple2 tuple_528;
    tuple_528.t0 = target_3;
    tuple_528.t1 = nameCtx_23;
    struct HExpr_NameCtx_Tuple2 call_737 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_528);
    struct HExpr_ target_4 = call_737.t0;
    struct NameCtx_ nameCtx_29 = call_737.t1;
    struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8 tuple_529;
    tuple_529.t0 = litFalse_;
    tuple_529.t1 = litTrue_;
    tuple_529.t2 = tyUnit_;
    tuple_529.t3 = tyStr_;
    tuple_529.t4 = tyChar_;
    tuple_529.t5 = tyInt_;
    tuple_529.t6 = tyBool_;
    tuple_529.t7 = noTy_;
    void* box_9 = (void*)malloc(sizeof(struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8));
    (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)box_9))) = tuple_529;
    void* env_38 = box_9;
    struct AArm_NameCtx_Tuple2HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2Fun1 fun_40 = (struct AArm_NameCtx_Tuple2HPat_HExpr_HExpr_Tuple3NameCtx_Tuple2Fun1){.fun = fun_11, .env = env_38};
    struct AArm_ListNameCtx_Tuple2 tuple_530;
    tuple_530.t0 = arms_5;
    tuple_530.t1 = nameCtx_29;
    struct HPat_HExpr_HExpr_Tuple3ListNameCtx_Tuple2 call_738 = stMap_3(fun_40, tuple_530);
    struct HPat_HExpr_HExpr_Tuple3List* arms_6 = call_738.t0;
    struct NameCtx_ nameCtx_30 = call_738.t1;
    struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4 tuple_532;
    tuple_532.t0 = target_4;
    tuple_532.t1 = arms_6;
    tuple_532.t2 = noTy_;
    tuple_532.t3 = loc_103;
    struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4* payload_178 = (struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4*)malloc(sizeof(struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4));
    (*(((struct HExpr_HPat_HExpr_HExpr_Tuple3ListTy_IntIntTuple2Tuple4*)payload_178))) = tuple_532;
    struct HExpr_ variant_178 = (struct HExpr_){.tag = Match_2, .Match_2 = payload_178};
    struct HExpr_NameCtx_Tuple2 tuple_531;
    tuple_531.t0 = variant_178;
    tuple_531.t1 = nameCtx_30;
    match_253 = tuple_531;
    goto end_match_1009;
next_1016:;
    if ((expr_18.tag != Fun_3)) goto next_1017;
    struct APat_List* pats_10 = (*(expr_18.Fun_3)).t0;
    struct AExpr_ body_20 = (*(expr_18.Fun_3)).t1;
    struct IntIntTuple2 loc_105 = (*(expr_18.Fun_3)).t2;
    struct AExpr_ call_739 = desugarFun_(pats_10, body_20, loc_105);
    struct AExpr_ expr_21 = call_739;
    struct AExpr_NameCtx_Tuple2 tuple_533;
    tuple_533.t0 = expr_21;
    tuple_533.t1 = nameCtx_23;
    struct HExpr_NameCtx_Tuple2 call_740 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_533);
    match_253 = call_740;
    goto end_match_1009;
next_1017:;
    if ((expr_18.tag != Nav_1)) goto next_1018;
    struct AExpr_ l_29 = (*(expr_18.Nav_1)).t0;
    struct String r_42 = (*(expr_18.Nav_1)).t1;
    struct IntIntTuple2 loc_106 = (*(expr_18.Nav_1)).t2;
    struct AExpr_NameCtx_Tuple2 tuple_534;
    tuple_534.t0 = l_29;
    tuple_534.t1 = nameCtx_23;
    struct HExpr_NameCtx_Tuple2 call_741 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_534);
    struct HExpr_ l_30 = call_741.t0;
    struct NameCtx_ nameCtx_31 = call_741.t1;
    struct HExpr_StringTy_IntIntTuple2Tuple4 tuple_536;
    tuple_536.t0 = l_30;
    tuple_536.t1 = r_42;
    tuple_536.t2 = noTy_;
    tuple_536.t3 = loc_106;
    struct HExpr_StringTy_IntIntTuple2Tuple4* payload_179 = (struct HExpr_StringTy_IntIntTuple2Tuple4*)malloc(sizeof(struct HExpr_StringTy_IntIntTuple2Tuple4));
    (*(((struct HExpr_StringTy_IntIntTuple2Tuple4*)payload_179))) = tuple_536;
    struct HExpr_ variant_179 = (struct HExpr_){.tag = Nav_3, .Nav_3 = payload_179};
    struct HExpr_NameCtx_Tuple2 tuple_535;
    tuple_535.t0 = variant_179;
    tuple_535.t1 = nameCtx_31;
    match_253 = tuple_535;
    goto end_match_1009;
next_1018:;
    if ((expr_18.tag != Index_)) goto next_1019;
    struct AExpr_ l_31 = (*(expr_18.Index_)).t0;
    struct AExpr_ r_43 = (*(expr_18.Index_)).t1;
    struct IntIntTuple2 loc_107 = (*(expr_18.Index_)).t2;
    struct HExpr_NameCtx_Tuple2 match_254;
    struct BoolAExpr_Tuple2 call_742 = tryDesugarIndexRange_(expr_18, loc_107);
    if ((!(call_742.t0))) goto next_1039;
    struct AExpr_ expr_22 = call_742.t1;
    struct AExpr_NameCtx_Tuple2 tuple_537;
    tuple_537.t0 = expr_22;
    tuple_537.t1 = nameCtx_23;
    struct HExpr_NameCtx_Tuple2 call_743 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_537);
    match_254 = call_743;
    goto end_match_1038;
next_1039:;
    if (call_742.t0) goto next_1040;
    struct AExpr_NameCtx_Tuple2 tuple_538;
    tuple_538.t0 = l_31;
    tuple_538.t1 = nameCtx_23;
    struct HExpr_NameCtx_Tuple2 call_744 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_538);
    struct HExpr_ l_32 = call_744.t0;
    struct NameCtx_ nameCtx_32 = call_744.t1;
    struct AExpr_NameCtx_Tuple2 tuple_539;
    tuple_539.t0 = r_43;
    tuple_539.t1 = nameCtx_32;
    struct HExpr_NameCtx_Tuple2 call_745 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_539);
    struct HExpr_ r_44 = call_745.t0;
    struct NameCtx_ nameCtx_33 = call_745.t1;
    struct HPrim_Ty_IntIntTuple2Tuple3 tuple_540;
    tuple_540.t0 = (struct HPrim_){.tag = Index_2};
    tuple_540.t1 = noTy_;
    tuple_540.t2 = loc_107;
    struct HPrim_Ty_IntIntTuple2Tuple3* payload_180 = (struct HPrim_Ty_IntIntTuple2Tuple3*)malloc(sizeof(struct HPrim_Ty_IntIntTuple2Tuple3));
    (*(((struct HPrim_Ty_IntIntTuple2Tuple3*)payload_180))) = tuple_540;
    struct HExpr_ variant_180 = (struct HExpr_){.tag = Prim_, .Prim_ = payload_180};
    struct HExpr_ call_746 = hxApp_(variant_180, l_32, noTy_, loc_107);
    struct HExpr_ call_747 = hxApp_(call_746, r_44, noTy_, loc_107);
    struct HExpr_ hxIndex_ = call_747;
    struct HExpr_NameCtx_Tuple2 tuple_541;
    tuple_541.t0 = hxIndex_;
    tuple_541.t1 = nameCtx_33;
    match_254 = tuple_541;
    goto end_match_1038;
next_1040:;
    exit(1);
end_match_1038:;
    match_253 = match_254;
    goto end_match_1009;
next_1019:;
    if ((expr_18.tag != Uni_)) goto next_1020;
    if (((*(expr_18.Uni_)).t0.tag != Neg_)) goto next_1020;
    struct AExpr_ arg_5 = (*(expr_18.Uni_)).t1;
    struct IntIntTuple2 loc_108 = (*(expr_18.Uni_)).t2;
    struct AExpr_ call_748 = desugarUniNeg_(arg_5, loc_108);
    struct AExpr_ expr_23 = call_748;
    struct AExpr_NameCtx_Tuple2 tuple_542;
    tuple_542.t0 = expr_23;
    tuple_542.t1 = nameCtx_23;
    struct HExpr_NameCtx_Tuple2 call_749 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_542);
    match_253 = call_749;
    goto end_match_1009;
next_1020:;
    if ((expr_18.tag != Bin_)) goto next_1021;
    if (((*(expr_18.Bin_)).t0.tag != Ne_)) goto next_1021;
    struct AExpr_ l_33 = (*(expr_18.Bin_)).t1;
    struct AExpr_ r_45 = (*(expr_18.Bin_)).t2;
    struct IntIntTuple2 loc_109 = (*(expr_18.Bin_)).t3;
    struct AExpr_ call_750 = desugarBinNe_(litFalse_, l_33, r_45, loc_109);
    struct AExpr_ expr_24 = call_750;
    struct AExpr_NameCtx_Tuple2 tuple_543;
    tuple_543.t0 = expr_24;
    tuple_543.t1 = nameCtx_23;
    struct HExpr_NameCtx_Tuple2 call_751 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_543);
    match_253 = call_751;
    goto end_match_1009;
next_1021:;
    if ((expr_18.tag != Bin_)) goto next_1022;
    if (((*(expr_18.Bin_)).t0.tag != Le_)) goto next_1022;
    struct AExpr_ l_34 = (*(expr_18.Bin_)).t1;
    struct AExpr_ r_46 = (*(expr_18.Bin_)).t2;
    struct IntIntTuple2 loc_110 = (*(expr_18.Bin_)).t3;
    struct AExpr_ call_752 = desugarBinLe_(litFalse_, l_34, r_46, loc_110);
    struct AExpr_ expr_25 = call_752;
    struct AExpr_NameCtx_Tuple2 tuple_544;
    tuple_544.t0 = expr_25;
    tuple_544.t1 = nameCtx_23;
    struct HExpr_NameCtx_Tuple2 call_753 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_544);
    match_253 = call_753;
    goto end_match_1009;
next_1022:;
    if ((expr_18.tag != Bin_)) goto next_1023;
    if (((*(expr_18.Bin_)).t0.tag != Gt_1)) goto next_1023;
    struct AExpr_ l_35 = (*(expr_18.Bin_)).t1;
    struct AExpr_ r_47 = (*(expr_18.Bin_)).t2;
    struct IntIntTuple2 loc_111 = (*(expr_18.Bin_)).t3;
    struct AExpr_ call_754 = desugarBinGt_(l_35, r_47, loc_111);
    struct AExpr_ expr_26 = call_754;
    struct AExpr_NameCtx_Tuple2 tuple_545;
    tuple_545.t0 = expr_26;
    tuple_545.t1 = nameCtx_23;
    struct HExpr_NameCtx_Tuple2 call_755 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_545);
    match_253 = call_755;
    goto end_match_1009;
next_1023:;
    if ((expr_18.tag != Bin_)) goto next_1024;
    if (((*(expr_18.Bin_)).t0.tag != Ge_)) goto next_1024;
    struct AExpr_ l_36 = (*(expr_18.Bin_)).t1;
    struct AExpr_ r_48 = (*(expr_18.Bin_)).t2;
    struct IntIntTuple2 loc_112 = (*(expr_18.Bin_)).t3;
    struct AExpr_ call_756 = desugarBinGe_(litFalse_, l_36, r_48, loc_112);
    struct AExpr_ expr_27 = call_756;
    struct AExpr_NameCtx_Tuple2 tuple_546;
    tuple_546.t0 = expr_27;
    tuple_546.t1 = nameCtx_23;
    struct HExpr_NameCtx_Tuple2 call_757 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_546);
    match_253 = call_757;
    goto end_match_1009;
next_1024:;
    if ((expr_18.tag != Bin_)) goto next_1025;
    if (((*(expr_18.Bin_)).t0.tag != And_1)) goto next_1025;
    struct AExpr_ l_37 = (*(expr_18.Bin_)).t1;
    struct AExpr_ r_49 = (*(expr_18.Bin_)).t2;
    struct IntIntTuple2 loc_113 = (*(expr_18.Bin_)).t3;
    struct AExpr_ call_758 = desugarBinAnd_(litFalse_, litTrue_, l_37, r_49, loc_113);
    struct AExpr_ expr_28 = call_758;
    struct AExpr_NameCtx_Tuple2 tuple_547;
    tuple_547.t0 = expr_28;
    tuple_547.t1 = nameCtx_23;
    struct HExpr_NameCtx_Tuple2 call_759 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_547);
    match_253 = call_759;
    goto end_match_1009;
next_1025:;
    if ((expr_18.tag != Bin_)) goto next_1026;
    if (((*(expr_18.Bin_)).t0.tag != Or_1)) goto next_1026;
    struct AExpr_ l_38 = (*(expr_18.Bin_)).t1;
    struct AExpr_ r_50 = (*(expr_18.Bin_)).t2;
    struct IntIntTuple2 loc_114 = (*(expr_18.Bin_)).t3;
    struct AExpr_ call_760 = desugarBinOr_(litFalse_, litTrue_, l_38, r_50, loc_114);
    struct AExpr_ expr_29 = call_760;
    struct AExpr_NameCtx_Tuple2 tuple_548;
    tuple_548.t0 = expr_29;
    tuple_548.t1 = nameCtx_23;
    struct HExpr_NameCtx_Tuple2 call_761 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_548);
    match_253 = call_761;
    goto end_match_1009;
next_1026:;
    if ((expr_18.tag != Bin_)) goto next_1027;
    if (((*(expr_18.Bin_)).t0.tag != Pipe_2)) goto next_1027;
    struct AExpr_ l_39 = (*(expr_18.Bin_)).t1;
    struct AExpr_ r_51 = (*(expr_18.Bin_)).t2;
    struct IntIntTuple2 loc_115 = (*(expr_18.Bin_)).t3;
    struct AExpr_ call_762 = desugarBinPipe_(l_39, r_51, loc_115);
    struct AExpr_ expr_30 = call_762;
    struct AExpr_NameCtx_Tuple2 tuple_549;
    tuple_549.t0 = expr_30;
    tuple_549.t1 = nameCtx_23;
    struct HExpr_NameCtx_Tuple2 call_763 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_549);
    match_253 = call_763;
    goto end_match_1009;
next_1027:;
    if ((expr_18.tag != Bin_)) goto next_1028;
    if (((*(expr_18.Bin_)).t0.tag != App_)) goto next_1028;
    struct AExpr_ l_40 = (*(expr_18.Bin_)).t1;
    struct AExpr_ r_52 = (*(expr_18.Bin_)).t2;
    struct IntIntTuple2 loc_116 = (*(expr_18.Bin_)).t3;
    struct AExpr_NameCtx_Tuple2 tuple_550;
    tuple_550.t0 = l_40;
    tuple_550.t1 = nameCtx_23;
    struct HExpr_NameCtx_Tuple2 call_764 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_550);
    struct HExpr_ l_41 = call_764.t0;
    struct NameCtx_ nameCtx_34 = call_764.t1;
    struct AExpr_NameCtx_Tuple2 tuple_551;
    tuple_551.t0 = r_52;
    tuple_551.t1 = nameCtx_34;
    struct HExpr_NameCtx_Tuple2 call_765 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_551);
    struct HExpr_ r_53 = call_765.t0;
    struct NameCtx_ nameCtx_35 = call_765.t1;
    struct HExpr_ call_766 = hxApp_(l_41, r_53, noTy_, loc_116);
    struct HExpr_NameCtx_Tuple2 tuple_552;
    tuple_552.t0 = call_766;
    tuple_552.t1 = nameCtx_35;
    match_253 = tuple_552;
    goto end_match_1009;
next_1028:;
    if ((expr_18.tag != Bin_)) goto next_1029;
    struct Op_ op_3 = (*(expr_18.Bin_)).t0;
    struct AExpr_ l_42 = (*(expr_18.Bin_)).t1;
    struct AExpr_ r_54 = (*(expr_18.Bin_)).t2;
    struct IntIntTuple2 loc_117 = (*(expr_18.Bin_)).t3;
    struct HPrim_ call_767 = opToPrim_(op_3);
    struct HPrim_ prim_2 = call_767;
    struct AExpr_NameCtx_Tuple2 tuple_553;
    tuple_553.t0 = l_42;
    tuple_553.t1 = nameCtx_23;
    struct HExpr_NameCtx_Tuple2 call_768 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_553);
    struct HExpr_ l_43 = call_768.t0;
    struct NameCtx_ nameCtx_36 = call_768.t1;
    struct AExpr_NameCtx_Tuple2 tuple_554;
    tuple_554.t0 = r_54;
    tuple_554.t1 = nameCtx_36;
    struct HExpr_NameCtx_Tuple2 call_769 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_554);
    struct HExpr_ r_55 = call_769.t0;
    struct NameCtx_ nameCtx_37 = call_769.t1;
    struct HPrim_Ty_IntIntTuple2Tuple3 tuple_555;
    tuple_555.t0 = prim_2;
    tuple_555.t1 = noTy_;
    tuple_555.t2 = loc_117;
    struct HPrim_Ty_IntIntTuple2Tuple3* payload_181 = (struct HPrim_Ty_IntIntTuple2Tuple3*)malloc(sizeof(struct HPrim_Ty_IntIntTuple2Tuple3));
    (*(((struct HPrim_Ty_IntIntTuple2Tuple3*)payload_181))) = tuple_555;
    struct HExpr_ variant_181 = (struct HExpr_){.tag = Prim_, .Prim_ = payload_181};
    struct HExpr_ primExpr_ = variant_181;
    struct HExpr_ call_770 = hxApp_(primExpr_, l_43, noTy_, loc_117);
    struct HExpr_ call_771 = hxApp_(call_770, r_55, noTy_, loc_117);
    struct HExpr_NameCtx_Tuple2 tuple_556;
    tuple_556.t0 = call_771;
    tuple_556.t1 = nameCtx_37;
    match_253 = tuple_556;
    goto end_match_1009;
next_1029:;
    if ((expr_18.tag != Range_)) goto next_1030;
    struct IntIntTuple2 loc_118 = (*(expr_18.Range_)).t1;
    struct StringIntIntTuple2Tuple2 tuple_558;
    tuple_558.t0 = (struct String){.str = "Invalid use of range syntax.", .len = 28};
    tuple_558.t1 = loc_118;
    struct StringIntIntTuple2Tuple2* payload_182 = (struct StringIntIntTuple2Tuple2*)malloc(sizeof(struct StringIntIntTuple2Tuple2));
    (*(((struct StringIntIntTuple2Tuple2*)payload_182))) = tuple_558;
    struct HExpr_ variant_182 = (struct HExpr_){.tag = Error_2, .Error_2 = payload_182};
    struct HExpr_NameCtx_Tuple2 tuple_557;
    tuple_557.t0 = variant_182;
    tuple_557.t1 = nameCtx_23;
    match_253 = tuple_557;
    goto end_match_1009;
next_1030:;
    if ((expr_18.tag != TupleLit_1)) goto next_1031;
    struct AExpr_List* items_11 = (*(expr_18.TupleLit_1)).t0;
    struct IntIntTuple2 loc_119 = (*(expr_18.TupleLit_1)).t1;
    struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8 tuple_559;
    tuple_559.t0 = litFalse_;
    tuple_559.t1 = litTrue_;
    tuple_559.t2 = tyUnit_;
    tuple_559.t3 = tyStr_;
    tuple_559.t4 = tyChar_;
    tuple_559.t5 = tyInt_;
    tuple_559.t6 = tyBool_;
    tuple_559.t7 = noTy_;
    void* box_10 = (void*)malloc(sizeof(struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8));
    (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)box_10))) = tuple_559;
    void* env_39 = box_10;
    struct AExpr_NameCtx_Tuple2HExpr_NameCtx_Tuple2Fun1 fun_41 = (struct AExpr_NameCtx_Tuple2HExpr_NameCtx_Tuple2Fun1){.fun = fun_12, .env = env_39};
    struct AExpr_ListNameCtx_Tuple2 tuple_560;
    tuple_560.t0 = items_11;
    tuple_560.t1 = nameCtx_23;
    struct HExpr_ListNameCtx_Tuple2 call_772 = stMap_2(fun_41, tuple_560);
    struct HExpr_List* items_12 = call_772.t0;
    struct NameCtx_ nameCtx_38 = call_772.t1;
    struct HExpr_ call_773 = hxTuple_(tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, items_12, loc_119);
    struct HExpr_NameCtx_Tuple2 tuple_561;
    tuple_561.t0 = call_773;
    tuple_561.t1 = nameCtx_38;
    match_253 = tuple_561;
    goto end_match_1009;
next_1031:;
    if ((expr_18.tag != Anno_1)) goto next_1032;
    struct AExpr_ body_21 = (*(expr_18.Anno_1)).t0;
    struct ATy_ ty_58 = (*(expr_18.Anno_1)).t1;
    struct IntIntTuple2 loc_120 = (*(expr_18.Anno_1)).t2;
    struct AExpr_NameCtx_Tuple2 tuple_562;
    tuple_562.t0 = body_21;
    tuple_562.t1 = nameCtx_23;
    struct HExpr_NameCtx_Tuple2 call_774 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_562);
    struct HExpr_ body_22 = call_774.t0;
    struct NameCtx_ nameCtx_39 = call_774.t1;
    struct ATy_NameCtx_Tuple2 tuple_563;
    tuple_563.t0 = ty_58;
    tuple_563.t1 = nameCtx_39;
    struct Ty_NameCtx_Tuple2 call_775 = onTy_(tuple_563);
    struct Ty_ ty_59 = call_775.t0;
    struct NameCtx_ nameCtx_40 = call_775.t1;
    struct HExpr_ call_776 = hxAnno_(body_22, ty_59, loc_120);
    struct HExpr_NameCtx_Tuple2 tuple_564;
    tuple_564.t0 = call_776;
    tuple_564.t1 = nameCtx_40;
    match_253 = tuple_564;
    goto end_match_1009;
next_1032:;
    if ((expr_18.tag != Semi_1)) goto next_1033;
    struct AExpr_List* exprs_1 = (*(expr_18.Semi_1)).t0;
    struct IntIntTuple2 loc_121 = (*(expr_18.Semi_1)).t1;
    int call_777 = listIsEmpty_1(exprs_1);
    milone_assert((!(call_777)), 389, 4);
    int call_778 = 0;
    struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8 tuple_565;
    tuple_565.t0 = litFalse_;
    tuple_565.t1 = litTrue_;
    tuple_565.t2 = tyUnit_;
    tuple_565.t3 = tyStr_;
    tuple_565.t4 = tyChar_;
    tuple_565.t5 = tyInt_;
    tuple_565.t6 = tyBool_;
    tuple_565.t7 = noTy_;
    void* box_11 = (void*)malloc(sizeof(struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8));
    (*(((struct Lit_Lit_Ty_Ty_Ty_Ty_Ty_Ty_Tuple8*)box_11))) = tuple_565;
    void* env_40 = box_11;
    struct AExpr_NameCtx_Tuple2HExpr_NameCtx_Tuple2Fun1 fun_42 = (struct AExpr_NameCtx_Tuple2HExpr_NameCtx_Tuple2Fun1){.fun = fun_13, .env = env_40};
    struct AExpr_ListNameCtx_Tuple2 tuple_566;
    tuple_566.t0 = exprs_1;
    tuple_566.t1 = nameCtx_23;
    struct HExpr_ListNameCtx_Tuple2 call_779 = stMap_2(fun_42, tuple_566);
    struct HExpr_List* exprs_2 = call_779.t0;
    struct NameCtx_ nameCtx_41 = call_779.t1;
    struct HExpr_ call_780 = hxSemi_(noTy_, exprs_2, loc_121);
    struct HExpr_NameCtx_Tuple2 tuple_567;
    tuple_567.t0 = call_780;
    tuple_567.t1 = nameCtx_41;
    match_253 = tuple_567;
    goto end_match_1009;
next_1033:;
    if ((expr_18.tag != Let_1)) goto next_1034;
    struct APat_ pat_34 = (*(expr_18.Let_1)).t0;
    struct AExpr_ body_23 = (*(expr_18.Let_1)).t1;
    struct AExpr_ next_12 = (*(expr_18.Let_1)).t2;
    struct IntIntTuple2 loc_122 = (*(expr_18.Let_1)).t3;
    struct HExpr_NameCtx_Tuple2 match_255;
    struct ALet_ call_781 = desugarLet_(pat_34, body_23, next_12, loc_122);
    if ((call_781.tag != LetFun_)) goto next_1042;
    struct String ident_32 = (*(call_781.LetFun_)).t0;
    struct APat_List* args_9 = (*(call_781.LetFun_)).t1;
    struct AExpr_ body_24 = (*(call_781.LetFun_)).t2;
    struct AExpr_ next_13 = (*(call_781.LetFun_)).t3;
    struct IntIntTuple2 loc_123 = (*(call_781.LetFun_)).t4;
    struct IntNameCtx_Tuple2 call_782 = nameCtxAdd_1(ident_32, nameCtx_23);
    int serial_11 = call_782.t0;
    struct NameCtx_ nameCtx_42 = call_782.t1;
    int isMainFun_1 = 0;
    struct Ty_Tuple1 tuple_568;
    tuple_568.t0 = noTy_;
    void* box_12 = (void*)malloc(sizeof(struct Ty_Tuple1));
    (*(((struct Ty_Tuple1*)box_12))) = tuple_568;
    void* env_41 = box_12;
    struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1 fun_43 = (struct APat_NameCtx_Tuple2HPat_NameCtx_Tuple2Fun1){.fun = fun_14, .env = env_41};
    struct APat_ListNameCtx_Tuple2 tuple_569;
    tuple_569.t0 = args_9;
    tuple_569.t1 = nameCtx_42;
    struct HPat_ListNameCtx_Tuple2 call_783 = stMap_1(fun_43, tuple_569);
    struct HPat_List* args_10 = call_783.t0;
    struct NameCtx_ nameCtx_43 = call_783.t1;
    struct AExpr_NameCtx_Tuple2 tuple_570;
    tuple_570.t0 = body_24;
    tuple_570.t1 = nameCtx_43;
    struct HExpr_NameCtx_Tuple2 call_784 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_570);
    struct HExpr_ body_25 = call_784.t0;
    struct NameCtx_ nameCtx_44 = call_784.t1;
    struct AExpr_NameCtx_Tuple2 tuple_571;
    tuple_571.t0 = next_13;
    tuple_571.t1 = nameCtx_44;
    struct HExpr_NameCtx_Tuple2 call_785 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_571);
    struct HExpr_ next_14 = call_785.t0;
    struct NameCtx_ nameCtx_45 = call_785.t1;
    struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7 tuple_573;
    tuple_573.t0 = serial_11;
    tuple_573.t1 = isMainFun_1;
    tuple_573.t2 = args_10;
    tuple_573.t3 = body_25;
    tuple_573.t4 = next_14;
    tuple_573.t5 = noTy_;
    tuple_573.t6 = loc_123;
    struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7* payload_183 = (struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7*)malloc(sizeof(struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7));
    (*(((struct IntBoolHPat_ListHExpr_HExpr_Ty_IntIntTuple2Tuple7*)payload_183))) = tuple_573;
    struct HExpr_ variant_183 = (struct HExpr_){.tag = LetFun_1, .LetFun_1 = payload_183};
    struct HExpr_NameCtx_Tuple2 tuple_572;
    tuple_572.t0 = variant_183;
    tuple_572.t1 = nameCtx_45;
    match_255 = tuple_572;
    goto end_match_1041;
next_1042:;
    if ((call_781.tag != LetVal_)) goto next_1043;
    struct APat_ pat_35 = (*(call_781.LetVal_)).t0;
    struct AExpr_ body_26 = (*(call_781.LetVal_)).t1;
    struct AExpr_ next_15 = (*(call_781.LetVal_)).t2;
    struct IntIntTuple2 loc_124 = (*(call_781.LetVal_)).t3;
    struct APat_NameCtx_Tuple2 tuple_574;
    tuple_574.t0 = pat_35;
    tuple_574.t1 = nameCtx_23;
    struct HPat_NameCtx_Tuple2 call_786 = onPat_(noTy_, tuple_574);
    struct HPat_ pat_36 = call_786.t0;
    struct NameCtx_ nameCtx_46 = call_786.t1;
    struct AExpr_NameCtx_Tuple2 tuple_575;
    tuple_575.t0 = body_26;
    tuple_575.t1 = nameCtx_46;
    struct HExpr_NameCtx_Tuple2 call_787 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_575);
    struct HExpr_ body_27 = call_787.t0;
    struct NameCtx_ nameCtx_47 = call_787.t1;
    struct AExpr_NameCtx_Tuple2 tuple_576;
    tuple_576.t0 = next_15;
    tuple_576.t1 = nameCtx_47;
    struct HExpr_NameCtx_Tuple2 call_788 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_576);
    struct HExpr_ next_16 = call_788.t0;
    struct NameCtx_ nameCtx_48 = call_788.t1;
    struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5 tuple_578;
    tuple_578.t0 = pat_36;
    tuple_578.t1 = body_27;
    tuple_578.t2 = next_16;
    tuple_578.t3 = noTy_;
    tuple_578.t4 = loc_124;
    struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5* payload_184 = (struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5*)malloc(sizeof(struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5));
    (*(((struct HPat_HExpr_HExpr_Ty_IntIntTuple2Tuple5*)payload_184))) = tuple_578;
    struct HExpr_ variant_184 = (struct HExpr_){.tag = Let_2, .Let_2 = payload_184};
    struct HExpr_NameCtx_Tuple2 tuple_577;
    tuple_577.t0 = variant_184;
    tuple_577.t1 = nameCtx_48;
    match_255 = tuple_577;
    goto end_match_1041;
next_1043:;
    exit(1);
end_match_1041:;
    match_253 = match_255;
    goto end_match_1009;
next_1034:;
    if ((expr_18.tag != TySynonym_)) goto next_1035;
    struct String ident_33 = (*(expr_18.TySynonym_)).t0;
    struct ATy_ ty_60 = (*(expr_18.TySynonym_)).t1;
    struct IntIntTuple2 loc_125 = (*(expr_18.TySynonym_)).t2;
    struct IntNameCtx_Tuple2 call_789 = nameCtxAdd_1(ident_33, nameCtx_23);
    int serial_12 = call_789.t0;
    struct NameCtx_ nameCtx_49 = call_789.t1;
    struct ATy_NameCtx_Tuple2 tuple_579;
    tuple_579.t0 = ty_60;
    tuple_579.t1 = nameCtx_49;
    struct Ty_NameCtx_Tuple2 call_790 = onTy_(tuple_579);
    struct Ty_ ty_61 = call_790.t0;
    struct NameCtx_ nameCtx_50 = call_790.t1;
    struct Ty_IntIntTuple2Tuple2 tuple_582;
    tuple_582.t0 = ty_61;
    tuple_582.t1 = loc_125;
    struct Ty_IntIntTuple2Tuple2* payload_185 = (struct Ty_IntIntTuple2Tuple2*)malloc(sizeof(struct Ty_IntIntTuple2Tuple2));
    (*(((struct Ty_IntIntTuple2Tuple2*)payload_185))) = tuple_582;
    struct TyDecl_ variant_185 = (struct TyDecl_){.tag = Synonym_1, .Synonym_1 = payload_185};
    struct IntTyDecl_IntIntTuple2Tuple3 tuple_581;
    tuple_581.t0 = serial_12;
    tuple_581.t1 = variant_185;
    tuple_581.t2 = loc_125;
    struct IntTyDecl_IntIntTuple2Tuple3* payload_186 = (struct IntTyDecl_IntIntTuple2Tuple3*)malloc(sizeof(struct IntTyDecl_IntIntTuple2Tuple3));
    (*(((struct IntTyDecl_IntIntTuple2Tuple3*)payload_186))) = tuple_581;
    struct HExpr_ variant_186 = (struct HExpr_){.tag = TyDecl_, .TyDecl_ = payload_186};
    struct HExpr_NameCtx_Tuple2 tuple_580;
    tuple_580.t0 = variant_186;
    tuple_580.t1 = nameCtx_50;
    match_253 = tuple_580;
    goto end_match_1009;
next_1035:;
    if ((expr_18.tag != TyUnion_)) goto next_1036;
    struct String ident_34 = (*(expr_18.TyUnion_)).t0;
    struct AVariant_List* variants_3 = (*(expr_18.TyUnion_)).t1;
    struct IntIntTuple2 loc_126 = (*(expr_18.TyUnion_)).t2;
    struct StringIntIntTuple2Tuple2 tuple_584;
    tuple_584.t0 = (struct String){.str = "", .len = 0};
    tuple_584.t1 = loc_126;
    struct StringIntIntTuple2Tuple2* payload_187 = (struct StringIntIntTuple2Tuple2*)malloc(sizeof(struct StringIntIntTuple2Tuple2));
    (*(((struct StringIntIntTuple2Tuple2*)payload_187))) = tuple_584;
    struct HExpr_ variant_187 = (struct HExpr_){.tag = Error_2, .Error_2 = payload_187};
    struct HExpr_NameCtx_Tuple2 tuple_583;
    tuple_583.t0 = variant_187;
    tuple_583.t1 = nameCtx_23;
    match_253 = tuple_583;
    goto end_match_1009;
next_1036:;
    if ((expr_18.tag != Open_1)) goto next_1037;
    struct StringList* path_3 = (*(expr_18.Open_1)).t0;
    struct IntIntTuple2 loc_127 = (*(expr_18.Open_1)).t1;
    struct StringListIntIntTuple2Tuple2 tuple_586;
    tuple_586.t0 = path_3;
    tuple_586.t1 = loc_127;
    struct StringListIntIntTuple2Tuple2* payload_188 = (struct StringListIntIntTuple2Tuple2*)malloc(sizeof(struct StringListIntIntTuple2Tuple2));
    (*(((struct StringListIntIntTuple2Tuple2*)payload_188))) = tuple_586;
    struct HExpr_ variant_188 = (struct HExpr_){.tag = Open_2, .Open_2 = payload_188};
    struct HExpr_NameCtx_Tuple2 tuple_585;
    tuple_585.t0 = variant_188;
    tuple_585.t1 = nameCtx_23;
    match_253 = tuple_585;
    goto end_match_1009;
next_1037:;
    exit(1);
end_match_1009:;
    return match_253;
}

struct HExpr_NameCtx_Tuple2 astToHir_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, struct AExpr_NameCtx_Tuple2 arg_171) {
    struct AExpr_ expr_31 = arg_171.t0;
    struct NameCtx_ nameCtx_51 = arg_171.t1;
    struct AExpr_NameCtx_Tuple2 tuple_587;
    tuple_587.t0 = expr_31;
    tuple_587.t1 = nameCtx_51;
    struct HExpr_NameCtx_Tuple2 call_791 = onExpr_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_587);
    return call_791;
}

struct String litToString_(struct Lit_ lit_5) {
    struct String match_256;
    if ((lit_5.tag != Bool_)) goto next_1045;
    if ((!((*(lit_5.Bool_))))) goto next_1045;
    match_256 = (struct String){.str = "true", .len = 4};
    goto end_match_1044;
next_1045:;
    if ((lit_5.tag != Bool_)) goto next_1046;
    if ((*(lit_5.Bool_))) goto next_1046;
    match_256 = (struct String){.str = "false", .len = 5};
    goto end_match_1044;
next_1046:;
    if ((lit_5.tag != Int_)) goto next_1047;
    int value_4 = (*(lit_5.Int_));
    struct String call_792 = str_of_int(value_4);
    match_256 = call_792;
    goto end_match_1044;
next_1047:;
    if ((lit_5.tag != Char_)) goto next_1048;
    char value_5 = (*(lit_5.Char_));
    int call_793 = ((int)value_5);
    struct String call_794 = str_of_int(call_793);
    match_256 = str_add((struct String){.str = "char ", .len = 5}, call_794);
    goto end_match_1044;
next_1048:;
    if ((lit_5.tag != Str_)) goto next_1049;
    match_256 = (struct String){.str = "\"...\"", .len = 5};
    goto end_match_1044;
next_1049:;
    exit(1);
end_match_1044:;
    return match_256;
}

struct String tokenToString_(struct Token_ token_12) {
    struct String match_257;
    if ((token_12.tag != Error_)) goto next_1051;
    match_257 = (struct String){.str = "Error", .len = 5};
    goto end_match_1050;
next_1051:;
    if ((token_12.tag != Bool_1)) goto next_1052;
    if ((*(token_12.Bool_1))) goto next_1052;
    match_257 = (struct String){.str = "false", .len = 5};
    goto end_match_1050;
next_1052:;
    if ((token_12.tag != Bool_1)) goto next_1053;
    if ((!((*(token_12.Bool_1))))) goto next_1053;
    match_257 = (struct String){.str = "true", .len = 4};
    goto end_match_1050;
next_1053:;
    if ((token_12.tag != Int_1)) goto next_1054;
    int value_6 = (*(token_12.Int_1));
    struct String call_795 = str_of_int(value_6);
    match_257 = call_795;
    goto end_match_1050;
next_1054:;
    if ((token_12.tag != Char_1)) goto next_1055;
    match_257 = (struct String){.str = "'?'", .len = 3};
    goto end_match_1050;
next_1055:;
    if ((token_12.tag != Str_1)) goto next_1056;
    match_257 = (struct String){.str = "\"?\"", .len = 3};
    goto end_match_1050;
next_1056:;
    if ((token_12.tag != Ident_)) goto next_1057;
    struct String ident_8 = (*(token_12.Ident_));
    match_257 = str_add(str_add((struct String){.str = "\"", .len = 1}, ident_8), (struct String){.str = "\"", .len = 1});
    goto end_match_1050;
next_1057:;
    if ((token_12.tag != ParenL_)) goto next_1058;
    match_257 = (struct String){.str = "(", .len = 1};
    goto end_match_1050;
next_1058:;
    if ((token_12.tag != ParenR_)) goto next_1059;
    match_257 = (struct String){.str = ")", .len = 1};
    goto end_match_1050;
next_1059:;
    if ((token_12.tag != BracketL_)) goto next_1060;
    match_257 = (struct String){.str = "[", .len = 1};
    goto end_match_1050;
next_1060:;
    if ((token_12.tag != BracketR_)) goto next_1061;
    match_257 = (struct String){.str = "]", .len = 1};
    goto end_match_1050;
next_1061:;
    if ((token_12.tag != Amp_)) goto next_1062;
    match_257 = (struct String){.str = "&", .len = 1};
    goto end_match_1050;
next_1062:;
    if ((token_12.tag != AmpAmp_)) goto next_1063;
    match_257 = (struct String){.str = "&&", .len = 2};
    goto end_match_1050;
next_1063:;
    if ((token_12.tag != Arrow_)) goto next_1064;
    match_257 = (struct String){.str = "->", .len = 2};
    goto end_match_1050;
next_1064:;
    if ((token_12.tag != Colon_)) goto next_1065;
    match_257 = (struct String){.str = ":", .len = 1};
    goto end_match_1050;
next_1065:;
    if ((token_12.tag != ColonColon_)) goto next_1066;
    match_257 = (struct String){.str = "::", .len = 2};
    goto end_match_1050;
next_1066:;
    if ((token_12.tag != Comma_)) goto next_1067;
    match_257 = (struct String){.str = ",", .len = 1};
    goto end_match_1050;
next_1067:;
    if ((token_12.tag != Dot_)) goto next_1068;
    match_257 = (struct String){.str = ".", .len = 1};
    goto end_match_1050;
next_1068:;
    if ((token_12.tag != DotDot_)) goto next_1069;
    match_257 = (struct String){.str = "..", .len = 2};
    goto end_match_1050;
next_1069:;
    if ((token_12.tag != Eq_)) goto next_1070;
    match_257 = (struct String){.str = "=", .len = 1};
    goto end_match_1050;
next_1070:;
    if ((token_12.tag != Gt_)) goto next_1071;
    match_257 = (struct String){.str = ">", .len = 1};
    goto end_match_1050;
next_1071:;
    if ((token_12.tag != GtEq_)) goto next_1072;
    match_257 = (struct String){.str = ">=", .len = 2};
    goto end_match_1050;
next_1072:;
    if ((token_12.tag != Lt_)) goto next_1073;
    match_257 = (struct String){.str = "<", .len = 1};
    goto end_match_1050;
next_1073:;
    if ((token_12.tag != LtEq_)) goto next_1074;
    match_257 = (struct String){.str = "<=", .len = 2};
    goto end_match_1050;
next_1074:;
    if ((token_12.tag != LtGt_)) goto next_1075;
    match_257 = (struct String){.str = "<>", .len = 2};
    goto end_match_1050;
next_1075:;
    if ((token_12.tag != Minus_)) goto next_1076;
    match_257 = (struct String){.str = "-", .len = 1};
    goto end_match_1050;
next_1076:;
    if ((token_12.tag != Percent_)) goto next_1077;
    match_257 = (struct String){.str = "%", .len = 1};
    goto end_match_1050;
next_1077:;
    if ((token_12.tag != Pipe_)) goto next_1078;
    match_257 = (struct String){.str = "|", .len = 1};
    goto end_match_1050;
next_1078:;
    if ((token_12.tag != PipeGt_)) goto next_1079;
    match_257 = (struct String){.str = "|>", .len = 2};
    goto end_match_1050;
next_1079:;
    if ((token_12.tag != PipePipe_)) goto next_1080;
    match_257 = (struct String){.str = "||", .len = 2};
    goto end_match_1050;
next_1080:;
    if ((token_12.tag != Plus_)) goto next_1081;
    match_257 = (struct String){.str = "+", .len = 1};
    goto end_match_1050;
next_1081:;
    if ((token_12.tag != Semi_)) goto next_1082;
    match_257 = (struct String){.str = ";", .len = 1};
    goto end_match_1050;
next_1082:;
    if ((token_12.tag != Star_)) goto next_1083;
    match_257 = (struct String){.str = "*", .len = 1};
    goto end_match_1050;
next_1083:;
    if ((token_12.tag != Slash_)) goto next_1084;
    match_257 = (struct String){.str = "/", .len = 1};
    goto end_match_1050;
next_1084:;
    if ((token_12.tag != As_)) goto next_1085;
    match_257 = (struct String){.str = "as", .len = 2};
    goto end_match_1050;
next_1085:;
    if ((token_12.tag != Do_)) goto next_1086;
    match_257 = (struct String){.str = "do", .len = 2};
    goto end_match_1050;
next_1086:;
    if ((token_12.tag != Else_)) goto next_1087;
    match_257 = (struct String){.str = "else", .len = 4};
    goto end_match_1050;
next_1087:;
    if ((token_12.tag != Fun_)) goto next_1088;
    match_257 = (struct String){.str = "fun", .len = 3};
    goto end_match_1050;
next_1088:;
    if ((token_12.tag != If_)) goto next_1089;
    match_257 = (struct String){.str = "if", .len = 2};
    goto end_match_1050;
next_1089:;
    if ((token_12.tag != In_)) goto next_1090;
    match_257 = (struct String){.str = "in", .len = 2};
    goto end_match_1050;
next_1090:;
    if ((token_12.tag != Internal_)) goto next_1091;
    match_257 = (struct String){.str = "internal", .len = 8};
    goto end_match_1050;
next_1091:;
    if ((token_12.tag != Let_)) goto next_1092;
    match_257 = (struct String){.str = "let", .len = 3};
    goto end_match_1050;
next_1092:;
    if ((token_12.tag != Match_)) goto next_1093;
    match_257 = (struct String){.str = "match", .len = 5};
    goto end_match_1050;
next_1093:;
    if ((token_12.tag != Module_)) goto next_1094;
    match_257 = (struct String){.str = "module", .len = 6};
    goto end_match_1050;
next_1094:;
    if ((token_12.tag != Namespace_)) goto next_1095;
    match_257 = (struct String){.str = "namespace", .len = 9};
    goto end_match_1050;
next_1095:;
    if ((token_12.tag != Of_)) goto next_1096;
    match_257 = (struct String){.str = "of", .len = 2};
    goto end_match_1050;
next_1096:;
    if ((token_12.tag != Open_)) goto next_1097;
    match_257 = (struct String){.str = "open", .len = 4};
    goto end_match_1050;
next_1097:;
    if ((token_12.tag != Private_)) goto next_1098;
    match_257 = (struct String){.str = "private", .len = 7};
    goto end_match_1050;
next_1098:;
    if ((token_12.tag != Public_)) goto next_1099;
    match_257 = (struct String){.str = "public", .len = 6};
    goto end_match_1050;
next_1099:;
    if ((token_12.tag != Rec_)) goto next_1100;
    match_257 = (struct String){.str = "rec", .len = 3};
    goto end_match_1050;
next_1100:;
    if ((token_12.tag != Then_)) goto next_1101;
    match_257 = (struct String){.str = "then", .len = 4};
    goto end_match_1050;
next_1101:;
    if ((token_12.tag != Type_)) goto next_1102;
    match_257 = (struct String){.str = "type", .len = 4};
    goto end_match_1050;
next_1102:;
    if ((token_12.tag != When_)) goto next_1103;
    match_257 = (struct String){.str = "when", .len = 4};
    goto end_match_1050;
next_1103:;
    if ((token_12.tag != With_)) goto next_1104;
    match_257 = (struct String){.str = "with", .len = 4};
    goto end_match_1050;
next_1104:;
end_match_1050:;
    return match_257;
}

struct DumpTree_ fun_15(void* env_13, struct ATy_ arg_61) {
    struct DumpTree_ call_796 = atDump_(arg_61);
    return call_796;
}

struct DumpTree_ fun_16(void* env_14, struct ATy_ arg_62) {
    struct DumpTree_ call_797 = atDump_(arg_62);
    return call_797;
}

struct DumpTree_ atDump_(struct ATy_ ty_43) {
    struct DumpTree_ match_258;
    if ((ty_43.tag != Missing_)) goto next_1106;
    struct IntIntTuple2 loc_23 = (*(ty_43.Missing_));
    struct DumpTree_ call_798 = dumpTreeFromError_((struct String){.str = "missing", .len = 7}, loc_23);
    match_258 = call_798;
    goto end_match_1105;
next_1106:;
    if ((ty_43.tag != Ident_1)) goto next_1107;
    struct String ident_9 = (*(ty_43.Ident_1)).t0;
    struct DumpTree_ call_799 = dumpTreeNewLeaf_(ident_9);
    match_258 = call_799;
    goto end_match_1105;
next_1107:;
    if ((ty_43.tag != Suffix_)) goto next_1108;
    struct ATy_ lTy_2 = (*(ty_43.Suffix_)).t0;
    struct String ident_10 = (*(ty_43.Suffix_)).t1;
    struct DumpTree_ call_800 = atDump_(lTy_2);
    struct DumpTree_List* list_79 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_79->head = call_800;
    list_79->tail = NULL;
    struct DumpTree_ call_801 = dumpTreeNew_(ident_10, list_79);
    match_258 = call_801;
    goto end_match_1105;
next_1108:;
    if ((ty_43.tag != Tuple_)) goto next_1109;
    struct ATy_List* itemTys_ = (*(ty_43.Tuple_)).t0;
    void* box_13 = (void*)malloc(sizeof(int));
    (*(((int*)box_13))) = 0;
    void* env_42 = box_13;
    struct ATy_DumpTree_Fun1 fun_44 = (struct ATy_DumpTree_Fun1){.fun = fun_15, .env = env_42};
    struct DumpTree_List* call_802 = listMap_6(fun_44, itemTys_);
    struct DumpTree_ call_803 = dumpTreeNew_((struct String){.str = "tuple", .len = 5}, call_802);
    match_258 = call_803;
    goto end_match_1105;
next_1109:;
    if ((ty_43.tag != Fun_1)) goto next_1110;
    struct ATy_ sTy_ = (*(ty_43.Fun_1)).t0;
    struct ATy_ tTy_ = (*(ty_43.Fun_1)).t1;
    void* box_14 = (void*)malloc(sizeof(int));
    (*(((int*)box_14))) = 0;
    void* env_43 = box_14;
    struct ATy_DumpTree_Fun1 fun_45 = (struct ATy_DumpTree_Fun1){.fun = fun_16, .env = env_43};
    struct ATy_List* list_81 = (struct ATy_List*)malloc(sizeof(struct ATy_List));
    list_81->head = tTy_;
    list_81->tail = NULL;
    struct ATy_List* list_80 = (struct ATy_List*)malloc(sizeof(struct ATy_List));
    list_80->head = sTy_;
    list_80->tail = list_81;
    struct DumpTree_List* call_804 = listMap_6(fun_45, list_80);
    struct DumpTree_ call_805 = dumpTreeNew_((struct String){.str = "fun", .len = 3}, call_804);
    match_258 = call_805;
    goto end_match_1105;
next_1110:;
    exit(1);
end_match_1105:;
    return match_258;
}

struct DumpTree_ fun_17(void* env_15, struct APat_ arg_63) {
    struct DumpTree_ call_806 = apDump_(arg_63);
    return call_806;
}

struct DumpTree_ fun_18(void* env_16, struct APat_ arg_64) {
    struct DumpTree_ call_807 = apDump_(arg_64);
    return call_807;
}

struct DumpTree_ fun_19(void* env_17, struct APat_ arg_65) {
    struct DumpTree_ call_808 = apDump_(arg_65);
    return call_808;
}

struct DumpTree_ fun_20(void* env_18, struct APat_ arg_66) {
    struct DumpTree_ call_809 = apDump_(arg_66);
    return call_809;
}

struct DumpTree_ apDump_(struct APat_ pat_10) {
    struct DumpTree_ match_259;
    if ((pat_10.tag != Missing_1)) goto next_1112;
    struct IntIntTuple2 loc_24 = (*(pat_10.Missing_1));
    struct DumpTree_ call_810 = dumpTreeFromError_((struct String){.str = "missing", .len = 7}, loc_24);
    match_259 = call_810;
    goto end_match_1111;
next_1112:;
    if ((pat_10.tag != Lit_)) goto next_1113;
    struct Lit_ lit_6 = (*(pat_10.Lit_)).t0;
    struct String call_811 = litToString_(lit_6);
    struct DumpTree_ call_812 = dumpTreeNewLeaf_(call_811);
    match_259 = call_812;
    goto end_match_1111;
next_1113:;
    if ((pat_10.tag != Ident_2)) goto next_1114;
    struct String ident_11 = (*(pat_10.Ident_2)).t0;
    struct DumpTree_ call_813 = dumpTreeNewLeaf_(ident_11);
    match_259 = call_813;
    goto end_match_1111;
next_1114:;
    if ((pat_10.tag != ListLit_)) goto next_1115;
    struct APat_List* pats_ = (*(pat_10.ListLit_)).t0;
    void* box_15 = (void*)malloc(sizeof(int));
    (*(((int*)box_15))) = 0;
    void* env_44 = box_15;
    struct APat_DumpTree_Fun1 fun_46 = (struct APat_DumpTree_Fun1){.fun = fun_17, .env = env_44};
    struct DumpTree_List* call_814 = listMap_4(fun_46, pats_);
    struct DumpTree_ call_815 = dumpTreeNew_((struct String){.str = "list", .len = 4}, call_814);
    match_259 = call_815;
    goto end_match_1111;
next_1115:;
    if ((pat_10.tag != Nav_)) goto next_1116;
    struct APat_ l_10 = (*(pat_10.Nav_)).t0;
    struct String r_23 = (*(pat_10.Nav_)).t1;
    struct IntIntTuple2 loc_25 = (*(pat_10.Nav_)).t2;
    struct DumpTree_ call_816 = apDump_(l_10);
    struct DumpTree_List* list_82 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_82->head = call_816;
    list_82->tail = NULL;
    struct DumpTree_ call_817 = dumpTreeNew_(str_add((struct String){.str = ".", .len = 1}, r_23), list_82);
    match_259 = call_817;
    goto end_match_1111;
next_1116:;
    if ((pat_10.tag != Call_)) goto next_1117;
    struct APat_ calleePat_ = (*(pat_10.Call_)).t0;
    struct APat_List* argPats_ = (*(pat_10.Call_)).t1;
    struct DumpTree_ call_818 = apDump_(calleePat_);
    void* box_16 = (void*)malloc(sizeof(int));
    (*(((int*)box_16))) = 0;
    void* env_45 = box_16;
    struct APat_DumpTree_Fun1 fun_47 = (struct APat_DumpTree_Fun1){.fun = fun_18, .env = env_45};
    struct DumpTree_List* call_819 = listMap_4(fun_47, argPats_);
    struct DumpTree_List* list_83 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_83->head = call_818;
    list_83->tail = call_819;
    struct DumpTree_ call_820 = dumpTreeNew_((struct String){.str = "call", .len = 4}, list_83);
    match_259 = call_820;
    goto end_match_1111;
next_1117:;
    if ((pat_10.tag != Cons_2)) goto next_1118;
    struct APat_ head_1 = (*(pat_10.Cons_2)).t0;
    struct APat_ tail_1 = (*(pat_10.Cons_2)).t1;
    struct DumpTree_ call_821 = apDump_(tail_1);
    struct DumpTree_ call_822 = apDump_(head_1);
    struct DumpTree_List* list_84 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_84->head = call_822;
    list_84->tail = NULL;
    struct DumpTree_ call_823 = dumpTreeNew_((struct String){.str = "cons", .len = 4}, list_84);
    struct DumpTree_ call_824 = dumpTreeAttachNext_(call_821, call_823);
    match_259 = call_824;
    goto end_match_1111;
next_1118:;
    if ((pat_10.tag != TupleLit_)) goto next_1119;
    struct APat_List* pats_1 = (*(pat_10.TupleLit_)).t0;
    void* box_17 = (void*)malloc(sizeof(int));
    (*(((int*)box_17))) = 0;
    void* env_46 = box_17;
    struct APat_DumpTree_Fun1 fun_48 = (struct APat_DumpTree_Fun1){.fun = fun_19, .env = env_46};
    struct DumpTree_List* call_825 = listMap_4(fun_48, pats_1);
    struct DumpTree_ call_826 = dumpTreeNew_((struct String){.str = "tuple", .len = 5}, call_825);
    match_259 = call_826;
    goto end_match_1111;
next_1119:;
    if ((pat_10.tag != As_1)) goto next_1120;
    struct APat_ pat_11 = (*(pat_10.As_1)).t0;
    struct String ident_12 = (*(pat_10.As_1)).t1;
    struct DumpTree_ call_827 = apDump_(pat_11);
    struct DumpTree_List* list_85 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_85->head = call_827;
    list_85->tail = NULL;
    struct DumpTree_ call_828 = dumpTreeNew_(str_add((struct String){.str = "as ", .len = 3}, ident_12), list_85);
    match_259 = call_828;
    goto end_match_1111;
next_1120:;
    if ((pat_10.tag != Anno_)) goto next_1121;
    struct APat_ pat_12 = (*(pat_10.Anno_)).t0;
    struct ATy_ ty_44 = (*(pat_10.Anno_)).t1;
    struct DumpTree_ call_829 = apDump_(pat_12);
    struct DumpTree_ call_830 = atDump_(ty_44);
    struct DumpTree_List* list_87 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_87->head = call_830;
    list_87->tail = NULL;
    struct DumpTree_List* list_86 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_86->head = call_829;
    list_86->tail = list_87;
    struct DumpTree_ call_831 = dumpTreeNew_((struct String){.str = "anno", .len = 4}, list_86);
    match_259 = call_831;
    goto end_match_1111;
next_1121:;
    if ((pat_10.tag != Or_2)) goto next_1122;
    struct APat_ l_11 = (*(pat_10.Or_2)).t0;
    struct APat_ r_24 = (*(pat_10.Or_2)).t1;
    struct DumpTree_ call_832 = apDump_(r_24);
    struct DumpTree_ call_833 = apDump_(l_11);
    struct DumpTree_List* list_88 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_88->head = call_833;
    list_88->tail = NULL;
    struct DumpTree_ call_834 = dumpTreeNew_((struct String){.str = "or", .len = 2}, list_88);
    struct DumpTree_ call_835 = dumpTreeAttachNext_(call_832, call_834);
    match_259 = call_835;
    goto end_match_1111;
next_1122:;
    if ((pat_10.tag != Fun_2)) goto next_1123;
    struct String callee_3 = (*(pat_10.Fun_2)).t0;
    struct APat_List* args_5 = (*(pat_10.Fun_2)).t1;
    struct IntIntTuple2 loc_26 = (*(pat_10.Fun_2)).t2;
    struct DumpTree_ call_836 = dumpTreeNewLeaf_(callee_3);
    void* box_18 = (void*)malloc(sizeof(int));
    (*(((int*)box_18))) = 0;
    void* env_47 = box_18;
    struct APat_DumpTree_Fun1 fun_49 = (struct APat_DumpTree_Fun1){.fun = fun_20, .env = env_47};
    struct DumpTree_List* call_837 = listMap_4(fun_49, args_5);
    struct DumpTree_List* list_89 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_89->head = call_836;
    list_89->tail = call_837;
    struct DumpTree_ call_838 = dumpTreeNew_((struct String){.str = "fun", .len = 3}, list_89);
    match_259 = call_838;
    goto end_match_1111;
next_1123:;
    exit(1);
end_match_1111:;
    return match_259;
}

struct DumpTree_ fun_21(void* env_19, struct AExpr_ arg_67) {
    struct DumpTree_ call_839 = axDump_(arg_67);
    return call_839;
}

struct DumpTree_ dumpArm_(struct AArm_ arg_172) {
    struct APat_ pat_13 = (*(arg_172.AArm_)).t0;
    struct AExpr_ guard_1 = (*(arg_172.AArm_)).t1;
    struct AExpr_ body_3 = (*(arg_172.AArm_)).t2;
    struct DumpTree_ call_840 = axDump_(body_3);
    struct DumpTree_ call_841 = apDump_(pat_13);
    struct DumpTree_ call_842 = axDump_(guard_1);
    struct DumpTree_List* list_91 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_91->head = call_842;
    list_91->tail = NULL;
    struct DumpTree_List* list_90 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_90->head = call_841;
    list_90->tail = list_91;
    struct DumpTree_ call_843 = dumpTreeNew_((struct String){.str = "arm", .len = 3}, list_90);
    struct DumpTree_ call_844 = dumpTreeAttachNext_(call_840, call_843);
    return call_844;
}

struct DumpTree_ fun_22(void* env_20, struct AArm_ arg_68) {
    struct DumpTree_ call_845 = dumpArm_(arg_68);
    return call_845;
}

struct DumpTree_ fun_23(void* env_21, struct APat_ arg_69) {
    struct DumpTree_ call_846 = apDump_(arg_69);
    return call_846;
}

struct DumpTree_ fun_24(void* env_22, struct AExpr_ arg_70) {
    struct DumpTree_ call_847 = axDump_(arg_70);
    return call_847;
}

struct DumpTree_ fun_25(void* env_23, struct AExpr_ arg_71) {
    struct DumpTree_ call_848 = axDump_(arg_71);
    return call_848;
}

struct DumpTree_ fun_26(void* env_24, struct AExpr_ arg_72) {
    struct DumpTree_ call_849 = axDump_(arg_72);
    return call_849;
}

struct DumpTree_ dumpVariant_(struct AVariant_ arg_173) {
    struct String ident_16 = (*(arg_173.AVariant_)).t0;
    struct DumpTree_ call_850 = dumpTreeNewLeaf_(ident_16);
    return call_850;
}

struct DumpTree_ fun_27(void* env_25, struct AVariant_ arg_73) {
    struct DumpTree_ call_851 = dumpVariant_(arg_73);
    return call_851;
}

struct DumpTree_ fun_28(void* env_26, struct String arg_74) {
    struct DumpTree_ call_852 = dumpTreeNewLeaf_(arg_74);
    return call_852;
}

struct DumpTree_ axDump_(struct AExpr_ expr_7) {
    struct DumpTree_ match_260;
    if ((expr_7.tag != Missing_2)) goto next_1125;
    struct IntIntTuple2 loc_27 = (*(expr_7.Missing_2));
    struct DumpTree_ call_853 = dumpTreeFromError_((struct String){.str = "missing", .len = 7}, loc_27);
    match_260 = call_853;
    goto end_match_1124;
next_1125:;
    if ((expr_7.tag != Lit_1)) goto next_1126;
    struct Lit_ lit_7 = (*(expr_7.Lit_1)).t0;
    struct String call_854 = litToString_(lit_7);
    struct DumpTree_ call_855 = dumpTreeNewLeaf_(call_854);
    match_260 = call_855;
    goto end_match_1124;
next_1126:;
    if ((expr_7.tag != Ident_3)) goto next_1127;
    struct String ident_13 = (*(expr_7.Ident_3)).t0;
    struct DumpTree_ call_856 = dumpTreeNewLeaf_(ident_13);
    match_260 = call_856;
    goto end_match_1124;
next_1127:;
    if ((expr_7.tag != ListLit_1)) goto next_1128;
    struct AExpr_List* items_2 = (*(expr_7.ListLit_1)).t0;
    void* box_19 = (void*)malloc(sizeof(int));
    (*(((int*)box_19))) = 0;
    void* env_48 = box_19;
    struct AExpr_DumpTree_Fun1 fun_50 = (struct AExpr_DumpTree_Fun1){.fun = fun_21, .env = env_48};
    struct DumpTree_List* call_857 = listMap_3(fun_50, items_2);
    struct DumpTree_ call_858 = dumpTreeNew_((struct String){.str = "list", .len = 4}, call_857);
    match_260 = call_858;
    goto end_match_1124;
next_1128:;
    if ((expr_7.tag != If_1)) goto next_1129;
    struct AExpr_ cond_ = (*(expr_7.If_1)).t0;
    struct AExpr_ body_2 = (*(expr_7.If_1)).t1;
    struct AExpr_ alt_ = (*(expr_7.If_1)).t2;
    struct DumpTree_ call_859 = axDump_(cond_);
    struct DumpTree_ call_860 = axDump_(body_2);
    struct DumpTree_ call_861 = axDump_(alt_);
    struct DumpTree_List* list_94 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_94->head = call_861;
    list_94->tail = NULL;
    struct DumpTree_List* list_93 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_93->head = call_860;
    list_93->tail = list_94;
    struct DumpTree_List* list_92 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_92->head = call_859;
    list_92->tail = list_93;
    struct DumpTree_ call_862 = dumpTreeNew_((struct String){.str = "if", .len = 2}, list_92);
    match_260 = call_862;
    goto end_match_1124;
next_1129:;
    if ((expr_7.tag != Match_1)) goto next_1130;
    struct AExpr_ target_1 = (*(expr_7.Match_1)).t0;
    struct AArm_List* arms_2 = (*(expr_7.Match_1)).t1;
    struct DumpTree_ call_863 = axDump_(target_1);
    void* box_20 = (void*)malloc(sizeof(int));
    (*(((int*)box_20))) = 0;
    void* env_49 = box_20;
    struct AArm_DumpTree_Fun1 fun_51 = (struct AArm_DumpTree_Fun1){.fun = fun_22, .env = env_49};
    struct DumpTree_List* call_864 = listMap_5(fun_51, arms_2);
    struct DumpTree_List* list_95 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_95->head = call_863;
    list_95->tail = call_864;
    struct DumpTree_ call_865 = dumpTreeNew_((struct String){.str = "match", .len = 5}, list_95);
    match_260 = call_865;
    goto end_match_1124;
next_1130:;
    if ((expr_7.tag != Fun_3)) goto next_1131;
    struct APat_List* pats_2 = (*(expr_7.Fun_3)).t0;
    struct AExpr_ body_4 = (*(expr_7.Fun_3)).t1;
    struct DumpTree_ call_866 = axDump_(body_4);
    void* box_21 = (void*)malloc(sizeof(int));
    (*(((int*)box_21))) = 0;
    void* env_50 = box_21;
    struct APat_DumpTree_Fun1 fun_52 = (struct APat_DumpTree_Fun1){.fun = fun_23, .env = env_50};
    struct DumpTree_List* call_867 = listMap_4(fun_52, pats_2);
    struct DumpTree_ call_868 = dumpTreeNew_((struct String){.str = "fun", .len = 3}, call_867);
    struct DumpTree_ call_869 = dumpTreeAttachNext_(call_866, call_868);
    match_260 = call_869;
    goto end_match_1124;
next_1131:;
    if ((expr_7.tag != Nav_1)) goto next_1132;
    struct AExpr_ l_12 = (*(expr_7.Nav_1)).t0;
    struct String r_25 = (*(expr_7.Nav_1)).t1;
    struct DumpTree_ call_870 = axDump_(l_12);
    struct DumpTree_List* list_96 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_96->head = call_870;
    list_96->tail = NULL;
    struct DumpTree_ call_871 = dumpTreeNew_(str_add((struct String){.str = ".", .len = 1}, r_25), list_96);
    match_260 = call_871;
    goto end_match_1124;
next_1132:;
    if ((expr_7.tag != Index_)) goto next_1133;
    struct AExpr_ l_13 = (*(expr_7.Index_)).t0;
    struct AExpr_ r_26 = (*(expr_7.Index_)).t1;
    struct DumpTree_ call_872 = axDump_(l_13);
    struct DumpTree_List* list_97 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_97->head = call_872;
    list_97->tail = NULL;
    struct DumpTree_ call_873 = dumpTreeNew_((struct String){.str = "index", .len = 5}, list_97);
    match_260 = call_873;
    goto end_match_1124;
next_1133:;
    if ((expr_7.tag != Uni_)) goto next_1134;
    if (((*(expr_7.Uni_)).t0.tag != Neg_)) goto next_1134;
    struct AExpr_ arg_1 = (*(expr_7.Uni_)).t1;
    struct DumpTree_ call_874 = axDump_(arg_1);
    struct DumpTree_List* list_98 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_98->head = call_874;
    list_98->tail = NULL;
    struct DumpTree_ call_875 = dumpTreeNew_((struct String){.str = "-", .len = 1}, list_98);
    match_260 = call_875;
    goto end_match_1124;
next_1134:;
    if ((expr_7.tag != Bin_)) goto next_1135;
    struct AExpr_ l_14 = (*(expr_7.Bin_)).t1;
    struct AExpr_ r_27 = (*(expr_7.Bin_)).t2;
    struct DumpTree_ call_876 = axDump_(l_14);
    struct DumpTree_ call_877 = axDump_(r_27);
    struct DumpTree_List* list_100 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_100->head = call_877;
    list_100->tail = NULL;
    struct DumpTree_List* list_99 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_99->head = call_876;
    list_99->tail = list_100;
    struct DumpTree_ call_878 = dumpTreeNew_((struct String){.str = "bin", .len = 3}, list_99);
    match_260 = call_878;
    goto end_match_1124;
next_1135:;
    if ((expr_7.tag != Range_)) goto next_1136;
    struct AExpr_List* items_3 = (*(expr_7.Range_)).t0;
    void* box_22 = (void*)malloc(sizeof(int));
    (*(((int*)box_22))) = 0;
    void* env_51 = box_22;
    struct AExpr_DumpTree_Fun1 fun_53 = (struct AExpr_DumpTree_Fun1){.fun = fun_24, .env = env_51};
    struct DumpTree_List* call_879 = listMap_3(fun_53, items_3);
    struct DumpTree_ call_880 = dumpTreeNew_((struct String){.str = "range", .len = 5}, call_879);
    match_260 = call_880;
    goto end_match_1124;
next_1136:;
    if ((expr_7.tag != TupleLit_1)) goto next_1137;
    struct AExpr_List* items_4 = (*(expr_7.TupleLit_1)).t0;
    void* box_23 = (void*)malloc(sizeof(int));
    (*(((int*)box_23))) = 0;
    void* env_52 = box_23;
    struct AExpr_DumpTree_Fun1 fun_54 = (struct AExpr_DumpTree_Fun1){.fun = fun_25, .env = env_52};
    struct DumpTree_List* call_881 = listMap_3(fun_54, items_4);
    struct DumpTree_ call_882 = dumpTreeNew_((struct String){.str = "tuple", .len = 5}, call_881);
    match_260 = call_882;
    goto end_match_1124;
next_1137:;
    if ((expr_7.tag != Anno_1)) goto next_1138;
    struct AExpr_ body_5 = (*(expr_7.Anno_1)).t0;
    struct ATy_ ty_45 = (*(expr_7.Anno_1)).t1;
    struct DumpTree_ call_883 = axDump_(body_5);
    struct DumpTree_ call_884 = atDump_(ty_45);
    struct DumpTree_List* list_102 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_102->head = call_884;
    list_102->tail = NULL;
    struct DumpTree_List* list_101 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_101->head = call_883;
    list_101->tail = list_102;
    struct DumpTree_ call_885 = dumpTreeNew_((struct String){.str = "anno", .len = 4}, list_101);
    match_260 = call_885;
    goto end_match_1124;
next_1138:;
    if ((expr_7.tag != Semi_1)) goto next_1139;
    struct AExpr_List* exprs_ = (*(expr_7.Semi_1)).t0;
    void* box_24 = (void*)malloc(sizeof(int));
    (*(((int*)box_24))) = 0;
    void* env_53 = box_24;
    struct AExpr_DumpTree_Fun1 fun_55 = (struct AExpr_DumpTree_Fun1){.fun = fun_26, .env = env_53};
    struct DumpTree_List* call_886 = listMap_3(fun_55, exprs_);
    struct DumpTree_ call_887 = dumpTreeNew_((struct String){.str = "semi", .len = 4}, call_886);
    match_260 = call_887;
    goto end_match_1124;
next_1139:;
    if ((expr_7.tag != Let_1)) goto next_1140;
    struct APat_ pat_14 = (*(expr_7.Let_1)).t0;
    struct AExpr_ body_6 = (*(expr_7.Let_1)).t1;
    struct AExpr_ next_8 = (*(expr_7.Let_1)).t2;
    struct DumpTree_ call_888 = axDump_(next_8);
    struct DumpTree_ call_889 = apDump_(pat_14);
    struct DumpTree_ call_890 = axDump_(body_6);
    struct DumpTree_List* list_104 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_104->head = call_890;
    list_104->tail = NULL;
    struct DumpTree_List* list_103 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_103->head = call_889;
    list_103->tail = list_104;
    struct DumpTree_ call_891 = dumpTreeNew_((struct String){.str = "let", .len = 3}, list_103);
    struct DumpTree_ call_892 = dumpTreeAttachNext_(call_888, call_891);
    match_260 = call_892;
    goto end_match_1124;
next_1140:;
    if ((expr_7.tag != TySynonym_)) goto next_1141;
    struct String ident_14 = (*(expr_7.TySynonym_)).t0;
    struct ATy_ ty_46 = (*(expr_7.TySynonym_)).t1;
    struct DumpTree_ call_893 = atDump_(ty_46);
    struct DumpTree_ call_894 = dumpTreeNewLeaf_(ident_14);
    struct DumpTree_List* list_105 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_105->head = call_894;
    list_105->tail = NULL;
    struct DumpTree_ call_895 = dumpTreeNew_((struct String){.str = "synonym", .len = 7}, list_105);
    struct DumpTree_ call_896 = dumpTreeAttachNext_(call_893, call_895);
    match_260 = call_896;
    goto end_match_1124;
next_1141:;
    if ((expr_7.tag != TyUnion_)) goto next_1142;
    struct String ident_15 = (*(expr_7.TyUnion_)).t0;
    struct AVariant_List* variants_ = (*(expr_7.TyUnion_)).t1;
    struct DumpTree_ call_897 = dumpTreeNewLeaf_(ident_15);
    void* box_25 = (void*)malloc(sizeof(int));
    (*(((int*)box_25))) = 0;
    void* env_54 = box_25;
    struct AVariant_DumpTree_Fun1 fun_56 = (struct AVariant_DumpTree_Fun1){.fun = fun_27, .env = env_54};
    struct DumpTree_List* call_898 = listMap_2(fun_56, variants_);
    struct DumpTree_List* list_106 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_106->head = call_897;
    list_106->tail = call_898;
    struct DumpTree_ call_899 = dumpTreeNew_((struct String){.str = "union", .len = 5}, list_106);
    match_260 = call_899;
    goto end_match_1124;
next_1142:;
    if ((expr_7.tag != Open_1)) goto next_1143;
    struct StringList* path_1 = (*(expr_7.Open_1)).t0;
    void* box_26 = (void*)malloc(sizeof(int));
    (*(((int*)box_26))) = 0;
    void* env_55 = box_26;
    struct StringDumpTree_Fun1 fun_57 = (struct StringDumpTree_Fun1){.fun = fun_28, .env = env_55};
    struct DumpTree_List* call_900 = listMap_1(fun_57, path_1);
    struct DumpTree_ call_901 = dumpTreeNew_((struct String){.str = "open", .len = 4}, call_900);
    match_260 = call_901;
    goto end_match_1124;
next_1143:;
    exit(1);
end_match_1124:;
    return match_260;
}

int fun_1(struct StringIntIntTuple2Tuple2 arg_174) {
    struct String msg_1 = arg_174.t0;
    int y_11 = arg_174.t1.t0;
    int x_20 = arg_174.t1.t1;
    printf("ERROR %s (%d:%d)\n", msg_1.str, (y_11 + 1), (x_20 + 1));
    int call_902 = 0;
    return 0;
}

int fun_29(void* env_27, struct StringIntIntTuple2Tuple2 arg_75) {
    int call_903 = fun_1(arg_75);
    return 0;
}

struct StringStringFun1 {
    struct String(*fun)(void*, struct String);
    void* env;
};

int doFile_(struct StringStringFun1 fileReadAllText_1, struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, struct String filePath_) {
    printf("FILE %s\n", filePath_.str);
    int call_904 = 0;
    struct String app_65 = fileReadAllText_1.fun(fileReadAllText_1.env, filePath_);
    struct String source_ = app_65;
    struct Token_IntIntTuple2Tuple2List* call_905 = tokenize_(source_);
    struct Token_IntIntTuple2Tuple2List* tokens_ = call_905;
    struct AExpr_StringIntIntTuple2Tuple2ListTuple2 call_906 = parse_(tokens_);
    struct AExpr_ ast_ = call_906.t0;
    struct StringIntIntTuple2Tuple2List* errors_ = call_906.t1;
    printf("AST:\n");
    int call_907 = 0;
    void* box_27 = (void*)malloc(sizeof(int));
    (*(((int*)box_27))) = 0;
    void* env_56 = box_27;
    struct StringIntIntTuple2Tuple2UnitFun1 fun_58 = (struct StringIntIntTuple2Tuple2UnitFun1){.fun = fun_29, .env = env_56};
    int call_908 = listIter_1(fun_58, errors_);
    struct NameCtx_ call_909 = nameCtxEmpty_(0);
    struct NameCtx_ nameCtx_ = call_909;
    struct AExpr_NameCtx_Tuple2 tuple_588;
    tuple_588.t0 = ast_;
    tuple_588.t1 = nameCtx_;
    struct HExpr_NameCtx_Tuple2 call_910 = astToHir_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, tuple_588);
    struct NameCtx_ nameCtx_1 = call_910.t1;
    printf("HIR:\n");
    int call_911 = 0;
    return 0;
}

int doSelf_(struct Lit_ litFalse_, struct Lit_ litTrue_, struct Ty_ tyUnit_, struct Ty_ tyStr_, struct Ty_ tyChar_, struct Ty_ tyInt_, struct Ty_ tyBool_, struct Ty_ noTy_, struct StringStringFun1 fileReadAllText_1) {
    int call_912 = doFile_(fileReadAllText_1, litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, (struct String){.str = "MiloneLang/Lexing.fs", .len = 20});
    int call_913 = doFile_(fileReadAllText_1, litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, (struct String){.str = "MiloneLang/Parsing.fs", .len = 21});
    return 0;
}

struct String fileReadAllText_(struct String fileName_) {
    struct String call_914 = file_read_all_text(fileName_);
    return call_914;
}

struct String fun_30(void* env_28, struct String arg_76) {
    struct String call_915 = fileReadAllText_(arg_76);
    return call_915;
}

int main() {
    struct IntIntTuple2 tuple_589;
    tuple_589.t0 = (0 - 1);
    tuple_589.t1 = (0 - 1);
    struct IntIntTuple2 noLoc_ = tuple_589;
    struct IntIntTuple2* payload_189 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_189))) = noLoc_;
    struct Ty_ variant_189 = (struct Ty_){.tag = Error_1, .Error_1 = payload_189};
    struct Ty_ noTy_ = variant_189;
    struct TyCon_Ty_ListTuple2 tuple_590;
    tuple_590.t0 = (struct TyCon_){.tag = Bool_2};
    tuple_590.t1 = NULL;
    struct TyCon_Ty_ListTuple2* payload_190 = (struct TyCon_Ty_ListTuple2*)malloc(sizeof(struct TyCon_Ty_ListTuple2));
    (*(((struct TyCon_Ty_ListTuple2*)payload_190))) = tuple_590;
    struct Ty_ variant_190 = (struct Ty_){.tag = Con_, .Con_ = payload_190};
    struct Ty_ tyBool_ = variant_190;
    struct TyCon_Ty_ListTuple2 tuple_591;
    tuple_591.t0 = (struct TyCon_){.tag = Int_2};
    tuple_591.t1 = NULL;
    struct TyCon_Ty_ListTuple2* payload_191 = (struct TyCon_Ty_ListTuple2*)malloc(sizeof(struct TyCon_Ty_ListTuple2));
    (*(((struct TyCon_Ty_ListTuple2*)payload_191))) = tuple_591;
    struct Ty_ variant_191 = (struct Ty_){.tag = Con_, .Con_ = payload_191};
    struct Ty_ tyInt_ = variant_191;
    struct TyCon_Ty_ListTuple2 tuple_592;
    tuple_592.t0 = (struct TyCon_){.tag = Char_2};
    tuple_592.t1 = NULL;
    struct TyCon_Ty_ListTuple2* payload_192 = (struct TyCon_Ty_ListTuple2*)malloc(sizeof(struct TyCon_Ty_ListTuple2));
    (*(((struct TyCon_Ty_ListTuple2*)payload_192))) = tuple_592;
    struct Ty_ variant_192 = (struct Ty_){.tag = Con_, .Con_ = payload_192};
    struct Ty_ tyChar_ = variant_192;
    struct TyCon_Ty_ListTuple2 tuple_593;
    tuple_593.t0 = (struct TyCon_){.tag = Str_2};
    tuple_593.t1 = NULL;
    struct TyCon_Ty_ListTuple2* payload_193 = (struct TyCon_Ty_ListTuple2*)malloc(sizeof(struct TyCon_Ty_ListTuple2));
    (*(((struct TyCon_Ty_ListTuple2*)payload_193))) = tuple_593;
    struct Ty_ variant_193 = (struct Ty_){.tag = Con_, .Con_ = payload_193};
    struct Ty_ tyStr_ = variant_193;
    struct TyCon_Ty_ListTuple2 tuple_594;
    tuple_594.t0 = (struct TyCon_){.tag = Obj_};
    tuple_594.t1 = NULL;
    struct TyCon_Ty_ListTuple2* payload_194 = (struct TyCon_Ty_ListTuple2*)malloc(sizeof(struct TyCon_Ty_ListTuple2));
    (*(((struct TyCon_Ty_ListTuple2*)payload_194))) = tuple_594;
    struct Ty_ variant_194 = (struct Ty_){.tag = Con_, .Con_ = payload_194};
    struct Ty_ tyObj_ = variant_194;
    struct Ty_ call_916 = tyTuple_(NULL);
    struct Ty_ tyUnit_ = call_916;
    int* payload_195 = (int*)malloc(sizeof(int));
    (*(((int*)payload_195))) = 1;
    struct Lit_ variant_195 = (struct Lit_){.tag = Bool_, .Bool_ = payload_195};
    struct Lit_ litTrue_ = variant_195;
    int* payload_196 = (int*)malloc(sizeof(int));
    (*(((int*)payload_196))) = 0;
    struct Lit_ variant_196 = (struct Lit_){.tag = Bool_, .Bool_ = payload_196};
    struct Lit_ litFalse_ = variant_196;
    char call_917 = ((char)0);
    char charNull_ = call_917;
    void* box_28 = (void*)malloc(sizeof(int));
    (*(((int*)box_28))) = 0;
    void* env_57 = box_28;
    struct StringStringFun1 fun_59 = (struct StringStringFun1){.fun = fun_30, .env = env_57};
    int call_918 = doSelf_(litFalse_, litTrue_, tyUnit_, tyStr_, tyChar_, tyInt_, tyBool_, noTy_, fun_59);
    return call_918;
}
