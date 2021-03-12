#include "milone.h"

struct StringList;

struct IntOption;

struct StringList;

struct CharOption;

struct CharBoolFun1;

struct StringOption;

struct StringStringOptionStringTuple3;

struct String str_concat(struct String, struct StringList const*);

struct String __stringJoin_(struct String sep_, struct StringList const* xs_);

int const* __ptrAsConst_1(int* mutPtr_);

void* milone_mem_alloc(int, uintptr_t);

void* memAlloc_(int len_, uintptr_t size_);

void* memcpy(void*, void const*, uintptr_t);

void* memcpy_(void* dest_, void const* src_, uintptr_t size_1);

bool str_to_int_checked(struct String, int*);

struct IntOption __intOfStr_(struct String s_);

int milone_get_arg_count();

int __argCount_(char arg_3);

struct String milone_get_arg(int);

struct String __argGet_(int index_4);

char subtract_(char l_, char r_);

bool isAscii_(char c_);

bool isControl_(char c_1);

bool isBlank_(char c_2);

bool isSpace_(char c_3);

bool isPunctuation_(char c_4);

bool isDigit_(char c_5);

bool isHex_(char c_6);

bool isUpper_(char c_7);

bool isLower_(char c_8);

bool isAlphabetic_(char c_9);

bool isAlphanumeric_(char c_10);

char toUpper_(char c_11);

char toLower_(char c_12);

struct StringList const* listRevLoop_1(struct StringList const* acc_, struct StringList const* xs_6);

struct StringList const* rev_1(struct StringList const* xs_5);

int intClamp_(int minValue_, int maxValue_, int value_1);

bool isEmpty_1(struct String str_);

struct CharOption tryItem_1(int index_5, struct String str_1);

bool occursAtLoop_(int start_2, struct String substr_, struct String s_1, int i_4);

bool occursAt_(int start_2, struct String substr_, struct String s_1);

bool startsWith_(struct String prefix_, struct String s_2);

bool endsWith_(struct String suffix_, struct String s_3);

struct IntOption stringFindIndexLoop_(struct String substr_1, struct String s_4, int r_1, int i_5);

struct IntOption findIndex_(struct String substr_1, struct String s_4);

struct IntOption stringFindLastIndexLoop_(struct String substr_2, struct String s_5, int r_2);

struct IntOption findLastIndex_(struct String substr_2, struct String s_5);

bool contains_(struct String substr_3, struct String s_6);

struct String truncate_1(int prefixLen_, struct String s_7);

struct String skip_1(int prefixLen_1, struct String s_8);

struct String slice_(int start_3, int endIndex_2, struct String s_9);

int stringTrimIfLoop1_(struct CharBoolFun1 isTrimmed_, struct String s_10, int l_2);

int stringTrimIfLoop2_(struct CharBoolFun1 isTrimmed_, struct String s_10, int l_1, int r_5);

struct String trimIf_(struct CharBoolFun1 isTrimmed_, struct String s_10);

int stringTrimStartIfLoop_(struct CharBoolFun1 isTrimmed_1, struct String s_11, int l_4);

struct String trimStartIf_(struct CharBoolFun1 isTrimmed_1, struct String s_11);

int stringTrimEndIfLoop_(struct CharBoolFun1 isTrimmed_2, struct String s_12, int r_7);

struct String trimEndIf_(struct CharBoolFun1 isTrimmed_2, struct String s_12);

bool fun_(void const* env_, char arg_);

struct String trim_(struct String s_13);

bool fun_1(void const* env_1, char arg_1);

struct String trimStart_(struct String s_14);

bool fun_2(void const* env_2, char arg_2);

struct String trimEnd_(struct String s_15);

struct StringList const* replaceLoop_(struct String pattern_, struct String s_16, struct StringList const* acc_14, int i_6);

struct String replace_(struct String pattern_, struct String target_, struct String s_16);

int findNewline_(int start_5, struct String s_17);

struct StringStringOptionStringTuple3 scanLine_(struct String s_18);

struct StringList const* stringToLinesLoop_(struct String s_19, int l_5, struct StringList const* acc_15);

struct StringList const* toLines_(struct String s_19);

struct String concat_(struct String sep_2, struct StringList const* xs_61);

bool isNone_2(struct CharOption opt_);

bool isNone_1(struct IntOption opt_);

char unwrap_2(struct CharOption opt_8);

int unwrap_1(struct IntOption opt_8);

char isEmptyTest_(char arg_42);

char tryItemTest_(char arg_43);

char startsWithTest_(char arg_44);

char endsWithTest_(char arg_45);

char findIndexTest_(char arg_46);

char findLastIndexTest_(char arg_47);

char containsTest_(char arg_48);

char truncateTest_(char arg_49);

char skipTest_(char arg_50);

char sliceTest_(char arg_51);

char trimTest_(char arg_52);

char replaceTest_(char arg_53);

char splitTest_(char arg_54);

char concatTest_(char arg_55);

int milone_main();

struct IntOption {
    bool some;
    int value;
};

struct StringList {
    struct String head;
    struct StringList const* tail;
};

struct CharOption {
    bool some;
    char value;
};

struct CharBoolFun1 {
    bool(*fun)(void const*, char);
    void const* env;
};

struct StringOption {
    bool some;
    struct String value;
};

struct StringStringOptionStringTuple3 {
    struct String t0;
    struct StringOption t1;
    struct String t2;
};

struct String __stringJoin_(struct String sep_, struct StringList const* xs_) {
    struct String str_concat_result_ = str_concat(sep_, xs_);
    return str_concat_result_;
}

int const* __ptrAsConst_1(int* mutPtr_) {
    return ((int const*)mutPtr_);
}

void* memAlloc_(int len_, uintptr_t size_) {
    void* milone_mem_alloc_result_ = milone_mem_alloc(len_, size_);
    return milone_mem_alloc_result_;
}

void* memcpy_(void* dest_, void const* src_, uintptr_t size_1) {
    void* memcpy_result_ = memcpy(dest_, src_, size_1);
    return memcpy_result_;
}

struct IntOption __intOfStr_(struct String s_) {
    void* call_ = memAlloc_(1, ((uintptr_t)sizeof(int)));
    int* valueRef_ = ((int*)call_);
    bool str_to_int_checked_result_ = str_to_int_checked(s_, valueRef_);
    bool ok_ = str_to_int_checked_result_;
    struct IntOption if_;
    if (ok_) {
        goto then_2;
    } else {
        goto else_3;
    }
then_2:;
    int const* call_1 = __ptrAsConst_1(valueRef_);
    int read_ = (*(call_1));
    struct IntOption some_ = ((struct IntOption){.some = true, .value = read_});
    if_ = some_;
    goto if_next_1;
else_3:;
    if_ = ((struct IntOption){.some = false});
    goto if_next_1;
if_next_1:;
    return if_;
}

int __argCount_(char arg_3) {
    int milone_get_arg_count_result_ = milone_get_arg_count();
    return milone_get_arg_count_result_;
}

