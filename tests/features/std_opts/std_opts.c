#include "milone.h"

struct IntStringTuple2;

struct StringList;

struct IntStringTuple2StringIntStringTuple2Fun2;

struct PropName_;

struct StringList;

struct Msg_;

struct StringOption;

struct PropName_StringOptionTuple2;

struct StringBoolFun1;

struct StringBoolFun1Tuple1;

struct PropName_StringListBoolFun2;

struct Msg_StringListStringListFun2;

struct Result_;

struct StringListResult_Tuple2;

struct PropName_StringTuple2;

struct StringStringTuple2;

struct StringListStringStringListFun2;

struct StringStringTuple2List;

struct Opts_;

struct StringListStringStringTuple2StringListFun2;

struct String MiloneStd_StdString_replace(struct String, struct String, struct String);

struct IntStringTuple2 fun_15(struct IntStringTuple2 arg_194, struct String arg_5);

struct IntStringTuple2 fun_47(void const* env_26, struct IntStringTuple2 arg_71, struct String arg_72);

struct IntStringTuple2 fold_2(struct IntStringTuple2StringIntStringTuple2Fun2, struct IntStringTuple2, struct StringList const*);

struct String std_opts_Program_format(struct String s_20, struct StringList const* args_15);

struct String ofName_(struct PropName_ name_12);

struct StringList const* myUpdate_(struct Msg_ msg_1, struct StringList const* acc_19);

bool myHasParam_(struct StringBoolFun1 hasParam_2, struct PropName_ name_17, struct StringList const* arg_195);

bool fun_48(void const* env_27, struct PropName_ arg_73, struct StringList const* arg_74);

struct StringList const* fun_49(void const* env_28, struct Msg_ arg_76, struct StringList const* arg_77);

struct StringListResult_Tuple2 run_(struct StringList const*, struct StringList const*, struct PropName_StringListBoolFun2, struct Msg_StringListStringListFun2);

struct StringList const* rev_(struct StringList const*);

struct String MiloneStd_StdString_concat(struct String, struct StringList const*);

struct String std_opts_Program_parseForTest(struct StringList const* args_16, struct StringBoolFun1 hasParam_2);

bool fun_16(struct String arg_196);

bool fun_50(void const* env_29, struct String arg_78);

bool MiloneStd_StdString_startsWith(struct String, struct String);

bool fun_17(struct String name_22);

bool fun_51(void const* env_30, struct String arg_79);

char std_opts_Program_testCore(char arg_197);

struct StringList const* fun_55(struct StringList const* s_25, struct String name_23);

struct StringList const* fun_52(void const* env_31, struct StringList const* arg_80, struct String arg_81);

struct StringList const* fun_19(struct StringList const* s_27, struct StringStringTuple2 arg_198);

struct StringList const* fun_53(void const* env_32, struct StringList const* arg_82, struct StringStringTuple2 arg_83);

struct StringList const* fun_20(struct StringList const* s_29, struct String value_16);

struct StringList const* fun_54(void const* env_33, struct StringList const* arg_84, struct String arg_85);

struct StringList const* fold_(struct StringListStringStringListFun2, struct StringList const*, struct StringList const*);

struct StringList const* fold_1(struct StringListStringStringTuple2StringListFun2, struct StringList const*, struct StringStringTuple2List const*);

struct String display_(void const* opts_2);

void const* MiloneStd_StdOpts_parseOpts(struct StringList const*, struct StringList const*);

char std_opts_Program_testParseOpts(char arg_199);

int milone_main();

struct IntStringTuple2 {
    int t0;
    struct String t1;
};

struct IntStringTuple2StringIntStringTuple2Fun2 {
    struct IntStringTuple2(*fun)(void const*, struct IntStringTuple2, struct String);
    void const* env;
};

enum PropName_Discriminant {
    Long_,
    Short_,
};

struct PropName_ {
    enum PropName_Discriminant discriminant;
    union {
        struct String Long_;
        char Short_;
    };
};

struct StringList {
    struct String head;
    struct StringList const* tail;
};

enum Msg_Discriminant {
    Binding_,
    Positional_,
};

struct Msg_ {
    enum Msg_Discriminant discriminant;
    union {
        void const* Binding_;
        struct String Positional_;
    };
};

struct StringOption {
    bool some;
    struct String value;
};

