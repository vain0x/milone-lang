int main() {
    Val t_6 = {.t = malloc(2 * sizeof(Val))};
    t_6.t[0] = (Val){.i = 1};
    t_6.t[1] = (Val){.s = "snd"};
    Val a_2 = t_6;
    int op_7 = (1 * tuple_i(a_2, 0));
    int x_3 = op_7;
    printf("%d\n", x_3);
    Val t_8 = {.t = malloc(2 * sizeof(Val))};
    t_8.t[0] = (Val){.s = "fst"};
    t_8.t[1] = (Val){.i = 2};
    Val b_4 = t_8;
    char* y_5 = tuple_s(b_4, 0);
    printf("%s\n", y_5);
    return 0;
}
