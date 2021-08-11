#include "milone.h"

struct Status_;

struct Limit_;

struct IntStringTuple2_;

struct ApiResponse_;

int milone_main();

enum Status_Discriminant {
    Ok_1,
    Err_,
};

struct Status_ {
    enum Status_Discriminant discriminant;
    union {
        struct String Err_;
    };
};

enum Limit_Discriminant {
    LimitVal_,
    LimitDiv_,
};

struct Limit_ {
    enum Limit_Discriminant discriminant;
    union {
        int LimitVal_;
    };
};

struct IntStringTuple2_ {
    int t0;
    struct String t1;
};

enum ApiResponse_Discriminant {
    ARJson_,
    ARError_,
    ARCancel_,
};

struct ApiResponse_ {
    enum ApiResponse_Discriminant discriminant;
    union {
        struct String ARJson_;
        struct IntStringTuple2_ ARError_;
    };
};

int milone_main() {
    struct String statusText_;
    int statusCode_;
    int x_;
    struct String e_;
    struct Status_ ok_ = (struct Status_){.discriminant = Ok_1};
    struct Status_ variant_ = (struct Status_){.discriminant = Err_, .Err_ = (struct String){.str = "No such file or directory.", .len = 26}};
    struct Status_ err1_ = variant_;
    struct Status_ variant_1 = (struct Status_){.discriminant = Err_, .Err_ = (struct String){.str = "Access denied.", .len = 14}};
    struct Status_ err2_ = variant_1;
    char match_;
    if ((err1_.discriminant != Ok_1)) goto next_2;
    milone_assert(false, 28, 12);
    match_ = 0;
    goto end_match_1;
next_2:;
    if ((err1_.discriminant != Err_)) goto next_3;
    e_ = err1_.Err_;
    milone_assert((str_compare(e_, (struct String){.str = "No such file or directory.", .len = 26}) == 0), 29, 15);
    match_ = 0;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    char match_1;
    struct Limit_ variant_2 = (struct Limit_){.discriminant = LimitVal_, .LimitVal_ = 1};
    if ((variant_2.discriminant != LimitVal_)) goto next_5;
    x_ = variant_2.LimitVal_;
    milone_assert((x_ == 1), 33, 20);
    match_1 = 0;
    goto end_match_4;
next_5:;
    if ((variant_2.discriminant != LimitDiv_)) goto next_6;
    exit(2);
next_6:;
    exit(1);
end_match_4:;
    char switch_;
    switch ((struct ApiResponse_){.discriminant = ARCancel_}.discriminant) {
        case ARCancel_:
            goto clause_8;

        default:
            goto clause_9;
    }
clause_8:;
    switch_ = 0;
    goto switch_next_7;
clause_9:;
    milone_assert(false, 39, 11);
    switch_ = 0;
    goto switch_next_7;
switch_next_7:;
    char match_2;
    struct IntStringTuple2_ IntStringTuple2_ = (struct IntStringTuple2_){.t0 = 404, .t1 = (struct String){.str = "Not Found", .len = 9}};
    struct ApiResponse_ variant_3 = (struct ApiResponse_){.discriminant = ARError_, .ARError_ = IntStringTuple2_};
    if ((variant_3.discriminant != ARError_)) goto next_11;
    statusCode_ = variant_3.ARError_.t0;
    statusText_ = variant_3.ARError_.t1;
    bool if_;
    if ((statusCode_ == 404)) {
        goto then_14;
    } else {
        goto else_15;
    }
then_14:;
    if_ = (str_compare(statusText_, (struct String){.str = "Not Found", .len = 9}) == 0);
    goto if_next_13;
else_15:;
    if_ = false;
    goto if_next_13;
if_next_13:;
    milone_assert(if_, 43, 42);
    match_2 = 0;
    goto end_match_10;
next_11:;
    milone_assert(false, 44, 11);
    match_2 = 0;
    goto end_match_10;
next_12:;
end_match_10:;
    struct Status_ ok_1 = (struct Status_){.discriminant = Ok_1};
    char okOk_ = 0;
    struct Status_ statusOk_ = (struct Status_){.discriminant = Ok_1};
    char switch_1;
    switch ((struct Status_){.discriminant = Ok_1}.discriminant) {
        case Ok_1:
            goto clause_17;

        case Err_:
            goto clause_18;

        default:
            exit(1);
    }
clause_17:;
    switch_1 = 0;
    goto switch_next_16;
clause_18:;
    milone_assert(false, 55, 20);
    switch_1 = 0;
    goto switch_next_16;
switch_next_16:;
    char okWrapper_ = 0;
    return 0;
}
