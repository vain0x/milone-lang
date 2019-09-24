#include "milone.h"

struct String failwith_3(struct String str_);

struct StringList;

struct StringList* failwith_2(struct String str_);

enum Token_Tag;

struct Token_;

struct Token_ failwith_1(struct String str_);

struct StringList* cons_1(struct String head_, struct StringList* tail_);

int listIsEmpty_2(struct StringList* xs_);

enum DumpTree_Tag;

struct DumpTree_;

struct StringDumpTree_ListDumpTree_ListTuple3;

struct DumpTree_List;

int listIsEmpty_1(struct DumpTree_List* xs_);

struct IntIntTuple2;

struct Token_IntIntTuple2Tuple2;

struct Token_IntIntTuple2Tuple2List;

struct Token_IntIntTuple2Tuple2List* go_44(struct Token_IntIntTuple2Tuple2List* acc_5, struct Token_IntIntTuple2Tuple2List* xs_2);

enum ATy_Tag;

struct ATy_;

struct StringIntIntTuple2Tuple2;

struct ATy_StringIntIntTuple2Tuple3;

struct ATy_ListIntIntTuple2Tuple2;

struct ATy_ATy_IntIntTuple2Tuple3;

struct ATy_List;

struct ATy_List* go_43(struct ATy_List* acc_5, struct ATy_List* xs_2);

enum AVariant_Tag;

struct AVariant_;

struct StringATy_ListIntIntTuple2Tuple3;

struct AVariant_List;

struct AVariant_List* go_42(struct AVariant_List* acc_5, struct AVariant_List* xs_2);

enum APat_Tag;

struct APat_;

enum Lit_Tag;

struct Lit_;

struct Lit_IntIntTuple2Tuple2;

struct APat_ListIntIntTuple2Tuple2;

struct APat_StringIntIntTuple2Tuple3;

struct APat_APat_ListIntIntTuple2Tuple3;

struct APat_APat_IntIntTuple2Tuple3;

struct APat_ATy_IntIntTuple2Tuple3;

struct StringAPat_ListIntIntTuple2Tuple3;

struct APat_List;

struct APat_List* go_41(struct APat_List* acc_5, struct APat_List* xs_2);

enum AArm_Tag;

struct AArm_;

enum AExpr_Tag;

struct AExpr_;

struct AExpr_List;

struct AExpr_ListIntIntTuple2Tuple2;

struct AExpr_AExpr_AExpr_IntIntTuple2Tuple4;

struct AExpr_AArm_ListIntIntTuple2Tuple3;

struct APat_ListAExpr_IntIntTuple2Tuple3;

struct AExpr_StringIntIntTuple2Tuple3;

struct AExpr_AExpr_IntIntTuple2Tuple3;

enum UniOp_Tag;

struct UniOp_;

struct UniOp_AExpr_IntIntTuple2Tuple3;

enum Op_Tag;

struct Op_;

struct Op_AExpr_AExpr_IntIntTuple2Tuple4;

struct AExpr_ATy_IntIntTuple2Tuple3;

struct StringATy_IntIntTuple2Tuple3;

struct StringAVariant_ListIntIntTuple2Tuple3;

struct StringListIntIntTuple2Tuple2;

struct APat_AExpr_AExpr_IntIntTuple2Tuple4;

struct AArm_List;

struct AArm_List* go_40(struct AArm_List* acc_5, struct AArm_List* xs_2);

struct StringList* go_39(struct StringList* acc_5, struct StringList* xs_2);

struct AExpr_List* go_38(struct AExpr_List* acc_5, struct AExpr_List* xs_2);

struct DumpTree_List* go_45(struct DumpTree_List* acc_5, struct DumpTree_List* xs_2);

struct Token_IntIntTuple2Tuple2List* listRev_7(struct Token_IntIntTuple2Tuple2List* xs_1);

struct ATy_List* listRev_6(struct ATy_List* xs_1);

struct AVariant_List* listRev_5(struct AVariant_List* xs_1);

struct APat_List* listRev_4(struct APat_List* xs_1);

struct AArm_List* listRev_3(struct AArm_List* xs_1);

struct StringList* listRev_2(struct StringList* xs_1);

struct AExpr_List* listRev_1(struct AExpr_List* xs_1);

struct DumpTree_List* listRev_8(struct DumpTree_List* xs_1);

int go_37(int len_, struct StringList* xs_5);

int listLength_1(struct StringList* xs_4);

struct Token_IntIntTuple2Tuple2UnitFun1;

int listIter_2(struct Token_IntIntTuple2Tuple2UnitFun1 f_, struct Token_IntIntTuple2Tuple2List* xs_7);

struct StringIntIntTuple2Tuple2UnitFun1;

struct StringIntIntTuple2Tuple2List;

int listIter_1(struct StringIntIntTuple2Tuple2UnitFun1 f_, struct StringIntIntTuple2Tuple2List* xs_7);

struct ATy_DumpTree_Fun1;

struct DumpTree_List* go_36(struct ATy_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct ATy_List* xs_10);

struct APat_DumpTree_Fun1;

struct DumpTree_List* go_35(struct APat_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct APat_List* xs_10);

struct AExpr_DumpTree_Fun1;

struct DumpTree_List* go_34(struct AExpr_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct AExpr_List* xs_10);

struct DumpTree_List* listMap_3(struct ATy_DumpTree_Fun1 f_1, struct ATy_List* xs_9);

struct DumpTree_List* listMap_2(struct APat_DumpTree_Fun1 f_1, struct APat_List* xs_9);

struct DumpTree_List* listMap_1(struct AExpr_DumpTree_Fun1 f_1, struct AExpr_List* xs_9);

int intMin_(int x_7, int y_2);

int intMax_(int x_8, int y_3);

int intEq_(int x_9, int y_4);

struct String strSlice_(int start_, int endIndex_1, struct String s_3);

struct StringStringListTuple2;

struct StringStringListTuple2 go_16(struct StringList* xs_16, int xn_);

struct String strConcat_(struct StringList* xs_15);

struct String go_17(struct String acc_7, int len_2, int n_1);

struct String intToHexWithPadding_(int len_1, int value_3);

struct DumpTree_ dumpTreeNew_(struct String text_43, struct DumpTree_List* children_);

struct DumpTree_ dumpTreeNewLeaf_(struct String text_44);

struct DumpTree_ dumpTreeAttachNext_(struct DumpTree_ next_1, struct DumpTree_ tree_);

struct DumpTree_ dumpTreeFromError_(struct String msg_, struct IntIntTuple2 arg_17);

int charIsControl_(char c_8);

int charNeedsEscaping_(char c_9);

int go_18(struct String str_2, int i_50);

int strNeedsEscaping_(struct String str_2);

struct IntStringTuple2;

struct IntStringTuple2 strEscapeCore_(int i_51, struct String str_3);

int raw_(struct String str_4, int i_53);

struct IntStringListTuple2;

struct StringList* go_19(struct String str_4, struct StringList* acc_8, int i_52);

struct String strEscape_(struct String str_4);

struct StringList* goChildren_(struct String eol_1, struct DumpTree_List* children_2, struct StringList* acc_11);

struct StringList* goNext_(struct String eol_2, struct DumpTree_List* next_2, struct StringList* acc_12);

struct StringList* go_20(struct String eol_, struct DumpTree_ node_1, struct StringList* acc_10);

struct String dumpTreeToString_(struct DumpTree_ node_);

int locX_(struct IntIntTuple2 arg_18);

int locY_(struct IntIntTuple2 arg_19);

int locIsSameRow_(struct IntIntTuple2 first_, struct IntIntTuple2 second_);

int locIsSameColumn_(struct IntIntTuple2 first_1, struct IntIntTuple2 second_1);

int locInside_(struct IntIntTuple2 firstLoc_, struct IntIntTuple2 secondLoc_);

struct IntIntTuple2 locAddX_(int dx_, struct IntIntTuple2 arg_20);

struct IntIntTuple2 locMax_(struct IntIntTuple2 arg_21, struct IntIntTuple2 arg_22);

int tokenIsExprOrPatFirst_(struct Token_ token_7);

int tokenIsExprFirst_(struct Token_ token_8);

int tokenIsArgFirst_(struct Token_ token_9);

int tokenIsPatFirst_(struct Token_ token_10);

int tokenIsAccessModifier_(struct Token_ token_11);

enum OpLevel_Tag;

struct OpLevel_;

struct OpLevel_ opLevelToNext_(struct OpLevel_ level_);

struct IntIntTuple2 go_(int r_, struct String text_, int y_1, int x_2, int i_);

struct IntIntTuple2 locShift_(struct String text_, int l_, int r_, struct IntIntTuple2 arg_23);

int charIsSpace_(char c_);

int charIsDigit_(char c_1);

int charIsAlpha_(char c_2);

int charIsIdent_(char c_3);

int charIsOp_(char c_4);

int charIsPun_(char c_5);

int go_1(struct String s_, struct String prefix_, int pi_, int si_);

int strIsFollowedBy_(int i_1, struct String prefix_, struct String s_);

int strIsFollowedByRawQuotes_(int i_2, struct String s_1);

int scanError_(struct String arg_24, int i_3);

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

struct StringIntTuple2 tokCtxToTextIndex_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 arg_25);

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokCtxSkip_(int r_8, struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 arg_26);

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokCtxPush_(struct Token_ kind_, int r_9, struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 arg_27);

struct Token_IntIntTuple2Tuple2List* tokEof_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 arg_28);

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

struct StringIntIntTuple2Tuple2List* parseErrorCore_1(struct String msg_2, struct IntIntTuple2 loc_9, struct Token_IntIntTuple2Tuple2List* tokens_6, struct StringIntIntTuple2Tuple2List* errors_1);

struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2;

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyError_1(struct String msg_3, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_29);

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatError_1(struct String msg_4, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_30);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseExprError_1(struct String msg_5, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_31);

struct StringIntIntTuple2Tuple2List* parseNewError_1(struct String msg_6, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_32);

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyAtom_(struct IntIntTuple2 baseLoc_1, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_33);

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_33(struct IntIntTuple2 baseLoc_2, struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 arg_34);

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTySuffix_(struct IntIntTuple2 baseLoc_2, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_35);

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyPrefix_(struct IntIntTuple2 baseLoc_3, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_36);

struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_22(struct IntIntTuple2 baseLoc_4, struct ATy_List* acc_13, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_37);

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyTuple_(struct IntIntTuple2 baseLoc_4, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_38);

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyFun_(struct IntIntTuple2 baseLoc_5, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_39);

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTy_(struct IntIntTuple2 baseLoc_6, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_40);

struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_23(struct IntIntTuple2 baseLoc_7, struct AVariant_List* acc_14, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_41);

enum ATyDecl_Tag;

struct ATyDecl_;

struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyDeclUnion_(struct IntIntTuple2 baseLoc_7, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_42);

struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyDeclBody_(struct IntIntTuple2 baseLoc_8, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_43);

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatParenBody_(struct IntIntTuple2 baseLoc_9, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_44);

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_24(struct IntIntTuple2 baseLoc_10, struct APat_List* patAcc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_45);

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatListBody_(struct IntIntTuple2 baseLoc_10, struct IntIntTuple2 bracketLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_46);

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatAtom_(struct IntIntTuple2 baseLoc_11, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_47);

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatNav_(struct IntIntTuple2 baseLoc_12, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_48);

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_25(struct IntIntTuple2 argBaseLoc_, struct IntIntTuple2 baseLoc_13, struct APat_List* acc_15, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_49);

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatCallArgs_(struct IntIntTuple2 baseLoc_13, struct IntIntTuple2 calleeLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_50);

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatCall_(struct IntIntTuple2 baseLoc_14, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_51);

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatCons_(struct IntIntTuple2 baseLoc_15, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_52);

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatAnno_(struct IntIntTuple2 baseLoc_16, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_53);

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_26(struct IntIntTuple2 baseLoc_17, struct APat_List* acc_16, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_54);

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatTuple_(struct IntIntTuple2 baseLoc_17, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_55);

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatAs_(struct IntIntTuple2 baseLoc_18, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_56);

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatOr_(struct IntIntTuple2 baseLoc_19, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_57);

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatLet_(struct IntIntTuple2 baseLoc_20, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_58);

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePat_(struct IntIntTuple2 baseLoc_21, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_59);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseRange_(struct IntIntTuple2 baseLoc_22, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_60);

struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseList_(struct IntIntTuple2 baseLoc_23, struct IntIntTuple2 bracketLoc_1, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_61);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseThenClause_(struct IntIntTuple2 baseLoc_24, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_62);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseElseClause_(struct IntIntTuple2 baseLoc_25, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_63);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseIf_(struct IntIntTuple2 ifLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_64);

struct AArm_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct AArm_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseMatchArm_(struct IntIntTuple2 matchLoc_, struct IntIntTuple2 armLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_65);

struct AArm_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct AArm_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_27(struct IntIntTuple2 matchLoc_1, struct AArm_List* acc_17, struct IntIntTuple2 armLoc_2, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_66);

struct IntIntTuple2Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseMatch_(struct IntIntTuple2 matchLoc_1, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_67);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseFun_(struct IntIntTuple2 baseLoc_26, struct IntIntTuple2 funLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_68);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseParenBody_(struct IntIntTuple2 baseLoc_27, struct IntIntTuple2 parenLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_69);

struct Token_IntIntTuple2Tuple2List* parseAccessModifier_1(struct Token_IntIntTuple2Tuple2List* tokens_138);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseLet_(struct IntIntTuple2 letLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_70);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyDecl_(struct IntIntTuple2 typeLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_71);

struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3;

struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_28(struct StringList* acc_18, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_72);

struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePath_(struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_73);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseOpen_(struct IntIntTuple2 openLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_74);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseAtom_(struct IntIntTuple2 baseLoc_29, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_75);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_29(struct IntIntTuple2 baseLoc_30, struct AExpr_ acc_19, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_76);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseSuffix_(struct IntIntTuple2 baseLoc_30, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_77);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_30(struct IntIntTuple2 argBaseLoc_1, struct IntIntTuple2 calleeLoc_3, struct IntIntTuple2 baseLoc_31, struct AExpr_ callee_4, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_78);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseApp_(struct IntIntTuple2 baseLoc_31, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_79);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePrefix_(struct IntIntTuple2 baseLoc_32, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_80);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseNextLevelOp_(struct OpLevel_ level_1, struct IntIntTuple2 baseLoc_33, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_81);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 nextL_(struct IntIntTuple2 baseLoc_34, struct OpLevel_ level_2, struct AExpr_ expr_3, struct Op_ op_, struct IntIntTuple2 opLoc_2, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_82);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 nextR_(struct IntIntTuple2 baseLoc_34, struct OpLevel_ level_2, struct AExpr_ expr_5, struct Op_ op_1, struct IntIntTuple2 opLoc_3, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_83);

struct OpLevel_Token_IntIntTuple2Tuple2ListTuple2;

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseOps_(struct OpLevel_ level_2, struct IntIntTuple2 baseLoc_34, struct AExpr_ first_2, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_84);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseOp_(struct OpLevel_ level_3, struct IntIntTuple2 baseLoc_35, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_85);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTupleItem_(struct IntIntTuple2 baseLoc_36, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_86);

struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_31(struct IntIntTuple2 baseLoc_37, struct AExpr_List* acc_20, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_87);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTuple_(struct IntIntTuple2 baseLoc_37, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_88);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseAnno_(struct IntIntTuple2 baseLoc_38, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_89);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseExpr_(struct IntIntTuple2 baseLoc_39, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_90);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseStmt_(struct IntIntTuple2 baseLoc_40, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_91);

struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_32(struct IntIntTuple2 baseLoc_41, struct AExpr_List* acc_21, struct IntIntTuple2 alignLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_92);

struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseStmts_(struct IntIntTuple2 baseLoc_41, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_93);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseSemi_(struct IntIntTuple2 baseLoc_42, struct IntIntTuple2 mainLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_94);

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTopLevel_(struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_95);

struct AExpr_StringIntIntTuple2Tuple2ListTuple2;

struct AExpr_StringIntIntTuple2Tuple2ListTuple2 parse_(struct Token_IntIntTuple2Tuple2List* tokens_242);

struct String litToString_(struct Lit_ lit_);

struct String tokenToString_(struct Token_ token_12);

struct DumpTree_ fun_2(void* env_, struct ATy_ arg_3);

struct DumpTree_ fun_3(void* env_1, struct ATy_ arg_4);

struct DumpTree_ atDump_(struct ATy_ ty_);

struct DumpTree_ fun_4(void* env_2, struct APat_ arg_5);

struct DumpTree_ fun_5(void* env_3, struct APat_ arg_6);

struct DumpTree_ fun_6(void* env_4, struct APat_ arg_7);

struct DumpTree_ fun_7(void* env_5, struct APat_ arg_8);

struct DumpTree_ apDump_(struct APat_ pat_);

struct DumpTree_ fun_8(void* env_6, struct AExpr_ arg_9);

struct DumpTree_ fun_9(void* env_7, struct APat_ arg_10);

struct DumpTree_ fun_10(void* env_8, struct AExpr_ arg_11);

struct DumpTree_ fun_11(void* env_9, struct AExpr_ arg_12);

struct DumpTree_ fun_12(void* env_10, struct AExpr_ arg_13);

struct DumpTree_ axDump_(struct AExpr_ expr_);

int fun_(struct Token_IntIntTuple2Tuple2 arg_96);

int fun_13(void* env_11, struct Token_IntIntTuple2Tuple2 arg_14);

int fun_1(struct StringIntIntTuple2Tuple2 arg_97);

int fun_14(void* env_12, struct StringIntIntTuple2Tuple2 arg_15);

struct StringStringFun1;

int doSelf_(struct StringStringFun1 fileReadAllText_1);

struct String fileReadAllText_(struct String fileName_);

struct String fun_15(void* env_13, struct String arg_16);

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

struct StringList* cons_1(struct String head_, struct StringList* tail_) {
    struct StringList* list_ = (struct StringList*)malloc(sizeof(struct StringList));
    list_->head = head_;
    list_->tail = tail_;
    return list_;
}

int listIsEmpty_2(struct StringList* xs_) {
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

struct StringDumpTree_ListDumpTree_ListTuple3 {
    struct String t0;
    struct DumpTree_List* t1;
    struct DumpTree_List* t2;
};

struct DumpTree_List {
    struct DumpTree_ head;
    struct DumpTree_List* tail;
};

int listIsEmpty_1(struct DumpTree_List* xs_) {
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

struct Token_IntIntTuple2Tuple2List* go_44(struct Token_IntIntTuple2Tuple2List* acc_5, struct Token_IntIntTuple2Tuple2List* xs_2) {
    struct Token_IntIntTuple2Tuple2List* match_2;
    if ((!((!(xs_2))))) goto next_8;
    match_2 = acc_5;
    goto end_match_7;
next_8:;
    if ((!(xs_2))) goto next_9;
    struct Token_IntIntTuple2Tuple2 x_3 = xs_2->head;
    struct Token_IntIntTuple2Tuple2List* xs_3 = xs_2->tail;
    struct Token_IntIntTuple2Tuple2List* list_1 = (struct Token_IntIntTuple2Tuple2List*)malloc(sizeof(struct Token_IntIntTuple2Tuple2List));
    list_1->head = x_3;
    list_1->tail = acc_5;
    struct Token_IntIntTuple2Tuple2List* call_3 = go_44(list_1, xs_3);
    match_2 = call_3;
    goto end_match_7;
next_9:;
    exit(1);
end_match_7:;
    return match_2;
}

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

struct StringIntIntTuple2Tuple2 {
    struct String t0;
    struct IntIntTuple2 t1;
};

struct ATy_StringIntIntTuple2Tuple3 {
    struct ATy_ t0;
    struct String t1;
    struct IntIntTuple2 t2;
};

struct ATy_ListIntIntTuple2Tuple2 {
    struct ATy_List* t0;
    struct IntIntTuple2 t1;
};

struct ATy_ATy_IntIntTuple2Tuple3 {
    struct ATy_ t0;
    struct ATy_ t1;
    struct IntIntTuple2 t2;
};

struct ATy_List {
    struct ATy_ head;
    struct ATy_List* tail;
};

struct ATy_List* go_43(struct ATy_List* acc_5, struct ATy_List* xs_2) {
    struct ATy_List* match_3;
    if ((!((!(xs_2))))) goto next_11;
    match_3 = acc_5;
    goto end_match_10;
next_11:;
    if ((!(xs_2))) goto next_12;
    struct ATy_ x_3 = xs_2->head;
    struct ATy_List* xs_3 = xs_2->tail;
    struct ATy_List* list_2 = (struct ATy_List*)malloc(sizeof(struct ATy_List));
    list_2->head = x_3;
    list_2->tail = acc_5;
    struct ATy_List* call_4 = go_43(list_2, xs_3);
    match_3 = call_4;
    goto end_match_10;
next_12:;
    exit(1);
end_match_10:;
    return match_3;
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

struct StringATy_ListIntIntTuple2Tuple3 {
    struct String t0;
    struct ATy_List* t1;
    struct IntIntTuple2 t2;
};

struct AVariant_List {
    struct AVariant_ head;
    struct AVariant_List* tail;
};

struct AVariant_List* go_42(struct AVariant_List* acc_5, struct AVariant_List* xs_2) {
    struct AVariant_List* match_4;
    if ((!((!(xs_2))))) goto next_14;
    match_4 = acc_5;
    goto end_match_13;
next_14:;
    if ((!(xs_2))) goto next_15;
    struct AVariant_ x_3 = xs_2->head;
    struct AVariant_List* xs_3 = xs_2->tail;
    struct AVariant_List* list_3 = (struct AVariant_List*)malloc(sizeof(struct AVariant_List));
    list_3->head = x_3;
    list_3->tail = acc_5;
    struct AVariant_List* call_5 = go_42(list_3, xs_3);
    match_4 = call_5;
    goto end_match_13;
next_15:;
    exit(1);
end_match_13:;
    return match_4;
}

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

struct APat_ListIntIntTuple2Tuple2 {
    struct APat_List* t0;
    struct IntIntTuple2 t1;
};

struct APat_StringIntIntTuple2Tuple3 {
    struct APat_ t0;
    struct String t1;
    struct IntIntTuple2 t2;
};

struct APat_APat_ListIntIntTuple2Tuple3 {
    struct APat_ t0;
    struct APat_List* t1;
    struct IntIntTuple2 t2;
};

struct APat_APat_IntIntTuple2Tuple3 {
    struct APat_ t0;
    struct APat_ t1;
    struct IntIntTuple2 t2;
};

struct APat_ATy_IntIntTuple2Tuple3 {
    struct APat_ t0;
    struct ATy_ t1;
    struct IntIntTuple2 t2;
};

struct StringAPat_ListIntIntTuple2Tuple3 {
    struct String t0;
    struct APat_List* t1;
    struct IntIntTuple2 t2;
};

struct APat_List {
    struct APat_ head;
    struct APat_List* tail;
};

struct APat_List* go_41(struct APat_List* acc_5, struct APat_List* xs_2) {
    struct APat_List* match_5;
    if ((!((!(xs_2))))) goto next_17;
    match_5 = acc_5;
    goto end_match_16;
next_17:;
    if ((!(xs_2))) goto next_18;
    struct APat_ x_3 = xs_2->head;
    struct APat_List* xs_3 = xs_2->tail;
    struct APat_List* list_4 = (struct APat_List*)malloc(sizeof(struct APat_List));
    list_4->head = x_3;
    list_4->tail = acc_5;
    struct APat_List* call_6 = go_41(list_4, xs_3);
    match_5 = call_6;
    goto end_match_16;
next_18:;
    exit(1);
end_match_16:;
    return match_5;
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

struct AExpr_ListIntIntTuple2Tuple2 {
    struct AExpr_List* t0;
    struct IntIntTuple2 t1;
};

struct AExpr_AExpr_AExpr_IntIntTuple2Tuple4 {
    struct AExpr_ t0;
    struct AExpr_ t1;
    struct AExpr_ t2;
    struct IntIntTuple2 t3;
};

struct AExpr_AArm_ListIntIntTuple2Tuple3 {
    struct AExpr_ t0;
    struct AArm_List* t1;
    struct IntIntTuple2 t2;
};

struct APat_ListAExpr_IntIntTuple2Tuple3 {
    struct APat_List* t0;
    struct AExpr_ t1;
    struct IntIntTuple2 t2;
};

struct AExpr_StringIntIntTuple2Tuple3 {
    struct AExpr_ t0;
    struct String t1;
    struct IntIntTuple2 t2;
};

struct AExpr_AExpr_IntIntTuple2Tuple3 {
    struct AExpr_ t0;
    struct AExpr_ t1;
    struct IntIntTuple2 t2;
};

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

struct AExpr_ATy_IntIntTuple2Tuple3 {
    struct AExpr_ t0;
    struct ATy_ t1;
    struct IntIntTuple2 t2;
};

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

struct StringListIntIntTuple2Tuple2 {
    struct StringList* t0;
    struct IntIntTuple2 t1;
};

struct APat_AExpr_AExpr_IntIntTuple2Tuple4 {
    struct APat_ t0;
    struct AExpr_ t1;
    struct AExpr_ t2;
    struct IntIntTuple2 t3;
};

struct AArm_List {
    struct AArm_ head;
    struct AArm_List* tail;
};

struct AArm_List* go_40(struct AArm_List* acc_5, struct AArm_List* xs_2) {
    struct AArm_List* match_6;
    if ((!((!(xs_2))))) goto next_20;
    match_6 = acc_5;
    goto end_match_19;
next_20:;
    if ((!(xs_2))) goto next_21;
    struct AArm_ x_3 = xs_2->head;
    struct AArm_List* xs_3 = xs_2->tail;
    struct AArm_List* list_5 = (struct AArm_List*)malloc(sizeof(struct AArm_List));
    list_5->head = x_3;
    list_5->tail = acc_5;
    struct AArm_List* call_7 = go_40(list_5, xs_3);
    match_6 = call_7;
    goto end_match_19;
next_21:;
    exit(1);
end_match_19:;
    return match_6;
}

struct StringList* go_39(struct StringList* acc_5, struct StringList* xs_2) {
    struct StringList* match_7;
    if ((!((!(xs_2))))) goto next_23;
    match_7 = acc_5;
    goto end_match_22;
next_23:;
    if ((!(xs_2))) goto next_24;
    struct String x_3 = xs_2->head;
    struct StringList* xs_3 = xs_2->tail;
    struct StringList* list_6 = (struct StringList*)malloc(sizeof(struct StringList));
    list_6->head = x_3;
    list_6->tail = acc_5;
    struct StringList* call_8 = go_39(list_6, xs_3);
    match_7 = call_8;
    goto end_match_22;
next_24:;
    exit(1);
end_match_22:;
    return match_7;
}

struct AExpr_List* go_38(struct AExpr_List* acc_5, struct AExpr_List* xs_2) {
    struct AExpr_List* match_8;
    if ((!((!(xs_2))))) goto next_26;
    match_8 = acc_5;
    goto end_match_25;
next_26:;
    if ((!(xs_2))) goto next_27;
    struct AExpr_ x_3 = xs_2->head;
    struct AExpr_List* xs_3 = xs_2->tail;
    struct AExpr_List* list_7 = (struct AExpr_List*)malloc(sizeof(struct AExpr_List));
    list_7->head = x_3;
    list_7->tail = acc_5;
    struct AExpr_List* call_9 = go_38(list_7, xs_3);
    match_8 = call_9;
    goto end_match_25;
next_27:;
    exit(1);
end_match_25:;
    return match_8;
}

struct DumpTree_List* go_45(struct DumpTree_List* acc_5, struct DumpTree_List* xs_2) {
    struct DumpTree_List* match_9;
    if ((!((!(xs_2))))) goto next_29;
    match_9 = acc_5;
    goto end_match_28;
next_29:;
    if ((!(xs_2))) goto next_30;
    struct DumpTree_ x_3 = xs_2->head;
    struct DumpTree_List* xs_3 = xs_2->tail;
    struct DumpTree_List* list_8 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_8->head = x_3;
    list_8->tail = acc_5;
    struct DumpTree_List* call_10 = go_45(list_8, xs_3);
    match_9 = call_10;
    goto end_match_28;
next_30:;
    exit(1);
end_match_28:;
    return match_9;
}

struct Token_IntIntTuple2Tuple2List* listRev_7(struct Token_IntIntTuple2Tuple2List* xs_1) {
    struct Token_IntIntTuple2Tuple2List* call_11 = go_44(NULL, xs_1);
    return call_11;
}

struct ATy_List* listRev_6(struct ATy_List* xs_1) {
    struct ATy_List* call_12 = go_43(NULL, xs_1);
    return call_12;
}

struct AVariant_List* listRev_5(struct AVariant_List* xs_1) {
    struct AVariant_List* call_13 = go_42(NULL, xs_1);
    return call_13;
}

struct APat_List* listRev_4(struct APat_List* xs_1) {
    struct APat_List* call_14 = go_41(NULL, xs_1);
    return call_14;
}

struct AArm_List* listRev_3(struct AArm_List* xs_1) {
    struct AArm_List* call_15 = go_40(NULL, xs_1);
    return call_15;
}

struct StringList* listRev_2(struct StringList* xs_1) {
    struct StringList* call_16 = go_39(NULL, xs_1);
    return call_16;
}

struct AExpr_List* listRev_1(struct AExpr_List* xs_1) {
    struct AExpr_List* call_17 = go_38(NULL, xs_1);
    return call_17;
}

struct DumpTree_List* listRev_8(struct DumpTree_List* xs_1) {
    struct DumpTree_List* call_18 = go_45(NULL, xs_1);
    return call_18;
}

int go_37(int len_, struct StringList* xs_5) {
    int match_10;
    if ((!((!(xs_5))))) goto next_32;
    match_10 = len_;
    goto end_match_31;
next_32:;
    if ((!(xs_5))) goto next_33;
    struct StringList* xs_6 = xs_5->tail;
    int call_19 = go_37((len_ + 1), xs_6);
    match_10 = call_19;
    goto end_match_31;
next_33:;
    exit(1);
end_match_31:;
    return match_10;
}

int listLength_1(struct StringList* xs_4) {
    int call_20 = go_37(0, xs_4);
    return call_20;
}

struct Token_IntIntTuple2Tuple2UnitFun1 {
    int(*fun)(void*, struct Token_IntIntTuple2Tuple2);
    void* env;
};

int listIter_2(struct Token_IntIntTuple2Tuple2UnitFun1 f_, struct Token_IntIntTuple2Tuple2List* xs_7) {
    int match_11;
    if ((!((!(xs_7))))) goto next_35;
    match_11 = 0;
    goto end_match_34;
next_35:;
    if ((!(xs_7))) goto next_36;
    struct Token_IntIntTuple2Tuple2 x_4 = xs_7->head;
    struct Token_IntIntTuple2Tuple2List* xs_8 = xs_7->tail;
    int app_ = f_.fun(f_.env, x_4);
    int call_21 = listIter_2(f_, xs_8);
    match_11 = 0;
    goto end_match_34;
next_36:;
    exit(1);
end_match_34:;
    return 0;
}

struct StringIntIntTuple2Tuple2UnitFun1 {
    int(*fun)(void*, struct StringIntIntTuple2Tuple2);
    void* env;
};

struct StringIntIntTuple2Tuple2List {
    struct StringIntIntTuple2Tuple2 head;
    struct StringIntIntTuple2Tuple2List* tail;
};

int listIter_1(struct StringIntIntTuple2Tuple2UnitFun1 f_, struct StringIntIntTuple2Tuple2List* xs_7) {
    int match_12;
    if ((!((!(xs_7))))) goto next_38;
    match_12 = 0;
    goto end_match_37;
next_38:;
    if ((!(xs_7))) goto next_39;
    struct StringIntIntTuple2Tuple2 x_4 = xs_7->head;
    struct StringIntIntTuple2Tuple2List* xs_8 = xs_7->tail;
    int app_1 = f_.fun(f_.env, x_4);
    int call_22 = listIter_1(f_, xs_8);
    match_12 = 0;
    goto end_match_37;
next_39:;
    exit(1);
end_match_37:;
    return 0;
}

struct ATy_DumpTree_Fun1 {
    struct DumpTree_(*fun)(void*, struct ATy_);
    void* env;
};

struct DumpTree_List* go_36(struct ATy_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct ATy_List* xs_10) {
    struct DumpTree_List* match_13;
    if ((!((!(xs_10))))) goto next_41;
    struct DumpTree_List* call_23 = listRev_8(acc_6);
    match_13 = call_23;
    goto end_match_40;
next_41:;
    if ((!(xs_10))) goto next_42;
    struct ATy_ x_5 = xs_10->head;
    struct ATy_List* xs_11 = xs_10->tail;
    struct DumpTree_ app_2 = f_1.fun(f_1.env, x_5);
    struct DumpTree_List* list_9 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_9->head = app_2;
    list_9->tail = acc_6;
    struct DumpTree_List* call_24 = go_36(f_1, list_9, xs_11);
    match_13 = call_24;
    goto end_match_40;
next_42:;
    exit(1);
end_match_40:;
    return match_13;
}

struct APat_DumpTree_Fun1 {
    struct DumpTree_(*fun)(void*, struct APat_);
    void* env;
};

struct DumpTree_List* go_35(struct APat_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct APat_List* xs_10) {
    struct DumpTree_List* match_14;
    if ((!((!(xs_10))))) goto next_44;
    struct DumpTree_List* call_25 = listRev_8(acc_6);
    match_14 = call_25;
    goto end_match_43;
next_44:;
    if ((!(xs_10))) goto next_45;
    struct APat_ x_5 = xs_10->head;
    struct APat_List* xs_11 = xs_10->tail;
    struct DumpTree_ app_3 = f_1.fun(f_1.env, x_5);
    struct DumpTree_List* list_10 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_10->head = app_3;
    list_10->tail = acc_6;
    struct DumpTree_List* call_26 = go_35(f_1, list_10, xs_11);
    match_14 = call_26;
    goto end_match_43;
next_45:;
    exit(1);
end_match_43:;
    return match_14;
}

struct AExpr_DumpTree_Fun1 {
    struct DumpTree_(*fun)(void*, struct AExpr_);
    void* env;
};

struct DumpTree_List* go_34(struct AExpr_DumpTree_Fun1 f_1, struct DumpTree_List* acc_6, struct AExpr_List* xs_10) {
    struct DumpTree_List* match_15;
    if ((!((!(xs_10))))) goto next_47;
    struct DumpTree_List* call_27 = listRev_8(acc_6);
    match_15 = call_27;
    goto end_match_46;
next_47:;
    if ((!(xs_10))) goto next_48;
    struct AExpr_ x_5 = xs_10->head;
    struct AExpr_List* xs_11 = xs_10->tail;
    struct DumpTree_ app_4 = f_1.fun(f_1.env, x_5);
    struct DumpTree_List* list_11 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_11->head = app_4;
    list_11->tail = acc_6;
    struct DumpTree_List* call_28 = go_34(f_1, list_11, xs_11);
    match_15 = call_28;
    goto end_match_46;
next_48:;
    exit(1);
end_match_46:;
    return match_15;
}

struct DumpTree_List* listMap_3(struct ATy_DumpTree_Fun1 f_1, struct ATy_List* xs_9) {
    struct DumpTree_List* call_29 = go_36(f_1, NULL, xs_9);
    return call_29;
}

struct DumpTree_List* listMap_2(struct APat_DumpTree_Fun1 f_1, struct APat_List* xs_9) {
    struct DumpTree_List* call_30 = go_35(f_1, NULL, xs_9);
    return call_30;
}

struct DumpTree_List* listMap_1(struct AExpr_DumpTree_Fun1 f_1, struct AExpr_List* xs_9) {
    struct DumpTree_List* call_31 = go_34(f_1, NULL, xs_9);
    return call_31;
}

int intMin_(int x_7, int y_2) {
    int match_16;
    if ((y_2 >= x_7)) goto next_50;
    match_16 = y_2;
    goto end_match_49;
next_50:;
    if ((y_2 < x_7)) goto next_51;
    match_16 = x_7;
    goto end_match_49;
next_51:;
    exit(1);
end_match_49:;
    return match_16;
}

int intMax_(int x_8, int y_3) {
    int match_17;
    if ((x_8 >= y_3)) goto next_53;
    match_17 = y_3;
    goto end_match_52;
next_53:;
    if ((x_8 < y_3)) goto next_54;
    match_17 = x_8;
    goto end_match_52;
next_54:;
    exit(1);
end_match_52:;
    return match_17;
}

int intEq_(int x_9, int y_4) {
    return (x_9 == y_4);
}

struct String strSlice_(int start_, int endIndex_1, struct String s_3) {
    int match_18;
    if ((endIndex_1 < start_)) goto next_56;
    match_18 = (s_3.len >= endIndex_1);
    goto end_match_55;
next_56:;
    if ((endIndex_1 >= start_)) goto next_57;
    match_18 = 0;
    goto end_match_55;
next_57:;
    exit(1);
end_match_55:;
    milone_assert(match_18, 85, 2);
    int call_32 = 0;
    struct String match_19;
    if ((start_ < endIndex_1)) goto next_59;
    match_19 = (struct String){.str = "", .len = 0};
    goto end_match_58;
next_59:;
    if ((start_ >= endIndex_1)) goto next_60;
    struct String call_33 = str_get_slice(start_, (endIndex_1 - 1), s_3);
    match_19 = call_33;
    goto end_match_58;
next_60:;
    exit(1);
end_match_58:;
    return match_19;
}

struct StringStringListTuple2 {
    struct String t0;
    struct StringList* t1;
};

struct StringStringListTuple2 go_16(struct StringList* xs_16, int xn_) {
    struct StringStringListTuple2 match_20;
    if ((!((!(xs_16))))) goto next_62;
    milone_assert((xn_ == 0), 99, 6);
    int call_34 = 0;
    struct StringStringListTuple2 tuple_;
    tuple_.t0 = (struct String){.str = "", .len = 0};
    tuple_.t1 = NULL;
    match_20 = tuple_;
    goto end_match_61;
next_62:;
    if ((!(xs_16))) goto next_63;
    struct String x_10 = xs_16->head;
    struct StringList* xs_17 = xs_16->tail;
    if ((xn_ != 1)) goto next_63;
    struct StringStringListTuple2 tuple_1;
    tuple_1.t0 = x_10;
    tuple_1.t1 = xs_17;
    match_20 = tuple_1;
    goto end_match_61;
next_63:;
    if ((!(xs_16))) goto next_64;
    struct String x_11 = xs_16->head;
    if ((!(xs_16->tail))) goto next_64;
    struct String y_5 = xs_16->tail->head;
    struct StringList* xs_18 = xs_16->tail->tail;
    if ((xn_ != 2)) goto next_64;
    struct StringStringListTuple2 tuple_2;
    tuple_2.t0 = str_add(x_11, y_5);
    tuple_2.t1 = xs_18;
    match_20 = tuple_2;
    goto end_match_61;
next_64:;
    struct StringList* xs_19 = xs_16;
    int m_ = (xn_ / 2);
    struct StringStringListTuple2 call_35 = go_16(xs_19, m_);
    struct String l_8 = call_35.t0;
    struct StringList* xs_20 = call_35.t1;
    struct StringStringListTuple2 call_36 = go_16(xs_20, (xn_ - m_));
    struct String r_20 = call_36.t0;
    struct StringList* xs_21 = call_36.t1;
    struct StringStringListTuple2 tuple_3;
    tuple_3.t0 = str_add(l_8, r_20);
    tuple_3.t1 = xs_21;
    match_20 = tuple_3;
    goto end_match_61;
next_65:;
end_match_61:;
    return match_20;
}

struct String strConcat_(struct StringList* xs_15) {
    int call_37 = listLength_1(xs_15);
    int n_ = call_37;
    struct StringStringListTuple2 call_38 = go_16(xs_15, n_);
    struct String s_4 = call_38.t0;
    struct StringList* xs_22 = call_38.t1;
    int call_39 = listIsEmpty_2(xs_22);
    milone_assert(call_39, 112, 2);
    int call_40 = 0;
    return s_4;
}

struct String go_17(struct String acc_7, int len_2, int n_1) {
    struct String match_21;
    int match_22;
    if ((n_1 != 0)) goto next_68;
    match_22 = (0 >= len_2);
    goto end_match_67;
next_68:;
    if ((n_1 == 0)) goto next_69;
    match_22 = 0;
    goto end_match_67;
next_69:;
    exit(1);
end_match_67:;
    if ((!(match_22))) goto next_70;
    match_21 = acc_7;
    goto end_match_66;
next_70:;
    if (match_22) goto next_71;
    int d_ = (n_1 % 16);
    struct String call_41 = strSlice_(d_, (d_ + 1), (struct String){.str = "0123456789abcdef", .len = 16});
    struct String s_5 = call_41;
    struct String call_42 = go_17(str_add(s_5, acc_7), (len_2 - 1), (n_1 / 16));
    match_21 = call_42;
    goto end_match_66;
next_71:;
    exit(1);
end_match_66:;
    return match_21;
}

struct String intToHexWithPadding_(int len_1, int value_3) {
    struct String match_23;
    if ((value_3 >= 0)) goto next_73;
    struct String call_43 = failwith_3((struct String){.str = "intToHexWithPadding: unimplemented negative", .len = 43});
    match_23 = call_43;
    goto end_match_72;
next_73:;
    if ((value_3 < 0)) goto next_74;
    milone_assert((len_1 >= 0), 132, 2);
    int call_44 = 0;
    struct String match_24;
    int match_25;
    if ((value_3 != 0)) goto next_77;
    match_25 = (len_1 == 0);
    goto end_match_76;
next_77:;
    if ((value_3 == 0)) goto next_78;
    match_25 = 0;
    goto end_match_76;
next_78:;
    exit(1);
end_match_76:;
    if ((!(match_25))) goto next_79;
    match_24 = (struct String){.str = "0", .len = 1};
    goto end_match_75;
next_79:;
    if (match_25) goto next_80;
    struct String call_45 = go_17((struct String){.str = "", .len = 0}, len_1, value_3);
    match_24 = call_45;
    goto end_match_75;
next_80:;
    exit(1);
end_match_75:;
    match_23 = match_24;
    goto end_match_72;
next_74:;
    exit(1);
end_match_72:;
    return match_23;
}

struct DumpTree_ dumpTreeNew_(struct String text_43, struct DumpTree_List* children_) {
    struct StringDumpTree_ListDumpTree_ListTuple3 tuple_4;
    tuple_4.t0 = text_43;
    tuple_4.t1 = children_;
    tuple_4.t2 = NULL;
    struct StringDumpTree_ListDumpTree_ListTuple3* payload_ = (struct StringDumpTree_ListDumpTree_ListTuple3*)malloc(sizeof(struct StringDumpTree_ListDumpTree_ListTuple3));
    (*(((struct StringDumpTree_ListDumpTree_ListTuple3*)payload_))) = tuple_4;
    struct DumpTree_ variant_ = (struct DumpTree_){.tag = DumpTree_, .DumpTree_ = payload_};
    return variant_;
}

struct DumpTree_ dumpTreeNewLeaf_(struct String text_44) {
    struct StringDumpTree_ListDumpTree_ListTuple3 tuple_5;
    tuple_5.t0 = text_44;
    tuple_5.t1 = NULL;
    tuple_5.t2 = NULL;
    struct StringDumpTree_ListDumpTree_ListTuple3* payload_1 = (struct StringDumpTree_ListDumpTree_ListTuple3*)malloc(sizeof(struct StringDumpTree_ListDumpTree_ListTuple3));
    (*(((struct StringDumpTree_ListDumpTree_ListTuple3*)payload_1))) = tuple_5;
    struct DumpTree_ variant_1 = (struct DumpTree_){.tag = DumpTree_, .DumpTree_ = payload_1};
    return variant_1;
}

struct DumpTree_ dumpTreeAttachNext_(struct DumpTree_ next_1, struct DumpTree_ tree_) {
    struct DumpTree_ match_26;
    struct String text_45 = (*(tree_.DumpTree_)).t0;
    struct DumpTree_List* children_1 = (*(tree_.DumpTree_)).t1;
    struct DumpTree_List* oldNext_ = (*(tree_.DumpTree_)).t2;
    int call_46 = listIsEmpty_1(children_1);
    milone_assert((!(call_46)), 156, 4);
    int call_47 = 0;
    int call_48 = listIsEmpty_1(oldNext_);
    milone_assert(call_48, 157, 4);
    int call_49 = 0;
    struct DumpTree_List* list_12 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_12->head = next_1;
    list_12->tail = NULL;
    struct StringDumpTree_ListDumpTree_ListTuple3 tuple_6;
    tuple_6.t0 = text_45;
    tuple_6.t1 = children_1;
    tuple_6.t2 = list_12;
    struct StringDumpTree_ListDumpTree_ListTuple3* payload_2 = (struct StringDumpTree_ListDumpTree_ListTuple3*)malloc(sizeof(struct StringDumpTree_ListDumpTree_ListTuple3));
    (*(((struct StringDumpTree_ListDumpTree_ListTuple3*)payload_2))) = tuple_6;
    struct DumpTree_ variant_2 = (struct DumpTree_){.tag = DumpTree_, .DumpTree_ = payload_2};
    match_26 = variant_2;
    goto end_match_81;
next_82:;
    exit(1);
end_match_81:;
    return match_26;
}

struct DumpTree_ dumpTreeFromError_(struct String msg_, struct IntIntTuple2 arg_17) {
    int y_6 = arg_17.t0;
    int x_12 = arg_17.t1;
    struct String call_50 = str_of_int((y_6 + 1));
    struct String y_7 = call_50;
    struct String call_51 = str_of_int((x_12 + 1));
    struct String x_13 = call_51;
    struct DumpTree_ call_52 = dumpTreeNewLeaf_(msg_);
    struct DumpTree_ call_53 = dumpTreeNewLeaf_(str_add(str_add(str_add(str_add((struct String){.str = "(", .len = 1}, y_7), (struct String){.str = ":", .len = 1}), x_13), (struct String){.str = ")", .len = 1}));
    struct DumpTree_List* list_14 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_14->head = call_53;
    list_14->tail = NULL;
    struct DumpTree_List* list_13 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_13->head = call_52;
    list_13->tail = list_14;
    struct DumpTree_ call_54 = dumpTreeNew_((struct String){.str = "ERROR", .len = 5}, list_13);
    return call_54;
}

int charIsControl_(char c_8) {
    int call_55 = ((int)c_8);
    int n_2 = call_55;
    int match_27;
    int match_28;
    if ((n_2 < 0)) goto next_85;
    match_28 = (n_2 < 32);
    goto end_match_84;
next_85:;
    if ((n_2 >= 0)) goto next_86;
    match_28 = 0;
    goto end_match_84;
next_86:;
    exit(1);
end_match_84:;
    if ((!(match_28))) goto next_87;
    match_27 = 1;
    goto end_match_83;
next_87:;
    if (match_28) goto next_88;
    match_27 = (n_2 == 127);
    goto end_match_83;
next_88:;
    exit(1);
end_match_83:;
    return match_27;
}

int charNeedsEscaping_(char c_9) {
    int match_29;
    int match_30;
    int match_31;
    int call_56 = charIsControl_(c_9);
    if ((!(call_56))) goto next_92;
    match_31 = 1;
    goto end_match_91;
next_92:;
    if (call_56) goto next_93;
    match_31 = (c_9 == '\\');
    goto end_match_91;
next_93:;
    exit(1);
end_match_91:;
    if ((!(match_31))) goto next_94;
    match_30 = 1;
    goto end_match_90;
next_94:;
    if (match_31) goto next_95;
    match_30 = (c_9 == '"');
    goto end_match_90;
next_95:;
    exit(1);
end_match_90:;
    if ((!(match_30))) goto next_96;
    match_29 = 1;
    goto end_match_89;
next_96:;
    if (match_30) goto next_97;
    match_29 = (c_9 == '\'');
    goto end_match_89;
next_97:;
    exit(1);
end_match_89:;
    return match_29;
}

int go_18(struct String str_2, int i_50) {
    int match_32;
    if ((i_50 >= str_2.len)) goto next_99;
    int match_33;
    int call_57 = charNeedsEscaping_(str_2.str[i_50]);
    if ((!(call_57))) goto next_102;
    match_33 = 1;
    goto end_match_101;
next_102:;
    if (call_57) goto next_103;
    int call_58 = go_18(str_2, (i_50 + 1));
    match_33 = call_58;
    goto end_match_101;
next_103:;
    exit(1);
end_match_101:;
    match_32 = match_33;
    goto end_match_98;
next_99:;
    if ((i_50 < str_2.len)) goto next_100;
    match_32 = 0;
    goto end_match_98;
next_100:;
    exit(1);
end_match_98:;
    return match_32;
}

int strNeedsEscaping_(struct String str_2) {
    int call_59 = go_18(str_2, 0);
    return call_59;
}

struct IntStringTuple2 {
    int t0;
    struct String t1;
};

struct IntStringTuple2 strEscapeCore_(int i_51, struct String str_3) {
    int call_60 = charNeedsEscaping_(str_3.str[i_51]);
    milone_assert(call_60, 181, 4);
    int call_61 = 0;
    struct IntStringTuple2 match_34;
    if ((str_3.str[i_51] != '\0')) goto next_105;
    struct IntStringTuple2 tuple_7;
    tuple_7.t0 = (i_51 + 1);
    tuple_7.t1 = (struct String){.str = "\\0", .len = 2};
    match_34 = tuple_7;
    goto end_match_104;
next_105:;
    if ((str_3.str[i_51] != '\t')) goto next_106;
    struct IntStringTuple2 tuple_8;
    tuple_8.t0 = (i_51 + 1);
    tuple_8.t1 = (struct String){.str = "\\t", .len = 2};
    match_34 = tuple_8;
    goto end_match_104;
next_106:;
    if ((str_3.str[i_51] != '\n')) goto next_107;
    struct IntStringTuple2 tuple_9;
    tuple_9.t0 = (i_51 + 1);
    tuple_9.t1 = (struct String){.str = "\\n", .len = 2};
    match_34 = tuple_9;
    goto end_match_104;
next_107:;
    if ((str_3.str[i_51] != '\r')) goto next_108;
    struct IntStringTuple2 tuple_10;
    tuple_10.t0 = (i_51 + 1);
    tuple_10.t1 = (struct String){.str = "\\r", .len = 2};
    match_34 = tuple_10;
    goto end_match_104;
next_108:;
    if ((str_3.str[i_51] != '\'')) goto next_109;
    struct IntStringTuple2 tuple_11;
    tuple_11.t0 = (i_51 + 1);
    tuple_11.t1 = (struct String){.str = "\\'", .len = 2};
    match_34 = tuple_11;
    goto end_match_104;
next_109:;
    if ((str_3.str[i_51] != '"')) goto next_110;
    struct IntStringTuple2 tuple_12;
    tuple_12.t0 = (i_51 + 1);
    tuple_12.t1 = (struct String){.str = "\\\"", .len = 2};
    match_34 = tuple_12;
    goto end_match_104;
next_110:;
    if ((str_3.str[i_51] != '\\')) goto next_111;
    struct IntStringTuple2 tuple_13;
    tuple_13.t0 = (i_51 + 1);
    tuple_13.t1 = (struct String){.str = "\\\\", .len = 2};
    match_34 = tuple_13;
    goto end_match_104;
next_111:;
    char c_10 = str_3.str[i_51];
    int call_62 = ((int)c_10);
    struct String call_63 = intToHexWithPadding_(2, call_62);
    struct String h_ = call_63;
    struct IntStringTuple2 tuple_14;
    tuple_14.t0 = (i_51 + 1);
    tuple_14.t1 = str_add((struct String){.str = "\\x", .len = 2}, h_);
    match_34 = tuple_14;
    goto end_match_104;
next_112:;
end_match_104:;
    return match_34;
}

int raw_(struct String str_4, int i_53) {
    int match_35;
    int match_36;
    if ((i_53 != str_4.len)) goto next_115;
    match_36 = 1;
    goto end_match_114;
next_115:;
    if ((i_53 == str_4.len)) goto next_116;
    int call_64 = charNeedsEscaping_(str_4.str[i_53]);
    match_36 = call_64;
    goto end_match_114;
next_116:;
    exit(1);
end_match_114:;
    if ((!(match_36))) goto next_117;
    match_35 = i_53;
    goto end_match_113;
next_117:;
    if (match_36) goto next_118;
    int call_65 = raw_(str_4, (i_53 + 1));
    match_35 = call_65;
    goto end_match_113;
next_118:;
    exit(1);
end_match_113:;
    return match_35;
}

struct IntStringListTuple2 {
    int t0;
    struct StringList* t1;
};

struct StringList* go_19(struct String str_4, struct StringList* acc_8, int i_52) {
    int call_66 = raw_(str_4, i_52);
    int r_21 = call_66;
    struct String call_67 = strSlice_(i_52, r_21, str_4);
    struct StringList* list_15 = (struct StringList*)malloc(sizeof(struct StringList));
    list_15->head = call_67;
    list_15->tail = acc_8;
    struct IntStringListTuple2 tuple_15;
    tuple_15.t0 = r_21;
    tuple_15.t1 = list_15;
    int i_54 = tuple_15.t0;
    struct StringList* acc_9 = tuple_15.t1;
    struct StringList* match_37;
    if ((i_54 != str_4.len)) goto next_120;
    match_37 = acc_9;
    goto end_match_119;
next_120:;
    if ((i_54 == str_4.len)) goto next_121;
    struct IntStringTuple2 call_68 = strEscapeCore_(i_54, str_4);
    int i_55 = call_68.t0;
    struct String s_6 = call_68.t1;
    struct StringList* list_16 = (struct StringList*)malloc(sizeof(struct StringList));
    list_16->head = s_6;
    list_16->tail = acc_9;
    struct StringList* call_69 = go_19(str_4, list_16, i_55);
    match_37 = call_69;
    goto end_match_119;
next_121:;
    exit(1);
end_match_119:;
    return match_37;
}

struct String strEscape_(struct String str_4) {
    struct String match_38;
    int call_70 = strNeedsEscaping_(str_4);
    if (call_70) goto next_123;
    match_38 = str_4;
    goto end_match_122;
next_123:;
    if ((!(call_70))) goto next_124;
    struct StringList* call_71 = go_19(str_4, NULL, 0);
    struct StringList* call_72 = listRev_2(call_71);
    struct String call_73 = strConcat_(call_72);
    match_38 = call_73;
    goto end_match_122;
next_124:;
    exit(1);
end_match_122:;
    return match_38;
}

struct StringList* goChildren_(struct String eol_1, struct DumpTree_List* children_2, struct StringList* acc_11) {
    struct StringList* match_39;
    if ((!((!(children_2))))) goto next_126;
    match_39 = acc_11;
    goto end_match_125;
next_126:;
    if ((!(children_2))) goto next_127;
    struct DumpTree_ child_ = children_2->head;
    struct DumpTree_List* children_3 = children_2->tail;
    struct StringList* call_74 = cons_1(eol_1, acc_11);
    struct StringList* call_75 = cons_1((struct String){.str = "- ", .len = 2}, call_74);
    struct StringList* call_76 = go_20(str_add(eol_1, (struct String){.str = "  ", .len = 2}), child_, call_75);
    struct StringList* call_77 = goChildren_(eol_1, children_3, call_76);
    match_39 = call_77;
    goto end_match_125;
next_127:;
    exit(1);
end_match_125:;
    return match_39;
}

struct StringList* goNext_(struct String eol_2, struct DumpTree_List* next_2, struct StringList* acc_12) {
    struct StringList* match_40;
    if ((!((!(next_2))))) goto next_129;
    match_40 = acc_12;
    goto end_match_128;
next_129:;
    if ((!(next_2))) goto next_130;
    struct DumpTree_ next_3 = next_2->head;
    if ((!((!(next_2->tail))))) goto next_130;
    struct StringList* call_78 = cons_1(eol_2, acc_12);
    struct StringList* call_79 = go_20(eol_2, next_3, call_78);
    match_40 = call_79;
    goto end_match_128;
next_130:;
    struct StringList* call_80 = failwith_2((struct String){.str = "NEVER: DumpTree.next never empty", .len = 32});
    match_40 = call_80;
    goto end_match_128;
next_131:;
end_match_128:;
    return match_40;
}

struct StringList* go_20(struct String eol_, struct DumpTree_ node_1, struct StringList* acc_10) {
    struct StringList* match_41;
    struct String text_46 = (*(node_1.DumpTree_)).t0;
    if ((!((!((*(node_1.DumpTree_)).t1))))) goto next_133;
    if ((!((!((*(node_1.DumpTree_)).t2))))) goto next_133;
    struct String call_81 = strEscape_(text_46);
    struct StringList* call_82 = cons_1(call_81, acc_10);
    match_41 = call_82;
    goto end_match_132;
next_133:;
    struct String text_47 = (*(node_1.DumpTree_)).t0;
    if ((!((*(node_1.DumpTree_)).t1))) goto next_134;
    struct String childText_ = (*((*(node_1.DumpTree_)).t1->head.DumpTree_)).t0;
    if ((!((!((*((*(node_1.DumpTree_)).t1->head.DumpTree_)).t1))))) goto next_134;
    if ((!((!((*((*(node_1.DumpTree_)).t1->head.DumpTree_)).t2))))) goto next_134;
    if ((!((!((*(node_1.DumpTree_)).t1->tail))))) goto next_134;
    struct DumpTree_List* next_4 = (*(node_1.DumpTree_)).t2;
    struct String call_83 = strEscape_(childText_);
    struct String call_84 = strEscape_(text_47);
    struct StringList* call_85 = cons_1(call_84, acc_10);
    struct StringList* call_86 = cons_1((struct String){.str = ": ", .len = 2}, call_85);
    struct StringList* call_87 = cons_1(call_83, call_86);
    struct StringList* call_88 = goNext_(eol_, next_4, call_87);
    match_41 = call_88;
    goto end_match_132;
next_134:;
    struct String text_48 = (*(node_1.DumpTree_)).t0;
    struct DumpTree_List* children_4 = (*(node_1.DumpTree_)).t1;
    struct DumpTree_List* next_5 = (*(node_1.DumpTree_)).t2;
    struct String call_89 = strEscape_(text_48);
    struct StringList* call_90 = cons_1(call_89, acc_10);
    struct StringList* call_91 = cons_1((struct String){.str = ":", .len = 1}, call_90);
    struct StringList* call_92 = goChildren_(eol_, children_4, call_91);
    struct StringList* call_93 = goNext_(eol_, next_5, call_92);
    match_41 = call_93;
    goto end_match_132;
next_135:;
    exit(1);
end_match_132:;
    return match_41;
}

struct String dumpTreeToString_(struct DumpTree_ node_) {
    struct String eol_3 = (struct String){.str = "\n", .len = 1};
    struct StringList* call_94 = go_20(eol_3, node_, NULL);
    struct StringList* call_95 = listRev_2(call_94);
    struct String call_96 = strConcat_(call_95);
    return call_96;
}

int locX_(struct IntIntTuple2 arg_18) {
    int x_14 = arg_18.t1;
    return x_14;
}

int locY_(struct IntIntTuple2 arg_19) {
    int y_8 = arg_19.t0;
    return y_8;
}

int locIsSameRow_(struct IntIntTuple2 first_, struct IntIntTuple2 second_) {
    int call_97 = locY_(first_);
    int call_98 = locY_(second_);
    return (call_97 == call_98);
}

int locIsSameColumn_(struct IntIntTuple2 first_1, struct IntIntTuple2 second_1) {
    int call_99 = locX_(first_1);
    int call_100 = locX_(second_1);
    return (call_99 == call_100);
}

int locInside_(struct IntIntTuple2 firstLoc_, struct IntIntTuple2 secondLoc_) {
    int call_101 = locX_(secondLoc_);
    int call_102 = locX_(firstLoc_);
    return (call_101 >= call_102);
}

struct IntIntTuple2 locAddX_(int dx_, struct IntIntTuple2 arg_20) {
    int y_9 = arg_20.t0;
    int x_15 = arg_20.t1;
    struct IntIntTuple2 tuple_16;
    tuple_16.t0 = y_9;
    tuple_16.t1 = (x_15 + dx_);
    return tuple_16;
}

struct IntIntTuple2 locMax_(struct IntIntTuple2 arg_21, struct IntIntTuple2 arg_22) {
    int firstY_ = arg_21.t0;
    int firstX_ = arg_21.t1;
    int secondY_ = arg_22.t0;
    int secondX_ = arg_22.t1;
    int call_103 = intMax_(firstY_, secondY_);
    int call_104 = intMax_(firstX_, secondX_);
    struct IntIntTuple2 tuple_17;
    tuple_17.t0 = call_103;
    tuple_17.t1 = call_104;
    return tuple_17;
}

int tokenIsExprOrPatFirst_(struct Token_ token_7) {
    int match_42;
    if ((token_7.tag != Bool_1)) goto next_138;
    goto match_body_137;
next_138:;
    if ((token_7.tag != Int_1)) goto next_139;
    goto match_body_137;
next_139:;
    if ((token_7.tag != Char_1)) goto next_140;
    goto match_body_137;
next_140:;
    if ((token_7.tag != Str_1)) goto next_141;
    goto match_body_137;
next_141:;
    if ((token_7.tag != Ident_)) goto next_142;
    goto match_body_137;
next_142:;
    if ((token_7.tag != ParenL_)) goto next_143;
    goto match_body_137;
next_143:;
    if ((token_7.tag != BracketL_)) goto next_144;
    goto match_body_137;
match_body_137:;
    match_42 = 1;
    goto end_match_136;
next_144:;
    match_42 = 0;
    goto end_match_136;
next_145:;
end_match_136:;
    return match_42;
}

int tokenIsExprFirst_(struct Token_ token_8) {
    int match_43;
    int call_105 = tokenIsExprOrPatFirst_(token_8);
    if ((!(call_105))) goto next_148;
    match_43 = 1;
    goto end_match_146;
next_148:;
    if ((token_8.tag != Minus_)) goto next_149;
    goto match_body_147;
next_149:;
    if ((token_8.tag != If_)) goto next_150;
    goto match_body_147;
next_150:;
    if ((token_8.tag != Match_)) goto next_151;
    goto match_body_147;
next_151:;
    if ((token_8.tag != Fun_)) goto next_152;
    goto match_body_147;
next_152:;
    if ((token_8.tag != Do_)) goto next_153;
    goto match_body_147;
next_153:;
    if ((token_8.tag != Let_)) goto next_154;
    goto match_body_147;
next_154:;
    if ((token_8.tag != Type_)) goto next_155;
    goto match_body_147;
next_155:;
    if ((token_8.tag != Open_)) goto next_156;
    goto match_body_147;
match_body_147:;
    match_43 = 1;
    goto end_match_146;
next_156:;
    match_43 = 0;
    goto end_match_146;
next_157:;
end_match_146:;
    return match_43;
}

int tokenIsArgFirst_(struct Token_ token_9) {
    int match_44;
    if ((token_9.tag != Minus_)) goto next_159;
    match_44 = 0;
    goto end_match_158;
next_159:;
    int call_106 = tokenIsExprFirst_(token_9);
    match_44 = call_106;
    goto end_match_158;
next_160:;
end_match_158:;
    return match_44;
}

int tokenIsPatFirst_(struct Token_ token_10) {
    int call_107 = tokenIsExprOrPatFirst_(token_10);
    return call_107;
}

int tokenIsAccessModifier_(struct Token_ token_11) {
    int match_45;
    if ((token_11.tag != Private_)) goto next_163;
    goto match_body_162;
next_163:;
    if ((token_11.tag != Internal_)) goto next_164;
    goto match_body_162;
next_164:;
    if ((token_11.tag != Public_)) goto next_165;
    goto match_body_162;
match_body_162:;
    match_45 = 1;
    goto end_match_161;
next_165:;
    match_45 = 0;
    goto end_match_161;
next_166:;
end_match_161:;
    return match_45;
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
    struct OpLevel_ match_46;
    if ((level_.tag != Or_)) goto next_168;
    match_46 = (struct OpLevel_){.tag = And_};
    goto end_match_167;
next_168:;
    if ((level_.tag != And_)) goto next_169;
    match_46 = (struct OpLevel_){.tag = Cmp_};
    goto end_match_167;
next_169:;
    if ((level_.tag != Cmp_)) goto next_170;
    match_46 = (struct OpLevel_){.tag = Pipe_1};
    goto end_match_167;
next_170:;
    if ((level_.tag != Pipe_1)) goto next_171;
    match_46 = (struct OpLevel_){.tag = Cons_};
    goto end_match_167;
next_171:;
    if ((level_.tag != Cons_)) goto next_172;
    match_46 = (struct OpLevel_){.tag = Add_};
    goto end_match_167;
next_172:;
    if ((level_.tag != Add_)) goto next_174;
    match_46 = (struct OpLevel_){.tag = Mul_};
    goto end_match_167;
next_174:;
    if ((level_.tag != Mul_)) goto next_175;
    goto match_body_173;
next_175:;
    if ((level_.tag != Prefix_)) goto next_176;
    goto match_body_173;
match_body_173:;
    match_46 = (struct OpLevel_){.tag = Prefix_};
    goto end_match_167;
next_176:;
end_match_167:;
    return match_46;
}

struct IntIntTuple2 go_(int r_, struct String text_, int y_1, int x_2, int i_) {
    struct IntIntTuple2 match_47;
    if ((i_ != r_)) goto next_178;
    struct IntIntTuple2 tuple_18;
    tuple_18.t0 = y_1;
    tuple_18.t1 = x_2;
    match_47 = tuple_18;
    goto end_match_177;
next_178:;
    if ((i_ == r_)) goto next_179;
    struct IntIntTuple2 match_48;
    if ((text_.str[i_] != '\n')) goto next_181;
    struct IntIntTuple2 call_108 = go_(r_, text_, (y_1 + 1), 0, (i_ + 1));
    match_48 = call_108;
    goto end_match_180;
next_181:;
    if ((text_.str[i_] == '\n')) goto next_182;
    struct IntIntTuple2 call_109 = go_(r_, text_, y_1, (x_2 + 1), (i_ + 1));
    match_48 = call_109;
    goto end_match_180;
next_182:;
    exit(1);
end_match_180:;
    match_47 = match_48;
    goto end_match_177;
next_179:;
    exit(1);
end_match_177:;
    return match_47;
}

struct IntIntTuple2 locShift_(struct String text_, int l_, int r_, struct IntIntTuple2 arg_23) {
    int y_ = arg_23.t0;
    int x_1 = arg_23.t1;
    int match_49;
    int match_50;
    if ((l_ < 0)) goto next_185;
    match_50 = (r_ >= l_);
    goto end_match_184;
next_185:;
    if ((l_ >= 0)) goto next_186;
    match_50 = 0;
    goto end_match_184;
next_186:;
    exit(1);
end_match_184:;
    if ((!(match_50))) goto next_187;
    match_49 = (text_.len >= r_);
    goto end_match_183;
next_187:;
    if (match_50) goto next_188;
    match_49 = 0;
    goto end_match_183;
next_188:;
    exit(1);
end_match_183:;
    milone_assert(match_49, 40, 2);
    int call_110 = 0;
    struct IntIntTuple2 call_111 = go_(r_, text_, y_, x_1, l_);
    return call_111;
}

int charIsSpace_(char c_) {
    int match_51;
    int match_52;
    int match_53;
    if ((c_ != ' ')) goto next_192;
    match_53 = 1;
    goto end_match_191;
next_192:;
    if ((c_ == ' ')) goto next_193;
    match_53 = (c_ == '\t');
    goto end_match_191;
next_193:;
    exit(1);
end_match_191:;
    if ((!(match_53))) goto next_194;
    match_52 = 1;
    goto end_match_190;
next_194:;
    if (match_53) goto next_195;
    match_52 = (c_ == '\r');
    goto end_match_190;
next_195:;
    exit(1);
end_match_190:;
    if ((!(match_52))) goto next_196;
    match_51 = 1;
    goto end_match_189;
next_196:;
    if (match_52) goto next_197;
    match_51 = (c_ == '\n');
    goto end_match_189;
next_197:;
    exit(1);
end_match_189:;
    return match_51;
}

int charIsDigit_(char c_1) {
    int match_54;
    if ((c_1 < '0')) goto next_199;
    match_54 = ('9' >= c_1);
    goto end_match_198;
next_199:;
    if ((c_1 >= '0')) goto next_200;
    match_54 = 0;
    goto end_match_198;
next_200:;
    exit(1);
end_match_198:;
    return match_54;
}

int charIsAlpha_(char c_2) {
    int match_55;
    int match_56;
    if ((c_2 < 'a')) goto next_203;
    match_56 = ('z' >= c_2);
    goto end_match_202;
next_203:;
    if ((c_2 >= 'a')) goto next_204;
    match_56 = 0;
    goto end_match_202;
next_204:;
    exit(1);
end_match_202:;
    if ((!(match_56))) goto next_205;
    match_55 = 1;
    goto end_match_201;
next_205:;
    if (match_56) goto next_206;
    int match_57;
    if ((c_2 < 'A')) goto next_208;
    match_57 = ('Z' >= c_2);
    goto end_match_207;
next_208:;
    if ((c_2 >= 'A')) goto next_209;
    match_57 = 0;
    goto end_match_207;
next_209:;
    exit(1);
end_match_207:;
    match_55 = match_57;
    goto end_match_201;
next_206:;
    exit(1);
end_match_201:;
    return match_55;
}

int charIsIdent_(char c_3) {
    int match_58;
    int match_59;
    if ((c_3 != '_')) goto next_212;
    match_59 = 1;
    goto end_match_211;
next_212:;
    if ((c_3 == '_')) goto next_213;
    int call_112 = charIsDigit_(c_3);
    match_59 = call_112;
    goto end_match_211;
next_213:;
    exit(1);
end_match_211:;
    if ((!(match_59))) goto next_214;
    match_58 = 1;
    goto end_match_210;
next_214:;
    if (match_59) goto next_215;
    int call_113 = charIsAlpha_(c_3);
    match_58 = call_113;
    goto end_match_210;
next_215:;
    exit(1);
end_match_210:;
    return match_58;
}

int charIsOp_(char c_4) {
    int match_60;
    int match_61;
    int match_62;
    int match_63;
    int match_64;
    int match_65;
    int match_66;
    int match_67;
    int match_68;
    int match_69;
    int match_70;
    int match_71;
    int match_72;
    int match_73;
    if ((c_4 != '+')) goto next_230;
    match_73 = 1;
    goto end_match_229;
next_230:;
    if ((c_4 == '+')) goto next_231;
    match_73 = (c_4 == '-');
    goto end_match_229;
next_231:;
    exit(1);
end_match_229:;
    if ((!(match_73))) goto next_232;
    match_72 = 1;
    goto end_match_228;
next_232:;
    if (match_73) goto next_233;
    match_72 = (c_4 == '*');
    goto end_match_228;
next_233:;
    exit(1);
end_match_228:;
    if ((!(match_72))) goto next_234;
    match_71 = 1;
    goto end_match_227;
next_234:;
    if (match_72) goto next_235;
    match_71 = (c_4 == '/');
    goto end_match_227;
next_235:;
    exit(1);
end_match_227:;
    if ((!(match_71))) goto next_236;
    match_70 = 1;
    goto end_match_226;
next_236:;
    if (match_71) goto next_237;
    match_70 = (c_4 == '%');
    goto end_match_226;
next_237:;
    exit(1);
end_match_226:;
    if ((!(match_70))) goto next_238;
    match_69 = 1;
    goto end_match_225;
next_238:;
    if (match_70) goto next_239;
    match_69 = (c_4 == '=');
    goto end_match_225;
next_239:;
    exit(1);
end_match_225:;
    if ((!(match_69))) goto next_240;
    match_68 = 1;
    goto end_match_224;
next_240:;
    if (match_69) goto next_241;
    match_68 = (c_4 == '<');
    goto end_match_224;
next_241:;
    exit(1);
end_match_224:;
    if ((!(match_68))) goto next_242;
    match_67 = 1;
    goto end_match_223;
next_242:;
    if (match_68) goto next_243;
    match_67 = (c_4 == '>');
    goto end_match_223;
next_243:;
    exit(1);
end_match_223:;
    if ((!(match_67))) goto next_244;
    match_66 = 1;
    goto end_match_222;
next_244:;
    if (match_67) goto next_245;
    match_66 = (c_4 == '^');
    goto end_match_222;
next_245:;
    exit(1);
end_match_222:;
    if ((!(match_66))) goto next_246;
    match_65 = 1;
    goto end_match_221;
next_246:;
    if (match_66) goto next_247;
    match_65 = (c_4 == '&');
    goto end_match_221;
next_247:;
    exit(1);
end_match_221:;
    if ((!(match_65))) goto next_248;
    match_64 = 1;
    goto end_match_220;
next_248:;
    if (match_65) goto next_249;
    match_64 = (c_4 == '|');
    goto end_match_220;
next_249:;
    exit(1);
end_match_220:;
    if ((!(match_64))) goto next_250;
    match_63 = 1;
    goto end_match_219;
next_250:;
    if (match_64) goto next_251;
    match_63 = (c_4 == ':');
    goto end_match_219;
next_251:;
    exit(1);
end_match_219:;
    if ((!(match_63))) goto next_252;
    match_62 = 1;
    goto end_match_218;
next_252:;
    if (match_63) goto next_253;
    match_62 = (c_4 == '@');
    goto end_match_218;
next_253:;
    exit(1);
end_match_218:;
    if ((!(match_62))) goto next_254;
    match_61 = 1;
    goto end_match_217;
next_254:;
    if (match_62) goto next_255;
    match_61 = (c_4 == ';');
    goto end_match_217;
next_255:;
    exit(1);
end_match_217:;
    if ((!(match_61))) goto next_256;
    match_60 = 1;
    goto end_match_216;
next_256:;
    if (match_61) goto next_257;
    match_60 = (c_4 == '.');
    goto end_match_216;
next_257:;
    exit(1);
end_match_216:;
    return match_60;
}

int charIsPun_(char c_5) {
    int match_74;
    int match_75;
    int match_76;
    int match_77;
    if ((c_5 != ',')) goto next_262;
    match_77 = 1;
    goto end_match_261;
next_262:;
    if ((c_5 == ',')) goto next_263;
    match_77 = (c_5 == '(');
    goto end_match_261;
next_263:;
    exit(1);
end_match_261:;
    if ((!(match_77))) goto next_264;
    match_76 = 1;
    goto end_match_260;
next_264:;
    if (match_77) goto next_265;
    match_76 = (c_5 == ')');
    goto end_match_260;
next_265:;
    exit(1);
end_match_260:;
    if ((!(match_76))) goto next_266;
    match_75 = 1;
    goto end_match_259;
next_266:;
    if (match_76) goto next_267;
    match_75 = (c_5 == '[');
    goto end_match_259;
next_267:;
    exit(1);
end_match_259:;
    if ((!(match_75))) goto next_268;
    match_74 = 1;
    goto end_match_258;
next_268:;
    if (match_75) goto next_269;
    match_74 = (c_5 == ']');
    goto end_match_258;
next_269:;
    exit(1);
end_match_258:;
    return match_74;
}

int go_1(struct String s_, struct String prefix_, int pi_, int si_) {
    int match_78;
    if ((pi_ != prefix_.len)) goto next_271;
    match_78 = 1;
    goto end_match_270;
next_271:;
    if ((pi_ == prefix_.len)) goto next_272;
    int match_79;
    int match_80;
    if ((si_ >= s_.len)) goto next_275;
    match_80 = (prefix_.str[pi_] == s_.str[si_]);
    goto end_match_274;
next_275:;
    if ((si_ < s_.len)) goto next_276;
    match_80 = 0;
    goto end_match_274;
next_276:;
    exit(1);
end_match_274:;
    if ((!(match_80))) goto next_277;
    int call_114 = go_1(s_, prefix_, (pi_ + 1), (si_ + 1));
    match_79 = call_114;
    goto end_match_273;
next_277:;
    if (match_80) goto next_278;
    match_79 = 0;
    goto end_match_273;
next_278:;
    exit(1);
end_match_273:;
    match_78 = match_79;
    goto end_match_270;
next_272:;
    exit(1);
end_match_270:;
    return match_78;
}

int strIsFollowedBy_(int i_1, struct String prefix_, struct String s_) {
    int match_81;
    if ((s_.len < (i_1 + prefix_.len))) goto next_280;
    int call_115 = go_1(s_, prefix_, 0, i_1);
    match_81 = call_115;
    goto end_match_279;
next_280:;
    if ((s_.len >= (i_1 + prefix_.len))) goto next_281;
    match_81 = 0;
    goto end_match_279;
next_281:;
    exit(1);
end_match_279:;
    return match_81;
}

int strIsFollowedByRawQuotes_(int i_2, struct String s_1) {
    int call_116 = strIsFollowedBy_(i_2, (struct String){.str = "\"\"\"", .len = 3}, s_1);
    return call_116;
}

int scanError_(struct String arg_24, int i_3) {
    return (i_3 + 1);
}

int lookEof_(struct String text_1, int i_4) {
    return (i_4 >= text_1.len);
}

int lookSpace_(struct String text_2, int i_5) {
    int call_117 = charIsSpace_(text_2.str[i_5]);
    return call_117;
}

int go_2(struct String text_3, int i_7) {
    int match_82;
    int match_83;
    if ((i_7 >= text_3.len)) goto next_284;
    int call_118 = charIsSpace_(text_3.str[i_7]);
    match_83 = call_118;
    goto end_match_283;
next_284:;
    if ((i_7 < text_3.len)) goto next_285;
    match_83 = 0;
    goto end_match_283;
next_285:;
    exit(1);
end_match_283:;
    if ((!(match_83))) goto next_286;
    int call_119 = go_2(text_3, (i_7 + 1));
    match_82 = call_119;
    goto end_match_282;
next_286:;
    if (match_83) goto next_287;
    match_82 = i_7;
    goto end_match_282;
next_287:;
    exit(1);
end_match_282:;
    return match_82;
}

int scanSpace_(struct String text_3, int i_6) {
    int call_120 = lookSpace_(text_3, i_6);
    milone_assert(call_120, 112, 2);
    int call_121 = 0;
    int call_122 = go_2(text_3, i_6);
    return call_122;
}

int lookComment_(struct String text_4, int i_8) {
    int match_84;
    int call_123 = strIsFollowedBy_(i_8, (struct String){.str = "//", .len = 2}, text_4);
    if ((!(call_123))) goto next_289;
    match_84 = 1;
    goto end_match_288;
next_289:;
    if (call_123) goto next_290;
    int call_124 = strIsFollowedBy_(i_8, (struct String){.str = "[<", .len = 2}, text_4);
    match_84 = call_124;
    goto end_match_288;
next_290:;
    exit(1);
end_match_288:;
    return match_84;
}

int go_3(struct String text_5, int i_10) {
    int match_85;
    if ((i_10 != text_5.len)) goto next_292;
    match_85 = i_10;
    goto end_match_291;
next_292:;
    if ((i_10 == text_5.len)) goto next_293;
    int match_86;
    if ((text_5.str[i_10] != '\n')) goto next_295;
    match_86 = (i_10 + 1);
    goto end_match_294;
next_295:;
    if ((text_5.str[i_10] == '\n')) goto next_296;
    int call_125 = go_3(text_5, (i_10 + 1));
    match_86 = call_125;
    goto end_match_294;
next_296:;
    exit(1);
end_match_294:;
    match_85 = match_86;
    goto end_match_291;
next_293:;
    exit(1);
end_match_291:;
    return match_85;
}

int scanLine_(struct String text_5, int i_9) {
    int call_126 = lookComment_(text_5, i_9);
    milone_assert(call_126, 126, 2);
    int call_127 = 0;
    int call_128 = go_3(text_5, i_9);
    return call_128;
}

int lookPun_(struct String text_6, int i_11) {
    int call_129 = charIsPun_(text_6.str[i_11]);
    return call_129;
}

int scanPun_(struct String text_7, int i_12) {
    int call_130 = lookPun_(text_7, i_12);
    milone_assert(call_130, 140, 2);
    int call_131 = 0;
    return (i_12 + 1);
}

int lookOp_(struct String text_8, int i_13) {
    int call_132 = charIsOp_(text_8.str[i_13]);
    return call_132;
}

int go_4(struct String text_9, int i_15) {
    int match_87;
    int match_88;
    if ((i_15 >= text_9.len)) goto next_299;
    int call_133 = charIsOp_(text_9.str[i_15]);
    match_88 = call_133;
    goto end_match_298;
next_299:;
    if ((i_15 < text_9.len)) goto next_300;
    match_88 = 0;
    goto end_match_298;
next_300:;
    exit(1);
end_match_298:;
    if ((!(match_88))) goto next_301;
    int call_134 = go_4(text_9, (i_15 + 1));
    match_87 = call_134;
    goto end_match_297;
next_301:;
    if (match_88) goto next_302;
    match_87 = i_15;
    goto end_match_297;
next_302:;
    exit(1);
end_match_297:;
    return match_87;
}

int scanOp_(struct String text_9, int i_14) {
    int call_135 = lookOp_(text_9, i_14);
    milone_assert(call_135, 147, 2);
    int call_136 = 0;
    int call_137 = go_4(text_9, i_14);
    return call_137;
}

int lookIdent_(struct String text_10, int i_16) {
    int match_89;
    int call_138 = charIsIdent_(text_10.str[i_16]);
    if ((!(call_138))) goto next_304;
    int call_139 = charIsDigit_(text_10.str[i_16]);
    match_89 = (!(call_139));
    goto end_match_303;
next_304:;
    if (call_138) goto next_305;
    match_89 = 0;
    goto end_match_303;
next_305:;
    exit(1);
end_match_303:;
    return match_89;
}

int go_5(struct String text_11, int i_18) {
    int match_90;
    int match_91;
    if ((i_18 >= text_11.len)) goto next_308;
    int call_140 = charIsIdent_(text_11.str[i_18]);
    match_91 = call_140;
    goto end_match_307;
next_308:;
    if ((i_18 < text_11.len)) goto next_309;
    match_91 = 0;
    goto end_match_307;
next_309:;
    exit(1);
end_match_307:;
    if ((!(match_91))) goto next_310;
    int call_141 = go_5(text_11, (i_18 + 1));
    match_90 = call_141;
    goto end_match_306;
next_310:;
    if (match_91) goto next_311;
    match_90 = i_18;
    goto end_match_306;
next_311:;
    exit(1);
end_match_306:;
    return match_90;
}

int scanIdent_(struct String text_11, int i_17) {
    int call_142 = lookIdent_(text_11, i_17);
    milone_assert(call_142, 160, 2);
    int call_143 = 0;
    int call_144 = go_5(text_11, i_17);
    return call_144;
}

int lookIntLit_(struct String text_12, int i_19) {
    int call_145 = charIsDigit_(text_12.str[i_19]);
    return call_145;
}

int go_6(struct String text_13, int i_21) {
    int match_92;
    int match_93;
    if ((i_21 >= text_13.len)) goto next_314;
    int call_146 = charIsDigit_(text_13.str[i_21]);
    match_93 = call_146;
    goto end_match_313;
next_314:;
    if ((i_21 < text_13.len)) goto next_315;
    match_93 = 0;
    goto end_match_313;
next_315:;
    exit(1);
end_match_313:;
    if ((!(match_93))) goto next_316;
    int call_147 = go_6(text_13, (i_21 + 1));
    match_92 = call_147;
    goto end_match_312;
next_316:;
    if (match_93) goto next_317;
    match_92 = i_21;
    goto end_match_312;
next_317:;
    exit(1);
end_match_312:;
    return match_92;
}

int scanIntLit_(struct String text_13, int i_20) {
    int call_148 = lookIntLit_(text_13, i_20);
    milone_assert(call_148, 172, 2);
    int call_149 = 0;
    int call_150 = go_6(text_13, i_20);
    return call_150;
}

int lookCharLit_(struct String text_14, int i_22) {
    return (text_14.str[i_22] == '\'');
}

struct BoolIntTuple2 {
    int t0;
    int t1;
};

struct BoolIntTuple2 go_7(struct String text_15, int i_24) {
    struct BoolIntTuple2 match_94;
    int match_95;
    if (((i_24 + 1) >= text_15.len)) goto next_320;
    match_95 = (text_15.str[i_24] == '\\');
    goto end_match_319;
next_320:;
    if (((i_24 + 1) < text_15.len)) goto next_321;
    match_95 = 0;
    goto end_match_319;
next_321:;
    exit(1);
end_match_319:;
    if ((!(match_95))) goto next_322;
    struct BoolIntTuple2 call_151 = go_7(text_15, (i_24 + 2));
    match_94 = call_151;
    goto end_match_318;
next_322:;
    if (match_95) goto next_323;
    struct BoolIntTuple2 match_96;
    int match_97;
    if ((i_24 >= text_15.len)) goto next_326;
    match_97 = (text_15.str[i_24] == '\'');
    goto end_match_325;
next_326:;
    if ((i_24 < text_15.len)) goto next_327;
    match_97 = 0;
    goto end_match_325;
next_327:;
    exit(1);
end_match_325:;
    if ((!(match_97))) goto next_328;
    struct BoolIntTuple2 tuple_19;
    tuple_19.t0 = 1;
    tuple_19.t1 = (i_24 + 1);
    match_96 = tuple_19;
    goto end_match_324;
next_328:;
    if (match_97) goto next_329;
    struct BoolIntTuple2 match_98;
    int match_99;
    if ((i_24 >= text_15.len)) goto next_332;
    match_99 = (text_15.str[i_24] != '\n');
    goto end_match_331;
next_332:;
    if ((i_24 < text_15.len)) goto next_333;
    match_99 = 0;
    goto end_match_331;
next_333:;
    exit(1);
end_match_331:;
    if ((!(match_99))) goto next_334;
    struct BoolIntTuple2 call_152 = go_7(text_15, (i_24 + 1));
    match_98 = call_152;
    goto end_match_330;
next_334:;
    if (match_99) goto next_335;
    int match_100;
    if ((i_24 != text_15.len)) goto next_337;
    match_100 = 1;
    goto end_match_336;
next_337:;
    if ((i_24 == text_15.len)) goto next_338;
    match_100 = (text_15.str[i_24] == '\n');
    goto end_match_336;
next_338:;
    exit(1);
end_match_336:;
    milone_assert(match_100, 197, 6);
    int call_153 = 0;
    struct BoolIntTuple2 tuple_20;
    tuple_20.t0 = 0;
    tuple_20.t1 = i_24;
    match_98 = tuple_20;
    goto end_match_330;
next_335:;
    exit(1);
end_match_330:;
    match_96 = match_98;
    goto end_match_324;
next_329:;
    exit(1);
end_match_324:;
    match_94 = match_96;
    goto end_match_318;
next_323:;
    exit(1);
end_match_318:;
    return match_94;
}

struct BoolIntTuple2 scanCharLit_(struct String text_15, int i_23) {
    int call_154 = lookCharLit_(text_15, i_23);
    milone_assert(call_154, 184, 2);
    int call_155 = 0;
    struct BoolIntTuple2 call_156 = go_7(text_15, (i_23 + 1));
    return call_156;
}

int lookStrLit_(struct String text_16, int i_25) {
    return (text_16.str[i_25] == '"');
}

struct BoolIntTuple2 go_8(struct String text_17, int i_27) {
    struct BoolIntTuple2 match_101;
    int match_102;
    if (((i_27 + 1) >= text_17.len)) goto next_341;
    match_102 = (text_17.str[i_27] == '\\');
    goto end_match_340;
next_341:;
    if (((i_27 + 1) < text_17.len)) goto next_342;
    match_102 = 0;
    goto end_match_340;
next_342:;
    exit(1);
end_match_340:;
    if ((!(match_102))) goto next_343;
    struct BoolIntTuple2 call_157 = go_8(text_17, (i_27 + 2));
    match_101 = call_157;
    goto end_match_339;
next_343:;
    if (match_102) goto next_344;
    struct BoolIntTuple2 match_103;
    int match_104;
    if ((i_27 >= text_17.len)) goto next_347;
    match_104 = (text_17.str[i_27] == '"');
    goto end_match_346;
next_347:;
    if ((i_27 < text_17.len)) goto next_348;
    match_104 = 0;
    goto end_match_346;
next_348:;
    exit(1);
end_match_346:;
    if ((!(match_104))) goto next_349;
    struct BoolIntTuple2 tuple_21;
    tuple_21.t0 = 1;
    tuple_21.t1 = (i_27 + 1);
    match_103 = tuple_21;
    goto end_match_345;
next_349:;
    if (match_104) goto next_350;
    struct BoolIntTuple2 match_105;
    int match_106;
    if ((i_27 >= text_17.len)) goto next_353;
    match_106 = (text_17.str[i_27] != '\n');
    goto end_match_352;
next_353:;
    if ((i_27 < text_17.len)) goto next_354;
    match_106 = 0;
    goto end_match_352;
next_354:;
    exit(1);
end_match_352:;
    if ((!(match_106))) goto next_355;
    struct BoolIntTuple2 call_158 = go_8(text_17, (i_27 + 1));
    match_105 = call_158;
    goto end_match_351;
next_355:;
    if (match_106) goto next_356;
    int match_107;
    if ((i_27 != text_17.len)) goto next_358;
    match_107 = 1;
    goto end_match_357;
next_358:;
    if ((i_27 == text_17.len)) goto next_359;
    match_107 = (text_17.str[i_27] == '\n');
    goto end_match_357;
next_359:;
    exit(1);
end_match_357:;
    milone_assert(match_107, 218, 6);
    int call_159 = 0;
    struct BoolIntTuple2 tuple_22;
    tuple_22.t0 = 0;
    tuple_22.t1 = i_27;
    match_105 = tuple_22;
    goto end_match_351;
next_356:;
    exit(1);
end_match_351:;
    match_103 = match_105;
    goto end_match_345;
next_350:;
    exit(1);
end_match_345:;
    match_101 = match_103;
    goto end_match_339;
next_344:;
    exit(1);
end_match_339:;
    return match_101;
}

struct BoolIntTuple2 scanStrLit_(struct String text_17, int i_26) {
    int call_160 = lookStrLit_(text_17, i_26);
    milone_assert(call_160, 205, 2);
    int call_161 = 0;
    struct BoolIntTuple2 call_162 = go_8(text_17, (i_26 + 1));
    return call_162;
}

int lookStrLitRaw_(struct String text_18, int i_28) {
    int call_163 = strIsFollowedByRawQuotes_(i_28, text_18);
    return call_163;
}

struct BoolIntTuple2 go_9(struct String text_19, int i_30) {
    struct BoolIntTuple2 match_108;
    int call_164 = strIsFollowedByRawQuotes_(i_30, text_19);
    if ((!(call_164))) goto next_361;
    struct BoolIntTuple2 tuple_23;
    tuple_23.t0 = 1;
    tuple_23.t1 = (i_30 + 3);
    match_108 = tuple_23;
    goto end_match_360;
next_361:;
    if (call_164) goto next_362;
    struct BoolIntTuple2 match_109;
    if (((i_30 + 1) >= text_19.len)) goto next_364;
    struct BoolIntTuple2 call_165 = go_9(text_19, (i_30 + 1));
    match_109 = call_165;
    goto end_match_363;
next_364:;
    if (((i_30 + 1) < text_19.len)) goto next_365;
    milone_assert((i_30 == text_19.len), 233, 6);
    int call_166 = 0;
    struct BoolIntTuple2 tuple_24;
    tuple_24.t0 = 0;
    tuple_24.t1 = i_30;
    match_109 = tuple_24;
    goto end_match_363;
next_365:;
    exit(1);
end_match_363:;
    match_108 = match_109;
    goto end_match_360;
next_362:;
    exit(1);
end_match_360:;
    return match_108;
}

struct BoolIntTuple2 scanStrLitRaw_(struct String text_19, int i_29) {
    int call_167 = lookStrLitRaw_(text_19, i_29);
    milone_assert(call_167, 226, 2);
    int call_168 = 0;
    struct BoolIntTuple2 call_169 = go_9(text_19, (i_29 + 3));
    return call_169;
}

struct Token_ tokenFromIdent_(struct String text_20, int l_1, int r_1) {
    struct Token_ match_110;
    struct String call_170 = strSlice_(l_1, r_1, text_20);
    if ((str_cmp(call_170, (struct String){.str = "true", .len = 4}) != 0)) goto next_367;
    int* payload_3 = (int*)malloc(sizeof(int));
    (*(((int*)payload_3))) = 1;
    struct Token_ variant_3 = (struct Token_){.tag = Bool_1, .Bool_1 = payload_3};
    match_110 = variant_3;
    goto end_match_366;
next_367:;
    if ((str_cmp(call_170, (struct String){.str = "false", .len = 5}) != 0)) goto next_368;
    int* payload_4 = (int*)malloc(sizeof(int));
    (*(((int*)payload_4))) = 0;
    struct Token_ variant_4 = (struct Token_){.tag = Bool_1, .Bool_1 = payload_4};
    match_110 = variant_4;
    goto end_match_366;
next_368:;
    if ((str_cmp(call_170, (struct String){.str = "do", .len = 2}) != 0)) goto next_369;
    match_110 = (struct Token_){.tag = Do_};
    goto end_match_366;
next_369:;
    if ((str_cmp(call_170, (struct String){.str = "let", .len = 3}) != 0)) goto next_370;
    match_110 = (struct Token_){.tag = Let_};
    goto end_match_366;
next_370:;
    if ((str_cmp(call_170, (struct String){.str = "if", .len = 2}) != 0)) goto next_371;
    match_110 = (struct Token_){.tag = If_};
    goto end_match_366;
next_371:;
    if ((str_cmp(call_170, (struct String){.str = "then", .len = 4}) != 0)) goto next_372;
    match_110 = (struct Token_){.tag = Then_};
    goto end_match_366;
next_372:;
    if ((str_cmp(call_170, (struct String){.str = "else", .len = 4}) != 0)) goto next_373;
    match_110 = (struct Token_){.tag = Else_};
    goto end_match_366;
next_373:;
    if ((str_cmp(call_170, (struct String){.str = "match", .len = 5}) != 0)) goto next_374;
    match_110 = (struct Token_){.tag = Match_};
    goto end_match_366;
next_374:;
    if ((str_cmp(call_170, (struct String){.str = "with", .len = 4}) != 0)) goto next_375;
    match_110 = (struct Token_){.tag = With_};
    goto end_match_366;
next_375:;
    if ((str_cmp(call_170, (struct String){.str = "as", .len = 2}) != 0)) goto next_376;
    match_110 = (struct Token_){.tag = As_};
    goto end_match_366;
next_376:;
    if ((str_cmp(call_170, (struct String){.str = "when", .len = 4}) != 0)) goto next_377;
    match_110 = (struct Token_){.tag = When_};
    goto end_match_366;
next_377:;
    if ((str_cmp(call_170, (struct String){.str = "rec", .len = 3}) != 0)) goto next_378;
    match_110 = (struct Token_){.tag = Rec_};
    goto end_match_366;
next_378:;
    if ((str_cmp(call_170, (struct String){.str = "private", .len = 7}) != 0)) goto next_379;
    match_110 = (struct Token_){.tag = Private_};
    goto end_match_366;
next_379:;
    if ((str_cmp(call_170, (struct String){.str = "internal", .len = 8}) != 0)) goto next_380;
    match_110 = (struct Token_){.tag = Internal_};
    goto end_match_366;
next_380:;
    if ((str_cmp(call_170, (struct String){.str = "public", .len = 6}) != 0)) goto next_381;
    match_110 = (struct Token_){.tag = Public_};
    goto end_match_366;
next_381:;
    if ((str_cmp(call_170, (struct String){.str = "module", .len = 6}) != 0)) goto next_382;
    match_110 = (struct Token_){.tag = Module_};
    goto end_match_366;
next_382:;
    if ((str_cmp(call_170, (struct String){.str = "namespace", .len = 9}) != 0)) goto next_383;
    match_110 = (struct Token_){.tag = Namespace_};
    goto end_match_366;
next_383:;
    if ((str_cmp(call_170, (struct String){.str = "open", .len = 4}) != 0)) goto next_384;
    match_110 = (struct Token_){.tag = Open_};
    goto end_match_366;
next_384:;
    if ((str_cmp(call_170, (struct String){.str = "type", .len = 4}) != 0)) goto next_385;
    match_110 = (struct Token_){.tag = Type_};
    goto end_match_366;
next_385:;
    if ((str_cmp(call_170, (struct String){.str = "of", .len = 2}) != 0)) goto next_386;
    match_110 = (struct Token_){.tag = Of_};
    goto end_match_366;
next_386:;
    if ((str_cmp(call_170, (struct String){.str = "fun", .len = 3}) != 0)) goto next_387;
    match_110 = (struct Token_){.tag = Fun_};
    goto end_match_366;
next_387:;
    if ((str_cmp(call_170, (struct String){.str = "in", .len = 2}) != 0)) goto next_388;
    match_110 = (struct Token_){.tag = In_};
    goto end_match_366;
next_388:;
    struct String s_2 = call_170;
    struct String* payload_5 = (struct String*)malloc(sizeof(struct String));
    (*(((struct String*)payload_5))) = s_2;
    struct Token_ variant_5 = (struct Token_){.tag = Ident_, .Ident_ = payload_5};
    match_110 = variant_5;
    goto end_match_366;
next_389:;
end_match_366:;
    return match_110;
}

struct Token_ tokenFromOp_(struct String text_21, int l_2, int r_2) {
    struct Token_ match_111;
    struct String call_171 = strSlice_(l_2, r_2, text_21);
    if ((str_cmp(call_171, (struct String){.str = "&", .len = 1}) != 0)) goto next_391;
    match_111 = (struct Token_){.tag = Amp_};
    goto end_match_390;
next_391:;
    if ((str_cmp(call_171, (struct String){.str = "&&", .len = 2}) != 0)) goto next_392;
    match_111 = (struct Token_){.tag = AmpAmp_};
    goto end_match_390;
next_392:;
    if ((str_cmp(call_171, (struct String){.str = "->", .len = 2}) != 0)) goto next_393;
    match_111 = (struct Token_){.tag = Arrow_};
    goto end_match_390;
next_393:;
    if ((str_cmp(call_171, (struct String){.str = ":", .len = 1}) != 0)) goto next_394;
    match_111 = (struct Token_){.tag = Colon_};
    goto end_match_390;
next_394:;
    if ((str_cmp(call_171, (struct String){.str = "::", .len = 2}) != 0)) goto next_395;
    match_111 = (struct Token_){.tag = ColonColon_};
    goto end_match_390;
next_395:;
    if ((str_cmp(call_171, (struct String){.str = ".", .len = 1}) != 0)) goto next_396;
    match_111 = (struct Token_){.tag = Dot_};
    goto end_match_390;
next_396:;
    if ((str_cmp(call_171, (struct String){.str = "..", .len = 2}) != 0)) goto next_397;
    match_111 = (struct Token_){.tag = DotDot_};
    goto end_match_390;
next_397:;
    if ((str_cmp(call_171, (struct String){.str = "=", .len = 1}) != 0)) goto next_398;
    match_111 = (struct Token_){.tag = Eq_};
    goto end_match_390;
next_398:;
    if ((str_cmp(call_171, (struct String){.str = ">", .len = 1}) != 0)) goto next_399;
    match_111 = (struct Token_){.tag = Gt_};
    goto end_match_390;
next_399:;
    if ((str_cmp(call_171, (struct String){.str = ">=", .len = 2}) != 0)) goto next_400;
    match_111 = (struct Token_){.tag = GtEq_};
    goto end_match_390;
next_400:;
    if ((str_cmp(call_171, (struct String){.str = "<", .len = 1}) != 0)) goto next_401;
    match_111 = (struct Token_){.tag = Lt_};
    goto end_match_390;
next_401:;
    if ((str_cmp(call_171, (struct String){.str = "<=", .len = 2}) != 0)) goto next_402;
    match_111 = (struct Token_){.tag = LtEq_};
    goto end_match_390;
next_402:;
    if ((str_cmp(call_171, (struct String){.str = "<>", .len = 2}) != 0)) goto next_403;
    match_111 = (struct Token_){.tag = LtGt_};
    goto end_match_390;
next_403:;
    if ((str_cmp(call_171, (struct String){.str = "-", .len = 1}) != 0)) goto next_404;
    match_111 = (struct Token_){.tag = Minus_};
    goto end_match_390;
next_404:;
    if ((str_cmp(call_171, (struct String){.str = "%", .len = 1}) != 0)) goto next_405;
    match_111 = (struct Token_){.tag = Percent_};
    goto end_match_390;
next_405:;
    if ((str_cmp(call_171, (struct String){.str = "|", .len = 1}) != 0)) goto next_406;
    match_111 = (struct Token_){.tag = Pipe_};
    goto end_match_390;
next_406:;
    if ((str_cmp(call_171, (struct String){.str = "|>", .len = 2}) != 0)) goto next_407;
    match_111 = (struct Token_){.tag = PipeGt_};
    goto end_match_390;
next_407:;
    if ((str_cmp(call_171, (struct String){.str = "||", .len = 2}) != 0)) goto next_408;
    match_111 = (struct Token_){.tag = PipePipe_};
    goto end_match_390;
next_408:;
    if ((str_cmp(call_171, (struct String){.str = "+", .len = 1}) != 0)) goto next_409;
    match_111 = (struct Token_){.tag = Plus_};
    goto end_match_390;
next_409:;
    if ((str_cmp(call_171, (struct String){.str = ";", .len = 1}) != 0)) goto next_410;
    match_111 = (struct Token_){.tag = Semi_};
    goto end_match_390;
next_410:;
    if ((str_cmp(call_171, (struct String){.str = "*", .len = 1}) != 0)) goto next_411;
    match_111 = (struct Token_){.tag = Star_};
    goto end_match_390;
next_411:;
    if ((str_cmp(call_171, (struct String){.str = "/", .len = 1}) != 0)) goto next_412;
    match_111 = (struct Token_){.tag = Slash_};
    goto end_match_390;
next_412:;
    match_111 = (struct Token_){.tag = Error_};
    goto end_match_390;
next_413:;
end_match_390:;
    return match_111;
}

struct Token_ tokenFromPun_(struct String text_22, int l_3, int r_3) {
    milone_assert(((r_3 - l_3) == 1), 340, 2);
    int call_172 = 0;
    struct Token_ match_112;
    if ((text_22.str[l_3] != ',')) goto next_415;
    match_112 = (struct Token_){.tag = Comma_};
    goto end_match_414;
next_415:;
    if ((text_22.str[l_3] != '(')) goto next_416;
    match_112 = (struct Token_){.tag = ParenL_};
    goto end_match_414;
next_416:;
    if ((text_22.str[l_3] != ')')) goto next_417;
    match_112 = (struct Token_){.tag = ParenR_};
    goto end_match_414;
next_417:;
    if ((text_22.str[l_3] != '[')) goto next_418;
    match_112 = (struct Token_){.tag = BracketL_};
    goto end_match_414;
next_418:;
    if ((text_22.str[l_3] != ']')) goto next_419;
    match_112 = (struct Token_){.tag = BracketR_};
    goto end_match_414;
next_419:;
    struct Token_ call_173 = failwith_1((struct String){.str = "NEVER! charIsPun is broken", .len = 26});
    match_112 = call_173;
    goto end_match_414;
next_420:;
end_match_414:;
    return match_112;
}

struct Token_ tokenFromIntLit_(struct String text_23, int l_4, int r_4) {
    struct String call_174 = strSlice_(l_4, r_4, text_23);
    int call_175 = str_to_int(call_174);
    int value_ = call_175;
    int* payload_6 = (int*)malloc(sizeof(int));
    (*(((int*)payload_6))) = value_;
    struct Token_ variant_6 = (struct Token_){.tag = Int_1, .Int_1 = payload_6};
    return variant_6;
}

struct Token_ tokenFromCharLit_(struct String text_24, int l_5, int r_5) {
    int match_113;
    int match_114;
    if ((r_5 < (l_5 + 2))) goto next_423;
    match_114 = (text_24.str[l_5] == '\'');
    goto end_match_422;
next_423:;
    if ((r_5 >= (l_5 + 2))) goto next_424;
    match_114 = 0;
    goto end_match_422;
next_424:;
    exit(1);
end_match_422:;
    if ((!(match_114))) goto next_425;
    match_113 = (text_24.str[(r_5 - 1)] == '\'');
    goto end_match_421;
next_425:;
    if (match_114) goto next_426;
    match_113 = 0;
    goto end_match_421;
next_426:;
    exit(1);
end_match_421:;
    milone_assert(match_113, 360, 2);
    int call_176 = 0;
    int i_31 = (l_5 + 1);
    char match_115;
    if ((text_24.str[i_31] != '\\')) goto next_428;
    char match_116;
    if ((text_24.str[(i_31 + 1)] != 'u')) goto next_431;
    char call_177 = ((char)0);
    match_116 = call_177;
    goto end_match_430;
next_431:;
    if ((text_24.str[(i_31 + 1)] != 't')) goto next_432;
    match_116 = '\t';
    goto end_match_430;
next_432:;
    if ((text_24.str[(i_31 + 1)] != 'r')) goto next_433;
    match_116 = '\r';
    goto end_match_430;
next_433:;
    if ((text_24.str[(i_31 + 1)] != 'n')) goto next_434;
    match_116 = '\n';
    goto end_match_430;
next_434:;
    char c_6 = text_24.str[(i_31 + 1)];
    match_116 = c_6;
    goto end_match_430;
next_435:;
end_match_430:;
    match_115 = match_116;
    goto end_match_427;
next_428:;
    char c_7 = text_24.str[i_31];
    match_115 = c_7;
    goto end_match_427;
next_429:;
end_match_427:;
    char value_1 = match_115;
    char* payload_7 = (char*)malloc(sizeof(char));
    (*(((char*)payload_7))) = value_1;
    struct Token_ variant_7 = (struct Token_){.tag = Char_1, .Char_1 = payload_7};
    return variant_7;
}

int next_(int r_6, struct String text_25, int i_33) {
    int match_117;
    int match_118;
    if ((i_33 != (r_6 - 1))) goto next_438;
    match_118 = 1;
    goto end_match_437;
next_438:;
    if ((i_33 == (r_6 - 1))) goto next_439;
    match_118 = (text_25.str[i_33] == '\\');
    goto end_match_437;
next_439:;
    exit(1);
end_match_437:;
    if ((!(match_118))) goto next_440;
    match_117 = i_33;
    goto end_match_436;
next_440:;
    if (match_118) goto next_441;
    int call_178 = next_(r_6, text_25, (i_33 + 1));
    match_117 = call_178;
    goto end_match_436;
next_441:;
    exit(1);
end_match_436:;
    return match_117;
}

struct String go_10(int r_6, struct String text_25, struct StringList* acc_, int i_32) {
    int call_179 = next_(r_6, text_25, i_32);
    int endIndex_ = call_179;
    struct String call_180 = strSlice_(i_32, endIndex_, text_25);
    struct StringList* list_17 = (struct StringList*)malloc(sizeof(struct StringList));
    list_17->head = call_180;
    list_17->tail = acc_;
    struct StringList* acc_1 = list_17;
    int i_34 = endIndex_;
    struct String match_119;
    if ((i_34 != (r_6 - 1))) goto next_443;
    struct StringList* call_181 = listRev_2(acc_1);
    struct String call_182 = strConcat_(call_181);
    match_119 = call_182;
    goto end_match_442;
next_443:;
    if ((i_34 == (r_6 - 1))) goto next_444;
    milone_assert((text_25.str[i_34] == '\\'), 403, 6);
    int call_183 = 0;
    struct String match_120;
    if ((text_25.str[(i_34 + 1)] != 'u')) goto next_446;
    struct StringList* list_18 = (struct StringList*)malloc(sizeof(struct StringList));
    list_18->head = (struct String){.str = "\0", .len = 1};
    list_18->tail = acc_1;
    struct String call_184 = go_10(r_6, text_25, list_18, (i_34 + 6));
    match_120 = call_184;
    goto end_match_445;
next_446:;
    if ((text_25.str[(i_34 + 1)] != 't')) goto next_447;
    struct StringList* list_19 = (struct StringList*)malloc(sizeof(struct StringList));
    list_19->head = (struct String){.str = "\t", .len = 1};
    list_19->tail = acc_1;
    struct String call_185 = go_10(r_6, text_25, list_19, (i_34 + 2));
    match_120 = call_185;
    goto end_match_445;
next_447:;
    if ((text_25.str[(i_34 + 1)] != 'r')) goto next_448;
    struct StringList* list_20 = (struct StringList*)malloc(sizeof(struct StringList));
    list_20->head = (struct String){.str = "\r", .len = 1};
    list_20->tail = acc_1;
    struct String call_186 = go_10(r_6, text_25, list_20, (i_34 + 2));
    match_120 = call_186;
    goto end_match_445;
next_448:;
    if ((text_25.str[(i_34 + 1)] != 'n')) goto next_449;
    struct StringList* list_21 = (struct StringList*)malloc(sizeof(struct StringList));
    list_21->head = (struct String){.str = "\n", .len = 1};
    list_21->tail = acc_1;
    struct String call_187 = go_10(r_6, text_25, list_21, (i_34 + 2));
    match_120 = call_187;
    goto end_match_445;
next_449:;
    struct String call_188 = strSlice_((i_34 + 1), (i_34 + 2), text_25);
    struct StringList* list_22 = (struct StringList*)malloc(sizeof(struct StringList));
    list_22->head = call_188;
    list_22->tail = acc_1;
    struct String call_189 = go_10(r_6, text_25, list_22, (i_34 + 2));
    match_120 = call_189;
    goto end_match_445;
next_450:;
end_match_445:;
    match_119 = match_120;
    goto end_match_442;
next_444:;
    exit(1);
end_match_442:;
    return match_119;
}

struct Token_ tokenFromStrLit_(struct String text_25, int l_6, int r_6) {
    int match_121;
    int match_122;
    if ((r_6 < (l_6 + 2))) goto next_453;
    match_122 = (text_25.str[l_6] == '"');
    goto end_match_452;
next_453:;
    if ((r_6 >= (l_6 + 2))) goto next_454;
    match_122 = 0;
    goto end_match_452;
next_454:;
    exit(1);
end_match_452:;
    if ((!(match_122))) goto next_455;
    match_121 = (text_25.str[(r_6 - 1)] == '"');
    goto end_match_451;
next_455:;
    if (match_122) goto next_456;
    match_121 = 0;
    goto end_match_451;
next_456:;
    exit(1);
end_match_451:;
    milone_assert(match_121, 384, 2);
    int call_190 = 0;
    struct String call_191 = go_10(r_6, text_25, NULL, (l_6 + 1));
    struct String value_2 = call_191;
    struct String* payload_8 = (struct String*)malloc(sizeof(struct String));
    (*(((struct String*)payload_8))) = value_2;
    struct Token_ variant_8 = (struct Token_){.tag = Str_1, .Str_1 = payload_8};
    return variant_8;
}

struct Token_ tokenFromStrLitRaw_(struct String text_26, int l_7, int r_7) {
    int match_123;
    int match_124;
    if ((r_7 < (l_7 + 6))) goto next_459;
    int call_192 = strIsFollowedByRawQuotes_(l_7, text_26);
    match_124 = call_192;
    goto end_match_458;
next_459:;
    if ((r_7 >= (l_7 + 6))) goto next_460;
    match_124 = 0;
    goto end_match_458;
next_460:;
    exit(1);
end_match_458:;
    if ((!(match_124))) goto next_461;
    int call_193 = strIsFollowedByRawQuotes_((r_7 - 3), text_26);
    match_123 = call_193;
    goto end_match_457;
next_461:;
    if (match_124) goto next_462;
    match_123 = 0;
    goto end_match_457;
next_462:;
    exit(1);
end_match_457:;
    milone_assert(match_123, 420, 2);
    int call_194 = 0;
    struct String call_195 = strSlice_((l_7 + 3), (r_7 - 3), text_26);
    struct String* payload_9 = (struct String*)malloc(sizeof(struct String));
    (*(((struct String*)payload_9))) = call_195;
    struct Token_ variant_9 = (struct Token_){.tag = Str_1, .Str_1 = payload_9};
    return variant_9;
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

struct StringIntTuple2 tokCtxToTextIndex_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 arg_25) {
    struct String text_27 = arg_25.t0;
    int i_35 = arg_25.t1;
    struct StringIntTuple2 tuple_25;
    tuple_25.t0 = text_27;
    tuple_25.t1 = i_35;
    return tuple_25;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokCtxSkip_(int r_8, struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 arg_26) {
    struct String text_28 = arg_26.t0;
    int i_36 = arg_26.t1;
    struct IntIntTuple2 loc_ = arg_26.t2;
    struct Token_IntIntTuple2Tuple2List* acc_2 = arg_26.t3;
    int match_125;
    int match_126;
    if ((i_36 < 0)) goto next_465;
    match_126 = (r_8 >= i_36);
    goto end_match_464;
next_465:;
    if ((i_36 >= 0)) goto next_466;
    match_126 = 0;
    goto end_match_464;
next_466:;
    exit(1);
end_match_464:;
    if ((!(match_126))) goto next_467;
    match_125 = (text_28.len >= r_8);
    goto end_match_463;
next_467:;
    if (match_126) goto next_468;
    match_125 = 0;
    goto end_match_463;
next_468:;
    exit(1);
end_match_463:;
    milone_assert(match_125, 433, 2);
    int call_196 = 0;
    struct IntIntTuple2 call_197 = locShift_(text_28, i_36, r_8, loc_);
    struct IntIntTuple2 newLoc_ = call_197;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tuple_26;
    tuple_26.t0 = text_28;
    tuple_26.t1 = r_8;
    tuple_26.t2 = newLoc_;
    tuple_26.t3 = acc_2;
    return tuple_26;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokCtxPush_(struct Token_ kind_, int r_9, struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 arg_27) {
    struct String text_29 = arg_27.t0;
    int i_37 = arg_27.t1;
    struct IntIntTuple2 loc_1 = arg_27.t2;
    struct Token_IntIntTuple2Tuple2List* acc_3 = arg_27.t3;
    int match_127;
    int match_128;
    if ((i_37 < 0)) goto next_471;
    match_128 = (r_9 >= i_37);
    goto end_match_470;
next_471:;
    if ((i_37 >= 0)) goto next_472;
    match_128 = 0;
    goto end_match_470;
next_472:;
    exit(1);
end_match_470:;
    if ((!(match_128))) goto next_473;
    match_127 = (text_29.len >= r_9);
    goto end_match_469;
next_473:;
    if (match_128) goto next_474;
    match_127 = 0;
    goto end_match_469;
next_474:;
    exit(1);
end_match_469:;
    milone_assert(match_127, 440, 2);
    int call_198 = 0;
    struct Token_IntIntTuple2Tuple2 tuple_27;
    tuple_27.t0 = kind_;
    tuple_27.t1 = loc_1;
    struct Token_IntIntTuple2Tuple2List* list_23 = (struct Token_IntIntTuple2Tuple2List*)malloc(sizeof(struct Token_IntIntTuple2Tuple2List));
    list_23->head = tuple_27;
    list_23->tail = acc_3;
    struct Token_IntIntTuple2Tuple2List* newAcc_ = list_23;
    struct IntIntTuple2 call_199 = locShift_(text_29, i_37, r_9, loc_1);
    struct IntIntTuple2 newLoc_1 = call_199;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tuple_28;
    tuple_28.t0 = text_29;
    tuple_28.t1 = r_9;
    tuple_28.t2 = newLoc_1;
    tuple_28.t3 = newAcc_;
    return tuple_28;
}

struct Token_IntIntTuple2Tuple2List* tokEof_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 arg_28) {
    struct String text_30 = arg_28.t0;
    int i_38 = arg_28.t1;
    struct Token_IntIntTuple2Tuple2List* acc_4 = arg_28.t3;
    int call_200 = lookEof_(text_30, i_38);
    milone_assert(call_200, 446, 2);
    int call_201 = 0;
    struct Token_IntIntTuple2Tuple2List* call_202 = listRev_7(acc_4);
    return call_202;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokError_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_) {
    struct StringIntTuple2 call_203 = tokCtxToTextIndex_(t_);
    struct String text_31 = call_203.t0;
    int i_39 = call_203.t1;
    int call_204 = scanError_(text_31, i_39);
    int r_10 = call_204;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_205 = tokCtxSkip_(r_10, t_);
    return call_205;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokComment_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_1) {
    struct StringIntTuple2 call_206 = tokCtxToTextIndex_(t_1);
    struct String text_32 = call_206.t0;
    int i_40 = call_206.t1;
    int call_207 = scanLine_(text_32, i_40);
    int r_11 = call_207;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_208 = tokCtxSkip_(r_11, t_1);
    return call_208;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokSpace_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_2) {
    struct StringIntTuple2 call_209 = tokCtxToTextIndex_(t_2);
    struct String text_33 = call_209.t0;
    int i_41 = call_209.t1;
    int call_210 = scanSpace_(text_33, i_41);
    int r_12 = call_210;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_211 = tokCtxSkip_(r_12, t_2);
    return call_211;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokPun_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_3) {
    struct StringIntTuple2 call_212 = tokCtxToTextIndex_(t_3);
    struct String text_34 = call_212.t0;
    int i_42 = call_212.t1;
    int call_213 = scanPun_(text_34, i_42);
    int r_13 = call_213;
    struct Token_ call_214 = tokenFromPun_(text_34, i_42, r_13);
    struct Token_ token_ = call_214;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_215 = tokCtxPush_(token_, r_13, t_3);
    return call_215;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokOp_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_4) {
    struct StringIntTuple2 call_216 = tokCtxToTextIndex_(t_4);
    struct String text_35 = call_216.t0;
    int i_43 = call_216.t1;
    int call_217 = scanOp_(text_35, i_43);
    int r_14 = call_217;
    struct Token_ call_218 = tokenFromOp_(text_35, i_43, r_14);
    struct Token_ token_1 = call_218;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_219 = tokCtxPush_(token_1, r_14, t_4);
    return call_219;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokIdent_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_5) {
    struct StringIntTuple2 call_220 = tokCtxToTextIndex_(t_5);
    struct String text_36 = call_220.t0;
    int i_44 = call_220.t1;
    int call_221 = scanIdent_(text_36, i_44);
    int r_15 = call_221;
    struct Token_ call_222 = tokenFromIdent_(text_36, i_44, r_15);
    struct Token_ token_2 = call_222;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_223 = tokCtxPush_(token_2, r_15, t_5);
    return call_223;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokIntLit_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_6) {
    struct StringIntTuple2 call_224 = tokCtxToTextIndex_(t_6);
    struct String text_37 = call_224.t0;
    int i_45 = call_224.t1;
    int call_225 = scanIntLit_(text_37, i_45);
    int r_16 = call_225;
    struct Token_ call_226 = tokenFromIntLit_(text_37, i_45, r_16);
    struct Token_ token_3 = call_226;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_227 = tokCtxPush_(token_3, r_16, t_6);
    return call_227;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokCharLit_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_7) {
    struct StringIntTuple2 call_228 = tokCtxToTextIndex_(t_7);
    struct String text_38 = call_228.t0;
    int i_46 = call_228.t1;
    struct BoolIntTuple2 call_229 = scanCharLit_(text_38, i_46);
    int ok_ = call_229.t0;
    int r_17 = call_229.t1;
    struct Token_ match_129;
    if ((!(ok_))) goto next_476;
    struct Token_ call_230 = tokenFromCharLit_(text_38, i_46, r_17);
    match_129 = call_230;
    goto end_match_475;
next_476:;
    if (ok_) goto next_477;
    match_129 = (struct Token_){.tag = Error_};
    goto end_match_475;
next_477:;
    exit(1);
end_match_475:;
    struct Token_ token_4 = match_129;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_231 = tokCtxPush_(token_4, r_17, t_7);
    return call_231;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokStrLit_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_8) {
    struct StringIntTuple2 call_232 = tokCtxToTextIndex_(t_8);
    struct String text_39 = call_232.t0;
    int i_47 = call_232.t1;
    struct BoolIntTuple2 call_233 = scanStrLit_(text_39, i_47);
    int ok_1 = call_233.t0;
    int r_18 = call_233.t1;
    struct Token_ match_130;
    if ((!(ok_1))) goto next_479;
    struct Token_ call_234 = tokenFromStrLit_(text_39, i_47, r_18);
    match_130 = call_234;
    goto end_match_478;
next_479:;
    if (ok_1) goto next_480;
    match_130 = (struct Token_){.tag = Error_};
    goto end_match_478;
next_480:;
    exit(1);
end_match_478:;
    struct Token_ token_5 = match_130;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_235 = tokCtxPush_(token_5, r_18, t_8);
    return call_235;
}

struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tokStrLitRaw_(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_9) {
    struct StringIntTuple2 call_236 = tokCtxToTextIndex_(t_9);
    struct String text_40 = call_236.t0;
    int i_48 = call_236.t1;
    struct BoolIntTuple2 call_237 = scanStrLitRaw_(text_40, i_48);
    int ok_2 = call_237.t0;
    int r_19 = call_237.t1;
    struct Token_ match_131;
    if ((!(ok_2))) goto next_482;
    struct Token_ call_238 = tokenFromStrLitRaw_(text_40, i_48, r_19);
    match_131 = call_238;
    goto end_match_481;
next_482:;
    if (ok_2) goto next_483;
    match_131 = (struct Token_){.tag = Error_};
    goto end_match_481;
next_483:;
    exit(1);
end_match_481:;
    struct Token_ token_6 = match_131;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_239 = tokCtxPush_(token_6, r_19, t_9);
    return call_239;
}

struct Token_IntIntTuple2Tuple2List* go_11(struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 t_10) {
    struct StringIntTuple2 call_240 = tokCtxToTextIndex_(t_10);
    struct String text_42 = call_240.t0;
    int i_49 = call_240.t1;
    struct Token_IntIntTuple2Tuple2List* match_132;
    int call_241 = lookEof_(text_42, i_49);
    if ((!(call_241))) goto next_485;
    struct Token_IntIntTuple2Tuple2List* call_242 = tokEof_(t_10);
    match_132 = call_242;
    goto end_match_484;
next_485:;
    if (call_241) goto next_486;
    struct Token_IntIntTuple2Tuple2List* match_133;
    int call_243 = lookComment_(text_42, i_49);
    if ((!(call_243))) goto next_488;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_244 = tokComment_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_245 = go_11(call_244);
    match_133 = call_245;
    goto end_match_487;
next_488:;
    if (call_243) goto next_489;
    struct Token_IntIntTuple2Tuple2List* match_134;
    int call_246 = lookSpace_(text_42, i_49);
    if ((!(call_246))) goto next_491;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_247 = tokSpace_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_248 = go_11(call_247);
    match_134 = call_248;
    goto end_match_490;
next_491:;
    if (call_246) goto next_492;
    struct Token_IntIntTuple2Tuple2List* match_135;
    int call_249 = lookOp_(text_42, i_49);
    if ((!(call_249))) goto next_494;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_250 = tokOp_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_251 = go_11(call_250);
    match_135 = call_251;
    goto end_match_493;
next_494:;
    if (call_249) goto next_495;
    struct Token_IntIntTuple2Tuple2List* match_136;
    int call_252 = lookIntLit_(text_42, i_49);
    if ((!(call_252))) goto next_497;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_253 = tokIntLit_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_254 = go_11(call_253);
    match_136 = call_254;
    goto end_match_496;
next_497:;
    if (call_252) goto next_498;
    struct Token_IntIntTuple2Tuple2List* match_137;
    int call_255 = lookIdent_(text_42, i_49);
    if ((!(call_255))) goto next_500;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_256 = tokIdent_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_257 = go_11(call_256);
    match_137 = call_257;
    goto end_match_499;
next_500:;
    if (call_255) goto next_501;
    struct Token_IntIntTuple2Tuple2List* match_138;
    int call_258 = lookCharLit_(text_42, i_49);
    if ((!(call_258))) goto next_503;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_259 = tokCharLit_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_260 = go_11(call_259);
    match_138 = call_260;
    goto end_match_502;
next_503:;
    if (call_258) goto next_504;
    struct Token_IntIntTuple2Tuple2List* match_139;
    int call_261 = lookStrLitRaw_(text_42, i_49);
    if ((!(call_261))) goto next_506;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_262 = tokStrLitRaw_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_263 = go_11(call_262);
    match_139 = call_263;
    goto end_match_505;
next_506:;
    if (call_261) goto next_507;
    struct Token_IntIntTuple2Tuple2List* match_140;
    int call_264 = lookStrLit_(text_42, i_49);
    if ((!(call_264))) goto next_509;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_265 = tokStrLit_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_266 = go_11(call_265);
    match_140 = call_266;
    goto end_match_508;
next_509:;
    if (call_264) goto next_510;
    struct Token_IntIntTuple2Tuple2List* match_141;
    int call_267 = lookPun_(text_42, i_49);
    if ((!(call_267))) goto next_512;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_268 = tokPun_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_269 = go_11(call_268);
    match_141 = call_269;
    goto end_match_511;
next_512:;
    if (call_267) goto next_513;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 call_270 = tokError_(t_10);
    struct Token_IntIntTuple2Tuple2List* call_271 = go_11(call_270);
    match_141 = call_271;
    goto end_match_511;
next_513:;
    exit(1);
end_match_511:;
    match_140 = match_141;
    goto end_match_508;
next_510:;
    exit(1);
end_match_508:;
    match_139 = match_140;
    goto end_match_505;
next_507:;
    exit(1);
end_match_505:;
    match_138 = match_139;
    goto end_match_502;
next_504:;
    exit(1);
end_match_502:;
    match_137 = match_138;
    goto end_match_499;
next_501:;
    exit(1);
end_match_499:;
    match_136 = match_137;
    goto end_match_496;
next_498:;
    exit(1);
end_match_496:;
    match_135 = match_136;
    goto end_match_493;
next_495:;
    exit(1);
end_match_493:;
    match_134 = match_135;
    goto end_match_490;
next_492:;
    exit(1);
end_match_490:;
    match_133 = match_134;
    goto end_match_487;
next_489:;
    exit(1);
end_match_487:;
    match_132 = match_133;
    goto end_match_484;
next_486:;
    exit(1);
end_match_484:;
    return match_132;
}

struct Token_IntIntTuple2Tuple2List* tokenize_(struct String text_41) {
    struct IntIntTuple2 tuple_30;
    tuple_30.t0 = 0;
    tuple_30.t1 = 0;
    struct StringIntIntIntTuple2Token_IntIntTuple2Tuple2ListTuple4 tuple_29;
    tuple_29.t0 = text_41;
    tuple_29.t1 = 0;
    tuple_29.t2 = tuple_30;
    tuple_29.t3 = NULL;
    struct Token_IntIntTuple2Tuple2List* call_272 = go_11(tuple_29);
    return call_272;
}

int leadsExpr_1(struct Token_IntIntTuple2Tuple2List* tokens_1) {
    int match_142;
    if ((!(tokens_1))) goto next_515;
    struct Token_ token_14 = tokens_1->head.t0;
    int call_273 = tokenIsExprFirst_(token_14);
    match_142 = call_273;
    goto end_match_514;
next_515:;
    match_142 = 0;
    goto end_match_514;
next_516:;
end_match_514:;
    return match_142;
}

int leadsArg_1(struct Token_IntIntTuple2Tuple2List* tokens_2) {
    int match_143;
    if ((!(tokens_2))) goto next_518;
    struct Token_ token_15 = tokens_2->head.t0;
    int call_274 = tokenIsArgFirst_(token_15);
    match_143 = call_274;
    goto end_match_517;
next_518:;
    match_143 = 0;
    goto end_match_517;
next_519:;
end_match_517:;
    return match_143;
}

int leadsPat_1(struct Token_IntIntTuple2Tuple2List* tokens_3) {
    int match_144;
    if ((!(tokens_3))) goto next_521;
    struct Token_ token_16 = tokens_3->head.t0;
    int call_275 = tokenIsPatFirst_(token_16);
    match_144 = call_275;
    goto end_match_520;
next_521:;
    match_144 = 0;
    goto end_match_520;
next_522:;
end_match_520:;
    return match_144;
}

struct IntIntTuple2 nextLoc_1(struct Token_IntIntTuple2Tuple2List* tokens_4) {
    struct IntIntTuple2 match_145;
    if ((!((!(tokens_4))))) goto next_524;
    struct IntIntTuple2 tuple_31;
    tuple_31.t0 = (0 - 1);
    tuple_31.t1 = 0;
    match_145 = tuple_31;
    goto end_match_523;
next_524:;
    if ((!(tokens_4))) goto next_525;
    struct IntIntTuple2 loc_7 = tokens_4->head.t1;
    match_145 = loc_7;
    goto end_match_523;
next_525:;
    exit(1);
end_match_523:;
    return match_145;
}

int nextInside_1(struct IntIntTuple2 baseLoc_, struct Token_IntIntTuple2Tuple2List* tokens_5) {
    int match_146;
    if ((!((!(tokens_5))))) goto next_527;
    match_146 = 0;
    goto end_match_526;
next_527:;
    if ((!(tokens_5))) goto next_528;
    struct IntIntTuple2 loc_8 = tokens_5->head.t1;
    int call_276 = locInside_(baseLoc_, loc_8);
    if ((!(call_276))) goto next_528;
    match_146 = 1;
    goto end_match_526;
next_528:;
    match_146 = 0;
    goto end_match_526;
next_529:;
end_match_526:;
    return match_146;
}

struct StringIntIntTuple2Tuple2List* parseErrorCore_1(struct String msg_2, struct IntIntTuple2 loc_9, struct Token_IntIntTuple2Tuple2List* tokens_6, struct StringIntIntTuple2Tuple2List* errors_1) {
    struct StringIntIntTuple2Tuple2 tuple_32;
    tuple_32.t0 = msg_2;
    tuple_32.t1 = loc_9;
    struct StringIntIntTuple2Tuple2List* list_24 = (struct StringIntIntTuple2Tuple2List*)malloc(sizeof(struct StringIntIntTuple2Tuple2List));
    list_24->head = tuple_32;
    list_24->tail = errors_1;
    return list_24;
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

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyError_1(struct String msg_3, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_29) {
    struct Token_IntIntTuple2Tuple2List* tokens_7 = arg_29.t0;
    struct StringIntIntTuple2Tuple2List* errors_2 = arg_29.t1;
    struct IntIntTuple2 call_277 = nextLoc_1(tokens_7);
    struct IntIntTuple2 loc_10 = call_277;
    struct StringIntIntTuple2Tuple2List* call_278 = parseErrorCore_1(msg_3, loc_10, tokens_7, errors_2);
    struct StringIntIntTuple2Tuple2List* errors_3 = call_278;
    struct IntIntTuple2* payload_10 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_10))) = loc_10;
    struct ATy_ variant_10 = (struct ATy_){.tag = Missing_, .Missing_ = payload_10};
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_33;
    tuple_33.t0 = variant_10;
    tuple_33.t1 = tokens_7;
    tuple_33.t2 = errors_3;
    return tuple_33;
}

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct APat_ t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatError_1(struct String msg_4, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_30) {
    struct Token_IntIntTuple2Tuple2List* tokens_8 = arg_30.t0;
    struct StringIntIntTuple2Tuple2List* errors_4 = arg_30.t1;
    struct IntIntTuple2 call_279 = nextLoc_1(tokens_8);
    struct IntIntTuple2 loc_11 = call_279;
    struct StringIntIntTuple2Tuple2List* call_280 = parseErrorCore_1(msg_4, loc_11, tokens_8, errors_4);
    struct StringIntIntTuple2Tuple2List* errors_5 = call_280;
    struct IntIntTuple2* payload_11 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_11))) = loc_11;
    struct APat_ variant_11 = (struct APat_){.tag = Missing_1, .Missing_1 = payload_11};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_34;
    tuple_34.t0 = variant_11;
    tuple_34.t1 = tokens_8;
    tuple_34.t2 = errors_5;
    return tuple_34;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct AExpr_ t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseExprError_1(struct String msg_5, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_31) {
    struct Token_IntIntTuple2Tuple2List* tokens_9 = arg_31.t0;
    struct StringIntIntTuple2Tuple2List* errors_6 = arg_31.t1;
    struct IntIntTuple2 call_281 = nextLoc_1(tokens_9);
    struct IntIntTuple2 loc_12 = call_281;
    struct StringIntIntTuple2Tuple2List* call_282 = parseErrorCore_1(msg_5, loc_12, tokens_9, errors_6);
    struct StringIntIntTuple2Tuple2List* errors_7 = call_282;
    struct IntIntTuple2* payload_12 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_12))) = loc_12;
    struct AExpr_ variant_12 = (struct AExpr_){.tag = Missing_2, .Missing_2 = payload_12};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_35;
    tuple_35.t0 = variant_12;
    tuple_35.t1 = tokens_9;
    tuple_35.t2 = errors_7;
    return tuple_35;
}

struct StringIntIntTuple2Tuple2List* parseNewError_1(struct String msg_6, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_32) {
    struct Token_IntIntTuple2Tuple2List* tokens_10 = arg_32.t0;
    struct StringIntIntTuple2Tuple2List* errors_8 = arg_32.t1;
    struct IntIntTuple2 call_283 = nextLoc_1(tokens_10);
    struct IntIntTuple2 loc_13 = call_283;
    struct StringIntIntTuple2Tuple2List* call_284 = parseErrorCore_1(msg_6, loc_13, tokens_10, errors_8);
    return call_284;
}

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyAtom_(struct IntIntTuple2 baseLoc_1, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_33) {
    struct Token_IntIntTuple2Tuple2List* tokens_11 = arg_33.t0;
    struct StringIntIntTuple2Tuple2List* errors_9 = arg_33.t1;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_147;
    int call_285 = nextInside_1(baseLoc_1, tokens_11);
    if (call_285) goto next_531;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_36;
    tuple_36.t0 = tokens_11;
    tuple_36.t1 = errors_9;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_286 = parseTyError_1((struct String){.str = "Expected a type atom", .len = 20}, tuple_36);
    match_147 = call_286;
    goto end_match_530;
next_531:;
    if ((!(tokens_11))) goto next_532;
    if ((tokens_11->head.t0.tag != Ident_)) goto next_532;
    struct String ident_8 = (*(tokens_11->head.t0.Ident_));
    struct IntIntTuple2 loc_14 = tokens_11->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_12 = tokens_11->tail;
    struct StringIntIntTuple2Tuple2 tuple_38;
    tuple_38.t0 = ident_8;
    tuple_38.t1 = loc_14;
    struct StringIntIntTuple2Tuple2* payload_13 = (struct StringIntIntTuple2Tuple2*)malloc(sizeof(struct StringIntIntTuple2Tuple2));
    (*(((struct StringIntIntTuple2Tuple2*)payload_13))) = tuple_38;
    struct ATy_ variant_13 = (struct ATy_){.tag = Ident_1, .Ident_1 = payload_13};
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_37;
    tuple_37.t0 = variant_13;
    tuple_37.t1 = tokens_12;
    tuple_37.t2 = errors_9;
    match_147 = tuple_37;
    goto end_match_530;
next_532:;
    if ((!(tokens_11))) goto next_533;
    if ((tokens_11->head.t0.tag != ParenL_)) goto next_533;
    struct Token_IntIntTuple2Tuple2List* tokens_13 = tokens_11->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_39;
    tuple_39.t0 = tokens_13;
    tuple_39.t1 = errors_9;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_287 = parseTy_(baseLoc_1, tuple_39);
    struct ATy_ ty_4 = call_287.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_14 = call_287.t1;
    struct StringIntIntTuple2Tuple2List* errors_10 = call_287.t2;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_148;
    if ((!(tokens_14))) goto next_536;
    if ((tokens_14->head.t0.tag != ParenR_)) goto next_536;
    struct Token_IntIntTuple2Tuple2List* tokens_15 = tokens_14->tail;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_40;
    tuple_40.t0 = ty_4;
    tuple_40.t1 = tokens_15;
    tuple_40.t2 = errors_10;
    match_148 = tuple_40;
    goto end_match_535;
next_536:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_41;
    tuple_41.t0 = tokens_14;
    tuple_41.t1 = errors_10;
    struct StringIntIntTuple2Tuple2List* call_288 = parseNewError_1((struct String){.str = "Expected ')'", .len = 12}, tuple_41);
    struct StringIntIntTuple2Tuple2List* errors_11 = call_288;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_42;
    tuple_42.t0 = ty_4;
    tuple_42.t1 = tokens_14;
    tuple_42.t2 = errors_11;
    match_148 = tuple_42;
    goto end_match_535;
next_537:;
end_match_535:;
    match_147 = match_148;
    goto end_match_530;
next_533:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_43;
    tuple_43.t0 = tokens_11;
    tuple_43.t1 = errors_9;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_289 = parseTyError_1((struct String){.str = "Expected a type atom", .len = 20}, tuple_43);
    match_147 = call_289;
    goto end_match_530;
next_534:;
end_match_530:;
    return match_147;
}

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_33(struct IntIntTuple2 baseLoc_2, struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 arg_34) {
    struct ATy_ ty_5 = arg_34.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_17 = arg_34.t1;
    struct StringIntIntTuple2Tuple2List* errors_13 = arg_34.t2;
    int call_290 = nextInside_1(baseLoc_2, tokens_17);
    int inside_ = call_290;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_149;
    if ((!(tokens_17))) goto next_539;
    if ((tokens_17->head.t0.tag != Ident_)) goto next_539;
    struct String ident_9 = (*(tokens_17->head.t0.Ident_));
    struct IntIntTuple2 loc_15 = tokens_17->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_18 = tokens_17->tail;
    if ((!(inside_))) goto next_539;
    struct ATy_StringIntIntTuple2Tuple3 tuple_45;
    tuple_45.t0 = ty_5;
    tuple_45.t1 = ident_9;
    tuple_45.t2 = loc_15;
    struct ATy_StringIntIntTuple2Tuple3* payload_14 = (struct ATy_StringIntIntTuple2Tuple3*)malloc(sizeof(struct ATy_StringIntIntTuple2Tuple3));
    (*(((struct ATy_StringIntIntTuple2Tuple3*)payload_14))) = tuple_45;
    struct ATy_ variant_14 = (struct ATy_){.tag = Suffix_, .Suffix_ = payload_14};
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_44;
    tuple_44.t0 = variant_14;
    tuple_44.t1 = tokens_18;
    tuple_44.t2 = errors_13;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_291 = go_33(baseLoc_2, tuple_44);
    match_149 = call_291;
    goto end_match_538;
next_539:;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_46;
    tuple_46.t0 = ty_5;
    tuple_46.t1 = tokens_17;
    tuple_46.t2 = errors_13;
    match_149 = tuple_46;
    goto end_match_538;
next_540:;
end_match_538:;
    return match_149;
}

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTySuffix_(struct IntIntTuple2 baseLoc_2, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_35) {
    struct Token_IntIntTuple2Tuple2List* tokens_16 = arg_35.t0;
    struct StringIntIntTuple2Tuple2List* errors_12 = arg_35.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_47;
    tuple_47.t0 = tokens_16;
    tuple_47.t1 = errors_12;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_292 = parseTyAtom_(baseLoc_2, tuple_47);
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_293 = go_33(baseLoc_2, call_292);
    return call_293;
}

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyPrefix_(struct IntIntTuple2 baseLoc_3, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_36) {
    struct Token_IntIntTuple2Tuple2List* tokens_19 = arg_36.t0;
    struct StringIntIntTuple2Tuple2List* errors_14 = arg_36.t1;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_150;
    if ((!(tokens_19))) goto next_542;
    if ((tokens_19->head.t0.tag != Ident_)) goto next_542;
    if ((!(tokens_19->tail))) goto next_542;
    if ((tokens_19->tail->head.t0.tag != Colon_)) goto next_542;
    struct Token_IntIntTuple2Tuple2List* tokens_20 = tokens_19->tail->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_48;
    tuple_48.t0 = tokens_20;
    tuple_48.t1 = errors_14;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_294 = parseTySuffix_(baseLoc_3, tuple_48);
    match_150 = call_294;
    goto end_match_541;
next_542:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_49;
    tuple_49.t0 = tokens_19;
    tuple_49.t1 = errors_14;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_295 = parseTySuffix_(baseLoc_3, tuple_49);
    match_150 = call_295;
    goto end_match_541;
next_543:;
end_match_541:;
    return match_150;
}

struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct ATy_List* t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_22(struct IntIntTuple2 baseLoc_4, struct ATy_List* acc_13, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_37) {
    struct Token_IntIntTuple2Tuple2List* tokens_22 = arg_37.t0;
    struct StringIntIntTuple2Tuple2List* errors_16 = arg_37.t1;
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_151;
    if ((!(tokens_22))) goto next_545;
    if ((tokens_22->head.t0.tag != Star_)) goto next_545;
    struct Token_IntIntTuple2Tuple2List* tokens_23 = tokens_22->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_50;
    tuple_50.t0 = tokens_23;
    tuple_50.t1 = errors_16;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_296 = parseTyPrefix_(baseLoc_4, tuple_50);
    struct ATy_ itemTy_ = call_296.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_24 = call_296.t1;
    struct StringIntIntTuple2Tuple2List* errors_17 = call_296.t2;
    struct ATy_List* list_25 = (struct ATy_List*)malloc(sizeof(struct ATy_List));
    list_25->head = itemTy_;
    list_25->tail = acc_13;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_51;
    tuple_51.t0 = tokens_24;
    tuple_51.t1 = errors_17;
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_297 = go_22(baseLoc_4, list_25, tuple_51);
    match_151 = call_297;
    goto end_match_544;
next_545:;
    struct ATy_List* call_298 = listRev_6(acc_13);
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_52;
    tuple_52.t0 = call_298;
    tuple_52.t1 = tokens_22;
    tuple_52.t2 = errors_16;
    match_151 = tuple_52;
    goto end_match_544;
next_546:;
end_match_544:;
    return match_151;
}

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyTuple_(struct IntIntTuple2 baseLoc_4, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_38) {
    struct Token_IntIntTuple2Tuple2List* tokens_21 = arg_38.t0;
    struct StringIntIntTuple2Tuple2List* errors_15 = arg_38.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_53;
    tuple_53.t0 = tokens_21;
    tuple_53.t1 = errors_15;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_299 = parseTyPrefix_(baseLoc_4, tuple_53);
    struct ATy_ itemTy_1 = call_299.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_25 = call_299.t1;
    struct StringIntIntTuple2Tuple2List* errors_18 = call_299.t2;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_152;
    if ((!(tokens_25))) goto next_548;
    if ((tokens_25->head.t0.tag != Star_)) goto next_548;
    struct IntIntTuple2 opLoc_ = tokens_25->head.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_54;
    tuple_54.t0 = tokens_25;
    tuple_54.t1 = errors_18;
    struct ATy_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_300 = go_22(baseLoc_4, NULL, tuple_54);
    struct ATy_List* itemTys_1 = call_300.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_26 = call_300.t1;
    struct StringIntIntTuple2Tuple2List* errors_19 = call_300.t2;
    struct ATy_List* list_26 = (struct ATy_List*)malloc(sizeof(struct ATy_List));
    list_26->head = itemTy_1;
    list_26->tail = itemTys_1;
    struct ATy_ListIntIntTuple2Tuple2 tuple_56;
    tuple_56.t0 = list_26;
    tuple_56.t1 = opLoc_;
    struct ATy_ListIntIntTuple2Tuple2* payload_15 = (struct ATy_ListIntIntTuple2Tuple2*)malloc(sizeof(struct ATy_ListIntIntTuple2Tuple2));
    (*(((struct ATy_ListIntIntTuple2Tuple2*)payload_15))) = tuple_56;
    struct ATy_ variant_15 = (struct ATy_){.tag = Tuple_, .Tuple_ = payload_15};
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_55;
    tuple_55.t0 = variant_15;
    tuple_55.t1 = tokens_26;
    tuple_55.t2 = errors_19;
    match_152 = tuple_55;
    goto end_match_547;
next_548:;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_57;
    tuple_57.t0 = itemTy_1;
    tuple_57.t1 = tokens_25;
    tuple_57.t2 = errors_18;
    match_152 = tuple_57;
    goto end_match_547;
next_549:;
end_match_547:;
    return match_152;
}

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyFun_(struct IntIntTuple2 baseLoc_5, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_39) {
    struct Token_IntIntTuple2Tuple2List* tokens_27 = arg_39.t0;
    struct StringIntIntTuple2Tuple2List* errors_20 = arg_39.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_58;
    tuple_58.t0 = tokens_27;
    tuple_58.t1 = errors_20;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_301 = parseTyTuple_(baseLoc_5, tuple_58);
    struct ATy_ sTy_1 = call_301.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_28 = call_301.t1;
    struct StringIntIntTuple2Tuple2List* errors_21 = call_301.t2;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_153;
    if ((!(tokens_28))) goto next_551;
    if ((tokens_28->head.t0.tag != Arrow_)) goto next_551;
    struct IntIntTuple2 opLoc_1 = tokens_28->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_29 = tokens_28->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_59;
    tuple_59.t0 = tokens_29;
    tuple_59.t1 = errors_21;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_302 = parseTyFun_(baseLoc_5, tuple_59);
    struct ATy_ tTy_1 = call_302.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_30 = call_302.t1;
    struct StringIntIntTuple2Tuple2List* errors_22 = call_302.t2;
    struct ATy_ATy_IntIntTuple2Tuple3 tuple_61;
    tuple_61.t0 = sTy_1;
    tuple_61.t1 = tTy_1;
    tuple_61.t2 = opLoc_1;
    struct ATy_ATy_IntIntTuple2Tuple3* payload_16 = (struct ATy_ATy_IntIntTuple2Tuple3*)malloc(sizeof(struct ATy_ATy_IntIntTuple2Tuple3));
    (*(((struct ATy_ATy_IntIntTuple2Tuple3*)payload_16))) = tuple_61;
    struct ATy_ variant_16 = (struct ATy_){.tag = Fun_1, .Fun_1 = payload_16};
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_60;
    tuple_60.t0 = variant_16;
    tuple_60.t1 = tokens_30;
    tuple_60.t2 = errors_22;
    match_153 = tuple_60;
    goto end_match_550;
next_551:;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_62;
    tuple_62.t0 = sTy_1;
    tuple_62.t1 = tokens_28;
    tuple_62.t2 = errors_21;
    match_153 = tuple_62;
    goto end_match_550;
next_552:;
end_match_550:;
    return match_153;
}

struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTy_(struct IntIntTuple2 baseLoc_6, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_40) {
    struct Token_IntIntTuple2Tuple2List* tokens_31 = arg_40.t0;
    struct StringIntIntTuple2Tuple2List* errors_23 = arg_40.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_63;
    tuple_63.t0 = tokens_31;
    tuple_63.t1 = errors_23;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_303 = parseTyFun_(baseLoc_6, tuple_63);
    return call_303;
}

struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct AVariant_List* t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_23(struct IntIntTuple2 baseLoc_7, struct AVariant_List* acc_14, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_41) {
    struct Token_IntIntTuple2Tuple2List* tokens_33 = arg_41.t0;
    struct StringIntIntTuple2Tuple2List* errors_25 = arg_41.t1;
    struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_154;
    if ((!(tokens_33))) goto next_554;
    if ((tokens_33->head.t0.tag != Pipe_)) goto next_554;
    if ((!(tokens_33->tail))) goto next_554;
    if ((tokens_33->tail->head.t0.tag != Ident_)) goto next_554;
    struct String variantIdent_ = (*(tokens_33->tail->head.t0.Ident_));
    struct IntIntTuple2 loc_16 = tokens_33->tail->head.t1;
    if ((!(tokens_33->tail->tail))) goto next_554;
    if ((tokens_33->tail->tail->head.t0.tag != Of_)) goto next_554;
    struct Token_IntIntTuple2Tuple2List* tokens_34 = tokens_33->tail->tail->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_64;
    tuple_64.t0 = tokens_34;
    tuple_64.t1 = errors_25;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_304 = parseTy_(baseLoc_7, tuple_64);
    struct ATy_ payloadTy_ = call_304.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_35 = call_304.t1;
    struct StringIntIntTuple2Tuple2List* errors_26 = call_304.t2;
    struct ATy_List* list_28 = (struct ATy_List*)malloc(sizeof(struct ATy_List));
    list_28->head = payloadTy_;
    list_28->tail = NULL;
    struct StringATy_ListIntIntTuple2Tuple3 tuple_65;
    tuple_65.t0 = variantIdent_;
    tuple_65.t1 = list_28;
    tuple_65.t2 = loc_16;
    struct StringATy_ListIntIntTuple2Tuple3* payload_17 = (struct StringATy_ListIntIntTuple2Tuple3*)malloc(sizeof(struct StringATy_ListIntIntTuple2Tuple3));
    (*(((struct StringATy_ListIntIntTuple2Tuple3*)payload_17))) = tuple_65;
    struct AVariant_ variant_17 = (struct AVariant_){.tag = AVariant_, .AVariant_ = payload_17};
    struct AVariant_List* list_27 = (struct AVariant_List*)malloc(sizeof(struct AVariant_List));
    list_27->head = variant_17;
    list_27->tail = acc_14;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_66;
    tuple_66.t0 = tokens_35;
    tuple_66.t1 = errors_26;
    struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_305 = go_23(baseLoc_7, list_27, tuple_66);
    match_154 = call_305;
    goto end_match_553;
next_554:;
    if ((!(tokens_33))) goto next_555;
    if ((tokens_33->head.t0.tag != Pipe_)) goto next_555;
    if ((!(tokens_33->tail))) goto next_555;
    if ((tokens_33->tail->head.t0.tag != Ident_)) goto next_555;
    struct String variantIdent_1 = (*(tokens_33->tail->head.t0.Ident_));
    struct IntIntTuple2 loc_17 = tokens_33->tail->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_36 = tokens_33->tail->tail;
    struct StringATy_ListIntIntTuple2Tuple3 tuple_67;
    tuple_67.t0 = variantIdent_1;
    tuple_67.t1 = NULL;
    tuple_67.t2 = loc_17;
    struct StringATy_ListIntIntTuple2Tuple3* payload_18 = (struct StringATy_ListIntIntTuple2Tuple3*)malloc(sizeof(struct StringATy_ListIntIntTuple2Tuple3));
    (*(((struct StringATy_ListIntIntTuple2Tuple3*)payload_18))) = tuple_67;
    struct AVariant_ variant_18 = (struct AVariant_){.tag = AVariant_, .AVariant_ = payload_18};
    struct AVariant_List* list_29 = (struct AVariant_List*)malloc(sizeof(struct AVariant_List));
    list_29->head = variant_18;
    list_29->tail = acc_14;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_68;
    tuple_68.t0 = tokens_36;
    tuple_68.t1 = errors_25;
    struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_306 = go_23(baseLoc_7, list_29, tuple_68);
    match_154 = call_306;
    goto end_match_553;
next_555:;
    struct AVariant_List* call_307 = listRev_5(acc_14);
    struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_69;
    tuple_69.t0 = call_307;
    tuple_69.t1 = tokens_33;
    tuple_69.t2 = errors_25;
    match_154 = tuple_69;
    goto end_match_553;
next_556:;
end_match_553:;
    return match_154;
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

struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyDeclUnion_(struct IntIntTuple2 baseLoc_7, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_42) {
    struct Token_IntIntTuple2Tuple2List* tokens_32 = arg_42.t0;
    struct StringIntIntTuple2Tuple2List* errors_24 = arg_42.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_70;
    tuple_70.t0 = tokens_32;
    tuple_70.t1 = errors_24;
    struct AVariant_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_308 = go_23(baseLoc_7, NULL, tuple_70);
    struct AVariant_List* variants_1 = call_308.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_37 = call_308.t1;
    struct StringIntIntTuple2Tuple2List* errors_27 = call_308.t2;
    struct AVariant_List** payload_19 = (struct AVariant_List**)malloc(sizeof(struct AVariant_List*));
    (*(((struct AVariant_List**)payload_19))) = variants_1;
    struct ATyDecl_ variant_19 = (struct ATyDecl_){.tag = Union_, .Union_ = payload_19};
    struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_71;
    tuple_71.t0 = variant_19;
    tuple_71.t1 = tokens_37;
    tuple_71.t2 = errors_27;
    return tuple_71;
}

struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyDeclBody_(struct IntIntTuple2 baseLoc_8, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_43) {
    struct Token_IntIntTuple2Tuple2List* tokens_38 = arg_43.t0;
    struct StringIntIntTuple2Tuple2List* errors_28 = arg_43.t1;
    struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_155;
    if ((!(tokens_38))) goto next_558;
    if ((tokens_38->head.t0.tag != Pipe_)) goto next_558;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_72;
    tuple_72.t0 = tokens_38;
    tuple_72.t1 = errors_28;
    struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_309 = parseTyDeclUnion_(baseLoc_8, tuple_72);
    match_155 = call_309;
    goto end_match_557;
next_558:;
    if ((!(tokens_38))) goto next_559;
    if ((tokens_38->head.t0.tag != Ident_)) goto next_559;
    if ((!(tokens_38->tail))) goto next_559;
    if ((tokens_38->tail->head.t0.tag != Of_)) goto next_559;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_73;
    tuple_73.t0 = tokens_38;
    tuple_73.t1 = errors_28;
    struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_310 = parseTyDeclUnion_(baseLoc_8, tuple_73);
    match_155 = call_310;
    goto end_match_557;
next_559:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_74;
    tuple_74.t0 = tokens_38;
    tuple_74.t1 = errors_28;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_311 = parseTy_(baseLoc_8, tuple_74);
    struct ATy_ ty_6 = call_311.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_39 = call_311.t1;
    struct StringIntIntTuple2Tuple2List* errors_29 = call_311.t2;
    struct ATy_* payload_20 = (struct ATy_*)malloc(sizeof(struct ATy_));
    (*(((struct ATy_*)payload_20))) = ty_6;
    struct ATyDecl_ variant_20 = (struct ATyDecl_){.tag = Synonym_, .Synonym_ = payload_20};
    struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_75;
    tuple_75.t0 = variant_20;
    tuple_75.t1 = tokens_39;
    tuple_75.t2 = errors_29;
    match_155 = tuple_75;
    goto end_match_557;
next_560:;
end_match_557:;
    return match_155;
}

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatParenBody_(struct IntIntTuple2 baseLoc_9, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_44) {
    struct Token_IntIntTuple2Tuple2List* tokens_40 = arg_44.t0;
    struct StringIntIntTuple2Tuple2List* errors_30 = arg_44.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_76;
    tuple_76.t0 = tokens_40;
    tuple_76.t1 = errors_30;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_312 = parsePat_(baseLoc_9, tuple_76);
    struct APat_ pat_4 = call_312.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_41 = call_312.t1;
    struct StringIntIntTuple2Tuple2List* errors_31 = call_312.t2;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_156;
    if ((!(tokens_41))) goto next_562;
    if ((tokens_41->head.t0.tag != ParenR_)) goto next_562;
    struct Token_IntIntTuple2Tuple2List* tokens_42 = tokens_41->tail;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_77;
    tuple_77.t0 = pat_4;
    tuple_77.t1 = tokens_42;
    tuple_77.t2 = errors_31;
    match_156 = tuple_77;
    goto end_match_561;
next_562:;
    struct Token_IntIntTuple2Tuple2List* tokens_43 = tokens_41;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_78;
    tuple_78.t0 = tokens_43;
    tuple_78.t1 = errors_31;
    struct StringIntIntTuple2Tuple2List* call_313 = parseNewError_1((struct String){.str = "Expected ')'", .len = 12}, tuple_78);
    struct StringIntIntTuple2Tuple2List* errors_32 = call_313;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_79;
    tuple_79.t0 = pat_4;
    tuple_79.t1 = tokens_43;
    tuple_79.t2 = errors_32;
    match_156 = tuple_79;
    goto end_match_561;
next_563:;
end_match_561:;
    return match_156;
}

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct APat_List* t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_24(struct IntIntTuple2 baseLoc_10, struct APat_List* patAcc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_45) {
    struct Token_IntIntTuple2Tuple2List* tokens_45 = arg_45.t0;
    struct StringIntIntTuple2Tuple2List* errors_34 = arg_45.t1;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_157;
    if ((!(tokens_45))) goto next_565;
    if ((tokens_45->head.t0.tag != BracketR_)) goto next_565;
    struct Token_IntIntTuple2Tuple2List* tokens_46 = tokens_45->tail;
    struct APat_List* call_314 = listRev_4(patAcc_);
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_80;
    tuple_80.t0 = call_314;
    tuple_80.t1 = tokens_46;
    tuple_80.t2 = errors_34;
    match_157 = tuple_80;
    goto end_match_564;
next_565:;
    if ((!(tokens_45))) goto next_566;
    if ((tokens_45->head.t0.tag != Semi_)) goto next_566;
    struct Token_IntIntTuple2Tuple2List* tokens_47 = tokens_45->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_81;
    tuple_81.t0 = tokens_47;
    tuple_81.t1 = errors_34;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_315 = parsePat_(baseLoc_10, tuple_81);
    struct APat_ pat_5 = call_315.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_48 = call_315.t1;
    struct StringIntIntTuple2Tuple2List* errors_35 = call_315.t2;
    struct APat_List* list_30 = (struct APat_List*)malloc(sizeof(struct APat_List));
    list_30->head = pat_5;
    list_30->tail = patAcc_;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_82;
    tuple_82.t0 = tokens_48;
    tuple_82.t1 = errors_35;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_316 = go_24(baseLoc_10, list_30, tuple_82);
    match_157 = call_316;
    goto end_match_564;
next_566:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_83;
    tuple_83.t0 = tokens_45;
    tuple_83.t1 = errors_34;
    struct StringIntIntTuple2Tuple2List* call_317 = parseNewError_1((struct String){.str = "Expected ';' or ']'", .len = 19}, tuple_83);
    struct StringIntIntTuple2Tuple2List* errors_36 = call_317;
    struct APat_List* call_318 = listRev_4(patAcc_);
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_84;
    tuple_84.t0 = call_318;
    tuple_84.t1 = tokens_45;
    tuple_84.t2 = errors_36;
    match_157 = tuple_84;
    goto end_match_564;
next_567:;
end_match_564:;
    return match_157;
}

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatListBody_(struct IntIntTuple2 baseLoc_10, struct IntIntTuple2 bracketLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_46) {
    struct Token_IntIntTuple2Tuple2List* tokens_44 = arg_46.t0;
    struct StringIntIntTuple2Tuple2List* errors_33 = arg_46.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_85;
    tuple_85.t0 = tokens_44;
    tuple_85.t1 = errors_33;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_319 = parsePat_(baseLoc_10, tuple_85);
    struct APat_ itemPat_ = call_319.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_49 = call_319.t1;
    struct StringIntIntTuple2Tuple2List* errors_37 = call_319.t2;
    struct APat_List* list_31 = (struct APat_List*)malloc(sizeof(struct APat_List));
    list_31->head = itemPat_;
    list_31->tail = NULL;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_86;
    tuple_86.t0 = tokens_49;
    tuple_86.t1 = errors_37;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_320 = go_24(baseLoc_10, list_31, tuple_86);
    struct APat_List* itemPats_ = call_320.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_50 = call_320.t1;
    struct StringIntIntTuple2Tuple2List* errors_38 = call_320.t2;
    struct APat_ListIntIntTuple2Tuple2 tuple_88;
    tuple_88.t0 = itemPats_;
    tuple_88.t1 = bracketLoc_;
    struct APat_ListIntIntTuple2Tuple2* payload_21 = (struct APat_ListIntIntTuple2Tuple2*)malloc(sizeof(struct APat_ListIntIntTuple2Tuple2));
    (*(((struct APat_ListIntIntTuple2Tuple2*)payload_21))) = tuple_88;
    struct APat_ variant_21 = (struct APat_){.tag = ListLit_, .ListLit_ = payload_21};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_87;
    tuple_87.t0 = variant_21;
    tuple_87.t1 = tokens_50;
    tuple_87.t2 = errors_38;
    return tuple_87;
}

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatAtom_(struct IntIntTuple2 baseLoc_11, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_47) {
    struct Token_IntIntTuple2Tuple2List* tokens_51 = arg_47.t0;
    struct StringIntIntTuple2Tuple2List* errors_39 = arg_47.t1;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_158;
    int match_159;
    int call_321 = nextInside_1(baseLoc_11, tokens_51);
    if ((!(call_321))) goto next_581;
    int call_322 = leadsPat_1(tokens_51);
    match_159 = call_322;
    goto end_match_580;
next_581:;
    if (call_321) goto next_582;
    match_159 = 0;
    goto end_match_580;
next_582:;
    exit(1);
end_match_580:;
    if (match_159) goto next_569;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_89;
    tuple_89.t0 = tokens_51;
    tuple_89.t1 = errors_39;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_323 = parsePatError_1((struct String){.str = "Expected a pattern atom", .len = 23}, tuple_89);
    match_158 = call_323;
    goto end_match_568;
next_569:;
    if ((!(tokens_51))) goto next_570;
    if ((tokens_51->head.t0.tag != Bool_1)) goto next_570;
    int value_7 = (*(tokens_51->head.t0.Bool_1));
    struct IntIntTuple2 loc_18 = tokens_51->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_52 = tokens_51->tail;
    int* payload_22 = (int*)malloc(sizeof(int));
    (*(((int*)payload_22))) = value_7;
    struct Lit_ variant_22 = (struct Lit_){.tag = Bool_, .Bool_ = payload_22};
    struct Lit_IntIntTuple2Tuple2 tuple_91;
    tuple_91.t0 = variant_22;
    tuple_91.t1 = loc_18;
    struct Lit_IntIntTuple2Tuple2* payload_23 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_23))) = tuple_91;
    struct APat_ variant_23 = (struct APat_){.tag = Lit_, .Lit_ = payload_23};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_90;
    tuple_90.t0 = variant_23;
    tuple_90.t1 = tokens_52;
    tuple_90.t2 = errors_39;
    match_158 = tuple_90;
    goto end_match_568;
next_570:;
    if ((!(tokens_51))) goto next_571;
    if ((tokens_51->head.t0.tag != Int_1)) goto next_571;
    int value_8 = (*(tokens_51->head.t0.Int_1));
    struct IntIntTuple2 loc_19 = tokens_51->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_53 = tokens_51->tail;
    int* payload_24 = (int*)malloc(sizeof(int));
    (*(((int*)payload_24))) = value_8;
    struct Lit_ variant_24 = (struct Lit_){.tag = Int_, .Int_ = payload_24};
    struct Lit_IntIntTuple2Tuple2 tuple_93;
    tuple_93.t0 = variant_24;
    tuple_93.t1 = loc_19;
    struct Lit_IntIntTuple2Tuple2* payload_25 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_25))) = tuple_93;
    struct APat_ variant_25 = (struct APat_){.tag = Lit_, .Lit_ = payload_25};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_92;
    tuple_92.t0 = variant_25;
    tuple_92.t1 = tokens_53;
    tuple_92.t2 = errors_39;
    match_158 = tuple_92;
    goto end_match_568;
next_571:;
    if ((!(tokens_51))) goto next_572;
    if ((tokens_51->head.t0.tag != Char_1)) goto next_572;
    char value_9 = (*(tokens_51->head.t0.Char_1));
    struct IntIntTuple2 loc_20 = tokens_51->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_54 = tokens_51->tail;
    char* payload_26 = (char*)malloc(sizeof(char));
    (*(((char*)payload_26))) = value_9;
    struct Lit_ variant_26 = (struct Lit_){.tag = Char_, .Char_ = payload_26};
    struct Lit_IntIntTuple2Tuple2 tuple_95;
    tuple_95.t0 = variant_26;
    tuple_95.t1 = loc_20;
    struct Lit_IntIntTuple2Tuple2* payload_27 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_27))) = tuple_95;
    struct APat_ variant_27 = (struct APat_){.tag = Lit_, .Lit_ = payload_27};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_94;
    tuple_94.t0 = variant_27;
    tuple_94.t1 = tokens_54;
    tuple_94.t2 = errors_39;
    match_158 = tuple_94;
    goto end_match_568;
next_572:;
    if ((!(tokens_51))) goto next_573;
    if ((tokens_51->head.t0.tag != Str_1)) goto next_573;
    struct String value_10 = (*(tokens_51->head.t0.Str_1));
    struct IntIntTuple2 loc_21 = tokens_51->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_55 = tokens_51->tail;
    struct String* payload_28 = (struct String*)malloc(sizeof(struct String));
    (*(((struct String*)payload_28))) = value_10;
    struct Lit_ variant_28 = (struct Lit_){.tag = Str_, .Str_ = payload_28};
    struct Lit_IntIntTuple2Tuple2 tuple_97;
    tuple_97.t0 = variant_28;
    tuple_97.t1 = loc_21;
    struct Lit_IntIntTuple2Tuple2* payload_29 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_29))) = tuple_97;
    struct APat_ variant_29 = (struct APat_){.tag = Lit_, .Lit_ = payload_29};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_96;
    tuple_96.t0 = variant_29;
    tuple_96.t1 = tokens_55;
    tuple_96.t2 = errors_39;
    match_158 = tuple_96;
    goto end_match_568;
next_573:;
    if ((!(tokens_51))) goto next_574;
    if ((tokens_51->head.t0.tag != Ident_)) goto next_574;
    struct String ident_10 = (*(tokens_51->head.t0.Ident_));
    struct IntIntTuple2 loc_22 = tokens_51->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_56 = tokens_51->tail;
    struct StringIntIntTuple2Tuple2 tuple_99;
    tuple_99.t0 = ident_10;
    tuple_99.t1 = loc_22;
    struct StringIntIntTuple2Tuple2* payload_30 = (struct StringIntIntTuple2Tuple2*)malloc(sizeof(struct StringIntIntTuple2Tuple2));
    (*(((struct StringIntIntTuple2Tuple2*)payload_30))) = tuple_99;
    struct APat_ variant_30 = (struct APat_){.tag = Ident_2, .Ident_2 = payload_30};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_98;
    tuple_98.t0 = variant_30;
    tuple_98.t1 = tokens_56;
    tuple_98.t2 = errors_39;
    match_158 = tuple_98;
    goto end_match_568;
next_574:;
    if ((!(tokens_51))) goto next_575;
    if ((tokens_51->head.t0.tag != ParenL_)) goto next_575;
    struct IntIntTuple2 loc_23 = tokens_51->head.t1;
    if ((!(tokens_51->tail))) goto next_575;
    if ((tokens_51->tail->head.t0.tag != ParenR_)) goto next_575;
    struct Token_IntIntTuple2Tuple2List* tokens_57 = tokens_51->tail->tail;
    struct APat_ListIntIntTuple2Tuple2 tuple_101;
    tuple_101.t0 = NULL;
    tuple_101.t1 = loc_23;
    struct APat_ListIntIntTuple2Tuple2* payload_31 = (struct APat_ListIntIntTuple2Tuple2*)malloc(sizeof(struct APat_ListIntIntTuple2Tuple2));
    (*(((struct APat_ListIntIntTuple2Tuple2*)payload_31))) = tuple_101;
    struct APat_ variant_31 = (struct APat_){.tag = TupleLit_, .TupleLit_ = payload_31};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_100;
    tuple_100.t0 = variant_31;
    tuple_100.t1 = tokens_57;
    tuple_100.t2 = errors_39;
    match_158 = tuple_100;
    goto end_match_568;
next_575:;
    if ((!(tokens_51))) goto next_576;
    if ((tokens_51->head.t0.tag != ParenL_)) goto next_576;
    struct Token_IntIntTuple2Tuple2List* tokens_58 = tokens_51->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_102;
    tuple_102.t0 = tokens_58;
    tuple_102.t1 = errors_39;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_324 = parsePatParenBody_(baseLoc_11, tuple_102);
    match_158 = call_324;
    goto end_match_568;
next_576:;
    if ((!(tokens_51))) goto next_577;
    if ((tokens_51->head.t0.tag != BracketL_)) goto next_577;
    struct IntIntTuple2 loc_24 = tokens_51->head.t1;
    if ((!(tokens_51->tail))) goto next_577;
    if ((tokens_51->tail->head.t0.tag != BracketR_)) goto next_577;
    struct Token_IntIntTuple2Tuple2List* tokens_59 = tokens_51->tail->tail;
    struct APat_ListIntIntTuple2Tuple2 tuple_104;
    tuple_104.t0 = NULL;
    tuple_104.t1 = loc_24;
    struct APat_ListIntIntTuple2Tuple2* payload_32 = (struct APat_ListIntIntTuple2Tuple2*)malloc(sizeof(struct APat_ListIntIntTuple2Tuple2));
    (*(((struct APat_ListIntIntTuple2Tuple2*)payload_32))) = tuple_104;
    struct APat_ variant_32 = (struct APat_){.tag = ListLit_, .ListLit_ = payload_32};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_103;
    tuple_103.t0 = variant_32;
    tuple_103.t1 = tokens_59;
    tuple_103.t2 = errors_39;
    match_158 = tuple_103;
    goto end_match_568;
next_577:;
    if ((!(tokens_51))) goto next_578;
    if ((tokens_51->head.t0.tag != BracketL_)) goto next_578;
    struct IntIntTuple2 loc_25 = tokens_51->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_60 = tokens_51->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_105;
    tuple_105.t0 = tokens_60;
    tuple_105.t1 = errors_39;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_325 = parsePatListBody_(baseLoc_11, loc_25, tuple_105);
    match_158 = call_325;
    goto end_match_568;
next_578:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_106;
    tuple_106.t0 = tokens_51;
    tuple_106.t1 = errors_39;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_326 = parsePatError_1((struct String){.str = "NEVER: The token must be a pat", .len = 30}, tuple_106);
    match_158 = call_326;
    goto end_match_568;
next_579:;
end_match_568:;
    return match_158;
}

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatNav_(struct IntIntTuple2 baseLoc_12, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_48) {
    struct Token_IntIntTuple2Tuple2List* tokens_61 = arg_48.t0;
    struct StringIntIntTuple2Tuple2List* errors_40 = arg_48.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_107;
    tuple_107.t0 = tokens_61;
    tuple_107.t1 = errors_40;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_327 = parsePatAtom_(baseLoc_12, tuple_107);
    struct APat_ pat_6 = call_327.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_62 = call_327.t1;
    struct StringIntIntTuple2Tuple2List* errors_41 = call_327.t2;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_160;
    if ((!(tokens_62))) goto next_584;
    if ((tokens_62->head.t0.tag != Dot_)) goto next_584;
    struct IntIntTuple2 loc_26 = tokens_62->head.t1;
    if ((!(tokens_62->tail))) goto next_584;
    if ((tokens_62->tail->head.t0.tag != Ident_)) goto next_584;
    struct String ident_11 = (*(tokens_62->tail->head.t0.Ident_));
    struct Token_IntIntTuple2Tuple2List* tokens_63 = tokens_62->tail->tail;
    struct APat_StringIntIntTuple2Tuple3 tuple_109;
    tuple_109.t0 = pat_6;
    tuple_109.t1 = ident_11;
    tuple_109.t2 = loc_26;
    struct APat_StringIntIntTuple2Tuple3* payload_33 = (struct APat_StringIntIntTuple2Tuple3*)malloc(sizeof(struct APat_StringIntIntTuple2Tuple3));
    (*(((struct APat_StringIntIntTuple2Tuple3*)payload_33))) = tuple_109;
    struct APat_ variant_33 = (struct APat_){.tag = Nav_, .Nav_ = payload_33};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_108;
    tuple_108.t0 = variant_33;
    tuple_108.t1 = tokens_63;
    tuple_108.t2 = errors_41;
    match_160 = tuple_108;
    goto end_match_583;
next_584:;
    if ((!(tokens_62))) goto next_585;
    if ((tokens_62->head.t0.tag != Dot_)) goto next_585;
    struct Token_IntIntTuple2Tuple2List* tokens_64 = tokens_62->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_110;
    tuple_110.t0 = tokens_64;
    tuple_110.t1 = errors_41;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_328 = parsePatError_1((struct String){.str = "Expected identifier", .len = 19}, tuple_110);
    match_160 = call_328;
    goto end_match_583;
next_585:;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_111;
    tuple_111.t0 = pat_6;
    tuple_111.t1 = tokens_62;
    tuple_111.t2 = errors_41;
    match_160 = tuple_111;
    goto end_match_583;
next_586:;
end_match_583:;
    return match_160;
}

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_25(struct IntIntTuple2 argBaseLoc_, struct IntIntTuple2 baseLoc_13, struct APat_List* acc_15, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_49) {
    struct Token_IntIntTuple2Tuple2List* tokens_66 = arg_49.t0;
    struct StringIntIntTuple2Tuple2List* errors_43 = arg_49.t1;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_161;
    int match_162;
    int call_329 = nextInside_1(argBaseLoc_, tokens_66);
    if ((!(call_329))) goto next_589;
    int call_330 = leadsPat_1(tokens_66);
    match_162 = call_330;
    goto end_match_588;
next_589:;
    if (call_329) goto next_590;
    match_162 = 0;
    goto end_match_588;
next_590:;
    exit(1);
end_match_588:;
    if ((!(match_162))) goto next_591;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_112;
    tuple_112.t0 = tokens_66;
    tuple_112.t1 = errors_43;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_331 = parsePatNav_(baseLoc_13, tuple_112);
    struct APat_ expr_1 = call_331.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_67 = call_331.t1;
    struct StringIntIntTuple2Tuple2List* errors_44 = call_331.t2;
    struct APat_List* list_32 = (struct APat_List*)malloc(sizeof(struct APat_List));
    list_32->head = expr_1;
    list_32->tail = acc_15;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_113;
    tuple_113.t0 = tokens_67;
    tuple_113.t1 = errors_44;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_332 = go_25(argBaseLoc_, baseLoc_13, list_32, tuple_113);
    match_161 = call_332;
    goto end_match_587;
next_591:;
    if (match_162) goto next_592;
    struct APat_List* call_333 = listRev_4(acc_15);
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_114;
    tuple_114.t0 = call_333;
    tuple_114.t1 = tokens_66;
    tuple_114.t2 = errors_43;
    match_161 = tuple_114;
    goto end_match_587;
next_592:;
    exit(1);
end_match_587:;
    return match_161;
}

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatCallArgs_(struct IntIntTuple2 baseLoc_13, struct IntIntTuple2 calleeLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_50) {
    struct Token_IntIntTuple2Tuple2List* tokens_65 = arg_50.t0;
    struct StringIntIntTuple2Tuple2List* errors_42 = arg_50.t1;
    struct IntIntTuple2 call_334 = locMax_(baseLoc_13, calleeLoc_);
    struct IntIntTuple2 call_335 = locAddX_(1, call_334);
    struct IntIntTuple2 argBaseLoc_ = call_335;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_115;
    tuple_115.t0 = tokens_65;
    tuple_115.t1 = errors_42;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_336 = go_25(argBaseLoc_, baseLoc_13, NULL, tuple_115);
    return call_336;
}

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatCall_(struct IntIntTuple2 baseLoc_14, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_51) {
    struct Token_IntIntTuple2Tuple2List* tokens_68 = arg_51.t0;
    struct StringIntIntTuple2Tuple2List* errors_45 = arg_51.t1;
    struct IntIntTuple2 call_337 = nextLoc_1(tokens_68);
    struct IntIntTuple2 calleeLoc_1 = call_337;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_116;
    tuple_116.t0 = tokens_68;
    tuple_116.t1 = errors_45;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_338 = parsePatNav_(baseLoc_14, tuple_116);
    struct APat_ callee_1 = call_338.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_69 = call_338.t1;
    struct StringIntIntTuple2Tuple2List* errors_46 = call_338.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_117;
    tuple_117.t0 = tokens_69;
    tuple_117.t1 = errors_46;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_339 = parsePatCallArgs_(baseLoc_14, calleeLoc_1, tuple_117);
    struct APat_List* args_1 = call_339.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_70 = call_339.t1;
    struct StringIntIntTuple2Tuple2List* errors_47 = call_339.t2;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_163;
    if ((!((!(args_1))))) goto next_594;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_118;
    tuple_118.t0 = callee_1;
    tuple_118.t1 = tokens_70;
    tuple_118.t2 = errors_47;
    match_163 = tuple_118;
    goto end_match_593;
next_594:;
    struct APat_APat_ListIntIntTuple2Tuple3 tuple_120;
    tuple_120.t0 = callee_1;
    tuple_120.t1 = args_1;
    tuple_120.t2 = calleeLoc_1;
    struct APat_APat_ListIntIntTuple2Tuple3* payload_34 = (struct APat_APat_ListIntIntTuple2Tuple3*)malloc(sizeof(struct APat_APat_ListIntIntTuple2Tuple3));
    (*(((struct APat_APat_ListIntIntTuple2Tuple3*)payload_34))) = tuple_120;
    struct APat_ variant_34 = (struct APat_){.tag = Call_, .Call_ = payload_34};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_119;
    tuple_119.t0 = variant_34;
    tuple_119.t1 = tokens_70;
    tuple_119.t2 = errors_47;
    match_163 = tuple_119;
    goto end_match_593;
next_595:;
end_match_593:;
    return match_163;
}

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatCons_(struct IntIntTuple2 baseLoc_15, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_52) {
    struct Token_IntIntTuple2Tuple2List* tokens_71 = arg_52.t0;
    struct StringIntIntTuple2Tuple2List* errors_48 = arg_52.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_121;
    tuple_121.t0 = tokens_71;
    tuple_121.t1 = errors_48;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_340 = parsePatCall_(baseLoc_15, tuple_121);
    struct APat_ head_2 = call_340.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_72 = call_340.t1;
    struct StringIntIntTuple2Tuple2List* errors_49 = call_340.t2;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_164;
    if ((!(tokens_72))) goto next_597;
    if ((tokens_72->head.t0.tag != ColonColon_)) goto next_597;
    struct IntIntTuple2 loc_27 = tokens_72->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_73 = tokens_72->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_122;
    tuple_122.t0 = tokens_73;
    tuple_122.t1 = errors_49;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_341 = parsePatCons_(baseLoc_15, tuple_122);
    struct APat_ tail_2 = call_341.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_74 = call_341.t1;
    struct StringIntIntTuple2Tuple2List* errors_50 = call_341.t2;
    struct APat_APat_IntIntTuple2Tuple3 tuple_124;
    tuple_124.t0 = head_2;
    tuple_124.t1 = tail_2;
    tuple_124.t2 = loc_27;
    struct APat_APat_IntIntTuple2Tuple3* payload_35 = (struct APat_APat_IntIntTuple2Tuple3*)malloc(sizeof(struct APat_APat_IntIntTuple2Tuple3));
    (*(((struct APat_APat_IntIntTuple2Tuple3*)payload_35))) = tuple_124;
    struct APat_ variant_35 = (struct APat_){.tag = Cons_2, .Cons_2 = payload_35};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_123;
    tuple_123.t0 = variant_35;
    tuple_123.t1 = tokens_74;
    tuple_123.t2 = errors_50;
    match_164 = tuple_123;
    goto end_match_596;
next_597:;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_125;
    tuple_125.t0 = head_2;
    tuple_125.t1 = tokens_72;
    tuple_125.t2 = errors_49;
    match_164 = tuple_125;
    goto end_match_596;
next_598:;
end_match_596:;
    return match_164;
}

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatAnno_(struct IntIntTuple2 baseLoc_16, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_53) {
    struct Token_IntIntTuple2Tuple2List* tokens_75 = arg_53.t0;
    struct StringIntIntTuple2Tuple2List* errors_51 = arg_53.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_126;
    tuple_126.t0 = tokens_75;
    tuple_126.t1 = errors_51;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_342 = parsePatCons_(baseLoc_16, tuple_126);
    struct APat_ pat_7 = call_342.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_76 = call_342.t1;
    struct StringIntIntTuple2Tuple2List* errors_52 = call_342.t2;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_165;
    if ((!(tokens_76))) goto next_600;
    if ((tokens_76->head.t0.tag != Colon_)) goto next_600;
    struct IntIntTuple2 loc_28 = tokens_76->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_77 = tokens_76->tail;
    struct IntIntTuple2 call_343 = nextLoc_1(tokens_77);
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_127;
    tuple_127.t0 = tokens_77;
    tuple_127.t1 = errors_52;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_344 = parseTy_(call_343, tuple_127);
    struct ATy_ ty_7 = call_344.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_78 = call_344.t1;
    struct StringIntIntTuple2Tuple2List* errors_53 = call_344.t2;
    struct APat_ATy_IntIntTuple2Tuple3 tuple_129;
    tuple_129.t0 = pat_7;
    tuple_129.t1 = ty_7;
    tuple_129.t2 = loc_28;
    struct APat_ATy_IntIntTuple2Tuple3* payload_36 = (struct APat_ATy_IntIntTuple2Tuple3*)malloc(sizeof(struct APat_ATy_IntIntTuple2Tuple3));
    (*(((struct APat_ATy_IntIntTuple2Tuple3*)payload_36))) = tuple_129;
    struct APat_ variant_36 = (struct APat_){.tag = Anno_, .Anno_ = payload_36};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_128;
    tuple_128.t0 = variant_36;
    tuple_128.t1 = tokens_78;
    tuple_128.t2 = errors_53;
    match_165 = tuple_128;
    goto end_match_599;
next_600:;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_130;
    tuple_130.t0 = pat_7;
    tuple_130.t1 = tokens_76;
    tuple_130.t2 = errors_52;
    match_165 = tuple_130;
    goto end_match_599;
next_601:;
end_match_599:;
    return match_165;
}

struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_26(struct IntIntTuple2 baseLoc_17, struct APat_List* acc_16, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_54) {
    struct Token_IntIntTuple2Tuple2List* tokens_80 = arg_54.t0;
    struct StringIntIntTuple2Tuple2List* errors_55 = arg_54.t1;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_166;
    if ((!(tokens_80))) goto next_603;
    if ((tokens_80->head.t0.tag != Comma_)) goto next_603;
    struct Token_IntIntTuple2Tuple2List* tokens_81 = tokens_80->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_131;
    tuple_131.t0 = tokens_81;
    tuple_131.t1 = errors_55;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_345 = parsePatAnno_(baseLoc_17, tuple_131);
    struct APat_ second_2 = call_345.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_82 = call_345.t1;
    struct StringIntIntTuple2Tuple2List* errors_56 = call_345.t2;
    struct APat_List* list_33 = (struct APat_List*)malloc(sizeof(struct APat_List));
    list_33->head = second_2;
    list_33->tail = acc_16;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_132;
    tuple_132.t0 = tokens_82;
    tuple_132.t1 = errors_56;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_346 = go_26(baseLoc_17, list_33, tuple_132);
    match_166 = call_346;
    goto end_match_602;
next_603:;
    struct APat_List* call_347 = listRev_4(acc_16);
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_133;
    tuple_133.t0 = call_347;
    tuple_133.t1 = tokens_80;
    tuple_133.t2 = errors_55;
    match_166 = tuple_133;
    goto end_match_602;
next_604:;
end_match_602:;
    return match_166;
}

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatTuple_(struct IntIntTuple2 baseLoc_17, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_55) {
    struct Token_IntIntTuple2Tuple2List* tokens_79 = arg_55.t0;
    struct StringIntIntTuple2Tuple2List* errors_54 = arg_55.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_134;
    tuple_134.t0 = tokens_79;
    tuple_134.t1 = errors_54;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_348 = parsePatAnno_(baseLoc_17, tuple_134);
    struct APat_ itemPat_1 = call_348.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_83 = call_348.t1;
    struct StringIntIntTuple2Tuple2List* errors_57 = call_348.t2;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_167;
    if ((!(tokens_83))) goto next_606;
    if ((tokens_83->head.t0.tag != Comma_)) goto next_606;
    struct IntIntTuple2 loc_29 = tokens_83->head.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_135;
    tuple_135.t0 = tokens_83;
    tuple_135.t1 = errors_57;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_349 = go_26(baseLoc_17, NULL, tuple_135);
    struct APat_List* itemPats_1 = call_349.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_84 = call_349.t1;
    struct StringIntIntTuple2Tuple2List* errors_58 = call_349.t2;
    struct APat_List* list_34 = (struct APat_List*)malloc(sizeof(struct APat_List));
    list_34->head = itemPat_1;
    list_34->tail = itemPats_1;
    struct APat_ListIntIntTuple2Tuple2 tuple_137;
    tuple_137.t0 = list_34;
    tuple_137.t1 = loc_29;
    struct APat_ListIntIntTuple2Tuple2* payload_37 = (struct APat_ListIntIntTuple2Tuple2*)malloc(sizeof(struct APat_ListIntIntTuple2Tuple2));
    (*(((struct APat_ListIntIntTuple2Tuple2*)payload_37))) = tuple_137;
    struct APat_ variant_37 = (struct APat_){.tag = TupleLit_, .TupleLit_ = payload_37};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_136;
    tuple_136.t0 = variant_37;
    tuple_136.t1 = tokens_84;
    tuple_136.t2 = errors_58;
    match_167 = tuple_136;
    goto end_match_605;
next_606:;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_138;
    tuple_138.t0 = itemPat_1;
    tuple_138.t1 = tokens_83;
    tuple_138.t2 = errors_57;
    match_167 = tuple_138;
    goto end_match_605;
next_607:;
end_match_605:;
    return match_167;
}

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatAs_(struct IntIntTuple2 baseLoc_18, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_56) {
    struct Token_IntIntTuple2Tuple2List* tokens_85 = arg_56.t0;
    struct StringIntIntTuple2Tuple2List* errors_59 = arg_56.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_139;
    tuple_139.t0 = tokens_85;
    tuple_139.t1 = errors_59;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_350 = parsePatTuple_(baseLoc_18, tuple_139);
    struct APat_ pat_8 = call_350.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_86 = call_350.t1;
    struct StringIntIntTuple2Tuple2List* errors_60 = call_350.t2;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_168;
    if ((!(tokens_86))) goto next_609;
    if ((tokens_86->head.t0.tag != As_)) goto next_609;
    struct IntIntTuple2 loc_30 = tokens_86->head.t1;
    if ((!(tokens_86->tail))) goto next_609;
    if ((tokens_86->tail->head.t0.tag != Ident_)) goto next_609;
    struct String ident_12 = (*(tokens_86->tail->head.t0.Ident_));
    struct Token_IntIntTuple2Tuple2List* tokens_87 = tokens_86->tail->tail;
    struct APat_StringIntIntTuple2Tuple3 tuple_141;
    tuple_141.t0 = pat_8;
    tuple_141.t1 = ident_12;
    tuple_141.t2 = loc_30;
    struct APat_StringIntIntTuple2Tuple3* payload_38 = (struct APat_StringIntIntTuple2Tuple3*)malloc(sizeof(struct APat_StringIntIntTuple2Tuple3));
    (*(((struct APat_StringIntIntTuple2Tuple3*)payload_38))) = tuple_141;
    struct APat_ variant_38 = (struct APat_){.tag = As_1, .As_1 = payload_38};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_140;
    tuple_140.t0 = variant_38;
    tuple_140.t1 = tokens_87;
    tuple_140.t2 = errors_60;
    match_168 = tuple_140;
    goto end_match_608;
next_609:;
    if ((!(tokens_86))) goto next_610;
    if ((tokens_86->head.t0.tag != As_)) goto next_610;
    struct Token_IntIntTuple2Tuple2List* tokens_88 = tokens_86->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_142;
    tuple_142.t0 = tokens_88;
    tuple_142.t1 = errors_60;
    struct StringIntIntTuple2Tuple2List* call_351 = parseNewError_1((struct String){.str = "Expected an identifier", .len = 22}, tuple_142);
    struct StringIntIntTuple2Tuple2List* errors_61 = call_351;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_143;
    tuple_143.t0 = pat_8;
    tuple_143.t1 = tokens_88;
    tuple_143.t2 = errors_61;
    match_168 = tuple_143;
    goto end_match_608;
next_610:;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_144;
    tuple_144.t0 = pat_8;
    tuple_144.t1 = tokens_86;
    tuple_144.t2 = errors_60;
    match_168 = tuple_144;
    goto end_match_608;
next_611:;
end_match_608:;
    return match_168;
}

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatOr_(struct IntIntTuple2 baseLoc_19, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_57) {
    struct Token_IntIntTuple2Tuple2List* tokens_89 = arg_57.t0;
    struct StringIntIntTuple2Tuple2List* errors_62 = arg_57.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_145;
    tuple_145.t0 = tokens_89;
    tuple_145.t1 = errors_62;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_352 = parsePatAs_(baseLoc_19, tuple_145);
    struct APat_ lPat_ = call_352.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_90 = call_352.t1;
    struct StringIntIntTuple2Tuple2List* errors_63 = call_352.t2;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_169;
    if ((!(tokens_90))) goto next_613;
    if ((tokens_90->head.t0.tag != Pipe_)) goto next_613;
    struct IntIntTuple2 loc_31 = tokens_90->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_91 = tokens_90->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_146;
    tuple_146.t0 = tokens_91;
    tuple_146.t1 = errors_63;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_353 = parsePatOr_(baseLoc_19, tuple_146);
    struct APat_ rPat_ = call_353.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_92 = call_353.t1;
    struct StringIntIntTuple2Tuple2List* errors_64 = call_353.t2;
    struct APat_APat_IntIntTuple2Tuple3 tuple_148;
    tuple_148.t0 = lPat_;
    tuple_148.t1 = rPat_;
    tuple_148.t2 = loc_31;
    struct APat_APat_IntIntTuple2Tuple3* payload_39 = (struct APat_APat_IntIntTuple2Tuple3*)malloc(sizeof(struct APat_APat_IntIntTuple2Tuple3));
    (*(((struct APat_APat_IntIntTuple2Tuple3*)payload_39))) = tuple_148;
    struct APat_ variant_39 = (struct APat_){.tag = Or_2, .Or_2 = payload_39};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_147;
    tuple_147.t0 = variant_39;
    tuple_147.t1 = tokens_92;
    tuple_147.t2 = errors_64;
    match_169 = tuple_147;
    goto end_match_612;
next_613:;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_149;
    tuple_149.t0 = lPat_;
    tuple_149.t1 = tokens_90;
    tuple_149.t2 = errors_63;
    match_169 = tuple_149;
    goto end_match_612;
next_614:;
end_match_612:;
    return match_169;
}

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePatLet_(struct IntIntTuple2 baseLoc_20, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_58) {
    struct Token_IntIntTuple2Tuple2List* tokens_93 = arg_58.t0;
    struct StringIntIntTuple2Tuple2List* errors_65 = arg_58.t1;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_170;
    if ((!(tokens_93))) goto next_616;
    if ((tokens_93->head.t0.tag != Ident_)) goto next_616;
    struct String callee_2 = (*(tokens_93->head.t0.Ident_));
    struct IntIntTuple2 calleeLoc_2 = tokens_93->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_94 = tokens_93->tail;
    int match_171;
    int call_354 = locInside_(baseLoc_20, calleeLoc_2);
    if ((!(call_354))) goto next_619;
    int call_355 = leadsPat_1(tokens_94);
    match_171 = call_355;
    goto end_match_618;
next_619:;
    if (call_354) goto next_620;
    match_171 = 0;
    goto end_match_618;
next_620:;
    exit(1);
end_match_618:;
    if ((!(match_171))) goto next_616;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_150;
    tuple_150.t0 = tokens_94;
    tuple_150.t1 = errors_65;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_356 = parsePatCallArgs_(baseLoc_20, calleeLoc_2, tuple_150);
    struct APat_List* args_2 = call_356.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_95 = call_356.t1;
    struct StringIntIntTuple2Tuple2List* errors_66 = call_356.t2;
    struct StringAPat_ListIntIntTuple2Tuple3 tuple_151;
    tuple_151.t0 = callee_2;
    tuple_151.t1 = args_2;
    tuple_151.t2 = calleeLoc_2;
    struct StringAPat_ListIntIntTuple2Tuple3* payload_40 = (struct StringAPat_ListIntIntTuple2Tuple3*)malloc(sizeof(struct StringAPat_ListIntIntTuple2Tuple3));
    (*(((struct StringAPat_ListIntIntTuple2Tuple3*)payload_40))) = tuple_151;
    struct APat_ variant_40 = (struct APat_){.tag = Fun_2, .Fun_2 = payload_40};
    struct APat_ pat_9 = variant_40;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_172;
    if ((!(tokens_95))) goto next_622;
    if ((tokens_95->head.t0.tag != Colon_)) goto next_622;
    struct IntIntTuple2 loc_32 = tokens_95->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_96 = tokens_95->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_152;
    tuple_152.t0 = tokens_96;
    tuple_152.t1 = errors_66;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_357 = parseTy_(baseLoc_20, tuple_152);
    struct ATy_ ty_8 = call_357.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_97 = call_357.t1;
    struct StringIntIntTuple2Tuple2List* errors_67 = call_357.t2;
    struct APat_ATy_IntIntTuple2Tuple3 tuple_154;
    tuple_154.t0 = pat_9;
    tuple_154.t1 = ty_8;
    tuple_154.t2 = loc_32;
    struct APat_ATy_IntIntTuple2Tuple3* payload_41 = (struct APat_ATy_IntIntTuple2Tuple3*)malloc(sizeof(struct APat_ATy_IntIntTuple2Tuple3));
    (*(((struct APat_ATy_IntIntTuple2Tuple3*)payload_41))) = tuple_154;
    struct APat_ variant_41 = (struct APat_){.tag = Anno_, .Anno_ = payload_41};
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_153;
    tuple_153.t0 = variant_41;
    tuple_153.t1 = tokens_97;
    tuple_153.t2 = errors_67;
    match_172 = tuple_153;
    goto end_match_621;
next_622:;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_155;
    tuple_155.t0 = pat_9;
    tuple_155.t1 = tokens_95;
    tuple_155.t2 = errors_66;
    match_172 = tuple_155;
    goto end_match_621;
next_623:;
end_match_621:;
    match_170 = match_172;
    goto end_match_615;
next_616:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_156;
    tuple_156.t0 = tokens_93;
    tuple_156.t1 = errors_65;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_358 = parsePat_(baseLoc_20, tuple_156);
    match_170 = call_358;
    goto end_match_615;
next_617:;
end_match_615:;
    return match_170;
}

struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePat_(struct IntIntTuple2 baseLoc_21, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_59) {
    struct Token_IntIntTuple2Tuple2List* tokens_98 = arg_59.t0;
    struct StringIntIntTuple2Tuple2List* errors_68 = arg_59.t1;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_173;
    int match_174;
    int call_359 = nextInside_1(baseLoc_21, tokens_98);
    if ((!(call_359))) goto next_626;
    int call_360 = leadsPat_1(tokens_98);
    match_174 = call_360;
    goto end_match_625;
next_626:;
    if (call_359) goto next_627;
    match_174 = 0;
    goto end_match_625;
next_627:;
    exit(1);
end_match_625:;
    if (match_174) goto next_628;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_157;
    tuple_157.t0 = tokens_98;
    tuple_157.t1 = errors_68;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_361 = parsePatError_1((struct String){.str = "Expected a pattern", .len = 18}, tuple_157);
    match_173 = call_361;
    goto end_match_624;
next_628:;
    if ((!(match_174))) goto next_629;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_158;
    tuple_158.t0 = tokens_98;
    tuple_158.t1 = errors_68;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_362 = parsePatOr_(baseLoc_21, tuple_158);
    match_173 = call_362;
    goto end_match_624;
next_629:;
    exit(1);
end_match_624:;
    return match_173;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseRange_(struct IntIntTuple2 baseLoc_22, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_60) {
    struct Token_IntIntTuple2Tuple2List* tokens_99 = arg_60.t0;
    struct StringIntIntTuple2Tuple2List* errors_69 = arg_60.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_159;
    tuple_159.t0 = tokens_99;
    tuple_159.t1 = errors_69;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_363 = parseExpr_(baseLoc_22, tuple_159);
    struct AExpr_ l_14 = call_363.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_100 = call_363.t1;
    struct StringIntIntTuple2Tuple2List* errors_70 = call_363.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_175;
    if ((!(tokens_100))) goto next_631;
    if ((tokens_100->head.t0.tag != DotDot_)) goto next_631;
    struct IntIntTuple2 loc_33 = tokens_100->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_101 = tokens_100->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_160;
    tuple_160.t0 = tokens_101;
    tuple_160.t1 = errors_70;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_364 = parseExpr_(baseLoc_22, tuple_160);
    struct AExpr_ r_27 = call_364.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_102 = call_364.t1;
    struct StringIntIntTuple2Tuple2List* errors_71 = call_364.t2;
    struct AExpr_List* list_36 = (struct AExpr_List*)malloc(sizeof(struct AExpr_List));
    list_36->head = r_27;
    list_36->tail = NULL;
    struct AExpr_List* list_35 = (struct AExpr_List*)malloc(sizeof(struct AExpr_List));
    list_35->head = l_14;
    list_35->tail = list_36;
    struct AExpr_ListIntIntTuple2Tuple2 tuple_162;
    tuple_162.t0 = list_35;
    tuple_162.t1 = loc_33;
    struct AExpr_ListIntIntTuple2Tuple2* payload_42 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_42))) = tuple_162;
    struct AExpr_ variant_42 = (struct AExpr_){.tag = Range_, .Range_ = payload_42};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_161;
    tuple_161.t0 = variant_42;
    tuple_161.t1 = tokens_102;
    tuple_161.t2 = errors_71;
    match_175 = tuple_161;
    goto end_match_630;
next_631:;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_163;
    tuple_163.t0 = l_14;
    tuple_163.t1 = tokens_100;
    tuple_163.t2 = errors_70;
    match_175 = tuple_163;
    goto end_match_630;
next_632:;
end_match_630:;
    return match_175;
}

struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct AExpr_List* t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseList_(struct IntIntTuple2 baseLoc_23, struct IntIntTuple2 bracketLoc_1, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_61) {
    struct Token_IntIntTuple2Tuple2List* tokens_103 = arg_61.t0;
    struct StringIntIntTuple2Tuple2List* errors_72 = arg_61.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_164;
    tuple_164.t0 = tokens_103;
    tuple_164.t1 = errors_72;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_365 = parseStmts_(baseLoc_23, tuple_164);
    struct AExpr_List* items_3 = call_365.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_104 = call_365.t1;
    struct StringIntIntTuple2Tuple2List* errors_73 = call_365.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 match_176;
    if ((!(tokens_104))) goto next_634;
    if ((tokens_104->head.t0.tag != BracketR_)) goto next_634;
    struct Token_IntIntTuple2Tuple2List* tokens_106 = tokens_104->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_165;
    tuple_165.t0 = tokens_106;
    tuple_165.t1 = errors_73;
    match_176 = tuple_165;
    goto end_match_633;
next_634:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_166;
    tuple_166.t0 = tokens_104;
    tuple_166.t1 = errors_73;
    struct StringIntIntTuple2Tuple2List* call_366 = parseNewError_1((struct String){.str = "Expected ']'", .len = 12}, tuple_166);
    struct StringIntIntTuple2Tuple2List* errors_75 = call_366;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_167;
    tuple_167.t0 = tokens_104;
    tuple_167.t1 = errors_75;
    match_176 = tuple_167;
    goto end_match_633;
next_635:;
end_match_633:;
    struct Token_IntIntTuple2Tuple2List* tokens_105 = match_176.t0;
    struct StringIntIntTuple2Tuple2List* errors_74 = match_176.t1;
    struct AExpr_ListIntIntTuple2Tuple2 tuple_169;
    tuple_169.t0 = items_3;
    tuple_169.t1 = bracketLoc_1;
    struct AExpr_ListIntIntTuple2Tuple2* payload_43 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_43))) = tuple_169;
    struct AExpr_ variant_43 = (struct AExpr_){.tag = ListLit_1, .ListLit_1 = payload_43};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_168;
    tuple_168.t0 = variant_43;
    tuple_168.t1 = tokens_105;
    tuple_168.t2 = errors_74;
    return tuple_168;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseThenClause_(struct IntIntTuple2 baseLoc_24, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_62) {
    struct Token_IntIntTuple2Tuple2List* tokens_107 = arg_62.t0;
    struct StringIntIntTuple2Tuple2List* errors_76 = arg_62.t1;
    struct IntIntTuple2 call_367 = locAddX_(1, baseLoc_24);
    struct IntIntTuple2 innerBaseLoc_ = call_367;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_177;
    if ((!(tokens_107))) goto next_637;
    if ((tokens_107->head.t0.tag != Then_)) goto next_637;
    struct IntIntTuple2 thenLoc_ = tokens_107->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_108 = tokens_107->tail;
    int call_368 = locInside_(baseLoc_24, thenLoc_);
    if ((!(call_368))) goto next_637;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_170;
    tuple_170.t0 = tokens_108;
    tuple_170.t1 = errors_76;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_369 = parseSemi_(innerBaseLoc_, thenLoc_, tuple_170);
    match_177 = call_369;
    goto end_match_636;
next_637:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_171;
    tuple_171.t0 = tokens_107;
    tuple_171.t1 = errors_76;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_370 = parseExprError_1((struct String){.str = "Expected 'then'", .len = 15}, tuple_171);
    match_177 = call_370;
    goto end_match_636;
next_638:;
end_match_636:;
    return match_177;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseElseClause_(struct IntIntTuple2 baseLoc_25, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_63) {
    struct Token_IntIntTuple2Tuple2List* tokens_109 = arg_63.t0;
    struct StringIntIntTuple2Tuple2List* errors_77 = arg_63.t1;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_178;
    if ((!(tokens_109))) goto next_640;
    if ((tokens_109->head.t0.tag != Else_)) goto next_640;
    struct IntIntTuple2 elseLoc_ = tokens_109->head.t1;
    if ((!(tokens_109->tail))) goto next_640;
    if ((tokens_109->tail->head.t0.tag != If_)) goto next_640;
    struct IntIntTuple2 nextIfLoc_ = tokens_109->tail->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_110 = tokens_109->tail->tail;
    int match_179;
    int call_371 = locInside_(baseLoc_25, elseLoc_);
    if ((!(call_371))) goto next_644;
    int call_372 = locIsSameRow_(elseLoc_, nextIfLoc_);
    match_179 = call_372;
    goto end_match_643;
next_644:;
    if (call_371) goto next_645;
    match_179 = 0;
    goto end_match_643;
next_645:;
    exit(1);
end_match_643:;
    if ((!(match_179))) goto next_640;
    struct Token_IntIntTuple2Tuple2 tuple_173;
    tuple_173.t0 = (struct Token_){.tag = If_};
    tuple_173.t1 = elseLoc_;
    struct Token_IntIntTuple2Tuple2List* list_37 = (struct Token_IntIntTuple2Tuple2List*)malloc(sizeof(struct Token_IntIntTuple2Tuple2List));
    list_37->head = tuple_173;
    list_37->tail = tokens_110;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_172;
    tuple_172.t0 = list_37;
    tuple_172.t1 = errors_77;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_373 = parseExpr_(baseLoc_25, tuple_172);
    match_178 = call_373;
    goto end_match_639;
next_640:;
    if ((!(tokens_109))) goto next_641;
    if ((tokens_109->head.t0.tag != Else_)) goto next_641;
    struct IntIntTuple2 elseLoc_1 = tokens_109->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_111 = tokens_109->tail;
    int call_374 = locInside_(baseLoc_25, elseLoc_1);
    if ((!(call_374))) goto next_641;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_174;
    tuple_174.t0 = tokens_111;
    tuple_174.t1 = errors_77;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_375 = parseSemi_(baseLoc_25, elseLoc_1, tuple_174);
    match_178 = call_375;
    goto end_match_639;
next_641:;
    struct IntIntTuple2* payload_44 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_44))) = baseLoc_25;
    struct AExpr_ variant_44 = (struct AExpr_){.tag = Missing_2, .Missing_2 = payload_44};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_175;
    tuple_175.t0 = variant_44;
    tuple_175.t1 = tokens_109;
    tuple_175.t2 = errors_77;
    match_178 = tuple_175;
    goto end_match_639;
next_642:;
end_match_639:;
    return match_178;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseIf_(struct IntIntTuple2 ifLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_64) {
    struct Token_IntIntTuple2Tuple2List* tokens_112 = arg_64.t0;
    struct StringIntIntTuple2Tuple2List* errors_78 = arg_64.t1;
    struct IntIntTuple2 call_376 = locAddX_(1, ifLoc_);
    struct IntIntTuple2 innerBaseLoc_1 = call_376;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_176;
    tuple_176.t0 = tokens_112;
    tuple_176.t1 = errors_78;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_377 = parseExpr_(innerBaseLoc_1, tuple_176);
    struct AExpr_ cond_1 = call_377.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_113 = call_377.t1;
    struct StringIntIntTuple2Tuple2List* errors_79 = call_377.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_177;
    tuple_177.t0 = tokens_113;
    tuple_177.t1 = errors_79;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_378 = parseThenClause_(ifLoc_, tuple_177);
    struct AExpr_ body_4 = call_378.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_114 = call_378.t1;
    struct StringIntIntTuple2Tuple2List* errors_80 = call_378.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_178;
    tuple_178.t0 = tokens_114;
    tuple_178.t1 = errors_80;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_379 = parseElseClause_(ifLoc_, tuple_178);
    struct AExpr_ alt_1 = call_379.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_115 = call_379.t1;
    struct StringIntIntTuple2Tuple2List* errors_81 = call_379.t2;
    struct AExpr_AExpr_AExpr_IntIntTuple2Tuple4 tuple_180;
    tuple_180.t0 = cond_1;
    tuple_180.t1 = body_4;
    tuple_180.t2 = alt_1;
    tuple_180.t3 = ifLoc_;
    struct AExpr_AExpr_AExpr_IntIntTuple2Tuple4* payload_45 = (struct AExpr_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct AExpr_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct AExpr_AExpr_AExpr_IntIntTuple2Tuple4*)payload_45))) = tuple_180;
    struct AExpr_ variant_45 = (struct AExpr_){.tag = If_1, .If_1 = payload_45};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_179;
    tuple_179.t0 = variant_45;
    tuple_179.t1 = tokens_115;
    tuple_179.t2 = errors_81;
    return tuple_179;
}

struct AArm_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct AArm_ t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct AArm_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseMatchArm_(struct IntIntTuple2 matchLoc_, struct IntIntTuple2 armLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_65) {
    struct Token_IntIntTuple2Tuple2List* tokens_116 = arg_65.t0;
    struct StringIntIntTuple2Tuple2List* errors_82 = arg_65.t1;
    struct IntIntTuple2 call_380 = locAddX_(1, matchLoc_);
    struct IntIntTuple2 innerBaseLoc_2 = call_380;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_181;
    tuple_181.t0 = tokens_116;
    tuple_181.t1 = errors_82;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_381 = parsePat_(innerBaseLoc_2, tuple_181);
    struct APat_ pat_10 = call_381.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_117 = call_381.t1;
    struct StringIntIntTuple2Tuple2List* errors_83 = call_381.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_180;
    if ((!(tokens_117))) goto next_647;
    if ((tokens_117->head.t0.tag != When_)) goto next_647;
    struct Token_IntIntTuple2Tuple2List* tokens_119 = tokens_117->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_182;
    tuple_182.t0 = tokens_119;
    tuple_182.t1 = errors_83;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_382 = parseExpr_(innerBaseLoc_2, tuple_182);
    match_180 = call_382;
    goto end_match_646;
next_647:;
    struct IntIntTuple2 call_383 = nextLoc_1(tokens_117);
    struct IntIntTuple2* payload_46 = (struct IntIntTuple2*)malloc(sizeof(struct IntIntTuple2));
    (*(((struct IntIntTuple2*)payload_46))) = call_383;
    struct AExpr_ variant_46 = (struct AExpr_){.tag = Missing_2, .Missing_2 = payload_46};
    struct AExpr_ guard_1 = variant_46;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_183;
    tuple_183.t0 = guard_1;
    tuple_183.t1 = tokens_117;
    tuple_183.t2 = errors_83;
    match_180 = tuple_183;
    goto end_match_646;
next_648:;
end_match_646:;
    struct AExpr_ guard_ = match_180.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_118 = match_180.t1;
    struct StringIntIntTuple2Tuple2List* errors_84 = match_180.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_181;
    if ((!(tokens_118))) goto next_650;
    if ((tokens_118->head.t0.tag != Arrow_)) goto next_650;
    struct IntIntTuple2 arrowLoc_ = tokens_118->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_121 = tokens_118->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_184;
    tuple_184.t0 = tokens_121;
    tuple_184.t1 = errors_84;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_384 = parseSemi_(matchLoc_, arrowLoc_, tuple_184);
    match_181 = call_384;
    goto end_match_649;
next_650:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_185;
    tuple_185.t0 = tokens_118;
    tuple_185.t1 = errors_84;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_385 = parseExprError_1((struct String){.str = "Expected '->'", .len = 13}, tuple_185);
    match_181 = call_385;
    goto end_match_649;
next_651:;
end_match_649:;
    struct AExpr_ body_5 = match_181.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_120 = match_181.t1;
    struct StringIntIntTuple2Tuple2List* errors_85 = match_181.t2;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4 tuple_187;
    tuple_187.t0 = pat_10;
    tuple_187.t1 = guard_;
    tuple_187.t2 = body_5;
    tuple_187.t3 = armLoc_;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4* payload_47 = (struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct APat_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)payload_47))) = tuple_187;
    struct AArm_ variant_47 = (struct AArm_){.tag = AArm_, .AArm_ = payload_47};
    struct AArm_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_186;
    tuple_186.t0 = variant_47;
    tuple_186.t1 = tokens_120;
    tuple_186.t2 = errors_85;
    return tuple_186;
}

struct AArm_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct AArm_List* t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct AArm_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_27(struct IntIntTuple2 matchLoc_1, struct AArm_List* acc_17, struct IntIntTuple2 armLoc_2, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_66) {
    struct Token_IntIntTuple2Tuple2List* tokens_127 = arg_66.t0;
    struct StringIntIntTuple2Tuple2List* errors_90 = arg_66.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_188;
    tuple_188.t0 = tokens_127;
    tuple_188.t1 = errors_90;
    struct AArm_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_386 = parseMatchArm_(matchLoc_1, armLoc_2, tuple_188);
    struct AArm_ arm_ = call_386.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_128 = call_386.t1;
    struct StringIntIntTuple2Tuple2List* errors_91 = call_386.t2;
    struct AArm_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_182;
    if ((!(tokens_128))) goto next_653;
    if ((tokens_128->head.t0.tag != Pipe_)) goto next_653;
    struct IntIntTuple2 pipeLoc_1 = tokens_128->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_129 = tokens_128->tail;
    int call_387 = locInside_(matchLoc_1, pipeLoc_1);
    if ((!(call_387))) goto next_653;
    struct AArm_List* list_38 = (struct AArm_List*)malloc(sizeof(struct AArm_List));
    list_38->head = arm_;
    list_38->tail = acc_17;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_189;
    tuple_189.t0 = tokens_129;
    tuple_189.t1 = errors_91;
    struct AArm_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_388 = go_27(matchLoc_1, list_38, pipeLoc_1, tuple_189);
    match_182 = call_388;
    goto end_match_652;
next_653:;
    struct AArm_List* list_39 = (struct AArm_List*)malloc(sizeof(struct AArm_List));
    list_39->head = arm_;
    list_39->tail = acc_17;
    struct AArm_List* call_389 = listRev_3(list_39);
    struct AArm_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_190;
    tuple_190.t0 = call_389;
    tuple_190.t1 = tokens_128;
    tuple_190.t2 = errors_91;
    match_182 = tuple_190;
    goto end_match_652;
next_654:;
end_match_652:;
    return match_182;
}

struct IntIntTuple2Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct IntIntTuple2 t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseMatch_(struct IntIntTuple2 matchLoc_1, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_67) {
    struct Token_IntIntTuple2Tuple2List* tokens_122 = arg_67.t0;
    struct StringIntIntTuple2Tuple2List* errors_86 = arg_67.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_191;
    tuple_191.t0 = tokens_122;
    tuple_191.t1 = errors_86;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_390 = parseExpr_(matchLoc_1, tuple_191);
    struct AExpr_ target_1 = call_390.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_123 = call_390.t1;
    struct StringIntIntTuple2Tuple2List* errors_87 = call_390.t2;
    struct IntIntTuple2Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_183;
    if ((!(tokens_123))) goto next_656;
    if ((tokens_123->head.t0.tag != With_)) goto next_656;
    if ((!(tokens_123->tail))) goto next_656;
    if ((tokens_123->tail->head.t0.tag != Pipe_)) goto next_656;
    struct IntIntTuple2 pipeLoc_ = tokens_123->tail->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_125 = tokens_123->tail->tail;
    struct IntIntTuple2Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_192;
    tuple_192.t0 = pipeLoc_;
    tuple_192.t1 = tokens_125;
    tuple_192.t2 = errors_87;
    match_183 = tuple_192;
    goto end_match_655;
next_656:;
    if ((!(tokens_123))) goto next_657;
    if ((tokens_123->head.t0.tag != With_)) goto next_657;
    struct IntIntTuple2 withLoc_ = tokens_123->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_126 = tokens_123->tail;
    struct IntIntTuple2Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_193;
    tuple_193.t0 = withLoc_;
    tuple_193.t1 = tokens_126;
    tuple_193.t2 = errors_87;
    match_183 = tuple_193;
    goto end_match_655;
next_657:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_194;
    tuple_194.t0 = tokens_123;
    tuple_194.t1 = errors_87;
    struct StringIntIntTuple2Tuple2List* call_391 = parseNewError_1((struct String){.str = "Expected 'with'", .len = 15}, tuple_194);
    struct StringIntIntTuple2Tuple2List* errors_89 = call_391;
    struct IntIntTuple2Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_195;
    tuple_195.t0 = matchLoc_1;
    tuple_195.t1 = tokens_123;
    tuple_195.t2 = errors_89;
    match_183 = tuple_195;
    goto end_match_655;
next_658:;
end_match_655:;
    struct IntIntTuple2 armLoc_1 = match_183.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_124 = match_183.t1;
    struct StringIntIntTuple2Tuple2List* errors_88 = match_183.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_196;
    tuple_196.t0 = tokens_124;
    tuple_196.t1 = errors_88;
    struct AArm_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_392 = go_27(matchLoc_1, NULL, armLoc_1, tuple_196);
    struct AArm_List* arms_1 = call_392.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_130 = call_392.t1;
    struct StringIntIntTuple2Tuple2List* errors_92 = call_392.t2;
    struct AExpr_AArm_ListIntIntTuple2Tuple3 tuple_198;
    tuple_198.t0 = target_1;
    tuple_198.t1 = arms_1;
    tuple_198.t2 = matchLoc_1;
    struct AExpr_AArm_ListIntIntTuple2Tuple3* payload_48 = (struct AExpr_AArm_ListIntIntTuple2Tuple3*)malloc(sizeof(struct AExpr_AArm_ListIntIntTuple2Tuple3));
    (*(((struct AExpr_AArm_ListIntIntTuple2Tuple3*)payload_48))) = tuple_198;
    struct AExpr_ variant_48 = (struct AExpr_){.tag = Match_1, .Match_1 = payload_48};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_197;
    tuple_197.t0 = variant_48;
    tuple_197.t1 = tokens_130;
    tuple_197.t2 = errors_92;
    return tuple_197;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseFun_(struct IntIntTuple2 baseLoc_26, struct IntIntTuple2 funLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_68) {
    struct Token_IntIntTuple2Tuple2List* tokens_131 = arg_68.t0;
    struct StringIntIntTuple2Tuple2List* errors_93 = arg_68.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_199;
    tuple_199.t0 = tokens_131;
    tuple_199.t1 = errors_93;
    struct APat_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_393 = parsePatCallArgs_(baseLoc_26, funLoc_, tuple_199);
    struct APat_List* pats_3 = call_393.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_132 = call_393.t1;
    struct StringIntIntTuple2Tuple2List* errors_94 = call_393.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_184;
    if ((!(tokens_132))) goto next_660;
    if ((tokens_132->head.t0.tag != Arrow_)) goto next_660;
    struct IntIntTuple2 arrowLoc_1 = tokens_132->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_134 = tokens_132->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_200;
    tuple_200.t0 = tokens_134;
    tuple_200.t1 = errors_94;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_394 = parseSemi_(baseLoc_26, arrowLoc_1, tuple_200);
    match_184 = call_394;
    goto end_match_659;
next_660:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_201;
    tuple_201.t0 = tokens_132;
    tuple_201.t1 = errors_94;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_395 = parseExprError_1((struct String){.str = "Missing '->'", .len = 12}, tuple_201);
    match_184 = call_395;
    goto end_match_659;
next_661:;
end_match_659:;
    struct AExpr_ body_6 = match_184.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_133 = match_184.t1;
    struct StringIntIntTuple2Tuple2List* errors_95 = match_184.t2;
    struct APat_ListAExpr_IntIntTuple2Tuple3 tuple_203;
    tuple_203.t0 = pats_3;
    tuple_203.t1 = body_6;
    tuple_203.t2 = funLoc_;
    struct APat_ListAExpr_IntIntTuple2Tuple3* payload_49 = (struct APat_ListAExpr_IntIntTuple2Tuple3*)malloc(sizeof(struct APat_ListAExpr_IntIntTuple2Tuple3));
    (*(((struct APat_ListAExpr_IntIntTuple2Tuple3*)payload_49))) = tuple_203;
    struct AExpr_ variant_49 = (struct AExpr_){.tag = Fun_3, .Fun_3 = payload_49};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_202;
    tuple_202.t0 = variant_49;
    tuple_202.t1 = tokens_133;
    tuple_202.t2 = errors_95;
    return tuple_202;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseParenBody_(struct IntIntTuple2 baseLoc_27, struct IntIntTuple2 parenLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_69) {
    struct Token_IntIntTuple2Tuple2List* tokens_135 = arg_69.t0;
    struct StringIntIntTuple2Tuple2List* errors_96 = arg_69.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_204;
    tuple_204.t0 = tokens_135;
    tuple_204.t1 = errors_96;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_396 = parseSemi_(baseLoc_27, parenLoc_, tuple_204);
    struct AExpr_ body_7 = call_396.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_136 = call_396.t1;
    struct StringIntIntTuple2Tuple2List* errors_97 = call_396.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_185;
    if ((!(tokens_136))) goto next_663;
    if ((tokens_136->head.t0.tag != ParenR_)) goto next_663;
    struct Token_IntIntTuple2Tuple2List* tokens_137 = tokens_136->tail;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_205;
    tuple_205.t0 = body_7;
    tuple_205.t1 = tokens_137;
    tuple_205.t2 = errors_97;
    match_185 = tuple_205;
    goto end_match_662;
next_663:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_206;
    tuple_206.t0 = tokens_136;
    tuple_206.t1 = errors_97;
    struct StringIntIntTuple2Tuple2List* call_397 = parseNewError_1((struct String){.str = "Expected ')'", .len = 12}, tuple_206);
    struct StringIntIntTuple2Tuple2List* errors_98 = call_397;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_207;
    tuple_207.t0 = body_7;
    tuple_207.t1 = tokens_136;
    tuple_207.t2 = errors_98;
    match_185 = tuple_207;
    goto end_match_662;
next_664:;
end_match_662:;
    return match_185;
}

struct Token_IntIntTuple2Tuple2List* parseAccessModifier_1(struct Token_IntIntTuple2Tuple2List* tokens_138) {
    struct Token_IntIntTuple2Tuple2List* match_186;
    if ((!(tokens_138))) goto next_666;
    struct Token_ t_11 = tokens_138->head.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_139 = tokens_138->tail;
    int call_398 = tokenIsAccessModifier_(t_11);
    if ((!(call_398))) goto next_666;
    match_186 = tokens_139;
    goto end_match_665;
next_666:;
    match_186 = tokens_138;
    goto end_match_665;
next_667:;
end_match_665:;
    return match_186;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseLet_(struct IntIntTuple2 letLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_70) {
    struct Token_IntIntTuple2Tuple2List* tokens_140 = arg_70.t0;
    struct StringIntIntTuple2Tuple2List* errors_99 = arg_70.t1;
    struct IntIntTuple2 call_399 = locAddX_(1, letLoc_);
    struct IntIntTuple2 innerBaseLoc_3 = call_399;
    struct Token_IntIntTuple2Tuple2List* call_400 = parseAccessModifier_1(tokens_140);
    struct Token_IntIntTuple2Tuple2List* tokens_141 = call_400;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_208;
    tuple_208.t0 = tokens_141;
    tuple_208.t1 = errors_99;
    struct APat_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_401 = parsePatLet_(innerBaseLoc_3, tuple_208);
    struct APat_ pat_11 = call_401.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_142 = call_401.t1;
    struct StringIntIntTuple2Tuple2List* errors_100 = call_401.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_187;
    if ((!(tokens_142))) goto next_669;
    if ((tokens_142->head.t0.tag != Eq_)) goto next_669;
    struct IntIntTuple2 eqLoc_ = tokens_142->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_144 = tokens_142->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_209;
    tuple_209.t0 = tokens_144;
    tuple_209.t1 = errors_100;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_402 = parseSemi_(innerBaseLoc_3, eqLoc_, tuple_209);
    match_187 = call_402;
    goto end_match_668;
next_669:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_210;
    tuple_210.t0 = tokens_142;
    tuple_210.t1 = errors_100;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_403 = parseExprError_1((struct String){.str = "Missing '='", .len = 11}, tuple_210);
    match_187 = call_403;
    goto end_match_668;
next_670:;
end_match_668:;
    struct AExpr_ body_8 = match_187.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_143 = match_187.t1;
    struct StringIntIntTuple2Tuple2List* errors_101 = match_187.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_188;
    if ((!(tokens_143))) goto next_672;
    if ((tokens_143->head.t0.tag != In_)) goto next_672;
    struct IntIntTuple2 inLoc_ = tokens_143->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_146 = tokens_143->tail;
    int call_404 = locInside_(letLoc_, inLoc_);
    if ((!(call_404))) goto next_672;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_211;
    tuple_211.t0 = tokens_146;
    tuple_211.t1 = errors_101;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_405 = parseSemi_(letLoc_, inLoc_, tuple_211);
    match_188 = call_405;
    goto end_match_671;
next_672:;
    if ((!(tokens_143))) goto next_673;
    struct IntIntTuple2 call_406 = nextLoc_1(tokens_143);
    int call_407 = locIsSameColumn_(call_406, letLoc_);
    if ((!(call_407))) goto next_673;
    struct IntIntTuple2 call_408 = nextLoc_1(tokens_143);
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_212;
    tuple_212.t0 = tokens_143;
    tuple_212.t1 = errors_101;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_409 = parseSemi_(letLoc_, call_408, tuple_212);
    match_188 = call_409;
    goto end_match_671;
next_673:;
    struct Token_IntIntTuple2Tuple2List* tokens_147 = tokens_143;
    struct AExpr_ListIntIntTuple2Tuple2 tuple_214;
    tuple_214.t0 = NULL;
    tuple_214.t1 = letLoc_;
    struct AExpr_ListIntIntTuple2Tuple2* payload_50 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_50))) = tuple_214;
    struct AExpr_ variant_50 = (struct AExpr_){.tag = TupleLit_1, .TupleLit_1 = payload_50};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_213;
    tuple_213.t0 = variant_50;
    tuple_213.t1 = tokens_147;
    tuple_213.t2 = errors_101;
    match_188 = tuple_213;
    goto end_match_671;
next_674:;
end_match_671:;
    struct AExpr_ next_7 = match_188.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_145 = match_188.t1;
    struct StringIntIntTuple2Tuple2List* errors_102 = match_188.t2;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4 tuple_216;
    tuple_216.t0 = pat_11;
    tuple_216.t1 = body_8;
    tuple_216.t2 = next_7;
    tuple_216.t3 = letLoc_;
    struct APat_AExpr_AExpr_IntIntTuple2Tuple4* payload_51 = (struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct APat_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct APat_AExpr_AExpr_IntIntTuple2Tuple4*)payload_51))) = tuple_216;
    struct AExpr_ variant_51 = (struct AExpr_){.tag = Let_1, .Let_1 = payload_51};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_215;
    tuple_215.t0 = variant_51;
    tuple_215.t1 = tokens_145;
    tuple_215.t2 = errors_102;
    return tuple_215;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTyDecl_(struct IntIntTuple2 typeLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_71) {
    struct Token_IntIntTuple2Tuple2List* tokens_148 = arg_71.t0;
    struct StringIntIntTuple2Tuple2List* errors_103 = arg_71.t1;
    struct IntIntTuple2 call_410 = locAddX_(1, typeLoc_);
    struct IntIntTuple2 baseLoc_28 = call_410;
    struct Token_IntIntTuple2Tuple2List* call_411 = parseAccessModifier_1(tokens_148);
    struct Token_IntIntTuple2Tuple2List* tokens_149 = call_411;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_189;
    if ((!(tokens_149))) goto next_676;
    if ((tokens_149->head.t0.tag != Ident_)) goto next_676;
    struct String tyIdent_ = (*(tokens_149->head.t0.Ident_));
    struct Token_IntIntTuple2Tuple2List* tokens_150 = tokens_149->tail;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_190;
    if ((!(tokens_150))) goto next_679;
    if ((tokens_150->head.t0.tag != Eq_)) goto next_679;
    struct Token_IntIntTuple2Tuple2List* tokens_151 = tokens_150->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_217;
    tuple_217.t0 = tokens_151;
    tuple_217.t1 = errors_103;
    struct ATyDecl_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_412 = parseTyDeclBody_(baseLoc_28, tuple_217);
    struct ATyDecl_ tyDecl_ = call_412.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_152 = call_412.t1;
    struct StringIntIntTuple2Tuple2List* errors_104 = call_412.t2;
    struct AExpr_ match_191;
    if ((tyDecl_.tag != Synonym_)) goto next_682;
    struct ATy_ ty_9 = (*(tyDecl_.Synonym_));
    struct StringATy_IntIntTuple2Tuple3 tuple_218;
    tuple_218.t0 = tyIdent_;
    tuple_218.t1 = ty_9;
    tuple_218.t2 = typeLoc_;
    struct StringATy_IntIntTuple2Tuple3* payload_52 = (struct StringATy_IntIntTuple2Tuple3*)malloc(sizeof(struct StringATy_IntIntTuple2Tuple3));
    (*(((struct StringATy_IntIntTuple2Tuple3*)payload_52))) = tuple_218;
    struct AExpr_ variant_52 = (struct AExpr_){.tag = TySynonym_, .TySynonym_ = payload_52};
    match_191 = variant_52;
    goto end_match_681;
next_682:;
    if ((tyDecl_.tag != Union_)) goto next_683;
    struct AVariant_List* variants_2 = (*(tyDecl_.Union_));
    struct StringAVariant_ListIntIntTuple2Tuple3 tuple_219;
    tuple_219.t0 = tyIdent_;
    tuple_219.t1 = variants_2;
    tuple_219.t2 = typeLoc_;
    struct StringAVariant_ListIntIntTuple2Tuple3* payload_53 = (struct StringAVariant_ListIntIntTuple2Tuple3*)malloc(sizeof(struct StringAVariant_ListIntIntTuple2Tuple3));
    (*(((struct StringAVariant_ListIntIntTuple2Tuple3*)payload_53))) = tuple_219;
    struct AExpr_ variant_53 = (struct AExpr_){.tag = TyUnion_, .TyUnion_ = payload_53};
    match_191 = variant_53;
    goto end_match_681;
next_683:;
    exit(1);
end_match_681:;
    struct AExpr_ expr_2 = match_191;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_220;
    tuple_220.t0 = expr_2;
    tuple_220.t1 = tokens_152;
    tuple_220.t2 = errors_104;
    match_190 = tuple_220;
    goto end_match_678;
next_679:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_221;
    tuple_221.t0 = tokens_150;
    tuple_221.t1 = errors_103;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_413 = parseTyError_1((struct String){.str = "Expected '='", .len = 12}, tuple_221);
    struct ATy_ ty_10 = call_413.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_153 = call_413.t1;
    struct StringIntIntTuple2Tuple2List* errors_105 = call_413.t2;
    struct StringATy_IntIntTuple2Tuple3 tuple_223;
    tuple_223.t0 = tyIdent_;
    tuple_223.t1 = ty_10;
    tuple_223.t2 = typeLoc_;
    struct StringATy_IntIntTuple2Tuple3* payload_54 = (struct StringATy_IntIntTuple2Tuple3*)malloc(sizeof(struct StringATy_IntIntTuple2Tuple3));
    (*(((struct StringATy_IntIntTuple2Tuple3*)payload_54))) = tuple_223;
    struct AExpr_ variant_54 = (struct AExpr_){.tag = TySynonym_, .TySynonym_ = payload_54};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_222;
    tuple_222.t0 = variant_54;
    tuple_222.t1 = tokens_153;
    tuple_222.t2 = errors_105;
    match_190 = tuple_222;
    goto end_match_678;
next_680:;
end_match_678:;
    match_189 = match_190;
    goto end_match_675;
next_676:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_224;
    tuple_224.t0 = tokens_149;
    tuple_224.t1 = errors_103;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_414 = parseExprError_1((struct String){.str = "Expected identifier", .len = 19}, tuple_224);
    match_189 = call_414;
    goto end_match_675;
next_677:;
end_match_675:;
    return match_189;
}

struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 {
    struct StringList* t0;
    struct Token_IntIntTuple2Tuple2List* t1;
    struct StringIntIntTuple2Tuple2List* t2;
};

struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_28(struct StringList* acc_18, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_72) {
    struct Token_IntIntTuple2Tuple2List* tokens_156 = arg_72.t0;
    struct StringIntIntTuple2Tuple2List* errors_108 = arg_72.t1;
    struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_192;
    if ((!(tokens_156))) goto next_685;
    if ((tokens_156->head.t0.tag != Dot_)) goto next_685;
    if ((!(tokens_156->tail))) goto next_685;
    if ((tokens_156->tail->head.t0.tag != Ident_)) goto next_685;
    struct String ident_13 = (*(tokens_156->tail->head.t0.Ident_));
    struct Token_IntIntTuple2Tuple2List* tokens_157 = tokens_156->tail->tail;
    struct StringList* list_40 = (struct StringList*)malloc(sizeof(struct StringList));
    list_40->head = ident_13;
    list_40->tail = acc_18;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_225;
    tuple_225.t0 = tokens_157;
    tuple_225.t1 = errors_108;
    struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_415 = go_28(list_40, tuple_225);
    match_192 = call_415;
    goto end_match_684;
next_685:;
    if ((!(tokens_156))) goto next_686;
    if ((tokens_156->head.t0.tag != Dot_)) goto next_686;
    struct Token_IntIntTuple2Tuple2List* tokens_158 = tokens_156->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_226;
    tuple_226.t0 = tokens_158;
    tuple_226.t1 = errors_108;
    struct StringIntIntTuple2Tuple2List* call_416 = parseNewError_1((struct String){.str = "Expected identifier", .len = 19}, tuple_226);
    struct StringIntIntTuple2Tuple2List* errors_109 = call_416;
    struct StringList* call_417 = listRev_2(acc_18);
    struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_227;
    tuple_227.t0 = call_417;
    tuple_227.t1 = tokens_158;
    tuple_227.t2 = errors_109;
    match_192 = tuple_227;
    goto end_match_684;
next_686:;
    struct StringList* call_418 = listRev_2(acc_18);
    struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_228;
    tuple_228.t0 = call_418;
    tuple_228.t1 = tokens_156;
    tuple_228.t2 = errors_108;
    match_192 = tuple_228;
    goto end_match_684;
next_687:;
end_match_684:;
    return match_192;
}

struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePath_(struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_73) {
    struct Token_IntIntTuple2Tuple2List* tokens_155 = arg_73.t0;
    struct StringIntIntTuple2Tuple2List* errors_107 = arg_73.t1;
    struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_193;
    if ((!(tokens_155))) goto next_689;
    if ((tokens_155->head.t0.tag != Ident_)) goto next_689;
    struct String ident_14 = (*(tokens_155->head.t0.Ident_));
    struct Token_IntIntTuple2Tuple2List* tokens_159 = tokens_155->tail;
    struct StringList* list_41 = (struct StringList*)malloc(sizeof(struct StringList));
    list_41->head = ident_14;
    list_41->tail = NULL;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_229;
    tuple_229.t0 = tokens_159;
    tuple_229.t1 = errors_107;
    struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_419 = go_28(list_41, tuple_229);
    match_193 = call_419;
    goto end_match_688;
next_689:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_230;
    tuple_230.t0 = tokens_155;
    tuple_230.t1 = errors_107;
    struct StringIntIntTuple2Tuple2List* call_420 = parseNewError_1((struct String){.str = "Expected identifier", .len = 19}, tuple_230);
    struct StringIntIntTuple2Tuple2List* errors_110 = call_420;
    struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_231;
    tuple_231.t0 = NULL;
    tuple_231.t1 = tokens_155;
    tuple_231.t2 = errors_110;
    match_193 = tuple_231;
    goto end_match_688;
next_690:;
end_match_688:;
    return match_193;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseOpen_(struct IntIntTuple2 openLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_74) {
    struct Token_IntIntTuple2Tuple2List* tokens_154 = arg_74.t0;
    struct StringIntIntTuple2Tuple2List* errors_106 = arg_74.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_232;
    tuple_232.t0 = tokens_154;
    tuple_232.t1 = errors_106;
    struct StringListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_421 = parsePath_(tuple_232);
    struct StringList* path_1 = call_421.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_160 = call_421.t1;
    struct StringIntIntTuple2Tuple2List* errors_111 = call_421.t2;
    struct StringListIntIntTuple2Tuple2 tuple_234;
    tuple_234.t0 = path_1;
    tuple_234.t1 = openLoc_;
    struct StringListIntIntTuple2Tuple2* payload_55 = (struct StringListIntIntTuple2Tuple2*)malloc(sizeof(struct StringListIntIntTuple2Tuple2));
    (*(((struct StringListIntIntTuple2Tuple2*)payload_55))) = tuple_234;
    struct AExpr_ variant_55 = (struct AExpr_){.tag = Open_1, .Open_1 = payload_55};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_233;
    tuple_233.t0 = variant_55;
    tuple_233.t1 = tokens_160;
    tuple_233.t2 = errors_111;
    return tuple_233;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseAtom_(struct IntIntTuple2 baseLoc_29, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_75) {
    struct Token_IntIntTuple2Tuple2List* tokens_161 = arg_75.t0;
    struct StringIntIntTuple2Tuple2List* errors_112 = arg_75.t1;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_194;
    int call_422 = nextInside_1(baseLoc_29, tokens_161);
    if (call_422) goto next_692;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_235;
    tuple_235.t0 = tokens_161;
    tuple_235.t1 = errors_112;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_423 = parseExprError_1((struct String){.str = "Expected an expression", .len = 22}, tuple_235);
    match_194 = call_423;
    goto end_match_691;
next_692:;
    if ((!(tokens_161))) goto next_693;
    if ((tokens_161->head.t0.tag != ParenL_)) goto next_693;
    struct IntIntTuple2 loc_34 = tokens_161->head.t1;
    if ((!(tokens_161->tail))) goto next_693;
    if ((tokens_161->tail->head.t0.tag != ParenR_)) goto next_693;
    struct Token_IntIntTuple2Tuple2List* tokens_162 = tokens_161->tail->tail;
    struct AExpr_ListIntIntTuple2Tuple2 tuple_237;
    tuple_237.t0 = NULL;
    tuple_237.t1 = loc_34;
    struct AExpr_ListIntIntTuple2Tuple2* payload_56 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_56))) = tuple_237;
    struct AExpr_ variant_56 = (struct AExpr_){.tag = TupleLit_1, .TupleLit_1 = payload_56};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_236;
    tuple_236.t0 = variant_56;
    tuple_236.t1 = tokens_162;
    tuple_236.t2 = errors_112;
    match_194 = tuple_236;
    goto end_match_691;
next_693:;
    if ((!(tokens_161))) goto next_694;
    if ((tokens_161->head.t0.tag != Bool_1)) goto next_694;
    int value_11 = (*(tokens_161->head.t0.Bool_1));
    struct IntIntTuple2 loc_35 = tokens_161->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_163 = tokens_161->tail;
    int* payload_57 = (int*)malloc(sizeof(int));
    (*(((int*)payload_57))) = value_11;
    struct Lit_ variant_57 = (struct Lit_){.tag = Bool_, .Bool_ = payload_57};
    struct Lit_IntIntTuple2Tuple2 tuple_239;
    tuple_239.t0 = variant_57;
    tuple_239.t1 = loc_35;
    struct Lit_IntIntTuple2Tuple2* payload_58 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_58))) = tuple_239;
    struct AExpr_ variant_58 = (struct AExpr_){.tag = Lit_1, .Lit_1 = payload_58};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_238;
    tuple_238.t0 = variant_58;
    tuple_238.t1 = tokens_163;
    tuple_238.t2 = errors_112;
    match_194 = tuple_238;
    goto end_match_691;
next_694:;
    if ((!(tokens_161))) goto next_695;
    if ((tokens_161->head.t0.tag != Int_1)) goto next_695;
    int value_12 = (*(tokens_161->head.t0.Int_1));
    struct IntIntTuple2 loc_36 = tokens_161->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_164 = tokens_161->tail;
    int* payload_59 = (int*)malloc(sizeof(int));
    (*(((int*)payload_59))) = value_12;
    struct Lit_ variant_59 = (struct Lit_){.tag = Int_, .Int_ = payload_59};
    struct Lit_IntIntTuple2Tuple2 tuple_241;
    tuple_241.t0 = variant_59;
    tuple_241.t1 = loc_36;
    struct Lit_IntIntTuple2Tuple2* payload_60 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_60))) = tuple_241;
    struct AExpr_ variant_60 = (struct AExpr_){.tag = Lit_1, .Lit_1 = payload_60};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_240;
    tuple_240.t0 = variant_60;
    tuple_240.t1 = tokens_164;
    tuple_240.t2 = errors_112;
    match_194 = tuple_240;
    goto end_match_691;
next_695:;
    if ((!(tokens_161))) goto next_696;
    if ((tokens_161->head.t0.tag != Char_1)) goto next_696;
    char value_13 = (*(tokens_161->head.t0.Char_1));
    struct IntIntTuple2 loc_37 = tokens_161->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_165 = tokens_161->tail;
    char* payload_61 = (char*)malloc(sizeof(char));
    (*(((char*)payload_61))) = value_13;
    struct Lit_ variant_61 = (struct Lit_){.tag = Char_, .Char_ = payload_61};
    struct Lit_IntIntTuple2Tuple2 tuple_243;
    tuple_243.t0 = variant_61;
    tuple_243.t1 = loc_37;
    struct Lit_IntIntTuple2Tuple2* payload_62 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_62))) = tuple_243;
    struct AExpr_ variant_62 = (struct AExpr_){.tag = Lit_1, .Lit_1 = payload_62};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_242;
    tuple_242.t0 = variant_62;
    tuple_242.t1 = tokens_165;
    tuple_242.t2 = errors_112;
    match_194 = tuple_242;
    goto end_match_691;
next_696:;
    if ((!(tokens_161))) goto next_697;
    if ((tokens_161->head.t0.tag != Str_1)) goto next_697;
    struct String value_14 = (*(tokens_161->head.t0.Str_1));
    struct IntIntTuple2 loc_38 = tokens_161->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_166 = tokens_161->tail;
    struct String* payload_63 = (struct String*)malloc(sizeof(struct String));
    (*(((struct String*)payload_63))) = value_14;
    struct Lit_ variant_63 = (struct Lit_){.tag = Str_, .Str_ = payload_63};
    struct Lit_IntIntTuple2Tuple2 tuple_245;
    tuple_245.t0 = variant_63;
    tuple_245.t1 = loc_38;
    struct Lit_IntIntTuple2Tuple2* payload_64 = (struct Lit_IntIntTuple2Tuple2*)malloc(sizeof(struct Lit_IntIntTuple2Tuple2));
    (*(((struct Lit_IntIntTuple2Tuple2*)payload_64))) = tuple_245;
    struct AExpr_ variant_64 = (struct AExpr_){.tag = Lit_1, .Lit_1 = payload_64};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_244;
    tuple_244.t0 = variant_64;
    tuple_244.t1 = tokens_166;
    tuple_244.t2 = errors_112;
    match_194 = tuple_244;
    goto end_match_691;
next_697:;
    if ((!(tokens_161))) goto next_698;
    if ((tokens_161->head.t0.tag != Ident_)) goto next_698;
    struct String ident_15 = (*(tokens_161->head.t0.Ident_));
    struct IntIntTuple2 loc_39 = tokens_161->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_167 = tokens_161->tail;
    struct StringIntIntTuple2Tuple2 tuple_247;
    tuple_247.t0 = ident_15;
    tuple_247.t1 = loc_39;
    struct StringIntIntTuple2Tuple2* payload_65 = (struct StringIntIntTuple2Tuple2*)malloc(sizeof(struct StringIntIntTuple2Tuple2));
    (*(((struct StringIntIntTuple2Tuple2*)payload_65))) = tuple_247;
    struct AExpr_ variant_65 = (struct AExpr_){.tag = Ident_3, .Ident_3 = payload_65};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_246;
    tuple_246.t0 = variant_65;
    tuple_246.t1 = tokens_167;
    tuple_246.t2 = errors_112;
    match_194 = tuple_246;
    goto end_match_691;
next_698:;
    if ((!(tokens_161))) goto next_699;
    if ((tokens_161->head.t0.tag != ParenL_)) goto next_699;
    struct IntIntTuple2 parenLoc_1 = tokens_161->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_168 = tokens_161->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_248;
    tuple_248.t0 = tokens_168;
    tuple_248.t1 = errors_112;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_424 = parseParenBody_(baseLoc_29, parenLoc_1, tuple_248);
    match_194 = call_424;
    goto end_match_691;
next_699:;
    if ((!(tokens_161))) goto next_700;
    if ((tokens_161->head.t0.tag != BracketL_)) goto next_700;
    struct IntIntTuple2 bracketLoc_2 = tokens_161->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_169 = tokens_161->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_249;
    tuple_249.t0 = tokens_169;
    tuple_249.t1 = errors_112;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_425 = parseList_(baseLoc_29, bracketLoc_2, tuple_249);
    match_194 = call_425;
    goto end_match_691;
next_700:;
    if ((!(tokens_161))) goto next_701;
    if ((tokens_161->head.t0.tag != If_)) goto next_701;
    struct IntIntTuple2 loc_40 = tokens_161->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_170 = tokens_161->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_250;
    tuple_250.t0 = tokens_170;
    tuple_250.t1 = errors_112;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_426 = parseIf_(loc_40, tuple_250);
    match_194 = call_426;
    goto end_match_691;
next_701:;
    if ((!(tokens_161))) goto next_702;
    if ((tokens_161->head.t0.tag != Match_)) goto next_702;
    struct IntIntTuple2 loc_41 = tokens_161->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_171 = tokens_161->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_251;
    tuple_251.t0 = tokens_171;
    tuple_251.t1 = errors_112;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_427 = parseMatch_(loc_41, tuple_251);
    match_194 = call_427;
    goto end_match_691;
next_702:;
    if ((!(tokens_161))) goto next_703;
    if ((tokens_161->head.t0.tag != Fun_)) goto next_703;
    struct IntIntTuple2 loc_42 = tokens_161->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_172 = tokens_161->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_252;
    tuple_252.t0 = tokens_172;
    tuple_252.t1 = errors_112;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_428 = parseFun_(baseLoc_29, loc_42, tuple_252);
    match_194 = call_428;
    goto end_match_691;
next_703:;
    if ((!(tokens_161))) goto next_704;
    if ((tokens_161->head.t0.tag != Let_)) goto next_704;
    struct IntIntTuple2 letLoc_1 = tokens_161->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_173 = tokens_161->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_253;
    tuple_253.t0 = tokens_173;
    tuple_253.t1 = errors_112;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_429 = parseLet_(letLoc_1, tuple_253);
    match_194 = call_429;
    goto end_match_691;
next_704:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_254;
    tuple_254.t0 = tokens_161;
    tuple_254.t1 = errors_112;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_430 = parseExprError_1((struct String){.str = "Expected an expression", .len = 22}, tuple_254);
    match_194 = call_430;
    goto end_match_691;
next_705:;
end_match_691:;
    return match_194;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_29(struct IntIntTuple2 baseLoc_30, struct AExpr_ acc_19, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_76) {
    struct Token_IntIntTuple2Tuple2List* tokens_176 = arg_76.t0;
    struct StringIntIntTuple2Tuple2List* errors_115 = arg_76.t1;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_195;
    if ((!(tokens_176))) goto next_707;
    if ((tokens_176->head.t0.tag != Dot_)) goto next_707;
    struct IntIntTuple2 loc_43 = tokens_176->head.t1;
    if ((!(tokens_176->tail))) goto next_707;
    if ((tokens_176->tail->head.t0.tag != BracketL_)) goto next_707;
    struct Token_IntIntTuple2Tuple2List* tokens_177 = tokens_176->tail->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_255;
    tuple_255.t0 = tokens_177;
    tuple_255.t1 = errors_115;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_431 = parseRange_(baseLoc_30, tuple_255);
    struct AExpr_ r_28 = call_431.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_178 = call_431.t1;
    struct StringIntIntTuple2Tuple2List* errors_116 = call_431.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 match_196;
    if ((!(tokens_178))) goto next_712;
    if ((tokens_178->head.t0.tag != BracketR_)) goto next_712;
    struct Token_IntIntTuple2Tuple2List* tokens_180 = tokens_178->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_256;
    tuple_256.t0 = tokens_180;
    tuple_256.t1 = errors_116;
    match_196 = tuple_256;
    goto end_match_711;
next_712:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_257;
    tuple_257.t0 = tokens_178;
    tuple_257.t1 = errors_116;
    struct StringIntIntTuple2Tuple2List* call_432 = parseNewError_1((struct String){.str = "Expected closing ']'", .len = 20}, tuple_257);
    struct StringIntIntTuple2Tuple2List* errors_118 = call_432;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_258;
    tuple_258.t0 = tokens_178;
    tuple_258.t1 = errors_118;
    match_196 = tuple_258;
    goto end_match_711;
next_713:;
end_match_711:;
    struct Token_IntIntTuple2Tuple2List* tokens_179 = match_196.t0;
    struct StringIntIntTuple2Tuple2List* errors_117 = match_196.t1;
    struct AExpr_AExpr_IntIntTuple2Tuple3 tuple_259;
    tuple_259.t0 = acc_19;
    tuple_259.t1 = r_28;
    tuple_259.t2 = loc_43;
    struct AExpr_AExpr_IntIntTuple2Tuple3* payload_66 = (struct AExpr_AExpr_IntIntTuple2Tuple3*)malloc(sizeof(struct AExpr_AExpr_IntIntTuple2Tuple3));
    (*(((struct AExpr_AExpr_IntIntTuple2Tuple3*)payload_66))) = tuple_259;
    struct AExpr_ variant_66 = (struct AExpr_){.tag = Index_, .Index_ = payload_66};
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_260;
    tuple_260.t0 = tokens_179;
    tuple_260.t1 = errors_117;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_433 = go_29(baseLoc_30, variant_66, tuple_260);
    match_195 = call_433;
    goto end_match_706;
next_707:;
    if ((!(tokens_176))) goto next_708;
    if ((tokens_176->head.t0.tag != Dot_)) goto next_708;
    struct IntIntTuple2 loc_44 = tokens_176->head.t1;
    if ((!(tokens_176->tail))) goto next_708;
    if ((tokens_176->tail->head.t0.tag != Ident_)) goto next_708;
    struct String r_29 = (*(tokens_176->tail->head.t0.Ident_));
    struct Token_IntIntTuple2Tuple2List* tokens_181 = tokens_176->tail->tail;
    struct AExpr_StringIntIntTuple2Tuple3 tuple_261;
    tuple_261.t0 = acc_19;
    tuple_261.t1 = r_29;
    tuple_261.t2 = loc_44;
    struct AExpr_StringIntIntTuple2Tuple3* payload_67 = (struct AExpr_StringIntIntTuple2Tuple3*)malloc(sizeof(struct AExpr_StringIntIntTuple2Tuple3));
    (*(((struct AExpr_StringIntIntTuple2Tuple3*)payload_67))) = tuple_261;
    struct AExpr_ variant_67 = (struct AExpr_){.tag = Nav_1, .Nav_1 = payload_67};
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_262;
    tuple_262.t0 = tokens_181;
    tuple_262.t1 = errors_115;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_434 = go_29(baseLoc_30, variant_67, tuple_262);
    match_195 = call_434;
    goto end_match_706;
next_708:;
    if ((!(tokens_176))) goto next_709;
    if ((tokens_176->head.t0.tag != Dot_)) goto next_709;
    struct Token_IntIntTuple2Tuple2List* tokens_182 = tokens_176->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_263;
    tuple_263.t0 = tokens_182;
    tuple_263.t1 = errors_115;
    struct StringIntIntTuple2Tuple2List* call_435 = parseNewError_1((struct String){.str = "Expected .[] or .field", .len = 22}, tuple_263);
    struct StringIntIntTuple2Tuple2List* errors_119 = call_435;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_264;
    tuple_264.t0 = acc_19;
    tuple_264.t1 = tokens_182;
    tuple_264.t2 = errors_119;
    match_195 = tuple_264;
    goto end_match_706;
next_709:;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_265;
    tuple_265.t0 = acc_19;
    tuple_265.t1 = tokens_176;
    tuple_265.t2 = errors_115;
    match_195 = tuple_265;
    goto end_match_706;
next_710:;
end_match_706:;
    return match_195;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseSuffix_(struct IntIntTuple2 baseLoc_30, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_77) {
    struct Token_IntIntTuple2Tuple2List* tokens_174 = arg_77.t0;
    struct StringIntIntTuple2Tuple2List* errors_113 = arg_77.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_266;
    tuple_266.t0 = tokens_174;
    tuple_266.t1 = errors_113;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_436 = parseAtom_(baseLoc_30, tuple_266);
    struct AExpr_ l_15 = call_436.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_175 = call_436.t1;
    struct StringIntIntTuple2Tuple2List* errors_114 = call_436.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_267;
    tuple_267.t0 = tokens_175;
    tuple_267.t1 = errors_114;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_437 = go_29(baseLoc_30, l_15, tuple_267);
    return call_437;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_30(struct IntIntTuple2 argBaseLoc_1, struct IntIntTuple2 calleeLoc_3, struct IntIntTuple2 baseLoc_31, struct AExpr_ callee_4, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_78) {
    struct Token_IntIntTuple2Tuple2List* tokens_185 = arg_78.t0;
    struct StringIntIntTuple2Tuple2List* errors_122 = arg_78.t1;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_197;
    int match_198;
    int call_438 = nextInside_1(argBaseLoc_1, tokens_185);
    if ((!(call_438))) goto next_716;
    int call_439 = leadsArg_1(tokens_185);
    match_198 = call_439;
    goto end_match_715;
next_716:;
    if (call_438) goto next_717;
    match_198 = 0;
    goto end_match_715;
next_717:;
    exit(1);
end_match_715:;
    if ((!(match_198))) goto next_718;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_268;
    tuple_268.t0 = tokens_185;
    tuple_268.t1 = errors_122;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_440 = parseSuffix_(baseLoc_31, tuple_268);
    struct AExpr_ arg_1 = call_440.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_186 = call_440.t1;
    struct StringIntIntTuple2Tuple2List* errors_123 = call_440.t2;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_269;
    tuple_269.t0 = (struct Op_){.tag = App_};
    tuple_269.t1 = callee_4;
    tuple_269.t2 = arg_1;
    tuple_269.t3 = calleeLoc_3;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_68 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_68))) = tuple_269;
    struct AExpr_ variant_68 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_68};
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_270;
    tuple_270.t0 = tokens_186;
    tuple_270.t1 = errors_123;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_441 = go_30(argBaseLoc_1, calleeLoc_3, baseLoc_31, variant_68, tuple_270);
    match_197 = call_441;
    goto end_match_714;
next_718:;
    if (match_198) goto next_719;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_271;
    tuple_271.t0 = callee_4;
    tuple_271.t1 = tokens_185;
    tuple_271.t2 = errors_122;
    match_197 = tuple_271;
    goto end_match_714;
next_719:;
    exit(1);
end_match_714:;
    return match_197;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseApp_(struct IntIntTuple2 baseLoc_31, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_79) {
    struct Token_IntIntTuple2Tuple2List* tokens_183 = arg_79.t0;
    struct StringIntIntTuple2Tuple2List* errors_120 = arg_79.t1;
    struct IntIntTuple2 call_442 = nextLoc_1(tokens_183);
    struct IntIntTuple2 calleeLoc_3 = call_442;
    struct IntIntTuple2 call_443 = locAddX_(1, calleeLoc_3);
    struct IntIntTuple2 argBaseLoc_1 = call_443;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_272;
    tuple_272.t0 = tokens_183;
    tuple_272.t1 = errors_120;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_444 = parseSuffix_(baseLoc_31, tuple_272);
    struct AExpr_ callee_3 = call_444.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_184 = call_444.t1;
    struct StringIntIntTuple2Tuple2List* errors_121 = call_444.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_273;
    tuple_273.t0 = tokens_184;
    tuple_273.t1 = errors_121;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_445 = go_30(argBaseLoc_1, calleeLoc_3, baseLoc_31, callee_3, tuple_273);
    return call_445;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parsePrefix_(struct IntIntTuple2 baseLoc_32, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_80) {
    struct Token_IntIntTuple2Tuple2List* tokens_187 = arg_80.t0;
    struct StringIntIntTuple2Tuple2List* errors_124 = arg_80.t1;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_199;
    if ((!(tokens_187))) goto next_721;
    if ((tokens_187->head.t0.tag != Minus_)) goto next_721;
    struct IntIntTuple2 loc_45 = tokens_187->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_188 = tokens_187->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_274;
    tuple_274.t0 = tokens_188;
    tuple_274.t1 = errors_124;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_446 = parseApp_(baseLoc_32, tuple_274);
    struct AExpr_ arg_2 = call_446.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_189 = call_446.t1;
    struct StringIntIntTuple2Tuple2List* errors_125 = call_446.t2;
    struct UniOp_AExpr_IntIntTuple2Tuple3 tuple_276;
    tuple_276.t0 = (struct UniOp_){.tag = Neg_};
    tuple_276.t1 = arg_2;
    tuple_276.t2 = loc_45;
    struct UniOp_AExpr_IntIntTuple2Tuple3* payload_69 = (struct UniOp_AExpr_IntIntTuple2Tuple3*)malloc(sizeof(struct UniOp_AExpr_IntIntTuple2Tuple3));
    (*(((struct UniOp_AExpr_IntIntTuple2Tuple3*)payload_69))) = tuple_276;
    struct AExpr_ variant_69 = (struct AExpr_){.tag = Uni_, .Uni_ = payload_69};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_275;
    tuple_275.t0 = variant_69;
    tuple_275.t1 = tokens_189;
    tuple_275.t2 = errors_125;
    match_199 = tuple_275;
    goto end_match_720;
next_721:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_277;
    tuple_277.t0 = tokens_187;
    tuple_277.t1 = errors_124;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_447 = parseApp_(baseLoc_32, tuple_277);
    match_199 = call_447;
    goto end_match_720;
next_722:;
end_match_720:;
    return match_199;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseNextLevelOp_(struct OpLevel_ level_1, struct IntIntTuple2 baseLoc_33, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_81) {
    struct Token_IntIntTuple2Tuple2List* tokens_190 = arg_81.t0;
    struct StringIntIntTuple2Tuple2List* errors_126 = arg_81.t1;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_200;
    struct OpLevel_ call_448 = opLevelToNext_(level_1);
    if ((call_448.tag != Prefix_)) goto next_724;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_278;
    tuple_278.t0 = tokens_190;
    tuple_278.t1 = errors_126;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_449 = parsePrefix_(baseLoc_33, tuple_278);
    match_200 = call_449;
    goto end_match_723;
next_724:;
    struct OpLevel_ nextLevel_ = call_448;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_279;
    tuple_279.t0 = tokens_190;
    tuple_279.t1 = errors_126;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_450 = parseOp_(nextLevel_, baseLoc_33, tuple_279);
    match_200 = call_450;
    goto end_match_723;
next_725:;
end_match_723:;
    return match_200;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 nextL_(struct IntIntTuple2 baseLoc_34, struct OpLevel_ level_2, struct AExpr_ expr_3, struct Op_ op_, struct IntIntTuple2 opLoc_2, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_82) {
    struct Token_IntIntTuple2Tuple2List* tokens_192 = arg_82.t0;
    struct StringIntIntTuple2Tuple2List* errors_128 = arg_82.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_280;
    tuple_280.t0 = tokens_192;
    tuple_280.t1 = errors_128;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_451 = parseNextLevelOp_(level_2, baseLoc_34, tuple_280);
    struct AExpr_ second_3 = call_451.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_193 = call_451.t1;
    struct StringIntIntTuple2Tuple2List* errors_129 = call_451.t2;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_281;
    tuple_281.t0 = op_;
    tuple_281.t1 = expr_3;
    tuple_281.t2 = second_3;
    tuple_281.t3 = opLoc_2;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_70 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_70))) = tuple_281;
    struct AExpr_ variant_70 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_70};
    struct AExpr_ expr_4 = variant_70;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_282;
    tuple_282.t0 = tokens_193;
    tuple_282.t1 = errors_129;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_452 = parseOps_(level_2, baseLoc_34, expr_4, tuple_282);
    return call_452;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 nextR_(struct IntIntTuple2 baseLoc_34, struct OpLevel_ level_2, struct AExpr_ expr_5, struct Op_ op_1, struct IntIntTuple2 opLoc_3, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_83) {
    struct Token_IntIntTuple2Tuple2List* tokens_194 = arg_83.t0;
    struct StringIntIntTuple2Tuple2List* errors_130 = arg_83.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_283;
    tuple_283.t0 = tokens_194;
    tuple_283.t1 = errors_130;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_453 = parseOp_(level_2, baseLoc_34, tuple_283);
    struct AExpr_ second_4 = call_453.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_195 = call_453.t1;
    struct StringIntIntTuple2Tuple2List* errors_131 = call_453.t2;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4 tuple_284;
    tuple_284.t0 = op_1;
    tuple_284.t1 = expr_5;
    tuple_284.t2 = second_4;
    tuple_284.t3 = opLoc_3;
    struct Op_AExpr_AExpr_IntIntTuple2Tuple4* payload_71 = (struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)malloc(sizeof(struct Op_AExpr_AExpr_IntIntTuple2Tuple4));
    (*(((struct Op_AExpr_AExpr_IntIntTuple2Tuple4*)payload_71))) = tuple_284;
    struct AExpr_ variant_71 = (struct AExpr_){.tag = Bin_, .Bin_ = payload_71};
    struct AExpr_ expr_6 = variant_71;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_285;
    tuple_285.t0 = tokens_195;
    tuple_285.t1 = errors_131;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_454 = parseOps_(level_2, baseLoc_34, expr_6, tuple_285);
    return call_454;
}

struct OpLevel_Token_IntIntTuple2Tuple2ListTuple2 {
    struct OpLevel_ t0;
    struct Token_IntIntTuple2Tuple2List* t1;
};

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseOps_(struct OpLevel_ level_2, struct IntIntTuple2 baseLoc_34, struct AExpr_ first_2, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_84) {
    struct Token_IntIntTuple2Tuple2List* tokens_191 = arg_84.t0;
    struct StringIntIntTuple2Tuple2List* errors_127 = arg_84.t1;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_201;
    struct OpLevel_Token_IntIntTuple2Tuple2ListTuple2 tuple_286;
    tuple_286.t0 = level_2;
    tuple_286.t1 = tokens_191;
    if ((tuple_286.t0.tag != Or_)) goto next_727;
    if ((!(tuple_286.t1))) goto next_727;
    if ((tuple_286.t1->head.t0.tag != PipePipe_)) goto next_727;
    struct IntIntTuple2 opLoc_4 = tuple_286.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_196 = tuple_286.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_287;
    tuple_287.t0 = tokens_196;
    tuple_287.t1 = errors_127;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_455 = nextL_(baseLoc_34, level_2, first_2, (struct Op_){.tag = Or_1}, opLoc_4, tuple_287);
    match_201 = call_455;
    goto end_match_726;
next_727:;
    if ((tuple_286.t0.tag != And_)) goto next_728;
    if ((!(tuple_286.t1))) goto next_728;
    if ((tuple_286.t1->head.t0.tag != AmpAmp_)) goto next_728;
    struct IntIntTuple2 opLoc_5 = tuple_286.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_197 = tuple_286.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_288;
    tuple_288.t0 = tokens_197;
    tuple_288.t1 = errors_127;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_456 = nextL_(baseLoc_34, level_2, first_2, (struct Op_){.tag = And_1}, opLoc_5, tuple_288);
    match_201 = call_456;
    goto end_match_726;
next_728:;
    if ((tuple_286.t0.tag != Cmp_)) goto next_729;
    if ((!(tuple_286.t1))) goto next_729;
    if ((tuple_286.t1->head.t0.tag != Eq_)) goto next_729;
    struct IntIntTuple2 opLoc_6 = tuple_286.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_198 = tuple_286.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_289;
    tuple_289.t0 = tokens_198;
    tuple_289.t1 = errors_127;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_457 = nextL_(baseLoc_34, level_2, first_2, (struct Op_){.tag = Eq_1}, opLoc_6, tuple_289);
    match_201 = call_457;
    goto end_match_726;
next_729:;
    if ((tuple_286.t0.tag != Cmp_)) goto next_730;
    if ((!(tuple_286.t1))) goto next_730;
    if ((tuple_286.t1->head.t0.tag != LtGt_)) goto next_730;
    struct IntIntTuple2 opLoc_7 = tuple_286.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_199 = tuple_286.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_290;
    tuple_290.t0 = tokens_199;
    tuple_290.t1 = errors_127;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_458 = nextL_(baseLoc_34, level_2, first_2, (struct Op_){.tag = Ne_}, opLoc_7, tuple_290);
    match_201 = call_458;
    goto end_match_726;
next_730:;
    if ((tuple_286.t0.tag != Cmp_)) goto next_731;
    if ((!(tuple_286.t1))) goto next_731;
    if ((tuple_286.t1->head.t0.tag != Lt_)) goto next_731;
    struct IntIntTuple2 opLoc_8 = tuple_286.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_200 = tuple_286.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_291;
    tuple_291.t0 = tokens_200;
    tuple_291.t1 = errors_127;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_459 = nextL_(baseLoc_34, level_2, first_2, (struct Op_){.tag = Lt_1}, opLoc_8, tuple_291);
    match_201 = call_459;
    goto end_match_726;
next_731:;
    if ((tuple_286.t0.tag != Cmp_)) goto next_732;
    if ((!(tuple_286.t1))) goto next_732;
    if ((tuple_286.t1->head.t0.tag != LtEq_)) goto next_732;
    struct IntIntTuple2 opLoc_9 = tuple_286.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_201 = tuple_286.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_292;
    tuple_292.t0 = tokens_201;
    tuple_292.t1 = errors_127;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_460 = nextL_(baseLoc_34, level_2, first_2, (struct Op_){.tag = Le_}, opLoc_9, tuple_292);
    match_201 = call_460;
    goto end_match_726;
next_732:;
    if ((tuple_286.t0.tag != Cmp_)) goto next_733;
    if ((!(tuple_286.t1))) goto next_733;
    if ((tuple_286.t1->head.t0.tag != Gt_)) goto next_733;
    struct IntIntTuple2 opLoc_10 = tuple_286.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_202 = tuple_286.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_293;
    tuple_293.t0 = tokens_202;
    tuple_293.t1 = errors_127;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_461 = nextL_(baseLoc_34, level_2, first_2, (struct Op_){.tag = Gt_1}, opLoc_10, tuple_293);
    match_201 = call_461;
    goto end_match_726;
next_733:;
    if ((tuple_286.t0.tag != Cmp_)) goto next_734;
    if ((!(tuple_286.t1))) goto next_734;
    if ((tuple_286.t1->head.t0.tag != GtEq_)) goto next_734;
    struct IntIntTuple2 opLoc_11 = tuple_286.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_203 = tuple_286.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_294;
    tuple_294.t0 = tokens_203;
    tuple_294.t1 = errors_127;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_462 = nextL_(baseLoc_34, level_2, first_2, (struct Op_){.tag = Ge_}, opLoc_11, tuple_294);
    match_201 = call_462;
    goto end_match_726;
next_734:;
    if ((tuple_286.t0.tag != Pipe_1)) goto next_735;
    if ((!(tuple_286.t1))) goto next_735;
    if ((tuple_286.t1->head.t0.tag != PipeGt_)) goto next_735;
    struct IntIntTuple2 opLoc_12 = tuple_286.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_204 = tuple_286.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_295;
    tuple_295.t0 = tokens_204;
    tuple_295.t1 = errors_127;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_463 = nextL_(baseLoc_34, level_2, first_2, (struct Op_){.tag = Pipe_2}, opLoc_12, tuple_295);
    match_201 = call_463;
    goto end_match_726;
next_735:;
    if ((tuple_286.t0.tag != Cons_)) goto next_736;
    if ((!(tuple_286.t1))) goto next_736;
    if ((tuple_286.t1->head.t0.tag != ColonColon_)) goto next_736;
    struct IntIntTuple2 opLoc_13 = tuple_286.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_205 = tuple_286.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_296;
    tuple_296.t0 = tokens_205;
    tuple_296.t1 = errors_127;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_464 = nextR_(baseLoc_34, level_2, first_2, (struct Op_){.tag = Cons_1}, opLoc_13, tuple_296);
    match_201 = call_464;
    goto end_match_726;
next_736:;
    if ((tuple_286.t0.tag != Add_)) goto next_737;
    if ((!(tuple_286.t1))) goto next_737;
    if ((tuple_286.t1->head.t0.tag != Plus_)) goto next_737;
    struct IntIntTuple2 opLoc_14 = tuple_286.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_206 = tuple_286.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_297;
    tuple_297.t0 = tokens_206;
    tuple_297.t1 = errors_127;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_465 = nextL_(baseLoc_34, level_2, first_2, (struct Op_){.tag = Add_1}, opLoc_14, tuple_297);
    match_201 = call_465;
    goto end_match_726;
next_737:;
    if ((tuple_286.t0.tag != Add_)) goto next_738;
    if ((!(tuple_286.t1))) goto next_738;
    if ((tuple_286.t1->head.t0.tag != Minus_)) goto next_738;
    struct IntIntTuple2 opLoc_15 = tuple_286.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_207 = tuple_286.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_298;
    tuple_298.t0 = tokens_207;
    tuple_298.t1 = errors_127;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_466 = nextL_(baseLoc_34, level_2, first_2, (struct Op_){.tag = Sub_}, opLoc_15, tuple_298);
    match_201 = call_466;
    goto end_match_726;
next_738:;
    if ((tuple_286.t0.tag != Mul_)) goto next_739;
    if ((!(tuple_286.t1))) goto next_739;
    if ((tuple_286.t1->head.t0.tag != Star_)) goto next_739;
    struct IntIntTuple2 opLoc_16 = tuple_286.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_208 = tuple_286.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_299;
    tuple_299.t0 = tokens_208;
    tuple_299.t1 = errors_127;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_467 = nextL_(baseLoc_34, level_2, first_2, (struct Op_){.tag = Mul_1}, opLoc_16, tuple_299);
    match_201 = call_467;
    goto end_match_726;
next_739:;
    if ((tuple_286.t0.tag != Mul_)) goto next_740;
    if ((!(tuple_286.t1))) goto next_740;
    if ((tuple_286.t1->head.t0.tag != Slash_)) goto next_740;
    struct IntIntTuple2 opLoc_17 = tuple_286.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_209 = tuple_286.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_300;
    tuple_300.t0 = tokens_209;
    tuple_300.t1 = errors_127;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_468 = nextL_(baseLoc_34, level_2, first_2, (struct Op_){.tag = Div_}, opLoc_17, tuple_300);
    match_201 = call_468;
    goto end_match_726;
next_740:;
    if ((tuple_286.t0.tag != Mul_)) goto next_741;
    if ((!(tuple_286.t1))) goto next_741;
    if ((tuple_286.t1->head.t0.tag != Percent_)) goto next_741;
    struct IntIntTuple2 opLoc_18 = tuple_286.t1->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_210 = tuple_286.t1->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_301;
    tuple_301.t0 = tokens_210;
    tuple_301.t1 = errors_127;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_469 = nextL_(baseLoc_34, level_2, first_2, (struct Op_){.tag = Mod_}, opLoc_18, tuple_301);
    match_201 = call_469;
    goto end_match_726;
next_741:;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_302;
    tuple_302.t0 = first_2;
    tuple_302.t1 = tokens_191;
    tuple_302.t2 = errors_127;
    match_201 = tuple_302;
    goto end_match_726;
next_742:;
end_match_726:;
    return match_201;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseOp_(struct OpLevel_ level_3, struct IntIntTuple2 baseLoc_35, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_85) {
    struct Token_IntIntTuple2Tuple2List* tokens_211 = arg_85.t0;
    struct StringIntIntTuple2Tuple2List* errors_132 = arg_85.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_303;
    tuple_303.t0 = tokens_211;
    tuple_303.t1 = errors_132;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_470 = parseNextLevelOp_(level_3, baseLoc_35, tuple_303);
    struct AExpr_ first_3 = call_470.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_212 = call_470.t1;
    struct StringIntIntTuple2Tuple2List* errors_133 = call_470.t2;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_304;
    tuple_304.t0 = tokens_212;
    tuple_304.t1 = errors_133;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_471 = parseOps_(level_3, baseLoc_35, first_3, tuple_304);
    return call_471;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTupleItem_(struct IntIntTuple2 baseLoc_36, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_86) {
    struct Token_IntIntTuple2Tuple2List* tokens_213 = arg_86.t0;
    struct StringIntIntTuple2Tuple2List* errors_134 = arg_86.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_305;
    tuple_305.t0 = tokens_213;
    tuple_305.t1 = errors_134;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_472 = parseOp_((struct OpLevel_){.tag = Or_}, baseLoc_36, tuple_305);
    return call_472;
}

struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_31(struct IntIntTuple2 baseLoc_37, struct AExpr_List* acc_20, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_87) {
    struct Token_IntIntTuple2Tuple2List* tokens_215 = arg_87.t0;
    struct StringIntIntTuple2Tuple2List* errors_136 = arg_87.t1;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_202;
    if ((!(tokens_215))) goto next_744;
    if ((tokens_215->head.t0.tag != Comma_)) goto next_744;
    struct Token_IntIntTuple2Tuple2List* tokens_216 = tokens_215->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_306;
    tuple_306.t0 = tokens_216;
    tuple_306.t1 = errors_136;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_473 = parseTupleItem_(baseLoc_37, tuple_306);
    struct AExpr_ second_5 = call_473.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_217 = call_473.t1;
    struct StringIntIntTuple2Tuple2List* errors_137 = call_473.t2;
    struct AExpr_List* list_42 = (struct AExpr_List*)malloc(sizeof(struct AExpr_List));
    list_42->head = second_5;
    list_42->tail = acc_20;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_307;
    tuple_307.t0 = tokens_217;
    tuple_307.t1 = errors_137;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_474 = go_31(baseLoc_37, list_42, tuple_307);
    match_202 = call_474;
    goto end_match_743;
next_744:;
    struct Token_IntIntTuple2Tuple2List* tokens_218 = tokens_215;
    struct AExpr_List* call_475 = listRev_1(acc_20);
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_308;
    tuple_308.t0 = call_475;
    tuple_308.t1 = tokens_218;
    tuple_308.t2 = errors_136;
    match_202 = tuple_308;
    goto end_match_743;
next_745:;
end_match_743:;
    return match_202;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTuple_(struct IntIntTuple2 baseLoc_37, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_88) {
    struct Token_IntIntTuple2Tuple2List* tokens_214 = arg_88.t0;
    struct StringIntIntTuple2Tuple2List* errors_135 = arg_88.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_309;
    tuple_309.t0 = tokens_214;
    tuple_309.t1 = errors_135;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_476 = parseTupleItem_(baseLoc_37, tuple_309);
    struct AExpr_ item_ = call_476.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_219 = call_476.t1;
    struct StringIntIntTuple2Tuple2List* errors_138 = call_476.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_203;
    if ((!(tokens_219))) goto next_747;
    if ((tokens_219->head.t0.tag != Comma_)) goto next_747;
    struct IntIntTuple2 loc_46 = tokens_219->head.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_310;
    tuple_310.t0 = tokens_219;
    tuple_310.t1 = errors_138;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_477 = go_31(baseLoc_37, NULL, tuple_310);
    struct AExpr_List* items_4 = call_477.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_220 = call_477.t1;
    struct StringIntIntTuple2Tuple2List* errors_139 = call_477.t2;
    struct AExpr_List* list_43 = (struct AExpr_List*)malloc(sizeof(struct AExpr_List));
    list_43->head = item_;
    list_43->tail = items_4;
    struct AExpr_ListIntIntTuple2Tuple2 tuple_312;
    tuple_312.t0 = list_43;
    tuple_312.t1 = loc_46;
    struct AExpr_ListIntIntTuple2Tuple2* payload_72 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_72))) = tuple_312;
    struct AExpr_ variant_72 = (struct AExpr_){.tag = TupleLit_1, .TupleLit_1 = payload_72};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_311;
    tuple_311.t0 = variant_72;
    tuple_311.t1 = tokens_220;
    tuple_311.t2 = errors_139;
    match_203 = tuple_311;
    goto end_match_746;
next_747:;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_313;
    tuple_313.t0 = item_;
    tuple_313.t1 = tokens_219;
    tuple_313.t2 = errors_138;
    match_203 = tuple_313;
    goto end_match_746;
next_748:;
end_match_746:;
    return match_203;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseAnno_(struct IntIntTuple2 baseLoc_38, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_89) {
    struct Token_IntIntTuple2Tuple2List* tokens_221 = arg_89.t0;
    struct StringIntIntTuple2Tuple2List* errors_140 = arg_89.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_314;
    tuple_314.t0 = tokens_221;
    tuple_314.t1 = errors_140;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_478 = parseTuple_(baseLoc_38, tuple_314);
    struct AExpr_ body_9 = call_478.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_222 = call_478.t1;
    struct StringIntIntTuple2Tuple2List* errors_141 = call_478.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_204;
    if ((!(tokens_222))) goto next_750;
    if ((tokens_222->head.t0.tag != Colon_)) goto next_750;
    struct IntIntTuple2 loc_47 = tokens_222->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_223 = tokens_222->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_315;
    tuple_315.t0 = tokens_223;
    tuple_315.t1 = errors_141;
    struct ATy_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_479 = parseTy_(baseLoc_38, tuple_315);
    struct ATy_ ty_11 = call_479.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_224 = call_479.t1;
    struct StringIntIntTuple2Tuple2List* errors_142 = call_479.t2;
    struct AExpr_ATy_IntIntTuple2Tuple3 tuple_317;
    tuple_317.t0 = body_9;
    tuple_317.t1 = ty_11;
    tuple_317.t2 = loc_47;
    struct AExpr_ATy_IntIntTuple2Tuple3* payload_73 = (struct AExpr_ATy_IntIntTuple2Tuple3*)malloc(sizeof(struct AExpr_ATy_IntIntTuple2Tuple3));
    (*(((struct AExpr_ATy_IntIntTuple2Tuple3*)payload_73))) = tuple_317;
    struct AExpr_ variant_73 = (struct AExpr_){.tag = Anno_1, .Anno_1 = payload_73};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_316;
    tuple_316.t0 = variant_73;
    tuple_316.t1 = tokens_224;
    tuple_316.t2 = errors_142;
    match_204 = tuple_316;
    goto end_match_749;
next_750:;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_318;
    tuple_318.t0 = body_9;
    tuple_318.t1 = tokens_222;
    tuple_318.t2 = errors_141;
    match_204 = tuple_318;
    goto end_match_749;
next_751:;
end_match_749:;
    return match_204;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseExpr_(struct IntIntTuple2 baseLoc_39, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_90) {
    struct Token_IntIntTuple2Tuple2List* tokens_225 = arg_90.t0;
    struct StringIntIntTuple2Tuple2List* errors_143 = arg_90.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_319;
    tuple_319.t0 = tokens_225;
    tuple_319.t1 = errors_143;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_480 = parseAnno_(baseLoc_39, tuple_319);
    return call_480;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseStmt_(struct IntIntTuple2 baseLoc_40, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_91) {
    struct Token_IntIntTuple2Tuple2List* tokens_226 = arg_91.t0;
    struct StringIntIntTuple2Tuple2List* errors_144 = arg_91.t1;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_205;
    if ((!(tokens_226))) goto next_753;
    if ((tokens_226->head.t0.tag != Let_)) goto next_753;
    struct IntIntTuple2 letLoc_2 = tokens_226->head.t1;
    if ((!(tokens_226->tail))) goto next_753;
    if ((tokens_226->tail->head.t0.tag != Rec_)) goto next_753;
    struct Token_IntIntTuple2Tuple2List* tokens_227 = tokens_226->tail->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_320;
    tuple_320.t0 = tokens_227;
    tuple_320.t1 = errors_144;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_481 = parseLet_(letLoc_2, tuple_320);
    match_205 = call_481;
    goto end_match_752;
next_753:;
    if ((!(tokens_226))) goto next_754;
    if ((tokens_226->head.t0.tag != Let_)) goto next_754;
    struct IntIntTuple2 letLoc_3 = tokens_226->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_228 = tokens_226->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_321;
    tuple_321.t0 = tokens_228;
    tuple_321.t1 = errors_144;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_482 = parseLet_(letLoc_3, tuple_321);
    match_205 = call_482;
    goto end_match_752;
next_754:;
    if ((!(tokens_226))) goto next_755;
    if ((tokens_226->head.t0.tag != Type_)) goto next_755;
    struct IntIntTuple2 typeLoc_1 = tokens_226->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_229 = tokens_226->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_322;
    tuple_322.t0 = tokens_229;
    tuple_322.t1 = errors_144;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_483 = parseTyDecl_(typeLoc_1, tuple_322);
    match_205 = call_483;
    goto end_match_752;
next_755:;
    if ((!(tokens_226))) goto next_756;
    if ((tokens_226->head.t0.tag != Open_)) goto next_756;
    struct IntIntTuple2 typeLoc_2 = tokens_226->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_230 = tokens_226->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_323;
    tuple_323.t0 = tokens_230;
    tuple_323.t1 = errors_144;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_484 = parseOpen_(typeLoc_2, tuple_323);
    match_205 = call_484;
    goto end_match_752;
next_756:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_324;
    tuple_324.t0 = tokens_226;
    tuple_324.t1 = errors_144;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_485 = parseExpr_(baseLoc_40, tuple_324);
    match_205 = call_485;
    goto end_match_752;
next_757:;
end_match_752:;
    return match_205;
}

struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 go_32(struct IntIntTuple2 baseLoc_41, struct AExpr_List* acc_21, struct IntIntTuple2 alignLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_92) {
    struct Token_IntIntTuple2Tuple2List* tokens_232 = arg_92.t0;
    struct StringIntIntTuple2Tuple2List* errors_146 = arg_92.t1;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_206;
    if ((!(tokens_232))) goto next_759;
    if ((tokens_232->head.t0.tag != Semi_)) goto next_759;
    struct IntIntTuple2 semiLoc_ = tokens_232->head.t1;
    struct Token_IntIntTuple2Tuple2List* tokens_233 = tokens_232->tail;
    int call_486 = locInside_(alignLoc_, semiLoc_);
    if ((!(call_486))) goto next_759;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_325;
    tuple_325.t0 = tokens_233;
    tuple_325.t1 = errors_146;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_487 = parseStmt_(baseLoc_41, tuple_325);
    struct AExpr_ expr_7 = call_487.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_234 = call_487.t1;
    struct StringIntIntTuple2Tuple2List* errors_147 = call_487.t2;
    struct AExpr_List* list_44 = (struct AExpr_List*)malloc(sizeof(struct AExpr_List));
    list_44->head = expr_7;
    list_44->tail = acc_21;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_326;
    tuple_326.t0 = tokens_234;
    tuple_326.t1 = errors_147;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_488 = go_32(baseLoc_41, list_44, alignLoc_, tuple_326);
    match_206 = call_488;
    goto end_match_758;
next_759:;
    int match_207;
    struct IntIntTuple2 call_489 = nextLoc_1(tokens_232);
    int call_490 = locIsSameColumn_(alignLoc_, call_489);
    if ((!(call_490))) goto next_763;
    int call_491 = leadsExpr_1(tokens_232);
    match_207 = call_491;
    goto end_match_762;
next_763:;
    if (call_490) goto next_764;
    match_207 = 0;
    goto end_match_762;
next_764:;
    exit(1);
end_match_762:;
    if ((!(match_207))) goto next_760;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_327;
    tuple_327.t0 = tokens_232;
    tuple_327.t1 = errors_146;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_492 = parseStmt_(baseLoc_41, tuple_327);
    struct AExpr_ expr_8 = call_492.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_235 = call_492.t1;
    struct StringIntIntTuple2Tuple2List* errors_148 = call_492.t2;
    struct AExpr_List* list_45 = (struct AExpr_List*)malloc(sizeof(struct AExpr_List));
    list_45->head = expr_8;
    list_45->tail = acc_21;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_328;
    tuple_328.t0 = tokens_235;
    tuple_328.t1 = errors_148;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_493 = go_32(baseLoc_41, list_45, alignLoc_, tuple_328);
    match_206 = call_493;
    goto end_match_758;
next_760:;
    struct AExpr_List* call_494 = listRev_1(acc_21);
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_329;
    tuple_329.t0 = call_494;
    tuple_329.t1 = tokens_232;
    tuple_329.t2 = errors_146;
    match_206 = tuple_329;
    goto end_match_758;
next_761:;
end_match_758:;
    return match_206;
}

struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseStmts_(struct IntIntTuple2 baseLoc_41, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_93) {
    struct Token_IntIntTuple2Tuple2List* tokens_231 = arg_93.t0;
    struct StringIntIntTuple2Tuple2List* errors_145 = arg_93.t1;
    struct IntIntTuple2 call_495 = nextLoc_1(tokens_231);
    struct IntIntTuple2 alignLoc_1 = call_495;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_208;
    int call_496 = locInside_(baseLoc_41, alignLoc_1);
    if ((!(call_496))) goto next_766;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_330;
    tuple_330.t0 = tokens_231;
    tuple_330.t1 = errors_145;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_497 = go_32(baseLoc_41, NULL, alignLoc_1, tuple_330);
    match_208 = call_497;
    goto end_match_765;
next_766:;
    if (call_496) goto next_767;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_331;
    tuple_331.t0 = NULL;
    tuple_331.t1 = tokens_231;
    tuple_331.t2 = errors_145;
    match_208 = tuple_331;
    goto end_match_765;
next_767:;
    exit(1);
end_match_765:;
    return match_208;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseSemi_(struct IntIntTuple2 baseLoc_42, struct IntIntTuple2 mainLoc_, struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_94) {
    struct Token_IntIntTuple2Tuple2List* tokens_236 = arg_94.t0;
    struct StringIntIntTuple2Tuple2List* errors_149 = arg_94.t1;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_332;
    tuple_332.t0 = tokens_236;
    tuple_332.t1 = errors_149;
    struct AExpr_ListToken_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_498 = parseStmts_(baseLoc_42, tuple_332);
    struct AExpr_List* items_5 = call_498.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_237 = call_498.t1;
    struct StringIntIntTuple2Tuple2List* errors_150 = call_498.t2;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_209;
    if ((!((!(items_5))))) goto next_769;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_333;
    tuple_333.t0 = tokens_237;
    tuple_333.t1 = errors_150;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_499 = parseExprError_1((struct String){.str = "Expected statements", .len = 19}, tuple_333);
    match_209 = call_499;
    goto end_match_768;
next_769:;
    if ((!(items_5))) goto next_770;
    struct AExpr_ item_1 = items_5->head;
    if ((!((!(items_5->tail))))) goto next_770;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_334;
    tuple_334.t0 = item_1;
    tuple_334.t1 = tokens_237;
    tuple_334.t2 = errors_150;
    match_209 = tuple_334;
    goto end_match_768;
next_770:;
    struct AExpr_ListIntIntTuple2Tuple2 tuple_336;
    tuple_336.t0 = items_5;
    tuple_336.t1 = mainLoc_;
    struct AExpr_ListIntIntTuple2Tuple2* payload_74 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_74))) = tuple_336;
    struct AExpr_ variant_74 = (struct AExpr_){.tag = Semi_1, .Semi_1 = payload_74};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_335;
    tuple_335.t0 = variant_74;
    tuple_335.t1 = tokens_237;
    tuple_335.t2 = errors_150;
    match_209 = tuple_335;
    goto end_match_768;
next_771:;
end_match_768:;
    return match_209;
}

struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 parseTopLevel_(struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 arg_95) {
    struct Token_IntIntTuple2Tuple2List* tokens_238 = arg_95.t0;
    struct StringIntIntTuple2Tuple2List* errors_151 = arg_95.t1;
    struct IntIntTuple2 tuple_337;
    tuple_337.t0 = 0;
    tuple_337.t1 = 0;
    struct IntIntTuple2 topLoc_ = tuple_337;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 match_210;
    if ((!((!(tokens_238))))) goto next_773;
    struct AExpr_ListIntIntTuple2Tuple2 tuple_339;
    tuple_339.t0 = NULL;
    tuple_339.t1 = topLoc_;
    struct AExpr_ListIntIntTuple2Tuple2* payload_75 = (struct AExpr_ListIntIntTuple2Tuple2*)malloc(sizeof(struct AExpr_ListIntIntTuple2Tuple2));
    (*(((struct AExpr_ListIntIntTuple2Tuple2*)payload_75))) = tuple_339;
    struct AExpr_ variant_75 = (struct AExpr_){.tag = TupleLit_1, .TupleLit_1 = payload_75};
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 tuple_338;
    tuple_338.t0 = variant_75;
    tuple_338.t1 = tokens_238;
    tuple_338.t2 = errors_151;
    match_210 = tuple_338;
    goto end_match_772;
next_773:;
    if ((!(tokens_238))) goto next_774;
    if ((tokens_238->head.t0.tag != Module_)) goto next_774;
    struct IntIntTuple2 moduleLoc_ = tokens_238->head.t1;
    if ((!(tokens_238->tail))) goto next_774;
    if ((tokens_238->tail->head.t0.tag != Rec_)) goto next_774;
    if ((!(tokens_238->tail->tail))) goto next_774;
    if ((tokens_238->tail->tail->head.t0.tag != Ident_)) goto next_774;
    if ((!(tokens_238->tail->tail->tail))) goto next_774;
    if ((tokens_238->tail->tail->tail->head.t0.tag != Dot_)) goto next_774;
    if ((!(tokens_238->tail->tail->tail->tail))) goto next_774;
    if ((tokens_238->tail->tail->tail->tail->head.t0.tag != Ident_)) goto next_774;
    struct Token_IntIntTuple2Tuple2List* tokens_239 = tokens_238->tail->tail->tail->tail->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_340;
    tuple_340.t0 = tokens_239;
    tuple_340.t1 = errors_151;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_500 = parseSemi_(moduleLoc_, moduleLoc_, tuple_340);
    match_210 = call_500;
    goto end_match_772;
next_774:;
    if ((!(tokens_238))) goto next_775;
    if ((tokens_238->head.t0.tag != Module_)) goto next_775;
    struct IntIntTuple2 moduleLoc_1 = tokens_238->head.t1;
    if ((!(tokens_238->tail))) goto next_775;
    if ((tokens_238->tail->head.t0.tag != Rec_)) goto next_775;
    if ((!(tokens_238->tail->tail))) goto next_775;
    if ((tokens_238->tail->tail->head.t0.tag != Ident_)) goto next_775;
    struct Token_IntIntTuple2Tuple2List* tokens_240 = tokens_238->tail->tail->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_341;
    tuple_341.t0 = tokens_240;
    tuple_341.t1 = errors_151;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_501 = parseSemi_(moduleLoc_1, moduleLoc_1, tuple_341);
    match_210 = call_501;
    goto end_match_772;
next_775:;
    if ((!(tokens_238))) goto next_776;
    if ((tokens_238->head.t0.tag != Module_)) goto next_776;
    struct IntIntTuple2 moduleLoc_2 = tokens_238->head.t1;
    if ((!(tokens_238->tail))) goto next_776;
    if ((tokens_238->tail->head.t0.tag != Ident_)) goto next_776;
    struct Token_IntIntTuple2Tuple2List* tokens_241 = tokens_238->tail->tail;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_342;
    tuple_342.t0 = tokens_241;
    tuple_342.t1 = errors_151;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_502 = parseSemi_(moduleLoc_2, moduleLoc_2, tuple_342);
    match_210 = call_502;
    goto end_match_772;
next_776:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_343;
    tuple_343.t0 = tokens_238;
    tuple_343.t1 = errors_151;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_503 = parseSemi_(topLoc_, topLoc_, tuple_343);
    match_210 = call_503;
    goto end_match_772;
next_777:;
end_match_772:;
    return match_210;
}

struct AExpr_StringIntIntTuple2Tuple2ListTuple2 {
    struct AExpr_ t0;
    struct StringIntIntTuple2Tuple2List* t1;
};

struct AExpr_StringIntIntTuple2Tuple2ListTuple2 parse_(struct Token_IntIntTuple2Tuple2List* tokens_242) {
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_344;
    tuple_344.t0 = tokens_242;
    tuple_344.t1 = NULL;
    struct AExpr_Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple3 call_504 = parseTopLevel_(tuple_344);
    struct AExpr_ expr_9 = call_504.t0;
    struct Token_IntIntTuple2Tuple2List* tokens_243 = call_504.t1;
    struct StringIntIntTuple2Tuple2List* errors_152 = call_504.t2;
    struct StringIntIntTuple2Tuple2List* match_211;
    if ((!((!(tokens_243))))) goto next_779;
    match_211 = errors_152;
    goto end_match_778;
next_779:;
    struct Token_IntIntTuple2Tuple2ListStringIntIntTuple2Tuple2ListTuple2 tuple_345;
    tuple_345.t0 = tokens_243;
    tuple_345.t1 = errors_152;
    struct StringIntIntTuple2Tuple2List* call_505 = parseNewError_1((struct String){.str = "Expected eof", .len = 12}, tuple_345);
    match_211 = call_505;
    goto end_match_778;
next_780:;
end_match_778:;
    struct StringIntIntTuple2Tuple2List* errors_153 = match_211;
    struct AExpr_StringIntIntTuple2Tuple2ListTuple2 tuple_346;
    tuple_346.t0 = expr_9;
    tuple_346.t1 = errors_153;
    return tuple_346;
}

struct String litToString_(struct Lit_ lit_) {
    struct String match_212;
    if ((lit_.tag != Bool_)) goto next_782;
    if ((!((*(lit_.Bool_))))) goto next_782;
    match_212 = (struct String){.str = "true", .len = 4};
    goto end_match_781;
next_782:;
    if ((lit_.tag != Bool_)) goto next_783;
    if ((*(lit_.Bool_))) goto next_783;
    match_212 = (struct String){.str = "false", .len = 5};
    goto end_match_781;
next_783:;
    if ((lit_.tag != Int_)) goto next_784;
    int value_4 = (*(lit_.Int_));
    struct String call_506 = str_of_int(value_4);
    match_212 = call_506;
    goto end_match_781;
next_784:;
    if ((lit_.tag != Char_)) goto next_785;
    char value_5 = (*(lit_.Char_));
    int call_507 = ((int)value_5);
    struct String call_508 = str_of_int(call_507);
    match_212 = str_add((struct String){.str = "char ", .len = 5}, call_508);
    goto end_match_781;
next_785:;
    if ((lit_.tag != Str_)) goto next_786;
    match_212 = (struct String){.str = "\"...\"", .len = 5};
    goto end_match_781;
next_786:;
    exit(1);
end_match_781:;
    return match_212;
}

struct String tokenToString_(struct Token_ token_12) {
    struct String match_213;
    if ((token_12.tag != Error_)) goto next_788;
    match_213 = (struct String){.str = "Error", .len = 5};
    goto end_match_787;
next_788:;
    if ((token_12.tag != Bool_1)) goto next_789;
    if ((*(token_12.Bool_1))) goto next_789;
    match_213 = (struct String){.str = "false", .len = 5};
    goto end_match_787;
next_789:;
    if ((token_12.tag != Bool_1)) goto next_790;
    if ((!((*(token_12.Bool_1))))) goto next_790;
    match_213 = (struct String){.str = "true", .len = 4};
    goto end_match_787;
next_790:;
    if ((token_12.tag != Int_1)) goto next_791;
    int value_6 = (*(token_12.Int_1));
    struct String call_509 = str_of_int(value_6);
    match_213 = call_509;
    goto end_match_787;
next_791:;
    if ((token_12.tag != Char_1)) goto next_792;
    match_213 = (struct String){.str = "'?'", .len = 3};
    goto end_match_787;
next_792:;
    if ((token_12.tag != Str_1)) goto next_793;
    match_213 = (struct String){.str = "\"?\"", .len = 3};
    goto end_match_787;
next_793:;
    if ((token_12.tag != Ident_)) goto next_794;
    struct String ident_ = (*(token_12.Ident_));
    match_213 = str_add(str_add((struct String){.str = "\"", .len = 1}, ident_), (struct String){.str = "\"", .len = 1});
    goto end_match_787;
next_794:;
    if ((token_12.tag != ParenL_)) goto next_795;
    match_213 = (struct String){.str = "(", .len = 1};
    goto end_match_787;
next_795:;
    if ((token_12.tag != ParenR_)) goto next_796;
    match_213 = (struct String){.str = ")", .len = 1};
    goto end_match_787;
next_796:;
    if ((token_12.tag != BracketL_)) goto next_797;
    match_213 = (struct String){.str = "[", .len = 1};
    goto end_match_787;
next_797:;
    if ((token_12.tag != BracketR_)) goto next_798;
    match_213 = (struct String){.str = "]", .len = 1};
    goto end_match_787;
next_798:;
    if ((token_12.tag != Amp_)) goto next_799;
    match_213 = (struct String){.str = "&", .len = 1};
    goto end_match_787;
next_799:;
    if ((token_12.tag != AmpAmp_)) goto next_800;
    match_213 = (struct String){.str = "&&", .len = 2};
    goto end_match_787;
next_800:;
    if ((token_12.tag != Arrow_)) goto next_801;
    match_213 = (struct String){.str = "->", .len = 2};
    goto end_match_787;
next_801:;
    if ((token_12.tag != Colon_)) goto next_802;
    match_213 = (struct String){.str = ":", .len = 1};
    goto end_match_787;
next_802:;
    if ((token_12.tag != ColonColon_)) goto next_803;
    match_213 = (struct String){.str = "::", .len = 2};
    goto end_match_787;
next_803:;
    if ((token_12.tag != Comma_)) goto next_804;
    match_213 = (struct String){.str = ",", .len = 1};
    goto end_match_787;
next_804:;
    if ((token_12.tag != Dot_)) goto next_805;
    match_213 = (struct String){.str = ".", .len = 1};
    goto end_match_787;
next_805:;
    if ((token_12.tag != DotDot_)) goto next_806;
    match_213 = (struct String){.str = "..", .len = 2};
    goto end_match_787;
next_806:;
    if ((token_12.tag != Eq_)) goto next_807;
    match_213 = (struct String){.str = "=", .len = 1};
    goto end_match_787;
next_807:;
    if ((token_12.tag != Gt_)) goto next_808;
    match_213 = (struct String){.str = ">", .len = 1};
    goto end_match_787;
next_808:;
    if ((token_12.tag != GtEq_)) goto next_809;
    match_213 = (struct String){.str = ">=", .len = 2};
    goto end_match_787;
next_809:;
    if ((token_12.tag != Lt_)) goto next_810;
    match_213 = (struct String){.str = "<", .len = 1};
    goto end_match_787;
next_810:;
    if ((token_12.tag != LtEq_)) goto next_811;
    match_213 = (struct String){.str = "<=", .len = 2};
    goto end_match_787;
next_811:;
    if ((token_12.tag != LtGt_)) goto next_812;
    match_213 = (struct String){.str = "<>", .len = 2};
    goto end_match_787;
next_812:;
    if ((token_12.tag != Minus_)) goto next_813;
    match_213 = (struct String){.str = "-", .len = 1};
    goto end_match_787;
next_813:;
    if ((token_12.tag != Percent_)) goto next_814;
    match_213 = (struct String){.str = "%", .len = 1};
    goto end_match_787;
next_814:;
    if ((token_12.tag != Pipe_)) goto next_815;
    match_213 = (struct String){.str = "|", .len = 1};
    goto end_match_787;
next_815:;
    if ((token_12.tag != PipeGt_)) goto next_816;
    match_213 = (struct String){.str = "|>", .len = 2};
    goto end_match_787;
next_816:;
    if ((token_12.tag != PipePipe_)) goto next_817;
    match_213 = (struct String){.str = "||", .len = 2};
    goto end_match_787;
next_817:;
    if ((token_12.tag != Plus_)) goto next_818;
    match_213 = (struct String){.str = "+", .len = 1};
    goto end_match_787;
next_818:;
    if ((token_12.tag != Semi_)) goto next_819;
    match_213 = (struct String){.str = ";", .len = 1};
    goto end_match_787;
next_819:;
    if ((token_12.tag != Star_)) goto next_820;
    match_213 = (struct String){.str = "*", .len = 1};
    goto end_match_787;
next_820:;
    if ((token_12.tag != Slash_)) goto next_821;
    match_213 = (struct String){.str = "/", .len = 1};
    goto end_match_787;
next_821:;
    if ((token_12.tag != As_)) goto next_822;
    match_213 = (struct String){.str = "as", .len = 2};
    goto end_match_787;
next_822:;
    if ((token_12.tag != Do_)) goto next_823;
    match_213 = (struct String){.str = "do", .len = 2};
    goto end_match_787;
next_823:;
    if ((token_12.tag != Else_)) goto next_824;
    match_213 = (struct String){.str = "else", .len = 4};
    goto end_match_787;
next_824:;
    if ((token_12.tag != Fun_)) goto next_825;
    match_213 = (struct String){.str = "fun", .len = 3};
    goto end_match_787;
next_825:;
    if ((token_12.tag != If_)) goto next_826;
    match_213 = (struct String){.str = "if", .len = 2};
    goto end_match_787;
next_826:;
    if ((token_12.tag != In_)) goto next_827;
    match_213 = (struct String){.str = "in", .len = 2};
    goto end_match_787;
next_827:;
    if ((token_12.tag != Internal_)) goto next_828;
    match_213 = (struct String){.str = "internal", .len = 8};
    goto end_match_787;
next_828:;
    if ((token_12.tag != Let_)) goto next_829;
    match_213 = (struct String){.str = "let", .len = 3};
    goto end_match_787;
next_829:;
    if ((token_12.tag != Match_)) goto next_830;
    match_213 = (struct String){.str = "match", .len = 5};
    goto end_match_787;
next_830:;
    if ((token_12.tag != Module_)) goto next_831;
    match_213 = (struct String){.str = "module", .len = 6};
    goto end_match_787;
next_831:;
    if ((token_12.tag != Namespace_)) goto next_832;
    match_213 = (struct String){.str = "namespace", .len = 9};
    goto end_match_787;
next_832:;
    if ((token_12.tag != Of_)) goto next_833;
    match_213 = (struct String){.str = "of", .len = 2};
    goto end_match_787;
next_833:;
    if ((token_12.tag != Open_)) goto next_834;
    match_213 = (struct String){.str = "open", .len = 4};
    goto end_match_787;
next_834:;
    if ((token_12.tag != Private_)) goto next_835;
    match_213 = (struct String){.str = "private", .len = 7};
    goto end_match_787;
next_835:;
    if ((token_12.tag != Public_)) goto next_836;
    match_213 = (struct String){.str = "public", .len = 6};
    goto end_match_787;
next_836:;
    if ((token_12.tag != Rec_)) goto next_837;
    match_213 = (struct String){.str = "rec", .len = 3};
    goto end_match_787;
next_837:;
    if ((token_12.tag != Then_)) goto next_838;
    match_213 = (struct String){.str = "then", .len = 4};
    goto end_match_787;
next_838:;
    if ((token_12.tag != Type_)) goto next_839;
    match_213 = (struct String){.str = "type", .len = 4};
    goto end_match_787;
next_839:;
    if ((token_12.tag != When_)) goto next_840;
    match_213 = (struct String){.str = "when", .len = 4};
    goto end_match_787;
next_840:;
    if ((token_12.tag != With_)) goto next_841;
    match_213 = (struct String){.str = "with", .len = 4};
    goto end_match_787;
next_841:;
end_match_787:;
    return match_213;
}

struct DumpTree_ fun_2(void* env_, struct ATy_ arg_3) {
    struct DumpTree_ call_510 = atDump_(arg_3);
    return call_510;
}

struct DumpTree_ fun_3(void* env_1, struct ATy_ arg_4) {
    struct DumpTree_ call_511 = atDump_(arg_4);
    return call_511;
}

struct DumpTree_ atDump_(struct ATy_ ty_) {
    struct DumpTree_ match_214;
    if ((ty_.tag != Missing_)) goto next_843;
    struct IntIntTuple2 loc_2 = (*(ty_.Missing_));
    struct DumpTree_ call_512 = dumpTreeFromError_((struct String){.str = "missing", .len = 7}, loc_2);
    match_214 = call_512;
    goto end_match_842;
next_843:;
    if ((ty_.tag != Ident_1)) goto next_844;
    struct String ident_1 = (*(ty_.Ident_1)).t0;
    struct DumpTree_ call_513 = dumpTreeNewLeaf_(ident_1);
    match_214 = call_513;
    goto end_match_842;
next_844:;
    if ((ty_.tag != Suffix_)) goto next_845;
    struct ATy_ lTy_ = (*(ty_.Suffix_)).t0;
    struct String ident_2 = (*(ty_.Suffix_)).t1;
    struct DumpTree_ call_514 = atDump_(lTy_);
    struct DumpTree_List* list_46 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_46->head = call_514;
    list_46->tail = NULL;
    struct DumpTree_ call_515 = dumpTreeNew_(ident_2, list_46);
    match_214 = call_515;
    goto end_match_842;
next_845:;
    if ((ty_.tag != Tuple_)) goto next_846;
    struct ATy_List* itemTys_ = (*(ty_.Tuple_)).t0;
    void* box_ = (void*)malloc(sizeof(int));
    (*(((int*)box_))) = 0;
    void* env_14 = box_;
    struct ATy_DumpTree_Fun1 fun_16 = (struct ATy_DumpTree_Fun1){.fun = fun_2, .env = env_14};
    struct DumpTree_List* call_516 = listMap_3(fun_16, itemTys_);
    struct DumpTree_ call_517 = dumpTreeNew_((struct String){.str = "tuple", .len = 5}, call_516);
    match_214 = call_517;
    goto end_match_842;
next_846:;
    if ((ty_.tag != Fun_1)) goto next_847;
    struct ATy_ sTy_ = (*(ty_.Fun_1)).t0;
    struct ATy_ tTy_ = (*(ty_.Fun_1)).t1;
    void* box_1 = (void*)malloc(sizeof(int));
    (*(((int*)box_1))) = 0;
    void* env_15 = box_1;
    struct ATy_DumpTree_Fun1 fun_17 = (struct ATy_DumpTree_Fun1){.fun = fun_3, .env = env_15};
    struct ATy_List* list_48 = (struct ATy_List*)malloc(sizeof(struct ATy_List));
    list_48->head = tTy_;
    list_48->tail = NULL;
    struct ATy_List* list_47 = (struct ATy_List*)malloc(sizeof(struct ATy_List));
    list_47->head = sTy_;
    list_47->tail = list_48;
    struct DumpTree_List* call_518 = listMap_3(fun_17, list_47);
    struct DumpTree_ call_519 = dumpTreeNew_((struct String){.str = "fun", .len = 3}, call_518);
    match_214 = call_519;
    goto end_match_842;
next_847:;
    exit(1);
end_match_842:;
    return match_214;
}

struct DumpTree_ fun_4(void* env_2, struct APat_ arg_5) {
    struct DumpTree_ call_520 = apDump_(arg_5);
    return call_520;
}

struct DumpTree_ fun_5(void* env_3, struct APat_ arg_6) {
    struct DumpTree_ call_521 = apDump_(arg_6);
    return call_521;
}

struct DumpTree_ fun_6(void* env_4, struct APat_ arg_7) {
    struct DumpTree_ call_522 = apDump_(arg_7);
    return call_522;
}

struct DumpTree_ fun_7(void* env_5, struct APat_ arg_8) {
    struct DumpTree_ call_523 = apDump_(arg_8);
    return call_523;
}

struct DumpTree_ apDump_(struct APat_ pat_) {
    struct DumpTree_ match_215;
    if ((pat_.tag != Missing_1)) goto next_849;
    struct IntIntTuple2 loc_3 = (*(pat_.Missing_1));
    struct DumpTree_ call_524 = dumpTreeFromError_((struct String){.str = "missing", .len = 7}, loc_3);
    match_215 = call_524;
    goto end_match_848;
next_849:;
    if ((pat_.tag != Lit_)) goto next_850;
    struct Lit_ lit_1 = (*(pat_.Lit_)).t0;
    struct String call_525 = litToString_(lit_1);
    struct DumpTree_ call_526 = dumpTreeNewLeaf_(call_525);
    match_215 = call_526;
    goto end_match_848;
next_850:;
    if ((pat_.tag != Ident_2)) goto next_851;
    struct String ident_3 = (*(pat_.Ident_2)).t0;
    struct DumpTree_ call_527 = dumpTreeNewLeaf_(ident_3);
    match_215 = call_527;
    goto end_match_848;
next_851:;
    if ((pat_.tag != ListLit_)) goto next_852;
    struct APat_List* pats_ = (*(pat_.ListLit_)).t0;
    void* box_2 = (void*)malloc(sizeof(int));
    (*(((int*)box_2))) = 0;
    void* env_16 = box_2;
    struct APat_DumpTree_Fun1 fun_18 = (struct APat_DumpTree_Fun1){.fun = fun_4, .env = env_16};
    struct DumpTree_List* call_528 = listMap_2(fun_18, pats_);
    struct DumpTree_ call_529 = dumpTreeNew_((struct String){.str = "list", .len = 4}, call_528);
    match_215 = call_529;
    goto end_match_848;
next_852:;
    if ((pat_.tag != Nav_)) goto next_853;
    struct APat_ l_9 = (*(pat_.Nav_)).t0;
    struct String r_22 = (*(pat_.Nav_)).t1;
    struct IntIntTuple2 loc_4 = (*(pat_.Nav_)).t2;
    struct DumpTree_ call_530 = apDump_(l_9);
    struct DumpTree_List* list_49 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_49->head = call_530;
    list_49->tail = NULL;
    struct DumpTree_ call_531 = dumpTreeNew_(str_add((struct String){.str = ".", .len = 1}, r_22), list_49);
    match_215 = call_531;
    goto end_match_848;
next_853:;
    if ((pat_.tag != Call_)) goto next_854;
    struct APat_ calleePat_ = (*(pat_.Call_)).t0;
    struct APat_List* argPats_ = (*(pat_.Call_)).t1;
    struct DumpTree_ call_532 = apDump_(calleePat_);
    void* box_3 = (void*)malloc(sizeof(int));
    (*(((int*)box_3))) = 0;
    void* env_17 = box_3;
    struct APat_DumpTree_Fun1 fun_19 = (struct APat_DumpTree_Fun1){.fun = fun_5, .env = env_17};
    struct DumpTree_List* call_533 = listMap_2(fun_19, argPats_);
    struct DumpTree_List* list_50 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_50->head = call_532;
    list_50->tail = call_533;
    struct DumpTree_ call_534 = dumpTreeNew_((struct String){.str = "call", .len = 4}, list_50);
    match_215 = call_534;
    goto end_match_848;
next_854:;
    if ((pat_.tag != Cons_2)) goto next_855;
    struct APat_ head_1 = (*(pat_.Cons_2)).t0;
    struct APat_ tail_1 = (*(pat_.Cons_2)).t1;
    struct DumpTree_ call_535 = apDump_(tail_1);
    struct DumpTree_ call_536 = apDump_(head_1);
    struct DumpTree_List* list_51 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_51->head = call_536;
    list_51->tail = NULL;
    struct DumpTree_ call_537 = dumpTreeNew_((struct String){.str = "cons", .len = 4}, list_51);
    struct DumpTree_ call_538 = dumpTreeAttachNext_(call_535, call_537);
    match_215 = call_538;
    goto end_match_848;
next_855:;
    if ((pat_.tag != TupleLit_)) goto next_856;
    struct APat_List* pats_1 = (*(pat_.TupleLit_)).t0;
    void* box_4 = (void*)malloc(sizeof(int));
    (*(((int*)box_4))) = 0;
    void* env_18 = box_4;
    struct APat_DumpTree_Fun1 fun_20 = (struct APat_DumpTree_Fun1){.fun = fun_6, .env = env_18};
    struct DumpTree_List* call_539 = listMap_2(fun_20, pats_1);
    struct DumpTree_ call_540 = dumpTreeNew_((struct String){.str = "tuple", .len = 5}, call_539);
    match_215 = call_540;
    goto end_match_848;
next_856:;
    if ((pat_.tag != As_1)) goto next_857;
    struct APat_ pat_1 = (*(pat_.As_1)).t0;
    struct String ident_4 = (*(pat_.As_1)).t1;
    struct DumpTree_ call_541 = apDump_(pat_1);
    struct DumpTree_List* list_52 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_52->head = call_541;
    list_52->tail = NULL;
    struct DumpTree_ call_542 = dumpTreeNew_(str_add((struct String){.str = "as ", .len = 3}, ident_4), list_52);
    match_215 = call_542;
    goto end_match_848;
next_857:;
    if ((pat_.tag != Anno_)) goto next_858;
    struct APat_ pat_2 = (*(pat_.Anno_)).t0;
    struct ATy_ ty_1 = (*(pat_.Anno_)).t1;
    struct DumpTree_ call_543 = apDump_(pat_2);
    struct DumpTree_ call_544 = atDump_(ty_1);
    struct DumpTree_List* list_54 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_54->head = call_544;
    list_54->tail = NULL;
    struct DumpTree_List* list_53 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_53->head = call_543;
    list_53->tail = list_54;
    struct DumpTree_ call_545 = dumpTreeNew_((struct String){.str = "anno", .len = 4}, list_53);
    match_215 = call_545;
    goto end_match_848;
next_858:;
    if ((pat_.tag != Or_2)) goto next_859;
    struct APat_ l_10 = (*(pat_.Or_2)).t0;
    struct APat_ r_23 = (*(pat_.Or_2)).t1;
    struct DumpTree_ call_546 = apDump_(r_23);
    struct DumpTree_ call_547 = apDump_(l_10);
    struct DumpTree_List* list_55 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_55->head = call_547;
    list_55->tail = NULL;
    struct DumpTree_ call_548 = dumpTreeNew_((struct String){.str = "or", .len = 2}, list_55);
    struct DumpTree_ call_549 = dumpTreeAttachNext_(call_546, call_548);
    match_215 = call_549;
    goto end_match_848;
next_859:;
    if ((pat_.tag != Fun_2)) goto next_860;
    struct String callee_ = (*(pat_.Fun_2)).t0;
    struct APat_List* args_ = (*(pat_.Fun_2)).t1;
    struct IntIntTuple2 loc_5 = (*(pat_.Fun_2)).t2;
    struct DumpTree_ call_550 = dumpTreeNewLeaf_(callee_);
    void* box_5 = (void*)malloc(sizeof(int));
    (*(((int*)box_5))) = 0;
    void* env_19 = box_5;
    struct APat_DumpTree_Fun1 fun_21 = (struct APat_DumpTree_Fun1){.fun = fun_7, .env = env_19};
    struct DumpTree_List* call_551 = listMap_2(fun_21, args_);
    struct DumpTree_List* list_56 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_56->head = call_550;
    list_56->tail = call_551;
    struct DumpTree_ call_552 = dumpTreeNew_((struct String){.str = "fun", .len = 3}, list_56);
    match_215 = call_552;
    goto end_match_848;
next_860:;
    exit(1);
end_match_848:;
    return match_215;
}

struct DumpTree_ fun_8(void* env_6, struct AExpr_ arg_9) {
    struct DumpTree_ call_553 = axDump_(arg_9);
    return call_553;
}

struct DumpTree_ fun_9(void* env_7, struct APat_ arg_10) {
    struct DumpTree_ call_554 = apDump_(arg_10);
    return call_554;
}

struct DumpTree_ fun_10(void* env_8, struct AExpr_ arg_11) {
    struct DumpTree_ call_555 = axDump_(arg_11);
    return call_555;
}

struct DumpTree_ fun_11(void* env_9, struct AExpr_ arg_12) {
    struct DumpTree_ call_556 = axDump_(arg_12);
    return call_556;
}

struct DumpTree_ fun_12(void* env_10, struct AExpr_ arg_13) {
    struct DumpTree_ call_557 = axDump_(arg_13);
    return call_557;
}

struct DumpTree_ axDump_(struct AExpr_ expr_) {
    struct DumpTree_ match_216;
    if ((expr_.tag != Missing_2)) goto next_862;
    struct IntIntTuple2 loc_6 = (*(expr_.Missing_2));
    struct DumpTree_ call_558 = dumpTreeFromError_((struct String){.str = "missing", .len = 7}, loc_6);
    match_216 = call_558;
    goto end_match_861;
next_862:;
    if ((expr_.tag != Lit_1)) goto next_863;
    struct Lit_ lit_2 = (*(expr_.Lit_1)).t0;
    struct String call_559 = litToString_(lit_2);
    struct DumpTree_ call_560 = dumpTreeNewLeaf_(call_559);
    match_216 = call_560;
    goto end_match_861;
next_863:;
    if ((expr_.tag != Ident_3)) goto next_864;
    struct String ident_5 = (*(expr_.Ident_3)).t0;
    struct DumpTree_ call_561 = dumpTreeNewLeaf_(ident_5);
    match_216 = call_561;
    goto end_match_861;
next_864:;
    if ((expr_.tag != ListLit_1)) goto next_865;
    struct AExpr_List* items_ = (*(expr_.ListLit_1)).t0;
    void* box_6 = (void*)malloc(sizeof(int));
    (*(((int*)box_6))) = 0;
    void* env_20 = box_6;
    struct AExpr_DumpTree_Fun1 fun_22 = (struct AExpr_DumpTree_Fun1){.fun = fun_8, .env = env_20};
    struct DumpTree_List* call_562 = listMap_1(fun_22, items_);
    struct DumpTree_ call_563 = dumpTreeNew_((struct String){.str = "list", .len = 4}, call_562);
    match_216 = call_563;
    goto end_match_861;
next_865:;
    if ((expr_.tag != If_1)) goto next_866;
    struct AExpr_ cond_ = (*(expr_.If_1)).t0;
    struct AExpr_ body_ = (*(expr_.If_1)).t1;
    struct AExpr_ alt_ = (*(expr_.If_1)).t2;
    struct DumpTree_ call_564 = axDump_(cond_);
    struct DumpTree_ call_565 = axDump_(body_);
    struct DumpTree_ call_566 = axDump_(alt_);
    struct DumpTree_List* list_59 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_59->head = call_566;
    list_59->tail = NULL;
    struct DumpTree_List* list_58 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_58->head = call_565;
    list_58->tail = list_59;
    struct DumpTree_List* list_57 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_57->head = call_564;
    list_57->tail = list_58;
    struct DumpTree_ call_567 = dumpTreeNew_((struct String){.str = "if", .len = 2}, list_57);
    match_216 = call_567;
    goto end_match_861;
next_866:;
    if ((expr_.tag != Match_1)) goto next_867;
    struct AExpr_ target_ = (*(expr_.Match_1)).t0;
    struct AArm_List* arms_ = (*(expr_.Match_1)).t1;
    struct DumpTree_ call_568 = axDump_(target_);
    struct DumpTree_List* list_60 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_60->head = call_568;
    list_60->tail = NULL;
    struct DumpTree_ call_569 = dumpTreeNew_((struct String){.str = "match", .len = 5}, list_60);
    match_216 = call_569;
    goto end_match_861;
next_867:;
    if ((expr_.tag != Fun_3)) goto next_868;
    struct APat_List* pats_2 = (*(expr_.Fun_3)).t0;
    struct AExpr_ body_1 = (*(expr_.Fun_3)).t1;
    struct DumpTree_ call_570 = axDump_(body_1);
    void* box_7 = (void*)malloc(sizeof(int));
    (*(((int*)box_7))) = 0;
    void* env_21 = box_7;
    struct APat_DumpTree_Fun1 fun_23 = (struct APat_DumpTree_Fun1){.fun = fun_9, .env = env_21};
    struct DumpTree_List* call_571 = listMap_2(fun_23, pats_2);
    struct DumpTree_ call_572 = dumpTreeNew_((struct String){.str = "fun", .len = 3}, call_571);
    struct DumpTree_ call_573 = dumpTreeAttachNext_(call_570, call_572);
    match_216 = call_573;
    goto end_match_861;
next_868:;
    if ((expr_.tag != Nav_1)) goto next_869;
    struct AExpr_ l_11 = (*(expr_.Nav_1)).t0;
    struct String r_24 = (*(expr_.Nav_1)).t1;
    struct DumpTree_ call_574 = axDump_(l_11);
    struct DumpTree_List* list_61 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_61->head = call_574;
    list_61->tail = NULL;
    struct DumpTree_ call_575 = dumpTreeNew_(str_add((struct String){.str = ".", .len = 1}, r_24), list_61);
    match_216 = call_575;
    goto end_match_861;
next_869:;
    if ((expr_.tag != Index_)) goto next_870;
    struct AExpr_ l_12 = (*(expr_.Index_)).t0;
    struct AExpr_ r_25 = (*(expr_.Index_)).t1;
    struct DumpTree_ call_576 = axDump_(l_12);
    struct DumpTree_List* list_62 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_62->head = call_576;
    list_62->tail = NULL;
    struct DumpTree_ call_577 = dumpTreeNew_((struct String){.str = "index", .len = 5}, list_62);
    match_216 = call_577;
    goto end_match_861;
next_870:;
    if ((expr_.tag != Uni_)) goto next_871;
    if (((*(expr_.Uni_)).t0.tag != Neg_)) goto next_871;
    struct AExpr_ arg_ = (*(expr_.Uni_)).t1;
    struct DumpTree_ call_578 = axDump_(arg_);
    struct DumpTree_List* list_63 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_63->head = call_578;
    list_63->tail = NULL;
    struct DumpTree_ call_579 = dumpTreeNew_((struct String){.str = "-", .len = 1}, list_63);
    match_216 = call_579;
    goto end_match_861;
next_871:;
    if ((expr_.tag != Bin_)) goto next_872;
    struct AExpr_ l_13 = (*(expr_.Bin_)).t1;
    struct AExpr_ r_26 = (*(expr_.Bin_)).t2;
    struct DumpTree_ call_580 = axDump_(l_13);
    struct DumpTree_ call_581 = axDump_(r_26);
    struct DumpTree_List* list_65 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_65->head = call_581;
    list_65->tail = NULL;
    struct DumpTree_List* list_64 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_64->head = call_580;
    list_64->tail = list_65;
    struct DumpTree_ call_582 = dumpTreeNew_((struct String){.str = "bin", .len = 3}, list_64);
    match_216 = call_582;
    goto end_match_861;
next_872:;
    if ((expr_.tag != Range_)) goto next_873;
    struct AExpr_List* items_1 = (*(expr_.Range_)).t0;
    void* box_8 = (void*)malloc(sizeof(int));
    (*(((int*)box_8))) = 0;
    void* env_22 = box_8;
    struct AExpr_DumpTree_Fun1 fun_24 = (struct AExpr_DumpTree_Fun1){.fun = fun_10, .env = env_22};
    struct DumpTree_List* call_583 = listMap_1(fun_24, items_1);
    struct DumpTree_ call_584 = dumpTreeNew_((struct String){.str = "range", .len = 5}, call_583);
    match_216 = call_584;
    goto end_match_861;
next_873:;
    if ((expr_.tag != TupleLit_1)) goto next_874;
    struct AExpr_List* items_2 = (*(expr_.TupleLit_1)).t0;
    void* box_9 = (void*)malloc(sizeof(int));
    (*(((int*)box_9))) = 0;
    void* env_23 = box_9;
    struct AExpr_DumpTree_Fun1 fun_25 = (struct AExpr_DumpTree_Fun1){.fun = fun_11, .env = env_23};
    struct DumpTree_List* call_585 = listMap_1(fun_25, items_2);
    struct DumpTree_ call_586 = dumpTreeNew_((struct String){.str = "tuple", .len = 5}, call_585);
    match_216 = call_586;
    goto end_match_861;
next_874:;
    if ((expr_.tag != Anno_1)) goto next_875;
    struct AExpr_ body_2 = (*(expr_.Anno_1)).t0;
    struct ATy_ ty_2 = (*(expr_.Anno_1)).t1;
    struct DumpTree_ call_587 = axDump_(body_2);
    struct DumpTree_ call_588 = atDump_(ty_2);
    struct DumpTree_List* list_67 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_67->head = call_588;
    list_67->tail = NULL;
    struct DumpTree_List* list_66 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_66->head = call_587;
    list_66->tail = list_67;
    struct DumpTree_ call_589 = dumpTreeNew_((struct String){.str = "anno", .len = 4}, list_66);
    match_216 = call_589;
    goto end_match_861;
next_875:;
    if ((expr_.tag != Semi_1)) goto next_876;
    struct AExpr_List* exprs_ = (*(expr_.Semi_1)).t0;
    void* box_10 = (void*)malloc(sizeof(int));
    (*(((int*)box_10))) = 0;
    void* env_24 = box_10;
    struct AExpr_DumpTree_Fun1 fun_26 = (struct AExpr_DumpTree_Fun1){.fun = fun_12, .env = env_24};
    struct DumpTree_List* call_590 = listMap_1(fun_26, exprs_);
    struct DumpTree_ call_591 = dumpTreeNew_((struct String){.str = "semi", .len = 4}, call_590);
    match_216 = call_591;
    goto end_match_861;
next_876:;
    if ((expr_.tag != Let_1)) goto next_877;
    struct APat_ pat_3 = (*(expr_.Let_1)).t0;
    struct AExpr_ body_3 = (*(expr_.Let_1)).t1;
    struct AExpr_ next_6 = (*(expr_.Let_1)).t2;
    struct DumpTree_ call_592 = axDump_(next_6);
    struct DumpTree_ call_593 = apDump_(pat_3);
    struct DumpTree_ call_594 = axDump_(body_3);
    struct DumpTree_List* list_69 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_69->head = call_594;
    list_69->tail = NULL;
    struct DumpTree_List* list_68 = (struct DumpTree_List*)malloc(sizeof(struct DumpTree_List));
    list_68->head = call_593;
    list_68->tail = list_69;
    struct DumpTree_ call_595 = dumpTreeNew_((struct String){.str = "let", .len = 3}, list_68);
    struct DumpTree_ call_596 = dumpTreeAttachNext_(call_592, call_595);
    match_216 = call_596;
    goto end_match_861;
next_877:;
    if ((expr_.tag != TySynonym_)) goto next_878;
    struct String ident_6 = (*(expr_.TySynonym_)).t0;
    struct ATy_ ty_3 = (*(expr_.TySynonym_)).t1;
    struct DumpTree_ call_597 = dumpTreeNewLeaf_((struct String){.str = "FIXME: TBD", .len = 10});
    match_216 = call_597;
    goto end_match_861;
next_878:;
    if ((expr_.tag != TyUnion_)) goto next_879;
    struct String ident_7 = (*(expr_.TyUnion_)).t0;
    struct AVariant_List* variants_ = (*(expr_.TyUnion_)).t1;
    struct DumpTree_ call_598 = dumpTreeNewLeaf_((struct String){.str = "FIXME: TBD", .len = 10});
    match_216 = call_598;
    goto end_match_861;
next_879:;
    if ((expr_.tag != Open_1)) goto next_880;
    struct StringList* path_ = (*(expr_.Open_1)).t0;
    struct DumpTree_ call_599 = dumpTreeNewLeaf_((struct String){.str = "FIXME: TBD", .len = 10});
    match_216 = call_599;
    goto end_match_861;
next_880:;
    exit(1);
end_match_861:;
    return match_216;
}

int fun_(struct Token_IntIntTuple2Tuple2 arg_96) {
    struct Token_ token_13 = arg_96.t0;
    int y_10 = arg_96.t1.t0;
    int x_16 = arg_96.t1.t1;
    struct String call_600 = tokenToString_(token_13);
    printf("%s (%d, %d)\n", call_600.str, y_10, x_16);
    int call_601 = 0;
    return 0;
}

int fun_13(void* env_11, struct Token_IntIntTuple2Tuple2 arg_14) {
    int call_602 = fun_(arg_14);
    return 0;
}

int fun_1(struct StringIntIntTuple2Tuple2 arg_97) {
    struct String msg_1 = arg_97.t0;
    int y_11 = arg_97.t1.t0;
    int x_17 = arg_97.t1.t1;
    printf("ERROR %s (%d:%d)\n", msg_1.str, (y_11 + 1), (x_17 + 1));
    int call_603 = 0;
    return 0;
}

int fun_14(void* env_12, struct StringIntIntTuple2Tuple2 arg_15) {
    int call_604 = fun_1(arg_15);
    return 0;
}

struct StringStringFun1 {
    struct String(*fun)(void*, struct String);
    void* env;
};

int doSelf_(struct StringStringFun1 fileReadAllText_1) {
    struct String app_5 = fileReadAllText_1.fun(fileReadAllText_1.env, (struct String){.str = "MiloneLang/Lexing.fs", .len = 20});
    struct String source_ = app_5;
    struct Token_IntIntTuple2Tuple2List* call_605 = tokenize_(source_);
    struct Token_IntIntTuple2Tuple2List* tokens_ = call_605;
    void* box_11 = (void*)malloc(sizeof(int));
    (*(((int*)box_11))) = 0;
    void* env_25 = box_11;
    struct Token_IntIntTuple2Tuple2UnitFun1 fun_27 = (struct Token_IntIntTuple2Tuple2UnitFun1){.fun = fun_13, .env = env_25};
    int call_606 = listIter_2(fun_27, tokens_);
    struct AExpr_StringIntIntTuple2Tuple2ListTuple2 call_607 = parse_(tokens_);
    struct AExpr_ ast_ = call_607.t0;
    struct StringIntIntTuple2Tuple2List* errors_ = call_607.t1;
    printf("AST:\n");
    int call_608 = 0;
    struct DumpTree_ call_609 = axDump_(ast_);
    struct String call_610 = dumpTreeToString_(call_609);
    printf("%s\n", call_610.str);
    int call_611 = 0;
    void* box_12 = (void*)malloc(sizeof(int));
    (*(((int*)box_12))) = 0;
    void* env_26 = box_12;
    struct StringIntIntTuple2Tuple2UnitFun1 fun_28 = (struct StringIntIntTuple2Tuple2UnitFun1){.fun = fun_14, .env = env_26};
    int call_612 = listIter_1(fun_28, errors_);
    return 0;
}

struct String fileReadAllText_(struct String fileName_) {
    struct String call_613 = file_read_all_text(fileName_);
    return call_613;
}

struct String fun_15(void* env_13, struct String arg_16) {
    struct String call_614 = fileReadAllText_(arg_16);
    return call_614;
}

int main() {
    struct IntIntTuple2 tuple_347;
    tuple_347.t0 = (0 - 1);
    tuple_347.t1 = (0 - 1);
    struct IntIntTuple2 noLoc_ = tuple_347;
    char call_615 = ((char)0);
    char charNull_ = call_615;
    void* box_13 = (void*)malloc(sizeof(int));
    (*(((int*)box_13))) = 0;
    void* env_27 = box_13;
    struct StringStringFun1 fun_29 = (struct StringStringFun1){.fun = fun_15, .env = env_27};
    int call_616 = doSelf_(fun_29);
    return call_616;
}
