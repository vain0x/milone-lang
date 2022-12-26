#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Int32MyNode1_Cons;

struct Int32Int32MyNode1ListTuple2_;

struct Int32MyNode1_;

typedef bool(*VoidConstPtrInt32MyNode1_Int32MyNode1_BoolFunPtr3)(void const *, struct Int32MyNode1_, struct Int32MyNode1_);

struct Int32MyNode1_Int32MyNode1_BoolFun2;

struct Int32Int32Tuple2_;

struct MyIntOption_;

struct MyIntOptionMyIntOptionTuple2_;

struct MyValue_;

struct MyValueMyValueTuple2_;

struct MyResult_;

struct MyResultMyResultTuple2_;

struct Int32MyNode1Int32MyNode1Tuple2_;

struct Int32MyNode1_Cons;

bool MiloneDerive_ListEqual_listEqual(struct Int32MyNode1_Cons const *, struct Int32MyNode1_Cons const *);

bool MiloneDerive_TupleEqual_tuple2Equal(struct Int32Int32MyNode1ListTuple2_ l_8, struct Int32Int32MyNode1ListTuple2_ r_8);

bool MiloneDerive_ListEqual_eta3_listEqual_MyNodeEqual(void const *env_, struct Int32MyNode1_ arg_, struct Int32MyNode1_ arg_1);

bool Std_Equal_Int32MyNode1Int32MyNode1BoolFun2Int32MyNode1ListInt32MyNode1ListBoolFun3_genericListEqual(struct Int32MyNode1_Int32MyNode1_BoolFun2, struct Int32MyNode1_Cons const *, struct Int32MyNode1_Cons const *);

bool MiloneDerive_ListEqual_listEqual(struct Int32MyNode1_Cons const *l_14, struct Int32MyNode1_Cons const *r_14);

bool union_equal_union_equal_MyBoolEqual(int32_t l_, int32_t r_);

bool union_equal_union_equal_MyIntOptionEqual(struct MyIntOption_ l_1, struct MyIntOption_ r_1);

bool union_equal_union_equal_MyValueEqual(struct MyValue_ l_11, struct MyValue_ r_11);

bool union_equal_union_equal_MyResultEqual(struct MyResult_ l_3, struct MyResult_ r_3);

bool MiloneDerive_TupleEqual_tuple2Equal(struct Int32Int32MyNode1ListTuple2_, struct Int32Int32MyNode1ListTuple2_);

bool union_equal_union_equal_MyNodeEqual(struct Int32MyNode1_ l_6, struct Int32MyNode1_ r_6);

void union_equal_union_equal_testMyBool(void);

void union_equal_union_equal_testMyInt(void);

void union_equal_union_equal_testMyResult(void);

void union_equal_union_equal_testMyNode(void);

int main(int argc, char **argv);

struct Int32Int32MyNode1ListTuple2_ {
    int32_t t0;
    struct Int32MyNode1_Cons const *t1;
};

enum Int32MyNode1_Discriminant {
    Int32MyNode1_MyNode,
};

struct Int32MyNode1_ {
    enum Int32MyNode1_Discriminant discriminant;
    union {
        struct Int32Int32MyNode1ListTuple2_ Int32MyNode1_MyNode;
    };
};

struct Int32MyNode1_Int32MyNode1_BoolFun2 {
    VoidConstPtrInt32MyNode1_Int32MyNode1_BoolFunPtr3 fun;
    void const *env;
};

struct Int32Int32Tuple2_ {
    int32_t t0;
    int32_t t1;
};

enum MyIntOption_Discriminant {
    MyIntOption_MySome,
    MyIntOption_MyNone,
};

struct MyIntOption_ {
    enum MyIntOption_Discriminant discriminant;
    union {
        int32_t MyIntOption_MySome;
    };
};

struct MyIntOptionMyIntOptionTuple2_ {
    struct MyIntOption_ t0;
    struct MyIntOption_ t1;
};

