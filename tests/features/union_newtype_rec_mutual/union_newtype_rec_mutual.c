#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Odd_;

struct Oddoption1_;

struct StringOddoption1Tuple2_;

struct StringOddoption1Tuple2option1_;

struct Int32StringOddoption1Tuple2option1Tuple2_;

int main(int argc, char **argv);

enum Odd_Discriminant {
    Odd_,
};

struct Odd_ {
    enum Odd_Discriminant discriminant;
    union {
        void const *Odd_;
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

struct Int32StringOddoption1Tuple2option1Tuple2_ {
    int32_t t0;
    struct StringOddoption1Tuple2option1_ t1;
};

int main(int argc, char **argv) {
    milone_start(argc, argv);
    struct Odd_ one_;
    struct StringOddoption1Tuple2_ two_;
    struct Odd_ three_;
    struct StringOddoption1Tuple2_ four_;
    struct String s4_;
    int32_t n3_;
    struct String s2_;
    int32_t n1_;
    struct Int32StringOddoption1Tuple2option1Tuple2_ Int32StringOddoption1Tuple2option1Tuple2_;
    void const *box_;
    struct Odd_ variant_;
    struct StringOddoption1Tuple2_ StringOddoption1Tuple2_;
    struct Oddoption1_ variant_1;
    struct Int32StringOddoption1Tuple2option1Tuple2_ Int32StringOddoption1Tuple2option1Tuple2_1;
    struct StringOddoption1Tuple2option1_ variant_2;
    void const *box_1;
    struct Odd_ variant_3;
    struct StringOddoption1Tuple2_ StringOddoption1Tuple2_1;
    struct Oddoption1_ variant_4;
    char match_;
    Int32StringOddoption1Tuple2option1Tuple2_ = (struct Int32StringOddoption1Tuple2option1Tuple2_){.t0 = 1, .t1 = (struct StringOddoption1Tuple2option1_){.discriminant = None_2}};
    box_ = ((void const *)milone_region_alloc(1, sizeof(struct Int32StringOddoption1Tuple2option1Tuple2_)));
    (*(((struct Int32StringOddoption1Tuple2option1Tuple2_ *)box_))) = Int32StringOddoption1Tuple2option1Tuple2_;
    variant_ = (struct Odd_){.discriminant = Odd_, .Odd_ = box_};
    one_ = variant_;
    variant_1 = (struct Oddoption1_){.discriminant = Some_1, .Some_1 = one_};
    StringOddoption1Tuple2_ = (struct StringOddoption1Tuple2_){.t0 = (struct String){.ptr = "two", .len = 3}, .t1 = variant_1};
    two_ = StringOddoption1Tuple2_;
    variant_2 = (struct StringOddoption1Tuple2option1_){.discriminant = Some_2, .Some_2 = two_};
    Int32StringOddoption1Tuple2option1Tuple2_1 = (struct Int32StringOddoption1Tuple2option1Tuple2_){.t0 = 3, .t1 = variant_2};
    box_1 = ((void const *)milone_region_alloc(1, sizeof(struct Int32StringOddoption1Tuple2option1Tuple2_)));
    (*(((struct Int32StringOddoption1Tuple2option1Tuple2_ *)box_1))) = Int32StringOddoption1Tuple2option1Tuple2_1;
    variant_3 = (struct Odd_){.discriminant = Odd_, .Odd_ = box_1};
    three_ = variant_3;
    variant_4 = (struct Oddoption1_){.discriminant = Some_1, .Some_1 = three_};
    StringOddoption1Tuple2_1 = (struct StringOddoption1Tuple2_){.t0 = (struct String){.ptr = "four", .len = 4}, .t1 = variant_4};
    four_ = StringOddoption1Tuple2_1;
    s4_ = four_.t0;
    if ((four_.t1.discriminant != Some_1)) goto next_2;
    n3_ = (*(((struct Int32StringOddoption1Tuple2option1Tuple2_ const *)four_.t1.Some_1.Odd_))).t0;
    if (((*(((struct Int32StringOddoption1Tuple2option1Tuple2_ const *)four_.t1.Some_1.Odd_))).t1.discriminant != Some_2)) goto next_2;
    s2_ = (*(((struct Int32StringOddoption1Tuple2option1Tuple2_ const *)four_.t1.Some_1.Odd_))).t1.Some_2.t0;
    if (((*(((struct Int32StringOddoption1Tuple2option1Tuple2_ const *)four_.t1.Some_1.Odd_))).t1.Some_2.t1.discriminant != Some_1)) goto next_2;
    n1_ = (*(((struct Int32StringOddoption1Tuple2option1Tuple2_ const *)(*(((struct Int32StringOddoption1Tuple2option1Tuple2_ const *)four_.t1.Some_1.Odd_))).t1.Some_2.t1.Some_1.Odd_))).t0;
    if (((*(((struct Int32StringOddoption1Tuple2option1Tuple2_ const *)(*(((struct Int32StringOddoption1Tuple2option1Tuple2_ const *)four_.t1.Some_1.Odd_))).t1.Some_2.t1.Some_1.Odd_))).t1.discriminant != None_2)) goto next_2;
    if ((n1_ != 1)) milone_assert_error("union_newtype_rec_mutual/union_newtype_rec_mutual.milone", 15, 4);
    if ((string_compare(s2_, (struct String){.ptr = "two", .len = 3}) != 0)) milone_assert_error("union_newtype_rec_mutual/union_newtype_rec_mutual.milone", 16, 4);
    if ((n3_ != 3)) milone_assert_error("union_newtype_rec_mutual/union_newtype_rec_mutual.milone", 17, 4);
    if ((string_compare(s4_, (struct String){.ptr = "four", .len = 4}) != 0)) milone_assert_error("union_newtype_rec_mutual/union_newtype_rec_mutual.milone", 18, 4);
    match_ = 0;
    goto end_match_1;
next_2:;
    if (true) milone_assert_error("union_newtype_rec_mutual/union_newtype_rec_mutual.milone", 20, 9);
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    return 0;
}