struct String __argGet_(int index_4) {
    struct String milone_get_arg_result_ = milone_get_arg(index_4);
    return milone_get_arg_result_;
}

char subtract_(char l_, char r_) {
    return ((char)(((int)l_) - ((int)r_)));
}

bool isAscii_(char c_) {
    return (((uint32_t)127) >= ((uint32_t)c_));
}

bool isControl_(char c_1) {
    int n_ = ((int)c_1);
    bool if_1;
    if ((n_ >= 0)) {
        goto then_5;
    } else {
        goto else_6;
    }
then_5:;
    if_1 = (31 >= n_);
    goto if_next_4;
else_6:;
    if_1 = false;
    goto if_next_4;
if_next_4:;
    bool if_2;
    if (if_1) {
        goto then_8;
    } else {
        goto else_9;
    }
then_8:;
    if_2 = true;
    goto if_next_7;
else_9:;
    if_2 = (n_ == 127);
    goto if_next_7;
if_next_7:;
    return if_2;
}

bool isBlank_(char c_2) {
    bool if_3;
    if ((c_2 == ' ')) {
        goto then_11;
    } else {
        goto else_12;
    }
then_11:;
    if_3 = true;
    goto if_next_10;
else_12:;
    if_3 = (c_2 == '\t');
    goto if_next_10;
if_next_10:;
    return if_3;
}

bool isSpace_(char c_3) {
    bool if_4;
    if ((c_3 >= '\t')) {
        goto then_14;
    } else {
        goto else_15;
    }
then_14:;
    if_4 = ('\r' >= c_3);
    goto if_next_13;
else_15:;
    if_4 = false;
    goto if_next_13;
if_next_13:;
    bool if_5;
    if (if_4) {
        goto then_17;
    } else {
        goto else_18;
    }
then_17:;
    if_5 = true;
    goto if_next_16;
else_18:;
    if_5 = (c_3 == ' ');
    goto if_next_16;
if_next_16:;
    return if_5;
}

bool isPunctuation_(char c_4) {
    int n_1 = ((int)c_4);
    bool if_6;
    if ((n_1 >= 33)) {
        goto then_20;
    } else {
        goto else_21;
    }
then_20:;
    if_6 = (47 >= n_1);
    goto if_next_19;
else_21:;
    if_6 = false;
    goto if_next_19;
if_next_19:;
    bool if_7;
    if (if_6) {
        goto then_23;
    } else {
        goto else_24;
    }
then_23:;
    if_7 = true;
    goto if_next_22;
else_24:;
    bool if_8;
    if ((n_1 >= 58)) {
        goto then_26;
    } else {
        goto else_27;
    }
then_26:;
    if_8 = (64 >= n_1);
    goto if_next_25;
else_27:;
    if_8 = false;
    goto if_next_25;
if_next_25:;
    if_7 = if_8;
    goto if_next_22;
if_next_22:;
    bool if_9;
    if (if_7) {
        goto then_29;
    } else {
        goto else_30;
    }
then_29:;
    if_9 = true;
    goto if_next_28;
else_30:;
    bool if_10;
    if ((n_1 >= 91)) {
        goto then_32;
    } else {
        goto else_33;
    }
then_32:;
    if_10 = (96 >= n_1);
    goto if_next_31;
else_33:;
    if_10 = false;
    goto if_next_31;
if_next_31:;
    if_9 = if_10;
    goto if_next_28;
if_next_28:;
    bool if_11;
    if (if_9) {
        goto then_35;
    } else {
        goto else_36;
    }
then_35:;
    if_11 = true;
    goto if_next_34;
else_36:;
    bool if_12;
    if ((n_1 >= 123)) {
        goto then_38;
    } else {
        goto else_39;
    }
then_38:;
    if_12 = (126 >= n_1);
    goto if_next_37;
else_39:;
    if_12 = false;
    goto if_next_37;
if_next_37:;
    if_11 = if_12;
    goto if_next_34;
if_next_34:;
    return if_11;
}

bool isDigit_(char c_5) {
    bool if_13;
    if ((c_5 >= '0')) {
        goto then_41;
    } else {
        goto else_42;
    }
then_41:;
    if_13 = ('9' >= c_5);
    goto if_next_40;
else_42:;
    if_13 = false;
    goto if_next_40;
if_next_40:;
    return if_13;
}

bool isHex_(char c_6) {
    bool call_2 = isDigit_(c_6);
    bool if_14;
    if (call_2) {
        goto then_44;
    } else {
        goto else_45;
    }
then_44:;
    if_14 = true;
    goto if_next_43;
else_45:;
    bool if_15;
    if ((c_6 >= 'A')) {
        goto then_47;
    } else {
        goto else_48;
    }
then_47:;
    if_15 = ('F' >= c_6);
    goto if_next_46;
else_48:;
    if_15 = false;
    goto if_next_46;
if_next_46:;
    if_14 = if_15;
    goto if_next_43;
if_next_43:;
    bool if_16;
    if (if_14) {
        goto then_50;
    } else {
        goto else_51;
    }
then_50:;
    if_16 = true;
    goto if_next_49;
else_51:;
    bool if_17;
    if ((c_6 >= 'a')) {
        goto then_53;
    } else {
        goto else_54;
    }
then_53:;
    if_17 = ('f' >= c_6);
    goto if_next_52;
else_54:;
    if_17 = false;
    goto if_next_52;
if_next_52:;
    if_16 = if_17;
    goto if_next_49;
if_next_49:;
    return if_16;
}

bool isUpper_(char c_7) {
    bool if_18;
    if ((c_7 >= 'A')) {
        goto then_56;
    } else {
        goto else_57;
    }
then_56:;
    if_18 = ('Z' >= c_7);
    goto if_next_55;
else_57:;
    if_18 = false;
    goto if_next_55;
if_next_55:;
    return if_18;
}

bool isLower_(char c_8) {
    bool if_19;
    if ((c_8 >= 'a')) {
        goto then_59;
    } else {
        goto else_60;
    }
then_59:;
    if_19 = ('z' >= c_8);
    goto if_next_58;
else_60:;
    if_19 = false;
    goto if_next_58;
if_next_58:;
    return if_19;
}

bool isAlphabetic_(char c_9) {
    bool call_3 = isUpper_(c_9);
    bool if_20;
    if (call_3) {
        goto then_62;
    } else {
        goto else_63;
    }
then_62:;
    if_20 = true;
    goto if_next_61;
else_63:;
    bool call_4 = isLower_(c_9);
    if_20 = call_4;
    goto if_next_61;
if_next_61:;
    return if_20;
}

bool isAlphanumeric_(char c_10) {
    bool call_5 = isDigit_(c_10);
    bool if_21;
    if (call_5) {
        goto then_65;
    } else {
        goto else_66;
    }
then_65:;
    if_21 = true;
    goto if_next_64;
else_66:;
    bool call_6 = isAlphabetic_(c_10);
    if_21 = call_6;
    goto if_next_64;
if_next_64:;
    return if_21;
}

