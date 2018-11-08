enum StatusTag_1 {
    Ok_1,
    Cancel_2,
};

struct Status_1 {
    enum StatusTag_1 tag;
};

int main() {
    struct Status_1 ok_5 = (struct Status_1){.tag = Ok_1};
    struct Status_1 cancel_6 = (struct Status_1){.tag = Cancel_2};
    return 0;
}
