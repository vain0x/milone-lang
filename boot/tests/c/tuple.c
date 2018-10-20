int main() {
    Box tuple_7 = {.t = malloc(2 * sizeof(Box))};
    tuple_7.t[0] = (Val){.i = 1};
    tuple_7.t[1] = (Val){.s = "snd"};
    Box a_2 = tuple_7;
    int op_8 = (1 * a_2.t[0].i);
    int x_3 = op_8;
    printf("%d\n", x_3);
    int call_9 = 0;
    Box tuple_10 = {.t = malloc(2 * sizeof(Box))};
    tuple_10.t[0] = (Val){.s = "fst"};
    tuple_10.t[1] = (Val){.i = 2};
    Box b_4 = tuple_10;
    char* y_5 = b_4.t[0].s;
    printf("%s\n", y_5);
    int call_11 = 0;
    return 0;
}
