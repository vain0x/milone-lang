#include "milone.h"

struct StringList;

struct String str_concat(struct String, struct StringList const*);

struct String __stringJoin_(struct String sep_, struct StringList const* xs_);

void* milone_mem_alloc(int, uintptr_t);

void* memAlloc_(int len_, uintptr_t size_);

void* memcpy(void*, void const*, uintptr_t);

void* memcpy_(void* dest_, void const* src_, uintptr_t size_1);

struct StringList const* listRevLoop_1(struct StringList const* acc_, struct StringList const* xs_6);

struct StringList const* rev_1(struct StringList const* xs_5);

struct CharList;

bool isNone_2(struct CharList const* opt_1);

struct IntList;

bool isNone_1(struct IntList const* opt_1);

char subtract_(char l_5, char r_9);

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

int intClamp_(int minValue_, int maxValue_, int value_2);

bool isEmpty_1(struct String str_);

struct CharList const* tryItem_1(int index_4, struct String str_1);

bool occursAtLoop_(int start_2, struct String substr_, struct String s_, int i_4);

bool occursAt_(int start_2, struct String substr_, struct String s_);

bool startsWith_(struct String prefix_, struct String s_1);

bool endsWith_(struct String suffix_, struct String s_2);

struct IntList const* stringFindIndexLoop_(struct String substr_1, struct String s_3, int r_, int i_5);

struct IntList const* findIndex_(struct String substr_1, struct String s_3);

struct IntList const* stringFindLastIndexLoop_(struct String substr_2, struct String s_4, int r_1);

struct IntList const* findLastIndex_(struct String substr_2, struct String s_4);

bool contains_(struct String substr_3, struct String s_5);

struct String truncate_1(int prefixLen_, struct String s_6);

struct String skip_1(int prefixLen_1, struct String s_7);

struct String slice_(int start_3, int endIndex_2, struct String s_8);

struct CharBoolFun1;

int stringTrimIfLoop1_(struct CharBoolFun1 isTrimmed_, struct String s_9, int l_1);

int stringTrimIfLoop2_(struct CharBoolFun1 isTrimmed_, struct String s_9, int l_, int r_4);

struct String trimIf_(struct CharBoolFun1 isTrimmed_, struct String s_9);

int stringTrimStartIfLoop_(struct CharBoolFun1 isTrimmed_1, struct String s_10, int l_3);

struct String trimStartIf_(struct CharBoolFun1 isTrimmed_1, struct String s_10);

int stringTrimEndIfLoop_(struct CharBoolFun1 isTrimmed_2, struct String s_11, int r_6);

struct String trimEndIf_(struct CharBoolFun1 isTrimmed_2, struct String s_11);

bool fun_(void const* env_, char arg_);

struct String trim_(struct String s_12);

bool fun_1(void const* env_1, char arg_1);

struct String trimStart_(struct String s_13);

bool fun_2(void const* env_2, char arg_2);

struct String trimEnd_(struct String s_14);

struct StringList const* replaceLoop_(struct String pattern_, struct String s_15, struct StringList const* acc_13, int i_6);

struct String replace_(struct String pattern_, struct String target_, struct String s_15);

int findNewline_(int start_5, struct String s_16);

struct StringStringListStringTuple3;

struct StringStringListStringTuple3 scanLine_(struct String s_17);

struct StringList const* stringToLinesLoop_(struct String s_18, int l_4, struct StringList const* acc_14);

struct StringList const* toLines_(struct String s_18);

struct String concat_(struct String sep_2, struct StringList const* xs_54);

char unwrap_2(struct CharList const* opt_);

int unwrap_1(struct IntList const* opt_);

int isEmptyTest_(int arg_41);

int tryItemTest_(int arg_42);

int startsWithTest_(int arg_43);

int endsWithTest_(int arg_44);

int findIndexTest_(int arg_45);

int findLastIndexTest_(int arg_46);

int containsTest_(int arg_47);

int truncateTest_(int arg_48);

int skipTest_(int arg_49);

int sliceTest_(int arg_50);

int trimTest_(int arg_51);

int replaceTest_(int arg_52);

int splitTest_(int arg_53);

int concatTest_(int arg_54);

int main();

struct StringList {
    struct String head;
    struct StringList const* tail;
};

struct String __stringJoin_(struct String sep_, struct StringList const* xs_) {
    struct String str_concat_result_ = str_concat(sep_, xs_);
    return str_concat_result_;
}

void* memAlloc_(int len_, uintptr_t size_) {
    void* milone_mem_alloc_result_ = milone_mem_alloc(len_, size_);
    return milone_mem_alloc_result_;
}

void* memcpy_(void* dest_, void const* src_, uintptr_t size_1) {
    void* memcpy_result_ = memcpy(dest_, src_, size_1);
    return memcpy_result_;
}

struct StringList const* listRevLoop_1(struct StringList const* acc_, struct StringList const* xs_6) {
tailrec_1:;
    struct StringList const* match_;
    if ((!((!(xs_6))))) goto next_3;
    match_ = acc_;
    goto end_match_2;
next_3:;
    if ((!(xs_6))) goto next_4;
    struct String x_ = xs_6->head;
    struct StringList const* xs_7 = xs_6->tail;
    struct StringList const* list_ = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_))) = (struct StringList){.head = x_, .tail = acc_};
    struct StringList const* arg_3 = list_;
    struct StringList const* arg_4 = xs_7;
    acc_ = arg_3;
    xs_6 = arg_4;
    goto tailrec_1;
    match_ = NULL;
    goto end_match_2;
next_4:;
    exit(1);
end_match_2:;
    return match_;
}

struct StringList const* rev_1(struct StringList const* xs_5) {
    struct StringList const* call_ = listRevLoop_1(NULL, xs_5);
    return call_;
}

struct CharList {
    char head;
    struct CharList const* tail;
};

bool isNone_2(struct CharList const* opt_1) {
    bool match_1;
    if ((!((!(opt_1))))) goto next_6;
    match_1 = true;
    goto end_match_5;
next_6:;
    if ((!(opt_1))) goto next_7;
    match_1 = false;
    goto end_match_5;
next_7:;
    exit(1);
end_match_5:;
    return match_1;
}

struct IntList {
    int head;
    struct IntList const* tail;
};

bool isNone_1(struct IntList const* opt_1) {
    bool match_2;
    if ((!((!(opt_1))))) goto next_9;
    match_2 = true;
    goto end_match_8;
next_9:;
    if ((!(opt_1))) goto next_10;
    match_2 = false;
    goto end_match_8;
next_10:;
    exit(1);
end_match_8:;
    return match_2;
}

char subtract_(char l_5, char r_9) {
    return ((char)(((int)l_5) - ((int)r_9)));
}

bool isAscii_(char c_) {
    bool if_;
    if ((c_ >= '\0')) {
        goto then_12;
    } else {
        goto else_13;
    }
then_12:;
    if_ = (((char)127) >= c_);
    goto if_next_11;
else_13:;
    if_ = false;
    goto if_next_11;
if_next_11:;
    return if_;
}