enum MyValue_Discriminant {
    MyValue_MyUnit,
    MyValue_MyInt,
    MyValue_MyString,
};

struct MyValue_ {
    enum MyValue_Discriminant discriminant;
    union {
        int32_t MyValue_MyInt;
        struct String MyValue_MyString;
    };
};

struct MyValueMyValueTuple2_ {
    struct MyValue_ t0;
    struct MyValue_ t1;
};

enum MyResult_Discriminant {
    MyResult_MyOk,
    MyResult_MyErr,
};

struct MyResult_ {
    enum MyResult_Discriminant discriminant;
    union {
        struct MyValue_ MyResult_MyOk;
        struct String MyResult_MyErr;
    };
};

struct MyResultMyResultTuple2_ {
    struct MyResult_ t0;
    struct MyResult_ t1;
};

struct Int32MyNode1Int32MyNode1Tuple2_ {
    struct Int32MyNode1_ t0;
    struct Int32MyNode1_ t1;
};

struct Int32MyNode1_Cons {
    struct Int32MyNode1_ head;
    struct Int32MyNode1_Cons const *tail;
};

bool MiloneDerive_TupleEqual_tuple2Equal(struct Int32Int32MyNode1ListTuple2_ l_8, struct Int32Int32MyNode1ListTuple2_ r_8) {
    int32_t l_9;
    int32_t r_9;
    struct Int32MyNode1_Cons const *l_10;
    struct Int32MyNode1_Cons const *r_10;
    bool call_;
    l_9 = l_8.t0;
    l_10 = l_8.t1;
    r_9 = r_8.t0;
    r_10 = r_8.t1;
    call_ = MiloneDerive_ListEqual_listEqual(l_10, r_10);
    return ((l_9 == r_9) & call_);
}

bool MiloneDerive_ListEqual_eta3_listEqual_MyNodeEqual(void const *env_, struct Int32MyNode1_ arg_, struct Int32MyNode1_ arg_1) {
    bool call_1;
    call_1 = union_equal_union_equal_MyNodeEqual(arg_, arg_1);
    return call_1;
}

bool MiloneDerive_ListEqual_listEqual(struct Int32MyNode1_Cons const *l_14, struct Int32MyNode1_Cons const *r_14) {
    struct Int32MyNode1_Int32MyNode1_BoolFun2 fun_;
    bool call_2;
    fun_ = (struct Int32MyNode1_Int32MyNode1_BoolFun2){.fun = MiloneDerive_ListEqual_eta3_listEqual_MyNodeEqual, .env = NULL};
    call_2 = Std_Equal_Int32MyNode1Int32MyNode1BoolFun2Int32MyNode1ListInt32MyNode1ListBoolFun3_genericListEqual(fun_, l_14, r_14);
    return call_2;
}

bool union_equal_union_equal_MyBoolEqual(int32_t l_, int32_t r_) {
    bool match_;
    struct Int32Int32Tuple2_ Int32Int32Tuple2_;
    Int32Int32Tuple2_ = (struct Int32Int32Tuple2_){.t0 = l_, .t1 = r_};
    if ((Int32Int32Tuple2_.t0 != 0)) goto next_2;
    if ((Int32Int32Tuple2_.t1 != 0)) goto next_2;
    match_ = true;
    goto end_match_1;
next_2:;
    if ((Int32Int32Tuple2_.t0 != 1)) goto next_3;
    if ((Int32Int32Tuple2_.t1 != 1)) goto next_3;
    match_ = true;
    goto end_match_1;
next_3:;
    match_ = false;
    goto end_match_1;
next_4:;
end_match_1:;
    return match_;
}

