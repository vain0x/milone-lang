int main() {
    Val t_3 = (Val) { .t2 = malloc(sizeof(Tuple2)) };
    *t_3.t2 = (Tuple2) { (Val) { .i = 1 }, (Val) { .s = "snd" } };
    Val a_2 = t_3;
    return 0;
}
