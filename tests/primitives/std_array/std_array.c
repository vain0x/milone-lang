#include "milone.h"

struct IntConstPtrIntTuple2_;

struct IntOption_;

struct IntUnitFun1;

struct UnitConstPtrIntTuple2_;

struct IntIntFun1;

struct IntIntConstPtrIntTuple2Tuple2_;

struct IntIntConstPtrIntTuple2Tuple2Option_;

struct IntIntIntFun2;

struct IntIntOption_Fun1;

struct IntList;

struct IntList;

struct IntOption_ tryItem_(int , struct IntConstPtrIntTuple2_ );

int length_(struct IntConstPtrIntTuple2_ );

int get_(int i_8, struct IntConstPtrIntTuple2_ array_18);

void fun_1(int arg_54);

void fun_9(void const* env_5, int arg_11);

int fun_2(int n_);

int fun_10(void const* env_6, int arg_12);

struct UnitConstPtrIntTuple2_ init_1(int , struct IntUnitFun1 );

int length_1(struct UnitConstPtrIntTuple2_ );

struct IntConstPtrIntTuple2_ init_(int , struct IntIntFun1 );

void std_array_Program_initTest(void);

struct IntConstPtrIntTuple2_ MiloneStd_StdArray_range(int );

void std_array_Program_rangeTest(void);

int at_(int bad_, int i_9, struct IntConstPtrIntTuple2_ array_19);

struct IntConstPtrIntTuple2_ empty_2(void);

void std_array_Program_tryItemTest(void);

struct IntConstPtrIntTuple2_ slice_(int , int , struct IntConstPtrIntTuple2_ );

void std_array_Program_sliceTest(void);

int fun_3(int n_1);

int fun_11(void const* env_7, int arg_13);

struct IntIntConstPtrIntTuple2Tuple2Option_ uncons_(struct IntConstPtrIntTuple2_ );

struct IntConstPtrIntTuple2_ skip_(int , struct IntConstPtrIntTuple2_ );

void std_array_Program_unconsTest(void);

int fun_4(int i_10, int n_2);

int fun_12(void const* env_8, int arg_14, int arg_15);

struct IntConstPtrIntTuple2_ mapi_(struct IntIntIntFun2 , struct IntConstPtrIntTuple2_ );

void std_array_Program_mapTest(void);

struct IntOption_ fun_5(int n_3);

struct IntOption_ fun_13(void const* env_9, int arg_16);

struct IntOption_ fun_6(int arg_55);

struct IntOption_ fun_14(void const* env_10, int arg_17);

struct IntConstPtrIntTuple2_ choose_(struct IntIntOption_Fun1 , struct IntConstPtrIntTuple2_ );

void std_array_Program_chooseTest(void);

int fun_7(int state_2, int i_11);

int fun_15(void const* env_11, int arg_18, int arg_19);

int fold_(struct IntIntIntFun2 , int , struct IntConstPtrIntTuple2_ );

void std_array_Program_foldTest(void);

struct IntConstPtrIntTuple2_ ofList_(struct IntList const* );

void std_array_Program_ofListTest(void);

struct IntList const* toList_(struct IntConstPtrIntTuple2_ );

void std_array_Program_toListTest(void);

int milone_main(void);

struct IntConstPtrIntTuple2_ {
    int const* t0;
    int t1;
};

enum IntOption_Discriminant {
    None_,
    Some_,
};

struct IntOption_ {
    enum IntOption_Discriminant discriminant;
    union {
        int Some_;
    };
};

struct IntUnitFun1 {
    void(*fun)(void const*, int);
    void const* env;
};

struct UnitConstPtrIntTuple2_ {
    char const* t0;
    int t1;
};

struct IntIntFun1 {
    int(*fun)(void const*, int);
    void const* env;
};

struct IntIntConstPtrIntTuple2Tuple2_ {
    int t0;
    struct IntConstPtrIntTuple2_ t1;
};

