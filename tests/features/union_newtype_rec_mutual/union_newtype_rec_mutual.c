#include "milone.h"

struct ObjectOption;

struct IntObjectOptionTuple2;

enum Odd_Discriminant;

struct Odd_;

struct Odd_Option;

struct StringOdd_OptionTuple2;

int milone_main();

struct ObjectOption {
    bool some;
    void const* value;
};

struct IntObjectOptionTuple2 {
    int t0;
    struct ObjectOption t1;
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

struct Odd_Option {
    bool some;
    struct Odd_ value;
};

struct StringOdd_OptionTuple2 {
    struct String t0;
    struct Odd_Option t1;
};

int milone_main() {
    struct IntObjectOptionTuple2 tuple_ = (struct IntObjectOptionTuple2){.t0 = 1, .t1 = ((struct ObjectOption){})};
    void const* box_ = milone_mem_alloc(1, sizeof(struct IntObjectOptionTuple2));
    (*(((struct IntObjectOptionTuple2*)box_))) = tuple_;
    struct Odd_ variant_ = (struct Odd_){.discriminant = Odd_, .Odd_ = box_};
    struct Odd_ one_ = variant_;
    struct Odd_Option some_ = (struct Odd_Option){.some = true, .value = one_};
    struct StringOdd_OptionTuple2 tuple_1 = (struct StringOdd_OptionTuple2){.t0 = (struct String){.str = "two", .len = 3}, .t1 = some_};
    void const* box_1 = milone_mem_alloc(1, sizeof(struct StringOdd_OptionTuple2));
    (*(((struct StringOdd_OptionTuple2*)box_1))) = tuple_1;
    void const* two_ = box_1;
    struct ObjectOption some_1 = (struct ObjectOption){.some = true, .value = two_};
    struct IntObjectOptionTuple2 tuple_2 = (struct IntObjectOptionTuple2){.t0 = 3, .t1 = some_1};
    void const* box_2 = milone_mem_alloc(1, sizeof(struct IntObjectOptionTuple2));
    (*(((struct IntObjectOptionTuple2*)box_2))) = tuple_2;
    struct Odd_ variant_1 = (struct Odd_){.discriminant = Odd_, .Odd_ = box_2};
    struct Odd_ three_ = variant_1;
    struct Odd_Option some_2 = (struct Odd_Option){.some = true, .value = three_};
    struct StringOdd_OptionTuple2 tuple_3 = (struct StringOdd_OptionTuple2){.t0 = (struct String){.str = "four", .len = 4}, .t1 = some_2};
    void const* box_3 = milone_mem_alloc(1, sizeof(struct StringOdd_OptionTuple2));
    (*(((struct StringOdd_OptionTuple2*)box_3))) = tuple_3;
    void const* four_ = box_3;
    char match_;
    struct String s4_ = (*(((struct StringOdd_OptionTuple2 const*)four_))).t0;
    if ((!((*(((struct StringOdd_OptionTuple2 const*)four_))).t1.some))) goto next_2;
    int n3_ = (*(((struct IntObjectOptionTuple2 const*)(*(((struct StringOdd_OptionTuple2 const*)four_))).t1.value.Odd_))).t0;
    if ((!((*(((struct IntObjectOptionTuple2 const*)(*(((struct StringOdd_OptionTuple2 const*)four_))).t1.value.Odd_))).t1.some))) goto next_2;
    struct String s2_ = (*(((struct StringOdd_OptionTuple2 const*)(*(((struct IntObjectOptionTuple2 const*)(*(((struct StringOdd_OptionTuple2 const*)four_))).t1.value.Odd_))).t1.value))).t0;
    if ((!((*(((struct StringOdd_OptionTuple2 const*)(*(((struct IntObjectOptionTuple2 const*)(*(((struct StringOdd_OptionTuple2 const*)four_))).t1.value.Odd_))).t1.value))).t1.some))) goto next_2;
    int n1_ = (*(((struct IntObjectOptionTuple2 const*)(*(((struct StringOdd_OptionTuple2 const*)(*(((struct IntObjectOptionTuple2 const*)(*(((struct StringOdd_OptionTuple2 const*)four_))).t1.value.Odd_))).t1.value))).t1.value.Odd_))).t0;
    if ((*(((struct IntObjectOptionTuple2 const*)(*(((struct StringOdd_OptionTuple2 const*)(*(((struct IntObjectOptionTuple2 const*)(*(((struct StringOdd_OptionTuple2 const*)four_))).t1.value.Odd_))).t1.value))).t1.value.Odd_))).t1.some) goto next_2;
    milone_assert((n1_ == 1), 15, 6);
    milone_assert((str_compare(s2_, (struct String){.str = "two", .len = 3}) == 0), 16, 6);
    milone_assert((n3_ == 3), 17, 6);
    milone_assert((str_compare(s4_, (struct String){.str = "four", .len = 4}) == 0), 18, 6);
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
