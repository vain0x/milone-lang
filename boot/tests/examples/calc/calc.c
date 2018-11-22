int assert_(int ok_) {
    int if_;
    if (!((!(ok_)))) goto else_1;
    printf("Assertion failed.\n");
    int call_ = 0;
    exit(1);
    if_ = 0;
    goto end_if_2;
else_1:;
    if_ = 0;
end_if_2:;
    return 0;
}

int charEq_(char l_, char r_) {
    return (l_ == r_);
}

int charBetween_(char l_1, char r_1, char c_) {
    int if_1;
    if (!((l_1 <= c_))) goto else_3;
    if_1 = (c_ <= r_1);
    goto end_if_4;
else_3:;
    if_1 = 0;
end_if_4:;
    return if_1;
}

struct CharStringTuple2 {
    char t0;
    struct String t1;
};

int go_(struct CharStringTuple2 caps_1, int i_) {
    struct String s_ = caps_1.t1;
    char c_1 = caps_1.t0;
    int if_2;
    if (!((i_ < s_.len))) goto else_5;
    int if_3;
    if (!((s_.str[i_] == c_1))) goto else_7;
    if_3 = 1;
    goto end_if_8;
else_7:;
    struct CharStringTuple2 caps_;
    caps_.t0 = c_1;
    caps_.t1 = s_;
    int call_1 = go_(caps_, (i_ + 1));
    if_3 = call_1;
end_if_8:;
    if_2 = if_3;
    goto end_if_6;
else_5:;
    if_2 = 0;
end_if_6:;
    return if_2;
}

int strContains_(char c_1, struct String s_) {
    struct CharStringTuple2 caps_3;
    caps_3.t0 = c_1;
    caps_3.t1 = s_;
    int call_2 = go_(caps_3, 0);
    return call_2;
}

struct StringStringTuple2 {
    struct String t0;
    struct String t1;
};

int go_1(struct StringStringTuple2 caps_5, int i_1) {
    struct String s_1 = caps_5.t1;
    struct String prefix_ = caps_5.t0;
    int if_4;
    if (!((prefix_.len <= i_1))) goto else_9;
    if_4 = 1;
    goto end_if_10;
else_9:;
    int if_5;
    if (!((s_1.str[i_1] == prefix_.str[i_1]))) goto else_11;
    struct StringStringTuple2 caps_4;
    caps_4.t0 = prefix_;
    caps_4.t1 = s_1;
    int call_3 = go_1(caps_4, (i_1 + 1));
    if_5 = call_3;
    goto end_if_12;
else_11:;
    if_5 = 0;
end_if_12:;
    if_4 = if_5;
end_if_10:;
    return if_4;
}

int strStartsWith_(struct String prefix_, struct String s_1) {
    int if_6;
    if (!((prefix_.len <= s_1.len))) goto else_13;
    struct StringStringTuple2 caps_7;
    caps_7.t0 = prefix_;
    caps_7.t1 = s_1;
    int call_4 = go_1(caps_7, 0);
    if_6 = call_4;
    goto end_if_14;
else_13:;
    if_6 = 0;
end_if_14:;
    return if_6;
}

struct StringList {
    struct String head;
    struct StringList* tail;
};

struct String go_2(struct StringList* xs_1) {
    struct String match_;
    if (!((!(xs_1)))) goto next_16;
    match_ = (struct String){.str = "", .len = 0};
    goto end_match_15;
next_16:;
    if (!((!((!(xs_1)))))) goto next_17;
    struct String x_ = xs_1->head;
    struct StringList* xs_2 = xs_1->tail;
    struct String call_5 = go_2(xs_2);
    match_ = str_add(x_, call_5);
    goto end_match_15;
next_17:;
    exit(1);
end_match_15:;
    return match_;
}

struct String strConcat_(struct StringList* xs_) {
    struct String call_6 = go_2(xs_);
    return call_6;
}

struct StringList* go_3(struct StringList* acc_, struct StringList* xs_4) {
    struct StringList* match_1;
    if (!((!(xs_4)))) goto next_19;
    match_1 = acc_;
    goto end_match_18;
next_19:;
    if (!((!((!(xs_4)))))) goto next_20;
    struct String x_1 = xs_4->head;
    struct StringList* xs_5 = xs_4->tail;
    struct StringList* list_ = (struct StringList*)malloc(sizeof(struct StringList));
    list_->head = x_1;
    list_->tail = acc_;
    struct StringList* call_7 = go_3(list_, xs_5);
    match_1 = call_7;
    goto end_match_18;
next_20:;
    exit(1);
end_match_18:;
    return match_1;
}

