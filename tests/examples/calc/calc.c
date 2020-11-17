#include "milone.h"

int charEq_(char l_, char r_);

int go_(struct String s_, char c_, int i_);

int strContains_(char c_, struct String s_);

int go_1(struct String s_1, struct String prefix_, int i_1);

int strStartsWith_(struct String prefix_, struct String s_1);

struct StringList;

struct String go_2(struct StringList* xs_1);

struct String strConcat_(struct StringList* xs_);

struct StringList* go_3(struct StringList* acc_, struct StringList* xs_4);

struct StringList* strListRev_(struct StringList* xs_3);

enum Token_Tag;

struct Token_;

struct Token_List;

struct Token_List* go_4(struct Token_List* acc_1, struct Token_List* xs_7);

struct Token_List* tokenListRev_(struct Token_List* xs_6);

int isDigit_(char c_1);

struct CharBoolFun1;

int go_5(struct String source_, struct CharBoolFun1 pred_, int r_1);

struct StringIntTuple2;

int takeWhile_(struct CharBoolFun1 pred_, struct StringIntTuple2 arg_16);

struct CharTuple1;

int fun_(void* env_, char arg_);

struct Token_ListIntTuple2;

struct Token_ListIntTuple2 readSpace_(struct String source_1, struct Token_ListIntTuple2 arg_17);

struct Token_ListIntTuple2 readEol_(struct String source_2, struct Token_ListIntTuple2 arg_18);

int fun_1(void* env_1, char arg_2);

struct Token_ListIntTuple2 readInt_(struct String source_3, struct Token_ListIntTuple2 arg_19);

char at_(struct String source_4, int i_6);

struct Token_List* go_6(struct String source_4, struct Token_ListIntTuple2 arg_20);

struct Token_List* tokenize_(struct String source_4);

int tokenListPrint_(struct Token_List* tokens_);

struct IntToken_ListTuple2;

struct IntToken_ListTuple2 evalTerm_(struct Token_List* tokens_4);

struct IntToken_ListTuple2 go_7(int acc_6, struct Token_List* tokens_9);

struct IntToken_ListTuple2 evalMul_(struct Token_List* tokens_8);

struct IntToken_ListTuple2 go_8(int acc_7, struct Token_List* tokens_14);

struct IntToken_ListTuple2 evalAdd_(struct Token_List* tokens_13);

struct IntToken_ListTuple2 evalExpr_(struct Token_List* tokens_3);

int eval_(struct String str_);

int main();

int charEq_(char l_, char r_) {
    return (l_ == r_);
}

int go_(struct String s_, char c_, int i_) {
tailrec_1:;
    int if_;
    if ((i_ >= s_.len)) goto else_2;
    int if_1;
    if ((s_.str[i_] != c_)) goto else_4;
    if_1 = 1;
    goto end_if_5;
else_4:;
    struct String arg_3 = s_;
    char arg_4 = c_;
    int arg_5 = (i_ + 1);
    s_ = arg_3;
    c_ = arg_4;
    i_ = arg_5;
    goto tailrec_1;
    if_1 = 0;
end_if_5:;
    if_ = if_1;
    goto end_if_3;
else_2:;
    if_ = 0;
end_if_3:;
    return if_;
}

int strContains_(char c_, struct String s_) {
    int call_ = go_(s_, c_, 0);
    return call_;
}

int go_1(struct String s_1, struct String prefix_, int i_1) {
tailrec_6:;
    int if_2;
    if ((i_1 < prefix_.len)) goto else_7;
    if_2 = 1;
    goto end_if_8;
else_7:;
    int if_3;
    if ((s_1.str[i_1] != prefix_.str[i_1])) goto else_9;
    struct String arg_6 = s_1;
    struct String arg_7 = prefix_;
    int arg_8 = (i_1 + 1);
    s_1 = arg_6;
    prefix_ = arg_7;
    i_1 = arg_8;
    goto tailrec_6;
    if_3 = 0;
    goto end_if_10;
else_9:;
    if_3 = 0;
end_if_10:;
    if_2 = if_3;
end_if_8:;
    return if_2;
}

