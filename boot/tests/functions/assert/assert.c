int main();

int main() {
    milone_assert(1);
    int call_ = 0;
    printf("pass\n");
    int call_1 = 0;
    milone_assert(0);
    int call_2 = 0;
    printf("not pass\n");
    int call_3 = 0;
    return 0;
}
