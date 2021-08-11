#include "milone.h"

struct MyList_;

struct MyListOption_;

struct IntMyListOptionTuple2_;

struct MyList_ myCons_(int head_, struct MyList_ tail_);

int milone_main();

enum MyList_Discriminant {
    MyList_,
};

struct MyList_ {
    enum MyList_Discriminant discriminant;
    union {
        void const* MyList_;
    };
};

enum MyListOption_Discriminant {
    None_,
    Some_,
};

struct MyListOption_ {
    enum MyListOption_Discriminant discriminant;
    union {
        struct MyList_ Some_;
    };
};

struct IntMyListOptionTuple2_ {
    int t0;
    struct MyListOption_ t1;
};

struct MyList_ myCons_(int head_, struct MyList_ tail_) {
    struct MyListOption_ variant_ = (struct MyListOption_){.discriminant = Some_, .Some_ = tail_};
    struct IntMyListOptionTuple2_ IntMyListOptionTuple2_ = (struct IntMyListOptionTuple2_){.t0 = head_, .t1 = variant_};
    void const* box_ = milone_mem_alloc(1, sizeof(struct IntMyListOptionTuple2_));
    (*(((struct IntMyListOptionTuple2_*)box_))) = IntMyListOptionTuple2_;
    struct MyList_ variant_1 = (struct MyList_){.discriminant = MyList_, .MyList_ = box_};
    return variant_1;
}

int milone_main() {
    int value_;
    struct IntMyListOptionTuple2_ IntMyListOptionTuple2_1 = (struct IntMyListOptionTuple2_){.t0 = 0, .t1 = (struct MyListOption_){.discriminant = None_}};
    void const* box_1 = milone_mem_alloc(1, sizeof(struct IntMyListOptionTuple2_));
    (*(((struct IntMyListOptionTuple2_*)box_1))) = IntMyListOptionTuple2_1;
    struct MyList_ variant_2 = (struct MyList_){.discriminant = MyList_, .MyList_ = box_1};
    struct MyList_ first_ = variant_2;
    struct MyList_ call_ = myCons_(1, first_);
    struct MyList_ second_ = call_;
    char match_;
    if (((*(((struct IntMyListOptionTuple2_ const*)first_.MyList_))).t0 != 0)) goto next_2;
    if (((*(((struct IntMyListOptionTuple2_ const*)first_.MyList_))).t1.discriminant != None_)) goto next_2;
    match_ = 0;
    goto end_match_1;
next_2:;
    milone_assert(false, 14, 9);
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    char match_1;
    if (((*(((struct IntMyListOptionTuple2_ const*)second_.MyList_))).t1.discriminant != Some_)) goto next_5;
    value_ = (*(((struct IntMyListOptionTuple2_ const*)(*(((struct IntMyListOptionTuple2_ const*)second_.MyList_))).t1.Some_.MyList_))).t0;
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
