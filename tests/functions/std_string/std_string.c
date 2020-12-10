#include "milone.h"

struct StringList;

struct String str_concat(struct String, struct StringList const*);

struct String __stringJoin_(struct String sep_, struct StringList const* xs_);

struct StringList const* listRevLoop_1(struct StringList const* acc_, struct StringList const* xs_6);

struct StringList const* rev_1(struct StringList const* xs_5);

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

int intClamp_(int minValue_, int maxValue_, int value_);

bool isEmpty_1(struct String str_);

struct CharList;

struct CharList const* tryItem_1(int index_, struct String str_1);

bool occursAtLoop_(int start_, struct String substr_, struct String s_, int i_4);

bool occursAt_(int start_, struct String substr_, struct String s_);

bool startsWith_(struct String prefix_, struct String s_1);

bool endsWith_(struct String suffix_, struct String s_2);

struct IntList;

struct IntList const* stringFindIndexLoop_(struct String substr_1, struct String s_3, int r_, int i_5);

struct IntList const* findIndex_(struct String substr_1, struct String s_3);

struct IntList const* stringFindLastIndexLoop_(struct String substr_2, struct String s_4, int r_1);

struct IntList const* findLastIndex_(struct String substr_2, struct String s_4);

bool contains_(struct String substr_3, struct String s_5);

struct String truncate_1(int prefixLen_, struct String s_6);

struct String skip_1(int prefixLen_1, struct String s_7);

struct String slice_(int start_1, int endIndex_, struct String s_8);

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

int findNewline_(int start_3, struct String s_16);

struct StringStringListStringTuple3;

struct StringStringListStringTuple3 scanLine_(struct String s_17);

struct StringList const* stringToLinesLoop_(struct String s_18, int l_4, struct StringList const* acc_14);

struct StringList const* toLines_(struct String s_18);

struct String concat_(struct String sep_2, struct StringList const* xs_53);

int replaceTest_(int arg_41);

int main();

struct StringList {
    struct String head;
    struct StringList const* tail;
};