char toUpper_(char c_11) {
    bool call_7 = isLower_(c_11);
    char if_22;
    if (call_7) {
        goto then_68;
    } else {
        goto else_69;
    }
then_68:;
    char call_8 = subtract_(c_11, 'a');
    if_22 = (call_8 + 'A');
    goto if_next_67;
else_69:;
    if_22 = c_11;
    goto if_next_67;
if_next_67:;
    return if_22;
}

char toLower_(char c_12) {
    bool call_9 = isUpper_(c_12);
    char if_23;
    if (call_9) {
        goto then_71;
    } else {
        goto else_72;
    }
then_71:;
    char call_10 = subtract_(c_12, 'A');
    if_23 = (call_10 + 'a');
    goto if_next_70;
else_72:;
    if_23 = c_12;
    goto if_next_70;
if_next_70:;
    return if_23;
}

struct StringList const* listRevLoop_1(struct StringList const* acc_, struct StringList const* xs_6) {
tailrec_73:;
    struct StringList const* match_;
    if ((!((!(xs_6))))) goto next_75;
    match_ = acc_;
    goto end_match_74;
next_75:;
    if ((!(xs_6))) goto next_76;
    struct String x_ = xs_6->head;
    struct StringList const* xs_7 = xs_6->tail;
    struct StringList const* list_ = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_))) = ((struct StringList){.head = x_, .tail = acc_});
    struct StringList const* arg_4 = list_;
    struct StringList const* arg_5 = xs_7;
    acc_ = arg_4;
    xs_6 = arg_5;
    goto tailrec_73;
next_76:;
    exit(1);
end_match_74:;
    return match_;
}

struct StringList const* rev_1(struct StringList const* xs_5) {
    struct StringList const* call_11 = listRevLoop_1(NULL, xs_5);
    return call_11;
}

int intClamp_(int minValue_, int maxValue_, int value_1) {
    int if_24;
    if ((value_1 < minValue_)) {
        goto then_78;
    } else {
        goto else_79;
    }
then_78:;
    if_24 = minValue_;
    goto if_next_77;
else_79:;
    int if_25;
    if ((maxValue_ < value_1)) {
        goto then_81;
    } else {
        goto else_82;
    }
then_81:;
    if_25 = maxValue_;
    goto if_next_80;
else_82:;
    if_25 = value_1;
    goto if_next_80;
if_next_80:;
    if_24 = if_25;
    goto if_next_77;
if_next_77:;
    return if_24;
}

bool isEmpty_1(struct String str_) {
    return (str_.len == 0);
}

struct CharOption tryItem_1(int index_5, struct String str_1) {
    bool if_26;
    if ((index_5 >= 0)) {
        goto then_84;
    } else {
        goto else_85;
    }
then_84:;
    if_26 = (index_5 < str_1.len);
    goto if_next_83;
else_85:;
    if_26 = false;
    goto if_next_83;
if_next_83:;
    struct CharOption if_27;
    if (if_26) {
        goto then_87;
    } else {
        goto else_88;
    }
then_87:;
    struct CharOption some_1 = ((struct CharOption){.some = true, .value = str_1.str[index_5]});
    if_27 = some_1;
    goto if_next_86;
else_88:;
    if_27 = ((struct CharOption){.some = false});
    goto if_next_86;
if_next_86:;
    return if_27;
}

bool occursAtLoop_(int start_2, struct String substr_, struct String s_1, int i_4) {
tailrec_89:;
    bool if_28;
    if ((i_4 == substr_.len)) {
        goto then_91;
    } else {
        goto else_92;
    }
then_91:;
    if_28 = true;
    goto if_next_90;
else_92:;
    bool if_29;
    if ((s_1.str[(start_2 + i_4)] == substr_.str[i_4])) {
        goto then_94;
    } else {
        goto else_95;
    }
then_94:;
    int arg_6 = start_2;
    struct String arg_7 = substr_;
    struct String arg_8 = s_1;
    int arg_9 = (i_4 + 1);
    start_2 = arg_6;
    substr_ = arg_7;
    s_1 = arg_8;
    i_4 = arg_9;
    goto tailrec_89;
else_95:;
    if_29 = false;
    goto if_next_93;
if_next_93:;
    if_28 = if_29;
    goto if_next_90;
if_next_90:;
    return if_28;
}

bool occursAt_(int start_2, struct String substr_, struct String s_1) {
    bool if_30;
    if ((start_2 >= 0)) {
        goto then_97;
    } else {
        goto else_98;
    }
then_97:;
    if_30 = (s_1.len >= (start_2 + substr_.len));
    goto if_next_96;
else_98:;
    if_30 = false;
    goto if_next_96;
if_next_96:;
    bool if_31;
    if (if_30) {
        goto then_100;
    } else {
        goto else_101;
    }
then_100:;
    bool call_12 = occursAtLoop_(start_2, substr_, s_1, 0);
    if_31 = call_12;
    goto if_next_99;
else_101:;
    if_31 = false;
    goto if_next_99;
if_next_99:;
    return if_31;
}

bool startsWith_(struct String prefix_, struct String s_2) {
    bool call_13 = occursAt_(0, prefix_, s_2);
    return call_13;
}

bool endsWith_(struct String suffix_, struct String s_3) {
    bool call_14 = occursAt_((s_3.len - suffix_.len), suffix_, s_3);
    return call_14;
}

struct IntOption stringFindIndexLoop_(struct String substr_1, struct String s_4, int r_1, int i_5) {
tailrec_102:;
    struct IntOption if_32;
    if ((i_5 >= r_1)) {
        goto then_104;
    } else {
        goto else_105;
    }
then_104:;
    if_32 = ((struct IntOption){.some = false});
    goto if_next_103;
else_105:;
    bool call_15 = occursAt_(i_5, substr_1, s_4);
    struct IntOption if_33;
    if (call_15) {
        goto then_107;
    } else {
        goto else_108;
    }
then_107:;
    struct IntOption some_2 = ((struct IntOption){.some = true, .value = i_5});
    if_33 = some_2;
    goto if_next_106;
else_108:;
    struct String arg_10 = substr_1;
    struct String arg_11 = s_4;
    int arg_12 = r_1;
    int arg_13 = (i_5 + 1);
    substr_1 = arg_10;
    s_4 = arg_11;
    r_1 = arg_12;
    i_5 = arg_13;
    goto tailrec_102;
if_next_106:;
    if_32 = if_33;
    goto if_next_103;
if_next_103:;
    return if_32;
}

struct IntOption findIndex_(struct String substr_1, struct String s_4) {
    int r_1 = ((s_4.len - substr_1.len) + 1);
    struct IntOption call_16 = stringFindIndexLoop_(substr_1, s_4, r_1, 0);
    return call_16;
}

