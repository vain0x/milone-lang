#include "milone.h"

struct StringList;

struct StringList;

struct Token_List;

struct Token_;

struct Token_List;

struct CharBoolFun1;

struct StringIntTuple2;

struct CharTuple1;

struct Token_ListIntTuple2;

struct IntToken_ListTuple2;

bool charEqual_(char l_, char r_);

bool go_(char c_, struct String s_, int i_);

bool strContains_(char c_, struct String s_);

bool go_1(struct String prefix_, struct String s_1, int i_1);

bool strStartsWith_(struct String prefix_, struct String s_1);

struct String go_2(struct StringList const* xs_1);

struct String strConcat_(struct StringList const* xs_);

struct StringList const* go_3(struct StringList const* acc_, struct StringList const* xs_4);

struct StringList const* strListRev_(struct StringList const* xs_3);

struct Token_List const* go_4(struct Token_List const* acc_1, struct Token_List const* xs_7);

struct Token_List const* tokenListRev_(struct Token_List const* xs_6);

bool isDigit_(char c_1);

int go_5(struct CharBoolFun1 pred_, struct String source_, int r_1);

int takeWhile_(struct CharBoolFun1 pred_, struct StringIntTuple2 arg_16);

bool fun_(void const* env_, char arg_);

struct Token_ListIntTuple2 readSpace_(struct String source_1, struct Token_ListIntTuple2 arg_17);

struct Token_ListIntTuple2 readEol_(struct String source_2, struct Token_ListIntTuple2 arg_18);

bool fun_1(void const* env_1, char arg_2);

struct Token_ListIntTuple2 readInt_(struct String source_3, struct Token_ListIntTuple2 arg_19);

char at_(struct String source_4, int i_6);

struct Token_List const* go_6(struct String source_4, struct Token_ListIntTuple2 arg_20);

struct Token_List const* tokenize_(struct String source_4);

char tokenListPrint_(struct Token_List const* tokens_);

struct IntToken_ListTuple2 evalTerm_(struct Token_List const* tokens_4);

struct IntToken_ListTuple2 go_7(int acc_6, struct Token_List const* tokens_9);

struct IntToken_ListTuple2 evalMul_(struct Token_List const* tokens_8);

struct IntToken_ListTuple2 go_8(int acc_7, struct Token_List const* tokens_14);

struct IntToken_ListTuple2 evalAdd_(struct Token_List const* tokens_13);

struct IntToken_ListTuple2 evalExpr_(struct Token_List const* tokens_3);

int eval_(struct String str_);

int milone_main();

struct StringList {
    struct String head;
    struct StringList const* tail;
};

enum Token_Discriminant {
    TkInt_,
    TkOp_,
};

struct Token_ {
    enum Token_Discriminant discriminant;
    union {
        int TkInt_;
        char TkOp_;
    };
};

struct Token_List {
    struct Token_ head;
    struct Token_List const* tail;
};

struct CharBoolFun1 {
    bool(*fun)(void const*, char);
    void const* env;
};

struct StringIntTuple2 {
    struct String t0;
    int t1;
};

struct CharTuple1 {
    char t0;
};

struct Token_ListIntTuple2 {
    struct Token_List const* t0;
    int t1;
};

struct IntToken_ListTuple2 {
    int t0;
    struct Token_List const* t1;
};

bool charEqual_(char l_, char r_) {
    return (l_ == r_);
}

bool go_(char c_, struct String s_, int i_) {
tailrec_1:;
    bool if_;
    if ((i_ < s_.len)) {
        goto then_3;
    } else {
        goto else_7;
    }
then_3:;
    bool if_1;
    if ((s_.str[i_] == c_)) {
        goto then_5;
    } else {
        goto else_6;
    }
then_5:;
    if_1 = true;
    goto if_next_4;
else_6:;
    char arg_3 = c_;
    struct String arg_4 = s_;
    int arg_5 = (i_ + 1);
    c_ = arg_3;
    s_ = arg_4;
    i_ = arg_5;
    goto tailrec_1;
if_next_4:;
    if_ = if_1;
    goto if_next_2;
else_7:;
    if_ = false;
    goto if_next_2;
if_next_2:;
    return if_;
}