bool isControl_(char c_1) {
    int n_1 = ((int)c_1);
    bool if_1;
    if ((n_1 >= 0)) {
        goto then_15;
    } else {
        goto else_16;
    }
then_15:;
    if_1 = (31 >= n_1);
    goto if_next_14;
else_16:;
    if_1 = false;
    goto if_next_14;
if_next_14:;
    bool if_2;
    if (if_1) {
        goto then_18;
    } else {
        goto else_19;
    }
then_18:;
    if_2 = true;
    goto if_next_17;
else_19:;
    if_2 = (n_1 == 127);
    goto if_next_17;
if_next_17:;
    return if_2;
}

bool isBlank_(char c_2) {
    bool if_3;
    if ((c_2 == ' ')) {
        goto then_21;
    } else {
        goto else_22;
    }
then_21:;
    if_3 = true;
    goto if_next_20;
else_22:;
    if_3 = (c_2 == '\t');
    goto if_next_20;
if_next_20:;
    return if_3;
}

bool isSpace_(char c_3) {
    bool if_4;
    if ((c_3 >= '\t')) {
        goto then_24;
    } else {
        goto else_25;
    }
then_24:;
    if_4 = ('\r' >= c_3);
    goto if_next_23;
else_25:;
    if_4 = false;
    goto if_next_23;
if_next_23:;
    bool if_5;
    if (if_4) {
        goto then_27;
    } else {
        goto else_28;
    }
then_27:;
    if_5 = true;
    goto if_next_26;
else_28:;
    if_5 = (c_3 == ' ');
    goto if_next_26;
if_next_26:;
    return if_5;
}

bool isPunctuation_(char c_4) {
    int n_2 = ((int)c_4);
    bool if_6;
    if ((n_2 >= 33)) {
        goto then_30;
    } else {
        goto else_31;
    }
then_30:;
    if_6 = (47 >= n_2);
    goto if_next_29;
else_31:;
    if_6 = false;
    goto if_next_29;
if_next_29:;
    bool if_7;
    if (if_6) {
        goto then_33;
    } else {
        goto else_34;
    }
then_33:;
    if_7 = true;
    goto if_next_32;
else_34:;
    bool if_8;
    if ((n_2 >= 58)) {
        goto then_36;
    } else {
        goto else_37;
    }
then_36:;
    if_8 = (64 >= n_2);
    goto if_next_35;
else_37:;
    if_8 = false;
    goto if_next_35;
if_next_35:;
    if_7 = if_8;
    goto if_next_32;
if_next_32:;
    bool if_9;
    if (if_7) {
        goto then_39;
    } else {
        goto else_40;
    }
then_39:;
    if_9 = true;
    goto if_next_38;
else_40:;
    bool if_10;
    if ((n_2 >= 91)) {
        goto then_42;
    } else {
        goto else_43;
    }
then_42:;
    if_10 = (96 >= n_2);
    goto if_next_41;
else_43:;
    if_10 = false;
    goto if_next_41;
if_next_41:;
    if_9 = if_10;
    goto if_next_38;
if_next_38:;
    bool if_11;
    if (if_9) {
        goto then_45;
    } else {
        goto else_46;
    }
then_45:;
    if_11 = true;
    goto if_next_44;
else_46:;
    bool if_12;
    if ((n_2 >= 123)) {
        goto then_48;
    } else {
        goto else_49;
    }
then_48:;
    if_12 = (126 >= n_2);
    goto if_next_47;
else_49:;
    if_12 = false;
    goto if_next_47;
if_next_47:;
    if_11 = if_12;
    goto if_next_44;
if_next_44:;
    return if_11;
}

bool isDigit_(char c_5) {
    bool if_13;
    if ((c_5 >= '0')) {
        goto then_51;
    } else {
        goto else_52;
    }
then_51:;
    if_13 = ('9' >= c_5);
    goto if_next_50;
else_52:;
    if_13 = false;
    goto if_next_50;
if_next_50:;
    return if_13;
}

bool isHex_(char c_6) {
    bool call_1 = isDigit_(c_6);
    bool if_14;
    if (call_1) {
        goto then_54;
    } else {
        goto else_55;
    }
then_54:;
    if_14 = true;
    goto if_next_53;
else_55:;
    bool if_15;
    if ((c_6 >= 'A')) {
        goto then_57;
    } else {
        goto else_58;
    }
then_57:;
    if_15 = ('F' >= c_6);
    goto if_next_56;
else_58:;
    if_15 = false;
    goto if_next_56;
if_next_56:;
    if_14 = if_15;
    goto if_next_53;
if_next_53:;
    bool if_16;
    if (if_14) {
        goto then_60;
    } else {
        goto else_61;
    }
then_60:;
    if_16 = true;
    goto if_next_59;
else_61:;
    bool if_17;
    if ((c_6 >= 'a')) {
        goto then_63;
    } else {
        goto else_64;
    }
then_63:;
    if_17 = ('f' >= c_6);
    goto if_next_62;
else_64:;
    if_17 = false;
    goto if_next_62;
if_next_62:;
    if_16 = if_17;
    goto if_next_59;
if_next_59:;
    return if_16;
}

bool isUpper_(char c_7) {
    bool if_18;
    if ((c_7 >= 'A')) {
        goto then_66;
    } else {
        goto else_67;
    }
then_66:;
    if_18 = ('Z' >= c_7);
    goto if_next_65;
else_67:;
    if_18 = false;
    goto if_next_65;
if_next_65:;
    return if_18;
}

bool isLower_(char c_8) {
    bool if_19;
    if ((c_8 >= 'a')) {
        goto then_69;
    } else {
        goto else_70;
    }
then_69:;
    if_19 = ('z' >= c_8);
    goto if_next_68;
else_70:;
    if_19 = false;
    goto if_next_68;
if_next_68:;
    return if_19;
}

bool isAlphabetic_(char c_9) {
    bool call_2 = isUpper_(c_9);
    bool if_20;
    if (call_2) {
        goto then_72;
    } else {
        goto else_73;
    }
then_72:;
    if_20 = true;
    goto if_next_71;
else_73:;
    bool call_3 = isLower_(c_9);
    if_20 = call_3;
    goto if_next_71;
if_next_71:;
    return if_20;
}

bool isAlphanumeric_(char c_10) {
    bool call_4 = isDigit_(c_10);
    bool if_21;
    if (call_4) {
        goto then_75;
    } else {
        goto else_76;
    }
then_75:;
    if_21 = true;
    goto if_next_74;
else_76:;
    bool call_5 = isAlphabetic_(c_10);
    if_21 = call_5;
    goto if_next_74;
if_next_74:;
    return if_21;
}

char toUpper_(char c_11) {
    bool call_6 = isLower_(c_11);
    char if_22;
    if (call_6) {
        goto then_78;
    } else {
        goto else_79;
    }
then_78:;
    char call_7 = subtract_(c_11, 'a');
    if_22 = (call_7 + 'A');
    goto if_next_77;
else_79:;
    if_22 = c_11;
    goto if_next_77;
if_next_77:;
    return if_22;
}

