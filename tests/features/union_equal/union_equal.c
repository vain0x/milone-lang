#include <milone.h>

struct IntMyNode1_List;

struct IntIntMyNode1ListTuple2_;

struct IntMyNode1_;

typedef bool(*VoidConstPtrIntMyNode1_IntMyNode1_BoolFunPtr3)(void const*, struct IntMyNode1_, struct IntMyNode1_);

struct IntMyNode1_IntMyNode1_BoolFun2;

struct MyBool_;

struct MyBoolMyBoolTuple2_;

struct MyIntOption_;

struct MyIntOptionMyIntOptionTuple2_;

struct MyValue_;

struct MyValueMyValueTuple2_;

struct MyResult_;

struct MyResultMyResultTuple2_;

struct IntMyNode1IntMyNode1Tuple2_;

struct IntMyNode1_List;

bool MiloneDerive_ListEqual_listEqual(struct IntMyNode1_List const* , struct IntMyNode1_List const* );

bool MiloneDerive_TupleEqual_tuple2Equal(struct IntIntMyNode1ListTuple2_ l_8, struct IntIntMyNode1ListTuple2_ r_8);

bool MiloneDerive_ListEqual_eta3_listEqual_MyNodeEqual(void const* env_, struct IntMyNode1_ arg_, struct IntMyNode1_ arg_1);

bool MiloneDerive_ListEqual_eta3_listEqual_MyNodeEqual(void const* , struct IntMyNode1_ , struct IntMyNode1_ );

bool Std_Equal_IntMyNode1IntMyNode1BoolFun2IntMyNode1ListIntMyNode1ListBoolFun3_genericListEqual(struct IntMyNode1_IntMyNode1_BoolFun2 , struct IntMyNode1_List const* , struct IntMyNode1_List const* );

bool MiloneDerive_ListEqual_listEqual(struct IntMyNode1_List const* l_14, struct IntMyNode1_List const* r_14);

bool union_equal_union_equal_MyBoolEqual(struct MyBool_ l_, struct MyBool_ r_);

bool union_equal_union_equal_MyIntOptionEqual(struct MyIntOption_ l_1, struct MyIntOption_ r_1);

bool union_equal_union_equal_MyValueEqual(struct MyValue_ l_11, struct MyValue_ r_11);

bool union_equal_union_equal_MyResultEqual(struct MyResult_ l_3, struct MyResult_ r_3);

bool MiloneDerive_TupleEqual_tuple2Equal(struct IntIntMyNode1ListTuple2_ , struct IntIntMyNode1ListTuple2_ );

bool union_equal_union_equal_MyNodeEqual(struct IntMyNode1_ l_6, struct IntMyNode1_ r_6);

void union_equal_union_equal_testMyBool(void);

void union_equal_union_equal_testMyInt(void);

void union_equal_union_equal_testMyResult(void);

void union_equal_union_equal_testMyNode(void);

int main(int argc, char** argv);

struct IntIntMyNode1ListTuple2_ {
    int t0;
    struct IntMyNode1_List const* t1;
};

enum IntMyNode1_Discriminant {
    MyNode_,
};

struct IntMyNode1_ {
    enum IntMyNode1_Discriminant discriminant;
    union {
        struct IntIntMyNode1ListTuple2_ MyNode_;
    };
};

struct IntMyNode1_IntMyNode1_BoolFun2 {
    VoidConstPtrIntMyNode1_IntMyNode1_BoolFunPtr3 fun;
    void const* env;
};

enum MyBool_Discriminant {
    MyTrue_,
    MyFalse_,
};

struct MyBool_ {
    enum MyBool_Discriminant discriminant;
};

struct MyBoolMyBoolTuple2_ {
    struct MyBool_ t0;
    struct MyBool_ t1;
};

enum MyIntOption_Discriminant {
    MySome_,
    MyNone_,
};

struct MyIntOption_ {
    enum MyIntOption_Discriminant discriminant;
    union {
        int MySome_;
    };
};

struct MyIntOptionMyIntOptionTuple2_ {
    struct MyIntOption_ t0;
    struct MyIntOption_ t1;
};

enum MyValue_Discriminant {
    MyUnit_,
    MyInt_,
    MyString_,
};

struct MyValue_ {
    enum MyValue_Discriminant discriminant;
    union {
        int MyInt_;
        struct String MyString_;
    };
};

struct MyValueMyValueTuple2_ {
    struct MyValue_ t0;
    struct MyValue_ t1;
};

