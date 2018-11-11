struct IntStringTuple2 {
    int t0;
    struct String t1;
};

int main() {
    exit(1);
    struct IntStringTuple2 t_ = ((struct IntStringTuple2){});
    int x_ = t_.t0;
    struct String y_ = t_.t1;
    exit(2);
    printf("%s\n", ((struct String){}).str);
    int call_ = 0;
    exit(0);
    return 0;
}
