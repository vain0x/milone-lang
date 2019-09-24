#include "milone.h"

struct StringList;

int listIsEmpty_1(struct StringList* xs_2);

enum TokenKind_Tag;

struct TokenKind_;

struct TokenKind_IntIntTuple3;

struct TokenKind_IntIntTuple3List;

struct TokenKind_IntIntTuple3List* go_20(struct TokenKind_IntIntTuple3List* acc_, struct TokenKind_IntIntTuple3List* xs_4);

struct StringList* go_19(struct StringList* acc_, struct StringList* xs_4);

enum Token_Tag;

struct Token_;

struct IntIntTuple2;

struct Token_IntIntTuple2Tuple2;

struct Token_IntIntTuple2Tuple2List;

struct Token_IntIntTuple2Tuple2List* go_18(struct Token_IntIntTuple2Tuple2List* acc_, struct Token_IntIntTuple2Tuple2List* xs_4);

struct TokenKind_IntIntTuple3List* listRev_3(struct TokenKind_IntIntTuple3List* xs_3);

struct StringList* listRev_2(struct StringList* xs_3);

struct Token_IntIntTuple2Tuple2List* listRev_1(struct Token_IntIntTuple2Tuple2List* xs_3);

int go_17(int len_, struct StringList* xs_7);

int listLength_1(struct StringList* xs_6);

int intMin_(int x_4, int y_1);

int go_3(struct String s_, char c_, int i_);

int strContainsChar_(char c_, struct String s_);

struct String strSlice_(int start_, int endIndex_, struct String s_1);

struct StringStringListTuple2;

struct StringStringListTuple2 go_4(struct StringList* xs_13, int xn_);

struct String strConcat_(struct StringList* xs_12);

struct Token_ failwith_1(struct String str_);

int charIsSpace_(char c_1);

int charIsDigit_(char c_2);

int charIsAlpha_(char c_3);

int charIsIdent_(char c_4);

int charIsOp_(char c_5);

int charIsPun_(char c_6);

int go_5(struct String s_3, struct String prefix_, int pi_, int si_);

int strNthStartsWith_(int i_1, struct String prefix_, struct String s_3);

struct TokenKind_IntIntTuple3ListStringIntTuple3;

struct TokenKind_IntIntTuple3ListStringIntTuple3 scanError_(struct TokenKind_IntIntTuple3ListStringIntTuple3 arg_1);

int go_6(struct String text_1, int i_4);

struct TokenKind_IntIntTuple3ListStringIntTuple3 scanSpace_(struct TokenKind_IntIntTuple3ListStringIntTuple3 arg_2);

int go_7(struct String text_2, int i_6);

struct TokenKind_IntIntTuple3ListStringIntTuple3 scanLine_(struct TokenKind_IntIntTuple3ListStringIntTuple3 arg_3);

struct TokenKind_IntIntTuple3ListStringIntTuple3 scanPun_(struct TokenKind_IntIntTuple3ListStringIntTuple3 arg_4);

int go_8(struct String text_4, int i_9);

struct TokenKind_IntIntTuple3ListStringIntTuple3 scanOp_(struct TokenKind_IntIntTuple3ListStringIntTuple3 arg_5);

int go_9(struct String text_5, int i_11);

struct TokenKind_IntIntTuple3ListStringIntTuple3 scanIdent_(struct TokenKind_IntIntTuple3ListStringIntTuple3 arg_6);

int go_10(struct String text_6, int i_13);

struct TokenKind_IntIntTuple3ListStringIntTuple3 scanIntLit_(struct TokenKind_IntIntTuple3ListStringIntTuple3 arg_7);

struct TokenKind_IntTuple2;

struct TokenKind_IntTuple2 go_11(struct String text_7, int i_15);

struct TokenKind_IntIntTuple3ListStringIntTuple3 scanCharLit_(struct TokenKind_IntIntTuple3ListStringIntTuple3 arg_8);

struct TokenKind_IntTuple2 go_12(struct String text_8, int i_17);

struct TokenKind_IntIntTuple3ListStringIntTuple3 scanStrLit_(struct TokenKind_IntIntTuple3ListStringIntTuple3 arg_9);

int follow_(int i_18, struct String text_10, struct String prefix_1);

struct StringTokenKind_IntIntTuple3ListTuple2;

struct StringTokenKind_IntIntTuple3ListTuple2 go_13(struct TokenKind_IntIntTuple3ListStringIntTuple3 arg_10);

struct StringTokenKind_IntIntTuple3ListTuple2 scanRoot_(struct String text_9);

struct IntIntTuple2 go_14(int r_1, struct String text_11, int y_4, int x_8, int i_19);

struct IntIntTuple2 advanceTextPos_(struct IntIntTuple2 arg_11, struct String text_11, int l_1, int r_1);

struct Token_ tokenFromIdent_(struct String text_12, int l_2, int r_2);

struct Token_ tokenFromOp_(struct String text_13, int l_3, int r_3);

struct Token_ tokenFromPun_(struct String text_14, int l_4, int r_4);

struct Token_ tokenFromIntLit_(struct String text_15, int l_5, int r_5);

struct Token_ tokenFromCharLit_(char charNull_, struct String text_16, int l_6, int r_6);

int next_(int r_7, struct String text_17, int i_22);

struct String go_15(int r_7, struct String text_17, struct StringList* acc_12, int i_21);

struct Token_ tokenFromStrLit_(struct String text_17, int l_7, int r_7);

struct Token_ recognizeToken_(char charNull_, struct TokenKind_ kind_3, struct String text_18, int l_8, int r_8);

struct Token_IntIntTuple2Tuple2List* go_16(struct String text_19, char charNull_, struct Token_IntIntTuple2Tuple2List* acc_14, int y_5, int x_9, int last_, struct TokenKind_IntIntTuple3List* tokens_1);

struct Token_IntIntTuple2Tuple2List* recognizeTokens_(char charNull_, struct StringTokenKind_IntIntTuple3ListTuple2 arg_12);

struct Token_IntIntTuple2Tuple2List* tokenize_(char charNull_, struct String text_20);

struct String fileReadAllText_(struct String fileName_);

struct String tokenKindToString_(struct TokenKind_ kind_);

struct String tokenToString_(struct Token_ token_);

struct Token_IntIntTuple2Tuple2UnitFun1;

int listIter_1(struct Token_IntIntTuple2Tuple2UnitFun1 f_, struct Token_IntIntTuple2Tuple2List* xs_);

int fun_(struct Token_IntIntTuple2Tuple2 arg_13);

int fun_1(void* env_, struct Token_IntIntTuple2Tuple2 arg_);

int main();

struct StringList {
    struct String head;
    struct StringList* tail;
};

int listIsEmpty_1(struct StringList* xs_2) {
    int match_;
    if ((!((!(xs_2))))) goto next_2;
    match_ = 1;
    goto end_match_1;
next_2:;
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    return match_;
}

enum TokenKind_Tag {
    Error_,
    Ident_,
    IntLit_,
    CharLit_,
    StrLit_,
    Op_,
    Pun_,
};

struct TokenKind_ {
    enum TokenKind_Tag tag;
};

struct TokenKind_IntIntTuple3 {
    struct TokenKind_ t0;
    int t1;
    int t2;
};

struct TokenKind_IntIntTuple3List {
    struct TokenKind_IntIntTuple3 head;
    struct TokenKind_IntIntTuple3List* tail;
};

struct TokenKind_IntIntTuple3List* go_20(struct TokenKind_IntIntTuple3List* acc_, struct TokenKind_IntIntTuple3List* xs_4) {
    struct TokenKind_IntIntTuple3List* match_1;
    if ((!((!(xs_4))))) goto next_5;
    match_1 = acc_;
    goto end_match_4;
next_5:;
    if ((!(xs_4))) goto next_6;
    struct TokenKind_IntIntTuple3 x_2 = xs_4->head;
    struct TokenKind_IntIntTuple3List* xs_5 = xs_4->tail;
    struct TokenKind_IntIntTuple3List* list_ = (struct TokenKind_IntIntTuple3List*)malloc(sizeof(struct TokenKind_IntIntTuple3List));
    list_->head = x_2;
    list_->tail = acc_;
    struct TokenKind_IntIntTuple3List* call_ = go_20(list_, xs_5);
    match_1 = call_;
    goto end_match_4;
next_6:;
    exit(1);
end_match_4:;
    return match_1;
}

struct StringList* go_19(struct StringList* acc_, struct StringList* xs_4) {
    struct StringList* match_2;
    if ((!((!(xs_4))))) goto next_8;
    match_2 = acc_;
    goto end_match_7;
next_8:;
    if ((!(xs_4))) goto next_9;
    struct String x_2 = xs_4->head;
    struct StringList* xs_5 = xs_4->tail;
    struct StringList* list_1 = (struct StringList*)malloc(sizeof(struct StringList));
    list_1->head = x_2;
    list_1->tail = acc_;
    struct StringList* call_1 = go_19(list_1, xs_5);
    match_2 = call_1;
    goto end_match_7;
next_9:;
    exit(1);
end_match_7:;
    return match_2;
}

enum Token_Tag {
    Bool_,
    Int_,
    Char_,
    Str_,
    Ident_1,
    Do_,
    Let_,
    Rec_,
    If_,
    Then_,
    Else_,
    Match_,
    With_,
    As_,
    When_,
    ParenL_,
    ParenR_,
    BracketL_,
    BracketR_,
    Colon_,
    Dot_,
    Range_,
    Pipe_,
    Arrow_,
    Punct_,
    Private_,
    Internal_,
    Public_,
    Module_,
    Namespace_,
    Open_,
    Type_,
    Of_,
    Fun_,
    In_,
};

struct Token_ {
    enum Token_Tag tag;
    union {
        int* Bool_;
        int* Int_;
        char* Char_;
        struct String* Str_;
        struct String* Ident_1;
        struct String* Punct_;
    };
};

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

