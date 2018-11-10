enum StatusTag_1 {
    Ok_1,
    Err_2,
};

struct Status_1 {
    enum StatusTag_1 tag;
    union {
        struct String Err_2;
    };
};

enum LimitTag_2 {
    LimitVal_3,
    LimitDiv_4,
};

struct Limit_2 {
    enum LimitTag_2 tag;
    union {
        int LimitVal_3;
    };
};

struct Tuple_1 {
    int t0;
    struct String t1;
};

enum ApiResponseTag_3 {
    ARJson_5,
    ARError_6,
    ARCancel_7,
};

struct ApiResponse_3 {
    enum ApiResponseTag_3 tag;
    union {
        struct String ARJson_5;
        struct Tuple_1 ARError_6;
    };
};

int main() {
    struct Status_1 ok_10 = (struct Status_1){.tag = Ok_1};
    struct Status_1 variant_19 = (struct Status_1){.tag = Err_2, .Err_2 = (struct String){.str = "No such file or directory.", .len = 26}};
    struct Status_1 err1_11 = variant_19;
    struct Status_1 variant_20 = (struct Status_1){.tag = Err_2, .Err_2 = (struct String){.str = "Access denied.", .len = 14}};
    struct Status_1 err2_12 = variant_20;
    int match_21;
    if (!((err1_11.tag == Ok_1))) goto next_2;
    exit(1);
    match_21 = 0;
    goto end_match_1;
next_2:;
    if (!((err1_11.tag == Err_2))) goto next_3;
    struct String e_13 = err1_11.Err_2;
    int if_22;
    if (!((str_cmp(e_13, (struct String){.str = "No such file or directory.", .len = 26}) != 0))) goto else_4;
    exit(2);
    if_22 = 0;
    goto end_if_5;
else_4:;
    if_22 = 0;
end_if_5:;
    match_21 = 0;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    int match_23;
    struct Limit_2 variant_24 = (struct Limit_2){.tag = LimitVal_3, .LimitVal_3 = 1};
    if (!((variant_24.tag == LimitVal_3))) goto next_7;
    int x_14 = variant_24.LimitVal_3;
    int if_25;
    if (!((x_14 != 1))) goto else_8;
    exit(1);
    if_25 = 0;
    goto end_if_9;
else_8:;
    if_25 = 0;
end_if_9:;
    match_23 = 0;
    goto end_match_6;
next_7:;
    if (!((variant_24.tag == LimitDiv_4))) goto next_10;
    exit(2);
    match_23 = 0;
    goto end_match_6;
next_10:;
    exit(1);
end_match_6:;
    int match_26;
    if (!(((struct ApiResponse_3){.tag = ARCancel_7}.tag == ARCancel_7))) goto next_12;
    match_26 = 0;
    goto end_match_11;
next_12:;
    exit(1);
    match_26 = 0;
    goto end_match_11;
end_match_11:;
    int match_27;
    struct Tuple_1 tuple_28;
    tuple_28.t0 = 404;
    tuple_28.t1 = (struct String){.str = "Not Found", .len = 9};
    struct ApiResponse_3 variant_29 = (struct ApiResponse_3){.tag = ARError_6, .ARError_6 = tuple_28};
    if (!((variant_29.tag == ARError_6))) goto next_15;
    int statusCode_16 = variant_29.ARError_6.t0;
    struct String statusText_17 = variant_29.ARError_6.t1;
    int if_30;
    int if_31;
    if (!((statusCode_16 != 404))) goto else_18;
    if_31 = 1;
    goto end_if_19;
else_18:;
    if_31 = (str_cmp(statusText_17, (struct String){.str = "Not Found", .len = 9}) != 0);
end_if_19:;
    if (!(if_31)) goto else_16;
    exit(1);
    if_30 = 0;
    goto end_if_17;
else_16:;
    if_30 = 0;
end_if_17:;
    match_27 = 0;
    goto end_match_14;
next_15:;
    exit(1);
    match_27 = 0;
    goto end_match_14;
end_match_14:;
    return 0;
}
