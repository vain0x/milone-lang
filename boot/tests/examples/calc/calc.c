int assert_(int ok_);

int charEq_(char l_, char r_);

struct CharStringTuple2;

int go_(struct CharStringTuple2 arg_3, int i_);

int strContains_(char c_, struct String s_);

struct StringStringTuple2;

int go_1(struct StringStringTuple2 arg_4, int i_1);

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

struct CharBoolFun1StringTuple2;

int go_5(struct CharBoolFun1StringTuple2 arg_6, int r_1);

struct StringIntTuple2;

int takeWhile_(struct CharBoolFun1 pred_, struct StringIntTuple2 arg_5);

struct CharTuple1;

int fun_(void* env_, char arg_);

struct Token_ListIntTuple2;

struct Token_ListIntTuple2 readSpace_(struct String source_1, struct Token_ListIntTuple2 arg_7);

struct Token_ListIntTuple2 readEol_(struct String source_2, struct Token_ListIntTuple2 arg_8);

int fun_1(void* env_1, char arg_2);

struct Token_ListIntTuple2 readInt_(struct String source_3, struct Token_ListIntTuple2 arg_9);

struct StringTuple1;

char at_(struct StringTuple1 arg_10, int i_6);

struct Token_List* go_6(struct StringTuple1 arg_11, struct Token_ListIntTuple2 arg_12);

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

struct CharStringTuple2 {
    char t0;
    struct String t1;
};

int go_(struct CharStringTuple2 arg_3, int i_) {
    char c_ = arg_3.t0;
    struct String s_ = arg_3.t1;
    int match_1;
    if (!(((i_ < s_.len) == 1))) goto next_5;
    int match_2;
    if (!(((s_.str[i_] == c_) == 1))) goto next_8;
    match_2 = 1;
    goto end_match_7;
next_8:;
    if (!(((s_.str[i_] == c_) == 0))) goto next_9;
    struct CharStringTuple2 tuple_;
    tuple_.t0 = c_;
    tuple_.t1 = s_;
    int call_1 = go_(tuple_, (i_ + 1));
    match_2 = call_1;
    goto end_match_7;
next_9:;
    exit(1);
end_match_7:;
    match_1 = match_2;
    goto end_match_4;
next_5:;
    if (!(((i_ < s_.len) == 0))) goto next_6;
    match_1 = 0;
    goto end_match_4;
next_6:;
    exit(1);
end_match_4:;
    return match_1;
}

int strContains_(char c_, struct String s_) {
    struct CharStringTuple2 tuple_1;
    tuple_1.t0 = c_;
    tuple_1.t1 = s_;
    int call_2 = go_(tuple_1, 0);
    return call_2;
}

struct StringStringTuple2 {
    struct String t0;
    struct String t1;
};

int go_1(struct StringStringTuple2 arg_4, int i_1) {
    struct String prefix_ = arg_4.t0;
    struct String s_1 = arg_4.t1;
    int match_3;
    if (!(((prefix_.len <= i_1) == 1))) goto next_11;
    match_3 = 1;
    goto end_match_10;
next_11:;
    if (!(((prefix_.len <= i_1) == 0))) goto next_12;
    int match_4;
    if (!(((s_1.str[i_1] == prefix_.str[i_1]) == 1))) goto next_14;
    struct StringStringTuple2 tuple_2;
    tuple_2.t0 = prefix_;
    tuple_2.t1 = s_1;
    int call_3 = go_1(tuple_2, (i_1 + 1));
    match_4 = call_3;
    goto end_match_13;
next_14:;
    if (!(((s_1.str[i_1] == prefix_.str[i_1]) == 0))) goto next_15;
    match_4 = 0;
    goto end_match_13;
next_15:;
    exit(1);
end_match_13:;
    match_3 = match_4;
    goto end_match_10;
next_12:;
    exit(1);
end_match_10:;
    return match_3;
}

int strStartsWith_(struct String prefix_, struct String s_1) {
    int match_5;
    if (!(((prefix_.len <= s_1.len) == 1))) goto next_17;
    struct StringStringTuple2 tuple_3;
    tuple_3.t0 = prefix_;
    tuple_3.t1 = s_1;
    int call_4 = go_1(tuple_3, 0);
    match_5 = call_4;
    goto end_match_16;
next_17:;
    if (!(((prefix_.len <= s_1.len) == 0))) goto next_18;
    match_5 = 0;
    goto end_match_16;
next_18:;
    exit(1);
end_match_16:;
    return match_5;
}

