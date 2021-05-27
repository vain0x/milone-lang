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

struct String MiloneStd_StdString_replace(struct String, struct String, struct String);

struct IntStringTuple2 fun_(struct IntStringTuple2 arg_86, struct String arg_5);

struct IntStringTuple2 fun_8(void const* env_5, struct IntStringTuple2 arg_15, struct String arg_16);

struct IntStringTuple2 fold_(struct IntStringTuple2StringIntStringTuple2Fun2, struct IntStringTuple2, struct StringList const*);

struct String std_opts_Program_format(struct String s_20, struct StringList const* args_14);

struct String ofName_(struct PropName_ name_4);

struct StringList const* myUpdate_(struct Msg_ msg_, struct StringList const* acc_17);

bool myHasParam_(struct StringBoolFun1 hasParam_1, struct PropName_ name_9, struct StringList const* arg_87);

bool fun_9(void const* env_6, struct PropName_ arg_17, struct StringList const* arg_18);

struct StringList const* fun_10(void const* env_7, struct Msg_ arg_20, struct StringList const* arg_21);

struct StringListResult_Tuple2 run_(struct StringList const*, struct StringList const*, struct PropName_StringListBoolFun2, struct Msg_StringListStringListFun2);

struct StringList const* rev_(struct StringList const*);

struct String MiloneStd_StdString_concat(struct String, struct StringList const*);

struct String std_opts_Program_parseForTest(struct StringList const* args_15, struct StringBoolFun1 hasParam_1);

bool fun_1(struct String arg_88);

bool fun_11(void const* env_8, struct String arg_22);

bool MiloneStd_StdString_startsWith(struct String, struct String);

bool fun_2(struct String name_14);

bool fun_12(void const* env_9, struct String arg_23);

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
    NoValueError_,
    InvalidValueError_,
};

struct Msg_ {
    enum Msg_Discriminant discriminant;
    union {
        void const* Binding_;
        struct String Positional_;
        struct PropName_ NoValueError_;
        void const* InvalidValueError_;
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
    NoValueError_1,
    RedundantValueError_,
};

struct Result_ {
    enum Result_Discriminant discriminant;
    union {
        struct PropName_ NoValueError_1;
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

struct IntStringTuple2 fun_(struct IntStringTuple2 arg_86, struct String arg_5) {
    int i_11 = arg_86.t0;
    struct String s_22 = arg_86.t1;
    struct String call_63 = str_of_int64(i_11);
    struct String call_64 = MiloneStd_StdString_replace(str_add(str_add((struct String){.str = "{", .len = 1}, call_63), (struct String){.str = "}", .len = 1}), arg_5, s_22);
    struct String s_23 = call_64;
    struct IntStringTuple2 tuple_25 = (struct IntStringTuple2){.t0 = (i_11 + 1), .t1 = s_23};
    return tuple_25;
}

struct IntStringTuple2 fun_8(void const* env_5, struct IntStringTuple2 arg_15, struct String arg_16) {
    struct IntStringTuple2 call_65 = fun_(arg_15, arg_16);
    return call_65;
}

struct String std_opts_Program_format(struct String s_20, struct StringList const* args_14) {
    struct IntStringTuple2StringIntStringTuple2Fun2 fun_18 = (struct IntStringTuple2StringIntStringTuple2Fun2){.fun = fun_8, .env = NULL};
    struct IntStringTuple2 tuple_26 = (struct IntStringTuple2){.t0 = 0, .t1 = s_20};
    struct IntStringTuple2 call_66 = fold_(fun_18, tuple_26, args_14);
    struct String s_21 = call_66.t1;
    return s_21;
}

struct String ofName_(struct PropName_ name_4) {
    struct String match_11;
    if ((name_4.discriminant != Long_)) goto next_295;
    struct String name_5 = name_4.Long_;
    struct StringList const* list_5 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_5))) = (struct StringList){.head = name_5, .tail = NULL};
    struct String call_67 = std_opts_Program_format((struct String){.str = "long `{0}`", .len = 10}, list_5);
    match_11 = call_67;
    goto end_match_294;
next_295:;
    if ((name_4.discriminant != Short_)) goto next_296;
    char name_6 = name_4.Short_;
    struct String call_68 = str_of_char(name_6);
    struct StringList const* list_6 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_6))) = (struct StringList){.head = call_68, .tail = NULL};
    struct String call_69 = std_opts_Program_format((struct String){.str = "short `{0}`", .len = 11}, list_6);
    match_11 = call_69;
    goto end_match_294;