struct IntOption stringFindLastIndexLoop_(struct String substr_2, struct String s_5, int r_2) {
tailrec_109:;
    struct IntOption if_34;
    if ((0 >= r_2)) {
        goto then_111;
    } else {
        goto else_112;
    }
then_111:;
    if_34 = ((struct IntOption){.some = false});
    goto if_next_110;
else_112:;
    bool call_17 = occursAt_((r_2 - 1), substr_2, s_5);
    struct IntOption if_35;
    if (call_17) {
        goto then_114;
    } else {
        goto else_115;
    }
then_114:;
    struct IntOption some_3 = ((struct IntOption){.some = true, .value = (r_2 - 1)});
    if_35 = some_3;
    goto if_next_113;
else_115:;
    struct String arg_14 = substr_2;
    struct String arg_15 = s_5;
    int arg_16 = (r_2 - 1);
    substr_2 = arg_14;
    s_5 = arg_15;
    r_2 = arg_16;
    goto tailrec_109;
if_next_113:;
    if_34 = if_35;
    goto if_next_110;
if_next_110:;
    return if_34;
}

struct IntOption findLastIndex_(struct String substr_2, struct String s_5) {
    int r_3 = ((s_5.len - substr_2.len) + 1);
    struct IntOption call_18 = stringFindLastIndexLoop_(substr_2, s_5, r_3);
    return call_18;
}

bool contains_(struct String substr_3, struct String s_6) {
    bool match_1;
    struct IntOption call_19 = findIndex_(substr_3, s_6);
    if ((!(call_19.some))) goto next_117;
    match_1 = true;
    goto end_match_116;
next_117:;
    if (call_19.some) goto next_118;
    match_1 = false;
    goto end_match_116;
next_118:;
    exit(1);
end_match_116:;
    return match_1;
}

struct String truncate_1(int prefixLen_, struct String s_7) {
    struct String if_36;
    if ((0 >= prefixLen_)) {
        goto then_120;
    } else {
        goto else_121;
    }
then_120:;
    if_36 = (struct String){.str = "", .len = 0};
    goto if_next_119;
else_121:;
    struct String if_37;
    if ((prefixLen_ >= s_7.len)) {
        goto then_123;
    } else {
        goto else_124;
    }
then_123:;
    if_37 = s_7;
    goto if_next_122;
else_124:;
    struct String slice_1 = str_get_slice(0, (prefixLen_ - 1), s_7);
    if_37 = slice_1;
    goto if_next_122;
if_next_122:;
    if_36 = if_37;
    goto if_next_119;
if_next_119:;
    return if_36;
}

struct String skip_1(int prefixLen_1, struct String s_8) {
    struct String if_38;
    if ((0 >= prefixLen_1)) {
        goto then_126;
    } else {
        goto else_127;
    }
then_126:;
    if_38 = s_8;
    goto if_next_125;
else_127:;
    struct String if_39;
    if ((prefixLen_1 >= s_8.len)) {
        goto then_129;
    } else {
        goto else_130;
    }
then_129:;
    if_39 = (struct String){.str = "", .len = 0};
    goto if_next_128;
else_130:;
    struct String slice_2 = str_get_slice(prefixLen_1, (s_8.len - 1), s_8);
    if_39 = slice_2;
    goto if_next_128;
if_next_128:;
    if_38 = if_39;
    goto if_next_125;
if_next_125:;
    return if_38;
}

struct String slice_(int start_3, int endIndex_2, struct String s_9) {
    int call_20 = intClamp_(0, s_9.len, start_3);
    int start_4 = call_20;
    int call_21 = intClamp_(start_4, s_9.len, endIndex_2);
    int endIndex_3 = call_21;
    struct String if_40;
    if ((start_4 < endIndex_3)) {
        goto then_132;
    } else {
        goto else_133;
    }
then_132:;
    struct String slice_3 = str_get_slice(start_4, (endIndex_3 - 1), s_9);
    if_40 = slice_3;
    goto if_next_131;
else_133:;
    if_40 = (struct String){.str = "", .len = 0};
    goto if_next_131;
if_next_131:;
    return if_40;
}

int stringTrimIfLoop1_(struct CharBoolFun1 isTrimmed_, struct String s_10, int l_2) {
tailrec_134:;
    bool if_41;
    if ((l_2 < s_10.len)) {
        goto then_136;
    } else {
        goto else_137;
    }
then_136:;
    bool app_ = isTrimmed_.fun(isTrimmed_.env, s_10.str[l_2]);
    if_41 = app_;
    goto if_next_135;
else_137:;
    if_41 = false;
    goto if_next_135;
if_next_135:;
    int if_42;
    if (if_41) {
        goto then_139;
    } else {
        goto else_140;
    }
then_139:;
    struct CharBoolFun1 arg_17 = isTrimmed_;
    struct String arg_18 = s_10;
    int arg_19 = (l_2 + 1);
    isTrimmed_ = arg_17;
    s_10 = arg_18;
    l_2 = arg_19;
    goto tailrec_134;
else_140:;
    if_42 = l_2;
    goto if_next_138;
if_next_138:;
    return if_42;
}

int stringTrimIfLoop2_(struct CharBoolFun1 isTrimmed_, struct String s_10, int l_1, int r_5) {
tailrec_141:;
    bool if_43;
    if ((l_1 < r_5)) {
        goto then_143;
    } else {
        goto else_144;
    }
then_143:;
    bool app_1 = isTrimmed_.fun(isTrimmed_.env, s_10.str[(r_5 - 1)]);
    if_43 = app_1;
    goto if_next_142;
else_144:;
    if_43 = false;
    goto if_next_142;
if_next_142:;
    int if_44;
    if (if_43) {
        goto then_146;
    } else {
        goto else_147;
    }
then_146:;
    struct CharBoolFun1 arg_20 = isTrimmed_;
    struct String arg_21 = s_10;
    int arg_22 = l_1;
    int arg_23 = (r_5 - 1);
    isTrimmed_ = arg_20;
    s_10 = arg_21;
    l_1 = arg_22;
    r_5 = arg_23;
    goto tailrec_141;
else_147:;
    if_44 = r_5;
    goto if_next_145;
if_next_145:;
    return if_44;
}

struct String trimIf_(struct CharBoolFun1 isTrimmed_, struct String s_10) {
    int call_22 = stringTrimIfLoop1_(isTrimmed_, s_10, 0);
    int l_1 = call_22;
    int call_23 = stringTrimIfLoop2_(isTrimmed_, s_10, l_1, s_10.len);
    int r_4 = call_23;
    struct String if_45;
    if ((l_1 < r_4)) {
        goto then_149;
    } else {
        goto else_150;
    }
then_149:;
    struct String slice_4 = str_get_slice(l_1, (r_4 - 1), s_10);
    if_45 = slice_4;
    goto if_next_148;
else_150:;
    if_45 = (struct String){.str = "", .len = 0};
    goto if_next_148;
if_next_148:;
    return if_45;
}

int stringTrimStartIfLoop_(struct CharBoolFun1 isTrimmed_1, struct String s_11, int l_4) {
tailrec_151:;
    bool if_46;
    if ((l_4 < s_11.len)) {
        goto then_153;
    } else {
        goto else_154;
    }
then_153:;
    bool app_2 = isTrimmed_1.fun(isTrimmed_1.env, s_11.str[l_4]);
    if_46 = app_2;
    goto if_next_152;
else_154:;
    if_46 = false;
    goto if_next_152;
if_next_152:;
    int if_47;
    if (if_46) {
        goto then_156;
    } else {
        goto else_157;
    }
then_156:;
    struct CharBoolFun1 arg_24 = isTrimmed_1;
    struct String arg_25 = s_11;
    int arg_26 = (l_4 + 1);
    isTrimmed_1 = arg_24;
    s_11 = arg_25;
    l_4 = arg_26;
    goto tailrec_151;
else_157:;
    if_47 = l_4;
    goto if_next_155;
if_next_155:;
    return if_47;
}