bool union_equal_union_equal_MyIntOptionEqual(struct MyIntOption_ l_1, struct MyIntOption_ r_1) {
    int32_t l_2;
    int32_t r_2;
    bool match_1;
    struct MyIntOptionMyIntOptionTuple2_ MyIntOptionMyIntOptionTuple2_;
    MyIntOptionMyIntOptionTuple2_ = (struct MyIntOptionMyIntOptionTuple2_){.t0 = l_1, .t1 = r_1};
    if ((MyIntOptionMyIntOptionTuple2_.t0.discriminant != MyIntOption_MySome)) goto next_2;
    l_2 = MyIntOptionMyIntOptionTuple2_.t0.MyIntOption_MySome;
    if ((MyIntOptionMyIntOptionTuple2_.t1.discriminant != MyIntOption_MySome)) goto next_2;
    r_2 = MyIntOptionMyIntOptionTuple2_.t1.MyIntOption_MySome;
    match_1 = (l_2 == r_2);
    goto end_match_1;
next_2:;
    if ((MyIntOptionMyIntOptionTuple2_.t0.discriminant != MyIntOption_MyNone)) goto next_3;
    if ((MyIntOptionMyIntOptionTuple2_.t1.discriminant != MyIntOption_MyNone)) goto next_3;
    match_1 = true;
    goto end_match_1;
next_3:;
    match_1 = false;
    goto end_match_1;
next_4:;
end_match_1:;
    return match_1;
}

bool union_equal_union_equal_MyValueEqual(struct MyValue_ l_11, struct MyValue_ r_11) {
    int32_t l_12;
    int32_t r_12;
    struct String l_13;
    struct String r_13;
    bool match_2;
    struct MyValueMyValueTuple2_ MyValueMyValueTuple2_;
    MyValueMyValueTuple2_ = (struct MyValueMyValueTuple2_){.t0 = l_11, .t1 = r_11};
    if ((MyValueMyValueTuple2_.t0.discriminant != MyValue_MyUnit)) goto next_2;
    if ((MyValueMyValueTuple2_.t1.discriminant != MyValue_MyUnit)) goto next_2;
    match_2 = true;
    goto end_match_1;
next_2:;
    if ((MyValueMyValueTuple2_.t0.discriminant != MyValue_MyInt)) goto next_3;
    l_12 = MyValueMyValueTuple2_.t0.MyValue_MyInt;
    if ((MyValueMyValueTuple2_.t1.discriminant != MyValue_MyInt)) goto next_3;
    r_12 = MyValueMyValueTuple2_.t1.MyValue_MyInt;
    match_2 = (l_12 == r_12);
    goto end_match_1;
next_3:;
    if ((MyValueMyValueTuple2_.t0.discriminant != MyValue_MyString)) goto next_4;
    l_13 = MyValueMyValueTuple2_.t0.MyValue_MyString;
    if ((MyValueMyValueTuple2_.t1.discriminant != MyValue_MyString)) goto next_4;
    r_13 = MyValueMyValueTuple2_.t1.MyValue_MyString;
    match_2 = (string_compare(l_13, r_13) == 0);
    goto end_match_1;
next_4:;
    match_2 = false;
    goto end_match_1;
next_5:;
end_match_1:;
    return match_2;
}

bool union_equal_union_equal_MyResultEqual(struct MyResult_ l_3, struct MyResult_ r_3) {
    struct MyValue_ l_4;
    struct MyValue_ r_4;
    struct String l_5;
    struct String r_5;
    bool match_3;
    struct MyResultMyResultTuple2_ MyResultMyResultTuple2_;
    bool call_3;
    MyResultMyResultTuple2_ = (struct MyResultMyResultTuple2_){.t0 = l_3, .t1 = r_3};
    if ((MyResultMyResultTuple2_.t0.discriminant != MyResult_MyOk)) goto next_2;
    l_4 = MyResultMyResultTuple2_.t0.MyResult_MyOk;
    if ((MyResultMyResultTuple2_.t1.discriminant != MyResult_MyOk)) goto next_2;
    r_4 = MyResultMyResultTuple2_.t1.MyResult_MyOk;
    call_3 = union_equal_union_equal_MyValueEqual(l_4, r_4);
    match_3 = call_3;
    goto end_match_1;
next_2:;
    if ((MyResultMyResultTuple2_.t0.discriminant != MyResult_MyErr)) goto next_3;
    l_5 = MyResultMyResultTuple2_.t0.MyResult_MyErr;
    if ((MyResultMyResultTuple2_.t1.discriminant != MyResult_MyErr)) goto next_3;
    r_5 = MyResultMyResultTuple2_.t1.MyResult_MyErr;
    match_3 = (string_compare(l_5, r_5) == 0);
    goto end_match_1;
next_3:;
    match_3 = false;
    goto end_match_1;
next_4:;
end_match_1:;
    return match_3;
}