char toLower_(char c_12) {
    bool call_8 = isUpper_(c_12);
    char if_23;
    if (call_8) {
        goto then_81;
    } else {
        goto else_82;
    }
then_81:;
    char call_9 = subtract_(c_12, 'A');
    if_23 = (call_9 + 'a');
    goto if_next_80;
else_82:;
    if_23 = c_12;
    goto if_next_80;
if_next_80:;
    return if_23;
}

int intClamp_(int minValue_, int maxValue_, int value_2) {
    int if_24;
    if ((value_2 < minValue_)) {
        goto then_84;
    } else {
        goto else_85;
    }
then_84:;
    if_24 = minValue_;
    goto if_next_83;
else_85:;
    int if_25;
    if ((maxValue_ < value_2)) {
        goto then_87;
    } else {
        goto else_88;
    }
then_87:;
    if_25 = maxValue_;
    goto if_next_86;
else_88:;
    if_25 = value_2;
    goto if_next_86;
if_next_86:;
    if_24 = if_25;
    goto if_next_83;
if_next_83:;
    return if_24;
}

bool isEmpty_1(struct String str_) {
    return (str_.len == 0);
}

struct CharList const* tryItem_1(int index_4, struct String str_1) {
    bool if_26;
    if ((index_4 >= 0)) {
        goto then_90;
    } else {
        goto else_91;
    }
then_90:;
    if_26 = (index_4 < str_1.len);
    goto if_next_89;
else_91:;
    if_26 = false;
    goto if_next_89;
if_next_89:;
    struct CharList const* if_27;
    if (if_26) {
        goto then_93;
    } else {
        goto else_94;
    }
then_93:;
    struct CharList const* some_ = milone_mem_alloc(1, sizeof(struct CharList));
    (*(((struct CharList*)some_))) = (struct CharList){.head = str_1.str[index_4], .tail = NULL};
    if_27 = some_;
    goto if_next_92;
else_94:;
    if_27 = NULL;
    goto if_next_92;
if_next_92:;
    return if_27;
}

bool occursAtLoop_(int start_2, struct String substr_, struct String s_, int i_4) {
tailrec_95:;
    bool if_28;
    if ((i_4 == substr_.len)) {
        goto then_97;
    } else {
        goto else_98;
    }
then_97:;
    if_28 = true;
    goto if_next_96;
else_98:;
    bool if_29;
    if ((s_.str[(start_2 + i_4)] == substr_.str[i_4])) {
        goto then_100;
    } else {
        goto else_101;
    }
then_100:;
    int arg_5 = start_2;
    struct String arg_6 = substr_;
    struct String arg_7 = s_;
    int arg_8 = (i_4 + 1);
    start_2 = arg_5;
    substr_ = arg_6;
    s_ = arg_7;
    i_4 = arg_8;
    goto tailrec_95;
    if_29 = false;
    goto if_next_99;
else_101:;
    if_29 = false;
    goto if_next_99;
if_next_99:;
    if_28 = if_29;
    goto if_next_96;
if_next_96:;
    return if_28;
}

bool occursAt_(int start_2, struct String substr_, struct String s_) {
    bool if_30;
    if ((start_2 >= 0)) {
        goto then_103;
    } else {
        goto else_104;
    }
then_103:;
    if_30 = (s_.len >= (start_2 + substr_.len));
    goto if_next_102;
else_104:;
    if_30 = false;
    goto if_next_102;
if_next_102:;
    bool if_31;
    if (if_30) {
        goto then_106;
    } else {
        goto else_107;
    }
then_106:;
    bool call_10 = occursAtLoop_(start_2, substr_, s_, 0);
    if_31 = call_10;
    goto if_next_105;
else_107:;
    if_31 = false;
    goto if_next_105;
if_next_105:;
    return if_31;
}

bool startsWith_(struct String prefix_, struct String s_1) {
    bool call_11 = occursAt_(0, prefix_, s_1);
    return call_11;
}

bool endsWith_(struct String suffix_, struct String s_2) {
    bool call_12 = occursAt_((s_2.len - suffix_.len), suffix_, s_2);
    return call_12;
}

struct IntList const* stringFindIndexLoop_(struct String substr_1, struct String s_3, int r_, int i_5) {
tailrec_108:;
    struct IntList const* if_32;
    if ((i_5 >= r_)) {
        goto then_110;
    } else {
        goto else_111;
    }
then_110:;
    if_32 = NULL;
    goto if_next_109;
else_111:;
    bool call_13 = occursAt_(i_5, substr_1, s_3);
    struct IntList const* if_33;
    if (call_13) {
        goto then_113;
    } else {
        goto else_114;
    }
then_113:;
    struct IntList const* some_1 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)some_1))) = (struct IntList){.head = i_5, .tail = NULL};
    if_33 = some_1;
    goto if_next_112;
else_114:;
    struct String arg_9 = substr_1;
    struct String arg_10 = s_3;
    int arg_11 = r_;
    int arg_12 = (i_5 + 1);
    substr_1 = arg_9;
    s_3 = arg_10;
    r_ = arg_11;
    i_5 = arg_12;
    goto tailrec_108;
    if_33 = NULL;
    goto if_next_112;
if_next_112:;
    if_32 = if_33;
    goto if_next_109;
if_next_109:;
    return if_32;
}

struct IntList const* findIndex_(struct String substr_1, struct String s_3) {
    int r_ = ((s_3.len - substr_1.len) + 1);
    struct IntList const* call_14 = stringFindIndexLoop_(substr_1, s_3, r_, 0);
    return call_14;
}

struct IntList const* stringFindLastIndexLoop_(struct String substr_2, struct String s_4, int r_1) {
tailrec_115:;
    struct IntList const* if_34;
    if ((0 >= r_1)) {
        goto then_117;
    } else {
        goto else_118;
    }
then_117:;
    if_34 = NULL;
    goto if_next_116;
else_118:;
    bool call_15 = occursAt_((r_1 - 1), substr_2, s_4);
    struct IntList const* if_35;
    if (call_15) {
        goto then_120;
    } else {
        goto else_121;
    }
then_120:;
    struct IntList const* some_2 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)some_2))) = (struct IntList){.head = (r_1 - 1), .tail = NULL};
    if_35 = some_2;
    goto if_next_119;
else_121:;
    struct String arg_13 = substr_2;
    struct String arg_14 = s_4;
    int arg_15 = (r_1 - 1);
    substr_2 = arg_13;
    s_4 = arg_14;
    r_1 = arg_15;
    goto tailrec_115;
    if_35 = NULL;
    goto if_next_119;
if_next_119:;
    if_34 = if_35;
    goto if_next_116;
if_next_116:;
    return if_34;
}

struct IntList const* findLastIndex_(struct String substr_2, struct String s_4) {
    int r_2 = ((s_4.len - substr_2.len) + 1);
    struct IntList const* call_16 = stringFindLastIndexLoop_(substr_2, s_4, r_2);
    return call_16;
}

bool contains_(struct String substr_3, struct String s_5) {
    bool match_3;
    struct IntList const* call_17 = findIndex_(substr_3, s_5);
    if ((!(call_17))) goto next_123;
    match_3 = true;
    goto end_match_122;
next_123:;
    if ((!((!(call_17))))) goto next_124;
    match_3 = false;
    goto end_match_122;
next_124:;
    exit(1);
end_match_122:;
    return match_3;
}