struct Token_IntIntTuple2Tuple2List* go_18(struct Token_IntIntTuple2Tuple2List* acc_, struct Token_IntIntTuple2Tuple2List* xs_4) {
    struct Token_IntIntTuple2Tuple2List* match_3;
    if ((!((!(xs_4))))) goto next_11;
    match_3 = acc_;
    goto end_match_10;
next_11:;
    if ((!(xs_4))) goto next_12;
    struct Token_IntIntTuple2Tuple2 x_2 = xs_4->head;
    struct Token_IntIntTuple2Tuple2List* xs_5 = xs_4->tail;
    struct Token_IntIntTuple2Tuple2List* list_2 = (struct Token_IntIntTuple2Tuple2List*)malloc(sizeof(struct Token_IntIntTuple2Tuple2List));
    list_2->head = x_2;
    list_2->tail = acc_;
    struct Token_IntIntTuple2Tuple2List* call_2 = go_18(list_2, xs_5);
    match_3 = call_2;
    goto end_match_10;
next_12:;
    exit(1);
end_match_10:;
    return match_3;
}

struct TokenKind_IntIntTuple3List* listRev_3(struct TokenKind_IntIntTuple3List* xs_3) {
    struct TokenKind_IntIntTuple3List* call_3 = go_20(NULL, xs_3);
    return call_3;
}

struct StringList* listRev_2(struct StringList* xs_3) {
    struct StringList* call_4 = go_19(NULL, xs_3);
    return call_4;
}

struct Token_IntIntTuple2Tuple2List* listRev_1(struct Token_IntIntTuple2Tuple2List* xs_3) {
    struct Token_IntIntTuple2Tuple2List* call_5 = go_18(NULL, xs_3);
    return call_5;
}

int go_17(int len_, struct StringList* xs_7) {
    int match_4;
    if ((!((!(xs_7))))) goto next_14;
    match_4 = len_;
    goto end_match_13;
next_14:;
    if ((!(xs_7))) goto next_15;
    struct StringList* xs_8 = xs_7->tail;
    int call_6 = go_17((len_ + 1), xs_8);
    match_4 = call_6;
    goto end_match_13;
next_15:;
    exit(1);
end_match_13:;
    return match_4;
}

int listLength_1(struct StringList* xs_6) {
    int call_7 = go_17(0, xs_6);
    return call_7;
}

int intMin_(int x_4, int y_1) {
    int match_5;
    if ((y_1 >= x_4)) goto next_17;
    match_5 = y_1;
    goto end_match_16;
next_17:;
    if ((y_1 < x_4)) goto next_18;
    match_5 = x_4;
    goto end_match_16;
next_18:;
    exit(1);
end_match_16:;
    return match_5;
}

int go_3(struct String s_, char c_, int i_) {
    int match_6;
    if ((i_ >= s_.len)) goto next_20;
    int match_7;
    if ((s_.str[i_] != c_)) goto next_23;
    match_7 = 1;
    goto end_match_22;
next_23:;
    if ((s_.str[i_] == c_)) goto next_24;
    int call_8 = go_3(s_, c_, (i_ + 1));
    match_7 = call_8;
    goto end_match_22;
next_24:;
    exit(1);
end_match_22:;
    match_6 = match_7;
    goto end_match_19;
next_20:;
    if ((i_ < s_.len)) goto next_21;
    match_6 = 0;
    goto end_match_19;
next_21:;
    exit(1);
end_match_19:;
    return match_6;
}

int strContainsChar_(char c_, struct String s_) {
    int call_9 = go_3(s_, c_, 0);
    return call_9;
}

struct String strSlice_(int start_, int endIndex_, struct String s_1) {
    int match_8;
    if ((endIndex_ < start_)) goto next_26;
    match_8 = (s_1.len >= endIndex_);
    goto end_match_25;
next_26:;
    if ((endIndex_ >= start_)) goto next_27;
    match_8 = 0;
    goto end_match_25;
next_27:;
    exit(1);
end_match_25:;
    milone_assert(match_8, 53, 2);
    int call_10 = 0;
    struct String match_9;
    if ((start_ < endIndex_)) goto next_29;
    match_9 = (struct String){.str = "", .len = 0};
    goto end_match_28;
next_29:;
    if ((start_ >= endIndex_)) goto next_30;
    struct String call_11 = str_get_slice(start_, (endIndex_ - 1), s_1);
    match_9 = call_11;
    goto end_match_28;
next_30:;
    exit(1);
end_match_28:;
    return match_9;
}

struct StringStringListTuple2 {
    struct String t0;
    struct StringList* t1;
};

struct StringStringListTuple2 go_4(struct StringList* xs_13, int xn_) {
    struct StringStringListTuple2 match_10;
    if ((!((!(xs_13))))) goto next_32;
    milone_assert((xn_ == 0), 67, 6);
    int call_12 = 0;
    struct StringStringListTuple2 tuple_;
    tuple_.t0 = (struct String){.str = "", .len = 0};
    tuple_.t1 = NULL;
    match_10 = tuple_;
    goto end_match_31;
next_32:;
    if ((!(xs_13))) goto next_33;
    struct String x_5 = xs_13->head;
    struct StringList* xs_14 = xs_13->tail;
    if ((xn_ != 1)) goto next_33;
    struct StringStringListTuple2 tuple_1;
    tuple_1.t0 = x_5;
    tuple_1.t1 = xs_14;
    match_10 = tuple_1;
    goto end_match_31;
next_33:;
    if ((!(xs_13))) goto next_34;
    struct String x_6 = xs_13->head;
    if ((!(xs_13->tail))) goto next_34;
    struct String y_2 = xs_13->tail->head;
    struct StringList* xs_15 = xs_13->tail->tail;
    if ((xn_ != 2)) goto next_34;
    struct StringStringListTuple2 tuple_2;
    tuple_2.t0 = str_add(x_6, y_2);
    tuple_2.t1 = xs_15;
    match_10 = tuple_2;
    goto end_match_31;
next_34:;
    struct StringList* xs_16 = xs_13;
    int m_ = (xn_ / 2);
    struct StringStringListTuple2 call_13 = go_4(xs_16, m_);
    struct String l_ = call_13.t0;
    struct StringList* xs_17 = call_13.t1;
    struct StringStringListTuple2 call_14 = go_4(xs_17, (xn_ - m_));
    struct String r_ = call_14.t0;
    struct StringList* xs_18 = call_14.t1;
    struct StringStringListTuple2 tuple_3;
    tuple_3.t0 = str_add(l_, r_);
    tuple_3.t1 = xs_18;
    match_10 = tuple_3;
    goto end_match_31;
next_35:;
end_match_31:;
    return match_10;
}

struct String strConcat_(struct StringList* xs_12) {
    int call_15 = listLength_1(xs_12);
    int n_ = call_15;
    struct StringStringListTuple2 call_16 = go_4(xs_12, n_);
    struct String s_2 = call_16.t0;
    struct StringList* xs_19 = call_16.t1;
    int call_17 = listIsEmpty_1(xs_19);
    milone_assert(call_17, 84, 2);
    int call_18 = 0;
    return s_2;
}

struct Token_ failwith_1(struct String str_) {
    printf("FATAL ERROR: %s\n", str_.str);
    int call_19 = 0;
    exit(1);
    return ((struct Token_){});
}

int charIsSpace_(char c_1) {
    int match_11;
    int match_12;
    int match_13;
    if ((c_1 != ' ')) goto next_39;
    match_13 = 1;
    goto end_match_38;
next_39:;
    if ((c_1 == ' ')) goto next_40;
    match_13 = (c_1 == '\t');
    goto end_match_38;
next_40:;
    exit(1);
end_match_38:;
    if ((!(match_13))) goto next_41;
    match_12 = 1;
    goto end_match_37;
next_41:;
    if (match_13) goto next_42;
    match_12 = (c_1 == '\r');
    goto end_match_37;
next_42:;
    exit(1);
end_match_37:;
    if ((!(match_12))) goto next_43;
    match_11 = 1;
    goto end_match_36;
next_43:;
    if (match_12) goto next_44;
    match_11 = (c_1 == '\n');
    goto end_match_36;
next_44:;
    exit(1);
end_match_36:;
    return match_11;
}

int charIsDigit_(char c_2) {
    int match_14;
    if ((c_2 < '0')) goto next_46;
    match_14 = ('9' >= c_2);
    goto end_match_45;
next_46:;
    if ((c_2 >= '0')) goto next_47;
    match_14 = 0;
    goto end_match_45;
next_47:;
    exit(1);
end_match_45:;
    return match_14;
}

int charIsAlpha_(char c_3) {
    int match_15;
    int match_16;
    if ((c_3 < 'a')) goto next_50;
    match_16 = ('z' >= c_3);
    goto end_match_49;
next_50:;
    if ((c_3 >= 'a')) goto next_51;
    match_16 = 0;
    goto end_match_49;
next_51:;
    exit(1);
end_match_49:;
    if ((!(match_16))) goto next_52;
    match_15 = 1;
    goto end_match_48;
next_52:;
    if (match_16) goto next_53;
    int match_17;
    if ((c_3 < 'A')) goto next_55;
    match_17 = ('Z' >= c_3);
    goto end_match_54;
next_55:;
    if ((c_3 >= 'A')) goto next_56;
    match_17 = 0;
    goto end_match_54;
next_56:;
    exit(1);
end_match_54:;
    match_15 = match_17;
    goto end_match_48;
next_53:;
    exit(1);
end_match_48:;
    return match_15;
}

int charIsIdent_(char c_4) {
    int match_18;
    int match_19;
    if ((c_4 != '_')) goto next_59;
    match_19 = 1;
    goto end_match_58;
next_59:;
    if ((c_4 == '_')) goto next_60;
    int call_20 = charIsDigit_(c_4);
    match_19 = call_20;
    goto end_match_58;
next_60:;
    exit(1);
end_match_58:;
    if ((!(match_19))) goto next_61;
    match_18 = 1;
    goto end_match_57;
next_61:;
    if (match_19) goto next_62;
    int call_21 = charIsAlpha_(c_4);
    match_18 = call_21;
    goto end_match_57;
next_62:;
    exit(1);
end_match_57:;
    return match_18;
}

int charIsOp_(char c_5) {
    int call_22 = strContainsChar_(c_5, (struct String){.str = "+-*/%=<>^&|:@;.,", .len = 16});
    return call_22;
}

int charIsPun_(char c_6) {
    int call_23 = strContainsChar_(c_6, (struct String){.str = "()[]", .len = 4});
    return call_23;
}