bool strContains_(char c_, struct String s_) {
    bool call_ = go_(c_, s_, 0);
    return call_;
}

bool go_1(struct String prefix_, struct String s_1, int i_1) {
tailrec_8:;
    bool if_2;
    if ((i_1 >= prefix_.len)) {
        goto then_10;
    } else {
        goto else_11;
    }
then_10:;
    if_2 = true;
    goto if_next_9;
else_11:;
    bool if_3;
    if ((s_1.str[i_1] == prefix_.str[i_1])) {
        goto then_13;
    } else {
        goto else_14;
    }
then_13:;
    struct String arg_6 = prefix_;
    struct String arg_7 = s_1;
    int arg_8 = (i_1 + 1);
    prefix_ = arg_6;
    s_1 = arg_7;
    i_1 = arg_8;
    goto tailrec_8;
else_14:;
    if_3 = false;
    goto if_next_12;
if_next_12:;
    if_2 = if_3;
    goto if_next_9;
if_next_9:;
    return if_2;
}

bool strStartsWith_(struct String prefix_, struct String s_1) {
    bool if_4;
    if ((s_1.len >= prefix_.len)) {
        goto then_16;
    } else {
        goto else_17;
    }
then_16:;
    bool call_1 = go_1(prefix_, s_1, 0);
    if_4 = call_1;
    goto if_next_15;
else_17:;
    if_4 = false;
    goto if_next_15;
if_next_15:;
    return if_4;
}

struct String go_2(struct StringList const* xs_1) {
    struct String match_;
    if ((!((!(xs_1))))) goto next_19;
    match_ = (struct String){.str = "", .len = 0};
    goto end_match_18;
next_19:;
    if ((!(xs_1))) goto next_20;
    struct String x_ = xs_1->head;
    struct StringList const* xs_2 = xs_1->tail;
    struct String call_2 = go_2(xs_2);
    match_ = str_add(x_, call_2);
    goto end_match_18;
next_20:;
    exit(1);
end_match_18:;
    return match_;
}

struct String strConcat_(struct StringList const* xs_) {
    struct String call_3 = go_2(xs_);
    return call_3;
}

struct StringList const* go_3(struct StringList const* acc_, struct StringList const* xs_4) {
tailrec_21:;
    struct StringList const* match_1;
    if ((!((!(xs_4))))) goto next_23;
    match_1 = acc_;
    goto end_match_22;
next_23:;
    if ((!(xs_4))) goto next_24;
    struct String x_1 = xs_4->head;
    struct StringList const* xs_5 = xs_4->tail;
    struct StringList const* list_ = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_))) = (struct StringList){.head = x_1, .tail = acc_};
    struct StringList const* arg_9 = list_;
    struct StringList const* arg_10 = xs_5;
    acc_ = arg_9;
    xs_4 = arg_10;
    goto tailrec_21;
next_24:;
    exit(1);
end_match_22:;
    return match_1;
}

struct StringList const* strListRev_(struct StringList const* xs_3) {
    struct StringList const* call_4 = go_3(NULL, xs_3);
    return call_4;
}

struct Token_List const* go_4(struct Token_List const* acc_1, struct Token_List const* xs_7) {
tailrec_25:;
    struct Token_List const* match_2;
    if ((!((!(xs_7))))) goto next_27;
    match_2 = acc_1;
    goto end_match_26;
next_27:;
    if ((!(xs_7))) goto next_28;
    struct Token_ x_2 = xs_7->head;
    struct Token_List const* xs_8 = xs_7->tail;
    struct Token_List const* list_1 = milone_mem_alloc(1, sizeof(struct Token_List));
    (*(((struct Token_List*)list_1))) = (struct Token_List){.head = x_2, .tail = acc_1};
    struct Token_List const* arg_11 = list_1;
    struct Token_List const* arg_12 = xs_8;
    acc_1 = arg_11;
    xs_7 = arg_12;
    goto tailrec_25;
next_28:;
    exit(1);
end_match_26:;
    return match_2;
}

