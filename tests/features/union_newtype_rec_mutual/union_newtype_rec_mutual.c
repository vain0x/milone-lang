#include "milone.h"

struct Odd_;

struct Oddoption1_;

struct StringOddoption1Tuple2_;

struct StringOddoption1Tuple2option1_;

struct IntStringOddoption1Tuple2option1Tuple2_;

int milone_main(void);

enum Odd_Discriminant {
    Odd_,
};

struct Odd_ {
    enum Odd_Discriminant discriminant;
    union {
        void const* Odd_;
    };
};

enum Oddoption1_Discriminant {
    None_1,
    Some_1,
};

struct Oddoption1_ {
    enum Oddoption1_Discriminant discriminant;
    union {
        struct Odd_ Some_1;
    };
};

struct StringOddoption1Tuple2_ {
    struct String t0;
    struct Oddoption1_ t1;
};

enum StringOddoption1Tuple2option1_Discriminant {
    None_2,
    Some_2,
};

struct StringOddoption1Tuple2option1_ {
    enum StringOddoption1Tuple2option1_Discriminant discriminant;
    union {
        struct StringOddoption1Tuple2_ Some_2;
    };
};

struct IntStringOddoption1Tuple2option1Tuple2_ {
    int t0;
    struct StringOddoption1Tuple2option1_ t1;
};

int milone_main(void) {
    int n1_;
    struct String s2_;
    int n3_;
    struct String s4_;
    struct IntStringOddoption1Tuple2option1Tuple2_ IntStringOddoption1Tuple2option1Tuple2_ = (struct IntStringOddoption1Tuple2option1Tuple2_){.t0 = 1, .t1 = (struct StringOddoption1Tuple2option1_){.discriminant = None_2}};
    void const* box_ = milone_mem_alloc(1, sizeof(struct IntStringOddoption1Tuple2option1Tuple2_));
    (*(((struct IntStringOddoption1Tuple2option1Tuple2_*)box_))) = IntStringOddoption1Tuple2option1Tuple2_;
    struct Odd_ variant_ = (struct Odd_){.discriminant = Odd_, .Odd_ = box_};
    struct Odd_ one_ = variant_;
    struct Oddoption1_ variant_1 = (struct Oddoption1_){.discriminant = Some_1, .Some_1 = one_};
    struct StringOddoption1Tuple2_ StringOddoption1Tuple2_ = (struct StringOddoption1Tuple2_){.t0 = (struct String){.str = "two", .len = 3}, .t1 = variant_1};
    struct StringOddoption1Tuple2_ two_ = StringOddoption1Tuple2_;
    struct StringOddoption1Tuple2option1_ variant_2 = (struct StringOddoption1Tuple2option1_){.discriminant = Some_2, .Some_2 = two_};
    struct IntStringOddoption1Tuple2option1Tuple2_ IntStringOddoption1Tuple2option1Tuple2_1 = (struct IntStringOddoption1Tuple2option1Tuple2_){.t0 = 3, .t1 = variant_2};
    void const* box_1 = milone_mem_alloc(1, sizeof(struct IntStringOddoption1Tuple2option1Tuple2_));
    (*(((struct IntStringOddoption1Tuple2option1Tuple2_*)box_1))) = IntStringOddoption1Tuple2option1Tuple2_1;
    struct Odd_ variant_3 = (struct Odd_){.discriminant = Odd_, .Odd_ = box_1};
    struct Odd_ three_ = variant_3;
    struct Oddoption1_ variant_4 = (struct Oddoption1_){.discriminant = Some_1, .Some_1 = three_};
    struct StringOddoption1Tuple2_ StringOddoption1Tuple2_1 = (struct StringOddoption1Tuple2_){.t0 = (struct String){.str = "four", .len = 4}, .t1 = variant_4};
    struct StringOddoption1Tuple2_ four_ = StringOddoption1Tuple2_1;
    char match_;
    s4_ = four_.t0;
    if ((four_.t1.discriminant != Some_1)) goto next_2;
    n3_ = (*(((struct IntStringOddoption1Tuple2option1Tuple2_ const*)four_.t1.Some_1.Odd_))).t0;
    if (((*(((struct IntStringOddoption1Tuple2option1Tuple2_ const*)four_.t1.Some_1.Odd_))).t1.discriminant != Some_2)) goto next_2;
    s2_ = (*(((struct IntStringOddoption1Tuple2option1Tuple2_ const*)four_.t1.Some_1.Odd_))).t1.Some_2.t0;
    if (((*(((struct IntStringOddoption1Tuple2option1Tuple2_ const*)four_.t1.Some_1.Odd_))).t1.Some_2.t1.discriminant != Some_1)) goto next_2;
    n1_ = (*(((struct IntStringOddoption1Tuple2option1Tuple2_ const*)(*(((struct IntStringOddoption1Tuple2option1Tuple2_ const*)four_.t1.Some_1.Odd_))).t1.Some_2.t1.Some_1.Odd_))).t0;
    if (((*(((struct IntStringOddoption1Tuple2option1Tuple2_ const*)(*(((struct IntStringOddoption1Tuple2option1Tuple2_ const*)four_.t1.Some_1.Odd_))).t1.Some_2.t1.Some_1.Odd_))).t1.discriminant != None_2)) goto next_2;
    milone_assert((n1_ == 1), 15, 4);
    milone_assert((str_compare(s2_, (struct String){.str = "two", .len = 3}) == 0), 16, 4);
    milone_assert((n3_ == 3), 17, 4);
    milone_assert((str_compare(s4_, (struct String){.str = "four", .len = 4}) == 0), 18, 4);
    match_ = 0;
    goto end_match_1;
next_2:;
    milone_assert(false, 20, 9);
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    return 0;
}