enum IntIntConstPtrIntTuple2Tuple2Option_Discriminant {
    None_1,
    Some_1,
};

struct IntIntConstPtrIntTuple2Tuple2Option_ {
    enum IntIntConstPtrIntTuple2Tuple2Option_Discriminant discriminant;
    union {
        struct IntIntConstPtrIntTuple2Tuple2_ Some_1;
    };
};

struct IntIntIntFun2 {
    int(*fun)(void const*, int, int);
    void const* env;
};

struct IntIntOption_Fun1 {
    struct IntOption_(*fun)(void const*, int);
    void const* env;
};

struct IntList {
    int head;
    struct IntList const* tail;
};

int get_(int i_8, struct IntConstPtrIntTuple2_ array_18) {
    int it_;
    int match_3;
    struct IntOption_ call_57 = tryItem_(i_8, array_18);
    if ((call_57.discriminant != Some_)) goto next_78;
    it_ = call_57.Some_;
    match_3 = it_;
    goto end_match_77;
next_78:;
    if ((call_57.discriminant != None_)) goto next_79;
    int call_58 = length_(array_18);
    printf("out of range: i=%d len=%d\n", i_8, call_58);
    milone_assert(false, 9, 4);
    exit(1);
next_79:;
    exit(1);
end_match_77:;
    return match_3;
}

void fun_1(int arg_54) {
    milone_assert(false, 13, 45);
    return;
}

void fun_9(void const* env_5, int arg_11) {
    fun_1(arg_11);
    return;
}

int fun_2(int n_) {
    return ((n_ + 1) * 3);
}

int fun_10(void const* env_6, int arg_12) {
    int call_59 = fun_2(arg_12);
    return call_59;
}

void std_array_Program_initTest(void) {
    struct IntUnitFun1 fun_20 = (struct IntUnitFun1){.fun = fun_9, .env = NULL};
    struct UnitConstPtrIntTuple2_ call_60 = init_1(0, fun_20);
    struct UnitConstPtrIntTuple2_ emptyArray_ = call_60;
    int call_61 = length_1(emptyArray_);
    milone_assert((call_61 == 0), 14, 2);
    struct IntIntFun1 fun_21 = (struct IntIntFun1){.fun = fun_10, .env = NULL};
    struct IntConstPtrIntTuple2_ call_62 = init_(3, fun_21);
    struct IntConstPtrIntTuple2_ a369_ = call_62;
    int call_63 = length_(a369_);
    milone_assert((call_63 == 3), 17, 2);
    int call_64 = get_(0, a369_);
    milone_assert((call_64 == 3), 18, 2);
    int call_65 = get_(1, a369_);
    milone_assert((call_65 == 6), 19, 2);
    int call_66 = get_(2, a369_);
    milone_assert((call_66 == 9), 20, 2);
    return;
}

void std_array_Program_rangeTest(void) {
    struct IntConstPtrIntTuple2_ call_67 = MiloneStd_StdArray_range(3);
    struct IntConstPtrIntTuple2_ a012_ = call_67;
    int call_68 = length_(a012_);
    milone_assert((call_68 == 3), 25, 2);
    int call_69 = get_(0, a012_);
    milone_assert((call_69 == 0), 26, 2);
    int call_70 = get_(1, a012_);
    milone_assert((call_70 == 1), 27, 2);
    int call_71 = get_(2, a012_);
    milone_assert((call_71 == 2), 28, 2);
    return;
}

int at_(int bad_, int i_9, struct IntConstPtrIntTuple2_ array_19) {
    int it_1;
    int match_4;
    struct IntOption_ call_72 = tryItem_(i_9, array_19);
    if ((call_72.discriminant != Some_)) goto next_81;
    it_1 = call_72.Some_;
    match_4 = it_1;
    goto end_match_80;
next_81:;
    if ((call_72.discriminant != None_)) goto next_82;
    match_4 = bad_;
    goto end_match_80;
next_82:;
    exit(1);
end_match_80:;
    return match_4;
}

