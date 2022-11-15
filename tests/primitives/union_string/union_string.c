#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct MyUnion_;

struct String MiloneDerive_UnionString_union0String(struct MyUnion_ union_);

struct String MiloneDerive_UnionString_union0String(struct MyUnion_);

int main(int argc, char **argv);

enum MyUnion_Discriminant {
    MyUnion_UnitLike,
    MyUnion_CarryingInt,
    MyUnion_CarryingOther,
};

struct MyUnion_ {
    enum MyUnion_Discriminant discriminant;
    union {
        int32_t MyUnion_CarryingInt;
        char MyUnion_CarryingOther;
    };
};

struct String MiloneDerive_UnionString_union0String(struct MyUnion_ union_) {
    int32_t payload_;
    char payload_1;
    struct String match_;
    struct String call_;
    if ((union_.discriminant != MyUnion_UnitLike)) goto next_2;
    match_ = (struct String){.ptr = "MyUnion.UnitLike", .len = 16};
    goto end_match_1;
next_2:;
    if ((union_.discriminant != MyUnion_CarryingInt)) goto next_3;
    payload_ = union_.MyUnion_CarryingInt;
    call_ = string_of_int64(payload_);
    match_ = string_add(string_add((struct String){.ptr = "MyUnion.CarryingInt(", .len = 20}, call_), (struct String){.ptr = ")", .len = 1});
    goto end_match_1;
next_3:;
    if ((union_.discriminant != MyUnion_CarryingOther)) goto next_4;
    payload_1 = union_.MyUnion_CarryingOther;
    match_ = string_add(string_add((struct String){.ptr = "MyUnion.CarryingOther(", .len = 22}, (struct String){.ptr = "()", .len = 2}), (struct String){.ptr = ")", .len = 1});
    goto end_match_1;
next_4:;
    milone_exhaust_error("MiloneDerive.UnionString", 0, 0);
end_match_1:;
    return match_;
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    struct String call_1;
    struct MyUnion_ variant_;
    struct String call_2;
    struct MyUnion_ variant_1;
    struct String call_3;
    call_1 = MiloneDerive_UnionString_union0String((struct MyUnion_){.discriminant = MyUnion_UnitLike});
    if ((string_compare(call_1, (struct String){.ptr = "MyUnion.UnitLike", .len = 16}) != 0)) milone_assert_error("union_string/union_string.milone", 10, 2);
    variant_ = (struct MyUnion_){.discriminant = MyUnion_CarryingInt, .MyUnion_CarryingInt = 1};
    call_2 = MiloneDerive_UnionString_union0String(variant_);
    if ((string_compare(call_2, (struct String){.ptr = "MyUnion.CarryingInt(1)", .len = 22}) != 0)) milone_assert_error("union_string/union_string.milone", 11, 2);
    variant_1 = (struct MyUnion_){.discriminant = MyUnion_CarryingOther, .MyUnion_CarryingOther = 0};
    call_3 = MiloneDerive_UnionString_union0String(variant_1);
    if ((string_compare(call_3, (struct String){.ptr = "MyUnion.CarryingOther(())", .len = 25}) != 0)) milone_assert_error("union_string/union_string.milone", 14, 2);
    return 0;
}