enum MyResult_Discriminant {
    MyOk_,
    MyErr_,
};

struct MyResult_ {
    enum MyResult_Discriminant discriminant;
    union {
        struct MyValue_ MyOk_;
        struct String MyErr_;
    };
};

struct MyResultMyResultTuple2_ {
    struct MyResult_ t0;
    struct MyResult_ t1;
};

struct IntMyNode1IntMyNode1Tuple2_ {
    struct IntMyNode1_ t0;
    struct IntMyNode1_ t1;
};

struct IntMyNode1_List {
    struct IntMyNode1_ head;
    struct IntMyNode1_List const* tail;
};

bool MiloneDerive_TupleEqual_tuple2Equal(struct IntIntMyNode1ListTuple2_ l_8, struct IntIntMyNode1ListTuple2_ r_8) {
    int l_9 = l_8.t0;
    struct IntMyNode1_List const* l_10 = l_8.t1;
    int r_9 = r_8.t0;
    struct IntMyNode1_List const* r_10 = r_8.t1;
    bool call_ = MiloneDerive_ListEqual_listEqual(l_10, r_10);
    return ((l_9 == r_9) & call_);
}

bool MiloneDerive_ListEqual_eta3_listEqual_MyNodeEqual(void const* env_, struct IntMyNode1_ arg_, struct IntMyNode1_ arg_1) {
    bool call_1 = union_equal_union_equal_MyNodeEqual(arg_, arg_1);
    return call_1;
}

bool MiloneDerive_ListEqual_listEqual(struct IntMyNode1_List const* l_14, struct IntMyNode1_List const* r_14) {
    struct IntMyNode1_IntMyNode1_BoolFun2 fun_ = (struct IntMyNode1_IntMyNode1_BoolFun2){.fun = MiloneDerive_ListEqual_eta3_listEqual_MyNodeEqual, .env = NULL};
    bool call_2 = Std_Equal_IntMyNode1IntMyNode1BoolFun2IntMyNode1ListIntMyNode1ListBoolFun3_genericListEqual(fun_, l_14, r_14);
    return call_2;
}

bool union_equal_union_equal_MyBoolEqual(struct MyBool_ l_, struct MyBool_ r_) {
    bool match_;
    struct MyBoolMyBoolTuple2_ MyBoolMyBoolTuple2_ = (struct MyBoolMyBoolTuple2_){.t0 = l_, .t1 = r_};
    if ((MyBoolMyBoolTuple2_.t0.discriminant != MyTrue_)) goto next_7;
    if ((MyBoolMyBoolTuple2_.t1.discriminant != MyTrue_)) goto next_7;
    match_ = true;
    goto end_match_6;
next_7:;
    if ((MyBoolMyBoolTuple2_.t0.discriminant != MyFalse_)) goto next_8;
    if ((MyBoolMyBoolTuple2_.t1.discriminant != MyFalse_)) goto next_8;
    match_ = true;
    goto end_match_6;
next_8:;
    match_ = false;
    goto end_match_6;
next_9:;
end_match_6:;
    return match_;
}

bool union_equal_union_equal_MyIntOptionEqual(struct MyIntOption_ l_1, struct MyIntOption_ r_1) {
    int r_2;
    int l_2;
    bool match_1;
    struct MyIntOptionMyIntOptionTuple2_ MyIntOptionMyIntOptionTuple2_ = (struct MyIntOptionMyIntOptionTuple2_){.t0 = l_1, .t1 = r_1};
    if ((MyIntOptionMyIntOptionTuple2_.t0.discriminant != MySome_)) goto next_11;
    l_2 = MyIntOptionMyIntOptionTuple2_.t0.MySome_;
    if ((MyIntOptionMyIntOptionTuple2_.t1.discriminant != MySome_)) goto next_11;
    r_2 = MyIntOptionMyIntOptionTuple2_.t1.MySome_;
    match_1 = (l_2 == r_2);
    goto end_match_10;
next_11:;
    if ((MyIntOptionMyIntOptionTuple2_.t0.discriminant != MyNone_)) goto next_12;
    if ((MyIntOptionMyIntOptionTuple2_.t1.discriminant != MyNone_)) goto next_12;
    match_1 = true;
    goto end_match_10;
next_12:;
    match_1 = false;
    goto end_match_10;
next_13:;
end_match_10:;
    return match_1;
}

