int main() {
    Box tuple_9 = {.t = malloc(2 * sizeof(Box))};
    tuple_9.t[0] = (Box){.i = 1};
    tuple_9.t[1] = (Box){.s = "snd"};
    Box a_2 = tuple_9;
    int op_10 = (1 * a_2.t[0].i);
    int x_3 = op_10;
    printf("%d\n", x_3);
    int call_11 = 0;
    Box tuple_12 = {.t = malloc(2 * sizeof(Box))};
    tuple_12.t[0] = (Box){.s = "fst"};
    tuple_12.t[1] = (Box){.i = 2};
    Box b_4 = tuple_12;
    char* y_5 = b_4.t[0].s;
    printf("%s\n", y_5);
    int call_13 = 0;
    Box tuple_14 = {.t = malloc(2 * sizeof(Box))};
    tuple_14.t[0] = (Box){.s = "z"};
    tuple_14.t[1] = (Box){.s = "w"};
    char* z_6 = tuple_14.t[0].s;
    printf("z=%s\n", z_6);
    int call_15 = 0;
    return 0;
}