struct String __stringJoin_(struct String sep_, struct StringList const* xs_) {
    struct String str_concat_result_ = str_concat(sep_, xs_);
    return str_concat_result_;
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

char subtract_(char l_5, char r_9) {
    return ((char)(((int)l_5) - ((int)r_9)));
}

bool isAscii_(char c_) {
    bool if_;
    if ((c_ >= '\0')) {
        goto then_6;
    } else {
        goto else_7;
    }
then_6:;
    if_ = (((char)127) >= c_);
    goto if_next_5;
else_7:;
    if_ = false;
    goto if_next_5;
if_next_5:;
    return if_;
}

bool isControl_(char c_1) {
    int n_1 = ((int)c_1);
    bool if_1;
    if ((n_1 >= 0)) {
        goto then_9;
    } else {
        goto else_10;
    }
then_9:;
    if_1 = (31 >= n_1);
    goto if_next_8;
else_10:;
    if_1 = false;
    goto if_next_8;
if_next_8:;
    bool if_2;
    if (if_1) {
        goto then_12;
    } else {
        goto else_13;
    }
then_12:;
    if_2 = true;
    goto if_next_11;
else_13:;
    if_2 = (n_1 == 127);
    goto if_next_11;
if_next_11:;
    return if_2;
}

bool isBlank_(char c_2) {
    bool if_3;
    if ((c_2 == ' ')) {
        goto then_15;
    } else {
        goto else_16;
    }
then_15:;
    if_3 = true;
    goto if_next_14;
else_16:;
    if_3 = (c_2 == '\t');
    goto if_next_14;
if_next_14:;
    return if_3;
}

bool isSpace_(char c_3) {
    bool if_4;
    if ((c_3 >= '\t')) {
        goto then_18;
    } else {
        goto else_19;
    }
then_18:;
    if_4 = ('\r' >= c_3);
    goto if_next_17;
else_19:;
    if_4 = false;
    goto if_next_17;
if_next_17:;
    bool if_5;
    if (if_4) {
        goto then_21;
    } else {
        goto else_22;
    }
then_21:;
    if_5 = true;
    goto if_next_20;
else_22:;
    if_5 = (c_3 == ' ');
    goto if_next_20;
if_next_20:;
    return if_5;
}

bool isPunctuation_(char c_4) {
    int n_2 = ((int)c_4);
    bool if_6;
    if ((n_2 >= 33)) {
        goto then_24;
    } else {
        goto else_25;
    }
then_24:;
    if_6 = (47 >= n_2);
    goto if_next_23;
else_25:;
    if_6 = false;
    goto if_next_23;
if_next_23:;
    bool if_7;
    if (if_6) {
        goto then_27;
    } else {
        goto else_28;
    }
then_27:;
    if_7 = true;
    goto if_next_26;
else_28:;
    bool if_8;
    if ((n_2 >= 58)) {
        goto then_30;
    } else {
        goto else_31;
    }
then_30:;
    if_8 = (64 >= n_2);
    goto if_next_29;
else_31:;
    if_8 = false;
    goto if_next_29;
if_next_29:;
    if_7 = if_8;
    goto if_next_26;
if_next_26:;
    bool if_9;
    if (if_7) {
        goto then_33;
    } else {
        goto else_34;
    }
then_33:;
    if_9 = true;
    goto if_next_32;
else_34:;
    bool if_10;
    if ((n_2 >= 91)) {
        goto then_36;
    } else {
        goto else_37;
    }
then_36:;
    if_10 = (96 >= n_2);
    goto if_next_35;
else_37:;
    if_10 = false;
    goto if_next_35;
if_next_35:;
    if_9 = if_10;
    goto if_next_32;
if_next_32:;
    bool if_11;
    if (if_9) {
        goto then_39;
    } else {
        goto else_40;
    }
then_39:;
    if_11 = true;
    goto if_next_38;
else_40:;
    bool if_12;
    if ((n_2 >= 123)) {
        goto then_42;
    } else {
        goto else_43;
    }
then_42:;
    if_12 = (126 >= n_2);
    goto if_next_41;
else_43:;
    if_12 = false;
    goto if_next_41;
if_next_41:;
    if_11 = if_12;
    goto if_next_38;
if_next_38:;
    return if_11;
}

bool isDigit_(char c_5) {
    bool if_13;
    if ((c_5 >= '0')) {
        goto then_45;
    } else {
        goto else_46;
    }
then_45:;
    if_13 = ('9' >= c_5);
    goto if_next_44;
else_46:;
    if_13 = false;
    goto if_next_44;
if_next_44:;
    return if_13;
}

bool isHex_(char c_6) {
    bool call_1 = isDigit_(c_6);
    bool if_14;
    if (call_1) {
        goto then_48;
    } else {
        goto else_49;
    }
then_48:;
    if_14 = true;
    goto if_next_47;
else_49:;
    bool if_15;
    if ((c_6 >= 'A')) {
        goto then_51;
    } else {
        goto else_52;
    }
then_51:;
    if_15 = ('F' >= c_6);
    goto if_next_50;
else_52:;
    if_15 = false;
    goto if_next_50;
if_next_50:;
    if_14 = if_15;
    goto if_next_47;
if_next_47:;
    bool if_16;
    if (if_14) {
        goto then_54;
    } else {
        goto else_55;
    }
then_54:;
    if_16 = true;
    goto if_next_53;
else_55:;
    bool if_17;
    if ((c_6 >= 'a')) {
        goto then_57;
    } else {
        goto else_58;
    }
then_57:;
    if_17 = ('f' >= c_6);
    goto if_next_56;
else_58:;
    if_17 = false;
    goto if_next_56;
if_next_56:;
    if_16 = if_17;
    goto if_next_53;
if_next_53:;
    return if_16;
}

bool isUpper_(char c_7) {
    bool if_18;
    if ((c_7 >= 'A')) {
        goto then_60;
    } else {
        goto else_61;
    }
then_60:;
    if_18 = ('Z' >= c_7);
    goto if_next_59;
else_61:;
    if_18 = false;
    goto if_next_59;
if_next_59:;
    return if_18;
}

bool isLower_(char c_8) {
    bool if_19;
    if ((c_8 >= 'a')) {
        goto then_63;
    } else {
        goto else_64;
    }
then_63:;
    if_19 = ('z' >= c_8);
    goto if_next_62;
else_64:;
    if_19 = false;
    goto if_next_62;
if_next_62:;
    return if_19;
}

bool isAlphabetic_(char c_9) {
    bool call_2 = isUpper_(c_9);
    bool if_20;
    if (call_2) {
        goto then_66;
    } else {
        goto else_67;
    }
then_66:;
    if_20 = true;
    goto if_next_65;
else_67:;
    bool call_3 = isLower_(c_9);
    if_20 = call_3;
    goto if_next_65;
if_next_65:;
    return if_20;
}

bool isAlphanumeric_(char c_10) {
    bool call_4 = isDigit_(c_10);
    bool if_21;
    if (call_4) {
        goto then_69;
    } else {
        goto else_70;
    }
then_69:;
    if_21 = true;
    goto if_next_68;
else_70:;
    bool call_5 = isAlphabetic_(c_10);
    if_21 = call_5;
    goto if_next_68;
if_next_68:;
    return if_21;
}

char toUpper_(char c_11) {
    bool call_6 = isLower_(c_11);
    char if_22;
    if (call_6) {
        goto then_72;
    } else {
        goto else_73;
    }
then_72:;
    char call_7 = subtract_(c_11, 'a');
    if_22 = (call_7 + 'A');
    goto if_next_71;
else_73:;
    if_22 = c_11;
    goto if_next_71;
if_next_71:;
    return if_22;
}

char toLower_(char c_12) {
    bool call_8 = isUpper_(c_12);
    char if_23;
    if (call_8) {
        goto then_75;
    } else {
        goto else_76;
    }
then_75:;
    char call_9 = subtract_(c_12, 'A');
    if_23 = (call_9 + 'a');
    goto if_next_74;
else_76:;
    if_23 = c_12;
    goto if_next_74;
if_next_74:;
    return if_23;
}

int intClamp_(int minValue_, int maxValue_, int value_) {
    int if_24;
    if ((value_ < minValue_)) {
        goto then_78;
    } else {
        goto else_79;
    }
then_78:;
    if_24 = minValue_;
    goto if_next_77;
else_79:;
    int if_25;
    if ((maxValue_ < value_)) {
        goto then_81;
    } else {
        goto else_82;
    }
then_81:;
    if_25 = maxValue_;
    goto if_next_80;
else_82:;
    if_25 = value_;
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

struct CharList {
    char head;
    struct CharList const* tail;
};

struct CharList const* tryItem_1(int index_, struct String str_1) {
    bool if_26;
    if ((index_ >= 0)) {
        goto then_84;
    } else {
        goto else_85;
    }
then_84:;
    if_26 = (str_1.len >= index_);
    goto if_next_83;
else_85:;
    if_26 = false;
    goto if_next_83;
if_next_83:;
    struct CharList const* if_27;
    if (if_26) {
        goto then_87;
    } else {
        goto else_88;
    }
then_87:;
    struct CharList const* some_ = milone_mem_alloc(1, sizeof(struct CharList));
    (*(((struct CharList*)some_))) = (struct CharList){.head = str_1.str[index_], .tail = NULL};
    if_27 = some_;
    goto if_next_86;
else_88:;
    if_27 = NULL;
    goto if_next_86;
if_next_86:;
    return if_27;
}

bool occursAtLoop_(int start_, struct String substr_, struct String s_, int i_4) {
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
    if ((s_.str[(start_ + i_4)] == substr_.str[i_4])) {
        goto then_94;
    } else {
        goto else_95;
    }
then_94:;
    int arg_5 = start_;
    struct String arg_6 = substr_;
    struct String arg_7 = s_;
    int arg_8 = (i_4 + 1);
    start_ = arg_5;
    substr_ = arg_6;
    s_ = arg_7;
    i_4 = arg_8;
    goto tailrec_89;
    if_29 = false;
    goto if_next_93;
else_95:;
    if_29 = false;
    goto if_next_93;
if_next_93:;
    if_28 = if_29;
    goto if_next_90;
if_next_90:;
    return if_28;
}

bool occursAt_(int start_, struct String substr_, struct String s_) {
    bool if_30;
    if ((start_ >= 0)) {
        goto then_97;
    } else {
        goto else_98;
    }
then_97:;
    if_30 = (s_.len >= (start_ + substr_.len));
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
    bool call_10 = occursAtLoop_(start_, substr_, s_, 0);
    if_31 = call_10;
    goto if_next_99;
else_101:;
    if_31 = false;
    goto if_next_99;
if_next_99:;
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

struct IntList {
    int head;
    struct IntList const* tail;
};

struct IntList const* stringFindIndexLoop_(struct String substr_1, struct String s_3, int r_, int i_5) {
tailrec_102:;
    struct IntList const* if_32;
    if ((i_5 >= r_)) {
        goto then_104;
    } else {
        goto else_105;
    }
then_104:;
    if_32 = NULL;
    goto if_next_103;
else_105:;
    bool call_13 = occursAt_(i_5, substr_1, s_3);
    struct IntList const* if_33;
    if (call_13) {
        goto then_107;
    } else {
        goto else_108;
    }
then_107:;
    struct IntList const* some_1 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)some_1))) = (struct IntList){.head = i_5, .tail = NULL};
    if_33 = some_1;
    goto if_next_106;
