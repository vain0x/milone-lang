int assert_(int ok_);

int charEq_(char l_, char r_);

int charBetween_(char l_1, char r_1, char c_);

struct CharStringTuple2;

int go_(struct CharStringTuple2 arg_4, int i_);

int strContains_(char c_1, struct String s_);

struct StringStringTuple2;

int go_1(struct StringStringTuple2 arg_5, int i_1);

int strStartsWith_(struct String prefix_, struct String s_1);

struct StringList;

struct String go_2(struct StringList* xs_1);

struct String strConcat_(struct StringList* xs_);

struct StringList* go_3(struct StringList* acc_, struct StringList* xs_4);

struct StringList* strListRev_(struct StringList* xs_3);

struct String digitToString_(int n_);

int digitToInt_(char c_2);

struct String go_4(struct String acc_1, int n_1);

struct String intToString_(int value_);

struct StringIntTuple2;

int go_5(struct StringIntTuple2 arg_6, int acc_2, int i_2);

int intParseCore_(struct String source_, int l_2, int r_2);

int intParse_(struct String source_1);

enum Token_Tag;

struct Token_;

struct Token_List;

struct Token_List* go_6(struct Token_List* acc_3, struct Token_List* xs_7);

struct Token_List* tokenListRev_(struct Token_List* xs_6);

int isDigit_(int arg_7, char c_3);

struct CharBoolFun1;

struct CharBoolFun1StringTuple2;

int go_7(struct CharBoolFun1StringTuple2 arg_9, int r_3);

int takeWhile_(struct CharBoolFun1 pred_, struct StringIntTuple2 arg_8);

struct CharTuple1;

int fun_(void* env_, char arg_);

struct Token_ListIntTuple2;

struct Token_ListIntTuple2 readSpace_(struct String source_3, struct Token_ListIntTuple2 arg_10);

struct Token_ListIntTuple2 readEol_(struct String source_4, struct Token_ListIntTuple2 arg_11);

struct UnitTuple1;

int fun_1(void* env_1, char arg_2);

struct Token_ListIntTuple2 readInt_(struct String source_5, struct Token_ListIntTuple2 arg_12);

struct StringTuple1;

char at_(struct StringTuple1 arg_13, int i_7);

struct Token_List* go_8(struct StringTuple1 arg_14, struct Token_ListIntTuple2 arg_15);

struct Token_List* tokenize_(struct String source_6);

int tokenListPrint_(struct Token_List* tokens_);

struct IntToken_ListTuple2;

struct IntToken_ListTuple2 evalTerm_(struct Token_List* tokens_4);

struct IntToken_ListTuple2 go_9(int acc_8, struct Token_List* tokens_9);

struct IntToken_ListTuple2 evalMul_(struct Token_List* tokens_8);

struct IntToken_ListTuple2 go_10(int acc_9, struct Token_List* tokens_14);

struct IntToken_ListTuple2 evalAdd_(struct Token_List* tokens_13);

struct IntToken_ListTuple2 evalExpr_(struct Token_List* tokens_3);

int eval_(struct String str_);

int main();

int assert_(int ok_) {
    int match_;
    if (!(((!(ok_)) == 1))) goto next_2;
    printf("Assertion failed.\n");
    int call_ = 0;
    exit(1);
    match_ = 0;
    goto end_match_1;
next_2:;
    if (!(((!(ok_)) == 0))) goto next_3;
    match_ = 0;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return 0;
}

int charEq_(char l_, char r_) {
    return (l_ == r_);
}

int charBetween_(char l_1, char r_1, char c_) {
    int match_1;
    if (!(((l_1 <= c_) == 1))) goto next_5;
    match_1 = (c_ <= r_1);
    goto end_match_4;
next_5:;
    if (!(((l_1 <= c_) == 0))) goto next_6;
    match_1 = 0;
    goto end_match_4;
next_6:;
    exit(1);
end_match_4:;
    return match_1;
}

struct CharStringTuple2 {
    char t0;
    struct String t1;
};

int go_(struct CharStringTuple2 arg_4, int i_) {
    char c_1 = arg_4.t0;
    struct String s_ = arg_4.t1;
    int match_2;
    if (!(((i_ < s_.len) == 1))) goto next_8;
    int match_3;
    if (!(((s_.str[i_] == c_1) == 1))) goto next_10;
    match_3 = 1;
    goto end_match_9;
next_10:;
    if (!(((s_.str[i_] == c_1) == 0))) goto next_11;
    struct CharStringTuple2 tuple_;
    tuple_.t0 = c_1;
    tuple_.t1 = s_;
    int call_1 = go_(tuple_, (i_ + 1));
    match_3 = call_1;
    goto end_match_9;
next_11:;
    exit(1);
end_match_9:;
    match_2 = match_3;
    goto end_match_7;
next_8:;
    if (!(((i_ < s_.len) == 0))) goto next_12;
    match_2 = 0;
    goto end_match_7;
next_12:;
    exit(1);
end_match_7:;
    return match_2;
}

