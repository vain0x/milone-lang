int main();

int main() {
    int le_ = (str_cmp((struct String){.str = "a", .len = 1}, (struct String){.str = "b", .len = 1}) < 0);
    int eq_ = (str_cmp((struct String){.str = "o", .len = 1}, (struct String){.str = "o", .len = 1}) == 0);
    int if_;
    int if_1;
    if (!(le_)) goto else_3;
    if_1 = eq_;
    goto end_if_4;
else_3:;
    if_1 = 0;
end_if_4:;
    if (!(if_1)) goto else_1;
    if_ = 0;
    goto end_if_2;
else_1:;
    if_ = 1;
end_if_2:;
    return if_;
}