struct String truncate_1(int prefixLen_, struct String s_6) {
    struct String if_36;
    if ((0 >= prefixLen_)) {
        goto then_126;
    } else {
        goto else_127;
    }
then_126:;
    if_36 = (struct String){.str = "", .len = 0};
    goto if_next_125;
else_127:;
    struct String if_37;
    if ((prefixLen_ >= s_6.len)) {
        goto then_129;
    } else {
        goto else_130;
    }
then_129:;
    if_37 = s_6;
    goto if_next_128;
else_130:;
    struct String slice_1 = str_get_slice(0, (prefixLen_ - 1), s_6);
    if_37 = slice_1;
    goto if_next_128;
if_next_128:;
    if_36 = if_37;
    goto if_next_125;
if_next_125:;
    return if_36;
}

struct String skip_1(int prefixLen_1, struct String s_7) {
    struct String if_38;
    if ((0 >= prefixLen_1)) {
        goto then_132;
    } else {
        goto else_133;
    }
then_132:;
    if_38 = s_7;
    goto if_next_131;
else_133:;
    struct String if_39;
    if ((prefixLen_1 >= s_7.len)) {
        goto then_135;
    } else {
        goto else_136;
    }
then_135:;
    if_39 = (struct String){.str = "", .len = 0};
    goto if_next_134;
else_136:;
    struct String slice_2 = str_get_slice(prefixLen_1, (s_7.len - 1), s_7);
    if_39 = slice_2;
    goto if_next_134;
if_next_134:;
    if_38 = if_39;
    goto if_next_131;
if_next_131:;
    return if_38;
}

struct String slice_(int start_3, int endIndex_2, struct String s_8) {
    int call_18 = intClamp_(0, s_8.len, start_3);
    int start_4 = call_18;
    int call_19 = intClamp_(start_4, s_8.len, endIndex_2);
    int endIndex_3 = call_19;
    struct String if_40;
    if ((start_4 < endIndex_3)) {
        goto then_138;
    } else {
        goto else_139;
    }
then_138:;
    struct String slice_3 = str_get_slice(start_4, (endIndex_3 - 1), s_8);
    if_40 = slice_3;
    goto if_next_137;
else_139:;
    if_40 = (struct String){.str = "", .len = 0};
    goto if_next_137;
if_next_137:;
    return if_40;
}

struct CharBoolFun1 {
    bool(*fun)(void const*, char);
    void const* env;
};

int stringTrimIfLoop1_(struct CharBoolFun1 isTrimmed_, struct String s_9, int l_1) {
tailrec_140:;
    bool if_41;
    if ((l_1 < s_9.len)) {
        goto then_142;
    } else {
        goto else_143;
    }
then_142:;
    bool app_ = isTrimmed_.fun(isTrimmed_.env, s_9.str[l_1]);
    if_41 = app_;
    goto if_next_141;
else_143:;
    if_41 = false;
    goto if_next_141;
if_next_141:;
    int if_42;
    if (if_41) {
        goto then_145;
    } else {
        goto else_146;
    }
then_145:;
    struct CharBoolFun1 arg_16 = isTrimmed_;
    struct String arg_17 = s_9;
    int arg_18 = (l_1 + 1);
    isTrimmed_ = arg_16;
    s_9 = arg_17;
    l_1 = arg_18;
    goto tailrec_140;
    if_42 = 0;
    goto if_next_144;
else_146:;
    if_42 = l_1;
    goto if_next_144;
if_next_144:;
    return if_42;
}

int stringTrimIfLoop2_(struct CharBoolFun1 isTrimmed_, struct String s_9, int l_, int r_4) {
tailrec_147:;
    bool if_43;
    if ((l_ < r_4)) {
        goto then_149;
    } else {
        goto else_150;
    }
then_149:;
    bool app_1 = isTrimmed_.fun(isTrimmed_.env, s_9.str[(r_4 - 1)]);
    if_43 = app_1;
    goto if_next_148;
else_150:;
    if_43 = false;
    goto if_next_148;
if_next_148:;
    int if_44;
    if (if_43) {
        goto then_152;
    } else {
        goto else_153;
    }
then_152:;
    struct CharBoolFun1 arg_19 = isTrimmed_;
    struct String arg_20 = s_9;
    int arg_21 = l_;
    int arg_22 = (r_4 - 1);
    isTrimmed_ = arg_19;
    s_9 = arg_20;
    l_ = arg_21;
    r_4 = arg_22;
    goto tailrec_147;
    if_44 = 0;
    goto if_next_151;
else_153:;
    if_44 = r_4;
    goto if_next_151;
if_next_151:;
    return if_44;
}

struct String trimIf_(struct CharBoolFun1 isTrimmed_, struct String s_9) {
    int call_20 = stringTrimIfLoop1_(isTrimmed_, s_9, 0);
    int l_ = call_20;
    int call_21 = stringTrimIfLoop2_(isTrimmed_, s_9, l_, s_9.len);
    int r_3 = call_21;
    struct String if_45;
    if ((l_ < r_3)) {
        goto then_155;
    } else {
        goto else_156;
    }
then_155:;
    struct String slice_4 = str_get_slice(l_, (r_3 - 1), s_9);
    if_45 = slice_4;
    goto if_next_154;
else_156:;
    if_45 = (struct String){.str = "", .len = 0};
    goto if_next_154;
if_next_154:;
    return if_45;
}

int stringTrimStartIfLoop_(struct CharBoolFun1 isTrimmed_1, struct String s_10, int l_3) {
tailrec_157:;
    bool if_46;
    if ((l_3 < s_10.len)) {
        goto then_159;
    } else {
        goto else_160;
    }
then_159:;
    bool app_2 = isTrimmed_1.fun(isTrimmed_1.env, s_10.str[l_3]);
    if_46 = app_2;
    goto if_next_158;
else_160:;
    if_46 = false;
    goto if_next_158;
if_next_158:;
    int if_47;
    if (if_46) {
        goto then_162;
    } else {
        goto else_163;
    }
then_162:;
    struct CharBoolFun1 arg_23 = isTrimmed_1;
    struct String arg_24 = s_10;
    int arg_25 = (l_3 + 1);
    isTrimmed_1 = arg_23;
    s_10 = arg_24;
    l_3 = arg_25;
    goto tailrec_157;
    if_47 = 0;
    goto if_next_161;
else_163:;
    if_47 = l_3;
    goto if_next_161;
if_next_161:;
    return if_47;
}

struct String trimStartIf_(struct CharBoolFun1 isTrimmed_1, struct String s_10) {
    int call_22 = stringTrimStartIfLoop_(isTrimmed_1, s_10, 0);
    int l_2 = call_22;
    struct String if_48;
    if ((l_2 < s_10.len)) {
        goto then_165;
    } else {
        goto else_166;
    }
then_165:;
    struct String slice_5 = str_get_slice(l_2, (s_10.len - 1), s_10);
    if_48 = slice_5;
    goto if_next_164;
else_166:;
    if_48 = (struct String){.str = "", .len = 0};
    goto if_next_164;
if_next_164:;
    return if_48;
}

