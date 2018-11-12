enum Status_Tag {
    Ok_,
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

int main() {
    struct Status_ ok_ = (struct Status_){.tag = Ok_};
    struct Status_ variant_ = (struct Status_){.tag = Err_, .Err_ = (struct String){.str = "No such file or directory.", .len = 26}};
    struct Status_ err1_ = variant_;
    struct Status_ variant_1 = (struct Status_){.tag = Err_, .Err_ = (struct String){.str = "Access denied.", .len = 14}};
    struct Status_ err2_ = variant_1;
    int match_;
    if (!((err1_.tag == Ok_))) goto next_2;
    exit(1);
    match_ = 0;
    goto end_match_1;
next_2:;
    if (!((err1_.tag == Err_))) goto next_3;
    struct String e_ = err1_.Err_;
    int if_;
    if (!((str_cmp(e_, (struct String){.str = "No such file or directory.", .len = 26}) != 0))) goto else_4;
    exit(2);
    if_ = 0;
    goto end_if_5;
else_4:;
    if_ = 0;
end_if_5:;
    match_ = 0;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    int match_1;
    struct Limit_ variant_2 = (struct Limit_){.tag = LimitVal_, .LimitVal_ = 1};
    if (!((variant_2.tag == LimitVal_))) goto next_7;
    int x_ = variant_2.LimitVal_;
    int if_1;
    if (!((x_ != 1))) goto else_8;
    exit(1);
    if_1 = 0;
    goto end_if_9;
else_8:;
    if_1 = 0;
end_if_9:;
    match_1 = 0;
    goto end_match_6;
next_7:;
    if (!((variant_2.tag == LimitDiv_))) goto next_10;
    exit(2);
    match_1 = 0;
    goto end_match_6;
next_10:;
    exit(1);
end_match_6:;
    int match_2;
    if (!(((struct ApiResponse_){.tag = ARCancel_}.tag == ARCancel_))) goto next_12;
    match_2 = 0;
    goto end_match_11;
next_12:;
    exit(1);
    match_2 = 0;
    goto end_match_11;
next_13:;
end_match_11:;
    int match_3;
    struct IntStringTuple2 tuple_;
    tuple_.t0 = 404;
    tuple_.t1 = (struct String){.str = "Not Found", .len = 9};
    struct ApiResponse_ variant_3 = (struct ApiResponse_){.tag = ARError_, .ARError_ = tuple_};
    if (!((variant_3.tag == ARError_))) goto next_15;
    int statusCode_ = variant_3.ARError_.t0;
    struct String statusText_ = variant_3.ARError_.t1;
    int if_2;
    int if_3;
    if (!((statusCode_ != 404))) goto else_18;
    if_3 = 1;
    goto end_if_19;
else_18:;
    if_3 = (str_cmp(statusText_, (struct String){.str = "Not Found", .len = 9}) != 0);
end_if_19:;
    if (!(if_3)) goto else_16;
    exit(1);
    if_2 = 0;
    goto end_if_17;
else_16:;
    if_2 = 0;
end_if_17:;
    match_3 = 0;
    goto end_match_14;
next_15:;
    exit(1);
    match_3 = 0;
    goto end_match_14;
next_20:;
end_match_14:;
    return 0;
}