next_296:;
    exit(1);
end_match_294:;
    return match_11;
}

struct StringList const* myUpdate_(struct Msg_ msg_, struct StringList const* acc_17) {
    struct StringList const* match_12;
    if ((msg_.discriminant != Binding_)) goto next_298;
    struct PropName_ name_7 = (*(((struct PropName_StringOptionTuple2 const*)msg_.Binding_))).t0;
    if ((*(((struct PropName_StringOptionTuple2 const*)msg_.Binding_))).t1.some) goto next_298;
    struct String call_70 = ofName_(name_7);
    struct StringList const* list_8 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_8))) = (struct StringList){.head = call_70, .tail = NULL};
    struct String call_71 = std_opts_Program_format((struct String){.str = "flag {0}", .len = 8}, list_8);
    struct StringList const* list_7 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_7))) = (struct StringList){.head = call_71, .tail = acc_17};
    match_12 = list_7;
    goto end_match_297;
next_298:;
    if ((msg_.discriminant != Binding_)) goto next_299;
    struct PropName_ name_8 = (*(((struct PropName_StringOptionTuple2 const*)msg_.Binding_))).t0;
    if ((!((*(((struct PropName_StringOptionTuple2 const*)msg_.Binding_))).t1.some))) goto next_299;
    struct String value_7 = (*(((struct PropName_StringOptionTuple2 const*)msg_.Binding_))).t1.value;
    struct String call_72 = ofName_(name_8);
    struct StringList const* list_11 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_11))) = (struct StringList){.head = value_7, .tail = NULL};
    struct StringList const* list_10 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_10))) = (struct StringList){.head = call_72, .tail = list_11};
    struct String call_73 = std_opts_Program_format((struct String){.str = "binding {0} = `{1}`", .len = 19}, list_10);
    struct StringList const* list_9 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_9))) = (struct StringList){.head = call_73, .tail = acc_17};
    match_12 = list_9;
    goto end_match_297;
next_299:;
    if ((msg_.discriminant != Positional_)) goto next_300;
    struct String value_8 = msg_.Positional_;
    struct StringList const* list_13 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_13))) = (struct StringList){.head = value_8, .tail = NULL};
    struct String call_74 = std_opts_Program_format((struct String){.str = "pos `{0}`", .len = 9}, list_13);
    struct StringList const* list_12 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_12))) = (struct StringList){.head = call_74, .tail = acc_17};
    match_12 = list_12;
    goto end_match_297;
next_300:;
    exit(1);
end_match_297:;
    return match_12;
}

bool myHasParam_(struct StringBoolFun1 hasParam_1, struct PropName_ name_9, struct StringList const* arg_87) {
    bool match_13;
    if ((name_9.discriminant != Long_)) goto next_302;
    struct String name_10 = name_9.Long_;
    bool app_10 = hasParam_1.fun(hasParam_1.env, name_10);
    match_13 = app_10;
    goto end_match_301;
next_302:;
    if ((name_9.discriminant != Short_)) goto next_303;
    char name_11 = name_9.Short_;
    struct String call_75 = str_of_char(name_11);
    bool app_11 = hasParam_1.fun(hasParam_1.env, call_75);
    match_13 = app_11;
    goto end_match_301;
next_303:;
    exit(1);
end_match_301:;
    return match_13;
}

bool fun_9(void const* env_6, struct PropName_ arg_17, struct StringList const* arg_18) {
    struct StringBoolFun1 arg_19 = (*(((struct StringBoolFun1Tuple1 const*)env_6))).t0;
    bool call_76 = myHasParam_(arg_19, arg_17, arg_18);
    return call_76;
}