int strStartsWith_(struct String prefix_, struct String s_1) {
    int if_4;
    if ((s_1.len < prefix_.len)) goto else_11;
    int call_1 = go_1(s_1, prefix_, 0);
    if_4 = call_1;
    goto end_if_12;
else_11:;
    if_4 = 0;
end_if_12:;
    return if_4;
}

struct StringList {
    struct String head;
    struct StringList* tail;
};

struct String go_2(struct StringList* xs_1) {
    struct String match_;
    if ((!((!(xs_1))))) goto next_14;
    match_ = (struct String){.str = "", .len = 0};
    goto end_match_13;
next_14:;
    if ((!(xs_1))) goto next_15;
    struct String x_ = xs_1->head;
    struct StringList* xs_2 = xs_1->tail;
    struct String call_2 = go_2(xs_2);
    match_ = str_add(x_, call_2);
    goto end_match_13;
next_15:;
    exit(1);
end_match_13:;
    return match_;
}

struct String strConcat_(struct StringList* xs_) {
    struct String call_3 = go_2(xs_);
    return call_3;
}

struct StringList* go_3(struct StringList* acc_, struct StringList* xs_4) {
tailrec_16:;
    struct StringList* match_1;
    if ((!((!(xs_4))))) goto next_18;
    match_1 = acc_;
    goto end_match_17;
next_18:;
    if ((!(xs_4))) goto next_19;
    struct String x_1 = xs_4->head;
    struct StringList* xs_5 = xs_4->tail;
    struct StringList* list_ = (struct StringList*)milone_mem_alloc(1, sizeof(struct StringList));
    list_->head = x_1;
    list_->tail = acc_;
    struct StringList* arg_9 = list_;
    struct StringList* arg_10 = xs_5;
    acc_ = arg_9;
    xs_4 = arg_10;
    goto tailrec_16;
    match_1 = NULL;
    goto end_match_17;
next_19:;
    exit(1);
end_match_17:;
    return match_1;
}

struct StringList* strListRev_(struct StringList* xs_3) {
    struct StringList* call_4 = go_3(NULL, xs_3);
    return call_4;
}

enum Token_Tag {
    TkInt_,
    TkOp_,
};

struct Token_ {
    enum Token_Tag tag;
    union {
        void* TkInt_;
        void* TkOp_;
    };
};

struct Token_List {
    struct Token_ head;
    struct Token_List* tail;
};

struct Token_List* go_4(struct Token_List* acc_1, struct Token_List* xs_7) {
tailrec_20:;
    struct Token_List* match_2;
    if ((!((!(xs_7))))) goto next_22;
    match_2 = acc_1;
    goto end_match_21;
next_22:;
    if ((!(xs_7))) goto next_23;
    struct Token_ x_2 = xs_7->head;
    struct Token_List* xs_8 = xs_7->tail;
    struct Token_List* list_1 = (struct Token_List*)milone_mem_alloc(1, sizeof(struct Token_List));
    list_1->head = x_2;
    list_1->tail = acc_1;
    struct Token_List* arg_11 = list_1;
    struct Token_List* arg_12 = xs_8;
    acc_1 = arg_11;
    xs_7 = arg_12;
    goto tailrec_20;
    match_2 = NULL;
    goto end_match_21;
next_23:;
    exit(1);
end_match_21:;
    return match_2;
}

struct Token_List* tokenListRev_(struct Token_List* xs_6) {
    struct Token_List* call_5 = go_4(NULL, xs_6);
    return call_5;
}

int isDigit_(char c_1) {
    int if_5;
    if ((c_1 < '0')) goto else_24;
    if_5 = ('9' >= c_1);
    goto end_if_25;
else_24:;
    if_5 = 0;
end_if_25:;
    return if_5;
}

struct CharBoolFun1 {
    int(*fun)(void*, char);
    void* env;
};

