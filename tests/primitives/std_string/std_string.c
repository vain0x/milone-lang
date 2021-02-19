#include "milone.h"

struct StringList;

struct String str_concat(struct String, struct StringList const*);

struct String __stringJoin_(struct String sep_2, struct StringList const* xs_54);

int const* __ptrAsConst_1(int* mutPtr_);

void* milone_mem_alloc(int, uintptr_t);

void* memAlloc_(int len_3, uintptr_t size_);

void* memcpy(void*, void const*, uintptr_t);

void* memcpy_(void* dest_, void const* src_, uintptr_t size_1);

bool str_to_int_checked(struct String, int*);

struct IntOption;

struct IntOption __intOfStr_(struct String s_19);

int milone_get_arg_count();

int __argCount_(int arg_3);

struct String milone_get_arg(int);

struct String __argGet_(int index_5);

struct CharOption;

bool isNone_2(struct CharOption opt_1);

bool isNone_1(struct IntOption opt_1);

struct StringList;

struct StringList const* listRevLoop_1(struct StringList const* acc_3, struct StringList const* xs_6);

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

int intClamp_(int minValue_, int maxValue_, int value_1);

bool isEmpty_(struct String str_);

struct CharOption tryItem_(int index_, struct String str_1);

bool occursAtLoop_(int start_, struct String substr_, struct String s_, int i_);

bool occursAt_(int start_, struct String substr_, struct String s_);

bool startsWith_(struct String prefix_, struct String s_1);

bool endsWith_(struct String suffix_, struct String s_2);

struct IntOption stringFindIndexLoop_(struct String substr_1, struct String s_3, int r_, int i_1);

struct IntOption findIndex_(struct String substr_1, struct String s_3);

struct IntOption stringFindLastIndexLoop_(struct String substr_2, struct String s_4, int r_1);

struct IntOption findLastIndex_(struct String substr_2, struct String s_4);

bool contains_(struct String substr_3, struct String s_5);

struct String truncate_(int prefixLen_, struct String s_6);

struct String skip_(int prefixLen_1, struct String s_7);

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

struct StringList const* replaceLoop_(struct String pattern_, struct String s_15, struct StringList const* acc_, int i_2);

struct String replace_(struct String pattern_, struct String target_, struct String s_15);

int findNewline_(int start_3, struct String s_16);

struct StringOption;

struct StringStringOptionStringTuple3;

struct StringStringOptionStringTuple3 scanLine_(struct String s_17);

struct StringList const* stringToLinesLoop_(struct String s_18, int l_4, struct StringList const* acc_1);

struct StringList const* toLines_(struct String s_18);

struct String concat_(struct String sep_1, struct StringList const* xs_);

char unwrap_2(struct CharOption opt_);

int unwrap_1(struct IntOption opt_);

int isEmptyTest_(int arg_42);

int tryItemTest_(int arg_43);

int startsWithTest_(int arg_44);

int endsWithTest_(int arg_45);

int findIndexTest_(int arg_46);

int findLastIndexTest_(int arg_47);

int containsTest_(int arg_48);

int truncateTest_(int arg_49);

int skipTest_(int arg_50);

int sliceTest_(int arg_51);

int trimTest_(int arg_52);

int replaceTest_(int arg_53);

int splitTest_(int arg_54);

int concatTest_(int arg_55);

int milone_main();


struct String __stringJoin_(struct String sep_2, struct StringList const* xs_54) {
    struct String str_concat_result_ = str_concat(sep_2, xs_54);
    return str_concat_result_;
}

int const* __ptrAsConst_1(int* mutPtr_) {
    return ((int const*)mutPtr_);
}

void* memAlloc_(int len_3, uintptr_t size_) {
    void* milone_mem_alloc_result_ = milone_mem_alloc(len_3, size_);
    return milone_mem_alloc_result_;
}

void* memcpy_(void* dest_, void const* src_, uintptr_t size_1) {
    void* memcpy_result_ = memcpy(dest_, src_, size_1);
    return memcpy_result_;
}

struct IntOption {
    bool some;
    int value;
};

struct IntOption __intOfStr_(struct String s_19) {
    void* call_ = memAlloc_(1, ((uintptr_t)sizeof(int)));
    int* valueRef_ = ((int*)call_);
    bool str_to_int_checked_result_ = str_to_int_checked(s_19, valueRef_);
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
    struct IntOption some_ = (struct IntOption){.some = true, .value = read_};
    if_ = some_;
    goto if_next_1;
else_3:;
    if_ = ((struct IntOption){});
    goto if_next_1;
if_next_1:;
    return if_;
}

int __argCount_(int arg_3) {
    int milone_get_arg_count_result_ = milone_get_arg_count();
    return milone_get_arg_count_result_;
}

struct String __argGet_(int index_5) {
    struct String milone_get_arg_result_ = milone_get_arg(index_5);
    return milone_get_arg_result_;
}

struct CharOption {
    bool some;
    char value;
};

bool isNone_2(struct CharOption opt_1) {
    bool match_;
    if (opt_1.some) goto next_5;
    match_ = true;
    goto end_match_4;
next_5:;
    if ((!(opt_1.some))) goto next_6;
    match_ = false;
    goto end_match_4;
next_6:;
    exit(1);
end_match_4:;
    return match_;
}

bool isNone_1(struct IntOption opt_1) {
    bool match_1;
    if (opt_1.some) goto next_8;
    match_1 = true;
    goto end_match_7;
next_8:;
    if ((!(opt_1.some))) goto next_9;
    match_1 = false;
    goto end_match_7;
next_9:;
    exit(1);
end_match_7:;
    return match_1;
}

struct StringList {
    struct String head;
    struct StringList const* tail;
};

struct StringList const* listRevLoop_1(struct StringList const* acc_3, struct StringList const* xs_6) {
tailrec_10:;
    struct StringList const* match_2;
    if ((!((!(xs_6))))) goto next_12;
    match_2 = acc_3;
    goto end_match_11;
next_12:;
    if ((!(xs_6))) goto next_13;
    struct String x_6 = xs_6->head;
    struct StringList const* xs_7 = xs_6->tail;
    struct StringList const* list_ = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_))) = (struct StringList){.head = x_6, .tail = acc_3};
    struct StringList const* arg_4 = list_;
    struct StringList const* arg_5 = xs_7;
    acc_3 = arg_4;
    xs_6 = arg_5;
    goto tailrec_10;
    match_2 = NULL;
    goto end_match_11;