else_108:;
    struct String arg_9 = substr_1;
    struct String arg_10 = s_3;
    int arg_11 = r_;
    int arg_12 = (i_5 + 1);
    substr_1 = arg_9;
    s_3 = arg_10;
    r_ = arg_11;
    i_5 = arg_12;
    goto tailrec_102;
    if_33 = NULL;
    goto if_next_106;
if_next_106:;
    if_32 = if_33;
    goto if_next_103;
if_next_103:;
    return if_32;
}

struct IntList const* findIndex_(struct String substr_1, struct String s_3) {
    int r_ = ((s_3.len - substr_1.len) + 1);
    struct IntList const* call_14 = stringFindIndexLoop_(substr_1, s_3, r_, 0);
    return call_14;
}

struct IntList const* stringFindLastIndexLoop_(struct String substr_2, struct String s_4, int r_1) {
tailrec_109:;
    struct IntList const* if_34;
    if ((0 >= r_1)) {
        goto then_111;
    } else {
        goto else_112;
    }
then_111:;
    if_34 = NULL;
    goto if_next_110;
else_112:;
    bool call_15 = occursAt_((r_1 - 1), substr_2, s_4);
    struct IntList const* if_35;
    if (call_15) {
        goto then_114;
    } else {
        goto else_115;
    }
then_114:;
    struct IntList const* some_2 = milone_mem_alloc(1, sizeof(struct IntList));
    (*(((struct IntList*)some_2))) = (struct IntList){.head = (r_1 - 1), .tail = NULL};
    if_35 = some_2;
    goto if_next_113;
else_115:;
    struct String arg_13 = substr_2;
    struct String arg_14 = s_4;
    int arg_15 = (r_1 - 1);
    substr_2 = arg_13;
    s_4 = arg_14;
    r_1 = arg_15;
    goto tailrec_109;
    if_35 = NULL;
    goto if_next_113;
if_next_113:;
    if_34 = if_35;
    goto if_next_110;
if_next_110:;
    return if_34;
}

