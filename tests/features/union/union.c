#include <stdio.h>
#include <stdlib.h>
#include <milone.h>

struct Status_;

struct Int32Cons;

struct Limit_;

struct Int32StringTuple2_;

struct ApiResponse_;

struct Int32Cons;

_Noreturn void MiloneCore_Prelude_exit(int32_t);

int32_t MiloneCore_List_Int32ListInt32Fun1_length(struct Int32Cons const *);

int main(int argc, char **argv);

enum Status_Discriminant {
    Status_Ok,
    Status_Err,
};

struct Status_ {
    enum Status_Discriminant discriminant;
    union {
        struct String Status_Err;
    };
};

enum Limit_Discriminant {
    Limit_LimitVal,
    Limit_LimitDiv,
};

struct Limit_ {
    enum Limit_Discriminant discriminant;
    union {
        int32_t Limit_LimitVal;
    };
};

struct Int32StringTuple2_ {
    int32_t t0;
    struct String t1;
};

enum ApiResponse_Discriminant {
    ApiResponse_ARJson,
    ApiResponse_ARError,
    ApiResponse_ARCancel,
};

struct ApiResponse_ {
    enum ApiResponse_Discriminant discriminant;
    union {
        struct String ApiResponse_ARJson;
        struct Int32StringTuple2_ ApiResponse_ARError;
    };
};

struct Int32Cons {
    int32_t head;
    struct Int32Cons const *tail;
};

int main(int argc, char **argv) {
    milone_start(argc, argv);
    struct Status_ ok_;
    struct Status_ err1_;
    struct Status_ err2_;
    struct String e_;
    int32_t x_;
    int32_t statusCode_;
    struct String statusText_;
    struct Status_ ok_1;
    int32_t okOk_;
    struct Status_ statusOk_;
    int32_t okWrapper_;
    int32_t yes_;
    struct Int32Cons const *results_;
    struct Status_ variant_;
    struct Status_ variant_1;
    char match_;
    char match_1;
    struct Limit_ variant_2;
    char switch_;
    char match_2;
    struct Int32StringTuple2_ Int32StringTuple2_;
    struct ApiResponse_ variant_3;
    bool if_;
    char switch_1;
    char switch_2;
    struct Int32Cons const *list_;
    struct Int32Cons const *list_1;
    struct Int32Cons const *list_2;
    int32_t call_;
    ok_ = (struct Status_){.discriminant = Status_Ok};
    variant_ = (struct Status_){.discriminant = Status_Err, .Status_Err = (struct String){.ptr = "No such file or directory.", .len = 26}};
    err1_ = variant_;
    variant_1 = (struct Status_){.discriminant = Status_Err, .Status_Err = (struct String){.ptr = "Access denied.", .len = 14}};
    err2_ = variant_1;
    if ((err1_.discriminant != Status_Ok)) goto next_6;
    if (true) milone_assert_error("union/union.milone", 34, 12);
    match_ = 0;
    goto end_match_5;
next_6:;
    if ((err1_.discriminant != Status_Err)) goto next_7;
    e_ = err1_.Status_Err;
    if ((string_compare(e_, (struct String){.ptr = "No such file or directory.", .len = 26}) != 0)) milone_assert_error("union/union.milone", 35, 15);
    match_ = 0;
    goto end_match_5;
next_7:;
    milone_exhaust_error("union/union.milone", 33, 4);
end_match_5:;
    variant_2 = (struct Limit_){.discriminant = Limit_LimitVal, .Limit_LimitVal = 1};
    if ((variant_2.discriminant != Limit_LimitVal)) goto next_9;
    x_ = variant_2.Limit_LimitVal;
    if ((x_ != 1)) milone_assert_error("union/union.milone", 39, 20);
    match_1 = 0;
    goto end_match_8;
next_9:;
    if ((variant_2.discriminant != Limit_LimitDiv)) goto next_10;
    MiloneCore_Prelude_exit(2);
    milone_never_error("union/union.milone", 40, 22);
next_10:;
    milone_exhaust_error("union/union.milone", 38, 4);
end_match_8:;
    switch ((struct ApiResponse_){.discriminant = ApiResponse_ARCancel}.discriminant) {
        case ApiResponse_ARCancel:
            goto clause_12;

        default:
            goto clause_13;
    }
clause_12:;
    switch_ = 0;
    goto switch_next_11;
clause_13:;
    if (true) milone_assert_error("union/union.milone", 45, 11);
    switch_ = 0;
    goto switch_next_11;
switch_next_11:;
    Int32StringTuple2_ = (struct Int32StringTuple2_){.t0 = 404, .t1 = (struct String){.ptr = "Not Found", .len = 9}};
    variant_3 = (struct ApiResponse_){.discriminant = ApiResponse_ARError, .ApiResponse_ARError = Int32StringTuple2_};
    if ((variant_3.discriminant != ApiResponse_ARError)) goto next_15;
    statusCode_ = variant_3.ApiResponse_ARError.t0;
    statusText_ = variant_3.ApiResponse_ARError.t1;
    if ((statusCode_ == 404)) {
        goto then_18;
    } else {
        goto else_19;
    }
then_18:;
    if_ = (string_compare(statusText_, (struct String){.ptr = "Not Found", .len = 9}) == 0);
    goto if_next_17;
else_19:;
    if_ = false;
    goto if_next_17;
if_next_17:;
    if ((!(if_))) milone_assert_error("union/union.milone", 49, 42);
    match_2 = 0;
    goto end_match_14;
next_15:;
    if (true) milone_assert_error("union/union.milone", 50, 11);
    match_2 = 0;
    goto end_match_14;
next_16:;
end_match_14:;
    ok_1 = (struct Status_){.discriminant = Status_Ok};
    okOk_ = 0;
    statusOk_ = (struct Status_){.discriminant = Status_Ok};
    switch ((struct Status_){.discriminant = Status_Ok}.discriminant) {
        case Status_Ok:
            goto clause_21;

        case Status_Err:
            goto clause_22;

        default:
            milone_exhaust_error("union/union.milone", 59, 2);
    }
clause_21:;
    switch_1 = 0;
    goto switch_next_20;
clause_22:;
    if (true) milone_assert_error("union/union.milone", 61, 20);
    switch_1 = 0;
    goto switch_next_20;
switch_next_20:;
    okWrapper_ = 0;
    yes_ = 0;
    switch (yes_) {
        case 0:
            goto clause_24;

        case 1:
        case 2:
            goto clause_25;

        default:
            milone_exhaust_error("union/union.milone", 67, 2);
    }
clause_24:;
    switch_2 = 0;
    goto switch_next_23;
clause_25:;
    if (true) milone_assert_error("union/union.milone", 70, 33);
    switch_2 = 0;
    goto switch_next_23;
switch_next_23:;
    list_2 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_2))) = (struct Int32Cons){.head = 2, .tail = NULL};
    list_1 = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_1))) = (struct Int32Cons){.head = 1, .tail = list_2};
    list_ = ((struct Int32Cons const *)milone_region_alloc(1, sizeof(struct Int32Cons)));
    (*(((struct Int32Cons *)list_))) = (struct Int32Cons){.head = 0, .tail = list_1};
    results_ = list_;
    call_ = MiloneCore_List_Int32ListInt32Fun1_length(results_);
    if ((call_ != 3)) milone_assert_error("union/union.milone", 73, 2);
    return 0;
}
