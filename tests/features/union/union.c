#include "milone.h"

enum Status_Tag;

struct Status_;

enum Limit_Tag;

struct Limit_;

enum ApiResponse_Tag;

struct ApiResponse_;

struct IntStringTuple2;

int main();

enum Status_Tag {
    Ok_1,
    Err_,
};

struct Status_ {
    enum Status_Tag tag;
    union {
        void* Err_;
    };
};

enum Limit_Tag {
    LimitVal_,
    LimitDiv_,
};

struct Limit_ {
    enum Limit_Tag tag;
    union {
        void* LimitVal_;
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
        void* ARJson_;
        void* ARError_;
    };
};

struct IntStringTuple2 {
    int t0;
    struct String t1;
};

int main() {
    struct Status_ ok_ = (struct Status_){.tag = Ok_1};
    void* box_ = (void*)milone_mem_alloc(1, sizeof(struct String));
    (*(((struct String*)box_))) = (struct String){.str = "No such file or directory.", .len = 26};
    struct Status_ variant_ = (struct Status_){.tag = Err_, .Err_ = box_};
    struct Status_ err1_ = variant_;
    void* box_1 = (void*)milone_mem_alloc(1, sizeof(struct String));
    (*(((struct String*)box_1))) = (struct String){.str = "Access denied.", .len = 14};
    struct Status_ variant_1 = (struct Status_){.tag = Err_, .Err_ = box_1};
    struct Status_ err2_ = variant_1;
    int match_;
    if ((err1_.tag != Ok_1)) goto next_2;
    milone_assert(0, 30, 6);
    int call_ = 0;
    match_ = 0;
    goto end_match_1;
next_2:;
    if ((err1_.tag != Err_)) goto next_3;
    struct String e_ = (*(((struct String*)err1_.Err_)));
    milone_assert((str_cmp(e_, (struct String){.str = "No such file or directory.", .len = 26}) == 0), 32, 6);
    int call_1 = 0;
    match_ = 0;
    goto end_match_1;
next_3:;
end_match_1:;
    int match_1;
    void* box_2 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_2))) = 1;
    struct Limit_ variant_2 = (struct Limit_){.tag = LimitVal_, .LimitVal_ = box_2};
    if ((variant_2.tag != LimitVal_)) goto next_5;
    int x_ = (*(((int*)variant_2.LimitVal_)));
    milone_assert((x_ == 1), 37, 6);
    int call_2 = 0;
    match_1 = 0;
    goto end_match_4;
next_5:;
    if ((variant_2.tag != LimitDiv_)) goto next_6;
    exit(2);
    match_1 = 0;
    goto end_match_4;
next_6:;
end_match_4:;
    int match_2;
    if (((struct ApiResponse_){.tag = ARCancel_}.tag != ARCancel_)) goto next_8;
    match_2 = 0;
    goto end_match_7;
next_8:;
    milone_assert(0, 46, 6);
    int call_3 = 0;
    match_2 = 0;
    goto end_match_7;
next_9:;
end_match_7:;
    int match_3;
    struct IntStringTuple2 tuple_;
    tuple_.t0 = 404;
    tuple_.t1 = (struct String){.str = "Not Found", .len = 9};
    void* box_3 = (void*)milone_mem_alloc(1, sizeof(struct IntStringTuple2));
    (*(((struct IntStringTuple2*)box_3))) = tuple_;
    struct ApiResponse_ variant_3 = (struct ApiResponse_){.tag = ARError_, .ARError_ = box_3};
    if ((variant_3.tag != ARError_)) goto next_11;
    int statusCode_ = (*(((struct IntStringTuple2*)variant_3.ARError_))).t0;
    struct String statusText_ = (*(((struct IntStringTuple2*)variant_3.ARError_))).t1;
    int match_4;
    if ((statusCode_ != 404)) goto next_14;
    match_4 = (str_cmp(statusText_, (struct String){.str = "Not Found", .len = 9}) == 0);
    goto end_match_13;
next_14:;
    if ((statusCode_ == 404)) goto next_15;
    match_4 = 0;
    goto end_match_13;
next_15:;
    exit(1);
end_match_13:;
    milone_assert(match_4, 51, 6);
    int call_4 = 0;
    match_3 = 0;
    goto end_match_10;
next_11:;
    milone_assert(0, 53, 6);
    int call_5 = 0;
    match_3 = 0;
    goto end_match_10;
next_12:;
end_match_10:;
    struct Status_ ok_1 = (struct Status_){.tag = Ok_1};
    void* okOk_ = 0;
    struct Status_ statusOk_ = (struct Status_){.tag = Ok_1};
    int match_5;
    if (((struct Status_){.tag = Ok_1}.tag != Ok_1)) goto next_17;
    match_5 = 0;
    goto end_match_16;
next_17:;
    if (((struct Status_){.tag = Ok_1}.tag != Err_)) goto next_18;
    milone_assert(0, 66, 4);
    int call_6 = 0;
    match_5 = 0;
    goto end_match_16;
next_18:;
end_match_16:;
    void* box_4 = (void*)milone_mem_alloc(1, sizeof(int));
    (*(((int*)box_4))) = 0;
    void* okWrapper_ = box_4;
    return 0;
}