struct Token_List const* tokenListRev_(struct Token_List const* xs_6) {
    struct Token_List const* call_5 = go_4(NULL, xs_6);
    return call_5;
}

bool isDigit_(char c_1) {
    bool if_5;
    if ((c_1 >= '0')) {
        goto then_30;
    } else {
        goto else_31;
    }
then_30:;
    if_5 = ('9' >= c_1);
    goto if_next_29;
else_31:;
    if_5 = false;
    goto if_next_29;
if_next_29:;
    return if_5;
}

int go_5(struct CharBoolFun1 pred_, struct String source_, int r_1) {
tailrec_32:;
    bool if_6;
    if ((r_1 < source_.len)) {
        goto then_34;
    } else {
        goto else_35;
    }
then_34:;
    bool app_ = pred_.fun(pred_.env, source_.str[r_1]);
    if_6 = app_;
    goto if_next_33;
else_35:;
    if_6 = false;
    goto if_next_33;
if_next_33:;
    int if_7;
    if (if_6) {
        goto then_37;
    } else {
        goto else_38;
    }
then_37:;
    struct CharBoolFun1 arg_13 = pred_;
    struct String arg_14 = source_;
    int arg_15 = (r_1 + 1);
    pred_ = arg_13;
    source_ = arg_14;
    r_1 = arg_15;
    goto tailrec_32;
else_38:;
    if_7 = r_1;
    goto if_next_36;
if_next_36:;
    return if_7;
}

int takeWhile_(struct CharBoolFun1 pred_, struct StringIntTuple2 arg_16) {
    struct String source_ = arg_16.t0;
    int i_2 = arg_16.t1;
    int call_6 = go_5(pred_, source_, i_2);
    return call_6;
}

bool fun_(void const* env_, char arg_) {
    char arg_1 = (*(((struct CharTuple1 const*)env_))).t0;
    bool call_7 = charEqual_(arg_1, arg_);
    return call_7;
}

struct Token_ListIntTuple2 readSpace_(struct String source_1, struct Token_ListIntTuple2 arg_17) {
    struct Token_List const* acc_2 = arg_17.t0;
    int i_3 = arg_17.t1;
    milone_assert((source_1.str[i_3] == ' '), 59, 2);
    struct CharTuple1 tuple_ = (struct CharTuple1){.t0 = ' '};
    void const* box_ = milone_mem_alloc(1, sizeof(struct CharTuple1));
    (*(((struct CharTuple1*)box_))) = tuple_;
    struct CharBoolFun1 fun_2 = (struct CharBoolFun1){.fun = fun_, .env = box_};
    struct StringIntTuple2 tuple_1 = (struct StringIntTuple2){.t0 = source_1, .t1 = (i_3 + 1)};
    int call_8 = takeWhile_(fun_2, tuple_1);
    int r_2 = call_8;
    struct Token_ListIntTuple2 tuple_2 = (struct Token_ListIntTuple2){.t0 = acc_2, .t1 = r_2};
    return tuple_2;
}

struct Token_ListIntTuple2 readEol_(struct String source_2, struct Token_ListIntTuple2 arg_18) {
    struct Token_List const* acc_3 = arg_18.t0;
    int i_4 = arg_18.t1;
    bool if_8;
    if ((source_2.str[i_4] == '\r')) {
        goto then_40;
    } else {
        goto else_41;
    }
then_40:;
    if_8 = true;
    goto if_next_39;
else_41:;
    if_8 = (source_2.str[i_4] == '\n');
    goto if_next_39;
if_next_39:;
    milone_assert(if_8, 67, 2);
    bool if_9;
    if (((i_4 + 1) < source_2.len)) {
        goto then_43;
    } else {
        goto else_44;
    }
then_43:;
    if_9 = (source_2.str[i_4] == '\r');
    goto if_next_42;
else_44:;
    if_9 = false;
    goto if_next_42;
if_next_42:;
    bool if_10;
    if (if_9) {
        goto then_46;
    } else {
        goto else_47;
    }
then_46:;
    if_10 = (source_2.str[(i_4 + 1)] == '\n');
    goto if_next_45;
else_47:;
    if_10 = false;
    goto if_next_45;
if_next_45:;
    int if_11;
    if (if_10) {
        goto then_49;
    } else {
        goto else_50;
    }
then_49:;
    if_11 = (i_4 + 2);
    goto if_next_48;
else_50:;
    if_11 = (i_4 + 1);
    goto if_next_48;
if_next_48:;
    int r_3 = if_11;
    struct Token_ListIntTuple2 tuple_3 = (struct Token_ListIntTuple2){.t0 = acc_3, .t1 = r_3};
    return tuple_3;
}

