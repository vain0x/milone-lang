int main();

int main() {
    struct String hello_ = (struct String){.str = "Hello", .len = 5};
    struct String world_ = (struct String){.str = ", world!", .len = 8};
    printf("%s\n", str_add(hello_, world_).str);
    int call_ = 0;
    return 0;
}