struct IntList const* findLastIndex_(struct String substr_2, struct String s_4) {
    int r_2 = ((s_4.len - substr_2.len) + 1);
    struct IntList const* call_16 = stringFindLastIndexLoop_(substr_2, s_4, r_2);
    return call_16;
}

bool contains_(struct String substr_3, struct String s_5) {
    bool match_1;
    struct IntList const* call_17 = findIndex_(substr_3, s_5);
    if ((!(call_17))) goto next_117;
    match_1 = true;
    goto end_match_116;
next_117:;
    if ((!((!(call_17))))) goto next_118;
    match_1 = false;
    goto end_match_116;
next_118:;
    exit(1);
end_match_116:;
    return match_1;
}

struct String truncate_1(int prefixLen_, struct String s_6) {
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
    if ((prefixLen_ >= s_6.len)) {
        goto then_123;
    } else {
        goto else_124;
    }
then_123:;
    if_37 = s_6;
    goto if_next_122;
else_124:;
    struct String slice_1 = str_get_slice(0, (prefixLen_ - 1), s_6);
    if_37 = slice_1;
    goto if_next_122;
if_next_122:;
    if_36 = if_37;
    goto if_next_119;
if_next_119:;
    return if_36;
}

struct String skip_1(int prefixLen_1, struct String s_7) {
    struct String if_38;
    if ((0 >= prefixLen_1)) {
        goto then_126;
    } else {
        goto else_127;
    }
then_126:;
    if_38 = s_7;
    goto if_next_125;
else_127:;
    struct String if_39;
    if ((prefixLen_1 >= s_7.len)) {
        goto then_129;
    } else {
        goto else_130;
    }
then_129:;
    if_39 = (struct String){.str = "", .len = 0};
    goto if_next_128;
else_130:;
    struct String slice_2 = str_get_slice(prefixLen_1, (s_7.len - 1), s_7);
    if_39 = slice_2;
    goto if_next_128;
if_next_128:;
    if_38 = if_39;
    goto if_next_125;
if_next_125:;
    return if_38;
}