int strContains_(char c_1, struct String s_) {
    struct CharStringTuple2 tuple_1;
    tuple_1.t0 = c_1;
    tuple_1.t1 = s_;
    int call_2 = go_(tuple_1, 0);
    return call_2;
}

struct StringStringTuple2 {
    struct String t0;
    struct String t1;
};

int go_1(struct StringStringTuple2 arg_5, int i_1) {
    struct String prefix_ = arg_5.t0;
    struct String s_1 = arg_5.t1;
    int match_4;
    if (!(((prefix_.len <= i_1) == 1))) goto next_14;
    match_4 = 1;
    goto end_match_13;
next_14:;
    if (!(((prefix_.len <= i_1) == 0))) goto next_15;
    int match_5;
    if (!(((s_1.str[i_1] == prefix_.str[i_1]) == 1))) goto next_17;
    struct StringStringTuple2 tuple_2;
    tuple_2.t0 = prefix_;
    tuple_2.t1 = s_1;
    int call_3 = go_1(tuple_2, (i_1 + 1));
    match_5 = call_3;
    goto end_match_16;
next_17:;
    if (!(((s_1.str[i_1] == prefix_.str[i_1]) == 0))) goto next_18;
    match_5 = 0;
    goto end_match_16;
next_18:;
    exit(1);
end_match_16:;
    match_4 = match_5;
    goto end_match_13;
next_15:;
    exit(1);
end_match_13:;
    return match_4;
}

int strStartsWith_(struct String prefix_, struct String s_1) {
    int match_6;
    if (!(((prefix_.len <= s_1.len) == 1))) goto next_20;
    struct StringStringTuple2 tuple_3;
    tuple_3.t0 = prefix_;
    tuple_3.t1 = s_1;
    int call_4 = go_1(tuple_3, 0);
    match_6 = call_4;
    goto end_match_19;
next_20:;
    if (!(((prefix_.len <= s_1.len) == 0))) goto next_21;
    match_6 = 0;
    goto end_match_19;
next_21:;
    exit(1);
end_match_19:;
    return match_6;
}

struct StringList {
    struct String head;
    struct StringList* tail;
};

struct String go_2(struct StringList* xs_1) {
    struct String match_7;
    if (!((!(xs_1)))) goto next_23;
    match_7 = (struct String){.str = "", .len = 0};
    goto end_match_22;
next_23:;
    if (!((!((!(xs_1)))))) goto next_24;
    struct String x_ = xs_1->head;
    struct StringList* xs_2 = xs_1->tail;
    struct String call_5 = go_2(xs_2);
    match_7 = str_add(x_, call_5);
    goto end_match_22;
next_24:;
    exit(1);
end_match_22:;
    return match_7;
}

struct String strConcat_(struct StringList* xs_) {
    struct String call_6 = go_2(xs_);
    return call_6;
}

struct StringList* go_3(struct StringList* acc_, struct StringList* xs_4) {
    struct StringList* match_8;
    if (!((!(xs_4)))) goto next_26;
    match_8 = acc_;
    goto end_match_25;
next_26:;
    if (!((!((!(xs_4)))))) goto next_27;
    struct String x_1 = xs_4->head;
    struct StringList* xs_5 = xs_4->tail;
    struct StringList* list_ = (struct StringList*)malloc(sizeof(struct StringList));
    list_->head = x_1;
    list_->tail = acc_;
    struct StringList* call_7 = go_3(list_, xs_5);
    match_8 = call_7;
    goto end_match_25;
next_27:;
    exit(1);
end_match_25:;
    return match_8;
}

struct StringList* strListRev_(struct StringList* xs_3) {
    struct StringList* call_8 = go_3(NULL, xs_3);
    return call_8;
}