next_13:;
    exit(1);
end_match_11:;
    return match_2;
}

struct StringList const* rev_1(struct StringList const* xs_5) {
    struct StringList const* call_2 = listRevLoop_1(NULL, xs_5);
    return call_2;
}

char subtract_(char l_5, char r_9) {
    return ((char)(((int)l_5) - ((int)r_9)));
}

bool isAscii_(char c_) {
    bool if_1;
    if ((c_ >= '\0')) {
        goto then_15;
    } else {
        goto else_16;
    }
then_15:;
    if_1 = (((char)127) >= c_);
    goto if_next_14;
else_16:;
    if_1 = false;
    goto if_next_14;
if_next_14:;
    return if_1;
}

bool isControl_(char c_1) {
    int n_1 = ((int)c_1);
    bool if_2;
    if ((n_1 >= 0)) {
        goto then_18;
    } else {
        goto else_19;
    }
then_18:;
    if_2 = (31 >= n_1);
    goto if_next_17;
else_19:;
    if_2 = false;
    goto if_next_17;
if_next_17:;
    bool if_3;
    if (if_2) {
        goto then_21;
    } else {
        goto else_22;
    }
then_21:;
    if_3 = true;
    goto if_next_20;
else_22:;
    if_3 = (n_1 == 127);
    goto if_next_20;
if_next_20:;
    return if_3;
}

bool isBlank_(char c_2) {
    bool if_4;
    if ((c_2 == ' ')) {
        goto then_24;
    } else {
        goto else_25;
    }
then_24:;
    if_4 = true;
    goto if_next_23;
else_25:;
    if_4 = (c_2 == '\t');
    goto if_next_23;
if_next_23:;
    return if_4;
}

bool isSpace_(char c_3) {
    bool if_5;
    if ((c_3 >= '\t')) {
        goto then_27;
    } else {
        goto else_28;
    }
then_27:;
    if_5 = ('\r' >= c_3);
    goto if_next_26;
else_28:;
    if_5 = false;
    goto if_next_26;
if_next_26:;
    bool if_6;
    if (if_5) {
        goto then_30;
    } else {
        goto else_31;
    }
then_30:;
    if_6 = true;
    goto if_next_29;
else_31:;
    if_6 = (c_3 == ' ');
    goto if_next_29;
if_next_29:;
    return if_6;
}

bool isPunctuation_(char c_4) {
    int n_2 = ((int)c_4);
    bool if_7;
    if ((n_2 >= 33)) {
        goto then_33;
    } else {
        goto else_34;
    }
then_33:;
    if_7 = (47 >= n_2);
    goto if_next_32;
else_34:;
    if_7 = false;
    goto if_next_32;
if_next_32:;
    bool if_8;
    if (if_7) {
        goto then_36;
    } else {
        goto else_37;
    }
then_36:;
    if_8 = true;
    goto if_next_35;
else_37:;
    bool if_9;
    if ((n_2 >= 58)) {
        goto then_39;
    } else {
        goto else_40;
    }
then_39:;
    if_9 = (64 >= n_2);
    goto if_next_38;
else_40:;
    if_9 = false;
    goto if_next_38;
if_next_38:;
    if_8 = if_9;
    goto if_next_35;
if_next_35:;
    bool if_10;
    if (if_8) {
        goto then_42;
    } else {
        goto else_43;
    }
then_42:;
    if_10 = true;
    goto if_next_41;
else_43:;
    bool if_11;
    if ((n_2 >= 91)) {
        goto then_45;
    } else {
        goto else_46;
    }
then_45:;
    if_11 = (96 >= n_2);
    goto if_next_44;
else_46:;
    if_11 = false;
    goto if_next_44;
if_next_44:;
    if_10 = if_11;
    goto if_next_41;
if_next_41:;
    bool if_12;
    if (if_10) {
        goto then_48;
    } else {
        goto else_49;
    }
then_48:;
    if_12 = true;
    goto if_next_47;
else_49:;
    bool if_13;
    if ((n_2 >= 123)) {
        goto then_51;
    } else {
        goto else_52;
    }
then_51:;
    if_13 = (126 >= n_2);
    goto if_next_50;
else_52:;
    if_13 = false;
    goto if_next_50;
if_next_50:;
    if_12 = if_13;
    goto if_next_47;
if_next_47:;
    return if_12;
}

bool isDigit_(char c_5) {
    bool if_14;
    if ((c_5 >= '0')) {
        goto then_54;
    } else {
        goto else_55;
    }
then_54:;
    if_14 = ('9' >= c_5);
    goto if_next_53;
else_55:;
    if_14 = false;
    goto if_next_53;
if_next_53:;
    return if_14;
}

bool isHex_(char c_6) {
    bool call_3 = isDigit_(c_6);
    bool if_15;
    if (call_3) {
        goto then_57;
    } else {
        goto else_58;
    }
then_57:;
    if_15 = true;
    goto if_next_56;
else_58:;
    bool if_16;
    if ((c_6 >= 'A')) {
        goto then_60;
    } else {
        goto else_61;
    }
then_60:;
    if_16 = ('F' >= c_6);
    goto if_next_59;
else_61:;
    if_16 = false;
    goto if_next_59;
if_next_59:;
    if_15 = if_16;
    goto if_next_56;
if_next_56:;
    bool if_17;
    if (if_15) {
        goto then_63;
    } else {
        goto else_64;
    }
then_63:;
    if_17 = true;
    goto if_next_62;
else_64:;
    bool if_18;
    if ((c_6 >= 'a')) {
        goto then_66;
    } else {
        goto else_67;
    }
then_66:;
    if_18 = ('f' >= c_6);
    goto if_next_65;
else_67:;
    if_18 = false;
    goto if_next_65;
if_next_65:;
    if_17 = if_18;
    goto if_next_62;
if_next_62:;
    return if_17;
}