void std_array_Program_tryItemTest(void) {
    struct IntConstPtrIntTuple2_ call_73 = MiloneStd_StdArray_range(3);
    struct IntConstPtrIntTuple2_ a012_1 = call_73;
    int bad_ = -127;
    int call_74 = at_(bad_, -1, a012_1);
    milone_assert((call_74 == bad_), 40, 2);
    int call_75 = at_(bad_, 0, a012_1);
    milone_assert((call_75 == 0), 41, 2);
    int call_76 = at_(bad_, 2, a012_1);
    milone_assert((call_76 == 2), 42, 2);
    int call_77 = at_(bad_, 3, a012_1);
    milone_assert((call_77 == bad_), 43, 2);
    struct IntConstPtrIntTuple2_ call_78 = empty_2();
    struct IntConstPtrIntTuple2_ emptyArray_1 = call_78;
    int call_79 = at_(bad_, 0, emptyArray_1);
    milone_assert((call_79 == bad_), 46, 2);
    return;
}

void std_array_Program_sliceTest(void) {
    struct IntConstPtrIntTuple2_ call_80 = MiloneStd_StdArray_range(10);
    struct IntConstPtrIntTuple2_ ten_ = call_80;
    struct IntConstPtrIntTuple2_ call_81 = slice_(1, 4, ten_);
    struct IntConstPtrIntTuple2_ three_ = call_81;
    int call_82 = length_(three_);
    milone_assert((call_82 == 3), 52, 2);
    int call_83 = get_(0, three_);
    milone_assert((call_83 == 1), 53, 2);
    int call_84 = get_(2, three_);
    milone_assert((call_84 == 3), 54, 2);
    struct IntConstPtrIntTuple2_ call_85 = slice_(-1, 2, ten_);
    struct IntConstPtrIntTuple2_ behind_ = call_85;
    int call_86 = length_(behind_);
    milone_assert((call_86 == 2), 58, 2);
    int call_87 = get_(1, behind_);
    milone_assert((call_87 == 1), 59, 2);
    struct IntConstPtrIntTuple2_ call_88 = slice_(7, 11, ten_);
    struct IntConstPtrIntTuple2_ beyond_ = call_88;
    int call_89 = length_(beyond_);
    milone_assert((call_89 == 3), 63, 2);
    int call_90 = get_(0, beyond_);
    milone_assert((call_90 == 7), 64, 2);
    int call_91 = get_(2, beyond_);
    milone_assert((call_91 == 9), 65, 2);
    return;
}

int fun_3(int n_1) {
    return (n_1 + 1);
}

int fun_11(void const* env_7, int arg_13) {
    int call_92 = fun_3(arg_13);
    return call_92;
}