bool union_equal_union_equal_MyNodeEqual(struct Int32MyNode1_ l_6, struct Int32MyNode1_ r_6) {
    struct Int32Int32MyNode1ListTuple2_ l_7;
    struct Int32Int32MyNode1ListTuple2_ r_7;
    bool match_4;
    struct Int32MyNode1Int32MyNode1Tuple2_ Int32MyNode1Int32MyNode1Tuple2_;
    bool call_4;
    Int32MyNode1Int32MyNode1Tuple2_ = (struct Int32MyNode1Int32MyNode1Tuple2_){.t0 = l_6, .t1 = r_6};
    l_7 = Int32MyNode1Int32MyNode1Tuple2_.t0.Int32MyNode1_MyNode;
    r_7 = Int32MyNode1Int32MyNode1Tuple2_.t1.Int32MyNode1_MyNode;
    call_4 = MiloneDerive_TupleEqual_tuple2Equal(l_7, r_7);
    match_4 = call_4;
    goto end_match_1;
next_2:;
    match_4 = false;
    goto end_match_1;
next_3:;
end_match_1:;
    return match_4;
}

void union_equal_union_equal_testMyBool(void) {
    int32_t t_;
    int32_t f_;
    bool call_5;
    bool call_6;
    bool call_7;
    bool call_8;
    t_ = 0;
    call_5 = union_equal_union_equal_MyBoolEqual(t_, 0);
    if ((!(call_5))) milone_assert_error("union_equal/union_equal.milone", 11, 2);
    call_6 = union_equal_union_equal_MyBoolEqual(t_, 1);
    if (call_6) milone_assert_error("union_equal/union_equal.milone", 12, 2);
    f_ = 1;
    call_7 = union_equal_union_equal_MyBoolEqual(t_, f_);
    if (call_7) milone_assert_error("union_equal/union_equal.milone", 15, 2);
    call_8 = union_equal_union_equal_MyBoolEqual(f_, 1);
    if ((!(call_8))) milone_assert_error("union_equal/union_equal.milone", 16, 2);
    return;
}

void union_equal_union_equal_testMyInt(void) {
    struct MyIntOption_ s_;
    struct MyIntOption_ n_;
    struct MyIntOption_ variant_;
    struct MyIntOption_ variant_1;
    bool call_9;
    struct MyIntOption_ variant_2;
    bool call_10;
    bool call_11;
    bool call_12;
    bool call_13;
    variant_ = (struct MyIntOption_){.discriminant = MyIntOption_MySome, .MyIntOption_MySome = 2};
    s_ = variant_;
    variant_1 = (struct MyIntOption_){.discriminant = MyIntOption_MySome, .MyIntOption_MySome = 2};
    call_9 = union_equal_union_equal_MyIntOptionEqual(s_, variant_1);
    if ((!(call_9))) milone_assert_error("union_equal/union_equal.milone", 25, 2);
    variant_2 = (struct MyIntOption_){.discriminant = MyIntOption_MySome, .MyIntOption_MySome = 3};
    call_10 = union_equal_union_equal_MyIntOptionEqual(s_, variant_2);
    if (call_10) milone_assert_error("union_equal/union_equal.milone", 26, 2);
    call_11 = union_equal_union_equal_MyIntOptionEqual(s_, (struct MyIntOption_){.discriminant = MyIntOption_MyNone});
    if (call_11) milone_assert_error("union_equal/union_equal.milone", 27, 2);
    n_ = (struct MyIntOption_){.discriminant = MyIntOption_MyNone};
    call_12 = union_equal_union_equal_MyIntOptionEqual(s_, n_);
    if (call_12) milone_assert_error("union_equal/union_equal.milone", 30, 2);
    call_13 = union_equal_union_equal_MyIntOptionEqual(n_, (struct MyIntOption_){.discriminant = MyIntOption_MyNone});
    if ((!(call_13))) milone_assert_error("union_equal/union_equal.milone", 31, 2);
    return;
}

