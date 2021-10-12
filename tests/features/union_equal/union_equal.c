#include "milone.h"

struct MyBool_;

struct MyBoolMyBoolTuple2_;

struct MyIntOption_;

struct MyIntOptionMyIntOptionTuple2_;

struct MyValue_;

struct MyValueMyValueTuple2_;

struct MyResult_;

struct MyResultMyResultTuple2_;

bool MyBoolEqual_(struct MyBool_ l_, struct MyBool_ r_);

bool MyIntOptionEqual_(struct MyIntOption_ l_1, struct MyIntOption_ r_1);

bool MyValueEqual_(struct MyValue_ l_6, struct MyValue_ r_6);

bool MyResultEqual_(struct MyResult_ l_3, struct MyResult_ r_3);

void testMyBool_(void);

void testMyInt_(void);

void testMyResult_(void);

int milone_main(void);

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

bool MyBoolEqual_(struct MyBool_ l_, struct MyBool_ r_) {
    bool match_;
    struct MyBoolMyBoolTuple2_ MyBoolMyBoolTuple2_ = (struct MyBoolMyBoolTuple2_){.t0 = l_, .t1 = r_};
    if ((MyBoolMyBoolTuple2_.t0.discriminant != MyTrue_)) goto next_2;
    if ((MyBoolMyBoolTuple2_.t1.discriminant != MyTrue_)) goto next_2;
    match_ = true;
    goto end_match_1;
next_2:;
    if ((MyBoolMyBoolTuple2_.t0.discriminant != MyFalse_)) goto next_3;
    if ((MyBoolMyBoolTuple2_.t1.discriminant != MyFalse_)) goto next_3;
    match_ = true;
    goto end_match_1;
next_3:;
    match_ = false;
    goto end_match_1;
next_4:;
end_match_1:;
    return match_;
}

bool MyIntOptionEqual_(struct MyIntOption_ l_1, struct MyIntOption_ r_1) {
    int r_2;
    int l_2;
    bool match_1;
    struct MyIntOptionMyIntOptionTuple2_ MyIntOptionMyIntOptionTuple2_ = (struct MyIntOptionMyIntOptionTuple2_){.t0 = l_1, .t1 = r_1};
    if ((MyIntOptionMyIntOptionTuple2_.t0.discriminant != MySome_)) goto next_6;
    l_2 = MyIntOptionMyIntOptionTuple2_.t0.MySome_;
    if ((MyIntOptionMyIntOptionTuple2_.t1.discriminant != MySome_)) goto next_6;
    r_2 = MyIntOptionMyIntOptionTuple2_.t1.MySome_;
    match_1 = (l_2 == r_2);
    goto end_match_5;
next_6:;
    if ((MyIntOptionMyIntOptionTuple2_.t0.discriminant != MyNone_)) goto next_7;
    if ((MyIntOptionMyIntOptionTuple2_.t1.discriminant != MyNone_)) goto next_7;
    match_1 = true;
    goto end_match_5;
next_7:;
    match_1 = false;
    goto end_match_5;
next_8:;
end_match_5:;
    return match_1;
}

bool MyValueEqual_(struct MyValue_ l_6, struct MyValue_ r_6) {
    struct String r_8;
    struct String l_8;
    int r_7;
    int l_7;
    bool match_2;
    struct MyValueMyValueTuple2_ MyValueMyValueTuple2_ = (struct MyValueMyValueTuple2_){.t0 = l_6, .t1 = r_6};
    if ((MyValueMyValueTuple2_.t0.discriminant != MyUnit_)) goto next_10;
    if ((MyValueMyValueTuple2_.t1.discriminant != MyUnit_)) goto next_10;
    match_2 = true;
    goto end_match_9;
next_10:;
    if ((MyValueMyValueTuple2_.t0.discriminant != MyInt_)) goto next_11;
    l_7 = MyValueMyValueTuple2_.t0.MyInt_;
    if ((MyValueMyValueTuple2_.t1.discriminant != MyInt_)) goto next_11;
    r_7 = MyValueMyValueTuple2_.t1.MyInt_;
    match_2 = (l_7 == r_7);
    goto end_match_9;
next_11:;
    if ((MyValueMyValueTuple2_.t0.discriminant != MyString_)) goto next_12;
    l_8 = MyValueMyValueTuple2_.t0.MyString_;
    if ((MyValueMyValueTuple2_.t1.discriminant != MyString_)) goto next_12;
    r_8 = MyValueMyValueTuple2_.t1.MyString_;
    match_2 = (str_compare(l_8, r_8) == 0);
    goto end_match_9;
next_12:;
    match_2 = false;
    goto end_match_9;
next_13:;
end_match_9:;
    return match_2;
}

bool MyResultEqual_(struct MyResult_ l_3, struct MyResult_ r_3) {
    struct String r_5;
    struct String l_5;
    struct MyValue_ r_4;
    struct MyValue_ l_4;
    bool match_3;
    struct MyResultMyResultTuple2_ MyResultMyResultTuple2_ = (struct MyResultMyResultTuple2_){.t0 = l_3, .t1 = r_3};
    if ((MyResultMyResultTuple2_.t0.discriminant != MyOk_)) goto next_15;
    l_4 = MyResultMyResultTuple2_.t0.MyOk_;
    if ((MyResultMyResultTuple2_.t1.discriminant != MyOk_)) goto next_15;
    r_4 = MyResultMyResultTuple2_.t1.MyOk_;
    bool call_ = MyValueEqual_(l_4, r_4);
    match_3 = call_;
    goto end_match_14;
next_15:;
    if ((MyResultMyResultTuple2_.t0.discriminant != MyErr_)) goto next_16;
    l_5 = MyResultMyResultTuple2_.t0.MyErr_;
    if ((MyResultMyResultTuple2_.t1.discriminant != MyErr_)) goto next_16;
    r_5 = MyResultMyResultTuple2_.t1.MyErr_;
    match_3 = (str_compare(l_5, r_5) == 0);
    goto end_match_14;
next_16:;
    match_3 = false;
    goto end_match_14;
next_17:;
end_match_14:;
    return match_3;
}

