#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct StringCons;

struct StringStringListTuple2_;

struct StringStringTuple2_;

struct Int32Int32Tuple2_;

struct StringCons;

struct StringStringListTuple2_ ty_var_ty_var_StringStringStringListTuple2Fun1_useTyVarInBody(struct String x_1);

int32_t ty_var_ty_var_StringStringTuple2Int32Fun1_pair(struct StringStringTuple2_ arg_);

int32_t ty_var_ty_var_Int32Int32Tuple2Int32Fun1_pair(struct Int32Int32Tuple2_ arg_1);

char ty_var_ty_var_useStringIndexWithoutAscription(struct String x_);

int main(int argc, char **argv);

struct StringStringListTuple2_ {
    struct String t0;
    struct StringCons const *t1;
};

struct StringStringTuple2_ {
    struct String t0;
    struct String t1;
};

struct Int32Int32Tuple2_ {
    int32_t t0;
    int32_t t1;
};

struct StringCons {
    struct String head;
    struct StringCons const *tail;
};

struct StringStringListTuple2_ ty_var_ty_var_StringStringStringListTuple2Fun1_useTyVarInBody(struct String x_1) {
    struct StringCons const *xs_;
    struct StringStringListTuple2_ StringStringListTuple2_;
    xs_ = NULL;
    StringStringListTuple2_ = (struct StringStringListTuple2_){.t0 = x_1, .t1 = xs_};
    return StringStringListTuple2_;
}

int32_t ty_var_ty_var_StringStringTuple2Int32Fun1_pair(struct StringStringTuple2_ arg_) {
    return 2;
}

int32_t ty_var_ty_var_Int32Int32Tuple2Int32Fun1_pair(struct Int32Int32Tuple2_ arg_1) {
    return 2;
}

char ty_var_ty_var_useStringIndexWithoutAscription(struct String x_) {
    struct StringStringTuple2_ StringStringTuple2_;
    int32_t call_;
    StringStringTuple2_ = (struct StringStringTuple2_){.t0 = x_, .t1 = (struct String){.ptr = "", .len = 0}};
    call_ = ty_var_ty_var_StringStringTuple2Int32Fun1_pair(StringStringTuple2_);
    return x_.ptr[0];
}

int main(int argc, char **argv) {
    milone_start(argc, argv);
    struct String s_;
    struct Int32Int32Tuple2_ Int32Int32Tuple2_;
    int32_t call_1;
    struct StringStringTuple2_ StringStringTuple2_1;
    int32_t call_2;
    char call_3;
    char match_;
    struct StringStringListTuple2_ call_4;
    Int32Int32Tuple2_ = (struct Int32Int32Tuple2_){.t0 = 0, .t1 = 0};
    call_1 = ty_var_ty_var_Int32Int32Tuple2Int32Fun1_pair(Int32Int32Tuple2_);
    if ((call_1 != 2)) milone_assert_error("ty_var/ty_var.milone", 18, 2);
    StringStringTuple2_1 = (struct StringStringTuple2_){.t0 = (struct String){.ptr = "", .len = 0}, .t1 = (struct String){.ptr = "", .len = 0}};
    call_2 = ty_var_ty_var_StringStringTuple2Int32Fun1_pair(StringStringTuple2_1);
    if ((call_2 != 2)) milone_assert_error("ty_var/ty_var.milone", 19, 2);
    call_3 = ty_var_ty_var_useStringIndexWithoutAscription((struct String){.ptr = "a", .len = 1});
    if ((call_3 != 'a')) milone_assert_error("ty_var/ty_var.milone", 21, 2);
    call_4 = ty_var_ty_var_StringStringStringListTuple2Fun1_useTyVarInBody((struct String){.ptr = "b", .len = 1});
    if ((!(call_4.t1))) goto next_2;
    s_ = call_4.t1->head;
    if ((s_.ptr[0] != 'b')) milone_assert_error("ty_var/ty_var.milone", 24, 17);
    match_ = 0;
    goto end_match_1;
next_2:;
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    return 0;
}