bool isUpper_(char c_7) {
    bool if_19;
    if ((c_7 >= 'A')) {
        goto then_69;
    } else {
        goto else_70;
    }
then_69:;
    if_19 = ('Z' >= c_7);
    goto if_next_68;
else_70:;
    if_19 = false;
    goto if_next_68;
if_next_68:;
    return if_19;
}

bool isLower_(char c_8) {
    bool if_20;
    if ((c_8 >= 'a')) {
        goto then_72;
    } else {
        goto else_73;
    }
then_72:;
    if_20 = ('z' >= c_8);
    goto if_next_71;
else_73:;
    if_20 = false;
    goto if_next_71;
if_next_71:;
    return if_20;
}

bool isAlphabetic_(char c_9) {
    bool call_4 = isUpper_(c_9);
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
    bool call_5 = isLower_(c_9);
    if_21 = call_5;
    goto if_next_74;
if_next_74:;
    return if_21;
}

bool isAlphanumeric_(char c_10) {
    bool call_6 = isDigit_(c_10);
    bool if_22;
    if (call_6) {
        goto then_78;
    } else {
        goto else_79;
    }
then_78:;
    if_22 = true;
    goto if_next_77;
else_79:;
    bool call_7 = isAlphabetic_(c_10);
    if_22 = call_7;
    goto if_next_77;
if_next_77:;
    return if_22;
}

char toUpper_(char c_11) {
    bool call_8 = isLower_(c_11);
    char if_23;
    if (call_8) {
        goto then_81;
    } else {
        goto else_82;
    }
then_81:;
    char call_9 = subtract_(c_11, 'a');
    if_23 = (call_9 + 'A');
    goto if_next_80;
else_82:;
    if_23 = c_11;
    goto if_next_80;
if_next_80:;
    return if_23;
}

char toLower_(char c_12) {
    bool call_10 = isUpper_(c_12);
    char if_24;
    if (call_10) {
        goto then_84;
    } else {
        goto else_85;
    }
then_84:;
    char call_11 = subtract_(c_12, 'A');
    if_24 = (call_11 + 'a');
    goto if_next_83;
else_85:;
    if_24 = c_12;
    goto if_next_83;
if_next_83:;
    return if_24;
}

int intClamp_(int minValue_, int maxValue_, int value_1) {
    int if_25;
    if ((value_1 < minValue_)) {
        goto then_87;
    } else {
        goto else_88;
    }
then_87:;
    if_25 = minValue_;
    goto if_next_86;
else_88:;
    int if_26;
    if ((maxValue_ < value_1)) {
        goto then_90;
    } else {
        goto else_91;
    }
then_90:;
    if_26 = maxValue_;
    goto if_next_89;
else_91:;
    if_26 = value_1;
    goto if_next_89;
if_next_89:;
    if_25 = if_26;
    goto if_next_86;
if_next_86:;
    return if_25;
}

bool isEmpty_(struct String str_) {
    return (str_.len == 0);
}

struct CharOption tryItem_(int index_, struct String str_1) {
    bool if_27;
    if ((index_ >= 0)) {
        goto then_93;
    } else {
        goto else_94;
    }
then_93:;
    if_27 = (index_ < str_1.len);
    goto if_next_92;
else_94:;
    if_27 = false;
    goto if_next_92;
if_next_92:;
    struct CharOption if_28;
    if (if_27) {
        goto then_96;
    } else {
        goto else_97;
    }
then_96:;
    struct CharOption some_1 = (struct CharOption){.some = true, .value = str_1.str[index_]};
    if_28 = some_1;
    goto if_next_95;
else_97:;
    if_28 = ((struct CharOption){});
    goto if_next_95;
if_next_95:;
    return if_28;
}

bool occursAtLoop_(int start_, struct String substr_, struct String s_, int i_) {
tailrec_98:;
    bool if_29;
    if ((i_ == substr_.len)) {
        goto then_100;
    } else {
        goto else_101;
    }
then_100:;
    if_29 = true;
    goto if_next_99;
else_101:;
    bool if_30;
    if ((s_.str[(start_ + i_)] == substr_.str[i_])) {
        goto then_103;
    } else {
        goto else_104;
    }
then_103:;
    int arg_6 = start_;
    struct String arg_7 = substr_;
    struct String arg_8 = s_;
    int arg_9 = (i_ + 1);
    start_ = arg_6;
    substr_ = arg_7;
    s_ = arg_8;
    i_ = arg_9;
    goto tailrec_98;
    if_30 = false;
    goto if_next_102;
else_104:;
    if_30 = false;
    goto if_next_102;
if_next_102:;
    if_29 = if_30;
    goto if_next_99;
if_next_99:;
    return if_29;
}

bool occursAt_(int start_, struct String substr_, struct String s_) {
    bool if_31;
    if ((start_ >= 0)) {
        goto then_106;
    } else {
        goto else_107;
    }
then_106:;
    if_31 = (s_.len >= (start_ + substr_.len));
    goto if_next_105;
else_107:;
    if_31 = false;
    goto if_next_105;
if_next_105:;
    bool if_32;
    if (if_31) {
        goto then_109;
    } else {
        goto else_110;
    }
then_109:;
    bool call_12 = occursAtLoop_(start_, substr_, s_, 0);
    if_32 = call_12;
    goto if_next_108;
else_110:;
    if_32 = false;
    goto if_next_108;
if_next_108:;
    return if_32;
}

bool startsWith_(struct String prefix_, struct String s_1) {
    bool call_13 = occursAt_(0, prefix_, s_1);
    return call_13;
}

bool endsWith_(struct String suffix_, struct String s_2) {
    bool call_14 = occursAt_((s_2.len - suffix_.len), suffix_, s_2);
    return call_14;
}