bool fun_1(void const* env_1, char arg_2) {
    bool call_9 = isDigit_(arg_2);
    return call_9;
}

struct Token_ListIntTuple2 readInt_(struct String source_3, struct Token_ListIntTuple2 arg_19) {
    struct Token_List const* acc_4 = arg_19.t0;
    int i_5 = arg_19.t1;
    bool call_10 = isDigit_(source_3.str[i_5]);
    milone_assert(call_10, 80, 2);
    struct CharBoolFun1 fun_3 = (struct CharBoolFun1){.fun = fun_1, .env = NULL};
    struct StringIntTuple2 tuple_4 = (struct StringIntTuple2){.t0 = source_3, .t1 = i_5};
    int call_11 = takeWhile_(fun_3, tuple_4);
    int r_4 = call_11;
    struct String slice_ = str_get_slice(i_5, (r_4 - 1), source_3);
    int call_12 = str_to_int(slice_);
    int n_ = call_12;
    struct Token_ variant_ = (struct Token_){.discriminant = TkInt_, .TkInt_ = n_};
    struct Token_List const* list_2 = milone_mem_alloc(1, sizeof(struct Token_List));
    (*(((struct Token_List*)list_2))) = (struct Token_List){.head = variant_, .tail = acc_4};
    struct Token_ListIntTuple2 tuple_5 = (struct Token_ListIntTuple2){.t0 = list_2, .t1 = r_4};
    return tuple_5;
}

char at_(struct String source_4, int i_6) {
    char if_12;
    if ((i_6 < source_4.len)) {
        goto then_52;
    } else {
        goto else_53;
    }
then_52:;
    if_12 = source_4.str[i_6];
    goto if_next_51;
else_53:;
    if_12 = '\0';
    goto if_next_51;
if_next_51:;
    return if_12;
}

