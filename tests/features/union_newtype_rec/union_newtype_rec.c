#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct MyList_;

struct MyListoption1_;

struct Int32MyListoption1Tuple2_;

struct MyList_ union_newtype_rec_union_newtype_rec_main_myCons(int32_t head_, struct MyList_ tail_);

int main(int argc, char **argv);

enum MyList_Discriminant {
    MyList_MyList,
};

struct MyList_ {
    enum MyList_Discriminant discriminant;
    union {
        void const *MyList_MyList;
    };
};

enum MyListoption1_Discriminant {
    MyListoption1_None,
    MyListoption1_Some,
};

struct MyListoption1_ {
    enum MyListoption1_Discriminant discriminant;
    union {
        struct MyList_ MyListoption1_Some;
    };
};

struct Int32MyListoption1Tuple2_ {
    int32_t t0;
    struct MyListoption1_ t1;
};

struct MyList_ union_newtype_rec_union_newtype_rec_main_myCons(int32_t head_, struct MyList_ tail_) {
    struct Int32MyListoption1Tuple2_ Int32MyListoption1Tuple2_;
    struct MyListoption1_ variant_;
    void const *box_;
    struct MyList_ variant_1;
    variant_ = (struct MyListoption1_){.discriminant = MyListoption1_Some, .MyListoption1_Some = tail_};
    Int32MyListoption1Tuple2_ = (struct Int32MyListoption1Tuple2_){.t0 = head_, .t1 = variant_};
    box_ = ((void const *)milone_region_alloc(1, sizeof(struct Int32MyListoption1Tuple2_)));
    (*(((struct Int32MyListoption1Tuple2_ *)box_))) = Int32MyListoption1Tuple2_;
    variant_1 = (struct MyList_){.discriminant = MyList_MyList, .MyList_MyList = box_};
    return variant_1;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    struct MyList_ first_;
    struct MyList_ second_;
    int32_t value_;
    struct Int32MyListoption1Tuple2_ Int32MyListoption1Tuple2_1;
    void const *box_1;
    struct MyList_ variant_2;
    struct MyList_ call_;
    char match_;
    char match_1;
    Int32MyListoption1Tuple2_1 = (struct Int32MyListoption1Tuple2_){.t0 = 0, .t1 = (struct MyListoption1_){.discriminant = MyListoption1_None}};
    box_1 = ((void const *)milone_region_alloc(1, sizeof(struct Int32MyListoption1Tuple2_)));
    (*(((struct Int32MyListoption1Tuple2_ *)box_1))) = Int32MyListoption1Tuple2_1;
    variant_2 = (struct MyList_){.discriminant = MyList_MyList, .MyList_MyList = box_1};
    first_ = variant_2;
    call_ = union_newtype_rec_union_newtype_rec_main_myCons(1, first_);
    second_ = call_;
    if (((*(((struct Int32MyListoption1Tuple2_ const *)first_.MyList_MyList))).t0 != 0)) goto next_2;
    if (((*(((struct Int32MyListoption1Tuple2_ const *)first_.MyList_MyList))).t1.discriminant != MyListoption1_None)) goto next_2;
    match_ = 0;
    goto end_match_1;
next_2:;
    if (true) milone_assert_error("union_newtype_rec/union_newtype_rec.milone", 14, 9);
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    if (((*(((struct Int32MyListoption1Tuple2_ const *)second_.MyList_MyList))).t1.discriminant != MyListoption1_Some)) goto next_5;
    value_ = (*(((struct Int32MyListoption1Tuple2_ const *)(*(((struct Int32MyListoption1Tuple2_ const *)second_.MyList_MyList))).t1.MyListoption1_Some.MyList_MyList))).t0;
    if ((value_ != 0)) milone_assert_error("union_newtype_rec/union_newtype_rec.milone", 17, 44);
    match_1 = 0;
    goto end_match_4;
next_5:;
    if (true) milone_assert_error("union_newtype_rec/union_newtype_rec.milone", 18, 9);
    match_1 = 0;
    goto end_match_4;
next_6:;
end_match_4:;
    return 0;
}