struct StringList* strListRev_(struct StringList* xs_3) {
    struct StringList* call_8 = go_3(NULL, xs_3);
    return call_8;
}

struct String digitToString_(int n_) {
    struct String match_2;
    if (!((n_ == 0))) goto next_22;
    match_2 = (struct String){.str = "0", .len = 1};
    goto end_match_21;
next_22:;
    if (!((n_ == 1))) goto next_23;
    match_2 = (struct String){.str = "1", .len = 1};
    goto end_match_21;
next_23:;
    if (!((n_ == 2))) goto next_24;
    match_2 = (struct String){.str = "2", .len = 1};
    goto end_match_21;
next_24:;
    if (!((n_ == 3))) goto next_25;
    match_2 = (struct String){.str = "3", .len = 1};
    goto end_match_21;
next_25:;
    if (!((n_ == 4))) goto next_26;
    match_2 = (struct String){.str = "4", .len = 1};
    goto end_match_21;
next_26:;
    if (!((n_ == 5))) goto next_27;
    match_2 = (struct String){.str = "5", .len = 1};
    goto end_match_21;
next_27:;
    if (!((n_ == 6))) goto next_28;
    match_2 = (struct String){.str = "6", .len = 1};
    goto end_match_21;
next_28:;
    if (!((n_ == 7))) goto next_29;
    match_2 = (struct String){.str = "7", .len = 1};
    goto end_match_21;
next_29:;
    if (!((n_ == 8))) goto next_30;
    match_2 = (struct String){.str = "8", .len = 1};
    goto end_match_21;
next_30:;
    if (!((n_ == 9))) goto next_31;
    match_2 = (struct String){.str = "9", .len = 1};
    goto end_match_21;
next_31:;
    exit(1);
    match_2 = ((struct String){});
    goto end_match_21;
next_32:;
end_match_21:;
    return match_2;
}

int digitToInt_(char c_2) {
    int match_3;
    if (!((c_2 == '0'))) goto next_34;
    match_3 = 0;
    goto end_match_33;
next_34:;
    if (!((c_2 == '1'))) goto next_35;
    match_3 = 1;
    goto end_match_33;
next_35:;
    if (!((c_2 == '2'))) goto next_36;
    match_3 = 2;
    goto end_match_33;
next_36:;
    if (!((c_2 == '3'))) goto next_37;
    match_3 = 3;
    goto end_match_33;
next_37:;
    if (!((c_2 == '4'))) goto next_38;
    match_3 = 4;
    goto end_match_33;
next_38:;
    if (!((c_2 == '5'))) goto next_39;
    match_3 = 5;
    goto end_match_33;
next_39:;
    if (!((c_2 == '6'))) goto next_40;
    match_3 = 6;
    goto end_match_33;
next_40:;
    if (!((c_2 == '7'))) goto next_41;
    match_3 = 7;
    goto end_match_33;
next_41:;
    if (!((c_2 == '8'))) goto next_42;
    match_3 = 8;
    goto end_match_33;
next_42:;
    if (!((c_2 == '9'))) goto next_43;
    match_3 = 9;
    goto end_match_33;
next_43:;
    exit(1);
    match_3 = 0;
    goto end_match_33;
next_44:;
end_match_33:;
    return match_3;
}

struct String go_4(struct String acc_1, int n_1) {
    struct String if_7;
    if (!((n_1 <= 0))) goto else_45;
    if_7 = acc_1;
    goto end_if_46;
else_45:;
    struct String call_9 = digitToString_((n_1 % 10));
    struct String call_10 = go_4(str_add(call_9, acc_1), (n_1 / 10));
    if_7 = call_10;
end_if_46:;
    return if_7;
}

struct String intToString_(int value_) {
    struct String if_8;
    if (!((value_ == 0))) goto else_47;
    if_8 = (struct String){.str = "0", .len = 1};
    goto end_if_48;
else_47:;
    struct String call_11 = go_4((struct String){.str = "", .len = 0}, value_);
    if_8 = call_11;
end_if_48:;
    return if_8;
}

