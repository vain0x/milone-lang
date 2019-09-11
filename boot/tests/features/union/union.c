#include "milone.h"

enum Status_Tag;

struct Status_;

enum Limit_Tag;

struct Limit_;

enum ApiResponse_Tag;

struct ApiResponse_;

struct IntStringTuple2;

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
        struct String* Err_;
    };
};

enum Limit_Tag {
    LimitVal_,
    LimitDiv_,
};

struct Limit_ {
    enum Limit_Tag tag;
    union {
        int* LimitVal_;
    };
};

enum ApiResponse_Tag {
    ARJson_,
    ARError_,
    ARCancel_,
};

struct ApiResponse_ {
    enum ApiResponse_Tag tag;
    union {
        struct String* ARJson_;
        struct IntStringTuple2* ARError_;
    };
};

struct IntStringTuple2 {
    int t0;
    struct String t1;
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
        struct Ok_* T_;
    };
};

int main() {
    struct Status_ ok_ = (struct Status_){.tag = Ok_1};
    struct String* payload_ = (struct String*)malloc(sizeof(struct String));
    (*(((struct String*)payload_))) = (struct String){.str = "No such file or directory.", .len = 26};
    struct Status_ variant_ = (struct Status_){.tag = Err_, .Err_ = payload_};
    struct Status_ err1_ = variant_;
    struct String* payload_1 = (struct String*)malloc(sizeof(struct String));
    (*(((struct String*)payload_1))) = (struct String){.str = "Access denied.", .len = 14};
    struct Status_ variant_1 = (struct Status_){.tag = Err_, .Err_ = payload_1};
    struct Status_ err2_ = variant_1;
    int match_;
    if (!((err1_.tag == Ok_1))) goto next_2;
    exit(1);
    match_ = 0;
    goto end_match_1;
next_2:;
    if (!((err1_.tag == Err_))) goto next_3;
    struct String e_ = (*(err1_.Err_));
    int match_1;
    if (!(((str_cmp(e_, (struct String){.str = "No such file or directory.", .len = 26}) != 0) == 1))) goto next_5;
    exit(2);
    match_1 = 0;
    goto end_match_4;
next_5:;
    if (!(((str_cmp(e_, (struct String){.str = "No such file or directory.", .len = 26}) != 0) == 0))) goto next_6;
    match_1 = 0;
    goto end_match_4;
next_6:;
    exit(1);
end_match_4:;
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    int match_2;
    int* payload_2 = (int*)malloc(sizeof(int));
    (*(((int*)payload_2))) = 1;
    struct Limit_ variant_2 = (struct Limit_){.tag = LimitVal_, .LimitVal_ = payload_2};
    if (!((variant_2.tag == LimitVal_))) goto next_8;
    int x_ = (*(variant_2.LimitVal_));
    int match_3;
    if (!(((x_ != 1) == 1))) goto next_11;
    exit(1);
    match_3 = 0;
    goto end_match_10;
next_11:;
    if (!(((x_ != 1) == 0))) goto next_12;
    match_3 = 0;
    goto end_match_10;
next_12:;
    exit(1);
end_match_10:;
    match_2 = 0;
    goto end_match_7;
next_8:;
    if (!((variant_2.tag == LimitDiv_))) goto next_9;
    exit(2);
    match_2 = 0;
    goto end_match_7;
next_9:;
end_match_7:;
    int match_4;
    if (!(((struct ApiResponse_){.tag = ARCancel_}.tag == ARCancel_))) goto next_14;
    match_4 = 0;
    goto end_match_13;
next_14:;
    exit(1);
    match_4 = 0;
    goto end_match_13;
next_15:;
end_match_13:;
    int match_5;
    struct IntStringTuple2 tuple_;
    tuple_.t0 = 404;
    tuple_.t1 = (struct String){.str = "Not Found", .len = 9};
    struct IntStringTuple2* payload_3 = (struct IntStringTuple2*)malloc(sizeof(struct IntStringTuple2));
    (*(((struct IntStringTuple2*)payload_3))) = tuple_;
    struct ApiResponse_ variant_3 = (struct ApiResponse_){.tag = ARError_, .ARError_ = payload_3};
    if (!((variant_3.tag == ARError_))) goto next_17;
    int statusCode_ = (*(variant_3.ARError_)).t0;
    struct String statusText_ = (*(variant_3.ARError_)).t1;
    int match_6;
    int match_7;
    if (!(((statusCode_ != 404) == 1))) goto next_21;
    match_7 = 1;
    goto end_match_20;
next_21:;
    if (!(((statusCode_ != 404) == 0))) goto next_22;
    match_7 = (str_cmp(statusText_, (struct String){.str = "Not Found", .len = 9}) != 0);
    goto end_match_20;
next_22:;
    exit(1);
end_match_20:;
    if (!((match_7 == 1))) goto next_23;
    exit(1);
    match_6 = 0;
    goto end_match_19;
next_23:;
    if (!((match_7 == 0))) goto next_24;
    match_6 = 0;
    goto end_match_19;
next_24:;
    exit(1);
end_match_19:;
    match_5 = 0;
    goto end_match_16;
next_17:;
    exit(1);
    match_5 = 0;
    goto end_match_16;
next_18:;
end_match_16:;
    struct Status_ ok_1 = (struct Status_){.tag = Ok_1};
    struct Ok_ okOk_ = (struct Ok_){.tag = Ok_};
    struct Status_ statusOk_ = (struct Status_){.tag = Ok_1};
    int match_8;
    if (!(((struct Status_){.tag = Ok_1}.tag == Ok_1))) goto next_26;
    match_8 = 0;
    goto end_match_25;
next_26:;
    if (!(((struct Status_){.tag = Ok_1}.tag == Err_))) goto next_27;
    exit(1);
    match_8 = 0;
    goto end_match_25;
next_27:;
end_match_25:;
    struct Ok_* payload_4 = (struct Ok_*)malloc(sizeof(struct Ok_));
    (*(((struct Ok_*)payload_4))) = (struct Ok_){.tag = Ok_};
    struct OkWrapper_ variant_4 = (struct OkWrapper_){.tag = T_, .T_ = payload_4};
    struct OkWrapper_ okWrapper_ = variant_4;
    return 0;
}