struct String trimStartIf_(struct CharBoolFun1 isTrimmed_1, struct String s_11) {
    int call_24 = stringTrimStartIfLoop_(isTrimmed_1, s_11, 0);
    int l_3 = call_24;
    struct String if_48;
    if ((l_3 < s_11.len)) {
        goto then_159;
    } else {
        goto else_160;
    }
then_159:;
    struct String slice_5 = str_get_slice(l_3, (s_11.len - 1), s_11);
    if_48 = slice_5;
    goto if_next_158;
else_160:;
    if_48 = (struct String){.str = "", .len = 0};
    goto if_next_158;
if_next_158:;
    return if_48;
}

int stringTrimEndIfLoop_(struct CharBoolFun1 isTrimmed_2, struct String s_12, int r_7) {
tailrec_161:;
    bool if_49;
    if ((0 < r_7)) {
        goto then_163;
    } else {
        goto else_164;
    }
then_163:;
    bool app_3 = isTrimmed_2.fun(isTrimmed_2.env, s_12.str[(r_7 - 1)]);
    if_49 = app_3;
    goto if_next_162;
else_164:;
    if_49 = false;
    goto if_next_162;
if_next_162:;
    int if_50;
    if (if_49) {
        goto then_166;
    } else {
        goto else_167;
    }
then_166:;
    struct CharBoolFun1 arg_27 = isTrimmed_2;
    struct String arg_28 = s_12;
    int arg_29 = (r_7 - 1);
    isTrimmed_2 = arg_27;
    s_12 = arg_28;
    r_7 = arg_29;
    goto tailrec_161;
else_167:;
    if_50 = r_7;
    goto if_next_165;
if_next_165:;
    return if_50;
}

struct String trimEndIf_(struct CharBoolFun1 isTrimmed_2, struct String s_12) {
    int call_25 = stringTrimEndIfLoop_(isTrimmed_2, s_12, s_12.len);
    int r_6 = call_25;
    struct String if_51;
    if ((0 < r_6)) {
        goto then_169;
    } else {
        goto else_170;
    }
then_169:;
    struct String slice_6 = str_get_slice(0, (r_6 - 1), s_12);
    if_51 = slice_6;
    goto if_next_168;
else_170:;
    if_51 = (struct String){.str = "", .len = 0};
    goto if_next_168;
if_next_168:;
    return if_51;
}

bool fun_(void const* env_, char arg_) {
    bool call_26 = isSpace_(arg_);
    return call_26;
}

struct String trim_(struct String s_13) {
    struct CharBoolFun1 fun_3 = ((struct CharBoolFun1){.fun = fun_, .env = NULL});
    struct String call_27 = trimIf_(fun_3, s_13);
    return call_27;
}

bool fun_1(void const* env_1, char arg_1) {
    bool call_28 = isSpace_(arg_1);
    return call_28;
}

struct String trimStart_(struct String s_14) {
    struct CharBoolFun1 fun_4 = ((struct CharBoolFun1){.fun = fun_1, .env = NULL});
    struct String call_29 = trimStartIf_(fun_4, s_14);
    return call_29;
}

bool fun_2(void const* env_2, char arg_2) {
    bool call_30 = isSpace_(arg_2);
    return call_30;
}

struct String trimEnd_(struct String s_15) {
    struct CharBoolFun1 fun_5 = ((struct CharBoolFun1){.fun = fun_2, .env = NULL});
    struct String call_31 = trimEndIf_(fun_5, s_15);
    return call_31;
}

struct StringList const* replaceLoop_(struct String pattern_, struct String s_16, struct StringList const* acc_14, int i_6) {
tailrec_171:;
    struct StringList const* match_2;
    struct String call_32 = skip_1(i_6, s_16);
    struct IntOption call_33 = findIndex_(pattern_, call_32);
    if (call_33.some) goto next_173;
    struct String call_34 = skip_1(i_6, s_16);
    struct StringList const* list_1 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_1))) = ((struct StringList){.head = call_34, .tail = acc_14});
    match_2 = list_1;
    goto end_match_172;
next_173:;
    if ((!(call_33.some))) goto next_174;
    int n_2 = call_33.value;
    struct String arg_30 = pattern_;
    struct String arg_31 = s_16;
    struct String call_35 = skip_1(i_6, s_16);
    struct String call_36 = truncate_1(n_2, call_35);
    struct StringList const* list_2 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_2))) = ((struct StringList){.head = call_36, .tail = acc_14});
    struct StringList const* arg_32 = list_2;
    int arg_33 = ((i_6 + n_2) + pattern_.len);
    pattern_ = arg_30;
    s_16 = arg_31;
    acc_14 = arg_32;
    i_6 = arg_33;
    goto tailrec_171;
next_174:;
    exit(1);
end_match_172:;
    return match_2;
}

struct String replace_(struct String pattern_, struct String target_, struct String s_16) {
    struct String if_52;
    if ((pattern_.len == 0)) {
        goto then_176;
    } else {
        goto else_177;
    }
then_176:;
    if_52 = s_16;
    goto if_next_175;
else_177:;
    struct StringList const* call_37 = replaceLoop_(pattern_, s_16, NULL, 0);
    struct StringList const* call_38 = rev_1(call_37);
    struct String call_39 = concat_(target_, call_38);
    if_52 = call_39;
    goto if_next_175;
if_next_175:;
    return if_52;
}

int findNewline_(int start_5, struct String s_17) {
tailrec_178:;
    int i_7 = start_5;
    bool if_53;
    if ((i_7 < s_17.len)) {
        goto then_180;
    } else {
        goto else_187;
    }
then_180:;
    bool if_54;
    if ((s_17.str[i_7] != '\0')) {
        goto then_182;
    } else {
        goto else_183;
    }
then_182:;
    if_54 = (s_17.str[i_7] != '\r');
    goto if_next_181;
else_183:;
    if_54 = false;
    goto if_next_181;
if_next_181:;
    bool if_55;
    if (if_54) {
        goto then_185;
    } else {
        goto else_186;
    }
then_185:;
    if_55 = (s_17.str[i_7] != '\n');
    goto if_next_184;
else_186:;
    if_55 = false;
    goto if_next_184;
if_next_184:;
    if_53 = if_55;
    goto if_next_179;
else_187:;
    if_53 = false;
    goto if_next_179;
if_next_179:;
    int if_56;
    if (if_53) {
        goto then_189;
    } else {
        goto else_190;
    }
then_189:;
    int arg_34 = (i_7 + 1);
    struct String arg_35 = s_17;
    start_5 = arg_34;
    s_17 = arg_35;
    goto tailrec_178;
else_190:;
    if_56 = i_7;
    goto if_next_188;
if_next_188:;
    return if_56;
}