int go_5(struct String s_3, struct String prefix_, int pi_, int si_) {
    int match_20;
    if ((pi_ != prefix_.len)) goto next_64;
    match_20 = 1;
    goto end_match_63;
next_64:;
    if ((pi_ == prefix_.len)) goto next_65;
    int match_21;
    int match_22;
    if ((si_ >= s_3.len)) goto next_68;
    match_22 = (prefix_.str[pi_] == s_3.str[si_]);
    goto end_match_67;
next_68:;
    if ((si_ < s_3.len)) goto next_69;
    match_22 = 0;
    goto end_match_67;
next_69:;
    exit(1);
end_match_67:;
    if ((!(match_22))) goto next_70;
    int call_24 = go_5(s_3, prefix_, (pi_ + 1), (si_ + 1));
    match_21 = call_24;
    goto end_match_66;
next_70:;
    if (match_22) goto next_71;
    match_21 = 0;
    goto end_match_66;
next_71:;
    exit(1);
end_match_66:;
    match_20 = match_21;
    goto end_match_63;
next_65:;
    exit(1);
end_match_63:;
    return match_20;
}

int strNthStartsWith_(int i_1, struct String prefix_, struct String s_3) {
    int match_23;
    if ((s_3.len < (i_1 + prefix_.len))) goto next_73;
    int call_25 = go_5(s_3, prefix_, 0, i_1);
    match_23 = call_25;
    goto end_match_72;
next_73:;
    if ((s_3.len >= (i_1 + prefix_.len))) goto next_74;
    match_23 = 0;
    goto end_match_72;
next_74:;
    exit(1);
end_match_72:;
    return match_23;
}

struct TokenKind_IntIntTuple3ListStringIntTuple3 {
    struct TokenKind_IntIntTuple3List* t0;
    struct String t1;
    int t2;
};

struct TokenKind_IntIntTuple3ListStringIntTuple3 scanError_(struct TokenKind_IntIntTuple3ListStringIntTuple3 arg_1) {
    struct TokenKind_IntIntTuple3List* acc_2 = arg_1.t0;
    struct String text_ = arg_1.t1;
    int i_2 = arg_1.t2;
    struct TokenKind_IntIntTuple3 tuple_5;
    tuple_5.t0 = (struct TokenKind_){.tag = Error_};
    tuple_5.t1 = i_2;
    tuple_5.t2 = (i_2 + 1);
    struct TokenKind_IntIntTuple3List* list_3 = (struct TokenKind_IntIntTuple3List*)malloc(sizeof(struct TokenKind_IntIntTuple3List));
    list_3->head = tuple_5;
    list_3->tail = acc_2;
    struct TokenKind_IntIntTuple3ListStringIntTuple3 tuple_4;
    tuple_4.t0 = list_3;
    tuple_4.t1 = text_;
    tuple_4.t2 = (i_2 + 1);
    return tuple_4;
}

int go_6(struct String text_1, int i_4) {
    int match_24;
    int match_25;
    if ((i_4 >= text_1.len)) goto next_77;
    int call_26 = charIsSpace_(text_1.str[i_4]);
    match_25 = call_26;
    goto end_match_76;
next_77:;
    if ((i_4 < text_1.len)) goto next_78;
    match_25 = 0;
    goto end_match_76;
next_78:;
    exit(1);
end_match_76:;
    if ((!(match_25))) goto next_79;
    int call_27 = go_6(text_1, (i_4 + 1));
    match_24 = call_27;
    goto end_match_75;
next_79:;
    if (match_25) goto next_80;
    match_24 = i_4;
    goto end_match_75;
next_80:;
    exit(1);
end_match_75:;
    return match_24;
}

struct TokenKind_IntIntTuple3ListStringIntTuple3 scanSpace_(struct TokenKind_IntIntTuple3ListStringIntTuple3 arg_2) {
    struct TokenKind_IntIntTuple3List* acc_3 = arg_2.t0;
    struct String text_1 = arg_2.t1;
    int i_3 = arg_2.t2;
    int call_28 = charIsSpace_(text_1.str[i_3]);
    milone_assert(call_28, 85, 2);
    int call_29 = 0;
    int call_30 = go_6(text_1, i_3);
    struct TokenKind_IntIntTuple3ListStringIntTuple3 tuple_6;
    tuple_6.t0 = acc_3;
    tuple_6.t1 = text_1;
    tuple_6.t2 = call_30;
    return tuple_6;
}

int go_7(struct String text_2, int i_6) {
    int match_26;
    if ((i_6 != text_2.len)) goto next_82;
    match_26 = i_6;
    goto end_match_81;
next_82:;
    if ((i_6 == text_2.len)) goto next_83;
    int match_27;
    if ((text_2.str[i_6] != '\n')) goto next_85;
    match_27 = (i_6 + 1);
    goto end_match_84;
next_85:;
    if ((text_2.str[i_6] == '\n')) goto next_86;
    int call_31 = go_7(text_2, (i_6 + 1));
    match_27 = call_31;
    goto end_match_84;
next_86:;
    exit(1);
end_match_84:;
    match_26 = match_27;
    goto end_match_81;
next_83:;
    exit(1);
end_match_81:;
    return match_26;
}

struct TokenKind_IntIntTuple3ListStringIntTuple3 scanLine_(struct TokenKind_IntIntTuple3ListStringIntTuple3 arg_3) {
    struct TokenKind_IntIntTuple3List* acc_4 = arg_3.t0;
    struct String text_2 = arg_3.t1;
    int i_5 = arg_3.t2;
    int call_32 = go_7(text_2, i_5);
    struct TokenKind_IntIntTuple3ListStringIntTuple3 tuple_7;
    tuple_7.t0 = acc_4;
    tuple_7.t1 = text_2;
    tuple_7.t2 = call_32;
    return tuple_7;
}

struct TokenKind_IntIntTuple3ListStringIntTuple3 scanPun_(struct TokenKind_IntIntTuple3ListStringIntTuple3 arg_4) {
    struct TokenKind_IntIntTuple3List* acc_5 = arg_4.t0;
    struct String text_3 = arg_4.t1;
    int i_7 = arg_4.t2;
    int call_33 = charIsPun_(text_3.str[i_7]);
    milone_assert(call_33, 104, 2);
    int call_34 = 0;
    int endIndex_1 = (i_7 + 1);
    struct TokenKind_IntIntTuple3 tuple_9;
    tuple_9.t0 = (struct TokenKind_){.tag = Pun_};
    tuple_9.t1 = i_7;
    tuple_9.t2 = endIndex_1;
    struct TokenKind_IntIntTuple3List* list_4 = (struct TokenKind_IntIntTuple3List*)malloc(sizeof(struct TokenKind_IntIntTuple3List));
    list_4->head = tuple_9;
    list_4->tail = acc_5;
    struct TokenKind_IntIntTuple3ListStringIntTuple3 tuple_8;
    tuple_8.t0 = list_4;
    tuple_8.t1 = text_3;
    tuple_8.t2 = endIndex_1;
    return tuple_8;
}

int go_8(struct String text_4, int i_9) {
    int match_28;
    int match_29;
    if ((i_9 >= text_4.len)) goto next_89;
    int call_35 = charIsOp_(text_4.str[i_9]);
    match_29 = call_35;
    goto end_match_88;
next_89:;
    if ((i_9 < text_4.len)) goto next_90;
    match_29 = 0;
    goto end_match_88;
next_90:;
    exit(1);
end_match_88:;
    if ((!(match_29))) goto next_91;
    int call_36 = go_8(text_4, (i_9 + 1));
    match_28 = call_36;
    goto end_match_87;
next_91:;
    if (match_29) goto next_92;
    match_28 = i_9;
    goto end_match_87;
next_92:;
    exit(1);
end_match_87:;
    return match_28;
}

struct TokenKind_IntIntTuple3ListStringIntTuple3 scanOp_(struct TokenKind_IntIntTuple3ListStringIntTuple3 arg_5) {
    struct TokenKind_IntIntTuple3List* acc_6 = arg_5.t0;
    struct String text_4 = arg_5.t1;
    int i_8 = arg_5.t2;
    int call_37 = charIsOp_(text_4.str[i_8]);
    milone_assert(call_37, 109, 2);
    int call_38 = 0;
    int call_39 = go_8(text_4, i_8);
    int endIndex_2 = call_39;
    struct TokenKind_IntIntTuple3 tuple_11;
    tuple_11.t0 = (struct TokenKind_){.tag = Op_};
    tuple_11.t1 = i_8;
    tuple_11.t2 = endIndex_2;
    struct TokenKind_IntIntTuple3List* list_5 = (struct TokenKind_IntIntTuple3List*)malloc(sizeof(struct TokenKind_IntIntTuple3List));
    list_5->head = tuple_11;
    list_5->tail = acc_6;
    struct TokenKind_IntIntTuple3ListStringIntTuple3 tuple_10;
    tuple_10.t0 = list_5;
    tuple_10.t1 = text_4;
    tuple_10.t2 = endIndex_2;
    return tuple_10;
}

int go_9(struct String text_5, int i_11) {
    int match_30;
    int match_31;
    if ((i_11 >= text_5.len)) goto next_95;
    int call_40 = charIsIdent_(text_5.str[i_11]);
    match_31 = call_40;
    goto end_match_94;
next_95:;
    if ((i_11 < text_5.len)) goto next_96;
    match_31 = 0;
    goto end_match_94;
next_96:;
    exit(1);
end_match_94:;
    if ((!(match_31))) goto next_97;
    int call_41 = go_9(text_5, (i_11 + 1));
    match_30 = call_41;
    goto end_match_93;
next_97:;
    if (match_31) goto next_98;
    match_30 = i_11;
    goto end_match_93;
next_98:;
    exit(1);
end_match_93:;
    return match_30;
}