struct String digitToString_(int n_) {
    struct String match_9;
    if (!((n_ == 0))) goto next_29;
    match_9 = (struct String){.str = "0", .len = 1};
    goto end_match_28;
next_29:;
    if (!((n_ == 1))) goto next_30;
    match_9 = (struct String){.str = "1", .len = 1};
    goto end_match_28;
next_30:;
    if (!((n_ == 2))) goto next_31;
    match_9 = (struct String){.str = "2", .len = 1};
    goto end_match_28;
next_31:;
    if (!((n_ == 3))) goto next_32;
    match_9 = (struct String){.str = "3", .len = 1};
    goto end_match_28;
next_32:;
    if (!((n_ == 4))) goto next_33;
    match_9 = (struct String){.str = "4", .len = 1};
    goto end_match_28;
next_33:;
    if (!((n_ == 5))) goto next_34;
    match_9 = (struct String){.str = "5", .len = 1};
    goto end_match_28;
next_34:;
    if (!((n_ == 6))) goto next_35;
    match_9 = (struct String){.str = "6", .len = 1};
    goto end_match_28;
next_35:;
    if (!((n_ == 7))) goto next_36;
    match_9 = (struct String){.str = "7", .len = 1};
    goto end_match_28;
next_36:;
    if (!((n_ == 8))) goto next_37;
    match_9 = (struct String){.str = "8", .len = 1};
    goto end_match_28;
next_37:;
    if (!((n_ == 9))) goto next_38;
    match_9 = (struct String){.str = "9", .len = 1};
    goto end_match_28;
next_38:;
    exit(1);
    match_9 = ((struct String){});
    goto end_match_28;
next_39:;
end_match_28:;
    return match_9;
}

int digitToInt_(char c_2) {
    int match_10;
    if (!((c_2 == '0'))) goto next_41;
    match_10 = 0;
    goto end_match_40;
next_41:;
    if (!((c_2 == '1'))) goto next_42;
    match_10 = 1;
    goto end_match_40;
next_42:;
    if (!((c_2 == '2'))) goto next_43;
    match_10 = 2;
    goto end_match_40;
next_43:;
    if (!((c_2 == '3'))) goto next_44;
    match_10 = 3;
    goto end_match_40;
next_44:;
    if (!((c_2 == '4'))) goto next_45;
    match_10 = 4;
    goto end_match_40;
next_45:;
    if (!((c_2 == '5'))) goto next_46;
    match_10 = 5;
    goto end_match_40;
next_46:;
    if (!((c_2 == '6'))) goto next_47;
    match_10 = 6;
    goto end_match_40;
next_47:;
    if (!((c_2 == '7'))) goto next_48;
    match_10 = 7;
    goto end_match_40;
next_48:;
    if (!((c_2 == '8'))) goto next_49;
    match_10 = 8;
    goto end_match_40;
next_49:;
    if (!((c_2 == '9'))) goto next_50;
    match_10 = 9;
    goto end_match_40;
next_50:;
    exit(1);
    match_10 = 0;
    goto end_match_40;
next_51:;
end_match_40:;
    return match_10;
}

struct String go_4(struct String acc_1, int n_1) {
    struct String match_11;
    if (!(((n_1 <= 0) == 1))) goto next_53;
    match_11 = acc_1;
    goto end_match_52;
next_53:;
    if (!(((n_1 <= 0) == 0))) goto next_54;
    struct String call_9 = digitToString_((n_1 % 10));
    struct String call_10 = go_4(str_add(call_9, acc_1), (n_1 / 10));
    match_11 = call_10;
    goto end_match_52;
next_54:;
    exit(1);
end_match_52:;
    return match_11;
}

struct String intToString_(int value_) {
    struct String match_12;
    if (!(((value_ == 0) == 1))) goto next_56;
    match_12 = (struct String){.str = "0", .len = 1};
    goto end_match_55;
next_56:;
    if (!(((value_ == 0) == 0))) goto next_57;
    struct String call_11 = go_4((struct String){.str = "", .len = 0}, value_);
    match_12 = call_11;
    goto end_match_55;
next_57:;
    exit(1);
end_match_55:;
    return match_12;
}

struct StringIntTuple2 {
    struct String t0;
    int t1;
};

int go_5(struct StringIntTuple2 arg_6, int acc_2, int i_2) {
    struct String source_ = arg_6.t0;
    int r_2 = arg_6.t1;
    int match_13;
    if (!(((r_2 <= i_2) == 1))) goto next_59;
    match_13 = acc_2;
    goto end_match_58;
next_59:;
    if (!(((r_2 <= i_2) == 0))) goto next_60;
    struct StringIntTuple2 tuple_4;
    tuple_4.t0 = source_;
    tuple_4.t1 = r_2;
    int call_12 = digitToInt_(source_.str[i_2]);
    int call_13 = go_5(tuple_4, ((acc_2 * 10) + call_12), (i_2 + 1));
    match_13 = call_13;
    goto end_match_58;
next_60:;
    exit(1);
end_match_58:;
    return match_13;
}