struct StringList const* fun_10(void const* env_7, struct Msg_ arg_20, struct StringList const* arg_21) {
    struct StringList const* call_77 = myUpdate_(arg_20, arg_21);
    return call_77;
}

struct String std_opts_Program_parseForTest(struct StringList const* args_15, struct StringBoolFun1 hasParam_1) {
    struct StringBoolFun1Tuple1 tuple_27 = (struct StringBoolFun1Tuple1){.t0 = hasParam_1};
    void const* box_3 = milone_mem_alloc(1, sizeof(struct StringBoolFun1Tuple1));
    (*(((struct StringBoolFun1Tuple1*)box_3))) = tuple_27;
    struct PropName_StringListBoolFun2 fun_19 = (struct PropName_StringListBoolFun2){.fun = fun_9, .env = box_3};
    struct Msg_StringListStringListFun2 fun_20 = (struct Msg_StringListStringListFun2){.fun = fun_10, .env = NULL};
    struct StringListResult_Tuple2 call_78 = run_(args_15, NULL, fun_19, fun_20);
    struct StringList const* acc_18 = call_78.t0;
    struct Result_ result_3 = call_78.t1;
    struct StringList const* match_14;
    if ((result_3.discriminant != Ok_)) goto next_305;
    match_14 = acc_18;
    goto end_match_304;
next_305:;
    if ((result_3.discriminant != NoValueError_1)) goto next_306;
    struct PropName_ name_12 = result_3.NoValueError_1;
    struct String call_79 = ofName_(name_12);
    struct StringList const* list_15 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_15))) = (struct StringList){.head = call_79, .tail = NULL};
    struct String call_80 = std_opts_Program_format((struct String){.str = "error (no-value) {0}", .len = 20}, list_15);
    struct StringList const* list_14 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_14))) = (struct StringList){.head = call_80, .tail = acc_18};
    match_14 = list_14;
    goto end_match_304;
next_306:;
    if ((result_3.discriminant != RedundantValueError_)) goto next_307;
    struct PropName_ name_13 = (*(((struct PropName_StringTuple2 const*)result_3.RedundantValueError_))).t0;
    struct String value_9 = (*(((struct PropName_StringTuple2 const*)result_3.RedundantValueError_))).t1;
    struct String call_81 = ofName_(name_13);
    struct StringList const* list_18 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_18))) = (struct StringList){.head = value_9, .tail = NULL};
    struct StringList const* list_17 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_17))) = (struct StringList){.head = call_81, .tail = list_18};
    struct String call_82 = std_opts_Program_format((struct String){.str = "error (invalid-value) {0} = `{1}`", .len = 33}, list_17);
    struct StringList const* list_16 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_16))) = (struct StringList){.head = call_82, .tail = acc_18};
    match_14 = list_16;
    goto end_match_304;
next_307:;
    exit(1);
end_match_304:;
    struct StringList const* acc_19 = match_14;
    struct StringList const* call_83 = rev_(acc_19);
    struct String call_84 = MiloneStd_StdString_concat((struct String){.str = "; ", .len = 2}, call_83);
    return call_84;
}

bool fun_1(struct String arg_88) {
    return false;
}

bool fun_11(void const* env_8, struct String arg_22) {
    bool call_85 = fun_1(arg_22);
    return call_85;
}

bool fun_2(struct String name_14) {
    bool if_76;
    if ((str_compare(name_14, (struct String){.str = "n", .len = 1}) == 0)) {
        goto then_309;
    } else {
        goto else_310;
    }
then_309:;
    if_76 = true;
    goto if_next_308;
else_310:;
    bool call_86 = MiloneStd_StdString_startsWith((struct String){.str = "set-", .len = 4}, name_14);
    if_76 = call_86;
    goto if_next_308;
if_next_308:;
    return if_76;
}

bool fun_12(void const* env_9, struct String arg_23) {
    bool call_87 = fun_2(arg_23);
    return call_87;
}