struct String slice_(int start_1, int endIndex_, struct String s_8) {
    int call_18 = intClamp_(0, s_8.len, start_1);
    int start_2 = call_18;
    int call_19 = intClamp_(start_2, s_8.len, endIndex_);
    int endIndex_1 = call_19;
    struct String if_40;
    if ((start_2 < endIndex_1)) {
        goto then_132;
    } else {
        goto else_133;
    }
then_132:;
    struct String slice_3 = str_get_slice(start_2, (endIndex_1 - 1), s_8);
    if_40 = slice_3;
    goto if_next_131;
else_133:;
    if_40 = (struct String){.str = "", .len = 0};
    goto if_next_131;
if_next_131:;
    return if_40;
}

struct CharBoolFun1 {
    bool(*fun)(void const*, char);
    void const* env;
};

int stringTrimIfLoop1_(struct CharBoolFun1 isTrimmed_, struct String s_9, int l_1) {
tailrec_134:;
    bool if_41;
    if ((l_1 < s_9.len)) {
        goto then_136;
    } else {
        goto else_137;
    }
then_136:;
    bool app_ = isTrimmed_.fun(isTrimmed_.env, s_9.str[l_1]);
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
    struct CharBoolFun1 arg_16 = isTrimmed_;
    struct String arg_17 = s_9;
    int arg_18 = (l_1 + 1);
    isTrimmed_ = arg_16;
    s_9 = arg_17;
    l_1 = arg_18;
    goto tailrec_134;
    if_42 = 0;
    goto if_next_138;
else_140:;
    if_42 = l_1;
    goto if_next_138;
if_next_138:;
    return if_42;
}

int stringTrimIfLoop2_(struct CharBoolFun1 isTrimmed_, struct String s_9, int l_, int r_4) {
tailrec_141:;
    bool if_43;
    if ((l_ < r_4)) {
        goto then_143;
    } else {
        goto else_144;
    }
then_143:;
    bool app_1 = isTrimmed_.fun(isTrimmed_.env, s_9.str[(r_4 - 1)]);
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
    struct CharBoolFun1 arg_19 = isTrimmed_;
    struct String arg_20 = s_9;
    int arg_21 = l_;
    int arg_22 = (r_4 - 1);
    isTrimmed_ = arg_19;
    s_9 = arg_20;
    l_ = arg_21;
    r_4 = arg_22;
    goto tailrec_141;
    if_44 = 0;
    goto if_next_145;
else_147:;
    if_44 = r_4;
    goto if_next_145;
if_next_145:;
    return if_44;
}