struct StringIntTuple2 {
    struct String t0;
    int t1;
};

int go_5(struct StringIntTuple2 caps_9, int acc_2, int i_2) {
    int r_2 = caps_9.t1;
    struct String source_ = caps_9.t0;
    int if_9;
    if (!((r_2 <= i_2))) goto else_49;
    if_9 = acc_2;
    goto end_if_50;
else_49:;
    int call_12 = digitToInt_(source_.str[i_2]);
    struct StringIntTuple2 caps_8;
    caps_8.t0 = source_;
    caps_8.t1 = r_2;
    int call_13 = go_5(caps_8, ((acc_2 * 10) + call_12), (i_2 + 1));
    if_9 = call_13;
end_if_50:;
    return if_9;
}

int intParseCore_(struct String source_, int l_2, int r_2) {
    struct StringIntTuple2 caps_11;
    caps_11.t0 = source_;
    caps_11.t1 = r_2;
    int call_14 = go_5(caps_11, 0, l_2);
    return call_14;
}

int intParse_(struct String source_1) {
    int call_15 = intParseCore_(source_1, 0, source_1.len);
    return call_15;
}

enum Token_Tag {
    TkInt_,
    TkOp_,
};

struct Token_ {
    enum Token_Tag tag;
    union {
        int TkInt_;
        char TkOp_;
    };
};

struct Token_List {
    struct Token_ head;
    struct Token_List* tail;
};

struct Token_List* go_6(struct Token_List* acc_3, struct Token_List* xs_7) {
    struct Token_List* match_4;
    if (!((!(xs_7)))) goto next_52;
    match_4 = acc_3;
    goto end_match_51;
next_52:;
    if (!((!((!(xs_7)))))) goto next_53;
    struct Token_ x_2 = xs_7->head;
    struct Token_List* xs_8 = xs_7->tail;
    struct Token_List* list_1 = (struct Token_List*)malloc(sizeof(struct Token_List));
    list_1->head = x_2;
    list_1->tail = acc_3;
    struct Token_List* call_16 = go_6(list_1, xs_8);
    match_4 = call_16;
    goto end_match_51;
next_53:;
    exit(1);
end_match_51:;
    return match_4;
}

struct Token_List* tokenListRev_(struct Token_List* xs_6) {
    struct Token_List* call_17 = go_6(NULL, xs_6);
    return call_17;
}

int isDigit_(int arg_, char c_3) {
    int call_18 = charBetween_('0', '9', c_3);
    return call_18;
}

struct CharBoolFun {
    int(*fun)(void*, char);
    void* env;
};

struct CharBoolFunStringTuple2 {
    struct CharBoolFun t0;
    struct String t1;
};

int go_7(struct CharBoolFunStringTuple2 caps_13, int r_3) {
    struct String source_2 = caps_13.t1;
    struct CharBoolFun pred_ = caps_13.t0;
    int if_10;
    int if_11;
    if (!((r_3 < source_2.len))) goto else_56;
    int call_19 = pred_.fun(pred_.env, source_2.str[r_3]);
    if_11 = call_19;
    goto end_if_57;
else_56:;
    if_11 = 0;
end_if_57:;
    if (!(if_11)) goto else_54;
    struct CharBoolFunStringTuple2 caps_12;
    caps_12.t0 = pred_;
    caps_12.t1 = source_2;
    int call_20 = go_7(caps_12, (r_3 + 1));
    if_10 = call_20;
    goto end_if_55;
else_54:;
    if_10 = r_3;
end_if_55:;
    return if_10;
}

int takeWhile_(struct CharBoolFun pred_, struct StringIntTuple2 arg_1) {
    struct String source_2 = arg_1.t0;
    int i_3 = arg_1.t1;
    struct CharBoolFunStringTuple2 caps_15;
    caps_15.t0 = pred_;
    caps_15.t1 = source_2;
    int call_21 = go_7(caps_15, i_3);
    return call_21;
}

struct CharTuple1 {
    char t0;
};

int fun_(void* env_, char arg_6) {
    int call_84 = charEq_((*(((struct CharTuple1*)env_))).t0, arg_6);
    return call_84;
}

struct Token_ListIntTuple2 {
    struct Token_List* t0;
    int t1;
};

