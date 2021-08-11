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

struct IntOption_ tryItem_(int, struct IntConstPtrIntTuple2_);

int length_(struct IntConstPtrIntTuple2_);

int get_(int i_8, struct IntConstPtrIntTuple2_ array_18);

char fun_1(int arg_57);

char fun_9(void const* env_5, int arg_11);

int fun_2(int n_);

int fun_10(void const* env_6, int arg_12);

struct UnitConstPtrIntTuple2_ init_1(int, struct IntUnitFun1);

int length_1(struct UnitConstPtrIntTuple2_);

struct IntConstPtrIntTuple2_ init_(int, struct IntIntFun1);

char std_array_Program_initTest(char arg_58);

struct IntConstPtrIntTuple2_ MiloneStd_StdArray_range(int);

char std_array_Program_rangeTest(char arg_59);

int at_(int bad_, int i_9, struct IntConstPtrIntTuple2_ array_19);

struct IntConstPtrIntTuple2_ empty_2(char);

char std_array_Program_tryItemTest(char arg_60);

struct IntConstPtrIntTuple2_ slice_(int, int, struct IntConstPtrIntTuple2_);

char std_array_Program_sliceTest(char arg_61);

int fun_3(int n_1);

int fun_11(void const* env_7, int arg_13);

struct IntIntConstPtrIntTuple2Tuple2Option_ uncons_(struct IntConstPtrIntTuple2_);

struct IntConstPtrIntTuple2_ skip_(int, struct IntConstPtrIntTuple2_);

char std_array_Program_unconsTest(char arg_62);

int fun_4(int i_10, int n_2);

int fun_12(void const* env_8, int arg_14, int arg_15);

struct IntConstPtrIntTuple2_ mapi_(struct IntIntIntFun2, struct IntConstPtrIntTuple2_);

char std_array_Program_mapTest(char arg_63);

struct IntOption_ fun_5(int n_3);

struct IntOption_ fun_13(void const* env_9, int arg_16);

struct IntOption_ fun_6(int arg_64);

struct IntOption_ fun_14(void const* env_10, int arg_17);

struct IntConstPtrIntTuple2_ choose_(struct IntIntOption_Fun1, struct IntConstPtrIntTuple2_);

char std_array_Program_chooseTest(char arg_65);

int fun_7(int state_2, int i_11);

int fun_15(void const* env_11, int arg_18, int arg_19);

int fold_(struct IntIntIntFun2, int, struct IntConstPtrIntTuple2_);

char std_array_Program_foldTest(char arg_66);

struct IntConstPtrIntTuple2_ ofList_(struct IntList const*);

char std_array_Program_ofListTest(char arg_67);

struct IntList const* toList_(struct IntConstPtrIntTuple2_);

char std_array_Program_toListTest(char arg_68);

int milone_main();

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
    char(*fun)(void const*, int);
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
    struct IntOption_ call_64 = tryItem_(i_8, array_18);
    if ((call_64.discriminant != Some_)) goto next_78;
    it_ = call_64.Some_;
    match_3 = it_;
    goto end_match_77;
next_78:;
    if ((call_64.discriminant != None_)) goto next_79;
    int call_65 = length_(array_18);
    printf("out of range: i=%d len=%d\n", i_8, call_65);
    milone_assert(false, 9, 4);
    exit(1);
next_79:;
    exit(1);
end_match_77:;
    return match_3;
}

char fun_1(int arg_57) {
    milone_assert(false, 13, 45);
    return 0;
}

char fun_9(void const* env_5, int arg_11) {
    char call_66 = fun_1(arg_11);
    return 0;
}

int fun_2(int n_) {
    return ((n_ + 1) * 3);
}

int fun_10(void const* env_6, int arg_12) {
    int call_67 = fun_2(arg_12);
    return call_67;
}

