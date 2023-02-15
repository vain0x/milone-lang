#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32GenericWrapper1_;

struct StringGenericWrapper1_;

typedef struct String(*VoidConstPtrInt32StringFunPtr2)(void const *, int32_t);

struct Int32StringFun1;

typedef struct String(*VoidConstPtrStringStringFunPtr2)(void const *, struct String);

struct StringStringFun1;

struct StringNode1_Cons;

struct StringNode1_;

typedef struct String(*VoidConstPtrStringNode1_StringFunPtr2)(void const *, struct StringNode1_);

struct StringNode1_StringFun1;

struct StringCons;

struct StringNode1_Cons;

struct String record_generic_record_generic_eta2_prim(void const *env_, int32_t arg_);

void record_generic_record_generic_testGenericWrapper(void);

struct String record_generic_record_generic_StringStringFun1StringNode1StringFun2_nodePrint(struct StringStringFun1 toString_, struct StringNode1_ node_);

struct StringNode1_ record_generic_record_generic_StringStringNode1ListStringNode1Fun2_newNode(struct String value_1, struct StringNode1_Cons const *children_);

struct StringGenericWrapper1_ record_generic_record_generic_Int32StringFun1Int32GenericWrapper1StringGenericWrapper1Fun2_gwMap(struct Int32StringFun1 f_, struct Int32GenericWrapper1_ r_1);

struct String record_generic_record_generic_StringGenericWrapper1StringFun1_gwUnwrap(struct StringGenericWrapper1_ r_);

struct StringGenericWrapper1_ record_generic_record_generic_StringStringGenericWrapper1Fun1_gwWrap(struct String value_);

int32_t record_generic_record_generic_Int32GenericWrapper1Int32Fun1_gwUnwrap(struct Int32GenericWrapper1_ r_);

struct Int32GenericWrapper1_ record_generic_record_generic_Int32Int32GenericWrapper1Fun1_gwWrap(int32_t value_);

bool MiloneCore_List_StringNode1ListBoolFun1_isEmpty(struct StringNode1_Cons const *);

struct StringCons const *MiloneCore_List_StringNode1StringFun1StringNode1ListStringListFun2_map(struct StringNode1_StringFun1, struct StringNode1_Cons const *);

struct String Std_StdString_concat(struct String, struct StringCons const *);

struct String record_generic_record_generic_nodePrint_StringStringFun1StringNode1StringFun2_go(struct StringStringFun1 toString_, struct StringNode1_ node_1);

struct String record_generic_record_generic_eta2_ObjectStringNode1StringFun2_nodePrint_go_go(void const *env_1, struct StringNode1_ arg_1);

struct String MiloneCore_Prelude_StringStringFun1_id(struct String);

struct String record_generic_record_generic_eta2_testRecusive_id(void const *env_2, struct String arg_3);

struct String record_generic_record_generic_eta2_testRecusive_id_1(void const *env_3, struct String arg_4);

void record_generic_record_generic_testRecusive(void);

int main(int argc, char **argv);

struct Int32GenericWrapper1_ {
    int32_t t0;
};

struct StringGenericWrapper1_ {
    struct String t0;
};

struct Int32StringFun1 {
    VoidConstPtrInt32StringFunPtr2 fun;
    void const *env;
};

struct StringStringFun1 {
    VoidConstPtrStringStringFunPtr2 fun;
    void const *env;
};

struct StringNode1_ {
    struct String t0;
    struct StringNode1_Cons const *t1;
};

struct StringNode1_StringFun1 {
    VoidConstPtrStringNode1_StringFunPtr2 fun;
    void const *env;
};

struct StringNode1_Cons {
    struct StringNode1_ head;
    struct StringNode1_Cons const *tail;
};

struct String record_generic_record_generic_eta2_prim(void const *env_, int32_t arg_) {
    struct String call_;
    call_ = string_of_int64(arg_);
    return call_;
}