struct IntOption stringFindIndexLoop_(struct String substr_1, struct String s_3, int r_, int i_1) {
tailrec_111:;
    struct IntOption if_33;
    if ((i_1 >= r_)) {
        goto then_113;
    } else {
        goto else_114;
    }
then_113:;
    if_33 = ((struct IntOption){});
    goto if_next_112;
else_114:;
    bool call_15 = occursAt_(i_1, substr_1, s_3);
    struct IntOption if_34;
    if (call_15) {
        goto then_116;
    } else {
        goto else_117;
    }
then_116:;
    struct IntOption some_2 = (struct IntOption){.some = true, .value = i_1};
    if_34 = some_2;
    goto if_next_115;
else_117:;
    struct String arg_10 = substr_1;
    struct String arg_11 = s_3;
    int arg_12 = r_;
    int arg_13 = (i_1 + 1);
    substr_1 = arg_10;
    s_3 = arg_11;
    r_ = arg_12;
    i_1 = arg_13;
    goto tailrec_111;
    if_34 = ((struct IntOption){});
    goto if_next_115;
if_next_115:;
    if_33 = if_34;
    goto if_next_112;
if_next_112:;
    return if_33;
}

struct IntOption findIndex_(struct String substr_1, struct String s_3) {
    int r_ = ((s_3.len - substr_1.len) + 1);
    struct IntOption call_16 = stringFindIndexLoop_(substr_1, s_3, r_, 0);
    return call_16;
}

struct IntOption stringFindLastIndexLoop_(struct String substr_2, struct String s_4, int r_1) {
tailrec_118:;
    struct IntOption if_35;
    if ((0 >= r_1)) {
        goto then_120;
    } else {
        goto else_121;
    }
then_120:;
    if_35 = ((struct IntOption){});
    goto if_next_119;
else_121:;
    bool call_17 = occursAt_((r_1 - 1), substr_2, s_4);
    struct IntOption if_36;
    if (call_17) {
        goto then_123;
    } else {
        goto else_124;
    }
then_123:;
    struct IntOption some_3 = (struct IntOption){.some = true, .value = (r_1 - 1)};
    if_36 = some_3;
    goto if_next_122;
else_124:;
    struct String arg_14 = substr_2;
    struct String arg_15 = s_4;
    int arg_16 = (r_1 - 1);
    substr_2 = arg_14;
    s_4 = arg_15;
    r_1 = arg_16;
    goto tailrec_118;
    if_36 = ((struct IntOption){});
    goto if_next_122;
if_next_122:;
    if_35 = if_36;
    goto if_next_119;
if_next_119:;
    return if_35;
}

struct IntOption findLastIndex_(struct String substr_2, struct String s_4) {
    int r_2 = ((s_4.len - substr_2.len) + 1);
    struct IntOption call_18 = stringFindLastIndexLoop_(substr_2, s_4, r_2);
    return call_18;
}

bool contains_(struct String substr_3, struct String s_5) {
    bool match_3;
    struct IntOption call_19 = findIndex_(substr_3, s_5);
    if ((!(call_19.some))) goto next_126;
    match_3 = true;
    goto end_match_125;
next_126:;
    if (call_19.some) goto next_127;
    match_3 = false;
    goto end_match_125;
next_127:;
    exit(1);
end_match_125:;
    return match_3;
}

struct String truncate_(int prefixLen_, struct String s_6) {
    struct String if_37;
    if ((0 >= prefixLen_)) {
        goto then_129;
    } else {
        goto else_130;
    }
then_129:;
    if_37 = (struct String){.str = "", .len = 0};
    goto if_next_128;
else_130:;
    struct String if_38;
    if ((prefixLen_ >= s_6.len)) {
        goto then_132;
    } else {
        goto else_133;
    }
then_132:;
    if_38 = s_6;
    goto if_next_131;
else_133:;
    struct String slice_1 = str_get_slice(0, (prefixLen_ - 1), s_6);
    if_38 = slice_1;
    goto if_next_131;
if_next_131:;
    if_37 = if_38;
    goto if_next_128;
if_next_128:;
    return if_37;
}

struct String skip_(int prefixLen_1, struct String s_7) {
    struct String if_39;
    if ((0 >= prefixLen_1)) {
        goto then_135;
    } else {
        goto else_136;
    }
then_135:;
    if_39 = s_7;
    goto if_next_134;
else_136:;
    struct String if_40;
    if ((prefixLen_1 >= s_7.len)) {
        goto then_138;
    } else {
        goto else_139;
    }
then_138:;
    if_40 = (struct String){.str = "", .len = 0};
    goto if_next_137;
else_139:;
    struct String slice_2 = str_get_slice(prefixLen_1, (s_7.len - 1), s_7);
    if_40 = slice_2;
    goto if_next_137;
if_next_137:;
    if_39 = if_40;
    goto if_next_134;
if_next_134:;
    return if_39;
}

struct String slice_(int start_1, int endIndex_, struct String s_8) {
    int call_20 = intClamp_(0, s_8.len, start_1);
    int start_2 = call_20;
    int call_21 = intClamp_(start_2, s_8.len, endIndex_);
    int endIndex_1 = call_21;
    struct String if_41;
    if ((start_2 < endIndex_1)) {
        goto then_141;
    } else {
        goto else_142;
    }
then_141:;
    struct String slice_3 = str_get_slice(start_2, (endIndex_1 - 1), s_8);
    if_41 = slice_3;
    goto if_next_140;
else_142:;
    if_41 = (struct String){.str = "", .len = 0};
    goto if_next_140;
if_next_140:;
    return if_41;
}

struct CharBoolFun1 {
    bool(*fun)(void const*, char);
    void const* env;
};

int stringTrimIfLoop1_(struct CharBoolFun1 isTrimmed_, struct String s_9, int l_1) {
tailrec_143:;
    bool if_42;
    if ((l_1 < s_9.len)) {
        goto then_145;
    } else {
        goto else_146;
    }
then_145:;
    bool app_ = isTrimmed_.fun(isTrimmed_.env, s_9.str[l_1]);
    if_42 = app_;
    goto if_next_144;
else_146:;
    if_42 = false;
    goto if_next_144;
if_next_144:;
    int if_43;
    if (if_42) {
        goto then_148;
    } else {
        goto else_149;
    }
then_148:;
    struct CharBoolFun1 arg_17 = isTrimmed_;
    struct String arg_18 = s_9;
    int arg_19 = (l_1 + 1);
    isTrimmed_ = arg_17;
    s_9 = arg_18;
    l_1 = arg_19;
    goto tailrec_143;
    if_43 = 0;
    goto if_next_147;
else_149:;
    if_43 = l_1;
    goto if_next_147;
if_next_147:;
    return if_43;
}