char std_array_Program_initTest(char arg_58) {
    struct IntUnitFun1 fun_20 = (struct IntUnitFun1){.fun = fun_9, .env = NULL};
    struct UnitConstPtrIntTuple2_ call_68 = init_1(0, fun_20);
    struct UnitConstPtrIntTuple2_ emptyArray_ = call_68;
    int call_69 = length_1(emptyArray_);
    milone_assert((call_69 == 0), 14, 2);
    struct IntIntFun1 fun_21 = (struct IntIntFun1){.fun = fun_10, .env = NULL};
    struct IntConstPtrIntTuple2_ call_70 = init_(3, fun_21);
    struct IntConstPtrIntTuple2_ a369_ = call_70;
    int call_71 = length_(a369_);
    milone_assert((call_71 == 3), 17, 2);
    int call_72 = get_(0, a369_);
    milone_assert((call_72 == 3), 18, 2);
    int call_73 = get_(1, a369_);
    milone_assert((call_73 == 6), 19, 2);
    int call_74 = get_(2, a369_);
    milone_assert((call_74 == 9), 20, 2);
    return 0;
}

char std_array_Program_rangeTest(char arg_59) {
    struct IntConstPtrIntTuple2_ call_75 = MiloneStd_StdArray_range(3);
    struct IntConstPtrIntTuple2_ a012_ = call_75;
    int call_76 = length_(a012_);
    milone_assert((call_76 == 3), 25, 2);
    int call_77 = get_(0, a012_);
    milone_assert((call_77 == 0), 26, 2);
    int call_78 = get_(1, a012_);
    milone_assert((call_78 == 1), 27, 2);
    int call_79 = get_(2, a012_);
    milone_assert((call_79 == 2), 28, 2);
    return 0;
}

int at_(int bad_, int i_9, struct IntConstPtrIntTuple2_ array_19) {
    int it_1;
    int match_4;
    struct IntOption_ call_80 = tryItem_(i_9, array_19);
    if ((call_80.discriminant != Some_)) goto next_81;
    it_1 = call_80.Some_;
    match_4 = it_1;
    goto end_match_80;
next_81:;
    if ((call_80.discriminant != None_)) goto next_82;
    match_4 = bad_;
    goto end_match_80;
next_82:;
    exit(1);
end_match_80:;
    return match_4;
}

char std_array_Program_tryItemTest(char arg_60) {
    struct IntConstPtrIntTuple2_ call_81 = MiloneStd_StdArray_range(3);
    struct IntConstPtrIntTuple2_ a012_1 = call_81;
    int bad_ = -127;
    int call_82 = at_(bad_, -1, a012_1);
    milone_assert((call_82 == bad_), 40, 2);
    int call_83 = at_(bad_, 0, a012_1);
    milone_assert((call_83 == 0), 41, 2);
    int call_84 = at_(bad_, 2, a012_1);
    milone_assert((call_84 == 2), 42, 2);
    int call_85 = at_(bad_, 3, a012_1);
    milone_assert((call_85 == bad_), 43, 2);
    struct IntConstPtrIntTuple2_ call_86 = empty_2(0);
    struct IntConstPtrIntTuple2_ emptyArray_1 = call_86;
    int call_87 = at_(bad_, 0, emptyArray_1);
    milone_assert((call_87 == bad_), 46, 2);
    return 0;
}

char std_array_Program_sliceTest(char arg_61) {
    struct IntConstPtrIntTuple2_ call_88 = MiloneStd_StdArray_range(10);
    struct IntConstPtrIntTuple2_ ten_ = call_88;
    struct IntConstPtrIntTuple2_ call_89 = slice_(1, 4, ten_);
    struct IntConstPtrIntTuple2_ three_ = call_89;
    int call_90 = length_(three_);
    milone_assert((call_90 == 3), 52, 2);
    int call_91 = get_(0, three_);
    milone_assert((call_91 == 1), 53, 2);
    int call_92 = get_(2, three_);
    milone_assert((call_92 == 3), 54, 2);
    struct IntConstPtrIntTuple2_ call_93 = slice_(-1, 2, ten_);
    struct IntConstPtrIntTuple2_ behind_ = call_93;
    int call_94 = length_(behind_);
    milone_assert((call_94 == 2), 58, 2);
    int call_95 = get_(1, behind_);
    milone_assert((call_95 == 1), 59, 2);
    struct IntConstPtrIntTuple2_ call_96 = slice_(7, 11, ten_);
    struct IntConstPtrIntTuple2_ beyond_ = call_96;
    int call_97 = length_(beyond_);
    milone_assert((call_97 == 3), 63, 2);
    int call_98 = get_(0, beyond_);
    milone_assert((call_98 == 7), 64, 2);
    int call_99 = get_(2, beyond_);
    milone_assert((call_99 == 9), 65, 2);
    return 0;
}