int go_5(struct String source_, struct CharBoolFun1 pred_, int r_1) {
tailrec_26:;
    int if_6;
    int if_7;
    if ((r_1 >= source_.len)) goto else_29;
    int app_ = pred_.fun(pred_.env, source_.str[r_1]);
    if_7 = app_;
    goto end_if_30;
else_29:;
    if_7 = 0;
end_if_30:;
    if ((!(if_7))) goto else_27;
    struct String arg_13 = source_;
    struct CharBoolFun1 arg_14 = pred_;
    int arg_15 = (r_1 + 1);
    source_ = arg_13;
    pred_ = arg_14;
    r_1 = arg_15;
    goto tailrec_26;
    if_6 = 0;
    goto end_if_28;
else_27:;
    if_6 = r_1;
end_if_28:;
    return if_6;
}

struct StringIntTuple2 {
    struct String t0;
    int t1;
};

int takeWhile_(struct CharBoolFun1 pred_, struct StringIntTuple2 arg_16) {
    struct String source_ = arg_16.t0;
    int i_2 = arg_16.t1;
    int call_6 = go_5(source_, pred_, i_2);
    return call_6;
}

struct CharTuple1 {
    char t0;
};

int fun_(void* env_, char arg_) {
    char arg_1 = (*(((struct CharTuple1*)env_))).t0;
    int call_7 = charEq_(arg_1, arg_);
    return call_7;
}

struct Token_ListIntTuple2 {
    struct Token_List* t0;
    int t1;
};

struct Token_ListIntTuple2 readSpace_(struct String source_1, struct Token_ListIntTuple2 arg_17) {
    struct Token_List* acc_2 = arg_17.t0;
    int i_3 = arg_17.t1;
    milone_assert((source_1.str[i_3] == ' '), 57, 2);
    int call_8 = 0;
    struct CharTuple1 tuple_;
    tuple_.t0 = ' ';
    void* box_ = (void*)milone_mem_alloc(1, sizeof(struct CharTuple1));
    (*(((struct CharTuple1*)box_))) = tuple_;
    void* env_2 = box_;
    struct CharBoolFun1 fun_2 = (struct CharBoolFun1){.fun = fun_, .env = env_2};
    struct StringIntTuple2 tuple_1;
    tuple_1.t0 = source_1;
    tuple_1.t1 = (i_3 + 1);
    int call_9 = takeWhile_(fun_2, tuple_1);
    int r_2 = call_9;
    struct Token_ListIntTuple2 tuple_2;
    tuple_2.t0 = acc_2;
    tuple_2.t1 = r_2;
    return tuple_2;
}

struct Token_ListIntTuple2 readEol_(struct String source_2, struct Token_ListIntTuple2 arg_18) {
    struct Token_List* acc_3 = arg_18.t0;
    int i_4 = arg_18.t1;
    int if_8;
    if ((source_2.str[i_4] != '\r')) goto else_31;
    if_8 = 1;
    goto end_if_32;
else_31:;
    if_8 = (source_2.str[i_4] == '\n');
end_if_32:;
    milone_assert(if_8, 62, 2);
    int call_10 = 0;
    int if_9;
    int if_10;
    int if_11;
    if (((i_4 + 1) >= source_2.len)) goto else_37;
    if_11 = (source_2.str[i_4] == '\r');
    goto end_if_38;
else_37:;
    if_11 = 0;
end_if_38:;
    if ((!(if_11))) goto else_35;
    if_10 = (source_2.str[(i_4 + 1)] == '\n');
    goto end_if_36;
else_35:;
    if_10 = 0;
end_if_36:;
    if ((!(if_10))) goto else_33;
    if_9 = (i_4 + 2);
    goto end_if_34;
else_33:;
    if_9 = (i_4 + 1);
end_if_34:;
    int r_3 = if_9;
    struct Token_ListIntTuple2 tuple_3;
    tuple_3.t0 = acc_3;
    tuple_3.t1 = r_3;
    return tuple_3;
}

int fun_1(void* env_1, char arg_2) {
    int call_11 = isDigit_(arg_2);
    return call_11;
}

