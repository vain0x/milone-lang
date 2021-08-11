#include "milone.h"

struct CharOption_;

struct IntOption_;

struct StringList;

struct StringList;

char unwrap_1(struct CharOption_ opt_8);

int unwrap_(struct IntOption_ opt_8);

bool MiloneStd_StdString_isEmpty(struct String);

char std_string_Program_isEmptyTest(char arg_42);

struct CharOption_ MiloneStd_StdString_tryItem(int, struct String);

bool isNone_1(struct CharOption_);

char std_string_Program_tryItemTest(char arg_43);

bool MiloneStd_StdString_startsWith(struct String, struct String);

char std_string_Program_startsWithTest(char arg_44);

bool MiloneStd_StdString_endsWith(struct String, struct String);

char std_string_Program_endsWithTest(char arg_45);

struct IntOption_ MiloneStd_StdString_findIndex(struct String, struct String);

bool isNone_(struct IntOption_);

char std_string_Program_findIndexTest(char arg_46);

struct IntOption_ MiloneStd_StdString_findLastIndex(struct String, struct String);

char std_string_Program_findLastIndexTest(char arg_47);

bool MiloneStd_StdString_contains(struct String, struct String);

char std_string_Program_containsTest(char arg_48);

struct String MiloneStd_StdString_truncate(int, struct String);

char std_string_Program_truncateTest(char arg_49);

struct String MiloneStd_StdString_skip(int, struct String);

char std_string_Program_skipTest(char arg_50);

struct String MiloneStd_StdString_slice(int, int, struct String);

char std_string_Program_sliceTest(char arg_51);

struct String MiloneStd_StdString_trim(struct String);

struct String MiloneStd_StdString_trimStart(struct String);

struct String MiloneStd_StdString_trimEnd(struct String);

char std_string_Program_trimTest(char arg_52);

struct String MiloneStd_StdString_replace(struct String, struct String, struct String);

char std_string_Program_replaceTest(char arg_53);

struct StringList const* MiloneStd_StdString_toLines(struct String);

struct String MiloneStd_StdString_concat(struct String, struct StringList const*);

char std_string_Program_splitTest(char arg_54);

char std_string_Program_concatTest(char arg_55);

int milone_main();

enum CharOption_Discriminant {
    None_1,
    Some_1,
};