int intParseCore_(struct String source_, int l_2, int r_2) {
    struct StringIntTuple2 tuple_5;
    tuple_5.t0 = source_;
    tuple_5.t1 = r_2;
    int call_14 = go_5(tuple_5, 0, l_2);
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
    struct Token_List* match_14;
    if (!((!(xs_7)))) goto next_62;
    match_14 = acc_3;
    goto end_match_61;
next_62:;
    if (!((!((!(xs_7)))))) goto next_63;
    struct Token_ x_2 = xs_7->head;
    struct Token_List* xs_8 = xs_7->tail;
    struct Token_List* list_1 = (struct Token_List*)malloc(sizeof(struct Token_List));
    list_1->head = x_2;
    list_1->tail = acc_3;
    struct Token_List* call_16 = go_6(list_1, xs_8);
    match_14 = call_16;
    goto end_match_61;
next_63:;
    exit(1);
end_match_61:;
    return match_14;
}

struct Token_List* tokenListRev_(struct Token_List* xs_6) {
    struct Token_List* call_17 = go_6(NULL, xs_6);
    return call_17;
}

int isDigit_(int arg_7, char c_3) {
    int call_18 = charBetween_('0', '9', c_3);
    return call_18;
}

struct CharBoolFun1 {
    int(*fun)(void*, char);
    void* env;
};

struct CharBoolFun1StringTuple2 {
    struct CharBoolFun1 t0;
    struct String t1;
};

int go_7(struct CharBoolFun1StringTuple2 arg_9, int r_3) {
    struct CharBoolFun1 pred_ = arg_9.t0;
    struct String source_2 = arg_9.t1;
    int match_15;
    int match_16;
    if (!(((r_3 < source_2.len) == 1))) goto next_66;
    int app_ = pred_.fun(pred_.env, source_2.str[r_3]);
    match_16 = app_;
    goto end_match_65;
next_66:;
    if (!(((r_3 < source_2.len) == 0))) goto next_67;
    match_16 = 0;
    goto end_match_65;
next_67:;
    exit(1);
end_match_65:;
    if (!((match_16 == 1))) goto next_68;
    struct CharBoolFun1StringTuple2 tuple_6;
    tuple_6.t0 = pred_;
    tuple_6.t1 = source_2;
    int call_19 = go_7(tuple_6, (r_3 + 1));
    match_15 = call_19;
    goto end_match_64;
next_68:;
    if (!((match_16 == 0))) goto next_69;
    match_15 = r_3;
    goto end_match_64;
next_69:;
    exit(1);
end_match_64:;
    return match_15;
}

int takeWhile_(struct CharBoolFun1 pred_, struct StringIntTuple2 arg_8) {
    struct String source_2 = arg_8.t0;
    int i_3 = arg_8.t1;
    struct CharBoolFun1StringTuple2 tuple_7;
    tuple_7.t0 = pred_;
    tuple_7.t1 = source_2;
    int call_20 = go_7(tuple_7, i_3);
    return call_20;
}

struct CharTuple1 {
    char t0;
};

int fun_(void* env_, char arg_) {
    char arg_1 = (*(((struct CharTuple1*)env_))).t0;
    int call_22 = charEq_(arg_1, arg_);
    return call_22;
}

struct Token_ListIntTuple2 {
    struct Token_List* t0;
    int t1;
};

struct Token_ListIntTuple2 readSpace_(struct String source_3, struct Token_ListIntTuple2 arg_10) {
    struct Token_List* acc_4 = arg_10.t0;
    int i_4 = arg_10.t1;
    int call_21 = assert_((source_3.str[i_4] == ' '));
    struct CharTuple1 tuple_8;
    tuple_8.t0 = ' ';
    void* box_ = (void*)malloc(sizeof(struct CharTuple1));
    (*(((struct CharTuple1*)box_))) = tuple_8;
    void* env_2 = box_;
    struct CharBoolFun1 fun_2 = (struct CharBoolFun1){.fun = fun_, .env = env_2};
    struct StringIntTuple2 tuple_9;
    tuple_9.t0 = source_3;
    tuple_9.t1 = (i_4 + 1);
    int call_23 = takeWhile_(fun_2, tuple_9);
    int r_4 = call_23;
    struct Token_ListIntTuple2 tuple_10;
    tuple_10.t0 = acc_4;
    tuple_10.t1 = r_4;
    return tuple_10;
}