struct StringList {
    struct String head;
    struct StringList* tail;
};

struct String go_2(struct StringList* xs_1) {
    struct String match_6;
    if (!((!(xs_1)))) goto next_20;
    match_6 = (struct String){.str = "", .len = 0};
    goto end_match_19;
next_20:;
    if (!((!((!(xs_1)))))) goto next_21;
    struct String x_ = xs_1->head;
    struct StringList* xs_2 = xs_1->tail;
    struct String call_5 = go_2(xs_2);
    match_6 = str_add(x_, call_5);
    goto end_match_19;
next_21:;
    exit(1);
end_match_19:;
    return match_6;
}

struct String strConcat_(struct StringList* xs_) {
    struct String call_6 = go_2(xs_);
    return call_6;
}

struct StringList* go_3(struct StringList* acc_, struct StringList* xs_4) {
    struct StringList* match_7;
    if (!((!(xs_4)))) goto next_23;
    match_7 = acc_;
    goto end_match_22;
next_23:;
    if (!((!((!(xs_4)))))) goto next_24;
    struct String x_1 = xs_4->head;
    struct StringList* xs_5 = xs_4->tail;
    struct StringList* list_ = (struct StringList*)malloc(sizeof(struct StringList));
    list_->head = x_1;
    list_->tail = acc_;
    struct StringList* call_7 = go_3(list_, xs_5);
    match_7 = call_7;
    goto end_match_22;
next_24:;
    exit(1);
end_match_22:;
    return match_7;
}

struct StringList* strListRev_(struct StringList* xs_3) {
    struct StringList* call_8 = go_3(NULL, xs_3);
    return call_8;
}

enum Token_Tag {
    TkInt_,
    TkOp_,
};

struct Token_ {
    enum Token_Tag tag;
    union {
        int* TkInt_;
        char* TkOp_;
    };
};

struct Token_List {
    struct Token_ head;
    struct Token_List* tail;
};

struct Token_List* go_4(struct Token_List* acc_1, struct Token_List* xs_7) {
    struct Token_List* match_8;
    if (!((!(xs_7)))) goto next_26;
    match_8 = acc_1;
    goto end_match_25;
next_26:;
    if (!((!((!(xs_7)))))) goto next_27;
    struct Token_ x_2 = xs_7->head;
    struct Token_List* xs_8 = xs_7->tail;
    struct Token_List* list_1 = (struct Token_List*)malloc(sizeof(struct Token_List));
    list_1->head = x_2;
    list_1->tail = acc_1;
    struct Token_List* call_9 = go_4(list_1, xs_8);
    match_8 = call_9;
    goto end_match_25;
next_27:;
    exit(1);
end_match_25:;
    return match_8;
}

struct Token_List* tokenListRev_(struct Token_List* xs_6) {
    struct Token_List* call_10 = go_4(NULL, xs_6);
    return call_10;
}

int isDigit_(char c_1) {
    int match_9;
    if (!((('0' <= c_1) == 1))) goto next_29;
    match_9 = (c_1 <= '9');
    goto end_match_28;
next_29:;
    if (!((('0' <= c_1) == 0))) goto next_30;
    match_9 = 0;
    goto end_match_28;
next_30:;
    exit(1);
end_match_28:;
    return match_9;
}

struct CharBoolFun1 {
    int(*fun)(void*, char);
    void* env;
};

struct CharBoolFun1StringTuple2 {
    struct CharBoolFun1 t0;
    struct String t1;
};