struct PropName_StringOptionTuple2 {
    struct PropName_ t0;
    struct StringOption t1;
};

struct StringBoolFun1 {
    bool(*fun)(void const*, struct String);
    void const* env;
};

struct StringBoolFun1Tuple1 {
    struct StringBoolFun1 t0;
};

struct PropName_StringListBoolFun2 {
    bool(*fun)(void const*, struct PropName_, struct StringList const*);
    void const* env;
};

struct Msg_StringListStringListFun2 {
    struct StringList const*(*fun)(void const*, struct Msg_, struct StringList const*);
    void const* env;
};

enum Result_Discriminant {
    Ok_,
    NoValueError_,
    RedundantValueError_,
};

struct Result_ {
    enum Result_Discriminant discriminant;
    union {
        struct PropName_ NoValueError_;
        void const* RedundantValueError_;
    };
};

struct StringListResult_Tuple2 {
    struct StringList const* t0;
    struct Result_ t1;
};

struct PropName_StringTuple2 {
    struct PropName_ t0;
    struct String t1;
};

struct StringStringTuple2 {
    struct String t0;
    struct String t1;
};

struct StringListStringStringListFun2 {
    struct StringList const*(*fun)(void const*, struct StringList const*, struct String);
    void const* env;
};

struct Opts_ {
    struct StringList const* t0;
    struct StringList const* t1;
    struct StringStringTuple2List const* t2;
    struct StringOption t3;
};

struct StringListStringStringTuple2StringListFun2 {
    struct StringList const*(*fun)(void const*, struct StringList const*, struct StringStringTuple2);
    void const* env;
};

void const* emptyOpts_;

struct IntStringTuple2 fun_15(struct IntStringTuple2 arg_194, struct String arg_5) {
    int i_11 = arg_194.t0;
    struct String s_22 = arg_194.t1;
    struct String call_162 = str_of_int64(i_11);
    struct String call_163 = MiloneStd_StdString_replace(str_add(str_add((struct String){.str = "{", .len = 1}, call_162), (struct String){.str = "}", .len = 1}), arg_5, s_22);
    struct String s_23 = call_163;
    struct IntStringTuple2 tuple_105 = (struct IntStringTuple2){.t0 = (i_11 + 1), .t1 = s_23};
    return tuple_105;
}

struct IntStringTuple2 fun_47(void const* env_26, struct IntStringTuple2 arg_71, struct String arg_72) {
    struct IntStringTuple2 call_164 = fun_15(arg_71, arg_72);
    return call_164;
}

struct String std_opts_Program_format(struct String s_20, struct StringList const* args_15) {
    struct IntStringTuple2StringIntStringTuple2Fun2 fun_90 = (struct IntStringTuple2StringIntStringTuple2Fun2){.fun = fun_47, .env = NULL};
    struct IntStringTuple2 tuple_106 = (struct IntStringTuple2){.t0 = 0, .t1 = s_20};
    struct IntStringTuple2 call_165 = fold_2(fun_90, tuple_106, args_15);
    struct String s_21 = call_165.t1;
    return s_21;
}

struct String ofName_(struct PropName_ name_12) {
    struct String match_41;
    if ((name_12.discriminant != Long_)) goto next_455;
    struct String name_13 = name_12.Long_;
    struct StringList const* list_13 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_13))) = (struct StringList){.head = name_13, .tail = NULL};
    struct String call_166 = std_opts_Program_format((struct String){.str = "long `{0}`", .len = 10}, list_13);
    match_41 = call_166;
    goto end_match_454;
next_455:;
    if ((name_12.discriminant != Short_)) goto next_456;
    char name_14 = name_12.Short_;
    struct String call_167 = str_of_char(name_14);
    struct StringList const* list_14 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_14))) = (struct StringList){.head = call_167, .tail = NULL};
    struct String call_168 = std_opts_Program_format((struct String){.str = "short `{0}`", .len = 11}, list_14);
    match_41 = call_168;
    goto end_match_454;
next_456:;
    exit(1);
end_match_454:;
    return match_41;
}