struct Token_ListIntTuple2 readEol_(struct String source_4, struct Token_ListIntTuple2 arg_11) {
    struct Token_List* acc_5 = arg_11.t0;
    int i_5 = arg_11.t1;
    int match_17;
    if (!(((source_4.str[i_5] == '\r') == 1))) goto next_71;
    match_17 = 1;
    goto end_match_70;
next_71:;
    if (!(((source_4.str[i_5] == '\r') == 0))) goto next_72;
    match_17 = (source_4.str[i_5] == '\n');
    goto end_match_70;
next_72:;
    exit(1);
end_match_70:;
    int call_24 = assert_(match_17);
    int match_18;
    int match_19;
    int match_20;
    if (!((((i_5 + 1) < source_4.len) == 1))) goto next_76;
    match_20 = (source_4.str[i_5] == '\r');
    goto end_match_75;
next_76:;
    if (!((((i_5 + 1) < source_4.len) == 0))) goto next_77;
    match_20 = 0;
    goto end_match_75;
next_77:;
    exit(1);
end_match_75:;
    if (!((match_20 == 1))) goto next_78;
    match_19 = (source_4.str[(i_5 + 1)] == '\n');
    goto end_match_74;
next_78:;
    if (!((match_20 == 0))) goto next_79;
    match_19 = 0;
    goto end_match_74;
next_79:;
    exit(1);
end_match_74:;
    if (!((match_19 == 1))) goto next_80;
    match_18 = (i_5 + 2);
    goto end_match_73;
next_80:;
    if (!((match_19 == 0))) goto next_81;
    match_18 = (i_5 + 1);
    goto end_match_73;
next_81:;
    exit(1);
end_match_73:;
    int r_5 = match_18;
    struct Token_ListIntTuple2 tuple_11;
    tuple_11.t0 = acc_5;
    tuple_11.t1 = r_5;
    return tuple_11;
}

struct UnitTuple1 {
    int t0;
};

int fun_1(void* env_1, char arg_2) {
    int arg_3 = (*(((struct UnitTuple1*)env_1))).t0;
    int call_27 = isDigit_(0, arg_2);
    return call_27;
}

struct Token_ListIntTuple2 readInt_(struct String source_5, struct Token_ListIntTuple2 arg_12) {
    struct Token_List* acc_6 = arg_12.t0;
    int i_6 = arg_12.t1;
    int call_25 = isDigit_(0, source_5.str[i_6]);
    int call_26 = assert_(call_25);
    struct UnitTuple1 tuple_12;
    tuple_12.t0 = 0;
    void* box_1 = (void*)malloc(sizeof(struct UnitTuple1));
    (*(((struct UnitTuple1*)box_1))) = tuple_12;
    void* env_3 = box_1;
    struct CharBoolFun1 fun_3 = (struct CharBoolFun1){.fun = fun_1, .env = env_3};
    struct StringIntTuple2 tuple_13;
    tuple_13.t0 = source_5;
    tuple_13.t1 = i_6;
    int call_28 = takeWhile_(fun_3, tuple_13);
    int r_6 = call_28;
    int call_29 = intParseCore_(source_5, i_6, r_6);
    int n_2 = call_29;
    struct Token_ variant_ = (struct Token_){.tag = TkInt_, .TkInt_ = n_2};
    struct Token_List* list_2 = (struct Token_List*)malloc(sizeof(struct Token_List));
    list_2->head = variant_;
    list_2->tail = acc_6;
    struct Token_ListIntTuple2 tuple_14;
    tuple_14.t0 = list_2;
    tuple_14.t1 = r_6;
    return tuple_14;
}

struct StringTuple1 {
    struct String t0;
};

char at_(struct StringTuple1 arg_13, int i_7) {
    struct String source_6 = arg_13.t0;
    char match_21;
    if (!(((i_7 < source_6.len) == 1))) goto next_83;
    match_21 = source_6.str[i_7];
    goto end_match_82;
next_83:;
    if (!(((i_7 < source_6.len) == 0))) goto next_84;
    match_21 = '\0';
    goto end_match_82;
next_84:;
    exit(1);
end_match_82:;
    return match_21;
}