int stringTrimEndIfLoop_(struct CharBoolFun1 isTrimmed_2, struct String s_11, int r_6) {
tailrec_167:;
    bool if_49;
    if ((0 < r_6)) {
        goto then_169;
    } else {
        goto else_170;
    }
then_169:;
    bool app_3 = isTrimmed_2.fun(isTrimmed_2.env, s_11.str[(r_6 - 1)]);
    if_49 = app_3;
    goto if_next_168;
else_170:;
    if_49 = false;
    goto if_next_168;
if_next_168:;
    int if_50;
    if (if_49) {
        goto then_172;
    } else {
        goto else_173;
    }
then_172:;
    struct CharBoolFun1 arg_26 = isTrimmed_2;
    struct String arg_27 = s_11;
    int arg_28 = (r_6 - 1);
    isTrimmed_2 = arg_26;
    s_11 = arg_27;
    r_6 = arg_28;
    goto tailrec_167;
    if_50 = 0;
    goto if_next_171;
else_173:;
    if_50 = r_6;
    goto if_next_171;
if_next_171:;
    return if_50;
}

struct String trimEndIf_(struct CharBoolFun1 isTrimmed_2, struct String s_11) {
    int call_23 = stringTrimEndIfLoop_(isTrimmed_2, s_11, s_11.len);
    int r_5 = call_23;
    struct String if_51;
    if ((0 < r_5)) {
        goto then_175;
    } else {
        goto else_176;
    }
then_175:;
    struct String slice_6 = str_get_slice(0, (r_5 - 1), s_11);
    if_51 = slice_6;
    goto if_next_174;
else_176:;
    if_51 = (struct String){.str = "", .len = 0};
    goto if_next_174;
if_next_174:;
    return if_51;
}

bool fun_(void const* env_, char arg_) {
    bool call_24 = isSpace_(arg_);
    return call_24;
}

struct String trim_(struct String s_12) {
    void const* box_ = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_))) = 0;
    void const* env_3 = box_;
    struct CharBoolFun1 fun_3 = (struct CharBoolFun1){.fun = fun_, .env = env_3};
    struct String call_25 = trimIf_(fun_3, s_12);
    return call_25;
}

bool fun_1(void const* env_1, char arg_1) {
    bool call_26 = isSpace_(arg_1);
    return call_26;
}

struct String trimStart_(struct String s_13) {
    void const* box_1 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_1))) = 0;
    void const* env_4 = box_1;
    struct CharBoolFun1 fun_4 = (struct CharBoolFun1){.fun = fun_1, .env = env_4};
    struct String call_27 = trimStartIf_(fun_4, s_13);
    return call_27;
}

bool fun_2(void const* env_2, char arg_2) {
    bool call_28 = isSpace_(arg_2);
    return call_28;
}

struct String trimEnd_(struct String s_14) {
    void const* box_2 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_2))) = 0;
    void const* env_5 = box_2;
    struct CharBoolFun1 fun_5 = (struct CharBoolFun1){.fun = fun_2, .env = env_5};
    struct String call_29 = trimEndIf_(fun_5, s_14);
    return call_29;
}

struct StringList const* replaceLoop_(struct String pattern_, struct String s_15, struct StringList const* acc_13, int i_6) {
tailrec_177:;
    struct StringList const* match_4;
    struct String call_30 = skip_1(i_6, s_15);
    struct IntList const* call_31 = findIndex_(pattern_, call_30);
    if ((!((!(call_31))))) goto next_179;
    struct String call_32 = skip_1(i_6, s_15);
    struct StringList const* list_1 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_1))) = (struct StringList){.head = call_32, .tail = acc_13};
    match_4 = list_1;
    goto end_match_178;
next_179:;
    if ((!(call_31))) goto next_180;
    int n_ = call_31->head;
    struct String arg_29 = pattern_;
    struct String arg_30 = s_15;
    struct String call_33 = skip_1(i_6, s_15);
    struct String call_34 = truncate_1(n_, call_33);
    struct StringList const* list_2 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_2))) = (struct StringList){.head = call_34, .tail = acc_13};
    struct StringList const* arg_31 = list_2;
    int arg_32 = ((i_6 + n_) + pattern_.len);
    pattern_ = arg_29;
    s_15 = arg_30;
    acc_13 = arg_31;
    i_6 = arg_32;
    goto tailrec_177;
    match_4 = NULL;
    goto end_match_178;
next_180:;
    exit(1);
end_match_178:;
    return match_4;
}

struct String replace_(struct String pattern_, struct String target_, struct String s_15) {
    struct String if_52;
    if ((pattern_.len == 0)) {
        goto then_182;
    } else {
        goto else_183;
    }
then_182:;
    if_52 = s_15;
    goto if_next_181;
else_183:;
    struct StringList const* call_35 = replaceLoop_(pattern_, s_15, NULL, 0);
    struct StringList const* call_36 = rev_1(call_35);
    struct String call_37 = concat_(target_, call_36);
    if_52 = call_37;
    goto if_next_181;
if_next_181:;
    return if_52;
}

int findNewline_(int start_5, struct String s_16) {
tailrec_184:;
    int i_7 = start_5;
    bool if_53;
    if ((i_7 < s_16.len)) {
        goto then_186;
    } else {
        goto else_193;
    }
then_186:;
    bool if_54;
    if ((s_16.str[i_7] != '\0')) {
        goto then_188;
    } else {
        goto else_189;
    }
then_188:;
    if_54 = (s_16.str[i_7] != '\r');
    goto if_next_187;
else_189:;
    if_54 = false;
    goto if_next_187;
if_next_187:;
    bool if_55;
    if (if_54) {
        goto then_191;
    } else {
        goto else_192;
    }
then_191:;
    if_55 = (s_16.str[i_7] != '\n');
    goto if_next_190;
else_192:;
    if_55 = false;
    goto if_next_190;
if_next_190:;
    if_53 = if_55;
    goto if_next_185;
else_193:;
    if_53 = false;
    goto if_next_185;
if_next_185:;
    int if_56;
    if (if_53) {
        goto then_195;
    } else {
        goto else_196;
    }
then_195:;
    int arg_33 = (i_7 + 1);
    struct String arg_34 = s_16;
    start_5 = arg_33;
    s_16 = arg_34;
    goto tailrec_184;
    if_56 = 0;
    goto if_next_194;
else_196:;
    if_56 = i_7;
    goto if_next_194;
if_next_194:;
    return if_56;
}

struct StringStringListStringTuple3 {
    struct String t0;
    struct StringList const* t1;
    struct String t2;
};