void std_array_Program_unconsTest(void) {
    struct IntConstPtrIntTuple2_ empty_;
    int n3_;
    struct IntConstPtrIntTuple2_ a23_;
    int n1_;
    struct IntIntFun1 fun_22 = (struct IntIntFun1){.fun = fun_11, .env = NULL};
    struct IntConstPtrIntTuple2_ call_93 = init_(3, fun_22);
    struct IntConstPtrIntTuple2_ a123_ = call_93;
    char match_5;
    struct IntIntConstPtrIntTuple2Tuple2Option_ call_94 = uncons_(a123_);
    if ((call_94.discriminant != None_1)) goto next_84;
    milone_assert(false, 71, 12);
    match_5 = 0;
    goto end_match_83;
next_84:;
    if ((call_94.discriminant != Some_1)) goto next_85;
    n1_ = call_94.Some_1.t0;
    a23_ = call_94.Some_1.t1;
    milone_assert((n1_ == 1), 73, 4);
    int call_95 = length_(a23_);
    milone_assert((call_95 == 2), 74, 4);
    char match_6;
    struct IntConstPtrIntTuple2_ call_96 = skip_(1, a23_);
    struct IntIntConstPtrIntTuple2Tuple2Option_ call_97 = uncons_(call_96);
    if ((call_97.discriminant != None_1)) goto next_87;
    milone_assert(false, 77, 14);
    match_6 = 0;
    goto end_match_86;
next_87:;
    if ((call_97.discriminant != Some_1)) goto next_88;
    n3_ = call_97.Some_1.t0;
    empty_ = call_97.Some_1.t1;
    milone_assert((n3_ == 3), 79, 6);
    int call_98 = length_(empty_);
    milone_assert((call_98 == 0), 80, 6);
    char switch_;
    struct IntIntConstPtrIntTuple2Tuple2Option_ call_99 = uncons_(empty_);
    switch (call_99.discriminant) {
        case None_1:
            goto clause_90;

        case Some_1:
            goto clause_91;

        default:
            exit(1);
    }
clause_90:;
    switch_ = 0;
    goto switch_next_89;
clause_91:;
    milone_assert(false, 84, 18);
    switch_ = 0;
    goto switch_next_89;
switch_next_89:;
    match_6 = 0;
    goto end_match_86;
next_88:;
    exit(1);
end_match_86:;
    match_5 = 0;
    goto end_match_83;
next_85:;
    exit(1);
end_match_83:;
    return;
}

int fun_4(int i_10, int n_2) {
    return ((i_10 * 10) + n_2);
}

int fun_12(void const* env_8, int arg_14, int arg_15) {
    int call_100 = fun_4(arg_14, arg_15);
    return call_100;
}

void std_array_Program_mapTest(void) {
    struct IntIntIntFun2 fun_23 = (struct IntIntIntFun2){.fun = fun_12, .env = NULL};
    struct IntConstPtrIntTuple2_ call_101 = MiloneStd_StdArray_range(3);
    struct IntConstPtrIntTuple2_ call_102 = mapi_(fun_23, call_101);
    struct IntConstPtrIntTuple2_ mapped_ = call_102;
    int call_103 = length_(mapped_);
    milone_assert((call_103 == 3), 90, 2);
    int call_104 = get_(0, mapped_);
    milone_assert((call_104 == 0), 91, 2);
    int call_105 = get_(1, mapped_);
    milone_assert((call_105 == 11), 92, 2);
    int call_106 = get_(2, mapped_);
    milone_assert((call_106 == 22), 93, 2);
    return;
}

struct IntOption_ fun_5(int n_3) {
    struct IntOption_ if_20;
    if (((n_3 % 2) == 0)) {
        goto then_93;
    } else {
        goto else_94;
    }
then_93:;
    struct IntOption_ variant_3 = (struct IntOption_){.discriminant = Some_, .Some_ = (n_3 * 2)};
    if_20 = variant_3;
    goto if_next_92;
else_94:;
    if_20 = (struct IntOption_){.discriminant = None_};
    goto if_next_92;
if_next_92:;
    return if_20;
}

struct IntOption_ fun_13(void const* env_9, int arg_16) {
    struct IntOption_ call_107 = fun_5(arg_16);
    return call_107;
}

struct IntOption_ fun_6(int arg_55) {
    return (struct IntOption_){.discriminant = None_};
}

struct IntOption_ fun_14(void const* env_10, int arg_17) {
    struct IntOption_ call_108 = fun_6(arg_17);
    return call_108;
}

