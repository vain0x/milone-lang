#include "milone.h"

enum Status_Tag;

struct Status_;

enum Limit_Tag;

struct Limit_;

struct IntStringTuple2;

enum ApiResponse_Tag;

struct ApiResponse_;

enum Ok_Tag;

struct Ok_;

enum OkWrapper_Tag;

struct OkWrapper_;

int main();

enum Status_Tag {
    Ok_1,
    Err_,
};

struct Status_ {
    enum Status_Tag tag;
    union {
        struct String Err_;
    };
};

enum Limit_Tag {
    LimitVal_,
    LimitDiv_,
};

struct Limit_ {
    enum Limit_Tag tag;
    union {
        int LimitVal_;
    };
};

struct IntStringTuple2 {
    int t0;
    struct String t1;
};

enum ApiResponse_Tag {
    ARJson_,
    ARError_,
    ARCancel_,
};

struct ApiResponse_ {
    enum ApiResponse_Tag tag;
    union {
        struct String ARJson_;
        struct IntStringTuple2 ARError_;
    };
};

enum Ok_Tag {
    Ok_,
};

struct Ok_ {
    enum Ok_Tag tag;
};

enum OkWrapper_Tag {
    T_,
};

struct OkWrapper_ {
    enum OkWrapper_Tag tag;
    union {
        struct Ok_ T_;
    };
};

int main() {
    struct Status_ ok_ = (struct Status_){.tag = Ok_1};
    struct Status_ variant_ = (struct Status_){.tag = Err_, .Err_ = (struct String){.str = "No such file or directory.", .len = 26}};
    struct Status_ err1_ = variant_;
    struct Status_ variant_1 = (struct Status_){.tag = Err_, .Err_ = (struct String){.str = "Access denied.", .len = 14}};
    struct Status_ err2_ = variant_1;
    int match_;
    if ((err1_.tag != Ok_1)) goto next_2;
    milone_assert(false, 28, 12);
    match_ = 0;
    goto end_match_1;
next_2:;
    if ((err1_.tag != Err_)) goto next_3;
    struct String e_ = err1_.Err_;
    milone_assert((str_cmp(e_, (struct String){.str = "No such file or directory.", .len = 26}) == 0), 29, 15);
    match_ = 0;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    int match_1;
    struct Limit_ variant_2 = (struct Limit_){.tag = LimitVal_, .LimitVal_ = 1};
    if ((variant_2.tag != LimitVal_)) goto next_5;
    int x_ = variant_2.LimitVal_;
    milone_assert((x_ == 1), 33, 20);
    match_1 = 0;
    goto end_match_4;
next_5:;
    if ((variant_2.tag != LimitDiv_)) goto next_6;
    exit(2);
    match_1 = 0;
    goto end_match_4;
next_6:;
    exit(1);
end_match_4:;
    int switch_;
    switch ((struct ApiResponse_){.tag = ARCancel_}.tag) {
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
    int match_2;
    struct IntStringTuple2 tuple_;
    tuple_.t0 = 404;
    tuple_.t1 = (struct String){.str = "Not Found", .len = 9};
    struct ApiResponse_ variant_3 = (struct ApiResponse_){.tag = ARError_, .ARError_ = tuple_};
    if ((variant_3.tag != ARError_)) goto next_11;
    int statusCode_ = variant_3.ARError_.t0;
    struct String statusText_ = variant_3.ARError_.t1;
    bool if_;
    if ((statusCode_ == 404)) {
        goto then_14;
    } else {
        goto else_15;
    }
then_14:;
    if_ = (str_cmp(statusText_, (struct String){.str = "Not Found", .len = 9}) == 0);
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
    struct Status_ ok_1 = (struct Status_){.tag = Ok_1};
    struct Ok_ okOk_ = (struct Ok_){.tag = Ok_};
    struct Status_ statusOk_ = (struct Status_){.tag = Ok_1};
    int switch_1;
    switch ((struct Status_){.tag = Ok_1}.tag) {
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
    struct OkWrapper_ variant_4 = (struct OkWrapper_){.tag = T_, .T_ = (struct Ok_){.tag = Ok_}};
    struct OkWrapper_ okWrapper_ = variant_4;
    return 0;
}