int go_5(struct CharBoolFun1StringTuple2 arg_6, int r_1) {
    struct CharBoolFun1 pred_ = arg_6.t0;
    struct String source_ = arg_6.t1;
    int match_10;
    int match_11;
    if (!(((r_1 < source_.len) == 1))) goto next_33;
    int app_ = pred_.fun(pred_.env, source_.str[r_1]);
    match_11 = app_;
    goto end_match_32;
next_33:;
    if (!(((r_1 < source_.len) == 0))) goto next_34;
    match_11 = 0;
    goto end_match_32;
next_34:;
    exit(1);
end_match_32:;
    if (!((match_11 == 1))) goto next_35;
    struct CharBoolFun1StringTuple2 tuple_4;
    tuple_4.t0 = pred_;
    tuple_4.t1 = source_;
    int call_11 = go_5(tuple_4, (r_1 + 1));
    match_10 = call_11;
    goto end_match_31;
next_35:;
    if (!((match_11 == 0))) goto next_36;
    match_10 = r_1;
    goto end_match_31;
next_36:;
    exit(1);
end_match_31:;
    return match_10;
}

struct StringIntTuple2 {
    struct String t0;
    int t1;
};

int takeWhile_(struct CharBoolFun1 pred_, struct StringIntTuple2 arg_5) {
    struct String source_ = arg_5.t0;
    int i_2 = arg_5.t1;
    struct CharBoolFun1StringTuple2 tuple_5;
    tuple_5.t0 = pred_;
    tuple_5.t1 = source_;
    int call_12 = go_5(tuple_5, i_2);
    return call_12;
}

struct CharTuple1 {
    char t0;
};

int fun_(void* env_, char arg_) {
    char arg_1 = (*(((struct CharTuple1*)env_))).t0;
    int call_14 = charEq_(arg_1, arg_);
    return call_14;
}

struct Token_ListIntTuple2 {
    struct Token_List* t0;
    int t1;
};

struct Token_ListIntTuple2 readSpace_(struct String source_1, struct Token_ListIntTuple2 arg_7) {
    struct Token_List* acc_2 = arg_7.t0;
    int i_3 = arg_7.t1;
    int call_13 = assert_((source_1.str[i_3] == ' '));
    struct CharTuple1 tuple_6;
    tuple_6.t0 = ' ';
    void* box_ = (void*)malloc(sizeof(struct CharTuple1));
    (*(((struct CharTuple1*)box_))) = tuple_6;
    void* env_2 = box_;
    struct CharBoolFun1 fun_2 = (struct CharBoolFun1){.fun = fun_, .env = env_2};
    struct StringIntTuple2 tuple_7;
    tuple_7.t0 = source_1;
    tuple_7.t1 = (i_3 + 1);
    int call_15 = takeWhile_(fun_2, tuple_7);
    int r_2 = call_15;
    struct Token_ListIntTuple2 tuple_8;
    tuple_8.t0 = acc_2;
    tuple_8.t1 = r_2;
    return tuple_8;
}

struct Token_ListIntTuple2 readEol_(struct String source_2, struct Token_ListIntTuple2 arg_8) {
    struct Token_List* acc_3 = arg_8.t0;
    int i_4 = arg_8.t1;
    int match_12;
    if (!(((source_2.str[i_4] == '\r') == 1))) goto next_38;
    match_12 = 1;
    goto end_match_37;
next_38:;
    if (!(((source_2.str[i_4] == '\r') == 0))) goto next_39;
    match_12 = (source_2.str[i_4] == '\n');
    goto end_match_37;
next_39:;
    exit(1);
end_match_37:;
    int call_16 = assert_(match_12);
    int match_13;
    int match_14;
    int match_15;
    if (!((((i_4 + 1) < source_2.len) == 1))) goto next_43;
    match_15 = (source_2.str[i_4] == '\r');
    goto end_match_42;
next_43:;
    if (!((((i_4 + 1) < source_2.len) == 0))) goto next_44;
    match_15 = 0;
    goto end_match_42;
next_44:;
    exit(1);
end_match_42:;
    if (!((match_15 == 1))) goto next_45;
    match_14 = (source_2.str[(i_4 + 1)] == '\n');
    goto end_match_41;
next_45:;
    if (!((match_15 == 0))) goto next_46;
    match_14 = 0;
    goto end_match_41;
next_46:;
    exit(1);
end_match_41:;
    if (!((match_14 == 1))) goto next_47;
    match_13 = (i_4 + 2);
    goto end_match_40;
next_47:;
    if (!((match_14 == 0))) goto next_48;
    match_13 = (i_4 + 1);
    goto end_match_40;
next_48:;
    exit(1);
end_match_40:;
    int r_3 = match_13;
    struct Token_ListIntTuple2 tuple_9;
    tuple_9.t0 = acc_3;
    tuple_9.t1 = r_3;
    return tuple_9;
}