struct Token_ListIntTuple2 readSpace_(struct String source_3, struct Token_ListIntTuple2 arg_2) {
    struct Token_List* acc_4 = arg_2.t0;
    int i_4 = arg_2.t1;
    int call_22 = assert_((source_3.str[i_4] == ' '));
    struct CharTuple1 env_1;
    env_1.t0 = ' ';
    void* box_ = (void*)malloc(sizeof(struct CharTuple1));
    (*(((struct CharTuple1*)box_))) = env_1;
    struct CharBoolFun call_23 = (struct CharBoolFun){.fun = fun_, .env = box_};
    struct StringIntTuple2 tuple_;
    tuple_.t0 = source_3;
    tuple_.t1 = (i_4 + 1);
    int call_24 = takeWhile_(call_23, tuple_);
    int r_4 = call_24;
    struct Token_ListIntTuple2 tuple_1;
    tuple_1.t0 = acc_4;
    tuple_1.t1 = r_4;
    return tuple_1;
}

struct Token_ListIntTuple2 readEol_(struct String source_4, struct Token_ListIntTuple2 arg_3) {
    struct Token_List* acc_5 = arg_3.t0;
    int i_5 = arg_3.t1;
    int if_12;
    if (!((source_4.str[i_5] == '\r'))) goto else_58;
    if_12 = 1;
    goto end_if_59;
else_58:;
    if_12 = (source_4.str[i_5] == '\n');
end_if_59:;
    int call_25 = assert_(if_12);
    int if_13;
    int if_14;
    int if_15;
    if (!(((i_5 + 1) < source_4.len))) goto else_64;
    if_15 = (source_4.str[i_5] == '\r');
    goto end_if_65;
else_64:;
    if_15 = 0;
end_if_65:;
    if (!(if_15)) goto else_62;
    if_14 = (source_4.str[(i_5 + 1)] == '\n');
    goto end_if_63;
else_62:;
    if_14 = 0;
end_if_63:;
    if (!(if_14)) goto else_60;
    if_13 = (i_5 + 2);
    goto end_if_61;
else_60:;
    if_13 = (i_5 + 1);
end_if_61:;
    int r_5 = if_13;
    struct Token_ListIntTuple2 tuple_2;
    tuple_2.t0 = acc_5;
    tuple_2.t1 = r_5;
    return tuple_2;
}

struct UnitTuple1 {
    int t0;
};

int fun_1(void* env_2, char arg_7) {
    int call_85 = isDigit_((*(((struct UnitTuple1*)env_2))).t0, arg_7);
    return call_85;
}

struct Token_ListIntTuple2 readInt_(struct String source_5, struct Token_ListIntTuple2 arg_4) {
    struct Token_List* acc_6 = arg_4.t0;
    int i_6 = arg_4.t1;
    int call_26 = isDigit_(0, source_5.str[i_6]);
    int call_27 = assert_(call_26);
    struct UnitTuple1 env_3;
    env_3.t0 = 0;
    void* box_1 = (void*)malloc(sizeof(struct UnitTuple1));
    (*(((struct UnitTuple1*)box_1))) = env_3;
    struct CharBoolFun call_28 = (struct CharBoolFun){.fun = fun_1, .env = box_1};
    struct StringIntTuple2 tuple_3;
    tuple_3.t0 = source_5;
    tuple_3.t1 = i_6;
    int call_29 = takeWhile_(call_28, tuple_3);
    int r_6 = call_29;
    int call_30 = intParseCore_(source_5, i_6, r_6);
    int n_2 = call_30;
    struct Token_ variant_ = (struct Token_){.tag = TkInt_, .TkInt_ = n_2};
    struct Token_List* list_2 = (struct Token_List*)malloc(sizeof(struct Token_List));
    list_2->head = variant_;
    list_2->tail = acc_6;
    struct Token_ListIntTuple2 tuple_4;
    tuple_4.t0 = list_2;
    tuple_4.t1 = r_6;
    return tuple_4;
}

struct StringTuple1 {
    struct String t0;
};

char at_(struct StringTuple1 caps_16, int i_7) {
    struct String source_6 = caps_16.t0;
    char if_16;
    if (!((i_7 < source_6.len))) goto else_66;
    if_16 = source_6.str[i_7];
    goto end_if_67;
else_66:;
    if_16 = '\0';
end_if_67:;
    return if_16;
}