struct StringList const* myUpdate_(struct Msg_ msg_1, struct StringList const* acc_19) {
    struct StringList const* match_42;
    if ((msg_1.discriminant != Binding_)) goto next_458;
    struct PropName_ name_15 = (*(((struct PropName_StringOptionTuple2 const*)msg_1.Binding_))).t0;
    if ((*(((struct PropName_StringOptionTuple2 const*)msg_1.Binding_))).t1.some) goto next_458;
    struct String call_169 = ofName_(name_15);
    struct StringList const* list_16 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_16))) = (struct StringList){.head = call_169, .tail = NULL};
    struct String call_170 = std_opts_Program_format((struct String){.str = "flag {0}", .len = 8}, list_16);
    struct StringList const* list_15 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_15))) = (struct StringList){.head = call_170, .tail = acc_19};
    match_42 = list_15;
    goto end_match_457;
next_458:;
    if ((msg_1.discriminant != Binding_)) goto next_459;
    struct PropName_ name_16 = (*(((struct PropName_StringOptionTuple2 const*)msg_1.Binding_))).t0;
    if ((!((*(((struct PropName_StringOptionTuple2 const*)msg_1.Binding_))).t1.some))) goto next_459;
    struct String value_12 = (*(((struct PropName_StringOptionTuple2 const*)msg_1.Binding_))).t1.value;
    struct String call_171 = ofName_(name_16);
    struct StringList const* list_19 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_19))) = (struct StringList){.head = value_12, .tail = NULL};
    struct StringList const* list_18 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_18))) = (struct StringList){.head = call_171, .tail = list_19};
    struct String call_172 = std_opts_Program_format((struct String){.str = "binding {0} = `{1}`", .len = 19}, list_18);
    struct StringList const* list_17 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_17))) = (struct StringList){.head = call_172, .tail = acc_19};
    match_42 = list_17;
    goto end_match_457;
next_459:;
    if ((msg_1.discriminant != Positional_)) goto next_460;
    struct String value_13 = msg_1.Positional_;
    struct StringList const* list_21 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_21))) = (struct StringList){.head = value_13, .tail = NULL};
    struct String call_173 = std_opts_Program_format((struct String){.str = "pos `{0}`", .len = 9}, list_21);
    struct StringList const* list_20 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_20))) = (struct StringList){.head = call_173, .tail = acc_19};
    match_42 = list_20;
    goto end_match_457;
next_460:;
    exit(1);
end_match_457:;
    return match_42;
}

bool myHasParam_(struct StringBoolFun1 hasParam_2, struct PropName_ name_17, struct StringList const* arg_195) {
    bool match_43;
    if ((name_17.discriminant != Long_)) goto next_462;
    struct String name_18 = name_17.Long_;
    bool app_29 = hasParam_2.fun(hasParam_2.env, name_18);
    match_43 = app_29;
    goto end_match_461;
next_462:;
    if ((name_17.discriminant != Short_)) goto next_463;
    char name_19 = name_17.Short_;
    struct String call_174 = str_of_char(name_19);
    bool app_30 = hasParam_2.fun(hasParam_2.env, call_174);
    match_43 = app_30;
    goto end_match_461;
next_463:;
    exit(1);
end_match_461:;
    return match_43;
}

bool fun_48(void const* env_27, struct PropName_ arg_73, struct StringList const* arg_74) {
    struct StringBoolFun1 arg_75 = (*(((struct StringBoolFun1Tuple1 const*)env_27))).t0;
    bool call_175 = myHasParam_(arg_75, arg_73, arg_74);
    return call_175;
}

struct StringList const* fun_49(void const* env_28, struct Msg_ arg_76, struct StringList const* arg_77) {
    struct StringList const* call_176 = myUpdate_(arg_76, arg_77);
    return call_176;
}