struct CharOption_ {
    enum CharOption_Discriminant discriminant;
    union {
        char Some_1;
    };
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

struct StringList {
    struct String head;
    struct StringList const* tail;
};

char unwrap_1(struct CharOption_ opt_8) {
    char value_2;
    char match_2;
    if ((opt_8.discriminant != Some_1)) goto next_241;
    value_2 = opt_8.Some_1;
    match_2 = value_2;
    goto end_match_240;
next_241:;
    if ((opt_8.discriminant != None_1)) goto next_242;
    printf("Can\'t unwrap None.\n");
    exit(1);
next_242:;
    exit(1);
end_match_240:;
    return match_2;
}

int unwrap_(struct IntOption_ opt_8) {
    int value_2;
    int match_3;
    if ((opt_8.discriminant != Some_)) goto next_244;
    value_2 = opt_8.Some_;
    match_3 = value_2;
    goto end_match_243;
next_244:;
    if ((opt_8.discriminant != None_)) goto next_245;
    printf("Can\'t unwrap None.\n");
    exit(1);
next_245:;
    exit(1);
end_match_243:;
    return match_3;
}

char std_string_Program_isEmptyTest(char arg_42) {
    bool call_45 = MiloneStd_StdString_isEmpty((struct String){.str = "", .len = 0});
    milone_assert(call_45, 15, 2);
    bool call_46 = MiloneStd_StdString_isEmpty((struct String){.str = "\0", .len = 1});
    milone_assert((!(call_46)), 16, 2);
    return 0;
}

char std_string_Program_tryItemTest(char arg_43) {
    struct CharOption_ call_47 = MiloneStd_StdString_tryItem(0, (struct String){.str = "", .len = 0});
    bool call_48 = isNone_1(call_47);
    milone_assert(call_48, 19, 2);
    struct CharOption_ call_49 = MiloneStd_StdString_tryItem(-1, (struct String){.str = "a", .len = 1});
    bool call_50 = isNone_1(call_49);
    milone_assert(call_50, 20, 2);
    struct CharOption_ call_51 = MiloneStd_StdString_tryItem(1, (struct String){.str = "a", .len = 1});
    bool call_52 = isNone_1(call_51);
    milone_assert(call_52, 21, 2);
    struct CharOption_ call_53 = MiloneStd_StdString_tryItem(2, (struct String){.str = "abc", .len = 3});
    char call_54 = unwrap_1(call_53);
    milone_assert((call_54 == 'c'), 22, 2);
    return 0;
}

char std_string_Program_startsWithTest(char arg_44) {
    bool call_55 = MiloneStd_StdString_startsWith((struct String){.str = "/bin", .len = 4}, (struct String){.str = "/usr/bin", .len = 8});
    milone_assert((!(call_55)), 25, 2);
    bool call_56 = MiloneStd_StdString_startsWith((struct String){.str = "/bin", .len = 4}, (struct String){.str = "/bin/ls", .len = 7});
    milone_assert(call_56, 26, 2);
    bool call_57 = MiloneStd_StdString_startsWith((struct String){.str = "", .len = 0}, (struct String){.str = "", .len = 0});
    milone_assert(call_57, 27, 2);
    return 0;
}

char std_string_Program_endsWithTest(char arg_45) {
    bool call_58 = MiloneStd_StdString_endsWith((struct String){.str = "/bin", .len = 4}, (struct String){.str = "/usr/bin", .len = 8});
    milone_assert(call_58, 30, 2);
    bool call_59 = MiloneStd_StdString_endsWith((struct String){.str = "/bin", .len = 4}, (struct String){.str = "/bin/ls", .len = 7});
    milone_assert((!(call_59)), 31, 2);
    bool call_60 = MiloneStd_StdString_endsWith((struct String){.str = "", .len = 0}, (struct String){.str = "", .len = 0});
    milone_assert(call_60, 32, 2);
    return 0;
}

char std_string_Program_findIndexTest(char arg_46) {
    struct IntOption_ call_61 = MiloneStd_StdString_findIndex((struct String){.str = "ab", .len = 2}, (struct String){.str = "", .len = 0});
    bool call_62 = isNone_(call_61);
    milone_assert(call_62, 35, 2);
    struct IntOption_ call_63 = MiloneStd_StdString_findIndex((struct String){.str = "ab", .len = 2}, (struct String){.str = "cacbc", .len = 5});
    bool call_64 = isNone_(call_63);
    milone_assert(call_64, 36, 2);
    struct IntOption_ call_65 = MiloneStd_StdString_findIndex((struct String){.str = "ab", .len = 2}, (struct String){.str = "abcc", .len = 4});
    int call_66 = unwrap_(call_65);
    milone_assert((call_66 == 0), 38, 2);
    struct IntOption_ call_67 = MiloneStd_StdString_findIndex((struct String){.str = "ab", .len = 2}, (struct String){.str = "ccabccabcc", .len = 10});
    int call_68 = unwrap_(call_67);
    milone_assert((call_68 == 2), 39, 2);
    struct IntOption_ call_69 = MiloneStd_StdString_findIndex((struct String){.str = "", .len = 0}, (struct String){.str = "", .len = 0});
    int call_70 = unwrap_(call_69);
    milone_assert((call_70 == 0), 40, 2);
    return 0;
}

char std_string_Program_findLastIndexTest(char arg_47) {
    struct IntOption_ call_71 = MiloneStd_StdString_findLastIndex((struct String){.str = "ab", .len = 2}, (struct String){.str = "", .len = 0});
    bool call_72 = isNone_(call_71);
    milone_assert(call_72, 43, 2);
    struct IntOption_ call_73 = MiloneStd_StdString_findLastIndex((struct String){.str = "ab", .len = 2}, (struct String){.str = "cacbc", .len = 5});
    bool call_74 = isNone_(call_73);
    milone_assert(call_74, 44, 2);
    struct IntOption_ call_75 = MiloneStd_StdString_findLastIndex((struct String){.str = "ab", .len = 2}, (struct String){.str = "ccab", .len = 4});
    int call_76 = unwrap_(call_75);
    milone_assert((call_76 == 2), 46, 2);
    struct IntOption_ call_77 = MiloneStd_StdString_findLastIndex((struct String){.str = "ab", .len = 2}, (struct String){.str = "ccabccabcc", .len = 10});
    int call_78 = unwrap_(call_77);
    milone_assert((call_78 == 6), 47, 2);
    struct IntOption_ call_79 = MiloneStd_StdString_findLastIndex((struct String){.str = "", .len = 0}, (struct String){.str = "", .len = 0});
    int call_80 = unwrap_(call_79);
    milone_assert((call_80 == 0), 48, 2);
    return 0;
}

char std_string_Program_containsTest(char arg_48) {
    bool call_81 = MiloneStd_StdString_contains((struct String){.str = "ab", .len = 2}, (struct String){.str = "cacbc", .len = 5});
    milone_assert((!(call_81)), 51, 2);
    bool call_82 = MiloneStd_StdString_contains((struct String){.str = "ab", .len = 2}, (struct String){.str = "ccabccabcc", .len = 10});
    milone_assert(call_82, 52, 2);
    bool call_83 = MiloneStd_StdString_contains((struct String){.str = "", .len = 0}, (struct String){.str = "", .len = 0});
    milone_assert(call_83, 53, 2);
    return 0;
}

char std_string_Program_truncateTest(char arg_49) {
    struct String call_84 = MiloneStd_StdString_truncate(-1, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_84, (struct String){.str = "", .len = 0}) == 0), 56, 2);
    struct String call_85 = MiloneStd_StdString_truncate(0, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_85, (struct String){.str = "", .len = 0}) == 0), 57, 2);
    struct String call_86 = MiloneStd_StdString_truncate(1, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_86, (struct String){.str = "a", .len = 1}) == 0), 58, 2);
    struct String call_87 = MiloneStd_StdString_truncate(2, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_87, (struct String){.str = "ab", .len = 2}) == 0), 59, 2);
    struct String call_88 = MiloneStd_StdString_truncate(3, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_88, (struct String){.str = "ab", .len = 2}) == 0), 60, 2);
    return 0;
}