struct StringStringOptionStringTuple3 scanLine_(struct String s_18) {
    int call_40 = findNewline_(0, s_18);
    int m_ = call_40;
    struct String if_57;
    if ((0 < m_)) {
        goto then_192;
    } else {
        goto else_193;
    }
then_192:;
    struct String slice_7 = str_get_slice(0, (m_ - 1), s_18);
    if_57 = slice_7;
    goto if_next_191;
else_193:;
    if_57 = (struct String){.str = "", .len = 0};
    goto if_next_191;
if_next_191:;
    struct String lineContents_ = if_57;
    struct StringStringOptionStringTuple3 if_58;
    if ((m_ == s_18.len)) {
        goto then_195;
    } else {
        goto else_196;
    }
then_195:;
    struct StringStringOptionStringTuple3 tuple_ = ((struct StringStringOptionStringTuple3){.t0 = lineContents_, .t1 = ((struct StringOption){.some = false}), .t2 = (struct String){.str = "", .len = 0}});
    if_58 = tuple_;
    goto if_next_194;
else_196:;
    bool if_59;
    if (((m_ + 1) < s_18.len)) {
        goto then_198;
    } else {
        goto else_199;
    }
then_198:;
    if_59 = (s_18.str[m_] == '\r');
    goto if_next_197;
else_199:;
    if_59 = false;
    goto if_next_197;
if_next_197:;
    bool if_60;
    if (if_59) {
        goto then_201;
    } else {
        goto else_202;
    }
then_201:;
    if_60 = (s_18.str[(m_ + 1)] == '\n');
    goto if_next_200;
else_202:;
    if_60 = false;
    goto if_next_200;
if_next_200:;
    int if_61;
    if (if_60) {
        goto then_204;
    } else {
        goto else_205;
    }
then_204:;
    if_61 = 2;
    goto if_next_203;
else_205:;
    bool if_62;
    if ((s_18.str[m_] == '\0')) {
        goto then_207;
    } else {
        goto else_208;
    }
then_207:;
    if_62 = true;
    goto if_next_206;
else_208:;
    if_62 = (s_18.str[m_] == '\r');
    goto if_next_206;
if_next_206:;
    bool if_63;
    if (if_62) {
        goto then_210;
    } else {
        goto else_211;
    }
then_210:;
    if_63 = true;
    goto if_next_209;
else_211:;
    if_63 = (s_18.str[m_] == '\n');
    goto if_next_209;
if_next_209:;
    milone_assert(if_63, 255, 8);
    if_61 = 1;
    goto if_next_203;
if_next_203:;
    int sepLen_ = if_61;
    int r_8 = (m_ + sepLen_);
    struct String slice_8 = str_get_slice(m_, (r_8 - 1), s_18);
    struct String sep_1 = slice_8;
    struct String if_64;
    if ((r_8 < s_18.len)) {
        goto then_213;
    } else {
        goto else_214;
    }
then_213:;
    struct String slice_9 = str_get_slice(r_8, (s_18.len - 1), s_18);
    if_64 = slice_9;
    goto if_next_212;
else_214:;
    if_64 = (struct String){.str = "", .len = 0};
    goto if_next_212;
if_next_212:;
    struct String rest_ = if_64;
    struct StringOption some_4 = ((struct StringOption){.some = true, .value = sep_1});
    struct StringStringOptionStringTuple3 tuple_1 = ((struct StringStringOptionStringTuple3){.t0 = lineContents_, .t1 = some_4, .t2 = rest_});
    if_58 = tuple_1;
    goto if_next_194;
if_next_194:;
    return if_58;
}

struct StringList const* stringToLinesLoop_(struct String s_19, int l_5, struct StringList const* acc_15) {
tailrec_215:;
    int call_41 = findNewline_(l_5, s_19);
    int r_9 = call_41;
    struct String if_65;
    if ((l_5 < r_9)) {
        goto then_217;
    } else {
        goto else_218;
    }
then_217:;
    struct String slice_10 = str_get_slice(l_5, (r_9 - 1), s_19);
    if_65 = slice_10;
    goto if_next_216;
else_218:;
    if_65 = (struct String){.str = "", .len = 0};
    goto if_next_216;
if_next_216:;
    struct StringList const* list_3 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_3))) = ((struct StringList){.head = if_65, .tail = acc_15});
    struct StringList const* acc_16 = list_3;
    struct StringList const* if_66;
    if ((r_9 == s_19.len)) {
        goto then_220;
    } else {
        goto else_221;
    }
then_220:;
    if_66 = acc_16;
    goto if_next_219;
else_221:;
    bool if_67;
    if (((r_9 + 1) < s_19.len)) {
        goto then_223;
    } else {
        goto else_224;
    }
then_223:;
    if_67 = (s_19.str[r_9] == '\r');
    goto if_next_222;
else_224:;
    if_67 = false;
    goto if_next_222;
if_next_222:;
    bool if_68;
    if (if_67) {
        goto then_226;
    } else {
        goto else_227;
    }
then_226:;
    if_68 = (s_19.str[(r_9 + 1)] == '\n');
    goto if_next_225;
else_227:;
    if_68 = false;
    goto if_next_225;
if_next_225:;
    struct StringList const* if_69;
    if (if_68) {
        goto then_229;
    } else {
        goto else_230;
    }
then_229:;
    struct String arg_36 = s_19;
    int arg_37 = (r_9 + 2);
    struct StringList const* arg_38 = acc_16;
    s_19 = arg_36;
    l_5 = arg_37;
    acc_15 = arg_38;
    goto tailrec_215;
else_230:;
    bool if_70;
    if ((s_19.str[r_9] == '\r')) {
        goto then_232;
    } else {
        goto else_233;
    }
then_232:;
    if_70 = true;
    goto if_next_231;
else_233:;
    if_70 = (s_19.str[r_9] == '\n');
    goto if_next_231;
if_next_231:;
    milone_assert(if_70, 285, 6);
    struct String arg_39 = s_19;
    int arg_40 = (r_9 + 1);
    struct StringList const* arg_41 = acc_16;
    s_19 = arg_39;
    l_5 = arg_40;
    acc_15 = arg_41;
    goto tailrec_215;
if_next_228:;
    if_66 = if_69;
    goto if_next_219;
if_next_219:;
    return if_66;
}

struct StringList const* toLines_(struct String s_19) {
    struct StringList const* call_42 = stringToLinesLoop_(s_19, 0, NULL);
    struct StringList const* call_43 = rev_1(call_42);
    return call_43;
}

struct String concat_(struct String sep_2, struct StringList const* xs_61) {
    struct String call_44 = __stringJoin_(sep_2, xs_61);
    return call_44;
}

bool isNone_2(struct CharOption opt_) {
    bool match_3;
    if (opt_.some) goto next_235;
    match_3 = true;
    goto end_match_234;
next_235:;
    if ((!(opt_.some))) goto next_236;
    match_3 = false;
    goto end_match_234;
next_236:;
    exit(1);
end_match_234:;
    return match_3;
}