struct Token_List const* go_6(struct String source_4, struct Token_ListIntTuple2 arg_20) {
tailrec_54:;
    struct Token_List const* acc_5 = arg_20.t0;
    int i_7 = arg_20.t1;
    struct Token_List const* if_13;
    if ((i_7 >= source_4.len)) {
        goto then_56;
    } else {
        goto else_57;
    }
then_56:;
    struct Token_List const* call_13 = tokenListRev_(acc_5);
    if_13 = call_13;
    goto if_next_55;
else_57:;
    struct Token_List const* match_3;
    if ((source_4.str[i_7] != ' ')) goto next_59;
    struct String arg_21 = source_4;
    struct Token_ListIntTuple2 tuple_6 = (struct Token_ListIntTuple2){.t0 = acc_5, .t1 = i_7};
    struct Token_ListIntTuple2 call_14 = readSpace_(source_4, tuple_6);
    struct Token_ListIntTuple2 arg_22 = call_14;
    source_4 = arg_21;
    arg_20 = arg_22;
    goto tailrec_54;
next_59:;
    if ((source_4.str[i_7] != '\r')) goto next_60;
    struct String arg_23 = source_4;
    struct Token_ListIntTuple2 tuple_7 = (struct Token_ListIntTuple2){.t0 = acc_5, .t1 = i_7};
    struct Token_ListIntTuple2 call_15 = readEol_(source_4, tuple_7);
    struct Token_ListIntTuple2 arg_24 = call_15;
    source_4 = arg_23;
    arg_20 = arg_24;
    goto tailrec_54;
next_60:;
    if ((source_4.str[i_7] != '\n')) goto next_61;
    struct String arg_25 = source_4;
    struct Token_ListIntTuple2 tuple_8 = (struct Token_ListIntTuple2){.t0 = acc_5, .t1 = i_7};
    struct Token_ListIntTuple2 call_16 = readEol_(source_4, tuple_8);
    struct Token_ListIntTuple2 arg_26 = call_16;
    source_4 = arg_25;
    arg_20 = arg_26;
    goto tailrec_54;
next_61:;
    char c_2 = source_4.str[i_7];
    bool call_17 = isDigit_(c_2);
    struct Token_List const* if_14;
    if (call_17) {
        goto then_64;
    } else {
        goto else_65;
    }
then_64:;
    struct String arg_27 = source_4;
    struct Token_ListIntTuple2 tuple_9 = (struct Token_ListIntTuple2){.t0 = acc_5, .t1 = i_7};
    struct Token_ListIntTuple2 call_18 = readInt_(source_4, tuple_9);
    struct Token_ListIntTuple2 arg_28 = call_18;
    source_4 = arg_27;
    arg_20 = arg_28;
    goto tailrec_54;
else_65:;
    struct String arg_29 = source_4;
    struct Token_ variant_1 = (struct Token_){.discriminant = TkOp_, .TkOp_ = c_2};
    struct Token_List const* list_3 = milone_mem_alloc(1, sizeof(struct Token_List));
    (*(((struct Token_List*)list_3))) = (struct Token_List){.head = variant_1, .tail = acc_5};
    struct Token_ListIntTuple2 tuple_10 = (struct Token_ListIntTuple2){.t0 = list_3, .t1 = (i_7 + 1)};
    struct Token_ListIntTuple2 arg_30 = tuple_10;
    source_4 = arg_29;
    arg_20 = arg_30;
    goto tailrec_54;
if_next_63:;
    match_3 = if_14;
    goto end_match_58;
next_62:;
end_match_58:;
    if_13 = match_3;
    goto if_next_55;
if_next_55:;
    return if_13;
}

struct Token_List const* tokenize_(struct String source_4) {
    struct Token_ListIntTuple2 tuple_11 = (struct Token_ListIntTuple2){.t0 = NULL, .t1 = 0};
    struct Token_List const* call_19 = go_6(source_4, tuple_11);
    return call_19;
}

char tokenListPrint_(struct Token_List const* tokens_) {
tailrec_66:;
    char match_4;
    if ((!((!(tokens_))))) goto next_68;
    match_4 = 0;
    goto end_match_67;
next_68:;
    if ((!(tokens_))) goto next_69;
    if ((tokens_->head.discriminant != TkInt_)) goto next_69;
    int n_1 = tokens_->head.TkInt_;
    struct Token_List const* tokens_1 = tokens_->tail;
    printf("int %d\n", n_1);
    struct Token_List const* arg_31 = tokens_1;
    tokens_ = arg_31;
    goto tailrec_66;
next_69:;
    if ((!(tokens_))) goto next_70;
    if ((tokens_->head.discriminant != TkOp_)) goto next_70;
    char c_3 = tokens_->head.TkOp_;
    struct Token_List const* tokens_2 = tokens_->tail;
    printf("op %c\n", c_3);
    struct Token_List const* arg_32 = tokens_2;
    tokens_ = arg_32;
    goto tailrec_66;
next_70:;
    exit(1);
end_match_67:;
    return 0;
}