char std_string_Program_skipTest(char arg_50) {
    struct String call_89 = MiloneStd_StdString_skip(-1, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_89, (struct String){.str = "ab", .len = 2}) == 0), 63, 2);
    struct String call_90 = MiloneStd_StdString_skip(0, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_90, (struct String){.str = "ab", .len = 2}) == 0), 64, 2);
    struct String call_91 = MiloneStd_StdString_skip(1, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_91, (struct String){.str = "b", .len = 1}) == 0), 65, 2);
    struct String call_92 = MiloneStd_StdString_skip(2, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_92, (struct String){.str = "", .len = 0}) == 0), 66, 2);
    struct String call_93 = MiloneStd_StdString_skip(3, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_93, (struct String){.str = "", .len = 0}) == 0), 67, 2);
    return 0;
}

char std_string_Program_sliceTest(char arg_51) {
    struct String call_94 = MiloneStd_StdString_slice(-2, -1, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_94, (struct String){.str = "", .len = 0}) == 0), 70, 2);
    struct String call_95 = MiloneStd_StdString_slice(-1, 1, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_95, (struct String){.str = "a", .len = 1}) == 0), 71, 2);
    struct String call_96 = MiloneStd_StdString_slice(0, 1, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_96, (struct String){.str = "a", .len = 1}) == 0), 72, 2);
    struct String call_97 = MiloneStd_StdString_slice(0, 2, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_97, (struct String){.str = "ab", .len = 2}) == 0), 73, 2);
    struct String call_98 = MiloneStd_StdString_slice(0, 3, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_98, (struct String){.str = "ab", .len = 2}) == 0), 74, 2);
    struct String call_99 = MiloneStd_StdString_slice(1, 2, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_99, (struct String){.str = "b", .len = 1}) == 0), 75, 2);
    struct String call_100 = MiloneStd_StdString_slice(1, 3, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_100, (struct String){.str = "b", .len = 1}) == 0), 76, 2);
    struct String call_101 = MiloneStd_StdString_slice(2, 3, (struct String){.str = "ab", .len = 2});
    milone_assert((str_compare(call_101, (struct String){.str = "", .len = 0}) == 0), 77, 2);
    return 0;
}

char std_string_Program_trimTest(char arg_52) {
    struct String call_102 = MiloneStd_StdString_trim((struct String){.str = "  ab  ", .len = 6});
    milone_assert((str_compare(call_102, (struct String){.str = "ab", .len = 2}) == 0), 80, 2);
    struct String call_103 = MiloneStd_StdString_trimStart((struct String){.str = "  ab  ", .len = 6});
    milone_assert((str_compare(call_103, (struct String){.str = "ab  ", .len = 4}) == 0), 81, 2);
    struct String call_104 = MiloneStd_StdString_trimEnd((struct String){.str = " ab", .len = 3});
    milone_assert((str_compare(call_104, (struct String){.str = " ab", .len = 3}) == 0), 82, 2);
    return 0;
}