struct Token_List* go_8(struct StringTuple1 caps_22, struct Token_ListIntTuple2 arg_5) {
    struct String source_6 = caps_22.t0;
    struct Token_List* acc_7 = arg_5.t0;
    int i_8 = arg_5.t1;
    struct Token_List* if_17;
    if (!((source_6.len <= i_8))) goto else_68;
    struct Token_List* call_31 = tokenListRev_(acc_7);
    if_17 = call_31;
    goto end_if_69;
else_68:;
    struct Token_List* match_5;
    if (!((source_6.str[i_8] == ' '))) goto next_71;
    struct Token_ListIntTuple2 tuple_5;
    tuple_5.t0 = acc_7;
    tuple_5.t1 = i_8;
    struct Token_ListIntTuple2 call_32 = readSpace_(source_6, tuple_5);
    struct StringTuple1 caps_17;
    caps_17.t0 = source_6;
    struct Token_List* call_33 = go_8(caps_17, call_32);
    match_5 = call_33;
    goto end_match_70;
next_71:;
    if (!((source_6.str[i_8] == '\r'))) goto next_72;
    struct Token_ListIntTuple2 tuple_6;
    tuple_6.t0 = acc_7;
    tuple_6.t1 = i_8;
    struct Token_ListIntTuple2 call_34 = readEol_(source_6, tuple_6);
    struct StringTuple1 caps_18;
    caps_18.t0 = source_6;
    struct Token_List* call_35 = go_8(caps_18, call_34);
    match_5 = call_35;
    goto end_match_70;
next_72:;
    if (!((source_6.str[i_8] == '\n'))) goto next_73;
    struct Token_ListIntTuple2 tuple_7;
    tuple_7.t0 = acc_7;
    tuple_7.t1 = i_8;
    struct Token_ListIntTuple2 call_36 = readEol_(source_6, tuple_7);
    struct StringTuple1 caps_19;
    caps_19.t0 = source_6;
    struct Token_List* call_37 = go_8(caps_19, call_36);
    match_5 = call_37;
    goto end_match_70;
next_73:;
    char c_4 = source_6.str[i_8];
    struct Token_List* if_18;
    int call_38 = isDigit_(0, c_4);
    if (!(call_38)) goto else_75;
    struct Token_ListIntTuple2 tuple_8;
    tuple_8.t0 = acc_7;
    tuple_8.t1 = i_8;
    struct Token_ListIntTuple2 call_39 = readInt_(source_6, tuple_8);
    struct StringTuple1 caps_20;
    caps_20.t0 = source_6;
    struct Token_List* call_40 = go_8(caps_20, call_39);
    if_18 = call_40;
    goto end_if_76;
else_75:;
    struct Token_ variant_1 = (struct Token_){.tag = TkOp_, .TkOp_ = c_4};
    struct Token_List* list_3 = (struct Token_List*)malloc(sizeof(struct Token_List));
    list_3->head = variant_1;
    list_3->tail = acc_7;
    struct Token_ListIntTuple2 tuple_9;
    tuple_9.t0 = list_3;
    tuple_9.t1 = (i_8 + 1);
    struct StringTuple1 caps_21;
    caps_21.t0 = source_6;
    struct Token_List* call_41 = go_8(caps_21, tuple_9);
    if_18 = call_41;
end_if_76:;
    match_5 = if_18;
    goto end_match_70;
next_74:;
end_match_70:;
    if_17 = match_5;
end_if_69:;
    return if_17;
}

struct Token_List* tokenize_(struct String source_6) {
    struct Token_ListIntTuple2 tuple_10;
    tuple_10.t0 = NULL;
    tuple_10.t1 = 0;
    struct StringTuple1 caps_24;
    caps_24.t0 = source_6;
    struct Token_List* call_42 = go_8(caps_24, tuple_10);
    return call_42;
}

int tokenListPrint_(struct Token_List* tokens_) {
    int match_6;
    if (!((!(tokens_)))) goto next_78;
    match_6 = 0;
    goto end_match_77;
next_78:;
    if (!((!((!(tokens_)))))) goto next_79;
    if (!((tokens_->head.tag == TkInt_))) goto next_79;
    int n_3 = tokens_->head.TkInt_;
    struct Token_List* tokens_1 = tokens_->tail;
    printf("int %d\n", n_3);
    int call_43 = 0;
    int call_44 = tokenListPrint_(tokens_1);
    match_6 = 0;
    goto end_match_77;
next_79:;
    if (!((!((!(tokens_)))))) goto next_80;
    if (!((tokens_->head.tag == TkOp_))) goto next_80;
    char c_5 = tokens_->head.TkOp_;
    struct Token_List* tokens_2 = tokens_->tail;
    printf("op %c\n", c_5);
    int call_45 = 0;
    int call_46 = tokenListPrint_(tokens_2);
    match_6 = 0;
    goto end_match_77;
next_80:;
    exit(1);
end_match_77:;
    return 0;
}