void union_equal_union_equal_testMyResult(void) {
    struct MyResult_ ok2_;
    struct MyResult_ hello_;
    struct MyValue_ variant_3;
    struct MyResult_ variant_4;
    struct MyValue_ variant_5;
    struct MyResult_ variant_6;
    bool call_14;
    struct MyValue_ variant_7;
    struct MyResult_ variant_8;
    bool call_15;
    struct MyResult_ variant_9;
    bool call_16;
    struct MyResult_ variant_10;
    bool call_17;
    struct MyValue_ variant_11;
    struct MyResult_ variant_12;
    struct MyValue_ variant_13;
    struct MyResult_ variant_14;
    bool call_18;
    bool call_19;
    struct MyResult_ variant_15;
    bool call_20;
    variant_3 = (struct MyValue_){.discriminant = MyValue_MyInt, .MyValue_MyInt = 2};
    variant_4 = (struct MyResult_){.discriminant = MyResult_MyOk, .MyResult_MyOk = variant_3};
    ok2_ = variant_4;
    variant_5 = (struct MyValue_){.discriminant = MyValue_MyInt, .MyValue_MyInt = 2};
    variant_6 = (struct MyResult_){.discriminant = MyResult_MyOk, .MyResult_MyOk = variant_5};
    call_14 = union_equal_union_equal_MyResultEqual(ok2_, variant_6);
    if ((!(call_14))) milone_assert_error("union_equal/union_equal.milone", 45, 2);
    variant_7 = (struct MyValue_){.discriminant = MyValue_MyInt, .MyValue_MyInt = 3};
    variant_8 = (struct MyResult_){.discriminant = MyResult_MyOk, .MyResult_MyOk = variant_7};
    call_15 = union_equal_union_equal_MyResultEqual(ok2_, variant_8);
    if (call_15) milone_assert_error("union_equal/union_equal.milone", 46, 2);
    variant_9 = (struct MyResult_){.discriminant = MyResult_MyOk, .MyResult_MyOk = (struct MyValue_){.discriminant = MyValue_MyUnit}};
    call_16 = union_equal_union_equal_MyResultEqual(ok2_, variant_9);
    if (call_16) milone_assert_error("union_equal/union_equal.milone", 47, 2);
    variant_10 = (struct MyResult_){.discriminant = MyResult_MyErr, .MyResult_MyErr = (struct String){.ptr = "", .len = 0}};
    call_17 = union_equal_union_equal_MyResultEqual(ok2_, variant_10);
    if (call_17) milone_assert_error("union_equal/union_equal.milone", 48, 2);
    variant_11 = (struct MyValue_){.discriminant = MyValue_MyString, .MyValue_MyString = (struct String){.ptr = "hello", .len = 5}};
    variant_12 = (struct MyResult_){.discriminant = MyResult_MyOk, .MyResult_MyOk = variant_11};
    hello_ = variant_12;
    variant_13 = (struct MyValue_){.discriminant = MyValue_MyString, .MyValue_MyString = (struct String){.ptr = "hello", .len = 5}};
    variant_14 = (struct MyResult_){.discriminant = MyResult_MyOk, .MyResult_MyOk = variant_13};
    call_18 = union_equal_union_equal_MyResultEqual(hello_, variant_14);
    if ((!(call_18))) milone_assert_error("union_equal/union_equal.milone", 51, 2);
    call_19 = union_equal_union_equal_MyResultEqual(hello_, ok2_);
    if (call_19) milone_assert_error("union_equal/union_equal.milone", 52, 2);
    variant_15 = (struct MyResult_){.discriminant = MyResult_MyErr, .MyResult_MyErr = (struct String){.ptr = "hello", .len = 5}};
    call_20 = union_equal_union_equal_MyResultEqual(hello_, variant_15);
    if (call_20) milone_assert_error("union_equal/union_equal.milone", 53, 2);
    return;
}