struct String std_opts_Program_parseForTest(struct StringList const* args_16, struct StringBoolFun1 hasParam_2) {
    struct StringBoolFun1Tuple1 tuple_107 = (struct StringBoolFun1Tuple1){.t0 = hasParam_2};
    void const* box_38 = milone_mem_alloc(1, sizeof(struct StringBoolFun1Tuple1));
    (*(((struct StringBoolFun1Tuple1*)box_38))) = tuple_107;
    struct PropName_StringListBoolFun2 fun_91 = (struct PropName_StringListBoolFun2){.fun = fun_48, .env = box_38};
    struct Msg_StringListStringListFun2 fun_92 = (struct Msg_StringListStringListFun2){.fun = fun_49, .env = NULL};
    struct StringListResult_Tuple2 call_177 = run_(args_16, NULL, fun_91, fun_92);
    struct StringList const* acc_20 = call_177.t0;
    struct Result_ result_4 = call_177.t1;
    struct StringList const* match_44;
    if ((result_4.discriminant != Ok_)) goto next_465;
    match_44 = acc_20;
    goto end_match_464;
next_465:;
    if ((result_4.discriminant != NoValueError_)) goto next_466;
    struct PropName_ name_20 = result_4.NoValueError_;
    struct String call_178 = ofName_(name_20);
    struct StringList const* list_23 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_23))) = (struct StringList){.head = call_178, .tail = NULL};
    struct String call_179 = std_opts_Program_format((struct String){.str = "error (no-value) {0}", .len = 20}, list_23);
    struct StringList const* list_22 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_22))) = (struct StringList){.head = call_179, .tail = acc_20};
    match_44 = list_22;
    goto end_match_464;
next_466:;
    if ((result_4.discriminant != RedundantValueError_)) goto next_467;
    struct PropName_ name_21 = (*(((struct PropName_StringTuple2 const*)result_4.RedundantValueError_))).t0;
    struct String value_14 = (*(((struct PropName_StringTuple2 const*)result_4.RedundantValueError_))).t1;
    struct String call_180 = ofName_(name_21);
    struct StringList const* list_26 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_26))) = (struct StringList){.head = value_14, .tail = NULL};
    struct StringList const* list_25 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_25))) = (struct StringList){.head = call_180, .tail = list_26};
    struct String call_181 = std_opts_Program_format((struct String){.str = "error (invalid-value) {0} = `{1}`", .len = 33}, list_25);
    struct StringList const* list_24 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_24))) = (struct StringList){.head = call_181, .tail = acc_20};
    match_44 = list_24;
    goto end_match_464;
next_467:;
    exit(1);
end_match_464:;
    struct StringList const* acc_21 = match_44;
    struct StringList const* call_182 = rev_(acc_21);
    struct String call_183 = MiloneStd_StdString_concat((struct String){.str = "; ", .len = 2}, call_182);
    return call_183;
}

bool fun_16(struct String arg_196) {
    return false;
}

bool fun_50(void const* env_29, struct String arg_78) {
    bool call_184 = fun_16(arg_78);
    return call_184;
}

bool fun_17(struct String name_22) {
    bool if_86;
    if ((str_compare(name_22, (struct String){.str = "n", .len = 1}) == 0)) {
        goto then_469;
    } else {
        goto else_470;
    }
then_469:;
    if_86 = true;
    goto if_next_468;
else_470:;
    bool call_185 = MiloneStd_StdString_startsWith((struct String){.str = "set-", .len = 4}, name_22);
    if_86 = call_185;
    goto if_next_468;
if_next_468:;
    return if_86;
}

bool fun_51(void const* env_30, struct String arg_79) {
    bool call_186 = fun_17(arg_79);
    return call_186;
}