int stringTrimIfLoop2_(struct CharBoolFun1 isTrimmed_, struct String s_9, int l_, int r_4) {
tailrec_150:;
    bool if_44;
    if ((l_ < r_4)) {
        goto then_152;
    } else {
        goto else_153;
    }
then_152:;
    bool app_1 = isTrimmed_.fun(isTrimmed_.env, s_9.str[(r_4 - 1)]);
    if_44 = app_1;
    goto if_next_151;
else_153:;
    if_44 = false;
    goto if_next_151;
if_next_151:;
    int if_45;
    if (if_44) {
        goto then_155;
    } else {
        goto else_156;
    }
then_155:;
    struct CharBoolFun1 arg_20 = isTrimmed_;
    struct String arg_21 = s_9;
    int arg_22 = l_;
    int arg_23 = (r_4 - 1);
    isTrimmed_ = arg_20;
    s_9 = arg_21;
    l_ = arg_22;
    r_4 = arg_23;
    goto tailrec_150;
    if_45 = 0;
    goto if_next_154;
else_156:;
    if_45 = r_4;
    goto if_next_154;
if_next_154:;
    return if_45;
}

struct String trimIf_(struct CharBoolFun1 isTrimmed_, struct String s_9) {
    int call_22 = stringTrimIfLoop1_(isTrimmed_, s_9, 0);
    int l_ = call_22;
    int call_23 = stringTrimIfLoop2_(isTrimmed_, s_9, l_, s_9.len);
    int r_3 = call_23;
    struct String if_46;
    if ((l_ < r_3)) {
        goto then_158;
    } else {
        goto else_159;
    }
then_158:;
    struct String slice_4 = str_get_slice(l_, (r_3 - 1), s_9);
    if_46 = slice_4;
    goto if_next_157;
else_159:;
    if_46 = (struct String){.str = "", .len = 0};
    goto if_next_157;
if_next_157:;
    return if_46;
}

int stringTrimStartIfLoop_(struct CharBoolFun1 isTrimmed_1, struct String s_10, int l_3) {
tailrec_160:;
    bool if_47;
    if ((l_3 < s_10.len)) {
        goto then_162;
    } else {
        goto else_163;
    }
then_162:;
    bool app_2 = isTrimmed_1.fun(isTrimmed_1.env, s_10.str[l_3]);
    if_47 = app_2;
    goto if_next_161;
else_163:;
    if_47 = false;
    goto if_next_161;
if_next_161:;
    int if_48;
    if (if_47) {
        goto then_165;
    } else {
        goto else_166;
    }
then_165:;
    struct CharBoolFun1 arg_24 = isTrimmed_1;
    struct String arg_25 = s_10;
    int arg_26 = (l_3 + 1);
    isTrimmed_1 = arg_24;
    s_10 = arg_25;
    l_3 = arg_26;
    goto tailrec_160;
    if_48 = 0;
    goto if_next_164;
else_166:;
    if_48 = l_3;
    goto if_next_164;
if_next_164:;
    return if_48;
}

struct String trimStartIf_(struct CharBoolFun1 isTrimmed_1, struct String s_10) {
    int call_24 = stringTrimStartIfLoop_(isTrimmed_1, s_10, 0);
    int l_2 = call_24;
    struct String if_49;
    if ((l_2 < s_10.len)) {
        goto then_168;
    } else {
        goto else_169;
    }
then_168:;
    struct String slice_5 = str_get_slice(l_2, (s_10.len - 1), s_10);
    if_49 = slice_5;
    goto if_next_167;
else_169:;
    if_49 = (struct String){.str = "", .len = 0};
    goto if_next_167;
if_next_167:;
    return if_49;
}

int stringTrimEndIfLoop_(struct CharBoolFun1 isTrimmed_2, struct String s_11, int r_6) {
tailrec_170:;
    bool if_50;
    if ((0 < r_6)) {
        goto then_172;
    } else {
        goto else_173;
    }
then_172:;
    bool app_3 = isTrimmed_2.fun(isTrimmed_2.env, s_11.str[(r_6 - 1)]);
    if_50 = app_3;
    goto if_next_171;
else_173:;
    if_50 = false;
    goto if_next_171;
if_next_171:;
    int if_51;
    if (if_50) {
        goto then_175;
    } else {
        goto else_176;
    }
then_175:;
    struct CharBoolFun1 arg_27 = isTrimmed_2;
    struct String arg_28 = s_11;
    int arg_29 = (r_6 - 1);
    isTrimmed_2 = arg_27;
    s_11 = arg_28;
    r_6 = arg_29;
    goto tailrec_170;
    if_51 = 0;
    goto if_next_174;
else_176:;
    if_51 = r_6;
    goto if_next_174;
if_next_174:;
    return if_51;
}

struct String trimEndIf_(struct CharBoolFun1 isTrimmed_2, struct String s_11) {
    int call_25 = stringTrimEndIfLoop_(isTrimmed_2, s_11, s_11.len);
    int r_5 = call_25;
    struct String if_52;
    if ((0 < r_5)) {
        goto then_178;
    } else {
        goto else_179;
    }
then_178:;
    struct String slice_6 = str_get_slice(0, (r_5 - 1), s_11);
    if_52 = slice_6;
    goto if_next_177;
else_179:;
    if_52 = (struct String){.str = "", .len = 0};
    goto if_next_177;
if_next_177:;
    return if_52;
}

bool fun_(void const* env_, char arg_) {
    bool call_26 = isSpace_(arg_);
    return call_26;
}

struct String trim_(struct String s_12) {
    void const* box_ = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_))) = 0;
    struct CharBoolFun1 fun_3 = (struct CharBoolFun1){.fun = fun_, .env = box_};
    struct String call_27 = trimIf_(fun_3, s_12);
    return call_27;
}

bool fun_1(void const* env_1, char arg_1) {
    bool call_28 = isSpace_(arg_1);
    return call_28;
}