struct TokenKind_IntIntTuple3ListStringIntTuple3 scanIdent_(struct TokenKind_IntIntTuple3ListStringIntTuple3 arg_6) {
    struct TokenKind_IntIntTuple3List* acc_7 = arg_6.t0;
    struct String text_5 = arg_6.t1;
    int i_10 = arg_6.t2;
    int match_32;
    int call_42 = charIsIdent_(text_5.str[i_10]);
    if ((!(call_42))) goto next_100;
    int call_43 = charIsDigit_(text_5.str[i_10]);
    match_32 = (!(call_43));
    goto end_match_99;
next_100:;
    if (call_42) goto next_101;
    match_32 = 0;
    goto end_match_99;
next_101:;
    exit(1);
end_match_99:;
    milone_assert(match_32, 119, 2);
    int call_44 = 0;
    int call_45 = go_9(text_5, i_10);
    int endIndex_3 = call_45;
    struct TokenKind_IntIntTuple3 tuple_13;
    tuple_13.t0 = (struct TokenKind_){.tag = Ident_};
    tuple_13.t1 = i_10;
    tuple_13.t2 = endIndex_3;
    struct TokenKind_IntIntTuple3List* list_6 = (struct TokenKind_IntIntTuple3List*)malloc(sizeof(struct TokenKind_IntIntTuple3List));
    list_6->head = tuple_13;
    list_6->tail = acc_7;
    struct TokenKind_IntIntTuple3ListStringIntTuple3 tuple_12;
    tuple_12.t0 = list_6;
    tuple_12.t1 = text_5;
    tuple_12.t2 = endIndex_3;
    return tuple_12;
}

int go_10(struct String text_6, int i_13) {
    int match_33;
    int match_34;
    if ((i_13 >= text_6.len)) goto next_104;
    int call_46 = charIsDigit_(text_6.str[i_13]);
    match_34 = call_46;
    goto end_match_103;
next_104:;
    if ((i_13 < text_6.len)) goto next_105;
    match_34 = 0;
    goto end_match_103;
next_105:;
    exit(1);
end_match_103:;
    if ((!(match_34))) goto next_106;
    int call_47 = go_10(text_6, (i_13 + 1));
    match_33 = call_47;
    goto end_match_102;
next_106:;
    if (match_34) goto next_107;
    match_33 = i_13;
    goto end_match_102;
next_107:;
    exit(1);
end_match_102:;
    return match_33;
}

struct TokenKind_IntIntTuple3ListStringIntTuple3 scanIntLit_(struct TokenKind_IntIntTuple3ListStringIntTuple3 arg_7) {
    struct TokenKind_IntIntTuple3List* acc_8 = arg_7.t0;
    struct String text_6 = arg_7.t1;
    int i_12 = arg_7.t2;
    int call_48 = charIsDigit_(text_6.str[i_12]);
    milone_assert(call_48, 129, 2);
    int call_49 = 0;
    int call_50 = go_10(text_6, i_12);
    int endIndex_4 = call_50;
    struct TokenKind_IntIntTuple3 tuple_15;
    tuple_15.t0 = (struct TokenKind_){.tag = IntLit_};
    tuple_15.t1 = i_12;
    tuple_15.t2 = endIndex_4;
    struct TokenKind_IntIntTuple3List* list_7 = (struct TokenKind_IntIntTuple3List*)malloc(sizeof(struct TokenKind_IntIntTuple3List));
    list_7->head = tuple_15;
    list_7->tail = acc_8;
    struct TokenKind_IntIntTuple3ListStringIntTuple3 tuple_14;
    tuple_14.t0 = list_7;
    tuple_14.t1 = text_6;
    tuple_14.t2 = endIndex_4;
    return tuple_14;
}

struct TokenKind_IntTuple2 {
    struct TokenKind_ t0;
    int t1;
};

struct TokenKind_IntTuple2 go_11(struct String text_7, int i_15) {
    struct TokenKind_IntTuple2 match_35;
    int match_36;
    if (((i_15 + 1) >= text_7.len)) goto next_110;
    match_36 = (text_7.str[i_15] == '\\');
    goto end_match_109;
next_110:;
    if (((i_15 + 1) < text_7.len)) goto next_111;
    match_36 = 0;
    goto end_match_109;
next_111:;
    exit(1);
end_match_109:;
    if ((!(match_36))) goto next_112;
    struct TokenKind_IntTuple2 call_51 = go_11(text_7, (i_15 + 2));
    match_35 = call_51;
    goto end_match_108;
next_112:;
    if (match_36) goto next_113;
    struct TokenKind_IntTuple2 match_37;
    int match_38;
    if ((i_15 >= text_7.len)) goto next_116;
    match_38 = (text_7.str[i_15] == '\'');
    goto end_match_115;
next_116:;
    if ((i_15 < text_7.len)) goto next_117;
    match_38 = 0;
    goto end_match_115;
next_117:;
    exit(1);
end_match_115:;
    if ((!(match_38))) goto next_118;
    struct TokenKind_IntTuple2 tuple_16;
    tuple_16.t0 = (struct TokenKind_){.tag = CharLit_};
    tuple_16.t1 = (i_15 + 1);
    match_37 = tuple_16;
    goto end_match_114;
next_118:;
    if (match_38) goto next_119;
    struct TokenKind_IntTuple2 match_39;
    int match_40;
    if ((i_15 >= text_7.len)) goto next_122;
    match_40 = (text_7.str[i_15] != '\n');
    goto end_match_121;
next_122:;
    if ((i_15 < text_7.len)) goto next_123;
    match_40 = 0;
    goto end_match_121;
next_123:;
    exit(1);
end_match_121:;
    if ((!(match_40))) goto next_124;
    struct TokenKind_IntTuple2 call_52 = go_11(text_7, (i_15 + 1));
    match_39 = call_52;
    goto end_match_120;
next_124:;
    if (match_40) goto next_125;
    int match_41;
    if ((i_15 != text_7.len)) goto next_127;
    match_41 = 1;
    goto end_match_126;
next_127:;
    if ((i_15 == text_7.len)) goto next_128;
    match_41 = (text_7.str[i_15] == '\n');
    goto end_match_126;
next_128:;
    exit(1);
end_match_126:;
    milone_assert(match_41, 152, 6);
    int call_53 = 0;
    struct TokenKind_IntTuple2 tuple_17;
    tuple_17.t0 = (struct TokenKind_){.tag = Error_};
    tuple_17.t1 = i_15;
    match_39 = tuple_17;
    goto end_match_120;
next_125:;
    exit(1);
end_match_120:;
    match_37 = match_39;
    goto end_match_114;
next_119:;
    exit(1);
end_match_114:;
    match_35 = match_37;
    goto end_match_108;
next_113:;
    exit(1);
end_match_108:;
    return match_35;
}

struct TokenKind_IntIntTuple3ListStringIntTuple3 scanCharLit_(struct TokenKind_IntIntTuple3ListStringIntTuple3 arg_8) {
    struct TokenKind_IntIntTuple3List* acc_9 = arg_8.t0;
    struct String text_7 = arg_8.t1;
    int i_14 = arg_8.t2;
    milone_assert((text_7.str[i_14] == '\''), 139, 2);
    int call_54 = 0;
    struct TokenKind_IntTuple2 call_55 = go_11(text_7, (i_14 + 1));
    struct TokenKind_ kind_1 = call_55.t0;
    int endIndex_5 = call_55.t1;
    struct TokenKind_IntIntTuple3 tuple_19;
    tuple_19.t0 = kind_1;
    tuple_19.t1 = i_14;
    tuple_19.t2 = endIndex_5;
    struct TokenKind_IntIntTuple3List* list_8 = (struct TokenKind_IntIntTuple3List*)malloc(sizeof(struct TokenKind_IntIntTuple3List));
    list_8->head = tuple_19;
    list_8->tail = acc_9;
    struct TokenKind_IntIntTuple3ListStringIntTuple3 tuple_18;
    tuple_18.t0 = list_8;
    tuple_18.t1 = text_7;
    tuple_18.t2 = endIndex_5;
    return tuple_18;
}

struct TokenKind_IntTuple2 go_12(struct String text_8, int i_17) {
    struct TokenKind_IntTuple2 match_42;
    int match_43;
    if (((i_17 + 1) >= text_8.len)) goto next_131;
    match_43 = (text_8.str[i_17] == '\\');
    goto end_match_130;
next_131:;
    if (((i_17 + 1) < text_8.len)) goto next_132;
    match_43 = 0;
    goto end_match_130;
next_132:;
    exit(1);
end_match_130:;
    if ((!(match_43))) goto next_133;
    struct TokenKind_IntTuple2 call_56 = go_12(text_8, (i_17 + 2));
    match_42 = call_56;
    goto end_match_129;
next_133:;
    if (match_43) goto next_134;
    struct TokenKind_IntTuple2 match_44;
    int match_45;
    if ((i_17 >= text_8.len)) goto next_137;
    match_45 = (text_8.str[i_17] == '"');
    goto end_match_136;
next_137:;
    if ((i_17 < text_8.len)) goto next_138;
    match_45 = 0;
    goto end_match_136;
next_138:;
    exit(1);
end_match_136:;
    if ((!(match_45))) goto next_139;
    struct TokenKind_IntTuple2 tuple_20;
    tuple_20.t0 = (struct TokenKind_){.tag = StrLit_};
    tuple_20.t1 = (i_17 + 1);
    match_44 = tuple_20;
    goto end_match_135;
next_139:;
    if (match_45) goto next_140;
    struct TokenKind_IntTuple2 match_46;
    int match_47;
    if ((i_17 >= text_8.len)) goto next_143;
    match_47 = (text_8.str[i_17] != '\n');
    goto end_match_142;
next_143:;
    if ((i_17 < text_8.len)) goto next_144;
    match_47 = 0;
    goto end_match_142;
next_144:;
    exit(1);
end_match_142:;
    if ((!(match_47))) goto next_145;
    struct TokenKind_IntTuple2 call_57 = go_12(text_8, (i_17 + 1));
    match_46 = call_57;
    goto end_match_141;
next_145:;
    if (match_47) goto next_146;
    int match_48;
    if ((i_17 != text_8.len)) goto next_148;
    match_48 = 1;
    goto end_match_147;
next_148:;
    if ((i_17 == text_8.len)) goto next_149;
    match_48 = (text_8.str[i_17] == '\n');
    goto end_match_147;
next_149:;
    exit(1);
end_match_147:;
    milone_assert(match_48, 171, 6);
    int call_58 = 0;
    struct TokenKind_IntTuple2 tuple_21;
    tuple_21.t0 = (struct TokenKind_){.tag = Error_};
    tuple_21.t1 = i_17;
    match_46 = tuple_21;
    goto end_match_141;
next_146:;
    exit(1);
end_match_141:;
    match_44 = match_46;
    goto end_match_135;
next_140:;
    exit(1);
end_match_135:;
    match_42 = match_44;
    goto end_match_129;
next_134:;
    exit(1);
end_match_129:;
    return match_42;
}