int fun_1(void* env_1, char arg_2) {
    int call_19 = isDigit_(arg_2);
    return call_19;
}

struct Token_ListIntTuple2 readInt_(struct String source_3, struct Token_ListIntTuple2 arg_9) {
    struct Token_List* acc_4 = arg_9.t0;
    int i_5 = arg_9.t1;
    int call_17 = isDigit_(source_3.str[i_5]);
    int call_18 = assert_(call_17);
    void* box_1 = (void*)malloc(sizeof(int));
    (*(((int*)box_1))) = 0;
    void* env_3 = box_1;
    struct CharBoolFun1 fun_3 = (struct CharBoolFun1){.fun = fun_1, .env = env_3};
    struct StringIntTuple2 tuple_10;
    tuple_10.t0 = source_3;
    tuple_10.t1 = i_5;
    int call_20 = takeWhile_(fun_3, tuple_10);
    int r_4 = call_20;
    struct String slice_ = str_slice(source_3, i_5, (r_4 - 1));
    int call_21 = str_to_int(slice_);
    int n_ = call_21;
    int* payload_ = (int*)malloc(sizeof(int));
    (*(((int*)payload_))) = n_;
    struct Token_ variant_ = (struct Token_){.tag = TkInt_, .TkInt_ = payload_};
    struct Token_List* list_2 = (struct Token_List*)malloc(sizeof(struct Token_List));
    list_2->head = variant_;
    list_2->tail = acc_4;
    struct Token_ListIntTuple2 tuple_11;
    tuple_11.t0 = list_2;
    tuple_11.t1 = r_4;
    return tuple_11;
}

struct StringTuple1 {
    struct String t0;
};

char at_(struct StringTuple1 arg_10, int i_6) {
    struct String source_4 = arg_10.t0;
    char match_16;
    if (!(((i_6 < source_4.len) == 1))) goto next_50;
    match_16 = source_4.str[i_6];
    goto end_match_49;
next_50:;
    if (!(((i_6 < source_4.len) == 0))) goto next_51;
    match_16 = '\0';
    goto end_match_49;
next_51:;
    exit(1);
end_match_49:;
    return match_16;
}

struct Token_List* go_6(struct StringTuple1 arg_11, struct Token_ListIntTuple2 arg_12) {
    struct String source_4 = arg_11.t0;
    struct Token_List* acc_5 = arg_12.t0;
    int i_7 = arg_12.t1;
    struct Token_List* match_17;
    if (!(((source_4.len <= i_7) == 1))) goto next_53;
    struct Token_List* call_22 = tokenListRev_(acc_5);
    match_17 = call_22;
    goto end_match_52;
next_53:;
    if (!(((source_4.len <= i_7) == 0))) goto next_54;
    struct Token_List* match_18;
    if (!((source_4.str[i_7] == ' '))) goto next_56;
    struct StringTuple1 tuple_12;
    tuple_12.t0 = source_4;
    struct Token_ListIntTuple2 tuple_13;
    tuple_13.t0 = acc_5;
    tuple_13.t1 = i_7;
    struct Token_ListIntTuple2 call_23 = readSpace_(source_4, tuple_13);
    struct Token_List* call_24 = go_6(tuple_12, call_23);
    match_18 = call_24;
    goto end_match_55;
next_56:;
    if (!((source_4.str[i_7] == '\r'))) goto next_57;
    struct StringTuple1 tuple_14;
    tuple_14.t0 = source_4;
    struct Token_ListIntTuple2 tuple_15;
    tuple_15.t0 = acc_5;
    tuple_15.t1 = i_7;
    struct Token_ListIntTuple2 call_25 = readEol_(source_4, tuple_15);
    struct Token_List* call_26 = go_6(tuple_14, call_25);
    match_18 = call_26;
    goto end_match_55;
next_57:;
    if (!((source_4.str[i_7] == '\n'))) goto next_58;
    struct StringTuple1 tuple_16;
    tuple_16.t0 = source_4;
    struct Token_ListIntTuple2 tuple_17;
    tuple_17.t0 = acc_5;
    tuple_17.t1 = i_7;
    struct Token_ListIntTuple2 call_27 = readEol_(source_4, tuple_17);
    struct Token_List* call_28 = go_6(tuple_16, call_27);
    match_18 = call_28;
    goto end_match_55;
next_58:;
    char c_2 = source_4.str[i_7];
    struct Token_List* match_19;
    int call_29 = isDigit_(c_2);
    if (!((call_29 == 1))) goto next_61;
    struct StringTuple1 tuple_18;
    tuple_18.t0 = source_4;
    struct Token_ListIntTuple2 tuple_19;
    tuple_19.t0 = acc_5;
    tuple_19.t1 = i_7;
    struct Token_ListIntTuple2 call_30 = readInt_(source_4, tuple_19);
    struct Token_List* call_31 = go_6(tuple_18, call_30);
    match_19 = call_31;
    goto end_match_60;
next_61:;
    if (!((call_29 == 0))) goto next_62;
    struct StringTuple1 tuple_20;
    tuple_20.t0 = source_4;
    char* payload_1 = (char*)malloc(sizeof(char));
    (*(((char*)payload_1))) = c_2;
    struct Token_ variant_1 = (struct Token_){.tag = TkOp_, .TkOp_ = payload_1};
    struct Token_List* list_3 = (struct Token_List*)malloc(sizeof(struct Token_List));
    list_3->head = variant_1;
    list_3->tail = acc_5;
    struct Token_ListIntTuple2 tuple_21;
    tuple_21.t0 = list_3;
    tuple_21.t1 = (i_7 + 1);
    struct Token_List* call_32 = go_6(tuple_20, tuple_21);
    match_19 = call_32;
    goto end_match_60;
next_62:;
    exit(1);
end_match_60:;
    match_18 = match_19;
    goto end_match_55;
next_59:;
end_match_55:;
    match_17 = match_18;
    goto end_match_52;
next_54:;
    exit(1);
end_match_52:;
    return match_17;
}

