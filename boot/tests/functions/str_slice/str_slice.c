int main();

int main() {
    struct String str_ = (struct String){.str = "Hello, John!", .len = 12};
    int if_;
    struct String slice_ = str_slice(str_, 0, 4);
    if (!((str_cmp(slice_, (struct String){.str = "Hello", .len = 5}) != 0))) goto else_1;
    exit(1);
    if_ = 0;
    goto end_if_2;
else_1:;
    if_ = 0;
end_if_2:;
    int if_1;
    struct String slice_1 = str_slice(str_, 7, 10);
    if (!((str_cmp(slice_1, (struct String){.str = "John", .len = 4}) != 0))) goto else_3;
    exit(2);
    if_1 = 0;
    goto end_if_4;
else_3:;
    if_1 = 0;
end_if_4:;
    int if_2;
    struct String slice_2 = str_slice(str_, 11, 11);
    if (!((str_cmp(slice_2, (struct String){.str = "!", .len = 1}) != 0))) goto else_5;
    exit(3);
    if_2 = 0;
    goto end_if_6;
else_5:;
    if_2 = 0;
end_if_6:;
    return 0;
}
