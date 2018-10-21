int add_2(Box arg_6) {
    int x_3 = arg_6.t[0].i;
    int y_4 = arg_6.t[1].i;
    int op_7 = (x_3 + y_4);
    return op_7;
}

int main() {
    Box tuple_8 = {.t = malloc(2 * sizeof(Box))};
    tuple_8.t[0] = (Box){.i = 2};
    tuple_8.t[1] = (Box){.i = 3};
    int call_9 = add_2(tuple_8);
    int op_10 = (call_9 - 5);
    return op_10;
}