struct Token_List* tokenize_(struct String source_4) {
    struct StringTuple1 tuple_22;
    tuple_22.t0 = source_4;
    struct Token_ListIntTuple2 tuple_23;
    tuple_23.t0 = NULL;
    tuple_23.t1 = 0;
    struct Token_List* call_33 = go_6(tuple_22, tuple_23);
    return call_33;
}

int tokenListPrint_(struct Token_List* tokens_) {
    int match_20;
    if (!((!(tokens_)))) goto next_64;
    match_20 = 0;
    goto end_match_63;
next_64:;
    if (!((!((!(tokens_)))))) goto next_65;
    if (!((tokens_->head.tag == TkInt_))) goto next_65;
    int n_1 = (*(tokens_->head.TkInt_));
    struct Token_List* tokens_1 = tokens_->tail;
    printf("int %d\n", n_1);
    int call_34 = 0;
    int call_35 = tokenListPrint_(tokens_1);
    match_20 = 0;
    goto end_match_63;
next_65:;
    if (!((!((!(tokens_)))))) goto next_66;
    if (!((tokens_->head.tag == TkOp_))) goto next_66;
    char c_3 = (*(tokens_->head.TkOp_));
    struct Token_List* tokens_2 = tokens_->tail;
    printf("op %c\n", c_3);
    int call_36 = 0;
    int call_37 = tokenListPrint_(tokens_2);
    match_20 = 0;
    goto end_match_63;
next_66:;
    exit(1);
end_match_63:;
    return 0;
}

struct IntToken_ListTuple2 {
    int t0;
    struct Token_List* t1;
};

