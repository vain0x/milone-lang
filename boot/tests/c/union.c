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
    struct Status_1 variant_8 = (struct Status_1){.tag = Err_2, .Err_2 = (struct String){.str = "No such a file.", .len = 15}};
    struct Status_1 err1_6 = variant_8;
    struct Status_1 variant_9 = (struct Status_1){.tag = Err_2, .Err_2 = (struct String){.str = "Access denied.", .len = 14}};
    struct Status_1 err2_7 = variant_9;
    return 0;
}