struct StringStringListStringTuple3 scanLine_(struct String s_17) {
    int call_38 = findNewline_(0, s_17);
    int m_ = call_38;
    struct String if_57;
    if ((0 < m_)) {
        goto then_198;
    } else {
        goto else_199;
    }
then_198:;
    struct String slice_7 = str_get_slice(0, (m_ - 1), s_17);
    if_57 = slice_7;
    goto if_next_197;
else_199:;
    if_57 = (struct String){.str = "", .len = 0};
    goto if_next_197;
if_next_197:;
    struct String lineContents_ = if_57;
    struct StringStringListStringTuple3 if_58;
    if ((m_ == s_17.len)) {
        goto then_201;
    } else {
        goto else_202;
    }
then_201:;
    struct StringStringListStringTuple3 tuple_;
    tuple_.t0 = lineContents_;
    tuple_.t1 = NULL;
    tuple_.t2 = (struct String){.str = "", .len = 0};
    if_58 = tuple_;
    goto if_next_200;
else_202:;
    bool if_59;
    if (((m_ + 1) < s_17.len)) {
        goto then_204;
    } else {
        goto else_205;
    }
then_204:;
    if_59 = (s_17.str[m_] == '\r');
    goto if_next_203;
else_205:;
    if_59 = false;
    goto if_next_203;
if_next_203:;
    bool if_60;
    if (if_59) {
        goto then_207;
    } else {
        goto else_208;
    }
then_207:;
    if_60 = (s_17.str[(m_ + 1)] == '\n');
    goto if_next_206;
else_208:;
    if_60 = false;
    goto if_next_206;
if_next_206:;
    int if_61;
    if (if_60) {
        goto then_210;
    } else {
        goto else_211;
    }
then_210:;
    if_61 = 2;
    goto if_next_209;
else_211:;
    bool if_62;
    if ((s_17.str[m_] == '\0')) {
        goto then_213;
    } else {
        goto else_214;
    }
then_213:;
    if_62 = true;
    goto if_next_212;
else_214:;
    if_62 = (s_17.str[m_] == '\r');
    goto if_next_212;
if_next_212:;
    bool if_63;
    if (if_62) {
        goto then_216;
    } else {
        goto else_217;
    }
then_216:;
    if_63 = true;
    goto if_next_215;
else_217:;
    if_63 = (s_17.str[m_] == '\n');
    goto if_next_215;
if_next_215:;
    milone_assert(if_63, 204, 8);
    if_61 = 1;
    goto if_next_209;
if_next_209:;
    int sepLen_ = if_61;
    int r_7 = (m_ + sepLen_);
    struct String slice_8 = str_get_slice(m_, (r_7 - 1), s_17);
    struct String sep_1 = slice_8;
    struct String if_64;
    if ((r_7 < s_17.len)) {
        goto then_219;
    } else {
        goto else_220;
    }
then_219:;
    struct String slice_9 = str_get_slice(r_7, (s_17.len - 1), s_17);
    if_64 = slice_9;
    goto if_next_218;
else_220:;
    if_64 = (struct String){.str = "", .len = 0};
    goto if_next_218;
if_next_218:;
    struct String rest_ = if_64;
    struct StringList const* some_3 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)some_3))) = (struct StringList){.head = sep_1, .tail = NULL};
    struct StringStringListStringTuple3 tuple_1;
    tuple_1.t0 = lineContents_;
    tuple_1.t1 = some_3;
    tuple_1.t2 = rest_;
    if_58 = tuple_1;
    goto if_next_200;
if_next_200:;
    return if_58;
}

struct StringList const* stringToLinesLoop_(struct String s_18, int l_4, struct StringList const* acc_14) {
tailrec_221:;
    int call_39 = findNewline_(l_4, s_18);
    int r_8 = call_39;
    struct String if_65;
    if ((l_4 < r_8)) {
        goto then_223;
    } else {
        goto else_224;
    }
then_223:;
    struct String slice_10 = str_get_slice(l_4, (r_8 - 1), s_18);
    if_65 = slice_10;
    goto if_next_222;
else_224:;
    if_65 = (struct String){.str = "", .len = 0};
    goto if_next_222;
if_next_222:;
    struct StringList const* list_3 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_3))) = (struct StringList){.head = if_65, .tail = acc_14};
    struct StringList const* acc_15 = list_3;
    struct StringList const* if_66;
    if ((r_8 == s_18.len)) {
        goto then_226;
    } else {
        goto else_227;
    }
then_226:;
    if_66 = acc_15;
    goto if_next_225;
else_227:;
    bool if_67;
    if (((r_8 + 1) < s_18.len)) {
        goto then_229;
    } else {
        goto else_230;
    }
then_229:;
    if_67 = (s_18.str[r_8] == '\r');
    goto if_next_228;
else_230:;
    if_67 = false;
    goto if_next_228;
if_next_228:;
    bool if_68;
    if (if_67) {
        goto then_232;
    } else {
        goto else_233;
    }
then_232:;
    if_68 = (s_18.str[(r_8 + 1)] == '\n');
    goto if_next_231;
else_233:;
    if_68 = false;
    goto if_next_231;
if_next_231:;
    struct StringList const* if_69;
    if (if_68) {
        goto then_235;
    } else {
        goto else_236;
    }
then_235:;
    struct String arg_35 = s_18;
    int arg_36 = (r_8 + 2);
    struct StringList const* arg_37 = acc_15;
    s_18 = arg_35;
    l_4 = arg_36;
    acc_14 = arg_37;
    goto tailrec_221;
    if_69 = NULL;
    goto if_next_234;
else_236:;
    bool if_70;
    if ((s_18.str[r_8] == '\r')) {
        goto then_238;
    } else {
        goto else_239;
    }
then_238:;
    if_70 = true;
    goto if_next_237;
else_239:;
    if_70 = (s_18.str[r_8] == '\n');
    goto if_next_237;
if_next_237:;
    milone_assert(if_70, 231, 6);
    struct String arg_38 = s_18;
    int arg_39 = (r_8 + 1);
    struct StringList const* arg_40 = acc_15;
    s_18 = arg_38;
    l_4 = arg_39;
    acc_14 = arg_40;
    goto tailrec_221;
    if_69 = NULL;
    goto if_next_234;
if_next_234:;
    if_66 = if_69;
    goto if_next_225;
if_next_225:;
    return if_66;
}

struct StringList const* toLines_(struct String s_18) {
    struct StringList const* call_40 = stringToLinesLoop_(s_18, 0, NULL);
    struct StringList const* call_41 = rev_1(call_40);
    return call_41;
}

struct String concat_(struct String sep_2, struct StringList const* xs_54) {
    struct String call_42 = __stringJoin_(sep_2, xs_54);
    return call_42;
}

char unwrap_2(struct CharList const* opt_) {
    char match_5;
    if ((!(opt_))) goto next_241;
    char value_1 = opt_->head;
    match_5 = value_1;
    goto end_match_240;
next_241:;
    if ((!((!(opt_))))) goto next_242;
    printf("Can\'t unwrap None.\n");
    exit(1);
    match_5 = 0;
    goto end_match_240;
next_242:;
    exit(1);
end_match_240:;
    return match_5;
}

int unwrap_1(struct IntList const* opt_) {
    int match_6;
    if ((!(opt_))) goto next_244;
    int value_1 = opt_->head;
    match_6 = value_1;
    goto end_match_243;
next_244:;
    if ((!((!(opt_))))) goto next_245;
    printf("Can\'t unwrap None.\n");
    exit(1);
    match_6 = 0;
    goto end_match_243;
next_245:;
    exit(1);
end_match_243:;
    return match_6;
}