struct Token_ListIntTuple2 readInt_(struct String source_3, struct Token_ListIntTuple2 arg_19) {
    struct Token_List* acc_4 = arg_19.t0;
    int i_5 = arg_19.t1;
    int call_12 = isDigit_(source_3.str[i_5]);
    milone_assert(call_12, 70, 2);
    int call_13 = 0;
    void* box_1 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_1))) = 0;
    void* env_3 = box_1;
    struct CharBoolFun1 fun_3 = (struct CharBoolFun1){.fun = fun_1, .env = env_3};
    struct StringIntTuple2 tuple_4;
    tuple_4.t0 = source_3;
    tuple_4.t1 = i_5;
    int call_14 = takeWhile_(fun_3, tuple_4);
    int r_4 = call_14;
    struct String call_15 = str_get_slice(i_5, (r_4 - 1), source_3);
    int call_16 = str_to_int(call_15);
    int n_ = call_16;
    void* box_2 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_2))) = n_;
    struct Token_ variant_ = (struct Token_){.tag = TkInt_, .TkInt_ = box_2};
    struct Token_List* list_2 = (struct Token_List*)milone_mem_alloc(1, sizeof(struct Token_List));
    list_2->head = variant_;
    list_2->tail = acc_4;
    struct Token_ListIntTuple2 tuple_5;
    tuple_5.t0 = list_2;
    tuple_5.t1 = r_4;
    return tuple_5;
}

char at_(struct String source_4, int i_6) {
    char if_12;
    if ((i_6 >= source_4.len)) goto else_39;
    if_12 = source_4.str[i_6];
    goto end_if_40;
else_39:;
    if_12 = '\0';
end_if_40:;
    return if_12;
}

struct Token_List* go_6(struct String source_4, struct Token_ListIntTuple2 arg_20) {
tailrec_41:;
    struct Token_List* acc_5 = arg_20.t0;
    int i_7 = arg_20.t1;
    struct Token_List* if_13;
    if ((i_7 < source_4.len)) goto else_42;
    struct Token_List* call_17 = tokenListRev_(acc_5);
    if_13 = call_17;
    goto end_if_43;
else_42:;
    struct Token_List* switch_;
    switch (source_4.str[i_7]) {
       case ' ':
          goto clause_45;

       case '\r':
          goto clause_46;

       case '\n':
          goto clause_47;

       default:
          goto clause_48;
    }
clause_45:;
    struct String arg_21 = source_4;
    struct Token_ListIntTuple2 tuple_6;
    tuple_6.t0 = acc_5;
    tuple_6.t1 = i_7;
    struct Token_ListIntTuple2 call_18 = readSpace_(source_4, tuple_6);
    struct Token_ListIntTuple2 arg_22 = call_18;
    source_4 = arg_21;
    arg_20 = arg_22;
    goto tailrec_41;
    switch_ = NULL;
    goto switch_next_44;
clause_46:;
    struct String arg_23 = source_4;
    struct Token_ListIntTuple2 tuple_7;
    tuple_7.t0 = acc_5;
    tuple_7.t1 = i_7;
    struct Token_ListIntTuple2 call_19 = readEol_(source_4, tuple_7);
    struct Token_ListIntTuple2 arg_24 = call_19;
    source_4 = arg_23;
    arg_20 = arg_24;
    goto tailrec_41;
    switch_ = NULL;
    goto switch_next_44;
clause_47:;
    struct String arg_25 = source_4;
    struct Token_ListIntTuple2 tuple_8;
    tuple_8.t0 = acc_5;
    tuple_8.t1 = i_7;
    struct Token_ListIntTuple2 call_20 = readEol_(source_4, tuple_8);
    struct Token_ListIntTuple2 arg_26 = call_20;
    source_4 = arg_25;
    arg_20 = arg_26;
    goto tailrec_41;
    switch_ = NULL;
    goto switch_next_44;
clause_48:;
    char c_2 = source_4.str[i_7];
    struct Token_List* if_14;
    int call_21 = isDigit_(c_2);
    if ((!(call_21))) goto else_49;
    struct String arg_27 = source_4;
    struct Token_ListIntTuple2 tuple_9;
    tuple_9.t0 = acc_5;
    tuple_9.t1 = i_7;
    struct Token_ListIntTuple2 call_22 = readInt_(source_4, tuple_9);
    struct Token_ListIntTuple2 arg_28 = call_22;
    source_4 = arg_27;
    arg_20 = arg_28;
    goto tailrec_41;
    if_14 = NULL;
    goto end_if_50;
else_49:;
    struct String arg_29 = source_4;
    void* box_3 = (void*)milone_mem_alloc(1, sizeof(char));
    (*(((char*)box_3))) = c_2;
    struct Token_ variant_1 = (struct Token_){.tag = TkOp_, .TkOp_ = box_3};
    struct Token_List* list_3 = (struct Token_List*)milone_mem_alloc(1, sizeof(struct Token_List));
    list_3->head = variant_1;
    list_3->tail = acc_5;
    struct Token_ListIntTuple2 tuple_10;
    tuple_10.t0 = list_3;
    tuple_10.t1 = (i_7 + 1);
    struct Token_ListIntTuple2 arg_30 = tuple_10;
    source_4 = arg_29;
    arg_20 = arg_30;
    goto tailrec_41;
    if_14 = NULL;
end_if_50:;
    switch_ = if_14;
    goto switch_next_44;
switch_next_44:;
    if_13 = switch_;
end_if_43:;
    return if_13;
}