struct IntToken_ListTuple2 evalTerm_(struct Token_List const* tokens_4) {
    struct IntToken_ListTuple2 match_5;
    if ((!(tokens_4))) goto next_72;
    if ((tokens_4->head.discriminant != TkInt_)) goto next_72;
    int n_2 = tokens_4->head.TkInt_;
    struct Token_List const* tokens_5 = tokens_4->tail;
    struct IntToken_ListTuple2 tuple_12 = (struct IntToken_ListTuple2){.t0 = n_2, .t1 = tokens_5};
    match_5 = tuple_12;
    goto end_match_71;
next_72:;
    if ((!(tokens_4))) goto next_73;
    if ((tokens_4->head.discriminant != TkOp_)) goto next_73;
    if ((tokens_4->head.TkOp_ != '(')) goto next_73;
    struct Token_List const* tokens_6 = tokens_4->tail;
    struct IntToken_ListTuple2 match_6;
    struct IntToken_ListTuple2 call_20 = evalExpr_(tokens_6);
    int value_ = call_20.t0;
    if ((!(call_20.t1))) goto next_76;
    if ((call_20.t1->head.discriminant != TkOp_)) goto next_76;
    if ((call_20.t1->head.TkOp_ != ')')) goto next_76;
    struct Token_List const* tokens_7 = call_20.t1->tail;
    struct IntToken_ListTuple2 tuple_13 = (struct IntToken_ListTuple2){.t0 = value_, .t1 = tokens_7};
    match_6 = tuple_13;
    goto end_match_75;
next_76:;
    printf("expected \')\'\n");
    exit(1);
next_77:;
end_match_75:;
    match_5 = match_6;
    goto end_match_71;
next_73:;
    printf("expected an int\n");
    exit(1);
next_74:;
end_match_71:;
    return match_5;
}

struct IntToken_ListTuple2 go_7(int acc_6, struct Token_List const* tokens_9) {
tailrec_78:;
    struct IntToken_ListTuple2 match_7;
    if ((!(tokens_9))) goto next_80;
    if ((tokens_9->head.discriminant != TkOp_)) goto next_80;
    if ((tokens_9->head.TkOp_ != '*')) goto next_80;
    struct Token_List const* tokens_10 = tokens_9->tail;
    struct IntToken_ListTuple2 call_21 = evalTerm_(tokens_10);
    int r_5 = call_21.t0;
    struct Token_List const* tokens_11 = call_21.t1;
    int arg_33 = (acc_6 * r_5);
    struct Token_List const* arg_34 = tokens_11;
    acc_6 = arg_33;
    tokens_9 = arg_34;
    goto tailrec_78;
next_80:;
    struct IntToken_ListTuple2 tuple_14 = (struct IntToken_ListTuple2){.t0 = acc_6, .t1 = tokens_9};
    match_7 = tuple_14;
    goto end_match_79;
next_81:;
end_match_79:;
    return match_7;
}

struct IntToken_ListTuple2 evalMul_(struct Token_List const* tokens_8) {
    struct IntToken_ListTuple2 call_22 = evalTerm_(tokens_8);
    int l_1 = call_22.t0;
    struct Token_List const* tokens_12 = call_22.t1;
    struct IntToken_ListTuple2 call_23 = go_7(l_1, tokens_12);
    return call_23;
}

struct IntToken_ListTuple2 go_8(int acc_7, struct Token_List const* tokens_14) {
tailrec_82:;
    struct IntToken_ListTuple2 match_8;
    if ((!(tokens_14))) goto next_84;
    if ((tokens_14->head.discriminant != TkOp_)) goto next_84;
    if ((tokens_14->head.TkOp_ != '+')) goto next_84;
    struct Token_List const* tokens_15 = tokens_14->tail;
    struct IntToken_ListTuple2 call_24 = evalMul_(tokens_15);
    int r_6 = call_24.t0;
    struct Token_List const* tokens_16 = call_24.t1;
    int arg_35 = (acc_7 + r_6);
    struct Token_List const* arg_36 = tokens_16;
    acc_7 = arg_35;
    tokens_14 = arg_36;
    goto tailrec_82;
next_84:;
    if ((!(tokens_14))) goto next_85;
    if ((tokens_14->head.discriminant != TkOp_)) goto next_85;
    if ((tokens_14->head.TkOp_ != '-')) goto next_85;
    struct Token_List const* tokens_17 = tokens_14->tail;
    struct IntToken_ListTuple2 call_25 = evalMul_(tokens_17);
    int r_7 = call_25.t0;
    struct Token_List const* tokens_18 = call_25.t1;
    int arg_37 = (acc_7 - r_7);
    struct Token_List const* arg_38 = tokens_18;
    acc_7 = arg_37;
    tokens_14 = arg_38;
    goto tailrec_82;
next_85:;
    struct IntToken_ListTuple2 tuple_15 = (struct IntToken_ListTuple2){.t0 = acc_7, .t1 = tokens_14};
    match_8 = tuple_15;
    goto end_match_83;
next_86:;
end_match_83:;
    return match_8;
}