void std_array_Program_chooseTest(void) {
    struct IntIntOption_Fun1 fun_24 = (struct IntIntOption_Fun1){.fun = fun_13, .env = NULL};
    struct IntConstPtrIntTuple2_ call_109 = MiloneStd_StdArray_range(6);
    struct IntConstPtrIntTuple2_ call_110 = choose_(fun_24, call_109);
    struct IntConstPtrIntTuple2_ chosen_ = call_110;
    int call_111 = length_(chosen_);
    milone_assert((call_111 == 3), 99, 2);
    int call_112 = get_(0, chosen_);
    milone_assert((call_112 == 0), 100, 2);
    int call_113 = get_(1, chosen_);
    milone_assert((call_113 == 4), 101, 2);
    int call_114 = get_(2, chosen_);
    milone_assert((call_114 == 8), 102, 2);
    struct IntIntOption_Fun1 fun_25 = (struct IntIntOption_Fun1){.fun = fun_14, .env = NULL};
    struct IntConstPtrIntTuple2_ call_115 = MiloneStd_StdArray_range(3);
    struct IntConstPtrIntTuple2_ call_116 = choose_(fun_25, call_115);
    struct IntConstPtrIntTuple2_ empty_1 = call_116;
    int call_117 = length_(empty_1);
    milone_assert((call_117 == 0), 107, 2);
    return;
}

int fun_7(int state_2, int i_11) {
    return ((state_2 * 10) + (i_11 + 1));
}

int fun_15(void const* env_11, int arg_18, int arg_19) {
    int call_118 = fun_7(arg_18, arg_19);
    return call_118;
}

void std_array_Program_foldTest(void) {
    struct IntIntIntFun2 fun_26 = (struct IntIntIntFun2){.fun = fun_15, .env = NULL};
    struct IntConstPtrIntTuple2_ call_119 = MiloneStd_StdArray_range(3);
    int call_120 = fold_(fun_26, 0, call_119);
    int sum_ = call_120;
    milone_assert((sum_ == 123), 113, 2);
    return;
}

void std_array_Program_ofListTest(void) {
    struct IntList const* list_3 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_3))) = (struct IntList){.head = 5, .tail = NULL};
    struct IntList const* list_2 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_2))) = (struct IntList){.head = 3, .tail = list_3};
    struct IntList const* list_1 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_1))) = (struct IntList){.head = 2, .tail = list_2};
    struct IntConstPtrIntTuple2_ call_121 = ofList_(list_1);
    struct IntConstPtrIntTuple2_ ol_ = call_121;
    int call_122 = length_(ol_);
    milone_assert((call_122 == 3), 126, 2);
    int call_123 = get_(0, ol_);
    milone_assert((call_123 == 2), 127, 2);
    int call_124 = get_(1, ol_);
    milone_assert((call_124 == 3), 128, 2);
    int call_125 = get_(2, ol_);
    milone_assert((call_125 == 5), 129, 2);
    return;
}

void std_array_Program_toListTest(void) {
    int n2_;
    int n1_1;
    int n0_;
    struct IntConstPtrIntTuple2_ call_126 = MiloneStd_StdArray_range(3);
    struct IntList const* call_127 = toList_(call_126);
    struct IntList const* tl_ = call_127;
    char match_7;
    if ((!(tl_))) goto next_96;
    n0_ = tl_->head;
    if ((!(tl_->tail))) goto next_96;
    n1_1 = tl_->tail->head;
    if ((!(tl_->tail->tail))) goto next_96;
    n2_ = tl_->tail->tail->head;
    if ((!((!(tl_->tail->tail->tail))))) goto next_96;
    milone_assert((n0_ == 0), 136, 4);
    milone_assert((n1_1 == 1), 137, 4);
    milone_assert((n2_ == 2), 138, 4);
    match_7 = 0;
    goto end_match_95;
next_96:;
    match_7 = 0;
    goto end_match_95;
next_97:;
end_match_95:;
    return;
}

int milone_main(void) {
    std_array_Program_initTest();
    std_array_Program_rangeTest();
    std_array_Program_tryItemTest();
    std_array_Program_sliceTest();
    std_array_Program_unconsTest();
    std_array_Program_mapTest();
    std_array_Program_chooseTest();
    std_array_Program_foldTest();
    std_array_Program_ofListTest();
    std_array_Program_toListTest();
    return 0;
}