struct Token_List* tokenize_(struct String source_4) {
    struct Token_ListIntTuple2 tuple_11;
    tuple_11.t0 = NULL;
    tuple_11.t1 = 0;
    struct Token_List* call_23 = go_6(source_4, tuple_11);
    return call_23;
}

int tokenListPrint_(struct Token_List* tokens_) {
tailrec_51:;
    int match_3;
    if ((!((!(tokens_))))) goto next_53;
    match_3 = 0;
    goto end_match_52;
next_53:;
    if ((!(tokens_))) goto next_54;
    if ((tokens_->head.tag != TkInt_)) goto next_54;
    int n_1 = (*(((int*)tokens_->head.TkInt_)));
    struct Token_List* tokens_1 = tokens_->tail;
    printf("int %d\n", n_1);
    int call_24 = 0;
    struct Token_List* arg_31 = tokens_1;
    tokens_ = arg_31;
    goto tailrec_51;
    match_3 = 0;
    goto end_match_52;
next_54:;
    if ((!(tokens_))) goto next_55;
    if ((tokens_->head.tag != TkOp_)) goto next_55;
    char c_3 = (*(((char*)tokens_->head.TkOp_)));
    struct Token_List* tokens_2 = tokens_->tail;
    printf("op %c\n", c_3);
    int call_25 = 0;
    struct Token_List* arg_32 = tokens_2;
    tokens_ = arg_32;
    goto tailrec_51;
    match_3 = 0;
    goto end_match_52;
next_55:;
    exit(1);
end_match_52:;
    return 0;
}

struct IntToken_ListTuple2 {
    int t0;
    struct Token_List* t1;
};

struct IntToken_ListTuple2 evalTerm_(struct Token_List* tokens_4) {
    struct IntToken_ListTuple2 match_4;
    if ((!(tokens_4))) goto next_57;
    if ((tokens_4->head.tag != TkInt_)) goto next_57;
    int n_2 = (*(((int*)tokens_4->head.TkInt_)));
    struct Token_List* tokens_5 = tokens_4->tail;
    struct IntToken_ListTuple2 tuple_12;
    tuple_12.t0 = n_2;
    tuple_12.t1 = tokens_5;
    match_4 = tuple_12;
    goto end_match_56;
next_57:;
    if ((!(tokens_4))) goto next_58;
    if ((tokens_4->head.tag != TkOp_)) goto next_58;
    if (((*(((char*)tokens_4->head.TkOp_))) != '(')) goto next_58;
    struct Token_List* tokens_6 = tokens_4->tail;
    struct IntToken_ListTuple2 match_5;
    struct IntToken_ListTuple2 call_26 = evalExpr_(tokens_6);
    int value_ = call_26.t0;
    if ((!(call_26.t1))) goto next_61;
    if ((call_26.t1->head.tag != TkOp_)) goto next_61;
    if (((*(((char*)call_26.t1->head.TkOp_))) != ')')) goto next_61;
    struct Token_List* tokens_7 = call_26.t1->tail;
    struct IntToken_ListTuple2 tuple_13;
    tuple_13.t0 = value_;
    tuple_13.t1 = tokens_7;
    match_5 = tuple_13;
    goto end_match_60;
next_61:;
    printf("expected \')\'\n");
    int call_27 = 0;
    exit(1);
    match_5 = ((struct IntToken_ListTuple2){});
    goto end_match_60;
next_62:;
end_match_60:;
    match_4 = match_5;
    goto end_match_56;
next_58:;
    printf("expected an int\n");
    int call_28 = 0;
    exit(1);
    match_4 = ((struct IntToken_ListTuple2){});
    goto end_match_56;
next_59:;
end_match_56:;
    return match_4;
}