struct TokenKind_IntIntTuple3ListStringIntTuple3 scanStrLit_(struct TokenKind_IntIntTuple3ListStringIntTuple3 arg_9) {
    struct TokenKind_IntIntTuple3List* acc_10 = arg_9.t0;
    struct String text_8 = arg_9.t1;
    int i_16 = arg_9.t2;
    milone_assert((text_8.str[i_16] == '"'), 158, 2);
    int call_59 = 0;
    struct TokenKind_IntTuple2 call_60 = go_12(text_8, (i_16 + 1));
    struct TokenKind_ kind_2 = call_60.t0;
    int endIndex_6 = call_60.t1;
    struct TokenKind_IntIntTuple3 tuple_23;
    tuple_23.t0 = kind_2;
    tuple_23.t1 = i_16;
    tuple_23.t2 = endIndex_6;
    struct TokenKind_IntIntTuple3List* list_9 = (struct TokenKind_IntIntTuple3List*)malloc(sizeof(struct TokenKind_IntIntTuple3List));
    list_9->head = tuple_23;
    list_9->tail = acc_10;
    struct TokenKind_IntIntTuple3ListStringIntTuple3 tuple_22;
    tuple_22.t0 = list_9;
    tuple_22.t1 = text_8;
    tuple_22.t2 = endIndex_6;
    return tuple_22;
}

int follow_(int i_18, struct String text_10, struct String prefix_1) {
    int call_61 = strNthStartsWith_(i_18, prefix_1, text_10);
    return call_61;
}

struct StringTokenKind_IntIntTuple3ListTuple2 {
    struct String t0;
    struct TokenKind_IntIntTuple3List* t1;
};

struct StringTokenKind_IntIntTuple3ListTuple2 go_13(struct TokenKind_IntIntTuple3ListStringIntTuple3 arg_10) {
    struct TokenKind_IntIntTuple3List* acc_11 = arg_10.t0;
    struct String text_10 = arg_10.t1;
    int i_18 = arg_10.t2;
    struct TokenKind_IntIntTuple3ListStringIntTuple3 tuple_24;
    tuple_24.t0 = acc_11;
    tuple_24.t1 = text_10;
    tuple_24.t2 = i_18;
    struct TokenKind_IntIntTuple3ListStringIntTuple3 t_ = tuple_24;
    struct StringTokenKind_IntIntTuple3ListTuple2 match_49;
    if ((i_18 < text_10.len)) goto next_151;
    struct TokenKind_IntIntTuple3List* call_62 = listRev_3(acc_11);
    struct StringTokenKind_IntIntTuple3ListTuple2 tuple_25;
    tuple_25.t0 = text_10;
    tuple_25.t1 = call_62;
    match_49 = tuple_25;
    goto end_match_150;
next_151:;
    if ((i_18 >= text_10.len)) goto next_152;
    struct StringTokenKind_IntIntTuple3ListTuple2 match_50;
    int match_51;
    int call_63 = follow_(i_18, text_10, (struct String){.str = "//", .len = 2});
    if ((!(call_63))) goto next_155;
    match_51 = 1;
    goto end_match_154;
next_155:;
    if (call_63) goto next_156;
    int call_64 = follow_(i_18, text_10, (struct String){.str = "[<", .len = 2});
    match_51 = call_64;
    goto end_match_154;
next_156:;
    exit(1);
end_match_154:;
    if ((!(match_51))) goto next_157;
    struct TokenKind_IntIntTuple3ListStringIntTuple3 call_65 = scanLine_(t_);
    struct StringTokenKind_IntIntTuple3ListTuple2 call_66 = go_13(call_65);
    match_50 = call_66;
    goto end_match_153;
next_157:;
    if (match_51) goto next_158;
    struct StringTokenKind_IntIntTuple3ListTuple2 match_52;
    int call_67 = charIsSpace_(text_10.str[i_18]);
    if ((!(call_67))) goto next_160;
    struct TokenKind_IntIntTuple3ListStringIntTuple3 call_68 = scanSpace_(t_);
    struct StringTokenKind_IntIntTuple3ListTuple2 call_69 = go_13(call_68);
    match_52 = call_69;
    goto end_match_159;
next_160:;
    if (call_67) goto next_161;
    struct StringTokenKind_IntIntTuple3ListTuple2 match_53;
    int call_70 = charIsOp_(text_10.str[i_18]);
    if ((!(call_70))) goto next_163;
    struct TokenKind_IntIntTuple3ListStringIntTuple3 call_71 = scanOp_(t_);
    struct StringTokenKind_IntIntTuple3ListTuple2 call_72 = go_13(call_71);
    match_53 = call_72;
    goto end_match_162;
next_163:;
    if (call_70) goto next_164;
    struct StringTokenKind_IntIntTuple3ListTuple2 match_54;
    int call_73 = charIsDigit_(text_10.str[i_18]);
    if ((!(call_73))) goto next_166;
    struct TokenKind_IntIntTuple3ListStringIntTuple3 call_74 = scanIntLit_(t_);
    struct StringTokenKind_IntIntTuple3ListTuple2 call_75 = go_13(call_74);
    match_54 = call_75;
    goto end_match_165;
next_166:;
    if (call_73) goto next_167;
    struct StringTokenKind_IntIntTuple3ListTuple2 match_55;
    int call_76 = charIsIdent_(text_10.str[i_18]);
    if ((!(call_76))) goto next_169;
    struct TokenKind_IntIntTuple3ListStringIntTuple3 call_77 = scanIdent_(t_);
    struct StringTokenKind_IntIntTuple3ListTuple2 call_78 = go_13(call_77);
    match_55 = call_78;
    goto end_match_168;
next_169:;
    if (call_76) goto next_170;
    struct StringTokenKind_IntIntTuple3ListTuple2 match_56;
    if ((text_10.str[i_18] != '\'')) goto next_172;
    struct TokenKind_IntIntTuple3ListStringIntTuple3 call_79 = scanCharLit_(t_);
    struct StringTokenKind_IntIntTuple3ListTuple2 call_80 = go_13(call_79);
    match_56 = call_80;
    goto end_match_171;
next_172:;
    if ((text_10.str[i_18] == '\'')) goto next_173;
    struct StringTokenKind_IntIntTuple3ListTuple2 match_57;
    if ((text_10.str[i_18] != '"')) goto next_175;
    struct TokenKind_IntIntTuple3ListStringIntTuple3 call_81 = scanStrLit_(t_);
    struct StringTokenKind_IntIntTuple3ListTuple2 call_82 = go_13(call_81);
    match_57 = call_82;
    goto end_match_174;
next_175:;
    if ((text_10.str[i_18] == '"')) goto next_176;
    struct StringTokenKind_IntIntTuple3ListTuple2 match_58;
    int call_83 = charIsPun_(text_10.str[i_18]);
    if ((!(call_83))) goto next_178;
    struct TokenKind_IntIntTuple3ListStringIntTuple3 call_84 = scanPun_(t_);
    struct StringTokenKind_IntIntTuple3ListTuple2 call_85 = go_13(call_84);
    match_58 = call_85;
    goto end_match_177;
next_178:;
    if (call_83) goto next_179;
    struct TokenKind_IntIntTuple3ListStringIntTuple3 call_86 = scanError_(t_);
    struct StringTokenKind_IntIntTuple3ListTuple2 call_87 = go_13(call_86);
    match_58 = call_87;
    goto end_match_177;
next_179:;
    exit(1);
end_match_177:;
    match_57 = match_58;
    goto end_match_174;
next_176:;
    exit(1);
end_match_174:;
    match_56 = match_57;
    goto end_match_171;
next_173:;
    exit(1);
end_match_171:;
    match_55 = match_56;
    goto end_match_168;
next_170:;
    exit(1);
end_match_168:;
    match_54 = match_55;
    goto end_match_165;
next_167:;
    exit(1);
end_match_165:;
    match_53 = match_54;
    goto end_match_162;
next_164:;
    exit(1);
end_match_162:;
    match_52 = match_53;
    goto end_match_159;
next_161:;
    exit(1);
end_match_159:;
    match_50 = match_52;
    goto end_match_153;
next_158:;
    exit(1);
end_match_153:;
    match_49 = match_50;
    goto end_match_150;
next_152:;
    exit(1);
end_match_150:;
    return match_49;
}

struct StringTokenKind_IntIntTuple3ListTuple2 scanRoot_(struct String text_9) {
    struct TokenKind_IntIntTuple3ListStringIntTuple3 tuple_26;
    tuple_26.t0 = NULL;
    tuple_26.t1 = text_9;
    tuple_26.t2 = 0;
    struct StringTokenKind_IntIntTuple3ListTuple2 call_88 = go_13(tuple_26);
    return call_88;
}

struct IntIntTuple2 go_14(int r_1, struct String text_11, int y_4, int x_8, int i_19) {
    struct IntIntTuple2 match_59;
    if ((i_19 != r_1)) goto next_181;
    struct IntIntTuple2 tuple_27;
    tuple_27.t0 = y_4;
    tuple_27.t1 = x_8;
    match_59 = tuple_27;
    goto end_match_180;
next_181:;
    if ((i_19 == r_1)) goto next_182;
    struct IntIntTuple2 match_60;
    if ((text_11.str[i_19] != '\n')) goto next_184;
    struct IntIntTuple2 call_89 = go_14(r_1, text_11, (y_4 + 1), 0, (i_19 + 1));
    match_60 = call_89;
    goto end_match_183;
next_184:;
    if ((text_11.str[i_19] == '\n')) goto next_185;
    struct IntIntTuple2 call_90 = go_14(r_1, text_11, y_4, (x_8 + 1), (i_19 + 1));
    match_60 = call_90;
    goto end_match_183;
next_185:;
    exit(1);
end_match_183:;
    match_59 = match_60;
    goto end_match_180;
next_182:;
    exit(1);
end_match_180:;
    return match_59;
}