struct Token_List* go_8(struct StringTuple1 arg_14, struct Token_ListIntTuple2 arg_15) {
    struct String source_6 = arg_14.t0;
    struct Token_List* acc_7 = arg_15.t0;
    int i_8 = arg_15.t1;
    struct Token_List* match_22;
    if (!(((source_6.len <= i_8) == 1))) goto next_86;
    struct Token_List* call_30 = tokenListRev_(acc_7);
    match_22 = call_30;
    goto end_match_85;
next_86:;
    if (!(((source_6.len <= i_8) == 0))) goto next_87;
    struct Token_List* match_23;
    if (!((source_6.str[i_8] == ' '))) goto next_89;
    struct StringTuple1 tuple_15;
    tuple_15.t0 = source_6;
    struct Token_ListIntTuple2 tuple_16;
    tuple_16.t0 = acc_7;
    tuple_16.t1 = i_8;
    struct Token_ListIntTuple2 call_31 = readSpace_(source_6, tuple_16);
    struct Token_List* call_32 = go_8(tuple_15, call_31);
    match_23 = call_32;
    goto end_match_88;
next_89:;
    if (!((source_6.str[i_8] == '\r'))) goto next_90;
    struct StringTuple1 tuple_17;
    tuple_17.t0 = source_6;
    struct Token_ListIntTuple2 tuple_18;
    tuple_18.t0 = acc_7;
    tuple_18.t1 = i_8;
    struct Token_ListIntTuple2 call_33 = readEol_(source_6, tuple_18);
    struct Token_List* call_34 = go_8(tuple_17, call_33);
    match_23 = call_34;
    goto end_match_88;
next_90:;
    if (!((source_6.str[i_8] == '\n'))) goto next_91;
    struct StringTuple1 tuple_19;
    tuple_19.t0 = source_6;
    struct Token_ListIntTuple2 tuple_20;
    tuple_20.t0 = acc_7;
    tuple_20.t1 = i_8;
    struct Token_ListIntTuple2 call_35 = readEol_(source_6, tuple_20);
    struct Token_List* call_36 = go_8(tuple_19, call_35);
    match_23 = call_36;
    goto end_match_88;
next_91:;
    char c_4 = source_6.str[i_8];
    struct Token_List* match_24;
    int call_37 = isDigit_(0, c_4);
    if (!((call_37 == 1))) goto next_94;
    struct StringTuple1 tuple_21;
    tuple_21.t0 = source_6;
    struct Token_ListIntTuple2 tuple_22;
    tuple_22.t0 = acc_7;
    tuple_22.t1 = i_8;
    struct Token_ListIntTuple2 call_38 = readInt_(source_6, tuple_22);
    struct Token_List* call_39 = go_8(tuple_21, call_38);
    match_24 = call_39;
    goto end_match_93;
next_94:;
    if (!((call_37 == 0))) goto next_95;
    struct StringTuple1 tuple_23;
    tuple_23.t0 = source_6;
    struct Token_ variant_1 = (struct Token_){.tag = TkOp_, .TkOp_ = c_4};
    struct Token_List* list_3 = (struct Token_List*)malloc(sizeof(struct Token_List));
    list_3->head = variant_1;
    list_3->tail = acc_7;
    struct Token_ListIntTuple2 tuple_24;
    tuple_24.t0 = list_3;
    tuple_24.t1 = (i_8 + 1);
    struct Token_List* call_40 = go_8(tuple_23, tuple_24);
    match_24 = call_40;
    goto end_match_93;
next_95:;
    exit(1);
end_match_93:;
    match_23 = match_24;
    goto end_match_88;
next_92:;
end_match_88:;
    match_22 = match_23;
    goto end_match_85;
next_87:;
    exit(1);
end_match_85:;
    return match_22;
}

struct Token_List* tokenize_(struct String source_6) {
    struct StringTuple1 tuple_25;
    tuple_25.t0 = source_6;
    struct Token_ListIntTuple2 tuple_26;
    tuple_26.t0 = NULL;
    tuple_26.t1 = 0;
    struct Token_List* call_41 = go_8(tuple_25, tuple_26);
    return call_41;
}

int tokenListPrint_(struct Token_List* tokens_) {
    int match_25;
    if (!((!(tokens_)))) goto next_97;
    match_25 = 0;
    goto end_match_96;
next_97:;
    if (!((!((!(tokens_)))))) goto next_98;
    if (!((tokens_->head.tag == TkInt_))) goto next_98;
    int n_3 = tokens_->head.TkInt_;
    struct Token_List* tokens_1 = tokens_->tail;
    printf("int %d\n", n_3);
    int call_42 = 0;
    int call_43 = tokenListPrint_(tokens_1);
    match_25 = 0;
    goto end_match_96;
next_98:;
    if (!((!((!(tokens_)))))) goto next_99;
    if (!((tokens_->head.tag == TkOp_))) goto next_99;
    char c_5 = tokens_->head.TkOp_;
    struct Token_List* tokens_2 = tokens_->tail;
    printf("op %c\n", c_5);
    int call_44 = 0;
    int call_45 = tokenListPrint_(tokens_2);
    match_25 = 0;
    goto end_match_96;
next_99:;
    exit(1);
end_match_96:;
    return 0;
}

struct IntToken_ListTuple2 {
    int t0;
    struct Token_List* t1;
};