char std_opts_Program_testCore(char arg_197) {
    struct String call_187 = std_opts_Program_format((struct String){.str = "", .len = 0}, NULL);
    milone_assert((str_compare(call_187, (struct String){.str = "", .len = 0}) == 0), 58, 2);
    struct StringList const* list_28 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_28))) = (struct StringList){.head = (struct String){.str = "2", .len = 1}, .tail = NULL};
    struct StringList const* list_27 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_27))) = (struct StringList){.head = (struct String){.str = "1", .len = 1}, .tail = list_28};
    struct String call_188 = std_opts_Program_format((struct String){.str = "{0} + {0} = {1}", .len = 15}, list_27);
    milone_assert((str_compare(call_188, (struct String){.str = "1 + 1 = 2", .len = 9}) == 0), 59, 2);
    struct StringBoolFun1 fun_93 = (struct StringBoolFun1){.fun = fun_50, .env = NULL};
    struct StringBoolFun1 noParam_ = fun_93;
    struct String call_189 = std_opts_Program_parseForTest(NULL, noParam_);
    milone_assert((str_compare(call_189, (struct String){.str = "", .len = 0}) == 0), 64, 2);
    struct StringList const* list_29 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_29))) = (struct StringList){.head = (struct String){.str = "-h", .len = 2}, .tail = NULL};
    struct String call_190 = std_opts_Program_parseForTest(list_29, noParam_);
    milone_assert((str_compare(call_190, (struct String){.str = "flag short `h`", .len = 14}) == 0), 67, 2);
    struct StringList const* list_30 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_30))) = (struct StringList){.head = (struct String){.str = "--help", .len = 6}, .tail = NULL};
    struct String call_191 = std_opts_Program_parseForTest(list_30, noParam_);
    milone_assert((str_compare(call_191, (struct String){.str = "flag long `help`", .len = 16}) == 0), 70, 2);
    struct StringList const* list_31 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_31))) = (struct StringList){.head = (struct String){.str = "-abc", .len = 4}, .tail = NULL};
    struct String call_192 = std_opts_Program_parseForTest(list_31, noParam_);
    milone_assert((str_compare(call_192, (struct String){.str = "flag short `a`; flag short `b`; flag short `c`", .len = 46}) == 0), 73, 2);
    struct StringList const* list_32 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_32))) = (struct StringList){.head = (struct String){.str = "foo", .len = 3}, .tail = NULL};
    struct String call_193 = std_opts_Program_parseForTest(list_32, noParam_);
    milone_assert((str_compare(call_193, (struct String){.str = "pos `foo`", .len = 9}) == 0), 76, 2);
    struct StringBoolFun1 fun_94 = (struct StringBoolFun1){.fun = fun_51, .env = NULL};
    struct StringBoolFun1 hasParam_3 = fun_94;
    struct StringList const* list_34 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_34))) = (struct StringList){.head = (struct String){.str = "10", .len = 2}, .tail = NULL};
    struct StringList const* list_33 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_33))) = (struct StringList){.head = (struct String){.str = "-n", .len = 2}, .tail = list_34};
    struct String call_194 = std_opts_Program_parseForTest(list_33, hasParam_3);
    milone_assert((str_compare(call_194, (struct String){.str = "binding short `n` = `10`", .len = 24}) == 0), 82, 2);
    struct StringList const* list_35 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_35))) = (struct StringList){.head = (struct String){.str = "-n=-1", .len = 5}, .tail = NULL};
    struct String call_195 = std_opts_Program_parseForTest(list_35, hasParam_3);
    milone_assert((str_compare(call_195, (struct String){.str = "binding short `n` = `-1`", .len = 24}) == 0), 85, 2);
    struct StringList const* list_37 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_37))) = (struct StringList){.head = (struct String){.str = "1", .len = 1}, .tail = NULL};
    struct StringList const* list_36 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_36))) = (struct StringList){.head = (struct String){.str = "-mn", .len = 3}, .tail = list_37};
    struct String call_196 = std_opts_Program_parseForTest(list_36, hasParam_3);
    milone_assert((str_compare(call_196, (struct String){.str = "flag short `m`; binding short `n` = `1`", .len = 39}) == 0), 88, 2);
    struct StringList const* list_38 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_38))) = (struct StringList){.head = (struct String){.str = "-mn=1", .len = 5}, .tail = NULL};
    struct String call_197 = std_opts_Program_parseForTest(list_38, hasParam_3);
    milone_assert((str_compare(call_197, (struct String){.str = "flag short `m`; binding short `n` = `1`", .len = 39}) == 0), 89, 2);
    struct StringList const* list_40 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_40))) = (struct StringList){.head = (struct String){.str = "john", .len = 4}, .tail = NULL};
    struct StringList const* list_39 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_39))) = (struct StringList){.head = (struct String){.str = "--set-name", .len = 10}, .tail = list_40};
    struct String call_198 = std_opts_Program_parseForTest(list_39, hasParam_3);
    milone_assert((str_compare(call_198, (struct String){.str = "binding long `set-name` = `john`", .len = 32}) == 0), 92, 2);
    struct StringList const* list_41 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_41))) = (struct StringList){.head = (struct String){.str = "--set-name=john-doe", .len = 19}, .tail = NULL};
    struct String call_199 = std_opts_Program_parseForTest(list_41, hasParam_3);
    milone_assert((str_compare(call_199, (struct String){.str = "binding long `set-name` = `john-doe`", .len = 36}) == 0), 93, 2);
    struct StringList const* list_42 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_42))) = (struct StringList){.head = (struct String){.str = "--", .len = 2}, .tail = NULL};
    struct String call_200 = std_opts_Program_parseForTest(list_42, noParam_);
    milone_assert((str_compare(call_200, (struct String){.str = "", .len = 0}) == 0), 96, 2);
    struct StringList const* list_44 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_44))) = (struct StringList){.head = (struct String){.str = "--help", .len = 6}, .tail = NULL};
    struct StringList const* list_43 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_43))) = (struct StringList){.head = (struct String){.str = "--", .len = 2}, .tail = list_44};
    struct String call_201 = std_opts_Program_parseForTest(list_43, noParam_);
    milone_assert((str_compare(call_201, (struct String){.str = "pos `--help`", .len = 12}) == 0), 97, 2);
    struct StringList const* list_46 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_46))) = (struct StringList){.head = (struct String){.str = "-=", .len = 2}, .tail = NULL};
    struct StringList const* list_45 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_45))) = (struct StringList){.head = (struct String){.str = "-", .len = 1}, .tail = list_46};
    struct String call_202 = std_opts_Program_parseForTest(list_45, noParam_);
    milone_assert((str_compare(call_202, (struct String){.str = "pos `-`; pos `-=`", .len = 17}) == 0), 100, 2);
    struct StringList const* list_47 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_47))) = (struct StringList){.head = (struct String){.str = "-n", .len = 2}, .tail = NULL};
    struct String call_203 = std_opts_Program_parseForTest(list_47, hasParam_3);
    milone_assert((str_compare(call_203, (struct String){.str = "error (no-value) short `n`", .len = 26}) == 0), 103, 2);
    struct StringList const* list_49 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_49))) = (struct StringList){.head = (struct String){.str = "--", .len = 2}, .tail = NULL};
    struct StringList const* list_48 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_48))) = (struct StringList){.head = (struct String){.str = "-n", .len = 2}, .tail = list_49};
    struct String call_204 = std_opts_Program_parseForTest(list_48, hasParam_3);
    milone_assert((str_compare(call_204, (struct String){.str = "error (no-value) short `n`", .len = 26}) == 0), 104, 2);
    struct StringList const* list_51 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_51))) = (struct StringList){.head = (struct String){.str = "-", .len = 1}, .tail = NULL};
    struct StringList const* list_50 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_50))) = (struct StringList){.head = (struct String){.str = "-x=foo", .len = 6}, .tail = list_51};
    struct String call_205 = std_opts_Program_parseForTest(list_50, hasParam_3);
    milone_assert((str_compare(call_205, (struct String){.str = "error (invalid-value) short `x` = `foo`", .len = 39}) == 0), 105, 2);
    return 0;
}