bool union_equal_union_equal_MyValueEqual(struct MyValue_ l_11, struct MyValue_ r_11) {
    struct String r_13;
    struct String l_13;
    int r_12;
    int l_12;
    bool match_2;
    struct MyValueMyValueTuple2_ MyValueMyValueTuple2_ = (struct MyValueMyValueTuple2_){.t0 = l_11, .t1 = r_11};
    if ((MyValueMyValueTuple2_.t0.discriminant != MyUnit_)) goto next_15;
    if ((MyValueMyValueTuple2_.t1.discriminant != MyUnit_)) goto next_15;
    match_2 = true;
    goto end_match_14;
next_15:;
    if ((MyValueMyValueTuple2_.t0.discriminant != MyInt_)) goto next_16;
    l_12 = MyValueMyValueTuple2_.t0.MyInt_;
    if ((MyValueMyValueTuple2_.t1.discriminant != MyInt_)) goto next_16;
    r_12 = MyValueMyValueTuple2_.t1.MyInt_;
    match_2 = (l_12 == r_12);
    goto end_match_14;
next_16:;
    if ((MyValueMyValueTuple2_.t0.discriminant != MyString_)) goto next_17;
    l_13 = MyValueMyValueTuple2_.t0.MyString_;
    if ((MyValueMyValueTuple2_.t1.discriminant != MyString_)) goto next_17;
    r_13 = MyValueMyValueTuple2_.t1.MyString_;
    match_2 = (str_compare(l_13, r_13) == 0);
    goto end_match_14;
next_17:;
    match_2 = false;
    goto end_match_14;
next_18:;
end_match_14:;
    return match_2;
}

bool union_equal_union_equal_MyResultEqual(struct MyResult_ l_3, struct MyResult_ r_3) {
    struct String r_5;
    struct String l_5;
    struct MyValue_ r_4;
    struct MyValue_ l_4;
    bool match_3;
    struct MyResultMyResultTuple2_ MyResultMyResultTuple2_ = (struct MyResultMyResultTuple2_){.t0 = l_3, .t1 = r_3};
    if ((MyResultMyResultTuple2_.t0.discriminant != MyOk_)) goto next_20;
    l_4 = MyResultMyResultTuple2_.t0.MyOk_;
    if ((MyResultMyResultTuple2_.t1.discriminant != MyOk_)) goto next_20;
    r_4 = MyResultMyResultTuple2_.t1.MyOk_;
    bool call_3 = union_equal_union_equal_MyValueEqual(l_4, r_4);
    match_3 = call_3;
    goto end_match_19;
next_20:;
    if ((MyResultMyResultTuple2_.t0.discriminant != MyErr_)) goto next_21;
    l_5 = MyResultMyResultTuple2_.t0.MyErr_;
    if ((MyResultMyResultTuple2_.t1.discriminant != MyErr_)) goto next_21;
    r_5 = MyResultMyResultTuple2_.t1.MyErr_;
    match_3 = (str_compare(l_5, r_5) == 0);
    goto end_match_19;
next_21:;
    match_3 = false;
    goto end_match_19;
next_22:;
end_match_19:;
    return match_3;
}

bool union_equal_union_equal_MyNodeEqual(struct IntMyNode1_ l_6, struct IntMyNode1_ r_6) {
    struct IntIntMyNode1ListTuple2_ r_7;
    struct IntIntMyNode1ListTuple2_ l_7;
    bool match_4;
    struct IntMyNode1IntMyNode1Tuple2_ IntMyNode1IntMyNode1Tuple2_ = (struct IntMyNode1IntMyNode1Tuple2_){.t0 = l_6, .t1 = r_6};
    l_7 = IntMyNode1IntMyNode1Tuple2_.t0.MyNode_;
    r_7 = IntMyNode1IntMyNode1Tuple2_.t1.MyNode_;
    bool call_4 = MiloneDerive_TupleEqual_tuple2Equal(l_7, r_7);
    match_4 = call_4;
    goto end_match_23;
next_24:;
    match_4 = false;
    goto end_match_23;
next_25:;
end_match_23:;
    return match_4;
}