struct IntToken_ListTuple2 evalTerm_(struct Token_List* tokens_4) {
    struct IntToken_ListTuple2 match_26;
    if (!((!((!(tokens_4)))))) goto next_101;
    if (!((tokens_4->head.tag == TkInt_))) goto next_101;
    int n_4 = tokens_4->head.TkInt_;
    struct Token_List* tokens_5 = tokens_4->tail;
    struct IntToken_ListTuple2 tuple_27;
    tuple_27.t0 = n_4;
    tuple_27.t1 = tokens_5;
    match_26 = tuple_27;
    goto end_match_100;
next_101:;
    if (!((!((!(tokens_4)))))) goto next_102;
    if (!((tokens_4->head.tag == TkOp_))) goto next_102;
    if (!((tokens_4->head.TkOp_ == '('))) goto next_102;
    struct Token_List* tokens_6 = tokens_4->tail;
    struct IntToken_ListTuple2 match_27;
    struct IntToken_ListTuple2 call_46 = evalExpr_(tokens_6);
    int value_1 = call_46.t0;
    if (!((!((!(call_46.t1)))))) goto next_104;
    if (!((call_46.t1->head.tag == TkOp_))) goto next_104;
    if (!((call_46.t1->head.TkOp_ == ')'))) goto next_104;
    struct Token_List* tokens_7 = call_46.t1->tail;
    struct IntToken_ListTuple2 tuple_28;
    tuple_28.t0 = value_1;
    tuple_28.t1 = tokens_7;
    match_27 = tuple_28;
    goto end_match_103;
next_104:;
    printf("expected ')'\n");
    int call_47 = 0;
    exit(1);
    match_27 = ((struct IntToken_ListTuple2){});
    goto end_match_103;
next_105:;
    printf("expected an int\n");
    int call_48 = 0;
    exit(1);
    match_27 = ((struct IntToken_ListTuple2){});
    goto end_match_103;
next_106:;
end_match_103:;
    match_26 = match_27;
    goto end_match_100;
next_102:;
    exit(1);
end_match_100:;
    return match_26;
}

struct IntToken_ListTuple2 go_9(int acc_8, struct Token_List* tokens_9) {
    struct IntToken_ListTuple2 match_28;
    if (!((!((!(tokens_9)))))) goto next_108;
    if (!((tokens_9->head.tag == TkOp_))) goto next_108;
    if (!((tokens_9->head.TkOp_ == '*'))) goto next_108;
    struct Token_List* tokens_10 = tokens_9->tail;
    struct IntToken_ListTuple2 call_49 = evalTerm_(tokens_10);
    int r_7 = call_49.t0;
    struct Token_List* tokens_11 = call_49.t1;
    struct IntToken_ListTuple2 call_50 = go_9((acc_8 * r_7), tokens_11);
    match_28 = call_50;
    goto end_match_107;
next_108:;
    struct IntToken_ListTuple2 tuple_29;
    tuple_29.t0 = acc_8;
    tuple_29.t1 = tokens_9;
    match_28 = tuple_29;
    goto end_match_107;
next_109:;
end_match_107:;
    return match_28;
}

struct IntToken_ListTuple2 evalMul_(struct Token_List* tokens_8) {
    struct IntToken_ListTuple2 call_51 = evalTerm_(tokens_8);
    int l_3 = call_51.t0;
    struct Token_List* tokens_12 = call_51.t1;
    struct IntToken_ListTuple2 call_52 = go_9(l_3, tokens_12);
    return call_52;
}

struct IntToken_ListTuple2 go_10(int acc_9, struct Token_List* tokens_14) {
    struct IntToken_ListTuple2 match_29;
    if (!((!((!(tokens_14)))))) goto next_111;
    if (!((tokens_14->head.tag == TkOp_))) goto next_111;
    if (!((tokens_14->head.TkOp_ == '+'))) goto next_111;
    struct Token_List* tokens_15 = tokens_14->tail;
    struct IntToken_ListTuple2 call_53 = evalMul_(tokens_15);
    int r_8 = call_53.t0;
    struct Token_List* tokens_16 = call_53.t1;
    struct IntToken_ListTuple2 call_54 = go_10((acc_9 + r_8), tokens_16);
    match_29 = call_54;
    goto end_match_110;
next_111:;
    if (!((!((!(tokens_14)))))) goto next_112;
    if (!((tokens_14->head.tag == TkOp_))) goto next_112;
    if (!((tokens_14->head.TkOp_ == '-'))) goto next_112;
    struct Token_List* tokens_17 = tokens_14->tail;
    struct IntToken_ListTuple2 call_55 = evalMul_(tokens_17);
    int r_9 = call_55.t0;
    struct Token_List* tokens_18 = call_55.t1;
    struct IntToken_ListTuple2 call_56 = go_10((acc_9 - r_9), tokens_18);
    match_29 = call_56;
    goto end_match_110;
next_112:;
    struct IntToken_ListTuple2 tuple_30;
    tuple_30.t0 = acc_9;
    tuple_30.t1 = tokens_14;
    match_29 = tuple_30;
    goto end_match_110;
next_113:;
end_match_110:;
    return match_29;
}

