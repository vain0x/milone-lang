#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct MyList_;

struct MyListoption1_;

struct IntMyListoption1Tuple2_;

struct MyList_ union_newtype_rec_union_newtype_rec_main_myCons(int head_, struct MyList_ tail_);

int main(int argc, char** argv);

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
    struct IntMyListoption1Tuple2_ IntMyListoption1Tuple2_;
    struct MyListoption1_ variant_;
    void const* box_;
    struct MyList_ variant_1;
    variant_ = (struct MyListoption1_){.discriminant = Some_, .Some_ = tail_};
    IntMyListoption1Tuple2_ = (struct IntMyListoption1Tuple2_){.t0 = head_, .t1 = variant_};
    box_ = ((void const*)milone_region_alloc(1, sizeof(struct IntMyListoption1Tuple2_)));
    (*(((struct IntMyListoption1Tuple2_*)box_))) = IntMyListoption1Tuple2_;
    variant_1 = (struct MyList_){.discriminant = MyList_, .MyList_ = box_};
    return variant_1;
}

int main(int argc, char** argv) {
    milone_start(argc, argv);
    struct MyList_ first_;
    struct MyList_ second_;
    int value_;
    struct IntMyListoption1Tuple2_ IntMyListoption1Tuple2_1;
    void const* box_1;
    struct MyList_ variant_2;
    struct MyList_ call_;
    char match_;
    char match_1;
    IntMyListoption1Tuple2_1 = (struct IntMyListoption1Tuple2_){.t0 = 0, .t1 = (struct MyListoption1_){.discriminant = None_}};
    box_1 = ((void const*)milone_region_alloc(1, sizeof(struct IntMyListoption1Tuple2_)));
    (*(((struct IntMyListoption1Tuple2_*)box_1))) = IntMyListoption1Tuple2_1;
    variant_2 = (struct MyList_){.discriminant = MyList_, .MyList_ = box_1};
    first_ = variant_2;
    call_ = union_newtype_rec_union_newtype_rec_main_myCons(1, first_);
    second_ = call_;
    if (((*(((struct IntMyListoption1Tuple2_ const*)first_.MyList_))).t0 != 0)) goto next_2;
    if (((*(((struct IntMyListoption1Tuple2_ const*)first_.MyList_))).t1.discriminant != None_)) goto next_2;
    match_ = 0;
    goto end_match_1;
next_2:;
    milone_assert(false, (struct String){.ptr = "union_newtype_rec/union_newtype_rec.milone", .len = 42}, 14, 9);
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    if (((*(((struct IntMyListoption1Tuple2_ const*)second_.MyList_))).t1.discriminant != Some_)) goto next_5;
    value_ = (*(((struct IntMyListoption1Tuple2_ const*)(*(((struct IntMyListoption1Tuple2_ const*)second_.MyList_))).t1.Some_.MyList_))).t0;
    milone_assert((value_ == 0), (struct String){.ptr = "union_newtype_rec/union_newtype_rec.milone", .len = 42}, 17, 44);
    match_1 = 0;
    goto end_match_4;
next_5:;
    milone_assert(false, (struct String){.ptr = "union_newtype_rec/union_newtype_rec.milone", .len = 42}, 18, 9);
    match_1 = 0;
    goto end_match_4;
next_6:;
end_match_4:;
    return 0;
}