int isEmptyTest_(int arg_41) {
    bool call_43 = isEmpty_1((struct String){.str = "", .len = 0});
    milone_assert(call_43, 18, 2);
    bool call_44 = isEmpty_1((struct String){.str = "\0", .len = 1});
    milone_assert((!(call_44)), 19, 2);
    return 0;
}

int tryItemTest_(int arg_42) {
    struct CharList const* call_45 = tryItem_1(0, (struct String){.str = "", .len = 0});
    bool call_46 = isNone_2(call_45);
    milone_assert(call_46, 22, 2);
    struct CharList const* call_47 = tryItem_1(-1, (struct String){.str = "a", .len = 1});
    bool call_48 = isNone_2(call_47);
    milone_assert(call_48, 23, 2);
    struct CharList const* call_49 = tryItem_1(1, (struct String){.str = "a", .len = 1});
    bool call_50 = isNone_2(call_49);
    milone_assert(call_50, 24, 2);
    struct CharList const* call_51 = tryItem_1(2, (struct String){.str = "abc", .len = 3});
    char call_52 = unwrap_2(call_51);
    milone_assert((call_52 == 'c'), 25, 2);
    return 0;
}

int startsWithTest_(int arg_43) {
    bool call_53 = startsWith_((struct String){.str = "/bin", .len = 4}, (struct String){.str = "/usr/bin", .len = 8});
    milone_assert((!(call_53)), 28, 2);
    bool call_54 = startsWith_((struct String){.str = "/bin", .len = 4}, (struct String){.str = "/bin/ls", .len = 7});
    milone_assert(call_54, 29, 2);
    bool call_55 = startsWith_((struct String){.str = "", .len = 0}, (struct String){.str = "", .len = 0});
    milone_assert(call_55, 30, 2);
    return 0;
}

int endsWithTest_(int arg_44) {
    bool call_56 = endsWith_((struct String){.str = "/bin", .len = 4}, (struct String){.str = "/usr/bin", .len = 8});
    milone_assert(call_56, 33, 2);
    bool call_57 = endsWith_((struct String){.str = "/bin", .len = 4}, (struct String){.str = "/bin/ls", .len = 7});
    milone_assert((!(call_57)), 34, 2);
    bool call_58 = endsWith_((struct String){.str = "", .len = 0}, (struct String){.str = "", .len = 0});
    milone_assert(call_58, 35, 2);
    return 0;
}

int findIndexTest_(int arg_45) {
    struct IntList const* call_59 = findIndex_((struct String){.str = "ab", .len = 2}, (struct String){.str = "", .len = 0});
    bool call_60 = isNone_1(call_59);
    milone_assert(call_60, 38, 2);
    struct IntList const* call_61 = findIndex_((struct String){.str = "ab", .len = 2}, (struct String){.str = "cacbc", .len = 5});
    bool call_62 = isNone_1(call_61);
    milone_assert(call_62, 39, 2);
    struct IntList const* call_63 = findIndex_((struct String){.str = "ab", .len = 2}, (struct String){.str = "abcc", .len = 4});
    int call_64 = unwrap_1(call_63);
    milone_assert((call_64 == 0), 41, 2);
    struct IntList const* call_65 = findIndex_((struct String){.str = "ab", .len = 2}, (struct String){.str = "ccabccabcc", .len = 10});
    int call_66 = unwrap_1(call_65);
    milone_assert((call_66 == 2), 42, 2);
    struct IntList const* call_67 = findIndex_((struct String){.str = "", .len = 0}, (struct String){.str = "", .len = 0});
    int call_68 = unwrap_1(call_67);
    milone_assert((call_68 == 0), 43, 2);
    return 0;
}

int findLastIndexTest_(int arg_46) {
    struct IntList const* call_69 = findLastIndex_((struct String){.str = "ab", .len = 2}, (struct String){.str = "", .len = 0});
    bool call_70 = isNone_1(call_69);
    milone_assert(call_70, 46, 2);
    struct IntList const* call_71 = findLastIndex_((struct String){.str = "ab", .len = 2}, (struct String){.str = "cacbc", .len = 5});
    bool call_72 = isNone_1(call_71);
    milone_assert(call_72, 47, 2);
    struct IntList const* call_73 = findLastIndex_((struct String){.str = "ab", .len = 2}, (struct String){.str = "ccab", .len = 4});
    int call_74 = unwrap_1(call_73);
    milone_assert((call_74 == 2), 49, 2);
    struct IntList const* call_75 = findLastIndex_((struct String){.str = "ab", .len = 2}, (struct String){.str = "ccabccabcc", .len = 10});
    int call_76 = unwrap_1(call_75);
    milone_assert((call_76 == 6), 50, 2);
    struct IntList const* call_77 = findLastIndex_((struct String){.str = "", .len = 0}, (struct String){.str = "", .len = 0});
    int call_78 = unwrap_1(call_77);
    milone_assert((call_78 == 0), 51, 2);
    return 0;
}

int containsTest_(int arg_47) {
    bool call_79 = contains_((struct String){.str = "ab", .len = 2}, (struct String){.str = "cacbc", .len = 5});
    milone_assert((!(call_79)), 54, 2);
    bool call_80 = contains_((struct String){.str = "ab", .len = 2}, (struct String){.str = "ccabccabcc", .len = 10});
    milone_assert(call_80, 55, 2);
    bool call_81 = contains_((struct String){.str = "", .len = 0}, (struct String){.str = "", .len = 0});
    milone_assert(call_81, 56, 2);
    return 0;
}

int truncateTest_(int arg_48) {
    struct String call_82 = truncate_1(-1, (struct String){.str = "ab", .len = 2});
    milone_assert((str_cmp(call_82, (struct String){.str = "", .len = 0}) == 0), 59, 2);
    struct String call_83 = truncate_1(0, (struct String){.str = "ab", .len = 2});
    milone_assert((str_cmp(call_83, (struct String){.str = "", .len = 0}) == 0), 60, 2);
    struct String call_84 = truncate_1(1, (struct String){.str = "ab", .len = 2});
    milone_assert((str_cmp(call_84, (struct String){.str = "a", .len = 1}) == 0), 61, 2);
    struct String call_85 = truncate_1(2, (struct String){.str = "ab", .len = 2});
    milone_assert((str_cmp(call_85, (struct String){.str = "ab", .len = 2}) == 0), 62, 2);
    struct String call_86 = truncate_1(3, (struct String){.str = "ab", .len = 2});
    milone_assert((str_cmp(call_86, (struct String){.str = "ab", .len = 2}) == 0), 63, 2);
    return 0;
}

int skipTest_(int arg_49) {
    struct String call_87 = skip_1(-1, (struct String){.str = "ab", .len = 2});
    milone_assert((str_cmp(call_87, (struct String){.str = "ab", .len = 2}) == 0), 66, 2);
    struct String call_88 = skip_1(0, (struct String){.str = "ab", .len = 2});
    milone_assert((str_cmp(call_88, (struct String){.str = "ab", .len = 2}) == 0), 67, 2);
    struct String call_89 = skip_1(1, (struct String){.str = "ab", .len = 2});
    milone_assert((str_cmp(call_89, (struct String){.str = "b", .len = 1}) == 0), 68, 2);
    struct String call_90 = skip_1(2, (struct String){.str = "ab", .len = 2});
    milone_assert((str_cmp(call_90, (struct String){.str = "", .len = 0}) == 0), 69, 2);
    struct String call_91 = skip_1(3, (struct String){.str = "ab", .len = 2});
    milone_assert((str_cmp(call_91, (struct String){.str = "", .len = 0}) == 0), 70, 2);
    return 0;
}