struct IntIntTuple2 advanceTextPos_(struct IntIntTuple2 arg_11, struct String text_11, int l_1, int r_1) {
    int y_3 = arg_11.t0;
    int x_7 = arg_11.t1;
    struct IntIntTuple2 call_91 = go_14(r_1, text_11, y_3, x_7, l_1);
    return call_91;
}

struct Token_ tokenFromIdent_(struct String text_12, int l_2, int r_2) {
    struct Token_ match_61;
    struct String call_92 = strSlice_(l_2, r_2, text_12);
    if ((str_cmp(call_92, (struct String){.str = "true", .len = 4}) != 0)) goto next_187;
    int* payload_ = (int*)malloc(sizeof(int));
    (*(((int*)payload_))) = 1;
    struct Token_ variant_ = (struct Token_){.tag = Bool_, .Bool_ = payload_};
    match_61 = variant_;
    goto end_match_186;
next_187:;
    if ((str_cmp(call_92, (struct String){.str = "false", .len = 5}) != 0)) goto next_188;
    int* payload_1 = (int*)malloc(sizeof(int));
    (*(((int*)payload_1))) = 0;
    struct Token_ variant_1 = (struct Token_){.tag = Bool_, .Bool_ = payload_1};
    match_61 = variant_1;
    goto end_match_186;
next_188:;
    if ((str_cmp(call_92, (struct String){.str = "do", .len = 2}) != 0)) goto next_189;
    match_61 = (struct Token_){.tag = Do_};
    goto end_match_186;
next_189:;
    if ((str_cmp(call_92, (struct String){.str = "let", .len = 3}) != 0)) goto next_190;
    match_61 = (struct Token_){.tag = Let_};
    goto end_match_186;
next_190:;
    if ((str_cmp(call_92, (struct String){.str = "if", .len = 2}) != 0)) goto next_191;
    match_61 = (struct Token_){.tag = If_};
    goto end_match_186;
next_191:;
    if ((str_cmp(call_92, (struct String){.str = "then", .len = 4}) != 0)) goto next_192;
    match_61 = (struct Token_){.tag = Then_};
    goto end_match_186;
next_192:;
    if ((str_cmp(call_92, (struct String){.str = "else", .len = 4}) != 0)) goto next_193;
    match_61 = (struct Token_){.tag = Else_};
    goto end_match_186;
next_193:;
    if ((str_cmp(call_92, (struct String){.str = "match", .len = 5}) != 0)) goto next_194;
    match_61 = (struct Token_){.tag = Match_};
    goto end_match_186;
next_194:;
    if ((str_cmp(call_92, (struct String){.str = "with", .len = 4}) != 0)) goto next_195;
    match_61 = (struct Token_){.tag = With_};
    goto end_match_186;
next_195:;
    if ((str_cmp(call_92, (struct String){.str = "as", .len = 2}) != 0)) goto next_196;
    match_61 = (struct Token_){.tag = As_};
    goto end_match_186;
next_196:;
    if ((str_cmp(call_92, (struct String){.str = "when", .len = 4}) != 0)) goto next_197;
    match_61 = (struct Token_){.tag = When_};
    goto end_match_186;
next_197:;
    if ((str_cmp(call_92, (struct String){.str = "rec", .len = 3}) != 0)) goto next_198;
    match_61 = (struct Token_){.tag = Rec_};
    goto end_match_186;
next_198:;
    if ((str_cmp(call_92, (struct String){.str = "private", .len = 7}) != 0)) goto next_199;
    match_61 = (struct Token_){.tag = Private_};
    goto end_match_186;
next_199:;
    if ((str_cmp(call_92, (struct String){.str = "internal", .len = 8}) != 0)) goto next_200;
    match_61 = (struct Token_){.tag = Internal_};
    goto end_match_186;
next_200:;
    if ((str_cmp(call_92, (struct String){.str = "public", .len = 6}) != 0)) goto next_201;
    match_61 = (struct Token_){.tag = Public_};
    goto end_match_186;
next_201:;
    if ((str_cmp(call_92, (struct String){.str = "module", .len = 6}) != 0)) goto next_202;
    match_61 = (struct Token_){.tag = Module_};
    goto end_match_186;
next_202:;
    if ((str_cmp(call_92, (struct String){.str = "namespace", .len = 9}) != 0)) goto next_203;
    match_61 = (struct Token_){.tag = Namespace_};
    goto end_match_186;
next_203:;
    if ((str_cmp(call_92, (struct String){.str = "open", .len = 4}) != 0)) goto next_204;
    match_61 = (struct Token_){.tag = Open_};
    goto end_match_186;
next_204:;
    if ((str_cmp(call_92, (struct String){.str = "type", .len = 4}) != 0)) goto next_205;
    match_61 = (struct Token_){.tag = Type_};
    goto end_match_186;
next_205:;
    if ((str_cmp(call_92, (struct String){.str = "of", .len = 2}) != 0)) goto next_206;
    match_61 = (struct Token_){.tag = Of_};
    goto end_match_186;
next_206:;
    if ((str_cmp(call_92, (struct String){.str = "fun", .len = 3}) != 0)) goto next_207;
    match_61 = (struct Token_){.tag = Fun_};
    goto end_match_186;
next_207:;
    if ((str_cmp(call_92, (struct String){.str = "in", .len = 2}) != 0)) goto next_208;
    match_61 = (struct Token_){.tag = In_};
    goto end_match_186;
next_208:;
    struct String s_4 = call_92;
    struct String* payload_2 = (struct String*)malloc(sizeof(struct String));
    (*(((struct String*)payload_2))) = s_4;
    struct Token_ variant_2 = (struct Token_){.tag = Ident_1, .Ident_1 = payload_2};
    match_61 = variant_2;
    goto end_match_186;
next_209:;
end_match_186:;
    return match_61;
}

struct Token_ tokenFromOp_(struct String text_13, int l_3, int r_3) {
    struct Token_ match_62;
    struct String call_93 = strSlice_(l_3, r_3, text_13);
    if ((str_cmp(call_93, (struct String){.str = ":", .len = 1}) != 0)) goto next_211;
    match_62 = (struct Token_){.tag = Colon_};
    goto end_match_210;
next_211:;
    if ((str_cmp(call_93, (struct String){.str = ".", .len = 1}) != 0)) goto next_212;
    match_62 = (struct Token_){.tag = Dot_};
    goto end_match_210;
next_212:;
    if ((str_cmp(call_93, (struct String){.str = "|", .len = 1}) != 0)) goto next_213;
    match_62 = (struct Token_){.tag = Pipe_};
    goto end_match_210;
next_213:;
    if ((str_cmp(call_93, (struct String){.str = "->", .len = 2}) != 0)) goto next_214;
    match_62 = (struct Token_){.tag = Arrow_};
    goto end_match_210;
next_214:;
    struct String s_5 = call_93;
    struct String* payload_3 = (struct String*)malloc(sizeof(struct String));
    (*(((struct String*)payload_3))) = s_5;
    struct Token_ variant_3 = (struct Token_){.tag = Punct_, .Punct_ = payload_3};
    match_62 = variant_3;
    goto end_match_210;
next_215:;
end_match_210:;
    return match_62;
}

struct Token_ tokenFromPun_(struct String text_14, int l_4, int r_4) {
    milone_assert(((r_4 - l_4) == 1), 285, 2);
    int call_94 = 0;
    struct Token_ match_63;
    if ((text_14.str[l_4] != '(')) goto next_217;
    match_63 = (struct Token_){.tag = ParenL_};
    goto end_match_216;
next_217:;
    if ((text_14.str[l_4] != ')')) goto next_218;
    match_63 = (struct Token_){.tag = ParenR_};
    goto end_match_216;
next_218:;
    if ((text_14.str[l_4] != '[')) goto next_219;
    match_63 = (struct Token_){.tag = BracketL_};
    goto end_match_216;
next_219:;
    if ((text_14.str[l_4] != ']')) goto next_220;
    match_63 = (struct Token_){.tag = BracketR_};
    goto end_match_216;
next_220:;
    struct Token_ call_95 = failwith_1((struct String){.str = "NEVER! charIsPun is broken", .len = 26});
    match_63 = call_95;
    goto end_match_216;
next_221:;
end_match_216:;
    return match_63;
}

struct Token_ tokenFromIntLit_(struct String text_15, int l_5, int r_5) {
    struct String call_96 = strSlice_(l_5, r_5, text_15);
    int call_97 = str_to_int(call_96);
    int value_2 = call_97;
    int* payload_4 = (int*)malloc(sizeof(int));
    (*(((int*)payload_4))) = value_2;
    struct Token_ variant_4 = (struct Token_){.tag = Int_, .Int_ = payload_4};
    return variant_4;
}

struct Token_ tokenFromCharLit_(char charNull_, struct String text_16, int l_6, int r_6) {
    int match_64;
    int match_65;
    if ((r_6 < (l_6 + 2))) goto next_224;
    match_65 = (text_16.str[l_6] == '\'');
    goto end_match_223;
next_224:;
    if ((r_6 >= (l_6 + 2))) goto next_225;
    match_65 = 0;
    goto end_match_223;
next_225:;
    exit(1);
end_match_223:;
    if ((!(match_65))) goto next_226;
    match_64 = (text_16.str[(r_6 - 1)] == '\'');
    goto end_match_222;
next_226:;
    if (match_65) goto next_227;
    match_64 = 0;
    goto end_match_222;
next_227:;
    exit(1);
end_match_222:;
    milone_assert(match_64, 303, 2);
    int call_98 = 0;
    int i_20 = (l_6 + 1);
    char match_66;
    if ((text_16.str[i_20] != '\\')) goto next_229;
    char match_67;
    if ((text_16.str[(i_20 + 1)] != 'u')) goto next_232;
    match_67 = charNull_;
    goto end_match_231;
next_232:;
    if ((text_16.str[(i_20 + 1)] != 't')) goto next_233;
    match_67 = '\t';
    goto end_match_231;
next_233:;
    if ((text_16.str[(i_20 + 1)] != 'r')) goto next_234;
    match_67 = '\r';
    goto end_match_231;
next_234:;
    if ((text_16.str[(i_20 + 1)] != 'n')) goto next_235;
    match_67 = '\n';
    goto end_match_231;
next_235:;
    char c_7 = text_16.str[(i_20 + 1)];
    match_67 = c_7;
    goto end_match_231;
next_236:;
end_match_231:;
    match_66 = match_67;
    goto end_match_228;
next_229:;
    char c_8 = text_16.str[i_20];
    match_66 = c_8;
    goto end_match_228;
next_230:;
end_match_228:;
    char value_3 = match_66;
    char* payload_5 = (char*)malloc(sizeof(char));
    (*(((char*)payload_5))) = value_3;
    struct Token_ variant_5 = (struct Token_){.tag = Char_, .Char_ = payload_5};
    return variant_5;
}

