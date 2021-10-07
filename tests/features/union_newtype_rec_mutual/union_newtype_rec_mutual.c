#include "milone.h"

struct ObjectOption_;

struct IntObjectOptionTuple2_;

struct Odd_;

struct OddOption_;

struct StringOddOptionTuple2_;

int milone_main(void);

enum ObjectOption_Discriminant {
    None_1,
    Some_1,
};

struct ObjectOption_ {
    enum ObjectOption_Discriminant discriminant;
    union {
        void const* Some_1;
    };
};

struct IntObjectOptionTuple2_ {
    int t0;
    struct ObjectOption_ t1;
};

enum Odd_Discriminant {
    Odd_,
};

struct Odd_ {
    enum Odd_Discriminant discriminant;
    union {
        void const* Odd_;
    };
};

enum OddOption_Discriminant {
    None_2,
    Some_2,
};

struct OddOption_ {
    enum OddOption_Discriminant discriminant;
    union {
        struct Odd_ Some_2;
    };
};

struct StringOddOptionTuple2_ {
    struct String t0;
    struct OddOption_ t1;
};

int milone_main(void) {
    int n1_;
    struct String s2_;
    int n3_;
    struct String s4_;
    struct IntObjectOptionTuple2_ IntObjectOptionTuple2_ = (struct IntObjectOptionTuple2_){.t0 = 1, .t1 = (struct ObjectOption_){.discriminant = None_1}};
    void const* box_ = milone_mem_alloc(1, sizeof(struct IntObjectOptionTuple2_));
    (*(((struct IntObjectOptionTuple2_*)box_))) = IntObjectOptionTuple2_;
    struct Odd_ variant_ = (struct Odd_){.discriminant = Odd_, .Odd_ = box_};
    struct Odd_ one_ = variant_;
    struct OddOption_ variant_1 = (struct OddOption_){.discriminant = Some_2, .Some_2 = one_};
    struct StringOddOptionTuple2_ StringOddOptionTuple2_ = (struct StringOddOptionTuple2_){.t0 = (struct String){.str = "two", .len = 3}, .t1 = variant_1};
    void const* box_1 = milone_mem_alloc(1, sizeof(struct StringOddOptionTuple2_));
    (*(((struct StringOddOptionTuple2_*)box_1))) = StringOddOptionTuple2_;
    void const* two_ = box_1;
    struct ObjectOption_ variant_2 = (struct ObjectOption_){.discriminant = Some_1, .Some_1 = two_};
    struct IntObjectOptionTuple2_ IntObjectOptionTuple2_1 = (struct IntObjectOptionTuple2_){.t0 = 3, .t1 = variant_2};
    void const* box_2 = milone_mem_alloc(1, sizeof(struct IntObjectOptionTuple2_));
    (*(((struct IntObjectOptionTuple2_*)box_2))) = IntObjectOptionTuple2_1;
    struct Odd_ variant_3 = (struct Odd_){.discriminant = Odd_, .Odd_ = box_2};
    struct Odd_ three_ = variant_3;
    struct OddOption_ variant_4 = (struct OddOption_){.discriminant = Some_2, .Some_2 = three_};
    struct StringOddOptionTuple2_ StringOddOptionTuple2_1 = (struct StringOddOptionTuple2_){.t0 = (struct String){.str = "four", .len = 4}, .t1 = variant_4};
    void const* box_3 = milone_mem_alloc(1, sizeof(struct StringOddOptionTuple2_));
    (*(((struct StringOddOptionTuple2_*)box_3))) = StringOddOptionTuple2_1;
    void const* four_ = box_3;
    char match_;
    s4_ = (*(((struct StringOddOptionTuple2_ const*)four_))).t0;
    if (((*(((struct StringOddOptionTuple2_ const*)four_))).t1.discriminant != Some_2)) goto next_2;
    n3_ = (*(((struct IntObjectOptionTuple2_ const*)(*(((struct StringOddOptionTuple2_ const*)four_))).t1.Some_2.Odd_))).t0;
    if (((*(((struct IntObjectOptionTuple2_ const*)(*(((struct StringOddOptionTuple2_ const*)four_))).t1.Some_2.Odd_))).t1.discriminant != Some_1)) goto next_2;
    s2_ = (*(((struct StringOddOptionTuple2_ const*)(*(((struct IntObjectOptionTuple2_ const*)(*(((struct StringOddOptionTuple2_ const*)four_))).t1.Some_2.Odd_))).t1.Some_1))).t0;
    if (((*(((struct StringOddOptionTuple2_ const*)(*(((struct IntObjectOptionTuple2_ const*)(*(((struct StringOddOptionTuple2_ const*)four_))).t1.Some_2.Odd_))).t1.Some_1))).t1.discriminant != Some_2)) goto next_2;
    n1_ = (*(((struct IntObjectOptionTuple2_ const*)(*(((struct StringOddOptionTuple2_ const*)(*(((struct IntObjectOptionTuple2_ const*)(*(((struct StringOddOptionTuple2_ const*)four_))).t1.Some_2.Odd_))).t1.Some_1))).t1.Some_2.Odd_))).t0;
    if (((*(((struct IntObjectOptionTuple2_ const*)(*(((struct StringOddOptionTuple2_ const*)(*(((struct IntObjectOptionTuple2_ const*)(*(((struct StringOddOptionTuple2_ const*)four_))).t1.Some_2.Odd_))).t1.Some_1))).t1.Some_2.Odd_))).t1.discriminant != None_1)) goto next_2;
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