void testMyBool_(void) {
    struct MyBool_ t_ = (struct MyBool_){.discriminant = MyTrue_};
    bool call_1 = MyBoolEqual_(t_, (struct MyBool_){.discriminant = MyTrue_});
    milone_assert(call_1, 9, 2);
    bool call_2 = MyBoolEqual_(t_, (struct MyBool_){.discriminant = MyFalse_});
    milone_assert((!(call_2)), 10, 2);
    struct MyBool_ f_ = (struct MyBool_){.discriminant = MyFalse_};
    bool call_3 = MyBoolEqual_(t_, f_);
    milone_assert((!(call_3)), 13, 2);
    bool call_4 = MyBoolEqual_(f_, (struct MyBool_){.discriminant = MyFalse_});
    milone_assert(call_4, 14, 2);
    return;
}

void testMyInt_(void) {
    struct MyIntOption_ variant_ = (struct MyIntOption_){.discriminant = MySome_, .MySome_ = 2};
    struct MyIntOption_ s_ = variant_;
    struct MyIntOption_ variant_1 = (struct MyIntOption_){.discriminant = MySome_, .MySome_ = 2};
    bool call_5 = MyIntOptionEqual_(s_, variant_1);
    milone_assert(call_5, 23, 2);
    struct MyIntOption_ variant_2 = (struct MyIntOption_){.discriminant = MySome_, .MySome_ = 3};
    bool call_6 = MyIntOptionEqual_(s_, variant_2);
    milone_assert((!(call_6)), 24, 2);
    bool call_7 = MyIntOptionEqual_(s_, (struct MyIntOption_){.discriminant = MyNone_});
    milone_assert((!(call_7)), 25, 2);
    struct MyIntOption_ n_ = (struct MyIntOption_){.discriminant = MyNone_};
    bool call_8 = MyIntOptionEqual_(s_, n_);
    milone_assert((!(call_8)), 28, 2);
    bool call_9 = MyIntOptionEqual_(n_, (struct MyIntOption_){.discriminant = MyNone_});
    milone_assert(call_9, 29, 2);
    return;
}

void testMyResult_(void) {
    struct MyValue_ variant_3 = (struct MyValue_){.discriminant = MyInt_, .MyInt_ = 2};
    struct MyResult_ variant_4 = (struct MyResult_){.discriminant = MyOk_, .MyOk_ = variant_3};
    struct MyResult_ ok2_ = variant_4;
    struct MyValue_ variant_5 = (struct MyValue_){.discriminant = MyInt_, .MyInt_ = 2};
    struct MyResult_ variant_6 = (struct MyResult_){.discriminant = MyOk_, .MyOk_ = variant_5};
    bool call_10 = MyResultEqual_(ok2_, variant_6);
    milone_assert(call_10, 43, 2);
    struct MyValue_ variant_7 = (struct MyValue_){.discriminant = MyInt_, .MyInt_ = 3};
    struct MyResult_ variant_8 = (struct MyResult_){.discriminant = MyOk_, .MyOk_ = variant_7};
    bool call_11 = MyResultEqual_(ok2_, variant_8);
    milone_assert((!(call_11)), 44, 2);
    struct MyResult_ variant_9 = (struct MyResult_){.discriminant = MyOk_, .MyOk_ = (struct MyValue_){.discriminant = MyUnit_}};
    bool call_12 = MyResultEqual_(ok2_, variant_9);
    milone_assert((!(call_12)), 45, 2);
    struct MyResult_ variant_10 = (struct MyResult_){.discriminant = MyErr_, .MyErr_ = (struct String){.str = "", .len = 0}};
    bool call_13 = MyResultEqual_(ok2_, variant_10);
    milone_assert((!(call_13)), 46, 2);
    struct MyValue_ variant_11 = (struct MyValue_){.discriminant = MyString_, .MyString_ = (struct String){.str = "hello", .len = 5}};
    struct MyResult_ variant_12 = (struct MyResult_){.discriminant = MyOk_, .MyOk_ = variant_11};
    struct MyResult_ hello_ = variant_12;
    struct MyValue_ variant_13 = (struct MyValue_){.discriminant = MyString_, .MyString_ = (struct String){.str = "hello", .len = 5}};
    struct MyResult_ variant_14 = (struct MyResult_){.discriminant = MyOk_, .MyOk_ = variant_13};
    bool call_14 = MyResultEqual_(hello_, variant_14);
    milone_assert(call_14, 49, 2);
    bool call_15 = MyResultEqual_(hello_, ok2_);
    milone_assert((!(call_15)), 50, 2);
    struct MyResult_ variant_15 = (struct MyResult_){.discriminant = MyErr_, .MyErr_ = (struct String){.str = "hello", .len = 5}};
    bool call_16 = MyResultEqual_(hello_, variant_15);
    milone_assert((!(call_16)), 51, 2);
    return;
}

int milone_main(void) {
    testMyBool_();
    testMyInt_();
    testMyResult_();
    return 0;
}
