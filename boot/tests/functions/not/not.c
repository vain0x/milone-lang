int not_(int arg_) {
    printf("shadowing not\n");
    int call_1 = 0;
    return 0;
}

int main() {
    int if_;
    if (!(!(0))) goto else_1;
    printf("not false\n");
    int call_ = 0;
    if_ = 0;
    goto end_if_2;
else_1:;
    if_ = 0;
end_if_2:;
    int call_2 = not_(0);
    return 0;
}
