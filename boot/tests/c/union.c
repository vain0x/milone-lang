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

int main() {
    struct Status_1 ok_7 = (struct Status_1){.tag = Ok_1};
    struct Status_1 variant_12 = (struct Status_1){.tag = Err_2, .Err_2 = (struct String){.str = "No such file or directory.", .len = 26}};
    struct Status_1 err1_8 = variant_12;
    struct Status_1 variant_13 = (struct Status_1){.tag = Err_2, .Err_2 = (struct String){.str = "Access denied.", .len = 14}};
    struct Status_1 err2_9 = variant_13;
    int match_14;
    if (!((err1_8.tag == Ok_1))) goto next_2;
    exit(1);
    match_14 = 0;
    goto end_match_1;
next_2:;
    if (!((err1_8.tag == Err_2))) goto next_3;
    struct String e_10 = err1_8.Err_2;
    int if_15;
    if (!((str_cmp(e_10, (struct String){.str = "No such file or directory.", .len = 26}) != 0))) goto else_4;
    exit(2);
    if_15 = 0;
    goto end_if_5;
else_4:;
    if_15 = 0;
end_if_5:;
    match_14 = 0;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    int match_16;
    struct Limit_2 variant_17 = (struct Limit_2){.tag = LimitVal_3, .LimitVal_3 = 1};
    if (!((variant_17.tag == LimitVal_3))) goto next_7;
    int x_11 = variant_17.LimitVal_3;
    int if_18;
    if (!((x_11 != 1))) goto else_8;
    exit(1);
    if_18 = 0;
    goto end_if_9;
else_8:;
    if_18 = 0;
end_if_9:;
    match_16 = 0;
    goto end_match_6;
next_7:;
    if (!((variant_17.tag == LimitDiv_4))) goto next_10;
    exit(2);
    match_16 = 0;
    goto end_match_6;
next_10:;
    exit(1);
end_match_6:;
    return 0;
}