struct IntToken_ListTuple2 evalAdd_(struct Token_List* tokens_13) {
    struct IntToken_ListTuple2 call_57 = evalMul_(tokens_13);
    int l_4 = call_57.t0;
    struct Token_List* tokens_19 = call_57.t1;
    struct IntToken_ListTuple2 call_58 = go_10(l_4, tokens_19);
    return call_58;
}

struct IntToken_ListTuple2 evalExpr_(struct Token_List* tokens_3) {
    struct IntToken_ListTuple2 call_59 = evalAdd_(tokens_3);
    return call_59;
}

int eval_(struct String str_) {
    int match_30;
    struct Token_List* call_60 = tokenize_(str_);
    struct IntToken_ListTuple2 call_61 = evalExpr_(call_60);
    int value_2 = call_61.t0;
    if (!((!(call_61.t1)))) goto next_115;
    match_30 = value_2;
    goto end_match_114;
next_115:;
    struct Token_List* tokens_20 = call_61.t1;
    printf("ERROR: couldn't parse tokens:\n");
    int call_62 = 0;
    int call_63 = tokenListPrint_(tokens_20);
    exit(1);
    match_30 = 0;
    goto end_match_114;
next_116:;
end_match_114:;
    return match_30;
}

int main() {
    int call_64 = strContains_('+', (struct String){.str = "+-*/", .len = 4});
    int call_65 = assert_(call_64);
    int call_66 = strStartsWith_((struct String){.str = "hell", .len = 4}, (struct String){.str = "hello", .len = 5});
    int call_67 = assert_(call_66);
    int call_68 = strStartsWith_((struct String){.str = "heaven", .len = 6}, (struct String){.str = "hello", .len = 5});
    int call_69 = assert_((!(call_68)));
    struct StringList* list_6 = (struct StringList*)malloc(sizeof(struct StringList));
    list_6->head = (struct String){.str = "b", .len = 1};
    list_6->tail = NULL;
    struct StringList* list_5 = (struct StringList*)malloc(sizeof(struct StringList));
    list_5->head = (struct String){.str = ",", .len = 1};
    list_5->tail = list_6;
    struct StringList* list_4 = (struct StringList*)malloc(sizeof(struct StringList));
    list_4->head = (struct String){.str = "a", .len = 1};
    list_4->tail = list_5;
    struct String call_70 = strConcat_(list_4);
    int call_71 = assert_((str_cmp(call_70, (struct String){.str = "a,b", .len = 3}) == 0));
    struct StringList* list_9 = (struct StringList*)malloc(sizeof(struct StringList));
    list_9->head = (struct String){.str = "b", .len = 1};
    list_9->tail = NULL;
    struct StringList* list_8 = (struct StringList*)malloc(sizeof(struct StringList));
    list_8->head = (struct String){.str = ",", .len = 1};
    list_8->tail = list_9;
    struct StringList* list_7 = (struct StringList*)malloc(sizeof(struct StringList));
    list_7->head = (struct String){.str = "a", .len = 1};
    list_7->tail = list_8;
    struct StringList* call_72 = strListRev_(list_7);
    struct String call_73 = strConcat_(call_72);
    int call_74 = assert_((str_cmp(call_73, (struct String){.str = "b,a", .len = 3}) == 0));
    struct String call_75 = intToString_(1024);
    int call_76 = assert_((str_cmp(call_75, (struct String){.str = "1024", .len = 4}) == 0));
    int call_77 = intParse_((struct String){.str = "1024", .len = 4});
    int call_78 = assert_((call_77 == 1024));
    struct String source_7 = (struct String){.str = "2 + 3\r\n    - 4", .len = 14};
    struct Token_List* call_79 = tokenize_(source_7);
    int call_80 = tokenListPrint_(call_79);
    int call_81 = eval_(source_7);
    int call_82 = assert_((call_81 == ((2 + 3) - 4)));
    int call_83 = eval_((struct String){.str = "2 - 3 * 4 + 5", .len = 13});
    int call_84 = assert_((call_83 == ((2 - (3 * 4)) + 5)));
    int call_85 = eval_((struct String){.str = "(2 - 3) * 4 + (1 + (2 + 2))", .len = 27});
    int call_86 = assert_((call_85 == (((2 - 3) * 4) + (1 + (2 + 2)))));
    return 0;
}