struct String trimIf_(struct CharBoolFun1 isTrimmed_, struct String s_9) {
    int call_20 = stringTrimIfLoop1_(isTrimmed_, s_9, 0);
    int l_ = call_20;
    int call_21 = stringTrimIfLoop2_(isTrimmed_, s_9, l_, s_9.len);
    int r_3 = call_21;
    struct String if_45;
    if ((l_ < r_3)) {
        goto then_149;
    } else {
        goto else_150;
    }
then_149:;
    struct String slice_4 = str_get_slice(l_, (r_3 - 1), s_9);
    if_45 = slice_4;
    goto if_next_148;
else_150:;
    if_45 = (struct String){.str = "", .len = 0};
    goto if_next_148;
if_next_148:;
    return if_45;
}

int stringTrimStartIfLoop_(struct CharBoolFun1 isTrimmed_1, struct String s_10, int l_3) {
tailrec_151:;
    bool if_46;
    if ((l_3 < s_10.len)) {
        goto then_153;
    } else {
        goto else_154;
    }
then_153:;
    bool app_2 = isTrimmed_1.fun(isTrimmed_1.env, s_10.str[l_3]);
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
    struct CharBoolFun1 arg_23 = isTrimmed_1;
    struct String arg_24 = s_10;
    int arg_25 = (l_3 + 1);
    isTrimmed_1 = arg_23;
    s_10 = arg_24;
    l_3 = arg_25;
    goto tailrec_151;
    if_47 = 0;
    goto if_next_155;
else_157:;
    if_47 = l_3;
    goto if_next_155;
if_next_155:;
    return if_47;
}

struct String trimStartIf_(struct CharBoolFun1 isTrimmed_1, struct String s_10) {
    int call_22 = stringTrimStartIfLoop_(isTrimmed_1, s_10, 0);
    int l_2 = call_22;
    struct String if_48;
    if ((l_2 < s_10.len)) {
        goto then_159;
    } else {
        goto else_160;
    }
then_159:;
    struct String slice_5 = str_get_slice(l_2, (s_10.len - 1), s_10);
    if_48 = slice_5;
    goto if_next_158;
else_160:;
    if_48 = (struct String){.str = "", .len = 0};
    goto if_next_158;
if_next_158:;
    return if_48;
}

int stringTrimEndIfLoop_(struct CharBoolFun1 isTrimmed_2, struct String s_11, int r_6) {
tailrec_161:;
    bool if_49;
    if ((0 < r_6)) {
        goto then_163;
    } else {
        goto else_164;
    }
then_163:;
    bool app_3 = isTrimmed_2.fun(isTrimmed_2.env, s_11.str[(r_6 - 1)]);
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
    struct CharBoolFun1 arg_26 = isTrimmed_2;
    struct String arg_27 = s_11;
    int arg_28 = (r_6 - 1);
    isTrimmed_2 = arg_26;
    s_11 = arg_27;
    r_6 = arg_28;
    goto tailrec_161;
    if_50 = 0;
    goto if_next_165;
else_167:;
    if_50 = r_6;
    goto if_next_165;
if_next_165:;
    return if_50;
}

struct String trimEndIf_(struct CharBoolFun1 isTrimmed_2, struct String s_11) {
    int call_23 = stringTrimEndIfLoop_(isTrimmed_2, s_11, s_11.len);
    int r_5 = call_23;
    struct String if_51;
    if ((0 < r_5)) {
        goto then_169;
    } else {
        goto else_170;
    }
then_169:;
    struct String slice_6 = str_get_slice(0, (r_5 - 1), s_11);
    if_51 = slice_6;
    goto if_next_168;
else_170:;
    if_51 = (struct String){.str = "", .len = 0};
    goto if_next_168;
if_next_168:;
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
tailrec_171:;
    struct StringList const* match_2;
    struct String call_30 = skip_1(i_6, s_15);
    struct IntList const* call_31 = findIndex_(pattern_, call_30);
    if ((!((!(call_31))))) goto next_173;
    struct String call_32 = skip_1(i_6, s_15);
    struct StringList const* list_1 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_1))) = (struct StringList){.head = call_32, .tail = acc_13};
    match_2 = list_1;
    goto end_match_172;
next_173:;
    if ((!(call_31))) goto next_174;
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
    goto tailrec_171;
    match_2 = NULL;
    goto end_match_172;