struct IntToken_ListTuple2 {
    int t0;
    struct Token_List* t1;
};

struct IntToken_ListTuple2 evalTerm_(struct Token_List* tokens_4) {
    struct IntToken_ListTuple2 match_7;
    if (!((!((!(tokens_4)))))) goto next_82;
    if (!((tokens_4->head.tag == TkInt_))) goto next_82;
    int n_4 = tokens_4->head.TkInt_;
    struct Token_List* tokens_5 = tokens_4->tail;
    struct IntToken_ListTuple2 tuple_11;
    tuple_11.t0 = n_4;
    tuple_11.t1 = tokens_5;
    match_7 = tuple_11;
    goto end_match_81;
next_82:;
    printf("expected an int\n");
    int call_47 = 0;
    exit(1);
    match_7 = ((struct IntToken_ListTuple2){});
    goto end_match_81;
next_83:;
end_match_81:;
    return match_7;
}

struct IntToken_ListTuple2 go_9(int acc_8, struct Token_List* tokens_7) {
    struct IntToken_ListTuple2 match_8;
    if (!((!((!(tokens_7)))))) goto next_85;
    if (!((tokens_7->head.tag == TkOp_))) goto next_85;
    if (!((tokens_7->head.TkOp_ == '*'))) goto next_85;
    struct Token_List* tokens_8 = tokens_7->tail;
    struct IntToken_ListTuple2 call_48 = evalTerm_(tokens_8);
    int r_7 = call_48.t0;
    struct Token_List* tokens_9 = call_48.t1;
    struct IntToken_ListTuple2 call_49 = go_9((acc_8 * r_7), tokens_9);
    match_8 = call_49;
    goto end_match_84;
next_85:;
    struct IntToken_ListTuple2 tuple_12;
    tuple_12.t0 = acc_8;
    tuple_12.t1 = tokens_7;
    match_8 = tuple_12;
    goto end_match_84;
next_86:;
end_match_84:;
    return match_8;
}

struct IntToken_ListTuple2 evalMul_(struct Token_List* tokens_6) {
    struct IntToken_ListTuple2 call_50 = evalTerm_(tokens_6);
    int l_3 = call_50.t0;
    struct Token_List* tokens_10 = call_50.t1;
    struct IntToken_ListTuple2 call_51 = go_9(l_3, tokens_10);
    return call_51;
}

struct IntToken_ListTuple2 go_10(int acc_9, struct Token_List* tokens_12) {
    struct IntToken_ListTuple2 match_9;
    if (!((!((!(tokens_12)))))) goto next_88;
    if (!((tokens_12->head.tag == TkOp_))) goto next_88;
    if (!((tokens_12->head.TkOp_ == '+'))) goto next_88;
    struct Token_List* tokens_13 = tokens_12->tail;
    struct IntToken_ListTuple2 call_52 = evalMul_(tokens_13);
    int r_8 = call_52.t0;
    struct Token_List* tokens_14 = call_52.t1;
    struct IntToken_ListTuple2 call_53 = go_10((acc_9 + r_8), tokens_14);
    match_9 = call_53;
    goto end_match_87;
next_88:;
    if (!((!((!(tokens_12)))))) goto next_89;
    if (!((tokens_12->head.tag == TkOp_))) goto next_89;
    if (!((tokens_12->head.TkOp_ == '-'))) goto next_89;
    struct Token_List* tokens_15 = tokens_12->tail;
    struct IntToken_ListTuple2 call_54 = evalMul_(tokens_15);
    int r_9 = call_54.t0;
    struct Token_List* tokens_16 = call_54.t1;
    struct IntToken_ListTuple2 call_55 = go_10((acc_9 - r_9), tokens_16);
    match_9 = call_55;
    goto end_match_87;
next_89:;
    struct IntToken_ListTuple2 tuple_13;
    tuple_13.t0 = acc_9;
    tuple_13.t1 = tokens_12;
    match_9 = tuple_13;
    goto end_match_87;
next_90:;
end_match_87:;
    return match_9;
}