void record_generic_record_generic_testGenericWrapper(void) {
    struct Int32GenericWrapper1_ wrappedInt_;
    struct StringGenericWrapper1_ wrappedString_;
    struct Int32GenericWrapper1_ call_1;
    int32_t call_2;
    struct StringGenericWrapper1_ call_3;
    struct String call_4;
    struct Int32StringFun1 fun_;
    struct StringGenericWrapper1_ call_5;
    call_1 = record_generic_record_generic_Int32Int32GenericWrapper1Fun1_gwWrap(42);
    wrappedInt_ = call_1;
    call_2 = record_generic_record_generic_Int32GenericWrapper1Int32Fun1_gwUnwrap(wrappedInt_);
    if ((call_2 != 42)) milone_assert_error("record_generic/record_generic.milone", 15, 2);
    call_3 = record_generic_record_generic_StringStringGenericWrapper1Fun1_gwWrap((struct String){.ptr = "john", .len = 4});
    wrappedString_ = call_3;
    call_4 = record_generic_record_generic_StringGenericWrapper1StringFun1_gwUnwrap(wrappedString_);
    if ((string_compare(call_4, (struct String){.ptr = "john", .len = 4}) != 0)) milone_assert_error("record_generic/record_generic.milone", 18, 2);
    fun_ = (struct Int32StringFun1){.fun = record_generic_record_generic_eta2_prim, .env = NULL};
    call_5 = record_generic_record_generic_Int32StringFun1Int32GenericWrapper1StringGenericWrapper1Fun2_gwMap(fun_, wrappedInt_);
    if ((string_compare(call_5.t0, (struct String){.ptr = "42", .len = 2}) != 0)) milone_assert_error("record_generic/record_generic.milone", 20, 2);
    return;
}

struct String record_generic_record_generic_StringStringFun1StringNode1StringFun2_nodePrint(struct StringStringFun1 toString_, struct StringNode1_ node_) {
    struct String call_6;
    call_6 = record_generic_record_generic_nodePrint_StringStringFun1StringNode1StringFun2_go(toString_, node_);
    return call_6;
}

struct StringNode1_ record_generic_record_generic_StringStringNode1ListStringNode1Fun2_newNode(struct String value_1, struct StringNode1_Cons const *children_) {
    struct StringNode1_ StringNode1_;
    StringNode1_ = (struct StringNode1_){.t0 = value_1, .t1 = children_};
    return StringNode1_;
}

struct StringGenericWrapper1_ record_generic_record_generic_Int32StringFun1Int32GenericWrapper1StringGenericWrapper1Fun2_gwMap(struct Int32StringFun1 f_, struct Int32GenericWrapper1_ r_1) {
    struct StringGenericWrapper1_ StringGenericWrapper1_;
    struct String app_;
    app_ = f_.fun(f_.env, r_1.t0);
    StringGenericWrapper1_ = (struct StringGenericWrapper1_){.t0 = app_};
    return StringGenericWrapper1_;
}

struct String record_generic_record_generic_StringGenericWrapper1StringFun1_gwUnwrap(struct StringGenericWrapper1_ r_) {
    return r_.t0;
}

struct StringGenericWrapper1_ record_generic_record_generic_StringStringGenericWrapper1Fun1_gwWrap(struct String value_) {
    struct StringGenericWrapper1_ StringGenericWrapper1_1;
    StringGenericWrapper1_1 = (struct StringGenericWrapper1_){.t0 = value_};
    return StringGenericWrapper1_1;
}

int32_t record_generic_record_generic_Int32GenericWrapper1Int32Fun1_gwUnwrap(struct Int32GenericWrapper1_ r_) {
    return r_.t0;
}

struct Int32GenericWrapper1_ record_generic_record_generic_Int32Int32GenericWrapper1Fun1_gwWrap(int32_t value_) {
    struct Int32GenericWrapper1_ Int32GenericWrapper1_;
    Int32GenericWrapper1_ = (struct Int32GenericWrapper1_){.t0 = value_};
    return Int32GenericWrapper1_;
}

struct String record_generic_record_generic_nodePrint_StringStringFun1StringNode1StringFun2_go(struct StringStringFun1 toString_, struct StringNode1_ node_1) {
    struct String value_2;
    struct String app_1;
    bool call_7;
    struct String if_;
    void const *box_;
    struct StringNode1_StringFun1 fun_1;
    struct StringCons const *call_8;
    struct String call_9;
    app_1 = toString_.fun(toString_.env, node_1.t0);
    value_2 = app_1;
    call_7 = MiloneCore_List_StringNode1ListBoolFun1_isEmpty(node_1.t1);
    if (call_7) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    if_ = value_2;
    goto if_next_1;
else_3:;
    box_ = ((void const *)milone_region_alloc(1, sizeof(struct StringStringFun1)));
    (*(((struct StringStringFun1 *)box_))) = toString_;
    fun_1 = (struct StringNode1_StringFun1){.fun = record_generic_record_generic_eta2_ObjectStringNode1StringFun2_nodePrint_go_go, .env = box_};
    call_8 = MiloneCore_List_StringNode1StringFun1StringNode1ListStringListFun2_map(fun_1, node_1.t1);
    call_9 = Std_StdString_concat((struct String){.ptr = " ", .len = 1}, call_8);
    if_ = string_add(string_add(string_add(value_2, (struct String){.ptr = "(", .len = 1}), call_9), (struct String){.ptr = ")", .len = 1});
    goto if_next_1;
if_next_1:;
    return if_;
}