int next_(int r_7, struct String text_17, int i_22) {
    int match_68;
    int match_69;
    if ((i_22 != (r_7 - 1))) goto next_239;
    match_69 = 1;
    goto end_match_238;
next_239:;
    if ((i_22 == (r_7 - 1))) goto next_240;
    match_69 = (text_17.str[i_22] == '\\');
    goto end_match_238;
next_240:;
    exit(1);
end_match_238:;
    if ((!(match_69))) goto next_241;
    match_68 = i_22;
    goto end_match_237;
next_241:;
    if (match_69) goto next_242;
    int call_99 = next_(r_7, text_17, (i_22 + 1));
    match_68 = call_99;
    goto end_match_237;
next_242:;
    exit(1);
end_match_237:;
    return match_68;
}

struct String go_15(int r_7, struct String text_17, struct StringList* acc_12, int i_21) {
    int call_100 = next_(r_7, text_17, i_21);
    int endIndex_7 = call_100;
    struct String call_101 = strSlice_(i_21, endIndex_7, text_17);
    struct StringList* list_10 = (struct StringList*)malloc(sizeof(struct StringList));
    list_10->head = call_101;
    list_10->tail = acc_12;
    struct StringList* acc_13 = list_10;
    int i_23 = endIndex_7;
    struct String match_70;
    if ((i_23 != (r_7 - 1))) goto next_244;
    struct StringList* call_102 = listRev_2(acc_13);
    struct String call_103 = strConcat_(call_102);
    match_70 = call_103;
    goto end_match_243;
next_244:;
    if ((i_23 == (r_7 - 1))) goto next_245;
    milone_assert((text_17.str[i_23] == '\\'), 346, 6);
    int call_104 = 0;
    struct String match_71;
    if ((text_17.str[(i_23 + 1)] != 'u')) goto next_247;
    struct StringList* list_11 = (struct StringList*)malloc(sizeof(struct StringList));
    list_11->head = (struct String){.str = "\0", .len = 1};
    list_11->tail = acc_13;
    struct String call_105 = go_15(r_7, text_17, list_11, (i_23 + 6));
    match_71 = call_105;
    goto end_match_246;
next_247:;
    if ((text_17.str[(i_23 + 1)] != 't')) goto next_248;
    struct StringList* list_12 = (struct StringList*)malloc(sizeof(struct StringList));
    list_12->head = (struct String){.str = "\t", .len = 1};
    list_12->tail = acc_13;
    struct String call_106 = go_15(r_7, text_17, list_12, (i_23 + 2));
    match_71 = call_106;
    goto end_match_246;
next_248:;
    if ((text_17.str[(i_23 + 1)] != 'r')) goto next_249;
    struct StringList* list_13 = (struct StringList*)malloc(sizeof(struct StringList));
    list_13->head = (struct String){.str = "\r", .len = 1};
    list_13->tail = acc_13;
    struct String call_107 = go_15(r_7, text_17, list_13, (i_23 + 2));
    match_71 = call_107;
    goto end_match_246;
next_249:;
    if ((text_17.str[(i_23 + 1)] != 'n')) goto next_250;
    struct StringList* list_14 = (struct StringList*)malloc(sizeof(struct StringList));
    list_14->head = (struct String){.str = "\n", .len = 1};
    list_14->tail = acc_13;
    struct String call_108 = go_15(r_7, text_17, list_14, (i_23 + 2));
    match_71 = call_108;
    goto end_match_246;
next_250:;
    struct String call_109 = strSlice_((i_23 + 1), (i_23 + 2), text_17);
    struct StringList* list_15 = (struct StringList*)malloc(sizeof(struct StringList));
    list_15->head = call_109;
    list_15->tail = acc_13;
    struct String call_110 = go_15(r_7, text_17, list_15, (i_23 + 2));
    match_71 = call_110;
    goto end_match_246;
next_251:;
end_match_246:;
    match_70 = match_71;
    goto end_match_243;
next_245:;
    exit(1);
end_match_243:;
    return match_70;
}

struct Token_ tokenFromStrLit_(struct String text_17, int l_7, int r_7) {
    int match_72;
    int match_73;
    if ((r_7 < (l_7 + 2))) goto next_254;
    match_73 = (text_17.str[l_7] == '"');
    goto end_match_253;
next_254:;
    if ((r_7 >= (l_7 + 2))) goto next_255;
    match_73 = 0;
    goto end_match_253;
next_255:;
    exit(1);
end_match_253:;
    if ((!(match_73))) goto next_256;
    match_72 = (text_17.str[(r_7 - 1)] == '"');
    goto end_match_252;
next_256:;
    if (match_73) goto next_257;
    match_72 = 0;
    goto end_match_252;
next_257:;
    exit(1);
end_match_252:;
    milone_assert(match_72, 327, 2);
    int call_111 = 0;
    struct String call_112 = go_15(r_7, text_17, NULL, (l_7 + 1));
    struct String value_4 = call_112;
    struct String* payload_6 = (struct String*)malloc(sizeof(struct String));
    (*(((struct String*)payload_6))) = value_4;
    struct Token_ variant_6 = (struct Token_){.tag = Str_, .Str_ = payload_6};
    return variant_6;
}

struct Token_ recognizeToken_(char charNull_, struct TokenKind_ kind_3, struct String text_18, int l_8, int r_8) {
    struct Token_ match_74;
    if ((kind_3.tag != Error_)) goto next_259;
    struct Token_ call_113 = failwith_1((struct String){.str = "Invalid char", .len = 12});
    match_74 = call_113;
    goto end_match_258;
next_259:;
    if ((kind_3.tag != Op_)) goto next_260;
    struct Token_ call_114 = tokenFromOp_(text_18, l_8, r_8);
    match_74 = call_114;
    goto end_match_258;
next_260:;
    if ((kind_3.tag != Pun_)) goto next_261;
    struct Token_ call_115 = tokenFromPun_(text_18, l_8, r_8);
    match_74 = call_115;
    goto end_match_258;
next_261:;
    if ((kind_3.tag != IntLit_)) goto next_262;
    struct Token_ call_116 = tokenFromIntLit_(text_18, l_8, r_8);
    match_74 = call_116;
    goto end_match_258;
next_262:;
    if ((kind_3.tag != CharLit_)) goto next_263;
    struct Token_ call_117 = tokenFromCharLit_(charNull_, text_18, l_8, r_8);
    match_74 = call_117;
    goto end_match_258;
next_263:;
    if ((kind_3.tag != StrLit_)) goto next_264;
    struct Token_ call_118 = tokenFromStrLit_(text_18, l_8, r_8);
    match_74 = call_118;
    goto end_match_258;
next_264:;
    if ((kind_3.tag != Ident_)) goto next_265;
    struct Token_ call_119 = tokenFromIdent_(text_18, l_8, r_8);
    match_74 = call_119;
    goto end_match_258;
next_265:;
end_match_258:;
    return match_74;
}

struct Token_IntIntTuple2Tuple2List* go_16(struct String text_19, char charNull_, struct Token_IntIntTuple2Tuple2List* acc_14, int y_5, int x_9, int last_, struct TokenKind_IntIntTuple3List* tokens_1) {
    struct Token_IntIntTuple2Tuple2List* match_75;
    if ((!((!(tokens_1))))) goto next_267;
    struct Token_IntIntTuple2Tuple2List* call_120 = listRev_1(acc_14);
    match_75 = call_120;
    goto end_match_266;
next_267:;
    if ((!(tokens_1))) goto next_268;
    struct TokenKind_ kind_4 = tokens_1->head.t0;
    int l_9 = tokens_1->head.t1;
    int r_9 = tokens_1->head.t2;
    struct TokenKind_IntIntTuple3List* tokens_2 = tokens_1->tail;
    struct IntIntTuple2 tuple_28;
    tuple_28.t0 = y_5;
    tuple_28.t1 = x_9;
    struct IntIntTuple2 call_121 = advanceTextPos_(tuple_28, text_19, last_, l_9);
    int y_6 = call_121.t0;
    int x_10 = call_121.t1;
    struct Token_ call_122 = recognizeToken_(charNull_, kind_4, text_19, l_9, r_9);
    struct Token_ token_2 = call_122;
    struct IntIntTuple2 tuple_30;
    tuple_30.t0 = y_6;
    tuple_30.t1 = x_10;
    struct Token_IntIntTuple2Tuple2 tuple_29;
    tuple_29.t0 = token_2;
    tuple_29.t1 = tuple_30;
    struct Token_IntIntTuple2Tuple2List* list_16 = (struct Token_IntIntTuple2Tuple2List*)malloc(sizeof(struct Token_IntIntTuple2Tuple2List));
    list_16->head = tuple_29;
    list_16->tail = acc_14;
    struct Token_IntIntTuple2Tuple2List* acc_15 = list_16;
    struct IntIntTuple2 tuple_31;
    tuple_31.t0 = y_6;
    tuple_31.t1 = x_10;
    struct IntIntTuple2 call_123 = advanceTextPos_(tuple_31, text_19, l_9, r_9);
    int y_7 = call_123.t0;
    int x_11 = call_123.t1;
    struct Token_IntIntTuple2Tuple2List* call_124 = go_16(text_19, charNull_, acc_15, y_7, x_11, r_9, tokens_2);
    match_75 = call_124;
    goto end_match_266;
next_268:;
    exit(1);
end_match_266:;
    return match_75;
}

