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
    struct Tuple_1 tuple_14;
    tuple_14.t0 = 1;
    tuple_14.t1 = "snd";
    struct Tuple_1 a_3 = tuple_14;
    int x_4 = a_3.t0;
    char* _x_5 = a_3.t1;
    printf("%d\n", x_4);
    int call_15 = 0;
    struct Tuple_2 tuple_16;
    tuple_16.t0 = "fst";
    tuple_16.t1 = 2;
    struct Tuple_2 b_6 = tuple_16;
    char* y_7 = b_6.t0;
    int _y_8 = b_6.t1;
    printf("%s\n", y_7);
    int call_17 = 0;
    struct Tuple_3 tuple_18;
    tuple_18.t0 = "z";
    tuple_18.t1 = "w";
    char* z_9 = tuple_18.t0;
    char* w_10 = tuple_18.t1;
    printf("z=%s\n", z_9);
    int call_19 = 0;
    printf("w=%s\n", w_10);
    int call_20 = 0;
    struct Tuple_3 tuple_22;
    tuple_22.t0 = "p";
    tuple_22.t1 = "q";
    struct Tuple_4 tuple_21;
    tuple_21.t0 = tuple_22;
    tuple_21.t1 = "r";
    char* p_11 = tuple_21.t0.t0;
    char* q_12 = tuple_21.t0.t1;
    char* r_13 = tuple_21.t1;
    printf("p=%s\n", p_11);
    int call_23 = 0;
    return 0;
}