void union_equal_union_equal_testMyBool(void) {
    struct MyBool_ t_ = (struct MyBool_){.discriminant = MyTrue_};
    bool call_5 = union_equal_union_equal_MyBoolEqual(t_, (struct MyBool_){.discriminant = MyTrue_});
    milone_assert(call_5, (struct String){.str = "union_equal/union_equal.milone", .len = 30}, 11, 2);
    bool call_6 = union_equal_union_equal_MyBoolEqual(t_, (struct MyBool_){.discriminant = MyFalse_});
    milone_assert((!(call_6)), (struct String){.str = "union_equal/union_equal.milone", .len = 30}, 12, 2);
    struct MyBool_ f_ = (struct MyBool_){.discriminant = MyFalse_};
    bool call_7 = union_equal_union_equal_MyBoolEqual(t_, f_);
    milone_assert((!(call_7)), (struct String){.str = "union_equal/union_equal.milone", .len = 30}, 15, 2);
    bool call_8 = union_equal_union_equal_MyBoolEqual(f_, (struct MyBool_){.discriminant = MyFalse_});
    milone_assert(call_8, (struct String){.str = "union_equal/union_equal.milone", .len = 30}, 16, 2);
    return;
}

void union_equal_union_equal_testMyInt(void) {
    struct MyIntOption_ variant_ = (struct MyIntOption_){.discriminant = MySome_, .MySome_ = 2};
    struct MyIntOption_ s_ = variant_;
    struct MyIntOption_ variant_1 = (struct MyIntOption_){.discriminant = MySome_, .MySome_ = 2};
    bool call_9 = union_equal_union_equal_MyIntOptionEqual(s_, variant_1);
    milone_assert(call_9, (struct String){.str = "union_equal/union_equal.milone", .len = 30}, 25, 2);
    struct MyIntOption_ variant_2 = (struct MyIntOption_){.discriminant = MySome_, .MySome_ = 3};
    bool call_10 = union_equal_union_equal_MyIntOptionEqual(s_, variant_2);
    milone_assert((!(call_10)), (struct String){.str = "union_equal/union_equal.milone", .len = 30}, 26, 2);
    bool call_11 = union_equal_union_equal_MyIntOptionEqual(s_, (struct MyIntOption_){.discriminant = MyNone_});
    milone_assert((!(call_11)), (struct String){.str = "union_equal/union_equal.milone", .len = 30}, 27, 2);
    struct MyIntOption_ n_ = (struct MyIntOption_){.discriminant = MyNone_};
    bool call_12 = union_equal_union_equal_MyIntOptionEqual(s_, n_);
    milone_assert((!(call_12)), (struct String){.str = "union_equal/union_equal.milone", .len = 30}, 30, 2);
    bool call_13 = union_equal_union_equal_MyIntOptionEqual(n_, (struct MyIntOption_){.discriminant = MyNone_});
    milone_assert(call_13, (struct String){.str = "union_equal/union_equal.milone", .len = 30}, 31, 2);
    return;
}

void union_equal_union_equal_testMyResult(void) {
    struct MyValue_ variant_3 = (struct MyValue_){.discriminant = MyInt_, .MyInt_ = 2};
    struct MyResult_ variant_4 = (struct MyResult_){.discriminant = MyOk_, .MyOk_ = variant_3};
    struct MyResult_ ok2_ = variant_4;
    struct MyValue_ variant_5 = (struct MyValue_){.discriminant = MyInt_, .MyInt_ = 2};
    struct MyResult_ variant_6 = (struct MyResult_){.discriminant = MyOk_, .MyOk_ = variant_5};
    bool call_14 = union_equal_union_equal_MyResultEqual(ok2_, variant_6);
    milone_assert(call_14, (struct String){.str = "union_equal/union_equal.milone", .len = 30}, 45, 2);
    struct MyValue_ variant_7 = (struct MyValue_){.discriminant = MyInt_, .MyInt_ = 3};
    struct MyResult_ variant_8 = (struct MyResult_){.discriminant = MyOk_, .MyOk_ = variant_7};
    bool call_15 = union_equal_union_equal_MyResultEqual(ok2_, variant_8);
    milone_assert((!(call_15)), (struct String){.str = "union_equal/union_equal.milone", .len = 30}, 46, 2);
    struct MyResult_ variant_9 = (struct MyResult_){.discriminant = MyOk_, .MyOk_ = (struct MyValue_){.discriminant = MyUnit_}};
    bool call_16 = union_equal_union_equal_MyResultEqual(ok2_, variant_9);
    milone_assert((!(call_16)), (struct String){.str = "union_equal/union_equal.milone", .len = 30}, 47, 2);
    struct MyResult_ variant_10 = (struct MyResult_){.discriminant = MyErr_, .MyErr_ = (struct String){.str = "", .len = 0}};
    bool call_17 = union_equal_union_equal_MyResultEqual(ok2_, variant_10);
    milone_assert((!(call_17)), (struct String){.str = "union_equal/union_equal.milone", .len = 30}, 48, 2);
    struct MyValue_ variant_11 = (struct MyValue_){.discriminant = MyString_, .MyString_ = (struct String){.str = "hello", .len = 5}};
    struct MyResult_ variant_12 = (struct MyResult_){.discriminant = MyOk_, .MyOk_ = variant_11};
    struct MyResult_ hello_ = variant_12;
    struct MyValue_ variant_13 = (struct MyValue_){.discriminant = MyString_, .MyString_ = (struct String){.str = "hello", .len = 5}};
    struct MyResult_ variant_14 = (struct MyResult_){.discriminant = MyOk_, .MyOk_ = variant_13};
    bool call_18 = union_equal_union_equal_MyResultEqual(hello_, variant_14);
    milone_assert(call_18, (struct String){.str = "union_equal/union_equal.milone", .len = 30}, 51, 2);
    bool call_19 = union_equal_union_equal_MyResultEqual(hello_, ok2_);
    milone_assert((!(call_19)), (struct String){.str = "union_equal/union_equal.milone", .len = 30}, 52, 2);
    struct MyResult_ variant_15 = (struct MyResult_){.discriminant = MyErr_, .MyErr_ = (struct String){.str = "hello", .len = 5}};
    bool call_20 = union_equal_union_equal_MyResultEqual(hello_, variant_15);
    milone_assert((!(call_20)), (struct String){.str = "union_equal/union_equal.milone", .len = 30}, 53, 2);
    return;
}

