#include "milone.h"

struct MyList_;

struct MyListoption1_;

struct IntMyListoption1Tuple2_;

struct MyList_ union_newtype_rec_union_newtype_rec_main_myCons(int head_, struct MyList_ tail_);

int milone_main(void);

enum MyList_Discriminant {
    MyList_,
};

struct MyList_ {
    enum MyList_Discriminant discriminant;
    union {
        void const* MyList_;
    };
};

enum MyListoption1_Discriminant {
    None_,
    Some_,
};

struct MyListoption1_ {
    enum MyListoption1_Discriminant discriminant;
    union {
        struct MyList_ Some_;
    };
};

struct IntMyListoption1Tuple2_ {
    int t0;
    struct MyListoption1_ t1;
};

struct MyList_ union_newtype_rec_union_newtype_rec_main_myCons(int head_, struct MyList_ tail_) {
    struct MyListoption1_ variant_ = (struct MyListoption1_){.discriminant = Some_, .Some_ = tail_};
    struct IntMyListoption1Tuple2_ IntMyListoption1Tuple2_ = (struct IntMyListoption1Tuple2_){.t0 = head_, .t1 = variant_};
    void const* box_ = milone_mem_alloc(1, sizeof(struct IntMyListoption1Tuple2_));
    (*(((struct IntMyListoption1Tuple2_*)box_))) = IntMyListoption1Tuple2_;
    struct MyList_ variant_1 = (struct MyList_){.discriminant = MyList_, .MyList_ = box_};
    return variant_1;
}

int milone_main(void) {
    int value_;
    struct IntMyListoption1Tuple2_ IntMyListoption1Tuple2_1 = (struct IntMyListoption1Tuple2_){.t0 = 0, .t1 = (struct MyListoption1_){.discriminant = None_}};
    void const* box_1 = milone_mem_alloc(1, sizeof(struct IntMyListoption1Tuple2_));
    (*(((struct IntMyListoption1Tuple2_*)box_1))) = IntMyListoption1Tuple2_1;
    struct MyList_ variant_2 = (struct MyList_){.discriminant = MyList_, .MyList_ = box_1};
    struct MyList_ first_ = variant_2;
    struct MyList_ call_ = union_newtype_rec_union_newtype_rec_main_myCons(1, first_);
    struct MyList_ second_ = call_;
    char match_;
    if (((*(((struct IntMyListoption1Tuple2_ const*)first_.MyList_))).t0 != 0)) goto next_2;
    if (((*(((struct IntMyListoption1Tuple2_ const*)first_.MyList_))).t1.discriminant != None_)) goto next_2;
    match_ = 0;
    goto end_match_1;
next_2:;
    milone_assert(false, 14, 9);
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    char match_1;
    if (((*(((struct IntMyListoption1Tuple2_ const*)second_.MyList_))).t1.discriminant != Some_)) goto next_5;
    value_ = (*(((struct IntMyListoption1Tuple2_ const*)(*(((struct IntMyListoption1Tuple2_ const*)second_.MyList_))).t1.Some_.MyList_))).t0;
    milone_assert((value_ == 0), 17, 44);
    match_1 = 0;
    goto end_match_4;
next_5:;
    milone_assert(false, 18, 9);
    match_1 = 0;
    goto end_match_4;
next_6:;
end_match_4:;
    return 0;
}