next_174:;
    exit(1);
end_match_172:;
    return match_2;
}

struct String replace_(struct String pattern_, struct String target_, struct String s_15) {
    struct String if_52;
    if ((pattern_.len == 0)) {
        goto then_176;
    } else {
        goto else_177;
    }
then_176:;
    if_52 = s_15;
    goto if_next_175;
else_177:;
    struct StringList const* call_35 = replaceLoop_(pattern_, s_15, NULL, 0);
    struct StringList const* call_36 = rev_1(call_35);
    struct String call_37 = concat_(target_, call_36);
    if_52 = call_37;
    goto if_next_175;
if_next_175:;
    return if_52;
}

int findNewline_(int start_3, struct String s_16) {
tailrec_178:;
    int i_7 = start_3;
    bool if_53;
    if ((i_7 < s_16.len)) {
        goto then_180;
    } else {
        goto else_187;
    }
then_180:;
    bool if_54;
    if ((s_16.str[i_7] != '\0')) {
        goto then_182;
    } else {
        goto else_183;
    }
then_182:;
    if_54 = (s_16.str[i_7] != '\r');
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
    if_55 = (s_16.str[i_7] != '\n');
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
    int arg_33 = (i_7 + 1);
    struct String arg_34 = s_16;
    start_3 = arg_33;
    s_16 = arg_34;
    goto tailrec_178;
    if_56 = 0;
    goto if_next_188;
else_190:;
    if_56 = i_7;
    goto if_next_188;
if_next_188:;
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
        goto then_192;
    } else {
        goto else_193;
    }
then_192:;
    struct String slice_7 = str_get_slice(0, (m_ - 1), s_17);
    if_57 = slice_7;
    goto if_next_191;
else_193:;
    if_57 = (struct String){.str = "", .len = 0};
    goto if_next_191;
if_next_191:;
    struct String lineContents_ = if_57;
    struct StringStringListStringTuple3 if_58;
    if ((m_ == s_17.len)) {
        goto then_195;
    } else {
        goto else_196;
    }
then_195:;
    struct StringStringListStringTuple3 tuple_;
    tuple_.t0 = lineContents_;
    tuple_.t1 = NULL;
    tuple_.t2 = (struct String){.str = "", .len = 0};
    if_58 = tuple_;
    goto if_next_194;
else_196:;
    bool if_59;
    if (((m_ + 1) < s_17.len)) {
        goto then_198;
    } else {
        goto else_199;
    }
then_198:;
    if_59 = (s_17.str[m_] == '\r');
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
    if_60 = (s_17.str[(m_ + 1)] == '\n');
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
    if ((s_17.str[m_] == '\0')) {
        goto then_207;
    } else {
        goto else_208;
    }
then_207:;
    if_62 = true;
    goto if_next_206;
else_208:;
    if_62 = (s_17.str[m_] == '\r');
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
    if_63 = (s_17.str[m_] == '\n');
    goto if_next_209;
if_next_209:;
    milone_assert(if_63, 204, 8);
    if_61 = 1;
    goto if_next_203;
if_next_203:;
    int sepLen_ = if_61;
    int r_7 = (m_ + sepLen_);
    struct String slice_8 = str_get_slice(m_, (r_7 - 1), s_17);
    struct String sep_1 = slice_8;
    struct String if_64;
    if ((r_7 < s_17.len)) {
        goto then_213;
    } else {
        goto else_214;
    }
then_213:;
    struct String slice_9 = str_get_slice(r_7, (s_17.len - 1), s_17);
    if_64 = slice_9;
    goto if_next_212;
else_214:;
    if_64 = (struct String){.str = "", .len = 0};
    goto if_next_212;
if_next_212:;
    struct String rest_ = if_64;
    struct StringList const* some_3 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)some_3))) = (struct StringList){.head = sep_1, .tail = NULL};
    struct StringStringListStringTuple3 tuple_1;
    tuple_1.t0 = lineContents_;
    tuple_1.t1 = some_3;
    tuple_1.t2 = rest_;
    if_58 = tuple_1;
    goto if_next_194;
if_next_194:;
    return if_58;
}