struct String trimStart_(struct String s_13) {
    void const* box_1 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_1))) = 0;
    struct CharBoolFun1 fun_4 = (struct CharBoolFun1){.fun = fun_1, .env = box_1};
    struct String call_29 = trimStartIf_(fun_4, s_13);
    return call_29;
}

bool fun_2(void const* env_2, char arg_2) {
    bool call_30 = isSpace_(arg_2);
    return call_30;
}

struct String trimEnd_(struct String s_14) {
    void const* box_2 = milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_2))) = 0;
    struct CharBoolFun1 fun_5 = (struct CharBoolFun1){.fun = fun_2, .env = box_2};
    struct String call_31 = trimEndIf_(fun_5, s_14);
    return call_31;
}

struct StringList const* replaceLoop_(struct String pattern_, struct String s_15, struct StringList const* acc_, int i_2) {
tailrec_180:;
    struct StringList const* match_4;
    struct String call_32 = skip_(i_2, s_15);
    struct IntOption call_33 = findIndex_(pattern_, call_32);
    if (call_33.some) goto next_182;
    struct String call_34 = skip_(i_2, s_15);
    struct StringList const* list_1 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_1))) = (struct StringList){.head = call_34, .tail = acc_};
    match_4 = list_1;
    goto end_match_181;
next_182:;
    if ((!(call_33.some))) goto next_183;
    int n_ = call_33.value;
    struct String arg_30 = pattern_;
    struct String arg_31 = s_15;
    struct String call_35 = skip_(i_2, s_15);
    struct String call_36 = truncate_(n_, call_35);
    struct StringList const* list_2 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_2))) = (struct StringList){.head = call_36, .tail = acc_};
    struct StringList const* arg_32 = list_2;
    int arg_33 = ((i_2 + n_) + pattern_.len);
    pattern_ = arg_30;
    s_15 = arg_31;
    acc_ = arg_32;
    i_2 = arg_33;
    goto tailrec_180;
    match_4 = NULL;
    goto end_match_181;
next_183:;
    exit(1);
end_match_181:;
    return match_4;
}

struct String replace_(struct String pattern_, struct String target_, struct String s_15) {
    struct String if_53;
    if ((pattern_.len == 0)) {
        goto then_185;
    } else {
        goto else_186;
    }
then_185:;
    if_53 = s_15;
    goto if_next_184;
else_186:;
    struct StringList const* call_37 = replaceLoop_(pattern_, s_15, NULL, 0);
    struct StringList const* call_38 = rev_1(call_37);
    struct String call_39 = concat_(target_, call_38);
    if_53 = call_39;
    goto if_next_184;
if_next_184:;
    return if_53;
}

int findNewline_(int start_3, struct String s_16) {
tailrec_187:;
    int i_3 = start_3;
    bool if_54;
    if ((i_3 < s_16.len)) {
        goto then_189;
    } else {
        goto else_196;
    }
then_189:;
    bool if_55;
    if ((s_16.str[i_3] != '\0')) {
        goto then_191;
    } else {
        goto else_192;
    }
then_191:;
    if_55 = (s_16.str[i_3] != '\r');
    goto if_next_190;
else_192:;
    if_55 = false;
    goto if_next_190;
if_next_190:;
    bool if_56;
    if (if_55) {
        goto then_194;
    } else {
        goto else_195;
    }
then_194:;
    if_56 = (s_16.str[i_3] != '\n');
    goto if_next_193;
else_195:;
    if_56 = false;
    goto if_next_193;
if_next_193:;
    if_54 = if_56;
    goto if_next_188;
else_196:;
    if_54 = false;
    goto if_next_188;
if_next_188:;
    int if_57;
    if (if_54) {
        goto then_198;
    } else {
        goto else_199;
    }
then_198:;
    int arg_34 = (i_3 + 1);
    struct String arg_35 = s_16;
    start_3 = arg_34;
    s_16 = arg_35;
    goto tailrec_187;
    if_57 = 0;
    goto if_next_197;
else_199:;
    if_57 = i_3;
    goto if_next_197;
if_next_197:;
    return if_57;
}

struct StringOption {
    bool some;
    struct String value;
};

struct StringStringOptionStringTuple3 {
    struct String t0;
    struct StringOption t1;
    struct String t2;
};

struct StringStringOptionStringTuple3 scanLine_(struct String s_17) {
    int call_40 = findNewline_(0, s_17);
    int m_ = call_40;
    struct String if_58;
    if ((0 < m_)) {
        goto then_201;
    } else {
        goto else_202;
    }
then_201:;
    struct String slice_7 = str_get_slice(0, (m_ - 1), s_17);
    if_58 = slice_7;
    goto if_next_200;
else_202:;
    if_58 = (struct String){.str = "", .len = 0};
    goto if_next_200;
if_next_200:;
    struct String lineContents_ = if_58;
    struct StringStringOptionStringTuple3 if_59;
    if ((m_ == s_17.len)) {
        goto then_204;
    } else {
        goto else_205;
    }
then_204:;
    struct StringStringOptionStringTuple3 tuple_ = (struct StringStringOptionStringTuple3){.t0 = lineContents_, .t1 = ((struct StringOption){}), .t2 = (struct String){.str = "", .len = 0}};
    if_59 = tuple_;
    goto if_next_203;
else_205:;
    bool if_60;
    if (((m_ + 1) < s_17.len)) {
        goto then_207;
    } else {
        goto else_208;
    }
then_207:;
    if_60 = (s_17.str[m_] == '\r');
    goto if_next_206;
else_208:;
    if_60 = false;
    goto if_next_206;
if_next_206:;
    bool if_61;
    if (if_60) {
        goto then_210;
    } else {
        goto else_211;
    }
then_210:;
    if_61 = (s_17.str[(m_ + 1)] == '\n');
    goto if_next_209;
else_211:;
    if_61 = false;
    goto if_next_209;
if_next_209:;
    int if_62;
    if (if_61) {
        goto then_213;
    } else {
        goto else_214;
    }
then_213:;
    if_62 = 2;
    goto if_next_212;
else_214:;
    bool if_63;
    if ((s_17.str[m_] == '\0')) {
        goto then_216;
    } else {
        goto else_217;
    }
then_216:;
    if_63 = true;
    goto if_next_215;
else_217:;
    if_63 = (s_17.str[m_] == '\r');
    goto if_next_215;
if_next_215:;
    bool if_64;
    if (if_63) {
        goto then_219;
    } else {
        goto else_220;
    }
then_219:;
    if_64 = true;
    goto if_next_218;
else_220:;
    if_64 = (s_17.str[m_] == '\n');
    goto if_next_218;
if_next_218:;
    milone_assert(if_64, 255, 8);
    if_62 = 1;
    goto if_next_212;
if_next_212:;
    int sepLen_ = if_62;
    int r_7 = (m_ + sepLen_);
    struct String slice_8 = str_get_slice(m_, (r_7 - 1), s_17);
    struct String sep_ = slice_8;
    struct String if_65;
    if ((r_7 < s_17.len)) {
        goto then_222;
    } else {
        goto else_223;
    }
then_222:;
    struct String slice_9 = str_get_slice(r_7, (s_17.len - 1), s_17);
    if_65 = slice_9;
    goto if_next_221;
else_223:;
    if_65 = (struct String){.str = "", .len = 0};
    goto if_next_221;
if_next_221:;
    struct String rest_ = if_65;
    struct StringOption some_4 = (struct StringOption){.some = true, .value = sep_};
    struct StringStringOptionStringTuple3 tuple_1 = (struct StringStringOptionStringTuple3){.t0 = lineContents_, .t1 = some_4, .t2 = rest_};
    if_59 = tuple_1;
    goto if_next_203;
if_next_203:;
    return if_59;
}