struct StringList const* fun_55(struct StringList const* s_25, struct String name_23) {
    struct StringList const* list_52 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_52))) = (struct StringList){.head = name_23, .tail = s_25};
    return list_52;
}

struct StringList const* fun_52(void const* env_31, struct StringList const* arg_80, struct String arg_81) {
    struct StringList const* call_206 = fun_55(arg_80, arg_81);
    return call_206;
}

struct StringList const* fun_19(struct StringList const* s_27, struct StringStringTuple2 arg_198) {
    struct String name_24 = arg_198.t0;
    struct String value_15 = arg_198.t1;
    struct StringList const* list_55 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_55))) = (struct StringList){.head = value_15, .tail = NULL};
    struct StringList const* list_54 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_54))) = (struct StringList){.head = name_24, .tail = list_55};
    struct String call_207 = std_opts_Program_format((struct String){.str = "{0}=`{1}`", .len = 9}, list_54);
    struct StringList const* list_53 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_53))) = (struct StringList){.head = call_207, .tail = s_27};
    return list_53;
}

struct StringList const* fun_53(void const* env_32, struct StringList const* arg_82, struct StringStringTuple2 arg_83) {
    struct StringList const* call_208 = fun_19(arg_82, arg_83);
    return call_208;
}

struct StringList const* fun_20(struct StringList const* s_29, struct String value_16) {
    struct StringList const* list_57 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_57))) = (struct StringList){.head = value_16, .tail = NULL};
    struct String call_209 = std_opts_Program_format((struct String){.str = "`{0}`", .len = 5}, list_57);
    struct StringList const* list_56 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_56))) = (struct StringList){.head = call_209, .tail = s_29};
    return list_56;
}