struct String record_generic_record_generic_eta2_ObjectStringNode1StringFun2_nodePrint_go_go(void const *env_1, struct StringNode1_ arg_1) {
    struct StringStringFun1 arg_2;
    struct String call_10;
    arg_2 = (*(((struct StringStringFun1 const *)env_1)));
    call_10 = record_generic_record_generic_nodePrint_StringStringFun1StringNode1StringFun2_go(arg_2, arg_1);
    return call_10;
}

struct String record_generic_record_generic_eta2_testRecusive_id(void const *env_2, struct String arg_3) {
    struct String call_11;
    call_11 = MiloneCore_Prelude_StringStringFun1_id(arg_3);
    return call_11;
}

struct String record_generic_record_generic_eta2_testRecusive_id_1(void const *env_3, struct String arg_4) {
    struct String call_12;
    call_12 = MiloneCore_Prelude_StringStringFun1_id(arg_4);
    return call_12;
}

void record_generic_record_generic_testRecusive(void) {
    struct StringNode1_ node_2;
    struct StringNode1_ other_;
    struct StringNode1_Cons const *list_;
    struct StringNode1_Cons const *list_1;
    struct StringNode1_ call_13;
    struct StringNode1_ call_14;
    struct StringNode1_Cons const *list_2;
    struct StringNode1_ call_15;
    struct StringNode1_ call_16;
    struct StringStringFun1 fun_2;
    struct String call_17;
    struct StringNode1_ StringNode1_1;
    struct StringStringFun1 fun_3;
    struct String call_18;
    call_13 = record_generic_record_generic_StringStringNode1ListStringNode1Fun2_newNode((struct String){.ptr = "x", .len = 1}, NULL);
    list_1 = ((struct StringNode1_Cons const *)milone_region_alloc(1, sizeof(struct StringNode1_Cons)));
    (*(((struct StringNode1_Cons *)list_1))) = (struct StringNode1_Cons){.head = call_13, .tail = NULL};
    call_14 = record_generic_record_generic_StringStringNode1ListStringNode1Fun2_newNode((struct String){.ptr = "f", .len = 1}, list_1);
    call_15 = record_generic_record_generic_StringStringNode1ListStringNode1Fun2_newNode((struct String){.ptr = "y", .len = 1}, NULL);
    list_2 = ((struct StringNode1_Cons const *)milone_region_alloc(1, sizeof(struct StringNode1_Cons)));
    (*(((struct StringNode1_Cons *)list_2))) = (struct StringNode1_Cons){.head = call_15, .tail = NULL};
    list_ = ((struct StringNode1_Cons const *)milone_region_alloc(1, sizeof(struct StringNode1_Cons)));
    (*(((struct StringNode1_Cons *)list_))) = (struct StringNode1_Cons){.head = call_14, .tail = list_2};
    call_16 = record_generic_record_generic_StringStringNode1ListStringNode1Fun2_newNode((struct String){.ptr = "add", .len = 3}, list_);
    node_2 = call_16;
    fun_2 = (struct StringStringFun1){.fun = record_generic_record_generic_eta2_testRecusive_id, .env = NULL};
    call_17 = record_generic_record_generic_StringStringFun1StringNode1StringFun2_nodePrint(fun_2, node_2);
    if ((string_compare(call_17, (struct String){.ptr = "add(f(x) y)", .len = 11}) != 0)) milone_assert_error("record_generic/record_generic.milone", 48, 2);
    StringNode1_1 = (struct StringNode1_){.t0 = (struct String){.ptr = "mul", .len = 3}, .t1 = node_2.t1};
    other_ = StringNode1_1;
    fun_3 = (struct StringStringFun1){.fun = record_generic_record_generic_eta2_testRecusive_id_1, .env = NULL};
    call_18 = record_generic_record_generic_StringStringFun1StringNode1StringFun2_nodePrint(fun_3, other_);
    if ((string_compare(call_18, (struct String){.ptr = "mul(f(x) y)", .len = 11}) != 0)) milone_assert_error("record_generic/record_generic.milone", 53, 2);
    return;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    record_generic_record_generic_testGenericWrapper();
    record_generic_record_generic_testRecusive();
    return 0;
}
