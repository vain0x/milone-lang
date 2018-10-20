int main() {
    Val t_6 = (Val) { .t2 = malloc(sizeof(Tuple2)) };
    *t_6.t2 = (Tuple2) { (Val) { .i = 1 }, (Val) { .s = "snd" } };
    Val a_2 = t_6;
    int op_7 = (1 * fst_i(a_2));
    int x_3 = op_7;
    printf("%d\n", x_3);
    Val t_8 = (Val) { .t2 = malloc(sizeof(Tuple2)) };
    *t_8.t2 = (Tuple2) { (Val) { .s = "fst" }, (Val) { .i = 2 } };
    Val b_4 = t_8;
    char* y_5 = fst_s(b_4);
    printf("%s\n", y_5);
    return 0;
}