struct StringList const* fun_54(void const* env_33, struct StringList const* arg_84, struct String arg_85) {
    struct StringList const* call_210 = fun_20(arg_84, arg_85);
    return call_210;
}

struct String display_(void const* opts_2) {
    struct StringListStringStringListFun2 fun_95 = (struct StringListStringStringListFun2){.fun = fun_52, .env = NULL};
    struct StringList const* call_211 = fold_(fun_95, NULL, (*(((struct Opts_ const*)opts_2))).t1);
    struct StringList const* s_24 = call_211;
    struct StringListStringStringTuple2StringListFun2 fun_96 = (struct StringListStringStringTuple2StringListFun2){.fun = fun_53, .env = NULL};
    struct StringList const* call_212 = fold_1(fun_96, s_24, (*(((struct Opts_ const*)opts_2))).t2);
    struct StringList const* s_26 = call_212;
    struct StringListStringStringListFun2 fun_97 = (struct StringListStringStringListFun2){.fun = fun_54, .env = NULL};
    struct StringList const* call_213 = fold_(fun_97, s_26, (*(((struct Opts_ const*)opts_2))).t0);
    struct StringList const* s_28 = call_213;
    struct StringList const* match_45;
    if ((!((*(((struct Opts_ const*)opts_2))).t3.some))) goto next_472;
    struct String error_1 = (*(((struct Opts_ const*)opts_2))).t3.value;
    struct StringList const* list_58 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_58))) = (struct StringList){.head = str_add((struct String){.str = "error ", .len = 6}, error_1), .tail = s_28};
    match_45 = list_58;
    goto end_match_471;
next_472:;
    if ((*(((struct Opts_ const*)opts_2))).t3.some) goto next_473;
    match_45 = s_28;
    goto end_match_471;
next_473:;
    exit(1);
end_match_471:;
    struct StringList const* s_30 = match_45;
    struct StringList const* call_214 = rev_(s_30);
    struct String call_215 = MiloneStd_StdString_concat((struct String){.str = "; ", .len = 2}, call_214);
    return call_215;
}

char std_opts_Program_testParseOpts(char arg_199) {
    struct StringList const* list_61 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_61))) = (struct StringList){.head = (struct String){.str = "?level", .len = 6}, .tail = NULL};
    struct StringList const* list_60 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_60))) = (struct StringList){.head = (struct String){.str = "*user", .len = 5}, .tail = list_61};
    struct StringList const* list_59 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_59))) = (struct StringList){.head = (struct String){.str = "help", .len = 4}, .tail = list_60};
    struct StringList const* def_2 = list_59;
    struct StringList const* list_66 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_66))) = (struct StringList){.head = (struct String){.str = "bar.txt", .len = 7}, .tail = NULL};
    struct StringList const* list_65 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_65))) = (struct StringList){.head = (struct String){.str = "--level=0", .len = 9}, .tail = list_66};
    struct StringList const* list_64 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_64))) = (struct StringList){.head = (struct String){.str = "foOC.txt", .len = 8}, .tail = list_65};
    struct StringList const* list_63 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_63))) = (struct StringList){.head = (struct String){.str = "john", .len = 4}, .tail = list_64};
    struct StringList const* list_62 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_62))) = (struct StringList){.head = (struct String){.str = "--user", .len = 6}, .tail = list_63};
    void const* call_216 = MiloneStd_StdOpts_parseOpts(def_2, list_62);
    struct String call_217 = display_(call_216);
    milone_assert((str_compare(call_217, (struct String){.str = "level=`0`; user=`john`; `bar.txt`; `foOC.txt`", .len = 45}) == 0), 130, 2);
    return 0;
}

int milone_main() {
    struct Opts_ Opts_5 = (struct Opts_){.t0 = NULL, .t1 = NULL, .t2 = NULL, .t3 = (struct StringOption){.some = false}};
    void const* box_39 = milone_mem_alloc(1, sizeof(struct Opts_));
    (*(((struct Opts_*)box_39))) = Opts_5;
    emptyOpts_ = box_39;
    char call_218 = std_opts_Program_testCore(0);
    char call_219 = std_opts_Program_testParseOpts(0);
    return 0;
}