char std_string_Program_replaceTest(char arg_53) {
    struct String call_105 = MiloneStd_StdString_replace((struct String){.str = "a", .len = 1}, (struct String){.str = "A", .len = 1}, (struct String){.str = "abaca", .len = 5});
    milone_assert((str_compare(call_105, (struct String){.str = "AbAcA", .len = 5}) == 0), 85, 2);
    struct String call_106 = MiloneStd_StdString_replace((struct String){.str = "xy", .len = 2}, (struct String){.str = "yx", .len = 2}, (struct String){.str = "xyxyx", .len = 5});
    milone_assert((str_compare(call_106, (struct String){.str = "yxyxx", .len = 5}) == 0), 86, 2);
    struct String call_107 = MiloneStd_StdString_replace((struct String){.str = "", .len = 0}, (struct String){.str = "", .len = 0}, (struct String){.str = "as is", .len = 5});
    milone_assert((str_compare(call_107, (struct String){.str = "as is", .len = 5}) == 0), 87, 2);
    struct String call_108 = MiloneStd_StdString_replace((struct String){.str = "aa", .len = 2}, (struct String){.str = "a", .len = 1}, (struct String){.str = "aaaaa", .len = 5});
    milone_assert((str_compare(call_108, (struct String){.str = "aaa", .len = 3}) == 0), 88, 2);
    return 0;
}

char std_string_Program_splitTest(char arg_54) {
    struct StringList const* call_109 = MiloneStd_StdString_toLines((struct String){.str = "a\nb\nc", .len = 5});
    struct String call_110 = MiloneStd_StdString_concat((struct String){.str = ";", .len = 1}, call_109);
    milone_assert((str_compare(call_110, (struct String){.str = "a;b;c", .len = 5}) == 0), 91, 2);
    struct StringList const* call_111 = MiloneStd_StdString_toLines((struct String){.str = "a\nb\nc\n", .len = 6});
    struct String call_112 = MiloneStd_StdString_concat((struct String){.str = ";", .len = 1}, call_111);
    milone_assert((str_compare(call_112, (struct String){.str = "a;b;c;", .len = 6}) == 0), 92, 2);
    struct StringList const* call_113 = MiloneStd_StdString_toLines((struct String){.str = "a", .len = 1});
    struct String call_114 = MiloneStd_StdString_concat((struct String){.str = ";", .len = 1}, call_113);
    milone_assert((str_compare(call_114, (struct String){.str = "a", .len = 1}) == 0), 93, 2);
    struct StringList const* call_115 = MiloneStd_StdString_toLines((struct String){.str = "\n", .len = 1});
    struct String call_116 = MiloneStd_StdString_concat((struct String){.str = ";", .len = 1}, call_115);
    milone_assert((str_compare(call_116, (struct String){.str = ";", .len = 1}) == 0), 94, 2);
    struct StringList const* call_117 = MiloneStd_StdString_toLines((struct String){.str = "", .len = 0});
    struct String call_118 = MiloneStd_StdString_concat((struct String){.str = ";", .len = 1}, call_117);
    milone_assert((str_compare(call_118, (struct String){.str = "", .len = 0}) == 0), 95, 2);
    return 0;
}

char std_string_Program_concatTest(char arg_55) {
    struct StringList const* list_6 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_6))) = (struct StringList){.head = (struct String){.str = "ef", .len = 2}, .tail = NULL};
    struct StringList const* list_5 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_5))) = (struct StringList){.head = (struct String){.str = "cd", .len = 2}, .tail = list_6};
    struct StringList const* list_4 = milone_mem_alloc(1, sizeof(struct StringList));
    (*(((struct StringList*)list_4))) = (struct StringList){.head = (struct String){.str = "ab", .len = 2}, .tail = list_5};
    struct String call_119 = MiloneStd_StdString_concat((struct String){.str = ", ", .len = 2}, list_4);
    milone_assert((str_compare(call_119, (struct String){.str = "ab, cd, ef", .len = 10}) == 0), 98, 2);
    struct String call_120 = MiloneStd_StdString_concat((struct String){.str = "", .len = 0}, NULL);
    milone_assert((str_compare(call_120, (struct String){.str = "", .len = 0}) == 0), 99, 2);
    return 0;
}

int milone_main() {
    char call_121 = std_string_Program_isEmptyTest(0);
    char call_122 = std_string_Program_tryItemTest(0);
    char call_123 = std_string_Program_startsWithTest(0);
    char call_124 = std_string_Program_endsWithTest(0);
    char call_125 = std_string_Program_findIndexTest(0);
    char call_126 = std_string_Program_findLastIndexTest(0);
    char call_127 = std_string_Program_containsTest(0);
    char call_128 = std_string_Program_truncateTest(0);
    char call_129 = std_string_Program_skipTest(0);
    char call_130 = std_string_Program_sliceTest(0);
    char call_131 = std_string_Program_trimTest(0);
    char call_132 = std_string_Program_replaceTest(0);
    char call_133 = std_string_Program_splitTest(0);
    char call_134 = std_string_Program_concatTest(0);
    return 0;
}
