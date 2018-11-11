int main() {
    int if_;
    if (!(1)) goto else_1;
    printf("then\n");
    int call_ = 0;
    struct String hello_ = (struct String){.str = "hello", .len = 5};
    int if_1;
    if (!(1)) goto else_3;
    if_1 = 0;
    goto end_if_4;
else_3:;
    struct String message_ = hello_;
    if_1 = 1;
end_if_4:;
    if_ = if_1;
    goto end_if_2;
else_1:;
    printf("else\n");
    int call_1 = 0;
    if_ = 1;
end_if_2:;
    return if_;
}