struct IntToken_ListTuple2 evalAdd_(struct Token_List* tokens_11) {
    struct IntToken_ListTuple2 call_56 = evalMul_(tokens_11);
    int l_4 = call_56.t0;
    struct Token_List* tokens_17 = call_56.t1;
    struct IntToken_ListTuple2 call_57 = go_10(l_4, tokens_17);
    return call_57;
}

struct IntToken_ListTuple2 evalExpr_(struct Token_List* tokens_3) {
    struct IntToken_ListTuple2 call_58 = evalAdd_(tokens_3);
    return call_58;
}

int eval_(struct String str_) {
    int match_10;
    struct Token_List* call_59 = tokenize_(str_);
    struct IntToken_ListTuple2 call_60 = evalExpr_(call_59);
    int value_1 = call_60.t0;
    if (!((!(call_60.t1)))) goto next_92;
    match_10 = value_1;
    goto end_match_91;
next_92:;
    struct Token_List* tokens_18 = call_60.t1;
    printf("ERROR: couldn't parse tokens:\n");
    int call_61 = 0;
    int call_62 = tokenListPrint_(tokens_18);
    exit(1);
    match_10 = 0;
    goto end_match_91;
next_93:;
end_match_91:;
    return match_10;
}

int main() {
    int call_63 = strContains_('+', (struct String){.str = "+-*/", .len = 4});
    int call_64 = assert_(call_63);
    int call_65 = strStartsWith_((struct String){.str = "hell", .len = 4}, (struct String){.str = "hello", .len = 5});
    int call_66 = assert_(call_65);
    int call_67 = strStartsWith_((struct String){.str = "heaven", .len = 6}, (struct String){.str = "hello", .len = 5});
    int call_68 = assert_((!(call_67)));
    struct StringList* list_6 = (struct StringList*)malloc(sizeof(struct StringList));
    list_6->head = (struct String){.str = "b", .len = 1};
    list_6->tail = NULL;
    struct StringList* list_5 = (struct StringList*)malloc(sizeof(struct StringList));
    list_5->head = (struct String){.str = ",", .len = 1};
    list_5->tail = list_6;
    struct StringList* list_4 = (struct StringList*)malloc(sizeof(struct StringList));
    list_4->head = (struct String){.str = "a", .len = 1};
    list_4->tail = list_5;
    struct String call_69 = strConcat_(list_4);
    int call_70 = assert_((str_cmp(call_69, (struct String){.str = "a,b", .len = 3}) == 0));
    struct StringList* list_9 = (struct StringList*)malloc(sizeof(struct StringList));
    list_9->head = (struct String){.str = "b", .len = 1};
    list_9->tail = NULL;
    struct StringList* list_8 = (struct StringList*)malloc(sizeof(struct StringList));
    list_8->head = (struct String){.str = ",", .len = 1};
    list_8->tail = list_9;
    struct StringList* list_7 = (struct StringList*)malloc(sizeof(struct StringList));
    list_7->head = (struct String){.str = "a", .len = 1};
    list_7->tail = list_8;
    struct StringList* call_71 = strListRev_(list_7);
    struct String call_72 = strConcat_(call_71);
    int call_73 = assert_((str_cmp(call_72, (struct String){.str = "b,a", .len = 3}) == 0));
    struct String call_74 = intToString_(1024);
    int call_75 = assert_((str_cmp(call_74, (struct String){.str = "1024", .len = 4}) == 0));
    int call_76 = intParse_((struct String){.str = "1024", .len = 4});
    int call_77 = assert_((call_76 == 1024));
    struct String source_7 = (struct String){.str = "2 + 3\r\n    - 4", .len = 14};
    struct Token_List* call_78 = tokenize_(source_7);
    int call_79 = tokenListPrint_(call_78);
    int call_80 = eval_(source_7);
    int call_81 = assert_((call_80 == ((2 + 3) - 4)));
    int call_82 = eval_((struct String){.str = "2 - 3 * 4 + 5", .len = 13});
    int call_83 = assert_((call_82 == ((2 - (3 * 4)) + 5)));
    return 0;
}