int milone_main() {
    struct String call_88 = std_opts_Program_format((struct String){.str = "", .len = 0}, NULL);
    milone_assert((str_compare(call_88, (struct String){.str = "", .len = 0}) == 0), 57, 2);
    struct StringList const* list_20 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_20))) = (struct StringList){.head = (struct String){.str = "2", .len = 1}, .tail = NULL};
    struct StringList const* list_19 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_19))) = (struct StringList){.head = (struct String){.str = "1", .len = 1}, .tail = list_20};
    struct String call_89 = std_opts_Program_format((struct String){.str = "{0} + {0} = {1}", .len = 15}, list_19);
    milone_assert((str_compare(call_89, (struct String){.str = "1 + 1 = 2", .len = 9}) == 0), 58, 2);
    struct StringBoolFun1 fun_21 = (struct StringBoolFun1){.fun = fun_11, .env = NULL};
    struct StringBoolFun1 noParam_ = fun_21;
    struct String call_90 = std_opts_Program_parseForTest(NULL, noParam_);
    milone_assert((str_compare(call_90, (struct String){.str = "", .len = 0}) == 0), 63, 2);
    struct StringList const* list_21 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_21))) = (struct StringList){.head = (struct String){.str = "-h", .len = 2}, .tail = NULL};
    struct String call_91 = std_opts_Program_parseForTest(list_21, noParam_);
    milone_assert((str_compare(call_91, (struct String){.str = "flag short `h`", .len = 14}) == 0), 66, 2);
    struct StringList const* list_22 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_22))) = (struct StringList){.head = (struct String){.str = "--help", .len = 6}, .tail = NULL};
    struct String call_92 = std_opts_Program_parseForTest(list_22, noParam_);
    milone_assert((str_compare(call_92, (struct String){.str = "flag long `help`", .len = 16}) == 0), 69, 2);
    struct StringList const* list_23 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_23))) = (struct StringList){.head = (struct String){.str = "-abc", .len = 4}, .tail = NULL};
    struct String call_93 = std_opts_Program_parseForTest(list_23, noParam_);
    milone_assert((str_compare(call_93, (struct String){.str = "flag short `a`; flag short `b`; flag short `c`", .len = 46}) == 0), 72, 2);
    struct StringList const* list_24 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_24))) = (struct StringList){.head = (struct String){.str = "foo", .len = 3}, .tail = NULL};
    struct String call_94 = std_opts_Program_parseForTest(list_24, noParam_);
    milone_assert((str_compare(call_94, (struct String){.str = "pos `foo`", .len = 9}) == 0), 75, 2);
    struct StringBoolFun1 fun_22 = (struct StringBoolFun1){.fun = fun_12, .env = NULL};
    struct StringBoolFun1 hasParam_2 = fun_22;
    struct StringList const* list_26 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_26))) = (struct StringList){.head = (struct String){.str = "10", .len = 2}, .tail = NULL};
    struct StringList const* list_25 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_25))) = (struct StringList){.head = (struct String){.str = "-n", .len = 2}, .tail = list_26};
    struct String call_95 = std_opts_Program_parseForTest(list_25, hasParam_2);
    milone_assert((str_compare(call_95, (struct String){.str = "binding short `n` = `10`", .len = 24}) == 0), 81, 2);
    struct StringList const* list_27 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_27))) = (struct StringList){.head = (struct String){.str = "-n=-1", .len = 5}, .tail = NULL};
    struct String call_96 = std_opts_Program_parseForTest(list_27, hasParam_2);
    milone_assert((str_compare(call_96, (struct String){.str = "binding short `n` = `-1`", .len = 24}) == 0), 84, 2);
    struct StringList const* list_29 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_29))) = (struct StringList){.head = (struct String){.str = "1", .len = 1}, .tail = NULL};
    struct StringList const* list_28 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_28))) = (struct StringList){.head = (struct String){.str = "-mn", .len = 3}, .tail = list_29};
    struct String call_97 = std_opts_Program_parseForTest(list_28, hasParam_2);
    milone_assert((str_compare(call_97, (struct String){.str = "flag short `m`; binding short `n` = `1`", .len = 39}) == 0), 87, 2);
    struct StringList const* list_30 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_30))) = (struct StringList){.head = (struct String){.str = "-mn=1", .len = 5}, .tail = NULL};
    struct String call_98 = std_opts_Program_parseForTest(list_30, hasParam_2);
    milone_assert((str_compare(call_98, (struct String){.str = "flag short `m`; binding short `n` = `1`", .len = 39}) == 0), 88, 2);
    struct StringList const* list_32 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_32))) = (struct StringList){.head = (struct String){.str = "john", .len = 4}, .tail = NULL};
    struct StringList const* list_31 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_31))) = (struct StringList){.head = (struct String){.str = "--set-name", .len = 10}, .tail = list_32};
    struct String call_99 = std_opts_Program_parseForTest(list_31, hasParam_2);
    milone_assert((str_compare(call_99, (struct String){.str = "binding long `set-name` = `john`", .len = 32}) == 0), 91, 2);
    struct StringList const* list_33 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_33))) = (struct StringList){.head = (struct String){.str = "--set-name=john-doe", .len = 19}, .tail = NULL};
    struct String call_100 = std_opts_Program_parseForTest(list_33, hasParam_2);
    milone_assert((str_compare(call_100, (struct String){.str = "binding long `set-name` = `john-doe`", .len = 36}) == 0), 92, 2);
    struct StringList const* list_34 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_34))) = (struct StringList){.head = (struct String){.str = "--", .len = 2}, .tail = NULL};
    struct String call_101 = std_opts_Program_parseForTest(list_34, noParam_);
    milone_assert((str_compare(call_101, (struct String){.str = "", .len = 0}) == 0), 95, 2);
    struct StringList const* list_36 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_36))) = (struct StringList){.head = (struct String){.str = "--help", .len = 6}, .tail = NULL};
    struct StringList const* list_35 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_35))) = (struct StringList){.head = (struct String){.str = "--", .len = 2}, .tail = list_36};
    struct String call_102 = std_opts_Program_parseForTest(list_35, noParam_);
    milone_assert((str_compare(call_102, (struct String){.str = "pos `--help`", .len = 12}) == 0), 96, 2);
    struct StringList const* list_38 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_38))) = (struct StringList){.head = (struct String){.str = "-=", .len = 2}, .tail = NULL};
    struct StringList const* list_37 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_37))) = (struct StringList){.head = (struct String){.str = "-", .len = 1}, .tail = list_38};
    struct String call_103 = std_opts_Program_parseForTest(list_37, noParam_);
    milone_assert((str_compare(call_103, (struct String){.str = "pos `-`; pos `-=`", .len = 17}) == 0), 99, 2);
    struct StringList const* list_39 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_39))) = (struct StringList){.head = (struct String){.str = "-n", .len = 2}, .tail = NULL};
    struct String call_104 = std_opts_Program_parseForTest(list_39, hasParam_2);
    milone_assert((str_compare(call_104, (struct String){.str = "error (no-value) short `n`", .len = 26}) == 0), 102, 2);
    struct StringList const* list_41 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_41))) = (struct StringList){.head = (struct String){.str = "--", .len = 2}, .tail = NULL};
    struct StringList const* list_40 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_40))) = (struct StringList){.head = (struct String){.str = "-n", .len = 2}, .tail = list_41};
    struct String call_105 = std_opts_Program_parseForTest(list_40, hasParam_2);
    milone_assert((str_compare(call_105, (struct String){.str = "error (no-value) short `n`", .len = 26}) == 0), 103, 2);
    struct StringList const* list_43 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_43))) = (struct StringList){.head = (struct String){.str = "-", .len = 1}, .tail = NULL};
    struct StringList const* list_42 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_42))) = (struct StringList){.head = (struct String){.str = "-x=foo", .len = 6}, .tail = list_43};
    struct String call_106 = std_opts_Program_parseForTest(list_42, hasParam_2);
    milone_assert((str_compare(call_106, (struct String){.str = "error (invalid-value) short `x` = `foo`", .len = 39}) == 0), 104, 2);
    return 0;
}
