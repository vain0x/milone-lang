int main() {
    struct String hello_3 = (struct String){.str = "Hello", .len = 5};
    struct String world_4 = (struct String){.str = ", world!", .len = 8};
    printf("%s\n", str_add(hello_3, world_4).str);
    int call_5 = 0;
    return 0;
}