struct IntToken_ListTuple2 evalTerm_(struct Token_List* tokens_4) {
    struct IntToken_ListTuple2 match_21;
    if (!((!((!(tokens_4)))))) goto next_68;
    if (!((tokens_4->head.tag == TkInt_))) goto next_68;
    int n_2 = (*(tokens_4->head.TkInt_));
    struct Token_List* tokens_5 = tokens_4->tail;
    struct IntToken_ListTuple2 tuple_24;
    tuple_24.t0 = n_2;
    tuple_24.t1 = tokens_5;
    match_21 = tuple_24;
    goto end_match_67;
next_68:;
    if (!((!((!(tokens_4)))))) goto next_69;
    if (!((tokens_4->head.tag == TkOp_))) goto next_69;
    if (!(((*(tokens_4->head.TkOp_)) == '('))) goto next_69;
    struct Token_List* tokens_6 = tokens_4->tail;
    struct IntToken_ListTuple2 match_22;
    struct IntToken_ListTuple2 call_38 = evalExpr_(tokens_6);
    int value_ = call_38.t0;
    if (!((!((!(call_38.t1)))))) goto next_72;
    if (!((call_38.t1->head.tag == TkOp_))) goto next_72;
    if (!(((*(call_38.t1->head.TkOp_)) == ')'))) goto next_72;
    struct Token_List* tokens_7 = call_38.t1->tail;
    struct IntToken_ListTuple2 tuple_25;
    tuple_25.t0 = value_;
    tuple_25.t1 = tokens_7;
    match_22 = tuple_25;
    goto end_match_71;
next_72:;
    printf("expected ')'\n");
    int call_39 = 0;
    exit(1);
    match_22 = ((struct IntToken_ListTuple2){});
    goto end_match_71;
next_73:;
end_match_71:;
    match_21 = match_22;
    goto end_match_67;
next_69:;
    printf("expected an int\n");
    int call_40 = 0;
    exit(1);
    match_21 = ((struct IntToken_ListTuple2){});
    goto end_match_67;
next_70:;
end_match_67:;
    return match_21;
}

struct IntToken_ListTuple2 go_7(int acc_6, struct Token_List* tokens_9) {
    struct IntToken_ListTuple2 match_23;
    if (!((!((!(tokens_9)))))) goto next_75;
    if (!((tokens_9->head.tag == TkOp_))) goto next_75;
    if (!(((*(tokens_9->head.TkOp_)) == '*'))) goto next_75;
    struct Token_List* tokens_10 = tokens_9->tail;
    struct IntToken_ListTuple2 call_41 = evalTerm_(tokens_10);
    int r_5 = call_41.t0;
    struct Token_List* tokens_11 = call_41.t1;
    struct IntToken_ListTuple2 call_42 = go_7((acc_6 * r_5), tokens_11);
    match_23 = call_42;
    goto end_match_74;
next_75:;
    struct IntToken_ListTuple2 tuple_26;
    tuple_26.t0 = acc_6;
    tuple_26.t1 = tokens_9;
    match_23 = tuple_26;
    goto end_match_74;
next_76:;
end_match_74:;
    return match_23;
}

struct IntToken_ListTuple2 evalMul_(struct Token_List* tokens_8) {
    struct IntToken_ListTuple2 call_43 = evalTerm_(tokens_8);
    int l_1 = call_43.t0;
    struct Token_List* tokens_12 = call_43.t1;
    struct IntToken_ListTuple2 call_44 = go_7(l_1, tokens_12);
    return call_44;
}

struct IntToken_ListTuple2 go_8(int acc_7, struct Token_List* tokens_14) {
    struct IntToken_ListTuple2 match_24;
    if (!((!((!(tokens_14)))))) goto next_78;
    if (!((tokens_14->head.tag == TkOp_))) goto next_78;
    if (!(((*(tokens_14->head.TkOp_)) == '+'))) goto next_78;
    struct Token_List* tokens_15 = tokens_14->tail;
    struct IntToken_ListTuple2 call_45 = evalMul_(tokens_15);
    int r_6 = call_45.t0;
    struct Token_List* tokens_16 = call_45.t1;
    struct IntToken_ListTuple2 call_46 = go_8((acc_7 + r_6), tokens_16);
    match_24 = call_46;
    goto end_match_77;
next_78:;
    if (!((!((!(tokens_14)))))) goto next_79;
    if (!((tokens_14->head.tag == TkOp_))) goto next_79;
    if (!(((*(tokens_14->head.TkOp_)) == '-'))) goto next_79;
    struct Token_List* tokens_17 = tokens_14->tail;
    struct IntToken_ListTuple2 call_47 = evalMul_(tokens_17);
    int r_7 = call_47.t0;
    struct Token_List* tokens_18 = call_47.t1;
    struct IntToken_ListTuple2 call_48 = go_8((acc_7 - r_7), tokens_18);
    match_24 = call_48;
    goto end_match_77;
next_79:;
    struct IntToken_ListTuple2 tuple_27;
    tuple_27.t0 = acc_7;
    tuple_27.t1 = tokens_14;
    match_24 = tuple_27;
    goto end_match_77;
next_80:;
end_match_77:;
    return match_24;
}