bool isNone_1(struct IntOption opt_) {
    bool match_4;
    if (opt_.some) goto next_238;
    match_4 = true;
    goto end_match_237;
next_238:;
    if ((!(opt_.some))) goto next_239;
    match_4 = false;
    goto end_match_237;
next_239:;
    exit(1);
end_match_237:;
    return match_4;
}

char unwrap_2(struct CharOption opt_8) {
    char match_5;
    if ((!(opt_8.some))) goto next_241;
    char value_2 = opt_8.value;
    match_5 = value_2;
    goto end_match_240;
next_241:;
    if (opt_8.some) goto next_242;
    printf("Can\'t unwrap None.\n");
    exit(1);
next_242:;
    exit(1);
end_match_240:;
    return match_5;
}

int unwrap_1(struct IntOption opt_8) {
    int match_6;
    if ((!(opt_8.some))) goto next_244;
    int value_2 = opt_8.value;
    match_6 = value_2;
    goto end_match_243;
next_244:;
    if (opt_8.some) goto next_245;
    printf("Can\'t unwrap None.\n");
    exit(1);
next_245:;
    exit(1);
end_match_243:;
    return match_6;
}

char isEmptyTest_(char arg_42) {
    bool call_45 = isEmpty_1((struct String){.str = "", .len = 0});
    milone_assert(call_45, 15, 2);
    bool call_46 = isEmpty_1((struct String){.str = "\0", .len = 1});
    milone_assert((!(call_46)), 16, 2);
    return 0;
}

char tryItemTest_(char arg_43) {
    struct CharOption call_47 = tryItem_1(0, (struct String){.str = "", .len = 0});
    bool call_48 = isNone_2(call_47);
    milone_assert(call_48, 19, 2);
    struct CharOption call_49 = tryItem_1(-1, (struct String){.str = "a", .len = 1});
    bool call_50 = isNone_2(call_49);
    milone_assert(call_50, 20, 2);
    struct CharOption call_51 = tryItem_1(1, (struct String){.str = "a", .len = 1});
    bool call_52 = isNone_2(call_51);
    milone_assert(call_52, 21, 2);
    struct CharOption call_53 = tryItem_1(2, (struct String){.str = "abc", .len = 3});
    char call_54 = unwrap_2(call_53);
    milone_assert((call_54 == 'c'), 22, 2);
    return 0;
}

char startsWithTest_(char arg_44) {
    bool call_55 = startsWith_((struct String){.str = "/bin", .len = 4}, (struct String){.str = "/usr/bin", .len = 8});
    milone_assert((!(call_55)), 25, 2);
    bool call_56 = startsWith_((struct String){.str = "/bin", .len = 4}, (struct String){.str = "/bin/ls", .len = 7});
    milone_assert(call_56, 26, 2);
    bool call_57 = startsWith_((struct String){.str = "", .len = 0}, (struct String){.str = "", .len = 0});
    milone_assert(call_57, 27, 2);
    return 0;
}

char endsWithTest_(char arg_45) {
    bool call_58 = endsWith_((struct String){.str = "/bin", .len = 4}, (struct String){.str = "/usr/bin", .len = 8});
    milone_assert(call_58, 30, 2);
    bool call_59 = endsWith_((struct String){.str = "/bin", .len = 4}, (struct String){.str = "/bin/ls", .len = 7});
    milone_assert((!(call_59)), 31, 2);
    bool call_60 = endsWith_((struct String){.str = "", .len = 0}, (struct String){.str = "", .len = 0});
    milone_assert(call_60, 32, 2);
    return 0;
}

char findIndexTest_(char arg_46) {
    struct IntOption call_61 = findIndex_((struct String){.str = "ab", .len = 2}, (struct String){.str = "", .len = 0});
    bool call_62 = isNone_1(call_61);
    milone_assert(call_62, 35, 2);
    struct IntOption call_63 = findIndex_((struct String){.str = "ab", .len = 2}, (struct String){.str = "cacbc", .len = 5});
    bool call_64 = isNone_1(call_63);
    milone_assert(call_64, 36, 2);
    struct IntOption call_65 = findIndex_((struct String){.str = "ab", .len = 2}, (struct String){.str = "abcc", .len = 4});
    int call_66 = unwrap_1(call_65);
    milone_assert((call_66 == 0), 38, 2);
    struct IntOption call_67 = findIndex_((struct String){.str = "ab", .len = 2}, (struct String){.str = "ccabccabcc", .len = 10});
    int call_68 = unwrap_1(call_67);
    milone_assert((call_68 == 2), 39, 2);
    struct IntOption call_69 = findIndex_((struct String){.str = "", .len = 0}, (struct String){.str = "", .len = 0});
    int call_70 = unwrap_1(call_69);
    milone_assert((call_70 == 0), 40, 2);
    return 0;
}

char findLastIndexTest_(char arg_47) {
    struct IntOption call_71 = findLastIndex_((struct String){.str = "ab", .len = 2}, (struct String){.str = "", .len = 0});
    bool call_72 = isNone_1(call_71);
    milone_assert(call_72, 43, 2);
    struct IntOption call_73 = findLastIndex_((struct String){.str = "ab", .len = 2}, (struct String){.str = "cacbc", .len = 5});
    bool call_74 = isNone_1(call_73);
    milone_assert(call_74, 44, 2);
    struct IntOption call_75 = findLastIndex_((struct String){.str = "ab", .len = 2}, (struct String){.str = "ccab", .len = 4});
    int call_76 = unwrap_1(call_75);
    milone_assert((call_76 == 2), 46, 2);
    struct IntOption call_77 = findLastIndex_((struct String){.str = "ab", .len = 2}, (struct String){.str = "ccabccabcc", .len = 10});
    int call_78 = unwrap_1(call_77);
    milone_assert((call_78 == 6), 47, 2);
    struct IntOption call_79 = findLastIndex_((struct String){.str = "", .len = 0}, (struct String){.str = "", .len = 0});
    int call_80 = unwrap_1(call_79);
    milone_assert((call_80 == 0), 48, 2);
    return 0;
}

char containsTest_(char arg_48) {
    bool call_81 = contains_((struct String){.str = "ab", .len = 2}, (struct String){.str = "cacbc", .len = 5});
    milone_assert((!(call_81)), 51, 2);
    bool call_82 = contains_((struct String){.str = "ab", .len = 2}, (struct String){.str = "ccabccabcc", .len = 10});
    milone_assert(call_82, 52, 2);
    bool call_83 = contains_((struct String){.str = "", .len = 0}, (struct String){.str = "", .len = 0});
    milone_assert(call_83, 53, 2);
    return 0;
}

char truncateTest_(char arg_49) {
    struct String call_84 = truncate_1(-1, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_84, (struct String){.str = "", .len = 0}) == 0), 56, 2);
    struct String call_85 = truncate_1(0, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_85, (struct String){.str = "", .len = 0}) == 0), 57, 2);
    struct String call_86 = truncate_1(1, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_86, (struct String){.str = "a", .len = 1}) == 0), 58, 2);
    struct String call_87 = truncate_1(2, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_87, (struct String){.str = "ab", .len = 2}) == 0), 59, 2);
    struct String call_88 = truncate_1(3, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_88, (struct String){.str = "ab", .len = 2}) == 0), 60, 2);
    return 0;
}

