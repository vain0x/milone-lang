#include "milone.h"

enum Even_Discriminant;

struct Even_;

struct Even_Option;

struct IntEven_OptionTuple2;

enum Odd_Discriminant;

struct Odd_;

struct Odd_Option;

struct StringOdd_OptionTuple2;

int milone_main();

enum Even_Discriminant {
    Even_,
};

struct Even_ {
    enum Even_Discriminant discriminant;
    union {
        void const* Even_;
    };
};

struct Even_Option {
    bool some;
    struct Even_ value;
};

struct IntEven_OptionTuple2 {
    int t0;
    struct Even_Option t1;
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
    struct IntEven_OptionTuple2 tuple_ = (struct IntEven_OptionTuple2){.t0 = 1, .t1 = ((struct Even_Option){})};
    void const* box_ = milone_mem_alloc(1, sizeof(struct IntEven_OptionTuple2));
    (*(((struct IntEven_OptionTuple2*)box_))) = tuple_;
    struct Odd_ variant_ = (struct Odd_){.discriminant = Odd_, .Odd_ = box_};
    struct Odd_ one_ = variant_;
    struct Odd_Option some_ = (struct Odd_Option){.some = true, .value = one_};
    struct StringOdd_OptionTuple2 tuple_1 = (struct StringOdd_OptionTuple2){.t0 = (struct String){.str = "two", .len = 3}, .t1 = some_};
    void const* box_1 = milone_mem_alloc(1, sizeof(struct StringOdd_OptionTuple2));
    (*(((struct StringOdd_OptionTuple2*)box_1))) = tuple_1;
    struct Even_ variant_1 = (struct Even_){.discriminant = Even_, .Even_ = box_1};
    struct Even_ two_ = variant_1;
    struct Even_Option some_1 = (struct Even_Option){.some = true, .value = two_};
    struct IntEven_OptionTuple2 tuple_2 = (struct IntEven_OptionTuple2){.t0 = 3, .t1 = some_1};
    void const* box_2 = milone_mem_alloc(1, sizeof(struct IntEven_OptionTuple2));
    (*(((struct IntEven_OptionTuple2*)box_2))) = tuple_2;
    struct Odd_ variant_2 = (struct Odd_){.discriminant = Odd_, .Odd_ = box_2};
    struct Odd_ three_ = variant_2;
    struct Odd_Option some_2 = (struct Odd_Option){.some = true, .value = three_};
    struct StringOdd_OptionTuple2 tuple_3 = (struct StringOdd_OptionTuple2){.t0 = (struct String){.str = "four", .len = 4}, .t1 = some_2};
    void const* box_3 = milone_mem_alloc(1, sizeof(struct StringOdd_OptionTuple2));
    (*(((struct StringOdd_OptionTuple2*)box_3))) = tuple_3;
    struct Even_ variant_3 = (struct Even_){.discriminant = Even_, .Even_ = box_3};
    struct Even_ four_ = variant_3;
    int match_;
    struct String s4_ = (*(((struct StringOdd_OptionTuple2 const*)four_.Even_))).t0;
    if ((!((*(((struct StringOdd_OptionTuple2 const*)four_.Even_))).t1.some))) goto next_2;
    int n3_ = (*(((struct IntEven_OptionTuple2 const*)(*(((struct StringOdd_OptionTuple2 const*)four_.Even_))).t1.value.Odd_))).t0;
    if ((!((*(((struct IntEven_OptionTuple2 const*)(*(((struct StringOdd_OptionTuple2 const*)four_.Even_))).t1.value.Odd_))).t1.some))) goto next_2;
    struct String s2_ = (*(((struct StringOdd_OptionTuple2 const*)(*(((struct IntEven_OptionTuple2 const*)(*(((struct StringOdd_OptionTuple2 const*)four_.Even_))).t1.value.Odd_))).t1.value.Even_))).t0;
    if ((!((*(((struct StringOdd_OptionTuple2 const*)(*(((struct IntEven_OptionTuple2 const*)(*(((struct StringOdd_OptionTuple2 const*)four_.Even_))).t1.value.Odd_))).t1.value.Even_))).t1.some))) goto next_2;
    int n1_ = (*(((struct IntEven_OptionTuple2 const*)(*(((struct StringOdd_OptionTuple2 const*)(*(((struct IntEven_OptionTuple2 const*)(*(((struct StringOdd_OptionTuple2 const*)four_.Even_))).t1.value.Odd_))).t1.value.Even_))).t1.value.Odd_))).t0;
    if ((*(((struct IntEven_OptionTuple2 const*)(*(((struct StringOdd_OptionTuple2 const*)(*(((struct IntEven_OptionTuple2 const*)(*(((struct StringOdd_OptionTuple2 const*)four_.Even_))).t1.value.Odd_))).t1.value.Even_))).t1.value.Odd_))).t1.some) goto next_2;
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
