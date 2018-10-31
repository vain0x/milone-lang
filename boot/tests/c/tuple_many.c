struct Tuple_1 {
    int t0;
    int t1;
};

struct Tuple_2 {
    int t0;
    int t1;
    struct Tuple_1 t2;
};

struct Tuple_3 {
    int t0;
    int t1;
    int t2;
    int t3;
    int t4;
    int t5;
    int t6;
    int t7;
    int t8;
    int t9;
    int t10;
};

int main() {
    struct Tuple_1 tuple_9;
    tuple_9.t0 = 3;
    tuple_9.t1 = 4;
    struct Tuple_2 tuple_8;
    tuple_8.t0 = 1;
    tuple_8.t1 = 2;
    tuple_8.t2 = tuple_9;
    int x_3 = tuple_8.t0;
    int y_4 = tuple_8.t1;
    int z_5 = tuple_8.t2.t0;
    int w_6 = tuple_8.t2.t1;
    int if_10;
    int if_11;
    int if_12;
    int if_13;
    if (!((x_3 == 1))) goto else_7;
    if_13 = (y_4 == 2);
    goto end_if_8;
else_7:;
    if_13 = 0;
end_if_8:;
    if (!(if_13)) goto else_5;
    if_12 = (z_5 == 3);
    goto end_if_6;
else_5:;
    if_12 = 0;
end_if_6:;
    if (!(if_12)) goto else_3;
    if_11 = (w_6 == 4);
    goto end_if_4;
else_3:;
    if_11 = 0;
end_if_4:;
    if (!(!(if_11))) goto else_1;
    exit(1);
    if_10 = 0;
    goto end_if_2;
else_1:;
    if_10 = 0;
end_if_2:;
    struct Tuple_3 tuple_14;
    tuple_14.t0 = 1;
    tuple_14.t1 = 2;
    tuple_14.t2 = 3;
    tuple_14.t3 = 4;
    tuple_14.t4 = 5;
    tuple_14.t5 = 6;
    tuple_14.t6 = 7;
    tuple_14.t7 = 8;
    tuple_14.t8 = 9;
    tuple_14.t9 = 10;
    tuple_14.t10 = 11;
    struct Tuple_3 t11_7 = tuple_14;
    return 0;
}