struct StringList const* stringToLinesLoop_(struct String s_18, int l_4, struct StringList const* acc_14) {
tailrec_215:;
    int call_39 = findNewline_(l_4, s_18);
    int r_8 = call_39;
    struct String if_65;
    if ((l_4 < r_8)) {
        goto then_217;
    } else {
        goto else_218;
    }
then_217:;
    struct String slice_10 = str_get_slice(l_4, (r_8 - 1), s_18);
    if_65 = slice_10;
    goto if_next_216;
else_218:;
    if_65 = (struct String){.str = "", .len = 0};
    goto if_next_216;
if_next_216:;
    struct StringList const* list_3 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_3))) = (struct StringList){.head = if_65, .tail = acc_14};
    struct StringList const* acc_15 = list_3;
    struct StringList const* if_66;
    if ((r_8 == s_18.len)) {
        goto then_220;
    } else {
        goto else_221;
    }
then_220:;
    if_66 = acc_15;
    goto if_next_219;
else_221:;
    bool if_67;
    if (((r_8 + 1) < s_18.len)) {
        goto then_223;
    } else {
        goto else_224;
    }
then_223:;
    if_67 = (s_18.str[r_8] == '\r');
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
    if_68 = (s_18.str[(r_8 + 1)] == '\n');
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
    struct String arg_35 = s_18;
    int arg_36 = (r_8 + 2);
    struct StringList const* arg_37 = acc_15;
    s_18 = arg_35;
    l_4 = arg_36;
    acc_14 = arg_37;
    goto tailrec_215;
    if_69 = NULL;
    goto if_next_228;
else_230:;
    bool if_70;
    if ((s_18.str[r_8] == '\r')) {
        goto then_232;
    } else {
        goto else_233;
    }
then_232:;
    if_70 = true;
    goto if_next_231;
else_233:;
    if_70 = (s_18.str[r_8] == '\n');
    goto if_next_231;
if_next_231:;
    milone_assert(if_70, 231, 6);
    struct String arg_38 = s_18;
    int arg_39 = (r_8 + 1);
    struct StringList const* arg_40 = acc_15;
    s_18 = arg_38;
    l_4 = arg_39;
    acc_14 = arg_40;
    goto tailrec_215;
    if_69 = NULL;
    goto if_next_228;
if_next_228:;
    if_66 = if_69;
    goto if_next_219;
if_next_219:;
    return if_66;
}

struct StringList const* toLines_(struct String s_18) {
    struct StringList const* call_40 = stringToLinesLoop_(s_18, 0, NULL);
    struct StringList const* call_41 = rev_1(call_40);
    return call_41;
}

struct String concat_(struct String sep_2, struct StringList const* xs_53) {
    struct String call_42 = __stringJoin_(sep_2, xs_53);
    return call_42;
}

int replaceTest_(int arg_41) {
    struct String call_43 = replace_((struct String){.str = "a", .len = 1}, (struct String){.str = "A", .len = 1}, (struct String){.str = "abaca", .len = 5});
    milone_assert((str_cmp(call_43, (struct String){.str = "AbAcA", .len = 5}) == 0), 7, 2);
    struct String call_44 = replace_((struct String){.str = "xy", .len = 2}, (struct String){.str = "yx", .len = 2}, (struct String){.str = "xyxyx", .len = 5});
    milone_assert((str_cmp(call_44, (struct String){.str = "yxyxx", .len = 5}) == 0), 8, 2);
    struct String call_45 = replace_((struct String){.str = "", .len = 0}, (struct String){.str = "", .len = 0}, (struct String){.str = "as is", .len = 5});
    milone_assert((str_cmp(call_45, (struct String){.str = "as is", .len = 5}) == 0), 9, 2);
    struct String call_46 = replace_((struct String){.str = "aa", .len = 2}, (struct String){.str = "a", .len = 1}, (struct String){.str = "aaaaa", .len = 5});
    milone_assert((str_cmp(call_46, (struct String){.str = "aaa", .len = 3}) == 0), 10, 2);
    return 0;
}

int main() {
    int call_47 = replaceTest_(0);
    return 0;
}