struct IntToken_ListTuple2 evalAdd_(struct Token_List const* tokens_13) {
    struct IntToken_ListTuple2 call_26 = evalMul_(tokens_13);
    int l_2 = call_26.t0;
    struct Token_List const* tokens_19 = call_26.t1;
    struct IntToken_ListTuple2 call_27 = go_8(l_2, tokens_19);
    return call_27;
}

struct IntToken_ListTuple2 evalExpr_(struct Token_List const* tokens_3) {
    struct IntToken_ListTuple2 call_28 = evalAdd_(tokens_3);
    return call_28;
}

int eval_(struct String str_) {
    int match_9;
    struct Token_List const* call_29 = tokenize_(str_);
    struct IntToken_ListTuple2 call_30 = evalExpr_(call_29);
    int value_1 = call_30.t0;
    if ((!((!(call_30.t1))))) goto next_88;
    match_9 = value_1;
    goto end_match_87;
next_88:;
    struct Token_List const* tokens_20 = call_30.t1;
    printf("ERROR: couldn\'t parse tokens:\n");
    char call_31 = tokenListPrint_(tokens_20);
    exit(1);
next_89:;
end_match_87:;
    return match_9;
}

int milone_main() {
    bool call_32 = strContains_('+', (struct String){.str = "+-*/", .len = 4});
    milone_assert(call_32, 168, 2);
    bool call_33 = strStartsWith_((struct String){.str = "hell", .len = 4}, (struct String){.str = "hello", .len = 5});
    milone_assert(call_33, 169, 2);
    bool call_34 = strStartsWith_((struct String){.str = "heaven", .len = 6}, (struct String){.str = "hello", .len = 5});
    milone_assert((!(call_34)), 170, 2);
    struct StringList const* list_6 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_6))) = (struct StringList){.head = (struct String){.str = "b", .len = 1}, .tail = NULL};
    struct StringList const* list_5 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_5))) = (struct StringList){.head = (struct String){.str = ",", .len = 1}, .tail = list_6};
    struct StringList const* list_4 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_4))) = (struct StringList){.head = (struct String){.str = "a", .len = 1}, .tail = list_5};
    struct String call_35 = strConcat_(list_4);
    milone_assert((str_compare(call_35, (struct String){.str = "a,b", .len = 3}) == 0), 171, 2);
    struct StringList const* list_9 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_9))) = (struct StringList){.head = (struct String){.str = "b", .len = 1}, .tail = NULL};
    struct StringList const* list_8 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_8))) = (struct StringList){.head = (struct String){.str = ",", .len = 1}, .tail = list_9};
    struct StringList const* list_7 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_7))) = (struct StringList){.head = (struct String){.str = "a", .len = 1}, .tail = list_8};
    struct StringList const* call_36 = strListRev_(list_7);
    struct String call_37 = strConcat_(call_36);
    milone_assert((str_compare(call_37, (struct String){.str = "b,a", .len = 3}) == 0), 172, 2);
    struct String source_5 = (struct String){.str = "2 + 3\r\n    - 4", .len = 14};
    struct Token_List const* call_38 = tokenize_(source_5);
    char call_39 = tokenListPrint_(call_38);
    int call_40 = eval_(source_5);
    milone_assert((call_40 == ((2 + 3) - 4)), 177, 2);
    int call_41 = eval_((struct String){.str = "2 - 3 * 4 + 5", .len = 13});
    milone_assert((call_41 == ((2 - (3 * 4)) + 5)), 178, 2);
    int call_42 = eval_((struct String){.str = "(2 - 3) * 4 + (1 + (2 + 2))", .len = 27});
    milone_assert((call_42 == (((2 - 3) * 4) + (1 + (2 + 2)))), 179, 2);
    return 0;
}