void union_equal_union_equal_testMyNode(void) {
    struct Int32MyNode1_ v_;
    struct Int32Int32MyNode1ListTuple2_ Int32Int32MyNode1ListTuple2_;
    struct Int32MyNode1_Cons const *list_;
    struct Int32Int32MyNode1ListTuple2_ Int32Int32MyNode1ListTuple2_1;
    struct Int32MyNode1_ variant_16;
    struct Int32MyNode1_Cons const *list_1;
    struct Int32Int32MyNode1ListTuple2_ Int32Int32MyNode1ListTuple2_2;
    struct Int32MyNode1_ variant_17;
    struct Int32MyNode1_ variant_18;
    bool call_21;
    struct Int32Int32MyNode1ListTuple2_ Int32Int32MyNode1ListTuple2_3;
    struct Int32MyNode1_ variant_19;
    bool call_22;
    Int32Int32MyNode1ListTuple2_1 = (struct Int32Int32MyNode1ListTuple2_){.t0 = 2, .t1 = NULL};
    variant_16 = (struct Int32MyNode1_){.discriminant = Int32MyNode1_MyNode, .Int32MyNode1_MyNode = Int32Int32MyNode1ListTuple2_1};
    Int32Int32MyNode1ListTuple2_2 = (struct Int32Int32MyNode1ListTuple2_){.t0 = 3, .t1 = NULL};
    variant_17 = (struct Int32MyNode1_){.discriminant = Int32MyNode1_MyNode, .Int32MyNode1_MyNode = Int32Int32MyNode1ListTuple2_2};
    list_1 = ((struct Int32MyNode1_Cons const *)milone_region_alloc(1, sizeof(struct Int32MyNode1_Cons)));
    (*(((struct Int32MyNode1_Cons *)list_1))) = (struct Int32MyNode1_Cons){.head = variant_17, .tail = NULL};
    list_ = ((struct Int32MyNode1_Cons const *)milone_region_alloc(1, sizeof(struct Int32MyNode1_Cons)));
    (*(((struct Int32MyNode1_Cons *)list_))) = (struct Int32MyNode1_Cons){.head = variant_16, .tail = list_1};
    Int32Int32MyNode1ListTuple2_ = (struct Int32Int32MyNode1ListTuple2_){.t0 = 5, .t1 = list_};
    variant_18 = (struct Int32MyNode1_){.discriminant = Int32MyNode1_MyNode, .Int32MyNode1_MyNode = Int32Int32MyNode1ListTuple2_};
    v_ = variant_18;
    call_21 = union_equal_union_equal_MyNodeEqual(v_, v_);
    if ((!(call_21))) milone_assert_error("union_equal/union_equal.milone", 62, 2);
    Int32Int32MyNode1ListTuple2_3 = (struct Int32Int32MyNode1ListTuple2_){.t0 = 5, .t1 = NULL};
    variant_19 = (struct Int32MyNode1_){.discriminant = Int32MyNode1_MyNode, .Int32MyNode1_MyNode = Int32Int32MyNode1ListTuple2_3};
    call_22 = union_equal_union_equal_MyNodeEqual(v_, variant_19);
    if (call_22) milone_assert_error("union_equal/union_equal.milone", 63, 2);
    return;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    union_equal_union_equal_testMyBool();
    union_equal_union_equal_testMyInt();
    union_equal_union_equal_testMyResult();
    union_equal_union_equal_testMyNode();
    return 0;
}