struct StringList const* stringToLinesLoop_(struct String s_18, int l_4, struct StringList const* acc_1) {
tailrec_224:;
    int call_41 = findNewline_(l_4, s_18);
    int r_8 = call_41;
    struct String if_66;
    if ((l_4 < r_8)) {
        goto then_226;
    } else {
        goto else_227;
    }
then_226:;
    struct String slice_10 = str_get_slice(l_4, (r_8 - 1), s_18);
    if_66 = slice_10;
    goto if_next_225;
else_227:;
    if_66 = (struct String){.str = "", .len = 0};
    goto if_next_225;
if_next_225:;
    struct StringList const* list_3 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_3))) = (struct StringList){.head = if_66, .tail = acc_1};
    struct StringList const* acc_2 = list_3;
    struct StringList const* if_67;
    if ((r_8 == s_18.len)) {
        goto then_229;
    } else {
        goto else_230;
    }
then_229:;
    if_67 = acc_2;
    goto if_next_228;
else_230:;
    bool if_68;
    if (((r_8 + 1) < s_18.len)) {
        goto then_232;
    } else {
        goto else_233;
    }
then_232:;
    if_68 = (s_18.str[r_8] == '\r');
    goto if_next_231;
else_233:;
    if_68 = false;
    goto if_next_231;
if_next_231:;
    bool if_69;
    if (if_68) {
        goto then_235;
    } else {
        goto else_236;
    }
then_235:;
    if_69 = (s_18.str[(r_8 + 1)] == '\n');
    goto if_next_234;
else_236:;
    if_69 = false;
    goto if_next_234;
if_next_234:;
    struct StringList const* if_70;
    if (if_69) {
        goto then_238;
    } else {
        goto else_239;
    }
then_238:;
    struct String arg_36 = s_18;
    int arg_37 = (r_8 + 2);
    struct StringList const* arg_38 = acc_2;
    s_18 = arg_36;
    l_4 = arg_37;
    acc_1 = arg_38;
    goto tailrec_224;
    if_70 = NULL;
    goto if_next_237;
else_239:;
    bool if_71;
    if ((s_18.str[r_8] == '\r')) {
        goto then_241;
    } else {
        goto else_242;
    }
then_241:;
    if_71 = true;
    goto if_next_240;
else_242:;
    if_71 = (s_18.str[r_8] == '\n');
    goto if_next_240;
if_next_240:;
    milone_assert(if_71, 285, 6);
    struct String arg_39 = s_18;
    int arg_40 = (r_8 + 1);
    struct StringList const* arg_41 = acc_2;
    s_18 = arg_39;
    l_4 = arg_40;
    acc_1 = arg_41;
    goto tailrec_224;
    if_70 = NULL;
    goto if_next_237;
if_next_237:;
    if_67 = if_70;
    goto if_next_228;
if_next_228:;
    return if_67;
}

struct StringList const* toLines_(struct String s_18) {
    struct StringList const* call_42 = stringToLinesLoop_(s_18, 0, NULL);
    struct StringList const* call_43 = rev_1(call_42);
    return call_43;
}

struct String concat_(struct String sep_1, struct StringList const* xs_) {
    struct String call_44 = __stringJoin_(sep_1, xs_);
    return call_44;
}

char unwrap_2(struct CharOption opt_) {
    char match_5;
    if ((!(opt_.some))) goto next_244;
    char value_ = opt_.value;
    match_5 = value_;
    goto end_match_243;
next_244:;
    if (opt_.some) goto next_245;
    printf("Can\'t unwrap None.\n");
    exit(1);
    match_5 = 0;
    goto end_match_243;
next_245:;
    exit(1);
end_match_243:;
    return match_5;
}

int unwrap_1(struct IntOption opt_) {
    int match_6;
    if ((!(opt_.some))) goto next_247;
    int value_ = opt_.value;
    match_6 = value_;
    goto end_match_246;
next_247:;
    if (opt_.some) goto next_248;
    printf("Can\'t unwrap None.\n");
    exit(1);
    match_6 = 0;
    goto end_match_246;
next_248:;
    exit(1);
end_match_246:;
    return match_6;
}

int isEmptyTest_(int arg_42) {
    bool call_45 = isEmpty_((struct String){.str = "", .len = 0});
    milone_assert(call_45, 15, 2);
    bool call_46 = isEmpty_((struct String){.str = "\0", .len = 1});
    milone_assert((!(call_46)), 16, 2);
    return 0;
}