int sliceTest_(int arg_50) {
    struct String call_92 = slice_(-2, -1, (struct String){.str = "ab", .len = 2});
    milone_assert((str_cmp(call_92, (struct String){.str = "", .len = 0}) == 0), 73, 2);
    struct String call_93 = slice_(-1, 1, (struct String){.str = "ab", .len = 2});
    milone_assert((str_cmp(call_93, (struct String){.str = "a", .len = 1}) == 0), 74, 2);
    struct String call_94 = slice_(0, 1, (struct String){.str = "ab", .len = 2});
    milone_assert((str_cmp(call_94, (struct String){.str = "a", .len = 1}) == 0), 75, 2);
    struct String call_95 = slice_(0, 2, (struct String){.str = "ab", .len = 2});
    milone_assert((str_cmp(call_95, (struct String){.str = "ab", .len = 2}) == 0), 76, 2);
    struct String call_96 = slice_(0, 3, (struct String){.str = "ab", .len = 2});
    milone_assert((str_cmp(call_96, (struct String){.str = "ab", .len = 2}) == 0), 77, 2);
    struct String call_97 = slice_(1, 2, (struct String){.str = "ab", .len = 2});
    milone_assert((str_cmp(call_97, (struct String){.str = "b", .len = 1}) == 0), 78, 2);
    struct String call_98 = slice_(1, 3, (struct String){.str = "ab", .len = 2});
    milone_assert((str_cmp(call_98, (struct String){.str = "b", .len = 1}) == 0), 79, 2);
    struct String call_99 = slice_(2, 3, (struct String){.str = "ab", .len = 2});
    milone_assert((str_cmp(call_99, (struct String){.str = "", .len = 0}) == 0), 80, 2);
    return 0;
}

int trimTest_(int arg_51) {
    struct String call_100 = trim_((struct String){.str = "  ab  ", .len = 6});
    milone_assert((str_cmp(call_100, (struct String){.str = "ab", .len = 2}) == 0), 83, 2);
    struct String call_101 = trimStart_((struct String){.str = "  ab  ", .len = 6});
    milone_assert((str_cmp(call_101, (struct String){.str = "ab  ", .len = 4}) == 0), 84, 2);
    struct String call_102 = trimEnd_((struct String){.str = " ab", .len = 3});
    milone_assert((str_cmp(call_102, (struct String){.str = " ab", .len = 3}) == 0), 85, 2);
    return 0;
}

int replaceTest_(int arg_52) {
    struct String call_103 = replace_((struct String){.str = "a", .len = 1}, (struct String){.str = "A", .len = 1}, (struct String){.str = "abaca", .len = 5});
    milone_assert((str_cmp(call_103, (struct String){.str = "AbAcA", .len = 5}) == 0), 88, 2);
    struct String call_104 = replace_((struct String){.str = "xy", .len = 2}, (struct String){.str = "yx", .len = 2}, (struct String){.str = "xyxyx", .len = 5});
    milone_assert((str_cmp(call_104, (struct String){.str = "yxyxx", .len = 5}) == 0), 89, 2);
    struct String call_105 = replace_((struct String){.str = "", .len = 0}, (struct String){.str = "", .len = 0}, (struct String){.str = "as is", .len = 5});
    milone_assert((str_cmp(call_105, (struct String){.str = "as is", .len = 5}) == 0), 90, 2);
    struct String call_106 = replace_((struct String){.str = "aa", .len = 2}, (struct String){.str = "a", .len = 1}, (struct String){.str = "aaaaa", .len = 5});
    milone_assert((str_cmp(call_106, (struct String){.str = "aaa", .len = 3}) == 0), 91, 2);
    return 0;
}

int splitTest_(int arg_53) {
    struct StringList const* call_107 = toLines_((struct String){.str = "a\nb\nc", .len = 5});
    struct String call_108 = concat_((struct String){.str = ";", .len = 1}, call_107);
    milone_assert((str_cmp(call_108, (struct String){.str = "a;b;c", .len = 5}) == 0), 94, 2);
    struct StringList const* call_109 = toLines_((struct String){.str = "a\nb\nc\n", .len = 6});
    struct String call_110 = concat_((struct String){.str = ";", .len = 1}, call_109);
    milone_assert((str_cmp(call_110, (struct String){.str = "a;b;c;", .len = 6}) == 0), 95, 2);
    struct StringList const* call_111 = toLines_((struct String){.str = "a", .len = 1});
    struct String call_112 = concat_((struct String){.str = ";", .len = 1}, call_111);
    milone_assert((str_cmp(call_112, (struct String){.str = "a", .len = 1}) == 0), 96, 2);
    struct StringList const* call_113 = toLines_((struct String){.str = "\n", .len = 1});
    struct String call_114 = concat_((struct String){.str = ";", .len = 1}, call_113);
    milone_assert((str_cmp(call_114, (struct String){.str = ";", .len = 1}) == 0), 97, 2);
    struct StringList const* call_115 = toLines_((struct String){.str = "", .len = 0});
    struct String call_116 = concat_((struct String){.str = ";", .len = 1}, call_115);
    milone_assert((str_cmp(call_116, (struct String){.str = "", .len = 0}) == 0), 98, 2);
    return 0;
}

int concatTest_(int arg_54) {
    struct StringList const* list_6 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_6))) = (struct StringList){.head = (struct String){.str = "ef", .len = 2}, .tail = NULL};
    struct StringList const* list_5 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_5))) = (struct StringList){.head = (struct String){.str = "cd", .len = 2}, .tail = list_6};
    struct StringList const* list_4 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_4))) = (struct StringList){.head = (struct String){.str = "ab", .len = 2}, .tail = list_5};
    struct String call_117 = concat_((struct String){.str = ", ", .len = 2}, list_4);
    milone_assert((str_cmp(call_117, (struct String){.str = "ab, cd, ef", .len = 10}) == 0), 101, 2);
    struct String call_118 = concat_((struct String){.str = "", .len = 0}, NULL);
    milone_assert((str_cmp(call_118, (struct String){.str = "", .len = 0}) == 0), 102, 2);
    return 0;
}

int main() {
    int call_119 = isEmptyTest_(0);
    int call_120 = tryItemTest_(0);
    int call_121 = startsWithTest_(0);
    int call_122 = endsWithTest_(0);
    int call_123 = findIndexTest_(0);
    int call_124 = findLastIndexTest_(0);
    int call_125 = containsTest_(0);
    int call_126 = truncateTest_(0);
    int call_127 = skipTest_(0);
    int call_128 = sliceTest_(0);
    int call_129 = trimTest_(0);
    int call_130 = replaceTest_(0);
    int call_131 = splitTest_(0);
    int call_132 = concatTest_(0);
    return 0;
}