int fun_3(int n_1) {
    return (n_1 + 1);
}

int fun_11(void const* env_7, int arg_13) {
    int call_100 = fun_3(arg_13);
    return call_100;
}

char std_array_Program_unconsTest(char arg_62) {
    struct IntConstPtrIntTuple2_ empty_;
    int n3_;
    struct IntConstPtrIntTuple2_ a23_;
    int n1_;
    struct IntIntFun1 fun_22 = (struct IntIntFun1){.fun = fun_11, .env = NULL};
    struct IntConstPtrIntTuple2_ call_101 = init_(3, fun_22);
    struct IntConstPtrIntTuple2_ a123_ = call_101;
    char match_5;
    struct IntIntConstPtrIntTuple2Tuple2Option_ call_102 = uncons_(a123_);
    if ((call_102.discriminant != None_1)) goto next_84;
    milone_assert(false, 71, 12);
    match_5 = 0;
    goto end_match_83;
next_84:;
    if ((call_102.discriminant != Some_1)) goto next_85;
    n1_ = call_102.Some_1.t0;
    a23_ = call_102.Some_1.t1;
    milone_assert((n1_ == 1), 73, 4);
    int call_103 = length_(a23_);
    milone_assert((call_103 == 2), 74, 4);
    char match_6;
    struct IntConstPtrIntTuple2_ call_104 = skip_(1, a23_);
    struct IntIntConstPtrIntTuple2Tuple2Option_ call_105 = uncons_(call_104);
    if ((call_105.discriminant != None_1)) goto next_87;
    milone_assert(false, 77, 14);
    match_6 = 0;
    goto end_match_86;
next_87:;
    if ((call_105.discriminant != Some_1)) goto next_88;
    n3_ = call_105.Some_1.t0;
    empty_ = call_105.Some_1.t1;
    milone_assert((n3_ == 3), 79, 6);
    int call_106 = length_(empty_);
    milone_assert((call_106 == 0), 80, 6);
    char switch_;
    struct IntIntConstPtrIntTuple2Tuple2Option_ call_107 = uncons_(empty_);
    switch (call_107.discriminant) {
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
    return 0;
}

int fun_4(int i_10, int n_2) {
    return ((i_10 * 10) + n_2);
}

int fun_12(void const* env_8, int arg_14, int arg_15) {
    int call_108 = fun_4(arg_14, arg_15);
    return call_108;
}

char std_array_Program_mapTest(char arg_63) {
    struct IntIntIntFun2 fun_23 = (struct IntIntIntFun2){.fun = fun_12, .env = NULL};
    struct IntConstPtrIntTuple2_ call_109 = MiloneStd_StdArray_range(3);
    struct IntConstPtrIntTuple2_ call_110 = mapi_(fun_23, call_109);
    struct IntConstPtrIntTuple2_ mapped_ = call_110;
    int call_111 = length_(mapped_);
    milone_assert((call_111 == 3), 90, 2);
    int call_112 = get_(0, mapped_);
    milone_assert((call_112 == 0), 91, 2);
    int call_113 = get_(1, mapped_);
    milone_assert((call_113 == 11), 92, 2);
    int call_114 = get_(2, mapped_);
    milone_assert((call_114 == 22), 93, 2);
    return 0;
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
    struct IntOption_ call_115 = fun_5(arg_16);
    return call_115;
}

struct IntOption_ fun_6(int arg_64) {
    return (struct IntOption_){.discriminant = None_};
}

struct IntOption_ fun_14(void const* env_10, int arg_17) {
    struct IntOption_ call_116 = fun_6(arg_17);
    return call_116;
}

char std_array_Program_chooseTest(char arg_65) {
    struct IntIntOption_Fun1 fun_24 = (struct IntIntOption_Fun1){.fun = fun_13, .env = NULL};
    struct IntConstPtrIntTuple2_ call_117 = MiloneStd_StdArray_range(6);
    struct IntConstPtrIntTuple2_ call_118 = choose_(fun_24, call_117);
    struct IntConstPtrIntTuple2_ chosen_ = call_118;
    int call_119 = length_(chosen_);
    milone_assert((call_119 == 3), 99, 2);
    int call_120 = get_(0, chosen_);
    milone_assert((call_120 == 0), 100, 2);
    int call_121 = get_(1, chosen_);
    milone_assert((call_121 == 4), 101, 2);
    int call_122 = get_(2, chosen_);
    milone_assert((call_122 == 8), 102, 2);
    struct IntIntOption_Fun1 fun_25 = (struct IntIntOption_Fun1){.fun = fun_14, .env = NULL};
    struct IntConstPtrIntTuple2_ call_123 = MiloneStd_StdArray_range(3);
    struct IntConstPtrIntTuple2_ call_124 = choose_(fun_25, call_123);
    struct IntConstPtrIntTuple2_ empty_1 = call_124;
    int call_125 = length_(empty_1);
    milone_assert((call_125 == 0), 107, 2);
    return 0;
}

int fun_7(int state_2, int i_11) {
    return ((state_2 * 10) + (i_11 + 1));
}

int fun_15(void const* env_11, int arg_18, int arg_19) {
    int call_126 = fun_7(arg_18, arg_19);
    return call_126;
}

char std_array_Program_foldTest(char arg_66) {
    struct IntIntIntFun2 fun_26 = (struct IntIntIntFun2){.fun = fun_15, .env = NULL};
    struct IntConstPtrIntTuple2_ call_127 = MiloneStd_StdArray_range(3);
    int call_128 = fold_(fun_26, 0, call_127);
    int sum_ = call_128;
    milone_assert((sum_ == 123), 113, 2);
    return 0;
}

char std_array_Program_ofListTest(char arg_67) {
    struct IntList const* list_3 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_3))) = (struct IntList){.head = 5, .tail = NULL};
    struct IntList const* list_2 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_2))) = (struct IntList){.head = 3, .tail = list_3};
    struct IntList const* list_1 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)list_1))) = (struct IntList){.head = 2, .tail = list_2};
    struct IntConstPtrIntTuple2_ call_129 = ofList_(list_1);
    struct IntConstPtrIntTuple2_ ol_ = call_129;
    int call_130 = length_(ol_);
    milone_assert((call_130 == 3), 126, 2);
    int call_131 = get_(0, ol_);
    milone_assert((call_131 == 2), 127, 2);
    int call_132 = get_(1, ol_);
    milone_assert((call_132 == 3), 128, 2);
    int call_133 = get_(2, ol_);
    milone_assert((call_133 == 5), 129, 2);
    return 0;
}

char std_array_Program_toListTest(char arg_68) {
    int n2_;
    int n1_1;
    int n0_;
    struct IntConstPtrIntTuple2_ call_134 = MiloneStd_StdArray_range(3);
    struct IntList const* call_135 = toList_(call_134);
    struct IntList const* tl_ = call_135;
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
    return 0;
}

int milone_main() {
    char call_136 = std_array_Program_initTest(0);
    char call_137 = std_array_Program_rangeTest(0);
    char call_138 = std_array_Program_tryItemTest(0);
    char call_139 = std_array_Program_sliceTest(0);
    char call_140 = std_array_Program_unconsTest(0);
    char call_141 = std_array_Program_mapTest(0);
    char call_142 = std_array_Program_chooseTest(0);
    char call_143 = std_array_Program_foldTest(0);
    char call_144 = std_array_Program_ofListTest(0);
    char call_145 = std_array_Program_toListTest(0);
    return 0;
}