struct IntToken_ListTuple2 go_7(int acc_6, struct Token_List* tokens_9) {
tailrec_63:;
    struct IntToken_ListTuple2 match_6;
    if ((!(tokens_9))) goto next_65;
    if ((tokens_9->head.tag != TkOp_)) goto next_65;
    if (((*(((char*)tokens_9->head.TkOp_))) != '*')) goto next_65;
    struct Token_List* tokens_10 = tokens_9->tail;
    struct IntToken_ListTuple2 call_29 = evalTerm_(tokens_10);
    int r_5 = call_29.t0;
    struct Token_List* tokens_11 = call_29.t1;
    int arg_33 = (acc_6 * r_5);
    struct Token_List* arg_34 = tokens_11;
    acc_6 = arg_33;
    tokens_9 = arg_34;
    goto tailrec_63;
    match_6 = ((struct IntToken_ListTuple2){});
    goto end_match_64;
next_65:;
    struct IntToken_ListTuple2 tuple_14;
    tuple_14.t0 = acc_6;
    tuple_14.t1 = tokens_9;
    match_6 = tuple_14;
    goto end_match_64;
next_66:;
end_match_64:;
    return match_6;
}

struct IntToken_ListTuple2 evalMul_(struct Token_List* tokens_8) {
    struct IntToken_ListTuple2 call_30 = evalTerm_(tokens_8);
    int l_1 = call_30.t0;
    struct Token_List* tokens_12 = call_30.t1;
    struct IntToken_ListTuple2 call_31 = go_7(l_1, tokens_12);
    return call_31;
}

struct IntToken_ListTuple2 go_8(int acc_7, struct Token_List* tokens_14) {
tailrec_67:;
    struct IntToken_ListTuple2 match_7;
    if ((!(tokens_14))) goto next_69;
    if ((tokens_14->head.tag != TkOp_)) goto next_69;
    if (((*(((char*)tokens_14->head.TkOp_))) != '+')) goto next_69;
    struct Token_List* tokens_15 = tokens_14->tail;
    struct IntToken_ListTuple2 call_32 = evalMul_(tokens_15);
    int r_6 = call_32.t0;
    struct Token_List* tokens_16 = call_32.t1;
    int arg_35 = (acc_7 + r_6);
    struct Token_List* arg_36 = tokens_16;
    acc_7 = arg_35;
    tokens_14 = arg_36;
    goto tailrec_67;
    match_7 = ((struct IntToken_ListTuple2){});
    goto end_match_68;
next_69:;
    if ((!(tokens_14))) goto next_70;
    if ((tokens_14->head.tag != TkOp_)) goto next_70;
    if (((*(((char*)tokens_14->head.TkOp_))) != '-')) goto next_70;
    struct Token_List* tokens_17 = tokens_14->tail;
    struct IntToken_ListTuple2 call_33 = evalMul_(tokens_17);
    int r_7 = call_33.t0;
    struct Token_List* tokens_18 = call_33.t1;
    int arg_37 = (acc_7 - r_7);
    struct Token_List* arg_38 = tokens_18;
    acc_7 = arg_37;
    tokens_14 = arg_38;
    goto tailrec_67;
    match_7 = ((struct IntToken_ListTuple2){});
    goto end_match_68;
next_70:;
    struct IntToken_ListTuple2 tuple_15;
    tuple_15.t0 = acc_7;
    tuple_15.t1 = tokens_14;
    match_7 = tuple_15;
    goto end_match_68;
next_71:;
end_match_68:;
    return match_7;
}

struct IntToken_ListTuple2 evalAdd_(struct Token_List* tokens_13) {
    struct IntToken_ListTuple2 call_34 = evalMul_(tokens_13);
    int l_2 = call_34.t0;
    struct Token_List* tokens_19 = call_34.t1;
    struct IntToken_ListTuple2 call_35 = go_8(l_2, tokens_19);
    return call_35;
}