struct IntToken_ListTuple2 evalAdd_(struct Token_List* tokens_13) {
    struct IntToken_ListTuple2 call_49 = evalMul_(tokens_13);
    int l_2 = call_49.t0;
    struct Token_List* tokens_19 = call_49.t1;
    struct IntToken_ListTuple2 call_50 = go_8(l_2, tokens_19);
    return call_50;
}

struct IntToken_ListTuple2 evalExpr_(struct Token_List* tokens_3) {
    struct IntToken_ListTuple2 call_51 = evalAdd_(tokens_3);
    return call_51;
}

int eval_(struct String str_) {
    int match_25;
    struct Token_List* call_52 = tokenize_(str_);
    struct IntToken_ListTuple2 call_53 = evalExpr_(call_52);
    int value_1 = call_53.t0;
    if (!((!(call_53.t1)))) goto next_82;
    match_25 = value_1;
    goto end_match_81;
next_82:;
    struct Token_List* tokens_20 = call_53.t1;
    printf("ERROR: couldn't parse tokens:\n");
    int call_54 = 0;
    int call_55 = tokenListPrint_(tokens_20);
    exit(1);
    match_25 = 0;
    goto end_match_81;
next_83:;
end_match_81:;
    return match_25;
}

int main() {
    int call_56 = strContains_('+', (struct String){.str = "+-*/", .len = 4});
    int call_57 = assert_(call_56);
    int call_58 = strStartsWith_((struct String){.str = "hell", .len = 4}, (struct String){.str = "hello", .len = 5});
    int call_59 = assert_(call_58);
    int call_60 = strStartsWith_((struct String){.str = "heaven", .len = 6}, (struct String){.str = "hello", .len = 5});
    int call_61 = assert_((!(call_60)));
    struct StringList* list_6 = (struct StringList*)malloc(sizeof(struct StringList));
    list_6->head = (struct String){.str = "b", .len = 1};
    list_6->tail = NULL;
    struct StringList* list_5 = (struct StringList*)malloc(sizeof(struct StringList));
    list_5->head = (struct String){.str = ",", .len = 1};
    list_5->tail = list_6;
    struct StringList* list_4 = (struct StringList*)malloc(sizeof(struct StringList));
    list_4->head = (struct String){.str = "a", .len = 1};
    list_4->tail = list_5;
    struct String call_62 = strConcat_(list_4);
    int call_63 = assert_((str_cmp(call_62, (struct String){.str = "a,b", .len = 3}) == 0));
    struct StringList* list_9 = (struct StringList*)malloc(sizeof(struct StringList));
    list_9->head = (struct String){.str = "b", .len = 1};
    list_9->tail = NULL;
    struct StringList* list_8 = (struct StringList*)malloc(sizeof(struct StringList));
    list_8->head = (struct String){.str = ",", .len = 1};
    list_8->tail = list_9;
    struct StringList* list_7 = (struct StringList*)malloc(sizeof(struct StringList));
    list_7->head = (struct String){.str = "a", .len = 1};
    list_7->tail = list_8;
    struct StringList* call_64 = strListRev_(list_7);
    struct String call_65 = strConcat_(call_64);
    int call_66 = assert_((str_cmp(call_65, (struct String){.str = "b,a", .len = 3}) == 0));
    struct String source_5 = (struct String){.str = "2 + 3\r\n    - 4", .len = 14};
    struct Token_List* call_67 = tokenize_(source_5);
    int call_68 = tokenListPrint_(call_67);
    int call_69 = eval_(source_5);
    int call_70 = assert_((call_69 == ((2 + 3) - 4)));
    int call_71 = eval_((struct String){.str = "2 - 3 * 4 + 5", .len = 13});
    int call_72 = assert_((call_71 == ((2 - (3 * 4)) + 5)));
    int call_73 = eval_((struct String){.str = "(2 - 3) * 4 + (1 + (2 + 2))", .len = 27});
    int call_74 = assert_((call_73 == (((2 - 3) * 4) + (1 + (2 + 2)))));
    return 0;
}
