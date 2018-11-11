struct Tuple_1 {
    int t0;
    struct String t1;
};

struct Tuple_2 {
    struct String t0;
    int t1;
};

struct Tuple_3 {
    struct String t0;
    struct String t1;
};

struct Tuple_4 {
    struct Tuple_3 t0;
    struct String t1;
};

int main() {
    struct Tuple_1 tuple_;
    tuple_.t0 = 1;
    tuple_.t1 = (struct String){.str = "snd", .len = 3};
    struct Tuple_1 a_ = tuple_;
    int x_ = a_.t0;
    struct String _x_ = a_.t1;
    printf("%d\n", x_);
    int call_ = 0;
    struct Tuple_2 tuple_1;
    tuple_1.t0 = (struct String){.str = "fst", .len = 3};
    tuple_1.t1 = 2;
    struct Tuple_2 b_ = tuple_1;
    struct String y_ = b_.t0;
    int _y_ = b_.t1;
    printf("%s\n", y_.str);
    int call_1 = 0;
    struct Tuple_3 tuple_2;
    tuple_2.t0 = (struct String){.str = "z", .len = 1};
    tuple_2.t1 = (struct String){.str = "w", .len = 1};
    struct String z_ = tuple_2.t0;
    struct String w_ = tuple_2.t1;
    printf("z=%s\n", z_.str);
    int call_2 = 0;
    printf("w=%s\n", w_.str);
    int call_3 = 0;
    struct Tuple_3 tuple_4;
    tuple_4.t0 = (struct String){.str = "p", .len = 1};
    tuple_4.t1 = (struct String){.str = "q", .len = 1};
    struct Tuple_4 tuple_3;
    tuple_3.t0 = tuple_4;
    tuple_3.t1 = (struct String){.str = "r", .len = 1};
    struct String p_ = tuple_3.t0.t0;
    struct String q_ = tuple_3.t0.t1;
    struct String r_ = tuple_3.t1;
    printf("p=%s\n", p_.str);
    int call_4 = 0;
    return 0;
}