char skipTest_(char arg_50) {
    struct String call_89 = skip_1(-1, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_89, (struct String){.str = "ab", .len = 2}) == 0), 63, 2);
    struct String call_90 = skip_1(0, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_90, (struct String){.str = "ab", .len = 2}) == 0), 64, 2);
    struct String call_91 = skip_1(1, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_91, (struct String){.str = "b", .len = 1}) == 0), 65, 2);
    struct String call_92 = skip_1(2, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_92, (struct String){.str = "", .len = 0}) == 0), 66, 2);
    struct String call_93 = skip_1(3, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_93, (struct String){.str = "", .len = 0}) == 0), 67, 2);
    return 0;
}

char sliceTest_(char arg_51) {
    struct String call_94 = slice_(-2, -1, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_94, (struct String){.str = "", .len = 0}) == 0), 70, 2);
    struct String call_95 = slice_(-1, 1, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_95, (struct String){.str = "a", .len = 1}) == 0), 71, 2);
    struct String call_96 = slice_(0, 1, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_96, (struct String){.str = "a", .len = 1}) == 0), 72, 2);
    struct String call_97 = slice_(0, 2, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_97, (struct String){.str = "ab", .len = 2}) == 0), 73, 2);
    struct String call_98 = slice_(0, 3, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_98, (struct String){.str = "ab", .len = 2}) == 0), 74, 2);
    struct String call_99 = slice_(1, 2, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_99, (struct String){.str = "b", .len = 1}) == 0), 75, 2);
    struct String call_100 = slice_(1, 3, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_100, (struct String){.str = "b", .len = 1}) == 0), 76, 2);
    struct String call_101 = slice_(2, 3, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_101, (struct String){.str = "", .len = 0}) == 0), 77, 2);
    return 0;
}

char trimTest_(char arg_52) {
    struct String call_102 = trim_((struct String){.str = "  ab  ", .len = 6});
    milone_assert((str_compare(call_102, (struct String){.str = "ab", .len = 2}) == 0), 80, 2);
    struct String call_103 = trimStart_((struct String){.str = "  ab  ", .len = 6});
    milone_assert((str_compare(call_103, (struct String){.str = "ab  ", .len = 4}) == 0), 81, 2);
    struct String call_104 = trimEnd_((struct String){.str = " ab", .len = 3});
    milone_assert((str_compare(call_104, (struct String){.str = " ab", .len = 3}) == 0), 82, 2);
    return 0;
}

char replaceTest_(char arg_53) {
    struct String call_105 = replace_((struct String){.str = "a", .len = 1}, (struct String){.str = "A", .len = 1}, (struct String){.str = "abaca", .len = 5});
    milone_assert((str_compare(call_105, (struct String){.str = "AbAcA", .len = 5}) == 0), 85, 2);
    struct String call_106 = replace_((struct String){.str = "xy", .len = 2}, (struct String){.str = "yx", .len = 2}, (struct String){.str = "xyxyx", .len = 5});
    milone_assert((str_compare(call_106, (struct String){.str = "yxyxx", .len = 5}) == 0), 86, 2);
    struct String call_107 = replace_((struct String){.str = "", .len = 0}, (struct String){.str = "", .len = 0}, (struct String){.str = "as is", .len = 5});
    milone_assert((str_compare(call_107, (struct String){.str = "as is", .len = 5}) == 0), 87, 2);
    struct String call_108 = replace_((struct String){.str = "aa", .len = 2}, (struct String){.str = "a", .len = 1}, (struct String){.str = "aaaaa", .len = 5});
    milone_assert((str_compare(call_108, (struct String){.str = "aaa", .len = 3}) == 0), 88, 2);
    return 0;
}

char splitTest_(char arg_54) {
    struct StringList const* call_109 = toLines_((struct String){.str = "a\nb\nc", .len = 5});
    struct String call_110 = concat_((struct String){.str = ";", .len = 1}, call_109);
    milone_assert((str_compare(call_110, (struct String){.str = "a;b;c", .len = 5}) == 0), 91, 2);
    struct StringList const* call_111 = toLines_((struct String){.str = "a\nb\nc\n", .len = 6});
    struct String call_112 = concat_((struct String){.str = ";", .len = 1}, call_111);
    milone_assert((str_compare(call_112, (struct String){.str = "a;b;c;", .len = 6}) == 0), 92, 2);
    struct StringList const* call_113 = toLines_((struct String){.str = "a", .len = 1});
    struct String call_114 = concat_((struct String){.str = ";", .len = 1}, call_113);
    milone_assert((str_compare(call_114, (struct String){.str = "a", .len = 1}) == 0), 93, 2);
    struct StringList const* call_115 = toLines_((struct String){.str = "\n", .len = 1});
    struct String call_116 = concat_((struct String){.str = ";", .len = 1}, call_115);
    milone_assert((str_compare(call_116, (struct String){.str = ";", .len = 1}) == 0), 94, 2);
    struct StringList const* call_117 = toLines_((struct String){.str = "", .len = 0});
    struct String call_118 = concat_((struct String){.str = ";", .len = 1}, call_117);
    milone_assert((str_compare(call_118, (struct String){.str = "", .len = 0}) == 0), 95, 2);
    return 0;
}

char concatTest_(char arg_55) {
    struct StringList const* list_6 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_6))) = ((struct StringList){.head = (struct String){.str = "ef", .len = 2}, .tail = NULL});
    struct StringList const* list_5 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_5))) = ((struct StringList){.head = (struct String){.str = "cd", .len = 2}, .tail = list_6});
    struct StringList const* list_4 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_4))) = ((struct StringList){.head = (struct String){.str = "ab", .len = 2}, .tail = list_5});
    struct String call_119 = concat_((struct String){.str = ", ", .len = 2}, list_4);
    milone_assert((str_compare(call_119, (struct String){.str = "ab, cd, ef", .len = 10}) == 0), 98, 2);
    struct String call_120 = concat_((struct String){.str = "", .len = 0}, NULL);
    milone_assert((str_compare(call_120, (struct String){.str = "", .len = 0}) == 0), 99, 2);
    return 0;
}

int milone_main() {
    char call_121 = isEmptyTest_(0);
    char call_122 = tryItemTest_(0);
    char call_123 = startsWithTest_(0);
    char call_124 = endsWithTest_(0);
    char call_125 = findIndexTest_(0);
    char call_126 = findLastIndexTest_(0);
    char call_127 = containsTest_(0);
    char call_128 = truncateTest_(0);
    char call_129 = skipTest_(0);
    char call_130 = sliceTest_(0);
    char call_131 = trimTest_(0);
    char call_132 = replaceTest_(0);
    char call_133 = splitTest_(0);
    char call_134 = concatTest_(0);
    return 0;
}