void union_equal_union_equal_testMyNode(void) {
    struct IntIntMyNode1ListTuple2_ IntIntMyNode1ListTuple2_1 = (struct IntIntMyNode1ListTuple2_){.t0 = 2, .t1 = NULL};
    struct IntMyNode1_ variant_16 = (struct IntMyNode1_){.discriminant = MyNode_, .MyNode_ = IntIntMyNode1ListTuple2_1};
    struct IntIntMyNode1ListTuple2_ IntIntMyNode1ListTuple2_2 = (struct IntIntMyNode1ListTuple2_){.t0 = 3, .t1 = NULL};
    struct IntMyNode1_ variant_17 = (struct IntMyNode1_){.discriminant = MyNode_, .MyNode_ = IntIntMyNode1ListTuple2_2};
    struct IntMyNode1_List const* list_1 = milone_mem_alloc(1, sizeof(struct IntMyNode1_List));
    (*(((struct IntMyNode1_List*)list_1))) = (struct IntMyNode1_List){.head = variant_17, .tail = NULL};
    struct IntMyNode1_List const* list_ = milone_mem_alloc(1, sizeof(struct IntMyNode1_List));
    (*(((struct IntMyNode1_List*)list_))) = (struct IntMyNode1_List){.head = variant_16, .tail = list_1};
    struct IntIntMyNode1ListTuple2_ IntIntMyNode1ListTuple2_ = (struct IntIntMyNode1ListTuple2_){.t0 = 5, .t1 = list_};
    struct IntMyNode1_ variant_18 = (struct IntMyNode1_){.discriminant = MyNode_, .MyNode_ = IntIntMyNode1ListTuple2_};
    struct IntMyNode1_ v_ = variant_18;
    bool call_21 = union_equal_union_equal_MyNodeEqual(v_, v_);
    milone_assert(call_21, (struct String){.str = "union_equal/union_equal.milone", .len = 30}, 62, 2);
    struct IntIntMyNode1ListTuple2_ IntIntMyNode1ListTuple2_3 = (struct IntIntMyNode1ListTuple2_){.t0 = 5, .t1 = NULL};
    struct IntMyNode1_ variant_19 = (struct IntMyNode1_){.discriminant = MyNode_, .MyNode_ = IntIntMyNode1ListTuple2_3};
    bool call_22 = union_equal_union_equal_MyNodeEqual(v_, variant_19);
    milone_assert((!(call_22)), (struct String){.str = "union_equal/union_equal.milone", .len = 30}, 63, 2);
    return;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    union_equal_union_equal_testMyBool();
    union_equal_union_equal_testMyInt();
    union_equal_union_equal_testMyResult();
    union_equal_union_equal_testMyNode();
    return 0;
}