int tryItemTest_(int arg_43) {
    struct CharOption call_47 = tryItem_(0, (struct String){.str = "", .len = 0});
    bool call_48 = isNone_2(call_47);
    milone_assert(call_48, 19, 2);
    struct CharOption call_49 = tryItem_(-1, (struct String){.str = "a", .len = 1});
    bool call_50 = isNone_2(call_49);
    milone_assert(call_50, 20, 2);
    struct CharOption call_51 = tryItem_(1, (struct String){.str = "a", .len = 1});
    bool call_52 = isNone_2(call_51);
    milone_assert(call_52, 21, 2);
    struct CharOption call_53 = tryItem_(2, (struct String){.str = "abc", .len = 3});
    char call_54 = unwrap_2(call_53);
    milone_assert((call_54 == 'c'), 22, 2);
    return 0;
}

int startsWithTest_(int arg_44) {
    bool call_55 = startsWith_((struct String){.str = "/bin", .len = 4}, (struct String){.str = "/usr/bin", .len = 8});
    milone_assert((!(call_55)), 25, 2);
    bool call_56 = startsWith_((struct String){.str = "/bin", .len = 4}, (struct String){.str = "/bin/ls", .len = 7});
    milone_assert(call_56, 26, 2);
    bool call_57 = startsWith_((struct String){.str = "", .len = 0}, (struct String){.str = "", .len = 0});
    milone_assert(call_57, 27, 2);
    return 0;
}

int endsWithTest_(int arg_45) {
    bool call_58 = endsWith_((struct String){.str = "/bin", .len = 4}, (struct String){.str = "/usr/bin", .len = 8});
    milone_assert(call_58, 30, 2);
    bool call_59 = endsWith_((struct String){.str = "/bin", .len = 4}, (struct String){.str = "/bin/ls", .len = 7});
    milone_assert((!(call_59)), 31, 2);
    bool call_60 = endsWith_((struct String){.str = "", .len = 0}, (struct String){.str = "", .len = 0});
    milone_assert(call_60, 32, 2);
    return 0;
}

int findIndexTest_(int arg_46) {
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

int findLastIndexTest_(int arg_47) {
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

int containsTest_(int arg_48) {
    bool call_81 = contains_((struct String){.str = "ab", .len = 2}, (struct String){.str = "cacbc", .len = 5});
    milone_assert((!(call_81)), 51, 2);
    bool call_82 = contains_((struct String){.str = "ab", .len = 2}, (struct String){.str = "ccabccabcc", .len = 10});
    milone_assert(call_82, 52, 2);
    bool call_83 = contains_((struct String){.str = "", .len = 0}, (struct String){.str = "", .len = 0});
    milone_assert(call_83, 53, 2);
    return 0;
}

int truncateTest_(int arg_49) {
    struct String call_84 = truncate_(-1, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_84, (struct String){.str = "", .len = 0}) == 0), 56, 2);
    struct String call_85 = truncate_(0, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_85, (struct String){.str = "", .len = 0}) == 0), 57, 2);
    struct String call_86 = truncate_(1, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_86, (struct String){.str = "a", .len = 1}) == 0), 58, 2);
    struct String call_87 = truncate_(2, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_87, (struct String){.str = "ab", .len = 2}) == 0), 59, 2);
    struct String call_88 = truncate_(3, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_88, (struct String){.str = "ab", .len = 2}) == 0), 60, 2);
    return 0;
}

int skipTest_(int arg_50) {
    struct String call_89 = skip_(-1, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_89, (struct String){.str = "ab", .len = 2}) == 0), 63, 2);
    struct String call_90 = skip_(0, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_90, (struct String){.str = "ab", .len = 2}) == 0), 64, 2);
    struct String call_91 = skip_(1, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_91, (struct String){.str = "b", .len = 1}) == 0), 65, 2);
    struct String call_92 = skip_(2, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_92, (struct String){.str = "", .len = 0}) == 0), 66, 2);
    struct String call_93 = skip_(3, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_93, (struct String){.str = "", .len = 0}) == 0), 67, 2);
    return 0;
}

int sliceTest_(int arg_51) {
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

int trimTest_(int arg_52) {
    struct String call_102 = trim_((struct String){.str = "  ab  ", .len = 6});
    milone_assert((str_compare(call_102, (struct String){.str = "ab", .len = 2}) == 0), 80, 2);
    struct String call_103 = trimStart_((struct String){.str = "  ab  ", .len = 6});
    milone_assert((str_compare(call_103, (struct String){.str = "ab  ", .len = 4}) == 0), 81, 2);
    struct String call_104 = trimEnd_((struct String){.str = " ab", .len = 3});
    milone_assert((str_compare(call_104, (struct String){.str = " ab", .len = 3}) == 0), 82, 2);
    return 0;
}

int replaceTest_(int arg_53) {
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

int splitTest_(int arg_54) {
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

int concatTest_(int arg_55) {
    struct StringList const* list_6 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_6))) = (struct StringList){.head = (struct String){.str = "ef", .len = 2}, .tail = NULL};
    struct StringList const* list_5 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_5))) = (struct StringList){.head = (struct String){.str = "cd", .len = 2}, .tail = list_6};
    struct StringList const* list_4 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_4))) = (struct StringList){.head = (struct String){.str = "ab", .len = 2}, .tail = list_5};
    struct String call_119 = concat_((struct String){.str = ", ", .len = 2}, list_4);
    milone_assert((str_compare(call_119, (struct String){.str = "ab, cd, ef", .len = 10}) == 0), 98, 2);
    struct String call_120 = concat_((struct String){.str = "", .len = 0}, NULL);
    milone_assert((str_compare(call_120, (struct String){.str = "", .len = 0}) == 0), 99, 2);
    return 0;
}

int milone_main() {
    int call_121 = isEmptyTest_(0);
    int call_122 = tryItemTest_(0);
    int call_123 = startsWithTest_(0);
    int call_124 = endsWithTest_(0);
    int call_125 = findIndexTest_(0);
    int call_126 = findLastIndexTest_(0);
    int call_127 = containsTest_(0);
    int call_128 = truncateTest_(0);
    int call_129 = skipTest_(0);
    int call_130 = sliceTest_(0);
    int call_131 = trimTest_(0);
    int call_132 = replaceTest_(0);
    int call_133 = splitTest_(0);
    int call_134 = concatTest_(0);
    return 0;
}