struct IntToken_ListTuple2 evalExpr_(struct Token_List* tokens_3) {
    struct IntToken_ListTuple2 call_36 = evalAdd_(tokens_3);
    return call_36;
}

int eval_(struct String str_) {
    int match_8;
    struct Token_List* call_37 = tokenize_(str_);
    struct IntToken_ListTuple2 call_38 = evalExpr_(call_37);
    int value_1 = call_38.t0;
    if ((!((!(call_38.t1))))) goto next_73;
    match_8 = value_1;
    goto end_match_72;
next_73:;
    struct Token_List* tokens_20 = call_38.t1;
    printf("ERROR: couldn\'t parse tokens:\n");
    int call_39 = 0;
    int call_40 = tokenListPrint_(tokens_20);
    exit(1);
    match_8 = 0;
    goto end_match_72;
next_74:;
end_match_72:;
    return match_8;
}

int main() {
    int call_41 = strContains_('+', (struct String){.str = "+-*/", .len = 4});
    milone_assert(call_41, 159, 2);
    int call_42 = 0;
    int call_43 = strStartsWith_((struct String){.str = "hell", .len = 4}, (struct String){.str = "hello", .len = 5});
    milone_assert(call_43, 160, 2);
    int call_44 = 0;
    int call_45 = strStartsWith_((struct String){.str = "heaven", .len = 6}, (struct String){.str = "hello", .len = 5});
    milone_assert((!(call_45)), 161, 2);
    int call_46 = 0;
    struct StringList* list_6 = (struct StringList*)milone_mem_alloc(1, sizeof(struct StringList));
    list_6->head = (struct String){.str = "b", .len = 1};
    list_6->tail = NULL;
    struct StringList* list_5 = (struct StringList*)milone_mem_alloc(1, sizeof(struct StringList));
    list_5->head = (struct String){.str = ",", .len = 1};
    list_5->tail = list_6;
    struct StringList* list_4 = (struct StringList*)milone_mem_alloc(1, sizeof(struct StringList));
    list_4->head = (struct String){.str = "a", .len = 1};
    list_4->tail = list_5;
    struct String call_47 = strConcat_(list_4);
    milone_assert((str_cmp(call_47, (struct String){.str = "a,b", .len = 3}) == 0), 162, 2);
    int call_48 = 0;
    struct StringList* list_9 = (struct StringList*)milone_mem_alloc(1, sizeof(struct StringList));
    list_9->head = (struct String){.str = "b", .len = 1};
    list_9->tail = NULL;
    struct StringList* list_8 = (struct StringList*)milone_mem_alloc(1, sizeof(struct StringList));
    list_8->head = (struct String){.str = ",", .len = 1};
    list_8->tail = list_9;
    struct StringList* list_7 = (struct StringList*)milone_mem_alloc(1, sizeof(struct StringList));
    list_7->head = (struct String){.str = "a", .len = 1};
    list_7->tail = list_8;
    struct StringList* call_49 = strListRev_(list_7);
    struct String call_50 = strConcat_(call_49);
    milone_assert((str_cmp(call_50, (struct String){.str = "b,a", .len = 3}) == 0), 163, 2);
    int call_51 = 0;
    struct String source_5 = (struct String){.str = "2 + 3\r\n    - 4", .len = 14};
    struct Token_List* call_52 = tokenize_(source_5);
    int call_53 = tokenListPrint_(call_52);
    int call_54 = eval_(source_5);
    milone_assert((call_54 == ((2 + 3) - 4)), 168, 2);
    int call_55 = 0;
    int call_56 = eval_((struct String){.str = "2 - 3 * 4 + 5", .len = 13});
    milone_assert((call_56 == ((2 - (3 * 4)) + 5)), 169, 2);
    int call_57 = 0;
    int call_58 = eval_((struct String){.str = "(2 - 3) * 4 + (1 + (2 + 2))", .len = 27});
    milone_assert((call_58 == (((2 - 3) * 4) + (1 + (2 + 2)))), 170, 2);
    int call_59 = 0;
    return 0;
}
