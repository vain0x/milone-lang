struct Tuple_1 {
    int t0;
    char* t1;
};

struct Tuple_2 {
    char* t0;
    int t1;
};

struct Tuple_3 {
    char* t0;
    char* t1;
};

struct Tuple_4 {
    struct Tuple_3 t0;
    char* t1;
};

int main() {
    struct Tuple_1 tuple_12;
    tuple_12.t0 = 1;
    tuple_12.t1 = "snd";
    struct Tuple_1 a_2 = tuple_12;
    int x_3 = (1 * a_2.t0);
    printf("%d\n", x_3);
    int call_13 = 0;
    struct Tuple_2 tuple_14;
    tuple_14.t0 = "fst";
    tuple_14.t1 = 2;
    struct Tuple_2 b_4 = tuple_14;
    char* y_5 = b_4.t0;
    printf("%s\n", y_5);
    int call_15 = 0;
    struct Tuple_3 tuple_16;
    tuple_16.t0 = "z";
    tuple_16.t1 = "w";
    char* z_6 = tuple_16.t0;
    char* w_7 = tuple_16.t1;
    printf("z=%s\n", z_6);
    int call_17 = 0;
    printf("w=%s\n", w_7);
    int call_18 = 0;
    struct Tuple_3 tuple_20;
    tuple_20.t0 = "p";
    tuple_20.t1 = "q";
    struct Tuple_4 tuple_19;
    tuple_19.t0 = tuple_20;
    tuple_19.t1 = "r";
    char* p_8 = tuple_19.t0.t0;
    char* q_9 = tuple_19.t0.t1;
    char* r_10 = tuple_19.t1;
    printf("p=%s\n", p_8);
    int call_21 = 0;
    return 0;
}
