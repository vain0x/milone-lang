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

int main() {
    struct Status_1 ok_5 = (struct Status_1){.tag = Ok_1};
    struct Status_1 variant_9 = (struct Status_1){.tag = Err_2, .Err_2 = (struct String){.str = "No such file or directory.", .len = 26}};
    struct Status_1 err1_6 = variant_9;
    struct Status_1 variant_10 = (struct Status_1){.tag = Err_2, .Err_2 = (struct String){.str = "Access denied.", .len = 14}};
    struct Status_1 err2_7 = variant_10;
    int match_11;
    if (!((err1_6.tag == Ok_1))) goto next_2;
    exit(1);
    match_11 = 0;
    goto end_match_1;
next_2:;
    if (!((err1_6.tag == Err_2))) goto next_3;
    struct String e_8 = err1_6.Err_2;
    int if_12;
    if (!((str_cmp(e_8, (struct String){.str = "No such file or directory.", .len = 26}) != 0))) goto else_4;
    exit(2);
    if_12 = 0;
    goto end_if_5;
else_4:;
    if_12 = 0;
end_if_5:;
    match_11 = 0;
    goto end_match_1;
next_3:;
    exit(1);
end_match_1:;
    return match_11;
}