struct Token_IntIntTuple2Tuple2List* recognizeTokens_(char charNull_, struct StringTokenKind_IntIntTuple3ListTuple2 arg_12) {
    struct String text_19 = arg_12.t0;
    struct TokenKind_IntIntTuple3List* tokens_ = arg_12.t1;
    struct Token_IntIntTuple2Tuple2List* call_125 = go_16(text_19, charNull_, NULL, 0, 0, 0, tokens_);
    return call_125;
}

struct Token_IntIntTuple2Tuple2List* tokenize_(char charNull_, struct String text_20) {
    struct StringTokenKind_IntIntTuple3ListTuple2 call_126 = scanRoot_(text_20);
    struct Token_IntIntTuple2Tuple2List* call_127 = recognizeTokens_(charNull_, call_126);
    return call_127;
}

struct String fileReadAllText_(struct String fileName_) {
    struct String call_128 = file_read_all_text(fileName_);
    return call_128;
}

struct String tokenKindToString_(struct TokenKind_ kind_) {
    struct String match_76;
    if ((kind_.tag != Error_)) goto next_270;
    match_76 = (struct String){.str = "Error", .len = 5};
    goto end_match_269;
next_270:;
    if ((kind_.tag != Ident_)) goto next_271;
    match_76 = (struct String){.str = "Ident", .len = 5};
    goto end_match_269;
next_271:;
    if ((kind_.tag != IntLit_)) goto next_272;
    match_76 = (struct String){.str = "IntLit", .len = 6};
    goto end_match_269;
next_272:;
    if ((kind_.tag != CharLit_)) goto next_273;
    match_76 = (struct String){.str = "CharLit", .len = 7};
    goto end_match_269;
next_273:;
    if ((kind_.tag != StrLit_)) goto next_274;
    match_76 = (struct String){.str = "StrLit", .len = 6};
    goto end_match_269;
next_274:;
    if ((kind_.tag != Op_)) goto next_275;
    match_76 = (struct String){.str = "Op", .len = 2};
    goto end_match_269;
next_275:;
    if ((kind_.tag != Pun_)) goto next_276;
    match_76 = (struct String){.str = "Pun", .len = 3};
    goto end_match_269;
next_276:;
end_match_269:;
    return match_76;
}

struct String tokenToString_(struct Token_ token_) {
    struct String match_77;
    if ((token_.tag != Bool_)) goto next_278;
    if ((!((*(token_.Bool_))))) goto next_278;
    match_77 = (struct String){.str = "true", .len = 4};
    goto end_match_277;
next_278:;
    if ((token_.tag != Bool_)) goto next_279;
    if ((*(token_.Bool_))) goto next_279;
    match_77 = (struct String){.str = "false", .len = 5};
    goto end_match_277;
next_279:;
    if ((token_.tag != Int_)) goto next_280;
    int value_ = (*(token_.Int_));
    struct String call_129 = str_of_int(value_);
    match_77 = call_129;
    goto end_match_277;
next_280:;
    if ((token_.tag != Char_)) goto next_281;
    match_77 = (struct String){.str = "'?'", .len = 3};
    goto end_match_277;
next_281:;
    if ((token_.tag != Str_)) goto next_282;
    match_77 = (struct String){.str = "\"..\"", .len = 4};
    goto end_match_277;
next_282:;
    if ((token_.tag != Ident_1)) goto next_283;
    struct String ident_ = (*(token_.Ident_1));
    match_77 = ident_;
    goto end_match_277;
next_283:;
    if ((token_.tag != Do_)) goto next_284;
    match_77 = (struct String){.str = "do", .len = 2};
    goto end_match_277;
next_284:;
    if ((token_.tag != Let_)) goto next_285;
    match_77 = (struct String){.str = "let", .len = 3};
    goto end_match_277;
next_285:;
    if ((token_.tag != Rec_)) goto next_286;
    match_77 = (struct String){.str = "rec", .len = 3};
    goto end_match_277;
next_286:;
    if ((token_.tag != If_)) goto next_287;
    match_77 = (struct String){.str = "if", .len = 2};
    goto end_match_277;
next_287:;
    if ((token_.tag != Then_)) goto next_288;
    match_77 = (struct String){.str = "then", .len = 4};
    goto end_match_277;
next_288:;
    if ((token_.tag != Else_)) goto next_289;
    match_77 = (struct String){.str = "else", .len = 4};
    goto end_match_277;
next_289:;
    if ((token_.tag != Match_)) goto next_290;
    match_77 = (struct String){.str = "match", .len = 5};
    goto end_match_277;
next_290:;
    if ((token_.tag != With_)) goto next_291;
    match_77 = (struct String){.str = "with", .len = 4};
    goto end_match_277;
next_291:;
    if ((token_.tag != As_)) goto next_292;
    match_77 = (struct String){.str = "as", .len = 2};
    goto end_match_277;
next_292:;
    if ((token_.tag != When_)) goto next_293;
    match_77 = (struct String){.str = "when", .len = 4};
    goto end_match_277;
next_293:;
    if ((token_.tag != ParenL_)) goto next_294;
    match_77 = (struct String){.str = "(", .len = 1};
    goto end_match_277;
next_294:;
    if ((token_.tag != ParenR_)) goto next_295;
    match_77 = (struct String){.str = ")", .len = 1};
    goto end_match_277;
next_295:;
    if ((token_.tag != BracketL_)) goto next_296;
    match_77 = (struct String){.str = "[", .len = 1};
    goto end_match_277;
next_296:;
    if ((token_.tag != BracketR_)) goto next_297;
    match_77 = (struct String){.str = "]", .len = 1};
    goto end_match_277;
next_297:;
    if ((token_.tag != Colon_)) goto next_298;
    match_77 = (struct String){.str = ":", .len = 1};
    goto end_match_277;
next_298:;
    if ((token_.tag != Dot_)) goto next_299;
    match_77 = (struct String){.str = ".", .len = 1};
    goto end_match_277;
next_299:;
    if ((token_.tag != Range_)) goto next_300;
    match_77 = (struct String){.str = "..", .len = 2};
    goto end_match_277;
next_300:;
    if ((token_.tag != Pipe_)) goto next_301;
    match_77 = (struct String){.str = "|", .len = 1};
    goto end_match_277;
next_301:;
    if ((token_.tag != Arrow_)) goto next_302;
    match_77 = (struct String){.str = "->", .len = 2};
    goto end_match_277;
next_302:;
    if ((token_.tag != Punct_)) goto next_303;
    struct String value_1 = (*(token_.Punct_));
    match_77 = value_1;
    goto end_match_277;
next_303:;
    if ((token_.tag != Private_)) goto next_304;
    match_77 = (struct String){.str = "private", .len = 7};
    goto end_match_277;
next_304:;
    if ((token_.tag != Internal_)) goto next_305;
    match_77 = (struct String){.str = "internal", .len = 8};
    goto end_match_277;
next_305:;
    if ((token_.tag != Public_)) goto next_306;
    match_77 = (struct String){.str = "public", .len = 6};
    goto end_match_277;
next_306:;
    if ((token_.tag != Module_)) goto next_307;
    match_77 = (struct String){.str = "module", .len = 6};
    goto end_match_277;
next_307:;
    if ((token_.tag != Namespace_)) goto next_308;
    match_77 = (struct String){.str = "namespace", .len = 9};
    goto end_match_277;
next_308:;
    if ((token_.tag != Open_)) goto next_309;
    match_77 = (struct String){.str = "open", .len = 4};
    goto end_match_277;
next_309:;
    if ((token_.tag != Type_)) goto next_310;
    match_77 = (struct String){.str = "type", .len = 4};
    goto end_match_277;
next_310:;
    if ((token_.tag != Of_)) goto next_311;
    match_77 = (struct String){.str = "of", .len = 2};
    goto end_match_277;
next_311:;
    if ((token_.tag != Fun_)) goto next_312;
    match_77 = (struct String){.str = "fun", .len = 3};
    goto end_match_277;
next_312:;
    if ((token_.tag != In_)) goto next_313;
    match_77 = (struct String){.str = "in", .len = 2};
    goto end_match_277;
next_313:;
end_match_277:;
    return match_77;
}

struct Token_IntIntTuple2Tuple2UnitFun1 {
    int(*fun)(void*, struct Token_IntIntTuple2Tuple2);
    void* env;
};

int listIter_1(struct Token_IntIntTuple2Tuple2UnitFun1 f_, struct Token_IntIntTuple2Tuple2List* xs_) {
    int match_78;
    if ((!((!(xs_))))) goto next_315;
    match_78 = 0;
    goto end_match_314;
next_315:;
    if ((!(xs_))) goto next_316;
    struct Token_IntIntTuple2Tuple2 x_ = xs_->head;
    struct Token_IntIntTuple2Tuple2List* xs_1 = xs_->tail;
    int app_ = f_.fun(f_.env, x_);
    int call_130 = listIter_1(f_, xs_1);
    match_78 = 0;
    goto end_match_314;
next_316:;
    exit(1);
end_match_314:;
    return 0;
}

int fun_(struct Token_IntIntTuple2Tuple2 arg_13) {
    struct Token_ token_1 = arg_13.t0;
    int y_ = arg_13.t1.t0;
    int x_1 = arg_13.t1.t1;
    struct String call_131 = tokenToString_(token_1);
    printf("%s (%d, %d)\n", call_131.str, y_, x_1);
    int call_132 = 0;
    return 0;
}

int fun_1(void* env_, struct Token_IntIntTuple2Tuple2 arg_) {
    int call_133 = fun_(arg_);
    return 0;
}

int main() {
    char call_134 = ((char)0);
    char charNull_ = call_134;
    struct String call_135 = fileReadAllText_((struct String){.str = "MiloneLang/Lexing.fs", .len = 20});
    struct String source_ = call_135;
    void* box_ = (void*)malloc(sizeof(int));
    (*(((int*)box_))) = 0;
    void* env_1 = box_;
    struct Token_IntIntTuple2Tuple2UnitFun1 fun_2 = (struct Token_IntIntTuple2Tuple2UnitFun1){.fun = fun_1, .env = env_1};
    struct Token_IntIntTuple2Tuple2List* call_136 = tokenize_(charNull_, source_);
    int call_137 = listIter_1(fun_2, call_136);
    return 0;
}
